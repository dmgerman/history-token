multiline_comment|/* atmsvc.h - ATM signaling kernel-demon interface definitions */
multiline_comment|/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef _LINUX_ATMSVC_H
DECL|macro|_LINUX_ATMSVC_H
mdefine_line|#define _LINUX_ATMSVC_H
macro_line|#include &lt;linux/atmapi.h&gt;
macro_line|#include &lt;linux/atm.h&gt;
macro_line|#include &lt;linux/atmioc.h&gt;
DECL|macro|ATMSIGD_CTRL
mdefine_line|#define ATMSIGD_CTRL _IO(&squot;a&squot;,ATMIOC_SPECIAL)
multiline_comment|/* become ATM signaling demon control socket */
DECL|enum|atmsvc_msg_type
DECL|enumerator|as_catch_null
DECL|enumerator|as_bind
DECL|enumerator|as_connect
DECL|enumerator|as_accept
DECL|enumerator|as_reject
r_enum
id|atmsvc_msg_type
(brace
id|as_catch_null
comma
id|as_bind
comma
id|as_connect
comma
id|as_accept
comma
id|as_reject
comma
DECL|enumerator|as_listen
DECL|enumerator|as_okay
DECL|enumerator|as_error
DECL|enumerator|as_indicate
DECL|enumerator|as_close
DECL|enumerator|as_itf_notify
id|as_listen
comma
id|as_okay
comma
id|as_error
comma
id|as_indicate
comma
id|as_close
comma
id|as_itf_notify
comma
DECL|enumerator|as_modify
DECL|enumerator|as_identify
DECL|enumerator|as_terminate
id|as_modify
comma
id|as_identify
comma
id|as_terminate
)brace
suffix:semicolon
DECL|struct|atmsvc_msg
r_struct
id|atmsvc_msg
(brace
DECL|member|type
r_enum
id|atmsvc_msg_type
id|type
suffix:semicolon
DECL|member|vcc
id|atm_kptr_t
id|vcc
suffix:semicolon
DECL|member|listen_vcc
id|atm_kptr_t
id|listen_vcc
suffix:semicolon
multiline_comment|/* indicate */
DECL|member|reply
r_int
id|reply
suffix:semicolon
multiline_comment|/* for okay and close:&t;&t;   */
multiline_comment|/*   &lt; 0: error before active&t;   */
multiline_comment|/*        (sigd has discarded ctx) */
multiline_comment|/*   ==0: success&t;&t;   */
multiline_comment|/*   &gt; 0: error when active (still */
multiline_comment|/*        need to close)&t;   */
DECL|member|pvc
r_struct
id|sockaddr_atmpvc
id|pvc
suffix:semicolon
multiline_comment|/* indicate, okay (connect) */
DECL|member|local
r_struct
id|sockaddr_atmsvc
id|local
suffix:semicolon
multiline_comment|/* local SVC address */
DECL|member|qos
r_struct
id|atm_qos
id|qos
suffix:semicolon
multiline_comment|/* QOS parameters */
DECL|member|sap
r_struct
id|atm_sap
id|sap
suffix:semicolon
multiline_comment|/* SAP */
DECL|member|session
r_int
r_int
id|session
suffix:semicolon
multiline_comment|/* for p2pm */
DECL|member|svc
r_struct
id|sockaddr_atmsvc
id|svc
suffix:semicolon
multiline_comment|/* SVC address */
DECL|variable|__ATM_API_ALIGN
)brace
id|__ATM_API_ALIGN
suffix:semicolon
multiline_comment|/*&n; * Message contents: see ftp://icaftp.epfl.ch/pub/linux/atm/docs/isp-*.tar.gz&n; */
multiline_comment|/*&n; * Some policy stuff for atmsigd and for net/atm/svc.c. Both have to agree on&n; * what PCR is used to request bandwidth from the device driver. net/atm/svc.c&n; * tries to do better than that, but only if there&squot;s no routing decision (i.e.&n; * if signaling only uses one ATM interface).&n; */
DECL|macro|SELECT_TOP_PCR
mdefine_line|#define SELECT_TOP_PCR(tp) ((tp).pcr ? (tp).pcr : &bslash;&n;  (tp).max_pcr &amp;&amp; (tp).max_pcr != ATM_MAX_PCR ? (tp).max_pcr : &bslash;&n;  (tp).min_pcr ? (tp).min_pcr : ATM_MAX_PCR)
macro_line|#endif
eof
