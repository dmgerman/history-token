multiline_comment|/* orinoco.h&n; * &n; * Common definitions to all pieces of the various orinoco&n; * drivers&n; */
macro_line|#ifndef _ORINOCO_H
DECL|macro|_ORINOCO_H
mdefine_line|#define _ORINOCO_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/wireless.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &quot;hermes.h&quot;
multiline_comment|/* Workqueue / task queue backwards compatibility stuff */
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,5,41)
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#else
macro_line|#include &lt;linux/tqueue.h&gt;
DECL|macro|work_struct
mdefine_line|#define work_struct tq_struct
DECL|macro|INIT_WORK
mdefine_line|#define INIT_WORK INIT_TQUEUE
DECL|macro|schedule_work
mdefine_line|#define schedule_work schedule_task
macro_line|#endif
multiline_comment|/* Interrupt handler backwards compatibility stuff */
macro_line|#ifndef IRQ_NONE
DECL|macro|IRQ_NONE
mdefine_line|#define IRQ_NONE
DECL|macro|IRQ_HANDLED
mdefine_line|#define IRQ_HANDLED
DECL|typedef|irqreturn_t
r_typedef
r_void
id|irqreturn_t
suffix:semicolon
macro_line|#endif
multiline_comment|/* To enable debug messages */
singleline_comment|//#define ORINOCO_DEBUG&t;&t;3
macro_line|#if (! defined (WIRELESS_EXT)) || (WIRELESS_EXT &lt; 10)
macro_line|#error &quot;orinoco driver requires Wireless extensions v10 or later.&quot;
macro_line|#endif /* (! defined (WIRELESS_EXT)) || (WIRELESS_EXT &lt; 10) */
DECL|macro|WIRELESS_SPY
mdefine_line|#define WIRELESS_SPY&t;&t;
singleline_comment|// enable iwspy support
DECL|macro|ORINOCO_MAX_KEY_SIZE
mdefine_line|#define ORINOCO_MAX_KEY_SIZE&t;14
DECL|macro|ORINOCO_MAX_KEYS
mdefine_line|#define ORINOCO_MAX_KEYS&t;4
DECL|struct|orinoco_key
r_struct
id|orinoco_key
(brace
DECL|member|len
id|u16
id|len
suffix:semicolon
multiline_comment|/* always stored as little-endian */
DECL|member|data
r_char
id|data
(braket
id|ORINOCO_MAX_KEY_SIZE
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|ORINOCO_INTEN
mdefine_line|#define ORINOCO_INTEN&t; &t;( HERMES_EV_RX | HERMES_EV_ALLOC | HERMES_EV_TX | &bslash;&n;&t;&t;&t;&t;HERMES_EV_TXEXC | HERMES_EV_WTERR | HERMES_EV_INFO | &bslash;&n;&t;&t;&t;&t;HERMES_EV_INFDROP )
DECL|struct|orinoco_private
r_struct
id|orinoco_private
(brace
DECL|member|card
r_void
op_star
id|card
suffix:semicolon
multiline_comment|/* Pointer to card dependent structure */
DECL|member|hard_reset
r_int
(paren
op_star
id|hard_reset
)paren
(paren
r_struct
id|orinoco_private
op_star
)paren
suffix:semicolon
multiline_comment|/* Synchronisation stuff */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|hw_unavailable
r_int
id|hw_unavailable
suffix:semicolon
DECL|member|reset_work
r_struct
id|work_struct
id|reset_work
suffix:semicolon
multiline_comment|/* driver state */
DECL|member|open
r_int
id|open
suffix:semicolon
DECL|member|last_linkstatus
id|u16
id|last_linkstatus
suffix:semicolon
DECL|member|connected
r_int
id|connected
suffix:semicolon
multiline_comment|/* Net device stuff */
DECL|member|ndev
r_struct
id|net_device
op_star
id|ndev
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|wstats
r_struct
id|iw_statistics
id|wstats
suffix:semicolon
multiline_comment|/* Hardware control variables */
DECL|member|hw
id|hermes_t
id|hw
suffix:semicolon
DECL|member|txfid
id|u16
id|txfid
suffix:semicolon
multiline_comment|/* Capabilities of the hardware/firmware */
DECL|member|firmware_type
r_int
id|firmware_type
suffix:semicolon
DECL|macro|FIRMWARE_TYPE_AGERE
mdefine_line|#define FIRMWARE_TYPE_AGERE 1
DECL|macro|FIRMWARE_TYPE_INTERSIL
mdefine_line|#define FIRMWARE_TYPE_INTERSIL 2
DECL|macro|FIRMWARE_TYPE_SYMBOL
mdefine_line|#define FIRMWARE_TYPE_SYMBOL 3
DECL|member|has_ibss
DECL|member|has_port3
DECL|member|has_ibss_any
DECL|member|ibss_port
r_int
id|has_ibss
comma
id|has_port3
comma
id|has_ibss_any
comma
id|ibss_port
suffix:semicolon
DECL|member|has_wep
DECL|member|has_big_wep
r_int
id|has_wep
comma
id|has_big_wep
suffix:semicolon
DECL|member|has_mwo
r_int
id|has_mwo
suffix:semicolon
DECL|member|has_pm
r_int
id|has_pm
suffix:semicolon
DECL|member|has_preamble
r_int
id|has_preamble
suffix:semicolon
DECL|member|has_sensitivity
r_int
id|has_sensitivity
suffix:semicolon
DECL|member|nicbuf_size
r_int
id|nicbuf_size
suffix:semicolon
DECL|member|channel_mask
id|u16
id|channel_mask
suffix:semicolon
DECL|member|broken_disableport
r_int
id|broken_disableport
suffix:semicolon
multiline_comment|/* Configuration paramaters */
DECL|member|iw_mode
id|u32
id|iw_mode
suffix:semicolon
DECL|member|prefer_port3
r_int
id|prefer_port3
suffix:semicolon
DECL|member|wep_on
DECL|member|wep_restrict
DECL|member|tx_key
id|u16
id|wep_on
comma
id|wep_restrict
comma
id|tx_key
suffix:semicolon
DECL|member|keys
r_struct
id|orinoco_key
id|keys
(braket
id|ORINOCO_MAX_KEYS
)braket
suffix:semicolon
DECL|member|bitratemode
r_int
id|bitratemode
suffix:semicolon
DECL|member|nick
r_char
id|nick
(braket
id|IW_ESSID_MAX_SIZE
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|desired_essid
r_char
id|desired_essid
(braket
id|IW_ESSID_MAX_SIZE
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|frag_thresh
DECL|member|mwo_robust
id|u16
id|frag_thresh
comma
id|mwo_robust
suffix:semicolon
DECL|member|channel
id|u16
id|channel
suffix:semicolon
DECL|member|ap_density
DECL|member|rts_thresh
id|u16
id|ap_density
comma
id|rts_thresh
suffix:semicolon
DECL|member|pm_on
DECL|member|pm_mcast
DECL|member|pm_period
DECL|member|pm_timeout
id|u16
id|pm_on
comma
id|pm_mcast
comma
id|pm_period
comma
id|pm_timeout
suffix:semicolon
DECL|member|preamble
id|u16
id|preamble
suffix:semicolon
macro_line|#ifdef WIRELESS_SPY
DECL|member|spy_number
r_int
id|spy_number
suffix:semicolon
DECL|member|spy_address
id|u_char
id|spy_address
(braket
id|IW_MAX_SPY
)braket
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|spy_stat
r_struct
id|iw_quality
id|spy_stat
(braket
id|IW_MAX_SPY
)braket
suffix:semicolon
macro_line|#endif
multiline_comment|/* Configuration dependent variables */
DECL|member|port_type
DECL|member|createibss
r_int
id|port_type
comma
id|createibss
suffix:semicolon
DECL|member|promiscuous
DECL|member|mc_count
r_int
id|promiscuous
comma
id|mc_count
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef ORINOCO_DEBUG
r_extern
r_int
id|orinoco_debug
suffix:semicolon
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...) do { if (orinoco_debug&gt;(n)) printk(KERN_DEBUG args); } while(0)
macro_line|#else
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...) do { } while (0)
macro_line|#endif&t;/* ORINOCO_DEBUG */
DECL|macro|TRACE_ENTER
mdefine_line|#define TRACE_ENTER(devname) DEBUG(2, &quot;%s: -&gt; &quot; __FUNCTION__ &quot;()&bslash;n&quot;, devname);
DECL|macro|TRACE_EXIT
mdefine_line|#define TRACE_EXIT(devname)  DEBUG(2, &quot;%s: &lt;- &quot; __FUNCTION__ &quot;()&bslash;n&quot;, devname);
r_extern
r_struct
id|net_device
op_star
id|alloc_orinocodev
c_func
(paren
r_int
id|sizeof_card
comma
r_int
(paren
op_star
id|hard_reset
)paren
(paren
r_struct
id|orinoco_private
op_star
)paren
)paren
suffix:semicolon
r_extern
r_int
id|__orinoco_up
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|__orinoco_down
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|orinoco_stop
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|orinoco_reinit_firmware
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
id|irqreturn_t
id|orinoco_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
multiline_comment|/********************************************************************/
multiline_comment|/* Locking and synchronization functions                            */
multiline_comment|/********************************************************************/
multiline_comment|/* These functions *must* be inline or they will break horribly on&n; * SPARC, due to its weird semantics for save/restore flags. extern&n; * inline should prevent the kernel from linking or module from&n; * loading if they are not inlined. */
DECL|function|orinoco_lock
r_extern
r_inline
r_int
id|orinoco_lock
c_func
(paren
r_struct
id|orinoco_private
op_star
id|priv
comma
r_int
r_int
op_star
id|flags
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|priv-&gt;lock
comma
op_star
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;hw_unavailable
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;orinoco_lock() called with hw_unavailable (dev=%p)&bslash;n&quot;
comma
id|priv-&gt;ndev
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|priv-&gt;lock
comma
op_star
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|orinoco_unlock
r_extern
r_inline
r_void
id|orinoco_unlock
c_func
(paren
r_struct
id|orinoco_private
op_star
id|priv
comma
r_int
r_int
op_star
id|flags
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|priv-&gt;lock
comma
op_star
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif /* _ORINOCO_H */
eof
