
#include <stdio.h>
#include "send_breach_alerts.h"
#include "check_battery_temp.h"

TempLimits TempLimits_st[MAX_COOLING_TYPE] =
{
  { 0, 35 },  // PASSIVE_COOLING
  { 0, 45 },  // HI_ACTIVE_COOLING
  { 0, 40 },  // MED_ACTIVE_COOLING
  // .. Future cooling additions
};

static BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

TempLimits getTempLimits(CoolingType type) {
  TempLimits limits = { DEFAULT_LOWER_TEMP_LIMIT, DEFAULT_UPPER_TEMP_LIMIT };

  if(type < MAX_COOLING_TYPE) {
    limits = TempLimits_st[type];
  }

  return limits;
}

void checkBatteryTempAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  TempLimits lcl_limits;

  lcl_limits = getTempLimits(batteryChar.coolingType);

  BreachType breachType = inferBreach(temperatureInC, lcl_limits.lowerLimit, lcl_limits.upperLimit);

  alertBreachToTarget(breachType, alertTarget);
}


