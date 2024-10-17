#include <stdio.h>
#include <stdint.h>

#define UDS_SVCID_DIAGSESS   ((uint8_t) 0x10U)
#define UDS_SVCID_ECURESET   ((uint8_t) 0x11U)
#define UDS_SVCID_SECURACC   ((uint8_t) 0x27U)
#define UDS_SVCID_COMMCONT   ((uint8_t) 0x28U)
#define UDS_SVCID_TESTER     ((uint8_t) 0x3EU)
#define UDS_SVCID_ACCTIMING  ((uint8_t) 0x83U)
#define UDS_SVCID_SECDATATX  ((uint8_t) 0x84U)
#define UDS_SVCID_CONTRDTC   ((uint8_t) 0x85U)
#define UDS_SVCID_ONEVENT    ((uint8_t) 0x86U)
#define UDS_SVCID_LINKCONT   ((uint8_t) 0x87U)
#define UDS_SVCID_RDDATAID   ((uint8_t) 0x22U)
#define UDS_SVCID_RDMEMADDR  ((uint8_t) 0x23U)
#define UDS_SVCID_RDSCDATA   ((uint8_t) 0x24U)
#define UDS_SVCID_RDPERIOID  ((uint8_t) 0x2AU)
#define UDS_SVCID_DEFDATAID  ((uint8_t) 0x2CU)
#define UDS_SVCID_WRDATAID   ((uint8_t) 0x2EU)
#define UDS_SVCID_WRMEMADDR  ((uint8_t) 0x3DU)
#define UDS_SVCID_CLEARDTC   ((uint8_t) 0x14U)
#define UDS_SVCID_READDTC    ((uint8_t) 0x19U)
#define UDS_SVCID_IOCONT     ((uint8_t) 0x2FU)
#define UDS_SVCID_ROUTCONT   ((uint8_t) 0x31U)
#define UDS_SVCID_REQDL      ((uint8_t) 0x34U)
#define UDS_SVCID_REQUL      ((uint8_t) 0x35U)
#define UDS_SVCID_TXDATA     ((uint8_t) 0x36U)
#define UDS_SVCID_TXEXIT     ((uint8_t) 0x37U)
#define UDS_SVCID_NRSP       ((uint8_t) 0x7FU)
#define UDS_SVCID_KEY        ((uint8_t) 0x33U)//DUMMY

#define UDS_RESP_SVCID_DIAGSESS   ((uint8_t) 0x50U)  //Diagnostic Session Control Response
#define UDS_RESP_SVCID_ECURESET   ((uint8_t) 0x51U)  //ECU Reset Response
#define UDS_RESP_SVCID_SECURACC   ((uint8_t) 0x67U)  //Securuty Access Response
#define UDS_RESP_SVCID_COMMCONT   ((uint8_t) 0x68U)  //Communication Control Response
#define UDS_RESP_SVCID_AUTH       ((uint8_t) 0x69U)  //Authentication Response
#define UDS_RESP_SVCID_TESTER     ((uint8_t) 0x7EU)  //Tester Present Response
#define UDS_RESP_SVCID_ACCTIMING  ((uint8_t) 0xC3U)  //Access Timing Parameters Response
#define UDS_RESP_SVCID_SECDATATX  ((uint8_t) 0xC4U)  //Secured Data Transmission Response
#define UDS_RESP_SVCID_CONTRDTC   ((uint8_t) 0xC5U)  //Control DTC Settings Response
#define UDS_RESP_SVCID_ONEVENT    ((uint8_t) 0xC6U)  //Response On Event Response
#define UDS_RESP_SVCID_LINKCONT   ((uint8_t) 0xC7U)  //Link Control Response
#define UDS_RESP_SVCID_RDDATAID   ((uint8_t) 0x62U)  //Read Data By Identifier Response
#define UDS_RESP_SVCID_RDMEMADDR  ((uint8_t) 0x63U)  //Read Memory By Address Response
#define UDS_RESP_SVCID_RDSCDATA   ((uint8_t) 0x64U)  //Read Scaling Data By Identifier Response
#define UDS_RESP_SVCID_RDPERIOID  ((uint8_t) 0x6AU)  //Read Data By Identifier Periodic Response
#define UDS_RESP_SVCID_DEFDATAID  ((uint8_t) 0x6CU)  //Dynamically Define Data Identifier Response
#define UDS_RESP_SVCID_WRDATAID   ((uint8_t) 0x6EU)  //Write Data By Identifier Response
#define UDS_RESP_SVCID_WRMEMADDR  ((uint8_t) 0x7DU)  //Write Memory By Identifier Response
#define UDS_RESP_SVCID_CLEARDTC   ((uint8_t) 0x54U)  //Clear Diagnostic Information Response
#define UDS_RESP_SVCID_READDTC    ((uint8_t) 0x59U)  //Read DTC Information Response
#define UDS_RESP_SVCID_IOCONT     ((uint8_t) 0x6FU)  //Input Output Control By Identifier Response
#define UDS_RESP_SVCID_ROUTCONT   ((uint8_t) 0x71U)  //Routine Control Response
#define UDS_RESP_SVCID_REQDL      ((uint8_t) 0x74U)  //Request Download Response
#define UDS_RESP_SVCID_REQUL      ((uint8_t) 0x75U)  //Request Upload Response
#define UDS_RESP_SVCID_TXDATA     ((uint8_t) 0x76U)  //Transfer Data Response
#define UDS_RESP_SVCID_TXEXIT     ((uint8_t) 0x77U)  //Request Transfer Exit Response
#define UDS_RESP_SVCID_TXFILE     ((uint8_t) 0x78U)  //Request File Transfer Response

#define UDS_SUBFN_PEFE        ((uint32_t) 0xF0CAU) //Partial Extraction & fULL Extraction
#define UDS_SUBFN_DDID       ((uint32_t) 0x22U)   //DID (four hex characters) received from CTP
#define UDS_SUBFN_REQDL      ((uint32_t) 0x34U)   //UDS_requestDownload
#define UDS_SUBFN_TRD        ((uint32_t) 0x36U)   //UDS_transferData
#define UDS_SUBFN_REQTREXIT  ((uint32_t) 0x37U)   //RequestTransferExit
#define UDS_SUBFN_DIAGSESS   ((uint32_t) 0x40U)   //diagnosticSessionType
#define UDS_SUBFN_SARS_BU    ((uint32_t) 0x0BU)   //securityAccessRequestSeed
#define UDS_SUBFN_SASK_0C    ((uint32_t) 0x0CU)   //securityAccessSendKey
#define UDS_SUBFN_SARS_0F    ((uint32_t) 0x0FU)    //securityAccessRequestSeed
#define UDS_SUBFN_SASK_10    ((uint32_t) 0x10U)    //securityAccessSendKey
#define UDS_SUBFN_SARS_11    ((uint32_t) 0x11U)    //securityAccessRequestSeed
#define UDS_SUBFN_SASK_12    ((uint32_t) 0x12U)    //securityAccessSendKey
#define UDS_SUBFN_DBI        ((uint32_t) 0xBAU)   //defineByIdentifier
#define UDS_SUBFN_TXM        ((uint32_t) 0xBBU)   //transmissionMode
#define UDS_SUBFN_WDI        ((uint32_t) 0xBCU)   //WriteDatabyIdentifier
#define UDS_SUBFN_RECMBMRA   ((uint32_t) 0xC17DU) //READ_ECM_Buffer_Memory_Restart_Address
#define UDS_SUBFN_RECMBMBR   ((uint32_t) 0xC17EU) //READ_ECM_Buffer_Memory_Bytes_Received
#define UDS_SUBFN_TRAC       ((uint32_t) 0xC3E2U) //Telematics Remote Adjustment Count
#define UDS_SUBFN_TRAS       ((uint32_t) 0xC3E3U) //Telematics Remote Adjustment Status
#define UDS_SUBFN_ERASeMEM   ((uint32_t) 0xFF00U) //UDS_eraseMemory
#define UDS_SUBFN_CPD        ((uint32_t) 0xFF01U) //UDS_checkProgrammingDependencies
#define UDS_SUBFN_EXEC_SBCI  ((uint32_t) 0xF084U) //EXEC_startBufferedCalibrationInstallation
#define UDS_SUBFN_EXEC_SRB   ((uint32_t) 0xF092U) //EXEC_startRollback
#define UDS_SUBFN_EXEC_IBC   ((uint32_t) 0xF0B3U) //EXEC_InvalidateBufferedCalibration
#define UDS_SUBFN_CRW        ((uint32_t) 0xF0BCU) //Cancel Remote Write
#define UDS_SUBFN_SUPLR_ID   ((uint32_t) 0x12C5U) //SUPPLIER_Id
#define UDS_SUBFN_ACESLEV_13 ((uint8_t) 0x13U)
#define UDS_SUBFN_ACESLEV_14 ((uint8_t) 0x14U)

// Function Prototypes
void uds_tx(const i15765_t *rec_msg, const uint8_t *ibuf, uint16_t len);
void uds_process(const i15765_t *msg);
void uds_update(void);
void uds_nrsp(const i15765_t *msg, uint8_t nrc, uint8_t svcid);
void uds_init(void);

#endif
