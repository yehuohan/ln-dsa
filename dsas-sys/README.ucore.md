
# ucore OS(x86) learning

All copyrights belong to [ucore os lab](https://github.com/chyyuu/ucore_os_lab).

# boot

boot目录下是系统引导代码。

## bootasm.S

 - CPU启动过程
切换到32位保护模式，加载系统ucore到内存中，然后将控制权交给ucore

 - 引导过程

硬盘的第一个扇区为引导代码(bootblock)，由bootasm.S和bootmain.c编译，引导代码即是bootloader，它由BIOS加载至内存的0x7c00处，然后CPU在实模式从`%cs=0 %ip=0x7c00` 开始执行bootloader，CPU控制权转入c语言bootmain函数。具体的做法是，在Makefile编译时指定bootloader的代码入口地址为0x7c00（其它汇编编程也可以做到）：

```text
-e start -Ttext 0x7C00
```

 - 内核加载

硬盘的第二个扇区为内核代码(kernel)，引导代码将kernel加载至内存，并将CPU的控制权交给kernel。内核代码的置可以通过dd命令实现：

```bash
dd if=/dev/zero of=$@ count=10000               # 建立10000扇区大小的文件
dd if=$(bootblock_bin) of=$@ conv=notrunc       # 在第一个扇区放bootblock
dd if=$(kernel_bin) of=$@ seek=1 conv=notrunc   # 在第二个扇区开始放kernel
```

## bootmain.c

bootmain.c的主要作用是从硬盘中加载ELF格式的ucore系统内核kernel，并将CPU控制权交给ucore。

  - 硬盘的第一个扇区是bootloader
  - 硬盘的第二个扇区开始是ucore的kernel


# kern

kern目录是内核代码。
init目录是系统初始化代码。

## init/init.c

系统初始化的入口函数为kern_init，函数kern_init要一直运行（`while(1)`），这样CPU控制权给内核了。
