#include <stddef.h>

#include "RuCC.h"

static RuCCToken *Token;

RuCCStatement *RuCCParseStatement(RuCCState *State) { return NULL; }

int RuCCParse(RuCCState *State) {
  Token = State->Tokens;

  while (Token != NULL) {
    RuCCStatement *Statement = RuCCParseStatement(State);

    Token = Token->Next;
  }
}
