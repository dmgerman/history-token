macro_line|#ifndef _H8300_CACHECTL_H
DECL|macro|_H8300_CACHECTL_H
mdefine_line|#define _H8300_CACHECTL_H
multiline_comment|/* Definitions for the cacheflush system call.  */
DECL|macro|FLUSH_SCOPE_LINE
mdefine_line|#define FLUSH_SCOPE_LINE    0&t;/* Flush a cache line */
DECL|macro|FLUSH_SCOPE_PAGE
mdefine_line|#define FLUSH_SCOPE_PAGE    0&t;/* Flush a page */
DECL|macro|FLUSH_SCOPE_ALL
mdefine_line|#define FLUSH_SCOPE_ALL     0&t;/* Flush the whole cache -- superuser only */
DECL|macro|FLUSH_CACHE_DATA
mdefine_line|#define FLUSH_CACHE_DATA    0&t;/* Writeback and flush data cache */
DECL|macro|FLUSH_CACHE_INSN
mdefine_line|#define FLUSH_CACHE_INSN    0&t;/* Flush instruction cache */
DECL|macro|FLUSH_CACHE_BOTH
mdefine_line|#define FLUSH_CACHE_BOTH    0&t;/* Flush both caches */
macro_line|#endif /* _H8300_CACHECTL_H */
eof
