multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    2.1&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &quot;platform.h&quot;
macro_line|#include &quot;pc.h&quot;
macro_line|#include &quot;debuglib.h&quot;
macro_line|#include &quot;di_defs.h&quot;
macro_line|#include &quot;divasync.h&quot;
macro_line|#include &quot;dadapter.h&quot;
multiline_comment|/* --------------------------------------------------------------------------&n;  Adapter array change notification framework&n;   -------------------------------------------------------------------------- */
DECL|struct|_didd_adapter_change_notification
r_typedef
r_struct
id|_didd_adapter_change_notification
(brace
DECL|member|callback
id|didd_adapter_change_callback_t
id|callback
suffix:semicolon
DECL|member|context
r_void
id|IDI_CALL_ENTITY_T
op_star
id|context
suffix:semicolon
DECL|typedef|didd_adapter_change_notification_t
)brace
id|didd_adapter_change_notification_t
comma
"&bslash;"
DECL|typedef|pdidd_adapter_change_notification_t
op_star
id|IDI_CALL_ENTITY_T
id|pdidd_adapter_change_notification_t
suffix:semicolon
DECL|macro|DIVA_DIDD_MAX_NOTIFICATIONS
mdefine_line|#define DIVA_DIDD_MAX_NOTIFICATIONS 256
r_static
id|didd_adapter_change_notification_t
"&bslash;"
DECL|variable|NotificationTable
id|NotificationTable
(braket
id|DIVA_DIDD_MAX_NOTIFICATIONS
)braket
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;  Array to held adapter information&n;   -------------------------------------------------------------------------- */
DECL|variable|HandleTable
r_static
id|DESCRIPTOR
id|HandleTable
(braket
id|NEW_MAX_DESCRIPTORS
)braket
suffix:semicolon
DECL|variable|Adapters
id|dword
id|Adapters
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Number of adapters */
multiline_comment|/* --------------------------------------------------------------------------&n;  Shadow IDI_DIMAINT&n;  and &squot;shadow&squot; debug stuff&n;   -------------------------------------------------------------------------- */
DECL|function|no_printf
r_static
r_void
id|no_printf
(paren
r_int
r_char
op_star
id|format
comma
dot
dot
dot
)paren
(brace
)brace
DECL|variable|dprintf
id|DIVA_DI_PRINTF
id|dprintf
op_assign
id|no_printf
suffix:semicolon
DECL|variable|MAdapter
r_static
id|DESCRIPTOR
id|MAdapter
op_assign
(brace
id|IDI_DIMAINT
comma
multiline_comment|/* Adapter Type */
l_int|0x00
comma
multiline_comment|/* Channels */
l_int|0x0000
comma
multiline_comment|/* Features */
(paren
id|IDI_CALL
)paren
id|no_printf
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;  DAdapter. Only IDI clients with buffer, that is huge enough to&n;  get all descriptors will receive information about DAdapter&n;  { byte type, byte channels, word features, IDI_CALL request }&n;   -------------------------------------------------------------------------- */
r_static
r_void
id|IDI_CALL_LINK_T
id|diva_dadapter_request
(paren
id|ENTITY
id|IDI_CALL_ENTITY_T
op_star
)paren
suffix:semicolon
DECL|variable|DAdapter
r_static
id|DESCRIPTOR
id|DAdapter
op_assign
(brace
id|IDI_DADAPTER
comma
multiline_comment|/* Adapter Type */
l_int|0x00
comma
multiline_comment|/* Channels */
l_int|0x0000
comma
multiline_comment|/* Features */
id|diva_dadapter_request
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;  LOCALS&n;   -------------------------------------------------------------------------- */
r_static
id|dword
id|diva_register_adapter_callback
(paren
"&bslash;"
id|didd_adapter_change_callback_t
id|callback
comma
r_void
id|IDI_CALL_ENTITY_T
op_star
id|context
)paren
suffix:semicolon
r_static
r_void
id|diva_remove_adapter_callback
(paren
id|dword
id|handle
)paren
suffix:semicolon
r_static
r_void
id|diva_notify_adapter_change
(paren
id|DESCRIPTOR
op_star
id|d
comma
r_int
id|removal
)paren
suffix:semicolon
DECL|variable|didd_spin
r_static
id|diva_os_spin_lock_t
id|didd_spin
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;  Should be called as first step, after driver init&n;  -------------------------------------------------------------------------- */
DECL|function|diva_didd_load_time_init
r_void
id|diva_didd_load_time_init
(paren
r_void
)paren
(brace
id|memset
(paren
op_amp
id|HandleTable
(braket
l_int|0
)braket
comma
l_int|0x00
comma
r_sizeof
(paren
id|HandleTable
)paren
)paren
suffix:semicolon
id|memset
(paren
op_amp
id|NotificationTable
(braket
l_int|0
)braket
comma
l_int|0x00
comma
r_sizeof
(paren
id|NotificationTable
)paren
)paren
suffix:semicolon
id|diva_os_initialize_spin_lock
(paren
op_amp
id|didd_spin
comma
l_string|&quot;didd&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;  Should be called as last step, if driver does unload&n;  -------------------------------------------------------------------------- */
DECL|function|diva_didd_load_time_finit
r_void
id|diva_didd_load_time_finit
(paren
r_void
)paren
(brace
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;  Called in order to register new adapter in adapter array&n;  return adapter handle (&gt; 0) on success&n;  return -1 adapter array overflow&n;  -------------------------------------------------------------------------- */
DECL|function|diva_didd_add_descriptor
r_int
id|diva_didd_add_descriptor
(paren
id|DESCRIPTOR
op_star
id|d
)paren
(brace
id|diva_os_spin_lock_magic_t
id|irql
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;type
op_eq
id|IDI_DIMAINT
)paren
(brace
r_if
c_cond
(paren
id|d-&gt;request
)paren
(brace
id|MAdapter.request
op_assign
id|d-&gt;request
suffix:semicolon
id|dprintf
op_assign
(paren
id|DIVA_DI_PRINTF
)paren
id|d-&gt;request
suffix:semicolon
id|diva_notify_adapter_change
(paren
op_amp
id|MAdapter
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Inserted */
id|DBG_TRC
(paren
(paren
l_string|&quot;DIMAINT registered, dprintf=%08x&quot;
comma
id|d-&gt;request
)paren
)paren
)brace
r_else
(brace
id|DBG_TRC
(paren
(paren
l_string|&quot;DIMAINT removed&quot;
)paren
)paren
id|diva_notify_adapter_change
(paren
op_amp
id|MAdapter
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* About to remove */
id|MAdapter.request
op_assign
(paren
id|IDI_CALL
)paren
id|no_printf
suffix:semicolon
id|dprintf
op_assign
id|no_printf
suffix:semicolon
)brace
r_return
(paren
id|NEW_MAX_DESCRIPTORS
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NEW_MAX_DESCRIPTORS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|diva_os_enter_spin_lock
(paren
op_amp
id|didd_spin
comma
op_amp
id|irql
comma
l_string|&quot;didd_add&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|HandleTable
(braket
id|i
)braket
dot
id|type
op_eq
l_int|0
)paren
(brace
id|memcpy
(paren
op_amp
id|HandleTable
(braket
id|i
)braket
comma
id|d
comma
r_sizeof
(paren
op_star
id|d
)paren
)paren
suffix:semicolon
id|Adapters
op_increment
suffix:semicolon
id|diva_os_leave_spin_lock
(paren
op_amp
id|didd_spin
comma
op_amp
id|irql
comma
l_string|&quot;didd_add&quot;
)paren
suffix:semicolon
id|diva_notify_adapter_change
(paren
id|d
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* we have new adapter */
id|DBG_TRC
(paren
(paren
l_string|&quot;Add adapter[%d], request=%08x&quot;
comma
(paren
id|i
op_plus
l_int|1
)paren
comma
id|d-&gt;request
)paren
)paren
r_return
(paren
id|i
op_plus
l_int|1
)paren
suffix:semicolon
)brace
id|diva_os_leave_spin_lock
(paren
op_amp
id|didd_spin
comma
op_amp
id|irql
comma
l_string|&quot;didd_add&quot;
)paren
suffix:semicolon
)brace
id|DBG_ERR
(paren
(paren
l_string|&quot;Can&squot;t add adapter, out of resources&quot;
)paren
)paren
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;  Called in order to remove one registered adapter from array&n;  return adapter handle (&gt; 0) on success&n;  return 0 on success&n;  -------------------------------------------------------------------------- */
DECL|function|diva_didd_remove_descriptor
r_int
id|diva_didd_remove_descriptor
(paren
id|IDI_CALL
id|request
)paren
(brace
id|diva_os_spin_lock_magic_t
id|irql
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|MAdapter.request
)paren
(brace
id|DBG_TRC
c_func
(paren
(paren
l_string|&quot;DIMAINT removed&quot;
)paren
)paren
id|dprintf
op_assign
id|no_printf
suffix:semicolon
id|diva_notify_adapter_change
(paren
op_amp
id|MAdapter
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* About to remove */
id|MAdapter.request
op_assign
(paren
id|IDI_CALL
)paren
id|no_printf
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|Adapters
op_logical_and
(paren
id|i
OL
id|NEW_MAX_DESCRIPTORS
)paren
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|HandleTable
(braket
id|i
)braket
dot
id|request
op_eq
id|request
)paren
(brace
id|diva_notify_adapter_change
(paren
op_amp
id|HandleTable
(braket
id|i
)braket
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* About to remove */
id|diva_os_enter_spin_lock
(paren
op_amp
id|didd_spin
comma
op_amp
id|irql
comma
l_string|&quot;didd_rm&quot;
)paren
suffix:semicolon
id|memset
(paren
op_amp
id|HandleTable
(braket
id|i
)braket
comma
l_int|0x00
comma
r_sizeof
(paren
id|HandleTable
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|Adapters
op_decrement
suffix:semicolon
id|diva_os_leave_spin_lock
(paren
op_amp
id|didd_spin
comma
op_amp
id|irql
comma
l_string|&quot;didd_rm&quot;
)paren
suffix:semicolon
id|DBG_TRC
(paren
(paren
l_string|&quot;Remove adapter[%d], request=%08x&quot;
comma
(paren
id|i
op_plus
l_int|1
)paren
comma
id|request
)paren
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
id|DBG_ERR
(paren
(paren
l_string|&quot;Invalid request=%08x, can&squot;t remove adapter&quot;
comma
id|request
)paren
)paren
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;  Read adapter array&n;  return 1 if not enough space to save all available adapters&n;   -------------------------------------------------------------------------- */
DECL|function|diva_didd_read_adapter_array
r_int
id|diva_didd_read_adapter_array
(paren
id|DESCRIPTOR
op_star
id|buffer
comma
r_int
id|length
)paren
(brace
id|diva_os_spin_lock_magic_t
id|irql
suffix:semicolon
r_int
id|src
comma
id|dst
suffix:semicolon
id|memset
(paren
id|buffer
comma
l_int|0x00
comma
id|length
)paren
suffix:semicolon
id|length
op_div_assign
r_sizeof
(paren
id|DESCRIPTOR
)paren
suffix:semicolon
id|DBG_TRC
(paren
(paren
l_string|&quot;DIDD_Read, space = %d, Adapters = %d&quot;
comma
id|length
comma
id|Adapters
op_plus
l_int|2
)paren
)paren
id|diva_os_enter_spin_lock
(paren
op_amp
id|didd_spin
comma
op_amp
id|irql
comma
l_string|&quot;didd_read&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|src
op_assign
l_int|0
comma
id|dst
op_assign
l_int|0
suffix:semicolon
(paren
id|Adapters
op_logical_and
(paren
id|src
OL
id|NEW_MAX_DESCRIPTORS
)paren
op_logical_and
(paren
id|dst
OL
id|length
)paren
)paren
suffix:semicolon
id|src
op_increment
)paren
(brace
r_if
c_cond
(paren
id|HandleTable
(braket
id|src
)braket
dot
id|type
)paren
(brace
id|memcpy
(paren
op_amp
id|buffer
(braket
id|dst
)braket
comma
op_amp
id|HandleTable
(braket
id|src
)braket
comma
r_sizeof
(paren
id|DESCRIPTOR
)paren
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
)brace
)brace
id|diva_os_leave_spin_lock
(paren
op_amp
id|didd_spin
comma
op_amp
id|irql
comma
l_string|&quot;didd_read&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dst
OL
id|length
)paren
(brace
id|memcpy
(paren
op_amp
id|buffer
(braket
id|dst
)braket
comma
op_amp
id|MAdapter
comma
r_sizeof
(paren
id|DESCRIPTOR
)paren
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
)brace
r_else
(brace
id|DBG_ERR
(paren
(paren
l_string|&quot;Can&squot;t write DIMAINT. Array too small&quot;
)paren
)paren
)brace
r_if
c_cond
(paren
id|dst
OL
id|length
)paren
(brace
id|memcpy
(paren
op_amp
id|buffer
(braket
id|dst
)braket
comma
op_amp
id|DAdapter
comma
r_sizeof
(paren
id|DESCRIPTOR
)paren
)paren
suffix:semicolon
id|dst
op_increment
suffix:semicolon
)brace
r_else
(brace
id|DBG_ERR
(paren
(paren
l_string|&quot;Can&squot;t write DADAPTER. Array too small&quot;
)paren
)paren
)brace
id|DBG_TRC
(paren
(paren
l_string|&quot;Read %d adapters&quot;
comma
id|dst
)paren
)paren
r_return
(paren
id|dst
op_eq
id|length
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;  DAdapter request function.&n;  This function does process only synchronous requests, and is used&n;  for reception/registration of new interfaces&n;   -------------------------------------------------------------------------- */
r_static
r_void
id|IDI_CALL_LINK_T
id|diva_dadapter_request
(paren
"&bslash;"
id|ENTITY
id|IDI_CALL_ENTITY_T
op_star
id|e
)paren
(brace
id|IDI_SYNC_REQ
op_star
id|syncReq
op_assign
(paren
id|IDI_SYNC_REQ
op_star
)paren
id|e
suffix:semicolon
r_if
c_cond
(paren
id|e-&gt;Req
)paren
(brace
multiline_comment|/* We do not process it, also return error */
id|e-&gt;Rc
op_assign
id|OUT_OF_RESOURCES
suffix:semicolon
id|DBG_ERR
(paren
(paren
l_string|&quot;Can&squot;t process async request, Req=%02x&quot;
comma
id|e-&gt;Req
)paren
)paren
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;  So, we process sync request&n;  */
r_switch
c_cond
(paren
id|e-&gt;Rc
)paren
(brace
r_case
id|IDI_SYNC_REQ_DIDD_REGISTER_ADAPTER_NOTIFY
suffix:colon
(brace
id|diva_didd_adapter_notify_t
op_star
id|pinfo
op_assign
op_amp
id|syncReq-&gt;didd_notify.info
suffix:semicolon
id|pinfo-&gt;handle
op_assign
id|diva_register_adapter_callback
(paren
"&bslash;"
(paren
id|didd_adapter_change_callback_t
)paren
id|pinfo-&gt;callback
comma
(paren
r_void
id|IDI_CALL_ENTITY_T
op_star
)paren
id|pinfo-&gt;context
)paren
suffix:semicolon
id|e-&gt;Rc
op_assign
l_int|0xff
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|IDI_SYNC_REQ_DIDD_REMOVE_ADAPTER_NOTIFY
suffix:colon
(brace
id|diva_didd_adapter_notify_t
op_star
id|pinfo
op_assign
op_amp
id|syncReq-&gt;didd_notify.info
suffix:semicolon
id|diva_remove_adapter_callback
(paren
id|pinfo-&gt;handle
)paren
suffix:semicolon
id|e-&gt;Rc
op_assign
l_int|0xff
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|IDI_SYNC_REQ_DIDD_ADD_ADAPTER
suffix:colon
(brace
id|diva_didd_add_adapter_t
op_star
id|pinfo
op_assign
op_amp
id|syncReq-&gt;didd_add_adapter.info
suffix:semicolon
r_if
c_cond
(paren
id|diva_didd_add_descriptor
(paren
(paren
id|DESCRIPTOR
op_star
)paren
id|pinfo-&gt;descriptor
)paren
OL
l_int|0
)paren
(brace
id|e-&gt;Rc
op_assign
id|OUT_OF_RESOURCES
suffix:semicolon
)brace
r_else
(brace
id|e-&gt;Rc
op_assign
l_int|0xff
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|IDI_SYNC_REQ_DIDD_REMOVE_ADAPTER
suffix:colon
(brace
id|diva_didd_remove_adapter_t
op_star
id|pinfo
op_assign
op_amp
id|syncReq-&gt;didd_remove_adapter.info
suffix:semicolon
r_if
c_cond
(paren
id|diva_didd_remove_descriptor
(paren
(paren
id|IDI_CALL
)paren
id|pinfo-&gt;p_request
)paren
OL
l_int|0
)paren
(brace
id|e-&gt;Rc
op_assign
id|OUT_OF_RESOURCES
suffix:semicolon
)brace
r_else
(brace
id|e-&gt;Rc
op_assign
l_int|0xff
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|IDI_SYNC_REQ_DIDD_READ_ADAPTER_ARRAY
suffix:colon
(brace
id|diva_didd_read_adapter_array_t
op_star
id|pinfo
op_assign
"&bslash;"
op_amp
id|syncReq-&gt;didd_read_adapter_array.info
suffix:semicolon
r_if
c_cond
(paren
id|diva_didd_read_adapter_array
(paren
(paren
id|DESCRIPTOR
op_star
)paren
id|pinfo-&gt;buffer
comma
(paren
r_int
)paren
id|pinfo-&gt;length
)paren
)paren
(brace
id|e-&gt;Rc
op_assign
id|OUT_OF_RESOURCES
suffix:semicolon
)brace
r_else
(brace
id|e-&gt;Rc
op_assign
l_int|0xff
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|DBG_ERR
(paren
(paren
l_string|&quot;Can&squot;t process sync request, Req=%02x&quot;
comma
id|e-&gt;Rc
)paren
)paren
id|e-&gt;Rc
op_assign
id|OUT_OF_RESOURCES
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;  IDI client does register his notification function&n;  -------------------------------------------------------------------------- */
r_static
id|dword
id|diva_register_adapter_callback
(paren
"&bslash;"
id|didd_adapter_change_callback_t
id|callback
comma
r_void
id|IDI_CALL_ENTITY_T
op_star
id|context
)paren
(brace
id|diva_os_spin_lock_magic_t
id|irql
suffix:semicolon
id|dword
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
id|DIVA_DIDD_MAX_NOTIFICATIONS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|diva_os_enter_spin_lock
(paren
op_amp
id|didd_spin
comma
op_amp
id|irql
comma
l_string|&quot;didd_nfy_add&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|NotificationTable
(braket
id|i
)braket
dot
id|callback
)paren
(brace
id|NotificationTable
(braket
id|i
)braket
dot
id|callback
op_assign
id|callback
suffix:semicolon
id|NotificationTable
(braket
id|i
)braket
dot
id|context
op_assign
id|context
suffix:semicolon
id|diva_os_leave_spin_lock
(paren
op_amp
id|didd_spin
comma
op_amp
id|irql
comma
l_string|&quot;didd_nfy_add&quot;
)paren
suffix:semicolon
id|DBG_TRC
c_func
(paren
(paren
l_string|&quot;Register adapter notification[%d]=%08x&quot;
comma
id|i
op_plus
l_int|1
comma
id|callback
)paren
)paren
r_return
(paren
id|i
op_plus
l_int|1
)paren
suffix:semicolon
)brace
id|diva_os_leave_spin_lock
(paren
op_amp
id|didd_spin
comma
op_amp
id|irql
comma
l_string|&quot;didd_nfy_add&quot;
)paren
suffix:semicolon
)brace
id|DBG_ERR
(paren
(paren
l_string|&quot;Can&squot;t register adapter notification, overflow&quot;
)paren
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;  IDI client does register his notification function&n;  -------------------------------------------------------------------------- */
DECL|function|diva_remove_adapter_callback
r_static
r_void
id|diva_remove_adapter_callback
(paren
id|dword
id|handle
)paren
(brace
id|diva_os_spin_lock_magic_t
id|irql
suffix:semicolon
r_if
c_cond
(paren
id|handle
op_logical_and
(paren
(paren
op_decrement
id|handle
)paren
OL
id|DIVA_DIDD_MAX_NOTIFICATIONS
)paren
)paren
(brace
id|diva_os_enter_spin_lock
(paren
op_amp
id|didd_spin
comma
op_amp
id|irql
comma
l_string|&quot;didd_nfy_rm&quot;
)paren
suffix:semicolon
id|NotificationTable
(braket
id|handle
)braket
dot
id|callback
op_assign
l_int|0
suffix:semicolon
id|NotificationTable
(braket
id|handle
)braket
dot
id|context
op_assign
l_int|0
suffix:semicolon
id|diva_os_leave_spin_lock
(paren
op_amp
id|didd_spin
comma
op_amp
id|irql
comma
l_string|&quot;didd_nfy_rm&quot;
)paren
suffix:semicolon
id|DBG_TRC
c_func
(paren
(paren
l_string|&quot;Remove adapter notification[%d]&quot;
comma
(paren
r_int
)paren
(paren
id|handle
op_plus
l_int|1
)paren
)paren
)paren
r_return
suffix:semicolon
)brace
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;Can&squot;t remove adapter notification, handle=%d&quot;
comma
id|handle
)paren
)paren
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;  Notify all client about adapter array change&n;  Does suppose following behavior in the client side:&n;  Step 1: Redister Notification&n;  Step 2: Read Adapter Array&n;  -------------------------------------------------------------------------- */
DECL|function|diva_notify_adapter_change
r_static
r_void
id|diva_notify_adapter_change
(paren
id|DESCRIPTOR
op_star
id|d
comma
r_int
id|removal
)paren
(brace
r_int
id|i
comma
id|do_notify
suffix:semicolon
id|didd_adapter_change_notification_t
id|nfy
suffix:semicolon
id|diva_os_spin_lock_magic_t
id|irql
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
id|DIVA_DIDD_MAX_NOTIFICATIONS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|do_notify
op_assign
l_int|0
suffix:semicolon
id|diva_os_enter_spin_lock
(paren
op_amp
id|didd_spin
comma
op_amp
id|irql
comma
l_string|&quot;didd_nfy&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|NotificationTable
(braket
id|i
)braket
dot
id|callback
)paren
(brace
id|memcpy
(paren
op_amp
id|nfy
comma
op_amp
id|NotificationTable
(braket
id|i
)braket
comma
r_sizeof
(paren
id|nfy
)paren
)paren
suffix:semicolon
id|do_notify
op_assign
l_int|1
suffix:semicolon
)brace
id|diva_os_leave_spin_lock
(paren
op_amp
id|didd_spin
comma
op_amp
id|irql
comma
l_string|&quot;didd_nfy&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|do_notify
)paren
(brace
(paren
op_star
(paren
id|nfy.callback
)paren
)paren
(paren
id|nfy.context
comma
id|d
comma
id|removal
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;  For all systems, that are linked by Kernel Mode Linker this is ONLY one&n;  function thet should be exported by this device driver&n;  IDI clients should look for IDI_DADAPTER, and use request function&n;  of this adapter (sync request) in order to receive appropriate services:&n;  - add new adapter&n;  - remove existing adapter&n;  - add adapter array notification&n;  - remove adapter array notification&n;  (read adapter is redundant in this case)&n;  INPUT:&n;   buffer - pointer to buffer that will receive adapter array&n;   length  - length (in bytes) of space in buffer&n;  OUTPUT:&n;   Adapter array will be written to memory described by &squot;buffer&squot;&n;   If the last adapter seen in the returned adapter array is&n;   IDI_DADAPTER or if last adapter in array does have type &squot;0&squot;, then&n;   it was enougth space in buffer to accommodate all available&n;   adapter descriptors&n;  *NOTE 1 (debug interface):&n;   The IDI adapter of type &squot;IDI_DIMAINT&squot; does register as &squot;request&squot;&n;   famous &squot;dprintf&squot; function (of type DI_PRINTF, please look&n;   include/debuglib.c and include/debuglib.h) for details.&n;   So dprintf is not exported from module debug module directly,&n;   instead of this IDI_DIMAINT is registered.&n;   Module load order will receive in this case:&n;    1. DIDD (this file)&n;    2. DIMAINT does load and register &squot;IDI_DIMAINT&squot;, at this step&n;      DIDD should be able to get &squot;dprintf&squot;, save it, and&n;      register with DIDD by means of &squot;dprintf&squot; function.&n;    3. any other driver is loaded and is able to access adapter array&n;      and debug interface&n;   This approach does allow to load/unload debug interface on demand,&n;   and save memory, it it is necessary.&n;  -------------------------------------------------------------------------- */
DECL|function|DIVA_DIDD_Read
r_void
id|IDI_CALL_LINK_T
id|DIVA_DIDD_Read
(paren
r_void
id|IDI_CALL_ENTITY_T
op_star
id|buffer
comma
r_int
id|length
)paren
(brace
id|diva_didd_read_adapter_array
(paren
id|buffer
comma
id|length
)paren
suffix:semicolon
)brace
multiline_comment|/* -------------------------------------------------------------------------&n;  Portable debug Library&n;  ------------------------------------------------------------------------- */
macro_line|#include &quot;debuglib.c&quot;
eof
