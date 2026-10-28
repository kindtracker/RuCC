#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "RuCC.h"

#define AnsiReset "\x1b[0m"
#define AnsiYellow "\x1b[33m"
#define AnsiRed "\x1b[31m"
#define AnsiRuCC "\x1b[1;37m"
#define AnsiLuaBlue "\x1b[38;2;100;200;255m"

void RuCCError(RuCCState *State, const char *Type, const char *Format, ...) {
  if (State->FileName) {
    fprintf(stderr, AnsiRuCC "RuCC: " AnsiReset "%s: " AnsiRed "%s: " AnsiReset,
            State->FileName, Type);
  } else {
    fprintf(stderr, AnsiRuCC "RuCC: " AnsiRed "%s: " AnsiReset, Type);
  }

  va_list Args;
  va_start(Args, Format);
  vfprintf(stderr, Format, Args);
  va_end(Args);

  fputc('\n', stderr);
  exit(1);
}
