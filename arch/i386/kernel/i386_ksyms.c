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
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/apm_bios.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mmx.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/nmi.h&gt;
macro_line|#include &lt;asm/ist.h&gt;
macro_line|#include &lt;asm/kdebug.h&gt;
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
id|spinlock_t
id|rtc_lock
suffix:semicolon
multiline_comment|/* This is definitely a GPL-only symbol */
DECL|variable|cpu_gdt_table
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|cpu_gdt_table
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_APM_MODULE)
r_extern
r_void
id|machine_real_restart
c_func
(paren
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|variable|machine_real_restart
id|EXPORT_SYMBOL
c_func
(paren
id|machine_real_restart
)paren
suffix:semicolon
r_extern
r_void
id|default_idle
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|default_idle
id|EXPORT_SYMBOL
c_func
(paren
id|default_idle
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__write_lock_failed
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__read_lock_failed
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_HD) || defined(CONFIG_BLK_DEV_IDE_MODULE) || defined(CONFIG_BLK_DEV_HD_MODULE)
r_extern
r_struct
id|drive_info_struct
id|drive_info
suffix:semicolon
DECL|variable|drive_info
id|EXPORT_SYMBOL
c_func
(paren
id|drive_info
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
r_int
id|cpu_khz
suffix:semicolon
r_extern
r_int
r_int
id|get_cmos_time
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* platform dependent support */
DECL|variable|boot_cpu_data
id|EXPORT_SYMBOL
c_func
(paren
id|boot_cpu_data
)paren
suffix:semicolon
DECL|variable|MCA_bus
id|EXPORT_SYMBOL
c_func
(paren
id|MCA_bus
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DISCONTIGMEM
DECL|variable|node_data
id|EXPORT_SYMBOL
c_func
(paren
id|node_data
)paren
suffix:semicolon
DECL|variable|physnode_map
id|EXPORT_SYMBOL
c_func
(paren
id|physnode_map
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_X86_NUMAQ
DECL|variable|xquad_portio
id|EXPORT_SYMBOL
c_func
(paren
id|xquad_portio
)paren
suffix:semicolon
macro_line|#endif
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
DECL|variable|dump_extended_fpu
id|EXPORT_SYMBOL
c_func
(paren
id|dump_extended_fpu
)paren
suffix:semicolon
DECL|variable|kernel_fpu_begin
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|kernel_fpu_begin
)paren
suffix:semicolon
DECL|variable|__ioremap
id|EXPORT_SYMBOL
c_func
(paren
id|__ioremap
)paren
suffix:semicolon
DECL|variable|ioremap_nocache
id|EXPORT_SYMBOL
c_func
(paren
id|ioremap_nocache
)paren
suffix:semicolon
DECL|variable|iounmap
id|EXPORT_SYMBOL
c_func
(paren
id|iounmap
)paren
suffix:semicolon
DECL|variable|probe_irq_mask
id|EXPORT_SYMBOL
c_func
(paren
id|probe_irq_mask
)paren
suffix:semicolon
DECL|variable|kernel_thread
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_thread
)paren
suffix:semicolon
DECL|variable|pm_idle
id|EXPORT_SYMBOL
c_func
(paren
id|pm_idle
)paren
suffix:semicolon
DECL|variable|pm_power_off
id|EXPORT_SYMBOL
c_func
(paren
id|pm_power_off
)paren
suffix:semicolon
DECL|variable|get_cmos_time
id|EXPORT_SYMBOL
c_func
(paren
id|get_cmos_time
)paren
suffix:semicolon
DECL|variable|cpu_khz
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_khz
)paren
suffix:semicolon
DECL|variable|apm_info
id|EXPORT_SYMBOL
c_func
(paren
id|apm_info
)paren
suffix:semicolon
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
DECL|variable|csum_partial_copy_generic
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial_copy_generic
)paren
suffix:semicolon
multiline_comment|/* Delay loops */
DECL|variable|__ndelay
id|EXPORT_SYMBOL
c_func
(paren
id|__ndelay
)paren
suffix:semicolon
DECL|variable|__udelay
id|EXPORT_SYMBOL
c_func
(paren
id|__udelay
)paren
suffix:semicolon
DECL|variable|__delay
id|EXPORT_SYMBOL
c_func
(paren
id|__delay
)paren
suffix:semicolon
DECL|variable|__const_udelay
id|EXPORT_SYMBOL
c_func
(paren
id|__const_udelay
)paren
suffix:semicolon
DECL|variable|__get_user_1
id|EXPORT_SYMBOL
c_func
(paren
id|__get_user_1
)paren
suffix:semicolon
DECL|variable|__get_user_2
id|EXPORT_SYMBOL
c_func
(paren
id|__get_user_2
)paren
suffix:semicolon
DECL|variable|__get_user_4
id|EXPORT_SYMBOL
c_func
(paren
id|__get_user_4
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
DECL|variable|strncpy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|strncpy_from_user
)paren
suffix:semicolon
DECL|variable|__strncpy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|__strncpy_from_user
)paren
suffix:semicolon
DECL|variable|clear_user
id|EXPORT_SYMBOL
c_func
(paren
id|clear_user
)paren
suffix:semicolon
DECL|variable|__clear_user
id|EXPORT_SYMBOL
c_func
(paren
id|__clear_user
)paren
suffix:semicolon
DECL|variable|__copy_from_user_ll
id|EXPORT_SYMBOL
c_func
(paren
id|__copy_from_user_ll
)paren
suffix:semicolon
DECL|variable|__copy_to_user_ll
id|EXPORT_SYMBOL
c_func
(paren
id|__copy_to_user_ll
)paren
suffix:semicolon
DECL|variable|strnlen_user
id|EXPORT_SYMBOL
c_func
(paren
id|strnlen_user
)paren
suffix:semicolon
DECL|variable|dma_alloc_coherent
id|EXPORT_SYMBOL
c_func
(paren
id|dma_alloc_coherent
)paren
suffix:semicolon
DECL|variable|dma_free_coherent
id|EXPORT_SYMBOL
c_func
(paren
id|dma_free_coherent
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
DECL|variable|pcibios_penalize_isa_irq
id|EXPORT_SYMBOL
c_func
(paren
id|pcibios_penalize_isa_irq
)paren
suffix:semicolon
DECL|variable|pci_mem_start
id|EXPORT_SYMBOL
c_func
(paren
id|pci_mem_start
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PCI_BIOS
DECL|variable|pcibios_set_irq_routing
id|EXPORT_SYMBOL
c_func
(paren
id|pcibios_set_irq_routing
)paren
suffix:semicolon
DECL|variable|pcibios_get_irq_routing_table
id|EXPORT_SYMBOL
c_func
(paren
id|pcibios_get_irq_routing_table
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_X86_USE_3DNOW
DECL|variable|_mmx_memcpy
id|EXPORT_SYMBOL
c_func
(paren
id|_mmx_memcpy
)paren
suffix:semicolon
DECL|variable|mmx_clear_page
id|EXPORT_SYMBOL
c_func
(paren
id|mmx_clear_page
)paren
suffix:semicolon
DECL|variable|mmx_copy_page
id|EXPORT_SYMBOL
c_func
(paren
id|mmx_copy_page
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_X86_HT
DECL|variable|smp_num_siblings
id|EXPORT_SYMBOL
c_func
(paren
id|smp_num_siblings
)paren
suffix:semicolon
DECL|variable|cpu_sibling_map
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_sibling_map
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
DECL|variable|cpu_data
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_data
)paren
suffix:semicolon
DECL|variable|cpu_online_map
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_online_map
)paren
suffix:semicolon
DECL|variable|cpu_callout_map
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_callout_map
)paren
suffix:semicolon
DECL|variable|__write_lock_failed
id|EXPORT_SYMBOL
c_func
(paren
id|__write_lock_failed
)paren
suffix:semicolon
DECL|variable|__read_lock_failed
id|EXPORT_SYMBOL
c_func
(paren
id|__read_lock_failed
)paren
suffix:semicolon
multiline_comment|/* Global SMP stuff */
DECL|variable|smp_call_function
id|EXPORT_SYMBOL
c_func
(paren
id|smp_call_function
)paren
suffix:semicolon
multiline_comment|/* TLB flushing */
DECL|variable|flush_tlb_page
id|EXPORT_SYMBOL
c_func
(paren
id|flush_tlb_page
)paren
suffix:semicolon
DECL|variable|flush_tlb_all
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|flush_tlb_all
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_X86_IO_APIC
DECL|variable|IO_APIC_get_PCI_irq_vector
id|EXPORT_SYMBOL
c_func
(paren
id|IO_APIC_get_PCI_irq_vector
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MCA
DECL|variable|machine_id
id|EXPORT_SYMBOL
c_func
(paren
id|machine_id
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VT
DECL|variable|screen_info
id|EXPORT_SYMBOL
c_func
(paren
id|screen_info
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
DECL|variable|rtc_lock
id|EXPORT_SYMBOL
c_func
(paren
id|rtc_lock
)paren
suffix:semicolon
DECL|variable|set_nmi_callback
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|set_nmi_callback
)paren
suffix:semicolon
DECL|variable|unset_nmi_callback
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|unset_nmi_callback
)paren
suffix:semicolon
DECL|macro|memcmp
macro_line|#undef memcmp
r_extern
r_int
id|memcmp
c_func
(paren
r_const
r_void
op_star
comma
r_const
r_void
op_star
comma
id|__kernel_size_t
)paren
suffix:semicolon
DECL|variable|memcmp
id|EXPORT_SYMBOL
c_func
(paren
id|memcmp
)paren
suffix:semicolon
DECL|variable|register_die_notifier
id|EXPORT_SYMBOL
c_func
(paren
id|register_die_notifier
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HAVE_DEC_LOCK
DECL|variable|atomic_dec_and_lock
id|EXPORT_SYMBOL
c_func
(paren
id|atomic_dec_and_lock
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|__PAGE_KERNEL
id|EXPORT_SYMBOL
c_func
(paren
id|__PAGE_KERNEL
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HIGHMEM
DECL|variable|kmap
id|EXPORT_SYMBOL
c_func
(paren
id|kmap
)paren
suffix:semicolon
DECL|variable|kunmap
id|EXPORT_SYMBOL
c_func
(paren
id|kunmap
)paren
suffix:semicolon
DECL|variable|kmap_atomic
id|EXPORT_SYMBOL
c_func
(paren
id|kmap_atomic
)paren
suffix:semicolon
DECL|variable|kunmap_atomic
id|EXPORT_SYMBOL
c_func
(paren
id|kunmap_atomic
)paren
suffix:semicolon
DECL|variable|kmap_atomic_to_page
id|EXPORT_SYMBOL
c_func
(paren
id|kmap_atomic_to_page
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_X86_SPEEDSTEP_SMI) || defined(CONFIG_X86_SPEEDSTEP_SMI_MODULE)
DECL|variable|ist_info
id|EXPORT_SYMBOL
c_func
(paren
id|ist_info
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|csum_partial
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial
)paren
suffix:semicolon
eof
