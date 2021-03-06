multiline_comment|/*&n; * Architecture-specific kernel symbols&n; *&n; * Don&squot;t put any exports here unless it&squot;s defined in an assembler file.&n; * All other exports should be put directly after the definition.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
DECL|variable|memset
id|EXPORT_SYMBOL
c_func
(paren
id|memset
)paren
suffix:semicolon
DECL|variable|memchr
id|EXPORT_SYMBOL
c_func
(paren
id|memchr
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
DECL|variable|memmove
id|EXPORT_SYMBOL
c_func
(paren
id|memmove
)paren
suffix:semicolon
DECL|variable|memscan
id|EXPORT_SYMBOL
c_func
(paren
id|memscan
)paren
suffix:semicolon
DECL|variable|strcat
id|EXPORT_SYMBOL
c_func
(paren
id|strcat
)paren
suffix:semicolon
DECL|variable|strchr
id|EXPORT_SYMBOL
c_func
(paren
id|strchr
)paren
suffix:semicolon
DECL|variable|strcmp
id|EXPORT_SYMBOL
c_func
(paren
id|strcmp
)paren
suffix:semicolon
DECL|variable|strcpy
id|EXPORT_SYMBOL
c_func
(paren
id|strcpy
)paren
suffix:semicolon
DECL|variable|strlen
id|EXPORT_SYMBOL
c_func
(paren
id|strlen
)paren
suffix:semicolon
DECL|variable|strncat
id|EXPORT_SYMBOL
c_func
(paren
id|strncat
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
DECL|variable|strpbrk
id|EXPORT_SYMBOL
c_func
(paren
id|strpbrk
)paren
suffix:semicolon
macro_line|#include &lt;asm/checksum.h&gt;
DECL|variable|ip_fast_csum
id|EXPORT_SYMBOL
c_func
(paren
id|ip_fast_csum
)paren
suffix:semicolon
multiline_comment|/* hand-coded assembly */
macro_line|#include &lt;asm/semaphore.h&gt;
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
macro_line|#include &lt;asm/page.h&gt;
DECL|variable|clear_page
id|EXPORT_SYMBOL
c_func
(paren
id|clear_page
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_VIRTUAL_MEM_MAP
macro_line|#include &lt;linux/bootmem.h&gt;
DECL|variable|max_low_pfn
id|EXPORT_SYMBOL
c_func
(paren
id|max_low_pfn
)paren
suffix:semicolon
multiline_comment|/* defined by bootmem.c, but not exported by generic code */
macro_line|#endif
macro_line|#include &lt;asm/processor.h&gt;
DECL|variable|per_cpu__cpu_info
id|EXPORT_SYMBOL
c_func
(paren
id|per_cpu__cpu_info
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|variable|per_cpu__local_per_cpu_offset
id|EXPORT_SYMBOL
c_func
(paren
id|per_cpu__local_per_cpu_offset
)paren
suffix:semicolon
macro_line|#endif
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|variable|__copy_user
id|EXPORT_SYMBOL
c_func
(paren
id|__copy_user
)paren
suffix:semicolon
DECL|variable|__do_clear_user
id|EXPORT_SYMBOL
c_func
(paren
id|__do_clear_user
)paren
suffix:semicolon
DECL|variable|__strlen_user
id|EXPORT_SYMBOL
c_func
(paren
id|__strlen_user
)paren
suffix:semicolon
DECL|variable|__strncpy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|__strncpy_from_user
)paren
suffix:semicolon
DECL|variable|__strnlen_user
id|EXPORT_SYMBOL
c_func
(paren
id|__strnlen_user
)paren
suffix:semicolon
macro_line|#include &lt;asm/unistd.h&gt;
DECL|variable|__ia64_syscall
id|EXPORT_SYMBOL
c_func
(paren
id|__ia64_syscall
)paren
suffix:semicolon
multiline_comment|/* from arch/ia64/lib */
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
id|__udivsi3
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
id|__umodsi3
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
id|__udivdi3
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
id|__umoddi3
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|__divsi3
id|EXPORT_SYMBOL
c_func
(paren
id|__divsi3
)paren
suffix:semicolon
DECL|variable|__udivsi3
id|EXPORT_SYMBOL
c_func
(paren
id|__udivsi3
)paren
suffix:semicolon
DECL|variable|__modsi3
id|EXPORT_SYMBOL
c_func
(paren
id|__modsi3
)paren
suffix:semicolon
DECL|variable|__umodsi3
id|EXPORT_SYMBOL
c_func
(paren
id|__umodsi3
)paren
suffix:semicolon
DECL|variable|__divdi3
id|EXPORT_SYMBOL
c_func
(paren
id|__divdi3
)paren
suffix:semicolon
DECL|variable|__udivdi3
id|EXPORT_SYMBOL
c_func
(paren
id|__udivdi3
)paren
suffix:semicolon
DECL|variable|__moddi3
id|EXPORT_SYMBOL
c_func
(paren
id|__moddi3
)paren
suffix:semicolon
DECL|variable|__umoddi3
id|EXPORT_SYMBOL
c_func
(paren
id|__umoddi3
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_MD_RAID5) || defined(CONFIG_MD_RAID5_MODULE)
r_extern
r_void
id|xor_ia64_2
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|xor_ia64_3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|xor_ia64_4
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|xor_ia64_5
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|xor_ia64_2
id|EXPORT_SYMBOL
c_func
(paren
id|xor_ia64_2
)paren
suffix:semicolon
DECL|variable|xor_ia64_3
id|EXPORT_SYMBOL
c_func
(paren
id|xor_ia64_3
)paren
suffix:semicolon
DECL|variable|xor_ia64_4
id|EXPORT_SYMBOL
c_func
(paren
id|xor_ia64_4
)paren
suffix:semicolon
DECL|variable|xor_ia64_5
id|EXPORT_SYMBOL
c_func
(paren
id|xor_ia64_5
)paren
suffix:semicolon
macro_line|#endif
macro_line|#include &lt;asm/pal.h&gt;
DECL|variable|ia64_pal_call_phys_stacked
id|EXPORT_SYMBOL
c_func
(paren
id|ia64_pal_call_phys_stacked
)paren
suffix:semicolon
DECL|variable|ia64_pal_call_phys_static
id|EXPORT_SYMBOL
c_func
(paren
id|ia64_pal_call_phys_static
)paren
suffix:semicolon
DECL|variable|ia64_pal_call_stacked
id|EXPORT_SYMBOL
c_func
(paren
id|ia64_pal_call_stacked
)paren
suffix:semicolon
DECL|variable|ia64_pal_call_static
id|EXPORT_SYMBOL
c_func
(paren
id|ia64_pal_call_static
)paren
suffix:semicolon
DECL|variable|ia64_load_scratch_fpregs
id|EXPORT_SYMBOL
c_func
(paren
id|ia64_load_scratch_fpregs
)paren
suffix:semicolon
DECL|variable|ia64_save_scratch_fpregs
id|EXPORT_SYMBOL
c_func
(paren
id|ia64_save_scratch_fpregs
)paren
suffix:semicolon
macro_line|#include &lt;asm/unwind.h&gt;
DECL|variable|unw_init_running
id|EXPORT_SYMBOL
c_func
(paren
id|unw_init_running
)paren
suffix:semicolon
macro_line|#ifdef ASM_SUPPORTED
macro_line|# ifdef CONFIG_SMP
macro_line|#  if __GNUC__ &lt; 3 || (__GNUC__ == 3 &amp;&amp; __GNUC_MINOR__ &lt; 3)
multiline_comment|/*&n; * This is not a normal routine and we don&squot;t want a function descriptor for it, so we use&n; * a fake declaration here.&n; */
r_extern
r_char
id|ia64_spinlock_contention_pre3_4
suffix:semicolon
DECL|variable|ia64_spinlock_contention_pre3_4
id|EXPORT_SYMBOL
c_func
(paren
id|ia64_spinlock_contention_pre3_4
)paren
suffix:semicolon
macro_line|#  else
multiline_comment|/*&n; * This is not a normal routine and we don&squot;t want a function descriptor for it, so we use&n; * a fake declaration here.&n; */
r_extern
r_char
id|ia64_spinlock_contention
suffix:semicolon
DECL|variable|ia64_spinlock_contention
id|EXPORT_SYMBOL
c_func
(paren
id|ia64_spinlock_contention
)paren
suffix:semicolon
macro_line|#  endif
macro_line|# endif
macro_line|#endif
r_extern
r_char
id|ia64_ivt
(braket
)braket
suffix:semicolon
DECL|variable|ia64_ivt
id|EXPORT_SYMBOL
c_func
(paren
id|ia64_ivt
)paren
suffix:semicolon
eof
