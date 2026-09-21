CSE 321: Operating Systems
Lab Term Project — Summer 2026
SimpleFS: Implementation of a Simple File System in C

Group Number: 06

Group Members:
1. Farhan Sadik - 24101406
2. Md Sahin Alam - 24101481
3. Rubyeat Wadud Galpa - 24101376



Compilation
--------------------------------------------------
gcc -Wall -Wextra -std=c11 simplefs_builder.c -o simplefs_builder
gcc -Wall -Wextra -std=c11 simplefs_adder.c -o simplefs_adder



Execution
--------------------------------------------------

To create a new SimpleFS image:
	./simplefs_builder --image disk.img

To add a file to the image:
	./simplefs_adder --input disk.img --file test1.txt

Additional files can be added using:
	./simplefs_adder --input disk.img --file test2.txt
	./simplefs_adder --input disk.img --file test3.txt



Implementation Description
--------------------------------------------------

In the simplefs_builder.c file we have created simplefs disk.img (file six 262144 bytes) with 64 blocks where each block size is 4096.From the 64 block Block 0 is occupied for superblock, the others are for inode bitmap, data bitmap, inode block and data block.

On the other hand, in simplefs_adder.c we had implemented programs which support to add files in the image file.In this file we completed the codes which handle many function duplicate filename cannot be entered, verifies file size limits, allocation free or not of both inode and data from inode bit mape and data bit map, updates bit map allocation status and so on.And this helps to handle some error case like invalid arguments, missing files, invalid filesystem, unavailable data block or inode etc.



Contribution of Each Member
--------------------------------------------------
Farhan Sadik: simplefs_builder.c — TODO 1–3, simplefs_adder.c — TODO 7–9
Md Sahin Alam: simplefs_adder.c — TODO 1–6
Rubyeat Wadud Galpa: simplefs_builder.c — TODO 4–6, simplefs_adder.c — TODO 10–11



Known Limitations / Problems
--------------------------------------------------
- No support for subdirectories.
- No support for file deletion.
- No support for renaming.
- Maximum of 31 user files (32 inodes − 1 for root) and 12288-byte max file size.