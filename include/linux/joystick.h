macro_line|#ifndef _LINUX_JOYSTICK_H
DECL|macro|_LINUX_JOYSTICK_H
mdefine_line|#define _LINUX_JOYSTICK_H
multiline_comment|/*&n; * $Id: joystick.h,v 1.2 2000/05/29 10:54:53 vojtech Exp $&n; *&n; *  Copyright (C) 1996-2000 Vojtech Pavlik&n; *&n; *  Sponsored by SuSE&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@suse.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/*&n; * Version&n; */
DECL|macro|JS_VERSION
mdefine_line|#define JS_VERSION&t;&t;0x020000
multiline_comment|/*&n; * Types and constants for reading from /dev/js&n; */
DECL|macro|JS_EVENT_BUTTON
mdefine_line|#define JS_EVENT_BUTTON&t;&t;0x01&t;/* button pressed/released */
DECL|macro|JS_EVENT_AXIS
mdefine_line|#define JS_EVENT_AXIS&t;&t;0x02&t;/* joystick moved */
DECL|macro|JS_EVENT_INIT
mdefine_line|#define JS_EVENT_INIT&t;&t;0x80&t;/* initial state of device */
DECL|struct|js_event
r_struct
id|js_event
(brace
DECL|member|time
id|__u32
id|time
suffix:semicolon
multiline_comment|/* event timestamp in miliseconds */
DECL|member|value
id|__s16
id|value
suffix:semicolon
multiline_comment|/* value */
DECL|member|type
id|__u8
id|type
suffix:semicolon
multiline_comment|/* event type */
DECL|member|number
id|__u8
id|number
suffix:semicolon
multiline_comment|/* axis/button number */
)brace
suffix:semicolon
multiline_comment|/*&n; * IOCTL commands for joystick driver&n; */
DECL|macro|JSIOCGVERSION
mdefine_line|#define JSIOCGVERSION&t;&t;_IOR(&squot;j&squot;, 0x01, __u32)&t;&t;&t;/* get driver version */
DECL|macro|JSIOCGAXES
mdefine_line|#define JSIOCGAXES&t;&t;_IOR(&squot;j&squot;, 0x11, __u8)&t;&t;&t;/* get number of axes */
DECL|macro|JSIOCGBUTTONS
mdefine_line|#define JSIOCGBUTTONS&t;&t;_IOR(&squot;j&squot;, 0x12, __u8)&t;&t;&t;/* get number of buttons */
DECL|macro|JSIOCGNAME
mdefine_line|#define JSIOCGNAME(len)&t;&t;_IOC(_IOC_READ, &squot;j&squot;, 0x13, len)         /* get identifier string */
DECL|macro|JSIOCSCORR
mdefine_line|#define JSIOCSCORR&t;&t;_IOW(&squot;j&squot;, 0x21, struct js_corr)&t;&t;/* set correction values */
DECL|macro|JSIOCGCORR
mdefine_line|#define JSIOCGCORR&t;&t;_IOR(&squot;j&squot;, 0x22, struct js_corr)&t;&t;/* get correction values */
multiline_comment|/*&n; * Types and constants for get/set correction&n; */
DECL|macro|JS_CORR_NONE
mdefine_line|#define JS_CORR_NONE&t;&t;0x00&t;/* returns raw values */
DECL|macro|JS_CORR_BROKEN
mdefine_line|#define JS_CORR_BROKEN&t;&t;0x01&t;/* broken line */
DECL|struct|js_corr
r_struct
id|js_corr
(brace
DECL|member|coef
id|__s32
id|coef
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|prec
id|__s16
id|prec
suffix:semicolon
DECL|member|type
id|__u16
id|type
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * v0.x compatibility definitions&n; */
DECL|macro|JS_RETURN
mdefine_line|#define JS_RETURN&t;&t;sizeof(struct JS_DATA_TYPE)
DECL|macro|JS_TRUE
mdefine_line|#define JS_TRUE&t;&t;&t;1
DECL|macro|JS_FALSE
mdefine_line|#define JS_FALSE&t;&t;0
DECL|macro|JS_X_0
mdefine_line|#define JS_X_0&t;&t;&t;0x01
DECL|macro|JS_Y_0
mdefine_line|#define JS_Y_0&t;&t;&t;0x02
DECL|macro|JS_X_1
mdefine_line|#define JS_X_1&t;&t;&t;0x04
DECL|macro|JS_Y_1
mdefine_line|#define JS_Y_1&t;&t;&t;0x08
DECL|macro|JS_MAX
mdefine_line|#define JS_MAX&t;&t;&t;2
DECL|macro|JS_DEF_TIMEOUT
mdefine_line|#define JS_DEF_TIMEOUT&t;&t;0x1300
DECL|macro|JS_DEF_CORR
mdefine_line|#define JS_DEF_CORR&t;&t;0
DECL|macro|JS_DEF_TIMELIMIT
mdefine_line|#define JS_DEF_TIMELIMIT&t;10L
DECL|macro|JS_SET_CAL
mdefine_line|#define JS_SET_CAL&t;&t;1
DECL|macro|JS_GET_CAL
mdefine_line|#define JS_GET_CAL&t;&t;2
DECL|macro|JS_SET_TIMEOUT
mdefine_line|#define JS_SET_TIMEOUT&t;&t;3
DECL|macro|JS_GET_TIMEOUT
mdefine_line|#define JS_GET_TIMEOUT&t;&t;4
DECL|macro|JS_SET_TIMELIMIT
mdefine_line|#define JS_SET_TIMELIMIT&t;5
DECL|macro|JS_GET_TIMELIMIT
mdefine_line|#define JS_GET_TIMELIMIT&t;6
DECL|macro|JS_GET_ALL
mdefine_line|#define JS_GET_ALL&t;&t;7
DECL|macro|JS_SET_ALL
mdefine_line|#define JS_SET_ALL&t;&t;8
DECL|struct|JS_DATA_TYPE
r_struct
id|JS_DATA_TYPE
(brace
DECL|member|buttons
r_int
id|buttons
suffix:semicolon
DECL|member|x
r_int
id|x
suffix:semicolon
DECL|member|y
r_int
id|y
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|JS_DATA_SAVE_TYPE
r_struct
id|JS_DATA_SAVE_TYPE
(brace
DECL|member|JS_TIMEOUT
r_int
id|JS_TIMEOUT
suffix:semicolon
DECL|member|BUSY
r_int
id|BUSY
suffix:semicolon
DECL|member|JS_EXPIRETIME
r_int
id|JS_EXPIRETIME
suffix:semicolon
DECL|member|JS_TIMELIMIT
r_int
id|JS_TIMELIMIT
suffix:semicolon
DECL|member|JS_SAVE
r_struct
id|JS_DATA_TYPE
id|JS_SAVE
suffix:semicolon
DECL|member|JS_CORR
r_struct
id|JS_DATA_TYPE
id|JS_CORR
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_JOYSTICK_H */
eof
