#pragma config(Sensor, S1,     ,               sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S2,     ,               sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S3,     ,               sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Motor,  motorA,          leftMotor,     tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorB,          rightMotor,    tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorC,           ,             tmotorEV3_Large, openLoop, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Medium, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "include/includes.h"
#include "logic/main_logic.c"
#include "logic/define_func.c"

task main()
{
	// define everything
	motor[motorA] = 0;
	motor[motorB] = 0;
	motor[motorC] = 0;
	motor[motorD] = 0;
	setMotorBrakeMode(motorA, motorCoast);
	setMotorBrakeMode(motorB, motorCoast);
	int r, g, b;
	getColorRawRGB(S1, r, g, b);
	getColorRawRGB(S2, r, g, b);
	getColorRawRGB(S3, r, g, b);
	sleep(200);

	initAll();
	setSoundVolume(30);

	// ??????N????�?????�N?N? N?????N??�N???N?N? ??N??�??N? ??????N??�?�???�?�N?????

	float startExecution = nPgmTime;

	float now = getBatteryVoltage();
	if (now < 7.8)
	{
		playSound(soundException);
	}
	eraseDisplay();
	displayCenteredBigTextLine(5, "voltage");
	displayCenteredBigTextLine(10, "%f", now);

	defineForLogic();

	defineMain();
	setLEDColor(ledOff);

#if RUN_ONLY_TEST_FUNCTION == 1
	testFunc();
#else
	mainLogic();
#endif

	stopMove(1, true);
	eraseDisplay();
	displayCenteredBigTextLine(5, "seconds");
	displayCenteredBigTextLine(10, "%f", (float)(nPgmTime - startExecution) / 1000);
		flushButtonMessages();
		waitForButtonPress();
}
