macro_line|#ifndef _LINUX_RESOURCE_H
DECL|macro|_LINUX_RESOURCE_H
mdefine_line|#define _LINUX_RESOURCE_H
macro_line|#include &lt;linux/time.h&gt;
multiline_comment|/*&n; * Resource control/accounting header file for linux&n; */
multiline_comment|/*&n; * Definition of struct rusage taken from BSD 4.3 Reno&n; * &n; * We don&squot;t support all of these yet, but we might as well have them....&n; * Otherwise, each time we add new items, programs which depend on this&n; * structure will lose.  This reduces the chances of that happening.&n; */
DECL|macro|RUSAGE_SELF
mdefine_line|#define&t;RUSAGE_SELF&t;0
DECL|macro|RUSAGE_CHILDREN
mdefine_line|#define&t;RUSAGE_CHILDREN&t;(-1)
DECL|macro|RUSAGE_BOTH
mdefine_line|#define RUSAGE_BOTH&t;(-2)&t;&t;/* sys_wait4() uses this */
DECL|struct|rusage
r_struct
id|rusage
(brace
DECL|member|ru_utime
r_struct
id|timeval
id|ru_utime
suffix:semicolon
multiline_comment|/* user time used */
DECL|member|ru_stime
r_struct
id|timeval
id|ru_stime
suffix:semicolon
multiline_comment|/* system time used */
DECL|member|ru_maxrss
r_int
id|ru_maxrss
suffix:semicolon
multiline_comment|/* maximum resident set size */
DECL|member|ru_ixrss
r_int
id|ru_ixrss
suffix:semicolon
multiline_comment|/* integral shared memory size */
DECL|member|ru_idrss
r_int
id|ru_idrss
suffix:semicolon
multiline_comment|/* integral unshared data size */
DECL|member|ru_isrss
r_int
id|ru_isrss
suffix:semicolon
multiline_comment|/* integral unshared stack size */
DECL|member|ru_minflt
r_int
id|ru_minflt
suffix:semicolon
multiline_comment|/* page reclaims */
DECL|member|ru_majflt
r_int
id|ru_majflt
suffix:semicolon
multiline_comment|/* page faults */
DECL|member|ru_nswap
r_int
id|ru_nswap
suffix:semicolon
multiline_comment|/* swaps */
DECL|member|ru_inblock
r_int
id|ru_inblock
suffix:semicolon
multiline_comment|/* block input operations */
DECL|member|ru_oublock
r_int
id|ru_oublock
suffix:semicolon
multiline_comment|/* block output operations */
DECL|member|ru_msgsnd
r_int
id|ru_msgsnd
suffix:semicolon
multiline_comment|/* messages sent */
DECL|member|ru_msgrcv
r_int
id|ru_msgrcv
suffix:semicolon
multiline_comment|/* messages received */
DECL|member|ru_nsignals
r_int
id|ru_nsignals
suffix:semicolon
multiline_comment|/* signals received */
DECL|member|ru_nvcsw
r_int
id|ru_nvcsw
suffix:semicolon
multiline_comment|/* voluntary context switches */
DECL|member|ru_nivcsw
r_int
id|ru_nivcsw
suffix:semicolon
multiline_comment|/* involuntary &quot; */
)brace
suffix:semicolon
DECL|struct|rlimit
r_struct
id|rlimit
(brace
DECL|member|rlim_cur
r_int
r_int
id|rlim_cur
suffix:semicolon
DECL|member|rlim_max
r_int
r_int
id|rlim_max
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PRIO_MIN
mdefine_line|#define&t;PRIO_MIN&t;(-20)
DECL|macro|PRIO_MAX
mdefine_line|#define&t;PRIO_MAX&t;20
DECL|macro|PRIO_PROCESS
mdefine_line|#define&t;PRIO_PROCESS&t;0
DECL|macro|PRIO_PGRP
mdefine_line|#define&t;PRIO_PGRP&t;1
DECL|macro|PRIO_USER
mdefine_line|#define&t;PRIO_USER&t;2
multiline_comment|/*&n; * Due to binary compatibility, the actual resource numbers&n; * may be different for different linux versions..&n; */
macro_line|#include &lt;asm/resource.h&gt;
macro_line|#endif
eof
