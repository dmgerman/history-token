multiline_comment|/* $Id: resource.h,v 1.12 2000/09/23 02:09:21 davem Exp $&n; * resource.h: Resource definitions.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_RESOURCE_H
DECL|macro|_SPARC_RESOURCE_H
mdefine_line|#define _SPARC_RESOURCE_H
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
DECL|macro|RLIMIT_NPROC
mdefine_line|#define RLIMIT_NPROC&t;7&t;&t;/* max number of processes */
DECL|macro|RLIMIT_MEMLOCK
mdefine_line|#define RLIMIT_MEMLOCK  8               /* max locked-in-memory address space */
DECL|macro|RLIMIT_AS
mdefine_line|#define RLIMIT_AS       9               /* address space limit */
DECL|macro|RLIMIT_LOCKS
mdefine_line|#define RLIMIT_LOCKS&t;10&t;&t;/* maximum file locks held */
DECL|macro|RLIM_NLIMITS
mdefine_line|#define RLIM_NLIMITS&t;11
multiline_comment|/*&n; * SuS says limits have to be unsigned.&n; * We make this unsigned, but keep the&n; * old value.&n; */
DECL|macro|RLIM_INFINITY
mdefine_line|#define RLIM_INFINITY&t;0x7fffffff
macro_line|#ifdef __KERNEL__
DECL|macro|INIT_RLIMITS
mdefine_line|#define INIT_RLIMITS&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&bslash;&n;    {RLIM_INFINITY, RLIM_INFINITY},&t;&bslash;&n;    {RLIM_INFINITY, RLIM_INFINITY},&t;&bslash;&n;    {RLIM_INFINITY, RLIM_INFINITY},&t;&bslash;&n;    {_STK_LIM, RLIM_INFINITY},&t;&t;&bslash;&n;    {       0, RLIM_INFINITY},&t;&t;&bslash;&n;    {RLIM_INFINITY, RLIM_INFINITY},&t;&bslash;&n;    {INR_OPEN, INR_OPEN}, {0, 0},&t;&bslash;&n;    {RLIM_INFINITY, RLIM_INFINITY},&t;&bslash;&n;    {RLIM_INFINITY, RLIM_INFINITY},&t;&bslash;&n;    {RLIM_INFINITY, RLIM_INFINITY}&t;&bslash;&n;}
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* !(_SPARC_RESOURCE_H) */
eof
