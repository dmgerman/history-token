multiline_comment|/*&n; * Export MIPS-specific functions needed for loadable modules.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1997, 1998, 2000, 2001 by Ralf Baechle&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/softirq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_FD
macro_line|#include &lt;asm/floppy.h&gt;
macro_line|#endif
r_extern
r_void
op_star
id|__bzero
c_func
(paren
r_void
op_star
id|__s
comma
r_int
id|__count
)paren
suffix:semicolon
r_extern
r_int
id|__strncpy_from_user_nocheck_asm
c_func
(paren
r_char
op_star
id|__to
comma
r_const
r_char
op_star
id|__from
comma
r_int
id|__len
)paren
suffix:semicolon
r_extern
r_int
id|__strncpy_from_user_asm
c_func
(paren
r_char
op_star
id|__to
comma
r_const
r_char
op_star
id|__from
comma
r_int
id|__len
)paren
suffix:semicolon
r_extern
r_int
id|__strlen_user_nocheck_asm
c_func
(paren
r_const
r_char
op_star
id|s
)paren
suffix:semicolon
r_extern
r_int
id|__strlen_user_asm
c_func
(paren
r_const
r_char
op_star
id|s
)paren
suffix:semicolon
r_extern
r_int
id|__strnlen_user_nocheck_asm
c_func
(paren
r_const
r_char
op_star
id|s
)paren
suffix:semicolon
r_extern
r_int
id|__strnlen_user_asm
c_func
(paren
r_const
r_char
op_star
id|s
)paren
suffix:semicolon
DECL|variable|mips_machtype
id|EXPORT_SYMBOL
c_func
(paren
id|mips_machtype
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_EISA
DECL|variable|EISA_bus
id|EXPORT_SYMBOL
c_func
(paren
id|EISA_bus
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * String functions&n; */
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
DECL|variable|memcpy
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memcpy
)paren
suffix:semicolon
DECL|variable|memmove
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memmove
)paren
suffix:semicolon
DECL|variable|strcat
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strcat
)paren
suffix:semicolon
DECL|variable|strchr
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strchr
)paren
suffix:semicolon
DECL|variable|strlen
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strlen
)paren
suffix:semicolon
DECL|variable|strpbrk
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strpbrk
)paren
suffix:semicolon
DECL|variable|strncat
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strncat
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
DECL|variable|_clear_page
id|EXPORT_SYMBOL
c_func
(paren
id|_clear_page
)paren
suffix:semicolon
DECL|variable|kernel_thread
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_thread
)paren
suffix:semicolon
multiline_comment|/*&n; * Userspace access stuff.&n; */
DECL|variable|__copy_user
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__copy_user
)paren
suffix:semicolon
DECL|variable|__bzero
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__bzero
)paren
suffix:semicolon
DECL|variable|__strncpy_from_user_nocheck_asm
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__strncpy_from_user_nocheck_asm
)paren
suffix:semicolon
DECL|variable|__strncpy_from_user_asm
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__strncpy_from_user_asm
)paren
suffix:semicolon
DECL|variable|__strlen_user_nocheck_asm
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__strlen_user_nocheck_asm
)paren
suffix:semicolon
DECL|variable|__strlen_user_asm
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__strlen_user_asm
)paren
suffix:semicolon
DECL|variable|__strnlen_user_nocheck_asm
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__strnlen_user_nocheck_asm
)paren
suffix:semicolon
DECL|variable|__strnlen_user_asm
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__strnlen_user_asm
)paren
suffix:semicolon
DECL|variable|invalid_pte_table
id|EXPORT_SYMBOL
c_func
(paren
id|invalid_pte_table
)paren
suffix:semicolon
multiline_comment|/*&n; * Semaphore stuff&n; */
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
DECL|variable|__up
id|EXPORT_SYMBOL
c_func
(paren
id|__up
)paren
suffix:semicolon
multiline_comment|/*&n; * Kernel hacking ...&n; */
macro_line|#include &lt;asm/branch.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#ifdef CONFIG_VT
DECL|variable|screen_info
id|EXPORT_SYMBOL
c_func
(paren
id|screen_info
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_IDE_MODULE)
DECL|variable|ide_ops
id|EXPORT_SYMBOL
c_func
(paren
id|ide_ops
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|get_wchan
id|EXPORT_SYMBOL
c_func
(paren
id|get_wchan
)paren
suffix:semicolon
eof
