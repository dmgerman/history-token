multiline_comment|/* $Id: setup.c,v 1.8 2001/01/16 16:31:38 bjornw Exp $&n; *&n; *  linux/arch/cris/kernel/setup.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Copyright (c) 2000  Axis Communications AB&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of initialization&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/svinto.h&gt;
multiline_comment|/*&n; * Setup options&n; */
DECL|struct|drive_info_struct
DECL|member|dummy
DECL|variable|drive_info
r_struct
id|drive_info_struct
(brace
r_char
id|dummy
(braket
l_int|32
)braket
suffix:semicolon
)brace
id|drive_info
suffix:semicolon
DECL|variable|screen_info
r_struct
id|screen_info
id|screen_info
suffix:semicolon
DECL|variable|aux_device_present
r_int
r_char
id|aux_device_present
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_RAM
r_extern
r_int
id|rd_doload
suffix:semicolon
multiline_comment|/* 1 = load ramdisk, 0 = don&squot;t load */
r_extern
r_int
id|rd_prompt
suffix:semicolon
multiline_comment|/* 1 = prompt for ramdisk, 0 = don&squot;t prompt */
r_extern
r_int
id|rd_image_start
suffix:semicolon
multiline_comment|/* starting block # of image */
macro_line|#endif
r_extern
r_int
id|root_mountflags
suffix:semicolon
r_extern
r_char
id|_etext
comma
id|_edata
comma
id|_end
suffix:semicolon
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE 256
DECL|variable|command_line
r_static
r_char
id|command_line
(braket
id|COMMAND_LINE_SIZE
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|saved_command_line
r_char
id|saved_command_line
(braket
id|COMMAND_LINE_SIZE
)braket
suffix:semicolon
r_extern
r_const
r_int
r_int
id|text_start
comma
id|edata
suffix:semicolon
multiline_comment|/* set by the linker script */
r_extern
r_int
r_int
id|romfs_start
comma
id|romfs_length
comma
id|romfs_in_flash
suffix:semicolon
multiline_comment|/* from head.S */
multiline_comment|/* This mainly sets up the memory area, and can be really confusing.&n; *&n; * The physical DRAM is virtually mapped into dram_start to dram_end&n; * (usually c0000000 to c0000000 + DRAM size). The physical address is&n; * given by the macro __pa().&n; *&n; * In this DRAM, the kernel code and data is loaded, in the beginning.&n; * It really starts at c00a0000 to make room for some special pages - &n; * the start address is text_start. The kernel data ends at _end. After&n; * this the ROM filesystem is appended (if there is any).&n; * &n; * Between this address and dram_end, we have RAM pages usable to the&n; * boot code and the system.&n; *&n; */
DECL|function|setup_arch
r_void
id|__init
id|setup_arch
c_func
(paren
r_char
op_star
op_star
id|cmdline_p
)paren
(brace
r_int
r_int
id|bootmap_size
suffix:semicolon
r_int
r_int
id|start_pfn
comma
id|max_pfn
suffix:semicolon
r_int
r_int
id|memory_start
suffix:semicolon
r_extern
r_void
id|console_print_etrax
c_func
(paren
r_const
r_char
op_star
id|b
)paren
suffix:semicolon
macro_line|#if (defined(CONFIG_CHR_DEV_FLASH) || defined(CONFIG_BLK_DEV_FLASH))
multiline_comment|/* TODO: move this into flash_init I think */
id|flash_probe
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* register an initial console printing routine for printk&squot;s */
id|init_etrax_debug
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* we should really poll for DRAM size! */
id|high_memory
op_assign
op_amp
id|dram_end
suffix:semicolon
r_if
c_cond
(paren
id|romfs_in_flash
op_logical_or
op_logical_neg
id|romfs_length
)paren
(brace
multiline_comment|/* if we have the romfs in flash, or if there is no rom filesystem,&n;&t;&t; * our free area starts directly after the BSS &n;&t;&t; */
id|memory_start
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_end
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* otherwise the free area starts after the ROM filesystem */
id|printk
c_func
(paren
l_string|&quot;ROM fs in RAM, size %d bytes&bslash;n&quot;
comma
id|romfs_length
)paren
suffix:semicolon
id|memory_start
op_assign
id|romfs_start
op_plus
id|romfs_length
suffix:semicolon
)brace
multiline_comment|/* process 1&squot;s initial memory region is the kernel code/data */
id|init_mm.start_code
op_assign
(paren
r_int
r_int
)paren
op_amp
id|text_start
suffix:semicolon
id|init_mm.end_code
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_etext
suffix:semicolon
id|init_mm.end_data
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_edata
suffix:semicolon
id|init_mm.brk
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_end
suffix:semicolon
DECL|macro|PFN_UP
mdefine_line|#define PFN_UP(x)       (((x) + PAGE_SIZE-1) &gt;&gt; PAGE_SHIFT)
DECL|macro|PFN_DOWN
mdefine_line|#define PFN_DOWN(x)     ((x) &gt;&gt; PAGE_SHIFT)
DECL|macro|PFN_PHYS
mdefine_line|#define PFN_PHYS(x)     ((x) &lt;&lt; PAGE_SHIFT)
multiline_comment|/* min_low_pfn points to the start of DRAM, start_pfn points&n;&t; * to the first DRAM pages after the kernel, and max_low_pfn&n;&t; * to the end of DRAM.&n;&t; */
multiline_comment|/*&n;         * partially used pages are not usable - thus&n;         * we are rounding upwards:&n;         */
id|start_pfn
op_assign
id|PFN_UP
c_func
(paren
id|memory_start
)paren
suffix:semicolon
multiline_comment|/* usually c0000000 + kernel + romfs */
id|max_pfn
op_assign
id|PFN_DOWN
c_func
(paren
(paren
r_int
r_int
)paren
id|high_memory
)paren
suffix:semicolon
multiline_comment|/* usually c0000000 + dram size */
multiline_comment|/*&n;         * Initialize the boot-time allocator (start, end)&n;&t; *&n;&t; * We give it access to all our DRAM, but we could as well just have&n;&t; * given it a small slice. No point in doing that though, unless we&n;&t; * have non-contiguous memory and want the boot-stuff to be in, say,&n;&t; * the smallest area.&n;&t; *&n;&t; * It will put a bitmap of the allocated pages in the beginning&n;&t; * of the range we give it, but it won&squot;t mark the bitmaps pages&n;&t; * as reserved. We have to do that ourselves below.&n;&t; *&n;&t; * We need to use init_bootmem_node instead of init_bootmem&n;&t; * because our map starts at a quite high address (min_low_pfn).&n;         */
id|max_low_pfn
op_assign
id|max_pfn
suffix:semicolon
id|min_low_pfn
op_assign
id|PAGE_OFFSET
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|bootmap_size
op_assign
id|init_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
l_int|0
)paren
comma
id|start_pfn
comma
id|min_low_pfn
comma
id|max_low_pfn
)paren
suffix:semicolon
multiline_comment|/* And free all memory not belonging to the kernel (addr, size) */
id|free_bootmem
c_func
(paren
id|PFN_PHYS
c_func
(paren
id|start_pfn
)paren
comma
id|PFN_PHYS
c_func
(paren
id|max_pfn
op_minus
id|start_pfn
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;         * Reserve the bootmem bitmap itself as well. We do this in two&n;         * steps (first step was init_bootmem()) because this catches&n;         * the (very unlikely) case of us accidentally initializing the&n;         * bootmem allocator with an invalid RAM area.&n;&t; *&n;&t; * Arguments are start, size&n;         */
id|reserve_bootmem
c_func
(paren
id|PFN_PHYS
c_func
(paren
id|start_pfn
)paren
comma
id|bootmap_size
)paren
suffix:semicolon
multiline_comment|/* paging_init() sets up the MMU and marks all pages as reserved */
id|paging_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* we dont use a command line yet, so just let it be an empty string */
op_star
id|cmdline_p
op_assign
id|command_line
suffix:semicolon
id|strcpy
c_func
(paren
id|command_line
comma
l_string|&quot;root=/dev/rom&quot;
)paren
suffix:semicolon
multiline_comment|/* use the appended romdisk as root */
multiline_comment|/* give credit for the CRIS port */
id|printk
c_func
(paren
l_string|&quot;Linux/CRIS port on ETRAX 100LX (c) 2000 Axis Communications AB&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
DECL|macro|HAS_FPU
mdefine_line|#define HAS_FPU&t;&t;0x0001
DECL|macro|HAS_MMU
mdefine_line|#define HAS_MMU&t;&t;0x0002
DECL|macro|HAS_ETHERNET100
mdefine_line|#define HAS_ETHERNET100&t;0x0004
DECL|macro|HAS_TOKENRING
mdefine_line|#define HAS_TOKENRING&t;0x0008
DECL|macro|HAS_SCSI
mdefine_line|#define HAS_SCSI&t;0x0010
DECL|macro|HAS_ATA
mdefine_line|#define HAS_ATA&t;&t;0x0020
DECL|macro|HAS_USB
mdefine_line|#define HAS_USB&t;&t;0x0040
DECL|macro|HAS_IRQ_BUG
mdefine_line|#define HAS_IRQ_BUG&t;0x0080
DECL|struct|cpu_info
r_static
r_struct
id|cpu_info
(brace
DECL|member|model
r_char
op_star
id|model
suffix:semicolon
DECL|member|cache
r_int
r_int
id|cache
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|variable|cpu_info
)brace
id|cpu_info
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;ETRAX 1&quot;
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_string|&quot;ETRAX 2&quot;
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* Don&squot;t say it HAS_TOKENRING - there are&n;&t;&t;&t;&t;   lethal bugs in that chip that&n;&t;&t;&t;&t;   prevents T-R from ever working.&n;&t;&t;&t;&t;   Never go there, and never lead anyone&n;&t;&t;&t;&t;   into believing it can work.  BTW:&n;&t;&t;&t;&t;   Anyone working on a T-R network&n;&t;&t;&t;&t;   driver? :-) :-) :-) :-/ */
(brace
l_string|&quot;ETRAX 3&quot;
comma
l_int|0
comma
id|HAS_TOKENRING
)brace
comma
(brace
l_string|&quot;ETRAX 4&quot;
comma
l_int|0
comma
id|HAS_TOKENRING
op_or
id|HAS_SCSI
)brace
comma
(brace
l_string|&quot;Unknown&quot;
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_string|&quot;Unknown&quot;
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_string|&quot;Unknown&quot;
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_string|&quot;Simulator&quot;
comma
l_int|8
comma
id|HAS_ETHERNET100
op_or
id|HAS_SCSI
op_or
id|HAS_ATA
)brace
comma
(brace
l_string|&quot;ETRAX 100&quot;
comma
l_int|8
comma
id|HAS_ETHERNET100
op_or
id|HAS_SCSI
op_or
id|HAS_ATA
op_or
id|HAS_IRQ_BUG
)brace
comma
(brace
l_string|&quot;ETRAX 100&quot;
comma
l_int|8
comma
id|HAS_ETHERNET100
op_or
id|HAS_SCSI
op_or
id|HAS_ATA
)brace
comma
(brace
l_string|&quot;ETRAX 100LX&quot;
comma
l_int|8
comma
id|HAS_ETHERNET100
op_or
id|HAS_SCSI
op_or
id|HAS_ATA
op_or
id|HAS_USB
op_or
id|HAS_MMU
)brace
comma
(brace
l_string|&quot;Unknown&quot;
comma
l_int|0
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * BUFFER is PAGE_SIZE bytes long.&n; */
DECL|function|get_cpuinfo
r_int
id|get_cpuinfo
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
r_int
id|revision
suffix:semicolon
macro_line|#ifndef CONFIG_SVINTO_SIM
r_int
r_char
id|tmp
suffix:semicolon
id|__asm__
r_volatile
(paren
l_string|&quot;move vr,%0&quot;
suffix:colon
l_string|&quot;=rm&quot;
(paren
id|tmp
)paren
)paren
suffix:semicolon
id|revision
op_assign
id|tmp
suffix:semicolon
macro_line|#else
multiline_comment|/* Fake a revision for the simulator */
id|revision
op_assign
l_int|7
suffix:semicolon
macro_line|#endif
r_return
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;cpu&bslash;t&bslash;t: CRIS&bslash;n&quot;
l_string|&quot;cpu revision&bslash;t: %d&bslash;n&quot;
l_string|&quot;cpu model&bslash;t: %s&bslash;n&quot;
l_string|&quot;cache size&bslash;t: %d kB&bslash;n&quot;
l_string|&quot;fpu&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;mmu&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;ethernet&bslash;t: %s Mbps&bslash;n&quot;
l_string|&quot;token ring&bslash;t: %s&bslash;n&quot;
l_string|&quot;scsi&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;ata&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;usb&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;bogomips&bslash;t: %lu.%02lu&bslash;n&quot;
comma
id|revision
comma
id|cpu_info
(braket
id|revision
)braket
dot
id|model
comma
id|cpu_info
(braket
id|revision
)braket
dot
id|cache
comma
id|cpu_info
(braket
id|revision
)braket
dot
id|flags
op_amp
id|HAS_FPU
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|cpu_info
(braket
id|revision
)braket
dot
id|flags
op_amp
id|HAS_MMU
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|cpu_info
(braket
id|revision
)braket
dot
id|flags
op_amp
id|HAS_ETHERNET100
ques
c_cond
l_string|&quot;10/100&quot;
suffix:colon
l_string|&quot;10&quot;
comma
id|cpu_info
(braket
id|revision
)braket
dot
id|flags
op_amp
id|HAS_TOKENRING
ques
c_cond
l_string|&quot;4/16 Mbps&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|cpu_info
(braket
id|revision
)braket
dot
id|flags
op_amp
id|HAS_SCSI
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|cpu_info
(braket
id|revision
)braket
dot
id|flags
op_amp
id|HAS_ATA
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|cpu_info
(braket
id|revision
)braket
dot
id|flags
op_amp
id|HAS_USB
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
(paren
id|loops_per_jiffy
op_star
id|HZ
op_plus
l_int|500
)paren
op_div
l_int|100000
comma
(paren
(paren
id|loops_per_jiffy
op_star
id|HZ
op_plus
l_int|500
)paren
op_div
l_int|1000
)paren
op_mod
l_int|100
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PROC_FS */
eof
