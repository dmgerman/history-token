multiline_comment|/* $Id: psr.h,v 1.15 1997/10/04 08:54:22 ecd Exp $&n; * psr.h: This file holds the macros for masking off various parts of&n; *        the processor status register on the Sparc. This is valid&n; *        for Version 8. On the V9 this is renamed to the PSTATE&n; *        register and its members are accessed as fields like&n; *        PSTATE.PRIV for the current CPU privilege level.&n; *&n; * Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __LINUX_SPARC_PSR_H
DECL|macro|__LINUX_SPARC_PSR_H
mdefine_line|#define __LINUX_SPARC_PSR_H
multiline_comment|/* The Sparc PSR fields are laid out as the following:&n; *&n; *  ------------------------------------------------------------------------&n; *  | impl  | vers  | icc   | resv  | EC | EF | PIL  | S | PS | ET |  CWP  |&n; *  | 31-28 | 27-24 | 23-20 | 19-14 | 13 | 12 | 11-8 | 7 | 6  | 5  |  4-0  |&n; *  ------------------------------------------------------------------------&n; */
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
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Get the %psr register. */
DECL|function|get_psr
r_extern
id|__inline__
r_int
r_int
id|get_psr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|psr
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rd&t;%%psr, %0&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|psr
)paren
suffix:colon
multiline_comment|/* no inputs */
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|psr
suffix:semicolon
)brace
DECL|function|put_psr
r_extern
id|__inline__
r_void
id|put_psr
c_func
(paren
r_int
r_int
id|new_psr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;wr&t;%0, 0x0, %%psr&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|new_psr
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the %fsr register.  Be careful, make sure the floating point&n; * enable bit is set in the %psr when you execute this or you will&n; * incur a trap.&n; */
r_extern
r_int
r_int
id|fsr_storage
suffix:semicolon
DECL|function|get_fsr
r_extern
id|__inline__
r_int
r_int
id|get_fsr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|fsr
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;st&t;%%fsr, %1&bslash;n&bslash;t&quot;
l_string|&quot;ld&t;%1, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|fsr
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|fsr_storage
)paren
)paren
suffix:semicolon
r_return
id|fsr
suffix:semicolon
)brace
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* (__KERNEL__) */
macro_line|#endif /* !(__LINUX_SPARC_PSR_H) */
eof
