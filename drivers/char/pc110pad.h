macro_line|#ifndef _PC110PAD_H
DECL|macro|_PC110PAD_H
mdefine_line|#define _PC110PAD_H
macro_line|#include &lt;linux/ioctl.h&gt;
DECL|enum|pc110pad_mode
r_enum
id|pc110pad_mode
(brace
DECL|enumerator|PC110PAD_RAW
id|PC110PAD_RAW
comma
multiline_comment|/* bytes as they come out of the hardware */
DECL|enumerator|PC110PAD_RARE
id|PC110PAD_RARE
comma
multiline_comment|/* debounced up/down and absolute x,y */
DECL|enumerator|PC110PAD_DEBUG
id|PC110PAD_DEBUG
comma
multiline_comment|/* up/down, debounced, transitions, button */
DECL|enumerator|PC110PAD_PS2
id|PC110PAD_PS2
comma
multiline_comment|/* ps2 relative (default) */
)brace
suffix:semicolon
DECL|struct|pc110pad_params
r_struct
id|pc110pad_params
(brace
DECL|member|mode
r_enum
id|pc110pad_mode
id|mode
suffix:semicolon
DECL|member|bounce_interval
r_int
id|bounce_interval
suffix:semicolon
DECL|member|tap_interval
r_int
id|tap_interval
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|io
r_int
id|io
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MS
mdefine_line|#define MS *HZ/1000
multiline_comment|/* Appears as device major=10 (MISC), minor=PC110_PAD */
DECL|macro|PC110PAD_IOCTL_TYPE
mdefine_line|#define PC110PAD_IOCTL_TYPE&t;&t;0x9a
DECL|macro|PC110PADIOCGETP
mdefine_line|#define PC110PADIOCGETP _IOR(PC110PAD_IOCTL_TYPE, 0, struct pc110pad_params)
DECL|macro|PC110PADIOCSETP
mdefine_line|#define PC110PADIOCSETP _IOW(PC110PAD_IOCTL_TYPE, 1, struct pc110pad_params)
macro_line|#endif /* _PC110PAD_H */
eof
