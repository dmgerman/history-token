multiline_comment|/* $Id: mntfunc.c,v 1.19.6.2 2004/08/28 20:03:53 armin Exp $&n; *&n; * Driver for Eicon DIVA Server ISDN cards.&n; * Maint module&n; *&n; * Copyright 2000-2003 by Armin Schindler (mac@melware.de)&n; * Copyright 2000-2003 Cytronics &amp; Melware (info@melware.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; */
macro_line|#include &quot;platform.h&quot;
macro_line|#include &quot;di_defs.h&quot;
macro_line|#include &quot;divasync.h&quot;
macro_line|#include &quot;debug_if.h&quot;
r_extern
r_char
op_star
id|DRIVERRELEASE_MNT
suffix:semicolon
DECL|macro|DBG_MINIMUM
mdefine_line|#define DBG_MINIMUM  (DL_LOG + DL_FTL + DL_ERR)
DECL|macro|DBG_DEFAULT
mdefine_line|#define DBG_DEFAULT  (DBG_MINIMUM + DL_XLOG + DL_REG)
r_extern
r_void
id|DIVA_DIDD_Read
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
DECL|variable|notify_handle
r_static
id|dword
id|notify_handle
suffix:semicolon
DECL|variable|DAdapter
r_static
id|DESCRIPTOR
id|DAdapter
suffix:semicolon
DECL|variable|MAdapter
r_static
id|DESCRIPTOR
id|MAdapter
suffix:semicolon
DECL|variable|MaintDescriptor
r_static
id|DESCRIPTOR
id|MaintDescriptor
op_assign
(brace
id|IDI_DIMAINT
comma
l_int|0
comma
l_int|0
comma
(paren
id|IDI_CALL
)paren
id|diva_maint_prtComp
)brace
suffix:semicolon
r_extern
r_int
id|diva_os_copy_to_user
c_func
(paren
r_void
op_star
id|os_handle
comma
r_void
id|__user
op_star
id|dst
comma
r_const
r_void
op_star
id|src
comma
r_int
id|length
)paren
suffix:semicolon
r_extern
r_int
id|diva_os_copy_from_user
c_func
(paren
r_void
op_star
id|os_handle
comma
r_void
op_star
id|dst
comma
r_const
r_void
id|__user
op_star
id|src
comma
r_int
id|length
)paren
suffix:semicolon
DECL|function|no_printf
r_static
r_void
id|no_printf
c_func
(paren
r_int
r_char
op_star
id|x
comma
dot
dot
dot
)paren
(brace
multiline_comment|/* dummy debug function */
)brace
macro_line|#include &quot;debuglib.c&quot;
multiline_comment|/*&n; *  DIDD callback function&n; */
DECL|function|didd_callback
r_static
r_void
op_star
id|didd_callback
c_func
(paren
r_void
op_star
id|context
comma
id|DESCRIPTOR
op_star
id|adapter
comma
r_int
id|removal
)paren
(brace
r_if
c_cond
(paren
id|adapter-&gt;type
op_eq
id|IDI_DADAPTER
)paren
(brace
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;cb: Change in DAdapter ? Oops ?.&quot;
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|adapter-&gt;type
op_eq
id|IDI_DIMAINT
)paren
(brace
r_if
c_cond
(paren
id|removal
)paren
(brace
id|DbgDeregister
c_func
(paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|MAdapter
comma
l_int|0
comma
r_sizeof
(paren
id|MAdapter
)paren
)paren
suffix:semicolon
id|dprintf
op_assign
id|no_printf
suffix:semicolon
)brace
r_else
(brace
id|memcpy
c_func
(paren
op_amp
id|MAdapter
comma
id|adapter
comma
r_sizeof
(paren
id|MAdapter
)paren
)paren
suffix:semicolon
id|dprintf
op_assign
(paren
id|DIVA_DI_PRINTF
)paren
id|MAdapter.request
suffix:semicolon
id|DbgRegister
c_func
(paren
l_string|&quot;MAINT&quot;
comma
id|DRIVERRELEASE_MNT
comma
id|DBG_DEFAULT
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
(paren
id|adapter-&gt;type
OG
l_int|0
)paren
op_logical_and
(paren
id|adapter-&gt;type
OL
l_int|16
)paren
)paren
(brace
r_if
c_cond
(paren
id|removal
)paren
(brace
id|diva_mnt_remove_xdi_adapter
c_func
(paren
id|adapter
)paren
suffix:semicolon
)brace
r_else
(brace
id|diva_mnt_add_xdi_adapter
c_func
(paren
id|adapter
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * connect to didd&n; */
DECL|function|connect_didd
r_static
r_int
id|DIVA_INIT_FUNCTION
id|connect_didd
c_func
(paren
r_void
)paren
(brace
r_int
id|x
op_assign
l_int|0
suffix:semicolon
r_int
id|dadapter
op_assign
l_int|0
suffix:semicolon
id|IDI_SYNC_REQ
id|req
suffix:semicolon
id|DESCRIPTOR
id|DIDD_Table
(braket
id|MAX_DESCRIPTORS
)braket
suffix:semicolon
id|DIVA_DIDD_Read
c_func
(paren
id|DIDD_Table
comma
r_sizeof
(paren
id|DIDD_Table
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
id|MAX_DESCRIPTORS
suffix:semicolon
id|x
op_increment
)paren
(brace
r_if
c_cond
(paren
id|DIDD_Table
(braket
id|x
)braket
dot
id|type
op_eq
id|IDI_DADAPTER
)paren
(brace
multiline_comment|/* DADAPTER found */
id|dadapter
op_assign
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|DAdapter
comma
op_amp
id|DIDD_Table
(braket
id|x
)braket
comma
r_sizeof
(paren
id|DAdapter
)paren
)paren
suffix:semicolon
id|req.didd_notify.e.Req
op_assign
l_int|0
suffix:semicolon
id|req.didd_notify.e.Rc
op_assign
id|IDI_SYNC_REQ_DIDD_REGISTER_ADAPTER_NOTIFY
suffix:semicolon
id|req.didd_notify.info.callback
op_assign
(paren
r_void
op_star
)paren
id|didd_callback
suffix:semicolon
id|req.didd_notify.info.context
op_assign
l_int|NULL
suffix:semicolon
id|DAdapter
dot
id|request
c_func
(paren
(paren
id|ENTITY
op_star
)paren
op_amp
id|req
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req.didd_notify.e.Rc
op_ne
l_int|0xff
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
id|notify_handle
op_assign
id|req.didd_notify.info.handle
suffix:semicolon
multiline_comment|/* Register MAINT (me) */
id|req.didd_add_adapter.e.Req
op_assign
l_int|0
suffix:semicolon
id|req.didd_add_adapter.e.Rc
op_assign
id|IDI_SYNC_REQ_DIDD_ADD_ADAPTER
suffix:semicolon
id|req.didd_add_adapter.info.descriptor
op_assign
(paren
r_void
op_star
)paren
op_amp
id|MaintDescriptor
suffix:semicolon
id|DAdapter
dot
id|request
c_func
(paren
(paren
id|ENTITY
op_star
)paren
op_amp
id|req
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req.didd_add_adapter.e.Rc
op_ne
l_int|0xff
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|DIDD_Table
(braket
id|x
)braket
dot
id|type
OG
l_int|0
)paren
op_logical_and
(paren
id|DIDD_Table
(braket
id|x
)braket
dot
id|type
OL
l_int|16
)paren
)paren
(brace
id|diva_mnt_add_xdi_adapter
c_func
(paren
op_amp
id|DIDD_Table
(braket
id|x
)braket
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
id|dadapter
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * disconnect from didd&n; */
DECL|function|disconnect_didd
r_static
r_void
id|DIVA_EXIT_FUNCTION
id|disconnect_didd
c_func
(paren
r_void
)paren
(brace
id|IDI_SYNC_REQ
id|req
suffix:semicolon
id|req.didd_notify.e.Req
op_assign
l_int|0
suffix:semicolon
id|req.didd_notify.e.Rc
op_assign
id|IDI_SYNC_REQ_DIDD_REMOVE_ADAPTER_NOTIFY
suffix:semicolon
id|req.didd_notify.info.handle
op_assign
id|notify_handle
suffix:semicolon
id|DAdapter
dot
id|request
c_func
(paren
(paren
id|ENTITY
op_star
)paren
op_amp
id|req
)paren
suffix:semicolon
id|req.didd_remove_adapter.e.Req
op_assign
l_int|0
suffix:semicolon
id|req.didd_remove_adapter.e.Rc
op_assign
id|IDI_SYNC_REQ_DIDD_REMOVE_ADAPTER
suffix:semicolon
id|req.didd_remove_adapter.info.p_request
op_assign
(paren
id|IDI_CALL
)paren
id|MaintDescriptor.request
suffix:semicolon
id|DAdapter
dot
id|request
c_func
(paren
(paren
id|ENTITY
op_star
)paren
op_amp
id|req
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * read/write maint&n; */
DECL|function|maint_read_write
r_int
id|maint_read_write
c_func
(paren
r_void
id|__user
op_star
id|buf
comma
r_int
id|count
)paren
(brace
id|byte
id|data
(braket
l_int|128
)braket
suffix:semicolon
id|dword
id|cmd
comma
id|id
comma
id|mask
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
(paren
l_int|3
op_star
r_sizeof
(paren
id|dword
)paren
)paren
)paren
r_return
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diva_os_copy_from_user
c_func
(paren
l_int|NULL
comma
(paren
r_void
op_star
)paren
op_amp
id|data
(braket
l_int|0
)braket
comma
id|buf
comma
l_int|3
op_star
r_sizeof
(paren
id|dword
)paren
)paren
)paren
(brace
r_return
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
)brace
id|cmd
op_assign
op_star
(paren
id|dword
op_star
)paren
op_amp
id|data
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* command */
id|id
op_assign
op_star
(paren
id|dword
op_star
)paren
op_amp
id|data
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* driver id */
id|mask
op_assign
op_star
(paren
id|dword
op_star
)paren
op_amp
id|data
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* mask or size */
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|DITRACE_CMD_GET_DRIVER_INFO
suffix:colon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|diva_get_driver_info
c_func
(paren
id|id
comma
id|data
comma
r_sizeof
(paren
id|data
)paren
)paren
)paren
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|count
OL
id|ret
)paren
op_logical_or
id|diva_os_copy_to_user
(paren
l_int|NULL
comma
id|buf
comma
(paren
r_void
op_star
)paren
op_amp
id|data
(braket
l_int|0
)braket
comma
id|ret
)paren
)paren
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|DITRACE_READ_DRIVER_DBG_MASK
suffix:colon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|diva_get_driver_dbg_mask
c_func
(paren
id|id
comma
(paren
id|byte
op_star
)paren
id|data
)paren
)paren
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|count
OL
id|ret
)paren
op_logical_or
id|diva_os_copy_to_user
(paren
l_int|NULL
comma
id|buf
comma
(paren
r_void
op_star
)paren
op_amp
id|data
(braket
l_int|0
)braket
comma
id|ret
)paren
)paren
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|DITRACE_WRITE_DRIVER_DBG_MASK
suffix:colon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|diva_set_driver_dbg_mask
c_func
(paren
id|id
comma
id|mask
)paren
)paren
op_le
l_int|0
)paren
(brace
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
)brace
r_break
suffix:semicolon
multiline_comment|/*&n;       Filter commands will ignore the ID due to fact that filtering affects&n;       the B- channel and Audio Tap trace levels only. Also MAINT driver will&n;       select the right trace ID by itself&n;       */
r_case
id|DITRACE_WRITE_SELECTIVE_TRACE_FILTER
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|mask
)paren
(brace
id|ret
op_assign
id|diva_set_trace_filter
(paren
l_int|1
comma
l_string|&quot;*&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|mask
OL
r_sizeof
(paren
id|data
)paren
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|data
comma
(paren
r_char
id|__user
op_star
)paren
id|buf
op_plus
l_int|12
comma
id|mask
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
id|diva_set_trace_filter
(paren
(paren
r_int
)paren
id|mask
comma
id|data
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|DITRACE_READ_SELECTIVE_TRACE_FILTER
suffix:colon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|diva_get_trace_filter
(paren
r_sizeof
(paren
id|data
)paren
comma
id|data
)paren
)paren
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
(paren
id|buf
comma
id|data
comma
id|ret
)paren
)paren
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|DITRACE_READ_TRACE_ENTRY
suffix:colon
(brace
id|diva_os_spin_lock_magic_t
id|old_irql
suffix:semicolon
id|word
id|size
suffix:semicolon
id|diva_dbg_entry_head_t
op_star
id|pmsg
suffix:semicolon
id|byte
op_star
id|pbuf
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pbuf
op_assign
id|diva_os_malloc
c_func
(paren
l_int|0
comma
id|mask
)paren
)paren
)paren
(brace
r_return
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|pmsg
op_assign
id|diva_maint_get_message
c_func
(paren
op_amp
id|size
comma
op_amp
id|old_irql
)paren
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
OG
id|mask
)paren
(brace
id|diva_maint_ack_message
c_func
(paren
l_int|0
comma
op_amp
id|old_irql
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ret
op_assign
id|size
suffix:semicolon
id|memcpy
c_func
(paren
id|pbuf
comma
id|pmsg
comma
id|size
)paren
suffix:semicolon
id|diva_maint_ack_message
c_func
(paren
l_int|1
comma
op_amp
id|old_irql
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|count
OL
id|size
)paren
op_logical_or
id|diva_os_copy_to_user
(paren
l_int|NULL
comma
id|buf
comma
(paren
r_void
op_star
)paren
id|pbuf
comma
id|size
)paren
)paren
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|diva_os_free
c_func
(paren
l_int|0
comma
id|pbuf
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|DITRACE_READ_TRACE_ENTRYS
suffix:colon
(brace
id|diva_os_spin_lock_magic_t
id|old_irql
suffix:semicolon
id|word
id|size
suffix:semicolon
id|diva_dbg_entry_head_t
op_star
id|pmsg
suffix:semicolon
id|byte
op_star
id|pbuf
op_assign
l_int|NULL
suffix:semicolon
r_int
id|written
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mask
OL
l_int|4096
)paren
(brace
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|pbuf
op_assign
id|diva_os_malloc
c_func
(paren
l_int|0
comma
id|mask
)paren
)paren
)paren
(brace
r_return
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|pmsg
op_assign
id|diva_maint_get_message
c_func
(paren
op_amp
id|size
comma
op_amp
id|old_irql
)paren
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|size
op_plus
l_int|8
)paren
OG
id|mask
)paren
(brace
id|diva_maint_ack_message
c_func
(paren
l_int|0
comma
op_amp
id|old_irql
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t;&t;   Write entry length&n;&t;&t;&t;&t; */
id|pbuf
(braket
id|written
op_increment
)braket
op_assign
(paren
id|byte
)paren
id|size
suffix:semicolon
id|pbuf
(braket
id|written
op_increment
)braket
op_assign
(paren
id|byte
)paren
(paren
id|size
op_rshift
l_int|8
)paren
suffix:semicolon
id|pbuf
(braket
id|written
op_increment
)braket
op_assign
l_int|0
suffix:semicolon
id|pbuf
(braket
id|written
op_increment
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;   Write message&n;&t;&t;&t;&t; */
id|memcpy
c_func
(paren
op_amp
id|pbuf
(braket
id|written
)braket
comma
id|pmsg
comma
id|size
)paren
suffix:semicolon
id|diva_maint_ack_message
c_func
(paren
l_int|1
comma
op_amp
id|old_irql
)paren
suffix:semicolon
id|written
op_add_assign
id|size
suffix:semicolon
id|mask
op_sub_assign
(paren
id|size
op_plus
l_int|4
)paren
suffix:semicolon
)brace
id|pbuf
(braket
id|written
op_increment
)braket
op_assign
l_int|0
suffix:semicolon
id|pbuf
(braket
id|written
op_increment
)braket
op_assign
l_int|0
suffix:semicolon
id|pbuf
(braket
id|written
op_increment
)braket
op_assign
l_int|0
suffix:semicolon
id|pbuf
(braket
id|written
op_increment
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|count
OL
id|written
)paren
op_logical_or
id|diva_os_copy_to_user
c_func
(paren
l_int|NULL
comma
id|buf
comma
(paren
r_void
op_star
)paren
id|pbuf
comma
id|written
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
id|written
suffix:semicolon
)brace
id|diva_os_free
c_func
(paren
l_int|0
comma
id|pbuf
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  init&n; */
DECL|function|mntfunc_init
r_int
id|DIVA_INIT_FUNCTION
id|mntfunc_init
c_func
(paren
r_int
op_star
id|buffer_length
comma
r_void
op_star
op_star
id|buffer
comma
r_int
r_int
id|diva_dbg_mem
)paren
(brace
r_if
c_cond
(paren
op_star
id|buffer_length
OL
l_int|64
)paren
(brace
op_star
id|buffer_length
op_assign
l_int|64
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|buffer_length
OG
l_int|512
)paren
(brace
op_star
id|buffer_length
op_assign
l_int|512
suffix:semicolon
)brace
op_star
id|buffer_length
op_mul_assign
l_int|1024
suffix:semicolon
r_if
c_cond
(paren
id|diva_dbg_mem
)paren
(brace
op_star
id|buffer
op_assign
(paren
r_void
op_star
)paren
id|diva_dbg_mem
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
(paren
op_star
id|buffer_length
op_ge
(paren
l_int|64
op_star
l_int|1024
)paren
)paren
op_logical_and
(paren
op_logical_neg
(paren
op_star
id|buffer
op_assign
id|diva_os_malloc
(paren
l_int|0
comma
op_star
id|buffer_length
)paren
)paren
)paren
)paren
(brace
op_star
id|buffer_length
op_sub_assign
l_int|1024
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|buffer
)paren
(brace
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;init: Can not alloc trace buffer&quot;
)paren
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|diva_maint_init
c_func
(paren
op_star
id|buffer
comma
op_star
id|buffer_length
comma
(paren
id|diva_dbg_mem
op_eq
l_int|0
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|diva_dbg_mem
)paren
(brace
id|diva_os_free
(paren
l_int|0
comma
op_star
id|buffer
)paren
suffix:semicolon
)brace
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;init: maint init failed&quot;
)paren
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|connect_didd
c_func
(paren
)paren
)paren
(brace
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;init: failed to connect to DIDD.&quot;
)paren
)paren
suffix:semicolon
id|diva_maint_finit
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|diva_dbg_mem
)paren
(brace
id|diva_os_free
(paren
l_int|0
comma
op_star
id|buffer
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  exit&n; */
DECL|function|mntfunc_finit
r_void
id|DIVA_EXIT_FUNCTION
id|mntfunc_finit
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|buffer
suffix:semicolon
r_int
id|i
op_assign
l_int|100
suffix:semicolon
id|DbgDeregister
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|diva_mnt_shutdown_xdi_adapters
c_func
(paren
)paren
op_logical_and
id|i
op_decrement
)paren
(brace
id|diva_os_sleep
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
id|disconnect_didd
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buffer
op_assign
id|diva_maint_finit
c_func
(paren
)paren
)paren
)paren
(brace
id|diva_os_free
(paren
l_int|0
comma
id|buffer
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|MAdapter
comma
l_int|0
comma
r_sizeof
(paren
id|MAdapter
)paren
)paren
suffix:semicolon
id|dprintf
op_assign
id|no_printf
suffix:semicolon
)brace
eof
