multiline_comment|/*&n; * iommu.c:  IOMMU specific routines for memory management.&n; *&n; * Copyright (C) 1995 David S. Miller  (davem@caip.rutgers.edu)&n; * Copyright (C) 1995,2002 Pete Zaitcev     (zaitcev@yahoo.com)&n; * Copyright (C) 1996 Eddie C. Dost    (ecd@skynet.be)&n; * Copyright (C) 1997,1998 Jakub Jelinek    (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;&t;/* pte_offset_map =&gt; kmap_atomic */
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mxcc.h&gt;
macro_line|#include &lt;asm/mbus.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/bitext.h&gt;
macro_line|#include &lt;asm/iommu.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
multiline_comment|/*&n; * This can be sized dynamically, but we will do this&n; * only when we have a guidance about actual I/O pressures.&n; */
DECL|macro|IOMMU_RNGE
mdefine_line|#define IOMMU_RNGE&t;IOMMU_RNGE_256MB
DECL|macro|IOMMU_START
mdefine_line|#define IOMMU_START&t;0xF0000000
DECL|macro|IOMMU_WINSIZE
mdefine_line|#define IOMMU_WINSIZE&t;(256*1024*1024U)
DECL|macro|IOMMU_NPTES
mdefine_line|#define IOMMU_NPTES&t;(IOMMU_WINSIZE/PAGE_SIZE)&t;/* 64K PTEs, 265KB */
DECL|macro|IOMMU_ORDER
mdefine_line|#define IOMMU_ORDER&t;6&t;&t;&t;&t;/* 4096 * (1&lt;&lt;6) */
multiline_comment|/* srmmu.c */
r_extern
r_int
id|viking_mxcc_present
suffix:semicolon
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|flush_page_for_dma
comma
r_int
r_int
)paren
DECL|macro|flush_page_for_dma
mdefine_line|#define flush_page_for_dma(page) BTFIXUP_CALL(flush_page_for_dma)(page)
r_extern
r_int
id|flush_page_for_dma_global
suffix:semicolon
DECL|variable|viking_flush
r_static
r_int
id|viking_flush
suffix:semicolon
multiline_comment|/* viking.S */
r_extern
r_void
id|viking_flush_page
c_func
(paren
r_int
r_int
id|page
)paren
suffix:semicolon
r_extern
r_void
id|viking_mxcc_flush_page
c_func
(paren
r_int
r_int
id|page
)paren
suffix:semicolon
multiline_comment|/*&n; * Values precomputed according to CPU type.&n; */
DECL|variable|ioperm_noc
r_static
r_int
r_int
id|ioperm_noc
suffix:semicolon
multiline_comment|/* Consistent mapping iopte flags */
DECL|variable|dvma_prot
r_static
id|pgprot_t
id|dvma_prot
suffix:semicolon
multiline_comment|/* Consistent mapping pte flags */
DECL|macro|IOPERM
mdefine_line|#define IOPERM        (IOPTE_CACHE | IOPTE_WRITE | IOPTE_VALID)
DECL|macro|MKIOPTE
mdefine_line|#define MKIOPTE(pfn, perm) (((((pfn)&lt;&lt;8) &amp; IOPTE_PAGE) | (perm)) &amp; ~IOPTE_WAZ)
r_void
id|__init
DECL|function|iommu_init
id|iommu_init
c_func
(paren
r_int
id|iommund
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
r_int
r_int
id|impl
comma
id|vers
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_struct
id|iommu_struct
op_star
id|iommu
suffix:semicolon
r_struct
id|linux_prom_registers
id|iommu_promregs
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
r_struct
id|resource
id|r
suffix:semicolon
r_int
r_int
op_star
id|bitmap
suffix:semicolon
id|iommu
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|iommu_struct
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iommu
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Unable to allocate iommu structure&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|prom_getproperty
c_func
(paren
id|iommund
comma
l_string|&quot;reg&quot;
comma
(paren
r_void
op_star
)paren
id|iommu_promregs
comma
r_sizeof
(paren
id|iommu_promregs
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|r
comma
l_int|0
comma
r_sizeof
(paren
id|r
)paren
)paren
suffix:semicolon
id|r.flags
op_assign
id|iommu_promregs
(braket
l_int|0
)braket
dot
id|which_io
suffix:semicolon
id|r.start
op_assign
id|iommu_promregs
(braket
l_int|0
)braket
dot
id|phys_addr
suffix:semicolon
id|iommu-&gt;regs
op_assign
(paren
r_struct
id|iommu_regs
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|r
comma
l_int|0
comma
id|PAGE_SIZE
op_star
l_int|3
comma
l_string|&quot;iommu_regs&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iommu-&gt;regs
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Cannot map IOMMU registers&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|impl
op_assign
(paren
id|iommu-&gt;regs-&gt;control
op_amp
id|IOMMU_CTRL_IMPL
)paren
op_rshift
l_int|28
suffix:semicolon
id|vers
op_assign
(paren
id|iommu-&gt;regs-&gt;control
op_amp
id|IOMMU_CTRL_VERS
)paren
op_rshift
l_int|24
suffix:semicolon
id|tmp
op_assign
id|iommu-&gt;regs-&gt;control
suffix:semicolon
id|tmp
op_and_assign
op_complement
(paren
id|IOMMU_CTRL_RNGE
)paren
suffix:semicolon
id|tmp
op_or_assign
(paren
id|IOMMU_RNGE_256MB
op_or
id|IOMMU_CTRL_ENAB
)paren
suffix:semicolon
id|iommu-&gt;regs-&gt;control
op_assign
id|tmp
suffix:semicolon
id|iommu_invalidate
c_func
(paren
id|iommu-&gt;regs
)paren
suffix:semicolon
id|iommu-&gt;start
op_assign
id|IOMMU_START
suffix:semicolon
id|iommu-&gt;end
op_assign
l_int|0xffffffff
suffix:semicolon
multiline_comment|/* Allocate IOMMU page table */
multiline_comment|/* Stupid alignment constraints give me a headache. &n;&t;   We need 256K or 512K or 1M or 2M area aligned to&n;           its size and current gfp will fortunately give&n;           it to us. */
id|tmp
op_assign
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
id|IOMMU_ORDER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Unable to allocate iommu table [0x%08x]&bslash;n&quot;
comma
id|IOMMU_NPTES
op_star
r_sizeof
(paren
id|iopte_t
)paren
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|iommu-&gt;page_table
op_assign
(paren
id|iopte_t
op_star
)paren
id|tmp
suffix:semicolon
multiline_comment|/* Initialize new table. */
id|memset
c_func
(paren
id|iommu-&gt;page_table
comma
l_int|0
comma
id|IOMMU_NPTES
op_star
r_sizeof
(paren
id|iopte_t
)paren
)paren
suffix:semicolon
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
id|iommu-&gt;regs-&gt;base
op_assign
id|__pa
c_func
(paren
(paren
r_int
r_int
)paren
id|iommu-&gt;page_table
)paren
op_rshift
l_int|4
suffix:semicolon
id|iommu_invalidate
c_func
(paren
id|iommu-&gt;regs
)paren
suffix:semicolon
id|bitmap
op_assign
id|kmalloc
c_func
(paren
id|IOMMU_NPTES
op_rshift
l_int|3
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bitmap
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Unable to allocate iommu bitmap [%d]&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
id|IOMMU_NPTES
op_rshift
l_int|3
)paren
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|bit_map_init
c_func
(paren
op_amp
id|iommu-&gt;usemap
comma
id|bitmap
comma
id|IOMMU_NPTES
)paren
suffix:semicolon
multiline_comment|/* To be coherent on HyperSparc, the page color of DVMA&n;&t; * and physical addresses must match.&n;&t; */
r_if
c_cond
(paren
id|srmmu_modtype
op_eq
id|HyperSparc
)paren
id|iommu-&gt;usemap.num_colors
op_assign
id|vac_cache_size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_else
id|iommu-&gt;usemap.num_colors
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;IOMMU: impl %d vers %d table 0x%p[%d B] map [%d b]&bslash;n&quot;
comma
id|impl
comma
id|vers
comma
id|iommu-&gt;page_table
comma
(paren
r_int
)paren
(paren
id|IOMMU_NPTES
op_star
r_sizeof
(paren
id|iopte_t
)paren
)paren
comma
(paren
r_int
)paren
id|IOMMU_NPTES
)paren
suffix:semicolon
id|sbus-&gt;iommu
op_assign
id|iommu
suffix:semicolon
)brace
multiline_comment|/* This begs to be btfixup-ed by srmmu. */
multiline_comment|/* Flush the iotlb entries to ram. */
multiline_comment|/* This could be better if we didn&squot;t have to flush whole pages. */
DECL|function|iommu_flush_iotlb
r_static
r_void
id|iommu_flush_iotlb
c_func
(paren
id|iopte_t
op_star
id|iopte
comma
r_int
r_int
id|niopte
)paren
(brace
r_int
r_int
id|start
suffix:semicolon
r_int
r_int
id|end
suffix:semicolon
id|start
op_assign
(paren
r_int
r_int
)paren
id|iopte
op_amp
id|PAGE_MASK
suffix:semicolon
id|end
op_assign
id|PAGE_ALIGN
c_func
(paren
id|start
op_plus
id|niopte
op_star
r_sizeof
(paren
id|iopte_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|viking_mxcc_present
)paren
(brace
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|viking_mxcc_flush_page
c_func
(paren
id|start
)paren
suffix:semicolon
id|start
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|viking_flush
)paren
(brace
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|viking_flush_page
c_func
(paren
id|start
)paren
suffix:semicolon
id|start
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
r_else
(brace
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|__flush_page_to_ram
c_func
(paren
id|start
)paren
suffix:semicolon
id|start
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
)brace
DECL|function|iommu_get_one
r_static
id|u32
id|iommu_get_one
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|npages
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
r_struct
id|iommu_struct
op_star
id|iommu
op_assign
id|sbus-&gt;iommu
suffix:semicolon
r_int
id|ioptex
suffix:semicolon
id|iopte_t
op_star
id|iopte
comma
op_star
id|iopte0
suffix:semicolon
r_int
r_int
id|busa
comma
id|busa0
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* page color = pfn of page */
id|ioptex
op_assign
id|bit_map_string_get
c_func
(paren
op_amp
id|iommu-&gt;usemap
comma
id|npages
comma
id|page_to_pfn
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ioptex
OL
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;iommu out&quot;
)paren
suffix:semicolon
id|busa0
op_assign
id|iommu-&gt;start
op_plus
(paren
id|ioptex
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|iopte0
op_assign
op_amp
id|iommu-&gt;page_table
(braket
id|ioptex
)braket
suffix:semicolon
id|busa
op_assign
id|busa0
suffix:semicolon
id|iopte
op_assign
id|iopte0
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
id|npages
suffix:semicolon
id|i
op_increment
)paren
(brace
id|iopte_val
c_func
(paren
op_star
id|iopte
)paren
op_assign
id|MKIOPTE
c_func
(paren
id|page_to_pfn
c_func
(paren
id|page
)paren
comma
id|IOPERM
)paren
suffix:semicolon
id|iommu_invalidate_page
c_func
(paren
id|iommu-&gt;regs
comma
id|busa
)paren
suffix:semicolon
id|busa
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|iopte
op_increment
suffix:semicolon
id|page
op_increment
suffix:semicolon
)brace
id|iommu_flush_iotlb
c_func
(paren
id|iopte0
comma
id|npages
)paren
suffix:semicolon
r_return
id|busa0
suffix:semicolon
)brace
DECL|function|iommu_get_scsi_one
r_static
id|u32
id|iommu_get_scsi_one
c_func
(paren
r_char
op_star
id|vaddr
comma
r_int
r_int
id|len
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
r_int
r_int
id|off
suffix:semicolon
r_int
id|npages
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|u32
id|busa
suffix:semicolon
id|off
op_assign
(paren
r_int
r_int
)paren
id|vaddr
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
id|npages
op_assign
(paren
id|off
op_plus
id|len
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|page
op_assign
id|virt_to_page
c_func
(paren
(paren
r_int
r_int
)paren
id|vaddr
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
id|busa
op_assign
id|iommu_get_one
c_func
(paren
id|page
comma
id|npages
comma
id|sbus
)paren
suffix:semicolon
r_return
id|busa
op_plus
id|off
suffix:semicolon
)brace
DECL|function|iommu_get_scsi_one_noflush
r_static
id|__u32
id|iommu_get_scsi_one_noflush
c_func
(paren
r_char
op_star
id|vaddr
comma
r_int
r_int
id|len
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
r_return
id|iommu_get_scsi_one
c_func
(paren
id|vaddr
comma
id|len
comma
id|sbus
)paren
suffix:semicolon
)brace
DECL|function|iommu_get_scsi_one_gflush
r_static
id|__u32
id|iommu_get_scsi_one_gflush
c_func
(paren
r_char
op_star
id|vaddr
comma
r_int
r_int
id|len
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
id|flush_page_for_dma
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
id|iommu_get_scsi_one
c_func
(paren
id|vaddr
comma
id|len
comma
id|sbus
)paren
suffix:semicolon
)brace
DECL|function|iommu_get_scsi_one_pflush
r_static
id|__u32
id|iommu_get_scsi_one_pflush
c_func
(paren
r_char
op_star
id|vaddr
comma
r_int
r_int
id|len
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
r_int
r_int
id|page
op_assign
(paren
(paren
r_int
r_int
)paren
id|vaddr
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
r_while
c_loop
(paren
id|page
OL
(paren
(paren
r_int
r_int
)paren
(paren
id|vaddr
op_plus
id|len
)paren
)paren
)paren
(brace
id|flush_page_for_dma
c_func
(paren
id|page
)paren
suffix:semicolon
id|page
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_return
id|iommu_get_scsi_one
c_func
(paren
id|vaddr
comma
id|len
comma
id|sbus
)paren
suffix:semicolon
)brace
DECL|function|iommu_get_scsi_sgl_noflush
r_static
r_void
id|iommu_get_scsi_sgl_noflush
c_func
(paren
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|sz
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
r_int
id|n
suffix:semicolon
r_while
c_loop
(paren
id|sz
op_ne
l_int|0
)paren
(brace
op_decrement
id|sz
suffix:semicolon
id|n
op_assign
(paren
id|sg-&gt;length
op_plus
id|sg-&gt;offset
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|sg-&gt;dvma_address
op_assign
id|iommu_get_one
c_func
(paren
id|sg-&gt;page
comma
id|n
comma
id|sbus
)paren
op_plus
id|sg-&gt;offset
suffix:semicolon
id|sg-&gt;dvma_length
op_assign
(paren
id|__u32
)paren
id|sg-&gt;length
suffix:semicolon
id|sg
op_increment
suffix:semicolon
)brace
)brace
DECL|function|iommu_get_scsi_sgl_gflush
r_static
r_void
id|iommu_get_scsi_sgl_gflush
c_func
(paren
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|sz
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
r_int
id|n
suffix:semicolon
id|flush_page_for_dma
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
id|sz
op_ne
l_int|0
)paren
(brace
op_decrement
id|sz
suffix:semicolon
id|n
op_assign
(paren
id|sg-&gt;length
op_plus
id|sg-&gt;offset
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|sg-&gt;dvma_address
op_assign
id|iommu_get_one
c_func
(paren
id|sg-&gt;page
comma
id|n
comma
id|sbus
)paren
op_plus
id|sg-&gt;offset
suffix:semicolon
id|sg-&gt;dvma_length
op_assign
(paren
id|__u32
)paren
id|sg-&gt;length
suffix:semicolon
id|sg
op_increment
suffix:semicolon
)brace
)brace
DECL|function|iommu_get_scsi_sgl_pflush
r_static
r_void
id|iommu_get_scsi_sgl_pflush
c_func
(paren
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|sz
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
r_int
r_int
id|page
comma
id|oldpage
op_assign
l_int|0
suffix:semicolon
r_int
id|n
comma
id|i
suffix:semicolon
r_while
c_loop
(paren
id|sz
op_ne
l_int|0
)paren
(brace
op_decrement
id|sz
suffix:semicolon
id|n
op_assign
(paren
id|sg-&gt;length
op_plus
id|sg-&gt;offset
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We expect unmapped highmem pages to be not in the cache.&n;&t;&t; * XXX Is this a good assumption?&n;&t;&t; * XXX What if someone else unmaps it here and races us?&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|page
op_assign
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|sg-&gt;page
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|page
op_ne
id|oldpage
)paren
(brace
multiline_comment|/* Already flushed? */
id|flush_page_for_dma
c_func
(paren
id|page
)paren
suffix:semicolon
id|oldpage
op_assign
id|page
suffix:semicolon
)brace
id|page
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
id|sg-&gt;dvma_address
op_assign
id|iommu_get_one
c_func
(paren
id|sg-&gt;page
comma
id|n
comma
id|sbus
)paren
op_plus
id|sg-&gt;offset
suffix:semicolon
id|sg-&gt;dvma_length
op_assign
(paren
id|__u32
)paren
id|sg-&gt;length
suffix:semicolon
id|sg
op_increment
suffix:semicolon
)brace
)brace
DECL|function|iommu_release_one
r_static
r_void
id|iommu_release_one
c_func
(paren
id|u32
id|busa
comma
r_int
id|npages
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
r_struct
id|iommu_struct
op_star
id|iommu
op_assign
id|sbus-&gt;iommu
suffix:semicolon
r_int
id|ioptex
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|busa
OL
id|iommu-&gt;start
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|ioptex
op_assign
(paren
id|busa
op_minus
id|iommu-&gt;start
)paren
op_rshift
id|PAGE_SHIFT
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
id|npages
suffix:semicolon
id|i
op_increment
)paren
(brace
id|iopte_val
c_func
(paren
id|iommu-&gt;page_table
(braket
id|ioptex
op_plus
id|i
)braket
)paren
op_assign
l_int|0
suffix:semicolon
id|iommu_invalidate_page
c_func
(paren
id|iommu-&gt;regs
comma
id|busa
)paren
suffix:semicolon
id|busa
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
id|bit_map_clear
c_func
(paren
op_amp
id|iommu-&gt;usemap
comma
id|ioptex
comma
id|npages
)paren
suffix:semicolon
)brace
DECL|function|iommu_release_scsi_one
r_static
r_void
id|iommu_release_scsi_one
c_func
(paren
id|__u32
id|vaddr
comma
r_int
r_int
id|len
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
r_int
r_int
id|off
suffix:semicolon
r_int
id|npages
suffix:semicolon
id|off
op_assign
id|vaddr
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
id|npages
op_assign
(paren
id|off
op_plus
id|len
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|iommu_release_one
c_func
(paren
id|vaddr
op_amp
id|PAGE_MASK
comma
id|npages
comma
id|sbus
)paren
suffix:semicolon
)brace
DECL|function|iommu_release_scsi_sgl
r_static
r_void
id|iommu_release_scsi_sgl
c_func
(paren
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|sz
comma
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
r_int
id|n
suffix:semicolon
r_while
c_loop
(paren
id|sz
op_ne
l_int|0
)paren
(brace
op_decrement
id|sz
suffix:semicolon
id|n
op_assign
(paren
id|sg-&gt;length
op_plus
id|sg-&gt;offset
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|iommu_release_one
c_func
(paren
id|sg-&gt;dvma_address
op_amp
id|PAGE_MASK
comma
id|n
comma
id|sbus
)paren
suffix:semicolon
id|sg-&gt;dvma_address
op_assign
l_int|0x21212121
suffix:semicolon
id|sg
op_increment
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_SBUS
DECL|function|iommu_map_dma_area
r_static
r_int
id|iommu_map_dma_area
c_func
(paren
id|dma_addr_t
op_star
id|pba
comma
r_int
r_int
id|va
comma
r_int
r_int
id|addr
comma
r_int
id|len
)paren
(brace
r_int
r_int
id|page
comma
id|end
suffix:semicolon
r_struct
id|iommu_struct
op_star
id|iommu
op_assign
id|sbus_root-&gt;iommu
suffix:semicolon
id|iopte_t
op_star
id|iopte
op_assign
id|iommu-&gt;page_table
suffix:semicolon
id|iopte_t
op_star
id|first
suffix:semicolon
r_int
id|ioptex
suffix:semicolon
r_if
c_cond
(paren
(paren
id|va
op_amp
op_complement
id|PAGE_MASK
)paren
op_ne
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
op_ne
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_amp
op_complement
id|PAGE_MASK
)paren
op_ne
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* page color = physical address */
id|ioptex
op_assign
id|bit_map_string_get
c_func
(paren
op_amp
id|iommu-&gt;usemap
comma
id|len
op_rshift
id|PAGE_SHIFT
comma
id|addr
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ioptex
OL
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;iommu out&quot;
)paren
suffix:semicolon
id|iopte
op_add_assign
id|ioptex
suffix:semicolon
id|first
op_assign
id|iopte
suffix:semicolon
id|end
op_assign
id|addr
op_plus
id|len
suffix:semicolon
r_while
c_loop
(paren
id|addr
OL
id|end
)paren
(brace
id|page
op_assign
id|va
suffix:semicolon
(brace
id|pgd_t
op_star
id|pgdp
suffix:semicolon
id|pmd_t
op_star
id|pmdp
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
r_if
c_cond
(paren
id|viking_mxcc_present
)paren
id|viking_mxcc_flush_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|viking_flush
)paren
id|viking_flush_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_else
id|__flush_page_to_ram
c_func
(paren
id|page
)paren
suffix:semicolon
id|pgdp
op_assign
id|pgd_offset
c_func
(paren
op_amp
id|init_mm
comma
id|addr
)paren
suffix:semicolon
id|pmdp
op_assign
id|pmd_offset
c_func
(paren
id|pgdp
comma
id|addr
)paren
suffix:semicolon
id|ptep
op_assign
id|pte_offset_map
c_func
(paren
id|pmdp
comma
id|addr
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|ptep
comma
id|mk_pte
c_func
(paren
id|virt_to_page
c_func
(paren
id|page
)paren
comma
id|dvma_prot
)paren
)paren
suffix:semicolon
)brace
id|iopte_val
c_func
(paren
op_star
id|iopte
op_increment
)paren
op_assign
id|MKIOPTE
c_func
(paren
id|page_to_pfn
c_func
(paren
id|virt_to_page
c_func
(paren
id|page
)paren
)paren
comma
id|ioperm_noc
)paren
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|va
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
multiline_comment|/* P3: why do we need this?&n;&t; *&n;&t; * DAVEM: Because there are several aspects, none of which&n;&t; *        are handled by a single interface.  Some cpus are&n;&t; *        completely not I/O DMA coherent, and some have&n;&t; *        virtually indexed caches.  The driver DMA flushing&n;&t; *        methods handle the former case, but here during&n;&t; *        IOMMU page table modifications, and usage of non-cacheable&n;&t; *        cpu mappings of pages potentially in the cpu caches, we have&n;&t; *        to handle the latter case as well.&n;&t; */
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|iommu_flush_iotlb
c_func
(paren
id|first
comma
id|len
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
id|iommu_invalidate
c_func
(paren
id|iommu-&gt;regs
)paren
suffix:semicolon
op_star
id|pba
op_assign
id|iommu-&gt;start
op_plus
(paren
id|ioptex
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|iommu_unmap_dma_area
r_static
r_void
id|iommu_unmap_dma_area
c_func
(paren
r_int
r_int
id|busa
comma
r_int
id|len
)paren
(brace
r_struct
id|iommu_struct
op_star
id|iommu
op_assign
id|sbus_root-&gt;iommu
suffix:semicolon
id|iopte_t
op_star
id|iopte
op_assign
id|iommu-&gt;page_table
suffix:semicolon
r_int
r_int
id|end
suffix:semicolon
r_int
id|ioptex
op_assign
(paren
id|busa
op_minus
id|iommu-&gt;start
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|busa
op_amp
op_complement
id|PAGE_MASK
)paren
op_ne
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_amp
op_complement
id|PAGE_MASK
)paren
op_ne
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|iopte
op_add_assign
id|ioptex
suffix:semicolon
id|end
op_assign
id|busa
op_plus
id|len
suffix:semicolon
r_while
c_loop
(paren
id|busa
OL
id|end
)paren
(brace
id|iopte_val
c_func
(paren
op_star
id|iopte
op_increment
)paren
op_assign
l_int|0
suffix:semicolon
id|busa
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
id|iommu_invalidate
c_func
(paren
id|iommu-&gt;regs
)paren
suffix:semicolon
id|bit_map_clear
c_func
(paren
op_amp
id|iommu-&gt;usemap
comma
id|ioptex
comma
id|len
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
)brace
DECL|function|iommu_translate_dvma
r_static
r_struct
id|page
op_star
id|iommu_translate_dvma
c_func
(paren
r_int
r_int
id|busa
)paren
(brace
r_struct
id|iommu_struct
op_star
id|iommu
op_assign
id|sbus_root-&gt;iommu
suffix:semicolon
id|iopte_t
op_star
id|iopte
op_assign
id|iommu-&gt;page_table
suffix:semicolon
id|iopte
op_add_assign
(paren
(paren
id|busa
op_minus
id|iommu-&gt;start
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_return
id|pfn_to_page
c_func
(paren
(paren
id|iopte_val
c_func
(paren
op_star
id|iopte
)paren
op_amp
id|IOPTE_PAGE
)paren
op_rshift
(paren
id|PAGE_SHIFT
op_minus
l_int|4
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|iommu_lockarea
r_static
r_char
op_star
id|iommu_lockarea
c_func
(paren
r_char
op_star
id|vaddr
comma
r_int
r_int
id|len
)paren
(brace
r_return
id|vaddr
suffix:semicolon
)brace
DECL|function|iommu_unlockarea
r_static
r_void
id|iommu_unlockarea
c_func
(paren
r_char
op_star
id|vaddr
comma
r_int
r_int
id|len
)paren
(brace
)brace
DECL|function|ld_mmu_iommu
r_void
id|__init
id|ld_mmu_iommu
c_func
(paren
r_void
)paren
(brace
id|viking_flush
op_assign
(paren
id|BTFIXUPVAL_CALL
c_func
(paren
id|flush_page_for_dma
)paren
op_eq
(paren
r_int
r_int
)paren
id|viking_flush_page
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_lockarea
comma
id|iommu_lockarea
comma
id|BTFIXUPCALL_RETO0
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_unlockarea
comma
id|iommu_unlockarea
comma
id|BTFIXUPCALL_NOP
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|BTFIXUPVAL_CALL
c_func
(paren
id|flush_page_for_dma
)paren
)paren
(brace
multiline_comment|/* IO coherent chip */
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_get_scsi_one
comma
id|iommu_get_scsi_one_noflush
comma
id|BTFIXUPCALL_RETO0
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_get_scsi_sgl
comma
id|iommu_get_scsi_sgl_noflush
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|flush_page_for_dma_global
)paren
(brace
multiline_comment|/* flush_page_for_dma flushes everything, no matter of what page is it */
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_get_scsi_one
comma
id|iommu_get_scsi_one_gflush
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_get_scsi_sgl
comma
id|iommu_get_scsi_sgl_gflush
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
)brace
r_else
(brace
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_get_scsi_one
comma
id|iommu_get_scsi_one_pflush
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_get_scsi_sgl
comma
id|iommu_get_scsi_sgl_pflush
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
)brace
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_release_scsi_one
comma
id|iommu_release_scsi_one
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_release_scsi_sgl
comma
id|iommu_release_scsi_sgl
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SBUS
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_map_dma_area
comma
id|iommu_map_dma_area
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_unmap_dma_area
comma
id|iommu_unmap_dma_area
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|mmu_translate_dvma
comma
id|iommu_translate_dvma
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|viking_mxcc_present
op_logical_or
id|srmmu_modtype
op_eq
id|HyperSparc
)paren
(brace
id|dvma_prot
op_assign
id|__pgprot
c_func
(paren
id|SRMMU_CACHE
op_or
id|SRMMU_ET_PTE
op_or
id|SRMMU_PRIV
)paren
suffix:semicolon
id|ioperm_noc
op_assign
id|IOPTE_CACHE
op_or
id|IOPTE_WRITE
op_or
id|IOPTE_VALID
suffix:semicolon
)brace
r_else
(brace
id|dvma_prot
op_assign
id|__pgprot
c_func
(paren
id|SRMMU_ET_PTE
op_or
id|SRMMU_PRIV
)paren
suffix:semicolon
id|ioperm_noc
op_assign
id|IOPTE_WRITE
op_or
id|IOPTE_VALID
suffix:semicolon
)brace
)brace
eof
