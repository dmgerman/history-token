macro_line|#ifndef _LINUX_VIDEO_ENCODER_H
DECL|macro|_LINUX_VIDEO_ENCODER_H
mdefine_line|#define _LINUX_VIDEO_ENCODER_H
DECL|struct|video_encoder_capability
r_struct
id|video_encoder_capability
(brace
multiline_comment|/* this name is too long */
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|macro|VIDEO_ENCODER_PAL
mdefine_line|#define&t;VIDEO_ENCODER_PAL&t;1&t;/* can encode PAL signal */
DECL|macro|VIDEO_ENCODER_NTSC
mdefine_line|#define&t;VIDEO_ENCODER_NTSC&t;2&t;/* can encode NTSC */
DECL|macro|VIDEO_ENCODER_SECAM
mdefine_line|#define&t;VIDEO_ENCODER_SECAM&t;4&t;/* can encode SECAM */
DECL|macro|VIDEO_ENCODER_CCIR
mdefine_line|#define&t;VIDEO_ENCODER_CCIR&t;16&t;/* CCIR-601 pixel rate (720 pixels per line) instead of square pixel rate */
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
DECL|macro|ENCODER_GET_CAPABILITIES
mdefine_line|#define&t;ENCODER_GET_CAPABILITIES _IOR(&squot;e&squot;, 1, struct video_encoder_capability)
DECL|macro|ENCODER_SET_NORM
mdefine_line|#define&t;ENCODER_SET_NORM&t;_IOW(&squot;e&squot;, 2, int)
DECL|macro|ENCODER_SET_INPUT
mdefine_line|#define&t;ENCODER_SET_INPUT&t;_IOW(&squot;e&squot;, 3, int)&t;/* 0 &lt;= input &lt; #inputs */
DECL|macro|ENCODER_SET_OUTPUT
mdefine_line|#define&t;ENCODER_SET_OUTPUT&t;_IOW(&squot;e&squot;, 4, int)&t;/* 0 &lt;= output &lt; #outputs */
DECL|macro|ENCODER_ENABLE_OUTPUT
mdefine_line|#define&t;ENCODER_ENABLE_OUTPUT&t;_IOW(&squot;e&squot;, 5, int)&t;/* boolean output enable control */
macro_line|#endif
eof
