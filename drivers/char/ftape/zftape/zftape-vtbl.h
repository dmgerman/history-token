macro_line|#ifndef _ZFTAPE_VTBL_H
DECL|macro|_ZFTAPE_VTBL_H
mdefine_line|#define _ZFTAPE_VTBL_H
multiline_comment|/*&n; *      Copyright (c) 1995-1997  Claus-Justus Heine&n;&n; This program is free software; you can redistribute it and/or&n; modify it under the terms of the GNU General Public License as&n; published by the Free Software Foundation; either version 2, or (at&n; your option) any later version.&n; &n; This program is distributed in the hope that it will be useful, but&n; WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; General Public License for more details.&n; &n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139,&n; USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/zftape/zftape-vtbl.h,v $&n; * $Revision: 1.3 $&n; * $Date: 1997/10/28 14:30:09 $&n; *&n; *      This file defines a volume table as defined in the QIC-80&n; *      development standards.&n; */
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &quot;../lowlevel/ftape-tracing.h&quot;
macro_line|#include &quot;../zftape/zftape-eof.h&quot;
macro_line|#include &quot;../zftape/zftape-ctl.h&quot;
macro_line|#include &quot;../zftape/zftape-rw.h&quot;
DECL|macro|VTBL_SIZE
mdefine_line|#define VTBL_SIZE 128 /* bytes */
multiline_comment|/* The following are offsets in the vtbl.  */
DECL|macro|VTBL_SIG
mdefine_line|#define VTBL_SIG   0
DECL|macro|VTBL_START
mdefine_line|#define VTBL_START 4
DECL|macro|VTBL_END
mdefine_line|#define VTBL_END   6
DECL|macro|VTBL_DESC
mdefine_line|#define VTBL_DESC  8
DECL|macro|VTBL_DATE
mdefine_line|#define VTBL_DATE  52
DECL|macro|VTBL_FLAGS
mdefine_line|#define VTBL_FLAGS 56
DECL|macro|VTBL_FL_VENDOR_SPECIFIC
mdefine_line|#define VTBL_FL_VENDOR_SPECIFIC (1&lt;&lt;0)
DECL|macro|VTBL_FL_MUTLI_CARTRIDGE
mdefine_line|#define VTBL_FL_MUTLI_CARTRIDGE (1&lt;&lt;1)
DECL|macro|VTBL_FL_NOT_VERIFIED
mdefine_line|#define VTBL_FL_NOT_VERIFIED    (1&lt;&lt;2)
DECL|macro|VTBL_FL_REDIR_INHIBIT
mdefine_line|#define VTBL_FL_REDIR_INHIBIT   (1&lt;&lt;3)
DECL|macro|VTBL_FL_SEG_SPANNING
mdefine_line|#define VTBL_FL_SEG_SPANNING    (1&lt;&lt;4)
DECL|macro|VTBL_FL_DIRECTORY_LAST
mdefine_line|#define VTBL_FL_DIRECTORY_LAST  (1&lt;&lt;5)
DECL|macro|VTBL_FL_RESERVED_6
mdefine_line|#define VTBL_FL_RESERVED_6      (1&lt;&lt;6)
DECL|macro|VTBL_FL_RESERVED_7
mdefine_line|#define VTBL_FL_RESERVED_7      (1&lt;&lt;7)
DECL|macro|VTBL_M_NO
mdefine_line|#define VTBL_M_NO  57
DECL|macro|VTBL_EXT
mdefine_line|#define VTBL_EXT   58
DECL|macro|EXT_ZFTAPE_SIG
mdefine_line|#define EXT_ZFTAPE_SIG     0
DECL|macro|EXT_ZFTAPE_BLKSZ
mdefine_line|#define EXT_ZFTAPE_BLKSZ  10
DECL|macro|EXT_ZFTAPE_CMAP
mdefine_line|#define EXT_ZFTAPE_CMAP   12
DECL|macro|EXT_ZFTAPE_QIC113
mdefine_line|#define EXT_ZFTAPE_QIC113 13
DECL|macro|VTBL_PWD
mdefine_line|#define VTBL_PWD   84
DECL|macro|VTBL_DIR_SIZE
mdefine_line|#define VTBL_DIR_SIZE 92
DECL|macro|VTBL_DATA_SIZE
mdefine_line|#define VTBL_DATA_SIZE 96
DECL|macro|VTBL_OS_VERSION
mdefine_line|#define VTBL_OS_VERSION 104
DECL|macro|VTBL_SRC_DRIVE
mdefine_line|#define VTBL_SRC_DRIVE  106
DECL|macro|VTBL_DEV
mdefine_line|#define VTBL_DEV        122
DECL|macro|VTBL_RESERVED_1
mdefine_line|#define VTBL_RESERVED_1 123
DECL|macro|VTBL_CMPR
mdefine_line|#define VTBL_CMPR       124
DECL|macro|VTBL_CMPR_UNREG
mdefine_line|#define VTBL_CMPR_UNREG 0x3f
DECL|macro|VTBL_CMPR_USED
mdefine_line|#define VTBL_CMPR_USED  0x80
DECL|macro|VTBL_FMT
mdefine_line|#define VTBL_FMT        125
DECL|macro|VTBL_RESERVED_2
mdefine_line|#define VTBL_RESERVED_2 126
DECL|macro|VTBL_RESERVED_3
mdefine_line|#define VTBL_RESERVED_3 127
multiline_comment|/* compatability with pre revision K */
DECL|macro|VTBL_K_CMPR
mdefine_line|#define VTBL_K_CMPR     120 
multiline_comment|/*  the next is used by QIC-3020 tapes with format code 6 (&gt;2^16&n; *  segments) It is specified in QIC-113, Rev. G, Section 5 (SCSI&n; *  volume table). The difference is simply, that we only store the&n; *  number of segments used, not the starting segment.&n; */
DECL|macro|VTBL_SCSI_SEGS
mdefine_line|#define VTBL_SCSI_SEGS  4 /* is a 4 byte value */
multiline_comment|/*  one vtbl is 128 bytes, that results in a maximum number of&n; *  29*1024/128 = 232 volumes.&n; */
DECL|macro|ZFT_MAX_VOLUMES
mdefine_line|#define ZFT_MAX_VOLUMES (FT_SEGMENT_SIZE/VTBL_SIZE)
DECL|macro|VTBL_ID
mdefine_line|#define VTBL_ID  &quot;VTBL&quot;
DECL|macro|VTBL_IDS
mdefine_line|#define VTBL_IDS { VTBL_ID, &quot;XTBL&quot;, &quot;UTID&quot;, &quot;EXVT&quot; } /* other valid ids */
DECL|macro|ZFT_VOL_NAME
mdefine_line|#define ZFT_VOL_NAME &quot;zftape volume&quot; /* volume label used by me */
DECL|macro|ZFTAPE_SIG
mdefine_line|#define ZFTAPE_SIG &quot;LINUX ZFT&quot;
multiline_comment|/*  global variables&n; */
DECL|struct|zft_internal_vtbl
r_typedef
r_struct
id|zft_internal_vtbl
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|start_seg
r_int
r_int
id|start_seg
suffix:semicolon
multiline_comment|/* 32 bits are enough for now */
DECL|member|end_seg
r_int
r_int
id|end_seg
suffix:semicolon
multiline_comment|/* 32 bits are enough for now */
DECL|member|size
id|__s64
id|size
suffix:semicolon
multiline_comment|/* uncompressed size */
DECL|member|blk_sz
r_int
r_int
id|blk_sz
suffix:semicolon
multiline_comment|/* block size for this volume */
DECL|member|zft_volume
r_int
r_int
id|zft_volume
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* zftape created this volume */
DECL|member|use_compression
r_int
r_int
id|use_compression
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* compressed volume  */
DECL|member|qic113
r_int
r_int
id|qic113
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* layout of compressed block&n;&t;&t;&t;&t;&t; * info and vtbl conforms to&n;&t;&t;&t;&t;&t; * QIC-113, Rev. G &n;&t;&t;&t;&t;&t; */
DECL|member|new_volume
r_int
r_int
id|new_volume
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* it was created by us, this&n;&t;&t;&t;&t;&t; * run.  this allows the&n;&t;&t;&t;&t;&t; * fields that aren&squot;t really&n;&t;&t;&t;&t;&t; * used by zftape to be filled&n;&t;&t;&t;&t;&t; * in by some user level&n;&t;&t;&t;&t;&t; * program.&n;&t;&t;&t;&t;&t; */
DECL|member|open
r_int
r_int
id|open
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* just in progress of being &n;&t;&t;&t;&t;&t; * written&n;&t;&t;&t;&t;&t; */
DECL|typedef|zft_volinfo
)brace
id|zft_volinfo
suffix:semicolon
r_extern
r_struct
id|list_head
id|zft_vtbl
suffix:semicolon
DECL|macro|zft_head_vtbl
mdefine_line|#define zft_head_vtbl  list_entry(zft_vtbl.next, zft_volinfo, node)
DECL|macro|zft_eom_vtbl
mdefine_line|#define zft_eom_vtbl   list_entry(zft_vtbl.prev, zft_volinfo, node)
DECL|macro|zft_last_vtbl
mdefine_line|#define zft_last_vtbl  list_entry(zft_eom_vtbl-&gt;node.prev, zft_volinfo, node)
DECL|macro|zft_first_vtbl
mdefine_line|#define zft_first_vtbl list_entry(zft_head_vtbl-&gt;node.next, zft_volinfo, node)
DECL|macro|zft_vtbl_empty
mdefine_line|#define zft_vtbl_empty (zft_eom_vtbl-&gt;node.prev == &amp;zft_head_vtbl-&gt;node)
DECL|macro|DUMP_VOLINFO
mdefine_line|#define DUMP_VOLINFO(level, desc, info)&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;char tmp[21];&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;strncpy(tmp, desc, 20);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;tmp[20] = &squot;&bslash;0&squot;;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;TRACE(level, &quot;Volume %d:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;      KERN_INFO &quot;description  : %s&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;      KERN_INFO &quot;first segment: %d&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;      KERN_INFO &quot;last  segment: %d&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;      KERN_INFO &quot;size         : &quot; LL_X &quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;      KERN_INFO &quot;block size   : %d&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;      KERN_INFO &quot;compression  : %d&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;      KERN_INFO &quot;zftape volume: %d&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;      KERN_INFO &quot;QIC-113 conf.: %d&quot;,&t;&t;&t;&t;&bslash;&n;&t;      (info)-&gt;count, tmp, (info)-&gt;start_seg, (info)-&gt;end_seg,&t;&bslash;&n;&t;      LL((info)-&gt;size), (info)-&gt;blk_sz,&t;&t;&t;&t;&bslash;&n;&t;      (info)-&gt;use_compression != 0, (info)-&gt;zft_volume != 0,&t;&bslash;&n;&t;      (info)-&gt;qic113 != 0);&t;&t;&t;&t;&t;&bslash;&n;}
r_extern
r_int
id|zft_qic_mode
suffix:semicolon
r_extern
r_int
id|zft_old_ftape
suffix:semicolon
r_extern
r_int
id|zft_volume_table_changed
suffix:semicolon
multiline_comment|/* exported functions */
r_extern
r_void
id|zft_init_vtbl
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|zft_free_vtbl
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|zft_new_vtbl_entry
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|zft_extract_volume_headers
c_func
(paren
id|__u8
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_int
id|zft_update_volume_table
(paren
r_int
r_int
id|segment
)paren
suffix:semicolon
r_extern
r_int
id|zft_open_volume
(paren
id|zft_position
op_star
id|pos
comma
r_int
id|blk_sz
comma
r_int
id|use_compression
)paren
suffix:semicolon
r_extern
r_int
id|zft_close_volume
(paren
id|zft_position
op_star
id|pos
)paren
suffix:semicolon
r_extern
r_const
id|zft_volinfo
op_star
id|zft_find_volume
c_func
(paren
r_int
r_int
id|seg_pos
)paren
suffix:semicolon
r_extern
r_int
id|zft_skip_volumes
(paren
r_int
id|count
comma
id|zft_position
op_star
id|pos
)paren
suffix:semicolon
r_extern
id|__s64
id|zft_get_eom_pos
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|zft_skip_to_eom
(paren
id|zft_position
op_star
id|pos
)paren
suffix:semicolon
r_extern
r_int
id|zft_fake_volume_headers
(paren
id|eof_mark_union
op_star
id|eof_map
comma
r_int
id|num_failed_sectors
)paren
suffix:semicolon
r_extern
r_int
id|zft_weof
(paren
r_int
r_int
id|count
comma
id|zft_position
op_star
id|pos
)paren
suffix:semicolon
r_extern
r_void
id|zft_move_past_eof
(paren
id|zft_position
op_star
id|pos
)paren
suffix:semicolon
r_extern
r_inline
r_int
id|zft_tape_at_eod
(paren
r_const
id|zft_position
op_star
id|pos
)paren
suffix:semicolon
r_extern
r_inline
r_int
id|zft_tape_at_lbot
(paren
r_const
id|zft_position
op_star
id|pos
)paren
suffix:semicolon
r_extern
r_inline
r_void
id|zft_position_before_eof
(paren
id|zft_position
op_star
id|pos
comma
r_const
id|zft_volinfo
op_star
id|volume
)paren
suffix:semicolon
r_extern
r_inline
id|__s64
id|zft_check_for_eof
c_func
(paren
r_const
id|zft_volinfo
op_star
id|vtbl
comma
r_const
id|zft_position
op_star
id|pos
)paren
suffix:semicolon
multiline_comment|/* this function decrements the zft_seg_pos counter if we are right&n; * at the beginning of a segment. This is to handel fsfm/bsfm -- we&n; * need to position before the eof mark.  NOTE: zft_tape_pos is not&n; * changed &n; */
DECL|function|zft_position_before_eof
r_extern
r_inline
r_void
id|zft_position_before_eof
c_func
(paren
id|zft_position
op_star
id|pos
comma
r_const
id|zft_volinfo
op_star
id|volume
)paren
(brace
id|TRACE_FUN
c_func
(paren
id|ft_t_flow
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos-&gt;seg_pos
op_eq
id|volume-&gt;end_seg
op_plus
l_int|1
op_logical_and
id|pos-&gt;seg_byte_pos
op_eq
l_int|0
)paren
(brace
id|pos-&gt;seg_pos
op_decrement
suffix:semicolon
id|pos-&gt;seg_byte_pos
op_assign
id|zft_get_seg_sz
c_func
(paren
id|pos-&gt;seg_pos
)paren
suffix:semicolon
)brace
id|TRACE_EXIT
suffix:semicolon
)brace
multiline_comment|/*  Mmmh. Is the position at the end of the last volume, that is right&n; *  before the last EOF mark also logical an EOD condition?&n; */
DECL|function|zft_tape_at_eod
r_extern
r_inline
r_int
id|zft_tape_at_eod
c_func
(paren
r_const
id|zft_position
op_star
id|pos
)paren
(brace
id|TRACE_FUN
c_func
(paren
id|ft_t_any
)paren
suffix:semicolon
r_if
c_cond
(paren
id|zft_qic_mode
)paren
(brace
id|TRACE_EXIT
(paren
id|pos-&gt;seg_pos
op_ge
id|zft_eom_vtbl-&gt;start_seg
op_logical_or
id|zft_last_vtbl-&gt;open
)paren
suffix:semicolon
)brace
r_else
(brace
id|TRACE_EXIT
id|pos-&gt;seg_pos
OG
id|ft_last_data_segment
suffix:semicolon
)brace
)brace
DECL|function|zft_tape_at_lbot
r_extern
r_inline
r_int
id|zft_tape_at_lbot
c_func
(paren
r_const
id|zft_position
op_star
id|pos
)paren
(brace
r_if
c_cond
(paren
id|zft_qic_mode
)paren
(brace
r_return
(paren
id|pos-&gt;seg_pos
op_le
id|zft_first_vtbl-&gt;start_seg
op_logical_and
id|pos-&gt;volume_pos
op_eq
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
(paren
id|pos-&gt;seg_pos
op_le
id|ft_first_data_segment
op_logical_and
id|pos-&gt;volume_pos
op_eq
l_int|0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* This one checks for EOF.  return remaing space (may be negative) &n; */
DECL|function|zft_check_for_eof
r_extern
r_inline
id|__s64
id|zft_check_for_eof
c_func
(paren
r_const
id|zft_volinfo
op_star
id|vtbl
comma
r_const
id|zft_position
op_star
id|pos
)paren
(brace
r_return
(paren
id|__s64
)paren
(paren
id|vtbl-&gt;size
op_minus
id|pos-&gt;volume_pos
)paren
suffix:semicolon
)brace
macro_line|#endif /* _ZFTAPE_VTBL_H */
eof
