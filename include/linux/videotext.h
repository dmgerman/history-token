macro_line|#ifndef _VTX_H
DECL|macro|_VTX_H
mdefine_line|#define _VTX_H
multiline_comment|/* $Id: videotext.h,v 1.1 1998/03/30 22:26:39 alan Exp $&n; *&n; * Copyright (c) 1994-97 Martin Buck  &lt;martin-2.buck@student.uni-ulm.de&gt;&n; * Read COPYING for more information&n; *&n; */
multiline_comment|/*&n; *&t;Videotext ioctls&n; */
DECL|macro|VTXIOCGETINFO
mdefine_line|#define VTXIOCGETINFO  0x7101  /* get version of driver &amp; capabilities of vtx-chipset */
DECL|macro|VTXIOCCLRPAGE
mdefine_line|#define VTXIOCCLRPAGE  0x7102  /* clear page-buffer */
DECL|macro|VTXIOCCLRFOUND
mdefine_line|#define VTXIOCCLRFOUND 0x7103  /* clear bits indicating that page was found */
DECL|macro|VTXIOCPAGEREQ
mdefine_line|#define VTXIOCPAGEREQ  0x7104  /* search for page */
DECL|macro|VTXIOCGETSTAT
mdefine_line|#define VTXIOCGETSTAT  0x7105  /* get status of page-buffer */
DECL|macro|VTXIOCGETPAGE
mdefine_line|#define VTXIOCGETPAGE  0x7106  /* get contents of page-buffer */
DECL|macro|VTXIOCSTOPDAU
mdefine_line|#define VTXIOCSTOPDAU  0x7107  /* stop data acquisition unit */
DECL|macro|VTXIOCPUTPAGE
mdefine_line|#define VTXIOCPUTPAGE  0x7108  /* display page on TV-screen */
DECL|macro|VTXIOCSETDISP
mdefine_line|#define VTXIOCSETDISP  0x7109  /* set TV-mode */
DECL|macro|VTXIOCPUTSTAT
mdefine_line|#define VTXIOCPUTSTAT  0x710a  /* set status of TV-output-buffer */
DECL|macro|VTXIOCCLRCACHE
mdefine_line|#define VTXIOCCLRCACHE 0x710b  /* clear cache on VTX-interface (if avail.) */
DECL|macro|VTXIOCSETVIRT
mdefine_line|#define VTXIOCSETVIRT  0x710c  /* turn on virtual mode (this disables TV-display) */
multiline_comment|/* &n; *&t;Definitions for VTXIOCGETINFO&n; */
DECL|macro|SAA5243
mdefine_line|#define SAA5243 0
DECL|macro|SAA5246
mdefine_line|#define SAA5246 1
DECL|macro|SAA5249
mdefine_line|#define SAA5249 2
DECL|macro|SAA5248
mdefine_line|#define SAA5248 3
DECL|macro|XSTV5346
mdefine_line|#define XSTV5346 4
r_typedef
r_struct
(brace
DECL|member|version_major
DECL|member|version_minor
r_int
id|version_major
comma
id|version_minor
suffix:semicolon
multiline_comment|/* version of driver; if version_major changes, driver */
multiline_comment|/* is not backward compatible!!! CHECK THIS!!! */
DECL|member|numpages
r_int
id|numpages
suffix:semicolon
multiline_comment|/* number of page-buffers of vtx-chipset */
DECL|member|cct_type
r_int
id|cct_type
suffix:semicolon
multiline_comment|/* type of vtx-chipset (SAA5243, SAA5246, SAA5248 or&n;  &t;&t;&t;&t;&t;&t; * SAA5249) */
)brace
DECL|typedef|vtx_info_t
id|vtx_info_t
suffix:semicolon
multiline_comment|/*&n; *&t;Definitions for VTXIOC{CLRPAGE,CLRFOUND,PAGEREQ,GETSTAT,GETPAGE,STOPDAU,PUTPAGE,SETDISP}&n; */
DECL|macro|MIN_UNIT
mdefine_line|#define MIN_UNIT   (1&lt;&lt;0)
DECL|macro|MIN_TEN
mdefine_line|#define MIN_TEN    (1&lt;&lt;1)
DECL|macro|HR_UNIT
mdefine_line|#define HR_UNIT    (1&lt;&lt;2)
DECL|macro|HR_TEN
mdefine_line|#define HR_TEN     (1&lt;&lt;3)
DECL|macro|PG_UNIT
mdefine_line|#define PG_UNIT    (1&lt;&lt;4)
DECL|macro|PG_TEN
mdefine_line|#define PG_TEN     (1&lt;&lt;5)
DECL|macro|PG_HUND
mdefine_line|#define PG_HUND    (1&lt;&lt;6)
DECL|macro|PGMASK_MAX
mdefine_line|#define PGMASK_MAX (1&lt;&lt;7)
DECL|macro|PGMASK_PAGE
mdefine_line|#define PGMASK_PAGE (PG_HUND | PG_TEN | PG_UNIT)
DECL|macro|PGMASK_HOUR
mdefine_line|#define PGMASK_HOUR (HR_TEN | HR_UNIT)
DECL|macro|PGMASK_MINUTE
mdefine_line|#define PGMASK_MINUTE (MIN_TEN | MIN_UNIT)
r_typedef
r_struct
(brace
DECL|member|page
r_int
id|page
suffix:semicolon
multiline_comment|/* number of requested page (hexadecimal) */
DECL|member|hour
r_int
id|hour
suffix:semicolon
multiline_comment|/* requested hour (hexadecimal) */
DECL|member|minute
r_int
id|minute
suffix:semicolon
multiline_comment|/* requested minute (hexadecimal) */
DECL|member|pagemask
r_int
id|pagemask
suffix:semicolon
multiline_comment|/* mask defining which values of the above are set */
DECL|member|pgbuf
r_int
id|pgbuf
suffix:semicolon
multiline_comment|/* buffer where page will be stored */
DECL|member|start
r_int
id|start
suffix:semicolon
multiline_comment|/* start of requested part of page */
DECL|member|end
r_int
id|end
suffix:semicolon
multiline_comment|/* end of requested part of page */
DECL|member|buffer
r_void
op_star
id|buffer
suffix:semicolon
multiline_comment|/* pointer to beginning of destination buffer */
)brace
DECL|typedef|vtx_pagereq_t
id|vtx_pagereq_t
suffix:semicolon
multiline_comment|/*&n; *&t;Definitions for VTXIOC{GETSTAT,PUTSTAT}&n; */
DECL|macro|VTX_PAGESIZE
mdefine_line|#define VTX_PAGESIZE (40 * 24)
DECL|macro|VTX_VIRTUALSIZE
mdefine_line|#define VTX_VIRTUALSIZE (40 * 49)
r_typedef
r_struct
(brace
DECL|member|pagenum
r_int
id|pagenum
suffix:semicolon
multiline_comment|/* number of page (hexadecimal) */
DECL|member|hour
r_int
id|hour
suffix:semicolon
multiline_comment|/* hour (hexadecimal) */
DECL|member|minute
r_int
id|minute
suffix:semicolon
multiline_comment|/* minute (hexadecimal) */
DECL|member|charset
r_int
id|charset
suffix:semicolon
multiline_comment|/* national charset */
DECL|member|delete
r_int
r_delete
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* delete page (C4) */
DECL|member|headline
r_int
id|headline
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* insert headline (C5) */
DECL|member|subtitle
r_int
id|subtitle
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* insert subtitle (C6) */
DECL|member|supp_header
r_int
id|supp_header
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* suppress header (C7) */
DECL|member|update
r_int
id|update
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* update page (C8) */
DECL|member|inter_seq
r_int
id|inter_seq
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* interrupted sequence (C9) */
DECL|member|dis_disp
r_int
id|dis_disp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* disable/suppress display (C10) */
DECL|member|serial
r_int
id|serial
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* serial mode (C11) */
DECL|member|notfound
r_int
id|notfound
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* /FOUND */
DECL|member|pblf
r_int
id|pblf
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* PBLF */
DECL|member|hamming
r_int
id|hamming
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* hamming-error occurred */
)brace
DECL|typedef|vtx_pageinfo_t
id|vtx_pageinfo_t
suffix:semicolon
multiline_comment|/*&n; *&t;Definitions for VTXIOCSETDISP&n; */
r_typedef
r_enum
(brace
DECL|enumerator|DISPOFF
DECL|enumerator|DISPNORM
DECL|enumerator|DISPTRANS
DECL|enumerator|DISPINS
DECL|enumerator|INTERLACE_OFFSET
id|DISPOFF
comma
id|DISPNORM
comma
id|DISPTRANS
comma
id|DISPINS
comma
id|INTERLACE_OFFSET
DECL|typedef|vtxdisp_t
)brace
id|vtxdisp_t
suffix:semicolon
multiline_comment|/*&n; *&t;Tuner ioctls&n; */
DECL|macro|TUNIOCGETINFO
mdefine_line|#define TUNIOCGETINFO  0x7201  /* get version of driver &amp; capabilities of tuner */
DECL|macro|TUNIOCRESET
mdefine_line|#define TUNIOCRESET    0x7202  /* reset tuner */
DECL|macro|TUNIOCSETFREQ
mdefine_line|#define TUNIOCSETFREQ  0x7203  /* set tuning frequency (unit: kHz) */
DECL|macro|TUNIOCGETFREQ
mdefine_line|#define TUNIOCGETFREQ  0x7204  /* get tuning frequency (unit: kHz) */
DECL|macro|TUNIOCSETCHAN
mdefine_line|#define TUNIOCSETCHAN  0x7205  /* set tuning channel */
DECL|macro|TUNIOCGETCHAN
mdefine_line|#define TUNIOCGETCHAN  0x7206  /* get tuning channel */
r_typedef
r_struct
(brace
DECL|member|version_major
DECL|member|version_minor
r_int
id|version_major
comma
id|version_minor
suffix:semicolon
multiline_comment|/* version of driver; if version_major changes, driver */
multiline_comment|/* is not backward compatible!!! CHECK THIS!!! */
DECL|member|freq
r_int
id|freq
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* tuner can be set to given frequency */
DECL|member|chan
r_int
id|chan
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* tuner stores several channels */
DECL|member|scan
r_int
id|scan
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* tuner supports scanning */
DECL|member|autoscan
r_int
id|autoscan
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* tuner supports scanning with automatic stop */
DECL|member|afc
r_int
id|afc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* tuner supports AFC */
DECL|member|dummy1
DECL|member|dummy2
DECL|member|dummy3
DECL|member|dummy4
DECL|member|dummy5
DECL|member|dummy6
DECL|member|dummy7
DECL|member|dummy8
DECL|member|dummy9
DECL|member|dummy10
r_int
id|dummy1
comma
id|dummy2
comma
id|dummy3
comma
id|dummy4
comma
id|dummy5
comma
id|dummy6
comma
id|dummy7
comma
id|dummy8
comma
id|dummy9
comma
id|dummy10
comma
DECL|member|dummy11
id|dummy11
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dummy12
DECL|member|dummy13
DECL|member|dummy14
DECL|member|dummy15
DECL|member|dummy16
DECL|member|dummy17
DECL|member|dummy18
DECL|member|dummy19
r_int
id|dummy12
comma
id|dummy13
comma
id|dummy14
comma
id|dummy15
comma
id|dummy16
comma
id|dummy17
comma
id|dummy18
comma
id|dummy19
suffix:semicolon
DECL|typedef|tuner_info_t
)brace
id|tuner_info_t
suffix:semicolon
macro_line|#endif /* _VTX_H */
eof
