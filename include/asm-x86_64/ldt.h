multiline_comment|/*&n; * ldt.h&n; *&n; * Definitions of structures used with the modify_ldt system call.&n; */
macro_line|#ifndef _LINUX_LDT_H
DECL|macro|_LINUX_LDT_H
mdefine_line|#define _LINUX_LDT_H
multiline_comment|/* Maximum number of LDT entries supported. */
DECL|macro|LDT_ENTRIES
mdefine_line|#define LDT_ENTRIES&t;8192
multiline_comment|/* The size of each LDT entry. */
DECL|macro|LDT_ENTRY_SIZE
mdefine_line|#define LDT_ENTRY_SIZE&t;8
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Note on 64bit base and limit is ignored and you cannot set&n;   DS/ES/CS not to the default values if you still want to do syscalls. This&n;   call is more for 32bit mode therefore. */
DECL|struct|modify_ldt_ldt_s
r_struct
id|modify_ldt_ldt_s
(brace
DECL|member|entry_number
r_int
r_int
id|entry_number
suffix:semicolon
DECL|member|base_addr
r_int
r_int
id|base_addr
suffix:semicolon
DECL|member|limit
r_int
r_int
id|limit
suffix:semicolon
DECL|member|seg_32bit
r_int
r_int
id|seg_32bit
suffix:colon
l_int|1
suffix:semicolon
DECL|member|contents
r_int
r_int
id|contents
suffix:colon
l_int|2
suffix:semicolon
DECL|member|read_exec_only
r_int
r_int
id|read_exec_only
suffix:colon
l_int|1
suffix:semicolon
DECL|member|limit_in_pages
r_int
r_int
id|limit_in_pages
suffix:colon
l_int|1
suffix:semicolon
DECL|member|seg_not_present
r_int
r_int
id|seg_not_present
suffix:colon
l_int|1
suffix:semicolon
DECL|member|useable
r_int
r_int
id|useable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|lm
r_int
r_int
id|lm
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MODIFY_LDT_CONTENTS_DATA
mdefine_line|#define MODIFY_LDT_CONTENTS_DATA&t;0
DECL|macro|MODIFY_LDT_CONTENTS_STACK
mdefine_line|#define MODIFY_LDT_CONTENTS_STACK&t;1
DECL|macro|MODIFY_LDT_CONTENTS_CODE
mdefine_line|#define MODIFY_LDT_CONTENTS_CODE&t;2
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif
eof
