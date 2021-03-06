multiline_comment|/*&n; * linux/fs/befs/io.c&n; *&n; * Copyright (C) 2001 Will Dyson &lt;will_dyson@pobox.com&n; *&n; * Based on portions of file.c and inode.c &n; * by Makoto Kato (m_kato@ga2.so-net.ne.jp)&n; *&n; * Many thanks to Dominic Giampaolo, author of Practical File System&n; * Design with the Be File System, for such a helpful book.&n; *&n; */
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &quot;befs.h&quot;
macro_line|#include &quot;io.h&quot;
multiline_comment|/*&n; * Converts befs notion of disk addr to a disk offset and uses&n; * linux kernel function sb_bread() to get the buffer containing&n; * the offset. -Will Dyson&n; *&n; */
r_struct
id|buffer_head
op_star
DECL|function|befs_bread_iaddr
id|befs_bread_iaddr
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|befs_inode_addr
id|iaddr
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|befs_blocknr_t
id|block
op_assign
l_int|0
suffix:semicolon
id|befs_sb_info
op_star
id|befs_sb
op_assign
id|BEFS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;---&gt; Enter befs_read_iaddr() &quot;
l_string|&quot;[%u, %hu, %hu]&quot;
comma
id|iaddr.allocation_group
comma
id|iaddr.start
comma
id|iaddr.len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iaddr.allocation_group
OG
id|befs_sb-&gt;num_ags
)paren
(brace
id|befs_error
c_func
(paren
id|sb
comma
l_string|&quot;BEFS: Invalid allocation group %u, max is %u&quot;
comma
id|iaddr.allocation_group
comma
id|befs_sb-&gt;num_ags
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|block
op_assign
id|iaddr2blockno
c_func
(paren
id|sb
comma
op_amp
id|iaddr
)paren
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;befs_read_iaddr: offset = %lu&quot;
comma
id|block
)paren
suffix:semicolon
id|bh
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
id|bh
op_eq
l_int|NULL
)paren
(brace
id|befs_error
c_func
(paren
id|sb
comma
l_string|&quot;Failed to read block %lu&quot;
comma
id|block
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;&lt;--- befs_read_iaddr()&quot;
)paren
suffix:semicolon
r_return
id|bh
suffix:semicolon
id|error
suffix:colon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;&lt;--- befs_read_iaddr() ERROR&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_struct
id|buffer_head
op_star
DECL|function|befs_bread
id|befs_bread
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|befs_blocknr_t
id|block
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;---&gt; Enter befs_read() %Lu&quot;
comma
id|block
)paren
suffix:semicolon
id|bh
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
id|bh
op_eq
l_int|NULL
)paren
(brace
id|befs_error
c_func
(paren
id|sb
comma
l_string|&quot;Failed to read block %lu&quot;
comma
id|block
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;&lt;--- befs_read()&quot;
)paren
suffix:semicolon
r_return
id|bh
suffix:semicolon
id|error
suffix:colon
id|befs_debug
c_func
(paren
id|sb
comma
l_string|&quot;&lt;--- befs_read() ERROR&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
eof
