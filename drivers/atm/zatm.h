multiline_comment|/* drivers/atm/zatm.h - ZeitNet ZN122x device driver declarations */
multiline_comment|/* Written 1995-1998 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef DRIVER_ATM_ZATM_H
DECL|macro|DRIVER_ATM_ZATM_H
mdefine_line|#define DRIVER_ATM_ZATM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/atm.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/sonet.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
DECL|macro|DEV_LABEL
mdefine_line|#define DEV_LABEL&t;&quot;zatm&quot;
DECL|macro|MAX_AAL5_PDU
mdefine_line|#define MAX_AAL5_PDU&t;10240&t;/* allocate for AAL5 PDUs of this size */
DECL|macro|MAX_RX_SIZE_LD
mdefine_line|#define MAX_RX_SIZE_LD&t;14&t;/* ceil(log2((MAX_AAL5_PDU+47)/48)) */
DECL|macro|LOW_MARK
mdefine_line|#define LOW_MARK&t;12&t;/* start adding new buffers if less than 12 */
DECL|macro|HIGH_MARK
mdefine_line|#define HIGH_MARK&t;30&t;/* stop adding buffers after reaching 30 */
DECL|macro|OFF_CNG_THRES
mdefine_line|#define OFF_CNG_THRES&t;5&t;/* threshold for offset changes */
DECL|macro|RX_SIZE
mdefine_line|#define RX_SIZE&t;&t;2&t;/* RX lookup entry size (in bytes) */
DECL|macro|NR_POOLS
mdefine_line|#define NR_POOLS&t;32&t;/* number of free buffer pointers */
DECL|macro|POOL_SIZE
mdefine_line|#define POOL_SIZE&t;8&t;/* buffer entry size (in bytes) */
DECL|macro|NR_SHAPERS
mdefine_line|#define NR_SHAPERS&t;16&t;/* number of shapers */
DECL|macro|SHAPER_SIZE
mdefine_line|#define SHAPER_SIZE&t;4&t;/* shaper entry size (in bytes) */
DECL|macro|VC_SIZE
mdefine_line|#define VC_SIZE&t;&t;32&t;/* VC dsc (TX or RX) size (in bytes) */
DECL|macro|RING_ENTRIES
mdefine_line|#define RING_ENTRIES&t;32&t;/* ring entries (without back pointer) */
DECL|macro|RING_WORDS
mdefine_line|#define RING_WORDS&t;4&t;/* ring element size */
DECL|macro|RING_SIZE
mdefine_line|#define RING_SIZE&t;(sizeof(unsigned long)*(RING_ENTRIES+1)*RING_WORDS)
DECL|macro|NR_MBX
mdefine_line|#define NR_MBX&t;&t;4&t;/* four mailboxes */
DECL|macro|MBX_RX_0
mdefine_line|#define MBX_RX_0&t;0&t;/* mailbox indices */
DECL|macro|MBX_RX_1
mdefine_line|#define MBX_RX_1&t;1
DECL|macro|MBX_TX_0
mdefine_line|#define MBX_TX_0&t;2
DECL|macro|MBX_TX_1
mdefine_line|#define MBX_TX_1&t;3
multiline_comment|/*&n; * mkdep doesn&squot;t spot this dependency, but that&squot;s okay, because zatm.c uses&n; * CONFIG_ATM_ZATM_EXACT_TS too.&n; */
macro_line|#ifdef CONFIG_ATM_ZATM_EXACT_TS
DECL|macro|POLL_INTERVAL
mdefine_line|#define POLL_INTERVAL&t;60&t;/* TSR poll interval in seconds; must be &lt;=&n;&t;&t;&t;&t;   (2^31-1)/clock */
DECL|macro|TIMER_SHIFT
mdefine_line|#define TIMER_SHIFT&t;20&t;/* scale factor for fixed-point arithmetic;&n;&t;&t;&t;&t;   1 &lt;&lt; TIMER_SHIFT must be&n;&t;&t;&t;&t;     (1)  &lt;= (2^64-1)/(POLL_INTERVAL*clock),&n;&t;&t;&t;&t;     (2)  &gt;&gt; clock/10^6, and&n;&t;&t;&t;&t;     (3)  &lt;= (2^32-1)/1000  */
DECL|macro|ADJ_IGN_THRES
mdefine_line|#define ADJ_IGN_THRES&t;1000000&t;/* don&squot;t adjust if we&squot;re off by more than that&n;&t;&t;&t;&t;   many usecs - this filters clock corrections,&n;&t;&t;&t;&t;   time zone changes, etc. */
DECL|macro|ADJ_REP_THRES
mdefine_line|#define ADJ_REP_THRES&t;20000&t;/* report only differences of more than that&n;&t;&t;&t;&t;   many usecs (don&squot;t mention single lost timer&n;&t;&t;&t;&t;   ticks; 10 msec is only 0.03% anyway) */
DECL|macro|ADJ_MSG_THRES
mdefine_line|#define ADJ_MSG_THRES&t;5&t;/* issue complaints only if getting that many&n;&t;&t;&t;&t;   significant timer differences in a row */
macro_line|#endif
DECL|struct|zatm_vcc
r_struct
id|zatm_vcc
(brace
multiline_comment|/*-------------------------------- RX part */
DECL|member|rx_chan
r_int
id|rx_chan
suffix:semicolon
multiline_comment|/* RX channel, 0 if none */
DECL|member|pool
r_int
id|pool
suffix:semicolon
multiline_comment|/* free buffer pool */
multiline_comment|/*-------------------------------- TX part */
DECL|member|tx_chan
r_int
id|tx_chan
suffix:semicolon
multiline_comment|/* TX channel, 0 if none */
DECL|member|shaper
r_int
id|shaper
suffix:semicolon
multiline_comment|/* shaper, &lt;0 if none */
DECL|member|tx_queue
r_struct
id|sk_buff_head
id|tx_queue
suffix:semicolon
multiline_comment|/* list of buffers in transit */
DECL|member|tx_wait
id|wait_queue_head_t
id|tx_wait
suffix:semicolon
multiline_comment|/* for close */
DECL|member|ring
id|u32
op_star
id|ring
suffix:semicolon
multiline_comment|/* transmit ring */
DECL|member|ring_curr
r_int
id|ring_curr
suffix:semicolon
multiline_comment|/* current write position */
DECL|member|txing
r_int
id|txing
suffix:semicolon
multiline_comment|/* number of transmits in progress */
DECL|member|backlog
r_struct
id|sk_buff_head
id|backlog
suffix:semicolon
multiline_comment|/* list of buffers waiting for ring */
)brace
suffix:semicolon
DECL|struct|zatm_dev
r_struct
id|zatm_dev
(brace
multiline_comment|/*-------------------------------- TX part */
DECL|member|tx_bw
r_int
id|tx_bw
suffix:semicolon
multiline_comment|/* remaining bandwidth */
DECL|member|free_shapers
id|u32
id|free_shapers
suffix:semicolon
multiline_comment|/* bit set */
DECL|member|ubr
r_int
id|ubr
suffix:semicolon
multiline_comment|/* UBR shaper; -1 if none */
DECL|member|ubr_ref_cnt
r_int
id|ubr_ref_cnt
suffix:semicolon
multiline_comment|/* number of VCs using UBR shaper */
multiline_comment|/*-------------------------------- RX part */
DECL|member|pool_ref
r_int
id|pool_ref
(braket
id|NR_POOLS
)braket
suffix:semicolon
multiline_comment|/* free buffer pool usage counters */
DECL|member|last_free
r_volatile
r_struct
id|sk_buff
op_star
id|last_free
(braket
id|NR_POOLS
)braket
suffix:semicolon
multiline_comment|/* last entry in respective pool */
DECL|member|pool
r_struct
id|sk_buff_head
id|pool
(braket
id|NR_POOLS
)braket
suffix:semicolon
multiline_comment|/* free buffer pools */
DECL|member|pool_info
r_struct
id|zatm_pool_info
id|pool_info
(braket
id|NR_POOLS
)braket
suffix:semicolon
multiline_comment|/* pool information */
multiline_comment|/*-------------------------------- maps */
DECL|member|tx_map
r_struct
id|atm_vcc
op_star
op_star
id|tx_map
suffix:semicolon
multiline_comment|/* TX VCCs */
DECL|member|rx_map
r_struct
id|atm_vcc
op_star
op_star
id|rx_map
suffix:semicolon
multiline_comment|/* RX VCCs */
DECL|member|chans
r_int
id|chans
suffix:semicolon
multiline_comment|/* map size, must be 2^n */
multiline_comment|/*-------------------------------- mailboxes */
DECL|member|mbx_start
r_int
r_int
id|mbx_start
(braket
id|NR_MBX
)braket
suffix:semicolon
multiline_comment|/* start addresses */
DECL|member|mbx_end
id|u16
id|mbx_end
(braket
id|NR_MBX
)braket
suffix:semicolon
multiline_comment|/* end offset (in bytes) */
multiline_comment|/*-------------------------------- other pointers */
DECL|member|pool_base
id|u32
id|pool_base
suffix:semicolon
multiline_comment|/* Free buffer pool dsc (word addr) */
multiline_comment|/*-------------------------------- ZATM links */
DECL|member|more
r_struct
id|atm_dev
op_star
id|more
suffix:semicolon
multiline_comment|/* other ZATM devices */
macro_line|#ifdef CONFIG_ATM_ZATM_EXACT_TS
multiline_comment|/*-------------------------------- timestamp calculation */
DECL|member|last_clk
id|u32
id|last_clk
suffix:semicolon
multiline_comment|/* results of last poll: clock, */
DECL|member|last_time
r_struct
id|timeval
id|last_time
suffix:semicolon
multiline_comment|/*   virtual time and */
DECL|member|last_real_time
r_struct
id|timeval
id|last_real_time
suffix:semicolon
multiline_comment|/*   real time */
DECL|member|factor
id|u32
id|factor
suffix:semicolon
multiline_comment|/* multiplication factor */
DECL|member|timer_diffs
r_int
id|timer_diffs
suffix:semicolon
multiline_comment|/* number of significant deviations */
DECL|member|timer_history
r_struct
id|zatm_t_hist
id|timer_history
(braket
id|ZATM_TIMER_HISTORY_SIZE
)braket
suffix:semicolon
multiline_comment|/* record of timer synchronizations */
DECL|member|th_curr
r_int
id|th_curr
suffix:semicolon
multiline_comment|/* current position */
macro_line|#endif
multiline_comment|/*-------------------------------- general information */
DECL|member|mem
r_int
id|mem
suffix:semicolon
multiline_comment|/* RAM on board (in bytes) */
DECL|member|khz
r_int
id|khz
suffix:semicolon
multiline_comment|/* timer clock */
DECL|member|copper
r_int
id|copper
suffix:semicolon
multiline_comment|/* PHY type */
DECL|member|irq
r_int
r_char
id|irq
suffix:semicolon
multiline_comment|/* IRQ */
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
multiline_comment|/* IO base address */
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
multiline_comment|/* PCI stuff */
)brace
suffix:semicolon
DECL|macro|ZATM_DEV
mdefine_line|#define ZATM_DEV(d) ((struct zatm_dev *) (d)-&gt;dev_data)
DECL|macro|ZATM_VCC
mdefine_line|#define ZATM_VCC(d) ((struct zatm_vcc *) (d)-&gt;dev_data)
DECL|struct|zatm_skb_prv
r_struct
id|zatm_skb_prv
(brace
DECL|member|_
r_struct
id|atm_skb_data
id|_
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|dsc
id|u32
op_star
id|dsc
suffix:semicolon
multiline_comment|/* pointer to skb&squot;s descriptor */
)brace
suffix:semicolon
DECL|macro|ZATM_PRV_DSC
mdefine_line|#define ZATM_PRV_DSC(skb) (((struct zatm_skb_prv *) (skb)-&gt;cb)-&gt;dsc)
macro_line|#endif
eof
