macro_line|#ifndef _ASM_IA64_SOCKIOS_H
DECL|macro|_ASM_IA64_SOCKIOS_H
mdefine_line|#define _ASM_IA64_SOCKIOS_H
multiline_comment|/*&n; * Socket-level I/O control calls.  This mostly mirrors the Linux/x86&n; * version.&n; *&n; * Copyright (C) 1998, 1999 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
DECL|macro|FIOSETOWN
mdefine_line|#define FIOSETOWN &t;0x8901
DECL|macro|SIOCSPGRP
mdefine_line|#define SIOCSPGRP&t;0x8902
DECL|macro|FIOGETOWN
mdefine_line|#define FIOGETOWN&t;0x8903
DECL|macro|SIOCGPGRP
mdefine_line|#define SIOCGPGRP&t;0x8904
DECL|macro|SIOCATMARK
mdefine_line|#define SIOCATMARK&t;0x8905
DECL|macro|SIOCGSTAMP
mdefine_line|#define SIOCGSTAMP&t;0x8906&t;&t;/* Get stamp */
macro_line|#endif /* _ASM_IA64_SOCKIOS_H */
eof
