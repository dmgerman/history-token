multiline_comment|/* &n; * dvb_net.h&n; *&n; * Copyright (C) 2001 Convergence integrated media GmbH&n; *                    Ralph Metzler &lt;ralph@convergence.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU Lesser General Public License&n; * as published by the Free Software Foundation; either version 2.1&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU Lesser General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; *&n; */
macro_line|#ifndef _DVB_NET_H_
DECL|macro|_DVB_NET_H_
mdefine_line|#define _DVB_NET_H_
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &quot;dvbdev.h&quot;
DECL|macro|DVB_NET_DEVICES_MAX
mdefine_line|#define DVB_NET_DEVICES_MAX 10
DECL|struct|dvb_net
r_struct
id|dvb_net
(brace
DECL|member|dvbdev
r_struct
id|dvb_device
op_star
id|dvbdev
suffix:semicolon
DECL|member|card_num
r_int
id|card_num
suffix:semicolon
DECL|member|dev_num
r_int
id|dev_num
suffix:semicolon
DECL|member|device
r_struct
id|net_device
id|device
(braket
id|DVB_NET_DEVICES_MAX
)braket
suffix:semicolon
DECL|member|state
r_int
id|state
(braket
id|DVB_NET_DEVICES_MAX
)braket
suffix:semicolon
DECL|member|demux
r_struct
id|dmx_demux
op_star
id|demux
suffix:semicolon
)brace
suffix:semicolon
r_void
id|dvb_net_release
c_func
(paren
r_struct
id|dvb_net
op_star
)paren
suffix:semicolon
r_int
id|dvb_net_init
c_func
(paren
r_struct
id|dvb_adapter
op_star
comma
r_struct
id|dvb_net
op_star
comma
r_struct
id|dmx_demux
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
