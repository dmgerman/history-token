macro_line|#ifndef __ALPHA_MMAN_H__
DECL|macro|__ALPHA_MMAN_H__
mdefine_line|#define __ALPHA_MMAN_H__
DECL|macro|PROT_READ
mdefine_line|#define PROT_READ&t;0x1&t;&t;/* page can be read */
DECL|macro|PROT_WRITE
mdefine_line|#define PROT_WRITE&t;0x2&t;&t;/* page can be written */
DECL|macro|PROT_EXEC
mdefine_line|#define PROT_EXEC&t;0x4&t;&t;/* page can be executed */
DECL|macro|PROT_SEM
mdefine_line|#define PROT_SEM&t;0x8&t;&t;/* page may be used for atomic ops */
DECL|macro|PROT_NONE
mdefine_line|#define PROT_NONE&t;0x0&t;&t;/* page can not be accessed */
DECL|macro|MAP_SHARED
mdefine_line|#define MAP_SHARED&t;0x01&t;&t;/* Share changes */
DECL|macro|MAP_PRIVATE
mdefine_line|#define MAP_PRIVATE&t;0x02&t;&t;/* Changes are private */
DECL|macro|MAP_TYPE
mdefine_line|#define MAP_TYPE&t;0x0f&t;&t;/* Mask for type of mapping (OSF/1 is _wrong_) */
DECL|macro|MAP_FIXED
mdefine_line|#define MAP_FIXED&t;0x100&t;&t;/* Interpret addr exactly */
DECL|macro|MAP_ANONYMOUS
mdefine_line|#define MAP_ANONYMOUS&t;0x10&t;&t;/* don&squot;t use a file */
multiline_comment|/* not used by linux, but here to make sure we don&squot;t clash with OSF/1 defines */
DECL|macro|_MAP_HASSEMAPHORE
mdefine_line|#define _MAP_HASSEMAPHORE 0x0200
DECL|macro|_MAP_INHERIT
mdefine_line|#define _MAP_INHERIT&t;0x0400
DECL|macro|_MAP_UNALIGNED
mdefine_line|#define _MAP_UNALIGNED&t;0x0800
multiline_comment|/* These are linux-specific */
DECL|macro|MAP_GROWSDOWN
mdefine_line|#define MAP_GROWSDOWN&t;0x1000&t;&t;/* stack-like segment */
DECL|macro|MAP_DENYWRITE
mdefine_line|#define MAP_DENYWRITE&t;0x2000&t;&t;/* ETXTBSY */
DECL|macro|MAP_EXECUTABLE
mdefine_line|#define MAP_EXECUTABLE&t;0x4000&t;&t;/* mark it as an executable */
DECL|macro|MAP_LOCKED
mdefine_line|#define MAP_LOCKED&t;0x8000&t;&t;/* lock the mapping */
DECL|macro|MAP_NORESERVE
mdefine_line|#define MAP_NORESERVE&t;0x10000&t;&t;/* don&squot;t check for reservations */
DECL|macro|MS_ASYNC
mdefine_line|#define MS_ASYNC&t;1&t;&t;/* sync memory asynchronously */
DECL|macro|MS_SYNC
mdefine_line|#define MS_SYNC&t;&t;2&t;&t;/* synchronous memory sync */
DECL|macro|MS_INVALIDATE
mdefine_line|#define MS_INVALIDATE&t;4&t;&t;/* invalidate the caches */
DECL|macro|MCL_CURRENT
mdefine_line|#define MCL_CURRENT&t; 8192&t;&t;/* lock all currently mapped pages */
DECL|macro|MCL_FUTURE
mdefine_line|#define MCL_FUTURE&t;16384&t;&t;/* lock all additions to address space */
DECL|macro|MADV_NORMAL
mdefine_line|#define MADV_NORMAL&t;0&t;&t;/* no further special treatment */
DECL|macro|MADV_RANDOM
mdefine_line|#define MADV_RANDOM&t;1&t;&t;/* expect random page references */
DECL|macro|MADV_SEQUENTIAL
mdefine_line|#define MADV_SEQUENTIAL&t;2&t;&t;/* expect sequential page references */
DECL|macro|MADV_WILLNEED
mdefine_line|#define MADV_WILLNEED&t;3&t;&t;/* will need these pages */
DECL|macro|MADV_SPACEAVAIL
mdefine_line|#define&t;MADV_SPACEAVAIL&t;5&t;&t;/* ensure resources are available */
DECL|macro|MADV_DONTNEED
mdefine_line|#define MADV_DONTNEED&t;6&t;&t;/* dont need these pages */
multiline_comment|/* compatibility flags */
DECL|macro|MAP_ANON
mdefine_line|#define MAP_ANON&t;MAP_ANONYMOUS
DECL|macro|MAP_FILE
mdefine_line|#define MAP_FILE&t;0
macro_line|#endif /* __ALPHA_MMAN_H__ */
eof
