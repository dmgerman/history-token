macro_line|#ifndef __INCLUDED_SAA7146_V4L_V4L__
DECL|macro|__INCLUDED_SAA7146_V4L_V4L__
mdefine_line|#define __INCLUDED_SAA7146_V4L_V4L__
multiline_comment|/************************************************************************/
multiline_comment|/* ADDRESSING &t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|SAA7146_V4L_BASE
mdefine_line|#define SAA7146_V4L_BASE&t;100
DECL|macro|SAA7146_V4L_GPICT
mdefine_line|#define&t;SAA7146_V4L_GPICT&t;    &t;_IOW(&squot;d&squot;, (SAA7146_V4L_BASE+ 1), struct video_picture)
DECL|macro|SAA7146_V4L_SPICT
mdefine_line|#define&t;SAA7146_V4L_SPICT&t;    &t;_IOW(&squot;d&squot;, (SAA7146_V4L_BASE+ 2), struct video_picture)
DECL|macro|SAA7146_V4L_GFBUF
mdefine_line|#define&t;SAA7146_V4L_GFBUF&t;    &t;_IOW(&squot;d&squot;, (SAA7146_V4L_BASE+ 3), struct video_buffer)
DECL|macro|SAA7146_V4L_SFBUF
mdefine_line|#define&t;SAA7146_V4L_SFBUF&t;    &t;_IOW(&squot;d&squot;, (SAA7146_V4L_BASE+ 4), struct video_buffer)
DECL|macro|SAA7146_V4L_GMBUF
mdefine_line|#define&t;SAA7146_V4L_GMBUF&t;    &t;_IOW(&squot;d&squot;, (SAA7146_V4L_BASE+ 5), struct video_mbuf)
DECL|macro|SAA7146_V4L_SWIN
mdefine_line|#define&t;SAA7146_V4L_SWIN&t;    &t;_IOW(&squot;d&squot;, (SAA7146_V4L_BASE+ 6), struct video_window)
DECL|macro|SAA7146_V4L_CCAPTURE
mdefine_line|#define&t;SAA7146_V4L_CCAPTURE    &t;_IOW(&squot;d&squot;, (SAA7146_V4L_BASE+ 7), int)
DECL|macro|SAA7146_V4L_CMCAPTURE
mdefine_line|#define&t;SAA7146_V4L_CMCAPTURE&t;&t;_IOW(&squot;d&squot;, (SAA7146_V4L_BASE+ 8), struct video_mmap)
DECL|macro|SAA7146_V4L_CSYNC
mdefine_line|#define&t;SAA7146_V4L_CSYNC    &t;&t;_IOW(&squot;d&squot;, (SAA7146_V4L_BASE+ 9), int)
DECL|macro|SAA7146_V4L_CGSTATUS
mdefine_line|#define&t;SAA7146_V4L_CGSTATUS   &t;&t;_IOW(&squot;d&squot;, (SAA7146_V4L_BASE+10), int)
DECL|macro|SAA7146_V4L_TSCAPTURE
mdefine_line|#define&t;SAA7146_V4L_TSCAPTURE  &t;&t;_IOW(&squot;d&squot;, (SAA7146_V4L_BASE+11), int)
r_extern
r_int
id|saa7146_v4l_init
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|saa7146_v4l_exit
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
