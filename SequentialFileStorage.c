#include <stdio.h>
#include <string.h>
#define MAX_DISK_SIZE 1000 // Define maximum disk size
// Structure to represent a file
struct File
{
    char name[20];
    int startBlock;
    int length;
    int allocatedBlocks[MAX_DISK_SIZE];
};
// Structure to represent the disk
struct Disk
{
    int blocks[MAX_DISK_SIZE]; // Array representing disk blocks (0 means free, 1 means occupied)
};
// Function to allocate a file on the disk
int allocateFile(struct Disk *disk, struct File *file)
{
    memset(file->allocatedBlocks, -1, sizeof(file->allocatedBlocks));
    int start = file->startBlock;
    int length = file->length;
    int k = 0;
    // Check if the requested blocks are free
    for (int i = start; i < start + length; i++)
    {
        if (disk->blocks[i] == 1 || i >= MAX_DISK_SIZE)
        {
            memset(file->allocatedBlocks, -1, sizeof(file->allocatedBlocks));
            return 0; // Allocation failed
        }
        file->allocatedBlocks[k++] = i;
    }
    // Allocate the blocks
    for (int i = start; i < start + length; i++)
    {
        disk->blocks[i] = 1; // Mark block as occupied
    }
    return 1; // Allocation successful
}
// Main function
int main()
{
    struct Disk disk;
    memset(disk.blocks, 0, sizeof(disk.blocks)); // Initialize all disk blocks as free
    int numFiles;
    printf("Enter the number of files to store: ");
    scanf("%d", &numFiles);
    struct File files[numFiles];
    printf("\nEnter details for Files as Name, staring block (0 to %d), size of file\n", MAX_DISK_SIZE - 1);
    for (int i = 0; i < numFiles; i++)
    {
        printf("File %d: ", i + 1);
        scanf("%s", files[i].name);
        scanf("%d", &files[i].startBlock);
        scanf("%d", &files[i].length);
        // Attempt to allocate the file
        if (!allocateFile(&disk, &files[i])){
            printf("Failed to allocate file '%s'. Not enough contiguous space or invalid block range.\n", files[i].name);
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
            printf("Blocks Occupied : ");
            int k = 0;
            while(files[it].allocatedBlocks[k] != -1){
                printf("%d ", files[it].allocatedBlocks[k]);
                k++;
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