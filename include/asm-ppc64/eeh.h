multiline_comment|/* &n; * eeh.h&n; * Copyright (C) 2001  Dave Engebretsen &amp; Todd Inglett IBM Corporation.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
multiline_comment|/* Start Change Log&n; * 2001/10/27 : engebret : Created.&n; * End Change Log &n; */
macro_line|#ifndef _EEH_H
DECL|macro|_EEH_H
mdefine_line|#define _EEH_H
macro_line|#include &lt;linux/string.h&gt;
r_struct
id|pci_dev
suffix:semicolon
multiline_comment|/* I/O addresses are converted to EEH &quot;tokens&quot; such that a driver will cause&n; * a bad page fault if the address is used directly (i.e. these addresses are&n; * never actually mapped.  Translation between IO &lt;-&gt; EEH region is 1 to 1.&n; */
DECL|macro|IO_TOKEN_TO_ADDR
mdefine_line|#define IO_TOKEN_TO_ADDR(token) (((unsigned long)(token) &amp; ~(0xfUL &lt;&lt; REGION_SHIFT)) | &bslash;&n;&t;&t;&t;&t;(IO_REGION_ID &lt;&lt; REGION_SHIFT))
DECL|macro|IO_ADDR_TO_TOKEN
mdefine_line|#define IO_ADDR_TO_TOKEN(addr) (((unsigned long)(addr) &amp; ~(0xfUL &lt;&lt; REGION_SHIFT)) | &bslash;&n;&t;&t;&t;&t;(EEH_REGION_ID &lt;&lt; REGION_SHIFT))
multiline_comment|/* Values for eeh_mode bits in device_node */
DECL|macro|EEH_MODE_SUPPORTED
mdefine_line|#define EEH_MODE_SUPPORTED&t;(1&lt;&lt;0)
DECL|macro|EEH_MODE_NOCHECK
mdefine_line|#define EEH_MODE_NOCHECK&t;(1&lt;&lt;1)
multiline_comment|/* This is for profiling only */
r_extern
r_int
r_int
id|eeh_total_mmio_ffs
suffix:semicolon
r_void
id|eeh_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|eeh_get_state
c_func
(paren
r_int
r_int
id|ea
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
multiline_comment|/* Given a PCI device check if eeh should be configured or not.&n; * This may look at firmware properties and/or kernel cmdline options.&n; */
r_int
id|is_eeh_configured
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Translate a (possible) eeh token to a physical addr.&n; * If &quot;token&quot; is not an eeh token it is simply returned under&n; * the assumption that it is already a physical addr.&n; */
r_int
r_int
id|eeh_token_to_phys
c_func
(paren
r_int
r_int
id|token
)paren
suffix:semicolon
multiline_comment|/* EEH_POSSIBLE_ERROR() -- test for possible MMIO failure.&n; *&n; * Order this macro for performance.&n; * If EEH is off for a device and it is a memory BAR, ioremap will&n; * map it to the IOREGION.  In this case addr == vaddr and since these&n; * should be in registers we compare them first.  Next we check for&n; * ff&squot;s which indicates a (very) possible failure.&n; *&n; * If this macro yields TRUE, the caller relays to eeh_check_failure()&n; * which does further tests out of line.&n; */
multiline_comment|/* #define EEH_POSSIBLE_IO_ERROR(val) (~(val) == 0) */
multiline_comment|/* #define EEH_POSSIBLE_ERROR(addr, vaddr, val) ((vaddr) != (addr) &amp;&amp; EEH_POSSIBLE_IO_ERROR(val) */
multiline_comment|/* This version is rearranged to collect some profiling data */
DECL|macro|EEH_POSSIBLE_IO_ERROR
mdefine_line|#define EEH_POSSIBLE_IO_ERROR(val) (~(val) == 0 &amp;&amp; ++eeh_total_mmio_ffs)
DECL|macro|EEH_POSSIBLE_ERROR
mdefine_line|#define EEH_POSSIBLE_ERROR(addr, vaddr, val) (EEH_POSSIBLE_IO_ERROR(val) &amp;&amp; (vaddr) != (addr))
multiline_comment|/* &n; * MMIO read/write operations with EEH support.&n; *&n; * addr: 64b token of the form 0xA0PPBBDDyyyyyyyy&n; *       0xA0     : Unmapped MMIO region&n; *       PP       : PHB index (starting at zero)&n; *&t; BB&t;  : PCI Bus number under given PHB&n; *&t; DD&t;  : PCI devfn under given bus&n; *       yyyyyyyy : Virtual address offset&n; * &n; * An actual virtual address is produced from this token&n; * by masking into the form:&n; *   0xE0000000yyyyyyyy&n; */
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
multiline_comment|/* look for ffff&squot;s here at dest[n] */
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
multiline_comment|/* The I/O macros must handle ISA ports as well as PCI I/O bars.&n; * ISA does not implement EEH and ISA may not exist in the system.&n; * For PCI we check for EEH failures.&n; */
DECL|macro|_IO_IS_ISA
mdefine_line|#define _IO_IS_ISA(port) ((port) &lt; 0x10000)
DECL|macro|_IO_HAS_ISA_BUS
mdefine_line|#define _IO_HAS_ISA_BUS&t;(isa_io_base != 0)
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
id|_IO_IS_ISA
c_func
(paren
id|port
)paren
op_logical_and
op_logical_neg
id|_IO_HAS_ISA_BUS
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
op_logical_neg
id|_IO_IS_ISA
c_func
(paren
id|port
)paren
op_logical_and
id|EEH_POSSIBLE_IO_ERROR
c_func
(paren
id|val
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
op_plus
id|pci_io_base
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
op_logical_neg
id|_IO_IS_ISA
c_func
(paren
id|port
)paren
op_logical_or
id|_IO_HAS_ISA_BUS
)paren
r_return
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
id|_IO_IS_ISA
c_func
(paren
id|port
)paren
op_logical_and
op_logical_neg
id|_IO_HAS_ISA_BUS
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
op_logical_neg
id|_IO_IS_ISA
c_func
(paren
id|port
)paren
op_logical_and
id|EEH_POSSIBLE_IO_ERROR
c_func
(paren
id|val
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
op_plus
id|pci_io_base
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
op_logical_neg
id|_IO_IS_ISA
c_func
(paren
id|port
)paren
op_logical_or
id|_IO_HAS_ISA_BUS
)paren
r_return
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
id|_IO_IS_ISA
c_func
(paren
id|port
)paren
op_logical_and
op_logical_neg
id|_IO_HAS_ISA_BUS
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
op_logical_neg
id|_IO_IS_ISA
c_func
(paren
id|port
)paren
op_logical_and
id|EEH_POSSIBLE_IO_ERROR
c_func
(paren
id|val
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
op_plus
id|pci_io_base
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
op_logical_neg
id|_IO_IS_ISA
c_func
(paren
id|port
)paren
op_logical_or
id|_IO_HAS_ISA_BUS
)paren
r_return
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
macro_line|#endif /* _EEH_H */
eof
