multiline_comment|/* drivers/atm/eni.h - Efficient Networks ENI155P device driver declarations */
multiline_comment|/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef DRIVER_ATM_ENI_H
DECL|macro|DRIVER_ATM_ENI_H
mdefine_line|#define DRIVER_ATM_ENI_H
macro_line|#include &lt;linux/atm.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/sonet.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &quot;midway.h&quot;
DECL|macro|KERNEL_OFFSET
mdefine_line|#define KERNEL_OFFSET&t;0xC0000000&t;/* kernel 0x0 is at phys 0xC0000000 */
DECL|macro|DEV_LABEL
mdefine_line|#define DEV_LABEL&t;&quot;eni&quot;
DECL|macro|UBR_BUFFER
mdefine_line|#define UBR_BUFFER&t;(128*1024)&t;/* UBR buffer size */
DECL|macro|RX_DMA_BUF
mdefine_line|#define RX_DMA_BUF&t;  8&t;&t;/* burst and skip a few things */
DECL|macro|TX_DMA_BUF
mdefine_line|#define TX_DMA_BUF&t;100&t;&t;/* should be enough for 64 kB */
DECL|macro|DEFAULT_RX_MULT
mdefine_line|#define DEFAULT_RX_MULT&t;300&t;&t;/* max_sdu*3 */
DECL|macro|DEFAULT_TX_MULT
mdefine_line|#define DEFAULT_TX_MULT&t;300&t;&t;/* max_sdu*3 */
DECL|macro|ENI_ZEROES_SIZE
mdefine_line|#define ENI_ZEROES_SIZE&t;  4&t;&t;/* need that many DMA-able zero bytes */
DECL|struct|eni_free
r_struct
id|eni_free
(brace
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
multiline_comment|/* counting in bytes */
DECL|member|order
r_int
id|order
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|eni_tx
r_struct
id|eni_tx
(brace
DECL|member|send
r_int
r_int
id|send
suffix:semicolon
multiline_comment|/* base, 0 if unused */
DECL|member|prescaler
r_int
id|prescaler
suffix:semicolon
multiline_comment|/* shaping prescaler */
DECL|member|resolution
r_int
id|resolution
suffix:semicolon
multiline_comment|/* shaping divider */
DECL|member|tx_pos
r_int
r_int
id|tx_pos
suffix:semicolon
multiline_comment|/* current TX write position */
DECL|member|words
r_int
r_int
id|words
suffix:semicolon
multiline_comment|/* size of TX queue */
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* TX channel number */
DECL|member|reserved
r_int
id|reserved
suffix:semicolon
multiline_comment|/* reserved peak cell rate */
DECL|member|shaping
r_int
id|shaping
suffix:semicolon
multiline_comment|/* shaped peak cell rate */
DECL|member|backlog
r_struct
id|sk_buff_head
id|backlog
suffix:semicolon
multiline_comment|/* queue of waiting TX buffers */
)brace
suffix:semicolon
DECL|struct|eni_vcc
r_struct
id|eni_vcc
(brace
DECL|member|rx
r_int
(paren
op_star
id|rx
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
suffix:semicolon
multiline_comment|/* RX function, NULL if none */
DECL|member|recv
r_int
r_int
id|recv
suffix:semicolon
multiline_comment|/* receive buffer */
DECL|member|words
r_int
r_int
id|words
suffix:semicolon
multiline_comment|/* its size in words */
DECL|member|descr
r_int
r_int
id|descr
suffix:semicolon
multiline_comment|/* next descriptor (RX) */
DECL|member|rx_pos
r_int
r_int
id|rx_pos
suffix:semicolon
multiline_comment|/* current RX descriptor pos */
DECL|member|tx
r_struct
id|eni_tx
op_star
id|tx
suffix:semicolon
multiline_comment|/* TXer, NULL if none */
DECL|member|rxing
r_int
id|rxing
suffix:semicolon
multiline_comment|/* number of pending PDUs */
DECL|member|servicing
r_int
id|servicing
suffix:semicolon
multiline_comment|/* number of waiting VCs (0 or 1) */
DECL|member|txing
r_int
id|txing
suffix:semicolon
multiline_comment|/* number of pending TX bytes */
DECL|member|timestamp
r_struct
id|timeval
id|timestamp
suffix:semicolon
multiline_comment|/* for RX timing */
DECL|member|next
r_struct
id|atm_vcc
op_star
id|next
suffix:semicolon
multiline_comment|/* next pending RX */
DECL|member|last
r_struct
id|sk_buff
op_star
id|last
suffix:semicolon
multiline_comment|/* last PDU being DMAed (used to carry&n;&t;&t;&t;&t;&t;   discard information) */
)brace
suffix:semicolon
DECL|struct|eni_dev
r_struct
id|eni_dev
(brace
multiline_comment|/*-------------------------------- spinlock */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* sync with interrupt */
DECL|member|task
r_struct
id|tasklet_struct
id|task
suffix:semicolon
multiline_comment|/* tasklet for interrupt work */
DECL|member|events
id|u32
id|events
suffix:semicolon
multiline_comment|/* pending events */
multiline_comment|/*-------------------------------- base pointers into Midway address&n;&t;&t;&t;&t;&t;   space */
DECL|member|phy
r_int
r_int
id|phy
suffix:semicolon
multiline_comment|/* PHY interface chip registers */
DECL|member|reg
r_int
r_int
id|reg
suffix:semicolon
multiline_comment|/* register base */
DECL|member|ram
r_int
r_int
id|ram
suffix:semicolon
multiline_comment|/* RAM base */
DECL|member|vci
r_int
r_int
id|vci
suffix:semicolon
multiline_comment|/* VCI table */
DECL|member|rx_dma
r_int
r_int
id|rx_dma
suffix:semicolon
multiline_comment|/* RX DMA queue */
DECL|member|tx_dma
r_int
r_int
id|tx_dma
suffix:semicolon
multiline_comment|/* TX DMA queue */
DECL|member|service
r_int
r_int
id|service
suffix:semicolon
multiline_comment|/* service list */
multiline_comment|/*-------------------------------- TX part */
DECL|member|tx
r_struct
id|eni_tx
id|tx
(braket
id|NR_CHAN
)braket
suffix:semicolon
multiline_comment|/* TX channels */
DECL|member|ubr
r_struct
id|eni_tx
op_star
id|ubr
suffix:semicolon
multiline_comment|/* UBR channel */
DECL|member|tx_queue
r_struct
id|sk_buff_head
id|tx_queue
suffix:semicolon
multiline_comment|/* PDUs currently being TX DMAed*/
DECL|member|tx_wait
id|wait_queue_head_t
id|tx_wait
suffix:semicolon
multiline_comment|/* for close */
DECL|member|tx_bw
r_int
id|tx_bw
suffix:semicolon
multiline_comment|/* remaining bandwidth */
DECL|member|dma
id|u32
id|dma
(braket
id|TX_DMA_BUF
op_star
l_int|2
)braket
suffix:semicolon
multiline_comment|/* DMA request scratch area */
DECL|member|tx_mult
r_int
id|tx_mult
suffix:semicolon
multiline_comment|/* buffer size multiplier (percent) */
multiline_comment|/*-------------------------------- RX part */
DECL|member|serv_read
id|u32
id|serv_read
suffix:semicolon
multiline_comment|/* host service read index */
DECL|member|fast
DECL|member|last_fast
r_struct
id|atm_vcc
op_star
id|fast
comma
op_star
id|last_fast
suffix:semicolon
multiline_comment|/* queues of VCCs with pending PDUs */
DECL|member|slow
DECL|member|last_slow
r_struct
id|atm_vcc
op_star
id|slow
comma
op_star
id|last_slow
suffix:semicolon
DECL|member|rx_map
r_struct
id|atm_vcc
op_star
op_star
id|rx_map
suffix:semicolon
multiline_comment|/* for fast lookups */
DECL|member|rx_queue
r_struct
id|sk_buff_head
id|rx_queue
suffix:semicolon
multiline_comment|/* PDUs currently being RX-DMAed */
DECL|member|rx_wait
id|wait_queue_head_t
id|rx_wait
suffix:semicolon
multiline_comment|/* for close */
DECL|member|rx_mult
r_int
id|rx_mult
suffix:semicolon
multiline_comment|/* buffer size multiplier (percent) */
multiline_comment|/*-------------------------------- statistics */
DECL|member|lost
r_int
r_int
id|lost
suffix:semicolon
multiline_comment|/* number of lost cells (RX) */
multiline_comment|/*-------------------------------- memory management */
DECL|member|base_diff
r_int
r_int
id|base_diff
suffix:semicolon
multiline_comment|/* virtual-real base address */
DECL|member|free_len
r_int
id|free_len
suffix:semicolon
multiline_comment|/* free list length */
DECL|member|free_list
r_struct
id|eni_free
op_star
id|free_list
suffix:semicolon
multiline_comment|/* free list */
DECL|member|free_list_size
r_int
id|free_list_size
suffix:semicolon
multiline_comment|/* maximum size of free list */
multiline_comment|/*-------------------------------- ENI links */
DECL|member|more
r_struct
id|atm_dev
op_star
id|more
suffix:semicolon
multiline_comment|/* other ENI devices */
multiline_comment|/*-------------------------------- general information */
DECL|member|mem
r_int
id|mem
suffix:semicolon
multiline_comment|/* RAM on board (in bytes) */
DECL|member|asic
r_int
id|asic
suffix:semicolon
multiline_comment|/* PCI interface type, 0 for FPGA */
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* IRQ */
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
multiline_comment|/* PCI stuff */
)brace
suffix:semicolon
DECL|macro|ENI_DEV
mdefine_line|#define ENI_DEV(d) ((struct eni_dev *) (d)-&gt;dev_data)
DECL|macro|ENI_VCC
mdefine_line|#define ENI_VCC(d) ((struct eni_vcc *) (d)-&gt;dev_data)
DECL|struct|eni_skb_prv
r_struct
id|eni_skb_prv
(brace
DECL|member|_
r_struct
id|atm_skb_data
id|_
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|pos
r_int
r_int
id|pos
suffix:semicolon
multiline_comment|/* position of next descriptor */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* PDU size in reassembly buffer */
DECL|member|paddr
id|dma_addr_t
id|paddr
suffix:semicolon
multiline_comment|/* DMA handle */
)brace
suffix:semicolon
DECL|macro|ENI_PRV_SIZE
mdefine_line|#define ENI_PRV_SIZE(skb) (((struct eni_skb_prv *) (skb)-&gt;cb)-&gt;size)
DECL|macro|ENI_PRV_POS
mdefine_line|#define ENI_PRV_POS(skb) (((struct eni_skb_prv *) (skb)-&gt;cb)-&gt;pos)
DECL|macro|ENI_PRV_PADDR
mdefine_line|#define ENI_PRV_PADDR(skb) (((struct eni_skb_prv *) (skb)-&gt;cb)-&gt;paddr)
macro_line|#endif
eof
