macro_line|#ifndef __ARCH_M68K_SOCKIOS__
DECL|macro|__ARCH_M68K_SOCKIOS__
mdefine_line|#define __ARCH_M68K_SOCKIOS__
multiline_comment|/* Socket-level I/O control calls. */
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
macro_line|#endif /* __ARCH_M68K_SOCKIOS__ */
eof
