macro_line|#ifndef _FTAPE_HEADER_SEGMENT_H
DECL|macro|_FTAPE_HEADER_SEGMENT_H
mdefine_line|#define _FTAPE_HEADER_SEGMENT_H
multiline_comment|/*&n; * Copyright (C) 1996-1997 Claus-Justus Heine.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/include/linux/ftape-header-segment.h,v $&n; * $Revision: 1.2 $&n; * $Date: 1997/10/05 19:19:28 $&n; *&n; *      This file defines some offsets into the header segment of a&n; *      floppy tape cartridge.  For use with the QIC-40/80/3010/3020&n; *      floppy-tape driver &quot;ftape&quot; for Linux.&n; */
DECL|macro|FT_SIGNATURE
mdefine_line|#define FT_SIGNATURE   0  /* must be 0xaa55aa55 */
DECL|macro|FT_FMT_CODE
mdefine_line|#define FT_FMT_CODE    4
DECL|macro|FT_REV_LEVEL
mdefine_line|#define FT_REV_LEVEL   5  /* only for QIC-80 since. Rev. L (== 0x0c)         */
DECL|macro|FT_HSEG_1
mdefine_line|#define FT_HSEG_1      6  /* first header segment, except for format code  6 */
DECL|macro|FT_HSEG_2
mdefine_line|#define FT_HSEG_2      8  /* second header segment, except for format code 6 */
DECL|macro|FT_FRST_SEG
mdefine_line|#define FT_FRST_SEG   10  /* first data segment, except for format code 6    */
DECL|macro|FT_LAST_SEG
mdefine_line|#define FT_LAST_SEG   12  /* last data segment, except for format code 6     */
DECL|macro|FT_FMT_DATE
mdefine_line|#define FT_FMT_DATE   14  /* date and time of most recent format, see below  */
DECL|macro|FT_WR_DATE
mdefine_line|#define FT_WR_DATE    18  /* date and time of most recent write or format    */
DECL|macro|FT_SPT
mdefine_line|#define FT_SPT        24  /* segments per track                              */
DECL|macro|FT_TPC
mdefine_line|#define FT_TPC        26  /* tracks per cartridge                            */
DECL|macro|FT_FHM
mdefine_line|#define FT_FHM        27  /* floppy drive head (maximum of it)               */
DECL|macro|FT_FTM
mdefine_line|#define FT_FTM        28  /* floppy track max.                               */
DECL|macro|FT_FSM
mdefine_line|#define FT_FSM        29  /* floppy sector max. (128)                        */
DECL|macro|FT_LABEL
mdefine_line|#define FT_LABEL      30  /* floppy tape label                               */
DECL|macro|FT_LABEL_DATE
mdefine_line|#define FT_LABEL_DATE 74  /* date and time the tape label was written        */
DECL|macro|FT_LABEL_SZ
mdefine_line|#define FT_LABEL_SZ   (FT_LABEL_DATE - FT_LABEL)
DECL|macro|FT_CMAP_START
mdefine_line|#define FT_CMAP_START 78  /* starting segment of compression map             */
DECL|macro|FT_FMT_ERROR
mdefine_line|#define FT_FMT_ERROR 128  /* must be set to 0xff if remainder gets lost during&n;&t;&t;&t;   * tape format&n;&t;&t;&t;   */
DECL|macro|FT_SEG_CNT
mdefine_line|#define FT_SEG_CNT   130  /* number of seg. written, formatted or verified&n;&t;&t;&t;   * through lifetime of tape (why not read?)&n;&t;&t;&t;   */
DECL|macro|FT_INIT_DATE
mdefine_line|#define FT_INIT_DATE 138  /* date and time of initial tape format    */
DECL|macro|FT_FMT_CNT
mdefine_line|#define FT_FMT_CNT   142  /* number of times tape has been formatted */
DECL|macro|FT_FSL_CNT
mdefine_line|#define FT_FSL_CNT   144  /* number of segments in failed sector log */
DECL|macro|FT_MK_CODE
mdefine_line|#define FT_MK_CODE   146  /* id string of tape manufacturer          */
DECL|macro|FT_LOT_CODE
mdefine_line|#define FT_LOT_CODE  190  /* tape manufacturer lot code              */
DECL|macro|FT_6_HSEG_1
mdefine_line|#define FT_6_HSEG_1  234  /* first header segment for format code  6 */
DECL|macro|FT_6_HSEG_2
mdefine_line|#define FT_6_HSEG_2  238  /* second header segment for format code 6 */
DECL|macro|FT_6_FRST_SEG
mdefine_line|#define FT_6_FRST_SEG 242 /* first data segment for format code 6    */
DECL|macro|FT_6_LAST_SEG
mdefine_line|#define FT_6_LAST_SEG 246 /* last data segment for format code 6     */
DECL|macro|FT_FSL
mdefine_line|#define FT_FSL        256
DECL|macro|FT_HEADER_END
mdefine_line|#define FT_HEADER_END 256 /* space beyond this point:&n;&t;&t;&t;   * format codes 2, 3 and 5: &n;&t;&t;&t;   * -  failed sector log until byte 2047&n;&t;&t;&t;   * -  bad sector map in the reamining part of segment&n;&t;&t;&t;   * format codes 4 and 6:&n;&t;&t;&t;   * -  bad sector map  starts hear&n;&t;&t;&t;   */
multiline_comment|/*  value to be stored at the FT_SIGNATURE offset &n; */
DECL|macro|FT_HSEG_MAGIC
mdefine_line|#define FT_HSEG_MAGIC 0xaa55aa55
DECL|macro|FT_D2G_MAGIC
mdefine_line|#define FT_D2G_MAGIC  0x82288228 /* Ditto 2GB */
multiline_comment|/* data and time encoding: */
DECL|macro|FT_YEAR_SHIFT
mdefine_line|#define FT_YEAR_SHIFT 25
DECL|macro|FT_YEAR_MASK
mdefine_line|#define FT_YEAR_MASK  0xfe000000
DECL|macro|FT_YEAR_0
mdefine_line|#define FT_YEAR_0     1970
DECL|macro|FT_YEAR_MAX
mdefine_line|#define FT_YEAR_MAX   127
DECL|macro|FT_YEAR
mdefine_line|#define FT_YEAR(year) ((((year)-FT_YEAR_0)&lt;&lt;FT_YEAR_SHIFT)&amp;FT_YEAR_MASK)
DECL|macro|FT_TIME_SHIFT
mdefine_line|#define FT_TIME_SHIFT   0
DECL|macro|FT_TIME_MASK
mdefine_line|#define FT_TIME_MASK    0x01FFFFFF
DECL|macro|FT_TIME_MAX
mdefine_line|#define FT_TIME_MAX     0x01ea6dff /* last second of a year */
DECL|macro|FT_TIME
mdefine_line|#define FT_TIME(mo,d,h,m,s) &bslash;&n;&t;((((s)+60*((m)+60*((h)+24*((d)+31*(mo))))) &amp; FT_TIME_MASK))
DECL|macro|FT_TIME_STAMP
mdefine_line|#define FT_TIME_STAMP(y,mo,d,h,m,s) (FT_YEAR(y) | FT_TIME(mo,d,h,m,s))
multiline_comment|/* values for the format code field */
r_typedef
r_enum
(brace
DECL|enumerator|fmt_normal
id|fmt_normal
op_assign
l_int|2
comma
multiline_comment|/*  QIC-80 post Rev. B 205Ft or 307Ft tape    */
DECL|enumerator|fmt_1100ft
id|fmt_1100ft
op_assign
l_int|3
comma
multiline_comment|/*  QIC-80 post Rev. B 1100Ft tape            */
DECL|enumerator|fmt_var
id|fmt_var
op_assign
l_int|4
comma
multiline_comment|/*  QIC-80 post Rev. B variabel length format */
DECL|enumerator|fmt_425ft
id|fmt_425ft
op_assign
l_int|5
comma
multiline_comment|/*  QIC-80 post Rev. B 425Ft tape             */
DECL|enumerator|fmt_big
id|fmt_big
op_assign
l_int|6
multiline_comment|/*  QIC-3010/3020 variable length tape with more &n;&t;&t;&t; *  than 2^16 segments per tape&n;&t;&t;&t; */
DECL|typedef|ft_format_type
)brace
id|ft_format_type
suffix:semicolon
multiline_comment|/* definitions for the failed sector log */
DECL|macro|FT_FSL_SIZE
mdefine_line|#define FT_FSL_SIZE        (2 * FT_SECTOR_SIZE - FT_HEADER_END)
DECL|macro|FT_FSL_MAX_ENTRIES
mdefine_line|#define FT_FSL_MAX_ENTRIES (FT_FSL_SIZE/sizeof(__u32))
DECL|struct|ft_fsl_entry
r_typedef
r_struct
id|ft_fsl_entry
(brace
DECL|member|segment
id|__u16
id|segment
suffix:semicolon
DECL|member|date
id|__u16
id|date
suffix:semicolon
DECL|typedef|ft_fsl_entry
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|ft_fsl_entry
suffix:semicolon
multiline_comment|/*  date encoding for the failed sector log &n; *  month: 1..12, day: 1..31, year: 1970..2097&n; */
DECL|macro|FT_FSL_TIME_STAMP
mdefine_line|#define FT_FSL_TIME_STAMP(y,m,d) &bslash;&n;&t;(((((y) - FT_YEAR_0)&lt;&lt;9)&amp;0xfe00) | (((m)&lt;&lt;5)&amp;0x01e0) | ((d)&amp;0x001f))
macro_line|#endif /* _FTAPE_HEADER_SEGMENT_H */
eof
