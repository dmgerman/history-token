multiline_comment|/*&n; * Copyright 2004 James Cleverdon, IBM.&n; * Subject to the GNU Public License, v.2&n; *&n; * Flat APIC subarch code.  Maximum 8 CPUs, logical delivery.&n; *&n; * Hacked for x86-64 by James Cleverdon from i386 architecture code by&n; * Martin Bligh, Andi Kleen, James Bottomley, John Stultz, and&n; * James Cleverdon.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/ipi.h&gt;
DECL|function|flat_target_cpus
r_static
id|cpumask_t
id|flat_target_cpus
c_func
(paren
r_void
)paren
(brace
r_return
id|cpu_online_map
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up the logical destination ID.&n; *&n; * Intel recommends to set DFR, LDR and TPR before enabling&n; * an APIC.  See e.g. &quot;AP-388 82489DX User&squot;s Manual&quot; (Intel&n; * document number 292116).  So here it goes...&n; */
DECL|function|flat_init_apic_ldr
r_static
r_void
id|flat_init_apic_ldr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
r_int
r_int
id|num
comma
id|id
suffix:semicolon
id|num
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|id
op_assign
l_int|1UL
op_lshift
id|num
suffix:semicolon
id|x86_cpu_to_log_apicid
(braket
id|num
)braket
op_assign
id|id
suffix:semicolon
id|apic_write_around
c_func
(paren
id|APIC_DFR
comma
id|APIC_DFR_FLAT
)paren
suffix:semicolon
id|val
op_assign
id|apic_read
c_func
(paren
id|APIC_LDR
)paren
op_amp
op_complement
id|APIC_LDR_MASK
suffix:semicolon
id|val
op_or_assign
id|SET_APIC_LOGICAL_ID
c_func
(paren
id|id
)paren
suffix:semicolon
id|apic_write_around
c_func
(paren
id|APIC_LDR
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|flat_send_IPI_allbutself
r_static
r_void
id|flat_send_IPI_allbutself
c_func
(paren
r_int
id|vector
)paren
(brace
multiline_comment|/*&n;&t; * if there are no other CPUs in the system then&n;&t; * we get an APIC send error if we try to broadcast.&n;&t; * thus we have to avoid sending IPIs in this case.&n;&t; */
r_if
c_cond
(paren
id|num_online_cpus
c_func
(paren
)paren
OG
l_int|1
)paren
id|__send_IPI_shortcut
c_func
(paren
id|APIC_DEST_ALLBUT
comma
id|vector
comma
id|APIC_DEST_LOGICAL
)paren
suffix:semicolon
)brace
DECL|function|flat_send_IPI_all
r_static
r_void
id|flat_send_IPI_all
c_func
(paren
r_int
id|vector
)paren
(brace
id|__send_IPI_shortcut
c_func
(paren
id|APIC_DEST_ALLINC
comma
id|vector
comma
id|APIC_DEST_LOGICAL
)paren
suffix:semicolon
)brace
DECL|function|flat_send_IPI_mask
r_static
r_void
id|flat_send_IPI_mask
c_func
(paren
id|cpumask_t
id|cpumask
comma
r_int
id|vector
)paren
(brace
r_int
r_int
id|mask
op_assign
id|cpus_addr
c_func
(paren
id|cpumask
)paren
(braket
l_int|0
)braket
suffix:semicolon
r_int
r_int
id|cfg
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|local_save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Wait for idle.&n;&t; */
id|apic_wait_icr_idle
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * prepare target chip field&n;&t; */
id|cfg
op_assign
id|__prepare_ICR2
c_func
(paren
id|mask
)paren
suffix:semicolon
id|apic_write_around
c_func
(paren
id|APIC_ICR2
comma
id|cfg
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * program the ICR&n;&t; */
id|cfg
op_assign
id|__prepare_ICR
c_func
(paren
l_int|0
comma
id|vector
comma
id|APIC_DEST_LOGICAL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Send the IPI. The write to APIC_ICR fires this off.&n;&t; */
id|apic_write_around
c_func
(paren
id|APIC_ICR
comma
id|cfg
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|flat_apic_id_registered
r_static
r_int
id|flat_apic_id_registered
c_func
(paren
r_void
)paren
(brace
r_return
id|physid_isset
c_func
(paren
id|GET_APIC_ID
c_func
(paren
id|apic_read
c_func
(paren
id|APIC_ID
)paren
)paren
comma
id|phys_cpu_present_map
)paren
suffix:semicolon
)brace
DECL|function|flat_cpu_mask_to_apicid
r_static
r_int
r_int
id|flat_cpu_mask_to_apicid
c_func
(paren
id|cpumask_t
id|cpumask
)paren
(brace
r_return
id|cpus_addr
c_func
(paren
id|cpumask
)paren
(braket
l_int|0
)braket
op_amp
id|APIC_ALL_CPUS
suffix:semicolon
)brace
DECL|function|phys_pkg_id
r_static
r_int
r_int
id|phys_pkg_id
c_func
(paren
r_int
id|index_msb
)paren
(brace
id|u32
id|ebx
suffix:semicolon
id|ebx
op_assign
id|cpuid_ebx
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_return
(paren
(paren
id|ebx
op_rshift
l_int|24
)paren
op_amp
l_int|0xFF
)paren
op_rshift
id|index_msb
suffix:semicolon
)brace
DECL|variable|apic_flat
r_struct
id|genapic
id|apic_flat
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;flat&quot;
comma
dot
id|int_delivery_mode
op_assign
id|dest_LowestPrio
comma
dot
id|int_dest_mode
op_assign
(paren
id|APIC_DEST_LOGICAL
op_ne
l_int|0
)paren
comma
dot
id|int_delivery_dest
op_assign
id|APIC_DEST_LOGICAL
op_or
id|APIC_DM_LOWEST
comma
dot
id|target_cpus
op_assign
id|flat_target_cpus
comma
dot
id|apic_id_registered
op_assign
id|flat_apic_id_registered
comma
dot
id|init_apic_ldr
op_assign
id|flat_init_apic_ldr
comma
dot
id|send_IPI_all
op_assign
id|flat_send_IPI_all
comma
dot
id|send_IPI_allbutself
op_assign
id|flat_send_IPI_allbutself
comma
dot
id|send_IPI_mask
op_assign
id|flat_send_IPI_mask
comma
dot
id|cpu_mask_to_apicid
op_assign
id|flat_cpu_mask_to_apicid
comma
dot
id|phys_pkg_id
op_assign
id|phys_pkg_id
comma
)brace
suffix:semicolon
eof
