#include <stdio.h>
#include <stdlib.h>

#include "Include/RuCC.h"

int RuCCCompile(const char *FileName) {
  FILE *FilePtr = fopen(FileName, "r");

  if (!FilePtr) {
    fprintf(stderr, "RuCC: Error: Failed to open %s\n", FileName);
    return 1;
  }

  fseek(FilePtr, 0, SEEK_END);
  size_t Size = ftell(FilePtr);
  fseek(FilePtr, 0, SEEK_SET);

  const char *FileContent = malloc(Size);
  fgets(FileContent, Size, FilePtr);

  puts(FileContent);

  return 0;
}
