multiline_comment|/*&n; *  include/asm-s390/resource.h&n; *&n; *  S390 version&n; *&n; *  Derived from &quot;include/asm-i386/resources.h&quot;&n; */
macro_line|#ifndef _S390_RESOURCE_H
DECL|macro|_S390_RESOURCE_H
mdefine_line|#define _S390_RESOURCE_H
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
DECL|macro|RLIMIT_NPROC
mdefine_line|#define RLIMIT_NPROC&t;6&t;&t;/* max number of processes */
DECL|macro|RLIMIT_NOFILE
mdefine_line|#define RLIMIT_NOFILE&t;7&t;&t;/* max number of open files */
DECL|macro|RLIMIT_MEMLOCK
mdefine_line|#define RLIMIT_MEMLOCK&t;8&t;&t;/* max locked-in-memory address space */
DECL|macro|RLIMIT_AS
mdefine_line|#define RLIMIT_AS&t;9&t;&t;/* address space limit */
DECL|macro|RLIMIT_LOCKS
mdefine_line|#define RLIMIT_LOCKS&t;10&t;&t;/* maximum file locks held */
DECL|macro|RLIM_NLIMITS
mdefine_line|#define RLIM_NLIMITS&t;11
multiline_comment|/*&n; * SuS says limits have to be unsigned.&n; * Which makes a ton more sense anyway.&n; */
DECL|macro|RLIM_INFINITY
mdefine_line|#define RLIM_INFINITY   (~0UL)
macro_line|#ifdef __KERNEL__
DECL|macro|INIT_RLIMITS
mdefine_line|#define INIT_RLIMITS&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{ RLIM_INFINITY, RLIM_INFINITY },&t;&t;&bslash;&n;&t;{ RLIM_INFINITY, RLIM_INFINITY },&t;&t;&bslash;&n;&t;{ RLIM_INFINITY, RLIM_INFINITY },&t;&t;&bslash;&n;&t;{      _STK_LIM, RLIM_INFINITY },&t;&t;&bslash;&n;&t;{             0, RLIM_INFINITY },&t;&t;&bslash;&n;&t;{ RLIM_INFINITY, RLIM_INFINITY },&t;&t;&bslash;&n;&t;{        0,        0 },                  &t;&bslash;&n;&t;{ INR_OPEN, INR_OPEN },                         &bslash;&n;&t;{ RLIM_INFINITY, RLIM_INFINITY },&t;&t;&bslash;&n;&t;{ RLIM_INFINITY, RLIM_INFINITY },&t;&t;&bslash;&n;&t;{ RLIM_INFINITY, RLIM_INFINITY },&t;&t;&bslash;&n;}
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
