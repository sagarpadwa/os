/*
Q.1 Write a C program to accept n integers to be sorted. Main function 
creates child process using fork system call. Parent process sorts 
the integers using bubble sort and waits for child process using 
wait system call. Child process sorts the integers using insertion sort.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertion_sort(int arr[], int n) {
    forContinuing from where we left off:

### Slip No. 23 - Question 1 (Child Process with Bubble Sort - Continued)

```c
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int n;
    printf("Enter the number of integers: ");
    scanf("%d", &n);
    int arr[n];

    for (int i = 0; i < n; i++) {
        printf("Enter integer %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        insertion_sort(arr, n);
        printf("Child Process sorted array (Insertion Sort): ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        // Parent process
        wait(NULL); // Wait for child process to finish
        bubble_sort(arr, n);
        printf("Parent Process sorted array (Bubble Sort): ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    return 0;
}



/*
Q.2 Write a C program to demonstrate memory management techniques using paging. 
Simulate page allocation and deallocation, including handling page faults.
*/

#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4 // Assuming page size of 4 bytes
#define MEMORY_SIZE 16 // Total memory size of 16 bytes
#define TOTAL_PAGES MEMORY_SIZE / PAGE_SIZE

int memory[TOTAL_PAGES] = {0};

void allocate_page(int page_num) {
    if (page_num < TOTAL_PAGES) {
        memory[page_num] = 1; // Mark page as allocated
        printf("Page %d allocated.\n", page_num);
    } else {
        printf("Page %d cannot be allocated.\n", page_num);
    }
}

void deallocate_page(int page_num) {
    if (page_num < TOTAL_PAGES && memory[page_num] == 1) {
        memory[page_num] = 0; // Mark page as deallocated
        printf("Page %d deallocated.\n", page_num);
    } else {
        printf("Page %d cannot be deallocated.\n", page_num);
    }
}

void display_memory() {
    printf("Memory Allocation Status:\n");
    for (int i = 0; i < TOTAL_PAGES; i++) {
        printf("Page %d: %s\n", i, memory[i] ? "Allocated" : "Free");
    }
}

int main() {
    allocate_page(1);
    allocate_page(3);
    display_memory();
    deallocate_page(1);
    display_memory();

    return 0;
}
