multiline_comment|/*&n; * arch/ppc/platforms/ev64260_setup.c&n; *&n; * Board setup routines for the Marvell/Galileo EV-64260-BP Evaluation Board.&n; *&n; * Author: Mark A. Greer &lt;mgreer@mvista.com&gt;&n; *&n; * 2001 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
multiline_comment|/*&n; * The EV-64260-BP port is the result of hard work from many people from&n; * many companies.  In particular, employees of Marvell/Galileo, Mission&n; * Critical Linux, Xyterra, and MontaVista Software were heavily involved.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#if&t;!defined(CONFIG_GT64260_CONSOLE)
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/gt64260.h&gt;
macro_line|#include &lt;platforms/ev64260.h&gt;
r_extern
r_char
id|cmd_line
(braket
)braket
suffix:semicolon
r_int
r_int
id|ev64260_find_end_of_memory
c_func
(paren
r_void
)paren
suffix:semicolon
id|TODC_ALLOC
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Marvell/Galileo EV-64260-BP Evaluation Board PCI interrupt routing.&n; */
r_static
r_int
id|__init
DECL|function|ev64260_map_irq
id|ev64260_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
r_char
id|idsel
comma
r_int
r_char
id|pin
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|pci_bus_to_hose
c_func
(paren
id|dev-&gt;bus-&gt;number
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hose-&gt;index
op_eq
l_int|0
)paren
(brace
r_static
r_char
id|pci_irq_table
(braket
)braket
(braket
l_int|4
)braket
op_assign
multiline_comment|/*&n;&t;&t; *&t;PCI IDSEL/INTPIN-&gt;INTLINE&n;&t;&t; * &t;   A   B   C   D&n;&t;&t; */
(brace
(brace
l_int|91
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IDSEL 7 - PCI bus 0 */
(brace
l_int|91
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IDSEL 8 - PCI bus 0 */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|7
comma
id|max_idsel
op_assign
l_int|8
comma
id|irqs_per_slot
op_assign
l_int|4
suffix:semicolon
r_return
id|PCI_IRQ_TABLE_LOOKUP
suffix:semicolon
)brace
r_else
(brace
r_static
r_char
id|pci_irq_table
(braket
)braket
(braket
l_int|4
)braket
op_assign
multiline_comment|/*&n;&t;&t; *&t;PCI IDSEL/INTPIN-&gt;INTLINE&n;&t;&t; * &t;   A   B   C   D&n;&t;&t; */
(brace
(brace
l_int|93
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IDSEL 7 - PCI bus 1 */
(brace
l_int|93
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IDSEL 8 - PCI bus 1 */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|7
comma
id|max_idsel
op_assign
l_int|8
comma
id|irqs_per_slot
op_assign
l_int|4
suffix:semicolon
r_return
id|PCI_IRQ_TABLE_LOOKUP
suffix:semicolon
)brace
)brace
r_static
r_void
id|__init
DECL|function|ev64260_setup_bridge
id|ev64260_setup_bridge
c_func
(paren
r_void
)paren
(brace
id|gt64260_bridge_info_t
id|info
suffix:semicolon
r_int
id|window
suffix:semicolon
id|GT64260_BRIDGE_INFO_DEFAULT
c_func
(paren
op_amp
id|info
comma
id|ev64260_find_end_of_memory
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Lookup PCI host bridges */
r_if
c_cond
(paren
id|gt64260_find_bridges
c_func
(paren
id|EV64260_BRIDGE_REG_BASE
comma
op_amp
id|info
comma
id|ev64260_map_irq
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Bridge initialization failed.&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Enabling of PCI internal-vs-external arbitration&n;&t; * is a platform- and errata-dependent decision.&n;&t; */
r_if
c_cond
(paren
id|gt64260_revision
op_eq
id|GT64260
)paren
(brace
multiline_comment|/* FEr#35 */
id|gt_clr_bits
c_func
(paren
id|GT64260_PCI_0_ARBITER_CNTL
comma
(paren
l_int|1
op_lshift
l_int|31
)paren
)paren
suffix:semicolon
id|gt_clr_bits
c_func
(paren
id|GT64260_PCI_1_ARBITER_CNTL
comma
(paren
l_int|1
op_lshift
l_int|31
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|gt64260_revision
op_eq
id|GT64260A
)paren
(brace
id|gt_set_bits
c_func
(paren
id|GT64260_PCI_0_ARBITER_CNTL
comma
(paren
l_int|1
op_lshift
l_int|31
)paren
)paren
suffix:semicolon
id|gt_set_bits
c_func
(paren
id|GT64260_PCI_1_ARBITER_CNTL
comma
(paren
l_int|1
op_lshift
l_int|31
)paren
)paren
suffix:semicolon
multiline_comment|/* Make external GPP interrupts level sensitive */
id|gt_set_bits
c_func
(paren
id|GT64260_COMM_ARBITER_CNTL
comma
(paren
l_int|1
op_lshift
l_int|10
)paren
)paren
suffix:semicolon
multiline_comment|/* Doc Change 9: &gt; 100 MHz so must be set */
id|gt_set_bits
c_func
(paren
id|GT64260_CPU_CONFIG
comma
(paren
l_int|1
op_lshift
l_int|23
)paren
)paren
suffix:semicolon
)brace
id|gt_set_bits
c_func
(paren
id|GT64260_CPU_MASTER_CNTL
comma
(paren
l_int|1
op_lshift
l_int|9
)paren
)paren
suffix:semicolon
multiline_comment|/* Only 1 cpu */
multiline_comment|/* SCS windows not disabled above, disable all but SCS 0 */
r_for
c_loop
(paren
id|window
op_assign
l_int|1
suffix:semicolon
id|window
OL
id|GT64260_CPU_SCS_DECODE_WINDOWS
suffix:semicolon
id|window
op_increment
)paren
(brace
id|gt64260_cpu_scs_set_window
c_func
(paren
id|window
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* Set up windows to RTC/TODC and DUART on device module (CS 1 &amp; 2) */
id|gt64260_cpu_cs_set_window
c_func
(paren
l_int|1
comma
id|EV64260_TODC_BASE
comma
id|EV64260_TODC_LEN
)paren
suffix:semicolon
id|gt64260_cpu_cs_set_window
c_func
(paren
l_int|2
comma
id|EV64260_UART_BASE
comma
id|EV64260_UART_LEN
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The EV-64260-BP uses several Multi-Purpose Pins (MPP) on the 64260&n;&t; * bridge as interrupt inputs (via the General Purpose Ports (GPP)&n;&t; * register).  Need to route the MPP inputs to the GPP and set the&n;&t; * polarity correctly.&n;&t; *&n;&t; * In MPP Control 2 Register&n;&t; *   MPP 21 -&gt; GPP 21 (DUART channel A intr)&n;&t; *   MPP 22 -&gt; GPP 22 (DUART channel B intr)&n;&t; *&n;&t; * In MPP Control 3 Register&n;&t; *   MPP 27 -&gt; GPP 27 (PCI 0 INTA)&n;&t; *   MPP 29 -&gt; GPP 29 (PCI 1 INTA)&n;&t; */
id|gt_clr_bits
c_func
(paren
id|GT64260_MPP_CNTL_2
comma
(paren
(paren
l_int|1
op_lshift
l_int|20
)paren
op_or
(paren
l_int|1
op_lshift
l_int|21
)paren
op_or
(paren
l_int|1
op_lshift
l_int|22
)paren
op_or
(paren
l_int|1
op_lshift
l_int|23
)paren
op_or
(paren
l_int|1
op_lshift
l_int|24
)paren
op_or
(paren
l_int|1
op_lshift
l_int|25
)paren
op_or
(paren
l_int|1
op_lshift
l_int|26
)paren
op_or
(paren
l_int|1
op_lshift
l_int|27
)paren
)paren
)paren
suffix:semicolon
id|gt_clr_bits
c_func
(paren
id|GT64260_MPP_CNTL_3
comma
(paren
(paren
l_int|1
op_lshift
l_int|12
)paren
op_or
(paren
l_int|1
op_lshift
l_int|13
)paren
op_or
(paren
l_int|1
op_lshift
l_int|14
)paren
op_or
(paren
l_int|1
op_lshift
l_int|15
)paren
op_or
(paren
l_int|1
op_lshift
l_int|20
)paren
op_or
(paren
l_int|1
op_lshift
l_int|21
)paren
op_or
(paren
l_int|1
op_lshift
l_int|22
)paren
op_or
(paren
l_int|1
op_lshift
l_int|23
)paren
)paren
)paren
suffix:semicolon
id|gt_write
c_func
(paren
id|GT64260_GPP_LEVEL_CNTL
comma
l_int|0x000002c6
)paren
suffix:semicolon
multiline_comment|/* DUART &amp; PCI interrupts are active low */
id|gt_set_bits
c_func
(paren
id|GT64260_GPP_LEVEL_CNTL
comma
(paren
(paren
l_int|1
op_lshift
l_int|21
)paren
op_or
(paren
l_int|1
op_lshift
l_int|22
)paren
op_or
(paren
l_int|1
op_lshift
l_int|27
)paren
op_or
(paren
l_int|1
op_lshift
l_int|29
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Clear any pending interrupts for these inputs and enable them. */
id|gt_write
c_func
(paren
id|GT64260_GPP_INTR_CAUSE
comma
op_complement
(paren
(paren
l_int|1
op_lshift
l_int|21
)paren
op_or
(paren
l_int|1
op_lshift
l_int|22
)paren
op_or
(paren
l_int|1
op_lshift
l_int|27
)paren
op_or
(paren
l_int|1
op_lshift
l_int|29
)paren
)paren
)paren
suffix:semicolon
id|gt_set_bits
c_func
(paren
id|GT64260_GPP_INTR_MASK
comma
(paren
(paren
l_int|1
op_lshift
l_int|21
)paren
op_or
(paren
l_int|1
op_lshift
l_int|22
)paren
op_or
(paren
l_int|1
op_lshift
l_int|27
)paren
op_or
(paren
l_int|1
op_lshift
l_int|29
)paren
)paren
)paren
suffix:semicolon
id|gt_set_bits
c_func
(paren
id|GT64260_IC_CPU_INTR_MASK_HI
comma
(paren
(paren
l_int|1
op_lshift
l_int|26
)paren
op_or
(paren
l_int|1
op_lshift
l_int|27
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Set MPSC Multiplex RMII */
multiline_comment|/* NOTE: ethernet driver modifies bit 0 and 1 */
id|gt_write
c_func
(paren
id|GT64260_MPP_SERIAL_PORTS_MULTIPLEX
comma
l_int|0x00001102
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|ev64260_setup_arch
id|ev64260_setup_arch
c_func
(paren
r_void
)paren
(brace
macro_line|#if&t;!defined(CONFIG_GT64260_CONSOLE)
r_struct
id|serial_struct
id|serial_req
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;ev64260_setup_arch: enter&quot;
comma
l_int|0
)paren
suffix:semicolon
id|loops_per_jiffy
op_assign
l_int|50000000
op_div
id|HZ
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
macro_line|#ifdef&t;CONFIG_ROOT_NFS
id|ROOT_DEV
op_assign
id|Root_NFS
suffix:semicolon
macro_line|#else
id|ROOT_DEV
op_assign
id|Root_SDA2
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;ev64260_setup_arch: find_bridges&quot;
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set up the L2CR register.&n;&t; * L2 cache was invalidated by bootloader.&n;&t; */
r_switch
c_cond
(paren
id|PVR_VER
c_func
(paren
id|mfspr
c_func
(paren
id|PVR
)paren
)paren
)paren
(brace
r_case
id|PVR_VER
c_func
(paren
id|PVR_750
)paren
suffix:colon
id|_set_L2CR
c_func
(paren
l_int|0xfd100000
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PVR_VER
c_func
(paren
id|PVR_7400
)paren
suffix:colon
r_case
id|PVR_VER
c_func
(paren
id|PVR_7410
)paren
suffix:colon
id|_set_L2CR
c_func
(paren
l_int|0xcd100000
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* case PVR_VER(PVR_7450): */
multiline_comment|/* XXXX WHAT VALUE?? FIXME */
r_break
suffix:semicolon
)brace
id|ev64260_setup_bridge
c_func
(paren
)paren
suffix:semicolon
id|TODC_INIT
c_func
(paren
id|TODC_TYPE_DS1501
comma
l_int|0
comma
l_int|0
comma
id|ioremap
c_func
(paren
id|EV64260_TODC_BASE
comma
l_int|0x20
)paren
comma
l_int|8
)paren
suffix:semicolon
macro_line|#if&t;!defined(CONFIG_GT64260_CONSOLE)
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
id|serial_req.line
op_assign
l_int|0
suffix:semicolon
id|serial_req.baud_base
op_assign
id|BASE_BAUD
suffix:semicolon
id|serial_req.port
op_assign
l_int|0
suffix:semicolon
id|serial_req.irq
op_assign
l_int|85
suffix:semicolon
id|serial_req.flags
op_assign
id|STD_COM_FLAGS
suffix:semicolon
id|serial_req.io_type
op_assign
id|SERIAL_IO_MEM
suffix:semicolon
id|serial_req.iomem_base
op_assign
id|ioremap
c_func
(paren
id|EV64260_SERIAL_0
comma
l_int|0x20
)paren
suffix:semicolon
id|serial_req.iomem_reg_shift
op_assign
l_int|2
suffix:semicolon
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
(brace
id|printk
c_func
(paren
l_string|&quot;Early serial init of port 0 failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Assume early_serial_setup() doesn&squot;t modify serial_req */
id|serial_req.line
op_assign
l_int|1
suffix:semicolon
id|serial_req.port
op_assign
l_int|1
suffix:semicolon
id|serial_req.irq
op_assign
l_int|86
suffix:semicolon
id|serial_req.iomem_base
op_assign
id|ioremap
c_func
(paren
id|EV64260_SERIAL_1
comma
l_int|0x20
)paren
suffix:semicolon
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
(brace
id|printk
c_func
(paren
l_string|&quot;Early serial init of port 1 failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;Marvell/Galileo EV-64260-BP Evaluation Board&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;EV-64260-BP port (C) 2001 MontaVista Software, Inc. (source@mvista.com)&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;ev64260_setup_arch: exit&quot;
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|ev64260_init_irq
id|ev64260_init_irq
c_func
(paren
r_void
)paren
(brace
id|gt64260_init_irq
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gt64260_revision
op_ne
id|GT64260
)paren
(brace
multiline_comment|/* XXXX Kludge--need to fix gt64260_init_irq() interface */
multiline_comment|/* Mark PCI intrs level sensitive */
id|irq_desc
(braket
l_int|91
)braket
dot
id|status
op_or_assign
id|IRQ_LEVEL
suffix:semicolon
id|irq_desc
(braket
l_int|93
)braket
dot
id|status
op_or_assign
id|IRQ_LEVEL
suffix:semicolon
)brace
)brace
r_int
r_int
id|__init
DECL|function|ev64260_find_end_of_memory
id|ev64260_find_end_of_memory
c_func
(paren
r_void
)paren
(brace
r_return
l_int|32
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
multiline_comment|/* XXXX FIXME */
)brace
r_static
r_void
DECL|function|ev64260_reset_board
id|ev64260_reset_board
c_func
(paren
r_void
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Set exception prefix high - to the firmware */
id|_nmask_and_or_msr
c_func
(paren
l_int|0
comma
id|MSR_IP
)paren
suffix:semicolon
multiline_comment|/* XXX FIXME */
id|printk
c_func
(paren
l_string|&quot;XXXX **** trying to reset board ****&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
r_void
DECL|function|ev64260_restart
id|ev64260_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
r_volatile
id|ulong
id|i
op_assign
l_int|10000000
suffix:semicolon
id|ev64260_reset_board
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
OG
l_int|0
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;restart failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|ev64260_halt
id|ev64260_halt
c_func
(paren
r_void
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* NOTREACHED */
)brace
r_static
r_void
DECL|function|ev64260_power_off
id|ev64260_power_off
c_func
(paren
r_void
)paren
(brace
id|ev64260_halt
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* NOTREACHED */
)brace
r_static
r_int
DECL|function|ev64260_show_cpuinfo
id|ev64260_show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
(brace
id|uint
id|pvid
suffix:semicolon
id|pvid
op_assign
id|mfspr
c_func
(paren
id|PVR
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;vendor&bslash;t&bslash;t: Marvell/Galileo&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;machine&bslash;t&bslash;t: EV-64260-BP&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;PVID&bslash;t&bslash;t: 0x%x, vendor: %s&bslash;n&quot;
comma
id|pvid
comma
(paren
id|pvid
op_amp
(paren
l_int|1
op_lshift
l_int|15
)paren
ques
c_cond
l_string|&quot;IBM&quot;
suffix:colon
l_string|&quot;Motorola&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* DS1501 RTC has too much variation to use RTC for calibration */
r_static
r_void
id|__init
DECL|function|ev64260_calibrate_decr
id|ev64260_calibrate_decr
c_func
(paren
r_void
)paren
(brace
id|ulong
id|freq
suffix:semicolon
id|freq
op_assign
l_int|100000000
op_div
l_int|4
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;time_init: decrementer frequency = %lu.%.6lu MHz&bslash;n&quot;
comma
id|freq
op_div
l_int|1000000
comma
id|freq
op_mod
l_int|1000000
)paren
suffix:semicolon
id|tb_ticks_per_jiffy
op_assign
id|freq
op_div
id|HZ
suffix:semicolon
id|tb_to_us
op_assign
id|mulhwu_scale_factor
c_func
(paren
id|freq
comma
l_int|1000000
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_SERIAL_TEXT_DEBUG)
multiline_comment|/*&n; * Set BAT 3 to map 0xf0000000 to end of physical memory space.&n; */
r_static
id|__inline__
r_void
DECL|function|ev64260_set_bat
id|ev64260_set_bat
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|bat3u
comma
id|bat3l
suffix:semicolon
r_static
r_int
id|mapping_set
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mapping_set
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot; lis %0,0xf000&bslash;n &bslash;&n;&t;&t;  ori %1,%0,0x002a&bslash;n &bslash;&n;&t;&t;  ori %0,%0,0x1ffe&bslash;n &bslash;&n;&t;&t;  mtspr 0x21e,%0&bslash;n &bslash;&n;&t;&t;  mtspr 0x21f,%1&bslash;n &bslash;&n;&t;&t;  isync&bslash;n &bslash;&n;&t;&t;  sync &quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|bat3u
)paren
comma
l_string|&quot;=r&quot;
(paren
id|bat3l
)paren
)paren
suffix:semicolon
id|mapping_set
op_assign
l_int|1
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
macro_line|#if !defined(CONFIG_GT64260_CONSOLE)
macro_line|#include &lt;linux/serialP.h&gt;
macro_line|#include &lt;linux/serial_reg.h&gt;
macro_line|#include &lt;asm/serial.h&gt;
DECL|variable|rs_table
r_static
r_struct
id|serial_state
id|rs_table
(braket
id|RS_TABLE_SIZE
)braket
op_assign
(brace
id|SERIAL_PORT_DFNS
multiline_comment|/* Defined in &lt;asm/serial.h&gt; */
)brace
suffix:semicolon
r_static
r_void
DECL|function|ev64260_16550_progress
id|ev64260_16550_progress
c_func
(paren
r_char
op_star
id|s
comma
r_int
r_int
id|hex
)paren
(brace
r_volatile
r_char
id|c
suffix:semicolon
r_volatile
r_int
r_int
id|com_port
suffix:semicolon
id|u16
id|shift
suffix:semicolon
id|com_port
op_assign
id|rs_table
(braket
l_int|0
)braket
dot
id|port
suffix:semicolon
id|shift
op_assign
id|rs_table
(braket
l_int|0
)braket
dot
id|iomem_reg_shift
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|s
op_increment
)paren
op_ne
l_int|0
)paren
(brace
r_while
c_loop
(paren
(paren
op_star
(paren
(paren
r_volatile
r_int
r_char
op_star
)paren
id|com_port
op_plus
(paren
id|UART_LSR
op_lshift
id|shift
)paren
)paren
op_amp
id|UART_LSR_THRE
)paren
op_eq
l_int|0
)paren
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|com_port
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_while
c_loop
(paren
(paren
op_star
(paren
(paren
r_volatile
r_int
r_char
op_star
)paren
id|com_port
op_plus
(paren
id|UART_LSR
op_lshift
id|shift
)paren
)paren
op_amp
id|UART_LSR_THRE
)paren
op_eq
l_int|0
)paren
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|com_port
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
)brace
)brace
multiline_comment|/* Move to next line on */
r_while
c_loop
(paren
(paren
op_star
(paren
(paren
r_volatile
r_int
r_char
op_star
)paren
id|com_port
op_plus
(paren
id|UART_LSR
op_lshift
id|shift
)paren
)paren
op_amp
id|UART_LSR_THRE
)paren
op_eq
l_int|0
)paren
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|com_port
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
(paren
(paren
r_volatile
r_int
r_char
op_star
)paren
id|com_port
op_plus
(paren
id|UART_LSR
op_lshift
id|shift
)paren
)paren
op_amp
id|UART_LSR_THRE
)paren
op_eq
l_int|0
)paren
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|com_port
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif&t;/* !CONFIG_GT64260_CONSOLE */
macro_line|#endif&t;/* CONFIG_SERIAL_TEXT_DEBUG */
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
id|isa_mem_base
op_assign
l_int|0
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|ev64260_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|ev64260_show_cpuinfo
suffix:semicolon
id|ppc_md.irq_canonicalize
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|ev64260_init_irq
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|gt64260_get_irq
suffix:semicolon
id|ppc_md.init
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.restart
op_assign
id|ev64260_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|ev64260_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|ev64260_halt
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|ev64260_find_end_of_memory
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
id|ev64260_calibrate_decr
suffix:semicolon
id|ppc_md.nvram_read_val
op_assign
id|todc_direct_read_val
suffix:semicolon
id|ppc_md.nvram_write_val
op_assign
id|todc_direct_write_val
suffix:semicolon
id|ppc_md.heartbeat
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.heartbeat_reset
op_assign
l_int|0
suffix:semicolon
id|ppc_md.heartbeat_count
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef&t;CONFIG_SERIAL_TEXT_DEBUG
id|ev64260_set_bat
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef&t;CONFIG_GT64260_CONSOLE
id|gt64260_base
op_assign
id|EV64260_BRIDGE_REG_BASE
suffix:semicolon
id|ppc_md.progress
op_assign
id|gt64260_mpsc_progress
suffix:semicolon
multiline_comment|/* embedded UART */
macro_line|#else
id|ppc_md.progress
op_assign
id|ev64260_16550_progress
suffix:semicolon
multiline_comment|/* Dev module DUART */
macro_line|#endif
macro_line|#else&t;/* !CONFIG_SERIAL_TEXT_DEBUG */
id|ppc_md.progress
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif&t;/* CONFIG_SERIAL_TEXT_DEBUG */
r_return
suffix:semicolon
)brace
eof
