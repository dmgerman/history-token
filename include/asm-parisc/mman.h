macro_line|#ifndef __PARISC_MMAN_H__
DECL|macro|__PARISC_MMAN_H__
mdefine_line|#define __PARISC_MMAN_H__
DECL|macro|PROT_READ
mdefine_line|#define PROT_READ&t;0x1&t;&t;/* page can be read */
DECL|macro|PROT_WRITE
mdefine_line|#define PROT_WRITE&t;0x2&t;&t;/* page can be written */
DECL|macro|PROT_EXEC
mdefine_line|#define PROT_EXEC&t;0x4&t;&t;/* page can be executed */
DECL|macro|PROT_NONE
mdefine_line|#define PROT_NONE&t;0x0&t;&t;/* page can not be accessed */
DECL|macro|MAP_SHARED
mdefine_line|#define MAP_SHARED&t;0x01&t;&t;/* Share changes */
DECL|macro|MAP_PRIVATE
mdefine_line|#define MAP_PRIVATE&t;0x02&t;&t;/* Changes are private */
DECL|macro|MAP_TYPE
mdefine_line|#define MAP_TYPE&t;0x03&t;&t;/* Mask for type of mapping */
DECL|macro|MAP_FIXED
mdefine_line|#define MAP_FIXED&t;0x04&t;&t;/* Interpret addr exactly */
DECL|macro|MAP_ANONYMOUS
mdefine_line|#define MAP_ANONYMOUS&t;0x10&t;&t;/* don&squot;t use a file */
DECL|macro|MAP_DENYWRITE
mdefine_line|#define MAP_DENYWRITE&t;0x0800&t;&t;/* ETXTBSY */
DECL|macro|MAP_EXECUTABLE
mdefine_line|#define MAP_EXECUTABLE&t;0x1000&t;&t;/* mark it as an executable */
DECL|macro|MAP_LOCKED
mdefine_line|#define MAP_LOCKED&t;0x2000&t;&t;/* pages are locked */
DECL|macro|MAP_NORESERVE
mdefine_line|#define MAP_NORESERVE&t;0x4000&t;&t;/* don&squot;t check for reservations */
DECL|macro|MAP_GROWSDOWN
mdefine_line|#define MAP_GROWSDOWN&t;0x8000&t;&t;/* stack-like segment */
DECL|macro|MS_SYNC
mdefine_line|#define MS_SYNC&t;&t;1&t;&t;/* synchronous memory sync */
DECL|macro|MS_ASYNC
mdefine_line|#define MS_ASYNC&t;2&t;&t;/* sync memory asynchronously */
DECL|macro|MS_INVALIDATE
mdefine_line|#define MS_INVALIDATE&t;4&t;&t;/* invalidate the caches */
DECL|macro|MCL_CURRENT
mdefine_line|#define MCL_CURRENT&t;1&t;&t;/* lock all current mappings */
DECL|macro|MCL_FUTURE
mdefine_line|#define MCL_FUTURE&t;2&t;&t;/* lock all future mappings */
DECL|macro|MADV_NORMAL
mdefine_line|#define MADV_NORMAL     0               /* no further special treatment */
DECL|macro|MADV_RANDOM
mdefine_line|#define MADV_RANDOM     1               /* expect random page references */
DECL|macro|MADV_SEQUENTIAL
mdefine_line|#define MADV_SEQUENTIAL 2               /* expect sequential page references */
DECL|macro|MADV_WILLNEED
mdefine_line|#define MADV_WILLNEED   3               /* will need these pages */
DECL|macro|MADV_DONTNEED
mdefine_line|#define MADV_DONTNEED   4               /* dont need these pages */
DECL|macro|MADV_SPACEAVAIL
mdefine_line|#define MADV_SPACEAVAIL 5               /* insure that resources are reserved */
DECL|macro|MADV_VPS_PURGE
mdefine_line|#define MADV_VPS_PURGE  6               /* Purge pages from VM page cache */
DECL|macro|MADV_VPS_INHERIT
mdefine_line|#define MADV_VPS_INHERIT 7              /* Inherit parents page size */
multiline_comment|/* The range 12-64 is reserved for page size specification. */
DECL|macro|MADV_4K_PAGES
mdefine_line|#define MADV_4K_PAGES   12              /* Use 4K pages  */
DECL|macro|MADV_16K_PAGES
mdefine_line|#define MADV_16K_PAGES  14              /* Use 16K pages */
DECL|macro|MADV_64K_PAGES
mdefine_line|#define MADV_64K_PAGES  16              /* Use 64K pages */
DECL|macro|MADV_256K_PAGES
mdefine_line|#define MADV_256K_PAGES 18              /* Use 256K pages */
DECL|macro|MADV_1M_PAGES
mdefine_line|#define MADV_1M_PAGES   20              /* Use 1 Megabyte pages */
DECL|macro|MADV_4M_PAGES
mdefine_line|#define MADV_4M_PAGES   22              /* Use 4 Megabyte pages */
DECL|macro|MADV_16M_PAGES
mdefine_line|#define MADV_16M_PAGES  24              /* Use 16 Megabyte pages */
DECL|macro|MADV_64M_PAGES
mdefine_line|#define MADV_64M_PAGES  26              /* Use 64 Megabyte pages */
multiline_comment|/* compatibility flags */
DECL|macro|MAP_ANON
mdefine_line|#define MAP_ANON&t;MAP_ANONYMOUS
DECL|macro|MAP_FILE
mdefine_line|#define MAP_FILE&t;0
DECL|macro|MAP_VARIABLE
mdefine_line|#define MAP_VARIABLE&t;0
macro_line|#endif /* __PARISC_MMAN_H__ */
eof
