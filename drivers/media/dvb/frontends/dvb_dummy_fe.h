multiline_comment|/*&n; *  Driver for Dummy Frontend&n; *&n; *  Written by Emard &lt;emard@softhome.net&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.=&n; */
macro_line|#ifndef DVB_DUMMY_FE_H
DECL|macro|DVB_DUMMY_FE_H
mdefine_line|#define DVB_DUMMY_FE_H
macro_line|#include &lt;linux/dvb/frontend.h&gt;
macro_line|#include &quot;dvb_frontend.h&quot;
r_extern
r_struct
id|dvb_frontend
op_star
id|dvb_dummy_fe_ofdm_attach
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|dvb_frontend
op_star
id|dvb_dummy_fe_qpsk_attach
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|dvb_frontend
op_star
id|dvb_dummy_fe_qam_attach
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// DVB_DUMMY_FE_H
eof
