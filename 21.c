#include <stdio.h>

#define MAX_PARTITIONS 50

int partitions[MAX_PARTITIONS];
int partition_size[MAX_PARTITIONS];
int num_partitions = 0;

void initializeMemory() {
    // Initialize memory partitions
    num_partitions = 5;
    partitions[0] = 0;
    partition_size[0] = 100;
    partitions[1] = 1;
    partition_size[1] = 200;
    partitions[2] = 2;
    partition_size[2] = 50;
    partitions[3] = 3;
    partition_size[3] = 300;
    partitions[4] = 4;
    partition_size[4] = 150;
}

void worstFit(int process_id, int process_size) {
    int i, j;
    int largest_index = -1;
    int largest_size = -1;

    // Find the largest partition that can accommodate the process
    for (i = 0; i < num_partitions; i++) {
        if (partition_size[i] >= process_size) {
            if (largest_size < partition_size[i]) {
                largest_size = partition_size[i];
                largest_index = i;
            }
        }
    }

    if (largest_index != -1) {
        // Allocate the process to the largest partition found
        printf("Process %d of size %d allocated to partition %d of size %d\n",
               process_id, process_size, partitions[largest_index], partition_size[largest_index]);
        partition_size[largest_index] -= process_size;
    } else {
        printf("Process %d of size %d cannot be allocated. No suitable partition found.\n",
               process_id, process_size);
    }
}

void displayMemoryStatus() {
    int i;
    printf("\nPartition\tSize\n");
    for (i = 0; i < num_partitions; i++) {
        printf("%d\t\t%d\n", partitions[i], partition_size[i]);
    }
    printf("\n");
}

int main() {
    initializeMemory();

    // Display initial memory status
    printf("Initial Memory Status:\n");
    displayMemoryStatus();

    // Example process allocations using worst fit
    worstFit(1, 120);
    displayMemoryStatus();

    worstFit(2, 30);
    displayMemoryStatus();

    worstFit(3, 250);
    displayMemoryStatus();

    worstFit(4, 80);
    displayMemoryStatus();

    worstFit(5, 200);
    displayMemoryStatus();

    return 0;
}
