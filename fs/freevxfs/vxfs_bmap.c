multiline_comment|/*&n; * Copyright (c) 2000-2001 Christoph Hellwig.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;).&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#ident &quot;$Id: vxfs_bmap.c,v 1.20 2001/04/25 18:11:23 hch Exp hch $&quot;
multiline_comment|/*&n; * Veritas filesystem driver - filesystem to disk block mapping.&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &quot;vxfs.h&quot;
macro_line|#include &quot;vxfs_inode.h&quot;
macro_line|#ifdef DIAGNOSTIC
r_static
r_void
DECL|function|vxfs_typdump
id|vxfs_typdump
c_func
(paren
r_struct
id|vxfs_typed
op_star
id|typ
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;type=%Lu &quot;
comma
id|typ-&gt;vt_hdr
op_rshift
id|VXFS_TYPED_TYPESHIFT
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;offset=%Lx &quot;
comma
id|typ-&gt;vt_hdr
op_amp
id|VXFS_TYPED_OFFSETMASK
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;block=%x &quot;
comma
id|typ-&gt;vt_block
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;size=%x&bslash;n&quot;
comma
id|typ-&gt;vt_size
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/**&n; * vxfs_bmap_ext4 - do bmap for ext4 extents&n; * @ip:&t;&t;pointer to the inode we do bmap for&n; * @iblock:&t;logical block.&n; *&n; * Description:&n; *   vxfs_bmap_ext4 performs the bmap operation for inodes with&n; *   ext4-style extents (which are much like the traditional UNIX&n; *   inode organisation).&n; *&n; * Returns:&n; *   The physical block number on success, else Zero.&n; */
r_static
id|daddr_t
DECL|function|vxfs_bmap_ext4
id|vxfs_bmap_ext4
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
r_int
id|iblock
)paren
(brace
r_struct
id|vxfs_inode_info
op_star
id|vip
op_assign
id|VXFS_INO
c_func
(paren
id|ip
)paren
suffix:semicolon
r_struct
id|super_block
op_star
id|sbp
op_assign
id|ip-&gt;i_sb
suffix:semicolon
id|kdev_t
id|dev
op_assign
id|ip-&gt;i_dev
suffix:semicolon
id|u_long
id|bsize
op_assign
id|sbp-&gt;s_blocksize
suffix:semicolon
id|u_long
id|size
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
id|VXFS_NDADDR
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|direct
op_star
id|dp
op_assign
id|vip-&gt;vii_ext4.ve4_direct
op_plus
id|i
suffix:semicolon
macro_line|#ifdef DIAGNOSTIC
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;iblock: %ld, %d (size: %lu)&bslash;n&quot;
comma
id|iblock
comma
id|i
comma
id|size
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;dp-&gt;extent: %d, dp-&gt;size: %d&bslash;n&quot;
comma
id|dp-&gt;extent
comma
id|dp-&gt;size
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|iblock
op_ge
id|size
op_logical_and
id|iblock
OL
(paren
id|size
op_plus
id|dp-&gt;size
)paren
)paren
r_return
(paren
(paren
id|iblock
op_minus
id|size
)paren
op_plus
id|dp-&gt;extent
)paren
suffix:semicolon
id|size
op_add_assign
id|dp-&gt;size
suffix:semicolon
)brace
id|iblock
op_sub_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|iblock
op_div
(paren
id|vip-&gt;vii_ext4.ve4_indsize
op_star
id|vip-&gt;vii_ext4.ve4_indsize
op_star
id|bsize
op_rshift
l_int|2
)paren
)paren
)paren
(brace
r_struct
id|buffer_head
op_star
id|bp
suffix:semicolon
id|daddr_t
id|pblock
suffix:semicolon
multiline_comment|/*&n;&t;&t; * XXX: is the second indir only used for&n;&t;&t; *&t;double indirect extents?&n;&t;&t; */
id|bp
op_assign
id|bread
c_func
(paren
id|dev
comma
id|vip-&gt;vii_ext4.ve4_indir
(braket
l_int|0
)braket
comma
id|bsize
op_star
(paren
(paren
id|vip-&gt;vii_ext4.ve4_indsize
)paren
op_div
id|bsize
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|pblock
op_assign
op_star
(paren
id|bp-&gt;b_data
op_plus
(paren
(paren
id|iblock
op_div
id|vip-&gt;vii_ext4.ve4_indsize
)paren
op_mod
(paren
id|vip-&gt;vii_ext4.ve4_indsize
op_star
id|bsize
)paren
)paren
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bp
)paren
suffix:semicolon
r_return
(paren
id|pblock
op_plus
(paren
id|iblock
op_mod
id|vip-&gt;vii_ext4.ve4_indsize
)paren
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;no matching indir?&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * vxfs_bmap_indir - recursion for vxfs_bmap_typed&n; * @ip:&t;&t;pointer to the inode we do bmap for&n; * @indir:&t;indirect block we start reading at&n; * @size:&t;size of the typed area to search&n; * @block:&t;partially result from further searches&n; *&n; * Description:&n; *   vxfs_bmap_indir reads a &amp;struct vxfs_typed at @indir&n; *   and performs the type-defined action.&n; *&n; * Return Value:&n; *   The physical block number on success, else Zero.&n; *&n; * Note:&n; *   Kernelstack is rare.  Unrecurse?&n; */
r_static
id|daddr_t
DECL|function|vxfs_bmap_indir
id|vxfs_bmap_indir
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
r_int
id|indir
comma
r_int
id|size
comma
r_int
id|block
)paren
(brace
r_struct
id|buffer_head
op_star
id|bp
op_assign
l_int|NULL
suffix:semicolon
id|daddr_t
id|pblock
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
id|size
op_star
id|VXFS_TYPED_PER_BLOCK
c_func
(paren
id|ip-&gt;i_sb
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|vxfs_typed
op_star
id|typ
suffix:semicolon
id|u_int64_t
id|off
suffix:semicolon
id|bp
op_assign
id|bread
c_func
(paren
id|ip-&gt;i_dev
comma
id|indir
op_plus
(paren
id|i
op_div
id|VXFS_TYPED_PER_BLOCK
c_func
(paren
id|ip-&gt;i_sb
)paren
)paren
comma
id|ip-&gt;i_sb-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer_mapped
c_func
(paren
id|bp
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|typ
op_assign
(paren
(paren
r_struct
id|vxfs_typed
op_star
)paren
id|bp-&gt;b_data
)paren
op_plus
(paren
id|i
op_mod
id|VXFS_TYPED_PER_BLOCK
c_func
(paren
id|ip-&gt;i_sb
)paren
)paren
suffix:semicolon
id|off
op_assign
(paren
id|typ-&gt;vt_hdr
op_amp
id|VXFS_TYPED_OFFSETMASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
OL
id|off
)paren
(brace
id|brelse
c_func
(paren
id|bp
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_switch
c_cond
(paren
(paren
id|u_int32_t
)paren
(paren
id|typ-&gt;vt_hdr
op_rshift
id|VXFS_TYPED_TYPESHIFT
)paren
)paren
(brace
r_case
id|VXFS_TYPED_INDIRECT
suffix:colon
id|pblock
op_assign
id|vxfs_bmap_indir
c_func
(paren
id|ip
comma
id|typ-&gt;vt_block
comma
id|typ-&gt;vt_size
comma
id|block
op_minus
id|off
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pblock
op_eq
op_minus
l_int|2
)paren
r_break
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|VXFS_TYPED_DATA
suffix:colon
r_if
c_cond
(paren
(paren
id|block
op_minus
id|off
)paren
op_ge
id|typ-&gt;vt_size
)paren
r_break
suffix:semicolon
id|pblock
op_assign
(paren
id|typ-&gt;vt_block
op_plus
id|block
op_minus
id|off
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|VXFS_TYPED_INDIRECT_DEV4
suffix:colon
r_case
id|VXFS_TYPED_DATA_DEV4
suffix:colon
(brace
r_struct
id|vxfs_typed_dev4
op_star
id|typ4
op_assign
(paren
r_struct
id|vxfs_typed_dev4
op_star
)paren
id|typ
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;&bslash;n&bslash;nTYPED_DEV4 detected!&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;block: %Ld&bslash;tsize: %Ld&bslash;tdev: %d&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|typ4-&gt;vd4_block
comma
(paren
r_int
r_int
)paren
id|typ4-&gt;vd4_size
comma
id|typ4-&gt;vd4_dev
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bp
)paren
suffix:semicolon
)brace
id|fail
suffix:colon
id|pblock
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|brelse
c_func
(paren
id|bp
)paren
suffix:semicolon
r_return
(paren
id|pblock
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * vxfs_bmap_typed - bmap for typed extents&n; * @ip:&t;&t;pointer to the inode we do bmap for&n; * @iblock:&t;logical block&n; *&n; * Description:&n; *   Performs the bmap operation for typed extents.&n; *&n; * Return Value:&n; *   The physical block number on success, else Zero.&n; */
r_static
id|daddr_t
DECL|function|vxfs_bmap_typed
id|vxfs_bmap_typed
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
r_int
id|iblock
)paren
(brace
r_struct
id|vxfs_inode_info
op_star
id|vip
op_assign
id|VXFS_INO
c_func
(paren
id|ip
)paren
suffix:semicolon
id|daddr_t
id|pblock
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
id|VXFS_NTYPED
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|vxfs_typed
op_star
id|typ
op_assign
id|vip-&gt;vii_org.typed
op_plus
id|i
suffix:semicolon
id|u_int64_t
id|off
op_assign
(paren
id|typ-&gt;vt_hdr
op_amp
id|VXFS_TYPED_OFFSETMASK
)paren
suffix:semicolon
macro_line|#ifdef DIAGNOSTIC
id|vxfs_typdump
c_func
(paren
id|typ
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|iblock
OL
id|off
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|u_int32_t
)paren
(paren
id|typ-&gt;vt_hdr
op_rshift
id|VXFS_TYPED_TYPESHIFT
)paren
)paren
(brace
r_case
id|VXFS_TYPED_INDIRECT
suffix:colon
id|pblock
op_assign
id|vxfs_bmap_indir
c_func
(paren
id|ip
comma
id|typ-&gt;vt_block
comma
id|typ-&gt;vt_size
comma
id|iblock
op_minus
id|off
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pblock
op_eq
op_minus
l_int|2
)paren
r_break
suffix:semicolon
r_return
(paren
id|pblock
)paren
suffix:semicolon
r_case
id|VXFS_TYPED_DATA
suffix:colon
r_if
c_cond
(paren
(paren
id|iblock
op_minus
id|off
)paren
OL
id|typ-&gt;vt_size
)paren
r_return
(paren
id|typ-&gt;vt_block
op_plus
id|iblock
op_minus
id|off
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VXFS_TYPED_INDIRECT_DEV4
suffix:colon
r_case
id|VXFS_TYPED_DATA_DEV4
suffix:colon
(brace
r_struct
id|vxfs_typed_dev4
op_star
id|typ4
op_assign
(paren
r_struct
id|vxfs_typed_dev4
op_star
)paren
id|typ
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;&bslash;n&bslash;nTYPED_DEV4 detected!&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;block: %Ld&bslash;tsize: %Ld&bslash;tdev: %d&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|typ4-&gt;vd4_block
comma
(paren
r_int
r_int
)paren
id|typ4-&gt;vd4_size
comma
id|typ4-&gt;vd4_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * vxfs_bmap1 - vxfs-internal bmap operation&n; * @ip:&t;&t;&t;pointer to the inode we do bmap for&n; * @iblock:&t;&t;logical block&n; *&n; * Description:&n; *   vxfs_bmap1 perfoms a logical to physical block mapping&n; *   for vxfs-internal purposes.&n; *&n; * Return Value:&n; *   The physical block number on success, else Zero.&n; */
id|daddr_t
DECL|function|vxfs_bmap1
id|vxfs_bmap1
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
r_int
id|iblock
)paren
(brace
r_struct
id|vxfs_inode_info
op_star
id|vip
op_assign
id|VXFS_INO
c_func
(paren
id|ip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|VXFS_ISEXT4
c_func
(paren
id|vip
)paren
)paren
r_return
id|vxfs_bmap_ext4
c_func
(paren
id|ip
comma
id|iblock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|VXFS_ISTYPED
c_func
(paren
id|vip
)paren
)paren
r_return
id|vxfs_bmap_typed
c_func
(paren
id|ip
comma
id|iblock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|VXFS_ISNONE
c_func
(paren
id|vip
)paren
)paren
r_goto
id|unsupp
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
r_goto
id|unsupp
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;vxfs: inode %ld has no valid orgtype (%x)&bslash;n&quot;
comma
id|ip-&gt;i_ino
comma
id|vip-&gt;vii_orgtype
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|unsupp
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;vxfs: inode %ld has an unsupported orgtype (%x)&bslash;n&quot;
comma
id|ip-&gt;i_ino
comma
id|vip-&gt;vii_orgtype
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
