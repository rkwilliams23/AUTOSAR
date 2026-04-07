#ifndef J1939_TYPES_H
#define J1939_TYPES_H

#include <stdint.h>

typedef struct
{
    uint32_t pgn;
    uint8_t priority;
    uint8_t source_address;
    uint8_t data[8];
} j1939_msg_t;

#endif
