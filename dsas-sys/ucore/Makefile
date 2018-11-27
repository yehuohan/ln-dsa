
#===============================================================================
# Paths and directories
#===============================================================================
SRC_BOOT_DIR := boot
SRC_TOOL_DIR := tools
INC_DIR      := libs boot
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
CFLAGS	+= $(addprefix -I, $(INC_DIR))
CTYPE	:= c S

LD      := ld
LDFLAGS	:= -m elf_i386
LDFLAGS += -N -e start -Ttext 0x7C00

OBJCOPY := objcopy
OBJDUMP := objdump

COPY	:= cp
MKDIR   := mkdir -p
MV		:= mv
RM		:= rm -f


#===============================================================================
# Functions and variables
#===============================================================================
# make directories
define make_dir
	$(shell $(MKDIR) $(OBJ_DIR)/$(SRC_BOOT_DIR))
	$(shell $(MKDIR) $(BIN_DIR))
endef

# list all source files in directories: (#directories, #types)
get_src = $(filter $(addprefix %.,$(2)),$(wildcard $(addsuffix /*,$(1))))

# get .o obj files: (#directories, #src_files])
get_obj = $(addprefix $(1)/,$(addsuffix .o,$(basename $(2))))

# get target: (#obj, #src, #cflags)
#create_obj_target = $()


$(call make_dir)
boot_src_files = $(call get_src,$(SRC_BOOT_DIR),$(CTYPE))
boot_obj_files = $(call get_obj,$(OBJ_DIR),$(boot_src_files))

bootblock_obj = $(OBJ_DIR)/bootblock
bootblock_bin = $(BIN_DIR)/bootblock
sign_bin = $(BIN_DIR)/sign


#===============================================================================
# Targets for ucore
#===============================================================================
# ucore.img
UCOREIMG := $(BIN_DIR)/ucore.img

$(UCOREIMG): $(bootblock_bin)
	$(V)dd if=/dev/zero of=$@ count=10000
	$(V)dd if=$< of=$@ conv=notrunc

# bootblock
$(bootblock_bin): $(bootblock_obj) $(sign_bin)
	$(V)$(OBJDUMP) -S $< > $@.asm
	$(V)$(OBJCOPY) -S -O binary $< $@.out
	$(V)$(sign_bin) $@.out $@

$(bootblock_obj): $(boot_obj_files)
	$(V)$(LD) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.S
	$(V)$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.c
	$(V)$(CC) $(CFLAGS) -c $< -o $@

# sign tool
$(sign_bin): $(SRC_TOOL_DIR)/sign.c
	$(V)$(CC) -g -Wall -O2 $^ -o $@

.PHONY: test
test:
	@echo
	@echo $(boot_src_files)
	@echo $(boot_obj_files)
	@echo


#===============================================================================
# Targets for qemu
#===============================================================================
QEMU := qemu-system-x86_64

.PHONY: qemu
qemu: $(UCOREIMG)
	$(V)$(QEMU) -parallel stdio -hda $< -serial null


#===============================================================================
#  Clean
#===============================================================================
.PHONY: clean
clean:
	$(RM) -r $(OBJ_DIR) $(BIN_DIR)
