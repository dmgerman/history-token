multiline_comment|/*&n; *&t;OSS handling&n; *&t;Written by Joshua M. Thompson (funaho@jurai.org)&n; *&n; *&n; *&t;This chip is used in the IIfx in place of VIA #2. It acts like a fancy&n; *&t;VIA chip with prorammable interrupt levels.&n; *&n; * 990502 (jmt) - Major rewrite for new interrupt architecture as well as some&n; *&t;&t;  recent insights into OSS operational details.&n; * 990610 (jmt) - Now taking fulll advantage of the OSS. Interrupts are mapped&n; *&t;&t;  to mostly match the A/UX interrupt scheme supported on the&n; *&t;&t;  VIA side. Also added support for enabling the ISM irq again&n; *&t;&t;  since we now have a functional IOP manager.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt; 
macro_line|#include &lt;asm/machw.h&gt; 
macro_line|#include &lt;asm/macintosh.h&gt; 
macro_line|#include &lt;asm/macints.h&gt;
macro_line|#include &lt;asm/mac_via.h&gt;
macro_line|#include &lt;asm/mac_oss.h&gt;
DECL|variable|oss_present
r_int
id|oss_present
suffix:semicolon
DECL|variable|oss
r_volatile
r_struct
id|mac_oss
op_star
id|oss
suffix:semicolon
id|irqreturn_t
id|oss_irq
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
id|irqreturn_t
id|oss_nubus_irq
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
id|irqreturn_t
id|via1_irq
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
id|irqreturn_t
id|mac_scc_dispatch
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Initialize the OSS&n; *&n; * The OSS &quot;detection&quot; code is actually in via_init() which is always called&n; * before us. Thus we can count on oss_present being valid on entry.&n; */
DECL|function|oss_init
r_void
id|__init
id|oss_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|oss_present
)paren
r_return
suffix:semicolon
id|oss
op_assign
(paren
r_struct
id|mac_oss
op_star
)paren
id|OSS_BASE
suffix:semicolon
multiline_comment|/* Disable all interrupts. Unlike a VIA it looks like we    */
multiline_comment|/* do this by setting the source&squot;s interrupt level to zero. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|OSS_NUM_SOURCES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|oss-&gt;irq_level
(braket
id|i
)braket
op_assign
id|OSS_IRQLEV_DISABLED
suffix:semicolon
)brace
multiline_comment|/* If we disable VIA1 here, we never really handle it... */
id|oss-&gt;irq_level
(braket
id|OSS_VIA1
)braket
op_assign
id|OSS_IRQLEV_VIA1
suffix:semicolon
)brace
multiline_comment|/*&n; * Register the OSS and NuBus interrupt dispatchers.&n; */
DECL|function|oss_register_interrupts
r_void
id|__init
id|oss_register_interrupts
c_func
(paren
r_void
)paren
(brace
id|sys_request_irq
c_func
(paren
id|OSS_IRQLEV_SCSI
comma
id|oss_irq
comma
id|IRQ_FLG_LOCK
comma
l_string|&quot;scsi&quot;
comma
(paren
r_void
op_star
)paren
id|oss
)paren
suffix:semicolon
id|sys_request_irq
c_func
(paren
id|OSS_IRQLEV_IOPSCC
comma
id|mac_scc_dispatch
comma
id|IRQ_FLG_LOCK
comma
l_string|&quot;scc&quot;
comma
id|mac_scc_dispatch
)paren
suffix:semicolon
id|sys_request_irq
c_func
(paren
id|OSS_IRQLEV_NUBUS
comma
id|oss_nubus_irq
comma
id|IRQ_FLG_LOCK
comma
l_string|&quot;nubus&quot;
comma
(paren
r_void
op_star
)paren
id|oss
)paren
suffix:semicolon
id|sys_request_irq
c_func
(paren
id|OSS_IRQLEV_SOUND
comma
id|oss_irq
comma
id|IRQ_FLG_LOCK
comma
l_string|&quot;sound&quot;
comma
(paren
r_void
op_star
)paren
id|oss
)paren
suffix:semicolon
id|sys_request_irq
c_func
(paren
id|OSS_IRQLEV_VIA1
comma
id|via1_irq
comma
id|IRQ_FLG_LOCK
comma
l_string|&quot;via1&quot;
comma
(paren
r_void
op_star
)paren
id|via1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize OSS for Nubus access&n; */
DECL|function|oss_nubus_init
r_void
id|__init
id|oss_nubus_init
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/*&n; * Handle miscellaneous OSS interrupts. Right now that&squot;s just sound&n; * and SCSI; everything else is routed to its own autovector IRQ.&n; */
DECL|function|oss_irq
id|irqreturn_t
id|oss_irq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|events
suffix:semicolon
id|events
op_assign
id|oss-&gt;irq_pending
op_amp
(paren
id|OSS_IP_SOUND
op_or
id|OSS_IP_SCSI
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|events
)paren
r_return
id|IRQ_NONE
suffix:semicolon
macro_line|#ifdef DEBUG_IRQS&t;
r_if
c_cond
(paren
(paren
id|console_loglevel
op_eq
l_int|10
)paren
op_logical_and
op_logical_neg
(paren
id|events
op_amp
id|OSS_IP_SCSI
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;oss_irq: irq %d events = 0x%04X&bslash;n&quot;
comma
id|irq
comma
(paren
r_int
)paren
id|oss-&gt;irq_pending
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* FIXME: how do you clear a pending IRQ?    */
r_if
c_cond
(paren
id|events
op_amp
id|OSS_IP_SOUND
)paren
(brace
multiline_comment|/* FIXME: call sound handler */
id|oss-&gt;irq_pending
op_and_assign
op_complement
id|OSS_IP_SOUND
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|events
op_amp
id|OSS_IP_SCSI
)paren
(brace
id|oss-&gt;irq_level
(braket
id|OSS_SCSI
)braket
op_assign
id|OSS_IRQLEV_DISABLED
suffix:semicolon
id|mac_do_irq_list
c_func
(paren
id|IRQ_MAC_SCSI
comma
id|regs
)paren
suffix:semicolon
id|oss-&gt;irq_pending
op_and_assign
op_complement
id|OSS_IP_SCSI
suffix:semicolon
id|oss-&gt;irq_level
(braket
id|OSS_SCSI
)braket
op_assign
id|OSS_IRQLEV_SCSI
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* FIXME: error check here? */
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*&n; * Nubus IRQ handler, OSS style&n; *&n; * Unlike the VIA/RBV this is on its own autovector interrupt level.&n; */
DECL|function|oss_nubus_irq
id|irqreturn_t
id|oss_nubus_irq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|events
comma
id|irq_bit
comma
id|i
suffix:semicolon
id|events
op_assign
id|oss-&gt;irq_pending
op_amp
id|OSS_IP_NUBUS
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|events
)paren
r_return
id|IRQ_NONE
suffix:semicolon
macro_line|#ifdef DEBUG_NUBUS_INT
r_if
c_cond
(paren
id|console_loglevel
OG
l_int|7
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;oss_nubus_irq: events = 0x%04X&bslash;n&quot;
comma
id|events
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* There are only six slots on the OSS, not seven */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|irq_bit
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
comma
id|irq_bit
op_lshift_assign
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|events
op_amp
id|irq_bit
)paren
(brace
id|oss-&gt;irq_level
(braket
id|i
)braket
op_assign
id|OSS_IRQLEV_DISABLED
suffix:semicolon
id|mac_do_irq_list
c_func
(paren
id|NUBUS_SOURCE_BASE
op_plus
id|i
comma
id|regs
)paren
suffix:semicolon
id|oss-&gt;irq_pending
op_and_assign
op_complement
id|irq_bit
suffix:semicolon
id|oss-&gt;irq_level
(braket
id|i
)braket
op_assign
id|OSS_IRQLEV_NUBUS
suffix:semicolon
)brace
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*&n; * Enable an OSS interrupt&n; *&n; * It looks messy but it&squot;s rather straightforward. The switch() statement&n; * just maps the machspec interrupt numbers to the right OSS interrupt&n; * source (if the OSS handles that interrupt) and then sets the interrupt&n; * level for that source to nonzero, thus enabling the interrupt.&n; */
DECL|function|oss_irq_enable
r_void
id|oss_irq_enable
c_func
(paren
r_int
id|irq
)paren
(brace
macro_line|#ifdef DEBUG_IRQUSE
id|printk
c_func
(paren
l_string|&quot;oss_irq_enable(%d)&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
id|IRQ_SCC
suffix:colon
r_case
id|IRQ_SCCA
suffix:colon
r_case
id|IRQ_SCCB
suffix:colon
id|oss-&gt;irq_level
(braket
id|OSS_IOPSCC
)braket
op_assign
id|OSS_IRQLEV_IOPSCC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_MAC_ADB
suffix:colon
id|oss-&gt;irq_level
(braket
id|OSS_IOPISM
)braket
op_assign
id|OSS_IRQLEV_IOPISM
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_MAC_SCSI
suffix:colon
id|oss-&gt;irq_level
(braket
id|OSS_SCSI
)braket
op_assign
id|OSS_IRQLEV_SCSI
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_NUBUS_9
suffix:colon
r_case
id|IRQ_NUBUS_A
suffix:colon
r_case
id|IRQ_NUBUS_B
suffix:colon
r_case
id|IRQ_NUBUS_C
suffix:colon
r_case
id|IRQ_NUBUS_D
suffix:colon
r_case
id|IRQ_NUBUS_E
suffix:colon
id|irq
op_sub_assign
id|NUBUS_SOURCE_BASE
suffix:semicolon
id|oss-&gt;irq_level
(braket
id|irq
)braket
op_assign
id|OSS_IRQLEV_NUBUS
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef DEBUG_IRQUSE
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;%s unknown irq %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
)brace
)brace
multiline_comment|/*&n; * Disable an OSS interrupt&n; *&n; * Same as above except we set the source&squot;s interrupt level to zero,&n; * to disable the interrupt.&n; */
DECL|function|oss_irq_disable
r_void
id|oss_irq_disable
c_func
(paren
r_int
id|irq
)paren
(brace
macro_line|#ifdef DEBUG_IRQUSE
id|printk
c_func
(paren
l_string|&quot;oss_irq_disable(%d)&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
id|IRQ_SCC
suffix:colon
r_case
id|IRQ_SCCA
suffix:colon
r_case
id|IRQ_SCCB
suffix:colon
id|oss-&gt;irq_level
(braket
id|OSS_IOPSCC
)braket
op_assign
id|OSS_IRQLEV_DISABLED
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_MAC_ADB
suffix:colon
id|oss-&gt;irq_level
(braket
id|OSS_IOPISM
)braket
op_assign
id|OSS_IRQLEV_DISABLED
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_MAC_SCSI
suffix:colon
id|oss-&gt;irq_level
(braket
id|OSS_SCSI
)braket
op_assign
id|OSS_IRQLEV_DISABLED
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_NUBUS_9
suffix:colon
r_case
id|IRQ_NUBUS_A
suffix:colon
r_case
id|IRQ_NUBUS_B
suffix:colon
r_case
id|IRQ_NUBUS_C
suffix:colon
r_case
id|IRQ_NUBUS_D
suffix:colon
r_case
id|IRQ_NUBUS_E
suffix:colon
id|irq
op_sub_assign
id|NUBUS_SOURCE_BASE
suffix:semicolon
id|oss-&gt;irq_level
(braket
id|irq
)braket
op_assign
id|OSS_IRQLEV_DISABLED
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef DEBUG_IRQUSE
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;%s unknown irq %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
)brace
)brace
multiline_comment|/*&n; * Clear an OSS interrupt&n; *&n; * Not sure if this works or not but it&squot;s the only method I could&n; * think of based on the contents of the mac_oss structure.&n; */
DECL|function|oss_irq_clear
r_void
id|oss_irq_clear
c_func
(paren
r_int
id|irq
)paren
(brace
multiline_comment|/* FIXME: how to do this on OSS? */
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
id|IRQ_SCC
suffix:colon
r_case
id|IRQ_SCCA
suffix:colon
r_case
id|IRQ_SCCB
suffix:colon
id|oss-&gt;irq_pending
op_and_assign
op_complement
id|OSS_IP_IOPSCC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_MAC_ADB
suffix:colon
id|oss-&gt;irq_pending
op_and_assign
op_complement
id|OSS_IP_IOPISM
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_MAC_SCSI
suffix:colon
id|oss-&gt;irq_pending
op_and_assign
op_complement
id|OSS_IP_SCSI
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_NUBUS_9
suffix:colon
r_case
id|IRQ_NUBUS_A
suffix:colon
r_case
id|IRQ_NUBUS_B
suffix:colon
r_case
id|IRQ_NUBUS_C
suffix:colon
r_case
id|IRQ_NUBUS_D
suffix:colon
r_case
id|IRQ_NUBUS_E
suffix:colon
id|irq
op_sub_assign
id|NUBUS_SOURCE_BASE
suffix:semicolon
id|oss-&gt;irq_pending
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Check to see if a specific OSS interrupt is pending&n; */
DECL|function|oss_irq_pending
r_int
id|oss_irq_pending
c_func
(paren
r_int
id|irq
)paren
(brace
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
id|IRQ_SCC
suffix:colon
r_case
id|IRQ_SCCA
suffix:colon
r_case
id|IRQ_SCCB
suffix:colon
r_return
id|oss-&gt;irq_pending
op_amp
id|OSS_IP_IOPSCC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_MAC_ADB
suffix:colon
r_return
id|oss-&gt;irq_pending
op_amp
id|OSS_IP_IOPISM
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_MAC_SCSI
suffix:colon
r_return
id|oss-&gt;irq_pending
op_amp
id|OSS_IP_SCSI
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IRQ_NUBUS_9
suffix:colon
r_case
id|IRQ_NUBUS_A
suffix:colon
r_case
id|IRQ_NUBUS_B
suffix:colon
r_case
id|IRQ_NUBUS_C
suffix:colon
r_case
id|IRQ_NUBUS_D
suffix:colon
r_case
id|IRQ_NUBUS_E
suffix:colon
id|irq
op_sub_assign
id|NUBUS_SOURCE_BASE
suffix:semicolon
r_return
id|oss-&gt;irq_pending
op_amp
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
