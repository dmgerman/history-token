multiline_comment|/*&n; * ramdisk.c - Multiple RAM disk driver - gzip-loading version - v. 0.8 beta.&n; * &n; * (C) Chad Page, Theodore Ts&squot;o, et. al, 1995. &n; *&n; * This RAM disk is designed to have filesystems created on it and mounted&n; * just like a regular floppy disk.  &n; *  &n; * It also does something suggested by Linus: use the buffer cache as the&n; * RAM disk data.  This makes it possible to dynamically allocate the RAM disk&n; * buffer - with some consequences I have to deal with as I write this. &n; * &n; * This code is based on the original ramdisk.c, written mostly by&n; * Theodore Ts&squot;o (TYT) in 1991.  The code was largely rewritten by&n; * Chad Page to use the buffer cache to store the RAM disk data in&n; * 1995; Theodore then took over the driver again, and cleaned it up&n; * for inclusion in the mainline kernel.&n; *&n; * The original CRAMDISK code was written by Richard Lyons, and&n; * adapted by Chad Page to use the new RAM disk interface.  Theodore&n; * Ts&squot;o rewrote it so that both the compressed RAM disk loader and the&n; * kernel decompressor uses the same inflate.c codebase.  The RAM disk&n; * loader now also loads into a dynamic (buffer cache based) RAM disk,&n; * not the old static RAM disk.  Support for the old static RAM disk has&n; * been completely removed.&n; *&n; * Loadable module support added by Tom Dyas.&n; *&n; * Further cleanups by Chad Page (page0588@sundance.sjsu.edu):&n; *&t;Cosmetic changes in #ifdef MODULE, code movement, etc.&n; * &t;When the RAM disk module is removed, free the protected buffers&n; * &t;Default RAM disk size changed to 2.88 MB&n; *&n; *  Added initrd: Werner Almesberger &amp; Hans Lermen, Feb &squot;96&n; *&n; * 4/25/96 : Made RAM disk size a parameter (default is now 4 MB) &n; *&t;&t;- Chad Page&n; *&n; * Add support for fs images split across &gt;1 disk, Paul Gortmaker, Mar &squot;98&n; *&n; * Make block size and block size shift for RAM disks a global macro&n; * and set blk_size for -ENOSPC,     Werner Fink &lt;werner@suse.de&gt;, Apr &squot;99&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;&t;&t;/* for invalidate_bdev() */
macro_line|#include &lt;linux/backing-dev.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/blkpg.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* The RAM disk size is now a parameter */
DECL|macro|NUM_RAMDISKS
mdefine_line|#define NUM_RAMDISKS 16&t;&t;/* This cannot be overridden (yet) */ 
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
DECL|variable|initrd_users
r_static
r_int
id|initrd_users
suffix:semicolon
DECL|variable|initrd_users_lock
r_static
id|spinlock_t
id|initrd_users_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|initrd_start
DECL|variable|initrd_end
r_int
r_int
id|initrd_start
comma
id|initrd_end
suffix:semicolon
DECL|variable|initrd_below_start_ok
r_int
id|initrd_below_start_ok
suffix:semicolon
macro_line|#endif
multiline_comment|/* Various static variables go here.  Most are used only in the RAM disk code.&n; */
DECL|variable|rd_disks
r_static
r_struct
id|gendisk
op_star
id|rd_disks
(braket
id|NUM_RAMDISKS
)braket
suffix:semicolon
DECL|variable|rd_bdev
r_static
r_struct
id|block_device
op_star
id|rd_bdev
(braket
id|NUM_RAMDISKS
)braket
suffix:semicolon
multiline_comment|/* Protected device data */
multiline_comment|/*&n; * Parameters for the boot-loading of the RAM disk.  These are set by&n; * init/main.c (from arguments to the kernel command line) or from the&n; * architecture-specific setup routine (from the stored boot sector&n; * information). &n; */
DECL|variable|rd_size
r_int
id|rd_size
op_assign
id|CONFIG_BLK_DEV_RAM_SIZE
suffix:semicolon
multiline_comment|/* Size of the RAM disks */
multiline_comment|/*&n; * It would be very desirable to have a soft-blocksize (that in the case&n; * of the ramdisk driver is also the hardblocksize ;) of PAGE_SIZE because&n; * doing that we&squot;ll achieve a far better MM footprint. Using a rd_blocksize of&n; * BLOCK_SIZE in the worst case we&squot;ll make PAGE_SIZE/BLOCK_SIZE buffer-pages&n; * unfreeable. With a rd_blocksize of PAGE_SIZE instead we are sure that only&n; * 1 page will be protected. Depending on the size of the ramdisk you&n; * may want to change the ramdisk blocksize to achieve a better or worse MM&n; * behaviour. The default is still BLOCK_SIZE (needed by rd_load_image that&n; * supposes the filesystem in the image uses a BLOCK_SIZE blocksize).&n; */
DECL|variable|rd_blocksize
r_int
id|rd_blocksize
op_assign
id|BLOCK_SIZE
suffix:semicolon
multiline_comment|/* blocksize of the RAM disks */
multiline_comment|/*&n; * Copyright (C) 2000 Linus Torvalds.&n; *               2000 Transmeta Corp.&n; * aops copied from ramfs.&n; */
DECL|function|ramdisk_readpage
r_static
r_int
id|ramdisk_readpage
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|PageUptodate
c_func
(paren
id|page
)paren
)paren
(brace
r_void
op_star
id|kaddr
op_assign
id|kmap_atomic
c_func
(paren
id|page
comma
id|KM_USER0
)paren
suffix:semicolon
id|memset
c_func
(paren
id|kaddr
comma
l_int|0
comma
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|kaddr
comma
id|KM_USER0
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ramdisk_prepare_write
r_static
r_int
id|ramdisk_prepare_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
comma
r_int
id|offset
comma
r_int
id|to
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|PageUptodate
c_func
(paren
id|page
)paren
)paren
(brace
r_void
op_star
id|kaddr
op_assign
id|kmap_atomic
c_func
(paren
id|page
comma
id|KM_USER0
)paren
suffix:semicolon
id|memset
c_func
(paren
id|kaddr
comma
l_int|0
comma
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|kaddr
comma
id|KM_USER0
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|SetPageDirty
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ramdisk_commit_write
r_static
r_int
id|ramdisk_commit_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
comma
r_int
id|offset
comma
r_int
id|to
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ramdisk_aops
r_static
r_struct
id|address_space_operations
id|ramdisk_aops
op_assign
(brace
dot
id|readpage
op_assign
id|ramdisk_readpage
comma
dot
id|prepare_write
op_assign
id|ramdisk_prepare_write
comma
dot
id|commit_write
op_assign
id|ramdisk_commit_write
comma
)brace
suffix:semicolon
DECL|function|rd_blkdev_pagecache_IO
r_static
r_int
id|rd_blkdev_pagecache_IO
c_func
(paren
r_int
id|rw
comma
r_struct
id|bio_vec
op_star
id|vec
comma
id|sector_t
id|sector
comma
r_struct
id|address_space
op_star
id|mapping
)paren
(brace
r_int
r_int
id|index
op_assign
id|sector
op_rshift
(paren
id|PAGE_CACHE_SHIFT
op_minus
l_int|9
)paren
suffix:semicolon
r_int
r_int
id|vec_offset
op_assign
id|vec-&gt;bv_offset
suffix:semicolon
r_int
id|offset
op_assign
(paren
id|sector
op_lshift
l_int|9
)paren
op_amp
op_complement
id|PAGE_CACHE_MASK
suffix:semicolon
r_int
id|size
op_assign
id|vec-&gt;bv_len
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_int
id|count
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_char
op_star
id|src
comma
op_star
id|dst
suffix:semicolon
r_int
id|unlock
op_assign
l_int|0
suffix:semicolon
id|count
op_assign
id|PAGE_CACHE_SIZE
op_minus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|size
)paren
id|count
op_assign
id|size
suffix:semicolon
id|size
op_sub_assign
id|count
suffix:semicolon
id|page
op_assign
id|find_get_page
c_func
(paren
id|mapping
comma
id|index
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
(brace
id|page
op_assign
id|grab_cache_page
c_func
(paren
id|mapping
comma
id|index
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageUptodate
c_func
(paren
id|page
)paren
)paren
(brace
r_void
op_star
id|kaddr
op_assign
id|kmap_atomic
c_func
(paren
id|page
comma
id|KM_USER0
)paren
suffix:semicolon
id|memset
c_func
(paren
id|kaddr
comma
l_int|0
comma
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|kaddr
comma
id|KM_USER0
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
id|unlock
op_assign
l_int|1
suffix:semicolon
)brace
id|index
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|READ
)paren
(brace
id|src
op_assign
id|kmap
c_func
(paren
id|page
)paren
op_plus
id|offset
suffix:semicolon
id|dst
op_assign
id|kmap
c_func
(paren
id|vec-&gt;bv_page
)paren
op_plus
id|vec_offset
suffix:semicolon
)brace
r_else
(brace
id|dst
op_assign
id|kmap
c_func
(paren
id|page
)paren
op_plus
id|offset
suffix:semicolon
id|src
op_assign
id|kmap
c_func
(paren
id|vec-&gt;bv_page
)paren
op_plus
id|vec_offset
suffix:semicolon
)brace
id|offset
op_assign
l_int|0
suffix:semicolon
id|vec_offset
op_add_assign
id|count
suffix:semicolon
id|memcpy
c_func
(paren
id|dst
comma
id|src
comma
id|count
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|vec-&gt;bv_page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|READ
)paren
(brace
id|flush_dcache_page
c_func
(paren
id|vec-&gt;bv_page
)paren
suffix:semicolon
)brace
r_else
(brace
id|SetPageDirty
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|unlock
)paren
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; *  Basically, my strategy here is to set up a buffer-head which can&squot;t be&n; *  deleted, and make that my Ramdisk.  If the request is outside of the&n; *  allocated size, we must get rid of it...&n; *&n; * 19-JAN-1998  Richard Gooch &lt;rgooch@atnf.csiro.au&gt;  Added devfs support&n; *&n; */
DECL|function|rd_make_request
r_static
r_int
id|rd_make_request
c_func
(paren
id|request_queue_t
op_star
id|q
comma
r_struct
id|bio
op_star
id|bio
)paren
(brace
r_struct
id|block_device
op_star
id|bdev
op_assign
id|bio-&gt;bi_bdev
suffix:semicolon
r_struct
id|address_space
op_star
id|mapping
op_assign
id|bdev-&gt;bd_inode-&gt;i_mapping
suffix:semicolon
id|sector_t
id|sector
op_assign
id|bio-&gt;bi_sector
suffix:semicolon
r_int
r_int
id|len
op_assign
id|bio-&gt;bi_size
op_rshift
l_int|9
suffix:semicolon
r_int
id|rw
op_assign
id|bio_data_dir
c_func
(paren
id|bio
)paren
suffix:semicolon
r_struct
id|bio_vec
op_star
id|bvec
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
id|sector
op_plus
id|len
OG
id|get_capacity
c_func
(paren
id|bdev-&gt;bd_disk
)paren
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|READA
)paren
id|rw
op_assign
id|READ
suffix:semicolon
id|bio_for_each_segment
c_func
(paren
id|bvec
comma
id|bio
comma
id|i
)paren
(brace
id|ret
op_or_assign
id|rd_blkdev_pagecache_IO
c_func
(paren
id|rw
comma
id|bvec
comma
id|sector
comma
id|mapping
)paren
suffix:semicolon
id|sector
op_add_assign
id|bvec-&gt;bv_len
op_rshift
l_int|9
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|fail
suffix:semicolon
id|bio_endio
c_func
(paren
id|bio
comma
id|bio-&gt;bi_size
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|bio_io_error
c_func
(paren
id|bio
comma
id|bio-&gt;bi_size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rd_ioctl
r_static
r_int
id|rd_ioctl
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
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_ne
id|BLKFLSBUF
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* special: we want to release the ramdisk memory,&n;&t;   it&squot;s not like with the other blockdevices where&n;&t;   this ioctl only flushes away the buffer cache. */
id|error
op_assign
op_minus
id|EBUSY
suffix:semicolon
id|down
c_func
(paren
op_amp
id|inode-&gt;i_bdev-&gt;bd_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_bdev-&gt;bd_openers
op_le
l_int|2
)paren
(brace
id|truncate_inode_pages
c_func
(paren
id|inode-&gt;i_mapping
comma
l_int|0
)paren
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|inode-&gt;i_bdev-&gt;bd_sem
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
DECL|variable|rd_bd_op
r_static
r_struct
id|block_device_operations
id|rd_bd_op
suffix:semicolon
DECL|variable|initrd_disk
r_static
r_struct
id|gendisk
op_star
id|initrd_disk
suffix:semicolon
DECL|function|initrd_read
r_static
id|ssize_t
id|initrd_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_int
id|left
suffix:semicolon
id|left
op_assign
id|initrd_end
op_minus
id|initrd_start
op_minus
op_star
id|ppos
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|left
)paren
id|count
op_assign
id|left
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
(paren
r_char
op_star
)paren
id|initrd_start
op_plus
op_star
id|ppos
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
id|ppos
op_add_assign
id|count
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|initrd_release
r_static
r_int
id|initrd_release
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
id|file
)paren
(brace
r_extern
r_void
id|free_initrd_mem
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
id|blkdev_put
c_func
(paren
id|inode-&gt;i_bdev
comma
id|BDEV_FILE
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|initrd_users_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|initrd_users
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|initrd_users_lock
)paren
suffix:semicolon
id|del_gendisk
c_func
(paren
id|initrd_disk
)paren
suffix:semicolon
id|free_initrd_mem
c_func
(paren
id|initrd_start
comma
id|initrd_end
)paren
suffix:semicolon
id|initrd_start
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|spin_unlock
c_func
(paren
op_amp
id|initrd_users_lock
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|initrd_fops
r_static
r_struct
id|file_operations
id|initrd_fops
op_assign
(brace
dot
id|read
op_assign
id|initrd_read
comma
dot
id|release
op_assign
id|initrd_release
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|rd_backing_dev_info
r_static
r_struct
id|backing_dev_info
id|rd_backing_dev_info
op_assign
(brace
dot
id|ra_pages
op_assign
l_int|0
comma
multiline_comment|/* No readahead */
dot
id|memory_backed
op_assign
l_int|1
comma
multiline_comment|/* Does not contribute to dirty memory */
)brace
suffix:semicolon
DECL|function|rd_open
r_static
r_int
id|rd_open
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
id|unit
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|unit
op_eq
id|INITRD_MINOR
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|initrd_users_lock
)paren
suffix:semicolon
id|initrd_users
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|initrd_users_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|initrd_start
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|filp-&gt;f_op
op_assign
op_amp
id|initrd_fops
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;&t; * Immunize device against invalidate_buffers() and prune_icache().&n;&t; */
r_if
c_cond
(paren
id|rd_bdev
(braket
id|unit
)braket
op_eq
l_int|NULL
)paren
(brace
r_struct
id|block_device
op_star
id|bdev
op_assign
id|inode-&gt;i_bdev
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|bdev-&gt;bd_count
)paren
suffix:semicolon
id|rd_bdev
(braket
id|unit
)braket
op_assign
id|bdev
suffix:semicolon
id|bdev-&gt;bd_openers
op_increment
suffix:semicolon
id|bdev-&gt;bd_block_size
op_assign
id|rd_blocksize
suffix:semicolon
id|bdev-&gt;bd_inode-&gt;i_size
op_assign
id|get_capacity
c_func
(paren
id|rd_disks
(braket
id|unit
)braket
)paren
op_lshift
l_int|9
suffix:semicolon
id|inode-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|ramdisk_aops
suffix:semicolon
id|inode-&gt;i_mapping-&gt;backing_dev_info
op_assign
op_amp
id|rd_backing_dev_info
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|rd_bd_op
r_static
r_struct
id|block_device_operations
id|rd_bd_op
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|rd_open
comma
dot
id|ioctl
op_assign
id|rd_ioctl
comma
)brace
suffix:semicolon
multiline_comment|/* Before freeing the module, invalidate all of the protected buffers! */
DECL|function|rd_cleanup
r_static
r_void
id|__exit
id|rd_cleanup
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
id|NUM_RAMDISKS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|block_device
op_star
id|bdev
op_assign
id|rd_bdev
(braket
id|i
)braket
suffix:semicolon
id|rd_bdev
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|bdev
)paren
(brace
id|invalidate_bdev
c_func
(paren
id|bdev
comma
l_int|1
)paren
suffix:semicolon
id|blkdev_put
c_func
(paren
id|bdev
comma
id|BDEV_FILE
)paren
suffix:semicolon
)brace
id|del_gendisk
c_func
(paren
id|rd_disks
(braket
id|i
)braket
)paren
suffix:semicolon
id|put_disk
c_func
(paren
id|rd_disks
(braket
id|i
)braket
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;rd/%d&quot;
comma
id|i
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
id|put_disk
c_func
(paren
id|initrd_disk
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;rd/initrd&quot;
)paren
suffix:semicolon
macro_line|#endif
id|devfs_remove
c_func
(paren
l_string|&quot;rd&quot;
)paren
suffix:semicolon
id|unregister_blkdev
c_func
(paren
id|RAMDISK_MAJOR
comma
l_string|&quot;ramdisk&quot;
)paren
suffix:semicolon
)brace
DECL|variable|rd_queue
r_static
r_struct
id|request_queue
id|rd_queue
suffix:semicolon
multiline_comment|/* This is the registration and initialization section of the RAM disk driver */
DECL|function|rd_init
r_static
r_int
id|__init
id|rd_init
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|rd_blocksize
OG
id|PAGE_SIZE
op_logical_or
id|rd_blocksize
OL
l_int|512
op_logical_or
(paren
id|rd_blocksize
op_amp
(paren
id|rd_blocksize
op_minus
l_int|1
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;RAMDISK: wrong blocksize %d, reverting to defaults&bslash;n&quot;
comma
id|rd_blocksize
)paren
suffix:semicolon
id|rd_blocksize
op_assign
id|BLOCK_SIZE
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
id|initrd_disk
op_assign
id|alloc_disk
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|initrd_disk
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|initrd_disk-&gt;major
op_assign
id|RAMDISK_MAJOR
suffix:semicolon
id|initrd_disk-&gt;first_minor
op_assign
id|INITRD_MINOR
suffix:semicolon
id|initrd_disk-&gt;fops
op_assign
op_amp
id|rd_bd_op
suffix:semicolon
id|sprintf
c_func
(paren
id|initrd_disk-&gt;disk_name
comma
l_string|&quot;initrd&quot;
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_RAMDISKS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rd_disks
(braket
id|i
)braket
op_assign
id|alloc_disk
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rd_disks
(braket
id|i
)braket
)paren
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|register_blkdev
c_func
(paren
id|RAMDISK_MAJOR
comma
l_string|&quot;ramdisk&quot;
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|blk_queue_make_request
c_func
(paren
op_amp
id|rd_queue
comma
op_amp
id|rd_make_request
)paren
suffix:semicolon
id|devfs_mk_dir
(paren
l_int|NULL
comma
l_string|&quot;rd&quot;
comma
l_int|NULL
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
id|NUM_RAMDISKS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|gendisk
op_star
id|disk
op_assign
id|rd_disks
(braket
id|i
)braket
suffix:semicolon
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* rd_size is given in kB */
id|disk-&gt;major
op_assign
id|RAMDISK_MAJOR
suffix:semicolon
id|disk-&gt;first_minor
op_assign
id|i
suffix:semicolon
id|disk-&gt;fops
op_assign
op_amp
id|rd_bd_op
suffix:semicolon
id|disk-&gt;queue
op_assign
op_amp
id|rd_queue
suffix:semicolon
id|sprintf
c_func
(paren
id|disk-&gt;disk_name
comma
l_string|&quot;ram%d&quot;
comma
id|i
)paren
suffix:semicolon
id|set_capacity
c_func
(paren
id|disk
comma
id|rd_size
op_star
l_int|2
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;rd/%d&quot;
comma
id|i
)paren
suffix:semicolon
id|devfs_register
c_func
(paren
l_int|NULL
comma
id|name
comma
id|DEVFS_FL_DEFAULT
comma
id|disk-&gt;major
comma
id|disk-&gt;first_minor
comma
id|S_IFBLK
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
id|disk-&gt;fops
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_RAMDISKS
suffix:semicolon
id|i
op_increment
)paren
id|add_disk
c_func
(paren
id|rd_disks
(braket
id|i
)braket
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
multiline_comment|/* We ought to separate initrd operations here */
id|set_capacity
c_func
(paren
id|initrd_disk
comma
(paren
id|initrd_end
op_minus
id|initrd_start
op_plus
l_int|511
)paren
op_rshift
l_int|9
)paren
suffix:semicolon
id|add_disk
c_func
(paren
id|initrd_disk
)paren
suffix:semicolon
id|devfs_register
c_func
(paren
l_int|NULL
comma
l_string|&quot;rd/initrd&quot;
comma
id|DEVFS_FL_DEFAULT
comma
id|RAMDISK_MAJOR
comma
id|INITRD_MINOR
comma
id|S_IFBLK
op_or
id|S_IRUSR
comma
op_amp
id|rd_bd_op
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* rd_size is given in kB */
id|printk
c_func
(paren
l_string|&quot;RAMDISK driver initialized: &quot;
l_string|&quot;%d RAM disks of %dK size %d blocksize&bslash;n&quot;
comma
id|NUM_RAMDISKS
comma
id|rd_size
comma
id|rd_blocksize
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
r_while
c_loop
(paren
id|i
op_decrement
)paren
id|put_disk
c_func
(paren
id|rd_disks
(braket
id|i
)braket
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
id|put_disk
c_func
(paren
id|initrd_disk
)paren
suffix:semicolon
macro_line|#endif
r_return
id|err
suffix:semicolon
)brace
DECL|variable|rd_init
id|module_init
c_func
(paren
id|rd_init
)paren
suffix:semicolon
DECL|variable|rd_cleanup
id|module_exit
c_func
(paren
id|rd_cleanup
)paren
suffix:semicolon
multiline_comment|/* options - nonmodular */
macro_line|#ifndef MODULE
DECL|function|ramdisk_size
r_static
r_int
id|__init
id|ramdisk_size
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|rd_size
op_assign
id|simple_strtol
c_func
(paren
id|str
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|ramdisk_size2
r_static
r_int
id|__init
id|ramdisk_size2
c_func
(paren
r_char
op_star
id|str
)paren
multiline_comment|/* kludge */
(brace
r_return
id|ramdisk_size
c_func
(paren
id|str
)paren
suffix:semicolon
)brace
DECL|function|ramdisk_blocksize
r_static
r_int
id|__init
id|ramdisk_blocksize
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|rd_blocksize
op_assign
id|simple_strtol
c_func
(paren
id|str
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;ramdisk=&quot;
comma
id|ramdisk_size
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;ramdisk_size=&quot;
comma
id|ramdisk_size2
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;ramdisk_blocksize=&quot;
comma
id|ramdisk_blocksize
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* options - modular */
id|MODULE_PARM
(paren
id|rd_size
comma
l_string|&quot;1i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|rd_size
comma
l_string|&quot;Size of each RAM disk in kbytes.&quot;
)paren
suffix:semicolon
id|MODULE_PARM
(paren
id|rd_blocksize
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|rd_blocksize
comma
l_string|&quot;Blocksize of each RAM disk in bytes.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
