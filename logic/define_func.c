#include "define_vals.c"

void defineMain(){
    // action which are defined by define variables
    #if CALIBRATION == 1
    myCalibration();
    #elif CALIBRATE_SEN1_COLOR_DETECTION == 1
    waitInitManip();
    displayValues(&CDSensor1);
    #elif CALIBRATE_SEN2_COLOR_DETECTION == 1
    waitInitManip();
    displayValues(&CDSensor2);
    #elif CALIBRATE_SEN3_COLOR_DETECTION == 1
    waitInitManip();
    displayValues(&CDSensor3);
    #elif DETECT_FROM_LINE_SEN3 == 1
    waitInitManip();
    setDegManipD(constsManipD.takeCube, 50, 10);
    setDegManipC(constsManipC.takeFromLineCube, 20, 0);
    waitForManipC();
    waitForManipD();
    displayValues(&CDSensor3);
    #endif
}