/*
Q.1 Write the simulation program for demand paging and show the 
page scheduling and total number of page faults according to 
the LFU page replacement algorithm. Assume the memory of n frames.
Reference String: 3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6
*/

#include <stdio.h>

int main() {
    int frames, pages, i, j, k, pageFaults = 0;
    int frame[10], page[20], freq[10], pos;

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
        freq[i] = 0;
    }

    printf("\nPage reference string\t\tFrames\n");
    for (i = 0; i < pages; i++) {
        int flag1 = 0;

        for (j = 0; j < frames; j++) {
            if (frame[j] == page[i]) {
                freq[j]++;
                flag1 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            pos = 0;
            for (j = 1; j < frames; j++) {
                if (frame[j] == -1 || freq[j] < freq[pos]) {
                    pos = j;
                }
            }
            frame[pos] = page[i];
            freq[pos] = 1;
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
