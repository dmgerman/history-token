multiline_comment|/*&n; * Ethernet driver for Motorola MPC8xx.&n; * Copyright (c) 2000 Michael Leslie &lt;mleslie@lineo.com&gt;&n; * Copyright (c) 1997 Dan Malek (dmalek@jlc.net)&n; *&n; * I copied the basic skeleton from the lance driver, because I did not&n; * know how to write the Linux driver, but I did know how the LANCE worked.&n; *&n; * This version of the driver is somewhat selectable for the different&n; * processor/board combinations.  It works for the boards I know about&n; * now, and should be easily modified to include others.  Some of the&n; * configuration information is contained in &quot;commproc.h&quot; and the&n; * remainder is here.&n; *&n; * Buffer descriptors are kept in the CPM dual port RAM, and the frame&n; * buffers are in the host memory.&n; *&n; * Right now, I am very watseful with the buffers.  I allocate memory&n; * pages and then divide them into 2K frame buffers.  This way I know I&n; * have buffers large enough to hold one frame within one buffer descriptor.&n; * Once I get this working, I will use 64 or 128 byte CPM buffers, which&n; * will be much more memory efficient and will easily handle lots of&n; * small packets.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt; 
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/m68360.h&gt;
multiline_comment|/* #include &lt;asm/8xx_immap.h&gt; */
multiline_comment|/* #include &lt;asm/pgtable.h&gt; */
multiline_comment|/* #include &lt;asm/mpc8xx.h&gt; */
macro_line|#include &lt;asm/bitops.h&gt;
multiline_comment|/* #include &lt;asm/uaccess.h&gt; */
macro_line|#include &lt;asm/commproc.h&gt;
multiline_comment|/*&n; *&t;&t;&t;&t;Theory of Operation&n; *&n; * The MPC8xx CPM performs the Ethernet processing on SCC1.  It can use&n; * an aribtrary number of buffers on byte boundaries, but must have at&n; * least two receive buffers to prevent constant overrun conditions.&n; *&n; * The buffer descriptors are allocated from the CPM dual port memory&n; * with the data buffers allocated from host memory, just like all other&n; * serial communication protocols.  The host memory buffers are allocated&n; * from the free page pool, and then divided into smaller receive and&n; * transmit buffers.  The size of the buffers should be a power of two,&n; * since that nicely divides the page.  This creates a ring buffer&n; * structure similar to the LANCE and other controllers.&n; *&n; * Like the LANCE driver:&n; * The driver runs as two independent, single-threaded flows of control.  One&n; * is the send-packet routine, which enforces single-threaded use by the&n; * cep-&gt;tx_busy flag.  The other thread is the interrupt handler, which is&n; * single threaded by the hardware and other software.&n; *&n; * The send packet thread has partial control over the Tx ring and the&n; * &squot;cep-&gt;tx_busy&squot; flag.  It sets the tx_busy flag whenever it&squot;s queuing a Tx&n; * packet. If the next queue slot is empty, it clears the tx_busy flag when&n; * finished otherwise it sets the &squot;lp-&gt;tx_full&squot; flag.&n; *&n; * The MBX has a control register external to the MPC8xx that has some&n; * control of the Ethernet interface.  Information is in the manual for&n; * your board.&n; *&n; * The RPX boards have an external control/status register.  Consult the&n; * programming documents for details unique to your board.&n; *&n; * For the TQM8xx(L) modules, there is no control register interface.&n; * All functions are directly controlled using I/O pins.  See commproc.h.&n; */
multiline_comment|/* The transmitter timeout&n; */
DECL|macro|TX_TIMEOUT
mdefine_line|#define TX_TIMEOUT&t;(2*HZ)
multiline_comment|/* The number of Tx and Rx buffers.  These are allocated statically here.&n; * We don&squot;t need to allocate pages for the transmitter.  We just use&n; * the skbuffer directly.&n; */
macro_line|#ifdef CONFIG_ENET_BIG_BUFFERS
DECL|macro|RX_RING_SIZE
mdefine_line|#define RX_RING_SIZE&t;&t;64
DECL|macro|TX_RING_SIZE
mdefine_line|#define TX_RING_SIZE&t;&t;64&t;/* Must be power of two */
DECL|macro|TX_RING_MOD_MASK
mdefine_line|#define TX_RING_MOD_MASK&t;63&t;/*   for this to work */
macro_line|#else
DECL|macro|RX_RING_SIZE
mdefine_line|#define RX_RING_SIZE&t;&t;8
DECL|macro|TX_RING_SIZE
mdefine_line|#define TX_RING_SIZE&t;&t;8&t;/* Must be power of two */
DECL|macro|TX_RING_MOD_MASK
mdefine_line|#define TX_RING_MOD_MASK&t;7&t;/*   for this to work */
macro_line|#endif
DECL|macro|CPM_ENET_RX_FRSIZE
mdefine_line|#define CPM_ENET_RX_FRSIZE  2048 /* overkill left over from ppc page-based allocation */
DECL|variable|rx_buf_pool
r_static
r_char
id|rx_buf_pool
(braket
id|RX_RING_SIZE
op_star
id|CPM_ENET_RX_FRSIZE
)braket
suffix:semicolon
multiline_comment|/* The CPM stores dest/src/type, data, and checksum for receive packets.&n; */
DECL|macro|PKT_MAXBUF_SIZE
mdefine_line|#define PKT_MAXBUF_SIZE&t;&t;1518
DECL|macro|PKT_MINBUF_SIZE
mdefine_line|#define PKT_MINBUF_SIZE&t;&t;64
DECL|macro|PKT_MAXBLR_SIZE
mdefine_line|#define PKT_MAXBLR_SIZE&t;&t;1520
multiline_comment|/* The CPM buffer descriptors track the ring buffers.  The rx_bd_base and&n; * tx_bd_base always point to the base of the buffer descriptors.  The&n; * cur_rx and cur_tx point to the currently available buffer.&n; * The dirty_tx tracks the current buffer that is being sent by the&n; * controller.  The cur_tx and dirty_tx are equal under both completely&n; * empty and completely full conditions.  The empty/ready indicator in&n; * the buffer descriptor determines the actual condition.&n; */
DECL|struct|scc_enet_private
r_struct
id|scc_enet_private
(brace
multiline_comment|/* The saved address of a sent-in-place packet/buffer, for skfree(). */
DECL|member|tx_skbuff
r_struct
id|sk_buff
op_star
id|tx_skbuff
(braket
id|TX_RING_SIZE
)braket
suffix:semicolon
DECL|member|skb_cur
id|ushort
id|skb_cur
suffix:semicolon
DECL|member|skb_dirty
id|ushort
id|skb_dirty
suffix:semicolon
multiline_comment|/* CPM dual port RAM relative addresses.&n;&t;*/
DECL|member|rx_bd_base
id|QUICC_BD
op_star
id|rx_bd_base
suffix:semicolon
multiline_comment|/* Address of Rx and Tx buffers. */
DECL|member|tx_bd_base
id|QUICC_BD
op_star
id|tx_bd_base
suffix:semicolon
DECL|member|cur_rx
DECL|member|cur_tx
id|QUICC_BD
op_star
id|cur_rx
comma
op_star
id|cur_tx
suffix:semicolon
multiline_comment|/* The next free ring entry */
DECL|member|dirty_tx
id|QUICC_BD
op_star
id|dirty_tx
suffix:semicolon
multiline_comment|/* The ring entries to be free()ed. */
DECL|member|sccp
r_volatile
r_struct
id|scc_regs
op_star
id|sccp
suffix:semicolon
multiline_comment|/* struct&t;net_device_stats stats; */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|tx_full
id|uint
id|tx_full
suffix:semicolon
multiline_comment|/* spinlock_t lock; */
DECL|member|lock
r_volatile
r_int
r_int
id|lock
suffix:semicolon
)brace
suffix:semicolon
r_static
r_int
id|scc_enet_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|scc_enet_start_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|scc_enet_rx
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* static void scc_enet_interrupt(void *dev_id); */
r_static
r_void
id|scc_enet_interrupt
c_func
(paren
r_int
id|vec
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
suffix:semicolon
r_static
r_int
id|scc_enet_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* static struct net_device_stats *scc_enet_get_stats(struct net_device *dev); */
r_static
r_struct
id|net_device_stats
op_star
id|scc_enet_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|set_multicast_list
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Get this from various configuration locations (depends on board).&n;*/
multiline_comment|/*static&t;ushort&t;my_enet_addr[] = { 0x0800, 0x3e26, 0x1559 };*/
multiline_comment|/* Typically, 860(T) boards use SCC1 for Ethernet, and other 8xx boards&n; * use SCC2.  This is easily extended if necessary.&n; */
DECL|macro|CONFIG_SCC1_ENET
mdefine_line|#define CONFIG_SCC1_ENET /* by default */
macro_line|#ifdef CONFIG_SCC1_ENET
DECL|macro|CPM_CR_ENET
mdefine_line|#define CPM_CR_ENET CPM_CR_CH_SCC1
DECL|macro|PROFF_ENET
mdefine_line|#define PROFF_ENET&t;PROFF_SCC1
DECL|macro|SCC_ENET
mdefine_line|#define SCC_ENET&t;0
DECL|macro|CPMVEC_ENET
mdefine_line|#define CPMVEC_ENET&t;CPMVEC_SCC1
macro_line|#endif
macro_line|#ifdef CONFIG_SCC2_ENET
DECL|macro|CPM_CR_ENET
mdefine_line|#define CPM_CR_ENET&t;CPM_CR_CH_SCC2
DECL|macro|PROFF_ENET
mdefine_line|#define PROFF_ENET&t;PROFF_SCC2
DECL|macro|SCC_ENET
mdefine_line|#define SCC_ENET&t;1&t;&t;/* Index, not number! */
DECL|macro|CPMVEC_ENET
mdefine_line|#define CPMVEC_ENET&t;CPMVEC_SCC2
macro_line|#endif
r_static
r_int
DECL|function|scc_enet_open
id|scc_enet_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
multiline_comment|/* I should reset the ring buffers here, but I don&squot;t yet know&n;&t; * a simple way to do that.&n;&t; * mleslie: That&squot;s no biggie. Worth doing, too.&n;&t; */
multiline_comment|/* netif_start_queue(dev); */
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Always succeed */
)brace
r_static
r_int
DECL|function|scc_enet_start_xmit
id|scc_enet_start_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|scc_enet_private
op_star
id|cep
op_assign
(paren
r_struct
id|scc_enet_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_volatile
id|QUICC_BD
op_star
id|bdp
suffix:semicolon
multiline_comment|/* Fill in a Tx ring entry */
id|bdp
op_assign
id|cep-&gt;cur_tx
suffix:semicolon
macro_line|#ifndef final_version
r_if
c_cond
(paren
id|bdp-&gt;status
op_amp
id|BD_ENET_TX_READY
)paren
(brace
multiline_comment|/* Ooops.  All transmit buffers are full.  Bail out.&n;&t;&t; * This should not happen, since cep-&gt;tx_busy should be set.&n;&t;&t; */
id|printk
c_func
(paren
l_string|&quot;%s: tx queue full!.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Clear all of the status flags.&n;&t; */
id|bdp-&gt;status
op_and_assign
op_complement
id|BD_ENET_TX_STATS
suffix:semicolon
multiline_comment|/* If the frame is short, tell CPM to pad it.&n;&t;*/
r_if
c_cond
(paren
id|skb-&gt;len
op_le
id|ETH_ZLEN
)paren
id|bdp-&gt;status
op_or_assign
id|BD_ENET_TX_PAD
suffix:semicolon
r_else
id|bdp-&gt;status
op_and_assign
op_complement
id|BD_ENET_TX_PAD
suffix:semicolon
multiline_comment|/* Set buffer length and buffer pointer.&n;&t;*/
id|bdp-&gt;length
op_assign
id|skb-&gt;len
suffix:semicolon
multiline_comment|/* bdp-&gt;buf = __pa(skb-&gt;data); */
id|bdp-&gt;buf
op_assign
id|skb-&gt;data
suffix:semicolon
multiline_comment|/* Save skb pointer.&n;&t;*/
id|cep-&gt;tx_skbuff
(braket
id|cep-&gt;skb_cur
)braket
op_assign
id|skb
suffix:semicolon
multiline_comment|/* cep-&gt;stats.tx_bytes += skb-&gt;len; */
multiline_comment|/* TODO: It would really be nice... */
id|cep-&gt;skb_cur
op_assign
(paren
id|cep-&gt;skb_cur
op_plus
l_int|1
)paren
op_amp
id|TX_RING_MOD_MASK
suffix:semicolon
multiline_comment|/* Push the data cache so the CPM does not get stale memory&n;&t; * data.&n;&t; */
multiline_comment|/* &t;flush_dcache_range((unsigned long)(skb-&gt;data), */
multiline_comment|/* &t;&t;&t;&t;&t;(unsigned long)(skb-&gt;data + skb-&gt;len)); */
multiline_comment|/* spin_lock_irq(&amp;cep-&gt;lock); */
multiline_comment|/* TODO: SPINLOCK */
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cep-&gt;lock
OG
l_int|0
)paren
(brace
id|printk
(paren
l_string|&quot;scc_enet_start_xmit() lock == %d&bslash;n&quot;
comma
id|cep-&gt;lock
)paren
suffix:semicolon
)brace
r_else
(brace
id|cep-&gt;lock
op_increment
suffix:semicolon
)brace
multiline_comment|/* Send it on its way.  Tell CPM its ready, interrupt when done,&n;&t; * its the last BD of the frame, and to put the CRC on the end.&n;&t; */
id|bdp-&gt;status
op_or_assign
(paren
id|BD_ENET_TX_READY
op_or
id|BD_ENET_TX_INTR
op_or
id|BD_ENET_TX_LAST
op_or
id|BD_ENET_TX_TC
)paren
suffix:semicolon
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/* If this was the last BD in the ring, start at the beginning again.&n;&t;*/
r_if
c_cond
(paren
id|bdp-&gt;status
op_amp
id|BD_ENET_TX_WRAP
)paren
id|bdp
op_assign
id|cep-&gt;tx_bd_base
suffix:semicolon
r_else
id|bdp
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|bdp-&gt;status
op_amp
id|BD_ENET_TX_READY
)paren
(brace
multiline_comment|/* netif_stop_queue(dev); */
id|cep-&gt;tx_full
op_assign
l_int|1
suffix:semicolon
)brace
id|cep-&gt;cur_tx
op_assign
(paren
id|QUICC_BD
op_star
)paren
id|bdp
suffix:semicolon
multiline_comment|/* spin_unlock_irq(&amp;cep-&gt;lock); */
multiline_comment|/* TODO: SPINLOCK */
id|cep-&gt;lock
op_decrement
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if 0
r_static
r_void
id|scc_enet_timeout
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|scc_enet_private
op_star
id|cep
op_assign
(paren
r_struct
id|scc_enet_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: transmit timed out.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|cep-&gt;stats.tx_errors
op_increment
suffix:semicolon
macro_line|#ifndef final_version
(brace
r_int
id|i
suffix:semicolon
id|QUICC_BD
op_star
id|bdp
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; Ring data dump: cur_tx %p%s cur_rx %p.&bslash;n&quot;
comma
id|cep-&gt;cur_tx
comma
id|cep-&gt;tx_full
ques
c_cond
l_string|&quot; (full)&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|cep-&gt;cur_rx
)paren
suffix:semicolon
id|bdp
op_assign
id|cep-&gt;tx_bd_base
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
id|TX_RING_SIZE
suffix:semicolon
id|i
op_increment
comma
id|bdp
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%04x %04x %08x&bslash;n&quot;
comma
id|bdp-&gt;status
comma
id|bdp-&gt;length
comma
(paren
r_int
)paren
(paren
id|bdp-&gt;buf
)paren
)paren
suffix:semicolon
id|bdp
op_assign
id|cep-&gt;rx_bd_base
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
id|RX_RING_SIZE
suffix:semicolon
id|i
op_increment
comma
id|bdp
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%04x %04x %08x&bslash;n&quot;
comma
id|bdp-&gt;status
comma
id|bdp-&gt;length
comma
(paren
r_int
)paren
(paren
id|bdp-&gt;buf
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* &t;if (!cep-&gt;tx_full) */
multiline_comment|/* &t;&t;netif_wake_queue(dev); */
)brace
macro_line|#endif
multiline_comment|/* The interrupt handler.&n; * This is called from the CPM handler, not the MPC core interrupt.&n; */
multiline_comment|/* static void scc_enet_interrupt(void *dev_id) */
DECL|function|scc_enet_interrupt
r_static
r_void
id|scc_enet_interrupt
c_func
(paren
r_int
id|vec
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
(paren
r_struct
id|net_device
op_star
)paren
id|dev_id
suffix:semicolon
r_volatile
r_struct
id|scc_enet_private
op_star
id|cep
suffix:semicolon
r_volatile
id|QUICC_BD
op_star
id|bdp
suffix:semicolon
id|ushort
id|int_events
suffix:semicolon
r_int
id|must_restart
suffix:semicolon
id|cep
op_assign
(paren
r_struct
id|scc_enet_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
multiline_comment|/* Get the interrupt events that caused us to be here.&n;&t;*/
id|int_events
op_assign
id|cep-&gt;sccp-&gt;scc_scce
suffix:semicolon
id|cep-&gt;sccp-&gt;scc_scce
op_assign
id|int_events
suffix:semicolon
id|must_restart
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Handle receive event in its own function.&n;&t;*/
r_if
c_cond
(paren
id|int_events
op_amp
id|SCCE_ENET_RXF
)paren
id|scc_enet_rx
c_func
(paren
id|dev_id
)paren
suffix:semicolon
multiline_comment|/* Check for a transmit error.  The manual is a little unclear&n;&t; * about this, so the debug code until I get it figured out.  It&n;&t; * appears that if TXE is set, then TXB is not set.  However,&n;&t; * if carrier sense is lost during frame transmission, the TXE&n;&t; * bit is set, &quot;and continues the buffer transmission normally.&quot;&n;&t; * I don&squot;t know if &quot;normally&quot; implies TXB is set when the buffer&n;&t; * descriptor is closed.....trial and error :-).&n;&t; */
multiline_comment|/* Transmit OK, or non-fatal error.  Update the buffer descriptors.&n;&t;*/
r_if
c_cond
(paren
id|int_events
op_amp
(paren
id|SCCE_ENET_TXE
op_or
id|SCCE_ENET_TXB
)paren
)paren
(brace
multiline_comment|/* spin_lock(&amp;cep-&gt;lock); */
multiline_comment|/* TODO: SPINLOCK */
multiline_comment|/* local_irq_disable(); */
r_if
c_cond
(paren
id|cep-&gt;lock
OG
l_int|0
)paren
(brace
id|printk
(paren
l_string|&quot;scc_enet_interrupt() lock == %d&bslash;n&quot;
comma
id|cep-&gt;lock
)paren
suffix:semicolon
)brace
r_else
(brace
id|cep-&gt;lock
op_increment
suffix:semicolon
)brace
id|bdp
op_assign
id|cep-&gt;dirty_tx
suffix:semicolon
r_while
c_loop
(paren
(paren
id|bdp-&gt;status
op_amp
id|BD_ENET_TX_READY
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|bdp
op_eq
id|cep-&gt;cur_tx
)paren
op_logical_and
(paren
id|cep-&gt;tx_full
op_eq
l_int|0
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|bdp-&gt;status
op_amp
id|BD_ENET_TX_HB
)paren
multiline_comment|/* No heartbeat */
id|cep-&gt;stats.tx_heartbeat_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|bdp-&gt;status
op_amp
id|BD_ENET_TX_LC
)paren
multiline_comment|/* Late collision */
id|cep-&gt;stats.tx_window_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|bdp-&gt;status
op_amp
id|BD_ENET_TX_RL
)paren
multiline_comment|/* Retrans limit */
id|cep-&gt;stats.tx_aborted_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|bdp-&gt;status
op_amp
id|BD_ENET_TX_UN
)paren
multiline_comment|/* Underrun */
id|cep-&gt;stats.tx_fifo_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|bdp-&gt;status
op_amp
id|BD_ENET_TX_CSL
)paren
multiline_comment|/* Carrier lost */
id|cep-&gt;stats.tx_carrier_errors
op_increment
suffix:semicolon
multiline_comment|/* No heartbeat or Lost carrier are not really bad errors.&n;&t;&t; * The others require a restart transmit command.&n;&t;&t; */
r_if
c_cond
(paren
id|bdp-&gt;status
op_amp
(paren
id|BD_ENET_TX_LC
op_or
id|BD_ENET_TX_RL
op_or
id|BD_ENET_TX_UN
)paren
)paren
(brace
id|must_restart
op_assign
l_int|1
suffix:semicolon
id|cep-&gt;stats.tx_errors
op_increment
suffix:semicolon
)brace
id|cep-&gt;stats.tx_packets
op_increment
suffix:semicolon
multiline_comment|/* Deferred means some collisions occurred during transmit,&n;&t;&t; * but we eventually sent the packet OK.&n;&t;&t; */
r_if
c_cond
(paren
id|bdp-&gt;status
op_amp
id|BD_ENET_TX_DEF
)paren
id|cep-&gt;stats.collisions
op_increment
suffix:semicolon
multiline_comment|/* Free the sk buffer associated with this last transmit.&n;&t;&t;*/
multiline_comment|/* dev_kfree_skb_irq(cep-&gt;tx_skbuff[cep-&gt;skb_dirty]); */
id|dev_kfree_skb
(paren
id|cep-&gt;tx_skbuff
(braket
id|cep-&gt;skb_dirty
)braket
)paren
suffix:semicolon
id|cep-&gt;skb_dirty
op_assign
(paren
id|cep-&gt;skb_dirty
op_plus
l_int|1
)paren
op_amp
id|TX_RING_MOD_MASK
suffix:semicolon
multiline_comment|/* Update pointer to next buffer descriptor to be transmitted.&n;&t;&t;*/
r_if
c_cond
(paren
id|bdp-&gt;status
op_amp
id|BD_ENET_TX_WRAP
)paren
id|bdp
op_assign
id|cep-&gt;tx_bd_base
suffix:semicolon
r_else
id|bdp
op_increment
suffix:semicolon
multiline_comment|/* I don&squot;t know if we can be held off from processing these&n;&t;&t; * interrupts for more than one frame time.  I really hope&n;&t;&t; * not.  In such a case, we would now want to check the&n;&t;&t; * currently available BD (cur_tx) and determine if any&n;&t;&t; * buffers between the dirty_tx and cur_tx have also been&n;&t;&t; * sent.  We would want to process anything in between that&n;&t;&t; * does not have BD_ENET_TX_READY set.&n;&t;&t; */
multiline_comment|/* Since we have freed up a buffer, the ring is no longer&n;&t;&t; * full.&n;&t;&t; */
r_if
c_cond
(paren
id|cep-&gt;tx_full
)paren
(brace
id|cep-&gt;tx_full
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* &t;&t;&t;if (netif_queue_stopped(dev)) */
multiline_comment|/* &t;&t;&t;&t;netif_wake_queue(dev); */
)brace
id|cep-&gt;dirty_tx
op_assign
(paren
id|QUICC_BD
op_star
)paren
id|bdp
suffix:semicolon
)brace
r_if
c_cond
(paren
id|must_restart
)paren
(brace
r_volatile
id|QUICC
op_star
id|cp
suffix:semicolon
multiline_comment|/* Some transmit errors cause the transmitter to shut&n;&t;&t; * down.  We now issue a restart transmit.  Since the&n;&t;&t; * errors close the BD and update the pointers, the restart&n;&t;&t; * _should_ pick up without having to reset any of our&n;&t;&t; * pointers either.&n;&t;&t; */
id|cp
op_assign
id|pquicc
suffix:semicolon
id|cp-&gt;cp_cr
op_assign
id|mk_cr_cmd
c_func
(paren
id|CPM_CR_ENET
comma
id|CPM_CR_RESTART_TX
)paren
op_or
id|CPM_CR_FLG
suffix:semicolon
r_while
c_loop
(paren
id|cp-&gt;cp_cr
op_amp
id|CPM_CR_FLG
)paren
suffix:semicolon
)brace
multiline_comment|/* spin_unlock(&amp;cep-&gt;lock); */
multiline_comment|/* TODO: SPINLOCK */
multiline_comment|/* sti(); */
id|cep-&gt;lock
op_decrement
suffix:semicolon
)brace
multiline_comment|/* Check for receive busy, i.e. packets coming but no place to&n;&t; * put them.  This &quot;can&squot;t happen&quot; because the receive interrupt&n;&t; * is tossing previous frames.&n;&t; */
r_if
c_cond
(paren
id|int_events
op_amp
id|SCCE_ENET_BSY
)paren
(brace
id|cep-&gt;stats.rx_dropped
op_increment
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPM ENET: BSY can&squot;t happen.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/* During a receive, the cur_rx points to the current incoming buffer.&n; * When we update through the ring, if the next incoming buffer has&n; * not been given to the system, we just set the empty indicator,&n; * effectively tossing the packet.&n; */
r_static
r_int
DECL|function|scc_enet_rx
id|scc_enet_rx
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|scc_enet_private
op_star
id|cep
suffix:semicolon
r_volatile
id|QUICC_BD
op_star
id|bdp
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|ushort
id|pkt_len
suffix:semicolon
id|cep
op_assign
(paren
r_struct
id|scc_enet_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
multiline_comment|/* First, grab all of the stats for the incoming packet.&n;&t; * These get messed up if we get called due to a busy condition.&n;&t; */
id|bdp
op_assign
id|cep-&gt;cur_rx
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|bdp-&gt;status
op_amp
id|BD_ENET_RX_EMPTY
)paren
r_break
suffix:semicolon
macro_line|#ifndef final_version
multiline_comment|/* Since we have allocated space to hold a complete frame, both&n;&t;&t; * the first and last indicators should be set.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|bdp-&gt;status
op_amp
(paren
id|BD_ENET_RX_FIRST
op_or
id|BD_ENET_RX_LAST
)paren
)paren
op_ne
(paren
id|BD_ENET_RX_FIRST
op_or
id|BD_ENET_RX_LAST
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;CPM ENET: rcv is not first+last&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Frame too long or too short.&n;&t;&t; */
r_if
c_cond
(paren
id|bdp-&gt;status
op_amp
(paren
id|BD_ENET_RX_LG
op_or
id|BD_ENET_RX_SH
)paren
)paren
id|cep-&gt;stats.rx_length_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|bdp-&gt;status
op_amp
id|BD_ENET_RX_NO
)paren
multiline_comment|/* Frame alignment */
id|cep-&gt;stats.rx_frame_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|bdp-&gt;status
op_amp
id|BD_ENET_RX_CR
)paren
multiline_comment|/* CRC Error */
id|cep-&gt;stats.rx_crc_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|bdp-&gt;status
op_amp
id|BD_ENET_RX_OV
)paren
multiline_comment|/* FIFO overrun */
id|cep-&gt;stats.rx_crc_errors
op_increment
suffix:semicolon
multiline_comment|/* Report late collisions as a frame error.&n;&t;&t; * On this error, the BD is closed, but we don&squot;t know what we&n;&t;&t; * have in the buffer.  So, just drop this frame on the floor.&n;&t;&t; */
r_if
c_cond
(paren
id|bdp-&gt;status
op_amp
id|BD_ENET_RX_CL
)paren
(brace
id|cep-&gt;stats.rx_frame_errors
op_increment
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Process the incoming frame.&n;&t;&t;&t; */
id|cep-&gt;stats.rx_packets
op_increment
suffix:semicolon
id|pkt_len
op_assign
id|bdp-&gt;length
suffix:semicolon
multiline_comment|/* cep-&gt;stats.rx_bytes += pkt_len; */
multiline_comment|/* TODO: It would really be nice... */
multiline_comment|/* This does 16 byte alignment, much more than we need.&n;&t;&t;&t; * The packet length includes FCS, but we don&squot;t want to&n;&t;&t;&t; * include that when passing upstream as it messes up&n;&t;&t;&t; * bridging applications.&n;&t;&t;&t; */
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|pkt_len
op_minus
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Memory squeeze, dropping packet.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|cep-&gt;stats.rx_dropped
op_increment
suffix:semicolon
)brace
r_else
(brace
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb_put
c_func
(paren
id|skb
comma
id|pkt_len
op_minus
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Make room */
id|eth_copy_and_sum
c_func
(paren
id|skb
comma
(paren
r_int
r_char
op_star
)paren
id|bdp-&gt;buf
comma
id|pkt_len
op_minus
l_int|4
comma
l_int|0
)paren
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|eth_type_trans
c_func
(paren
id|skb
comma
id|dev
)paren
suffix:semicolon
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Clear the status flags for this buffer.&n;&t;&t; */
id|bdp-&gt;status
op_and_assign
op_complement
id|BD_ENET_RX_STATS
suffix:semicolon
multiline_comment|/* Mark the buffer empty.&n;&t;&t; */
id|bdp-&gt;status
op_or_assign
id|BD_ENET_RX_EMPTY
suffix:semicolon
multiline_comment|/* Update BD pointer to next entry.&n;&t;&t; */
r_if
c_cond
(paren
id|bdp-&gt;status
op_amp
id|BD_ENET_RX_WRAP
)paren
id|bdp
op_assign
id|cep-&gt;rx_bd_base
suffix:semicolon
r_else
id|bdp
op_increment
suffix:semicolon
)brace
id|cep-&gt;cur_rx
op_assign
(paren
id|QUICC_BD
op_star
)paren
id|bdp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|scc_enet_close
id|scc_enet_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
multiline_comment|/* Don&squot;t know what to do yet.&n;&t;*/
multiline_comment|/* netif_stop_queue(dev); */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* static struct net_device_stats *scc_enet_get_stats(struct net_device *dev) */
DECL|function|scc_enet_get_stats
r_static
r_struct
id|net_device_stats
op_star
id|scc_enet_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|scc_enet_private
op_star
id|cep
op_assign
(paren
r_struct
id|scc_enet_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_return
op_amp
id|cep-&gt;stats
suffix:semicolon
)brace
multiline_comment|/* Set or clear the multicast filter for this adaptor.&n; * Skeleton taken from sunlance driver.&n; * The CPM Ethernet implementation allows Multicast as well as individual&n; * MAC address filtering.  Some of the drivers check to make sure it is&n; * a group multicast address, and discard those that are not.  I guess I&n; * will do the same for now, but just remove the test if you want&n; * individual filtering as well (do the upper net layers want or support&n; * this kind of feature?).&n; */
DECL|function|set_multicast_list
r_static
r_void
id|set_multicast_list
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|scc_enet_private
op_star
id|cep
suffix:semicolon
r_struct
id|dev_mc_list
op_star
id|dmi
suffix:semicolon
id|u_char
op_star
id|mcptr
comma
op_star
id|tdptr
suffix:semicolon
r_volatile
id|scc_enet_t
op_star
id|ep
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_volatile
id|QUICC
op_star
id|cp
op_assign
id|pquicc
suffix:semicolon
id|cep
op_assign
(paren
r_struct
id|scc_enet_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
multiline_comment|/* Get pointer to SCC area in parameter RAM.&n;&t;*/
id|ep
op_assign
(paren
id|scc_enet_t
op_star
)paren
id|dev-&gt;base_addr
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_PROMISC
)paren
(brace
multiline_comment|/* Log any net taps. */
id|printk
c_func
(paren
l_string|&quot;%s: Promiscuous mode enabled.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|cep-&gt;sccp-&gt;scc_psmr
op_or_assign
id|ETHER_PRO
suffix:semicolon
)brace
r_else
(brace
id|cep-&gt;sccp-&gt;scc_psmr
op_and_assign
op_complement
id|ETHER_PRO
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_ALLMULTI
)paren
(brace
multiline_comment|/* Catch all multicast addresses, so set the&n;&t;&t;&t; * filter to all 1&squot;s.&n;&t;&t;&t; */
id|ep-&gt;sen_gaddr1
op_assign
l_int|0xffff
suffix:semicolon
id|ep-&gt;sen_gaddr2
op_assign
l_int|0xffff
suffix:semicolon
id|ep-&gt;sen_gaddr3
op_assign
l_int|0xffff
suffix:semicolon
id|ep-&gt;sen_gaddr4
op_assign
l_int|0xffff
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Clear filter and add the addresses in the list.&n;&t;&t;&t;*/
id|ep-&gt;sen_gaddr1
op_assign
l_int|0
suffix:semicolon
id|ep-&gt;sen_gaddr2
op_assign
l_int|0
suffix:semicolon
id|ep-&gt;sen_gaddr3
op_assign
l_int|0
suffix:semicolon
id|ep-&gt;sen_gaddr4
op_assign
l_int|0
suffix:semicolon
id|dmi
op_assign
id|dev-&gt;mc_list
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
id|dev-&gt;mc_count
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Only support group multicast for now.&n;&t;&t;&t;&t;*/
r_if
c_cond
(paren
op_logical_neg
(paren
id|dmi-&gt;dmi_addr
(braket
l_int|0
)braket
op_amp
l_int|1
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* The address in dmi_addr is LSB first,&n;&t;&t;&t;&t; * and taddr is MSB first.  We have to&n;&t;&t;&t;&t; * copy bytes MSB first from dmi_addr.&n;&t;&t;&t;&t; */
id|mcptr
op_assign
(paren
id|u_char
op_star
)paren
id|dmi-&gt;dmi_addr
op_plus
l_int|5
suffix:semicolon
id|tdptr
op_assign
(paren
id|u_char
op_star
)paren
op_amp
id|ep-&gt;sen_taddrh
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|6
suffix:semicolon
id|j
op_increment
)paren
op_star
id|tdptr
op_increment
op_assign
op_star
id|mcptr
op_decrement
suffix:semicolon
multiline_comment|/* Ask CPM to run CRC and set bit in&n;&t;&t;&t;&t; * filter mask.&n;&t;&t;&t;&t; */
id|cp-&gt;cp_cr
op_assign
id|mk_cr_cmd
c_func
(paren
id|CPM_CR_ENET
comma
id|CPM_CR_SET_GADDR
)paren
op_or
id|CPM_CR_FLG
suffix:semicolon
multiline_comment|/* this delay is necessary here -- Cort */
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_while
c_loop
(paren
id|cp-&gt;cp_cr
op_amp
id|CPM_CR_FLG
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
multiline_comment|/* Initialize the CPM Ethernet on SCC.&n; */
DECL|function|scc_enet_init
r_int
id|scc_enet_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_struct
id|scc_enet_private
op_star
id|cep
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_int
r_char
op_star
id|eap
suffix:semicolon
multiline_comment|/* unsigned long&t;mem_addr; */
multiline_comment|/* pte_t&t;&t;*pte; */
multiline_comment|/* bd_t&t;&t;*bd; */
multiline_comment|/* `board tag&squot; used by ppc - TODO: integrate uC bootloader vars */
r_volatile
id|QUICC_BD
op_star
id|bdp
suffix:semicolon
r_volatile
id|QUICC
op_star
id|cp
suffix:semicolon
r_volatile
r_struct
id|scc_regs
op_star
id|sccp
suffix:semicolon
r_volatile
r_struct
id|ethernet_pram
op_star
id|ep
suffix:semicolon
multiline_comment|/* volatile&t;immap_t&t;&t;*immap; */
id|cp
op_assign
id|pquicc
suffix:semicolon
multiline_comment|/* Get pointer to Communication Processor */
multiline_comment|/* immap = (immap_t *)IMAP_ADDR; */
multiline_comment|/* and to internal registers */
multiline_comment|/* bd = (bd_t *)__res; */
multiline_comment|/* Allocate some private information.&n;&t;*/
id|cep
op_assign
(paren
r_struct
id|scc_enet_private
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|cep
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
id|cep
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|cep
)paren
)paren
suffix:semicolon
multiline_comment|/* __clear_user(cep,sizeof(*cep)); */
multiline_comment|/* spin_lock_init(&amp;cep-&gt;lock); */
multiline_comment|/* TODO: SPINLOCK */
multiline_comment|/* Create an Ethernet device instance.&n;&t; */
id|dev
op_assign
id|init_etherdev
c_func
(paren
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Get pointer to SCC area in parameter RAM.&n;&t;*/
multiline_comment|/* ep = (ethernet_pram *)(&amp;cp-&gt;cp_dparam[PROFF_ENET]); */
id|ep
op_assign
op_amp
id|pquicc-&gt;pram
(braket
id|SCC_ENET
)braket
dot
id|enet_scc
suffix:semicolon
multiline_comment|/* And another to the SCC register area.&n;&t;*/
id|sccp
op_assign
op_amp
id|pquicc-&gt;scc_regs
(braket
id|SCC_ENET
)braket
suffix:semicolon
id|cep-&gt;sccp
op_assign
id|sccp
suffix:semicolon
multiline_comment|/* Keep the pointer handy */
multiline_comment|/* Disable receive and transmit in case EPPC-Bug started it.&n;&t;*/
id|sccp-&gt;scc_gsmr.w.low
op_and_assign
op_complement
(paren
id|SCC_GSMRL_ENR
op_or
id|SCC_GSMRL_ENT
)paren
suffix:semicolon
multiline_comment|/* Set up 360 pins for SCC interface to ethernet transceiver.&n;&t; * Pin mappings (PA_xx and PC_xx) are defined in commproc.h&n;&t; */
multiline_comment|/* Configure port A pins for Txd and Rxd.&n;&t; */
id|pquicc-&gt;pio_papar
op_or_assign
(paren
id|PA_ENET_RXD
op_or
id|PA_ENET_TXD
)paren
suffix:semicolon
id|pquicc-&gt;pio_padir
op_and_assign
op_complement
(paren
id|PA_ENET_RXD
op_or
id|PA_ENET_TXD
)paren
suffix:semicolon
id|pquicc-&gt;pio_paodr
op_and_assign
op_complement
id|PA_ENET_TXD
suffix:semicolon
multiline_comment|/* Configure port C pins to enable CLSN and RENA.&n;&t; */
id|pquicc-&gt;pio_pcpar
op_and_assign
op_complement
(paren
id|PC_ENET_CLSN
op_or
id|PC_ENET_RENA
)paren
suffix:semicolon
id|pquicc-&gt;pio_pcdir
op_and_assign
op_complement
(paren
id|PC_ENET_CLSN
op_or
id|PC_ENET_RENA
)paren
suffix:semicolon
id|pquicc-&gt;pio_pcso
op_or_assign
(paren
id|PC_ENET_CLSN
op_or
id|PC_ENET_RENA
)paren
suffix:semicolon
multiline_comment|/* Configure port A for TCLK and RCLK.&n;&t;*/
id|pquicc-&gt;pio_papar
op_or_assign
(paren
id|PA_ENET_TCLK
op_or
id|PA_ENET_RCLK
)paren
suffix:semicolon
id|pquicc-&gt;pio_padir
op_and_assign
op_complement
(paren
id|PA_ENET_TCLK
op_or
id|PA_ENET_RCLK
)paren
suffix:semicolon
multiline_comment|/* Configure Serial Interface clock routing.&n;&t; * First, clear all SCC bits to zero, then set the ones we want.&n;&t; */
id|pquicc-&gt;si_sicr
op_and_assign
op_complement
id|SICR_ENET_MASK
suffix:semicolon
id|pquicc-&gt;si_sicr
op_or_assign
id|SICR_ENET_CLKRT
suffix:semicolon
multiline_comment|/* Allocate space for the buffer descriptors in the DP ram.&n;&t; * These are relative offsets in the DP ram address space.&n;&t; * Initialize base addresses for the buffer descriptors.&n;&t; */
id|i
op_assign
id|m360_cpm_dpalloc
c_func
(paren
r_sizeof
(paren
id|QUICC_BD
)paren
op_star
id|RX_RING_SIZE
)paren
suffix:semicolon
id|ep-&gt;rbase
op_assign
id|i
suffix:semicolon
id|cep-&gt;rx_bd_base
op_assign
(paren
id|QUICC_BD
op_star
)paren
(paren
(paren
id|uint
)paren
id|pquicc
op_plus
id|i
)paren
suffix:semicolon
id|i
op_assign
id|m360_cpm_dpalloc
c_func
(paren
r_sizeof
(paren
id|QUICC_BD
)paren
op_star
id|TX_RING_SIZE
)paren
suffix:semicolon
id|ep-&gt;tbase
op_assign
id|i
suffix:semicolon
id|cep-&gt;tx_bd_base
op_assign
(paren
id|QUICC_BD
op_star
)paren
(paren
(paren
id|uint
)paren
id|pquicc
op_plus
id|i
)paren
suffix:semicolon
id|cep-&gt;dirty_tx
op_assign
id|cep-&gt;cur_tx
op_assign
id|cep-&gt;tx_bd_base
suffix:semicolon
id|cep-&gt;cur_rx
op_assign
id|cep-&gt;rx_bd_base
suffix:semicolon
multiline_comment|/* Issue init Rx BD command for SCC.&n;&t; * Manual says to perform an Init Rx parameters here.  We have&n;&t; * to perform both Rx and Tx because the SCC may have been&n;&t; * already running. [In uCquicc&squot;s case, I don&squot;t think that is so - mles]&n;&t; * In addition, we have to do it later because we don&squot;t yet have&n;&t; * all of the BD control/status set properly.&n;&t;cp-&gt;cp_cpcr = mk_cr_cmd(CPM_CR_ENET, CPM_CR_INIT_RX) | CPM_CR_FLG;&n;&t;while (cp-&gt;cp_cpcr &amp; CPM_CR_FLG);&n;&t; */
multiline_comment|/* Initialize function code registers for big-endian.&n;&t;*/
id|ep-&gt;rfcr
op_assign
(paren
id|SCC_EB
op_or
id|SCC_FC_DMA
)paren
suffix:semicolon
id|ep-&gt;tfcr
op_assign
(paren
id|SCC_EB
op_or
id|SCC_FC_DMA
)paren
suffix:semicolon
multiline_comment|/* Set maximum bytes per receive buffer.&n;&t; * This appears to be an Ethernet frame size, not the buffer&n;&t; * fragment size.  It must be a multiple of four.&n;&t; */
id|ep-&gt;mrblr
op_assign
id|PKT_MAXBLR_SIZE
suffix:semicolon
multiline_comment|/* Set CRC preset and mask.&n;&t; */
id|ep-&gt;c_pres
op_assign
l_int|0xffffffff
suffix:semicolon
id|ep-&gt;c_mask
op_assign
l_int|0xdebb20e3
suffix:semicolon
multiline_comment|/* see 360UM p. 7-247 */
id|ep-&gt;crcec
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* CRC Error counter */
id|ep-&gt;alec
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* alignment error counter */
id|ep-&gt;disfc
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* discard frame counter */
id|ep-&gt;pads
op_assign
l_int|0x8888
suffix:semicolon
multiline_comment|/* Tx short frame pad character */
id|ep-&gt;ret_lim
op_assign
l_int|0x000f
suffix:semicolon
multiline_comment|/* Retry limit threshold */
id|ep-&gt;mflr
op_assign
id|PKT_MAXBUF_SIZE
suffix:semicolon
multiline_comment|/* maximum frame length register */
id|ep-&gt;minflr
op_assign
id|PKT_MINBUF_SIZE
suffix:semicolon
multiline_comment|/* minimum frame length register */
id|ep-&gt;maxd1
op_assign
id|PKT_MAXBLR_SIZE
suffix:semicolon
multiline_comment|/* maximum DMA1 length */
id|ep-&gt;maxd2
op_assign
id|PKT_MAXBLR_SIZE
suffix:semicolon
multiline_comment|/* maximum DMA2 length */
multiline_comment|/* Clear hash tables, group and individual.&n;&t; */
id|ep-&gt;gaddr1
op_assign
id|ep-&gt;gaddr2
op_assign
id|ep-&gt;gaddr3
op_assign
id|ep-&gt;gaddr4
op_assign
l_int|0
suffix:semicolon
id|ep-&gt;iaddr1
op_assign
id|ep-&gt;iaddr2
op_assign
id|ep-&gt;iaddr3
op_assign
id|ep-&gt;iaddr4
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set Ethernet station address.&n;&t; *&n;&t; * The uCbootloader provides a hook to the kernel to retrieve&n;&t; * stuff like the MAC address. This is retrieved in config_BSP()&n;&t; */
macro_line|#if defined (CONFIG_UCQUICC)
(brace
r_extern
r_int
r_char
op_star
id|scc1_hwaddr
suffix:semicolon
id|eap
op_assign
(paren
r_char
op_star
)paren
id|ep-&gt;paddr.b
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|5
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
op_star
id|eap
op_increment
op_assign
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
id|scc1_hwaddr
(braket
id|i
)braket
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* #ifndef CONFIG_MBX */
multiline_comment|/* &t;eap = (unsigned char *)&amp;(ep-&gt;paddrh); */
multiline_comment|/* &t;for (i=5; i&gt;=0; i--) */
multiline_comment|/* &t;&t;*eap++ = dev-&gt;dev_addr[i] = bd-&gt;bi_enetaddr[i]; */
multiline_comment|/* #else */
multiline_comment|/* &t;for (i=5; i&gt;=0; i--) */
multiline_comment|/* &t;&t;dev-&gt;dev_addr[i] = *eap++; */
multiline_comment|/* #endif */
id|ep-&gt;p_per
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* &squot;cause the book says so */
id|ep-&gt;taddr_l
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* temp address (LSB) */
id|ep-&gt;taddr_m
op_assign
l_int|0
suffix:semicolon
id|ep-&gt;taddr_h
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* temp address (MSB) */
multiline_comment|/* Now allocate the host memory pages and initialize the&n;&t; * buffer descriptors.&n;&t; */
multiline_comment|/* initialize rx buffer descriptors */
id|bdp
op_assign
id|cep-&gt;tx_bd_base
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
(paren
id|TX_RING_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|j
op_increment
)paren
(brace
id|bdp-&gt;buf
op_assign
l_int|0
suffix:semicolon
id|bdp-&gt;status
op_assign
l_int|0
suffix:semicolon
id|bdp
op_increment
suffix:semicolon
)brace
id|bdp-&gt;buf
op_assign
l_int|0
suffix:semicolon
id|bdp-&gt;status
op_assign
id|BD_SC_WRAP
suffix:semicolon
multiline_comment|/* initialize rx buffer descriptors */
id|bdp
op_assign
id|cep-&gt;rx_bd_base
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
(paren
id|RX_RING_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|j
op_increment
)paren
(brace
id|bdp-&gt;buf
op_assign
op_amp
id|rx_buf_pool
(braket
id|j
op_star
id|CPM_ENET_RX_FRSIZE
)braket
suffix:semicolon
id|bdp-&gt;status
op_assign
id|BD_SC_EMPTY
op_or
id|BD_SC_INTRPT
suffix:semicolon
id|bdp
op_increment
suffix:semicolon
)brace
id|bdp-&gt;buf
op_assign
op_amp
id|rx_buf_pool
(braket
id|j
op_star
id|CPM_ENET_RX_FRSIZE
)braket
suffix:semicolon
id|bdp-&gt;status
op_assign
id|BD_SC_WRAP
op_or
id|BD_SC_EMPTY
op_or
id|BD_SC_INTRPT
suffix:semicolon
multiline_comment|/* Let&squot;s re-initialize the channel now.  We have to do it later&n;&t; * than the manual describes because we have just now finished&n;&t; * the BD initialization.&n;&t; */
id|cp-&gt;cp_cr
op_assign
id|mk_cr_cmd
c_func
(paren
id|CPM_CR_ENET
comma
id|CPM_CR_INIT_TRX
)paren
op_or
id|CPM_CR_FLG
suffix:semicolon
r_while
c_loop
(paren
id|cp-&gt;cp_cr
op_amp
id|CPM_CR_FLG
)paren
suffix:semicolon
id|cep-&gt;skb_cur
op_assign
id|cep-&gt;skb_dirty
op_assign
l_int|0
suffix:semicolon
id|sccp-&gt;scc_scce
op_assign
l_int|0xffff
suffix:semicolon
multiline_comment|/* Clear any pending events */
multiline_comment|/* Enable interrupts for transmit error, complete frame&n;&t; * received, and any transmit buffer we have also set the&n;&t; * interrupt flag.&n;&t; */
id|sccp-&gt;scc_sccm
op_assign
(paren
id|SCCE_ENET_TXE
op_or
id|SCCE_ENET_RXF
op_or
id|SCCE_ENET_TXB
)paren
suffix:semicolon
multiline_comment|/* Install our interrupt handler.&n;&t; */
multiline_comment|/* cpm_install_handler(CPMVEC_ENET, scc_enet_interrupt, dev); */
id|request_irq
c_func
(paren
id|CPMVEC_ENET
comma
id|scc_enet_interrupt
comma
id|IRQ_FLG_LOCK
comma
id|dev-&gt;name
comma
(paren
r_void
op_star
)paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Set GSMR_H to enable all normal operating modes.&n;&t; * Set GSMR_L to enable Ethernet to MC68160.&n;&t; */
id|sccp-&gt;scc_gsmr.w.high
op_assign
l_int|0
suffix:semicolon
id|sccp-&gt;scc_gsmr.w.low
op_assign
(paren
id|SCC_GSMRL_TCI
op_or
id|SCC_GSMRL_TPL_48
op_or
id|SCC_GSMRL_TPP_10
op_or
id|SCC_GSMRL_MODE_ENET
)paren
suffix:semicolon
multiline_comment|/* Set sync/delimiters.&n;&t; */
id|sccp-&gt;scc_dsr
op_assign
l_int|0xd555
suffix:semicolon
multiline_comment|/* Set processing mode.  Use Ethernet CRC, catch broadcast, and&n;&t; * start frame search 22 bit times after RENA.&n;&t; */
id|sccp-&gt;scc_psmr
op_assign
(paren
id|SCC_PMSR_ENCRC
multiline_comment|/* Ethernet CRC mode */
multiline_comment|/* | SCC_PSMR_HBC */
multiline_comment|/* Enable heartbeat */
multiline_comment|/* | SCC_PMSR_PRO */
multiline_comment|/* Promiscuous mode */
multiline_comment|/* | SCC_PMSR_FDE */
multiline_comment|/* Full duplex enable */
op_or
id|ETHER_NIB_22
)paren
suffix:semicolon
multiline_comment|/* sccp-&gt;scc_psmr = (SCC_PMSR_PRO | ETHER_CRC_32 | ETHER_NIB_22); */
multiline_comment|/* It is now OK to enable the Ethernet transmitter.&n;&t; * Unfortunately, there are board implementation differences here.&n;&t; */
macro_line|#if defined(CONFIG_UCQUICC)
multiline_comment|/* &t; immap-&gt;im_ioport.iop_pcpar |= PC_ENET_TENA; */
multiline_comment|/* &t; immap-&gt;im_ioport.iop_pcdir &amp;= ~PC_ENET_TENA; */
id|cp-&gt;pio_pcpar
op_or_assign
id|PC_ENET_TENA
suffix:semicolon
multiline_comment|/* t_en */
id|cp-&gt;pio_pcdir
op_and_assign
op_complement
id|PC_ENET_TENA
suffix:semicolon
id|cp-&gt;pip_pbpar
op_and_assign
op_complement
(paren
l_int|0x00000200
)paren
suffix:semicolon
multiline_comment|/* power up ethernet transceiver */
id|cp-&gt;pip_pbdir
op_or_assign
(paren
l_int|0x00000200
)paren
suffix:semicolon
id|cp-&gt;pip_pbdat
op_or_assign
(paren
l_int|0x00000200
)paren
suffix:semicolon
macro_line|#endif
id|dev-&gt;base_addr
op_assign
(paren
r_int
r_int
)paren
id|ep
suffix:semicolon
id|dev-&gt;priv
op_assign
id|cep
suffix:semicolon
macro_line|#if 0
id|dev-&gt;name
op_assign
l_string|&quot;CPM_ENET&quot;
suffix:semicolon
macro_line|#endif
multiline_comment|/* The CPM Ethernet specific entries in the device structure. */
id|dev-&gt;open
op_assign
id|scc_enet_open
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|scc_enet_start_xmit
suffix:semicolon
multiline_comment|/* dev-&gt;tx_timeout = scc_enet_timeout; */
multiline_comment|/* dev-&gt;watchdog_timeo = TX_TIMEOUT; */
id|dev-&gt;stop
op_assign
id|scc_enet_close
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|scc_enet_get_stats
suffix:semicolon
id|dev-&gt;set_multicast_list
op_assign
id|set_multicast_list
suffix:semicolon
multiline_comment|/* And last, enable the transmit and receive processing.&n;&t;*/
id|sccp-&gt;scc_gsmr.w.low
op_or_assign
(paren
id|SCC_GSMRL_ENR
op_or
id|SCC_GSMRL_ENT
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: CPM ENET Version 0.3, &quot;
comma
id|dev-&gt;name
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
l_int|5
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%02x:&quot;
comma
id|dev-&gt;dev_addr
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%02x&bslash;n&quot;
comma
id|dev-&gt;dev_addr
(braket
l_int|5
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|m68360_enet_probe
r_int
id|m68360_enet_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_return
id|scc_enet_init
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Local variables:&n; *  c-indent-level: 4&n; *  c-basic-offset: 4&n; *  tab-width: 4&n; * End:&n; */
eof
