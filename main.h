
#ifndef standardIO

  #include <stdio.h>
  #include <stdlib.h>

#endif // !standardIO

#ifndef formatter

  struct strNode {
    char ch;
    struct strNode* next;
  };

  typedef struct strNode* Node;
  typedef Node String;

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

#endif // !formatter
