macro_line|#ifndef _ASM_IA64_IO_H
DECL|macro|_ASM_IA64_IO_H
mdefine_line|#define _ASM_IA64_IO_H
multiline_comment|/*&n; * This file contains the definitions for the emulated IO instructions&n; * inb/inw/inl/outb/outw/outl and the &quot;string versions&quot; of the same&n; * (insb/insw/insl/outsb/outsw/outsl). You can also use &quot;pausing&quot;&n; * versions of the single-IO instructions (inb_p/inw_p/..).&n; *&n; * This file is not meant to be obfuscating: it&squot;s just complicated to&n; * (a) handle it all in a way that makes gcc able to optimize it as&n; * well as possible and (b) trying to avoid writing the same thing&n; * over and over again with slight variations and possibly making a&n; * mistake somewhere.&n; *&n; * Copyright (C) 1998-2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1999 Asit Mallick &lt;asit.k.mallick@intel.com&gt;&n; * Copyright (C) 1999 Don Dugger &lt;don.dugger@intel.com&gt;&n; */
multiline_comment|/* We don&squot;t use IO slowdowns on the ia64, but.. */
DECL|macro|__SLOW_DOWN_IO
mdefine_line|#define __SLOW_DOWN_IO&t;do { } while (0)
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO&t;do { } while (0)
DECL|macro|__IA64_UNCACHED_OFFSET
mdefine_line|#define __IA64_UNCACHED_OFFSET&t;0xc000000000000000UL&t;/* region 6 */
multiline_comment|/*&n; * The legacy I/O space defined by the ia64 architecture supports only 65536 ports, but&n; * large machines may have multiple other I/O spaces so we can&squot;t place any a priori limit&n; * on IO_SPACE_LIMIT.  These additional spaces are described in ACPI.&n; */
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT&t;&t;0xffffffffffffffffUL
DECL|macro|MAX_IO_SPACES_BITS
mdefine_line|#define MAX_IO_SPACES_BITS&t;&t;4
DECL|macro|MAX_IO_SPACES
mdefine_line|#define MAX_IO_SPACES&t;&t;&t;(1UL &lt;&lt; MAX_IO_SPACES_BITS)
DECL|macro|IO_SPACE_BITS
mdefine_line|#define IO_SPACE_BITS&t;&t;&t;24
DECL|macro|IO_SPACE_SIZE
mdefine_line|#define IO_SPACE_SIZE&t;&t;&t;(1UL &lt;&lt; IO_SPACE_BITS)
DECL|macro|IO_SPACE_NR
mdefine_line|#define IO_SPACE_NR(port)&t;&t;((port) &gt;&gt; IO_SPACE_BITS)
DECL|macro|IO_SPACE_BASE
mdefine_line|#define IO_SPACE_BASE(space)&t;&t;((space) &lt;&lt; IO_SPACE_BITS)
DECL|macro|IO_SPACE_PORT
mdefine_line|#define IO_SPACE_PORT(port)&t;&t;((port) &amp; (IO_SPACE_SIZE - 1))
DECL|macro|IO_SPACE_SPARSE_ENCODING
mdefine_line|#define IO_SPACE_SPARSE_ENCODING(p)&t;((((p) &gt;&gt; 2) &lt;&lt; 12) | (p &amp; 0xfff))
DECL|struct|io_space
r_struct
id|io_space
(brace
DECL|member|mmio_base
r_int
r_int
id|mmio_base
suffix:semicolon
multiline_comment|/* base in MMIO space */
DECL|member|sparse
r_int
id|sparse
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|io_space
id|io_space
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|num_io_spaces
suffix:semicolon
macro_line|# ifdef __KERNEL__
multiline_comment|/*&n; * All MMIO iomem cookies are in region 6; anything less is a PIO cookie:&n; *&t;0xCxxxxxxxxxxxxxxx&t;MMIO cookie (return from ioremap)&n; *&t;0x000000001SPPPPPP&t;PIO cookie (S=space number, P..P=port)&n; *&n; * ioread/writeX() uses the leading 1 in PIO cookies (PIO_OFFSET) to catch&n; * code that uses bare port numbers without the prerequisite pci_iomap().&n; */
DECL|macro|PIO_OFFSET
mdefine_line|#define PIO_OFFSET&t;&t;(1UL &lt;&lt; (MAX_IO_SPACES_BITS + IO_SPACE_BITS))
DECL|macro|PIO_MASK
mdefine_line|#define PIO_MASK&t;&t;(PIO_OFFSET - 1)
DECL|macro|PIO_RESERVED
mdefine_line|#define PIO_RESERVED&t;&t;__IA64_UNCACHED_OFFSET
DECL|macro|HAVE_ARCH_PIO_SIZE
mdefine_line|#define HAVE_ARCH_PIO_SIZE
macro_line|#include &lt;asm/intrinsics.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm-generic/iomap.h&gt;
multiline_comment|/*&n; * Change virtual addresses to physical addresses and vv.&n; */
r_static
r_inline
r_int
r_int
DECL|function|virt_to_phys
id|virt_to_phys
(paren
r_volatile
r_void
op_star
id|address
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|address
op_minus
id|PAGE_OFFSET
suffix:semicolon
)brace
r_static
r_inline
r_void
op_star
DECL|function|phys_to_virt
id|phys_to_virt
(paren
r_int
r_int
id|address
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
id|address
op_plus
id|PAGE_OFFSET
)paren
suffix:semicolon
)brace
DECL|macro|ARCH_HAS_VALID_PHYS_ADDR_RANGE
mdefine_line|#define ARCH_HAS_VALID_PHYS_ADDR_RANGE
r_extern
r_int
id|valid_phys_addr_range
(paren
r_int
r_int
id|addr
comma
r_int
op_star
id|count
)paren
suffix:semicolon
multiline_comment|/* efi.c */
multiline_comment|/*&n; * The following two macros are deprecated and scheduled for removal.&n; * Please use the PCI-DMA interface defined in &lt;asm/pci.h&gt; instead.&n; */
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt&t;phys_to_virt
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus&t;virt_to_phys
DECL|macro|page_to_bus
mdefine_line|#define page_to_bus&t;page_to_phys
macro_line|# endif /* KERNEL */
multiline_comment|/*&n; * Memory fence w/accept.  This should never be used in code that is&n; * not IA-64 specific.&n; */
DECL|macro|__ia64_mf_a
mdefine_line|#define __ia64_mf_a()&t;ia64_mfa()
multiline_comment|/**&n; * ___ia64_mmiowb - I/O write barrier&n; *&n; * Ensure ordering of I/O space writes.  This will make sure that writes&n; * following the barrier will arrive after all previous writes.  For most&n; * ia64 platforms, this is a simple &squot;mf.a&squot; instruction.&n; *&n; * See Documentation/DocBook/deviceiobook.tmpl for more information.&n; */
DECL|function|___ia64_mmiowb
r_static
r_inline
r_void
id|___ia64_mmiowb
c_func
(paren
r_void
)paren
(brace
id|ia64_mfa
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_const
r_int
r_int
DECL|function|__ia64_get_io_port_base
id|__ia64_get_io_port_base
(paren
r_void
)paren
(brace
r_extern
r_int
r_int
id|ia64_iobase
suffix:semicolon
r_return
id|ia64_iobase
suffix:semicolon
)brace
r_static
r_inline
r_void
op_star
DECL|function|__ia64_mk_io_addr
id|__ia64_mk_io_addr
(paren
r_int
r_int
id|port
)paren
(brace
r_struct
id|io_space
op_star
id|space
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
id|space
op_assign
op_amp
id|io_space
(braket
id|IO_SPACE_NR
c_func
(paren
id|port
)paren
)braket
suffix:semicolon
id|port
op_assign
id|IO_SPACE_PORT
c_func
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|space-&gt;sparse
)paren
id|offset
op_assign
id|IO_SPACE_SPARSE_ENCODING
c_func
(paren
id|port
)paren
suffix:semicolon
r_else
id|offset
op_assign
id|port
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
(paren
id|space-&gt;mmio_base
op_or
id|offset
)paren
suffix:semicolon
)brace
DECL|macro|__ia64_inb
mdefine_line|#define __ia64_inb&t;___ia64_inb
DECL|macro|__ia64_inw
mdefine_line|#define __ia64_inw&t;___ia64_inw
DECL|macro|__ia64_inl
mdefine_line|#define __ia64_inl&t;___ia64_inl
DECL|macro|__ia64_outb
mdefine_line|#define __ia64_outb&t;___ia64_outb
DECL|macro|__ia64_outw
mdefine_line|#define __ia64_outw&t;___ia64_outw
DECL|macro|__ia64_outl
mdefine_line|#define __ia64_outl&t;___ia64_outl
DECL|macro|__ia64_readb
mdefine_line|#define __ia64_readb&t;___ia64_readb
DECL|macro|__ia64_readw
mdefine_line|#define __ia64_readw&t;___ia64_readw
DECL|macro|__ia64_readl
mdefine_line|#define __ia64_readl&t;___ia64_readl
DECL|macro|__ia64_readq
mdefine_line|#define __ia64_readq&t;___ia64_readq
DECL|macro|__ia64_readb_relaxed
mdefine_line|#define __ia64_readb_relaxed&t;___ia64_readb
DECL|macro|__ia64_readw_relaxed
mdefine_line|#define __ia64_readw_relaxed&t;___ia64_readw
DECL|macro|__ia64_readl_relaxed
mdefine_line|#define __ia64_readl_relaxed&t;___ia64_readl
DECL|macro|__ia64_readq_relaxed
mdefine_line|#define __ia64_readq_relaxed&t;___ia64_readq
DECL|macro|__ia64_writeb
mdefine_line|#define __ia64_writeb&t;___ia64_writeb
DECL|macro|__ia64_writew
mdefine_line|#define __ia64_writew&t;___ia64_writew
DECL|macro|__ia64_writel
mdefine_line|#define __ia64_writel&t;___ia64_writel
DECL|macro|__ia64_writeq
mdefine_line|#define __ia64_writeq&t;___ia64_writeq
DECL|macro|__ia64_mmiowb
mdefine_line|#define __ia64_mmiowb&t;___ia64_mmiowb
multiline_comment|/*&n; * For the in/out routines, we need to do &quot;mf.a&quot; _after_ doing the I/O access to ensure&n; * that the access has completed before executing other I/O accesses.  Since we&squot;re doing&n; * the accesses through an uncachable (UC) translation, the CPU will execute them in&n; * program order.  However, we still need to tell the compiler not to shuffle them around&n; * during optimization, which is why we use &quot;volatile&quot; pointers.&n; */
r_static
r_inline
r_int
r_int
DECL|function|___ia64_inb
id|___ia64_inb
(paren
r_int
r_int
id|port
)paren
(brace
r_volatile
r_int
r_char
op_star
id|addr
op_assign
id|__ia64_mk_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
r_int
r_char
id|ret
suffix:semicolon
id|ret
op_assign
op_star
id|addr
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|___ia64_inw
id|___ia64_inw
(paren
r_int
r_int
id|port
)paren
(brace
r_volatile
r_int
r_int
op_star
id|addr
op_assign
id|__ia64_mk_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
id|ret
op_assign
op_star
id|addr
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|___ia64_inl
id|___ia64_inl
(paren
r_int
r_int
id|port
)paren
(brace
r_volatile
r_int
r_int
op_star
id|addr
op_assign
id|__ia64_mk_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
id|ret
op_assign
op_star
id|addr
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|___ia64_outb
id|___ia64_outb
(paren
r_int
r_char
id|val
comma
r_int
r_int
id|port
)paren
(brace
r_volatile
r_int
r_char
op_star
id|addr
op_assign
id|__ia64_mk_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
op_star
id|addr
op_assign
id|val
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|___ia64_outw
id|___ia64_outw
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|port
)paren
(brace
r_volatile
r_int
r_int
op_star
id|addr
op_assign
id|__ia64_mk_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
op_star
id|addr
op_assign
id|val
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|___ia64_outl
id|___ia64_outl
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|port
)paren
(brace
r_volatile
r_int
r_int
op_star
id|addr
op_assign
id|__ia64_mk_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
op_star
id|addr
op_assign
id|val
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__insb
id|__insb
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
(brace
r_int
r_char
op_star
id|dp
op_assign
id|dst
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|dp
op_increment
op_assign
id|platform_inb
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__insw
id|__insw
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
(brace
r_int
r_int
op_star
id|dp
op_assign
id|dst
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|dp
op_increment
op_assign
id|platform_inw
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__insl
id|__insl
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|dst
comma
r_int
r_int
id|count
)paren
(brace
r_int
r_int
op_star
id|dp
op_assign
id|dst
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|dp
op_increment
op_assign
id|platform_inl
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__outsb
id|__outsb
(paren
r_int
r_int
id|port
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
(brace
r_const
r_int
r_char
op_star
id|sp
op_assign
id|src
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
id|platform_outb
c_func
(paren
op_star
id|sp
op_increment
comma
id|port
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__outsw
id|__outsw
(paren
r_int
r_int
id|port
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
(brace
r_const
r_int
r_int
op_star
id|sp
op_assign
id|src
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
id|platform_outw
c_func
(paren
op_star
id|sp
op_increment
comma
id|port
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__outsl
id|__outsl
(paren
r_int
r_int
id|port
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
(brace
r_const
r_int
r_int
op_star
id|sp
op_assign
id|src
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
id|platform_outl
c_func
(paren
op_star
id|sp
op_increment
comma
id|port
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Unfortunately, some platforms are broken and do not follow the IA-64 architecture&n; * specification regarding legacy I/O support.  Thus, we have to make these operations&n; * platform dependent...&n; */
DECL|macro|__inb
mdefine_line|#define __inb&t;&t;platform_inb
DECL|macro|__inw
mdefine_line|#define __inw&t;&t;platform_inw
DECL|macro|__inl
mdefine_line|#define __inl&t;&t;platform_inl
DECL|macro|__outb
mdefine_line|#define __outb&t;&t;platform_outb
DECL|macro|__outw
mdefine_line|#define __outw&t;&t;platform_outw
DECL|macro|__outl
mdefine_line|#define __outl&t;&t;platform_outl
DECL|macro|__mmiowb
mdefine_line|#define __mmiowb&t;platform_mmiowb
DECL|macro|inb
mdefine_line|#define inb(p)&t;&t;__inb(p)
DECL|macro|inw
mdefine_line|#define inw(p)&t;&t;__inw(p)
DECL|macro|inl
mdefine_line|#define inl(p)&t;&t;__inl(p)
DECL|macro|insb
mdefine_line|#define insb(p,d,c)&t;__insb(p,d,c)
DECL|macro|insw
mdefine_line|#define insw(p,d,c)&t;__insw(p,d,c)
DECL|macro|insl
mdefine_line|#define insl(p,d,c)&t;__insl(p,d,c)
DECL|macro|outb
mdefine_line|#define outb(v,p)&t;__outb(v,p)
DECL|macro|outw
mdefine_line|#define outw(v,p)&t;__outw(v,p)
DECL|macro|outl
mdefine_line|#define outl(v,p)&t;__outl(v,p)
DECL|macro|outsb
mdefine_line|#define outsb(p,s,c)&t;__outsb(p,s,c)
DECL|macro|outsw
mdefine_line|#define outsw(p,s,c)&t;__outsw(p,s,c)
DECL|macro|outsl
mdefine_line|#define outsl(p,s,c)&t;__outsl(p,s,c)
DECL|macro|mmiowb
mdefine_line|#define mmiowb()&t;__mmiowb()
multiline_comment|/*&n; * The address passed to these functions are ioremap()ped already.&n; *&n; * We need these to be machine vectors since some platforms don&squot;t provide&n; * DMA coherence via PIO reads (PCI drivers and the spec imply that this is&n; * a good idea).  Writes are ok though for all existing ia64 platforms (and&n; * hopefully it&squot;ll stay that way).&n; */
r_static
r_inline
r_int
r_char
DECL|function|___ia64_readb
id|___ia64_readb
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_char
id|__force
op_star
)paren
id|addr
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|___ia64_readw
id|___ia64_readw
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
id|__force
op_star
)paren
id|addr
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|___ia64_readl
id|___ia64_readl
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
id|__force
op_star
)paren
id|addr
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|___ia64_readq
id|___ia64_readq
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
id|__force
op_star
)paren
id|addr
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__writeb
id|__writeb
(paren
r_int
r_char
id|val
comma
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_char
id|__force
op_star
)paren
id|addr
op_assign
id|val
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__writew
id|__writew
(paren
r_int
r_int
id|val
comma
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
id|__force
op_star
)paren
id|addr
op_assign
id|val
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__writel
id|__writel
(paren
r_int
r_int
id|val
comma
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
id|__force
op_star
)paren
id|addr
op_assign
id|val
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__writeq
id|__writeq
(paren
r_int
r_int
id|val
comma
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
id|__force
op_star
)paren
id|addr
op_assign
id|val
suffix:semicolon
)brace
DECL|macro|__readb
mdefine_line|#define __readb&t;&t;platform_readb
DECL|macro|__readw
mdefine_line|#define __readw&t;&t;platform_readw
DECL|macro|__readl
mdefine_line|#define __readl&t;&t;platform_readl
DECL|macro|__readq
mdefine_line|#define __readq&t;&t;platform_readq
DECL|macro|__readb_relaxed
mdefine_line|#define __readb_relaxed&t;platform_readb_relaxed
DECL|macro|__readw_relaxed
mdefine_line|#define __readw_relaxed&t;platform_readw_relaxed
DECL|macro|__readl_relaxed
mdefine_line|#define __readl_relaxed&t;platform_readl_relaxed
DECL|macro|__readq_relaxed
mdefine_line|#define __readq_relaxed&t;platform_readq_relaxed
DECL|macro|readb
mdefine_line|#define readb(a)&t;__readb((a))
DECL|macro|readw
mdefine_line|#define readw(a)&t;__readw((a))
DECL|macro|readl
mdefine_line|#define readl(a)&t;__readl((a))
DECL|macro|readq
mdefine_line|#define readq(a)&t;__readq((a))
DECL|macro|readb_relaxed
mdefine_line|#define readb_relaxed(a)&t;__readb_relaxed((a))
DECL|macro|readw_relaxed
mdefine_line|#define readw_relaxed(a)&t;__readw_relaxed((a))
DECL|macro|readl_relaxed
mdefine_line|#define readl_relaxed(a)&t;__readl_relaxed((a))
DECL|macro|readq_relaxed
mdefine_line|#define readq_relaxed(a)&t;__readq_relaxed((a))
DECL|macro|__raw_readb
mdefine_line|#define __raw_readb&t;readb
DECL|macro|__raw_readw
mdefine_line|#define __raw_readw&t;readw
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl&t;readl
DECL|macro|__raw_readq
mdefine_line|#define __raw_readq&t;readq
DECL|macro|__raw_readb_relaxed
mdefine_line|#define __raw_readb_relaxed&t;readb_relaxed
DECL|macro|__raw_readw_relaxed
mdefine_line|#define __raw_readw_relaxed&t;readw_relaxed
DECL|macro|__raw_readl_relaxed
mdefine_line|#define __raw_readl_relaxed&t;readl_relaxed
DECL|macro|__raw_readq_relaxed
mdefine_line|#define __raw_readq_relaxed&t;readq_relaxed
DECL|macro|writeb
mdefine_line|#define writeb(v,a)&t;__writeb((v), (a))
DECL|macro|writew
mdefine_line|#define writew(v,a)&t;__writew((v), (a))
DECL|macro|writel
mdefine_line|#define writel(v,a)&t;__writel((v), (a))
DECL|macro|writeq
mdefine_line|#define writeq(v,a)&t;__writeq((v), (a))
DECL|macro|__raw_writeb
mdefine_line|#define __raw_writeb&t;writeb
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew&t;writew
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel&t;writel
DECL|macro|__raw_writeq
mdefine_line|#define __raw_writeq&t;writeq
macro_line|#ifndef inb_p
DECL|macro|inb_p
macro_line|# define inb_p&t;&t;inb
macro_line|#endif
macro_line|#ifndef inw_p
DECL|macro|inw_p
macro_line|# define inw_p&t;&t;inw
macro_line|#endif
macro_line|#ifndef inl_p
DECL|macro|inl_p
macro_line|# define inl_p&t;&t;inl
macro_line|#endif
macro_line|#ifndef outb_p
DECL|macro|outb_p
macro_line|# define outb_p&t;&t;outb
macro_line|#endif
macro_line|#ifndef outw_p
DECL|macro|outw_p
macro_line|# define outw_p&t;&t;outw
macro_line|#endif
macro_line|#ifndef outl_p
DECL|macro|outl_p
macro_line|# define outl_p&t;&t;outl
macro_line|#endif
multiline_comment|/*&n; * An &quot;address&quot; in IO memory space is not clearly either an integer or a pointer. We will&n; * accept both, thus the casts.&n; *&n; * On ia-64, we access the physical I/O memory space through the uncached kernel region.&n; */
r_static
r_inline
r_void
id|__iomem
op_star
DECL|function|ioremap
id|ioremap
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
)paren
(brace
r_return
(paren
r_void
id|__iomem
op_star
)paren
(paren
id|__IA64_UNCACHED_OFFSET
op_or
(paren
id|offset
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|iounmap
id|iounmap
(paren
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
)brace
DECL|macro|ioremap_nocache
mdefine_line|#define ioremap_nocache(o,s)&t;ioremap(o,s)
macro_line|# ifdef __KERNEL__
multiline_comment|/*&n; * String version of IO memory access ops:&n; */
r_extern
r_void
id|memcpy_fromio
c_func
(paren
r_void
op_star
id|dst
comma
r_const
r_volatile
r_void
id|__iomem
op_star
id|src
comma
r_int
id|n
)paren
suffix:semicolon
r_extern
r_void
id|memcpy_toio
c_func
(paren
r_volatile
r_void
id|__iomem
op_star
id|dst
comma
r_const
r_void
op_star
id|src
comma
r_int
id|n
)paren
suffix:semicolon
r_extern
r_void
id|memset_io
c_func
(paren
r_volatile
r_void
id|__iomem
op_star
id|s
comma
r_int
id|c
comma
r_int
id|n
)paren
suffix:semicolon
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(_start,_size)             do { } while (0)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(_start,_size)           do { } while (0)
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(_start,_size)       do { } while (0)
macro_line|# endif /* __KERNEL__ */
multiline_comment|/*&n; * Enabling BIO_VMERGE_BOUNDARY forces us to turn off I/O MMU bypassing.  It is said that&n; * BIO-level virtual merging can give up to 4% performance boost (not verified for ia64).&n; * On the other hand, we know that I/O MMU bypassing gives ~8% performance improvement on&n; * SPECweb-like workloads on zx1-based machines.  Thus, for now we favor I/O MMU bypassing&n; * over BIO-level virtual merging.&n; */
r_extern
r_int
r_int
id|ia64_max_iommu_merge_mask
suffix:semicolon
macro_line|#if 1
DECL|macro|BIO_VMERGE_BOUNDARY
mdefine_line|#define BIO_VMERGE_BOUNDARY&t;0
macro_line|#else
multiline_comment|/*&n; * It makes no sense at all to have this BIO_VMERGE_BOUNDARY macro here.  Should be&n; * replaced by dma_merge_mask() or something of that sort.  Note: the only way&n; * BIO_VMERGE_BOUNDARY is used is to mask off bits.  Effectively, our definition gets&n; * expanded into:&n; *&n; *&t;addr &amp; ((ia64_max_iommu_merge_mask + 1) - 1) == (addr &amp; ia64_max_iommu_vmerge_mask)&n; *&n; * which is precisely what we want.&n; */
DECL|macro|BIO_VMERGE_BOUNDARY
mdefine_line|#define BIO_VMERGE_BOUNDARY&t;(ia64_max_iommu_merge_mask + 1)
macro_line|#endif
macro_line|#endif /* _ASM_IA64_IO_H */
eof
