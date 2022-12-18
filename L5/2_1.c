#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
  // Array of all available signals
  int signals[] = {
    SIGHUP, SIGINT, SIGQUIT, SIGILL, SIGTRAP, SIGABRT, SIGBUS, SIGFPE,
    SIGKILL, SIGUSR1, SIGSEGV, SIGUSR2, SIGPIPE, SIGALRM, SIGTERM,
    SIGSTKFLT, SIGCHLD, SIGCONT, SIGSTOP, SIGTSTP, SIGTTIN, SIGTTOU,
    SIGURG, SIGXCPU, SIGXFSZ, SIGVTALRM, SIGPROF, SIGWINCH, SIGIO,
    SIGPWR, SIGSYS
  };

  size_t num_signals = sizeof(signals) / sizeof(int);

  // Try to send each signal to ourselves
  for (size_t i = 0; i < num_signals; i++) {
    int sig = signals[i];
    if (kill(getpid(), sig) != 0) {
      printf("Failed to send signal %d\n", sig);
    }
  }

  printf("Successfully sent all signals\n");
  return 0;
}
