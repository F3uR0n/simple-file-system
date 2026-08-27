CSE 321: Operating Systems
Lab Term Project — Summer 2026
SimpleFS: Implementation of a Simple File System in C

Group Number: 06

Group Members:
1. Farhan Sadik - 24101406
2. Md Sahin Alam - 24101481
3. Rubyeat Wadud Galpa - 24101376



Compilation
----------------------
gcc -Wall -Wextra -std=c11 simplefs_builder.c -o simplefs_builder
gcc -Wall -Wextra -std=c11 simplefs_adder.c -o simplefs_adder



Execution
----------------------

To create a new SimpleFS image:

	./simplefs_builder --image disk.img

To add a file to the image:

	./simplefs_adder --input disk.img --file test1.txt

Additional files can be added using:

	./simplefs_adder --input disk.img --file test2.txt
	./simplefs_adder --input disk.img --file test3.txt



Implementation Description
--------------------------------------------------

simplefs_builder.c creates a 262144-byte (64-block, 4096 bytes/block) SimpleFS image and initializes it: writes the superblock to Block 0, sets bit 0 in the inode bitmap (Block 1) and data bitmap (Block 2) to mark the root inode and root data block as allocated, writes the root inode (type=directory, links=2, size=128, direct[0]=4) to Block 3, and writes the "." and ".." directory entries to Block 4.

simplefs_adder.c adds a regular file from the current working directory into an existing image. It validates the image's magic number, rejects files over 12288 bytes or names over 58 characters, computes the number of 4096-byte blocks needed (ceil(file_size / BLOCK_SIZE)), rejects duplicate file names by scanning the root directory, then uses first-fit allocation over the inode bitmap and data bitmap to find a free inode and the required number of free data blocks. It copies the source file's contents into the allocated blocks (zero-padding the final partial block), writes a new inode with the correct direct pointers, marks the inode/data bitmaps, adds a directory entry mapping the file name to the new inode number, and increases the root inode's size by 64 bytes (sizeof(dirent_t)).



Contribution of Each Member
--------------------------------------------------
Farhan Sadik: [e.g., simplefs_builder.c — superblock, bitmaps, root inode/entries]
Md Sahin Alam: [e.g., simplefs_adder.c — allocation, file copy, directory update]
Rubyeat Wadud Galpa: [e.g., testing with xxd/hexdump, README, edge cases]



Known Limitations / Problems
--------------------------------------------------
- No support for subdirectories, file deletion, renaming, or links (by design, per project spec).
- Maximum of 31 user files (32 inodes − 1 for root) and 12288-byte max file size, both fixed by the SimpleFS parameters.