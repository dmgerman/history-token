macro_line|#ifndef _ZFTAPE_RW_H
DECL|macro|_ZFTAPE_RW_H
mdefine_line|#define _ZFTAPE_RW_H
multiline_comment|/*&n; * Copyright (C) 1996, 1997 Claus-Justus Heine.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/zftape/zftape-rw.h,v $&n; * $Revision: 1.2 $&n; * $Date: 1997/10/05 19:19:09 $&n; *&n; *      This file contains the definitions for the read and write&n; *      functions for the QIC-117 floppy-tape driver for Linux.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt; /* for CONFIG_ZFT_DFLT_BLK_SZ */
macro_line|#include &quot;../zftape/zftape-buffers.h&quot;
DECL|macro|SEGMENTS_PER_TAPE
mdefine_line|#define SEGMENTS_PER_TAPE  (ft_segments_per_track * ft_tracks_per_tape)
multiline_comment|/*  QIC-113 Rev. G says that `a maximum of 63488 raw bytes may be&n; *  compressed into a single frame&squot;.&n; *  Maybe we should stick to 32kb to make it more `beautiful&squot;&n; */
DECL|macro|ZFT_MAX_BLK_SZ
mdefine_line|#define ZFT_MAX_BLK_SZ           (62*1024) /* bytes */
macro_line|#if !defined(CONFIG_ZFT_DFLT_BLK_SZ)
DECL|macro|CONFIG_ZFT_DFLT_BLK_SZ
macro_line|# define CONFIG_ZFT_DFLT_BLK_SZ   (10*1024) /* bytes, default of gnu tar */
macro_line|#elif CONFIG_ZFT_DFLT_BLK_SZ == 0
DECL|macro|CONFIG_ZFT_DFLT_BLK_SZ
macro_line|# undef  CONFIG_ZFT_DFLT_BLK_SZ
DECL|macro|CONFIG_ZFT_DFLT_BLK_SZ
macro_line|# define CONFIG_ZFT_DFLT_BLK_SZ 1
macro_line|#elif (CONFIG_ZFT_DFLT_BLK_SZ % 1024) != 0
macro_line|# error CONFIG_ZFT_DFLT_BLK_SZ must be 1 or a multiple of 1024
macro_line|#endif
multiline_comment|/* The *optional* compression routines need some overhead per tape&n; *  block for their purposes. Instead of asking the actual compression&n; *  implementation how much it needs, we restrict this overhead to be&n; *  maximal of ZFT_CMPT_OVERHEAD size. We need this for EOT&n; *  conditions. The tape is assumed to be logical at EOT when the&n; *  distance from the physical EOT is less than &n; *  one tape block + ZFT_CMPR_OVERHEAD &n; */
DECL|macro|ZFT_CMPR_OVERHEAD
mdefine_line|#define ZFT_CMPR_OVERHEAD 16        /* bytes */
r_typedef
r_enum
(brace
DECL|enumerator|zft_idle
id|zft_idle
op_assign
l_int|0
comma
DECL|enumerator|zft_reading
id|zft_reading
comma
DECL|enumerator|zft_writing
id|zft_writing
comma
DECL|typedef|zft_status_enum
)brace
id|zft_status_enum
suffix:semicolon
r_typedef
r_struct
multiline_comment|/*  all values measured in bytes */
(brace
DECL|member|seg_pos
r_int
id|seg_pos
suffix:semicolon
multiline_comment|/*  segment currently positioned at */
DECL|member|seg_byte_pos
r_int
id|seg_byte_pos
suffix:semicolon
multiline_comment|/*  offset in current segment */
DECL|member|tape_pos
id|__s64
id|tape_pos
suffix:semicolon
multiline_comment|/*  real offset from BOT */
DECL|member|volume_pos
id|__s64
id|volume_pos
suffix:semicolon
multiline_comment|/*  pos. in uncompressed data stream in&n;&t;&t;&t;      *  current volume &n;&t;&t;&t;      */
DECL|typedef|zft_position
)brace
id|zft_position
suffix:semicolon
r_extern
id|zft_position
id|zft_pos
suffix:semicolon
r_extern
id|__u8
op_star
id|zft_deblock_buf
suffix:semicolon
r_extern
id|__u8
op_star
id|zft_hseg_buf
suffix:semicolon
r_extern
r_int
id|zft_deblock_segment
suffix:semicolon
r_extern
id|zft_status_enum
id|zft_io_state
suffix:semicolon
r_extern
r_int
id|zft_header_changed
suffix:semicolon
r_extern
r_int
id|zft_bad_sector_map_changed
suffix:semicolon
r_extern
r_int
id|zft_qic113
suffix:semicolon
multiline_comment|/* conform to old specs. and old zftape */
r_extern
r_int
id|zft_use_compression
suffix:semicolon
r_extern
r_int
r_int
id|zft_blk_sz
suffix:semicolon
r_extern
id|__s64
id|zft_capacity
suffix:semicolon
r_extern
r_int
r_int
id|zft_written_segments
suffix:semicolon
r_extern
r_int
id|zft_label_changed
suffix:semicolon
multiline_comment|/*  zftape-rw.c exported functions&n; */
r_extern
r_int
r_int
id|zft_get_seg_sz
c_func
(paren
r_int
r_int
id|segment
)paren
suffix:semicolon
r_extern
r_void
id|zft_set_flags
c_func
(paren
r_int
r_int
id|minor_unit
)paren
suffix:semicolon
r_extern
r_int
id|zft_calc_seg_byte_coord
c_func
(paren
r_int
op_star
id|seg_byte_pos
comma
id|__s64
id|tape_pos
)paren
suffix:semicolon
r_extern
id|__s64
id|zft_calc_tape_pos
c_func
(paren
r_int
id|segment
)paren
suffix:semicolon
r_extern
id|__s64
id|zft_get_capacity
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|zft_update_label
c_func
(paren
id|__u8
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_int
id|zft_erase
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|zft_verify_write_segments
c_func
(paren
r_int
r_int
id|segment
comma
id|__u8
op_star
id|data
comma
r_int
id|size
comma
id|__u8
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_int
r_int
id|zft_get_time
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _ZFTAPE_RW_H */
eof
