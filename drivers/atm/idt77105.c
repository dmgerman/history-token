multiline_comment|/* drivers/atm/idt77105.c - IDT77105 (PHY) driver */
multiline_comment|/* Written 1999 by Greg Banks, NEC Australia &lt;gnb@linuxfan.com&gt;. Based on suni.c */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/sonet.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/capability.h&gt;
macro_line|#include &lt;linux/atm_idt77105.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;idt77105.h&quot;
DECL|macro|GENERAL_DEBUG
macro_line|#undef GENERAL_DEBUG
macro_line|#ifdef GENERAL_DEBUG
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(format,args...) printk(KERN_DEBUG format,##args)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(format,args...)
macro_line|#endif
DECL|struct|idt77105_priv
r_struct
id|idt77105_priv
(brace
DECL|member|stats
r_struct
id|idt77105_stats
id|stats
suffix:semicolon
multiline_comment|/* link diagnostics */
DECL|member|dev
r_struct
id|atm_dev
op_star
id|dev
suffix:semicolon
multiline_comment|/* device back-pointer */
DECL|member|next
r_struct
id|idt77105_priv
op_star
id|next
suffix:semicolon
DECL|member|loop_mode
r_int
id|loop_mode
suffix:semicolon
DECL|member|old_mcr
r_int
r_char
id|old_mcr
suffix:semicolon
multiline_comment|/* storage of MCR reg while signal lost */
)brace
suffix:semicolon
DECL|variable|idt77105_priv_lock
r_static
id|spinlock_t
id|idt77105_priv_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|PRIV
mdefine_line|#define PRIV(dev) ((struct idt77105_priv *) dev-&gt;phy_data)
DECL|macro|PUT
mdefine_line|#define PUT(val,reg) dev-&gt;ops-&gt;phy_put(dev,val,IDT77105_##reg)
DECL|macro|GET
mdefine_line|#define GET(reg) dev-&gt;ops-&gt;phy_get(dev,IDT77105_##reg)
r_static
r_void
id|idt77105_stats_timer_func
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|idt77105_restart_timer_func
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|variable|stats_timer
r_static
r_struct
id|timer_list
id|stats_timer
op_assign
id|TIMER_INITIALIZER
c_func
(paren
id|idt77105_stats_timer_func
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
DECL|variable|restart_timer
r_static
r_struct
id|timer_list
id|restart_timer
op_assign
id|TIMER_INITIALIZER
c_func
(paren
id|idt77105_restart_timer_func
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
DECL|variable|start_timer
r_static
r_int
id|start_timer
op_assign
l_int|1
suffix:semicolon
DECL|variable|idt77105_all
r_static
r_struct
id|idt77105_priv
op_star
id|idt77105_all
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * Retrieve the value of one of the IDT77105&squot;s counters.&n; * `counter&squot; is one of the IDT77105_CTRSEL_* constants.&n; */
DECL|function|get_counter
r_static
id|u16
id|get_counter
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
comma
r_int
id|counter
)paren
(brace
id|u16
id|val
suffix:semicolon
multiline_comment|/* write the counter bit into PHY register 6 */
id|PUT
c_func
(paren
id|counter
comma
id|CTRSEL
)paren
suffix:semicolon
multiline_comment|/* read the low 8 bits from register 4 */
id|val
op_assign
id|GET
c_func
(paren
id|CTRLO
)paren
suffix:semicolon
multiline_comment|/* read the high 8 bits from register 5 */
id|val
op_or_assign
id|GET
c_func
(paren
id|CTRHI
)paren
op_lshift
l_int|8
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/*&n; * Timer function called every second to gather statistics&n; * from the 77105. This is done because the h/w registers&n; * will overflow if not read at least once per second. The&n; * kernel&squot;s stats are much higher precision. Also, having&n; * a separate copy of the stats allows implementation of&n; * an ioctl which gathers the stats *without* zero&squot;ing them.&n; */
DECL|function|idt77105_stats_timer_func
r_static
r_void
id|idt77105_stats_timer_func
c_func
(paren
r_int
r_int
id|dummy
)paren
(brace
r_struct
id|idt77105_priv
op_star
id|walk
suffix:semicolon
r_struct
id|atm_dev
op_star
id|dev
suffix:semicolon
r_struct
id|idt77105_stats
op_star
id|stats
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;IDT77105 gathering statistics&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|walk
op_assign
id|idt77105_all
suffix:semicolon
id|walk
suffix:semicolon
id|walk
op_assign
id|walk-&gt;next
)paren
(brace
id|dev
op_assign
id|walk-&gt;dev
suffix:semicolon
id|stats
op_assign
op_amp
id|walk-&gt;stats
suffix:semicolon
id|stats-&gt;symbol_errors
op_add_assign
id|get_counter
c_func
(paren
id|dev
comma
id|IDT77105_CTRSEL_SEC
)paren
suffix:semicolon
id|stats-&gt;tx_cells
op_add_assign
id|get_counter
c_func
(paren
id|dev
comma
id|IDT77105_CTRSEL_TCC
)paren
suffix:semicolon
id|stats-&gt;rx_cells
op_add_assign
id|get_counter
c_func
(paren
id|dev
comma
id|IDT77105_CTRSEL_RCC
)paren
suffix:semicolon
id|stats-&gt;rx_hec_errors
op_add_assign
id|get_counter
c_func
(paren
id|dev
comma
id|IDT77105_CTRSEL_RHEC
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|start_timer
)paren
id|mod_timer
c_func
(paren
op_amp
id|stats_timer
comma
id|jiffies
op_plus
id|IDT77105_STATS_TIMER_PERIOD
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * A separate timer func which handles restarting PHY chips which&n; * have had the cable re-inserted after being pulled out. This is&n; * done by polling the Good Signal Bit in the Interrupt Status&n; * register every 5 seconds. The other technique (checking Good&n; * Signal Bit in the interrupt handler) cannot be used because PHY&n; * interrupts need to be disabled when the cable is pulled out&n; * to avoid lots of spurious cell error interrupts.&n; */
DECL|function|idt77105_restart_timer_func
r_static
r_void
id|idt77105_restart_timer_func
c_func
(paren
r_int
r_int
id|dummy
)paren
(brace
r_struct
id|idt77105_priv
op_star
id|walk
suffix:semicolon
r_struct
id|atm_dev
op_star
id|dev
suffix:semicolon
r_int
r_char
id|istat
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;IDT77105 checking for cable re-insertion&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|walk
op_assign
id|idt77105_all
suffix:semicolon
id|walk
suffix:semicolon
id|walk
op_assign
id|walk-&gt;next
)paren
(brace
id|dev
op_assign
id|walk-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;signal
op_ne
id|ATM_PHY_SIG_LOST
)paren
r_continue
suffix:semicolon
id|istat
op_assign
id|GET
c_func
(paren
id|ISTAT
)paren
suffix:semicolon
multiline_comment|/* side effect: clears all interrupt status bits */
r_if
c_cond
(paren
id|istat
op_amp
id|IDT77105_ISTAT_GOODSIG
)paren
(brace
multiline_comment|/* Found signal again */
id|dev-&gt;signal
op_assign
id|ATM_PHY_SIG_FOUND
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s(itf %d): signal detected again&bslash;n&quot;
comma
id|dev-&gt;type
comma
id|dev-&gt;number
)paren
suffix:semicolon
multiline_comment|/* flush the receive FIFO */
id|PUT
c_func
(paren
id|GET
c_func
(paren
id|DIAG
)paren
op_or
id|IDT77105_DIAG_RFLUSH
comma
id|DIAG
)paren
suffix:semicolon
multiline_comment|/* re-enable interrupts */
id|PUT
c_func
(paren
id|walk-&gt;old_mcr
comma
id|MCR
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|start_timer
)paren
id|mod_timer
c_func
(paren
op_amp
id|restart_timer
comma
id|jiffies
op_plus
id|IDT77105_RESTART_TIMER_PERIOD
)paren
suffix:semicolon
)brace
DECL|function|fetch_stats
r_static
r_int
id|fetch_stats
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
comma
r_struct
id|idt77105_stats
op_star
id|arg
comma
r_int
id|zero
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|idt77105_stats
id|stats
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|idt77105_priv_lock
comma
id|flags
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|stats
comma
op_amp
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|stats
comma
r_sizeof
(paren
r_struct
id|idt77105_stats
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|zero
)paren
id|memset
c_func
(paren
op_amp
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|stats
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|idt77105_stats
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|idt77105_priv_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
id|arg
comma
op_amp
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|stats
comma
r_sizeof
(paren
r_struct
id|idt77105_stats
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|set_loopback
r_static
r_int
id|set_loopback
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
comma
r_int
id|mode
)paren
(brace
r_int
id|diag
suffix:semicolon
id|diag
op_assign
id|GET
c_func
(paren
id|DIAG
)paren
op_amp
op_complement
id|IDT77105_DIAG_LCMASK
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|ATM_LM_NONE
suffix:colon
r_break
suffix:semicolon
r_case
id|ATM_LM_LOC_ATM
suffix:colon
id|diag
op_or_assign
id|IDT77105_DIAG_LC_PHY_LOOPBACK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ATM_LM_RMT_ATM
suffix:colon
id|diag
op_or_assign
id|IDT77105_DIAG_LC_LINE_LOOPBACK
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|PUT
c_func
(paren
id|diag
comma
id|DIAG
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s(%d) Loopback mode is: %s&bslash;n&quot;
comma
id|dev-&gt;type
comma
id|dev-&gt;number
comma
(paren
id|mode
op_eq
id|ATM_LM_NONE
ques
c_cond
l_string|&quot;NONE&quot;
suffix:colon
(paren
id|mode
op_eq
id|ATM_LM_LOC_ATM
ques
c_cond
l_string|&quot;DIAG (local)&quot;
suffix:colon
(paren
id|mode
op_eq
id|IDT77105_DIAG_LC_LINE_LOOPBACK
ques
c_cond
l_string|&quot;LOOP (remote)&quot;
suffix:colon
l_string|&quot;unknown&quot;
)paren
)paren
)paren
)paren
suffix:semicolon
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|loop_mode
op_assign
id|mode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|idt77105_ioctl
r_static
r_int
id|idt77105_ioctl
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s(%d) idt77105_ioctl() called&bslash;n&quot;
comma
id|dev-&gt;type
comma
id|dev-&gt;number
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|IDT77105_GETSTATZ
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/* fall through */
r_case
id|IDT77105_GETSTAT
suffix:colon
r_return
id|fetch_stats
c_func
(paren
id|dev
comma
(paren
r_struct
id|idt77105_stats
op_star
)paren
id|arg
comma
id|cmd
op_eq
id|IDT77105_GETSTATZ
)paren
suffix:semicolon
r_case
id|ATM_SETLOOP
suffix:colon
r_return
id|set_loopback
c_func
(paren
id|dev
comma
(paren
r_int
)paren
(paren
r_int
)paren
id|arg
)paren
suffix:semicolon
r_case
id|ATM_GETLOOP
suffix:colon
r_return
id|put_user
c_func
(paren
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|loop_mode
comma
(paren
r_int
op_star
)paren
id|arg
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|ATM_QUERYLOOP
suffix:colon
r_return
id|put_user
c_func
(paren
id|ATM_LM_LOC_ATM
op_or
id|ATM_LM_RMT_ATM
comma
(paren
r_int
op_star
)paren
id|arg
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
)brace
DECL|function|idt77105_int
r_static
r_void
id|idt77105_int
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
(brace
r_int
r_char
id|istat
suffix:semicolon
id|istat
op_assign
id|GET
c_func
(paren
id|ISTAT
)paren
suffix:semicolon
multiline_comment|/* side effect: clears all interrupt status bits */
id|DPRINTK
c_func
(paren
l_string|&quot;IDT77105 generated an interrupt, istat=%02x&bslash;n&quot;
comma
(paren
r_int
)paren
id|istat
)paren
suffix:semicolon
r_if
c_cond
(paren
id|istat
op_amp
id|IDT77105_ISTAT_RSCC
)paren
(brace
multiline_comment|/* Rx Signal Condition Change - line went up or down */
r_if
c_cond
(paren
id|istat
op_amp
id|IDT77105_ISTAT_GOODSIG
)paren
(brace
multiline_comment|/* signal detected again */
multiline_comment|/* This should not happen (restart timer does it) but JIC */
id|dev-&gt;signal
op_assign
id|ATM_PHY_SIG_FOUND
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* signal lost */
multiline_comment|/*&n;                 * Disable interrupts and stop all transmission and&n;                 * reception - the restart timer will restore these.&n;                 */
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|old_mcr
op_assign
id|GET
c_func
(paren
id|MCR
)paren
suffix:semicolon
id|PUT
c_func
(paren
(paren
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|old_mcr
op_or
id|IDT77105_MCR_DREC
op_or
id|IDT77105_MCR_DRIC
op_or
id|IDT77105_MCR_HALTTX
)paren
op_amp
op_complement
id|IDT77105_MCR_EIP
comma
id|MCR
)paren
suffix:semicolon
id|dev-&gt;signal
op_assign
id|ATM_PHY_SIG_LOST
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s(itf %d): signal lost&bslash;n&quot;
comma
id|dev-&gt;type
comma
id|dev-&gt;number
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|istat
op_amp
id|IDT77105_ISTAT_RFO
)paren
(brace
multiline_comment|/* Rx FIFO Overrun -- perform a FIFO flush */
id|PUT
c_func
(paren
id|GET
c_func
(paren
id|DIAG
)paren
op_or
id|IDT77105_DIAG_RFLUSH
comma
id|DIAG
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s(itf %d): receive FIFO overrun&bslash;n&quot;
comma
id|dev-&gt;type
comma
id|dev-&gt;number
)paren
suffix:semicolon
)brace
macro_line|#ifdef GENERAL_DEBUG
r_if
c_cond
(paren
id|istat
op_amp
(paren
id|IDT77105_ISTAT_HECERR
op_or
id|IDT77105_ISTAT_SCR
op_or
id|IDT77105_ISTAT_RSE
)paren
)paren
(brace
multiline_comment|/* normally don&squot;t care - just report in stats */
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s(itf %d): received cell with error&bslash;n&quot;
comma
id|dev-&gt;type
comma
id|dev-&gt;number
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|idt77105_start
r_static
r_int
id|idt77105_start
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;dev_data
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|idt77105_priv
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|dev
op_assign
id|dev
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|idt77105_priv_lock
comma
id|flags
)paren
suffix:semicolon
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|next
op_assign
id|idt77105_all
suffix:semicolon
id|idt77105_all
op_assign
id|PRIV
c_func
(paren
id|dev
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|idt77105_priv_lock
comma
id|flags
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|stats
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|idt77105_stats
)paren
)paren
suffix:semicolon
multiline_comment|/* initialise dev-&gt;signal from Good Signal Bit */
id|dev-&gt;signal
op_assign
id|GET
c_func
(paren
id|ISTAT
)paren
op_amp
id|IDT77105_ISTAT_GOODSIG
ques
c_cond
id|ATM_PHY_SIG_FOUND
suffix:colon
id|ATM_PHY_SIG_LOST
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;signal
op_eq
id|ATM_PHY_SIG_LOST
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s(itf %d): no signal&bslash;n&quot;
comma
id|dev-&gt;type
comma
id|dev-&gt;number
)paren
suffix:semicolon
multiline_comment|/* initialise loop mode from hardware */
r_switch
c_cond
(paren
id|GET
c_func
(paren
id|DIAG
)paren
op_amp
id|IDT77105_DIAG_LCMASK
)paren
(brace
r_case
id|IDT77105_DIAG_LC_NORMAL
suffix:colon
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|loop_mode
op_assign
id|ATM_LM_NONE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IDT77105_DIAG_LC_PHY_LOOPBACK
suffix:colon
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|loop_mode
op_assign
id|ATM_LM_LOC_ATM
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IDT77105_DIAG_LC_LINE_LOOPBACK
suffix:colon
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|loop_mode
op_assign
id|ATM_LM_RMT_ATM
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* enable interrupts, e.g. on loss of signal */
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|old_mcr
op_assign
id|GET
c_func
(paren
id|MCR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;signal
op_eq
id|ATM_PHY_SIG_FOUND
)paren
(brace
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|old_mcr
op_or_assign
id|IDT77105_MCR_EIP
suffix:semicolon
id|PUT
c_func
(paren
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|old_mcr
comma
id|MCR
)paren
suffix:semicolon
)brace
id|idt77105_stats_timer_func
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* clear 77105 counters */
(paren
r_void
)paren
id|fetch_stats
c_func
(paren
id|dev
comma
l_int|NULL
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* clear kernel counters */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|idt77105_priv_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start_timer
)paren
(brace
id|start_timer
op_assign
l_int|0
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|stats_timer
)paren
suffix:semicolon
id|stats_timer.expires
op_assign
id|jiffies
op_plus
id|IDT77105_STATS_TIMER_PERIOD
suffix:semicolon
id|stats_timer.function
op_assign
id|idt77105_stats_timer_func
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|stats_timer
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|restart_timer
)paren
suffix:semicolon
id|restart_timer.expires
op_assign
id|jiffies
op_plus
id|IDT77105_RESTART_TIMER_PERIOD
suffix:semicolon
id|restart_timer.function
op_assign
id|idt77105_restart_timer_func
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|restart_timer
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|idt77105_priv_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|idt77105_stop
r_int
id|idt77105_stop
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
(brace
r_struct
id|idt77105_priv
op_star
id|walk
comma
op_star
id|prev
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;%s(itf %d): stopping IDT77105&bslash;n&quot;
comma
id|dev-&gt;type
comma
id|dev-&gt;number
)paren
suffix:semicolon
multiline_comment|/* disable interrupts */
id|PUT
c_func
(paren
id|GET
c_func
(paren
id|MCR
)paren
op_amp
op_complement
id|IDT77105_MCR_EIP
comma
id|MCR
)paren
suffix:semicolon
multiline_comment|/* detach private struct from atm_dev &amp; free */
r_for
c_loop
(paren
id|prev
op_assign
l_int|NULL
comma
id|walk
op_assign
id|idt77105_all
suffix:semicolon
id|walk
op_ne
l_int|NULL
suffix:semicolon
id|prev
op_assign
id|walk
comma
id|walk
op_assign
id|walk-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|walk-&gt;dev
op_eq
id|dev
)paren
(brace
r_if
c_cond
(paren
id|prev
op_ne
l_int|NULL
)paren
id|prev-&gt;next
op_assign
id|walk-&gt;next
suffix:semicolon
r_else
id|idt77105_all
op_assign
id|walk-&gt;next
suffix:semicolon
id|dev-&gt;phy
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;dev_data
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|walk
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|idt77105_ops
r_static
r_const
r_struct
id|atmphy_ops
id|idt77105_ops
op_assign
(brace
dot
id|start
op_assign
id|idt77105_start
comma
dot
id|ioctl
op_assign
id|idt77105_ioctl
comma
dot
id|interrupt
op_assign
id|idt77105_int
comma
dot
id|stop
op_assign
id|idt77105_stop
comma
)brace
suffix:semicolon
DECL|function|idt77105_init
r_int
id|idt77105_init
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
(brace
id|dev-&gt;phy
op_assign
op_amp
id|idt77105_ops
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|idt77105_init
id|EXPORT_SYMBOL
c_func
(paren
id|idt77105_init
)paren
suffix:semicolon
DECL|function|idt77105_exit
r_static
r_void
id|__exit
id|idt77105_exit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* turn off timers */
id|del_timer
c_func
(paren
op_amp
id|stats_timer
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|restart_timer
)paren
suffix:semicolon
)brace
DECL|variable|idt77105_exit
id|module_exit
c_func
(paren
id|idt77105_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
