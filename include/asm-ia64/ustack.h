macro_line|#ifndef _ASM_IA64_USTACK_H
DECL|macro|_ASM_IA64_USTACK_H
mdefine_line|#define _ASM_IA64_USTACK_H
multiline_comment|/*&n; * Constants for the user stack size&n; */
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/* The absolute hard limit for stack size is 1/2 of the mappable space in the region */
DECL|macro|MAX_USER_STACK_SIZE
mdefine_line|#define MAX_USER_STACK_SIZE&t;(RGN_MAP_LIMIT/2)
multiline_comment|/* Make a default stack size of 2GB */
DECL|macro|DEFAULT_USER_STACK_SIZE
mdefine_line|#define DEFAULT_USER_STACK_SIZE&t;(1UL &lt;&lt; 31)
DECL|macro|STACK_TOP
mdefine_line|#define STACK_TOP&t;&t;(0x6000000000000000UL + RGN_MAP_LIMIT)
macro_line|#endif /* _ASM_IA64_USTACK_H */
eof
