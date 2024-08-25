
#ifndef SEND_BREACH_ALERTS_H_
#define SEND_BREACH_ALERTS_H_

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL,
  MAX_TARGETS,
} AlertTarget;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH,
  MAX_BREACH_TYPE
} BreachType;

void alertBreachToTarget(BreachType breachType, AlertTarget alertTarget);

#endif
