#include "j1939.h"
#include "j1939app.h"
#include "UDS/uds.h"	   


/* wait 250 ms before claiming an address */
#define J1939_ADDRESS_CLAIM_TIME_OUT           (2500u/J1939CFG_TICK_PERIOD)

/* apprx number of messsags in 250ms */
#define J1939_BIP_MSGS_250MS                                           477u

uint32_t ecff_cntr=0;

/* babbling-idiot protection variables */
uint16_t j1939_bip_time[ J1939CFG_PORTS_NUM ];
uint16_t j1939_bip_tx_cnt[ J1939CFG_PORTS_NUM ];
uint16_t j1939_bip_tx_cnt_max[ J1939CFG_PORTS_NUM ];
uint8_t  j1939_bip_tx_is_disabled[ J1939CFG_PORTS_NUM ];
uint16_t j1939_bip_tx_cnt_allowed[ J1939CFG_PORTS_NUM ];

/* address claim algorithm variables */
uint16_t j1939_address_claim_time[ J1939CFG_PORTS_NUM ];
uint8_t  j1939_address_claim_requested[ J1939CFG_PORTS_NUM ];
uint8_t  j1939_address_claim_has_failed[ J1939CFG_PORTS_NUM ];
uint8_t  j1939_address_claim_tx_requested[ J1939CFG_PORTS_NUM ];
uint8_t  j1939_address_claim_has_been_sent[ J1939CFG_PORTS_NUM ];
uint8_t  j1939_address_claim_was_successful[ J1939CFG_PORTS_NUM ];
uint8_t  j1939_address_cannot_claim_tx_requested[ J1939CFG_PORTS_NUM ];
uint8_t  j1939_address_claim_received_higher_priority[ J1939CFG_PORTS_NUM ];

/* source address */
uint8_t j1939_sa[ J1939CFG_PORTS_NUM ];

/* modifiable name field */
uint8_t j1939_name[ J1939CFG_PORTS_NUM ][ 8 ];

uint32_t msgID;
can_t can;
uint8_t Countr1;




// sets the application's max allowable bus load threshold
// INPUT: rate - percent load from 0 to 100
void j1939_bip_tx_rate_allowed_set ( uint8_t p, uint8_t rate ) {

  if( rate <= 100)
    j1939_bip_tx_cOUnt_allowed[p] = (J1939_BIP_MSGS_250MS*(uint16_t)rate)/100U;

  return;
}

//Returns the application's peak bus load usage
//RETURN: percent load from 0 to 100
uint8_t j1939_bip_tx_rate_max_get ( uint8_t p ) {

  return ((j1939_bip_tx_cnt_max[p] * 100U)/J1939_BIP_MSGS_250MS);
}

//Initializes the entire J1939 protocol stack 
void j1939_init (void) {

  uint8_t p;

  for( p = 0; p < J1939CFG_PORTS_NUM; p++ ) { 

    /* babbling-idiot protection variables */
    j1939_bip_time[p] = 0;
    j1939_bip_tx_cnt[p] = 0;
    j1939_bip_tx_cnt_max[p] = 0;
    j1939_bip_tx_is_disabled[p] = 0;
    j1939_bip_tx_cnt_allowed[p] = J1939_BIP_MSGS_250MS/4U;

    /* address claim algorithm variables */
    j1939_address_claim_time[p] = 0;
    j1939_address_claim_requested[p] = 0;
    j1939_address_claim_has_failed[p] = 0;
    j1939_address_claim_tx_requested[p] = 1;
    j1939_address_claim_has_been_sent[p] = 0;
    j1939_address_claim_was_successful[p] = 0;
    j1939_address_cannot_claim_tx_requested[p] = 0;
    j1939_address_claim_received_higher_priority[p] = 0;

    /* get the source address */
    j1939_sa[p] = j1939app_sa_get(p);
  }

  j1939tp_init();
  j1939app_init();
}



/*
** This function is the first level of inspection of a J1939 message.  It's
** sole purpose is to decide where the message should go from here.
** INPUT: msg - pointer to J1939 message
*/
void
j1939_process (j1939_t *msg) {

  uint8_t p;
  uint8_t cnt, tmp_sa;
  uint32_t req_pgn;
  // what CAN port do we need to service
      p = msg->port;
  {
    appTimer[p]++;
    OSTmr_Count_Start(&canDataReceiveTimer[p]);canDataStatus[p]=1;
  switch( msg->pgn ) {

    /* address claim PGN */
    case J1939_PGN_ADDRESS_CLAIMED: //{

      /* what CAN port do we need to service */
      p = msg->port;

      /* if this message isn't using the same source address, ignore it */
      if( msg->src != j1939_sa[p] )
        break;

      /* find first byte which is different (MSB is byte 7) */
      for( cnt=7; (msg->buf[cnt]==j1939_name[p][cnt]) && (cnt > 0); cnt-- );

      /* is their's lower (higher priority)? if it's the same NAME
         we treat it as higher priority and won't transmit */
      if( msg->buf[cnt] <= j1939_name[p][cnt] ) {
        
        /* we can't use the current address anymore */
        j1939_address_claim_was_successful[p] = 0;

        /* we now know there is a higher priority CA out there */
        j1939_address_claim_received_higher_priority[p] = 1;

        /* see if the application has a new address for us to try */
        tmp_sa = j1939app_sa_get(p);

        /* 254 or 255 indicate no more addresses are available */
        if( tmp_sa < 254 ) {

          j1939_address_claim_time[p] = 0;
          j1939_address_claim_tx_requested[p] = 1;
          j1939_address_cannot_claim_tx_requested[p] = 0;
          j1939_address_claim_has_been_sent[p] = 0;
          j1939_address_claim_was_successful[p] = 0;
          j1939_address_claim_received_higher_priority[p] = 0;
          j1939_sa[p] = tmp_sa;

        } else {

          /* we failed to claim an address */
          j1939_address_claim_has_failed[p] = 1;

          /* we can not send a 'cannot claim' without first sending a 'claim' */
          if( j1939_address_claim_has_been_sent[p] )
            j1939_address_cannot_claim_tx_requested[p] = 1;
        }

      } else {

        /* we're high priority, so send another address claim message (only
           if we haven't already received a higher priority before this) */
        if( j1939_address_claim_received_higher_priority[p] == 0 )
          j1939_address_claim_tx_requested[p] = 1;
      }

      break;
   // }

    case J1939_PGN_COMMANDED_ADDRESS: //{

      /* what CAN port do we need to service */
      p = msg->port;

      /* find first byte which is different */
      for( cnt = 0; cnt < 8; cnt++ )
        if( msg->buf[cnt] != j1939_name[p][cnt] )
          break;

      /* is the NAME the same as ours? */
      if( cnt == 8 ) {
        
        /* what is our new address */
        tmp_sa = msg->buf[8];

        /* 254 or 255 indicates no more addresses are available */
        if( tmp_sa < 254 ) {

          /* we can't use the current address anymore */
          j1939_address_claim_time[p] = 0;
          j1939_address_claim_tx_requested[p] = 1;
          j1939_address_cannot_claim_tx_requested[p] = 0;
          j1939_address_claim_has_been_sent[p] = 0;
          j1939_address_claim_was_successful[p] = 0;
          j1939_address_claim_received_higher_priority[p] = 0;
          j1939_sa[p] = tmp_sa;
        }
      }

      break;
   // }

    /* request */
    case J1939_PGN_REQUEST: //{

      /* find out what pgn is being requested */
      req_pgn = msg->buf[0] | ((uint32_t)msg->buf[1]<<8UL) |
                              ((uint32_t)msg->buf[2]<<16UL);

      /* if it's a request for address claimed, we handle it here */
      if( req_pgn == J1939_PGN_ADDRESS_CLAIMED ) {

         j1939_address_claim_requested[msg->port] = 1;

      } else {

        j1939app_process_req(msg,req_pgn);
      }

      break;
   // }

    /* tp - connection management message */
    case J1939_PGN_TP_CM: 
         j1939tp_post_cm(msg);
      break;
    case J1939_PGN_TP_CM1:
      j1939tp_post_cm(msg);
      break;
    
    /* tp - data transfer message */
    case J1939_PGN_TP_DT:
        j1939tp_post_dt(msg);
      break;
    case J1939_PGN_TP_DT1:
      j1939tp_post_dt(msg);
      break;
      
    case J1939_PGN_DM1:
      j1939dm_process( msg );
    break;      

    /* anything not handled here is handed to application layer */
    default:
        if(msg->port == 1)
        {
          j1939app_process(msg);
        }
        else
        {
         j1939app_process_MCAN1(msg);
        }
      break;
  }
}

  return;
}



/*
** This function translates a J1939 message into a CAN frame which
** is then buffered for transmission.
** INPUT: msg - pointer to J1939 message
** RETURN: 0 - success
**         1 - failure
*/
uint8_t
j1939_tx ( j1939_t *msg ) {

  can_t can;
  uint8_t p;
  uint8_t cnt, ret;

  /* CAN port */
  p = msg->port;

  /* is babbling-idiot protection active? */
  if( j1939_bip_tx_is_disabled[p] )
    return 1;

  /* copy over buffer */
  for( cnt = 0; cnt < msg->buf_len; cnt++ )
    can.buf[cnt] = msg->buf[cnt];

  /* get size of data to go out */
  can.buf_len = (uint8_t)msg->buf_len;

  /* we start off by loading the pgn into the CAN frame */
  can.id = msg->pgn;

  /* is the protocol format less than 240, the ps field is the dst */
  if( ((uint16_t)msg->pgn) < ((uint16_t)0xf000) )
    can.id |= msg->dst;

  /* load in the priority */
  can.id |= (((uint32_t)(msg->pri & 0x7)) << 18UL);

  /* make room for source address and load it in */
  can.id <<= 8;
  can.id |= msg->src;

  /* the 31st bit being set indicates its an extended frame message */
  can.id |= (B31);

  /* send it to the CAN buffer/isr routines */
  ret = can_tx(p,&can);

  /* keep track of number of transmits for babble protection */
  if( ret == 0 )
    if( j1939_bip_tx_cnt[p] < J1939_BIP_MSGS_250MS )
      j1939_bip_tx_cnt[p]++;

  return ret;
}



/*
** This function buffers a J1939 message for transmission.  For multi-packet
** messages, *status will be set to J1939TP_INPROCESS during transmission,
** J1939TP_DONE for success, or J1939TP_FAILED for failure.
** INPUT: msg - pointer to J1939 message
**        status - pointer to status variable
** RETURN: 0 - success
**         1 - failure
*/
uint8_t
j1939_tx_app ( j1939_t *msg, uint8_t *status ) {
  
  /* we can not transmit until we have claimed an address */
  if( j1939_address_claim_was_successful[msg->port] == 0 )
    return 1;

  /* every message has our source address */
  msg->src = j1939_sa[msg->port];

  /* per J1939/21 any global request must also be processed by this ECU.
     also, the only msg that can be less than 8 bytes is a request */
  if( msg->pgn == J1939_PGN_REQUEST ) {

    if( msg->dst == J1939_ADDR_GLOBAL )
      j1939_process(msg);
    
  } else if( msg->buf_len < 8 ) {

    return 1;
  }

  /* is it single or multi-packet msg? */
  if( msg->buf_len <= 8 )
    return j1939_tx(msg);
  else
    return j1939tp_tx(msg,status);
}



/*
** Transmits a J1939 request message. (dst of 255 = global request)
** INPUT: p=CAN port, req_pgn=requested PGN, dst = destination address
** RETURN: 0=success, 1=failure
*/
uint8_t
j1939_tx_req ( uint8_t p, uint32_t req_pgn, uint8_t dst )
{
  j1939_t msg;
  uint8_t buf[8];

  msg.pri = 6;
  msg.port = p;
  msg.buf = buf;
  msg.dst = dst;
  msg.buf_len = 3;
  msg.buf[0] = (uint8_t)req_pgn;
  msg.buf[1] = (uint8_t)(req_pgn >> 8);
  msg.buf[2] = (uint8_t)(req_pgn >> 16);
  msg.pgn = J1939_PGN_REQUEST;
  printf("trmb");
  return j1939_tx_app( &msg, 0 );
}



uint8_t
j1939_tx_ackx ( uint8_t p, uint32_t req_pgn, uint8_t src, uint8_t np )
{
  j1939_t msg;
  uint8_t buf[8];

  msg.pri = 6;
  msg.port = p;
  msg.buf = buf;
  msg.dst = 255;
  msg.buf_len = 8;
  msg.buf[0] = np;
  msg.buf[1] = 0xFF;
  msg.buf[2] = 0xFF;
  msg.buf[3] = 0xFF;
  msg.buf[4] = src;
  msg.buf[5] = (uint8_t)req_pgn;
  msg.buf[6] = (uint8_t)(req_pgn >> 8);
  msg.buf[7] = (uint8_t)(req_pgn >> 16);
  msg.pgn = J1939_PGN_ACK;

  return j1939_tx_app( &msg, 0 );
}



/*
** Transmit a negative ACK.
*/
uint8_t
j1939_tx_ackn ( uint8_t p, uint32_t req_pgn, uint8_t src )
{
  return j1939_tx_ackx( p, req_pgn, src, 1 );
}


/*
** Transmit a positive ACK.
*/
uint8_t
j1939_tx_ackp ( uint8_t p, uint32_t req_pgn, uint8_t src )
{
  return j1939_tx_ackx( p, req_pgn, src, 0 );
}


/*
** Buffers an address claimed message for transmission.
** INPUT: src - source address of controlling application
** RETURN: 0 - success
**         1 - failure
*/
uint8_t
j1939_tx_address_claimed ( uint8_t p, uint8_t src ) {

  j1939_t msg;

  /* destination must be global for all address claim msgs. J1939-81 4.2.2 */
  msg.dst = J1939_ADDR_GLOBAL;
  msg.src = src;
  msg.pgn = J1939_PGN_ADDRESS_CLAIMED;
  msg.pri = 6;
  msg.buf = &j1939_name[p][0];
  msg.buf_len = 8;
  msg.port = p;

  return j1939_tx( &msg );
}



/*
** Translates a CAN frame into a J1939 message
*/
//void
//j1939_post ( uint8_t p, can_t *can ) {
//
//  j1939_t msg;
//
//  /* if EDP is set, or if it's a 2.0a msg, the message should be ignored */
//  if( (can->id & B25) || ((can->id & B31) == 0) )
//    return;
//
//  /* get source address of frame and chop it off.
//     reference SAE J1939/21 for more information */
//  msg.src = (uint8_t)can->id;
//  can->id >>= 8;
//
//  /* if the protocol formart is less than 240, it is destination specific */
//  if( ((uint8_t)(can->id >> 8)) < 240 ) {
//
//    /* destination specific */
//    msg.dst = (uint8_t)can->id;
//    msg.pgn = can->id & 0x1ff00;
//
//  } else {
//
//    /* ps field is a group extension */
//    msg.dst = J1939_ADDR_GLOBAL;
//    msg.pgn = can->id & 0x1ffff;
//  }
//
//  /* if this packet isn't for us or isn't a broadcast, then ignore */
//  if( (msg.dst != j1939_sa[p]) && (msg.dst != J1939_ADDR_GLOBAL) )
//    return;
//
//  /* CAN port */
//  msg.port = p;
//   
//  /* J1939_post doesn't own the passed memory so this is ok.  this memory
//     is from the interrupt receive buffer so should be quick and dirty.  */
//  msg.buf = can->buf;
//  msg.buf_len = can->buf_len;
//
//  /* we decoded the CAN frame into the J1939 parts, so process it */
//  j1939_process(&msg);
//}


void j1939_post ( uint8_t p, can_t *can ,uint8_t cnt) 
{
  j1939_t msg;
  uint8_t lp;
  uint8_t dtabuf[9];
  msg.port = p;
  /* if EDP is set, or if it's a 2.0a msg, the message should be ignored */
//  if( (mcan_ram[p].rx_mbox[writePointer[p]].id & B25) || ((mcan_ram[p].rx_mbox[writePointer[p]].id & B31) == 0) )
//    return;
//  if(dataPointer[p]>110)
//  {
//      printf("msgID=%lX,dataPointer[p]=%d\r\n",msgID,dataPointer[p]);
//  }
  for(lp=0;lp<cnt;lp++)  // 20 is default
  {
  if(dataPointer[p]!=0)
  {
      dataPointer[p]--;
  /* get source address of frame and chop it off.
     reference SAE J1939/21 for more information */
  msg.src = (uint8_t)mcan_ram[p].rx_mbox[readPointer[p]].id;
  //printf("msg.src=%d\r\n",msg.src);
  msgID = mcan_ram[p].rx_mbox[readPointer[p]].id;
  //printf("msgID=%lX,dataPointer=%d\r\n",msgID,dataPointer[p]);
  
  memset((uint8_t *)dtabuf, 0, (sizeof(dtabuf)));
  for (int i=0;i<8;i++)
  {
      dtabuf[i] = mcan_ram[p].rx_mbox[readPointer[p]].buf[i];
  }
  msg.buf = (uint8_t*)dtabuf;
  msg.buf_len = mcan_ram[p].rx_mbox[readPointer[p]].fd;
  if(mcan_ram[p].rx_mbox[readPointer[p]].id < 0x800)    // standard CAN ID processing
  {
      msg.pgn = mcan_ram[p].rx_mbox[readPointer[p]].id;
     // printf("msg.pgn=%lX\r\n",msg.pgn);
  }
  else                                                  // Extended CAN ID processing
  {
      mcan_ram[p].rx_mbox[readPointer[p]].id >>= 8;
  /* if the protocol format is less than 240, it is destination specific */
  if( ((uint8_t)(mcan_ram[p].rx_mbox[readPointer[p]].id >> 8)) < 240 ) 
  {
    /* destination specific */
    msg.dst = (uint8_t)mcan_ram[p].rx_mbox[readPointer[p]].id;
    msg.pgn = mcan_ram[p].rx_mbox[readPointer[p]].id & 0x1ff00;

  } 
  else 
  {
    /* ps field is a group extension */
    msg.dst = J1939_ADDR_GLOBAL;
    msg.pgn = mcan_ram[p].rx_mbox[readPointer[p]].id & 0xffff;           //0x1ffff
  }
  }
  
  /* if this packet isn't for us or isn't a broadcast, then ignore */
  if( (msg.dst != j1939_sa[p]) && (msg.dst != J1939_ADDR_GLOBAL) )
  {
//    return;                   //Sathya - commented
  }
  /* CAN port */
  msg.port = p;
   
  /* J1939_post doesn't own the passed memory so this is ok.  this memory
     is from the interrupt receive buffer so should be quick and dirty.  */
  if(msg.pgn!=0)
  {
     // Countr1++;
    /* we decoded the CAN frame into the J1939 parts, so process it */
      if(msgID == 0x18DAF100)//yat
    {
       i15765_update(msg.port);
       uds_update();
    }
  else
  {
  j1939_process(&msg);

  }
    // 
    mcan_ram[p].rx_mbox[readPointer[p]].fd=0;
    mcan_ram[p].rx_mbox[readPointer[p]].id=0;
    //memset((uint8_t *)mcan_ram[p].rx_mbox[readPointer[p]].buf, 0, (sizeof(mcan_ram[p].rx_mbox[readPointer[p]].buf)));
    memset((uint8_t *)mcan_ram[p].rx_mbox[readPointer[p]].buf, 0, 8);
    readPointer[p]++;
    if(readPointer[p]>=(CAN_RX_BUF_LEN-1))
    {
        readPointer[p]=0;
    }
  }
  else
  {
      
  }
  }
  else
  {
      break;  // data pointer is zero so we can exit the loop run
  }
  }
  return;
}

// This function is the time base for the entire J1939 module.
void
j1939_update ( uint8_t count ) {
  uint8_t p=1;
  { 

    /* update address claim state machine */
    j1939_update_address_claim(p);

    /* update babbling-idiot protection */
    j1939_bip_update(p);

    /* update transport protocol */
    j1939tp_update(p);
  }

  /* application layer that transmits messages periodically */
  j1939app_update();

  return;
}
