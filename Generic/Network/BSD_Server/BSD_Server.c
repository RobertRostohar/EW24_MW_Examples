/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::Network
 * Copyright (c) 2004-2019 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    BSD_Server.c
 * Purpose: BSD socket server example
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "RTE_Components.h" 

#include "main.h"

#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#include "cmsis_vio.h"                  // ::CMSIS Driver:VIO

#include "rl_net.h"                     // Keil::Network&MDK:CORE

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------

//   <o>Local Port <1-65535>
//   <i>Local port number.
//   <i> Default: 1001
#define SOCK_PORT      1001

//   <q>Use IPv4
//   <i>Use IPv4 Protocol to accept connections.
#define IP4_ENABLE      1

//   <q>Use IPv6
//   <i>Use IPv6 Protocol to accept connections.
#define IP6_ENABLE      0

//------------- <<< end of configuration section >>> -----------------------

#if (!(IP4_ENABLE ^ IP6_ENABLE))
  #error Select only IPv4 or only IPv6!
#endif

#define BLINKLED        0x01

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
    printf("IP4=%s\n", ip4_ascii);
  }
#endif

#if (IP6_ENABLE)
  uint8_t ip6_addr[NET_ADDR_IP6_LEN];
  char    ip6_ascii[40];

  if (netIF_GetOption(NET_IF_CLASS_ETH, netIF_OptionIP6_LinkLocalAddress,
                                        ip6_addr, sizeof(ip6_addr)) == netOK) {
    /* Print IPv6 network address (MDK-Pro only) */
    netIP_ntoa(NET_ADDR_IP6, ip6_addr, ip6_ascii, sizeof(ip6_ascii));
    printf("IP6:%s\n", ip_ascii);
  }
#endif
}

/// Stream socket server thread
static void Stream_Server (void *argument) {
  int32_t sock, sd, retv;
  char dbuf[4];

  while (1) {

#if (IP4_ENABLE)
    /* Create IPv4 socket address */
    SOCKADDR_IN addr;
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(SOCK_PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    retv = bind(sock, (SOCKADDR *)&addr, sizeof (addr));
#endif

#if (IP6_ENABLE)
    /* Create IPv6 socket address (MDK-Pro only) */
    SOCKADDR_IN6 addr6;
    addr6.sin6_family    = AF_INET6;
    addr6.sin6_port      = htons(SOCK_PORT);
    addr6.sin6_flowinfo  = 0;
    if (!inet_pton(AF_INET6, "::", &addr6.sin6_addr)) {
      /* IPv6 not supported */
      for (;;);
    }

    sock = socket(AF_INET6, SOCK_STREAM, 0);
    retv = bind(sock, (SOCKADDR *)&addr6, sizeof (addr6));
#endif

    if (retv < 0) {
      closesocket(sock);
      continue;
    }
    retv = listen(sock, 1);
    if (retv < 0) {
      closesocket(sock);
      continue;
    }
    sd = accept(sock, NULL, NULL);
    closesocket(sock);

    while (1) {
      retv = recv(sd, dbuf, sizeof (dbuf), 0);
      if (retv <= 0) {
        break;
      }
      if (dbuf[0] == BLINKLED) {
        vioSetSignal(0xFFU, (uint8_t)dbuf[1]);
      }
    }
    closesocket(sd);
  }
}

/// Datagram socket server thread
static void Dgram_Server (void *argument) {
  int32_t sock, retv;
  char dbuf[4];

  while (1) {

#if (IP4_ENABLE)
    /* Create IPv4 socket address */
    SOCKADDR_IN addr;
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(SOCK_PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    retv = bind(sock, (SOCKADDR *)&addr, sizeof (addr));
#endif

#if (IP6_ENABLE)
    /* Create IPv6 socket address (MDK-Pro only) */
    SOCKADDR_IN6 addr6;
    addr6.sin6_family    = AF_INET6;
    addr6.sin6_port      = htons(SOCK_PORT);
    addr6.sin6_flowinfo  = 0;
    if (!inet_pton(AF_INET6, "::", &addr6.sin6_addr)) {
      /* IPv6 not supported */
      for (;;);
    }

    sock = socket(AF_INET6, SOCK_DGRAM, 0);
    retv = bind(sock, (SOCKADDR *)&addr6, sizeof (addr6));
#endif

    if (retv < 0) {
      closesocket(sock);
      continue;
    }

    while (1) {
      retv = recv(sock, dbuf, sizeof (dbuf), 0);
      if (retv == BSD_ETIMEDOUT) {
        continue;
      }
      if (retv <= 0) {
        break;
      }
      if (dbuf[0] == BLINKLED) {
        vioSetSignal(0xFFU, (uint8_t)dbuf[1]);
      }
    }
    closesocket(sock);
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

  printf("Network BSD Server example\n");

  netInitialize();
  print_address();

  /* Create server threads */
  osThreadNew(Stream_Server, NULL, NULL);
  osThreadNew(Dgram_Server, NULL, NULL);

  osThreadExit();
}
