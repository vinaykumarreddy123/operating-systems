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

void bestFit(int process_id, int process_size) {
    int i, j;
    int best_index = -1;
    int best_fit_size = INT_MAX;

    // Find the smallest partition that can accommodate the process
    for (i = 0; i < num_partitions; i++) {
        if (partition_size[i] >= process_size) {
            if (partition_size[i] < best_fit_size) {
                best_fit_size = partition_size[i];
                best_index = i;
            }
        }
    }

    if (best_index != -1) {
        // Allocate the process to the best fit partition found
        printf("Process %d of size %d allocated to partition %d of size %d\n",
               process_id, process_size, partitions[best_index], partition_size[best_index]);
        partition_size[best_index] -= process_size;
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

    // Example process allocations using best fit
    bestFit(1, 120);
    displayMemoryStatus();

    bestFit(2, 30);
    displayMemoryStatus();

    bestFit(3, 250);
    displayMemoryStatus();

    bestFit(4, 80);
    displayMemoryStatus();

    bestFit(5, 200);
    displayMemoryStatus();

    return 0;
}
