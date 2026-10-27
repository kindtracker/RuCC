#pragma once

typedef struct {
  const char *FileContent;
} RuCCState;

RuCCState *RUCCNewState();
int RuCCCompile(RuCCState *State, const char *FileName);
