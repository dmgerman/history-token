multiline_comment|/* const.h: Macros for dealing with constants.  */
macro_line|#ifndef _SPARC64_CONST_H
DECL|macro|_SPARC64_CONST_H
mdefine_line|#define _SPARC64_CONST_H
multiline_comment|/* Some constant macros are used in both assembler and&n; * C code.  Therefore we cannot annotate them always with&n; * &squot;UL&squot; and other type specificers unilaterally.  We&n; * use the following macros to deal with this.&n; */
macro_line|#ifdef __ASSEMBLY__
DECL|macro|_AC
mdefine_line|#define _AC(X,Y)&t;X
macro_line|#else
DECL|macro|_AC
mdefine_line|#define _AC(X,Y)&t;(X##Y)
macro_line|#endif
macro_line|#endif /* !(_SPARC64_CONST_H) */
eof
