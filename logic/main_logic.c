#include "logic_vars.c"
#include "tools.c"

void goOverBridge()
{
    setDegManipD(constsManipD.startSuspension, 62, 0, 7.96);
    lineFollowCross(25, 25, 1);
    stopMove(1);
    waitForManipD();
    setDegManipD(constsManipD.suspensionForStartBridge - constsManipD.startSuspension, 62, 0, 7.96);
    stopMove(500);
    arcEnc(-30, -29, -32, -30, 260);
    stopMove(1);
    setDegManipD(constsManipD.suspensionForStartBridge, -45, 0, 7.89);
    sleep(600);
    arcEnc(-36.5, -35, -40, -30, 383);
    stopMove(900, true);
    sleep(800);
    arcEnc(-30, -30, -30, -30, 200);
    setDegManipC(constsManipC.closed, 40, 80, 8);
    arcEnc(-18, -18, -18, -17, 20);
    stopMove(500);
    motor[motorA] = 15;
    motor[motorB] = 15;
    sleep(1000);
    stopMove(1500, true);

    waitForManipC();
    sleep(500);
    setDegManipD(constsManipD.suspensionGoBackFromBridge, 75, 0, 8);
    waitForManipD();
    arcEnc(50, 50, 100, 80, 215);
    arcEnc(80, 80, 40, 27, 210);
    stopMove(1000);
    setDegManipD(constsManipD.suspensionGoBackFromBridge - constsManipD.suspenionPeakGoBack, -50, 0, 8);
    arcEnc(40, 40, 45, 30, 130);
    stopMove(1000);
}

void goOverObstacles()
{
    setDegManipD(constsManipD.startSuspension, 50, 0, 7.96);
    lineFollowCross(25, 25, 1);
    stopMove(100);
    setDegManipD(constsManipD.suspensionOverObstacles1Part - constsManipD.startSuspension, 65, 0, 7.96);
    waitForManipD();
    setDegManipD(constsManipD.suspensionOverObstacles - constsManipD.suspensionOverObstacles1Part, 35, 0, 7.96);
    waitForManipD();
    arcEnc(30, -30, -90, -26, 65);
    stopMove(300);
    arcEnc(-30, -30, -90, -26, 703);
    stopMove(300);
    arcEnc(-30, 30, -90, -26, 187);
    stopMove(450);
    arcEnc(-30, -31, -45, -27, 530);
    stopMove(450);
    arcEnc(30, -35, -35, -35, 118);
    stopMove(4500);
    arcEnc(30, 30, 30, 30, 100);
    stopMove(4500);
    setDegManipD(constsManipD.suspensionOverObstacles, -30, 0, 8);
    waitForManipD();
    arcEnc(-25, -25, -25, -20, 103);
    setDegManipC(constsManipC.closed, 50, 80, 8);
    stopMove(600);
    waitForManipC();
    setDegManipD(constsManipD.suspensionOverObstacles1Part, 75, 0, 7.96);
    waitForManipD();
    setDegManipD(constsManipD.suspensionOverObstaclesBack - constsManipD.suspensionOverObstacles1Part, 60, 0, 7.96);
    waitForManipD();
    arcEnc(-30, 30, -50, -30, 117);
    stopMove(100);
    arcEnc(30, 30, 90, 30, 640);
    stopMove(1000);
    arcEnc(-30, 30, -90, -30, 130);
    stopMove(300);
    setDegManipD(constsManipD.suspensionOverObstacles - constsManipD.holdCubes, -30, 0, 8);
    arcEnc(-30, -30, -90, -30, 420);
    stopMove(300);
    arcEnc(-30, 30, -90, -30, 175);
    stopMove(400);
    waitForManipD();
    stopD();

    // setDegManipD(constsManipD.startSuspension, 50, 0, 7.96);
    // lineFollowCross(25, 25, 1);
    // stopMove(100);
    // setDegManipD(constsManipD.suspensionOverObstacles1Part - constsManipD.startSuspension, 65, 0, 7.96);
    // waitForManipD();
    // setDegManipD(constsManipD.suspensionOverObstacles - constsManipD.suspensionOverObstacles1Part, 35, 0, 7.96);
    // sleep(200);
    // arcEnc(-30, 0, -100, -30, 380);
    // stopMove(500);
    // arcEnc(0, -30, -100, -30, 380);
    // arcEnc(-30, -30, -30, -30, 130);
    // arcEnc(0, -40, -80, -40, 171);
    // arcEnc(-50, -50, -80, -40, 190);
    // arcEnc(-50, -10, -50, -50, 139);
    // stopMove(2000, true);
    // setDegManipD(constsManipD.suspensionOverObstacles, -40, 0, 8);
    // waitForManipD();
    // sleep(100);
    // arcEnc(-25, -25, -25, -25, 150);
    // stopMove(1)
    // setDegManipC(constsManipC.closed, 50, 80, 8);
    // waitForManipC();
    // sleep(100);
    // setDegManipD(constsManipD.suspensionOverObstacles1Part, 75, 0, 7.96);
    // waitForManipD();
    // setDegManipD(constsManipD.suspensionOverObstaclesBack - constsManipD.suspensionOverObstacles1Part, 55, 0, 7.96);
    // waitForManipD();
    // arcEnc(58, 58, 80, 50, 245);
    // arcEnc(50, -20, 50, 50, 160);
    // arcEnc(25, 25, 50, 25, 310);
    // stopMove(2000);
    // arcEnc(0, -60, -90, -50, 400);
    // setDegManipD(constsManipD.suspensionOverObstaclesBack, -20, 0, 8);
    // stopMove(1000);
}

void startFirstMovement()
{
    arcEnc(30, -30, 50, 30, 45);
    stopMove(100);
    arcEnc(-30, -30, -60, -80, 100);
    setMotorA(-90);
    setMotorB(-90);

    getCDValues(&CDSensor2);
    while (CDSensor2.normAmbient > 20)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
}

void prepareBeforeTakeCubesFromLine() {
    if (CUBE_MANIP_LEFT[0] != 0 && CUBE_MANIP_RIGHT[0] != 0)
    {
        setDegManipD(constsManipD.readyFor2 - constsManipD.holdCubes, 40, 0, 8);
        waitForManipD();
    }
    else
    {
        setTimeManipC(1000, -30, 0, 8);
    }
}

void takeCubesFromLine()
{
    if (CUBE_MANIP_LEFT[0] != 0 || CUBE_MANIP_RIGHT[0] != 0)
    {
        arcEnc(-25, -25, -35, -25, 260);
        arcEnc(-20, -20, -15, -15, 20);
        stopMove(200);
        setTimeManipC(200, -60, 0, 8);
        setTimeManipD(1200, -40, 0, 8);
        waitForManipD();
        sleep(200);
        setTimeManipC(500, 80, 80, 8);
        waitForManipC();
        sleep(100);
        setDegManipD(constsManipD.holdCubes, 40, 0, 8);
        waitForManipD();
        stopMove(300);
    }
    else
    {
        arcEnc(-25, -25, -45, -20, 255);
        setTimeManipC(500, 80, 70, 8);
        arcEnc(-20, -20, -15, -15, 26);
        stopMove(100);
        waitForManipC();
        sleep(200);
        setDegManipD(constsManipD.holdCubes, 40, 0, 8);
        waitForManipD();
    }
    arcEnc(27, 27, 60, 27, 275);
    stopMove(300);
}

void takeRedAndYellowLower()
{
}

void takeRedAndYellowUpper()
{
    // prepareBeforeTakeCubesFromLine();
    // arcEnc(0, 29, 90, 29, 300);

    // setMotorBrakeMode(motorA, motorBrake);
    // setMotorA(0);
    // setMotorB(28);
    // getCDValues(&CDSensor2);
    // while (CDSensor2.normAmbient < 80)
    // {
    //     getCDValues(&CDSensor2);
    // }
    // MTVarsA.targetEnc = nMotorEncoder[motorA];
    // MTVarsB.targetEnc = nMotorEncoder[motorB];

    // stopMove(300, true);

    // setMotorBrakeMode(motorB, motorBrake);
    // setMotorB(0);
    // setMotorA(28);
    // getCDValues(&CDSensor1);
    // while (CDSensor1.normAmbient < 92.5)
    // {
    //     getCDValues(&CDSensor1);
    // }
    // MTVarsA.targetEnc = nMotorEncoder[motorA];
    // MTVarsB.targetEnc = nMotorEncoder[motorB];
    // stopMove(100, true);
    // takeCubesFromLine();

    // arcEnc(0, -29, -60, -29, 350);
    // setMotorBrakeMode(motorA, motorBrake);
    // setMotorA(0);
    // setMotorB(-29);
    // getCDValues(&CDSensor2);
    // while (CDSensor2.normAmbient < 80)
    // {
    //     getCDValues(&CDSensor2);
    // }
    // while (CDSensor2.normAmbient > 70)
    // {
    //     getCDValues(&CDSensor2);
    // }
    // MTVarsA.targetEnc = nMotorEncoder[motorA];
    // MTVarsB.targetEnc = nMotorEncoder[motorB];
    // stopMove(400, true);
    CUBE_MANIP_LEFT[0] = 1;
    CUBE_MANIP_RIGHT[0] = 1;

    lineFollowEncoder(28, 50, 50, 50);
    setMotorA(-50);
    setMotorB(-50);
    getCDValues(&CDSensor1);
    while (CDSensor1.normAmbient > 20)
    {
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    arcEnc(-50, -50, -70, -70, 60);
    lineFollowEncoder(70, 45, 30, 210);
    stopMove(400);

    // prepareBeforeTakeCubesFromLine();
    // arcEnc(0, 29, 90, 29, 350);

    // setMotorBrakeMode(motorA, motorBrake);
    // setMotorA(0);
    // setMotorB(28);
    // getCDValues(&CDSensor2);
    // while (CDSensor2.normAmbient < 80)
    // {
    //     getCDValues(&CDSensor2);
    // }
    // MTVarsA.targetEnc = nMotorEncoder[motorA];
    // MTVarsB.targetEnc = nMotorEncoder[motorB];

    // stopMove(300, true);

    // setMotorBrakeMode(motorB, motorBrake);
    // setMotorB(0);
    // setMotorA(28);
    // getCDValues(&CDSensor1);
    // while (CDSensor1.normAmbient < 92.5)
    // {
    //     getCDValues(&CDSensor1);
    // }
    // MTVarsA.targetEnc = nMotorEncoder[motorA];
    // MTVarsB.targetEnc = nMotorEncoder[motorB];
    // stopMove(100, true);
    // takeCubesFromLine();

    CUBE_MANIP_LEFT[1] = 1;
    CUBE_MANIP_RIGHT[1] = 1;
    CUBE_MANIP_LEFT[0] = 4;
    CUBE_MANIP_RIGHT[0] = 4;
}

void goToLowerFromUpper() {
    arcEnc(30, -30, -60, -30, 180);
    stopMove(100);
    arcEnc(-30, -30, -93, -30, 700);
    setMotorA(-30);
    setMotorB(-30);
    getCDValues(&CDSensor1);
    while (CDSensor1.normAmbient < 90)
    {
        getCDValues(&CDSensor1);
    }
    while (CDSensor1.normAmbient > 30)
    {
        getCDValues(&CDSensor1);
    }
    while (CDSensor1.normAmbient < 95)
    {
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    arcEnc(-30, -30, -30, -30, 7);
    arcEnc(0, -30, -90, -30, 370);

    setMotorBrakeMode(motorA, motorBrake);
    setMotorA(0);
    setMotorB(-30);
    getCDValues(&CDSensor2);
    while (CDSensor2.normAmbient < 90)
    {
        getCDValues(&CDSensor2);
    }
    getCDValues(&CDSensor2);
    while (CDSensor2.normAmbient > 60)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    stopMove(300, true);
    arcEnc(30, 30, 50, 30, 240);
    stopMove(300);

    // использовать для старта в lower
    lineFollowEncoder(70, 90, 27, 200);

    setMotorA(-27);
    setMotorB(-27);
    getCDValues(&CDSensor1);
    while (CDSensor1.normAmbient > 30)
    {
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(-29, -29, -40, -45, 70);
    lineFollowEncoder(45, 40, 30, 50);
    stopMove(300);
}

void buildTowersInLower() {
}

void myStart()
{
    startFirstMovement();
    stopMove(0, true);
    if (UPPER_START)
    {
        lineFollowEncoder(70, 90, 27, 370);

        setMotorA(-27);
        setMotorB(-27);
        getCDValues(&CDSensor1);
        while (CDSensor1.normAmbient > 30)
        {
            getCDValues(&CDSensor1);
        }
        stopMove(600, true);

        arcEnc(30, 30, 40, 30, 89);
        stopMove(300);

        takeRedAndYellowUpper();
        goToLowerFromUpper();
        buildTowersInLower();
    }
    else
    {
        stopMove(1000);

        arcEnc(30, 30, 40, 30, 230); // нужно поставить другие градусы
        stopMove(1000);
    }
}

void testFunc()
{
    // setDefaultLineRightStop();
    // lineFollowCross(20, 20, 1);
    // stopMove(1000);

    //displayValues(&CDSensor2);
    myStart();

    // setDegManipC(constsManipC.closed, 40, 80, 7.9);
    // waitForManipC();
    // sleep(2000);
    // setDegManipD(constsManipD.suspensionGoBackFromBridge, 68, 0, 8);
    // waitForManipD();
    // stopD();
    // sleep(3000);
    // setDegManipD(constsManipD.suspensionGoBackFromBridge, -25, 0, 8);
    // waitForManipD();

    // setDegManipD(constsManipD.suspensionGoBackFromBridge, 60, 0, 8);
    // waitForManipD();
    // sleep(1000);
    // setDegManipD(constsManipD.suspensionGoBackFromBridge, -30, 0, 8);

    // lineFollowEncoder(20, 70, 70, 300);
    // playSound(soundBlip);
    // arcEnc(-70, -70, -70, -20, 1200);
    // stopMove(1000);
}

void mainLogic()
{
    myStart();
}