macro_line|#ifndef _ASM_IA64_SHMPARAM_H
DECL|macro|_ASM_IA64_SHMPARAM_H
mdefine_line|#define _ASM_IA64_SHMPARAM_H
multiline_comment|/*&n; * SHMLBA controls minimum alignment at which shared memory segments&n; * get attached.  The IA-64 architecture says that there may be a&n; * performance degradation when there are virtual aliases within 1MB.&n; * To reduce the chance of this, we set SHMLBA to 1MB. --davidm 00/12/20&n; */
DECL|macro|SHMLBA
mdefine_line|#define&t;SHMLBA&t;(1024*1024)
macro_line|#endif /* _ASM_IA64_SHMPARAM_H */
eof
