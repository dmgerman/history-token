multiline_comment|/*&n; *  BSD Process Accounting for Linux - Definitions&n; *&n; *  Author: Marco van Wieringen (mvw@planets.elm.net)&n; *&n; *  This header file contains the definitions needed to implement&n; *  BSD-style process accounting. The kernel accounting code and all&n; *  user-level programs that try to do something useful with the&n; *  process accounting log must include this file.&n; *&n; *  Copyright (C) 1995 - 1997 Marco van Wieringen - ELM Consultancy B.V.&n; *&n; */
macro_line|#ifndef _LINUX_ACCT_H
DECL|macro|_LINUX_ACCT_H
mdefine_line|#define _LINUX_ACCT_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* &n; *  comp_t is a 16-bit &quot;floating&quot; point number with a 3-bit base 8&n; *  exponent and a 13-bit fraction. See linux/kernel/acct.c for the&n; *  specific encoding system used.&n; */
DECL|typedef|comp_t
r_typedef
id|__u16
id|comp_t
suffix:semicolon
multiline_comment|/*&n; *   accounting file record&n; *&n; *   This structure contains all of the information written out to the&n; *   process accounting file whenever a process exits.&n; */
DECL|macro|ACCT_COMM
mdefine_line|#define ACCT_COMM&t;16
DECL|struct|acct
r_struct
id|acct
(brace
DECL|member|ac_flag
r_char
id|ac_flag
suffix:semicolon
multiline_comment|/* Accounting Flags */
multiline_comment|/*&n; *&t;No binary format break with 2.0 - but when we hit 32bit uid we&squot;ll&n; *&t;have to bite one&n; */
DECL|member|ac_uid
id|__u16
id|ac_uid
suffix:semicolon
multiline_comment|/* Accounting Real User ID */
DECL|member|ac_gid
id|__u16
id|ac_gid
suffix:semicolon
multiline_comment|/* Accounting Real Group ID */
DECL|member|ac_tty
id|__u16
id|ac_tty
suffix:semicolon
multiline_comment|/* Accounting Control Terminal */
DECL|member|ac_btime
id|__u32
id|ac_btime
suffix:semicolon
multiline_comment|/* Accounting Process Creation Time */
DECL|member|ac_utime
id|comp_t
id|ac_utime
suffix:semicolon
multiline_comment|/* Accounting User Time */
DECL|member|ac_stime
id|comp_t
id|ac_stime
suffix:semicolon
multiline_comment|/* Accounting System Time */
DECL|member|ac_etime
id|comp_t
id|ac_etime
suffix:semicolon
multiline_comment|/* Accounting Elapsed Time */
DECL|member|ac_mem
id|comp_t
id|ac_mem
suffix:semicolon
multiline_comment|/* Accounting Average Memory Usage */
DECL|member|ac_io
id|comp_t
id|ac_io
suffix:semicolon
multiline_comment|/* Accounting Chars Transferred */
DECL|member|ac_rw
id|comp_t
id|ac_rw
suffix:semicolon
multiline_comment|/* Accounting Blocks Read or Written */
DECL|member|ac_minflt
id|comp_t
id|ac_minflt
suffix:semicolon
multiline_comment|/* Accounting Minor Pagefaults */
DECL|member|ac_majflt
id|comp_t
id|ac_majflt
suffix:semicolon
multiline_comment|/* Accounting Major Pagefaults */
DECL|member|ac_swaps
id|comp_t
id|ac_swaps
suffix:semicolon
multiline_comment|/* Accounting Number of Swaps */
DECL|member|ac_exitcode
id|__u32
id|ac_exitcode
suffix:semicolon
multiline_comment|/* Accounting Exitcode */
DECL|member|ac_comm
r_char
id|ac_comm
(braket
id|ACCT_COMM
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Accounting Command Name */
DECL|member|ac_pad
r_char
id|ac_pad
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* Accounting Padding Bytes */
)brace
suffix:semicolon
multiline_comment|/*&n; *  accounting flags&n; */
multiline_comment|/* bit set when the process ... */
DECL|macro|AFORK
mdefine_line|#define AFORK&t;&t;0x01&t;/* ... executed fork, but did not exec */
DECL|macro|ASU
mdefine_line|#define ASU&t;&t;0x02&t;/* ... used super-user privileges */
DECL|macro|ACOMPAT
mdefine_line|#define ACOMPAT&t;&t;0x04&t;/* ... used compatibility mode (VAX only not used) */
DECL|macro|ACORE
mdefine_line|#define ACORE&t;&t;0x08&t;/* ... dumped core */
DECL|macro|AXSIG
mdefine_line|#define AXSIG&t;&t;0x10&t;/* ... was killed by a signal */
DECL|macro|AHZ
mdefine_line|#define AHZ&t;&t;100
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_BSD_PROCESS_ACCT
r_extern
r_void
id|acct_auto_close
c_func
(paren
id|kdev_t
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|acct_process
c_func
(paren
r_int
id|exitcode
)paren
suffix:semicolon
macro_line|#else
DECL|macro|acct_auto_close
mdefine_line|#define acct_auto_close(x)&t;do { } while (0)
DECL|macro|acct_process
mdefine_line|#define acct_process(x)&t;&t;do { } while (0)
macro_line|#endif
macro_line|#endif&t;/* __KERNEL */
macro_line|#endif&t;/* _LINUX_ACCT_H */
eof
