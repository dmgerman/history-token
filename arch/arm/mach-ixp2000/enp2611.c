multiline_comment|/*&n; * arch/arm/mach-ixp2000/enp2611.c&n; *&n; * Radisys ENP-2611 support.&n; *&n; * Created 2004 by Lennert Buytenhek from the ixdp2x01 code.  The&n; * original version carries the following notices:&n; *&n; * Original Author: Andrzej Mialwoski &lt;andrzej.mialwoski@intel.com&gt;&n; * Maintainer: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; *&n; * Copyright (C) 2002-2003 Intel Corp.&n; * Copyright (C) 2003-2004 MontaVista Software, Inc.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;linux/device.h&gt;
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
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/flash.h&gt;
multiline_comment|/*************************************************************************&n; * ENP-2611 timer tick configuration&n; *************************************************************************/
DECL|function|enp2611_timer_init
r_static
r_void
id|__init
id|enp2611_timer_init
c_func
(paren
r_void
)paren
(brace
id|ixp2000_init_time
c_func
(paren
l_int|50
op_star
l_int|1000
op_star
l_int|1000
)paren
suffix:semicolon
)brace
r_static
r_struct
id|enp2611_timer
op_assign
(brace
dot
id|init
op_assign
id|enp2611_timer_init
comma
dot
id|offset
op_assign
id|ixp2000_gettimeoffset
comma
)brace
suffix:semicolon
multiline_comment|/*************************************************************************&n; * ENP-2611 PCI&n; *************************************************************************/
DECL|function|enp2611_pci_setup
r_static
r_int
id|enp2611_pci_setup
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
l_int|0xe0000000
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
DECL|function|enp2611_pci_preinit
r_static
r_void
id|__init
id|enp2611_pci_preinit
c_func
(paren
r_void
)paren
(brace
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_PCI_ADDR_EXT
comma
l_int|0x00100000
)paren
suffix:semicolon
id|ixp2000_pci_preinit
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|enp2611_pci_valid_device
r_static
r_inline
r_int
id|enp2611_pci_valid_device
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
)paren
(brace
multiline_comment|/* The 82559 ethernet controller appears at both PCI:1:0:0 and&n;&t; * PCI:1:2:0, so let&squot;s pretend the second one isn&squot;t there.&n;&t; */
r_if
c_cond
(paren
id|bus-&gt;number
op_eq
l_int|0x01
op_logical_and
id|devfn
op_eq
l_int|0x10
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|enp2611_pci_read_config
r_static
r_int
id|enp2611_pci_read_config
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
op_star
id|value
)paren
(brace
r_if
c_cond
(paren
id|enp2611_pci_valid_device
c_func
(paren
id|bus
comma
id|devfn
)paren
)paren
r_return
id|ixp2000_pci_read_config
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
comma
id|size
comma
id|value
)paren
suffix:semicolon
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
DECL|function|enp2611_pci_write_config
r_static
r_int
id|enp2611_pci_write_config
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
id|value
)paren
(brace
r_if
c_cond
(paren
id|enp2611_pci_valid_device
c_func
(paren
id|bus
comma
id|devfn
)paren
)paren
r_return
id|ixp2000_pci_write_config
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
comma
id|size
comma
id|value
)paren
suffix:semicolon
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
DECL|variable|enp2611_pci_ops
r_static
r_struct
id|pci_ops
id|enp2611_pci_ops
op_assign
(brace
dot
id|read
op_assign
id|enp2611_pci_read_config
comma
dot
id|write
op_assign
id|enp2611_pci_write_config
)brace
suffix:semicolon
DECL|function|enp2611_pci_scan_bus
r_static
r_struct
id|pci_bus
op_star
id|__init
id|enp2611_pci_scan_bus
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
r_return
id|pci_scan_bus
c_func
(paren
id|sys-&gt;busnr
comma
op_amp
id|enp2611_pci_ops
comma
id|sys
)paren
suffix:semicolon
)brace
DECL|function|enp2611_pci_map_irq
r_static
r_int
id|__init
id|enp2611_pci_map_irq
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
r_int
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
op_eq
l_int|0x00
op_logical_and
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
op_eq
l_int|0x01
)paren
(brace
multiline_comment|/* 21555 non-transparent bridge.  */
id|irq
op_assign
id|IRQ_IXP2000_PCIB
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
op_eq
l_int|0x01
op_logical_and
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
op_eq
l_int|0x00
)paren
(brace
multiline_comment|/* 82559 ethernet.  */
id|irq
op_assign
id|IRQ_IXP2000_PCIA
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;enp2611_pci_map_irq for unknown device&bslash;n&quot;
)paren
suffix:semicolon
id|irq
op_assign
id|IRQ_IXP2000_PCI
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Assigned IRQ %d to PCI:%d:%d:%d&bslash;n&quot;
comma
id|irq
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
DECL|variable|__initdata
r_struct
id|hw_pci
id|enp2611_pci
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
id|enp2611_pci_setup
comma
dot
id|preinit
op_assign
id|enp2611_pci_preinit
comma
dot
id|scan
op_assign
id|enp2611_pci_scan_bus
comma
dot
id|map_irq
op_assign
id|enp2611_pci_map_irq
comma
)brace
suffix:semicolon
DECL|function|enp2611_pci_init
r_int
id|__init
id|enp2611_pci_init
c_func
(paren
r_void
)paren
(brace
id|pci_common_init
c_func
(paren
op_amp
id|enp2611_pci
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|enp2611_pci_init
id|subsys_initcall
c_func
(paren
id|enp2611_pci_init
)paren
suffix:semicolon
multiline_comment|/*************************************************************************&n; * ENP-2611 Machine Intialization&n; *************************************************************************/
DECL|variable|enp2611_flash_platform_data
r_static
r_struct
id|flash_platform_data
id|enp2611_flash_platform_data
op_assign
(brace
dot
id|map_name
op_assign
l_string|&quot;cfi_probe&quot;
comma
dot
id|width
op_assign
l_int|1
comma
)brace
suffix:semicolon
DECL|variable|enp2611_flash_data
r_static
r_struct
id|ixp2000_flash_data
id|enp2611_flash_data
op_assign
(brace
dot
id|platform_data
op_assign
op_amp
id|enp2611_flash_platform_data
comma
dot
id|nr_banks
op_assign
l_int|1
)brace
suffix:semicolon
DECL|variable|enp2611_flash_resource
r_static
r_struct
id|resource
id|enp2611_flash_resource
op_assign
(brace
dot
id|start
op_assign
l_int|0xc4000000
comma
dot
id|end
op_assign
l_int|0xc4000000
op_plus
l_int|0x00ffffff
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
DECL|variable|enp2611_flash
r_static
r_struct
id|platform_device
id|enp2611_flash
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;IXP2000-Flash&quot;
comma
dot
id|id
op_assign
l_int|0
comma
dot
id|dev
op_assign
(brace
dot
id|platform_data
op_assign
op_amp
id|enp2611_flash_data
comma
)brace
comma
dot
id|num_resources
op_assign
l_int|1
comma
dot
id|resource
op_assign
op_amp
id|enp2611_flash_resource
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|enp2611_devices
(braket
)braket
id|__initdata
op_assign
(brace
op_amp
id|enp2611_flash
)brace
suffix:semicolon
DECL|function|enp2611_init_machine
r_static
r_void
id|__init
id|enp2611_init_machine
c_func
(paren
r_void
)paren
(brace
id|platform_add_devices
c_func
(paren
id|enp2611_devices
comma
id|ARRAY_SIZE
c_func
(paren
id|enp2611_devices
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ARCH_ENP2611
id|MACHINE_START
c_func
(paren
id|ENP2611
comma
l_string|&quot;Radisys ENP-2611 PCI network processor board&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Lennert Buytenhek &lt;buytenh@wantstofly.org&gt;&quot;
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
id|ixp2000_map_io
)paren
id|INITIRQ
c_func
(paren
id|ixp2000_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|enp2611_timer
comma
id|INIT_MACHINE
c_func
(paren
id|enp2611_init_machine
)paren
id|MACHINE_END
macro_line|#endif
eof
