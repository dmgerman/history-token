multiline_comment|/* $Id: head.h,v 1.30 1997/08/08 08:34:33 jj Exp $ */
macro_line|#ifndef _SPARC64_HEAD_H
DECL|macro|_SPARC64_HEAD_H
mdefine_line|#define _SPARC64_HEAD_H
macro_line|#include &lt;asm/pstate.h&gt;
DECL|macro|KERNBASE
mdefine_line|#define KERNBASE&t;0x400000
DECL|macro|PTREGS_OFF
mdefine_line|#define&t;PTREGS_OFF&t;(STACK_BIAS + REGWIN_SZ)
macro_line|#endif /* !(_SPARC64_HEAD_H) */
eof
