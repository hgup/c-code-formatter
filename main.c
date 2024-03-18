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
    

    // STEP 1
    
    String S = remove_existing_formatting(buffer, length);
    printf("\nSTART======\n");
    printString(S);
    printf("======END\n");

    // STEP 2
    Tree T = getNewTree();
    // T->Line=makeString("Hello there");
    // T->child = getNewTree();
    // T->child->Line=makeString("This is cool");
    // T->child->nextSibling=getNewTree();
    // T->child->nextSibling->Line =makeString("This was uncalled for");
    // T->nextSibling=getNewTree();
    // T->nextSibling->Line=makeString("This is also cool");

    String p = makeTree(S,T);
    // // add_formatting(S);
    printTree(T, 0);

  }
}
