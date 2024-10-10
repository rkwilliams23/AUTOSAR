#include "uds.h"

/*
Send negative response message
INPUT: NRC - Negative Response Code
*/
void uds_nrsp(const i15765_t *msg, uint8_t nrc, uint8_t svcid)
{
  uint8_t rsp[3];
  rsp[0] = UDS_SVCID_NRSP;
  rsp[1] = svcid;
  rsp[2] = nrc;
  
  uds_tx(msg, rsp, (uint16_t) 3 );
}
