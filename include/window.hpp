#include <stdio.h>
#include <iostream>
#include <map>
#include <unistd.h>
#include <sys/ioctl.h>

winsize get_winsize(void) {
  struct winsize ws;

  if (~ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws)) return ws;
}

int get_winsize_col(void) {
  std::map<int, int> seqLen;

  seqLen[0] = 0;
  seqLen[1] = 0;
  seqLen[2] = 0;
  seqLen[3] = 0;
  seqLen[4] = 0;
  seqLen[5] = 0;
  seqLen[6] = 0;
  seqLen[7] = 0;
  seqLen[8] = 0;
  seqLen[9] = 0;
  seqLen[10] = 0;
  seqLen[11] = 0;
  seqLen[12] = 0;
  seqLen[13] = 0;
  

  return get_winsize().ws_col;
}