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
macro_line|#include &lt;linux/syscalls.h&gt;
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
macro_line|#include &lt;asm/iSeries/HvCallSc.h&gt;
macro_line|#include &lt;asm/iSeries/LparData.h&gt;
macro_line|#endif
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
r_int
id|abs
c_func
(paren
r_int
)paren
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
macro_line|#ifdef CONFIG_PPC_ISERIES
DECL|variable|itLpNaca
id|EXPORT_SYMBOL
c_func
(paren
id|itLpNaca
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
DECL|variable|clear_user_page
id|EXPORT_SYMBOL
c_func
(paren
id|clear_user_page
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
macro_line|#ifdef CONFIG_ALTIVEC
DECL|variable|giveup_altivec
id|EXPORT_SYMBOL
c_func
(paren
id|giveup_altivec
)paren
suffix:semicolon
macro_line|#endif
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
DECL|variable|local_get_flags
id|EXPORT_SYMBOL
c_func
(paren
id|local_get_flags
)paren
suffix:semicolon
DECL|variable|local_irq_disable
id|EXPORT_SYMBOL
c_func
(paren
id|local_irq_disable
)paren
suffix:semicolon
DECL|variable|local_irq_restore
id|EXPORT_SYMBOL
c_func
(paren
id|local_irq_restore
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
macro_line|#ifdef CONFIG_PPC_PSERIES
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
macro_line|#endif
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
DECL|variable|tb_ticks_per_usec
id|EXPORT_SYMBOL
c_func
(paren
id|tb_ticks_per_usec
)paren
suffix:semicolon
DECL|variable|paca
id|EXPORT_SYMBOL
c_func
(paren
id|paca
)paren
suffix:semicolon
DECL|variable|cur_cpu_spec
id|EXPORT_SYMBOL
c_func
(paren
id|cur_cpu_spec
)paren
suffix:semicolon
DECL|variable|systemcfg
id|EXPORT_SYMBOL
c_func
(paren
id|systemcfg
)paren
suffix:semicolon
eof
