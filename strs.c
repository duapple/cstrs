#include "strs.h"
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOG_INFO(...)  println(__VA_ARGS__)
#define LOG_ERROR(...) println(__VA_ARGS__)
#define CHECK_RET(rule, value)                                                                                         \
    do {                                                                                                               \
        if (!(rule)) {                                                                                                 \
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

int strs_set_plat_hooks(strs_plat_hook_t *hooks)
{
    CHECK_RET_INT(hooks && hooks->calloc && hooks->free);
    phook.calloc = hooks->calloc;
    phook.free = hooks->free;
    return 0;
}

bool strs_is_space(char ch)
{
    if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
        return true;
    }
    return false;
}

bool strs_is_number(char ch)
{
    if (ch >= '0' && ch <= '9')
        return true;
    return false;
}

bool strs_is_letter(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return true;
    return false;
}

bool strs_is_up_letter(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
        return true;
    return false;
}

bool strs_is_low_letter(char ch)
{
    if (!strs_is_up_letter(ch))
        return true;
    return false;
}

bool strs_is_end(char ch)
{
    if (ch == '\0')
        return true;
    return false;
}

char *chcm_strsloc(size_t size)
{
    return (char *)phook.calloc(size, sizeof(char));
}

char **chcm_strsloc2(int row, int col)
{
    CHECK_RET_PTR((row > 0) && (col > 0));
    char **strList = phook.calloc(row, sizeof(char *));
    for (int i = 0; i < row; i++) {
        strList[i] = phook.calloc(col, sizeof(char));
    }
    return strList;
}

size_t chcm_strslen(const char *str)
{
    CHECK_RET_INT(str);
    return strlen(str) + 1;
}

int println(const char *format, ...)
{
    CHECK_RET_INT(format);
    int ret;
    va_list arg;
    va_start(arg, format);
    ret = vprintf(format, arg);
    putchar('\n');
    va_end(arg);
    return ret;
}

void __strs_free(void *str)
{
    if (str == NULL)
        return;
    phook.free(str);
}

void __strs_free2(char **strList, int listSize)
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

char *strs_reverse(char *str)
{
    CHECK_RET_PTR(str);
    size_t size = chcm_strslen(str);
    char *buff = chcm_strsloc(size);
    for (int i = 0, max = strlen(str), j = max - 1; i < max; i++, j--) {
        buff[j] = str[i];
    }
    memcpy(str, buff, size);
    strs_free(buff);
    return str;
}

int strs_num(const char *str)
{
    CHECK_RET_INT(str);
    size_t strLen = strlen(str);
    int index = 0;
    int offset = 0;
    int num = 0;
    for (int i = 0; i < strLen + 1; i++) {
        if (strs_is_space(str[i]) || strs_is_end(str[i])) {
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

char *strs_dup(const char *str)
{
    CHECK_RET_PTR(str);
    size_t size = chcm_strslen(str);
    char *dst = chcm_strsloc(size);
    memcpy(dst, str, size);
    return dst;
}

char *strs_dup2(char *buf, unsigned int size, char *str)
{
    CHECK_RET_PTR(buf && str);
    strncpy(buf, str, size - 1);
    free(str);
    return buf;
}

char *strs_to_upper(char *str)
{
    CHECK_RET_PTR(str);
    size_t strLen = strlen(str);
    for (int i = 0; i < strLen; i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

char *strs_to_lower(char *str)
{
    CHECK_RET_PTR(str);
    size_t strLen = strlen(str);
    for (int i = 0; i < strLen; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

bool strs_contain_char(const char *str, char ch)
{
    CHECK_RET_BOOL(str);
    if (strchr(str, ch))
        return true;
    return false;
}

bool strs_contains(const char *str, const char *substr)
{
    CHECK_RET_BOOL(str && substr);
    if (strstr(str, substr))
        return true;
    return false;
}

bool strs_compare(const char *str1, const char *str2)
{
    CHECK_RET_BOOL(str1 && str2);
    if (strcmp(str1, str2) == 0)
        return true;
    return false;
}

bool strs_contains_any(const char *str, const char *chars)
{
    CHECK_RET_BOOL(str && chars);
    if (strpbrk(str, chars))
        return true;
    return false;
}

bool strs_equal_case(const char *str1, const char *str2)
{
    CHECK_RET_BOOL(str1 && str2);
    char *buff1 = strs_dup(str1);
    char *buff2 = strs_dup(str2);
    strs_to_upper(buff1);
    strs_to_upper(buff2);
    bool ret = false;
    if (strcmp(buff1, buff2) == 0) {
        ret = true;
    }
    strs_free(buff1);
    strs_free(buff2);
    return ret;
}

int strs_count(const char *str, const char *substr)
{
    CHECK_RET_INT(str && substr);
    size_t offset = 0;
    size_t strLen = strlen(str);
    size_t substrLen = strlen(substr);
    int count = 0;
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

char **strs_fields(const char *str, int *listSize)
{
    CHECK_RET_PTR(str && listSize);
    int num = strs_num(str);
    char **strList = phook.calloc(num, sizeof(char *));
    int index = 0;
    int offset = 0;
    size_t buffSize = chcm_strslen(str);
    char *buff = chcm_strsloc(buffSize);
    *listSize = num;
    for (int i = 0, j = 0; i < buffSize && j < num; i++) {
        if (strs_is_space(str[i]) || strs_is_end(str[i])) {
            if (offset > index) {
                sscanf(str + index, "%s", buff);
                int strSize = chcm_strslen(buff);
                strList[j] = chcm_strsloc(strSize);
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

char **strs_fields_func(const char *str, bool (*func)(char ch), int *listSize)
{
    CHECK_RET_PTR(str && func && listSize);
    size_t size = strlen(str);
    char *buff = strs_dup(str);
    for (int i = 0; i < size; i++) {
        if (func(buff[i])) {
            buff[i] = ' ';
        }
    }
    char **dst = strs_fields(buff, listSize);
    strs_free(buff);
    return dst;
}

bool strs_has_prefix(const char *str, const char *prefix)
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

bool strs_has_suffix(const char *str, const char *suffix)
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

int strs_index(const char *str, const char *substr)
{
    CHECK_RET_INT(str && substr);
    char *pos = strstr(str, substr);
    if (pos == NULL) {
        return -1;
    }
    return pos - str;
}

char *strs_join(const char *str1, const char *str2, const char *sep)
{
    CHECK_RET_PTR(str1 && str2 && sep);
    size_t size = strlen(str1) + strlen(str2) + strlen(sep) + 1;
    char *dst = chcm_strsloc(size);
    strcat(dst, str1);
    strcat(dst, sep);
    strcat(dst, str2);
    return dst;
}

char *strs_join_n(const char *sep, ...)
{
    CHECK_RET_PTR(sep);
    size_t size = 0;
    unsigned int num = 0;
    char *arg_str = NULL;
    va_list arg;

    va_start(arg, sep);
    while ((arg_str = va_arg(arg, char *))) {
        size += strlen(arg_str);
        ++num;
    }
    va_end(arg);

    char *dst = chcm_strsloc(size + 1 + strlen(sep) * num);
    va_start(arg, sep);
    for (int i = 0; i < num; i++) {
        strcat(dst, va_arg(arg, char *));
        if (i != num - 1) {
            strcat(dst, sep);
        }
    }
    va_end(arg);
    return dst;
}

int strs_last_index(const char *str, const char *substr)
{
    CHECK_RET_INT(str && substr);
    int index = 0;
    int offset = 0;
    int pos = -1;
    size_t size = strlen(substr);
    index = strs_index(str, substr);
    for (; index >= 0; index = strs_index(str + offset, substr)) {
        pos = index + offset;
        offset += index + size;
    }
    return pos;
}

int strs_index_any(const char *str, const char *substr)
{
    CHECK_RET_INT(str && substr);

    size_t size = strlen(substr);
    int ret = -1;
    int pos1 = size + 1;
    for (int i = 0; i < size; i++) {
        char *index = strrchr(str, substr[i]);
        if (index == NULL)
            continue;
        int pos = strs_index(str, index);
        pos1 = pos < pos1 ? pos : pos1;
        ret = pos1;
    }
    return ret;
}

int strs_index_char(const char *str, char ch)
{
    CHECK_RET_INT(str);
    int size = strlen(str);
    for (int i = 0; i < size; i++) {
        if (str[i] == ch) {
            return i;
        }
    }
    return -1;
}

int strs_last_index_char(const char *str, char ch)
{
    CHECK_RET_INT(str);
    char *pos = strrchr(str, ch);
    if (pos != NULL)
        return pos - str;
    return -1;
}

char *strs_map(char *str, char (*map)(char ch))
{
    CHECK_RET_PTR(str && map);
    size_t size = strlen(str);
    for (int i = 0; i < size; i++) {
        str[i] = map(str[i]);
    }
    return str;
}

char *strs_repeat(const char *str, int num)
{
    CHECK_RET_PTR(str && (num >= 0));
    size_t size = strlen(str);
    char *dst = chcm_strsloc(size * num + 1);
    for (int i = 0; i < num; i++) {
        strcat(dst, str);
    }
    return dst;
}

char *strs_replace(const char *str, const char *old, const char *new, int num)
{
    CHECK_RET_PTR(str && old && new);
    if (num < 0) {
        return strs_replace_all(str, old, new);
    }

    size_t size1 = strlen(str);
    size_t size2 = strlen(old);
    size_t size3 = strlen(new);

    int cnt = strs_count(str, old);
    if (cnt <= 0) {
        char *buff = chcm_strsloc(size1 + 1);
        memcpy(buff, str, size1);
        return buff;
    }

    char *dst = NULL;
    size_t diff = size3 - size2;
    if (diff > 0) {
        dst = chcm_strsloc(size1 + cnt * (diff) + 1);
    } else {
        dst = chcm_strsloc(size1 + 1);
    }

    int pos = 0;
    int index = strs_index(str, old);
    for (int j = 0;; j++) {
        if (index >= 0 && j < num) {
            strncat(dst, str + pos, index);
            strncat(dst, new, size3);
            pos = pos + index + size2;
            index = strs_index(str + pos, old);
        } else {
            strcat(dst, str + pos);
            break;
        }
    }
    return dst;
}

char *strs_replace_all(const char *str, const char *old, const char *new)
{
    CHECK_RET_PTR(str && old && new);
    size_t size1 = strlen(str);
    size_t size2 = strlen(old);
    size_t size3 = strlen(new);

    int cnt = strs_count(str, old);
    if (cnt <= 0) {
        char *buff = chcm_strsloc(size1 + 1);
        memcpy(buff, str, size1);
        return buff;
    }

    char *dst = NULL;
    size_t diff = size3 - size2;
    if (diff > 0) {
        dst = chcm_strsloc(size1 + cnt * (diff) + 1);
    } else {
        dst = chcm_strsloc(size1 + 1);
    }

    int pos = 0;
    int index = strs_index(str, old);
    for (;;) {
        if (index >= 0) {
            strncat(dst, str + pos, index);
            strncat(dst, new, size3);
            pos = pos + index + size2;
            index = strs_index(str + pos, old);
        } else {
            strcat(dst, str + pos);
            break;
        }
    }
    return dst;
}

char *strs_remove(char *str, const char *substr)
{
    CHECK_RET_PTR(str && substr);
    char *buff = strs_replace_all(str, substr, "");
    memcpy(str, buff, chcm_strslen(buff));
    strs_free(buff);
    return str;
}

char **strs_split(const char *str, const char *sep, int *num)
{
    CHECK_RET_PTR(str && sep && num);
    size_t size1 = strlen(str);
    size_t size2 = strlen(sep);
    char **strList = NULL;

    if (size2 == 0) {
        strList = chcm_strsloc2(size1, 2);
        for (int i = 0; i < size1; i++) {
            strList[i][0] = str[i];
        }
        *num = size1;
        return strList;
    }

    int cnt = strs_count(str, sep);
    if (cnt <= 0) {
        strList = chcm_strsloc2(1, size1 + 1);
        memcpy(strList[0], str, size1);
        *num = 1;
        return strList;
    }

    strList = phook.calloc(cnt + 1, sizeof(char *));
    int pos = 0;
    int index = strs_index(str, sep);
    int i = 0;
    for (;;) {
        if (index >= 0) {
            strList[i] = chcm_strsloc(index + 1);
            strncat(strList[i], str + pos, index);
            pos = pos + index + size2;
            index = strs_index(str + pos, sep);
            i++;
        } else {
            strList[i] = chcm_strsloc(size1 - pos + 1);
            strcat(strList[i], str + pos);
            break;
        }
    }

    *num = cnt + 1;
    return strList;
}

char **strs_split_n(const char *str, const char *sep, int *num)
{
    CHECK_RET_PTR(str && sep && num);
    size_t size1 = strlen(str);
    size_t size2 = strlen(sep);
    char **strList = NULL;

    if (*num == 0) {
        return strList;
    } else if (*num == 1) {
        strList = chcm_strsloc2(1, size1 + 1);
        strcat(strList[0], str);
        return strList;
    } else if (*num < 0) {
        return strs_split(str, sep, num);
    }

    if (size2 == 0) {
        strList = phook.calloc(*num, sizeof(char *));
        for (int i = 0; i < *num - 1; i++) {
            strList[i] = chcm_strsloc(2);
            strList[i][0] = str[i];
        }
        strList[*num - 1] = chcm_strsloc(size1 - (*num - 1) + 1);
        strcat(strList[*num - 1], str + *num - 1);
        return strList;
    }

    int cnt = strs_count(str, sep);
    if (cnt <= 0) {
        strList = chcm_strsloc2(1, size1 + 1);
        memcpy(strList[0], str, size1);
        *num = 1;
        return strList;
    }

    strList = phook.calloc(cnt + 1, sizeof(char *));
    int pos = 0;
    int index = strs_index(str, sep);
    int i = 0;
    for (int j = 0; j < *num - 1;) {
        if (index >= 0) {
            strList[i] = chcm_strsloc(index + 1);
            strncat(strList[i], str + pos, index);
            pos = pos + index + size2;
            index = strs_index(str + pos, sep);
            i++;
            j++;
        } else {
            break;
        }
    }
    strList[i] = chcm_strsloc(size1 - pos + 1);
    strcat(strList[i], str + pos);
    if (*num > cnt + 1) {
        *num = cnt + 1;
    }
    return strList;
}

char **strs_split_after(const char *str, const char *sep, int *num)
{
    CHECK_RET_PTR(str && sep && num);
    size_t size1 = strlen(str);
    size_t size2 = strlen(sep);
    char **strList = NULL;

    if (size2 == 0) {
        strList = chcm_strsloc2(size1, 2);
        for (int i = 0; i < size1; i++) {
            strList[i][0] = str[i];
        }
        *num = size1;
        return strList;
    }

    int cnt = strs_count(str, sep);
    if (cnt <= 0) {
        strList = chcm_strsloc2(1, size1 + 1);
        memcpy(strList[0], str, size1);
        *num = 1;
        return strList;
    }

    strList = phook.calloc(cnt + 1, sizeof(char *));
    int pos = 0;
    int index = strs_index(str, sep);
    int i = 0;
    for (;;) {
        if (index >= 0) {
            strList[i] = chcm_strsloc(index + size2 + 1);
            strncat(strList[i], str + pos, index + size2);
            pos = pos + index + size2;
            index = strs_index(str + pos, sep);
            i++;
        } else {
            strList[i] = chcm_strsloc(size1 - pos + 1);
            strcat(strList[i], str + pos);
            break;
        }
    }

    *num = cnt + 1;
    return strList;
}

char **strs_split_after_n(const char *str, const char *sep, int *num)
{
    CHECK_RET_PTR(str && sep && num);
    size_t size1 = strlen(str);
    size_t size2 = strlen(sep);
    char **strList = NULL;

    if (*num == 0) {
        return strList;
    } else if (*num == 1) {
        strList = chcm_strsloc2(1, size1 + 1);
        strcat(strList[0], str);
        return strList;
    } else if (*num < 0) {
        return strs_split_after(str, sep, num);
    }

    if (size2 == 0) {
        strList = phook.calloc(*num, sizeof(char *));
        for (int i = 0; i < *num - 1; i++) {
            strList[i] = chcm_strsloc(2);
            strList[i][0] = str[i];
        }
        strList[*num - 1] = chcm_strsloc(size1 - (*num - 1) + 1);
        strcat(strList[*num - 1], str + *num - 1);
        return strList;
    }

    int cnt = strs_count(str, sep);
    if (cnt <= 0) {
        strList = chcm_strsloc2(1, size1 + 1);
        memcpy(strList[0], str, size1);
        *num = 1;
        return strList;
    }

    strList = phook.calloc(cnt + 1, sizeof(char *));
    int pos = 0;
    int index = strs_index(str, sep);
    int i = 0;
    for (int j = 0; j < *num - 1;) {
        if (index >= 0) {
            strList[i] = chcm_strsloc(index + size2 + 1);
            strncat(strList[i], str + pos, index + size2);
            pos = pos + index + size2;
            index = strs_index(str + pos, sep);
            i++;
            j++;
        } else {
            break;
        }
    }
    strList[i] = chcm_strsloc(size1 - pos + 1);
    strcat(strList[i], str + pos);
    if (*num > cnt + 1) {
        *num = cnt + 1;
    }
    return strList;
}

char *strs_title(char *str)
{
    CHECK_RET_PTR(str);
    size_t size = strlen(str);
    bool upFlag = true;
    for (int i = 0; i < size; i++) {
        if (strs_is_space(str[i])) {
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

char *strs_trim(char *str, const char *cutset)
{
    CHECK_RET_PTR(str && cutset);
    size_t size = strlen(str);
    char *buff = chcm_strsloc(size + 1);
    int startPos = 0;
    int endPos = 0;
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
    strs_free(buff);
    return str;
}

char *strs_trim_func(char *str, bool (*func)(char ch))
{
    CHECK_RET_PTR(str && func);
    size_t size = strlen(str);
    char *buff = chcm_strsloc(size + 1);
    int startPos = 0;
    int endPos = 0;
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
    strs_free(buff);
    return str;
}

char *strs_trim_left(char *str, const char *cutset)
{
    CHECK_RET_PTR(str && cutset);
    size_t size = strlen(str);
    char *buff = chcm_strsloc(size + 1);
    int startPos = 0;
    for (int i = 0; i < size; i++) {
        if (strchr(cutset, str[i])) {
            continue;
        }
        startPos = i;
        break;
    }
    strcpy(buff, str + startPos);
    memcpy(str, buff, size);
    strs_free(buff);
    return str;
}

char *strs_trim_left_func(char *str, bool (*func)(char ch))
{
    CHECK_RET_PTR(str && func);
    size_t size = strlen(str);
    char *buff = chcm_strsloc(size + 1);
    int startPos = 0;
    for (int i = 0; i < size; i++) {
        if (func(str[i])) {
            continue;
        }
        startPos = i;
        break;
    }
    strcpy(buff, str + startPos);
    memcpy(str, buff, size);
    strs_free(buff);
    return str;
}

char *strs_trim_prefix(char *str, const char *prefix)
{
    CHECK_RET_PTR(str && prefix);
    if (strs_has_prefix(str, prefix)) {
        size_t size = chcm_strslen(str);
        char *buff = chcm_strsloc(size);
        strcpy(buff, str + strlen(prefix));
        memcpy(str, buff, size);
        strs_free(buff);
    }
    return str;
}

char *strs_trim_right(char *str, const char *cutset)
{
    CHECK_RET_PTR(str && cutset);
    size_t size = strlen(str);
    char *buff = chcm_strsloc(size + 1);
    int endPos = 0;
    for (int i = size - 1; i >= 0; i--) {
        if (strchr(cutset, str[i])) {
            continue;
        }
        endPos = i + 1;
        break;
    }
    strncpy(buff, str, endPos);
    memcpy(str, buff, size);
    strs_free(buff);
    return str;
}

char *strs_trim_right_func(char *str, bool (*func)(char ch))
{
    CHECK_RET_PTR(str && func);
    size_t size = strlen(str);
    char *buff = chcm_strsloc(size + 1);
    int endPos = 0;
    for (int i = size - 1; i >= 0; i--) {
        if (func(str[i])) {
            continue;
        }
        endPos = i + 1;
        break;
    }
    strncpy(buff, str, endPos);
    memcpy(str, buff, size);
    strs_free(buff);
    return str;
}

char *strs_trim_space(char *str)
{
    CHECK_RET_PTR(str);
    strs_trim_left_func(str, strs_is_space);
    strs_trim_right_func(str, strs_is_space);
    return str;
}

char *strs_trim_suffix(char *str, const char *suffix)
{
    CHECK_RET_PTR(str && suffix);
    if (strs_has_suffix(str, suffix)) {
        size_t size1 = strlen(str);
        size_t size2 = strlen(suffix);
        str[size1 - size2] = '\0';
    }
    return str;
}

char *strs_insert(const char *str, const char *substr, int pos)
{
    CHECK_RET_PTR(str && substr && (pos >= 0) && (strlen(str) >= pos));

    size_t size1 = strlen(str);
    size_t size2 = strlen(substr);
    char *dst = chcm_strsloc(size1 + size2 + 1);
    strncpy(dst, str, pos);
    strcat(dst, substr);
    strcat(dst, str + pos);
    return dst;
}
