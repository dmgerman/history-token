multiline_comment|/* vlclient.c: AFS Volume Location Service client&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;rxrpc/rxrpc.h&gt;
macro_line|#include &lt;rxrpc/transport.h&gt;
macro_line|#include &lt;rxrpc/connection.h&gt;
macro_line|#include &lt;rxrpc/call.h&gt;
macro_line|#include &quot;server.h&quot;
macro_line|#include &quot;volume.h&quot;
macro_line|#include &quot;vlclient.h&quot;
macro_line|#include &quot;kafsasyncd.h&quot;
macro_line|#include &quot;kafstimod.h&quot;
macro_line|#include &quot;errors.h&quot;
macro_line|#include &quot;internal.h&quot;
DECL|macro|VLGETENTRYBYID
mdefine_line|#define VLGETENTRYBYID&t;&t;503&t;/* AFS Get Cache Entry By ID operation ID */
DECL|macro|VLGETENTRYBYNAME
mdefine_line|#define VLGETENTRYBYNAME&t;504&t;/* AFS Get Cache Entry By Name operation ID */
DECL|macro|VLPROBE
mdefine_line|#define VLPROBE&t;&t;&t;514&t;/* AFS Probe Volume Location Service operation ID */
r_static
r_void
id|afs_rxvl_get_entry_by_id_attn
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
suffix:semicolon
r_static
r_void
id|afs_rxvl_get_entry_by_id_error
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * map afs VL abort codes to/from Linux error codes&n; * - called with call-&gt;lock held&n; */
DECL|function|afs_rxvl_aemap
r_static
r_void
id|afs_rxvl_aemap
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
(brace
r_int
id|err
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;{%u,%u,%d}&quot;
comma
id|call-&gt;app_err_state
comma
id|call-&gt;app_abort_code
comma
id|call-&gt;app_errno
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|call-&gt;app_err_state
)paren
(brace
r_case
id|RXRPC_ESTATE_LOCAL_ABORT
suffix:colon
id|call-&gt;app_abort_code
op_assign
op_minus
id|call-&gt;app_errno
suffix:semicolon
r_return
suffix:semicolon
r_case
id|RXRPC_ESTATE_PEER_ABORT
suffix:colon
r_switch
c_cond
(paren
id|call-&gt;app_abort_code
)paren
(brace
r_case
id|AFSVL_IDEXIST
suffix:colon
id|err
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_IO
suffix:colon
id|err
op_assign
op_minus
id|EREMOTEIO
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_NAMEEXIST
suffix:colon
id|err
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_CREATEFAIL
suffix:colon
id|err
op_assign
op_minus
id|EREMOTEIO
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_NOENT
suffix:colon
id|err
op_assign
op_minus
id|ENOMEDIUM
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_EMPTY
suffix:colon
id|err
op_assign
op_minus
id|ENOMEDIUM
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_ENTDELETED
suffix:colon
id|err
op_assign
op_minus
id|ENOMEDIUM
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_BADNAME
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_BADINDEX
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_BADVOLTYPE
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_BADSERVER
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_BADPARTITION
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_REPSFULL
suffix:colon
id|err
op_assign
op_minus
id|EFBIG
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_NOREPSERVER
suffix:colon
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_DUPREPSERVER
suffix:colon
id|err
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_RWNOTFOUND
suffix:colon
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_BADREFCOUNT
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_SIZEEXCEEDED
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_BADENTRY
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_BADVOLIDBUMP
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_IDALREADYHASHED
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_ENTRYLOCKED
suffix:colon
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_BADVOLOPER
suffix:colon
id|err
op_assign
op_minus
id|EBADRQC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_BADRELLOCKTYPE
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_RERELEASE
suffix:colon
id|err
op_assign
op_minus
id|EREMOTEIO
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_BADSERVERFLAG
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_PERM
suffix:colon
id|err
op_assign
op_minus
id|EACCES
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFSVL_NOMEM
suffix:colon
id|err
op_assign
op_minus
id|EREMOTEIO
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
id|afs_abort_to_error
c_func
(paren
id|call-&gt;app_abort_code
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|call-&gt;app_errno
op_assign
id|err
suffix:semicolon
r_return
suffix:semicolon
r_default
suffix:colon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/* end afs_rxvl_aemap() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * probe a volume location server to see if it is still alive&n; */
DECL|function|afs_rxvl_probe
r_int
id|afs_rxvl_probe
c_func
(paren
id|afs_server_t
op_star
id|server
comma
r_int
id|alloc_flags
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|myself
comma
id|current
)paren
suffix:semicolon
r_struct
id|rxrpc_connection
op_star
id|conn
suffix:semicolon
r_struct
id|rxrpc_call
op_star
id|call
suffix:semicolon
r_struct
id|iovec
id|piov
(braket
l_int|1
)braket
suffix:semicolon
r_int
id|sent
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|u32
id|param
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* get hold of the vlserver connection */
id|ret
op_assign
id|afs_server_get_vlconn
c_func
(paren
id|server
comma
op_amp
id|conn
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
id|out
suffix:semicolon
multiline_comment|/* create a call through that connection */
id|ret
op_assign
id|rxrpc_create_call
c_func
(paren
id|conn
comma
l_int|NULL
comma
l_int|NULL
comma
id|afs_rxvl_aemap
comma
op_amp
id|call
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;kAFS: Unable to create call: %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_goto
id|out_put_conn
suffix:semicolon
)brace
id|call-&gt;app_opcode
op_assign
id|VLPROBE
suffix:semicolon
multiline_comment|/* we want to get event notifications from the call */
id|add_wait_queue
c_func
(paren
op_amp
id|call-&gt;waitq
comma
op_amp
id|myself
)paren
suffix:semicolon
multiline_comment|/* marshall the parameters */
id|param
(braket
l_int|0
)braket
op_assign
id|htonl
c_func
(paren
id|VLPROBE
)paren
suffix:semicolon
id|piov
(braket
l_int|0
)braket
dot
id|iov_len
op_assign
r_sizeof
(paren
id|param
)paren
suffix:semicolon
id|piov
(braket
l_int|0
)braket
dot
id|iov_base
op_assign
id|param
suffix:semicolon
multiline_comment|/* send the parameters to the server */
id|ret
op_assign
id|rxrpc_call_write_data
c_func
(paren
id|call
comma
l_int|1
comma
id|piov
comma
id|RXRPC_LAST_PACKET
comma
id|alloc_flags
comma
l_int|0
comma
op_amp
id|sent
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
m_abort
suffix:semicolon
multiline_comment|/* wait for the reply to completely arrive */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|call-&gt;app_call_state
op_ne
id|RXRPC_CSTATE_CLNT_RCV_REPLY
op_logical_or
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_break
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINTR
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_goto
m_abort
suffix:semicolon
r_switch
c_cond
(paren
id|call-&gt;app_call_state
)paren
(brace
r_case
id|RXRPC_CSTATE_ERROR
suffix:colon
id|ret
op_assign
id|call-&gt;app_errno
suffix:semicolon
r_goto
id|out_unwait
suffix:semicolon
r_case
id|RXRPC_CSTATE_CLNT_GOT_REPLY
suffix:colon
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out_unwait
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
m_abort
suffix:colon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|rxrpc_call_abort
c_func
(paren
id|call
comma
id|ret
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|out_unwait
suffix:colon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|call-&gt;waitq
comma
op_amp
id|myself
)paren
suffix:semicolon
id|rxrpc_put_call
c_func
(paren
id|call
)paren
suffix:semicolon
id|out_put_conn
suffix:colon
id|rxrpc_put_connection
c_func
(paren
id|conn
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end afs_rxvl_probe() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * look up a volume location database entry by name&n; */
DECL|function|afs_rxvl_get_entry_by_name
r_int
id|afs_rxvl_get_entry_by_name
c_func
(paren
id|afs_server_t
op_star
id|server
comma
r_const
r_char
op_star
id|volname
comma
id|afsc_vldb_record_t
op_star
id|entry
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|myself
comma
id|current
)paren
suffix:semicolon
r_struct
id|rxrpc_connection
op_star
id|conn
suffix:semicolon
r_struct
id|rxrpc_call
op_star
id|call
suffix:semicolon
r_struct
id|iovec
id|piov
(braket
l_int|3
)braket
suffix:semicolon
r_int
id|tmp
suffix:semicolon
r_int
id|sent
suffix:semicolon
r_int
id|ret
comma
id|loop
suffix:semicolon
id|u32
op_star
id|bp
comma
id|param
(braket
l_int|2
)braket
comma
id|zero
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;,%s,&quot;
comma
id|volname
)paren
suffix:semicolon
id|memset
c_func
(paren
id|entry
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|entry
)paren
)paren
suffix:semicolon
multiline_comment|/* get hold of the vlserver connection */
id|ret
op_assign
id|afs_server_get_vlconn
c_func
(paren
id|server
comma
op_amp
id|conn
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
id|out
suffix:semicolon
multiline_comment|/* create a call through that connection */
id|ret
op_assign
id|rxrpc_create_call
c_func
(paren
id|conn
comma
l_int|NULL
comma
l_int|NULL
comma
id|afs_rxvl_aemap
comma
op_amp
id|call
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;kAFS: Unable to create call: %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_goto
id|out_put_conn
suffix:semicolon
)brace
id|call-&gt;app_opcode
op_assign
id|VLGETENTRYBYNAME
suffix:semicolon
multiline_comment|/* we want to get event notifications from the call */
id|add_wait_queue
c_func
(paren
op_amp
id|call-&gt;waitq
comma
op_amp
id|myself
)paren
suffix:semicolon
multiline_comment|/* marshall the parameters */
id|piov
(braket
l_int|1
)braket
dot
id|iov_len
op_assign
id|strlen
c_func
(paren
id|volname
)paren
suffix:semicolon
id|piov
(braket
l_int|1
)braket
dot
id|iov_base
op_assign
(paren
r_char
op_star
)paren
id|volname
suffix:semicolon
id|zero
op_assign
l_int|0
suffix:semicolon
id|piov
(braket
l_int|2
)braket
dot
id|iov_len
op_assign
(paren
l_int|4
op_minus
(paren
id|piov
(braket
l_int|1
)braket
dot
id|iov_len
op_amp
l_int|3
)paren
)paren
op_amp
l_int|3
suffix:semicolon
id|piov
(braket
l_int|2
)braket
dot
id|iov_base
op_assign
op_amp
id|zero
suffix:semicolon
id|param
(braket
l_int|0
)braket
op_assign
id|htonl
c_func
(paren
id|VLGETENTRYBYNAME
)paren
suffix:semicolon
id|param
(braket
l_int|1
)braket
op_assign
id|htonl
c_func
(paren
id|piov
(braket
l_int|1
)braket
dot
id|iov_len
)paren
suffix:semicolon
id|piov
(braket
l_int|0
)braket
dot
id|iov_len
op_assign
r_sizeof
(paren
id|param
)paren
suffix:semicolon
id|piov
(braket
l_int|0
)braket
dot
id|iov_base
op_assign
id|param
suffix:semicolon
multiline_comment|/* send the parameters to the server */
id|ret
op_assign
id|rxrpc_call_write_data
c_func
(paren
id|call
comma
l_int|3
comma
id|piov
comma
id|RXRPC_LAST_PACKET
comma
id|GFP_NOFS
comma
l_int|0
comma
op_amp
id|sent
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
m_abort
suffix:semicolon
multiline_comment|/* wait for the reply to completely arrive */
id|bp
op_assign
id|rxrpc_call_alloc_scratch
c_func
(paren
id|call
comma
l_int|384
)paren
suffix:semicolon
id|ret
op_assign
id|rxrpc_call_read_data
c_func
(paren
id|call
comma
id|bp
comma
l_int|384
comma
id|RXRPC_CALL_READ_BLOCK
op_or
id|RXRPC_CALL_READ_ALL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|ret
op_eq
op_minus
id|ECONNABORTED
)paren
(brace
id|ret
op_assign
id|call-&gt;app_errno
suffix:semicolon
r_goto
id|out_unwait
suffix:semicolon
)brace
r_goto
m_abort
suffix:semicolon
)brace
multiline_comment|/* unmarshall the reply */
r_for
c_loop
(paren
id|loop
op_assign
l_int|0
suffix:semicolon
id|loop
OL
l_int|64
suffix:semicolon
id|loop
op_increment
)paren
id|entry-&gt;name
(braket
id|loop
)braket
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
id|bp
op_increment
suffix:semicolon
multiline_comment|/* final NUL */
id|bp
op_increment
suffix:semicolon
multiline_comment|/* type */
id|entry-&gt;nservers
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
r_for
c_loop
(paren
id|loop
op_assign
l_int|0
suffix:semicolon
id|loop
OL
l_int|8
suffix:semicolon
id|loop
op_increment
)paren
id|entry-&gt;servers
(braket
id|loop
)braket
dot
id|s_addr
op_assign
op_star
id|bp
op_increment
suffix:semicolon
id|bp
op_add_assign
l_int|8
suffix:semicolon
multiline_comment|/* partition IDs */
r_for
c_loop
(paren
id|loop
op_assign
l_int|0
suffix:semicolon
id|loop
OL
l_int|8
suffix:semicolon
id|loop
op_increment
)paren
(brace
id|tmp
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|AFS_VLSF_RWVOL
)paren
id|entry-&gt;srvtmask
(braket
id|loop
)braket
op_or_assign
id|AFSC_VOL_STM_RW
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|AFS_VLSF_ROVOL
)paren
id|entry-&gt;srvtmask
(braket
id|loop
)braket
op_or_assign
id|AFSC_VOL_STM_RO
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|AFS_VLSF_BACKVOL
)paren
id|entry-&gt;srvtmask
(braket
id|loop
)braket
op_or_assign
id|AFSC_VOL_STM_BAK
suffix:semicolon
)brace
id|entry-&gt;vid
(braket
l_int|0
)braket
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
id|entry-&gt;vid
(braket
l_int|1
)braket
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
id|entry-&gt;vid
(braket
l_int|2
)braket
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
id|bp
op_increment
suffix:semicolon
multiline_comment|/* clone ID */
id|tmp
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
multiline_comment|/* flags */
r_if
c_cond
(paren
id|tmp
op_amp
id|AFS_VLF_RWEXISTS
)paren
id|entry-&gt;vidmask
op_or_assign
id|AFSC_VOL_STM_RW
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|AFS_VLF_ROEXISTS
)paren
id|entry-&gt;vidmask
op_or_assign
id|AFSC_VOL_STM_RO
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|AFS_VLF_BACKEXISTS
)paren
id|entry-&gt;vidmask
op_or_assign
id|AFSC_VOL_STM_BAK
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEDIUM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;vidmask
)paren
r_goto
m_abort
suffix:semicolon
multiline_comment|/* success */
id|entry-&gt;ctime
op_assign
id|get_seconds
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|out_unwait
suffix:colon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|call-&gt;waitq
comma
op_amp
id|myself
)paren
suffix:semicolon
id|rxrpc_put_call
c_func
(paren
id|call
)paren
suffix:semicolon
id|out_put_conn
suffix:colon
id|rxrpc_put_connection
c_func
(paren
id|conn
)paren
suffix:semicolon
id|out
suffix:colon
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
m_abort
suffix:colon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|rxrpc_call_abort
c_func
(paren
id|call
comma
id|ret
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_goto
id|out_unwait
suffix:semicolon
)brace
multiline_comment|/* end afs_rxvl_get_entry_by_name() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * look up a volume location database entry by ID&n; */
DECL|function|afs_rxvl_get_entry_by_id
r_int
id|afs_rxvl_get_entry_by_id
c_func
(paren
id|afs_server_t
op_star
id|server
comma
id|afs_volid_t
id|volid
comma
id|afs_voltype_t
id|voltype
comma
id|afsc_vldb_record_t
op_star
id|entry
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|myself
comma
id|current
)paren
suffix:semicolon
r_struct
id|rxrpc_connection
op_star
id|conn
suffix:semicolon
r_struct
id|rxrpc_call
op_star
id|call
suffix:semicolon
r_struct
id|iovec
id|piov
(braket
l_int|1
)braket
suffix:semicolon
r_int
id|tmp
suffix:semicolon
r_int
id|sent
suffix:semicolon
r_int
id|ret
comma
id|loop
suffix:semicolon
id|u32
op_star
id|bp
comma
id|param
(braket
l_int|3
)braket
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;,%x,%d,&quot;
comma
id|volid
comma
id|voltype
)paren
suffix:semicolon
id|memset
c_func
(paren
id|entry
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|entry
)paren
)paren
suffix:semicolon
multiline_comment|/* get hold of the vlserver connection */
id|ret
op_assign
id|afs_server_get_vlconn
c_func
(paren
id|server
comma
op_amp
id|conn
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
id|out
suffix:semicolon
multiline_comment|/* create a call through that connection */
id|ret
op_assign
id|rxrpc_create_call
c_func
(paren
id|conn
comma
l_int|NULL
comma
l_int|NULL
comma
id|afs_rxvl_aemap
comma
op_amp
id|call
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;kAFS: Unable to create call: %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_goto
id|out_put_conn
suffix:semicolon
)brace
id|call-&gt;app_opcode
op_assign
id|VLGETENTRYBYID
suffix:semicolon
multiline_comment|/* we want to get event notifications from the call */
id|add_wait_queue
c_func
(paren
op_amp
id|call-&gt;waitq
comma
op_amp
id|myself
)paren
suffix:semicolon
multiline_comment|/* marshall the parameters */
id|param
(braket
l_int|0
)braket
op_assign
id|htonl
c_func
(paren
id|VLGETENTRYBYID
)paren
suffix:semicolon
id|param
(braket
l_int|1
)braket
op_assign
id|htonl
c_func
(paren
id|volid
)paren
suffix:semicolon
id|param
(braket
l_int|2
)braket
op_assign
id|htonl
c_func
(paren
id|voltype
)paren
suffix:semicolon
id|piov
(braket
l_int|0
)braket
dot
id|iov_len
op_assign
r_sizeof
(paren
id|param
)paren
suffix:semicolon
id|piov
(braket
l_int|0
)braket
dot
id|iov_base
op_assign
id|param
suffix:semicolon
multiline_comment|/* send the parameters to the server */
id|ret
op_assign
id|rxrpc_call_write_data
c_func
(paren
id|call
comma
l_int|1
comma
id|piov
comma
id|RXRPC_LAST_PACKET
comma
id|GFP_NOFS
comma
l_int|0
comma
op_amp
id|sent
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
m_abort
suffix:semicolon
multiline_comment|/* wait for the reply to completely arrive */
id|bp
op_assign
id|rxrpc_call_alloc_scratch
c_func
(paren
id|call
comma
l_int|384
)paren
suffix:semicolon
id|ret
op_assign
id|rxrpc_call_read_data
c_func
(paren
id|call
comma
id|bp
comma
l_int|384
comma
id|RXRPC_CALL_READ_BLOCK
op_or
id|RXRPC_CALL_READ_ALL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|ret
op_eq
op_minus
id|ECONNABORTED
)paren
(brace
id|ret
op_assign
id|call-&gt;app_errno
suffix:semicolon
r_goto
id|out_unwait
suffix:semicolon
)brace
r_goto
m_abort
suffix:semicolon
)brace
multiline_comment|/* unmarshall the reply */
r_for
c_loop
(paren
id|loop
op_assign
l_int|0
suffix:semicolon
id|loop
OL
l_int|64
suffix:semicolon
id|loop
op_increment
)paren
id|entry-&gt;name
(braket
id|loop
)braket
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
id|bp
op_increment
suffix:semicolon
multiline_comment|/* final NUL */
id|bp
op_increment
suffix:semicolon
multiline_comment|/* type */
id|entry-&gt;nservers
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
r_for
c_loop
(paren
id|loop
op_assign
l_int|0
suffix:semicolon
id|loop
OL
l_int|8
suffix:semicolon
id|loop
op_increment
)paren
id|entry-&gt;servers
(braket
id|loop
)braket
dot
id|s_addr
op_assign
op_star
id|bp
op_increment
suffix:semicolon
id|bp
op_add_assign
l_int|8
suffix:semicolon
multiline_comment|/* partition IDs */
r_for
c_loop
(paren
id|loop
op_assign
l_int|0
suffix:semicolon
id|loop
OL
l_int|8
suffix:semicolon
id|loop
op_increment
)paren
(brace
id|tmp
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|AFS_VLSF_RWVOL
)paren
id|entry-&gt;srvtmask
(braket
id|loop
)braket
op_or_assign
id|AFSC_VOL_STM_RW
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|AFS_VLSF_ROVOL
)paren
id|entry-&gt;srvtmask
(braket
id|loop
)braket
op_or_assign
id|AFSC_VOL_STM_RO
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|AFS_VLSF_BACKVOL
)paren
id|entry-&gt;srvtmask
(braket
id|loop
)braket
op_or_assign
id|AFSC_VOL_STM_BAK
suffix:semicolon
)brace
id|entry-&gt;vid
(braket
l_int|0
)braket
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
id|entry-&gt;vid
(braket
l_int|1
)braket
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
id|entry-&gt;vid
(braket
l_int|2
)braket
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
id|bp
op_increment
suffix:semicolon
multiline_comment|/* clone ID */
id|tmp
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
multiline_comment|/* flags */
r_if
c_cond
(paren
id|tmp
op_amp
id|AFS_VLF_RWEXISTS
)paren
id|entry-&gt;vidmask
op_or_assign
id|AFSC_VOL_STM_RW
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|AFS_VLF_ROEXISTS
)paren
id|entry-&gt;vidmask
op_or_assign
id|AFSC_VOL_STM_RO
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|AFS_VLF_BACKEXISTS
)paren
id|entry-&gt;vidmask
op_or_assign
id|AFSC_VOL_STM_BAK
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEDIUM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;vidmask
)paren
r_goto
m_abort
suffix:semicolon
macro_line|#if 0 /* TODO: remove */
id|entry-&gt;nservers
op_assign
l_int|3
suffix:semicolon
id|entry-&gt;servers
(braket
l_int|0
)braket
dot
id|s_addr
op_assign
id|htonl
c_func
(paren
l_int|0xac101249
)paren
suffix:semicolon
id|entry-&gt;servers
(braket
l_int|1
)braket
dot
id|s_addr
op_assign
id|htonl
c_func
(paren
l_int|0xac101243
)paren
suffix:semicolon
id|entry-&gt;servers
(braket
l_int|2
)braket
dot
id|s_addr
op_assign
id|htonl
c_func
(paren
l_int|0xac10125b
multiline_comment|/*0xac10125b*/
)paren
suffix:semicolon
id|entry-&gt;srvtmask
(braket
l_int|0
)braket
op_assign
id|AFSC_VOL_STM_RO
suffix:semicolon
id|entry-&gt;srvtmask
(braket
l_int|1
)braket
op_assign
id|AFSC_VOL_STM_RO
suffix:semicolon
id|entry-&gt;srvtmask
(braket
l_int|2
)braket
op_assign
id|AFSC_VOL_STM_RO
op_or
id|AFSC_VOL_STM_RW
suffix:semicolon
macro_line|#endif
multiline_comment|/* success */
id|entry-&gt;ctime
op_assign
id|get_seconds
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|out_unwait
suffix:colon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|call-&gt;waitq
comma
op_amp
id|myself
)paren
suffix:semicolon
id|rxrpc_put_call
c_func
(paren
id|call
)paren
suffix:semicolon
id|out_put_conn
suffix:colon
id|rxrpc_put_connection
c_func
(paren
id|conn
)paren
suffix:semicolon
id|out
suffix:colon
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
m_abort
suffix:colon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|rxrpc_call_abort
c_func
(paren
id|call
comma
id|ret
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_goto
id|out_unwait
suffix:semicolon
)brace
multiline_comment|/* end afs_rxvl_get_entry_by_id() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * look up a volume location database entry by ID asynchronously&n; */
DECL|function|afs_rxvl_get_entry_by_id_async
r_int
id|afs_rxvl_get_entry_by_id_async
c_func
(paren
id|afs_async_op_t
op_star
id|op
comma
id|afs_volid_t
id|volid
comma
id|afs_voltype_t
id|voltype
)paren
(brace
r_struct
id|rxrpc_connection
op_star
id|conn
suffix:semicolon
r_struct
id|rxrpc_call
op_star
id|call
suffix:semicolon
r_struct
id|iovec
id|piov
(braket
l_int|1
)braket
suffix:semicolon
r_int
id|sent
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|u32
id|param
(braket
l_int|3
)braket
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;,%x,%d,&quot;
comma
id|volid
comma
id|voltype
)paren
suffix:semicolon
multiline_comment|/* get hold of the vlserver connection */
id|ret
op_assign
id|afs_server_get_vlconn
c_func
(paren
id|op-&gt;server
comma
op_amp
id|conn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* create a call through that connection */
id|ret
op_assign
id|rxrpc_create_call
c_func
(paren
id|conn
comma
id|afs_rxvl_get_entry_by_id_attn
comma
id|afs_rxvl_get_entry_by_id_error
comma
id|afs_rxvl_aemap
comma
op_amp
id|op-&gt;call
)paren
suffix:semicolon
id|rxrpc_put_connection
c_func
(paren
id|conn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;kAFS: Unable to create call: %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|op-&gt;call-&gt;app_opcode
op_assign
id|VLGETENTRYBYID
suffix:semicolon
id|op-&gt;call-&gt;app_user
op_assign
id|op
suffix:semicolon
id|call
op_assign
id|op-&gt;call
suffix:semicolon
id|rxrpc_get_call
c_func
(paren
id|call
)paren
suffix:semicolon
multiline_comment|/* send event notifications from the call to kafsasyncd */
id|afs_kafsasyncd_begin_op
c_func
(paren
id|op
)paren
suffix:semicolon
multiline_comment|/* marshall the parameters */
id|param
(braket
l_int|0
)braket
op_assign
id|htonl
c_func
(paren
id|VLGETENTRYBYID
)paren
suffix:semicolon
id|param
(braket
l_int|1
)braket
op_assign
id|htonl
c_func
(paren
id|volid
)paren
suffix:semicolon
id|param
(braket
l_int|2
)braket
op_assign
id|htonl
c_func
(paren
id|voltype
)paren
suffix:semicolon
id|piov
(braket
l_int|0
)braket
dot
id|iov_len
op_assign
r_sizeof
(paren
id|param
)paren
suffix:semicolon
id|piov
(braket
l_int|0
)braket
dot
id|iov_base
op_assign
id|param
suffix:semicolon
multiline_comment|/* allocate result read buffer in scratch space */
id|call-&gt;app_scr_ptr
op_assign
id|rxrpc_call_alloc_scratch
c_func
(paren
id|op-&gt;call
comma
l_int|384
)paren
suffix:semicolon
multiline_comment|/* send the parameters to the server */
id|ret
op_assign
id|rxrpc_call_write_data
c_func
(paren
id|call
comma
l_int|1
comma
id|piov
comma
id|RXRPC_LAST_PACKET
comma
id|GFP_NOFS
comma
l_int|0
comma
op_amp
id|sent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|rxrpc_call_abort
c_func
(paren
id|call
comma
id|ret
)paren
suffix:semicolon
multiline_comment|/* handle from kafsasyncd */
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* wait for the reply to completely arrive */
id|ret
op_assign
id|rxrpc_call_read_data
c_func
(paren
id|call
comma
id|call-&gt;app_scr_ptr
comma
l_int|384
comma
l_int|0
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ret
)paren
(brace
r_case
l_int|0
suffix:colon
r_case
op_minus
id|EAGAIN
suffix:colon
r_case
op_minus
id|ECONNABORTED
suffix:colon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* all handled by kafsasyncd */
r_default
suffix:colon
id|rxrpc_call_abort
c_func
(paren
id|call
comma
id|ret
)paren
suffix:semicolon
multiline_comment|/* force kafsasyncd to handle it */
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|out
suffix:colon
id|rxrpc_put_call
c_func
(paren
id|call
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end afs_rxvl_get_entry_by_id_async() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * attend to the asynchronous get VLDB entry by ID&n; */
DECL|function|afs_rxvl_get_entry_by_id_async2
r_int
id|afs_rxvl_get_entry_by_id_async2
c_func
(paren
id|afs_async_op_t
op_star
id|op
comma
id|afsc_vldb_record_t
op_star
id|entry
)paren
(brace
r_int
op_star
id|bp
comma
id|tmp
suffix:semicolon
r_int
id|loop
comma
id|ret
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;{op=%p cst=%u}&quot;
comma
id|op
comma
id|op-&gt;call-&gt;app_call_state
)paren
suffix:semicolon
id|memset
c_func
(paren
id|entry
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|entry
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|op-&gt;call-&gt;app_call_state
op_eq
id|RXRPC_CSTATE_COMPLETE
)paren
(brace
multiline_comment|/* operation finished */
id|afs_kafsasyncd_terminate_op
c_func
(paren
id|op
)paren
suffix:semicolon
id|bp
op_assign
id|op-&gt;call-&gt;app_scr_ptr
suffix:semicolon
multiline_comment|/* unmarshall the reply */
r_for
c_loop
(paren
id|loop
op_assign
l_int|0
suffix:semicolon
id|loop
OL
l_int|64
suffix:semicolon
id|loop
op_increment
)paren
id|entry-&gt;name
(braket
id|loop
)braket
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
id|bp
op_increment
suffix:semicolon
multiline_comment|/* final NUL */
id|bp
op_increment
suffix:semicolon
multiline_comment|/* type */
id|entry-&gt;nservers
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
r_for
c_loop
(paren
id|loop
op_assign
l_int|0
suffix:semicolon
id|loop
OL
l_int|8
suffix:semicolon
id|loop
op_increment
)paren
id|entry-&gt;servers
(braket
id|loop
)braket
dot
id|s_addr
op_assign
op_star
id|bp
op_increment
suffix:semicolon
id|bp
op_add_assign
l_int|8
suffix:semicolon
multiline_comment|/* partition IDs */
r_for
c_loop
(paren
id|loop
op_assign
l_int|0
suffix:semicolon
id|loop
OL
l_int|8
suffix:semicolon
id|loop
op_increment
)paren
(brace
id|tmp
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|AFS_VLSF_RWVOL
)paren
id|entry-&gt;srvtmask
(braket
id|loop
)braket
op_or_assign
id|AFSC_VOL_STM_RW
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|AFS_VLSF_ROVOL
)paren
id|entry-&gt;srvtmask
(braket
id|loop
)braket
op_or_assign
id|AFSC_VOL_STM_RO
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|AFS_VLSF_BACKVOL
)paren
id|entry-&gt;srvtmask
(braket
id|loop
)braket
op_or_assign
id|AFSC_VOL_STM_BAK
suffix:semicolon
)brace
id|entry-&gt;vid
(braket
l_int|0
)braket
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
id|entry-&gt;vid
(braket
l_int|1
)braket
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
id|entry-&gt;vid
(braket
l_int|2
)braket
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
id|bp
op_increment
suffix:semicolon
multiline_comment|/* clone ID */
id|tmp
op_assign
id|ntohl
c_func
(paren
op_star
id|bp
op_increment
)paren
suffix:semicolon
multiline_comment|/* flags */
r_if
c_cond
(paren
id|tmp
op_amp
id|AFS_VLF_RWEXISTS
)paren
id|entry-&gt;vidmask
op_or_assign
id|AFSC_VOL_STM_RW
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|AFS_VLF_ROEXISTS
)paren
id|entry-&gt;vidmask
op_or_assign
id|AFSC_VOL_STM_RO
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|AFS_VLF_BACKEXISTS
)paren
id|entry-&gt;vidmask
op_or_assign
id|AFSC_VOL_STM_BAK
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEDIUM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;vidmask
)paren
(brace
id|rxrpc_call_abort
c_func
(paren
id|op-&gt;call
comma
id|ret
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
macro_line|#if 0 /* TODO: remove */
id|entry-&gt;nservers
op_assign
l_int|3
suffix:semicolon
id|entry-&gt;servers
(braket
l_int|0
)braket
dot
id|s_addr
op_assign
id|htonl
c_func
(paren
l_int|0xac101249
)paren
suffix:semicolon
id|entry-&gt;servers
(braket
l_int|1
)braket
dot
id|s_addr
op_assign
id|htonl
c_func
(paren
l_int|0xac101243
)paren
suffix:semicolon
id|entry-&gt;servers
(braket
l_int|2
)braket
dot
id|s_addr
op_assign
id|htonl
c_func
(paren
l_int|0xac10125b
multiline_comment|/*0xac10125b*/
)paren
suffix:semicolon
id|entry-&gt;srvtmask
(braket
l_int|0
)braket
op_assign
id|AFSC_VOL_STM_RO
suffix:semicolon
id|entry-&gt;srvtmask
(braket
l_int|1
)braket
op_assign
id|AFSC_VOL_STM_RO
suffix:semicolon
id|entry-&gt;srvtmask
(braket
l_int|2
)braket
op_assign
id|AFSC_VOL_STM_RO
op_or
id|AFSC_VOL_STM_RW
suffix:semicolon
macro_line|#endif
multiline_comment|/* success */
id|entry-&gt;ctime
op_assign
id|get_seconds
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
id|op-&gt;call-&gt;app_call_state
op_eq
id|RXRPC_CSTATE_ERROR
)paren
(brace
multiline_comment|/* operation error */
id|ret
op_assign
id|op-&gt;call-&gt;app_errno
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|_leave
c_func
(paren
l_string|&quot; = -EAGAIN&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|done
suffix:colon
id|rxrpc_put_call
c_func
(paren
id|op-&gt;call
)paren
suffix:semicolon
id|op-&gt;call
op_assign
l_int|NULL
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot; = %d&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* end afs_rxvl_get_entry_by_id_async2() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * handle attention events on an async get-entry-by-ID op&n; * - called from krxiod&n; */
DECL|function|afs_rxvl_get_entry_by_id_attn
r_static
r_void
id|afs_rxvl_get_entry_by_id_attn
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
(brace
id|afs_async_op_t
op_star
id|op
op_assign
id|call-&gt;app_user
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;{op=%p cst=%u}&quot;
comma
id|op
comma
id|call-&gt;app_call_state
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|call-&gt;app_call_state
)paren
(brace
r_case
id|RXRPC_CSTATE_COMPLETE
suffix:colon
id|afs_kafsasyncd_attend_op
c_func
(paren
id|op
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RXRPC_CSTATE_CLNT_RCV_REPLY
suffix:colon
r_if
c_cond
(paren
id|call-&gt;app_async_read
)paren
r_break
suffix:semicolon
r_case
id|RXRPC_CSTATE_CLNT_GOT_REPLY
suffix:colon
r_if
c_cond
(paren
id|call-&gt;app_read_count
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;kAFS: Reply bigger than expected {cst=%u asyn=%d mark=%Zu rdy=%Zu pr=%u%s}&quot;
comma
id|call-&gt;app_call_state
comma
id|call-&gt;app_async_read
comma
id|call-&gt;app_mark
comma
id|call-&gt;app_ready_qty
comma
id|call-&gt;pkt_rcv_count
comma
id|call-&gt;app_last_rcv
ques
c_cond
l_string|&quot; last&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|rxrpc_call_abort
c_func
(paren
id|call
comma
op_minus
id|EBADMSG
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_rxvl_get_entry_by_id_attn() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * handle error events on an async get-entry-by-ID op&n; * - called from krxiod&n; */
DECL|function|afs_rxvl_get_entry_by_id_error
r_static
r_void
id|afs_rxvl_get_entry_by_id_error
c_func
(paren
r_struct
id|rxrpc_call
op_star
id|call
)paren
(brace
id|afs_async_op_t
op_star
id|op
op_assign
id|call-&gt;app_user
suffix:semicolon
id|_enter
c_func
(paren
l_string|&quot;{op=%p cst=%u}&quot;
comma
id|op
comma
id|call-&gt;app_call_state
)paren
suffix:semicolon
id|afs_kafsasyncd_attend_op
c_func
(paren
id|op
)paren
suffix:semicolon
id|_leave
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end afs_rxvl_get_entry_by_id_error() */
eof
