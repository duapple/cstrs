/*
 * @Author: duapple
 * @Date: 2021-11-17 21:42:51
 * @LastEditTime: 2021-11-22 20:55:10
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

bool letter(char ch)
{
    if (!strsIsLetter(ch) && !strsIsNumber(ch)) {
        return true;
    }
    return false;
}

void test_main();

int main()
{
    test_main();
    return 0;
}

void test_main()
{
    if (1) {
        char str[] = "~ Hi, Hello world! ~";
        println("       \"%s\"        ", str);
        println("%-15s test: \"%s\"", "println", str);
        println("%-15s test: \"%s\"", "strsReverse", strsReverse(str));
        strsReverse(str);
        println("%-15s test: has %d substr", "strsNum", strsNum(str));
        char *str1 = strsDump(str);
        println("%-15s test: \"%s\"", "strDump", str1);
        strsFree(str1);
        println("%-15s test: has '%c': %s", "strsContainChar", 'r', strsContainChar(str, 'r') ? "true" : "false");
        println("%-15s test: has \"%s\": %s", "strsContains", "wor", strsContains(str, "wor") ? "true" : "false");
        println("%-15s test: has \"%s\" character: %s", "strsContains", "str",
                strContainsAny(str, "str") ? "true" : "false");

        char **str2 = NULL;
        int    size = 0;
        str2        = strsFields(str, &size);
        if (str2 != NULL) {
            for (int i = 0; i < size; i++) {
                println("\"%s\"", str2[i]);
            }
        }
        println("");
        strsFree2(str2, size);
        str2 = strsSplit(str, "l", &size);
        if (str2 != NULL) {
            for (int i = 0; i < size; i++) {
                println("\"%s\"", str2[i]);
            }
        }
        strsFree2(str2, size);

        str1 = strsDump(str);
        println("\"%s\"", strsRemove(str1, "o"));
        strsFree(str1);

        str1 = strsJoinN(" test ", 4, "you", "are", "very", "good");
        if (str1 != NULL) {
            println("\"%s\"", str1);
        }
        strsFree(str1);

        str1       = strsDump(str);
        char *str3 = strsInsert(str1, "INSERT", 5);
        println("\"%s\"", str3);
        strsFree(str2);
        strsFree(str1);
    }

    println("");

    if (1) {
        char str[] = "Hello world";
        println("       \"%s\"        ", str);
        char *str1 = strsDump(str);
        println("%-15s test: \"%s\"", "strsToupper", strsToupper(str));
        println("%-15s test: \"%s\"", "strsTolower", strsTolower(str));
        strsFree(str1);
        str1 = strsDump(str);
        println("%-15s test: \"%s\"", "strsTitle", strsTitle(str));
        strsFree(str1);
    }
}