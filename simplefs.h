#ifndef SIMPLEFS_H
#define SIMPLEFS_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define BLOCK_SIZE 4096
#define TOTAL_BLOCKS 64
#define TOTAL_INODES 32
#define SUPERBLOCK_BLOCK 0
#define INODE_BITMAP_BLOCK 1
#define DATA_BITMAP_BLOCK 2
#define INODE_TABLE_BLOCK 3
#define DATA_REGION_BLOCK 4
#define DATA_BLOCKS 60
#define ROOT_INODE 1
#define ROOT_DATA_BLOCK 4
#define MAGIC_NUMBER 0x53465331
#define TYPE_FILE 1
#define TYPE_DIRECTORY 2
#define MAX_DIRECT_BLOCKS 3
#define MAX_FILE_SIZE (MAX_DIRECT_BLOCKS * BLOCK_SIZE)
#define DIRENT_SIZE 64

typedef struct {
    uint32_t magic, block_size, total_blocks, inode_count;
    uint32_t inode_bitmap_block, data_bitmap_block, inode_table_block, data_region_block;
    uint32_t root_inode;
} superblock_t;

typedef struct {
    uint16_t type, links;
    uint32_t size;
    uint32_t direct[3];
    uint8_t reserved[108];
} inode_t;

typedef struct {
    uint32_t inode_no;
    uint8_t type;
    char name[59];
} dirent_t;

void set_bit(unsigned char *bitmap, int index);
int is_bit_set(unsigned char *bitmap, int index);
int find_free_inode(unsigned char *bitmap);
int find_free_data_block(unsigned char *bitmap);
long inode_offset(int inode_number);
#endif
