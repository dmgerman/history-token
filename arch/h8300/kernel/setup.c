multiline_comment|/*&n; *  linux/arch/h8300/kernel/setup.c&n; *&n; *  Copyleft  ()) 2000       James D. Schettine {james@telos-systems.com}&n; *  Copyright (C) 1999,2000  Greg Ungerer (gerg@snapgear.com)&n; *  Copyright (C) 1998,1999  D. Jeff Dionne &lt;jeff@lineo.ca&gt;&n; *  Copyright (C) 1998       Kenneth Albanowski &lt;kjahds@kjahds.com&gt;&n; *  Copyright (C) 1995       Hamish Macdonald&n; *  Copyright (C) 2000       Lineo Inc. (www.lineo.com) &n; *  Copyright (C) 2001 &t;     Lineo, Inc. &lt;www.lineo.com&gt;&n; *&n; *  H8/300 porting Yoshinori Sato &lt;ysato@users.sourceforge.jp&gt;&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of system setup&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#endif
macro_line|#if defined(__H8300H__)
DECL|macro|CPU
mdefine_line|#define CPU &quot;H8/300H&quot;
macro_line|#include &lt;asm/regs306x.h&gt;
macro_line|#endif
macro_line|#if defined(__H8300S__)
DECL|macro|CPU
mdefine_line|#define CPU &quot;H8S&quot;
macro_line|#include &lt;asm/regs267x.h&gt;
macro_line|#endif
DECL|macro|STUBSIZE
mdefine_line|#define STUBSIZE 0xc000;
DECL|variable|rom_length
r_int
r_int
id|rom_length
suffix:semicolon
DECL|variable|memory_start
r_int
r_int
id|memory_start
suffix:semicolon
DECL|variable|memory_end
r_int
r_int
id|memory_end
suffix:semicolon
DECL|variable|command_line
r_char
id|command_line
(braket
l_int|512
)braket
suffix:semicolon
DECL|variable|saved_command_line
r_char
id|saved_command_line
(braket
l_int|512
)braket
suffix:semicolon
r_extern
r_int
id|_stext
comma
id|_etext
comma
id|_sdata
comma
id|_edata
comma
id|_sbss
comma
id|_ebss
comma
id|_end
suffix:semicolon
r_extern
r_int
id|_ramstart
comma
id|_ramend
suffix:semicolon
r_extern
r_char
id|_target_name
(braket
)braket
suffix:semicolon
r_extern
r_void
id|h8300_gpio_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#if (defined(CONFIG_H8300H_SIM) || defined(CONFIG_H8S_SIM)) &bslash;&n;    &amp;&amp; defined(CONFIG_GDB_MAGICPRINT)
multiline_comment|/* printk with gdb service */
DECL|function|gdb_console_output
r_static
r_void
id|gdb_console_output
c_func
(paren
r_struct
id|console
op_star
id|c
comma
r_const
r_char
op_star
id|msg
comma
r_int
id|len
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|len
OG
l_int|0
suffix:semicolon
id|len
op_decrement
)paren
(brace
id|asm
c_func
(paren
l_string|&quot;mov.w %0,r2&bslash;n&bslash;t&quot;
l_string|&quot;jsr @0xc4&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
op_star
id|msg
op_increment
)paren
suffix:colon
l_string|&quot;er2&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Setup initial baud/bits/parity. We do two things here:&n; *&t;- construct a cflag setting for the first rs_open()&n; *&t;- initialize the serial port&n; *&t;Return non-zero if we didn&squot;t find a serial port.&n; */
DECL|function|gdb_console_setup
r_static
r_int
id|__init
id|gdb_console_setup
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_char
op_star
id|options
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|gdb_console
r_static
r_const
r_struct
id|console
id|gdb_console
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;gdb_con&quot;
comma
dot
id|write
op_assign
id|gdb_console_output
comma
dot
id|device
op_assign
l_int|NULL
comma
dot
id|setup
op_assign
id|gdb_console_setup
comma
dot
id|flags
op_assign
id|CON_PRINTBUFFER
comma
dot
id|index
op_assign
op_minus
l_int|1
comma
)brace
suffix:semicolon
macro_line|#endif
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
id|bootmap_size
suffix:semicolon
id|memory_start
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_ramstart
suffix:semicolon
multiline_comment|/* allow for ROMFS on the end of the kernel */
r_if
c_cond
(paren
id|memcmp
c_func
(paren
(paren
r_void
op_star
)paren
id|memory_start
comma
l_string|&quot;-rom1fs-&quot;
comma
l_int|8
)paren
op_eq
l_int|0
)paren
(brace
macro_line|#if defined(CONFIG_BLK_DEV_INITRD)
id|initrd_start
op_assign
id|memory_start
suffix:semicolon
id|initrd_end
op_assign
id|memory_start
op_add_assign
id|be32_to_cpu
c_func
(paren
(paren
(paren
r_int
r_int
op_star
)paren
(paren
id|memory_start
)paren
)paren
(braket
l_int|2
)braket
)paren
suffix:semicolon
macro_line|#else
id|memory_start
op_add_assign
id|be32_to_cpu
c_func
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|memory_start
)paren
(braket
l_int|2
)braket
)paren
suffix:semicolon
macro_line|#endif
)brace
id|memory_start
op_assign
id|PAGE_ALIGN
c_func
(paren
id|memory_start
)paren
suffix:semicolon
macro_line|#if !defined(CONFIG_BLKDEV_RESERVE)
id|memory_end
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_ramend
suffix:semicolon
multiline_comment|/* by now the stack is part of the init task */
macro_line|#if defined(CONFIG_GDB_DEBUG)
id|memory_end
op_sub_assign
id|STUBSIZE
suffix:semicolon
macro_line|#endif
macro_line|#else
r_if
c_cond
(paren
(paren
id|memory_end
OL
id|CONFIG_BLKDEV_RESERVE_ADDRESS
)paren
op_logical_and
(paren
id|memory_end
OG
id|CONFIG_BLKDEV_RESERVE_ADDRESS
)paren
multiline_comment|/* overlap userarea */
id|memory_end
op_assign
id|CONFIG_BLKDEV_RESERVE_ADDRESS
suffix:semicolon
macro_line|#endif
id|init_mm.start_code
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_stext
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
l_int|0
suffix:semicolon
macro_line|#if (defined(CONFIG_H8300H_SIM) || defined(CONFIG_H8S_SIM)) &amp;&amp; defined(CONFIG_GDB_MAGICPRINT)
id|register_console
c_func
(paren
(paren
r_struct
id|console
op_star
)paren
op_amp
id|gdb_console
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;&bslash;r&bslash;n&bslash;nuClinux &quot;
id|CPU
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Target Hardware: %s&bslash;n&quot;
comma
id|_target_name
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Flat model support (C) 1998,1999 Kenneth Albanowski, D. Jeff Dionne&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;H8/300 series support by Yoshinori Sato &lt;ysato@users.sourceforge.jp&gt;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;KERNEL -&gt; TEXT=0x%06x-0x%06x DATA=0x%06x-0x%06x &quot;
l_string|&quot;BSS=0x%06x-0x%06x&bslash;n&quot;
comma
(paren
r_int
)paren
op_amp
id|_stext
comma
(paren
r_int
)paren
op_amp
id|_etext
comma
(paren
r_int
)paren
op_amp
id|_sdata
comma
(paren
r_int
)paren
op_amp
id|_edata
comma
(paren
r_int
)paren
op_amp
id|_sbss
comma
(paren
r_int
)paren
op_amp
id|_ebss
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;KERNEL -&gt; ROMFS=0x%06x-0x%06x MEM=0x%06x-0x%06x &quot;
l_string|&quot;STACK=0x%06x-0x%06x&bslash;n&quot;
comma
(paren
r_int
)paren
op_amp
id|_ebss
comma
(paren
r_int
)paren
id|memory_start
comma
(paren
r_int
)paren
id|memory_start
comma
(paren
r_int
)paren
id|memory_end
comma
(paren
r_int
)paren
id|memory_end
comma
(paren
r_int
)paren
op_amp
id|_ramend
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DEFAULT_CMDLINE
multiline_comment|/* set from default command line */
r_if
c_cond
(paren
op_star
id|command_line
op_eq
l_char|&squot;&bslash;0&squot;
)paren
id|strcpy
c_func
(paren
id|command_line
comma
id|CONFIG_KERNEL_COMMAND
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Keep a copy of command line */
op_star
id|cmdline_p
op_assign
op_amp
id|command_line
(braket
l_int|0
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|saved_command_line
comma
id|command_line
comma
r_sizeof
(paren
id|saved_command_line
)paren
)paren
suffix:semicolon
id|saved_command_line
(braket
r_sizeof
(paren
id|saved_command_line
)paren
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef DEBUG
r_if
c_cond
(paren
id|strlen
c_func
(paren
op_star
id|cmdline_p
)paren
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Command line: &squot;%s&squot;&bslash;n&quot;
comma
op_star
id|cmdline_p
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * give all the memory to the bootmap allocator,  tell it to put the&n;&t; * boot mem_map at the start of memory&n;&t; */
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
id|memory_start
op_rshift
id|PAGE_SHIFT
comma
multiline_comment|/* map goes here */
id|PAGE_OFFSET
op_rshift
id|PAGE_SHIFT
comma
multiline_comment|/* 0 on coldfire */
id|memory_end
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * free the usable memory,  we have to make sure we do not free&n;&t; * the bootmem bitmap so we then reserve it after freeing it :-)&n;&t; */
id|free_bootmem
c_func
(paren
id|memory_start
comma
id|memory_end
op_minus
id|memory_start
)paren
suffix:semicolon
id|reserve_bootmem
c_func
(paren
id|memory_start
comma
id|bootmap_size
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * get kmalloc into gear&n;&t; */
id|paging_init
c_func
(paren
)paren
suffix:semicolon
id|h8300_gpio_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_H8300_AKI3068NET) &amp;&amp; defined(CONFIG_IDE)
(brace
DECL|macro|AREABIT
mdefine_line|#define AREABIT(addr) (1 &lt;&lt; (((addr) &gt;&gt; 21) &amp; 7))
multiline_comment|/* setup BSC */
r_volatile
r_int
r_char
op_star
id|abwcr
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
id|ABWCR
suffix:semicolon
r_volatile
r_int
r_char
op_star
id|cscr
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
id|CSCR
suffix:semicolon
op_star
id|abwcr
op_and_assign
op_complement
(paren
id|AREABIT
c_func
(paren
id|CONFIG_H8300_IDE_BASE
)paren
op_or
id|AREABIT
c_func
(paren
id|CONFIG_H8300_IDE_ALT
)paren
)paren
suffix:semicolon
op_star
id|cscr
op_or_assign
(paren
id|AREABIT
c_func
(paren
id|CONFIG_H8300_IDE_BASE
)paren
op_or
id|AREABIT
c_func
(paren
id|CONFIG_H8300_IDE_ALT
)paren
)paren
op_or
l_int|0x0f
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Done setup_arch&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; *&t;Get CPU information for use by the procfs.&n; */
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
r_char
op_star
id|cpu
suffix:semicolon
r_int
id|mode
suffix:semicolon
id|u_long
id|clockfreq
suffix:semicolon
id|cpu
op_assign
id|CPU
suffix:semicolon
id|mode
op_assign
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|MDCR
op_amp
l_int|0x07
suffix:semicolon
id|clockfreq
op_assign
id|CONFIG_CPU_CLOCK
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;CPU:&bslash;t&bslash;t%s (mode:%d)&bslash;n&quot;
l_string|&quot;Clock:&bslash;t&bslash;t%lu.%1luMHz&bslash;n&quot;
l_string|&quot;BogoMips:&bslash;t%lu.%02lu&bslash;n&quot;
l_string|&quot;Calibration:&bslash;t%lu loops&bslash;n&quot;
comma
id|cpu
comma
id|mode
comma
id|clockfreq
op_div
l_int|100
comma
id|clockfreq
op_mod
l_int|100
comma
(paren
id|loops_per_jiffy
op_star
id|HZ
)paren
op_div
l_int|500000
comma
(paren
(paren
id|loops_per_jiffy
op_star
id|HZ
)paren
op_div
l_int|5000
)paren
op_mod
l_int|100
comma
(paren
id|loops_per_jiffy
op_star
id|HZ
)paren
)paren
suffix:semicolon
r_return
l_int|0
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
r_return
op_star
id|pos
OL
id|NR_CPUS
ques
c_cond
(paren
(paren
r_void
op_star
)paren
l_int|0x12345678
)paren
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
id|c_start
c_func
(paren
id|m
comma
id|pos
)paren
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
eof
