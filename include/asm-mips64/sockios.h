multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1999 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_SOCKIOS_H
DECL|macro|_ASM_SOCKIOS_H
mdefine_line|#define _ASM_SOCKIOS_H
macro_line|#include &lt;asm/ioctl.h&gt;
multiline_comment|/* Socket-level I/O control calls. */
DECL|macro|FIOGETOWN
mdefine_line|#define FIOGETOWN&t;_IOR(&squot;f&squot;, 123, int)
DECL|macro|FIOSETOWN
mdefine_line|#define FIOSETOWN &t;_IOW(&squot;f&squot;, 124, int)
DECL|macro|SIOCATMARK
mdefine_line|#define SIOCATMARK&t;_IOR(&squot;s&squot;, 7, int)
DECL|macro|SIOCSPGRP
mdefine_line|#define SIOCSPGRP&t;_IOW(&squot;s&squot;, 8, pid_t)
DECL|macro|SIOCGPGRP
mdefine_line|#define SIOCGPGRP&t;_IOR(&squot;s&squot;, 9, pid_t)
DECL|macro|SIOCGSTAMP
mdefine_line|#define SIOCGSTAMP&t;0x8906&t;&t;&t;/* Get stamp - linux-specific */
macro_line|#endif /* _ASM_SOCKIOS_H */
eof
