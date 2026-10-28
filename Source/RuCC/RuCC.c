#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RuCC.h"

RuCCState *RUCCNewState() {
  RuCCState *State = malloc(sizeof(RuCCState));
  memset(State, 0, sizeof(RuCCState));

  return State;
}

int RuCCCompile(RuCCState *State, char *FileName) {
  FILE *FilePtr = fopen(FileName, "r");

  if (!FilePtr) {
    RuCCError(State, "IoError", "Failed to open %s", FileName);
  }

  State->FileName = FileName;

  fseek(FilePtr, 0, SEEK_END);
  size_t Size = ftell(FilePtr);
  fseek(FilePtr, 0, SEEK_SET);

  char *FileContent = malloc(Size);
  fgets(FileContent, Size, FilePtr);
  State->FileContent = FileContent;

  RuCCTokenize(State);
  RuCCParse(State);

  free(FileContent);
  return 0;
}
