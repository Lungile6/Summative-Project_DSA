## Device Mapping (Question 3)

A simple C program that models device-to-device communication using a directed graph. Each node represents a device ID and each edge represents a communication (data transfer) from one device to another. The program supports interactive queries and dynamic updates at runtime.

### Features
- **Directed graph construction**: Maintains an adjacency matrix of up to `MAX_DEVICES` devices.
- **Query outgoing connections**: List devices that a given device sends data to.
- **Query incoming connections**: List devices that send data to a given device.
- **Show both directions**: Convenience call to display outgoing and incoming for a device.
- **Adjacency matrix display**: View the full connectivity matrix.
- **Dynamic updates at runtime**:
  - Add devices
  - Add directed or bidirectional connections
  - Remove connections
  - Remove devices (with adjacency maintenance)

### Files
- `graph.h` — Graph data structure and function prototypes.
- `graph.c` — Implementations for graph initialization, add/remove, queries, and display.
- `main.c` — Interactive menu-driven CLI to exercise all features.

### Requirements Coverage
- **Directed graph**: `addDevice`, `addConnection`, adjacency matrix in `graph.c`.
- **Query functionality**: `displayConnections` (outgoing), `displayIncomingConnections` (incoming), `displayBothConnections` (both), with graceful handling of unknown IDs.
- **Adjacency matrix**: `displayAdjacencyMatrix`.
- **Optional features**:
  - Bidirectional edges: `addBidirectionalConnection` or add two directed edges.
  - Dynamic updates: menu options for add/remove device/connection.
  - Incoming connections display: `displayIncomingConnections` and combined display.

### Build
From the `Question 3/DeviceMapping` directory:

```bash
gcc -std=c11 -Wall -Wextra -O2 main.c graph.c -o DeviceMapping
```

This produces an executable named `DeviceMapping`.

### Run

```bash
./DeviceMapping
```

You will see an interactive menu.

### Menu Options
- **1. Add device**: Adds a new device by ID (e.g., `D009`). Fails gracefully if `MAX_DEVICES` reached.
- **2. Add connection (directed)**: Adds an edge `A -> B`.
- **3. Add connection (bidirectional)**: Adds edges `A -> B` and `B -> A`.
- **4. Remove connection**: Removes a directed edge `A -> B`.
- **5. Remove device**: Removes a device and shifts the adjacency matrix accordingly.
- **6. Show outgoing connections**: All devices directly reachable from a device.
- **7. Show incoming connections**: All devices that directly reach a device.
- **8. Show both incoming and outgoing**: Convenience of 6 and 7.
- **9. Show adjacency matrix**: Matrix of size `deviceCount × deviceCount`.
- **0. Exit**: Quit the program.

### Example Session

```text
Device Mapping Menu:
1. Add device
2. Add connection (directed)
3. Add connection (bidirectional)
4. Remove connection
5. Remove device
6. Show outgoing connections
7. Show incoming connections
8. Show both incoming and outgoing
9. Show adjacency matrix
0. Exit
Select an option: 6
Enter device ID: D004
Devices directly communicating with D004:
- D005
- D006

Select an option: 7
Enter device ID: D005
Devices sending to D005:
- D003
- D004

Select an option: 9
Adjacency Matrix:
0 1 1 0 0 0 0 0
0 0 0 1 0 0 0 0
0 0 0 0 1 0 0 0
0 0 0 0 1 1 0 0
0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
```

Note: The exact matrix depends on the current graph state. The program seeds an initial set of devices and connections in `main.c`; you can add/remove interactively.

### Data Structures
- **Devices**: `char* devices[MAX_DEVICES]`
- **Edges**: `int adjacencyMatrix[MAX_DEVICES][MAX_DEVICES]`, where `adjacencyMatrix[i][j] == 1` iff there is a directed edge `device[i] -> device[j]`.
- **Count**: `int deviceCount` tracks the active device slots from `0..deviceCount-1`.

### Complexity
- **Add connection / remove connection**: `O(n)` to resolve device indices by ID, where `n = deviceCount`.
- **Display outgoing/incoming**: `O(n)` scans a row or column.
- **Remove device**: `O(n^2)` due to shifting rows/columns in the adjacency matrix and device array.
- **Adjacency matrix display**: `O(n^2)`.

Given `MAX_DEVICES` is small (default `10`), the above operations are efficient and simple.

### Limits and Behavior
- **Maximum devices**: Controlled by `MAX_DEVICES` in `graph.h` (default `10`).
- **Unknown IDs**: All query and update functions handle invalid IDs gracefully by printing a message.
- **Memory management**: Device IDs are allocated via `strdup` in `addDevice` and freed in `removeDevice` or `freeGraph`.

### Extending the Program
- Increase `MAX_DEVICES` for larger graphs.
- Replace the adjacency matrix with adjacency lists for better scalability.
- Add persistence (load/save graph to a file, e.g., JSON or CSV mapping).
- Introduce weights (e.g., bandwidth) and path-finding (BFS/DFS) queries.
- Improve input validation and command parsing for robust CLI/REPL behavior.

### Testing Tips
- Try adding a device beyond `MAX_DEVICES` to see graceful failure.
- Add a connection to a non-existent device to confirm validation.
- Remove a device and verify that adjacency matrix dimensions and indices adjust correctly.
- Cross-check outgoing lists against the adjacency matrix rows; incoming lists against columns.


