macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* Needed for i386 to build */
macro_line|#include &lt;asm/scatterlist.h&gt;&t;/* Needed for i386 to build */
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;linux/dmapool.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
multiline_comment|/*&n; * Pool allocator ... wraps the dma_alloc_coherent page allocator, so&n; * small blocks are easily used by drivers for bus mastering controllers.&n; * This should probably be sharing the guts of the slab allocator.&n; */
DECL|struct|dma_pool
r_struct
id|dma_pool
(brace
multiline_comment|/* the pool */
DECL|member|page_list
r_struct
id|list_head
id|page_list
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|blocks_per_page
r_int
id|blocks_per_page
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
DECL|member|allocation
r_int
id|allocation
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|waitq
id|wait_queue_head_t
id|waitq
suffix:semicolon
DECL|member|pools
r_struct
id|list_head
id|pools
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dma_page
r_struct
id|dma_page
(brace
multiline_comment|/* cacheable header for &squot;allocation&squot; bytes */
DECL|member|page_list
r_struct
id|list_head
id|page_list
suffix:semicolon
DECL|member|vaddr
r_void
op_star
id|vaddr
suffix:semicolon
DECL|member|dma
id|dma_addr_t
id|dma
suffix:semicolon
DECL|member|in_use
r_int
id|in_use
suffix:semicolon
DECL|member|bitmap
r_int
r_int
id|bitmap
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|POOL_TIMEOUT_JIFFIES
mdefine_line|#define&t;POOL_TIMEOUT_JIFFIES&t;((100 /* msec */ * HZ) / 1000)
DECL|macro|POOL_POISON_FREED
mdefine_line|#define&t;POOL_POISON_FREED&t;0xa7&t;/* !inuse */
DECL|macro|POOL_POISON_ALLOCATED
mdefine_line|#define&t;POOL_POISON_ALLOCATED&t;0xa9&t;/* !initted */
r_static
id|DECLARE_MUTEX
(paren
id|pools_lock
)paren
suffix:semicolon
r_static
id|ssize_t
DECL|function|show_pools
id|show_pools
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_int
id|temp
comma
id|size
suffix:semicolon
r_char
op_star
id|next
suffix:semicolon
r_struct
id|list_head
op_star
id|i
comma
op_star
id|j
suffix:semicolon
id|next
op_assign
id|buf
suffix:semicolon
id|size
op_assign
id|PAGE_SIZE
suffix:semicolon
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot;poolinfo - 0.1&bslash;n&quot;
)paren
suffix:semicolon
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
suffix:semicolon
id|down
(paren
op_amp
id|pools_lock
)paren
suffix:semicolon
id|list_for_each
(paren
id|i
comma
op_amp
id|dev-&gt;dma_pools
)paren
(brace
r_struct
id|dma_pool
op_star
id|pool
suffix:semicolon
r_int
id|pages
op_assign
l_int|0
comma
id|blocks
op_assign
l_int|0
suffix:semicolon
id|pool
op_assign
id|list_entry
(paren
id|i
comma
r_struct
id|dma_pool
comma
id|pools
)paren
suffix:semicolon
id|list_for_each
(paren
id|j
comma
op_amp
id|pool-&gt;page_list
)paren
(brace
r_struct
id|dma_page
op_star
id|page
suffix:semicolon
id|page
op_assign
id|list_entry
(paren
id|j
comma
r_struct
id|dma_page
comma
id|page_list
)paren
suffix:semicolon
id|pages
op_increment
suffix:semicolon
id|blocks
op_add_assign
id|page-&gt;in_use
suffix:semicolon
)brace
multiline_comment|/* per-pool info, no real statistics yet */
id|temp
op_assign
id|snprintf
(paren
id|next
comma
id|size
comma
l_string|&quot;%-16s %4u %4Zu %4Zu %2u&bslash;n&quot;
comma
id|pool-&gt;name
comma
id|blocks
comma
id|pages
op_star
id|pool-&gt;blocks_per_page
comma
id|pool-&gt;size
comma
id|pages
)paren
suffix:semicolon
id|size
op_sub_assign
id|temp
suffix:semicolon
id|next
op_add_assign
id|temp
suffix:semicolon
)brace
id|up
(paren
op_amp
id|pools_lock
)paren
suffix:semicolon
r_return
id|PAGE_SIZE
op_minus
id|size
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
(paren
id|pools
comma
id|S_IRUGO
comma
id|show_pools
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/**&n; * dma_pool_create - Creates a pool of consistent memory blocks, for dma.&n; * @name: name of pool, for diagnostics&n; * @dev: device that will be doing the DMA&n; * @size: size of the blocks in this pool.&n; * @align: alignment requirement for blocks; must be a power of two&n; * @allocation: returned blocks won&squot;t cross this boundary (or zero)&n; * Context: !in_interrupt()&n; *&n; * Returns a dma allocation pool with the requested characteristics, or&n; * null if one can&squot;t be created.  Given one of these pools, dma_pool_alloc()&n; * may be used to allocate memory.  Such memory will all have &quot;consistent&quot;&n; * DMA mappings, accessible by the device and its driver without using&n; * cache flushing primitives.  The actual size of blocks allocated may be&n; * larger than requested because of alignment.&n; *&n; * If allocation is nonzero, objects returned from dma_pool_alloc() won&squot;t&n; * cross that size boundary.  This is useful for devices which have&n; * addressing restrictions on individual DMA transfers, such as not crossing&n; * boundaries of 4KBytes.&n; */
r_struct
id|dma_pool
op_star
DECL|function|dma_pool_create
id|dma_pool_create
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|device
op_star
id|dev
comma
r_int
id|size
comma
r_int
id|align
comma
r_int
id|allocation
)paren
(brace
r_struct
id|dma_pool
op_star
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|align
op_eq
l_int|0
)paren
id|align
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|size
OL
id|align
)paren
id|size
op_assign
id|align
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|size
op_mod
id|align
)paren
op_ne
l_int|0
)paren
(brace
id|size
op_add_assign
id|align
op_plus
l_int|1
suffix:semicolon
id|size
op_and_assign
op_complement
(paren
id|align
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|allocation
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|PAGE_SIZE
OL
id|size
)paren
id|allocation
op_assign
id|size
suffix:semicolon
r_else
id|allocation
op_assign
id|PAGE_SIZE
suffix:semicolon
singleline_comment|// FIXME: round up for less fragmentation
)brace
r_else
r_if
c_cond
(paren
id|allocation
OL
id|size
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|retval
op_assign
id|kmalloc
(paren
r_sizeof
op_star
id|retval
comma
id|SLAB_KERNEL
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
id|strlcpy
(paren
id|retval-&gt;name
comma
id|name
comma
r_sizeof
id|retval-&gt;name
)paren
suffix:semicolon
id|retval-&gt;dev
op_assign
id|dev
suffix:semicolon
id|INIT_LIST_HEAD
(paren
op_amp
id|retval-&gt;page_list
)paren
suffix:semicolon
id|spin_lock_init
(paren
op_amp
id|retval-&gt;lock
)paren
suffix:semicolon
id|retval-&gt;size
op_assign
id|size
suffix:semicolon
id|retval-&gt;allocation
op_assign
id|allocation
suffix:semicolon
id|retval-&gt;blocks_per_page
op_assign
id|allocation
op_div
id|size
suffix:semicolon
id|init_waitqueue_head
(paren
op_amp
id|retval-&gt;waitq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
id|down
(paren
op_amp
id|pools_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
(paren
op_amp
id|dev-&gt;dma_pools
)paren
)paren
id|device_create_file
(paren
id|dev
comma
op_amp
id|dev_attr_pools
)paren
suffix:semicolon
multiline_comment|/* note:  not currently insisting &quot;name&quot; be unique */
id|list_add
(paren
op_amp
id|retval-&gt;pools
comma
op_amp
id|dev-&gt;dma_pools
)paren
suffix:semicolon
id|up
(paren
op_amp
id|pools_lock
)paren
suffix:semicolon
)brace
r_else
id|INIT_LIST_HEAD
(paren
op_amp
id|retval-&gt;pools
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_static
r_struct
id|dma_page
op_star
DECL|function|pool_alloc_page
id|pool_alloc_page
(paren
r_struct
id|dma_pool
op_star
id|pool
comma
r_int
id|mem_flags
)paren
(brace
r_struct
id|dma_page
op_star
id|page
suffix:semicolon
r_int
id|mapsize
suffix:semicolon
id|mapsize
op_assign
id|pool-&gt;blocks_per_page
suffix:semicolon
id|mapsize
op_assign
(paren
id|mapsize
op_plus
id|BITS_PER_LONG
op_minus
l_int|1
)paren
op_div
id|BITS_PER_LONG
suffix:semicolon
id|mapsize
op_mul_assign
r_sizeof
(paren
r_int
)paren
suffix:semicolon
id|page
op_assign
(paren
r_struct
id|dma_page
op_star
)paren
id|kmalloc
(paren
id|mapsize
op_plus
r_sizeof
op_star
id|page
comma
id|mem_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
l_int|0
suffix:semicolon
id|page-&gt;vaddr
op_assign
id|dma_alloc_coherent
(paren
id|pool-&gt;dev
comma
id|pool-&gt;allocation
comma
op_amp
id|page-&gt;dma
comma
id|mem_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;vaddr
)paren
(brace
id|memset
(paren
id|page-&gt;bitmap
comma
l_int|0xff
comma
id|mapsize
)paren
suffix:semicolon
singleline_comment|// bit set == free
macro_line|#ifdef&t;CONFIG_DEBUG_SLAB
id|memset
(paren
id|page-&gt;vaddr
comma
id|POOL_POISON_FREED
comma
id|pool-&gt;allocation
)paren
suffix:semicolon
macro_line|#endif
id|list_add
(paren
op_amp
id|page-&gt;page_list
comma
op_amp
id|pool-&gt;page_list
)paren
suffix:semicolon
id|page-&gt;in_use
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|kfree
(paren
id|page
)paren
suffix:semicolon
id|page
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|page
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|is_page_busy
id|is_page_busy
(paren
r_int
id|blocks
comma
r_int
r_int
op_star
id|bitmap
)paren
(brace
r_while
c_loop
(paren
id|blocks
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_star
id|bitmap
op_increment
op_ne
op_complement
l_int|0UL
)paren
r_return
l_int|1
suffix:semicolon
id|blocks
op_sub_assign
id|BITS_PER_LONG
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|pool_free_page
id|pool_free_page
(paren
r_struct
id|dma_pool
op_star
id|pool
comma
r_struct
id|dma_page
op_star
id|page
)paren
(brace
id|dma_addr_t
id|dma
op_assign
id|page-&gt;dma
suffix:semicolon
macro_line|#ifdef&t;CONFIG_DEBUG_SLAB
id|memset
(paren
id|page-&gt;vaddr
comma
id|POOL_POISON_FREED
comma
id|pool-&gt;allocation
)paren
suffix:semicolon
macro_line|#endif
id|dma_free_coherent
(paren
id|pool-&gt;dev
comma
id|pool-&gt;allocation
comma
id|page-&gt;vaddr
comma
id|dma
)paren
suffix:semicolon
id|list_del
(paren
op_amp
id|page-&gt;page_list
)paren
suffix:semicolon
id|kfree
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * dma_pool_destroy - destroys a pool of dma memory blocks.&n; * @pool: dma pool that will be destroyed&n; * Context: !in_interrupt()&n; *&n; * Caller guarantees that no more memory from the pool is in use,&n; * and that nothing will try to use the pool after this call.&n; */
r_void
DECL|function|dma_pool_destroy
id|dma_pool_destroy
(paren
r_struct
id|dma_pool
op_star
id|pool
)paren
(brace
id|down
(paren
op_amp
id|pools_lock
)paren
suffix:semicolon
id|list_del
(paren
op_amp
id|pool-&gt;pools
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pool-&gt;dev
op_logical_and
id|list_empty
(paren
op_amp
id|pool-&gt;dev-&gt;dma_pools
)paren
)paren
id|device_remove_file
(paren
id|pool-&gt;dev
comma
op_amp
id|dev_attr_pools
)paren
suffix:semicolon
id|up
(paren
op_amp
id|pools_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
(paren
op_amp
id|pool-&gt;page_list
)paren
)paren
(brace
r_struct
id|dma_page
op_star
id|page
suffix:semicolon
id|page
op_assign
id|list_entry
(paren
id|pool-&gt;page_list.next
comma
r_struct
id|dma_page
comma
id|page_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_page_busy
(paren
id|pool-&gt;blocks_per_page
comma
id|page-&gt;bitmap
)paren
)paren
(brace
r_if
c_cond
(paren
id|pool-&gt;dev
)paren
id|dev_err
c_func
(paren
id|pool-&gt;dev
comma
l_string|&quot;dma_pool_destroy %s, %p busy&bslash;n&quot;
comma
id|pool-&gt;name
comma
id|page-&gt;vaddr
)paren
suffix:semicolon
r_else
id|printk
(paren
id|KERN_ERR
l_string|&quot;dma_pool_destroy %s, %p busy&bslash;n&quot;
comma
id|pool-&gt;name
comma
id|page-&gt;vaddr
)paren
suffix:semicolon
multiline_comment|/* leak the still-in-use consistent memory */
id|list_del
(paren
op_amp
id|page-&gt;page_list
)paren
suffix:semicolon
id|kfree
(paren
id|page
)paren
suffix:semicolon
)brace
r_else
id|pool_free_page
(paren
id|pool
comma
id|page
)paren
suffix:semicolon
)brace
id|kfree
(paren
id|pool
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * dma_pool_alloc - get a block of consistent memory&n; * @pool: dma pool that will produce the block&n; * @mem_flags: GFP_* bitmask&n; * @handle: pointer to dma address of block&n; *&n; * This returns the kernel virtual address of a currently unused block,&n; * and reports its dma address through the handle.&n; * If such a memory block can&squot;t be allocated, null is returned.&n; */
r_void
op_star
DECL|function|dma_pool_alloc
id|dma_pool_alloc
(paren
r_struct
id|dma_pool
op_star
id|pool
comma
r_int
id|mem_flags
comma
id|dma_addr_t
op_star
id|handle
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_struct
id|dma_page
op_star
id|page
suffix:semicolon
r_int
id|map
comma
id|block
suffix:semicolon
r_int
id|offset
suffix:semicolon
r_void
op_star
id|retval
suffix:semicolon
id|restart
suffix:colon
id|spin_lock_irqsave
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each
(paren
id|entry
comma
op_amp
id|pool-&gt;page_list
)paren
(brace
r_int
id|i
suffix:semicolon
id|page
op_assign
id|list_entry
(paren
id|entry
comma
r_struct
id|dma_page
comma
id|page_list
)paren
suffix:semicolon
multiline_comment|/* only cachable accesses here ... */
r_for
c_loop
(paren
id|map
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|pool-&gt;blocks_per_page
suffix:semicolon
id|i
op_add_assign
id|BITS_PER_LONG
comma
id|map
op_increment
)paren
(brace
r_if
c_cond
(paren
id|page-&gt;bitmap
(braket
id|map
)braket
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|block
op_assign
id|ffz
(paren
op_complement
id|page-&gt;bitmap
(braket
id|map
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_plus
id|block
)paren
OL
id|pool-&gt;blocks_per_page
)paren
(brace
id|clear_bit
(paren
id|block
comma
op_amp
id|page-&gt;bitmap
(braket
id|map
)braket
)paren
suffix:semicolon
id|offset
op_assign
(paren
id|BITS_PER_LONG
op_star
id|map
)paren
op_plus
id|block
suffix:semicolon
id|offset
op_mul_assign
id|pool-&gt;size
suffix:semicolon
r_goto
id|ready
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_assign
id|pool_alloc_page
(paren
id|pool
comma
id|SLAB_ATOMIC
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|mem_flags
op_amp
id|__GFP_WAIT
)paren
(brace
id|DECLARE_WAITQUEUE
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|add_wait_queue
(paren
op_amp
id|pool-&gt;waitq
comma
op_amp
id|wait
)paren
suffix:semicolon
id|spin_unlock_irqrestore
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|schedule_timeout
(paren
id|POOL_TIMEOUT_JIFFIES
)paren
suffix:semicolon
id|remove_wait_queue
(paren
op_amp
id|pool-&gt;waitq
comma
op_amp
id|wait
)paren
suffix:semicolon
r_goto
id|restart
suffix:semicolon
)brace
id|retval
op_assign
l_int|0
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|clear_bit
(paren
l_int|0
comma
op_amp
id|page-&gt;bitmap
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
id|ready
suffix:colon
id|page-&gt;in_use
op_increment
suffix:semicolon
id|retval
op_assign
id|offset
op_plus
id|page-&gt;vaddr
suffix:semicolon
op_star
id|handle
op_assign
id|offset
op_plus
id|page-&gt;dma
suffix:semicolon
macro_line|#ifdef&t;CONFIG_DEBUG_SLAB
id|memset
(paren
id|retval
comma
id|POOL_POISON_ALLOCATED
comma
id|pool-&gt;size
)paren
suffix:semicolon
macro_line|#endif
id|done
suffix:colon
id|spin_unlock_irqrestore
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_static
r_struct
id|dma_page
op_star
DECL|function|pool_find_page
id|pool_find_page
(paren
r_struct
id|dma_pool
op_star
id|pool
comma
id|dma_addr_t
id|dma
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_struct
id|dma_page
op_star
id|page
suffix:semicolon
id|spin_lock_irqsave
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each
(paren
id|entry
comma
op_amp
id|pool-&gt;page_list
)paren
(brace
id|page
op_assign
id|list_entry
(paren
id|entry
comma
r_struct
id|dma_page
comma
id|page_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma
OL
id|page-&gt;dma
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|dma
OL
(paren
id|page-&gt;dma
op_plus
id|pool-&gt;allocation
)paren
)paren
r_goto
id|done
suffix:semicolon
)brace
id|page
op_assign
l_int|0
suffix:semicolon
id|done
suffix:colon
id|spin_unlock_irqrestore
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
multiline_comment|/**&n; * dma_pool_free - put block back into dma pool&n; * @pool: the dma pool holding the block&n; * @vaddr: virtual address of block&n; * @dma: dma address of block&n; *&n; * Caller promises neither device nor driver will again touch this block&n; * unless it is first re-allocated.&n; */
r_void
DECL|function|dma_pool_free
id|dma_pool_free
(paren
r_struct
id|dma_pool
op_star
id|pool
comma
r_void
op_star
id|vaddr
comma
id|dma_addr_t
id|dma
)paren
(brace
r_struct
id|dma_page
op_star
id|page
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|map
comma
id|block
suffix:semicolon
r_if
c_cond
(paren
(paren
id|page
op_assign
id|pool_find_page
(paren
id|pool
comma
id|dma
)paren
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|pool-&gt;dev
)paren
id|dev_err
c_func
(paren
id|pool-&gt;dev
comma
l_string|&quot;dma_pool_free %s, %p/%lx (bad dma)&bslash;n&quot;
comma
id|pool-&gt;name
comma
id|vaddr
comma
(paren
r_int
r_int
)paren
id|dma
)paren
suffix:semicolon
r_else
id|printk
(paren
id|KERN_ERR
l_string|&quot;dma_pool_free %s, %p/%lx (bad dma)&bslash;n&quot;
comma
id|pool-&gt;name
comma
id|vaddr
comma
(paren
r_int
r_int
)paren
id|dma
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|block
op_assign
id|dma
op_minus
id|page-&gt;dma
suffix:semicolon
id|block
op_div_assign
id|pool-&gt;size
suffix:semicolon
id|map
op_assign
id|block
op_div
id|BITS_PER_LONG
suffix:semicolon
id|block
op_mod_assign
id|BITS_PER_LONG
suffix:semicolon
macro_line|#ifdef&t;CONFIG_DEBUG_SLAB
r_if
c_cond
(paren
(paren
(paren
id|dma
op_minus
id|page-&gt;dma
)paren
op_plus
(paren
r_void
op_star
)paren
id|page-&gt;vaddr
)paren
op_ne
id|vaddr
)paren
(brace
r_if
c_cond
(paren
id|pool-&gt;dev
)paren
id|dev_err
c_func
(paren
id|pool-&gt;dev
comma
l_string|&quot;dma_pool_free %s, %p (bad vaddr)/%Lx&bslash;n&quot;
comma
id|pool-&gt;name
comma
id|vaddr
comma
(paren
r_int
r_int
r_int
)paren
id|dma
)paren
suffix:semicolon
r_else
id|printk
(paren
id|KERN_ERR
l_string|&quot;dma_pool_free %s, %p (bad vaddr)/%Lx&bslash;n&quot;
comma
id|pool-&gt;name
comma
id|vaddr
comma
(paren
r_int
r_int
r_int
)paren
id|dma
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|page-&gt;bitmap
(braket
id|map
)braket
op_amp
(paren
l_int|1UL
op_lshift
id|block
)paren
)paren
(brace
r_if
c_cond
(paren
id|pool-&gt;dev
)paren
id|dev_err
c_func
(paren
id|pool-&gt;dev
comma
l_string|&quot;dma_pool_free %s, dma %Lx already free&bslash;n&quot;
comma
id|pool-&gt;name
comma
(paren
r_int
r_int
r_int
)paren
id|dma
)paren
suffix:semicolon
r_else
id|printk
(paren
id|KERN_ERR
l_string|&quot;dma_pool_free %s, dma %Lx already free&bslash;n&quot;
comma
id|pool-&gt;name
comma
(paren
r_int
r_int
r_int
)paren
id|dma
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memset
(paren
id|vaddr
comma
id|POOL_POISON_FREED
comma
id|pool-&gt;size
)paren
suffix:semicolon
macro_line|#endif
id|spin_lock_irqsave
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|page-&gt;in_use
op_decrement
suffix:semicolon
id|set_bit
(paren
id|block
comma
op_amp
id|page-&gt;bitmap
(braket
id|map
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|waitqueue_active
(paren
op_amp
id|pool-&gt;waitq
)paren
)paren
id|wake_up
(paren
op_amp
id|pool-&gt;waitq
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Resist a temptation to do&n;&t; *    if (!is_page_busy(bpp, page-&gt;bitmap)) pool_free_page(pool, page);&n;&t; * Better have a few empty pages hang around.&n;&t; */
id|spin_unlock_irqrestore
(paren
op_amp
id|pool-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|dma_pool_create
id|EXPORT_SYMBOL
(paren
id|dma_pool_create
)paren
suffix:semicolon
DECL|variable|dma_pool_destroy
id|EXPORT_SYMBOL
(paren
id|dma_pool_destroy
)paren
suffix:semicolon
DECL|variable|dma_pool_alloc
id|EXPORT_SYMBOL
(paren
id|dma_pool_alloc
)paren
suffix:semicolon
DECL|variable|dma_pool_free
id|EXPORT_SYMBOL
(paren
id|dma_pool_free
)paren
suffix:semicolon
eof
