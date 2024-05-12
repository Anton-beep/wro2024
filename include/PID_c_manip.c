/*
TODO:
- тест waitForManip (wait может срботать до активации функции)
- попробовать управлять не просто мощностью, а скоростью моторов, чтобы держать стабильную скорость движения
захватов (ПИД регулятор на RPM)
*/


int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

void setPowerAdjustBatteryManipC(short pow, float batVoltage)
{
    if (pow == 0)
    {
        motor[motorC] = 0;
    }
    else
    {
        float val = pow * batVoltage / getBatteryVoltage();
        if (val < 0)
        {
            motor[motorC] = min(-1, val);
        }
        else
        {
            motor[motorC] = max(1, val);
        }
    }
}

void setPowerAdjustBatteryManipD(short pow, float batVoltage)
{
    if (pow == 0)
    {
        motor[motorD] = 0;
    }
    else
    {
        float val = pow * batVoltage / getBatteryVoltage();
        if (val < 0)
        {
            motor[motorD] = min(-1, val);
        }
        else
        {
            motor[motorD] = max(1, val);
        }
    }
}

int getSignedRPM(short mot)
{
    if (motor[mot] > 0)
    {
        return getMotorRPM(mot);
    }
    else
    {
        return -getMotorRPM(mot);
    }
}

void stopC()
{
    motor[motorC] = 0;
    setMotorBrakeMode(motorC, motorBrake);
}

void stopD()
{
    motor[motorD] = 0;
    setMotorBrakeMode(motorD, motorBrake);
}

void keepMovingManipC(short pow, float voltage)
{
    if (fabs(getMotorRPM(motorC)) < 6) {
        setPowerAdjustBatteryManipC(min(100, motor[motorC] + pow * 0.1), voltage);
    } else {
        setPowerAdjustBatteryManipC(max(pow, motor[motorC] - pow * 0.1), voltage);
    }
}

void keepMovingManipD(short pow, float voltage)
{
    if (fabs(getMotorRPM(motorD)) < 6) {
        setPowerAdjustBatteryManipD(min(100, motor[motorD] + pow * 0.1), voltage);
    } else {
        // int tempSpeed = motor[motorD] - pow * 0.1;
        // if (fabs(tempSpeed) > pow) {
        //     setPowerAdjustBatteryManipD(tempSpeed, voltage)  ; 
        // } else {
        //     setPowerAdjustBatteryManipD(pow, voltage);
        // }
    }
    eraseDisplay();
    displayTextLine(1, "rpm: %f", getMotorRPM(motorD));
    displayTextLine(2, "pow: %d", motor[motorD]);
}

void testAdjust()
{
    setPowerAdjustBatteryManipC(80, 7.6);
    while (true)
    {
        writeDebugStreamLine("%f; %d", getBatteryVoltage(), getSignedRPM(motorA));
        sleep(1);
    }
}

bool MANIP_C_READY = true;
bool MANIP_D_READY = true;

void waitForManipC()
{
    while (!MANIP_C_READY)
    {
        sleep(1);
    }
}

void waitForManipD()
{
    while (!MANIP_D_READY)
    {
        sleep(1);
    }
}

short TIME_MANIP_C_START_POW;
short TIME_MANIP_C_AFTER_POW;
float TIME_MANIP_C_VOLTAGE;
int TIME_MANIP_C_TIME;

task moveTimeManipC()
{
    setPowerAdjustBatteryManipC(TIME_MANIP_C_START_POW, TIME_MANIP_C_VOLTAGE);
    sleep(TIME_MANIP_C_TIME);
    setPowerAdjustBatteryManipC(TIME_MANIP_C_AFTER_POW, TIME_MANIP_C_VOLTAGE);
    MANIP_C_READY = true;
}

short TIME_MANIP_D_START_POW;
short TIME_MANIP_D_AFTER_POW;
float TIME_MANIP_D_VOLTAGE;
int TIME_MANIP_D_TIME;

task moveTimeManipD()
{
    setPowerAdjustBatteryManipD(TIME_MANIP_D_START_POW, TIME_MANIP_D_VOLTAGE);
    sleep(TIME_MANIP_D_TIME);
    setPowerAdjustBatteryManipD(TIME_MANIP_D_AFTER_POW, TIME_MANIP_D_VOLTAGE);
    MANIP_D_READY = true;
}

int DEG_MANIP_C_DEG;
short DEG_MANIP_C_START_POW;
short DEG_MANIP_C_AFTER_POW;
float DEG_MANIP_C_VOLTAGE;

task moveDegManipC()
{
    setPowerAdjustBatteryManipC(DEG_MANIP_C_START_POW, DEG_MANIP_C_VOLTAGE);
    int endDeg;
    if (DEG_MANIP_C_START_POW >= 0)
    {
        endDeg = nMotorEncoder[motorC] + DEG_MANIP_C_DEG;
        while (nMotorEncoder[motorC] < endDeg)
        {
            sleep(1);
        }
    }
    else
    {
        endDeg = nMotorEncoder[motorC] - DEG_MANIP_C_DEG;
        while (nMotorEncoder[motorC] > endDeg)
        {
            sleep(1);
        }
    }
    setPowerAdjustBatteryManipC(DEG_MANIP_C_AFTER_POW, DEG_MANIP_C_VOLTAGE);
    MANIP_C_READY = true;
}

int DEG_MANIP_D_DEG;
short DEG_MANIP_D_START_POW;
short DEG_MANIP_D_AFTER_POW;
float DEG_MANIP_D_VOLTAGE;

task moveDegManipD()
{
    setPowerAdjustBatteryManipD(DEG_MANIP_D_START_POW, DEG_MANIP_D_VOLTAGE);
    int endDeg;
    if (DEG_MANIP_D_START_POW >= 0)
    {
        endDeg = nMotorEncoder[motorD] + DEG_MANIP_D_DEG;
        while (nMotorEncoder[motorD] < endDeg)
        {
            sleep(1);
        }
    }
    else
    {
        endDeg = nMotorEncoder[motorD] - DEG_MANIP_D_DEG;
        while (nMotorEncoder[motorD] > endDeg)
        {
            sleep(1);
        }
    }
    setPowerAdjustBatteryManipD(DEG_MANIP_D_AFTER_POW, DEG_MANIP_D_VOLTAGE);
    MANIP_D_READY = true;
}

bool *setTimeManipC(int time, short powStart, short powAfter, float voltage = 8)
{
    stopTask(moveTimeManipC);
    stopTask(moveDegManipC);
    TIME_MANIP_C_START_POW = powStart;
    TIME_MANIP_C_AFTER_POW = powAfter;
    TIME_MANIP_C_VOLTAGE = voltage;
    TIME_MANIP_C_TIME = time;
    MANIP_C_READY = false;
    startTask(moveTimeManipC);
    return &MANIP_C_READY;
}

bool *setTimeManipD(int time, short powStart, short powAfter, float voltage = 8)
{
    stopTask(moveTimeManipD);
    stopTask(moveDegManipD);
    TIME_MANIP_D_START_POW = powStart;
    TIME_MANIP_D_AFTER_POW = powAfter;
    TIME_MANIP_D_VOLTAGE = voltage;
    TIME_MANIP_D_TIME = time;
    MANIP_D_READY = false;
    startTask(moveTimeManipD);
    return &MANIP_D_READY;
}

bool *setDegManipC(int deg, short powStart, short powAfter, float voltage = 8)
{
    stopTask(moveDegManipC);
    stopTask(moveTimeManipC);
    DEG_MANIP_C_DEG = deg;
    DEG_MANIP_C_START_POW = powStart;
    DEG_MANIP_C_AFTER_POW = powAfter;
    DEG_MANIP_C_VOLTAGE = voltage;
    MANIP_C_READY = false;
    startTask(moveDegManipC);
    return &MANIP_C_READY;
}

bool *setDegManipD(int deg, short powStart, short powAfter, float voltage = 8)
{
    stopTask(moveDegManipD);
    stopTask(moveTimeManipD);
    DEG_MANIP_D_DEG = deg;
    DEG_MANIP_D_START_POW = powStart;
    DEG_MANIP_D_AFTER_POW = powAfter;
    DEG_MANIP_D_VOLTAGE = voltage;
    MANIP_D_READY = false;
    startTask(moveDegManipD);
    return &MANIP_D_READY;
}

typedef struct {
    int takeFromLineCube;
    int close;
    int goOverTwoCubesOnLine;
} ConstsManipC;

typedef struct {
    int readCube;
    int takeCube;
    int put1Cube;
    int land1Cube;
    int prepareToTakeFromLine;
    int goOverCubes;
    int goOverTwoCubes;
} ConstsManipD;

ConstsManipC constsManipC;
ConstsManipD constsManipD;

bool IS_MANIPS_READY = false;

task initManip() {
    setPowerAdjustBatteryManipC(-40, 8);
    setPowerAdjustBatteryManipD(40, 8);
    sleep(400);
    setMotorBrakeMode(motorC, motorBrake);
    setMotorBrakeMode(motorD, motorBrake);
    motor[motorC] = 0;
    motor[motorD] = 0;
    sleep(300);

    nMotorEncoder[motorC] = 0;
    nMotorEncoder[motorD] = 0;

    setDegManipD(98, -75, -15);
    waitForManipD();
    sleep(500);
    // consts

    constsManipC.close = 300;
    constsManipC.takeFromLineCube = 269;
    constsManipC.goOverTwoCubesOnLine = 225;

    constsManipD.readCube = -185;
    constsManipD.takeCube = -134;
    constsManipD.put1Cube = -100;
    constsManipD.land1Cube = 52;
    constsManipD.prepareToTakeFromLine = -125;
    constsManipD.goOverCubes = -102;
    constsManipD.goOverTwoCubes = -95;

    IS_MANIPS_READY = true;
}

void waitInitManip() {
    while (!IS_MANIPS_READY) {
        sleep(100);
    }
}

void runMot(short mot)
{
    int pow = 0;
    bool pressedUp = false;
    bool pressedDown = false;
    while (getButtonPress(buttonEnter) == false)
    {
        if (getButtonPress(buttonLeft))
            motor[mot] = -1 * pow;
        else if (getButtonPress(buttonRight))
            motor[mot] = pow;
        else
            motor[mot] = 0;

        if (getButtonPress(buttonUp))
            pressedUp = true;
        else if (getButtonPress(buttonDown))
            pressedDown = true;

        if (getButtonPress(buttonUp) == false && pressedUp == true)
        {
            pressedUp = false;
            pow++;
        }
        else if (getButtonPress(buttonDown) == false && pressedDown == true)
        {
            pressedDown = false;
            pow--;
        }
        eraseDisplay();
        displayTextLine(1, "Pow: %d", pow);
        sleep(100);
    }
}