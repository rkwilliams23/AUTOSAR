#include "uds.h"

//Function prototypes
void uds_tx (const i15765 *rec_message, const uint8_t *ibuffer, uint16_t length)
{
  i15765 message;
  uint16_t count;

  //basic stuff
  message.buffer = response_buffer;
  message.priority = 6;

  //respond to source
  message.source_address = uds_source_address;
  message.target_address = rec_message->source_address;
  message.target_address_type = received_message->target_address_type & ~0x01;
  message.address_extension = 0xFF;

  for (count = 0; count < length; count++ ) 
  { 
    response_buffer[count] = ibuffer[count]; 
   }
  message.buffer_length = length;

  /* transmit message */
  i15765_tx_app( &message, 0 );
}

//Send Negative Response Code
void uds_negative_response_code(const i15765 *message, uint8_t negative_response_code, uint8_t svcid)
{
  uint8_t response[3];
  response[0] = UDS_SVCID_NEGATIVE_RESPONSE_CODE;
  response[1] = svcid;
  response[2] = negative_response_code;
  
  uds_tx(message, response, (uint16_t) 3 );
}




//function Prototypes
void uds_tx(const i15765 *rec_message, const uint8_t *ibuffer, uint16_t length);
void uds_process(const i15765 *message);
void uds_update(void);
void uds_negative_response_code(const i15765 *message, uint8_t negative_response_code, uint8_t svcid);
void uds_init(void);
