multiline_comment|/* $Id: shmparam.h,v 1.5 2001/09/24 21:17:57 kanoj Exp $ */
macro_line|#ifndef _ASMSPARC64_SHMPARAM_H
DECL|macro|_ASMSPARC64_SHMPARAM_H
mdefine_line|#define _ASMSPARC64_SHMPARAM_H
macro_line|#include &lt;asm/spitfire.h&gt;
multiline_comment|/* attach addr a multiple of this */
DECL|macro|SHMLBA
mdefine_line|#define&t;SHMLBA&t;((PAGE_SIZE &gt; L1DCACHE_SIZE) ? PAGE_SIZE : L1DCACHE_SIZE)
macro_line|#endif /* _ASMSPARC64_SHMPARAM_H */
eof
