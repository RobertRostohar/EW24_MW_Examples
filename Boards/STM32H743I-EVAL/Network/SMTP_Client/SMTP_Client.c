/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::Network
 * Copyright (c) 2004-2019 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    SMTP_Client.c
 * Purpose: SMTP Client example
 *----------------------------------------------------------------------------*/

#include <stdio.h>

#include "main.h"

#include "cmsis_os2.h"                  // ::CMSIS:RTOS2

#include "rl_net.h"                     // Keil::Network&MDK:CORE

// Main stack size must be multiple of 8 Bytes
#define APP_MAIN_STK_SZ (1024U)
uint64_t app_main_stk[APP_MAIN_STK_SZ / 8];
const osThreadAttr_t app_main_attr = {
  .stack_mem  = &app_main_stk[0],
  .stack_size = sizeof(app_main_stk)
};

static const NET_SMTP_MAIL mail = {
  /* Addresses: From */
  "Alex  <alex@gmail.com>;",
  /* Addresses: To */
  "Alister <alister@example.com>;"
  "Susan   <susan@example.com>;",
  /* Cc */
  NULL,
  /* Bcc */
  NULL,
  /* Subject */
  "Subject text",
  /* Message */
  "This is email body.",
  /* Attachments */
  NULL,
  /* Encoding */
  NULL
};

static const NET_SMTP_MTA server = {
  /* Server address (FQDN or IP address) */
  "smtp.gmail.com",
  /* Server port */
  25,
  /* Service control flags */
  0,
  /* Account user name, can be NULL */
  "username",
  /* Account password, can be NULL */
  "password"
};

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
  netStatus retv;
  (void)argument;

  printf("MW Network      \n\r");
  printf("SMTP Client     \n\r");
  printf("Sending email...\n\r");

  netInitialize();

  retv = netSMTPc_SendMail(&mail, &server);
  if (retv == netOK) {
    printf("Success, email sent.\n\r");
  } else {
    printf("Send email failed.\n\r");
  }

  osThreadExit();
}
