multiline_comment|/*&n; * arch/ppc/platforms/4xx/luan.c&n; *&n; * Luan board specific routines&n; *&n; * Matt Porter &lt;mporter@kernel.crashing.org&gt;&n; *&n; * Copyright 2004-2005 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
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
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/ocp.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/todc.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/ppc4xx_pic.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
macro_line|#include &lt;syslib/ibm44x_common.h&gt;
macro_line|#include &lt;syslib/ibm440gx_common.h&gt;
macro_line|#include &lt;syslib/ibm440sp_common.h&gt;
multiline_comment|/*&n; * This is a horrible kludge, we eventually need to abstract this&n; * generic PHY stuff, so the  standard phy mode defines can be&n; * easily used from arch code.&n; */
macro_line|#include &quot;../../../../drivers/net/ibm_emac/ibm_emac_phy.h&quot;
DECL|variable|__res
id|bd_t
id|__res
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|ibm44x_clocks
id|clocks
id|__initdata
suffix:semicolon
r_static
r_void
id|__init
DECL|function|luan_calibrate_decr
id|luan_calibrate_decr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|freq
suffix:semicolon
r_if
c_cond
(paren
id|mfspr
c_func
(paren
id|SPRN_CCR1
)paren
op_amp
id|CCR1_TCS
)paren
id|freq
op_assign
id|LUAN_TMR_CLK
suffix:semicolon
r_else
id|freq
op_assign
id|clocks.cpu
suffix:semicolon
id|ibm44x_calibrate_decr
c_func
(paren
id|freq
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|luan_show_cpuinfo
id|luan_show_cpuinfo
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
l_string|&quot;machine&bslash;t&bslash;t: PPC440SP EVB (Luan)&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|luan_map_irq
id|luan_map_irq
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
multiline_comment|/* PCIX0 in adapter mode, no host interrupt routing */
multiline_comment|/* PCIX1 */
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
multiline_comment|/*&n;&t;&t; *&t;PCI IDSEL/INTPIN-&gt;INTLINE&n;&t;&t; *&t;  A   B   C   D&n;&t;&t; */
(brace
(brace
l_int|49
comma
l_int|49
comma
l_int|49
comma
l_int|49
)brace
comma
multiline_comment|/* IDSEL 1 - PCIX1 Slot 0 */
(brace
l_int|49
comma
l_int|49
comma
l_int|49
comma
l_int|49
)brace
comma
multiline_comment|/* IDSEL 2 - PCIX1 Slot 1 */
(brace
l_int|49
comma
l_int|49
comma
l_int|49
comma
l_int|49
)brace
comma
multiline_comment|/* IDSEL 3 - PCIX1 Slot 2 */
(brace
l_int|49
comma
l_int|49
comma
l_int|49
comma
l_int|49
)brace
comma
multiline_comment|/* IDSEL 4 - PCIX1 Slot 3 */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|1
comma
id|max_idsel
op_assign
l_int|4
comma
id|irqs_per_slot
op_assign
l_int|4
suffix:semicolon
r_return
id|PCI_IRQ_TABLE_LOOKUP
suffix:semicolon
multiline_comment|/* PCIX2 */
)brace
r_else
r_if
c_cond
(paren
id|hose-&gt;index
op_eq
l_int|1
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
multiline_comment|/*&n;&t;&t; *&t;PCI IDSEL/INTPIN-&gt;INTLINE&n;&t;&t; *&t;  A   B   C   D&n;&t;&t; */
(brace
(brace
l_int|50
comma
l_int|50
comma
l_int|50
comma
l_int|50
)brace
comma
multiline_comment|/* IDSEL 1 - PCIX2 Slot 0 */
(brace
l_int|50
comma
l_int|50
comma
l_int|50
comma
l_int|50
)brace
comma
multiline_comment|/* IDSEL 2 - PCIX2 Slot 1 */
(brace
l_int|50
comma
l_int|50
comma
l_int|50
comma
l_int|50
)brace
comma
multiline_comment|/* IDSEL 3 - PCIX2 Slot 2 */
(brace
l_int|50
comma
l_int|50
comma
l_int|50
comma
l_int|50
)brace
comma
multiline_comment|/* IDSEL 4 - PCIX2 Slot 3 */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|1
comma
id|max_idsel
op_assign
l_int|4
comma
id|irqs_per_slot
op_assign
l_int|4
suffix:semicolon
r_return
id|PCI_IRQ_TABLE_LOOKUP
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|luan_set_emacdata
r_static
r_void
id|__init
id|luan_set_emacdata
c_func
(paren
r_void
)paren
(brace
r_struct
id|ocp_def
op_star
id|def
suffix:semicolon
r_struct
id|ocp_func_emac_data
op_star
id|emacdata
suffix:semicolon
multiline_comment|/* Set phy_map, phy_mode, and mac_addr for the EMAC */
id|def
op_assign
id|ocp_get_one_device
c_func
(paren
id|OCP_VENDOR_IBM
comma
id|OCP_FUNC_EMAC
comma
l_int|0
)paren
suffix:semicolon
id|emacdata
op_assign
id|def-&gt;additions
suffix:semicolon
id|emacdata-&gt;phy_map
op_assign
l_int|0x00000001
suffix:semicolon
multiline_comment|/* Skip 0x00 */
id|emacdata-&gt;phy_mode
op_assign
id|PHY_MODE_GMII
suffix:semicolon
id|memcpy
c_func
(paren
id|emacdata-&gt;mac_addr
comma
id|__res.bi_enetaddr
comma
l_int|6
)paren
suffix:semicolon
)brace
DECL|macro|PCIX_READW
mdefine_line|#define PCIX_READW(offset) &bslash;&n;&t;(readw((void *)((u32)pcix_reg_base+offset)))
DECL|macro|PCIX_WRITEW
mdefine_line|#define PCIX_WRITEW(value, offset) &bslash;&n;&t;(writew(value, (void *)((u32)pcix_reg_base+offset)))
DECL|macro|PCIX_WRITEL
mdefine_line|#define PCIX_WRITEL(value, offset) &bslash;&n;&t;(writel(value, (void *)((u32)pcix_reg_base+offset)))
r_static
r_void
id|__init
DECL|function|luan_setup_pcix
id|luan_setup_pcix
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_void
op_star
id|pcix_reg_base
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pcix_reg_base
op_assign
id|ioremap64
c_func
(paren
id|PCIX0_REG_BASE
op_plus
id|i
op_star
id|PCIX_REG_OFFSET
comma
id|PCIX_REG_SIZE
)paren
suffix:semicolon
multiline_comment|/* Enable PCIX0 I/O, Mem, and Busmaster cycles */
id|PCIX_WRITEW
c_func
(paren
id|PCIX_READW
c_func
(paren
id|PCIX0_COMMAND
)paren
op_or
id|PCI_COMMAND_IO
op_or
id|PCI_COMMAND_MEMORY
op_or
id|PCI_COMMAND_MASTER
comma
id|PCIX0_COMMAND
)paren
suffix:semicolon
multiline_comment|/* Disable all windows */
id|PCIX_WRITEL
c_func
(paren
l_int|0
comma
id|PCIX0_POM0SA
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0
comma
id|PCIX0_POM1SA
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0
comma
id|PCIX0_POM2SA
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0
comma
id|PCIX0_PIM0SA
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0
comma
id|PCIX0_PIM0SAH
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0
comma
id|PCIX0_PIM1SA
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0
comma
id|PCIX0_PIM2SA
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0
comma
id|PCIX0_PIM2SAH
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Setup 512MB PLB-&gt;PCI outbound mem window&n;&t;&t; * (a_n000_0000-&gt;0_n000_0000)&n;&t;&t; * */
id|PCIX_WRITEL
c_func
(paren
l_int|0x0000000a
comma
id|PCIX0_POM0LAH
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0x80000000
op_or
id|i
op_star
id|LUAN_PCIX_MEM_SIZE
comma
id|PCIX0_POM0LAL
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0x00000000
comma
id|PCIX0_POM0PCIAH
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0x80000000
op_or
id|i
op_star
id|LUAN_PCIX_MEM_SIZE
comma
id|PCIX0_POM0PCIAL
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0xe0000001
comma
id|PCIX0_POM0SA
)paren
suffix:semicolon
multiline_comment|/* Setup 2GB PCI-&gt;PLB inbound memory window at 0, enable MSIs */
id|PCIX_WRITEL
c_func
(paren
l_int|0x00000000
comma
id|PCIX0_PIM0LAH
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0x00000000
comma
id|PCIX0_PIM0LAL
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0xe0000007
comma
id|PCIX0_PIM0SA
)paren
suffix:semicolon
id|PCIX_WRITEL
c_func
(paren
l_int|0xffffffff
comma
id|PCIX0_PIM0SAH
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|pcix_reg_base
)paren
suffix:semicolon
)brace
id|eieio
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|luan_setup_hose
id|luan_setup_hose
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
r_int
id|lower_mem
comma
r_int
id|upper_mem
comma
r_int
id|cfga
comma
r_int
id|cfgd
comma
id|u64
id|pcix_io_base
)paren
(brace
r_char
id|name
(braket
l_int|20
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;PCIX%d host bridge&quot;
comma
id|hose-&gt;index
)paren
suffix:semicolon
id|hose-&gt;pci_mem_offset
op_assign
id|LUAN_PCIX_MEM_OFFSET
suffix:semicolon
id|pci_init_resource
c_func
(paren
op_amp
id|hose-&gt;io_resource
comma
id|LUAN_PCIX_LOWER_IO
comma
id|LUAN_PCIX_UPPER_IO
comma
id|IORESOURCE_IO
comma
id|name
)paren
suffix:semicolon
id|pci_init_resource
c_func
(paren
op_amp
id|hose-&gt;mem_resources
(braket
l_int|0
)braket
comma
id|lower_mem
comma
id|upper_mem
comma
id|IORESOURCE_MEM
comma
id|name
)paren
suffix:semicolon
id|hose-&gt;io_space.start
op_assign
id|LUAN_PCIX_LOWER_IO
suffix:semicolon
id|hose-&gt;io_space.end
op_assign
id|LUAN_PCIX_UPPER_IO
suffix:semicolon
id|hose-&gt;mem_space.start
op_assign
id|lower_mem
suffix:semicolon
id|hose-&gt;mem_space.end
op_assign
id|upper_mem
suffix:semicolon
id|isa_io_base
op_assign
(paren
r_int
r_int
)paren
id|ioremap64
c_func
(paren
id|pcix_io_base
comma
id|PCIX_IO_SIZE
)paren
suffix:semicolon
id|hose-&gt;io_base_virt
op_assign
(paren
r_void
op_star
)paren
id|isa_io_base
suffix:semicolon
id|setup_indirect_pci
c_func
(paren
id|hose
comma
id|cfga
comma
id|cfgd
)paren
suffix:semicolon
id|hose-&gt;set_cfg_type
op_assign
l_int|1
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|luan_setup_hoses
id|luan_setup_hoses
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose1
comma
op_star
id|hose2
suffix:semicolon
multiline_comment|/* Configure windows on the PCI-X host bridge */
id|luan_setup_pcix
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Allocate hoses for PCIX1 and PCIX2 */
id|hose1
op_assign
id|pcibios_alloc_controller
c_func
(paren
)paren
suffix:semicolon
id|hose2
op_assign
id|pcibios_alloc_controller
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hose1
op_logical_or
op_logical_neg
id|hose2
)paren
r_return
suffix:semicolon
multiline_comment|/* Setup PCIX1 */
id|hose1-&gt;first_busno
op_assign
l_int|0
suffix:semicolon
id|hose1-&gt;last_busno
op_assign
l_int|0xff
suffix:semicolon
id|luan_setup_hose
c_func
(paren
id|hose1
comma
id|LUAN_PCIX1_LOWER_MEM
comma
id|LUAN_PCIX1_UPPER_MEM
comma
id|PCIX1_CFGA
comma
id|PCIX1_CFGD
comma
id|PCIX1_IO_BASE
)paren
suffix:semicolon
id|hose1-&gt;last_busno
op_assign
id|pciauto_bus_scan
c_func
(paren
id|hose1
comma
id|hose1-&gt;first_busno
)paren
suffix:semicolon
multiline_comment|/* Setup PCIX2 */
id|hose2-&gt;first_busno
op_assign
id|hose1-&gt;last_busno
op_plus
l_int|1
suffix:semicolon
id|hose2-&gt;last_busno
op_assign
l_int|0xff
suffix:semicolon
id|luan_setup_hose
c_func
(paren
id|hose2
comma
id|LUAN_PCIX2_LOWER_MEM
comma
id|LUAN_PCIX2_UPPER_MEM
comma
id|PCIX2_CFGA
comma
id|PCIX2_CFGD
comma
id|PCIX2_IO_BASE
)paren
suffix:semicolon
id|hose2-&gt;last_busno
op_assign
id|pciauto_bus_scan
c_func
(paren
id|hose2
comma
id|hose2-&gt;first_busno
)paren
suffix:semicolon
id|ppc_md.pci_swizzle
op_assign
id|common_swizzle
suffix:semicolon
id|ppc_md.pci_map_irq
op_assign
id|luan_map_irq
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
DECL|function|luan_early_serial_map
id|luan_early_serial_map
c_func
(paren
r_void
)paren
(brace
r_struct
id|uart_port
id|port
suffix:semicolon
multiline_comment|/* Setup ioremapped serial port access */
id|memset
c_func
(paren
op_amp
id|port
comma
l_int|0
comma
r_sizeof
(paren
id|port
)paren
)paren
suffix:semicolon
id|port.membase
op_assign
id|ioremap64
c_func
(paren
id|PPC440SP_UART0_ADDR
comma
l_int|8
)paren
suffix:semicolon
id|port.irq
op_assign
id|UART0_INT
suffix:semicolon
id|port.uartclk
op_assign
id|clocks.uart0
suffix:semicolon
id|port.regshift
op_assign
l_int|0
suffix:semicolon
id|port.iotype
op_assign
id|SERIAL_IO_MEM
suffix:semicolon
id|port.flags
op_assign
id|ASYNC_BOOT_AUTOCONF
op_or
id|ASYNC_SKIP_TEST
suffix:semicolon
id|port.line
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|early_serial_setup
c_func
(paren
op_amp
id|port
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
id|port.membase
op_assign
id|ioremap64
c_func
(paren
id|PPC440SP_UART1_ADDR
comma
l_int|8
)paren
suffix:semicolon
id|port.irq
op_assign
id|UART1_INT
suffix:semicolon
id|port.uartclk
op_assign
id|clocks.uart1
suffix:semicolon
id|port.line
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|early_serial_setup
c_func
(paren
op_amp
id|port
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
id|port.membase
op_assign
id|ioremap64
c_func
(paren
id|PPC440SP_UART2_ADDR
comma
l_int|8
)paren
suffix:semicolon
id|port.irq
op_assign
id|UART2_INT
suffix:semicolon
id|port.uartclk
op_assign
id|BASE_BAUD
suffix:semicolon
id|port.line
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
id|port
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Early serial init of port 2 failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
id|__init
DECL|function|luan_setup_arch
id|luan_setup_arch
c_func
(paren
r_void
)paren
(brace
id|luan_set_emacdata
c_func
(paren
)paren
suffix:semicolon
macro_line|#if !defined(CONFIG_BDI_SWITCH)
multiline_comment|/*&n;&t; * The Abatron BDI JTAG debugger does not tolerate others&n;&t; * mucking with the debug registers.&n;&t; */
id|mtspr
c_func
(paren
id|SPRN_DBCR0
comma
(paren
id|DBCR0_TDE
op_or
id|DBCR0_IDM
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Determine various clocks.&n;&t; * To be completely correct we should get SysClk&n;&t; * from FPGA, because it can be changed by on-board switches&n;&t; * --ebs&n;&t; */
multiline_comment|/* 440GX and 440SP clocking is the same -mdp */
id|ibm440gx_get_clocks
c_func
(paren
op_amp
id|clocks
comma
l_int|33333333
comma
l_int|6
op_star
l_int|1843200
)paren
suffix:semicolon
id|ocp_sys_info.opb_bus_freq
op_assign
id|clocks.opb
suffix:semicolon
multiline_comment|/* init to some ~sane value until calibrate_delay() runs */
id|loops_per_jiffy
op_assign
l_int|50000000
op_div
id|HZ
suffix:semicolon
multiline_comment|/* Setup PCIXn host bridges */
id|luan_setup_hoses
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
id|Root_HDA1
suffix:semicolon
macro_line|#endif
id|luan_early_serial_map
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Identify the system */
id|printk
c_func
(paren
l_string|&quot;Luan port (MontaVista Software, Inc. &lt;source@mvista.com&gt;)&bslash;n&quot;
)paren
suffix:semicolon
)brace
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
id|parse_bootinfo
c_func
(paren
id|find_bootinfo
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we were passed in a board information, copy it into the&n;&t; * residual data area.&n;&t; */
r_if
c_cond
(paren
id|r3
)paren
id|__res
op_assign
op_star
(paren
id|bd_t
op_star
)paren
(paren
id|r3
op_plus
id|KERNELBASE
)paren
suffix:semicolon
id|ibm44x_platform_init
c_func
(paren
)paren
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|luan_setup_arch
suffix:semicolon
id|ppc_md.show_cpuinfo
op_assign
id|luan_show_cpuinfo
suffix:semicolon
id|ppc_md.find_end_of_memory
op_assign
id|ibm440sp_find_end_of_memory
suffix:semicolon
id|ppc_md.get_irq
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Set in ppc4xx_pic_init() */
id|ppc_md.calibrate_decr
op_assign
id|luan_calibrate_decr
suffix:semicolon
macro_line|#ifdef CONFIG_KGDB
id|ppc_md.early_serial_map
op_assign
id|luan_early_serial_map
suffix:semicolon
macro_line|#endif
)brace
eof
