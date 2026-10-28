#pragma once

typedef enum { RuCCTokenIdent } RuCCTokenKind;

typedef struct {
  char *FileContent;
  char *FileName;
} RuCCState;

typedef struct {
  const char *Kind;
  void *Value;
  RuCCState *NextToken;
} RuCCToken;

RuCCState *RUCCNewState();

void RuCCError(RuCCState *State, const char *Type, const char *Format, ...);

int RuCCCompile(RuCCState *State, char *FileName);
int RuCCTokenize(RuCCState *State);
