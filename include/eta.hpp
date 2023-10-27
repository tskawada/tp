#include <stdio.h>
#include <time.h>
#include "window.hpp"

class ETA {
    public:
        ETA(int num_of_frames) {
            this->num_of_frames = num_of_frames;
            this->i = 0;
            this->start = time(NULL);
            this->now = time(NULL);
        }
        void update() {
            int winsize_col = get_winsize().ws_col - 50;
            this->now = time(NULL);
            this->i++;
            if (this->i == 1) {
                printf("Progress | %04d \e[42m %.2f%% \e[0m\n", 
                    this->i, 
                    this->i / (double)this->num_of_frames * 100
                );
            } else {
                printf("\e[1AProgress | %04d \e[42m %.2f%% \e[0m | ", 
                    this->i, 
                    this->i / (double)this->num_of_frames * 100
                );
                for (int pg = 0; pg < winsize_col; pg++) {
                    if (pg == int(this->i / (double)this->num_of_frames * winsize_col)) printf(">");
                    if (pg < int(this->i / (double)this->num_of_frames * winsize_col)) printf("=");
                    else printf(" ");
                }
                printf(" | ETA: %02d:%02d:%02d\n", 
                    (int)((this->num_of_frames - this->i) * (this->now - this->start) / this->i / 3600),
                    (int)((this->num_of_frames - this->i) * (this->now - this->start) / this->i / 60) % 60,
                    (int)((this->num_of_frames - this->i) * (this->now - this->start) / this->i) % 60
                );
            }
        }
    private:
        int num_of_frames;
        int i;
        time_t start;
        time_t now;
};