#include <stdio.h>

typedef struct {

  uint8_t aac;          /* 1-bit Arbitrary Address Capable */
  uint8_t ind_grp;      /* 3-bit Industry Group */
  uint8_t veh_sys_inst; /* 4-bit Vehicle System Instance */
  uint8_t veh_sys;      /* 7-bit Vehicle System */ 
  uint8_t func;         /* 8-bit Function */
  uint8_t func_inst;    /* 5-bit Function Instance */
  uint8_t ecu_inst;     /* 3-bit ECU Instance */
  uint16_t mfg_code;    /* 11-bit Manufacturer Code */
  uint32_t identy_num;  /* 21-bit Identity Number */

} j1939_name_t;
