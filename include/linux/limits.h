macro_line|#ifndef _LINUX_LIMITS_H
DECL|macro|_LINUX_LIMITS_H
mdefine_line|#define _LINUX_LIMITS_H
DECL|macro|NR_OPEN
mdefine_line|#define NR_OPEN&t;        1024
DECL|macro|NGROUPS_MAX
mdefine_line|#define NGROUPS_MAX       32&t;/* supplemental group IDs are available */
DECL|macro|ARG_MAX
mdefine_line|#define ARG_MAX       131072&t;/* # bytes of args + environ for exec() */
DECL|macro|CHILD_MAX
mdefine_line|#define CHILD_MAX        999    /* no limit :-) */
DECL|macro|OPEN_MAX
mdefine_line|#define OPEN_MAX         256&t;/* # open files a process may have */
DECL|macro|LINK_MAX
mdefine_line|#define LINK_MAX         127&t;/* # links a file may have */
DECL|macro|MAX_CANON
mdefine_line|#define MAX_CANON        255&t;/* size of the canonical input queue */
DECL|macro|MAX_INPUT
mdefine_line|#define MAX_INPUT        255&t;/* size of the type-ahead buffer */
DECL|macro|NAME_MAX
mdefine_line|#define NAME_MAX         255&t;/* # chars in a file name */
DECL|macro|PATH_MAX
mdefine_line|#define PATH_MAX        4096&t;/* # chars in a path name including nul */
DECL|macro|PIPE_BUF
mdefine_line|#define PIPE_BUF        4096&t;/* # bytes in atomic write to a pipe */
DECL|macro|XATTR_NAME_MAX
mdefine_line|#define XATTR_NAME_MAX   255&t;/* # chars in an extended attribute name */
DECL|macro|XATTR_SIZE_MAX
mdefine_line|#define XATTR_SIZE_MAX 65536&t;/* size of an extended attribute value (64k) */
DECL|macro|XATTR_LIST_MAX
mdefine_line|#define XATTR_LIST_MAX 65536&t;/* size of extended attribute namelist (64k) */
DECL|macro|RTSIG_MAX
mdefine_line|#define RTSIG_MAX&t;  32
macro_line|#endif
eof
