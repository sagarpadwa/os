/*
Q.1 Write the simulation program for demand paging and show the 
page scheduling and total number of page faults according to 
the optimal page replacement algorithm. Assume the memory of n frames.
Reference String: 8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2
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



