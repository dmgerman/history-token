multiline_comment|/*&n; * arch/arm/mach-ixp2000/ixdp2800.c&n; *&n; * IXDP2800 platform support&n; *&n; * Original Author: Jeffrey Daly &lt;jeffrey.daly@intel.com&gt;&n; * Maintainer: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; *&n; * Copyright (C) 2002 Intel Corp.&n; * Copyright (C) 2003-2004 MontaVista Software, Inc.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/pci.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/time.h&gt;
macro_line|#include &lt;asm/mach/flash.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
DECL|function|ixdp2400_init_irq
r_void
id|ixdp2400_init_irq
c_func
(paren
r_void
)paren
(brace
id|ixdp2x00_init_irq
c_func
(paren
id|IXDP2800_CPLD_INT_STAT
comma
id|IXDP2800_CPLD_INT_MASK
comma
id|IXDP2400_NR_IRQS
)paren
suffix:semicolon
)brace
multiline_comment|/*************************************************************************&n; * IXDP2800 timer tick&n; *************************************************************************/
DECL|function|ixdp2800_timer_init
r_static
r_void
id|__init
id|ixdp2800_timer_init
c_func
(paren
r_void
)paren
(brace
id|ixp2000_init_time
c_func
(paren
l_int|50000000
)paren
suffix:semicolon
)brace
DECL|variable|ixdp2800_timer
r_static
r_struct
id|sys_timer
id|ixdp2800_timer
op_assign
(brace
dot
id|init
op_assign
id|ixdp2800_timer_init
comma
dot
id|offset
op_assign
id|ixp2000_gettimeoffset
comma
)brace
suffix:semicolon
multiline_comment|/*************************************************************************&n; * IXDP2800 PCI&n; *************************************************************************/
DECL|function|ixdp2800_pci_preinit
r_void
id|__init
id|ixdp2800_pci_preinit
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ixdp2x00_pci_preinit called&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|IXP2000_PCI_ADDR_EXT
op_assign
l_int|0x0000e000
suffix:semicolon
op_star
id|IXP2000_PCI_DRAM_BASE_ADDR_MASK
op_assign
(paren
l_int|0x40000000
op_minus
l_int|1
)paren
op_amp
op_complement
l_int|0xfffff
suffix:semicolon
op_star
id|IXP2000_PCI_SRAM_BASE_ADDR_MASK
op_assign
(paren
l_int|0x2000000
op_minus
l_int|1
)paren
op_amp
op_complement
l_int|0x3ffff
suffix:semicolon
id|ixp2000_pci_preinit
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|ixdp2800_pci_setup
r_int
id|ixdp2800_pci_setup
c_func
(paren
r_int
id|nr
comma
r_struct
id|pci_sys_data
op_star
id|sys
)paren
(brace
id|sys-&gt;mem_offset
op_assign
l_int|0x00000000
suffix:semicolon
id|ixp2000_pci_setup
c_func
(paren
id|nr
comma
id|sys
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|ixdp2800_pci_map_irq
r_static
r_int
id|__init
id|ixdp2800_pci_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|slot
comma
id|u8
id|pin
)paren
(brace
r_if
c_cond
(paren
id|ixdp2x00_master_npu
c_func
(paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Root bus devices.  Slave NPU is only one with interrupt.&n;&t;&t; * Everything else, we just return -1 which is invalid.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;bus-&gt;self
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;devfn
op_eq
id|IXDP2X00_SLAVE_NPU_DEVFN
)paren
(brace
r_return
id|IRQ_IXDP2800_INGRESS_NPU
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Bridge behind the PMC slot.&n;&t;&t; */
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;self-&gt;devfn
op_eq
id|IXDP2X00_PMC_DEVFN
op_logical_and
id|dev-&gt;bus-&gt;parent-&gt;self-&gt;devfn
op_eq
id|IXDP2X00_P2P_DEVFN
op_logical_and
op_logical_neg
id|dev-&gt;bus-&gt;parent-&gt;self-&gt;bus-&gt;parent
)paren
(brace
r_return
id|IRQ_IXDP2800_PMC
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Device behind the first bridge&n;&t;&t; */
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;self-&gt;devfn
op_eq
id|IXDP2X00_P2P_DEVFN
)paren
(brace
r_switch
c_cond
(paren
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
(brace
r_case
id|IXDP2X00_PMC_DEVFN
suffix:colon
r_return
id|IRQ_IXDP2800_PMC
suffix:semicolon
r_case
id|IXDP2800_MASTER_ENET_DEVFN
suffix:colon
r_return
id|IRQ_IXDP2800_EGRESS_ENET
suffix:semicolon
r_case
id|IXDP2800_SWITCH_FABRIC_DEVFN
suffix:colon
r_return
id|IRQ_IXDP2800_FABRIC
suffix:semicolon
)brace
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
r_return
id|IRQ_IXP2000_PCIB
suffix:semicolon
multiline_comment|/* Slave NIC interrupt */
)brace
DECL|function|ixdp2800_pci_postinit
r_static
r_void
id|ixdp2800_pci_postinit
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_if
c_cond
(paren
id|ixdp2x00_master_npu
c_func
(paren
)paren
)paren
(brace
id|dev
op_assign
id|pci_find_slot
c_func
(paren
l_int|1
comma
id|IXDP2800_SLAVE_ENET_DEVFN
)paren
suffix:semicolon
id|pci_remove_bus_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_else
(brace
id|dev
op_assign
id|pci_find_slot
c_func
(paren
l_int|1
comma
id|IXDP2800_MASTER_ENET_DEVFN
)paren
suffix:semicolon
id|pci_remove_bus_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ixdp2x00_slave_pci_postinit
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|variable|__initdata
r_struct
id|hw_pci
id|ixdp2800_pci
id|__initdata
op_assign
(brace
dot
id|nr_controllers
op_assign
l_int|1
comma
dot
id|setup
op_assign
id|ixdp2800_pci_setup
comma
dot
id|preinit
op_assign
id|ixdp2800_pci_preinit
comma
dot
id|postinit
op_assign
id|ixdp2800_pci_postinit
comma
dot
id|scan
op_assign
id|ixp2000_pci_scan_bus
comma
dot
id|map_irq
op_assign
id|ixdp2800_pci_map_irq
comma
)brace
suffix:semicolon
DECL|function|ixdp2800_pci_init
r_int
id|__init
id|ixdp2800_pci_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_ixdp2800
c_func
(paren
)paren
)paren
id|pci_common_init
c_func
(paren
op_amp
id|ixdp2800_pci
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ixdp2800_pci_init
id|subsys_initcall
c_func
(paren
id|ixdp2800_pci_init
)paren
suffix:semicolon
DECL|function|ixdp2800_init_irq
r_void
id|ixdp2800_init_irq
c_func
(paren
r_void
)paren
(brace
id|ixdp2x00_init_irq
c_func
(paren
id|IXDP2800_CPLD_INT_STAT
comma
id|IXDP2800_CPLD_INT_MASK
comma
id|IXDP2800_NR_IRQS
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|IXDP2800
comma
l_string|&quot;Intel IXDP2800 Development Platform&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;MontaVista Software, Inc.&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x00000000
comma
id|IXP2000_UART_PHYS_BASE
comma
id|IXP2000_UART_VIRT_BASE
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x00000100
)paren
id|MAPIO
c_func
(paren
id|ixdp2x00_map_io
)paren
id|INITIRQ
c_func
(paren
id|ixdp2800_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|ixdp2800_timer
comma
id|INIT_MACHINE
c_func
(paren
id|ixdp2x00_init_machine
)paren
id|MACHINE_END
eof
