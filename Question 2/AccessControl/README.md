# Access Control System

A secure access control system that uses an AVL-balanced Binary Search Tree (BST) to efficiently manage authorized personnel and provide intelligent name matching with typo suggestions.

## Features

- **Secure Access Control**: Verifies names against an authorized list
- **Intelligent Typo Detection**: Uses Levenshtein distance algorithm to suggest similar names
- **Efficient Search**: AVL-balanced BST ensures O(log n) search performance
- **Audit Logging**: Logs unrecognized access attempts for security review
- **Memory Efficient**: Handles up to 40 authorized names with optimal memory usage

## Architecture

### Data Structures
- **NameNode**: AVL tree node containing name, height, and child pointers
- **AVL Tree**: Self-balancing binary search tree for efficient name lookup
- **Levenshtein Distance**: String similarity algorithm for typo detection

### Core Components
- `main.c`: Main application logic and user interface
- `bst.c`: AVL tree implementation with balancing operations
- `levenshtein.c`: String distance calculation for typo detection
- `name_node.h`: Node structure definition
- `bst.h`: BST function declarations
- `levenshtein.h`: Distance function declaration

## Functional Requirements

✅ **Load Names**: Reads authorized names from file and constructs balanced BST
✅ **Access Verification**: 
- Exact match: Grants access
- Minor typo: Suggests closest matching name using Levenshtein distance
- Unrecognized name: Logs for review, denies access
✅ **Memory Efficiency**: Handles up to 40 authorized names efficiently
✅ **Balanced BST**: AVL tree maintains O(log n) search performance

## Installation & Usage

### Prerequisites
- GCC compiler
- Standard C library

### Compilation
```bash
gcc -o AccessControl main.c bst.c levenshtein.c
```

### Setup
1. Ensure `authorized_names.txt` exists with authorized personnel names (one per line)
2. Run the program:
```bash
./AccessControl
```

### Usage
The program provides an interactive interface:

```
Enter your name (or 'exit' to quit): John Smith
Access granted.

Enter your name (or 'exit' to quit): Jon Smith
Access denied.
Did you mean: John Smith?

Enter your name (or 'exit' to quit): exit
```

## File Structure

```
AccessControl/
├── main.c                 # Main application logic
├── bst.c                  # AVL tree implementation
├── bst.h                  # BST function declarations
├── levenshtein.c          # String distance algorithm
├── levenshtein.h          # Distance function declaration
├── name_node.h            # Node structure definition
├── authorized_names.txt   # List of authorized personnel
├── unrecognized_names.log # Log of denied access attempts
└── README.md             # This documentation
```

## Algorithm Details

### AVL Tree Balancing
The system uses AVL (Adelson-Velsky and Landis) tree balancing to maintain optimal search performance:

- **Height Balance**: Difference between left and right subtrees ≤ 1
- **Rotations**: Left and right rotations maintain balance
- **Search Time**: O(log n) guaranteed performance
- **Insertion**: O(log n) with automatic rebalancing

### Levenshtein Distance
String similarity calculation for typo detection:

- **Edit Distance**: Minimum operations to transform one string to another
- **Operations**: Insertion, deletion, substitution
- **Threshold**: Suggests closest match when exact match fails

## Security Features

- **Audit Trail**: All unrecognized access attempts are logged
- **No Access Leakage**: Unauthorized users receive no information about authorized names
- **Efficient Lookup**: Fast verification prevents timing attacks
- **Memory Management**: Proper cleanup prevents memory leaks

## Performance Characteristics

- **Search Complexity**: O(log n) average and worst case
- **Memory Usage**: O(n) where n is number of authorized names
- **Insertion**: O(log n) with automatic balancing
- **Space Efficiency**: Minimal overhead with height tracking

## Error Handling

- **File I/O**: Graceful handling of missing files
- **Memory Allocation**: Proper error checking and cleanup
- **Input Validation**: Safe string handling and buffer management
- **Logging**: Robust error logging for system administration

## Example Output

```
$ ./AccessControl
Enter your name (or 'exit' to quit): Alice Johnson
Access granted.

Enter your name (or 'exit' to quit): Alice Jonson
Access denied.
Did you mean: Alice Johnson?

Enter your name (or 'exit' to quit): Bob Wilson
Access granted.

Enter your name (or 'exit' to quit): exit
```

## Log Files

- **unrecognized_names.log**: Contains all denied access attempts with timestamps
- **System Logs**: Standard error output for debugging

## Development Notes

- **Thread Safety**: Single-threaded implementation
- **Platform**: POSIX-compliant systems
- **Dependencies**: Standard C library only
- **Memory**: Automatic cleanup on program exit

## Future Enhancements

- **Case Insensitive**: Add case-insensitive name matching
- **Fuzzy Matching**: Implement more sophisticated typo detection
- **Database Integration**: Replace file-based storage with database
- **Network Interface**: Add remote access capabilities
- **Encryption**: Secure name storage and transmission

## License

This project is part of a Data Structures and Algorithms course assignment.
