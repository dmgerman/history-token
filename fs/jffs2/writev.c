multiline_comment|/*&n; * JFFS2 -- Journalling Flash File System, Version 2.&n; *&n; * Copyright (C) 2001, 2002 Red Hat, Inc.&n; *&n; * Created by David Woodhouse &lt;dwmw2@redhat.com&gt;&n; *&n; * For licensing information, see the file &squot;LICENCE&squot; in this directory.&n; *&n; * $Id: writev.c,v 1.4 2003/10/04 08:33:07 dwmw2 Exp $&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &quot;nodelist.h&quot;
multiline_comment|/* This ought to be in core MTD code. All registered MTD devices&n;   without writev should have this put in place. Bug the MTD&n;   maintainer */
DECL|function|mtd_fake_writev
r_static
r_inline
r_int
id|mtd_fake_writev
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_const
r_struct
id|kvec
op_star
id|vecs
comma
r_int
r_int
id|count
comma
id|loff_t
id|to
comma
r_int
op_star
id|retlen
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_int
id|totlen
op_assign
l_int|0
comma
id|thislen
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|vecs
(braket
id|i
)braket
dot
id|iov_len
)paren
r_continue
suffix:semicolon
id|ret
op_assign
id|mtd
op_member_access_from_pointer
id|write
c_func
(paren
id|mtd
comma
id|to
comma
id|vecs
(braket
id|i
)braket
dot
id|iov_len
comma
op_amp
id|thislen
comma
id|vecs
(braket
id|i
)braket
dot
id|iov_base
)paren
suffix:semicolon
id|totlen
op_add_assign
id|thislen
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_logical_or
id|thislen
op_ne
id|vecs
(braket
id|i
)braket
dot
id|iov_len
)paren
r_break
suffix:semicolon
id|to
op_add_assign
id|vecs
(braket
id|i
)braket
dot
id|iov_len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retlen
)paren
op_star
id|retlen
op_assign
id|totlen
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|jffs2_flash_direct_writev
r_int
id|jffs2_flash_direct_writev
c_func
(paren
r_struct
id|jffs2_sb_info
op_star
id|c
comma
r_const
r_struct
id|kvec
op_star
id|vecs
comma
r_int
r_int
id|count
comma
id|loff_t
id|to
comma
r_int
op_star
id|retlen
)paren
(brace
r_if
c_cond
(paren
id|c-&gt;mtd-&gt;writev
)paren
r_return
id|c-&gt;mtd
op_member_access_from_pointer
id|writev
c_func
(paren
id|c-&gt;mtd
comma
id|vecs
comma
id|count
comma
id|to
comma
id|retlen
)paren
suffix:semicolon
r_else
r_return
id|mtd_fake_writev
c_func
(paren
id|c-&gt;mtd
comma
id|vecs
comma
id|count
comma
id|to
comma
id|retlen
)paren
suffix:semicolon
)brace
eof
