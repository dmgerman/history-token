macro_line|#ifndef _M68K_CACHECTL_H
DECL|macro|_M68K_CACHECTL_H
mdefine_line|#define _M68K_CACHECTL_H
multiline_comment|/* Definitions for the cacheflush system call.  */
DECL|macro|FLUSH_SCOPE_LINE
mdefine_line|#define FLUSH_SCOPE_LINE    1&t;/* Flush a cache line */
DECL|macro|FLUSH_SCOPE_PAGE
mdefine_line|#define FLUSH_SCOPE_PAGE    2&t;/* Flush a page */
DECL|macro|FLUSH_SCOPE_ALL
mdefine_line|#define FLUSH_SCOPE_ALL     3&t;/* Flush the whole cache -- superuser only */
DECL|macro|FLUSH_CACHE_DATA
mdefine_line|#define FLUSH_CACHE_DATA    1&t;/* Writeback and flush data cache */
DECL|macro|FLUSH_CACHE_INSN
mdefine_line|#define FLUSH_CACHE_INSN    2&t;/* Flush instruction cache */
DECL|macro|FLUSH_CACHE_BOTH
mdefine_line|#define FLUSH_CACHE_BOTH    3&t;/* Flush both caches */
macro_line|#endif /* _M68K_CACHECTL_H */
eof
