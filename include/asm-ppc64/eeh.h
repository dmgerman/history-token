multiline_comment|/* &n; * eeh.h&n; * Copyright (C) 2001  Dave Engebretsen &amp; Todd Inglett IBM Corporation.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef _PPC64_EEH_H
DECL|macro|_PPC64_EEH_H
mdefine_line|#define _PPC64_EEH_H
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
r_struct
id|pci_dev
suffix:semicolon
r_struct
id|device_node
suffix:semicolon
multiline_comment|/* I/O addresses are converted to EEH &quot;tokens&quot; such that a driver will cause&n; * a bad page fault if the address is used directly (i.e. these addresses are&n; * never actually mapped.  Translation between IO &lt;-&gt; EEH region is 1 to 1.&n; */
DECL|macro|IO_TOKEN_TO_ADDR
mdefine_line|#define IO_TOKEN_TO_ADDR(token) &bslash;&n;&t;(((unsigned long)(token) &amp; ~(0xfUL &lt;&lt; REGION_SHIFT)) | &bslash;&n;&t;(IO_REGION_ID &lt;&lt; REGION_SHIFT))
DECL|macro|IO_ADDR_TO_TOKEN
mdefine_line|#define IO_ADDR_TO_TOKEN(addr) &bslash;&n;&t;(((unsigned long)(addr) &amp; ~(0xfUL &lt;&lt; REGION_SHIFT)) | &bslash;&n;&t;(EEH_REGION_ID &lt;&lt; REGION_SHIFT))
multiline_comment|/* Values for eeh_mode bits in device_node */
DECL|macro|EEH_MODE_SUPPORTED
mdefine_line|#define EEH_MODE_SUPPORTED&t;(1&lt;&lt;0)
DECL|macro|EEH_MODE_NOCHECK
mdefine_line|#define EEH_MODE_NOCHECK&t;(1&lt;&lt;1)
r_extern
r_void
id|__init
id|eeh_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|eeh_check_failure
c_func
(paren
r_void
op_star
id|token
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_void
op_star
id|eeh_ioremap
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|vaddr
)paren
suffix:semicolon
r_void
id|__init
id|pci_addr_cache_build
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/**&n; * eeh_add_device_early&n; * eeh_add_device_late&n; *&n; * Perform eeh initialization for devices added after boot.&n; * Call eeh_add_device_early before doing any i/o to the&n; * device (including config space i/o).  Call eeh_add_device_late&n; * to finish the eeh setup for this device.&n; */
r_struct
id|device_node
suffix:semicolon
r_void
id|eeh_add_device_early
c_func
(paren
r_struct
id|device_node
op_star
)paren
suffix:semicolon
r_void
id|eeh_add_device_late
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
multiline_comment|/**&n; * eeh_remove_device - undo EEH setup for the indicated pci device&n; * @dev: pci device to be removed&n; *&n; * This routine should be when a device is removed from a running&n; * system (e.g. by hotplug or dlpar).&n; */
r_void
id|eeh_remove_device
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
DECL|macro|EEH_DISABLE
mdefine_line|#define EEH_DISABLE&t;&t;0
DECL|macro|EEH_ENABLE
mdefine_line|#define EEH_ENABLE&t;&t;1
DECL|macro|EEH_RELEASE_LOADSTORE
mdefine_line|#define EEH_RELEASE_LOADSTORE&t;2
DECL|macro|EEH_RELEASE_DMA
mdefine_line|#define EEH_RELEASE_DMA&t;&t;3
r_int
id|eeh_set_option
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|options
)paren
suffix:semicolon
multiline_comment|/*&n; * EEH_POSSIBLE_ERROR() -- test for possible MMIO failure.&n; *&n; * Order this macro for performance.&n; * If EEH is off for a device and it is a memory BAR, ioremap will&n; * map it to the IOREGION.  In this case addr == vaddr and since these&n; * should be in registers we compare them first.  Next we check for&n; * ff&squot;s which indicates a (very) possible failure.&n; *&n; * If this macro yields TRUE, the caller relays to eeh_check_failure()&n; * which does further tests out of line.&n; */
DECL|macro|EEH_POSSIBLE_IO_ERROR
mdefine_line|#define EEH_POSSIBLE_IO_ERROR(val, type)&t;((val) == (type)~0)
multiline_comment|/* The vaddr will equal the addr if EEH checking is disabled for&n; * this device.  This is because eeh_ioremap() will not have&n; * remapped to 0xA0, and thus both vaddr and addr will be 0xE0...&n; */
DECL|macro|EEH_POSSIBLE_ERROR
mdefine_line|#define EEH_POSSIBLE_ERROR(addr, vaddr, val, type) &bslash;&n;&t;&t;((vaddr) != (addr) &amp;&amp; EEH_POSSIBLE_IO_ERROR(val, type))
multiline_comment|/* &n; * MMIO read/write operations with EEH support.&n; */
DECL|function|eeh_readb
r_static
r_inline
id|u8
id|eeh_readb
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_volatile
id|u8
op_star
id|vaddr
op_assign
(paren
r_volatile
id|u8
op_star
)paren
id|IO_TOKEN_TO_ADDR
c_func
(paren
id|addr
)paren
suffix:semicolon
id|u8
id|val
op_assign
id|in_8
c_func
(paren
id|vaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|EEH_POSSIBLE_ERROR
c_func
(paren
id|addr
comma
id|vaddr
comma
id|val
comma
id|u8
)paren
)paren
r_return
id|eeh_check_failure
c_func
(paren
id|addr
comma
id|val
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|eeh_writeb
r_static
r_inline
r_void
id|eeh_writeb
c_func
(paren
id|u8
id|val
comma
r_void
op_star
id|addr
)paren
(brace
r_volatile
id|u8
op_star
id|vaddr
op_assign
(paren
r_volatile
id|u8
op_star
)paren
id|IO_TOKEN_TO_ADDR
c_func
(paren
id|addr
)paren
suffix:semicolon
id|out_8
c_func
(paren
id|vaddr
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|eeh_readw
r_static
r_inline
id|u16
id|eeh_readw
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_volatile
id|u16
op_star
id|vaddr
op_assign
(paren
r_volatile
id|u16
op_star
)paren
id|IO_TOKEN_TO_ADDR
c_func
(paren
id|addr
)paren
suffix:semicolon
id|u16
id|val
op_assign
id|in_le16
c_func
(paren
id|vaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|EEH_POSSIBLE_ERROR
c_func
(paren
id|addr
comma
id|vaddr
comma
id|val
comma
id|u16
)paren
)paren
r_return
id|eeh_check_failure
c_func
(paren
id|addr
comma
id|val
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|eeh_writew
r_static
r_inline
r_void
id|eeh_writew
c_func
(paren
id|u16
id|val
comma
r_void
op_star
id|addr
)paren
(brace
r_volatile
id|u16
op_star
id|vaddr
op_assign
(paren
r_volatile
id|u16
op_star
)paren
id|IO_TOKEN_TO_ADDR
c_func
(paren
id|addr
)paren
suffix:semicolon
id|out_le16
c_func
(paren
id|vaddr
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|eeh_raw_readw
r_static
r_inline
id|u16
id|eeh_raw_readw
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_volatile
id|u16
op_star
id|vaddr
op_assign
(paren
r_volatile
id|u16
op_star
)paren
id|IO_TOKEN_TO_ADDR
c_func
(paren
id|addr
)paren
suffix:semicolon
id|u16
id|val
op_assign
id|in_be16
c_func
(paren
id|vaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|EEH_POSSIBLE_ERROR
c_func
(paren
id|addr
comma
id|vaddr
comma
id|val
comma
id|u16
)paren
)paren
r_return
id|eeh_check_failure
c_func
(paren
id|addr
comma
id|val
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|eeh_raw_writew
r_static
r_inline
r_void
id|eeh_raw_writew
c_func
(paren
id|u16
id|val
comma
r_void
op_star
id|addr
)paren
(brace
r_volatile
id|u16
op_star
id|vaddr
op_assign
(paren
r_volatile
id|u16
op_star
)paren
id|IO_TOKEN_TO_ADDR
c_func
(paren
id|addr
)paren
suffix:semicolon
id|out_be16
c_func
(paren
id|vaddr
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|eeh_readl
r_static
r_inline
id|u32
id|eeh_readl
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_volatile
id|u32
op_star
id|vaddr
op_assign
(paren
r_volatile
id|u32
op_star
)paren
id|IO_TOKEN_TO_ADDR
c_func
(paren
id|addr
)paren
suffix:semicolon
id|u32
id|val
op_assign
id|in_le32
c_func
(paren
id|vaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|EEH_POSSIBLE_ERROR
c_func
(paren
id|addr
comma
id|vaddr
comma
id|val
comma
id|u32
)paren
)paren
r_return
id|eeh_check_failure
c_func
(paren
id|addr
comma
id|val
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|eeh_writel
r_static
r_inline
r_void
id|eeh_writel
c_func
(paren
id|u32
id|val
comma
r_void
op_star
id|addr
)paren
(brace
r_volatile
id|u32
op_star
id|vaddr
op_assign
(paren
r_volatile
id|u32
op_star
)paren
id|IO_TOKEN_TO_ADDR
c_func
(paren
id|addr
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|vaddr
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|eeh_raw_readl
r_static
r_inline
id|u32
id|eeh_raw_readl
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_volatile
id|u32
op_star
id|vaddr
op_assign
(paren
r_volatile
id|u32
op_star
)paren
id|IO_TOKEN_TO_ADDR
c_func
(paren
id|addr
)paren
suffix:semicolon
id|u32
id|val
op_assign
id|in_be32
c_func
(paren
id|vaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|EEH_POSSIBLE_ERROR
c_func
(paren
id|addr
comma
id|vaddr
comma
id|val
comma
id|u32
)paren
)paren
r_return
id|eeh_check_failure
c_func
(paren
id|addr
comma
id|val
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|eeh_raw_writel
r_static
r_inline
r_void
id|eeh_raw_writel
c_func
(paren
id|u32
id|val
comma
r_void
op_star
id|addr
)paren
(brace
r_volatile
id|u32
op_star
id|vaddr
op_assign
(paren
r_volatile
id|u32
op_star
)paren
id|IO_TOKEN_TO_ADDR
c_func
(paren
id|addr
)paren
suffix:semicolon
id|out_be32
c_func
(paren
id|vaddr
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|eeh_readq
r_static
r_inline
id|u64
id|eeh_readq
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_volatile
id|u64
op_star
id|vaddr
op_assign
(paren
r_volatile
id|u64
op_star
)paren
id|IO_TOKEN_TO_ADDR
c_func
(paren
id|addr
)paren
suffix:semicolon
id|u64
id|val
op_assign
id|in_le64
c_func
(paren
id|vaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|EEH_POSSIBLE_ERROR
c_func
(paren
id|addr
comma
id|vaddr
comma
id|val
comma
id|u64
)paren
)paren
r_return
id|eeh_check_failure
c_func
(paren
id|addr
comma
id|val
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|eeh_writeq
r_static
r_inline
r_void
id|eeh_writeq
c_func
(paren
id|u64
id|val
comma
r_void
op_star
id|addr
)paren
(brace
r_volatile
id|u64
op_star
id|vaddr
op_assign
(paren
r_volatile
id|u64
op_star
)paren
id|IO_TOKEN_TO_ADDR
c_func
(paren
id|addr
)paren
suffix:semicolon
id|out_le64
c_func
(paren
id|vaddr
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|eeh_raw_readq
r_static
r_inline
id|u64
id|eeh_raw_readq
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_volatile
id|u64
op_star
id|vaddr
op_assign
(paren
r_volatile
id|u64
op_star
)paren
id|IO_TOKEN_TO_ADDR
c_func
(paren
id|addr
)paren
suffix:semicolon
id|u64
id|val
op_assign
id|in_be64
c_func
(paren
id|vaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|EEH_POSSIBLE_ERROR
c_func
(paren
id|addr
comma
id|vaddr
comma
id|val
comma
id|u64
)paren
)paren
r_return
id|eeh_check_failure
c_func
(paren
id|addr
comma
id|val
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|eeh_raw_writeq
r_static
r_inline
r_void
id|eeh_raw_writeq
c_func
(paren
id|u64
id|val
comma
r_void
op_star
id|addr
)paren
(brace
r_volatile
id|u64
op_star
id|vaddr
op_assign
(paren
r_volatile
id|u64
op_star
)paren
id|IO_TOKEN_TO_ADDR
c_func
(paren
id|addr
)paren
suffix:semicolon
id|out_be64
c_func
(paren
id|vaddr
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|eeh_memset_io
r_static
r_inline
r_void
id|eeh_memset_io
c_func
(paren
r_void
op_star
id|addr
comma
r_int
id|c
comma
r_int
r_int
id|n
)paren
(brace
r_void
op_star
id|vaddr
op_assign
(paren
r_void
op_star
)paren
id|IO_TOKEN_TO_ADDR
c_func
(paren
id|addr
)paren
suffix:semicolon
id|memset
c_func
(paren
id|vaddr
comma
id|c
comma
id|n
)paren
suffix:semicolon
)brace
DECL|function|eeh_memcpy_fromio
r_static
r_inline
r_void
id|eeh_memcpy_fromio
c_func
(paren
r_void
op_star
id|dest
comma
r_void
op_star
id|src
comma
r_int
r_int
id|n
)paren
(brace
r_void
op_star
id|vsrc
op_assign
(paren
r_void
op_star
)paren
id|IO_TOKEN_TO_ADDR
c_func
(paren
id|src
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dest
comma
id|vsrc
comma
id|n
)paren
suffix:semicolon
multiline_comment|/* Look for ffff&squot;s here at dest[n].  Assume that at least 4 bytes&n;&t; * were copied. Check all four bytes.&n;&t; */
r_if
c_cond
(paren
(paren
id|n
op_ge
l_int|4
)paren
op_logical_and
(paren
id|EEH_POSSIBLE_ERROR
c_func
(paren
id|src
comma
id|vsrc
comma
(paren
op_star
(paren
(paren
id|u32
op_star
)paren
id|dest
op_plus
id|n
op_minus
l_int|4
)paren
)paren
comma
id|u32
)paren
)paren
)paren
(brace
id|eeh_check_failure
c_func
(paren
id|src
comma
(paren
op_star
(paren
(paren
id|u32
op_star
)paren
id|dest
op_plus
id|n
op_minus
l_int|4
)paren
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|eeh_memcpy_toio
r_static
r_inline
r_void
id|eeh_memcpy_toio
c_func
(paren
r_void
op_star
id|dest
comma
r_void
op_star
id|src
comma
r_int
r_int
id|n
)paren
(brace
r_void
op_star
id|vdest
op_assign
(paren
r_void
op_star
)paren
id|IO_TOKEN_TO_ADDR
c_func
(paren
id|dest
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|vdest
comma
id|src
comma
id|n
)paren
suffix:semicolon
)brace
DECL|macro|MAX_ISA_PORT
mdefine_line|#define MAX_ISA_PORT 0x10000
r_extern
r_int
r_int
id|io_page_mask
suffix:semicolon
DECL|macro|_IO_IS_VALID
mdefine_line|#define _IO_IS_VALID(port) ((port) &gt;= MAX_ISA_PORT || (1 &lt;&lt; (port&gt;&gt;PAGE_SHIFT)) &amp; io_page_mask)
DECL|function|eeh_inb
r_static
r_inline
id|u8
id|eeh_inb
c_func
(paren
r_int
r_int
id|port
)paren
(brace
id|u8
id|val
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|_IO_IS_VALID
c_func
(paren
id|port
)paren
)paren
r_return
op_complement
l_int|0
suffix:semicolon
id|val
op_assign
id|in_8
c_func
(paren
(paren
id|u8
op_star
)paren
(paren
id|port
op_plus
id|pci_io_base
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|EEH_POSSIBLE_IO_ERROR
c_func
(paren
id|val
comma
id|u8
)paren
)paren
r_return
id|eeh_check_failure
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|port
)paren
comma
id|val
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|eeh_outb
r_static
r_inline
r_void
id|eeh_outb
c_func
(paren
id|u8
id|val
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|_IO_IS_VALID
c_func
(paren
id|port
)paren
)paren
id|out_8
c_func
(paren
(paren
id|u8
op_star
)paren
(paren
id|port
op_plus
id|pci_io_base
)paren
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|eeh_inw
r_static
r_inline
id|u16
id|eeh_inw
c_func
(paren
r_int
r_int
id|port
)paren
(brace
id|u16
id|val
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|_IO_IS_VALID
c_func
(paren
id|port
)paren
)paren
r_return
op_complement
l_int|0
suffix:semicolon
id|val
op_assign
id|in_le16
c_func
(paren
(paren
id|u16
op_star
)paren
(paren
id|port
op_plus
id|pci_io_base
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|EEH_POSSIBLE_IO_ERROR
c_func
(paren
id|val
comma
id|u16
)paren
)paren
r_return
id|eeh_check_failure
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|port
)paren
comma
id|val
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|eeh_outw
r_static
r_inline
r_void
id|eeh_outw
c_func
(paren
id|u16
id|val
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|_IO_IS_VALID
c_func
(paren
id|port
)paren
)paren
id|out_le16
c_func
(paren
(paren
id|u16
op_star
)paren
(paren
id|port
op_plus
id|pci_io_base
)paren
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|eeh_inl
r_static
r_inline
id|u32
id|eeh_inl
c_func
(paren
r_int
r_int
id|port
)paren
(brace
id|u32
id|val
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|_IO_IS_VALID
c_func
(paren
id|port
)paren
)paren
r_return
op_complement
l_int|0
suffix:semicolon
id|val
op_assign
id|in_le32
c_func
(paren
(paren
id|u32
op_star
)paren
(paren
id|port
op_plus
id|pci_io_base
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|EEH_POSSIBLE_IO_ERROR
c_func
(paren
id|val
comma
id|u32
)paren
)paren
r_return
id|eeh_check_failure
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|port
)paren
comma
id|val
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|eeh_outl
r_static
r_inline
r_void
id|eeh_outl
c_func
(paren
id|u32
id|val
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|_IO_IS_VALID
c_func
(paren
id|port
)paren
)paren
id|out_le32
c_func
(paren
(paren
id|u32
op_star
)paren
(paren
id|port
op_plus
id|pci_io_base
)paren
comma
id|val
)paren
suffix:semicolon
)brace
multiline_comment|/* in-string eeh macros */
DECL|function|eeh_insb
r_static
r_inline
r_void
id|eeh_insb
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
(brace
id|_insb
c_func
(paren
(paren
id|u8
op_star
)paren
(paren
id|port
op_plus
id|pci_io_base
)paren
comma
id|buf
comma
id|ns
)paren
suffix:semicolon
r_if
c_cond
(paren
id|EEH_POSSIBLE_IO_ERROR
c_func
(paren
(paren
op_star
(paren
(paren
(paren
id|u8
op_star
)paren
id|buf
)paren
op_plus
id|ns
op_minus
l_int|1
)paren
)paren
comma
id|u8
)paren
)paren
id|eeh_check_failure
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|port
)paren
comma
op_star
(paren
id|u8
op_star
)paren
id|buf
)paren
suffix:semicolon
)brace
DECL|function|eeh_insw_ns
r_static
r_inline
r_void
id|eeh_insw_ns
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
(brace
id|_insw_ns
c_func
(paren
(paren
id|u16
op_star
)paren
(paren
id|port
op_plus
id|pci_io_base
)paren
comma
id|buf
comma
id|ns
)paren
suffix:semicolon
r_if
c_cond
(paren
id|EEH_POSSIBLE_IO_ERROR
c_func
(paren
(paren
op_star
(paren
(paren
(paren
id|u16
op_star
)paren
id|buf
)paren
op_plus
id|ns
op_minus
l_int|1
)paren
)paren
comma
id|u16
)paren
)paren
id|eeh_check_failure
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|port
)paren
comma
op_star
(paren
id|u16
op_star
)paren
id|buf
)paren
suffix:semicolon
)brace
DECL|function|eeh_insl_ns
r_static
r_inline
r_void
id|eeh_insl_ns
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|nl
)paren
(brace
id|_insl_ns
c_func
(paren
(paren
id|u32
op_star
)paren
(paren
id|port
op_plus
id|pci_io_base
)paren
comma
id|buf
comma
id|nl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|EEH_POSSIBLE_IO_ERROR
c_func
(paren
(paren
op_star
(paren
(paren
(paren
id|u32
op_star
)paren
id|buf
)paren
op_plus
id|nl
op_minus
l_int|1
)paren
)paren
comma
id|u32
)paren
)paren
id|eeh_check_failure
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|port
)paren
comma
op_star
(paren
id|u32
op_star
)paren
id|buf
)paren
suffix:semicolon
)brace
macro_line|#endif /* _PPC64_EEH_H */
eof
