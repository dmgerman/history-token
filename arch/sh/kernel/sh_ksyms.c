macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
macro_line|#include &lt;linux/mca.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
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
r_extern
r_struct
id|hw_interrupt_type
id|no_irq_type
suffix:semicolon
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
DECL|variable|disable_irq_nosync
id|EXPORT_SYMBOL
c_func
(paren
id|disable_irq_nosync
)paren
suffix:semicolon
DECL|variable|irq_desc
id|EXPORT_SYMBOL
c_func
(paren
id|irq_desc
)paren
suffix:semicolon
DECL|variable|no_irq_type
id|EXPORT_SYMBOL
c_func
(paren
id|no_irq_type
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
DECL|variable|strlen
id|EXPORT_SYMBOL
c_func
(paren
id|strlen
)paren
suffix:semicolon
DECL|variable|strnlen
id|EXPORT_SYMBOL
c_func
(paren
id|strnlen
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
DECL|variable|strncat
id|EXPORT_SYMBOL
c_func
(paren
id|strncat
)paren
suffix:semicolon
multiline_comment|/* PCI exports */
macro_line|#ifdef CONFIG_PCI
DECL|variable|pci_alloc_consistent
id|EXPORT_SYMBOL
c_func
(paren
id|pci_alloc_consistent
)paren
suffix:semicolon
DECL|variable|pci_free_consistent
id|EXPORT_SYMBOL
c_func
(paren
id|pci_free_consistent
)paren
suffix:semicolon
DECL|variable|pcibios_penalize_isa_irq
id|EXPORT_SYMBOL
c_func
(paren
id|pcibios_penalize_isa_irq
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* mem exports */
DECL|variable|memchr
id|EXPORT_SYMBOL
c_func
(paren
id|memchr
)paren
suffix:semicolon
DECL|variable|memcpy
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy
)paren
suffix:semicolon
DECL|variable|memcpy_fromio
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy_fromio
)paren
suffix:semicolon
DECL|variable|memcpy_toio
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy_toio
)paren
suffix:semicolon
DECL|variable|memset
id|EXPORT_SYMBOL
c_func
(paren
id|memset
)paren
suffix:semicolon
DECL|variable|memset_io
id|EXPORT_SYMBOL
c_func
(paren
id|memset_io
)paren
suffix:semicolon
DECL|variable|memmove
id|EXPORT_SYMBOL
c_func
(paren
id|memmove
)paren
suffix:semicolon
DECL|variable|memcmp
id|EXPORT_SYMBOL
c_func
(paren
id|memcmp
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
DECL|variable|boot_cpu_data
id|EXPORT_SYMBOL
c_func
(paren
id|boot_cpu_data
)paren
suffix:semicolon
DECL|variable|get_vm_area
id|EXPORT_SYMBOL
c_func
(paren
id|get_vm_area
)paren
suffix:semicolon
multiline_comment|/* semaphore exports */
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
DECL|variable|__udelay
id|EXPORT_SYMBOL
c_func
(paren
id|__udelay
)paren
suffix:semicolon
DECL|variable|__const_udelay
id|EXPORT_SYMBOL
c_func
(paren
id|__const_udelay
)paren
suffix:semicolon
DECL|macro|DECLARE_EXPORT
mdefine_line|#define DECLARE_EXPORT(name) extern void name(void);EXPORT_SYMBOL_NOVERS(name)
multiline_comment|/* These symbols are generated by the compiler itself */
DECL|variable|__udivsi3
id|DECLARE_EXPORT
c_func
(paren
id|__udivsi3
)paren
suffix:semicolon
DECL|variable|__sdivsi3
id|DECLARE_EXPORT
c_func
(paren
id|__sdivsi3
)paren
suffix:semicolon
DECL|variable|__ashrdi3
id|DECLARE_EXPORT
c_func
(paren
id|__ashrdi3
)paren
suffix:semicolon
DECL|variable|__ashldi3
id|DECLARE_EXPORT
c_func
(paren
id|__ashldi3
)paren
suffix:semicolon
DECL|variable|__lshrdi3
id|DECLARE_EXPORT
c_func
(paren
id|__lshrdi3
)paren
suffix:semicolon
DECL|variable|__movstr
id|DECLARE_EXPORT
c_func
(paren
id|__movstr
)paren
suffix:semicolon
macro_line|#ifdef __SH4__
DECL|variable|__movstr_i4_even
id|DECLARE_EXPORT
c_func
(paren
id|__movstr_i4_even
)paren
suffix:semicolon
DECL|variable|__movstr_i4_odd
id|DECLARE_EXPORT
c_func
(paren
id|__movstr_i4_odd
)paren
suffix:semicolon
multiline_comment|/* needed by some modules */
DECL|variable|flush_cache_all
id|EXPORT_SYMBOL
c_func
(paren
id|flush_cache_all
)paren
suffix:semicolon
DECL|variable|flush_cache_range
id|EXPORT_SYMBOL
c_func
(paren
id|flush_cache_range
)paren
suffix:semicolon
DECL|variable|flush_dcache_page
id|EXPORT_SYMBOL
c_func
(paren
id|flush_dcache_page
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|flush_tlb_page
id|EXPORT_SYMBOL
c_func
(paren
id|flush_tlb_page
)paren
suffix:semicolon
eof
