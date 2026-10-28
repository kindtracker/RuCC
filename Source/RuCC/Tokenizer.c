#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RuCC.h"

static bool IsIdent(char Character, bool NoNumber) {
  return ((!NoNumber ? isalpha(Character) : isalnum(Character)) ||
          Character == '_');
}

static char *Slice(const char *String, size_t Start, size_t End) {
  size_t ResultSize = End - Start;
  char *Result = malloc(ResultSize);
  strncpy(Result, String + Start, ResultSize);

  return Result;
}

#define GetIndex() Character - FileContent
int RuCCTokenize(RuCCState *State) {
  char *FileContent = State->FileContent;
  char *Character = FileContent;

  while (*Character) {
    if (IsIdent(*Character, false)) {
      int StartIndex = GetIndex();

      while (IsIdent(*Character, true)) {
        Character++;
      }

      const char *Ident = Slice(FileContent, StartIndex, GetIndex());

      printf("Ident %s\n", Ident);
    }

    Character++;
  }
}
