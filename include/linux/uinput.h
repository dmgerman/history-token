macro_line|#ifndef __UINPUT_H_
DECL|macro|__UINPUT_H_
mdefine_line|#define __UINPUT_H_
multiline_comment|/*&n; *  User level driver support for input subsystem&n; *&n; * Heavily based on evdev.c by Vojtech Pavlik&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Author: Aristeu Sergio Rozanski Filho &lt;aris@cathedrallabs.org&gt;&n; * &n; * Changes/Revisions:&n; *&t;0.1&t;20/06/2002&n; *&t;&t;- first public version&n; */
macro_line|#ifdef __KERNEL__
DECL|macro|UINPUT_MINOR
mdefine_line|#define UINPUT_MINOR&t;&t;223
DECL|macro|UINPUT_NAME
mdefine_line|#define UINPUT_NAME&t;&t;&quot;uinput&quot;
DECL|macro|UINPUT_BUFFER_SIZE
mdefine_line|#define UINPUT_BUFFER_SIZE&t;16
DECL|macro|U_MAX_NAME_SIZE
mdefine_line|#define U_MAX_NAME_SIZE&t;&t;50
DECL|macro|UIST_CREATED
mdefine_line|#define UIST_CREATED&t;&t;1
DECL|struct|uinput_device
r_struct
id|uinput_device
(brace
DECL|member|dev
r_struct
id|input_dev
op_star
id|dev
suffix:semicolon
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
DECL|member|waitq
id|wait_queue_head_t
id|waitq
suffix:semicolon
DECL|member|ready
r_int
r_char
id|ready
comma
DECL|member|head
id|head
comma
DECL|member|tail
id|tail
suffix:semicolon
DECL|member|buff
r_struct
id|input_event
id|buff
(braket
id|UINPUT_BUFFER_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
multiline_comment|/* ioctl */
DECL|macro|UINPUT_IOCTL_BASE
mdefine_line|#define UINPUT_IOCTL_BASE&t;&squot;U&squot;
DECL|macro|UI_DEV_CREATE
mdefine_line|#define UI_DEV_CREATE&t;&t;_IO(UINPUT_IOCTL_BASE, 1)
DECL|macro|UI_DEV_DESTROY
mdefine_line|#define UI_DEV_DESTROY&t;&t;_IO(UINPUT_IOCTL_BASE, 2)
DECL|macro|UI_SET_EVBIT
mdefine_line|#define UI_SET_EVBIT&t;&t;_IOW(UINPUT_IOCTL_BASE, 100, int)
DECL|macro|UI_SET_KEYBIT
mdefine_line|#define UI_SET_KEYBIT&t;&t;_IOW(UINPUT_IOCTL_BASE, 101, int)
DECL|macro|UI_SET_RELBIT
mdefine_line|#define UI_SET_RELBIT&t;&t;_IOW(UINPUT_IOCTL_BASE, 102, int)
DECL|macro|UI_SET_ABSBIT
mdefine_line|#define UI_SET_ABSBIT&t;&t;_IOW(UINPUT_IOCTL_BASE, 103, int)
DECL|macro|UI_SET_MSCBIT
mdefine_line|#define UI_SET_MSCBIT&t;&t;_IOW(UINPUT_IOCTL_BASE, 104, int)
DECL|macro|UI_SET_LEDBIT
mdefine_line|#define UI_SET_LEDBIT&t;&t;_IOW(UINPUT_IOCTL_BASE, 105, int)
DECL|macro|UI_SET_SNDBIT
mdefine_line|#define UI_SET_SNDBIT&t;&t;_IOW(UINPUT_IOCTL_BASE, 106, int)
DECL|macro|UI_SET_FFBIT
mdefine_line|#define UI_SET_FFBIT&t;&t;_IOW(UINPUT_IOCTL_BASE, 107, int)
macro_line|#ifndef NBITS
DECL|macro|NBITS
mdefine_line|#define NBITS(x) ((((x)-1)/(sizeof(long)*8))+1)
macro_line|#endif&t;/* NBITS */
DECL|macro|UINPUT_MAX_NAME_SIZE
mdefine_line|#define UINPUT_MAX_NAME_SIZE&t;80
DECL|struct|uinput_user_dev
r_struct
id|uinput_user_dev
(brace
DECL|member|name
r_char
id|name
(braket
id|UINPUT_MAX_NAME_SIZE
)braket
suffix:semicolon
DECL|member|id
r_struct
id|input_devinfo
id|id
suffix:semicolon
DECL|member|ff_effects_max
r_int
id|ff_effects_max
suffix:semicolon
DECL|member|absmax
r_int
id|absmax
(braket
id|ABS_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|absmin
r_int
id|absmin
(braket
id|ABS_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|absfuzz
r_int
id|absfuzz
(braket
id|ABS_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|absflat
r_int
id|absflat
(braket
id|ABS_MAX
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;/* __UINPUT_H_ */
eof
