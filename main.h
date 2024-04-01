
#ifndef standardIO

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

#endif // !standardIO

#ifndef formatter

  struct strNode {
    char ch;
    struct strNode* next;
  };

  typedef struct strNode* Node;
  typedef Node String;

  struct treeNode;
  typedef struct treeNode* TNode;
  typedef TNode Tree;

  struct treeNode {
    String Line;
    TNode child;
    TNode nextSibling;
  };

  typedef struct treeNode* TNode;
  typedef TNode Tree;

/*
 * Prints the string
 */
void printString(String S);

/*
 * Removes existing formatting from `buffer` string of length `length`
 *
 * NOTE: buffer gets modified
 */
String remove_existing_formatting(char* buffer, long length);


/*
 * adds good formatting to the String S
 */
void add_formatting(String S);

/*
 * type: 'n' means normal
 *       'c' means case from 'switch-case'
 */
String makeTree(String S, Tree OG_T, char type);

/*
 *
 */
void printTree(Tree T, int depth);

/*
 *
 */
void fprintString(String S, FILE* fp, int depth);

/*
 *
 */
void fprintTree(Tree T, int depth, FILE* fp);

String makeString(char *p);

Tree getNewTree();

#endif // !formatter
