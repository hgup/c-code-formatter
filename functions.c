
#include "main.h"

void append(String S, char c);
int isFormatChar(char c);

String remove_existing_formatting(char* buffer, long length){

  String S = (String)malloc(sizeof(struct strNode)); // Dummy node
  int INSTRING = 0; // am I inside a string literal -1: No, +1: Yes
  Node t = S;
  t->next = NULL;

  for(int i = 0; i < length; i++ ){

    switch(buffer[i]){
      case '"':
        append(t, buffer[i]);
        t = t->next;
        if (INSTRING)
          INSTRING = 0; // switch INSTRING
        else
          INSTRING = 1;
        break;
      
      case '}':
      case '{':
      case ';':
      case '+':
      case '-':
      case '/':
      case '*':
      case '(':
      case ')':
        append(t, buffer[i]);
        t = t->next;
        if (!INSTRING)
          while(isFormatChar(buffer[i+1]))
            i++;
        // the next char is not a formatting character
        break;
      default:
        append(t, buffer[i]);
        t = t->next;
        break;
    }
  }
  return S;
}

void append(String S, char c){
  // while(S->next)
  //   S = S->next;
  
  S->next = (Node)malloc(sizeof(struct strNode));
  S = S->next;
  S->ch = c;
  S->next = NULL;
}

int isFormatChar(char c){
 if(c == '\n' || c == ' ' || c == '\t')
    return 1;
  return 0;
}

void printString(String S){
  Node t = S->next;
  printf("\nSTART======\n");
  while(t){
    printf("%c",t->ch);
    t = t->next;
  }
  printf("======END\n");
}
