#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[])
{
  float sum = 0, num = 0, infrac = 0;
  char c;
  char *name = NULL;
  name = malloc(sizeof(char) * 255);
  for (int i = 0; i < 256; i++)
    name[i] = 0;
  int j = 0;
  for (int i = 0; i < 256; i++)
  {
    if ((argv[1][i] != '\'') && (argv[1][i] != '\n') && (argv[1][i] != '$'))
    {
      name[j] = argv[1][i];
      j++;
    }
  }
  int minus = 0, i = 0;
  while (argv[2][i] != '\0')
  {
    c = argv[2][i];
    if (c == ' ' || c == '\t')
    {
      sum = minus ? sum - num : sum + num;
      num = 0;
      minus = 0;
      infrac = 0;
    }
    else if (c == '-')
    {
      minus = 1;
    }
    else if (c == '.' || c == ',')
    {
      infrac = 10;
    }
    else if (c >= '0' && c <= '9')
    {
      if (infrac == 0)
        num = num * 10 + c - '0';
      else
      {
        float f = (c - '0') / infrac;
        num = num + f;
        infrac *= 10;
      }
    }
    i++;
  }
  sum = minus ? sum - num : sum + num;
  FILE *filename;
  if ((filename = fopen(name, "a")) == NULL)
  {
    printf("Cannot open file");
    return 0;
  }
  fprintf(filename, "%.3f\n", sum);
  fclose(filename);
  return 0;
}
