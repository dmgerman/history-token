multiline_comment|/*&n; * BK Id: SCCS/s.linux_logo.h 1.7 05/17/01 18:14:24 cort&n; */
multiline_comment|/*&n; * include/asm-ppc/linux_logo.h: A linux logo to be displayed on boot&n; * (pinched from the sparc port).&n; *&n; * Copyright (C) 1996 Larry Ewing (lewing@isc.tamu.edu)&n; * Copyright (C) 1996 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; *&n; * You can put anything here, but:&n; * LINUX_LOGO_COLORS has to be less than 224&n; * values have to start from 0x20&n; * (i.e. linux_logo_{red,green,blue}[0] is color 0x20)&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/init.h&gt;
DECL|macro|linux_logo_banner
mdefine_line|#define linux_logo_banner &quot;Linux/PPC version &quot; UTS_RELEASE
DECL|macro|LINUX_LOGO_HEIGHT
mdefine_line|#define LINUX_LOGO_HEIGHT&t;80
DECL|macro|LINUX_LOGO_WIDTH
mdefine_line|#define LINUX_LOGO_WIDTH&t;80
macro_line|#include &lt;linux/linux_logo.h&gt;
macro_line|#endif /* __KERNEL__ */
eof
