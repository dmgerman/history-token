multiline_comment|/*&n; *  linux/fs/block_dev.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *  Copyright (C) 2001  Andrea Arcangeli &lt;andrea@suse.de&gt; SuSE&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/iobuf.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/blkpg.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/mpage.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|function|max_block
r_static
r_int
r_int
id|max_block
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
)paren
(brace
r_int
r_int
id|retval
op_assign
op_complement
l_int|0U
suffix:semicolon
id|loff_t
id|sz
op_assign
id|bdev-&gt;bd_inode-&gt;i_size
suffix:semicolon
r_if
c_cond
(paren
id|sz
)paren
(brace
r_int
r_int
id|size
op_assign
id|block_size
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_int
r_int
id|sizebits
op_assign
id|blksize_bits
c_func
(paren
id|size
)paren
suffix:semicolon
id|retval
op_assign
(paren
id|sz
op_rshift
id|sizebits
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|blkdev_size
r_static
id|loff_t
id|blkdev_size
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
id|loff_t
id|sz
op_assign
id|blkdev_size_in_bytes
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sz
)paren
r_return
id|sz
suffix:semicolon
r_return
op_complement
l_int|0ULL
suffix:semicolon
)brace
multiline_comment|/* Kill _all_ buffers, dirty or not.. */
DECL|function|kill_bdev
r_static
r_void
id|kill_bdev
c_func
(paren
r_struct
id|block_device
op_star
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
id|truncate_inode_pages
c_func
(paren
id|bdev-&gt;bd_inode-&gt;i_mapping
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|set_blocksize
r_int
id|set_blocksize
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
id|size
)paren
(brace
r_int
id|oldsize
suffix:semicolon
multiline_comment|/* Size must be a power of two, and between 512 and PAGE_SIZE */
r_if
c_cond
(paren
id|size
OG
id|PAGE_SIZE
op_logical_or
id|size
OL
l_int|512
op_logical_or
(paren
id|size
op_amp
(paren
id|size
op_minus
l_int|1
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Size cannot be smaller than the size supported by the device */
r_if
c_cond
(paren
id|size
OL
id|bdev_hardsect_size
c_func
(paren
id|bdev
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|oldsize
op_assign
id|bdev-&gt;bd_block_size
suffix:semicolon
r_if
c_cond
(paren
id|oldsize
op_eq
id|size
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Ok, we&squot;re actually changing the blocksize.. */
id|sync_blockdev
c_func
(paren
id|bdev
)paren
suffix:semicolon
id|bdev-&gt;bd_block_size
op_assign
id|size
suffix:semicolon
id|bdev-&gt;bd_inode-&gt;i_blkbits
op_assign
id|blksize_bits
c_func
(paren
id|size
)paren
suffix:semicolon
id|kill_bdev
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sb_set_blocksize
r_int
id|sb_set_blocksize
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|size
)paren
(brace
r_int
id|bits
suffix:semicolon
r_if
c_cond
(paren
id|set_blocksize
c_func
(paren
id|sb-&gt;s_bdev
comma
id|size
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|sb-&gt;s_blocksize
op_assign
id|size
suffix:semicolon
r_for
c_loop
(paren
id|bits
op_assign
l_int|9
comma
id|size
op_rshift_assign
l_int|9
suffix:semicolon
id|size
op_rshift_assign
l_int|1
suffix:semicolon
id|bits
op_increment
)paren
suffix:semicolon
id|sb-&gt;s_blocksize_bits
op_assign
id|bits
suffix:semicolon
r_return
id|sb-&gt;s_blocksize
suffix:semicolon
)brace
DECL|function|sb_min_blocksize
r_int
id|sb_min_blocksize
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|size
)paren
(brace
r_int
id|minsize
op_assign
id|bdev_hardsect_size
c_func
(paren
id|sb-&gt;s_bdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
id|minsize
)paren
id|size
op_assign
id|minsize
suffix:semicolon
r_return
id|sb_set_blocksize
c_func
(paren
id|sb
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|blkdev_get_block
r_static
r_int
id|blkdev_get_block
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|sector_t
id|iblock
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|create
)paren
(brace
r_if
c_cond
(paren
id|iblock
op_ge
id|max_block
c_func
(paren
id|inode-&gt;i_bdev
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|bh-&gt;b_bdev
op_assign
id|inode-&gt;i_bdev
suffix:semicolon
id|bh-&gt;b_blocknr
op_assign
id|iblock
suffix:semicolon
id|set_buffer_mapped
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|blkdev_direct_IO
id|blkdev_direct_IO
c_func
(paren
r_int
id|rw
comma
r_struct
id|inode
op_star
id|inode
comma
r_char
op_star
id|buf
comma
id|loff_t
id|offset
comma
r_int
id|count
)paren
(brace
r_return
id|generic_direct_IO
c_func
(paren
id|rw
comma
id|inode
comma
id|buf
comma
id|offset
comma
id|count
comma
id|blkdev_get_block
)paren
suffix:semicolon
)brace
DECL|function|blkdev_writepage
r_static
r_int
id|blkdev_writepage
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
id|block_write_full_page
c_func
(paren
id|page
comma
id|blkdev_get_block
)paren
suffix:semicolon
)brace
DECL|function|blkdev_readpage
r_static
r_int
id|blkdev_readpage
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
r_return
id|block_read_full_page
c_func
(paren
id|page
comma
id|blkdev_get_block
)paren
suffix:semicolon
)brace
DECL|function|blkdev_prepare_write
r_static
r_int
id|blkdev_prepare_write
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
id|from
comma
r_int
id|to
)paren
(brace
r_return
id|block_prepare_write
c_func
(paren
id|page
comma
id|from
comma
id|to
comma
id|blkdev_get_block
)paren
suffix:semicolon
)brace
DECL|function|blkdev_commit_write
r_static
r_int
id|blkdev_commit_write
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
id|from
comma
r_int
id|to
)paren
(brace
r_return
id|block_commit_write
c_func
(paren
id|page
comma
id|from
comma
id|to
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * private llseek:&n; * for a block special file file-&gt;f_dentry-&gt;d_inode-&gt;i_size is zero&n; * so we compute the size by hand (just as in block_read/write above)&n; */
DECL|function|block_llseek
r_static
id|loff_t
id|block_llseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|origin
)paren
(brace
multiline_comment|/* ewww */
id|loff_t
id|size
op_assign
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_bdev-&gt;bd_inode-&gt;i_size
suffix:semicolon
id|loff_t
id|retval
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|origin
)paren
(brace
r_case
l_int|2
suffix:colon
id|offset
op_add_assign
id|size
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|offset
op_add_assign
id|file-&gt;f_pos
suffix:semicolon
)brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
l_int|0
op_logical_and
id|offset
op_le
id|size
)paren
(brace
r_if
c_cond
(paren
id|offset
op_ne
id|file-&gt;f_pos
)paren
(brace
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
id|file-&gt;f_version
op_assign
op_increment
id|event
suffix:semicolon
)brace
id|retval
op_assign
id|offset
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Filp may be NULL when we are called by an msync of a vma&n; *&t;since the vma has no handle.&n; */
DECL|function|block_fsync
r_static
r_int
id|block_fsync
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|datasync
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_return
id|sync_blockdev
c_func
(paren
id|inode-&gt;i_bdev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * pseudo-fs&n; */
DECL|function|bd_get_sb
r_static
r_struct
id|super_block
op_star
id|bd_get_sb
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs_type
comma
r_int
id|flags
comma
r_char
op_star
id|dev_name
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|get_sb_pseudo
c_func
(paren
id|fs_type
comma
l_string|&quot;bdev:&quot;
comma
l_int|NULL
comma
l_int|0x62646576
)paren
suffix:semicolon
)brace
DECL|variable|bd_type
r_static
r_struct
id|file_system_type
id|bd_type
op_assign
(brace
id|name
suffix:colon
l_string|&quot;bdev&quot;
comma
id|get_sb
suffix:colon
id|bd_get_sb
comma
id|kill_sb
suffix:colon
id|kill_anon_super
comma
)brace
suffix:semicolon
DECL|variable|bd_mnt
r_static
r_struct
id|vfsmount
op_star
id|bd_mnt
suffix:semicolon
multiline_comment|/*&n; * bdev cache handling - shamelessly stolen from inode.c&n; * We use smaller hashtable, though.&n; */
DECL|macro|HASH_BITS
mdefine_line|#define HASH_BITS&t;6
DECL|macro|HASH_SIZE
mdefine_line|#define HASH_SIZE&t;(1UL &lt;&lt; HASH_BITS)
DECL|macro|HASH_MASK
mdefine_line|#define HASH_MASK&t;(HASH_SIZE-1)
DECL|variable|bdev_hashtable
r_static
r_struct
id|list_head
id|bdev_hashtable
(braket
id|HASH_SIZE
)braket
suffix:semicolon
DECL|variable|__cacheline_aligned_in_smp
r_static
id|spinlock_t
id|bdev_lock
id|__cacheline_aligned_in_smp
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|bdev_cachep
r_static
id|kmem_cache_t
op_star
id|bdev_cachep
suffix:semicolon
DECL|macro|alloc_bdev
mdefine_line|#define alloc_bdev() &bslash;&n;&t; ((struct block_device *) kmem_cache_alloc(bdev_cachep, SLAB_KERNEL))
DECL|macro|destroy_bdev
mdefine_line|#define destroy_bdev(bdev) kmem_cache_free(bdev_cachep, (bdev))
DECL|function|init_once
r_static
r_void
id|init_once
c_func
(paren
r_void
op_star
id|foo
comma
id|kmem_cache_t
op_star
id|cachep
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|block_device
op_star
id|bdev
op_assign
(paren
r_struct
id|block_device
op_star
)paren
id|foo
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
(paren
id|SLAB_CTOR_VERIFY
op_or
id|SLAB_CTOR_CONSTRUCTOR
)paren
)paren
op_eq
id|SLAB_CTOR_CONSTRUCTOR
)paren
(brace
id|memset
c_func
(paren
id|bdev
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|bdev
)paren
)paren
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|bdev-&gt;bd_sem
comma
l_int|1
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|bdev-&gt;bd_inodes
)paren
suffix:semicolon
)brace
)brace
DECL|function|bdev_cache_init
r_void
id|__init
id|bdev_cache_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|err
suffix:semicolon
r_struct
id|list_head
op_star
id|head
op_assign
id|bdev_hashtable
suffix:semicolon
id|i
op_assign
id|HASH_SIZE
suffix:semicolon
r_do
(brace
id|INIT_LIST_HEAD
c_func
(paren
id|head
)paren
suffix:semicolon
id|head
op_increment
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
)paren
suffix:semicolon
id|bdev_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;bdev_cache&quot;
comma
r_sizeof
(paren
r_struct
id|block_device
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
id|init_once
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev_cachep
)paren
id|panic
c_func
(paren
l_string|&quot;Cannot create bdev_cache SLAB cache&quot;
)paren
suffix:semicolon
id|err
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|bd_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|panic
c_func
(paren
l_string|&quot;Cannot register bdev pseudo-fs&quot;
)paren
suffix:semicolon
id|bd_mnt
op_assign
id|kern_mount
c_func
(paren
op_amp
id|bd_type
)paren
suffix:semicolon
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|bd_mnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|bd_mnt
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Cannot create bdev pseudo-fs&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Most likely _very_ bad one - but then it&squot;s hardly critical for small&n; * /dev and can be fixed when somebody will need really large one.&n; */
DECL|function|hash
r_static
r_inline
r_int
r_int
id|hash
c_func
(paren
id|dev_t
id|dev
)paren
(brace
r_int
r_int
id|tmp
op_assign
id|dev
suffix:semicolon
id|tmp
op_assign
id|tmp
op_plus
(paren
id|tmp
op_rshift
id|HASH_BITS
)paren
op_plus
(paren
id|tmp
op_rshift
id|HASH_BITS
op_star
l_int|2
)paren
suffix:semicolon
r_return
id|tmp
op_amp
id|HASH_MASK
suffix:semicolon
)brace
DECL|function|bdfind
r_static
r_struct
id|block_device
op_star
id|bdfind
c_func
(paren
id|dev_t
id|dev
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
id|head
)paren
(brace
id|bdev
op_assign
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|block_device
comma
id|bd_hash
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bdev-&gt;bd_dev
op_ne
id|dev
)paren
r_continue
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|bdev-&gt;bd_count
)paren
suffix:semicolon
r_return
id|bdev
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|bdget
r_struct
id|block_device
op_star
id|bdget
c_func
(paren
id|dev_t
id|dev
)paren
(brace
r_struct
id|list_head
op_star
id|head
op_assign
id|bdev_hashtable
op_plus
id|hash
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|block_device
op_star
id|bdev
comma
op_star
id|new_bdev
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
id|bdev
op_assign
id|bdfind
c_func
(paren
id|dev
comma
id|head
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bdev
)paren
r_return
id|bdev
suffix:semicolon
id|new_bdev
op_assign
id|alloc_bdev
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_bdev
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|new_inode
c_func
(paren
id|bd_mnt-&gt;mnt_sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
(brace
id|kdev_t
id|kdev
op_assign
id|to_kdev_t
c_func
(paren
id|dev
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|new_bdev-&gt;bd_count
comma
l_int|1
)paren
suffix:semicolon
id|new_bdev-&gt;bd_dev
op_assign
id|dev
suffix:semicolon
id|new_bdev-&gt;bd_op
op_assign
l_int|NULL
suffix:semicolon
id|new_bdev-&gt;bd_queue
op_assign
l_int|NULL
suffix:semicolon
id|new_bdev-&gt;bd_contains
op_assign
l_int|NULL
suffix:semicolon
id|new_bdev-&gt;bd_inode
op_assign
id|inode
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|S_IFBLK
suffix:semicolon
id|inode-&gt;i_rdev
op_assign
id|kdev
suffix:semicolon
id|inode-&gt;i_bdev
op_assign
id|new_bdev
suffix:semicolon
id|inode-&gt;i_data.a_ops
op_assign
op_amp
id|def_blk_aops
suffix:semicolon
id|inode-&gt;i_data.gfp_mask
op_assign
id|GFP_USER
suffix:semicolon
id|inode-&gt;i_data.backing_dev_info
op_assign
op_amp
id|default_backing_dev_info
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
id|bdev
op_assign
id|bdfind
c_func
(paren
id|dev
comma
id|head
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev
)paren
(brace
id|list_add
c_func
(paren
op_amp
id|new_bdev-&gt;bd_hash
comma
id|head
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
r_return
id|new_bdev
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
id|iput
c_func
(paren
id|new_bdev-&gt;bd_inode
)paren
suffix:semicolon
)brace
id|destroy_bdev
c_func
(paren
id|new_bdev
)paren
suffix:semicolon
)brace
r_return
id|bdev
suffix:semicolon
)brace
DECL|function|__bd_forget
r_static
r_inline
r_void
id|__bd_forget
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|list_del_init
c_func
(paren
op_amp
id|inode-&gt;i_devices
)paren
suffix:semicolon
id|inode-&gt;i_bdev
op_assign
l_int|NULL
suffix:semicolon
id|inode-&gt;i_mapping
op_assign
op_amp
id|inode-&gt;i_data
suffix:semicolon
)brace
DECL|function|bdput
r_void
id|bdput
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_lock
c_func
(paren
op_amp
id|bdev-&gt;bd_count
comma
op_amp
id|bdev_lock
)paren
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|bdev-&gt;bd_openers
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|bdev-&gt;bd_hash
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|p
op_assign
id|bdev-&gt;bd_inodes.next
)paren
op_ne
op_amp
id|bdev-&gt;bd_inodes
)paren
(brace
id|__bd_forget
c_func
(paren
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|inode
comma
id|i_devices
)paren
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
id|iput
c_func
(paren
id|bdev-&gt;bd_inode
)paren
suffix:semicolon
id|destroy_bdev
c_func
(paren
id|bdev
)paren
suffix:semicolon
)brace
)brace
DECL|function|bd_acquire
r_int
id|bd_acquire
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_bdev
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|inode-&gt;i_bdev-&gt;bd_count
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
id|bdev
op_assign
id|bdget
c_func
(paren
id|kdev_t_to_nr
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_bdev
)paren
(brace
id|inode-&gt;i_bdev
op_assign
id|bdev
suffix:semicolon
id|inode-&gt;i_mapping
op_assign
id|bdev-&gt;bd_inode-&gt;i_mapping
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|inode-&gt;i_devices
comma
op_amp
id|bdev-&gt;bd_inodes
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|inode-&gt;i_bdev
op_ne
id|bdev
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Call when you free inode */
DECL|function|bd_forget
r_void
id|bd_forget
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_bdev
)paren
id|__bd_forget
c_func
(paren
id|inode
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
)brace
DECL|function|bd_claim
r_int
id|bd_claim
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_void
op_star
id|holder
)paren
(brace
r_int
id|res
op_assign
op_minus
id|EBUSY
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev-&gt;bd_holder
op_logical_or
id|bdev-&gt;bd_holder
op_eq
id|holder
)paren
(brace
id|bdev-&gt;bd_holder
op_assign
id|holder
suffix:semicolon
id|bdev-&gt;bd_holders
op_increment
suffix:semicolon
id|res
op_assign
l_int|0
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|bd_release
r_void
id|bd_release
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|bdev-&gt;bd_holders
)paren
id|bdev-&gt;bd_holder
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|bdev_lock
)paren
suffix:semicolon
)brace
r_static
r_struct
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|bdops
r_struct
id|block_device_operations
op_star
id|bdops
suffix:semicolon
DECL|variable|blkdevs
)brace
id|blkdevs
(braket
id|MAX_BLKDEV
)braket
suffix:semicolon
DECL|function|get_blkdev_list
r_int
id|get_blkdev_list
c_func
(paren
r_char
op_star
id|p
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;nBlock devices:&bslash;n&quot;
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
id|MAX_BLKDEV
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|blkdevs
(braket
id|i
)braket
dot
id|bdops
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|p
op_plus
id|len
comma
l_string|&quot;%3d %s&bslash;n&quot;
comma
id|i
comma
id|blkdevs
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
)brace
)brace
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n;&t;Return the function table of a device.&n;&t;Load the driver if needed.&n;*/
DECL|function|get_blkfops
r_const
r_struct
id|block_device_operations
op_star
id|get_blkfops
c_func
(paren
r_int
r_int
id|major
)paren
(brace
r_const
r_struct
id|block_device_operations
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* major 0 is used for non-device mounts */
r_if
c_cond
(paren
id|major
op_logical_and
id|major
OL
id|MAX_BLKDEV
)paren
(brace
macro_line|#ifdef CONFIG_KMOD
r_if
c_cond
(paren
op_logical_neg
id|blkdevs
(braket
id|major
)braket
dot
id|bdops
)paren
(brace
r_char
id|name
(braket
l_int|20
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;block-major-%d&quot;
comma
id|major
)paren
suffix:semicolon
id|request_module
c_func
(paren
id|name
)paren
suffix:semicolon
)brace
macro_line|#endif
id|ret
op_assign
id|blkdevs
(braket
id|major
)braket
dot
id|bdops
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|register_blkdev
r_int
id|register_blkdev
c_func
(paren
r_int
r_int
id|major
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|block_device_operations
op_star
id|bdops
)paren
(brace
r_if
c_cond
(paren
id|major
op_eq
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|major
op_assign
id|MAX_BLKDEV
op_minus
l_int|1
suffix:semicolon
id|major
OG
l_int|0
suffix:semicolon
id|major
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|blkdevs
(braket
id|major
)braket
dot
id|bdops
op_eq
l_int|NULL
)paren
(brace
id|blkdevs
(braket
id|major
)braket
dot
id|name
op_assign
id|name
suffix:semicolon
id|blkdevs
(braket
id|major
)braket
dot
id|bdops
op_assign
id|bdops
suffix:semicolon
r_return
id|major
suffix:semicolon
)brace
)brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|major
op_ge
id|MAX_BLKDEV
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|blkdevs
(braket
id|major
)braket
dot
id|bdops
op_logical_and
id|blkdevs
(braket
id|major
)braket
dot
id|bdops
op_ne
id|bdops
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|blkdevs
(braket
id|major
)braket
dot
id|name
op_assign
id|name
suffix:semicolon
id|blkdevs
(braket
id|major
)braket
dot
id|bdops
op_assign
id|bdops
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unregister_blkdev
r_int
id|unregister_blkdev
c_func
(paren
r_int
r_int
id|major
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_if
c_cond
(paren
id|major
op_ge
id|MAX_BLKDEV
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|blkdevs
(braket
id|major
)braket
dot
id|bdops
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|blkdevs
(braket
id|major
)braket
dot
id|name
comma
id|name
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|blkdevs
(braket
id|major
)braket
dot
id|name
op_assign
l_int|NULL
suffix:semicolon
id|blkdevs
(braket
id|major
)braket
dot
id|bdops
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine checks whether a removable media has been changed,&n; * and invalidates all buffer-cache-entries in that case. This&n; * is a relatively slow routine, so we have to try to minimize using&n; * it. Thus it is called only upon a &squot;mount&squot; or &squot;open&squot;. This&n; * is the best way of combining speed and utility, I think.&n; * People changing diskettes in the middle of an operation deserve&n; * to lose :-)&n; */
DECL|function|check_disk_change
r_int
id|check_disk_change
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_const
r_struct
id|block_device_operations
op_star
id|bdops
op_assign
l_int|NULL
suffix:semicolon
id|i
op_assign
id|major
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|MAX_BLKDEV
)paren
id|bdops
op_assign
id|blkdevs
(braket
id|i
)braket
dot
id|bdops
suffix:semicolon
r_if
c_cond
(paren
id|bdops
op_eq
l_int|NULL
)paren
(brace
id|devfs_handle_t
id|de
suffix:semicolon
id|de
op_assign
id|devfs_find_handle
(paren
l_int|NULL
comma
l_int|NULL
comma
id|i
comma
id|minor
c_func
(paren
id|dev
)paren
comma
id|DEVFS_SPECIAL_BLK
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|de
)paren
(brace
id|bdops
op_assign
id|devfs_get_ops
(paren
id|de
)paren
suffix:semicolon
id|devfs_put_ops
(paren
id|de
)paren
suffix:semicolon
multiline_comment|/* We&squot;re running in owner module */
)brace
)brace
r_if
c_cond
(paren
id|bdops
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bdops-&gt;check_media_change
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdops
op_member_access_from_pointer
id|check_media_change
c_func
(paren
id|dev
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;VFS: Disk change detected on device %s&bslash;n&quot;
comma
id|__bdevname
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|invalidate_device
c_func
(paren
id|dev
comma
l_int|0
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;VFS: busy inodes on changed media.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bdops-&gt;revalidate
)paren
id|bdops
op_member_access_from_pointer
id|revalidate
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|ioctl_by_bdev
r_int
id|ioctl_by_bdev
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|res
suffix:semicolon
id|mm_segment_t
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev-&gt;bd_op-&gt;ioctl
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|res
op_assign
id|bdev-&gt;bd_op
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|bdev-&gt;bd_inode
comma
l_int|NULL
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|do_open
r_static
r_int
id|do_open
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
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
r_int
id|ret
op_assign
op_minus
id|ENXIO
suffix:semicolon
id|kdev_t
id|dev
op_assign
id|to_kdev_t
c_func
(paren
id|bdev-&gt;bd_dev
)paren
suffix:semicolon
r_struct
id|module
op_star
id|owner
op_assign
l_int|NULL
suffix:semicolon
id|down
c_func
(paren
op_amp
id|bdev-&gt;bd_sem
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev-&gt;bd_op
)paren
(brace
id|bdev-&gt;bd_op
op_assign
id|get_blkfops
c_func
(paren
id|major
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev-&gt;bd_op
)paren
r_goto
id|out
suffix:semicolon
id|owner
op_assign
id|bdev-&gt;bd_op-&gt;owner
suffix:semicolon
r_if
c_cond
(paren
id|owner
)paren
id|__MOD_INC_USE_COUNT
c_func
(paren
id|owner
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|bdev-&gt;bd_contains
)paren
(brace
r_int
id|minor
op_assign
id|minor
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|gendisk
op_star
id|g
op_assign
id|get_gendisk
c_func
(paren
id|dev
)paren
suffix:semicolon
id|bdev-&gt;bd_contains
op_assign
id|bdev
suffix:semicolon
r_if
c_cond
(paren
id|g
)paren
(brace
r_int
id|shift
op_assign
id|g-&gt;minor_shift
suffix:semicolon
r_int
id|minor0
op_assign
(paren
id|minor
op_rshift
id|shift
)paren
op_lshift
id|shift
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_ne
id|minor0
)paren
(brace
r_struct
id|block_device
op_star
id|disk
suffix:semicolon
id|disk
op_assign
id|bdget
c_func
(paren
id|MKDEV
c_func
(paren
id|major
c_func
(paren
id|dev
)paren
comma
id|minor0
)paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|disk
)paren
r_goto
id|out1
suffix:semicolon
id|ret
op_assign
id|blkdev_get
c_func
(paren
id|disk
comma
id|file-&gt;f_mode
comma
id|file-&gt;f_flags
comma
id|BDEV_RAW
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out1
suffix:semicolon
id|bdev-&gt;bd_contains
op_assign
id|disk
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|bdev-&gt;bd_inode-&gt;i_data.backing_dev_info
op_eq
op_amp
id|default_backing_dev_info
)paren
(brace
r_struct
id|backing_dev_info
op_star
id|bdi
op_assign
id|blk_get_backing_dev_info
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bdi
op_eq
l_int|NULL
)paren
id|bdi
op_assign
op_amp
id|default_backing_dev_info
suffix:semicolon
id|inode-&gt;i_data.backing_dev_info
op_assign
id|bdi
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bdev-&gt;bd_op-&gt;open
)paren
(brace
id|ret
op_assign
id|bdev-&gt;bd_op
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out2
suffix:semicolon
)brace
id|bdev-&gt;bd_inode-&gt;i_size
op_assign
id|blkdev_size
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev-&gt;bd_openers
)paren
(brace
r_struct
id|blk_dev_struct
op_star
id|p
op_assign
id|blk_dev
op_plus
id|major
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|bsize
op_assign
id|bdev_hardsect_size
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_while
c_loop
(paren
id|bsize
OL
id|PAGE_CACHE_SIZE
)paren
(brace
r_if
c_cond
(paren
id|bdev-&gt;bd_inode-&gt;i_size
op_amp
id|bsize
)paren
r_break
suffix:semicolon
id|bsize
op_lshift_assign
l_int|1
suffix:semicolon
)brace
id|bdev-&gt;bd_block_size
op_assign
id|bsize
suffix:semicolon
id|bdev-&gt;bd_inode-&gt;i_blkbits
op_assign
id|blksize_bits
c_func
(paren
id|bsize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;queue
)paren
id|bdev-&gt;bd_queue
op_assign
id|p
op_member_access_from_pointer
id|queue
c_func
(paren
id|dev
)paren
suffix:semicolon
r_else
id|bdev-&gt;bd_queue
op_assign
op_amp
id|p-&gt;request_queue
suffix:semicolon
)brace
id|bdev-&gt;bd_openers
op_increment
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|bdev-&gt;bd_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out2
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|bdev-&gt;bd_openers
)paren
(brace
id|bdev-&gt;bd_op
op_assign
l_int|NULL
suffix:semicolon
id|bdev-&gt;bd_queue
op_assign
l_int|NULL
suffix:semicolon
id|bdev-&gt;bd_inode-&gt;i_data.backing_dev_info
op_assign
op_amp
id|default_backing_dev_info
suffix:semicolon
r_if
c_cond
(paren
id|bdev
op_ne
id|bdev-&gt;bd_contains
)paren
(brace
id|blkdev_put
c_func
(paren
id|bdev-&gt;bd_contains
comma
id|BDEV_RAW
)paren
suffix:semicolon
id|bdev-&gt;bd_contains
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|out1
suffix:colon
r_if
c_cond
(paren
id|owner
)paren
id|__MOD_DEC_USE_COUNT
c_func
(paren
id|owner
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|bdev-&gt;bd_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|bdput
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|blkdev_get
r_int
id|blkdev_get
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
id|mode_t
id|mode
comma
r_int
id|flags
comma
r_int
id|kind
)paren
(brace
multiline_comment|/*&n;&t; * This crockload is due to bad choice of -&gt;open() type.&n;&t; * It will go away.&n;&t; * For now, block device -&gt;open() routine must _not_&n;&t; * examine anything in &squot;inode&squot; argument except -&gt;i_rdev.&n;&t; */
r_struct
id|file
id|fake_file
op_assign
(brace
)brace
suffix:semicolon
r_struct
id|dentry
id|fake_dentry
op_assign
(brace
)brace
suffix:semicolon
id|fake_file.f_mode
op_assign
id|mode
suffix:semicolon
id|fake_file.f_flags
op_assign
id|flags
suffix:semicolon
id|fake_file.f_dentry
op_assign
op_amp
id|fake_dentry
suffix:semicolon
id|fake_dentry.d_inode
op_assign
id|bdev-&gt;bd_inode
suffix:semicolon
r_return
id|do_open
c_func
(paren
id|bdev
comma
id|bdev-&gt;bd_inode
comma
op_amp
id|fake_file
)paren
suffix:semicolon
)brace
DECL|function|blkdev_open
r_int
id|blkdev_open
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
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
multiline_comment|/*&n;&t; * Preserve backwards compatibility and allow large file access&n;&t; * even if userspace doesn&squot;t ask for it explicitly. Some mkfs&n;&t; * binary needs it. We might want to drop this workaround&n;&t; * during an unstable branch.&n;&t; */
id|filp-&gt;f_flags
op_or_assign
id|O_LARGEFILE
suffix:semicolon
id|bd_acquire
c_func
(paren
id|inode
)paren
suffix:semicolon
id|bdev
op_assign
id|inode-&gt;i_bdev
suffix:semicolon
r_return
id|do_open
c_func
(paren
id|bdev
comma
id|inode
comma
id|filp
)paren
suffix:semicolon
)brace
DECL|function|blkdev_put
r_int
id|blkdev_put
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
id|kind
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_struct
id|inode
op_star
id|bd_inode
op_assign
id|bdev-&gt;bd_inode
suffix:semicolon
id|down
c_func
(paren
op_amp
id|bdev-&gt;bd_sem
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|kind
)paren
(brace
r_case
id|BDEV_FILE
suffix:colon
r_case
id|BDEV_FS
suffix:colon
id|sync_blockdev
c_func
(paren
id|bd_inode-&gt;i_bdev
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|bdev-&gt;bd_openers
)paren
id|kill_bdev
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bdev-&gt;bd_op-&gt;release
)paren
id|ret
op_assign
id|bdev-&gt;bd_op
op_member_access_from_pointer
id|release
c_func
(paren
id|bd_inode
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bdev-&gt;bd_op-&gt;owner
)paren
id|__MOD_DEC_USE_COUNT
c_func
(paren
id|bdev-&gt;bd_op-&gt;owner
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bdev-&gt;bd_openers
)paren
(brace
id|bdev-&gt;bd_op
op_assign
l_int|NULL
suffix:semicolon
id|bdev-&gt;bd_queue
op_assign
l_int|NULL
suffix:semicolon
id|bdev-&gt;bd_inode-&gt;i_data.backing_dev_info
op_assign
op_amp
id|default_backing_dev_info
suffix:semicolon
r_if
c_cond
(paren
id|bdev
op_ne
id|bdev-&gt;bd_contains
)paren
(brace
id|blkdev_put
c_func
(paren
id|bdev-&gt;bd_contains
comma
id|BDEV_RAW
)paren
suffix:semicolon
id|bdev-&gt;bd_contains
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|bdev-&gt;bd_sem
)paren
suffix:semicolon
id|bdput
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|blkdev_close
r_int
id|blkdev_close
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
r_return
id|blkdev_put
c_func
(paren
id|inode-&gt;i_bdev
comma
id|BDEV_FILE
)paren
suffix:semicolon
)brace
DECL|function|blkdev_ioctl
r_static
r_int
id|blkdev_ioctl
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
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|BLKRAGET
suffix:colon
r_case
id|BLKFRAGET
suffix:colon
r_case
id|BLKRASET
suffix:colon
r_case
id|BLKFRASET
suffix:colon
id|ret
op_assign
id|blk_ioctl
c_func
(paren
id|inode-&gt;i_bdev
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|inode-&gt;i_bdev-&gt;bd_op-&gt;ioctl
)paren
id|ret
op_assign
id|inode-&gt;i_bdev-&gt;bd_op
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|inode
comma
id|file
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|def_blk_aops
r_struct
id|address_space_operations
id|def_blk_aops
op_assign
(brace
id|readpage
suffix:colon
id|blkdev_readpage
comma
id|writepage
suffix:colon
id|blkdev_writepage
comma
id|sync_page
suffix:colon
id|block_sync_page
comma
id|prepare_write
suffix:colon
id|blkdev_prepare_write
comma
id|commit_write
suffix:colon
id|blkdev_commit_write
comma
id|writepages
suffix:colon
id|generic_writepages
comma
id|vm_writeback
suffix:colon
id|generic_vm_writeback
comma
id|direct_IO
suffix:colon
id|blkdev_direct_IO
comma
)brace
suffix:semicolon
DECL|variable|def_blk_fops
r_struct
id|file_operations
id|def_blk_fops
op_assign
(brace
id|open
suffix:colon
id|blkdev_open
comma
id|release
suffix:colon
id|blkdev_close
comma
id|llseek
suffix:colon
id|block_llseek
comma
id|read
suffix:colon
id|generic_file_read
comma
id|write
suffix:colon
id|generic_file_write
comma
id|mmap
suffix:colon
id|generic_file_mmap
comma
id|fsync
suffix:colon
id|block_fsync
comma
id|ioctl
suffix:colon
id|blkdev_ioctl
comma
)brace
suffix:semicolon
DECL|function|__bdevname
r_const
r_char
op_star
id|__bdevname
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_static
r_char
id|buffer
(braket
l_int|32
)braket
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|blkdevs
(braket
id|major
c_func
(paren
id|dev
)paren
)braket
dot
id|name
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
id|name
op_assign
l_string|&quot;unknown-block&quot;
suffix:semicolon
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%s(%d,%d)&quot;
comma
id|name
comma
id|major
c_func
(paren
id|dev
)paren
comma
id|minor
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
eof
