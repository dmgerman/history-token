multiline_comment|/* $Id: setup.c,v 1.2 2001/12/18 13:35:20 bjornw Exp $&n; *&n; *  linux/arch/cris/kernel/setup.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Copyright (c) 2001  Axis Communications AB&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of initialization&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
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
multiline_comment|/* This mainly sets up the memory area, and can be really confusing.&n; *&n; * The physical DRAM is virtually mapped into dram_start to dram_end&n; * (usually c0000000 to c0000000 + DRAM size). The physical address is&n; * given by the macro __pa().&n; *&n; * In this DRAM, the kernel code and data is loaded, in the beginning.&n; * It really starts at c0004000 to make room for some special pages - &n; * the start address is text_start. The kernel data ends at _end. After&n; * this the ROM filesystem is appended (if there is any).&n; * &n; * Between this address and dram_end, we have RAM pages usable to the&n; * boot code and the system.&n; *&n; */
r_void
id|__init
DECL|function|setup_arch
id|setup_arch
c_func
(paren
r_char
op_star
op_star
id|cmdline_p
)paren
(brace
r_extern
r_void
id|init_etrax_debug
c_func
(paren
r_void
)paren
suffix:semicolon
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
multiline_comment|/* if we have the romfs in flash, or if there is no rom filesystem,&n;&t;&t; * our free area starts directly after the BSS&n;&t;&t; */
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
l_string|&quot;ROM fs in RAM, size %lu bytes&bslash;n&quot;
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
multiline_comment|/* We dont use a command line yet, so just re-initialize it without&n;&t;   saving anything that might be there.  */
op_star
id|cmdline_p
op_assign
id|command_line
suffix:semicolon
r_if
c_cond
(paren
id|romfs_in_flash
)paren
(brace
id|strncpy
c_func
(paren
id|command_line
comma
l_string|&quot;root=&quot;
comma
id|COMMAND_LINE_SIZE
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|command_line
op_plus
l_int|5
comma
id|CONFIG_ETRAX_ROOT_DEVICE
comma
id|COMMAND_LINE_SIZE
op_minus
l_int|5
)paren
suffix:semicolon
multiline_comment|/* Save command line copy for /proc/cmdline */
id|memcpy
c_func
(paren
id|saved_command_line
comma
id|command_line
comma
id|COMMAND_LINE_SIZE
)paren
suffix:semicolon
id|saved_command_line
(braket
id|COMMAND_LINE_SIZE
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
multiline_comment|/* give credit for the CRIS port */
id|printk
c_func
(paren
l_string|&quot;Linux/CRIS port on ETRAX 100LX (c) 2001 Axis Communications AB&bslash;n&quot;
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
DECL|macro|HAS_MMU_BUG
mdefine_line|#define HAS_MMU_BUG&t;0x0100
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
multiline_comment|/* The first four models will never ever run this code and are&n;&t;   only here for display.  */
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
op_or
id|HAS_MMU_BUG
)brace
comma
(brace
l_string|&quot;ETRAX 100LX v2&quot;
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
multiline_comment|/* This entry MUST be the last */
)brace
suffix:semicolon
DECL|function|show_cpuinfo
r_static
r_int
id|show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
r_int
r_int
id|revision
suffix:semicolon
r_struct
id|cpu_info
op_star
id|info
suffix:semicolon
multiline_comment|/* read the version register in the CPU and print some stuff */
id|revision
op_assign
id|rdvr
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|revision
op_ge
r_sizeof
id|cpu_info
op_div
r_sizeof
op_star
id|cpu_info
)paren
id|info
op_assign
op_amp
id|cpu_info
(braket
r_sizeof
id|cpu_info
op_div
r_sizeof
op_star
id|cpu_info
op_minus
l_int|1
)braket
suffix:semicolon
r_else
id|info
op_assign
op_amp
id|cpu_info
(braket
id|revision
)braket
suffix:semicolon
r_return
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;cpu&bslash;t&bslash;t: CRIS&bslash;n&quot;
l_string|&quot;cpu revision&bslash;t: %lu&bslash;n&quot;
l_string|&quot;cpu model&bslash;t: %s&bslash;n&quot;
l_string|&quot;cache size&bslash;t: %d kB&bslash;n&quot;
l_string|&quot;fpu&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;mmu&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;mmu DMA bug&bslash;t: %s&bslash;n&quot;
l_string|&quot;ethernet&bslash;t: %s Mbps&bslash;n&quot;
l_string|&quot;token ring&bslash;t: %s&bslash;n&quot;
l_string|&quot;scsi&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;ata&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;usb&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;bogomips&bslash;t: %lu.%02lu&bslash;n&quot;
comma
id|revision
comma
id|info-&gt;model
comma
id|info-&gt;cache
comma
id|info-&gt;flags
op_amp
id|HAS_FPU
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|info-&gt;flags
op_amp
id|HAS_MMU
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|info-&gt;flags
op_amp
id|HAS_MMU_BUG
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|info-&gt;flags
op_amp
id|HAS_ETHERNET100
ques
c_cond
l_string|&quot;10/100&quot;
suffix:colon
l_string|&quot;10&quot;
comma
id|info-&gt;flags
op_amp
id|HAS_TOKENRING
ques
c_cond
l_string|&quot;4/16 Mbps&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|info-&gt;flags
op_amp
id|HAS_SCSI
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|info-&gt;flags
op_amp
id|HAS_ATA
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|info-&gt;flags
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
l_int|500000
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
l_int|5000
)paren
op_mod
l_int|100
)paren
suffix:semicolon
)brace
DECL|function|c_start
r_static
r_void
op_star
id|c_start
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
id|loff_t
op_star
id|pos
)paren
(brace
multiline_comment|/* We only got one CPU... */
r_return
op_star
id|pos
OL
l_int|1
ques
c_cond
(paren
r_void
op_star
)paren
l_int|1
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|c_next
r_static
r_void
op_star
id|c_next
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
(brace
op_increment
op_star
id|pos
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|c_stop
r_static
r_void
id|c_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
)brace
DECL|variable|cpuinfo_op
r_struct
id|seq_operations
id|cpuinfo_op
op_assign
(brace
dot
id|start
op_assign
id|c_start
comma
dot
id|next
op_assign
id|c_next
comma
dot
id|stop
op_assign
id|c_stop
comma
dot
id|show
op_assign
id|show_cpuinfo
comma
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_PROC_FS */
eof
