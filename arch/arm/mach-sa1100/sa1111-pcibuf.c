multiline_comment|/*&n; *  linux/arch/arm/mach-sa1100/pci-sa1111.c&n; *&n; *  Special pci_{map/unmap/dma_sync}_* routines for SA-1111.&n; *&n; *  These functions utilize bouncer buffers to compensate for a bug in&n; *  the SA-1111 hardware which don&squot;t allow DMA to/from addresses&n; *  certain addresses above 1MB.&n; *&n; *  Re-written by Christopher Hoover &lt;ch@murgatroid.com&gt;&n; *  Original version by Brad Parker (brad@heeltoe.com)&n; *&n; *  Copyright (C) 2002 Hewlett Packard Company.&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  version 2 as published by the Free Software Foundation.&n; * */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;asm/hardware/sa1111.h&gt;
singleline_comment|//#define DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(...) do { printk(KERN_DEBUG __VA_ARGS__); } while (0)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(...) do { } while (0)
macro_line|#endif
singleline_comment|//#define STATS
macro_line|#ifdef STATS
DECL|macro|DO_STATS
mdefine_line|#define DO_STATS(X) do { X ; } while (0)
macro_line|#else
DECL|macro|DO_STATS
mdefine_line|#define DO_STATS(X) do { } while (0)
macro_line|#endif
multiline_comment|/* ************************************************** */
DECL|struct|safe_buffer
r_struct
id|safe_buffer
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
multiline_comment|/* original request */
DECL|member|ptr
r_void
op_star
id|ptr
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|direction
r_int
id|direction
suffix:semicolon
multiline_comment|/* safe buffer info */
DECL|member|pool
r_struct
id|pci_pool
op_star
id|pool
suffix:semicolon
DECL|member|safe
r_void
op_star
id|safe
suffix:semicolon
DECL|member|safe_dma_addr
id|dma_addr_t
id|safe_dma_addr
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|safe_buffers
id|LIST_HEAD
c_func
(paren
id|safe_buffers
)paren
suffix:semicolon
DECL|macro|SIZE_SMALL
mdefine_line|#define SIZE_SMALL&t;1024
DECL|macro|SIZE_LARGE
mdefine_line|#define SIZE_LARGE&t;(4*1024)
DECL|variable|small_buffer_pool
DECL|variable|large_buffer_pool
r_static
r_struct
id|pci_pool
op_star
id|small_buffer_pool
comma
op_star
id|large_buffer_pool
suffix:semicolon
macro_line|#ifdef STATS
DECL|variable|__initdata
r_static
r_int
r_int
id|sbp_allocs
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
r_int
id|lbp_allocs
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
r_int
id|total_allocs
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|function|print_alloc_stats
r_static
r_void
id|print_alloc_stats
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;sa1111_pcibuf: sbp: %lu, lbp: %lu, other: %lu, total: %lu&bslash;n&quot;
comma
id|sbp_allocs
comma
id|lbp_allocs
comma
id|total_allocs
op_minus
id|sbp_allocs
op_minus
id|lbp_allocs
comma
id|total_allocs
)paren
suffix:semicolon
)brace
macro_line|#endif
r_static
r_int
id|__init
DECL|function|create_safe_buffer_pools
id|create_safe_buffer_pools
c_func
(paren
r_void
)paren
(brace
id|small_buffer_pool
op_assign
id|pci_pool_create
c_func
(paren
l_string|&quot;sa1111_small_dma_buffer&quot;
comma
id|SA1111_FAKE_PCIDEV
comma
id|SIZE_SMALL
comma
l_int|0
multiline_comment|/* byte alignment */
comma
l_int|0
multiline_comment|/* no page-crossing issues */
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_eq
id|small_buffer_pool
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sa1111_pcibuf: could not allocate small pci pool&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|large_buffer_pool
op_assign
id|pci_pool_create
c_func
(paren
l_string|&quot;sa1111_large_dma_buffer&quot;
comma
id|SA1111_FAKE_PCIDEV
comma
id|SIZE_LARGE
comma
l_int|0
multiline_comment|/* byte alignment */
comma
l_int|0
multiline_comment|/* no page-crossing issues */
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_eq
id|large_buffer_pool
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sa1111_pcibuf: could not allocate large pci pool&bslash;n&quot;
)paren
suffix:semicolon
id|pci_pool_destroy
c_func
(paren
id|small_buffer_pool
)paren
suffix:semicolon
id|small_buffer_pool
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;sa1111_pcibuf: buffer sizes: small=%u, large=%u&bslash;n&quot;
comma
id|SIZE_SMALL
comma
id|SIZE_LARGE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|destroy_safe_buffer_pools
id|destroy_safe_buffer_pools
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|small_buffer_pool
)paren
id|pci_pool_destroy
c_func
(paren
id|small_buffer_pool
)paren
suffix:semicolon
r_if
c_cond
(paren
id|large_buffer_pool
)paren
id|pci_pool_destroy
c_func
(paren
id|large_buffer_pool
)paren
suffix:semicolon
id|small_buffer_pool
op_assign
id|large_buffer_pool
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* allocate a &squot;safe&squot; buffer and keep track of it */
r_static
r_struct
id|safe_buffer
op_star
DECL|function|alloc_safe_buffer
id|alloc_safe_buffer
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
r_struct
id|safe_buffer
op_star
id|buf
suffix:semicolon
r_struct
id|pci_pool
op_star
id|pool
suffix:semicolon
r_void
op_star
id|safe
suffix:semicolon
id|dma_addr_t
id|safe_dma_addr
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;%s(ptr=%p, size=%d, direction=%d)&bslash;n&quot;
comma
id|__func__
comma
id|ptr
comma
id|size
comma
id|direction
)paren
suffix:semicolon
id|DO_STATS
(paren
id|total_allocs
op_increment
)paren
suffix:semicolon
id|buf
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|safe_buffer
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: kmalloc failed&bslash;n&quot;
comma
id|__func__
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
op_le
id|SIZE_SMALL
)paren
(brace
id|pool
op_assign
id|small_buffer_pool
suffix:semicolon
id|safe
op_assign
id|pci_pool_alloc
c_func
(paren
id|pool
comma
id|GFP_ATOMIC
comma
op_amp
id|safe_dma_addr
)paren
suffix:semicolon
id|DO_STATS
(paren
id|sbp_allocs
op_increment
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|size
op_le
id|SIZE_LARGE
)paren
(brace
id|pool
op_assign
id|large_buffer_pool
suffix:semicolon
id|safe
op_assign
id|pci_pool_alloc
c_func
(paren
id|pool
comma
id|GFP_ATOMIC
comma
op_amp
id|safe_dma_addr
)paren
suffix:semicolon
id|DO_STATS
(paren
id|lbp_allocs
op_increment
)paren
suffix:semicolon
)brace
r_else
(brace
id|pool
op_assign
l_int|0
suffix:semicolon
id|safe
op_assign
id|pci_alloc_consistent
c_func
(paren
id|SA1111_FAKE_PCIDEV
comma
id|size
comma
op_amp
id|safe_dma_addr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|safe
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: could not alloc dma memory (size=%d)&bslash;n&quot;
comma
id|__func__
comma
id|size
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef STATS
r_if
c_cond
(paren
id|total_allocs
op_mod
l_int|1000
op_eq
l_int|0
)paren
id|print_alloc_stats
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|BUG_ON
c_func
(paren
id|sa1111_check_dma_bug
c_func
(paren
id|safe_dma_addr
)paren
)paren
suffix:semicolon
singleline_comment|// paranoia
id|buf-&gt;ptr
op_assign
id|ptr
suffix:semicolon
id|buf-&gt;size
op_assign
id|size
suffix:semicolon
id|buf-&gt;direction
op_assign
id|direction
suffix:semicolon
id|buf-&gt;pool
op_assign
id|pool
suffix:semicolon
id|buf-&gt;safe
op_assign
id|safe
suffix:semicolon
id|buf-&gt;safe_dma_addr
op_assign
id|safe_dma_addr
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|buf-&gt;node
comma
op_amp
id|safe_buffers
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
multiline_comment|/* determine if a buffer is from our &quot;safe&quot; pool */
r_static
r_struct
id|safe_buffer
op_star
DECL|function|find_safe_buffer
id|find_safe_buffer
c_func
(paren
id|dma_addr_t
id|safe_dma_addr
)paren
(brace
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
comma
op_amp
id|safe_buffers
)paren
(brace
r_struct
id|safe_buffer
op_star
id|b
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|safe_buffer
comma
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b-&gt;safe_dma_addr
op_eq
id|safe_dma_addr
)paren
(brace
r_return
id|b
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|free_safe_buffer
id|free_safe_buffer
c_func
(paren
r_struct
id|safe_buffer
op_star
id|buf
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;%s(buf=%p)&bslash;n&quot;
comma
id|__func__
comma
id|buf
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|buf-&gt;node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf-&gt;pool
)paren
id|pci_pool_free
c_func
(paren
id|buf-&gt;pool
comma
id|buf-&gt;safe
comma
id|buf-&gt;safe_dma_addr
)paren
suffix:semicolon
r_else
id|pci_free_consistent
c_func
(paren
id|SA1111_FAKE_PCIDEV
comma
id|buf-&gt;size
comma
id|buf-&gt;safe
comma
id|buf-&gt;safe_dma_addr
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|dma_range_is_safe
id|dma_range_is_safe
c_func
(paren
id|dma_addr_t
id|addr
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|physaddr
op_assign
id|SA1111_DMA_ADDR
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
)paren
suffix:semicolon
multiline_comment|/* Any address within one megabyte of the start of the target&n;         * bank will be OK.  This is an overly conservative test:&n;         * other addresses can be OK depending on the dram&n;         * configuration.  (See sa1111.c:sa1111_check_dma_bug() * for&n;         * details.)&n;&t; *&n;&t; * We take care to ensure the entire dma region is within&n;&t; * the safe range.&n;&t; */
r_return
(paren
(paren
id|physaddr
op_plus
id|size
op_minus
l_int|1
)paren
OL
(paren
l_int|1
op_lshift
l_int|20
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* ************************************************** */
macro_line|#ifdef STATS
DECL|variable|__initdata
r_static
r_int
r_int
id|map_op_count
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
r_int
id|bounce_count
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|function|print_map_stats
r_static
r_void
id|print_map_stats
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;sa1111_pcibuf: map_op_count=%lu, bounce_count=%lu&bslash;n&quot;
comma
id|map_op_count
comma
id|bounce_count
)paren
suffix:semicolon
)brace
macro_line|#endif
r_static
id|dma_addr_t
DECL|function|map_single
id|map_single
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
id|dma_addr_t
id|dma_addr
suffix:semicolon
id|DO_STATS
(paren
id|map_op_count
op_increment
)paren
suffix:semicolon
id|dma_addr
op_assign
id|virt_to_bus
c_func
(paren
id|ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma_range_is_safe
c_func
(paren
id|dma_addr
comma
id|size
)paren
)paren
(brace
r_struct
id|safe_buffer
op_star
id|buf
suffix:semicolon
id|DO_STATS
(paren
id|bounce_count
op_increment
)paren
suffix:semicolon
id|buf
op_assign
id|alloc_safe_buffer
c_func
(paren
id|hwdev
comma
id|ptr
comma
id|size
comma
id|direction
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to map unsafe buffer %p!&bslash;n&quot;
comma
id|__func__
comma
id|ptr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|DPRINTK
c_func
(paren
l_string|&quot;%s: unsafe buffer %p (phy=%p) mapped to %p (phy=%p)&bslash;n&quot;
comma
id|__func__
comma
id|buf-&gt;ptr
comma
(paren
r_void
op_star
)paren
id|virt_to_bus
c_func
(paren
id|buf-&gt;ptr
)paren
comma
id|buf-&gt;safe
comma
(paren
r_void
op_star
)paren
id|buf-&gt;safe_dma_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|direction
op_eq
id|PCI_DMA_TODEVICE
)paren
op_logical_or
(paren
id|direction
op_eq
id|PCI_DMA_BIDIRECTIONAL
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;%s: copy out from unsafe %p, to safe %p, size %d&bslash;n&quot;
comma
id|__func__
comma
id|ptr
comma
id|buf-&gt;safe
comma
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buf-&gt;safe
comma
id|ptr
comma
id|size
)paren
suffix:semicolon
)brace
id|consistent_sync
c_func
(paren
id|buf-&gt;safe
comma
id|size
comma
id|direction
)paren
suffix:semicolon
id|dma_addr
op_assign
id|buf-&gt;safe_dma_addr
suffix:semicolon
)brace
r_else
(brace
id|consistent_sync
c_func
(paren
id|ptr
comma
id|size
comma
id|direction
)paren
suffix:semicolon
)brace
macro_line|#ifdef STATS
r_if
c_cond
(paren
id|map_op_count
op_mod
l_int|1000
op_eq
l_int|0
)paren
id|print_map_stats
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|dma_addr
suffix:semicolon
)brace
r_static
r_void
DECL|function|unmap_single
id|unmap_single
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
r_struct
id|safe_buffer
op_star
id|buf
suffix:semicolon
id|buf
op_assign
id|find_safe_buffer
c_func
(paren
id|dma_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
)paren
(brace
id|BUG_ON
c_func
(paren
id|buf-&gt;size
op_ne
id|size
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|buf-&gt;direction
op_ne
id|direction
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;%s: unsafe buffer %p (phy=%p) mapped to %p (phy=%p)&bslash;n&quot;
comma
id|__func__
comma
id|buf-&gt;ptr
comma
(paren
r_void
op_star
)paren
id|virt_to_bus
c_func
(paren
id|buf-&gt;ptr
)paren
comma
id|buf-&gt;safe
comma
(paren
r_void
op_star
)paren
id|buf-&gt;safe_dma_addr
)paren
suffix:semicolon
id|DO_STATS
(paren
id|bounce_count
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|direction
op_eq
id|PCI_DMA_FROMDEVICE
)paren
op_logical_or
(paren
id|direction
op_eq
id|PCI_DMA_BIDIRECTIONAL
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;%s: copy back from safe %p, to unsafe %p size %d&bslash;n&quot;
comma
id|__func__
comma
id|buf-&gt;safe
comma
id|buf-&gt;ptr
comma
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buf-&gt;ptr
comma
id|buf-&gt;safe
comma
id|size
)paren
suffix:semicolon
)brace
id|free_safe_buffer
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|sync_single
id|sync_single
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
r_struct
id|safe_buffer
op_star
id|buf
suffix:semicolon
id|buf
op_assign
id|find_safe_buffer
c_func
(paren
id|dma_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
)paren
(brace
id|BUG_ON
c_func
(paren
id|buf-&gt;size
op_ne
id|size
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|buf-&gt;direction
op_ne
id|direction
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;%s: unsafe buffer %p (phy=%p) mapped to %p (phy=%p)&bslash;n&quot;
comma
id|__func__
comma
id|buf-&gt;ptr
comma
(paren
r_void
op_star
)paren
id|virt_to_bus
c_func
(paren
id|buf-&gt;ptr
)paren
comma
id|buf-&gt;safe
comma
(paren
r_void
op_star
)paren
id|buf-&gt;safe_dma_addr
)paren
suffix:semicolon
id|DO_STATS
(paren
id|bounce_count
op_increment
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|direction
)paren
(brace
r_case
id|PCI_DMA_FROMDEVICE
suffix:colon
id|DPRINTK
c_func
(paren
l_string|&quot;%s: copy back from safe %p, to unsafe %p size %d&bslash;n&quot;
comma
id|__func__
comma
id|buf-&gt;safe
comma
id|buf-&gt;ptr
comma
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buf-&gt;ptr
comma
id|buf-&gt;safe
comma
id|size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_DMA_TODEVICE
suffix:colon
id|DPRINTK
c_func
(paren
l_string|&quot;%s: copy out from unsafe %p, to safe %p, size %d&bslash;n&quot;
comma
id|__func__
comma
id|buf-&gt;ptr
comma
id|buf-&gt;safe
comma
id|size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buf-&gt;safe
comma
id|buf-&gt;ptr
comma
id|size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_DMA_BIDIRECTIONAL
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* is this allowed?  what does it mean? */
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|consistent_sync
c_func
(paren
id|buf-&gt;safe
comma
id|size
comma
id|direction
)paren
suffix:semicolon
)brace
r_else
(brace
id|consistent_sync
c_func
(paren
id|bus_to_virt
c_func
(paren
id|dma_addr
)paren
comma
id|size
comma
id|direction
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* ************************************************** */
multiline_comment|/*&n; * see if a buffer address is in an &squot;unsafe&squot; range.  if it is&n; * allocate a &squot;safe&squot; buffer and copy the unsafe buffer into it.&n; * substitute the safe buffer for the unsafe one.&n; * (basically move the buffer from an unsafe area to a safe one)&n; */
id|dma_addr_t
DECL|function|sa1111_map_single
id|sa1111_map_single
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
r_int
r_int
id|flags
suffix:semicolon
id|dma_addr_t
id|dma_addr
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;%s(hwdev=%p,ptr=%p,size=%d,dir=%x)&bslash;n&quot;
comma
id|__func__
comma
id|hwdev
comma
id|ptr
comma
id|size
comma
id|direction
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|hwdev
op_ne
id|SA1111_FAKE_PCIDEV
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|dma_addr
op_assign
id|map_single
c_func
(paren
id|hwdev
comma
id|ptr
comma
id|size
comma
id|direction
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|dma_addr
suffix:semicolon
)brace
multiline_comment|/*&n; * see if a mapped address was really a &quot;safe&quot; buffer and if so, copy&n; * the data from the safe buffer back to the unsafe buffer and free up&n; * the safe buffer.  (basically return things back to the way they&n; * should be)&n; */
r_void
DECL|function|sa1111_unmap_single
id|sa1111_unmap_single
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
id|flags
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;%s(hwdev=%p,ptr=%p,size=%d,dir=%x)&bslash;n&quot;
comma
id|__func__
comma
id|hwdev
comma
(paren
r_void
op_star
)paren
id|dma_addr
comma
id|size
comma
id|direction
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|hwdev
op_ne
id|SA1111_FAKE_PCIDEV
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|unmap_single
c_func
(paren
id|hwdev
comma
id|dma_addr
comma
id|size
comma
id|direction
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_int
DECL|function|sa1111_map_sg
id|sa1111_map_sg
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
r_int
id|flags
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;%s(hwdev=%p,sg=%p,nents=%d,dir=%x)&bslash;n&quot;
comma
id|__func__
comma
id|hwdev
comma
id|sg
comma
id|nents
comma
id|direction
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|hwdev
op_ne
id|SA1111_FAKE_PCIDEV
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
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
id|nents
suffix:semicolon
id|i
op_increment
comma
id|sg
op_increment
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|sg-&gt;page
suffix:semicolon
r_int
r_int
id|offset
op_assign
id|sg-&gt;offset
suffix:semicolon
r_int
r_int
id|length
op_assign
id|sg-&gt;length
suffix:semicolon
r_void
op_star
id|ptr
op_assign
id|page_address
c_func
(paren
id|page
)paren
op_plus
id|offset
suffix:semicolon
id|sg-&gt;dma_address
op_assign
id|map_single
c_func
(paren
id|hwdev
comma
id|ptr
comma
id|length
comma
id|direction
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|nents
suffix:semicolon
)brace
r_void
DECL|function|sa1111_unmap_sg
id|sa1111_unmap_sg
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
r_int
id|flags
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;%s(hwdev=%p,sg=%p,nents=%d,dir=%x)&bslash;n&quot;
comma
id|__func__
comma
id|hwdev
comma
id|sg
comma
id|nents
comma
id|direction
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|hwdev
op_ne
id|SA1111_FAKE_PCIDEV
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
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
id|nents
suffix:semicolon
id|i
op_increment
comma
id|sg
op_increment
)paren
(brace
id|dma_addr_t
id|dma_addr
op_assign
id|sg-&gt;dma_address
suffix:semicolon
r_int
r_int
id|length
op_assign
id|sg-&gt;length
suffix:semicolon
id|unmap_single
c_func
(paren
id|hwdev
comma
id|dma_addr
comma
id|length
comma
id|direction
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_void
DECL|function|sa1111_dma_sync_single
id|sa1111_dma_sync_single
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
id|flags
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;%s(hwdev=%p,ptr=%p,size=%d,dir=%x)&bslash;n&quot;
comma
id|__func__
comma
id|hwdev
comma
(paren
r_void
op_star
)paren
id|dma_addr
comma
id|size
comma
id|direction
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|hwdev
op_ne
id|SA1111_FAKE_PCIDEV
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|sync_single
c_func
(paren
id|hwdev
comma
id|dma_addr
comma
id|size
comma
id|direction
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_void
DECL|function|sa1111_dma_sync_sg
id|sa1111_dma_sync_sg
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
r_int
id|flags
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;%s(hwdev=%p,sg=%p,nents=%d,dir=%x)&bslash;n&quot;
comma
id|__func__
comma
id|hwdev
comma
id|sg
comma
id|nents
comma
id|direction
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|hwdev
op_ne
id|SA1111_FAKE_PCIDEV
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|direction
op_eq
id|PCI_DMA_NONE
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
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
id|nents
suffix:semicolon
id|i
op_increment
comma
id|sg
op_increment
)paren
(brace
id|dma_addr_t
id|dma_addr
op_assign
id|sg-&gt;dma_address
suffix:semicolon
r_int
r_int
id|length
op_assign
id|sg-&gt;length
suffix:semicolon
id|sync_single
c_func
(paren
id|hwdev
comma
id|dma_addr
comma
id|length
comma
id|direction
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|sa1111_map_single
id|EXPORT_SYMBOL
c_func
(paren
id|sa1111_map_single
)paren
suffix:semicolon
DECL|variable|sa1111_unmap_single
id|EXPORT_SYMBOL
c_func
(paren
id|sa1111_unmap_single
)paren
suffix:semicolon
DECL|variable|sa1111_map_sg
id|EXPORT_SYMBOL
c_func
(paren
id|sa1111_map_sg
)paren
suffix:semicolon
DECL|variable|sa1111_unmap_sg
id|EXPORT_SYMBOL
c_func
(paren
id|sa1111_unmap_sg
)paren
suffix:semicolon
DECL|variable|sa1111_dma_sync_single
id|EXPORT_SYMBOL
c_func
(paren
id|sa1111_dma_sync_single
)paren
suffix:semicolon
DECL|variable|sa1111_dma_sync_sg
id|EXPORT_SYMBOL
c_func
(paren
id|sa1111_dma_sync_sg
)paren
suffix:semicolon
multiline_comment|/* **************************************** */
DECL|function|sa1111_pcibuf_init
r_static
r_int
id|__init
id|sa1111_pcibuf_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;sa1111_pcibuf: initializing SA-1111 DMA workaround&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
id|create_safe_buffer_pools
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|sa1111_pcibuf_init
id|module_init
c_func
(paren
id|sa1111_pcibuf_init
)paren
suffix:semicolon
DECL|function|sa1111_pcibuf_exit
r_static
r_void
id|__exit
id|sa1111_pcibuf_exit
c_func
(paren
r_void
)paren
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|safe_buffers
)paren
)paren
suffix:semicolon
macro_line|#ifdef STATS
id|print_alloc_stats
c_func
(paren
)paren
suffix:semicolon
id|print_map_stats
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|destroy_safe_buffer_pools
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|sa1111_pcibuf_exit
id|module_exit
c_func
(paren
id|sa1111_pcibuf_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Christopher Hoover &lt;ch@hpl.hp.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Special pci_{map/unmap/dma_sync}_* routines for SA-1111.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
