multiline_comment|/*&n; * Dynamic DMA mapping support for AMD Hammer.&n; * &n; * Use the integrated AGP GART in the Hammer northbridge as an IOMMU for PCI.&n; * This allows to use PCI devices that only support 32bit addresses on systems&n; * with more than 4GB. &n; *&n; * See Documentation/DMA-mapping.txt for the interface specification.&n; * &n; * Copyright 2002 Andi Kleen, SuSE Labs.&n; * $Id: pci-gart.c,v 1.20 2003/03/12 08:23:29 ak Exp $&n; */
multiline_comment|/* &n; * Notebook:&n;&n;possible future tuning: &n; fast path for sg streaming mappings - only take the locks once.&n; more intelligent flush strategy - flush only the NB of the CPU directly&n; connected to the device?&n; move boundary between IOMMU and AGP in GART dynamically&n;  &n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mtrr.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/proto.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/kdebug.h&gt;
macro_line|#include &lt;asm/proto.h&gt;
DECL|variable|iommu_bus_base
r_int
r_int
id|iommu_bus_base
suffix:semicolon
multiline_comment|/* GART remapping area (physical) */
DECL|variable|iommu_size
r_static
r_int
r_int
id|iommu_size
suffix:semicolon
multiline_comment|/* size of remapping area bytes */
DECL|variable|iommu_pages
r_static
r_int
r_int
id|iommu_pages
suffix:semicolon
multiline_comment|/* .. and in pages */
DECL|variable|iommu_gatt_base
id|u32
op_star
id|iommu_gatt_base
suffix:semicolon
multiline_comment|/* Remapping table */
DECL|variable|no_iommu
r_int
id|no_iommu
suffix:semicolon
DECL|variable|no_agp
r_static
r_int
id|no_agp
suffix:semicolon
macro_line|#ifdef CONFIG_IOMMU_DEBUG
DECL|variable|force_mmu
r_int
id|force_mmu
op_assign
l_int|1
suffix:semicolon
macro_line|#else
DECL|variable|force_mmu
r_int
id|force_mmu
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/* Allocation bitmap for the remapping area */
DECL|variable|iommu_bitmap_lock
r_static
id|spinlock_t
id|iommu_bitmap_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|iommu_gart_bitmap
r_static
r_int
r_int
op_star
id|iommu_gart_bitmap
suffix:semicolon
multiline_comment|/* guarded by iommu_bitmap_lock */
DECL|macro|GPTE_VALID
mdefine_line|#define GPTE_VALID    1
DECL|macro|GPTE_COHERENT
mdefine_line|#define GPTE_COHERENT 2
DECL|macro|GPTE_ENCODE
mdefine_line|#define GPTE_ENCODE(x) &bslash;&n;&t;(((x) &amp; 0xfffff000) | (((x) &gt;&gt; 32) &lt;&lt; 4) | GPTE_VALID | GPTE_COHERENT)
DECL|macro|GPTE_DECODE
mdefine_line|#define GPTE_DECODE(x) (((x) &amp; 0xfffff000) | (((u64)(x) &amp; 0xff0) &lt;&lt; 28))
DECL|macro|for_all_nb
mdefine_line|#define for_all_nb(dev) &bslash;&n;&t;dev=NULL; &bslash;&n;&t;while ((dev = pci_find_device(PCI_ANY_ID, PCI_ANY_ID, dev)) != NULL) &bslash;&n;&t;&t;if (dev-&gt;bus-&gt;number == 0 &amp;&amp; PCI_FUNC(dev-&gt;devfn) == 3 &amp;&amp; &bslash;&n;&t;&t;    (PCI_SLOT(dev-&gt;devfn) &gt;= 24) &amp;&amp; (PCI_SLOT(dev-&gt;devfn) &lt;= 31))
DECL|macro|EMERGENCY_PAGES
mdefine_line|#define EMERGENCY_PAGES 32 /* = 128KB */ 
macro_line|#ifdef CONFIG_AGP
r_extern
r_int
id|agp_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|AGPEXTERN
mdefine_line|#define AGPEXTERN extern
macro_line|#else
DECL|macro|AGPEXTERN
mdefine_line|#define AGPEXTERN
macro_line|#endif
multiline_comment|/* backdoor interface to AGP driver */
DECL|variable|agp_memory_reserved
id|AGPEXTERN
r_int
id|agp_memory_reserved
suffix:semicolon
DECL|variable|agp_gatt_table
id|AGPEXTERN
id|__u32
op_star
id|agp_gatt_table
suffix:semicolon
DECL|variable|next_bit
r_static
r_int
r_int
id|next_bit
suffix:semicolon
multiline_comment|/* protected by iommu_bitmap_lock */
DECL|function|alloc_iommu
r_static
r_int
r_int
id|alloc_iommu
c_func
(paren
r_int
id|size
comma
r_int
op_star
id|flush
)paren
(brace
r_int
r_int
id|offset
comma
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iommu_bitmap_lock
comma
id|flags
)paren
suffix:semicolon
id|offset
op_assign
id|find_next_zero_string
c_func
(paren
id|iommu_gart_bitmap
comma
id|next_bit
comma
id|iommu_pages
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_eq
op_minus
l_int|1
)paren
(brace
op_star
id|flush
op_assign
l_int|1
suffix:semicolon
id|offset
op_assign
id|find_next_zero_string
c_func
(paren
id|iommu_gart_bitmap
comma
l_int|0
comma
id|next_bit
comma
id|size
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|offset
op_ne
op_minus
l_int|1
)paren
(brace
id|set_bit_string
c_func
(paren
id|iommu_gart_bitmap
comma
id|offset
comma
id|size
)paren
suffix:semicolon
id|next_bit
op_assign
id|offset
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|next_bit
op_ge
id|iommu_pages
)paren
(brace
id|next_bit
op_assign
l_int|0
suffix:semicolon
op_star
id|flush
op_assign
l_int|1
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iommu_bitmap_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|offset
suffix:semicolon
)brace
DECL|function|free_iommu
r_static
r_void
id|free_iommu
c_func
(paren
r_int
r_int
id|offset
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iommu_bitmap_lock
comma
id|flags
)paren
suffix:semicolon
id|clear_bit_string
c_func
(paren
id|iommu_gart_bitmap
comma
id|offset
comma
id|size
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iommu_bitmap_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|flush_gart
r_static
r_inline
r_void
id|flush_gart
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|nb
suffix:semicolon
id|for_all_nb
c_func
(paren
id|nb
)paren
(brace
id|u32
id|flag
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|nb
comma
l_int|0x9c
comma
op_amp
id|flag
)paren
suffix:semicolon
multiline_comment|/* could cache this */
multiline_comment|/* could complain for PTE walk errors here (bit 1 of flag) */
id|flag
op_or_assign
l_int|1
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|nb
comma
l_int|0x9c
comma
id|flag
)paren
suffix:semicolon
)brace
)brace
DECL|function|pci_alloc_consistent
r_void
op_star
id|pci_alloc_consistent
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_handle
)paren
(brace
r_void
op_star
id|memory
suffix:semicolon
r_int
id|gfp
op_assign
id|GFP_ATOMIC
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|flush
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|iommu_page
suffix:semicolon
r_int
r_int
id|dma_mask
suffix:semicolon
r_if
c_cond
(paren
id|hwdev
op_eq
l_int|NULL
)paren
(brace
id|gfp
op_or_assign
id|GFP_DMA
suffix:semicolon
id|dma_mask
op_assign
l_int|0xffffffff
suffix:semicolon
)brace
r_else
(brace
id|dma_mask
op_assign
id|hwdev-&gt;consistent_dma_mask
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dma_mask
op_eq
l_int|0
)paren
id|dma_mask
op_assign
l_int|0xffffffff
suffix:semicolon
r_if
c_cond
(paren
id|dma_mask
OL
l_int|0xffffffff
op_logical_or
id|no_iommu
)paren
id|gfp
op_or_assign
id|GFP_DMA
suffix:semicolon
multiline_comment|/* &n;&t; * First try to allocate continuous and use directly if already &n;&t; * in lowmem. &n;&t; */
id|size
op_assign
id|round_up
c_func
(paren
id|size
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|memory
op_assign
(paren
r_void
op_star
)paren
id|__get_free_pages
c_func
(paren
id|gfp
comma
id|get_order
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memory
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
r_int
id|high
op_assign
l_int|0
comma
id|mmu
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|virt_to_bus
c_func
(paren
id|memory
)paren
op_plus
id|size
)paren
OG
id|dma_mask
)paren
id|high
op_assign
l_int|1
suffix:semicolon
id|mmu
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|force_mmu
op_logical_and
op_logical_neg
(paren
id|gfp
op_amp
id|GFP_DMA
)paren
)paren
id|mmu
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|no_iommu
)paren
(brace
r_if
c_cond
(paren
id|high
)paren
r_goto
id|error
suffix:semicolon
id|mmu
op_assign
l_int|0
suffix:semicolon
)brace
id|memset
c_func
(paren
id|memory
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mmu
)paren
(brace
op_star
id|dma_handle
op_assign
id|virt_to_bus
c_func
(paren
id|memory
)paren
suffix:semicolon
r_return
id|memory
suffix:semicolon
)brace
)brace
id|size
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|iommu_page
op_assign
id|alloc_iommu
c_func
(paren
id|size
comma
op_amp
id|flush
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iommu_page
op_eq
op_minus
l_int|1
)paren
r_goto
id|error
suffix:semicolon
multiline_comment|/* Fill in the GATT */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|phys_mem
suffix:semicolon
r_void
op_star
id|mem
op_assign
id|memory
op_plus
id|i
op_star
id|PAGE_SIZE
suffix:semicolon
id|phys_mem
op_assign
id|virt_to_phys
c_func
(paren
id|mem
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|phys_mem
op_amp
op_complement
id|PHYSICAL_PAGE_MASK
)paren
suffix:semicolon
id|iommu_gatt_base
(braket
id|iommu_page
op_plus
id|i
)braket
op_assign
id|GPTE_ENCODE
c_func
(paren
id|phys_mem
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flush
)paren
id|flush_gart
c_func
(paren
)paren
suffix:semicolon
op_star
id|dma_handle
op_assign
id|iommu_bus_base
op_plus
(paren
id|iommu_page
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_return
id|memory
suffix:semicolon
id|error
suffix:colon
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|memory
comma
id|get_order
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* &n; * Unmap consistent memory.&n; * The caller must ensure that the device has finished accessing the mapping.&n; */
DECL|function|pci_free_consistent
r_void
id|pci_free_consistent
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_int
id|size
comma
r_void
op_star
id|vaddr
comma
id|dma_addr_t
id|bus
)paren
(brace
r_int
r_int
id|iommu_page
suffix:semicolon
id|size
op_assign
id|round_up
c_func
(paren
id|size
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bus
op_ge
id|iommu_bus_base
op_logical_and
id|bus
op_le
id|iommu_bus_base
op_plus
id|iommu_size
)paren
(brace
r_int
id|pages
op_assign
id|size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_int
id|i
suffix:semicolon
id|iommu_page
op_assign
(paren
id|bus
op_minus
id|iommu_bus_base
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|vaddr
op_assign
id|__va
c_func
(paren
id|GPTE_DECODE
c_func
(paren
id|iommu_gatt_base
(braket
id|iommu_page
)braket
)paren
)paren
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
id|pages
suffix:semicolon
id|i
op_increment
)paren
(brace
id|u64
id|pte
op_assign
id|iommu_gatt_base
(braket
id|iommu_page
op_plus
id|i
)braket
suffix:semicolon
id|BUG_ON
c_func
(paren
(paren
id|pte
op_amp
id|GPTE_VALID
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|iommu_gatt_base
(braket
id|iommu_page
op_plus
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|free_iommu
c_func
(paren
id|iommu_page
comma
id|pages
)paren
suffix:semicolon
)brace
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|vaddr
comma
id|get_order
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_IOMMU_LEAK
multiline_comment|/* Debugging aid for drivers that don&squot;t free their IOMMU tables */
DECL|variable|iommu_leak_tab
r_static
r_void
op_star
op_star
id|iommu_leak_tab
suffix:semicolon
DECL|variable|leak_trace
r_static
r_int
id|leak_trace
suffix:semicolon
DECL|variable|iommu_leak_pages
r_int
id|iommu_leak_pages
op_assign
l_int|20
suffix:semicolon
DECL|function|dump_leak
r_void
id|dump_leak
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_static
r_int
id|dump
suffix:semicolon
r_if
c_cond
(paren
id|dump
op_logical_or
op_logical_neg
id|iommu_leak_tab
)paren
r_return
suffix:semicolon
id|dump
op_assign
l_int|1
suffix:semicolon
id|show_stack
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Very crude. dump some from the end of the table too */
id|printk
c_func
(paren
l_string|&quot;Dumping %d pages from end of IOMMU:&bslash;n&quot;
comma
id|iommu_leak_pages
)paren
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
id|iommu_leak_pages
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%lu: &quot;
comma
id|iommu_pages
op_minus
id|i
)paren
suffix:semicolon
id|printk_address
c_func
(paren
(paren
r_int
r_int
)paren
id|iommu_leak_tab
(braket
id|iommu_pages
op_minus
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%c&quot;
comma
(paren
id|i
op_plus
l_int|1
)paren
op_mod
l_int|2
op_eq
l_int|0
ques
c_cond
l_char|&squot;&bslash;n&squot;
suffix:colon
l_char|&squot; &squot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|iommu_full
r_static
r_void
id|iommu_full
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_void
op_star
id|addr
comma
r_int
id|size
comma
r_int
id|dir
)paren
(brace
multiline_comment|/* &n;&t; * Ran out of IOMMU space for this operation. This is very bad.&n;&t; * Unfortunately the drivers cannot handle this operation properly.&n;&t; * Return some non mapped prereserved space in the aperture and &n;&t; * let the Northbridge deal with it. This will result in garbage&n;&t; * in the IO operation. When the size exceeds the prereserved space&n;&t; * memory corruption will occur or random memory will be DMAed &n;&t; * out. Hopefully no network devices use single mappings that big.&n;&t; */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI-DMA: Out of IOMMU space for %p size %lu at device %s[%s]&bslash;n&quot;
comma
id|addr
comma
id|size
comma
id|dev
ques
c_cond
id|dev-&gt;dev.name
suffix:colon
l_string|&quot;?&quot;
comma
id|dev
ques
c_cond
id|dev-&gt;slot_name
suffix:colon
l_string|&quot;?&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|PAGE_SIZE
op_star
id|EMERGENCY_PAGES
)paren
(brace
r_if
c_cond
(paren
id|dir
op_eq
id|PCI_DMA_FROMDEVICE
op_logical_or
id|dir
op_eq
id|PCI_DMA_BIDIRECTIONAL
)paren
id|panic
c_func
(paren
l_string|&quot;PCI-DMA: Memory will be corrupted&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir
op_eq
id|PCI_DMA_TODEVICE
op_logical_or
id|dir
op_eq
id|PCI_DMA_BIDIRECTIONAL
)paren
id|panic
c_func
(paren
l_string|&quot;PCI-DMA: Random memory will be DMAed&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_IOMMU_LEAK
id|dump_leak
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|need_iommu
r_static
r_inline
r_int
id|need_iommu
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
r_int
id|addr
comma
r_int
id|size
)paren
(brace
id|u64
id|mask
op_assign
id|dev
ques
c_cond
id|dev-&gt;dma_mask
suffix:colon
l_int|0xffffffff
suffix:semicolon
r_int
id|high
op_assign
(paren
op_complement
id|mask
op_amp
(paren
r_int
r_int
)paren
(paren
id|addr
op_plus
id|size
)paren
)paren
op_ne
l_int|0
suffix:semicolon
r_int
id|mmu
op_assign
id|high
suffix:semicolon
r_if
c_cond
(paren
id|force_mmu
)paren
id|mmu
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|no_iommu
)paren
(brace
r_if
c_cond
(paren
id|high
)paren
id|panic
c_func
(paren
l_string|&quot;pci_map_single: high address but no IOMMU.&bslash;n&quot;
)paren
suffix:semicolon
id|mmu
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|mmu
suffix:semicolon
)brace
DECL|function|pci_map_single
id|dma_addr_t
id|pci_map_single
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_void
op_star
id|addr
comma
r_int
id|size
comma
r_int
id|dir
)paren
(brace
r_int
r_int
id|iommu_page
suffix:semicolon
r_int
r_int
id|phys_mem
comma
id|bus
suffix:semicolon
r_int
id|i
comma
id|npages
suffix:semicolon
r_int
id|flush
op_assign
l_int|0
suffix:semicolon
id|BUG_ON
c_func
(paren
id|dir
op_eq
id|PCI_DMA_NONE
)paren
suffix:semicolon
id|phys_mem
op_assign
id|virt_to_phys
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|need_iommu
c_func
(paren
id|dev
comma
id|phys_mem
comma
id|size
)paren
)paren
r_return
id|phys_mem
suffix:semicolon
id|npages
op_assign
id|round_up
c_func
(paren
id|size
op_plus
(paren
(paren
id|u64
)paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
comma
id|PAGE_SIZE
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|iommu_page
op_assign
id|alloc_iommu
c_func
(paren
id|npages
comma
op_amp
id|flush
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iommu_page
op_eq
op_minus
l_int|1
)paren
(brace
id|iommu_full
c_func
(paren
id|dev
comma
id|addr
comma
id|size
comma
id|dir
)paren
suffix:semicolon
r_return
id|iommu_bus_base
suffix:semicolon
)brace
id|phys_mem
op_and_assign
id|PAGE_MASK
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
comma
id|phys_mem
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|BUG_ON
c_func
(paren
id|phys_mem
op_amp
op_complement
id|PHYSICAL_PAGE_MASK
)paren
suffix:semicolon
multiline_comment|/* &n;&t;&t; * Set coherent mapping here to avoid needing to flush&n;&t;&t; * the caches on mapping.&n;&t;&t; */
id|iommu_gatt_base
(braket
id|iommu_page
op_plus
id|i
)braket
op_assign
id|GPTE_ENCODE
c_func
(paren
id|phys_mem
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IOMMU_LEAK
multiline_comment|/* XXX need eventually caller of pci_map_sg */
r_if
c_cond
(paren
id|iommu_leak_tab
)paren
id|iommu_leak_tab
(braket
id|iommu_page
op_plus
id|i
)braket
op_assign
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
id|flush
)paren
id|flush_gart
c_func
(paren
)paren
suffix:semicolon
id|bus
op_assign
id|iommu_bus_base
op_plus
id|iommu_page
op_star
id|PAGE_SIZE
suffix:semicolon
r_return
id|bus
op_plus
(paren
(paren
r_int
r_int
)paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Free a temporary PCI mapping.&n; */
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
id|dma_addr
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
r_int
r_int
id|iommu_page
suffix:semicolon
r_int
id|npages
suffix:semicolon
r_if
c_cond
(paren
id|dma_addr
template_param
id|iommu_bus_base
op_plus
id|iommu_size
)paren
r_return
suffix:semicolon
id|iommu_page
op_assign
(paren
id|dma_addr
op_minus
id|iommu_bus_base
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|npages
op_assign
id|round_up
c_func
(paren
id|size
op_plus
(paren
id|dma_addr
op_amp
op_complement
id|PAGE_MASK
)paren
comma
id|PAGE_SIZE
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_int
id|i
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
id|iommu_gatt_base
(braket
id|iommu_page
op_plus
id|i
)braket
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_IOMMU_LEAK
r_if
c_cond
(paren
id|iommu_leak_tab
)paren
id|iommu_leak_tab
(braket
id|iommu_page
op_plus
id|i
)braket
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
)brace
id|free_iommu
c_func
(paren
id|iommu_page
comma
id|npages
)paren
suffix:semicolon
)brace
DECL|variable|pci_map_single
id|EXPORT_SYMBOL
c_func
(paren
id|pci_map_single
)paren
suffix:semicolon
DECL|variable|pci_unmap_single
id|EXPORT_SYMBOL
c_func
(paren
id|pci_unmap_single
)paren
suffix:semicolon
DECL|function|check_iommu_size
r_static
id|__init
r_int
r_int
id|check_iommu_size
c_func
(paren
r_int
r_int
id|aper
comma
id|u64
id|aper_size
)paren
(brace
r_int
r_int
id|a
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iommu_size
)paren
(brace
id|iommu_size
op_assign
id|aper_size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|no_agp
)paren
id|iommu_size
op_div_assign
l_int|2
suffix:semicolon
)brace
id|a
op_assign
id|aper
op_plus
id|iommu_size
suffix:semicolon
id|iommu_size
op_sub_assign
id|round_up
c_func
(paren
id|a
comma
id|LARGE_PAGE_SIZE
)paren
op_minus
id|a
suffix:semicolon
r_if
c_cond
(paren
id|iommu_size
OL
l_int|64
op_star
l_int|1024
op_star
l_int|1024
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI-DMA: Warning: Small IOMMU %luMB. Consider increasing the AGP aperture in BIOS&bslash;n&quot;
comma
id|iommu_size
op_rshift
l_int|20
)paren
suffix:semicolon
r_return
id|iommu_size
suffix:semicolon
)brace
DECL|function|read_aperture
r_static
id|__init
r_int
id|read_aperture
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u32
op_star
id|size
)paren
(brace
r_int
id|aper_size
op_assign
l_int|0
comma
id|aper_base_32
suffix:semicolon
id|u64
id|aper_base
suffix:semicolon
r_int
id|aper_order
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x94
comma
op_amp
id|aper_base_32
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x90
comma
op_amp
id|aper_order
)paren
suffix:semicolon
id|aper_order
op_assign
(paren
id|aper_order
op_rshift
l_int|1
)paren
op_amp
l_int|7
suffix:semicolon
id|aper_base
op_assign
id|aper_base_32
op_amp
l_int|0x7fff
suffix:semicolon
id|aper_base
op_lshift_assign
l_int|25
suffix:semicolon
id|aper_size
op_assign
(paren
l_int|32
op_star
l_int|1024
op_star
l_int|1024
)paren
op_lshift
id|aper_order
suffix:semicolon
r_if
c_cond
(paren
id|aper_base
op_plus
id|aper_size
op_ge
l_int|0xffffffff
op_logical_or
op_logical_neg
id|aper_size
)paren
id|aper_base
op_assign
l_int|0
suffix:semicolon
op_star
id|size
op_assign
id|aper_size
suffix:semicolon
r_return
id|aper_base
suffix:semicolon
)brace
multiline_comment|/* &n; * Private Northbridge GATT initialization in case we cannot use the&n; * AGP driver for some reason.  &n; */
DECL|function|init_k8_gatt
r_static
id|__init
r_int
id|init_k8_gatt
c_func
(paren
r_struct
id|agp_kern_info
op_star
id|info
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_void
op_star
id|gatt
suffix:semicolon
r_int
id|aper_base
comma
id|new_aper_base
suffix:semicolon
r_int
id|aper_size
comma
id|gatt_size
comma
id|new_aper_size
suffix:semicolon
id|aper_size
op_assign
id|aper_base
op_assign
id|info-&gt;aper_size
op_assign
l_int|0
suffix:semicolon
id|for_all_nb
c_func
(paren
id|dev
)paren
(brace
id|new_aper_base
op_assign
id|read_aperture
c_func
(paren
id|dev
comma
op_amp
id|new_aper_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_aper_base
)paren
r_goto
id|nommu
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|aper_base
)paren
(brace
id|aper_size
op_assign
id|new_aper_size
suffix:semicolon
id|aper_base
op_assign
id|new_aper_base
suffix:semicolon
)brace
r_if
c_cond
(paren
id|aper_size
op_ne
id|new_aper_size
op_logical_or
id|aper_base
op_ne
id|new_aper_base
)paren
r_goto
id|nommu
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|aper_base
)paren
r_goto
id|nommu
suffix:semicolon
id|info-&gt;aper_base
op_assign
id|aper_base
suffix:semicolon
id|info-&gt;aper_size
op_assign
id|aper_size
op_rshift
l_int|20
suffix:semicolon
id|gatt_size
op_assign
(paren
id|aper_size
op_rshift
id|PAGE_SHIFT
)paren
op_star
r_sizeof
(paren
id|u32
)paren
suffix:semicolon
id|gatt
op_assign
(paren
r_void
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
id|get_order
c_func
(paren
id|gatt_size
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gatt
)paren
id|panic
c_func
(paren
l_string|&quot;Cannot allocate GATT table&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
id|gatt
comma
l_int|0
comma
id|gatt_size
)paren
suffix:semicolon
id|agp_gatt_table
op_assign
id|gatt
suffix:semicolon
id|for_all_nb
c_func
(paren
id|dev
)paren
(brace
id|u32
id|ctl
suffix:semicolon
id|u32
id|gatt_reg
suffix:semicolon
id|gatt_reg
op_assign
id|__pa
c_func
(paren
id|gatt
)paren
op_rshift
l_int|12
suffix:semicolon
id|gatt_reg
op_lshift_assign
l_int|4
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x98
comma
id|gatt_reg
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x90
comma
op_amp
id|ctl
)paren
suffix:semicolon
id|ctl
op_or_assign
l_int|1
suffix:semicolon
id|ctl
op_and_assign
op_complement
(paren
(paren
l_int|1
op_lshift
l_int|4
)paren
op_or
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x90
comma
id|ctl
)paren
suffix:semicolon
)brace
id|flush_gart
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI-DMA: aperture base @ %x size %u KB&bslash;n&quot;
comma
id|aper_base
comma
id|aper_size
op_rshift
l_int|10
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|nommu
suffix:colon
multiline_comment|/* XXX: reject 0xffffffff mask now in pci mapping functions */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI-DMA: More than 4GB of RAM and no IOMMU&bslash;n&quot;
id|KERN_ERR
l_string|&quot;PCI-DMA: 32bit PCI IO may malfunction.&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_extern
r_int
id|agp_amdk8_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|pci_iommu_init
r_int
id|__init
id|pci_iommu_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|agp_kern_info
id|info
suffix:semicolon
r_int
r_int
id|aper_size
suffix:semicolon
r_int
r_int
id|iommu_start
suffix:semicolon
macro_line|#ifndef CONFIG_AGP_AMD_8151
id|no_agp
op_assign
l_int|1
suffix:semicolon
macro_line|#else
multiline_comment|/* Makefile puts PCI initialization via subsys_initcall first. */
multiline_comment|/* Add other K8 AGP bridge drivers here */
id|no_agp
op_assign
id|no_agp
op_logical_or
(paren
id|agp_amdk8_init
c_func
(paren
)paren
OL
l_int|0
)paren
op_logical_or
(paren
id|agp_copy_info
c_func
(paren
op_amp
id|info
)paren
OL
l_int|0
)paren
suffix:semicolon
macro_line|#endif&t;
r_if
c_cond
(paren
id|no_iommu
op_logical_or
(paren
op_logical_neg
id|force_mmu
op_logical_and
id|end_pfn
OL
l_int|0xffffffff
op_rshift
id|PAGE_SHIFT
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI-DMA: Disabling IOMMU.&bslash;n&quot;
)paren
suffix:semicolon
id|no_iommu
op_assign
l_int|1
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|no_agp
)paren
(brace
r_int
id|err
op_assign
op_minus
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI-DMA: Disabling AGP.&bslash;n&quot;
)paren
suffix:semicolon
id|no_agp
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|force_mmu
op_logical_or
id|end_pfn
op_ge
l_int|0xffffffff
op_rshift
id|PAGE_SHIFT
)paren
id|err
op_assign
id|init_k8_gatt
c_func
(paren
op_amp
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI-DMA: Disabling IOMMU.&bslash;n&quot;
)paren
suffix:semicolon
id|no_iommu
op_assign
l_int|1
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|aper_size
op_assign
id|info.aper_size
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
id|iommu_size
op_assign
id|check_iommu_size
c_func
(paren
id|info.aper_base
comma
id|aper_size
)paren
suffix:semicolon
id|iommu_pages
op_assign
id|iommu_size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|iommu_gart_bitmap
op_assign
(paren
r_void
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
id|get_order
c_func
(paren
id|iommu_pages
op_div
l_int|8
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iommu_gart_bitmap
)paren
id|panic
c_func
(paren
l_string|&quot;Cannot allocate iommu bitmap&bslash;n&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
id|iommu_gart_bitmap
comma
l_int|0
comma
id|iommu_pages
op_div
l_int|8
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IOMMU_LEAK
r_if
c_cond
(paren
id|leak_trace
)paren
(brace
id|iommu_leak_tab
op_assign
(paren
r_void
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
id|get_order
c_func
(paren
id|iommu_pages
op_star
r_sizeof
(paren
r_void
op_star
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iommu_leak_tab
)paren
id|memset
c_func
(paren
id|iommu_leak_tab
comma
l_int|0
comma
id|iommu_pages
op_star
l_int|8
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;PCI-DMA: Cannot allocate leak trace area&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* &n;&t; * Out of IOMMU space handling.&n;&t; * Reserve some invalid pages at the beginning of the GART. &n;&t; */
id|set_bit_string
c_func
(paren
id|iommu_gart_bitmap
comma
l_int|0
comma
id|EMERGENCY_PAGES
)paren
suffix:semicolon
id|agp_memory_reserved
op_assign
id|iommu_size
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI-DMA: Reserving %luMB of IOMMU area in the AGP aperture&bslash;n&quot;
comma
id|iommu_size
op_rshift
l_int|20
)paren
suffix:semicolon
id|iommu_start
op_assign
id|aper_size
op_minus
id|iommu_size
suffix:semicolon
id|iommu_bus_base
op_assign
id|info.aper_base
op_plus
id|iommu_start
suffix:semicolon
id|iommu_gatt_base
op_assign
id|agp_gatt_table
op_plus
(paren
id|iommu_start
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|bad_dma_address
op_assign
id|iommu_bus_base
suffix:semicolon
multiline_comment|/* &n;         * Unmap the IOMMU part of the GART. The alias of the page is always mapped&n;&t; * with cache enabled and there is no full cache coherency across the GART&n;&t; * remapping. The unmapping avoids automatic prefetches from the CPU &n;&t; * allocating cache lines in there. All CPU accesses are done via the &n;&t; * direct mapping to the backing memory. The GART address is only used by PCI &n;&t; * devices. &n;&t; */
id|clear_kernel_mapping
c_func
(paren
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|iommu_bus_base
)paren
comma
id|iommu_size
)paren
suffix:semicolon
id|flush_gart
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Must execute after PCI subsystem */
DECL|variable|pci_iommu_init
id|fs_initcall
c_func
(paren
id|pci_iommu_init
)paren
suffix:semicolon
multiline_comment|/* iommu=[size][,noagp][,off][,force][,noforce][,leak][,memaper[=order]]&n;   size  set size of iommu (in bytes) &n;   noagp don&squot;t initialize the AGP driver and use full aperture.&n;   off   don&squot;t use the IOMMU&n;   leak  turn on simple iommu leak tracing (only when CONFIG_IOMMU_LEAK is on)&n;   memaper[=order] allocate an own aperture over RAM with size 32MB^order.  &n;   noforce don&squot;t force IOMMU usage. Should be fastest.&n;   force  Force IOMMU and turn on unmap debugging.&n;*/
DECL|function|iommu_setup
id|__init
r_int
id|iommu_setup
c_func
(paren
r_char
op_star
id|opt
)paren
(brace
r_int
id|arg
suffix:semicolon
r_char
op_star
id|p
op_assign
id|opt
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|p
comma
l_string|&quot;noagp&quot;
comma
l_int|5
)paren
)paren
id|no_agp
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|p
comma
l_string|&quot;off&quot;
comma
l_int|3
)paren
)paren
id|no_iommu
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|p
comma
l_string|&quot;force&quot;
comma
l_int|5
)paren
)paren
id|force_mmu
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|p
comma
l_string|&quot;noforce&quot;
comma
l_int|7
)paren
)paren
id|force_mmu
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|p
comma
l_string|&quot;memaper&quot;
comma
l_int|7
)paren
)paren
(brace
id|fallback_aper_force
op_assign
l_int|1
suffix:semicolon
id|p
op_add_assign
l_int|7
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_eq
l_char|&squot;=&squot;
op_logical_and
id|get_option
c_func
(paren
op_amp
id|p
comma
op_amp
id|arg
)paren
)paren
id|fallback_aper_order
op_assign
id|arg
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_IOMMU_LEAK
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|p
comma
l_string|&quot;leak&quot;
comma
l_int|4
)paren
)paren
(brace
id|leak_trace
op_assign
l_int|1
suffix:semicolon
id|p
op_add_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_eq
l_char|&squot;=&squot;
)paren
op_increment
id|p
suffix:semicolon
r_if
c_cond
(paren
id|isdigit
c_func
(paren
op_star
id|p
)paren
op_logical_and
id|get_option
c_func
(paren
op_amp
id|p
comma
op_amp
id|arg
)paren
)paren
id|iommu_leak_pages
op_assign
id|arg
suffix:semicolon
)brace
r_else
macro_line|#endif
r_if
c_cond
(paren
id|isdigit
c_func
(paren
op_star
id|p
)paren
op_logical_and
id|get_option
c_func
(paren
op_amp
id|p
comma
op_amp
id|arg
)paren
)paren
id|iommu_size
op_assign
id|arg
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_star
id|p
op_eq
l_char|&squot; &squot;
op_logical_or
op_star
id|p
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
op_star
id|p
op_increment
op_ne
l_char|&squot;,&squot;
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
eof
