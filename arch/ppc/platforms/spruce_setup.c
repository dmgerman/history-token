multiline_comment|/*&n; * arch/ppc/platforms/spruce_setup.c&n; *&n; * Board setup routines for IBM Spruce&n; *&n; * Authors: Johnnie Peters &lt;jpeters@mvista.com&gt;&n; *          Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * 2001-2002 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
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
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
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
macro_line|#include &lt;asm/kgdb.h&gt;
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
r_static
r_void
id|__init
DECL|function|spruce_early_serial_map
id|spruce_early_serial_map
c_func
(paren
r_void
)paren
(brace
id|u32
id|uart_clk
suffix:semicolon
r_struct
id|uart_port
id|serial_req
suffix:semicolon
r_if
c_cond
(paren
id|SPRUCE_UARTCLK_IS_33M
c_func
(paren
id|readb
c_func
(paren
id|SPRUCE_FPGA_REG_A
)paren
)paren
)paren
id|uart_clk
op_assign
id|SPRUCE_BAUD_33M
op_star
l_int|16
suffix:semicolon
r_else
id|uart_clk
op_assign
id|SPRUCE_BAUD_30M
op_star
l_int|16
suffix:semicolon
multiline_comment|/* Setup serial port access */
id|memset
c_func
(paren
op_amp
id|serial_req
comma
l_int|0
comma
r_sizeof
(paren
id|serial_req
)paren
)paren
suffix:semicolon
id|serial_req.uartclk
op_assign
id|uart_clk
suffix:semicolon
id|serial_req.irq
op_assign
id|UART0_INT
suffix:semicolon
id|serial_req.flags
op_assign
id|ASYNC_BOOT_AUTOCONF
op_or
id|ASYNC_SKIP_TEST
suffix:semicolon
id|serial_req.iotype
op_assign
id|SERIAL_IO_MEM
suffix:semicolon
id|serial_req.membase
op_assign
(paren
id|u_char
op_star
)paren
id|UART0_IO_BASE
suffix:semicolon
id|serial_req.regshift
op_assign
l_int|0
suffix:semicolon
macro_line|#if defined(CONFIG_KGDB) || defined(CONFIG_SERIAL_TEXT_DEBUG)
id|gen550_init
c_func
(paren
l_int|0
comma
op_amp
id|serial_req
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SERIAL_8250
r_if
c_cond
(paren
id|early_serial_setup
c_func
(paren
op_amp
id|serial_req
)paren
op_ne
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;Early serial init of port 0 failed&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Assume early_serial_setup() doesn&squot;t modify serial_req */
id|serial_req.line
op_assign
l_int|1
suffix:semicolon
id|serial_req.irq
op_assign
id|UART1_INT
suffix:semicolon
id|serial_req.membase
op_assign
(paren
id|u_char
op_star
)paren
id|UART1_IO_BASE
suffix:semicolon
macro_line|#if defined(CONFIG_KGDB) || defined(CONFIG_SERIAL_TEXT_DEBUG)
id|gen550_init
c_func
(paren
l_int|1
comma
op_amp
id|serial_req
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SERIAL_8250
r_if
c_cond
(paren
id|early_serial_setup
c_func
(paren
op_amp
id|serial_req
)paren
op_ne
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;Early serial init of port 1 failed&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
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
macro_line|#ifdef CONFIG_VT
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
id|KERN_INFO
l_string|&quot;System Identification: IBM Spruce&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Port by MontaVista Software, Inc. (source@mvista.com)&bslash;n&quot;
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
l_string|&quot;&bslash;n&bslash;&n;&t;lis&t;3,0xfff0&t;&bslash;n&bslash;&n;&t;ori&t;3,3,0x0100&t;&bslash;n&bslash;&n;&t;mtspr&t;26,3&t;&t;&bslash;n&bslash;&n;&t;li&t;3,0&t;&t;&bslash;n&bslash;&n;&t;mtspr&t;27,3&t;&t;&bslash;n&bslash;&n;&t;rfi&t;&t;&t;&bslash;n&bslash;&n;&t;&quot;
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
multiline_comment|/*&n; * Set BAT 3 to map 0xf8000000 to end of physical memory space 1-to-1.&n; */
r_static
id|__inline__
r_void
DECL|function|spruce_set_bat
id|spruce_set_bat
c_func
(paren
r_void
)paren
(brace
id|mb
c_func
(paren
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|DBAT1U
comma
l_int|0xf8000ffe
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|DBAT1L
comma
l_int|0xf800002a
)paren
suffix:semicolon
id|mb
c_func
(paren
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
multiline_comment|/* Map in board regs, etc. */
id|spruce_set_bat
c_func
(paren
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
id|spruce_early_serial_map
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SERIAL_TEXT_DEBUG
id|ppc_md.progress
op_assign
id|gen550_progress
suffix:semicolon
macro_line|#endif /* CONFIG_SERIAL_TEXT_DEBUG */
macro_line|#ifdef CONFIG_KGDB
id|ppc_md.kgdb_map_scc
op_assign
id|gen550_kgdb_map_scc
suffix:semicolon
macro_line|#endif
)brace
eof
