#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
  // Check if we are root
  if (geteuid() != 0) {
    fprintf(stderr, "Error: This program must be run as root\n");
    return 1;
  }

  // Try to send a SIGKILL signal to PID 1
  if (kill(1, SIGKILL) != 0) {
    perror("kill");
    return 1;
  }

  printf("Successfully sent SIGKILL to PID 1\n");
  return 0;
}
