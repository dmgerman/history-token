multiline_comment|/*&n; *  include/asm-s390x/extmem.h&n; *&n; *  definitions for external memory segment support&n; *  Copyright (C) 2003 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; */
macro_line|#ifndef _ASM_S390X_DCSS_H
DECL|macro|_ASM_S390X_DCSS_H
mdefine_line|#define _ASM_S390X_DCSS_H
macro_line|#ifndef __ASSEMBLY__
DECL|macro|SEGMENT_SHARED_RW
mdefine_line|#define SEGMENT_SHARED_RW       0
DECL|macro|SEGMENT_SHARED_RO
mdefine_line|#define SEGMENT_SHARED_RO       1
DECL|macro|SEGMENT_EXCLUSIVE_RW
mdefine_line|#define SEGMENT_EXCLUSIVE_RW    2
DECL|macro|SEGMENT_EXCLUSIVE_RO
mdefine_line|#define SEGMENT_EXCLUSIVE_RO    3
r_extern
r_int
id|segment_load
(paren
r_char
op_star
id|name
comma
r_int
id|segtype
comma
r_int
r_int
op_star
id|addr
comma
r_int
r_int
op_star
id|length
)paren
suffix:semicolon
r_extern
r_void
id|segment_unload
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|segment_replace
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
