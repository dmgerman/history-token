macro_line|#ifndef _FTAPE_ECC_H_
DECL|macro|_FTAPE_ECC_H_
mdefine_line|#define _FTAPE_ECC_H_
multiline_comment|/*&n; *      Copyright (C) 1993 Ning and David Mosberger.&n; *      Original:&n; *      Copyright (C) 1993 Bas Laarhoven.&n; *      Copyright (C) 1992 David L. Brown, Jr.&n; &n; This program is free software; you can redistribute it and/or&n; modify it under the terms of the GNU General Public License as&n; published by the Free Software Foundation; either version 2, or (at&n; your option) any later version.&n; &n; This program is distributed in the hope that it will be useful, but&n; WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; General Public License for more details.&n; &n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139,&n; USA.&n; &n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/lowlevel/ftape-ecc.h,v $&n; * $Revision: 1.2 $&n; * $Date: 1997/10/05 19:18:11 $&n; *&n; *      This file contains the definitions for the&n; *      Reed-Solomon error correction code &n; *      for the QIC-40/80 tape streamer device driver.&n; */
macro_line|#include &quot;../lowlevel/ftape-bsm.h&quot;
DECL|macro|BAD_CLEAR
mdefine_line|#define BAD_CLEAR(entry) ((entry)=0)
DECL|macro|BAD_SET
mdefine_line|#define BAD_SET(entry,sector) ((entry)|=(1&lt;&lt;(sector)))
DECL|macro|BAD_CHECK
mdefine_line|#define BAD_CHECK(entry,sector) ((entry)&amp;(1&lt;&lt;(sector)))
multiline_comment|/*&n; * Return values for ecc_correct_data:&n; */
r_enum
(brace
DECL|enumerator|ECC_OK
id|ECC_OK
comma
multiline_comment|/* Data was correct. */
DECL|enumerator|ECC_CORRECTED
id|ECC_CORRECTED
comma
multiline_comment|/* Correctable error in data. */
DECL|enumerator|ECC_FAILED
id|ECC_FAILED
comma
multiline_comment|/* Could not correct data. */
)brace
suffix:semicolon
multiline_comment|/*&n; * Representation of an in memory segment.  MARKED_BAD lists the&n; * sectors that were marked bad during formatting.  If the N-th sector&n; * in a segment is marked bad, bit 1&lt;&lt;N will be set in MARKED_BAD.&n; * The sectors should be read in from the disk and packed, as if the&n; * bad sectors were not there, and the segment just contained fewer&n; * sectors.  READ_SECTORS is a bitmap of errors encountered while&n; * reading the data.  These offsets are relative to the packed data.&n; * BLOCKS is a count of the sectors not marked bad.  This is just to&n; * prevent having to count the zero bits in MARKED_BAD each time this&n; * is needed.  DATA is the actual sector packed data from (or to) the&n; * tape.&n; */
DECL|struct|memory_segment
r_struct
id|memory_segment
(brace
DECL|member|marked_bad
id|SectorMap
id|marked_bad
suffix:semicolon
DECL|member|read_bad
id|SectorMap
id|read_bad
suffix:semicolon
DECL|member|blocks
r_int
id|blocks
suffix:semicolon
DECL|member|data
id|__u8
op_star
id|data
suffix:semicolon
DECL|member|corrected
id|SectorMap
id|corrected
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ecc.c defined global variables:&n; */
macro_line|#ifdef TEST
r_extern
r_int
id|ftape_ecc_tracing
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * ecc.c defined global functions:&n; */
r_extern
r_int
id|ftape_ecc_correct_data
c_func
(paren
r_struct
id|memory_segment
op_star
id|data
)paren
suffix:semicolon
r_extern
r_int
id|ftape_ecc_set_segment_parity
c_func
(paren
r_struct
id|memory_segment
op_star
id|data
)paren
suffix:semicolon
macro_line|#endif&t;/* _FTAPE_ECC_H_ */
eof
