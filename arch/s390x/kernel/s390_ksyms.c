multiline_comment|/*&n; *  arch/s390/kernel/s390_ksyms.c&n; *&n; *  S390 version&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/highuid.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#if CONFIG_IP_MULTICAST
macro_line|#include &lt;net/arp.h&gt;
macro_line|#endif
multiline_comment|/*&n; * memory management&n; */
DECL|variable|_oi_bitmap
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|_oi_bitmap
)paren
suffix:semicolon
DECL|variable|_ni_bitmap
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|_ni_bitmap
)paren
suffix:semicolon
DECL|variable|_zb_findmap
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|_zb_findmap
)paren
suffix:semicolon
DECL|variable|__copy_from_user_fixup
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__copy_from_user_fixup
)paren
suffix:semicolon
DECL|variable|__copy_to_user_fixup
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__copy_to_user_fixup
)paren
suffix:semicolon
multiline_comment|/*&n; * semaphore ops&n; */
DECL|variable|__up
id|EXPORT_SYMBOL
c_func
(paren
id|__up
)paren
suffix:semicolon
DECL|variable|__down
id|EXPORT_SYMBOL
c_func
(paren
id|__down
)paren
suffix:semicolon
DECL|variable|__down_interruptible
id|EXPORT_SYMBOL
c_func
(paren
id|__down_interruptible
)paren
suffix:semicolon
DECL|variable|__down_trylock
id|EXPORT_SYMBOL
c_func
(paren
id|__down_trylock
)paren
suffix:semicolon
multiline_comment|/*&n; * string functions&n; */
DECL|variable|memcmp
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memcmp
)paren
suffix:semicolon
DECL|variable|memset
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memset
)paren
suffix:semicolon
DECL|variable|memmove
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memmove
)paren
suffix:semicolon
DECL|variable|strlen
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strlen
)paren
suffix:semicolon
DECL|variable|strchr
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strchr
)paren
suffix:semicolon
DECL|variable|strcmp
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strcmp
)paren
suffix:semicolon
DECL|variable|strncat
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strncat
)paren
suffix:semicolon
DECL|variable|strncmp
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strncmp
)paren
suffix:semicolon
DECL|variable|strncpy
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strncpy
)paren
suffix:semicolon
DECL|variable|strnlen
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strnlen
)paren
suffix:semicolon
DECL|variable|strrchr
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strrchr
)paren
suffix:semicolon
DECL|variable|strstr
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strstr
)paren
suffix:semicolon
DECL|variable|strtok
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strtok
)paren
suffix:semicolon
DECL|variable|strpbrk
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strpbrk
)paren
suffix:semicolon
multiline_comment|/*&n; * binfmt_elf loader &n; */
r_extern
r_int
id|dump_fpu
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|s390_fp_regs
op_star
id|fpregs
)paren
suffix:semicolon
DECL|variable|dump_fpu
id|EXPORT_SYMBOL
c_func
(paren
id|dump_fpu
)paren
suffix:semicolon
DECL|variable|overflowuid
id|EXPORT_SYMBOL
c_func
(paren
id|overflowuid
)paren
suffix:semicolon
DECL|variable|overflowgid
id|EXPORT_SYMBOL
c_func
(paren
id|overflowgid
)paren
suffix:semicolon
multiline_comment|/*&n; * misc.&n; */
DECL|variable|machine_flags
id|EXPORT_SYMBOL
c_func
(paren
id|machine_flags
)paren
suffix:semicolon
DECL|variable|__udelay
id|EXPORT_SYMBOL
c_func
(paren
id|__udelay
)paren
suffix:semicolon
DECL|variable|kernel_thread
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_thread
)paren
suffix:semicolon
DECL|variable|console_mode
id|EXPORT_SYMBOL
c_func
(paren
id|console_mode
)paren
suffix:semicolon
DECL|variable|console_device
id|EXPORT_SYMBOL
c_func
(paren
id|console_device
)paren
suffix:semicolon
DECL|variable|do_call_softirq
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|do_call_softirq
)paren
suffix:semicolon
eof
