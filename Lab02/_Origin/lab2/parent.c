#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main()
{
  char *name = NULL;
  name = malloc(256 * sizeof(char));
  for (int i = 0; i < 256; i++)
    name[i] = 0;
  char str[255];
  printf("Введите имя файла ");
  fgets(name, 255, stdin);
  fgets(str, 255, stdin);
  while (str[0] != '*')
  {
    int fd[2];
    if (pipe(fd) == -1)
    {
      printf("Error creating pipe");
      return 2;
    }
    int id = fork();
    if (id == -1)
    {
      printf("Error creating process");
      return 3;
    }
    else if (id == 0)
    { //дочерний процесс
      close(fd[1]);
      read(fd[0], str, 255);
      execl("child.out", " ", name, str, NULL);
      close(fd[0]);
    }
    else
    { //родительский процесс
      close(fd[0]);
      write(fd[1], str, 255);
      close(fd[1]);
    }
    fgets(str, 255, stdin);
  }
  return 0;
}
