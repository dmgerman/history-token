multiline_comment|/*&n; * Bt8xx based DVB adapter driver&n; *&n; * Copyright (C) 2002,2003 Florian Schirmer &lt;jolt@tuxbox.org&gt;&n; * Copyright (C) 2002 Peter Hettkamp &lt;peter.hettkamp@t-online.de&gt;&n; * Copyright (C) 1999-2001 Ralph  Metzler &amp; Marcus Metzler for convergence integrated media GmbH&n; * Copyright (C) 1998,1999 Christian Theiss &lt;mistert@rz.fh-augsburg.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef DVB_BT8XX_H
DECL|macro|DVB_BT8XX_H
mdefine_line|#define DVB_BT8XX_H
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &quot;dvbdev.h&quot;
macro_line|#include &quot;dvb_net.h&quot;
macro_line|#include &quot;bttv.h&quot;
macro_line|#include &quot;mt352.h&quot;
macro_line|#include &quot;sp887x.h&quot;
macro_line|#include &quot;dst.h&quot;
macro_line|#include &quot;nxt6000.h&quot;
macro_line|#include &quot;cx24110.h&quot;
macro_line|#include &quot;or51211.h&quot;
DECL|struct|dvb_bt8xx_card
r_struct
id|dvb_bt8xx_card
(brace
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|nfeeds
r_int
id|nfeeds
suffix:semicolon
DECL|member|card_name
r_char
id|card_name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|dvb_adapter
r_struct
id|dvb_adapter
op_star
id|dvb_adapter
suffix:semicolon
DECL|member|bt
r_struct
id|bt878
op_star
id|bt
suffix:semicolon
DECL|member|bttv_nr
r_int
r_int
id|bttv_nr
suffix:semicolon
DECL|member|demux
r_struct
id|dvb_demux
id|demux
suffix:semicolon
DECL|member|dmxdev
r_struct
id|dmxdev
id|dmxdev
suffix:semicolon
DECL|member|fe_hw
r_struct
id|dmx_frontend
id|fe_hw
suffix:semicolon
DECL|member|fe_mem
r_struct
id|dmx_frontend
id|fe_mem
suffix:semicolon
DECL|member|gpio_mode
id|u32
id|gpio_mode
suffix:semicolon
DECL|member|op_sync_orin
id|u32
id|op_sync_orin
suffix:semicolon
DECL|member|irq_err_ignore
id|u32
id|irq_err_ignore
suffix:semicolon
DECL|member|i2c_adapter
r_struct
id|i2c_adapter
op_star
id|i2c_adapter
suffix:semicolon
DECL|member|dvbnet
r_struct
id|dvb_net
id|dvbnet
suffix:semicolon
DECL|member|fe
r_struct
id|dvb_frontend
op_star
id|fe
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* DVB_BT8XX_H */
eof
