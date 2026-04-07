#ifndef CAN_TYPES_H
#define CAN_TYPES_H

#include <stdint.h>

typedef uint32_t can_id_t;

typedef struct
{
    can_id_t id;
    uint8_t dlc;
    uint8_t data[8];
} can_frame_t;

#endif
