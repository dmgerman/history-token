macro_line|#ifndef _ASM_SEGMENT_H
DECL|macro|_ASM_SEGMENT_H
mdefine_line|#define _ASM_SEGMENT_H
multiline_comment|/* argh. really legacy. totally misnomed. */
DECL|macro|__KERNEL_CS
mdefine_line|#define __KERNEL_CS&t;0x10
DECL|macro|__KERNEL_DS
mdefine_line|#define __KERNEL_DS&t;0x18
DECL|macro|__USER_CS
mdefine_line|#define __USER_CS&t;0x23
DECL|macro|__USER_DS
mdefine_line|#define __USER_DS&t;0x2B
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
macro_line|#endif
eof
