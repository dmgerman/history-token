multiline_comment|/* &n;   BNEP implementation for Linux Bluetooth stack (BlueZ).&n;   Copyright (C) 2001-2002 Inventel Systemes&n;   Written 2001-2002 by&n;&t;David Libault  &lt;david.libault@inventel.fr&gt;&n;&n;   Copyright (C) 2002 Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; * $Id: sock.c,v 1.4 2002/08/04 21:23:58 maxk Exp $&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;bnep.h&quot;
macro_line|#ifndef CONFIG_BT_BNEP_DEBUG
DECL|macro|BT_DBG
macro_line|#undef  BT_DBG
DECL|macro|BT_DBG
mdefine_line|#define BT_DBG( A... )
macro_line|#endif
DECL|function|bnep_sock_release
r_static
r_int
id|bnep_sock_release
c_func
(paren
r_struct
id|socket
op_star
id|sock
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|sock-&gt;sk
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;sock %p sk %p&quot;
comma
id|sock
comma
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sk
)paren
r_return
l_int|0
suffix:semicolon
id|sock_orphan
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sock_put
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bnep_sock_ioctl
r_static
r_int
id|bnep_sock_ioctl
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|bnep_connlist_req
id|cl
suffix:semicolon
r_struct
id|bnep_connadd_req
id|ca
suffix:semicolon
r_struct
id|bnep_conndel_req
id|cd
suffix:semicolon
r_struct
id|bnep_conninfo
id|ci
suffix:semicolon
r_struct
id|socket
op_star
id|nsock
suffix:semicolon
r_void
id|__user
op_star
id|argp
op_assign
(paren
r_void
id|__user
op_star
)paren
id|arg
suffix:semicolon
r_int
id|err
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;cmd %x arg %lx&quot;
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|BNEPCONNADD
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ca
comma
id|argp
comma
r_sizeof
(paren
id|ca
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|nsock
op_assign
id|sockfd_lookup
c_func
(paren
id|ca.sock
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nsock
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|nsock-&gt;sk-&gt;sk_state
op_ne
id|BT_CONNECTED
)paren
(brace
id|fput
c_func
(paren
id|nsock-&gt;file
)paren
suffix:semicolon
r_return
op_minus
id|EBADFD
suffix:semicolon
)brace
id|err
op_assign
id|bnep_add_connection
c_func
(paren
op_amp
id|ca
comma
id|nsock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|argp
comma
op_amp
id|ca
comma
r_sizeof
(paren
id|ca
)paren
)paren
)paren
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
id|fput
c_func
(paren
id|nsock-&gt;file
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
r_case
id|BNEPCONNDEL
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|cd
comma
id|argp
comma
r_sizeof
(paren
id|cd
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|bnep_del_connection
c_func
(paren
op_amp
id|cd
)paren
suffix:semicolon
r_case
id|BNEPGETCONNLIST
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|cl
comma
id|argp
comma
r_sizeof
(paren
id|cl
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|cl.cnum
op_le
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|err
op_assign
id|bnep_get_connlist
c_func
(paren
op_amp
id|cl
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
op_logical_and
id|copy_to_user
c_func
(paren
id|argp
comma
op_amp
id|cl
comma
r_sizeof
(paren
id|cl
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|err
suffix:semicolon
r_case
id|BNEPGETCONNINFO
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ci
comma
id|argp
comma
r_sizeof
(paren
id|ci
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|err
op_assign
id|bnep_get_conninfo
c_func
(paren
op_amp
id|ci
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
op_logical_and
id|copy_to_user
c_func
(paren
id|argp
comma
op_amp
id|ci
comma
r_sizeof
(paren
id|ci
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|err
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|bnep_sock_ops
r_static
r_struct
id|proto_ops
id|bnep_sock_ops
op_assign
(brace
dot
id|family
op_assign
id|PF_BLUETOOTH
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|release
op_assign
id|bnep_sock_release
comma
dot
id|ioctl
op_assign
id|bnep_sock_ioctl
comma
dot
id|bind
op_assign
id|sock_no_bind
comma
dot
id|getname
op_assign
id|sock_no_getname
comma
dot
id|sendmsg
op_assign
id|sock_no_sendmsg
comma
dot
id|recvmsg
op_assign
id|sock_no_recvmsg
comma
dot
id|poll
op_assign
id|sock_no_poll
comma
dot
id|listen
op_assign
id|sock_no_listen
comma
dot
id|shutdown
op_assign
id|sock_no_shutdown
comma
dot
id|setsockopt
op_assign
id|sock_no_setsockopt
comma
dot
id|getsockopt
op_assign
id|sock_no_getsockopt
comma
dot
id|connect
op_assign
id|sock_no_connect
comma
dot
id|socketpair
op_assign
id|sock_no_socketpair
comma
dot
id|accept
op_assign
id|sock_no_accept
comma
dot
id|mmap
op_assign
id|sock_no_mmap
)brace
suffix:semicolon
DECL|function|bnep_sock_create
r_static
r_int
id|bnep_sock_create
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|protocol
)paren
(brace
r_struct
id|sock
op_star
id|sk
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;sock %p&quot;
comma
id|sock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sock-&gt;type
op_ne
id|SOCK_RAW
)paren
r_return
op_minus
id|ESOCKTNOSUPPORT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sk
op_assign
id|sk_alloc
c_func
(paren
id|PF_BLUETOOTH
comma
id|GFP_KERNEL
comma
r_sizeof
(paren
r_struct
id|bt_sock
)paren
comma
l_int|NULL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|sock_init_data
c_func
(paren
id|sock
comma
id|sk
)paren
suffix:semicolon
id|sk_set_owner
c_func
(paren
id|sk
comma
id|THIS_MODULE
)paren
suffix:semicolon
id|sock-&gt;ops
op_assign
op_amp
id|bnep_sock_ops
suffix:semicolon
id|sock-&gt;state
op_assign
id|SS_UNCONNECTED
suffix:semicolon
id|sock_reset_flag
c_func
(paren
id|sk
comma
id|SOCK_ZAPPED
)paren
suffix:semicolon
id|sk-&gt;sk_protocol
op_assign
id|protocol
suffix:semicolon
id|sk-&gt;sk_state
op_assign
id|BT_OPEN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|bnep_sock_family_ops
r_static
r_struct
id|net_proto_family
id|bnep_sock_family_ops
op_assign
(brace
dot
id|family
op_assign
id|PF_BLUETOOTH
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|create
op_assign
id|bnep_sock_create
)brace
suffix:semicolon
DECL|function|bnep_sock_init
r_int
id|__init
id|bnep_sock_init
c_func
(paren
r_void
)paren
(brace
id|bt_sock_register
c_func
(paren
id|BTPROTO_BNEP
comma
op_amp
id|bnep_sock_family_ops
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bnep_sock_cleanup
r_int
id|__exit
id|bnep_sock_cleanup
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|bt_sock_unregister
c_func
(paren
id|BTPROTO_BNEP
)paren
)paren
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t unregister BNEP socket&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
