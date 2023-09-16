#include <stdio.h>

void progress_bar(int i, int num_of_frames) {
    if (i == 1) {
        printf("Progress | %04d \e[42m %.2f%% \e[0m\n", i, i / (double)num_of_frames * 100);
    } else {
        printf("\e[1AProgress | %04d \e[42m %.2f%% \e[0m | ", i, i / (double)num_of_frames * 100);
        for (int pg = 0; pg < 100; pg++) {
            if (pg < int(i / (double)num_of_frames * 100)) printf("=");
            else if (pg == int(i / (double)num_of_frames * 100)) printf(">");
            else printf(" ");
        }
        printf(" | \n");
    }
}