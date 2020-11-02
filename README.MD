# KlimaLogLib
A data manipulation library/abstraction for KlimaLogg Pro devices. The library wraps a bunch of parsing, reading and manipulation features for work with the `0_history.dat` and `0_alarmevents.dat` files.

### Usage:
The library provides two structures
```c
// Singular sensor data
struct klg_sensordata {
    uint8_t t_enable;  // Flag raised if the temperature reading is out of bounds
    uint8_t h_enable;  // Flag raised if the humidity reading is out of bounds
    uint8_t alarm;     // Flag raised if an alarm event has been triggered 
    float temp;        // Measured temperature in celsius
    float humid;       // Measured humidity in % RH
};
```
and 
```c
// An entire measurement, containing readings from all sensors
struct klg_measurement{
    struct tm datetime;            // A C tm datetime object with exact measurement time
    struct klg_sensordata sensor0; // Singular sensor data for sensor 0
    struct klg_sensordata sensor1; // Singular sensor data for sensor 1
    struct klg_sensordata sensor2; // Singular sensor data for sensor 2
    struct klg_sensordata sensor3; // Singular sensor data for sensor 3
    struct klg_sensordata sensor4; // Singular sensor data for sensor 4
    struct klg_sensordata sensor5; // Singular sensor data for sensor 5
    struct klg_sensordata sensor6; // Singular sensor data for sensor 6
    struct klg_sensordata sensor7; // Singular sensor data for sensor 7
    struct klg_sensordata sensor8; // Singular sensor data for sensor 8
};
```

It also defines the following
```c
#define KLG_INVALID_TEMP    0x42A23333         // Value returned by sensor when it's reading is invalid
#define KLG_INVALID_HUMID   0x42DC0000         // Value returned by sensor when it's reading is invalid
#define KLG_UNIX_T_JULIAN   210866803200000000 // UNIX time as a julian timestamp in micro seconds
#define KLG_MEASURE_SIZE    84                 // Amount of bytes a measurement packet is
```

Read `KLG_MEASURE_SIZE` amount of bytes and place them in a buffer:
```c
uint8_t *buffer = malloc(KLG_MEASURE_SIZE);
size_t read = fread(buffer, 1, KLG_MEASURE_SIZE, file);
```

Create a `klg_measurement` structure and parse the buffer into it:
```c
struct klg_measurement measurement;
klg_parsebuffer(&measurement, buffer, sizeof(buffer));
```

`struct klg_measurement measurement` now contains all data for the specific measurement buffer.
Access it like so:

Read temperature:
```c
// Make sure the temperature reading is not out of bounds
if (measurement.sensor5.t_enable) {
    // Read the temperature of that sensor at that time
    float myTemperature = measurement.sensor5.temp;
    printf("Sensor 5 temperature: %fC\n", myTemperature);
}
```

Read humidity:
```c
// Make sure the humidity reading is not out of bounds
if (measurement.sensor2.h_enable) {
    // Read the humidity of that sensor at that time
    float myHumidity = measurement.sensor2.humid;
    printf("Sensor 2 humidity: %f% RH\n", myHumidity);
}
```

Read measurement time:
```c
struct tm myMeasurementTime = measurement.datetime;
// Print out the formatted time (or format in any other way you want. Refer to time.h)
printf("Measured at: %s\n", asctime(myMeasurementTime));
```

Check for an alarm event:
```c
// Check if sensor has raised an alarm event
if (measurement.sensor3.alarm) {
    printf("Sensor 3 has raised an alarm!\n");
}
```