#include "define_vals.c"

void defineMain(){
    // action which are defined by define variables
    #if CALIBRATION == 1
    myCalibration();
    #endif
}