#pragma once

// Tokenizer:
// TODO: Remove comments
// TODO: Support more stuff in TokenNumber (Hex/binary numbers, etc)

// Parser:
// TODO: Implement function call
// TODO: Implement function declaration
// TODO: Implement variable declaration
// TODO: Implement variable assign
// TODO: Implement if
// TODO: Implement else
// TODO: Implement while
// TODO: Implement for (break and continue)
// TODO: Implement switch

typedef enum {
  RuCCTokenIdent,   // Implemented
  RuCCTokenKeyword, // Implemented
  RuCCTokenPunct,   // Implemented
  RuCCTokenString,  // Implemented
  RuCCTokenNumber   // Implemented
} RuCCTokenKind;

typedef enum {
  RuCCStatementFunctionCall, // Not Implemented
} RuCCStatementKind;

typedef struct RuCCToken RuCCToken;
struct RuCCToken {
  RuCCTokenKind Kind;
  void *Value;
  RuCCToken *Next;
};

typedef struct RuCCStatement RuCCStatement;
struct RuCCStatement {
  RuCCStatementKind Kind;
  void *Value;
  RuCCStatement *Body;
};

typedef struct {
  char *FileContent;
  char *FileName;
  RuCCToken *Tokens;
  RuCCStatement *Ast;
} RuCCState;

RuCCState *RUCCNewState();

void RuCCError(RuCCState *State, const char *Type, const char *Format, ...);

int RuCCCompile(RuCCState *State, char *FileName);
int RuCCTokenize(RuCCState *State);
int RuCCParse(RuCCState *State);
