// UDS Frame Types
#define UDS_FRAME_TYPE_SF 0x01; //Single Frame (SF): Used for messages that fit within a single frame (up to 255 bytes).
#define UDS_FRAME_TYPE_FF 0x02; //First Frame (FF): Used for messages that are larger than 255 bytes. It indicates the beginning of a multi-frame message.
#define UDS_FRAME_TYPE_CF 0x03; //Consecutive Frame (CF): Used to continue a multi-frame message after the first frame.

// Diagnostic and communication management
#define UDS_DSC_REQUEST_SERVICE_ID 0x10 //DIAGNOSTIC SESSION CONTROL
#define UDS_ECU_RESET_REQUEST_ID 0x11 //ECU RESET
#define UDS_SA_REQUEST_ID 0x27 //Security Access
#define UDS_CCC_REQUEST_SERVICE_ID 0x28 //Communication Control
#define UDS_AUTHENTICATION 0x29
#define UDS_TESTER_PRESENT 0x3E
#define UDS_ACCESS_TIMING_PARAMETERS 0x83
#define UDS_SECURED_DATA_TRANSMISSION 0x84
#define UDS_CONTROL_DTC_SETTINGS 0x85
#define UDS_RESPONSE_ON_EVENT 0x86
#define UDS_LINK_CONTROL 0x87

// Data Transmission
#define READ_DATA_BY_IDENTIFIER 0x22
#define READ_MEMORY_BY_ADDRESS 0x23
#define READ_SCALING_DATA_BY_IDENTIFIER 0x24
#define READ_DATA_BY_IDENTIFIER_PERIODIC 0x2A
#define DYNAMICALLY_DEFINE_DATA_IDENTIFIER 0x2C
#define WRITE_DATA_BY_IDENTIFIER 0x2E
#define WRITE_MEMORY_BY_IDENTIFIER 0x3D

// DTC
#define CLEAR_DIAGONSTIC_INFORMATION 0x14
#define READ_DTC_INFORMATION 0x19

#define INPUT_OUTPUT_CONTROL_BY_IDENTIFIER 0x2F

#define ROUTINE_CONTROL 0x31

// Upload/Download
#define REQUEST_DOWNLOAD 0x34
#define REQUEST_UPLOAD 0x35
#define TRANSFER_DATA 0x36
#define REQUEST_TRANSFER_EXIT 0x37
#define REQUEST_FILE_TRANSFER 0x38

#define NR 0x7F //NEGATIVE RESPONSE MODE

#define UDS_DSC_RESPONSE_SERVICE_ID 0x50;
#define ECU_RESET_RESPONSE_ID 0x51;

// Diagnostic Session Control
#define UDS_DSC_PCI 0x01; //Protocol Control Information
#define UDS_DSC_TYPE_DEFAULT_SESSION 0x01;
#define UDS_DSC_TYPE_EXTENDED_SESSION 0x02;
#define UDS_DSC_TYPE_PROGRAMMING_SESSION 0x03;
