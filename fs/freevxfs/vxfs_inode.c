multiline_comment|/*&n; * Copyright (c) 2000-2001 Christoph Hellwig.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;).&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#ident &quot;$Id: vxfs_inode.c,v 1.42 2002/01/02 23:51:36 hch Exp hch $&quot;
multiline_comment|/*&n; * Veritas filesystem driver - inode routines.&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;vxfs.h&quot;
macro_line|#include &quot;vxfs_inode.h&quot;
macro_line|#include &quot;vxfs_extern.h&quot;
r_extern
r_struct
id|address_space_operations
id|vxfs_aops
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|vxfs_immed_aops
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|vxfs_immed_symlink_iops
suffix:semicolon
DECL|variable|vxfs_file_operations
r_static
r_struct
id|file_operations
id|vxfs_file_operations
op_assign
(brace
dot
id|open
op_assign
id|generic_file_open
comma
dot
id|llseek
op_assign
id|generic_file_llseek
comma
dot
id|read
op_assign
id|generic_file_read
comma
dot
id|mmap
op_assign
id|generic_file_mmap
comma
dot
id|sendfile
op_assign
id|generic_file_sendfile
comma
)brace
suffix:semicolon
DECL|variable|vxfs_inode_cachep
id|kmem_cache_t
op_star
id|vxfs_inode_cachep
suffix:semicolon
macro_line|#ifdef DIAGNOSTIC
multiline_comment|/*&n; * Dump inode contents (partially).&n; */
r_void
DECL|function|vxfs_dumpi
id|vxfs_dumpi
c_func
(paren
r_struct
id|vxfs_inode_info
op_star
id|vip
comma
id|ino_t
id|ino
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ino
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;dumping vxfs inode %ld&bslash;n&quot;
comma
id|ino
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;dumping unknown vxfs inode&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;---------------------------&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;mode is %x&bslash;n&quot;
comma
id|vip-&gt;vii_mode
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;nlink:%u, uid:%u, gid:%u&bslash;n&quot;
comma
id|vip-&gt;vii_nlink
comma
id|vip-&gt;vii_uid
comma
id|vip-&gt;vii_gid
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;size:%Lx, blocks:%u&bslash;n&quot;
comma
id|vip-&gt;vii_size
comma
id|vip-&gt;vii_blocks
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;orgtype:%u&bslash;n&quot;
comma
id|vip-&gt;vii_orgtype
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/**&n; * vxfs_blkiget - find inode based on extent #&n; * @sbp:&t;superblock of the filesystem we search in&n; * @extent:&t;number of the extent to search&n; * @ino:&t;inode number to search&n; *&n; * Description:&n; *  vxfs_blkiget searches inode @ino in the filesystem described by&n; *  @sbp in the extent @extent.&n; *  Returns the matching VxFS inode on success, else a NULL pointer.&n; *&n; * NOTE:&n; *  While __vxfs_iget uses the pagecache vxfs_blkiget uses the&n; *  buffercache.  This function should not be used outside the&n; *  read_super() method, otherwise the data may be incoherent.&n; */
r_struct
id|vxfs_inode_info
op_star
DECL|function|vxfs_blkiget
id|vxfs_blkiget
c_func
(paren
r_struct
id|super_block
op_star
id|sbp
comma
id|u_long
id|extent
comma
id|ino_t
id|ino
)paren
(brace
r_struct
id|buffer_head
op_star
id|bp
suffix:semicolon
id|u_long
id|block
comma
id|offset
suffix:semicolon
id|block
op_assign
id|extent
op_plus
(paren
(paren
id|ino
op_star
id|VXFS_ISIZE
)paren
op_div
id|sbp-&gt;s_blocksize
)paren
suffix:semicolon
id|offset
op_assign
(paren
(paren
id|ino
op_mod
(paren
id|sbp-&gt;s_blocksize
op_div
id|VXFS_ISIZE
)paren
)paren
op_star
id|VXFS_ISIZE
)paren
suffix:semicolon
id|bp
op_assign
id|sb_bread
c_func
(paren
id|sbp
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer_mapped
c_func
(paren
id|bp
)paren
)paren
(brace
r_struct
id|vxfs_inode_info
op_star
id|vip
suffix:semicolon
r_struct
id|vxfs_dinode
op_star
id|dip
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|vip
op_assign
id|kmem_cache_alloc
c_func
(paren
id|vxfs_inode_cachep
comma
id|SLAB_KERNEL
)paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|dip
op_assign
(paren
r_struct
id|vxfs_dinode
op_star
)paren
(paren
id|bp-&gt;b_data
op_plus
id|offset
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|vip
comma
id|dip
comma
r_sizeof
(paren
op_star
id|vip
)paren
)paren
suffix:semicolon
macro_line|#ifdef DIAGNOSTIC
id|vxfs_dumpi
c_func
(paren
id|vip
comma
id|ino
)paren
suffix:semicolon
macro_line|#endif
id|brelse
c_func
(paren
id|bp
)paren
suffix:semicolon
r_return
(paren
id|vip
)paren
suffix:semicolon
)brace
id|fail
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;vxfs: unable to read block %ld&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bp
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; * __vxfs_iget - generic find inode facility&n; * @sbp:&t;&t;VFS superblock&n; * @ino:&t;&t;inode number&n; * @ilistp:&t;&t;inode list&n; *&n; * Description:&n; *  Search the for inode number @ino in the filesystem&n; *  described by @sbp.  Use the specified inode table (@ilistp).&n; *  Returns the matching VxFS inode on success, else a NULL pointer.&n; */
r_static
r_struct
id|vxfs_inode_info
op_star
DECL|function|__vxfs_iget
id|__vxfs_iget
c_func
(paren
id|ino_t
id|ino
comma
r_struct
id|inode
op_star
id|ilistp
)paren
(brace
r_struct
id|page
op_star
id|pp
suffix:semicolon
id|u_long
id|offset
suffix:semicolon
id|offset
op_assign
(paren
id|ino
op_mod
(paren
id|PAGE_SIZE
op_div
id|VXFS_ISIZE
)paren
)paren
op_star
id|VXFS_ISIZE
suffix:semicolon
id|pp
op_assign
id|vxfs_get_page
c_func
(paren
id|ilistp-&gt;i_mapping
comma
id|ino
op_star
id|VXFS_ISIZE
op_div
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|pp
)paren
)paren
(brace
r_struct
id|vxfs_inode_info
op_star
id|vip
suffix:semicolon
r_struct
id|vxfs_dinode
op_star
id|dip
suffix:semicolon
id|caddr_t
id|kaddr
op_assign
(paren
r_char
op_star
)paren
id|page_address
c_func
(paren
id|pp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|vip
op_assign
id|kmem_cache_alloc
c_func
(paren
id|vxfs_inode_cachep
comma
id|SLAB_KERNEL
)paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|dip
op_assign
(paren
r_struct
id|vxfs_dinode
op_star
)paren
(paren
id|kaddr
op_plus
id|offset
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|vip
comma
id|dip
comma
r_sizeof
(paren
op_star
id|vip
)paren
)paren
suffix:semicolon
macro_line|#ifdef DIAGNOSTIC
id|vxfs_dumpi
c_func
(paren
id|vip
comma
id|ino
)paren
suffix:semicolon
macro_line|#endif
id|vxfs_put_page
c_func
(paren
id|pp
)paren
suffix:semicolon
r_return
(paren
id|vip
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;vxfs: error on page %p&bslash;n&quot;
comma
id|pp
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
id|fail
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;vxfs: unable to read inode %ld&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|ino
)paren
suffix:semicolon
id|vxfs_put_page
c_func
(paren
id|pp
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; * vxfs_stiget - find inode using the structural inode list&n; * @sbp:&t;VFS superblock&n; * @ino:&t;inode #&n; *&n; * Description:&n; *  Find inode @ino in the filesystem described by @sbp using&n; *  the structural inode list.&n; *  Returns the matching VxFS inode on success, else a NULL pointer.&n; */
r_struct
id|vxfs_inode_info
op_star
DECL|function|vxfs_stiget
id|vxfs_stiget
c_func
(paren
r_struct
id|super_block
op_star
id|sbp
comma
id|ino_t
id|ino
)paren
(brace
r_return
id|__vxfs_iget
c_func
(paren
id|ino
comma
id|VXFS_SBI
c_func
(paren
id|sbp
)paren
op_member_access_from_pointer
id|vsi_stilist
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * vxfs_transmod - mode for a VxFS inode&n; * @vip:&t;VxFS inode&n; *&n; * Description:&n; *  vxfs_transmod returns a Linux mode_t for a given&n; *  VxFS inode structure.&n; */
r_static
id|__inline__
id|mode_t
DECL|function|vxfs_transmod
id|vxfs_transmod
c_func
(paren
r_struct
id|vxfs_inode_info
op_star
id|vip
)paren
(brace
id|mode_t
id|ret
op_assign
id|vip-&gt;vii_mode
op_amp
op_complement
id|VXFS_TYPE_MASK
suffix:semicolon
r_if
c_cond
(paren
id|VXFS_ISFIFO
c_func
(paren
id|vip
)paren
)paren
id|ret
op_or_assign
id|S_IFIFO
suffix:semicolon
r_if
c_cond
(paren
id|VXFS_ISCHR
c_func
(paren
id|vip
)paren
)paren
id|ret
op_or_assign
id|S_IFCHR
suffix:semicolon
r_if
c_cond
(paren
id|VXFS_ISDIR
c_func
(paren
id|vip
)paren
)paren
id|ret
op_or_assign
id|S_IFDIR
suffix:semicolon
r_if
c_cond
(paren
id|VXFS_ISBLK
c_func
(paren
id|vip
)paren
)paren
id|ret
op_or_assign
id|S_IFBLK
suffix:semicolon
r_if
c_cond
(paren
id|VXFS_ISLNK
c_func
(paren
id|vip
)paren
)paren
id|ret
op_or_assign
id|S_IFLNK
suffix:semicolon
r_if
c_cond
(paren
id|VXFS_ISREG
c_func
(paren
id|vip
)paren
)paren
id|ret
op_or_assign
id|S_IFREG
suffix:semicolon
r_if
c_cond
(paren
id|VXFS_ISSOC
c_func
(paren
id|vip
)paren
)paren
id|ret
op_or_assign
id|S_IFSOCK
suffix:semicolon
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * vxfs_iinit- helper to fill inode fields&n; * @ip:&t;&t;VFS inode&n; * @vip:&t;VxFS inode&n; *&n; * Description:&n; *  vxfs_instino is a helper function to fill in all relevant&n; *  fields in @ip from @vip.&n; */
r_static
r_void
DECL|function|vxfs_iinit
id|vxfs_iinit
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
r_struct
id|vxfs_inode_info
op_star
id|vip
)paren
(brace
id|ip-&gt;i_mode
op_assign
id|vxfs_transmod
c_func
(paren
id|vip
)paren
suffix:semicolon
id|ip-&gt;i_uid
op_assign
(paren
id|uid_t
)paren
id|vip-&gt;vii_uid
suffix:semicolon
id|ip-&gt;i_gid
op_assign
(paren
id|gid_t
)paren
id|vip-&gt;vii_gid
suffix:semicolon
id|ip-&gt;i_nlink
op_assign
id|vip-&gt;vii_nlink
suffix:semicolon
id|ip-&gt;i_size
op_assign
id|vip-&gt;vii_size
suffix:semicolon
id|ip-&gt;i_atime.tv_sec
op_assign
id|vip-&gt;vii_atime
suffix:semicolon
id|ip-&gt;i_ctime.tv_sec
op_assign
id|vip-&gt;vii_ctime
suffix:semicolon
id|ip-&gt;i_mtime.tv_sec
op_assign
id|vip-&gt;vii_mtime
suffix:semicolon
id|ip-&gt;i_atime.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|ip-&gt;i_ctime.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|ip-&gt;i_mtime.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|ip-&gt;i_blksize
op_assign
id|PAGE_SIZE
suffix:semicolon
id|ip-&gt;i_blocks
op_assign
id|vip-&gt;vii_blocks
suffix:semicolon
id|ip-&gt;i_generation
op_assign
id|vip-&gt;vii_gen
suffix:semicolon
id|ip-&gt;u.generic_ip
op_assign
(paren
r_void
op_star
)paren
id|vip
suffix:semicolon
)brace
multiline_comment|/**&n; * vxfs_get_fake_inode - get fake inode structure&n; * @sbp:&t;&t;filesystem superblock&n; * @vip:&t;&t;fspriv inode&n; *&n; * Description:&n; *  vxfs_fake_inode gets a fake inode (not in the inode hash) for a&n; *  superblock, vxfs_inode pair.&n; *  Returns the filled VFS inode.&n; */
r_struct
id|inode
op_star
DECL|function|vxfs_get_fake_inode
id|vxfs_get_fake_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sbp
comma
r_struct
id|vxfs_inode_info
op_star
id|vip
)paren
(brace
r_struct
id|inode
op_star
id|ip
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ip
op_assign
id|new_inode
c_func
(paren
id|sbp
)paren
)paren
)paren
(brace
id|vxfs_iinit
c_func
(paren
id|ip
comma
id|vip
)paren
suffix:semicolon
id|ip-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|vxfs_aops
suffix:semicolon
)brace
r_return
(paren
id|ip
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * vxfs_put_fake_inode - free faked inode&n; * *ip:&t;&t;&t;VFS inode&n; *&n; * Description:&n; *  vxfs_put_fake_inode frees all data asssociated with @ip.&n; */
r_void
DECL|function|vxfs_put_fake_inode
id|vxfs_put_fake_inode
c_func
(paren
r_struct
id|inode
op_star
id|ip
)paren
(brace
id|iput
c_func
(paren
id|ip
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * vxfs_read_inode - fill in inode information&n; * @ip:&t;&t;inode pointer to fill&n; *&n; * Description:&n; *  vxfs_read_inode reads the disk inode for @ip and fills&n; *  in all relevant fields in @ip.&n; */
r_void
DECL|function|vxfs_read_inode
id|vxfs_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|ip
)paren
(brace
r_struct
id|super_block
op_star
id|sbp
op_assign
id|ip-&gt;i_sb
suffix:semicolon
r_struct
id|vxfs_inode_info
op_star
id|vip
suffix:semicolon
r_struct
id|address_space_operations
op_star
id|aops
suffix:semicolon
id|ino_t
id|ino
op_assign
id|ip-&gt;i_ino
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|vip
op_assign
id|__vxfs_iget
c_func
(paren
id|ino
comma
id|VXFS_SBI
c_func
(paren
id|sbp
)paren
op_member_access_from_pointer
id|vsi_ilist
)paren
)paren
)paren
r_return
suffix:semicolon
id|vxfs_iinit
c_func
(paren
id|ip
comma
id|vip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|VXFS_ISIMMED
c_func
(paren
id|vip
)paren
)paren
id|aops
op_assign
op_amp
id|vxfs_immed_aops
suffix:semicolon
r_else
id|aops
op_assign
op_amp
id|vxfs_aops
suffix:semicolon
r_if
c_cond
(paren
id|S_ISREG
c_func
(paren
id|ip-&gt;i_mode
)paren
)paren
(brace
id|ip-&gt;i_fop
op_assign
op_amp
id|vxfs_file_operations
suffix:semicolon
id|ip-&gt;i_mapping-&gt;a_ops
op_assign
id|aops
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|ip-&gt;i_mode
)paren
)paren
(brace
id|ip-&gt;i_op
op_assign
op_amp
id|vxfs_dir_inode_ops
suffix:semicolon
id|ip-&gt;i_fop
op_assign
op_amp
id|vxfs_dir_operations
suffix:semicolon
id|ip-&gt;i_mapping-&gt;a_ops
op_assign
id|aops
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|ip-&gt;i_mode
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|VXFS_ISIMMED
c_func
(paren
id|vip
)paren
)paren
(brace
id|ip-&gt;i_op
op_assign
op_amp
id|page_symlink_inode_operations
suffix:semicolon
id|ip-&gt;i_mapping-&gt;a_ops
op_assign
op_amp
id|vxfs_aops
suffix:semicolon
)brace
r_else
id|ip-&gt;i_op
op_assign
op_amp
id|vxfs_immed_symlink_iops
suffix:semicolon
)brace
r_else
id|init_special_inode
c_func
(paren
id|ip
comma
id|ip-&gt;i_mode
comma
id|old_decode_dev
c_func
(paren
id|vip-&gt;vii_rdev
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; * vxfs_put_inode - remove inode from main memory&n; * @ip:&t;&t;inode to discard.&n; *&n; * Description:&n; *  vxfs_put_inode() is called on each iput.  If we are the last&n; *  link in memory, free the fspriv inode area.&n; */
r_void
DECL|function|vxfs_put_inode
id|vxfs_put_inode
c_func
(paren
r_struct
id|inode
op_star
id|ip
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|ip-&gt;i_count
)paren
op_eq
l_int|1
)paren
id|kmem_cache_free
c_func
(paren
id|vxfs_inode_cachep
comma
id|ip-&gt;u.generic_ip
)paren
suffix:semicolon
)brace
eof
