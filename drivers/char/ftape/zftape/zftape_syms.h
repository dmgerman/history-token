macro_line|#ifndef _ZFTAPE_SYMS_H
DECL|macro|_ZFTAPE_SYMS_H
mdefine_line|#define _ZFTAPE_SYMS_H
multiline_comment|/*&n; * Copyright (C) 1996, 1997 Claus-Justus Heine&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/zftape/zftape_syms.h,v $&n; * $Revision: 1.2 $&n; * $Date: 1997/10/05 19:19:14 $&n; *&n; *      This file contains the definitions needed for the symbols&n; *      ftape exports&n; * &n; */
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VER(2,1,18)
macro_line|#include &lt;linux/module.h&gt;
multiline_comment|/*      ftape-vfs.c defined global vars.&n; */
r_extern
r_struct
id|symbol_table
id|zft_symbol_table
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
