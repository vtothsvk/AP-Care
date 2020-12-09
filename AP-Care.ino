#include <M5StickC.h>    
#include "AP_Nurse.h"

//uncommenting next line enables buzzer
//#define _BUZZER

//uncommenting the next line enables debug printout
//#define _DEBUG
#ifdef _DEBUG
#define loopDelay   200
#endif

//uncommenting the next line enables alert level debug printout
//#define _LEVEL

/** Alert control directives
 */
#define muteDuration    2000

/** Encoder transmission enable pin control directives
 */
#define pWindow     5000//ms pair window
#define pWidth      100//ms TE pulse width
#define pInterval   5000//ms periodic RF message advertisement interval

void AP_loop(int alert);
int Alert(level_t enable);
level_t alertLevel(int alert);

void pulse();
void periodicPulse();

/** AP-Nurse Home config initialisation
 */
ap_config_t config_day = { NOISE_TH, SMOKE_TH, GAS_TH, LIGHT_TH, PRESSURE_TH, TEMP_TH, HUMIDITY_TH, PIR_E, NOISE_E, BME_E, EXTENDER_E };
ap_config_t config_night = { NOISE_TH_N, SMOKE_TH_N, GAS_TH_N, LIGHT_TH_N, PRESSURE_TH_N, TEMP_TH_N, HUMIDITY_TH_N, PIR_E_N, NOISE_E_N, BME_E_N, EXTENDER_E_N };

/** AP-Nurse Home object and global variable initialisation
 */
static AP_Nurse_Universal ap_node(config_day);//ap nurse control interface
static AP_Nurse_Universal ap_node_night(config_night);//ap nurse night control interface
volatile bool muted = false;
volatile bool wasAlert = false;
volatile long muteStart = 0;
volatile long lastPulse = 0;

void setup() {
    M5.begin();
    //Serial comm setup
    Serial.begin(115200);
    Serial.println("AP Nurse Universal V 1.0 Booted Succesfully ^^");
    Serial.println("Pairing...");
    Serial.println("End of pairing window...");
}//setup

void loop() {
    int alert = 0;
    bool d_n = false;

    if (d_n) {//sensor data update, basedd on D/N setting
        alert = ap_node_night.update();
    } else {
        alert = ap_node.update();
    }//if (d_n)
    
    AP_loop(alert);//ap node loop body

    #ifdef _DEBUG
    delay(loopDelay);
    
    if (d_n){
        ap_node_night.printData();
    } else {
        ap_node.printData();
    }
    #endif
}//loop

//Ap node main loop bodys
void AP_loop(int alert) {
    //Alert debug
    if (0 < alert) {
        char buffer[9];
        sprintf(&buffer[0], BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(alert));
        Serial.print("STATUS: ");
        Serial.println(buffer);  
    }else{
        Serial.println(alert); //debug alert
    }//if (0 < alert)
    
    //Alert handling
    if (alert&&(!muted)) {
        level_t condition = alertLevel(alert);
        Alert(condition);
        muted = true;
        muteStart = millis();
    }//if (alert&&(!muted))
    if (muted&&((millis() - muteStart) >= muteDuration)) {
        muted = false;
        Alert(NO_ALERT);
    }//if (muted&&((millis() - muteStart) >= muteDuration))
}//AP_loop

//Alert handler
int Alert(level_t enable) {
    #ifdef _LEVEL
    Serial.printf("a level: %d\r\n", enable);
    #endif

    if (enable) {

        if (enable & CRITICAL) { //in case of a critical condition
            M5.Lcd.fillScreen(RED);
            return 2;
        }

        #ifdef _BUZZER
        digitalWrite(BUZZER_PIN, LOW);
        #endif

        M5.Lcd.fillScreen(YELLOW);
        wasAlert = true;
        return 1;
    }//if (enable)

    wasAlert = false;

    #ifdef _BUZZER
    digitalWrite(BUZZER_PIN, HIGH);
    #endif

    M5.Lcd.fillScreen(GREEN);

    return 0;
}//Alert

level_t alertLevel(int alert) {

    #ifdef BED
    if (alert & (MOTION_ALERT | SMOKE_ALERT | GAS_ALERT | NOISE_ALERT)) {
        return CRITICAL;
    } else if ((alert & LIGHT_ALERT) && (alert & MOTION_ALERT)) {
        return ABNORMAL;
    } else {
        return NO_ALERT;
    }//(alert & (MOTION_ALERT | SMOKE_ALERT | GAS_ALERT | NOISE_ALERT))
    #endif

    #ifdef DOOR
    if (alert & STUCK_ALERT) {
        return CRITICAL;
    } else if (alert & MOTION_ALERT) {
        return ABNORMAL;
    } else {
        return NO_ALERT;
    }//if (alert & STUCK_ALERT)
    #endif

    #ifdef HALLWAY
    if (alert & MOTION_ALERT) {
        return CRITICAL;
    } else if (alert & NOISE_ALERT) {
        return ABNORMAL;
    } else {
        return NO_ALERT;
    }//if (alert & MOTION_ALERT) 
    #endif

    #ifdef KITCHEN
    if (alert & (0xffff - LIGHT_ALERT)) {
        return CRITICAL;
    } else if (alert & LIGHT_ALERT) {
        return ABNORMAL;
    } else {
        return NO_ALERT;
    }//if (alert & (0xffff - LIGHT_ALERT)) 
    #endif
}
