
#include "main.h"
#include <stdlib.h>

void attach(String S, char c);
int isFormatChar(char c);
void attachTabs(Node t, int ID);
int isInlineFormatChar(char c);

Node newNode(char c){
  Node N = (Node)malloc(sizeof(struct strNode));
  N->next= NULL;
  N->ch = c;
  return N;
}

void attachTabs(Node t, int ID ){
  t->next = (Node)malloc(sizeof(struct strNode));
  t = t->next;
  t->ch = '\n';
  
  for(int i = 0; i < ID; i++){
    t->next = (Node)malloc(sizeof(struct strNode));
    t = t->next;
    t->ch = '\t';
  }
  t->next = NULL;
}

void printDepth(int d){
  for(int i = 0; i<d; i++){
    printf("   ");
  }
}

Tree getNewTree(){
  Tree T = (Tree) malloc(sizeof(struct treeNode));
  T->nextSibling = NULL;
  T->Line = NULL;
  T->child = NULL;
  return T;
}
String makeString(char *p){
  String S = (String)malloc(sizeof(struct strNode));
  String t = S;
  while(*p){
    t->next = (Node)malloc(sizeof(struct strNode));
    t = t->next;
    t->ch = *p;
    p++;
  }
  t->next = NULL;
  return S;
}

int isThis(String S, char *str){
  while(*str){
    if (S){
      if (S->ch != *str)
        return 0; //false
       }
    else {
      return 0;
    }
    str++;
    S = S->next;
  }
  return 1;
}

// NOTE: You always return and call the function with a dummy node
String makeTree(String S, Tree T, char type){
  int balance = 0;
  int for_col_count = 0;

  T->Line = S;
  String p;
  while(S->next){
    p = NULL;
    switch(S->next->ch){
      case 'f':
        if(isThis(S->next->next, "or(")){
          balance = 0;
          for_col_count = 0;
          while(balance != 0 || for_col_count != 2){
            S = S->next;
            if (S->next->ch == ';')
              for_col_count++;
            if (S->next->ch == '(')
              balance++;
            if (S->next->ch == ')')
              balance--;
          }
          p = S->next;
          S->next = (String)malloc(sizeof(struct strNode));
          S->next->ch = ')';
          S->next->next = NULL;
          T->nextSibling = getNewTree();
          T = T->nextSibling;
          T->Line = p;
          break;
        }
        break;
      // case ':':
      //     printString(S->next);
      //     printf("\n\n");
      //     p = S->next;
      //     S->next = newNode(':');
      //     T->child = getNewTree();
      //     p = makeTree(p,T->child,'c'); // passed '{' node as dummy
      //   break;
      case '{':
        // whatever scanned till now will go to current line
        p = S->next;
        S->next = NULL;
        T->child = getNewTree();
        p = makeTree(p,T->child,'n'); // passed '{' node as dummy
        break;
      case '}':
        p = S->next;
        S->next = NULL;
        return p; // treated '}' node as dummy
        break;
      // case '\n':
      case ';':
        p = S->next;
        S->next = (String)malloc(sizeof(struct strNode));
        S->next->ch = ';';
        S->next->next = NULL;
        T->nextSibling = getNewTree();
        T = T->nextSibling;
        T->Line = p;
        break;
      default:
        break;
    }
    if (p)
      S = p;
    else
      S = S->next;
    }
  return NULL;
}

String remove_existing_formatting(char* buffer, long length){

  String S = (String)malloc(sizeof(struct strNode)); // Dummy node
  int INSTRING = 0; // am I inside a string literal 0: No, 1: Yes
  Node p, q, t = S;
  t->next = NULL;

  for(int i = 0; i < length; i++ ){

    switch(buffer[i]){
      case '#':
        while(buffer[i] != '\n'){
          attach(t,buffer[i++]);
          t = t->next;
        }
        attach(t,'\n');
        t = t->next;
        break;
      case '"':
        attach(t, buffer[i]);
        t = t->next;
        if (INSTRING && buffer[i-1]!='\\')
          INSTRING = 0; // switch INSTRING
        else
          INSTRING = 1;
        break;
      
      case '}':
        attach(t, buffer[i]);
        t = t->next;
        attach(t,';');
        t = t->next;
        if (!INSTRING)
          while(isFormatChar(buffer[i+1]))
            i++;
        break;
      case '{':
      case ';':
      case '=':
      case '+':
      case ',':
      case ':':
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
  INSTRING = 0;

  while(t->next){
    if (t->ch == '"'){
        if (INSTRING)
          INSTRING = 0; // switch INSTRING
        else
          INSTRING = 1;
    }
    if (!INSTRING && isInlineFormatChar(t->next->ch)){
      // skip all format chars if the other end has  , \{, ;... etc
      // otherwise replace all format chars with one space
      p = t->next;
      while(isInlineFormatChar(p->ch)){
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
        case ':':
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
  attach(t,'\n');

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

int isInlineFormatChar(char c){
 if( c == ' ' || c == '\t')
    return 1;
  return 0;
}


void printString(String S){
  Node t = S->next;
  while(t){
    printf("%c",t->ch);
    t = t->next;
  }
}

void printTree(Tree T, int depth){
  while(T){
    // printf("[%d]\t",depth);
    if(T->child){
      if (T->Line->next != NULL){
      // printf("\n");
      printDepth(depth);
      printString(T->Line);
      printf("\n");
      }
      printDepth(depth);
      printf("{\n");
      printTree(T->child, depth+1);
      printDepth(depth);
      printf("}\n");
    } else {
      if(T->Line->next != NULL){
        printDepth(depth);
        printString(T->Line);
        printf("\n");
      }
    }
    T = T->nextSibling;
    if(depth == 0){
      printf("\n\n");
    }
  }
}

void fprintDepth(int d, FILE *fp){
  for(int i = 0; i<d; i++){
    fprintf(fp,"   ");
  }
}

void fprintString(String S, FILE *fp){
  Node t = S->next;
  while(t){
    fprintf(fp,"%c",t->ch);
    t = t->next;
  }
}

void fprintTree(Tree T, int depth, FILE* fp){
  while(T){
    // printf("[%d]\t",depth);
    if(T->child){
      if (T->Line->next != NULL){
      // printf("\n");
      fprintDepth(depth,fp);
      fprintString(T->Line,fp);
      fprintf(fp,"\n");
      }
      fprintDepth(depth,fp);
      fprintf(fp,"{\n");
      fprintTree(T->child, depth+1, fp);
      fprintDepth(depth,fp);
      fprintf(fp,"}\n");
    } else {
      if(T->Line->next != NULL){
        fprintDepth(depth,fp);
        fprintString(T->Line,fp);
        fprintf(fp,"\n");
      }
    }
    T = T->nextSibling;
    if(depth == 0){
      fprintf(fp,"\n\n");
    }
  }
}
