multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
macro_line|#ifndef&t;_MBUF_
DECL|macro|_MBUF_
mdefine_line|#define _MBUF_
macro_line|#ifndef PCI
DECL|macro|M_SIZE
mdefine_line|#define M_SIZE&t;4550
macro_line|#else
DECL|macro|M_SIZE
mdefine_line|#define M_SIZE&t;4504
macro_line|#endif
macro_line|#ifndef MAX_MBUF
DECL|macro|MAX_MBUF
mdefine_line|#define MAX_MBUF&t;4
macro_line|#endif
macro_line|#ifndef NO_STD_MBUF
DECL|macro|sm_next
mdefine_line|#define sm_next         m_next
DECL|macro|sm_off
mdefine_line|#define sm_off          m_off
DECL|macro|sm_len
mdefine_line|#define sm_len          m_len
DECL|macro|sm_data
mdefine_line|#define sm_data         m_data
DECL|macro|SMbuf
mdefine_line|#define SMbuf           Mbuf
DECL|macro|mtod
mdefine_line|#define mtod&t;&t;smtod
DECL|macro|mtodoff
mdefine_line|#define mtodoff&t;&t;smtodoff
macro_line|#endif
DECL|struct|s_mbuf
r_struct
id|s_mbuf
(brace
DECL|member|sm_next
r_struct
id|s_mbuf
op_star
id|sm_next
suffix:semicolon
multiline_comment|/* low level linked list */
DECL|member|sm_off
r_int
id|sm_off
suffix:semicolon
multiline_comment|/* offset in m_data */
DECL|member|sm_len
id|u_int
id|sm_len
suffix:semicolon
multiline_comment|/* len of data */
macro_line|#ifdef&t;PCI
DECL|member|sm_use_count
r_int
id|sm_use_count
suffix:semicolon
macro_line|#endif
DECL|member|sm_data
r_char
id|sm_data
(braket
id|M_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|SMbuf
r_typedef
r_struct
id|s_mbuf
id|SMbuf
suffix:semicolon
multiline_comment|/* mbuf head, to typed data */
DECL|macro|smtod
mdefine_line|#define&t;smtod(x,t)&t;((t)((x)-&gt;sm_data + (x)-&gt;sm_off))
DECL|macro|smtodoff
mdefine_line|#define&t;smtodoff(x,t,o)&t;((t)((x)-&gt;sm_data + (o)))
macro_line|#endif&t;/* _MBUF_ */
eof
