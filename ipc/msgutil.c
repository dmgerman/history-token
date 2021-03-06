multiline_comment|/*&n; * linux/ipc/util.c&n; * Copyright (C) 1999, 2004 Manfred Spraul&n; *&n; * This file is released under GNU General Public Licence version 2 or&n; * (at your option) any later version.&n; *&n; * See the file COPYING for more details.&n; */
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ipc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;util.h&quot;
DECL|struct|msg_msgseg
r_struct
id|msg_msgseg
(brace
DECL|member|next
r_struct
id|msg_msgseg
op_star
id|next
suffix:semicolon
multiline_comment|/* the next part of the message follows immediately */
)brace
suffix:semicolon
DECL|macro|DATALEN_MSG
mdefine_line|#define DATALEN_MSG&t;(PAGE_SIZE-sizeof(struct msg_msg))
DECL|macro|DATALEN_SEG
mdefine_line|#define DATALEN_SEG&t;(PAGE_SIZE-sizeof(struct msg_msgseg))
DECL|function|load_msg
r_struct
id|msg_msg
op_star
id|load_msg
c_func
(paren
r_const
r_void
id|__user
op_star
id|src
comma
r_int
id|len
)paren
(brace
r_struct
id|msg_msg
op_star
id|msg
suffix:semicolon
r_struct
id|msg_msgseg
op_star
op_star
id|pseg
suffix:semicolon
r_int
id|err
suffix:semicolon
r_int
id|alen
suffix:semicolon
id|alen
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|alen
OG
id|DATALEN_MSG
)paren
id|alen
op_assign
id|DATALEN_MSG
suffix:semicolon
id|msg
op_assign
(paren
r_struct
id|msg_msg
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|msg
)paren
op_plus
id|alen
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msg
op_eq
l_int|NULL
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|msg-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|msg-&gt;security
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|msg
op_plus
l_int|1
comma
id|src
comma
id|alen
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
)brace
id|len
op_sub_assign
id|alen
suffix:semicolon
id|src
op_assign
(paren
(paren
r_char
id|__user
op_star
)paren
id|src
)paren
op_plus
id|alen
suffix:semicolon
id|pseg
op_assign
op_amp
id|msg-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_struct
id|msg_msgseg
op_star
id|seg
suffix:semicolon
id|alen
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|alen
OG
id|DATALEN_SEG
)paren
id|alen
op_assign
id|DATALEN_SEG
suffix:semicolon
id|seg
op_assign
(paren
r_struct
id|msg_msgseg
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|seg
)paren
op_plus
id|alen
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|seg
op_eq
l_int|NULL
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
)brace
op_star
id|pseg
op_assign
id|seg
suffix:semicolon
id|seg-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|seg
op_plus
l_int|1
comma
id|src
comma
id|alen
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
)brace
id|pseg
op_assign
op_amp
id|seg-&gt;next
suffix:semicolon
id|len
op_sub_assign
id|alen
suffix:semicolon
id|src
op_assign
(paren
(paren
r_char
id|__user
op_star
)paren
id|src
)paren
op_plus
id|alen
suffix:semicolon
)brace
id|err
op_assign
id|security_msg_msg_alloc
c_func
(paren
id|msg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out_err
suffix:semicolon
r_return
id|msg
suffix:semicolon
id|out_err
suffix:colon
id|free_msg
c_func
(paren
id|msg
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|err
)paren
suffix:semicolon
)brace
DECL|function|store_msg
r_int
id|store_msg
c_func
(paren
r_void
id|__user
op_star
id|dest
comma
r_struct
id|msg_msg
op_star
id|msg
comma
r_int
id|len
)paren
(brace
r_int
id|alen
suffix:semicolon
r_struct
id|msg_msgseg
op_star
id|seg
suffix:semicolon
id|alen
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|alen
OG
id|DATALEN_MSG
)paren
id|alen
op_assign
id|DATALEN_MSG
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|dest
comma
id|msg
op_plus
l_int|1
comma
id|alen
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|len
op_sub_assign
id|alen
suffix:semicolon
id|dest
op_assign
(paren
(paren
r_char
id|__user
op_star
)paren
id|dest
)paren
op_plus
id|alen
suffix:semicolon
id|seg
op_assign
id|msg-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
id|alen
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|alen
OG
id|DATALEN_SEG
)paren
id|alen
op_assign
id|DATALEN_SEG
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|dest
comma
id|seg
op_plus
l_int|1
comma
id|alen
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|len
op_sub_assign
id|alen
suffix:semicolon
id|dest
op_assign
(paren
(paren
r_char
id|__user
op_star
)paren
id|dest
)paren
op_plus
id|alen
suffix:semicolon
id|seg
op_assign
id|seg-&gt;next
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|free_msg
r_void
id|free_msg
c_func
(paren
r_struct
id|msg_msg
op_star
id|msg
)paren
(brace
r_struct
id|msg_msgseg
op_star
id|seg
suffix:semicolon
id|security_msg_msg_free
c_func
(paren
id|msg
)paren
suffix:semicolon
id|seg
op_assign
id|msg-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|msg
)paren
suffix:semicolon
r_while
c_loop
(paren
id|seg
op_ne
l_int|NULL
)paren
(brace
r_struct
id|msg_msgseg
op_star
id|tmp
op_assign
id|seg-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|seg
)paren
suffix:semicolon
id|seg
op_assign
id|tmp
suffix:semicolon
)brace
)brace
eof
