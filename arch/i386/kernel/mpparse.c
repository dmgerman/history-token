multiline_comment|/*&n; *&t;Intel Multiprocessor Specificiation 1.1 and 1.4&n; *&t;compliant MP-table parsing routines.&n; *&n; *&t;(c) 1995 Alan Cox, Building #3 &lt;alan@redhat.com&gt;&n; *&t;(c) 1998, 1999, 2000 Ingo Molnar &lt;mingo@redhat.com&gt;&n; *&n; *&t;Fixes&n; *&t;&t;Erich Boleyn&t;:&t;MP v1.4 and additional changes.&n; *&t;&t;Alan Cox&t;:&t;Added EBDA scanning&n; *&t;&t;Ingo Molnar&t;:&t;various cleanups and rewrites&n; *&t;Maciej W. Rozycki&t;:&t;Bits for default MP configurations&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/mtrr.h&gt;
macro_line|#include &lt;asm/mpspec.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
multiline_comment|/* Have we found an MP table */
DECL|variable|smp_found_config
r_int
id|smp_found_config
suffix:semicolon
multiline_comment|/*&n; * Various Linux-internal data structures created from the&n; * MP-table.&n; */
DECL|variable|apic_version
r_int
id|apic_version
(braket
id|MAX_APICS
)braket
suffix:semicolon
DECL|variable|mp_bus_id_to_type
r_int
id|mp_bus_id_to_type
(braket
id|MAX_MP_BUSSES
)braket
suffix:semicolon
DECL|variable|mp_bus_id_to_pci_bus
r_int
id|mp_bus_id_to_pci_bus
(braket
id|MAX_MP_BUSSES
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
id|MAX_MP_BUSSES
op_minus
l_int|1
)braket
op_assign
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|mp_current_pci_id
r_int
id|mp_current_pci_id
suffix:semicolon
multiline_comment|/* I/O APIC entries */
DECL|variable|mp_ioapics
r_struct
id|mpc_config_ioapic
id|mp_ioapics
(braket
id|MAX_IO_APICS
)braket
suffix:semicolon
multiline_comment|/* # of MP IRQ source entries */
DECL|variable|mp_irqs
r_struct
id|mpc_config_intsrc
id|mp_irqs
(braket
id|MAX_IRQ_SOURCES
)braket
suffix:semicolon
multiline_comment|/* MP IRQ source entries */
DECL|variable|mp_irq_entries
r_int
id|mp_irq_entries
suffix:semicolon
DECL|variable|nr_ioapics
r_int
id|nr_ioapics
suffix:semicolon
DECL|variable|pic_mode
r_int
id|pic_mode
suffix:semicolon
DECL|variable|mp_lapic_addr
r_int
r_int
id|mp_lapic_addr
suffix:semicolon
multiline_comment|/* Processor that is doing the boot up */
DECL|variable|boot_cpu_id
r_int
r_int
id|boot_cpu_id
op_assign
op_minus
l_int|1U
suffix:semicolon
multiline_comment|/* Internal processor count */
DECL|variable|num_processors
r_static
r_int
r_int
id|num_processors
suffix:semicolon
multiline_comment|/* Bitmask of physically existing CPUs */
DECL|variable|phys_cpu_present_map
r_int
r_int
id|phys_cpu_present_map
suffix:semicolon
multiline_comment|/*&n; * Intel MP BIOS table parsing routines:&n; */
macro_line|#ifndef CONFIG_X86_VISWS_APIC
multiline_comment|/*&n; * Checksum an MP configuration block.&n; */
DECL|function|mpf_checksum
r_static
r_int
id|__init
id|mpf_checksum
c_func
(paren
r_int
r_char
op_star
id|mp
comma
r_int
id|len
)paren
(brace
r_int
id|sum
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
id|sum
op_add_assign
op_star
id|mp
op_increment
suffix:semicolon
r_return
id|sum
op_amp
l_int|0xFF
suffix:semicolon
)brace
multiline_comment|/*&n; * Processor encoding in an MP configuration block&n; */
DECL|function|mpc_family
r_static
r_char
id|__init
op_star
id|mpc_family
c_func
(paren
r_int
id|family
comma
r_int
id|model
)paren
(brace
r_static
r_char
id|n
(braket
l_int|32
)braket
suffix:semicolon
r_static
r_char
op_star
id|model_defs
(braket
)braket
op_assign
(brace
l_string|&quot;80486DX&quot;
comma
l_string|&quot;80486DX&quot;
comma
l_string|&quot;80486SX&quot;
comma
l_string|&quot;80486DX/2 or 80487&quot;
comma
l_string|&quot;80486SL&quot;
comma
l_string|&quot;80486SX/2&quot;
comma
l_string|&quot;Unknown&quot;
comma
l_string|&quot;80486DX/2-WB&quot;
comma
l_string|&quot;80486DX/4&quot;
comma
l_string|&quot;80486DX/4-WB&quot;
)brace
suffix:semicolon
r_switch
c_cond
(paren
id|family
)paren
(brace
r_case
l_int|0x04
suffix:colon
r_if
c_cond
(paren
id|model
OL
l_int|10
)paren
r_return
id|model_defs
(braket
id|model
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x05
suffix:colon
r_return
l_string|&quot;Pentium(tm)&quot;
suffix:semicolon
r_case
l_int|0x06
suffix:colon
r_return
l_string|&quot;Pentium(tm) Pro&quot;
suffix:semicolon
r_case
l_int|0x0F
suffix:colon
r_if
c_cond
(paren
id|model
op_eq
l_int|0x00
)paren
r_return
l_string|&quot;Pentium 4(tm)&quot;
suffix:semicolon
r_if
c_cond
(paren
id|model
op_eq
l_int|0x0F
)paren
r_return
l_string|&quot;Special controller&quot;
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|n
comma
l_string|&quot;Unknown CPU [%d:%d]&quot;
comma
id|family
comma
id|model
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|function|MP_processor_info
r_static
r_void
id|__init
id|MP_processor_info
(paren
r_struct
id|mpc_config_processor
op_star
id|m
)paren
(brace
r_int
id|ver
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|m-&gt;mpc_cpuflag
op_amp
id|CPU_ENABLED
)paren
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Processor #%d %s APIC version %d&bslash;n&quot;
comma
id|m-&gt;mpc_apicid
comma
id|mpc_family
c_func
(paren
(paren
id|m-&gt;mpc_cpufeature
op_amp
id|CPU_FAMILY_MASK
)paren
op_rshift
l_int|8
comma
(paren
id|m-&gt;mpc_cpufeature
op_amp
id|CPU_MODEL_MASK
)paren
op_rshift
l_int|4
)paren
comma
id|m-&gt;mpc_apicver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|0
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    Floating point unit present.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|7
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    Machine Exception supported.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|8
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    64 bit compare &amp; exchange supported.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|9
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    Internal APIC present.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|11
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    SEP present.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|12
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    MTRR  present.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|13
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    PGE  present.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|14
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    MCA  present.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|15
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    CMOV  present.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|16
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    PAT  present.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|17
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    PSE  present.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|18
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    PSN  present.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|19
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    Cache Line Flush Instruction present.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* 20 Reserved */
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|21
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    Debug Trace and EMON Store present.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|22
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    ACPI Thermal Throttle Registers  present.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|23
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    MMX  present.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|24
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    FXSR  present.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|25
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    XMM  present.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|26
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    Willamette New Instructions  present.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|27
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    Self Snoop  present.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* 28 Reserved */
r_if
c_cond
(paren
id|m-&gt;mpc_featureflag
op_amp
(paren
l_int|1
op_lshift
l_int|29
)paren
)paren
id|Dprintk
c_func
(paren
l_string|&quot;    Thermal Monitor present.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* 30, 31 Reserved */
r_if
c_cond
(paren
id|m-&gt;mpc_cpuflag
op_amp
id|CPU_BOOTPROCESSOR
)paren
(brace
id|Dprintk
c_func
(paren
l_string|&quot;    Bootup CPU&bslash;n&quot;
)paren
suffix:semicolon
id|boot_cpu_id
op_assign
id|m-&gt;mpc_apicid
suffix:semicolon
)brace
id|num_processors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;mpc_apicid
OG
id|MAX_APICS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Processor #%d INVALID. (Max ID: %d).&bslash;n&quot;
comma
id|m-&gt;mpc_apicid
comma
id|MAX_APICS
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ver
op_assign
id|m-&gt;mpc_apicver
suffix:semicolon
id|phys_cpu_present_map
op_or_assign
l_int|1
op_lshift
id|m-&gt;mpc_apicid
suffix:semicolon
multiline_comment|/*&n;&t; * Validate version&n;&t; */
r_if
c_cond
(paren
id|ver
op_eq
l_int|0x0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;BIOS bug, APIC version is 0 for CPU#%d! fixing up to 0x10. (tell your hw vendor)&bslash;n&quot;
comma
id|m-&gt;mpc_apicid
)paren
suffix:semicolon
id|ver
op_assign
l_int|0x10
suffix:semicolon
)brace
id|apic_version
(braket
id|m-&gt;mpc_apicid
)braket
op_assign
id|ver
suffix:semicolon
)brace
DECL|function|MP_bus_info
r_static
r_void
id|__init
id|MP_bus_info
(paren
r_struct
id|mpc_config_bus
op_star
id|m
)paren
(brace
r_char
id|str
(braket
l_int|7
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|str
comma
id|m-&gt;mpc_bustype
comma
l_int|6
)paren
suffix:semicolon
id|str
(braket
l_int|6
)braket
op_assign
l_int|0
suffix:semicolon
id|Dprintk
c_func
(paren
l_string|&quot;Bus #%d is %s&bslash;n&quot;
comma
id|m-&gt;mpc_busid
comma
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
id|BUSTYPE_ISA
comma
r_sizeof
(paren
id|BUSTYPE_ISA
)paren
op_minus
l_int|1
)paren
op_eq
l_int|0
)paren
(brace
id|mp_bus_id_to_type
(braket
id|m-&gt;mpc_busid
)braket
op_assign
id|MP_BUS_ISA
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
id|BUSTYPE_EISA
comma
r_sizeof
(paren
id|BUSTYPE_EISA
)paren
op_minus
l_int|1
)paren
op_eq
l_int|0
)paren
(brace
id|mp_bus_id_to_type
(braket
id|m-&gt;mpc_busid
)braket
op_assign
id|MP_BUS_EISA
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
id|BUSTYPE_PCI
comma
r_sizeof
(paren
id|BUSTYPE_PCI
)paren
op_minus
l_int|1
)paren
op_eq
l_int|0
)paren
(brace
id|mp_bus_id_to_type
(braket
id|m-&gt;mpc_busid
)braket
op_assign
id|MP_BUS_PCI
suffix:semicolon
id|mp_bus_id_to_pci_bus
(braket
id|m-&gt;mpc_busid
)braket
op_assign
id|mp_current_pci_id
suffix:semicolon
id|mp_current_pci_id
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
id|BUSTYPE_MCA
comma
r_sizeof
(paren
id|BUSTYPE_MCA
)paren
op_minus
l_int|1
)paren
op_eq
l_int|0
)paren
(brace
id|mp_bus_id_to_type
(braket
id|m-&gt;mpc_busid
)braket
op_assign
id|MP_BUS_MCA
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;Unknown bustype %s - ignoring&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
)brace
)brace
DECL|function|MP_ioapic_info
r_static
r_void
id|__init
id|MP_ioapic_info
(paren
r_struct
id|mpc_config_ioapic
op_star
id|m
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|m-&gt;mpc_flags
op_amp
id|MPC_APIC_USABLE
)paren
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;I/O APIC #%d Version %d at 0x%lX.&bslash;n&quot;
comma
id|m-&gt;mpc_apicid
comma
id|m-&gt;mpc_apicver
comma
id|m-&gt;mpc_apicaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr_ioapics
op_ge
id|MAX_IO_APICS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Max # of I/O APICs (%d) exceeded (found %d).&bslash;n&quot;
comma
id|MAX_IO_APICS
comma
id|nr_ioapics
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Recompile kernel with bigger MAX_IO_APICS!.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|m-&gt;mpc_apicaddr
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;WARNING: bogus zero I/O APIC address&quot;
l_string|&quot; found in MP table, skipping!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|mp_ioapics
(braket
id|nr_ioapics
)braket
op_assign
op_star
id|m
suffix:semicolon
id|nr_ioapics
op_increment
suffix:semicolon
)brace
DECL|function|MP_intsrc_info
r_static
r_void
id|__init
id|MP_intsrc_info
(paren
r_struct
id|mpc_config_intsrc
op_star
id|m
)paren
(brace
id|mp_irqs
(braket
id|mp_irq_entries
)braket
op_assign
op_star
id|m
suffix:semicolon
id|Dprintk
c_func
(paren
l_string|&quot;Int: type %d, pol %d, trig %d, bus %d,&quot;
l_string|&quot; IRQ %02x, APIC ID %x, APIC INT %02x&bslash;n&quot;
comma
id|m-&gt;mpc_irqtype
comma
id|m-&gt;mpc_irqflag
op_amp
l_int|3
comma
(paren
id|m-&gt;mpc_irqflag
op_rshift
l_int|2
)paren
op_amp
l_int|3
comma
id|m-&gt;mpc_srcbus
comma
id|m-&gt;mpc_srcbusirq
comma
id|m-&gt;mpc_dstapic
comma
id|m-&gt;mpc_dstirq
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|mp_irq_entries
op_eq
id|MAX_IRQ_SOURCES
)paren
id|panic
c_func
(paren
l_string|&quot;Max # of irq sources exceeded!!&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|MP_lintsrc_info
r_static
r_void
id|__init
id|MP_lintsrc_info
(paren
r_struct
id|mpc_config_lintsrc
op_star
id|m
)paren
(brace
id|Dprintk
c_func
(paren
l_string|&quot;Lint: type %d, pol %d, trig %d, bus %d,&quot;
l_string|&quot; IRQ %02x, APIC ID %x, APIC LINT %02x&bslash;n&quot;
comma
id|m-&gt;mpc_irqtype
comma
id|m-&gt;mpc_irqflag
op_amp
l_int|3
comma
(paren
id|m-&gt;mpc_irqflag
op_rshift
l_int|2
)paren
op_amp
l_int|3
comma
id|m-&gt;mpc_srcbusid
comma
id|m-&gt;mpc_srcbusirq
comma
id|m-&gt;mpc_destapic
comma
id|m-&gt;mpc_destapiclint
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Well it seems all SMP boards in existence&n;&t; * use ExtINT/LVT1 == LINT0 and&n;&t; * NMI/LVT2 == LINT1 - the following check&n;&t; * will show us if this assumptions is false.&n;&t; * Until then we do not have to add baggage.&n;&t; */
r_if
c_cond
(paren
(paren
id|m-&gt;mpc_irqtype
op_eq
id|mp_ExtINT
)paren
op_logical_and
(paren
id|m-&gt;mpc_destapiclint
op_ne
l_int|0
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|m-&gt;mpc_irqtype
op_eq
id|mp_NMI
)paren
op_logical_and
(paren
id|m-&gt;mpc_destapiclint
op_ne
l_int|1
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read/parse the MPC&n; */
DECL|function|smp_read_mpc
r_static
r_int
id|__init
id|smp_read_mpc
c_func
(paren
r_struct
id|mp_config_table
op_star
id|mpc
)paren
(brace
r_char
id|str
(braket
l_int|16
)braket
suffix:semicolon
r_int
id|count
op_assign
r_sizeof
(paren
op_star
id|mpc
)paren
suffix:semicolon
r_int
r_char
op_star
id|mpt
op_assign
(paren
(paren
r_int
r_char
op_star
)paren
id|mpc
)paren
op_plus
id|count
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|mpc-&gt;mpc_signature
comma
id|MPC_SIGNATURE
comma
l_int|4
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;SMP mptable: bad signature [%c%c%c%c]!&bslash;n&quot;
comma
id|mpc-&gt;mpc_signature
(braket
l_int|0
)braket
comma
id|mpc-&gt;mpc_signature
(braket
l_int|1
)braket
comma
id|mpc-&gt;mpc_signature
(braket
l_int|2
)braket
comma
id|mpc-&gt;mpc_signature
(braket
l_int|3
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mpf_checksum
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|mpc
comma
id|mpc-&gt;mpc_length
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;SMP mptable: checksum error!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mpc-&gt;mpc_spec
op_ne
l_int|0x01
op_logical_and
id|mpc-&gt;mpc_spec
op_ne
l_int|0x04
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SMP mptable: bad table version (%d)!!&bslash;n&quot;
comma
id|mpc-&gt;mpc_spec
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|mpc-&gt;mpc_lapic
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SMP mptable: null local APIC address!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|str
comma
id|mpc-&gt;mpc_oem
comma
l_int|8
)paren
suffix:semicolon
id|str
(braket
l_int|8
)braket
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;OEM ID: %s &quot;
comma
id|str
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|str
comma
id|mpc-&gt;mpc_productid
comma
l_int|12
)paren
suffix:semicolon
id|str
(braket
l_int|12
)braket
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Product ID: %s &quot;
comma
id|str
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;APIC at: 0x%lX&bslash;n&quot;
comma
id|mpc-&gt;mpc_lapic
)paren
suffix:semicolon
multiline_comment|/* save the local APIC address, it might be non-default */
id|mp_lapic_addr
op_assign
id|mpc-&gt;mpc_lapic
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Now process the configuration blocks.&n;&t; */
r_while
c_loop
(paren
id|count
OL
id|mpc-&gt;mpc_length
)paren
(brace
r_switch
c_cond
(paren
op_star
id|mpt
)paren
(brace
r_case
id|MP_PROCESSOR
suffix:colon
(brace
r_struct
id|mpc_config_processor
op_star
id|m
op_assign
(paren
r_struct
id|mpc_config_processor
op_star
)paren
id|mpt
suffix:semicolon
id|MP_processor_info
c_func
(paren
id|m
)paren
suffix:semicolon
id|mpt
op_add_assign
r_sizeof
(paren
op_star
id|m
)paren
suffix:semicolon
id|count
op_add_assign
r_sizeof
(paren
op_star
id|m
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|MP_BUS
suffix:colon
(brace
r_struct
id|mpc_config_bus
op_star
id|m
op_assign
(paren
r_struct
id|mpc_config_bus
op_star
)paren
id|mpt
suffix:semicolon
id|MP_bus_info
c_func
(paren
id|m
)paren
suffix:semicolon
id|mpt
op_add_assign
r_sizeof
(paren
op_star
id|m
)paren
suffix:semicolon
id|count
op_add_assign
r_sizeof
(paren
op_star
id|m
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|MP_IOAPIC
suffix:colon
(brace
r_struct
id|mpc_config_ioapic
op_star
id|m
op_assign
(paren
r_struct
id|mpc_config_ioapic
op_star
)paren
id|mpt
suffix:semicolon
id|MP_ioapic_info
c_func
(paren
id|m
)paren
suffix:semicolon
id|mpt
op_add_assign
r_sizeof
(paren
op_star
id|m
)paren
suffix:semicolon
id|count
op_add_assign
r_sizeof
(paren
op_star
id|m
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|MP_INTSRC
suffix:colon
(brace
r_struct
id|mpc_config_intsrc
op_star
id|m
op_assign
(paren
r_struct
id|mpc_config_intsrc
op_star
)paren
id|mpt
suffix:semicolon
id|MP_intsrc_info
c_func
(paren
id|m
)paren
suffix:semicolon
id|mpt
op_add_assign
r_sizeof
(paren
op_star
id|m
)paren
suffix:semicolon
id|count
op_add_assign
r_sizeof
(paren
op_star
id|m
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|MP_LINTSRC
suffix:colon
(brace
r_struct
id|mpc_config_lintsrc
op_star
id|m
op_assign
(paren
r_struct
id|mpc_config_lintsrc
op_star
)paren
id|mpt
suffix:semicolon
id|MP_lintsrc_info
c_func
(paren
id|m
)paren
suffix:semicolon
id|mpt
op_add_assign
r_sizeof
(paren
op_star
id|m
)paren
suffix:semicolon
id|count
op_add_assign
r_sizeof
(paren
op_star
id|m
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|num_processors
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SMP mptable: no processors registered!&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|num_processors
suffix:semicolon
)brace
DECL|function|ELCR_trigger
r_static
r_int
id|__init
id|ELCR_trigger
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|port
suffix:semicolon
id|port
op_assign
l_int|0x4d0
op_plus
(paren
id|irq
op_rshift
l_int|3
)paren
suffix:semicolon
r_return
(paren
id|inb
c_func
(paren
id|port
)paren
op_rshift
(paren
id|irq
op_amp
l_int|7
)paren
)paren
op_amp
l_int|1
suffix:semicolon
)brace
DECL|function|construct_default_ioirq_mptable
r_static
r_void
id|__init
id|construct_default_ioirq_mptable
c_func
(paren
r_int
id|mpc_default_type
)paren
(brace
r_struct
id|mpc_config_intsrc
id|intsrc
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|ELCR_fallback
op_assign
l_int|0
suffix:semicolon
id|intsrc.mpc_type
op_assign
id|MP_INTSRC
suffix:semicolon
id|intsrc.mpc_irqflag
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* conforming */
id|intsrc.mpc_srcbus
op_assign
l_int|0
suffix:semicolon
id|intsrc.mpc_dstapic
op_assign
id|mp_ioapics
(braket
l_int|0
)braket
dot
id|mpc_apicid
suffix:semicolon
id|intsrc.mpc_irqtype
op_assign
id|mp_INT
suffix:semicolon
multiline_comment|/*&n;&t; *  If true, we have an ISA/PCI system with no IRQ entries&n;&t; *  in the MP table. To prevent the PCI interrupts from being set up&n;&t; *  incorrectly, we try to use the ELCR. The sanity check to see if&n;&t; *  there is good ELCR data is very simple - IRQ0, 1, 2 and 13 can&n;&t; *  never be level sensitive, so we simply see if the ELCR agrees.&n;&t; *  If it does, we assume it&squot;s valid.&n;&t; */
r_if
c_cond
(paren
id|mpc_default_type
op_eq
l_int|5
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ISA/PCI bus type with no IRQ information... falling back to ELCR&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ELCR_trigger
c_func
(paren
l_int|0
)paren
op_logical_or
id|ELCR_trigger
c_func
(paren
l_int|1
)paren
op_logical_or
id|ELCR_trigger
c_func
(paren
l_int|2
)paren
op_logical_or
id|ELCR_trigger
c_func
(paren
l_int|13
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;ELCR contains invalid data... not using ELCR&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;Using ELCR to identify PCI interrupts&bslash;n&quot;
)paren
suffix:semicolon
id|ELCR_fallback
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
r_switch
c_cond
(paren
id|mpc_default_type
)paren
(brace
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
id|i
op_eq
l_int|0
op_logical_or
id|i
op_eq
l_int|13
)paren
r_continue
suffix:semicolon
multiline_comment|/* IRQ0 &amp; IRQ13 not connected */
multiline_comment|/* fall through */
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|2
)paren
r_continue
suffix:semicolon
multiline_comment|/* IRQ2 is never connected */
)brace
r_if
c_cond
(paren
id|ELCR_fallback
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; *  If the ELCR indicates a level-sensitive interrupt, we&n;&t;&t;&t; *  copy that information over to the MP table in the&n;&t;&t;&t; *  irqflag field (level sensitive, active high polarity).&n;&t;&t;&t; */
r_if
c_cond
(paren
id|ELCR_trigger
c_func
(paren
id|i
)paren
)paren
id|intsrc.mpc_irqflag
op_assign
l_int|13
suffix:semicolon
r_else
id|intsrc.mpc_irqflag
op_assign
l_int|0
suffix:semicolon
)brace
id|intsrc.mpc_srcbusirq
op_assign
id|i
suffix:semicolon
id|intsrc.mpc_dstirq
op_assign
id|i
ques
c_cond
id|i
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* IRQ0 to INTIN2 */
id|MP_intsrc_info
c_func
(paren
op_amp
id|intsrc
)paren
suffix:semicolon
)brace
id|intsrc.mpc_irqtype
op_assign
id|mp_ExtINT
suffix:semicolon
id|intsrc.mpc_srcbusirq
op_assign
l_int|0
suffix:semicolon
id|intsrc.mpc_dstirq
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* 8259A to INTIN0 */
id|MP_intsrc_info
c_func
(paren
op_amp
id|intsrc
)paren
suffix:semicolon
)brace
DECL|function|construct_default_ISA_mptable
r_static
r_inline
r_void
id|__init
id|construct_default_ISA_mptable
c_func
(paren
r_int
id|mpc_default_type
)paren
(brace
r_struct
id|mpc_config_processor
id|processor
suffix:semicolon
r_struct
id|mpc_config_bus
id|bus
suffix:semicolon
r_struct
id|mpc_config_ioapic
id|ioapic
suffix:semicolon
r_struct
id|mpc_config_lintsrc
id|lintsrc
suffix:semicolon
r_int
id|linttypes
(braket
l_int|2
)braket
op_assign
(brace
id|mp_ExtINT
comma
id|mp_NMI
)brace
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * local APIC has default address&n;&t; */
id|mp_lapic_addr
op_assign
id|APIC_DEFAULT_PHYS_BASE
suffix:semicolon
multiline_comment|/*&n;&t; * 2 CPUs, numbered 0 &amp; 1.&n;&t; */
id|processor.mpc_type
op_assign
id|MP_PROCESSOR
suffix:semicolon
multiline_comment|/* Either an integrated APIC or a discrete 82489DX. */
id|processor.mpc_apicver
op_assign
id|mpc_default_type
OG
l_int|4
ques
c_cond
l_int|0x10
suffix:colon
l_int|0x01
suffix:semicolon
id|processor.mpc_cpuflag
op_assign
id|CPU_ENABLED
suffix:semicolon
id|processor.mpc_cpufeature
op_assign
(paren
id|boot_cpu_data.x86
op_lshift
l_int|8
)paren
op_or
(paren
id|boot_cpu_data.x86_model
op_lshift
l_int|4
)paren
op_or
id|boot_cpu_data.x86_mask
suffix:semicolon
id|processor.mpc_featureflag
op_assign
id|boot_cpu_data.x86_capability
(braket
l_int|0
)braket
suffix:semicolon
id|processor.mpc_reserved
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|processor.mpc_reserved
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|processor.mpc_apicid
op_assign
id|i
suffix:semicolon
id|MP_processor_info
c_func
(paren
op_amp
id|processor
)paren
suffix:semicolon
)brace
id|bus.mpc_type
op_assign
id|MP_BUS
suffix:semicolon
id|bus.mpc_busid
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|mpc_default_type
)paren
(brace
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;???&bslash;nUnknown standard configuration %d&bslash;n&quot;
comma
id|mpc_default_type
)paren
suffix:semicolon
multiline_comment|/* fall through */
r_case
l_int|1
suffix:colon
r_case
l_int|5
suffix:colon
id|memcpy
c_func
(paren
id|bus.mpc_bustype
comma
l_string|&quot;ISA   &quot;
comma
l_int|6
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_case
l_int|6
suffix:colon
r_case
l_int|3
suffix:colon
id|memcpy
c_func
(paren
id|bus.mpc_bustype
comma
l_string|&quot;EISA  &quot;
comma
l_int|6
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
r_case
l_int|7
suffix:colon
id|memcpy
c_func
(paren
id|bus.mpc_bustype
comma
l_string|&quot;MCA   &quot;
comma
l_int|6
)paren
suffix:semicolon
)brace
id|MP_bus_info
c_func
(paren
op_amp
id|bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mpc_default_type
OG
l_int|4
)paren
(brace
id|bus.mpc_busid
op_assign
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|bus.mpc_bustype
comma
l_string|&quot;PCI   &quot;
comma
l_int|6
)paren
suffix:semicolon
id|MP_bus_info
c_func
(paren
op_amp
id|bus
)paren
suffix:semicolon
)brace
id|ioapic.mpc_type
op_assign
id|MP_IOAPIC
suffix:semicolon
id|ioapic.mpc_apicid
op_assign
l_int|2
suffix:semicolon
id|ioapic.mpc_apicver
op_assign
id|mpc_default_type
OG
l_int|4
ques
c_cond
l_int|0x10
suffix:colon
l_int|0x01
suffix:semicolon
id|ioapic.mpc_flags
op_assign
id|MPC_APIC_USABLE
suffix:semicolon
id|ioapic.mpc_apicaddr
op_assign
l_int|0xFEC00000
suffix:semicolon
id|MP_ioapic_info
c_func
(paren
op_amp
id|ioapic
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We set up most of the low 16 IO-APIC pins according to MPS rules.&n;&t; */
id|construct_default_ioirq_mptable
c_func
(paren
id|mpc_default_type
)paren
suffix:semicolon
id|lintsrc.mpc_type
op_assign
id|MP_LINTSRC
suffix:semicolon
id|lintsrc.mpc_irqflag
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* conforming */
id|lintsrc.mpc_srcbusid
op_assign
l_int|0
suffix:semicolon
id|lintsrc.mpc_srcbusirq
op_assign
l_int|0
suffix:semicolon
id|lintsrc.mpc_destapic
op_assign
id|MP_APIC_ALL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|lintsrc.mpc_irqtype
op_assign
id|linttypes
(braket
id|i
)braket
suffix:semicolon
id|lintsrc.mpc_destapiclint
op_assign
id|i
suffix:semicolon
id|MP_lintsrc_info
c_func
(paren
op_amp
id|lintsrc
)paren
suffix:semicolon
)brace
)brace
DECL|variable|mpf_found
r_static
r_struct
id|intel_mp_floating
op_star
id|mpf_found
suffix:semicolon
multiline_comment|/*&n; * Scan the memory blocks for an SMP configuration block.&n; */
DECL|function|get_smp_config
r_void
id|__init
id|get_smp_config
(paren
r_void
)paren
(brace
r_struct
id|intel_mp_floating
op_star
id|mpf
op_assign
id|mpf_found
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Intel MultiProcessor Specification v1.%d&bslash;n&quot;
comma
id|mpf-&gt;mpf_specification
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mpf-&gt;mpf_feature2
op_amp
(paren
l_int|1
op_lshift
l_int|7
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;    IMCR and PIC compatibility mode.&bslash;n&quot;
)paren
suffix:semicolon
id|pic_mode
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;    Virtual Wire compatibility mode.&bslash;n&quot;
)paren
suffix:semicolon
id|pic_mode
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Now see if we need to read further.&n;&t; */
r_if
c_cond
(paren
id|mpf-&gt;mpf_feature1
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Default MP configuration #%d&bslash;n&quot;
comma
id|mpf-&gt;mpf_feature1
)paren
suffix:semicolon
id|construct_default_ISA_mptable
c_func
(paren
id|mpf-&gt;mpf_feature1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|mpf-&gt;mpf_physptr
)paren
(brace
multiline_comment|/*&n;&t;&t; * Read the physical hardware table.  Anything here will&n;&t;&t; * override the defaults.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|smp_read_mpc
c_func
(paren
(paren
r_void
op_star
)paren
id|mpf-&gt;mpf_physptr
)paren
)paren
(brace
id|smp_found_config
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;BIOS bug, MP table errors detected!...&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;... disabling SMP support. (tell your hw vendor)&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * If there are no explicit MP IRQ entries, then we are&n;&t;&t; * broken.  We set up most of the low 16 IO-APIC pins to&n;&t;&t; * ISA defaults and hope it will work.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|mp_irq_entries
)paren
(brace
r_struct
id|mpc_config_bus
id|bus
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;BIOS bug, no explicit IRQ entries, using default mptable. (tell your hw vendor)&bslash;n&quot;
)paren
suffix:semicolon
id|bus.mpc_type
op_assign
id|MP_BUS
suffix:semicolon
id|bus.mpc_busid
op_assign
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
id|bus.mpc_bustype
comma
l_string|&quot;ISA   &quot;
comma
l_int|6
)paren
suffix:semicolon
id|MP_bus_info
c_func
(paren
op_amp
id|bus
)paren
suffix:semicolon
id|construct_default_ioirq_mptable
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_else
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Processors: %d&bslash;n&quot;
comma
id|num_processors
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Only use the first configuration found.&n;&t; */
)brace
DECL|function|smp_scan_config
r_static
r_int
id|__init
id|smp_scan_config
(paren
r_int
r_int
id|base
comma
r_int
r_int
id|length
)paren
(brace
r_int
r_int
op_star
id|bp
op_assign
id|phys_to_virt
c_func
(paren
id|base
)paren
suffix:semicolon
r_struct
id|intel_mp_floating
op_star
id|mpf
suffix:semicolon
id|Dprintk
c_func
(paren
l_string|&quot;Scan SMP from %p for %ld bytes.&bslash;n&quot;
comma
id|bp
comma
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
r_sizeof
(paren
op_star
id|mpf
)paren
op_ne
l_int|16
)paren
id|printk
c_func
(paren
l_string|&quot;Error: MPF size&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|length
OG
l_int|0
)paren
(brace
id|mpf
op_assign
(paren
r_struct
id|intel_mp_floating
op_star
)paren
id|bp
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|bp
op_eq
id|SMP_MAGIC_IDENT
)paren
op_logical_and
(paren
id|mpf-&gt;mpf_length
op_eq
l_int|1
)paren
op_logical_and
op_logical_neg
id|mpf_checksum
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|bp
comma
l_int|16
)paren
op_logical_and
(paren
(paren
id|mpf-&gt;mpf_specification
op_eq
l_int|1
)paren
op_logical_or
(paren
id|mpf-&gt;mpf_specification
op_eq
l_int|4
)paren
)paren
)paren
(brace
id|smp_found_config
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;found SMP MP-table at %08lx&bslash;n&quot;
comma
id|virt_to_phys
c_func
(paren
id|mpf
)paren
)paren
suffix:semicolon
id|reserve_bootmem
c_func
(paren
id|virt_to_phys
c_func
(paren
id|mpf
)paren
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mpf-&gt;mpf_physptr
)paren
id|reserve_bootmem
c_func
(paren
id|mpf-&gt;mpf_physptr
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|mpf_found
op_assign
id|mpf
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|bp
op_add_assign
l_int|4
suffix:semicolon
id|length
op_sub_assign
l_int|16
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|find_intel_smp
r_void
id|__init
id|find_intel_smp
(paren
r_void
)paren
(brace
r_int
r_int
id|address
suffix:semicolon
multiline_comment|/*&n;&t; * FIXME: Linux assumes you have 640K of base ram..&n;&t; * this continues the error...&n;&t; *&n;&t; * 1) Scan the bottom 1K for a signature&n;&t; * 2) Scan the top 1K of base RAM&n;&t; * 3) Scan the 64K of bios&n;&t; */
r_if
c_cond
(paren
id|smp_scan_config
c_func
(paren
l_int|0x0
comma
l_int|0x400
)paren
op_logical_or
id|smp_scan_config
c_func
(paren
l_int|639
op_star
l_int|0x400
comma
l_int|0x400
)paren
op_logical_or
id|smp_scan_config
c_func
(paren
l_int|0xF0000
comma
l_int|0x10000
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * If it is an SMP machine we should know now, unless the&n;&t; * configuration is in an EISA/MCA bus machine with an&n;&t; * extended bios data area.&n;&t; *&n;&t; * there is a real-mode segmented pointer pointing to the&n;&t; * 4K EBDA area at 0x40E, calculate and scan it here.&n;&t; *&n;&t; * NOTE! There are Linux loaders that will corrupt the EBDA&n;&t; * area, and as such this kind of SMP config may be less&n;&t; * trustworthy, simply because the SMP table may have been&n;&t; * stomped on during early boot. These loaders are buggy and&n;&t; * should be fixed.&n;&t; */
id|address
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|phys_to_virt
c_func
(paren
l_int|0x40E
)paren
suffix:semicolon
id|address
op_lshift_assign
l_int|4
suffix:semicolon
id|smp_scan_config
c_func
(paren
id|address
comma
l_int|0x1000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|smp_found_config
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;WARNING: MP table in the EBDA can be UNSAFE, contact linux-smp@vger.kernel.org if you experience SMP problems!&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/*&n; * The Visual Workstation is Intel MP compliant in the hardware&n; * sense, but it doesnt have a BIOS(-configuration table).&n; * No problem for Linux.&n; */
DECL|function|find_visws_smp
r_void
id|__init
id|find_visws_smp
c_func
(paren
r_void
)paren
(brace
id|smp_found_config
op_assign
l_int|1
suffix:semicolon
id|phys_cpu_present_map
op_or_assign
l_int|2
suffix:semicolon
multiline_comment|/* or in id 1 */
id|apic_version
(braket
l_int|1
)braket
op_or_assign
l_int|0x10
suffix:semicolon
multiline_comment|/* integrated APIC */
id|apic_version
(braket
l_int|0
)braket
op_or_assign
l_int|0x10
suffix:semicolon
id|mp_lapic_addr
op_assign
id|APIC_DEFAULT_PHYS_BASE
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * - Intel MP Configuration Table&n; * - or SGI Visual Workstation configuration&n; */
DECL|function|find_smp_config
r_void
id|__init
id|find_smp_config
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
id|find_intel_smp
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VISWS
id|find_visws_smp
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
