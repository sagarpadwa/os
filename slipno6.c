/*
Q.1 Write the simulation program for demand paging and show the 
page scheduling and total number of page faults according to 
the Optimal page replacement algorithm. Assume the memory of n frames.
Reference String: 7, 5, 4, 8, 5, 7, 2, 3, 1, 3, 5, 9, 4, 6, 2
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
Q.2 Write the simulation program for Round Robin scheduling for given time quantum.
The arrival time and first CPU-burst of different jobs should be input to the system.
Accept no. of Processes, arrival time and burst time.
The output should give the Gantt chart, turnaround time, and waiting time for each process.
Also display the average turnaround time and average waiting time.
*/

#include <stdio.h>

int main() {
    int i, j, n, time, remain, flag = 0, quantum;
    int wait_time = 0, turnaround_time = 0, arrival_time[10], burst_time[10], temp[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);
    remain = n;

    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &arrival_time[i], &burst_time[i]);
        temp[i] = burst_time[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    printf("\nGantt Chart:\n");
    for (time = 0, i = 0; remain != 0;) {
        if (temp[i] <= quantum && temp[i] > 0) {
            time += temp[i];
            printf("| P%d ", i + 1);
            temp[i] = 0;
            flag = 1;
        } else if (temp[i] > 0) {
            temp[i] -= quantum;
            time += quantum;
            printf("| P%d ", i + 1);
        }

        if (temp[i] == 0 && flag == 1) {
            remain--;
            printf("| Finish ");
            wait_time += time - arrival_time[i] - burst_time[i];
            turnaround_time += time - arrival_time[i];
            flag = 0;
        }

        if (i == n - 1)
            i = 0;
        else if (arrival_time[i + 1] <= time)
            i++;
        else
            i = 0;
    }

    printf("\n\nAverage Waiting Time: %.2f\n", (float)wait_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)turnaround_time / n);

    return 0;
}
