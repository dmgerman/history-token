macro_line|#ifndef _FTAPE_WRITE_H
DECL|macro|_FTAPE_WRITE_H
mdefine_line|#define _FTAPE_WRITE_H
multiline_comment|/*&n; * Copyright (C) 1994-1995 Bas Laarhoven,&n; *           (C) 1996-1997 Claus-Justus Heine.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; $Source: /homes/cvs/ftape-stacked/ftape/lowlevel/ftape-write.h,v $&n; $Author: claus $&n; *&n; $Revision: 1.2 $&n; $Date: 1997/10/05 19:18:30 $&n; $State: Exp $&n; *&n; *      This file contains the definitions for the write functions&n; *      for the QIC-117 floppy-tape driver for Linux.&n; *&n; */
multiline_comment|/*      ftape-write.c defined global functions.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|FT_WR_ASYNC
id|FT_WR_ASYNC
op_assign
l_int|0
comma
multiline_comment|/* start tape only when all buffers are full */
DECL|enumerator|FT_WR_MULTI
id|FT_WR_MULTI
op_assign
l_int|1
comma
multiline_comment|/* start tape, but don&squot;t necessarily stop */
DECL|enumerator|FT_WR_SINGLE
id|FT_WR_SINGLE
op_assign
l_int|2
comma
multiline_comment|/* write a single segment and stop afterwards */
DECL|enumerator|FT_WR_DELETE
id|FT_WR_DELETE
op_assign
l_int|3
multiline_comment|/* write deleted data marks */
DECL|typedef|ft_write_mode_t
)brace
id|ft_write_mode_t
suffix:semicolon
r_extern
r_int
id|ftape_start_writing
c_func
(paren
r_const
id|ft_write_mode_t
id|mode
)paren
suffix:semicolon
r_extern
r_int
id|ftape_write_segment
c_func
(paren
r_const
r_int
id|segment
comma
r_const
r_void
op_star
id|address
comma
r_const
id|ft_write_mode_t
id|flushing
)paren
suffix:semicolon
r_extern
r_void
id|ftape_zap_write_buffers
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ftape_loop_until_writes_done
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _FTAPE_WRITE_H */
eof
