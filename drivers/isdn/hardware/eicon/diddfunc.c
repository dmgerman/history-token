multiline_comment|/* $Id: diddfunc.c,v 1.1.2.2 2002/10/02 14:38:37 armin Exp $&n; *&n; * DIDD Interface module for Eicon active cards.&n; * &n; * Functions are in dadapter.c &n; * &n; * Copyright 2002 by Armin Schindler (mac@melware.de) &n; * Copyright 2002 Cytronics &amp; Melware (info@melware.de)&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; */
macro_line|#include &quot;platform.h&quot;
macro_line|#include &quot;di_defs.h&quot;
macro_line|#include &quot;dadapter.h&quot;
macro_line|#include &quot;divasync.h&quot;
DECL|macro|MAX_DESCRIPTORS
mdefine_line|#define MAX_DESCRIPTORS  32
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
r_extern
r_char
op_star
id|DRIVERRELEASE
suffix:semicolon
DECL|variable|notify_handle
r_static
id|dword
id|notify_handle
suffix:semicolon
DECL|variable|_DAdapter
r_static
id|DESCRIPTOR
id|_DAdapter
suffix:semicolon
multiline_comment|/*&n; * didd callback function&n; */
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
id|DbgDeregister
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|DbgRegister
c_func
(paren
l_string|&quot;DIDD&quot;
comma
id|DRIVERRELEASE
comma
id|DBG_DEFAULT
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
id|_DAdapter
comma
op_amp
id|DIDD_Table
(braket
id|x
)braket
comma
r_sizeof
(paren
id|_DAdapter
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
id|didd_callback
suffix:semicolon
id|req.didd_notify.info.context
op_assign
l_int|0
suffix:semicolon
id|_DAdapter
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
id|DbgRegister
c_func
(paren
l_string|&quot;DIDD&quot;
comma
id|DRIVERRELEASE
comma
id|DBG_DEFAULT
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
id|_DAdapter
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
DECL|function|diddfunc_init
r_int
id|DIVA_INIT_FUNCTION
id|diddfunc_init
c_func
(paren
r_void
)paren
(brace
id|diva_didd_load_time_init
c_func
(paren
)paren
suffix:semicolon
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
id|diva_didd_load_time_finit
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
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * finit&n; */
DECL|function|diddfunc_finit
r_void
id|DIVA_EXIT_FUNCTION
id|diddfunc_finit
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
id|disconnect_didd
c_func
(paren
)paren
suffix:semicolon
id|diva_didd_load_time_finit
c_func
(paren
)paren
suffix:semicolon
)brace
eof
