#ifndef ISO14229_H
#define ISO14229_H

#include <stdio.h>
#include <stdint.h>

const uint8_t UDS_SVCID_DIAGSESS   = 0x10U
const uint8_t UDS_SVCID_ECURESET   = 0x11U
const uint8_t UDS_SVCID_SECURACC   = 0x27U
const uint8_t UDS_SVCID_COMMCONT   = 0x28U
const uint8_t UDS_SVCID_TESTER     = 0x3EU
const uint8_t UDS_SVCID_ACCTIMING  = 0x83U
const uint8_t UDS_SVCID_SECDATATX  = 0x84U
const uint8_t UDS_SVCID_CONTRDTC   = 0x85U
const uint8_t UDS_SVCID_ONEVENT    = 0x86U
const uint8_t UDS_SVCID_LINKCONT   = 0x87U
const uint8_t UDS_SVCID_RDDATAID   = 0x22U
const uint8_t UDS_SVCID_RDMEMADDR  = 0x23U
const uint8_t UDS_SVCID_RDSCDATA   = 0x24U
const uint8_t UDS_SVCID_RDPERIOID  = 0x2AU
const uint8_t UDS_SVCID_DEFDATAID  = 0x2CU
const uint8_t UDS_SVCID_WRDATAID   = 0x2EU
const uint8_t UDS_SVCID_WRMEMADDR  = 0x3DU
const uint8_t UDS_SVCID_CLEARDTC   = 0x14U
const uint8_t UDS_SVCID_READDTC    = 0x19U
const uint8_t UDS_SVCID_IOCONT     = 0x2FU
const uint8_t UDS_SVCID_ROUTCONT   = 0x31U
const uint8_t UDS_SVCID_REQDL      = 0x34U
const uint8_t UDS_SVCID_REQUL      = 0x35U
const uint8_t UDS_SVCID_TXDATA     = 0x36U
const uint8_t UDS_SVCID_TXEXIT     = 0x37U
const uint8_t UDS_SVCID_NRSP       = 0x7FU
const uint8_t UDS_SVCID_KEY        = 0x33U//DUMMY

const uint8_t UDS_RESP_SVCID_DIAGSESS   = 0x50U  //Diagnostic Session Control Response
const uint8_t UDS_RESP_SVCID_ECURESET   = 0x51U  //ECU Reset Response
const uint8_t UDS_RESP_SVCID_SECURACC   = 0x67U  //Securuty Access Response
const uint8_t UDS_RESP_SVCID_COMMCONT   = 0x68U  //Communication Control Response
const uint8_t UDS_RESP_SVCID_AUTH       = 0x69U  //Authentication Response
const uint8_t UDS_RESP_SVCID_TESTER     = 0x7EU  //Tester Present Response
const uint8_t UDS_RESP_SVCID_ACCTIMING  = 0xC3U  //Access Timing Parameters Response
const uint8_t UDS_RESP_SVCID_SECDATATX  = 0xC4U  //Secured Data Transmission Response
const uint8_t UDS_RESP_SVCID_CONTRDTC   = 0xC5U  //Control DTC Settings Response
const uint8_t UDS_RESP_SVCID_ONEVENT    = 0xC6U  //Response On Event Response
const uint8_t UDS_RESP_SVCID_LINKCONT   = 0xC7U  //Link Control Response
const uint8_t UDS_RESP_SVCID_RDDATAID   = 0x62U  //Read Data By Identifier Response
const uint8_t UDS_RESP_SVCID_RDMEMADDR  = 0x63U  //Read Memory By Address Response
const uint8_t UDS_RESP_SVCID_RDSCDATA   = 0x64U  //Read Scaling Data By Identifier Response
const uint8_t UDS_RESP_SVCID_RDPERIOID  = 0x6AU  //Read Data By Identifier Periodic Response
const uint8_t UDS_RESP_SVCID_DEFDATAID  = 0x6CU  //Dynamically Define Data Identifier Response
const uint8_t UDS_RESP_SVCID_WRDATAID   = 0x6EU  //Write Data By Identifier Response
const uint8_t UDS_RESP_SVCID_WRMEMADDR  = 0x7DU  //Write Memory By Identifier Response
const uint8_t UDS_RESP_SVCID_CLEARDTC   = 0x54U  //Clear Diagnostic Information Response
const uint8_t UDS_RESP_SVCID_READDTC    = 0x59U  //Read DTC Information Response
const uint8_t UDS_RESP_SVCID_IOCONT     = 0x6FU  //Input Output Control By Identifier Response
const uint8_t UDS_RESP_SVCID_ROUTCONT   = 0x71U  //Routine Control Response
const uint8_t UDS_RESP_SVCID_REQDL      = 0x74U  //Request Download Response
const uint8_t UDS_RESP_SVCID_REQUL      = 0x75U  //Request Upload Response
const uint8_t UDS_RESP_SVCID_TXDATA     = 0x76U  //Transfer Data Response
const uint8_t UDS_RESP_SVCID_TXEXIT     = 0x77U  //Request Transfer Exit Response
const uint8_t UDS_RESP_SVCID_TXFILE     = 0x78U  //Request File Transfer Response

const uint32_t UDS_SUBFN_PEFE           = 0xF0CAU //Partial Extraction & fULL Extraction
const uint32_t UDS_SUBFN_DDID           = 0x22U   //DID (four hex characters received from CTP
const uint32_t UDS_SUBFN_REQDL          = 0x34U   //UDS_requestDownload
const uint32_t UDS_SUBFN_TRD            = 0x36U   //UDS_transferData
const uint32_t UDS_SUBFN_REQTREXIT      = 0x37U   //RequestTransferExit
const uint32_t UDS_SUBFN_DIAGSESS       = 0x40U   //diagnosticSessionType
const uint32_t UDS_SUBFN_SARS_BU        = 0x0BU   //securityAccessRequestSeed
const uint32_t UDS_SUBFN_SASK_0C        = 0x0CU   //securityAccessSendKey
const uint32_t UDS_SUBFN_SARS_0F        = 0x0FU   //securityAccessRequestSeed
const uint32_t UDS_SUBFN_SASK_10        = 0x10U   //securityAccessSendKey
const uint32_t UDS_SUBFN_SARS_11        = 0x11U   //securityAccessRequestSeed
const uint32_t UDS_SUBFN_SASK_12        = 0x12U   //securityAccessSendKey
const uint32_t UDS_SUBFN_DBI            = 0xBAU   //defineByIdentifier
const uint32_t UDS_SUBFN_TXM            = 0xBBU   //transmissionMode
const uint32_t UDS_SUBFN_WDI            = 0xBCU   //WriteDatabyIdentifier
const uint32_t UDS_SUBFN_RECMBMRA       = 0xC17DU //READ_ECM_Buffer_Memory_Restart_Address
const uint32_t UDS_SUBFN_RECMBMBR       = 0xC17EU //READ_ECM_Buffer_Memory_Bytes_Received
const uint32_t UDS_SUBFN_TRAC           = 0xC3E2U //Telematics Remote Adjustment Count
const uint32_t UDS_SUBFN_TRAS           = 0xC3E3U //Telematics Remote Adjustment Status
const uint32_t UDS_SUBFN_ERASeMEM       = 0xFF00U //UDS_eraseMemory
const uint32_t UDS_SUBFN_CPD            = 0xFF01U //UDS_checkProgrammingDependencies
const uint32_t UDS_SUBFN_EXEC_SBCI      = 0xF084U //EXEC_startBufferedCalibrationInstallation
const uint32_t UDS_SUBFN_EXEC_SRB       = 0xF092U //EXEC_startRollback
const uint32_t UDS_SUBFN_EXEC_IBC       = 0xF0B3U //EXEC_InvalidateBufferedCalibration
const uint32_t UDS_SUBFN_CRW            = 0xF0BCU //Cancel Remote Write
const uint32_t UDS_SUBFN_SUPLR_ID       = 0x12C5U //SUPPLIER_Id
const uint8_t UDS_SUBFN_ACESLEV_13      = 0x13U
const uint8_t UDS_SUBFN_ACESLEV_14      = 0x14U

// Function Prototypes
void uds_tx(const i15765_t *rec_msg, const uint8_t *ibuf, uint16_t len);
void uds_process(const i15765_t *msg);
void uds_update(void);
void uds_nrsp(const i15765_t *msg, uint8_t nrc, uint8_t svcid);
void uds_init(void);

#endif
