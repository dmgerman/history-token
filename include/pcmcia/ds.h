multiline_comment|/*&n; * ds.h 1.56 2000/06/12 21:55:40&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; */
macro_line|#ifndef _LINUX_DS_H
DECL|macro|_LINUX_DS_H
mdefine_line|#define _LINUX_DS_H
macro_line|#include &lt;pcmcia/driver_ops.h&gt;
macro_line|#include &lt;pcmcia/bulkmem.h&gt;
DECL|struct|tuple_parse_t
r_typedef
r_struct
id|tuple_parse_t
(brace
DECL|member|tuple
id|tuple_t
id|tuple
suffix:semicolon
DECL|member|data
id|cisdata_t
id|data
(braket
l_int|255
)braket
suffix:semicolon
DECL|member|parse
id|cisparse_t
id|parse
suffix:semicolon
DECL|typedef|tuple_parse_t
)brace
id|tuple_parse_t
suffix:semicolon
DECL|struct|win_info_t
r_typedef
r_struct
id|win_info_t
(brace
DECL|member|handle
id|window_handle_t
id|handle
suffix:semicolon
DECL|member|window
id|win_req_t
id|window
suffix:semicolon
DECL|member|map
id|memreq_t
id|map
suffix:semicolon
DECL|typedef|win_info_t
)brace
id|win_info_t
suffix:semicolon
DECL|struct|bind_info_t
r_typedef
r_struct
id|bind_info_t
(brace
DECL|member|dev_info
id|dev_info_t
id|dev_info
suffix:semicolon
DECL|member|function
id|u_char
id|function
suffix:semicolon
DECL|member|instance
r_struct
id|dev_link_t
op_star
id|instance
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|DEV_NAME_LEN
)braket
suffix:semicolon
DECL|member|major
DECL|member|minor
id|u_short
id|major
comma
id|minor
suffix:semicolon
DECL|member|next
r_void
op_star
id|next
suffix:semicolon
DECL|typedef|bind_info_t
)brace
id|bind_info_t
suffix:semicolon
DECL|struct|mtd_info_t
r_typedef
r_struct
id|mtd_info_t
(brace
DECL|member|dev_info
id|dev_info_t
id|dev_info
suffix:semicolon
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|CardOffset
id|u_int
id|CardOffset
suffix:semicolon
DECL|typedef|mtd_info_t
)brace
id|mtd_info_t
suffix:semicolon
DECL|union|ds_ioctl_arg_t
r_typedef
r_union
id|ds_ioctl_arg_t
(brace
DECL|member|servinfo
id|servinfo_t
id|servinfo
suffix:semicolon
DECL|member|adjust
id|adjust_t
id|adjust
suffix:semicolon
DECL|member|config
id|config_info_t
id|config
suffix:semicolon
DECL|member|tuple
id|tuple_t
id|tuple
suffix:semicolon
DECL|member|tuple_parse
id|tuple_parse_t
id|tuple_parse
suffix:semicolon
DECL|member|client_req
id|client_req_t
id|client_req
suffix:semicolon
DECL|member|status
id|cs_status_t
id|status
suffix:semicolon
DECL|member|conf_reg
id|conf_reg_t
id|conf_reg
suffix:semicolon
DECL|member|cisinfo
id|cisinfo_t
id|cisinfo
suffix:semicolon
DECL|member|region
id|region_info_t
id|region
suffix:semicolon
DECL|member|bind_info
id|bind_info_t
id|bind_info
suffix:semicolon
DECL|member|mtd_info
id|mtd_info_t
id|mtd_info
suffix:semicolon
DECL|member|win_info
id|win_info_t
id|win_info
suffix:semicolon
DECL|member|cisdump
id|cisdump_t
id|cisdump
suffix:semicolon
DECL|typedef|ds_ioctl_arg_t
)brace
id|ds_ioctl_arg_t
suffix:semicolon
DECL|macro|DS_GET_CARD_SERVICES_INFO
mdefine_line|#define DS_GET_CARD_SERVICES_INFO&t;_IOR (&squot;d&squot;, 1, servinfo_t)
DECL|macro|DS_ADJUST_RESOURCE_INFO
mdefine_line|#define DS_ADJUST_RESOURCE_INFO&t;&t;_IOWR(&squot;d&squot;, 2, adjust_t)
DECL|macro|DS_GET_CONFIGURATION_INFO
mdefine_line|#define DS_GET_CONFIGURATION_INFO&t;_IOWR(&squot;d&squot;, 3, config_info_t)
DECL|macro|DS_GET_FIRST_TUPLE
mdefine_line|#define DS_GET_FIRST_TUPLE&t;&t;_IOWR(&squot;d&squot;, 4, tuple_t)
DECL|macro|DS_GET_NEXT_TUPLE
mdefine_line|#define DS_GET_NEXT_TUPLE&t;&t;_IOWR(&squot;d&squot;, 5, tuple_t)
DECL|macro|DS_GET_TUPLE_DATA
mdefine_line|#define DS_GET_TUPLE_DATA&t;&t;_IOWR(&squot;d&squot;, 6, tuple_parse_t)
DECL|macro|DS_PARSE_TUPLE
mdefine_line|#define DS_PARSE_TUPLE&t;&t;&t;_IOWR(&squot;d&squot;, 7, tuple_parse_t)
DECL|macro|DS_RESET_CARD
mdefine_line|#define DS_RESET_CARD&t;&t;&t;_IO  (&squot;d&squot;, 8)
DECL|macro|DS_GET_STATUS
mdefine_line|#define DS_GET_STATUS&t;&t;&t;_IOWR(&squot;d&squot;, 9, cs_status_t)
DECL|macro|DS_ACCESS_CONFIGURATION_REGISTER
mdefine_line|#define DS_ACCESS_CONFIGURATION_REGISTER _IOWR(&squot;d&squot;, 10, conf_reg_t)
DECL|macro|DS_VALIDATE_CIS
mdefine_line|#define DS_VALIDATE_CIS&t;&t;&t;_IOR (&squot;d&squot;, 11, cisinfo_t)
DECL|macro|DS_SUSPEND_CARD
mdefine_line|#define DS_SUSPEND_CARD&t;&t;&t;_IO  (&squot;d&squot;, 12)
DECL|macro|DS_RESUME_CARD
mdefine_line|#define DS_RESUME_CARD&t;&t;&t;_IO  (&squot;d&squot;, 13)
DECL|macro|DS_EJECT_CARD
mdefine_line|#define DS_EJECT_CARD&t;&t;&t;_IO  (&squot;d&squot;, 14)
DECL|macro|DS_INSERT_CARD
mdefine_line|#define DS_INSERT_CARD&t;&t;&t;_IO  (&squot;d&squot;, 15)
DECL|macro|DS_GET_FIRST_REGION
mdefine_line|#define DS_GET_FIRST_REGION&t;&t;_IOWR(&squot;d&squot;, 16, region_info_t)
DECL|macro|DS_GET_NEXT_REGION
mdefine_line|#define DS_GET_NEXT_REGION&t;&t;_IOWR(&squot;d&squot;, 17, region_info_t)
DECL|macro|DS_REPLACE_CIS
mdefine_line|#define DS_REPLACE_CIS&t;&t;&t;_IOWR(&squot;d&squot;, 18, cisdump_t)
DECL|macro|DS_GET_FIRST_WINDOW
mdefine_line|#define DS_GET_FIRST_WINDOW&t;&t;_IOR (&squot;d&squot;, 19, win_info_t)
DECL|macro|DS_GET_NEXT_WINDOW
mdefine_line|#define DS_GET_NEXT_WINDOW&t;&t;_IOWR(&squot;d&squot;, 20, win_info_t)
DECL|macro|DS_GET_MEM_PAGE
mdefine_line|#define DS_GET_MEM_PAGE&t;&t;&t;_IOWR(&squot;d&squot;, 21, win_info_t)
DECL|macro|DS_BIND_REQUEST
mdefine_line|#define DS_BIND_REQUEST&t;&t;&t;_IOWR(&squot;d&squot;, 60, bind_info_t)
DECL|macro|DS_GET_DEVICE_INFO
mdefine_line|#define DS_GET_DEVICE_INFO&t;&t;_IOWR(&squot;d&squot;, 61, bind_info_t) 
DECL|macro|DS_GET_NEXT_DEVICE
mdefine_line|#define DS_GET_NEXT_DEVICE&t;&t;_IOWR(&squot;d&squot;, 62, bind_info_t) 
DECL|macro|DS_UNBIND_REQUEST
mdefine_line|#define DS_UNBIND_REQUEST&t;&t;_IOW (&squot;d&squot;, 63, bind_info_t)
DECL|macro|DS_BIND_MTD
mdefine_line|#define DS_BIND_MTD&t;&t;&t;_IOWR(&squot;d&squot;, 64, mtd_info_t)
macro_line|#ifdef __KERNEL__
DECL|struct|dev_link_t
r_typedef
r_struct
id|dev_link_t
(brace
DECL|member|dev
id|dev_node_t
op_star
id|dev
suffix:semicolon
DECL|member|state
DECL|member|open
id|u_int
id|state
comma
id|open
suffix:semicolon
DECL|member|pending
id|wait_queue_head_t
id|pending
suffix:semicolon
DECL|member|release
r_struct
id|timer_list
id|release
suffix:semicolon
DECL|member|handle
id|client_handle_t
id|handle
suffix:semicolon
DECL|member|io
id|io_req_t
id|io
suffix:semicolon
DECL|member|irq
id|irq_req_t
id|irq
suffix:semicolon
DECL|member|conf
id|config_req_t
id|conf
suffix:semicolon
DECL|member|win
id|window_handle_t
id|win
suffix:semicolon
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
DECL|member|next
r_struct
id|dev_link_t
op_star
id|next
suffix:semicolon
DECL|typedef|dev_link_t
)brace
id|dev_link_t
suffix:semicolon
multiline_comment|/* Flags for device state */
DECL|macro|DEV_PRESENT
mdefine_line|#define DEV_PRESENT&t;&t;0x01
DECL|macro|DEV_CONFIG
mdefine_line|#define DEV_CONFIG&t;&t;0x02
DECL|macro|DEV_STALE_CONFIG
mdefine_line|#define DEV_STALE_CONFIG&t;0x04&t;/* release on close */
DECL|macro|DEV_STALE_LINK
mdefine_line|#define DEV_STALE_LINK&t;&t;0x08&t;/* detach on release */
DECL|macro|DEV_CONFIG_PENDING
mdefine_line|#define DEV_CONFIG_PENDING&t;0x10
DECL|macro|DEV_RELEASE_PENDING
mdefine_line|#define DEV_RELEASE_PENDING&t;0x20
DECL|macro|DEV_SUSPEND
mdefine_line|#define DEV_SUSPEND&t;&t;0x40
DECL|macro|DEV_BUSY
mdefine_line|#define DEV_BUSY&t;&t;0x80
DECL|macro|DEV_OK
mdefine_line|#define DEV_OK(l) &bslash;&n;    ((l) &amp;&amp; ((l-&gt;state &amp; ~DEV_BUSY) == (DEV_CONFIG|DEV_PRESENT)))
r_int
id|register_pccard_driver
c_func
(paren
id|dev_info_t
op_star
id|dev_info
comma
id|dev_link_t
op_star
(paren
op_star
id|attach
)paren
(paren
r_void
)paren
comma
r_void
(paren
op_star
id|detach
)paren
(paren
id|dev_link_t
op_star
)paren
)paren
suffix:semicolon
r_int
id|unregister_pccard_driver
c_func
(paren
id|dev_info_t
op_star
id|dev_info
)paren
suffix:semicolon
DECL|macro|register_pcmcia_driver
mdefine_line|#define register_pcmcia_driver register_pccard_driver
DECL|macro|unregister_pcmcia_driver
mdefine_line|#define unregister_pcmcia_driver unregister_pccard_driver
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_DS_H */
eof
