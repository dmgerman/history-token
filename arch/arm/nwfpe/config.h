multiline_comment|/*&n;    NetWinder Floating Point Emulator&n;    (c) Rebel.com, 1998-1999&n;&n;    Direct questions, comments to Scott Bambrough &lt;scottb@netwinder.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef __CONFIG_H__
DECL|macro|__CONFIG_H__
mdefine_line|#define __CONFIG_H__
macro_line|#if 1
DECL|macro|C_SYMBOL_NAME
mdefine_line|#define C_SYMBOL_NAME(foo)&t;foo
macro_line|#else
DECL|macro|C_SYMBOL_NAME
mdefine_line|#define C_SYMBOL_NAME(foo)&t;_##foo
macro_line|#endif
macro_line|#endif
eof
