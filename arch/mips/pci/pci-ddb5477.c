multiline_comment|/*&n; * PCI code for DDB5477.&n; *&n; * Copyright (C) 2001 MontaVista Software Inc.&n; * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/pci_channel.h&gt;
macro_line|#include &lt;asm/debug.h&gt;
macro_line|#include &lt;asm/ddb5xxx/ddb5xxx.h&gt;
DECL|variable|extpci_io_resource
r_static
r_struct
id|resource
id|extpci_io_resource
op_assign
(brace
l_string|&quot;ext pci IO space&quot;
comma
id|DDB_PCI0_IO_BASE
op_minus
id|DDB_PCI_IO_BASE
op_plus
l_int|0x4000
comma
id|DDB_PCI0_IO_BASE
op_minus
id|DDB_PCI_IO_BASE
op_plus
id|DDB_PCI0_IO_SIZE
op_minus
l_int|1
comma
id|IORESOURCE_IO
)brace
suffix:semicolon
DECL|variable|extpci_mem_resource
r_static
r_struct
id|resource
id|extpci_mem_resource
op_assign
(brace
l_string|&quot;ext pci memory space&quot;
comma
id|DDB_PCI0_MEM_BASE
op_plus
l_int|0x100000
comma
id|DDB_PCI0_MEM_BASE
op_plus
id|DDB_PCI0_MEM_SIZE
op_minus
l_int|1
comma
id|IORESOURCE_MEM
)brace
suffix:semicolon
DECL|variable|iopci_io_resource
r_static
r_struct
id|resource
id|iopci_io_resource
op_assign
(brace
l_string|&quot;io pci IO space&quot;
comma
id|DDB_PCI1_IO_BASE
op_minus
id|DDB_PCI_IO_BASE
comma
id|DDB_PCI1_IO_BASE
op_minus
id|DDB_PCI_IO_BASE
op_plus
id|DDB_PCI1_IO_SIZE
op_minus
l_int|1
comma
id|IORESOURCE_IO
)brace
suffix:semicolon
DECL|variable|iopci_mem_resource
r_static
r_struct
id|resource
id|iopci_mem_resource
op_assign
(brace
l_string|&quot;ext pci memory space&quot;
comma
id|DDB_PCI1_MEM_BASE
comma
id|DDB_PCI1_MEM_BASE
op_plus
id|DDB_PCI1_MEM_SIZE
op_minus
l_int|1
comma
id|IORESOURCE_MEM
)brace
suffix:semicolon
r_extern
r_struct
id|pci_ops
id|ddb5477_ext_pci_ops
suffix:semicolon
r_extern
r_struct
id|pci_ops
id|ddb5477_io_pci_ops
suffix:semicolon
DECL|variable|mips_pci_channels
r_struct
id|pci_channel
id|mips_pci_channels
(braket
)braket
op_assign
(brace
(brace
op_amp
id|ddb5477_ext_pci_ops
comma
op_amp
id|extpci_io_resource
comma
op_amp
id|extpci_mem_resource
)brace
comma
(brace
op_amp
id|ddb5477_io_pci_ops
comma
op_amp
id|iopci_io_resource
comma
op_amp
id|iopci_mem_resource
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * we fix up irqs based on the slot number.&n; * The first entry is at AD:11.&n; * Fortunately this works because, although we have two pci buses,&n; * they all have different slot numbers (except for rockhopper slot 20&n; * which is handled below).&n; *&n; */
multiline_comment|/*&n; * irq mapping : device -&gt; pci int # -&gt; vrc4377 irq# , &n; * ddb5477 board manual page 4  and vrc5477 manual page 46&n; */
multiline_comment|/*&n; * based on ddb5477 manual page 11&n; */
DECL|macro|MAX_SLOT_NUM
mdefine_line|#define&t;&t;MAX_SLOT_NUM&t;&t;21
DECL|variable|irq_map
r_static
r_int
r_char
id|irq_map
(braket
id|MAX_SLOT_NUM
)braket
op_assign
(brace
multiline_comment|/* SLOT:  0, AD:11 */
l_int|0xff
comma
multiline_comment|/* SLOT:  1, AD:12 */
l_int|0xff
comma
multiline_comment|/* SLOT:  2, AD:13 */
l_int|0xff
comma
multiline_comment|/* SLOT:  3, AD:14 */
l_int|0xff
comma
multiline_comment|/* SLOT:  4, AD:15 */
id|VRC5477_IRQ_INTA
comma
multiline_comment|/* onboard tulip */
multiline_comment|/* SLOT:  5, AD:16 */
id|VRC5477_IRQ_INTB
comma
multiline_comment|/* slot 1 */
multiline_comment|/* SLOT:  6, AD:17 */
id|VRC5477_IRQ_INTC
comma
multiline_comment|/* slot 2 */
multiline_comment|/* SLOT:  7, AD:18 */
id|VRC5477_IRQ_INTD
comma
multiline_comment|/* slot 3 */
multiline_comment|/* SLOT:  8, AD:19 */
id|VRC5477_IRQ_INTE
comma
multiline_comment|/* slot 4 */
multiline_comment|/* SLOT:  9, AD:20 */
l_int|0xff
comma
multiline_comment|/* SLOT: 10, AD:21 */
l_int|0xff
comma
multiline_comment|/* SLOT: 11, AD:22 */
l_int|0xff
comma
multiline_comment|/* SLOT: 12, AD:23 */
l_int|0xff
comma
multiline_comment|/* SLOT: 13, AD:24 */
l_int|0xff
comma
multiline_comment|/* SLOT: 14, AD:25 */
l_int|0xff
comma
multiline_comment|/* SLOT: 15, AD:26 */
l_int|0xff
comma
multiline_comment|/* SLOT: 16, AD:27 */
l_int|0xff
comma
multiline_comment|/* SLOT: 17, AD:28 */
l_int|0xff
comma
multiline_comment|/* SLOT: 18, AD:29 */
id|VRC5477_IRQ_IOPCI_INTC
comma
multiline_comment|/* vrc5477 ac97 */
multiline_comment|/* SLOT: 19, AD:30 */
id|VRC5477_IRQ_IOPCI_INTB
comma
multiline_comment|/* vrc5477 usb peri */
multiline_comment|/* SLOT: 20, AD:31 */
id|VRC5477_IRQ_IOPCI_INTA
comma
multiline_comment|/* vrc5477 usb host */
)brace
suffix:semicolon
DECL|variable|rockhopperII_irq_map
r_static
r_int
r_char
id|rockhopperII_irq_map
(braket
id|MAX_SLOT_NUM
)braket
op_assign
(brace
multiline_comment|/* SLOT:  0, AD:11 */
l_int|0xff
comma
multiline_comment|/* SLOT:  1, AD:12 */
id|VRC5477_IRQ_INTB
comma
multiline_comment|/* onboard AMD PCNET */
multiline_comment|/* SLOT:  2, AD:13 */
l_int|0xff
comma
multiline_comment|/* SLOT:  3, AD:14 */
l_int|0xff
comma
multiline_comment|/* SLOT:  4, AD:15 */
l_int|14
comma
multiline_comment|/* M5229 ide ISA irq */
multiline_comment|/* SLOT:  5, AD:16 */
id|VRC5477_IRQ_INTD
comma
multiline_comment|/* slot 3 */
multiline_comment|/* SLOT:  6, AD:17 */
id|VRC5477_IRQ_INTA
comma
multiline_comment|/* slot 4 */
multiline_comment|/* SLOT:  7, AD:18 */
id|VRC5477_IRQ_INTD
comma
multiline_comment|/* slot 5 */
multiline_comment|/* SLOT:  8, AD:19 */
l_int|0
comma
multiline_comment|/* M5457 modem nop */
multiline_comment|/* SLOT:  9, AD:20 */
id|VRC5477_IRQ_INTA
comma
multiline_comment|/* slot 2 */
multiline_comment|/* SLOT: 10, AD:21 */
l_int|0xff
comma
multiline_comment|/* SLOT: 11, AD:22 */
l_int|0xff
comma
multiline_comment|/* SLOT: 12, AD:23 */
l_int|0xff
comma
multiline_comment|/* SLOT: 13, AD:24 */
l_int|0xff
comma
multiline_comment|/* SLOT: 14, AD:25 */
l_int|0xff
comma
multiline_comment|/* SLOT: 15, AD:26 */
l_int|0xff
comma
multiline_comment|/* SLOT: 16, AD:27 */
l_int|0xff
comma
multiline_comment|/* SLOT: 17, AD:28 */
l_int|0
comma
multiline_comment|/* M7101 PMU nop */
multiline_comment|/* SLOT: 18, AD:29 */
id|VRC5477_IRQ_IOPCI_INTC
comma
multiline_comment|/* vrc5477 ac97 */
multiline_comment|/* SLOT: 19, AD:30 */
id|VRC5477_IRQ_IOPCI_INTB
comma
multiline_comment|/* vrc5477 usb peri */
multiline_comment|/* SLOT: 20, AD:31 */
id|VRC5477_IRQ_IOPCI_INTA
comma
multiline_comment|/* vrc5477 usb host */
)brace
suffix:semicolon
DECL|function|pcibios_fixup_irqs
r_void
id|__init
id|pcibios_fixup_irqs
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|slot_num
suffix:semicolon
r_int
r_char
op_star
id|slot_irq_map
suffix:semicolon
r_int
r_char
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|mips_machtype
op_eq
id|MACH_NEC_ROCKHOPPERII
)paren
id|slot_irq_map
op_assign
id|rockhopperII_irq_map
suffix:semicolon
r_else
id|slot_irq_map
op_assign
id|irq_map
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|slot_num
op_assign
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
id|irq
op_assign
id|slot_irq_map
(braket
id|slot_num
)braket
suffix:semicolon
id|db_assert
c_func
(paren
id|slot_num
OL
id|MAX_SLOT_NUM
)paren
suffix:semicolon
id|db_assert
c_func
(paren
id|irq
op_ne
l_int|0xff
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
id|irq
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|mips_machtype
op_eq
id|MACH_NEC_ROCKHOPPERII
)paren
(brace
multiline_comment|/* hack to distinquish overlapping slot 20s, one&n;&t;&t;&t; * on bus 0 (ALI USB on the M1535 on the backplane), &n;&t;&t;&t; * and one on bus 2 (NEC USB controller on the CPU board)&n;&t;&t;&t; * Make the M1535 USB - ISA IRQ number 9.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|slot_num
op_eq
l_int|20
op_logical_and
id|dev-&gt;bus-&gt;number
op_eq
l_int|0
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
l_int|9
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
l_int|9
suffix:semicolon
)brace
)brace
)brace
)brace
macro_line|#if defined(CONFIG_RUNTIME_DEBUG)
r_extern
r_void
id|jsun_scan_pci_bus
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|jsun_assign_pci_resource
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|function|ddb_pci_reset_bus
r_void
id|ddb_pci_reset_bus
c_func
(paren
r_void
)paren
(brace
id|u32
id|temp
suffix:semicolon
multiline_comment|/*&n;&t; * I am not sure about the &quot;official&quot; procedure, the following&n;&t; * steps work as far as I know:&n;&t; * We first set PCI cold reset bit (bit 31) in PCICTRL-H.&n;&t; * Then we clear the PCI warm reset bit (bit 30) to 0 in PCICTRL-H.&n;&t; * The same is true for both PCI channels.&n;&t; */
id|temp
op_assign
id|ddb_in32
c_func
(paren
id|DDB_PCICTL0_H
)paren
suffix:semicolon
id|temp
op_or_assign
l_int|0x80000000
suffix:semicolon
id|ddb_out32
c_func
(paren
id|DDB_PCICTL0_H
comma
id|temp
)paren
suffix:semicolon
id|temp
op_and_assign
op_complement
l_int|0xc0000000
suffix:semicolon
id|ddb_out32
c_func
(paren
id|DDB_PCICTL0_H
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
id|ddb_in32
c_func
(paren
id|DDB_PCICTL1_H
)paren
suffix:semicolon
id|temp
op_or_assign
l_int|0x80000000
suffix:semicolon
id|ddb_out32
c_func
(paren
id|DDB_PCICTL1_H
comma
id|temp
)paren
suffix:semicolon
id|temp
op_and_assign
op_complement
l_int|0xc0000000
suffix:semicolon
id|ddb_out32
c_func
(paren
id|DDB_PCICTL1_H
comma
id|temp
)paren
suffix:semicolon
)brace
DECL|function|pcibios_assign_all_busses
r_int
id|__init
r_int
id|pcibios_assign_all_busses
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* we hope pci_auto has assigned the bus numbers to all buses */
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pcibios_fixup_resources
r_void
id|__init
id|pcibios_fixup_resources
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
)brace
multiline_comment|/* &n; * fixup baseboard AMD chip so that tx does not underflow.&n; *&t;bcr_18 |= 0x0800&n; * This sets NOUFLO bit which makes tx not start until whole pkt &n; * is fetched to the chip.&n; */
DECL|macro|PCNET32_WIO_RDP
mdefine_line|#define&t;PCNET32_WIO_RDP         0x10
DECL|macro|PCNET32_WIO_RAP
mdefine_line|#define&t;PCNET32_WIO_RAP&t;&t;0x12
DECL|macro|PCNET32_WIO_RESET
mdefine_line|#define&t;PCNET32_WIO_RESET       0x14
DECL|macro|PCNET32_WIO_BDP
mdefine_line|#define&t;PCNET32_WIO_BDP         0x16
DECL|function|fix_amd_lance
r_void
id|__init
id|fix_amd_lance
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
r_int
id|ioaddr
suffix:semicolon
id|u16
id|temp
suffix:semicolon
id|ioaddr
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|inw
c_func
(paren
id|ioaddr
op_plus
id|PCNET32_WIO_RESET
)paren
suffix:semicolon
multiline_comment|/* reset chip */
multiline_comment|/* bcr_18 |= 0x0800 */
id|outw
c_func
(paren
l_int|18
comma
id|ioaddr
op_plus
id|PCNET32_WIO_RAP
)paren
suffix:semicolon
id|temp
op_assign
id|inw
c_func
(paren
id|ioaddr
op_plus
id|PCNET32_WIO_BDP
)paren
suffix:semicolon
id|temp
op_or_assign
l_int|0x0800
suffix:semicolon
id|outw
c_func
(paren
l_int|18
comma
id|ioaddr
op_plus
id|PCNET32_WIO_RAP
)paren
suffix:semicolon
id|outw
c_func
(paren
id|temp
comma
id|ioaddr
op_plus
id|PCNET32_WIO_BDP
)paren
suffix:semicolon
)brace
DECL|function|pcibios_fixup
r_void
id|__init
id|pcibios_fixup
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|mips_machtype
op_ne
id|MACH_NEC_ROCKHOPPERII
)paren
r_return
suffix:semicolon
DECL|macro|M1535_CONFIG_PORT
mdefine_line|#define M1535_CONFIG_PORT 0x3f0
DECL|macro|M1535_INDEX_PORT
mdefine_line|#define M1535_INDEX_PORT  0x3f0
DECL|macro|M1535_DATA_PORT
mdefine_line|#define M1535_DATA_PORT   0x3f1
id|printk
c_func
(paren
l_string|&quot;Configuring ALI M1535 Super I/O mouse irq.&bslash;n&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
id|M1535_CONFIG_PORT
comma
l_int|2
comma
l_string|&quot;M1535 Super I/O config&quot;
)paren
suffix:semicolon
multiline_comment|/* Enter config mode. */
id|outb
c_func
(paren
l_int|0x51
comma
id|M1535_CONFIG_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x23
comma
id|M1535_CONFIG_PORT
)paren
suffix:semicolon
multiline_comment|/* Select device 0x07. */
id|outb
c_func
(paren
l_int|0x07
comma
id|M1535_INDEX_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x07
comma
id|M1535_DATA_PORT
)paren
suffix:semicolon
multiline_comment|/* Set mouse irq (register 0x72) to 12. */
id|outb
c_func
(paren
l_int|0x72
comma
id|M1535_INDEX_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x0c
comma
id|M1535_DATA_PORT
)paren
suffix:semicolon
multiline_comment|/* Exit config mode. */
id|outb
c_func
(paren
l_int|0xbb
comma
id|M1535_CONFIG_PORT
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_AL
)paren
r_if
c_cond
(paren
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_AL_M1535
op_logical_or
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_AL_M1533
)paren
(brace
id|u8
id|old
suffix:semicolon
id|printk
(paren
l_string|&quot;Enabling ALI M1533/35 PS2 keyboard/mouse.&bslash;n&quot;
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x41
comma
op_amp
id|old
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x41
comma
id|old
op_or
l_int|0xd0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_AMD
op_logical_and
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_AMD_LANCE
)paren
id|fix_amd_lance
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
eof
