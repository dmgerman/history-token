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
macro_line|#include &lt;asm/gpio.h&gt;
singleline_comment|//asmlinkage long long __ashrdi3 (long long, int);
singleline_comment|//asmlinkage long long __lshrdi3 (long long, int);
r_extern
r_char
id|h8300_debug_device
(braket
)braket
suffix:semicolon
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
multiline_comment|/* platform dependent support */
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
DECL|variable|ip_fast_csum
id|EXPORT_SYMBOL
c_func
(paren
id|ip_fast_csum
)paren
suffix:semicolon
DECL|variable|kernel_thread
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_thread
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
singleline_comment|//EXPORT_SYMBOL_NOVERS(__ashrdi3);
singleline_comment|//EXPORT_SYMBOL_NOVERS(__lshrdi3);
DECL|variable|memcpy
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memcpy
)paren
suffix:semicolon
DECL|variable|memset
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memset
)paren
suffix:semicolon
DECL|variable|memcmp
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memcmp
)paren
suffix:semicolon
DECL|variable|memscan
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memscan
)paren
suffix:semicolon
DECL|variable|memmove
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memmove
)paren
suffix:semicolon
DECL|variable|get_wchan
id|EXPORT_SYMBOL
c_func
(paren
id|get_wchan
)paren
suffix:semicolon
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
id|__divsi3
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
id|__modsi3
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
id|__mulsi3
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
id|__udivsi3
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
r_extern
r_void
id|__umodsi3
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* gcc lib functions */
DECL|variable|__gcc_bcmp
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__gcc_bcmp
)paren
suffix:semicolon
DECL|variable|__ashldi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__ashldi3
)paren
suffix:semicolon
DECL|variable|__ashrdi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__ashrdi3
)paren
suffix:semicolon
DECL|variable|__cmpdi2
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__cmpdi2
)paren
suffix:semicolon
DECL|variable|__divdi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__divdi3
)paren
suffix:semicolon
DECL|variable|__divsi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__divsi3
)paren
suffix:semicolon
DECL|variable|__lshrdi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__lshrdi3
)paren
suffix:semicolon
DECL|variable|__moddi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__moddi3
)paren
suffix:semicolon
DECL|variable|__modsi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__modsi3
)paren
suffix:semicolon
DECL|variable|__muldi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__muldi3
)paren
suffix:semicolon
DECL|variable|__mulsi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__mulsi3
)paren
suffix:semicolon
DECL|variable|__negdi2
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__negdi2
)paren
suffix:semicolon
DECL|variable|__ucmpdi2
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__ucmpdi2
)paren
suffix:semicolon
DECL|variable|__udivdi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__udivdi3
)paren
suffix:semicolon
DECL|variable|__udivmoddi4
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__udivmoddi4
)paren
suffix:semicolon
DECL|variable|__udivsi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__udivsi3
)paren
suffix:semicolon
DECL|variable|__umoddi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__umoddi3
)paren
suffix:semicolon
DECL|variable|__umodsi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__umodsi3
)paren
suffix:semicolon
macro_line|#ifdef MAGIC_ROM_PTR
DECL|variable|is_in_rom
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|is_in_rom
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|h8300_reserved_gpio
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|h8300_reserved_gpio
)paren
suffix:semicolon
DECL|variable|h8300_free_gpio
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|h8300_free_gpio
)paren
suffix:semicolon
DECL|variable|h8300_set_gpio_dir
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|h8300_set_gpio_dir
)paren
suffix:semicolon
eof
