multiline_comment|/*&n; *&t;Macintosh interrupts&n; *&n; * General design:&n; * In contrary to the Amiga and Atari platforms, the Mac hardware seems to &n; * exclusively use the autovector interrupts (the &squot;generic level0-level7&squot; &n; * interrupts with exception vectors 0x19-0x1f). The following interrupt levels&n; * are used:&n; *&t;1&t;- VIA1&n; *&t;&t;  - slot 0: one second interrupt (CA2)&n; *&t;&t;  - slot 1: VBlank (CA1)&n; *&t;&t;  - slot 2: ADB data ready (SR full)&n; *&t;&t;  - slot 3: ADB data  (CB2)&n; *&t;&t;  - slot 4: ADB clock (CB1)&n; *&t;&t;  - slot 5: timer 2&n; *&t;&t;  - slot 6: timer 1&n; *&t;&t;  - slot 7: status of IRQ; signals &squot;any enabled int.&squot;&n; *&n; *&t;2&t;- VIA2 or RBV&n; *&t;&t;  - slot 0: SCSI DRQ (CA2)&n; *&t;&t;  - slot 1: NUBUS IRQ (CA1) need to read port A to find which&n; *&t;&t;  - slot 2: /EXP IRQ (only on IIci)&n; *&t;&t;  - slot 3: SCSI IRQ (CB2)&n; *&t;&t;  - slot 4: ASC IRQ (CB1)&n; *&t;&t;  - slot 5: timer 2 (not on IIci)&n; *&t;&t;  - slot 6: timer 1 (not on IIci)&n; *&t;&t;  - slot 7: status of IRQ; signals &squot;any enabled int.&squot;&n; *&n; *&t;2&t;- OSS (IIfx only?)&n; *&t;&t;  - slot 0: SCSI interrupt&n; *&t;&t;  - slot 1: Sound interrupt&n; *&n; * Levels 3-6 vary by machine type. For VIA or RBV Macintoshes:&n; *&n; *&t;3&t;- unused (?)&n; *&n; *&t;4&t;- SCC (slot number determined by reading RR3 on the SSC itself)&n; *&t;&t;  - slot 1: SCC channel A&n; *&t;&t;  - slot 2: SCC channel B&n; *&n; *&t;5&t;- unused (?)&n; *&t;&t;  [serial errors or special conditions seem to raise level 6&n; *&t;&t;  interrupts on some models (LC4xx?)]&n; *&n; *&t;6&t;- off switch (?)&n; *&n; * For OSS Macintoshes (IIfx only at this point):&n; *&n; *&t;3&t;- Nubus interrupt&n; *&t;&t;  - slot 0: Slot $9&n; *&t;&t;  - slot 1: Slot $A&n; *&t;&t;  - slot 2: Slot $B&n; *&t;&t;  - slot 3: Slot $C&n; *&t;&t;  - slot 4: Slot $D&n; *&t;&t;  - slot 5: Slot $E&n; *&n; *&t;4&t;- SCC IOP&n; *&t;&t;  - slot 1: SCC channel A&n; *&t;&t;  - slot 2: SCC channel B&n; *&n; *&t;5&t;- ISM IOP (ADB?)&n; *&n; *&t;6&t;- unused&n; *&n; * For PSC Macintoshes (660AV, 840AV):&n; *&n; *&t;3&t;- PSC level 3&n; *&t;&t;  - slot 0: MACE&n; *&n; *&t;4&t;- PSC level 4&n; *&t;&t;  - slot 1: SCC channel A interrupt&n; *&t;&t;  - slot 2: SCC channel B interrupt&n; *&t;&t;  - slot 3: MACE DMA&n; *&n; *&t;5&t;- PSC level 5&n; *&n; *&t;6&t;- PSC level 6&n; *&n; * Finally we have good &squot;ole level 7, the non-maskable interrupt:&n; *&n; *&t;7&t;- NMI (programmer&squot;s switch on the back of some Macs)&n; *&t;&t;  Also RAM parity error on models which support it (IIc, IIfx?)&n; *&n; * The current interrupt logic looks something like this:&n; *&n; * - We install dispatchers for the autovector interrupts (1-7). These&n; *   dispatchers are responsible for querying the hardware (the&n; *   VIA/RBV/OSS/PSC chips) to determine the actual interrupt source. Using&n; *   this information a machspec interrupt number is generated by placing the&n; *   index of the interrupt hardware into the low three bits and the original&n; *   autovector interrupt number in the upper 5 bits. The handlers for the&n; *   resulting machspec interrupt are then called.&n; *&n; * - Nubus is a special case because its interrupts are hidden behind two&n; *   layers of hardware. Nubus interrupts come in as index 1 on VIA #2,&n; *   which translates to IRQ number 17. In this spot we install _another_&n; *   dispatcher. This dispatcher finds the interrupting slot number (9-F) and&n; *   then forms a new machspec interrupt number as above with the slot number&n; *   minus 9 in the low three bits and the pseudo-level 7 in the upper five&n; *   bits.  The handlers for this new machspec interrupt number are then&n; *   called. This puts Nubus interrupts into the range 56-62.&n; *&n; * - The Baboon interrupts (used on some PowerBooks) are an even more special&n; *   case. They&squot;re hidden behind the Nubus slot $C interrupt thus adding a&n; *   third layer of indirection. Why oh why did the Apple engineers do that?&n; *&n; * - We support &quot;fast&quot; and &quot;slow&quot; handlers, just like the Amiga port. The&n; *   fast handlers are called first and with all interrupts disabled. They&n; *   are expected to execute quickly (hence the name). The slow handlers are&n; *   called last with interrupts enabled and the interrupt level restored.&n; *   They must therefore be reentrant.&n; *&n; *   TODO:&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt; /* for intr_count */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/machw.h&gt;
macro_line|#include &lt;asm/macintosh.h&gt;
macro_line|#include &lt;asm/mac_via.h&gt;
macro_line|#include &lt;asm/mac_psc.h&gt;
macro_line|#include &lt;asm/hwtest.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &lt;asm/macints.h&gt;
DECL|macro|DEBUG_SPURIOUS
mdefine_line|#define DEBUG_SPURIOUS
DECL|macro|SHUTUP_SONIC
mdefine_line|#define SHUTUP_SONIC
multiline_comment|/*&n; * The mac_irq_list array is an array of linked lists of irq_node_t nodes.&n; * Each node contains one handler to be called whenever the interrupt&n; * occurs, with fast handlers listed before slow handlers.&n; */
DECL|variable|mac_irq_list
id|irq_node_t
op_star
id|mac_irq_list
(braket
id|NUM_MAC_SOURCES
)braket
suffix:semicolon
multiline_comment|/* SCC interrupt mask */
DECL|variable|scc_mask
r_static
r_int
id|scc_mask
suffix:semicolon
multiline_comment|/*&n; * VIA/RBV hooks&n; */
r_extern
r_void
id|via_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|via_register_interrupts
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|via_irq_enable
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|via_irq_disable
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|via_irq_clear
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|via_irq_pending
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * OSS hooks&n; */
r_extern
r_int
id|oss_present
suffix:semicolon
r_extern
r_void
id|oss_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|oss_register_interrupts
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|oss_irq_enable
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|oss_irq_disable
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|oss_irq_clear
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|oss_irq_pending
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * PSC hooks&n; */
r_extern
r_int
id|psc_present
suffix:semicolon
r_extern
r_void
id|psc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|psc_register_interrupts
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|psc_irq_enable
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|psc_irq_disable
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|psc_irq_clear
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|psc_irq_pending
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * IOP hooks&n; */
r_extern
r_void
id|iop_register_interrupts
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Baboon hooks&n; */
r_extern
r_int
id|baboon_present
suffix:semicolon
r_extern
r_void
id|baboon_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|baboon_register_interrupts
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|baboon_irq_enable
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|baboon_irq_disable
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|baboon_irq_clear
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|baboon_irq_pending
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * SCC interrupt routines&n; */
r_static
r_void
id|scc_irq_enable
c_func
(paren
r_int
)paren
suffix:semicolon
r_static
r_void
id|scc_irq_disable
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * console_loglevel determines NMI handler function&n; */
r_extern
id|irqreturn_t
id|mac_bang
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
id|mac_nmi_handler
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
id|mac_debug_handler
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
multiline_comment|/* #define DEBUG_MACINTS */
DECL|function|mac_init_IRQ
r_void
id|mac_init_IRQ
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
macro_line|#ifdef DEBUG_MACINTS
id|printk
c_func
(paren
l_string|&quot;mac_init_IRQ(): Setting things up...&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Initialize the IRQ handler lists. Initially each list is empty, */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_MAC_SOURCES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mac_irq_list
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
id|scc_mask
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Make sure the SONIC interrupt is cleared or things get ugly */
macro_line|#ifdef SHUTUP_SONIC
id|printk
c_func
(paren
l_string|&quot;Killing onboard sonic... &quot;
)paren
suffix:semicolon
multiline_comment|/* This address should hopefully be mapped already */
r_if
c_cond
(paren
id|hwreg_present
c_func
(paren
(paren
r_void
op_star
)paren
(paren
l_int|0x50f0a000
)paren
)paren
)paren
(brace
op_star
(paren
r_int
op_star
)paren
(paren
l_int|0x50f0a014
)paren
op_assign
l_int|0x7fffL
suffix:semicolon
op_star
(paren
r_int
op_star
)paren
(paren
l_int|0x50f0a010
)paren
op_assign
l_int|0L
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Done.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif /* SHUTUP_SONIC */
multiline_comment|/* &n;&t; * Now register the handlers for the master IRQ handlers&n;&t; * at levels 1-7. Most of the work is done elsewhere.&n;&t; */
r_if
c_cond
(paren
id|oss_present
)paren
(brace
id|oss_register_interrupts
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|via_register_interrupts
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|psc_present
)paren
id|psc_register_interrupts
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|baboon_present
)paren
id|baboon_register_interrupts
c_func
(paren
)paren
suffix:semicolon
id|iop_register_interrupts
c_func
(paren
)paren
suffix:semicolon
id|cpu_request_irq
c_func
(paren
l_int|7
comma
id|mac_nmi_handler
comma
id|IRQ_FLG_LOCK
comma
l_string|&quot;NMI&quot;
comma
id|mac_nmi_handler
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_MACINTS
id|printk
c_func
(paren
l_string|&quot;mac_init_IRQ(): Done!&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Routines to work with irq_node_t&squot;s on linked lists lifted from&n; * the Amiga code written by Roman Zippel.&n; */
DECL|function|mac_insert_irq
r_static
r_inline
r_void
id|mac_insert_irq
c_func
(paren
id|irq_node_t
op_star
op_star
id|list
comma
id|irq_node_t
op_star
id|node
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|irq_node_t
op_star
id|cur
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node-&gt;dev_id
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Warning: dev_id of %s is zero&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|node-&gt;devname
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cur
op_assign
op_star
id|list
suffix:semicolon
r_if
c_cond
(paren
id|node-&gt;flags
op_amp
id|IRQ_FLG_FAST
)paren
(brace
id|node-&gt;flags
op_and_assign
op_complement
id|IRQ_FLG_SLOW
suffix:semicolon
r_while
c_loop
(paren
id|cur
op_logical_and
id|cur-&gt;flags
op_amp
id|IRQ_FLG_FAST
)paren
(brace
id|list
op_assign
op_amp
id|cur-&gt;next
suffix:semicolon
id|cur
op_assign
id|cur-&gt;next
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|node-&gt;flags
op_amp
id|IRQ_FLG_SLOW
)paren
(brace
r_while
c_loop
(paren
id|cur
)paren
(brace
id|list
op_assign
op_amp
id|cur-&gt;next
suffix:semicolon
id|cur
op_assign
id|cur-&gt;next
suffix:semicolon
)brace
)brace
r_else
(brace
r_while
c_loop
(paren
id|cur
op_logical_and
op_logical_neg
(paren
id|cur-&gt;flags
op_amp
id|IRQ_FLG_SLOW
)paren
)paren
(brace
id|list
op_assign
op_amp
id|cur-&gt;next
suffix:semicolon
id|cur
op_assign
id|cur-&gt;next
suffix:semicolon
)brace
)brace
id|node-&gt;next
op_assign
id|cur
suffix:semicolon
op_star
id|list
op_assign
id|node
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|mac_delete_irq
r_static
r_inline
r_void
id|mac_delete_irq
c_func
(paren
id|irq_node_t
op_star
op_star
id|list
comma
r_void
op_star
id|dev_id
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|irq_node_t
op_star
id|node
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|node
op_assign
op_star
id|list
suffix:semicolon
id|node
suffix:semicolon
id|list
op_assign
op_amp
id|node-&gt;next
comma
id|node
op_assign
op_star
id|list
)paren
(brace
r_if
c_cond
(paren
id|node-&gt;dev_id
op_eq
id|dev_id
)paren
(brace
op_star
id|list
op_assign
id|node-&gt;next
suffix:semicolon
multiline_comment|/* Mark it as free. */
id|node-&gt;handler
op_assign
l_int|NULL
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;%s: tried to remove invalid irq&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Call all the handlers for a given interrupt. Fast handlers are called&n; * first followed by slow handlers.&n; *&n; * This code taken from the original Amiga code written by Roman Zippel.&n; */
DECL|function|mac_do_irq_list
r_void
id|mac_do_irq_list
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
id|irq_node_t
op_star
id|node
comma
op_star
id|slow_nodes
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|kstat_cpu
c_func
(paren
l_int|0
)paren
dot
id|irqs
(braket
id|irq
)braket
op_increment
suffix:semicolon
macro_line|#ifdef DEBUG_SPURIOUS
r_if
c_cond
(paren
op_logical_neg
id|mac_irq_list
(braket
id|irq
)braket
op_logical_and
(paren
id|console_loglevel
OG
l_int|7
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mac_do_irq_list: spurious interrupt %d!&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* serve first fast and normal handlers */
r_for
c_loop
(paren
id|node
op_assign
id|mac_irq_list
(braket
id|irq
)braket
suffix:semicolon
id|node
op_logical_and
(paren
op_logical_neg
(paren
id|node-&gt;flags
op_amp
id|IRQ_FLG_SLOW
)paren
)paren
suffix:semicolon
id|node
op_assign
id|node-&gt;next
)paren
id|node
op_member_access_from_pointer
id|handler
c_func
(paren
id|irq
comma
id|node-&gt;dev_id
comma
id|fp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
r_return
suffix:semicolon
id|local_save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
(paren
id|flags
op_amp
op_complement
l_int|0x0700
)paren
op_or
(paren
id|fp-&gt;sr
op_amp
l_int|0x0700
)paren
)paren
suffix:semicolon
multiline_comment|/* if slow handlers exists, serve them now */
id|slow_nodes
op_assign
id|node
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|node
suffix:semicolon
id|node
op_assign
id|node-&gt;next
)paren
(brace
id|node
op_member_access_from_pointer
id|handler
c_func
(paren
id|irq
comma
id|node-&gt;dev_id
comma
id|fp
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  mac_enable_irq - enable an interrupt source&n; * mac_disable_irq - disable an interrupt source&n; *   mac_clear_irq - clears a pending interrupt&n; * mac_pending_irq - Returns the pending status of an IRQ (nonzero = pending)&n; *&n; * These routines are just dispatchers to the VIA/OSS/PSC routines.&n; */
DECL|function|mac_enable_irq
r_void
id|mac_enable_irq
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
id|irq_src
op_assign
id|IRQ_SRC
c_func
(paren
id|irq
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|irq_src
)paren
(brace
r_case
l_int|1
suffix:colon
id|via_irq_enable
c_func
(paren
id|irq
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_case
l_int|7
suffix:colon
r_if
c_cond
(paren
id|oss_present
)paren
(brace
id|oss_irq_enable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_else
(brace
id|via_irq_enable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_case
l_int|4
suffix:colon
r_case
l_int|5
suffix:colon
r_case
l_int|6
suffix:colon
r_if
c_cond
(paren
id|psc_present
)paren
(brace
id|psc_irq_enable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|oss_present
)paren
(brace
id|oss_irq_enable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|irq_src
op_eq
l_int|4
)paren
(brace
id|scc_irq_enable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
r_if
c_cond
(paren
id|baboon_present
)paren
(brace
id|baboon_irq_enable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
DECL|function|mac_disable_irq
r_void
id|mac_disable_irq
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
id|irq_src
op_assign
id|IRQ_SRC
c_func
(paren
id|irq
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|irq_src
)paren
(brace
r_case
l_int|1
suffix:colon
id|via_irq_disable
c_func
(paren
id|irq
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_case
l_int|7
suffix:colon
r_if
c_cond
(paren
id|oss_present
)paren
(brace
id|oss_irq_disable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_else
(brace
id|via_irq_disable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_case
l_int|4
suffix:colon
r_case
l_int|5
suffix:colon
r_case
l_int|6
suffix:colon
r_if
c_cond
(paren
id|psc_present
)paren
(brace
id|psc_irq_disable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|oss_present
)paren
(brace
id|oss_irq_disable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|irq_src
op_eq
l_int|4
)paren
(brace
id|scc_irq_disable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
r_if
c_cond
(paren
id|baboon_present
)paren
(brace
id|baboon_irq_disable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
DECL|function|mac_clear_irq
r_void
id|mac_clear_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_switch
c_cond
(paren
id|IRQ_SRC
c_func
(paren
id|irq
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
id|via_irq_clear
c_func
(paren
id|irq
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_case
l_int|7
suffix:colon
r_if
c_cond
(paren
id|oss_present
)paren
(brace
id|oss_irq_clear
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_else
(brace
id|via_irq_clear
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_case
l_int|4
suffix:colon
r_case
l_int|5
suffix:colon
r_case
l_int|6
suffix:colon
r_if
c_cond
(paren
id|psc_present
)paren
(brace
id|psc_irq_clear
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|oss_present
)paren
(brace
id|oss_irq_clear
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
r_if
c_cond
(paren
id|baboon_present
)paren
(brace
id|baboon_irq_clear
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
DECL|function|mac_irq_pending
r_int
id|mac_irq_pending
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_switch
c_cond
(paren
id|IRQ_SRC
c_func
(paren
id|irq
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
r_return
id|via_irq_pending
c_func
(paren
id|irq
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
r_case
l_int|7
suffix:colon
r_if
c_cond
(paren
id|oss_present
)paren
(brace
r_return
id|oss_irq_pending
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|via_irq_pending
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_case
l_int|3
suffix:colon
r_case
l_int|4
suffix:colon
r_case
l_int|5
suffix:colon
r_case
l_int|6
suffix:colon
r_if
c_cond
(paren
id|psc_present
)paren
(brace
r_return
id|psc_irq_pending
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|oss_present
)paren
(brace
r_return
id|oss_irq_pending
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Add an interrupt service routine to an interrupt source.&n; * Returns 0 on success.&n; *&n; * FIXME: You can register interrupts on nonexistent source (ie PSC4 on a&n; *        non-PSC machine). We should return -EINVAL in those cases.&n; */
DECL|function|mac_request_irq
r_int
id|mac_request_irq
c_func
(paren
r_int
r_int
id|irq
comma
id|irqreturn_t
(paren
op_star
id|handler
)paren
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
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|devname
comma
r_void
op_star
id|dev_id
)paren
(brace
id|irq_node_t
op_star
id|node
suffix:semicolon
macro_line|#ifdef DEBUG_MACINTS
id|printk
(paren
l_string|&quot;%s: irq %d requested for %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|devname
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|irq
OL
id|VIA1_SOURCE_BASE
)paren
(brace
r_return
id|cpu_request_irq
c_func
(paren
id|irq
comma
id|handler
comma
id|flags
comma
id|devname
comma
id|dev_id
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
op_ge
id|NUM_MAC_SOURCES
)paren
(brace
id|printk
(paren
l_string|&quot;%s: unknown irq %d requested by %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|devname
)paren
suffix:semicolon
)brace
multiline_comment|/* Get a node and stick it onto the right list */
r_if
c_cond
(paren
op_logical_neg
(paren
id|node
op_assign
id|new_irq_node
c_func
(paren
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|node-&gt;handler
op_assign
id|handler
suffix:semicolon
id|node-&gt;flags
op_assign
id|flags
suffix:semicolon
id|node-&gt;dev_id
op_assign
id|dev_id
suffix:semicolon
id|node-&gt;devname
op_assign
id|devname
suffix:semicolon
id|node-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|mac_insert_irq
c_func
(paren
op_amp
id|mac_irq_list
(braket
id|irq
)braket
comma
id|node
)paren
suffix:semicolon
multiline_comment|/* Now enable the IRQ source */
id|mac_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Removes an interrupt service routine from an interrupt source.&n; */
DECL|function|mac_free_irq
r_void
id|mac_free_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
(brace
macro_line|#ifdef DEBUG_MACINTS
id|printk
(paren
l_string|&quot;%s: irq %d freed by %p&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|dev_id
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|irq
OL
id|VIA1_SOURCE_BASE
)paren
(brace
r_return
id|cpu_free_irq
c_func
(paren
id|irq
comma
id|dev_id
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
op_ge
id|NUM_MAC_SOURCES
)paren
(brace
id|printk
(paren
l_string|&quot;%s: unknown irq %d freed&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|mac_delete_irq
c_func
(paren
op_amp
id|mac_irq_list
(braket
id|irq
)braket
comma
id|dev_id
)paren
suffix:semicolon
multiline_comment|/* If the list for this interrupt is */
multiline_comment|/* empty then disable the source.    */
r_if
c_cond
(paren
op_logical_neg
id|mac_irq_list
(braket
id|irq
)braket
)paren
(brace
id|mac_disable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Generate a pretty listing for /proc/interrupts&n; *&n; * By the time we&squot;re called the autovector interrupt list has already been&n; * generated, so we just need to do the machspec interrupts.&n; *&n; * 990506 (jmt) - rewritten to handle chained machspec interrupt handlers.&n; *                Also removed display of num_spurious it is already&n; *&t;&t;  displayed for us as autovector irq 0.&n; */
DECL|function|show_mac_interrupts
r_int
id|show_mac_interrupts
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
r_void
op_star
id|v
)paren
(brace
r_int
id|i
suffix:semicolon
id|irq_node_t
op_star
id|node
suffix:semicolon
r_char
op_star
id|base
suffix:semicolon
multiline_comment|/* Don&squot;t do Nubus interrupts in this loop; we do them separately  */
multiline_comment|/* below so that we can print slot numbers instead of IRQ numbers */
r_for
c_loop
(paren
id|i
op_assign
id|VIA1_SOURCE_BASE
suffix:semicolon
id|i
OL
id|NUM_MAC_SOURCES
suffix:semicolon
op_increment
id|i
)paren
(brace
multiline_comment|/* Nonexistant interrupt or nothing registered; skip it. */
r_if
c_cond
(paren
(paren
id|node
op_assign
id|mac_irq_list
(braket
id|i
)braket
)paren
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|node-&gt;flags
op_amp
id|IRQ_FLG_STD
)paren
r_continue
suffix:semicolon
id|base
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_switch
c_cond
(paren
id|IRQ_SRC
c_func
(paren
id|i
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
id|base
op_assign
l_string|&quot;via1&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
id|oss_present
)paren
(brace
id|base
op_assign
l_string|&quot;oss&quot;
suffix:semicolon
)brace
r_else
(brace
id|base
op_assign
l_string|&quot;via2&quot;
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_case
l_int|4
suffix:colon
r_case
l_int|5
suffix:colon
r_case
l_int|6
suffix:colon
r_if
c_cond
(paren
id|psc_present
)paren
(brace
id|base
op_assign
l_string|&quot;psc&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|oss_present
)paren
(brace
id|base
op_assign
l_string|&quot;oss&quot;
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|IRQ_SRC
c_func
(paren
id|i
)paren
op_eq
l_int|4
)paren
id|base
op_assign
l_string|&quot;scc&quot;
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|base
op_assign
l_string|&quot;nbus&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|base
op_assign
l_string|&quot;bbn&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%4s %2d: %10u &quot;
comma
id|base
comma
id|i
comma
id|kstat_cpu
c_func
(paren
l_int|0
)paren
dot
id|irqs
(braket
id|i
)braket
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|node-&gt;flags
op_amp
id|IRQ_FLG_FAST
)paren
(brace
id|seq_puts
c_func
(paren
id|p
comma
l_string|&quot;F &quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|node-&gt;flags
op_amp
id|IRQ_FLG_SLOW
)paren
(brace
id|seq_puts
c_func
(paren
id|p
comma
l_string|&quot;S &quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|seq_puts
c_func
(paren
id|p
comma
l_string|&quot;  &quot;
)paren
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|node-&gt;devname
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|node
op_assign
id|node-&gt;next
)paren
)paren
(brace
id|seq_puts
c_func
(paren
id|p
comma
l_string|&quot;                    &quot;
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|node
)paren
(brace
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mac_default_handler
r_void
id|mac_default_handler
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
macro_line|#ifdef DEBUG_SPURIOUS
id|printk
c_func
(paren
l_string|&quot;Unexpected IRQ %d on device %p&bslash;n&quot;
comma
id|irq
comma
id|dev_id
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|num_debug
r_static
r_int
id|num_debug
(braket
l_int|8
)braket
suffix:semicolon
DECL|function|mac_debug_handler
id|irqreturn_t
id|mac_debug_handler
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
r_if
c_cond
(paren
id|num_debug
(braket
id|irq
)braket
OL
l_int|10
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;DEBUG: Unexpected IRQ %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|num_debug
(braket
id|irq
)braket
op_increment
suffix:semicolon
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|variable|in_nmi
r_static
r_int
id|in_nmi
suffix:semicolon
DECL|variable|nmi_hold
r_static
r_volatile
r_int
id|nmi_hold
suffix:semicolon
DECL|function|mac_nmi_handler
id|irqreturn_t
id|mac_nmi_handler
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
id|fp
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* &n;&t; * generate debug output on NMI switch if &squot;debug&squot; kernel option given&n;&t; * (only works with Penguin!)&n;&t; */
id|in_nmi
op_increment
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
l_int|100
suffix:semicolon
id|i
op_increment
)paren
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in_nmi
op_eq
l_int|1
)paren
(brace
id|nmi_hold
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;... pausing, press NMI to resume ...&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot; ok!&bslash;n&quot;
)paren
suffix:semicolon
id|nmi_hold
op_assign
l_int|0
suffix:semicolon
)brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|nmi_hold
op_eq
l_int|1
)paren
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|console_loglevel
op_ge
l_int|8
)paren
(brace
macro_line|#if 0
id|show_state
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PC: %08lx&bslash;nSR: %04x  SP: %p&bslash;n&quot;
comma
id|fp-&gt;pc
comma
id|fp-&gt;sr
comma
id|fp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;d0: %08lx    d1: %08lx    d2: %08lx    d3: %08lx&bslash;n&quot;
comma
id|fp-&gt;d0
comma
id|fp-&gt;d1
comma
id|fp-&gt;d2
comma
id|fp-&gt;d3
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;d4: %08lx    d5: %08lx    a0: %08lx    a1: %08lx&bslash;n&quot;
comma
id|fp-&gt;d4
comma
id|fp-&gt;d5
comma
id|fp-&gt;a0
comma
id|fp-&gt;a1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|STACK_MAGIC
op_ne
op_star
(paren
r_int
r_int
op_star
)paren
id|current-&gt;kernel_stack_page
)paren
id|printk
c_func
(paren
l_string|&quot;Corrupted stack page&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Process %s (pid: %d, stackpage=%08lx)&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|current-&gt;kernel_stack_page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intr_count
op_eq
l_int|1
)paren
id|dump_stack
c_func
(paren
(paren
r_struct
id|frame
op_star
)paren
id|fp
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* printk(&quot;NMI &quot;); */
macro_line|#endif
)brace
id|in_nmi
op_decrement
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*&n; * Simple routines for masking and unmasking&n; * SCC interrupts in cases where this can&squot;t be&n; * done in hardware (only the PSC can do that.)&n; */
DECL|function|scc_irq_enable
r_static
r_void
id|scc_irq_enable
c_func
(paren
r_int
id|irq
)paren
(brace
r_int
id|irq_idx
op_assign
id|IRQ_IDX
c_func
(paren
id|irq
)paren
suffix:semicolon
id|scc_mask
op_or_assign
(paren
l_int|1
op_lshift
id|irq_idx
)paren
suffix:semicolon
)brace
DECL|function|scc_irq_disable
r_static
r_void
id|scc_irq_disable
c_func
(paren
r_int
id|irq
)paren
(brace
r_int
id|irq_idx
op_assign
id|IRQ_IDX
c_func
(paren
id|irq
)paren
suffix:semicolon
id|scc_mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq_idx
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * SCC master interrupt handler. We have to do a bit of magic here&n; * to figure out what channel gave us the interrupt; putting this&n; * here is cleaner than hacking it into drivers/char/macserial.c.&n; */
DECL|function|mac_scc_dispatch
r_void
id|mac_scc_dispatch
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
r_volatile
r_int
r_char
op_star
id|scc
op_assign
(paren
r_int
r_char
op_star
)paren
id|mac_bi_data.sccbase
op_plus
l_int|2
suffix:semicolon
r_int
r_char
id|reg
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Read RR3 from the chip. Always do this on channel A */
multiline_comment|/* This must be an atomic operation so disable irqs.   */
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
op_star
id|scc
op_assign
l_int|3
suffix:semicolon
id|reg
op_assign
op_star
id|scc
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* Now dispatch. Bits 0-2 are for channel B and */
multiline_comment|/* bits 3-5 are for channel A. We can safely    */
multiline_comment|/* ignore the remaining bits here.              */
multiline_comment|/*                                              */
multiline_comment|/* Note that we&squot;re ignoring scc_mask for now.   */
multiline_comment|/* If we actually mask the ints then we tend to */
multiline_comment|/* get hammered by very persistent SCC irqs,    */
multiline_comment|/* and since they&squot;re autovector interrupts they */
multiline_comment|/* pretty much kill the system.                 */
r_if
c_cond
(paren
id|reg
op_amp
l_int|0x38
)paren
id|mac_do_irq_list
c_func
(paren
id|IRQ_SCCA
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_amp
l_int|0x07
)paren
id|mac_do_irq_list
c_func
(paren
id|IRQ_SCCB
comma
id|regs
)paren
suffix:semicolon
)brace
eof
