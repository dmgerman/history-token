multiline_comment|/*&n; *  arch/m68k/mvme16x/config.c&n; *&n; *  Copyright (C) 1995 Richard Hirst [richard@sleepie.demon.co.uk]&n; *&n; * Based on:&n; *&n; *  linux/amiga/config.c&n; *&n; *  Copyright (C) 1993 Hamish Macdonald&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file README.legal in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/rtc.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/mvme16xhw.h&gt;
r_extern
id|t_bdid
id|mvme_bdid
suffix:semicolon
DECL|variable|rtc
r_static
id|MK48T08ptr_t
r_volatile
id|rtc
op_assign
(paren
id|MK48T08ptr_t
)paren
id|MVME_RTC_BASE
suffix:semicolon
r_extern
r_void
id|mvme16x_process_int
(paren
r_int
id|level
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|mvme16x_init_IRQ
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mvme16x_free_irq
(paren
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|show_mvme16x_interrupts
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
id|mvme16x_enable_irq
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|mvme16x_disable_irq
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|mvme16x_get_model
c_func
(paren
r_char
op_star
id|model
)paren
suffix:semicolon
r_static
r_int
id|mvme16x_get_hardware_list
c_func
(paren
r_char
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_int
id|mvme16x_request_irq
c_func
(paren
r_int
r_int
id|irq
comma
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
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|devname
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
r_extern
r_void
id|mvme16x_sched_init
c_func
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
suffix:semicolon
r_extern
r_int
id|mvme16x_keyb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|mvme16x_kbdrate
(paren
r_struct
id|kbd_repeat
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|mvme16x_gettimeoffset
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|mvme16x_hwclk
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
id|mvme16x_set_clock_mmss
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|mvme16x_check_partition
(paren
r_struct
id|gendisk
op_star
id|hd
comma
r_int
r_int
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|mvme16x_mksound
c_func
(paren
r_int
r_int
id|count
comma
r_int
r_int
id|ticks
)paren
suffix:semicolon
r_extern
r_void
id|mvme16x_reset
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mvme16x_waitbut
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|bcd2int
(paren
r_int
r_char
id|b
)paren
suffix:semicolon
multiline_comment|/* Save tick handler routine pointer, will point to do_timer() in&n; * kernel/sched.c, called via mvme16x_process_int() */
DECL|variable|tick_handler
r_static
r_void
(paren
op_star
id|tick_handler
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
suffix:semicolon
DECL|variable|mvme16x_config
r_int
r_int
id|mvme16x_config
suffix:semicolon
DECL|function|mvme16x_parse_bootinfo
r_int
id|mvme16x_parse_bootinfo
c_func
(paren
r_const
r_struct
id|bi_record
op_star
id|bi
)paren
(brace
r_if
c_cond
(paren
id|bi-&gt;tag
op_eq
id|BI_VME_TYPE
op_logical_or
id|bi-&gt;tag
op_eq
id|BI_VME_BRDINFO
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|mvme16x_kbdrate
r_int
id|mvme16x_kbdrate
(paren
r_struct
id|kbd_repeat
op_star
id|k
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mvme16x_mksound
r_void
id|mvme16x_mksound
c_func
(paren
r_int
r_int
id|count
comma
r_int
r_int
id|ticks
)paren
(brace
)brace
DECL|function|mvme16x_reset
r_void
id|mvme16x_reset
c_func
(paren
)paren
(brace
id|printk
(paren
l_string|&quot;&bslash;r&bslash;n&bslash;nCalled mvme16x_reset&bslash;r&bslash;n&quot;
l_string|&quot;&bslash;r&bslash;r&bslash;r&bslash;r&bslash;r&bslash;r&bslash;r&bslash;r&bslash;r&bslash;r&bslash;r&bslash;r&bslash;r&bslash;r&bslash;r&bslash;r&bslash;r&bslash;r&quot;
)paren
suffix:semicolon
multiline_comment|/* The string of returns is to delay the reset until the whole&n;&t; * message is output.  Assert reset bit in GCSR */
op_star
(paren
r_volatile
r_char
op_star
)paren
l_int|0xfff40107
op_assign
l_int|0x80
suffix:semicolon
)brace
DECL|function|mvme16x_get_model
r_static
r_void
id|mvme16x_get_model
c_func
(paren
r_char
op_star
id|model
)paren
(brace
id|p_bdid
id|p
op_assign
op_amp
id|mvme_bdid
suffix:semicolon
r_char
id|suf
(braket
l_int|4
)braket
suffix:semicolon
id|suf
(braket
l_int|1
)braket
op_assign
id|p-&gt;brdsuffix
(braket
l_int|0
)braket
suffix:semicolon
id|suf
(braket
l_int|2
)braket
op_assign
id|p-&gt;brdsuffix
(braket
l_int|1
)braket
suffix:semicolon
id|suf
(braket
l_int|3
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|suf
(braket
l_int|0
)braket
op_assign
id|suf
(braket
l_int|1
)braket
ques
c_cond
l_char|&squot;-&squot;
suffix:colon
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|sprintf
c_func
(paren
id|model
comma
l_string|&quot;Motorola MVME%x%s&quot;
comma
id|p-&gt;brdno
comma
id|suf
)paren
suffix:semicolon
)brace
DECL|function|mvme16x_get_hardware_list
r_static
r_int
id|mvme16x_get_hardware_list
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
id|p_bdid
id|p
op_assign
op_amp
id|mvme_bdid
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;brdno
op_eq
l_int|0x0162
op_logical_or
id|p-&gt;brdno
op_eq
l_int|0x0172
)paren
(brace
r_int
r_char
id|rev
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
id|MVME162_VERSION_REG
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;VMEchip2        %spresent&bslash;n&quot;
comma
id|rev
op_amp
id|MVME16x_CONFIG_NO_VMECHIP2
ques
c_cond
l_string|&quot;NOT &quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;SCSI interface  %spresent&bslash;n&quot;
comma
id|rev
op_amp
id|MVME16x_CONFIG_NO_SCSICHIP
ques
c_cond
l_string|&quot;NOT &quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Ethernet i/f    %spresent&bslash;n&quot;
comma
id|rev
op_amp
id|MVME16x_CONFIG_NO_ETHERNET
ques
c_cond
l_string|&quot;NOT &quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
r_else
op_star
id|buffer
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
(paren
id|len
)paren
suffix:semicolon
)brace
DECL|macro|pcc2chip
mdefine_line|#define pcc2chip&t;((volatile u_char *)0xfff42000)
DECL|macro|PccSCCMICR
mdefine_line|#define PccSCCMICR&t;0x1d
DECL|macro|PccSCCTICR
mdefine_line|#define PccSCCTICR&t;0x1e
DECL|macro|PccSCCRICR
mdefine_line|#define PccSCCRICR&t;0x1f
DECL|function|config_mvme16x
r_void
id|__init
id|config_mvme16x
c_func
(paren
r_void
)paren
(brace
id|p_bdid
id|p
op_assign
op_amp
id|mvme_bdid
suffix:semicolon
r_char
id|id
(braket
l_int|40
)braket
suffix:semicolon
id|mach_max_dma_address
op_assign
l_int|0xffffffff
suffix:semicolon
id|mach_sched_init
op_assign
id|mvme16x_sched_init
suffix:semicolon
id|mach_keyb_init
op_assign
id|mvme16x_keyb_init
suffix:semicolon
id|mach_kbdrate
op_assign
id|mvme16x_kbdrate
suffix:semicolon
id|mach_init_IRQ
op_assign
id|mvme16x_init_IRQ
suffix:semicolon
id|mach_gettimeoffset
op_assign
id|mvme16x_gettimeoffset
suffix:semicolon
id|mach_hwclk
op_assign
id|mvme16x_hwclk
suffix:semicolon
id|mach_set_clock_mmss
op_assign
id|mvme16x_set_clock_mmss
suffix:semicolon
multiline_comment|/*  kd_mksound           = mvme16x_mksound; */
id|mach_reset
op_assign
id|mvme16x_reset
suffix:semicolon
id|mach_free_irq
op_assign
id|mvme16x_free_irq
suffix:semicolon
id|mach_process_int
op_assign
id|mvme16x_process_int
suffix:semicolon
id|mach_get_irq_list
op_assign
id|show_mvme16x_interrupts
suffix:semicolon
id|mach_request_irq
op_assign
id|mvme16x_request_irq
suffix:semicolon
id|enable_irq
op_assign
id|mvme16x_enable_irq
suffix:semicolon
id|disable_irq
op_assign
id|mvme16x_disable_irq
suffix:semicolon
id|mach_get_model
op_assign
id|mvme16x_get_model
suffix:semicolon
id|mach_get_hardware_list
op_assign
id|mvme16x_get_hardware_list
suffix:semicolon
multiline_comment|/* Report board revision */
r_if
c_cond
(paren
id|strncmp
c_func
(paren
l_string|&quot;BDID&quot;
comma
id|p-&gt;bdid
comma
l_int|4
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;&bslash;n&bslash;nBug call .BRD_ID returned garbage - giving up&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Board type is only set by newer versions of vmelilo/tftplilo */
r_if
c_cond
(paren
id|vme_brdtype
op_eq
l_int|0
)paren
id|vme_brdtype
op_assign
id|p-&gt;brdno
suffix:semicolon
id|mvme16x_get_model
c_func
(paren
id|id
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;&bslash;nBRD_ID: %s   BUG %x.%x %02x/%02x/%02x&bslash;n&quot;
comma
id|id
comma
id|p-&gt;rev
op_rshift
l_int|4
comma
id|p-&gt;rev
op_amp
l_int|0xf
comma
id|p-&gt;yr
comma
id|p-&gt;mth
comma
id|p-&gt;day
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;brdno
op_eq
l_int|0x0162
op_logical_or
id|p-&gt;brdno
op_eq
l_int|0x172
)paren
(brace
r_int
r_char
id|rev
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
id|MVME162_VERSION_REG
suffix:semicolon
id|mvme16x_config
op_assign
id|rev
op_or
id|MVME16x_CONFIG_GOT_SCCA
suffix:semicolon
id|printk
(paren
l_string|&quot;MVME%x Hardware status:&bslash;n&quot;
comma
id|p-&gt;brdno
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;    CPU Type           68%s040&bslash;n&quot;
comma
id|rev
op_amp
id|MVME16x_CONFIG_GOT_FPU
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;LC&quot;
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;    CPU clock          %dMHz&bslash;n&quot;
comma
id|rev
op_amp
id|MVME16x_CONFIG_SPEED_32
ques
c_cond
l_int|32
suffix:colon
l_int|25
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;    VMEchip2           %spresent&bslash;n&quot;
comma
id|rev
op_amp
id|MVME16x_CONFIG_NO_VMECHIP2
ques
c_cond
l_string|&quot;NOT &quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;    SCSI interface     %spresent&bslash;n&quot;
comma
id|rev
op_amp
id|MVME16x_CONFIG_NO_SCSICHIP
ques
c_cond
l_string|&quot;NOT &quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;    Ethernet interface %spresent&bslash;n&quot;
comma
id|rev
op_amp
id|MVME16x_CONFIG_NO_ETHERNET
ques
c_cond
l_string|&quot;NOT &quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|mvme16x_config
op_assign
id|MVME16x_CONFIG_GOT_LP
op_or
id|MVME16x_CONFIG_GOT_CD2401
suffix:semicolon
multiline_comment|/* Dont allow any interrupts from the CD2401 until the interrupt */
multiline_comment|/* handlers are installed&t;&t;&t;&t;&t; */
id|pcc2chip
(braket
id|PccSCCMICR
)braket
op_assign
l_int|0x10
suffix:semicolon
id|pcc2chip
(braket
id|PccSCCTICR
)braket
op_assign
l_int|0x10
suffix:semicolon
id|pcc2chip
(braket
id|PccSCCRICR
)braket
op_assign
l_int|0x10
suffix:semicolon
)brace
)brace
DECL|function|mvme16x_abort_int
r_static
r_void
id|mvme16x_abort_int
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
id|p_bdid
id|p
op_assign
op_amp
id|mvme_bdid
suffix:semicolon
r_int
r_int
op_star
r_new
op_assign
(paren
r_int
r_int
op_star
)paren
id|vectors
suffix:semicolon
r_int
r_int
op_star
id|old
op_assign
(paren
r_int
r_int
op_star
)paren
l_int|0xffe00000
suffix:semicolon
r_volatile
r_int
r_char
id|uc
comma
op_star
id|ucp
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;brdno
op_eq
l_int|0x0162
op_logical_or
id|p-&gt;brdno
op_eq
l_int|0x172
)paren
(brace
id|ucp
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
l_int|0xfff42043
suffix:semicolon
id|uc
op_assign
op_star
id|ucp
op_or
l_int|8
suffix:semicolon
op_star
id|ucp
op_assign
id|uc
suffix:semicolon
)brace
r_else
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
l_int|0xfff40074
op_assign
l_int|0x40000000
suffix:semicolon
)brace
op_star
(paren
r_new
op_plus
l_int|4
)paren
op_assign
op_star
(paren
id|old
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Illegal instruction */
op_star
(paren
r_new
op_plus
l_int|9
)paren
op_assign
op_star
(paren
id|old
op_plus
l_int|9
)paren
suffix:semicolon
multiline_comment|/* Trace */
op_star
(paren
r_new
op_plus
l_int|47
)paren
op_assign
op_star
(paren
id|old
op_plus
l_int|47
)paren
suffix:semicolon
multiline_comment|/* Trap #15 */
r_if
c_cond
(paren
id|p-&gt;brdno
op_eq
l_int|0x0162
op_logical_or
id|p-&gt;brdno
op_eq
l_int|0x172
)paren
op_star
(paren
r_new
op_plus
l_int|0x5e
)paren
op_assign
op_star
(paren
id|old
op_plus
l_int|0x5e
)paren
suffix:semicolon
multiline_comment|/* ABORT switch */
r_else
op_star
(paren
r_new
op_plus
l_int|0x6e
)paren
op_assign
op_star
(paren
id|old
op_plus
l_int|0x6e
)paren
suffix:semicolon
multiline_comment|/* ABORT switch */
)brace
DECL|function|mvme16x_timer_int
r_static
r_void
id|mvme16x_timer_int
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
l_int|0xfff4201b
op_or_assign
l_int|8
suffix:semicolon
id|tick_handler
c_func
(paren
id|irq
comma
id|dev_id
comma
id|fp
)paren
suffix:semicolon
)brace
DECL|function|mvme16x_sched_init
r_void
id|mvme16x_sched_init
(paren
r_void
(paren
op_star
id|timer_routine
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
id|p_bdid
id|p
op_assign
op_amp
id|mvme_bdid
suffix:semicolon
r_int
id|irq
suffix:semicolon
id|tick_handler
op_assign
id|timer_routine
suffix:semicolon
multiline_comment|/* Using PCCchip2 or MC2 chip tick timer 1 */
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
l_int|0xfff42008
op_assign
l_int|0
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
l_int|0xfff42004
op_assign
l_int|10000
suffix:semicolon
multiline_comment|/* 10ms */
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
l_int|0xfff42017
op_or_assign
l_int|3
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
l_int|0xfff4201b
op_assign
l_int|0x16
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|MVME16x_IRQ_TIMER
comma
id|mvme16x_timer_int
comma
l_int|0
comma
l_string|&quot;timer&quot;
comma
id|mvme16x_timer_int
)paren
)paren
id|panic
(paren
l_string|&quot;Couldn&squot;t register timer int&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;brdno
op_eq
l_int|0x0162
op_logical_or
id|p-&gt;brdno
op_eq
l_int|0x172
)paren
id|irq
op_assign
id|MVME162_IRQ_ABORT
suffix:semicolon
r_else
id|irq
op_assign
id|MVME167_IRQ_ABORT
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|irq
comma
id|mvme16x_abort_int
comma
l_int|0
comma
l_string|&quot;abort&quot;
comma
id|mvme16x_abort_int
)paren
)paren
id|panic
(paren
l_string|&quot;Couldn&squot;t register abort int&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* This is always executed with interrupts disabled.  */
DECL|function|mvme16x_gettimeoffset
r_int
r_int
id|mvme16x_gettimeoffset
(paren
r_void
)paren
(brace
r_return
(paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
l_int|0xfff42008
)paren
suffix:semicolon
)brace
DECL|function|bcd2int
r_int
id|bcd2int
(paren
r_int
r_char
id|b
)paren
(brace
r_return
(paren
(paren
id|b
op_rshift
l_int|4
)paren
op_star
l_int|10
op_plus
(paren
id|b
op_amp
l_int|15
)paren
)paren
suffix:semicolon
)brace
DECL|function|mvme16x_hwclk
r_int
id|mvme16x_hwclk
c_func
(paren
r_int
id|op
comma
r_struct
id|rtc_time
op_star
id|t
)paren
(brace
macro_line|#warning check me!
r_if
c_cond
(paren
op_logical_neg
id|op
)paren
(brace
id|rtc-&gt;ctrl
op_assign
id|RTC_READ
suffix:semicolon
id|t-&gt;tm_year
op_assign
id|bcd2int
(paren
id|rtc-&gt;bcd_year
)paren
suffix:semicolon
id|t-&gt;tm_mon
op_assign
id|bcd2int
(paren
id|rtc-&gt;bcd_mth
)paren
suffix:semicolon
id|t-&gt;tm_mday
op_assign
id|bcd2int
(paren
id|rtc-&gt;bcd_dom
)paren
suffix:semicolon
id|t-&gt;tm_hour
op_assign
id|bcd2int
(paren
id|rtc-&gt;bcd_hr
)paren
suffix:semicolon
id|t-&gt;tm_min
op_assign
id|bcd2int
(paren
id|rtc-&gt;bcd_min
)paren
suffix:semicolon
id|t-&gt;tm_sec
op_assign
id|bcd2int
(paren
id|rtc-&gt;bcd_sec
)paren
suffix:semicolon
id|rtc-&gt;ctrl
op_assign
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mvme16x_set_clock_mmss
r_int
id|mvme16x_set_clock_mmss
(paren
r_int
r_int
id|nowtime
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mvme16x_keyb_init
r_int
id|mvme16x_keyb_init
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
eof
