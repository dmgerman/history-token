multiline_comment|/* atm_tcp.h - Driver-specific declarations of the ATMTCP driver (for use by&n;&t;       driver-specific utilities) */
multiline_comment|/* Written 1997-2000 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef LINUX_ATM_TCP_H
DECL|macro|LINUX_ATM_TCP_H
mdefine_line|#define LINUX_ATM_TCP_H
macro_line|#include &lt;linux/atmapi.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/atmioc.h&gt;
multiline_comment|/*&n; * All values in struct atmtcp_hdr are in network byte order&n; */
DECL|struct|atmtcp_hdr
r_struct
id|atmtcp_hdr
(brace
DECL|member|vpi
r_uint16
id|vpi
suffix:semicolon
DECL|member|vci
r_uint16
id|vci
suffix:semicolon
DECL|member|length
r_uint32
id|length
suffix:semicolon
multiline_comment|/* ... of data part */
)brace
suffix:semicolon
multiline_comment|/*&n; * All values in struct atmtcp_command are in host byte order&n; */
DECL|macro|ATMTCP_HDR_MAGIC
mdefine_line|#define ATMTCP_HDR_MAGIC&t;(~0)&t;/* this length indicates a command */
DECL|macro|ATMTCP_CTRL_OPEN
mdefine_line|#define ATMTCP_CTRL_OPEN&t;1&t;/* request/reply */
DECL|macro|ATMTCP_CTRL_CLOSE
mdefine_line|#define ATMTCP_CTRL_CLOSE&t;2&t;/* request/reply */
DECL|struct|atmtcp_control
r_struct
id|atmtcp_control
(brace
DECL|member|hdr
r_struct
id|atmtcp_hdr
id|hdr
suffix:semicolon
multiline_comment|/* must be first */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* message type; both directions */
DECL|member|vcc
id|atm_kptr_t
id|vcc
suffix:semicolon
multiline_comment|/* both directions */
DECL|member|addr
r_struct
id|sockaddr_atmpvc
id|addr
suffix:semicolon
multiline_comment|/* suggested value from kernel */
DECL|member|qos
r_struct
id|atm_qos
id|qos
suffix:semicolon
multiline_comment|/* both directions */
DECL|member|result
r_int
id|result
suffix:semicolon
multiline_comment|/* to kernel only */
DECL|variable|__ATM_API_ALIGN
)brace
id|__ATM_API_ALIGN
suffix:semicolon
multiline_comment|/*&n; * Field usage:&n; * Messge type&t;dir.&t;hdr.v?i&t;type&t;addr&t;qos&t;vcc&t;result&n; * -----------  ----&t;------- ----&t;----&t;---&t;---&t;------&n; * OPEN&t;&t;K-&gt;D&t;Y&t;Y&t;Y&t;Y&t;Y&t;0&n; * OPEN&t;&t;D-&gt;K&t;-&t;Y&t;Y&t;Y&t;Y&t;Y&n; * CLOSE&t;K-&gt;D&t;-&t;-&t;Y&t;-&t;Y&t;0&n; * CLOSE&t;D-&gt;K&t;-&t;-&t;-&t;-&t;Y&t;Y&n; */
DECL|macro|SIOCSIFATMTCP
mdefine_line|#define SIOCSIFATMTCP&t;_IO(&squot;a&squot;,ATMIOC_ITF)&t;/* set ATMTCP mode */
DECL|macro|ATMTCP_CREATE
mdefine_line|#define ATMTCP_CREATE&t;_IO(&squot;a&squot;,ATMIOC_ITF+14)&t;/* create persistent ATMTCP&n;&t;&t;&t;&t;&t;&t;   interface */
DECL|macro|ATMTCP_REMOVE
mdefine_line|#define ATMTCP_REMOVE&t;_IO(&squot;a&squot;,ATMIOC_ITF+15)&t;/* destroy persistent ATMTCP&n;&t;&t;&t;&t;&t;&t;   interface */
macro_line|#ifdef __KERNEL__
DECL|struct|atm_tcp_ops
r_struct
id|atm_tcp_ops
(brace
DECL|member|attach
r_int
(paren
op_star
id|attach
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|itf
)paren
suffix:semicolon
DECL|member|create_persistent
r_int
(paren
op_star
id|create_persistent
)paren
(paren
r_int
id|itf
)paren
suffix:semicolon
DECL|member|remove_persistent
r_int
(paren
op_star
id|remove_persistent
)paren
(paren
r_int
id|itf
)paren
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|atm_tcp_ops
id|atm_tcp_ops
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
