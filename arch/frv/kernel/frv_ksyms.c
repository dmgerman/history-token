macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/current.h&gt;
r_extern
r_void
id|dump_thread
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_struct
id|user
op_star
)paren
suffix:semicolon
r_extern
r_int
id|__memcpy_user
c_func
(paren
r_void
op_star
id|dst
comma
r_const
r_void
op_star
id|src
comma
r_int
id|count
)paren
suffix:semicolon
multiline_comment|/* platform dependent support */
DECL|variable|__ioremap
id|EXPORT_SYMBOL
c_func
(paren
id|__ioremap
)paren
suffix:semicolon
DECL|variable|iounmap
id|EXPORT_SYMBOL
c_func
(paren
id|iounmap
)paren
suffix:semicolon
DECL|variable|dump_thread
id|EXPORT_SYMBOL
c_func
(paren
id|dump_thread
)paren
suffix:semicolon
DECL|variable|strnlen
id|EXPORT_SYMBOL
c_func
(paren
id|strnlen
)paren
suffix:semicolon
DECL|variable|strrchr
id|EXPORT_SYMBOL
c_func
(paren
id|strrchr
)paren
suffix:semicolon
DECL|variable|strstr
id|EXPORT_SYMBOL
c_func
(paren
id|strstr
)paren
suffix:semicolon
DECL|variable|strchr
id|EXPORT_SYMBOL
c_func
(paren
id|strchr
)paren
suffix:semicolon
DECL|variable|strcat
id|EXPORT_SYMBOL
c_func
(paren
id|strcat
)paren
suffix:semicolon
DECL|variable|strlen
id|EXPORT_SYMBOL
c_func
(paren
id|strlen
)paren
suffix:semicolon
DECL|variable|strcmp
id|EXPORT_SYMBOL
c_func
(paren
id|strcmp
)paren
suffix:semicolon
DECL|variable|strncmp
id|EXPORT_SYMBOL
c_func
(paren
id|strncmp
)paren
suffix:semicolon
DECL|variable|strncpy
id|EXPORT_SYMBOL
c_func
(paren
id|strncpy
)paren
suffix:semicolon
DECL|variable|ip_fast_csum
id|EXPORT_SYMBOL
c_func
(paren
id|ip_fast_csum
)paren
suffix:semicolon
macro_line|#if 0
id|EXPORT_SYMBOL
c_func
(paren
id|local_irq_count
)paren
suffix:semicolon
id|EXPORT_SYMBOL
c_func
(paren
id|local_bh_count
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|kernel_thread
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_thread
)paren
suffix:semicolon
DECL|variable|enable_irq
id|EXPORT_SYMBOL
c_func
(paren
id|enable_irq
)paren
suffix:semicolon
DECL|variable|disable_irq
id|EXPORT_SYMBOL
c_func
(paren
id|disable_irq
)paren
suffix:semicolon
DECL|variable|__res_bus_clock_speed_HZ
id|EXPORT_SYMBOL
c_func
(paren
id|__res_bus_clock_speed_HZ
)paren
suffix:semicolon
DECL|variable|__page_offset
id|EXPORT_SYMBOL
c_func
(paren
id|__page_offset
)paren
suffix:semicolon
DECL|variable|__memcpy_user
id|EXPORT_SYMBOL
c_func
(paren
id|__memcpy_user
)paren
suffix:semicolon
DECL|variable|flush_dcache_page
id|EXPORT_SYMBOL
c_func
(paren
id|flush_dcache_page
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_MMU
DECL|variable|memory_start
id|EXPORT_SYMBOL
c_func
(paren
id|memory_start
)paren
suffix:semicolon
DECL|variable|memory_end
id|EXPORT_SYMBOL
c_func
(paren
id|memory_end
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|__debug_bug_trap
id|EXPORT_SYMBOL
c_func
(paren
id|__debug_bug_trap
)paren
suffix:semicolon
multiline_comment|/* Networking helper routines. */
DECL|variable|csum_partial_copy
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial_copy
)paren
suffix:semicolon
multiline_comment|/* The following are special because they&squot;re not called&n;   explicitly (the C compiler generates them).  Fortunately,&n;   their interface isn&squot;t gonna change any time soon now, so&n;   it&squot;s OK to leave it out of version control.  */
DECL|variable|memcpy
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy
)paren
suffix:semicolon
DECL|variable|memset
id|EXPORT_SYMBOL
c_func
(paren
id|memset
)paren
suffix:semicolon
DECL|variable|memcmp
id|EXPORT_SYMBOL
c_func
(paren
id|memcmp
)paren
suffix:semicolon
DECL|variable|memscan
id|EXPORT_SYMBOL
c_func
(paren
id|memscan
)paren
suffix:semicolon
DECL|variable|memmove
id|EXPORT_SYMBOL
c_func
(paren
id|memmove
)paren
suffix:semicolon
DECL|variable|strtok
id|EXPORT_SYMBOL
c_func
(paren
id|strtok
)paren
suffix:semicolon
DECL|variable|get_wchan
id|EXPORT_SYMBOL
c_func
(paren
id|get_wchan
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_FRV_OUTOFLINE_ATOMIC_OPS
DECL|variable|atomic_test_and_ANDNOT_mask
id|EXPORT_SYMBOL
c_func
(paren
id|atomic_test_and_ANDNOT_mask
)paren
suffix:semicolon
DECL|variable|atomic_test_and_OR_mask
id|EXPORT_SYMBOL
c_func
(paren
id|atomic_test_and_OR_mask
)paren
suffix:semicolon
DECL|variable|atomic_test_and_XOR_mask
id|EXPORT_SYMBOL
c_func
(paren
id|atomic_test_and_XOR_mask
)paren
suffix:semicolon
DECL|variable|atomic_add_return
id|EXPORT_SYMBOL
c_func
(paren
id|atomic_add_return
)paren
suffix:semicolon
DECL|variable|atomic_sub_return
id|EXPORT_SYMBOL
c_func
(paren
id|atomic_sub_return
)paren
suffix:semicolon
DECL|variable|__xchg_8
id|EXPORT_SYMBOL
c_func
(paren
id|__xchg_8
)paren
suffix:semicolon
DECL|variable|__xchg_16
id|EXPORT_SYMBOL
c_func
(paren
id|__xchg_16
)paren
suffix:semicolon
DECL|variable|__xchg_32
id|EXPORT_SYMBOL
c_func
(paren
id|__xchg_32
)paren
suffix:semicolon
DECL|variable|__cmpxchg_8
id|EXPORT_SYMBOL
c_func
(paren
id|__cmpxchg_8
)paren
suffix:semicolon
DECL|variable|__cmpxchg_16
id|EXPORT_SYMBOL
c_func
(paren
id|__cmpxchg_16
)paren
suffix:semicolon
DECL|variable|__cmpxchg_32
id|EXPORT_SYMBOL
c_func
(paren
id|__cmpxchg_32
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * libgcc functions - functions that are used internally by the&n; * compiler...  (prototypes are not correct though, but that&n; * doesn&squot;t really matter since they&squot;re not versioned).&n; */
r_extern
r_void
id|__gcc_bcmp
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__ashldi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__ashrdi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__cmpdi2
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__divdi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__lshrdi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__moddi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__muldi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__negdi2
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__ucmpdi2
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__udivdi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__udivmoddi4
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__umoddi3
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* gcc lib functions */
singleline_comment|//EXPORT_SYMBOL(__gcc_bcmp);
DECL|variable|__ashldi3
id|EXPORT_SYMBOL
c_func
(paren
id|__ashldi3
)paren
suffix:semicolon
DECL|variable|__ashrdi3
id|EXPORT_SYMBOL
c_func
(paren
id|__ashrdi3
)paren
suffix:semicolon
singleline_comment|//EXPORT_SYMBOL(__cmpdi2);
singleline_comment|//EXPORT_SYMBOL(__divdi3);
DECL|variable|__lshrdi3
id|EXPORT_SYMBOL
c_func
(paren
id|__lshrdi3
)paren
suffix:semicolon
singleline_comment|//EXPORT_SYMBOL(__moddi3);
DECL|variable|__muldi3
id|EXPORT_SYMBOL
c_func
(paren
id|__muldi3
)paren
suffix:semicolon
DECL|variable|__negdi2
id|EXPORT_SYMBOL
c_func
(paren
id|__negdi2
)paren
suffix:semicolon
singleline_comment|//EXPORT_SYMBOL(__ucmpdi2);
singleline_comment|//EXPORT_SYMBOL(__udivdi3);
singleline_comment|//EXPORT_SYMBOL(__udivmoddi4);
singleline_comment|//EXPORT_SYMBOL(__umoddi3);
eof
