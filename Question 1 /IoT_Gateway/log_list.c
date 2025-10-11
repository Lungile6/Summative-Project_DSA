#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "log_list.h"

// Initialize the log list
void initializeLogList(LogList* logList, int maxSize) {
    logList->head = NULL;
    logList->tail = NULL;
    logList->current = NULL;
    logList->size = 0;
    logList->maxSize = maxSize;
    logList->liveStreaming = 0;  // Initialize live streaming flag
    pthread_mutex_init(&logList->lock, NULL);
}

// Add a new log entry to the list
void addLogEntry(LogList* logList, SensorData newData) {
    pthread_mutex_lock(&logList->lock);
    
    LogEntry* newEntry = malloc(sizeof(LogEntry));
    newEntry->data = newData;
    newEntry->next = NULL;

    if (logList->size == 0) {
        newEntry->prev = NULL;
        logList->head = newEntry;
        logList->tail = newEntry;
    } else {
        newEntry->prev = logList->tail;
        logList->tail->next = newEntry;
        logList->tail = newEntry;
    }

    logList->size++;

    // Discard the oldest log if the maximum size is exceeded
    if (logList->size > logList->maxSize) {
        LogEntry* toDelete = logList->head;
        logList->head = logList->head->next;
        logList->head->prev = NULL;
        free(toDelete);
        logList->size--;
    }

    pthread_mutex_unlock(&logList->lock);
}

// Navigate to the next log entry
void navigateNext(LogList* logList) {
    pthread_mutex_lock(&logList->lock);
    if (logList->current && logList->current->next) {
        logList->current = logList->current->next;
    } else {
        logList->current = logList->head; // Loop back to the head
    }
    pthread_mutex_unlock(&logList->lock);
}

// Navigate to the previous log entry
void navigatePrevious(LogList* logList) {
    pthread_mutex_lock(&logList->lock);
    if (logList->current && logList->current->prev) {
        logList->current = logList->current->prev;
    } else {
        logList->current = logList->tail; // Loop back to the tail
    }
    pthread_mutex_unlock(&logList->lock);
}

// Start live streaming of sensor data
void* liveStreamingThread(void* arg) {
    LogList* logList = (LogList*)arg;
    while (logList->liveStreaming) {
        SensorData newData = {rand() % 30 + 20, rand() % 100, 1013.0, 0.5}; // Simulate sensor data
        addLogEntry(logList, newData);
        printf("New log entry added: Temperature = %.1f, Humidity = %.1f\n", newData.temperature, newData.humidity);
        sleep(1);  // Simulate delay between readings
    }
    return NULL;
}

// Start live streaming of sensor data
void startLiveStreaming(LogList* logList) {
    if (!logList->liveStreaming) {
        logList->liveStreaming = 1;
        pthread_t thread;
        pthread_create(&thread, NULL, liveStreamingThread, logList);
        pthread_detach(thread); // Detach thread to run independently
    }
}

// Stop live streaming of sensor data
void stopLiveStreaming(LogList* logList) {
    logList->liveStreaming = 0; // Set flag to stop the streaming
}

// Gracefully terminate the system and save the logs
void terminateSystem(LogList* logList) {
    pthread_mutex_lock(&logList->lock);
    // Logic to save the current logs to persistent storage
    pthread_mutex_unlock(&logList->lock);

    // Clean up all log entries
    while (logList->head) {
        LogEntry* toDelete = logList->head;
        logList->head = logList->head->next;
        free(toDelete);
    }
    pthread_mutex_destroy(&logList->lock);
}

// Clear all logs from the log list
void clearLogs(LogList* logList) {
    pthread_mutex_lock(&logList->lock);
    while (logList->head) {
        LogEntry* toDelete = logList->head;
        logList->head = logList->head->next;
        free(toDelete);
    }
    logList->tail = NULL;
    logList->current = NULL;
    logList->size = 0;
    pthread_mutex_unlock(&logList->lock);
}
