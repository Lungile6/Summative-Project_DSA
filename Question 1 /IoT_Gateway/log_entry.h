#ifndef LOG_ENTRY_H
#define LOG_ENTRY_H

typedef struct SensorData {
    float temperature;
    float humidity;
    float pressure;
    float vibration;
} SensorData;

typedef struct LogEntry {
    SensorData data;          // Holds the sensor readings
    struct LogEntry* next;    // Pointer to the next log entry
    struct LogEntry* prev;    // Pointer to the previous log entry
} LogEntry;

#endif // LOG_ENTRY_H
