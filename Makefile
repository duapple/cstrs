#-----------------------------------------------
# 生成程序名称
#-----------------------------------------------
target := test

#-----------------------------------------------
# 选择编译工具链
#-----------------------------------------------
CROSS =
export CC = ${CROSS}gcc
export AR = ${CROSS}ar

#-----------------------------------------------
# 全局编译参数变量
#-----------------------------------------------
export CFLAGS_ENV=-Wall -g -ffunction-sections -fdata-sections -std=c99 -fPIC 

#-----------------------------------------------
# 全局编译路径变量
#-----------------------------------------------
export ROOT_DIR = $(shell pwd)
export BUILD_DIR = build/out
export OBJS_CACHE = $(BUILD_DIR)/objs.cache

#-----------------------------------------------
# 定义全局头文件路径
# 相对路径放 INCLUDE_ENV, 绝对路径放 INCLUDE_ABS_ENV
# （绝对路径头文件传递到子Makefile时无需转换路径）
#-----------------------------------------------
export INCLUDE_ENV = -I.

export INCLUDE_ABS_ENV = -I$(ROOT_DIR)

#-----------------------------------------------
# 生成程序输出路径，使用相对路径
#-----------------------------------------------
outdir := .

#-----------------------------------------------
# 源文件路径，使用相对路径
#-----------------------------------------------
# src := $(foreach d, $(srcdir), $(wildcard $(d)/*.c))
src := test.c strs.c

#-----------------------------------------------
# 编译参数
#-----------------------------------------------
CFLAGS := $(CFLAGS_ENV) 

#-----------------------------------------------
# 链接参数
#-----------------------------------------------
LDFLAGS := -Wl,-Map=$(BUILD_DIR)/object.map,--cref,--gc-section -fPIC

#-----------------------------------------------
# 添加子模块，使用相对路径
#-----------------------------------------------
MOD := 

#-----------------------------------------------
# 头文件路径
#-----------------------------------------------
INCLUDE := $(INCLUDE_ENV) $(INCLUDE_ABS_ENV)

#-----------------------------------------------
# 链接时需要的静态库
#-----------------------------------------------
LIB += 

#-----------------------------------------------
# 编译前准备
#-----------------------------------------------
obj := $(src:.c=.o)
dep := $(src:.c=.d)
build := $(BUILD_DIR)
objs := $(addprefix $(build)/, $(obj))
deps := $(addprefix $(build)/, $(dep))
target_out := $(outdir)/$(target)
$(shell mkdir -p $(BUILD_DIR))
$(shell echo "" > $(OBJS_CACHE))

all: $(target_out)
	@echo "All completed."

#-----------------------------------------------
# 子模块编译
#-----------------------------------------------
module: ${MOD}

${MOD}: 
	@echo 
	@+${MAKE} -C $@
	@echo 

#-----------------------------------------------
# 生成程序
#-----------------------------------------------
$(target_out): $(objs) module
	@mkdir -p $(outdir)
	@sort -u $(OBJS_CACHE) -o $(OBJS_CACHE)
	$(CC) -o $(target_out) $(objs) $$(cat $(OBJS_CACHE)) -Xlinker "-(" $(LIB) -Xlinker "-)" $(LDFLAGS)
	@echo "-------------------------------------------"
	@echo "Generate $(target) successs."
	@echo "-------------------------------------------"

-include $(deps)

#-----------------------------------------------
# 生成.o文件的所有依赖关系
#-----------------------------------------------
$(build)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

#-----------------------------------------------
# 生成.d文件的所有依赖关系
#-----------------------------------------------
$(build)/%.d: %.c
	@set -e; mkdir -p $(@D); rm -f $@; \
	$(CC) -MM $(CFLAGS) $(INCLUDE) $< > $@.$$$$; \
	sed 's,\($(*F)\)\.o[ :]*,$(build)/$(<D)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$;\

#echo "generate dependencies $(@F) ."

.PHONY: clean clean_all ${MOD} all module $(MOD_CLEAN) $(MOD_CLEAN_ALL)

#-----------------------------------------------
# 子模块clean
#-----------------------------------------------
MOD_CLEAN = $(addprefix clean_, ${MOD})
$(MOD_CLEAN):
	@echo 
	@+${MAKE} -C $(patsubst clean_%,%,$@) clean
	@echo 

MOD_CLEAN_ALL = $(addprefix clean_all_, ${MOD})
$(MOD_CLEAN_ALL):
	@echo 
	@+${MAKE} -C $(patsubst clean_all_%,%,$@) clean_all
	@echo 

clean: $(MOD_CLEAN)
	@echo "Cleanning ..."
	-@rm -f $(target_out) $(objs) $(OBJS_CACHE)
	@echo "Clean completed."

clean_all: $(MOD_CLEAN_ALL)
	-@rm -rf $(BUILD_DIR) $(target_out)
	@echo "Remove build/out dir."