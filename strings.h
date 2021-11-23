/*
 * @Author: duapple
 * @Date: 2021-11-19 18:35:45
 * @LastEditTime: 2021-11-22 21:13:48
 * @LastEditors: duapple
 * @Description: Add description
 * @FilePath: /strings/strings.h
 * Copyright (c) 2011 duapple - All rights reserved.
 */
#ifndef __HJ_STRINGS_H__
#define __HJ_STRINGS_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// #define STRS_PLAT_HOOKS

#define strsFree(ptr)                                                                                                  \
    do {                                                                                                               \
        __strsFree(ptr);                                                                                               \
        ptr = NULL;                                                                                                    \
    } while (0)
#define strsFree2(ptr, size)                                                                                           \
    do {                                                                                                               \
        __strsFree2(ptr, size);                                                                                        \
        ptr = NULL;                                                                                                    \
    } while (0)

typedef struct {
    void *(*calloc)(size_t nmemb, size_t size);
    void (*free)(void *);
} strs_plat_hook_t;

int strsSetPlatHook(strs_plat_hook_t *hooks);

bool strsIsSpace(char ch);
bool strsIsNumber(char ch);
bool strsIsLetter(char ch);
bool strsIsUpLetter(char ch);
bool strsIsLowLetter(char ch);
bool strsIsEnd(const char ch);

char * strsloc(size_t size);
char **strsloc2(int row, int col);
size_t strsLen(const char *str);
int    println(const char *format, ...);
void   __strsFree(void *str);
void   __strsFree2(char **strList, int listSize);

char * strsReverse(char *str);
int    strsNum(const char *str);
char * strsDump(const char *str);
char * strsToupper(char *str);
char * strsTolower(char *str);
bool   strsContainChar(const char *str, char ch);
bool   strsContains(const char *str, const char *substr);
bool   strContainsAny(const char *str, const char *chars);
bool   strsEqualCase(const char *str1, const char *str2);
int    strsCount(const char *str, const char *substr);
char **strsFields(const char *str, int *listSize);
char **strsFieldsFunc(const char *str, bool (*func)(char ch), int *listSize);
bool   strsHasPrefix(const char *str, const char *prefix);
bool   strsHasSuffix(const char *str, const char *suffix);
int    strsIndex(const char *str, const char *substr);
char * strsJoin(const char *str1, const char *str2, const char *sep);
char * strsJoinN(const char *sep, int num, ...);
int    strsLastIndex(const char *str, const char *substr);
int    strsIndexAny(const char *str, const char *substr);
int    strsIndexChar(const char *str, char ch);
int    strsLastIndexChar(const char *str, char ch);
char * strsMap(char *str, char (*map)(char ch));
char * strsRepeat(const char *str, int num);
char * strsReplace(const char *str, const char *old, const char *new, int num);
char * strsReplaceAll(const char *str, const char *old, const char *new);
char * strsRemove(char *str, const char *substr);
char **strsSplit(const char *str, const char *sep, int *num);
char **strsSplitAfter(const char *str, const char *sep, int *num);
char **strsSplitAfterN(const char *str, const char *sep, int *num);
char * strsTitle(char *str);
char * strsTrim(char *str, const char *cutset);
char * strsTrimFunc(char *str, bool (*func)(char ch));
char * strsTrimLeft(char *str, const char *cutset);
char * strsTrimLeftFunc(char *str, bool (*func)(char ch));
char * strsTrimPrefix(char *str, const char *prefix);
char * strsTrimRight(char *str, const char *cutset);
char * strsTrimSpace(char *str);
char * strsTrimSuffix(char *str, const char *suffix);
char * strsInsert(const char *str, const char *substr, int pos);

#endif /* __HJ_STRINGS_H__ */
