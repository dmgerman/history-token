macro_line|#ifndef _VTX_H
DECL|macro|_VTX_H
mdefine_line|#define _VTX_H
multiline_comment|/*&n; * Teletext (=Videotext) hardware decoders using interface /dev/vtx&n; * Do not confuse with drivers using /dev/vbi which decode videotext by software&n; *&n; * Videotext IOCTLs changed in order to use _IO() macros defined in &lt;linux/ioctl.h&gt;,&n; * unused tuner IOCTLs cleaned up by&n; * Michael Geng &lt;linux@MichaelGeng.de&gt;&n; *&n; * Copyright (c) 1994-97 Martin Buck  &lt;martin-2.buck@student.uni-ulm.de&gt;&n; * Read COPYING for more information&n; *&n; */
multiline_comment|/*&n; *&t;Videotext ioctls&n; */
DECL|macro|VTXIOCGETINFO
mdefine_line|#define VTXIOCGETINFO&t;_IOR  (0x81,  1, vtx_info_t)
DECL|macro|VTXIOCCLRPAGE
mdefine_line|#define VTXIOCCLRPAGE&t;_IOW  (0x81,  2, vtx_pagereq_t)
DECL|macro|VTXIOCCLRFOUND
mdefine_line|#define VTXIOCCLRFOUND&t;_IOW  (0x81,  3, vtx_pagereq_t)
DECL|macro|VTXIOCPAGEREQ
mdefine_line|#define VTXIOCPAGEREQ&t;_IOW  (0x81,  4, vtx_pagereq_t)
DECL|macro|VTXIOCGETSTAT
mdefine_line|#define VTXIOCGETSTAT&t;_IOW  (0x81,  5, vtx_pagereq_t)
DECL|macro|VTXIOCGETPAGE
mdefine_line|#define VTXIOCGETPAGE&t;_IOW  (0x81,  6, vtx_pagereq_t)
DECL|macro|VTXIOCSTOPDAU
mdefine_line|#define VTXIOCSTOPDAU&t;_IOW  (0x81,  7, vtx_pagereq_t)
DECL|macro|VTXIOCPUTPAGE
mdefine_line|#define VTXIOCPUTPAGE&t;_IO   (0x81,  8)
DECL|macro|VTXIOCSETDISP
mdefine_line|#define VTXIOCSETDISP&t;_IO   (0x81,  9)
DECL|macro|VTXIOCPUTSTAT
mdefine_line|#define VTXIOCPUTSTAT&t;_IO   (0x81, 10)
DECL|macro|VTXIOCCLRCACHE
mdefine_line|#define VTXIOCCLRCACHE&t;_IO   (0x81, 11)
DECL|macro|VTXIOCSETVIRT
mdefine_line|#define VTXIOCSETVIRT&t;_IOW  (0x81, 12, long)
multiline_comment|/* for compatibility, will go away some day */
DECL|macro|VTXIOCGETINFO_OLD
mdefine_line|#define VTXIOCGETINFO_OLD  0x7101  /* get version of driver &amp; capabilities of vtx-chipset */
DECL|macro|VTXIOCCLRPAGE_OLD
mdefine_line|#define VTXIOCCLRPAGE_OLD  0x7102  /* clear page-buffer */
DECL|macro|VTXIOCCLRFOUND_OLD
mdefine_line|#define VTXIOCCLRFOUND_OLD 0x7103  /* clear bits indicating that page was found */
DECL|macro|VTXIOCPAGEREQ_OLD
mdefine_line|#define VTXIOCPAGEREQ_OLD  0x7104  /* search for page */
DECL|macro|VTXIOCGETSTAT_OLD
mdefine_line|#define VTXIOCGETSTAT_OLD  0x7105  /* get status of page-buffer */
DECL|macro|VTXIOCGETPAGE_OLD
mdefine_line|#define VTXIOCGETPAGE_OLD  0x7106  /* get contents of page-buffer */
DECL|macro|VTXIOCSTOPDAU_OLD
mdefine_line|#define VTXIOCSTOPDAU_OLD  0x7107  /* stop data acquisition unit */
DECL|macro|VTXIOCPUTPAGE_OLD
mdefine_line|#define VTXIOCPUTPAGE_OLD  0x7108  /* display page on TV-screen */
DECL|macro|VTXIOCSETDISP_OLD
mdefine_line|#define VTXIOCSETDISP_OLD  0x7109  /* set TV-mode */
DECL|macro|VTXIOCPUTSTAT_OLD
mdefine_line|#define VTXIOCPUTSTAT_OLD  0x710a  /* set status of TV-output-buffer */
DECL|macro|VTXIOCCLRCACHE_OLD
mdefine_line|#define VTXIOCCLRCACHE_OLD 0x710b  /* clear cache on VTX-interface (if avail.) */
DECL|macro|VTXIOCSETVIRT_OLD
mdefine_line|#define VTXIOCSETVIRT_OLD  0x710c  /* turn on virtual mode (this disables TV-display) */
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
id|__user
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
macro_line|#endif /* _VTX_H */
eof
