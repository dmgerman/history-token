macro_line|#ifndef __LINUX_RADEONFB_H__
DECL|macro|__LINUX_RADEONFB_H__
mdefine_line|#define __LINUX_RADEONFB_H__
macro_line|#include &lt;asm/ioctl.h&gt;
macro_line|#include &lt;asm/types.h&gt;
DECL|macro|ATY_RADEON_LCD_ON
mdefine_line|#define ATY_RADEON_LCD_ON&t;0x00000001
DECL|macro|ATY_RADEON_CRT_ON
mdefine_line|#define ATY_RADEON_CRT_ON&t;0x00000002
DECL|macro|FBIO_RADEON_GET_MIRROR
mdefine_line|#define FBIO_RADEON_GET_MIRROR&t;_IOR(&squot;@&squot;, 3, size_t)
DECL|macro|FBIO_RADEON_SET_MIRROR
mdefine_line|#define FBIO_RADEON_SET_MIRROR&t;_IOW(&squot;@&squot;, 4, size_t)
macro_line|#endif
eof
