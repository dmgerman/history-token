multiline_comment|/*&n; *  linux/include/asm-arm/linux_logo.h&n; *&n; *  Copyright (C) 1998 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Linux console driver logo definitions for ARM&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/version.h&gt;
DECL|macro|linux_logo_banner
mdefine_line|#define linux_logo_banner &quot;ARM Linux version &quot; UTS_RELEASE
DECL|macro|LINUX_LOGO_COLORS
mdefine_line|#define LINUX_LOGO_COLORS&t;214
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
id|linux_logo16
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
op_star
id|linux_serial_image
suffix:semicolon
r_extern
r_int
(paren
op_star
id|console_show_logo
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
