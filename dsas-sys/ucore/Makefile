
#===============================================================================
# Paths and directories
#===============================================================================
SRC_BOOT_DIR := boot
INC_BOOT_DIR := boot\
				libs
SRC_TOOL_DIR := tools
SRC_KERN_DIR := kern/driver \
				kern/init \
				kern/libs \
				libs
INC_KERN_DIR := kern/driver \
				libs
OBJ_DIR      := obj
BIN_DIR      := bin


#===============================================================================
# Commands
#===============================================================================
#V		:= @
CC		:= gcc
GDB		:= gdb
CFLAGS	:= -Wall -ggdb -m32 -Os -fno-builtin -nostdinc
CFLAGS	+= $(shell $(CC) -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector)
CFLAGS	+= $(addprefix -I, $(INC_BOOT_DIR))
CTYPE	:= c S
KCFLAGS := -Wall -ggdb -m32 -Os -fno-builtin -nostdinc
KCFLAGS	+= $(shell $(CC) -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector)
KCFLAGS += $(addprefix -I, $(INC_KERN_DIR))

LD      := ld
LDFLAGS	:= -m elf_i386 -N -e start -Ttext 0x7C00
KLDFLAGS:= -m elf_i386 -e kern_init -Ttext 0x100000

OBJCOPY := objcopy
OBJDUMP := objdump

COPY	:= cp
MKDIR   := mkdir -p
MV		:= mv
RM		:= rm -f
SED 	:= sed


#===============================================================================
# Functions and variables
#===============================================================================
# make directories
define make_dir
	$(foreach str,\
			  $(addprefix $(OBJ_DIR)/,$(SRC_BOOT_DIR) $(SRC_KERN_DIR)),\
			  $(shell $(MKDIR) $(str)))
	$(shell $(MKDIR) $(BIN_DIR))
endef

# list all source files in directories: (#src_dirs, #types)
get_src = $(filter $(addprefix %.,$(2)),$(wildcard $(addsuffix /*,$(1))))

# get .o obj files: (#obj_dirs, #src_files])
get_obj = $(addprefix $(1)/,$(addsuffix .o,$(basename $(2))))

# create target: (#obj_dir, #src_file, #cflags)
define do_create_obj_target
$(1)/$(basename $(2)).o: $(2)
	$(V)$(CC) $(3) -c $$< -o $$@
endef
create_obj_target = $(foreach line,$(2),$(eval $(call do_create_obj_target,$(1),$(line),$(3))))


$(call make_dir)
boot_src_files := $(call get_src,$(SRC_BOOT_DIR),$(CTYPE))
boot_obj_files := $(call get_obj,$(OBJ_DIR),$(boot_src_files))

bootblock_obj := $(OBJ_DIR)/bootblock
bootblock_bin := $(BIN_DIR)/bootblock
sign_bin := $(BIN_DIR)/sign

kernel_src_files := $(call get_src,$(SRC_KERN_DIR),$(CTYPE))
kernel_obj_files := $(call get_obj,$(OBJ_DIR),$(kernel_src_files))
kernel_bin := $(BIN_DIR)/kernel

UCOREIMG := $(BIN_DIR)/ucore.img


#===============================================================================
# Targets for ucore
#===============================================================================
# ucore.img
# ucore.img在硬盘上的分布：
# 		第一个扇区为引导代码(bootblock)
# 		第二个扇区开始为kernel代码
$(UCOREIMG): $(bootblock_bin) $(kernel_bin)
	$(V)dd if=/dev/zero of=$@ count=10000
	$(V)dd if=$(bootblock_bin) of=$@ conv=notrunc
	$(V)dd if=$(kernel_bin) of=$@ seek=1 conv=notrunc

# bootblock
$(bootblock_bin): $(bootblock_obj) $(sign_bin)
	$(V)$(OBJDUMP) -S $< > $@.asm
	$(V)$(OBJCOPY) -S -O binary $< $@.out
	$(V)$(sign_bin) $@.out $@

$(bootblock_obj): $(boot_obj_files)
	$(V)$(LD) $(LDFLAGS) $^ -o $@

$(call create_obj_target,$(OBJ_DIR),$(boot_src_files),$(CFLAGS))

$(sign_bin): $(SRC_TOOL_DIR)/sign.c
	$(V)$(CC) -g -Wall -O2 $^ -o $@

# kernel
$(kernel_bin): $(kernel_obj_files)
	$(V)$(LD) $(KLDFLAGS) $^ -o $@
	$(V)$(OBJDUMP) -S $@ > $@.asm
	$(V)$(OBJDUMP) -t $@ | $(SED) '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > $@.sym

$(call create_obj_target,$(OBJ_DIR),$(kernel_src_files),$(KCFLAGS))

.PHONY: test
test:
	@echo
	@echo $(boot_src_files)
	@echo $(boot_obj_files)
	@echo $(kernel_src_files)
	@echo $(kernel_obj_files)
	@echo


#===============================================================================
# Targets for qemu
#===============================================================================
QEMU := qemu-system-x86_64
TERMINAL := xfce4-terminal

.PHONY: qemu
qemu: $(UCOREIMG)
	$(V)$(QEMU) -parallel stdio -hda $< -serial null

debug: $(UCOREIMG)
	$(V)$(QEMU) -S -s -parallel stdio -hda $< -serial null &
	$(V)sleep 2
	$(V)$(TERMINAL) -e "$(GDB) -q -x tools/gdbinit"


#===============================================================================
#  Clean
#===============================================================================
.PHONY: clean
clean:
	$(RM) -r $(OBJ_DIR) $(BIN_DIR)
