multiline_comment|/* &n; * c 2001 PPC 64 Team, IBM Corp&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/hw_irq.h&gt;
macro_line|#include &lt;asm/abs_addr.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#ifdef CONFIG_PPC_ISERIES
macro_line|#include &lt;asm/iSeries/iSeries_pci.h&gt;
macro_line|#include &lt;asm/iSeries/iSeries_proc.h&gt;
macro_line|#include &lt;asm/iSeries/mf.h&gt;
macro_line|#include &lt;asm/iSeries/HvLpEvent.h&gt;
macro_line|#include &lt;asm/iSeries/HvLpConfig.h&gt;
macro_line|#endif
r_extern
r_int
id|sys_ioctl
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
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
id|register_ioctl32_conversion
c_func
(paren
r_int
r_int
id|cmd
comma
r_int
(paren
op_star
id|handler
)paren
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|file
op_star
)paren
)paren
suffix:semicolon
r_extern
r_int
id|unregister_ioctl32_conversion
c_func
(paren
r_int
r_int
id|cmd
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
r_struct
id|pci_dev
op_star
id|iSeries_veth_dev
suffix:semicolon
r_extern
r_struct
id|pci_dev
op_star
id|iSeries_vio_dev
suffix:semicolon
DECL|variable|do_signal
id|EXPORT_SYMBOL
c_func
(paren
id|do_signal
)paren
suffix:semicolon
DECL|variable|sys_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|sys_ioctl
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
macro_line|#ifdef CONFIG_SMP
DECL|variable|synchronize_irq
id|EXPORT_SYMBOL
c_func
(paren
id|synchronize_irq
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
DECL|variable|register_ioctl32_conversion
id|EXPORT_SYMBOL
c_func
(paren
id|register_ioctl32_conversion
)paren
suffix:semicolon
DECL|variable|unregister_ioctl32_conversion
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_ioctl32_conversion
)paren
suffix:semicolon
DECL|variable|isa_io_base
id|EXPORT_SYMBOL
c_func
(paren
id|isa_io_base
)paren
suffix:semicolon
DECL|variable|pci_io_base
id|EXPORT_SYMBOL
c_func
(paren
id|pci_io_base
)paren
suffix:semicolon
DECL|variable|find_next_zero_bit
id|EXPORT_SYMBOL
c_func
(paren
id|find_next_zero_bit
)paren
suffix:semicolon
DECL|variable|find_next_zero_le_bit
id|EXPORT_SYMBOL
c_func
(paren
id|find_next_zero_le_bit
)paren
suffix:semicolon
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
DECL|variable|__down_interruptible
id|EXPORT_SYMBOL
c_func
(paren
id|__down_interruptible
)paren
suffix:semicolon
DECL|variable|__up
id|EXPORT_SYMBOL
c_func
(paren
id|__up
)paren
suffix:semicolon
DECL|variable|naca
id|EXPORT_SYMBOL
c_func
(paren
id|naca
)paren
suffix:semicolon
DECL|variable|__down
id|EXPORT_SYMBOL
c_func
(paren
id|__down
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
macro_line|#ifdef CONFIG_MSCHUNKS
DECL|variable|msChunks
id|EXPORT_SYMBOL
c_func
(paren
id|msChunks
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|reloc_offset
id|EXPORT_SYMBOL
c_func
(paren
id|reloc_offset
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_ISERIES
DECL|variable|iSeries_proc_callback
id|EXPORT_SYMBOL
c_func
(paren
id|iSeries_proc_callback
)paren
suffix:semicolon
DECL|variable|HvCall0
id|EXPORT_SYMBOL
c_func
(paren
id|HvCall0
)paren
suffix:semicolon
DECL|variable|HvCall1
id|EXPORT_SYMBOL
c_func
(paren
id|HvCall1
)paren
suffix:semicolon
DECL|variable|HvCall2
id|EXPORT_SYMBOL
c_func
(paren
id|HvCall2
)paren
suffix:semicolon
DECL|variable|HvCall3
id|EXPORT_SYMBOL
c_func
(paren
id|HvCall3
)paren
suffix:semicolon
DECL|variable|HvCall4
id|EXPORT_SYMBOL
c_func
(paren
id|HvCall4
)paren
suffix:semicolon
DECL|variable|HvCall5
id|EXPORT_SYMBOL
c_func
(paren
id|HvCall5
)paren
suffix:semicolon
DECL|variable|HvCall6
id|EXPORT_SYMBOL
c_func
(paren
id|HvCall6
)paren
suffix:semicolon
DECL|variable|HvCall7
id|EXPORT_SYMBOL
c_func
(paren
id|HvCall7
)paren
suffix:semicolon
DECL|variable|HvLpEvent_unregisterHandler
id|EXPORT_SYMBOL
c_func
(paren
id|HvLpEvent_unregisterHandler
)paren
suffix:semicolon
DECL|variable|HvLpEvent_registerHandler
id|EXPORT_SYMBOL
c_func
(paren
id|HvLpEvent_registerHandler
)paren
suffix:semicolon
DECL|variable|mf_allocateLpEvents
id|EXPORT_SYMBOL
c_func
(paren
id|mf_allocateLpEvents
)paren
suffix:semicolon
DECL|variable|mf_deallocateLpEvents
id|EXPORT_SYMBOL
c_func
(paren
id|mf_deallocateLpEvents
)paren
suffix:semicolon
DECL|variable|HvLpConfig_getLpIndex_outline
id|EXPORT_SYMBOL
c_func
(paren
id|HvLpConfig_getLpIndex_outline
)paren
suffix:semicolon
macro_line|#endif
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
DECL|variable|pci_unmap_single
id|EXPORT_SYMBOL
c_func
(paren
id|pci_unmap_single
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
macro_line|#ifdef CONFIG_PPC_ISERIES
DECL|variable|iSeries_GetLocationData
id|EXPORT_SYMBOL
c_func
(paren
id|iSeries_GetLocationData
)paren
suffix:semicolon
DECL|variable|iSeries_Device_ToggleReset
id|EXPORT_SYMBOL
c_func
(paren
id|iSeries_Device_ToggleReset
)paren
suffix:semicolon
DECL|variable|iSeries_memset_io
id|EXPORT_SYMBOL
c_func
(paren
id|iSeries_memset_io
)paren
suffix:semicolon
DECL|variable|iSeries_memcpy_toio
id|EXPORT_SYMBOL
c_func
(paren
id|iSeries_memcpy_toio
)paren
suffix:semicolon
DECL|variable|iSeries_memcpy_fromio
id|EXPORT_SYMBOL
c_func
(paren
id|iSeries_memcpy_fromio
)paren
suffix:semicolon
DECL|variable|iSeries_Read_Byte
id|EXPORT_SYMBOL
c_func
(paren
id|iSeries_Read_Byte
)paren
suffix:semicolon
DECL|variable|iSeries_Read_Word
id|EXPORT_SYMBOL
c_func
(paren
id|iSeries_Read_Word
)paren
suffix:semicolon
DECL|variable|iSeries_Read_Long
id|EXPORT_SYMBOL
c_func
(paren
id|iSeries_Read_Long
)paren
suffix:semicolon
DECL|variable|iSeries_Write_Byte
id|EXPORT_SYMBOL
c_func
(paren
id|iSeries_Write_Byte
)paren
suffix:semicolon
DECL|variable|iSeries_Write_Word
id|EXPORT_SYMBOL
c_func
(paren
id|iSeries_Write_Word
)paren
suffix:semicolon
DECL|variable|iSeries_Write_Long
id|EXPORT_SYMBOL
c_func
(paren
id|iSeries_Write_Long
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PPC_ISERIES */
macro_line|#ifndef CONFIG_PPC_ISERIES
DECL|variable|eeh_check_failure
id|EXPORT_SYMBOL
c_func
(paren
id|eeh_check_failure
)paren
suffix:semicolon
DECL|variable|eeh_total_mmio_ffs
id|EXPORT_SYMBOL
c_func
(paren
id|eeh_total_mmio_ffs
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PPC_ISERIES */
macro_line|#endif /* CONFIG_PCI */
DECL|variable|iSeries_veth_dev
id|EXPORT_SYMBOL
c_func
(paren
id|iSeries_veth_dev
)paren
suffix:semicolon
DECL|variable|iSeries_vio_dev
id|EXPORT_SYMBOL
c_func
(paren
id|iSeries_vio_dev
)paren
suffix:semicolon
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
DECL|variable|_get_PVR
id|EXPORT_SYMBOL
c_func
(paren
id|_get_PVR
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
DECL|variable|flush_icache_user_range
id|EXPORT_SYMBOL
c_func
(paren
id|flush_icache_user_range
)paren
suffix:semicolon
DECL|variable|flush_dcache_page
id|EXPORT_SYMBOL
c_func
(paren
id|flush_dcache_page
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
macro_line|#ifdef CONFIG_PPC_ISERIES
DECL|variable|__no_use_restore_flags
id|EXPORT_SYMBOL
c_func
(paren
id|__no_use_restore_flags
)paren
suffix:semicolon
DECL|variable|__no_use_save_flags
id|EXPORT_SYMBOL
c_func
(paren
id|__no_use_save_flags
)paren
suffix:semicolon
DECL|variable|__no_use_sti
id|EXPORT_SYMBOL
c_func
(paren
id|__no_use_sti
)paren
suffix:semicolon
DECL|variable|__no_use_cli
id|EXPORT_SYMBOL
c_func
(paren
id|__no_use_cli
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
DECL|variable|ppc_md
id|EXPORT_SYMBOL
c_func
(paren
id|ppc_md
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
DECL|variable|abs
id|EXPORT_SYMBOL
c_func
(paren
id|abs
)paren
suffix:semicolon
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
DECL|variable|xmon
id|EXPORT_SYMBOL
c_func
(paren
id|xmon
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DEBUG_KERNEL
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
DECL|variable|tb_ticks_per_usec
id|EXPORT_SYMBOL
c_func
(paren
id|tb_ticks_per_usec
)paren
suffix:semicolon
eof
