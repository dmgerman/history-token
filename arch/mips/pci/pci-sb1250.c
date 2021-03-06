multiline_comment|/*&n; * Copyright (C) 2001,2002,2003 Broadcom Corporation&n; * Copyright (C) 2004 by Ralf Baechle (ralf@linux-mips.org)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
multiline_comment|/*&n; * BCM1250-specific PCI support&n; *&n; * This module provides the glue between Linux&squot;s PCI subsystem&n; * and the hardware.  We basically provide glue for accessing&n; * configuration space, and set up the translation for I/O&n; * space accesses.&n; *&n; * To access configuration space, we use ioremap.  In the 32-bit&n; * kernel, this consumes either 4 or 8 page table pages, and 16MB of&n; * kernel mapped memory.  Hopefully neither of these should be a huge&n; * problem.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_defs.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_regs.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_scd.h&gt;
macro_line|#include &lt;asm/sibyte/board.h&gt;
multiline_comment|/*&n; * Macros for calculating offsets into config space given a device&n; * structure or dev/fun/reg&n; */
DECL|macro|CFGOFFSET
mdefine_line|#define CFGOFFSET(bus,devfn,where) (((bus)&lt;&lt;16) + ((devfn)&lt;&lt;8) + (where))
DECL|macro|CFGADDR
mdefine_line|#define CFGADDR(bus,devfn,where)   CFGOFFSET((bus)-&gt;number,(devfn),where)
DECL|variable|cfg_space
r_static
r_void
op_star
id|cfg_space
suffix:semicolon
DECL|macro|PCI_BUS_ENABLED
mdefine_line|#define PCI_BUS_ENABLED&t;1
DECL|macro|LDT_BUS_ENABLED
mdefine_line|#define LDT_BUS_ENABLED&t;2
DECL|macro|PCI_DEVICE_MODE
mdefine_line|#define PCI_DEVICE_MODE&t;4
DECL|variable|sb1250_bus_status
r_static
r_int
id|sb1250_bus_status
op_assign
l_int|0
suffix:semicolon
DECL|macro|PCI_BRIDGE_DEVICE
mdefine_line|#define PCI_BRIDGE_DEVICE  0
DECL|macro|LDT_BRIDGE_DEVICE
mdefine_line|#define LDT_BRIDGE_DEVICE  1
macro_line|#ifdef CONFIG_SIBYTE_HAS_LDT
multiline_comment|/*&n; * HT&squot;s level-sensitive interrupts require EOI, which is generated&n; * through a 4MB memory-mapped region&n; */
DECL|variable|ldt_eoi_space
r_int
r_int
id|ldt_eoi_space
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Read/write 32-bit values in config space.&n; */
DECL|function|READCFG32
r_static
r_inline
id|u32
id|READCFG32
c_func
(paren
id|u32
id|addr
)paren
(brace
r_return
op_star
(paren
id|u32
op_star
)paren
(paren
id|cfg_space
op_plus
(paren
id|addr
op_amp
op_complement
l_int|3
)paren
)paren
suffix:semicolon
)brace
DECL|function|WRITECFG32
r_static
r_inline
r_void
id|WRITECFG32
c_func
(paren
id|u32
id|addr
comma
id|u32
id|data
)paren
(brace
op_star
(paren
id|u32
op_star
)paren
(paren
id|cfg_space
op_plus
(paren
id|addr
op_amp
op_complement
l_int|3
)paren
)paren
op_assign
id|data
suffix:semicolon
)brace
DECL|function|pcibios_map_irq
r_int
id|pcibios_map_irq
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
r_return
id|dev-&gt;irq
suffix:semicolon
)brace
multiline_comment|/* Do platform specific device initialization at pci_enable_device() time */
DECL|function|pcibios_plat_dev_init
r_int
id|pcibios_plat_dev_init
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Some checks before doing config cycles:&n; * In PCI Device Mode, hide everything on bus 0 except the LDT host&n; * bridge.  Otherwise, access is controlled by bridge MasterEn bits.&n; */
DECL|function|sb1250_pci_can_access
r_static
r_int
id|sb1250_pci_can_access
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
id|devfn
)paren
(brace
id|u32
id|devno
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb1250_bus_status
op_amp
(paren
id|PCI_BUS_ENABLED
op_or
id|PCI_DEVICE_MODE
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bus-&gt;number
op_eq
l_int|0
)paren
(brace
id|devno
op_assign
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|devno
op_eq
id|LDT_BRIDGE_DEVICE
)paren
r_return
(paren
id|sb1250_bus_status
op_amp
id|LDT_BUS_ENABLED
)paren
op_ne
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sb1250_bus_status
op_amp
id|PCI_DEVICE_MODE
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Read/write access functions for various sizes of values&n; * in config space.  Return all 1&squot;s for disallowed accesses&n; * for a kludgy but adequate simulation of master aborts.&n; */
DECL|function|sb1250_pcibios_read
r_static
r_int
id|sb1250_pcibios_read
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
id|val
)paren
(brace
id|u32
id|data
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|size
op_eq
l_int|2
)paren
op_logical_and
(paren
id|where
op_amp
l_int|1
)paren
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|size
op_eq
l_int|4
)paren
op_logical_and
(paren
id|where
op_amp
l_int|3
)paren
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
r_if
c_cond
(paren
id|sb1250_pci_can_access
c_func
(paren
id|bus
comma
id|devfn
)paren
)paren
id|data
op_assign
id|READCFG32
c_func
(paren
id|CFGADDR
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
)paren
)paren
suffix:semicolon
r_else
id|data
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|1
)paren
op_star
id|val
op_assign
(paren
id|data
op_rshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
op_amp
l_int|0xff
suffix:semicolon
r_else
r_if
c_cond
(paren
id|size
op_eq
l_int|2
)paren
op_star
id|val
op_assign
(paren
id|data
op_rshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
op_amp
l_int|0xffff
suffix:semicolon
r_else
op_star
id|val
op_assign
id|data
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|sb1250_pcibios_write
r_static
r_int
id|sb1250_pcibios_write
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
id|val
)paren
(brace
id|u32
id|cfgaddr
op_assign
id|CFGADDR
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
)paren
suffix:semicolon
id|u32
id|data
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|size
op_eq
l_int|2
)paren
op_logical_and
(paren
id|where
op_amp
l_int|1
)paren
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|size
op_eq
l_int|4
)paren
op_logical_and
(paren
id|where
op_amp
l_int|3
)paren
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb1250_pci_can_access
c_func
(paren
id|bus
comma
id|devfn
)paren
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
id|data
op_assign
id|READCFG32
c_func
(paren
id|cfgaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|1
)paren
id|data
op_assign
(paren
id|data
op_amp
op_complement
(paren
l_int|0xff
op_lshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
)paren
op_or
(paren
id|val
op_lshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|size
op_eq
l_int|2
)paren
id|data
op_assign
(paren
id|data
op_amp
op_complement
(paren
l_int|0xffff
op_lshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
)paren
op_or
(paren
id|val
op_lshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
r_else
id|data
op_assign
id|val
suffix:semicolon
id|WRITECFG32
c_func
(paren
id|cfgaddr
comma
id|data
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|sb1250_pci_ops
r_struct
id|pci_ops
id|sb1250_pci_ops
op_assign
(brace
dot
id|read
op_assign
id|sb1250_pcibios_read
comma
dot
id|write
op_assign
id|sb1250_pcibios_write
comma
)brace
suffix:semicolon
DECL|variable|sb1250_mem_resource
r_static
r_struct
id|resource
id|sb1250_mem_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;SB1250 PCI MEM&quot;
comma
dot
id|start
op_assign
l_int|0x40000000UL
comma
dot
id|end
op_assign
l_int|0x5fffffffUL
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
DECL|variable|sb1250_io_resource
r_static
r_struct
id|resource
id|sb1250_io_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;SB1250 PCI I/O&quot;
comma
dot
id|start
op_assign
l_int|0x00000000UL
comma
dot
id|end
op_assign
l_int|0x01ffffffUL
comma
dot
id|flags
op_assign
id|IORESOURCE_IO
comma
)brace
suffix:semicolon
DECL|variable|sb1250_controller
r_struct
id|pci_controller
id|sb1250_controller
op_assign
(brace
dot
id|pci_ops
op_assign
op_amp
id|sb1250_pci_ops
comma
dot
id|mem_resource
op_assign
op_amp
id|sb1250_mem_resource
comma
dot
id|io_resource
op_assign
op_amp
id|sb1250_io_resource
comma
)brace
suffix:semicolon
DECL|function|sb1250_pcibios_init
r_static
r_int
id|__init
id|sb1250_pcibios_init
c_func
(paren
r_void
)paren
(brace
r_uint32
id|cmdreg
suffix:semicolon
r_uint64
id|reg
suffix:semicolon
r_extern
r_int
id|pci_probe_only
suffix:semicolon
multiline_comment|/* CFE will assign PCI resources */
id|pci_probe_only
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Avoid ISA compat ranges.  */
id|PCIBIOS_MIN_IO
op_assign
l_int|0x00008000UL
suffix:semicolon
id|PCIBIOS_MIN_MEM
op_assign
l_int|0x01000000UL
suffix:semicolon
multiline_comment|/* Set I/O resource limits.  */
id|ioport_resource.end
op_assign
l_int|0x01ffffffUL
suffix:semicolon
multiline_comment|/* 32MB accessible by sb1250 */
id|iomem_resource.end
op_assign
l_int|0xffffffffUL
suffix:semicolon
multiline_comment|/* no HT support yet */
id|cfg_space
op_assign
id|ioremap
c_func
(paren
id|A_PHYS_LDTPCI_CFG_MATCH_BITS
comma
l_int|16
op_star
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * See if the PCI bus has been configured by the firmware.&n;&t; */
id|reg
op_assign
op_star
(paren
(paren
r_volatile
r_uint64
op_star
)paren
id|IOADDR
c_func
(paren
id|A_SCD_SYSTEM_CFG
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|reg
op_amp
id|M_SYS_PCI_HOST
)paren
)paren
(brace
id|sb1250_bus_status
op_or_assign
id|PCI_DEVICE_MODE
suffix:semicolon
)brace
r_else
(brace
id|cmdreg
op_assign
id|READCFG32
c_func
(paren
id|CFGOFFSET
(paren
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
id|PCI_BRIDGE_DEVICE
comma
l_int|0
)paren
comma
id|PCI_COMMAND
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cmdreg
op_amp
id|PCI_COMMAND_MASTER
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;PCI: Skipping PCI probe.  Bus is not initialized.&bslash;n&quot;
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|cfg_space
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|sb1250_bus_status
op_or_assign
id|PCI_BUS_ENABLED
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Establish mappings in KSEG2 (kernel virtual) to PCI I/O&n;&t; * space.  Use &quot;match bytes&quot; policy to make everything look&n;&t; * little-endian.  So, you need to also set&n;&t; * CONFIG_SWAP_IO_SPACE, but this is the combination that&n;&t; * works correctly with most of Linux&squot;s drivers.&n;&t; * XXX ehs: Should this happen in PCI Device mode?&n;&t; */
id|set_io_port_base
c_func
(paren
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|A_PHYS_LDTPCI_IO_MATCH_BYTES
comma
l_int|65536
)paren
)paren
suffix:semicolon
id|isa_slot_offset
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|A_PHYS_LDTPCI_IO_MATCH_BYTES_32
comma
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SIBYTE_HAS_LDT
multiline_comment|/*&n;&t; * Also check the LDT bridge&squot;s enable, just in case we didn&squot;t&n;&t; * initialize that one.&n;&t; */
id|cmdreg
op_assign
id|READCFG32
c_func
(paren
id|CFGOFFSET
c_func
(paren
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
id|LDT_BRIDGE_DEVICE
comma
l_int|0
)paren
comma
id|PCI_COMMAND
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmdreg
op_amp
id|PCI_COMMAND_MASTER
)paren
(brace
id|sb1250_bus_status
op_or_assign
id|LDT_BUS_ENABLED
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Need bits 23:16 to convey vector number.  Note that&n;&t;&t; * this consumes 4MB of kernel-mapped memory&n;&t;&t; * (Kseg2/Kseg3) for 32-bit kernel.&n;&t;&t; */
id|ldt_eoi_space
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|A_PHYS_LDT_SPECIAL_MATCH_BYTES
comma
l_int|4
op_star
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
)brace
macro_line|#endif
id|register_pci_controller
c_func
(paren
op_amp
id|sb1250_controller
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_VGA_CONSOLE
id|take_over_console
c_func
(paren
op_amp
id|vga_con
comma
l_int|0
comma
id|MAX_NR_CONSOLES
op_minus
l_int|1
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sb1250_pcibios_init
id|arch_initcall
c_func
(paren
id|sb1250_pcibios_init
)paren
suffix:semicolon
eof
