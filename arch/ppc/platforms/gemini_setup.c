multiline_comment|/*&n; *  arch/ppc/platforms/gemini_setup.c&n; *&n; *  Copyright (C) 1995 Linus Torvalds&n; *  Adapted from &squot;alpha&squot; version by Gary Thomas&n; *  Modified by Cort Dougan (cort@cs.nmt.edu)&n; *  Synergy Microsystems board support by Dan Cox (dan@synergymicro.com)&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/m48t35.h&gt;
macro_line|#include &lt;platforms/gemini.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/open_pic.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
r_void
id|gemini_find_bridges
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|gemini_get_clock_speed
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|gemini_pcibios_fixup
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|gemini_board_families
r_static
r_char
op_star
id|gemini_board_families
(braket
)braket
op_assign
(brace
l_string|&quot;VGM&quot;
comma
l_string|&quot;VSS&quot;
comma
l_string|&quot;KGM&quot;
comma
l_string|&quot;VGR&quot;
comma
l_string|&quot;VCM&quot;
comma
l_string|&quot;VCS&quot;
comma
l_string|&quot;KCM&quot;
comma
l_string|&quot;VCR&quot;
)brace
suffix:semicolon
DECL|variable|gemini_board_count
r_static
r_int
id|gemini_board_count
op_assign
r_sizeof
(paren
id|gemini_board_families
)paren
op_div
r_sizeof
(paren
id|gemini_board_families
(braket
l_int|0
)braket
)paren
suffix:semicolon
DECL|variable|cpu_7xx
r_static
r_int
r_int
id|cpu_7xx
(braket
l_int|16
)braket
op_assign
(brace
l_int|0
comma
l_int|15
comma
l_int|14
comma
l_int|0
comma
l_int|0
comma
l_int|13
comma
l_int|5
comma
l_int|9
comma
l_int|6
comma
l_int|11
comma
l_int|8
comma
l_int|10
comma
l_int|16
comma
l_int|12
comma
l_int|7
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|cpu_6xx
r_static
r_int
r_int
id|cpu_6xx
(braket
l_int|16
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|14
comma
l_int|0
comma
l_int|0
comma
l_int|13
comma
l_int|5
comma
l_int|9
comma
l_int|6
comma
l_int|11
comma
l_int|8
comma
l_int|10
comma
l_int|0
comma
l_int|12
comma
l_int|7
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/*&n; * prom_init is the Gemini version of prom.c:prom_init.  We only need&n; * the BSS clearing code, so I copied that out of prom.c.  This is a&n; * lot simpler than hacking prom.c so it will build with Gemini. -VAL&n; */
DECL|macro|PTRRELOC
mdefine_line|#define PTRRELOC(x)&t;((typeof(x))((unsigned long)(x) + offset))
r_int
r_int
DECL|function|prom_init
id|prom_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|offset
op_assign
id|reloc_offset
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
id|phys
suffix:semicolon
r_extern
r_char
id|__bss_start
comma
id|_end
suffix:semicolon
multiline_comment|/* First zero the BSS -- use memset, some arches don&squot;t have&n;&t; * caches on yet */
id|memset_io
c_func
(paren
id|PTRRELOC
c_func
(paren
op_amp
id|__bss_start
)paren
comma
l_int|0
comma
op_amp
id|_end
op_minus
op_amp
id|__bss_start
)paren
suffix:semicolon
multiline_comment|/* Default */
id|phys
op_assign
id|offset
op_plus
id|KERNELBASE
suffix:semicolon
id|gemini_prom_init
c_func
(paren
)paren
suffix:semicolon
r_return
id|phys
suffix:semicolon
)brace
r_int
DECL|function|gemini_show_cpuinfo
id|gemini_show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
r_int
r_char
id|reg
comma
id|rev
suffix:semicolon
r_char
op_star
id|family
suffix:semicolon
r_int
r_int
id|type
suffix:semicolon
id|reg
op_assign
id|readb
c_func
(paren
id|GEMINI_FEAT
)paren
suffix:semicolon
id|family
op_assign
id|gemini_board_families
(braket
(paren
(paren
id|reg
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|reg
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
)paren
OG
id|gemini_board_count
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cpuinfo(): unable to determine board family&bslash;n&quot;
)paren
suffix:semicolon
id|reg
op_assign
id|readb
c_func
(paren
id|GEMINI_BREV
)paren
suffix:semicolon
id|type
op_assign
(paren
id|reg
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
suffix:semicolon
id|rev
op_assign
id|reg
op_amp
l_int|0xf
suffix:semicolon
id|reg
op_assign
id|readb
c_func
(paren
id|GEMINI_BECO
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;machine&bslash;t&bslash;t: Gemini %s%d, rev %c, eco %d&bslash;n&quot;
comma
id|family
comma
id|type
comma
(paren
id|rev
op_plus
l_char|&squot;A&squot;
)paren
comma
(paren
id|reg
op_amp
l_int|0xf
)paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;board&bslash;t&bslash;t: Gemini %s&quot;
comma
id|family
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
OG
l_int|9
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%c&quot;
comma
(paren
id|type
op_minus
l_int|10
)paren
op_plus
l_char|&squot;A&squot;
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%d&quot;
comma
id|type
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;, rev %c, eco %d&bslash;n&quot;
comma
(paren
id|rev
op_plus
l_char|&squot;A&squot;
)paren
comma
(paren
id|reg
op_amp
l_int|0xf
)paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;clock&bslash;t&bslash;t: %dMhz&bslash;n&quot;
comma
id|gemini_get_clock_speed
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|gemini_openpic_initsenses
r_static
id|u_char
id|gemini_openpic_initsenses
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
multiline_comment|/* remainder are level-triggered */
)brace
suffix:semicolon
DECL|macro|GEMINI_MPIC_ADDR
mdefine_line|#define GEMINI_MPIC_ADDR (0xfcfc0000)
DECL|macro|GEMINI_MPIC_PCI_CFG
mdefine_line|#define GEMINI_MPIC_PCI_CFG (0x80005800)
DECL|function|gemini_openpic_init
r_void
id|__init
id|gemini_openpic_init
c_func
(paren
r_void
)paren
(brace
id|OpenPIC_Addr
op_assign
(paren
r_volatile
r_struct
id|OpenPIC
op_star
)paren
id|grackle_read
c_func
(paren
id|GEMINI_MPIC_PCI_CFG
op_plus
l_int|0x10
)paren
suffix:semicolon
id|OpenPIC_InitSenses
op_assign
id|gemini_openpic_initsenses
suffix:semicolon
id|OpenPIC_NumInitSenses
op_assign
r_sizeof
(paren
id|gemini_openpic_initsenses
)paren
suffix:semicolon
id|ioremap
c_func
(paren
id|GEMINI_MPIC_ADDR
comma
id|OPENPIC_SIZE
)paren
suffix:semicolon
)brace
r_extern
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
r_extern
r_int
id|root_mountflags
suffix:semicolon
r_extern
r_char
id|cmd_line
(braket
)braket
suffix:semicolon
r_void
DECL|function|gemini_heartbeat
id|gemini_heartbeat
c_func
(paren
r_void
)paren
(brace
r_static
r_int
r_int
id|led
op_assign
id|GEMINI_LEDBASE
op_plus
(paren
l_int|4
op_star
l_int|8
)paren
suffix:semicolon
r_static
r_char
id|direction
op_assign
l_int|8
suffix:semicolon
multiline_comment|/* We only want to do this on 1 CPU */
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
r_return
suffix:semicolon
op_star
(paren
r_char
op_star
)paren
id|led
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|led
op_plus
id|direction
)paren
OG
(paren
id|GEMINI_LEDBASE
op_plus
(paren
l_int|7
op_star
l_int|8
)paren
)paren
op_logical_or
(paren
id|led
op_plus
id|direction
)paren
OL
(paren
id|GEMINI_LEDBASE
op_plus
(paren
l_int|4
op_star
l_int|8
)paren
)paren
)paren
id|direction
op_mul_assign
op_minus
l_int|1
suffix:semicolon
id|led
op_add_assign
id|direction
suffix:semicolon
op_star
(paren
r_char
op_star
)paren
id|led
op_assign
l_int|0xff
suffix:semicolon
id|ppc_md.heartbeat_count
op_assign
id|ppc_md.heartbeat_reset
suffix:semicolon
)brace
DECL|function|gemini_setup_arch
r_void
id|__init
id|gemini_setup_arch
c_func
(paren
r_void
)paren
(brace
r_extern
r_char
id|cmd_line
(braket
)braket
suffix:semicolon
id|loops_per_jiffy
op_assign
l_int|50000000
op_div
id|HZ
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
multiline_comment|/* bootable off CDROM */
r_if
c_cond
(paren
id|initrd_start
)paren
id|ROOT_DEV
op_assign
id|Root_SR0
suffix:semicolon
r_else
macro_line|#endif
id|ROOT_DEV
op_assign
id|Root_SDA1
suffix:semicolon
multiline_comment|/* nothing but serial consoles... */
id|sprintf
c_func
(paren
id|cmd_line
comma
l_string|&quot;%s console=ttyS0&quot;
comma
id|cmd_line
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Boot arguments: %s&bslash;n&quot;
comma
id|cmd_line
)paren
suffix:semicolon
id|ppc_md.heartbeat
op_assign
id|gemini_heartbeat
suffix:semicolon
id|ppc_md.heartbeat_reset
op_assign
id|HZ
op_div
l_int|8
suffix:semicolon
id|ppc_md.heartbeat_count
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Lookup PCI hosts */
id|gemini_find_bridges
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* take special pains to map the MPIC, since it isn&squot;t mapped yet */
id|gemini_openpic_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* start the L2 */
id|gemini_init_l2
c_func
(paren
)paren
suffix:semicolon
)brace
r_int
DECL|function|gemini_get_clock_speed
id|gemini_get_clock_speed
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|hid1
comma
id|pvr
suffix:semicolon
r_int
id|clock
suffix:semicolon
id|pvr
op_assign
id|mfspr
c_func
(paren
id|PVR
)paren
suffix:semicolon
id|hid1
op_assign
(paren
id|mfspr
c_func
(paren
id|HID1
)paren
op_rshift
l_int|28
)paren
op_amp
l_int|0xf
suffix:semicolon
r_if
c_cond
(paren
id|PVR_VER
c_func
(paren
id|pvr
)paren
op_eq
l_int|8
op_logical_or
id|PVR_VER
c_func
(paren
id|pvr
)paren
op_eq
l_int|12
)paren
id|hid1
op_assign
id|cpu_7xx
(braket
id|hid1
)braket
suffix:semicolon
r_else
id|hid1
op_assign
id|cpu_6xx
(braket
id|hid1
)braket
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|readb
c_func
(paren
id|GEMINI_BSTAT
)paren
op_amp
l_int|0xc
)paren
op_rshift
l_int|2
)paren
(brace
r_case
l_int|0
suffix:colon
r_default
suffix:colon
id|clock
op_assign
(paren
id|hid1
op_star
l_int|100
)paren
op_div
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|clock
op_assign
(paren
id|hid1
op_star
l_int|125
)paren
op_div
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|clock
op_assign
(paren
id|hid1
op_star
l_int|50
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|clock
suffix:semicolon
)brace
DECL|function|gemini_init_l2
r_void
id|__init
id|gemini_init_l2
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|reg
comma
id|brev
comma
id|fam
comma
id|creg
suffix:semicolon
r_int
r_int
id|cache
suffix:semicolon
r_int
r_int
id|pvr
suffix:semicolon
id|reg
op_assign
id|readb
c_func
(paren
id|GEMINI_L2CFG
)paren
suffix:semicolon
id|brev
op_assign
id|readb
c_func
(paren
id|GEMINI_BREV
)paren
suffix:semicolon
id|fam
op_assign
id|readb
c_func
(paren
id|GEMINI_FEAT
)paren
suffix:semicolon
id|pvr
op_assign
id|mfspr
c_func
(paren
id|PVR
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|PVR_VER
c_func
(paren
id|pvr
)paren
)paren
(brace
r_case
l_int|8
suffix:colon
r_if
c_cond
(paren
id|reg
op_amp
l_int|0xc0
)paren
id|cache
op_assign
(paren
(paren
(paren
id|reg
op_rshift
l_int|6
)paren
op_amp
l_int|0x3
)paren
op_lshift
l_int|28
)paren
suffix:semicolon
r_else
id|cache
op_assign
l_int|0x3
op_lshift
l_int|28
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* Pre-3.0 processor revs had snooping errata.  Leave&n;                   their L2&squot;s disabled with SMP. -- Dan */
r_if
c_cond
(paren
id|PVR_CFG
c_func
(paren
id|pvr
)paren
OL
l_int|3
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Pre-3.0 750; L2 left disabled!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SMP */
multiline_comment|/* Special case: VGM5-B&squot;s came before L2 ratios were set on&n;                   the board.  Processor speed shouldn&squot;t be too high, so&n;                   set L2 ratio to 1:1.5.  */
r_if
c_cond
(paren
(paren
id|brev
op_eq
l_int|0x51
)paren
op_logical_and
(paren
(paren
id|fam
op_amp
l_int|0xa0
)paren
op_rshift
l_int|4
)paren
op_eq
l_int|0
)paren
id|reg
op_or_assign
l_int|1
suffix:semicolon
multiline_comment|/* determine best cache ratio based upon what the board&n;                   tells us (which sometimes _may_ not be true) and&n;                   the processor speed. */
r_else
(brace
r_if
c_cond
(paren
id|gemini_get_clock_speed
c_func
(paren
)paren
OG
l_int|250
)paren
id|reg
op_assign
l_int|2
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|12
suffix:colon
(brace
r_static
r_int
r_int
id|l2_size_val
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|l2_size_val
)paren
id|l2_size_val
op_assign
id|_get_L2CR
c_func
(paren
)paren
suffix:semicolon
id|cache
op_assign
id|l2_size_val
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
l_int|4
suffix:colon
r_case
l_int|9
suffix:colon
id|creg
op_assign
id|readb
c_func
(paren
id|GEMINI_CPUSTAT
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|creg
op_amp
l_int|0xc
)paren
op_rshift
l_int|2
)paren
op_ne
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;Dual-604 boards don&squot;t support the use of L2&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|writeb
c_func
(paren
l_int|1
comma
id|GEMINI_L2CFG
)paren
suffix:semicolon
r_return
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Unknown processor; L2 left disabled&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cache
op_or_assign
(paren
(paren
l_int|1
op_lshift
id|reg
)paren
op_lshift
l_int|25
)paren
suffix:semicolon
id|cache
op_or_assign
(paren
id|L2CR_L2RAM_MASK
op_or
id|L2CR_L2CTL
op_or
id|L2CR_L2DO
)paren
suffix:semicolon
id|_set_L2CR
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|_set_L2CR
c_func
(paren
id|cache
op_or
id|L2CR_L2E
)paren
suffix:semicolon
)brace
r_void
DECL|function|gemini_restart
id|gemini_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* make a clean restart, not via the MPIC */
id|_gemini_reboot
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
suffix:semicolon
)brace
)brace
r_void
DECL|function|gemini_power_off
id|gemini_power_off
c_func
(paren
r_void
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
suffix:semicolon
)brace
)brace
r_void
DECL|function|gemini_halt
id|gemini_halt
c_func
(paren
r_void
)paren
(brace
id|gemini_restart
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|gemini_init_IRQ
r_void
id|__init
id|gemini_init_IRQ
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* gemini has no 8259 */
id|openpic_init
c_func
(paren
l_int|1
comma
l_int|0
comma
l_int|0
comma
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|macro|gemini_rtc_read
mdefine_line|#define gemini_rtc_read(x)       (readb(GEMINI_RTC+(x)))
DECL|macro|gemini_rtc_write
mdefine_line|#define gemini_rtc_write(val,x)  (writeb((val),(GEMINI_RTC+(x))))
multiline_comment|/* ensure that the RTC is up and running */
DECL|function|gemini_time_init
r_int
id|__init
id|gemini_time_init
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|reg
suffix:semicolon
id|reg
op_assign
id|gemini_rtc_read
c_func
(paren
id|M48T35_RTC_CONTROL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_amp
id|M48T35_RTC_STOPPED
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;M48T35 real-time-clock was stopped. Now starting...&bslash;n&quot;
)paren
suffix:semicolon
id|gemini_rtc_write
c_func
(paren
(paren
id|reg
op_amp
op_complement
(paren
id|M48T35_RTC_STOPPED
)paren
)paren
comma
id|M48T35_RTC_CONTROL
)paren
suffix:semicolon
id|gemini_rtc_write
c_func
(paren
(paren
id|reg
op_or
id|M48T35_RTC_SET
)paren
comma
id|M48T35_RTC_CONTROL
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|DEBUG_RTC
macro_line|#undef DEBUG_RTC
r_int
r_int
DECL|function|gemini_get_rtc_time
id|gemini_get_rtc_time
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|year
comma
id|mon
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
suffix:semicolon
r_int
r_char
id|reg
suffix:semicolon
id|reg
op_assign
id|gemini_rtc_read
c_func
(paren
id|M48T35_RTC_CONTROL
)paren
suffix:semicolon
id|gemini_rtc_write
c_func
(paren
(paren
id|reg
op_or
id|M48T35_RTC_READ
)paren
comma
id|M48T35_RTC_CONTROL
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_RTC
id|printk
c_func
(paren
l_string|&quot;get rtc: reg = %x&bslash;n&quot;
comma
id|reg
)paren
suffix:semicolon
macro_line|#endif
r_do
(brace
id|sec
op_assign
id|gemini_rtc_read
c_func
(paren
id|M48T35_RTC_SECONDS
)paren
suffix:semicolon
id|min
op_assign
id|gemini_rtc_read
c_func
(paren
id|M48T35_RTC_MINUTES
)paren
suffix:semicolon
id|hour
op_assign
id|gemini_rtc_read
c_func
(paren
id|M48T35_RTC_HOURS
)paren
suffix:semicolon
id|day
op_assign
id|gemini_rtc_read
c_func
(paren
id|M48T35_RTC_DOM
)paren
suffix:semicolon
id|mon
op_assign
id|gemini_rtc_read
c_func
(paren
id|M48T35_RTC_MONTH
)paren
suffix:semicolon
id|year
op_assign
id|gemini_rtc_read
c_func
(paren
id|M48T35_RTC_YEAR
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|sec
op_ne
id|gemini_rtc_read
c_func
(paren
id|M48T35_RTC_SECONDS
)paren
)paren
(brace
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_RTC
id|printk
c_func
(paren
l_string|&quot;get rtc: sec=%x, min=%x, hour=%x, day=%x, mon=%x, year=%x&bslash;n&quot;
comma
id|sec
comma
id|min
comma
id|hour
comma
id|day
comma
id|mon
comma
id|year
)paren
suffix:semicolon
macro_line|#endif
id|gemini_rtc_write
c_func
(paren
id|reg
comma
id|M48T35_RTC_CONTROL
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|sec
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|min
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|hour
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|day
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|mon
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|year
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|year
op_add_assign
l_int|1900
)paren
OL
l_int|1970
)paren
id|year
op_add_assign
l_int|100
suffix:semicolon
macro_line|#ifdef DEBUG_RTC
id|printk
c_func
(paren
l_string|&quot;get rtc: sec=%x, min=%x, hour=%x, day=%x, mon=%x, year=%x&bslash;n&quot;
comma
id|sec
comma
id|min
comma
id|hour
comma
id|day
comma
id|mon
comma
id|year
)paren
suffix:semicolon
macro_line|#endif
r_return
id|mktime
c_func
(paren
id|year
comma
id|mon
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
)paren
suffix:semicolon
)brace
r_int
DECL|function|gemini_set_rtc_time
id|gemini_set_rtc_time
c_func
(paren
r_int
r_int
id|now
)paren
(brace
r_int
r_char
id|reg
suffix:semicolon
r_struct
id|rtc_time
id|tm
suffix:semicolon
id|to_tm
c_func
(paren
id|now
comma
op_amp
id|tm
)paren
suffix:semicolon
id|reg
op_assign
id|gemini_rtc_read
c_func
(paren
id|M48T35_RTC_CONTROL
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_RTC
id|printk
c_func
(paren
l_string|&quot;set rtc: reg = %x&bslash;n&quot;
comma
id|reg
)paren
suffix:semicolon
macro_line|#endif
id|gemini_rtc_write
c_func
(paren
(paren
id|reg
op_or
id|M48T35_RTC_SET
)paren
comma
id|M48T35_RTC_CONTROL
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_RTC
id|printk
c_func
(paren
l_string|&quot;set rtc: tm vals - sec=%x, min=%x, hour=%x, mon=%x, mday=%x, year=%x&bslash;n&quot;
comma
id|tm.tm_sec
comma
id|tm.tm_min
comma
id|tm.tm_hour
comma
id|tm.tm_mon
comma
id|tm.tm_mday
comma
id|tm.tm_year
)paren
suffix:semicolon
macro_line|#endif
id|tm.tm_year
op_sub_assign
l_int|1900
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_sec
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_min
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_hour
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_mon
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_mday
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|tm.tm_year
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_RTC
id|printk
c_func
(paren
l_string|&quot;set rtc: tm vals - sec=%x, min=%x, hour=%x, mon=%x, mday=%x, year=%x&bslash;n&quot;
comma
id|tm.tm_sec
comma
id|tm.tm_min
comma
id|tm.tm_hour
comma
id|tm.tm_mon
comma
id|tm.tm_mday
comma
id|tm.tm_year
)paren
suffix:semicolon
macro_line|#endif
id|gemini_rtc_write
c_func
(paren
id|tm.tm_sec
comma
id|M48T35_RTC_SECONDS
)paren
suffix:semicolon
id|gemini_rtc_write
c_func
(paren
id|tm.tm_min
comma
id|M48T35_RTC_MINUTES
)paren
suffix:semicolon
id|gemini_rtc_write
c_func
(paren
id|tm.tm_hour
comma
id|M48T35_RTC_HOURS
)paren
suffix:semicolon
id|gemini_rtc_write
c_func
(paren
id|tm.tm_mday
comma
id|M48T35_RTC_DOM
)paren
suffix:semicolon
id|gemini_rtc_write
c_func
(paren
id|tm.tm_mon
comma
id|M48T35_RTC_MONTH
)paren
suffix:semicolon
id|gemini_rtc_write
c_func
(paren
id|tm.tm_year
comma
id|M48T35_RTC_YEAR
)paren
suffix:semicolon
multiline_comment|/* done writing */
id|gemini_rtc_write
c_func
(paren
id|reg
comma
id|M48T35_RTC_CONTROL
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|time_state
op_eq
id|TIME_ERROR
)paren
op_logical_or
(paren
id|time_state
op_eq
id|TIME_BAD
)paren
)paren
id|time_state
op_assign
id|TIME_OK
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*  use the RTC to determine the decrementer count */
DECL|function|gemini_calibrate_decr
r_void
id|__init
id|gemini_calibrate_decr
c_func
(paren
r_void
)paren
(brace
r_int
id|freq
comma
id|divisor
suffix:semicolon
r_int
r_char
id|reg
suffix:semicolon
multiline_comment|/* determine processor bus speed */
id|reg
op_assign
id|readb
c_func
(paren
id|GEMINI_BSTAT
)paren
suffix:semicolon
r_switch
c_cond
(paren
(paren
(paren
id|reg
op_amp
l_int|0x0c
)paren
op_rshift
l_int|2
)paren
op_amp
l_int|0x3
)paren
(brace
r_case
l_int|0
suffix:colon
r_default
suffix:colon
id|freq
op_assign
l_int|66667
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|freq
op_assign
l_int|83000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|freq
op_assign
l_int|100000
suffix:semicolon
r_break
suffix:semicolon
)brace
id|freq
op_mul_assign
l_int|1000
suffix:semicolon
id|divisor
op_assign
l_int|4
suffix:semicolon
id|tb_ticks_per_jiffy
op_assign
id|freq
op_div
id|HZ
op_div
id|divisor
suffix:semicolon
id|tb_to_us
op_assign
id|mulhwu_scale_factor
c_func
(paren
id|freq
op_div
id|divisor
comma
l_int|1000000
)paren
suffix:semicolon
)brace
DECL|function|gemini_find_end_of_memory
r_int
r_int
id|__init
id|gemini_find_end_of_memory
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|total
suffix:semicolon
r_int
r_char
id|reg
suffix:semicolon
id|reg
op_assign
id|readb
c_func
(paren
id|GEMINI_MEMCFG
)paren
suffix:semicolon
id|total
op_assign
(paren
(paren
l_int|1
op_lshift
(paren
(paren
id|reg
op_amp
l_int|0x7
)paren
op_minus
l_int|1
)paren
)paren
op_star
(paren
l_int|8
op_lshift
(paren
(paren
id|reg
op_rshift
l_int|3
)paren
op_amp
l_int|0x7
)paren
)paren
)paren
suffix:semicolon
id|total
op_mul_assign
(paren
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
r_return
id|total
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|gemini_map_io
id|gemini_map_io
c_func
(paren
r_void
)paren
(brace
id|io_block_mapping
c_func
(paren
l_int|0xf0000000
comma
l_int|0xf0000000
comma
l_int|0x10000000
comma
id|_PAGE_IO
)paren
suffix:semicolon
id|io_block_mapping
c_func
(paren
l_int|0x80000000
comma
l_int|0x80000000
comma
l_int|0x10000000
comma
id|_PAGE_IO
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
r_static
r_int
DECL|function|smp_gemini_probe
id|smp_gemini_probe
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|nr
suffix:semicolon
id|nr
op_assign
(paren
id|readb
c_func
(paren
id|GEMINI_CPUSTAT
)paren
op_amp
id|GEMINI_CPU_COUNT_MASK
)paren
op_rshift
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_eq
l_int|0
)paren
id|nr
op_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|nr
OG
l_int|1
)paren
(brace
id|openpic_request_IPIs
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|nr
suffix:semicolon
op_increment
id|i
)paren
id|smp_hw_index
(braket
id|i
)braket
op_assign
id|i
suffix:semicolon
)brace
r_return
id|nr
suffix:semicolon
)brace
r_static
r_void
DECL|function|smp_gemini_kick_cpu
id|smp_gemini_kick_cpu
c_func
(paren
r_int
id|nr
)paren
(brace
id|openpic_reset_processor_phys
c_func
(paren
l_int|1
op_lshift
id|nr
)paren
suffix:semicolon
id|openpic_reset_processor_phys
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|smp_gemini_setup_cpu
id|smp_gemini_setup_cpu
c_func
(paren
r_int
id|cpu_nr
)paren
(brace
r_if
c_cond
(paren
id|OpenPIC_Addr
)paren
id|do_openpic_setup_cpu
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_nr
OG
l_int|0
)paren
id|gemini_init_l2
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|gemini_smp_ops
r_static
r_struct
id|smp_ops_t
id|gemini_smp_ops
op_assign
(brace
id|smp_openpic_message_pass
comma
id|smp_gemini_probe
comma
id|smp_gemini_kick_cpu
comma
id|smp_gemini_setup_cpu
comma
dot
id|give_timebase
op_assign
id|smp_generic_give_timebase
comma
dot
id|take_timebase
op_assign
id|smp_generic_take_timebase
comma
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
DECL|function|platform_init
r_void
id|__init
id|platform_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Restore BATs for now */
id|mtspr
c_func
(paren
id|DBAT3U
comma
l_int|0xf0001fff
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|DBAT3L
comma
l_int|0xf000002a
)paren
suffix:semicolon
id|parse_bootinfo
c_func
(paren
id|find_bootinfo
c_func
(paren
)paren
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
id|GEMINI_LEDS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|gemini_led_off
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
id|ISA_DMA_THRESHOLD
op_assign
l_int|0
suffix:semicolon
id|DMA_MODE_READ
op_assign
l_int|0
suffix:semicolon
id|DMA_MODE_WRITE
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|r4
)paren
(brace
id|initrd_start
op_assign
id|r4
op_plus
id|KERNELBASE
suffix:semicolon
id|initrd_end
op_assign
id|r5
op_plus
id|KERNELBASE
suffix:semicolon
)brace
macro_line|#endif
id|ppc_md.setup_arch
op_assign
id|gemini_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|gemini_show_cpuinfo
suffix:semicolon
id|ppc_md.irq_canonicalize
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|gemini_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|openpic_get_irq
suffix:semicolon
id|ppc_md.init
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.restart
op_assign
id|gemini_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|gemini_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|gemini_halt
suffix:semicolon
id|ppc_md.time_init
op_assign
id|gemini_time_init
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
id|gemini_set_rtc_time
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
id|gemini_get_rtc_time
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|gemini_calibrate_decr
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|gemini_find_end_of_memory
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|gemini_map_io
suffix:semicolon
id|ppc_md.pcibios_fixup_bus
op_assign
id|gemini_pcibios_fixup
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|ppc_md.smp_ops
op_assign
op_amp
id|gemini_smp_ops
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
)brace
eof
