multiline_comment|/* $Id: linux_logo.h,v 1.6 1998/07/30 16:30:20 jj Exp $&n; * include/asm-alpha/linux_logo.h: This is a linux logo&n; *                                 to be displayed on boot.&n; *&n; * Copyright (C) 1996 Larry Ewing (lewing@isc.tamu.edu)&n; * Copyright (C) 1996 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; *&n; * You can put anything here, but:&n; * LINUX_LOGO_COLORS has to be less than 224&n; * image size has to be 80x80&n; * values have to start from 0x20&n; * (i.e. RGB(linux_logo_red[0],&n; *&t;     linux_logo_green[0],&n; *&t;     linux_logo_blue[0]) is color 0x20)&n; * BW image has to be 80x80 as well, with MS bit&n; * on the left&n; * Serial_console ascii image can be any size,&n; * but should contain %s to display the version&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/version.h&gt;
DECL|macro|linux_logo_banner
mdefine_line|#define linux_logo_banner &quot;Linux/AXP version &quot; UTS_RELEASE
DECL|macro|LINUX_LOGO_COLORS
mdefine_line|#define LINUX_LOGO_COLORS 214
macro_line|#ifdef INCLUDE_LINUX_LOGO_DATA
DECL|macro|INCLUDE_LINUX_LOGOBW
mdefine_line|#define INCLUDE_LINUX_LOGOBW
DECL|macro|INCLUDE_LINUX_LOGO16
mdefine_line|#define INCLUDE_LINUX_LOGO16
macro_line|#include &lt;linux/linux_logo.h&gt;
macro_line|#else
multiline_comment|/* prototypes only */
r_extern
r_int
r_char
id|linux_logo_red
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|linux_logo_green
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|linux_logo_blue
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|linux_logo
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|linux_logo_bw
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|linux_logo16_red
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|linux_logo16_green
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|linux_logo16_blue
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|linux_logo16
(braket
)braket
suffix:semicolon
macro_line|#endif
eof
