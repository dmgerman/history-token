macro_line|#ifndef _VXFS_KCOMPAT_H
DECL|macro|_VXFS_KCOMPAT_H
mdefine_line|#define _VXFS_KCOMPAT_H
macro_line|#include &lt;linux/version.h&gt;
macro_line|#if (LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,0))
macro_line|#include &lt;linux/blkdev.h&gt;
DECL|typedef|sector_t
r_typedef
r_int
id|sector_t
suffix:semicolon
multiline_comment|/* From include/linux/fs.h (Linux 2.5.2-pre3)  */
DECL|function|sb_bread
r_static
r_inline
r_struct
id|buffer_head
op_star
id|sb_bread
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|block
)paren
(brace
r_return
id|bread
c_func
(paren
id|sb-&gt;s_dev
comma
id|block
comma
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
)brace
multiline_comment|/* Dito.  */
DECL|function|map_bh
r_static
r_inline
r_void
id|map_bh
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|block
)paren
(brace
id|bh-&gt;b_state
op_or_assign
l_int|1
op_lshift
id|BH_Mapped
suffix:semicolon
id|bh-&gt;b_dev
op_assign
id|sb-&gt;s_dev
suffix:semicolon
id|bh-&gt;b_blocknr
op_assign
id|block
suffix:semicolon
)brace
multiline_comment|/* From fs/block_dev.c (Linux 2.5.2-pre2)  */
DECL|function|sb_set_blocksize
r_static
r_inline
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
id|sb-&gt;s_dev
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
multiline_comment|/* Dito.  */
DECL|function|sb_min_blocksize
r_static
r_inline
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
id|get_hardsect_size
c_func
(paren
id|sb-&gt;s_dev
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
macro_line|#endif /* Kernel 2.4 */
macro_line|#endif /* _VXFS_KCOMPAT_H */
eof