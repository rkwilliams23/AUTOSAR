#include <stdio.h>

#define CAN_PORT 1 //enter the can Port

typedef struct
{
  uint32_t id;
  uint8_t  fdf;
  uint8_t  brs;
  uint8_t  buf_len;
  uint8_t  buf[8];
} can_t; /*can_t is a data type used to store CAN frames.
It contains the CAN frame identifier, the CAN frame data, and the size of data.
NOTE: If the most significant bit of id (i.e. bit 31) is set,
it indicates an extended CAN frame,
else it indicates a standard CAN frame.*/

extern void can_init( void ); //initializes CAN hardware (Function Prototype - Function Description)
extern uint8_t can_tx( uint8_t p, can_t *frame ); //receives CAN frame (buffered I/O) (Function Prototype - Function Description)
extern uint8_t can_rx( uint8_t p, can_t *frame ); //transmits CAN frame (buffered I/O) (Function Prototype - Function Description)
