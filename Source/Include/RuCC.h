#pragma once

typedef struct {
  char *FileContent;
} RuCCState;

typedef struct {
  const char *Kind;
  void *Value;
  RuCCState *NextToken;
} RuCCToken;

RuCCState *RUCCNewState();
int RuCCCompile(RuCCState *State, const char *FileName);
int RuCCTokenize(RuCCState *State);
