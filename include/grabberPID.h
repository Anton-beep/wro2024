typedef struct {
    tMotor nDeviceIndex;
    float maxDown;
    float maxUp;
    float maxUpWithoutShip;
    float upForDrop;
    float maxV;
    float targetPos;
    float upForTakeFromShip;

    int opened;
    int closed;

    float stopWorkAt;
    bool keepWorking;
    bool idle;
} tGrabberPositionC;

typedef struct {
    tMotor nDeviceIndex;
    float close;
    float openMax;
    float openMin;
    float maxV;
    float targetPos;

    int readyFor2;
    int readyFor4;
    int startSuspension;
    int suspensionForStartBridge;
    int suspensionMovingBridge;
    int suspensionBridgePeak;
    int suspensionMovingFromPeak;
    int suspensionGoBackFromBridge;
    int suspenionPeakGoBack;
    int suspenionGoBackAfterPeak;
    int endSuspension;

    float stopWorkAt;
    bool keepWorking;
    bool idle;
} tGrabberPositionD;

tGrabberPositionC grabberC;
tGrabberPositionD grabberD;

task initGrabber() {
    motor[motorC] = -30;
    motor[motorD] = 40;
    sleep(500);

    setMotorBrakeMode(motorC, motorCoast);
    setMotorBrakeMode(motorD, motorCoast);
    sleep(600);
    setMotorBrakeMode(motorC, motorBrake);
    setMotorBrakeMode(motorD, motorBrake);
    motor[motorC] = 0;
    motor[motorD] = 0;
    nMotorEncoder[motorC] = 0;
    nMotorEncoder[motorD] = 0;

    grabberC.maxUp = 0;
    grabberC.maxUpWithoutShip = -390;
    grabberC.maxDown = -820;
    grabberC.upForDrop = -670;
    grabberC.upForTakeFromShip = -690;

    grabberC.opened = 0;
    grabberC.closed = 373;

    grabberD.close = 0;
    grabberD.openMin = 230;
    grabberD.openMax = 480;

    grabberD.readyFor2 = 0;
    grabberD.readyFor4 = -45;
    grabberD.startSuspension = -110;
    grabberD.suspensionForStartBridge = -90;
    grabberD.suspensionMovingBridge = -85;
    grabberD.suspensionBridgePeak = -100;
    grabberD.suspensionMovingFromPeak = -110;
    grabberD.suspensionGoBackFromBridge = -141;
    grabberD.suspenionPeakGoBack = -80;
    grabberD.suspenionGoBackAfterPeak = -80;
    grabberD.endSuspension = -141;
    stopTask(initGrabber);
}

task initGrabber_t() {
    motor[motorC] = 100;
    motor[motorD] = -100;
    sleep(500);

    setMotorBrakeMode(motorC, motorBrake);
    setMotorBrakeMode(motorD, motorBrake);
    motor[motorC] = 0;
    motor[motorD] = 0;
    nMotorEncoder[motorC] = 0;
    nMotorEncoder[motorD] = 0;

    grabberC.maxUp = 0;
    grabberC.maxUpWithoutShip = -390;
    grabberC.maxDown = -820;
    grabberC.upForDrop = -670;
    grabberC.upForTakeFromShip = -690;

    grabberD.close = 0;
    grabberD.openMin = 230;
    grabberD.openMax = 480;
    stopTask(initGrabber);
}

task thr_changePosGrabberC() {
    grabberC.idle = false;
    float ce, cee, cP, cD, cU;
    float cisum = 0;
    float ckp = 2;
    float ckd = 6;
    float cki = 0.004;
    cee = 0;
    float ctt = nPgmTime;
    while (nPgmTime < grabberC.stopWorkAt && grabberC.keepWorking) {
        ce = grabberC.targetPos - nMotorEncoder[motorC];

        if (ce == 0) {
            cisum = 0;
        } else if (ce > 0 && cee <= 0) {
            cisum = 0;
        } else if (ce < 0 && cee >= 0) {
            cisum = 0;
        }

        cisum += ce * cki;



        cP = ce * ckp;
        cD = (ce - cee) * ckd;
        cU = cP + cD + cisum;
        if (cU > grabberC.maxV) {
            cU = grabberC.maxV;
        } else if (cU < (-1) * grabberC.maxV) {
            cU = (-1) * grabberC.maxV;
        }
        motor[motorC] = cU;
        cee = ce;
        sleep(1);
    }
    setMotorBrakeMode(motorC, motorBrake);
    motor[motorC] = 0;
    grabberC.idle = true;
    stopTask(thr_changePosGrabberC);
}

task thr_changePosGrabberD() {
    grabberD.idle = false;
    float de, dee, dP, dD, dU;
    float disum = 0;
    float dkp = 2;
    float dkd = 6;
    float dki = 0.004;
    dee = 0;
    float dtt = nPgmTime;
    while (nPgmTime < grabberD.stopWorkAt && grabberD.keepWorking) {
        de = grabberD.targetPos - nMotorEncoder[motorD];
        if (de == 0) {
            disum = 0;
        } else if (de > 0 && dee <= 0) {
            disum = 0;
        } else if (de < 0 && dee >= 0) {
            disum = 0;
        }
        disum += de * dki;
        dP = de * dkp;
        dD = (de - dee) * dkd;
        dU = dP + dD + disum;
        if (dU > grabberD.maxV) {
            dU = grabberD.maxV;
        } else if (dU < (-1) * grabberD.maxV) {
            dU = (-1) * grabberD.maxV;
        }
        motor[motorD] = dU;
        dee = de;
        sleep(1);
    }
    if (grabberD.targetPos == grabberD.close) {
        motor[motorD] = -100;
    } else {
        setMotorBrakeMode(motorD, motorBrake);
        motor[motorD] = 0;
    }
    grabberD.idle = true;
    stopTask(thr_changePosGrabberD);
}
void changePosGrabberC(float v, float pos, float duration = 5000) {
    grabberC.maxV = v;
    grabberC.targetPos = pos;
    grabberC.stopWorkAt = nPgmTime + duration;
    grabberC.keepWorking = true;
    startTask(thr_changePosGrabberC, kLowPriority);
}

void changePosGrabberD(float v, float pos, float duration = 5000) {
    grabberD.maxV = v;
    grabberD.targetPos = pos;
    grabberD.stopWorkAt = nPgmTime + duration;
    grabberD.keepWorking = true;
    startTask(thr_changePosGrabberD, kLowPriority);
}

void stopGrabberC() {
    grabberC.keepWorking = false;
}

void stopGrabberD() {
    grabberD.keepWorking = false;
}

void waitGrabberC() {
    while (!grabberC.idle) {
        sleep(70);
    }
}

void waitGrabberD() {
    while (!grabberD.idle) {
        sleep(70);
    }
}