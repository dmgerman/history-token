multiline_comment|/* &n; * Sony Programmable I/O Control Device driver for VAIO&n; *&n; * Copyright (C) 2001 Stelian Pop &lt;stelian.pop@fr.alcove.com&gt;, Alc&#xfffd;ve&n; *&n; * Copyright (C) 2001 Michael Ashley &lt;m.ashley@unsw.edu.au&gt;&n; *&n; * Copyright (C) 2001 Junichi Morita &lt;jun1m@mars.dti.ne.jp&gt;&n; *&n; * Copyright (C) 2000 Takaya Kinjo &lt;t-kinjo@tc4.so-net.ne.jp&gt;&n; *&n; * Copyright (C) 2000 Andrew Tridgell &lt;tridge@valinux.com&gt;&n; *&n; * Earlier work by Werner Almesberger, Paul `Rusty&squot; Russell and Paul Mackerras.&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef _SONYPI_H_ 
DECL|macro|_SONYPI_H_
mdefine_line|#define _SONYPI_H_
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* events the user application reading /dev/sonypi can use */
DECL|macro|SONYPI_EVENT_JOGDIAL_DOWN
mdefine_line|#define SONYPI_EVENT_JOGDIAL_DOWN&t;&t; 1
DECL|macro|SONYPI_EVENT_JOGDIAL_UP
mdefine_line|#define SONYPI_EVENT_JOGDIAL_UP&t;&t;&t; 2
DECL|macro|SONYPI_EVENT_JOGDIAL_DOWN_PRESSED
mdefine_line|#define SONYPI_EVENT_JOGDIAL_DOWN_PRESSED&t; 3
DECL|macro|SONYPI_EVENT_JOGDIAL_UP_PRESSED
mdefine_line|#define SONYPI_EVENT_JOGDIAL_UP_PRESSED&t;&t; 4
DECL|macro|SONYPI_EVENT_JOGDIAL_PRESSED
mdefine_line|#define SONYPI_EVENT_JOGDIAL_PRESSED&t;&t; 5
DECL|macro|SONYPI_EVENT_JOGDIAL_RELEASED
mdefine_line|#define SONYPI_EVENT_JOGDIAL_RELEASED&t;&t; 6
DECL|macro|SONYPI_EVENT_CAPTURE_PRESSED
mdefine_line|#define SONYPI_EVENT_CAPTURE_PRESSED&t;&t; 7
DECL|macro|SONYPI_EVENT_CAPTURE_RELEASED
mdefine_line|#define SONYPI_EVENT_CAPTURE_RELEASED&t;&t; 8
DECL|macro|SONYPI_EVENT_CAPTURE_PARTIALPRESSED
mdefine_line|#define SONYPI_EVENT_CAPTURE_PARTIALPRESSED&t; 9
DECL|macro|SONYPI_EVENT_CAPTURE_PARTIALRELEASED
mdefine_line|#define SONYPI_EVENT_CAPTURE_PARTIALRELEASED&t;10
DECL|macro|SONYPI_EVENT_FNKEY_ESC
mdefine_line|#define SONYPI_EVENT_FNKEY_ESC&t;&t;&t;11
DECL|macro|SONYPI_EVENT_FNKEY_F1
mdefine_line|#define SONYPI_EVENT_FNKEY_F1&t;&t;&t;12
DECL|macro|SONYPI_EVENT_FNKEY_F2
mdefine_line|#define SONYPI_EVENT_FNKEY_F2&t;&t;&t;13
DECL|macro|SONYPI_EVENT_FNKEY_F3
mdefine_line|#define SONYPI_EVENT_FNKEY_F3&t;&t;&t;14
DECL|macro|SONYPI_EVENT_FNKEY_F4
mdefine_line|#define SONYPI_EVENT_FNKEY_F4&t;&t;&t;15
DECL|macro|SONYPI_EVENT_FNKEY_F5
mdefine_line|#define SONYPI_EVENT_FNKEY_F5&t;&t;&t;16
DECL|macro|SONYPI_EVENT_FNKEY_F6
mdefine_line|#define SONYPI_EVENT_FNKEY_F6&t;&t;&t;17
DECL|macro|SONYPI_EVENT_FNKEY_F7
mdefine_line|#define SONYPI_EVENT_FNKEY_F7&t;&t;&t;18
DECL|macro|SONYPI_EVENT_FNKEY_F8
mdefine_line|#define SONYPI_EVENT_FNKEY_F8&t;&t;&t;19
DECL|macro|SONYPI_EVENT_FNKEY_F9
mdefine_line|#define SONYPI_EVENT_FNKEY_F9&t;&t;&t;20
DECL|macro|SONYPI_EVENT_FNKEY_F10
mdefine_line|#define SONYPI_EVENT_FNKEY_F10&t;&t;&t;21
DECL|macro|SONYPI_EVENT_FNKEY_F11
mdefine_line|#define SONYPI_EVENT_FNKEY_F11&t;&t;&t;22
DECL|macro|SONYPI_EVENT_FNKEY_F12
mdefine_line|#define SONYPI_EVENT_FNKEY_F12&t;&t;&t;23
DECL|macro|SONYPI_EVENT_FNKEY_1
mdefine_line|#define SONYPI_EVENT_FNKEY_1&t;&t;&t;24
DECL|macro|SONYPI_EVENT_FNKEY_2
mdefine_line|#define SONYPI_EVENT_FNKEY_2&t;&t;&t;25
DECL|macro|SONYPI_EVENT_FNKEY_D
mdefine_line|#define SONYPI_EVENT_FNKEY_D&t;&t;&t;26
DECL|macro|SONYPI_EVENT_FNKEY_E
mdefine_line|#define SONYPI_EVENT_FNKEY_E&t;&t;&t;27
DECL|macro|SONYPI_EVENT_FNKEY_F
mdefine_line|#define SONYPI_EVENT_FNKEY_F&t;&t;&t;28
DECL|macro|SONYPI_EVENT_FNKEY_S
mdefine_line|#define SONYPI_EVENT_FNKEY_S&t;&t;&t;29
DECL|macro|SONYPI_EVENT_FNKEY_B
mdefine_line|#define SONYPI_EVENT_FNKEY_B&t;&t;&t;30
DECL|macro|SONYPI_EVENT_BLUETOOTH_PRESSED
mdefine_line|#define SONYPI_EVENT_BLUETOOTH_PRESSED&t;&t;31
DECL|macro|SONYPI_EVENT_PKEY_P1
mdefine_line|#define SONYPI_EVENT_PKEY_P1&t;&t;&t;32
DECL|macro|SONYPI_EVENT_PKEY_P2
mdefine_line|#define SONYPI_EVENT_PKEY_P2&t;&t;&t;33
DECL|macro|SONYPI_EVENT_PKEY_P3
mdefine_line|#define SONYPI_EVENT_PKEY_P3&t;&t;&t;34
DECL|macro|SONYPI_EVENT_BACK_PRESSED
mdefine_line|#define SONYPI_EVENT_BACK_PRESSED&t;&t;35
DECL|macro|SONYPI_EVENT_LID_CLOSED
mdefine_line|#define SONYPI_EVENT_LID_CLOSED&t;&t;&t;36
DECL|macro|SONYPI_EVENT_LID_OPENED
mdefine_line|#define SONYPI_EVENT_LID_OPENED&t;&t;&t;37
multiline_comment|/* brightness etc. ioctls */
DECL|macro|SONYPI_IOCGBRT
mdefine_line|#define SONYPI_IOCGBRT&t;_IOR(&squot;v&squot;, 0, __u8)
DECL|macro|SONYPI_IOCSBRT
mdefine_line|#define SONYPI_IOCSBRT&t;_IOW(&squot;v&squot;, 0, __u8)
macro_line|#ifdef __KERNEL__
multiline_comment|/* used only for communication between v4l and sonypi */
DECL|macro|SONYPI_COMMAND_GETCAMERA
mdefine_line|#define SONYPI_COMMAND_GETCAMERA&t;&t; 1
DECL|macro|SONYPI_COMMAND_SETCAMERA
mdefine_line|#define SONYPI_COMMAND_SETCAMERA&t;&t; 2
DECL|macro|SONYPI_COMMAND_GETCAMERABRIGHTNESS
mdefine_line|#define SONYPI_COMMAND_GETCAMERABRIGHTNESS&t; 3
DECL|macro|SONYPI_COMMAND_SETCAMERABRIGHTNESS
mdefine_line|#define SONYPI_COMMAND_SETCAMERABRIGHTNESS&t; 4
DECL|macro|SONYPI_COMMAND_GETCAMERACONTRAST
mdefine_line|#define SONYPI_COMMAND_GETCAMERACONTRAST&t; 5
DECL|macro|SONYPI_COMMAND_SETCAMERACONTRAST
mdefine_line|#define SONYPI_COMMAND_SETCAMERACONTRAST&t; 6
DECL|macro|SONYPI_COMMAND_GETCAMERAHUE
mdefine_line|#define SONYPI_COMMAND_GETCAMERAHUE&t;&t; 7
DECL|macro|SONYPI_COMMAND_SETCAMERAHUE
mdefine_line|#define SONYPI_COMMAND_SETCAMERAHUE&t;&t; 8
DECL|macro|SONYPI_COMMAND_GETCAMERACOLOR
mdefine_line|#define SONYPI_COMMAND_GETCAMERACOLOR&t;&t; 9
DECL|macro|SONYPI_COMMAND_SETCAMERACOLOR
mdefine_line|#define SONYPI_COMMAND_SETCAMERACOLOR&t;&t;10
DECL|macro|SONYPI_COMMAND_GETCAMERASHARPNESS
mdefine_line|#define SONYPI_COMMAND_GETCAMERASHARPNESS&t;11
DECL|macro|SONYPI_COMMAND_SETCAMERASHARPNESS
mdefine_line|#define SONYPI_COMMAND_SETCAMERASHARPNESS&t;12
DECL|macro|SONYPI_COMMAND_GETCAMERAPICTURE
mdefine_line|#define SONYPI_COMMAND_GETCAMERAPICTURE&t;&t;13
DECL|macro|SONYPI_COMMAND_SETCAMERAPICTURE
mdefine_line|#define SONYPI_COMMAND_SETCAMERAPICTURE&t;&t;14
DECL|macro|SONYPI_COMMAND_GETCAMERAAGC
mdefine_line|#define SONYPI_COMMAND_GETCAMERAAGC&t;&t;15
DECL|macro|SONYPI_COMMAND_SETCAMERAAGC
mdefine_line|#define SONYPI_COMMAND_SETCAMERAAGC&t;&t;16
DECL|macro|SONYPI_COMMAND_GETCAMERADIRECTION
mdefine_line|#define SONYPI_COMMAND_GETCAMERADIRECTION&t;17
DECL|macro|SONYPI_COMMAND_GETCAMERAROMVERSION
mdefine_line|#define SONYPI_COMMAND_GETCAMERAROMVERSION&t;18
DECL|macro|SONYPI_COMMAND_GETCAMERAREVISION
mdefine_line|#define SONYPI_COMMAND_GETCAMERAREVISION&t;19
id|u8
id|sonypi_camera_command
c_func
(paren
r_int
id|command
comma
id|u8
id|value
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _SONYPI_H_ */
eof
