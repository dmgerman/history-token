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
DECL|macro|DVB_NET_MULTICAST_MAX
mdefine_line|#define DVB_NET_MULTICAST_MAX 10
DECL|struct|dvb_net_priv_s
r_typedef
r_struct
id|dvb_net_priv_s
(brace
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|pid
id|u16
id|pid
suffix:semicolon
DECL|member|demux
id|dmx_demux_t
op_star
id|demux
suffix:semicolon
DECL|member|secfeed
id|dmx_section_feed_t
op_star
id|secfeed
suffix:semicolon
DECL|member|secfilter
id|dmx_section_filter_t
op_star
id|secfilter
suffix:semicolon
DECL|member|multi_num
r_int
id|multi_num
suffix:semicolon
DECL|member|multi_secfilter
id|dmx_section_filter_t
op_star
id|multi_secfilter
(braket
id|DVB_NET_MULTICAST_MAX
)braket
suffix:semicolon
DECL|member|multi_macs
r_int
r_char
id|multi_macs
(braket
id|DVB_NET_MULTICAST_MAX
)braket
(braket
l_int|6
)braket
suffix:semicolon
DECL|typedef|dvb_net_priv_t
)brace
id|dvb_net_priv_t
suffix:semicolon
DECL|struct|dvb_net_s
r_typedef
r_struct
id|dvb_net_s
(brace
DECL|member|dvbdev
id|dvb_device_t
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
id|dmx_demux_t
op_star
id|demux
suffix:semicolon
DECL|typedef|dvb_net_t
)brace
id|dvb_net_t
suffix:semicolon
r_void
id|dvb_net_release
c_func
(paren
id|dvb_net_t
op_star
)paren
suffix:semicolon
r_int
id|dvb_net_init
c_func
(paren
id|dvb_adapter_t
op_star
comma
id|dvb_net_t
op_star
comma
id|dmx_demux_t
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
