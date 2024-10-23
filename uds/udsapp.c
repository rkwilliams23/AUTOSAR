#include "uds.h"
#include "udsapp.h"

#define UDSAPP_NOSEED            0
#define UDSAPP_DOWNLOAD          1
#define UDSAPP_UPLOAD            2
#define UDSAPP_TRANSFER_FINISHED 3

static uint8_t *udsapp_tx_address;
static uint32_t udsapp_tx_size;
static uint32_t udsapp_tx_bytes;
static uint16_t udsapp_tx_plen;
static uint8_t udsapp_tx_dir;
static uint8_t udsapp_tx_bsc;
static uint8_t udsapp_seed_flag = UDSAPP_NOSEED;

static uint32_t udsapp_rdbpi_timer[UDSCFG_RDBPI_MAX];
static uint32_t udsapp_rdbpi_reload[UDSCFG_RDBPI_MAX];
static uint8_t udsapp_rdbpi_did[UDSCFG_RDBPI_MAX];
static uint8_t udsapp_rdbpi_ta[UDSCFG_RDBPI_MAX];
uint8_t udsapp_rdbpi_count;



/*
** Triggers a reset of the ECU
** Response message must be sent BEFORE reset
**
** INPUT type - reset type to occur
**/
void
udsapp_reset( uint8_t type )
{
  //response message send BEFORE reset
  uint8_t rsp[3];
  rsp[0] = UDS_SRVC_ERPR + UDS_PRSP;
  rsp[1] = type;
  rsp[2] = power_down_time;
  uds_tx(response, 3);
}

/*
** This function is called by uds_init.
** Any initialization code should go here.
*/
void
udsapp_init( void )
{
  uint8_t cnt=0;

  udsapp_seed_flag = UDSAPP_NOSEED;

  for( cnt = 0; cnt < UDSCFG_RDBPI_MAX; cnt++ ) {
    udsapp_rdbpi_timer[cnt] = 0;
    udsapp_rdbpi_reload[cnt] = 0;
    udsapp_rdbpi_did[cnt] = 0xFF;
    udsapp_rdbpi_ta[cnt] = 0xFF;
  }
  udsapp_rdbpi_cnt = 0;
}

/*
** Read the specified data identifier into a static buf.
** Return a pointer to buf. Set data_len to length of output.
** If data is unavailable at data_id set data_len to zero.
** If data is secured set data_len to zero and return UDS_NRC_SAD.
*/
uint8_t
udsapp_rddataid( uint16_t dataid, uint8_t *data_len, uint8_t *buf )
{
  uint8_t nrc = UDS_NRC_NONE;
  uint8_t databuf[2]={0};       
  databuf[0] = 0x0Au;
  databuf[1] = 0x0Bu;
  buf = databuf;
  *data_len = 2;

  return nrc;
}

/*
** Read memory from specified address into buf.
** Return UDS_NRC_NONE if completed successfully.
** Return UDS_NRC_ROOR if invalid address.
** Return UDS_NRC_SAD  if memory requested is secured.
*/
uint8_t
udsapp_rdmem( uint32_t req_addr, uint32_t size, uint8_t *buf )
{
  uint32_t cnt;
  uint8_t *addr = (uint8_t *) req_addr;
  /* MISRA Rule 45 - Casting from int to ptr
  Exception taken: Because address is received from message,
  it must be cast from an int. We mitigate risk by using a uint8_t *
  which will be large enough for any system ptr. The user should verify
  the address is valid on the target. */
  for( cnt = 0; cnt < size; cnt++ ) { buf[cnt] = addr[cnt]; }

  return UDS_NRC_NONE;
}

/*
** Read scaling data by data identifier
** Write data into buf and set size.
** Return UDS_NRC_NONE if completed successfully
** Return UDS_NRC_ROOR if scaling data is unavailable
** Return UDS_NRC_AR if authentication is required
** Return UDS_NRC_SAD if a secure session is required
*/
uint8_t
udsapp_rdscaledataid( uint16_t data_id, uint8_t *rsp, uint16_t *size )
{
  return UDS_NRC_SNS;
}

/*
** Dynamically define new data_id from predefined data_id.
** Args: data_id -> new data_id to be defined
**        src_did -> source data_id for data to be referenced
**        pos     -> starting position in source data_id (one indexed)
**        len     -> number of bytes to be referenced in new data_id
** Return: UDS_NRC_NONE if completed successfully.
**         UDS_NRC_ROOR if data identifier is invalid.
**         UDS_NRC_SAD  if data identifier is secured.
*/
uint8_t
udsapp_defdid_id( uint16_t data_id, uint16_t src_did, uint8_t pos, uint8_t len )
{
  return UDS_NRC_SNS;
}

/*
** Dynamically define new data_id from an address.
** Args: data_id  -> new data_id to be defined
**        req_addr -> address which should be added
**        size     -> length of data to be added
** Return: UDS_NRC_NONE if completed successfully.
**         UDS_NRC_ROOR if address is invalid.
**         UDS_NRC_SAD  if address is secured.
*/
uint8_t
udsapp_defdid_addr( uint16_t data_id, uint32_t req_addr, uint32_t size )
{
  return UDS_NRC_SNS;
}

/*
** Clear a defined data_id.
** Args:  data_id -> dynamically defined data_id to be cleared
** Return: UDS_NRC_NONE if completed successfully.
**         UDS_NRC_ROOR if data_id is invalid.
**         UDS_NRC_SAD  if data_id is secured.
*/
uint8_t
udsapp_cleardid( uint16_t data_id )
{
  return UDS_NRC_SNS;
}

/*
** Write to a data identifier
** Args: data_id -> new data_id to be defined
**        data    -> data to be written
**        len     -> length of data to be added
** Return: UDS_NRC_NONE if completed successfully.
**         UDS_NRC_ROOR if data_id is invalid.
**         UDS_NRC_SAD  if data_id is secured.
*/
uint8_t
udsapp_write_did( uint16_t dataid, uint8_t *data, uint16_t len )
{
  return UDS_NRC_SNS;
}

/*
** Write to a memory address
** Args: req_addr -> target address
**        size     -> length of data to be written
**        data     -> data to be written
** Return: UDS_NRC_NONE if completed successfully.
**         UDS_NRC_ROOR if address or length are invalid.
*/
uint8_t
udsapp_write_mem( uint32_t req_addr, uint32_t size, uint8_t *data )
{
  return UDS_NRC_SNS;
}

/*
** Clear the status information associated with the given dtc
** Args: dtc -> DTC identifier to be cleared
** Output: Return UDS_NRC_NONE if completed successfully.
**         Return UDS_NRC_ROOR if dtc value is invalid.
*/
uint8_t
udsapp_cleardtc( uint32_t dtc )
{
  return UDS_NRC_SNS;
}

/*
**
*/
uint8_t
udsapp_iocontrol( uint16_t data_id, uint8_t *buf, uint16_t buf_len, uint8_t *rsp, uint16_t *rsp_len )
{
  return UDS_NRC_SNS;
}

/*
** Start a predefined routine
** Args: rout_id -> Identifier of routine
**        control_record -> optional arguments for routine
**        rec_len -> length of control record
**        rsp -> response to be sent to tester
**        rsp_len -> length of response
** Output: Set rsp and rsp_len
**         Return UDS_NRC_NONE if routine started successfully.
*/
uint8_t
udsapp_routine_start( uint16_t rout_id, uint8_t *control_record, uint16_t rec_len, uint8_t *rsp, uint16_t *rsp_len )
{
  return UDS_NRC_SNS;
}

/*
** Stop a predefined routine
** Args: rout_id -> Identifier of routine
**        control_record -> optional arguments for routine
**        rec_len -> length of control record
**        rsp -> response to be sent to tester
**        rsp_len -> length of response
** Output: Set rsp and rsp_len
**         Return UDS_NRC_NONE if routine stopped successfully.
*/
uint8_t
udsapp_routine_stop( uint16_t rout_id, uint8_t *control_record, uint16_t rec_len, uint8_t *rsp, uint16_t *rsp_len )
{
  return UDS_NRC_SNS;
}

/*
** Request status of a predefined routine
** Args: rout_id -> Identifier of routine
**        control_record -> optional arguments for routine
**        rec_len -> length of control record
**        rsp -> response to be sent to tester
**        rsp_len -> length of response
** Output: Set rsp and rsp_len
**         Return UDS_NRC_NONE if status retrieved successfully.
*/
uint8_t
udsapp_routine_status( uint16_t rout_id, uint8_t *control_record, uint16_t rec_len, uint8_t *rsp, uint16_t *rsp_len )
{
  return UDS_NRC_SNS;
}

/*
** Starts a download session
** Args: req_addr -> Starting address for transfer
**        size -> length of memory area to be transfered
**        fmt -> format byte
** Output: Return UDS_NRC_NONE if system is ready for a download.
*/
uint8_t
udsapp_reqdl( uint32_t req_addr, uint32_t size, uint8_t fmt )
{
  /* MISRA Rule 45 - Casting from int to ptr
  Exception taken: because address is received from message,
  it must be cast from an int. We mitigate risk by using a uint8_t *
  which will be large enough for any system ptr. The user should verify
  the address is valid on the target. */

  /* IF req_addr access requires additional security
    return UDS_NRC_SAD; */

  udsapp_tx_address = (uint8_t *) req_addr;
  udsapp_tx_size = size;
  udsapp_tx_dir = UDSAPP_DOWNLOAD;
  udsapp_tx_bsc = 0;
  /* if using compression/encryption the requested versions are stored in fmt
     the upper nibble is used for compression method,
     lower nibble for encryption method */
  return UDS_NRC_NONE;
}

/*
** Starts an uplaod session
** Args: req_addr -> Starting address for transfer
**        size -> length of memory area to be transfered
**        fmt -> format byte
** Output: Return UDS_NRC_NONE if system is ready for an upload.
*/
uint8_t
udsapp_requl( uint32_t req_addr, uint32_t size, uint8_t fmt )
{
  /* MISRA Rule 45 - Casting from int to ptr
  Exception taken: because address is received from message,
  it must be cast from an int. The user should verify
  the address is valid on the target. */

  /* IF req_addr access requires additional security
    return UDS_NRC_SAD; */

  udsapp_tx_address = (uint8_t *) req_addr;
  udsapp_tx_size = size;
  udsapp_tx_dir = UDSAPP_UPLOAD;
  udsapp_tx_bsc = 0;
  /* if using compression/encryption the requested versions are stored in fmt
  the upper nibble is used for compression method,
  lower nibble for encryption method */
  return UDS_NRC_NONE;
}

/*
** Continues an active transfer
** Args: bsc -> block sequence counter
**        buf -> input/output data
**        buf_len -> length of i/o data
** Output: Return UDS_NRC_NONE if packet handled correctly.
*/
uint8_t
udsapp_transfer_data( uint8_t bsc, uint8_t *buf, uint16_t *buf_len )
{
  uint16_t len = 0;
  uint16_t cnt = 0;
  uint8_t nrc = UDS_NRC_NONE;
  if( udsapp_tx_dir == UDSAPP_UPLOAD ) {
    if( bsc == udsapp_tx_bsc ) {
      /* resend previous */
      len = udsapp_tx_plen;
    } else if( bsc == ( udsapp_tx_bsc + 1 ) ) {
      /* send next */
      udsapp_tx_address = &udsapp_tx_address[udsapp_tx_plen];
      udsapp_tx_bytes += (uint32_t) udsapp_tx_plen;
      if( udsapp_tx_bytes > udsapp_tx_size ) {
        /* transfered too many bytes
        shouldn't happen, but should check */
        nrc = UDS_NRC_GPF;
      } else {
        uint32_t diff;
        diff = udsapp_tx_size - udsapp_tx_bytes;
        len = ( uint16_t )( ( diff > (uint32_t) UDSCFG_MAXBLKSIZE ) ? UDSCFG_MAXBLKSIZE : diff );
        udsapp_tx_plen = len;
        udsapp_tx_bsc = bsc;
      }
    } else {
      /* requested a bsc which is not valid */
      nrc = UDS_NRC_WBSC;
    }
    if( nrc == UDS_NRC_NONE ) {
      for( cnt = 0; cnt < len; cnt++ ) { buf[2 + cnt] = udsapp_tx_address[cnt]; }
      buf[0] = UDS_SVCID_TXDATA;
      buf[1] = bsc;
      *buf_len = len + 2;
    }
  } else if( udsapp_tx_dir == UDSAPP_DOWNLOAD ) {
    if( bsc == udsapp_tx_bsc ) {
      nrc = UDS_NRC_NONE;
      *buf_len = 0;
      /* ignore repeat and hope for best */
    } else if( bsc == ( udsapp_tx_bsc + 1 ) ) {
      /* receive next message */
      udsapp_tx_bsc = bsc;
      udsapp_tx_address = &udsapp_tx_address[udsapp_tx_plen];
      udsapp_tx_plen = *buf_len;

      for( cnt = 0; cnt < *buf_len; cnt++ ) { udsapp_tx_address[cnt] = buf[cnt]; }

    } else {
      /* sequence error */
      nrc = UDS_NRC_WBSC;
    }
  } else {
    /* not currently in a transfer */
    nrc = UDS_NRC_RSE;
  }
  return nrc;
}

/*
** Exit a transfer.
** Args: trpr -> Optional transfer paramaters
**       trpr_len -> length of transfer paramters buf
**       rsp -> response to be sent to tester
**       rsp_len -> length of response
** Output: Set rsp and rsp_len
**         Return UDS_NRC_NONE if transfer exited successfully.
*/
uint8_t
udsapp_transfer_exit( uint8_t *trpr, uint16_t trpr_len, uint8_t *rsp, uint16_t *rsp_len )
{
  udsapp_tx_dir = UDSAPP_TRANSFER_FINISHED;
  rsp[0] = UDS_SVCID_TXEXIT + UDS_PRSP;
  *rsp_len = 1;
  return UDS_NRC_NONE;
}

/*
** Control setting of DTC
** Args: subfunc -> subfunction of message
**       opt_rec -> optional control record
**       rec_len -> length of record
** Output: Return UDS_NRC_NONE if successful
**         Return UDS_NRC_ROOR if DTC not supported
*/
uint8_t
udsapp_contr_dtc( uint8_t subfunc, uint8_t *opt_rec, uint16_t rec_len )
{
  switch( subfunc ) {
    case 0x01:
      /* dtc_on */
    case 0x02:
      /* dtc_off */
    default:
      return UDS_NRC_SFNS;
  }
}

/*
** Reset baud rate to default during session change
** Return 0 on success
*/
uint8_t
udsapp_reset_timing( void )
{
  return 0;
}

/*
** Clears all response on event messages
** ROE is not currently supported.
*/
uint8_t
udsapp_clear_roe( void )
{
  return 0;
}

/*
** Reset security to locked state on session change
** Return 0 on success
*/
uint8_t
udsapp_reset_security( void )
{
  uds_secure_status = UDS_SECURE;
  udsapp_seed_flag = UDSAPP_NOSEED;
  return 0;
}

/*
** Seed/Key security mechanism
** Args: sub_func -> type of message being processed
**       rec -> seed or key received
**       rec_len -> length of received seed or key
** Output: rsp -> response to be sent to tester
**         rsp_len -> length of response
** Return: UDS_NRC_NONE on success
*/
uint8_t
udsapp_secure_access( uint8_t sub_func, uint8_t *rec, uint16_t rec_len, uint8_t *rsp, uint16_t *rsp_len )
{
  uint8_t nrc;
  switch( sub_func ) {
    case 0x01:
      /* - check current security
         - set seed out flag
         - set active pair to 01/02
         - send seed
         PORT: Change this function to be more secure than the example
         */
      if( rec_len != 0 ) {
        nrc = UDS_NRC_IMLOIF;
      } else if( uds_secure_status == UDS_SECURE ) {
        /* send a response with the seed 0x00000001*/
        rsp[0] = UDS_SVCID_SECURACC + UDS_PRSP;
        rsp[1] = 0x01; /* echo of sub function */
        rsp[2] = 0x00;
        rsp[3] = 0x00;
        rsp[4] = 0x00;
        rsp[5] = 0x01;
        *rsp_len = 6;   
        /* waiting for key 1 to pair with seed 1 */
        udsapp_seed_flag = UDS_SECURE_01;
        nrc = UDS_NRC_NONE;
      } else if( uds_secure_status == UDS_UNSECURE ) {
        /* return a seed of 0x00 because we're already unlocked */
        rsp[0] = UDS_SVCID_SECURACC + UDS_PRSP;
        rsp[1] = 0x01; /* echo of sub function */
        rsp[2] = 0x00;
        *rsp_len = 3;
        nrc = UDS_NRC_NONE;
      } else {
        nrc = UDS_NRC_GPF;
      }
      break;
    case 0x02:
      if( ( uds_secure_status == UDS_SECURE ) && ( udsapp_seed_flag == UDS_SECURE_01 ) ) {
        /* verify the key & change status */
        if( ( ( rec[0] == 0x00 ) && ( rec[1] == 0x00 ) ) && ( rec[2] == 0x00 ) ) {
          uds_secure_status = UDS_UNSECURE;
          rsp[0] = UDS_SVCID_SECURACC + UDS_PRSP;
          rsp[1] = 0x02;
          *rsp_len = 2;
          udsapp_seed_flag = UDSAPP_NOSEED;
          nrc = UDS_NRC_NONE;
        } else {
          nrc = UDS_NRC_IK;
        }
      } else {
        nrc = UDS_NRC_RSE;
      }
      break;
    default:
      nrc = UDS_NRC_SFNS;
  }
  return nrc;
}

/*
** Transition to a default session
*/
uint8_t
udsapp_session_default( void )
{
  /* reset everything except timing */
  udsapp_init();
  /* reset timing to original values */
  udsapp_reset_timing();
  uds_p2 = UDSCFG_DS_P2;
  uds_p2star = UDSCFG_DS_P2STAR;

  uds_stype = UDS_STYPE_DS;
  return UDS_NRC_NONE;
}

// Transition to a programming session
uint8_t
udsapp_session_programming( void )
{
  if( uds_stype == UDS_STYPE_DS ) {
    udsapp_clear_roe();
  } else {
    udsapp_clear_roe();
    udsapp_reset_security();
  }

  uds_p2 = UDSCFG_PRGS_P2;
  uds_p2star = UDSCFG_PRGS_P2STAR;
  /* send response */
  uds_stype = UDS_STYPE_PRGS;
  return UDS_NRC_NONE;
}

uint8_t
udsapp_session_extended( void )
{
  if( uds_stype == UDS_STYPE_DS ) {
    udsapp_clear_roe();
  } else {
    udsapp_clear_roe();
    udsapp_reset_security();
  }
  uds_p2 = UDSCFG_EXTDS_P2;
  uds_p2star = UDSCFG_EXTDS_P2STAR;
  uds_stype = UDS_STYPE_EXTDS;
  return UDS_NRC_NONE;
}

//transition to a safety session
uint8_t udsapp_session_safety( void )
{
  if( uds_stype == UDS_STYPE_DS ) {
    udsapp_clear_roe();
  } else {
    udsapp_clear_roe();
    udsapp_reset_security();
  }
  uds_p2 = UDSCFG_SSDS_P2;
  uds_p2star = UDSCFG_SSDS_P2STAR;
  uds_stype = UDS_STYPE_SSDS;
  return UDS_NRC_NONE;
}

/*
** Read a periodic data identifier
** Args: trans_mode -> Transmission mode
**        dids -> Data-identifiers to be transmitted
**        did_cnt -> Number of data identifiers
**        rsp -> Response to be transmitted to host
**        rsp_len -> Length of response
** Output: Set rsp and rsp_len
** Return: UDS_NRC_NONE on success
**         UDS_NRC_ROOR if data-id is invalid
*/
uint8_t
udsapp_rdperdataid( uint8_t trans_mode, uint8_t *dids, uint16_t did_cnt, uint8_t ta, uint8_t *rsp, uint16_t *rsp_len )
{
  uint32_t trans_time;
  uint8_t cnt, i, nrc = UDS_NRC_SNS;
  uint8_t rdbpi_placed = 0;
  uint8_t did_present_cnt = 0;

  /* PORT: User needs to verify DID valid and is 7 bytes or less
  **       Return ROOR if not
  */

  switch( trans_mode ) {
    case 1:
      trans_time = UDSCFG_RDBPI_SLOW;
      break;
    case 2:
      trans_time = UDSCFG_RDBPI_MED;
      break;
    case 3:
      trans_time = UDSCFG_RDBPI_FAST;
      break;
    case 4:
      trans_time = UDSCFG_RDBPI_STOP;
      break;
    default:
      return UDS_NRC_SFNS;
  }

  if( ( did_cnt == 0U ) && ( trans_time == UDSCFG_RDBPI_STOP ) ) {
    for( cnt = 0; ( cnt < UDSCFG_RDBPI_MAX ) && !rdbpi_placed; cnt++ ) {
      udsapp_rdbpi_did[cnt] = 0xFF;
      udsapp_rdbpi_reload[cnt] = 0;
      udsapp_rdbpi_timer[cnt] = 0;
    }
    udsapp_rdbpi_cnt = 0;
    rdbpi_placed = 1;
  }
  for( i = 0; i < did_cnt; i++ ) {
    rdbpi_placed = 0;
    did_present_cnt = 0;
    for( cnt = 0; ( cnt < UDSCFG_RDBPI_MAX ) && ( did_present_cnt < udsapp_rdbpi_cnt ) && !rdbpi_placed; cnt++ ) {
      if( udsapp_rdbpi_did[cnt] == dids[i] ) {
        /* updating existing did */
        if( trans_time == UDSCFG_RDBPI_STOP ) {
          /* stopping active did, decrease count and clear did */
          udsapp_rdbpi_did[cnt] = 0xFF;
          udsapp_rdbpi_ta[cnt] = 0xFF;
          udsapp_rdbpi_cnt--;
        }
        udsapp_rdbpi_reload[cnt] = trans_time;
        udsapp_rdbpi_timer[cnt] = trans_time;
        rdbpi_placed = 1;
      } else if( udsapp_rdbpi_did[cnt] != 0xFF ) {
        did_present_cnt++;
      }
    }
    if( trans_time == UDSCFG_RDBPI_STOP ) {
      /* DId does not exist, no need to continue looking just to stop */
      rdbpi_placed = 1;
    }
    for( cnt = 0; ( cnt < UDSCFG_RDBPI_MAX ) && !rdbpi_placed; cnt++ ) {
      if( ( udsapp_rdbpi_did[cnt] == 0xFFU ) || ( udsapp_rdbpi_reload[cnt] == 0U ) ) {
        /* placing did in new slot */
        udsapp_rdbpi_reload[cnt] = trans_time;
        udsapp_rdbpi_timer[cnt] = trans_time;
        udsapp_rdbpi_did[cnt] = dids[i];
        udsapp_rdbpi_ta[cnt] = ta;
        rdbpi_placed = 1;
        udsapp_rdbpi_cnt++;
      }
    }
  }
  if( rdbpi_placed ) {
    /* set prsp for did */
    rsp[0] = UDS_SVCID_RDPERIOID + UDS_PRSP;
    *rsp_len = 1;
    nrc = UDS_NRC_NONE;
  } else {
    /* exit due to error and send nrsp */
    nrc = UDS_NRC_ROOR;
  }

  return nrc;
}

uint8_t
udsapp_rdbpi_send_data( uint8_t did, uint8_t ta )
{
  uint8_t data_len = 0;
  //uint8_t *data=NULL; 
  uint8_t data[2]={0}; 
  //uint8_t *data;
  uint16_t dataid = 0xF200 | did;
  uint8_t nrc=0;
  uint8_t cnt=0;
  can_t frame={0};

  nrc = udsapp_rddataid( dataid, &data_len, data );

  if( ( nrc == UDS_NRC_NONE ) && ( data_len < 8 ) ) {
    frame.buf[0] = did;
    for( cnt = 0; cnt < data_len; cnt++ ) { frame.buf[cnt + 1] = data[cnt]; }

    /* PORT: use ta to translate into CAN ID, drop this frame directly to data link layer */
    frame.id = ta;
    frame.buf_len = data_len + 1;
//    can_tx( &frame );     //Sathya
    can_tx (1, &frame );
  }
  return nrc;
}

/*
** Read a DTC
** Args: sub_func -> Sub-function being requested
**        buf -> input from tester
**        buf_len -> length of buf
**        rsp -> response to be transmitted to tester
**        rsp_len -> length of response
** Output: Set rsp and rsp_len
** Return: UDS_NRC_NONE on success
**         UDS_NRC_SFNS if requested sub-function is not supported
**         UDS_NRC_ROOR if requested DTC is not valid
*/
uint8_t udsapp_readdtc( uint8_t sub_func, uint8_t *buf, uint16_t buf_len, uint8_t *rsp, uint16_t *rsp_len )
{
  uint8_t nrc = UDS_NRC_NONE;
  switch( sub_func ) {
      /*case 0x01:
        break;*/
      /*case 0x02:
        break;*/
      /*case 0x03:
        break;*/
      /*case 0x04:
        break;*/
      /*case 0x05:
        break;*/
      /*case 0x06:
        break;*/
      /*case 0x07:
        break;*/
      /*case 0x08:
        break;*/
      /*case 0x09:
        break;*/
      /*case 0x0A:
        break;*/
      /*case 0x0B:
        break;*/
      /*case 0x0C:
        break;*/
      /*case 0x0D:
        break;*/
      /*case 0x0E:
        break;*/
      /*case 0x0F:
        break;*/
      /*case 0x10:
        break;*/
      /*case 0x11:
        break;*/
      /*case 0x12:
        break;*/
      /*case 0x13:
        break;*/
      /*case 0x14:
        break;*/
      /*case 0x15:
        break;*/
    default:
      nrc = UDS_NRC_SFNS;
  }

  return nrc;
}

/*
** Switches between sessions as requested
** Args: session_type -> session being requested
** Returns: UDS_NRC_NONE on success
*/
uint8_t udsapp_session( uint8_t session_type )
{
  uint8_t nrc = UDS_NRC_NONE;
  switch( session_type ) {
    case UDS_STYPE_DS:
      /* switch on current session type*/
      nrc = udsapp_session_default();
      break;
    case UDS_STYPE_PRGS:
      nrc = udsapp_session_programming();
      break;
    case UDS_STYPE_EXTDS:
      nrc = udsapp_session_extended();
      break;
    case UDS_STYPE_SSDS:
      nrc = udsapp_session_safety();
      break;
    default:
      nrc = UDS_NRC_SFNS;
      break;
  }

  return nrc;
}

//changes to communication protocol are not currently supported
uint8_t udsapp_comm_cont( uint8_t sub_func, uint8_t type )
{
  return UDS_NRC_SNS;
}

//Any periodic updates to the user application
void udsapp_update(void)
{
  uint8_t count;

  for( count = 0; cnt < UDSCFG_READ_BY_PERIODIC_IDENTIFIER_MAX; count++ ) {
    if( udsapp_read_by_periodic_identifier_timer[count] ) {
      if( --udsapp_read_by_periodic_identifier_timer[count] == 0U ) {
        udsapp_read_by_periodic_identifier_timer[count] = udsapp_read_by_periodic_identifier_reload[count];
        /* resend requested data */
        udsapp_rdbpi_send_data( udsapp_rdbpi_did[count], udsapp_read_data_by_periodic_identifier_ta[count] );
      }
    }
  }
}
