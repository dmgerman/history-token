multiline_comment|/*&n; *&t;IrNET protocol module : Synchronous PPP over an IrDA socket.&n; *&n; *&t;&t;Jean II - HPL `00 - &lt;jt@hpl.hp.com&gt;&n; *&n; * This file contains all definitions and declarations necessary for the&n; * IRDA part of the IrNET module (dealing with IrTTP, IrIAS and co).&n; * This file is a private header, so other modules don&squot;t want to know&n; * what&squot;s in there...&n; */
macro_line|#ifndef IRNET_IRDA_H
DECL|macro|IRNET_IRDA_H
mdefine_line|#define IRNET_IRDA_H
multiline_comment|/***************************** INCLUDES *****************************/
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Please add other headers in irnet.h */
macro_line|#include &quot;irnet.h&quot;&t;&t;/* Module global include */
multiline_comment|/************************ CONSTANTS &amp; MACROS ************************/
multiline_comment|/*&n; * Name of the service (socket name) used by IrNET&n; */
multiline_comment|/* IAS object name (or part of it) */
DECL|macro|IRNET_SERVICE_NAME
mdefine_line|#define IRNET_SERVICE_NAME&t;&quot;IrNetv1&quot;
multiline_comment|/* IAS attribute */
DECL|macro|IRNET_IAS_VALUE
mdefine_line|#define IRNET_IAS_VALUE&t;&t;&quot;IrDA:TinyTP:LsapSel&quot;
multiline_comment|/* LMP notify name for client (only for /proc/net/irda/irlmp) */
DECL|macro|IRNET_NOTIFY_NAME
mdefine_line|#define IRNET_NOTIFY_NAME&t;&quot;IrNET socket&quot;
multiline_comment|/* LMP notify name for server (only for /proc/net/irda/irlmp) */
DECL|macro|IRNET_NOTIFY_NAME_SERV
mdefine_line|#define IRNET_NOTIFY_NAME_SERV&t;&quot;IrNET server&quot;
multiline_comment|/****************************** TYPES ******************************/
multiline_comment|/*&n; * This is the main structure where we store all the data pertaining to&n; * the IrNET server (listen for connection requests) and the root&n; * of the IrNET socket list&n; */
DECL|struct|irnet_root
r_typedef
r_struct
id|irnet_root
(brace
DECL|member|s
id|irnet_socket
id|s
suffix:semicolon
multiline_comment|/* To pretend we are a client... */
multiline_comment|/* Generic stuff */
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* Paranoia */
DECL|member|running
r_int
id|running
suffix:semicolon
multiline_comment|/* Are we operational ? */
multiline_comment|/* Link list of all IrNET instances opened */
DECL|member|list
id|hashbin_t
op_star
id|list
suffix:semicolon
DECL|member|spinlock
id|spinlock_t
id|spinlock
suffix:semicolon
multiline_comment|/* Serialize access to the list */
multiline_comment|/* Note : the way hashbin has been designed is absolutely not&n;   * reentrant, beware... So, we blindly protect all with spinlock */
multiline_comment|/* Handle for the hint bit advertised in IrLMP */
DECL|member|skey
id|__u32
id|skey
suffix:semicolon
multiline_comment|/* Server socket part */
DECL|member|ias_obj
r_struct
id|ias_object
op_star
id|ias_obj
suffix:semicolon
multiline_comment|/* Our service name + lsap in IAS */
DECL|typedef|irnet_root
)brace
id|irnet_root
suffix:semicolon
multiline_comment|/**************************** PROTOTYPES ****************************/
multiline_comment|/* ----------------------- CONTROL CHANNEL ----------------------- */
r_static
r_void
id|irnet_post_event
c_func
(paren
id|irnet_socket
op_star
comma
id|irnet_event
comma
id|__u32
comma
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* ----------------------- IRDA SUBROUTINES ----------------------- */
r_static
r_inline
r_int
id|irnet_open_tsap
c_func
(paren
id|irnet_socket
op_star
)paren
suffix:semicolon
r_static
r_int
id|irnet_find_lsap_sel
c_func
(paren
id|irnet_socket
op_star
)paren
suffix:semicolon
r_static
r_inline
r_int
id|irnet_discover_daddr_and_lsap_sel
c_func
(paren
id|irnet_socket
op_star
)paren
suffix:semicolon
r_static
r_inline
r_int
id|irnet_dname_to_daddr
c_func
(paren
id|irnet_socket
op_star
)paren
suffix:semicolon
multiline_comment|/* ------------------------ SERVER SOCKET ------------------------ */
r_static
r_inline
r_int
id|irnet_daddr_to_dname
c_func
(paren
id|irnet_socket
op_star
)paren
suffix:semicolon
r_static
r_inline
id|irnet_socket
op_star
id|irnet_find_socket
c_func
(paren
id|irnet_socket
op_star
)paren
suffix:semicolon
r_static
r_inline
r_int
id|irnet_connect_socket
c_func
(paren
id|irnet_socket
op_star
comma
id|irnet_socket
op_star
comma
r_struct
id|qos_info
op_star
comma
id|__u32
comma
id|__u8
)paren
suffix:semicolon
r_static
r_inline
r_void
id|irnet_disconnect_server
c_func
(paren
id|irnet_socket
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_static
r_inline
r_int
id|irnet_setup_server
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_inline
r_void
id|irnet_destroy_server
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* ---------------------- IRDA-TTP CALLBACKS ---------------------- */
r_static
r_int
id|irnet_data_indication
c_func
(paren
r_void
op_star
comma
multiline_comment|/* instance */
r_void
op_star
comma
multiline_comment|/* sap */
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_static
r_void
id|irnet_disconnect_indication
c_func
(paren
r_void
op_star
comma
r_void
op_star
comma
id|LM_REASON
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_static
r_void
id|irnet_connect_confirm
c_func
(paren
r_void
op_star
comma
r_void
op_star
comma
r_struct
id|qos_info
op_star
comma
id|__u32
comma
id|__u8
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_static
r_void
id|irnet_flow_indication
c_func
(paren
r_void
op_star
comma
r_void
op_star
comma
id|LOCAL_FLOW
)paren
suffix:semicolon
r_static
r_void
id|irnet_status_indication
c_func
(paren
r_void
op_star
comma
id|LINK_STATUS
comma
id|LOCK_STATUS
)paren
suffix:semicolon
r_static
r_void
id|irnet_connect_indication
c_func
(paren
r_void
op_star
comma
r_void
op_star
comma
r_struct
id|qos_info
op_star
comma
id|__u32
comma
id|__u8
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/* -------------------- IRDA-IAS/LMP CALLBACKS -------------------- */
r_static
r_void
id|irnet_getvalue_confirm
c_func
(paren
r_int
comma
id|__u16
comma
r_struct
id|ias_value
op_star
comma
r_void
op_star
)paren
suffix:semicolon
macro_line|#ifdef DISCOVERY_EVENTS
r_static
r_void
id|irnet_discovery_indication
c_func
(paren
id|discovery_t
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_static
r_void
id|irnet_expiry_indication
c_func
(paren
id|discovery_t
op_star
comma
r_void
op_star
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* -------------------------- PROC ENTRY -------------------------- */
macro_line|#ifdef CONFIG_PROC_FS
r_static
r_int
id|irnet_proc_read
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PROC_FS */
multiline_comment|/**************************** VARIABLES ****************************/
multiline_comment|/*&n; * The IrNET server. Listen to connection requests and co...&n; */
DECL|variable|irnet_server
r_static
r_struct
id|irnet_root
id|irnet_server
suffix:semicolon
multiline_comment|/* Control channel stuff (note : extern) */
DECL|variable|irnet_events
r_struct
id|irnet_ctrl_channel
id|irnet_events
suffix:semicolon
multiline_comment|/* The /proc/net/irda directory, defined elsewhere... */
macro_line|#ifdef CONFIG_PROC_FS
r_extern
r_struct
id|proc_dir_entry
op_star
id|proc_irda
suffix:semicolon
macro_line|#endif /* CONFIG_PROC_FS */
macro_line|#endif /* IRNET_IRDA_H */
eof
