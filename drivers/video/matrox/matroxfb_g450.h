macro_line|#ifndef __MATROXFB_G450_H__
DECL|macro|__MATROXFB_G450_H__
mdefine_line|#define __MATROXFB_G450_H__
macro_line|#include &quot;matroxfb_base.h&quot;
macro_line|#ifdef CONFIG_FB_MATROX_G
r_void
id|matroxfb_g450_connect
c_func
(paren
id|WPMINFO2
)paren
suffix:semicolon
r_void
id|matroxfb_g450_shutdown
c_func
(paren
id|WPMINFO2
)paren
suffix:semicolon
macro_line|#else
DECL|function|matroxfb_g450_connect
r_static
r_inline
r_void
id|matroxfb_g450_connect
c_func
(paren
id|WPMINFO2
)paren
(brace
)brace
suffix:semicolon
DECL|function|matroxfb_g450_shutdown
r_static
r_inline
r_void
id|matroxfb_g450_shutdown
c_func
(paren
id|WPMINFO2
)paren
(brace
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __MATROXFB_G450_H__ */
eof
