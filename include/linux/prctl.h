macro_line|#ifndef _LINUX_PRCTL_H
DECL|macro|_LINUX_PRCTL_H
mdefine_line|#define _LINUX_PRCTL_H
multiline_comment|/* Values to pass as first argument to prctl() */
DECL|macro|PR_SET_PDEATHSIG
mdefine_line|#define PR_SET_PDEATHSIG  1  /* Second arg is a signal */
DECL|macro|PR_GET_PDEATHSIG
mdefine_line|#define PR_GET_PDEATHSIG  2  /* Second arg is a ptr to return the signal */
multiline_comment|/* Get/set current-&gt;mm-&gt;dumpable */
DECL|macro|PR_GET_DUMPABLE
mdefine_line|#define PR_GET_DUMPABLE   3
DECL|macro|PR_SET_DUMPABLE
mdefine_line|#define PR_SET_DUMPABLE   4
multiline_comment|/* Get/set unaligned access control bits (if meaningful) */
DECL|macro|PR_GET_UNALIGN
mdefine_line|#define PR_GET_UNALIGN&t;  5
DECL|macro|PR_SET_UNALIGN
mdefine_line|#define PR_SET_UNALIGN&t;  6
DECL|macro|PR_UNALIGN_NOPRINT
macro_line|# define PR_UNALIGN_NOPRINT&t;1&t;/* silently fix up unaligned user accesses */
DECL|macro|PR_UNALIGN_SIGBUS
macro_line|# define PR_UNALIGN_SIGBUS&t;2&t;/* generate SIGBUS on unaligned user access */
multiline_comment|/* Get/set whether or not to drop capabilities on setuid() away from uid 0 */
DECL|macro|PR_GET_KEEPCAPS
mdefine_line|#define PR_GET_KEEPCAPS   7
DECL|macro|PR_SET_KEEPCAPS
mdefine_line|#define PR_SET_KEEPCAPS   8
multiline_comment|/* Get/set floating-point emulation control bits (if meaningful) */
DECL|macro|PR_GET_FPEMU
mdefine_line|#define PR_GET_FPEMU  9
DECL|macro|PR_SET_FPEMU
mdefine_line|#define PR_SET_FPEMU 10
DECL|macro|PR_FPEMU_NOPRINT
macro_line|# define PR_FPEMU_NOPRINT&t;1&t;/* silently emulate fp operations accesses */
DECL|macro|PR_FPEMU_SIGFPE
macro_line|# define PR_FPEMU_SIGFPE&t;2&t;/* don&squot;t emulate fp operations, send SIGFPE instead */
multiline_comment|/* Get/set floating-point exception mode (if meaningful) */
DECL|macro|PR_GET_FPEXC
mdefine_line|#define PR_GET_FPEXC&t;11
DECL|macro|PR_SET_FPEXC
mdefine_line|#define PR_SET_FPEXC&t;12
DECL|macro|PR_FP_EXC_DISABLED
macro_line|# define PR_FP_EXC_DISABLED&t;0&t;/* FP exceptions disabled */
DECL|macro|PR_FP_EXC_NONRECOV
macro_line|# define PR_FP_EXC_NONRECOV&t;1&t;/* async non-recoverable exc. mode */
DECL|macro|PR_FP_EXC_ASYNC
macro_line|# define PR_FP_EXC_ASYNC&t;2&t;/* async recoverable exception mode */
DECL|macro|PR_FP_EXC_PRECISE
macro_line|# define PR_FP_EXC_PRECISE&t;3&t;/* precise exception mode */
macro_line|#endif /* _LINUX_PRCTL_H */
eof
