multiline_comment|/*&n; *  include/asm-s390x/extmem.h&n; *&n; *  definitions for external memory segment support&n; *  Copyright (C) 2003 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; */
macro_line|#ifndef _ASM_S390X_DCSS_H
DECL|macro|_ASM_S390X_DCSS_H
mdefine_line|#define _ASM_S390X_DCSS_H
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* possible values for segment type as returned by segment_info */
DECL|macro|SEG_TYPE_SW
mdefine_line|#define SEG_TYPE_SW 0
DECL|macro|SEG_TYPE_EW
mdefine_line|#define SEG_TYPE_EW 1
DECL|macro|SEG_TYPE_SR
mdefine_line|#define SEG_TYPE_SR 2
DECL|macro|SEG_TYPE_ER
mdefine_line|#define SEG_TYPE_ER 3
DECL|macro|SEG_TYPE_SN
mdefine_line|#define SEG_TYPE_SN 4
DECL|macro|SEG_TYPE_EN
mdefine_line|#define SEG_TYPE_EN 5
DECL|macro|SEG_TYPE_SC
mdefine_line|#define SEG_TYPE_SC 6
DECL|macro|SEG_TYPE_EWEN
mdefine_line|#define SEG_TYPE_EWEN 7
DECL|macro|SEGMENT_SHARED
mdefine_line|#define SEGMENT_SHARED 0
DECL|macro|SEGMENT_EXCLUSIVE
mdefine_line|#define SEGMENT_EXCLUSIVE 1
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
id|segment_save
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_int
id|segment_type
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_int
id|segment_modify_shared
(paren
r_char
op_star
id|name
comma
r_int
id|do_nonshared
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
