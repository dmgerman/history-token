macro_line|#ifndef _ASM_X86_64_VSYSCALL_H_
DECL|macro|_ASM_X86_64_VSYSCALL_H_
mdefine_line|#define _ASM_X86_64_VSYSCALL_H_
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/seqlock.h&gt;
DECL|enum|vsyscall_num
r_enum
id|vsyscall_num
(brace
DECL|enumerator|__NR_vgettimeofday
id|__NR_vgettimeofday
comma
DECL|enumerator|__NR_vtime
id|__NR_vtime
comma
)brace
suffix:semicolon
DECL|macro|VSYSCALL_START
mdefine_line|#define VSYSCALL_START (-10UL &lt;&lt; 20)
DECL|macro|VSYSCALL_SIZE
mdefine_line|#define VSYSCALL_SIZE 1024
DECL|macro|VSYSCALL_END
mdefine_line|#define VSYSCALL_END (-2UL &lt;&lt; 20)
DECL|macro|VSYSCALL_ADDR
mdefine_line|#define VSYSCALL_ADDR(vsyscall_nr) (VSYSCALL_START+VSYSCALL_SIZE*(vsyscall_nr))
macro_line|#ifdef __KERNEL__
DECL|macro|__section_hpet
mdefine_line|#define __section_hpet __attribute__ ((unused, __section__ (&quot;.hpet&quot;), aligned(16)))
DECL|macro|__section_wall_jiffies
mdefine_line|#define __section_wall_jiffies __attribute__ ((unused, __section__ (&quot;.wall_jiffies&quot;), aligned(16)))
DECL|macro|__section_jiffies
mdefine_line|#define __section_jiffies __attribute__ ((unused, __section__ (&quot;.jiffies&quot;), aligned(16)))
DECL|macro|__section_sys_tz
mdefine_line|#define __section_sys_tz __attribute__ ((unused, __section__ (&quot;.sys_tz&quot;), aligned(16)))
DECL|macro|__section_sysctl_vsyscall
mdefine_line|#define __section_sysctl_vsyscall __attribute__ ((unused, __section__ (&quot;.sysctl_vsyscall&quot;), aligned(16)))
DECL|macro|__section_xtime
mdefine_line|#define __section_xtime __attribute__ ((unused, __section__ (&quot;.xtime&quot;), aligned(16)))
DECL|macro|__section_xtime_lock
mdefine_line|#define __section_xtime_lock __attribute__ ((unused, __section__ (&quot;.xtime_lock&quot;), aligned(L1_CACHE_BYTES)))
DECL|struct|hpet_data
r_struct
id|hpet_data
(brace
DECL|member|address
r_int
id|address
suffix:semicolon
multiline_comment|/* base address */
DECL|member|hz
r_int
r_int
id|hz
suffix:semicolon
multiline_comment|/* HPET clocks / sec */
DECL|member|trigger
r_int
id|trigger
suffix:semicolon
multiline_comment|/* value at last interrupt */
DECL|member|last
r_int
id|last
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|last_tsc
r_int
r_int
id|last_tsc
suffix:semicolon
DECL|member|ticks
r_int
id|ticks
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|hpet_readl
mdefine_line|#define hpet_readl(a)           readl(fix_to_virt(FIX_HPET_BASE) + a)
DECL|macro|hpet_writel
mdefine_line|#define hpet_writel(d,a)        writel(d, fix_to_virt(FIX_HPET_BASE) + a)
multiline_comment|/* vsyscall space (readonly) */
r_extern
r_struct
id|hpet_data
id|__hpet
suffix:semicolon
r_extern
r_struct
id|timespec
id|__xtime
suffix:semicolon
r_extern
r_volatile
r_int
r_int
id|__jiffies
suffix:semicolon
r_extern
r_int
r_int
id|__wall_jiffies
suffix:semicolon
r_extern
r_struct
id|timezone
id|__sys_tz
suffix:semicolon
r_extern
id|seqlock_t
id|__xtime_lock
suffix:semicolon
multiline_comment|/* kernel space (writeable) */
r_extern
r_struct
id|hpet_data
id|hpet
suffix:semicolon
r_extern
r_int
r_int
id|wall_jiffies
suffix:semicolon
r_extern
r_struct
id|timezone
id|sys_tz
suffix:semicolon
r_extern
r_int
id|sysctl_vsyscall
suffix:semicolon
r_extern
id|seqlock_t
id|xtime_lock
suffix:semicolon
DECL|macro|ARCH_HAVE_XTIME_LOCK
mdefine_line|#define ARCH_HAVE_XTIME_LOCK 1
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_X86_64_VSYSCALL_H_ */
eof
