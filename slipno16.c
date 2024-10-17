/*
Q.1 Write the simulation program for demand paging and show the 
page scheduling and total number of page faults according to 
the Optimal page replacement algorithm. Assume the memory of n frames.
Reference String: 7, 5, 4, 8, 5, 7, 2, 3, 1, 3, 5, 9, 4, 6
*/

#include <stdio.h>

int find_optimal(int pages[], int frame[], int frames, int n, int current) {
    int pos = -1, farthest = current;
    for (int i = 0; i < frames; i++) {
        int j;
        for (j = current + 1; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n) return i; // If not found in future
    }
    return (pos == -1) ? 0 : pos;
}

int main() {
    int frames, pages[20], frame[10], pageFaults = 0, n, i, j;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    for (i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    printf("\nPage reference string\t\tFrames\n");
    for (i = 0; i < n; i++) {
        int flag1 = 0;

        for (j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                flag1 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            if (frame[frames - 1] == -1) {
                for (j = 0; j < frames; j++) {
                    if (frame[j] == -1) {
                        frame[j] = pages[i];
                        break;
                    }
                }
            } else {
                int pos = find_optimal(pages, frame, frames, n, i);
                frame[pos] = pages[i];
            }
            pageFaults++;
        }

        printf("%d\t\t\t", pages[i]);
        for (j = 0; j < frames; j++) {
            if (frame[j] != -1) {
                printf("%d ", frame[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}


/*
Q.2 Write the program to simulate FCFS CPU-scheduling. The arrival time and 
first CPU-burst of different jobs should be input to the system. Accept no. of 
Processes, arrival time, and burst time. The output should give Gantt chart, 
turnaround time, andContinuing with Slip No. 16 and beyond.

---

### Slip No. 16 - Question 2 (FCFS CPU Scheduling)

```c
/*
Q.2 Write the program to simulate FCFS CPU-scheduling. The arrival time and 
first CPU-burst of different jobs should be input to the system. Accept no. of 
Processes, arrival time, and burst time. The output should give Gantt chart, 
turnaround time, and waiting time for each process. Also find the average 
waiting time and turnaround time.
*/

#include <stdio.h>

typedef struct {
    int pid, at, bt, wt, tat;
} Process;

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    Process proc[n];
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].at, &proc[i].bt);
        proc[i].pid = i + 1;
    }

    // FCFS Scheduling
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < proc[i].at) {
            time = proc[i].at; // wait for the process to arrive
        }
        proc[i].wt = time - proc[i].at;
        time += proc[i].bt;
        proc[i].tat = proc[i].wt + proc[i].bt;
    }

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].at, proc[i].bt, proc[i].wt, proc[i].tat);
    }

    return 0;
}
