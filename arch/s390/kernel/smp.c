multiline_comment|/*&n; *  arch/s390/kernel/smp.c&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com),&n; *               Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  based on other smp stuff by &n; *    (c) 1995 Alan Cox, CymruNET Ltd  &lt;alan@cymru.net&gt;&n; *    (c) 1998 Ingo Molnar&n; *&n; * We work with logical cpu numbering everywhere we can. The only&n; * functions using the real cpu address (got from STAP) are the sigp&n; * functions. For all other functions we use the identity mapping.&n; * That means that cpu_number_map[i] == i for every cpu. cpu_number_map is&n; * used e.g. to find the idle task belonging to a logical cpu. Every array&n; * in the kernel is sorted by the logical cpu number and not by the physical&n; * one which is causing all the confusion with __cpu_logical_map and&n; * cpu_number_map in other architectures.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/sigp.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/s390_ext.h&gt;
macro_line|#include &lt;asm/cpcmd.h&gt;
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
id|__u16
id|boot_cpu_addr
suffix:semicolon
r_extern
r_volatile
r_int
id|__cpu_logical_map
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * An array with a pointer the lowcore of every CPU.&n; */
DECL|variable|max_cpus
r_static
r_int
id|max_cpus
op_assign
id|NR_CPUS
suffix:semicolon
multiline_comment|/* Setup configured maximum number of CPUs to activate&t;*/
DECL|variable|smp_num_cpus
r_int
id|smp_num_cpus
suffix:semicolon
DECL|variable|lowcore_ptr
r_struct
id|_lowcore
op_star
id|lowcore_ptr
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|prof_multiplier
r_int
r_int
id|prof_multiplier
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|prof_old_multiplier
r_int
r_int
id|prof_old_multiplier
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|prof_counter
r_int
r_int
id|prof_counter
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
DECL|variable|smp_commenced
r_static
id|atomic_t
id|smp_commenced
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
DECL|variable|kernel_flag
id|spinlock_t
id|kernel_flag
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; *      Setup routine for controlling SMP activation&n; *&n; *      Command-line option of &quot;nosmp&quot; or &quot;maxcpus=0&quot; will disable SMP&n; *      activation entirely (the MPS table probe still happens, though).&n; *&n; *      Command-line option of &quot;maxcpus=&lt;NUM&gt;&quot;, where &lt;NUM&gt; is an integer&n; *      greater than 0, limits the maximum number of CPUs activated in&n; *      SMP mode to &lt;NUM&gt;.&n; */
DECL|function|nosmp
r_static
r_int
id|__init
id|nosmp
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|max_cpus
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;nosmp&quot;
comma
id|nosmp
)paren
suffix:semicolon
DECL|function|maxcpus
r_static
r_int
id|__init
id|maxcpus
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|max_cpus
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;maxcpus=&quot;
comma
id|maxcpus
)paren
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
id|reipl
c_func
(paren
r_int
r_int
id|devno
)paren
suffix:semicolon
DECL|function|do_machine_restart
r_void
id|do_machine_restart
c_func
(paren
r_void
)paren
(brace
id|smp_send_stop
c_func
(paren
)paren
suffix:semicolon
id|reipl
c_func
(paren
id|S390_lowcore.ipl_device
)paren
suffix:semicolon
)brace
DECL|function|machine_restart
r_void
id|machine_restart
c_func
(paren
r_char
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
op_ne
l_int|0
)paren
(brace
id|smp_ext_bitcall
c_func
(paren
l_int|0
comma
id|ec_restart
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
r_else
id|do_machine_restart
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_machine_halt
r_void
id|do_machine_halt
c_func
(paren
r_void
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
DECL|function|machine_halt
r_void
id|machine_halt
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_ne
l_int|0
)paren
(brace
id|smp_ext_bitcall
c_func
(paren
l_int|0
comma
id|ec_halt
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
r_else
id|do_machine_halt
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_machine_power_off
r_void
id|do_machine_power_off
c_func
(paren
r_void
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
DECL|function|machine_power_off
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_ne
l_int|0
)paren
(brace
id|smp_ext_bitcall
c_func
(paren
l_int|0
comma
id|ec_power_off
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
r_else
id|do_machine_power_off
c_func
(paren
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
id|ec_ext_call
op_star
id|ec
comma
op_star
id|next
suffix:semicolon
r_int
id|bits
suffix:semicolon
multiline_comment|/*&n;         * handle bit signal external calls&n;         *&n;         * For the ec_schedule signal we have to do nothing. All the work&n;         * is done automatically when we return from the interrupt.&n;&t; * For the ec_restart, ec_halt and ec_power_off we call the&n;         * appropriate routine.&n;         */
r_do
(brace
id|bits
op_assign
id|atomic_read
c_func
(paren
op_amp
id|S390_lowcore.ext_call_fast
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|atomic_compare_and_swap
c_func
(paren
id|bits
comma
l_int|0
comma
op_amp
id|S390_lowcore.ext_call_fast
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|ec_restart
comma
op_amp
id|bits
)paren
)paren
id|do_machine_restart
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|ec_halt
comma
op_amp
id|bits
)paren
)paren
id|do_machine_halt
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|ec_power_off
comma
op_amp
id|bits
)paren
)paren
id|do_machine_power_off
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|ec_ptlb
comma
op_amp
id|bits
)paren
)paren
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;         * Handle external call commands with a parameter area&n;         */
r_do
(brace
id|ec
op_assign
(paren
id|ec_ext_call
op_star
)paren
id|atomic_read
c_func
(paren
op_amp
id|S390_lowcore.ext_call_queue
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|atomic_compare_and_swap
c_func
(paren
(paren
r_int
)paren
id|ec
comma
l_int|0
comma
op_amp
id|S390_lowcore.ext_call_queue
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ec
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
multiline_comment|/* no command signals */
multiline_comment|/* Make a fifo out of the lifo */
id|next
op_assign
id|ec-&gt;next
suffix:semicolon
id|ec-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|next
op_ne
l_int|NULL
)paren
(brace
id|ec_ext_call
op_star
id|tmp
op_assign
id|next-&gt;next
suffix:semicolon
id|next-&gt;next
op_assign
id|ec
suffix:semicolon
id|ec
op_assign
id|next
suffix:semicolon
id|next
op_assign
id|tmp
suffix:semicolon
)brace
multiline_comment|/* Execute every sigp command on the queue */
r_while
c_loop
(paren
id|ec
op_ne
l_int|NULL
)paren
(brace
r_switch
c_cond
(paren
id|ec-&gt;cmd
)paren
(brace
r_case
id|ec_callback_async
suffix:colon
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
suffix:semicolon
r_void
op_star
id|info
suffix:semicolon
id|func
op_assign
id|ec-&gt;func
suffix:semicolon
id|info
op_assign
id|ec-&gt;info
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|ec-&gt;status
comma
id|ec_executing
)paren
suffix:semicolon
(paren
id|func
)paren
(paren
id|info
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_case
id|ec_callback_sync
suffix:colon
id|atomic_set
c_func
(paren
op_amp
id|ec-&gt;status
comma
id|ec_executing
)paren
suffix:semicolon
(paren
id|ec-&gt;func
)paren
(paren
id|ec-&gt;info
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|ec-&gt;status
comma
id|ec_done
)paren
suffix:semicolon
r_return
suffix:semicolon
r_default
suffix:colon
(brace
)brace
)brace
id|ec
op_assign
id|ec-&gt;next
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Send a callback sigp to another cpu.&n; */
id|sigp_ccode
DECL|function|smp_ext_call
id|smp_ext_call
c_func
(paren
r_int
id|cpu
comma
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
id|wait
)paren
(brace
r_struct
id|_lowcore
op_star
id|lowcore
op_assign
op_amp
id|get_cpu_lowcore
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|sigp_ccode
id|ccode
suffix:semicolon
id|ec_ext_call
id|ec
suffix:semicolon
id|ec.cmd
op_assign
id|wait
ques
c_cond
id|ec_callback_sync
suffix:colon
id|ec_callback_async
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|ec.status
comma
id|ec_pending
)paren
suffix:semicolon
id|ec.func
op_assign
id|func
suffix:semicolon
id|ec.info
op_assign
id|info
suffix:semicolon
r_do
(brace
id|ec.next
op_assign
(paren
id|ec_ext_call
op_star
)paren
id|atomic_read
c_func
(paren
op_amp
id|lowcore-&gt;ext_call_queue
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|atomic_compare_and_swap
c_func
(paren
(paren
r_int
)paren
id|ec.next
comma
(paren
r_int
)paren
(paren
op_amp
id|ec
)paren
comma
op_amp
id|lowcore-&gt;ext_call_queue
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;         * We try once to deliver the signal. There are four possible&n;         * return codes:&n;         * 0) Order code accepted - can&squot;t show up on an external call&n;         * 1) Status stored - fine, wait for completion.&n;         * 2) Busy - there is another signal pending. Thats fine too, because&n;         *    do_ext_call from the pending signal will execute all signals on&n;         *    the queue. We wait for completion.&n;         * 3) Not operational - something very bad has happened to the cpu.&n;         *    do not wait for completion.&n;         */
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
r_if
c_cond
(paren
id|ccode
op_ne
id|sigp_not_operational
)paren
multiline_comment|/* wait for completion, FIXME: possible seed of a deadlock */
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|ec.status
)paren
op_ne
(paren
id|wait
ques
c_cond
id|ec_done
suffix:colon
id|ec_executing
)paren
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
multiline_comment|/*&n; * Send a callback sigp to every other cpu in the system.&n; */
DECL|function|smp_ext_call_others
r_void
id|smp_ext_call_others
c_func
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
id|wait
)paren
(brace
r_struct
id|_lowcore
op_star
id|lowcore
suffix:semicolon
id|ec_ext_call
id|ec
(braket
id|NR_CPUS
)braket
suffix:semicolon
id|sigp_ccode
id|ccode
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
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
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
id|i
)paren
r_continue
suffix:semicolon
id|lowcore
op_assign
op_amp
id|get_cpu_lowcore
c_func
(paren
id|i
)paren
suffix:semicolon
id|ec
(braket
id|i
)braket
dot
id|cmd
op_assign
id|wait
ques
c_cond
id|ec_callback_sync
suffix:colon
id|ec_callback_async
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|ec
(braket
id|i
)braket
dot
id|status
comma
id|ec_pending
)paren
suffix:semicolon
id|ec
(braket
id|i
)braket
dot
id|func
op_assign
id|func
suffix:semicolon
id|ec
(braket
id|i
)braket
dot
id|info
op_assign
id|info
suffix:semicolon
r_do
(brace
id|ec
(braket
id|i
)braket
dot
id|next
op_assign
(paren
id|ec_ext_call
op_star
)paren
id|atomic_read
c_func
(paren
op_amp
id|lowcore-&gt;ext_call_queue
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|atomic_compare_and_swap
c_func
(paren
(paren
r_int
)paren
id|ec
(braket
id|i
)braket
dot
id|next
comma
(paren
r_int
)paren
(paren
id|ec
op_plus
id|i
)paren
comma
op_amp
id|lowcore-&gt;ext_call_queue
)paren
)paren
suffix:semicolon
id|ccode
op_assign
id|signal_processor
c_func
(paren
id|i
comma
id|sigp_external_call
)paren
suffix:semicolon
)brace
multiline_comment|/* wait for completion, FIXME: possible seed of a deadlock */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
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
id|i
)paren
r_continue
suffix:semicolon
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|ec
(braket
id|i
)braket
dot
id|status
)paren
op_ne
(paren
id|wait
ques
c_cond
id|ec_done
suffix:colon
id|ec_executing
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Send an external call sigp to another cpu and return without waiting&n; * for its completion.&n; */
DECL|function|smp_ext_bitcall
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
r_struct
id|_lowcore
op_star
id|lowcore
op_assign
op_amp
id|get_cpu_lowcore
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|sigp_ccode
id|ccode
suffix:semicolon
multiline_comment|/*&n;         * Set signaling bit in lowcore of target cpu and kick it&n;         */
id|atomic_set_mask
c_func
(paren
l_int|1
op_lshift
id|sig
comma
op_amp
id|lowcore-&gt;ext_call_fast
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
id|sigp_ccode
id|ccode
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
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
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
id|i
)paren
r_continue
suffix:semicolon
id|lowcore
op_assign
op_amp
id|get_cpu_lowcore
c_func
(paren
id|i
)paren
suffix:semicolon
multiline_comment|/*&n;                 * Set signaling bit in lowcore of target cpu and kick it&n;                 */
id|atomic_set_mask
c_func
(paren
l_int|1
op_lshift
id|sig
comma
op_amp
id|lowcore-&gt;ext_call_fast
)paren
suffix:semicolon
id|ccode
op_assign
id|signal_processor
c_func
(paren
id|i
comma
id|sigp_external_call
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * cycles through all the cpus,&n; * returns early if info is not NULL &amp; the processor has something&n; * of intrest to report in the info structure.&n; * it returns the next cpu to check if it returns early.&n; * i.e. it should be used as follows if you wish to receive info.&n; * next_cpu=0;&n; * do&n; * {&n; *    info-&gt;cpu=next_cpu;&n; *    next_cpu=smp_signal_others(order_code,parameter,1,info);&n; *    ... check info here&n; * } while(next_cpu&lt;=smp_num_cpus)&n; *&n; *  if you are lazy just use it like&n; * smp_signal_others(order_code,parameter,0,1,NULL);&n; */
DECL|function|smp_signal_others
r_int
id|smp_signal_others
c_func
(paren
id|sigp_order_code
id|order_code
comma
id|u32
id|parameter
comma
r_int
id|spin
comma
id|sigp_info
op_star
id|info
)paren
(brace
id|sigp_ccode
id|ccode
suffix:semicolon
id|u32
id|dummy
suffix:semicolon
id|u16
id|i
suffix:semicolon
r_if
c_cond
(paren
id|info
)paren
id|info-&gt;intresting
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
(paren
id|info
ques
c_cond
id|info-&gt;cpu
suffix:colon
l_int|0
)paren
suffix:semicolon
id|i
OL
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_ne
id|i
)paren
(brace
r_do
(brace
id|ccode
op_assign
id|signal_processor_ps
c_func
(paren
(paren
id|info
ques
c_cond
op_amp
id|info-&gt;status
suffix:colon
op_amp
id|dummy
)paren
comma
id|parameter
comma
id|i
comma
id|order_code
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|spin
op_logical_and
id|ccode
op_eq
id|sigp_busy
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info
op_logical_and
id|ccode
op_ne
id|sigp_order_code_accepted
)paren
(brace
id|info-&gt;intresting
op_assign
l_int|1
suffix:semicolon
id|info-&gt;cpu
op_assign
id|i
suffix:semicolon
id|info-&gt;ccode
op_assign
id|ccode
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_return
id|i
suffix:semicolon
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
r_int
id|i
suffix:semicolon
id|u32
id|dummy
suffix:semicolon
r_int
r_int
id|low_core_addr
suffix:semicolon
multiline_comment|/* write magic number to zero page (absolute 0) */
id|get_cpu_lowcore
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
dot
id|panic_magic
op_assign
id|__PANIC_MAGIC
suffix:semicolon
multiline_comment|/* stop all processors */
id|smp_signal_others
c_func
(paren
id|sigp_stop
comma
l_int|0
comma
l_int|1
comma
l_int|NULL
)paren
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
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_ne
id|i
)paren
(brace
r_int
id|ccode
suffix:semicolon
id|low_core_addr
op_assign
(paren
r_int
r_int
)paren
op_amp
id|get_cpu_lowcore
c_func
(paren
id|i
)paren
suffix:semicolon
r_do
(brace
id|ccode
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
id|ccode
op_eq
id|sigp_busy
)paren
(brace
suffix:semicolon
)brace
)brace
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
id|smp_ext_call_others
c_func
(paren
id|smp_ptlb_callback
comma
l_int|NULL
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
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|smp_commenced
)paren
op_ne
l_int|0
)paren
(brace
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
id|smp_ext_call_others
c_func
(paren
id|smp_ctl_bit_callback
comma
op_amp
id|parms
comma
l_int|1
)paren
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|smp_commenced
)paren
op_ne
l_int|0
)paren
(brace
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
id|smp_ext_call_others
c_func
(paren
id|smp_ctl_bit_callback
comma
op_amp
id|parms
comma
l_int|1
)paren
suffix:semicolon
)brace
id|__ctl_clear_bit
c_func
(paren
id|cr
comma
id|bit
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Call a function on all other processors&n; */
r_int
DECL|function|smp_call_function
id|smp_call_function
c_func
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
id|retry
comma
r_int
id|wait
)paren
multiline_comment|/*&n; * [SUMMARY] Run a function on all other CPUs.&n; * &lt;func&gt; The function to run. This must be fast and non-blocking.&n; * &lt;info&gt; An arbitrary pointer to pass to the function.&n; * &lt;retry&gt; currently unused.&n; * &lt;wait&gt; If true, wait (atomically) until function has completed on other CPUs.&n; * [RETURNS] 0 on success, else a negative status code. Does not return until&n; * remote CPUs are nearly ready to execute &lt;&lt;func&gt;&gt; or are or have executed.&n; *&n; * You must not call this function with disabled interrupts or from a&n; * hardware interrupt handler, you may call it from a bottom half handler.&n; */
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|smp_commenced
)paren
op_ne
l_int|0
)paren
id|smp_ext_call_others
c_func
(paren
id|func
comma
id|info
comma
id|wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Lets check how many CPUs we have.&n; */
DECL|function|smp_count_cpus
r_void
id|smp_count_cpus
c_func
(paren
r_void
)paren
(brace
r_int
id|curr_cpu
suffix:semicolon
id|current-&gt;processor
op_assign
l_int|0
suffix:semicolon
id|smp_num_cpus
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
id|smp_num_cpus
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
id|smp_num_cpus
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
id|smp_num_cpus
comma
id|sigp_sense
)paren
op_eq
id|sigp_not_operational
)paren
r_continue
suffix:semicolon
id|smp_num_cpus
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
id|smp_num_cpus
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
id|init_100hz_timer
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|start_secondary
r_int
id|__init
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
multiline_comment|/* Print info about this processor */
id|print_cpu_info
c_func
(paren
op_amp
id|safe_get_cpu_lowcore
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
dot
id|cpu_data
)paren
suffix:semicolon
multiline_comment|/* Wait for completion of smp startup */
r_while
c_loop
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|smp_commenced
)paren
)paren
multiline_comment|/* nothing */
suffix:semicolon
multiline_comment|/* init per CPU 100 hz timer */
id|init_100hz_timer
c_func
(paren
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
multiline_comment|/*&n; * The restart interrupt handler jumps to start_secondary directly&n; * without the detour over initialize_secondary. We defined it here&n; * so that the linker doesn&squot;t complain.&n; */
DECL|function|initialize_secondary
r_void
id|__init
id|initialize_secondary
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|fork_by_hand
r_static
r_int
id|__init
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
id|CLONE_PID
comma
l_int|0
comma
op_amp
id|regs
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|do_boot_cpu
r_static
r_void
id|__init
id|do_boot_cpu
c_func
(paren
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
multiline_comment|/* We can&squot;t use kernel_thread since we must _avoid_ to reschedule&n;           the child. */
r_if
c_cond
(paren
id|fork_by_hand
c_func
(paren
)paren
OL
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;failed fork for CPU %d&quot;
comma
id|cpu
)paren
suffix:semicolon
multiline_comment|/*&n;         * We remove it from the pidhash and the runqueue&n;         * once we got the process:&n;         */
id|idle
op_assign
id|init_task.prev_task
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|idle
)paren
id|panic
c_func
(paren
l_string|&quot;No idle process for CPU %d&quot;
comma
id|cpu
)paren
suffix:semicolon
id|idle-&gt;processor
op_assign
id|cpu
suffix:semicolon
id|idle-&gt;has_cpu
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* we schedule the first task manually */
id|del_from_runqueue
c_func
(paren
id|idle
)paren
suffix:semicolon
id|unhash_process
c_func
(paren
id|idle
)paren
suffix:semicolon
id|init_tasks
(braket
id|cpu
)braket
op_assign
id|idle
suffix:semicolon
id|cpu_lowcore
op_assign
op_amp
id|get_cpu_lowcore
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|cpu_lowcore-&gt;kernel_stack
op_assign
id|idle-&gt;thread.ksp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stctl 0,15,%0&bslash;n&bslash;t&quot;
l_string|&quot;stam  0,15,%1&quot;
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
)brace
multiline_comment|/*&n; *      Architecture specific routine called by the kernel just before init is&n; *      fired off. This allows the BP to have everything in order [we hope].&n; *      At the end of this all the APs will hit the system scheduling and off&n; *      we go. Each AP will load the system gdt&squot;s and jump through the kernel&n; *      init into idle(). At this point the scheduler will one day take over&n; *      and give them jobs to do. smp_callin is a standard routine&n; *      we use to track CPUs as they power up.&n; */
DECL|function|smp_commence
r_void
id|__init
id|smp_commence
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;         *      Lets the callins below out of their loop.&n;         */
id|atomic_set
c_func
(paren
op_amp
id|smp_commenced
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Cycle through the processors sending APIC IPIs to boot each.&n; */
DECL|function|smp_boot_cpus
r_void
id|__init
id|smp_boot_cpus
c_func
(paren
r_void
)paren
(brace
r_struct
id|_lowcore
op_star
id|curr_lowcore
suffix:semicolon
id|sigp_ccode
id|ccode
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
id|smp_count_cpus
c_func
(paren
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
multiline_comment|/*&n;         *      Initialize the logical to physical CPU number mapping&n;         *      and the per-CPU profiling counter/multiplier&n;         */
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
id|prof_counter
(braket
id|i
)braket
op_assign
l_int|1
suffix:semicolon
id|prof_old_multiplier
(braket
id|i
)braket
op_assign
l_int|1
suffix:semicolon
id|prof_multiplier
(braket
id|i
)braket
op_assign
l_int|1
suffix:semicolon
)brace
id|print_cpu_info
c_func
(paren
op_amp
id|safe_get_cpu_lowcore
c_func
(paren
l_int|0
)paren
dot
id|cpu_data
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
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
(brace
id|curr_lowcore
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
r_if
c_cond
(paren
id|curr_lowcore
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;smp_boot_cpus failed to allocate prefix memory&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|lowcore_ptr
(braket
id|i
)braket
op_assign
id|curr_lowcore
suffix:semicolon
id|memcpy
c_func
(paren
id|curr_lowcore
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
multiline_comment|/*&n;                 * Most of the parameters are set up when the cpu is&n;                 * started up.&n;                 */
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_eq
id|i
)paren
id|set_prefix
c_func
(paren
(paren
id|u32
)paren
id|curr_lowcore
)paren
suffix:semicolon
r_else
(brace
id|ccode
op_assign
id|signal_processor_p
c_func
(paren
(paren
id|u32
)paren
(paren
id|curr_lowcore
)paren
comma
id|i
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
multiline_comment|/* if this gets troublesome I&squot;ll have to do&n;                                 * something about it. */
id|printk
c_func
(paren
l_string|&quot;ccode %d for cpu %d  returned when &quot;
l_string|&quot;setting prefix in smp_boot_cpus not good.&bslash;n&quot;
comma
(paren
r_int
)paren
id|ccode
comma
(paren
r_int
)paren
id|i
)paren
suffix:semicolon
)brace
r_else
id|do_boot_cpu
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
)brace
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
multiline_comment|/*&n; * Local timer interrupt handler. It does both profiling and&n; * process statistics/rescheduling.&n; *&n; * We do profiling in every local tick, statistics/rescheduling&n; * happen only every &squot;profiling multiplier&squot; ticks. The default&n; * multiplier is 1 and it can be changed by writing the new multiplier&n; * value into /proc/profile.&n; */
DECL|function|smp_local_timer_interrupt
r_void
id|smp_local_timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|user
op_assign
(paren
id|user_mode
c_func
(paren
id|regs
)paren
op_ne
l_int|0
)paren
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;         * The profiling function is SMP safe. (nothing can mess&n;         * around with &quot;current&quot;, and the profiling counters are&n;         * updated with atomic operations). This is especially&n;         * useful with a profiling multiplier != 1&n;         */
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
)paren
id|s390_do_profile
c_func
(paren
id|regs-&gt;psw.addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|prof_counter
(braket
id|cpu
)braket
)paren
(brace
r_int
id|system
op_assign
l_int|1
op_minus
id|user
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
op_assign
id|current
suffix:semicolon
multiline_comment|/*&n;                 * The multiplier may have changed since the last time we got&n;                 * to this point as a result of the user writing to&n;                 * /proc/profile.  In this case we need to adjust the APIC&n;                 * timer accordingly.&n;                 *&n;                 * Interrupts are already masked off at this point.&n;                 */
id|prof_counter
(braket
id|cpu
)braket
op_assign
id|prof_multiplier
(braket
id|cpu
)braket
suffix:semicolon
r_if
c_cond
(paren
id|prof_counter
(braket
id|cpu
)braket
op_ne
id|prof_old_multiplier
(braket
id|cpu
)braket
)paren
(brace
multiline_comment|/* FIXME setup_APIC_timer(calibration_result/prof_counter[cpu]&n;&t;&t;&t;   ); */
id|prof_old_multiplier
(braket
id|cpu
)braket
op_assign
id|prof_counter
(braket
id|cpu
)braket
suffix:semicolon
)brace
multiline_comment|/*&n;                 * After doing the above, we need to make like&n;                 * a normal interrupt - otherwise timer interrupts&n;                 * ignore the global interrupt lock, which is the&n;                 * WrongThing (tm) to do.&n;                 */
id|irq_enter
c_func
(paren
id|cpu
comma
l_int|0
)paren
suffix:semicolon
id|update_process_times
c_func
(paren
id|user
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
id|cpu
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|variable|lowcore_ptr
id|EXPORT_SYMBOL
c_func
(paren
id|lowcore_ptr
)paren
suffix:semicolon
DECL|variable|kernel_flag
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_flag
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
DECL|variable|smp_num_cpus
id|EXPORT_SYMBOL
c_func
(paren
id|smp_num_cpus
)paren
suffix:semicolon
eof
