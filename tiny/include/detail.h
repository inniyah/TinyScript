#pragma once

#include "lexer.h"
#include "tiny.h"
#include "arena.h"

#define MAX_NUMBERS 512
#define MAX_STRINGS 1024

typedef unsigned char Word;

typedef struct Tiny_Object {
    bool marked;

    Tiny_ValueType type;
    struct Tiny_Object *next;

    union {
        struct {
            size_t len;
            // NOTE(Apaar): If the user calls "NewStringWithLen" then this is just
            // a pointer to the same allocation as this object!
            //
            // Otherwise (if calling NewString)
            char *ptr;
        } string;

        struct {
            void *addr;
            const Tiny_NativeProp *prop;  // Can be used to check type of native (ex. obj->nat.prop
                                          // == &ArrayProp // this is an Array)
        } nat;

        struct {
            Word n;
            Tiny_Value fields[];
        } ostruct;
    };
} Tiny_Object;

typedef struct Tiny_PCToFileLine {
    int pc;
    int fileStrIndex;
    int line;
} Tiny_PCToFileLine;

typedef struct Tiny_State {
    Tiny_Context ctx;

    // Program info
    Word *program;  // array

    int numStrings;
    char *strings[MAX_STRINGS];

    int numGlobalVars;

    int numFunctions;
    int *functionPcs;

    int numForeignFunctions;
    Tiny_ForeignFunction *foreignFunctions;

    // Compiler Info
    int currScope;
    Tiny_Symbol *currFunc;

    Tiny_Symbol **globalSymbols;  // array

    // We keep information about what file and line number
    // correspond to what PC. It is sorted by PC so we should
    // be able to do a lookup in log(n) time.
    Tiny_PCToFileLine *pcToFileLine;  // array

    Tiny_Lexer l;

    // Ephemeral arena for the parser. Storing it on state so we
    // don't have to drill it into every parser function.
    Tiny_Arena parserArena;
} Tiny_State;
