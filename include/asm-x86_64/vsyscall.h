macro_line|#ifndef _ASM_X86_64_VSYSCALL_H_
DECL|macro|_ASM_X86_64_VSYSCALL_H_
mdefine_line|#define _ASM_X86_64_VSYSCALL_H_
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
DECL|macro|__section_last_tsc_low
mdefine_line|#define __section_last_tsc_low&t;__attribute__ ((unused, __section__ (&quot;.last_tsc_low&quot;)))
DECL|macro|__section_delay_at_last_interrupt
mdefine_line|#define __section_delay_at_last_interrupt&t;__attribute__ ((unused, __section__ (&quot;.delay_at_last_interrupt&quot;)))
DECL|macro|__section_fast_gettimeoffset_quotient
mdefine_line|#define __section_fast_gettimeoffset_quotient&t;__attribute__ ((unused, __section__ (&quot;.fast_gettimeoffset_quotient&quot;)))
DECL|macro|__section_wall_jiffies
mdefine_line|#define __section_wall_jiffies __attribute__ ((unused, __section__ (&quot;.wall_jiffies&quot;)))
DECL|macro|__section_jiffies
mdefine_line|#define __section_jiffies __attribute__ ((unused, __section__ (&quot;.jiffies&quot;)))
DECL|macro|__section_sys_tz
mdefine_line|#define __section_sys_tz __attribute__ ((unused, __section__ (&quot;.sys_tz&quot;)))
DECL|macro|__section_xtime
mdefine_line|#define __section_xtime __attribute__ ((unused, __section__ (&quot;.xtime&quot;)))
DECL|macro|__section_vxtime_sequence
mdefine_line|#define __section_vxtime_sequence __attribute__ ((unused, __section__ (&quot;.vxtime_sequence&quot;)))
multiline_comment|/* vsyscall space (readonly) */
r_extern
r_int
id|__vxtime_sequence
(braket
l_int|2
)braket
suffix:semicolon
r_extern
r_int
id|__delay_at_last_interrupt
suffix:semicolon
r_extern
r_int
r_int
id|__last_tsc_low
suffix:semicolon
r_extern
r_int
r_int
id|__fast_gettimeoffset_quotient
suffix:semicolon
r_extern
r_struct
id|timeval
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
multiline_comment|/* kernel space (writeable) */
r_extern
r_int
r_int
id|last_tsc_low
suffix:semicolon
r_extern
r_int
id|delay_at_last_interrupt
suffix:semicolon
r_extern
r_int
r_int
id|fast_gettimeoffset_quotient
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
id|vxtime_sequence
(braket
l_int|2
)braket
suffix:semicolon
DECL|macro|vxtime_lock
mdefine_line|#define vxtime_lock() do { vxtime_sequence[0]++; wmb(); } while(0)
DECL|macro|vxtime_unlock
mdefine_line|#define vxtime_unlock() do { wmb(); vxtime_sequence[1]++; } while (0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_X86_64_VSYSCALL_H_ */
eof
