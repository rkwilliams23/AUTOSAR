#ifndef J1939_H
#define J1939_H
#include <stdint.h>
#include "j1939cfg.h"


//SAE J1939 Source Addresses
#define J1939_ADDRESS_DIAGNOSTIC_TOOL                 249 //Target the diagnostic tool
#define J1939_ADDRESS_EXPERIMENTAL_USE                252 //This can be used when testing new ECUs or during the development process.
#define J1939_ADDRESS_NULL                            254 //indicate that no address is yet claimed
#define J1939_ADDRESS_GLOBAL                          255 //send to all nodes

//SAE J1939 parameter group numbers
#define J1939_PGN_ACKNOWLEDGEMENT                   59392
#define J1939_PGN_REQUEST                           59904
#define J1939_PGN_ADDRESS_CLAIMED                   60928
#define J1939_PGN_PROPRIETARY_A                     61184
#define J1939_PGN_TRANSPORT_CONNECTIONMANAGEMENT    60416  
#define J1939_PGN_TP_DATATRANSFER                   60160  
#define J1939_PGN_TP_CM1                            60671
#define J1939_PGN_TP_DT1                            60415
#define J1939_PGN_COMMANDED_ADDRESS                 65240

#define J1939_PGN_DIAGNOSTIC_MESSAGE1               65226
#define J1939_PGN_DIAGNOSTIC_MESSAGE2               65227
#define J1939_PGN_DIAGNOSTIC_MESSAGE3               65228
#define J1939_PGN_DIAGNOSTIC_MESSAGE4               65229

typedef struct {

  uint8_t arbitrary_address_code;          /* 1-bit Arbitrary Address Capable */
  uint8_t industry_group;                 /* 3-bit Industry Group */
  uint8_t vehicle_system_instance; /* 4-bit Vehicle System Instance */
  uint8_t vehicel_system;      /* 7-bit Vehicle System */ 
  uint8_t function;         /* 8-bit Function */
  uint8_t function_instance;    /* 5-bit Function Instance */
  uint8_t ecu_instance;     /* 3-bit ECU Instance */
  uint16_t manufacturer_code;    /* 11-bit Manufacturer Code */
  uint32_t identity_number;  /* 21-bit Identity Number */

} j1939_name;


typedef struct {

  uint32_t parameter_group_number;         /* parameter group number */
  uint8_t *buffer;         /* pointer to data */
  uint16_t buffer_length;     /* size of data */
  uint8_t destination;          /* destination of message */
  uint8_t source;          /* source of message */
  uint8_t priority;          /* priority of message */
  uint8_t port;         /* CAN port of message */

} j1939_t;

extern void j1939dm_process(j1939_t *msg);

extern void j1939_init( void );

extern void j1939_update( uint8_t cnt );

extern uint8_t j1939_tx_request ( uint8_t p, uint32_t req_pgn, uint8_t dst );

extern uint8_t j1939_tx_acknowledgement (uint8_t p, uint32_t req_pgn, uint8_t src); 

extern uint8_t j1939_tx_ackp ( uint8_t p, uint32_t req_pgn, uint8_t src ); //transmit a positive ACK

extern uint8_t j1939_bip_tx_rate_max_get ( uint8_t p ); //retrieves peak bus load usage.

extern void j1939_name_set( uint8_t p, j1939_name_t *n );

extern uint8_t j1939_tx_app( j1939_t *msg, uint8_t *status );

extern void j1939_bip_tx_rate_allowed_set ( uint8_t p, uint8_t rate ); //sets max allowed transmit rate

extern uint32_t msgID;
extern uint8_t j1939_sa[ J1939CFG_PORTS_NUM ];
#endif
