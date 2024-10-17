/*
Q.1 Write a C program that demonstrates the use of nice() system call. 
After a child process is started using fork(), assign higher priority to 
the child using nice() system call.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        nice(-5); // Increase priority (lower nice value = higher priority)
        printf("Child Process (PID: %d) has increased priority.\n", getpid());
    } else {
        // Parent process
        printf("Parent Process (PID: %d)\n", getpid());
    }

    return 0;
}


/*
Q.2 Write a program to simulate Non-preemptive priority scheduling. 
The arrival time and first CPU-burst of different jobs should be input 
to the system. Accept no. of Processes, arrival time, and burst time. 
The output should give Gantt chart, turnaround time, and waiting time 
for each process. Also find the average waiting time and turnaround time.
*/

#include <stdio.h>

typedef struct {
    int pid, bt, at, wt, tat, priority;
} Process;

void find_waiting_time(Process proc[], int n) {
    // Sort based on arrival time
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].at > proc[j].at) {
                Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    // FCFS with Priority Scheduling
    int time = 0, remain = n;
    while (remain > 0) {
        int min_index = -1;
        for (int j = 0; j < n; j++) {
            if (proc[j].at <= time && proc[j].bt > 0) {
                if (min_index == -1 || proc[j].priority < proc[min_index].priority) {
                    min_index = j;
                }
            }
        }

        if (min_index != -1) {
            time += proc[min_index].bt; // Process execution
            proc[min_index].bt = 0;
            proc[min_index].tat = time - proc[min_index].at;
            proc[min_index].wt = proc[min_index].tat - proc[min_index].bt;
            remain--;
        } else {
            time++; // If no process is ready, just increment time
        }
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process proc[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &proc[i].at, &proc[i].bt, &proc[i].priority);
        proc[i].pid = i + 1;
    }

    find_waiting_time(proc, n);

    float total_wt = 0, total_tat = 0;
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].at, proc[i].bt, proc[i].wt, proc[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
