#include "main.h"
String makeTree(String S, Tree OG_T){

  Tree T = OG_T;
  T->nextSibling = NULL;
  T->child = NULL;
  String p;

  S = S->next; // skip the dummy
  while(S && S->ch != '}'){ // stop when S is null or you reach a '}' character

      T->Line = (String)malloc(sizeof(struct strNode)); // this is the dummy
      T->Line->next = S;
      T->nextSibling = NULL;
      p = NULL; // if no {block} business happens
      while(S->ch != '\n' && S->ch != ';') 
      {
        if (S->next && S->next->ch == '{'){
          p = S->next->next; // first char in the {block} (business happened)
          free(S->next); // remove `{`
          S->next = NULL;

          T->child = (Tree) malloc(sizeof(struct treeNode)); // dummy
          p = makeTree(p, T->child);
          break;
        }
        S = S->next;
      }
      if(!p){ // if none of that {block} business happened
       p = S->next;
        S->next = NULL; // cut the line for T->Line = S
      }
      S = p;
      T->nextSibling = (Tree) malloc(sizeof(struct treeNode));
      T = T->nextSibling;
  }
  T->child = NULL;
  T->Line = NULL;
  p = S->next;
  free(S); // remove '}'
  return p;
}
