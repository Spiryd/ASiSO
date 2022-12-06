#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 1024
#define MAX_ARGS 64

int main(int argc, char *argv[]) {
  char line[MAX_LINE_LENGTH];
  char *args[MAX_ARGS];
  int should_wait = 1;

  while (1) {
    printf("lsh> ");

    if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL) {
      // Ctrl+D was pressed
      printf("\n");
      break;
    }

    // Parse the command line
    int argc = 0;
    char *token;
    char *rest = line;
    while ((token = strtok_r(rest, " \t\n", &rest))) {
      if (strcmp(token, "&") == 0) {
        // "&" character indicates that the command should be run in the background
        // and lsh should not wait for it to finish
        should_wait = 0;
      } else {
        args[argc++] = token;
      }
    }
    args[argc] = NULL;

    if (argc == 0) {
      // Empty command, do nothing
      continue;
    }

    if (strcmp(args[0], "exit") == 0) {
      // "exit" command exits the shell
      break;
    }

    if (strcmp(args[0], "cd") == 0) {
      // "cd" command changes the current working directory
      if (argc != 2) {
        printf("cd: expected 1 argument\n");
      } else {
        if (chdir(args[1]) != 0) {
          perror("cd");
        }
      }
      continue;
    }

    int child_pid = fork();
    if (child_pid == 0) {
      // This is the child process
      execvp(args[0], args);
      perror("execvp");
      exit(1);
    } else if (child_pid > 0) {
      // This is the parent process
      if (should_wait) {
        // Wait for the child process to finish
        int child_status;
        waitpid(child_pid, &child_status, 0);
      } else {
        // Check for terminated child processes
        int child_status;
        while (waitpid(-1, &child_status, WNOHANG) > 0) {
          // Child process terminated, do nothing
        }
      }
    } else {
      // fork() failed
      perror("fork");
    }

    should_wait = 1;
  }

  return 0;
}
