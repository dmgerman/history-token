multiline_comment|/*&n; *  include/asm-s390/siginfo.h&n; *&n; *  S390 version&n; *&n; *  Derived from &quot;include/asm-i386/siginfo.h&quot;&n; */
macro_line|#ifndef _S390_SIGINFO_H
DECL|macro|_S390_SIGINFO_H
mdefine_line|#define _S390_SIGINFO_H
DECL|macro|HAVE_ARCH_SI_CODES
mdefine_line|#define HAVE_ARCH_SI_CODES
macro_line|#include &lt;asm-generic/siginfo.h&gt;
multiline_comment|/*&n; * SIGILL si_codes&n; */
DECL|macro|ILL_ILLOPC
mdefine_line|#define ILL_ILLOPC&t;(__SI_FAULT|1)&t;/* illegal opcode */
DECL|macro|ILL_ILLOPN
mdefine_line|#define ILL_ILLOPN&t;(__SI_FAULT|2)&t;/* illegal operand */
DECL|macro|ILL_ILLADR
mdefine_line|#define ILL_ILLADR&t;(__SI_FAULT|3)&t;/* illegal addressing mode */
DECL|macro|ILL_ILLTRP
mdefine_line|#define ILL_ILLTRP&t;(__SI_FAULT|4)&t;/* illegal trap */
DECL|macro|ILL_PRVOPC
mdefine_line|#define ILL_PRVOPC&t;(__SI_FAULT|5)&t;/* privileged opcode */
DECL|macro|ILL_PRVREG
mdefine_line|#define ILL_PRVREG&t;(__SI_FAULT|6)&t;/* privileged register */
DECL|macro|ILL_COPROC
mdefine_line|#define ILL_COPROC&t;(__SI_FAULT|7)&t;/* coprocessor error */
DECL|macro|ILL_BADSTK
mdefine_line|#define ILL_BADSTK&t;(__SI_FAULT|8)&t;/* internal stack error */
DECL|macro|NSIGILL
mdefine_line|#define NSIGILL&t;&t;8
multiline_comment|/*&n; * SIGFPE si_codes&n; */
DECL|macro|FPE_INTDIV
mdefine_line|#define FPE_INTDIV&t;(__SI_FAULT|1)&t;/* integer divide by zero */
DECL|macro|FPE_INTOVF
mdefine_line|#define FPE_INTOVF&t;(__SI_FAULT|2)&t;/* integer overflow */
DECL|macro|FPE_FLTDIV
mdefine_line|#define FPE_FLTDIV&t;(__SI_FAULT|3)&t;/* floating point divide by zero */
DECL|macro|FPE_FLTOVF
mdefine_line|#define FPE_FLTOVF&t;(__SI_FAULT|4)&t;/* floating point overflow */
DECL|macro|FPE_FLTUND
mdefine_line|#define FPE_FLTUND&t;(__SI_FAULT|5)&t;/* floating point underflow */
DECL|macro|FPE_FLTRES
mdefine_line|#define FPE_FLTRES&t;(__SI_FAULT|6)&t;/* floating point inexact result */
DECL|macro|FPE_FLTINV
mdefine_line|#define FPE_FLTINV&t;(__SI_FAULT|7)&t;/* floating point invalid operation */
DECL|macro|FPE_FLTSUB
mdefine_line|#define FPE_FLTSUB&t;(__SI_FAULT|8)&t;/* subscript out of range */
DECL|macro|NSIGFPE
mdefine_line|#define NSIGFPE&t;&t;8
multiline_comment|/*&n; * SIGSEGV si_codes&n; */
DECL|macro|SEGV_MAPERR
mdefine_line|#define SEGV_MAPERR&t;(__SI_FAULT|1)&t;/* address not mapped to object */
DECL|macro|SEGV_ACCERR
mdefine_line|#define SEGV_ACCERR&t;(__SI_FAULT|2)&t;/* invalid permissions for mapped object */
DECL|macro|NSIGSEGV
mdefine_line|#define NSIGSEGV&t;2
multiline_comment|/*&n; * SIGBUS si_codes&n; */
DECL|macro|BUS_ADRALN
mdefine_line|#define BUS_ADRALN&t;(__SI_FAULT|1)&t;/* invalid address alignment */
DECL|macro|BUS_ADRERR
mdefine_line|#define BUS_ADRERR&t;(__SI_FAULT|2)&t;/* non-existant physical address */
DECL|macro|BUS_OBJERR
mdefine_line|#define BUS_OBJERR&t;(__SI_FAULT|3)&t;/* object specific hardware error */
DECL|macro|NSIGBUS
mdefine_line|#define NSIGBUS&t;&t;3
multiline_comment|/*&n; * SIGTRAP si_codes&n; */
DECL|macro|TRAP_BRKPT
mdefine_line|#define TRAP_BRKPT&t;(__SI_FAULT|1)&t;/* process breakpoint */
DECL|macro|TRAP_TRACE
mdefine_line|#define TRAP_TRACE&t;(__SI_FAULT|2)&t;/* process trace trap */
DECL|macro|NSIGTRAP
mdefine_line|#define NSIGTRAP&t;2
multiline_comment|/*&n; * SIGCHLD si_codes&n; */
DECL|macro|CLD_EXITED
mdefine_line|#define CLD_EXITED&t;(__SI_CHLD|1)&t;/* child has exited */
DECL|macro|CLD_KILLED
mdefine_line|#define CLD_KILLED&t;(__SI_CHLD|2)&t;/* child was killed */
DECL|macro|CLD_DUMPED
mdefine_line|#define CLD_DUMPED&t;(__SI_CHLD|3)&t;/* child terminated abnormally */
DECL|macro|CLD_TRAPPED
mdefine_line|#define CLD_TRAPPED&t;(__SI_CHLD|4)&t;/* traced child has trapped */
DECL|macro|CLD_STOPPED
mdefine_line|#define CLD_STOPPED&t;(__SI_CHLD|5)&t;/* child has stopped */
DECL|macro|CLD_CONTINUED
mdefine_line|#define CLD_CONTINUED&t;(__SI_CHLD|6)&t;/* stopped child has continued */
DECL|macro|NSIGCHLD
mdefine_line|#define NSIGCHLD&t;6
multiline_comment|/*&n; * SIGPOLL si_codes&n; */
DECL|macro|POLL_IN
mdefine_line|#define POLL_IN&t;&t;(__SI_POLL|1)&t;/* data input available */
DECL|macro|POLL_OUT
mdefine_line|#define POLL_OUT&t;(__SI_POLL|2)&t;/* output buffers available */
DECL|macro|POLL_MSG
mdefine_line|#define POLL_MSG&t;(__SI_POLL|3)&t;/* input message available */
DECL|macro|POLL_ERR
mdefine_line|#define POLL_ERR&t;(__SI_POLL|4)&t;/* i/o error */
DECL|macro|POLL_PRI
mdefine_line|#define POLL_PRI&t;(__SI_POLL|5)&t;/* high priority input available */
DECL|macro|POLL_HUP
mdefine_line|#define POLL_HUP&t;(__SI_POLL|6)&t;/* device disconnected */
DECL|macro|NSIGPOLL
mdefine_line|#define NSIGPOLL&t;6
macro_line|#endif
eof
