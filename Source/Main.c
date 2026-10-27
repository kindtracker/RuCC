#include <stdio.h>

#include "RuCC.h"

int main(int Argc, char *Argv[]) {
  char *FileName = NULL;

  for (int Idx = 1; Idx < Argc; Idx++) {
    char *Argument = Argv[Idx];
    FileName = Argument;
  }

  RuCCState *State = RUCCNewState();

  if (FileName == NULL) {
    RuCCError(State, "UsageError", "No input files");
  }

  int Status = RuCCCompile(State, FileName);

  return Status;
}
