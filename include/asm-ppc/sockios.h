multiline_comment|/*&n; * BK Id: SCCS/s.sockios.h 1.5 05/17/01 18:14:25 cort&n; */
macro_line|#ifndef _ASM_PPC_SOCKIOS_H
DECL|macro|_ASM_PPC_SOCKIOS_H
mdefine_line|#define _ASM_PPC_SOCKIOS_H
macro_line|#if 0 /* These are defined this way on Alpha - maybe later. */
multiline_comment|/* Socket-level I/O control calls. */
mdefine_line|#define FIOGETOWN&t;_IOR(&squot;f&squot;, 123, int)
mdefine_line|#define FIOSETOWN &t;_IOW(&squot;f&squot;, 124, int)
mdefine_line|#define SIOCATMARK&t;_IOR(&squot;s&squot;, 7, int)
mdefine_line|#define SIOCSPGRP&t;_IOW(&squot;s&squot;, 8, pid_t)
mdefine_line|#define SIOCGPGRP&t;_IOR(&squot;s&squot;, 9, pid_t)
mdefine_line|#define SIOCGSTAMP&t;0x8906&t;&t;/* Get stamp - linux-specific */
macro_line|#endif
macro_line|#endif /* _ASM_PPC_SOCKIOS_H */
eof
