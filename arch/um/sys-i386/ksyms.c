macro_line|#include &quot;linux/module.h&quot;
macro_line|#include &quot;linux/in6.h&quot;
macro_line|#include &quot;linux/rwsem.h&quot;
macro_line|#include &quot;asm/byteorder.h&quot;
macro_line|#include &quot;asm/semaphore.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;asm/checksum.h&quot;
macro_line|#include &quot;asm/errno.h&quot;
DECL|variable|__down_failed
id|EXPORT_SYMBOL
c_func
(paren
id|__down_failed
)paren
suffix:semicolon
DECL|variable|__down_failed_interruptible
id|EXPORT_SYMBOL
c_func
(paren
id|__down_failed_interruptible
)paren
suffix:semicolon
DECL|variable|__down_failed_trylock
id|EXPORT_SYMBOL
c_func
(paren
id|__down_failed_trylock
)paren
suffix:semicolon
DECL|variable|__up_wakeup
id|EXPORT_SYMBOL
c_func
(paren
id|__up_wakeup
)paren
suffix:semicolon
multiline_comment|/* Networking helper routines. */
DECL|variable|csum_partial_copy_from
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial_copy_from
)paren
suffix:semicolon
DECL|variable|csum_partial_copy_to
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial_copy_to
)paren
suffix:semicolon
eof
