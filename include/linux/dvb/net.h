multiline_comment|/* &n; * net.h&n; *&n; * Copyright (C) 2000 Marcus Metzler &lt;marcus@convergence.de&gt;&n; *                  &amp; Ralph  Metzler &lt;ralph@convergence.de&gt;&n;                      for convergence integrated media GmbH&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU Lesser General Public License&n; * as published by the Free Software Foundation; either version 2.1&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU Lesser General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; *&n; */
macro_line|#ifndef _DVBNET_H_
DECL|macro|_DVBNET_H_
mdefine_line|#define _DVBNET_H_
macro_line|#include &lt;asm/types.h&gt;
DECL|struct|dvb_net_if
r_struct
id|dvb_net_if
(brace
DECL|member|pid
id|__u16
id|pid
suffix:semicolon
DECL|member|if_num
id|__u16
id|if_num
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NET_ADD_IF
mdefine_line|#define NET_ADD_IF                 _IOWR(&squot;o&squot;, 52, struct dvb_net_if)
DECL|macro|NET_REMOVE_IF
mdefine_line|#define NET_REMOVE_IF              _IO(&squot;o&squot;, 53)
DECL|macro|NET_GET_IF
mdefine_line|#define NET_GET_IF                 _IOWR(&squot;o&squot;, 54, struct dvb_net_if)
macro_line|#endif /*_DVBNET_H_*/
eof
