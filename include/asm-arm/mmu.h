macro_line|#ifndef __ARM_MMU_H
DECL|macro|__ARM_MMU_H
mdefine_line|#define __ARM_MMU_H
macro_line|#include &lt;linux/config.h&gt;
r_typedef
r_struct
(brace
macro_line|#if __LINUX_ARM_ARCH__ &gt;= 6
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
macro_line|#endif
DECL|typedef|mm_context_t
)brace
id|mm_context_t
suffix:semicolon
macro_line|#if __LINUX_ARM_ARCH__ &gt;= 6
DECL|macro|ASID
mdefine_line|#define ASID(mm)&t;((mm)-&gt;context.id &amp; 255)
macro_line|#else
DECL|macro|ASID
mdefine_line|#define ASID(mm)&t;(0)
macro_line|#endif
macro_line|#endif
eof
