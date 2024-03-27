/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::Network
 * Copyright (c) 2004-2019 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    BSD_Client.c
 * Purpose: BSD socket client example
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "RTE_Components.h" 

#include "main.h"

#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#include "cmsis_vio.h"                  // ::CMSIS Driver:VIO

#include "rl_net.h"                     // Keil::Network&MDK:CORE

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------

//   <o>Socket type <0=>Stream <1=>Datagram
//   <i>Stream (TCP) or Datagram (UDP) socket type.
#define SOCK_TYPE       0

//   <o>Remote Port <1-65535>
//   <i>Remote port number.
//   <i> Default: 1001
#define SOCK_PORT       1001

//   <e>Use IPv4
//   <i>Use IPv4 Protocol to connect.
#define IP4_ENABLE      1

//     <s.15>Remote IP Address
//     <i>Remote IPv4 Address in text representation.
//     <i>Default: "192.168.0.100"
#define IP4_ADDR        "192.168.0.100"

//   </e>
//   <e>Use IPv6
//   <i>Use IPv6 Protocol to connect
#define IP6_ENABLE      0

//     <s.40>Remote IP Address
//     <i>Remote IPv6 Address in text representation.
//     <i>Default: "fe80::1c30:6cff:fea2:455e"
#define IP6_ADDR        "fe80::1c30:6cff:fea2:455e"

//   </e>

//------------- <<< end of configuration section >>> -----------------------

#if (!(IP4_ENABLE ^ IP6_ENABLE))
  #error Select only IPv4 or only IPv6!
#endif

#define BLINKLED        0x01
#define SOCKTYPE  ((SOCK_TYPE == 0) ? SOCK_STREAM : SOCK_DGRAM)

// Main stack size must be multiple of 8 Bytes
#define APP_MAIN_STK_SZ (1024U)
uint64_t app_main_stk[APP_MAIN_STK_SZ / 8];
const osThreadAttr_t app_main_attr = {
  .stack_mem  = &app_main_stk[0],
  .stack_size = sizeof(app_main_stk)
};

/* Print local IP addresses */
static void print_address (void) {

#if (IP4_ENABLE)
  uint8_t ip4_addr[NET_ADDR_IP4_LEN];
  char    ip4_ascii[16];

  if (netIF_GetOption(NET_IF_CLASS_ETH, netIF_OptionIP4_Address,
                                        ip4_addr, sizeof(ip4_addr)) == netOK) {
  /* Print IPv4 network address */
    netIP_ntoa(NET_ADDR_IP4, ip4_addr, ip4_ascii, sizeof(ip4_ascii));
    printf("IP4=%-15s", ip4_ascii);
  }
#endif

#if (IP6_ENABLE)
  uint8_t ip6_addr[NET_ADDR_IP6_LEN];
  char    ip6_ascii[40];

  if (netIF_GetOption(NET_IF_CLASS_ETH, netIF_OptionIP6_LinkLocalAddress,
                                        ip6_addr, sizeof(ip6_addr)) == netOK) {
    /* Print IPv6 network address (MDK-Pro only) */
    netIP_ntoa(NET_ADDR_IP6, ip6_addr, ip6_ascii, sizeof(ip6_ascii));
    printf("IP6=%.16s", ip6_ascii);
    printf("%s",ip6_ascii+16);
  }
#endif
}

/* IP address change notification */
void netDHCP_Notify (uint32_t if_num, uint8_t option, const uint8_t *val, uint32_t len) {

  (void)if_num;
  (void)val;
  (void)len;

  if (option == NET_DHCP_OPTION_IP_ADDRESS) {
    /* IP address change, trigger LCD update */
    print_address();
  }
}

/*-----------------------------------------------------------------------------
  Thread 'Client': BSD Client socket process
 *----------------------------------------------------------------------------*/
static __NO_RETURN void Client (void *argument) {
  int32_t  sock, retv;
  uint32_t led_num, led;
  char     dbuf[4];

  (void)argument;

  led_num = 1U;

  /* Connect and send LED state */

  while (1) {
    osDelay(2000U);

    print_address();

#if (IP4_ENABLE)
    /* Create IPv4 socket address */
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(SOCK_PORT);
    if (!inet_pton(AF_INET, IP4_ADDR, &addr.sin_addr)) {
      /* Address configuration error */
      for (;;);
    }

    sock = socket(AF_INET, SOCKTYPE, 0);
    retv = connect(sock, (SOCKADDR *)&addr, sizeof(addr));
#endif

#if (IP6_ENABLE)
    /* Create IPv6 socket address (MDK-Pro only) */
    SOCKADDR_IN6 addr6;
    addr6.sin6_family   = AF_INET6;
    addr6.sin6_port     = htons(SOCK_PORT);
    addr6.sin6_flowinfo = 0;
    if (!inet_pton(AF_INET6, IP6_ADDR, &addr6.sin6_addr)) {
      /* Address configuration error or IPv6 not supported */
      for (;;);
    }

    sock = socket(AF_INET6, SOCKTYPE, 0);
    retv = connect(sock, (SOCKADDR *)&addr6, sizeof(addr6));
#endif

    if (retv < 0) {
      closesocket(sock);
      continue;
    }

    led = 0;
    while (1) {
      // Send data to BSD Server
      dbuf[0] = BLINKLED;
      dbuf[1] = 0x01 << led;
      retv = send(sock, dbuf, 2, 0);
      if (retv < 0) {
        break;
      }
      if (++led >= led_num) {
        led = 0;
      }
      // Blink LED 0
      vioSetSignal(vioLED0, vioLEDon);
      osDelay(100U);
      vioSetSignal(vioLED0, vioLEDoff);
      osDelay(900U);
    }
    closesocket (sock);
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

  netInitialize();
  print_address();

  // Create networking task
  osThreadNew(Client, NULL, NULL);

  osThreadExit();
}
