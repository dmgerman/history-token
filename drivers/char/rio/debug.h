multiline_comment|/*&n;** File:&t;&t;debug.h&n;**&n;** Author:&t;&t;David Dix&n;**&n;** Created:&t;&t;12th March 1993&n;**&n;** Last modified:&t;93/04/27&n;**&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef _debug_h_
DECL|macro|_debug_h_
mdefine_line|#define _debug_h_
macro_line|#if defined(DCIRRUS)
DECL|macro|DBPACKET
mdefine_line|#define&t;DBPACKET(pkt, opt, str, chn) &t;debug_packet((pkt), (opt), (str), (chn))
macro_line|#else
DECL|macro|DBPACKET
mdefine_line|#define&t;DBPACKET(pkt, opt, str, c)
macro_line|#endif&t;/* DCIRRUS */
macro_line|#endif&t;/* _debug_h_ */
eof
