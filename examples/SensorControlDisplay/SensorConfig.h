// SensorConfig.h
#pragma once

// Define sensor types
#define SENSOR_TYPE_ANALOG 0 // Analog sensor

#define ACTIVE_SENSOR_TYPE SENSOR_TYPE_ANALOG // Active sensor type

const char* const SENSOR_LABEL = "Moisture";   // Label for the sensor reading
const char* const SENSOR_KEY = "M";   // Short key for the sensor reading

#define READING_INTERVAL 500      // Interval between sensor readings (milliseconds)

#define SENSOR_PIN A0

// #define DEFAULT_CALIBRATION_LOW 0
// #define DEFAULT_CALIBRATION_HIGH 1024

// Defaults for DFRobot soil moisture sensor
#define DEFAULT_CALIBRATION_LOW 476
#define DEFAULT_CALIBRATION_HIGH 0


