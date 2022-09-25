#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// #define STRS_PLAT_HOOKS /**< 自定义平台钩子函数 */

/**
 * @brief 释放内存空间，并将指针置空
 * 
 */
#define strs_free(ptr)                                                                                            \
    do {                                                                                                               \
        __strs_free(ptr);                                                                                              \
        ptr = NULL;                                                                                                    \
    } while (0)

/**
 * @brief 释放一个二重指针的所有内存空间，并将指针置空
 * 
 */
#define strs_free2(ptr, size)                                                                                     \
    do {                                                                                                               \
        __strs_free2(ptr, size);                                                                                       \
        ptr = NULL;                                                                                                    \
    } while (0)

/**
 * @brief 平台内存分配与释放的钩子
 * 
 */
typedef struct {
    void *(*calloc)(size_t nmemb, size_t size);
    void (*free)(void *);
} strs_plat_hook_t;

/**
 * @description: 设置平台hooks，注册calloc和free函数
 * @param {strs_plat_hook_t} *hooks
 * @return {*}
 */
int strs_set_plat_hooks(strs_plat_hook_t *hooks);

/**
 * @description: 判断字符是否是空白字符
 * @param {char} ch
 * @return {*}
 */
bool strs_is_space(char ch);

/**
 * @description: 判断字符是否是数字
 * @param {char} ch
 * @return {*}
 */
bool strs_is_number(char ch);

/**
 * @description: 判断字符是否是字母
 * @param {char} ch
 * @return {*}
 */
bool strs_is_letter(char ch);

/**
 * @description: 判断字符是否是大写字母
 * @param {char} ch
 * @return {*}
 */
bool strs_is_up_letter(char ch);

/**
 * @description: 判断字符是否是小写字母
 * @param {char} ch
 * @return {*}
 */
bool strs_is_low_letter(char ch);

/**
 * @description: 是否是结束符
 * @param {char} ch
 * @return {*}
 */
bool strs_is_end(char ch);

/**
 * @description: 为字符串分配存储空间，已经对存储空间进行初始化，需要free
 * @param {size_t} size
 * @return {*}
 */
char *chcm_strsloc(size_t size);

/**
 * @description: 为字符串列表分配空间，需要strs_free2()释放
 * @param {char} *
 * @param {int} row
 * @param {int} col
 * @return {*}
 */
char **chcm_strsloc2(int row, int col);

/**
 * @description: 字符串包含结束符的长度
 * @param {char} *str
 * @return {*}
 */
size_t chcm_strslen(const char *str);

/**
 * @description: 字符串打印函数，自动换行
 * @param {char} *format
 * @return {*}
 */
__attribute__((weak)) int println(const char *format, ...);

/**
 * @description: 释放空间，并将指针置空
 * @param {char} *str
 * @return {*}
 */
void __strs_free(void *str);

/**
 * @description: 释放字符串列表申请的内存空间
 * @param {char} *
 * @param {int} listSize
 * @return {*}
 */
void __strs_free2(char **strList, int listSize);

/**
 * @description: 字符串翻转，原字符串会被替换
 * @param {char} *str 注意，str指针指向的内存必须是可修改的，否则将段错误
 * @return {*} 返回翻转后的字符串
 */
char *strs_reverse(char *str);

/**
 * @description: 字符串中子串的数量，以空白为分割
 * @param {char} *str
 * @return {*}
 */
int strs_num(const char *str);

/**
 * @description: 拷贝str副本。需要strs_free()释放
 * @param {char} *str
 * @return {*}
 */
char *strs_dup(const char *str);

/**
 * @description: 拷贝str副本, 并释放str。
 * @param {char} *buf 目标buf
 * @param {char} *size buf的大小
 * @param {char} *str 目标字符串
 * @return {*} 拷贝完成后的buf地址, 如果str为空，将返回NULL
 */
char *strs_dup2(char *buf, unsigned int size, char *str);

/**
 * @description: 字符串转为全大写
 * @param {char} *str
 * @return {*}
 */
char *strs_to_upper(char *str);

/**
 * @description: 字符串转为全小写
 * @param {char} *str
 * @return {*}
 */
char *strs_to_lower(char *str);

/**
 * @description: 字符串str是否包含字符ch。
 * @param {char} *str
 * @param {char} ch
 * @return {*}
 */
bool strs_contain_char(const char *str, char ch);

/**
 * @description: 字符串str是否包含字符串substr。
 * @param {char} *str
 * @param {char} *substr
 * @return {*}
 */
bool strs_contains(const char *str, const char *substr);

/**
 * @description: 比较两个字符串是否相等。
 * @param {char} *str1
 * @param {char} *str2
 * @return {*}
 */
bool strs_compare(const char *str1, const char *str2);

/**
 * @description: chars字符串是否有字符在str字符串中出现过。
 * @param {char} *str
 * @param {char} *chars
 * @return {*}
 */
bool strs_contains_any(const char *str, const char *chars);

/**
 * @description: 比较两个字符串是否相等，比较时忽略大小写
 * @param {char} *str1
 * @param {char} *str2
 * @return {*}
 */
bool strs_equal_case(const char *str1, const char *str2);

/**
 * @description: 统计子串substr在字符串str中出现过多少次
 * @param {char} *str
 * @param {char} *substr
 * @return {*}
 */
int strs_count(const char *str, const char *substr);

/**
 * @description: 将字符串分割为子串，根据空白进行分割，需要使用strs_free2()释放
 * @param {char} *str
 * @param {char} *
 * @param {int} *listSize 字符串列表大小
 * @return {*}
 */
char **strs_fields(const char *str, int *listSize);

/**
 * @description: 将字符串分割为子串，根据func的规则进行分割（仍然包含了空白分割），需要使用strs_free2()释放
 * @param {char} *str
 * @param {func} func 
 * @param {int} *listSize 字符串列表大小
 * @return {*}
 */
char **strs_fields_func(const char *str, bool (*func)(char ch), int *listSize);

/**
 * @description: 字符串str是否拥有字符串prefix前缀
 * @param {char} *str
 * @param {char} *prefix
 * @return {*}
 */
bool strs_has_prefix(const char *str, const char *prefix);

/**
 * @description: 字符串str是否拥有字符串suffix后缀
 * @param {char} *str
 * @param {char} *suffix
 * @return {*}
 */
bool strs_has_suffix(const char *str, const char *suffix);

/**
 * @description: 子串substr出现在str中的位置
 * @param {char} *str
 * @param {char} *substr
 * @return {*}
 */
int strs_index(const char *str, const char *substr);

/**
 * @description: 拼接两个字符创，将sep作为分割。需要free
 * @param {char} *str1
 * @param {char} *str2
 * @param {char} *sep
 * @return {*}
 */
char *strs_join(const char *str1, const char *str2, const char *sep);

/**
 * @description: 拼接num个字符串，将sep作为分割。需要free
 * @param {char} *sep
 * @param {int} num
 * @return {*}
 */
char *strs_join_n(const char *sep, ...);

/**
 * @description: 返回子串substr在字符串str中最后一次出现的位置
 * @param {char} *str
 * @param {char} *substr
 * @return {*} 不存在返回-1
 */
int strs_last_index(const char *str, const char *substr);

/**
 * @description: 检索字符串 str1 中第一个匹配字符串 str2 中字符的字符，不包含空结束字符。
 * 也就是说，依次检验字符串 str1 中的字符，当被检验字符在字符串 str2 中也包含时，则停止检验，并返回该字符位置。
 * @param {char} *str
 * @param {char} *substr
 * @return {*} 不存在返回-1
 */
int strs_index_any(const char *str, const char *substr);

/**
 * @description: 返回字符ch在字符串str中首次出现的位置。
 * @param {char} *str
 * @param {char} ch
 * @return {*} 当不存在时返回-1
 */
int strs_index_char(const char *str, char ch);

/**
 * @description: 返回字符ch在字符串str中最后一次出现的位置。
 * @param {char} *str
 * @param {char} ch
 * @return {*} 不存在则返回-1
 */
int strs_last_index_char(const char *str, char ch);

/**
 * @description: 使用map的字符的映射规则生成新的字符串
 * @param {char} *str
 * @param {char} ch
 * @return {*} 
 */
char *strs_map(char *str, char (*map)(char ch));

/**
 * @description: 复制字符串str num次，并拼接到一起。需要strs_free()
 * @param {char} *str
 * @param {int} num
 * @return {*}
 */
char *strs_repeat(const char *str, int num);

/**
 * @description: 将字符串str中的字符串old部分替换为字符串new。需要strs_free()
 * @param {char} *str
 * @param {char} *old
 * @param {char} *new
 * @param {int} num  替换的字符串的数量。<0时，全部替换
 * @return {*}
 */
char *strs_replace(const char *str, const char *old, const char *new, int num);

/**
 * @description: 将字符串str中的字符串old全部替换为字符串new。需要strs_free()
 * @param {char} *str
 * @param {char} *old
 * @param {char} *new
 * @return {*}
 */
char *strs_replace_all(const char *str, const char *old, const char *new);

/**
 * @description: 删除字符串str中的所有子串substr
 * @param {char} *str
 * @param {char} *substr
 * @return {*}
 */
char *strs_remove(char *str, const char *substr);

/**
 * @description: 以sep作为分隔符，分隔字符串str。需要strs_free2()释放
 * @param {char} *str
 * @param {char} *sep
 * @param {int} *num 分割后的所有字符串的数量
 * @return {*} 分割后的字符串列表
 */
char **strs_split(const char *str, const char *sep, int *num);

/**
 * @description: 以sep作为分隔符，分隔字符串str。需要strs_free2()释放
 * @param {char} *str
 * @param {char} *sep
 * @param {int} *num 分割后的所有字符串的数量
 * @return {*} 分割后的字符串列表
 */
char **strs_split_n(const char *str, const char *sep, int *num);

/**
 * @description: 以sep为分割，分割字符串str, 分割后的字符串包含分隔符。需要strs_free2()释放
 * @param {char} *str
 * @param {char} *sep
 * @param {int} *num
 * @return {*} 分割后的字符串列表
 */
char **strs_split_after(const char *str, const char *sep, int *num);

/**
 * @description: 以sep作为分隔符，分割字符串str，分割后的字符串包含分隔符。需要strs_free2()释放。
 * @param {char} *str
 * @param {char} *sep
 * @param {int} *num
 * @return {*}
 */
char **strs_split_after_n(const char *str, const char *sep, int *num);

/**
 * @description: 字符串转化为标题格式，单词首字母大写。
 * @param {char} *str
 * @return {*}
 */
char *strs_title(char *str);

/**
 * @description: 移除str的前导和结尾，需要移除的字符来自cutset。
 * @param {char} *str
 * @param {char} *cutset
 * @return {*}
 */
char *strs_trim(char *str, const char *cutset);

/**
 * @description: 移除str的前导和结尾，需要移除的字符根据函数指针func的规则进行判断。
 * @param {char} *str
 * @param {char} ch
 * @return {*}
 */
char *strs_trim_func(char *str, bool (*func)(char ch));

/**
 * @description: 移除字符串str左边的一些字符，这些字符来自cutset。当字符不是cutset中的字符时停止。
 * @param {char} *str
 * @param {char} *cutset
 * @return {*}
 */
char *strs_trim_left(char *str, const char *cutset);

/**
 * @description: 移除字符串str左边的一些字符，字符是否被移除的规则来自func。当func返回false时停止。
 * @param {char} *str
 * @param {char} ch
 * @return {*}
 */
char *strs_trim_left_func(char *str, bool (*func)(char ch));

/**
 * @description: 移除字符串str的前缀字符串prefix。
 * @param {char} *str
 * @param {char} *prefix
 * @return {*}
 */
char *strs_trim_prefix(char *str, const char *prefix);

/**
 * @description: 移除字符串str右边的一些字符，这些字符来自cutset。当字符不是cutset中的字符时停止。
 * @param {char} *str
 * @param {char} *cutset
 * @return {*}
 */
char *strs_trim_right(char *str, const char *cutset);

/**
 * @description: 移除字符串str右边的一些字符，字符是否被移除的规则来自func。当func返回false时停止。
 * @param {char} *str
 * @param {char} ch
 * @return {*}
 */
char *strs_trim_right_func(char *str, bool (*func)(char ch));

/**
 * @description: 移除字符串前后的所有空白。
 * @param {char} *str
 * @return {*}
 */
char *strs_trim_space(char *str);

/**
 * @description: 移除字符串str的后缀字符串suffix。
 * @param {char} *str
 * @param {char} *suffix
 * @return {*}
 */
char *strs_trim_suffix(char *str, const char *suffix);

/**
 * @description: 在str字符串中的pos位置插入字符串substr。
 * @param {char} *str
 * @param {char} *substr
 * @param {int} pos
 * @return {*}
 */
char *strs_insert(const char *str, const char *substr, int pos);
