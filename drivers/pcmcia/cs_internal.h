multiline_comment|/*&n; * cs_internal.h 1.57 2002/10/24 06:11:43&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n; *  are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; */
macro_line|#ifndef _LINUX_CS_INTERNAL_H
DECL|macro|_LINUX_CS_INTERNAL_H
mdefine_line|#define _LINUX_CS_INTERNAL_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|CLIENT_MAGIC
mdefine_line|#define CLIENT_MAGIC &t;0x51E6
DECL|struct|client_t
r_typedef
r_struct
id|client_t
(brace
DECL|member|client_magic
id|u_short
id|client_magic
suffix:semicolon
DECL|member|Socket
r_struct
id|pcmcia_socket
op_star
id|Socket
suffix:semicolon
DECL|member|Function
id|u_char
id|Function
suffix:semicolon
DECL|member|dev_info
id|dev_info_t
id|dev_info
suffix:semicolon
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|state
id|u_int
id|state
suffix:semicolon
DECL|member|EventMask
DECL|member|PendingEvents
id|event_t
id|EventMask
comma
id|PendingEvents
suffix:semicolon
DECL|member|event_handler
r_int
(paren
op_star
id|event_handler
)paren
(paren
id|event_t
id|event
comma
r_int
id|priority
comma
id|event_callback_args_t
op_star
)paren
suffix:semicolon
DECL|member|event_callback_args
id|event_callback_args_t
id|event_callback_args
suffix:semicolon
DECL|member|next
r_struct
id|client_t
op_star
id|next
suffix:semicolon
DECL|typedef|client_t
)brace
id|client_t
suffix:semicolon
multiline_comment|/* Flags in client state */
DECL|macro|CLIENT_CONFIG_LOCKED
mdefine_line|#define CLIENT_CONFIG_LOCKED&t;0x0001
DECL|macro|CLIENT_IRQ_REQ
mdefine_line|#define CLIENT_IRQ_REQ&t;&t;0x0002
DECL|macro|CLIENT_IO_REQ
mdefine_line|#define CLIENT_IO_REQ&t;&t;0x0004
DECL|macro|CLIENT_UNBOUND
mdefine_line|#define CLIENT_UNBOUND&t;&t;0x0008
DECL|macro|CLIENT_STALE
mdefine_line|#define CLIENT_STALE&t;&t;0x0010
DECL|macro|CLIENT_WIN_REQ
mdefine_line|#define CLIENT_WIN_REQ(i)&t;(0x20&lt;&lt;(i))
DECL|macro|CLIENT_CARDBUS
mdefine_line|#define CLIENT_CARDBUS&t;&t;0x8000
DECL|macro|REGION_MAGIC
mdefine_line|#define REGION_MAGIC&t;0xE3C9
DECL|struct|region_t
r_typedef
r_struct
id|region_t
(brace
DECL|member|region_magic
id|u_short
id|region_magic
suffix:semicolon
DECL|member|state
id|u_short
id|state
suffix:semicolon
DECL|member|dev_info
id|dev_info_t
id|dev_info
suffix:semicolon
DECL|member|mtd
id|client_handle_t
id|mtd
suffix:semicolon
DECL|member|MediaID
id|u_int
id|MediaID
suffix:semicolon
DECL|member|info
id|region_info_t
id|info
suffix:semicolon
DECL|typedef|region_t
)brace
id|region_t
suffix:semicolon
DECL|macro|REGION_STALE
mdefine_line|#define REGION_STALE&t;0x01
multiline_comment|/* Each card function gets one of these guys */
DECL|struct|config_t
r_typedef
r_struct
id|config_t
(brace
DECL|member|state
id|u_int
id|state
suffix:semicolon
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|Vcc
DECL|member|Vpp1
DECL|member|Vpp2
id|u_int
id|Vcc
comma
id|Vpp1
comma
id|Vpp2
suffix:semicolon
DECL|member|IntType
id|u_int
id|IntType
suffix:semicolon
DECL|member|ConfigBase
id|u_int
id|ConfigBase
suffix:semicolon
DECL|member|Status
DECL|member|Pin
DECL|member|Copy
DECL|member|Option
DECL|member|ExtStatus
id|u_char
id|Status
comma
id|Pin
comma
id|Copy
comma
id|Option
comma
id|ExtStatus
suffix:semicolon
DECL|member|Present
id|u_int
id|Present
suffix:semicolon
DECL|member|CardValues
id|u_int
id|CardValues
suffix:semicolon
DECL|member|io
id|io_req_t
id|io
suffix:semicolon
r_struct
(brace
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|irq
)brace
id|irq
suffix:semicolon
DECL|typedef|config_t
)brace
id|config_t
suffix:semicolon
DECL|struct|cis_cache_entry
r_struct
id|cis_cache_entry
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|attr
r_int
r_int
id|attr
suffix:semicolon
DECL|member|cache
r_int
r_char
id|cache
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Flags in config state */
DECL|macro|CONFIG_LOCKED
mdefine_line|#define CONFIG_LOCKED&t;&t;0x01
DECL|macro|CONFIG_IRQ_REQ
mdefine_line|#define CONFIG_IRQ_REQ&t;&t;0x02
DECL|macro|CONFIG_IO_REQ
mdefine_line|#define CONFIG_IO_REQ&t;&t;0x04
multiline_comment|/* Flags in socket state */
DECL|macro|SOCKET_PRESENT
mdefine_line|#define SOCKET_PRESENT&t;&t;0x0008
DECL|macro|SOCKET_INUSE
mdefine_line|#define SOCKET_INUSE&t;&t;0x0010
DECL|macro|SOCKET_SUSPEND
mdefine_line|#define SOCKET_SUSPEND&t;&t;0x0080
DECL|macro|SOCKET_WIN_REQ
mdefine_line|#define SOCKET_WIN_REQ(i)&t;(0x0100&lt;&lt;(i))
DECL|macro|SOCKET_REGION_INFO
mdefine_line|#define SOCKET_REGION_INFO&t;0x4000
DECL|macro|SOCKET_CARDBUS
mdefine_line|#define SOCKET_CARDBUS&t;&t;0x8000
DECL|macro|SOCKET_CARDBUS_CONFIG
mdefine_line|#define SOCKET_CARDBUS_CONFIG&t;0x10000
DECL|function|cs_socket_get
r_static
r_inline
r_int
id|cs_socket_get
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|skt
)paren
(brace
r_int
id|ret
suffix:semicolon
id|WARN_ON
c_func
(paren
id|skt-&gt;state
op_amp
id|SOCKET_INUSE
)paren
suffix:semicolon
id|ret
op_assign
id|try_module_get
c_func
(paren
id|skt-&gt;owner
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|skt-&gt;state
op_or_assign
id|SOCKET_INUSE
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|cs_socket_put
r_static
r_inline
r_void
id|cs_socket_put
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|skt
)paren
(brace
r_if
c_cond
(paren
id|skt-&gt;state
op_amp
id|SOCKET_INUSE
)paren
(brace
id|skt-&gt;state
op_and_assign
op_complement
id|SOCKET_INUSE
suffix:semicolon
id|module_put
c_func
(paren
id|skt-&gt;owner
)paren
suffix:semicolon
)brace
)brace
DECL|macro|CHECK_HANDLE
mdefine_line|#define CHECK_HANDLE(h) &bslash;&n;    (((h) == NULL) || ((h)-&gt;client_magic != CLIENT_MAGIC))
DECL|macro|CHECK_SOCKET
mdefine_line|#define CHECK_SOCKET(s) &bslash;&n;    (((s) &gt;= sockets) || (socket_table[s]-&gt;ops == NULL))
DECL|macro|SOCKET
mdefine_line|#define SOCKET(h) (h-&gt;Socket)
DECL|macro|CONFIG
mdefine_line|#define CONFIG(h) (&amp;SOCKET(h)-&gt;config[(h)-&gt;Function])
DECL|macro|CHECK_REGION
mdefine_line|#define CHECK_REGION(r) &bslash;&n;    (((r) == NULL) || ((r)-&gt;region_magic != REGION_MAGIC))
DECL|macro|CHECK_ERASEQ
mdefine_line|#define CHECK_ERASEQ(q) &bslash;&n;    (((q) == NULL) || ((q)-&gt;eraseq_magic != ERASEQ_MAGIC))
DECL|macro|EVENT
mdefine_line|#define EVENT(h, e, p) &bslash;&n;    ((h)-&gt;event_handler((e), (p), &amp;(h)-&gt;event_callback_args))
multiline_comment|/* In cardbus.c */
r_int
id|cb_alloc
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|s
)paren
suffix:semicolon
r_void
id|cb_free
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|s
)paren
suffix:semicolon
r_int
id|read_cb_mem
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|s
comma
r_int
id|space
comma
id|u_int
id|addr
comma
id|u_int
id|len
comma
r_void
op_star
id|ptr
)paren
suffix:semicolon
multiline_comment|/* In cistpl.c */
r_int
id|read_cis_mem
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|s
comma
r_int
id|attr
comma
id|u_int
id|addr
comma
id|u_int
id|len
comma
r_void
op_star
id|ptr
)paren
suffix:semicolon
r_void
id|write_cis_mem
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|s
comma
r_int
id|attr
comma
id|u_int
id|addr
comma
id|u_int
id|len
comma
r_void
op_star
id|ptr
)paren
suffix:semicolon
r_void
id|release_cis_mem
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|s
)paren
suffix:semicolon
r_void
id|destroy_cis_cache
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|s
)paren
suffix:semicolon
r_int
id|verify_cis_cache
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|s
)paren
suffix:semicolon
r_int
id|pccard_read_tuple
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|s
comma
r_int
r_int
id|function
comma
id|cisdata_t
id|code
comma
r_void
op_star
id|parse
)paren
suffix:semicolon
multiline_comment|/* In rsrc_mgr */
r_void
id|pcmcia_validate_mem
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|s
)paren
suffix:semicolon
r_struct
id|resource
op_star
id|find_io_region
c_func
(paren
r_int
r_int
id|base
comma
r_int
id|num
comma
r_int
r_int
id|align
comma
r_char
op_star
id|name
comma
r_struct
id|pcmcia_socket
op_star
id|s
)paren
suffix:semicolon
r_int
id|adjust_io_region
c_func
(paren
r_struct
id|resource
op_star
id|res
comma
r_int
r_int
id|r_start
comma
r_int
r_int
id|r_end
comma
r_struct
id|pcmcia_socket
op_star
id|s
)paren
suffix:semicolon
r_struct
id|resource
op_star
id|find_mem_region
c_func
(paren
id|u_long
id|base
comma
id|u_long
id|num
comma
id|u_long
id|align
comma
r_int
id|low
comma
r_char
op_star
id|name
comma
r_struct
id|pcmcia_socket
op_star
id|s
)paren
suffix:semicolon
r_int
id|try_irq
c_func
(paren
id|u_int
id|Attributes
comma
r_int
id|irq
comma
r_int
id|specific
)paren
suffix:semicolon
r_void
id|undo_irq
c_func
(paren
id|u_int
id|Attributes
comma
r_int
id|irq
)paren
suffix:semicolon
r_int
id|adjust_resource_info
c_func
(paren
id|client_handle_t
id|handle
comma
id|adjust_t
op_star
id|adj
)paren
suffix:semicolon
r_void
id|release_resource_db
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* In socket_sysfs.c */
r_extern
r_struct
id|class_interface
id|pccard_sysfs_interface
suffix:semicolon
multiline_comment|/* In cs.c */
r_extern
r_struct
id|rw_semaphore
id|pcmcia_socket_list_rwsem
suffix:semicolon
r_extern
r_struct
id|list_head
id|pcmcia_socket_list
suffix:semicolon
r_int
id|pcmcia_get_window
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|s
comma
id|window_handle_t
op_star
id|handle
comma
r_int
id|idx
comma
id|win_req_t
op_star
id|req
)paren
suffix:semicolon
r_int
id|pccard_get_configuration_info
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|s
comma
r_int
r_int
id|function
comma
id|config_info_t
op_star
id|config
)paren
suffix:semicolon
r_int
id|pccard_reset_card
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|skt
)paren
suffix:semicolon
r_int
id|pccard_get_status
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|s
comma
r_int
r_int
id|function
comma
id|cs_status_t
op_star
id|status
)paren
suffix:semicolon
r_int
id|pccard_access_configuration_register
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|s
comma
r_int
r_int
id|function
comma
id|conf_reg_t
op_star
id|reg
)paren
suffix:semicolon
DECL|struct|pcmcia_callback
r_struct
id|pcmcia_callback
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|event
r_int
(paren
op_star
id|event
)paren
(paren
r_struct
id|pcmcia_socket
op_star
id|s
comma
id|event_t
id|event
comma
r_int
id|priority
)paren
suffix:semicolon
)brace
suffix:semicolon
r_int
id|pccard_register_pcmcia
c_func
(paren
r_struct
id|pcmcia_socket
op_star
id|s
comma
r_struct
id|pcmcia_callback
op_star
id|c
)paren
suffix:semicolon
DECL|macro|cs_socket_name
mdefine_line|#define cs_socket_name(skt)&t;((skt)-&gt;dev.class_id)
macro_line|#ifdef DEBUG
r_extern
r_int
id|cs_debug_level
c_func
(paren
r_int
)paren
suffix:semicolon
DECL|macro|cs_dbg
mdefine_line|#define cs_dbg(skt, lvl, fmt, arg...) do {&t;&t;&bslash;&n;&t;if (cs_debug_level(lvl))&t;&t;&t;&bslash;&n;&t;&t;printk(KERN_DEBUG &quot;cs: %s: &quot; fmt, &t;&bslash;&n;&t;&t;       cs_socket_name(skt) , ## arg);&t;&bslash;&n;} while (0)
macro_line|#else
DECL|macro|cs_dbg
mdefine_line|#define cs_dbg(skt, lvl, fmt, arg...) do { } while (0)
macro_line|#endif
DECL|macro|cs_err
mdefine_line|#define cs_err(skt, fmt, arg...) &bslash;&n;&t;printk(KERN_ERR &quot;cs: %s: &quot; fmt, (skt)-&gt;dev.class_id , ## arg)
macro_line|#endif /* _LINUX_CS_INTERNAL_H */
eof
