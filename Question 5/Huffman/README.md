# Huffman Coding - Compression and Decompression

## Overview
This program implements lossless text compression using Huffman coding. It:
- Reads an input patient record file (`patient_record.txt`)
- Builds a Huffman tree from character frequencies
- Compresses the input into a compact bitstream written to `compressed.txt`
- Decompresses the bitstream back to `decompressed.txt`
- Verifies data integrity by comparing the decompressed output with the original
- Prints original, compressed, and decompressed sizes and reports compression ratio

The implementation uses a binary header and packs bits into bytes for the compressed payload to ensure space efficiency.

## Project Layout
- `huffman huffman.c`: Main implementation (Huffman tree, compression, decompression, verification)
- `patient_record.txt`: Example input text file (you can replace with any `.txt`)
- `compressed.txt`: Binary compressed output
- `decompressed.txt`: Decompressed output (text)

## Build
```bash
# From the Huffman folder
gcc -o huffman "huffman huffman.c" -Wall -Wextra
```

## Run
```bash
./huffman
```
Program output will display:
- Original, compressed, and decompressed sizes
- Whether decompressed output matches the original exactly
- Compression ratio and whether compression was achieved

## Using Your Own Input
Replace the contents of `patient_record.txt` with any `.txt` file data you want to compress, then rebuild and re-run the program.

## Compressed File Format (Binary)
The compressed file (`compressed.txt`) is a binary file with the following layout:
1. Original file size: `long` (8 bytes on most platforms)
2. Unique character count: `int`
3. Frequency table entries repeated `uniqueCount` times:
   - Character: `char`
   - Frequency: `int`
4. Huffman-encoded payload as a packed bitstream (most significant bit written first within each byte)

During decompression, the program:
- Reads the header (original size and frequency table)
- Reconstructs the exact Huffman tree used for compression
- Reads bits from the payload and traverses the tree until it decodes exactly `originalSize` characters

## Notes
- `compressed.txt` is binary; opening it in a text editor may show unreadable characters. Use tools like `hexdump -C compressed.txt | head` if you need to inspect it.
- For small or highly diverse inputs, compression ratios may be near or above 100% due to header overhead. Larger and more repetitive inputs compress better.
- The integrity check uses a byte-exact comparison of original and decompressed files.

## Example Output
```
=== Advanced Huffman Coding Implementation ===

1. Compressing file: patient_record.txt
Original Size: 1002 bytes
Compressed file created successfully.

2. Decompressing file: compressed.txt
Decompressed file created successfully.

3. Verifying data integrity...
✓ Data integrity verified: Original and decompressed files match exactly!

=== File Size Comparison ===
Original file size: 1002 bytes
Compressed file size: 1000 bytes
Decompressed file size: 1002 bytes
Compression ratio: 99.80%
✓ Compression achieved: 0.20% reduction

=== Process Complete ===
```

## Troubleshooting
- If you see a data integrity failure, ensure you are running the current compiled binary and that `patient_record.txt` remains unchanged between compression and verification.
- If the program cannot open files, confirm the working directory is the `Huffman` folder and that the files exist with appropriate permissions.

## References (APA)
- Huffman, D. A. (1952). A method for the construction of minimum-redundancy codes. Proceedings of the IRE, 40(9), 1098–1101. https://doi.org/10.1109/JRPROC.1952.273898
- Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). Introduction to Algorithms (3rd ed.). MIT Press.
- Salomon, D., & Motta, G. (2010). Handbook of Data Compression (5th ed.). Springer. https://doi.org/10.1007/978-1-84882-903-9
- Witten, I. H., Moffat, A., & Bell, T. C. (1999). Managing Gigabytes: Compressing and Indexing Documents and Images (2nd ed.). Morgan Kaufmann.
