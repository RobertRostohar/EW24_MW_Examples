/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::Network
 * Copyright (c) 2004-2019 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    HTTP_Upload.c
 * Purpose: HTTP File upload example
 *----------------------------------------------------------------------------*/

#include <stdio.h>

#include "main.h"

#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#include "cmsis_vio.h"                  // ::CMSIS Driver:VIO

#include "rl_net.h"                     // Keil::Network&MDK:CORE
#include "rl_fs.h"                      // Keil::File System&MDK:CORE

// Main stack size must be multiple of 8 Bytes
#define APP_MAIN_STK_SZ (1024U)
uint64_t app_main_stk[APP_MAIN_STK_SZ / 8];
const osThreadAttr_t app_main_attr = {
  .stack_mem  = &app_main_stk[0],
  .stack_size = sizeof(app_main_stk)
};

/* Thread IDs */
static osThreadId_t TID_Terminal;

/* IP address change notification */
void netDHCP_Notify (uint32_t if_num, uint8_t option, const uint8_t *val, uint32_t len) {

  (void)if_num;
  (void)val;
  (void)len;

  if (option == NET_DHCP_OPTION_IP_ADDRESS) {
    /* IP address change, trigger LCD update */
    osThreadFlagsSet(TID_Terminal, 0x01);
  }
}

/*-----------------------------------------------------------------------------
  Thread 'Terminal': Terminal handler
 *----------------------------------------------------------------------------*/
static __NO_RETURN void Terminal (void *argument) {
  static uint8_t ip_addr[NET_ADDR_IP6_LEN];
  static char    ip_ascii[40];

  (void)argument;

  printf("IP4:Waiting for DHCP");

  /* Print Link-local IPv6 address */
  netIF_GetOption(NET_IF_CLASS_ETH,
                  netIF_OptionIP6_LinkLocalAddress, ip_addr, sizeof(ip_addr));

  netIP_ntoa(NET_ADDR_IP6, ip_addr, ip_ascii, sizeof(ip_ascii));

  printf("IP6:%.16s", ip_ascii);
  printf("%s", ip_ascii+16);

  while(1) {
    /* Wait for signal from DHCP */
    osThreadFlagsWait(0x01U, osFlagsWaitAny, osWaitForever);

    /* Retrieve and print IPv4 address */
    netIF_GetOption(NET_IF_CLASS_ETH,
                    netIF_OptionIP4_Address, ip_addr, sizeof(ip_addr));

    netIP_ntoa(NET_ADDR_IP4, ip_addr, ip_ascii, sizeof(ip_ascii));

    printf("IP4:%-16s",ip_ascii);
  }
}

/*-----------------------------------------------------------------------------
  Thread 'BlinkLed': Blink the LEDs on an eval board
 *----------------------------------------------------------------------------*/
static __NO_RETURN void BlinkLed (void *argument) {
  const uint8_t led_val[16] = { 0x48,0x88,0x84,0x44,0x42,0x22,0x21,0x11,
                                0x12,0x0A,0x0C,0x14,0x18,0x28,0x30,0x50 };
  uint32_t cnt = 0U;

  (void)argument;

  while(1) {
    /* Every 100 ms */
    vioSetSignal(0xFFU, led_val[cnt]);
    if (++cnt >= sizeof(led_val)) {
      cnt = 0U;
    }
    osDelay (100U);
  }
}

/*-----------------------------------------------------------------------------
 * Application initialization
 *----------------------------------------------------------------------------*/
int32_t app_initialize (void) {
  osThreadNew(app_main, NULL, &app_main_attr);
  return 0;
}

/*-----------------------------------------------------------------------------
  Main Thread 'app_main': Run Network
 *----------------------------------------------------------------------------*/
__NO_RETURN void app_main (void *argument) {
  (void)argument;

  printf("Network HTTP Upload example\n");

  if (finit("M0:") == fsOK) {
    fmount("M0:");
  }
  netInitialize();

                 osThreadNew(BlinkLed, NULL, NULL);
  TID_Terminal = osThreadNew(Terminal, NULL, NULL);

  osThreadExit();
}
