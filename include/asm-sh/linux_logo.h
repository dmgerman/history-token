multiline_comment|/* $Id: linux_logo.h,v 1.1 2000/06/10 21:45:48 yaegashi Exp $&n; * include/asm-sh/linux_logo.h: This is a linux logo&n; *                                to be displayed on boot.&n; *&n; * Copyright (C) 1996 Larry Ewing (lewing@isc.tamu.edu)&n; * Copyright (C) 1996 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; *&n; * You can put anything here, but:&n; * LINUX_LOGO_COLORS has to be less than 224&n; * image size has to be 80x80&n; * values have to start from 0x20&n; * (i.e. RGB(linux_logo_red[0],&n; *&t;     linux_logo_green[0],&n; *&t;     linux_logo_blue[0]) is color 0x20)&n; * BW image has to be 80x80 as well, with MS bit&n; * on the left&n; * Serial_console ascii image can be any size,&n; * but should contain %s to display the version&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/version.h&gt;
DECL|macro|linux_logo_banner
mdefine_line|#define linux_logo_banner &quot;Linux/SuperH version &quot; UTS_RELEASE
macro_line|#include &lt;linux/linux_logo.h&gt;
eof
