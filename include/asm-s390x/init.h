multiline_comment|/*&n; *  include/asm-s390/init.h&n; *&n; *  S390 version&n; */
macro_line|#ifndef _S390_INIT_H
DECL|macro|_S390_INIT_H
mdefine_line|#define _S390_INIT_H
DECL|macro|__init
mdefine_line|#define __init __attribute__ ((constructor))
multiline_comment|/* don&squot;t know, if need on S390 */
DECL|macro|__initdata
mdefine_line|#define __initdata
DECL|macro|__initfunc
mdefine_line|#define __initfunc(__arginit) &bslash;&n;        __arginit __init; &bslash;&n;        __arginit
multiline_comment|/* For assembly routines&n; * need to define ?&n; */
multiline_comment|/*&n;#define __INIT          .section        &quot;.text.init&quot;,#alloc,#execinstr&n;#define __FINIT .previous&n;#define __INITDATA      .section        &quot;.data.init&quot;,#alloc,#write&n;*/
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned __attribute__ ((__aligned__(16)))
macro_line|#endif
eof
