macro_line|#ifndef _ASMARM_SHMPARAM_H
DECL|macro|_ASMARM_SHMPARAM_H
mdefine_line|#define _ASMARM_SHMPARAM_H
macro_line|#include &lt;asm/proc/shmparam.h&gt;
multiline_comment|/*&n; * This should be the size of the virtually indexed cache/ways,&n; * or page size, whichever is greater since the cache aliases&n; * every size/ways bytes.&n; */
DECL|macro|SHMLBA
mdefine_line|#define&t;SHMLBA PAGE_SIZE&t;&t; /* attach addr a multiple of this */
macro_line|#endif /* _ASMARM_SHMPARAM_H */
eof
