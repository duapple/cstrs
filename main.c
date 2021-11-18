/*
 * @Author: duapple
 * @Date: 2021-11-17 21:42:51
 * @LastEditTime: 2021-11-19 00:34:17
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
    } 
    else if (ch >= 'a' && ch <= 'z') {
        return 'a' + (ch - 'a' + 13) % 26;
    } 
    else {
        return ch;
    }
}

int main()
{
    char str[80] = "This is - - www.runoob.com - website";

    char str1[] = "oink rink oink";

    char *str2 = strsReplace(str1, "oink", "moo", 0);
    println("%s", str2);
    strsFree(str2);

    return 0;
}