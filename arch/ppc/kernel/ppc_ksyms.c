multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;linux/nvram.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/ide.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;linux/adb.h&gt;
macro_line|#include &lt;linux/cuda.h&gt;
macro_line|#include &lt;linux/pmu.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pmac_feature.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/hw_irq.h&gt;
macro_line|#include &lt;asm/nvram.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/backlight.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;asm/smplock.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#endif /* CONFIG_SMP */
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#include &lt;asm/btext.h&gt;
macro_line|#ifdef  CONFIG_8xx
macro_line|#include &lt;asm/commproc.h&gt;
macro_line|#endif
multiline_comment|/* Tell string.h we don&squot;t want memcpy etc. as cpp defines */
DECL|macro|EXPORT_SYMTAB_STROPS
mdefine_line|#define EXPORT_SYMTAB_STROPS
r_extern
r_void
id|transfer_to_handler
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|do_syscall_trace
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|do_IRQ
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|MachineCheckException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|AlignmentException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|ProgramCheckException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|SingleStepException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|do_signal
c_func
(paren
id|sigset_t
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
id|pmac_newworld
suffix:semicolon
r_extern
r_int
id|sys_sigreturn
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_int
r_int
id|__ashrdi3
c_func
(paren
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_int
r_int
id|__ashldi3
c_func
(paren
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_int
r_int
id|__lshrdi3
c_func
(paren
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|abs
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
r_char
id|__res
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|mm_ptov
(paren
r_int
r_int
id|paddr
)paren
suffix:semicolon
DECL|variable|clear_page
id|EXPORT_SYMBOL
c_func
(paren
id|clear_page
)paren
suffix:semicolon
DECL|variable|do_signal
id|EXPORT_SYMBOL
c_func
(paren
id|do_signal
)paren
suffix:semicolon
DECL|variable|do_syscall_trace
id|EXPORT_SYMBOL
c_func
(paren
id|do_syscall_trace
)paren
suffix:semicolon
DECL|variable|transfer_to_handler
id|EXPORT_SYMBOL
c_func
(paren
id|transfer_to_handler
)paren
suffix:semicolon
DECL|variable|do_IRQ
id|EXPORT_SYMBOL
c_func
(paren
id|do_IRQ
)paren
suffix:semicolon
DECL|variable|MachineCheckException
id|EXPORT_SYMBOL
c_func
(paren
id|MachineCheckException
)paren
suffix:semicolon
DECL|variable|AlignmentException
id|EXPORT_SYMBOL
c_func
(paren
id|AlignmentException
)paren
suffix:semicolon
DECL|variable|ProgramCheckException
id|EXPORT_SYMBOL
c_func
(paren
id|ProgramCheckException
)paren
suffix:semicolon
DECL|variable|SingleStepException
id|EXPORT_SYMBOL
c_func
(paren
id|SingleStepException
)paren
suffix:semicolon
DECL|variable|sys_sigreturn
id|EXPORT_SYMBOL
c_func
(paren
id|sys_sigreturn
)paren
suffix:semicolon
DECL|variable|ppc_n_lost_interrupts
id|EXPORT_SYMBOL
c_func
(paren
id|ppc_n_lost_interrupts
)paren
suffix:semicolon
DECL|variable|ppc_lost_interrupts
id|EXPORT_SYMBOL
c_func
(paren
id|ppc_lost_interrupts
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
macro_line|#ifdef CONFIG_SMP
DECL|variable|kernel_flag
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_flag
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
DECL|variable|ISA_DMA_THRESHOLD
id|EXPORT_SYMBOL
c_func
(paren
id|ISA_DMA_THRESHOLD
)paren
suffix:semicolon
DECL|variable|DMA_MODE_READ
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|DMA_MODE_READ
)paren
suffix:semicolon
DECL|variable|DMA_MODE_WRITE
id|EXPORT_SYMBOL
c_func
(paren
id|DMA_MODE_WRITE
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_ALL_PPC)
DECL|variable|_prep_type
id|EXPORT_SYMBOL
c_func
(paren
id|_prep_type
)paren
suffix:semicolon
DECL|variable|ucSystemType
id|EXPORT_SYMBOL
c_func
(paren
id|ucSystemType
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if !__INLINE_BITOPS
DECL|variable|set_bit
id|EXPORT_SYMBOL
c_func
(paren
id|set_bit
)paren
suffix:semicolon
DECL|variable|clear_bit
id|EXPORT_SYMBOL
c_func
(paren
id|clear_bit
)paren
suffix:semicolon
DECL|variable|change_bit
id|EXPORT_SYMBOL
c_func
(paren
id|change_bit
)paren
suffix:semicolon
DECL|variable|test_and_set_bit
id|EXPORT_SYMBOL
c_func
(paren
id|test_and_set_bit
)paren
suffix:semicolon
DECL|variable|test_and_clear_bit
id|EXPORT_SYMBOL
c_func
(paren
id|test_and_clear_bit
)paren
suffix:semicolon
DECL|variable|test_and_change_bit
id|EXPORT_SYMBOL
c_func
(paren
id|test_and_change_bit
)paren
suffix:semicolon
macro_line|#endif /* __INLINE_BITOPS */
DECL|variable|strcpy
id|EXPORT_SYMBOL
c_func
(paren
id|strcpy
)paren
suffix:semicolon
DECL|variable|strncpy
id|EXPORT_SYMBOL
c_func
(paren
id|strncpy
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
DECL|variable|strcmp
id|EXPORT_SYMBOL
c_func
(paren
id|strcmp
)paren
suffix:semicolon
DECL|variable|strncmp
id|EXPORT_SYMBOL
c_func
(paren
id|strncmp
)paren
suffix:semicolon
DECL|variable|strcasecmp
id|EXPORT_SYMBOL
c_func
(paren
id|strcasecmp
)paren
suffix:semicolon
multiline_comment|/* EXPORT_SYMBOL(csum_partial); already in net/netsyms.c */
DECL|variable|csum_partial_copy_generic
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial_copy_generic
)paren
suffix:semicolon
DECL|variable|ip_fast_csum
id|EXPORT_SYMBOL
c_func
(paren
id|ip_fast_csum
)paren
suffix:semicolon
DECL|variable|csum_tcpudp_magic
id|EXPORT_SYMBOL
c_func
(paren
id|csum_tcpudp_magic
)paren
suffix:semicolon
DECL|variable|__copy_tofrom_user
id|EXPORT_SYMBOL
c_func
(paren
id|__copy_tofrom_user
)paren
suffix:semicolon
DECL|variable|__clear_user
id|EXPORT_SYMBOL
c_func
(paren
id|__clear_user
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
multiline_comment|/*&n;EXPORT_SYMBOL(inb);&n;EXPORT_SYMBOL(inw);&n;EXPORT_SYMBOL(inl);&n;EXPORT_SYMBOL(outb);&n;EXPORT_SYMBOL(outw);&n;EXPORT_SYMBOL(outl);&n;EXPORT_SYMBOL(outsl);*/
DECL|variable|_insb
id|EXPORT_SYMBOL
c_func
(paren
id|_insb
)paren
suffix:semicolon
DECL|variable|_outsb
id|EXPORT_SYMBOL
c_func
(paren
id|_outsb
)paren
suffix:semicolon
DECL|variable|_insw
id|EXPORT_SYMBOL
c_func
(paren
id|_insw
)paren
suffix:semicolon
DECL|variable|_outsw
id|EXPORT_SYMBOL
c_func
(paren
id|_outsw
)paren
suffix:semicolon
DECL|variable|_insl
id|EXPORT_SYMBOL
c_func
(paren
id|_insl
)paren
suffix:semicolon
DECL|variable|_outsl
id|EXPORT_SYMBOL
c_func
(paren
id|_outsl
)paren
suffix:semicolon
DECL|variable|_insw_ns
id|EXPORT_SYMBOL
c_func
(paren
id|_insw_ns
)paren
suffix:semicolon
DECL|variable|_outsw_ns
id|EXPORT_SYMBOL
c_func
(paren
id|_outsw_ns
)paren
suffix:semicolon
DECL|variable|_insl_ns
id|EXPORT_SYMBOL
c_func
(paren
id|_insl_ns
)paren
suffix:semicolon
DECL|variable|_outsl_ns
id|EXPORT_SYMBOL
c_func
(paren
id|_outsl_ns
)paren
suffix:semicolon
DECL|variable|iopa
id|EXPORT_SYMBOL
c_func
(paren
id|iopa
)paren
suffix:semicolon
DECL|variable|mm_ptov
id|EXPORT_SYMBOL
c_func
(paren
id|mm_ptov
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_PPC_ISERIES
DECL|variable|ioremap
id|EXPORT_SYMBOL
c_func
(paren
id|ioremap
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
macro_line|#endif
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_IDE_MODULE)
DECL|variable|ppc_ide_md
id|EXPORT_SYMBOL
c_func
(paren
id|ppc_ide_md
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PCI
DECL|variable|isa_io_base
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|isa_io_base
)paren
suffix:semicolon
DECL|variable|isa_mem_base
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|isa_mem_base
)paren
suffix:semicolon
DECL|variable|pci_dram_offset
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|pci_dram_offset
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
DECL|variable|pci_bus_io_base
id|EXPORT_SYMBOL
c_func
(paren
id|pci_bus_io_base
)paren
suffix:semicolon
DECL|variable|pci_bus_io_base_phys
id|EXPORT_SYMBOL
c_func
(paren
id|pci_bus_io_base_phys
)paren
suffix:semicolon
DECL|variable|pci_bus_mem_base_phys
id|EXPORT_SYMBOL
c_func
(paren
id|pci_bus_mem_base_phys
)paren
suffix:semicolon
DECL|variable|pci_bus_to_hose
id|EXPORT_SYMBOL
c_func
(paren
id|pci_bus_to_hose
)paren
suffix:semicolon
DECL|variable|pci_resource_to_bus
id|EXPORT_SYMBOL
c_func
(paren
id|pci_resource_to_bus
)paren
suffix:semicolon
DECL|variable|pci_phys_to_bus
id|EXPORT_SYMBOL
c_func
(paren
id|pci_phys_to_bus
)paren
suffix:semicolon
DECL|variable|pci_bus_to_phys
id|EXPORT_SYMBOL
c_func
(paren
id|pci_bus_to_phys
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PCI */
macro_line|#ifdef CONFIG_NOT_COHERENT_CACHE
DECL|variable|consistent_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|consistent_alloc
)paren
suffix:semicolon
DECL|variable|consistent_free
id|EXPORT_SYMBOL
c_func
(paren
id|consistent_free
)paren
suffix:semicolon
DECL|variable|consistent_sync
id|EXPORT_SYMBOL
c_func
(paren
id|consistent_sync
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|start_thread
id|EXPORT_SYMBOL
c_func
(paren
id|start_thread
)paren
suffix:semicolon
DECL|variable|kernel_thread
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_thread
)paren
suffix:semicolon
DECL|variable|flush_instruction_cache
id|EXPORT_SYMBOL
c_func
(paren
id|flush_instruction_cache
)paren
suffix:semicolon
DECL|variable|giveup_fpu
id|EXPORT_SYMBOL
c_func
(paren
id|giveup_fpu
)paren
suffix:semicolon
DECL|variable|enable_kernel_fp
id|EXPORT_SYMBOL
c_func
(paren
id|enable_kernel_fp
)paren
suffix:semicolon
DECL|variable|flush_icache_range
id|EXPORT_SYMBOL
c_func
(paren
id|flush_icache_range
)paren
suffix:semicolon
DECL|variable|flush_dcache_range
id|EXPORT_SYMBOL
c_func
(paren
id|flush_dcache_range
)paren
suffix:semicolon
DECL|variable|flush_icache_user_range
id|EXPORT_SYMBOL
c_func
(paren
id|flush_icache_user_range
)paren
suffix:semicolon
DECL|variable|flush_icache_page
id|EXPORT_SYMBOL
c_func
(paren
id|flush_icache_page
)paren
suffix:semicolon
DECL|variable|flush_dcache_page
id|EXPORT_SYMBOL
c_func
(paren
id|flush_dcache_page
)paren
suffix:semicolon
DECL|variable|xchg_u32
id|EXPORT_SYMBOL
c_func
(paren
id|xchg_u32
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ALTIVEC
DECL|variable|last_task_used_altivec
id|EXPORT_SYMBOL
c_func
(paren
id|last_task_used_altivec
)paren
suffix:semicolon
DECL|variable|giveup_altivec
id|EXPORT_SYMBOL
c_func
(paren
id|giveup_altivec
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ALTIVEC */
macro_line|#ifdef CONFIG_SMP
macro_line|#ifdef CONFIG_DEBUG_SPINLOCK
DECL|variable|_raw_spin_lock
id|EXPORT_SYMBOL
c_func
(paren
id|_raw_spin_lock
)paren
suffix:semicolon
DECL|variable|_raw_spin_unlock
id|EXPORT_SYMBOL
c_func
(paren
id|_raw_spin_unlock
)paren
suffix:semicolon
DECL|variable|_raw_spin_trylock
id|EXPORT_SYMBOL
c_func
(paren
id|_raw_spin_trylock
)paren
suffix:semicolon
DECL|variable|_raw_read_lock
id|EXPORT_SYMBOL
c_func
(paren
id|_raw_read_lock
)paren
suffix:semicolon
DECL|variable|_raw_read_unlock
id|EXPORT_SYMBOL
c_func
(paren
id|_raw_read_unlock
)paren
suffix:semicolon
DECL|variable|_raw_write_lock
id|EXPORT_SYMBOL
c_func
(paren
id|_raw_write_lock
)paren
suffix:semicolon
DECL|variable|_raw_write_unlock
id|EXPORT_SYMBOL
c_func
(paren
id|_raw_write_unlock
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|smp_call_function
id|EXPORT_SYMBOL
c_func
(paren
id|smp_call_function
)paren
suffix:semicolon
DECL|variable|smp_hw_index
id|EXPORT_SYMBOL
c_func
(paren
id|smp_hw_index
)paren
suffix:semicolon
DECL|variable|synchronize_irq
id|EXPORT_SYMBOL
c_func
(paren
id|synchronize_irq
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|ppc_md
id|EXPORT_SYMBOL
c_func
(paren
id|ppc_md
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ADB
DECL|variable|adb_request
id|EXPORT_SYMBOL
c_func
(paren
id|adb_request
)paren
suffix:semicolon
DECL|variable|adb_register
id|EXPORT_SYMBOL
c_func
(paren
id|adb_register
)paren
suffix:semicolon
DECL|variable|adb_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|adb_unregister
)paren
suffix:semicolon
DECL|variable|adb_poll
id|EXPORT_SYMBOL
c_func
(paren
id|adb_poll
)paren
suffix:semicolon
DECL|variable|adb_try_handler_change
id|EXPORT_SYMBOL
c_func
(paren
id|adb_try_handler_change
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ADB */
macro_line|#ifdef CONFIG_ADB_CUDA
DECL|variable|cuda_request
id|EXPORT_SYMBOL
c_func
(paren
id|cuda_request
)paren
suffix:semicolon
DECL|variable|cuda_poll
id|EXPORT_SYMBOL
c_func
(paren
id|cuda_poll
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ADB_CUDA */
macro_line|#ifdef CONFIG_PMAC_BACKLIGHT
DECL|variable|get_backlight_level
id|EXPORT_SYMBOL
c_func
(paren
id|get_backlight_level
)paren
suffix:semicolon
DECL|variable|set_backlight_level
id|EXPORT_SYMBOL
c_func
(paren
id|set_backlight_level
)paren
suffix:semicolon
DECL|variable|set_backlight_enable
id|EXPORT_SYMBOL
c_func
(paren
id|set_backlight_enable
)paren
suffix:semicolon
DECL|variable|register_backlight_controller
id|EXPORT_SYMBOL
c_func
(paren
id|register_backlight_controller
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PMAC_BACKLIGHT */
macro_line|#if defined(CONFIG_ALL_PPC)
DECL|variable|_machine
id|EXPORT_SYMBOL
c_func
(paren
id|_machine
)paren
suffix:semicolon
DECL|variable|sys_ctrler
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|sys_ctrler
)paren
suffix:semicolon
DECL|variable|find_devices
id|EXPORT_SYMBOL
c_func
(paren
id|find_devices
)paren
suffix:semicolon
DECL|variable|find_type_devices
id|EXPORT_SYMBOL
c_func
(paren
id|find_type_devices
)paren
suffix:semicolon
DECL|variable|find_compatible_devices
id|EXPORT_SYMBOL
c_func
(paren
id|find_compatible_devices
)paren
suffix:semicolon
DECL|variable|find_path_device
id|EXPORT_SYMBOL
c_func
(paren
id|find_path_device
)paren
suffix:semicolon
DECL|variable|device_is_compatible
id|EXPORT_SYMBOL
c_func
(paren
id|device_is_compatible
)paren
suffix:semicolon
DECL|variable|machine_is_compatible
id|EXPORT_SYMBOL
c_func
(paren
id|machine_is_compatible
)paren
suffix:semicolon
DECL|variable|find_all_nodes
id|EXPORT_SYMBOL
c_func
(paren
id|find_all_nodes
)paren
suffix:semicolon
DECL|variable|get_property
id|EXPORT_SYMBOL
c_func
(paren
id|get_property
)paren
suffix:semicolon
DECL|variable|request_OF_resource
id|EXPORT_SYMBOL
c_func
(paren
id|request_OF_resource
)paren
suffix:semicolon
DECL|variable|release_OF_resource
id|EXPORT_SYMBOL
c_func
(paren
id|release_OF_resource
)paren
suffix:semicolon
DECL|variable|pci_device_to_OF_node
id|EXPORT_SYMBOL
c_func
(paren
id|pci_device_to_OF_node
)paren
suffix:semicolon
DECL|variable|pci_device_from_OF_node
id|EXPORT_SYMBOL
c_func
(paren
id|pci_device_from_OF_node
)paren
suffix:semicolon
DECL|variable|pmac_newworld
id|EXPORT_SYMBOL
c_func
(paren
id|pmac_newworld
)paren
suffix:semicolon
macro_line|#endif /* defined(CONFIG_ALL_PPC) */
macro_line|#if defined(CONFIG_BOOTX_TEXT)
DECL|variable|btext_update_display
id|EXPORT_SYMBOL
c_func
(paren
id|btext_update_display
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_SCSI) &amp;&amp; defined(CONFIG_ALL_PPC)
DECL|variable|note_scsi_host
id|EXPORT_SYMBOL
c_func
(paren
id|note_scsi_host
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VT
DECL|variable|kd_mksound
id|EXPORT_SYMBOL
c_func
(paren
id|kd_mksound
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NVRAM
DECL|variable|nvram_read_byte
id|EXPORT_SYMBOL
c_func
(paren
id|nvram_read_byte
)paren
suffix:semicolon
DECL|variable|nvram_write_byte
id|EXPORT_SYMBOL
c_func
(paren
id|nvram_write_byte
)paren
suffix:semicolon
DECL|variable|pmac_xpram_read
id|EXPORT_SYMBOL
c_func
(paren
id|pmac_xpram_read
)paren
suffix:semicolon
DECL|variable|pmac_xpram_write
id|EXPORT_SYMBOL
c_func
(paren
id|pmac_xpram_write
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_NVRAM */
DECL|variable|to_tm
id|EXPORT_SYMBOL
c_func
(paren
id|to_tm
)paren
suffix:semicolon
DECL|variable|__ashrdi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__ashrdi3
)paren
suffix:semicolon
DECL|variable|__ashldi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__ashldi3
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
DECL|variable|memmove
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memmove
)paren
suffix:semicolon
DECL|variable|memscan
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memscan
)paren
suffix:semicolon
DECL|variable|memcmp
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memcmp
)paren
suffix:semicolon
DECL|variable|memchr
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memchr
)paren
suffix:semicolon
DECL|variable|abs
id|EXPORT_SYMBOL
c_func
(paren
id|abs
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_FB_VGA16_MODULE)
DECL|variable|screen_info
id|EXPORT_SYMBOL
c_func
(paren
id|screen_info
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|__delay
id|EXPORT_SYMBOL
c_func
(paren
id|__delay
)paren
suffix:semicolon
macro_line|#ifndef INLINE_IRQS
DECL|variable|__sti
id|EXPORT_SYMBOL
c_func
(paren
id|__sti
)paren
suffix:semicolon
DECL|variable|__sti_end
id|EXPORT_SYMBOL
c_func
(paren
id|__sti_end
)paren
suffix:semicolon
DECL|variable|__cli
id|EXPORT_SYMBOL
c_func
(paren
id|__cli
)paren
suffix:semicolon
DECL|variable|__cli_end
id|EXPORT_SYMBOL
c_func
(paren
id|__cli_end
)paren
suffix:semicolon
DECL|variable|__save_flags_ptr
id|EXPORT_SYMBOL
c_func
(paren
id|__save_flags_ptr
)paren
suffix:semicolon
DECL|variable|__save_flags_ptr_end
id|EXPORT_SYMBOL
c_func
(paren
id|__save_flags_ptr_end
)paren
suffix:semicolon
DECL|variable|__restore_flags
id|EXPORT_SYMBOL
c_func
(paren
id|__restore_flags
)paren
suffix:semicolon
DECL|variable|__restore_flags_end
id|EXPORT_SYMBOL
c_func
(paren
id|__restore_flags_end
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|timer_interrupt
id|EXPORT_SYMBOL
c_func
(paren
id|timer_interrupt
)paren
suffix:semicolon
DECL|variable|irq_desc
id|EXPORT_SYMBOL
c_func
(paren
id|irq_desc
)paren
suffix:semicolon
r_void
id|ppc_irq_dispatch_handler
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_int
)paren
suffix:semicolon
DECL|variable|ppc_irq_dispatch_handler
id|EXPORT_SYMBOL
c_func
(paren
id|ppc_irq_dispatch_handler
)paren
suffix:semicolon
DECL|variable|tb_ticks_per_jiffy
id|EXPORT_SYMBOL
c_func
(paren
id|tb_ticks_per_jiffy
)paren
suffix:semicolon
DECL|variable|get_wchan
id|EXPORT_SYMBOL
c_func
(paren
id|get_wchan
)paren
suffix:semicolon
DECL|variable|console_drivers
id|EXPORT_SYMBOL
c_func
(paren
id|console_drivers
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_XMON
r_extern
r_void
id|xmon_printf
c_func
(paren
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|variable|xmon
id|EXPORT_SYMBOL
c_func
(paren
id|xmon
)paren
suffix:semicolon
DECL|variable|xmon_printf
id|EXPORT_SYMBOL
c_func
(paren
id|xmon_printf
)paren
suffix:semicolon
macro_line|#endif
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
macro_line|#if defined(CONFIG_KGDB) || defined(CONFIG_XMON)
r_extern
r_void
(paren
op_star
id|debugger
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|debugger_bpt
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|debugger_sstep
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|debugger_iabr_match
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|debugger_dabr_match
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|debugger_fault_handler
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|debugger
id|EXPORT_SYMBOL
c_func
(paren
id|debugger
)paren
suffix:semicolon
DECL|variable|debugger_bpt
id|EXPORT_SYMBOL
c_func
(paren
id|debugger_bpt
)paren
suffix:semicolon
DECL|variable|debugger_sstep
id|EXPORT_SYMBOL
c_func
(paren
id|debugger_sstep
)paren
suffix:semicolon
DECL|variable|debugger_iabr_match
id|EXPORT_SYMBOL
c_func
(paren
id|debugger_iabr_match
)paren
suffix:semicolon
DECL|variable|debugger_dabr_match
id|EXPORT_SYMBOL
c_func
(paren
id|debugger_dabr_match
)paren
suffix:semicolon
DECL|variable|debugger_fault_handler
id|EXPORT_SYMBOL
c_func
(paren
id|debugger_fault_handler
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef  CONFIG_8xx
DECL|variable|__res
id|EXPORT_SYMBOL
c_func
(paren
id|__res
)paren
suffix:semicolon
DECL|variable|cpm_install_handler
id|EXPORT_SYMBOL
c_func
(paren
id|cpm_install_handler
)paren
suffix:semicolon
DECL|variable|cpm_free_handler
id|EXPORT_SYMBOL
c_func
(paren
id|cpm_free_handler
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_8xx */
macro_line|#if defined(CONFIG_8xx) || defined(CONFIG_8260)
DECL|variable|request_8xxirq
id|EXPORT_SYMBOL
c_func
(paren
id|request_8xxirq
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|next_mmu_context
id|EXPORT_SYMBOL
c_func
(paren
id|next_mmu_context
)paren
suffix:semicolon
DECL|variable|set_context
id|EXPORT_SYMBOL
c_func
(paren
id|set_context
)paren
suffix:semicolon
DECL|variable|handle_mm_fault
id|EXPORT_SYMBOL
c_func
(paren
id|handle_mm_fault
)paren
suffix:semicolon
multiline_comment|/* For MOL */
DECL|variable|disarm_decr
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|disarm_decr
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_STD_MMU
DECL|variable|flush_hash_pages
id|EXPORT_SYMBOL
c_func
(paren
id|flush_hash_pages
)paren
suffix:semicolon
multiline_comment|/* For MOL */
r_extern
r_int
op_star
id|intercept_table
suffix:semicolon
DECL|variable|intercept_table
id|EXPORT_SYMBOL
c_func
(paren
id|intercept_table
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|cur_cpu_spec
id|EXPORT_SYMBOL
c_func
(paren
id|cur_cpu_spec
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_ALL_PPC)
r_extern
r_int
r_int
id|agp_special_page
suffix:semicolon
DECL|variable|agp_special_page
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|agp_special_page
)paren
suffix:semicolon
macro_line|#endif /* defined(CONFIG_ALL_PPC) */
eof
