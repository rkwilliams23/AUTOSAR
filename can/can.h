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

extern void can_init( void ); //initializes CAN hardware (Function Prototype - Function Description)
extern uint8_t can_tx( uint8_t p, can_t *frame ); //receives CAN frame (buffered I/O) (Function Prototype - Function Description)
extern uint8_t can_rx( uint8_t p, can_t *frame ); //transmits CAN frame (buffered I/O) (Function Prototype - Function Description)
