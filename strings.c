/*
 * @Author: duapple
 * @Date: 2021-11-17 21:42:40
 * @LastEditTime: 2021-11-22 21:17:04
 * @LastEditors: duapple
 * @Description: Add description
 * 
 * @FilePath: /strings/strings.c
 * Copyright (c) 2011 duapple - All rights reserved.
 */
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strings.h"

#define LOG_INFO(...)  println(__VA_ARGS__)
#define LOG_ERROR(...) println(__VA_ARGS__)
#define CHECK_RET(rule, value)                                                                                         \
    do {                                                                                                               \
        if (!(rule)) {                                                                                                 \
            LOG_ERROR("rules false");                                                                                  \
            return value;                                                                                              \
        }                                                                                                              \
    } while (0)
#define CHECK_RET_PTR(rule)  CHECK_RET(rule, NULL)
#define CHECK_RET_INT(rule)  CHECK_RET(rule, -1)
#define CHECK_RET_BOOL(rule) CHECK_RET(rule, false)

#ifdef STRS_PLAT_HOOKS
static strs_plat_hook_t phook;
#else
static strs_plat_hook_t phook = {.calloc = calloc, .free = free};
#endif

/**
 * @description: 设置平台hooks，注册calloc和free函数
 * @param {strs_plat_hook_t} *hooks
 * @return {*}
 */
int strsSetPlatHook(strs_plat_hook_t *hooks)
{
    CHECK_RET_INT(hooks && hooks->calloc && hooks->free);
    phook.calloc = hooks->calloc;
    phook.free   = hooks->free;
    return 0;
}

/**
 * @description: 判断字符是否是空白字符
 * @param {char} ch
 * @return {*}
 */
bool strsIsSpace(char ch)
{
    if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
        return true;
    }
    return false;
}

/**
 * @description: 判断字符是否是数字
 * @param {char} ch
 * @return {*}
 */
bool strsIsNumber(char ch)
{
    if (ch >= '0' && ch <= '9')
        return true;
    return false;
}

/**
 * @description: 判断字符是否是字母
 * @param {char} ch
 * @return {*}
 */
bool strsIsLetter(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return true;
    return false;
}

/**
 * @description: 判断字符是否是大写字母
 * @param {char} ch
 * @return {*}
 */
bool strsIsUpLetter(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
        return true;
    return false;
}

/**
 * @description: 判断字符是否是小写字母
 * @param {char} ch
 * @return {*}
 */
bool strsIsLowLetter(char ch)
{
    if (!strsIsUpLetter(ch))
        return true;
    return false;
}

/**
 * @description: 为字符串分配存储空间，已经对存储空间进行初始化，需要free
 * @param {size_t} size
 * @return {*}
 */
char *strsloc(size_t size)
{
    return (char *)phook.calloc(size, sizeof(char));
}

/**
 * @description: 为字符串列表分配空间，需要strsFree2()释放
 * @param {char} *
 * @param {int} row
 * @param {int} col
 * @return {*}
 */
char **strsloc2(int row, int col)
{
    CHECK_RET_PTR((row > 0) && (col > 0));
    char **strList = phook.calloc(row, sizeof(char *));
    for (int i = 0; i < row; i++) {
        strList[i] = phook.calloc(col, sizeof(char));
    }
    return strList;
}

/**
 * @description: 字符串包含结束符的长度
 * @param {char} *str
 * @return {*}
 */
size_t strsLen(const char *str)
{
    CHECK_RET_INT(str);
    return strlen(str) + 1;
}

/**
 * @description: 是否是结束符
 * @param {char} ch
 * @return {*}
 */
bool strsIsEnd(const char ch)
{
    if (ch == '\0')
        return true;
    return false;
}

/**
 * @description: 字符串翻转
 * @param {char} *str
 * @return {*}
 */
char *strsReverse(char *str)
{
    CHECK_RET_PTR(str);
    size_t size = strsLen(str);
    char * buff = strsloc(size);
    for (int i = 0, max = strlen(str), j = max - 1; i < max; i++, j--) {
        buff[j] = str[i];
    }
    memcpy(str, buff, size);
    strsFree(buff);
    return str;
}

/**
 * @description: 字符串中子串的数量
 * @param {char} *str
 * @return {*}
 */
int strsNum(const char *str)
{
    CHECK_RET_INT(str);
    size_t strLen = strlen(str);
    int    index  = 0;
    int    offset = 0;
    int    num    = 0;
    for (int i = 0; i < strLen + 1; i++) {
        if (strsIsSpace(str[i]) || strsIsEnd(str[i])) {
            if (offset > index) {
                num++;
            }
            index = offset;
            index++;
            offset++;
        } else {
            offset++;
        }
    }
    return num;
}

/**
 * @description: 字符串打印函数，自动换行
 * @param {char} *format
 * @return {*}
 */
int println(const char *format, ...)
{
    CHECK_RET_INT(format);
    int     ret;
    va_list arg;
    va_start(arg, format);
    ret = vprintf(format, arg);
    putchar('\n');
    va_end(arg);
    return ret;
}

/**
 * @description: 释放空间，并将指针置空
 * @param {char} *str
 * @return {*}
 */
void __strsFree(void *str)
{
    if (str == NULL)
        return;
    phook.free(str);
}

/**
 * @description: 释放字符串列表申请的内存空间
 * @param {char} *
 * @param {int} listSize
 * @return {*}
 */
void __strsFree2(char **strList, int listSize)
{
    if (strList == NULL)
        return;
    for (int i = 0; i < listSize; i++) {
        if (strList[i] == NULL)
            continue;
        phook.free(strList[i]);
    }
    phook.free(strList);
}

/**
 * @description: 字符串转为全大写
 * @param {char} *str
 * @return {*}
 */
char *strsToupper(char *str)
{
    CHECK_RET_PTR(str);
    size_t strLen = strlen(str);
    for (int i = 0; i < strLen; i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

/**
 * @description: 字符串转为全小写
 * @param {char} *str
 * @return {*}
 */
char *strsTolower(char *str)
{
    CHECK_RET_PTR(str);
    size_t strLen = strlen(str);
    for (int i = 0; i < strLen; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

/**
 * @description: 统计子串substr在字符串str中出现过多少次
 * @param {char} *str
 * @param {char} *substr
 * @return {*}
 */
int strsCount(const char *str, const char *substr)
{
    CHECK_RET_INT(str && substr);
    size_t offset    = 0;
    size_t strLen    = strlen(str);
    size_t substrLen = strlen(substr);
    int    count     = 0;
    for (; offset < strLen;) {
        char *strIndex = strstr(str + offset, substr);
        if (strIndex == NULL) {
            break;
        }
        count++;
        offset = strIndex - str + substrLen;
    }
    return count;
}

/**
 * @description: 将字符串分割为子串，根据空白进行分割，需要使用strsFree()释放
 * @param {char} *str
 * @param {char} *
 * @param {int} *listSize
 * @return {*}
 */
char **strsFields(const char *str, int *listSize)
{
    CHECK_RET_PTR(str && listSize);
    int    num      = strsNum(str);
    char **strList  = phook.calloc(num, sizeof(char *));
    int    index    = 0;
    int    offset   = 0;
    size_t buffSize = strsLen(str);
    char * buff     = strsloc(buffSize);
    *listSize       = num;
    for (int i = 0, j = 0; i < buffSize && j < num; i++) {
        if (strsIsSpace(str[i]) || strsIsEnd(str[i])) {
            if (offset > index) {
                sscanf(str + index, "%s", buff);
                int strSize = strsLen(buff);
                strList[j]  = strsloc(strSize);
                memcpy(strList[j], buff, strSize);
                memset(buff, 0, buffSize);
                j++;
            }
            index = offset;
            index++;
            offset++;
        } else
            offset++;
    }
    return strList;
}

/**
 * @description: 字符串str是否拥有字符串prefix前缀
 * @param {char} *str
 * @param {char} *prefix
 * @return {*}
 */
bool strsHasPrefix(const char *str, const char *prefix)
{
    CHECK_RET_BOOL(str && prefix);
    size_t size = strlen(prefix);
    if (size == 0)
        return true;

    for (int i = 0; i < size; i++) {
        if (str[i] != prefix[i]) {
            return false;
        }
    }
    return true;
}

/**
 * @description: 字符串str是否拥有字符串suffix后缀
 * @param {char} *str
 * @param {char} *suffix
 * @return {*}
 */
bool strsHasSuffix(const char *str, const char *suffix)
{
    CHECK_RET_BOOL(str && suffix);
    size_t size1 = strlen(suffix);
    size_t size2 = strlen(str);
    if (size1 == 0) {
        return true;
    }
    for (int i = 0, k = size1 - 1, j = size2 - 1; i < size1; i++, j--, k--) {
        if (str[j] != suffix[k]) {
            return false;
        }
    }
    return true;
}

/**
 * @description: 子串substr出现在str中的位置
 * @param {char} *str
 * @param {char} *substr
 * @return {*}
 */
int strsIndex(const char *str, const char *substr)
{
    CHECK_RET_INT(str && substr);
    char *pos = strstr(str, substr);
    if (pos == NULL) {
        return -1;
    }
    return pos - str;
}

/**
 * @description: 拼接两个字符创，将sep作为分割。需要free
 * @param {char} *str1
 * @param {char} *str2
 * @param {char} *sep
 * @return {*}
 */
char *strsJoin(const char *str1, const char *str2, const char *sep)
{
    CHECK_RET_PTR(str1 && str2 && sep);
    size_t size = strlen(str1) + strlen(str2) + strlen(sep) + 1;
    char * dst  = strsloc(size);
    strcat(dst, str1);
    strcat(dst, sep);
    strcat(dst, str2);
    return dst;
}

/**
 * @description: 拼接num个字符串，将sep作为分割。需要free
 * @param {char} *sep
 * @param {int} num
 * @return {*}
 */
char *strsJoinN(const char *sep, int num, ...)
{
    CHECK_RET_PTR(sep && (num > 0));
    size_t  size = 0;
    va_list arg;
    va_start(arg, num);
    for (int i = 0; i < num; i++) {
        size += strlen(va_arg(arg, char *));
    }
    va_end(arg);

    char *dst = strsloc(size + 1 + strlen(sep) * num);
    va_start(arg, num);
    for (int i = 0; i < num; i++) {
        strcat(dst, va_arg(arg, char *));
        if (i != num - 1) {
            strcat(dst, sep);
        }
    }
    va_end(arg);
    return dst;
}

/**
 * @description: 返回子串substr在字符串str中最后一次出现的位置
 * @param {char} *str
 * @param {char} *substr
 * @return {*}
 */
int strsLastIndex(const char *str, const char *substr)
{
    CHECK_RET_INT(str && substr);
    int    index  = 0;
    int    offset = 0;
    int    pos    = -1;
    size_t size   = strlen(substr);
    index         = strsIndex(str, substr);
    for (; index >= 0; index = strsIndex(str + offset, substr)) {
        pos = index + offset;
        offset += index + size;
    }
    return pos;
}

/**
 * @description: 检索字符串 str1 中第一个匹配字符串 str2 中字符的字符，不包含空结束字符。
 * 也就是说，依次检验字符串 str1 中的字符，当被检验字符在字符串 str2 中也包含时，则停止检验，并返回该字符位置。
 * @param {char} *str
 * @param {char} *substr
 * @return {*}
 */
int strsIndexAny(const char *str, const char *substr)
{
    CHECK_RET_INT(str && substr);
#if 1
    size_t size = strsLen(str);
    char * buff = strsloc(size);
    memcpy(buff, str, size);
    strsReverse(buff);
    char *pos = strpbrk(buff, substr);
    strsFree(buff);
    if (pos == NULL) {
        return -1;
    }
    int index = pos - buff;
    return size - 2 - index;
#else
    size_t size   = strlen(substr);
    int    maxPos = -1;
    for (int i = 0; i < size; i++) {
        char *index = strrchr(str, substr[i]);
        if (index == NULL)
            continue;
        int pos = strsIndex(str, index);
        maxPos  = maxPos > pos ? maxPos : pos;
    }
    return maxPos;
#endif
}

/**
 * @description: 使用map的字符的映射规则生成新的字符串
 * @param {char} *str
 * @param {char} ch
 * @return {*}
 */
char *strsMap(char *str, char (*map)(char ch))
{
    CHECK_RET_PTR(str && map);
    size_t size = strlen(str);
    for (int i = 0; i < size; i++) {
        str[i] = map(str[i]);
    }
    return str;
}

/**
 * @description: 复制字符串str num次，并拼接到一起。需要strsFree()
 * @param {char} *str
 * @param {int} num
 * @return {*}
 */
char *strsRepeat(const char *str, int num)
{
    CHECK_RET_PTR(str && (num >= 0));
    size_t size = strlen(str);
    char * dst  = strsloc(size * num + 1);
    for (int i = 0; i < num; i++) {
        strcat(dst, str);
    }
    return dst;
}

/**
 * @description: 将字符串str中的字符串old部分替换为字符串new。需要strsFree()
 * @param {char} *str
 * @param {char} *old
 * @param {char} *new
 * @param {int} num   <0时，全部替换
 * @return {*}
 */
char *strsReplace(const char *str, const char *old, const char *new, int num)
{
    CHECK_RET_PTR(str && old && new);
    if (num < 0) {
        return strsReplaceAll(str, old, new);
    }

    size_t size1 = strlen(str);
    size_t size2 = strlen(old);
    size_t size3 = strlen(new);

    int cnt = strsCount(str, old);
    if (cnt <= 0) {
        char *buff = strsloc(size1 + 1);
        memcpy(buff, str, size1);
        return buff;
    }

    char * dst  = NULL;
    size_t diff = size3 - size2;
    if (diff > 0) {
        dst = strsloc(size1 + cnt * (diff) + 1);
    } else {
        dst = strsloc(size1 + 1);
    }

    int pos   = 0;
    int index = strsIndex(str, old);
    for (int j = 0;; j++) {
        if (index >= 0 && j < num) {
            strncat(dst, str + pos, index);
            strncat(dst, new, size3);
            pos   = pos + index + size2;
            index = strsIndex(str + pos, old);
        } else {
            strcat(dst, str + pos);
            break;
        }
    }
    return dst;
}

/**
 * @description: 将字符串str中的字符串old全部替换为字符串new。需要strsFree()
 * @param {char} *str
 * @param {char} *old
 * @param {char} *new
 * @return {*}
 */
char *strsReplaceAll(const char *str, const char *old, const char *new)
{
    CHECK_RET_PTR(str && old && new);
    size_t size1 = strlen(str);
    size_t size2 = strlen(old);
    size_t size3 = strlen(new);

    int cnt = strsCount(str, old);
    if (cnt <= 0) {
        char *buff = strsloc(size1 + 1);
        memcpy(buff, str, size1);
        return buff;
    }

    char * dst  = NULL;
    size_t diff = size3 - size2;
    if (diff > 0) {
        dst = strsloc(size1 + cnt * (diff) + 1);
    } else {
        dst = strsloc(size1 + 1);
    }

    int pos   = 0;
    int index = strsIndex(str, old);
    for (;;) {
        if (index >= 0) {
            strncat(dst, str + pos, index);
            strncat(dst, new, size3);
            pos   = pos + index + size2;
            index = strsIndex(str + pos, old);
        } else {
            strcat(dst, str + pos);
            break;
        }
    }
    return dst;
}

/**
 * @description: 删除字符串str中的所有子串substr
 * @param {char} *str
 * @param {char} *substr
 * @return {*}
 */
char *strsRemove(char *str, const char *substr)
{
    CHECK_RET_PTR(str && substr);
    char *buff = strsReplaceAll(str, substr, "");
    memcpy(str, buff, strsLen(buff));
    strsFree(buff);
    return str;
}

/**
 * @description: 以sep作为分隔符，分隔字符串str。需要strsFree2()释放
 * @param {char} *str
 * @param {char} *sep
 * @param {int} *num 分割后的所有字符串的数量
 * @return {*}
 */
char **strsSplit(const char *str, const char *sep, int *num)
{
    CHECK_RET_PTR(str && sep && num);
    size_t size1   = strlen(str);
    size_t size2   = strlen(sep);
    char **strList = NULL;

    if (size2 == 0) {
        strList = strsloc2(size1, 2);
        for (int i = 0; i < size1; i++) {
            strList[i][0] = str[i];
        }
        *num = size1;
        return strList;
    }

    int cnt = strsCount(str, sep);
    if (cnt <= 0) {
        strList = strsloc2(1, size1 + 1);
        memcpy(strList[0], str, size1);
        *num = 1;
        return strList;
    }

    strList   = phook.calloc(cnt + 1, sizeof(char *));
    int pos   = 0;
    int index = strsIndex(str, sep);
    int i     = 0;
    for (;;) {
        if (index >= 0) {
            strList[i] = strsloc(index + 1);
            strncat(strList[i], str + pos, index);
            pos   = pos + index + size2;
            index = strsIndex(str + pos, sep);
            i++;
        } else {
            strList[i] = strsloc(size1 - pos + 1);
            strcat(strList[i], str + pos);
            break;
        }
    }

    *num = cnt + 1;
    return strList;
}

/**
 * @description: 以sep为分割，分割字符串str。需要strsFree2()释放
 * @param {char} *str
 * @param {char} *sep
 * @param {int} *num
 * @return {*}
 */
char **strsSplitAfter(const char *str, const char *sep, int *num)
{
    CHECK_RET_PTR(str && sep && num);
    size_t size1   = strlen(str);
    size_t size2   = strlen(sep);
    char **strList = NULL;

    if (size2 == 0) {
        strList = strsloc2(size1, 2);
        for (int i = 0; i < size1; i++) {
            strList[i][0] = str[i];
        }
        *num = size1;
        return strList;
    }

    int cnt = strsCount(str, sep);
    if (cnt <= 0) {
        strList = strsloc2(1, size1 + 1);
        memcpy(strList[0], str, size1);
        *num = 1;
        return strList;
    }

    strList   = phook.calloc(cnt + 1, sizeof(char *));
    int pos   = 0;
    int index = strsIndex(str, sep);
    int i     = 0;
    for (;;) {
        if (index >= 0) {
            strList[i] = strsloc(index + size2 + 1);
            strncat(strList[i], str + pos, index + size2);
            pos   = pos + index + size2;
            index = strsIndex(str + pos, sep);
            i++;
        } else {
            strList[i] = strsloc(size1 - pos + 1);
            strcat(strList[i], str + pos);
            break;
        }
    }

    *num = cnt + 1;
    return strList;
}

/**
 * @description: 以sep作为分隔符，分割字符串str，分割后的字符串包含分隔符。需要strsFree2()释放。
 * @param {char} *str
 * @param {char} *sep
 * @param {int} *num
 * @return {*}
 */
char **strsSplitAfterN(const char *str, const char *sep, int *num)
{
    CHECK_RET_PTR(str && sep && num);
    size_t size1   = strlen(str);
    size_t size2   = strlen(sep);
    char **strList = NULL;

    if (*num == 0) {
        return strList;
    } else if (*num == 1) {
        strList = strsloc2(1, size1 + 1);
        strcat(strList[0], str);
        return strList;
    } else if (*num < 0) {
        return strsSplitAfter(str, sep, num);
    }

    if (size2 == 0) {
        strList = phook.calloc(*num, sizeof(char *));
        for (int i = 0; i < *num - 1; i++) {
            strList[i]    = strsloc(2);
            strList[i][0] = str[i];
        }
        strList[*num - 1] = strsloc(size1 - (*num - 1) + 1);
        strcat(strList[*num - 1], str + *num - 1);
        return strList;
    }

    int cnt = strsCount(str, sep);
    if (cnt <= 0) {
        strList = strsloc2(1, size1 + 1);
        memcpy(strList[0], str, size1);
        *num = 1;
        return strList;
    }

    strList   = phook.calloc(cnt + 1, sizeof(char *));
    int pos   = 0;
    int index = strsIndex(str, sep);
    int i     = 0;
    for (int j = 0; j < *num - 1;) {
        if (index >= 0) {
            strList[i] = strsloc(index + size2 + 1);
            strncat(strList[i], str + pos, index + size2);
            pos   = pos + index + size2;
            index = strsIndex(str + pos, sep);
            i++;
            j++;
        } else {
            break;
        }
    }
    strList[i] = strsloc(size1 - pos + 1);
    strcat(strList[i], str + pos);
    if (*num > cnt + 1) {
        *num = cnt + 1;
    }
    return strList;
}

char **strsSplitN(const char *str, const char *sep, int *num)
{
    CHECK_RET_PTR(str && sep && num);
    size_t size1   = strlen(str);
    size_t size2   = strlen(sep);
    char **strList = NULL;

    if (*num == 0) {
        return strList;
    } else if (*num == 1) {
        strList = strsloc2(1, size1 + 1);
        strcat(strList[0], str);
        return strList;
    } else if (*num < 0) {
        return strsSplit(str, sep, num);
    }

    if (size2 == 0) {
        strList = phook.calloc(*num, sizeof(char *));
        for (int i = 0; i < *num - 1; i++) {
            strList[i]    = strsloc(2);
            strList[i][0] = str[i];
        }
        strList[*num - 1] = strsloc(size1 - (*num - 1) + 1);
        strcat(strList[*num - 1], str + *num - 1);
        return strList;
    }

    int cnt = strsCount(str, sep);
    if (cnt <= 0) {
        strList = strsloc2(1, size1 + 1);
        memcpy(strList[0], str, size1);
        *num = 1;
        return strList;
    }

    strList   = phook.calloc(cnt + 1, sizeof(char *));
    int pos   = 0;
    int index = strsIndex(str, sep);
    int i     = 0;
    for (int j = 0; j < *num - 1;) {
        if (index >= 0) {
            strList[i] = strsloc(index + 1);
            strncat(strList[i], str + pos, index);
            pos   = pos + index + size2;
            index = strsIndex(str + pos, sep);
            i++;
            j++;
        } else {
            break;
        }
    }
    strList[i] = strsloc(size1 - pos + 1);
    strcat(strList[i], str + pos);
    if (*num > cnt + 1) {
        *num = cnt + 1;
    }
    return strList;
}

/**
 * @description: 字符串转化为标题格式，单词首字母大写。
 * @param {char} *str
 * @return {*}
 */
char *strsTitle(char *str)
{
    CHECK_RET_PTR(str);
    size_t size   = strlen(str);
    bool   upFlag = true;
    for (int i = 0; i < size; i++) {
        if (strsIsSpace(str[i])) {
            upFlag = true;
            continue;
        }
        if (upFlag) {
            str[i] = toupper(str[i]);
            upFlag = false;
        }
    }
    return str;
}

/**
 * @description: 移除str的前导和结尾，需要移除的字符来自cutset。
 * @param {char} *str
 * @param {char} *cutset
 * @return {*}
 */
char *strsTrim(char *str, const char *cutset)
{
    CHECK_RET_PTR(str && cutset);
    size_t size     = strlen(str);
    char * buff     = strsloc(size + 1);
    int    startPos = 0;
    int    endPos   = 0;
    for (int i = 0; i < size; i++) {
        if (strchr(cutset, str[i])) {
            continue;
        }
        startPos = i;
        break;
    }
    for (int i = size - 1; i >= 0; i--) {
        if (strchr(cutset, str[i])) {
            continue;
        }
        endPos = i + 1;
        break;
    }
    strncpy(buff, str + startPos, endPos - startPos);
    memcpy(str, buff, size);
    strsFree(buff);
    return str;
}

/**
 * @description: 移除str的前导和结尾，需要移除的字符根据函数指针func的规则进行判断。
 * @param {char} *str
 * @param {char} ch
 * @return {*}
 */
char *strsTrimFunc(char *str, bool (*func)(char ch))
{
    CHECK_RET_PTR(str && func);
    size_t size     = strlen(str);
    char * buff     = strsloc(size + 1);
    int    startPos = 0;
    int    endPos   = 0;
    for (int i = 0; i < size; i++) {
        if (func(str[i])) {
            continue;
        }
        startPos = i;
        break;
    }
    for (int i = size - 1; i >= 0; i--) {
        if (func(str[i])) {
            continue;
        }
        endPos = i + 1;
        break;
    }
    strncpy(buff, str + startPos, endPos - startPos);
    memcpy(str, buff, size);
    strsFree(buff);
    return str;
}

/**
 * @description: 移除字符串str左边的一些字符，这些字符来自cutset。当字符不是cutset中的字符时停止。
 * @param {char} *str
 * @param {char} *cutset
 * @return {*}
 */
char *strsTrimLeft(char *str, const char *cutset)
{
    CHECK_RET_PTR(str && cutset);
    size_t size     = strlen(str);
    char * buff     = strsloc(size + 1);
    int    startPos = 0;
    for (int i = 0; i < size; i++) {
        if (strchr(cutset, str[i])) {
            continue;
        }
        startPos = i;
        break;
    }
    strcpy(buff, str + startPos);
    memcpy(str, buff, size);
    strsFree(buff);
    return str;
}

/**
 * @description: 移除字符串str左边的一些字符，字符是否被移除的规则来自func。当func返回false时停止。
 * @param {char} *str
 * @param {char} ch
 * @return {*}
 */
char *strsTrimLeftFunc(char *str, bool (*func)(char ch))
{
    CHECK_RET_PTR(str && func);
    size_t size     = strlen(str);
    char * buff     = strsloc(size + 1);
    int    startPos = 0;
    for (int i = 0; i < size; i++) {
        if (func(str[i])) {
            continue;
        }
        startPos = i;
        break;
    }
    strcpy(buff, str + startPos);
    memcpy(str, buff, size);
    strsFree(buff);
    return str;
}

/**
 * @description: 移除字符串str的前缀字符串prefix。
 * @param {char} *str
 * @param {char} *prefix
 * @return {*}
 */
char *strsTrimPrefix(char *str, const char *prefix)
{
    CHECK_RET_PTR(str && prefix);
    if (strsHasPrefix(str, prefix)) {
        size_t size = strsLen(str);
        char * buff = strsloc(size);
        strcpy(buff, str + strlen(prefix));
        memcpy(str, buff, size);
        strsFree(buff);
    }
    return str;
}

/**
 * @description: 移除字符串str右边的一些字符，这些字符来自cutset。当字符不是cutset中的字符时停止。
 * @param {char} *str
 * @param {char} *cutset
 * @return {*}
 */
char *strsTrimRight(char *str, const char *cutset)
{
    CHECK_RET_PTR(str && cutset);
    size_t size   = strlen(str);
    char * buff   = strsloc(size + 1);
    int    endPos = 0;
    for (int i = size - 1; i >= 0; i--) {
        if (strchr(cutset, str[i])) {
            continue;
        }
        endPos = i + 1;
        break;
    }
    strncpy(buff, str, endPos);
    memcpy(str, buff, size);
    strsFree(buff);
    return str;
}

/**
 * @description: 移除字符串str右边的一些字符，字符是否被移除的规则来自func。当func返回false时停止。
 * @param {char} *str
 * @param {char} ch
 * @return {*}
 */
char *strsTrimRightFunc(char *str, bool (*func)(char ch))
{
    CHECK_RET_PTR(str && func);
    size_t size   = strlen(str);
    char * buff   = strsloc(size + 1);
    int    endPos = 0;
    for (int i = size - 1; i >= 0; i--) {
        if (func(str[i])) {
            continue;
        }
        endPos = i + 1;
        break;
    }
    strncpy(buff, str, endPos);
    memcpy(str, buff, size);
    strsFree(buff);
    return str;
}

/**
 * @description: 移除字符串前后的所有空白。
 * @param {char} *str
 * @return {*}
 */
char *strsTrimSpace(char *str)
{
    CHECK_RET_PTR(str);
    strsTrimLeftFunc(str, strsIsSpace);
    strsTrimRightFunc(str, strsIsSpace);
    return str;
}

/**
 * @description: 移除字符串str的后缀字符串suffix。
 * @param {char} *str
 * @param {char} *suffix
 * @return {*}
 */
char *strsTrimSuffix(char *str, const char *suffix)
{
    CHECK_RET_PTR(str && suffix);
    if (strsHasSuffix(str, suffix)) {
        size_t size1       = strlen(str);
        size_t size2       = strlen(suffix);
        str[size1 - size2] = '\0';
    }
    return str;
}

/**
 * @description: 字符串str是否包含字符串substr。
 * @param {char} *str
 * @param {char} *substr
 * @return {*}
 */
bool strsContains(const char *str, const char *substr)
{
    CHECK_RET_BOOL(str && substr);
    if (strstr(str, substr))
        return true;
    return false;
}

/**
 * @description: chars字符串是否有字符在str字符串中出现过。
 * @param {char} *str
 * @param {char} *chars
 * @return {*}
 */
bool strContainsAny(const char *str, const char *chars)
{
    CHECK_RET_BOOL(str && chars);
    if (strpbrk(str, chars))
        return true;
    return false;
}

/**
 * @description: 比较两个字符串是否相等，比较时忽略大小写
 * @param {char} *str1
 * @param {char} *str2
 * @return {*}
 */
bool strsEqualCase(const char *str1, const char *str2)
{
    CHECK_RET_BOOL(str1 && str2);
    char *buff1 = strsDump(str1);
    char *buff2 = strsDump(str2);
    strsToupper(buff1);
    strsToupper(buff2);
    bool ret = false;
    if (strcmp(buff1, buff2) == 0) {
        ret = true;
    }
    strsFree(buff1);
    strsFree(buff2);
    return ret;
}

/**
 * @description: 拷贝str副本。需要strsFree()释放
 * @param {char} *str
 * @return {*}
 */
char *strsDump(const char *str)
{
    CHECK_RET_PTR(str);
    size_t size = strsLen(str);
    char * dst  = strsloc(size);
    memcpy(dst, str, size);
    return dst;
}

/**
 * @description: 字符串str是否包含字符ch。
 * @param {char} *str
 * @param {char} ch
 * @return {*}
 */
bool strsContainChar(const char *str, char ch)
{
    CHECK_RET_BOOL(str);
    if (strchr(str, ch))
        return true;
    return false;
}

/**
 * @description: 比较两个字符串是否相等。
 * @param {char} *str1
 * @param {char} *str2
 * @return {*}
 */
bool strsCompare(const char *str1, const char *str2)
{
    CHECK_RET_BOOL(str1 && str2);
    if (strcmp(str1, str2) == 0)
        return true;
    return false;
}

/**
 * @description: 将字符串分割为子串，根据func的规则进行分割（仍然包含了空白分割），需要使用strsFree2()释放
 * @param {char} *str
 * @param {char} ch
 * @param {int} *listSize
 * @return {*}
 */
char **strsFieldsFunc(const char *str, bool (*func)(char ch), int *listSize)
{
    CHECK_RET_PTR(str && func && listSize);
    size_t size = strlen(str);
    char * buff = strsDump(str);
    for (int i = 0; i < size; i++) {
        if (func(buff[i])) {
            buff[i] = ' ';
        }
    }
    char **dst = strsFields(buff, listSize);
    strsFree(buff);
    return dst;
}

/**
 * @description: 返回字符ch在字符串str中首次出现的位置。
 * @param {char} *str
 * @param {char} ch
 * @return {*} 当不存在时返回-1
 */
int strsIndexChar(const char *str, char ch)
{
    CHECK_RET_INT(str);
    char *pos = strchr(str, ch);
    if (pos != NULL)
        return pos - str;
    return -1;
}

/**
 * @description: 返回字符ch在字符串str中最后一次出现的位置。
 * @param {char} *str
 * @param {char} ch
 * @return {*}
 */
int strsLastIndexChar(const char *str, char ch)
{
    CHECK_RET_INT(str);
    char *pos = strrchr(str, ch);
    if (pos != NULL)
        return pos - str;
    return -1;
}

/**
 * @description: 在str字符串中的pos位置插入字符串substr。
 * @param {char} *str
 * @param {char} *substr
 * @param {int} pos
 * @return {*}
 */
char *strsInsert(const char *str, const char *substr, int pos)
{
    CHECK_RET_PTR(str && substr && (pos >= 0));
    size_t size1 = strlen(str);
    size_t size2 = strlen(substr);
    char * dst   = strsloc(size1 + size2 + 1);
    strncpy(dst, str, pos);
    strcat(dst, substr);
    strcat(dst, str + pos);
    return dst;
}