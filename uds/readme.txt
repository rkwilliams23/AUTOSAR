uds.h
Core header file. Modification discouraged.

uds.c
Core source file. Modification discouraged.

udsapp.h
Application header file. Modification required.

udsapp.c
Application source file. Modification required.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

void uds_init ( void )
Initializes protocol stack

void udsapp_init ( void )
Called on startup

void uds_update ( void )
Provides periodic time base

void udsapp_update ( void )
Called at periodic tick rate

void udsapp_process ( i15765_t *msg )
Processes received messages.

uint8_t udsapp_rddataid ( uint16_t data_id, uint8_t *data_len, uint8_t *buf )
Read data by identifier

uint8_t udsapp_rdmem ( uint32_t addr, uint32_t size, uint8_t *buf )
Read data from memory

uint8_t udsapp_defdid_id ( uint16_t data_id, uint16_t src_id, uint8_t pos, uint8_t len )
Define new data_id from existing id

uint8_t udsapp_defdid_addr ( uint16_t data_id, uint32_t addr, uint32_t size )
Define new data_id from memory address

uint8_t udsapp_cleardid ( uint16_t data_id )
Clear existing data_id

uint8_t udsapp_write_did ( uint16_t data_id, uint8_t *data, uint16_t len )
Write data to data_id

uint8_t udsapp_write_mem ( uint32_t addr, uint32_t size, uint8_t *data )
Write data to memory address

uint8_t udsapp_cleardtc ( uint32_t dtc )
Clear specified DTC

uint8_t udsapp_iocontrol ( uint16_t data_id, uint8_t *buf, uint16_t buf_len, uint8_t *rsp, uint16_t *rsp_len )
Modify input/output from ECU

uint8_t udsapp_routine_start ( uint16_t rout_id, uint8_t *control_record, uint16_t rec_len, uint8_t *rsp, uint16_t *rsp_len )
Start a predefined routine

uint8_t udsapp_routine_status(uint16_t rout_id, uint8_t *control_record, uint16_t rec_len, uint8_t *rsp, uint16_t *rsp_len)
Report status of a predefined routine

uint8_t udsapp_reqdl(uint32_t addr, uint32_t size, uint8_t fmt)
Request a download start

uint8_t udsapp_requl(uint32_t addr, uint32_t size, uint8_t fmt)
Request an upload start

uint8_t udsapp_transfer_data(uint8_t bsc, uint8_t *buf, uint16_t *buf_len)
Transfer data to/from the tester

uint8_t udsapp_transfer_exit(uint8_t *trpr, uint16_t trpr_len, uint8_t *rsp, uint16_t *rsp_len)
Exit a download/upload session

uint8_t udsapp_contr_dtc ( uint8_t subfunc, uint8_t* opt_rec, uint8_t buf_len )
Controls DTC setting

uint8_t udsapp_reset_timing ( void )
Reset modified timing parameters

uint8_t udsapp_clear_roe ( void )
Clear all defined response on event flows

uint8_t udsapp_reset_security ( void )
Reset security to default state

uint8_t udsapp_secure_access ( uint8_t sub_func, uint8_t *rec, uint16_t rec_len, uint8_t *rsp, uint16_t *rsp_len )
Exchange seed/key and verify responses for secure access

uint8_t udsapp_session ( uint8_t session_type )
Change the active session

uint8_t udsapp_readdtc ( uint8_t sub_func, uint8_t *buf, uint16_t buf_len, uint8_t *rsp, uint16_t *rsp_len )
Read a DTC

uint8_t udsapp_comm_cont ( uint8_t sub_func, uint8_t type)
Control the communication mode

uint8_t udsapp_rdper_dataid ( uint8_t trans_mode, uint8_t *dids, uint8_t did_cnt, uint8_t *rsp, uint16_t *rsp_len)
Setup a periodic read of a data identifier
