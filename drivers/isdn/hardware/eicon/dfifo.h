multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    2.1&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef __DIVA_IDI_DFIFO_INC__
DECL|macro|__DIVA_IDI_DFIFO_INC__
mdefine_line|#define __DIVA_IDI_DFIFO_INC__
DECL|macro|DIVA_DFIFO_CACHE_SZ
mdefine_line|#define DIVA_DFIFO_CACHE_SZ   64 /* Used to isolate pipe from&n;                    rest of the world&n;                   should be divisible by 4&n;                   */
DECL|macro|DIVA_DFIFO_RAW_SZ
mdefine_line|#define DIVA_DFIFO_RAW_SZ    (2512*8)
DECL|macro|DIVA_DFIFO_DATA_SZ
mdefine_line|#define DIVA_DFIFO_DATA_SZ   68
DECL|macro|DIVA_DFIFO_HDR_SZ
mdefine_line|#define DIVA_DFIFO_HDR_SZ    4
DECL|macro|DIVA_DFIFO_SEGMENT_SZ
mdefine_line|#define DIVA_DFIFO_SEGMENT_SZ  (DIVA_DFIFO_DATA_SZ+DIVA_DFIFO_HDR_SZ)
DECL|macro|DIVA_DFIFO_SEGMENTS
mdefine_line|#define DIVA_DFIFO_SEGMENTS   ((DIVA_DFIFO_RAW_SZ)/(DIVA_DFIFO_SEGMENT_SZ)+1)
DECL|macro|DIVA_DFIFO_MEM_SZ
mdefine_line|#define DIVA_DFIFO_MEM_SZ (&bslash;&n;        (DIVA_DFIFO_SEGMENT_SZ)*(DIVA_DFIFO_SEGMENTS)+&bslash;&n;        (DIVA_DFIFO_CACHE_SZ)*2&bslash;&n;             )
DECL|macro|DIVA_DFIFO_STEP
mdefine_line|#define DIVA_DFIFO_STEP DIVA_DFIFO_SEGMENT_SZ
multiline_comment|/* -------------------------------------------------------------------------&n;  Block header layout is:&n;   byte[0] -&gt; flags&n;   byte[1] -&gt; length of data in block&n;   byte[2] -&gt; reserved&n;   byte[4] -&gt; reserved&n;  ------------------------------------------------------------------------- */
DECL|macro|DIVA_DFIFO_WRAP
mdefine_line|#define DIVA_DFIFO_WRAP   0x80 /* This is the last block in fifo   */
DECL|macro|DIVA_DFIFO_READY
mdefine_line|#define DIVA_DFIFO_READY  0x40 /* This block is ready for processing */
DECL|macro|DIVA_DFIFO_LAST
mdefine_line|#define DIVA_DFIFO_LAST   0x20 /* This block is last in message      */
DECL|macro|DIVA_DFIFO_AUTO
mdefine_line|#define DIVA_DFIFO_AUTO   0x10 /* Don&squot;t look for &squot;ready&squot;, don&squot;t ack */
r_int
id|diva_dfifo_create
(paren
r_void
op_star
id|start
comma
r_int
id|length
)paren
suffix:semicolon
macro_line|#endif
eof
