multiline_comment|/* Hook to call BIOS initialisation function */
multiline_comment|/* no action for generic */
DECL|macro|ARCH_SETUP
mdefine_line|#define ARCH_SETUP arch_setup_pc9800();
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pc9800.h&gt;
macro_line|#include &lt;asm/pc9800_sca.h&gt;
DECL|variable|CLOCK_TICK_RATE
r_int
id|CLOCK_TICK_RATE
suffix:semicolon
r_extern
r_int
r_int
id|tick_usec
suffix:semicolon
multiline_comment|/* ACTHZ          period (usec) */
r_extern
r_int
r_int
id|tick_nsec
suffix:semicolon
multiline_comment|/* USER_HZ period (nsec) */
DECL|variable|pc9800_misc_flags
r_int
r_char
id|pc9800_misc_flags
suffix:semicolon
multiline_comment|/* (bit 0) 1:High Address Video ram exists 0:otherwise */
macro_line|#ifdef CONFIG_SMP
DECL|macro|MPC_TABLE_SIZE
mdefine_line|#define MPC_TABLE_SIZE 512
DECL|macro|MPC_TABLE
mdefine_line|#define MPC_TABLE ((char *) (PARAM+0x400))
DECL|variable|mpc_table
r_char
id|mpc_table
(braket
id|MPC_TABLE_SIZE
)braket
suffix:semicolon
macro_line|#endif
DECL|function|arch_setup_pc9800
r_static
r_inline
r_void
id|arch_setup_pc9800
c_func
(paren
r_void
)paren
(brace
id|CLOCK_TICK_RATE
op_assign
id|PC9800_8MHz_P
c_func
(paren
)paren
ques
c_cond
l_int|1996800
suffix:colon
l_int|2457600
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;CLOCK_TICK_RATE = %d&bslash;n&quot;
comma
id|CLOCK_TICK_RATE
)paren
suffix:semicolon
id|tick_usec
op_assign
id|TICK_USEC
suffix:semicolon
multiline_comment|/* USER_HZ period (usec) */
id|tick_nsec
op_assign
id|TICK_NSEC
suffix:semicolon
multiline_comment|/* ACTHZ period (nsec) */
id|pc9800_misc_flags
op_assign
id|PC9800_MISC_FLAGS
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
(paren
op_star
(paren
id|u32
op_star
)paren
(paren
id|MPC_TABLE
)paren
)paren
op_eq
l_int|0x504d4350
)paren
id|memcpy
c_func
(paren
id|mpc_table
comma
id|MPC_TABLE
comma
op_star
(paren
id|u16
op_star
)paren
(paren
id|MPC_TABLE
op_plus
l_int|4
)paren
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
)brace
eof
