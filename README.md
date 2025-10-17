# Data Structures and Algorithms - Summative Project

## Project Overview
This repository contains five comprehensive implementations demonstrating various data structures and algorithms concepts. Each question addresses a specific real-world problem using appropriate data structures and algorithmic approaches.

## Project Structure
```
Summative-Project_DSA/
├── Question 1/          # IoT Gateway - Linked Lists
├── Question 2/          # Access Control - Binary Search Trees
├── Question 3/          # Device Mapping - Graph Theory
├── Question 4/          # Route Optimization - Graph Algorithms
└── Question 5/          # Huffman Coding - Compression Algorithms
```

## Question 1: IoT Gateway - Linked Lists
**Problem**: Implement a logging system for IoT devices using linked lists to manage log entries efficiently.

**Key Features**:
- Dynamic log entry management
- Efficient insertion and retrieval
- Memory management for IoT environments

**Data Structure**: Singly Linked List
**Files**: `log_list.c`, `log_list.h`, `log_entry.h`, `main.c`

## Question 2: Access Control - Binary Search Trees
**Problem**: Develop an access control system using BST for efficient name lookup and fuzzy matching.

**Key Features**:
- Binary search tree implementation
- Levenshtein distance algorithm for fuzzy matching
- Authorized name verification system

**Data Structure**: Binary Search Tree (BST)
**Files**: `bst.c`, `bst.h`, `levenshtein.c`, `levenshtein.h`, `main.c`

## Question 3: Device Mapping - Graph Theory
**Problem**: Model and analyze device connectivity in a network using graph theory concepts.

**Key Features**:
- Graph representation (adjacency list/matrix)
- Device relationship modeling
- Network topology analysis

**Data Structure**: Graph (Adjacency List/Matrix)
**Files**: `graph.c`, `graph.h`, `main.c`

## Question 4: Route Optimization - Graph Algorithms
**Problem**: Implement route optimization algorithms for finding shortest paths in transportation networks.

**Key Features**:
- Shortest path algorithms (Dijkstra's, Floyd-Warshall)
- Route optimization
- Network analysis

**Data Structure**: Weighted Graph
**Files**: `graph.c`, `graph.h`, `main.c`

## Question 5: Huffman Coding - Compression Algorithms
**Problem**: Implement lossless data compression using Huffman coding for efficient data storage.

**Key Features**:
- Huffman tree construction
- Bit-level compression
- Data integrity verification
- Binary file format

**Data Structure**: Min-Heap, Huffman Tree
**Files**: `huffman huffman.c`, `patient_record.txt`

## Build Instructions

### Prerequisites
- GCC compiler
- Make (optional)
- Standard C library

### Compilation
Each question can be compiled independently:

```bash
# Question 1 - IoT Gateway
cd "Question 1/IoT_Gateway"
gcc -o IoT_Gateway main.c log_list.c -Wall -Wextra

# Question 2 - Access Control
cd "Question 2/AccessControl"
gcc -o AccessControl main.c bst.c levenshtein.c -Wall -Wextra

# Question 3 - Device Mapping
cd "Question 3/DeviceMapping"
gcc -o DeviceMapping main.c graph.c -Wall -Wextra

# Question 4 - Route Optimization
cd "Question 4/RouteOptimization"
gcc -o RouteOptimization main.c graph.c -Wall -Wextra

# Question 5 - Huffman Coding
cd "Question 5/Huffman"
gcc -o huffman "huffman huffman.c" -Wall -Wextra
```

## Running the Programs

### Question 1: IoT Gateway
```bash
./IoT_Gateway
```
Manages IoT device log entries with linked list operations.

### Question 2: Access Control
```bash
./AccessControl
```
Performs name verification using BST and fuzzy matching algorithms.

### Question 3: Device Mapping
```bash
./DeviceMapping
```
Analyzes device connectivity and network topology.

### Question 4: Route Optimization
```bash
./RouteOptimization
```
Finds optimal routes using graph algorithms.

### Question 5: Huffman Coding
```bash
./huffman
```
Compresses and decompresses files using Huffman coding.

## Algorithmic Complexity Analysis

| Question | Data Structure | Time Complexity | Space Complexity |
|----------|----------------|-----------------|------------------|
| Q1 | Linked List | O(n) insertion, O(1) deletion | O(n) |
| Q2 | BST | O(log n) search, O(n) worst case | O(n) |
| Q3 | Graph | O(V + E) traversal | O(V + E) |
| Q4 | Weighted Graph | O(V²) Floyd-Warshall | O(V²) |
| Q5 | Min-Heap + Tree | O(n log n) construction | O(n) |

## Key Learning Outcomes

### Data Structures Mastery
- **Linked Lists**: Dynamic memory management, sequential access patterns
- **Binary Search Trees**: Hierarchical organization, logarithmic search
- **Graphs**: Network modeling, relationship representation
- **Heaps**: Priority queues, tree-based sorting

### Algorithm Design
- **Search Algorithms**: Binary search, tree traversal
- **Graph Algorithms**: Shortest path, connectivity analysis
- **Compression Algorithms**: Huffman coding, entropy reduction
- **String Algorithms**: Levenshtein distance, fuzzy matching

### Software Engineering
- **Modular Design**: Separate header and implementation files
- **Memory Management**: Dynamic allocation and deallocation
- **Error Handling**: Robust input validation and error recovery
- **Code Documentation**: Comprehensive comments and README files

## Testing and Validation

Each implementation includes:
- **Unit Testing**: Individual component validation
- **Integration Testing**: End-to-end functionality verification
- **Edge Case Handling**: Boundary condition testing
- **Performance Analysis**: Complexity measurement and optimization

## Real-World Applications

### Question 1: IoT Systems
- Smart home device logging
- Industrial sensor data management
- Real-time monitoring systems

### Question 2: Security Systems
- Access control systems
- User authentication
- Name matching in databases

### Question 3: Network Analysis
- Computer network topology
- Social network analysis
- Transportation networks

### Question 4: Logistics
- Delivery route optimization
- GPS navigation systems
- Supply chain management

### Question 5: Data Storage
- File compression utilities
- Database optimization
- Network transmission efficiency

## Future Enhancements

### Potential Improvements
- **Parallel Processing**: Multi-threaded implementations
- **Advanced Algorithms**: A* search, genetic algorithms
- **User Interfaces**: GUI implementations
- **Database Integration**: Persistent storage solutions

### Scalability Considerations
- **Large Dataset Handling**: Streaming algorithms
- **Memory Optimization**: Space-efficient data structures
- **Performance Tuning**: Algorithmic optimizations
- **Distributed Systems**: Multi-node implementations

## Troubleshooting Guide

### Common Issues
1. **Compilation Errors**: Ensure all source files are present
2. **Memory Leaks**: Check for proper memory deallocation
3. **Input Validation**: Verify input format and range
4. **File Permissions**: Ensure read/write access for file operations

### Debugging Tips
- Use `valgrind` for memory leak detection
- Enable compiler warnings with `-Wall -Wextra`
- Implement logging for algorithm tracing
- Test with various input sizes and edge cases

## References (APA Format)

### Core Algorithm References
- Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). *Introduction to Algorithms* (3rd ed.). MIT Press.

- Sedgewick, R., & Wayne, K. (2011). *Algorithms* (4th ed.). Addison-Wesley Professional.

- Knuth, D. E. (1998). *The Art of Computer Programming, Volume 3: Sorting and Searching* (2nd ed.). Addison-Wesley.

### Data Structure References
- Weiss, M. A. (2011). *Data Structures and Algorithm Analysis in C* (2nd ed.). Pearson.

- Goodrich, M. T., Tamassia, R., & Goldwasser, M. H. (2014). *Data Structures and Algorithms in Java* (6th ed.). Wiley.

### Specialized Algorithm References
- Huffman, D. A. (1952). A method for the construction of minimum-redundancy codes. *Proceedings of the IRE*, 40(9), 1098–1101. https://doi.org/10.1109/JRPROC.1952.273898

- Dijkstra, E. W. (1959). A note on two problems in connexion with graphs. *Numerische Mathematik*, 1(1), 269-271. https://doi.org/10.1007/BF01386390

- Floyd, R. W. (1962). Algorithm 97: Shortest path. *Communications of the ACM*, 5(6), 345. https://doi.org/10.1145/367766.368168

### Compression and Information Theory
- Salomon, D., & Motta, G. (2010). *Handbook of Data Compression* (5th ed.). Springer. https://doi.org/10.1007/978-1-84882-903-9

- Witten, I. H., Moffat, A., & Bell, T. C. (1999). *Managing Gigabytes: Compressing and Indexing Documents and Images* (2nd ed.). Morgan Kaufmann.

### String Matching and Fuzzy Search
- Navarro, G. (2001). A guided tour to approximate string matching. *ACM Computing Surveys*, 33(1), 31-88. https://doi.org/10.1145/375360.375365

- Levenshtein, V. I. (1966). Binary codes capable of correcting deletions, insertions, and reversals. *Soviet Physics Doklady*, 10(8), 707-710.

### Graph Theory and Network Analysis
- Bondy, J. A., & Murty, U. S. R. (2008). *Graph Theory* (1st ed.). Springer. https://doi.org/10.1007/978-1-84628-970-5

- Newman, M. E. J. (2010). *Networks: An Introduction*. Oxford University Press.

### IoT and Embedded Systems
- Gubbi, J., Buyya, R., Marusic, S., & Palaniswami, M. (2013). Internet of Things (IoT): A vision, architectural elements, and future directions. *Future Generation Computer Systems*, 29(7), 1645-1660. https://doi.org/10.1016/j.future.2013.01.010

## License
This project is created for educational purposes as part of a Data Structures and Algorithms course.

## Contact
For questions or clarifications regarding the implementations, please refer to the individual README files in each question directory.

---
*Last Updated: December 2024*
