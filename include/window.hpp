#include <stdio.h>
#include <iostream>
#include <map>
#include <unistd.h>
#include <sys/ioctl.h>

winsize get_winsize(void) {
  struct winsize ws;

  if (~ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws)) return ws;
  else {
    perror("ioctl");
    exit(1);
  }
}
