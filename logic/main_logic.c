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
    setDegManipD(nMotorEncoder[motorD] - constsManipD.prepareToTakeFromLine, -70, 0);
    waitForManipD();
    setDegManipC(constsManipC.takeFromLineCube, 90, 0);
    waitForManipC();
    setDegManipD(constsManipD.takeCube - nMotorEncoder[motorD], 20, 0);

    arcEnc(-23, 0, -70, -23, 380);
    arcEnc(0, 23, 70, 23, 380);
    setMotorB(45);
    sleep(250);
    stopMove(100, true);

    arcEnc(25, -24, 60, 30, 300);
    setMotorA(32);
    setMotorB(-30);
    getCDValues(&CDSensor1);
    while (true)
    {
        if (CDSensor1.normRed > 200 && CDSensor1.normGreen < 200 && CDSensor1.normBlue < 200)
        {
            break;
        }
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    

    arcEnc(25, -24, 40, 14, 270);

    stopMove(300, true);
    setTimeManipC(400, 50, 0);
    waitForManipC();
    sleep(100);
    setDegManipC(nMotorEncoder[motorC] - constsManipC.takeFromLineCube, -70, 0);
    waitForManipC();
    setDegManipD(nMotorEncoder[motorD] - constsManipD.goOverCubes, -50, 0);
    waitForManipD();
    sleep(300);
    arcEnc(24, -23, 40, 18, 150);
    stopMove(300, true);

    setDegManipD(constsManipD.takeCube - nMotorEncoder[motorD], 20, 0);
    waitForManipD();
    sleep(300);
    arcEnc(24, -23, 15, 11, 80);
    stopMove(300, true);
    setTimeManipC(350, 60, 40);
    waitForManipC();
    setDegManipD(nMotorEncoder[motorD] - constsManipD.put1Cube, -70, 0);
    waitForManipD();
    sleep(200);
    arcEnc(-23, 23, 25, 11, 232);
    stopMove(300, true);
    setTimeManipD(400, 20, 0);
    waitForManipD();
    sleep(200);
    setDegManipC(nMotorEncoder[motorC] - constsManipC.takeFromLineCube, -15, 0);
    waitForManipC();
    sleep(300);
    setDegManipD(constsManipD.takeCube - nMotorEncoder[motorD], 20, 0);
    waitForManipD();
    sleep(300);
    setTimeManipC(700, 30, 30);
    waitForManipC();
    sleep(300);
    setDegManipC(nMotorEncoder[motorC] - constsManipC.goOverTwoCubesOnLine, -50, 0);
    waitForManipC();
    sleep(300);
    setDegManipD(nMotorEncoder[motorD] - constsManipD.goOverTwoCubes, -70, 0);
    waitForManipD();
    sleep(300);

    arcEnc(25, -23, 50, 20, 230);
    stopMove(300, true);
    setDegManipD(constsManipD.takeCube - nMotorEncoder[motorD], 30, 0);
    waitForManipD();
    setDegManipC(constsManipC.takeFromLineCube - nMotorEncoder[motorC], 70, 0);
    waitForManipC();
    arcEnc(17, -16, 17, 11, 260);
    stopMove(300, true);

    setTimeManipC(400, 50, 0);
    waitForManipC();
    sleep(100);
    setDegManipC(nMotorEncoder[motorC] - constsManipC.takeFromLineCube, -40, 0);
    waitForManipC();
    setDegManipD(nMotorEncoder[motorD] - constsManipD.goOverCubes, -80, 0);
    waitForManipD();
    sleep(300);
    arcEnc(17, -16, 17, 11, 137);
    stopMove(300, true);

    setDegManipD(constsManipD.takeCube - nMotorEncoder[motorD], 20, 0);
    waitForManipD();
    sleep(300);
    arcEnc(17, -16, 17, 17, 40);
    stopMove(300, true);
    setTimeManipC(350, 60, 40);
    waitForManipC();
    setDegManipD(nMotorEncoder[motorD] - constsManipD.put1Cube, -70, 0);
    waitForManipD();
    sleep(200);
    arcEnc(-23, 23, 25, 15, 169);
    stopMove(300, true);
    setTimeManipD(400, 20, 0);
    waitForManipD();
    sleep(200);
    setDegManipC(nMotorEncoder[motorC] - constsManipC.takeFromLineCube, -15, 0);
    waitForManipC();
    sleep(300);
    setDegManipD(constsManipD.takeCube - nMotorEncoder[motorD], 20, 0);
    waitForManipD();
    sleep(300);
    setTimeManipC(700, 40, 80);
    waitForManipC();
    sleep(300);
    setDegManipD(nMotorEncoder[motorD] - constsManipD.carryCubes, -60, 0);
    waitForManipD();
}

void lowerToUpper()
{

}

void upperToLower()
{
    arcEnc(0, -50, -70, -50, 750);
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    gBoost = 25;
    arcEnc(70, -70, 200, 90, 680);
    gBoost = 10;
    arcEnc(90, -90, 50, 30, 420);
    playSound(soundBlip);

    setMotorA(30);
    setMotorB(-30);

    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(45, 0, 80, 40, 540);
    setMotorA(40);
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue > 50)
    {
        getCDValues(&CDSensor1);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    setLeftSensorOut();
    lineFollowEncoder(35, 60, 30, 550);
    setMotorA(28);
    setMotorB(-28);
    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 100)
    {
        getCDValues(&CDSensor2);
    }
    setMotorA(26);
    setMotorB(-26);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }
    setMotorA(24);
    setMotorB(-24);
    // ехать до коричневого
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 400)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(22, -22, 20, 20, 15)

    // доворот одним колесом до зоны разгрузки
    arcEnc(40, 0, 80, 25, 500);
    setMotorA(22);
    while (true) {
        getCDValues(&CDSensor2);
        if (CDSensor2.normRed > 100 && CDSensor2.normGreen < 60 && CDSensor2.normBlue < 60) {
            break;
        }
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(-18, 18, 20, 15, 130);
    stopMove(300);
    
    setTimeManipD(400, 10, 0);
    waitForManipD();
    setDegManipC(nMotorEncoder[motorC] - constsManipC.almostClose, -40, 0);
    waitForManipC();
    sleep(300);
    arcEnc(-18, 18, 18, 14, 20);
    stopMove(300);
    setDegManipD(nMotorEncoder[motorD] - constsManipD.takeFromStorage, -70, 0);
    waitForManipD();
    sleep(300);
    setDegManipC(nMotorEncoder[motorC] - constsManipC.openToTakeFromStorage, -70, 0);
    waitForManipC();
    sleep(300);

    arcEnc(-30, 30, 30, 12, 230);
    stopMove(300);

    // захват башни
    setDegManipC(constsManipC.almostClose - nMotorEncoder[motorC], 40, 0);
    waitForManipC();
    sleep(300);
    setDegManipD(constsManipD.takeCube - nMotorEncoder[motorD], 30, 0);
    waitForManipD();
    sleep(300);
    arcEnc(14, -14, 12, 11, 100);
    stopMove(300);
    setTimeManipC(300, 40, 30);
    waitForManipC();
    sleep(300);
    setDegManipD(nMotorEncoder[motorD] - constsManipD.carryCubes, -60, 0);
    waitForManipD();

    // перевозим башню в красную зону
}

void testFunc()
{
    // waitInitManip();
    // playSound(soundBlip);
    // setDegManipD(nMotorEncoder[motorD] - constsManipD.prepareToTakeFromLine, -60, 0);
    // waitForManipD();
    // setDegManipC(constsManipC.takeFromLineCube, 90, 0);
    // waitForManipC();
    // setDegManipD(constsManipD.takeCube - nMotorEncoder[motorD], 25, 0);
    // waitForManipD();
    // sleep(5000);
    // setTimeManipC(800, 40, 80);
    // waitForManipC();
    // sleep(300);
    // setDegManipD(nMotorEncoder[motorD] - constsManipD.put2Cube, -80, 0);
    // waitForManipD();
    // sleep(3000000);

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