multiline_comment|/* drivers/atm/suni.c - PMC PM5346 SUNI (PHY) driver */
multiline_comment|/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
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
macro_line|#include &lt;linux/atm_suni.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &quot;suni.h&quot;
macro_line|#if 0
mdefine_line|#define DPRINTK(format,args...) printk(KERN_DEBUG format,##args)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(format,args...)
macro_line|#endif
DECL|struct|suni_priv
r_struct
id|suni_priv
(brace
DECL|member|sonet_stats
r_struct
id|k_sonet_stats
id|sonet_stats
suffix:semicolon
multiline_comment|/* link diagnostics */
DECL|member|loop_mode
r_int
id|loop_mode
suffix:semicolon
multiline_comment|/* loopback mode */
DECL|member|dev
r_struct
id|atm_dev
op_star
id|dev
suffix:semicolon
multiline_comment|/* device back-pointer */
DECL|member|next
r_struct
id|suni_priv
op_star
id|next
suffix:semicolon
multiline_comment|/* next SUNI */
)brace
suffix:semicolon
DECL|macro|PRIV
mdefine_line|#define PRIV(dev) ((struct suni_priv *) dev-&gt;phy_data)
DECL|macro|PUT
mdefine_line|#define PUT(val,reg) dev-&gt;ops-&gt;phy_put(dev,val,SUNI_##reg)
DECL|macro|GET
mdefine_line|#define GET(reg) dev-&gt;ops-&gt;phy_get(dev,SUNI_##reg)
DECL|macro|REG_CHANGE
mdefine_line|#define REG_CHANGE(mask,shift,value,reg) &bslash;&n;  PUT((GET(reg) &amp; ~(mask)) | ((value) &lt;&lt; (shift)),reg)
DECL|variable|poll_timer
r_static
r_struct
id|timer_list
id|poll_timer
suffix:semicolon
DECL|variable|sunis
r_static
r_struct
id|suni_priv
op_star
id|sunis
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|sunis_lock
r_static
id|spinlock_t
id|sunis_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|ADD_LIMITED
mdefine_line|#define ADD_LIMITED(s,v) &bslash;&n;    atomic_add((v),&amp;stats-&gt;s); &bslash;&n;    if (atomic_read(&amp;stats-&gt;s) &lt; 0) atomic_set(&amp;stats-&gt;s,INT_MAX);
DECL|function|suni_hz
r_static
r_void
id|suni_hz
c_func
(paren
r_int
r_int
id|from_timer
)paren
(brace
r_struct
id|suni_priv
op_star
id|walk
suffix:semicolon
r_struct
id|atm_dev
op_star
id|dev
suffix:semicolon
r_struct
id|k_sonet_stats
op_star
id|stats
suffix:semicolon
r_for
c_loop
(paren
id|walk
op_assign
id|sunis
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
id|walk-&gt;sonet_stats
suffix:semicolon
id|PUT
c_func
(paren
l_int|0
comma
id|MRI
)paren
suffix:semicolon
multiline_comment|/* latch counters */
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|ADD_LIMITED
c_func
(paren
id|section_bip
comma
(paren
id|GET
c_func
(paren
id|RSOP_SBL
)paren
op_amp
l_int|0xff
)paren
op_or
(paren
(paren
id|GET
c_func
(paren
id|RSOP_SBM
)paren
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
id|ADD_LIMITED
c_func
(paren
id|line_bip
comma
(paren
id|GET
c_func
(paren
id|RLOP_LBL
)paren
op_amp
l_int|0xff
)paren
op_or
(paren
(paren
id|GET
c_func
(paren
id|RLOP_LB
)paren
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|GET
c_func
(paren
id|RLOP_LBM
)paren
op_amp
l_int|0xf
)paren
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
id|ADD_LIMITED
c_func
(paren
id|path_bip
comma
(paren
id|GET
c_func
(paren
id|RPOP_PBL
)paren
op_amp
l_int|0xff
)paren
op_or
(paren
(paren
id|GET
c_func
(paren
id|RPOP_PBM
)paren
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
id|ADD_LIMITED
c_func
(paren
id|line_febe
comma
(paren
id|GET
c_func
(paren
id|RLOP_LFL
)paren
op_amp
l_int|0xff
)paren
op_or
(paren
(paren
id|GET
c_func
(paren
id|RLOP_LF
)paren
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|GET
c_func
(paren
id|RLOP_LFM
)paren
op_amp
l_int|0xf
)paren
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
id|ADD_LIMITED
c_func
(paren
id|path_febe
comma
(paren
id|GET
c_func
(paren
id|RPOP_PFL
)paren
op_amp
l_int|0xff
)paren
op_or
(paren
(paren
id|GET
c_func
(paren
id|RPOP_PFM
)paren
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
id|ADD_LIMITED
c_func
(paren
id|corr_hcs
comma
id|GET
c_func
(paren
id|RACP_CHEC
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|ADD_LIMITED
c_func
(paren
id|uncorr_hcs
comma
id|GET
c_func
(paren
id|RACP_UHEC
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|ADD_LIMITED
c_func
(paren
id|rx_cells
comma
(paren
id|GET
c_func
(paren
id|RACP_RCCL
)paren
op_amp
l_int|0xff
)paren
op_or
(paren
(paren
id|GET
c_func
(paren
id|RACP_RCC
)paren
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|GET
c_func
(paren
id|RACP_RCCM
)paren
op_amp
l_int|7
)paren
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
id|ADD_LIMITED
c_func
(paren
id|tx_cells
comma
(paren
id|GET
c_func
(paren
id|TACP_TCCL
)paren
op_amp
l_int|0xff
)paren
op_or
(paren
(paren
id|GET
c_func
(paren
id|TACP_TCC
)paren
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|GET
c_func
(paren
id|TACP_TCCM
)paren
op_amp
l_int|7
)paren
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|from_timer
)paren
id|mod_timer
c_func
(paren
op_amp
id|poll_timer
comma
id|jiffies
op_plus
id|HZ
)paren
suffix:semicolon
)brace
DECL|macro|ADD_LIMITED
macro_line|#undef ADD_LIMITED
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
id|sonet_stats
op_star
id|arg
comma
r_int
id|zero
)paren
(brace
r_struct
id|sonet_stats
id|tmp
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|sonet_copy_stats
c_func
(paren
op_amp
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|sonet_stats
comma
op_amp
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg
)paren
id|error
op_assign
id|copy_to_user
c_func
(paren
id|arg
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|zero
op_logical_and
op_logical_neg
id|error
)paren
id|sonet_subtract_stats
c_func
(paren
op_amp
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|sonet_stats
comma
op_amp
id|tmp
)paren
suffix:semicolon
r_return
id|error
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|macro|HANDLE_FLAG
mdefine_line|#define HANDLE_FLAG(flag,reg,bit) &bslash;&n;  if (todo &amp; flag) { &bslash;&n;    if (set) PUT(GET(reg) | bit,reg); &bslash;&n;    else PUT(GET(reg) &amp; ~bit,reg); &bslash;&n;    todo &amp;= ~flag; &bslash;&n;  }
DECL|function|change_diag
r_static
r_int
id|change_diag
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
comma
r_void
op_star
id|arg
comma
r_int
id|set
)paren
(brace
r_int
id|todo
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|todo
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|HANDLE_FLAG
c_func
(paren
id|SONET_INS_SBIP
comma
id|TSOP_DIAG
comma
id|SUNI_TSOP_DIAG_DBIP8
)paren
suffix:semicolon
id|HANDLE_FLAG
c_func
(paren
id|SONET_INS_LBIP
comma
id|TLOP_DIAG
comma
id|SUNI_TLOP_DIAG_DBIP
)paren
suffix:semicolon
id|HANDLE_FLAG
c_func
(paren
id|SONET_INS_PBIP
comma
id|TPOP_CD
comma
id|SUNI_TPOP_DIAG_DB3
)paren
suffix:semicolon
id|HANDLE_FLAG
c_func
(paren
id|SONET_INS_FRAME
comma
id|RSOP_CIE
comma
id|SUNI_RSOP_CIE_FOOF
)paren
suffix:semicolon
id|HANDLE_FLAG
c_func
(paren
id|SONET_INS_LAIS
comma
id|TSOP_CTRL
comma
id|SUNI_TSOP_CTRL_LAIS
)paren
suffix:semicolon
id|HANDLE_FLAG
c_func
(paren
id|SONET_INS_PAIS
comma
id|TPOP_CD
comma
id|SUNI_TPOP_DIAG_PAIS
)paren
suffix:semicolon
id|HANDLE_FLAG
c_func
(paren
id|SONET_INS_LOS
comma
id|TSOP_DIAG
comma
id|SUNI_TSOP_DIAG_DLOS
)paren
suffix:semicolon
id|HANDLE_FLAG
c_func
(paren
id|SONET_INS_HCS
comma
id|TACP_CS
comma
id|SUNI_TACP_CS_DHCS
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|todo
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
)brace
DECL|macro|HANDLE_FLAG
macro_line|#undef HANDLE_FLAG
DECL|function|get_diag
r_static
r_int
id|get_diag
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
comma
r_void
op_star
id|arg
)paren
(brace
r_int
id|set
suffix:semicolon
id|set
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|GET
c_func
(paren
id|TSOP_DIAG
)paren
op_amp
id|SUNI_TSOP_DIAG_DBIP8
)paren
id|set
op_or_assign
id|SONET_INS_SBIP
suffix:semicolon
r_if
c_cond
(paren
id|GET
c_func
(paren
id|TLOP_DIAG
)paren
op_amp
id|SUNI_TLOP_DIAG_DBIP
)paren
id|set
op_or_assign
id|SONET_INS_LBIP
suffix:semicolon
r_if
c_cond
(paren
id|GET
c_func
(paren
id|TPOP_CD
)paren
op_amp
id|SUNI_TPOP_DIAG_DB3
)paren
id|set
op_or_assign
id|SONET_INS_PBIP
suffix:semicolon
multiline_comment|/* SONET_INS_FRAME is one-shot only */
r_if
c_cond
(paren
id|GET
c_func
(paren
id|TSOP_CTRL
)paren
op_amp
id|SUNI_TSOP_CTRL_LAIS
)paren
id|set
op_or_assign
id|SONET_INS_LAIS
suffix:semicolon
r_if
c_cond
(paren
id|GET
c_func
(paren
id|TPOP_CD
)paren
op_amp
id|SUNI_TPOP_DIAG_PAIS
)paren
id|set
op_or_assign
id|SONET_INS_PAIS
suffix:semicolon
r_if
c_cond
(paren
id|GET
c_func
(paren
id|TSOP_DIAG
)paren
op_amp
id|SUNI_TSOP_DIAG_DLOS
)paren
id|set
op_or_assign
id|SONET_INS_LOS
suffix:semicolon
r_if
c_cond
(paren
id|GET
c_func
(paren
id|TACP_CS
)paren
op_amp
id|SUNI_TACP_CS_DHCS
)paren
id|set
op_or_assign
id|SONET_INS_HCS
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|set
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
r_char
id|control
suffix:semicolon
id|control
op_assign
id|GET
c_func
(paren
id|MCT
)paren
op_amp
op_complement
(paren
id|SUNI_MCT_DLE
op_or
id|SUNI_MCT_LLE
)paren
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
id|ATM_LM_LOC_PHY
suffix:colon
id|control
op_or_assign
id|SUNI_MCT_DLE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ATM_LM_RMT_PHY
suffix:colon
id|control
op_or_assign
id|SUNI_MCT_LLE
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
id|control
comma
id|MCT
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
DECL|function|suni_ioctl
r_static
r_int
id|suni_ioctl
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
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SONET_GETSTATZ
suffix:colon
r_case
id|SONET_GETSTAT
suffix:colon
r_return
id|fetch_stats
c_func
(paren
id|dev
comma
(paren
r_struct
id|sonet_stats
op_star
)paren
id|arg
comma
id|cmd
op_eq
id|SONET_GETSTATZ
)paren
suffix:semicolon
r_case
id|SONET_SETDIAG
suffix:colon
r_return
id|change_diag
c_func
(paren
id|dev
comma
id|arg
comma
l_int|1
)paren
suffix:semicolon
r_case
id|SONET_CLRDIAG
suffix:colon
r_return
id|change_diag
c_func
(paren
id|dev
comma
id|arg
comma
l_int|0
)paren
suffix:semicolon
r_case
id|SONET_GETDIAG
suffix:colon
r_return
id|get_diag
c_func
(paren
id|dev
comma
id|arg
)paren
suffix:semicolon
r_case
id|SONET_SETFRAMING
suffix:colon
r_if
c_cond
(paren
id|arg
op_ne
id|SONET_FRAME_SONET
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SONET_GETFRAMING
suffix:colon
r_return
id|put_user
c_func
(paren
id|SONET_FRAME_SONET
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
id|SONET_GETFRSENSE
suffix:colon
r_return
op_minus
id|EINVAL
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
id|ATM_LM_LOC_PHY
op_or
id|ATM_LM_RMT_PHY
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
DECL|function|poll_los
r_static
r_void
id|poll_los
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
(brace
id|dev-&gt;signal
op_assign
id|GET
c_func
(paren
id|RSOP_SIS
)paren
op_amp
id|SUNI_RSOP_SIS_LOSV
ques
c_cond
id|ATM_PHY_SIG_LOST
suffix:colon
id|ATM_PHY_SIG_FOUND
suffix:semicolon
)brace
DECL|function|suni_int
r_static
r_void
id|suni_int
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
(brace
id|poll_los
c_func
(paren
id|dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s(itf %d): signal %s&bslash;n&quot;
comma
id|dev-&gt;type
comma
id|dev-&gt;number
comma
id|dev-&gt;signal
op_eq
id|ATM_PHY_SIG_LOST
ques
c_cond
l_string|&quot;lost&quot;
suffix:colon
l_string|&quot;detected again&quot;
)paren
suffix:semicolon
)brace
DECL|function|suni_start
r_static
r_int
id|suni_start
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
r_int
id|first
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|PRIV
c_func
(paren
id|dev
)paren
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|suni_priv
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
id|sunis_lock
comma
id|flags
)paren
suffix:semicolon
id|first
op_assign
op_logical_neg
id|sunis
suffix:semicolon
id|PRIV
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|next
op_assign
id|sunis
suffix:semicolon
id|sunis
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
id|sunis_lock
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
id|sonet_stats
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|k_sonet_stats
)paren
)paren
suffix:semicolon
id|PUT
c_func
(paren
id|GET
c_func
(paren
id|RSOP_CIE
)paren
op_or
id|SUNI_RSOP_CIE_LOSE
comma
id|RSOP_CIE
)paren
suffix:semicolon
multiline_comment|/* interrupt on loss of signal */
id|poll_los
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* ... and clear SUNI interrupts */
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
id|suni_hz
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* clear SUNI counters */
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
r_if
c_cond
(paren
id|first
)paren
(brace
id|init_timer
c_func
(paren
op_amp
id|poll_timer
)paren
suffix:semicolon
id|poll_timer.expires
op_assign
id|jiffies
op_plus
id|HZ
suffix:semicolon
id|poll_timer.function
op_assign
id|suni_hz
suffix:semicolon
id|poll_timer.data
op_assign
l_int|1
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;[u] p=0x%lx,n=0x%lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|poll_timer.list.prev
comma
(paren
r_int
r_int
)paren
id|poll_timer.list.next
)paren
suffix:semicolon
macro_line|#endif
id|add_timer
c_func
(paren
op_amp
id|poll_timer
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|suni_stop
r_static
r_int
id|suni_stop
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
(brace
r_struct
id|suni_priv
op_star
op_star
id|walk
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* let SAR driver worry about stopping interrupts */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sunis_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|walk
op_assign
op_amp
id|sunis
suffix:semicolon
op_star
id|walk
op_ne
id|PRIV
c_func
(paren
id|dev
)paren
suffix:semicolon
id|walk
op_assign
op_amp
id|PRIV
c_func
(paren
(paren
op_star
id|walk
)paren
op_member_access_from_pointer
id|dev
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
op_star
id|walk
op_assign
id|PRIV
c_func
(paren
(paren
op_star
id|walk
)paren
op_member_access_from_pointer
id|dev
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sunis
)paren
id|del_timer_sync
c_func
(paren
op_amp
id|poll_timer
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sunis_lock
comma
id|flags
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|PRIV
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|suni_ops
r_static
r_const
r_struct
id|atmphy_ops
id|suni_ops
op_assign
(brace
id|start
suffix:colon
id|suni_start
comma
id|ioctl
suffix:colon
id|suni_ioctl
comma
id|interrupt
suffix:colon
id|suni_int
comma
id|stop
suffix:colon
id|suni_stop
comma
)brace
suffix:semicolon
DECL|function|suni_init
r_int
id|__init
id|suni_init
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
id|mri
suffix:semicolon
id|mri
op_assign
id|GET
c_func
(paren
id|MRI
)paren
suffix:semicolon
multiline_comment|/* reset SUNI */
id|PUT
c_func
(paren
id|mri
op_or
id|SUNI_MRI_RESET
comma
id|MRI
)paren
suffix:semicolon
id|PUT
c_func
(paren
id|mri
comma
id|MRI
)paren
suffix:semicolon
id|PUT
c_func
(paren
l_int|0
comma
id|MT
)paren
suffix:semicolon
multiline_comment|/* disable all tests */
id|REG_CHANGE
c_func
(paren
id|SUNI_TPOP_APM_S
comma
id|SUNI_TPOP_APM_S_SHIFT
comma
id|SUNI_TPOP_S_SONET
comma
id|TPOP_APM
)paren
suffix:semicolon
multiline_comment|/* use SONET */
id|REG_CHANGE
c_func
(paren
id|SUNI_TACP_IUCHP_CLP
comma
l_int|0
comma
id|SUNI_TACP_IUCHP_CLP
comma
id|TACP_IUCHP
)paren
suffix:semicolon
multiline_comment|/* idle cells */
id|PUT
c_func
(paren
id|SUNI_IDLE_PATTERN
comma
id|TACP_IUCPOP
)paren
suffix:semicolon
id|dev-&gt;phy
op_assign
op_amp
id|suni_ops
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|suni_init
id|EXPORT_SYMBOL
c_func
(paren
id|suni_init
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Nay */
)brace
macro_line|#endif
eof
