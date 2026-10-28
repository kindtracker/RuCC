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
    if (isspace(*Character)) {
      Character++;
    }

    if (IsIdent(*Character, false)) {
      int StartIndex = GetIndex();

      while (IsIdent(*Character, true)) {
        Character++;
      }

      char *Ident = Slice(FileContent, StartIndex, GetIndex());
      Character--;

      bool IsKeyword = false;
      if (strcmp(Ident, "return") == 0 || strcmp(Ident, "if") == 0 ||
          strcmp(Ident, "else") == 0 || strcmp(Ident, "for") == 0 ||
          strcmp(Ident, "while") == 0 || strcmp(Ident, "int") == 0 ||
          strcmp(Ident, "sizeof") == 0 || strcmp(Ident, "char") == 0 ||
          strcmp(Ident, "struct") == 0 || strcmp(Ident, "union") == 0 ||
          strcmp(Ident, "short") == 0 || strcmp(Ident, "long") == 0 ||
          strcmp(Ident, "void") == 0 || strcmp(Ident, "typedef") == 0 ||
          strcmp(Ident, "_Bool") == 0 || strcmp(Ident, "enum") == 0 ||
          strcmp(Ident, "static") == 0 || strcmp(Ident, "goto") == 0 ||
          strcmp(Ident, "break") == 0 || strcmp(Ident, "continue") == 0 ||
          strcmp(Ident, "switch") == 0 || strcmp(Ident, "case") == 0 ||
          strcmp(Ident, "default") == 0 || strcmp(Ident, "extern") == 0 ||
          strcmp(Ident, "_Alignof") == 0 || strcmp(Ident, "_Alignas") == 0 ||
          strcmp(Ident, "do") == 0 || strcmp(Ident, "signed") == 0 ||
          strcmp(Ident, "unsigned") == 0 || strcmp(Ident, "const") == 0 ||
          strcmp(Ident, "volatile") == 0 || strcmp(Ident, "auto") == 0 ||
          strcmp(Ident, "register") == 0 || strcmp(Ident, "restrict") == 0 ||
          strcmp(Ident, "__restrict") == 0 ||
          strcmp(Ident, "__restrict__") == 0 ||
          strcmp(Ident, "_Noreturn") == 0 || strcmp(Ident, "float") == 0 ||
          strcmp(Ident, "double") == 0 || strcmp(Ident, "typeof") == 0 ||
          strcmp(Ident, "asm") == 0 || strcmp(Ident, "_Thread_local") == 0 ||
          strcmp(Ident, "__thread") == 0 || strcmp(Ident, "_Atomic") == 0 ||
          strcmp(Ident, "__attribute__") == 0) {
        IsKeyword = true;
      }

      Token->Kind = IsKeyword ? RuCCTokenKeyword : RuCCTokenIdent;
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
    } else if (isdigit(*Character)) {
      int StartIndex = GetIndex();

      while (isdigit(*Character) || *Character == '.') {
        Character++;
      }

      char *String = Slice(FileContent, StartIndex, GetIndex());
      double Number = atof(String);

      double *NumberPointer = malloc(sizeof(double));
      memcpy(NumberPointer, &Number, sizeof(double));

      Token->Kind = RuCCTokenNumber;
      Token->Value = NumberPointer;
      NewToken();
    } else {
      RuCCError(State, "SyntaxError", "Unexpected character: '%c'", *Character);
    }

    Character++;
  }
}
