
#include "main.h"
#include <stdio.h>

int main(int args, char** argv){
  {{

  if (args < 2){
    printf("\nformat:      missing operand\nUsage: format [FILENAME] [FILENAME]...\n");
    return -1;
  }

  char *buffer = 0;
  long length;

  for(int i = 1; i < args; i++){
    FILE *f = fopen(argv[i], "r");

    if (!f){
      printf("format ERROR: file %s doens't exist",argv[i]);
      return -1;
    }
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length);
    if (!buffer){
      printf("Ran out of Memory!\n");
      return -1;
    }

    fread(buffer, 1, length, f);
    fclose(f);
    

    String S = remove_existing_formatting(buffer, length);


    add_formatting(S);
    printString(S);

  }
  printf("done");
}}}
