macro_line|#ifndef _LINUX_CTYPE_H
DECL|macro|_LINUX_CTYPE_H
mdefine_line|#define _LINUX_CTYPE_H
multiline_comment|/*&n; * NOTE! This ctype does not handle EOF like the standard C&n; * library is required to.&n; */
DECL|macro|_U
mdefine_line|#define _U&t;0x01&t;/* upper */
DECL|macro|_L
mdefine_line|#define _L&t;0x02&t;/* lower */
DECL|macro|_D
mdefine_line|#define _D&t;0x04&t;/* digit */
DECL|macro|_C
mdefine_line|#define _C&t;0x08&t;/* cntrl */
DECL|macro|_P
mdefine_line|#define _P&t;0x10&t;/* punct */
DECL|macro|_S
mdefine_line|#define _S&t;0x20&t;/* white space (space/lf/tab) */
DECL|macro|_X
mdefine_line|#define _X&t;0x40&t;/* hex digit */
DECL|macro|_SP
mdefine_line|#define _SP&t;0x80&t;/* hard space (0x20) */
r_extern
r_int
r_char
id|_ctype
(braket
)braket
suffix:semicolon
DECL|macro|__ismask
mdefine_line|#define __ismask(x) (_ctype[(int)(unsigned char)(x)])
DECL|macro|isalnum
mdefine_line|#define isalnum(c)&t;((__ismask(c)&amp;(_U|_L|_D)) != 0)
DECL|macro|isalpha
mdefine_line|#define isalpha(c)&t;((__ismask(c)&amp;(_U|_L)) != 0)
DECL|macro|iscntrl
mdefine_line|#define iscntrl(c)&t;((__ismask(c)&amp;(_C)) != 0)
DECL|macro|isdigit
mdefine_line|#define isdigit(c)&t;((__ismask(c)&amp;(_D)) != 0)
DECL|macro|isgraph
mdefine_line|#define isgraph(c)&t;((__ismask(c)&amp;(_P|_U|_L|_D)) != 0)
DECL|macro|islower
mdefine_line|#define islower(c)&t;((__ismask(c)&amp;(_L)) != 0)
DECL|macro|isprint
mdefine_line|#define isprint(c)&t;((__ismask(c)&amp;(_P|_U|_L|_D|_SP)) != 0)
DECL|macro|ispunct
mdefine_line|#define ispunct(c)&t;((__ismask(c)&amp;(_P)) != 0)
DECL|macro|isspace
mdefine_line|#define isspace(c)&t;((__ismask(c)&amp;(_S)) != 0)
DECL|macro|isupper
mdefine_line|#define isupper(c)&t;((__ismask(c)&amp;(_U)) != 0)
DECL|macro|isxdigit
mdefine_line|#define isxdigit(c)&t;((__ismask(c)&amp;(_D|_X)) != 0)
DECL|macro|isascii
mdefine_line|#define isascii(c) (((unsigned char)(c))&lt;=0x7f)
DECL|macro|toascii
mdefine_line|#define toascii(c) (((unsigned char)(c))&amp;0x7f)
DECL|function|__tolower
r_static
r_inline
r_int
r_char
id|__tolower
c_func
(paren
r_int
r_char
id|c
)paren
(brace
r_if
c_cond
(paren
id|isupper
c_func
(paren
id|c
)paren
)paren
id|c
op_sub_assign
l_char|&squot;A&squot;
op_minus
l_char|&squot;a&squot;
suffix:semicolon
r_return
id|c
suffix:semicolon
)brace
DECL|function|__toupper
r_static
r_inline
r_int
r_char
id|__toupper
c_func
(paren
r_int
r_char
id|c
)paren
(brace
r_if
c_cond
(paren
id|islower
c_func
(paren
id|c
)paren
)paren
id|c
op_sub_assign
l_char|&squot;a&squot;
op_minus
l_char|&squot;A&squot;
suffix:semicolon
r_return
id|c
suffix:semicolon
)brace
DECL|macro|tolower
mdefine_line|#define tolower(c) __tolower(c)
DECL|macro|toupper
mdefine_line|#define toupper(c) __toupper(c)
macro_line|#endif
eof
