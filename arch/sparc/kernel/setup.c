multiline_comment|/*  $Id: setup.c,v 1.126 2001/11/13 00:49:27 davem Exp $&n; *  linux/arch/sparc/kernel/setup.c&n; *&n; *  Copyright (C) 1995  David S. Miller (davem@caip.rutgers.edu)&n; *  Copyright (C) 2000  Anton Blanchard (anton@samba.org)&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/kgdb.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/vaddrs.h&gt;
macro_line|#include &lt;asm/kdebug.h&gt;
macro_line|#include &lt;asm/mbus.h&gt;
macro_line|#include &lt;asm/idprom.h&gt;
macro_line|#include &lt;asm/softirq.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/machines.h&gt;
DECL|variable|screen_info
r_struct
id|screen_info
id|screen_info
op_assign
(brace
l_int|0
comma
l_int|0
comma
multiline_comment|/* orig-x, orig-y */
l_int|0
comma
multiline_comment|/* unused */
l_int|0
comma
multiline_comment|/* orig-video-page */
l_int|0
comma
multiline_comment|/* orig-video-mode */
l_int|128
comma
multiline_comment|/* orig-video-cols */
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ega_ax, ega_bx, ega_cx */
l_int|54
comma
multiline_comment|/* orig-video-lines */
l_int|0
comma
multiline_comment|/* orig-video-isVGA */
l_int|16
multiline_comment|/* orig-video-points */
)brace
suffix:semicolon
multiline_comment|/* Typing sync at the prom prompt calls the function pointed to by&n; * romvec-&gt;pv_synchook which I set to the following function.&n; * This should sync all filesystems and return, for now it just&n; * prints out pretty messages and returns.&n; */
r_extern
r_int
r_int
id|trapbase
suffix:semicolon
r_extern
r_int
id|serial_console
suffix:semicolon
r_extern
r_void
id|breakpoint
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|prom_palette
r_void
(paren
op_star
id|prom_palette
)paren
(paren
r_int
)paren
suffix:semicolon
id|asmlinkage
r_void
id|sys_sync
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* it&squot;s really int */
multiline_comment|/* Pretty sick eh? */
DECL|function|prom_sync_me
r_void
id|prom_sync_me
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|prom_tbr
comma
id|flags
suffix:semicolon
multiline_comment|/* XXX Badly broken. FIX! - Anton */
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rd %%tbr, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|prom_tbr
)paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;wr %0, 0x0, %%tbr&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|trapbase
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prom_palette
)paren
id|prom_palette
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;PROM SYNC COMMAND...&bslash;n&quot;
)paren
suffix:semicolon
id|show_free_areas
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;pid
op_ne
l_int|0
)paren
(brace
id|sti
c_func
(paren
)paren
suffix:semicolon
id|sys_sync
c_func
(paren
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
)brace
id|prom_printf
c_func
(paren
l_string|&quot;Returning to prom&bslash;n&quot;
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;wr %0, 0x0, %%tbr&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|prom_tbr
)paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_extern
r_void
id|rs_kgdb_hook
c_func
(paren
r_int
id|tty_num
)paren
suffix:semicolon
multiline_comment|/* sparc/serial.c */
DECL|variable|__initdata
r_int
r_int
id|boot_flags
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|macro|BOOTME_DEBUG
mdefine_line|#define BOOTME_DEBUG  0x1
DECL|macro|BOOTME_SINGLE
mdefine_line|#define BOOTME_SINGLE 0x2
DECL|macro|BOOTME_KGDBA
mdefine_line|#define BOOTME_KGDBA  0x4
DECL|macro|BOOTME_KGDBB
mdefine_line|#define BOOTME_KGDBB  0x8
DECL|macro|BOOTME_KGDB
mdefine_line|#define BOOTME_KGDB   0xc
DECL|variable|__initdata
r_static
r_int
id|console_fb
id|__initdata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Exported for mm/init.c:paging_init. */
DECL|variable|__initdata
r_int
r_int
id|cmdline_memory_size
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|function|kernel_enter_debugger
r_void
id|kernel_enter_debugger
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|boot_flags
op_amp
id|BOOTME_KGDB
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;KGDB: Entered&bslash;n&quot;
)paren
suffix:semicolon
id|breakpoint
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|prom_console_write
id|prom_console_write
c_func
(paren
r_struct
id|console
op_star
id|con
comma
r_const
r_char
op_star
id|s
comma
r_int
id|n
)paren
(brace
id|prom_write
c_func
(paren
id|s
comma
id|n
)paren
suffix:semicolon
)brace
DECL|variable|prom_debug_console
r_static
r_struct
id|console
id|prom_debug_console
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;debug&quot;
comma
dot
id|write
op_assign
id|prom_console_write
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
DECL|function|obp_system_intr
r_int
id|obp_system_intr
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|boot_flags
op_amp
id|BOOTME_KGDB
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;KGDB: system interrupted&bslash;n&quot;
)paren
suffix:semicolon
id|breakpoint
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|boot_flags
op_amp
id|BOOTME_DEBUG
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;OBP: system interrupted&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; * Process kernel command line switches that are specific to the&n; * SPARC or that require special low-level processing.&n; */
DECL|function|process_switch
r_static
r_void
id|__init
id|process_switch
c_func
(paren
r_char
id|c
)paren
(brace
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_char|&squot;d&squot;
suffix:colon
id|boot_flags
op_or_assign
id|BOOTME_DEBUG
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
id|boot_flags
op_or_assign
id|BOOTME_SINGLE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;h&squot;
suffix:colon
id|prom_printf
c_func
(paren
l_string|&quot;boot_flags_init: Halt!&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;p&squot;
suffix:colon
multiline_comment|/* Use PROM debug console. */
id|register_console
c_func
(paren
op_amp
id|prom_debug_console
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Unknown boot switch (-%c)&bslash;n&quot;
comma
id|c
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|boot_flags_init
r_static
r_void
id|__init
id|boot_flags_init
c_func
(paren
r_char
op_star
id|commands
)paren
(brace
r_while
c_loop
(paren
op_star
id|commands
)paren
(brace
multiline_comment|/* Move to the start of the next &quot;argument&quot;. */
r_while
c_loop
(paren
op_star
id|commands
op_logical_and
op_star
id|commands
op_eq
l_char|&squot; &squot;
)paren
id|commands
op_increment
suffix:semicolon
multiline_comment|/* Process any command switches, otherwise skip it. */
r_if
c_cond
(paren
op_star
id|commands
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_break
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|commands
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|commands
op_increment
suffix:semicolon
r_while
c_loop
(paren
op_star
id|commands
op_logical_and
op_star
id|commands
op_ne
l_char|&squot; &squot;
)paren
id|process_switch
c_func
(paren
op_star
id|commands
op_increment
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|commands
)paren
op_ge
l_int|9
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|commands
comma
l_string|&quot;kgdb=tty&quot;
comma
l_int|8
)paren
)paren
(brace
r_switch
c_cond
(paren
id|commands
(braket
l_int|8
)braket
)paren
(brace
macro_line|#ifdef CONFIG_SUN_SERIAL
r_case
l_char|&squot;a&squot;
suffix:colon
id|boot_flags
op_or_assign
id|BOOTME_KGDBA
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;KGDB: Using serial line /dev/ttya.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;b&squot;
suffix:colon
id|boot_flags
op_or_assign
id|BOOTME_KGDBB
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;KGDB: Using serial line /dev/ttyb.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;KGDB: Unknown tty line.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|commands
op_add_assign
l_int|9
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|commands
comma
l_string|&quot;console=&quot;
comma
l_int|8
)paren
)paren
(brace
id|commands
op_add_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
(paren
id|commands
comma
l_string|&quot;ttya&quot;
comma
l_int|4
)paren
)paren
(brace
id|console_fb
op_assign
l_int|2
suffix:semicolon
id|prom_printf
(paren
l_string|&quot;Using /dev/ttya as console.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
(paren
id|commands
comma
l_string|&quot;ttyb&quot;
comma
l_int|4
)paren
)paren
(brace
id|console_fb
op_assign
l_int|3
suffix:semicolon
id|prom_printf
(paren
l_string|&quot;Using /dev/ttyb as console.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_PROM_CONSOLE)
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
(paren
id|commands
comma
l_string|&quot;prom&quot;
comma
l_int|4
)paren
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|commands
op_minus
l_int|8
suffix:semicolon
op_star
id|p
op_logical_and
op_star
id|p
op_ne
l_char|&squot; &squot;
suffix:semicolon
id|p
op_increment
)paren
op_star
id|p
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|conswitchp
op_assign
op_amp
id|prom_con
suffix:semicolon
id|console_fb
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
id|console_fb
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|commands
comma
l_string|&quot;mem=&quot;
comma
l_int|4
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * &quot;mem=XXX[kKmM] overrides the PROM-reported&n;&t;&t;&t;&t; * memory size.&n;&t;&t;&t;&t; */
id|cmdline_memory_size
op_assign
id|simple_strtoul
c_func
(paren
id|commands
op_plus
l_int|4
comma
op_amp
id|commands
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|commands
op_eq
l_char|&squot;K&squot;
op_logical_or
op_star
id|commands
op_eq
l_char|&squot;k&squot;
)paren
(brace
id|cmdline_memory_size
op_lshift_assign
l_int|10
suffix:semicolon
id|commands
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|commands
op_eq
l_char|&squot;M&squot;
op_logical_or
op_star
id|commands
op_eq
l_char|&squot;m&squot;
)paren
(brace
id|cmdline_memory_size
op_lshift_assign
l_int|20
suffix:semicolon
id|commands
op_increment
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_star
id|commands
op_logical_and
op_star
id|commands
op_ne
l_char|&squot; &squot;
)paren
id|commands
op_increment
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* This routine will in the future do all the nasty prom stuff&n; * to probe for the mmu type and its parameters, etc. This will&n; * also be where SMP things happen plus the Sparc specific memory&n; * physical memory probe as on the alpha.&n; */
r_extern
r_int
id|prom_probe_memory
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sun4c_probe_vac
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_char
id|cputypval
suffix:semicolon
r_extern
r_int
r_int
id|start
comma
id|end
suffix:semicolon
r_extern
r_void
id|panic_setup
c_func
(paren
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|srmmu_end_memory
c_func
(paren
r_int
r_int
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sun_serial_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|root_flags
suffix:semicolon
r_extern
r_int
r_int
id|root_dev
suffix:semicolon
r_extern
r_int
r_int
id|ram_flags
suffix:semicolon
DECL|macro|RAMDISK_IMAGE_START_MASK
mdefine_line|#define RAMDISK_IMAGE_START_MASK&t;0x07FF
DECL|macro|RAMDISK_PROMPT_FLAG
mdefine_line|#define RAMDISK_PROMPT_FLAG&t;&t;0x8000
DECL|macro|RAMDISK_LOAD_FLAG
mdefine_line|#define RAMDISK_LOAD_FLAG&t;&t;0x4000
r_extern
r_int
id|root_mountflags
suffix:semicolon
DECL|variable|saved_command_line
r_char
id|saved_command_line
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|reboot_command
r_char
id|reboot_command
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|sparc_cpu_model
r_enum
id|sparc_cpu
id|sparc_cpu_model
suffix:semicolon
DECL|variable|sparc_ttable
r_struct
id|tt_entry
op_star
id|sparc_ttable
suffix:semicolon
DECL|variable|fake_swapper_regs
r_struct
id|pt_regs
id|fake_swapper_regs
suffix:semicolon
r_extern
r_void
id|paging_init
c_func
(paren
r_void
)paren
suffix:semicolon
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
id|i
suffix:semicolon
r_int
r_int
id|highest_paddr
suffix:semicolon
id|sparc_ttable
op_assign
(paren
r_struct
id|tt_entry
op_star
)paren
op_amp
id|start
suffix:semicolon
multiline_comment|/* Initialize PROM console and command line. */
op_star
id|cmdline_p
op_assign
id|prom_getbootargs
c_func
(paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|saved_command_line
comma
op_star
id|cmdline_p
)paren
suffix:semicolon
multiline_comment|/* Set sparc_cpu_model */
id|sparc_cpu_model
op_assign
id|sun_unknown
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
op_amp
id|cputypval
comma
l_string|&quot;sun4 &quot;
)paren
)paren
(brace
id|sparc_cpu_model
op_assign
id|sun4
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
op_amp
id|cputypval
comma
l_string|&quot;sun4c&quot;
)paren
)paren
(brace
id|sparc_cpu_model
op_assign
id|sun4c
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
op_amp
id|cputypval
comma
l_string|&quot;sun4m&quot;
)paren
)paren
(brace
id|sparc_cpu_model
op_assign
id|sun4m
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
op_amp
id|cputypval
comma
l_string|&quot;sun4s&quot;
)paren
)paren
(brace
id|sparc_cpu_model
op_assign
id|sun4m
suffix:semicolon
)brace
multiline_comment|/* CP-1200 with PROM 2.30 -E */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
op_amp
id|cputypval
comma
l_string|&quot;sun4d&quot;
)paren
)paren
(brace
id|sparc_cpu_model
op_assign
id|sun4d
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
op_amp
id|cputypval
comma
l_string|&quot;sun4e&quot;
)paren
)paren
(brace
id|sparc_cpu_model
op_assign
id|sun4e
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
op_amp
id|cputypval
comma
l_string|&quot;sun4u&quot;
)paren
)paren
(brace
id|sparc_cpu_model
op_assign
id|sun4u
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SUN4
r_if
c_cond
(paren
id|sparc_cpu_model
op_ne
id|sun4
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;This kernel is for Sun4 architecture only.&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;ARCH: &quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|sparc_cpu_model
)paren
(brace
r_case
id|sun4
suffix:colon
id|printk
c_func
(paren
l_string|&quot;SUN4&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sun4c
suffix:colon
id|printk
c_func
(paren
l_string|&quot;SUN4C&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sun4m
suffix:colon
id|printk
c_func
(paren
l_string|&quot;SUN4M&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sun4d
suffix:colon
id|printk
c_func
(paren
l_string|&quot;SUN4D&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sun4e
suffix:colon
id|printk
c_func
(paren
l_string|&quot;SUN4E&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sun4u
suffix:colon
id|printk
c_func
(paren
l_string|&quot;SUN4U&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;UNKNOWN!&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_DUMMY_CONSOLE
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#elif defined(CONFIG_PROM_CONSOLE)
id|conswitchp
op_assign
op_amp
id|prom_con
suffix:semicolon
macro_line|#endif
id|boot_flags_init
c_func
(paren
op_star
id|cmdline_p
)paren
suffix:semicolon
id|idprom_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ARCH_SUN4C_SUN4
)paren
id|sun4c_probe_vac
c_func
(paren
)paren
suffix:semicolon
id|load_mmu
c_func
(paren
)paren
suffix:semicolon
(paren
r_void
)paren
id|prom_probe_memory
c_func
(paren
)paren
suffix:semicolon
id|phys_base
op_assign
l_int|0xffffffffUL
suffix:semicolon
id|highest_paddr
op_assign
l_int|0UL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|top
suffix:semicolon
r_if
c_cond
(paren
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
OL
id|phys_base
)paren
id|phys_base
op_assign
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
suffix:semicolon
id|top
op_assign
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
op_plus
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
suffix:semicolon
r_if
c_cond
(paren
id|highest_paddr
OL
id|top
)paren
id|highest_paddr
op_assign
id|top
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|root_flags
)paren
id|root_mountflags
op_and_assign
op_complement
id|MS_RDONLY
suffix:semicolon
id|ROOT_DEV
op_assign
id|root_dev
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
id|rd_image_start
op_assign
id|ram_flags
op_amp
id|RAMDISK_IMAGE_START_MASK
suffix:semicolon
id|rd_prompt
op_assign
(paren
(paren
id|ram_flags
op_amp
id|RAMDISK_PROMPT_FLAG
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|rd_doload
op_assign
(paren
(paren
id|ram_flags
op_amp
id|RAMDISK_LOAD_FLAG
)paren
op_ne
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|prom_setsync
c_func
(paren
id|prom_sync_me
)paren
suffix:semicolon
(brace
macro_line|#if !CONFIG_SUN_SERIAL
id|serial_console
op_assign
l_int|0
suffix:semicolon
macro_line|#else
r_switch
c_cond
(paren
id|console_fb
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* Let get our io devices from prom */
(brace
r_int
id|idev
op_assign
id|prom_query_input_device
c_func
(paren
)paren
suffix:semicolon
r_int
id|odev
op_assign
id|prom_query_output_device
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idev
op_eq
id|PROMDEV_IKBD
op_logical_and
id|odev
op_eq
id|PROMDEV_OSCREEN
)paren
(brace
id|serial_console
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|idev
op_eq
id|PROMDEV_ITTYA
op_logical_and
id|odev
op_eq
id|PROMDEV_OTTYA
)paren
(brace
id|serial_console
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|idev
op_eq
id|PROMDEV_ITTYB
op_logical_and
id|odev
op_eq
id|PROMDEV_OTTYB
)paren
(brace
id|serial_console
op_assign
l_int|2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|idev
op_eq
id|PROMDEV_I_UNK
op_logical_and
id|odev
op_eq
id|PROMDEV_OTTYA
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;MrCoffee ttya&bslash;n&quot;
)paren
suffix:semicolon
id|serial_console
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|idev
op_eq
id|PROMDEV_I_UNK
op_logical_and
id|odev
op_eq
id|PROMDEV_OSCREEN
)paren
(brace
id|serial_console
op_assign
l_int|0
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;MrCoffee keyboard&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Inconsistent or unknown console&bslash;n&quot;
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;You cannot mix serial and non serial input/output devices&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|serial_console
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Force one of the framebuffers as console */
r_case
l_int|2
suffix:colon
id|serial_console
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Force ttya as console */
r_case
l_int|3
suffix:colon
id|serial_console
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Force ttyb as console */
)brace
macro_line|#endif
)brace
r_if
c_cond
(paren
(paren
id|boot_flags
op_amp
id|BOOTME_KGDBA
)paren
)paren
(brace
id|rs_kgdb_hook
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|boot_flags
op_amp
id|BOOTME_KGDBB
)paren
)paren
(brace
id|rs_kgdb_hook
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|boot_flags
op_amp
id|BOOTME_DEBUG
)paren
op_logical_and
(paren
id|linux_dbvec
op_ne
l_int|0
)paren
op_logical_and
(paren
(paren
op_star
(paren
r_int
op_star
)paren
id|linux_dbvec
)paren
op_ne
op_minus
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Booted under KADB. Syncing trap table.&bslash;n&quot;
)paren
suffix:semicolon
(paren
op_star
(paren
id|linux_dbvec-&gt;teach_debugger
)paren
)paren
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|boot_flags
op_amp
id|BOOTME_KGDB
)paren
)paren
(brace
id|set_debug_traps
c_func
(paren
)paren
suffix:semicolon
id|prom_printf
(paren
l_string|&quot;Breakpoint!&bslash;n&quot;
)paren
suffix:semicolon
id|breakpoint
c_func
(paren
)paren
suffix:semicolon
)brace
id|init_mm.context
op_assign
(paren
r_int
r_int
)paren
id|NO_CONTEXT
suffix:semicolon
id|init_task.thread.kregs
op_assign
op_amp
id|fake_swapper_regs
suffix:semicolon
r_if
c_cond
(paren
id|serial_console
)paren
id|conswitchp
op_assign
l_int|NULL
suffix:semicolon
id|paging_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sys_ioperm
id|asmlinkage
r_int
id|sys_ioperm
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|num
comma
r_int
id|on
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_extern
r_char
op_star
id|sparc_cpu_type
(braket
)braket
suffix:semicolon
r_extern
r_char
op_star
id|sparc_fpu_type
(braket
)braket
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
id|__unused
)paren
(brace
r_int
id|cpuid
op_assign
id|hard_smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;cpu&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;fpu&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;promlib&bslash;t&bslash;t: Version %d Revision %d&bslash;n&quot;
l_string|&quot;prom&bslash;t&bslash;t: %d.%d&bslash;n&quot;
l_string|&quot;type&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;ncpus probed&bslash;t: %d&bslash;n&quot;
l_string|&quot;ncpus active&bslash;t: %d&bslash;n&quot;
macro_line|#ifndef CONFIG_SMP
l_string|&quot;BogoMips&bslash;t: %lu.%02lu&bslash;n&quot;
macro_line|#endif
comma
id|sparc_cpu_type
(braket
id|cpuid
)braket
ques
c_cond
suffix:colon
l_string|&quot;undetermined&quot;
comma
id|sparc_fpu_type
(braket
id|cpuid
)braket
ques
c_cond
suffix:colon
l_string|&quot;undetermined&quot;
comma
id|romvec-&gt;pv_romvers
comma
id|prom_rev
comma
id|romvec-&gt;pv_printrev
op_rshift
l_int|16
comma
(paren
r_int
)paren
id|romvec-&gt;pv_printrev
comma
op_amp
id|cputypval
comma
id|linux_num_cpus
comma
id|num_online_cpus
c_func
(paren
)paren
macro_line|#ifndef CONFIG_SMP
comma
id|loops_per_jiffy
op_div
(paren
l_int|500000
op_div
id|HZ
)paren
comma
(paren
id|loops_per_jiffy
op_div
(paren
l_int|5000
op_div
id|HZ
)paren
)paren
op_mod
l_int|100
macro_line|#endif
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|smp_bogo_info
c_func
(paren
id|m
)paren
suffix:semicolon
macro_line|#endif
id|mmu_info
c_func
(paren
id|m
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|smp_info
c_func
(paren
id|m
)paren
suffix:semicolon
macro_line|#endif
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
multiline_comment|/* The pointer we are returning is arbitrary,&n;&t; * it just has to be non-NULL and not IS_ERR&n;&t; * in the success case.&n;&t; */
r_return
op_star
id|pos
op_eq
l_int|0
ques
c_cond
op_amp
id|c_start
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
