macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/fasttimer.h&gt;
r_extern
r_void
id|dump_thread
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_struct
id|user
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_cmos_time
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__Udiv
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__Umod
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__Div
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__Mod
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__ashrdi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iounmap
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
multiline_comment|/* Platform dependent support */
DECL|variable|dump_thread
id|EXPORT_SYMBOL
c_func
(paren
id|dump_thread
)paren
suffix:semicolon
DECL|variable|enable_irq
id|EXPORT_SYMBOL
c_func
(paren
id|enable_irq
)paren
suffix:semicolon
DECL|variable|disable_irq
id|EXPORT_SYMBOL
c_func
(paren
id|disable_irq
)paren
suffix:semicolon
DECL|variable|kernel_thread
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_thread
)paren
suffix:semicolon
DECL|variable|get_cmos_time
id|EXPORT_SYMBOL
c_func
(paren
id|get_cmos_time
)paren
suffix:semicolon
DECL|variable|loops_per_usec
id|EXPORT_SYMBOL
c_func
(paren
id|loops_per_usec
)paren
suffix:semicolon
multiline_comment|/* String functions */
DECL|variable|memcmp
id|EXPORT_SYMBOL
c_func
(paren
id|memcmp
)paren
suffix:semicolon
DECL|variable|memmove
id|EXPORT_SYMBOL
c_func
(paren
id|memmove
)paren
suffix:semicolon
DECL|variable|strpbrk
id|EXPORT_SYMBOL
c_func
(paren
id|strpbrk
)paren
suffix:semicolon
DECL|variable|strstr
id|EXPORT_SYMBOL
c_func
(paren
id|strstr
)paren
suffix:semicolon
DECL|variable|strcpy
id|EXPORT_SYMBOL
c_func
(paren
id|strcpy
)paren
suffix:semicolon
DECL|variable|strchr
id|EXPORT_SYMBOL
c_func
(paren
id|strchr
)paren
suffix:semicolon
DECL|variable|strcmp
id|EXPORT_SYMBOL
c_func
(paren
id|strcmp
)paren
suffix:semicolon
DECL|variable|strlen
id|EXPORT_SYMBOL
c_func
(paren
id|strlen
)paren
suffix:semicolon
DECL|variable|strcat
id|EXPORT_SYMBOL
c_func
(paren
id|strcat
)paren
suffix:semicolon
DECL|variable|strncat
id|EXPORT_SYMBOL
c_func
(paren
id|strncat
)paren
suffix:semicolon
DECL|variable|strncmp
id|EXPORT_SYMBOL
c_func
(paren
id|strncmp
)paren
suffix:semicolon
DECL|variable|strncpy
id|EXPORT_SYMBOL
c_func
(paren
id|strncpy
)paren
suffix:semicolon
multiline_comment|/* Math functions */
DECL|variable|__Udiv
id|EXPORT_SYMBOL
c_func
(paren
id|__Udiv
)paren
suffix:semicolon
DECL|variable|__Umod
id|EXPORT_SYMBOL
c_func
(paren
id|__Umod
)paren
suffix:semicolon
DECL|variable|__Div
id|EXPORT_SYMBOL
c_func
(paren
id|__Div
)paren
suffix:semicolon
DECL|variable|__Mod
id|EXPORT_SYMBOL
c_func
(paren
id|__Mod
)paren
suffix:semicolon
DECL|variable|__ashrdi3
id|EXPORT_SYMBOL
c_func
(paren
id|__ashrdi3
)paren
suffix:semicolon
multiline_comment|/* Memory functions */
DECL|variable|__ioremap
id|EXPORT_SYMBOL
c_func
(paren
id|__ioremap
)paren
suffix:semicolon
DECL|variable|iounmap
id|EXPORT_SYMBOL
c_func
(paren
id|iounmap
)paren
suffix:semicolon
multiline_comment|/* Semaphore functions */
DECL|variable|__up
id|EXPORT_SYMBOL
c_func
(paren
id|__up
)paren
suffix:semicolon
DECL|variable|__down
id|EXPORT_SYMBOL
c_func
(paren
id|__down
)paren
suffix:semicolon
DECL|variable|__down_interruptible
id|EXPORT_SYMBOL
c_func
(paren
id|__down_interruptible
)paren
suffix:semicolon
DECL|variable|__down_trylock
id|EXPORT_SYMBOL
c_func
(paren
id|__down_trylock
)paren
suffix:semicolon
multiline_comment|/* Export shadow registers for the CPU I/O pins */
DECL|variable|genconfig_shadow
id|EXPORT_SYMBOL
c_func
(paren
id|genconfig_shadow
)paren
suffix:semicolon
DECL|variable|port_pa_data_shadow
id|EXPORT_SYMBOL
c_func
(paren
id|port_pa_data_shadow
)paren
suffix:semicolon
DECL|variable|port_pa_dir_shadow
id|EXPORT_SYMBOL
c_func
(paren
id|port_pa_dir_shadow
)paren
suffix:semicolon
DECL|variable|port_pb_data_shadow
id|EXPORT_SYMBOL
c_func
(paren
id|port_pb_data_shadow
)paren
suffix:semicolon
DECL|variable|port_pb_dir_shadow
id|EXPORT_SYMBOL
c_func
(paren
id|port_pb_dir_shadow
)paren
suffix:semicolon
DECL|variable|port_pb_config_shadow
id|EXPORT_SYMBOL
c_func
(paren
id|port_pb_config_shadow
)paren
suffix:semicolon
DECL|variable|port_g_data_shadow
id|EXPORT_SYMBOL
c_func
(paren
id|port_g_data_shadow
)paren
suffix:semicolon
multiline_comment|/* Userspace access functions */
DECL|variable|__copy_user_zeroing
id|EXPORT_SYMBOL
c_func
(paren
id|__copy_user_zeroing
)paren
suffix:semicolon
DECL|variable|__copy_user
id|EXPORT_SYMBOL
c_func
(paren
id|__copy_user
)paren
suffix:semicolon
multiline_comment|/* Cache flush functions */
DECL|variable|flush_etrax_cache
id|EXPORT_SYMBOL
c_func
(paren
id|flush_etrax_cache
)paren
suffix:semicolon
DECL|variable|prepare_rx_descriptor
id|EXPORT_SYMBOL
c_func
(paren
id|prepare_rx_descriptor
)paren
suffix:semicolon
DECL|macro|memcpy
macro_line|#undef memcpy
DECL|macro|memset
macro_line|#undef memset
r_extern
r_void
op_star
id|memset
c_func
(paren
r_void
op_star
comma
r_int
comma
id|__kernel_size_t
)paren
suffix:semicolon
r_extern
r_void
op_star
id|memcpy
c_func
(paren
r_void
op_star
comma
r_const
r_void
op_star
comma
id|__kernel_size_t
)paren
suffix:semicolon
DECL|variable|memcpy
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy
)paren
suffix:semicolon
DECL|variable|memset
id|EXPORT_SYMBOL
c_func
(paren
id|memset
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ETRAX_FAST_TIMER
multiline_comment|/* Fast timer functions */
DECL|variable|fast_timer_list
id|EXPORT_SYMBOL
c_func
(paren
id|fast_timer_list
)paren
suffix:semicolon
DECL|variable|start_one_shot_timer
id|EXPORT_SYMBOL
c_func
(paren
id|start_one_shot_timer
)paren
suffix:semicolon
DECL|variable|del_fast_timer
id|EXPORT_SYMBOL
c_func
(paren
id|del_fast_timer
)paren
suffix:semicolon
DECL|variable|schedule_usleep
id|EXPORT_SYMBOL
c_func
(paren
id|schedule_usleep
)paren
suffix:semicolon
macro_line|#endif
eof
