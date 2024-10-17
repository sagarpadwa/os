/*
Q.1 Write the simulation program for demand paging and show the 
page scheduling and total number of page faults according to 
the LRU page replacement algorithm. Assume the memory of n frames.
Reference String: 3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6
*/

#include <stdio.h>

int main() {
    int frames, pages, i, j, pageFaults = 0, counter = 0;
    int frame[10], page[20], time[10], pos;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    printf("Enter page reference string:\n");
    for (i = 0; i < pages; i++) {
        scanf("%d", &page[i]);
    }

    for (i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    printf("\nPage reference string\t\tFrames\n");
    for (i = 0; i < pages; i++) {
        int flag1 = 0;

        for (j = 0; j < frames; j++) {
            if (frame[j] == page[i]) {
                time[j] = ++counter; // Update time
                flag1 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            pos = 0;
            for (j = 1; j < frames; j++) {
                if (time[j] < time[pos]) {
                    pos = j; // Find the LRU frame
                }
            }
            frame[pos] = page[i];
            time[pos] = ++counter; // Update time for new page
            pageFaults++;
        }

        printf("%d\t\t\t", page[i]);
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
Q.2 Write a program to simulate FCFS CPU-scheduling. The arrival time and 
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
