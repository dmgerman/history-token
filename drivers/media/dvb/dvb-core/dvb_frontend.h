multiline_comment|/* &n; * dvb_frontend.h&n; *&n; * Copyright (C) 2001 Ralph Metzler for convergence integrated media GmbH&n; *                    overhauled by Holger Waechtler for Convergence GmbH&n; *&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU Lesser General Public License&n; * as published by the Free Software Foundation; either version 2.1&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n;&n; * You should have received a copy of the GNU Lesser General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; *&n; */
macro_line|#ifndef _DVB_FRONTEND_H_
DECL|macro|_DVB_FRONTEND_H_
mdefine_line|#define _DVB_FRONTEND_H_
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/dvb/frontend.h&gt;
macro_line|#include &quot;dvbdev.h&quot;
multiline_comment|/* FIXME: Move to i2c-id.h */
DECL|macro|I2C_DRIVERID_DVBFE_ALPS_TDLB7
mdefine_line|#define I2C_DRIVERID_DVBFE_ALPS_TDLB7&t;I2C_DRIVERID_EXP2
DECL|macro|I2C_DRIVERID_DVBFE_ALPS_TDMB7
mdefine_line|#define I2C_DRIVERID_DVBFE_ALPS_TDMB7&t;I2C_DRIVERID_EXP2
DECL|macro|I2C_DRIVERID_DVBFE_AT76C651
mdefine_line|#define I2C_DRIVERID_DVBFE_AT76C651&t;I2C_DRIVERID_EXP2
DECL|macro|I2C_DRIVERID_DVBFE_CX24110
mdefine_line|#define I2C_DRIVERID_DVBFE_CX24110&t;I2C_DRIVERID_EXP2
DECL|macro|I2C_DRIVERID_DVBFE_CX22702
mdefine_line|#define I2C_DRIVERID_DVBFE_CX22702&t;I2C_DRIVERID_EXP2
DECL|macro|I2C_DRIVERID_DVBFE_DIB3000MB
mdefine_line|#define I2C_DRIVERID_DVBFE_DIB3000MB&t;I2C_DRIVERID_EXP2
DECL|macro|I2C_DRIVERID_DVBFE_DST
mdefine_line|#define I2C_DRIVERID_DVBFE_DST&t;&t;I2C_DRIVERID_EXP2
DECL|macro|I2C_DRIVERID_DVBFE_DUMMY
mdefine_line|#define I2C_DRIVERID_DVBFE_DUMMY&t;I2C_DRIVERID_EXP2
DECL|macro|I2C_DRIVERID_DVBFE_L64781
mdefine_line|#define I2C_DRIVERID_DVBFE_L64781&t;I2C_DRIVERID_EXP2
DECL|macro|I2C_DRIVERID_DVBFE_MT312
mdefine_line|#define I2C_DRIVERID_DVBFE_MT312&t;I2C_DRIVERID_EXP2
DECL|macro|I2C_DRIVERID_DVBFE_MT352
mdefine_line|#define I2C_DRIVERID_DVBFE_MT352&t;I2C_DRIVERID_EXP2
DECL|macro|I2C_DRIVERID_DVBFE_NXT6000
mdefine_line|#define I2C_DRIVERID_DVBFE_NXT6000&t;I2C_DRIVERID_EXP2
DECL|macro|I2C_DRIVERID_DVBFE_SP887X
mdefine_line|#define I2C_DRIVERID_DVBFE_SP887X&t;I2C_DRIVERID_EXP2
DECL|macro|I2C_DRIVERID_DVBFE_STV0299
mdefine_line|#define I2C_DRIVERID_DVBFE_STV0299&t;I2C_DRIVERID_EXP2
DECL|macro|I2C_DRIVERID_DVBFE_TDA1004X
mdefine_line|#define I2C_DRIVERID_DVBFE_TDA1004X&t;I2C_DRIVERID_EXP2
DECL|macro|I2C_DRIVERID_DVBFE_TDA8083
mdefine_line|#define I2C_DRIVERID_DVBFE_TDA8083&t;I2C_DRIVERID_EXP2
DECL|macro|I2C_DRIVERID_DVBFE_VES1820
mdefine_line|#define I2C_DRIVERID_DVBFE_VES1820&t;I2C_DRIVERID_EXP2
DECL|macro|I2C_DRIVERID_DVBFE_VES1X93
mdefine_line|#define I2C_DRIVERID_DVBFE_VES1X93&t;I2C_DRIVERID_EXP2
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
DECL|member|dvb_adapter
r_struct
id|dvb_adapter
op_star
id|dvb_adapter
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
DECL|struct|dvb_frontend_tune_settings
r_struct
id|dvb_frontend_tune_settings
(brace
DECL|member|min_delay_ms
r_int
id|min_delay_ms
suffix:semicolon
DECL|member|step_size
r_int
id|step_size
suffix:semicolon
DECL|member|max_drift
r_int
id|max_drift
suffix:semicolon
DECL|member|parameters
r_struct
id|dvb_frontend_parameters
id|parameters
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *   private frontend command ioctl&squot;s.&n; *   keep them in sync with the public ones defined in linux/dvb/frontend.h&n; * &n; *   FE_SLEEP. Ioctl used to put frontend into a low power mode.&n; *   FE_INIT. Ioctl used to initialise the frontend.&n; *   FE_GET_TUNE_SETTINGS. Get the frontend-specific tuning loop settings for the supplied set of parameters.&n; */
DECL|macro|FE_SLEEP
mdefine_line|#define FE_SLEEP              _IO(&squot;v&squot;, 80)
DECL|macro|FE_INIT
mdefine_line|#define FE_INIT               _IO(&squot;v&squot;, 81)
DECL|macro|FE_GET_TUNE_SETTINGS
mdefine_line|#define FE_GET_TUNE_SETTINGS  _IOWR(&squot;v&squot;, 83, struct dvb_frontend_tune_settings)
DECL|macro|FE_REGISTER
mdefine_line|#define FE_REGISTER&t;      _IO  (&squot;v&squot;, 84)
DECL|macro|FE_UNREGISTER
mdefine_line|#define FE_UNREGISTER&t;      _IO  (&squot;v&squot;, 85)
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
id|dvb_adapter
op_star
id|dvb_adapter
comma
r_void
op_star
id|data
comma
r_struct
id|dvb_frontend_info
op_star
id|info
comma
r_struct
id|module
op_star
id|module
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
id|dvb_adapter
op_star
id|dvb_adapter
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
