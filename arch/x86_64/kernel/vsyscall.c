multiline_comment|/*&n; *  linux/arch/x86_64/kernel/vsyscall.c&n; *&n; *  Copyright (C) 2001 Andrea Arcangeli &lt;andrea@suse.de&gt; SuSE&n; *&n; *  Thanks to hpa@transmeta.com for some useful hint.&n; *  Special thanks to Ingo Molnar for his early experience with&n; *  a different vsyscall implementation for Linux/IA32 and for the name.&n; *&n; *  vsyscall 1 is located at -10Mbyte, vsyscall 2 is located&n; *  at virtual address -10Mbyte+1024bytes etc... There are at max 8192&n; *  vsyscalls. One vsyscall can reserve more than 1 slot to avoid&n; *  jumping out of line if necessary.&n; *&n; *  $Id: vsyscall.c,v 1.9 2002/03/21 13:42:58 ak Exp $&n; */
multiline_comment|/*&n; * TODO 2001-03-20:&n; *&n; * 1) make page fault handler detect faults on page1-page-last of the vsyscall&n; *    virtual space, and make it increase %rip and write -ENOSYS in %rax (so&n; *    we&squot;ll be able to upgrade to a new glibc without upgrading kernel after&n; *    we add more vsyscalls.&n; * 2) Possibly we need a fixmap table for the vsyscalls too if we want&n; *    to avoid SIGSEGV and we want to return -EFAULT from the vsyscalls as well.&n; *    Can we segfault inside a &quot;syscall&quot;? We can fix this anytime and those fixes&n; *    won&squot;t be visible for userspace. Not fixing this is a noop for correct programs,&n; *    broken programs will segfault and there&squot;s no security risk until we choose to&n; *    fix it.&n; *&n; * These are not urgent things that we need to address only before shipping the first&n; * production binary kernels.&n; */
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;asm/vsyscall.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
DECL|macro|__vsyscall
mdefine_line|#define __vsyscall(nr) __attribute__ ((unused,__section__(&quot;.vsyscall_&quot; #nr)))
DECL|macro|NO_VSYSCALL
mdefine_line|#define NO_VSYSCALL 1
macro_line|#ifdef NO_VSYSCALL
macro_line|#include &lt;asm/unistd.h&gt;
DECL|variable|__section_vxtime_sequence
r_static
r_int
id|errno
id|__section_vxtime_sequence
suffix:semicolon
r_static
r_inline
id|_syscall2
c_func
(paren
r_int
comma
id|gettimeofday
comma
r_struct
id|timeval
op_star
comma
id|tv
comma
r_struct
id|timezone
op_star
comma
id|tz
)paren
macro_line|#else
r_static
r_inline
r_void
id|timeval_normalize
c_func
(paren
r_struct
id|timeval
op_star
id|tv
)paren
(brace
id|time_t
id|__sec
suffix:semicolon
id|__sec
op_assign
id|tv-&gt;tv_usec
op_div
l_int|1000000
suffix:semicolon
r_if
c_cond
(paren
id|__sec
)paren
(brace
id|tv-&gt;tv_usec
op_mod_assign
l_int|1000000
suffix:semicolon
id|tv-&gt;tv_sec
op_add_assign
id|__sec
suffix:semicolon
)brace
)brace
r_int
id|__vxtime_sequence
(braket
l_int|2
)braket
id|__section_vxtime_sequence
suffix:semicolon
r_static
r_inline
r_void
id|do_vgettimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
)paren
(brace
r_int
id|sequence
comma
id|t
suffix:semicolon
r_int
r_int
id|sec
comma
id|usec
suffix:semicolon
r_do
(brace
id|sequence
op_assign
id|__vxtime_sequence
(braket
l_int|1
)braket
suffix:semicolon
id|rmb
c_func
(paren
)paren
suffix:semicolon
id|rdtscll
c_func
(paren
id|t
)paren
suffix:semicolon
id|sec
op_assign
id|__xtime.tv_sec
suffix:semicolon
id|usec
op_assign
id|__xtime.tv_usec
op_plus
(paren
id|__jiffies
op_minus
id|__wall_jiffies
)paren
op_star
(paren
l_int|1000000
op_div
id|HZ
)paren
op_plus
(paren
id|t
op_minus
id|__hpet.last_tsc
)paren
op_star
(paren
l_int|1000000
op_div
id|HZ
)paren
op_div
id|__hpet.ticks
op_plus
id|__hpet.offset
suffix:semicolon
id|rmb
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|sequence
op_ne
id|__vxtime_sequence
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|tv-&gt;tv_sec
op_assign
id|sec
op_plus
id|usec
op_div
l_int|1000000
suffix:semicolon
id|tv-&gt;tv_usec
op_assign
id|usec
op_mod
l_int|1000000
suffix:semicolon
)brace
r_static
r_inline
r_void
id|do_get_tz
c_func
(paren
r_struct
id|timezone
op_star
id|tz
)paren
(brace
r_int
id|sequence
suffix:semicolon
r_do
(brace
id|sequence
op_assign
id|__vxtime_sequence
(braket
l_int|1
)braket
suffix:semicolon
id|rmb
c_func
(paren
)paren
suffix:semicolon
op_star
id|tz
op_assign
id|__sys_tz
suffix:semicolon
id|rmb
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|sequence
op_ne
id|__vxtime_sequence
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|vgettimeofday
r_static
r_int
id|__vsyscall
c_func
(paren
l_int|0
)paren
id|vgettimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
comma
r_struct
id|timezone
op_star
id|tz
)paren
(brace
macro_line|#ifdef NO_VSYSCALL
r_return
id|gettimeofday
c_func
(paren
id|tv
comma
id|tz
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|tv
)paren
id|do_vgettimeofday
c_func
(paren
id|tv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tz
)paren
id|do_get_tz
c_func
(paren
id|tz
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
DECL|function|vtime
r_static
id|time_t
id|__vsyscall
c_func
(paren
l_int|1
)paren
id|vtime
c_func
(paren
id|time_t
op_star
id|t
)paren
(brace
r_struct
id|timeval
id|tv
suffix:semicolon
id|vgettimeofday
c_func
(paren
op_amp
id|tv
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t
)paren
op_star
id|t
op_assign
id|tv.tv_sec
suffix:semicolon
r_return
id|tv.tv_sec
suffix:semicolon
)brace
DECL|function|venosys_0
r_static
r_int
id|__vsyscall
c_func
(paren
l_int|2
)paren
id|venosys_0
c_func
(paren
r_void
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|venosys_1
r_static
r_int
id|__vsyscall
c_func
(paren
l_int|3
)paren
id|venosys_1
c_func
(paren
r_void
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|map_vsyscall
r_static
r_void
id|__init
id|map_vsyscall
c_func
(paren
r_void
)paren
(brace
r_extern
r_char
id|__vsyscall_0
suffix:semicolon
r_int
r_int
id|physaddr_page0
op_assign
(paren
r_int
r_int
)paren
op_amp
id|__vsyscall_0
op_minus
id|__START_KERNEL_map
suffix:semicolon
id|__set_fixmap
c_func
(paren
id|VSYSCALL_FIRST_PAGE
comma
id|physaddr_page0
comma
id|PAGE_KERNEL_VSYSCALL
)paren
suffix:semicolon
)brace
DECL|function|vsyscall_init
r_static
r_int
id|__init
id|vsyscall_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;VSYSCALL: consistency checks...&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
op_amp
id|vgettimeofday
op_ne
id|VSYSCALL_ADDR
c_func
(paren
id|__NR_vgettimeofday
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;vgettimeofday link addr broken&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
op_amp
id|vtime
op_ne
id|VSYSCALL_ADDR
c_func
(paren
id|__NR_vtime
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;vtime link addr broken&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|VSYSCALL_ADDR
c_func
(paren
l_int|0
)paren
op_ne
id|__fix_to_virt
c_func
(paren
id|VSYSCALL_FIRST_PAGE
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;fixmap first vsyscall %lx should be %lx&quot;
comma
id|__fix_to_virt
c_func
(paren
id|VSYSCALL_FIRST_PAGE
)paren
comma
id|VSYSCALL_ADDR
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;passed...mapping...&quot;
)paren
suffix:semicolon
id|map_vsyscall
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;done.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|vsyscall_init
id|__initcall
c_func
(paren
id|vsyscall_init
)paren
suffix:semicolon
eof
