typedef struct {
    tMotor nDeviceIndex;
    float maxDown;
    float maxUp;
    float maxUpWithoutShip;
    float upForDrop;
    float maxV;
    float targetPos;
    float upForTakeFromShip;
} tGrabberPositionC;

typedef struct {
    tMotor nDeviceIndex;
    float close;
    float openMax;
    float openMin;
    float maxV;
    float targetPos;
} tGrabberPositionD;

tGrabberPositionC grabberC;
tGrabberPositionD grabberD;

bool WORKING_GRABBER_C = false;
bool WORKING_GRABBER_D = false;

task initGrabber() {
    motor[motorC] = 100;
    motor[motorD] = -100;
    sleep(100);

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
    float ce, cee, cP, cD, cU;
    float cisum = 0;
    float ckp = 2;
    float ckd = 6;
    float cki = 0.004;
    cee = 0;
    float ctt = nPgmTime;
    while (nPgmTime - ctt < 5000) {
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
    WORKING_GRABBER_C = false;
    stopTask(thr_changePosGrabberC);
}

task thr_changePosGrabberD() {
    float de, dee, dP, dD, dU;
    float disum = 0;
    float dkp = 2;
    float dkd = 6;
    float dki = 0.004;
    dee = 0;
    float dtt = nPgmTime;
    while (nPgmTime - dtt < 5000) {
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
    WORKING_GRABBER_D = false;
    stopTask(thr_changePosGrabberD);
}
void changePosGrabberC(float v, float pos) {
    grabberC.maxV = v;
    grabberC.targetPos = pos;
    WORKING_GRABBER_C = true;
    startTask(thr_changePosGrabberC, kLowPriority);
}

void waitGrabberC() {
    while (WORKING_GRABBER_C) {
        sleep(1);
    }
}

void changePosGrabberD(float v, float pos) {
    grabberD.maxV = v;
    grabberD.targetPos = pos;
    WORKING_GRABBER_D = true;
    startTask(thr_changePosGrabberD, kLowPriority);
}

void waitGrabberD() {
    while (WORKING_GRABBER_D) {
        sleep(1);
    }
}