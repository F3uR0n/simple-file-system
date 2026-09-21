# SimpleFS

![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square)
![Standard](https://img.shields.io/badge/C_Standard-C11-lightgrey?style=flat-square)

A simple, flat file system implemented in C as a binary disk image. SimpleFS was developed as a lab term project for **CSE 321: Operating Systems (Summer 2026)** and demonstrates core file system concepts including superblock management, inode/data bitmaps, inode tables, and flat directory structures.

---

## Project Overview

SimpleFS is a single-level file system that operates on a fixed-size binary image (262,144 bytes). The implementation is split into two standalone tools: one that initializes a formatted disk image, and one that adds files into it. The design closely mirrors the on-disk layout of real UNIX-style file systems at a simplified scale.

---

## Technologies

- **Language:** C (C11 standard)
- **Compiler:** GCC
- **Build:** Manual compilation via GCC (no build system required)
- **Platform:** Linux / Unix-compatible shell

---

## Filesystem Layout

| Block Index | Purpose          |
|-------------|------------------|
| 0           | Superblock       |
| 1           | Inode Bitmap     |
| 2           | Data Bitmap      |
| 3           | Inode Table      |
| 4 – 63      | Data Region      |

**Key constants:**

| Parameter          | Value                        |
|--------------------|------------------------------|
| Block Size         | 4096 bytes                   |
| Total Blocks       | 64                           |
| Total Inodes       | 32 (inode 1 = root)          |
| Data Blocks        | 60                           |
| Max Direct Blocks  | 3 per file                   |
| Max File Size      | 12,288 bytes (3 × 4096)      |
| Max User Files     | 31 (32 inodes − 1 for root)  |
| Magic Number       | `0x53465331`                 |

---

## Key Features

- Initializes a zero-filled 64-block disk image with a valid superblock, inode bitmap, data bitmap, and pre-populated root directory (`./` and `../` entries).
- Adds regular files from the host filesystem into the SimpleFS image using first-fit inode and data block allocation.
- Validates the filesystem magic number before any write operation.
- Detects and rejects duplicate filenames, oversized files (> 12,288 bytes), filenames exceeding 58 characters, full inode tables, and full root directories.
- Updates the root inode size on each successful file addition.
- Stores file data in zero-padded, block-aligned chunks across up to three direct block pointers.

---

## File Structure

```
simple-file-system/
├── simplefs.h           # Shared header: constants, struct definitions (superblock_t, inode_t, dirent_t), utility prototypes
├── simplefs_builder.c   # Tool 1: Creates and formats a new SimpleFS disk image
├── simplefs_adder.c     # Tool 2: Adds a host file into an existing SimpleFS image
├── test1.txt            # Sample file for testing
├── test2.txt            # Sample file for testing
├── test3.txt            # Sample file for testing
├── LICENSE              # MIT License
└── README.txt           # Original plain-text project notes
```

---

## Build Instructions

Compile each tool separately using GCC:

```bash
gcc -Wall -Wextra -std=c11 simplefs_builder.c -o simplefs_builder
gcc -Wall -Wextra -std=c11 simplefs_adder.c -o simplefs_adder
```

---

## Usage

**1. Create a new SimpleFS image:**

```bash
./simplefs_builder --image disk.img
```

**2. Add files to the image:**

```bash
./simplefs_adder --input disk.img --file test1.txt
./simplefs_adder --input disk.img --file test2.txt
./simplefs_adder --input disk.img --file test3.txt
```

Each invocation validates the image, checks for duplicate filenames, allocates a free inode and the required data blocks, writes the file contents, updates the bitmaps, and appends a directory entry to the root directory.

---

## Known Limitations

- No support for subdirectories; all files reside in the root directory.
- No support for file deletion or renaming.
- Maximum of 31 user files per image.
- Maximum file size of 12,288 bytes (no indirect block support).

---

## License

This project is licensed under the [MIT License](LICENSE).
