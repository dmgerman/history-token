macro_line|#ifndef _LINUX_LINUX_LOGO_H
DECL|macro|_LINUX_LINUX_LOGO_H
mdefine_line|#define _LINUX_LINUX_LOGO_H
multiline_comment|/*&n; *  Linux logo to be displayed on boot&n; *&n; *  Copyright (C) 1996 Larry Ewing (lewing@isc.tamu.edu)&n; *  Copyright (C) 1996,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; *  Copyright (C) 2001 Greg Banks &lt;gnb@alphalink.com.au&gt;&n; *  Copyright (C) 2001 Jan-Benedict Glaw &lt;jbglaw@lug-owl.de&gt;&n; *  Copyright (C) 2003 Geert Uytterhoeven &lt;geert@linux-m68k.org&gt;&n; *&n; *  Serial_console ascii image can be any size,&n; *  but should contain %s to display the version&n; */
macro_line|#include &lt;linux/init.h&gt;
DECL|macro|LINUX_LOGO_MONO
mdefine_line|#define LINUX_LOGO_MONO&t;&t;1&t;/* monochrome black/white */
DECL|macro|LINUX_LOGO_VGA16
mdefine_line|#define LINUX_LOGO_VGA16&t;2&t;/* 16 colors VGA text palette */
DECL|macro|LINUX_LOGO_CLUT224
mdefine_line|#define LINUX_LOGO_CLUT224&t;3&t;/* 224 colors */
DECL|macro|LINUX_LOGO_GRAY256
mdefine_line|#define LINUX_LOGO_GRAY256&t;4&t;/* 256 levels grayscale */
DECL|struct|linux_logo
r_struct
id|linux_logo
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* one of LINUX_LOGO_* */
DECL|member|width
r_int
r_int
id|width
suffix:semicolon
DECL|member|height
r_int
r_int
id|height
suffix:semicolon
DECL|member|clutsize
r_int
r_int
id|clutsize
suffix:semicolon
multiline_comment|/* LINUX_LOGO_CLUT224 only */
DECL|member|clut
r_const
r_int
r_char
op_star
id|clut
suffix:semicolon
multiline_comment|/* LINUX_LOGO_CLUT224 only */
DECL|member|data
r_const
r_int
r_char
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_const
r_struct
id|linux_logo
op_star
id|__init
id|fb_find_logo
c_func
(paren
r_int
id|type
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_LINUX_LOGO_H */
eof
