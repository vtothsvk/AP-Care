#ifndef AP_CONFIG_H
#define AP_CONFIG_H

#include "AP_Nurse_types.h"

/** AP-Nurse Home version selection directives
 * 
 *  @note select only one
 */
#define BED
//#define DOOR
//#define HALLWAY
//#define KITCHEN

/** Threshold and sensor enable directives 
 *
 *  @note each uint8_t level represents one 255th of the reference voltage (eg. a threshold of 100 @ 3.3V represents 1.29V)
 *  @note each float level represets a float falue
 */
#ifdef BED
//Day uint8_t
#define NOISE_TH        50
#define SMOKE_TH        100
#define GAS_TH          60
#define LIGHT_TH        80
#define PRESSURE_TH     80
//Day float
#define TEMP_TH         18
#define HUMIDITY_TH     50
//Day sensor enable
#define PIR_E           false
#define NOISE_E         true
#define BME_E           true
#define EXTENDER_E      false

//Night uint8_t
#define NOISE_TH_N      50
#define SMOKE_TH_N      100
#define GAS_TH_N        60
#define LIGHT_TH_N      80
#define PRESSURE_TH_N   80
//Night float
#define TEMP_TH_N       18
#define HUMIDITY_TH_N   50
//Night sensor enable
#define PIR_E_N         true
#define NOISE_E_N       true
#define BME_E_N         true
#define EXTENDER_E_N    true
#endif//BED

#ifdef DOOR
//Day uint8_t
#define NOISE_TH        50
#define SMOKE_TH        100
#define GAS_TH          60
#define LIGHT_TH        80
#define PRESSURE_TH     80
//Day float
#define TEMP_TH         18
#define HUMIDITY_TH     50
//Day sensor enable
#define PIR_E           true
#define NOISE_E         false
#define BME_E           false
#define EXTENDER_E      false

//Night uint8_t
#define NOISE_TH_N      50
#define SMOKE_TH_N      100
#define GAS_TH_N        60
#define LIGHT_TH_N      80
#define PRESSURE_TH_N   80
//Night float
#define TEMP_TH_N       18
#define HUMIDITY_TH_N   50
//Night sensor enable
#define PIR_E_N         true
#define NOISE_E_N       false
#define BME_E_N         false
#define EXTENDER_E_N    false
#endif//DOOR

#ifdef HALLWAY
//Day uint8_t
#define NOISE_TH        50
#define SMOKE_TH        100
#define GAS_TH          60
#define LIGHT_TH        80
#define PRESSURE_TH     80
//Day float
#define TEMP_TH         18
#define HUMIDITY_TH     50
//Day sensor enable
#define PIR_E           true
#define NOISE_E         false
#define BME_E           false
#define EXTENDER_E      false

//Night uint8_t
#define NOISE_TH_N      50
#define SMOKE_TH_N      100
#define GAS_TH_N        60
#define LIGHT_TH_N      80
#define PRESSURE_TH_N   80
//Night float
#define TEMP_TH_N       18
#define HUMIDITY_TH_N   50
//Night sensor enable
#define PIR_E_N         true
#define NOISE_E_N       false
#define BME_E_N         false
#define EXTENDER_E_N    false
#endif//HALLWAY

#ifdef KITCHEN
//Day uint8_t
#define NOISE_TH        50
#define SMOKE_TH        100
#define GAS_TH          60
#define LIGHT_TH        80
#define PRESSURE_TH     80
//Day float
#define TEMP_TH         18
#define HUMIDITY_TH     50
//Day sensor enable
#define PIR_E           true
#define NOISE_E         true
#define BME_E           false
#define EXTENDER_E      true

//Night uint8_t
#define NOISE_TH_N      50
#define SMOKE_TH_N      100
#define GAS_TH_N        60
#define LIGHT_TH_N      80
#define PRESSURE_TH_N   80
//Night float
#define TEMP_TH_N       18
#define HUMIDITY_TH_N   50
//Night sensor enable
#define PIR_E_N         true
#define NOISE_E_N       true
#define BME_E_N         false
#define EXTENDER_E_N    true
#endif//KITCHEN

/** AP-Nurse Home DOOR version config
 */
#define STUCK_TIMER_DELAY   5//s

#endif