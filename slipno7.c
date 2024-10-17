/*
Q.1 Write the simulation program for demand paging and show the 
page scheduling and total number of page faults according to 
the LRU page replacement algorithm. Assume the memory of n frames.
Reference String: 8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2
*/

#include <stdio.h>

int main() {
    int frames, pages, i, j, k, pageFaults = 0, counter = 0;
    int frame[10], page[20], flag[10], time[10], pos;

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
        int flag1 = 0, flag2 = 0;

        for (j = 0; j < frames; j++) {
            if (frame[j] == page[i]) {
                counter++;
                time[j] = counter;
                flag1 = 1;
                flag2 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            for (j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    counter++;
                    frame[j] = page[i];
                    time[j] = counter;
                    flag2 = 1;
                    pageFaults++;
                    break;
                }
            }
        }

        if (flag2 == 0) {
            pos = 0;
            for (j = 1; j < frames; j++) {
                if (time[j] < time[pos]) {
                    pos = j;
                }
            }
            counter++;
            frame[pos] = page[i];
            time[pos] = counter;
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
