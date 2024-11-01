#include <stdint.h>

#define CAN_PORT 1 //enter the can Port

#define CAN_MAX_DATA_LENGTH 8 //CAN data length for standard CAN

typedef struct
{
  uint32_t id; //CAN ID (11-bit for standard, 29-bit for extended if MSB is set)
  uint8_t  flexible_data_frame; //Flexible Data Rate Frame (0 = standard, 1 = CAN FD)
  uint8_t  bit_rate_switchng_flag; //Bit Rate Switching flag (0 = normal rate, 1 = faster rate for data section in CAN FD)
  uint8_t  buffer_length; //Data length (0-8 for standard CAN, up to 64 for CAN FD)
  uint8_t  buffer[CAN_FD_MAX_DATA_LENGTH]; // Data payload (up to 8 bytes for standard CAN, up to 64 for CAN FD)
} can_t;

/*can_t is a data type used to store CAN frames. It contains the CAN frame identifier, the CAN frame data, and the size of data.
NOTE: If the most significant bit of id (i.e. bit 31) is set, it indicates an extended CAN frame, else it indicates a standard CAN frame.*/

typedef struct {
  uint32_t CREL;      /* Core Release */
  uint32_t ENDN;      /* Endian */
  uint32_t rsv0;      /* Reserved in TI M_CAN */
  uint32_t DBTP;      /* Fast Bit Timing and Prescaler */
  uint32_t TEST;      /* Test */
  uint32_t RWD;       /* RAM Watchdog */
  uint32_t CCCR;      /* CC Control */
  uint32_t NBTP;      /* Nominal Bit Timing and Prescaler */
  uint32_t TSCC;      /* Timestamp Counter Configuration */
  uint32_t TSCV;      /* Timestamp Counter Value */
  uint32_t TOCC;      /* Timeout Counter Configuration */
  uint32_t TOCV;      /* Timeout Counter Value */
  uint8_t  res1[0x10];
  uint32_t ECR;       /* Error Counter */
  uint32_t PSR;       /* Protocol Status */
  uint32_t TDCR;      /* Extended ID Filter Configuration */
  uint8_t  res2[0x4];
  uint32_t IR;        /* Interrupt */
  uint32_t IE;        /* Interrupt Enable */
  uint32_t ILS;       /* Interrupt Line Select */
  uint32_t ILE;       /* Interrupt Line Enable */
  uint8_t  res3[0x20];
  uint32_t GFC;       /* Global Filter Configuration */
  uint32_t SIDFC;     /* Standard ID Filter Configuration */
  uint32_t XIDFC;     /* Extended ID Filter Configuration */
  uint8_t  res4[0x4];
  uint32_t XIDAM;     /* Extended ID AND Mask */
  uint32_t HPMS;      /* High Priority Message Status */
  uint32_t NDAT1;     /* New Data 1 */
  uint32_t NDAT2;     /* New Data 2 */
  uint32_t RXF0C;     /* Rx FIFO 0 Configuration */
  uint32_t RXF0S;     /* Rx FIFO 0 Status */
  uint32_t RXF0A;     /* Rx FIFO 0 Acknowledge */
  uint32_t RXBC;      /* Rx Buffer Configuration */
  uint32_t RXF1C;     /* Rx FIFO 1 Configuration */
  uint32_t RXF1S;     /* Rx FIFO 1 Status */
  uint32_t RXF1A;     /* Rx FIFO 1 Acknowledge */
  uint32_t RXESC;     /* Rx Buffer / FIFO Element Size Configuration */
  uint32_t TXBC;      /* Tx Buffer Configuration */
  uint32_t TXFQS;     /* Tx FIFO / Queue Status */
  uint32_t TXESC;     /* Tx Buffer Element Size Configuration */
  uint32_t TXBRP;     /* Tx Buffer Request Pending */
  uint32_t TXBAR;     /* Tx Buffer Add Request */
  uint32_t TXBCR;     /* Tx Buffer Cancellation Request */
  uint32_t TXBTO;     /* Tx Buffer Transmission Occurred */
  uint32_t TXBCF;     /* Tx Buffer Cancellation Finished */
  uint32_t TXBTIE;    /* Tx Buffer Transmission Interrupt Enable */
  uint32_t TXBCIE;    /* Tx Buffer Cancellation Finished Interrupt Enable */
  uint8_t  res5[0x8];
  uint32_t TXEFC;     /* Tx Event FIFO Configuration */
  uint32_t TXEFS;     /* Tx Event FIFO Status */
  uint32_t TXEFA;     /* Tx Event FIFO Acknowledge */
} mcan_t;

struct mcan_mbox_struct {
  uint32_t id;
  uint32_t fd;
  uint8_t buf[8];
} __attribute__((packed));

extern void can_init( void ); //initializes CAN hardware (Function Prototype - Function Description)
extern uint8_t can_tx( uint8_t p, can_t *frame ); //receives CAN frame (buffered I/O) (Function Prototype - Function Description)
extern uint8_t can_rx( uint8_t p, can_t *frame ); //transmits CAN frame (buffered I/O) (Function Prototype - Function Description)

typedef struct mcan_mbox_struct mcan_mbox_t;

extern volatile uint16_t writePointer[2];
extern volatile uint16_t readPointer[2];
extern volatile uint16_t dataPointer[2];

extern volatile uint16_t MCAN1_writePointer[2];
extern volatile uint16_t MCAN1_readPointer[2];
extern volatile uint16_t MCAN1_dataPointer[2];
