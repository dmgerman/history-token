macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* IBM Summit (EXA) Cyclone counter code*/
DECL|macro|CYCLONE_CBAR_ADDR
mdefine_line|#define CYCLONE_CBAR_ADDR 0xFEB00CD0
DECL|macro|CYCLONE_PMCC_OFFSET
mdefine_line|#define CYCLONE_PMCC_OFFSET 0x51A0
DECL|macro|CYCLONE_MPMC_OFFSET
mdefine_line|#define CYCLONE_MPMC_OFFSET 0x51D0
DECL|macro|CYCLONE_MPCS_OFFSET
mdefine_line|#define CYCLONE_MPCS_OFFSET 0x51A8
DECL|macro|CYCLONE_TIMER_FREQ
mdefine_line|#define CYCLONE_TIMER_FREQ 100000000
DECL|variable|use_cyclone
r_int
id|use_cyclone
suffix:semicolon
DECL|function|cyclone_setup
r_void
id|__init
id|cyclone_setup
c_func
(paren
r_void
)paren
(brace
id|use_cyclone
op_assign
l_int|1
suffix:semicolon
)brace
DECL|variable|cyclone_timer
r_static
id|u32
op_star
r_volatile
id|cyclone_timer
suffix:semicolon
multiline_comment|/* Cyclone MPMC0 register */
DECL|variable|last_update_cyclone
r_static
id|u32
id|last_update_cyclone
suffix:semicolon
DECL|variable|offset_base
r_static
r_int
r_int
id|offset_base
suffix:semicolon
DECL|function|get_offset_cyclone
r_static
r_int
r_int
id|get_offset_cyclone
c_func
(paren
r_void
)paren
(brace
id|u32
id|now
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
multiline_comment|/* Read the cyclone timer */
id|now
op_assign
id|readl
c_func
(paren
id|cyclone_timer
)paren
suffix:semicolon
multiline_comment|/* .. relative to previous update*/
id|offset
op_assign
id|now
op_minus
id|last_update_cyclone
suffix:semicolon
multiline_comment|/* convert cyclone ticks to nanoseconds */
id|offset
op_assign
(paren
id|offset
op_star
id|NSEC_PER_SEC
)paren
op_div
id|CYCLONE_TIMER_FREQ
suffix:semicolon
multiline_comment|/* our adjusted time in nanoseconds */
r_return
id|offset_base
op_plus
id|offset
suffix:semicolon
)brace
DECL|function|update_cyclone
r_static
r_void
id|update_cyclone
c_func
(paren
r_int
id|delta_nsec
)paren
(brace
id|u32
id|now
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
multiline_comment|/* Read the cyclone timer */
id|now
op_assign
id|readl
c_func
(paren
id|cyclone_timer
)paren
suffix:semicolon
multiline_comment|/* .. relative to previous update*/
id|offset
op_assign
id|now
op_minus
id|last_update_cyclone
suffix:semicolon
multiline_comment|/* convert cyclone ticks to nanoseconds */
id|offset
op_assign
(paren
id|offset
op_star
id|NSEC_PER_SEC
)paren
op_div
id|CYCLONE_TIMER_FREQ
suffix:semicolon
id|offset
op_add_assign
id|offset_base
suffix:semicolon
multiline_comment|/* Be careful about signed/unsigned comparisons here: */
r_if
c_cond
(paren
id|delta_nsec
OL
l_int|0
op_logical_or
(paren
r_int
r_int
)paren
id|delta_nsec
OL
id|offset
)paren
id|offset_base
op_assign
id|offset
op_minus
id|delta_nsec
suffix:semicolon
r_else
id|offset_base
op_assign
l_int|0
suffix:semicolon
id|last_update_cyclone
op_assign
id|now
suffix:semicolon
)brace
DECL|function|reset_cyclone
r_static
r_void
id|reset_cyclone
c_func
(paren
r_void
)paren
(brace
id|offset_base
op_assign
l_int|0
suffix:semicolon
id|last_update_cyclone
op_assign
id|readl
c_func
(paren
id|cyclone_timer
)paren
suffix:semicolon
)brace
DECL|variable|cyclone_interpolator
r_struct
id|time_interpolator
id|cyclone_interpolator
op_assign
(brace
dot
id|get_offset
op_assign
id|get_offset_cyclone
comma
dot
id|update
op_assign
id|update_cyclone
comma
dot
id|reset
op_assign
id|reset_cyclone
comma
dot
id|frequency
op_assign
id|CYCLONE_TIMER_FREQ
comma
dot
id|drift
op_assign
op_minus
l_int|100
comma
)brace
suffix:semicolon
DECL|function|init_cyclone_clock
r_int
id|__init
id|init_cyclone_clock
c_func
(paren
r_void
)paren
(brace
id|u64
op_star
id|reg
suffix:semicolon
id|u64
id|base
suffix:semicolon
multiline_comment|/* saved cyclone base address */
id|u64
id|offset
suffix:semicolon
multiline_comment|/* offset from pageaddr to cyclone_timer register */
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|use_cyclone
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Summit chipset: Starting Cyclone Counter.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* find base address */
id|offset
op_assign
(paren
id|CYCLONE_CBAR_ADDR
)paren
suffix:semicolon
id|reg
op_assign
(paren
id|u64
op_star
)paren
id|ioremap_nocache
c_func
(paren
id|offset
comma
r_sizeof
(paren
id|u64
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|reg
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Summit chipset: Could not find valid CBAR register.&bslash;n&quot;
)paren
suffix:semicolon
id|use_cyclone
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|base
op_assign
id|readq
c_func
(paren
id|reg
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Summit chipset: Could not find valid CBAR value.&bslash;n&quot;
)paren
suffix:semicolon
id|use_cyclone
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|iounmap
c_func
(paren
id|reg
)paren
suffix:semicolon
multiline_comment|/* setup PMCC */
id|offset
op_assign
(paren
id|base
op_plus
id|CYCLONE_PMCC_OFFSET
)paren
suffix:semicolon
id|reg
op_assign
(paren
id|u64
op_star
)paren
id|ioremap_nocache
c_func
(paren
id|offset
comma
r_sizeof
(paren
id|u64
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|reg
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Summit chipset: Could not find valid PMCC register.&bslash;n&quot;
)paren
suffix:semicolon
id|use_cyclone
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|writel
c_func
(paren
l_int|0x00000001
comma
id|reg
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|reg
)paren
suffix:semicolon
multiline_comment|/* setup MPCS */
id|offset
op_assign
(paren
id|base
op_plus
id|CYCLONE_MPCS_OFFSET
)paren
suffix:semicolon
id|reg
op_assign
(paren
id|u64
op_star
)paren
id|ioremap_nocache
c_func
(paren
id|offset
comma
r_sizeof
(paren
id|u64
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|reg
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Summit chipset: Could not find valid MPCS register.&bslash;n&quot;
)paren
suffix:semicolon
id|use_cyclone
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|writel
c_func
(paren
l_int|0x00000001
comma
id|reg
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|reg
)paren
suffix:semicolon
multiline_comment|/* map in cyclone_timer */
id|offset
op_assign
(paren
id|base
op_plus
id|CYCLONE_MPMC_OFFSET
)paren
suffix:semicolon
id|cyclone_timer
op_assign
(paren
id|u32
op_star
)paren
id|ioremap_nocache
c_func
(paren
id|offset
comma
r_sizeof
(paren
id|u32
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cyclone_timer
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Summit chipset: Could not find valid MPMC register.&bslash;n&quot;
)paren
suffix:semicolon
id|use_cyclone
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/*quick test to make sure its ticking*/
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
id|u32
id|old
op_assign
id|readl
c_func
(paren
id|cyclone_timer
)paren
suffix:semicolon
r_int
id|stall
op_assign
l_int|100
suffix:semicolon
r_while
c_loop
(paren
id|stall
op_decrement
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|readl
c_func
(paren
id|cyclone_timer
)paren
op_eq
id|old
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Summit chipset: Counter not counting! DISABLED&bslash;n&quot;
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|cyclone_timer
)paren
suffix:semicolon
id|cyclone_timer
op_assign
l_int|0
suffix:semicolon
id|use_cyclone
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
multiline_comment|/* initialize last tick */
id|last_update_cyclone
op_assign
id|readl
c_func
(paren
id|cyclone_timer
)paren
suffix:semicolon
id|register_time_interpolator
c_func
(paren
op_amp
id|cyclone_interpolator
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|init_cyclone_clock
id|__initcall
c_func
(paren
id|init_cyclone_clock
)paren
suffix:semicolon
eof
