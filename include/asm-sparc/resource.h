multiline_comment|/* $Id: resource.h,v 1.12 2000/09/23 02:09:21 davem Exp $&n; * resource.h: Resource definitions.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_RESOURCE_H
DECL|macro|_SPARC_RESOURCE_H
mdefine_line|#define _SPARC_RESOURCE_H
multiline_comment|/*&n; * These two resource limit IDs have a Sparc/Linux-specific ordering,&n; * the rest comes from the generic header:&n; */
DECL|macro|RLIMIT_NOFILE
mdefine_line|#define RLIMIT_NOFILE&t;&t;6&t;/* max number of open files */
DECL|macro|RLIMIT_NPROC
mdefine_line|#define RLIMIT_NPROC&t;&t;7&t;/* max number of processes */
multiline_comment|/*&n; * SuS says limits have to be unsigned.&n; * We make this unsigned, but keep the&n; * old value for compatibility:&n; */
DECL|macro|RLIM_INFINITY
mdefine_line|#define RLIM_INFINITY&t;&t;0x7fffffff
macro_line|#include &lt;asm-generic/resource.h&gt;
macro_line|#endif /* !(_SPARC_RESOURCE_H) */
eof
