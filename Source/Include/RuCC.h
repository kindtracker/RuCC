#pragma once

typedef enum { RuCCTokenIdent } RuCCTokenKind;

typedef struct RuCCToken RuCCToken;
struct RuCCToken {
  const char *Kind;
  void *Value;
  RuCCToken *NextToken;
};

typedef struct {
  char *FileContent;
  char *FileName;
  RuCCToken *Tokens;
} RuCCState;

RuCCState *RUCCNewState();

void RuCCError(RuCCState *State, const char *Type, const char *Format, ...);

int RuCCCompile(RuCCState *State, char *FileName);
int RuCCTokenize(RuCCState *State);
