multiline_comment|/* $Id: resource.h,v 1.8 2000/09/23 02:09:21 davem Exp $&n; * resource.h: Resource definitions.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC64_RESOURCE_H
DECL|macro|_SPARC64_RESOURCE_H
mdefine_line|#define _SPARC64_RESOURCE_H
multiline_comment|/*&n; * These two resource limit IDs have a Sparc/Linux-specific ordering,&n; * the rest comes from the generic header:&n; */
DECL|macro|RLIMIT_NOFILE
mdefine_line|#define RLIMIT_NOFILE&t;&t;6&t;/* max number of open files */
DECL|macro|RLIMIT_NPROC
mdefine_line|#define RLIMIT_NPROC&t;&t;7&t;/* max number of processes */
macro_line|#include &lt;asm-generic/resource.h&gt;
macro_line|#endif /* !(_SPARC64_RESOURCE_H) */
eof
