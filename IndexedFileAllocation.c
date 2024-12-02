#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
 
#define DISK_SIZE 200 
 
typedef struct 
{ 
    char name[20]; 
    int index_block; 
    int block_count; 
    int blocks[DISK_SIZE]; 
} File; 
 
int disk[DISK_SIZE]; 
 
void initializeDisk() 
{ 
    for (int i = 0; i < DISK_SIZE; i++) 
    { 
        disk[i] = 0; 
    } 
} 
 
void displayFiles(File files[], int file_count) 
{ 
    printf("\n%-12s %-12s %-14s %s\n", "File Name", "Index Block", "No. of Blocks", 
"Blocks Occupied"); 
    for (int i = 0; i < file_count; i++) 
    { 
        printf("%-12s %-12d %-14d", files[i].name, files[i].index_block, files[i].block_count); 
        for (int j = 0; j < files[i].block_count; j++) 
        { 
            printf("%d", files[i].blocks[j]); 
            if (j < files[i].block_count - 1) 
            { 
                printf(", "); 
            } 
        } 
        printf("\n"); 
    } 
} 
 
int allocateFile(File *file) 
{ 
    int count = 0, block; 
    srand(time(0)); 
 
    do 
    { 
        file->index_block = rand() % DISK_SIZE; 
    } while (disk[file->index_block]); 
 
    disk[file->index_block] = 1; 
 
    while (count < file->block_count) 
    {
         block = rand() % DISK_SIZE; 
        if (!disk[block]) 
        { 
            file->blocks[count++] = block; 
            disk[block] = 1; 
        } 
    } 
    return 1; 
} 
 
int main() {
    initializeDisk(); 
 
    int file_count; 
    printf("Enter number of files: "); 
    scanf("%d", &file_count); 
 
    File files[file_count]; 
 
    for (int i = 0; i < file_count; i++) 
    { 
        printf("Enter file %d name: ", i + 1); 
        scanf("%s", files[i].name); 
        printf("Enter number of blocks in file %d: ", i + 1); 
        scanf("%d", &files[i].block_count); 
        allocateFile(&files[i]); 
    } 
 
    displayFiles(files, file_count);
     
    return 0; 
} 