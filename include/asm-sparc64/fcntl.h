multiline_comment|/* $Id: fcntl.h,v 1.12 2001/09/20 00:35:34 davem Exp $ */
macro_line|#ifndef _SPARC64_FCNTL_H
DECL|macro|_SPARC64_FCNTL_H
mdefine_line|#define _SPARC64_FCNTL_H
multiline_comment|/* open/fcntl - O_SYNC is only implemented on blocks devices and on files&n;   located on an ext2 file system */
DECL|macro|O_RDONLY
mdefine_line|#define O_RDONLY&t;0x0000
DECL|macro|O_WRONLY
mdefine_line|#define O_WRONLY&t;0x0001
DECL|macro|O_RDWR
mdefine_line|#define O_RDWR&t;&t;0x0002
DECL|macro|O_ACCMODE
mdefine_line|#define O_ACCMODE&t;0x0003
DECL|macro|O_NDELAY
mdefine_line|#define O_NDELAY&t;0x0004
DECL|macro|O_APPEND
mdefine_line|#define O_APPEND&t;0x0008
DECL|macro|FASYNC
mdefine_line|#define FASYNC&t;&t;0x0040&t;/* fcntl, for BSD compatibility */
DECL|macro|O_CREAT
mdefine_line|#define O_CREAT&t;&t;0x0200&t;/* not fcntl */
DECL|macro|O_TRUNC
mdefine_line|#define O_TRUNC&t;&t;0x0400&t;/* not fcntl */
DECL|macro|O_EXCL
mdefine_line|#define O_EXCL&t;&t;0x0800&t;/* not fcntl */
DECL|macro|O_SYNC
mdefine_line|#define O_SYNC&t;&t;0x2000
DECL|macro|O_NONBLOCK
mdefine_line|#define O_NONBLOCK&t;0x4000
DECL|macro|O_NOCTTY
mdefine_line|#define O_NOCTTY&t;0x8000&t;/* not fcntl */
DECL|macro|O_DIRECTORY
mdefine_line|#define O_DIRECTORY&t;0x10000&t;/* must be a directory */
DECL|macro|O_NOFOLLOW
mdefine_line|#define O_NOFOLLOW&t;0x20000&t;/* don&squot;t follow links */
DECL|macro|O_LARGEFILE
mdefine_line|#define O_LARGEFILE&t;0x40000
DECL|macro|O_DIRECT
mdefine_line|#define O_DIRECT        0x100000 /* direct disk access hint */
DECL|macro|F_DUPFD
mdefine_line|#define F_DUPFD&t;&t;0&t;/* dup */
DECL|macro|F_GETFD
mdefine_line|#define F_GETFD&t;&t;1&t;/* get close_on_exec */
DECL|macro|F_SETFD
mdefine_line|#define F_SETFD&t;&t;2&t;/* set/clear close_on_exec */
DECL|macro|F_GETFL
mdefine_line|#define F_GETFL&t;&t;3&t;/* get file-&gt;f_flags */
DECL|macro|F_SETFL
mdefine_line|#define F_SETFL&t;&t;4&t;/* set file-&gt;f_flags */
DECL|macro|F_GETOWN
mdefine_line|#define F_GETOWN&t;5&t;/*  for sockets. */
DECL|macro|F_SETOWN
mdefine_line|#define F_SETOWN&t;6&t;/*  for sockets. */
DECL|macro|F_GETLK
mdefine_line|#define F_GETLK&t;&t;7
DECL|macro|F_SETLK
mdefine_line|#define F_SETLK&t;&t;8
DECL|macro|F_SETLKW
mdefine_line|#define F_SETLKW&t;9
DECL|macro|F_SETSIG
mdefine_line|#define F_SETSIG&t;10&t;/*  for sockets. */
DECL|macro|F_GETSIG
mdefine_line|#define F_GETSIG&t;11&t;/*  for sockets. */
macro_line|#ifdef __KERNEL__
DECL|macro|F_GETLK64
mdefine_line|#define F_GETLK64&t;12
DECL|macro|F_SETLK64
mdefine_line|#define F_SETLK64&t;13
DECL|macro|F_SETLKW64
mdefine_line|#define F_SETLKW64&t;14
macro_line|#endif
multiline_comment|/* for F_[GET|SET]FL */
DECL|macro|FD_CLOEXEC
mdefine_line|#define FD_CLOEXEC&t;1&t;/* actually anything with low bit set goes */
multiline_comment|/* for posix fcntl() and lockf() */
DECL|macro|F_RDLCK
mdefine_line|#define F_RDLCK&t;&t;1
DECL|macro|F_WRLCK
mdefine_line|#define F_WRLCK&t;&t;2
DECL|macro|F_UNLCK
mdefine_line|#define F_UNLCK&t;&t;3
multiline_comment|/* for old implementation of bsd flock () */
DECL|macro|F_EXLCK
mdefine_line|#define F_EXLCK&t;&t;4&t;/* or 3 */
DECL|macro|F_SHLCK
mdefine_line|#define F_SHLCK&t;&t;8&t;/* or 4 */
multiline_comment|/* for leases */
DECL|macro|F_INPROGRESS
mdefine_line|#define F_INPROGRESS&t;16
multiline_comment|/* operations for bsd flock(), also used by the kernel implementation */
DECL|macro|LOCK_SH
mdefine_line|#define LOCK_SH&t;&t;1&t;/* shared lock */
DECL|macro|LOCK_EX
mdefine_line|#define LOCK_EX&t;&t;2&t;/* exclusive lock */
DECL|macro|LOCK_NB
mdefine_line|#define LOCK_NB&t;&t;4&t;/* or&squot;d with one of the above to prevent&n;&t;&t;&t;&t;   blocking */
DECL|macro|LOCK_UN
mdefine_line|#define LOCK_UN&t;&t;8&t;/* remove lock */
DECL|macro|LOCK_MAND
mdefine_line|#define LOCK_MAND&t;32&t;/* This is a mandatory flock */
DECL|macro|LOCK_READ
mdefine_line|#define LOCK_READ&t;64&t;/* ... Which allows concurrent read operations */
DECL|macro|LOCK_WRITE
mdefine_line|#define LOCK_WRITE&t;128&t;/* ... Which allows concurrent write operations */
DECL|macro|LOCK_RW
mdefine_line|#define LOCK_RW&t;&t;192&t;/* ... Which allows concurrent read &amp; write ops */
DECL|struct|flock
r_struct
id|flock
(brace
DECL|member|l_type
r_int
id|l_type
suffix:semicolon
DECL|member|l_whence
r_int
id|l_whence
suffix:semicolon
DECL|member|l_start
id|off_t
id|l_start
suffix:semicolon
DECL|member|l_len
id|off_t
id|l_len
suffix:semicolon
DECL|member|l_pid
id|pid_t
id|l_pid
suffix:semicolon
DECL|member|__unused
r_int
id|__unused
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|macro|flock64
mdefine_line|#define flock64&t;flock
macro_line|#endif
DECL|macro|F_LINUX_SPECIFIC_BASE
mdefine_line|#define F_LINUX_SPECIFIC_BASE&t;1024
macro_line|#endif /* !(_SPARC64_FCNTL_H) */
eof
