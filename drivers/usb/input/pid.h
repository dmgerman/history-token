multiline_comment|/*&n; *  PID Force feedback support for hid devices.&n; *&n; *  Copyright (c) 2002 Rodrigo Damazio.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so by&n; * e-mail - mail your message to &lt;rdamazio@lsi.usp.br&gt;&n; */
DECL|macro|FF_EFFECTS_MAX
mdefine_line|#define FF_EFFECTS_MAX 64
DECL|macro|FF_PID_FLAGS_USED
mdefine_line|#define FF_PID_FLAGS_USED&t;1  /* If the effect exists */
DECL|macro|FF_PID_FLAGS_UPDATING
mdefine_line|#define FF_PID_FLAGS_UPDATING&t;2  /* If the effect is being updated */
DECL|macro|FF_PID_FLAGS_PLAYING
mdefine_line|#define FF_PID_FLAGS_PLAYING&t;3  /* If the effect is currently being played */
DECL|macro|FF_PID_FALSE
mdefine_line|#define FF_PID_FALSE&t;0
DECL|macro|FF_PID_TRUE
mdefine_line|#define FF_PID_TRUE&t;1
DECL|struct|hid_pid_effect
r_struct
id|hid_pid_effect
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|owner
id|pid_t
id|owner
suffix:semicolon
DECL|member|device_id
r_int
r_int
id|device_id
suffix:semicolon
singleline_comment|// The device-assigned ID
DECL|member|effect
r_struct
id|ff_effect
id|effect
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hid_ff_pid
r_struct
id|hid_ff_pid
(brace
DECL|member|hid
r_struct
id|hid_device
op_star
id|hid
suffix:semicolon
DECL|member|gain
r_int
r_int
r_int
id|gain
suffix:semicolon
DECL|member|urbffout
r_struct
id|urb
op_star
id|urbffout
suffix:semicolon
DECL|member|ffcr
r_struct
id|usb_ctrlrequest
id|ffcr
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|ctrl_buffer
r_char
id|ctrl_buffer
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|effects
r_struct
id|hid_pid_effect
id|effects
(braket
id|FF_EFFECTS_MAX
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Constants from the PID usage table (still far from complete)&n; */
DECL|macro|FF_PID_USAGE_BLOCK_LOAD
mdefine_line|#define FF_PID_USAGE_BLOCK_LOAD &t;0x89UL
DECL|macro|FF_PID_USAGE_BLOCK_FREE
mdefine_line|#define FF_PID_USAGE_BLOCK_FREE&t;&t;0x90UL
DECL|macro|FF_PID_USAGE_NEW_EFFECT
mdefine_line|#define FF_PID_USAGE_NEW_EFFECT &t;0xABUL
DECL|macro|FF_PID_USAGE_POOL_REPORT
mdefine_line|#define FF_PID_USAGE_POOL_REPORT&t;0x7FUL
eof
