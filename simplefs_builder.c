#include "simplefs.h"

void set_bit(unsigned char *bitmap, int index) { bitmap[index / 8] |= (1u << (index % 8)); }
int is_bit_set(unsigned char *bitmap, int index) { return bitmap[index / 8] & (1u << (index % 8)); }
long inode_offset(int inode_number) { return ((long)INODE_TABLE_BLOCK * BLOCK_SIZE) + ((long)(inode_number - 1) * sizeof(inode_t)); }
int find_free_inode(unsigned char *bitmap) { (void)bitmap; return -1; }
int find_free_data_block(unsigned char *bitmap) { (void)bitmap; return -1; }

int main(int argc, char *argv[])
{
    char *image_name = NULL;
    FILE *fp;
    unsigned char zero_block[BLOCK_SIZE] = {0};
    unsigned char inode_bitmap[BLOCK_SIZE] = {0};
    unsigned char data_bitmap[BLOCK_SIZE] = {0};
    superblock_t sb;
    inode_t root_inode;
    dirent_t dot, dotdot;

    if (argc != 3) { printf("Usage: %s --image <image_name>\n", argv[0]); return 1; }
    if (strcmp(argv[1], "--image") != 0) { printf("Error: expected --image option.\n"); return 1; }
    image_name = argv[2];

    fp = fopen(image_name, "wb+");
    if (!fp) { printf("Error: could not create image file.\n"); return 1; }

    for (int i = 0; i < TOTAL_BLOCKS; i++) {
        if (fwrite(zero_block, BLOCK_SIZE, 1, fp) != 1) { printf("Error: could not initialize image.\n"); fclose(fp); return 1; }
    }

    /* TODO 1: Fill all superblock fields. */
    memset(&sb, 0, sizeof(sb));
    /* TODO: STUDENT CODE START */

    /* TODO: STUDENT CODE END */
    fseek(fp, SUPERBLOCK_BLOCK * BLOCK_SIZE, SEEK_SET);
    fwrite(&sb, sizeof(sb), 1, fp);

    /* TODO 2: Mark inode 1 allocated (inode bitmap index 0). */
    /* TODO: STUDENT CODE START */

    /* TODO: STUDENT CODE END */
    fseek(fp, INODE_BITMAP_BLOCK * BLOCK_SIZE, SEEK_SET);
    fwrite(inode_bitmap, BLOCK_SIZE, 1, fp);

    /* TODO 3: Mark root data block allocated (data bitmap index 0). */
    /* TODO: STUDENT CODE START */

    /* TODO: STUDENT CODE END */
    fseek(fp, DATA_BITMAP_BLOCK * BLOCK_SIZE, SEEK_SET);
    fwrite(data_bitmap, BLOCK_SIZE, 1, fp);

    /* TODO 4: Initialize root inode according to the specification. */
    memset(&root_inode, 0, sizeof(root_inode));
    /* TODO: STUDENT CODE START */

    /* TODO: STUDENT CODE END */
    fseek(fp, inode_offset(ROOT_INODE), SEEK_SET);
    fwrite(&root_inode, sizeof(root_inode), 1, fp);

    /* TODO 5: Initialize the '.' entry. */
    memset(&dot, 0, sizeof(dot));
    /* TODO: STUDENT CODE START */

    /* TODO: STUDENT CODE END */

    /* TODO 6: Initialize the '..' entry. */
    memset(&dotdot, 0, sizeof(dotdot));
    /* TODO: STUDENT CODE START */

    /* TODO: STUDENT CODE END */

    fseek(fp, ROOT_DATA_BLOCK * BLOCK_SIZE, SEEK_SET);
    fwrite(&dot, sizeof(dot), 1, fp);
    fwrite(&dotdot, sizeof(dotdot), 1, fp);

    fclose(fp);
    printf("SimpleFS image created successfully: %s\n", image_name);
    return 0;
}
