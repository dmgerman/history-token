multiline_comment|/*&n; *  linux/arch/m68k/kernel/setup.c&n; *&n; *  Copyright (C) 1995  Hamish Macdonald&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of system setup&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#ifdef CONFIG_AMIGA
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_ATARI
macro_line|#include &lt;asm/atarihw.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_SUN3X
macro_line|#include &lt;asm/dvma.h&gt;
r_extern
r_void
id|sun_serial_setup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#endif
DECL|variable|m68k_machtype
r_int
r_int
id|m68k_machtype
suffix:semicolon
DECL|variable|m68k_cputype
r_int
r_int
id|m68k_cputype
suffix:semicolon
DECL|variable|m68k_fputype
r_int
r_int
id|m68k_fputype
suffix:semicolon
DECL|variable|m68k_mmutype
r_int
r_int
id|m68k_mmutype
suffix:semicolon
macro_line|#ifdef CONFIG_VME
DECL|variable|vme_brdtype
r_int
r_int
id|vme_brdtype
suffix:semicolon
macro_line|#endif
DECL|variable|m68k_is040or060
r_int
id|m68k_is040or060
op_assign
l_int|0
suffix:semicolon
r_extern
r_int
id|end
suffix:semicolon
r_extern
r_int
r_int
id|availmem
suffix:semicolon
DECL|variable|m68k_num_memory
r_int
id|m68k_num_memory
op_assign
l_int|0
suffix:semicolon
DECL|variable|m68k_realnum_memory
r_int
id|m68k_realnum_memory
op_assign
l_int|0
suffix:semicolon
DECL|variable|m68k_memoffset
r_int
r_int
id|m68k_memoffset
suffix:semicolon
DECL|variable|m68k_memory
r_struct
id|mem_info
id|m68k_memory
(braket
id|NUM_MEMINFO
)braket
suffix:semicolon
DECL|variable|m68k_ramdisk
r_static
r_struct
id|mem_info
id|m68k_ramdisk
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|m68k_command_line
r_static
r_char
id|m68k_command_line
(braket
id|CL_SIZE
)braket
suffix:semicolon
DECL|variable|saved_command_line
r_char
id|saved_command_line
(braket
id|CL_SIZE
)braket
suffix:semicolon
DECL|variable|m68k_debug_device
r_char
id|m68k_debug_device
(braket
l_int|6
)braket
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_void
(paren
op_star
id|mach_sched_init
)paren
(paren
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
)paren
id|__initdata
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* machine dependent keyboard functions */
r_int
(paren
op_star
id|mach_keyb_init
)paren
(paren
r_void
)paren
id|__initdata
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_kbdrate
r_int
(paren
op_star
id|mach_kbdrate
)paren
(paren
r_struct
id|kbd_repeat
op_star
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_kbd_leds
r_void
(paren
op_star
id|mach_kbd_leds
)paren
(paren
r_int
r_int
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_kbd_translate
r_int
(paren
op_star
id|mach_kbd_translate
)paren
(paren
r_int
r_char
id|scancode
comma
r_int
r_char
op_star
id|keycode
comma
r_char
id|raw_mode
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|SYSRQ_KEY
r_int
r_int
id|SYSRQ_KEY
suffix:semicolon
multiline_comment|/* machine dependent irq functions */
r_void
(paren
op_star
id|mach_init_IRQ
)paren
(paren
r_void
)paren
id|__initdata
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_default_handler
r_void
(paren
op_star
(paren
op_star
id|mach_default_handler
)paren
(braket
)braket
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_get_model
r_void
(paren
op_star
id|mach_get_model
)paren
(paren
r_char
op_star
id|model
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_get_hardware_list
r_int
(paren
op_star
id|mach_get_hardware_list
)paren
(paren
r_char
op_star
id|buffer
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_get_irq_list
r_int
(paren
op_star
id|mach_get_irq_list
)paren
(paren
r_struct
id|seq_file
op_star
comma
r_void
op_star
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_process_int
r_void
(paren
op_star
id|mach_process_int
)paren
(paren
r_int
comma
r_struct
id|pt_regs
op_star
)paren
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* machine dependent timer functions */
DECL|variable|mach_gettimeoffset
r_int
r_int
(paren
op_star
id|mach_gettimeoffset
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|mach_hwclk
r_int
(paren
op_star
id|mach_hwclk
)paren
(paren
r_int
comma
r_struct
id|rtc_time
op_star
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_set_clock_mmss
r_int
(paren
op_star
id|mach_set_clock_mmss
)paren
(paren
r_int
r_int
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_reset
r_void
(paren
op_star
id|mach_reset
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|mach_halt
r_void
(paren
op_star
id|mach_halt
)paren
(paren
r_void
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_power_off
r_void
(paren
op_star
id|mach_power_off
)paren
(paren
r_void
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_max_dma_address
r_int
id|mach_max_dma_address
op_assign
l_int|0x00ffffff
suffix:semicolon
multiline_comment|/* default set to the lower 16MB */
macro_line|#if defined(CONFIG_AMIGA_FLOPPY) || defined(CONFIG_ATARI_FLOPPY) 
r_void
(paren
op_star
id|mach_floppy_setup
)paren
(paren
r_char
op_star
comma
r_int
op_star
)paren
id|__initdata
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_HEARTBEAT
DECL|variable|mach_heartbeat
r_void
(paren
op_star
id|mach_heartbeat
)paren
(paren
r_int
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_heartbeat
id|EXPORT_SYMBOL
c_func
(paren
id|mach_heartbeat
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_M68K_L2_CACHE
DECL|variable|mach_l2_flush
r_void
(paren
op_star
id|mach_l2_flush
)paren
(paren
r_int
)paren
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
DECL|variable|mach_sysrq_key
r_int
id|mach_sysrq_key
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|mach_sysrq_shift_state
r_int
id|mach_sysrq_shift_state
op_assign
l_int|0
suffix:semicolon
DECL|variable|mach_sysrq_shift_mask
r_int
id|mach_sysrq_shift_mask
op_assign
l_int|0
suffix:semicolon
DECL|variable|mach_sysrq_xlate
r_char
op_star
id|mach_sysrq_xlate
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_ISA) &amp;&amp; defined(MULTI_ISA)
DECL|variable|isa_type
r_int
id|isa_type
suffix:semicolon
DECL|variable|isa_sex
r_int
id|isa_sex
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|amiga_parse_bootinfo
c_func
(paren
r_const
r_struct
id|bi_record
op_star
)paren
suffix:semicolon
r_extern
r_int
id|atari_parse_bootinfo
c_func
(paren
r_const
r_struct
id|bi_record
op_star
)paren
suffix:semicolon
r_extern
r_int
id|mac_parse_bootinfo
c_func
(paren
r_const
r_struct
id|bi_record
op_star
)paren
suffix:semicolon
r_extern
r_int
id|q40_parse_bootinfo
c_func
(paren
r_const
r_struct
id|bi_record
op_star
)paren
suffix:semicolon
r_extern
r_int
id|bvme6000_parse_bootinfo
c_func
(paren
r_const
r_struct
id|bi_record
op_star
)paren
suffix:semicolon
r_extern
r_int
id|mvme16x_parse_bootinfo
c_func
(paren
r_const
r_struct
id|bi_record
op_star
)paren
suffix:semicolon
r_extern
r_int
id|mvme147_parse_bootinfo
c_func
(paren
r_const
r_struct
id|bi_record
op_star
)paren
suffix:semicolon
r_extern
r_void
id|config_amiga
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|config_atari
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|config_mac
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|config_sun3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|config_apollo
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|config_mvme147
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|config_mvme16x
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|config_bvme6000
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|config_hp300
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|config_q40
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|config_sun3x
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mac_debugging_short
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|mac_debugging_long
(paren
r_int
comma
r_int
)paren
suffix:semicolon
DECL|macro|MASK_256K
mdefine_line|#define MASK_256K 0xfffc0000
r_extern
r_void
id|paging_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|m68k_parse_bootinfo
r_static
r_void
id|__init
id|m68k_parse_bootinfo
c_func
(paren
r_const
r_struct
id|bi_record
op_star
id|record
)paren
(brace
r_while
c_loop
(paren
id|record-&gt;tag
op_ne
id|BI_LAST
)paren
(brace
r_int
id|unknown
op_assign
l_int|0
suffix:semicolon
r_const
r_int
r_int
op_star
id|data
op_assign
id|record-&gt;data
suffix:semicolon
r_switch
c_cond
(paren
id|record-&gt;tag
)paren
(brace
r_case
id|BI_MACHTYPE
suffix:colon
r_case
id|BI_CPUTYPE
suffix:colon
r_case
id|BI_FPUTYPE
suffix:colon
r_case
id|BI_MMUTYPE
suffix:colon
multiline_comment|/* Already set up by head.S */
r_break
suffix:semicolon
r_case
id|BI_MEMCHUNK
suffix:colon
r_if
c_cond
(paren
id|m68k_num_memory
OL
id|NUM_MEMINFO
)paren
(brace
id|m68k_memory
(braket
id|m68k_num_memory
)braket
dot
id|addr
op_assign
id|data
(braket
l_int|0
)braket
suffix:semicolon
id|m68k_memory
(braket
id|m68k_num_memory
)braket
dot
id|size
op_assign
id|data
(braket
l_int|1
)braket
suffix:semicolon
id|m68k_num_memory
op_increment
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;m68k_parse_bootinfo: too many memory chunks&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_RAMDISK
suffix:colon
id|m68k_ramdisk.addr
op_assign
id|data
(braket
l_int|0
)braket
suffix:semicolon
id|m68k_ramdisk.size
op_assign
id|data
(braket
l_int|1
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_COMMAND_LINE
suffix:colon
id|strncpy
c_func
(paren
id|m68k_command_line
comma
(paren
r_const
r_char
op_star
)paren
id|data
comma
id|CL_SIZE
)paren
suffix:semicolon
id|m68k_command_line
(braket
id|CL_SIZE
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|MACH_IS_AMIGA
)paren
id|unknown
op_assign
id|amiga_parse_bootinfo
c_func
(paren
id|record
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|MACH_IS_ATARI
)paren
id|unknown
op_assign
id|atari_parse_bootinfo
c_func
(paren
id|record
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|MACH_IS_MAC
)paren
id|unknown
op_assign
id|mac_parse_bootinfo
c_func
(paren
id|record
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|MACH_IS_Q40
)paren
id|unknown
op_assign
id|q40_parse_bootinfo
c_func
(paren
id|record
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|MACH_IS_BVME6000
)paren
id|unknown
op_assign
id|bvme6000_parse_bootinfo
c_func
(paren
id|record
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|MACH_IS_MVME16x
)paren
id|unknown
op_assign
id|mvme16x_parse_bootinfo
c_func
(paren
id|record
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|MACH_IS_MVME147
)paren
id|unknown
op_assign
id|mvme147_parse_bootinfo
c_func
(paren
id|record
)paren
suffix:semicolon
r_else
id|unknown
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|unknown
)paren
id|printk
c_func
(paren
l_string|&quot;m68k_parse_bootinfo: unknown tag 0x%04x ignored&bslash;n&quot;
comma
id|record-&gt;tag
)paren
suffix:semicolon
id|record
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|record
op_plus
id|record-&gt;size
)paren
suffix:semicolon
)brace
id|m68k_realnum_memory
op_assign
id|m68k_num_memory
suffix:semicolon
macro_line|#ifdef CONFIG_SINGLE_MEMORY_CHUNK
r_if
c_cond
(paren
id|m68k_num_memory
OG
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Ignoring last %i chunks of physical memory&bslash;n&quot;
comma
(paren
id|m68k_num_memory
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|m68k_num_memory
op_assign
l_int|1
suffix:semicolon
)brace
id|m68k_memoffset
op_assign
id|m68k_memory
(braket
l_int|0
)braket
dot
id|addr
op_minus
id|PAGE_OFFSET
suffix:semicolon
macro_line|#endif
)brace
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
r_extern
r_int
id|_etext
comma
id|_edata
comma
id|_end
suffix:semicolon
macro_line|#ifndef CONFIG_SUN3
r_int
r_int
id|endmem
comma
id|startmem
suffix:semicolon
macro_line|#endif
r_int
id|i
suffix:semicolon
r_char
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_HP300
)paren
(brace
multiline_comment|/* The bootinfo is located right after the kernel bss */
id|m68k_parse_bootinfo
c_func
(paren
(paren
r_const
r_struct
id|bi_record
op_star
)paren
op_amp
id|_end
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* FIXME HP300 doesn&squot;t use bootinfo yet */
r_extern
r_int
r_int
id|hp300_phys_ram_base
suffix:semicolon
r_int
r_int
id|hp300_mem_size
op_assign
l_int|0xffffffff
op_minus
id|hp300_phys_ram_base
suffix:semicolon
id|m68k_cputype
op_assign
id|CPU_68030
suffix:semicolon
id|m68k_fputype
op_assign
id|FPU_68882
suffix:semicolon
id|m68k_memory
(braket
l_int|0
)braket
dot
id|addr
op_assign
id|hp300_phys_ram_base
suffix:semicolon
multiline_comment|/* 0.5M fudge factor */
id|m68k_memory
(braket
l_int|0
)braket
dot
id|size
op_assign
id|hp300_mem_size
op_minus
l_int|512
op_star
l_int|1024
suffix:semicolon
id|m68k_num_memory
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|CPU_IS_040
)paren
id|m68k_is040or060
op_assign
l_int|4
suffix:semicolon
r_else
r_if
c_cond
(paren
id|CPU_IS_060
)paren
id|m68k_is040or060
op_assign
l_int|6
suffix:semicolon
multiline_comment|/* FIXME: m68k_fputype is passed in by Penguin booter, which can&n;&t; * be confused by software FPU emulation. BEWARE.&n;&t; * We should really do our own FPU check at startup.&n;&t; * [what do we do with buggy 68LC040s? if we have problems&n;&t; *  with them, we should add a test to check_bugs() below] */
macro_line|#ifndef CONFIG_M68KFPU_EMU_ONLY
multiline_comment|/* clear the fpu if we have one */
r_if
c_cond
(paren
id|m68k_fputype
op_amp
(paren
id|FPU_68881
op_or
id|FPU_68882
op_or
id|FPU_68040
op_or
id|FPU_68060
)paren
)paren
(brace
r_volatile
r_int
id|zero
op_assign
l_int|0
suffix:semicolon
id|asm
id|__volatile__
(paren
l_string|&quot;frestore %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|zero
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif&t;
id|init_mm.start_code
op_assign
id|PAGE_OFFSET
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
op_star
id|cmdline_p
op_assign
id|m68k_command_line
suffix:semicolon
id|memcpy
c_func
(paren
id|saved_command_line
comma
op_star
id|cmdline_p
comma
id|CL_SIZE
)paren
suffix:semicolon
multiline_comment|/* Parse the command line for arch-specific options.&n;&t; * For the m68k, this is currently only &quot;debug=xxx&quot; to enable printing&n;&t; * certain kernel messages to some machine-specific device.&n;&t; */
r_for
c_loop
(paren
id|p
op_assign
op_star
id|cmdline_p
suffix:semicolon
id|p
op_logical_and
op_star
id|p
suffix:semicolon
)paren
(brace
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|p
comma
l_string|&quot;debug=&quot;
comma
l_int|6
)paren
)paren
(brace
id|strncpy
c_func
(paren
id|m68k_debug_device
comma
id|p
op_plus
l_int|6
comma
r_sizeof
(paren
id|m68k_debug_device
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|m68k_debug_device
(braket
r_sizeof
(paren
id|m68k_debug_device
)paren
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|q
op_assign
id|strchr
c_func
(paren
id|m68k_debug_device
comma
l_char|&squot; &squot;
)paren
)paren
)paren
op_star
id|q
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ATARI
multiline_comment|/* This option must be parsed very early */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|p
comma
l_string|&quot;switches=&quot;
comma
l_int|9
)paren
)paren
(brace
r_extern
r_void
id|atari_switches_setup
c_func
(paren
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
id|atari_switches_setup
c_func
(paren
id|p
op_plus
l_int|9
comma
(paren
id|q
op_assign
id|strchr
c_func
(paren
id|p
op_plus
l_int|9
comma
l_char|&squot; &squot;
)paren
)paren
ques
c_cond
(paren
id|q
op_minus
(paren
id|p
op_plus
l_int|9
)paren
)paren
suffix:colon
id|strlen
c_func
(paren
id|p
op_plus
l_int|9
)paren
)paren
suffix:semicolon
id|i
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|i
)paren
(brace
multiline_comment|/* option processed, delete it */
r_if
c_cond
(paren
(paren
id|q
op_assign
id|strchr
c_func
(paren
id|p
comma
l_char|&squot; &squot;
)paren
)paren
)paren
id|strcpy
c_func
(paren
id|p
comma
id|q
op_plus
l_int|1
)paren
suffix:semicolon
r_else
op_star
id|p
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|p
op_assign
id|strchr
c_func
(paren
id|p
comma
l_char|&squot; &squot;
)paren
)paren
)paren
op_increment
id|p
suffix:semicolon
)brace
)brace
r_switch
c_cond
(paren
id|m68k_machtype
)paren
(brace
macro_line|#ifdef CONFIG_AMIGA
r_case
id|MACH_AMIGA
suffix:colon
id|config_amiga
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATARI
r_case
id|MACH_ATARI
suffix:colon
id|config_atari
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MAC
r_case
id|MACH_MAC
suffix:colon
id|config_mac
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SUN3
r_case
id|MACH_SUN3
suffix:colon
id|config_sun3
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_APOLLO
r_case
id|MACH_APOLLO
suffix:colon
id|config_apollo
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MVME147
r_case
id|MACH_MVME147
suffix:colon
id|config_mvme147
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MVME16x
r_case
id|MACH_MVME16x
suffix:colon
id|config_mvme16x
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BVME6000
r_case
id|MACH_BVME6000
suffix:colon
id|config_bvme6000
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_HP300
r_case
id|MACH_HP300
suffix:colon
id|config_hp300
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_Q40
r_case
id|MACH_Q40
suffix:colon
id|config_q40
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SUN3X
r_case
id|MACH_SUN3X
suffix:colon
id|config_sun3x
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|panic
(paren
l_string|&quot;No configuration setup&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_SUN3
id|startmem
op_assign
id|m68k_memory
(braket
l_int|0
)braket
dot
id|addr
suffix:semicolon
id|endmem
op_assign
id|startmem
op_plus
id|m68k_memory
(braket
l_int|0
)braket
dot
id|size
suffix:semicolon
id|high_memory
op_assign
id|PAGE_OFFSET
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|m68k_num_memory
suffix:semicolon
id|i
op_increment
)paren
(brace
id|m68k_memory
(braket
id|i
)braket
dot
id|size
op_and_assign
id|MASK_256K
suffix:semicolon
r_if
c_cond
(paren
id|m68k_memory
(braket
id|i
)braket
dot
id|addr
OL
id|startmem
)paren
id|startmem
op_assign
id|m68k_memory
(braket
id|i
)braket
dot
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|m68k_memory
(braket
id|i
)braket
dot
id|addr
op_plus
id|m68k_memory
(braket
id|i
)braket
dot
id|size
OG
id|endmem
)paren
id|endmem
op_assign
id|m68k_memory
(braket
id|i
)braket
dot
id|addr
op_plus
id|m68k_memory
(braket
id|i
)braket
dot
id|size
suffix:semicolon
id|high_memory
op_add_assign
id|m68k_memory
(braket
id|i
)braket
dot
id|size
suffix:semicolon
)brace
id|availmem
op_add_assign
id|init_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
l_int|0
)paren
comma
id|availmem
op_rshift
id|PAGE_SHIFT
comma
id|startmem
op_rshift
id|PAGE_SHIFT
comma
id|endmem
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|m68k_num_memory
suffix:semicolon
id|i
op_increment
)paren
id|free_bootmem
c_func
(paren
id|m68k_memory
(braket
id|i
)braket
dot
id|addr
comma
id|m68k_memory
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
id|reserve_bootmem
c_func
(paren
id|m68k_memory
(braket
l_int|0
)braket
dot
id|addr
comma
id|availmem
op_minus
id|m68k_memory
(braket
l_int|0
)braket
dot
id|addr
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|m68k_ramdisk.size
)paren
(brace
id|reserve_bootmem
c_func
(paren
id|m68k_ramdisk.addr
comma
id|m68k_ramdisk.size
)paren
suffix:semicolon
id|initrd_start
op_assign
(paren
r_int
r_int
)paren
id|phys_to_virt
c_func
(paren
id|m68k_ramdisk.addr
)paren
suffix:semicolon
id|initrd_end
op_assign
id|initrd_start
op_plus
id|m68k_ramdisk.size
suffix:semicolon
id|printk
(paren
l_string|&quot;initrd: %08lx - %08lx&bslash;n&quot;
comma
id|initrd_start
comma
id|initrd_end
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_ATARI
r_if
c_cond
(paren
id|MACH_IS_ATARI
)paren
id|atari_stram_reserve_pages
c_func
(paren
id|availmem
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SUN3X
r_if
c_cond
(paren
id|MACH_IS_SUN3X
)paren
(brace
id|dvma_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SUN3X_ZS
id|sun_serial_setup
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
macro_line|#endif /* !CONFIG_SUN3 */
id|paging_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* set ISA defs early as possible */
macro_line|#if defined(CONFIG_ISA) &amp;&amp; defined(MULTI_ISA)
macro_line|#if defined(CONFIG_Q40) 
r_if
c_cond
(paren
id|MACH_IS_Q40
)paren
(brace
id|isa_type
op_assign
id|Q40_ISA
suffix:semicolon
id|isa_sex
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_GG2)
r_if
c_cond
(paren
id|MACH_IS_AMIGA
op_logical_and
id|AMIGAHW_PRESENT
c_func
(paren
id|GG2_ISA
)paren
)paren
(brace
id|isa_type
op_assign
id|GG2_ISA
suffix:semicolon
id|isa_sex
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_AMIGA_PCMCIA)
r_if
c_cond
(paren
id|MACH_IS_AMIGA
op_logical_and
id|AMIGAHW_PRESENT
c_func
(paren
id|PCMCIA
)paren
)paren
(brace
id|isa_type
op_assign
id|AG_ISA
suffix:semicolon
id|isa_sex
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
)brace
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
r_const
r_char
op_star
id|cpu
comma
op_star
id|mmu
comma
op_star
id|fpu
suffix:semicolon
r_int
r_int
id|clockfreq
comma
id|clockfactor
suffix:semicolon
DECL|macro|LOOP_CYCLES_68020
mdefine_line|#define LOOP_CYCLES_68020&t;(8)
DECL|macro|LOOP_CYCLES_68030
mdefine_line|#define LOOP_CYCLES_68030&t;(8)
DECL|macro|LOOP_CYCLES_68040
mdefine_line|#define LOOP_CYCLES_68040&t;(3)
DECL|macro|LOOP_CYCLES_68060
mdefine_line|#define LOOP_CYCLES_68060&t;(1)
r_if
c_cond
(paren
id|CPU_IS_020
)paren
(brace
id|cpu
op_assign
l_string|&quot;68020&quot;
suffix:semicolon
id|clockfactor
op_assign
id|LOOP_CYCLES_68020
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|CPU_IS_030
)paren
(brace
id|cpu
op_assign
l_string|&quot;68030&quot;
suffix:semicolon
id|clockfactor
op_assign
id|LOOP_CYCLES_68030
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|CPU_IS_040
)paren
(brace
id|cpu
op_assign
l_string|&quot;68040&quot;
suffix:semicolon
id|clockfactor
op_assign
id|LOOP_CYCLES_68040
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|CPU_IS_060
)paren
(brace
id|cpu
op_assign
l_string|&quot;68060&quot;
suffix:semicolon
id|clockfactor
op_assign
id|LOOP_CYCLES_68060
suffix:semicolon
)brace
r_else
(brace
id|cpu
op_assign
l_string|&quot;680x0&quot;
suffix:semicolon
id|clockfactor
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_M68KFPU_EMU_ONLY
id|fpu
op_assign
l_string|&quot;none(soft float)&quot;
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|m68k_fputype
op_amp
id|FPU_68881
)paren
id|fpu
op_assign
l_string|&quot;68881&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|m68k_fputype
op_amp
id|FPU_68882
)paren
id|fpu
op_assign
l_string|&quot;68882&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|m68k_fputype
op_amp
id|FPU_68040
)paren
id|fpu
op_assign
l_string|&quot;68040&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|m68k_fputype
op_amp
id|FPU_68060
)paren
id|fpu
op_assign
l_string|&quot;68060&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|m68k_fputype
op_amp
id|FPU_SUNFPA
)paren
id|fpu
op_assign
l_string|&quot;Sun FPA&quot;
suffix:semicolon
r_else
id|fpu
op_assign
l_string|&quot;none&quot;
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|m68k_mmutype
op_amp
id|MMU_68851
)paren
id|mmu
op_assign
l_string|&quot;68851&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|m68k_mmutype
op_amp
id|MMU_68030
)paren
id|mmu
op_assign
l_string|&quot;68030&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|m68k_mmutype
op_amp
id|MMU_68040
)paren
id|mmu
op_assign
l_string|&quot;68040&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|m68k_mmutype
op_amp
id|MMU_68060
)paren
id|mmu
op_assign
l_string|&quot;68060&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|m68k_mmutype
op_amp
id|MMU_SUN3
)paren
id|mmu
op_assign
l_string|&quot;Sun-3&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|m68k_mmutype
op_amp
id|MMU_APOLLO
)paren
id|mmu
op_assign
l_string|&quot;Apollo&quot;
suffix:semicolon
r_else
id|mmu
op_assign
l_string|&quot;unknown&quot;
suffix:semicolon
id|clockfreq
op_assign
id|loops_per_jiffy
op_star
id|HZ
op_star
id|clockfactor
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;CPU:&bslash;t&bslash;t%s&bslash;n&quot;
l_string|&quot;MMU:&bslash;t&bslash;t%s&bslash;n&quot;
l_string|&quot;FPU:&bslash;t&bslash;t%s&bslash;n&quot;
l_string|&quot;Clocking:&bslash;t%lu.%1luMHz&bslash;n&quot;
l_string|&quot;BogoMips:&bslash;t%lu.%02lu&bslash;n&quot;
l_string|&quot;Calibration:&bslash;t%lu loops&bslash;n&quot;
comma
id|cpu
comma
id|mmu
comma
id|fpu
comma
id|clockfreq
op_div
l_int|1000000
comma
(paren
id|clockfreq
op_div
l_int|100000
)paren
op_mod
l_int|10
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
comma
id|loops_per_jiffy
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
DECL|function|get_hardware_list
r_int
id|get_hardware_list
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_char
id|model
(braket
l_int|80
)braket
suffix:semicolon
r_int
r_int
id|mem
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|mach_get_model
)paren
id|mach_get_model
c_func
(paren
id|model
)paren
suffix:semicolon
r_else
id|strcpy
c_func
(paren
id|model
comma
l_string|&quot;Unknown m68k&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Model:&bslash;t&bslash;t%s&bslash;n&quot;
comma
id|model
)paren
suffix:semicolon
id|len
op_add_assign
id|get_cpuinfo
c_func
(paren
id|buffer
op_plus
id|len
)paren
suffix:semicolon
r_for
c_loop
(paren
id|mem
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|m68k_num_memory
suffix:semicolon
id|i
op_increment
)paren
id|mem
op_add_assign
id|m68k_memory
(braket
id|i
)braket
dot
id|size
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;System Memory:&bslash;t%ldK&bslash;n&quot;
comma
id|mem
op_rshift
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mach_get_hardware_list
)paren
id|len
op_add_assign
id|mach_get_hardware_list
c_func
(paren
id|buffer
op_plus
id|len
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_AMIGA_FLOPPY) || defined(CONFIG_ATARI_FLOPPY)
DECL|function|floppy_setup
r_void
id|__init
id|floppy_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
(brace
r_if
c_cond
(paren
id|mach_floppy_setup
)paren
id|mach_floppy_setup
(paren
id|str
comma
id|ints
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* for &quot;kbd-reset&quot; cmdline param */
DECL|function|kbd_reset_setup
r_void
id|__init
id|kbd_reset_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
(brace
)brace
DECL|function|check_bugs
r_void
id|check_bugs
c_func
(paren
r_void
)paren
(brace
macro_line|#ifndef CONFIG_M68KFPU_EMU
r_if
c_cond
(paren
id|m68k_fputype
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;*** YOU DO NOT HAVE A FLOATING POINT UNIT, &quot;
l_string|&quot;WHICH IS REQUIRED BY LINUX/M68K ***&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Upgrade your hardware or join the FPU &quot;
l_string|&quot;emulation project&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;(see http://no-fpu.linux-m68k.org)&bslash;n&quot;
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;no FPU&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SUN3 */
)brace
eof
