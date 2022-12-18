#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t count = 0;

void sig_handler(int signum)
{
  count++;
}

int main(void)
{
  struct sigaction sa;

  // Install the signal handler
  sa.sa_handler = sig_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;

  if (sigaction(SIGUSR1, &sa, NULL) != 0) {
    perror("sigaction");
    return 1;
  }

  // Send multiple signals to ourselves
  for (int i = 0; i < 5; i++) {
    if (kill(getpid(), SIGUSR1) != 0) {
      perror("kill");
      return 1;
    }
  }

  // Wait for the signal handler to be called
  sleep(1);

  printf("Received %d signals\n", count);
  return 0;
}