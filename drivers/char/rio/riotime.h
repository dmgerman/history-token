multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******            T I M E&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Jeremy Rolls&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n;&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef _riotime_h
DECL|macro|_riotime_h
mdefine_line|#define _riotime_h 1
macro_line|#ifndef lint
macro_line|#ifdef SCCS
DECL|variable|_rio_riotime_h_sccs
r_static
r_char
op_star
id|_rio_riotime_h_sccs
op_assign
l_string|&quot;@(#)riotime.h&t;1.1&quot;
suffix:semicolon
macro_line|#endif
macro_line|#endif
DECL|macro|TWO_POWER_FIFTEEN
mdefine_line|#define TWO_POWER_FIFTEEN (ushort)32768
DECL|macro|RioTime
mdefine_line|#define RioTime()    riotime
DECL|macro|RioTimeAfter
mdefine_line|#define RioTimeAfter(time1,time2) ((ushort)time1 - (ushort)time2) &lt; TWO_POWER_FIFTEEN
DECL|macro|RioTimePlus
mdefine_line|#define RioTimePlus(time1,time2) ((ushort)time1 + (ushort)time2)
multiline_comment|/**************************************&n; * Convert a RIO tick (1/10th second)&n; * into transputer low priority ticks&n; *************************************/
DECL|macro|RioTimeToLow
mdefine_line|#define RioTimeToLow(time) (time*(100000 / 64))
DECL|macro|RioLowToTime
mdefine_line|#define RioLowToTime(time) ((time*64)/100000)
DECL|macro|RIOTENTHSECOND
mdefine_line|#define RIOTENTHSECOND (ushort)1
DECL|macro|RIOSECOND
mdefine_line|#define RIOSECOND (ushort)(RIOTENTHSECOND * 10)
macro_line|#endif
multiline_comment|/*********** end of file ***********/
eof
