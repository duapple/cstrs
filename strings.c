/*
 * @Author: duapple
 * @Date: 2021-11-17 21:42:40
 * @LastEditTime: 2021-11-19 00:33:09
 * @LastEditors: duapple
 * @Description: Add description
 * 
 * @FilePath: /strings/strings.c
 * Copyright (c) 2011 duapple - All rights reserved.
 */
#include "strings.h"
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOG_INFO(...)  println(__VA_ARGS__)
#define LOG_ERROR(...) println(__VA_ARGS__)

/**
 * @description: 判断字符是否是空白字符
 * @param {char} ch
 * @return {*}
 */
bool strsIsSpace(const char ch)
{
    if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
    {
        return true;
    }
    return false;
}

/**
 * @description: 为字符串分配存储空间，已经对存储空间进行初始化，需要free
 * @param {size_t} size
 * @return {*}
 */
void *strsloc(size_t size)
{
    return calloc(size, sizeof(char));
}

/**
 * @description: 字符串包含结束符的长度
 * @param {char} *str
 * @return {*}
 */
size_t strsLen(const char *str)
{
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
void strsReverse(char *str)
{
    size_t size = strsLen(str);
    char *buff = strsloc(size);
    for (int i = 0, max = strlen(str), j = max - 1; i < max; i++, j--)
    {  
        buff[j] = str[i];
    }
    memcpy(str, buff, size);
    strsFree(buff);
}

/**
 * @description: 字符串中子串的数量
 * @param {char} *str
 * @return {*}
 */
int strsNum(const char *str)
{
    size_t strLen = strlen(str);
    int    index  = 0;
    int    offset = 0;
    int    num    = 0;
    for (int i = 0; i < strLen + 1; i++)
    {
        if (strsIsSpace(str[i]) || strsIsEnd(str[i]))
        {
            if (offset > index)
            {
                num++;
            }
            index = offset;
            index++;
            offset++;
        }
        else
        {
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
void strsFree(void *str)
{
    free(str);
    str = NULL;
}

/**
 * @description: 字符串转为全大写
 * @param {char} *str
 * @return {*}
 */
void strsToupper(char *str)
{
    size_t strLen = strlen(str);
    for (int i = 0; i < strLen; i++)
    {
        str[i] = toupper(str[i]);
    }
}

/**
 * @description: 字符串转为全小写
 * @param {char} *str
 * @return {*}
 */
void strsTolower(char *str)
{
    size_t strLen = strlen(str);
    for (int i = 0; i < strLen; i++)
    {
        str[i] = tolower(str[i]);
    }
}

/**
 * @description: 统计子串substr在字符串str中出现过多少次
 * @param {char} *str
 * @param {char} *substr
 * @return {*}
 */
int strsCount(const char *str, const char *substr)
{
    size_t offset    = 0;
    size_t strLen    = strlen(str);
    size_t substrLen = strlen(substr);
    int    count     = 0;
    for (; offset < strLen;)
    {
        char *strIndex = strstr(str + offset, substr);
        if (strIndex == NULL)
        {
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
int strsFields(const char *str, char **strList, int *listSize)
{
    int num         = strsNum(str);
    strList         = malloc(sizeof(char *) * num);
    int    index    = 0;
    int    offset   = 0;
    size_t buffSize = strsLen(str);
    char * buff     = calloc(buffSize, sizeof(char));
    if (buff == NULL)
    {
        LOG_ERROR("calloc failed");
    }
    for (int i = 0; i < buffSize; i++)
    {
        if (strsIsSpace(str[i]) || strsIsEnd(str[i]))
        {
            if (offset > index)
            {
                sscanf(str + index, "%s", buff);
                int strSize = strsLen(buff);
                strList[i]  = strsloc(strSize);
                memcpy(strList[i], buff, strSize);
                memset(buff, 0, buffSize);
                LOG_INFO("%s", strList[i]);
            }
            index = offset;
            index++;
            offset++;
        }
        else
            offset++;
    }
    return 0;
}

/**
 * @description: 释放strsFields()申请的内存空间
 * @param {char} *
 * @param {int} listSize
 * @return {*}
 */
void strsFree2(char **strList, int listSize)
{
    for (int i = 0; i < listSize; i++)
    {
        strsFree(strList[i]);
    }
    strsFree(strList);
}

/**
 * @description: 字符串str是否拥有字符串prefix前缀
 * @param {char} *str
 * @param {char} *prefix
 * @return {*}
 */
bool strsHasPrefix(const char *str, const char *prefix)
{
    size_t size = strlen(prefix);
    if (size == 0)
        return true;

    for (int i = 0; i < size; i++)
    {
        if (str[i] != prefix[i])
        {
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
    size_t size1 = strlen(suffix);
    size_t size2 = strlen(str);
    if (size1 == 0)
    {
        return true;
    }
    for (int i = 0, k = size1 - 1, j = size2 - 1; i < size1; i++, j--, k--)
    {
        if (str[j] != suffix[k])
        {
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
    char *pos = strstr(str, substr);
    if (pos == NULL)
    {
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
    size_t  size = 0;
    va_list arg;
    va_start(arg, num);
    for (int i = 0; i < num - 1; i++)
    {
        size += strlen(va_arg(arg, char *));
    }
    va_end(arg);

    char *dst = strsloc(size + 1);
    va_start(arg, num);
    for (int i = 0; i < num; i++)
    {
        strcat(dst, va_arg(arg, char *));
        if (i != num - 1)
        {
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
    int    index  = 0;
    int    offset = 0;
    int    pos    = -1;
    size_t size   = strlen(substr);
    index         = strsIndex(str, substr);
    for (; index >= 0; index = strsIndex(str + offset, substr))
    {
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
#if 0
    size_t size = strsLen(str);
    char *buff = strsloc(size);
    memcpy(buff, str, size);
    strsReverse(buff);
    char *pos = strpbrk(buff, substr);
    strsFree(buff);
    if (pos == NULL) {
        return -1;
    }
    int index = pos - buff;
    return size -2 - index;
#else
    size_t size = strlen(substr);
    int maxPos = -1;
    for (int i = 0; i < size; i++)
    {
        char* index = strrchr(str, substr[i]);
        if (index == NULL)
            continue;
        int pos = strsIndex(str, index);
        maxPos = maxPos > pos ? maxPos : pos;
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
void strsMap(char *str, char (*map)(char ch))
{
    size_t size = strlen(str);
    for (int i = 0; i < size; i++)
    {
        str[i] = map(str[i]);
    }
}

/**
 * @description: 复制字符串str num次，并拼接到一起。需要free()
 * @param {char} *str
 * @param {int} num
 * @return {*}
 */
char* strsRepeat(const char *str, int num)
{
    if (num <= 0) {
        return NULL;
    }
    size_t size = strlen(str);
    char *dst = strsloc(size * num + 1);
    for (int i = 0; i < num; i++)
    {
        strcat(dst, str);
    }
    return dst;
}

/**
 * @description: 将字符串str中的字符串old部分替换为字符串new。需要free()
 * @param {char} *str
 * @param {char} *old
 * @param {char} *new
 * @param {int} num   <0时，全部替换
 * @return {*}
 */
char * strsReplace(const char *str, const char *old, const char *new, int num)
{
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

    char *dst = NULL;
    size_t diff = size3 - size2;
    if (diff > 0) {
        dst = strsloc(size1 + cnt * (diff) + 1);
    } else {
        dst = strsloc(size1 + 1);
    }

    int pos = 0;
    int index = strsIndex(str, old);
    for (int j = 0;;j++)
    {
        if (index >= 0 && j < num) {
            strncat(dst, str + pos, index);
            strncat(dst, new, size3);
            pos = pos + index + size2 ;
            index = strsIndex(str + pos, old);
        } 
        else {
            strcat(dst, str + pos);
            break;
        }
    }
    return dst;
}

/**
 * @description: 将字符串str中的字符串old全部替换为字符串new。需要free()
 * @param {char} *str
 * @param {char} *old
 * @param {char} *new
 * @return {*}
 */
char * strsReplaceAll(const char *str, const char *old, const char *new)
{
    size_t size1 = strlen(str);
    size_t size2 = strlen(old);
    size_t size3 = strlen(new);

    int cnt = strsCount(str, old);
    if (cnt <= 0) {
        char *buff = strsloc(size1 + 1);
        memcpy(buff, str, size1);
        return buff;
    }

    char *dst = NULL;
    size_t diff = size3 - size2;
    if (diff > 0) {
        dst = strsloc(size1 + cnt * (diff) + 1);
    } else {
        dst = strsloc(size1 + 1);
    }

    int pos = 0;
    int index = strsIndex(str, old);
    for (;;)
    {
        if (index >= 0) {
            strncat(dst, str + pos, index);
            strncat(dst, new, size3);
            pos = pos + index + size2 ;
            index = strsIndex(str + pos, old);
        } 
        else {
            strcat(dst, str + pos);
            break;
        }
    }
    return dst;
}