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
#define NewToken()                                                             \
  Token->NextToken = malloc(sizeof(RuCCToken));                                \
  Token = Token->NextToken;                                                    \
  memset(Token, 0, sizeof(RuCCToken))

int RuCCTokenize(RuCCState *State) {
  char *FileContent = State->FileContent;
  char *Character = FileContent;

  RuCCToken *Token = malloc(sizeof(RuCCToken));
  memset(Token, 0, sizeof(RuCCToken));
  State->Tokens = Token;

  while (*Character) {
    if (IsIdent(*Character, false)) {
      int StartIndex = GetIndex();

      while (IsIdent(*Character, true)) {
        Character++;
      }

      char *Ident = Slice(FileContent, StartIndex, GetIndex());
      Character--;

      Token->Kind = RuCCTokenIdent;
      Token->Value = Ident;
      NewToken();
    } else if (*Character == '\"') {
      Character++;
      int StartIndex = GetIndex();

      while (*Character != '\"') {
        Character++;
      }

      Character--;
      char *String = Slice(FileContent, StartIndex, GetIndex());
      Character++;

      Token->Kind = RuCCTokenString;
      Token->Value = String;
      NewToken();
    } else if (*Character == '(' || *Character == ')' || *Character == '{' ||
               *Character == '}' || *Character == '[' || *Character == ']' ||
               *Character == ';' || *Character == ',' || *Character == ':' ||
               *Character == '.') {
      Token->Kind = RuCCTokenPunct;
      Token->Value = Character;
      NewToken();
    } else {
      RuCCError(State, "SyntaxError", "Unexpected character: '%c'", *Character);
    }

    Character++;
  }
}
