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
DECL|variable|cyclone_interpolator
r_struct
id|time_interpolator
id|cyclone_interpolator
op_assign
(brace
dot
id|source
op_assign
id|TIME_SOURCE_MMIO32
comma
dot
id|shift
op_assign
l_int|32
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
id|u32
op_star
r_volatile
id|cyclone_timer
suffix:semicolon
multiline_comment|/* Cyclone MPMC0 register */
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
id|cyclone_interpolator.addr
op_assign
id|cyclone_timer
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
