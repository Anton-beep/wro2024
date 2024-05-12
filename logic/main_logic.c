#include "logic_vars.c"
#include "tools.c"

void calibrateSensor3()
{
    sleep(2000);
    displayValues(&CDSensor3);
}

void takeRedAndYellowCubes()
{
    waitInitManip();
    setDegManipD(-nMotorEncoder[motorD] + constsManipD.prepareToTakeFromLine, 70, 0);
    waitForManipD();
    setDegManipC(constsManipC.takeFromLineCube, 90, 0);
    waitForManipC();
    setDegManipD(nMotorEncoder[motorD] - constsManipD.takeCube, -20, 0);

    arcEnc(-23, 0, -70, -23, 380);
    arcEnc(0, 23, 70, 23, 380);
    setMotorB(45);
    sleep(250);
    stopMove(100, true);
    arcEnc(25, -24, 80, 20, 553);

    stopMove(100, true);
    setTimeManipC(400, 50, 0);
    waitForManipC();
    sleep(300);
    setDegManipC(nMotorEncoder[motorC] - constsManipC.takeFromLineCube, -70, 0);
    waitForManipC();
    sleep(300);
    setDegManipD(-nMotorEncoder[motorD] + constsManipD.goOverCubes, 100, 0);
    waitForManipD();
    sleep(300);
    arcEnc(24, -23, 40, 18, 150);
    stopMove(300, true);

    setDegManipD(nMotorEncoder[motorD] - constsManipD.takeCube, -20, 0);
    waitForManipD();
    sleep(300);
    arcEnc(24, -23, 30, 11, 70);
    stopMove(300, true);
    setTimeManipC(350, 60, 40);
    waitForManipC();
    setDegManipD(-nMotorEncoder[motorD] + constsManipD.put1Cube, 100, 0);
    waitForManipD();
    sleep(200);
    arcEnc(-23, 23, 25, 11, 219);
    stopMove(300, true);
    setTimeManipD(350, -7, 0);
    waitForManipD();
    sleep(200);
    setDegManipC(nMotorEncoder[motorC] - constsManipC.takeFromLineCube, -15, 0);
    waitForManipC();
    sleep(300);
    setDegManipD(nMotorEncoder[motorD] - constsManipD.takeCube, -50, 0);
    waitForManipD();
    sleep(300);
    setTimeManipC(800, 30, 0);
    waitForManipC();
    sleep(300);
    setDegManipC(nMotorEncoder[motorC] - constsManipC.goOverTwoCubesOnLine, -50, 0);
    waitForManipC();
    sleep(300);
    setDegManipD(-nMotorEncoder[motorD] + constsManipD.goOverTwoCubes, 100, 0);
    waitForManipD();
    sleep(300);

    arcEnc(25, -23, 50, 20, 150);
    stopMove(300, true);
    setDegManipD(nMotorEncoder[motorD] - constsManipD.takeCube, -50, 0);
    waitForManipD();
    setDegManipC(constsManipC.takeFromLineCube - nMotorEncoder[motorC], 70, 0);
    waitForManipC();
    arcEnc(17, -16, 17, 11, 340);
    stopMove(300, true);

    setTimeManipC(350, 60, 0);
    waitForManipC();
    sleep(300);
    setDegManipC(nMotorEncoder[motorC] - constsManipC.takeFromLineCube, -40, 0);
    waitForManipC();
    sleep(300);
    setDegManipD(-nMotorEncoder[motorD] + constsManipD.goOverCubes, 100, 0);
    waitForManipD();
    sleep(300);
    arcEnc(17, -16, 17, 11, 137);
    stopMove(300, true);

    setDegManipD(nMotorEncoder[motorD] - constsManipD.takeCube, -20, 0);
    waitForManipD();
    sleep(300);
    arcEnc(17, -16, 17, 17, 30);
    stopMove(300, true);
    setTimeManipC(350, 60, 40);
    waitForManipC();
    setDegManipD(-nMotorEncoder[motorD] + constsManipD.put1Cube, 100, 0);
    waitForManipD();
    sleep(200);
    arcEnc(-23, 23, 25, 15, 161);
    stopMove(300, true);
    setTimeManipD(350, -7, 0);
    waitForManipD();
    sleep(200);
    setDegManipC(nMotorEncoder[motorC] - constsManipC.takeFromLineCube, -15, 0);
    waitForManipC();
    sleep(300);
    setDegManipD(nMotorEncoder[motorD] - constsManipD.takeCube, -50, 0);
    waitForManipD();
    sleep(300);
    setTimeManipC(800, 30, 0);
    waitForManipC();
}

void lowerToUpper()
{

}

void upperToLower()
{
    arcEnc(0, -70, -90, -40, 750);
    stopMove(300, true);
    arcEnc(17, -17, 25, 25, 50);
    gBoost = 25;
    arcEnc(100, -100, 100, 70, 630);
    gBoost = 10;
    arcEnc(70, -70, 23, 23, 420);
    playSound(soundBlip);

    setMotorA(23);
    setMotorB(-23);

    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(35, 0, 60, 34, 540);
    setMotorA(32);
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue > 100)
    {
        getCDValues(&CDSensor1);
    }
    setMotorA(30);
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue < 600)
    {
        getCDValues(&CDSensor1);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    stopMove(3000);
}

void testFunc()
{
    takeRedAndYellowCubes();
    if (UPPER_START)
    {
        upperToLower();
    }
    else
    {
        lowerToUpper();
    }
}

void mainLogic()
{
}