multiline_comment|/*&n; *  include/asm-s390/ebcdic.h&n; *    EBCDIC -&gt; ASCII, ASCII -&gt; EBCDIC conversion routines.&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky &lt;schwidefsky@de.ibm.com&gt;&n; */
macro_line|#ifndef _EBCDIC_H
DECL|macro|_EBCDIC_H
mdefine_line|#define _EBCDIC_H
macro_line|#ifndef _S390_TYPES_H
macro_line|#include &lt;types.h&gt;
macro_line|#endif
r_extern
id|__u8
id|_ascebc
(braket
)braket
suffix:semicolon
multiline_comment|/* ASCII -&gt; EBCDIC conversion table */
r_extern
id|__u8
id|_ebcasc
(braket
)braket
suffix:semicolon
multiline_comment|/* EBCDIC -&gt; ASCII conversion table */
r_extern
id|__u8
id|_ebc_tolower
(braket
)braket
suffix:semicolon
multiline_comment|/* EBCDIC -&gt; lowercase */
r_extern
id|__u8
id|_ebc_toupper
(braket
)braket
suffix:semicolon
multiline_comment|/* EBCDIC -&gt; uppercase */
r_extern
id|__inline__
DECL|function|codepage_convert
r_void
id|codepage_convert
c_func
(paren
r_const
id|__u8
op_star
id|codepage
comma
r_volatile
id|__u8
op_star
id|addr
comma
r_int
id|nr
)paren
(brace
r_static
r_const
id|__u16
id|tr_op
(braket
)braket
op_assign
(brace
l_int|0xDC00
comma
l_int|0x1000
comma
l_int|0x3000
)brace
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lr    1,%0&bslash;n&quot;
l_string|&quot;   lr    2,%1&bslash;n&quot;
l_string|&quot;   lr    3,%2&bslash;n&quot;
l_string|&quot;   ahi   2,-256&bslash;n&quot;
l_string|&quot;   jm    1f&bslash;n&quot;
l_string|&quot;0: tr    0(256,1),0(3)&bslash;n&quot;
l_string|&quot;   ahi   1,256&bslash;n&quot;
l_string|&quot;   ahi   2,-256&bslash;n&quot;
l_string|&quot;   jp    0b&bslash;n&quot;
l_string|&quot;1: ahi   2,255&bslash;n&quot;
l_string|&quot;   jm    2f&bslash;n&quot;
l_string|&quot;   ex    2,%3&bslash;n&quot;
l_string|&quot;2:&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;d&quot;
(paren
id|nr
)paren
comma
l_string|&quot;a&quot;
(paren
id|codepage
)paren
comma
l_string|&quot;m&quot;
(paren
id|tr_op
(braket
l_int|0
)braket
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
)paren
suffix:semicolon
)brace
DECL|macro|ASCEBC
mdefine_line|#define ASCEBC(addr,nr) codepage_convert(_ascebc, addr, nr)
DECL|macro|EBCASC
mdefine_line|#define EBCASC(addr,nr) codepage_convert(_ebcasc, addr, nr)
DECL|macro|EBC_TOLOWER
mdefine_line|#define EBC_TOLOWER(addr,nr) codepage_convert(_ebc_tolower, addr, nr)
DECL|macro|EBC_TOUPPER
mdefine_line|#define EBC_TOUPPER(addr,nr) codepage_convert(_ebc_toupper, addr, nr)
macro_line|#endif
eof
