multiline_comment|/*&n; *&t;Intel SMP support routines.&n; *&n; *&t;(c) 1995 Alan Cox, Building #3 &lt;alan@redhat.com&gt;&n; *&t;(c) 1998-99, 2000 Ingo Molnar &lt;mingo@redhat.com&gt;&n; *      (c) 2002,2003 Andi Kleen, SuSE Labs.&n; *&n; *&t;This code is released under the GNU General Public License version 2 or&n; *&t;later.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/mtrr.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
multiline_comment|/*&n; * the following functions deal with sending IPIs between CPUs.&n; *&n; * We use &squot;broadcast&squot;, CPU-&gt;CPU IPIs and self-IPIs too.&n; */
DECL|function|__prepare_ICR
r_static
r_inline
r_int
r_int
id|__prepare_ICR
(paren
r_int
r_int
id|shortcut
comma
r_int
id|vector
)paren
(brace
r_int
r_int
id|icr
op_assign
id|APIC_DM_FIXED
op_or
id|shortcut
op_or
id|vector
op_or
id|APIC_DEST_LOGICAL
suffix:semicolon
r_if
c_cond
(paren
id|vector
op_eq
id|KDB_VECTOR
)paren
id|icr
op_assign
(paren
id|icr
op_amp
(paren
op_complement
id|APIC_VECTOR_MASK
)paren
)paren
op_or
id|APIC_DM_NMI
suffix:semicolon
r_return
id|icr
suffix:semicolon
)brace
DECL|function|__prepare_ICR2
r_static
r_inline
r_int
id|__prepare_ICR2
(paren
r_int
r_int
id|mask
)paren
(brace
r_return
id|SET_APIC_DEST_FIELD
c_func
(paren
id|mask
)paren
suffix:semicolon
)brace
DECL|function|__send_IPI_shortcut
r_static
r_inline
r_void
id|__send_IPI_shortcut
c_func
(paren
r_int
r_int
id|shortcut
comma
r_int
id|vector
)paren
(brace
multiline_comment|/*&n;&t; * Subtle. In the case of the &squot;never do double writes&squot; workaround&n;&t; * we have to lock out interrupts to be safe.  As we don&squot;t care&n;&t; * of the value read we use an atomic rmw access to avoid costly&n;&t; * cli/sti.  Otherwise we use an even cheaper single atomic write&n;&t; * to the APIC.&n;&t; */
r_int
r_int
id|cfg
suffix:semicolon
multiline_comment|/*&n;&t; * Wait for idle.&n;&t; */
id|apic_wait_icr_idle
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * No need to touch the target chip field&n;&t; */
id|cfg
op_assign
id|__prepare_ICR
c_func
(paren
id|shortcut
comma
id|vector
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
)brace
DECL|function|send_IPI_allbutself
r_static
r_inline
r_void
id|send_IPI_allbutself
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
)paren
suffix:semicolon
)brace
DECL|function|send_IPI_all
r_static
r_inline
r_void
id|send_IPI_all
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
)paren
suffix:semicolon
)brace
DECL|function|send_IPI_self
r_void
id|send_IPI_self
c_func
(paren
r_int
id|vector
)paren
(brace
id|__send_IPI_shortcut
c_func
(paren
id|APIC_DEST_SELF
comma
id|vector
)paren
suffix:semicolon
)brace
DECL|function|send_IPI_mask
r_static
r_inline
r_void
id|send_IPI_mask
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
multiline_comment|/*&n;&t; * program the ICR &n;&t; */
id|cfg
op_assign
id|__prepare_ICR
c_func
(paren
l_int|0
comma
id|vector
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
multiline_comment|/*&n; *&t;Smarter SMP flushing macros. &n; *&t;&t;c/o Linus Torvalds.&n; *&n; *&t;These mean you can really definitely utterly forget about&n; *&t;writing to user space from interrupts. (Its not allowed anyway).&n; *&n; *&t;Optimizations Manfred Spraul &lt;manfred@colorfullife.com&gt;&n; */
DECL|variable|flush_cpumask
r_static
id|cpumask_t
id|flush_cpumask
suffix:semicolon
DECL|variable|flush_mm
r_static
r_struct
id|mm_struct
op_star
id|flush_mm
suffix:semicolon
DECL|variable|flush_va
r_static
r_int
r_int
id|flush_va
suffix:semicolon
DECL|variable|tlbstate_lock
r_static
id|spinlock_t
id|tlbstate_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|FLUSH_ALL
mdefine_line|#define FLUSH_ALL&t;0xffffffff
multiline_comment|/*&n; * We cannot call mmdrop() because we are in interrupt context, &n; * instead update mm-&gt;cpu_vm_mask.&n; */
DECL|function|leave_mm
r_static
r_inline
r_void
id|leave_mm
(paren
r_int
r_int
id|cpu
)paren
(brace
r_if
c_cond
(paren
id|read_pda
c_func
(paren
id|mmu_state
)paren
op_eq
id|TLBSTATE_OK
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|cpu
comma
op_amp
id|read_pda
c_func
(paren
id|active_mm
)paren
op_member_access_from_pointer
id|cpu_vm_mask
)paren
suffix:semicolon
id|__flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&n; * The flush IPI assumes that a thread switch happens in this order:&n; * [cpu0: the cpu that switches]&n; * 1) switch_mm() either 1a) or 1b)&n; * 1a) thread switch to a different mm&n; * 1a1) clear_bit(cpu, &amp;old_mm-&gt;cpu_vm_mask);&n; * &t;Stop ipi delivery for the old mm. This is not synchronized with&n; * &t;the other cpus, but smp_invalidate_interrupt ignore flush ipis&n; * &t;for the wrong mm, and in the worst case we perform a superfluous&n; * &t;tlb flush.&n; * 1a2) set cpu mmu_state to TLBSTATE_OK&n; * &t;Now the smp_invalidate_interrupt won&squot;t call leave_mm if cpu0&n; *&t;was in lazy tlb mode.&n; * 1a3) update cpu active_mm&n; * &t;Now cpu0 accepts tlb flushes for the new mm.&n; * 1a4) set_bit(cpu, &amp;new_mm-&gt;cpu_vm_mask);&n; * &t;Now the other cpus will send tlb flush ipis.&n; * 1a4) change cr3.&n; * 1b) thread switch without mm change&n; *&t;cpu active_mm is correct, cpu0 already handles&n; *&t;flush ipis.&n; * 1b1) set cpu mmu_state to TLBSTATE_OK&n; * 1b2) test_and_set the cpu bit in cpu_vm_mask.&n; * &t;Atomically set the bit [other cpus will start sending flush ipis],&n; * &t;and test the bit.&n; * 1b3) if the bit was 0: leave_mm was called, flush the tlb.&n; * 2) switch %%esp, ie current&n; *&n; * The interrupt must handle 2 special cases:&n; * - cr3 is changed before %%esp, ie. it cannot use current-&gt;{active_,}mm.&n; * - the cpu performs speculative tlb reads, i.e. even if the cpu only&n; *   runs in kernel space, the cpu could load tlb entries for user space&n; *   pages.&n; *&n; * The good news is that cpu mmu_state is local to each cpu, no&n; * write/read ordering problems.&n; */
multiline_comment|/*&n; * TLB flush IPI:&n; *&n; * 1) Flush the tlb entries if the cpu uses the mm that&squot;s being flushed.&n; * 2) Leave the mm if we are in the lazy tlb mode.&n; */
DECL|function|smp_invalidate_interrupt
id|asmlinkage
r_void
id|smp_invalidate_interrupt
(paren
r_void
)paren
(brace
r_int
r_int
id|cpu
suffix:semicolon
id|cpu
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_isset
c_func
(paren
id|cpu
comma
id|flush_cpumask
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* &n;&t;&t; * This was a BUG() but until someone can quote me the&n;&t;&t; * line from the intel manual that guarantees an IPI to&n;&t;&t; * multiple CPUs is retried _only_ on the erroring CPUs&n;&t;&t; * its staying as a return&n;&t;&t; *&n;&t;&t; * BUG();&n;&t;&t; */
r_if
c_cond
(paren
id|flush_mm
op_eq
id|read_pda
c_func
(paren
id|active_mm
)paren
)paren
(brace
r_if
c_cond
(paren
id|read_pda
c_func
(paren
id|mmu_state
)paren
op_eq
id|TLBSTATE_OK
)paren
(brace
r_if
c_cond
(paren
id|flush_va
op_eq
id|FLUSH_ALL
)paren
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
r_else
id|__flush_tlb_one
c_func
(paren
id|flush_va
)paren
suffix:semicolon
)brace
r_else
id|leave_mm
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
id|ack_APIC_irq
c_func
(paren
)paren
suffix:semicolon
id|cpu_clear
c_func
(paren
id|cpu
comma
id|flush_cpumask
)paren
suffix:semicolon
id|out
suffix:colon
id|put_cpu_no_resched
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_others
r_static
r_void
id|flush_tlb_others
c_func
(paren
id|cpumask_t
id|cpumask
comma
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|va
)paren
(brace
id|cpumask_t
id|tmp
suffix:semicolon
multiline_comment|/*&n;&t; * A couple of (to be removed) sanity checks:&n;&t; *&n;&t; * - we do not send IPIs to not-yet booted CPUs.&n;&t; * - current CPU must not be in mask&n;&t; * - mask must exist :)&n;&t; */
id|BUG_ON
c_func
(paren
id|cpus_empty
c_func
(paren
id|cpumask
)paren
)paren
suffix:semicolon
id|cpus_and
c_func
(paren
id|tmp
comma
id|cpumask
comma
id|cpu_online_map
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|cpus_equal
c_func
(paren
id|tmp
comma
id|cpumask
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|cpu_isset
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|cpumask
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mm
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * I&squot;m not happy about this global shared spinlock in the&n;&t; * MM hot path, but we&squot;ll see how contended it is.&n;&t; * Temporarily this turns IRQs off, so that lockups are&n;&t; * detected by the NMI watchdog.&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|tlbstate_lock
)paren
suffix:semicolon
id|flush_mm
op_assign
id|mm
suffix:semicolon
id|flush_va
op_assign
id|va
suffix:semicolon
id|cpus_or
c_func
(paren
id|flush_cpumask
comma
id|cpumask
comma
id|flush_cpumask
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We have to send the IPI only to&n;&t; * CPUs affected.&n;&t; */
id|send_IPI_mask
c_func
(paren
id|cpumask
comma
id|INVALIDATE_TLB_VECTOR
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|cpus_empty
c_func
(paren
id|flush_cpumask
)paren
)paren
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* nothing. lockup detection does not belong here */
suffix:semicolon
id|flush_mm
op_assign
l_int|NULL
suffix:semicolon
id|flush_va
op_assign
l_int|0
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|tlbstate_lock
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_current_task
r_void
id|flush_tlb_current_task
c_func
(paren
r_void
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
id|cpumask_t
id|cpu_mask
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|cpu_mask
op_assign
id|mm-&gt;cpu_vm_mask
suffix:semicolon
id|cpu_clear
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|cpu_mask
)paren
suffix:semicolon
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpus_empty
c_func
(paren
id|cpu_mask
)paren
)paren
id|flush_tlb_others
c_func
(paren
id|cpu_mask
comma
id|mm
comma
id|FLUSH_ALL
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_mm
r_void
id|flush_tlb_mm
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|cpumask_t
id|cpu_mask
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|cpu_mask
op_assign
id|mm-&gt;cpu_vm_mask
suffix:semicolon
id|cpu_clear
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|cpu_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;active_mm
op_eq
id|mm
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;mm
)paren
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
r_else
id|leave_mm
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cpus_empty
c_func
(paren
id|cpu_mask
)paren
)paren
id|flush_tlb_others
c_func
(paren
id|cpu_mask
comma
id|mm
comma
id|FLUSH_ALL
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_page
r_void
id|flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|va
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
id|cpumask_t
id|cpu_mask
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|cpu_mask
op_assign
id|mm-&gt;cpu_vm_mask
suffix:semicolon
id|cpu_clear
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|cpu_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;active_mm
op_eq
id|mm
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;mm
)paren
(brace
id|__flush_tlb_one
c_func
(paren
id|va
)paren
suffix:semicolon
)brace
r_else
id|leave_mm
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cpus_empty
c_func
(paren
id|cpu_mask
)paren
)paren
id|flush_tlb_others
c_func
(paren
id|cpu_mask
comma
id|mm
comma
id|va
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_flush_tlb_all
r_static
r_void
id|do_flush_tlb_all
c_func
(paren
r_void
op_star
id|info
)paren
(brace
r_int
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|__flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_pda
c_func
(paren
id|mmu_state
)paren
op_eq
id|TLBSTATE_LAZY
)paren
id|leave_mm
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
DECL|function|flush_tlb_all
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
(brace
id|on_each_cpu
c_func
(paren
id|do_flush_tlb_all
comma
l_int|NULL
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|smp_kdb_stop
r_void
id|smp_kdb_stop
c_func
(paren
r_void
)paren
(brace
id|send_IPI_allbutself
c_func
(paren
id|KDB_VECTOR
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * this function sends a &squot;reschedule&squot; IPI to another CPU.&n; * it goes straight through and wastes no time serializing&n; * anything. Worst case is that we lose a reschedule ...&n; */
DECL|function|smp_send_reschedule
r_void
id|smp_send_reschedule
c_func
(paren
r_int
id|cpu
)paren
(brace
id|send_IPI_mask
c_func
(paren
id|cpumask_of_cpu
c_func
(paren
id|cpu
)paren
comma
id|RESCHEDULE_VECTOR
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Structure and data for smp_call_function(). This is designed to minimise&n; * static memory requirements. It also looks cleaner.&n; */
DECL|variable|call_lock
r_static
id|spinlock_t
id|call_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|struct|call_data_struct
r_struct
id|call_data_struct
(brace
DECL|member|func
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
id|info
)paren
suffix:semicolon
DECL|member|info
r_void
op_star
id|info
suffix:semicolon
DECL|member|started
id|atomic_t
id|started
suffix:semicolon
DECL|member|finished
id|atomic_t
id|finished
suffix:semicolon
DECL|member|wait
r_int
id|wait
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|call_data
r_static
r_struct
id|call_data_struct
op_star
id|call_data
suffix:semicolon
multiline_comment|/*&n; * this function sends a &squot;generic call function&squot; IPI to all other CPUs&n; * in the system.&n; */
DECL|function|smp_call_function
r_int
id|smp_call_function
(paren
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
id|info
)paren
comma
r_void
op_star
id|info
comma
r_int
id|nonatomic
comma
r_int
id|wait
)paren
multiline_comment|/*&n; * [SUMMARY] Run a function on all other CPUs.&n; * &lt;func&gt; The function to run. This must be fast and non-blocking.&n; * &lt;info&gt; An arbitrary pointer to pass to the function.&n; * &lt;nonatomic&gt; currently unused.&n; * &lt;wait&gt; If true, wait (atomically) until function has completed on other CPUs.&n; * [RETURNS] 0 on success, else a negative status code. Does not return until&n; * remote CPUs are nearly ready to execute &lt;&lt;func&gt;&gt; or are or have executed.&n; *&n; * You must not call this function with disabled interrupts or from a&n; * hardware interrupt handler or from a bottom half handler.&n; */
(brace
r_struct
id|call_data_struct
id|data
suffix:semicolon
r_int
id|cpus
op_assign
id|num_online_cpus
c_func
(paren
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpus
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Can deadlock when called with interrupts disabled */
id|WARN_ON
c_func
(paren
id|irqs_disabled
c_func
(paren
)paren
)paren
suffix:semicolon
id|data.func
op_assign
id|func
suffix:semicolon
id|data.info
op_assign
id|info
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|data.started
comma
l_int|0
)paren
suffix:semicolon
id|data.wait
op_assign
id|wait
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
id|atomic_set
c_func
(paren
op_amp
id|data.finished
comma
l_int|0
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|call_lock
)paren
suffix:semicolon
id|call_data
op_assign
op_amp
id|data
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Send a message to all other CPUs and wait for them to respond */
id|send_IPI_allbutself
c_func
(paren
id|CALL_FUNCTION_VECTOR
)paren
suffix:semicolon
multiline_comment|/* Wait for response */
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|data.started
)paren
op_ne
id|cpus
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|data.finished
)paren
op_ne
id|cpus
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|call_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|smp_stop_cpu
r_void
id|smp_stop_cpu
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Remove this CPU:&n;&t; */
id|cpu_clear
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|cpu_online_map
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|disable_local_APIC
c_func
(paren
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|smp_really_stop_cpu
r_static
r_void
id|smp_really_stop_cpu
c_func
(paren
r_void
op_star
id|dummy
)paren
(brace
id|smp_stop_cpu
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
id|asm
c_func
(paren
l_string|&quot;hlt&quot;
)paren
suffix:semicolon
)brace
DECL|function|smp_send_stop
r_void
id|smp_send_stop
c_func
(paren
r_void
)paren
(brace
id|smp_call_function
c_func
(paren
id|smp_really_stop_cpu
comma
l_int|NULL
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|smp_stop_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Reschedule call back. Nothing to do,&n; * all the work is done automatically when&n; * we return from the interrupt.&n; */
DECL|function|smp_reschedule_interrupt
id|asmlinkage
r_void
id|smp_reschedule_interrupt
c_func
(paren
r_void
)paren
(brace
id|ack_APIC_irq
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|smp_call_function_interrupt
id|asmlinkage
r_void
id|smp_call_function_interrupt
c_func
(paren
r_void
)paren
(brace
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
id|info
)paren
op_assign
id|call_data-&gt;func
suffix:semicolon
r_void
op_star
id|info
op_assign
id|call_data-&gt;info
suffix:semicolon
r_int
id|wait
op_assign
id|call_data-&gt;wait
suffix:semicolon
id|ack_APIC_irq
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Notify initiating CPU that I&squot;ve grabbed the data and am&n;&t; * about to execute the function&n;&t; */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|call_data-&gt;started
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * At this point the info structure may be out of scope unless wait==1&n;&t; */
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
(paren
op_star
id|func
)paren
(paren
id|info
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
(brace
id|mb
c_func
(paren
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|call_data-&gt;finished
)paren
suffix:semicolon
)brace
)brace
eof
