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
macro_line|#endif /* _LINUX_PRCTL_H */
eof
