multiline_comment|/* $Id: io.h,v 1.47 2001/12/13 10:36:02 davem Exp $ */
macro_line|#ifndef __SPARC64_IO_H
DECL|macro|__SPARC64_IO_H
mdefine_line|#define __SPARC64_IO_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/page.h&gt;      /* IO address mapping routines need this */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
multiline_comment|/* PC crapola... */
DECL|macro|__SLOW_DOWN_IO
mdefine_line|#define __SLOW_DOWN_IO&t;do { } while (0)
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO&t;do { } while (0)
r_extern
r_int
r_int
id|virt_to_bus_not_defined_use_pci_map
c_func
(paren
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus virt_to_bus_not_defined_use_pci_map
r_extern
r_int
r_int
id|bus_to_virt_not_defined_use_pci_map
c_func
(paren
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt bus_to_virt_not_defined_use_pci_map
multiline_comment|/* BIO layer definitions. */
r_extern
r_int
r_int
id|phys_base
comma
id|kern_base
comma
id|kern_size
suffix:semicolon
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)&t;((((page) - mem_map) &lt;&lt; PAGE_SHIFT)+phys_base)
DECL|macro|BIO_VMERGE_BOUNDARY
mdefine_line|#define BIO_VMERGE_BOUNDARY&t;8192
multiline_comment|/* Different PCI controllers we support have their PCI MEM space&n; * mapped to an either 2GB (Psycho) or 4GB (Sabre) aligned area,&n; * so need to chop off the top 33 or 32 bits.&n; */
r_extern
r_int
r_int
id|pci_memspace_mask
suffix:semicolon
DECL|macro|bus_dvma_to_mem
mdefine_line|#define bus_dvma_to_mem(__vaddr) ((__vaddr) &amp; pci_memspace_mask)
DECL|function|inb
r_static
id|__inline__
id|u8
id|inb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|u8
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduba&bslash;t[%1] %2, %0&bslash;t/* pci_inb */&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E_L
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|inw
r_static
id|__inline__
id|u16
id|inw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|u16
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduha&bslash;t[%1] %2, %0&bslash;t/* pci_inw */&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E_L
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|inl
r_static
id|__inline__
id|u32
id|inl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|u32
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduwa&bslash;t[%1] %2, %0&bslash;t/* pci_inl */&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E_L
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|outb
r_static
id|__inline__
r_void
id|outb
c_func
(paren
id|u8
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stba&bslash;t%r0, [%1] %2&bslash;t/* pci_outb */&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|b
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E_L
)paren
)paren
suffix:semicolon
)brace
DECL|function|outw
r_static
id|__inline__
r_void
id|outw
c_func
(paren
id|u16
id|w
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stha&bslash;t%r0, [%1] %2&bslash;t/* pci_outw */&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|w
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E_L
)paren
)paren
suffix:semicolon
)brace
DECL|function|outl
r_static
id|__inline__
r_void
id|outl
c_func
(paren
id|u32
id|l
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stwa&bslash;t%r0, [%1] %2&bslash;t/* pci_outl */&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|l
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E_L
)paren
)paren
suffix:semicolon
)brace
DECL|macro|inb_p
mdefine_line|#define inb_p inb
DECL|macro|outb_p
mdefine_line|#define outb_p outb
DECL|macro|inw_p
mdefine_line|#define inw_p inw
DECL|macro|outw_p
mdefine_line|#define outw_p outw
DECL|macro|inl_p
mdefine_line|#define inl_p inl
DECL|macro|outl_p
mdefine_line|#define outl_p outl
r_extern
r_void
id|outsb
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|outsw
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|outsl
c_func
(paren
r_int
r_int
id|addr
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|insb
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|insw
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|insl
c_func
(paren
r_int
r_int
id|addr
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
suffix:semicolon
multiline_comment|/* Memory functions, same as I/O accesses on Ultra. */
DECL|function|_readb
r_static
id|__inline__
id|u8
id|_readb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|u8
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduba&bslash;t[%1] %2, %0&bslash;t/* pci_readb */&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E_L
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|_readw
r_static
id|__inline__
id|u16
id|_readw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|u16
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduha&bslash;t[%1] %2, %0&bslash;t/* pci_readw */&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E_L
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|_readl
r_static
id|__inline__
id|u32
id|_readl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|u32
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduwa&bslash;t[%1] %2, %0&bslash;t/* pci_readl */&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E_L
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|_readq
r_static
id|__inline__
id|u64
id|_readq
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|u64
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldxa&bslash;t[%1] %2, %0&bslash;t/* pci_readq */&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E_L
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|_writeb
r_static
id|__inline__
r_void
id|_writeb
c_func
(paren
id|u8
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stba&bslash;t%r0, [%1] %2&bslash;t/* pci_writeb */&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|b
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E_L
)paren
)paren
suffix:semicolon
)brace
DECL|function|_writew
r_static
id|__inline__
r_void
id|_writew
c_func
(paren
id|u16
id|w
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stha&bslash;t%r0, [%1] %2&bslash;t/* pci_writew */&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|w
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E_L
)paren
)paren
suffix:semicolon
)brace
DECL|function|_writel
r_static
id|__inline__
r_void
id|_writel
c_func
(paren
id|u32
id|l
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stwa&bslash;t%r0, [%1] %2&bslash;t/* pci_writel */&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|l
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E_L
)paren
)paren
suffix:semicolon
)brace
DECL|function|_writeq
r_static
id|__inline__
r_void
id|_writeq
c_func
(paren
id|u64
id|q
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stxa&bslash;t%r0, [%1] %2&bslash;t/* pci_writeq */&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|q
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E_L
)paren
)paren
suffix:semicolon
)brace
DECL|macro|readb
mdefine_line|#define readb(__addr)&t;&t;(_readb((unsigned long)(__addr)))
DECL|macro|readw
mdefine_line|#define readw(__addr)&t;&t;(_readw((unsigned long)(__addr)))
DECL|macro|readl
mdefine_line|#define readl(__addr)&t;&t;(_readl((unsigned long)(__addr)))
DECL|macro|readq
mdefine_line|#define readq(__addr)&t;&t;(_readq((unsigned long)(__addr)))
DECL|macro|readb_relaxed
mdefine_line|#define readb_relaxed(a)&t;readb(a)
DECL|macro|readw_relaxed
mdefine_line|#define readw_relaxed(a)&t;readw(a)
DECL|macro|readl_relaxed
mdefine_line|#define readl_relaxed(a)&t;readl(a)
DECL|macro|readq_relaxed
mdefine_line|#define readq_relaxed(a)&t;readq(a)
DECL|macro|writeb
mdefine_line|#define writeb(__b, __addr)&t;(_writeb((u8)(__b), (unsigned long)(__addr)))
DECL|macro|writew
mdefine_line|#define writew(__w, __addr)&t;(_writew((u16)(__w), (unsigned long)(__addr)))
DECL|macro|writel
mdefine_line|#define writel(__l, __addr)&t;(_writel((u32)(__l), (unsigned long)(__addr)))
DECL|macro|writeq
mdefine_line|#define writeq(__q, __addr)&t;(_writeq((u64)(__q), (unsigned long)(__addr)))
multiline_comment|/* Now versions without byte-swapping. */
DECL|function|_raw_readb
r_static
id|__inline__
id|u8
id|_raw_readb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|u8
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduba&bslash;t[%1] %2, %0&bslash;t/* pci_raw_readb */&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|_raw_readw
r_static
id|__inline__
id|u16
id|_raw_readw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|u16
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduha&bslash;t[%1] %2, %0&bslash;t/* pci_raw_readw */&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|_raw_readl
r_static
id|__inline__
id|u32
id|_raw_readl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|u32
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduwa&bslash;t[%1] %2, %0&bslash;t/* pci_raw_readl */&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|_raw_readq
r_static
id|__inline__
id|u64
id|_raw_readq
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|u64
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldxa&bslash;t[%1] %2, %0&bslash;t/* pci_raw_readq */&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|_raw_writeb
r_static
id|__inline__
r_void
id|_raw_writeb
c_func
(paren
id|u8
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stba&bslash;t%r0, [%1] %2&bslash;t/* pci_raw_writeb */&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|b
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
)brace
DECL|function|_raw_writew
r_static
id|__inline__
r_void
id|_raw_writew
c_func
(paren
id|u16
id|w
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stha&bslash;t%r0, [%1] %2&bslash;t/* pci_raw_writew */&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|w
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
)brace
DECL|function|_raw_writel
r_static
id|__inline__
r_void
id|_raw_writel
c_func
(paren
id|u32
id|l
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stwa&bslash;t%r0, [%1] %2&bslash;t/* pci_raw_writel */&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|l
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
)brace
DECL|function|_raw_writeq
r_static
id|__inline__
r_void
id|_raw_writeq
c_func
(paren
id|u64
id|q
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stxa&bslash;t%r0, [%1] %2&bslash;t/* pci_raw_writeq */&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|q
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
)brace
DECL|macro|__raw_readb
mdefine_line|#define __raw_readb(__addr)&t;&t;(_raw_readb((unsigned long)(__addr)))
DECL|macro|__raw_readw
mdefine_line|#define __raw_readw(__addr)&t;&t;(_raw_readw((unsigned long)(__addr)))
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl(__addr)&t;&t;(_raw_readl((unsigned long)(__addr)))
DECL|macro|__raw_readq
mdefine_line|#define __raw_readq(__addr)&t;&t;(_raw_readq((unsigned long)(__addr)))
DECL|macro|__raw_writeb
mdefine_line|#define __raw_writeb(__b, __addr)&t;(_raw_writeb((u8)(__b), (unsigned long)(__addr)))
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew(__w, __addr)&t;(_raw_writew((u16)(__w), (unsigned long)(__addr)))
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel(__l, __addr)&t;(_raw_writel((u32)(__l), (unsigned long)(__addr)))
DECL|macro|__raw_writeq
mdefine_line|#define __raw_writeq(__q, __addr)&t;(_raw_writeq((u64)(__q), (unsigned long)(__addr)))
multiline_comment|/* Valid I/O Space regions are anywhere, because each PCI bus supported&n; * can live in an arbitrary area of the physical address range.&n; */
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffffffffffffUL
multiline_comment|/* Now, SBUS variants, only difference from PCI is that we do&n; * not use little-endian ASIs.&n; */
DECL|function|_sbus_readb
r_static
id|__inline__
id|u8
id|_sbus_readb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|u8
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduba&bslash;t[%1] %2, %0&bslash;t/* sbus_readb */&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|_sbus_readw
r_static
id|__inline__
id|u16
id|_sbus_readw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|u16
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduha&bslash;t[%1] %2, %0&bslash;t/* sbus_readw */&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|_sbus_readl
r_static
id|__inline__
id|u32
id|_sbus_readl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|u32
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lduwa&bslash;t[%1] %2, %0&bslash;t/* sbus_readl */&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|_sbus_readq
r_static
id|__inline__
id|u64
id|_sbus_readq
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|u64
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldxa&bslash;t[%1] %2, %0&bslash;t/* sbus_readq */&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|_sbus_writeb
r_static
id|__inline__
r_void
id|_sbus_writeb
c_func
(paren
id|u8
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stba&bslash;t%r0, [%1] %2&bslash;t/* sbus_writeb */&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|b
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
)brace
DECL|function|_sbus_writew
r_static
id|__inline__
r_void
id|_sbus_writew
c_func
(paren
id|u16
id|w
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stha&bslash;t%r0, [%1] %2&bslash;t/* sbus_writew */&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|w
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
)brace
DECL|function|_sbus_writel
r_static
id|__inline__
r_void
id|_sbus_writel
c_func
(paren
id|u32
id|l
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stwa&bslash;t%r0, [%1] %2&bslash;t/* sbus_writel */&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|l
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
)brace
DECL|function|_sbus_writeq
r_static
id|__inline__
r_void
id|_sbus_writeq
c_func
(paren
id|u64
id|l
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stxa&bslash;t%r0, [%1] %2&bslash;t/* sbus_writeq */&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|l
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_PHYS_BYPASS_EC_E
)paren
)paren
suffix:semicolon
)brace
DECL|macro|sbus_readb
mdefine_line|#define sbus_readb(__addr)&t;&t;(_sbus_readb((unsigned long)(__addr)))
DECL|macro|sbus_readw
mdefine_line|#define sbus_readw(__addr)&t;&t;(_sbus_readw((unsigned long)(__addr)))
DECL|macro|sbus_readl
mdefine_line|#define sbus_readl(__addr)&t;&t;(_sbus_readl((unsigned long)(__addr)))
DECL|macro|sbus_readq
mdefine_line|#define sbus_readq(__addr)&t;&t;(_sbus_readq((unsigned long)(__addr)))
DECL|macro|sbus_writeb
mdefine_line|#define sbus_writeb(__b, __addr)&t;(_sbus_writeb((__b), (unsigned long)(__addr)))
DECL|macro|sbus_writew
mdefine_line|#define sbus_writew(__w, __addr)&t;(_sbus_writew((__w), (unsigned long)(__addr)))
DECL|macro|sbus_writel
mdefine_line|#define sbus_writel(__l, __addr)&t;(_sbus_writel((__l), (unsigned long)(__addr)))
DECL|macro|sbus_writeq
mdefine_line|#define sbus_writeq(__l, __addr)&t;(_sbus_writeq((__l), (unsigned long)(__addr)))
DECL|function|_sbus_memset_io
r_static
r_inline
r_void
op_star
id|_sbus_memset_io
c_func
(paren
r_int
r_int
id|dst
comma
r_int
id|c
comma
id|__kernel_size_t
id|n
)paren
(brace
r_while
c_loop
(paren
id|n
op_decrement
)paren
(brace
id|sbus_writeb
c_func
(paren
id|c
comma
id|dst
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
)brace
r_return
(paren
r_void
op_star
)paren
id|dst
suffix:semicolon
)brace
DECL|macro|sbus_memset_io
mdefine_line|#define sbus_memset_io(d,c,sz)&t;&bslash;&n;&t;_sbus_memset_io((unsigned long)d,(int)c,(__kernel_size_t)sz)
r_static
r_inline
r_void
op_star
DECL|function|_memset_io
id|_memset_io
c_func
(paren
r_void
op_star
id|dst
comma
r_int
id|c
comma
id|__kernel_size_t
id|n
)paren
(brace
r_char
op_star
id|d
op_assign
id|dst
suffix:semicolon
r_while
c_loop
(paren
id|n
op_decrement
)paren
(brace
id|writeb
c_func
(paren
id|c
comma
id|d
)paren
suffix:semicolon
id|d
op_increment
suffix:semicolon
)brace
r_return
id|dst
suffix:semicolon
)brace
DECL|macro|memset_io
mdefine_line|#define memset_io(d,c,sz)&t;&bslash;&n;&t;_memset_io((void *)d,(int)c,(__kernel_size_t)sz)
r_static
r_inline
r_void
op_star
DECL|function|_memcpy_fromio
id|_memcpy_fromio
c_func
(paren
r_void
op_star
id|dst
comma
r_int
r_int
id|src
comma
id|__kernel_size_t
id|n
)paren
(brace
r_char
op_star
id|d
op_assign
id|dst
suffix:semicolon
r_while
c_loop
(paren
id|n
op_decrement
)paren
(brace
r_char
id|tmp
op_assign
id|readb
c_func
(paren
id|src
)paren
suffix:semicolon
op_star
id|d
op_increment
op_assign
id|tmp
suffix:semicolon
id|src
op_increment
suffix:semicolon
)brace
r_return
id|dst
suffix:semicolon
)brace
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(d,s,sz)&t;&bslash;&n;&t;_memcpy_fromio((void *)d,(unsigned long)s,(__kernel_size_t)sz)
r_static
r_inline
r_void
op_star
DECL|function|_memcpy_toio
id|_memcpy_toio
c_func
(paren
r_int
r_int
id|dst
comma
r_const
r_void
op_star
id|src
comma
id|__kernel_size_t
id|n
)paren
(brace
r_const
r_char
op_star
id|s
op_assign
id|src
suffix:semicolon
r_int
r_int
id|d
op_assign
id|dst
suffix:semicolon
r_while
c_loop
(paren
id|n
op_decrement
)paren
(brace
r_char
id|tmp
op_assign
op_star
id|s
op_increment
suffix:semicolon
id|writeb
c_func
(paren
id|tmp
comma
id|d
)paren
suffix:semicolon
id|d
op_increment
suffix:semicolon
)brace
r_return
(paren
r_void
op_star
)paren
id|dst
suffix:semicolon
)brace
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(d,s,sz)&t;&bslash;&n;&t;_memcpy_toio((unsigned long)d,(const void *)s,(__kernel_size_t)sz)
DECL|function|check_signature
r_static
r_inline
r_int
id|check_signature
c_func
(paren
r_int
r_int
id|io_addr
comma
r_const
r_int
r_char
op_star
id|signature
comma
r_int
id|length
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|readb
c_func
(paren
id|io_addr
op_increment
)paren
op_ne
op_star
id|signature
op_increment
)paren
r_goto
id|out
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|length
)paren
suffix:semicolon
id|retval
op_assign
l_int|1
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#ifdef __KERNEL__
multiline_comment|/* On sparc64 we have the whole physical IO address space accessible&n; * using physically addressed loads and stores, so this does nothing.&n; */
DECL|macro|ioremap
mdefine_line|#define ioremap(__offset, __size)&t;((void *)(__offset))
DECL|macro|ioremap_nocache
mdefine_line|#define ioremap_nocache(X,Y)&t;&t;ioremap((X),(Y))
DECL|macro|iounmap
mdefine_line|#define iounmap(__addr)&t;&t;&t;do { (void)(__addr); } while(0)
multiline_comment|/* Similarly for SBUS. */
DECL|macro|sbus_ioremap
mdefine_line|#define sbus_ioremap(__res, __offset, __size, __name) &bslash;&n;({&t;unsigned long __ret; &bslash;&n;&t;__ret  = (__res)-&gt;start + (((__res)-&gt;flags &amp; 0x1ffUL) &lt;&lt; 32UL); &bslash;&n;&t;__ret += (unsigned long) (__offset); &bslash;&n;&t;if (! request_region((__ret), (__size), (__name))) &bslash;&n;&t;&t;__ret = 0UL; &bslash;&n;&t;__ret; &bslash;&n;})
DECL|macro|sbus_iounmap
mdefine_line|#define sbus_iounmap(__addr, __size)&t;&bslash;&n;&t;release_region((__addr), (__size))
multiline_comment|/* Nothing to do */
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(_start,_size)&t;do { } while (0)
macro_line|#endif
macro_line|#endif /* !(__SPARC64_IO_H) */
eof
