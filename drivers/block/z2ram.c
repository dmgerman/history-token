multiline_comment|/*&n;** z2ram - Amiga pseudo-driver to access 16bit-RAM in ZorroII space&n;**         as a block device, to be used as a RAM disk or swap space&n;** &n;** Copyright (C) 1994 by Ingo Wilken (Ingo.Wilken@informatik.uni-oldenburg.de)&n;**&n;** ++Geert: support for zorro_unused_z2ram, better range checking&n;** ++roman: translate accesses via an array&n;** ++Milan: support for ChipRAM usage&n;** ++yambo: converted to 2.0 kernel&n;** ++yambo: modularized and support added for 3 minor devices including:&n;**          MAJOR  MINOR  DESCRIPTION&n;**          -----  -----  ----------------------------------------------&n;**          37     0       Use Zorro II and Chip ram&n;**          37     1       Use only Zorro II ram&n;**          37     2       Use only Chip ram&n;**          37     4-7     Use memory list entry 1-4 (first is 0)&n;** ++jskov: support for 1-4th memory list entry.&n;**&n;** Permission to use, copy, modify, and distribute this software and its&n;** documentation for any purpose and without fee is hereby granted, provided&n;** that the above copyright notice appear in all copies and that both that&n;** copyright notice and this permission notice appear in supporting&n;** documentation.  This software is provided &quot;as is&quot; without express or&n;** implied warranty.&n;*/
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR    Z2RAM_MAJOR
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/zorro.h&gt;
r_extern
r_int
id|m68k_realnum_memory
suffix:semicolon
r_extern
r_struct
id|mem_info
id|m68k_memory
(braket
id|NUM_MEMINFO
)braket
suffix:semicolon
DECL|macro|TRUE
mdefine_line|#define TRUE                  (1)
DECL|macro|FALSE
mdefine_line|#define FALSE                 (0)
DECL|macro|Z2MINOR_COMBINED
mdefine_line|#define Z2MINOR_COMBINED      (0)
DECL|macro|Z2MINOR_Z2ONLY
mdefine_line|#define Z2MINOR_Z2ONLY        (1)
DECL|macro|Z2MINOR_CHIPONLY
mdefine_line|#define Z2MINOR_CHIPONLY      (2)
DECL|macro|Z2MINOR_MEMLIST1
mdefine_line|#define Z2MINOR_MEMLIST1      (4)
DECL|macro|Z2MINOR_MEMLIST2
mdefine_line|#define Z2MINOR_MEMLIST2      (5)
DECL|macro|Z2MINOR_MEMLIST3
mdefine_line|#define Z2MINOR_MEMLIST3      (6)
DECL|macro|Z2MINOR_MEMLIST4
mdefine_line|#define Z2MINOR_MEMLIST4      (7)
DECL|macro|Z2MINOR_COUNT
mdefine_line|#define Z2MINOR_COUNT         (8) /* Move this down when adding a new minor */
DECL|macro|Z2RAM_CHUNK1024
mdefine_line|#define Z2RAM_CHUNK1024       ( Z2RAM_CHUNKSIZE &gt;&gt; 10 )
DECL|variable|z2ram_map
r_static
id|u_long
op_star
id|z2ram_map
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|z2ram_size
r_static
id|u_long
id|z2ram_size
op_assign
l_int|0
suffix:semicolon
DECL|variable|z2_sizes
r_static
r_int
id|z2_sizes
(braket
id|Z2MINOR_COUNT
)braket
suffix:semicolon
DECL|variable|z2_count
r_static
r_int
id|z2_count
op_assign
l_int|0
suffix:semicolon
DECL|variable|chip_count
r_static
r_int
id|chip_count
op_assign
l_int|0
suffix:semicolon
DECL|variable|list_count
r_static
r_int
id|list_count
op_assign
l_int|0
suffix:semicolon
DECL|variable|current_device
r_static
r_int
id|current_device
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|z2ram_lock
r_static
id|spinlock_t
id|z2ram_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_static
r_void
DECL|function|do_z2_request
id|do_z2_request
c_func
(paren
id|request_queue_t
op_star
id|q
)paren
(brace
id|u_long
id|start
comma
id|len
comma
id|addr
comma
id|size
suffix:semicolon
r_while
c_loop
(paren
id|TRUE
)paren
(brace
id|INIT_REQUEST
suffix:semicolon
id|start
op_assign
id|CURRENT-&gt;sector
op_lshift
l_int|9
suffix:semicolon
id|len
op_assign
id|CURRENT-&gt;current_nr_sectors
op_lshift
l_int|9
suffix:semicolon
r_if
c_cond
(paren
(paren
id|start
op_plus
id|len
)paren
OG
id|z2ram_size
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|DEVICE_NAME
l_string|&quot;: bad access: block=%ld, count=%ld&bslash;n&quot;
comma
id|CURRENT-&gt;sector
comma
id|CURRENT-&gt;current_nr_sectors
)paren
suffix:semicolon
id|end_request
c_func
(paren
id|FALSE
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|CURRENT-&gt;cmd
op_ne
id|READ
)paren
op_logical_and
(paren
id|CURRENT-&gt;cmd
op_ne
id|WRITE
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|DEVICE_NAME
l_string|&quot;: bad command: %d&bslash;n&quot;
comma
id|CURRENT-&gt;cmd
)paren
suffix:semicolon
id|end_request
c_func
(paren
id|FALSE
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
)paren
(brace
id|addr
op_assign
id|start
op_amp
id|Z2RAM_CHUNKMASK
suffix:semicolon
id|size
op_assign
id|Z2RAM_CHUNKSIZE
op_minus
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|size
)paren
id|size
op_assign
id|len
suffix:semicolon
id|addr
op_add_assign
id|z2ram_map
(braket
id|start
op_rshift
id|Z2RAM_CHUNKSHIFT
)braket
suffix:semicolon
r_if
c_cond
(paren
id|CURRENT-&gt;cmd
op_eq
id|READ
)paren
id|memcpy
c_func
(paren
id|CURRENT-&gt;buffer
comma
(paren
r_char
op_star
)paren
id|addr
comma
id|size
)paren
suffix:semicolon
r_else
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|addr
comma
id|CURRENT-&gt;buffer
comma
id|size
)paren
suffix:semicolon
id|start
op_add_assign
id|size
suffix:semicolon
id|len
op_sub_assign
id|size
suffix:semicolon
)brace
id|end_request
c_func
(paren
id|TRUE
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|get_z2ram
id|get_z2ram
c_func
(paren
r_void
)paren
(brace
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
id|Z2RAM_SIZE
op_div
id|Z2RAM_CHUNKSIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|i
comma
id|zorro_unused_z2ram
)paren
)paren
(brace
id|z2_count
op_increment
suffix:semicolon
id|z2ram_map
(braket
id|z2ram_size
op_increment
)braket
op_assign
id|ZTWO_VADDR
c_func
(paren
id|Z2RAM_START
)paren
op_plus
(paren
id|i
op_lshift
id|Z2RAM_CHUNKSHIFT
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|i
comma
id|zorro_unused_z2ram
)paren
suffix:semicolon
)brace
)brace
r_return
suffix:semicolon
)brace
r_static
r_void
DECL|function|get_chipram
id|get_chipram
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
id|amiga_chip_avail
c_func
(paren
)paren
OG
(paren
id|Z2RAM_CHUNKSIZE
op_star
l_int|4
)paren
)paren
(brace
id|chip_count
op_increment
suffix:semicolon
id|z2ram_map
(braket
id|z2ram_size
)braket
op_assign
(paren
id|u_long
)paren
id|amiga_chip_alloc
c_func
(paren
id|Z2RAM_CHUNKSIZE
comma
l_string|&quot;z2ram&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|z2ram_map
(braket
id|z2ram_size
)braket
op_eq
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
id|z2ram_size
op_increment
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
r_static
r_int
DECL|function|z2_open
id|z2_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_int
id|device
suffix:semicolon
r_int
id|max_z2_map
op_assign
(paren
id|Z2RAM_SIZE
op_div
id|Z2RAM_CHUNKSIZE
)paren
op_star
r_sizeof
(paren
id|z2ram_map
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_int
id|max_chip_map
op_assign
(paren
id|amiga_chip_size
op_div
id|Z2RAM_CHUNKSIZE
)paren
op_star
r_sizeof
(paren
id|z2ram_map
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_int
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|device
op_assign
id|DEVICE_NR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current_device
op_ne
op_minus
l_int|1
op_logical_and
id|current_device
op_ne
id|device
)paren
(brace
id|rc
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|current_device
op_eq
op_minus
l_int|1
)paren
(brace
id|z2_count
op_assign
l_int|0
suffix:semicolon
id|chip_count
op_assign
l_int|0
suffix:semicolon
id|list_count
op_assign
l_int|0
suffix:semicolon
id|z2ram_size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Use a specific list entry. */
r_if
c_cond
(paren
id|device
op_ge
id|Z2MINOR_MEMLIST1
op_logical_and
id|device
op_le
id|Z2MINOR_MEMLIST4
)paren
(brace
r_int
id|index
op_assign
id|device
op_minus
id|Z2MINOR_MEMLIST1
op_plus
l_int|1
suffix:semicolon
r_int
r_int
id|size
comma
id|paddr
comma
id|vaddr
suffix:semicolon
r_if
c_cond
(paren
id|index
op_ge
id|m68k_realnum_memory
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|DEVICE_NAME
l_string|&quot;: no such entry in z2ram_map&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
id|paddr
op_assign
id|m68k_memory
(braket
id|index
)braket
dot
id|addr
suffix:semicolon
id|size
op_assign
id|m68k_memory
(braket
id|index
)braket
dot
id|size
op_amp
op_complement
(paren
id|Z2RAM_CHUNKSIZE
op_minus
l_int|1
)paren
suffix:semicolon
macro_line|#ifdef __powerpc__
multiline_comment|/* FIXME: ioremap doesn&squot;t build correct memory tables. */
(brace
id|vfree
c_func
(paren
id|vmalloc
(paren
id|size
)paren
)paren
suffix:semicolon
)brace
id|vaddr
op_assign
(paren
r_int
r_int
)paren
id|__ioremap
(paren
id|paddr
comma
id|size
comma
id|_PAGE_WRITETHRU
)paren
suffix:semicolon
macro_line|#else
id|vaddr
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|paddr
comma
id|size
)paren
suffix:semicolon
macro_line|#endif
id|z2ram_map
op_assign
id|kmalloc
c_func
(paren
(paren
id|size
op_div
id|Z2RAM_CHUNKSIZE
)paren
op_star
r_sizeof
(paren
id|z2ram_map
(braket
l_int|0
)braket
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|z2ram_map
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|DEVICE_NAME
l_string|&quot;: cannot get mem for z2ram_map&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
)paren
(brace
id|z2ram_map
(braket
id|z2ram_size
op_increment
)braket
op_assign
id|vaddr
suffix:semicolon
id|size
op_sub_assign
id|Z2RAM_CHUNKSIZE
suffix:semicolon
id|vaddr
op_add_assign
id|Z2RAM_CHUNKSIZE
suffix:semicolon
id|list_count
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|z2ram_size
op_ne
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
id|DEVICE_NAME
l_string|&quot;: using %iK List Entry %d Memory&bslash;n&quot;
comma
id|list_count
op_star
id|Z2RAM_CHUNK1024
comma
id|index
)paren
suffix:semicolon
)brace
r_else
r_switch
c_cond
(paren
id|device
)paren
(brace
r_case
id|Z2MINOR_COMBINED
suffix:colon
id|z2ram_map
op_assign
id|kmalloc
c_func
(paren
id|max_z2_map
op_plus
id|max_chip_map
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|z2ram_map
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|DEVICE_NAME
l_string|&quot;: cannot get mem for z2ram_map&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
id|get_z2ram
c_func
(paren
)paren
suffix:semicolon
id|get_chipram
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|z2ram_size
op_ne
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
id|DEVICE_NAME
l_string|&quot;: using %iK Zorro II RAM and %iK Chip RAM (Total %dK)&bslash;n&quot;
comma
id|z2_count
op_star
id|Z2RAM_CHUNK1024
comma
id|chip_count
op_star
id|Z2RAM_CHUNK1024
comma
(paren
id|z2_count
op_plus
id|chip_count
)paren
op_star
id|Z2RAM_CHUNK1024
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Z2MINOR_Z2ONLY
suffix:colon
id|z2ram_map
op_assign
id|kmalloc
c_func
(paren
id|max_z2_map
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|z2ram_map
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|DEVICE_NAME
l_string|&quot;: cannot get mem for z2ram_map&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
id|get_z2ram
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|z2ram_size
op_ne
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
id|DEVICE_NAME
l_string|&quot;: using %iK of Zorro II RAM&bslash;n&quot;
comma
id|z2_count
op_star
id|Z2RAM_CHUNK1024
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|Z2MINOR_CHIPONLY
suffix:colon
id|z2ram_map
op_assign
id|kmalloc
c_func
(paren
id|max_chip_map
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|z2ram_map
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|DEVICE_NAME
l_string|&quot;: cannot get mem for z2ram_map&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
id|get_chipram
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|z2ram_size
op_ne
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
id|DEVICE_NAME
l_string|&quot;: using %iK Chip RAM&bslash;n&quot;
comma
id|chip_count
op_star
id|Z2RAM_CHUNK1024
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|z2ram_size
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
id|DEVICE_NAME
l_string|&quot;: no unused ZII/Chip RAM found&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_out_kfree
suffix:semicolon
)brace
id|current_device
op_assign
id|device
suffix:semicolon
id|z2ram_size
op_lshift_assign
id|Z2RAM_CHUNKSHIFT
suffix:semicolon
id|z2_sizes
(braket
id|device
)braket
op_assign
id|z2ram_size
op_rshift
l_int|10
suffix:semicolon
id|blk_size
(braket
id|MAJOR_NR
)braket
op_assign
id|z2_sizes
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|err_out_kfree
suffix:colon
id|kfree
c_func
(paren
id|z2ram_map
)paren
suffix:semicolon
id|err_out
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
r_static
r_int
DECL|function|z2_release
id|z2_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_if
c_cond
(paren
id|current_device
op_eq
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;     * FIXME: unmap memory&n;     */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|z2_fops
r_static
r_struct
id|block_device_operations
id|z2_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|open
suffix:colon
id|z2_open
comma
id|release
suffix:colon
id|z2_release
comma
)brace
suffix:semicolon
r_int
id|__init
DECL|function|z2_init
id|z2_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_AMIGA
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|register_blkdev
c_func
(paren
id|MAJOR_NR
comma
id|DEVICE_NAME
comma
op_amp
id|z2_fops
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|DEVICE_NAME
l_string|&quot;: Unable to get major %d&bslash;n&quot;
comma
id|MAJOR_NR
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
(brace
multiline_comment|/* Initialize size arrays. */
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
id|Z2MINOR_COUNT
suffix:semicolon
id|i
op_increment
)paren
(brace
id|z2_sizes
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|blk_init_queue
c_func
(paren
id|BLK_DEFAULT_QUEUE
c_func
(paren
id|MAJOR_NR
)paren
comma
id|DEVICE_REQUEST
comma
op_amp
id|z2ram_lock
)paren
suffix:semicolon
id|blk_size
(braket
id|MAJOR_NR
)braket
op_assign
id|z2_sizes
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if defined(MODULE)
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
r_int
DECL|function|init_module
id|init_module
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
id|error
op_assign
id|z2_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|DEVICE_NAME
l_string|&quot;: loaded as module&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
r_void
DECL|function|cleanup_module
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
id|unregister_blkdev
c_func
(paren
id|MAJOR_NR
comma
id|DEVICE_NAME
)paren
op_ne
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
id|DEVICE_NAME
l_string|&quot;: unregister of device failed&bslash;n&quot;
)paren
suffix:semicolon
id|blk_cleanup_queue
c_func
(paren
id|BLK_DEFAULT_QUEUE
c_func
(paren
id|MAJOR_NR
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current_device
op_ne
op_minus
l_int|1
)paren
(brace
id|i
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|z2_count
suffix:semicolon
id|j
op_increment
)paren
(brace
id|set_bit
c_func
(paren
id|i
op_increment
comma
id|zorro_unused_z2ram
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|chip_count
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|z2ram_map
(braket
id|i
)braket
)paren
(brace
id|amiga_chip_free
c_func
(paren
(paren
r_void
op_star
)paren
id|z2ram_map
(braket
id|i
op_increment
)braket
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|z2ram_map
op_ne
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|z2ram_map
)paren
suffix:semicolon
)brace
)brace
r_return
suffix:semicolon
)brace
macro_line|#endif
eof
