macro_line|#ifndef _ZFTAPE_WRITE_H
DECL|macro|_ZFTAPE_WRITE_H
mdefine_line|#define _ZFTAPE_WRITE_H
multiline_comment|/*&n; * Copyright (C) 1996, 1997 Claus-Justus Heine&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/zftape/zftape-write.h,v $&n; * $Revision: 1.2 $&n; * $Date: 1997/10/05 19:19:13 $&n; *&n; *      This file contains the definitions for the write functions&n; *      for the zftape driver for Linux.&n; *&n; */
r_extern
r_int
id|zft_flush_buffers
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|zft_update_header_segments
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|zft_prevent_flush
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*  hook for the VFS interface &n; */
r_extern
r_int
id|_zft_write
c_func
(paren
r_const
r_char
op_star
id|buff
comma
r_int
id|req_len
)paren
suffix:semicolon
macro_line|#endif /* _ZFTAPE_WRITE_H */
eof
