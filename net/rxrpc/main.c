multiline_comment|/* main.c: Rx RPC interface&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;rxrpc/rxrpc.h&gt;
macro_line|#include &lt;rxrpc/krxiod.h&gt;
macro_line|#include &lt;rxrpc/krxsecd.h&gt;
macro_line|#include &lt;rxrpc/krxtimod.h&gt;
macro_line|#include &lt;rxrpc/transport.h&gt;
macro_line|#include &lt;rxrpc/connection.h&gt;
macro_line|#include &lt;rxrpc/call.h&gt;
macro_line|#include &lt;rxrpc/message.h&gt;
macro_line|#include &quot;internal.h&quot;
r_static
r_int
id|rxrpc_initialise
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|rxrpc_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|rxrpc_initialise
id|module_init
c_func
(paren
id|rxrpc_initialise
)paren
suffix:semicolon
DECL|variable|rxrpc_cleanup
id|module_exit
c_func
(paren
id|rxrpc_cleanup
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Rx RPC implementation&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Red Hat, Inc.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|rxrpc_epoch
id|u32
id|rxrpc_epoch
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * initialise the Rx module&n; */
DECL|function|rxrpc_initialise
r_static
r_int
id|rxrpc_initialise
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
multiline_comment|/* my epoch value */
id|rxrpc_epoch
op_assign
id|htonl
c_func
(paren
id|xtime.tv_sec
)paren
suffix:semicolon
multiline_comment|/* register the /proc interface */
macro_line|#ifdef CONFIG_PROC_FS
id|ret
op_assign
id|rxrpc_proc_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
macro_line|#endif
multiline_comment|/* register the sysctl files */
macro_line|#ifdef CONFIG_SYSCTL
id|ret
op_assign
id|rxrpc_sysctl_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|error_proc
suffix:semicolon
macro_line|#endif
multiline_comment|/* start the krxtimod daemon */
id|ret
op_assign
id|rxrpc_krxtimod_start
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|error_sysctl
suffix:semicolon
multiline_comment|/* start the krxiod daemon */
id|ret
op_assign
id|rxrpc_krxiod_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|error_krxtimod
suffix:semicolon
multiline_comment|/* start the krxsecd daemon */
id|ret
op_assign
id|rxrpc_krxsecd_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|error_krxiod
suffix:semicolon
id|kdebug
c_func
(paren
l_string|&quot;&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error_krxiod
suffix:colon
id|rxrpc_krxiod_kill
c_func
(paren
)paren
suffix:semicolon
id|error_krxtimod
suffix:colon
id|rxrpc_krxtimod_kill
c_func
(paren
)paren
suffix:semicolon
id|error_sysctl
suffix:colon
macro_line|#ifdef CONFIG_SYSCTL
id|rxrpc_sysctl_cleanup
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|error_proc
suffix:colon
macro_line|#ifdef CONFIG_PROC_FS
id|rxrpc_proc_cleanup
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_initialise() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * clean up the Rx module&n; */
DECL|function|rxrpc_cleanup
r_static
r_void
id|rxrpc_cleanup
c_func
(paren
r_void
)paren
(brace
id|kenter
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
id|__RXACCT
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;Outstanding Messages   : %d&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|rxrpc_message_count
)paren
)paren
)paren
suffix:semicolon
id|__RXACCT
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;Outstanding Calls      : %d&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|rxrpc_call_count
)paren
)paren
)paren
suffix:semicolon
id|__RXACCT
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;Outstanding Connections: %d&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|rxrpc_connection_count
)paren
)paren
)paren
suffix:semicolon
id|__RXACCT
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;Outstanding Peers      : %d&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|rxrpc_peer_count
)paren
)paren
)paren
suffix:semicolon
id|__RXACCT
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;Outstanding Transports : %d&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|rxrpc_transport_count
)paren
)paren
)paren
suffix:semicolon
id|rxrpc_krxsecd_kill
c_func
(paren
)paren
suffix:semicolon
id|rxrpc_krxiod_kill
c_func
(paren
)paren
suffix:semicolon
id|rxrpc_krxtimod_kill
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
id|rxrpc_sysctl_cleanup
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PROC_FS
id|rxrpc_proc_cleanup
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|__RXACCT
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;Outstanding Messages   : %d&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|rxrpc_message_count
)paren
)paren
)paren
suffix:semicolon
id|__RXACCT
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;Outstanding Calls      : %d&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|rxrpc_call_count
)paren
)paren
)paren
suffix:semicolon
id|__RXACCT
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;Outstanding Connections: %d&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|rxrpc_connection_count
)paren
)paren
)paren
suffix:semicolon
id|__RXACCT
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;Outstanding Peers      : %d&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|rxrpc_peer_count
)paren
)paren
)paren
suffix:semicolon
id|__RXACCT
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;Outstanding Transports : %d&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|rxrpc_transport_count
)paren
)paren
)paren
suffix:semicolon
id|kleave
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* end rxrpc_cleanup() */
eof
