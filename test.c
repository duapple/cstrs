#include "strs.h"
#include <stdio.h>

static void test();

int main()
{
    test();
    return 0;
}

void test()
{
    println("strs lib test");

    println("[%s] is space: %s", " ", strs_is_space(' ') ? "TRUR" : "FALSE");
    println("[%s] is space: %s", "\\t", strs_is_space('\t') ? "TRUR" : "FALSE");
    println("[%s] is space: %s", "\\n", strs_is_space('\n') ? "TRUR" : "FALSE");
    println("[%s] is space: %s", "\\r", strs_is_space('\r') ? "TRUR" : "FALSE");
    println("[%s] is space: %s", "c", strs_is_space('c') ? "TRUR" : "FALSE");
    println("");

    for (char i = '0'; i < '9'; i++) {
        println("[%c] is a number: %s", i, strs_is_number(i) ? "TRUE" : "FALSE");
    }
    println("[%c] is a number: %s", 'c', strs_is_number('c') ? "TRUE" : "FALSE");
    println("");

    for (char i = 'a'; i <= 'z'; i++) {
        println("[%c] is letter: %s", i, strs_is_letter(i) ? "TRUE" : "FALSE");
    }
    for (char i = 'A'; i <= 'Z'; i++) {
        println("[%c] is letter: %s", i, strs_is_letter(i) ? "TRUE" : "FALSE");
    }
    println("[%c] is letter: %s", '9', strs_is_letter('9') ? "TRUE" : "FALSE");
    println("");

    for (char i = 'a'; i <= 'z'; i++) {
        println("[%c] is a low letter: %s", i, strs_is_low_letter(i) ? "TRUE" : "FALSE");
    }
    for (char i = 'A'; i <= 'Z'; i++) {
        println("[%c] is a up letter: %s", i, strs_is_up_letter(i) ? "TRUE" : "FALSE");
    }
    println("[%c] is a up letter: %s", 'a', strs_is_up_letter('a') ? "TRUE" : "FALSE");
    println("[%c] is a low letter: %s", 'A', strs_is_low_letter('A') ? "TRUE" : "FALSE");
    println("");

    char str1[] = "hello world!";
    println("[%s] size (contain \\0) is: %d", str1, chcm_strslen(str1));
    println("");

    char *str2 = strs_dup(str1);
    println("[%s] reverse is: [%s]", str2, strs_reverse(str1));
    strs_reverse(str1);
    strs_free(str2);
    println("");

    println("[%s] sub str number is: %d", str1, strs_num(str1));
    println("");

    str2 = strs_dup(str1);
    println("[%s] dup is: [%s]", str1, str2);
    println("[%s] to upper is: [%s]", str1, strs_to_upper(str2));
    println("[%s] to lower is: [%s]", str1, strs_to_lower(str2));
    strs_free(str2);
    println("");

    println("[%s] contain char %c: %s", str1, 'r', strs_contain_char(str1, 'r') ? "TRUE" : "FALSE");
    println("[%s] contain char %c: %s", str1, 'R', strs_contain_char(str1, 'R') ? "TRUE" : "FALSE");
    println("[%s] contain char %c: %s", str1, 'x', strs_contain_char(str1, 'x') ? "TRUE" : "FALSE");
    println("[%s] contain char %c: %s", str1, 'X', strs_contain_char(str1, 'X') ? "TRUE" : "FALSE");
    println("");

    println("[%s] constain sub str [%s]: %s", str1, "orl", strs_contains(str1, "orl") ? "TRUE" : "FALSE");
    println("[%s] constain sub str [%s]: %s", str1, "ORL", strs_contains(str1, "ORL") ? "TRUE" : "FALSE");
    println("[%s] constain sub str [%s]: %s", str1, "wow", strs_contains(str1, "wow") ? "TRUE" : "FALSE");
    println("");

    println("[%s] == [%s]: %s", "hello", "hello1", strs_compare("hello", "hello\r") ? "TRUE" : "FALSE");
    println("");

    println("[%s] contains any char from sub str [%s]: %s", str1, "it works",
            strs_contains_any(str1, "it works") ? "TRUE" : "FALSE");
    println("");

    str2 = strs_dup(str1);
    strs_to_upper(str2);
    println("[%s] == [%s] (ignore upper or lower letter): %s", str1, str2,
            strs_equal_case(str1, str2) ? "TRUE" : "FALSE");
    strs_free(str2);
    println("");

    println("[%s] has sub str [%s]: %d", str1, "l", strs_count(str1, "l"));
    println("[%s] has sub str [%s]: %d", "Today is a funny day", "day", strs_count("Today is a funny day", "day"));
    println("");

    str2 = "Hello world! \nToday is a funny day.";
    int listSize;
    char **strlist = strs_fields(str2, &listSize);
    for (int i = 0; i < listSize; i++) {
        println("splite %d: [%s]", i, strlist[i]);
    }
    strs_free2(strlist, listSize);
    println("");

    println("[%s] has prefix [%s]: %s", str1, "hel", strs_has_prefix(str1, "hel") ? "TRUE" : "FALSE");
    println("[%s] has prefix [%s]: %s", str1, "ello", strs_has_prefix(str1, "ello") ? "TRUE" : "FALSE");
    println("");

    println("[%s] has suffix [%s]: %s", str1, "rld!", strs_has_suffix(str1, "rld!") ? "TRUE" : "FALSE");
    println("[%s] has suffix [%s]: %s", str1, "rld", strs_has_suffix(str1, "rld") ? "TRUE" : "FALSE");
    println("");

    println("[%s] in the [%s]: %d", "wor", str1, strs_index(str1, "wor"));
    println("[%s] in the [%s]: %d", "ddd", str1, strs_index(str1, "ddd"));
    println("");

    str2 = strs_join("hello", "world", " ");
    println("[%s] + [%s] = [%s]", "hello", "world", str2);
    strs_free(str2);
    str2 = strs_join("hello", "world", "");
    println("[%s] + [%s] = [%s]", "hello", "world", str2);
    strs_free(str2);
    println("");

    str2 = strs_join_n(" ", "Today", "is", "a", "funny", "day", "!", NULL);
    println("[%s] + [%s] + [%s] + [%s] + [%s] + [%s] = [%s]", "To", "is", "a", "funny", "day", "!", str2);
    strs_free(str2);
    println("");

    str2 = "Today is a funny day!";
    println("[%s] in the [%s] last pos: %d", "day", str2, strs_last_index(str2, "day"));
    println("[%s] in the [%s] last pos: %d", "is", str2, strs_last_index(str2, "is"));
    println("[%s] in the [%s] last pos: %d", "ddd", str2, strs_last_index(str2, "ddd"));
    println("");

    println("[%s] [%s] index any: %d", "chicken", "aeiouy", strs_index_any("chicken", "aeiouy"));
    println("[%s] [%s] index any: %d", "crwth", "aeiouy", strs_index_any("crwth", "aeiouy"));
    println("");

    println("%c in the [%s] pos: %d", 'o', str1, strs_index_char(str1, 'o'));
    println("%c in the [%s] pos: %d", 'x', str1, strs_index_char(str1, 'x'));
    println("");

    println("%c in the [%s] pos: %d", 'o', str1, strs_last_index_char(str1, 'o'));
    println("%c in the [%s] pos: %d", 'x', str1, strs_last_index_char(str1, 'x'));
    println("");

    str2 = strs_repeat("good ", 3);
    println("[%s] repeat %d: [%s]", "good ", 3, str2);
    strs_free(str2);
    println("");

    str2 = strs_replace(str1, "l", "xx", 2);
    println("[%s] replace [%s] to [%s] (count %d): %s", str1, "l", "xx", 2, str2);
    strs_free(str2);
    str2 = strs_replace(str1, "l", "xx", 0);
    println("[%s] replace [%s] to [%s] (count %d): %s", str1, "l", "xx", 0, str2);
    strs_free(str2);
    str2 = strs_replace(str1, "l", "xx", -1);
    println("[%s] replace [%s] to [%s] (count %d): %s", str1, "l", "xx", -1, str2);
    strs_free(str2);
    println("");

    str2 = strs_replace_all(str1, "l", "xx");
    println("[%s] replace all [%s] to [%s]: %s", str1, "l", "xx", str2);
    strs_free(str2);
    println("");

    str2 = strs_dup(str1);
    strs_remove(str2, "l");
    println("[%s] remove [%s]: [%s]", str1, "l", str2);
    strs_free(str2);
    println("");

    int num;
    strlist = strs_split(str1, "o", &num);
    for (int i = 0; i < num; i++) {
        println("split[%d]: [%s]", i, strlist[i]);
    }
    strs_free2(strlist, num);
    println("");

    num = 2;
    strlist = strs_split_n(str1, "o", &num);
    for (int i = 0; i < num; i++) {
        println("split[%d]: [%s]", i, strlist[i]);
    }
    strs_free2(strlist, num);
    num = 4;
    strlist = strs_split_n(str1, "lo", &num);
    for (int i = 0; i < num; i++) {
        println("split[%d]: [%s]", i, strlist[i]);
    }
    println("num: %d", num);
    strs_free2(strlist, num);
    println("");

    strlist = strs_split_after(str1, "o", &num);
    for (int i = 0; i < num; i++) {
        println("split[%d]: [%s]", i, strlist[i]);
    }
    strs_free2(strlist, num);
    println("");

    num = 2;
    strlist = strs_split_after_n(str1, "o", &num);
    for (int i = 0; i < num; i++) {
        println("split[%d]: [%s]", i, strlist[i]);
    }
    strs_free2(strlist, num);
    println("");

    str2 = strs_dup(str1);
    println("[%s] title: [%s]", str1, strs_title(str2));
    strs_free(str2);
    println("");

    str2 = strs_dup("xoxo Hello, Gophers!!!oxox");
    println("[%s] trim [%s]: [%s]", "xoxo Hello, Gophers!!!oxox", "xo", strs_trim(str2, "xo"));
    strs_free(str2);
    println("");

    str2 = strs_dup("xoxo Hello, Gophers!!!oxox");
    println("[%s] trim left [%s]: [%s]", "xoxo Hello, Gophers!!!oxox", "xo", strs_trim_left(str2, "xo"));
    strs_free(str2);
    println("");

    str2 = strs_dup("xoxo Hello, Gophers!!!oxox");
    println("[%s] trim right [%s]: [%s]", "xoxo Hello, Gophers!!!oxox", "xo", strs_trim_right(str2, "xo"));
    strs_free(str2);
    println("");

    str2 = strs_dup("xoxo Hello, Gophers!!!oxox");
    println("[%s] trim prefix [%s]: [%s]", "xoxo Hello, Gophers!!!oxox", "xo", strs_trim_prefix(str2, "xo"));
    strs_free(str2);
    str2 = strs_dup("xoxo Hello, Gophers!!!oxox");
    println("[%s] trim prefix [%s]: [%s]", "xoxo Hello, Gophers!!!oxox", "xo H", strs_trim_prefix(str2, "xo H"));
    strs_free(str2);
    println("");

    str2 = strs_dup("xoxo Hello, Gophers!!!oxox");
    println("[%s] trim suffix [%s]: [%s]", "xoxo Hello, Gophers!!!oxox", "ox", strs_trim_suffix(str2, "ox"));
    strs_free(str2);
    str2 = strs_dup("xoxo Hello, Gophers!!!oxox");
    println("[%s] trim suffix [%s]: [%s]", "xoxo Hello, Gophers!!!oxox", "xo", strs_trim_suffix(str2, "xo"));
    strs_free(str2);
    println("");

    str2 = "\t hello world!\n\r ";
    char *str3 = strs_dup(str2);
    println("[%s] trim space: [%s]", str2, strs_trim_space(str3));
    strs_free(str3);
    println("");

    str2 = strs_insert(str1, "my ", 6);
    println("[%s] insert [%s] in pos %d: [%s]", "my ", str1, 6, str2);
    strs_free(str2);

    println("\ntest complete!!!!!!\n");
}