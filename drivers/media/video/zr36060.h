multiline_comment|/* &n;   zr36060.h - zr36060 register offsets&n;&n;   Copyright (C) 1998 Dave Perks &lt;dperks@ibm.net&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _ZR36060_H_
DECL|macro|_ZR36060_H_
mdefine_line|#define _ZR36060_H_
multiline_comment|/* Zoran ZR36060 registers */
DECL|macro|ZR36060_LoadParameters
mdefine_line|#define ZR36060_LoadParameters  &t;0x000
DECL|macro|ZR36060_Load
mdefine_line|#define ZR36060_Load                    (1&lt;&lt;7)
DECL|macro|ZR36060_SyncRst
mdefine_line|#define ZR36060_SyncRst                 (1&lt;&lt;0)
DECL|macro|ZR36060_CodeFifoStatus
mdefine_line|#define ZR36060_CodeFifoStatus  &t;0x001
DECL|macro|ZR36060_Load
mdefine_line|#define ZR36060_Load                    (1&lt;&lt;7)
DECL|macro|ZR36060_SyncRst
mdefine_line|#define ZR36060_SyncRst                 (1&lt;&lt;0)
macro_line|#endif
eof
