multiline_comment|/*&n; * Architecture-specific kernel symbols&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
DECL|variable|memset
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memset
)paren
suffix:semicolon
multiline_comment|/* gcc generates direct calls to memset()... */
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
id|EXPORT_SYMBOL_NOVERS
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
macro_line|#include &lt;linux/irq.h&gt;
DECL|variable|isa_irq_to_vector_map
id|EXPORT_SYMBOL
c_func
(paren
id|isa_irq_to_vector_map
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
DECL|variable|disable_irq_nosync
id|EXPORT_SYMBOL
c_func
(paren
id|disable_irq_nosync
)paren
suffix:semicolon
macro_line|#include &lt;linux/interrupt.h&gt;
DECL|variable|probe_irq_mask
id|EXPORT_SYMBOL
c_func
(paren
id|probe_irq_mask
)paren
suffix:semicolon
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
multiline_comment|/* not coded yet?? EXPORT_SYMBOL(csum_ipv6_magic); */
DECL|variable|csum_partial_copy_nocheck
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial_copy_nocheck
)paren
suffix:semicolon
DECL|variable|csum_tcpudp_magic
id|EXPORT_SYMBOL
c_func
(paren
id|csum_tcpudp_magic
)paren
suffix:semicolon
DECL|variable|ip_compute_csum
id|EXPORT_SYMBOL
c_func
(paren
id|ip_compute_csum
)paren
suffix:semicolon
DECL|variable|ip_fast_csum
id|EXPORT_SYMBOL
c_func
(paren
id|ip_fast_csum
)paren
suffix:semicolon
macro_line|#include &lt;asm/io.h&gt;
DECL|variable|__ia64_memcpy_fromio
id|EXPORT_SYMBOL
c_func
(paren
id|__ia64_memcpy_fromio
)paren
suffix:semicolon
DECL|variable|__ia64_memcpy_toio
id|EXPORT_SYMBOL
c_func
(paren
id|__ia64_memcpy_toio
)paren
suffix:semicolon
DECL|variable|__ia64_memset_c_io
id|EXPORT_SYMBOL
c_func
(paren
id|__ia64_memset_c_io
)paren
suffix:semicolon
macro_line|#include &lt;asm/semaphore.h&gt;
DECL|variable|__down
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__down
)paren
suffix:semicolon
DECL|variable|__down_interruptible
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__down_interruptible
)paren
suffix:semicolon
DECL|variable|__down_trylock
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__down_trylock
)paren
suffix:semicolon
DECL|variable|__up
id|EXPORT_SYMBOL_NOVERS
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
macro_line|#include &lt;asm/processor.h&gt;
macro_line|# ifndef CONFIG_NUMA
DECL|variable|cpu_info__per_cpu
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_info__per_cpu
)paren
suffix:semicolon
macro_line|# endif
DECL|variable|kernel_thread
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_thread
)paren
suffix:semicolon
macro_line|#include &lt;asm/system.h&gt;
macro_line|#ifdef CONFIG_IA64_DEBUG_IRQ
DECL|variable|last_cli_ip
id|EXPORT_SYMBOL
c_func
(paren
id|last_cli_ip
)paren
suffix:semicolon
macro_line|#endif
macro_line|#include &lt;asm/tlbflush.h&gt;
DECL|variable|flush_tlb_range
id|EXPORT_SYMBOL
c_func
(paren
id|flush_tlb_range
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|variable|smp_flush_tlb_all
id|EXPORT_SYMBOL
c_func
(paren
id|smp_flush_tlb_all
)paren
suffix:semicolon
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|variable|synchronize_irq
id|EXPORT_SYMBOL
c_func
(paren
id|synchronize_irq
)paren
suffix:semicolon
macro_line|#include &lt;asm/smp.h&gt;
DECL|variable|smp_call_function
id|EXPORT_SYMBOL
c_func
(paren
id|smp_call_function
)paren
suffix:semicolon
DECL|variable|smp_call_function_single
id|EXPORT_SYMBOL
c_func
(paren
id|smp_call_function_single
)paren
suffix:semicolon
DECL|variable|cpu_online_map
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_online_map
)paren
suffix:semicolon
DECL|variable|ia64_cpu_to_sapicid
id|EXPORT_SYMBOL
c_func
(paren
id|ia64_cpu_to_sapicid
)paren
suffix:semicolon
macro_line|#else /* !CONFIG_SMP */
DECL|variable|__flush_tlb_all
id|EXPORT_SYMBOL
c_func
(paren
id|__flush_tlb_all
)paren
suffix:semicolon
macro_line|#endif /* !CONFIG_SMP */
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
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__divsi3
)paren
suffix:semicolon
DECL|variable|__udivsi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__udivsi3
)paren
suffix:semicolon
DECL|variable|__modsi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__modsi3
)paren
suffix:semicolon
DECL|variable|__umodsi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__umodsi3
)paren
suffix:semicolon
DECL|variable|__divdi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__divdi3
)paren
suffix:semicolon
DECL|variable|__udivdi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__udivdi3
)paren
suffix:semicolon
DECL|variable|__moddi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__moddi3
)paren
suffix:semicolon
DECL|variable|__umoddi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__umoddi3
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ia64_iobase
suffix:semicolon
DECL|variable|ia64_iobase
id|EXPORT_SYMBOL
c_func
(paren
id|ia64_iobase
)paren
suffix:semicolon
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
r_extern
r_struct
id|efi
id|efi
suffix:semicolon
DECL|variable|efi
id|EXPORT_SYMBOL
c_func
(paren
id|efi
)paren
suffix:semicolon
macro_line|#include &lt;linux/proc_fs.h&gt;
r_extern
r_struct
id|proc_dir_entry
op_star
id|efi_dir
suffix:semicolon
DECL|variable|efi_dir
id|EXPORT_SYMBOL
c_func
(paren
id|efi_dir
)paren
suffix:semicolon
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#ifdef CONFIG_IA64_GENERIC
DECL|variable|ia64_mv
id|EXPORT_SYMBOL
c_func
(paren
id|ia64_mv
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|machvec_noop
id|EXPORT_SYMBOL
c_func
(paren
id|machvec_noop
)paren
suffix:semicolon
eof
