macro_line|#ifndef _ASMARM_SHMPARAM_H
DECL|macro|_ASMARM_SHMPARAM_H
mdefine_line|#define _ASMARM_SHMPARAM_H
multiline_comment|/*&n; * This should be the size of the virtually indexed cache/ways,&n; * or page size, whichever is greater since the cache aliases&n; * every size/ways bytes.&n; */
DECL|macro|SHMLBA
mdefine_line|#define&t;SHMLBA&t;(4 * PAGE_SIZE)&t;&t; /* attach addr a multiple of this */
multiline_comment|/*&n; * Enforce SHMLBA in shmat&n; */
DECL|macro|__ARCH_FORCE_SHMLBA
mdefine_line|#define __ARCH_FORCE_SHMLBA
macro_line|#endif /* _ASMARM_SHMPARAM_H */
eof
