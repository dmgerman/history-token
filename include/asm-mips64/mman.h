multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1999 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_MMAN_H
DECL|macro|_ASM_MMAN_H
mdefine_line|#define _ASM_MMAN_H
multiline_comment|/*&n; * Protections are chosen from these bits, OR&squot;d together.  The&n; * implementation does not necessarily support PROT_EXEC or PROT_WRITE&n; * without PROT_READ.  The only guarantees are that no writing will be&n; * allowed without PROT_WRITE and no access will be allowed for PROT_NONE.&n; */
DECL|macro|PROT_NONE
mdefine_line|#define PROT_NONE&t;0x0&t;&t;/* page can not be accessed */
DECL|macro|PROT_READ
mdefine_line|#define PROT_READ&t;0x1&t;&t;/* page can be read */
DECL|macro|PROT_WRITE
mdefine_line|#define PROT_WRITE&t;0x2&t;&t;/* page can be written */
DECL|macro|PROT_EXEC
mdefine_line|#define PROT_EXEC&t;0x4&t;&t;/* page can be executed */
multiline_comment|/*&n; * Flags for mmap&n; */
DECL|macro|MAP_SHARED
mdefine_line|#define MAP_SHARED&t;0x001&t;&t;/* Share changes */
DECL|macro|MAP_PRIVATE
mdefine_line|#define MAP_PRIVATE&t;0x002&t;&t;/* Changes are private */
DECL|macro|MAP_TYPE
mdefine_line|#define MAP_TYPE&t;0x00f&t;&t;/* Mask for type of mapping */
DECL|macro|MAP_FIXED
mdefine_line|#define MAP_FIXED&t;0x010&t;&t;/* Interpret addr exactly */
multiline_comment|/* not used by linux, but here to make sure we don&squot;t clash with ABI defines */
DECL|macro|MAP_RENAME
mdefine_line|#define MAP_RENAME&t;0x020&t;&t;/* Assign page to file */
DECL|macro|MAP_AUTOGROW
mdefine_line|#define MAP_AUTOGROW&t;0x040&t;&t;/* File may grow by writing */
DECL|macro|MAP_LOCAL
mdefine_line|#define MAP_LOCAL&t;0x080&t;&t;/* Copy on fork/sproc */
DECL|macro|MAP_AUTORSRV
mdefine_line|#define MAP_AUTORSRV&t;0x100&t;&t;/* Logical swap reserved on demand */
multiline_comment|/* These are linux-specific */
DECL|macro|MAP_NORESERVE
mdefine_line|#define MAP_NORESERVE&t;0x0400&t;&t;/* don&squot;t check for reservations */
DECL|macro|MAP_ANONYMOUS
mdefine_line|#define MAP_ANONYMOUS&t;0x0800&t;&t;/* don&squot;t use a file */
DECL|macro|MAP_GROWSDOWN
mdefine_line|#define MAP_GROWSDOWN&t;0x1000&t;&t;/* stack-like segment */
DECL|macro|MAP_DENYWRITE
mdefine_line|#define MAP_DENYWRITE&t;0x2000&t;&t;/* ETXTBSY */
DECL|macro|MAP_EXECUTABLE
mdefine_line|#define MAP_EXECUTABLE&t;0x4000&t;&t;/* mark it as an executable */
DECL|macro|MAP_LOCKED
mdefine_line|#define MAP_LOCKED&t;0x8000&t;&t;/* pages are locked */
multiline_comment|/*&n; * Flags for msync&n; */
DECL|macro|MS_ASYNC
mdefine_line|#define MS_ASYNC&t;0x0001&t;&t;/* sync memory asynchronously */
DECL|macro|MS_INVALIDATE
mdefine_line|#define MS_INVALIDATE&t;0x0002&t;&t;/* invalidate mappings &amp; caches */
DECL|macro|MS_SYNC
mdefine_line|#define MS_SYNC&t;&t;0x0004&t;&t;/* synchronous memory sync */
multiline_comment|/*&n; * Flags for mlockall&n; */
DECL|macro|MCL_CURRENT
mdefine_line|#define MCL_CURRENT&t;1&t;&t;/* lock all current mappings */
DECL|macro|MCL_FUTURE
mdefine_line|#define MCL_FUTURE&t;2&t;&t;/* lock all future mappings */
DECL|macro|MADV_NORMAL
mdefine_line|#define MADV_NORMAL&t;0x0&t;&t;/* default page-in behavior */
DECL|macro|MADV_RANDOM
mdefine_line|#define MADV_RANDOM&t;0x1&t;&t;/* page-in minimum required */
DECL|macro|MADV_SEQUENTIAL
mdefine_line|#define MADV_SEQUENTIAL&t;0x2&t;&t;/* read-ahead aggressively */
DECL|macro|MADV_WILLNEED
mdefine_line|#define MADV_WILLNEED&t;0x3&t;&t;/* pre-fault pages */
DECL|macro|MADV_DONTNEED
mdefine_line|#define MADV_DONTNEED&t;0x4&t;&t;/* discard these pages */
multiline_comment|/* compatibility flags */
DECL|macro|MAP_ANON
mdefine_line|#define MAP_ANON       MAP_ANONYMOUS
DECL|macro|MAP_FILE
mdefine_line|#define MAP_FILE       0
macro_line|#endif /* _ASM_MMAN_H */
eof
