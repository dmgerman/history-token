macro_line|#ifndef _INPUT_H
DECL|macro|_INPUT_H
mdefine_line|#define _INPUT_H
multiline_comment|/*&n; * $Id: input.h,v 1.68 2002/05/31 10:35:49 fsirl Exp $&n; *&n; *  Copyright (c) 1999-2001 Vojtech Pavlik&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/time.h&gt;
macro_line|#else
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &lt;sys/ioctl.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#endif
multiline_comment|/*&n; * The event structure itself&n; */
DECL|struct|input_event
r_struct
id|input_event
(brace
DECL|member|time
r_struct
id|timeval
id|time
suffix:semicolon
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
DECL|member|code
r_int
r_int
id|code
suffix:semicolon
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Protocol version.&n; */
DECL|macro|EV_VERSION
mdefine_line|#define EV_VERSION&t;&t;0x010000
multiline_comment|/*&n; * IOCTLs (0x00 - 0x7f)&n; */
DECL|macro|EVIOCGVERSION
mdefine_line|#define EVIOCGVERSION&t;&t;_IOR(&squot;E&squot;, 0x01, int)&t;&t;&t;/* get driver version */
DECL|macro|EVIOCGID
mdefine_line|#define EVIOCGID&t;&t;_IOR(&squot;E&squot;, 0x02, short[4])&t;&t;/* get device ID */
DECL|macro|EVIOCGREP
mdefine_line|#define EVIOCGREP&t;&t;_IOR(&squot;E&squot;, 0x03, int[2])&t;&t;&t;/* get repeat settings */
DECL|macro|EVIOCSREP
mdefine_line|#define EVIOCSREP&t;&t;_IOW(&squot;E&squot;, 0x03, int[2])&t;&t;&t;/* get repeat settings */
DECL|macro|EVIOCGKEYCODE
mdefine_line|#define EVIOCGKEYCODE&t;&t;_IOR(&squot;E&squot;, 0x04, int[2])&t;&t;&t;/* get keycode */
DECL|macro|EVIOCSKEYCODE
mdefine_line|#define EVIOCSKEYCODE&t;&t;_IOW(&squot;E&squot;, 0x04, int[2])&t;&t;&t;/* set keycode */
DECL|macro|EVIOCGNAME
mdefine_line|#define EVIOCGNAME(len)&t;&t;_IOC(_IOC_READ, &squot;E&squot;, 0x06, len)&t;&t;/* get device name */
DECL|macro|EVIOCGPHYS
mdefine_line|#define EVIOCGPHYS(len)&t;&t;_IOC(_IOC_READ, &squot;E&squot;, 0x07, len)&t;&t;/* get physical location */
DECL|macro|EVIOCGUNIQ
mdefine_line|#define EVIOCGUNIQ(len)&t;&t;_IOC(_IOC_READ, &squot;E&squot;, 0x08, len)&t;&t;/* get unique identifier */
DECL|macro|EVIOCGKEY
mdefine_line|#define EVIOCGKEY(len)&t;&t;_IOC(_IOC_READ, &squot;E&squot;, 0x18, len)&t;&t;/* get global keystate */
DECL|macro|EVIOCGLED
mdefine_line|#define EVIOCGLED(len)&t;&t;_IOC(_IOC_READ, &squot;E&squot;, 0x19, len)&t;&t;/* get all LEDs */
DECL|macro|EVIOCGSND
mdefine_line|#define EVIOCGSND(len)&t;&t;_IOC(_IOC_READ, &squot;E&squot;, 0x1a, len)&t;&t;/* get all sounds status */
DECL|macro|EVIOCGBIT
mdefine_line|#define EVIOCGBIT(ev,len)&t;_IOC(_IOC_READ, &squot;E&squot;, 0x20 + ev, len)&t;/* get event bits */
DECL|macro|EVIOCGABS
mdefine_line|#define EVIOCGABS(abs)&t;&t;_IOR(&squot;E&squot;, 0x40 + abs, int[5])&t;&t;/* get abs value/limits */
DECL|macro|EVIOCSFF
mdefine_line|#define EVIOCSFF&t;&t;_IOC(_IOC_WRITE, &squot;E&squot;, 0x80, sizeof(struct ff_effect))&t;/* send a force effect to a force feedback device */
DECL|macro|EVIOCRMFF
mdefine_line|#define EVIOCRMFF&t;&t;_IOW(&squot;E&squot;, 0x81, int)&t;&t;&t;/* Erase a force effect */
DECL|macro|EVIOCGEFFECTS
mdefine_line|#define EVIOCGEFFECTS&t;&t;_IOR(&squot;E&squot;, 0x84, int)&t;&t;&t;/* Report number of effects playable at the same time */
multiline_comment|/*&n; * Event types&n; */
DECL|macro|EV_RST
mdefine_line|#define EV_RST&t;&t;&t;0x00
DECL|macro|EV_KEY
mdefine_line|#define EV_KEY&t;&t;&t;0x01
DECL|macro|EV_REL
mdefine_line|#define EV_REL&t;&t;&t;0x02
DECL|macro|EV_ABS
mdefine_line|#define EV_ABS&t;&t;&t;0x03
DECL|macro|EV_MSC
mdefine_line|#define EV_MSC&t;&t;&t;0x04
DECL|macro|EV_LED
mdefine_line|#define EV_LED&t;&t;&t;0x11
DECL|macro|EV_SND
mdefine_line|#define EV_SND&t;&t;&t;0x12
DECL|macro|EV_REP
mdefine_line|#define EV_REP&t;&t;&t;0x14
DECL|macro|EV_FF
mdefine_line|#define EV_FF&t;&t;&t;0x15
DECL|macro|EV_PWR
mdefine_line|#define EV_PWR&t;&t;&t;0x16
DECL|macro|EV_FF_STATUS
mdefine_line|#define EV_FF_STATUS&t;&t;0x17
DECL|macro|EV_MAX
mdefine_line|#define EV_MAX&t;&t;&t;0x1f
multiline_comment|/*&n; * Keys and buttons&n; */
DECL|macro|KEY_RESERVED
mdefine_line|#define KEY_RESERVED&t;&t;0
DECL|macro|KEY_ESC
mdefine_line|#define KEY_ESC&t;&t;&t;1
DECL|macro|KEY_1
mdefine_line|#define KEY_1&t;&t;&t;2
DECL|macro|KEY_2
mdefine_line|#define KEY_2&t;&t;&t;3
DECL|macro|KEY_3
mdefine_line|#define KEY_3&t;&t;&t;4
DECL|macro|KEY_4
mdefine_line|#define KEY_4&t;&t;&t;5
DECL|macro|KEY_5
mdefine_line|#define KEY_5&t;&t;&t;6
DECL|macro|KEY_6
mdefine_line|#define KEY_6&t;&t;&t;7
DECL|macro|KEY_7
mdefine_line|#define KEY_7&t;&t;&t;8
DECL|macro|KEY_8
mdefine_line|#define KEY_8&t;&t;&t;9
DECL|macro|KEY_9
mdefine_line|#define KEY_9&t;&t;&t;10
DECL|macro|KEY_0
mdefine_line|#define KEY_0&t;&t;&t;11
DECL|macro|KEY_MINUS
mdefine_line|#define KEY_MINUS&t;&t;12
DECL|macro|KEY_EQUAL
mdefine_line|#define KEY_EQUAL&t;&t;13
DECL|macro|KEY_BACKSPACE
mdefine_line|#define KEY_BACKSPACE&t;&t;14
DECL|macro|KEY_TAB
mdefine_line|#define KEY_TAB&t;&t;&t;15
DECL|macro|KEY_Q
mdefine_line|#define KEY_Q&t;&t;&t;16
DECL|macro|KEY_W
mdefine_line|#define KEY_W&t;&t;&t;17
DECL|macro|KEY_E
mdefine_line|#define KEY_E&t;&t;&t;18
DECL|macro|KEY_R
mdefine_line|#define KEY_R&t;&t;&t;19
DECL|macro|KEY_T
mdefine_line|#define KEY_T&t;&t;&t;20
DECL|macro|KEY_Y
mdefine_line|#define KEY_Y&t;&t;&t;21
DECL|macro|KEY_U
mdefine_line|#define KEY_U&t;&t;&t;22
DECL|macro|KEY_I
mdefine_line|#define KEY_I&t;&t;&t;23
DECL|macro|KEY_O
mdefine_line|#define KEY_O&t;&t;&t;24
DECL|macro|KEY_P
mdefine_line|#define KEY_P&t;&t;&t;25
DECL|macro|KEY_LEFTBRACE
mdefine_line|#define KEY_LEFTBRACE&t;&t;26
DECL|macro|KEY_RIGHTBRACE
mdefine_line|#define KEY_RIGHTBRACE&t;&t;27
DECL|macro|KEY_ENTER
mdefine_line|#define KEY_ENTER&t;&t;28
DECL|macro|KEY_LEFTCTRL
mdefine_line|#define KEY_LEFTCTRL&t;&t;29
DECL|macro|KEY_A
mdefine_line|#define KEY_A&t;&t;&t;30
DECL|macro|KEY_S
mdefine_line|#define KEY_S&t;&t;&t;31
DECL|macro|KEY_D
mdefine_line|#define KEY_D&t;&t;&t;32
DECL|macro|KEY_F
mdefine_line|#define KEY_F&t;&t;&t;33
DECL|macro|KEY_G
mdefine_line|#define KEY_G&t;&t;&t;34
DECL|macro|KEY_H
mdefine_line|#define KEY_H&t;&t;&t;35
DECL|macro|KEY_J
mdefine_line|#define KEY_J&t;&t;&t;36
DECL|macro|KEY_K
mdefine_line|#define KEY_K&t;&t;&t;37
DECL|macro|KEY_L
mdefine_line|#define KEY_L&t;&t;&t;38
DECL|macro|KEY_SEMICOLON
mdefine_line|#define KEY_SEMICOLON&t;&t;39
DECL|macro|KEY_APOSTROPHE
mdefine_line|#define KEY_APOSTROPHE&t;&t;40
DECL|macro|KEY_GRAVE
mdefine_line|#define KEY_GRAVE&t;&t;41
DECL|macro|KEY_LEFTSHIFT
mdefine_line|#define KEY_LEFTSHIFT&t;&t;42
DECL|macro|KEY_BACKSLASH
mdefine_line|#define KEY_BACKSLASH&t;&t;43
DECL|macro|KEY_Z
mdefine_line|#define KEY_Z&t;&t;&t;44
DECL|macro|KEY_X
mdefine_line|#define KEY_X&t;&t;&t;45
DECL|macro|KEY_C
mdefine_line|#define KEY_C&t;&t;&t;46
DECL|macro|KEY_V
mdefine_line|#define KEY_V&t;&t;&t;47
DECL|macro|KEY_B
mdefine_line|#define KEY_B&t;&t;&t;48
DECL|macro|KEY_N
mdefine_line|#define KEY_N&t;&t;&t;49
DECL|macro|KEY_M
mdefine_line|#define KEY_M&t;&t;&t;50
DECL|macro|KEY_COMMA
mdefine_line|#define KEY_COMMA&t;&t;51
DECL|macro|KEY_DOT
mdefine_line|#define KEY_DOT&t;&t;&t;52
DECL|macro|KEY_SLASH
mdefine_line|#define KEY_SLASH&t;&t;53
DECL|macro|KEY_RIGHTSHIFT
mdefine_line|#define KEY_RIGHTSHIFT&t;&t;54
DECL|macro|KEY_KPASTERISK
mdefine_line|#define KEY_KPASTERISK&t;&t;55
DECL|macro|KEY_LEFTALT
mdefine_line|#define KEY_LEFTALT&t;&t;56
DECL|macro|KEY_SPACE
mdefine_line|#define KEY_SPACE&t;&t;57
DECL|macro|KEY_CAPSLOCK
mdefine_line|#define KEY_CAPSLOCK&t;&t;58
DECL|macro|KEY_F1
mdefine_line|#define KEY_F1&t;&t;&t;59
DECL|macro|KEY_F2
mdefine_line|#define KEY_F2&t;&t;&t;60
DECL|macro|KEY_F3
mdefine_line|#define KEY_F3&t;&t;&t;61
DECL|macro|KEY_F4
mdefine_line|#define KEY_F4&t;&t;&t;62
DECL|macro|KEY_F5
mdefine_line|#define KEY_F5&t;&t;&t;63
DECL|macro|KEY_F6
mdefine_line|#define KEY_F6&t;&t;&t;64
DECL|macro|KEY_F7
mdefine_line|#define KEY_F7&t;&t;&t;65
DECL|macro|KEY_F8
mdefine_line|#define KEY_F8&t;&t;&t;66
DECL|macro|KEY_F9
mdefine_line|#define KEY_F9&t;&t;&t;67
DECL|macro|KEY_F10
mdefine_line|#define KEY_F10&t;&t;&t;68
DECL|macro|KEY_NUMLOCK
mdefine_line|#define KEY_NUMLOCK&t;&t;69
DECL|macro|KEY_SCROLLLOCK
mdefine_line|#define KEY_SCROLLLOCK&t;&t;70
DECL|macro|KEY_KP7
mdefine_line|#define KEY_KP7&t;&t;&t;71
DECL|macro|KEY_KP8
mdefine_line|#define KEY_KP8&t;&t;&t;72
DECL|macro|KEY_KP9
mdefine_line|#define KEY_KP9&t;&t;&t;73
DECL|macro|KEY_KPMINUS
mdefine_line|#define KEY_KPMINUS&t;&t;74
DECL|macro|KEY_KP4
mdefine_line|#define KEY_KP4&t;&t;&t;75
DECL|macro|KEY_KP5
mdefine_line|#define KEY_KP5&t;&t;&t;76
DECL|macro|KEY_KP6
mdefine_line|#define KEY_KP6&t;&t;&t;77
DECL|macro|KEY_KPPLUS
mdefine_line|#define KEY_KPPLUS&t;&t;78
DECL|macro|KEY_KP1
mdefine_line|#define KEY_KP1&t;&t;&t;79
DECL|macro|KEY_KP2
mdefine_line|#define KEY_KP2&t;&t;&t;80
DECL|macro|KEY_KP3
mdefine_line|#define KEY_KP3&t;&t;&t;81
DECL|macro|KEY_KP0
mdefine_line|#define KEY_KP0&t;&t;&t;82
DECL|macro|KEY_KPDOT
mdefine_line|#define KEY_KPDOT&t;&t;83
DECL|macro|KEY_103RD
mdefine_line|#define KEY_103RD&t;&t;84
DECL|macro|KEY_F13
mdefine_line|#define KEY_F13&t;&t;&t;85
DECL|macro|KEY_102ND
mdefine_line|#define KEY_102ND&t;&t;86
DECL|macro|KEY_F11
mdefine_line|#define KEY_F11&t;&t;&t;87
DECL|macro|KEY_F12
mdefine_line|#define KEY_F12&t;&t;&t;88
DECL|macro|KEY_F14
mdefine_line|#define KEY_F14&t;&t;&t;89
DECL|macro|KEY_F15
mdefine_line|#define KEY_F15&t;&t;&t;90
DECL|macro|KEY_F16
mdefine_line|#define KEY_F16&t;&t;&t;91
DECL|macro|KEY_F17
mdefine_line|#define KEY_F17&t;&t;&t;92
DECL|macro|KEY_F18
mdefine_line|#define KEY_F18&t;&t;&t;93
DECL|macro|KEY_F19
mdefine_line|#define KEY_F19&t;&t;&t;94
DECL|macro|KEY_F20
mdefine_line|#define KEY_F20&t;&t;&t;95
DECL|macro|KEY_KPENTER
mdefine_line|#define KEY_KPENTER&t;&t;96
DECL|macro|KEY_RIGHTCTRL
mdefine_line|#define KEY_RIGHTCTRL&t;&t;97
DECL|macro|KEY_KPSLASH
mdefine_line|#define KEY_KPSLASH&t;&t;98
DECL|macro|KEY_SYSRQ
mdefine_line|#define KEY_SYSRQ&t;&t;99
DECL|macro|KEY_RIGHTALT
mdefine_line|#define KEY_RIGHTALT&t;&t;100
DECL|macro|KEY_LINEFEED
mdefine_line|#define KEY_LINEFEED&t;&t;101
DECL|macro|KEY_HOME
mdefine_line|#define KEY_HOME&t;&t;102
DECL|macro|KEY_UP
mdefine_line|#define KEY_UP&t;&t;&t;103
DECL|macro|KEY_PAGEUP
mdefine_line|#define KEY_PAGEUP&t;&t;104
DECL|macro|KEY_LEFT
mdefine_line|#define KEY_LEFT&t;&t;105
DECL|macro|KEY_RIGHT
mdefine_line|#define KEY_RIGHT&t;&t;106
DECL|macro|KEY_END
mdefine_line|#define KEY_END&t;&t;&t;107
DECL|macro|KEY_DOWN
mdefine_line|#define KEY_DOWN&t;&t;108
DECL|macro|KEY_PAGEDOWN
mdefine_line|#define KEY_PAGEDOWN&t;&t;109
DECL|macro|KEY_INSERT
mdefine_line|#define KEY_INSERT&t;&t;110
DECL|macro|KEY_DELETE
mdefine_line|#define KEY_DELETE&t;&t;111
DECL|macro|KEY_MACRO
mdefine_line|#define KEY_MACRO&t;&t;112
DECL|macro|KEY_MUTE
mdefine_line|#define KEY_MUTE&t;&t;113
DECL|macro|KEY_VOLUMEDOWN
mdefine_line|#define KEY_VOLUMEDOWN&t;&t;114
DECL|macro|KEY_VOLUMEUP
mdefine_line|#define KEY_VOLUMEUP&t;&t;115
DECL|macro|KEY_POWER
mdefine_line|#define KEY_POWER&t;&t;116
DECL|macro|KEY_KPEQUAL
mdefine_line|#define KEY_KPEQUAL&t;&t;117
DECL|macro|KEY_KPPLUSMINUS
mdefine_line|#define KEY_KPPLUSMINUS&t;&t;118
DECL|macro|KEY_PAUSE
mdefine_line|#define KEY_PAUSE&t;&t;119
DECL|macro|KEY_F21
mdefine_line|#define KEY_F21&t;&t;&t;120
DECL|macro|KEY_F22
mdefine_line|#define KEY_F22&t;&t;&t;121
DECL|macro|KEY_F23
mdefine_line|#define KEY_F23&t;&t;&t;122
DECL|macro|KEY_F24
mdefine_line|#define KEY_F24&t;&t;&t;123
DECL|macro|KEY_KPCOMMA
mdefine_line|#define KEY_KPCOMMA&t;&t;124
DECL|macro|KEY_LEFTMETA
mdefine_line|#define KEY_LEFTMETA&t;&t;125
DECL|macro|KEY_RIGHTMETA
mdefine_line|#define KEY_RIGHTMETA&t;&t;126
DECL|macro|KEY_COMPOSE
mdefine_line|#define KEY_COMPOSE&t;&t;127
DECL|macro|KEY_STOP
mdefine_line|#define KEY_STOP&t;&t;128
DECL|macro|KEY_AGAIN
mdefine_line|#define KEY_AGAIN&t;&t;129
DECL|macro|KEY_PROPS
mdefine_line|#define KEY_PROPS&t;&t;130
DECL|macro|KEY_UNDO
mdefine_line|#define KEY_UNDO&t;&t;131
DECL|macro|KEY_FRONT
mdefine_line|#define KEY_FRONT&t;&t;132
DECL|macro|KEY_COPY
mdefine_line|#define KEY_COPY&t;&t;133
DECL|macro|KEY_OPEN
mdefine_line|#define KEY_OPEN&t;&t;134
DECL|macro|KEY_PASTE
mdefine_line|#define KEY_PASTE&t;&t;135
DECL|macro|KEY_FIND
mdefine_line|#define KEY_FIND&t;&t;136
DECL|macro|KEY_CUT
mdefine_line|#define KEY_CUT&t;&t;&t;137
DECL|macro|KEY_HELP
mdefine_line|#define KEY_HELP&t;&t;138
DECL|macro|KEY_MENU
mdefine_line|#define KEY_MENU&t;&t;139
DECL|macro|KEY_CALC
mdefine_line|#define KEY_CALC&t;&t;140
DECL|macro|KEY_SETUP
mdefine_line|#define KEY_SETUP&t;&t;141
DECL|macro|KEY_SLEEP
mdefine_line|#define KEY_SLEEP&t;&t;142
DECL|macro|KEY_WAKEUP
mdefine_line|#define KEY_WAKEUP&t;&t;143
DECL|macro|KEY_FILE
mdefine_line|#define KEY_FILE&t;&t;144
DECL|macro|KEY_SENDFILE
mdefine_line|#define KEY_SENDFILE&t;&t;145
DECL|macro|KEY_DELETEFILE
mdefine_line|#define KEY_DELETEFILE&t;&t;146
DECL|macro|KEY_XFER
mdefine_line|#define KEY_XFER&t;&t;147
DECL|macro|KEY_PROG1
mdefine_line|#define KEY_PROG1&t;&t;148
DECL|macro|KEY_PROG2
mdefine_line|#define KEY_PROG2&t;&t;149
DECL|macro|KEY_WWW
mdefine_line|#define KEY_WWW&t;&t;&t;150
DECL|macro|KEY_MSDOS
mdefine_line|#define KEY_MSDOS&t;&t;151
DECL|macro|KEY_COFFEE
mdefine_line|#define KEY_COFFEE&t;&t;152
DECL|macro|KEY_DIRECTION
mdefine_line|#define KEY_DIRECTION&t;&t;153
DECL|macro|KEY_CYCLEWINDOWS
mdefine_line|#define KEY_CYCLEWINDOWS&t;154
DECL|macro|KEY_MAIL
mdefine_line|#define KEY_MAIL&t;&t;155
DECL|macro|KEY_BOOKMARKS
mdefine_line|#define KEY_BOOKMARKS&t;&t;156
DECL|macro|KEY_COMPUTER
mdefine_line|#define KEY_COMPUTER&t;&t;157
DECL|macro|KEY_BACK
mdefine_line|#define KEY_BACK&t;&t;158
DECL|macro|KEY_FORWARD
mdefine_line|#define KEY_FORWARD&t;&t;159
DECL|macro|KEY_CLOSECD
mdefine_line|#define KEY_CLOSECD&t;&t;160
DECL|macro|KEY_EJECTCD
mdefine_line|#define KEY_EJECTCD&t;&t;161
DECL|macro|KEY_EJECTCLOSECD
mdefine_line|#define KEY_EJECTCLOSECD&t;162
DECL|macro|KEY_NEXTSONG
mdefine_line|#define KEY_NEXTSONG&t;&t;163
DECL|macro|KEY_PLAYPAUSE
mdefine_line|#define KEY_PLAYPAUSE&t;&t;164
DECL|macro|KEY_PREVIOUSSONG
mdefine_line|#define KEY_PREVIOUSSONG&t;165
DECL|macro|KEY_STOPCD
mdefine_line|#define KEY_STOPCD&t;&t;166
DECL|macro|KEY_RECORD
mdefine_line|#define KEY_RECORD&t;&t;167
DECL|macro|KEY_REWIND
mdefine_line|#define KEY_REWIND&t;&t;168
DECL|macro|KEY_PHONE
mdefine_line|#define KEY_PHONE&t;&t;169
DECL|macro|KEY_ISO
mdefine_line|#define KEY_ISO&t;&t;&t;170
DECL|macro|KEY_CONFIG
mdefine_line|#define KEY_CONFIG&t;&t;171
DECL|macro|KEY_HOMEPAGE
mdefine_line|#define KEY_HOMEPAGE&t;&t;172
DECL|macro|KEY_REFRESH
mdefine_line|#define KEY_REFRESH&t;&t;173
DECL|macro|KEY_EXIT
mdefine_line|#define KEY_EXIT&t;&t;174
DECL|macro|KEY_MOVE
mdefine_line|#define KEY_MOVE&t;&t;175
DECL|macro|KEY_EDIT
mdefine_line|#define KEY_EDIT&t;&t;176
DECL|macro|KEY_SCROLLUP
mdefine_line|#define KEY_SCROLLUP&t;&t;177
DECL|macro|KEY_SCROLLDOWN
mdefine_line|#define KEY_SCROLLDOWN&t;&t;178
DECL|macro|KEY_KPLEFTPAREN
mdefine_line|#define KEY_KPLEFTPAREN&t;&t;179
DECL|macro|KEY_KPRIGHTPAREN
mdefine_line|#define KEY_KPRIGHTPAREN&t;180
DECL|macro|KEY_INTL1
mdefine_line|#define KEY_INTL1&t;&t;181
DECL|macro|KEY_INTL2
mdefine_line|#define KEY_INTL2&t;&t;182
DECL|macro|KEY_INTL3
mdefine_line|#define KEY_INTL3&t;&t;183
DECL|macro|KEY_INTL4
mdefine_line|#define KEY_INTL4&t;&t;184
DECL|macro|KEY_INTL5
mdefine_line|#define KEY_INTL5&t;&t;185
DECL|macro|KEY_INTL6
mdefine_line|#define KEY_INTL6&t;&t;186
DECL|macro|KEY_INTL7
mdefine_line|#define KEY_INTL7&t;&t;187
DECL|macro|KEY_INTL8
mdefine_line|#define KEY_INTL8&t;&t;188
DECL|macro|KEY_INTL9
mdefine_line|#define KEY_INTL9&t;&t;189
DECL|macro|KEY_LANG1
mdefine_line|#define KEY_LANG1&t;&t;190
DECL|macro|KEY_LANG2
mdefine_line|#define KEY_LANG2&t;&t;191
DECL|macro|KEY_LANG3
mdefine_line|#define KEY_LANG3&t;&t;192
DECL|macro|KEY_LANG4
mdefine_line|#define KEY_LANG4&t;&t;193
DECL|macro|KEY_LANG5
mdefine_line|#define KEY_LANG5&t;&t;194
DECL|macro|KEY_LANG6
mdefine_line|#define KEY_LANG6&t;&t;195
DECL|macro|KEY_LANG7
mdefine_line|#define KEY_LANG7&t;&t;196
DECL|macro|KEY_LANG8
mdefine_line|#define KEY_LANG8&t;&t;197
DECL|macro|KEY_LANG9
mdefine_line|#define KEY_LANG9&t;&t;198
DECL|macro|KEY_PLAYCD
mdefine_line|#define KEY_PLAYCD&t;&t;200
DECL|macro|KEY_PAUSECD
mdefine_line|#define KEY_PAUSECD&t;&t;201
DECL|macro|KEY_PROG3
mdefine_line|#define KEY_PROG3&t;&t;202
DECL|macro|KEY_PROG4
mdefine_line|#define KEY_PROG4&t;&t;203
DECL|macro|KEY_SUSPEND
mdefine_line|#define KEY_SUSPEND&t;&t;205
DECL|macro|KEY_CLOSE
mdefine_line|#define KEY_CLOSE&t;&t;206
DECL|macro|KEY_PLAY
mdefine_line|#define KEY_PLAY&t;&t;207
DECL|macro|KEY_FASTFORWARD
mdefine_line|#define KEY_FASTFORWARD&t;&t;208
DECL|macro|KEY_BASSBOOST
mdefine_line|#define KEY_BASSBOOST&t;&t;209
DECL|macro|KEY_PRINT
mdefine_line|#define KEY_PRINT&t;&t;210
DECL|macro|KEY_HP
mdefine_line|#define KEY_HP&t;&t;&t;211
DECL|macro|KEY_CAMERA
mdefine_line|#define KEY_CAMERA&t;&t;212
DECL|macro|KEY_SOUND
mdefine_line|#define KEY_SOUND&t;&t;213
DECL|macro|KEY_QUESTION
mdefine_line|#define KEY_QUESTION&t;&t;214
DECL|macro|KEY_EMAIL
mdefine_line|#define KEY_EMAIL&t;&t;215
DECL|macro|KEY_CHAT
mdefine_line|#define KEY_CHAT&t;&t;216
DECL|macro|KEY_SEARCH
mdefine_line|#define KEY_SEARCH&t;&t;217
DECL|macro|KEY_CONNECT
mdefine_line|#define KEY_CONNECT&t;&t;218
DECL|macro|KEY_FINANCE
mdefine_line|#define KEY_FINANCE&t;&t;219
DECL|macro|KEY_SPORT
mdefine_line|#define KEY_SPORT&t;&t;220
DECL|macro|KEY_SHOP
mdefine_line|#define KEY_SHOP&t;&t;221
DECL|macro|KEY_ALTERASE
mdefine_line|#define KEY_ALTERASE&t;&t;222
DECL|macro|KEY_CANCEL
mdefine_line|#define KEY_CANCEL&t;&t;223
DECL|macro|KEY_BRIGHTNESSDOWN
mdefine_line|#define KEY_BRIGHTNESSDOWN&t;224
DECL|macro|KEY_BRIGHTNESSUP
mdefine_line|#define KEY_BRIGHTNESSUP&t;225
DECL|macro|KEY_UNKNOWN
mdefine_line|#define KEY_UNKNOWN&t;&t;240
DECL|macro|BTN_MISC
mdefine_line|#define BTN_MISC&t;&t;0x100
DECL|macro|BTN_0
mdefine_line|#define BTN_0&t;&t;&t;0x100
DECL|macro|BTN_1
mdefine_line|#define BTN_1&t;&t;&t;0x101
DECL|macro|BTN_2
mdefine_line|#define BTN_2&t;&t;&t;0x102
DECL|macro|BTN_3
mdefine_line|#define BTN_3&t;&t;&t;0x103
DECL|macro|BTN_4
mdefine_line|#define BTN_4&t;&t;&t;0x104
DECL|macro|BTN_5
mdefine_line|#define BTN_5&t;&t;&t;0x105
DECL|macro|BTN_6
mdefine_line|#define BTN_6&t;&t;&t;0x106
DECL|macro|BTN_7
mdefine_line|#define BTN_7&t;&t;&t;0x107
DECL|macro|BTN_8
mdefine_line|#define BTN_8&t;&t;&t;0x108
DECL|macro|BTN_9
mdefine_line|#define BTN_9&t;&t;&t;0x109
DECL|macro|BTN_MOUSE
mdefine_line|#define BTN_MOUSE&t;&t;0x110
DECL|macro|BTN_LEFT
mdefine_line|#define BTN_LEFT&t;&t;0x110
DECL|macro|BTN_RIGHT
mdefine_line|#define BTN_RIGHT&t;&t;0x111
DECL|macro|BTN_MIDDLE
mdefine_line|#define BTN_MIDDLE&t;&t;0x112
DECL|macro|BTN_SIDE
mdefine_line|#define BTN_SIDE&t;&t;0x113
DECL|macro|BTN_EXTRA
mdefine_line|#define BTN_EXTRA&t;&t;0x114
DECL|macro|BTN_FORWARD
mdefine_line|#define BTN_FORWARD&t;&t;0x115
DECL|macro|BTN_BACK
mdefine_line|#define BTN_BACK&t;&t;0x116
DECL|macro|BTN_JOYSTICK
mdefine_line|#define BTN_JOYSTICK&t;&t;0x120
DECL|macro|BTN_TRIGGER
mdefine_line|#define BTN_TRIGGER&t;&t;0x120
DECL|macro|BTN_THUMB
mdefine_line|#define BTN_THUMB&t;&t;0x121
DECL|macro|BTN_THUMB2
mdefine_line|#define BTN_THUMB2&t;&t;0x122
DECL|macro|BTN_TOP
mdefine_line|#define BTN_TOP&t;&t;&t;0x123
DECL|macro|BTN_TOP2
mdefine_line|#define BTN_TOP2&t;&t;0x124
DECL|macro|BTN_PINKIE
mdefine_line|#define BTN_PINKIE&t;&t;0x125
DECL|macro|BTN_BASE
mdefine_line|#define BTN_BASE&t;&t;0x126
DECL|macro|BTN_BASE2
mdefine_line|#define BTN_BASE2&t;&t;0x127
DECL|macro|BTN_BASE3
mdefine_line|#define BTN_BASE3&t;&t;0x128
DECL|macro|BTN_BASE4
mdefine_line|#define BTN_BASE4&t;&t;0x129
DECL|macro|BTN_BASE5
mdefine_line|#define BTN_BASE5&t;&t;0x12a
DECL|macro|BTN_BASE6
mdefine_line|#define BTN_BASE6&t;&t;0x12b
DECL|macro|BTN_DEAD
mdefine_line|#define BTN_DEAD&t;&t;0x12f
DECL|macro|BTN_GAMEPAD
mdefine_line|#define BTN_GAMEPAD&t;&t;0x130
DECL|macro|BTN_A
mdefine_line|#define BTN_A&t;&t;&t;0x130
DECL|macro|BTN_B
mdefine_line|#define BTN_B&t;&t;&t;0x131
DECL|macro|BTN_C
mdefine_line|#define BTN_C&t;&t;&t;0x132
DECL|macro|BTN_X
mdefine_line|#define BTN_X&t;&t;&t;0x133
DECL|macro|BTN_Y
mdefine_line|#define BTN_Y&t;&t;&t;0x134
DECL|macro|BTN_Z
mdefine_line|#define BTN_Z&t;&t;&t;0x135
DECL|macro|BTN_TL
mdefine_line|#define BTN_TL&t;&t;&t;0x136
DECL|macro|BTN_TR
mdefine_line|#define BTN_TR&t;&t;&t;0x137
DECL|macro|BTN_TL2
mdefine_line|#define BTN_TL2&t;&t;&t;0x138
DECL|macro|BTN_TR2
mdefine_line|#define BTN_TR2&t;&t;&t;0x139
DECL|macro|BTN_SELECT
mdefine_line|#define BTN_SELECT&t;&t;0x13a
DECL|macro|BTN_START
mdefine_line|#define BTN_START&t;&t;0x13b
DECL|macro|BTN_MODE
mdefine_line|#define BTN_MODE&t;&t;0x13c
DECL|macro|BTN_THUMBL
mdefine_line|#define BTN_THUMBL&t;&t;0x13d
DECL|macro|BTN_THUMBR
mdefine_line|#define BTN_THUMBR&t;&t;0x13e
DECL|macro|BTN_DIGI
mdefine_line|#define BTN_DIGI&t;&t;0x140
DECL|macro|BTN_TOOL_PEN
mdefine_line|#define BTN_TOOL_PEN&t;&t;0x140
DECL|macro|BTN_TOOL_RUBBER
mdefine_line|#define BTN_TOOL_RUBBER&t;&t;0x141
DECL|macro|BTN_TOOL_BRUSH
mdefine_line|#define BTN_TOOL_BRUSH&t;&t;0x142
DECL|macro|BTN_TOOL_PENCIL
mdefine_line|#define BTN_TOOL_PENCIL&t;&t;0x143
DECL|macro|BTN_TOOL_AIRBRUSH
mdefine_line|#define BTN_TOOL_AIRBRUSH&t;0x144
DECL|macro|BTN_TOOL_FINGER
mdefine_line|#define BTN_TOOL_FINGER&t;&t;0x145
DECL|macro|BTN_TOOL_MOUSE
mdefine_line|#define BTN_TOOL_MOUSE&t;&t;0x146
DECL|macro|BTN_TOOL_LENS
mdefine_line|#define BTN_TOOL_LENS&t;&t;0x147
DECL|macro|BTN_TOUCH
mdefine_line|#define BTN_TOUCH&t;&t;0x14a
DECL|macro|BTN_STYLUS
mdefine_line|#define BTN_STYLUS&t;&t;0x14b
DECL|macro|BTN_STYLUS2
mdefine_line|#define BTN_STYLUS2&t;&t;0x14c
DECL|macro|BTN_WHEEL
mdefine_line|#define BTN_WHEEL&t;&t;0x150
DECL|macro|BTN_GEAR_DOWN
mdefine_line|#define BTN_GEAR_DOWN&t;&t;0x150
DECL|macro|BTN_GEAR_UP
mdefine_line|#define BTN_GEAR_UP&t;&t;0x151
DECL|macro|KEY_MAX
mdefine_line|#define KEY_MAX&t;&t;&t;0x1ff
multiline_comment|/*&n; * Relative axes&n; */
DECL|macro|REL_X
mdefine_line|#define REL_X&t;&t;&t;0x00
DECL|macro|REL_Y
mdefine_line|#define REL_Y&t;&t;&t;0x01
DECL|macro|REL_Z
mdefine_line|#define REL_Z&t;&t;&t;0x02
DECL|macro|REL_HWHEEL
mdefine_line|#define REL_HWHEEL&t;&t;0x06
DECL|macro|REL_DIAL
mdefine_line|#define REL_DIAL&t;&t;0x07
DECL|macro|REL_WHEEL
mdefine_line|#define REL_WHEEL&t;&t;0x08
DECL|macro|REL_MISC
mdefine_line|#define REL_MISC&t;&t;0x09
DECL|macro|REL_MAX
mdefine_line|#define REL_MAX&t;&t;&t;0x0f
multiline_comment|/*&n; * Absolute axes&n; */
DECL|macro|ABS_X
mdefine_line|#define ABS_X&t;&t;&t;0x00
DECL|macro|ABS_Y
mdefine_line|#define ABS_Y&t;&t;&t;0x01
DECL|macro|ABS_Z
mdefine_line|#define ABS_Z&t;&t;&t;0x02
DECL|macro|ABS_RX
mdefine_line|#define ABS_RX&t;&t;&t;0x03
DECL|macro|ABS_RY
mdefine_line|#define ABS_RY&t;&t;&t;0x04
DECL|macro|ABS_RZ
mdefine_line|#define ABS_RZ&t;&t;&t;0x05
DECL|macro|ABS_THROTTLE
mdefine_line|#define ABS_THROTTLE&t;&t;0x06
DECL|macro|ABS_RUDDER
mdefine_line|#define ABS_RUDDER&t;&t;0x07
DECL|macro|ABS_WHEEL
mdefine_line|#define ABS_WHEEL&t;&t;0x08
DECL|macro|ABS_GAS
mdefine_line|#define ABS_GAS&t;&t;&t;0x09
DECL|macro|ABS_BRAKE
mdefine_line|#define ABS_BRAKE&t;&t;0x0a
DECL|macro|ABS_HAT0X
mdefine_line|#define ABS_HAT0X&t;&t;0x10
DECL|macro|ABS_HAT0Y
mdefine_line|#define ABS_HAT0Y&t;&t;0x11
DECL|macro|ABS_HAT1X
mdefine_line|#define ABS_HAT1X&t;&t;0x12
DECL|macro|ABS_HAT1Y
mdefine_line|#define ABS_HAT1Y&t;&t;0x13
DECL|macro|ABS_HAT2X
mdefine_line|#define ABS_HAT2X&t;&t;0x14
DECL|macro|ABS_HAT2Y
mdefine_line|#define ABS_HAT2Y&t;&t;0x15
DECL|macro|ABS_HAT3X
mdefine_line|#define ABS_HAT3X&t;&t;0x16
DECL|macro|ABS_HAT3Y
mdefine_line|#define ABS_HAT3Y&t;&t;0x17
DECL|macro|ABS_PRESSURE
mdefine_line|#define ABS_PRESSURE&t;&t;0x18
DECL|macro|ABS_DISTANCE
mdefine_line|#define ABS_DISTANCE&t;&t;0x19
DECL|macro|ABS_TILT_X
mdefine_line|#define ABS_TILT_X&t;&t;0x1a
DECL|macro|ABS_TILT_Y
mdefine_line|#define ABS_TILT_Y&t;&t;0x1b
DECL|macro|ABS_VOLUME
mdefine_line|#define ABS_VOLUME&t;&t;0x20
DECL|macro|ABS_MISC
mdefine_line|#define ABS_MISC&t;&t;0x28
DECL|macro|ABS_MAX
mdefine_line|#define ABS_MAX&t;&t;&t;0x3f
multiline_comment|/*&n; * Misc events&n; */
DECL|macro|MSC_SERIAL
mdefine_line|#define MSC_SERIAL&t;&t;0x00
DECL|macro|MSC_PULSELED
mdefine_line|#define MSC_PULSELED&t;&t;0x01
DECL|macro|MSC_MAX
mdefine_line|#define MSC_MAX&t;&t;&t;0x07
multiline_comment|/*&n; * LEDs&n; */
DECL|macro|LED_NUML
mdefine_line|#define LED_NUML&t;&t;0x00
DECL|macro|LED_CAPSL
mdefine_line|#define LED_CAPSL&t;&t;0x01
DECL|macro|LED_SCROLLL
mdefine_line|#define LED_SCROLLL&t;&t;0x02
DECL|macro|LED_COMPOSE
mdefine_line|#define LED_COMPOSE&t;&t;0x03
DECL|macro|LED_KANA
mdefine_line|#define LED_KANA&t;&t;0x04
DECL|macro|LED_SLEEP
mdefine_line|#define LED_SLEEP&t;&t;0x05
DECL|macro|LED_SUSPEND
mdefine_line|#define LED_SUSPEND&t;&t;0x06
DECL|macro|LED_MUTE
mdefine_line|#define LED_MUTE&t;&t;0x07
DECL|macro|LED_MISC
mdefine_line|#define LED_MISC&t;&t;0x08
DECL|macro|LED_MAX
mdefine_line|#define LED_MAX&t;&t;&t;0x0f
multiline_comment|/*&n; * Autorepeat values&n; */
DECL|macro|REP_DELAY
mdefine_line|#define REP_DELAY&t;&t;0x00
DECL|macro|REP_PERIOD
mdefine_line|#define REP_PERIOD&t;&t;0x01
DECL|macro|REP_MAX
mdefine_line|#define REP_MAX&t;&t;&t;0x01
multiline_comment|/*&n; * Sounds&n; */
DECL|macro|SND_CLICK
mdefine_line|#define SND_CLICK&t;&t;0x00
DECL|macro|SND_BELL
mdefine_line|#define SND_BELL&t;&t;0x01
DECL|macro|SND_MAX
mdefine_line|#define SND_MAX&t;&t;&t;0x07
multiline_comment|/*&n; * IDs.&n; */
DECL|macro|ID_BUS
mdefine_line|#define ID_BUS&t;&t;&t;0
DECL|macro|ID_VENDOR
mdefine_line|#define ID_VENDOR&t;&t;1
DECL|macro|ID_PRODUCT
mdefine_line|#define ID_PRODUCT&t;&t;2
DECL|macro|ID_VERSION
mdefine_line|#define ID_VERSION&t;&t;3
DECL|macro|BUS_PCI
mdefine_line|#define BUS_PCI&t;&t;&t;0x01
DECL|macro|BUS_ISAPNP
mdefine_line|#define BUS_ISAPNP&t;&t;0x02
DECL|macro|BUS_USB
mdefine_line|#define BUS_USB&t;&t;&t;0x03
DECL|macro|BUS_HIL
mdefine_line|#define BUS_HIL&t;&t;&t;0x04
DECL|macro|BUS_ISA
mdefine_line|#define BUS_ISA&t;&t;&t;0x10
DECL|macro|BUS_I8042
mdefine_line|#define BUS_I8042&t;&t;0x11
DECL|macro|BUS_XTKBD
mdefine_line|#define BUS_XTKBD&t;&t;0x12
DECL|macro|BUS_RS232
mdefine_line|#define BUS_RS232&t;&t;0x13
DECL|macro|BUS_GAMEPORT
mdefine_line|#define BUS_GAMEPORT&t;&t;0x14
DECL|macro|BUS_PARPORT
mdefine_line|#define BUS_PARPORT&t;&t;0x15
DECL|macro|BUS_AMIGA
mdefine_line|#define BUS_AMIGA&t;&t;0x16
DECL|macro|BUS_ADB
mdefine_line|#define BUS_ADB&t;&t;&t;0x17
DECL|macro|BUS_I2C
mdefine_line|#define BUS_I2C&t;&t;&t;0x18
multiline_comment|/*&n; * Values describing the status of an effect&n; */
DECL|macro|FF_STATUS_STOPPED
mdefine_line|#define FF_STATUS_STOPPED&t;0x00
DECL|macro|FF_STATUS_PLAYING
mdefine_line|#define FF_STATUS_PLAYING&t;0x01
DECL|macro|FF_STATUS_MAX
mdefine_line|#define FF_STATUS_MAX&t;&t;0x01
multiline_comment|/*&n; * Structures used in ioctls to upload effects to a device&n; * The first structures are not passed directly by using ioctls.&n; * They are sub-structures of the actually sent structure (called ff_effect)&n; */
DECL|struct|ff_replay
r_struct
id|ff_replay
(brace
DECL|member|length
id|__u16
id|length
suffix:semicolon
multiline_comment|/* Duration of an effect in ms. All other times are also expressed in ms */
DECL|member|delay
id|__u16
id|delay
suffix:semicolon
multiline_comment|/* Time to wait before to start playing an effect */
)brace
suffix:semicolon
DECL|struct|ff_trigger
r_struct
id|ff_trigger
(brace
DECL|member|button
id|__u16
id|button
suffix:semicolon
multiline_comment|/* Number of button triggering an effect */
DECL|member|interval
id|__u16
id|interval
suffix:semicolon
multiline_comment|/* Time to wait before an effect can be re-triggered (ms) */
)brace
suffix:semicolon
DECL|struct|ff_envelope
r_struct
id|ff_envelope
(brace
DECL|member|attack_length
id|__u16
id|attack_length
suffix:semicolon
multiline_comment|/* Duration of attack (ms) */
DECL|member|attack_level
id|__u16
id|attack_level
suffix:semicolon
multiline_comment|/* Level at beginning of attack */
DECL|member|fade_length
id|__u16
id|fade_length
suffix:semicolon
multiline_comment|/* Duration of fade (ms) */
DECL|member|fade_level
id|__u16
id|fade_level
suffix:semicolon
multiline_comment|/* Level at end of fade */
)brace
suffix:semicolon
multiline_comment|/* FF_CONSTANT */
DECL|struct|ff_constant_effect
r_struct
id|ff_constant_effect
(brace
DECL|member|level
id|__s16
id|level
suffix:semicolon
multiline_comment|/* Strength of effect. Negative values are OK */
DECL|member|envelope
r_struct
id|ff_envelope
id|envelope
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* FF_RAMP */
DECL|struct|ff_ramp_effect
r_struct
id|ff_ramp_effect
(brace
DECL|member|start_level
id|__s16
id|start_level
suffix:semicolon
DECL|member|end_level
id|__s16
id|end_level
suffix:semicolon
DECL|member|envelope
r_struct
id|ff_envelope
id|envelope
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* FF_SPRING of FF_FRICTION */
DECL|struct|ff_condition_effect
r_struct
id|ff_condition_effect
(brace
DECL|member|right_saturation
id|__u16
id|right_saturation
suffix:semicolon
multiline_comment|/* Max level when joystick is on the right */
DECL|member|left_saturation
id|__u16
id|left_saturation
suffix:semicolon
multiline_comment|/* Max level when joystick in on the left */
DECL|member|right_coeff
id|__s16
id|right_coeff
suffix:semicolon
multiline_comment|/* Indicates how fast the force grows when the&n;&t;&t;&t;&t;   joystick moves to the right */
DECL|member|left_coeff
id|__s16
id|left_coeff
suffix:semicolon
multiline_comment|/* Same for left side */
DECL|member|deadband
id|__u16
id|deadband
suffix:semicolon
multiline_comment|/* Size of area where no force is produced */
DECL|member|center
id|__s16
id|center
suffix:semicolon
multiline_comment|/* Position of dead zone */
)brace
suffix:semicolon
multiline_comment|/* FF_PERIODIC */
DECL|struct|ff_periodic_effect
r_struct
id|ff_periodic_effect
(brace
DECL|member|waveform
id|__u16
id|waveform
suffix:semicolon
multiline_comment|/* Kind of wave (sine, square...) */
DECL|member|period
id|__u16
id|period
suffix:semicolon
multiline_comment|/* in ms */
DECL|member|magnitude
id|__s16
id|magnitude
suffix:semicolon
multiline_comment|/* Peak value */
DECL|member|offset
id|__s16
id|offset
suffix:semicolon
multiline_comment|/* Mean value of wave (roughly) */
DECL|member|phase
id|__u16
id|phase
suffix:semicolon
multiline_comment|/* &squot;Horizontal&squot; shift */
DECL|member|envelope
r_struct
id|ff_envelope
id|envelope
suffix:semicolon
multiline_comment|/* Only used if waveform == FF_CUSTOM */
DECL|member|custom_len
id|__u32
id|custom_len
suffix:semicolon
multiline_comment|/* Number of samples  */
DECL|member|custom_data
id|__s16
op_star
id|custom_data
suffix:semicolon
multiline_comment|/* Buffer of samples */
multiline_comment|/* Note: the data pointed by custom_data is copied by the driver. You can&n; * therefore dispose of the memory after the upload/update */
)brace
suffix:semicolon
multiline_comment|/* FF_RUMBLE */
multiline_comment|/* Some rumble pads have two motors of different weight.&n;   strong_magnitude represents the magnitude of the vibration generated&n;   by the heavy motor.&n;*/
DECL|struct|ff_rumble_effect
r_struct
id|ff_rumble_effect
(brace
DECL|member|strong_magnitude
id|__u16
id|strong_magnitude
suffix:semicolon
multiline_comment|/* Magnitude of the heavy motor */
DECL|member|weak_magnitude
id|__u16
id|weak_magnitude
suffix:semicolon
multiline_comment|/* Magnitude of the light one */
)brace
suffix:semicolon
multiline_comment|/*&n; * Structure sent through ioctl from the application to the driver&n; */
DECL|struct|ff_effect
r_struct
id|ff_effect
(brace
DECL|member|type
id|__u16
id|type
suffix:semicolon
multiline_comment|/* Following field denotes the unique id assigned to an effect.&n; * If user sets if to -1, a new effect is created, and its id is returned in the same field&n; * Else, the user sets it to the effect id it wants to update.&n; */
DECL|member|id
id|__s16
id|id
suffix:semicolon
DECL|member|direction
id|__u16
id|direction
suffix:semicolon
multiline_comment|/* Direction. 0 deg -&gt; 0x0000 (down)&n;&t;&t;&t;&t;&t;     90 deg -&gt; 0x4000 (left)&n;&t;&t;&t;&t;&t;    180 deg -&gt; 0x8000 (up)&n;&t;&t;&t;&t;&t;    270 deg -&gt; 0xC000 (right)&n;&t;&t;&t;&t;*/
DECL|member|trigger
r_struct
id|ff_trigger
id|trigger
suffix:semicolon
DECL|member|replay
r_struct
id|ff_replay
id|replay
suffix:semicolon
r_union
(brace
DECL|member|constant
r_struct
id|ff_constant_effect
id|constant
suffix:semicolon
DECL|member|ramp
r_struct
id|ff_ramp_effect
id|ramp
suffix:semicolon
DECL|member|periodic
r_struct
id|ff_periodic_effect
id|periodic
suffix:semicolon
DECL|member|condition
r_struct
id|ff_condition_effect
id|condition
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* One for each axis */
DECL|member|rumble
r_struct
id|ff_rumble_effect
id|rumble
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Force feedback effect types&n; */
DECL|macro|FF_RUMBLE
mdefine_line|#define FF_RUMBLE&t;0x50
DECL|macro|FF_PERIODIC
mdefine_line|#define FF_PERIODIC&t;0x51
DECL|macro|FF_CONSTANT
mdefine_line|#define FF_CONSTANT&t;0x52
DECL|macro|FF_SPRING
mdefine_line|#define FF_SPRING&t;0x53
DECL|macro|FF_FRICTION
mdefine_line|#define FF_FRICTION&t;0x54
DECL|macro|FF_DAMPER
mdefine_line|#define FF_DAMPER&t;0x55
DECL|macro|FF_INERTIA
mdefine_line|#define FF_INERTIA&t;0x56
DECL|macro|FF_RAMP
mdefine_line|#define FF_RAMP&t;&t;0x57
multiline_comment|/*&n; * Force feedback periodic effect types&n; */
DECL|macro|FF_SQUARE
mdefine_line|#define FF_SQUARE&t;0x58
DECL|macro|FF_TRIANGLE
mdefine_line|#define FF_TRIANGLE&t;0x59
DECL|macro|FF_SINE
mdefine_line|#define FF_SINE&t;&t;0x5a
DECL|macro|FF_SAW_UP
mdefine_line|#define FF_SAW_UP&t;0x5b
DECL|macro|FF_SAW_DOWN
mdefine_line|#define FF_SAW_DOWN&t;0x5c
DECL|macro|FF_CUSTOM
mdefine_line|#define FF_CUSTOM&t;0x5d
multiline_comment|/*&n; * Set ff device properties&n; */
DECL|macro|FF_GAIN
mdefine_line|#define FF_GAIN&t;&t;0x60
DECL|macro|FF_AUTOCENTER
mdefine_line|#define FF_AUTOCENTER&t;0x61
DECL|macro|FF_MAX
mdefine_line|#define FF_MAX&t;&t;0x7f
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * In-kernel definitions.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
DECL|macro|NBITS
mdefine_line|#define NBITS(x) ((((x)-1)/BITS_PER_LONG)+1)
DECL|macro|BIT
mdefine_line|#define BIT(x)&t;(1UL&lt;&lt;((x)%BITS_PER_LONG))
DECL|macro|LONG
mdefine_line|#define LONG(x) ((x)/BITS_PER_LONG)
DECL|struct|input_dev
r_struct
id|input_dev
(brace
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|phys
r_char
op_star
id|phys
suffix:semicolon
DECL|member|uniq
r_char
op_star
id|uniq
suffix:semicolon
DECL|member|idbus
r_int
r_int
id|idbus
suffix:semicolon
DECL|member|idvendor
r_int
r_int
id|idvendor
suffix:semicolon
DECL|member|idproduct
r_int
r_int
id|idproduct
suffix:semicolon
DECL|member|idversion
r_int
r_int
id|idversion
suffix:semicolon
DECL|member|evbit
r_int
r_int
id|evbit
(braket
id|NBITS
c_func
(paren
id|EV_MAX
)paren
)braket
suffix:semicolon
DECL|member|keybit
r_int
r_int
id|keybit
(braket
id|NBITS
c_func
(paren
id|KEY_MAX
)paren
)braket
suffix:semicolon
DECL|member|relbit
r_int
r_int
id|relbit
(braket
id|NBITS
c_func
(paren
id|REL_MAX
)paren
)braket
suffix:semicolon
DECL|member|absbit
r_int
r_int
id|absbit
(braket
id|NBITS
c_func
(paren
id|ABS_MAX
)paren
)braket
suffix:semicolon
DECL|member|mscbit
r_int
r_int
id|mscbit
(braket
id|NBITS
c_func
(paren
id|MSC_MAX
)paren
)braket
suffix:semicolon
DECL|member|ledbit
r_int
r_int
id|ledbit
(braket
id|NBITS
c_func
(paren
id|LED_MAX
)paren
)braket
suffix:semicolon
DECL|member|sndbit
r_int
r_int
id|sndbit
(braket
id|NBITS
c_func
(paren
id|SND_MAX
)paren
)braket
suffix:semicolon
DECL|member|ffbit
r_int
r_int
id|ffbit
(braket
id|NBITS
c_func
(paren
id|FF_MAX
)paren
)braket
suffix:semicolon
DECL|member|ff_effects_max
r_int
id|ff_effects_max
suffix:semicolon
DECL|member|keycodemax
r_int
r_int
id|keycodemax
suffix:semicolon
DECL|member|keycodesize
r_int
r_int
id|keycodesize
suffix:semicolon
DECL|member|keycode
r_void
op_star
id|keycode
suffix:semicolon
DECL|member|repeat_key
r_int
r_int
id|repeat_key
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|pm_dev
r_struct
id|pm_dev
op_star
id|pm_dev
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|abs
r_int
id|abs
(braket
id|ABS_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|rep
r_int
id|rep
(braket
id|REP_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|key
r_int
r_int
id|key
(braket
id|NBITS
c_func
(paren
id|KEY_MAX
)paren
)braket
suffix:semicolon
DECL|member|led
r_int
r_int
id|led
(braket
id|NBITS
c_func
(paren
id|LED_MAX
)paren
)braket
suffix:semicolon
DECL|member|snd
r_int
r_int
id|snd
(braket
id|NBITS
c_func
(paren
id|SND_MAX
)paren
)braket
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
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|member|accept
r_int
(paren
op_star
id|accept
)paren
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
DECL|member|flush
r_int
(paren
op_star
id|flush
)paren
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
DECL|member|event
r_int
(paren
op_star
id|event
)paren
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_int
r_int
id|code
comma
r_int
id|value
)paren
suffix:semicolon
DECL|member|upload_effect
r_int
(paren
op_star
id|upload_effect
)paren
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_struct
id|ff_effect
op_star
id|effect
)paren
suffix:semicolon
DECL|member|erase_effect
r_int
(paren
op_star
id|erase_effect
)paren
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_int
id|effect_id
)paren
suffix:semicolon
DECL|member|handle
r_struct
id|input_handle
op_star
id|handle
suffix:semicolon
DECL|member|next
r_struct
id|input_dev
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Structure for hotplug &amp; device&lt;-&gt;driver matching.&n; */
DECL|macro|INPUT_DEVICE_ID_MATCH_BUS
mdefine_line|#define INPUT_DEVICE_ID_MATCH_BUS&t;1
DECL|macro|INPUT_DEVICE_ID_MATCH_VENDOR
mdefine_line|#define INPUT_DEVICE_ID_MATCH_VENDOR&t;2
DECL|macro|INPUT_DEVICE_ID_MATCH_PRODUCT
mdefine_line|#define INPUT_DEVICE_ID_MATCH_PRODUCT&t;4
DECL|macro|INPUT_DEVICE_ID_MATCH_VERSION
mdefine_line|#define INPUT_DEVICE_ID_MATCH_VERSION&t;8
DECL|macro|INPUT_DEVICE_ID_MATCH_EVBIT
mdefine_line|#define INPUT_DEVICE_ID_MATCH_EVBIT&t;0x010
DECL|macro|INPUT_DEVICE_ID_MATCH_KEYBIT
mdefine_line|#define INPUT_DEVICE_ID_MATCH_KEYBIT&t;0x020
DECL|macro|INPUT_DEVICE_ID_MATCH_RELBIT
mdefine_line|#define INPUT_DEVICE_ID_MATCH_RELBIT&t;0x040
DECL|macro|INPUT_DEVICE_ID_MATCH_ABSBIT
mdefine_line|#define INPUT_DEVICE_ID_MATCH_ABSBIT&t;0x080
DECL|macro|INPUT_DEVICE_ID_MATCH_MSCIT
mdefine_line|#define INPUT_DEVICE_ID_MATCH_MSCIT&t;0x100
DECL|macro|INPUT_DEVICE_ID_MATCH_LEDBIT
mdefine_line|#define INPUT_DEVICE_ID_MATCH_LEDBIT&t;0x200
DECL|macro|INPUT_DEVICE_ID_MATCH_SNDBIT
mdefine_line|#define INPUT_DEVICE_ID_MATCH_SNDBIT&t;0x400
DECL|macro|INPUT_DEVICE_ID_MATCH_FFBIT
mdefine_line|#define INPUT_DEVICE_ID_MATCH_FFBIT&t;0x800
DECL|macro|INPUT_DEVICE_ID_MATCH_DEVICE
mdefine_line|#define INPUT_DEVICE_ID_MATCH_DEVICE&bslash;&n;&t;(INPUT_DEVICE_ID_MATCH_BUS | INPUT_DEVICE_ID_MATCH_VENDOR | INPUT_DEVICE_ID_MATCH_PRODUCT)
DECL|macro|INPUT_DEVICE_ID_MATCH_DEVICE_AND_VERSION
mdefine_line|#define INPUT_DEVICE_ID_MATCH_DEVICE_AND_VERSION&bslash;&n;&t;(INPUT_DEVICE_ID_MATCH_DEVICE | INPUT_DEVICE_ID_MATCH_VERSION)
DECL|struct|input_device_id
r_struct
id|input_device_id
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|idbus
r_int
r_int
id|idbus
suffix:semicolon
DECL|member|idvendor
r_int
r_int
id|idvendor
suffix:semicolon
DECL|member|idproduct
r_int
r_int
id|idproduct
suffix:semicolon
DECL|member|idversion
r_int
r_int
id|idversion
suffix:semicolon
DECL|member|evbit
r_int
r_int
id|evbit
(braket
id|NBITS
c_func
(paren
id|EV_MAX
)paren
)braket
suffix:semicolon
DECL|member|keybit
r_int
r_int
id|keybit
(braket
id|NBITS
c_func
(paren
id|KEY_MAX
)paren
)braket
suffix:semicolon
DECL|member|relbit
r_int
r_int
id|relbit
(braket
id|NBITS
c_func
(paren
id|REL_MAX
)paren
)braket
suffix:semicolon
DECL|member|absbit
r_int
r_int
id|absbit
(braket
id|NBITS
c_func
(paren
id|ABS_MAX
)paren
)braket
suffix:semicolon
DECL|member|mscbit
r_int
r_int
id|mscbit
(braket
id|NBITS
c_func
(paren
id|MSC_MAX
)paren
)braket
suffix:semicolon
DECL|member|ledbit
r_int
r_int
id|ledbit
(braket
id|NBITS
c_func
(paren
id|LED_MAX
)paren
)braket
suffix:semicolon
DECL|member|sndbit
r_int
r_int
id|sndbit
(braket
id|NBITS
c_func
(paren
id|SND_MAX
)paren
)braket
suffix:semicolon
DECL|member|ffbit
r_int
r_int
id|ffbit
(braket
id|NBITS
c_func
(paren
id|FF_MAX
)paren
)braket
suffix:semicolon
DECL|member|driver_info
r_int
r_int
id|driver_info
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|input_handler
r_struct
id|input_handler
(brace
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
DECL|member|event
r_void
(paren
op_star
id|event
)paren
(paren
r_struct
id|input_handle
op_star
id|handle
comma
r_int
r_int
id|type
comma
r_int
r_int
id|code
comma
r_int
id|value
)paren
suffix:semicolon
DECL|member|connect
r_struct
id|input_handle
op_star
(paren
op_star
id|connect
)paren
(paren
r_struct
id|input_handler
op_star
id|handler
comma
r_struct
id|input_dev
op_star
id|dev
comma
r_struct
id|input_device_id
op_star
id|id
)paren
suffix:semicolon
DECL|member|disconnect
r_void
(paren
op_star
id|disconnect
)paren
(paren
r_struct
id|input_handle
op_star
id|handle
)paren
suffix:semicolon
DECL|member|fops
r_struct
id|file_operations
op_star
id|fops
suffix:semicolon
DECL|member|minor
r_int
id|minor
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|id_table
r_struct
id|input_device_id
op_star
id|id_table
suffix:semicolon
DECL|member|handle
r_struct
id|input_handle
op_star
id|handle
suffix:semicolon
DECL|member|next
r_struct
id|input_handler
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|input_handle
r_struct
id|input_handle
(brace
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
DECL|member|open
r_int
id|open
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|dev
r_struct
id|input_dev
op_star
id|dev
suffix:semicolon
DECL|member|handler
r_struct
id|input_handler
op_star
id|handler
suffix:semicolon
DECL|member|dnext
r_struct
id|input_handle
op_star
id|dnext
suffix:semicolon
DECL|member|hnext
r_struct
id|input_handle
op_star
id|hnext
suffix:semicolon
)brace
suffix:semicolon
r_void
id|input_register_device
c_func
(paren
r_struct
id|input_dev
op_star
)paren
suffix:semicolon
r_void
id|input_unregister_device
c_func
(paren
r_struct
id|input_dev
op_star
)paren
suffix:semicolon
r_void
id|input_register_handler
c_func
(paren
r_struct
id|input_handler
op_star
)paren
suffix:semicolon
r_void
id|input_unregister_handler
c_func
(paren
r_struct
id|input_handler
op_star
)paren
suffix:semicolon
r_int
id|input_open_device
c_func
(paren
r_struct
id|input_handle
op_star
)paren
suffix:semicolon
r_void
id|input_close_device
c_func
(paren
r_struct
id|input_handle
op_star
)paren
suffix:semicolon
r_int
id|input_accept_process
c_func
(paren
r_struct
id|input_handle
op_star
id|handle
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_int
id|input_flush_device
c_func
(paren
r_struct
id|input_handle
op_star
id|handle
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
id|devfs_handle_t
id|input_register_minor
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|minor
comma
r_int
id|minor_base
)paren
suffix:semicolon
r_void
id|input_unregister_minor
c_func
(paren
id|devfs_handle_t
id|handle
)paren
suffix:semicolon
r_void
id|input_event
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_int
r_int
id|code
comma
r_int
id|value
)paren
suffix:semicolon
DECL|macro|input_report_key
mdefine_line|#define input_report_key(a,b,c) input_event(a, EV_KEY, b, !!(c))
DECL|macro|input_report_rel
mdefine_line|#define input_report_rel(a,b,c) input_event(a, EV_REL, b, c)
DECL|macro|input_report_abs
mdefine_line|#define input_report_abs(a,b,c) input_event(a, EV_ABS, b, c)
DECL|macro|input_report_ff
mdefine_line|#define input_report_ff(a,b,c)&t;input_event(a, EV_FF, b, c)
DECL|macro|input_report_ff_status
mdefine_line|#define input_report_ff_status(a,b,c)&t;input_event(a, EV_FF_STATUS, b, c)
macro_line|#endif
macro_line|#endif
eof
