macro_line|#ifndef _CRIS_ARCH_TLB_H
DECL|macro|_CRIS_ARCH_TLB_H
mdefine_line|#define _CRIS_ARCH_TLB_H
multiline_comment|/* The TLB can host up to 64 different mm contexts at the same time.&n; * The last page_id is never running - it is used as an invalid page_id&n; * so we can make TLB entries that will never match. &n; */
DECL|macro|NUM_TLB_ENTRIES
mdefine_line|#define NUM_TLB_ENTRIES 64
DECL|macro|NUM_PAGEID
mdefine_line|#define NUM_PAGEID 64
DECL|macro|INVALID_PAGEID
mdefine_line|#define INVALID_PAGEID 63
DECL|macro|NO_CONTEXT
mdefine_line|#define NO_CONTEXT -1
macro_line|#endif
eof
