multiline_comment|/*&n; * include/asm-ppc64/linux_logo.h: A linux logo to be displayed on boot&n; * (pinched from the sparc port).&n; *&n; * Copyright (C) 1996 Larry Ewing (lewing@isc.tamu.edu)&n; * Copyright (C) 1996 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; *&n; * You can put anything here, but:&n; * LINUX_LOGO_COLORS has to be less than 224&n; * values have to start from 0x20&n; * (i.e. linux_logo_{red,green,blue}[0] is color 0x20)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/init.h&gt;
DECL|macro|linux_logo_banner
mdefine_line|#define linux_logo_banner &quot;Linux/PPC-64 version &quot; UTS_RELEASE
DECL|macro|LINUX_LOGO_HEIGHT
mdefine_line|#define LINUX_LOGO_HEIGHT&t;80
DECL|macro|LINUX_LOGO_WIDTH
mdefine_line|#define LINUX_LOGO_WIDTH&t;80
macro_line|#include &lt;linux/linux_logo.h&gt;
eof
