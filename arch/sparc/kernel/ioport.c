multiline_comment|/* $Id: ioport.c,v 1.45 2001/10/30 04:54:21 davem Exp $&n; * ioport.c:  Simple io mapping allocator.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1995 Miguel de Icaza (miguel@nuclecu.unam.mx)&n; *&n; * 1996: sparc_free_io, 1999: ioremap()/iounmap() by Pete Zaitcev.&n; *&n; * 2000/01/29&n; * &lt;rth&gt; zait: as long as pci_alloc_consistent produces something addressable, &n; *&t;things are ok.&n; * &lt;zaitcev&gt; rth: no, it is relevant, because get_free_pages returns you a&n; *&t;pointer into the big page mapping&n; * &lt;rth&gt; zait: so what?&n; * &lt;rth&gt; zait: remap_it_my_way(virt_to_phys(get_free_page()))&n; * &lt;zaitcev&gt; Hmm&n; * &lt;zaitcev&gt; Suppose I did this remap_it_my_way(virt_to_phys(get_free_page())).&n; *&t;So far so good.&n; * &lt;zaitcev&gt; Now, driver calls pci_free_consistent(with result of&n; *&t;remap_it_my_way()).&n; * &lt;zaitcev&gt; How do you find the address to pass to free_pages()?&n; * &lt;rth&gt; zait: walk the page tables?  It&squot;s only two or three level after all.&n; * &lt;rth&gt; zait: you have to walk them anyway to remove the mapping.&n; * &lt;zaitcev&gt; Hmm&n; * &lt;zaitcev&gt; Sounds reasonable&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pci.h&gt;&t;&t;/* struct pci_dev */
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/vaddrs.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|macro|mmu_inval_dma_area
mdefine_line|#define mmu_inval_dma_area(p, l)&t;/* Anton pulled it out for 2.4.0-xx */
r_struct
id|resource
op_star
id|_sparc_find_resource
c_func
(paren
r_struct
id|resource
op_star
id|r
comma
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
op_star
id|_sparc_ioremap
c_func
(paren
r_struct
id|resource
op_star
id|res
comma
id|u32
id|bus
comma
id|u32
id|pa
comma
r_int
id|sz
)paren
suffix:semicolon
r_static
r_void
op_star
id|_sparc_alloc_io
c_func
(paren
r_int
r_int
id|busno
comma
r_int
r_int
id|phys
comma
r_int
r_int
id|size
comma
r_char
op_star
id|name
)paren
suffix:semicolon
r_static
r_void
id|_sparc_free_io
c_func
(paren
r_struct
id|resource
op_star
id|res
)paren
suffix:semicolon
multiline_comment|/* This points to the next to use virtual memory for DVMA mappings */
DECL|variable|_sparc_dvma
r_static
r_struct
id|resource
id|_sparc_dvma
op_assign
(brace
l_string|&quot;sparc_dvma&quot;
comma
id|DVMA_VADDR
comma
id|DVMA_END
op_minus
l_int|1
)brace
suffix:semicolon
multiline_comment|/* This points to the start of I/O mappings, cluable from outside. */
DECL|variable|sparc_iomap
multiline_comment|/*ext*/
r_struct
id|resource
id|sparc_iomap
op_assign
(brace
l_string|&quot;sparc_iomap&quot;
comma
id|IOBASE_VADDR
comma
id|IOBASE_END
op_minus
l_int|1
)brace
suffix:semicolon
multiline_comment|/*&n; * Our mini-allocator...&n; * Boy this is gross! We need it because we must map I/O for&n; * timers and interrupt controller before the kmalloc is available.&n; */
DECL|macro|XNMLN
mdefine_line|#define XNMLN  15
DECL|macro|XNRES
mdefine_line|#define XNRES  10&t;/* SS-10 uses 8 */
DECL|struct|xresource
r_struct
id|xresource
(brace
DECL|member|xres
r_struct
id|resource
id|xres
suffix:semicolon
multiline_comment|/* Must be first */
DECL|member|xflag
r_int
id|xflag
suffix:semicolon
multiline_comment|/* 1 == used */
DECL|member|xname
r_char
id|xname
(braket
id|XNMLN
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|xresv
r_static
r_struct
id|xresource
id|xresv
(braket
id|XNRES
)braket
suffix:semicolon
DECL|function|xres_alloc
r_static
r_struct
id|xresource
op_star
id|xres_alloc
c_func
(paren
r_void
)paren
(brace
r_struct
id|xresource
op_star
id|xrp
suffix:semicolon
r_int
id|n
suffix:semicolon
id|xrp
op_assign
id|xresv
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|XNRES
suffix:semicolon
id|n
op_increment
)paren
(brace
r_if
c_cond
(paren
id|xrp-&gt;xflag
op_eq
l_int|0
)paren
(brace
id|xrp-&gt;xflag
op_assign
l_int|1
suffix:semicolon
r_return
id|xrp
suffix:semicolon
)brace
id|xrp
op_increment
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|xres_free
r_static
r_void
id|xres_free
c_func
(paren
r_struct
id|xresource
op_star
id|xrp
)paren
(brace
id|xrp-&gt;xflag
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * These are typically used in PCI drivers&n; * which are trying to be cross-platform.&n; *&n; * Bus type is always zero on IIep.&n; */
DECL|function|ioremap
r_void
op_star
id|ioremap
c_func
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
r_char
id|name
(braket
l_int|14
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;phys_%08x&quot;
comma
(paren
id|u32
)paren
id|offset
)paren
suffix:semicolon
r_return
id|_sparc_alloc_io
c_func
(paren
l_int|0
comma
id|offset
comma
id|size
comma
id|name
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Comlimentary to ioremap().&n; */
DECL|function|iounmap
r_void
id|iounmap
c_func
(paren
r_void
op_star
r_virtual
)paren
(brace
r_int
r_int
id|vaddr
op_assign
(paren
r_int
r_int
)paren
r_virtual
op_amp
id|PAGE_MASK
suffix:semicolon
r_struct
id|resource
op_star
id|res
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_assign
id|_sparc_find_resource
c_func
(paren
op_amp
id|sparc_iomap
comma
id|vaddr
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;free_io/iounmap: cannot free %lx&bslash;n&quot;
comma
id|vaddr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|_sparc_free_io
c_func
(paren
id|res
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_char
op_star
)paren
id|res
op_ge
(paren
r_char
op_star
)paren
id|xresv
op_logical_and
(paren
r_char
op_star
)paren
id|res
OL
(paren
r_char
op_star
)paren
op_amp
id|xresv
(braket
id|XNRES
)braket
)paren
(brace
id|xres_free
c_func
(paren
(paren
r_struct
id|xresource
op_star
)paren
id|res
)paren
suffix:semicolon
)brace
r_else
(brace
id|kfree
c_func
(paren
id|res
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; */
DECL|function|sbus_ioremap
r_int
r_int
id|sbus_ioremap
c_func
(paren
r_struct
id|resource
op_star
id|phyres
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
r_char
op_star
id|name
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|_sparc_alloc_io
c_func
(paren
id|phyres-&gt;flags
op_amp
l_int|0xF
comma
id|phyres-&gt;start
op_plus
id|offset
comma
id|size
comma
id|name
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; */
DECL|function|sbus_iounmap
r_void
id|sbus_iounmap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Meat of mapping&n; */
DECL|function|_sparc_alloc_io
r_static
r_void
op_star
id|_sparc_alloc_io
c_func
(paren
r_int
r_int
id|busno
comma
r_int
r_int
id|phys
comma
r_int
r_int
id|size
comma
r_char
op_star
id|name
)paren
(brace
r_static
r_int
id|printed_full
suffix:semicolon
r_struct
id|xresource
op_star
id|xres
suffix:semicolon
r_struct
id|resource
op_star
id|res
suffix:semicolon
r_char
op_star
id|tack
suffix:semicolon
r_int
id|tlen
suffix:semicolon
r_void
op_star
id|va
suffix:semicolon
multiline_comment|/* P3 diag */
r_if
c_cond
(paren
id|name
op_eq
l_int|NULL
)paren
id|name
op_assign
l_string|&quot;???&quot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|xres
op_assign
id|xres_alloc
c_func
(paren
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|tack
op_assign
id|xres-&gt;xname
suffix:semicolon
id|res
op_assign
op_amp
id|xres-&gt;xres
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|printed_full
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ioremap: done with statics, switching to malloc&bslash;n&quot;
)paren
suffix:semicolon
id|printed_full
op_assign
l_int|1
suffix:semicolon
)brace
id|tlen
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
id|tack
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|resource
)paren
op_plus
id|tlen
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tack
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|tack
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|resource
)paren
)paren
suffix:semicolon
id|res
op_assign
(paren
r_struct
id|resource
op_star
)paren
id|tack
suffix:semicolon
id|tack
op_add_assign
r_sizeof
(paren
r_struct
id|resource
)paren
suffix:semicolon
)brace
id|strlcpy
c_func
(paren
id|tack
comma
id|name
comma
id|XNMLN
op_plus
l_int|1
)paren
suffix:semicolon
id|res-&gt;name
op_assign
id|tack
suffix:semicolon
id|va
op_assign
id|_sparc_ioremap
c_func
(paren
id|res
comma
id|busno
comma
id|phys
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* printk(&quot;ioremap(0x%x:%08lx[0x%lx])=%p&bslash;n&quot;, busno, phys, size, va); */
multiline_comment|/* P3 diag */
r_return
id|va
suffix:semicolon
)brace
multiline_comment|/*&n; */
r_static
r_void
op_star
DECL|function|_sparc_ioremap
id|_sparc_ioremap
c_func
(paren
r_struct
id|resource
op_star
id|res
comma
id|u32
id|bus
comma
id|u32
id|pa
comma
r_int
id|sz
)paren
(brace
r_int
r_int
id|offset
op_assign
(paren
(paren
r_int
r_int
)paren
id|pa
)paren
op_amp
(paren
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|allocate_resource
c_func
(paren
op_amp
id|sparc_iomap
comma
id|res
comma
(paren
id|offset
op_plus
id|sz
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
id|PAGE_MASK
comma
id|sparc_iomap.start
comma
id|sparc_iomap.end
comma
id|PAGE_SIZE
comma
l_int|NULL
comma
l_int|NULL
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Usually we cannot see printks in this case. */
id|prom_printf
c_func
(paren
l_string|&quot;alloc_io_res(%s): cannot occupy&bslash;n&quot;
comma
(paren
id|res-&gt;name
op_ne
l_int|NULL
)paren
ques
c_cond
id|res-&gt;name
suffix:colon
l_string|&quot;???&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|pa
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|sparc_mapiorange
c_func
(paren
id|bus
comma
id|pa
comma
id|res-&gt;start
comma
id|res-&gt;end
op_minus
id|res-&gt;start
op_plus
l_int|1
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
(paren
id|res-&gt;start
op_plus
id|offset
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Comlimentary to _sparc_ioremap().&n; */
DECL|function|_sparc_free_io
r_static
r_void
id|_sparc_free_io
c_func
(paren
r_struct
id|resource
op_star
id|res
)paren
(brace
r_int
r_int
id|plen
suffix:semicolon
id|plen
op_assign
id|res-&gt;end
op_minus
id|res-&gt;start
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|plen
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_ne
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|sparc_unmapiorange
c_func
(paren
id|res-&gt;start
comma
id|plen
)paren
suffix:semicolon
id|release_resource
c_func
(paren
id|res
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SBUS
DECL|function|sbus_set_sbus64
r_void
id|sbus_set_sbus64
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
comma
r_int
id|x
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sbus_set_sbus64: unsupported&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Allocate a chunk of memory suitable for DMA.&n; * Typically devices use them for control blocks.&n; * CPU may access them without any explicit flushing.&n; *&n; * XXX Some clever people know that sdev is not used and supply NULL. Watch.&n; */
DECL|function|sbus_alloc_consistent
r_void
op_star
id|sbus_alloc_consistent
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
comma
r_int
id|len
comma
id|u32
op_star
id|dma_addrp
)paren
(brace
r_int
r_int
id|len_total
op_assign
(paren
id|len
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
r_int
r_int
id|va
suffix:semicolon
r_struct
id|resource
op_star
id|res
suffix:semicolon
r_int
id|order
suffix:semicolon
multiline_comment|/* XXX why are some lenghts signed, others unsigned? */
r_if
c_cond
(paren
id|len
op_le
l_int|0
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* XXX So what is maxphys for us and how do drivers know it? */
r_if
c_cond
(paren
id|len
OG
l_int|256
op_star
l_int|1024
)paren
(brace
multiline_comment|/* __get_free_pages() limit */
r_return
l_int|NULL
suffix:semicolon
)brace
id|order
op_assign
id|get_order
c_func
(paren
id|len_total
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|va
op_assign
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
id|order
)paren
)paren
op_eq
l_int|0
)paren
r_goto
id|err_nopages
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|resource
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|err_nomem
suffix:semicolon
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
id|res
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|resource
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|allocate_resource
c_func
(paren
op_amp
id|_sparc_dvma
comma
id|res
comma
id|len_total
comma
id|_sparc_dvma.start
comma
id|_sparc_dvma.end
comma
id|PAGE_SIZE
comma
l_int|NULL
comma
l_int|NULL
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sbus_alloc_consistent: cannot occupy 0x%lx&quot;
comma
id|len_total
)paren
suffix:semicolon
r_goto
id|err_nova
suffix:semicolon
)brace
id|mmu_inval_dma_area
c_func
(paren
id|va
comma
id|len_total
)paren
suffix:semicolon
singleline_comment|// XXX The mmu_map_dma_area does this for us below, see comments.
singleline_comment|// sparc_mapiorange(0, virt_to_phys(va), res-&gt;start, len_total);
multiline_comment|/*&n;&t; * XXX That&squot;s where sdev would be used. Currently we load&n;&t; * all iommu tables with the same translations.&n;&t; */
r_if
c_cond
(paren
id|mmu_map_dma_area
c_func
(paren
id|dma_addrp
comma
id|va
comma
id|res-&gt;start
comma
id|len_total
)paren
op_ne
l_int|0
)paren
r_goto
id|err_noiommu
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|res-&gt;start
suffix:semicolon
id|err_noiommu
suffix:colon
id|release_resource
c_func
(paren
id|res
)paren
suffix:semicolon
id|err_nova
suffix:colon
id|free_pages
c_func
(paren
id|va
comma
id|order
)paren
suffix:semicolon
id|err_nomem
suffix:colon
id|kfree
c_func
(paren
id|res
)paren
suffix:semicolon
id|err_nopages
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|sbus_free_consistent
r_void
id|sbus_free_consistent
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
comma
r_int
id|n
comma
r_void
op_star
id|p
comma
id|u32
id|ba
)paren
(brace
r_struct
id|resource
op_star
id|res
suffix:semicolon
r_struct
id|page
op_star
id|pgv
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_assign
id|_sparc_find_resource
c_func
(paren
op_amp
id|_sparc_dvma
comma
(paren
r_int
r_int
)paren
id|p
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sbus_free_consistent: cannot free %p&bslash;n&quot;
comma
id|p
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|p
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sbus_free_consistent: unaligned va %p&bslash;n&quot;
comma
id|p
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|n
op_assign
(paren
id|n
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res-&gt;end
op_minus
id|res-&gt;start
)paren
op_plus
l_int|1
op_ne
id|n
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sbus_free_consistent: region 0x%lx asked 0x%lx&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
(paren
id|res-&gt;end
op_minus
id|res-&gt;start
)paren
op_plus
l_int|1
)paren
comma
id|n
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|release_resource
c_func
(paren
id|res
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|res
)paren
suffix:semicolon
multiline_comment|/* mmu_inval_dma_area(va, n); */
multiline_comment|/* it&squot;s consistent, isn&squot;t it */
id|pgv
op_assign
id|mmu_translate_dvma
c_func
(paren
id|ba
)paren
suffix:semicolon
id|mmu_unmap_dma_area
c_func
(paren
id|ba
comma
id|n
)paren
suffix:semicolon
id|__free_pages
c_func
(paren
id|pgv
comma
id|get_order
c_func
(paren
id|n
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Map a chunk of memory so that devices can see it.&n; * CPU view of this memory may be inconsistent with&n; * a device view and explicit flushing is necessary.&n; */
DECL|function|sbus_map_single
id|dma_addr_t
id|sbus_map_single
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
comma
r_void
op_star
id|va
comma
r_int
id|len
comma
r_int
id|direction
)paren
(brace
multiline_comment|/* XXX why are some lenghts signed, others unsigned? */
r_if
c_cond
(paren
id|len
op_le
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* XXX So what is maxphys for us and how do drivers know it? */
r_if
c_cond
(paren
id|len
OG
l_int|256
op_star
l_int|1024
)paren
(brace
multiline_comment|/* __get_free_pages() limit */
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|mmu_get_scsi_one
c_func
(paren
id|va
comma
id|len
comma
id|sdev-&gt;bus
)paren
suffix:semicolon
)brace
DECL|function|sbus_unmap_single
r_void
id|sbus_unmap_single
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
comma
id|dma_addr_t
id|ba
comma
r_int
id|n
comma
r_int
id|direction
)paren
(brace
id|mmu_release_scsi_one
c_func
(paren
id|ba
comma
id|n
comma
id|sdev-&gt;bus
)paren
suffix:semicolon
)brace
DECL|function|sbus_map_sg
r_int
id|sbus_map_sg
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|n
comma
r_int
id|direction
)paren
(brace
id|mmu_get_scsi_sgl
c_func
(paren
id|sg
comma
id|n
comma
id|sdev-&gt;bus
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * XXX sparc64 can return a partial length here. sun4c should do this&n;&t; * but it currently panics if it can&squot;t fulfill the request - Anton&n;&t; */
r_return
id|n
suffix:semicolon
)brace
DECL|function|sbus_unmap_sg
r_void
id|sbus_unmap_sg
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|n
comma
r_int
id|direction
)paren
(brace
id|mmu_release_scsi_sgl
c_func
(paren
id|sg
comma
id|n
comma
id|sdev-&gt;bus
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; */
DECL|function|sbus_dma_sync_single
r_void
id|sbus_dma_sync_single
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
comma
id|dma_addr_t
id|ba
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
macro_line|#if 0
r_int
r_int
id|va
suffix:semicolon
r_struct
id|resource
op_star
id|res
suffix:semicolon
multiline_comment|/* We do not need the resource, just print a message if invalid. */
id|res
op_assign
id|_sparc_find_resource
c_func
(paren
op_amp
id|_sparc_dvma
comma
id|ba
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
l_int|NULL
)paren
id|panic
c_func
(paren
l_string|&quot;sbus_dma_sync_single: 0x%x&bslash;n&quot;
comma
id|ba
)paren
suffix:semicolon
id|va
op_assign
id|page_address
c_func
(paren
id|mmu_translate_dvma
c_func
(paren
id|ba
)paren
)paren
suffix:semicolon
multiline_comment|/* XXX higmem */
multiline_comment|/*&n;&t; * XXX This bogosity will be fixed with the iommu rewrite coming soon&n;&t; * to a kernel near you. - Anton&n;&t; */
multiline_comment|/* mmu_inval_dma_area(va, (size + PAGE_SIZE-1) &amp; PAGE_MASK); */
macro_line|#endif
)brace
DECL|function|sbus_dma_sync_sg
r_void
id|sbus_dma_sync_sg
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|n
comma
r_int
id|direction
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sbus_dma_sync_sg: not implemented yet&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SBUS */
macro_line|#ifdef CONFIG_PCI
multiline_comment|/* Allocate and map kernel buffer using consistent mode DMA for a device.&n; * hwdev should be valid struct pci_dev pointer for PCI devices.&n; */
DECL|function|pci_alloc_consistent
r_void
op_star
id|pci_alloc_consistent
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_int
id|len
comma
id|dma_addr_t
op_star
id|pba
)paren
(brace
r_int
r_int
id|len_total
op_assign
(paren
id|len
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
r_int
r_int
id|va
suffix:semicolon
r_struct
id|resource
op_star
id|res
suffix:semicolon
r_int
id|order
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OG
l_int|256
op_star
l_int|1024
)paren
(brace
multiline_comment|/* __get_free_pages() limit */
r_return
l_int|NULL
suffix:semicolon
)brace
id|order
op_assign
id|get_order
c_func
(paren
id|len_total
)paren
suffix:semicolon
id|va
op_assign
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
id|order
)paren
suffix:semicolon
r_if
c_cond
(paren
id|va
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pci_alloc_consistent: no %ld pages&bslash;n&quot;
comma
id|len_total
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|res
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|resource
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|free_pages
c_func
(paren
id|va
comma
id|order
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;pci_alloc_consistent: no core&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
id|res
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|resource
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|allocate_resource
c_func
(paren
op_amp
id|_sparc_dvma
comma
id|res
comma
id|len_total
comma
id|_sparc_dvma.start
comma
id|_sparc_dvma.end
comma
id|PAGE_SIZE
comma
l_int|NULL
comma
l_int|NULL
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pci_alloc_consistent: cannot occupy 0x%lx&quot;
comma
id|len_total
)paren
suffix:semicolon
id|free_pages
c_func
(paren
id|va
comma
id|order
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|res
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|mmu_inval_dma_area
c_func
(paren
id|va
comma
id|len_total
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/* P3 */
id|printk
c_func
(paren
l_string|&quot;pci_alloc_consistent: kva %lx uncva %lx phys %lx size %lx&bslash;n&quot;
comma
(paren
r_int
)paren
id|va
comma
(paren
r_int
)paren
id|res-&gt;start
comma
(paren
r_int
)paren
id|virt_to_phys
c_func
(paren
id|va
)paren
comma
id|len_total
)paren
suffix:semicolon
macro_line|#endif
id|sparc_mapiorange
c_func
(paren
l_int|0
comma
id|virt_to_phys
c_func
(paren
id|va
)paren
comma
id|res-&gt;start
comma
id|len_total
)paren
suffix:semicolon
op_star
id|pba
op_assign
id|virt_to_phys
c_func
(paren
id|va
)paren
suffix:semicolon
multiline_comment|/* equals virt_to_bus (R.I.P.) for us. */
r_return
(paren
r_void
op_star
)paren
id|res-&gt;start
suffix:semicolon
)brace
multiline_comment|/* Free and unmap a consistent DMA buffer.&n; * cpu_addr is what was returned from pci_alloc_consistent,&n; * size must be the same as what as passed into pci_alloc_consistent,&n; * and likewise dma_addr must be the same as what *dma_addrp was set to.&n; *&n; * References to the memory and mappings assosciated with cpu_addr/dma_addr&n; * past this call are illegal.&n; */
DECL|function|pci_free_consistent
r_void
id|pci_free_consistent
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_int
id|n
comma
r_void
op_star
id|p
comma
id|dma_addr_t
id|ba
)paren
(brace
r_struct
id|resource
op_star
id|res
suffix:semicolon
r_int
r_int
id|pgp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_assign
id|_sparc_find_resource
c_func
(paren
op_amp
id|_sparc_dvma
comma
(paren
r_int
r_int
)paren
id|p
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pci_free_consistent: cannot free %p&bslash;n&quot;
comma
id|p
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|p
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pci_free_consistent: unaligned va %p&bslash;n&quot;
comma
id|p
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|n
op_assign
(paren
id|n
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res-&gt;end
op_minus
id|res-&gt;start
)paren
op_plus
l_int|1
op_ne
id|n
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pci_free_consistent: region 0x%lx asked 0x%lx&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
(paren
id|res-&gt;end
op_minus
id|res-&gt;start
)paren
op_plus
l_int|1
)paren
comma
(paren
r_int
)paren
id|n
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pgp
op_assign
(paren
r_int
r_int
)paren
id|phys_to_virt
c_func
(paren
id|ba
)paren
suffix:semicolon
multiline_comment|/* bus_to_virt actually */
id|mmu_inval_dma_area
c_func
(paren
id|pgp
comma
id|n
)paren
suffix:semicolon
id|sparc_unmapiorange
c_func
(paren
(paren
r_int
r_int
)paren
id|p
comma
id|n
)paren
suffix:semicolon
id|release_resource
c_func
(paren
id|res
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|res
)paren
suffix:semicolon
id|free_pages
c_func
(paren
id|pgp
comma
id|get_order
c_func
(paren
id|n
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Map a single buffer of the indicated size for DMA in streaming mode.&n; * The 32-bit bus address to use is returned.&n; *&n; * Once the device is given the dma address, the device owns this memory&n; * until either pci_unmap_single or pci_dma_sync_single is performed.&n; */
DECL|function|pci_map_single
id|dma_addr_t
id|pci_map_single
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_void
op_star
id|ptr
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* IIep is write-through, not flushing. */
r_return
id|virt_to_phys
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
multiline_comment|/* Unmap a single streaming mode DMA translation.  The dma_addr and size&n; * must match what was provided for in a previous pci_map_single call.  All&n; * other usages are undefined.&n; *&n; * After this call, reads by the cpu to the buffer are guaranteed to see&n; * whatever the device wrote there.&n; */
DECL|function|pci_unmap_single
r_void
id|pci_unmap_single
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
id|dma_addr_t
id|ba
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_ne
id|PCI_DMA_TODEVICE
)paren
(brace
id|mmu_inval_dma_area
c_func
(paren
(paren
r_int
r_int
)paren
id|phys_to_virt
c_func
(paren
id|ba
)paren
comma
(paren
id|size
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Map a set of buffers described by scatterlist in streaming&n; * mode for DMA.  This is the scather-gather version of the&n; * above pci_map_single interface.  Here the scatter gather list&n; * elements are each tagged with the appropriate dma address&n; * and length.  They are obtained via sg_dma_{address,length}(SG).&n; *&n; * NOTE: An implementation may be able to use a smaller number of&n; *       DMA address/length pairs than there are SG table elements.&n; *       (for example via virtual mapping capabilities)&n; *       The routine returns the number of addr/length pairs actually&n; *       used, at most nents.&n; *&n; * Device ownership issues as mentioned above for pci_map_single are&n; * the same here.&n; */
DECL|function|pci_map_sg
r_int
id|pci_map_sg
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nents
comma
r_int
id|direction
)paren
(brace
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* IIep is write-through, not flushing. */
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|nents
suffix:semicolon
id|n
op_increment
)paren
(brace
r_if
c_cond
(paren
id|page_address
c_func
(paren
id|sg-&gt;page
)paren
op_eq
l_int|NULL
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|sg-&gt;dvma_address
op_assign
id|virt_to_phys
c_func
(paren
id|page_address
c_func
(paren
id|sg-&gt;page
)paren
)paren
suffix:semicolon
id|sg-&gt;dvma_length
op_assign
id|sg-&gt;length
suffix:semicolon
id|sg
op_increment
suffix:semicolon
)brace
r_return
id|nents
suffix:semicolon
)brace
multiline_comment|/* Unmap a set of streaming mode DMA translations.&n; * Again, cpu read rules concerning calls here are the same as for&n; * pci_unmap_single() above.&n; */
DECL|function|pci_unmap_sg
r_void
id|pci_unmap_sg
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nents
comma
r_int
id|direction
)paren
(brace
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_ne
id|PCI_DMA_TODEVICE
)paren
(brace
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|nents
suffix:semicolon
id|n
op_increment
)paren
(brace
r_if
c_cond
(paren
id|page_address
c_func
(paren
id|sg-&gt;page
)paren
op_eq
l_int|NULL
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|mmu_inval_dma_area
c_func
(paren
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|sg-&gt;page
)paren
comma
(paren
id|sg-&gt;length
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
id|sg
op_increment
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Make physical memory consistent for a single&n; * streaming mode DMA translation before or after a transfer.&n; *&n; * If you perform a pci_map_single() but wish to interrogate the&n; * buffer using the cpu, yet do not wish to teardown the PCI dma&n; * mapping, you must call this function before doing so.  At the&n; * next point you give the PCI dma address back to the card, the&n; * device again owns the buffer.&n; */
DECL|function|pci_dma_sync_single
r_void
id|pci_dma_sync_single
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
id|dma_addr_t
id|ba
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_ne
id|PCI_DMA_TODEVICE
)paren
(brace
id|mmu_inval_dma_area
c_func
(paren
(paren
r_int
r_int
)paren
id|phys_to_virt
c_func
(paren
id|ba
)paren
comma
(paren
id|size
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Make physical memory consistent for a set of streaming&n; * mode DMA translations after a transfer.&n; *&n; * The same as pci_dma_sync_single but for a scatter-gather list,&n; * same rules and usage.&n; */
DECL|function|pci_dma_sync_sg
r_void
id|pci_dma_sync_sg
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nents
comma
r_int
id|direction
)paren
(brace
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_ne
id|PCI_DMA_TODEVICE
)paren
(brace
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|nents
suffix:semicolon
id|n
op_increment
)paren
(brace
r_if
c_cond
(paren
id|page_address
c_func
(paren
id|sg-&gt;page
)paren
op_eq
l_int|NULL
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|mmu_inval_dma_area
c_func
(paren
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|sg-&gt;page
)paren
comma
(paren
id|sg-&gt;length
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
id|sg
op_increment
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif /* CONFIG_PCI */
macro_line|#ifdef CONFIG_PROC_FS
r_static
r_int
DECL|function|_sparc_io_get_info
id|_sparc_io_get_info
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|fpos
comma
r_int
id|length
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_char
op_star
id|p
op_assign
id|buf
comma
op_star
id|e
op_assign
id|buf
op_plus
id|length
suffix:semicolon
r_struct
id|resource
op_star
id|r
suffix:semicolon
r_const
r_char
op_star
id|nm
suffix:semicolon
r_for
c_loop
(paren
id|r
op_assign
(paren
(paren
r_struct
id|resource
op_star
)paren
id|data
)paren
op_member_access_from_pointer
id|child
suffix:semicolon
id|r
op_ne
l_int|NULL
suffix:semicolon
id|r
op_assign
id|r-&gt;sibling
)paren
(brace
r_if
c_cond
(paren
id|p
op_plus
l_int|32
op_ge
id|e
)paren
multiline_comment|/* Better than nothing */
r_break
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nm
op_assign
id|r-&gt;name
)paren
op_eq
l_int|0
)paren
id|nm
op_assign
l_string|&quot;???&quot;
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%08lx-%08lx: %s&bslash;n&quot;
comma
id|r-&gt;start
comma
id|r-&gt;end
comma
id|nm
)paren
suffix:semicolon
)brace
r_return
id|p
op_minus
id|buf
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PROC_FS */
multiline_comment|/*&n; * This is a version of find_resource and it belongs to kernel/resource.c.&n; * Until we have agreement with Linus and Martin, it lingers here.&n; *&n; * XXX Too slow. Can have 8192 DVMA pages on sun4m in the worst case.&n; * This probably warrants some sort of hashing.&n; */
r_struct
id|resource
op_star
DECL|function|_sparc_find_resource
id|_sparc_find_resource
c_func
(paren
r_struct
id|resource
op_star
id|root
comma
r_int
r_int
id|hit
)paren
(brace
r_struct
id|resource
op_star
id|tmp
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|root-&gt;child
suffix:semicolon
id|tmp
op_ne
l_int|0
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;sibling
)paren
(brace
r_if
c_cond
(paren
id|tmp-&gt;start
op_le
id|hit
op_logical_and
id|tmp-&gt;end
op_ge
id|hit
)paren
r_return
id|tmp
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|register_proc_sparc_ioport
r_void
id|register_proc_sparc_ioport
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PROC_FS
id|create_proc_read_entry
c_func
(paren
l_string|&quot;io_map&quot;
comma
l_int|0
comma
l_int|0
comma
id|_sparc_io_get_info
comma
op_amp
id|sparc_iomap
)paren
suffix:semicolon
id|create_proc_read_entry
c_func
(paren
l_string|&quot;dvma_map&quot;
comma
l_int|0
comma
l_int|0
comma
id|_sparc_io_get_info
comma
op_amp
id|_sparc_dvma
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
