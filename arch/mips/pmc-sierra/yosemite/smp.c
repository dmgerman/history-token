macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/pmon.h&gt;
macro_line|#include &lt;asm/titan_dep.h&gt;
r_extern
r_int
r_int
(paren
op_star
id|mips_hpt_read
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mips_hpt_init
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|LAUNCHSTACK_SIZE
mdefine_line|#define LAUNCHSTACK_SIZE 256
DECL|variable|__initdata
r_static
id|spinlock_t
id|launch_lock
id|__initdata
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
r_int
id|secondary_sp
id|__initdata
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
r_int
id|secondary_gp
id|__initdata
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
r_char
id|launchstack
(braket
id|LAUNCHSTACK_SIZE
)braket
id|__initdata
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|2
op_star
r_sizeof
(paren
r_int
)paren
)paren
)paren
)paren
suffix:semicolon
DECL|function|prom_smp_bootstrap
r_static
r_void
id|__init
id|prom_smp_bootstrap
c_func
(paren
r_void
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|spin_is_locked
c_func
(paren
op_amp
id|launch_lock
)paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;move&t;$sp, %0&t;&t;&bslash;n&quot;
l_string|&quot;&t;move&t;$gp, %1&t;&t;&bslash;n&quot;
l_string|&quot;&t;j&t;smp_bootstrap&t;&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|secondary_sp
)paren
comma
l_string|&quot;r&quot;
(paren
id|secondary_gp
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * PMON is a fragile beast.  It&squot;ll blow up once the mappings it&squot;s littering&n; * right into the middle of KSEG3 are blown away so we have to grab the slave&n; * core early and keep it in a waiting loop.&n; */
DECL|function|prom_grab_secondary
r_void
id|__init
id|prom_grab_secondary
c_func
(paren
r_void
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|launch_lock
)paren
suffix:semicolon
id|pmon_cpustart
c_func
(paren
l_int|1
comma
op_amp
id|prom_smp_bootstrap
comma
id|launchstack
op_plus
id|LAUNCHSTACK_SIZE
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Detect available CPUs, populate phys_cpu_present_map before smp_init&n; *&n; * We don&squot;t want to start the secondary CPU yet nor do we have a nice probing&n; * feature in PMON so we just assume presence of the secondary core.&n; */
DECL|variable|__initdata
r_static
r_char
id|maxcpus_string
(braket
)braket
id|__initdata
op_assign
id|KERN_WARNING
l_string|&quot;max_cpus set to 0; using 1 instead&bslash;n&quot;
suffix:semicolon
DECL|function|prom_prepare_cpus
r_void
id|__init
id|prom_prepare_cpus
c_func
(paren
r_int
r_int
id|max_cpus
)paren
(brace
r_int
id|enabled
op_assign
l_int|0
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
id|max_cpus
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|maxcpus_string
)paren
suffix:semicolon
id|max_cpus
op_assign
l_int|1
suffix:semicolon
)brace
id|cpus_clear
c_func
(paren
id|phys_cpu_present_map
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_eq
id|max_cpus
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The boot CPU&n;&t;&t; */
id|cpu_set
c_func
(paren
id|i
comma
id|phys_cpu_present_map
)paren
suffix:semicolon
id|__cpu_number_map
(braket
id|i
)braket
op_assign
id|i
suffix:semicolon
id|__cpu_logical_map
(braket
id|i
)braket
op_assign
id|i
suffix:semicolon
id|enabled
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Be paranoid.  Enable the IPI only if we&squot;re really about to go SMP.&n;&t; */
r_if
c_cond
(paren
id|enabled
OG
l_int|1
)paren
id|set_c0_status
c_func
(paren
id|STATUSF_IP5
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Firmware CPU startup hook&n; * Complicated by PMON&squot;s weird interface which tries to minimic the UNIX fork.&n; * It launches the next * available CPU and copies some information on the&n; * stack so the first thing we do is throw away that stuff and load useful&n; * values into the registers ...&n; */
DECL|function|prom_boot_secondary
r_void
id|prom_boot_secondary
c_func
(paren
r_int
id|cpu
comma
r_struct
id|task_struct
op_star
id|idle
)paren
(brace
r_int
r_int
id|gp
op_assign
(paren
r_int
r_int
)paren
id|idle-&gt;thread_info
suffix:semicolon
r_int
r_int
id|sp
op_assign
id|gp
op_plus
id|THREAD_SIZE
op_minus
l_int|32
suffix:semicolon
id|secondary_sp
op_assign
id|sp
suffix:semicolon
id|secondary_gp
op_assign
id|gp
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|launch_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Hook for after all CPUs are online */
DECL|function|prom_cpus_done
r_void
id|prom_cpus_done
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/*&n; *  After we&squot;ve done initial boot, this function is called to allow the&n; *  board code to clean up state, if needed&n; */
DECL|function|prom_init_secondary
r_void
id|prom_init_secondary
c_func
(paren
r_void
)paren
(brace
id|mips_hpt_init
c_func
(paren
id|mips_hpt_read
c_func
(paren
)paren
)paren
suffix:semicolon
id|set_c0_status
c_func
(paren
id|ST0_CO
op_or
id|ST0_IE
op_or
id|ST0_IM
)paren
suffix:semicolon
)brace
DECL|function|prom_smp_finish
r_void
id|prom_smp_finish
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|titan_mailbox_irq
id|asmlinkage
r_void
id|titan_mailbox_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
r_if
c_cond
(paren
id|cpu
op_eq
l_int|0
)paren
(brace
id|status
op_assign
id|OCD_READ
c_func
(paren
id|RM9000x2_OCD_INTP0STATUS3
)paren
suffix:semicolon
id|OCD_WRITE
c_func
(paren
id|RM9000x2_OCD_INTP0CLEAR3
comma
id|status
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cpu
op_eq
l_int|1
)paren
(brace
id|status
op_assign
id|OCD_READ
c_func
(paren
id|RM9000x2_OCD_INTP1STATUS3
)paren
suffix:semicolon
id|OCD_WRITE
c_func
(paren
id|RM9000x2_OCD_INTP1CLEAR3
comma
id|status
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
l_int|0x2
)paren
id|smp_call_function_interrupt
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Send inter-processor interrupt&n; */
DECL|function|core_send_ipi
r_void
id|core_send_ipi
c_func
(paren
r_int
id|cpu
comma
r_int
r_int
id|action
)paren
(brace
multiline_comment|/*&n;&t; * Generate an INTMSG so that it can be sent over to the&n;&t; * destination CPU. The INTMSG will put the STATUS bits&n;&t; * based on the action desired. An alternative strategy&n;&t; * is to write to the Interrupt Set register, read the&n;&t; * Interrupt Status register and clear the Interrupt&n;&t; * Clear register. The latter is preffered.&n;&t; */
r_switch
c_cond
(paren
id|action
)paren
(brace
r_case
id|SMP_RESCHEDULE_YOURSELF
suffix:colon
r_if
c_cond
(paren
id|cpu
op_eq
l_int|1
)paren
id|OCD_WRITE
c_func
(paren
id|RM9000x2_OCD_INTP1SET3
comma
l_int|4
)paren
suffix:semicolon
r_else
id|OCD_WRITE
c_func
(paren
id|RM9000x2_OCD_INTP0SET3
comma
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SMP_CALL_FUNCTION
suffix:colon
r_if
c_cond
(paren
id|cpu
op_eq
l_int|1
)paren
id|OCD_WRITE
c_func
(paren
id|RM9000x2_OCD_INTP1SET3
comma
l_int|2
)paren
suffix:semicolon
r_else
id|OCD_WRITE
c_func
(paren
id|RM9000x2_OCD_INTP0SET3
comma
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
eof
