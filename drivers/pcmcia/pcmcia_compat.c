multiline_comment|/*&n; * PCMCIA 16-bit compatibility functions&n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Copyright (C) 2004 Dominik Brodowski&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|macro|IN_CARD_SERVICES
mdefine_line|#define IN_CARD_SERVICES
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/bulkmem.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &lt;pcmcia/ds.h&gt;
macro_line|#include &lt;pcmcia/ss.h&gt;
macro_line|#include &quot;cs_internal.h&quot;
DECL|function|pcmcia_get_first_tuple
r_int
id|pcmcia_get_first_tuple
c_func
(paren
id|client_handle_t
id|handle
comma
id|tuple_t
op_star
id|tuple
)paren
(brace
r_struct
id|pcmcia_socket
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_HANDLE
c_func
(paren
id|handle
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
id|s
op_assign
id|SOCKET
c_func
(paren
id|handle
)paren
suffix:semicolon
r_return
id|pccard_get_first_tuple
c_func
(paren
id|s
comma
id|handle-&gt;Function
comma
id|tuple
)paren
suffix:semicolon
)brace
DECL|variable|pcmcia_get_first_tuple
id|EXPORT_SYMBOL
c_func
(paren
id|pcmcia_get_first_tuple
)paren
suffix:semicolon
DECL|function|pcmcia_get_next_tuple
r_int
id|pcmcia_get_next_tuple
c_func
(paren
id|client_handle_t
id|handle
comma
id|tuple_t
op_star
id|tuple
)paren
(brace
r_struct
id|pcmcia_socket
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_HANDLE
c_func
(paren
id|handle
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
id|s
op_assign
id|SOCKET
c_func
(paren
id|handle
)paren
suffix:semicolon
r_return
id|pccard_get_next_tuple
c_func
(paren
id|s
comma
id|handle-&gt;Function
comma
id|tuple
)paren
suffix:semicolon
)brace
DECL|variable|pcmcia_get_next_tuple
id|EXPORT_SYMBOL
c_func
(paren
id|pcmcia_get_next_tuple
)paren
suffix:semicolon
DECL|function|pcmcia_get_tuple_data
r_int
id|pcmcia_get_tuple_data
c_func
(paren
id|client_handle_t
id|handle
comma
id|tuple_t
op_star
id|tuple
)paren
(brace
r_struct
id|pcmcia_socket
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_HANDLE
c_func
(paren
id|handle
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
id|s
op_assign
id|SOCKET
c_func
(paren
id|handle
)paren
suffix:semicolon
r_return
id|pccard_get_tuple_data
c_func
(paren
id|s
comma
id|tuple
)paren
suffix:semicolon
)brace
DECL|variable|pcmcia_get_tuple_data
id|EXPORT_SYMBOL
c_func
(paren
id|pcmcia_get_tuple_data
)paren
suffix:semicolon
DECL|function|pcmcia_parse_tuple
r_int
id|pcmcia_parse_tuple
c_func
(paren
id|client_handle_t
id|handle
comma
id|tuple_t
op_star
id|tuple
comma
id|cisparse_t
op_star
id|parse
)paren
(brace
r_return
id|pccard_parse_tuple
c_func
(paren
id|tuple
comma
id|parse
)paren
suffix:semicolon
)brace
DECL|variable|pcmcia_parse_tuple
id|EXPORT_SYMBOL
c_func
(paren
id|pcmcia_parse_tuple
)paren
suffix:semicolon
DECL|function|pcmcia_validate_cis
r_int
id|pcmcia_validate_cis
c_func
(paren
id|client_handle_t
id|handle
comma
id|cisinfo_t
op_star
id|info
)paren
(brace
r_struct
id|pcmcia_socket
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_HANDLE
c_func
(paren
id|handle
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
id|s
op_assign
id|SOCKET
c_func
(paren
id|handle
)paren
suffix:semicolon
r_return
id|pccard_validate_cis
c_func
(paren
id|s
comma
id|handle-&gt;Function
comma
id|info
)paren
suffix:semicolon
)brace
DECL|variable|pcmcia_validate_cis
id|EXPORT_SYMBOL
c_func
(paren
id|pcmcia_validate_cis
)paren
suffix:semicolon
DECL|function|pcmcia_get_configuration_info
r_int
id|pcmcia_get_configuration_info
c_func
(paren
id|client_handle_t
id|handle
comma
id|config_info_t
op_star
id|config
)paren
(brace
r_struct
id|pcmcia_socket
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
(paren
id|CHECK_HANDLE
c_func
(paren
id|handle
)paren
)paren
op_logical_or
op_logical_neg
id|config
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
id|s
op_assign
id|SOCKET
c_func
(paren
id|handle
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
r_return
id|pccard_get_configuration_info
c_func
(paren
id|s
comma
id|handle-&gt;Function
comma
id|config
)paren
suffix:semicolon
)brace
DECL|variable|pcmcia_get_configuration_info
id|EXPORT_SYMBOL
c_func
(paren
id|pcmcia_get_configuration_info
)paren
suffix:semicolon
DECL|function|pcmcia_reset_card
r_int
id|pcmcia_reset_card
c_func
(paren
id|client_handle_t
id|handle
comma
id|client_req_t
op_star
id|req
)paren
(brace
r_struct
id|pcmcia_socket
op_star
id|skt
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_HANDLE
c_func
(paren
id|handle
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
id|skt
op_assign
id|SOCKET
c_func
(paren
id|handle
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skt
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
r_return
id|pccard_reset_card
c_func
(paren
id|skt
)paren
suffix:semicolon
)brace
DECL|variable|pcmcia_reset_card
id|EXPORT_SYMBOL
c_func
(paren
id|pcmcia_reset_card
)paren
suffix:semicolon
DECL|function|pcmcia_get_status
r_int
id|pcmcia_get_status
c_func
(paren
id|client_handle_t
id|handle
comma
id|cs_status_t
op_star
id|status
)paren
(brace
r_struct
id|pcmcia_socket
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_HANDLE
c_func
(paren
id|handle
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
id|s
op_assign
id|SOCKET
c_func
(paren
id|handle
)paren
suffix:semicolon
r_return
id|pccard_get_status
c_func
(paren
id|s
comma
id|handle-&gt;Function
comma
id|status
)paren
suffix:semicolon
)brace
DECL|variable|pcmcia_get_status
id|EXPORT_SYMBOL
c_func
(paren
id|pcmcia_get_status
)paren
suffix:semicolon
DECL|function|pcmcia_access_configuration_register
r_int
id|pcmcia_access_configuration_register
c_func
(paren
id|client_handle_t
id|handle
comma
id|conf_reg_t
op_star
id|reg
)paren
(brace
r_struct
id|pcmcia_socket
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_HANDLE
c_func
(paren
id|handle
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
id|s
op_assign
id|SOCKET
c_func
(paren
id|handle
)paren
suffix:semicolon
r_return
id|pccard_access_configuration_register
c_func
(paren
id|s
comma
id|handle-&gt;Function
comma
id|reg
)paren
suffix:semicolon
)brace
DECL|variable|pcmcia_access_configuration_register
id|EXPORT_SYMBOL
c_func
(paren
id|pcmcia_access_configuration_register
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCMCIA_OBSOLETE
DECL|function|pcmcia_get_first_window
r_int
id|pcmcia_get_first_window
c_func
(paren
id|window_handle_t
op_star
id|win
comma
id|win_req_t
op_star
id|req
)paren
(brace
r_if
c_cond
(paren
(paren
id|win
op_eq
l_int|NULL
)paren
op_logical_or
(paren
(paren
op_star
id|win
)paren
op_member_access_from_pointer
id|magic
op_ne
id|WINDOW_MAGIC
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
r_return
id|pcmcia_get_window
c_func
(paren
(paren
(paren
id|client_handle_t
)paren
op_star
id|win
)paren
op_member_access_from_pointer
id|Socket
comma
id|win
comma
l_int|0
comma
id|req
)paren
suffix:semicolon
)brace
DECL|variable|pcmcia_get_first_window
id|EXPORT_SYMBOL
c_func
(paren
id|pcmcia_get_first_window
)paren
suffix:semicolon
DECL|function|pcmcia_get_next_window
r_int
id|pcmcia_get_next_window
c_func
(paren
id|window_handle_t
op_star
id|win
comma
id|win_req_t
op_star
id|req
)paren
(brace
r_if
c_cond
(paren
(paren
id|win
op_eq
l_int|NULL
)paren
op_logical_or
(paren
(paren
op_star
id|win
)paren
op_member_access_from_pointer
id|magic
op_ne
id|WINDOW_MAGIC
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
r_return
id|pcmcia_get_window
c_func
(paren
(paren
op_star
id|win
)paren
op_member_access_from_pointer
id|sock
comma
id|win
comma
(paren
op_star
id|win
)paren
op_member_access_from_pointer
id|index
op_plus
l_int|1
comma
id|req
)paren
suffix:semicolon
)brace
DECL|variable|pcmcia_get_next_window
id|EXPORT_SYMBOL
c_func
(paren
id|pcmcia_get_next_window
)paren
suffix:semicolon
macro_line|#endif
eof
