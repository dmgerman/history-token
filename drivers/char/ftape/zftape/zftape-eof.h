macro_line|#ifndef _ZFTAPE_EOF_H
DECL|macro|_ZFTAPE_EOF_H
mdefine_line|#define _ZFTAPE_EOF_H
multiline_comment|/*&n; * Copyright (C) 1994-1995 Bas Laarhoven.&n; * adaptaed for zftape 1996, 1997 by Claus Heine&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/zftape/zftape-eof.h,v $&n; * $Revision: 1.2 $&n; * $Date: 1997/10/05 19:19:03 $&n; *&n; *      Definitions and declarations for the end of file markers&n; *      for the QIC-40/80 floppy-tape driver for Linux.&n; */
macro_line|#include &lt;linux/ftape-header-segment.h&gt;
macro_line|#include &quot;../zftape/zftape-buffers.h&quot;
multiline_comment|/*  failed sector log size (only used if format code != 4).&n; */
r_typedef
r_union
(brace
DECL|member|mark
id|ft_fsl_entry
id|mark
suffix:semicolon
DECL|member|entry
id|__u32
id|entry
suffix:semicolon
DECL|typedef|eof_mark_union
)brace
id|eof_mark_union
suffix:semicolon
multiline_comment|/*      ftape-eof.c defined global vars.&n; */
r_extern
r_int
id|zft_nr_eof_marks
suffix:semicolon
r_extern
id|eof_mark_union
op_star
id|zft_eof_map
suffix:semicolon
multiline_comment|/*      ftape-eof.c defined global functions.&n; */
r_extern
r_void
id|zft_ftape_extract_file_marks
c_func
(paren
id|__u8
op_star
id|address
)paren
suffix:semicolon
r_extern
r_int
id|zft_ftape_validate_label
c_func
(paren
r_char
op_star
id|label
)paren
suffix:semicolon
r_extern
r_void
id|zft_clear_ftape_file_marks
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
