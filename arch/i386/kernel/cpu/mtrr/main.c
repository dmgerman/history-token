multiline_comment|/*  Generic MTRR (Memory Type Range Register) driver.&n;&n;    Copyright (C) 1997-2000  Richard Gooch&n;    Copyright (c) 2002&t;     Patrick Mochel&n;&n;    This library is free software; you can redistribute it and/or&n;    modify it under the terms of the GNU Library General Public&n;    License as published by the Free Software Foundation; either&n;    version 2 of the License, or (at your option) any later version.&n;&n;    This library is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;    Library General Public License for more details.&n;&n;    You should have received a copy of the GNU Library General Public&n;    License along with this library; if not, write to the Free&n;    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;    Richard Gooch may be reached by email at  rgooch@atnf.csiro.au&n;    The postal address is:&n;      Richard Gooch, c/o ATNF, P. O. Box 76, Epping, N.S.W., 2121, Australia.&n;&n;    Source: &quot;Pentium Pro Family Developer&squot;s Manual, Volume 3:&n;    Operating System Writer&squot;s Guide&quot; (Intel document number 242692),&n;    section 11.11.7&n;&n;    This was cleaned and made readable by Patrick Mochel &lt;mochel@osdl.org&gt; &n;    on 6-7 March 2002. &n;    Source: Intel Architecture Software Developers Manual, Volume 3: &n;    System Programming Guide; Section 9.11. (1997 edition - PPro).&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;asm/mtrr.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &quot;mtrr.h&quot;
DECL|macro|MTRR_VERSION
mdefine_line|#define MTRR_VERSION            &quot;2.0 (20020519)&quot;
DECL|variable|num_var_ranges
id|u32
id|num_var_ranges
op_assign
l_int|0
suffix:semicolon
DECL|variable|usage_table
r_int
r_int
op_star
id|usage_table
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|main_lock
)paren
suffix:semicolon
DECL|variable|size_or_mask
DECL|variable|size_and_mask
id|u32
id|size_or_mask
comma
id|size_and_mask
suffix:semicolon
DECL|variable|mtrr_ops
r_static
r_struct
id|mtrr_ops
op_star
id|mtrr_ops
(braket
id|X86_VENDOR_NUM
)braket
op_assign
(brace
)brace
suffix:semicolon
DECL|variable|mtrr_if
r_struct
id|mtrr_ops
op_star
id|mtrr_if
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mtrr_if_name
id|__initdata
r_char
op_star
id|mtrr_if_name
(braket
)braket
op_assign
(brace
l_string|&quot;none&quot;
comma
l_string|&quot;Intel&quot;
comma
l_string|&quot;AMD K6&quot;
comma
l_string|&quot;Cyrix ARR&quot;
comma
l_string|&quot;Centaur MCR&quot;
)brace
suffix:semicolon
r_static
r_void
id|set_mtrr
c_func
(paren
r_int
r_int
id|reg
comma
r_int
r_int
id|base
comma
r_int
r_int
id|size
comma
id|mtrr_type
id|type
)paren
suffix:semicolon
r_extern
r_int
id|arr3_protected
suffix:semicolon
DECL|function|set_mtrr_ops
r_void
id|set_mtrr_ops
c_func
(paren
r_struct
id|mtrr_ops
op_star
id|ops
)paren
(brace
r_if
c_cond
(paren
id|ops-&gt;vendor
op_logical_and
id|ops-&gt;vendor
OL
id|X86_VENDOR_NUM
)paren
id|mtrr_ops
(braket
id|ops-&gt;vendor
)braket
op_assign
id|ops
suffix:semicolon
)brace
multiline_comment|/*  Returns non-zero if we have the write-combining memory type  */
DECL|function|have_wrcomb
r_static
r_int
id|have_wrcomb
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|pci_get_class
c_func
(paren
id|PCI_CLASS_BRIDGE_HOST
op_lshift
l_int|8
comma
l_int|NULL
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* ServerWorks LE chipsets have problems with write-combining &n;&t;&t;   Don&squot;t allow it and leave room for other chipsets to be tagged */
r_if
c_cond
(paren
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_SERVERWORKS
op_logical_and
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_SERVERWORKS_LE
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;mtrr: Serverworks LE detected. Write-combining disabled.&bslash;n&quot;
)paren
suffix:semicolon
id|pci_dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Intel 450NX errata # 23. Non ascending cachline evictions to&n;&t;&t;   write combining memory may resulting in data corruption */
r_if
c_cond
(paren
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_INTEL
op_logical_and
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_INTEL_82451NX
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;mtrr: Intel 450NX MMC detected. Write-combining disabled.&bslash;n&quot;
)paren
suffix:semicolon
id|pci_dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|pci_dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_return
(paren
id|mtrr_if-&gt;have_wrcomb
ques
c_cond
id|mtrr_if
op_member_access_from_pointer
id|have_wrcomb
c_func
(paren
)paren
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*  This function returns the number of variable MTRRs  */
DECL|function|set_num_var_ranges
r_void
id|__init
id|set_num_var_ranges
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|config
op_assign
l_int|0
comma
id|dummy
suffix:semicolon
r_if
c_cond
(paren
id|use_intel
c_func
(paren
)paren
)paren
(brace
id|rdmsr
c_func
(paren
id|MTRRcap_MSR
comma
id|config
comma
id|dummy
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|is_cpu
c_func
(paren
id|AMD
)paren
)paren
id|config
op_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|is_cpu
c_func
(paren
id|CYRIX
)paren
op_logical_or
id|is_cpu
c_func
(paren
id|CENTAUR
)paren
)paren
id|config
op_assign
l_int|8
suffix:semicolon
id|num_var_ranges
op_assign
id|config
op_amp
l_int|0xff
suffix:semicolon
)brace
DECL|function|init_table
r_static
r_void
id|__init
id|init_table
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|max
suffix:semicolon
id|max
op_assign
id|num_var_ranges
suffix:semicolon
r_if
c_cond
(paren
(paren
id|usage_table
op_assign
id|kmalloc
c_func
(paren
id|max
op_star
r_sizeof
op_star
id|usage_table
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mtrr: could not allocate&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
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
id|max
suffix:semicolon
id|i
op_increment
)paren
id|usage_table
(braket
id|i
)braket
op_assign
l_int|1
suffix:semicolon
)brace
DECL|struct|set_mtrr_data
r_struct
id|set_mtrr_data
(brace
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|gate
id|atomic_t
id|gate
suffix:semicolon
DECL|member|smp_base
r_int
r_int
id|smp_base
suffix:semicolon
DECL|member|smp_size
r_int
r_int
id|smp_size
suffix:semicolon
DECL|member|smp_reg
r_int
r_int
id|smp_reg
suffix:semicolon
DECL|member|smp_type
id|mtrr_type
id|smp_type
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|function|ipi_handler
r_static
r_void
id|ipi_handler
c_func
(paren
r_void
op_star
id|info
)paren
multiline_comment|/*  [SUMMARY] Synchronisation handler. Executed by &quot;other&quot; CPUs.&n;    [RETURNS] Nothing.&n;*/
(brace
r_struct
id|set_mtrr_data
op_star
id|data
op_assign
id|info
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|data-&gt;count
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|data-&gt;gate
)paren
)paren
(brace
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*  The master has cleared me to execute  */
r_if
c_cond
(paren
id|data-&gt;smp_reg
op_ne
op_complement
l_int|0U
)paren
id|mtrr_if
op_member_access_from_pointer
id|set
c_func
(paren
id|data-&gt;smp_reg
comma
id|data-&gt;smp_base
comma
id|data-&gt;smp_size
comma
id|data-&gt;smp_type
)paren
suffix:semicolon
r_else
id|mtrr_if
op_member_access_from_pointer
id|set_all
c_func
(paren
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|data-&gt;count
)paren
suffix:semicolon
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|data-&gt;gate
)paren
)paren
(brace
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
id|atomic_dec
c_func
(paren
op_amp
id|data-&gt;count
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/**&n; * set_mtrr - update mtrrs on all processors&n; * @reg:&t;mtrr in question&n; * @base:&t;mtrr base&n; * @size:&t;mtrr size&n; * @type:&t;mtrr type&n; *&n; * This is kinda tricky, but fortunately, Intel spelled it out for us cleanly:&n; * &n; * 1. Send IPI to do the following:&n; * 2. Disable Interrupts&n; * 3. Wait for all procs to do so &n; * 4. Enter no-fill cache mode&n; * 5. Flush caches&n; * 6. Clear PGE bit&n; * 7. Flush all TLBs&n; * 8. Disable all range registers&n; * 9. Update the MTRRs&n; * 10. Enable all range registers&n; * 11. Flush all TLBs and caches again&n; * 12. Enter normal cache mode and reenable caching&n; * 13. Set PGE &n; * 14. Wait for buddies to catch up&n; * 15. Enable interrupts.&n; * &n; * What does that mean for us? Well, first we set data.count to the number&n; * of CPUs. As each CPU disables interrupts, it&squot;ll decrement it once. We wait&n; * until it hits 0 and proceed. We set the data.gate flag and reset data.count.&n; * Meanwhile, they are waiting for that flag to be set. Once it&squot;s set, each &n; * CPU goes through the transition of updating MTRRs. The CPU vendors may each do it &n; * differently, so we call mtrr_if-&gt;set() callback and let them take care of it.&n; * When they&squot;re done, they again decrement data-&gt;count and wait for data.gate to &n; * be reset. &n; * When we finish, we wait for data.count to hit 0 and toggle the data.gate flag.&n; * Everyone then enables interrupts and we all continue on.&n; *&n; * Note that the mechanism is the same for UP systems, too; all the SMP stuff&n; * becomes nops.&n; */
DECL|function|set_mtrr
r_static
r_void
id|set_mtrr
c_func
(paren
r_int
r_int
id|reg
comma
r_int
r_int
id|base
comma
r_int
r_int
id|size
comma
id|mtrr_type
id|type
)paren
(brace
r_struct
id|set_mtrr_data
id|data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|data.smp_reg
op_assign
id|reg
suffix:semicolon
id|data.smp_base
op_assign
id|base
suffix:semicolon
id|data.smp_size
op_assign
id|size
suffix:semicolon
id|data.smp_type
op_assign
id|type
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|data.count
comma
id|num_booting_cpus
c_func
(paren
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|data.gate
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*  Start the ball rolling on other CPUs  */
r_if
c_cond
(paren
id|smp_call_function
c_func
(paren
id|ipi_handler
comma
op_amp
id|data
comma
l_int|1
comma
l_int|0
)paren
op_ne
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;mtrr: timed out waiting for other CPUs&bslash;n&quot;
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|data.count
)paren
)paren
(brace
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* ok, reset count and toggle gate */
id|atomic_set
c_func
(paren
op_amp
id|data.count
comma
id|num_booting_cpus
c_func
(paren
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|data.gate
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* do our MTRR business */
multiline_comment|/* HACK!&n;&t; * We use this same function to initialize the mtrrs on boot.&n;&t; * The state of the boot cpu&squot;s mtrrs has been saved, and we want&n;&t; * to replicate across all the APs. &n;&t; * If we&squot;re doing that @reg is set to something special...&n;&t; */
r_if
c_cond
(paren
id|reg
op_ne
op_complement
l_int|0U
)paren
id|mtrr_if
op_member_access_from_pointer
id|set
c_func
(paren
id|reg
comma
id|base
comma
id|size
comma
id|type
)paren
suffix:semicolon
multiline_comment|/* wait for the others */
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|data.count
)paren
)paren
(brace
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
id|atomic_set
c_func
(paren
op_amp
id|data.count
comma
id|num_booting_cpus
c_func
(paren
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|data.gate
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Wait here for everyone to have seen the gate change&n;&t; * So we&squot;re the last ones to touch &squot;data&squot;&n;&t; */
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|data.count
)paren
)paren
(brace
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;mtrr_add_page - Add a memory type region&n; *&t;@base: Physical base address of region in pages (4 KB)&n; *&t;@size: Physical size of region in pages (4 KB)&n; *&t;@type: Type of MTRR desired&n; *&t;@increment: If this is true do usage counting on the region&n; *&n; *&t;Memory type region registers control the caching on newer Intel and&n; *&t;non Intel processors. This function allows drivers to request an&n; *&t;MTRR is added. The details and hardware specifics of each processor&squot;s&n; *&t;implementation are hidden from the caller, but nevertheless the &n; *&t;caller should expect to need to provide a power of two size on an&n; *&t;equivalent power of two boundary.&n; *&n; *&t;If the region cannot be added either because all regions are in use&n; *&t;or the CPU cannot support it a negative value is returned. On success&n; *&t;the register number for this entry is returned, but should be treated&n; *&t;as a cookie only.&n; *&n; *&t;On a multiprocessor machine the changes are made to all processors.&n; *&t;This is required on x86 by the Intel processors.&n; *&n; *&t;The available types are&n; *&n; *&t;%MTRR_TYPE_UNCACHABLE&t;-&t;No caching&n; *&n; *&t;%MTRR_TYPE_WRBACK&t;-&t;Write data back in bursts whenever&n; *&n; *&t;%MTRR_TYPE_WRCOMB&t;-&t;Write data back soon but allow bursts&n; *&n; *&t;%MTRR_TYPE_WRTHROUGH&t;-&t;Cache reads but not writes&n; *&n; *&t;BUGS: Needs a quiet flag for the cases where drivers do not mind&n; *&t;failures and do not wish system log messages to be sent.&n; */
DECL|function|mtrr_add_page
r_int
id|mtrr_add_page
c_func
(paren
r_int
r_int
id|base
comma
r_int
r_int
id|size
comma
r_int
r_int
id|type
comma
r_char
id|increment
)paren
(brace
r_int
id|i
suffix:semicolon
id|mtrr_type
id|ltype
suffix:semicolon
r_int
r_int
id|lbase
suffix:semicolon
r_int
r_int
id|lsize
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mtrr_if
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|mtrr_if
op_member_access_from_pointer
id|validate_add_page
c_func
(paren
id|base
comma
id|size
comma
id|type
)paren
)paren
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ge
id|MTRR_NUM_TYPES
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;mtrr: type: %u invalid&bslash;n&quot;
comma
id|type
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*  If the type is WC, check that this processor supports it  */
r_if
c_cond
(paren
(paren
id|type
op_eq
id|MTRR_TYPE_WRCOMB
)paren
op_logical_and
op_logical_neg
id|have_wrcomb
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;mtrr: your processor doesn&squot;t support write-combining&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
r_if
c_cond
(paren
id|base
op_amp
id|size_or_mask
op_logical_or
id|size
op_amp
id|size_or_mask
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;mtrr: base or size exceeds the MTRR width&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*  Search for existing MTRR  */
id|down
c_func
(paren
op_amp
id|main_lock
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
id|num_var_ranges
suffix:semicolon
op_increment
id|i
)paren
(brace
id|mtrr_if
op_member_access_from_pointer
id|get
c_func
(paren
id|i
comma
op_amp
id|lbase
comma
op_amp
id|lsize
comma
op_amp
id|ltype
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base
op_ge
id|lbase
op_plus
id|lsize
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|base
OL
id|lbase
)paren
op_logical_and
(paren
id|base
op_plus
id|size
op_le
id|lbase
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/*  At this point we know there is some kind of overlap/enclosure  */
r_if
c_cond
(paren
(paren
id|base
OL
id|lbase
)paren
op_logical_or
(paren
id|base
op_plus
id|size
OG
id|lbase
op_plus
id|lsize
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;mtrr: 0x%lx000,0x%lx000 overlaps existing&quot;
l_string|&quot; 0x%lx000,0x%x000&bslash;n&quot;
comma
id|base
comma
id|size
comma
id|lbase
comma
id|lsize
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*  New region is enclosed by an existing region  */
r_if
c_cond
(paren
id|ltype
op_ne
id|type
)paren
(brace
r_if
c_cond
(paren
id|type
op_eq
id|MTRR_TYPE_UNCACHABLE
)paren
r_continue
suffix:semicolon
id|printk
(paren
id|KERN_WARNING
l_string|&quot;mtrr: type mismatch for %lx000,%lx000 old: %s new: %s&bslash;n&quot;
comma
id|base
comma
id|size
comma
id|mtrr_attrib_to_str
c_func
(paren
id|ltype
)paren
comma
id|mtrr_attrib_to_str
c_func
(paren
id|type
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|increment
)paren
op_increment
id|usage_table
(braket
id|i
)braket
suffix:semicolon
id|error
op_assign
id|i
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*  Search for an empty MTRR  */
id|i
op_assign
id|mtrr_if
op_member_access_from_pointer
id|get_free_region
c_func
(paren
id|base
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
l_int|0
)paren
(brace
id|set_mtrr
c_func
(paren
id|i
comma
id|base
comma
id|size
comma
id|type
)paren
suffix:semicolon
id|usage_table
(braket
id|i
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;mtrr: no more MTRRs available&bslash;n&quot;
)paren
suffix:semicolon
id|error
op_assign
id|i
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|main_lock
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;mtrr_add - Add a memory type region&n; *&t;@base: Physical base address of region&n; *&t;@size: Physical size of region&n; *&t;@type: Type of MTRR desired&n; *&t;@increment: If this is true do usage counting on the region&n; *&n; *&t;Memory type region registers control the caching on newer Intel and&n; *&t;non Intel processors. This function allows drivers to request an&n; *&t;MTRR is added. The details and hardware specifics of each processor&squot;s&n; *&t;implementation are hidden from the caller, but nevertheless the &n; *&t;caller should expect to need to provide a power of two size on an&n; *&t;equivalent power of two boundary.&n; *&n; *&t;If the region cannot be added either because all regions are in use&n; *&t;or the CPU cannot support it a negative value is returned. On success&n; *&t;the register number for this entry is returned, but should be treated&n; *&t;as a cookie only.&n; *&n; *&t;On a multiprocessor machine the changes are made to all processors.&n; *&t;This is required on x86 by the Intel processors.&n; *&n; *&t;The available types are&n; *&n; *&t;%MTRR_TYPE_UNCACHABLE&t;-&t;No caching&n; *&n; *&t;%MTRR_TYPE_WRBACK&t;-&t;Write data back in bursts whenever&n; *&n; *&t;%MTRR_TYPE_WRCOMB&t;-&t;Write data back soon but allow bursts&n; *&n; *&t;%MTRR_TYPE_WRTHROUGH&t;-&t;Cache reads but not writes&n; *&n; *&t;BUGS: Needs a quiet flag for the cases where drivers do not mind&n; *&t;failures and do not wish system log messages to be sent.&n; */
r_int
DECL|function|mtrr_add
id|mtrr_add
c_func
(paren
r_int
r_int
id|base
comma
r_int
r_int
id|size
comma
r_int
r_int
id|type
comma
r_char
id|increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|base
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_logical_or
(paren
id|size
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;mtrr: size and base must be multiples of 4 kiB&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;mtrr: size: 0x%lx  base: 0x%lx&bslash;n&quot;
comma
id|size
comma
id|base
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|mtrr_add_page
c_func
(paren
id|base
op_rshift
id|PAGE_SHIFT
comma
id|size
op_rshift
id|PAGE_SHIFT
comma
id|type
comma
id|increment
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;mtrr_del_page - delete a memory type region&n; *&t;@reg: Register returned by mtrr_add&n; *&t;@base: Physical base address&n; *&t;@size: Size of region&n; *&n; *&t;If register is supplied then base and size are ignored. This is&n; *&t;how drivers should call it.&n; *&n; *&t;Releases an MTRR region. If the usage count drops to zero the &n; *&t;register is freed and the region returns to default state.&n; *&t;On success the register is returned, on failure a negative error&n; *&t;code.&n; */
DECL|function|mtrr_del_page
r_int
id|mtrr_del_page
c_func
(paren
r_int
id|reg
comma
r_int
r_int
id|base
comma
r_int
r_int
id|size
)paren
(brace
r_int
id|i
comma
id|max
suffix:semicolon
id|mtrr_type
id|ltype
suffix:semicolon
r_int
r_int
id|lbase
suffix:semicolon
r_int
r_int
id|lsize
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mtrr_if
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|max
op_assign
id|num_var_ranges
suffix:semicolon
id|down
c_func
(paren
op_amp
id|main_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
OL
l_int|0
)paren
(brace
multiline_comment|/*  Search for existing MTRR  */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|max
suffix:semicolon
op_increment
id|i
)paren
(brace
id|mtrr_if
op_member_access_from_pointer
id|get
c_func
(paren
id|i
comma
op_amp
id|lbase
comma
op_amp
id|lsize
comma
op_amp
id|ltype
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lbase
op_eq
id|base
op_logical_and
id|lsize
op_eq
id|size
)paren
(brace
id|reg
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|reg
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;mtrr: no MTRR for %lx000,%lx000 found&bslash;n&quot;
comma
id|base
comma
id|size
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|reg
op_ge
id|max
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;mtrr: register: %d too big&bslash;n&quot;
comma
id|reg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|is_cpu
c_func
(paren
id|CYRIX
)paren
op_logical_and
op_logical_neg
id|use_intel
c_func
(paren
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|reg
op_eq
l_int|3
)paren
op_logical_and
id|arr3_protected
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;mtrr: ARR3 cannot be changed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|mtrr_if
op_member_access_from_pointer
id|get
c_func
(paren
id|reg
comma
op_amp
id|lbase
comma
op_amp
id|lsize
comma
op_amp
id|ltype
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lsize
OL
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;mtrr: MTRR %d not used&bslash;n&quot;
comma
id|reg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|usage_table
(braket
id|reg
)braket
OL
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;mtrr: reg: %d has count=0&bslash;n&quot;
comma
id|reg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_decrement
id|usage_table
(braket
id|reg
)braket
OL
l_int|1
)paren
id|set_mtrr
c_func
(paren
id|reg
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|error
op_assign
id|reg
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|main_lock
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;mtrr_del - delete a memory type region&n; *&t;@reg: Register returned by mtrr_add&n; *&t;@base: Physical base address&n; *&t;@size: Size of region&n; *&n; *&t;If register is supplied then base and size are ignored. This is&n; *&t;how drivers should call it.&n; *&n; *&t;Releases an MTRR region. If the usage count drops to zero the &n; *&t;register is freed and the region returns to default state.&n; *&t;On success the register is returned, on failure a negative error&n; *&t;code.&n; */
r_int
DECL|function|mtrr_del
id|mtrr_del
c_func
(paren
r_int
id|reg
comma
r_int
r_int
id|base
comma
r_int
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
(paren
id|base
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_logical_or
(paren
id|size
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;mtrr: size and base must be multiples of 4 kiB&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;mtrr: size: 0x%lx  base: 0x%lx&bslash;n&quot;
comma
id|size
comma
id|base
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|mtrr_del_page
c_func
(paren
id|reg
comma
id|base
op_rshift
id|PAGE_SHIFT
comma
id|size
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
)brace
DECL|variable|mtrr_add
id|EXPORT_SYMBOL
c_func
(paren
id|mtrr_add
)paren
suffix:semicolon
DECL|variable|mtrr_del
id|EXPORT_SYMBOL
c_func
(paren
id|mtrr_del
)paren
suffix:semicolon
multiline_comment|/* HACK ALERT!&n; * These should be called implicitly, but we can&squot;t yet until all the initcall&n; * stuff is done...&n; */
r_extern
r_void
id|amd_init_mtrr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cyrix_init_mtrr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|centaur_init_mtrr
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|init_ifs
r_static
r_void
id|__init
id|init_ifs
c_func
(paren
r_void
)paren
(brace
id|amd_init_mtrr
c_func
(paren
)paren
suffix:semicolon
id|cyrix_init_mtrr
c_func
(paren
)paren
suffix:semicolon
id|centaur_init_mtrr
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|init_other_cpus
r_static
r_void
id|__init
id|init_other_cpus
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|use_intel
c_func
(paren
)paren
)paren
id|get_mtrr_state
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* bring up the other processors */
id|set_mtrr
c_func
(paren
op_complement
l_int|0U
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|use_intel
c_func
(paren
)paren
)paren
(brace
id|finalize_mtrr_state
c_func
(paren
)paren
suffix:semicolon
id|mtrr_state_warn
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|struct|mtrr_value
r_struct
id|mtrr_value
(brace
DECL|member|ltype
id|mtrr_type
id|ltype
suffix:semicolon
DECL|member|lbase
r_int
r_int
id|lbase
suffix:semicolon
DECL|member|lsize
r_int
r_int
id|lsize
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|mtrr_state
r_static
r_struct
id|mtrr_value
op_star
id|mtrr_state
suffix:semicolon
DECL|function|mtrr_save
r_static
r_int
id|mtrr_save
c_func
(paren
r_struct
id|sys_device
op_star
id|sysdev
comma
id|u32
id|state
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|size
op_assign
id|num_var_ranges
op_star
r_sizeof
(paren
r_struct
id|mtrr_value
)paren
suffix:semicolon
id|mtrr_state
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtrr_state
)paren
id|memset
c_func
(paren
id|mtrr_state
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
r_else
r_return
op_minus
id|ENOMEM
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
id|num_var_ranges
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mtrr_if
op_member_access_from_pointer
id|get
c_func
(paren
id|i
comma
op_amp
id|mtrr_state
(braket
id|i
)braket
dot
id|lbase
comma
op_amp
id|mtrr_state
(braket
id|i
)braket
dot
id|lsize
comma
op_amp
id|mtrr_state
(braket
id|i
)braket
dot
id|ltype
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mtrr_restore
r_static
r_int
id|mtrr_restore
c_func
(paren
r_struct
id|sys_device
op_star
id|sysdev
)paren
(brace
r_int
id|i
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
id|num_var_ranges
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mtrr_state
(braket
id|i
)braket
dot
id|lsize
)paren
id|set_mtrr
c_func
(paren
id|i
comma
id|mtrr_state
(braket
id|i
)braket
dot
id|lbase
comma
id|mtrr_state
(braket
id|i
)braket
dot
id|lsize
comma
id|mtrr_state
(braket
id|i
)braket
dot
id|ltype
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|mtrr_state
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mtrr_sysdev_driver
r_static
r_struct
id|sysdev_driver
id|mtrr_sysdev_driver
op_assign
(brace
dot
id|suspend
op_assign
id|mtrr_save
comma
dot
id|resume
op_assign
id|mtrr_restore
comma
)brace
suffix:semicolon
multiline_comment|/**&n; * mtrr_init - initialize mtrrs on the boot CPU&n; *&n; * This needs to be called early; before any of the other CPUs are &n; * initialized (i.e. before smp_init()).&n; * &n; */
DECL|function|mtrr_init
r_static
r_int
id|__init
id|mtrr_init
c_func
(paren
r_void
)paren
(brace
id|init_ifs
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_mtrr
)paren
(brace
id|mtrr_if
op_assign
op_amp
id|generic_mtrr_ops
suffix:semicolon
id|size_or_mask
op_assign
l_int|0xff000000
suffix:semicolon
multiline_comment|/* 36 bits */
id|size_and_mask
op_assign
l_int|0x00f00000
suffix:semicolon
r_switch
c_cond
(paren
id|boot_cpu_data.x86_vendor
)paren
(brace
r_case
id|X86_VENDOR_AMD
suffix:colon
multiline_comment|/* The original Athlon docs said that&n;&t;&t;&t;   total addressable memory is 44 bits wide.&n;&t;&t;&t;   It was not really clear whether its MTRRs&n;&t;&t;&t;   follow this or not. (Read: 44 or 36 bits).&n;&t;&t;&t;   However, &quot;x86-64_overview.pdf&quot; explicitly&n;&t;&t;&t;   states that &quot;previous implementations support&n;&t;&t;&t;   36 bit MTRRs&quot; and also provides a way to&n;&t;&t;&t;   query the width (in bits) of the physical&n;&t;&t;&t;   addressable memory on the Hammer family.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|boot_cpu_data.x86
op_eq
l_int|15
op_logical_and
(paren
id|cpuid_eax
c_func
(paren
l_int|0x80000000
)paren
op_ge
l_int|0x80000008
)paren
)paren
(brace
id|u32
id|phys_addr
suffix:semicolon
id|phys_addr
op_assign
id|cpuid_eax
c_func
(paren
l_int|0x80000008
)paren
op_amp
l_int|0xff
suffix:semicolon
id|size_or_mask
op_assign
op_complement
(paren
(paren
l_int|1
op_lshift
(paren
id|phys_addr
op_minus
id|PAGE_SHIFT
)paren
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|size_and_mask
op_assign
op_complement
id|size_or_mask
op_amp
l_int|0xfff00000
suffix:semicolon
)brace
multiline_comment|/* Athlon MTRRs use an Intel-compatible interface for &n;&t;&t;&t; * getting and setting */
r_break
suffix:semicolon
r_case
id|X86_VENDOR_CENTAUR
suffix:colon
r_if
c_cond
(paren
id|boot_cpu_data.x86
op_eq
l_int|6
)paren
(brace
multiline_comment|/* VIA Cyrix family have Intel style MTRRs, but don&squot;t support PAE */
id|size_or_mask
op_assign
l_int|0xfff00000
suffix:semicolon
multiline_comment|/* 32 bits */
id|size_and_mask
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
r_switch
c_cond
(paren
id|boot_cpu_data.x86_vendor
)paren
(brace
r_case
id|X86_VENDOR_AMD
suffix:colon
r_if
c_cond
(paren
id|cpu_has_k6_mtrr
)paren
(brace
multiline_comment|/* Pre-Athlon (K6) AMD CPU MTRRs */
id|mtrr_if
op_assign
id|mtrr_ops
(braket
id|X86_VENDOR_AMD
)braket
suffix:semicolon
id|size_or_mask
op_assign
l_int|0xfff00000
suffix:semicolon
multiline_comment|/* 32 bits */
id|size_and_mask
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|X86_VENDOR_CENTAUR
suffix:colon
r_if
c_cond
(paren
id|cpu_has_centaur_mcr
)paren
(brace
id|mtrr_if
op_assign
id|mtrr_ops
(braket
id|X86_VENDOR_CENTAUR
)braket
suffix:semicolon
id|size_or_mask
op_assign
l_int|0xfff00000
suffix:semicolon
multiline_comment|/* 32 bits */
id|size_and_mask
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|X86_VENDOR_CYRIX
suffix:colon
r_if
c_cond
(paren
id|cpu_has_cyrix_arr
)paren
(brace
id|mtrr_if
op_assign
id|mtrr_ops
(braket
id|X86_VENDOR_CYRIX
)braket
suffix:semicolon
id|size_or_mask
op_assign
l_int|0xfff00000
suffix:semicolon
multiline_comment|/* 32 bits */
id|size_and_mask
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;mtrr: v%s&bslash;n&quot;
comma
id|MTRR_VERSION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtrr_if
)paren
(brace
id|set_num_var_ranges
c_func
(paren
)paren
suffix:semicolon
id|init_table
c_func
(paren
)paren
suffix:semicolon
id|init_other_cpus
c_func
(paren
)paren
suffix:semicolon
r_return
id|sysdev_driver_register
c_func
(paren
op_amp
id|cpu_sysdev_class
comma
op_amp
id|mtrr_sysdev_driver
)paren
suffix:semicolon
)brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|variable|mtrr_init
id|subsys_initcall
c_func
(paren
id|mtrr_init
)paren
suffix:semicolon
eof
