
#include <stdio.h>
#include "send_breach_alerts.h"
#include "send_email_alerts.h"

static void sendLowBreachAlertToEmail(const char *recepient);
static void sendHighBreachAlertToEmail(const char *recepient);
static void sendNormalLvlAlertToEmail(const char *recepient);

static void sendLowBreachAlertToEmail(const char *recepient) {
  printf("To: %s\n", recepient);
  printf("Hi, the temperature is too low\n");
}

static void sendHighBreachAlertToEmail(const char *recepient) {
  printf("To: %s\n", recepient);
  printf("Hi, the temperature is too high\n");
}

static void sendNormalLvlAlertToEmail(const char *recepient) {
  return;
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";

  void (*emailFunction[MAX_BREACH_TYPE])(const char*) = {
    sendNormalLvlAlertToEmail,
    sendLowBreachAlertToEmail,
    sendHighBreachAlertToEmail,
  };

  if(breachType < MAX_BREACH_TYPE) {
    emailFunction[breachType](recepient);
  }
}
