#include <stdlib.h>
#include <stdio.h>
#include "ex2.h"

#define DOUBLE_2_FORMAT "%.2lf"
#define ARGC_ERROR_MSG "ERROR: Wrong number of arguments.\nUsage: main <path to file>\n"

// main to run functions from Ex2
int main(int argc, char *argv[]){
  if (argc < 2){
    fprintf(stderr, ARGC_ERROR_MSG);
    return EXIT_FAILURE;  // EXIT_FAILURE is a macro for 1. Only to be used as return value from main or
    // parameter to exit()! Don't use it to replace 1 in function return value etc.
  }
  LinkedList *list = ParseLinkedList(argv[1]); // use of trenary: (condition) ? value if true: value if false
  size_t n = 0; // will contain the number of elements in the returned array after call to getAverage(list,&n)
  Node *node = calloc(1, sizeof(Node));
  AddToStartLinkedList(list, node);
  double *averageList = GetAverages(list, &n);
  for (size_t i = 0; i < n; ++i){
    printf(DOUBLE_2_FORMAT, averageList[i]);
    if (i != n - 1){
      printf(", ");
    }
  }
  printf("\n");
  free(averageList);
  FreeLinkedList(list); // not setting to NULL as the program is terminated after the free
  return EXIT_SUCCESS; // macro for 0. Like EXIT_FAILURE, not to be used for function return values!!
}
