/******************************************************************************
 *
 *  Copyright 2003-2012 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

/******************************************************************************
 *
 *  This is the private interface file for the BTA system manager.
 *
 ******************************************************************************/
#ifndef BTA_SYS_INT_H
#define BTA_SYS_INT_H

/*****************************************************************************
 *  Constants and data types
 ****************************************************************************/

/*****************************************************************************
 *  state table
 ****************************************************************************/

/* SYS HW state */
enum {
  BTA_SYS_HW_OFF,
  BTA_SYS_HW_STARTING,
  BTA_SYS_HW_ON,
  BTA_SYS_HW_STOPPING
};
typedef uint8_t tBTA_SYS_HW_STATE;

/* Collision callback */
#define MAX_COLLISION_REG 5

typedef struct {
  uint8_t id[MAX_COLLISION_REG];
  tBTA_SYS_CONN_CBACK* p_coll_cback[MAX_COLLISION_REG];
} tBTA_SYS_COLLISION;

/* system manager control block */
typedef struct {
  tBTA_SYS_REG* reg[BTA_ID_MAX]; /* registration structures */
  bool is_reg[BTA_ID_MAX];       /* registration structures */
  tBTA_SYS_HW_STATE state;
  tBTA_SYS_HW_CBACK* sys_hw_cback;
  bool bluetooth_active;
  uint16_t sys_features;         /* Bitmask of sys features */

  tBTA_SYS_CONN_CBACK* prm_cb; /* role management callback registered by DM */
  tBTA_SYS_CONN_CBACK*
      ppm_cb; /* low power management callback registered by DM */
  tBTA_SYS_CONN_CBACK*
      p_policy_cb; /* link policy change callback registered by DM */
  tBTA_SYS_CONN_CBACK*
      p_sco_cb; /* SCO connection change callback registered by AV */
  tBTA_SYS_CONN_CBACK* p_role_cb; /* role change callback registered by AV */
  tBTA_SYS_COLLISION colli_reg;   /* collision handling module */
#if (BTA_EIR_CANNED_UUID_LIST != TRUE)
  tBTA_SYS_EIR_CBACK* eir_cb; /* add/remove UUID into EIR */
#endif
#if (BTM_SSR_INCLUDED == TRUE)
  tBTA_SYS_SSR_CFG_CBACK* p_ssr_cb;
#endif
  /* VS event handler */
  tBTA_SYS_VS_EVT_HDLR* p_vs_evt_hdlr;

} tBTA_SYS_CB;

/*****************************************************************************
 *  Global variables
 ****************************************************************************/

/* system manager control block */
extern tBTA_SYS_CB bta_sys_cb;

/* functions used for BTA SYS HW state machine */
void bta_sys_hw_error();
void bta_sys_hw_api_enable();
void bta_sys_hw_api_disable();
void bta_sys_hw_evt_enabled();
void bta_sys_hw_evt_stack_enabled();

#endif /* BTA_SYS_INT_H */
