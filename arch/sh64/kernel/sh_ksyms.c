multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * arch/sh64/kernel/sh_ksyms.c&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
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
id|dump_fpu
c_func
(paren
r_struct
id|pt_regs
op_star
comma
id|elf_fpregset_t
op_star
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/* Not yet - there&squot;s no declaration of drive_info anywhere. */
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_HD) || defined(CONFIG_BLK_DEV_IDE_MODULE) || defined(CONFIG_BLK_DEV_HD_MODULE)
r_extern
r_struct
id|drive_info_struct
id|drive_info
suffix:semicolon
id|EXPORT_SYMBOL
c_func
(paren
id|drive_info
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/* platform dependent support */
DECL|variable|dump_thread
id|EXPORT_SYMBOL
c_func
(paren
id|dump_thread
)paren
suffix:semicolon
DECL|variable|dump_fpu
id|EXPORT_SYMBOL
c_func
(paren
id|dump_fpu
)paren
suffix:semicolon
DECL|variable|iounmap
id|EXPORT_SYMBOL
c_func
(paren
id|iounmap
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
DECL|variable|strpbrk
id|EXPORT_SYMBOL
c_func
(paren
id|strpbrk
)paren
suffix:semicolon
DECL|variable|strstr
id|EXPORT_SYMBOL
c_func
(paren
id|strstr
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_VT
DECL|variable|screen_info
id|EXPORT_SYMBOL
c_func
(paren
id|screen_info
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|__down
id|EXPORT_SYMBOL
c_func
(paren
id|__down
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
DECL|variable|__put_user_asm_l
id|EXPORT_SYMBOL
c_func
(paren
id|__put_user_asm_l
)paren
suffix:semicolon
DECL|variable|__get_user_asm_l
id|EXPORT_SYMBOL
c_func
(paren
id|__get_user_asm_l
)paren
suffix:semicolon
DECL|variable|memcmp
id|EXPORT_SYMBOL
c_func
(paren
id|memcmp
)paren
suffix:semicolon
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
DECL|variable|memscan
id|EXPORT_SYMBOL
c_func
(paren
id|memscan
)paren
suffix:semicolon
DECL|variable|strchr
id|EXPORT_SYMBOL
c_func
(paren
id|strchr
)paren
suffix:semicolon
DECL|variable|strlen
id|EXPORT_SYMBOL
c_func
(paren
id|strlen
)paren
suffix:semicolon
DECL|variable|flush_dcache_page
id|EXPORT_SYMBOL
c_func
(paren
id|flush_dcache_page
)paren
suffix:semicolon
multiline_comment|/* For ext3 */
DECL|variable|sh64_page_clear
id|EXPORT_SYMBOL
c_func
(paren
id|sh64_page_clear
)paren
suffix:semicolon
multiline_comment|/* Ugh.  These come in from libgcc.a at link time. */
r_extern
r_void
id|__sdivsi3
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
id|__udivsi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_char
id|__div_table
suffix:semicolon
DECL|variable|__sdivsi3
id|EXPORT_SYMBOL
c_func
(paren
id|__sdivsi3
)paren
suffix:semicolon
DECL|variable|__muldi3
id|EXPORT_SYMBOL
c_func
(paren
id|__muldi3
)paren
suffix:semicolon
DECL|variable|__udivsi3
id|EXPORT_SYMBOL
c_func
(paren
id|__udivsi3
)paren
suffix:semicolon
DECL|variable|__div_table
id|EXPORT_SYMBOL
c_func
(paren
id|__div_table
)paren
suffix:semicolon
eof
