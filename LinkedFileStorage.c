#include <stdio.h>
#include <string.h>
#define MAX_DISK_SIZE 1000 // Define maximum disk size
// Structure to represent a file
struct File
{
    char name[20];
    int startBlock;
    int length;
};
// Structure to represent a disk block
struct DiskBlock
{
    int occupied;  // 0 means free, 1 means occupied
    int nextBlock; // Stores the index of the next block in the linked list
};
// Structure to represent the disk
struct Disk
{
    struct DiskBlock blocks[MAX_DISK_SIZE];
};
// Function to allocate a file on the disk using linked list allocation
int allocateFile(struct Disk *disk, struct File *file)
{
    int requiredBlocks = file->length;
    int allocatedBlocks = 0;
    int currentBlock = file->startBlock;
    int previousBlock = -1;
    while (allocatedBlocks < requiredBlocks)
    {
        if (currentBlock >= MAX_DISK_SIZE || disk->blocks[currentBlock].occupied == 1)
        {
            return 0; // Allocation failed
        }
        disk->blocks[currentBlock].occupied = 1; // Mark block as occupied
        if (previousBlock != -1)
        {
            disk->blocks[previousBlock].nextBlock = currentBlock; // Link previous block to current block
        }
        previousBlock = currentBlock;
        allocatedBlocks++;
        // Find the next free block
        int foundNext = 0;
        for (int i = 0; i < MAX_DISK_SIZE; i++)
        {
            if (disk->blocks[i].occupied == 0)
            {
                currentBlock = i;
                foundNext = 1;
                break;
            }
        }
        if (!foundNext && allocatedBlocks < requiredBlocks)
        {
            return 0; // No more free blocks and still need more blocks
        }
    }
    disk->blocks[previousBlock].nextBlock = -1; // End of the linked list
    return 1;                                   // Allocation successful
}
// Main function
int main()
{
    struct Disk disk;
    for (int i = 0; i < MAX_DISK_SIZE; i++)
    {
        disk.blocks[i].occupied = 0;
        disk.blocks[i].nextBlock = -1; // Initialize all blocks as free and without a next block
    }
    int numFiles;
    printf("Enter the number of files to store: ");
    scanf("%d", &numFiles);
    struct File files[numFiles];
    for (int i = 0; i < numFiles; i++)
    {
        printf("\nEnter details for File %d:\n", i + 1);
        printf("File name: ");
        scanf("%s", files[i].name);
        printf("Starting block (0 to %d): ", MAX_DISK_SIZE - 1);
        scanf("%d", &files[i].startBlock);
        printf("Length of file: ");
        scanf("%d", &files[i].length);
        // Attempt to allocate the file
        if (allocateFile(&disk, &files[i])){
            printf("File '%s' allocated successfully!\n", files[i].name);
        }
        else{
            printf("Failed to allocate file '%s'. Not enough free blocks or invalid block range.\n", files[i].name);
        }
    }
    printf("\nEnter the file name to be searched : ");
    char searchName[20];
    scanf("%s", searchName);
    int it = 0;
    for(it = 0; it < numFiles; it++){
        if(strcmp(files[it].name, searchName) == 0){
            printf("File Name : %s\n", files[it].name);
            printf("File Name : %d\n", files[it].startBlock);
            printf("File Name : %d\n", files[it].length);
            printf("Blocks Occupied : %d ", files[it].startBlock);
            int k = files[it].startBlock;
            while(disk.blocks[k].nextBlock != -1){
                printf("%d ", disk.blocks[k].nextBlock);
                k = disk.blocks[k].nextBlock;
            }
            printf("\n");
            break;
        }
    }
    if(it == numFiles){
        printf("File does not exist\n");
    }
    return 0;
}