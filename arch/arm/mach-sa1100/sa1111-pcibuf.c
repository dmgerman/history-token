multiline_comment|/*&n; *  linux/arch/arm/mach-sa1100/pci-sa1111.c&n; *&n; *  Special pci_map/unmap_single routines for SA-1111.   These functions&n; *  compensate for a bug in the SA-1111 hardware which don&squot;t allow DMA&n; *  to/from addresses above 1MB.&n; *&n; *  Brad Parker (brad@heeltoe.com)&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License version 2 as&n; *  published by the Free Software Foundation.&n; *&n; *  06/13/2001 - created.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;pcipool.h&quot;
multiline_comment|/*&n; * simple buffer allocator for copying of unsafe to safe buffers&n; * uses __alloc/__free for actual buffers&n; * keeps track of safe buffers we&squot;ve allocated so we can recover the&n; * unsafe buffers.&n; */
DECL|macro|MAX_SAFE
mdefine_line|#define MAX_SAFE&t;32
DECL|macro|SIZE_SMALL
mdefine_line|#define SIZE_SMALL&t;1024
DECL|macro|SIZE_LARGE
mdefine_line|#define SIZE_LARGE&t;(16*1024)
DECL|variable|mapped_alloc_size
r_static
r_int
id|mapped_alloc_size
suffix:semicolon
DECL|variable|safe_buffers
r_static
r_char
op_star
id|safe_buffers
(braket
id|MAX_SAFE
)braket
(braket
l_int|2
)braket
suffix:semicolon
DECL|variable|small_buffer_cache
DECL|variable|large_buffer_cache
r_static
r_struct
id|pci_pool
op_star
id|small_buffer_cache
comma
op_star
id|large_buffer_cache
suffix:semicolon
r_static
r_int
DECL|function|init_safe_buffers
id|init_safe_buffers
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|small_buffer_cache
op_assign
id|pci_pool_create
c_func
(paren
l_string|&quot;pci_small_buffer&quot;
comma
id|dev
comma
id|SIZE_SMALL
comma
l_int|0
multiline_comment|/* byte alignment */
comma
l_int|0
multiline_comment|/* no page-crossing issues */
comma
id|GFP_KERNEL
op_or
id|GFP_DMA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|small_buffer_cache
op_eq
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|large_buffer_cache
op_assign
id|pci_pool_create
c_func
(paren
l_string|&quot;pci_large_buffer&quot;
comma
id|dev
comma
id|SIZE_LARGE
comma
l_int|0
multiline_comment|/* byte alignment */
comma
l_int|0
multiline_comment|/* no page-crossing issues */
comma
id|GFP_KERNEL
op_or
id|GFP_DMA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|large_buffer_cache
op_eq
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* allocate a &squot;safe&squot; buffer and keep track of it */
r_static
r_char
op_star
DECL|function|alloc_safe_buffer
id|alloc_safe_buffer
c_func
(paren
r_char
op_star
id|unsafe
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|pbus
)paren
(brace
r_char
op_star
id|safe
suffix:semicolon
id|dma_addr_t
id|busptr
suffix:semicolon
r_struct
id|pci_pool
op_star
id|pool
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;alloc_safe_buffer(size=%d)&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_le
id|SIZE_SMALL
)paren
id|pool
op_assign
id|small_buffer_cache
suffix:semicolon
r_else
r_if
c_cond
(paren
id|size
OL
id|SIZE_LARGE
)paren
id|pool
op_assign
id|large_buffer_cache
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
id|safe
op_assign
id|pci_pool_alloc
c_func
(paren
id|pool
comma
id|SLAB_ATOMIC
comma
op_amp
id|busptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|safe
op_eq
l_int|0
)paren
r_return
l_int|0
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
id|MAX_SAFE
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|safe_buffers
(braket
id|i
)braket
(braket
l_int|0
)braket
op_eq
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|MAX_SAFE
)paren
(brace
id|panic
c_func
(paren
id|__FILE__
l_string|&quot;: exceeded MAX_SAFE buffers&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* place the size index and the old buffer ptr in the first 8 bytes&n;&t; * and return a ptr + 12 to caller&n;&t; */
(paren
(paren
r_int
op_star
)paren
id|safe
)paren
(braket
l_int|0
)braket
op_assign
id|i
suffix:semicolon
(paren
(paren
r_char
op_star
op_star
)paren
id|safe
)paren
(braket
l_int|1
)braket
op_assign
(paren
r_char
op_star
)paren
id|pool
suffix:semicolon
(paren
(paren
r_char
op_star
op_star
)paren
id|safe
)paren
(braket
l_int|2
)braket
op_assign
id|unsafe
suffix:semicolon
id|busptr
op_add_assign
r_sizeof
(paren
r_int
)paren
op_plus
r_sizeof
(paren
r_char
op_star
)paren
op_plus
r_sizeof
(paren
r_char
op_star
)paren
suffix:semicolon
id|safe_buffers
(braket
id|i
)braket
(braket
l_int|0
)braket
op_assign
(paren
r_void
op_star
)paren
id|busptr
suffix:semicolon
id|safe_buffers
(braket
id|i
)braket
(braket
l_int|1
)braket
op_assign
(paren
r_void
op_star
)paren
id|safe
suffix:semicolon
id|safe
op_add_assign
r_sizeof
(paren
r_int
)paren
op_plus
r_sizeof
(paren
r_char
op_star
)paren
op_plus
r_sizeof
(paren
r_char
op_star
)paren
suffix:semicolon
op_star
id|pbus
op_assign
id|busptr
suffix:semicolon
r_return
id|safe
suffix:semicolon
)brace
multiline_comment|/* determine if a buffer is from our &quot;safe&quot; pool */
r_static
r_char
op_star
DECL|function|find_safe_buffer
id|find_safe_buffer
c_func
(paren
r_char
op_star
id|busptr
comma
r_char
op_star
op_star
id|unsafe
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|buf
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
id|MAX_SAFE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|safe_buffers
(braket
id|i
)braket
(braket
l_int|0
)braket
op_eq
id|busptr
)paren
(brace
r_if
c_cond
(paren
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;find_safe_buffer(%p) found @ %d&bslash;n&quot;
comma
id|busptr
comma
id|i
)paren
suffix:semicolon
id|buf
op_assign
id|safe_buffers
(braket
id|i
)braket
(braket
l_int|1
)braket
suffix:semicolon
op_star
id|unsafe
op_assign
(paren
(paren
r_char
op_star
op_star
)paren
id|buf
)paren
(braket
l_int|2
)braket
suffix:semicolon
r_return
id|buf
op_plus
r_sizeof
(paren
r_int
)paren
op_plus
r_sizeof
(paren
r_char
op_star
)paren
op_plus
r_sizeof
(paren
r_char
op_star
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
r_char
op_star
)paren
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|free_safe_buffer
id|free_safe_buffer
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_int
id|index
suffix:semicolon
r_struct
id|pci_pool
op_star
id|pool
suffix:semicolon
r_char
op_star
id|dma
suffix:semicolon
r_if
c_cond
(paren
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;free_safe_buffer(buf=%p)&bslash;n&quot;
comma
id|buf
)paren
suffix:semicolon
multiline_comment|/* retrieve the buffer size index */
id|buf
op_sub_assign
r_sizeof
(paren
r_int
)paren
op_plus
r_sizeof
(paren
r_char
op_star
)paren
op_plus
r_sizeof
(paren
r_char
op_star
)paren
suffix:semicolon
id|index
op_assign
(paren
(paren
r_int
op_star
)paren
id|buf
)paren
(braket
l_int|0
)braket
suffix:semicolon
id|pool
op_assign
(paren
r_struct
id|pci_pool
op_star
)paren
(paren
(paren
r_char
op_star
op_star
)paren
id|buf
)paren
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;free_safe_buffer(%p) index %d&bslash;n&quot;
comma
id|buf
comma
id|index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index
OL
l_int|0
op_logical_or
id|index
op_ge
id|MAX_SAFE
)paren
(brace
id|printk
c_func
(paren
id|__FILE__
l_string|&quot;: free_safe_buffer() corrupt buffer&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|dma
op_assign
id|safe_buffers
(braket
id|index
)braket
(braket
l_int|0
)braket
suffix:semicolon
id|safe_buffers
(braket
id|index
)braket
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|pci_pool_free
c_func
(paren
id|pool
comma
id|buf
comma
(paren
id|u32
)paren
id|dma
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;  NOTE:&n;  replace pci_map/unmap_single with local routines which will&n;  do buffer copies if buffer is above 1mb...&n;*/
multiline_comment|/*&n; * see if a buffer address is in an &squot;unsafe&squot; range.  if it is&n; * allocate a &squot;safe&squot; buffer and copy the unsafe buffer into it.&n; * substitute the safe buffer for the unsafe one.&n; * (basically move the buffer from an unsafe area to a safe one)&n; *&n; * we assume calls to map_single are symmetric with calls to unmap_single...&n; */
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
id|virtptr
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
id|dma_addr_t
id|busptr
suffix:semicolon
id|mapped_alloc_size
op_add_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;pci_map_single(hwdev=%p,ptr=%p,size=%d,dir=%x) &quot;
l_string|&quot;alloced=%ld&bslash;n&quot;
comma
id|hwdev
comma
id|virtptr
comma
id|size
comma
id|direction
comma
id|mapped_alloc_size
)paren
suffix:semicolon
id|busptr
op_assign
id|virt_to_bus
c_func
(paren
id|virtptr
)paren
suffix:semicolon
multiline_comment|/* we assume here that a buffer will never be &gt;=64k */
r_if
c_cond
(paren
(paren
(paren
(paren
r_int
r_int
)paren
id|busptr
)paren
op_amp
l_int|0x100000
)paren
op_logical_or
(paren
(paren
(paren
(paren
r_int
r_int
)paren
id|busptr
)paren
op_plus
id|size
)paren
op_amp
l_int|0x100000
)paren
)paren
(brace
r_char
op_star
id|safe
suffix:semicolon
id|safe
op_assign
id|alloc_safe_buffer
c_func
(paren
id|virtptr
comma
id|size
comma
op_amp
id|busptr
)paren
suffix:semicolon
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
l_string|&quot;unable to map unsafe buffer %p!&bslash;n&quot;
comma
id|virtptr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;unsafe buffer %p (phy=%p) mapped to %p (phy=%p)&bslash;n&quot;
comma
id|virtptr
comma
(paren
r_void
op_star
)paren
id|virt_to_bus
c_func
(paren
id|virtptr
)paren
comma
id|safe
comma
(paren
r_void
op_star
)paren
id|busptr
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|safe
comma
id|virtptr
comma
id|size
)paren
suffix:semicolon
id|consistent_sync
c_func
(paren
id|safe
comma
id|size
comma
id|direction
)paren
suffix:semicolon
r_return
id|busptr
suffix:semicolon
)brace
id|consistent_sync
c_func
(paren
id|virtptr
comma
id|size
comma
id|direction
)paren
suffix:semicolon
r_return
id|busptr
suffix:semicolon
)brace
multiline_comment|/*&n; * see if a mapped address was really a &quot;safe&quot; buffer and if so,&n; * copy the data from the safe buffer back to the unsafe buffer&n; * and free up the safe buffer.&n; * (basically return things back to the way they should be)&n; */
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
r_char
op_star
id|safe
comma
op_star
id|unsafe
suffix:semicolon
r_void
op_star
id|buf
suffix:semicolon
multiline_comment|/* hack; usb-ohci.c never sends hwdev==NULL, all others do */
r_if
c_cond
(paren
id|hwdev
op_eq
l_int|NULL
)paren
(brace
r_return
suffix:semicolon
)brace
id|mapped_alloc_size
op_sub_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;pci_unmap_single(hwdev=%p,ptr=%p,size=%d,dir=%x) &quot;
l_string|&quot;alloced=%ld&bslash;n&quot;
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
comma
id|mapped_alloc_size
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|safe
op_assign
id|find_safe_buffer
c_func
(paren
(paren
r_void
op_star
)paren
id|dma_addr
comma
op_amp
id|unsafe
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;copyback unsafe %p, safe %p, size %d&bslash;n&quot;
comma
id|unsafe
comma
id|safe
comma
id|size
)paren
suffix:semicolon
id|consistent_sync
c_func
(paren
id|safe
comma
id|size
comma
id|PCI_DMA_FROMDEVICE
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|unsafe
comma
id|safe
comma
id|size
)paren
suffix:semicolon
id|free_safe_buffer
c_func
(paren
id|safe
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* assume this is normal memory */
id|buf
op_assign
id|bus_to_virt
c_func
(paren
id|dma_addr
)paren
suffix:semicolon
id|consistent_sync
c_func
(paren
id|buf
comma
id|size
comma
id|PCI_DMA_FROMDEVICE
)paren
suffix:semicolon
)brace
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
DECL|function|sa1111_init_safe_buffers
r_static
r_int
id|__init
id|sa1111_init_safe_buffers
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Initializing SA1111 buffer pool for DMA workaround&bslash;n&quot;
)paren
suffix:semicolon
id|init_safe_buffers
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|free_safe_buffers
r_static
r_void
id|free_safe_buffers
c_func
(paren
r_void
)paren
(brace
id|pci_pool_destroy
c_func
(paren
id|small_buffer_cache
)paren
suffix:semicolon
id|pci_pool_destroy
c_func
(paren
id|large_buffer_cache
)paren
suffix:semicolon
)brace
DECL|variable|sa1111_init_safe_buffers
id|module_init
c_func
(paren
id|sa1111_init_safe_buffers
)paren
suffix:semicolon
DECL|variable|free_safe_buffers
id|module_exit
c_func
(paren
id|free_safe_buffers
)paren
suffix:semicolon
eof
