macro_line|#ifndef _ZFTAPE_READ_H
DECL|macro|_ZFTAPE_READ_H
mdefine_line|#define _ZFTAPE_READ_H
multiline_comment|/*&n; * Copyright (C) 1996, 1997 Claus-Justus Heine&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/zftape/zftape-read.h,v $&n; * $Revision: 1.2 $&n; * $Date: 1997/10/05 19:19:07 $&n; *&n; *      This file contains the definitions for the read functions&n; *      for the zftape driver for Linux.&n; *&n; */
macro_line|#include &quot;../lowlevel/ftape-read.h&quot;
multiline_comment|/*      ftape-read.c defined global vars.&n; */
r_extern
r_int
id|zft_just_before_eof
suffix:semicolon
multiline_comment|/*      ftape-read.c defined global functions.&n; */
r_extern
r_void
id|zft_zap_read_buffers
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|zft_read_header_segments
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|zft_fetch_segment_fraction
c_func
(paren
r_const
r_int
r_int
id|segment
comma
r_void
op_star
id|buffer
comma
r_const
id|ft_read_mode_t
id|read_mode
comma
r_const
r_int
r_int
id|start
comma
r_const
r_int
r_int
id|size
)paren
suffix:semicolon
DECL|macro|zft_fetch_segment
mdefine_line|#define zft_fetch_segment(segment, address, read_mode)&t;&t;&bslash;&n;&t;zft_fetch_segment_fraction(segment, address, read_mode,&t;&bslash;&n;&t;&t;&t;&t;   0, FT_SEGMENT_SIZE)
multiline_comment|/*   hook for the VFS interface&n; */
r_extern
r_int
id|_zft_read
c_func
(paren
r_char
op_star
id|buff
comma
r_int
id|req_len
)paren
suffix:semicolon
macro_line|#endif /* _ZFTAPE_READ_H */
eof
