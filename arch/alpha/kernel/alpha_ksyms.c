multiline_comment|/*&n; * linux/arch/alpha/kernel/ksyms.c&n; *&n; * Export the alpha-specific functions that are needed for loadable&n; * modules.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/console.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/fpu.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/vga.h&gt;
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;asm/unistd.h&gt;
r_extern
r_struct
id|hwrpb_struct
op_star
id|hwrpb
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
id|spinlock_t
id|rtc_lock
suffix:semicolon
multiline_comment|/* these are C runtime functions with special calling conventions: */
r_extern
r_void
id|__divl
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__reml
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__divq
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__remq
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__divlu
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__remlu
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__divqu
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__remqu
(paren
r_void
)paren
suffix:semicolon
DECL|variable|alpha_mv
id|EXPORT_SYMBOL
c_func
(paren
id|alpha_mv
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
DECL|variable|screen_info
id|EXPORT_SYMBOL
c_func
(paren
id|screen_info
)paren
suffix:semicolon
DECL|variable|perf_irq
id|EXPORT_SYMBOL
c_func
(paren
id|perf_irq
)paren
suffix:semicolon
DECL|variable|callback_getenv
id|EXPORT_SYMBOL
c_func
(paren
id|callback_getenv
)paren
suffix:semicolon
DECL|variable|callback_setenv
id|EXPORT_SYMBOL
c_func
(paren
id|callback_setenv
)paren
suffix:semicolon
DECL|variable|callback_save_env
id|EXPORT_SYMBOL
c_func
(paren
id|callback_save_env
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ALPHA_GENERIC
DECL|variable|alpha_using_srm
id|EXPORT_SYMBOL
c_func
(paren
id|alpha_using_srm
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ALPHA_GENERIC */
multiline_comment|/* platform dependent support */
DECL|variable|strcat
id|EXPORT_SYMBOL
c_func
(paren
id|strcat
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
DECL|variable|strncat
id|EXPORT_SYMBOL
c_func
(paren
id|strncat
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
DECL|variable|strchr
id|EXPORT_SYMBOL
c_func
(paren
id|strchr
)paren
suffix:semicolon
DECL|variable|strrchr
id|EXPORT_SYMBOL
c_func
(paren
id|strrchr
)paren
suffix:semicolon
DECL|variable|memcmp
id|EXPORT_SYMBOL
c_func
(paren
id|memcmp
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
DECL|variable|__memcpy
id|EXPORT_SYMBOL
c_func
(paren
id|__memcpy
)paren
suffix:semicolon
DECL|variable|__memset
id|EXPORT_SYMBOL
c_func
(paren
id|__memset
)paren
suffix:semicolon
DECL|variable|__memsetw
id|EXPORT_SYMBOL
c_func
(paren
id|__memsetw
)paren
suffix:semicolon
DECL|variable|__constant_c_memset
id|EXPORT_SYMBOL
c_func
(paren
id|__constant_c_memset
)paren
suffix:semicolon
DECL|variable|copy_page
id|EXPORT_SYMBOL
c_func
(paren
id|copy_page
)paren
suffix:semicolon
DECL|variable|clear_page
id|EXPORT_SYMBOL
c_func
(paren
id|clear_page
)paren
suffix:semicolon
DECL|variable|__direct_map_base
id|EXPORT_SYMBOL
c_func
(paren
id|__direct_map_base
)paren
suffix:semicolon
DECL|variable|__direct_map_size
id|EXPORT_SYMBOL
c_func
(paren
id|__direct_map_size
)paren
suffix:semicolon
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
DECL|variable|pci_map_single
id|EXPORT_SYMBOL
c_func
(paren
id|pci_map_single
)paren
suffix:semicolon
DECL|variable|pci_map_page
id|EXPORT_SYMBOL
c_func
(paren
id|pci_map_page
)paren
suffix:semicolon
DECL|variable|pci_unmap_single
id|EXPORT_SYMBOL
c_func
(paren
id|pci_unmap_single
)paren
suffix:semicolon
DECL|variable|pci_unmap_page
id|EXPORT_SYMBOL
c_func
(paren
id|pci_unmap_page
)paren
suffix:semicolon
DECL|variable|pci_map_sg
id|EXPORT_SYMBOL
c_func
(paren
id|pci_map_sg
)paren
suffix:semicolon
DECL|variable|pci_unmap_sg
id|EXPORT_SYMBOL
c_func
(paren
id|pci_unmap_sg
)paren
suffix:semicolon
DECL|variable|pci_dma_supported
id|EXPORT_SYMBOL
c_func
(paren
id|pci_dma_supported
)paren
suffix:semicolon
DECL|variable|pci_dac_dma_supported
id|EXPORT_SYMBOL
c_func
(paren
id|pci_dac_dma_supported
)paren
suffix:semicolon
DECL|variable|pci_dac_page_to_dma
id|EXPORT_SYMBOL
c_func
(paren
id|pci_dac_page_to_dma
)paren
suffix:semicolon
DECL|variable|pci_dac_dma_to_page
id|EXPORT_SYMBOL
c_func
(paren
id|pci_dac_dma_to_page
)paren
suffix:semicolon
DECL|variable|pci_dac_dma_to_offset
id|EXPORT_SYMBOL
c_func
(paren
id|pci_dac_dma_to_offset
)paren
suffix:semicolon
DECL|variable|alpha_gendev_to_pci
id|EXPORT_SYMBOL
c_func
(paren
id|alpha_gendev_to_pci
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|dma_set_mask
id|EXPORT_SYMBOL
c_func
(paren
id|dma_set_mask
)paren
suffix:semicolon
DECL|variable|dump_thread
id|EXPORT_SYMBOL
c_func
(paren
id|dump_thread
)paren
suffix:semicolon
DECL|variable|dump_elf_thread
id|EXPORT_SYMBOL
c_func
(paren
id|dump_elf_thread
)paren
suffix:semicolon
DECL|variable|dump_elf_task
id|EXPORT_SYMBOL
c_func
(paren
id|dump_elf_task
)paren
suffix:semicolon
DECL|variable|dump_elf_task_fp
id|EXPORT_SYMBOL
c_func
(paren
id|dump_elf_task_fp
)paren
suffix:semicolon
DECL|variable|hwrpb
id|EXPORT_SYMBOL
c_func
(paren
id|hwrpb
)paren
suffix:semicolon
DECL|variable|start_thread
id|EXPORT_SYMBOL
c_func
(paren
id|start_thread
)paren
suffix:semicolon
DECL|variable|alpha_read_fp_reg
id|EXPORT_SYMBOL
c_func
(paren
id|alpha_read_fp_reg
)paren
suffix:semicolon
DECL|variable|alpha_read_fp_reg_s
id|EXPORT_SYMBOL
c_func
(paren
id|alpha_read_fp_reg_s
)paren
suffix:semicolon
DECL|variable|alpha_write_fp_reg
id|EXPORT_SYMBOL
c_func
(paren
id|alpha_write_fp_reg
)paren
suffix:semicolon
DECL|variable|alpha_write_fp_reg_s
id|EXPORT_SYMBOL
c_func
(paren
id|alpha_write_fp_reg_s
)paren
suffix:semicolon
multiline_comment|/* In-kernel system calls.  */
DECL|variable|kernel_thread
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_thread
)paren
suffix:semicolon
DECL|variable|sys_open
id|EXPORT_SYMBOL
c_func
(paren
id|sys_open
)paren
suffix:semicolon
DECL|variable|sys_dup
id|EXPORT_SYMBOL
c_func
(paren
id|sys_dup
)paren
suffix:semicolon
DECL|variable|sys_exit
id|EXPORT_SYMBOL
c_func
(paren
id|sys_exit
)paren
suffix:semicolon
DECL|variable|sys_write
id|EXPORT_SYMBOL
c_func
(paren
id|sys_write
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
DECL|variable|execve
id|EXPORT_SYMBOL
c_func
(paren
id|execve
)paren
suffix:semicolon
DECL|variable|sys_setsid
id|EXPORT_SYMBOL
c_func
(paren
id|sys_setsid
)paren
suffix:semicolon
DECL|variable|sys_wait4
id|EXPORT_SYMBOL
c_func
(paren
id|sys_wait4
)paren
suffix:semicolon
multiline_comment|/* Networking helper routines. */
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
DECL|variable|csum_partial_copy_nocheck
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial_copy_nocheck
)paren
suffix:semicolon
DECL|variable|csum_partial_copy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial_copy_from_user
)paren
suffix:semicolon
DECL|variable|csum_ipv6_magic
id|EXPORT_SYMBOL
c_func
(paren
id|csum_ipv6_magic
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MATHEMU_MODULE
r_extern
r_int
(paren
op_star
id|alpha_fp_emul_imprecise
)paren
(paren
r_struct
id|pt_regs
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|alpha_fp_emul
)paren
(paren
r_int
r_int
id|pc
)paren
suffix:semicolon
DECL|variable|alpha_fp_emul_imprecise
id|EXPORT_SYMBOL
c_func
(paren
id|alpha_fp_emul_imprecise
)paren
suffix:semicolon
DECL|variable|alpha_fp_emul
id|EXPORT_SYMBOL
c_func
(paren
id|alpha_fp_emul
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ALPHA_BROKEN_IRQ_MASK
DECL|variable|__min_ipl
id|EXPORT_SYMBOL
c_func
(paren
id|__min_ipl
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * The following are specially called from the uaccess assembly stubs.&n; */
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
multiline_comment|/* Semaphore helper functions.  */
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
DECL|variable|__up_wakeup
id|EXPORT_SYMBOL
c_func
(paren
id|__up_wakeup
)paren
suffix:semicolon
DECL|variable|down
id|EXPORT_SYMBOL
c_func
(paren
id|down
)paren
suffix:semicolon
DECL|variable|down_interruptible
id|EXPORT_SYMBOL
c_func
(paren
id|down_interruptible
)paren
suffix:semicolon
DECL|variable|down_trylock
id|EXPORT_SYMBOL
c_func
(paren
id|down_trylock
)paren
suffix:semicolon
DECL|variable|up
id|EXPORT_SYMBOL
c_func
(paren
id|up
)paren
suffix:semicolon
multiline_comment|/* &n; * SMP-specific symbols.&n; */
macro_line|#ifdef CONFIG_SMP
DECL|variable|synchronize_irq
id|EXPORT_SYMBOL
c_func
(paren
id|synchronize_irq
)paren
suffix:semicolon
DECL|variable|flush_tlb_mm
id|EXPORT_SYMBOL
c_func
(paren
id|flush_tlb_mm
)paren
suffix:semicolon
DECL|variable|flush_tlb_range
id|EXPORT_SYMBOL
c_func
(paren
id|flush_tlb_range
)paren
suffix:semicolon
DECL|variable|flush_tlb_page
id|EXPORT_SYMBOL
c_func
(paren
id|flush_tlb_page
)paren
suffix:semicolon
DECL|variable|smp_imb
id|EXPORT_SYMBOL
c_func
(paren
id|smp_imb
)paren
suffix:semicolon
DECL|variable|cpu_data
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_data
)paren
suffix:semicolon
DECL|variable|smp_num_cpus
id|EXPORT_SYMBOL
c_func
(paren
id|smp_num_cpus
)paren
suffix:semicolon
DECL|variable|smp_call_function
id|EXPORT_SYMBOL
c_func
(paren
id|smp_call_function
)paren
suffix:semicolon
DECL|variable|smp_call_function_on_cpu
id|EXPORT_SYMBOL
c_func
(paren
id|smp_call_function_on_cpu
)paren
suffix:semicolon
DECL|variable|_atomic_dec_and_lock
id|EXPORT_SYMBOL
c_func
(paren
id|_atomic_dec_and_lock
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_SPINLOCK
DECL|variable|_raw_spin_unlock
id|EXPORT_SYMBOL
c_func
(paren
id|_raw_spin_unlock
)paren
suffix:semicolon
DECL|variable|debug_spin_lock
id|EXPORT_SYMBOL
c_func
(paren
id|debug_spin_lock
)paren
suffix:semicolon
DECL|variable|debug_spin_trylock
id|EXPORT_SYMBOL
c_func
(paren
id|debug_spin_trylock
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DEBUG_RWLOCK
DECL|variable|_raw_write_lock
id|EXPORT_SYMBOL
c_func
(paren
id|_raw_write_lock
)paren
suffix:semicolon
DECL|variable|_raw_read_lock
id|EXPORT_SYMBOL
c_func
(paren
id|_raw_read_lock
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|cpu_present_mask
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_present_mask
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
multiline_comment|/*&n; * NUMA specific symbols&n; */
macro_line|#ifdef CONFIG_DISCONTIGMEM
DECL|variable|node_data
id|EXPORT_SYMBOL
c_func
(paren
id|node_data
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_DISCONTIGMEM */
DECL|variable|rtc_lock
id|EXPORT_SYMBOL
c_func
(paren
id|rtc_lock
)paren
suffix:semicolon
multiline_comment|/*&n; * The following are special because they&squot;re not called&n; * explicitly (the C compiler or assembler generates them in&n; * response to division operations).  Fortunately, their&n; * interface isn&squot;t gonna change any time soon now, so it&squot;s OK&n; * to leave it out of version control.&n; */
DECL|macro|memcpy
macro_line|# undef memcpy
DECL|macro|memset
macro_line|# undef memset
DECL|variable|__divl
id|EXPORT_SYMBOL
c_func
(paren
id|__divl
)paren
suffix:semicolon
DECL|variable|__divlu
id|EXPORT_SYMBOL
c_func
(paren
id|__divlu
)paren
suffix:semicolon
DECL|variable|__divq
id|EXPORT_SYMBOL
c_func
(paren
id|__divq
)paren
suffix:semicolon
DECL|variable|__divqu
id|EXPORT_SYMBOL
c_func
(paren
id|__divqu
)paren
suffix:semicolon
DECL|variable|__reml
id|EXPORT_SYMBOL
c_func
(paren
id|__reml
)paren
suffix:semicolon
DECL|variable|__remlu
id|EXPORT_SYMBOL
c_func
(paren
id|__remlu
)paren
suffix:semicolon
DECL|variable|__remq
id|EXPORT_SYMBOL
c_func
(paren
id|__remq
)paren
suffix:semicolon
DECL|variable|__remqu
id|EXPORT_SYMBOL
c_func
(paren
id|__remqu
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
DECL|variable|memchr
id|EXPORT_SYMBOL
c_func
(paren
id|memchr
)paren
suffix:semicolon
DECL|variable|get_wchan
id|EXPORT_SYMBOL
c_func
(paren
id|get_wchan
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ALPHA_IRONGATE
DECL|variable|irongate_ioremap
id|EXPORT_SYMBOL
c_func
(paren
id|irongate_ioremap
)paren
suffix:semicolon
DECL|variable|irongate_iounmap
id|EXPORT_SYMBOL
c_func
(paren
id|irongate_iounmap
)paren
suffix:semicolon
macro_line|#endif
eof
