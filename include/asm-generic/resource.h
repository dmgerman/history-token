macro_line|#ifndef _ASM_GENERIC_RESOURCE_H
DECL|macro|_ASM_GENERIC_RESOURCE_H
mdefine_line|#define _ASM_GENERIC_RESOURCE_H
multiline_comment|/*&n; * Resource limit IDs&n; *&n; * ( Compatibility detail: there are architectures that have&n; *   a different rlimit ID order in the 5-9 range and want&n; *   to keep that order for binary compatibility. The reasons&n; *   are historic and all new rlimits are identical across all&n; *   arches. If an arch has such special order for some rlimits&n; *   then it defines them prior including asm-generic/resource.h. )&n; */
DECL|macro|RLIMIT_CPU
mdefine_line|#define RLIMIT_CPU&t;&t;0&t;/* CPU time in ms */
DECL|macro|RLIMIT_FSIZE
mdefine_line|#define RLIMIT_FSIZE&t;&t;1&t;/* Maximum filesize */
DECL|macro|RLIMIT_DATA
mdefine_line|#define RLIMIT_DATA&t;&t;2&t;/* max data size */
DECL|macro|RLIMIT_STACK
mdefine_line|#define RLIMIT_STACK&t;&t;3&t;/* max stack size */
DECL|macro|RLIMIT_CORE
mdefine_line|#define RLIMIT_CORE&t;&t;4&t;/* max core file size */
macro_line|#ifndef RLIMIT_RSS
DECL|macro|RLIMIT_RSS
macro_line|# define RLIMIT_RSS&t;&t;5&t;/* max resident set size */
macro_line|#endif
macro_line|#ifndef RLIMIT_NPROC
DECL|macro|RLIMIT_NPROC
macro_line|# define RLIMIT_NPROC&t;&t;6&t;/* max number of processes */
macro_line|#endif
macro_line|#ifndef RLIMIT_NOFILE
DECL|macro|RLIMIT_NOFILE
macro_line|# define RLIMIT_NOFILE&t;&t;7&t;/* max number of open files */
macro_line|#endif
macro_line|#ifndef RLIMIT_MEMLOCK
DECL|macro|RLIMIT_MEMLOCK
macro_line|# define RLIMIT_MEMLOCK&t;&t;8&t;/* max locked-in-memory address space */
macro_line|#endif
macro_line|#ifndef RLIMIT_AS
DECL|macro|RLIMIT_AS
macro_line|# define RLIMIT_AS&t;&t;9&t;/* address space limit */
macro_line|#endif
DECL|macro|RLIMIT_LOCKS
mdefine_line|#define RLIMIT_LOCKS&t;&t;10&t;/* maximum file locks held */
DECL|macro|RLIMIT_SIGPENDING
mdefine_line|#define RLIMIT_SIGPENDING&t;11&t;/* max number of pending signals */
DECL|macro|RLIMIT_MSGQUEUE
mdefine_line|#define RLIMIT_MSGQUEUE&t;&t;12&t;/* maximum bytes in POSIX mqueues */
DECL|macro|RLIM_NLIMITS
mdefine_line|#define RLIM_NLIMITS&t;&t;13
multiline_comment|/*&n; * SuS says limits have to be unsigned.&n; * Which makes a ton more sense anyway.&n; *&n; * Some architectures override this (for compatibility reasons):&n; */
macro_line|#ifndef RLIM_INFINITY
DECL|macro|RLIM_INFINITY
macro_line|# define RLIM_INFINITY&t;&t;(~0UL)
macro_line|#endif
multiline_comment|/*&n; * RLIMIT_STACK default maximum - some architectures override it:&n; */
macro_line|#ifndef _STK_LIM_MAX
DECL|macro|_STK_LIM_MAX
macro_line|# define _STK_LIM_MAX&t;&t;RLIM_INFINITY
macro_line|#endif
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * boot-time rlimit defaults for the init task:&n; */
DECL|macro|INIT_RLIMITS
mdefine_line|#define INIT_RLIMITS&t;&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;[RLIMIT_CPU]&t;&t;= {  RLIM_INFINITY,  RLIM_INFINITY },&t;&bslash;&n;&t;[RLIMIT_FSIZE]&t;&t;= {  RLIM_INFINITY,  RLIM_INFINITY },&t;&bslash;&n;&t;[RLIMIT_DATA]&t;&t;= {  RLIM_INFINITY,  RLIM_INFINITY },&t;&bslash;&n;&t;[RLIMIT_STACK]&t;&t;= {       _STK_LIM,   _STK_LIM_MAX },&t;&bslash;&n;&t;[RLIMIT_CORE]&t;&t;= {              0,  RLIM_INFINITY },&t;&bslash;&n;&t;[RLIMIT_RSS]&t;&t;= {  RLIM_INFINITY,  RLIM_INFINITY },&t;&bslash;&n;&t;[RLIMIT_NPROC]&t;&t;= {              0,              0 },&t;&bslash;&n;&t;[RLIMIT_NOFILE]&t;&t;= {       INR_OPEN,       INR_OPEN },&t;&bslash;&n;&t;[RLIMIT_MEMLOCK]&t;= {    MLOCK_LIMIT,    MLOCK_LIMIT },&t;&bslash;&n;&t;[RLIMIT_AS]&t;&t;= {  RLIM_INFINITY,  RLIM_INFINITY },&t;&bslash;&n;&t;[RLIMIT_LOCKS]&t;&t;= {  RLIM_INFINITY,  RLIM_INFINITY },&t;&bslash;&n;&t;[RLIMIT_SIGPENDING]&t;= { MAX_SIGPENDING, MAX_SIGPENDING },&t;&bslash;&n;&t;[RLIMIT_MSGQUEUE]&t;= {   MQ_BYTES_MAX,   MQ_BYTES_MAX },&t;&bslash;&n;}
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif
eof
