multiline_comment|/*&n; *  acpi.c - Architecture-Specific Low-Level ACPI Support&n; *&n; *  Copyright (C) 1999 VA Linux Systems&n; *  Copyright (C) 1999,2000 Walt Drummond &lt;drummond@valinux.com&gt;&n; *  Copyright (C) 2000, 2002-2003 Hewlett-Packard Co.&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *  Copyright (C) 2000 Intel Corp.&n; *  Copyright (C) 2000,2001 J.I. Lee &lt;jung-ik.lee@intel.com&gt;&n; *  Copyright (C) 2001 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *  Copyright (C) 2001 Jenna Hall &lt;jenna.s.hall@intel.com&gt;&n; *  Copyright (C) 2001 Takayoshi Kochi &lt;t-kochi@bq.jp.nec.com&gt;&n; *  Copyright (C) 2002 Erich Focht &lt;efocht@ess.nec.de&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;linux/efi.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/iosapic.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/numa.h&gt;
DECL|macro|PREFIX
mdefine_line|#define PREFIX&t;&t;&t;&quot;ACPI: &quot;
DECL|variable|pm_idle
r_void
(paren
op_star
id|pm_idle
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|pm_power_off
r_void
(paren
op_star
id|pm_power_off
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|acpi_kbd_controller_present
r_int
r_char
id|acpi_kbd_controller_present
op_assign
l_int|1
suffix:semicolon
DECL|variable|acpi_disabled
r_int
id|acpi_disabled
suffix:semicolon
multiline_comment|/* XXX this shouldn&squot;t be needed---we can&squot;t boot without ACPI! */
r_const
r_char
op_star
DECL|function|acpi_get_sysname
id|acpi_get_sysname
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_IA64_GENERIC
r_int
r_int
id|rsdp_phys
suffix:semicolon
r_struct
id|acpi20_table_rsdp
op_star
id|rsdp
suffix:semicolon
r_struct
id|acpi_table_xsdt
op_star
id|xsdt
suffix:semicolon
r_struct
id|acpi_table_header
op_star
id|hdr
suffix:semicolon
id|rsdp_phys
op_assign
id|acpi_find_rsdp
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rsdp_phys
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ACPI 2.0 RSDP not found, default to &bslash;&quot;dig&bslash;&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_string|&quot;dig&quot;
suffix:semicolon
)brace
id|rsdp
op_assign
(paren
r_struct
id|acpi20_table_rsdp
op_star
)paren
id|__va
c_func
(paren
id|rsdp_phys
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|rsdp-&gt;signature
comma
id|RSDP_SIG
comma
r_sizeof
(paren
id|RSDP_SIG
)paren
op_minus
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ACPI 2.0 RSDP signature incorrect, default to &bslash;&quot;dig&bslash;&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_string|&quot;dig&quot;
suffix:semicolon
)brace
id|xsdt
op_assign
(paren
r_struct
id|acpi_table_xsdt
op_star
)paren
id|__va
c_func
(paren
id|rsdp-&gt;xsdt_address
)paren
suffix:semicolon
id|hdr
op_assign
op_amp
id|xsdt-&gt;header
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|hdr-&gt;signature
comma
id|XSDT_SIG
comma
r_sizeof
(paren
id|XSDT_SIG
)paren
op_minus
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ACPI 2.0 XSDT signature incorrect, default to &bslash;&quot;dig&bslash;&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_string|&quot;dig&quot;
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|hdr-&gt;oem_id
comma
l_string|&quot;HP&quot;
)paren
)paren
(brace
r_return
l_string|&quot;hpzx1&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|hdr-&gt;oem_id
comma
l_string|&quot;SGI&quot;
)paren
)paren
(brace
r_return
l_string|&quot;sn2&quot;
suffix:semicolon
)brace
r_return
l_string|&quot;dig&quot;
suffix:semicolon
macro_line|#else
macro_line|# if defined (CONFIG_IA64_HP_SIM)
r_return
l_string|&quot;hpsim&quot;
suffix:semicolon
macro_line|# elif defined (CONFIG_IA64_HP_ZX1)
r_return
l_string|&quot;hpzx1&quot;
suffix:semicolon
macro_line|# elif defined (CONFIG_IA64_SGI_SN2)
r_return
l_string|&quot;sn2&quot;
suffix:semicolon
macro_line|# elif defined (CONFIG_IA64_DIG)
r_return
l_string|&quot;dig&quot;
suffix:semicolon
macro_line|# else
macro_line|#&t;error Unknown platform.  Fix acpi.c.
macro_line|# endif
macro_line|#endif
)brace
macro_line|#ifdef CONFIG_ACPI_BOOT
DECL|macro|ACPI_MAX_PLATFORM_INTERRUPTS
mdefine_line|#define ACPI_MAX_PLATFORM_INTERRUPTS&t;256
multiline_comment|/* Array to record platform interrupt vectors for generic interrupt routing. */
DECL|variable|platform_intr_list
r_int
id|platform_intr_list
(braket
id|ACPI_MAX_PLATFORM_INTERRUPTS
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
id|ACPI_MAX_PLATFORM_INTERRUPTS
op_minus
l_int|1
)braket
op_assign
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|acpi_irq_model
r_enum
id|acpi_irq_model_id
id|acpi_irq_model
op_assign
id|ACPI_IRQ_MODEL_IOSAPIC
suffix:semicolon
multiline_comment|/*&n; * Interrupt routing API for device drivers.  Provides interrupt vector for&n; * a generic platform event.  Currently only CPEI is implemented.&n; */
r_int
DECL|function|acpi_request_vector
id|acpi_request_vector
(paren
id|u32
id|int_type
)paren
(brace
r_int
id|vector
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|int_type
OL
id|ACPI_MAX_PLATFORM_INTERRUPTS
)paren
(brace
multiline_comment|/* corrected platform error interrupt */
id|vector
op_assign
id|platform_intr_list
(braket
id|int_type
)braket
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;acpi_request_vector(): invalid interrupt type&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|vector
suffix:semicolon
)brace
r_char
op_star
DECL|function|__acpi_map_table
id|__acpi_map_table
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|__va
c_func
(paren
id|phys_addr
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;                            Boot-time Table Parsing&n;   -------------------------------------------------------------------------- */
DECL|variable|__initdata
r_static
r_int
id|total_cpus
id|__initdata
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|available_cpus
id|__initdata
suffix:semicolon
DECL|variable|__initdata
r_struct
id|acpi_table_madt
op_star
id|acpi_madt
id|__initdata
suffix:semicolon
DECL|variable|has_8259
r_static
id|u8
id|has_8259
suffix:semicolon
r_static
r_int
id|__init
DECL|function|acpi_parse_lapic_addr_ovr
id|acpi_parse_lapic_addr_ovr
(paren
id|acpi_table_entry_header
op_star
id|header
)paren
(brace
r_struct
id|acpi_table_lapic_addr_ovr
op_star
id|lapic
suffix:semicolon
id|lapic
op_assign
(paren
r_struct
id|acpi_table_lapic_addr_ovr
op_star
)paren
id|header
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lapic
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|acpi_table_print_madt_entry
c_func
(paren
id|header
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lapic-&gt;address
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|ipi_base_addr
)paren
suffix:semicolon
id|ipi_base_addr
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|lapic-&gt;address
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|acpi_parse_lsapic
id|acpi_parse_lsapic
(paren
id|acpi_table_entry_header
op_star
id|header
)paren
(brace
r_struct
id|acpi_table_lsapic
op_star
id|lsapic
suffix:semicolon
id|lsapic
op_assign
(paren
r_struct
id|acpi_table_lsapic
op_star
)paren
id|header
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lsapic
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|acpi_table_print_madt_entry
c_func
(paren
id|header
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CPU %d (0x%04x)&quot;
comma
id|total_cpus
comma
(paren
id|lsapic-&gt;id
op_lshift
l_int|8
)paren
op_or
id|lsapic-&gt;eid
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lsapic-&gt;flags.enabled
)paren
id|printk
c_func
(paren
l_string|&quot; disabled&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|available_cpus
op_ge
id|NR_CPUS
)paren
id|printk
c_func
(paren
l_string|&quot; ignored (increase NR_CPUS)&quot;
)paren
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
l_string|&quot; enabled&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|smp_boot_data.cpu_phys_id
(braket
id|available_cpus
)braket
op_assign
(paren
id|lsapic-&gt;id
op_lshift
l_int|8
)paren
op_or
id|lsapic-&gt;eid
suffix:semicolon
r_if
c_cond
(paren
id|hard_smp_processor_id
c_func
(paren
)paren
op_eq
(paren
r_int
r_int
)paren
id|smp_boot_data.cpu_phys_id
(braket
id|available_cpus
)braket
)paren
id|printk
c_func
(paren
l_string|&quot; (BSP)&quot;
)paren
suffix:semicolon
macro_line|#endif
op_increment
id|available_cpus
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|total_cpus
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|acpi_parse_lapic_nmi
id|acpi_parse_lapic_nmi
(paren
id|acpi_table_entry_header
op_star
id|header
)paren
(brace
r_struct
id|acpi_table_lapic_nmi
op_star
id|lacpi_nmi
suffix:semicolon
id|lacpi_nmi
op_assign
(paren
r_struct
id|acpi_table_lapic_nmi
op_star
)paren
id|header
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lacpi_nmi
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|acpi_table_print_madt_entry
c_func
(paren
id|header
)paren
suffix:semicolon
multiline_comment|/* TBD: Support lapic_nmi entries */
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|acpi_parse_iosapic
id|acpi_parse_iosapic
(paren
id|acpi_table_entry_header
op_star
id|header
)paren
(brace
r_struct
id|acpi_table_iosapic
op_star
id|iosapic
suffix:semicolon
id|iosapic
op_assign
(paren
r_struct
id|acpi_table_iosapic
op_star
)paren
id|header
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iosapic
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|acpi_table_print_madt_entry
c_func
(paren
id|header
)paren
suffix:semicolon
id|iosapic_init
c_func
(paren
id|iosapic-&gt;address
comma
id|iosapic-&gt;global_irq_base
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|acpi_parse_plat_int_src
id|acpi_parse_plat_int_src
(paren
id|acpi_table_entry_header
op_star
id|header
)paren
(brace
r_struct
id|acpi_table_plat_int_src
op_star
id|plintsrc
suffix:semicolon
r_int
id|vector
suffix:semicolon
id|plintsrc
op_assign
(paren
r_struct
id|acpi_table_plat_int_src
op_star
)paren
id|header
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|plintsrc
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|acpi_table_print_madt_entry
c_func
(paren
id|header
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get vector assignment for this interrupt, set attributes,&n;&t; * and program the IOSAPIC routing table.&n;&t; */
id|vector
op_assign
id|iosapic_register_platform_intr
c_func
(paren
id|plintsrc-&gt;type
comma
id|plintsrc-&gt;global_irq
comma
id|plintsrc-&gt;iosapic_vector
comma
id|plintsrc-&gt;eid
comma
id|plintsrc-&gt;id
comma
(paren
id|plintsrc-&gt;flags.polarity
op_eq
l_int|1
)paren
ques
c_cond
id|IOSAPIC_POL_HIGH
suffix:colon
id|IOSAPIC_POL_LOW
comma
(paren
id|plintsrc-&gt;flags.trigger
op_eq
l_int|1
)paren
ques
c_cond
id|IOSAPIC_EDGE
suffix:colon
id|IOSAPIC_LEVEL
)paren
suffix:semicolon
id|platform_intr_list
(braket
id|plintsrc-&gt;type
)braket
op_assign
id|vector
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|acpi_parse_int_src_ovr
id|acpi_parse_int_src_ovr
(paren
id|acpi_table_entry_header
op_star
id|header
)paren
(brace
r_struct
id|acpi_table_int_src_ovr
op_star
id|p
suffix:semicolon
id|p
op_assign
(paren
r_struct
id|acpi_table_int_src_ovr
op_star
)paren
id|header
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|acpi_table_print_madt_entry
c_func
(paren
id|header
)paren
suffix:semicolon
id|iosapic_override_isa_irq
c_func
(paren
id|p-&gt;bus_irq
comma
id|p-&gt;global_irq
comma
(paren
id|p-&gt;flags.polarity
op_eq
l_int|1
)paren
ques
c_cond
id|IOSAPIC_POL_HIGH
suffix:colon
id|IOSAPIC_POL_LOW
comma
(paren
id|p-&gt;flags.trigger
op_eq
l_int|1
)paren
ques
c_cond
id|IOSAPIC_EDGE
suffix:colon
id|IOSAPIC_LEVEL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|acpi_parse_nmi_src
id|acpi_parse_nmi_src
(paren
id|acpi_table_entry_header
op_star
id|header
)paren
(brace
r_struct
id|acpi_table_nmi_src
op_star
id|nmi_src
suffix:semicolon
id|nmi_src
op_assign
(paren
r_struct
id|acpi_table_nmi_src
op_star
)paren
id|header
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nmi_src
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|acpi_table_print_madt_entry
c_func
(paren
id|header
)paren
suffix:semicolon
multiline_comment|/* TBD: Support nimsrc entries */
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|acpi_parse_madt
id|acpi_parse_madt
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|phys_addr
op_logical_or
op_logical_neg
id|size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|acpi_madt
op_assign
(paren
r_struct
id|acpi_table_madt
op_star
)paren
id|__va
c_func
(paren
id|phys_addr
)paren
suffix:semicolon
multiline_comment|/* remember the value for reference after free_initmem() */
macro_line|#ifdef CONFIG_ITANIUM
id|has_8259
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Firmware on old Itanium systems is broken */
macro_line|#else
id|has_8259
op_assign
id|acpi_madt-&gt;flags.pcat_compat
suffix:semicolon
macro_line|#endif
id|iosapic_system_init
c_func
(paren
id|has_8259
)paren
suffix:semicolon
multiline_comment|/* Get base address of IPI Message Block */
r_if
c_cond
(paren
id|acpi_madt-&gt;lapic_address
)paren
id|ipi_base_addr
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|acpi_madt-&gt;lapic_address
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;Local APIC address 0x%lx&bslash;n&quot;
comma
id|ipi_base_addr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ACPI_NUMA
DECL|macro|SLIT_DEBUG
macro_line|#undef SLIT_DEBUG
DECL|macro|PXM_FLAG_LEN
mdefine_line|#define PXM_FLAG_LEN ((MAX_PXM_DOMAINS + 1)/32)
DECL|variable|srat_num_cpus
r_static
r_int
id|__initdata
id|srat_num_cpus
suffix:semicolon
multiline_comment|/* number of cpus */
DECL|variable|pxm_flag
r_static
id|u32
id|__initdata
id|pxm_flag
(braket
id|PXM_FLAG_LEN
)braket
suffix:semicolon
DECL|macro|pxm_bit_set
mdefine_line|#define pxm_bit_set(bit)&t;(set_bit(bit,(void *)pxm_flag))
DECL|macro|pxm_bit_test
mdefine_line|#define pxm_bit_test(bit)&t;(test_bit(bit,(void *)pxm_flag))
multiline_comment|/* maps to convert between proximity domain and logical node ID */
DECL|variable|pxm_to_nid_map
r_int
id|__initdata
id|pxm_to_nid_map
(braket
id|MAX_PXM_DOMAINS
)braket
suffix:semicolon
DECL|variable|nid_to_pxm_map
r_int
id|__initdata
id|nid_to_pxm_map
(braket
id|MAX_NUMNODES
)braket
suffix:semicolon
DECL|variable|slit_table
r_static
r_struct
id|acpi_table_slit
id|__initdata
op_star
id|slit_table
suffix:semicolon
multiline_comment|/*&n; * ACPI 2.0 SLIT (System Locality Information Table)&n; * http://devresource.hp.com/devresource/Docs/TechPapers/IA64/slit.pdf&n; */
r_void
id|__init
DECL|function|acpi_numa_slit_init
id|acpi_numa_slit_init
(paren
r_struct
id|acpi_table_slit
op_star
id|slit
)paren
(brace
id|u32
id|len
suffix:semicolon
id|len
op_assign
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
op_plus
l_int|8
op_plus
id|slit-&gt;localities
op_star
id|slit-&gt;localities
suffix:semicolon
r_if
c_cond
(paren
id|slit-&gt;header.length
op_ne
id|len
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ACPI 2.0 SLIT: size mismatch: %d expected, %d actual&bslash;n&quot;
comma
id|len
comma
id|slit-&gt;header.length
)paren
suffix:semicolon
id|memset
c_func
(paren
id|numa_slit
comma
l_int|10
comma
r_sizeof
(paren
id|numa_slit
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|slit_table
op_assign
id|slit
suffix:semicolon
)brace
r_void
id|__init
DECL|function|acpi_numa_processor_affinity_init
id|acpi_numa_processor_affinity_init
(paren
r_struct
id|acpi_table_processor_affinity
op_star
id|pa
)paren
(brace
multiline_comment|/* record this node in proximity bitmap */
id|pxm_bit_set
c_func
(paren
id|pa-&gt;proximity_domain
)paren
suffix:semicolon
id|node_cpuid
(braket
id|srat_num_cpus
)braket
dot
id|phys_id
op_assign
(paren
id|pa-&gt;apic_id
op_lshift
l_int|8
)paren
op_or
(paren
id|pa-&gt;lsapic_eid
)paren
suffix:semicolon
multiline_comment|/* nid should be overridden as logical node id later */
id|node_cpuid
(braket
id|srat_num_cpus
)braket
dot
id|nid
op_assign
id|pa-&gt;proximity_domain
suffix:semicolon
id|srat_num_cpus
op_increment
suffix:semicolon
)brace
r_void
id|__init
DECL|function|acpi_numa_memory_affinity_init
id|acpi_numa_memory_affinity_init
(paren
r_struct
id|acpi_table_memory_affinity
op_star
id|ma
)paren
(brace
r_int
r_int
id|paddr
comma
id|size
comma
id|hole_size
comma
id|min_hole_size
suffix:semicolon
id|u8
id|pxm
suffix:semicolon
r_struct
id|node_memblk_s
op_star
id|p
comma
op_star
id|q
comma
op_star
id|pend
suffix:semicolon
id|pxm
op_assign
id|ma-&gt;proximity_domain
suffix:semicolon
multiline_comment|/* fill node memory chunk structure */
id|paddr
op_assign
id|ma-&gt;base_addr_hi
suffix:semicolon
id|paddr
op_assign
(paren
id|paddr
op_lshift
l_int|32
)paren
op_or
id|ma-&gt;base_addr_lo
suffix:semicolon
id|size
op_assign
id|ma-&gt;length_hi
suffix:semicolon
id|size
op_assign
(paren
id|size
op_lshift
l_int|32
)paren
op_or
id|ma-&gt;length_lo
suffix:semicolon
r_if
c_cond
(paren
id|num_memblks
op_ge
id|NR_MEMBLKS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Too many mem chunks in SRAT. Ignoring %ld MBytes at %lx&bslash;n&quot;
comma
id|size
op_div
(paren
l_int|1024
op_star
l_int|1024
)paren
comma
id|paddr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Ignore disabled entries */
r_if
c_cond
(paren
op_logical_neg
id|ma-&gt;flags.enabled
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * When the chunk is not the first one in the node, check distance&n;&t; * from the other chunks. When the hole is too huge ignore the chunk.&n;&t; * This restriction should be removed when multiple chunks per node&n;&t; * is supported.&n;&t; */
id|pend
op_assign
op_amp
id|node_memblk
(braket
id|num_memblks
)braket
suffix:semicolon
id|min_hole_size
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|node_memblk
(braket
l_int|0
)braket
suffix:semicolon
id|p
OL
id|pend
suffix:semicolon
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;nid
op_ne
id|pxm
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;start_paddr
OL
id|paddr
)paren
id|hole_size
op_assign
id|paddr
op_minus
(paren
id|p-&gt;start_paddr
op_plus
id|p-&gt;size
)paren
suffix:semicolon
r_else
id|hole_size
op_assign
id|p-&gt;start_paddr
op_minus
(paren
id|paddr
op_plus
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|min_hole_size
op_logical_or
id|hole_size
OL
id|min_hole_size
)paren
id|min_hole_size
op_assign
id|hole_size
suffix:semicolon
)brace
r_if
c_cond
(paren
id|min_hole_size
)paren
(brace
r_if
c_cond
(paren
id|min_hole_size
OG
id|size
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Too huge memory hole. Ignoring %ld MBytes at %lx&bslash;n&quot;
comma
id|size
op_div
(paren
l_int|1024
op_star
l_int|1024
)paren
comma
id|paddr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/* record this node in proximity bitmap */
id|pxm_bit_set
c_func
(paren
id|pxm
)paren
suffix:semicolon
multiline_comment|/* Insertion sort based on base address */
id|pend
op_assign
op_amp
id|node_memblk
(braket
id|num_memblks
)braket
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|node_memblk
(braket
l_int|0
)braket
suffix:semicolon
id|p
OL
id|pend
suffix:semicolon
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
id|paddr
OL
id|p-&gt;start_paddr
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p
OL
id|pend
)paren
(brace
r_for
c_loop
(paren
id|q
op_assign
id|pend
suffix:semicolon
id|q
op_ge
id|p
suffix:semicolon
id|q
op_decrement
)paren
op_star
(paren
id|q
op_plus
l_int|1
)paren
op_assign
op_star
id|q
suffix:semicolon
)brace
id|p-&gt;start_paddr
op_assign
id|paddr
suffix:semicolon
id|p-&gt;size
op_assign
id|size
suffix:semicolon
id|p-&gt;nid
op_assign
id|pxm
suffix:semicolon
id|num_memblks
op_increment
suffix:semicolon
)brace
r_void
id|__init
DECL|function|acpi_numa_arch_fixup
id|acpi_numa_arch_fixup
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|j
comma
id|node_from
comma
id|node_to
suffix:semicolon
multiline_comment|/* If there&squot;s no SRAT, fix the phys_id */
r_if
c_cond
(paren
id|srat_num_cpus
op_eq
l_int|0
)paren
(brace
id|node_cpuid
(braket
l_int|0
)braket
dot
id|phys_id
op_assign
id|hard_smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* calculate total number of nodes in system from PXM bitmap */
id|numnodes
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* init total nodes in system */
id|memset
c_func
(paren
id|pxm_to_nid_map
comma
op_minus
l_int|1
comma
r_sizeof
(paren
id|pxm_to_nid_map
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|nid_to_pxm_map
comma
op_minus
l_int|1
comma
r_sizeof
(paren
id|nid_to_pxm_map
)paren
)paren
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
id|MAX_PXM_DOMAINS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pxm_bit_test
c_func
(paren
id|i
)paren
)paren
(brace
id|pxm_to_nid_map
(braket
id|i
)braket
op_assign
id|numnodes
suffix:semicolon
id|nid_to_pxm_map
(braket
id|numnodes
op_increment
)braket
op_assign
id|i
suffix:semicolon
)brace
)brace
multiline_comment|/* set logical node id in memory chunk structure */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_memblks
suffix:semicolon
id|i
op_increment
)paren
id|node_memblk
(braket
id|i
)braket
dot
id|nid
op_assign
id|pxm_to_nid_map
(braket
id|node_memblk
(braket
id|i
)braket
dot
id|nid
)braket
suffix:semicolon
multiline_comment|/* assign memory bank numbers for each chunk on each node */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|numnodes
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|bank
suffix:semicolon
id|bank
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|num_memblks
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|node_memblk
(braket
id|j
)braket
dot
id|nid
op_eq
id|i
)paren
id|node_memblk
(braket
id|j
)braket
dot
id|bank
op_assign
id|bank
op_increment
suffix:semicolon
)brace
multiline_comment|/* set logical node id in cpu structure */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|srat_num_cpus
suffix:semicolon
id|i
op_increment
)paren
id|node_cpuid
(braket
id|i
)braket
dot
id|nid
op_assign
id|pxm_to_nid_map
(braket
id|node_cpuid
(braket
id|i
)braket
dot
id|nid
)braket
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Number of logical nodes in system = %d&bslash;n&quot;
comma
id|numnodes
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Number of memory chunks in system = %d&bslash;n&quot;
comma
id|num_memblks
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|slit_table
)paren
r_return
suffix:semicolon
id|memset
c_func
(paren
id|numa_slit
comma
op_minus
l_int|1
comma
r_sizeof
(paren
id|numa_slit
)paren
)paren
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
id|slit_table-&gt;localities
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pxm_bit_test
c_func
(paren
id|i
)paren
)paren
r_continue
suffix:semicolon
id|node_from
op_assign
id|pxm_to_nid_map
(braket
id|i
)braket
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|slit_table-&gt;localities
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pxm_bit_test
c_func
(paren
id|j
)paren
)paren
r_continue
suffix:semicolon
id|node_to
op_assign
id|pxm_to_nid_map
(braket
id|j
)braket
suffix:semicolon
id|node_distance
c_func
(paren
id|node_from
comma
id|node_to
)paren
op_assign
id|slit_table-&gt;entry
(braket
id|i
op_star
id|slit_table-&gt;localities
op_plus
id|j
)braket
suffix:semicolon
)brace
)brace
macro_line|#ifdef SLIT_DEBUG
id|printk
c_func
(paren
l_string|&quot;ACPI 2.0 SLIT locality table:&bslash;n&quot;
)paren
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
id|numnodes
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|numnodes
suffix:semicolon
id|j
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%03d &quot;
comma
id|node_distance
c_func
(paren
id|i
comma
id|j
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
macro_line|#endif /* CONFIG_ACPI_NUMA */
r_static
r_int
id|__init
DECL|function|acpi_parse_fadt
id|acpi_parse_fadt
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
)paren
(brace
r_struct
id|acpi_table_header
op_star
id|fadt_header
suffix:semicolon
r_struct
id|fadt_descriptor_rev2
op_star
id|fadt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|phys_addr
op_logical_or
op_logical_neg
id|size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|fadt_header
op_assign
(paren
r_struct
id|acpi_table_header
op_star
)paren
id|__va
c_func
(paren
id|phys_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fadt_header-&gt;revision
op_ne
l_int|3
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Only deal with ACPI 2.0 FADT */
id|fadt
op_assign
(paren
r_struct
id|fadt_descriptor_rev2
op_star
)paren
id|fadt_header
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|fadt-&gt;iapc_boot_arch
op_amp
id|BAF_8042_KEYBOARD_CONTROLLER
)paren
)paren
id|acpi_kbd_controller_present
op_assign
l_int|0
suffix:semicolon
id|acpi_register_irq
c_func
(paren
id|fadt-&gt;sci_int
comma
id|ACPI_ACTIVE_LOW
comma
id|ACPI_LEVEL_SENSITIVE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
r_int
id|__init
DECL|function|acpi_find_rsdp
id|acpi_find_rsdp
(paren
r_void
)paren
(brace
r_int
r_int
id|rsdp_phys
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|efi.acpi20
)paren
id|rsdp_phys
op_assign
id|__pa
c_func
(paren
id|efi.acpi20
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|efi.acpi
)paren
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;v1.0/r0.71 tables no longer supported&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|rsdp_phys
suffix:semicolon
)brace
r_int
id|__init
DECL|function|acpi_boot_init
id|acpi_boot_init
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * MADT&n;&t; * ----&n;&t; * Parse the Multiple APIC Description Table (MADT), if exists.&n;&t; * Note that this table provides platform SMP configuration&n;&t; * information -- the successor to MPS tables.&n;&t; */
r_if
c_cond
(paren
id|acpi_table_parse
c_func
(paren
id|ACPI_APIC
comma
id|acpi_parse_madt
)paren
OL
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Can&squot;t find MADT&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|skip_madt
suffix:semicolon
)brace
multiline_comment|/* Local APIC */
r_if
c_cond
(paren
id|acpi_table_parse_madt
c_func
(paren
id|ACPI_MADT_LAPIC_ADDR_OVR
comma
id|acpi_parse_lapic_addr_ovr
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Error parsing LAPIC address override entry&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_table_parse_madt
c_func
(paren
id|ACPI_MADT_LSAPIC
comma
id|acpi_parse_lsapic
)paren
OL
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Error parsing MADT - no LAPIC entries&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_table_parse_madt
c_func
(paren
id|ACPI_MADT_LAPIC_NMI
comma
id|acpi_parse_lapic_nmi
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Error parsing LAPIC NMI entry&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* I/O APIC */
r_if
c_cond
(paren
id|acpi_table_parse_madt
c_func
(paren
id|ACPI_MADT_IOSAPIC
comma
id|acpi_parse_iosapic
)paren
OL
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Error parsing MADT - no IOSAPIC entries&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* System-Level Interrupt Routing */
r_if
c_cond
(paren
id|acpi_table_parse_madt
c_func
(paren
id|ACPI_MADT_PLAT_INT_SRC
comma
id|acpi_parse_plat_int_src
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Error parsing platform interrupt source entry&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_table_parse_madt
c_func
(paren
id|ACPI_MADT_INT_SRC_OVR
comma
id|acpi_parse_int_src_ovr
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Error parsing interrupt source overrides entry&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_table_parse_madt
c_func
(paren
id|ACPI_MADT_NMI_SRC
comma
id|acpi_parse_nmi_src
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Error parsing NMI SRC entry&bslash;n&quot;
)paren
suffix:semicolon
id|skip_madt
suffix:colon
multiline_comment|/*&n;&t; * FADT says whether a legacy keyboard controller is present.&n;&t; * The FADT also contains an SCI_INT line, by which the system&n;&t; * gets interrupts such as power and sleep buttons.  If it&squot;s not&n;&t; * on a Legacy interrupt, it needs to be setup.&n;&t; */
r_if
c_cond
(paren
id|acpi_table_parse
c_func
(paren
id|ACPI_FADT
comma
id|acpi_parse_fadt
)paren
OL
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Can&squot;t find FADT&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
id|available_cpus
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ACPI: Found 0 CPUS; assuming 1&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CPU 0 (0x%04x)&quot;
comma
id|hard_smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|smp_boot_data.cpu_phys_id
(braket
id|available_cpus
)braket
op_assign
id|hard_smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|available_cpus
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* We&squot;ve got at least one of these, no? */
)brace
id|smp_boot_data.cpu_count
op_assign
id|available_cpus
suffix:semicolon
id|smp_build_cpu_map
c_func
(paren
)paren
suffix:semicolon
macro_line|# ifdef CONFIG_NUMA
r_if
c_cond
(paren
id|srat_num_cpus
op_eq
l_int|0
)paren
(brace
r_int
id|cpu
comma
id|i
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|smp_boot_data.cpu_count
suffix:semicolon
id|cpu
op_increment
)paren
r_if
c_cond
(paren
id|smp_boot_data.cpu_phys_id
(braket
id|cpu
)braket
op_ne
id|hard_smp_processor_id
c_func
(paren
)paren
)paren
id|node_cpuid
(braket
id|i
op_increment
)braket
dot
id|phys_id
op_assign
id|smp_boot_data.cpu_phys_id
(braket
id|cpu
)braket
suffix:semicolon
)brace
id|build_cpu_to_node_map
c_func
(paren
)paren
suffix:semicolon
macro_line|# endif
macro_line|#endif
multiline_comment|/* Make boot-up look pretty */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%d CPUs available, %d CPUs total&bslash;n&quot;
comma
id|available_cpus
comma
id|total_cpus
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * PCI Interrupt Routing&n; */
macro_line|#ifdef CONFIG_PCI
r_int
id|__init
DECL|function|acpi_get_prt
id|acpi_get_prt
(paren
r_struct
id|pci_vector_struct
op_star
op_star
id|vectors
comma
r_int
op_star
id|count
)paren
(brace
r_struct
id|pci_vector_struct
op_star
id|vector
suffix:semicolon
r_struct
id|list_head
op_star
id|node
suffix:semicolon
r_struct
id|acpi_prt_entry
op_star
id|entry
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vectors
op_logical_or
op_logical_neg
id|count
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|vectors
op_assign
l_int|NULL
suffix:semicolon
op_star
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|acpi_prt.count
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;No PCI interrupt routing entries&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* Allocate vectors */
op_star
id|vectors
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pci_vector_struct
)paren
op_star
id|acpi_prt.count
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|vectors
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* Convert PRT entries to IOSAPIC PCI vectors */
id|vector
op_assign
op_star
id|vectors
suffix:semicolon
id|list_for_each
c_func
(paren
id|node
comma
op_amp
id|acpi_prt.entries
)paren
(brace
id|entry
op_assign
(paren
r_struct
id|acpi_prt_entry
op_star
)paren
id|node
suffix:semicolon
id|vector
(braket
id|i
)braket
dot
id|segment
op_assign
id|entry-&gt;id.segment
suffix:semicolon
id|vector
(braket
id|i
)braket
dot
id|bus
op_assign
id|entry-&gt;id.bus
suffix:semicolon
id|vector
(braket
id|i
)braket
dot
id|pci_id
op_assign
(paren
(paren
id|u32
)paren
id|entry-&gt;id.device
op_lshift
l_int|16
)paren
op_or
l_int|0xffff
suffix:semicolon
id|vector
(braket
id|i
)braket
dot
id|pin
op_assign
id|entry-&gt;pin
suffix:semicolon
id|vector
(braket
id|i
)braket
dot
id|irq
op_assign
id|entry-&gt;link.index
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
op_star
id|count
op_assign
id|acpi_prt.count
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PCI */
multiline_comment|/* Assume IA64 always use I/O SAPIC */
r_int
id|__init
DECL|function|acpi_get_interrupt_model
id|acpi_get_interrupt_model
(paren
r_int
op_star
id|type
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|type
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|type
op_assign
id|ACPI_IRQ_MODEL_IOSAPIC
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|acpi_irq_to_vector
id|acpi_irq_to_vector
(paren
id|u32
id|gsi
)paren
(brace
r_if
c_cond
(paren
id|has_8259
op_logical_and
id|gsi
OL
l_int|16
)paren
r_return
id|isa_irq_to_vector
c_func
(paren
id|gsi
)paren
suffix:semicolon
r_return
id|gsi_to_vector
c_func
(paren
id|gsi
)paren
suffix:semicolon
)brace
r_int
DECL|function|acpi_register_irq
id|acpi_register_irq
(paren
id|u32
id|gsi
comma
id|u32
id|polarity
comma
id|u32
id|trigger
)paren
(brace
r_if
c_cond
(paren
id|has_8259
op_logical_and
id|gsi
OL
l_int|16
)paren
r_return
id|isa_irq_to_vector
c_func
(paren
id|gsi
)paren
suffix:semicolon
r_return
id|iosapic_register_intr
c_func
(paren
id|gsi
comma
(paren
id|polarity
op_eq
id|ACPI_ACTIVE_HIGH
)paren
ques
c_cond
id|IOSAPIC_POL_HIGH
suffix:colon
id|IOSAPIC_POL_LOW
comma
(paren
id|trigger
op_eq
id|ACPI_EDGE_SENSITIVE
)paren
ques
c_cond
id|IOSAPIC_EDGE
suffix:colon
id|IOSAPIC_LEVEL
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_ACPI_BOOT */
eof
