multiline_comment|/* Copyright (c) 1996 by Manish Vachharajani */
macro_line|#ifndef _LINUX_VFC_IOCTLS_H_
DECL|macro|_LINUX_VFC_IOCTLS_H_
mdefine_line|#define&t;_LINUX_VFC_IOCTLS_H_
multiline_comment|/* IOCTLs */
DECL|macro|VFC_IOCTL
mdefine_line|#define VFC_IOCTL(a)          ((&squot;j&squot; &lt;&lt; 8) | a)
DECL|macro|VFCGCTRL
mdefine_line|#define VFCGCTRL&t;(VFC_IOCTL (0))&t;        /* get vfc attributes */
DECL|macro|VFCSCTRL
mdefine_line|#define VFCSCTRL&t;(VFC_IOCTL (1))  &t;/* set vfc attributes */
DECL|macro|VFCGVID
mdefine_line|#define VFCGVID&t;&t;(VFC_IOCTL (2)) &t;/* get video decoder attributes */
DECL|macro|VFCSVID
mdefine_line|#define VFCSVID&t;&t;(VFC_IOCTL (3))&t;        /* set video decoder attributes */
DECL|macro|VFCHUE
mdefine_line|#define VFCHUE&t;&t;(VFC_IOCTL (4))   &t;/* set hue */
DECL|macro|VFCPORTCHG
mdefine_line|#define VFCPORTCHG&t;(VFC_IOCTL (5))  &t;/* change port */
DECL|macro|VFCRDINFO
mdefine_line|#define VFCRDINFO&t;(VFC_IOCTL (6))  &t;/* read info */
multiline_comment|/* Options for setting the vfc attributes and status */
DECL|macro|MEMPRST
mdefine_line|#define MEMPRST&t;&t;0x1&t;/* reset FIFO ptr. */
DECL|macro|CAPTRCMD
mdefine_line|#define CAPTRCMD&t;0x2&t;/* start capture and wait */
DECL|macro|DIAGMODE
mdefine_line|#define DIAGMODE&t;0x3&t;/* diag mode */
DECL|macro|NORMMODE
mdefine_line|#define NORMMODE&t;0x4&t;/* normal mode */
DECL|macro|CAPTRSTR
mdefine_line|#define CAPTRSTR&t;0x5&t;/* start capture */
DECL|macro|CAPTRWAIT
mdefine_line|#define CAPTRWAIT&t;0x6&t;/* wait for capture to finish */
multiline_comment|/* Options for the decoder */
DECL|macro|STD_NTSC
mdefine_line|#define STD_NTSC&t;0x1&t;/* NTSC mode */
DECL|macro|STD_PAL
mdefine_line|#define STD_PAL&t;&t;0x2&t;/* PAL mode */
DECL|macro|COLOR_ON
mdefine_line|#define COLOR_ON&t;0x3&t;/* force color ON */
DECL|macro|MONO
mdefine_line|#define MONO&t;&t;0x4&t;/* force color OFF */
multiline_comment|/* Values returned by ioctl 2 */
DECL|macro|NO_LOCK
mdefine_line|#define NO_LOCK&t;        1
DECL|macro|NTSC_COLOR
mdefine_line|#define NTSC_COLOR&t;2
DECL|macro|NTSC_NOCOLOR
mdefine_line|#define NTSC_NOCOLOR    3
DECL|macro|PAL_COLOR
mdefine_line|#define PAL_COLOR&t;4
DECL|macro|PAL_NOCOLOR
mdefine_line|#define PAL_NOCOLOR&t;5
multiline_comment|/* Not too sure what this does yet */
multiline_comment|/* Options for setting Field number */
DECL|macro|ODD_FIELD
mdefine_line|#define ODD_FIELD&t;0x1
DECL|macro|EVEN_FIELD
mdefine_line|#define EVEN_FIELD&t;0x0
DECL|macro|ACTIVE_ONLY
mdefine_line|#define ACTIVE_ONLY     0x2
DECL|macro|NON_ACTIVE
mdefine_line|#define NON_ACTIVE&t;0x0
multiline_comment|/* Debug options */
DECL|macro|VFC_I2C_SEND
mdefine_line|#define VFC_I2C_SEND 0
DECL|macro|VFC_I2C_RECV
mdefine_line|#define VFC_I2C_RECV 1
DECL|struct|vfc_debug_inout
r_struct
id|vfc_debug_inout
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|ret
r_int
r_int
id|ret
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|buffer
r_int
r_char
op_star
id|buffer
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_VFC_IOCTLS_H_ */
eof
