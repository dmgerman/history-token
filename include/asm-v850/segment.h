macro_line|#ifndef __V850_SEGMENT_H__
DECL|macro|__V850_SEGMENT_H__
mdefine_line|#define __V850_SEGMENT_H__
macro_line|#ifndef __ASSEMBLY__
DECL|typedef|mm_segment_t
r_typedef
r_int
r_int
id|mm_segment_t
suffix:semicolon
multiline_comment|/* domain register */
macro_line|#endif /* !__ASSEMBLY__ */
DECL|macro|__KERNEL_CS
mdefine_line|#define __KERNEL_CS&t;0x0
DECL|macro|__KERNEL_DS
mdefine_line|#define __KERNEL_DS&t;0x0
DECL|macro|__USER_CS
mdefine_line|#define __USER_CS&t;0x1
DECL|macro|__USER_DS
mdefine_line|#define __USER_DS&t;0x1
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;__KERNEL_DS
DECL|macro|KERNEL_CS
mdefine_line|#define KERNEL_CS&t;__KERNEL_CS
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;__USER_DS
DECL|macro|USER_CS
mdefine_line|#define USER_CS&t;&t;__USER_CS
DECL|macro|segment_eq
mdefine_line|#define segment_eq(a,b)&t;((a) == (b))
DECL|macro|get_ds
mdefine_line|#define get_ds()&t;(KERNEL_DS)
DECL|macro|get_fs
mdefine_line|#define get_fs()&t;(USER_DS)
DECL|macro|set_fs
mdefine_line|#define set_fs(seg)&t;((void)(seg))
DECL|macro|copy_segments
mdefine_line|#define copy_segments(task, mm)&t;((void)((void)(task), (mm)))
DECL|macro|release_segments
mdefine_line|#define release_segments(mm)&t;((void)(mm))
DECL|macro|forget_segments
mdefine_line|#define forget_segments()&t;((void)0)
macro_line|#endif /* __V850_SEGMENT_H__ */
eof
