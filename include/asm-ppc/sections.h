macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_SECTIONS_H
DECL|macro|_PPC_SECTIONS_H
mdefine_line|#define _PPC_SECTIONS_H
DECL|macro|__pmac
mdefine_line|#define __pmac __attribute__ ((__section__ (&quot;.pmac.text&quot;)))
DECL|macro|__pmacdata
mdefine_line|#define __pmacdata __attribute__ ((__section__ (&quot;.pmac.data&quot;)))
DECL|macro|__pmacfunc
mdefine_line|#define __pmacfunc(__argpmac) &bslash;&n;&t;__argpmac __pmac; &bslash;&n;&t;__argpmac
DECL|macro|__prep
mdefine_line|#define __prep __attribute__ ((__section__ (&quot;.prep.text&quot;)))
DECL|macro|__prepdata
mdefine_line|#define __prepdata __attribute__ ((__section__ (&quot;.prep.data&quot;)))
DECL|macro|__prepfunc
mdefine_line|#define __prepfunc(__argprep) &bslash;&n;&t;__argprep __prep; &bslash;&n;&t;__argprep
DECL|macro|__chrp
mdefine_line|#define __chrp __attribute__ ((__section__ (&quot;.chrp.text&quot;)))
DECL|macro|__chrpdata
mdefine_line|#define __chrpdata __attribute__ ((__section__ (&quot;.chrp.data&quot;)))
DECL|macro|__chrpfunc
mdefine_line|#define __chrpfunc(__argchrp) &bslash;&n;&t;__argchrp __chrp; &bslash;&n;&t;__argchrp
multiline_comment|/* this is actually just common chrp/pmac code, not OF code -- Cort */
DECL|macro|__openfirmware
mdefine_line|#define __openfirmware __attribute__ ((__section__ (&quot;.openfirmware.text&quot;)))
DECL|macro|__openfirmwaredata
mdefine_line|#define __openfirmwaredata __attribute__ ((__section__ (&quot;.openfirmware.data&quot;)))
DECL|macro|__openfirmwarefunc
mdefine_line|#define __openfirmwarefunc(__argopenfirmware) &bslash;&n;&t;__argopenfirmware __openfirmware; &bslash;&n;&t;__argopenfirmware
macro_line|#endif /* _PPC_SECTIONS_H */
macro_line|#endif /* __KERNEL__ */
eof
