#ifndef LOG_LIST_H
#define LOG_LIST_H

#include <pthread.h>
#include "log_entry.h"

typedef struct {
    LogEntry* head;          // Pointer to the head of the log list
    LogEntry* tail;          // Pointer to the tail of the log list
    LogEntry* current;       // Pointer to the current log entry for navigation
    int size;                // Current number of logs in the list
    int maxSize;             // Maximum size of the log list
    pthread_mutex_t lock;    // Mutex for thread safety
    int liveStreaming;        // Flag for live streaming state
} LogList;

// Function prototypes
void initializeLogList(LogList* logList, int maxSize);
void addLogEntry(LogList* logList, SensorData newData);
void navigateNext(LogList* logList);
void navigatePrevious(LogList* logList);
void startLiveStreaming(LogList* logList);
void stopLiveStreaming(LogList* logList);
void terminateSystem(LogList* logList);
void clearLogs(LogList* logList);

#endif // LOG_LIST_H
