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
DECL|variable|mp_bus_id_to_node
r_int
id|mp_bus_id_to_node
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
DECL|variable|boot_cpu_physical_apicid
r_int
r_int
id|boot_cpu_physical_apicid
op_assign
op_minus
l_int|1U
suffix:semicolon
DECL|variable|boot_cpu_logical_apicid
r_int
r_int
id|boot_cpu_logical_apicid
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
multiline_comment|/*&n; * The Visual Workstation is Intel MP compliant in the hardware&n; * sense, but it doesn&squot;t have a BIOS(-configuration table).&n; * No problem for Linux.&n; */
DECL|function|find_smp_config
r_void
id|__init
id|find_smp_config
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
eof
