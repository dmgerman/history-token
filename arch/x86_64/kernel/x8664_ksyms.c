macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/user.h&gt;
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
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mmx.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/nmi.h&gt;
macro_line|#include &lt;asm/kdebug.h&gt;
macro_line|#include &lt;asm/unistd.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
r_extern
id|spinlock_t
id|rtc_lock
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|__write_lock_failed
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
suffix:semicolon
r_extern
r_void
id|__read_lock_failed
c_func
(paren
id|rwlock_t
op_star
id|rw
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
singleline_comment|//EXPORT_SYMBOL(dump_fpu);
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
macro_line|#ifdef CONFIG_IO_DEBUG
DECL|variable|__io_virt_debug
id|EXPORT_SYMBOL
c_func
(paren
id|__io_virt_debug
)paren
suffix:semicolon
macro_line|#endif
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
multiline_comment|/* Networking helper routines. */
DECL|variable|csum_partial_copy_nocheck
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial_copy_nocheck
)paren
suffix:semicolon
DECL|variable|ip_compute_csum
id|EXPORT_SYMBOL
c_func
(paren
id|ip_compute_csum
)paren
suffix:semicolon
multiline_comment|/* Delay loops */
DECL|variable|__udelay
id|EXPORT_SYMBOL
c_func
(paren
id|__udelay
)paren
suffix:semicolon
DECL|variable|__ndelay
id|EXPORT_SYMBOL
c_func
(paren
id|__ndelay
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
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__get_user_1
)paren
suffix:semicolon
DECL|variable|__get_user_2
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__get_user_2
)paren
suffix:semicolon
DECL|variable|__get_user_4
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__get_user_4
)paren
suffix:semicolon
DECL|variable|__get_user_8
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__get_user_8
)paren
suffix:semicolon
DECL|variable|__put_user_1
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__put_user_1
)paren
suffix:semicolon
DECL|variable|__put_user_2
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__put_user_2
)paren
suffix:semicolon
DECL|variable|__put_user_4
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__put_user_4
)paren
suffix:semicolon
DECL|variable|__put_user_8
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__put_user_8
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
DECL|variable|copy_user_generic
id|EXPORT_SYMBOL
c_func
(paren
id|copy_user_generic
)paren
suffix:semicolon
DECL|variable|copy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|copy_from_user
)paren
suffix:semicolon
DECL|variable|copy_to_user
id|EXPORT_SYMBOL
c_func
(paren
id|copy_to_user
)paren
suffix:semicolon
DECL|variable|copy_in_user
id|EXPORT_SYMBOL
c_func
(paren
id|copy_in_user
)paren
suffix:semicolon
DECL|variable|strnlen_user
id|EXPORT_SYMBOL
c_func
(paren
id|strnlen_user
)paren
suffix:semicolon
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
DECL|variable|cpu_pda
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_pda
)paren
suffix:semicolon
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
DECL|variable|__write_lock_failed
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__write_lock_failed
)paren
suffix:semicolon
DECL|variable|__read_lock_failed
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__read_lock_failed
)paren
suffix:semicolon
DECL|variable|synchronize_irq
id|EXPORT_SYMBOL
c_func
(paren
id|synchronize_irq
)paren
suffix:semicolon
DECL|variable|smp_call_function
id|EXPORT_SYMBOL
c_func
(paren
id|smp_call_function
)paren
suffix:semicolon
DECL|variable|cpu_callout_map
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_callout_map
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
multiline_comment|/* Export string functions. We normally rely on gcc builtin for most of these,&n;   but gcc sometimes decides not to inline them. */
DECL|macro|memcpy
macro_line|#undef memcpy
DECL|macro|memset
macro_line|#undef memset
DECL|macro|memmove
macro_line|#undef memmove
DECL|macro|memchr
macro_line|#undef memchr
DECL|macro|strlen
macro_line|#undef strlen
DECL|macro|strcpy
macro_line|#undef strcpy
DECL|macro|strncmp
macro_line|#undef strncmp
DECL|macro|strncpy
macro_line|#undef strncpy
DECL|macro|strchr
macro_line|#undef strchr&t;
DECL|macro|strcmp
macro_line|#undef strcmp 
DECL|macro|strcpy
macro_line|#undef strcpy 
DECL|macro|strcat
macro_line|#undef strcat
r_extern
r_void
op_star
id|memset
c_func
(paren
r_void
op_star
comma
r_int
comma
id|__kernel_size_t
)paren
suffix:semicolon
r_extern
r_int
id|strlen
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
op_star
id|memmove
c_func
(paren
r_void
op_star
id|dest
comma
r_const
r_void
op_star
id|src
comma
r_int
id|count
)paren
suffix:semicolon
r_extern
r_char
op_star
id|strcpy
c_func
(paren
r_char
op_star
id|dest
comma
r_const
r_char
op_star
id|src
)paren
suffix:semicolon
r_extern
r_int
id|strcmp
c_func
(paren
r_const
r_char
op_star
id|cs
comma
r_const
r_char
op_star
id|ct
)paren
suffix:semicolon
r_extern
r_void
op_star
id|memchr
c_func
(paren
r_const
r_void
op_star
id|s
comma
r_int
id|c
comma
r_int
id|n
)paren
suffix:semicolon
r_extern
r_void
op_star
id|memcpy
c_func
(paren
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
r_extern
r_void
op_star
id|__memcpy
c_func
(paren
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
r_extern
r_char
op_star
id|strcat
c_func
(paren
r_char
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
DECL|variable|memset
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memset
)paren
suffix:semicolon
DECL|variable|strlen
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strlen
)paren
suffix:semicolon
DECL|variable|memmove
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memmove
)paren
suffix:semicolon
DECL|variable|strcpy
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strcpy
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
DECL|variable|strcat
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strcat
)paren
suffix:semicolon
DECL|variable|strncat
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strncat
)paren
suffix:semicolon
DECL|variable|memchr
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memchr
)paren
suffix:semicolon
DECL|variable|strrchr
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strrchr
)paren
suffix:semicolon
DECL|variable|strnlen
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strnlen
)paren
suffix:semicolon
DECL|variable|memscan
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memscan
)paren
suffix:semicolon
DECL|variable|memcpy
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memcpy
)paren
suffix:semicolon
DECL|variable|__memcpy
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__memcpy
)paren
suffix:semicolon
multiline_comment|/* syscall export needed for misdesigned sound drivers. */
r_extern
id|ssize_t
id|sys_read
c_func
(paren
r_int
r_int
id|fd
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_extern
id|off_t
id|sys_lseek
c_func
(paren
r_int
r_int
id|fd
comma
id|off_t
id|offset
comma
r_int
r_int
id|origin
)paren
suffix:semicolon
DECL|variable|sys_read
id|EXPORT_SYMBOL
c_func
(paren
id|sys_read
)paren
suffix:semicolon
DECL|variable|sys_lseek
id|EXPORT_SYMBOL
c_func
(paren
id|sys_lseek
)paren
suffix:semicolon
DECL|variable|sys_open
id|EXPORT_SYMBOL
c_func
(paren
id|sys_open
)paren
suffix:semicolon
DECL|variable|empty_zero_page
id|EXPORT_SYMBOL
c_func
(paren
id|empty_zero_page
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
DECL|variable|die_chain
id|EXPORT_SYMBOL
c_func
(paren
id|die_chain
)paren
suffix:semicolon
DECL|variable|cpu_sibling_map
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_sibling_map
)paren
suffix:semicolon
r_extern
r_void
id|do_softirq_thunk
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|do_softirq_thunk
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|do_softirq_thunk
)paren
suffix:semicolon
r_void
id|out_of_line_bug
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|out_of_line_bug
id|EXPORT_SYMBOL
c_func
(paren
id|out_of_line_bug
)paren
suffix:semicolon
DECL|variable|init_level4_pgt
id|EXPORT_SYMBOL
c_func
(paren
id|init_level4_pgt
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__supported_pte_mask
suffix:semicolon
DECL|variable|__supported_pte_mask
id|EXPORT_SYMBOL
c_func
(paren
id|__supported_pte_mask
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DISCONTIGMEM
DECL|variable|memnode_shift
id|EXPORT_SYMBOL
c_func
(paren
id|memnode_shift
)paren
suffix:semicolon
DECL|variable|memnodemap
id|EXPORT_SYMBOL
c_func
(paren
id|memnodemap
)paren
suffix:semicolon
DECL|variable|node_data
id|EXPORT_SYMBOL
c_func
(paren
id|node_data
)paren
suffix:semicolon
DECL|variable|fake_node
id|EXPORT_SYMBOL
c_func
(paren
id|fake_node
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|clear_page
id|EXPORT_SYMBOL
c_func
(paren
id|clear_page
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
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
eof
