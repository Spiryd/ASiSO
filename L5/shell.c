#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
  // Temporarily grant the process root privileges
  if (setuid(0) != 0) {
    perror("setuid");
    return 1;
  }

  // Launch the root shell
  execlp("/bin/bash", "bash", (char*)NULL);

  // If we reach here, the execlp call failed
  perror("execlp");
  return 1;
}