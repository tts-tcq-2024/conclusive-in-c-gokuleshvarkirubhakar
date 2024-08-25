
#include <stdio.h>
#include "send_breach_alerts.h"
#include "send_email_alerts.h"

#define TEST_ENVIRONMENT

int controllerAlertCount = 0;

#ifdef TEST_ENVIRONMENT
#define sendAlertToController sendToControllerStub
#else
#define sendAlertToController sendToController
#endif

static void sendToControllerStub(BreachType breachType) {
    controllerAlertCount++;
}

static void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void alertBreachToTarget(BreachType breachType, AlertTarget alertTarget) {
  void (*alertFunction[MAX_TARGETS])(BreachType) = {
    sendAlertToController,
    sendToEmail,
  };

  if(alertTarget < MAX_TARGETS) {
      alertFunction[alertTarget](breachType);
  }      
}

