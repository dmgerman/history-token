multiline_comment|/* $Id: fcheck.c,v 1.3 2000/06/12 12:44:02 armin Exp $&n; * &n; * (c) 2000 Cytronics &amp; Melware&n; *&n; *  This file is (c) under GNU PUBLIC LICENSE&n; *  For changes and modifications please read&n; *  ../../../Documentation/isdn/README.eicon&n; *&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
r_char
op_star
DECL|function|file_check
id|file_check
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef FILECHECK
macro_line|#if FILECHECK == 0
r_return
l_string|&quot;verified&quot;
suffix:semicolon
macro_line|#endif
macro_line|#if FILECHECK == 1 
r_return
l_string|&quot;modified&quot;
suffix:semicolon
macro_line|#endif
macro_line|#if FILECHECK == 127 
r_return
l_string|&quot;verification failed&quot;
suffix:semicolon
macro_line|#endif
macro_line|#else
r_return
l_string|&quot;not verified&quot;
suffix:semicolon
macro_line|#endif
)brace
eof
