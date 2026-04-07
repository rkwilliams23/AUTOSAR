#ifndef CAN_IF_H
#define CAN_IF_H

#include "can_types.h"

int can_if_init(void);

int can_if_send(const can_frame_t *frame);

int can_if_receive(can_frame_t *frame);

#endif
