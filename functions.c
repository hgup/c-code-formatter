
#include "main.h"

void attach(String S, char c);
int isFormatChar(char c);

String remove_existing_formatting(char* buffer, long length){

  String S = (String)malloc(sizeof(struct strNode)); // Dummy node
  int INSTRING = 0; // am I inside a string literal -1: No, +1: Yes
  Node p, q, t = S;
  t->next = NULL;

  for(int i = 0; i < length; i++ ){

    switch(buffer[i]){
      case '"':
        attach(t, buffer[i]);
        t = t->next;
        if (INSTRING)
          INSTRING = 0; // switch INSTRING
        else
          INSTRING = 1;
        break;
      
      case '}':
      case '{':
      case ';':
      case '=':
      case '+':
      case ',':
      case '-':
      case '/':
      case '*':
      case '(':
      case ')':
        attach(t, buffer[i]);
        t = t->next;
        if (!INSTRING)
          while(isFormatChar(buffer[i+1]))
            i++;
        // the next char is not a formatting character
        break;
      default:
        attach(t, buffer[i]);
        t = t->next;
        break;
    }
  }

  // for the preceeding formatting characters
  t = S->next;

  while(t->next){
    if (isFormatChar(t->next->ch)){
      // skip all format chars if the other end has  , \{, ;... etc
      // otherwise replace all format chars with one space
      p = t->next;
      while(isFormatChar(p->ch)){
        q = p->next;
        free(p);
        p = q;
      }
      switch(p->ch){
        case '}':
        case '{':
        case ';':
        case '=':
        case ',':
        case '+':
        case '-':
        case '/':
        case '*':
        case '(':
        case ')':
          t->next = p;
          break;
        default:
          attach(t,' ');
          t = t->next;
          t->next = p;
          break;
      }
    }
    t = t->next;
  }

  return S;
}

void attach(Node t, char c){
  // while(S->next)
  //   S = S->next;
  
  t->next = (Node)malloc(sizeof(struct strNode));
  t = t->next;
  t->ch = c;
  t->next = NULL;
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
