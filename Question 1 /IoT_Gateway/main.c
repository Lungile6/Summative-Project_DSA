#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "log_list.h"

void printCurrentLog(LogList* logList) {
    if (logList->current) {
        printf("Current log entry: Temperature = %.1f, Humidity = %.1f\n", logList->current->data.temperature, logList->current->data.humidity);
    } else {
        printf("No current log entry available.\n");
    }
}

int main() {
    LogList logList;
    initializeLogList(&logList, 20); // Initialize log list with a max size of 20

    char command;
    logList.current = logList.head; // Start at the first log

    while (1) {
        printf("Enter command (n: next, p: previous, y: start live, z: stop live, s: terminate, c: clear): ");
        scanf(" %c", &command); // Note the space before %c to consume any newline

        switch (command) {
            case 'n':
                navigateNext(&logList);
                printCurrentLog(&logList);
                break;
            case 'p':
                navigatePrevious(&logList);
                printCurrentLog(&logList);
                break;
            case 'y':
                startLiveStreaming(&logList);
                break;
            case 'z':
                stopLiveStreaming(&logList);
                printf("Live streaming stopped.\n");
                break;
            case 's':
                terminateSystem(&logList);
                printf("System terminated.\n");
                return 0;
            case 'c':
                clearLogs(&logList);
                printf("All logs cleared.\n");
                break;
            default:
                printf("Invalid command.\n");
                break;
        }
    }

    return 0;
}
