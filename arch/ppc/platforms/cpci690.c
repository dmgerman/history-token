multiline_comment|/*&n; * arch/ppc/platforms/cpci690.c&n; *&n; * Board setup routines for the Force CPCI690 board.&n; *&n; * Author: Mark A. Greer &lt;mgreer@mvista.com&gt;&n; *&n; * 2003 (c) MontaVista Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This programr&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;linux/mv643xx.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/mv64x60.h&gt;
macro_line|#include &lt;platforms/cpci690.h&gt;
DECL|macro|BOARD_VENDOR
mdefine_line|#define BOARD_VENDOR&t;&quot;Force&quot;
DECL|macro|BOARD_MACHINE
mdefine_line|#define BOARD_MACHINE&t;&quot;CPCI690&quot;
multiline_comment|/* Set IDE controllers into Native mode? */
DECL|macro|SET_PCI_IDE_NATIVE
mdefine_line|#define SET_PCI_IDE_NATIVE
DECL|variable|bh
r_static
r_struct
id|mv64x60_handle
id|bh
suffix:semicolon
DECL|variable|cpci690_br_base
r_static
id|u32
id|cpci690_br_base
suffix:semicolon
DECL|variable|cpu_7xx
r_static
r_const
r_int
r_int
id|cpu_7xx
(braket
l_int|16
)braket
op_assign
(brace
multiline_comment|/* 7xx &amp; 74xx (but not 745x) */
l_int|18
comma
l_int|15
comma
l_int|14
comma
l_int|2
comma
l_int|4
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
id|TODC_ALLOC
c_func
(paren
)paren
suffix:semicolon
r_static
r_int
id|__init
DECL|function|cpci690_map_irq
id|cpci690_map_irq
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
l_int|90
comma
l_int|91
comma
l_int|88
comma
l_int|89
)brace
comma
multiline_comment|/* IDSEL 30/20 - Sentinel */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|20
comma
id|max_idsel
op_assign
l_int|20
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
l_int|94
comma
l_int|95
comma
l_int|92
)brace
comma
multiline_comment|/* IDSEL 28/18 - PMC slot 2 */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IDSEL 29/19 - Not used */
(brace
l_int|94
comma
l_int|95
comma
l_int|92
comma
l_int|93
)brace
comma
multiline_comment|/* IDSEL 30/20 - PMC slot 1 */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|18
comma
id|max_idsel
op_assign
l_int|20
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
r_int
DECL|function|cpci690_get_cpu_speed
id|cpci690_get_cpu_speed
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|hid1
suffix:semicolon
id|hid1
op_assign
id|mfspr
c_func
(paren
id|SPRN_HID1
)paren
op_rshift
l_int|28
suffix:semicolon
r_return
id|CPCI690_BUS_FREQ
op_star
id|cpu_7xx
(braket
id|hid1
)braket
op_div
l_int|2
suffix:semicolon
)brace
DECL|macro|KB
mdefine_line|#define&t;KB&t;(1024UL)
DECL|macro|MB
mdefine_line|#define&t;MB&t;(1024UL * KB)
DECL|macro|GB
mdefine_line|#define&t;GB&t;(1024UL * MB)
r_int
r_int
id|__init
DECL|function|cpci690_find_end_of_memory
id|cpci690_find_end_of_memory
c_func
(paren
r_void
)paren
(brace
id|u32
id|mem_ctlr_size
suffix:semicolon
r_static
id|u32
id|board_size
suffix:semicolon
r_static
id|u8
id|first_time
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|first_time
)paren
(brace
multiline_comment|/* Using cpci690_set_bat() mapping ==&gt; virt addr == phys addr */
r_switch
c_cond
(paren
id|in_8
c_func
(paren
(paren
id|u8
op_star
)paren
(paren
id|cpci690_br_base
op_plus
id|CPCI690_BR_MEM_CTLR
)paren
)paren
op_amp
l_int|0x07
)paren
(brace
r_case
l_int|0x01
suffix:colon
id|board_size
op_assign
l_int|256
op_star
id|MB
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x02
suffix:colon
id|board_size
op_assign
l_int|512
op_star
id|MB
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x03
suffix:colon
id|board_size
op_assign
l_int|768
op_star
id|MB
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x04
suffix:colon
id|board_size
op_assign
l_int|1
op_star
id|GB
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x05
suffix:colon
id|board_size
op_assign
l_int|1
op_star
id|GB
op_plus
l_int|512
op_star
id|MB
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x06
suffix:colon
id|board_size
op_assign
l_int|2
op_star
id|GB
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|board_size
op_assign
l_int|0xffffffff
suffix:semicolon
multiline_comment|/* use mem ctlr size */
)brace
multiline_comment|/* switch */
id|mem_ctlr_size
op_assign
id|mv64x60_get_mem_size
c_func
(paren
id|CONFIG_MV64X60_NEW_BASE
comma
id|MV64x60_TYPE_GT64260A
)paren
suffix:semicolon
multiline_comment|/* Check that mem ctlr &amp; board reg agree.  If not, pick MIN. */
r_if
c_cond
(paren
id|board_size
op_ne
id|mem_ctlr_size
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Board register &amp; memory controller&quot;
l_string|&quot;mem size disagree (board reg: 0x%lx, &quot;
l_string|&quot;mem ctlr: 0x%lx)&bslash;n&quot;
comma
(paren
id|ulong
)paren
id|board_size
comma
(paren
id|ulong
)paren
id|mem_ctlr_size
)paren
suffix:semicolon
id|board_size
op_assign
id|min
c_func
(paren
id|board_size
comma
id|mem_ctlr_size
)paren
suffix:semicolon
)brace
id|first_time
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* if */
r_return
id|board_size
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|cpci690_setup_bridge
id|cpci690_setup_bridge
c_func
(paren
r_void
)paren
(brace
r_struct
id|mv64x60_setup_info
id|si
suffix:semicolon
r_int
id|i
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|si
comma
l_int|0
comma
r_sizeof
(paren
id|si
)paren
)paren
suffix:semicolon
id|si.phys_reg_base
op_assign
id|CONFIG_MV64X60_NEW_BASE
suffix:semicolon
id|si.pci_0.enable_bus
op_assign
l_int|1
suffix:semicolon
id|si.pci_0.pci_io.cpu_base
op_assign
id|CPCI690_PCI0_IO_START_PROC_ADDR
suffix:semicolon
id|si.pci_0.pci_io.pci_base_hi
op_assign
l_int|0
suffix:semicolon
id|si.pci_0.pci_io.pci_base_lo
op_assign
id|CPCI690_PCI0_IO_START_PCI_ADDR
suffix:semicolon
id|si.pci_0.pci_io.size
op_assign
id|CPCI690_PCI0_IO_SIZE
suffix:semicolon
id|si.pci_0.pci_io.swap
op_assign
id|MV64x60_CPU2PCI_SWAP_NONE
suffix:semicolon
id|si.pci_0.pci_mem
(braket
l_int|0
)braket
dot
id|cpu_base
op_assign
id|CPCI690_PCI0_MEM_START_PROC_ADDR
suffix:semicolon
id|si.pci_0.pci_mem
(braket
l_int|0
)braket
dot
id|pci_base_hi
op_assign
id|CPCI690_PCI0_MEM_START_PCI_HI_ADDR
suffix:semicolon
id|si.pci_0.pci_mem
(braket
l_int|0
)braket
dot
id|pci_base_lo
op_assign
id|CPCI690_PCI0_MEM_START_PCI_LO_ADDR
suffix:semicolon
id|si.pci_0.pci_mem
(braket
l_int|0
)braket
dot
id|size
op_assign
id|CPCI690_PCI0_MEM_SIZE
suffix:semicolon
id|si.pci_0.pci_mem
(braket
l_int|0
)braket
dot
id|swap
op_assign
id|MV64x60_CPU2PCI_SWAP_NONE
suffix:semicolon
id|si.pci_0.pci_cmd_bits
op_assign
l_int|0
suffix:semicolon
id|si.pci_0.latency_timer
op_assign
l_int|0x80
suffix:semicolon
id|si.pci_1.enable_bus
op_assign
l_int|1
suffix:semicolon
id|si.pci_1.pci_io.cpu_base
op_assign
id|CPCI690_PCI1_IO_START_PROC_ADDR
suffix:semicolon
id|si.pci_1.pci_io.pci_base_hi
op_assign
l_int|0
suffix:semicolon
id|si.pci_1.pci_io.pci_base_lo
op_assign
id|CPCI690_PCI1_IO_START_PCI_ADDR
suffix:semicolon
id|si.pci_1.pci_io.size
op_assign
id|CPCI690_PCI1_IO_SIZE
suffix:semicolon
id|si.pci_1.pci_io.swap
op_assign
id|MV64x60_CPU2PCI_SWAP_NONE
suffix:semicolon
id|si.pci_1.pci_mem
(braket
l_int|0
)braket
dot
id|cpu_base
op_assign
id|CPCI690_PCI1_MEM_START_PROC_ADDR
suffix:semicolon
id|si.pci_1.pci_mem
(braket
l_int|0
)braket
dot
id|pci_base_hi
op_assign
id|CPCI690_PCI1_MEM_START_PCI_HI_ADDR
suffix:semicolon
id|si.pci_1.pci_mem
(braket
l_int|0
)braket
dot
id|pci_base_lo
op_assign
id|CPCI690_PCI1_MEM_START_PCI_LO_ADDR
suffix:semicolon
id|si.pci_1.pci_mem
(braket
l_int|0
)braket
dot
id|size
op_assign
id|CPCI690_PCI1_MEM_SIZE
suffix:semicolon
id|si.pci_1.pci_mem
(braket
l_int|0
)braket
dot
id|swap
op_assign
id|MV64x60_CPU2PCI_SWAP_NONE
suffix:semicolon
id|si.pci_1.pci_cmd_bits
op_assign
l_int|0
suffix:semicolon
id|si.pci_1.latency_timer
op_assign
l_int|0x80
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
id|MV64x60_CPU2MEM_WINDOWS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|si.cpu_prot_options
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|si.cpu_snoop_options
(braket
id|i
)braket
op_assign
id|GT64260_CPU_SNOOP_WB
suffix:semicolon
id|si.pci_0.acc_cntl_options
(braket
id|i
)braket
op_assign
id|GT64260_PCI_ACC_CNTL_DREADEN
op_or
id|GT64260_PCI_ACC_CNTL_RDPREFETCH
op_or
id|GT64260_PCI_ACC_CNTL_RDLINEPREFETCH
op_or
id|GT64260_PCI_ACC_CNTL_RDMULPREFETCH
op_or
id|GT64260_PCI_ACC_CNTL_SWAP_NONE
op_or
id|GT64260_PCI_ACC_CNTL_MBURST_32_BTYES
suffix:semicolon
id|si.pci_0.snoop_options
(braket
id|i
)braket
op_assign
id|GT64260_PCI_SNOOP_WB
suffix:semicolon
id|si.pci_1.acc_cntl_options
(braket
id|i
)braket
op_assign
id|GT64260_PCI_ACC_CNTL_DREADEN
op_or
id|GT64260_PCI_ACC_CNTL_RDPREFETCH
op_or
id|GT64260_PCI_ACC_CNTL_RDLINEPREFETCH
op_or
id|GT64260_PCI_ACC_CNTL_RDMULPREFETCH
op_or
id|GT64260_PCI_ACC_CNTL_SWAP_NONE
op_or
id|GT64260_PCI_ACC_CNTL_MBURST_32_BTYES
suffix:semicolon
id|si.pci_1.snoop_options
(braket
id|i
)braket
op_assign
id|GT64260_PCI_SNOOP_WB
suffix:semicolon
)brace
multiline_comment|/* Lookup PCI host bridges */
r_if
c_cond
(paren
id|mv64x60_init
c_func
(paren
op_amp
id|bh
comma
op_amp
id|si
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Bridge initialization failed.&bslash;n&quot;
)paren
suffix:semicolon
id|pci_dram_offset
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* System mem at same addr on PCI &amp; cpu bus */
id|ppc_md.pci_swizzle
op_assign
id|common_swizzle
suffix:semicolon
id|ppc_md.pci_map_irq
op_assign
id|cpci690_map_irq
suffix:semicolon
id|ppc_md.pci_exclude_device
op_assign
id|mv64x60_pci_exclude_device
suffix:semicolon
id|mv64x60_set_bus
c_func
(paren
op_amp
id|bh
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|bh.hose_a-&gt;first_busno
op_assign
l_int|0
suffix:semicolon
id|bh.hose_a-&gt;last_busno
op_assign
l_int|0xff
suffix:semicolon
id|bh.hose_a-&gt;last_busno
op_assign
id|pciauto_bus_scan
c_func
(paren
id|bh.hose_a
comma
l_int|0
)paren
suffix:semicolon
id|bh.hose_b-&gt;first_busno
op_assign
id|bh.hose_a-&gt;last_busno
op_plus
l_int|1
suffix:semicolon
id|mv64x60_set_bus
c_func
(paren
op_amp
id|bh
comma
l_int|1
comma
id|bh.hose_b-&gt;first_busno
)paren
suffix:semicolon
id|bh.hose_b-&gt;last_busno
op_assign
l_int|0xff
suffix:semicolon
id|bh.hose_b-&gt;last_busno
op_assign
id|pciauto_bus_scan
c_func
(paren
id|bh.hose_b
comma
id|bh.hose_b-&gt;first_busno
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|cpci690_setup_peripherals
id|cpci690_setup_peripherals
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Set up windows to CPLD, RTC/TODC, IPMI. */
id|mv64x60_set_32bit_window
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_CPU2DEV_0_WIN
comma
id|CPCI690_BR_BASE
comma
id|CPCI690_BR_SIZE
comma
l_int|0
)paren
suffix:semicolon
id|bh.ci
op_member_access_from_pointer
id|enable_window_32bit
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_CPU2DEV_0_WIN
)paren
suffix:semicolon
id|cpci690_br_base
op_assign
(paren
id|u32
)paren
id|ioremap
c_func
(paren
id|CPCI690_BR_BASE
comma
id|CPCI690_BR_SIZE
)paren
suffix:semicolon
id|mv64x60_set_32bit_window
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_CPU2DEV_1_WIN
comma
id|CPCI690_TODC_BASE
comma
id|CPCI690_TODC_SIZE
comma
l_int|0
)paren
suffix:semicolon
id|bh.ci
op_member_access_from_pointer
id|enable_window_32bit
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_CPU2DEV_1_WIN
)paren
suffix:semicolon
id|TODC_INIT
c_func
(paren
id|TODC_TYPE_MK48T35
comma
l_int|0
comma
l_int|0
comma
id|ioremap
c_func
(paren
id|CPCI690_TODC_BASE
comma
id|CPCI690_TODC_SIZE
)paren
comma
l_int|8
)paren
suffix:semicolon
id|mv64x60_set_32bit_window
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_CPU2DEV_2_WIN
comma
id|CPCI690_IPMI_BASE
comma
id|CPCI690_IPMI_SIZE
comma
l_int|0
)paren
suffix:semicolon
id|bh.ci
op_member_access_from_pointer
id|enable_window_32bit
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_CPU2DEV_2_WIN
)paren
suffix:semicolon
id|mv64x60_set_bits
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_PCI0_ARBITER_CNTL
comma
(paren
l_int|1
op_lshift
l_int|31
)paren
)paren
suffix:semicolon
id|mv64x60_set_bits
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_PCI1_ARBITER_CNTL
comma
(paren
l_int|1
op_lshift
l_int|31
)paren
)paren
suffix:semicolon
id|mv64x60_set_bits
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_CPU_MASTER_CNTL
comma
(paren
l_int|1
op_lshift
l_int|9
)paren
)paren
suffix:semicolon
multiline_comment|/* Only 1 cpu */
multiline_comment|/*&n;&t; * Turn off timer/counters.  Not turning off watchdog timer because&n;&t; * can&squot;t read its reg on the 64260A so don&squot;t know if we&squot;ll be enabling&n;&t; * or disabling.&n;&t; */
id|mv64x60_clr_bits
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_TIMR_CNTR_0_3_CNTL
comma
(paren
(paren
l_int|1
op_lshift
l_int|0
)paren
op_or
(paren
l_int|1
op_lshift
l_int|8
)paren
op_or
(paren
l_int|1
op_lshift
l_int|16
)paren
op_or
(paren
l_int|1
op_lshift
l_int|24
)paren
)paren
)paren
suffix:semicolon
id|mv64x60_clr_bits
c_func
(paren
op_amp
id|bh
comma
id|GT64260_TIMR_CNTR_4_7_CNTL
comma
(paren
(paren
l_int|1
op_lshift
l_int|0
)paren
op_or
(paren
l_int|1
op_lshift
l_int|8
)paren
op_or
(paren
l_int|1
op_lshift
l_int|16
)paren
op_or
(paren
l_int|1
op_lshift
l_int|24
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set MPSC Multiplex RMII&n;&t; * NOTE: ethernet driver modifies bit 0 and 1&n;&t; */
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|GT64260_MPP_SERIAL_PORTS_MULTIPLEX
comma
l_int|0x00001102
)paren
suffix:semicolon
DECL|macro|GPP_EXTERNAL_INTERRUPTS
mdefine_line|#define GPP_EXTERNAL_INTERRUPTS &bslash;&n;&t;&t;((1&lt;&lt;24) | (1&lt;&lt;25) | (1&lt;&lt;26) | (1&lt;&lt;27) | &bslash;&n;&t;&t; (1&lt;&lt;28) | (1&lt;&lt;29) | (1&lt;&lt;30) | (1&lt;&lt;31))
multiline_comment|/* PCI interrupts are inputs */
id|mv64x60_clr_bits
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_GPP_IO_CNTL
comma
id|GPP_EXTERNAL_INTERRUPTS
)paren
suffix:semicolon
multiline_comment|/* PCI interrupts are active low */
id|mv64x60_set_bits
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_GPP_LEVEL_CNTL
comma
id|GPP_EXTERNAL_INTERRUPTS
)paren
suffix:semicolon
multiline_comment|/* Clear any pending interrupts for these inputs and enable them. */
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_GPP_INTR_CAUSE
comma
op_complement
id|GPP_EXTERNAL_INTERRUPTS
)paren
suffix:semicolon
id|mv64x60_set_bits
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_GPP_INTR_MASK
comma
id|GPP_EXTERNAL_INTERRUPTS
)paren
suffix:semicolon
multiline_comment|/* Route MPP interrupt inputs to GPP */
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_MPP_CNTL_2
comma
l_int|0x00000000
)paren
suffix:semicolon
id|mv64x60_write
c_func
(paren
op_amp
id|bh
comma
id|MV64x60_MPP_CNTL_3
comma
l_int|0x00000000
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|cpci690_setup_arch
id|cpci690_setup_arch
c_func
(paren
r_void
)paren
(brace
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
l_string|&quot;cpci690_setup_arch: enter&quot;
comma
l_int|0
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
macro_line|#ifdef   CONFIG_ROOT_NFS
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
l_string|&quot;cpci690_setup_arch: Enabling L2 cache&quot;
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Enable L2 and L3 caches (if 745x) */
id|_set_L2CR
c_func
(paren
id|_get_L2CR
c_func
(paren
)paren
op_or
id|L2CR_L2E
)paren
suffix:semicolon
id|_set_L3CR
c_func
(paren
id|_get_L3CR
c_func
(paren
)paren
op_or
id|L3CR_L3E
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
l_string|&quot;cpci690_setup_arch: Initializing bridge&quot;
comma
l_int|0
)paren
suffix:semicolon
id|cpci690_setup_bridge
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* set up PCI bridge(s) */
id|cpci690_setup_peripherals
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* set up chip selects/GPP/MPP etc */
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
l_string|&quot;cpci690_setup_arch: bridge init complete&quot;
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s %s port (C) 2003 MontaVista Software, Inc. &quot;
l_string|&quot;(source@mvista.com)&bslash;n&quot;
comma
id|BOARD_VENDOR
comma
id|BOARD_MACHINE
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
l_string|&quot;cpci690_setup_arch: exit&quot;
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* Platform device data fixup routines. */
macro_line|#if defined(CONFIG_SERIAL_MPSC)
r_static
r_void
id|__init
DECL|function|cpci690_fixup_mpsc_pdata
id|cpci690_fixup_mpsc_pdata
c_func
(paren
r_struct
id|platform_device
op_star
id|pdev
)paren
(brace
r_struct
id|mpsc_pdata
op_star
id|pdata
suffix:semicolon
id|pdata
op_assign
(paren
r_struct
id|mpsc_pdata
op_star
)paren
id|pdev-&gt;dev.platform_data
suffix:semicolon
id|pdata-&gt;max_idle
op_assign
l_int|40
suffix:semicolon
id|pdata-&gt;default_baud
op_assign
id|CPCI690_MPSC_BAUD
suffix:semicolon
id|pdata-&gt;brg_clk_src
op_assign
id|CPCI690_MPSC_CLK_SRC
suffix:semicolon
id|pdata-&gt;brg_clk_freq
op_assign
id|CPCI690_BUS_FREQ
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|cpci690_platform_notify
id|cpci690_platform_notify
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_static
r_struct
(brace
r_char
op_star
id|bus_id
suffix:semicolon
r_void
(paren
(paren
op_star
id|rtn
)paren
(paren
r_struct
id|platform_device
op_star
id|pdev
)paren
)paren
suffix:semicolon
)brace
id|dev_map
(braket
)braket
op_assign
(brace
(brace
id|MPSC_CTLR_NAME
l_string|&quot;.0&quot;
comma
id|cpci690_fixup_mpsc_pdata
)brace
comma
(brace
id|MPSC_CTLR_NAME
l_string|&quot;.1&quot;
comma
id|cpci690_fixup_mpsc_pdata
)brace
comma
)brace
suffix:semicolon
r_struct
id|platform_device
op_star
id|pdev
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_logical_and
id|dev-&gt;bus_id
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|dev_map
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|dev-&gt;bus_id
comma
id|dev_map
(braket
id|i
)braket
dot
id|bus_id
comma
id|BUS_ID_SIZE
)paren
)paren
(brace
id|pdev
op_assign
id|container_of
c_func
(paren
id|dev
comma
r_struct
id|platform_device
comma
id|dev
)paren
suffix:semicolon
id|dev_map
(braket
id|i
)braket
dot
id|rtn
c_func
(paren
id|pdev
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_static
r_void
DECL|function|cpci690_reset_board
id|cpci690_reset_board
c_func
(paren
r_void
)paren
(brace
id|u32
id|i
op_assign
l_int|10000
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|out_8
c_func
(paren
(paren
id|u8
op_star
)paren
(paren
id|cpci690_br_base
op_plus
id|CPCI690_BR_SW_RESET
)paren
comma
l_int|0x11
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_ne
l_int|0
)paren
id|i
op_increment
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
DECL|function|cpci690_restart
id|cpci690_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
id|cpci690_reset_board
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|cpci690_halt
id|cpci690_halt
c_func
(paren
r_void
)paren
(brace
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
DECL|function|cpci690_power_off
id|cpci690_power_off
c_func
(paren
r_void
)paren
(brace
id|cpci690_halt
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* NOTREACHED */
)brace
r_static
r_int
DECL|function|cpci690_show_cpuinfo
id|cpci690_show_cpuinfo
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
l_string|&quot;vendor&bslash;t&bslash;t: &quot;
id|BOARD_VENDOR
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;machine&bslash;t&bslash;t: &quot;
id|BOARD_MACHINE
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;cpu MHz&bslash;t&bslash;t: %d&bslash;n&quot;
comma
id|cpci690_get_cpu_speed
c_func
(paren
)paren
op_div
l_int|1000
op_div
l_int|1000
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;bus MHz&bslash;t&bslash;t: %d&bslash;n&quot;
comma
id|CPCI690_BUS_FREQ
op_div
l_int|1000
op_div
l_int|1000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|cpci690_calibrate_decr
id|cpci690_calibrate_decr
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
id|CPCI690_BUS_FREQ
op_div
l_int|4
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
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
)brace
r_static
id|__inline__
r_void
DECL|function|cpci690_set_bat
id|cpci690_set_bat
c_func
(paren
id|u32
id|addr
comma
id|u32
id|size
)paren
(brace
id|addr
op_and_assign
l_int|0xfffe0000
suffix:semicolon
id|size
op_and_assign
l_int|0x1ffe0000
suffix:semicolon
id|size
op_assign
(paren
(paren
id|size
op_rshift
l_int|17
)paren
op_minus
l_int|1
)paren
op_lshift
l_int|2
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_DBAT1U
comma
id|addr
op_or
id|size
op_or
l_int|0x2
)paren
suffix:semicolon
multiline_comment|/* Vs == 1; Vp == 0 */
id|mtspr
c_func
(paren
id|SPRN_DBAT1L
comma
id|addr
op_or
l_int|0x2a
)paren
suffix:semicolon
multiline_comment|/* WIMG bits == 0101; PP == r/w access */
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_SERIAL_TEXT_DEBUG) || defined(CONFIG_KGDB)
r_static
r_void
id|__init
DECL|function|cpci690_map_io
id|cpci690_map_io
c_func
(paren
r_void
)paren
(brace
id|io_block_mapping
c_func
(paren
id|CONFIG_MV64X60_NEW_BASE
comma
id|CONFIG_MV64X60_NEW_BASE
comma
l_int|128
op_star
id|KB
comma
id|_PAGE_IO
)paren
suffix:semicolon
)brace
macro_line|#endif
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
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
id|initrd_start
op_assign
id|initrd_end
op_assign
l_int|0
suffix:semicolon
id|initrd_below_start_ok
op_assign
l_int|0
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_INITRD */
id|parse_bootinfo
c_func
(paren
id|find_bootinfo
c_func
(paren
)paren
)paren
suffix:semicolon
id|loops_per_jiffy
op_assign
id|cpci690_get_cpu_speed
c_func
(paren
)paren
op_div
id|HZ
suffix:semicolon
id|isa_mem_base
op_assign
l_int|0
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|cpci690_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|cpci690_show_cpuinfo
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|gt64260_init_irq
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|gt64260_get_irq
suffix:semicolon
id|ppc_md.restart
op_assign
id|cpci690_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|cpci690_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|cpci690_halt
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|cpci690_find_end_of_memory
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
id|ppc_md.nvram_read_val
op_assign
id|todc_direct_read_val
suffix:semicolon
id|ppc_md.nvram_write_val
op_assign
id|todc_direct_write_val
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|cpci690_calibrate_decr
suffix:semicolon
multiline_comment|/*&n;&t; * Need to map in board regs (used by cpci690_find_end_of_memory())&n;&t; * and the bridge&squot;s regs (used by progress);&n;&t; */
id|cpci690_set_bat
c_func
(paren
id|CPCI690_BR_BASE
comma
l_int|32
op_star
id|MB
)paren
suffix:semicolon
id|cpci690_br_base
op_assign
id|CPCI690_BR_BASE
suffix:semicolon
macro_line|#ifdef&t;CONFIG_SERIAL_TEXT_DEBUG
id|ppc_md.setup_io_mappings
op_assign
id|cpci690_map_io
suffix:semicolon
id|ppc_md.progress
op_assign
id|mv64x60_mpsc_progress
suffix:semicolon
id|mv64x60_progress_init
c_func
(paren
id|CONFIG_MV64X60_NEW_BASE
)paren
suffix:semicolon
macro_line|#endif&t;/* CONFIG_SERIAL_TEXT_DEBUG */
macro_line|#ifdef&t;CONFIG_KGDB
id|ppc_md.setup_io_mappings
op_assign
id|cpci690_map_io
suffix:semicolon
id|ppc_md.early_serial_map
op_assign
id|cpci690_early_serial_map
suffix:semicolon
macro_line|#endif&t;/* CONFIG_KGDB */
macro_line|#if defined(CONFIG_SERIAL_MPSC)
id|platform_notify
op_assign
id|cpci690_platform_notify
suffix:semicolon
macro_line|#endif
)brace
eof
