multiline_comment|/* drivers/char/ser_a2232.h */
multiline_comment|/* $Id: ser_a2232.h,v 0.4 2000/01/25 12:00:00 ehaase Exp $ */
multiline_comment|/* Linux serial driver for the Amiga A2232 board */
multiline_comment|/* This driver is MAINTAINED. Before applying any changes, please contact&n; * the author.&n; */
multiline_comment|/* Copyright (c) 2000-2001 Enver Haase    &lt;ehaase@inf.fu-berlin.de&gt;&n; *                   alias The A2232 driver project &lt;A2232@gmx.net&gt;&n; * All rights reserved.&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *  &n; */
macro_line|#ifndef _SER_A2232_H_
DECL|macro|_SER_A2232_H_
mdefine_line|#define _SER_A2232_H_
multiline_comment|/*&n;&t;How many boards are to be supported at maximum;&n;&t;&quot;up to five A2232 Multiport Serial Cards may be installed in a&n;&t;single Amiga 2000&quot; states the A2232 User&squot;s Guide. If you have&n;&t;more slots available, you might want to change the value below.&n;*/
DECL|macro|MAX_A2232_BOARDS
mdefine_line|#define MAX_A2232_BOARDS 5
macro_line|#ifndef A2232_NORMAL_MAJOR
multiline_comment|/* This allows overriding on the compiler commandline, or in a &quot;major.h&quot; &n;   include or something like that */
DECL|macro|A2232_NORMAL_MAJOR
mdefine_line|#define A2232_NORMAL_MAJOR  224&t;/* /dev/ttyY* */
DECL|macro|A2232_CALLOUT_MAJOR
mdefine_line|#define A2232_CALLOUT_MAJOR 225&t;/* /dev/cuy*  */
macro_line|#endif
multiline_comment|/* Some magic is always good - Who knows :) */
DECL|macro|A2232_MAGIC
mdefine_line|#define A2232_MAGIC 0x000a2232
multiline_comment|/* for the tty_struct subtype field */
DECL|macro|A2232_TTY_SUBTYPE_NORMAL
mdefine_line|#define A2232_TTY_SUBTYPE_NORMAL&t;1
DECL|macro|A2232_TTY_SUBTYPE_CALLOUT
mdefine_line|#define A2232_TTY_SUBTYPE_CALLOUT&t;2
multiline_comment|/* A2232 port structure to keep track of the&n;   status of every single line used */
DECL|struct|a2232_port
r_struct
id|a2232_port
(brace
DECL|member|gs
r_struct
id|gs_port
id|gs
suffix:semicolon
DECL|member|which_a2232
r_int
r_int
id|which_a2232
suffix:semicolon
DECL|member|which_port_on_a2232
r_int
r_int
id|which_port_on_a2232
suffix:semicolon
DECL|member|disable_rx
r_int
id|disable_rx
suffix:semicolon
DECL|member|throttle_input
r_int
id|throttle_input
suffix:semicolon
DECL|member|cd_status
r_int
id|cd_status
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NUMLINES
mdefine_line|#define&t;NUMLINES&t;&t;7&t;/* number of lines per board */
DECL|macro|A2232_IOBUFLEN
mdefine_line|#define&t;A2232_IOBUFLEN&t;&t;256&t;/* number of bytes per buffer */
DECL|macro|A2232_IOBUFLENMASK
mdefine_line|#define&t;A2232_IOBUFLENMASK&t;0xff&t;/* mask for maximum number of bytes */
DECL|macro|A2232_UNKNOWN
mdefine_line|#define&t;A2232_UNKNOWN&t;0&t;/* crystal not known */
DECL|macro|A2232_NORMAL
mdefine_line|#define&t;A2232_NORMAL&t;1&t;/* normal A2232 (1.8432 MHz oscillator) */
DECL|macro|A2232_TURBO
mdefine_line|#define&t;A2232_TURBO&t;2&t;/* turbo A2232 (3.6864 MHz oscillator) */
DECL|struct|a2232common
r_struct
id|a2232common
(brace
DECL|member|Crystal
r_char
id|Crystal
suffix:semicolon
multiline_comment|/* normal (1) or turbo (2) board? */
DECL|member|Pad_a
id|u_char
id|Pad_a
suffix:semicolon
DECL|member|TimerH
id|u_char
id|TimerH
suffix:semicolon
multiline_comment|/* timer value after speed check */
DECL|member|TimerL
id|u_char
id|TimerL
suffix:semicolon
DECL|member|CDHead
id|u_char
id|CDHead
suffix:semicolon
multiline_comment|/* head pointer for CD message queue */
DECL|member|CDTail
id|u_char
id|CDTail
suffix:semicolon
multiline_comment|/* tail pointer for CD message queue */
DECL|member|CDStatus
id|u_char
id|CDStatus
suffix:semicolon
DECL|member|Pad_b
id|u_char
id|Pad_b
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|a2232status
r_struct
id|a2232status
(brace
DECL|member|InHead
id|u_char
id|InHead
suffix:semicolon
multiline_comment|/* input queue head */
DECL|member|InTail
id|u_char
id|InTail
suffix:semicolon
multiline_comment|/* input queue tail */
DECL|member|OutDisable
id|u_char
id|OutDisable
suffix:semicolon
multiline_comment|/* disables output */
DECL|member|OutHead
id|u_char
id|OutHead
suffix:semicolon
multiline_comment|/* output queue head */
DECL|member|OutTail
id|u_char
id|OutTail
suffix:semicolon
multiline_comment|/* output queue tail */
DECL|member|OutCtrl
id|u_char
id|OutCtrl
suffix:semicolon
multiline_comment|/* soft flow control character to send */
DECL|member|OutFlush
id|u_char
id|OutFlush
suffix:semicolon
multiline_comment|/* flushes output buffer */
DECL|member|Setup
id|u_char
id|Setup
suffix:semicolon
multiline_comment|/* causes reconfiguration */
DECL|member|Param
id|u_char
id|Param
suffix:semicolon
multiline_comment|/* parameter byte - see A2232PARAM */
DECL|member|Command
id|u_char
id|Command
suffix:semicolon
multiline_comment|/* command byte - see A2232CMD */
DECL|member|SoftFlow
id|u_char
id|SoftFlow
suffix:semicolon
multiline_comment|/* enables xon/xoff flow control */
multiline_comment|/* private 65EC02 fields: */
DECL|member|XonOff
id|u_char
id|XonOff
suffix:semicolon
multiline_comment|/* stores XON/XOFF enable/disable */
)brace
suffix:semicolon
DECL|macro|A2232_MEMPAD1
mdefine_line|#define&t;A2232_MEMPAD1&t;&bslash;&n;&t;(0x0200 - NUMLINES * sizeof(struct a2232status)&t;-&t;&bslash;&n;&t;sizeof(struct a2232common))
DECL|macro|A2232_MEMPAD2
mdefine_line|#define&t;A2232_MEMPAD2&t;(0x2000 - NUMLINES * A2232_IOBUFLEN - A2232_IOBUFLEN)
DECL|struct|a2232memory
r_struct
id|a2232memory
(brace
DECL|member|Status
r_struct
id|a2232status
id|Status
(braket
id|NUMLINES
)braket
suffix:semicolon
multiline_comment|/* 0x0000-0x006f status areas */
DECL|member|Common
r_struct
id|a2232common
id|Common
suffix:semicolon
multiline_comment|/* 0x0070-0x0077 common flags */
DECL|member|Dummy1
id|u_char
id|Dummy1
(braket
id|A2232_MEMPAD1
)braket
suffix:semicolon
multiline_comment|/* 0x00XX-0x01ff */
DECL|member|OutBuf
id|u_char
id|OutBuf
(braket
id|NUMLINES
)braket
(braket
id|A2232_IOBUFLEN
)braket
suffix:semicolon
multiline_comment|/* 0x0200-0x08ff output bufs */
DECL|member|InBuf
id|u_char
id|InBuf
(braket
id|NUMLINES
)braket
(braket
id|A2232_IOBUFLEN
)braket
suffix:semicolon
multiline_comment|/* 0x0900-0x0fff input bufs */
DECL|member|InCtl
id|u_char
id|InCtl
(braket
id|NUMLINES
)braket
(braket
id|A2232_IOBUFLEN
)braket
suffix:semicolon
multiline_comment|/* 0x1000-0x16ff control data */
DECL|member|CDBuf
id|u_char
id|CDBuf
(braket
id|A2232_IOBUFLEN
)braket
suffix:semicolon
multiline_comment|/* 0x1700-0x17ff CD event buffer */
DECL|member|Dummy2
id|u_char
id|Dummy2
(braket
id|A2232_MEMPAD2
)braket
suffix:semicolon
multiline_comment|/* 0x1800-0x2fff */
DECL|member|Code
id|u_char
id|Code
(braket
l_int|0x1000
)braket
suffix:semicolon
multiline_comment|/* 0x3000-0x3fff code area */
DECL|member|InterruptAck
id|u_short
id|InterruptAck
suffix:semicolon
multiline_comment|/* 0x4000        intr ack */
DECL|member|Dummy3
id|u_char
id|Dummy3
(braket
l_int|0x3ffe
)braket
suffix:semicolon
multiline_comment|/* 0x4002-0x7fff */
DECL|member|Enable6502Reset
id|u_short
id|Enable6502Reset
suffix:semicolon
multiline_comment|/* 0x8000 Stop board, */
multiline_comment|/*  6502 RESET line held low */
DECL|member|Dummy4
id|u_char
id|Dummy4
(braket
l_int|0x3ffe
)braket
suffix:semicolon
multiline_comment|/* 0x8002-0xbfff */
DECL|member|ResetBoard
id|u_short
id|ResetBoard
suffix:semicolon
multiline_comment|/* 0xc000 reset board &amp; run, */
multiline_comment|/*  6502 RESET line held high */
)brace
suffix:semicolon
DECL|macro|A2232_MEMPAD1
macro_line|#undef A2232_MEMPAD1
DECL|macro|A2232_MEMPAD2
macro_line|#undef A2232_MEMPAD2
DECL|macro|A2232INCTL_CHAR
mdefine_line|#define&t;A2232INCTL_CHAR&t;&t;0&t;/* corresponding byte in InBuf is a character */
DECL|macro|A2232INCTL_EVENT
mdefine_line|#define&t;A2232INCTL_EVENT&t;1&t;/* corresponding byte in InBuf is an event */
DECL|macro|A2232EVENT_Break
mdefine_line|#define&t;A2232EVENT_Break&t;1&t;/* break set */
DECL|macro|A2232EVENT_CarrierOn
mdefine_line|#define&t;A2232EVENT_CarrierOn&t;2&t;/* carrier raised */
DECL|macro|A2232EVENT_CarrierOff
mdefine_line|#define&t;A2232EVENT_CarrierOff&t;3&t;/* carrier dropped */
DECL|macro|A2232EVENT_Sync
mdefine_line|#define A2232EVENT_Sync&t;&t;4&t;/* don&squot;t know, defined in 2232.ax */
DECL|macro|A2232CMD_Enable
mdefine_line|#define&t;A2232CMD_Enable&t;&t;0x1&t;/* enable/DTR bit */
DECL|macro|A2232CMD_Close
mdefine_line|#define&t;A2232CMD_Close&t;&t;0x2&t;/* close the device */
DECL|macro|A2232CMD_Open
mdefine_line|#define&t;A2232CMD_Open&t;&t;0xb&t;/* open the device */
DECL|macro|A2232CMD_CMask
mdefine_line|#define&t;A2232CMD_CMask&t;&t;0xf&t;/* command mask */
DECL|macro|A2232CMD_RTSOff
mdefine_line|#define&t;A2232CMD_RTSOff&t;&t;0x0  &t;/* turn off RTS */
DECL|macro|A2232CMD_RTSOn
mdefine_line|#define&t;A2232CMD_RTSOn&t;&t;0x8&t;/* turn on RTS */
DECL|macro|A2232CMD_Break
mdefine_line|#define&t;A2232CMD_Break&t;&t;0xd&t;/* transmit a break */
DECL|macro|A2232CMD_RTSMask
mdefine_line|#define&t;A2232CMD_RTSMask&t;0xc&t;/* mask for RTS stuff */
DECL|macro|A2232CMD_NoParity
mdefine_line|#define&t;A2232CMD_NoParity&t;0x00&t;/* don&squot;t use parity */
DECL|macro|A2232CMD_OddParity
mdefine_line|#define&t;A2232CMD_OddParity&t;0x20&t;/* odd parity */
DECL|macro|A2232CMD_EvenParity
mdefine_line|#define&t;A2232CMD_EvenParity&t;0x60&t;/* even parity */
DECL|macro|A2232CMD_ParityMask
mdefine_line|#define&t;A2232CMD_ParityMask&t;0xe0&t;/* parity mask */
DECL|macro|A2232PARAM_B115200
mdefine_line|#define&t;A2232PARAM_B115200&t;0x0&t;/* baud rates */
DECL|macro|A2232PARAM_B50
mdefine_line|#define&t;A2232PARAM_B50&t;&t;0x1
DECL|macro|A2232PARAM_B75
mdefine_line|#define&t;A2232PARAM_B75&t;&t;0x2
DECL|macro|A2232PARAM_B110
mdefine_line|#define&t;A2232PARAM_B110&t;&t;0x3
DECL|macro|A2232PARAM_B134
mdefine_line|#define&t;A2232PARAM_B134&t;&t;0x4
DECL|macro|A2232PARAM_B150
mdefine_line|#define&t;A2232PARAM_B150&t;&t;0x5
DECL|macro|A2232PARAM_B300
mdefine_line|#define&t;A2232PARAM_B300&t;&t;0x6
DECL|macro|A2232PARAM_B600
mdefine_line|#define&t;A2232PARAM_B600&t;&t;0x7
DECL|macro|A2232PARAM_B1200
mdefine_line|#define&t;A2232PARAM_B1200&t;0x8
DECL|macro|A2232PARAM_B1800
mdefine_line|#define&t;A2232PARAM_B1800&t;0x9
DECL|macro|A2232PARAM_B2400
mdefine_line|#define&t;A2232PARAM_B2400&t;0xa
DECL|macro|A2232PARAM_B3600
mdefine_line|#define&t;A2232PARAM_B3600&t;0xb
DECL|macro|A2232PARAM_B4800
mdefine_line|#define&t;A2232PARAM_B4800&t;0xc
DECL|macro|A2232PARAM_B7200
mdefine_line|#define&t;A2232PARAM_B7200&t;0xd
DECL|macro|A2232PARAM_B9600
mdefine_line|#define&t;A2232PARAM_B9600&t;0xe
DECL|macro|A2232PARAM_B19200
mdefine_line|#define&t;A2232PARAM_B19200&t;0xf
DECL|macro|A2232PARAM_BaudMask
mdefine_line|#define&t;A2232PARAM_BaudMask&t;0xf&t;/* baud rate mask */
DECL|macro|A2232PARAM_RcvBaud
mdefine_line|#define&t;A2232PARAM_RcvBaud&t;0x10&t;/* enable receive baud rate */
DECL|macro|A2232PARAM_8Bit
mdefine_line|#define&t;A2232PARAM_8Bit&t;&t;0x00&t;/* numbers of bits */
DECL|macro|A2232PARAM_7Bit
mdefine_line|#define&t;A2232PARAM_7Bit&t;&t;0x20
DECL|macro|A2232PARAM_6Bit
mdefine_line|#define&t;A2232PARAM_6Bit&t;&t;0x40
DECL|macro|A2232PARAM_5Bit
mdefine_line|#define&t;A2232PARAM_5Bit&t;&t;0x60
DECL|macro|A2232PARAM_BitMask
mdefine_line|#define&t;A2232PARAM_BitMask&t;0x60&t;/* numbers of bits mask */
multiline_comment|/* Standard speeds tables, -1 means unavailable, -2 means 0 baud: switch off line */
DECL|macro|A2232_BAUD_TABLE_NOAVAIL
mdefine_line|#define A2232_BAUD_TABLE_NOAVAIL -1
DECL|macro|A2232_BAUD_TABLE_NUM_RATES
mdefine_line|#define A2232_BAUD_TABLE_NUM_RATES (18)
DECL|variable|a2232_baud_table
r_static
r_int
id|a2232_baud_table
(braket
id|A2232_BAUD_TABLE_NUM_RATES
op_star
l_int|3
)braket
op_assign
(brace
singleline_comment|//Baud&t;//Normal&t;&t;&t;//Turbo
l_int|50
comma
id|A2232PARAM_B50
comma
id|A2232_BAUD_TABLE_NOAVAIL
comma
l_int|75
comma
id|A2232PARAM_B75
comma
id|A2232_BAUD_TABLE_NOAVAIL
comma
l_int|110
comma
id|A2232PARAM_B110
comma
id|A2232_BAUD_TABLE_NOAVAIL
comma
l_int|134
comma
id|A2232PARAM_B134
comma
id|A2232_BAUD_TABLE_NOAVAIL
comma
l_int|150
comma
id|A2232PARAM_B150
comma
id|A2232PARAM_B75
comma
l_int|200
comma
id|A2232_BAUD_TABLE_NOAVAIL
comma
id|A2232_BAUD_TABLE_NOAVAIL
comma
l_int|300
comma
id|A2232PARAM_B300
comma
id|A2232PARAM_B150
comma
l_int|600
comma
id|A2232PARAM_B600
comma
id|A2232PARAM_B300
comma
l_int|1200
comma
id|A2232PARAM_B1200
comma
id|A2232PARAM_B600
comma
l_int|1800
comma
id|A2232PARAM_B1800
comma
id|A2232_BAUD_TABLE_NOAVAIL
comma
l_int|2400
comma
id|A2232PARAM_B2400
comma
id|A2232PARAM_B1200
comma
l_int|4800
comma
id|A2232PARAM_B4800
comma
id|A2232PARAM_B2400
comma
l_int|9600
comma
id|A2232PARAM_B9600
comma
id|A2232PARAM_B4800
comma
l_int|19200
comma
id|A2232PARAM_B19200
comma
id|A2232PARAM_B9600
comma
l_int|38400
comma
id|A2232_BAUD_TABLE_NOAVAIL
comma
id|A2232PARAM_B19200
comma
l_int|57600
comma
id|A2232_BAUD_TABLE_NOAVAIL
comma
id|A2232_BAUD_TABLE_NOAVAIL
comma
macro_line|#ifdef A2232_SPEEDHACK
l_int|115200
comma
id|A2232PARAM_B115200
comma
id|A2232_BAUD_TABLE_NOAVAIL
comma
l_int|230400
comma
id|A2232_BAUD_TABLE_NOAVAIL
comma
id|A2232PARAM_B115200
macro_line|#else
l_int|115200
comma
id|A2232_BAUD_TABLE_NOAVAIL
comma
id|A2232_BAUD_TABLE_NOAVAIL
comma
l_int|230400
comma
id|A2232_BAUD_TABLE_NOAVAIL
comma
id|A2232_BAUD_TABLE_NOAVAIL
macro_line|#endif
)brace
suffix:semicolon
macro_line|#endif
eof
