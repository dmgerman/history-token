macro_line|#ifndef _ALPHA_RESOURCE_H
DECL|macro|_ALPHA_RESOURCE_H
mdefine_line|#define _ALPHA_RESOURCE_H
multiline_comment|/*&n; * Resource limits&n; */
DECL|macro|RLIMIT_CPU
mdefine_line|#define RLIMIT_CPU&t;0&t;&t;/* CPU time in ms */
DECL|macro|RLIMIT_FSIZE
mdefine_line|#define RLIMIT_FSIZE&t;1&t;&t;/* Maximum filesize */
DECL|macro|RLIMIT_DATA
mdefine_line|#define RLIMIT_DATA&t;2&t;&t;/* max data size */
DECL|macro|RLIMIT_STACK
mdefine_line|#define RLIMIT_STACK&t;3&t;&t;/* max stack size */
DECL|macro|RLIMIT_CORE
mdefine_line|#define RLIMIT_CORE&t;4&t;&t;/* max core file size */
DECL|macro|RLIMIT_RSS
mdefine_line|#define RLIMIT_RSS&t;5&t;&t;/* max resident set size */
DECL|macro|RLIMIT_NOFILE
mdefine_line|#define RLIMIT_NOFILE&t;6&t;&t;/* max number of open files */
DECL|macro|RLIMIT_AS
mdefine_line|#define RLIMIT_AS&t;7&t;&t;/* address space limit(?) */
DECL|macro|RLIMIT_NPROC
mdefine_line|#define RLIMIT_NPROC&t;8&t;&t;/* max number of processes */
DECL|macro|RLIMIT_MEMLOCK
mdefine_line|#define RLIMIT_MEMLOCK&t;9&t;&t;/* max locked-in-memory address space */
DECL|macro|RLIMIT_LOCKS
mdefine_line|#define RLIMIT_LOCKS   10              /* maximum file locks held */
DECL|macro|RLIM_NLIMITS
mdefine_line|#define RLIM_NLIMITS&t;11
multiline_comment|/*&n; * SuS says limits have to be unsigned.  Fine, it&squot;s unsigned, but&n; * we retain the old value for compatibility, especially with DU. &n; * When you run into the 2^63 barrier, you call me.&n; */
DECL|macro|RLIM_INFINITY
mdefine_line|#define RLIM_INFINITY&t;0x7ffffffffffffffful
macro_line|#ifdef __KERNEL__
DECL|macro|INIT_RLIMITS
mdefine_line|#define INIT_RLIMITS&t;&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    {LONG_MAX, LONG_MAX},&t;&t;&t;/* RLIMIT_CPU */&t;&bslash;&n;    {LONG_MAX, LONG_MAX},&t;&t;&t;/* RLIMIT_FSIZE */&t;&bslash;&n;    {LONG_MAX, LONG_MAX},&t;&t;&t;/* RLIMIT_DATA */&t;&bslash;&n;    {_STK_LIM, LONG_MAX},&t;&t;&t;/* RLIMIT_STACK */&t;&bslash;&n;    {       0, LONG_MAX},&t;&t;&t;/* RLIMIT_CORE */&t;&bslash;&n;    {LONG_MAX, LONG_MAX},&t;&t;&t;/* RLIMIT_RSS */&t;&bslash;&n;    {INR_OPEN, INR_OPEN},&t;&t;&t;/* RLIMIT_NOFILE */&t;&bslash;&n;    {LONG_MAX, LONG_MAX},&t;&t;&t;/* RLIMIT_AS */&t;&t;&bslash;&n;    {LONG_MAX, LONG_MAX},&t;&t;&t;/* RLIMIT_NPROC */&t;&bslash;&n;    {LONG_MAX, LONG_MAX},&t;&t;&t;/* RLIMIT_MEMLOCK */&t;&bslash;&n;    {LONG_MAX, LONG_MAX},                       /* RLIMIT_LOCKS */      &bslash;&n;}
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ALPHA_RESOURCE_H */
eof
