multiline_comment|/*&n; * arch/ppc/platforms/spruce_setup.c&n; *&n; * Board setup routines for IBM Spruce&n; *&n; * Authors: Johnnie Peters &lt;jpeters@mvista.com&gt;&n; *          Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * 2001-2002 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.1.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;platforms/spruce.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;syslib/cpc700.h&gt;
r_extern
r_void
id|spruce_init_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|spruce_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|spruce_setup_hose
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_char
id|cmd_line
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * CPC700 PIC interrupt programming table&n; *&n; * First entry is the sensitivity (level/edge), second is the polarity.&n; */
DECL|variable|cpc700_irq_assigns
r_int
r_int
id|cpc700_irq_assigns
(braket
l_int|32
)braket
(braket
l_int|2
)braket
op_assign
(brace
(brace
l_int|1
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ  0: ECC Correctable Error - rising edge */
(brace
l_int|1
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ  1: PCI Write Mem Range   - rising edge */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ  2: PCI Write Command Reg - active high */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ  3: UART 0                - active high */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ  4: UART 1                - active high */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ  5: ICC 0                 - active high */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ  6: ICC 1                 - active high */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ  7: GPT Compare 0         - active high */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ  8: GPT Compare 1         - active high */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ  9: GPT Compare 2         - active high */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 10: GPT Compare 3         - active high */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 11: GPT Compare 4         - active high */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 12: GPT Capture 0         - active high */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 13: GPT Capture 1         - active high */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 14: GPT Capture 2         - active high */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 15: GPT Capture 3         - active high */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 16: GPT Capture 4         - active high */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 17: Reserved */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 18: Reserved */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 19: Reserved */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 20: FPGA EXT_IRQ0         - active high */
(brace
l_int|1
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 21: Mouse                 - rising edge */
(brace
l_int|1
comma
l_int|1
)brace
comma
multiline_comment|/* IRQ 22: Keyboard              - rising edge */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 23: PCI Slot 3            - active low */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 24: PCI Slot 2            - active low */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 25: PCI Slot 1            - active low */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IRQ 26: PCI Slot 0            - active low */
)brace
suffix:semicolon
r_static
r_void
id|__init
DECL|function|spruce_calibrate_decr
id|spruce_calibrate_decr
c_func
(paren
r_void
)paren
(brace
r_int
id|freq
comma
id|divisor
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* determine processor bus speed */
id|freq
op_assign
id|SPRUCE_BUS_SPEED
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
r_static
r_int
DECL|function|spruce_show_cpuinfo
id|spruce_show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;vendor&bslash;t&bslash;t: IBM&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;machine&bslash;t&bslash;t: Spruce&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|TODC_ALLOC
c_func
(paren
)paren
suffix:semicolon
r_static
r_void
id|__init
DECL|function|spruce_setup_arch
id|spruce_setup_arch
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Setup TODC access */
id|TODC_INIT
c_func
(paren
id|TODC_TYPE_DS1643
comma
l_int|0
comma
l_int|0
comma
id|SPRUCE_RTC_BASE_ADDR
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* init to some ~sane value until calibrate_delay() runs */
id|loops_per_jiffy
op_assign
l_int|50000000
op_div
id|HZ
suffix:semicolon
multiline_comment|/* Setup PCI host bridge */
id|spruce_setup_hose
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|initrd_start
)paren
id|ROOT_DEV
op_assign
id|Root_RAM0
suffix:semicolon
r_else
macro_line|#endif
macro_line|#ifdef CONFIG_ROOT_NFS
id|ROOT_DEV
op_assign
id|Root_NFS
suffix:semicolon
macro_line|#else
id|ROOT_DEV
op_assign
id|Root_SDA1
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DUMMY_CONSOLE
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
multiline_comment|/* Identify the system */
id|printk
c_func
(paren
l_string|&quot;System Identification: IBM Spruce&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;IBM Spruce port (C) 2001 MontaVista Software, Inc. (source@mvista.com)&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|spruce_restart
id|spruce_restart
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
multiline_comment|/* SRR0 has system reset vector, SRR1 has default MSR value */
multiline_comment|/* rfi restores MSR from SRR1 and sets the PC to the SRR0 value */
id|__asm__
id|__volatile__
(paren
"&quot;&bslash;"
id|n
"&bslash;"
id|lis
l_int|3
comma
l_int|0xfff0
id|ori
l_int|3
comma
l_int|3
comma
l_int|0x0100
id|mtspr
l_int|26
comma
l_int|3
id|li
l_int|3
comma
l_int|0
id|mtspr
l_int|27
comma
l_int|3
id|rfi
"&quot;"
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
r_static
r_void
DECL|function|spruce_power_off
id|spruce_power_off
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
r_static
r_void
DECL|function|spruce_halt
id|spruce_halt
c_func
(paren
r_void
)paren
(brace
id|spruce_restart
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|spruce_map_io
id|spruce_map_io
c_func
(paren
r_void
)paren
(brace
id|io_block_mapping
c_func
(paren
id|SPRUCE_PCI_IO_BASE
comma
id|SPRUCE_PCI_PHY_IO_BASE
comma
l_int|0x08000000
comma
id|_PAGE_IO
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|platform_init
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
id|parse_bootinfo
c_func
(paren
id|find_bootinfo
c_func
(paren
)paren
)paren
suffix:semicolon
id|isa_io_base
op_assign
id|SPRUCE_ISA_IO_BASE
suffix:semicolon
id|pci_dram_offset
op_assign
id|SPRUCE_PCI_SYS_MEM_BASE
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|spruce_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|spruce_show_cpuinfo
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|cpc700_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|cpc700_get_irq
suffix:semicolon
id|ppc_md.setup_io_mappings
op_assign
id|spruce_map_io
suffix:semicolon
id|ppc_md.restart
op_assign
id|spruce_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|spruce_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|spruce_halt
suffix:semicolon
id|ppc_md.time_init
op_assign
id|todc_time_init
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
id|todc_set_rtc_time
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
id|todc_get_rtc_time
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|spruce_calibrate_decr
suffix:semicolon
id|ppc_md.nvram_read_val
op_assign
id|todc_direct_read_val
suffix:semicolon
id|ppc_md.nvram_write_val
op_assign
id|todc_direct_write_val
suffix:semicolon
)brace
eof
