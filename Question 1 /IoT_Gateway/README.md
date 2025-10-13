## IoT_Gateway — Sensor Log List (Question 1)

### Overview
This program simulates an IoT gateway that maintains a rolling list of sensor readings. It supports:

- **Live streaming** of synthetic sensor data on a background thread
- **Bounded log storage** using a doubly linked list with automatic eviction of oldest entries
- **Cursor-based navigation** through stored logs
- **Clearing logs** and **graceful termination**

Core types and functionality live in `log_entry.h`, `log_list.h`, and `log_list.c`, with the CLI loop in `main.c`.

### Files
- `main.c`: CLI loop for user commands and interaction
- `log_entry.h`: `SensorData` and `LogEntry` type definitions
- `log_list.h`: `LogList` structure and public API
- `log_list.c`: Implementation of list management, navigation, live streaming, and cleanup

### Build
Requires a C compiler with POSIX threads. Tested with `gcc`.

```bash
cd "Question 1 /IoT_Gateway"
gcc -std=c11 -Wall -Wextra -pthread -o IoT_Gateway main.c log_list.c
```

Alternatively, you may already have a prebuilt executable named `IoT_Gateway` in this folder.

### Run
```bash
./IoT_Gateway
```

### Controls
- `y`: Start live streaming (adds a new synthetic reading ~once per second)
- `z`: Stop live streaming
- `n`: Move to the next log entry (wraps to head if at end)
- `p`: Move to the previous log entry (wraps to tail if at start)
- `c`: Clear all logs
- `s`: Terminate the system and exit

When navigating, the program prints the current entry as:
```
Current log entry: Temperature = <temp>, Humidity = <humidity>
```

### Implementation Notes
- The log list is **bounded** by `maxSize` (initialized to 20 in `main.c`). When the bound is exceeded, the oldest entry is evicted.
- Live streaming runs on a **detached pthread** and is guarded by a mutex in `LogList` for thread safety.
- `terminateSystem` performs cleanup of all nodes and destroys the mutex. The placeholder comment for persistence is where you could add file/database saving if needed.
- Synthetic readings are generated with simple random values for temperature/humidity and constants for other fields.

### Example Session
```
Enter command (n: next, p: previous, y: start live, z: stop live, s: terminate, c: clear): y
New log entry added: Temperature = 24.0, Humidity = 65.0
New log entry added: Temperature = 30.0, Humidity = 50.0
... (streaming) ...
z
Live streaming stopped.
n
Current log entry: Temperature = 30.0, Humidity = 50.0
p
Current log entry: Temperature = 24.0, Humidity = 65.0
s
System terminated.
```

### Troubleshooting
- On macOS or Linux, ensure you include `-pthread` when building.
- If you see no output for navigation, ensure at least one entry exists (start streaming with `y` first).


