multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******&t;&t;BRATES.H&t;&t;&t;&t;      *******&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Jeremy Rolls&n; Date    : 1 Nov 1990&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef _brates_h
macro_line|#ifndef lint
multiline_comment|/* static char * _brates_h_sccs = &quot;@(#)brates.h&t;1.4&quot;; */
macro_line|#endif
DECL|macro|_brates_h
mdefine_line|#define _brates_h 1
multiline_comment|/* List of baud rate defines. Most are borrowed from /usr/include/sys/termio.h&n;*/
macro_line|#ifndef INKERNEL
DECL|macro|B0
mdefine_line|#define&t;B0&t;0x00
DECL|macro|B50
mdefine_line|#define&t;B50&t;0x01
DECL|macro|B75
mdefine_line|#define&t;B75&t;0x02
DECL|macro|B110
mdefine_line|#define&t;B110&t;0x03
DECL|macro|B134
mdefine_line|#define&t;B134&t;0x04
DECL|macro|B150
mdefine_line|#define&t;B150&t;0x05
DECL|macro|B200
mdefine_line|#define&t;B200&t;0x06
DECL|macro|B300
mdefine_line|#define&t;B300&t;0x07
DECL|macro|B600
mdefine_line|#define&t;B600&t;0x08
DECL|macro|B1200
mdefine_line|#define&t;B1200&t;0x09
DECL|macro|B1800
mdefine_line|#define&t;B1800&t;0x0a
DECL|macro|B2400
mdefine_line|#define&t;B2400&t;0x0b
DECL|macro|B4800
mdefine_line|#define&t;B4800&t;0x0c
DECL|macro|B9600
mdefine_line|#define&t;B9600&t;0x0d
DECL|macro|B19200
mdefine_line|#define&t;B19200&t;0x0e
DECL|macro|B38400
mdefine_line|#define&t;B38400&t;0x0f
macro_line|#endif
multiline_comment|/*&n;** The following baudrates may or may not be defined&n;** on various UNIX systems.&n;** If they are not then we define them.&n;** If they are then we do not define them ;-)&n;**&n;** This is appalling that we use same definitions as UNIX&n;** for our own download code as there is no garuntee that&n;** B57600 will be defined as 0x11 by a UNIX system....&n;** Arghhhhh!!!!!!!!!!!!!!&n;*/
macro_line|#if !defined(B56000)
DECL|macro|B56000
mdefine_line|#define&t;B56000&t;0x10
macro_line|#endif
macro_line|#if !defined(B57600)
DECL|macro|B57600
mdefine_line|#define&t;B57600&t;0x11
macro_line|#endif
macro_line|#if !defined(B64000)
DECL|macro|B64000
mdefine_line|#define&t;B64000&t;0x12
macro_line|#endif
macro_line|#if !defined(B115200)
DECL|macro|B115200
mdefine_line|#define&t;B115200&t;0x13
macro_line|#endif
macro_line|#if !defined(B2000)
DECL|macro|B2000
mdefine_line|#define B2000&t;0x14
macro_line|#endif
DECL|macro|MAX_RATE
mdefine_line|#define MAX_RATE B2000
DECL|struct|baud_rate
r_struct
id|baud_rate
multiline_comment|/* Tag for baud rates */
(brace
multiline_comment|/* short    host_rate,*/
multiline_comment|/* As passed by the driver */
DECL|member|divisor
r_int
id|divisor
comma
multiline_comment|/* The divisor */
DECL|member|prescaler
id|prescaler
suffix:semicolon
multiline_comment|/* The pre-scaler */
)brace
suffix:semicolon
macro_line|#endif
eof
