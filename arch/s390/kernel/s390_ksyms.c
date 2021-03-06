multiline_comment|/*&n; *  arch/s390/kernel/s390_ksyms.c&n; *&n; *  S390 version&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/highuid.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioctl32.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;asm/cpcmd.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#ifdef CONFIG_IP_MULTICAST
macro_line|#include &lt;net/arp.h&gt;
macro_line|#endif
multiline_comment|/*&n; * memory management&n; */
DECL|variable|_oi_bitmap
id|EXPORT_SYMBOL
c_func
(paren
id|_oi_bitmap
)paren
suffix:semicolon
DECL|variable|_ni_bitmap
id|EXPORT_SYMBOL
c_func
(paren
id|_ni_bitmap
)paren
suffix:semicolon
DECL|variable|_zb_findmap
id|EXPORT_SYMBOL
c_func
(paren
id|_zb_findmap
)paren
suffix:semicolon
DECL|variable|_sb_findmap
id|EXPORT_SYMBOL
c_func
(paren
id|_sb_findmap
)paren
suffix:semicolon
DECL|variable|__copy_from_user_asm
id|EXPORT_SYMBOL
c_func
(paren
id|__copy_from_user_asm
)paren
suffix:semicolon
DECL|variable|__copy_to_user_asm
id|EXPORT_SYMBOL
c_func
(paren
id|__copy_to_user_asm
)paren
suffix:semicolon
DECL|variable|__copy_in_user_asm
id|EXPORT_SYMBOL
c_func
(paren
id|__copy_in_user_asm
)paren
suffix:semicolon
DECL|variable|__clear_user_asm
id|EXPORT_SYMBOL
c_func
(paren
id|__clear_user_asm
)paren
suffix:semicolon
DECL|variable|__strncpy_from_user_asm
id|EXPORT_SYMBOL
c_func
(paren
id|__strncpy_from_user_asm
)paren
suffix:semicolon
DECL|variable|__strnlen_user_asm
id|EXPORT_SYMBOL
c_func
(paren
id|__strnlen_user_asm
)paren
suffix:semicolon
DECL|variable|diag10
id|EXPORT_SYMBOL
c_func
(paren
id|diag10
)paren
suffix:semicolon
DECL|variable|default_storage_key
id|EXPORT_SYMBOL
c_func
(paren
id|default_storage_key
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
DECL|variable|empty_zero_page
id|EXPORT_SYMBOL
c_func
(paren
id|empty_zero_page
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
DECL|variable|csum_fold
id|EXPORT_SYMBOL
c_func
(paren
id|csum_fold
)paren
suffix:semicolon
DECL|variable|console_mode
id|EXPORT_SYMBOL
c_func
(paren
id|console_mode
)paren
suffix:semicolon
DECL|variable|console_devno
id|EXPORT_SYMBOL
c_func
(paren
id|console_devno
)paren
suffix:semicolon
DECL|variable|console_irq
id|EXPORT_SYMBOL
c_func
(paren
id|console_irq
)paren
suffix:semicolon
DECL|variable|sys_wait4
id|EXPORT_SYMBOL
c_func
(paren
id|sys_wait4
)paren
suffix:semicolon
eof
