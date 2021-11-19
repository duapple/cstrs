/*
 * @Author: duapple
 * @Date: 2021-11-17 21:42:51
 * @LastEditTime: 2021-11-19 10:29:03
 * @LastEditors: duapple
 * @Description: Add description
 * @FilePath: /strings/main.c
 * Copyright (c) 2011 duapple - All rights reserved.
 */
#include "strings.h"
#include <stdio.h>
#include <string.h>

char map(char ch)
{
    if (ch >= 'A' && ch <= 'Z') {
        return 'A' + (ch - 'A' + 13) % 26;
    } else if (ch >= 'a' && ch <= 'z') {
        return 'a' + (ch - 'a' + 13) % 26;
    } else {
        return ch;
    }
}

char map1(char ch)
{
    if (ch >= 'A' && ch <= 'Z') {
        return 'A' + (ch - 'A' + 3) % 26;
    } else if (ch >= 'a' && ch <= 'z') {
        return 'a' + (ch - 'a' + 3) % 26;
    } else {
        return ch;
    }
}

int main()
{
    char str[80] = "This     is    -    -  www.runoob.com   -      website";
    char str1[]  = "oink rink oink";

    char **strList = NULL;
    int    size    = 0;
    strsFields(str, &strList, &size);
    // println("%p", strList);
    // println("%d", size);
    // strcat(strList[0], "hel");
    for (int i = 0; i < size; i++) {
        println("%s#", strList[i]);
    }
    strsFree2(strList, size);

    return 0;
}