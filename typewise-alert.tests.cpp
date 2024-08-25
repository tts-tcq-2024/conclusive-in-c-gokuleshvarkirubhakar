#include <gtest/gtest.h>
#include "check_battery_temp.h"
#include "send_breach_alerts.h"
#include "send_email_alerts.h"

extern int controllerAlertCount;
extern int lowBreachAlertCount;
extern int highBreachAlertCount;
extern int normalLvlAlertCount;

TEST(BatteryMonitorTest, inferBreach_TooLow) {
    EXPECT_EQ(inferBreach(10, 20, 30), TOO_LOW);
}

TEST(BatteryMonitorTest, inferBreach_TooHigh) {
    EXPECT_EQ(inferBreach(40, 20, 30), TOO_HIGH);
}

TEST(BatteryMonitorTest, inferBreach_Normal) {
    EXPECT_EQ(inferBreach(25, 20, 30), NORMAL);
}

TEST(BatteryMonitorTest, getTempLimits_WithinRange) {
    TempLimits limits;
    limits = getTempLimits(PASSIVE_COOLING);
    EXPECT_EQ(limits.lowerLimit, 0);
    EXPECT_EQ(limits.upperLimit, 35);
    limits = getTempLimits(HI_ACTIVE_COOLING);
    EXPECT_EQ(limits.lowerLimit, 0);
    EXPECT_EQ(limits.upperLimit, 45);
    limits = getTempLimits(MED_ACTIVE_COOLING);
    EXPECT_EQ(limits.lowerLimit, 0);
    EXPECT_EQ(limits.upperLimit, 40);
}

TEST(BatteryMonitorTest, getTempLimits_OutOfRange) {
    TempLimits limits = getTempLimits(MAX_COOLING_TYPE + 1);
    EXPECT_EQ(limits.lowerLimit, DEFAULT_LOWER_TEMP_LIMIT);
    EXPECT_EQ(limits.upperLimit, DEFAULT_UPPER_TEMP_LIMIT);
}

TEST(BatteryMonitorTest, checkBatteryTempAndAlert_Low_ToController) {
    BatteryCharacter batteryChar = { PASSIVE_COOLING };
    controllerAlertCount = 0;
    checkBatteryTempAndAlert(TO_CONTROLLER, batteryChar, -10);
    EXPECT_EQ(controllerAlertCount, 1);
}

TEST(BatteryMonitorTest, checkBatteryTempAndAlert_High_ToController) {
    BatteryCharacter batteryChar = { HI_ACTIVE_COOLING };
    controllerAlertCount = 0;
    checkBatteryTempAndAlert(TO_CONTROLLER, batteryChar, 50);
    EXPECT_EQ(controllerAlertCount, 1);
}

TEST(BatteryMonitorTest, checkBatteryTempAndAlert_Normal_ToController) {
    BatteryCharacter batteryChar = { MED_ACTIVE_COOLING };
    controllerAlertCount = 0;
    checkBatteryTempAndAlert(TO_CONTROLLER, batteryChar, 30);
    EXPECT_EQ(controllerAlertCount, 1);
}

TEST(BatteryMonitorTest, sendToEmail_LowBreach) {
    lowBreachAlertCount = 0;
    sendToEmail(TOO_LOW);
    EXPECT_EQ(lowBreachAlertCount, 1);
}

TEST(BatteryMonitorTest, sendToEmail_HighBreach) {
    highBreachAlertCount = 0;
    sendToEmail(TOO_HIGH);
    EXPECT_EQ(highBreachAlertCount, 1);
}

TEST(BatteryMonitorTest, sendToEmail_NormalBreach) {
    normalLvlAlertCount = 0;
    sendToEmail(NORMAL);
    EXPECT_EQ(normalLvlAlertCount, 1);
}
