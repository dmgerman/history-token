macro_line|#ifndef _LINUX_VIDEO_DECODER_H
DECL|macro|_LINUX_VIDEO_DECODER_H
mdefine_line|#define _LINUX_VIDEO_DECODER_H
DECL|struct|video_decoder_capability
r_struct
id|video_decoder_capability
(brace
multiline_comment|/* this name is too long */
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|macro|VIDEO_DECODER_PAL
mdefine_line|#define&t;VIDEO_DECODER_PAL&t;1&t;/* can decode PAL signal */
DECL|macro|VIDEO_DECODER_NTSC
mdefine_line|#define&t;VIDEO_DECODER_NTSC&t;2&t;/* can decode NTSC */
DECL|macro|VIDEO_DECODER_SECAM
mdefine_line|#define&t;VIDEO_DECODER_SECAM&t;4&t;/* can decode SECAM */
DECL|macro|VIDEO_DECODER_AUTO
mdefine_line|#define&t;VIDEO_DECODER_AUTO&t;8&t;/* can autosense norm */
DECL|macro|VIDEO_DECODER_CCIR
mdefine_line|#define&t;VIDEO_DECODER_CCIR&t;16&t;/* CCIR-601 pixel rate (720 pixels per line) instead of square pixel rate */
DECL|member|inputs
r_int
id|inputs
suffix:semicolon
multiline_comment|/* number of inputs */
DECL|member|outputs
r_int
id|outputs
suffix:semicolon
multiline_comment|/* number of outputs */
)brace
suffix:semicolon
multiline_comment|/*&n;DECODER_GET_STATUS returns the following flags.  The only one you need is&n;DECODER_STATUS_GOOD, the others are just nice things to know.&n;*/
DECL|macro|DECODER_STATUS_GOOD
mdefine_line|#define&t;DECODER_STATUS_GOOD&t;1&t;/* receiving acceptable input */
DECL|macro|DECODER_STATUS_COLOR
mdefine_line|#define&t;DECODER_STATUS_COLOR&t;2&t;/* receiving color information */
DECL|macro|DECODER_STATUS_PAL
mdefine_line|#define&t;DECODER_STATUS_PAL&t;4&t;/* auto detected */
DECL|macro|DECODER_STATUS_NTSC
mdefine_line|#define&t;DECODER_STATUS_NTSC&t;8&t;/* auto detected */
DECL|macro|DECODER_STATUS_SECAM
mdefine_line|#define&t;DECODER_STATUS_SECAM&t;16&t;/* auto detected */
DECL|macro|DECODER_GET_CAPABILITIES
mdefine_line|#define&t;DECODER_GET_CAPABILITIES _IOR(&squot;d&squot;, 1, struct video_decoder_capability)
DECL|macro|DECODER_GET_STATUS
mdefine_line|#define&t;DECODER_GET_STATUS    &t;_IOR(&squot;d&squot;, 2, int)
DECL|macro|DECODER_SET_NORM
mdefine_line|#define&t;DECODER_SET_NORM&t;_IOW(&squot;d&squot;, 3, int)
DECL|macro|DECODER_SET_INPUT
mdefine_line|#define&t;DECODER_SET_INPUT&t;_IOW(&squot;d&squot;, 4, int)&t;/* 0 &lt;= input &lt; #inputs */
DECL|macro|DECODER_SET_OUTPUT
mdefine_line|#define&t;DECODER_SET_OUTPUT&t;_IOW(&squot;d&squot;, 5, int)&t;/* 0 &lt;= output &lt; #outputs */
DECL|macro|DECODER_ENABLE_OUTPUT
mdefine_line|#define&t;DECODER_ENABLE_OUTPUT&t;_IOW(&squot;d&squot;, 6, int)&t;/* boolean output enable control */
DECL|macro|DECODER_SET_PICTURE
mdefine_line|#define&t;DECODER_SET_PICTURE   &t;_IOW(&squot;d&squot;, 7, struct video_picture)
DECL|macro|DECODER_DUMP
mdefine_line|#define&t;DECODER_DUMP&t;&t;_IO(&squot;d&squot;, 192)&t;&t;/* debug hook */
macro_line|#endif
eof
