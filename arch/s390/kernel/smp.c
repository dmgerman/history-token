multiline_comment|/*&n; *  arch/s390/kernel/smp.c&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com),&n; *               Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  based on other smp stuff by &n; *    (c) 1995 Alan Cox, CymruNET Ltd  &lt;alan@cymru.net&gt;&n; *    (c) 1998 Ingo Molnar&n; *&n; * We work with logical cpu numbering everywhere we can. The only&n; * functions using the real cpu address (got from STAP) are the sigp&n; * functions. For all other functions we use the identity mapping.&n; * That means that cpu_number_map[i] == i for every cpu. cpu_number_map is&n; * used e.g. to find the idle task belonging to a logical cpu. Every array&n; * in the kernel is sorted by the logical cpu number and not by the physical&n; * one which is causing all the confusion with __cpu_logical_map and&n; * cpu_number_map in other architectures.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;asm/sigp.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/s390_ext.h&gt;
macro_line|#include &lt;asm/cpcmd.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
multiline_comment|/* prototypes */
r_extern
r_int
id|cpu_idle
c_func
(paren
r_void
op_star
id|unused
)paren
suffix:semicolon
r_extern
r_volatile
r_int
id|__cpu_logical_map
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * An array with a pointer the lowcore of every CPU.&n; */
DECL|variable|lowcore_ptr
r_struct
id|_lowcore
op_star
id|lowcore_ptr
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|cacheflush_time
id|cycles_t
id|cacheflush_time
op_assign
l_int|0
suffix:semicolon
DECL|variable|smp_threads_ready
r_int
id|smp_threads_ready
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set when the idlers are all forked. */
DECL|variable|cpu_online_map
r_volatile
r_int
r_int
id|cpu_online_map
suffix:semicolon
DECL|variable|cpu_possible_map
r_volatile
r_int
r_int
id|cpu_possible_map
suffix:semicolon
DECL|variable|cache_decay_ticks
r_int
r_int
id|cache_decay_ticks
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Reboot, halt and power_off routines for SMP.&n; */
r_extern
r_char
id|vmhalt_cmd
(braket
)braket
suffix:semicolon
r_extern
r_char
id|vmpoff_cmd
(braket
)braket
suffix:semicolon
r_extern
r_void
id|do_reipl
c_func
(paren
r_int
r_int
id|devno
)paren
suffix:semicolon
r_static
id|sigp_ccode
id|smp_ext_bitcall
c_func
(paren
r_int
comma
id|ec_bit_sig
)paren
suffix:semicolon
r_static
r_void
id|smp_ext_bitcall_others
c_func
(paren
id|ec_bit_sig
)paren
suffix:semicolon
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
multiline_comment|/*&n; * &squot;Call function&squot; interrupt callback&n; */
DECL|function|do_call_function
r_static
r_void
id|do_call_function
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
id|atomic_inc
c_func
(paren
op_amp
id|call_data-&gt;started
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
r_if
c_cond
(paren
id|wait
)paren
id|atomic_inc
c_func
(paren
op_amp
id|call_data-&gt;finished
)paren
suffix:semicolon
)brace
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
multiline_comment|/* FIXME: get cpu lock -hc */
r_if
c_cond
(paren
id|cpus
op_le
l_int|0
)paren
r_return
l_int|0
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
multiline_comment|/* Send a message to all other CPUs and wait for them to respond */
id|smp_ext_bitcall_others
c_func
(paren
id|ec_call_function
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
DECL|function|do_send_stop
r_static
r_inline
r_void
id|do_send_stop
c_func
(paren
r_void
)paren
(brace
id|u32
id|dummy
suffix:semicolon
r_int
id|i
comma
id|rc
suffix:semicolon
multiline_comment|/* stop all processors */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|i
)paren
op_logical_or
id|smp_processor_id
c_func
(paren
)paren
op_eq
id|i
)paren
r_continue
suffix:semicolon
r_do
(brace
id|rc
op_assign
id|signal_processor_ps
c_func
(paren
op_amp
id|dummy
comma
l_int|0
comma
id|i
comma
id|sigp_stop
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|rc
op_eq
id|sigp_busy
)paren
suffix:semicolon
)brace
)brace
DECL|function|do_store_status
r_static
r_inline
r_void
id|do_store_status
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|low_core_addr
suffix:semicolon
id|u32
id|dummy
suffix:semicolon
r_int
id|i
comma
id|rc
suffix:semicolon
multiline_comment|/* store status of all processors in their lowcores (real 0) */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|i
)paren
op_logical_or
id|smp_processor_id
c_func
(paren
)paren
op_eq
id|i
)paren
r_continue
suffix:semicolon
id|low_core_addr
op_assign
(paren
r_int
r_int
)paren
id|lowcore_ptr
(braket
id|i
)braket
suffix:semicolon
r_do
(brace
id|rc
op_assign
id|signal_processor_ps
c_func
(paren
op_amp
id|dummy
comma
id|low_core_addr
comma
id|i
comma
id|sigp_store_status_at_address
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|rc
op_eq
id|sigp_busy
)paren
(brace
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * this function sends a &squot;stop&squot; sigp to all other CPUs in the system.&n; * it goes straight through.&n; */
DECL|function|smp_send_stop
r_void
id|smp_send_stop
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* write magic number to zero page (absolute 0) */
id|lowcore_ptr
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
op_member_access_from_pointer
id|panic_magic
op_assign
id|__PANIC_MAGIC
suffix:semicolon
multiline_comment|/* stop other processors. */
id|do_send_stop
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* store status of other processors. */
id|do_store_status
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Reboot, halt and power_off routines for SMP.&n; */
DECL|variable|cpu_restart_map
r_static
r_volatile
r_int
r_int
id|cpu_restart_map
suffix:semicolon
DECL|function|do_machine_restart
r_static
r_void
id|do_machine_restart
c_func
(paren
r_void
op_star
id|__unused
)paren
(brace
id|clear_bit
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
op_amp
id|cpu_restart_map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Wait for all other cpus to enter do_machine_restart. */
r_while
c_loop
(paren
id|cpu_restart_map
op_ne
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Store status of other cpus. */
id|do_store_status
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Finally call reipl. Because we waited for all other&n;&t;&t; * cpus to enter this function we know that they do&n;&t;&t; * not hold any s390irq-locks (the cpus have been&n;&t;&t; * interrupted by an external interrupt and s390irq&n;&t;&t; * locks are always held disabled).&n;&t;&t; */
r_if
c_cond
(paren
id|MACHINE_IS_VM
)paren
id|cpcmd
(paren
l_string|&quot;IPL&quot;
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_else
id|do_reipl
(paren
l_int|0x10000
op_or
id|S390_lowcore.ipl_device
)paren
suffix:semicolon
)brace
id|signal_processor
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|sigp_stop
)paren
suffix:semicolon
)brace
DECL|function|machine_restart_smp
r_void
id|machine_restart_smp
c_func
(paren
r_char
op_star
id|__unused
)paren
(brace
id|cpu_restart_map
op_assign
id|cpu_online_map
suffix:semicolon
id|smp_call_function
c_func
(paren
id|do_machine_restart
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|do_machine_restart
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|do_machine_halt
r_static
r_void
id|do_machine_halt
c_func
(paren
r_void
op_star
id|__unused
)paren
(brace
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_eq
l_int|0
)paren
(brace
id|smp_send_stop
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|MACHINE_IS_VM
op_logical_and
id|strlen
c_func
(paren
id|vmhalt_cmd
)paren
OG
l_int|0
)paren
id|cpcmd
c_func
(paren
id|vmhalt_cmd
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|signal_processor
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|sigp_stop_and_store_status
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
id|enabled_wait
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|machine_halt_smp
r_void
id|machine_halt_smp
c_func
(paren
r_void
)paren
(brace
id|smp_call_function
c_func
(paren
id|do_machine_halt
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|do_machine_halt
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|do_machine_power_off
r_static
r_void
id|do_machine_power_off
c_func
(paren
r_void
op_star
id|__unused
)paren
(brace
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_eq
l_int|0
)paren
(brace
id|smp_send_stop
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|MACHINE_IS_VM
op_logical_and
id|strlen
c_func
(paren
id|vmpoff_cmd
)paren
OG
l_int|0
)paren
id|cpcmd
c_func
(paren
id|vmpoff_cmd
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|signal_processor
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|sigp_stop_and_store_status
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
id|enabled_wait
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|machine_power_off_smp
r_void
id|machine_power_off_smp
c_func
(paren
r_void
)paren
(brace
id|smp_call_function
c_func
(paren
id|do_machine_power_off
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|do_machine_power_off
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the main routine where commands issued by other&n; * cpus are handled.&n; */
DECL|function|do_ext_call_interrupt
r_void
id|do_ext_call_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|__u16
id|code
)paren
(brace
r_int
r_int
id|bits
suffix:semicolon
multiline_comment|/*&n;         * handle bit signal external calls&n;         *&n;         * For the ec_schedule signal we have to do nothing. All the work&n;         * is done automatically when we return from the interrupt.&n;         */
id|bits
op_assign
id|xchg
c_func
(paren
op_amp
id|S390_lowcore.ext_call_fast
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|ec_call_function
comma
op_amp
id|bits
)paren
)paren
id|do_call_function
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Send an external call sigp to another cpu and return without waiting&n; * for its completion.&n; */
DECL|function|smp_ext_bitcall
r_static
id|sigp_ccode
id|smp_ext_bitcall
c_func
(paren
r_int
id|cpu
comma
id|ec_bit_sig
id|sig
)paren
(brace
id|sigp_ccode
id|ccode
suffix:semicolon
multiline_comment|/*&n;         * Set signaling bit in lowcore of target cpu and kick it&n;         */
id|set_bit
c_func
(paren
id|sig
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|lowcore_ptr
(braket
id|cpu
)braket
op_member_access_from_pointer
id|ext_call_fast
)paren
suffix:semicolon
id|ccode
op_assign
id|signal_processor
c_func
(paren
id|cpu
comma
id|sigp_external_call
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
multiline_comment|/*&n; * Send an external call sigp to every other cpu in the system and&n; * return without waiting for its completion.&n; */
DECL|function|smp_ext_bitcall_others
r_static
r_void
id|smp_ext_bitcall_others
c_func
(paren
id|ec_bit_sig
id|sig
)paren
(brace
r_struct
id|_lowcore
op_star
id|lowcore
suffix:semicolon
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
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|i
)paren
op_logical_or
id|smp_processor_id
c_func
(paren
)paren
op_eq
id|i
)paren
r_continue
suffix:semicolon
id|lowcore
op_assign
id|lowcore_ptr
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/*&n;                 * Set signaling bit in lowcore of target cpu and kick it&n;                 */
id|set_bit
c_func
(paren
id|sig
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|lowcore_ptr
(braket
id|i
)braket
op_member_access_from_pointer
id|ext_call_fast
)paren
suffix:semicolon
r_while
c_loop
(paren
id|signal_processor
c_func
(paren
id|i
comma
id|sigp_external_call
)paren
op_eq
id|sigp_busy
)paren
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * this function sends a &squot;purge tlb&squot; signal to another CPU.&n; */
DECL|function|smp_ptlb_callback
r_void
id|smp_ptlb_callback
c_func
(paren
r_void
op_star
id|info
)paren
(brace
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|smp_ptlb_all
r_void
id|smp_ptlb_all
c_func
(paren
r_void
)paren
(brace
id|smp_call_function
c_func
(paren
id|smp_ptlb_callback
comma
l_int|NULL
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|local_flush_tlb
c_func
(paren
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
id|smp_ext_bitcall
c_func
(paren
id|cpu
comma
id|ec_schedule
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * parameter area for the set/clear control bit callbacks&n; */
r_typedef
r_struct
(brace
DECL|member|start_ctl
id|__u16
id|start_ctl
suffix:semicolon
DECL|member|end_ctl
id|__u16
id|end_ctl
suffix:semicolon
DECL|member|orvals
id|__u32
id|orvals
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|andvals
id|__u32
id|andvals
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|ec_creg_mask_parms
)brace
id|ec_creg_mask_parms
suffix:semicolon
multiline_comment|/*&n; * callback for setting/clearing control bits&n; */
DECL|function|smp_ctl_bit_callback
r_void
id|smp_ctl_bit_callback
c_func
(paren
r_void
op_star
id|info
)paren
(brace
id|ec_creg_mask_parms
op_star
id|pp
suffix:semicolon
id|u32
id|cregs
(braket
l_int|16
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
id|pp
op_assign
(paren
id|ec_creg_mask_parms
op_star
)paren
id|info
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;   bras  1,0f&bslash;n&quot;
l_string|&quot;   stctl 0,0,0(%0)&bslash;n&quot;
l_string|&quot;0: ex    %1,0(1)&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|cregs
op_plus
id|pp-&gt;start_ctl
)paren
comma
l_string|&quot;a&quot;
(paren
(paren
id|pp-&gt;start_ctl
op_lshift
l_int|4
)paren
op_plus
id|pp-&gt;end_ctl
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|pp-&gt;start_ctl
suffix:semicolon
id|i
op_le
id|pp-&gt;end_ctl
suffix:semicolon
id|i
op_increment
)paren
id|cregs
(braket
id|i
)braket
op_assign
(paren
id|cregs
(braket
id|i
)braket
op_amp
id|pp-&gt;andvals
(braket
id|i
)braket
)paren
op_or
id|pp-&gt;orvals
(braket
id|i
)braket
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;   bras  1,0f&bslash;n&quot;
l_string|&quot;   lctl 0,0,0(%0)&bslash;n&quot;
l_string|&quot;0: ex    %1,0(1)&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|cregs
op_plus
id|pp-&gt;start_ctl
)paren
comma
l_string|&quot;a&quot;
(paren
(paren
id|pp-&gt;start_ctl
op_lshift
l_int|4
)paren
op_plus
id|pp-&gt;end_ctl
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Set a bit in a control register of all cpus&n; */
DECL|function|smp_ctl_set_bit
r_void
id|smp_ctl_set_bit
c_func
(paren
r_int
id|cr
comma
r_int
id|bit
)paren
(brace
id|ec_creg_mask_parms
id|parms
suffix:semicolon
id|parms.start_ctl
op_assign
id|cr
suffix:semicolon
id|parms.end_ctl
op_assign
id|cr
suffix:semicolon
id|parms.orvals
(braket
id|cr
)braket
op_assign
l_int|1
op_lshift
id|bit
suffix:semicolon
id|parms.andvals
(braket
id|cr
)braket
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
id|smp_call_function
c_func
(paren
id|smp_ctl_bit_callback
comma
op_amp
id|parms
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|__ctl_set_bit
c_func
(paren
id|cr
comma
id|bit
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Clear a bit in a control register of all cpus&n; */
DECL|function|smp_ctl_clear_bit
r_void
id|smp_ctl_clear_bit
c_func
(paren
r_int
id|cr
comma
r_int
id|bit
)paren
(brace
id|ec_creg_mask_parms
id|parms
suffix:semicolon
id|parms.start_ctl
op_assign
id|cr
suffix:semicolon
id|parms.end_ctl
op_assign
id|cr
suffix:semicolon
id|parms.orvals
(braket
id|cr
)braket
op_assign
l_int|0x00000000
suffix:semicolon
id|parms.andvals
(braket
id|cr
)braket
op_assign
op_complement
(paren
l_int|1
op_lshift
id|bit
)paren
suffix:semicolon
id|smp_call_function
c_func
(paren
id|smp_ctl_bit_callback
comma
op_amp
id|parms
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|__ctl_clear_bit
c_func
(paren
id|cr
comma
id|bit
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Lets check how many CPUs we have.&n; */
DECL|function|smp_check_cpus
r_void
id|__init
id|smp_check_cpus
c_func
(paren
r_int
r_int
id|max_cpus
)paren
(brace
r_int
id|curr_cpu
comma
id|num_cpus
suffix:semicolon
id|__u16
id|boot_cpu_addr
suffix:semicolon
id|boot_cpu_addr
op_assign
id|S390_lowcore.cpu_data.cpu_addr
suffix:semicolon
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|cpu
op_assign
l_int|0
suffix:semicolon
id|num_cpus
op_assign
l_int|1
suffix:semicolon
id|cpu_possible_map
op_assign
l_int|1
suffix:semicolon
id|cpu_online_map
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|curr_cpu
op_assign
l_int|0
suffix:semicolon
id|curr_cpu
op_le
l_int|65535
op_logical_and
id|num_cpus
OL
id|max_cpus
suffix:semicolon
id|curr_cpu
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|__u16
)paren
id|curr_cpu
op_eq
id|boot_cpu_addr
)paren
r_continue
suffix:semicolon
id|__cpu_logical_map
(braket
id|num_cpus
)braket
op_assign
(paren
id|__u16
)paren
id|curr_cpu
suffix:semicolon
r_if
c_cond
(paren
id|signal_processor
c_func
(paren
id|num_cpus
comma
id|sigp_sense
)paren
op_eq
id|sigp_not_operational
)paren
r_continue
suffix:semicolon
id|set_bit
c_func
(paren
id|num_cpus
comma
op_amp
id|cpu_possible_map
)paren
suffix:semicolon
id|num_cpus
op_increment
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Detected %d CPU&squot;s&bslash;n&quot;
comma
(paren
r_int
)paren
id|num_cpus
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Boot cpu address %2X&bslash;n&quot;
comma
id|boot_cpu_addr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *      Activate a secondary processor.&n; */
r_extern
r_void
id|init_cpu_timer
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pfault_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pfault_token
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|start_secondary
r_int
id|__devinit
id|start_secondary
c_func
(paren
r_void
op_star
id|cpuvoid
)paren
(brace
multiline_comment|/* Setup the cpu */
id|cpu_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* init per CPU timer */
id|init_cpu_timer
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PFAULT
multiline_comment|/* Enable pfault pseudo page faults on this cpu. */
id|pfault_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Mark this cpu as online */
id|set_bit
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
op_amp
id|cpu_online_map
)paren
suffix:semicolon
multiline_comment|/* Switch on interrupts */
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Print info about this processor */
id|print_cpu_info
c_func
(paren
op_amp
id|S390_lowcore.cpu_data
)paren
suffix:semicolon
multiline_comment|/* cpu_idle will call schedule for us */
r_return
id|cpu_idle
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|fork_by_hand
r_static
r_struct
id|task_struct
op_star
id|__devinit
id|fork_by_hand
c_func
(paren
r_void
)paren
(brace
r_struct
id|pt_regs
id|regs
suffix:semicolon
multiline_comment|/* don&squot;t care about the psw and regs settings since we&squot;ll never&n;          reschedule the forked task. */
id|memset
c_func
(paren
op_amp
id|regs
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
suffix:semicolon
r_return
id|do_fork
c_func
(paren
id|CLONE_VM
op_or
id|CLONE_IDLETASK
comma
l_int|0
comma
op_amp
id|regs
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|__cpu_up
r_int
id|__cpu_up
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
r_struct
id|task_struct
op_star
id|idle
suffix:semicolon
r_struct
id|_lowcore
op_star
id|cpu_lowcore
suffix:semicolon
id|sigp_ccode
id|ccode
suffix:semicolon
multiline_comment|/*&n;&t; *  Set prefix page for new cpu&n;&t; */
id|ccode
op_assign
id|signal_processor_p
c_func
(paren
(paren
id|u32
)paren
(paren
id|lowcore_ptr
(braket
id|cpu
)braket
)paren
comma
id|cpu
comma
id|sigp_set_prefix
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ccode
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sigp_set_prefix failed for cpu %d &quot;
l_string|&quot;with condition code %d&bslash;n&quot;
comma
(paren
r_int
)paren
id|cpu
comma
(paren
r_int
)paren
id|ccode
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* We can&squot;t use kernel_thread since we must _avoid_ to reschedule&n;           the child. */
id|idle
op_assign
id|fork_by_hand
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|idle
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;failed fork for CPU %d&quot;
comma
id|cpu
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/*&n;         * We remove it from the pidhash and the runqueue&n;         * once we got the process:&n;         */
id|init_idle
c_func
(paren
id|idle
comma
id|cpu
)paren
suffix:semicolon
id|unhash_process
c_func
(paren
id|idle
)paren
suffix:semicolon
id|cpu_lowcore
op_assign
id|lowcore_ptr
(braket
id|cpu
)braket
suffix:semicolon
id|cpu_lowcore-&gt;save_area
(braket
l_int|15
)braket
op_assign
id|idle-&gt;thread.ksp
suffix:semicolon
id|cpu_lowcore-&gt;kernel_stack
op_assign
(paren
id|__u32
)paren
id|idle-&gt;thread_info
op_plus
(paren
l_int|2
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;la    1,%0&bslash;n&bslash;t&quot;
l_string|&quot;stctl 0,15,0(1)&bslash;n&bslash;t&quot;
l_string|&quot;la    1,%1&bslash;n&bslash;t&quot;
l_string|&quot;stam  0,15,0(1)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|cpu_lowcore-&gt;cregs_save_area
(braket
l_int|0
)braket
)paren
comma
l_string|&quot;=m&quot;
(paren
id|cpu_lowcore-&gt;access_regs_save_area
(braket
l_int|0
)braket
)paren
suffix:colon
suffix:colon
l_string|&quot;1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|signal_processor
c_func
(paren
id|cpu
comma
id|sigp_restart
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Cycle through the processors and setup structures.&n; */
DECL|function|smp_prepare_cpus
r_void
id|__init
id|smp_prepare_cpus
c_func
(paren
r_int
r_int
id|max_cpus
)paren
(brace
r_int
r_int
id|async_stack
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* request the 0x1202 external interrupt */
r_if
c_cond
(paren
id|register_external_interrupt
c_func
(paren
l_int|0x1202
comma
id|do_ext_call_interrupt
)paren
op_ne
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t request external interrupt 0x1202&quot;
)paren
suffix:semicolon
id|smp_check_cpus
c_func
(paren
id|max_cpus
)paren
suffix:semicolon
id|memset
c_func
(paren
id|lowcore_ptr
comma
l_int|0
comma
r_sizeof
(paren
id|lowcore_ptr
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;         *  Initialize prefix pages and stacks for all possible cpus&n;         */
id|print_cpu_info
c_func
(paren
op_amp
id|S390_lowcore.cpu_data
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
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_possible
c_func
(paren
id|i
)paren
)paren
r_continue
suffix:semicolon
id|lowcore_ptr
(braket
id|i
)braket
op_assign
(paren
r_struct
id|_lowcore
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
op_or
id|GFP_DMA
)paren
suffix:semicolon
id|async_stack
op_assign
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lowcore_ptr
(braket
id|i
)braket
op_eq
l_int|NULL
op_logical_or
id|async_stack
op_eq
l_int|0UL
)paren
id|panic
c_func
(paren
l_string|&quot;smp_boot_cpus failed to allocate memory&bslash;n&quot;
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|lowcore_ptr
(braket
id|i
)braket
comma
op_amp
id|S390_lowcore
comma
r_sizeof
(paren
r_struct
id|_lowcore
)paren
)paren
suffix:semicolon
id|lowcore_ptr
(braket
id|i
)braket
op_member_access_from_pointer
id|async_stack
op_assign
id|async_stack
op_plus
(paren
l_int|2
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
id|set_prefix
c_func
(paren
(paren
id|u32
)paren
id|lowcore_ptr
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
)paren
suffix:semicolon
)brace
DECL|function|smp_prepare_boot_cpu
r_void
id|__devinit
id|smp_prepare_boot_cpu
c_func
(paren
r_void
)paren
(brace
id|set_bit
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
op_amp
id|cpu_online_map
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
op_amp
id|cpu_possible_map
)paren
suffix:semicolon
)brace
DECL|function|smp_cpus_done
r_void
id|smp_cpus_done
c_func
(paren
r_int
r_int
id|max_cpus
)paren
(brace
)brace
multiline_comment|/*&n; * the frequency of the profiling timer can be changed&n; * by writing a multiplier value into /proc/profile.&n; *&n; * usually you want to run this on all CPUs ;)&n; */
DECL|function|setup_profiling_timer
r_int
id|setup_profiling_timer
c_func
(paren
r_int
r_int
id|multiplier
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|lowcore_ptr
id|EXPORT_SYMBOL
c_func
(paren
id|lowcore_ptr
)paren
suffix:semicolon
DECL|variable|smp_ctl_set_bit
id|EXPORT_SYMBOL
c_func
(paren
id|smp_ctl_set_bit
)paren
suffix:semicolon
DECL|variable|smp_ctl_clear_bit
id|EXPORT_SYMBOL
c_func
(paren
id|smp_ctl_clear_bit
)paren
suffix:semicolon
DECL|variable|smp_call_function
id|EXPORT_SYMBOL
c_func
(paren
id|smp_call_function
)paren
suffix:semicolon
eof
