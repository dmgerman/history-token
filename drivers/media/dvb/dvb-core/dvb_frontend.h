multiline_comment|/* &n; * dvb-core.h&n; *&n; * Copyright (C) 2001 Ralph  Metzler &lt;ralph@convergence.de&gt;&n; *                    overhauled by Holger Waechtler &lt;holger@convergence.de&gt;&n; *                    for convergence integrated media GmbH&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU Lesser General Public License&n; * as published by the Free Software Foundation; either version 2.1&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n;&n; * You should have received a copy of the GNU Lesser General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; *&n; */
macro_line|#ifndef _DVB_FRONTEND_H_
DECL|macro|_DVB_FRONTEND_H_
mdefine_line|#define _DVB_FRONTEND_H_
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/dvb/frontend.h&gt;
macro_line|#include &quot;dvb_i2c.h&quot;
macro_line|#include &quot;dvbdev.h&quot;
multiline_comment|/**&n; *   when before_ioctl is registered and returns value 0, ioctl and after_ioctl&n; *   are not executed.&n; */
DECL|struct|dvb_frontend
r_struct
id|dvb_frontend
(brace
DECL|member|before_ioctl
r_int
(paren
op_star
id|before_ioctl
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|frontend
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|frontend
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
DECL|member|after_ioctl
r_int
(paren
op_star
id|after_ioctl
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|frontend
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
DECL|member|notifier_callback
r_void
(paren
op_star
id|notifier_callback
)paren
(paren
id|fe_status_t
id|s
comma
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|member|i2c
r_struct
id|dvb_i2c_bus
op_star
id|i2c
suffix:semicolon
DECL|member|before_after_data
r_void
op_star
id|before_after_data
suffix:semicolon
multiline_comment|/*  can be used by hardware module... */
DECL|member|notifier_data
r_void
op_star
id|notifier_data
suffix:semicolon
multiline_comment|/*  can be used by hardware module... */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/*  can be used by hardware module... */
)brace
suffix:semicolon
multiline_comment|/**&n; *   private frontend command ioctl&squot;s.&n; *   keep them in sync with the public ones defined in linux/dvb/frontend.h&n; */
DECL|macro|FE_SLEEP
mdefine_line|#define FE_SLEEP              _IO(&squot;v&squot;, 80)
DECL|macro|FE_INIT
mdefine_line|#define FE_INIT               _IO(&squot;v&squot;, 81)
DECL|macro|FE_RESET
mdefine_line|#define FE_RESET              _IO(&squot;v&squot;, 82)
r_extern
r_int
id|dvb_register_frontend
(paren
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|frontend
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
comma
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_void
op_star
id|data
comma
r_struct
id|dvb_frontend_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_int
id|dvb_unregister_frontend
(paren
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|frontend
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
comma
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
suffix:semicolon
multiline_comment|/**&n; *  Add special ioctl code performed before and after the main ioctl&n; *  to all frontend devices on the specified DVB adapter.&n; *  This is necessairy because the 22kHz/13V-18V/DiSEqC stuff depends&n; *  heavily on the hardware around the frontend, the same tuner can create &n; *  these signals on about a million different ways...&n; *&n; *  Return value: number of frontends where the ioctl&squot;s were applied.&n; */
r_extern
r_int
id|dvb_add_frontend_ioctls
(paren
r_struct
id|dvb_adapter
op_star
id|adapter
comma
r_int
(paren
op_star
id|before_ioctl
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|frontend
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
comma
r_int
(paren
op_star
id|after_ioctl
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|frontend
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
comma
r_void
op_star
id|before_after_data
)paren
suffix:semicolon
r_extern
r_void
id|dvb_remove_frontend_ioctls
(paren
r_struct
id|dvb_adapter
op_star
id|adapter
comma
r_int
(paren
op_star
id|before_ioctl
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|frontend
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
comma
r_int
(paren
op_star
id|after_ioctl
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|frontend
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
)paren
suffix:semicolon
r_extern
r_int
id|dvb_add_frontend_notifier
(paren
r_struct
id|dvb_adapter
op_star
id|adapter
comma
r_void
(paren
op_star
id|callback
)paren
(paren
id|fe_status_t
id|s
comma
r_void
op_star
id|data
)paren
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_void
id|dvb_remove_frontend_notifier
(paren
r_struct
id|dvb_adapter
op_star
id|adapter
comma
r_void
(paren
op_star
id|callback
)paren
(paren
id|fe_status_t
id|s
comma
r_void
op_star
id|data
)paren
)paren
suffix:semicolon
macro_line|#endif
eof
