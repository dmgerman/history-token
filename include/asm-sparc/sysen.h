multiline_comment|/* $Id: sysen.h,v 1.3 1995/11/25 02:32:58 davem Exp $&n; * sysen.h:  Bit fields within the &quot;System Enable&quot; register accessed via&n; *           the ASI_CONTROL address space at address AC_SYSENABLE.&n; *&n; * Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_SYSEN_H
DECL|macro|_SPARC_SYSEN_H
mdefine_line|#define _SPARC_SYSEN_H
DECL|macro|SENABLE_DVMA
mdefine_line|#define SENABLE_DVMA   0x20   /* enable dvma transfers */
DECL|macro|SENABLE_CACHE
mdefine_line|#define SENABLE_CACHE  0x10   /* enable VAC cache */
DECL|macro|SENABLE_RESET
mdefine_line|#define SENABLE_RESET  0x04   /* reset whole machine, danger Will Robinson */
macro_line|#endif /* _SPARC_SYSEN_H */
eof
