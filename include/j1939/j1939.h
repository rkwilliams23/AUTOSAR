#ifndef J1939_H
#define J1939_H

#include "j1939_types.h"

void j1939_init(void);

void j1939_process(const j1939_msg_t *msg);

#endif
