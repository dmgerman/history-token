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
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/current.h&gt;
r_extern
r_void
op_star
id|trap_table
suffix:semicolon
DECL|variable|trap_table
id|EXPORT_SYMBOL
(paren
id|trap_table
)paren
suffix:semicolon
multiline_comment|/* platform dependent support */
r_extern
r_void
id|dump_thread
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
DECL|variable|dump_thread
id|EXPORT_SYMBOL
(paren
id|dump_thread
)paren
suffix:semicolon
DECL|variable|kernel_thread
id|EXPORT_SYMBOL
(paren
id|kernel_thread
)paren
suffix:semicolon
DECL|variable|enable_irq
id|EXPORT_SYMBOL
(paren
id|enable_irq
)paren
suffix:semicolon
DECL|variable|disable_irq
id|EXPORT_SYMBOL
(paren
id|disable_irq
)paren
suffix:semicolon
DECL|variable|disable_irq_nosync
id|EXPORT_SYMBOL
(paren
id|disable_irq_nosync
)paren
suffix:semicolon
DECL|variable|__bug
id|EXPORT_SYMBOL
(paren
id|__bug
)paren
suffix:semicolon
multiline_comment|/* Networking helper routines. */
DECL|variable|csum_partial_copy
id|EXPORT_SYMBOL
(paren
id|csum_partial_copy
)paren
suffix:semicolon
DECL|variable|csum_partial_copy_from_user
id|EXPORT_SYMBOL
(paren
id|csum_partial_copy_from_user
)paren
suffix:semicolon
DECL|variable|ip_compute_csum
id|EXPORT_SYMBOL
(paren
id|ip_compute_csum
)paren
suffix:semicolon
DECL|variable|ip_fast_csum
id|EXPORT_SYMBOL
(paren
id|ip_fast_csum
)paren
suffix:semicolon
multiline_comment|/* string / mem functions */
DECL|variable|strcpy
id|EXPORT_SYMBOL
(paren
id|strcpy
)paren
suffix:semicolon
DECL|variable|strncpy
id|EXPORT_SYMBOL
(paren
id|strncpy
)paren
suffix:semicolon
DECL|variable|strcat
id|EXPORT_SYMBOL
(paren
id|strcat
)paren
suffix:semicolon
DECL|variable|strncat
id|EXPORT_SYMBOL
(paren
id|strncat
)paren
suffix:semicolon
DECL|variable|strcmp
id|EXPORT_SYMBOL
(paren
id|strcmp
)paren
suffix:semicolon
DECL|variable|strncmp
id|EXPORT_SYMBOL
(paren
id|strncmp
)paren
suffix:semicolon
DECL|variable|strchr
id|EXPORT_SYMBOL
(paren
id|strchr
)paren
suffix:semicolon
DECL|variable|strlen
id|EXPORT_SYMBOL
(paren
id|strlen
)paren
suffix:semicolon
DECL|variable|strnlen
id|EXPORT_SYMBOL
(paren
id|strnlen
)paren
suffix:semicolon
DECL|variable|strpbrk
id|EXPORT_SYMBOL
(paren
id|strpbrk
)paren
suffix:semicolon
DECL|variable|strrchr
id|EXPORT_SYMBOL
(paren
id|strrchr
)paren
suffix:semicolon
DECL|variable|strstr
id|EXPORT_SYMBOL
(paren
id|strstr
)paren
suffix:semicolon
DECL|variable|memset
id|EXPORT_SYMBOL
(paren
id|memset
)paren
suffix:semicolon
DECL|variable|memcpy
id|EXPORT_SYMBOL
(paren
id|memcpy
)paren
suffix:semicolon
DECL|variable|memmove
id|EXPORT_SYMBOL
(paren
id|memmove
)paren
suffix:semicolon
DECL|variable|memcmp
id|EXPORT_SYMBOL
(paren
id|memcmp
)paren
suffix:semicolon
DECL|variable|memscan
id|EXPORT_SYMBOL
(paren
id|memscan
)paren
suffix:semicolon
multiline_comment|/* semaphores */
DECL|variable|__down
id|EXPORT_SYMBOL
(paren
id|__down
)paren
suffix:semicolon
DECL|variable|__down_interruptible
id|EXPORT_SYMBOL
(paren
id|__down_interruptible
)paren
suffix:semicolon
DECL|variable|__down_trylock
id|EXPORT_SYMBOL
(paren
id|__down_trylock
)paren
suffix:semicolon
DECL|variable|__up
id|EXPORT_SYMBOL
(paren
id|__up
)paren
suffix:semicolon
multiline_comment|/*&n; * libgcc functions - functions that are used internally by the&n; * compiler...  (prototypes are not correct though, but that&n; * doesn&squot;t really matter since they&squot;re not versioned).&n; */
r_extern
r_void
id|__ashldi3
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__ashrdi3
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__lshrdi3
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__muldi3
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__negdi2
(paren
r_void
)paren
suffix:semicolon
DECL|variable|__ashldi3
id|EXPORT_SYMBOL
(paren
id|__ashldi3
)paren
suffix:semicolon
DECL|variable|__ashrdi3
id|EXPORT_SYMBOL
(paren
id|__ashrdi3
)paren
suffix:semicolon
DECL|variable|__lshrdi3
id|EXPORT_SYMBOL
(paren
id|__lshrdi3
)paren
suffix:semicolon
DECL|variable|__muldi3
id|EXPORT_SYMBOL
(paren
id|__muldi3
)paren
suffix:semicolon
DECL|variable|__negdi2
id|EXPORT_SYMBOL
(paren
id|__negdi2
)paren
suffix:semicolon
eof
