macro_line|#ifndef _FTAPE_BSM_H
DECL|macro|_FTAPE_BSM_H
mdefine_line|#define _FTAPE_BSM_H
multiline_comment|/*&n; * Copyright (C) 1994-1996 Bas Laarhoven,&n; *           (C) 1996-1997 Claus-Justus Heine.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/lowlevel/ftape-bsm.h,v $&n; * $Revision: 1.2 $&n; * $Date: 1997/10/05 19:18:07 $&n; *&n; *      This file contains definitions for the bad sector map handling&n; *      routines for the QIC-117 floppy-tape driver for Linux.&n; */
macro_line|#include &lt;linux/ftape.h&gt;
macro_line|#include &lt;linux/ftape-header-segment.h&gt;
DECL|macro|EMPTY_SEGMENT
mdefine_line|#define EMPTY_SEGMENT           (0xffffffff)
DECL|macro|FAKE_SEGMENT
mdefine_line|#define FAKE_SEGMENT            (0xfffffffe)
multiline_comment|/*  maximum (format code 4) bad sector map size (bytes).&n; */
DECL|macro|BAD_SECTOR_MAP_SIZE
mdefine_line|#define BAD_SECTOR_MAP_SIZE     (29 * SECTOR_SIZE - 256)
multiline_comment|/*  format code 4 bad sector entry, ftape uses this&n; *  internally for all format codes&n; */
DECL|typedef|SectorMap
r_typedef
id|__u32
id|SectorMap
suffix:semicolon
multiline_comment|/*  variable and 1100 ft bad sector map entry. These three bytes represent&n; *  a single sector address measured from BOT. &n; */
DECL|struct|NewSectorMap
r_typedef
r_struct
id|NewSectorMap
(brace
DECL|member|bytes
id|__u8
id|bytes
(braket
l_int|3
)braket
suffix:semicolon
DECL|typedef|SectorCount
)brace
id|SectorCount
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; *      ftape-bsm.c defined global vars.&n; */
multiline_comment|/*&n; *      ftape-bsm.c defined global functions.&n; */
r_extern
r_void
id|update_bad_sector_map
c_func
(paren
id|__u8
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_void
id|ftape_extract_bad_sector_map
c_func
(paren
id|__u8
op_star
id|buffer
)paren
suffix:semicolon
r_extern
id|SectorMap
id|ftape_get_bad_sector_entry
c_func
(paren
r_int
id|segment_id
)paren
suffix:semicolon
r_extern
r_void
id|ftape_put_bad_sector_entry
c_func
(paren
r_int
id|segment_id
comma
id|SectorMap
id|mask
)paren
suffix:semicolon
r_extern
id|__u8
op_star
id|ftape_find_end_of_bsm_list
c_func
(paren
id|__u8
op_star
id|address
)paren
suffix:semicolon
r_extern
r_void
id|ftape_init_bsm
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
