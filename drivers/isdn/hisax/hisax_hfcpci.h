macro_line|#include &quot;hisax_if.h&quot;
macro_line|#include &quot;hisax_isac.h&quot;
macro_line|#include &lt;linux/pci.h&gt;
DECL|struct|hfcpci_bcs
r_struct
id|hfcpci_bcs
(brace
DECL|member|b_if
r_struct
id|hisax_b_if
id|b_if
suffix:semicolon
DECL|member|adapter
r_struct
id|hfcpci_adapter
op_star
id|adapter
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|channel
r_int
id|channel
suffix:semicolon
DECL|member|last_fcnt
r_int
id|last_fcnt
suffix:semicolon
DECL|member|tx_skb
r_struct
id|sk_buff
op_star
id|tx_skb
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hfcpci_adapter
r_struct
id|hfcpci_adapter
(brace
DECL|member|d_if
r_struct
id|hisax_d_if
id|d_if
suffix:semicolon
DECL|member|hw_lock
id|spinlock_t
id|hw_lock
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|mmio
r_void
op_star
id|mmio
suffix:semicolon
DECL|member|fifo
id|u8
op_star
id|fifo
suffix:semicolon
DECL|member|fifo_dma
id|dma_addr_t
id|fifo_dma
suffix:semicolon
DECL|member|l1m
r_struct
id|FsmInst
id|l1m
suffix:semicolon
DECL|member|timer
r_struct
id|FsmTimer
id|timer
suffix:semicolon
DECL|member|tx_skb
r_struct
id|sk_buff
op_star
id|tx_skb
suffix:semicolon
DECL|member|last_fcnt
r_int
id|last_fcnt
suffix:semicolon
DECL|member|int_m1
DECL|member|int_m2
id|u8
id|int_m1
comma
id|int_m2
suffix:semicolon
DECL|member|fifo_en
id|u8
id|fifo_en
suffix:semicolon
DECL|member|trm
id|u8
id|trm
suffix:semicolon
DECL|member|sctrl
DECL|member|sctrl_r
DECL|member|sctrl_e
id|u8
id|sctrl
comma
id|sctrl_r
comma
id|sctrl_e
suffix:semicolon
DECL|member|nt_mode
id|u8
id|nt_mode
suffix:semicolon
DECL|member|ctmt
id|u8
id|ctmt
suffix:semicolon
DECL|member|mst_m
id|u8
id|mst_m
suffix:semicolon
DECL|member|conn
id|u8
id|conn
suffix:semicolon
DECL|member|bswapped
id|u8
id|bswapped
suffix:semicolon
DECL|member|bcs
r_struct
id|hfcpci_bcs
id|bcs
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
eof
