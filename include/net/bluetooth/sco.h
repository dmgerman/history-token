multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; *  $Id: sco.h,v 1.1.1.1 2002/03/08 21:03:15 maxk Exp $&n; */
macro_line|#ifndef __SCO_H
DECL|macro|__SCO_H
mdefine_line|#define __SCO_H
multiline_comment|/* SCO defaults */
DECL|macro|SCO_DEFAULT_MTU
mdefine_line|#define SCO_DEFAULT_MTU &t;500
DECL|macro|SCO_DEFAULT_FLUSH_TO
mdefine_line|#define SCO_DEFAULT_FLUSH_TO&t;0xFFFF
DECL|macro|SCO_CONN_TIMEOUT
mdefine_line|#define SCO_CONN_TIMEOUT &t;(HZ * 40)
DECL|macro|SCO_DISCONN_TIMEOUT
mdefine_line|#define SCO_DISCONN_TIMEOUT &t;(HZ * 2)
DECL|macro|SCO_CONN_IDLE_TIMEOUT
mdefine_line|#define SCO_CONN_IDLE_TIMEOUT&t;(HZ * 60)
multiline_comment|/* SCO socket address */
DECL|struct|sockaddr_sco
r_struct
id|sockaddr_sco
(brace
DECL|member|sco_family
id|sa_family_t
id|sco_family
suffix:semicolon
DECL|member|sco_bdaddr
id|bdaddr_t
id|sco_bdaddr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* set/get sockopt defines */
DECL|macro|SCO_OPTIONS
mdefine_line|#define SCO_OPTIONS  0x01
DECL|struct|sco_options
r_struct
id|sco_options
(brace
DECL|member|mtu
id|__u16
id|mtu
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SCO_CONNINFO
mdefine_line|#define SCO_CONNINFO  0x02
DECL|struct|sco_conninfo
r_struct
id|sco_conninfo
(brace
DECL|member|hci_handle
id|__u16
id|hci_handle
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ---- SCO connections ---- */
DECL|struct|sco_conn
r_struct
id|sco_conn
(brace
DECL|member|hcon
r_struct
id|hci_conn
op_star
id|hcon
suffix:semicolon
DECL|member|dst
id|bdaddr_t
op_star
id|dst
suffix:semicolon
DECL|member|src
id|bdaddr_t
op_star
id|src
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
DECL|member|mtu
r_int
r_int
id|mtu
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|sco_conn_lock
mdefine_line|#define sco_conn_lock(c)&t;spin_lock(&amp;c-&gt;lock);
DECL|macro|sco_conn_unlock
mdefine_line|#define sco_conn_unlock(c)&t;spin_unlock(&amp;c-&gt;lock);
multiline_comment|/* ----- SCO socket info ----- */
DECL|macro|sco_pi
mdefine_line|#define sco_pi(sk)   ((struct sco_pinfo *) sk-&gt;protinfo)
DECL|struct|sco_pinfo
r_struct
id|sco_pinfo
(brace
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|member|conn
r_struct
id|sco_conn
op_star
id|conn
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __SCO_H */
eof
