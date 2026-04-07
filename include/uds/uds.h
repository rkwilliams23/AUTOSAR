#ifndef UDS_H
#define UDS_H

#include "uds_types.h"

void uds_init(void);

/* Process incoming UDS request */
uds_status_t uds_process_request(
    const uint8_t *req,
    uint16_t req_len,
    uint8_t *resp,
    uint16_t *resp_len
);

#endif
