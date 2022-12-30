int execute(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (????) {
    execvp(???, ???);
    exit(EXIT_FAILURE);
  } 
  else {
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }  
  return 1;
}
