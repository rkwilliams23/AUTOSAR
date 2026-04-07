#ifndef UDS_TYPES_H
#define UDS_TYPES_H

#include <stdint.h>

typedef uint8_t uds_sid_t;

typedef enum
{
    UDS_OK = 0,
    UDS_ERROR,
    UDS_PENDING
} uds_status_t;

typedef struct
{
    uint16_t did;
    uint8_t (*read)(uint8_t *data);
} uds_did_entry_t;

#endif
