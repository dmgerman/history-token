macro_line|#ifndef _PPC64_INIT_H
DECL|macro|_PPC64_INIT_H
mdefine_line|#define _PPC64_INIT_H
macro_line|#include &lt;linux/init.h&gt;
macro_line|#if __GNUC__ &gt; 2 || __GNUC_MINOR__ &gt;= 90 /* egcs */
multiline_comment|/* DRENG add back in when we get section attribute support */
DECL|macro|__chrp
mdefine_line|#define __chrp __attribute__ ((__section__ (&quot;.text.chrp&quot;)))
DECL|macro|__chrpdata
mdefine_line|#define __chrpdata __attribute__ ((__section__ (&quot;.data.chrp&quot;)))
DECL|macro|__chrpfunc
mdefine_line|#define __chrpfunc(__argchrp) &bslash;&n;&t;__argchrp __chrp; &bslash;&n;&t;__argchrp
multiline_comment|/* this is actually just common chrp/pmac code, not OF code -- Cort */
DECL|macro|__openfirmware
mdefine_line|#define __openfirmware __attribute__ ((__section__ (&quot;.text.openfirmware&quot;)))
DECL|macro|__openfirmwaredata
mdefine_line|#define __openfirmwaredata __attribute__ ((__section__ (&quot;.data.openfirmware&quot;)))
DECL|macro|__openfirmwarefunc
mdefine_line|#define __openfirmwarefunc(__argopenfirmware) &bslash;&n;&t;__argopenfirmware __openfirmware; &bslash;&n;&t;__argopenfirmware
macro_line|#else /* not egcs */
DECL|macro|__openfirmware
mdefine_line|#define __openfirmware
DECL|macro|__openfirmwaredata
mdefine_line|#define __openfirmwaredata
DECL|macro|__openfirmwarefunc
mdefine_line|#define __openfirmwarefunc(x) x
macro_line|#endif /* egcs */
macro_line|#endif /* _PPC64_INIT_H */
eof
