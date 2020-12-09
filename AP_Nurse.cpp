#include "AP_Nurse.h"

PCF8591 extender(0, false);

/** AP_nurse methods definitions
 */
AP_Nurse::AP_Nurse(){
    //I/O init
    #ifdef PIR_ENABLE
    pinMode(PIR_PIN, INPUT);
    #endif

    #ifdef NOISE_ENABLE
    pinMode(NOISE_PIN, INPUT);
    #endif

    //I2C init
    Wire.begin();

    bme.begin();

    //get program start time
    //this -> ap_node.lastEcheck = millis();
    //Wire.pins(I2C_SDA, I2C_SCL);
}

uint8_t AP_Nurse::getLastAlert(){
    return (this -> ap_node.lastAlert);
}

bool AP_Nurse::getLastMotion(){
    return (this -> ap_node.lastMotion);
}

uint8_t AP_Nurse::getLastNoise(){
    return (this -> ap_node.lastNoise);
}

uint8_t AP_Nurse::getLastSmoke(){
    return (this -> ap_node.lastVal[1]);
}

uint8_t AP_Nurse::getLastGas(){
    return (this -> ap_node.lastVal[2]);
}

uint8_t AP_Nurse::getLastLight(){
    return (this -> ap_node.lastVal[3]);
}

uint8_t AP_Nurse::getLastPressure(){
    return (this -> ap_node.lastVal[4]);
}

float AP_Nurse::getLastTemperature(){
    return (this -> ap_node.lastTemperature);
}

float AP_Nurse::getLastHumidity(){
    return (this -> ap_node.lastHumidity);
}

float AP_Nurse::getLastAPressure(){
    return (this -> ap_node.lastAPressure);
}

void AP_Nurse::printData(){
    Serial.println();
  
    #ifdef PIR_ENABLE
    Serial.printf("Motion:      %d\r\n", this -> getLastMotion());
    #endif

    #ifdef BME_ENABLE
    Serial.printf("Temperature: %.1f\r\n", this -> getLastTemperature());
    Serial.printf("Humidity:    %.1f\r\n", this -> getLastHumidity());
    Serial.printf("APressure:   %.1f\r\n", this -> getLastAPressure());
    #endif

    //Serial.printf("Button:      %d\r\n", digitalRead(BUTTON_PIN));
}

status_t AP_Nurse::checkMotion(){
    this -> ap_node.lastMotion = digitalRead(PIR_PIN);
    if(this -> ap_node.lastMotion){
        this -> ap_node.lastAlert |= MOTION_ALERT;
        #ifdef DOOR
        if ((this -> ap_node.isTimer_a) & this -> ap_node.isMotionCheck_n) {
            this -> disableTimer();
        } else if (this -> ap_node.isMotionCheck_n) {
            this -> startTimer();
        }
        this -> ap_node.isMotionCheck_n = false;
        #endif
        return MOTION_ALERT;
    }
    
    this -> ap_node.lastAlert &= (0xff - MOTION_ALERT);
    this -> ap_node.isMotionCheck_n = true;
    return STATUS_OK;
}

status_t AP_Nurse::checkBme() {
    int ret = STATUS_OK;
    if ((this -> ap_node.lastTemperature = bme.readTemperature()) <= this -> ap_th.tempTH) {
        ret |= TEMPERATURE_ALERT;
        this -> ap_node.lastAlert |= TEMPERATURE_ALERT;
    } else {
        this -> ap_node.lastAlert &= (0xff - TEMPERATURE_ALERT);
    }
    this -> ap_node.lastHumidity = bme.readHumidity();
    this -> ap_node.lastAPressure = bme.readPressure();

    return (status_t)ret;
}

status_t AP_Nurse::checkGas() {
    int ret = STATUS_OK;
    if (bme.readGas() >= this -> ap_th.gasTH) {
        ret |= GAS_ALERT;
        this -> ap_node.lastAlert |= GAS_ALERT|SMOKE_ALERT;
    } else {
        this -> ap_node.lastAlert &= (0xff - (GAS_ALERT|SMOKE_ALERT));
    }

    return (status_t)ret;
}//gas

status_t AP_Nurse::checkLight() {
    int ret = STATUS_OK;
    if (analogRead(LIGHT_PIN) >= this -> ap_th.lightTH) {
        ret |= LIGHT_ALERT;
        this -> ap_node.lastAlert |= LIGHT_ALERT;
    } else {
        this -> ap_node.lastAlert &= (0xff - LIGHT_ALERT);
    }

    return (status_t)ret;
}//light

status_t AP_Nurse::checkFSR() {
    int ret = STATUS_OK;
    if (analogRead(FSR_PIN) >= this -> ap_th.pressureTH) {
        ret |= PRESSURE_ALERT;
        this -> ap_node.lastAlert |= PRESSURE_ALERT;
    } else {
        this -> ap_node.lastAlert &= (0xff - PRESSURE_ALERT);
    }

    return (status_t)ret;
}//pressure/fsr

void AP_Nurse::startTimer() {
    this -> ap_node.isTimer_a = true;
    this -> ap_node.timerStart = millis();
}

void AP_Nurse::checkTimer() {
    if (this -> ap_node.isTimer_a && ((millis() - this -> ap_node.timerStart) >= (STUCK_TIMER_DELAY * 1000))) {
        this -> ap_node.lastAlert |= STUCK_ALERT;
    }
}

void AP_Nurse::disableTimer() {
    this -> ap_node.isTimer_a = false;
}


void AP_Nurse::timerISR(void *pArg){
    this -> ap_node.lastAlert |= STUCK_ALERT;
}

void AP_Nurse::clearAlert(){
    this -> ap_node.lastAlert = STATUS_OK;
}

/** AP_nurse_Universal methods definitions
 */
uint8_t AP_Nurse_Universal::update(){
    #ifdef PIR_ENABLE
    if (this -> ap_config.enable_pir) {
        this -> checkMotion();
    }
    #endif

    #ifdef DOOR
    this -> checkTimer();
    #endif

    #ifdef BME_ENABLE
    if (this -> ap_config.enable_bme) {
        //this -> checkBme();
        delay(1);
    }
    #endif

    if (this -> ap_config.enable_light) {
        this -> checkLight();
    }

    if (this -> ap_config.enable_fsr) {
        this -> checkFSR();
    }

    if (this -> ap_config.enable_smoke) {
        this -> checkGas();
    }

    return this -> ap_node.lastAlert;
}