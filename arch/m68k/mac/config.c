multiline_comment|/*&n; *  linux/arch/m68k/mac/config.c&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
multiline_comment|/*&n; * Miscellaneous linux stuff&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
multiline_comment|/* keyb */
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
multiline_comment|/* keyb */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
DECL|macro|BOOTINFO_COMPAT_1_0
mdefine_line|#define BOOTINFO_COMPAT_1_0
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/macintosh.h&gt;
macro_line|#include &lt;asm/macints.h&gt;
macro_line|#include &lt;asm/machw.h&gt;
macro_line|#include &lt;asm/mac_iop.h&gt;
macro_line|#include &lt;asm/mac_via.h&gt;
macro_line|#include &lt;asm/mac_oss.h&gt;
macro_line|#include &lt;asm/mac_psc.h&gt;
multiline_comment|/* Mac bootinfo struct */
DECL|variable|mac_bi_data
r_struct
id|mac_booter_data
id|mac_bi_data
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|mac_bisize
r_int
id|mac_bisize
op_assign
r_sizeof
id|mac_bi_data
suffix:semicolon
DECL|variable|mac_hw_present
r_struct
id|mac_hw_present
id|mac_hw_present
suffix:semicolon
multiline_comment|/* New m68k bootinfo stuff and videobase */
r_extern
r_int
id|m68k_num_memory
suffix:semicolon
r_extern
r_struct
id|mem_info
id|m68k_memory
(braket
id|NUM_MEMINFO
)braket
suffix:semicolon
r_extern
r_struct
id|mem_info
id|m68k_ramdisk
suffix:semicolon
r_extern
r_char
id|m68k_command_line
(braket
id|CL_SIZE
)braket
suffix:semicolon
DECL|variable|mac_env
r_void
op_star
id|mac_env
suffix:semicolon
multiline_comment|/* Loaded by the boot asm */
multiline_comment|/* The phys. video addr. - might be bogus on some machines */
DECL|variable|mac_orig_videoaddr
r_int
r_int
id|mac_orig_videoaddr
suffix:semicolon
multiline_comment|/* Mac specific timer functions */
r_extern
r_int
r_int
id|mac_gettimeoffset
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|mac_hwclk
(paren
r_int
comma
r_struct
id|rtc_time
op_star
)paren
suffix:semicolon
r_extern
r_int
id|mac_set_clock_mmss
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|show_mac_interrupts
c_func
(paren
r_struct
id|seq_file
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|iop_preinit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iop_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|via_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|via_init_clock
c_func
(paren
r_void
(paren
op_star
id|func
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
suffix:semicolon
r_extern
r_void
id|via_flush_cache
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|oss_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|psc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|baboon_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|nubus_sweep_video
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Mac specific debug functions (in debug.c) */
r_extern
r_void
id|mac_debug_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mac_debugging_long
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_static
r_void
id|mac_get_model
c_func
(paren
r_char
op_star
id|str
)paren
suffix:semicolon
DECL|function|mac_bang
r_void
id|mac_bang
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|vector
comma
r_struct
id|pt_regs
op_star
id|p
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Resetting ...&bslash;n&quot;
)paren
suffix:semicolon
id|mac_reset
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|mac_sched_init
r_static
r_void
id|mac_sched_init
c_func
(paren
r_void
(paren
op_star
id|vector
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
(brace
id|via_init_clock
c_func
(paren
id|vector
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_void
id|mac_waitbut
(paren
r_void
)paren
(brace
suffix:semicolon
)brace
macro_line|#endif
r_extern
r_void
id|mac_default_handler
c_func
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
suffix:semicolon
DECL|variable|mac_handlers
r_void
(paren
op_star
id|mac_handlers
(braket
l_int|8
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
(brace
id|mac_default_handler
comma
id|mac_default_handler
comma
id|mac_default_handler
comma
id|mac_default_handler
comma
id|mac_default_handler
comma
id|mac_default_handler
comma
id|mac_default_handler
comma
id|mac_default_handler
)brace
suffix:semicolon
multiline_comment|/*&n; * Parse a Macintosh-specific record in the bootinfo&n; */
DECL|function|mac_parse_bootinfo
r_int
id|__init
id|mac_parse_bootinfo
c_func
(paren
r_const
r_struct
id|bi_record
op_star
id|record
)paren
(brace
r_int
id|unknown
op_assign
l_int|0
suffix:semicolon
r_const
id|u_long
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
id|BI_MAC_MODEL
suffix:colon
id|mac_bi_data.id
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_VADDR
suffix:colon
id|mac_bi_data.videoaddr
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_VDEPTH
suffix:colon
id|mac_bi_data.videodepth
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_VROW
suffix:colon
id|mac_bi_data.videorow
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_VDIM
suffix:colon
id|mac_bi_data.dimensions
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_VLOGICAL
suffix:colon
id|mac_bi_data.videological
op_assign
id|VIDEOMEMBASE
op_plus
(paren
op_star
id|data
op_amp
op_complement
id|VIDEOMEMMASK
)paren
suffix:semicolon
id|mac_orig_videoaddr
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_SCCBASE
suffix:colon
id|mac_bi_data.sccbase
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_BTIME
suffix:colon
id|mac_bi_data.boottime
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_GMTBIAS
suffix:colon
id|mac_bi_data.gmtbias
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_MEMSIZE
suffix:colon
id|mac_bi_data.memsize
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_CPUID
suffix:colon
id|mac_bi_data.cpuid
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_ROMBASE
suffix:colon
id|mac_bi_data.rombase
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|unknown
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|unknown
suffix:semicolon
)brace
multiline_comment|/*&n; * Flip into 24bit mode for an instant - flushes the L2 cache card. We&n; * have to disable interrupts for this. Our IRQ handlers will crap &n; * themselves if they take an IRQ in 24bit mode!&n; */
DECL|function|mac_cache_card_flush
r_static
r_void
id|mac_cache_card_flush
c_func
(paren
r_int
id|writeback
)paren
(brace
r_int
r_int
id|cpu_flags
suffix:semicolon
id|save_flags
c_func
(paren
id|cpu_flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|via_flush_cache
c_func
(paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|cpu_flags
)paren
suffix:semicolon
)brace
DECL|function|config_mac
r_void
id|__init
id|config_mac
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_MAC
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ERROR: no Mac, but config_mac() called!! &bslash;n&quot;
)paren
suffix:semicolon
)brace
id|mach_sched_init
op_assign
id|mac_sched_init
suffix:semicolon
id|mach_init_IRQ
op_assign
id|mac_init_IRQ
suffix:semicolon
id|mach_request_irq
op_assign
id|mac_request_irq
suffix:semicolon
id|mach_free_irq
op_assign
id|mac_free_irq
suffix:semicolon
id|enable_irq
op_assign
id|mac_enable_irq
suffix:semicolon
id|disable_irq
op_assign
id|mac_disable_irq
suffix:semicolon
id|mach_get_model
op_assign
id|mac_get_model
suffix:semicolon
id|mach_default_handler
op_assign
op_amp
id|mac_handlers
suffix:semicolon
id|mach_get_irq_list
op_assign
id|show_mac_interrupts
suffix:semicolon
id|mach_gettimeoffset
op_assign
id|mac_gettimeoffset
suffix:semicolon
macro_line|#warning move to adb/via init
macro_line|#if 0
id|mach_hwclk
op_assign
id|mac_hwclk
suffix:semicolon
macro_line|#endif
id|mach_set_clock_mmss
op_assign
id|mac_set_clock_mmss
suffix:semicolon
id|mach_reset
op_assign
id|mac_reset
suffix:semicolon
id|mach_halt
op_assign
id|mac_poweroff
suffix:semicolon
id|mach_power_off
op_assign
id|mac_poweroff
suffix:semicolon
macro_line|#ifdef CONFIG_DUMMY_CONSOLE
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
id|mach_max_dma_address
op_assign
l_int|0xffffffff
suffix:semicolon
macro_line|#if 0
id|mach_debug_init
op_assign
id|mac_debug_init
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_INPUT_M68K_BEEP
id|mach_beep
op_assign
id|mac_mksound
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_HEARTBEAT
macro_line|#if 0
id|mach_heartbeat
op_assign
id|mac_heartbeat
suffix:semicolon
id|mach_heartbeat_irq
op_assign
id|IRQ_MAC_TIMER
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n;&t; * Determine hardware present&n;&t; */
id|mac_identify
c_func
(paren
)paren
suffix:semicolon
id|mac_report_hardware
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* AFAIK only the IIci takes a cache card.  The IIfx has onboard&n;&t;   cache ... someone needs to figure out how to tell if it&squot;s on or&n;&t;   not. */
r_if
c_cond
(paren
id|macintosh_config-&gt;ident
op_eq
id|MAC_MODEL_IICI
op_logical_or
id|macintosh_config-&gt;ident
op_eq
id|MAC_MODEL_IIFX
)paren
(brace
id|mach_l2_flush
op_assign
id|mac_cache_card_flush
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Check for machine specific fixups.&n;&t; */
macro_line|#ifdef OLD_NUBUS_CODE
id|nubus_sweep_video
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; *&t;Macintosh Table: hardcoded model configuration data. &n; *&n; *&t;Much of this was defined by Alan, based on who knows what docs. &n; *&t;I&squot;ve added a lot more, and some of that was pure guesswork based &n; *&t;on hardware pages present on the Mac web site. Possibly wildly &n; *&t;inaccurate, so look here if a new Mac model won&squot;t run. Example: if&n; *&t;a Mac crashes immediately after the VIA1 registers have been dumped&n; *&t;to the screen, it probably died attempting to read DirB on a RBV. &n; *&t;Meaning it should have MAC_VIA_IIci here :-)&n; */
DECL|variable|macintosh_config
r_struct
id|mac_model
op_star
id|macintosh_config
suffix:semicolon
DECL|variable|mac_data_table
r_static
r_struct
id|mac_model
id|mac_data_table
(braket
)braket
op_assign
(brace
multiline_comment|/*&n;&t; *&t;We&squot;ll pretend to be a Macintosh II, that&squot;s pretty safe.&n;&t; */
(brace
id|MAC_MODEL_II
comma
l_string|&quot;Unknown&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_II
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/*&n;&t; *&t;Original MacII hardware&n;&t; *&t;&n;&t; */
(brace
id|MAC_MODEL_II
comma
l_string|&quot;II&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_II
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_IIX
comma
l_string|&quot;IIx&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_II
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_IICX
comma
l_string|&quot;IIcx&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_II
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_SE30
comma
l_string|&quot;SE/30&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_II
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/*&n;&t; *&t;Weirdified MacII hardware - all subtley different. Gee thanks&n;&t; *&t;Apple. All these boxes seem to have VIA2 in a different place to&n;&t; *&t;the MacII (+1A000 rather than +4000)&n;&t; * CSA: see http://developer.apple.com/technotes/hw/hw_09.html&n;&t; */
(brace
id|MAC_MODEL_IICI
comma
l_string|&quot;IIci&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_IIFX
comma
l_string|&quot;IIfx&quot;
comma
id|MAC_ADB_IOP
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_IOP
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_IISI
comma
l_string|&quot;IIsi&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_IIVI
comma
l_string|&quot;IIvi&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_IIVX
comma
l_string|&quot;IIvx&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/*&n;&t; *&t;Classic models (guessing: similar to SE/30 ?? Nope, similar to LC ...)&n;&t; */
(brace
id|MAC_MODEL_CLII
comma
l_string|&quot;Classic II&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_CCL
comma
l_string|&quot;Color Classic&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/*&n;&t; *&t;Some Mac LC machines. Basically the same as the IIci, ADB like IIsi&n;&t; */
(brace
id|MAC_MODEL_LC
comma
l_string|&quot;LC&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_LCII
comma
l_string|&quot;LC II&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_LCIII
comma
l_string|&quot;LC III&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/*&n;&t; *&t;Quadra. Video is at 0xF9000000, via is like a MacII. We label it differently &n;&t; *&t;as some of the stuff connected to VIA2 seems different. Better SCSI chip and &n;&t; *&t;onboard ethernet using a NatSemi SONIC except the 660AV and 840AV which use an &n;&t; *&t;AMD 79C940 (MACE).&n;&t; *&t;The 700, 900 and 950 have some I/O chips in the wrong place to&n;&t; *&t;confuse us. The 840AV has a SCSI location of its own (same as&n;&t; *&t;the 660AV).&n;&t; */
(brace
id|MAC_MODEL_Q605
comma
l_string|&quot;Quadra 605&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_Q610
comma
l_string|&quot;Quadra 610&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_SONIC
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_Q630
comma
l_string|&quot;Quadra 630&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_QUADRA
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_SONIC
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_Q650
comma
l_string|&quot;Quadra 650&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_SONIC
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/*&t;The Q700 does have a NS Sonic */
(brace
id|MAC_MODEL_Q700
comma
l_string|&quot;Quadra 700&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA2
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA2
comma
id|MAC_ETHER_SONIC
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_Q800
comma
l_string|&quot;Quadra 800&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_SONIC
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_Q840
comma
l_string|&quot;Quadra 840AV&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA3
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_MACE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_Q900
comma
l_string|&quot;Quadra 900&quot;
comma
id|MAC_ADB_IOP
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA2
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_IOP
comma
id|MAC_ETHER_SONIC
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_Q950
comma
l_string|&quot;Quadra 950&quot;
comma
id|MAC_ADB_IOP
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA2
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_IOP
comma
id|MAC_ETHER_SONIC
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/* &n;&t; *&t;Performa - more LC type machines&n;&t; */
(brace
id|MAC_MODEL_P460
comma
l_string|&quot;Performa 460&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_P475
comma
l_string|&quot;Performa 475&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_P475F
comma
l_string|&quot;Performa 475&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_P520
comma
l_string|&quot;Performa 520&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_P550
comma
l_string|&quot;Performa 550&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_P575
comma
l_string|&quot;Performa 575&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/* These have the comm slot, and therefore the possibility of SONIC ethernet */
(brace
id|MAC_MODEL_P588
comma
l_string|&quot;Performa 588&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_QUADRA
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_SONIC
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_TV
comma
l_string|&quot;TV&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_P600
comma
l_string|&quot;Performa 600&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/*&n;&t; *&t;Centris - just guessing again; maybe like Quadra&n;&t; */
multiline_comment|/* The C610 may or may not have SONIC.  We probe to make sure */
(brace
id|MAC_MODEL_C610
comma
l_string|&quot;Centris 610&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_SONIC
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_C650
comma
l_string|&quot;Centris 650&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_SONIC
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_C660
comma
l_string|&quot;Centris 660AV&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA3
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_MACE
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/*&n;&t; * The PowerBooks all the same &quot;Combo&quot; custom IC for SCSI and SCC&n;&t; * and a PMU (in two variations?) for ADB. Most of them use the&n;&t; * Quadra-style VIAs. A few models also have IDE from hell.&n;&t; */
(brace
id|MAC_MODEL_PB140
comma
l_string|&quot;PowerBook 140&quot;
comma
id|MAC_ADB_PB1
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB145
comma
l_string|&quot;PowerBook 145&quot;
comma
id|MAC_ADB_PB1
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB150
comma
l_string|&quot;PowerBook 150&quot;
comma
id|MAC_ADB_PB1
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_PB
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB160
comma
l_string|&quot;PowerBook 160&quot;
comma
id|MAC_ADB_PB1
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB165
comma
l_string|&quot;PowerBook 165&quot;
comma
id|MAC_ADB_PB1
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB165C
comma
l_string|&quot;PowerBook 165c&quot;
comma
id|MAC_ADB_PB1
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB170
comma
l_string|&quot;PowerBook 170&quot;
comma
id|MAC_ADB_PB1
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB180
comma
l_string|&quot;PowerBook 180&quot;
comma
id|MAC_ADB_PB1
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB180C
comma
l_string|&quot;PowerBook 180c&quot;
comma
id|MAC_ADB_PB1
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB190
comma
l_string|&quot;PowerBook 190&quot;
comma
id|MAC_ADB_PB2
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_BABOON
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB520
comma
l_string|&quot;PowerBook 520&quot;
comma
id|MAC_ADB_PB2
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_SONIC
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/*&n;&t; * PowerBook Duos are pretty much like normal PowerBooks&n;&t; * All of these probably have onboard SONIC in the Dock which&n;&t; * means we&squot;ll have to probe for it eventually.&n;&t; *&n;&t; * Are these reallly MAC_VIA_IIci? The developer notes for the&n;&t; * Duos show pretty much the same custom parts as in most of&n;&t; * the other PowerBooks which would imply MAC_VIA_QUADRA.&n;&t; */
(brace
id|MAC_MODEL_PB210
comma
l_string|&quot;PowerBook Duo 210&quot;
comma
id|MAC_ADB_PB2
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB230
comma
l_string|&quot;PowerBook Duo 230&quot;
comma
id|MAC_ADB_PB2
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB250
comma
l_string|&quot;PowerBook Duo 250&quot;
comma
id|MAC_ADB_PB2
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB270C
comma
l_string|&quot;PowerBook Duo 270c&quot;
comma
id|MAC_ADB_PB2
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB280
comma
l_string|&quot;PowerBook Duo 280&quot;
comma
id|MAC_ADB_PB2
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB280C
comma
l_string|&quot;PowerBook Duo 280c&quot;
comma
id|MAC_ADB_PB2
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/*&n;&t; *&t;Other stuff ??&n;&t; */
(brace
op_minus
l_int|1
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|function|mac_identify
r_void
id|mac_identify
c_func
(paren
r_void
)paren
(brace
r_struct
id|mac_model
op_star
id|m
suffix:semicolon
multiline_comment|/* Penguin data useful? */
r_int
id|model
op_assign
id|mac_bi_data.id
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|model
)paren
(brace
multiline_comment|/* no bootinfo model id -&gt; NetBSD booter was used! */
multiline_comment|/* XXX FIXME: breaks for model &gt; 31 */
id|model
op_assign
(paren
id|mac_bi_data.cpuid
op_rshift
l_int|2
)paren
op_amp
l_int|63
suffix:semicolon
id|printk
(paren
l_string|&quot;No bootinfo model ID, using cpuid instead (hey, use Penguin!)&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|macintosh_config
op_assign
id|mac_data_table
suffix:semicolon
r_for
c_loop
(paren
id|m
op_assign
id|macintosh_config
suffix:semicolon
id|m-&gt;ident
op_ne
op_minus
l_int|1
suffix:semicolon
id|m
op_increment
)paren
(brace
r_if
c_cond
(paren
id|m-&gt;ident
op_eq
id|model
)paren
(brace
id|macintosh_config
op_assign
id|m
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* We need to pre-init the IOPs, if any. Otherwise */
multiline_comment|/* the serial console won&squot;t work if the user had   */
multiline_comment|/* the serial ports set to &quot;Faster&quot; mode in MacOS. */
id|iop_preinit
c_func
(paren
)paren
suffix:semicolon
id|mac_debug_init
c_func
(paren
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;Detected Macintosh model: %d &bslash;n&quot;
comma
id|model
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Report booter data:&n;&t; */
id|printk
(paren
l_string|&quot; Penguin bootinfo data:&bslash;n&quot;
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot; Video: addr 0x%lx row 0x%lx depth %lx dimensions %ld x %ld&bslash;n&quot;
comma
id|mac_bi_data.videoaddr
comma
id|mac_bi_data.videorow
comma
id|mac_bi_data.videodepth
comma
id|mac_bi_data.dimensions
op_amp
l_int|0xFFFF
comma
id|mac_bi_data.dimensions
op_rshift
l_int|16
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot; Videological 0x%lx phys. 0x%lx, SCC at 0x%lx &bslash;n&quot;
comma
id|mac_bi_data.videological
comma
id|mac_orig_videoaddr
comma
id|mac_bi_data.sccbase
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot; Boottime: 0x%lx GMTBias: 0x%lx &bslash;n&quot;
comma
id|mac_bi_data.boottime
comma
id|mac_bi_data.gmtbias
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot; Machine ID: %ld CPUid: 0x%lx memory size: 0x%lx &bslash;n&quot;
comma
id|mac_bi_data.id
comma
id|mac_bi_data.cpuid
comma
id|mac_bi_data.memsize
)paren
suffix:semicolon
macro_line|#if 0
id|printk
(paren
l_string|&quot;Ramdisk: addr 0x%lx size 0x%lx&bslash;n&quot;
comma
id|m68k_ramdisk.addr
comma
id|m68k_ramdisk.size
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * TODO: set the various fields in macintosh_config-&gt;hw_present here!&n;&t; */
r_switch
c_cond
(paren
id|macintosh_config-&gt;scsi_type
)paren
(brace
r_case
id|MAC_SCSI_OLD
suffix:colon
id|MACHW_SET
c_func
(paren
id|MAC_SCSI_80
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MAC_SCSI_QUADRA
suffix:colon
r_case
id|MAC_SCSI_QUADRA2
suffix:colon
r_case
id|MAC_SCSI_QUADRA3
suffix:colon
id|MACHW_SET
c_func
(paren
id|MAC_SCSI_96
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|macintosh_config-&gt;ident
op_eq
id|MAC_MODEL_Q900
)paren
op_logical_or
(paren
id|macintosh_config-&gt;ident
op_eq
id|MAC_MODEL_Q950
)paren
)paren
id|MACHW_SET
c_func
(paren
id|MAC_SCSI_96_2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;config.c: wtf: unknown scsi, using 53c80&bslash;n&quot;
)paren
suffix:semicolon
id|MACHW_SET
c_func
(paren
id|MAC_SCSI_80
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|iop_init
c_func
(paren
)paren
suffix:semicolon
id|via_init
c_func
(paren
)paren
suffix:semicolon
id|oss_init
c_func
(paren
)paren
suffix:semicolon
id|psc_init
c_func
(paren
)paren
suffix:semicolon
id|baboon_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|mac_report_hardware
r_void
id|mac_report_hardware
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Apple Macintosh %s&bslash;n&quot;
comma
id|macintosh_config-&gt;name
)paren
suffix:semicolon
)brace
DECL|function|mac_get_model
r_static
r_void
id|mac_get_model
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|strcpy
c_func
(paren
id|str
comma
l_string|&quot;Macintosh &quot;
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|str
comma
id|macintosh_config-&gt;name
)paren
suffix:semicolon
)brace
eof
