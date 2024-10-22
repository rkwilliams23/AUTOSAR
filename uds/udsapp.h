#ifndef ISO14229_APP_H
#define ISO14229_APP_H
#include <stdint.h>

#define UDS_MAX_RESPONSE_LENGTH ((uint32_t) 255U)
#define UDS_MAX_DID_COUNT ((uint8_t) 10U)

extern void udsapp_reset (uint8_t type);

extern void udsapp_update (void);

//read data by identifier
extern uint8_t udsapp_read_data_identifier (uint16_t dataid, uint8_t *data_length, uint8_t *buffer);

//read data from memory
extern uint8_t udsapp_read_memory (uint32_t request_addr, uint32_t size, uint8_t *buffer);

//define new data_id from existing id
extern uint8_t udsapp_define_data_id (uint16_t data_id, uint16_t src_did, uint8_t pos, uint8_t length);

//Define new data_id from memory address
extern uint8_t udsapp_define_data_id_addr (uint16_t data_id, uint32_t request_addr, uint32_t size);

//Clear existing data_id
extern uint8_t udsapp_clear_did (uint16_t data_id);

//write data to data_id
extern uint8_t udsapp_write_did (uint16_t dataid, uint8_t *data, uint16_t length);

//write data to memory address
extern uint8_t udsapp_write_memory(uint32_t request_addr, uint32_t size, uint8_t *data);

//clear specified DTC
extern uint8_t udsapp_clear_dtc (uint32_t dtc);

//modify input/output from ECU
extern uint8_t udsapp_input_output_control (uint16_t data_id, uint8_t *buffer, uint16_t buffer_length, uint8_t *rsp, uint16_t *rsp_length);\

//start a predefined routine
extern uint8_t udsapp_routine_start (uint16_t rout_id, uint8_t *control_record, uint16_t rec_length, uint8_t *rsp, uint16_t *rsp_length);

//stop a predefined routine
extern uint8_t udsapp_routine_stop (uint16_t rout_id, uint8_t *control_record, uint16_t rec_length, uint8_t *rsp, uint16_t *rsp_length);

//report status of a predefined routine
extern uint8_t udsapp_routine_status (uint16_t rout_id, uint8_t *control_record, uint16_t rec_length, uint8_t *rsp, uint16_t *rsp_length);

//request a download start
extern uint8_t udsapp_request_download_start (uint32_t request_addr, uint32_t size, uint8_t format_byte);

//request an upload start
extern uint8_t udsapp_request_upload_start(uint32_t request_addr, uint32_t size, uint8_t format_byte);

//transfer data to/from the tester
extern uint8_t udsapp_transfer_data (uint8_t bsc, uint8_t *buffer, uint16_t *buffer_length);

//exit a download/upload session
extern uint8_t udsapp_transfer_exit (uint8_t *trpr, uint16_t trpr_length, uint8_t *rsp, uint16_t *rsp_length);

extern uint8_t udsapp_session_default (void);
extern uint8_t udsapp_session_programming (void);
extern uint8_t udsapp_session_extended (void);
extern uint8_t udsapp_session_safety (void);

//controls DTC setting
extern uint8_t udsapp_control_dtc (uint8_t subfunc, uint8_t* opt_rec, uint16_t rec_length);

//reset modified timing parameters
extern uint8_t udsapp_reset_timing (void);

//clear all defined response on event flows
extern uint8_t udsapp_clear_response_on_event(void);

//reset security to default state
extern uint8_t udsapp_reset_security (void);

//exchange seed/key and verify responses for secure access
extern uint8_t udsapp_secure_access (uint8_t sub_func, uint8_t *rec, uint16_t rec_length, uint8_t *response, uint16_t *response_length);

//change the active session
extern uint8_t udsapp_session (uint8_t session_type);

//read DTC
extern uint8_t udsapp_read_dtc (uint8_t sub_func, uint8_t *buffer, uint16_t buffer_length, uint8_t *response, uint16_t *response_length);

//control the communication mode
extern uint8_t udsapp_communication_mode (uint8_t sub_func, uint8_t type);

//setup a periodic read of a data identifier
extern uint8_t udsapp_read_period_data_id (uint8_t trans_mode, uint8_t *dids, uint16_t did_count, uint8_t target_address, uint8_t *response, uint16_t *response_length);

//read data by periodic identifier(rdbpi)
extern uint8_t udsapp_read_by_periodic_identifier_send_data (uint8_t did, uint8_t traget_address);

//Read scaling data by data identifier
extern uint8_t udsapp_read_scale_data_id (uint16_t data_id, uint8_t *response, uint16_t *size);
extern void udsapp_init (void);

extern uint8_t udsapp_rdbpi_count;
#endif
