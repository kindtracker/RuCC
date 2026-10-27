#include <stdio.h>

#include "Include/RuCC.h"

int main(int Argc, char *Argv[]) {
  char *FileName = NULL;

  for (int Idx = 1; Idx < Argc; Idx++) {
    char *Argument = Argv[Idx];
    FileName = Argument;
  }

  if (FileName == NULL) {
    fprintf(stderr, "RuCC: Error: No input files\n");
    return 1;
  }

  int Status = RuCCCompile(FileName);

  return Status;
}
