
#include <stdio.h>
#include "send_breach_alerts.h"
#include "send_email_alerts.h"

static void sendToController(BreachType breachType);

static void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void alertBreachToTarget(BreachType breachType, AlertTarget alertTarget) {
  void (*alertFunction[MAX_TARGETS])(BreachType) = {
    sendToController,
    sendToEmail,
  };

  if(alertTarget < MAX_TARGETS) {
      alertFunction[alertTarget](breachType);
  }      
}

