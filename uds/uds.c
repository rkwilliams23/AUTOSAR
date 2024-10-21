#include "uds.h"

//Function prototypes
void uds_tx(const i15765 *rec_msg, const uint8_t *)

//Send Negative Response Code
void uds_nrsp(const i15765 *msg, uint8_t nrc, uint8_t svcid)
{
  uint8_t rsp[3];
  rsp[0] = UDS_SVCID_NRSP;
  rsp[1] = svcid;
  rsp[2] = nrc;
  
  uds_tx(msg, rsp, (uint16_t) 3 );
}




// Function Prototypes
void uds_tx(const i15765 *rec_msg, const uint8_t *ibuf, uint16_t len);
void uds_process(const i15765 *msg);
void uds_update(void);
void uds_nrsp(const i15765 *msg, uint8_t nrc, uint8_t svcid);
void uds_init(void);
