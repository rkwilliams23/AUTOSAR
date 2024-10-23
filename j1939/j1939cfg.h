#ifndef J1939CFG_H
#define J1939CFG_H

//tick period in 0.1 milliseconds (e.g. 10=1ms)
#define J1939CFG_TICK_PERIOD

//number of J1939 networks/ports
#define J1939CFG_PORTS_NUMBER

//1 to enable, 0 to disable
#define J1939CFG_DM_EN

//multi-packet TX buffer size per network
#define J1939CFG_TP_TX_BUFFER_NUMBER
#define J1939CFG_TP_TX_BUFFER_SIZE

/* multi-packet RX buffer size per network */
#define J1939CFG_TP_RX_BUFFER_NUMBER
#define J1939CFG_TP_RX_BUFFER_SIZE

#endif
