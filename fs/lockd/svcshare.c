multiline_comment|/*&n; * linux/fs/lockd/svcshare.c&n; *&n; * Management of DOS shares.&n; *&n; * Copyright (C) 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/lockd/lockd.h&gt;
macro_line|#include &lt;linux/lockd/share.h&gt;
r_static
r_inline
r_int
DECL|function|nlm_cmp_owner
id|nlm_cmp_owner
c_func
(paren
r_struct
id|nlm_share
op_star
id|share
comma
r_struct
id|xdr_netobj
op_star
id|oh
)paren
(brace
r_return
id|share-&gt;s_owner.len
op_eq
id|oh-&gt;len
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|share-&gt;s_owner.data
comma
id|oh-&gt;data
comma
id|oh-&gt;len
)paren
suffix:semicolon
)brace
id|u32
DECL|function|nlmsvc_share_file
id|nlmsvc_share_file
c_func
(paren
r_struct
id|nlm_host
op_star
id|host
comma
r_struct
id|nlm_file
op_star
id|file
comma
r_struct
id|nlm_args
op_star
id|argp
)paren
(brace
r_struct
id|nlm_share
op_star
id|share
suffix:semicolon
r_struct
id|xdr_netobj
op_star
id|oh
op_assign
op_amp
id|argp-&gt;lock.oh
suffix:semicolon
id|u8
op_star
id|ohdata
suffix:semicolon
r_for
c_loop
(paren
id|share
op_assign
id|file-&gt;f_shares
suffix:semicolon
id|share
suffix:semicolon
id|share
op_assign
id|share-&gt;s_next
)paren
(brace
r_if
c_cond
(paren
id|share-&gt;s_host
op_eq
id|host
op_logical_and
id|nlm_cmp_owner
c_func
(paren
id|share
comma
id|oh
)paren
)paren
r_goto
id|update
suffix:semicolon
r_if
c_cond
(paren
(paren
id|argp-&gt;fsm_access
op_amp
id|share-&gt;s_mode
)paren
op_logical_or
(paren
id|argp-&gt;fsm_mode
op_amp
id|share-&gt;s_access
)paren
)paren
r_return
id|nlm_lck_denied
suffix:semicolon
)brace
id|share
op_assign
(paren
r_struct
id|nlm_share
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|share
)paren
op_plus
id|oh-&gt;len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|share
op_eq
l_int|NULL
)paren
r_return
id|nlm_lck_denied_nolocks
suffix:semicolon
multiline_comment|/* Copy owner handle */
id|ohdata
op_assign
(paren
id|u8
op_star
)paren
(paren
id|share
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ohdata
comma
id|oh-&gt;data
comma
id|oh-&gt;len
)paren
suffix:semicolon
id|share-&gt;s_file
op_assign
id|file
suffix:semicolon
id|share-&gt;s_host
op_assign
id|host
suffix:semicolon
id|share-&gt;s_owner.data
op_assign
id|ohdata
suffix:semicolon
id|share-&gt;s_owner.len
op_assign
id|oh-&gt;len
suffix:semicolon
id|share-&gt;s_next
op_assign
id|file-&gt;f_shares
suffix:semicolon
id|file-&gt;f_shares
op_assign
id|share
suffix:semicolon
id|update
suffix:colon
id|share-&gt;s_access
op_assign
id|argp-&gt;fsm_access
suffix:semicolon
id|share-&gt;s_mode
op_assign
id|argp-&gt;fsm_mode
suffix:semicolon
r_return
id|nlm_granted
suffix:semicolon
)brace
multiline_comment|/*&n; * Delete a share.&n; */
id|u32
DECL|function|nlmsvc_unshare_file
id|nlmsvc_unshare_file
c_func
(paren
r_struct
id|nlm_host
op_star
id|host
comma
r_struct
id|nlm_file
op_star
id|file
comma
r_struct
id|nlm_args
op_star
id|argp
)paren
(brace
r_struct
id|nlm_share
op_star
id|share
comma
op_star
op_star
id|shpp
suffix:semicolon
r_struct
id|xdr_netobj
op_star
id|oh
op_assign
op_amp
id|argp-&gt;lock.oh
suffix:semicolon
r_for
c_loop
(paren
id|shpp
op_assign
op_amp
id|file-&gt;f_shares
suffix:semicolon
(paren
id|share
op_assign
op_star
id|shpp
)paren
op_ne
l_int|0
suffix:semicolon
id|shpp
op_assign
op_amp
id|share-&gt;s_next
)paren
(brace
r_if
c_cond
(paren
id|share-&gt;s_host
op_eq
id|host
op_logical_and
id|nlm_cmp_owner
c_func
(paren
id|share
comma
id|oh
)paren
)paren
(brace
op_star
id|shpp
op_assign
id|share-&gt;s_next
suffix:semicolon
id|kfree
c_func
(paren
id|share
)paren
suffix:semicolon
r_return
id|nlm_granted
suffix:semicolon
)brace
)brace
multiline_comment|/* X/Open spec says return success even if there was no&n;&t; * corresponding share. */
r_return
id|nlm_granted
suffix:semicolon
)brace
multiline_comment|/*&n; * Traverse all shares for a given file (and host).&n; * NLM_ACT_CHECK is handled by nlmsvc_inspect_file.&n; */
r_int
DECL|function|nlmsvc_traverse_shares
id|nlmsvc_traverse_shares
c_func
(paren
r_struct
id|nlm_host
op_star
id|host
comma
r_struct
id|nlm_file
op_star
id|file
comma
r_int
id|action
)paren
(brace
r_struct
id|nlm_share
op_star
id|share
comma
op_star
op_star
id|shpp
suffix:semicolon
id|shpp
op_assign
op_amp
id|file-&gt;f_shares
suffix:semicolon
r_while
c_loop
(paren
(paren
id|share
op_assign
op_star
id|shpp
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|action
op_eq
id|NLM_ACT_MARK
)paren
id|share-&gt;s_host-&gt;h_inuse
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|action
op_eq
id|NLM_ACT_UNLOCK
)paren
(brace
r_if
c_cond
(paren
id|host
op_eq
l_int|NULL
op_logical_or
id|host
op_eq
id|share-&gt;s_host
)paren
(brace
op_star
id|shpp
op_assign
id|share-&gt;s_next
suffix:semicolon
id|kfree
c_func
(paren
id|share
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
id|shpp
op_assign
op_amp
id|share-&gt;s_next
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
