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
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/softirq.h&gt;
id|asmlinkage
r_int
r_int
id|__ashldi3
(paren
r_int
r_int
comma
r_int
)paren
suffix:semicolon
id|asmlinkage
r_int
r_int
id|__ashrdi3
(paren
r_int
r_int
comma
r_int
)paren
suffix:semicolon
id|asmlinkage
r_int
r_int
id|__lshrdi3
(paren
r_int
r_int
comma
r_int
)paren
suffix:semicolon
id|asmlinkage
r_int
r_int
id|__muldi3
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_char
id|m68k_debug_device
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
r_extern
r_int
id|dump_fpu
c_func
(paren
id|elf_fpregset_t
op_star
)paren
suffix:semicolon
multiline_comment|/* platform dependent support */
DECL|variable|m68k_machtype
id|EXPORT_SYMBOL
c_func
(paren
id|m68k_machtype
)paren
suffix:semicolon
DECL|variable|m68k_cputype
id|EXPORT_SYMBOL
c_func
(paren
id|m68k_cputype
)paren
suffix:semicolon
DECL|variable|m68k_is040or060
id|EXPORT_SYMBOL
c_func
(paren
id|m68k_is040or060
)paren
suffix:semicolon
DECL|variable|m68k_realnum_memory
id|EXPORT_SYMBOL
c_func
(paren
id|m68k_realnum_memory
)paren
suffix:semicolon
DECL|variable|m68k_memory
id|EXPORT_SYMBOL
c_func
(paren
id|m68k_memory
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SUN3
DECL|variable|cache_push
id|EXPORT_SYMBOL
c_func
(paren
id|cache_push
)paren
suffix:semicolon
DECL|variable|cache_clear
id|EXPORT_SYMBOL
c_func
(paren
id|cache_clear
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SINGLE_MEMORY_CHUNK
DECL|variable|mm_vtop
id|EXPORT_SYMBOL
c_func
(paren
id|mm_vtop
)paren
suffix:semicolon
DECL|variable|mm_ptov
id|EXPORT_SYMBOL
c_func
(paren
id|mm_ptov
)paren
suffix:semicolon
DECL|variable|mm_end_of_chunk
id|EXPORT_SYMBOL
c_func
(paren
id|mm_end_of_chunk
)paren
suffix:semicolon
macro_line|#else
DECL|variable|m68k_memoffset
id|EXPORT_SYMBOL
c_func
(paren
id|m68k_memoffset
)paren
suffix:semicolon
macro_line|#endif /* !CONFIG_SINGLE_MEMORY_CHUNK */
DECL|variable|mm_vtop_fallback
id|EXPORT_SYMBOL
c_func
(paren
id|mm_vtop_fallback
)paren
suffix:semicolon
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
DECL|variable|kernel_set_cachemode
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_set_cachemode
)paren
suffix:semicolon
macro_line|#endif /* !CONFIG_SUN3 */
DECL|variable|m68k_debug_device
id|EXPORT_SYMBOL
c_func
(paren
id|m68k_debug_device
)paren
suffix:semicolon
DECL|variable|mach_hwclk
id|EXPORT_SYMBOL
c_func
(paren
id|mach_hwclk
)paren
suffix:semicolon
DECL|variable|dump_fpu
id|EXPORT_SYMBOL
c_func
(paren
id|dump_fpu
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
macro_line|#ifdef CONFIG_VME
DECL|variable|vme_brdtype
id|EXPORT_SYMBOL
c_func
(paren
id|vme_brdtype
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* The following are special because they&squot;re not called&n;   explicitly (the C compiler generates them).  Fortunately,&n;   their interface isn&squot;t gonna change any time soon now, so&n;   it&squot;s OK to leave it out of version control.  */
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
DECL|variable|__lshrdi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__lshrdi3
)paren
suffix:semicolon
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
DECL|variable|__muldi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__muldi3
)paren
suffix:semicolon
DECL|variable|__down_failed
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__down_failed
)paren
suffix:semicolon
DECL|variable|__down_failed_interruptible
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__down_failed_interruptible
)paren
suffix:semicolon
DECL|variable|__down_failed_trylock
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__down_failed_trylock
)paren
suffix:semicolon
DECL|variable|__up_wakeup
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__up_wakeup
)paren
suffix:semicolon
DECL|variable|get_wchan
id|EXPORT_SYMBOL
c_func
(paren
id|get_wchan
)paren
suffix:semicolon
eof
