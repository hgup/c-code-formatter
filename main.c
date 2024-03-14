
#include "main.h"

int main(int args, char** argv){

  // HANDLE INPUT ERROR
  if (args < 2){
    printf("\nformat: missing operand\nUsage: format [FILENAME] [FILENAME]...\n");
    return -1;
  }

  char *buffer = 0;
  long length;

  for(int i = 1; i < args; i++){
    // for each file we do the following operations
    FILE *f = fopen(argv[i], "r");

    if (!f){
      printf("format ERROR: file %s doens't exist",argv[i]);
      return -1;
    }
    // if file exists
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
    

    // printf("%s\n",buffer);
    // STEP 1
    
    String S = remove_existing_formatting(buffer, length);
    printString(S);


  }
}
