multiline_comment|/*&n; *&t;For declaring structures shared with assembly routines&n; *&n; *&t;$Id: asstruct.h,v 1.1.1.1 1994/10/23 05:08:32 rick Exp $&n; */
macro_line|#if ASSEMBLER
DECL|macro|MO
macro_line|#&t;define MO(t,a)&t;&t;(a)
DECL|macro|VMO
macro_line|#&t;define VMO(t,a)&t;&t;(a)
DECL|macro|BEGIN_STRUCT
macro_line|#&t;define&t;BEGIN_STRUCT(x)&t;_Off=0
DECL|macro|S1A
macro_line|#&t;define&t;S1A(t,x,n)&t;_Off=(_Off+0)&amp;~0; x=_Off; _Off=_Off+(1*n)
DECL|macro|S2A
macro_line|#&t;define&t;S2A(t,x,n)&t;_Off=(_Off+1)&amp;~1; x=_Off; _Off=_Off+(2*n)
DECL|macro|S4A
macro_line|#&t;define&t;S4A(t,x,n)&t;_Off=(_Off+3)&amp;~3; x=_Off; _Off=_Off+(4*n)
DECL|macro|WORD
macro_line|#&t;define&t;WORD(x)&t;&t;_Off=(_Off+3)&amp;~3; x=_Off; _Off=_Off+4
DECL|macro|WORDA
macro_line|#&t;define&t;WORDA(x,n)&t;_Off=(_Off+3)&amp;~3; x=_Off; _Off=_Off+(4*n)
DECL|macro|VWORD
macro_line|#&t;define&t;VWORD(x)&t;_Off=(_Off+3)&amp;~3; x=_Off; _Off=_Off+4
DECL|macro|S1
macro_line|#&t;define&t;S1(t,x)&t;&t;_Off=(_Off+0)&amp;~0; x=_Off; _Off=_Off+1
DECL|macro|S2
macro_line|#&t;define&t;S2(t,x)&t;&t;_Off=(_Off+1)&amp;~1; x=_Off; _Off=_Off+2
DECL|macro|S4
macro_line|#&t;define&t;S4(t,x)&t;&t;_Off=(_Off+3)&amp;~3; x=_Off; _Off=_Off+4
DECL|macro|END_STRUCT
macro_line|#&t;define&t;END_STRUCT(x)&t;_Off=(_Off+3)&amp;~3; x=_Off 
macro_line|#else&t;/* C */
DECL|macro|VMO
mdefine_line|#define VMO(t,a)        (*(volatile t *)(a))
DECL|macro|BEGIN_STRUCT
macro_line|#&t;define BEGIN_STRUCT(x) struct x {
DECL|macro|S1
macro_line|#&t;define S1(t,x)         t x ;
DECL|macro|S1A
macro_line|#&t;define S1A(t,x,n)      t x[n] ;
DECL|macro|S2
macro_line|#&t;define S2(t,x)         t x ;
DECL|macro|S2A
macro_line|#&t;define S2A(t,x,n)      t x[n] ;
DECL|macro|S4
macro_line|#&t;define S4(t,x)         t x ;
DECL|macro|S4A
macro_line|#&t;define S4A(t,x,n)      t x[n] ;
DECL|macro|END_STRUCT
macro_line|#&t;define END_STRUCT(x)   } ;
macro_line|#endif
eof
