#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256
#define MAX_TREE_HEIGHT 100

// Node structure for Huffman tree
struct Node {
    char character;
    unsigned frequency;
    struct Node *left, *right;
};

// Min-heap structure
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct Node** array;
};

// Function to create a new node
struct Node* newNode(char character, unsigned frequency) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->left = temp->right = NULL;
    temp->character = character;
    temp->frequency = frequency;
    return temp;
}

// Function to create a MinHeap
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct Node**)malloc(minHeap->capacity * sizeof(struct Node*));
    return minHeap;
}

// Function to swap two min heap nodes
void swapNode(struct Node** a, struct Node** b) {
    struct Node* t = *a;
    *a = *b;
    *b = t;
}

// Heapify function
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < (int)minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;

    if (right < (int)minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    if (smallest != idx) {
        swapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Function to check if size of heap is 1
int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// Function to extract minimum value node from heap
struct Node* extractMin(struct MinHeap* minHeap) {
    struct Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// Function to insert a new node to MinHeap
void insertMinHeap(struct MinHeap* minHeap, struct Node* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->frequency < minHeap->array[(i - 1) / 2]->frequency) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// Function to build Huffman tree
struct Node* buildHuffmanTree(char data[], int freq[], int size) {
    struct Node *left, *right, *top;
    struct MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        insertMinHeap(minHeap, newNode(data[i], freq[i]));

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

// Global variables for Huffman codes
char huffmanCodes[MAX_CHAR][MAX_TREE_HEIGHT];
int codeLengths[MAX_CHAR];

// Function to store Huffman codes
void storeCodes(struct Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        storeCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top + 1);
    }
    if (!(root->left) && !(root->right)) {
        for (int i = 0; i < top; i++) {
            huffmanCodes[(unsigned char)root->character][i] = arr[i] + '0';
        }
        huffmanCodes[(unsigned char)root->character][top] = '\0';
        codeLengths[(unsigned char)root->character] = top;
    }
}

// Advanced bit buffer for efficient compression
struct BitBuffer {
    unsigned char buffer;
    int bitCount;
    FILE* file;
};

void initBitBuffer(struct BitBuffer* bb, FILE* file) {
    bb->buffer = 0;
    bb->bitCount = 0;
    bb->file = file;
}

void writeBit(struct BitBuffer* bb, int bit) {
    bb->buffer |= (bit << (7 - bb->bitCount));
    bb->bitCount++;
    
    if (bb->bitCount == 8) {
        fputc(bb->buffer, bb->file);
        bb->buffer = 0;
        bb->bitCount = 0;
    }
}

void flushBits(struct BitBuffer* bb) {
    if (bb->bitCount > 0) {
        fputc(bb->buffer, bb->file);
    }
}

int readBit(struct BitBuffer* bb) {
    if (bb->bitCount == 0) {
        int byte = fgetc(bb->file);
        if (byte == EOF) return -1;
        bb->buffer = (unsigned char)byte;
        bb->bitCount = 8;
    }
    
    int bit = (bb->buffer >> (bb->bitCount - 1)) & 1;
    bb->bitCount--;
    return bit;
}

// Function to compress file with advanced bit-level compression
void compressFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("File opening failed");
        return;
    }

    // Read entire file
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *data = (char*)malloc(fileSize + 1);
    if (!data) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }
    
    fread(data, 1, fileSize, file);
    data[fileSize] = '\0';
    fclose(file);

    // Calculate frequencies
    int freq[MAX_CHAR] = {0};
    for (int i = 0; i < fileSize; i++) {
        freq[(unsigned char)data[i]]++;
    }

    // Build Huffman tree
    char uniqueChars[MAX_CHAR];
    int uniqueFreq[MAX_CHAR];
    int uniqueCount = 0;
    
    for (int i = 0; i < MAX_CHAR; i++) {
        if (freq[i] > 0) {
            uniqueChars[uniqueCount] = (char)i;
            uniqueFreq[uniqueCount] = freq[i];
            uniqueCount++;
        }
    }
    
    struct Node* root = buildHuffmanTree(uniqueChars, uniqueFreq, uniqueCount);
    
    // Store Huffman codes
    int arr[MAX_TREE_HEIGHT];
    storeCodes(root, arr, 0);

    // Write compressed file
    FILE *output = fopen("compressed.txt", "wb");
    if (!output) {
        perror("Output file opening failed");
        free(data);
        return;
    }

    // Write header with character frequencies (binary format)
    fwrite(&fileSize, sizeof(long), 1, output);
    fwrite(&uniqueCount, sizeof(int), 1, output);
    for (int i = 0; i < uniqueCount; i++) {
        fwrite(&uniqueChars[i], sizeof(char), 1, output);
        fwrite(&uniqueFreq[i], sizeof(int), 1, output);
    }

    // Write compressed data using bit buffer
    struct BitBuffer bb;
    initBitBuffer(&bb, output);
    
    for (long i = 0; i < fileSize; i++) {
        char* code = huffmanCodes[(unsigned char)data[i]];
        for (int j = 0; code[j]; j++) {
            writeBit(&bb, code[j] - '0');
        }
    }
    
    flushBits(&bb);
    fclose(output);
    free(data);

    printf("Original Size: %ld bytes\n", fileSize);
    printf("Compressed file created successfully.\n");
}

// Function to decompress file
void decompressFile(char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("File opening failed");
        return;
    }

    // Read header
    long originalSize;
    fread(&originalSize, sizeof(long), 1, file);
    int uniqueCount;
    fread(&uniqueCount, sizeof(int), 1, file);
    
    char data[MAX_CHAR];
    int freqArray[MAX_CHAR];
    
    for (int i = 0; i < uniqueCount; i++) {
        fread(&data[i], sizeof(char), 1, file);
        fread(&freqArray[i], sizeof(int), 1, file);
    }
    
    // Build Huffman tree
    struct Node* root = buildHuffmanTree(data, freqArray, uniqueCount);
    
    // Decode compressed data
    FILE *output = fopen("decompressed.txt", "w");
    if (!output) {
        perror("Output file opening failed");
        fclose(file);
        return;
    }
    
    struct BitBuffer bb;
    bb.file = file;
    bb.bitCount = 0;
    
    struct Node* current = root;
    int bit;
    int decodedChars = 0;
    
    while (decodedChars < originalSize && (bit = readBit(&bb)) != -1) {
        if (bit == 0) {
            current = current->left;
        } else {
            current = current->right;
        }
        
        if (!current->left && !current->right) {
            fputc(current->character, output);
            decodedChars++;
            current = root;
        }
    }
    
    fclose(file);
    fclose(output);
    printf("Decompressed file created successfully.\n");
}

// Function to compare two files using system diff command
int compareFiles(char *file1, char *file2) {
    char command[200];
    snprintf(command, sizeof(command), "diff %s %s > /dev/null 2>&1", file1, file2);
    int result = system(command);
    return (result == 0); // diff returns 0 if files are identical
}

int main() {
    char *filename = "patient_record.txt";
    
    printf("=== Advanced Huffman Coding Implementation ===\n\n");
    
    printf("1. Compressing file: %s\n", filename);
    compressFile(filename);
    
    printf("\n2. Decompressing file: compressed.txt\n");
    decompressFile("compressed.txt");
    
    printf("\n3. Verifying data integrity...\n");
    if (compareFiles(filename, "decompressed.txt")) {
        printf("✓ Data integrity verified: Original and decompressed files match exactly!\n");
    } else {
        printf("✗ Data integrity check failed: Files do not match!\n");
    }
    
    // Display file sizes
    FILE *original = fopen(filename, "r");
    FILE *compressed = fopen("compressed.txt", "r");
    FILE *decompressed = fopen("decompressed.txt", "r");
    
    if (original && compressed && decompressed) {
        fseek(original, 0, SEEK_END);
        long originalSize = ftell(original);
        fseek(compressed, 0, SEEK_END);
        long compressedSize = ftell(compressed);
        fseek(decompressed, 0, SEEK_END);
        long decompressedSize = ftell(decompressed);
        
        printf("\n=== File Size Comparison ===\n");
        printf("Original file size: %ld bytes\n", originalSize);
        printf("Compressed file size: %ld bytes\n", compressedSize);
        printf("Decompressed file size: %ld bytes\n", decompressedSize);
        
        if (compressedSize > 0) {
            double compressionRatio = (double)compressedSize / originalSize * 100;
            printf("Compression ratio: %.2f%%\n", compressionRatio);
            
            if (compressionRatio < 100) {
                printf("✓ Compression achieved: %.2f%% reduction\n", 100 - compressionRatio);
            } else {
                printf("✗ No compression achieved\n");
            }
        }
        
        fclose(original);
        fclose(compressed);
        fclose(decompressed);
    }
    
    printf("\n=== Process Complete ===\n");
    return 0;
}
