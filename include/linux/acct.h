multiline_comment|/*&n; *  BSD Process Accounting for Linux - Definitions&n; *&n; *  Author: Marco van Wieringen (mvw@planets.elm.net)&n; *&n; *  This header file contains the definitions needed to implement&n; *  BSD-style process accounting. The kernel accounting code and all&n; *  user-level programs that try to do something useful with the&n; *  process accounting log must include this file.&n; *&n; *  Copyright (C) 1995 - 1997 Marco van Wieringen - ELM Consultancy B.V.&n; *&n; */
macro_line|#ifndef _LINUX_ACCT_H
DECL|macro|_LINUX_ACCT_H
mdefine_line|#define _LINUX_ACCT_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/* &n; *  comp_t is a 16-bit &quot;floating&quot; point number with a 3-bit base 8&n; *  exponent and a 13-bit fraction.&n; *  comp2_t is 24-bit with 5-bit base 2 exponent and 20 bit fraction&n; *  (leading 1 not stored).&n; *  See linux/kernel/acct.c for the specific encoding systems used.&n; */
DECL|typedef|comp_t
r_typedef
id|__u16
id|comp_t
suffix:semicolon
DECL|typedef|comp2_t
r_typedef
id|__u32
id|comp2_t
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
multiline_comment|/* Flags */
DECL|member|ac_version
r_char
id|ac_version
suffix:semicolon
multiline_comment|/* Always set to ACCT_VERSION */
multiline_comment|/* for binary compatibility back until 2.0 */
DECL|member|ac_uid16
id|__u16
id|ac_uid16
suffix:semicolon
multiline_comment|/* LSB of Real User ID */
DECL|member|ac_gid16
id|__u16
id|ac_gid16
suffix:semicolon
multiline_comment|/* LSB of Real Group ID */
DECL|member|ac_tty
id|__u16
id|ac_tty
suffix:semicolon
multiline_comment|/* Control Terminal */
DECL|member|ac_btime
id|__u32
id|ac_btime
suffix:semicolon
multiline_comment|/* Process Creation Time */
DECL|member|ac_utime
id|comp_t
id|ac_utime
suffix:semicolon
multiline_comment|/* User Time */
DECL|member|ac_stime
id|comp_t
id|ac_stime
suffix:semicolon
multiline_comment|/* System Time */
DECL|member|ac_etime
id|comp_t
id|ac_etime
suffix:semicolon
multiline_comment|/* Elapsed Time */
DECL|member|ac_mem
id|comp_t
id|ac_mem
suffix:semicolon
multiline_comment|/* Average Memory Usage */
DECL|member|ac_io
id|comp_t
id|ac_io
suffix:semicolon
multiline_comment|/* Chars Transferred */
DECL|member|ac_rw
id|comp_t
id|ac_rw
suffix:semicolon
multiline_comment|/* Blocks Read or Written */
DECL|member|ac_minflt
id|comp_t
id|ac_minflt
suffix:semicolon
multiline_comment|/* Minor Pagefaults */
DECL|member|ac_majflt
id|comp_t
id|ac_majflt
suffix:semicolon
multiline_comment|/* Major Pagefaults */
DECL|member|ac_swaps
id|comp_t
id|ac_swaps
suffix:semicolon
multiline_comment|/* Number of Swaps */
multiline_comment|/* m68k had no padding here. */
macro_line|#if !defined(CONFIG_M68K) || !defined(__KERNEL__)
DECL|member|ac_ahz
id|__u16
id|ac_ahz
suffix:semicolon
multiline_comment|/* AHZ */
macro_line|#endif
DECL|member|ac_exitcode
id|__u32
id|ac_exitcode
suffix:semicolon
multiline_comment|/* Exitcode */
DECL|member|ac_comm
r_char
id|ac_comm
(braket
id|ACCT_COMM
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Command Name */
DECL|member|ac_etime_hi
id|__u8
id|ac_etime_hi
suffix:semicolon
multiline_comment|/* Elapsed Time MSB */
DECL|member|ac_etime_lo
id|__u16
id|ac_etime_lo
suffix:semicolon
multiline_comment|/* Elapsed Time LSB */
DECL|member|ac_uid
id|__u32
id|ac_uid
suffix:semicolon
multiline_comment|/* Real User ID */
DECL|member|ac_gid
id|__u32
id|ac_gid
suffix:semicolon
multiline_comment|/* Real Group ID */
)brace
suffix:semicolon
DECL|struct|acct_v3
r_struct
id|acct_v3
(brace
DECL|member|ac_flag
r_char
id|ac_flag
suffix:semicolon
multiline_comment|/* Flags */
DECL|member|ac_version
r_char
id|ac_version
suffix:semicolon
multiline_comment|/* Always set to ACCT_VERSION */
DECL|member|ac_tty
id|__u16
id|ac_tty
suffix:semicolon
multiline_comment|/* Control Terminal */
DECL|member|ac_exitcode
id|__u32
id|ac_exitcode
suffix:semicolon
multiline_comment|/* Exitcode */
DECL|member|ac_uid
id|__u32
id|ac_uid
suffix:semicolon
multiline_comment|/* Real User ID */
DECL|member|ac_gid
id|__u32
id|ac_gid
suffix:semicolon
multiline_comment|/* Real Group ID */
DECL|member|ac_pid
id|__u32
id|ac_pid
suffix:semicolon
multiline_comment|/* Process ID */
DECL|member|ac_ppid
id|__u32
id|ac_ppid
suffix:semicolon
multiline_comment|/* Parent Process ID */
DECL|member|ac_btime
id|__u32
id|ac_btime
suffix:semicolon
multiline_comment|/* Process Creation Time */
macro_line|#ifdef __KERNEL__
DECL|member|ac_etime
id|__u32
id|ac_etime
suffix:semicolon
multiline_comment|/* Elapsed Time */
macro_line|#else
DECL|member|ac_etime
r_float
id|ac_etime
suffix:semicolon
multiline_comment|/* Elapsed Time */
macro_line|#endif
DECL|member|ac_utime
id|comp_t
id|ac_utime
suffix:semicolon
multiline_comment|/* User Time */
DECL|member|ac_stime
id|comp_t
id|ac_stime
suffix:semicolon
multiline_comment|/* System Time */
DECL|member|ac_mem
id|comp_t
id|ac_mem
suffix:semicolon
multiline_comment|/* Average Memory Usage */
DECL|member|ac_io
id|comp_t
id|ac_io
suffix:semicolon
multiline_comment|/* Chars Transferred */
DECL|member|ac_rw
id|comp_t
id|ac_rw
suffix:semicolon
multiline_comment|/* Blocks Read or Written */
DECL|member|ac_minflt
id|comp_t
id|ac_minflt
suffix:semicolon
multiline_comment|/* Minor Pagefaults */
DECL|member|ac_majflt
id|comp_t
id|ac_majflt
suffix:semicolon
multiline_comment|/* Major Pagefaults */
DECL|member|ac_swaps
id|comp_t
id|ac_swaps
suffix:semicolon
multiline_comment|/* Number of Swaps */
DECL|member|ac_comm
r_char
id|ac_comm
(braket
id|ACCT_COMM
)braket
suffix:semicolon
multiline_comment|/* Command Name */
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
macro_line|#ifdef __BIG_ENDIAN
DECL|macro|ACCT_BYTEORDER
mdefine_line|#define ACCT_BYTEORDER&t;0x80&t;/* accounting file is big endian */
macro_line|#else
DECL|macro|ACCT_BYTEORDER
mdefine_line|#define ACCT_BYTEORDER&t;0x00&t;/* accounting file is little endian */
macro_line|#endif
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_BSD_PROCESS_ACCT
r_struct
id|super_block
suffix:semicolon
r_extern
r_void
id|acct_auto_close
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_extern
r_void
id|acct_process
c_func
(paren
r_int
id|exitcode
)paren
suffix:semicolon
r_extern
r_void
id|acct_update_integrals
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
r_extern
r_void
id|acct_clear_integrals
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
macro_line|#else
DECL|macro|acct_auto_close
mdefine_line|#define acct_auto_close(x)&t;do { } while (0)
DECL|macro|acct_process
mdefine_line|#define acct_process(x)&t;&t;do { } while (0)
DECL|macro|acct_update_integrals
mdefine_line|#define acct_update_integrals(x)&t;&t;do { } while (0)
DECL|macro|acct_clear_integrals
mdefine_line|#define acct_clear_integrals(task)&t;do { } while (0)
macro_line|#endif
multiline_comment|/*&n; * ACCT_VERSION numbers as yet defined:&n; * 0: old format (until 2.6.7) with 16 bit uid/gid&n; * 1: extended variant (binary compatible on M68K)&n; * 2: extended variant (binary compatible on everything except M68K)&n; * 3: new binary incompatible format (64 bytes)&n; * 4: new binary incompatible format (128 bytes)&n; * 5: new binary incompatible format (128 bytes, second half)&n; *&n; */
macro_line|#ifdef CONFIG_BSD_PROCESS_ACCT_V3
DECL|macro|ACCT_VERSION
mdefine_line|#define ACCT_VERSION&t;3
DECL|macro|AHZ
mdefine_line|#define AHZ&t;&t;100
DECL|typedef|acct_t
r_typedef
r_struct
id|acct_v3
id|acct_t
suffix:semicolon
macro_line|#else
macro_line|#ifdef CONFIG_M68K
DECL|macro|ACCT_VERSION
mdefine_line|#define ACCT_VERSION&t;1
macro_line|#else
DECL|macro|ACCT_VERSION
mdefine_line|#define ACCT_VERSION&t;2
macro_line|#endif
DECL|macro|AHZ
mdefine_line|#define AHZ&t;&t;(USER_HZ)
DECL|typedef|acct_t
r_typedef
r_struct
id|acct
id|acct_t
suffix:semicolon
macro_line|#endif
macro_line|#else
DECL|macro|ACCT_VERSION
mdefine_line|#define ACCT_VERSION&t;2
DECL|macro|AHZ
mdefine_line|#define AHZ&t;&t;(HZ)
macro_line|#endif&t;/* __KERNEL */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Yet another set of HZ to *HZ helper functions.&n; * See &lt;linux/times.h&gt; for the original.&n; */
DECL|function|jiffies_to_AHZ
r_static
r_inline
id|u32
id|jiffies_to_AHZ
c_func
(paren
r_int
r_int
id|x
)paren
(brace
macro_line|#if (TICK_NSEC % (NSEC_PER_SEC / AHZ)) == 0
r_return
id|x
op_div
(paren
id|HZ
op_div
id|USER_HZ
)paren
suffix:semicolon
macro_line|#else
id|u64
id|tmp
op_assign
(paren
id|u64
)paren
id|x
op_star
id|TICK_NSEC
suffix:semicolon
id|do_div
c_func
(paren
id|tmp
comma
(paren
id|NSEC_PER_SEC
op_div
id|AHZ
)paren
)paren
suffix:semicolon
r_return
(paren
r_int
)paren
id|tmp
suffix:semicolon
macro_line|#endif
)brace
DECL|function|nsec_to_AHZ
r_static
r_inline
id|u64
id|nsec_to_AHZ
c_func
(paren
id|u64
id|x
)paren
(brace
macro_line|#if (NSEC_PER_SEC % AHZ) == 0
id|do_div
c_func
(paren
id|x
comma
(paren
id|NSEC_PER_SEC
op_div
id|AHZ
)paren
)paren
suffix:semicolon
macro_line|#elif (AHZ % 512) == 0
id|x
op_mul_assign
id|AHZ
op_div
l_int|512
suffix:semicolon
id|do_div
c_func
(paren
id|x
comma
(paren
id|NSEC_PER_SEC
op_div
l_int|512
)paren
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/*&n;         * max relative error 5.7e-8 (1.8s per year) for AHZ &lt;= 1024,&n;         * overflow after 64.99 years.&n;         * exact for AHZ=60, 72, 90, 120, 144, 180, 300, 600, 900, ...&n;         */
id|x
op_mul_assign
l_int|9
suffix:semicolon
id|do_div
c_func
(paren
id|x
comma
(paren
r_int
r_int
)paren
(paren
(paren
l_int|9ull
op_star
id|NSEC_PER_SEC
op_plus
(paren
id|AHZ
op_div
l_int|2
)paren
)paren
op_div
id|AHZ
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|x
suffix:semicolon
)brace
macro_line|#endif  /* __KERNEL */
macro_line|#endif&t;/* _LINUX_ACCT_H */
eof
