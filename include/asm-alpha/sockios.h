macro_line|#ifndef _ASM_ALPHA_SOCKIOS_H
DECL|macro|_ASM_ALPHA_SOCKIOS_H
mdefine_line|#define _ASM_ALPHA_SOCKIOS_H
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
mdefine_line|#define SIOCGSTAMP&t;0x8906&t;&t;/* Get stamp - linux-specific */
macro_line|#endif /* _ASM_ALPHA_SOCKIOS_H */
eof
