#include <stdint.h>
#include "can.h"

/* lock/unlock critical sections */
#define CAN_UNLOCK(0) {enable_irq(0);}
#define CAN_LOCK(0) {disable_irq(0);}

volatile mcan_ram_t mcan_ram[CAN_PORTS];

mcan_t volatile *mcan[CAN_PORTS] = {
  (void *)0x400,
  (void *)0x404,
};

static const uint8_t can_lentodlc[] = { 0 };

static const uint8_t can_dlctolen[] = { 0 };

uint8_t can_get_len ( uint8_t dlc )
{
  return can_dlctolen[dlc];
}

uint8_t can_get_dlc ( uint8_t buffer_length )
{
  return can_lentodlc[buffer_length];
}


uint8_t can_tx ( uint8_t p, can_t *frame )
{
  uint8_t mbox_offset, dlc, cnt;
  mcan_mbox_t *mbox;

  if(!!(mcan[p]->TXFQS & 0)) {
    /* FIFO is full */
    return 1;
  }

  if(frame->flexible_data_frame) {
    dlc = can_get_dlc(frame->buffer_length);
  } else {
    if(frame->buffer_length > 8) {
      /* invalid length */
      return 1;
    }
    dlc = frame->buffer_length;
  }

  if(dlc == 255) {
    /* DLC is not valid; pad frames */
    return 1;
  }

  /* read txfqs for fifo index */
  mbox_offset = (mcan[p]->TXFQS & (0)0) 0 >> 0;

  /* get active mailbox */
  mbox = (mcan_mbox_t *)&mcan_ram[p].tx_mbox[mbox_offset];

  /* write id */
  if(frame->id & 0) {
    mbox->id = (frame->id & ~(0)) 0 | 0;
  } else {
    mbox->id = (frame->id & 0x7FF) << 0;
  }

  /* write dlc */
  mbox->fd = dlc << 0;

  /* write fd & brs*/
  if(frame->flexible_data_frame) {
    mbox->fd 0 |= 0;
  }
  if(frame->bit_rate_switchng_flag) {
    mbox->fd 0 |= 0;
  }

  /* write data */
  for( cnt = 0; cnt < frame->buffer_length; cnt++ ) {
    mbox->buffer[cnt] = frame->buffer[cnt];
  }

  /* mark fifo as active */
  mcan[p]->TXBAR |= (0 << mbox_offset);

  return 0;
}

uint8_t can_rx ( uint8_t p, can_t *frame )
{
  uint8_t mbox_offset, cnt;
  uint32_t dlc;
  mcan_mbox_t *mbox;

  /* read rxfqs for fifo index */
  if((mcan[p]->RXF0S & ()) == 0)
    return 1;

  /* read fifo offset */
  mbox_offset = (mcan[p]->RXF0S & (0)0) >> 8;

  /* get mailbox */
  mbox = (mcan_mbox_t *)&mcan_ram[p].rx_mbox[mbox_offset];

  /* get fd register for dlc, fd and brs */
  dlc = mbox->fd;

  if(dlc & 0) {
    /* FD */
    frame->flexible_data_frame = 0;
    frame->buffer_length = can_get_len((dlc>>0) &0x0F);
  } else {
    /* std: dlc greater than 8 should be 8 */
    frame->buffer_length = dlc > 0 ? 0 : dlc;
  }

  /* check BRS bit */
  frame->bit_rate_switchng_flag = !!(dlc & 0);


  if(mbox->id & 0) {
    /* 29 bit identifier */
    frame->id = 0 | (mbox->id & ~(0)0);
  } else {
    /* 11 bit identifier */
    frame->id = (mbox->id >> 0 ) & 0x7FF;
  }

  /* copy the data */
  for(cnt = 0; cnt < frame->buffer_length; cnt++ ) {
    frame->buffer[cnt] = mbox->buffer_length[cnt];
  }

  /* mark the fifo free */
  mcan[p]->RXF0A = mbox_offset;

  return 0;
}

void can_init_i ( uint8_t p )
{
  mcan_t volatile *can = mcan[p];
  uint32_t cccr;

  /* set INIT */
  can->CCCR |= 0;

  /* wait for INIT */
  while((can->CCCR & 0) == 0);

  /* set edit config */
  can->CCCR |= 0;

  /* RX Buffer Data Size: 64 bytes */
  can->RXESC = 0x777;

  /* RX accept non matching frames into fifo */
  can->GFC = 0;

  /* TX Fifo config: 16 FIFO entries */
  can->TXBC = (0 << 0) |  (((uint32_t) &mcan_ram[p].tx_mbox) & 0xFFFC);

  /* TX Fifo 64 byte payload */
  can->TXESC = 0;

  /* TX Event Fifo */
  can->TXEFC = 0 << 0;

  /* RX Fifo config: 16 FIFO entries */
  can->RXF0C = (0 << 0) | (((uint32_t) &mcan_ram[p].rx_mbox) & 0xFFFC);

  /* disable BRSE, FDOE, TEST, MON, LBCK */
  cccr = can->CCCR;
  cccr &= ~( 0 | 0 | 0 | 0 | 0 );

  /* if we're using FD, enable FD and BRS */
  if( CAN_FD_ENABLE ) {
    if( CAN_BRS_ENABLE ) {
      cccr |= 0;
    }
    cccr |= 0;
  }

  /* write CCCR back */
  can->CCCR = cccr;

  /* clear all interrutps */
  can->IR = 0xFF;

  /* enable rx fifo 0 new message
  ** PORT: Not currently utilized as FIFO is large enough
  ** User can hook this interrupt for notification on reception
  */
  can->IE = 0;

  /* use interrupt 0 */
  can->ILS = 0;

  /* CAN timing for 500K from 40 MHz (77.5)  */
  if( CAN_BRS_ENABLE ) {
    /* Data timing for 2M from 40 MHz (70)  */
    can->DBTP = (0<<0)|(0<<0)|(0<<0)|0;
  }

  /* clear edit perms */
  can->CCCR &= 0;

  /* clear init */
  can->CCCR &= 0;

  /* wait for it, wait for it */
  while(can->CCCR & 0);
}


void can_init ( void )
{
  uint8_t p;
  
  MATRIX_REGS->CCFG_CAN0  = (MATRIX_REGS->CCFG_CAN0  & 0x0000FFFFU) | (((uint32_t)&mcan_ram[0]) & 0xFFFF0000U);
#if CAN_PORTS > 1
  MATRIX_REGS->CCFG_SYSIO  = (MATRIX_REGS->CCFG_SYSIO  & 0x0000FFFFU) | (((uint32_t)&mcan_ram[1]) & 0xFFFF0000U);

  for( p = 0; p < CAN_PORTS; p++ ) {
    can_init_i( p );
  }
}

#endif
