void setMotorA(float speed) {
    // inputted speed will be assumed with voltage 8V, we need to take current voltage and adapt the given speed
    motor[motorA] = speed * 8 / getBatteryVoltage();
}

void setMotorB(float speed) {
    motor[motorB] = speed * 8 / getBatteryVoltage();
}