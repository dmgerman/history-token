macro_line|#ifndef _SIS_H
DECL|macro|_SIS_H
mdefine_line|#define _SIS_H
macro_line|#if 1
DECL|macro|TWDEBUG
mdefine_line|#define TWDEBUG(x)
macro_line|#else
DECL|macro|TWDEBUG
mdefine_line|#define TWDEBUG(x) printk(KERN_INFO x &quot;&bslash;n&quot;);
macro_line|#endif
macro_line|#endif
eof
