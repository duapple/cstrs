#ifndef __HJ_STRINGS_H__
#define __HJ_STRINGS_H__

#include <stdbool.h>
#include <stdlib.h>

int println(const char *format, ...);

void strsFree(void *str);

char *strsToupper(char *str);

char *strsTolower(char *str);

char *strsReverse(char *str);

int strsCount(const char *str, const char *substr);

int strsNum(const char *str);

bool strsIsSpace(const char ch);

size_t strsLen(const char *str);

int strsFields(const char *str, char ***strList, int *listSize);

void strsFree2(char **strList, int listSize);

bool strsIsEnd(const char ch);

char *strsloc(size_t size);

char **strsloc2(int row, int col);

bool strsHasPrefix(const char *str, const char *prefix);

bool strsHasSuffix(const char *str, const char *suffix);

int strsIndex(const char *str, const char *substr);

char *strsJoin(const char *str1, const char *str2, const char *sep);

char *strsJoinN(const char *sep, int num, ...);

int strsLastIndex(const char *str, const char *substr);

int strsIndexAny(const char *str, const char *substr);

char *strsMap(char *str, char (*map)(char ch));

char *strsRepeat(const char *str, int num);

char *strsReplace(const char *str, const char *old, const char *new, int num);

char *strsReplaceAll(const char *str, const char *old, const char *new);

char *strsRemove(char *str, const char *substr);

#endif /* __HJ_STRINGS_H__ */
