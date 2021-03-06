multiline_comment|/* $Id: idifunc.c,v 1.14.4.4 2004/08/28 20:03:53 armin Exp $&n; *&n; * Driver for Eicon DIVA Server ISDN cards.&n; * User Mode IDI Interface &n; *&n; * Copyright 2000-2003 by Armin Schindler (mac@melware.de)&n; * Copyright 2000-2003 Cytronics &amp; Melware (info@melware.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; */
macro_line|#include &quot;platform.h&quot;
macro_line|#include &quot;di_defs.h&quot;
macro_line|#include &quot;divasync.h&quot;
macro_line|#include &quot;um_xdi.h&quot;
macro_line|#include &quot;um_idi.h&quot;
DECL|macro|DBG_MINIMUM
mdefine_line|#define DBG_MINIMUM  (DL_LOG + DL_FTL + DL_ERR)
DECL|macro|DBG_DEFAULT
mdefine_line|#define DBG_DEFAULT  (DBG_MINIMUM + DL_XLOG + DL_REG)
r_extern
r_char
op_star
id|DRIVERRELEASE_IDI
suffix:semicolon
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
r_extern
r_int
id|diva_user_mode_idi_create_adapter
c_func
(paren
r_const
id|DESCRIPTOR
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|diva_user_mode_idi_remove_adapter
c_func
(paren
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
multiline_comment|/*&n; * stop debug&n; */
DECL|function|stop_dbg
r_static
r_void
id|stop_dbg
c_func
(paren
r_void
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
DECL|struct|_udiva_card
r_typedef
r_struct
id|_udiva_card
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|Id
r_int
id|Id
suffix:semicolon
DECL|member|d
id|DESCRIPTOR
id|d
suffix:semicolon
DECL|typedef|udiva_card
)brace
id|udiva_card
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|cards
)paren
suffix:semicolon
DECL|variable|ll_lock
r_static
id|diva_os_spin_lock_t
id|ll_lock
suffix:semicolon
multiline_comment|/*&n; * find card in list&n; */
DECL|function|find_card_in_list
r_static
id|udiva_card
op_star
id|find_card_in_list
c_func
(paren
id|DESCRIPTOR
op_star
id|d
)paren
(brace
id|udiva_card
op_star
id|card
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
id|diva_os_spin_lock_magic_t
id|old_irql
suffix:semicolon
id|diva_os_enter_spin_lock
c_func
(paren
op_amp
id|ll_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;find card&quot;
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|tmp
comma
op_amp
id|cards
)paren
(brace
id|card
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
id|udiva_card
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;d.request
op_eq
id|d-&gt;request
)paren
(brace
id|diva_os_leave_spin_lock
c_func
(paren
op_amp
id|ll_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;find card&quot;
)paren
suffix:semicolon
r_return
(paren
id|card
)paren
suffix:semicolon
)brace
)brace
id|diva_os_leave_spin_lock
c_func
(paren
op_amp
id|ll_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;find card&quot;
)paren
suffix:semicolon
r_return
(paren
(paren
id|udiva_card
op_star
)paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * new card&n; */
DECL|function|um_new_card
r_static
r_void
id|um_new_card
c_func
(paren
id|DESCRIPTOR
op_star
id|d
)paren
(brace
r_int
id|adapter_nr
op_assign
l_int|0
suffix:semicolon
id|udiva_card
op_star
id|card
op_assign
l_int|NULL
suffix:semicolon
id|IDI_SYNC_REQ
id|sync_req
suffix:semicolon
id|diva_os_spin_lock_magic_t
id|old_irql
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|card
op_assign
id|diva_os_malloc
c_func
(paren
l_int|0
comma
r_sizeof
(paren
id|udiva_card
)paren
)paren
)paren
)paren
(brace
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;cannot get buffer for card&quot;
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memcpy
c_func
(paren
op_amp
id|card-&gt;d
comma
id|d
comma
r_sizeof
(paren
id|DESCRIPTOR
)paren
)paren
suffix:semicolon
id|sync_req.xdi_logical_adapter_number.Req
op_assign
l_int|0
suffix:semicolon
id|sync_req.xdi_logical_adapter_number.Rc
op_assign
id|IDI_SYNC_REQ_XDI_GET_LOGICAL_ADAPTER_NUMBER
suffix:semicolon
id|card-&gt;d
dot
id|request
c_func
(paren
(paren
id|ENTITY
op_star
)paren
op_amp
id|sync_req
)paren
suffix:semicolon
id|adapter_nr
op_assign
id|sync_req.xdi_logical_adapter_number.info.logical_adapter_number
suffix:semicolon
id|card-&gt;Id
op_assign
id|adapter_nr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|diva_user_mode_idi_create_adapter
c_func
(paren
id|d
comma
id|adapter_nr
)paren
)paren
)paren
(brace
id|diva_os_enter_spin_lock
c_func
(paren
op_amp
id|ll_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;add card&quot;
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|card-&gt;list
comma
op_amp
id|cards
)paren
suffix:semicolon
id|diva_os_leave_spin_lock
c_func
(paren
op_amp
id|ll_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;add card&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;could not create user mode idi card %d&quot;
comma
id|adapter_nr
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * remove card&n; */
DECL|function|um_remove_card
r_static
r_void
id|um_remove_card
c_func
(paren
id|DESCRIPTOR
op_star
id|d
)paren
(brace
id|diva_os_spin_lock_magic_t
id|old_irql
suffix:semicolon
id|udiva_card
op_star
id|card
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|card
op_assign
id|find_card_in_list
c_func
(paren
id|d
)paren
)paren
)paren
(brace
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;cannot find card to remove&quot;
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|diva_user_mode_idi_remove_adapter
c_func
(paren
id|card-&gt;Id
)paren
suffix:semicolon
id|diva_os_enter_spin_lock
c_func
(paren
op_amp
id|ll_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;remove card&quot;
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|card-&gt;list
)paren
suffix:semicolon
id|diva_os_leave_spin_lock
c_func
(paren
op_amp
id|ll_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;remove card&quot;
)paren
suffix:semicolon
id|DBG_LOG
c_func
(paren
(paren
l_string|&quot;idi proc entry removed for card %d&quot;
comma
id|card-&gt;Id
)paren
)paren
suffix:semicolon
id|diva_os_free
c_func
(paren
l_int|0
comma
id|card
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * remove all adapter&n; */
DECL|function|remove_all_idi_proc
r_static
r_void
id|DIVA_EXIT_FUNCTION
id|remove_all_idi_proc
c_func
(paren
r_void
)paren
(brace
id|udiva_card
op_star
id|card
suffix:semicolon
id|diva_os_spin_lock_magic_t
id|old_irql
suffix:semicolon
id|rescan
suffix:colon
id|diva_os_enter_spin_lock
c_func
(paren
op_amp
id|ll_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;remove all&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|cards
)paren
)paren
(brace
id|card
op_assign
id|list_entry
c_func
(paren
id|cards.next
comma
id|udiva_card
comma
id|list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|card-&gt;list
)paren
suffix:semicolon
id|diva_os_leave_spin_lock
c_func
(paren
op_amp
id|ll_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;remove all&quot;
)paren
suffix:semicolon
id|diva_user_mode_idi_remove_adapter
c_func
(paren
id|card-&gt;Id
)paren
suffix:semicolon
id|diva_os_free
c_func
(paren
l_int|0
comma
id|card
)paren
suffix:semicolon
r_goto
id|rescan
suffix:semicolon
)brace
id|diva_os_leave_spin_lock
c_func
(paren
op_amp
id|ll_lock
comma
op_amp
id|old_irql
comma
l_string|&quot;remove all&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * DIDD notify callback&n; */
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
l_string|&quot;Notification about IDI_DADAPTER change ! Oops.&quot;
)paren
)paren
suffix:semicolon
r_return
(paren
l_int|NULL
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
id|stop_dbg
c_func
(paren
)paren
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
l_string|&quot;User IDI&quot;
comma
id|DRIVERRELEASE_IDI
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
multiline_comment|/* IDI Adapter */
r_if
c_cond
(paren
id|removal
)paren
(brace
id|um_remove_card
c_func
(paren
id|adapter
)paren
suffix:semicolon
)brace
r_else
(brace
id|um_new_card
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
multiline_comment|/*&n; * connect DIDD&n; */
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
(brace
id|stop_dbg
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|notify_handle
op_assign
id|req.didd_notify.info.handle
suffix:semicolon
)brace
r_else
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
id|IDI_DIMAINT
)paren
(brace
multiline_comment|/* MAINT found */
id|memcpy
c_func
(paren
op_amp
id|MAdapter
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
l_string|&quot;User IDI&quot;
comma
id|DRIVERRELEASE_IDI
comma
id|DBG_DEFAULT
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
multiline_comment|/* IDI Adapter found */
id|um_new_card
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
r_if
c_cond
(paren
op_logical_neg
id|dadapter
)paren
(brace
id|stop_dbg
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
(paren
id|dadapter
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Disconnect from DIDD&n; */
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
id|stop_dbg
c_func
(paren
)paren
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
)brace
multiline_comment|/*&n; * init&n; */
DECL|function|idifunc_init
r_int
id|DIVA_INIT_FUNCTION
id|idifunc_init
c_func
(paren
r_void
)paren
(brace
id|diva_os_initialize_spin_lock
c_func
(paren
op_amp
id|ll_lock
comma
l_string|&quot;idifunc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diva_user_mode_idi_init
c_func
(paren
)paren
)paren
(brace
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;init: init failed.&quot;
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
id|diva_user_mode_idi_finit
c_func
(paren
)paren
suffix:semicolon
id|DBG_ERR
c_func
(paren
(paren
l_string|&quot;init: failed to connect to DIDD.&quot;
)paren
)paren
suffix:semicolon
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
multiline_comment|/*&n; * finit&n; */
DECL|function|idifunc_finit
r_void
id|DIVA_EXIT_FUNCTION
id|idifunc_finit
c_func
(paren
r_void
)paren
(brace
id|diva_user_mode_idi_finit
c_func
(paren
)paren
suffix:semicolon
id|disconnect_didd
c_func
(paren
)paren
suffix:semicolon
id|remove_all_idi_proc
c_func
(paren
)paren
suffix:semicolon
)brace
eof
