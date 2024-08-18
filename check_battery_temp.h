
#ifndef CHECK_BATTERY_TEMP_H_
#define CHECK_BATTERY_TEMP_H_

#define DEFAULT_LOWER_TEMP_LIMIT    0.0
#define DEFAULT_UPPER_TEMP_LIMIT    0.0

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING,
  MAX_COOLING_TYPE
} CoolingType;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

typedef struct {
  double upperLimit;
  double lowerLimit;
} TempLimits;

static BreachType inferBreach(double value, double lowerLimit, double upperLimit);
TempLimits getTempLimits(CoolingType type);
void checkBatteryTempAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

#endif
