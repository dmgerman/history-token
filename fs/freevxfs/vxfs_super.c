multiline_comment|/*&n; * Copyright (c) 2000-2001 Christoph Hellwig.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;).&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#ident &quot;$Id: vxfs_super.c,v 1.29 2002/01/02 22:02:12 hch Exp hch $&quot;
multiline_comment|/*&n; * Veritas filesystem driver - superblock related routines.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &quot;vxfs.h&quot;
macro_line|#include &quot;vxfs_extern.h&quot;
macro_line|#include &quot;vxfs_dir.h&quot;
macro_line|#include &quot;vxfs_inode.h&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Christoph Hellwig&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Veritas Filesystem (VxFS) driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;Dual BSD/GPL&quot;
)paren
suffix:semicolon
r_static
r_void
id|vxfs_put_super
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_static
r_int
id|vxfs_statfs
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|statfs
op_star
)paren
suffix:semicolon
DECL|variable|vxfs_super_ops
r_static
r_struct
id|super_operations
id|vxfs_super_ops
op_assign
(brace
dot
id|read_inode
op_assign
id|vxfs_read_inode
comma
dot
id|put_inode
op_assign
id|vxfs_put_inode
comma
dot
id|put_super
op_assign
id|vxfs_put_super
comma
dot
id|statfs
op_assign
id|vxfs_statfs
comma
)brace
suffix:semicolon
multiline_comment|/**&n; * vxfs_put_super - free superblock resources&n; * @sbp:&t;VFS superblock.&n; *&n; * Description:&n; *   vxfs_put_super frees all resources allocated for @sbp&n; *   after the last instance of the filesystem is unmounted.&n; */
r_static
r_void
DECL|function|vxfs_put_super
id|vxfs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sbp
)paren
(brace
r_struct
id|vxfs_sb_info
op_star
id|infp
op_assign
id|VXFS_SBI
c_func
(paren
id|sbp
)paren
suffix:semicolon
id|vxfs_put_fake_inode
c_func
(paren
id|infp-&gt;vsi_fship
)paren
suffix:semicolon
id|vxfs_put_fake_inode
c_func
(paren
id|infp-&gt;vsi_ilist
)paren
suffix:semicolon
id|vxfs_put_fake_inode
c_func
(paren
id|infp-&gt;vsi_stilist
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|infp-&gt;vsi_bp
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|infp
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * vxfs_statfs - get filesystem information&n; * @sbp:&t;VFS superblock&n; * @bufp:&t;output buffer&n; *&n; * Description:&n; *   vxfs_statfs fills the statfs buffer @bufp with information&n; *   about the filesystem described by @sbp.&n; *&n; * Returns:&n; *   Zero.&n; *&n; * Locking:&n; *   We are under bkl and @sbp-&gt;s_lock.&n; *&n; * Notes:&n; *   This is everything but complete...&n; */
r_static
r_int
DECL|function|vxfs_statfs
id|vxfs_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|sbp
comma
r_struct
id|statfs
op_star
id|bufp
)paren
(brace
r_struct
id|vxfs_sb_info
op_star
id|infp
op_assign
id|VXFS_SBI
c_func
(paren
id|sbp
)paren
suffix:semicolon
id|bufp-&gt;f_type
op_assign
id|VXFS_SUPER_MAGIC
suffix:semicolon
id|bufp-&gt;f_bsize
op_assign
id|sbp-&gt;s_blocksize
suffix:semicolon
id|bufp-&gt;f_blocks
op_assign
id|infp-&gt;vsi_raw-&gt;vs_dsize
suffix:semicolon
id|bufp-&gt;f_bfree
op_assign
id|infp-&gt;vsi_raw-&gt;vs_free
suffix:semicolon
id|bufp-&gt;f_bavail
op_assign
l_int|0
suffix:semicolon
id|bufp-&gt;f_files
op_assign
l_int|0
suffix:semicolon
id|bufp-&gt;f_ffree
op_assign
id|infp-&gt;vsi_raw-&gt;vs_ifree
suffix:semicolon
id|bufp-&gt;f_namelen
op_assign
id|VXFS_NAMELEN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * vxfs_read_super - read superblock into memory and initalize filesystem&n; * @sbp:&t;&t;VFS superblock (to fill)&n; * @dp:&t;&t;&t;fs private mount data&n; * @silent:&t;&t;do not complain loudly when sth is wrong&n; *&n; * Description:&n; *   We are called on the first mount of a filesystem to read the&n; *   superblock into memory and do some basic setup.&n; *&n; * Returns:&n; *   The superblock on success, else %NULL.&n; *&n; * Locking:&n; *   We are under the bkl and @sbp-&gt;s_lock.&n; */
DECL|function|vxfs_fill_super
r_static
r_int
id|vxfs_fill_super
c_func
(paren
r_struct
id|super_block
op_star
id|sbp
comma
r_void
op_star
id|dp
comma
r_int
id|silent
)paren
(brace
r_struct
id|vxfs_sb_info
op_star
id|infp
suffix:semicolon
r_struct
id|vxfs_sb
op_star
id|rsbp
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bp
op_assign
l_int|NULL
suffix:semicolon
id|u_long
id|bsize
suffix:semicolon
id|infp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|infp
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|infp
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;vxfs: unable to allocate incore superblock&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|infp
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|infp
)paren
)paren
suffix:semicolon
id|bsize
op_assign
id|sb_min_blocksize
c_func
(paren
id|sbp
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bsize
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;vxfs: unable to set blocksize&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|bp
op_assign
id|sb_bread
c_func
(paren
id|sbp
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bp
op_logical_or
op_logical_neg
id|buffer_mapped
c_func
(paren
id|bp
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;vxfs: unable to read disk superblock&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
id|rsbp
op_assign
(paren
r_struct
id|vxfs_sb
op_star
)paren
id|bp-&gt;b_data
suffix:semicolon
r_if
c_cond
(paren
id|rsbp-&gt;vs_magic
op_ne
id|VXFS_SUPER_MAGIC
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;vxfs: WRONG superblock magic&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|rsbp-&gt;vs_version
template_param
l_int|4
)paren
op_logical_and
op_logical_neg
id|silent
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;vxfs: unsupported VxFS version (%d)&bslash;n&quot;
comma
id|rsbp-&gt;vs_version
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
macro_line|#ifdef DIAGNOSTIC
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;vxfs: supported VxFS version (%d)&bslash;n&quot;
comma
id|rsbp-&gt;vs_version
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;vxfs: blocksize: %d&bslash;n&quot;
comma
id|rsbp-&gt;vs_bsize
)paren
suffix:semicolon
macro_line|#endif
id|sbp-&gt;s_magic
op_assign
id|rsbp-&gt;vs_magic
suffix:semicolon
id|sbp-&gt;u.generic_sbp
op_assign
(paren
r_void
op_star
)paren
id|infp
suffix:semicolon
id|infp-&gt;vsi_raw
op_assign
id|rsbp
suffix:semicolon
id|infp-&gt;vsi_bp
op_assign
id|bp
suffix:semicolon
id|infp-&gt;vsi_oltext
op_assign
id|rsbp-&gt;vs_oltext
(braket
l_int|0
)braket
suffix:semicolon
id|infp-&gt;vsi_oltsize
op_assign
id|rsbp-&gt;vs_oltsize
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb_set_blocksize
c_func
(paren
id|sbp
comma
id|rsbp-&gt;vs_bsize
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;vxfs: unable to set final block size&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vxfs_read_olt
c_func
(paren
id|sbp
comma
id|bsize
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;vxfs: unable to read olt&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vxfs_read_fshead
c_func
(paren
id|sbp
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;vxfs: unable to read fshead&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|sbp-&gt;s_op
op_assign
op_amp
id|vxfs_super_ops
suffix:semicolon
id|sbp-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|iget
c_func
(paren
id|sbp
comma
id|VXFS_ROOT_INO
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbp-&gt;s_root
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;vxfs: unable to get root dentry.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_free_ilist
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|out_free_ilist
suffix:colon
id|vxfs_put_fake_inode
c_func
(paren
id|infp-&gt;vsi_fship
)paren
suffix:semicolon
id|vxfs_put_fake_inode
c_func
(paren
id|infp-&gt;vsi_ilist
)paren
suffix:semicolon
id|vxfs_put_fake_inode
c_func
(paren
id|infp-&gt;vsi_stilist
)paren
suffix:semicolon
id|out
suffix:colon
id|brelse
c_func
(paren
id|bp
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|infp
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; * The usual module blurb.&n; */
DECL|function|vxfs_get_sb
r_static
r_struct
id|super_block
op_star
id|vxfs_get_sb
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
id|get_sb_bdev
c_func
(paren
id|fs_type
comma
id|flags
comma
id|dev_name
comma
id|data
comma
id|vxfs_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|vxfs_fs_type
r_static
r_struct
id|file_system_type
id|vxfs_fs_type
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|name
suffix:colon
l_string|&quot;vxfs&quot;
comma
id|get_sb
suffix:colon
id|vxfs_get_sb
comma
id|kill_sb
suffix:colon
id|kill_block_super
comma
id|fs_flags
suffix:colon
id|FS_REQUIRES_DEV
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|vxfs_init
id|vxfs_init
c_func
(paren
r_void
)paren
(brace
id|vxfs_inode_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;vxfs_inode&quot;
comma
r_sizeof
(paren
r_struct
id|vxfs_inode_info
)paren
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vxfs_inode_cachep
)paren
r_return
(paren
id|register_filesystem
c_func
(paren
op_amp
id|vxfs_fs_type
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|vxfs_cleanup
id|vxfs_cleanup
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|vxfs_fs_type
)paren
suffix:semicolon
id|kmem_cache_destroy
c_func
(paren
id|vxfs_inode_cachep
)paren
suffix:semicolon
)brace
DECL|variable|vxfs_init
id|module_init
c_func
(paren
id|vxfs_init
)paren
suffix:semicolon
DECL|variable|vxfs_cleanup
id|module_exit
c_func
(paren
id|vxfs_cleanup
)paren
suffix:semicolon
eof
