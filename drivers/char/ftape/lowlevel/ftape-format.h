macro_line|#ifndef _FTAPE_FORMAT_H
DECL|macro|_FTAPE_FORMAT_H
mdefine_line|#define _FTAPE_FORMAT_H
multiline_comment|/*&n; * Copyright (C) 1996-1997 Claus-Justus Heine.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/lowlevel/ftape-format.h,v $&n; * $Revision: 1.2 $&n; * $Date: 1997/10/05 19:18:13 $&n; *&n; *      This file contains the low level definitions for the&n; *      formatting support for the QIC-40/80/3010/3020 floppy-tape&n; *      driver &quot;ftape&quot; for Linux.&n; */
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|ftape_format_track
c_func
(paren
r_const
r_int
r_int
id|track
comma
r_const
id|__u8
id|gap3
)paren
suffix:semicolon
r_extern
r_int
id|ftape_format_status
c_func
(paren
r_int
r_int
op_star
id|segment_id
)paren
suffix:semicolon
r_extern
r_int
id|ftape_verify_segment
c_func
(paren
r_const
r_int
r_int
id|segment_id
comma
id|SectorMap
op_star
id|bsm
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
