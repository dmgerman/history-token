macro_line|#ifndef __CRAP_H
DECL|macro|__CRAP_H
mdefine_line|#define __CRAP_H
multiline_comment|/**&n; *  compatibility crap for old kernels. No guarantee for a working driver&n; *  even when everything compiles.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#ifndef MODULE_LICENSE
DECL|macro|MODULE_LICENSE
mdefine_line|#define MODULE_LICENSE(x)
macro_line|#endif
macro_line|#ifndef list_for_each_safe
DECL|macro|list_for_each_safe
mdefine_line|#define list_for_each_safe(pos, n, head) &bslash;&n;        for (pos = (head)-&gt;next, n = pos-&gt;next; pos != (head); &bslash;&n;                pos = n, n = pos-&gt;next)
macro_line|#endif
macro_line|#endif
eof
