macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC64_MACHDEP_H
DECL|macro|_PPC64_MACHDEP_H
mdefine_line|#define _PPC64_MACHDEP_H
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
r_struct
id|pt_regs
suffix:semicolon
r_struct
id|pci_bus
suffix:semicolon
r_struct
id|device_node
suffix:semicolon
r_struct
id|iommu_table
suffix:semicolon
r_struct
id|rtc_time
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|struct|smp_ops_t
r_struct
id|smp_ops_t
(brace
DECL|member|message_pass
r_void
(paren
op_star
id|message_pass
)paren
(paren
r_int
id|target
comma
r_int
id|msg
)paren
suffix:semicolon
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|kick_cpu
r_void
(paren
op_star
id|kick_cpu
)paren
(paren
r_int
id|nr
)paren
suffix:semicolon
DECL|member|setup_cpu
r_void
(paren
op_star
id|setup_cpu
)paren
(paren
r_int
id|nr
)paren
suffix:semicolon
DECL|member|take_timebase
r_void
(paren
op_star
id|take_timebase
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|give_timebase
r_void
(paren
op_star
id|give_timebase
)paren
(paren
r_void
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
DECL|struct|machdep_calls
r_struct
id|machdep_calls
(brace
DECL|member|hpte_invalidate
r_void
(paren
op_star
id|hpte_invalidate
)paren
(paren
r_int
r_int
id|slot
comma
r_int
r_int
id|va
comma
r_int
id|large
comma
r_int
id|local
)paren
suffix:semicolon
DECL|member|hpte_updatepp
r_int
(paren
op_star
id|hpte_updatepp
)paren
(paren
r_int
r_int
id|slot
comma
r_int
r_int
id|newpp
comma
r_int
r_int
id|va
comma
r_int
id|large
comma
r_int
id|local
)paren
suffix:semicolon
DECL|member|hpte_updateboltedpp
r_void
(paren
op_star
id|hpte_updateboltedpp
)paren
(paren
r_int
r_int
id|newpp
comma
r_int
r_int
id|ea
)paren
suffix:semicolon
DECL|member|hpte_insert
r_int
(paren
op_star
id|hpte_insert
)paren
(paren
r_int
r_int
id|hpte_group
comma
r_int
r_int
id|va
comma
r_int
r_int
id|prpn
comma
r_int
id|secondary
comma
r_int
r_int
id|hpteflags
comma
r_int
id|bolted
comma
r_int
id|large
)paren
suffix:semicolon
DECL|member|hpte_remove
r_int
(paren
op_star
id|hpte_remove
)paren
(paren
r_int
r_int
id|hpte_group
)paren
suffix:semicolon
DECL|member|flush_hash_range
r_void
(paren
op_star
id|flush_hash_range
)paren
(paren
r_int
r_int
id|context
comma
r_int
r_int
id|number
comma
r_int
id|local
)paren
suffix:semicolon
DECL|member|tce_build
r_void
(paren
op_star
id|tce_build
)paren
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
r_int
id|index
comma
r_int
id|npages
comma
r_int
r_int
id|uaddr
comma
r_int
id|direction
)paren
suffix:semicolon
DECL|member|tce_free
r_void
(paren
op_star
id|tce_free
)paren
(paren
r_struct
id|iommu_table
op_star
id|tbl
comma
r_int
id|index
comma
r_int
id|npages
)paren
suffix:semicolon
DECL|member|tce_flush
r_void
(paren
op_star
id|tce_flush
)paren
(paren
r_struct
id|iommu_table
op_star
id|tbl
)paren
suffix:semicolon
DECL|member|setup_arch
r_void
(paren
op_star
id|setup_arch
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Optional, may be NULL. */
DECL|member|get_cpuinfo
r_void
(paren
op_star
id|get_cpuinfo
)paren
(paren
r_struct
id|seq_file
op_star
id|m
)paren
suffix:semicolon
DECL|member|init_IRQ
r_void
(paren
op_star
id|init_IRQ
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|get_irq
r_int
(paren
op_star
id|get_irq
)paren
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
multiline_comment|/* PCI stuff */
DECL|member|pcibios_fixup
r_void
(paren
op_star
id|pcibios_fixup
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Optional, may be NULL. */
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|restart
r_void
(paren
op_star
id|restart
)paren
(paren
r_char
op_star
id|cmd
)paren
suffix:semicolon
DECL|member|power_off
r_void
(paren
op_star
id|power_off
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|halt
r_void
(paren
op_star
id|halt
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|set_rtc_time
r_int
(paren
op_star
id|set_rtc_time
)paren
(paren
r_struct
id|rtc_time
op_star
)paren
suffix:semicolon
DECL|member|get_rtc_time
r_void
(paren
op_star
id|get_rtc_time
)paren
(paren
r_struct
id|rtc_time
op_star
)paren
suffix:semicolon
DECL|member|get_boot_time
r_void
(paren
op_star
id|get_boot_time
)paren
(paren
r_struct
id|rtc_time
op_star
)paren
suffix:semicolon
DECL|member|calibrate_decr
r_void
(paren
op_star
id|calibrate_decr
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|progress
r_void
(paren
op_star
id|progress
)paren
(paren
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* Debug interface.  Low level I/O to some terminal device */
DECL|member|udbg_putc
r_void
(paren
op_star
id|udbg_putc
)paren
(paren
r_int
r_char
id|c
)paren
suffix:semicolon
DECL|member|udbg_getc
r_int
r_char
(paren
op_star
id|udbg_getc
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|udbg_getc_poll
r_int
(paren
op_star
id|udbg_getc_poll
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Interface for platform error logging */
DECL|member|log_error
r_void
(paren
op_star
id|log_error
)paren
(paren
r_char
op_star
id|buf
comma
r_int
r_int
id|err_type
comma
r_int
id|fatal
)paren
suffix:semicolon
DECL|member|nvram_write
id|ssize_t
(paren
op_star
id|nvram_write
)paren
(paren
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|index
)paren
suffix:semicolon
DECL|member|nvram_read
id|ssize_t
(paren
op_star
id|nvram_read
)paren
(paren
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|index
)paren
suffix:semicolon
DECL|member|nvram_size
id|ssize_t
(paren
op_star
id|nvram_size
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|nvram_sync
r_int
(paren
op_star
id|nvram_sync
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Motherboard/chipset features. This is a kind of general purpose&n;&t; * hook used to control some machine specific features (like reset&n;&t; * lines, chip power control, etc...).&n;&t; */
DECL|member|feature_call
r_int
(paren
op_star
id|feature_call
)paren
(paren
r_int
r_int
id|feature
comma
dot
dot
dot
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|machdep_calls
id|ppc_md
suffix:semicolon
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE 512
r_extern
r_char
id|cmd_line
(braket
id|COMMAND_LINE_SIZE
)braket
suffix:semicolon
r_extern
r_char
id|saved_command_line
(braket
id|COMMAND_LINE_SIZE
)braket
suffix:semicolon
multiline_comment|/* Functions to produce codes on the leds.&n; * The SRC code should be unique for the message category and should&n; * be limited to the lower 24 bits (the upper 8 are set by these funcs),&n; * and (for boot &amp; dump) should be sorted numerically in the order&n; * the events occur.&n; */
multiline_comment|/* Print a boot progress message. */
r_void
id|ppc64_boot_msg
c_func
(paren
r_int
r_int
id|src
comma
r_const
r_char
op_star
id|msg
)paren
suffix:semicolon
multiline_comment|/* Print a termination message (print only -- does not stop the kernel) */
r_void
id|ppc64_terminate_msg
c_func
(paren
r_int
r_int
id|src
comma
r_const
r_char
op_star
id|msg
)paren
suffix:semicolon
multiline_comment|/* Print something that needs attention (device error, etc) */
r_void
id|ppc64_attention_msg
c_func
(paren
r_int
r_int
id|src
comma
r_const
r_char
op_star
id|msg
)paren
suffix:semicolon
multiline_comment|/* Print a dump progress message. */
r_void
id|ppc64_dump_msg
c_func
(paren
r_int
r_int
id|src
comma
r_const
r_char
op_star
id|msg
)paren
suffix:semicolon
DECL|function|log_error
r_static
r_inline
r_void
id|log_error
c_func
(paren
r_char
op_star
id|buf
comma
r_int
r_int
id|err_type
comma
r_int
id|fatal
)paren
(brace
r_if
c_cond
(paren
id|ppc_md.log_error
)paren
id|ppc_md
dot
id|log_error
c_func
(paren
id|buf
comma
id|err_type
comma
id|fatal
)paren
suffix:semicolon
)brace
macro_line|#endif /* _PPC64_MACHDEP_H */
macro_line|#endif /* __KERNEL__ */
eof
