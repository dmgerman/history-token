multiline_comment|/* sysctl.c: Rx RPC control&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;rxrpc/types.h&gt;
macro_line|#include &lt;rxrpc/rxrpc.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &quot;internal.h&quot;
DECL|variable|rxrpc_ktrace
r_int
id|rxrpc_ktrace
suffix:semicolon
DECL|variable|rxrpc_kdebug
r_int
id|rxrpc_kdebug
suffix:semicolon
DECL|variable|rxrpc_kproto
r_int
id|rxrpc_kproto
suffix:semicolon
DECL|variable|rxrpc_knet
r_int
id|rxrpc_knet
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
DECL|variable|rxrpc_sysctl
r_static
r_struct
id|ctl_table_header
op_star
id|rxrpc_sysctl
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|rxrpc_sysctl_table
r_static
id|ctl_table
id|rxrpc_sysctl_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
l_int|1
comma
dot
id|procname
op_assign
l_string|&quot;kdebug&quot;
comma
dot
id|data
op_assign
op_amp
id|rxrpc_kdebug
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|2
comma
dot
id|procname
op_assign
l_string|&quot;ktrace&quot;
comma
dot
id|data
op_assign
op_amp
id|rxrpc_ktrace
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|3
comma
dot
id|procname
op_assign
l_string|&quot;kproto&quot;
comma
dot
id|data
op_assign
op_amp
id|rxrpc_kproto
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|4
comma
dot
id|procname
op_assign
l_string|&quot;knet&quot;
comma
dot
id|data
op_assign
op_amp
id|rxrpc_knet
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|rxrpc_dir_sysctl_table
r_static
id|ctl_table
id|rxrpc_dir_sysctl_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
l_int|1
comma
dot
id|procname
op_assign
l_string|&quot;rxrpc&quot;
comma
dot
id|mode
op_assign
l_int|0555
comma
dot
id|child
op_assign
id|rxrpc_sysctl_table
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_SYSCTL */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * initialise the sysctl stuff for Rx RPC&n; */
DECL|function|rxrpc_sysctl_init
r_int
id|rxrpc_sysctl_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SYSCTL
id|rxrpc_sysctl
op_assign
id|register_sysctl_table
c_func
(paren
id|rxrpc_dir_sysctl_table
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rxrpc_sysctl
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
macro_line|#endif /* CONFIG_SYSCTL */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_sysctl_init() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * clean up the sysctl stuff for Rx RPC&n; */
DECL|function|rxrpc_sysctl_cleanup
r_void
id|rxrpc_sysctl_cleanup
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SYSCTL
r_if
c_cond
(paren
id|rxrpc_sysctl
)paren
(brace
id|unregister_sysctl_table
c_func
(paren
id|rxrpc_sysctl
)paren
suffix:semicolon
id|rxrpc_sysctl
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SYSCTL */
)brace
multiline_comment|/* end rxrpc_sysctl_cleanup() */
eof
