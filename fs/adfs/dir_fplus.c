multiline_comment|/*&n; *  linux/fs/adfs/dir_fplus.c&n; *&n; *  Copyright (C) 1997-1999 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/adfs_fs.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &quot;adfs.h&quot;
macro_line|#include &quot;dir_fplus.h&quot;
r_static
r_int
DECL|function|adfs_fplus_read
id|adfs_fplus_read
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|id
comma
r_int
r_int
id|sz
comma
r_struct
id|adfs_dir
op_star
id|dir
)paren
(brace
r_struct
id|adfs_bigdirheader
op_star
id|h
suffix:semicolon
r_struct
id|adfs_bigdirtail
op_star
id|t
suffix:semicolon
r_int
r_int
id|block
suffix:semicolon
r_int
r_int
id|blk
comma
id|size
suffix:semicolon
r_int
id|i
comma
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
id|dir-&gt;nr_buffers
op_assign
l_int|0
suffix:semicolon
id|block
op_assign
id|__adfs_block_map
c_func
(paren
id|sb
comma
id|id
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|block
)paren
(brace
id|adfs_error
c_func
(paren
id|sb
comma
l_string|&quot;dir object %X has a hole at offset 0&quot;
comma
id|id
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|dir-&gt;bh
(braket
l_int|0
)braket
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir-&gt;bh
(braket
l_int|0
)braket
)paren
r_goto
id|out
suffix:semicolon
id|dir-&gt;nr_buffers
op_add_assign
l_int|1
suffix:semicolon
id|h
op_assign
(paren
r_struct
id|adfs_bigdirheader
op_star
)paren
id|dir-&gt;bh
(braket
l_int|0
)braket
op_member_access_from_pointer
id|b_data
suffix:semicolon
id|size
op_assign
id|le32_to_cpu
c_func
(paren
id|h-&gt;bigdirsize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_ne
id|sz
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;adfs: adfs_fplus_read: directory header size&bslash;n&quot;
l_string|&quot; does not match directory size&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|h-&gt;bigdirversion
(braket
l_int|0
)braket
op_ne
l_int|0
op_logical_or
id|h-&gt;bigdirversion
(braket
l_int|1
)braket
op_ne
l_int|0
op_logical_or
id|h-&gt;bigdirversion
(braket
l_int|2
)braket
op_ne
l_int|0
op_logical_or
id|size
op_amp
l_int|2047
op_logical_or
id|h-&gt;bigdirstartname
op_ne
id|cpu_to_le32
c_func
(paren
id|BIGDIRSTARTNAME
)paren
)paren
r_goto
id|out
suffix:semicolon
id|size
op_rshift_assign
id|sb-&gt;s_blocksize_bits
suffix:semicolon
r_for
c_loop
(paren
id|blk
op_assign
l_int|1
suffix:semicolon
id|blk
OL
id|size
suffix:semicolon
id|blk
op_increment
)paren
(brace
id|block
op_assign
id|__adfs_block_map
c_func
(paren
id|sb
comma
id|id
comma
id|blk
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|block
)paren
(brace
id|adfs_error
c_func
(paren
id|sb
comma
l_string|&quot;dir object %X has a hole at offset %d&quot;
comma
id|id
comma
id|blk
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|dir-&gt;bh
(braket
id|blk
)braket
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir-&gt;bh
(braket
id|blk
)braket
)paren
r_goto
id|out
suffix:semicolon
id|dir-&gt;nr_buffers
op_assign
id|blk
suffix:semicolon
)brace
id|t
op_assign
(paren
r_struct
id|adfs_bigdirtail
op_star
)paren
(paren
id|dir-&gt;bh
(braket
id|size
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|b_data
op_plus
(paren
id|sb-&gt;s_blocksize
op_minus
l_int|8
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;bigdirendname
op_ne
id|cpu_to_le32
c_func
(paren
id|BIGDIRENDNAME
)paren
op_logical_or
id|t-&gt;bigdirendmasseq
op_ne
id|h-&gt;startmasseq
op_logical_or
id|t-&gt;reserved
(braket
l_int|0
)braket
op_ne
l_int|0
op_logical_or
id|t-&gt;reserved
(braket
l_int|1
)braket
op_ne
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|dir-&gt;parent_id
op_assign
id|le32_to_cpu
c_func
(paren
id|h-&gt;bigdirparent
)paren
suffix:semicolon
id|dir-&gt;sb
op_assign
id|sb
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dir-&gt;nr_buffers
suffix:semicolon
id|i
op_increment
)paren
id|brelse
c_func
(paren
id|dir-&gt;bh
(braket
id|i
)braket
)paren
suffix:semicolon
id|dir-&gt;sb
op_assign
l_int|NULL
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_int
DECL|function|adfs_fplus_setpos
id|adfs_fplus_setpos
c_func
(paren
r_struct
id|adfs_dir
op_star
id|dir
comma
r_int
r_int
id|fpos
)paren
(brace
r_struct
id|adfs_bigdirheader
op_star
id|h
op_assign
(paren
r_struct
id|adfs_bigdirheader
op_star
)paren
id|dir-&gt;bh
(braket
l_int|0
)braket
op_member_access_from_pointer
id|b_data
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
id|fpos
op_le
id|le32_to_cpu
c_func
(paren
id|h-&gt;bigdirentries
)paren
)paren
(brace
id|dir-&gt;pos
op_assign
id|fpos
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
r_static
r_void
DECL|function|dir_memcpy
id|dir_memcpy
c_func
(paren
r_struct
id|adfs_dir
op_star
id|dir
comma
r_int
r_int
id|offset
comma
r_void
op_star
id|to
comma
r_int
id|len
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|dir-&gt;sb
suffix:semicolon
r_int
r_int
id|buffer
comma
id|partial
comma
id|remainder
suffix:semicolon
id|buffer
op_assign
id|offset
op_rshift
id|sb-&gt;s_blocksize_bits
suffix:semicolon
id|offset
op_and_assign
id|sb-&gt;s_blocksize
op_minus
l_int|1
suffix:semicolon
id|partial
op_assign
id|sb-&gt;s_blocksize
op_minus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|partial
op_ge
id|len
)paren
id|memcpy
c_func
(paren
id|to
comma
id|dir-&gt;bh
(braket
id|buffer
)braket
op_member_access_from_pointer
id|b_data
op_plus
id|offset
comma
id|len
)paren
suffix:semicolon
r_else
(brace
r_char
op_star
id|c
op_assign
(paren
r_char
op_star
)paren
id|to
suffix:semicolon
id|remainder
op_assign
id|len
op_minus
id|partial
suffix:semicolon
id|memcpy
c_func
(paren
id|c
comma
id|dir-&gt;bh
(braket
id|buffer
)braket
op_member_access_from_pointer
id|b_data
op_plus
id|offset
comma
id|partial
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|c
op_plus
id|partial
comma
id|dir-&gt;bh
(braket
id|buffer
op_plus
l_int|1
)braket
op_member_access_from_pointer
id|b_data
comma
id|remainder
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|adfs_fplus_getnext
id|adfs_fplus_getnext
c_func
(paren
r_struct
id|adfs_dir
op_star
id|dir
comma
r_struct
id|object_info
op_star
id|obj
)paren
(brace
r_struct
id|adfs_bigdirheader
op_star
id|h
op_assign
(paren
r_struct
id|adfs_bigdirheader
op_star
)paren
id|dir-&gt;bh
(braket
l_int|0
)braket
op_member_access_from_pointer
id|b_data
suffix:semicolon
r_struct
id|adfs_bigdirentry
id|bde
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_int
id|i
comma
id|ret
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;pos
op_ge
id|le32_to_cpu
c_func
(paren
id|h-&gt;bigdirentries
)paren
)paren
r_goto
id|out
suffix:semicolon
id|offset
op_assign
m_offsetof
(paren
r_struct
id|adfs_bigdirheader
comma
id|bigdirname
)paren
suffix:semicolon
id|offset
op_add_assign
(paren
(paren
id|le32_to_cpu
c_func
(paren
id|h-&gt;bigdirnamelen
)paren
op_plus
l_int|4
)paren
op_amp
op_complement
l_int|3
)paren
suffix:semicolon
id|offset
op_add_assign
id|dir-&gt;pos
op_star
r_sizeof
(paren
r_struct
id|adfs_bigdirentry
)paren
suffix:semicolon
id|dir_memcpy
c_func
(paren
id|dir
comma
id|offset
comma
op_amp
id|bde
comma
r_sizeof
(paren
r_struct
id|adfs_bigdirentry
)paren
)paren
suffix:semicolon
id|obj-&gt;loadaddr
op_assign
id|le32_to_cpu
c_func
(paren
id|bde.bigdirload
)paren
suffix:semicolon
id|obj-&gt;execaddr
op_assign
id|le32_to_cpu
c_func
(paren
id|bde.bigdirexec
)paren
suffix:semicolon
id|obj-&gt;size
op_assign
id|le32_to_cpu
c_func
(paren
id|bde.bigdirlen
)paren
suffix:semicolon
id|obj-&gt;file_id
op_assign
id|le32_to_cpu
c_func
(paren
id|bde.bigdirindaddr
)paren
suffix:semicolon
id|obj-&gt;attr
op_assign
id|le32_to_cpu
c_func
(paren
id|bde.bigdirattr
)paren
suffix:semicolon
id|obj-&gt;name_len
op_assign
id|le32_to_cpu
c_func
(paren
id|bde.bigdirobnamelen
)paren
suffix:semicolon
id|offset
op_assign
m_offsetof
(paren
r_struct
id|adfs_bigdirheader
comma
id|bigdirname
)paren
suffix:semicolon
id|offset
op_add_assign
(paren
(paren
id|le32_to_cpu
c_func
(paren
id|h-&gt;bigdirnamelen
)paren
op_plus
l_int|4
)paren
op_amp
op_complement
l_int|3
)paren
suffix:semicolon
id|offset
op_add_assign
id|le32_to_cpu
c_func
(paren
id|h-&gt;bigdirentries
)paren
op_star
r_sizeof
(paren
r_struct
id|adfs_bigdirentry
)paren
suffix:semicolon
id|offset
op_add_assign
id|le32_to_cpu
c_func
(paren
id|bde.bigdirobnameptr
)paren
suffix:semicolon
id|dir_memcpy
c_func
(paren
id|dir
comma
id|offset
comma
id|obj-&gt;name
comma
id|obj-&gt;name_len
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
id|obj-&gt;name_len
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|obj-&gt;name
(braket
id|i
)braket
op_eq
l_char|&squot;/&squot;
)paren
id|obj-&gt;name
(braket
id|i
)braket
op_assign
l_char|&squot;.&squot;
suffix:semicolon
id|dir-&gt;pos
op_add_assign
l_int|1
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_void
DECL|function|adfs_fplus_free
id|adfs_fplus_free
c_func
(paren
r_struct
id|adfs_dir
op_star
id|dir
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
id|dir-&gt;nr_buffers
suffix:semicolon
id|i
op_increment
)paren
id|brelse
c_func
(paren
id|dir-&gt;bh
(braket
id|i
)braket
)paren
suffix:semicolon
id|dir-&gt;sb
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|variable|adfs_fplus_dir_ops
r_struct
id|adfs_dir_ops
id|adfs_fplus_dir_ops
op_assign
(brace
dot
id|read
op_assign
id|adfs_fplus_read
comma
dot
id|setpos
op_assign
id|adfs_fplus_setpos
comma
dot
id|getnext
op_assign
id|adfs_fplus_getnext
comma
dot
id|free
op_assign
id|adfs_fplus_free
)brace
suffix:semicolon
eof
