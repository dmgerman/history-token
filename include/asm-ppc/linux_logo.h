multiline_comment|/*&n; * include/asm-ppc/linux_logo.h: A linux logo to be displayed on boot&n; * (pinched from the sparc port).&n; *&n; * Copyright (C) 1996 Larry Ewing (lewing@isc.tamu.edu)&n; * Copyright (C) 1996 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; *&n; * You can put anything here, but:&n; * LINUX_LOGO_COLORS has to be less than 224&n; * values have to start from 0x20&n; * (i.e. linux_logo_{red,green,blue}[0] is color 0x20)&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/init.h&gt;
DECL|macro|linux_logo_banner
mdefine_line|#define linux_logo_banner &quot;Linux/PPC version &quot; UTS_RELEASE
DECL|macro|LINUX_LOGO_HEIGHT
mdefine_line|#define LINUX_LOGO_HEIGHT&t;80
DECL|macro|LINUX_LOGO_WIDTH
mdefine_line|#define LINUX_LOGO_WIDTH&t;80
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
macro_line|#endif /* __KERNEL__ */
eof
