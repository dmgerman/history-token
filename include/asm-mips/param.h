macro_line|#ifndef _ASM_PARAM_H
DECL|macro|_ASM_PARAM_H
mdefine_line|#define _ASM_PARAM_H
macro_line|#ifndef HZ
macro_line|#ifdef __KERNEL__
multiline_comment|/* Safeguard against user stupidity  */
macro_line|#ifdef _SYS_PARAM_H
macro_line|#error Do not include &lt;asm/param.h&gt; with __KERNEL__ defined!
macro_line|#endif
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_DECSTATION
multiline_comment|/*&n;    * log2(HZ), change this here if you want another HZ value. This is also&n;    * used in dec_time_init.  Minimum is 1, Maximum is 15.&n;    */
DECL|macro|LOG_2_HZ
macro_line|#  define LOG_2_HZ 7
DECL|macro|HZ
macro_line|#  define HZ (1 &lt;&lt; LOG_2_HZ)
multiline_comment|/*&n;    * Ye olde division-by-multiplication trick.&n;    * This works only if 100 / HZ &lt;= 1&n;    */
DECL|macro|QUOTIENT
macro_line|#  define QUOTIENT ((1UL &lt;&lt; (32 - LOG_2_HZ)) * 100)
DECL|macro|hz_to_std
macro_line|#  define hz_to_std(a)                            &bslash;&n;   ({ unsigned int __res;&t;&t;&t;  &bslash;&n;      unsigned long __lo;&t;&t;&t;  &bslash;&n;        __asm__(&quot;multu&bslash;t%2,%3&bslash;n&bslash;t&quot;&t;&t;  &bslash;&n;&t;&t;:&quot;=h&quot; (__res), &quot;=l&quot; (__lo)&t;  &bslash;&n;&t;&t;:&quot;r&quot; (a),&quot;r&quot; (QUOTIENT));         &bslash;&n;        (__typeof__(a)) __res;})
macro_line|#else /* Not a DECstation  */
multiline_comment|/* This is the internal value of HZ, that is the rate at which the jiffies&n;   counter is increasing.  This value is independent from the external value&n;   and can be changed in order to suit the hardware and application&n;   requirements.  */
DECL|macro|HZ
macro_line|#  define HZ 100
DECL|macro|hz_to_std
macro_line|#  define hz_to_std(a) (a)
macro_line|#endif /* Not a DECstation */
macro_line|#else /* defined(__KERNEL__)  */
multiline_comment|/* This is the external value of HZ as seen by user programs.  Don&squot;t change&n;   unless you know what you&squot;re doing - changing breaks binary compatibility.  */
DECL|macro|HZ
mdefine_line|#define HZ 100
macro_line|#endif /* defined(__KERNEL__)  */
macro_line|#endif /* defined(HZ)  */
DECL|macro|EXEC_PAGESIZE
mdefine_line|#define EXEC_PAGESIZE&t;4096
macro_line|#ifndef NGROUPS
DECL|macro|NGROUPS
mdefine_line|#define NGROUPS&t;&t;32
macro_line|#endif
macro_line|#ifndef NOGROUP
DECL|macro|NOGROUP
mdefine_line|#define NOGROUP&t;&t;(-1)
macro_line|#endif
DECL|macro|MAXHOSTNAMELEN
mdefine_line|#define MAXHOSTNAMELEN&t;64&t;/* max length of hostname */
macro_line|#endif /* _ASM_PARAM_H */
eof
