macro_line|#ifndef _FTAPE_INIT_H
DECL|macro|_FTAPE_INIT_H
mdefine_line|#define _FTAPE_INIT_H
multiline_comment|/*&n; * Copyright (C) 1993-1996 Bas Laarhoven,&n; *           (C) 1996-1997 Claus-Justus Heine.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/lowlevel/ftape-init.h,v $&n; * $Revision: 1.2 $&n; * $Date: 1997/10/05 19:18:16 $&n; *&n; * This file contains the definitions for the interface to &n; * the Linux kernel for floppy tape driver ftape.&n; *&n; */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
DECL|macro|_NEVER_BLOCK
mdefine_line|#define _NEVER_BLOCK    (sigmask(SIGKILL) | sigmask(SIGSTOP))
DECL|macro|_DONT_BLOCK
mdefine_line|#define _DONT_BLOCK     (_NEVER_BLOCK | sigmask(SIGINT))
DECL|macro|_DO_BLOCK
mdefine_line|#define _DO_BLOCK       (sigmask(SIGPIPE))
macro_line|#ifndef QIC117_TAPE_MAJOR
DECL|macro|QIC117_TAPE_MAJOR
mdefine_line|#define QIC117_TAPE_MAJOR 27
macro_line|#endif
multiline_comment|/*      ftape-init.c defined global variables.&n; */
multiline_comment|/*      ftape-init.c defined global functions not defined in ftape.h&n; */
macro_line|#ifdef MODULE
id|asmlinkage
r_extern
r_int
id|init_module
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_extern
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
