macro_line|#ifndef _M68K_SEGMENT_H
DECL|macro|_M68K_SEGMENT_H
mdefine_line|#define _M68K_SEGMENT_H
multiline_comment|/* define constants */
multiline_comment|/* Address spaces (FC0-FC2) */
DECL|macro|USER_DATA
mdefine_line|#define USER_DATA     (1)
macro_line|#ifndef __USER_DS
DECL|macro|__USER_DS
mdefine_line|#define __USER_DS     (USER_DATA)
macro_line|#endif
DECL|macro|USER_PROGRAM
mdefine_line|#define USER_PROGRAM  (2)
DECL|macro|SUPER_DATA
mdefine_line|#define SUPER_DATA    (5)
macro_line|#ifndef __KERNEL_DS
DECL|macro|__KERNEL_DS
mdefine_line|#define __KERNEL_DS   (SUPER_DATA)
macro_line|#endif
DECL|macro|SUPER_PROGRAM
mdefine_line|#define SUPER_PROGRAM (6)
DECL|macro|CPU_SPACE
mdefine_line|#define CPU_SPACE     (7)
macro_line|#ifndef __ASSEMBLY__
r_typedef
r_struct
(brace
DECL|member|seg
r_int
r_int
id|seg
suffix:semicolon
DECL|typedef|mm_segment_t
)brace
id|mm_segment_t
suffix:semicolon
DECL|macro|MAKE_MM_SEG
mdefine_line|#define MAKE_MM_SEG(s)&t;((mm_segment_t) { (s) })
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;MAKE_MM_SEG(__USER_DS)
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;MAKE_MM_SEG(__KERNEL_DS)
multiline_comment|/*&n; * Get/set the SFC/DFC registers for MOVES instructions&n; */
DECL|function|get_fs
r_static
r_inline
id|mm_segment_t
id|get_fs
c_func
(paren
r_void
)paren
(brace
r_return
id|USER_DS
suffix:semicolon
)brace
DECL|function|get_ds
r_static
r_inline
id|mm_segment_t
id|get_ds
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* return the supervisor data space code */
r_return
id|KERNEL_DS
suffix:semicolon
)brace
DECL|function|set_fs
r_static
r_inline
r_void
id|set_fs
c_func
(paren
id|mm_segment_t
id|val
)paren
(brace
)brace
DECL|macro|segment_eq
mdefine_line|#define segment_eq(a,b)&t;((a).seg == (b).seg)
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _M68K_SEGMENT_H */
eof
