multiline_comment|/* $Id: psrcompat.h,v 1.5 1998/10/06 09:28:39 jj Exp $ */
macro_line|#ifndef _SPARC64_PSRCOMPAT_H
DECL|macro|_SPARC64_PSRCOMPAT_H
mdefine_line|#define _SPARC64_PSRCOMPAT_H
macro_line|#include &lt;asm/pstate.h&gt;
multiline_comment|/* Old 32-bit PSR fields for the compatability conversion code. */
DECL|macro|PSR_CWP
mdefine_line|#define PSR_CWP     0x0000001f         /* current window pointer     */
DECL|macro|PSR_ET
mdefine_line|#define PSR_ET      0x00000020         /* enable traps field         */
DECL|macro|PSR_PS
mdefine_line|#define PSR_PS      0x00000040         /* previous privilege level   */
DECL|macro|PSR_S
mdefine_line|#define PSR_S       0x00000080         /* current privilege level    */
DECL|macro|PSR_PIL
mdefine_line|#define PSR_PIL     0x00000f00         /* processor interrupt level  */
DECL|macro|PSR_EF
mdefine_line|#define PSR_EF      0x00001000         /* enable floating point      */
DECL|macro|PSR_EC
mdefine_line|#define PSR_EC      0x00002000         /* enable co-processor        */
DECL|macro|PSR_LE
mdefine_line|#define PSR_LE      0x00008000         /* SuperSparcII little-endian */
DECL|macro|PSR_ICC
mdefine_line|#define PSR_ICC     0x00f00000         /* integer condition codes    */
DECL|macro|PSR_C
mdefine_line|#define PSR_C       0x00100000         /* carry bit                  */
DECL|macro|PSR_V
mdefine_line|#define PSR_V       0x00200000         /* overflow bit               */
DECL|macro|PSR_Z
mdefine_line|#define PSR_Z       0x00400000         /* zero bit                   */
DECL|macro|PSR_N
mdefine_line|#define PSR_N       0x00800000         /* negative bit               */
DECL|macro|PSR_VERS
mdefine_line|#define PSR_VERS    0x0f000000         /* cpu-version field          */
DECL|macro|PSR_IMPL
mdefine_line|#define PSR_IMPL    0xf0000000         /* cpu-implementation field   */
DECL|macro|PSR_V8PLUS
mdefine_line|#define PSR_V8PLUS  0xff000000         /* fake impl/ver, meaning a 64bit CPU is present */
DECL|macro|PSR_XCC
mdefine_line|#define PSR_XCC&t;    0x000f0000         /* if PSR_V8PLUS, this is %xcc */
DECL|function|tstate_to_psr
r_extern
r_inline
r_int
r_int
id|tstate_to_psr
c_func
(paren
r_int
r_int
id|tstate
)paren
(brace
r_return
(paren
(paren
id|tstate
op_amp
id|TSTATE_CWP
)paren
op_or
id|PSR_S
op_or
(paren
(paren
id|tstate
op_amp
id|TSTATE_ICC
)paren
op_rshift
l_int|12
)paren
op_or
(paren
(paren
id|tstate
op_amp
id|TSTATE_XCC
)paren
op_rshift
l_int|20
)paren
op_or
id|PSR_V8PLUS
)paren
suffix:semicolon
)brace
DECL|function|psr_to_tstate_icc
r_extern
r_inline
r_int
r_int
id|psr_to_tstate_icc
c_func
(paren
r_int
r_int
id|psr
)paren
(brace
r_int
r_int
id|tstate
op_assign
(paren
(paren
r_int
r_int
)paren
(paren
id|psr
op_amp
id|PSR_ICC
)paren
)paren
op_lshift
l_int|12
suffix:semicolon
r_if
c_cond
(paren
(paren
id|psr
op_amp
(paren
id|PSR_VERS
op_or
id|PSR_IMPL
)paren
)paren
op_eq
id|PSR_V8PLUS
)paren
id|tstate
op_or_assign
(paren
(paren
r_int
r_int
)paren
(paren
id|psr
op_amp
id|PSR_XCC
)paren
)paren
op_lshift
l_int|20
suffix:semicolon
r_return
id|tstate
suffix:semicolon
)brace
macro_line|#endif /* !(_SPARC64_PSRCOMPAT_H) */
eof
