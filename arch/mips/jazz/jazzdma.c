multiline_comment|/*&n; * Mips Jazz DMA controller support&n; * Copyright (C) 1995, 1996 by Andreas Busse&n; *&n; * NOTE: Some of the argument checking could be removed when&n; * things have settled down. Also, instead of returning 0xffffffff&n; * on failure of vdma_alloc() one could leave page #0 unused&n; * and return the more usual NULL pointer as logical address.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/jazz.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/jazzdma.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/*&n; * Set this to one to enable additional vdma debug code.&n; */
DECL|macro|CONF_DEBUG_VDMA
mdefine_line|#define CONF_DEBUG_VDMA 0
DECL|variable|vdma_pagetable_start
r_static
r_int
r_int
id|vdma_pagetable_start
suffix:semicolon
DECL|variable|vdma_lock
r_static
id|spinlock_t
id|vdma_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * Debug stuff&n; */
DECL|macro|vdma_debug
mdefine_line|#define vdma_debug     ((CONF_DEBUG_VDMA) ? debuglvl : 0)
DECL|variable|debuglvl
r_static
r_int
id|debuglvl
op_assign
l_int|3
suffix:semicolon
multiline_comment|/*&n; * Initialize the pagetable with a one-to-one mapping of&n; * the first 16 Mbytes of main memory and declare all&n; * entries to be unused. Using this method will at least&n; * allow some early device driver operations to work.&n; */
DECL|function|vdma_pgtbl_init
r_static
r_inline
r_void
id|vdma_pgtbl_init
c_func
(paren
r_void
)paren
(brace
id|VDMA_PGTBL_ENTRY
op_star
id|pgtbl
op_assign
(paren
id|VDMA_PGTBL_ENTRY
op_star
)paren
id|vdma_pagetable_start
suffix:semicolon
r_int
r_int
id|paddr
op_assign
l_int|0
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
id|VDMA_PGTBL_ENTRIES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pgtbl
(braket
id|i
)braket
dot
id|frame
op_assign
id|paddr
suffix:semicolon
id|pgtbl
(braket
id|i
)braket
dot
id|owner
op_assign
id|VDMA_PAGE_EMPTY
suffix:semicolon
id|paddr
op_add_assign
id|VDMA_PAGESIZE
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Initialize the Jazz R4030 dma controller&n; */
DECL|function|vdma_init
r_void
id|__init
id|vdma_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Allocate 32k of memory for DMA page tables.  This needs to be page&n;&t; * aligned and should be uncached to avoid cache flushing after every&n;&t; * update.&n;&t; */
id|vdma_pagetable_start
op_assign
id|alloc_bootmem_low_pages
c_func
(paren
id|VDMA_PGTBL_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vdma_pagetable_start
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|dma_cache_wback_inv
c_func
(paren
id|vdma_pagetable_start
comma
id|VDMA_PGTBL_SIZE
)paren
suffix:semicolon
id|vdma_pagetable_start
op_assign
id|KSEG1ADDR
c_func
(paren
id|vdma_pagetable_start
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Clear the R4030 translation table&n;&t; */
id|vdma_pgtbl_init
c_func
(paren
)paren
suffix:semicolon
id|r4030_write_reg32
c_func
(paren
id|JAZZ_R4030_TRSTBL_BASE
comma
id|CPHYSADDR
c_func
(paren
id|vdma_pagetable_start
)paren
)paren
suffix:semicolon
id|r4030_write_reg32
c_func
(paren
id|JAZZ_R4030_TRSTBL_LIM
comma
id|VDMA_PGTBL_SIZE
)paren
suffix:semicolon
id|r4030_write_reg32
c_func
(paren
id|JAZZ_R4030_TRSTBL_INV
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;VDMA: R4030 DMA pagetables initialized.&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Allocate DMA pagetables using a simple first-fit algorithm&n; */
DECL|function|vdma_alloc
r_int
r_int
id|vdma_alloc
c_func
(paren
r_int
r_int
id|paddr
comma
r_int
r_int
id|size
)paren
(brace
id|VDMA_PGTBL_ENTRY
op_star
id|entry
op_assign
(paren
id|VDMA_PGTBL_ENTRY
op_star
)paren
id|vdma_pagetable_start
suffix:semicolon
r_int
id|first
comma
id|last
comma
id|pages
comma
id|frame
comma
id|i
suffix:semicolon
r_int
r_int
id|laddr
comma
id|flags
suffix:semicolon
multiline_comment|/* check arguments */
r_if
c_cond
(paren
id|paddr
OG
l_int|0x1fffffff
)paren
(brace
r_if
c_cond
(paren
id|vdma_debug
)paren
id|printk
c_func
(paren
l_string|&quot;vdma_alloc: Invalid physical address: %08lx&bslash;n&quot;
comma
id|paddr
)paren
suffix:semicolon
r_return
id|VDMA_ERROR
suffix:semicolon
multiline_comment|/* invalid physical address */
)brace
r_if
c_cond
(paren
id|size
OG
l_int|0x400000
op_logical_or
id|size
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|vdma_debug
)paren
id|printk
c_func
(paren
l_string|&quot;vdma_alloc: Invalid size: %08lx&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
r_return
id|VDMA_ERROR
suffix:semicolon
multiline_comment|/* invalid physical address */
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|vdma_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Find free chunk&n;&t; */
id|pages
op_assign
(paren
id|size
op_plus
l_int|4095
)paren
op_rshift
l_int|12
suffix:semicolon
multiline_comment|/* no. of pages to allocate */
id|first
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_while
c_loop
(paren
id|entry
(braket
id|first
)braket
dot
id|owner
op_ne
id|VDMA_PAGE_EMPTY
op_logical_and
id|first
OL
id|VDMA_PGTBL_ENTRIES
)paren
id|first
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|first
op_plus
id|pages
OG
id|VDMA_PGTBL_ENTRIES
)paren
(brace
multiline_comment|/* nothing free */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|vdma_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|VDMA_ERROR
suffix:semicolon
)brace
id|last
op_assign
id|first
op_plus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|entry
(braket
id|last
)braket
dot
id|owner
op_eq
id|VDMA_PAGE_EMPTY
op_logical_and
id|last
op_minus
id|first
OL
id|pages
)paren
id|last
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|last
op_minus
id|first
op_eq
id|pages
)paren
r_break
suffix:semicolon
multiline_comment|/* found */
)brace
multiline_comment|/*&n;&t; * Mark pages as allocated&n;&t; */
id|laddr
op_assign
(paren
id|first
op_lshift
l_int|12
)paren
op_plus
(paren
id|paddr
op_amp
(paren
id|VDMA_PAGESIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|frame
op_assign
id|paddr
op_amp
op_complement
(paren
id|VDMA_PAGESIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|first
suffix:semicolon
id|i
OL
id|last
suffix:semicolon
id|i
op_increment
)paren
(brace
id|entry
(braket
id|i
)braket
dot
id|frame
op_assign
id|frame
suffix:semicolon
id|entry
(braket
id|i
)braket
dot
id|owner
op_assign
id|laddr
suffix:semicolon
id|frame
op_add_assign
id|VDMA_PAGESIZE
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Update translation table and return logical start address&n;&t; */
id|r4030_write_reg32
c_func
(paren
id|JAZZ_R4030_TRSTBL_INV
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vdma_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;vdma_alloc: Allocated %d pages starting from %08lx&bslash;n&quot;
comma
id|pages
comma
id|laddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vdma_debug
OG
l_int|2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;LADDR: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|first
suffix:semicolon
id|i
OL
id|last
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%08x &quot;
comma
id|i
op_lshift
l_int|12
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nPADDR: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|first
suffix:semicolon
id|i
OL
id|last
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%08x &quot;
comma
id|entry
(braket
id|i
)braket
dot
id|frame
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nOWNER: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|first
suffix:semicolon
id|i
OL
id|last
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%08x &quot;
comma
id|entry
(braket
id|i
)braket
dot
id|owner
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|vdma_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|laddr
suffix:semicolon
)brace
DECL|variable|vdma_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|vdma_alloc
)paren
suffix:semicolon
multiline_comment|/*&n; * Free previously allocated dma translation pages&n; * Note that this does NOT change the translation table,&n; * it just marks the free&squot;d pages as unused!&n; */
DECL|function|vdma_free
r_int
id|vdma_free
c_func
(paren
r_int
r_int
id|laddr
)paren
(brace
id|VDMA_PGTBL_ENTRY
op_star
id|pgtbl
op_assign
(paren
id|VDMA_PGTBL_ENTRY
op_star
)paren
id|vdma_pagetable_start
suffix:semicolon
r_int
id|i
suffix:semicolon
id|i
op_assign
id|laddr
op_rshift
l_int|12
suffix:semicolon
r_if
c_cond
(paren
id|pgtbl
(braket
id|i
)braket
dot
id|owner
op_ne
id|laddr
)paren
(brace
id|printk
(paren
l_string|&quot;vdma_free: trying to free other&squot;s dma pages, laddr=%8lx&bslash;n&quot;
comma
id|laddr
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pgtbl
(braket
id|i
)braket
dot
id|owner
op_eq
id|laddr
op_logical_and
id|i
OL
id|VDMA_PGTBL_ENTRIES
)paren
(brace
id|pgtbl
(braket
id|i
)braket
dot
id|owner
op_assign
id|VDMA_PAGE_EMPTY
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vdma_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;vdma_free: freed %ld pages starting from %08lx&bslash;n&quot;
comma
id|i
op_minus
(paren
id|laddr
op_rshift
l_int|12
)paren
comma
id|laddr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|vdma_free
id|EXPORT_SYMBOL
c_func
(paren
id|vdma_free
)paren
suffix:semicolon
multiline_comment|/*&n; * Map certain page(s) to another physical address.&n; * Caller must have allocated the page(s) before.&n; */
DECL|function|vdma_remap
r_int
id|vdma_remap
c_func
(paren
r_int
r_int
id|laddr
comma
r_int
r_int
id|paddr
comma
r_int
r_int
id|size
)paren
(brace
id|VDMA_PGTBL_ENTRY
op_star
id|pgtbl
op_assign
(paren
id|VDMA_PGTBL_ENTRY
op_star
)paren
id|vdma_pagetable_start
suffix:semicolon
r_int
id|first
comma
id|pages
comma
id|npages
suffix:semicolon
r_if
c_cond
(paren
id|laddr
OG
l_int|0xffffff
)paren
(brace
r_if
c_cond
(paren
id|vdma_debug
)paren
id|printk
(paren
l_string|&quot;vdma_map: Invalid logical address: %08lx&bslash;n&quot;
comma
id|laddr
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* invalid logical address */
)brace
r_if
c_cond
(paren
id|paddr
OG
l_int|0x1fffffff
)paren
(brace
r_if
c_cond
(paren
id|vdma_debug
)paren
id|printk
(paren
l_string|&quot;vdma_map: Invalid physical address: %08lx&bslash;n&quot;
comma
id|paddr
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* invalid physical address */
)brace
id|npages
op_assign
id|pages
op_assign
(paren
(paren
(paren
id|paddr
op_amp
(paren
id|VDMA_PAGESIZE
op_minus
l_int|1
)paren
)paren
op_plus
id|size
)paren
op_rshift
l_int|12
)paren
op_plus
l_int|1
suffix:semicolon
id|first
op_assign
id|laddr
op_rshift
l_int|12
suffix:semicolon
r_if
c_cond
(paren
id|vdma_debug
)paren
id|printk
c_func
(paren
l_string|&quot;vdma_remap: first=%x, pages=%x&bslash;n&quot;
comma
id|first
comma
id|pages
)paren
suffix:semicolon
r_if
c_cond
(paren
id|first
op_plus
id|pages
OG
id|VDMA_PGTBL_ENTRIES
)paren
(brace
r_if
c_cond
(paren
id|vdma_debug
)paren
id|printk
c_func
(paren
l_string|&quot;vdma_alloc: Invalid size: %08lx&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|paddr
op_and_assign
op_complement
(paren
id|VDMA_PAGESIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|pages
OG
l_int|0
op_logical_and
id|first
OL
id|VDMA_PGTBL_ENTRIES
)paren
(brace
r_if
c_cond
(paren
id|pgtbl
(braket
id|first
)braket
dot
id|owner
op_ne
id|laddr
)paren
(brace
r_if
c_cond
(paren
id|vdma_debug
)paren
id|printk
c_func
(paren
l_string|&quot;Trying to remap other&squot;s pages.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/* not owner */
)brace
id|pgtbl
(braket
id|first
)braket
dot
id|frame
op_assign
id|paddr
suffix:semicolon
id|paddr
op_add_assign
id|VDMA_PAGESIZE
suffix:semicolon
id|first
op_increment
suffix:semicolon
id|pages
op_decrement
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Update translation table&n;&t; */
id|r4030_write_reg32
c_func
(paren
id|JAZZ_R4030_TRSTBL_INV
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vdma_debug
OG
l_int|2
)paren
(brace
r_int
id|i
suffix:semicolon
id|pages
op_assign
(paren
(paren
(paren
id|paddr
op_amp
(paren
id|VDMA_PAGESIZE
op_minus
l_int|1
)paren
)paren
op_plus
id|size
)paren
op_rshift
l_int|12
)paren
op_plus
l_int|1
suffix:semicolon
id|first
op_assign
id|laddr
op_rshift
l_int|12
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;LADDR: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|first
suffix:semicolon
id|i
OL
id|first
op_plus
id|pages
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%08x &quot;
comma
id|i
op_lshift
l_int|12
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nPADDR: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|first
suffix:semicolon
id|i
OL
id|first
op_plus
id|pages
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%08x &quot;
comma
id|pgtbl
(braket
id|i
)braket
dot
id|frame
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nOWNER: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|first
suffix:semicolon
id|i
OL
id|first
op_plus
id|pages
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%08x &quot;
comma
id|pgtbl
(braket
id|i
)braket
dot
id|owner
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Translate a physical address to a logical address.&n; * This will return the logical address of the first&n; * match.&n; */
DECL|function|vdma_phys2log
r_int
r_int
id|vdma_phys2log
c_func
(paren
r_int
r_int
id|paddr
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|frame
suffix:semicolon
id|VDMA_PGTBL_ENTRY
op_star
id|pgtbl
op_assign
(paren
id|VDMA_PGTBL_ENTRY
op_star
)paren
id|vdma_pagetable_start
suffix:semicolon
id|frame
op_assign
id|paddr
op_amp
op_complement
(paren
id|VDMA_PAGESIZE
op_minus
l_int|1
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
id|VDMA_PGTBL_ENTRIES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pgtbl
(braket
id|i
)braket
dot
id|frame
op_eq
id|frame
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|VDMA_PGTBL_ENTRIES
)paren
r_return
op_complement
l_int|0UL
suffix:semicolon
r_return
(paren
id|i
op_lshift
l_int|12
)paren
op_plus
(paren
id|paddr
op_amp
(paren
id|VDMA_PAGESIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
DECL|variable|vdma_phys2log
id|EXPORT_SYMBOL
c_func
(paren
id|vdma_phys2log
)paren
suffix:semicolon
multiline_comment|/*&n; * Translate a logical DMA address to a physical address&n; */
DECL|function|vdma_log2phys
r_int
r_int
id|vdma_log2phys
c_func
(paren
r_int
r_int
id|laddr
)paren
(brace
id|VDMA_PGTBL_ENTRY
op_star
id|pgtbl
op_assign
(paren
id|VDMA_PGTBL_ENTRY
op_star
)paren
id|vdma_pagetable_start
suffix:semicolon
r_return
id|pgtbl
(braket
id|laddr
op_rshift
l_int|12
)braket
dot
id|frame
op_plus
(paren
id|laddr
op_amp
(paren
id|VDMA_PAGESIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
DECL|variable|vdma_log2phys
id|EXPORT_SYMBOL
c_func
(paren
id|vdma_log2phys
)paren
suffix:semicolon
multiline_comment|/*&n; * Print DMA statistics&n; */
DECL|function|vdma_stats
r_void
id|vdma_stats
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;vdma_stats: CONFIG: %08x&bslash;n&quot;
comma
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_CONFIG
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;R4030 translation table base: %08x&bslash;n&quot;
comma
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_TRSTBL_BASE
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;R4030 translation table limit: %08x&bslash;n&quot;
comma
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_TRSTBL_LIM
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;vdma_stats: INV_ADDR: %08x&bslash;n&quot;
comma
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_INV_ADDR
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;vdma_stats: R_FAIL_ADDR: %08x&bslash;n&quot;
comma
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_R_FAIL_ADDR
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;vdma_stats: M_FAIL_ADDR: %08x&bslash;n&quot;
comma
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_M_FAIL_ADDR
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;vdma_stats: IRQ_SOURCE: %08x&bslash;n&quot;
comma
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_IRQ_SOURCE
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;vdma_stats: I386_ERROR: %08x&bslash;n&quot;
comma
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_I386_ERROR
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;vdma_chnl_modes:   &quot;
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%04x &quot;
comma
(paren
r_int
)paren
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_MODE
op_plus
(paren
id|i
op_lshift
l_int|5
)paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;vdma_chnl_enables: &quot;
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%04x &quot;
comma
(paren
r_int
)paren
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_ENABLE
op_plus
(paren
id|i
op_lshift
l_int|5
)paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * DMA transfer functions&n; */
multiline_comment|/*&n; * Enable a DMA channel. Also clear any error conditions.&n; */
DECL|function|vdma_enable
r_void
id|vdma_enable
c_func
(paren
r_int
id|channel
)paren
(brace
r_int
id|status
suffix:semicolon
r_if
c_cond
(paren
id|vdma_debug
)paren
id|printk
c_func
(paren
l_string|&quot;vdma_enable: channel %d&bslash;n&quot;
comma
id|channel
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check error conditions first&n;&t; */
id|status
op_assign
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_ENABLE
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x400
)paren
id|printk
c_func
(paren
l_string|&quot;VDMA: Channel %d: Address error!&bslash;n&quot;
comma
id|channel
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x200
)paren
id|printk
c_func
(paren
l_string|&quot;VDMA: Channel %d: Memory error!&bslash;n&quot;
comma
id|channel
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Clear all interrupt flags&n;&t; */
id|r4030_write_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_ENABLE
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
comma
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_ENABLE
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
)paren
op_or
id|R4030_TC_INTR
op_or
id|R4030_MEM_INTR
op_or
id|R4030_ADDR_INTR
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Enable the desired channel&n;&t; */
id|r4030_write_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_ENABLE
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
comma
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_ENABLE
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
)paren
op_or
id|R4030_CHNL_ENABLE
)paren
suffix:semicolon
)brace
DECL|variable|vdma_enable
id|EXPORT_SYMBOL
c_func
(paren
id|vdma_enable
)paren
suffix:semicolon
multiline_comment|/*&n; * Disable a DMA channel&n; */
DECL|function|vdma_disable
r_void
id|vdma_disable
c_func
(paren
r_int
id|channel
)paren
(brace
r_if
c_cond
(paren
id|vdma_debug
)paren
(brace
r_int
id|status
op_assign
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_ENABLE
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;vdma_disable: channel %d&bslash;n&quot;
comma
id|channel
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;VDMA: channel %d status: %04x (%s) mode: &quot;
l_string|&quot;%02x addr: %06x count: %06x&bslash;n&quot;
comma
id|channel
comma
id|status
comma
(paren
(paren
id|status
op_amp
l_int|0x600
)paren
ques
c_cond
l_string|&quot;ERROR&quot;
suffix:colon
l_string|&quot;OK&quot;
)paren
comma
(paren
r_int
)paren
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_MODE
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
)paren
comma
(paren
r_int
)paren
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_ADDR
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
)paren
comma
(paren
r_int
)paren
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_COUNT
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
)paren
)paren
suffix:semicolon
)brace
id|r4030_write_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_ENABLE
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
comma
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_ENABLE
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
)paren
op_amp
op_complement
id|R4030_CHNL_ENABLE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * After disabling a DMA channel a remote bus register should be&n;&t; * read to ensure that the current DMA acknowledge cycle is completed.&n;&t; */
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|JAZZ_DUMMY_DEVICE
)paren
suffix:semicolon
)brace
DECL|variable|vdma_disable
id|EXPORT_SYMBOL
c_func
(paren
id|vdma_disable
)paren
suffix:semicolon
multiline_comment|/*&n; * Set DMA mode. This function accepts the mode values used&n; * to set a PC-style DMA controller. For the SCSI and FDC&n; * channels, we also set the default modes each time we&squot;re&n; * called.&n; * NOTE: The FAST and BURST dma modes are supported by the&n; * R4030 Rev. 2 and PICA chipsets only. I leave them disabled&n; * for now.&n; */
DECL|function|vdma_set_mode
r_void
id|vdma_set_mode
c_func
(paren
r_int
id|channel
comma
r_int
id|mode
)paren
(brace
r_if
c_cond
(paren
id|vdma_debug
)paren
id|printk
c_func
(paren
l_string|&quot;vdma_set_mode: channel %d, mode 0x%x&bslash;n&quot;
comma
id|channel
comma
id|mode
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|channel
)paren
(brace
r_case
id|JAZZ_SCSI_DMA
suffix:colon
multiline_comment|/* scsi */
id|r4030_write_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_MODE
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
comma
multiline_comment|/*&t;&t;&t;  R4030_MODE_FAST | */
multiline_comment|/*&t;&t;&t;  R4030_MODE_BURST | */
id|R4030_MODE_INTR_EN
op_or
id|R4030_MODE_WIDTH_16
op_or
id|R4030_MODE_ATIME_80
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|JAZZ_FLOPPY_DMA
suffix:colon
multiline_comment|/* floppy */
id|r4030_write_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_MODE
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
comma
multiline_comment|/*&t;&t;&t;  R4030_MODE_FAST | */
multiline_comment|/*&t;&t;&t;  R4030_MODE_BURST | */
id|R4030_MODE_INTR_EN
op_or
id|R4030_MODE_WIDTH_8
op_or
id|R4030_MODE_ATIME_120
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|JAZZ_AUDIOL_DMA
suffix:colon
r_case
id|JAZZ_AUDIOR_DMA
suffix:colon
id|printk
c_func
(paren
l_string|&quot;VDMA: Audio DMA not supported yet.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
(paren
l_string|&quot;VDMA: vdma_set_mode() called with unsupported channel %d!&bslash;n&quot;
comma
id|channel
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|DMA_MODE_READ
suffix:colon
id|r4030_write_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_ENABLE
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
comma
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_ENABLE
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
)paren
op_amp
op_complement
id|R4030_CHNL_WRITE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DMA_MODE_WRITE
suffix:colon
id|r4030_write_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_ENABLE
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
comma
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_ENABLE
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
)paren
op_or
id|R4030_CHNL_WRITE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
(paren
l_string|&quot;VDMA: vdma_set_mode() called with unknown dma mode 0x%x&bslash;n&quot;
comma
id|mode
)paren
suffix:semicolon
)brace
)brace
DECL|variable|vdma_set_mode
id|EXPORT_SYMBOL
c_func
(paren
id|vdma_set_mode
)paren
suffix:semicolon
multiline_comment|/*&n; * Set Transfer Address&n; */
DECL|function|vdma_set_addr
r_void
id|vdma_set_addr
c_func
(paren
r_int
id|channel
comma
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|vdma_debug
)paren
id|printk
c_func
(paren
l_string|&quot;vdma_set_addr: channel %d, addr %lx&bslash;n&quot;
comma
id|channel
comma
id|addr
)paren
suffix:semicolon
id|r4030_write_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_ADDR
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|variable|vdma_set_addr
id|EXPORT_SYMBOL
c_func
(paren
id|vdma_set_addr
)paren
suffix:semicolon
multiline_comment|/*&n; * Set Transfer Count&n; */
DECL|function|vdma_set_count
r_void
id|vdma_set_count
c_func
(paren
r_int
id|channel
comma
r_int
id|count
)paren
(brace
r_if
c_cond
(paren
id|vdma_debug
)paren
id|printk
c_func
(paren
l_string|&quot;vdma_set_count: channel %d, count %08x&bslash;n&quot;
comma
id|channel
comma
(paren
r_int
)paren
id|count
)paren
suffix:semicolon
id|r4030_write_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_COUNT
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
comma
id|count
)paren
suffix:semicolon
)brace
DECL|variable|vdma_set_count
id|EXPORT_SYMBOL
c_func
(paren
id|vdma_set_count
)paren
suffix:semicolon
multiline_comment|/*&n; * Get Residual&n; */
DECL|function|vdma_get_residue
r_int
id|vdma_get_residue
c_func
(paren
r_int
id|channel
)paren
(brace
r_int
id|residual
suffix:semicolon
id|residual
op_assign
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_COUNT
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vdma_debug
)paren
id|printk
c_func
(paren
l_string|&quot;vdma_get_residual: channel %d: residual=%d&bslash;n&quot;
comma
id|channel
comma
id|residual
)paren
suffix:semicolon
r_return
id|residual
suffix:semicolon
)brace
multiline_comment|/*&n; * Get DMA channel enable register&n; */
DECL|function|vdma_get_enable
r_int
id|vdma_get_enable
c_func
(paren
r_int
id|channel
)paren
(brace
r_int
id|enable
suffix:semicolon
id|enable
op_assign
id|r4030_read_reg32
c_func
(paren
id|JAZZ_R4030_CHNL_ENABLE
op_plus
(paren
id|channel
op_lshift
l_int|5
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vdma_debug
)paren
id|printk
c_func
(paren
l_string|&quot;vdma_get_enable: channel %d: enable=%d&bslash;n&quot;
comma
id|channel
comma
id|enable
)paren
suffix:semicolon
r_return
id|enable
suffix:semicolon
)brace
eof
