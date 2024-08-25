
#include <stdio.h>
#include "send_breach_alerts.h"
#include "send_email_alerts.h"

#define TEST_ENVIRONMENT

int lowBreachAlertCount = 0;
int highBreachAlertCount = 0;
int normalLvlAlertCount = 0;

#ifdef TEST_ENVIRONMENT
#define sendLowBreachEmailAlert  sendLowBreachAlertToEmailStub
#define sendHighBreachEmailAlert sendHighBreachAlertToEmailStub
#define sendNormalLvlEmailAlert  sendNormalLvlAlertToEmailStub
#else
#define sendLowBreachEmailAlert  sendLowBreachAlertToEmail
#define sendHighBreachEmailAlert sendHighBreachAlertToEmail
#define sendNormalLvlEmailAlert  sendNormalLvlAlertToEmail
#endif

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

static void sendLowBreachAlertToEmailStub(const char *recepient) {
  lowBreachAlertCount++;
}

static void sendHighBreachAlertToEmailStub(const char *recepient) {
  highBreachAlertCount++;
}

static void sendNormalLvlAlertToEmailStub(const char *recepient) {
  normalLvlAlertCount++;
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
