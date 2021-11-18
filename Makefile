#------------------------------
# 选择编译工具链
#------------------------------
CROSS=
#arm-himix100-linux-
export CC=${CROSS}gcc
export AR=${CROSS}ar

#------------------------------
# 全局编译参数变量
#------------------------------
export CFLAGS_ENV=-Wall -Os -ffunction-sections -fdata-sections
#-g 

#-------------------------------
# 全局编译路径变量
#-------------------------------
export ROOT_DIR=$(shell pwd)
export mk_dir=$(pwd)/build/tool
export BUILD_DIR=$(ROOT_DIR)/build/out
export APP_DIR=$(ROOT_DIR)/app
export MOD_DIR=$(ROOT_DIR)/mod

#------------------------------
# 生成程序名称
#------------------------------
target := main

#------------------------------
# 生成程序输出路径
#------------------------------
outdir := $(ROOT_DIR)

#----------------------------------------
# 源文件路径（采用相对路径）
#----------------------------------------
srcdir := . src source 

#----------------------------------------
# 头文件路径
#----------------------------------------
INCLUDE := -I./include 
INCLUDE += $(addprefix -I./, $(srcdir))
INCLUDE += -I./mod/app

#----------------------------------------
# 编译参数
#----------------------------------------
CFLAGS := $(CFLAGS_ENV)

#------------------------------
# 链接参数
#------------------------------
LDLAGS := -Wl,-Map=$(BUILD_DIR)/object.map,--cref,--gc-section

#------------------------------
# 模块路径
#------------------------------
MOD := app

#------------------------------
# 链接时需要的库
#------------------------------
LIB += $(foreach d, $(addsuffix /lib, $(addprefix $(MOD_DIR)/, $(MOD))), $(wildcard $(d)/*.a))

#------------------------------
# 编译前准备
#------------------------------
src := $(foreach d, $(srcdir), $(wildcard $(d)/*.c))
obj := $(src:.c=.o)
dep := $(src:.c=.d)
build := $(BUILD_DIR)/$(subst $(ROOT_DIR)/,,$(CURDIR)/)
objs := $(addprefix $(build)/, $(obj))
deps := $(addprefix $(build)/, $(dep))
target_out := $(outdir)/$(target)

all: $(target_out)

#-----------------------------------------------
# 子模块编译
#-----------------------------------------------
module:
	@make -C $(MOD_DIR)/$(MOD)

#-----------------------------------------------
# 生成静态库及依赖关系
#-----------------------------------------------
$(target_out):$(objs)
	@mkdir -p $(addprefix $(build)/, $(srcdir))
	@mkdir -p $(outdir)
	$(CC) -o $(target_out) $(objs) $(INCLUDE) -Xlinker "-(" $(LIB) -Xlinker "-)" $(LDLAGS)
	@echo "-------------------------------------------"
	@echo "create $(target) successs."
	@echo "-------------------------------------------"

-include $(deps)

#-----------------------------------------------
# 生成.o文件的所有依赖关系
#-----------------------------------------------
$(build)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

#-----------------------------------------------
# 生成.d文件的所有依赖关系
#-----------------------------------------------
$(build)/%.d: %.c
	@set -e; mkdir -p $(@D); rm -f $@; \
	$(CC) -MM $(CFLAGS) $(INCLUDE) $< > $@.$$$$; \
	sed 's,\($(*F)\)\.o[ :]*,$(build)/$(<D)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$;\

#echo "generate dependencies $(@F) ."

.PHONY: clean clean_all

clean_all:
	-@rm -rf $(BUILD_DIR)

clean:
	@echo "cleanning ..."
	-@make -C $(MOD_DIR)/$(MOD) clean
	-@rm -f $(target_out) $(objs)
	@echo "clean completed."