multiline_comment|/* ANSI and traditional C compatability macros&n;   Copyright 1991, 1992 Free Software Foundation, Inc.&n;   This file is part of the GNU C Library.&n;&n;This program is free software; you can redistribute it and/or modify&n;it under the terms of the GNU General Public License as published by&n;the Free Software Foundation; either version 2 of the License, or&n;(at your option) any later version.&n;&n;This program is distributed in the hope that it will be useful,&n;but WITHOUT ANY WARRANTY; without even the implied warranty of&n;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;GNU General Public License for more details.&n;&n;You should have received a copy of the GNU General Public License&n;along with this program; if not, write to the Free Software&n;Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
multiline_comment|/* ANSI and traditional C compatibility macros&n;&n;   ANSI C is assumed if __STDC__ is #defined.&n;&n;   Macro&t;ANSI C definition&t;Traditional C definition&n;   -----&t;---- - ----------&t;----------- - ----------&n;   PTR&t;&t;`void *&squot;&t;&t;`char *&squot;&n;   LONG_DOUBLE&t;`long double&squot;&t;&t;`double&squot;&n;   VOLATILE&t;`volatile&squot;&t;&t;`&squot;&n;   SIGNED&t;`signed&squot;&t;&t;`&squot;&n;   PTRCONST&t;`void *const&squot;&t;&t;`char *&squot;&n;   ANSI_PROTOTYPES  1&t;&t;&t;not defined&n;&n;   CONST is also defined, but is obsolete.  Just use const.&n;&n;   DEFUN (name, arglist, args)&n;&n;&t;Defines function NAME.&n;&n;&t;ARGLIST lists the arguments, separated by commas and enclosed in&n;&t;parentheses.  ARGLIST becomes the argument list in traditional C.&n;&n;&t;ARGS list the arguments with their types.  It becomes a prototype in&n;&t;ANSI C, and the type declarations in traditional C.  Arguments should&n;&t;be separated with `AND&squot;.  For functions with a variable number of&n;&t;arguments, the last thing listed should be `DOTS&squot;.&n;&n;   DEFUN_VOID (name)&n;&n;&t;Defines a function NAME, which takes no arguments.&n;&n;   obsolete --     EXFUN (name, (prototype))&t;-- obsolete.&n;&n;&t;Replaced by PARAMS.  Do not use; will disappear someday soon.&n;&t;Was used in external function declarations.&n;&t;In ANSI C it is `NAME PROTOTYPE&squot; (so PROTOTYPE should be enclosed in&n;&t;parentheses).  In traditional C it is `NAME()&squot;.&n;&t;For a function that takes no arguments, PROTOTYPE should be `(void)&squot;.&n;&n;    PARAMS ((args))&n;&n;&t;We could use the EXFUN macro to handle prototype declarations, but&n;&t;the name is misleading and the result is ugly.  So we just define a&n;&t;simple macro to handle the parameter lists, as in:&n;&n;&t;      static int foo PARAMS ((int, char));&n;&n;&t;This produces:  `static int foo();&squot; or `static int foo (int, char);&squot;&n;&n;&t;EXFUN would have done it like this:&n;&n;&t;      static int EXFUN (foo, (int, char));&n;&n;&t;but the function is not external...and it&squot;s hard to visually parse&n;&t;the function name out of the mess.   EXFUN should be considered&n;&t;obsolete; new code should be written to use PARAMS.&n;&n;    For example:&n;&t;extern int printf PARAMS ((CONST char *format DOTS));&n;&t;int DEFUN(fprintf, (stream, format),&n;&t;&t;  FILE *stream AND CONST char *format DOTS) { ... }&n;&t;void DEFUN_VOID(abort) { ... }&n;*/
macro_line|#ifndef&t;_ANSIDECL_H
DECL|macro|_ANSIDECL_H
mdefine_line|#define&t;_ANSIDECL_H&t;1
multiline_comment|/* Every source file includes this file,&n;   so they will all get the switch for lint.  */
multiline_comment|/* LINTLIBRARY */
macro_line|#if defined (__STDC__) || defined (_AIX) || (defined (__mips) &amp;&amp; defined (_SYSTYPE_SVR4)) || defined(WIN32)
multiline_comment|/* All known AIX compilers implement these things (but don&squot;t always&n;   define __STDC__).  The RISC/OS MIPS compiler defines these things&n;   in SVR4 mode, but does not define __STDC__.  */
DECL|macro|PTR
mdefine_line|#define&t;PTR&t;&t;void *
DECL|macro|PTRCONST
mdefine_line|#define&t;PTRCONST&t;void *CONST
DECL|macro|LONG_DOUBLE
mdefine_line|#define&t;LONG_DOUBLE&t;long double
DECL|macro|AND
mdefine_line|#define&t;AND&t;&t;,
DECL|macro|NOARGS
mdefine_line|#define&t;NOARGS&t;&t;void
DECL|macro|CONST
mdefine_line|#define&t;CONST&t;&t;const
DECL|macro|VOLATILE
mdefine_line|#define&t;VOLATILE&t;volatile
DECL|macro|SIGNED
mdefine_line|#define&t;SIGNED&t;&t;signed
DECL|macro|DOTS
mdefine_line|#define&t;DOTS&t;&t;, ...
DECL|macro|EXFUN
mdefine_line|#define&t;EXFUN(name, proto)&t;&t;name proto
DECL|macro|DEFUN
mdefine_line|#define&t;DEFUN(name, arglist, args)&t;name(args)
DECL|macro|DEFUN_VOID
mdefine_line|#define&t;DEFUN_VOID(name)&t;&t;name(void)
DECL|macro|PROTO
mdefine_line|#define PROTO(type, name, arglist)&t;type name arglist
DECL|macro|PARAMS
mdefine_line|#define PARAMS(paramlist)&t;&t;paramlist
DECL|macro|ANSI_PROTOTYPES
mdefine_line|#define ANSI_PROTOTYPES&t;&t;&t;1
macro_line|#else&t;/* Not ANSI C.  */
DECL|macro|PTR
mdefine_line|#define&t;PTR&t;&t;char *
DECL|macro|PTRCONST
mdefine_line|#define&t;PTRCONST&t;PTR
DECL|macro|LONG_DOUBLE
mdefine_line|#define&t;LONG_DOUBLE&t;double
DECL|macro|AND
mdefine_line|#define&t;AND&t;&t;;
DECL|macro|NOARGS
mdefine_line|#define&t;NOARGS
DECL|macro|CONST
mdefine_line|#define&t;CONST
macro_line|#ifndef const /* some systems define it in header files for non-ansi mode */
DECL|macro|const
mdefine_line|#define&t;const
macro_line|#endif
DECL|macro|VOLATILE
mdefine_line|#define&t;VOLATILE
DECL|macro|SIGNED
mdefine_line|#define&t;SIGNED
DECL|macro|DOTS
mdefine_line|#define&t;DOTS
DECL|macro|EXFUN
mdefine_line|#define&t;EXFUN(name, proto)&t;&t;name()
DECL|macro|DEFUN
mdefine_line|#define&t;DEFUN(name, arglist, args)&t;name arglist args;
DECL|macro|DEFUN_VOID
mdefine_line|#define&t;DEFUN_VOID(name)&t;&t;name()
DECL|macro|PROTO
mdefine_line|#define PROTO(type, name, arglist) type name ()
DECL|macro|PARAMS
mdefine_line|#define PARAMS(paramlist)&t;&t;()
macro_line|#endif&t;/* ANSI C.  */
macro_line|#endif&t;/* ansidecl.h&t;*/
eof
