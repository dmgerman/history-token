multiline_comment|/*&n; *  include/asm-s390/ebcdic.h&n; *    EBCDIC -&gt; ASCII, ASCII -&gt; EBCDIC conversion routines.&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky &lt;schwidefsky@de.ibm.com&gt;&n; */
macro_line|#ifndef _EBCDIC_H
DECL|macro|_EBCDIC_H
mdefine_line|#define _EBCDIC_H
macro_line|#ifndef _S390_TYPES_H
macro_line|#include &lt;types.h&gt;
macro_line|#endif
r_extern
id|__u8
id|_ascebc_500
(braket
)braket
suffix:semicolon
multiline_comment|/* ASCII -&gt; EBCDIC 500 conversion table */
r_extern
id|__u8
id|_ebcasc_500
(braket
)braket
suffix:semicolon
multiline_comment|/* EBCDIC 500 -&gt; ASCII conversion table */
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
r_if
c_cond
(paren
id|nr
op_le
l_int|0
)paren
r_return
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   bras 1,1f&bslash;n&quot;
l_string|&quot;   tr   0(1,%0),0(%2)&bslash;n&quot;
l_string|&quot;0: la   %0,256(%0)&bslash;n&quot;
l_string|&quot;   tr   0(256,%0),0(%2)&bslash;n&quot;
l_string|&quot;1: ahi  %1,-256&bslash;n&quot;
l_string|&quot;   jp   0b&bslash;n&quot;
l_string|&quot;   ex   %1,0(1)&quot;
suffix:colon
l_string|&quot;+&amp;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;+&amp;a&quot;
(paren
id|nr
op_minus
l_int|1
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|codepage
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
)brace
DECL|macro|ASCEBC
mdefine_line|#define ASCEBC(addr,nr) codepage_convert(_ascebc, addr, nr)
DECL|macro|EBCASC
mdefine_line|#define EBCASC(addr,nr) codepage_convert(_ebcasc, addr, nr)
DECL|macro|ASCEBC_500
mdefine_line|#define ASCEBC_500(addr,nr) codepage_convert(_ascebc_500, addr, nr)
DECL|macro|EBCASC_500
mdefine_line|#define EBCASC_500(addr,nr) codepage_convert(_ebcasc_500, addr, nr)
DECL|macro|EBC_TOLOWER
mdefine_line|#define EBC_TOLOWER(addr,nr) codepage_convert(_ebc_tolower, addr, nr)
DECL|macro|EBC_TOUPPER
mdefine_line|#define EBC_TOUPPER(addr,nr) codepage_convert(_ebc_toupper, addr, nr)
macro_line|#endif
eof
