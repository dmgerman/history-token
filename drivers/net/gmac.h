multiline_comment|/*&n; * Definitions for the GMAC ethernet chip, used in the&n; * Apple G4 powermac.&n; */
multiline_comment|/* &n; * GMAC register definitions&n; * &n; * Note: We encode the register size the same way Apple does. I didn&squot;t copy&n; *       Apple&squot;s source as-is to avoid licence issues however. That&squot;s really&n; *       painful to re-define all those registers ...&n; *       The constants themselves were partially found in OF code, in Sun&n; *       GEM driver and in Apple&squot;s Darwin GMAC driver&n; */
DECL|macro|REG_SZ_8
mdefine_line|#define REG_SZ_8&t;&t;&t;0x00000000
DECL|macro|REG_SZ_16
mdefine_line|#define REG_SZ_16&t;&t;&t;0x40000000
DECL|macro|REG_SZ_32
mdefine_line|#define REG_SZ_32&t;&t;&t;0x80000000
DECL|macro|REG_MASK
mdefine_line|#define REG_MASK&t;&t;&t;0x0FFFFFFF
multiline_comment|/*&n;&t; * Global registers&n;&t; */
multiline_comment|/* -- 0x0004&t;RW&t;Global configuration&n; * d: 0x00000042&n; */
DECL|macro|GM_GCONF
mdefine_line|#define GM_GCONF&t;&t;&t;(0x0004 | REG_SZ_16)
DECL|macro|GM_GCONF_BURST_SZ
mdefine_line|#define GM_GCONF_BURST_SZ&t;&t;0x0001&t;&t;/* 1: 64 bytes/burst, 0: infinite */
DECL|macro|GM_GCONF_TXDMA_LIMIT_MASK
mdefine_line|#define GM_GCONF_TXDMA_LIMIT_MASK&t;0x003e&t;&t;/* 5-1: No of 64 bytes transfers */
DECL|macro|GM_GCONF_TXDMA_LIMIT_SHIFT
mdefine_line|#define GM_GCONF_TXDMA_LIMIT_SHIFT&t;1
DECL|macro|GM_GCONF_RXDMA_LIMIT_MASK
mdefine_line|#define GM_GCONF_RXDMA_LIMIT_MASK&t;0x07c0&t;&t;/* 10-6: No of 64 bytes transfers */
DECL|macro|GM_GCONF_RXDMA_LIMIT_SHIFT
mdefine_line|#define GM_GCONF_RXDMA_LIMIT_SHIFT&t;6
multiline_comment|/* -- 0x000C&t;R-C&t;Global Interrupt status. &n; * d: 0x00000000&t;bits 0-6 cleared on read (C)&n; */
DECL|macro|GM_IRQ_STATUS
mdefine_line|#define GM_IRQ_STATUS&t;&t;&t;(0x000c | REG_SZ_32)
DECL|macro|GM_IRQ_TX_INT_ME
mdefine_line|#define GM_IRQ_TX_INT_ME&t;&t;0x00000001&t;/* C Frame with INT_ME bit set in fifo */
DECL|macro|GM_IRQ_TX_ALL
mdefine_line|#define GM_IRQ_TX_ALL&t;&t;&t;0x00000002&t;/* C TX descriptor ring empty */
DECL|macro|GM_IRQ_TX_DONE
mdefine_line|#define GM_IRQ_TX_DONE&t;&t;&t;0x00000004&t;/* C moved from host to TX fifo */
DECL|macro|GM_IRQ_RX_DONE
mdefine_line|#define GM_IRQ_RX_DONE&t;&t;&t;0x00000010&t;/* C moved from RX fifo to host */
DECL|macro|GM_IRQ_RX_NO_BUF
mdefine_line|#define GM_IRQ_RX_NO_BUF&t;&t;0x00000020&t;/* C No RX buffer available */
DECL|macro|GM_IRQ_RX_TAG_ERR
mdefine_line|#define GM_IRQ_RX_TAG_ERR&t;&t;0x00000040&t;/* C RX tag error */
DECL|macro|GM_IRQ_PCS
mdefine_line|#define GM_IRQ_PCS&t;&t;&t;0x00002000&t;/* PCS interrupt ? */
DECL|macro|GM_IRQ_MAC_TX
mdefine_line|#define GM_IRQ_MAC_TX&t;&t;&t;0x00004000&t;/* MAC tx register set */
DECL|macro|GM_IRQ_MAC_RX
mdefine_line|#define GM_IRQ_MAC_RX&t;&t;&t;0x00008000&t;/* MAC rx register set  */
DECL|macro|GM_IRQ_MAC_CTRL
mdefine_line|#define GM_IRQ_MAC_CTRL&t;&t;&t;0x00010000&t;/* MAC control register set  */
DECL|macro|GM_IRQ_MIF
mdefine_line|#define GM_IRQ_MIF&t;&t;&t;0x00020000&t;/* MIF status register set */
DECL|macro|GM_IRQ_BUS_ERROR
mdefine_line|#define GM_IRQ_BUS_ERROR&t;&t;0x00040000&t;/* Bus error status register set */
DECL|macro|GM_IRQ_TX_COMP
mdefine_line|#define GM_IRQ_TX_COMP&t;&t;&t;0xfff80000&t;/* TX completion mask */
multiline_comment|/* -- 0x0010&t;RW&t;Interrupt mask. &n; * d: 0xFFFFFFFF&n; */
DECL|macro|GM_IRQ_MASK
mdefine_line|#define GM_IRQ_MASK&t;&t;&t;(0x0010 | REG_SZ_32)
multiline_comment|/* -- 0x0014&t;WO&t;Interrupt ack.&n; * &t;&t;&t;Ack. &quot;high&quot; interrupts&n; */
DECL|macro|GM_IRQ_ACK
mdefine_line|#define GM_IRQ_ACK&t;&t;&t;(0x0014 | REG_SZ_32)
multiline_comment|/* -- 0x001C&t;WO&t;Alias of status register (no auto-clear of &quot;low&quot; interrupts)&n; */
DECL|macro|GM_IRQ_ALT_STAT
mdefine_line|#define GM_IRQ_ALT_STAT&t;&t;&t;(0x001C | REG_SZ_32)
multiline_comment|/* -- 0x1000&t;R-C&t;PCI Error status register&n; */
DECL|macro|GM_PCI_ERR_STAT
mdefine_line|#define GM_PCI_ERR_STAT&t;&t;&t;(0x1000 | REG_SZ_8)
DECL|macro|GM_PCI_ERR_BAD_ACK
mdefine_line|#define GM_PCI_ERR_BAD_ACK&t;&t;0x01&t;&t;/* Bad Ack64 */
DECL|macro|GM_PCI_ERR_TIMEOUT
mdefine_line|#define GM_PCI_ERR_TIMEOUT&t;&t;0x02&t;&t;/* Transaction timeout */
DECL|macro|GM_PCI_ERR_OTHER
mdefine_line|#define GM_PCI_ERR_OTHER&t;&t;0x04&t;&t;/* Any other PCI error */
multiline_comment|/* -- 0x1004&t;RW&t;PCI Error mask register&n; * d: 0xFFFFFFFF&n; */
DECL|macro|GM_PCI_ERR_MASK
mdefine_line|#define GM_PCI_ERR_MASK&t;&t;&t;(0x1004 | REG_SZ_8)
multiline_comment|/* -- 0x1008&t;RW&t;BIF Configuration&n; * d: 0x00000000&n; */
DECL|macro|GM_BIF_CFG
mdefine_line|#define GM_BIF_CFG&t;&t;&t;(0x1008 | REG_SZ_8)
DECL|macro|GM_BIF_CFG_SLOWCLK
mdefine_line|#define&t;GM_BIF_CFG_SLOWCLK&t;&t;0x01&t;&t;/* for parity error timing */
DECL|macro|GM_BIF_CFG_HOST_64
mdefine_line|#define&t;GM_BIF_CFG_HOST_64&t;&t;0x02&t;&t;/* 64-bit host */
DECL|macro|GM_BIF_CFG_B64D_DIS
mdefine_line|#define&t;GM_BIF_CFG_B64D_DIS&t;&t;0x04&t;&t;/* no 64-bit wide data cycle */
DECL|macro|GM_BIF_CFG_M66EN
mdefine_line|#define&t;GM_BIF_CFG_M66EN&t;&t;0x08&t;&t;/* Read-only: sense if configured for 66MHz */
multiline_comment|/* -- 0x100C&t;RW&t;BIF Diagnostic ???&n; */
DECL|macro|GM_BIF_DIAG
mdefine_line|#define GM_BIF_DIAG&t;&t;&t;(0x100C | REG_SZ_32)
DECL|macro|GM_BIF_DIAG_BURST_STATE
mdefine_line|#define GM_BIF_DIAG_BURST_STATE&t;&t;0x007F0000
DECL|macro|GM_BIF_DIAG_STATE_MACH
mdefine_line|#define GM_BIF_DIAG_STATE_MACH&t;&t;0xFF000000
multiline_comment|/* -- 0x1010&t;RW&t;Software reset&n; *&t;&t;&t;Lower two bits reset TX and RX, both reset whole gmac. They come back&n; *&t;&t;&t;to 0 when reset is complete.&n; *&t;&t;&t;bit 2 force RSTOUT# pin when set (PHY reset)&n; */
DECL|macro|GM_RESET
mdefine_line|#define GM_RESET&t;&t;&t;(0x1010 | REG_SZ_8)
DECL|macro|GM_RESET_TX
mdefine_line|#define&t;GM_RESET_TX&t;&t;&t;0x01
DECL|macro|GM_RESET_RX
mdefine_line|#define&t;GM_RESET_RX&t;&t;&t;0x02
DECL|macro|GM_RESET_RSTOUT
mdefine_line|#define&t;GM_RESET_RSTOUT&t;&t;&t;0x04&t;&t;/* PHY reset */
multiline_comment|/*&n;&t; * Tx DMA Registers&n;&t; */
multiline_comment|/* -- 0x2000&t;RW&t;Tx Kick&n; * d: 0x00000000&t;Written by the host with the last tx descriptor number +1 to send&n; */
DECL|macro|GM_TX_KICK
mdefine_line|#define GM_TX_KICK&t;&t;&t;(0x2000 | REG_SZ_16)
multiline_comment|/* -- 0x2004&t;RW&t;Tx configuration&n; * d: 0x118010&t;&t;Controls operation of Tx DMA channel&n; */
DECL|macro|GM_TX_CONF
mdefine_line|#define GM_TX_CONF&t;&t;&t;(0x2004 | REG_SZ_32)
DECL|macro|GM_TX_CONF_DMA_EN
mdefine_line|#define&t;GM_TX_CONF_DMA_EN&t;&t;0x00000001&t;/* Tx DMA enable */
DECL|macro|GM_TX_CONF_RING_SZ_MASK
mdefine_line|#define&t;GM_TX_CONF_RING_SZ_MASK&t;&t;0x0000001e&t;/* Tx desc ring size */
DECL|macro|GM_TX_CONF_RING_SZ_SHIFT
mdefine_line|#define GM_TX_CONF_RING_SZ_SHIFT&t;1&t;&t;/* Tx desc ring size shift */
DECL|macro|GM_TX_CONF_FIFO_PIO
mdefine_line|#define GM_TX_CONF_FIFO_PIO&t;&t;0x00000020&t;/* Tx fifo PIO select ??? */
DECL|macro|GM_TX_CONF_FIFO_THR_MASK
mdefine_line|#define&t;GM_TX_CONF_FIFO_THR_MASK&t;0x001ffc00&t;/* Tx fifo threshold */
DECL|macro|GM_TX_CONF_FIFO_THR_SHIFT
mdefine_line|#define GM_TX_CONF_FIFO_THR_SHIFT&t;10&t;&t;/* Tx fifo threshold shift */
DECL|macro|GM_TX_CONF_FIFO_THR_DEFAULT
mdefine_line|#define GM_TX_CONF_FIFO_THR_DEFAULT&t;0x7ff&t;&t;/* Tx fifo threshold default */
DECL|macro|GM_TX_CONF_PACED_MODE
mdefine_line|#define&t;GM_TX_CONF_PACED_MODE&t;&t;0x00100000&t;/* 1: tx_all irq after last descriptor */
multiline_comment|/* 0: tx_all irq when tx fifo empty */
DECL|macro|GM_TX_RING_SZ_32
mdefine_line|#define&t;GM_TX_RING_SZ_32&t;&t;(0 &lt;&lt; 1)
DECL|macro|GM_TX_RING_SZ_64
mdefine_line|#define&t;GM_TX_RING_SZ_64&t;&t;(1 &lt;&lt; 1)
DECL|macro|GM_TX_RING_SZ_128
mdefine_line|#define&t;GM_TX_RING_SZ_128&t;&t;(2 &lt;&lt; 1)
DECL|macro|GM_TX_RING_SZ_256
mdefine_line|#define&t;GM_TX_RING_SZ_256&t;&t;(3 &lt;&lt; 1)
DECL|macro|GM_TX_RING_SZ_512
mdefine_line|#define&t;GM_TX_RING_SZ_512&t;&t;(4 &lt;&lt; 1)
DECL|macro|GM_TX_RING_SZ_1024
mdefine_line|#define&t;GM_TX_RING_SZ_1024&t;&t;(5 &lt;&lt; 1)
DECL|macro|GM_TX_RING_SZ_2048
mdefine_line|#define&t;GM_TX_RING_SZ_2048&t;&t;(6 &lt;&lt; 1)
DECL|macro|GM_TX_RING_SZ_4086
mdefine_line|#define&t;GM_TX_RING_SZ_4086&t;&t;(7 &lt;&lt; 1)
DECL|macro|GM_TX_RING_SZ_8192
mdefine_line|#define&t;GM_TX_RING_SZ_8192&t;&t;(8 &lt;&lt; 1)
multiline_comment|/* -- 0x2008&t;RW&t;Tx descriptor ring base low&n; * -- 0x200C&t;RW&t;Tx descriptor ring base high&n; *&n; * Base of tx ring, must be 2k aligned&n; */
DECL|macro|GM_TX_DESC_LO
mdefine_line|#define GM_TX_DESC_LO&t;&t;&t;(0x2008 | REG_SZ_32)
DECL|macro|GM_TX_DESC_HI
mdefine_line|#define GM_TX_DESC_HI&t;&t;&t;(0x200C | REG_SZ_32)
multiline_comment|/* -- 0x2100&t;RW&t;Tx Completion&n; * d: 0x00000000&t;Written by the gmac with the last tx descriptor number +1 sent&n; */
DECL|macro|GM_TX_COMP
mdefine_line|#define GM_TX_COMP&t;&t;&t;(0x2100 | REG_SZ_16)
multiline_comment|/*&n;&t; * Rx DMA registers&n;&t; */
multiline_comment|/* -- 0x4000&t;RW&t;Rx configuration&n; * d: 0x1000010&t;&t;Controls operation of Rx DMA channel&n; */
DECL|macro|GM_RX_CONF
mdefine_line|#define GM_RX_CONF&t;&t;&t;(0x4000 | REG_SZ_32)
DECL|macro|GM_RX_CONF_DMA_EN
mdefine_line|#define&t;GM_RX_CONF_DMA_EN&t;&t;0x00000001&t;/* Rx DMA enable */
DECL|macro|GM_RX_CONF_RING_SZ_MASK
mdefine_line|#define&t;GM_RX_CONF_RING_SZ_MASK&t;&t;0x0000001e&t;/* Rx desc ring size */
DECL|macro|GM_RX_CONF_RING_SZ_SHIFT
mdefine_line|#define GM_RX_CONF_RING_SZ_SHIFT&t;1
DECL|macro|GM_RX_CONF_BATCH_DIS
mdefine_line|#define&t;GM_RX_CONF_BATCH_DIS&t;&t;0x00000020&t;/* Rx batch disable */
DECL|macro|GM_RX_CONF_FBYTE_OFF_MASK
mdefine_line|#define&t;GM_RX_CONF_FBYTE_OFF_MASK&t;0x00001c00&t;/* First byte offset (10-12) */
DECL|macro|GM_RX_CONF_FBYTE_OFF_SHIFT
mdefine_line|#define GM_RX_CONF_FBYTE_OFF_SHIFT&t;10
DECL|macro|GM_RX_CONF_CHK_START_MASK
mdefine_line|#define&t;GM_RX_CONF_CHK_START_MASK&t;0x000FE000&t;/* Checksum start offset */
DECL|macro|GM_RX_CONF_CHK_START_SHIFT
mdefine_line|#define GM_RX_CONF_CHK_START_SHIFT&t;13
DECL|macro|GM_RX_CONF_DMA_THR_MASK
mdefine_line|#define&t;GM_RX_CONF_DMA_THR_MASK&t;&t;0x07000000&t;/* Rx DMA threshold */
DECL|macro|GM_RX_CONF_DMA_THR_SHIFT
mdefine_line|#define GM_RX_CONF_DMA_THR_SHIFT&t;24&t;&t;/* Rx DMA threshold shift */
DECL|macro|GM_RX_CONF_DMA_THR_DEFAULT
mdefine_line|#define GM_RX_CONF_DMA_THR_DEFAULT&t;1&t;&t;/* Rx DMA threshold default */
DECL|macro|GM_RX_RING_SZ_32
mdefine_line|#define&t;GM_RX_RING_SZ_32&t;&t;(0 &lt;&lt; 1)
DECL|macro|GM_RX_RING_SZ_64
mdefine_line|#define&t;GM_RX_RING_SZ_64&t;&t;(1 &lt;&lt; 1)
DECL|macro|GM_RX_RING_SZ_128
mdefine_line|#define&t;GM_RX_RING_SZ_128&t;&t;(2 &lt;&lt; 1)
DECL|macro|GM_RX_RING_SZ_256
mdefine_line|#define&t;GM_RX_RING_SZ_256&t;&t;(3 &lt;&lt; 1)
DECL|macro|GM_RX_RING_SZ_512
mdefine_line|#define&t;GM_RX_RING_SZ_512&t;&t;(4 &lt;&lt; 1)
DECL|macro|GM_RX_RING_SZ_1024
mdefine_line|#define&t;GM_RX_RING_SZ_1024&t;&t;(5 &lt;&lt; 1)
DECL|macro|GM_RX_RING_SZ_2048
mdefine_line|#define&t;GM_RX_RING_SZ_2048&t;&t;(6 &lt;&lt; 1)
DECL|macro|GM_RX_RING_SZ_4086
mdefine_line|#define&t;GM_RX_RING_SZ_4086&t;&t;(7 &lt;&lt; 1)
DECL|macro|GM_RX_RING_SZ_8192
mdefine_line|#define&t;GM_RX_RING_SZ_8192&t;&t;(8 &lt;&lt; 1)
multiline_comment|/* -- 0x4004&t;RW&t;Rx descriptor ring base low&n; * -- 0x4008&t;RW&t;Rx descriptor ring base high&n; *&n; * Base of rx ring&n; */
DECL|macro|GM_RX_DESC_LO
mdefine_line|#define GM_RX_DESC_LO&t;&t;&t;(0x4004 | REG_SZ_32)
DECL|macro|GM_RX_DESC_HI
mdefine_line|#define GM_RX_DESC_HI&t;&t;&t;(0x4008 | REG_SZ_32)
multiline_comment|/* -- 0x4020&t;RW&t;Rx pause threshold&n; * d: 0x000000f8&t;&n; *&n; * Two PAUSE thresholds are used to define when PAUSE flow control frames are&n; * emitted by GEM. The granularity of these thresholds is in 64 byte increments.&n; * XOFF PAUSE frames use the pause_time value pre-programmed in the&n; * Send PAUSE MAC Register.&n; * XON PAUSE frames use a pause_time of 0.&n; */
DECL|macro|GM_RX_PTH
mdefine_line|#define GM_RX_PTH&t;&t;&t;(0x4020 | REG_SZ_32)
multiline_comment|/*&n;&t;&t;&t; * 0-8: XOFF PAUSE emitted when RX FIFO&n;&t;&t;&t; * occupancy rises above this value (times 64 bytes)&n;&t;&t;&t; */
DECL|macro|GM_RX_PTH_OFF_MASK
mdefine_line|#define&t;GM_RX_PTH_OFF_MASK&t;&t;0x000001ff
DECL|macro|GM_RX_PTH_OFF_SHIFT
mdefine_line|#define GM_RX_PTH_OFF_SHIFT&t;&t;0
multiline_comment|/*&n;&t;&t;&t; * 12-20: XON PAUSE emitted when RX FIFO&n;&t;&t;&t; * occupancy falls below this value (times 64 bytes)&n;&t;&t;&t; */
DECL|macro|GM_RX_PTH_ON_MASK
mdefine_line|#define&t;GM_RX_PTH_ON_MASK&t;&t;0x001ff000
DECL|macro|GM_RX_PTH_ON_SHIFT
mdefine_line|#define&t;GM_RX_PTH_ON_SHIFT&t;&t;12
DECL|macro|GM_RX_PTH_UNITS
mdefine_line|#define GM_RX_PTH_UNITS&t;&t;&t;64
multiline_comment|/* -- 0x4100&t;RW&t;Rx Kick&n; * d: 0x00000000&t;The last valid RX descriptor is the one right before the value of the&n; *                      register. Initially set to 0 on reset. RX descriptors must be posted&n; *                      in multiples of 4. The first descriptor should be cache-line aligned&n; *                      for best performance.&n; */
DECL|macro|GM_RX_KICK
mdefine_line|#define GM_RX_KICK&t;&t;&t;(0x4100 | REG_SZ_16)
multiline_comment|/* -- 0x4104&t;RW&t;Rx Completion&n; * d: 0x00000000&t;All descriptors upto but excluding the register value are ready to be&n; *                      processed by the host.&n; */
DECL|macro|GM_RX_COMP
mdefine_line|#define GM_RX_COMP&t;&t;&t;(0x4104 | REG_SZ_16)
multiline_comment|/* -- 0x4108&t;RW&t;Rx Blanking&n; * d: 0x00000000&t;Written by the gmac with the last tx descriptor number +1 sent&n; *&n; * Defines the values used for receive interrupt blanking.&n; * For INTR_TIME field, every count is 2048 PCI clock time. For 66 Mhz, each&n; * count is about 15 ns.&n; */
DECL|macro|GM_RX_BLANK
mdefine_line|#define GM_RX_BLANK&t;&t;&t;(0x4108 | REG_SZ_32)
multiline_comment|/*&n;&t;&t;&t; * 0-8:no.of pkts to be recvd since the last RX_DONE&n;&t;&t;&t; * interrupt, before a new interrupt&n;&t;&t;&t; */
DECL|macro|GM_RX_BLANK_INTR_PACKETS_MASK
mdefine_line|#define&t;GM_RX_BLANK_INTR_PACKETS_MASK&t;0x000001ff
DECL|macro|GM_RX_BLANK_INTR_PACKETS_SHIFT
mdefine_line|#define&t;GM_RX_BLANK_INTR_PACKETS_SHIFT&t;0
multiline_comment|/*&n;&t;&t;&t; * 12-19 : no. of clocks to be counted since the last&n;&t;&t;&t; * RX_DONE interrupt, before a new interrupt&n;&t;&t;&t; */
DECL|macro|GM_RX_BLANK_INTR_TIME_MASK
mdefine_line|#define&t;GM_RX_BLANK_INTR_TIME_MASK&t;0x000ff000
DECL|macro|GM_RX_BLANK_INTR_TIME_SHIFT
mdefine_line|#define&t;GM_RX_BLANK_INTR_TIME_SHIFT&t;12
DECL|macro|GM_RX_BLANK_UNITS
mdefine_line|#define GM_RX_BLANK_UNITS&t;&t;2048
multiline_comment|/* -- 0x4120&t;RO&t;Rx fifo size&n; *&n; * This 11-bit RO register indicates the size, in 64-byte multiples, of the&n; * RX FIFO. Software should use it to properly configure the PAUSE thresholds.&n; * The value read is 0x140, indicating a 20kbyte RX FIFO.&n; * -------------------------------------------------------------------------&n; */
DECL|macro|GM_RX_FIFO_SIZE
mdefine_line|#define GM_RX_FIFO_SIZE&t;&t;&t;(0x4120 | REG_SZ_16)
DECL|macro|GM_RZ_FIFO_SIZE_UNITS
mdefine_line|#define GM_RZ_FIFO_SIZE_UNITS&t;&t;64
multiline_comment|/*&n;&t; * MAC regisers&n;&t; */
multiline_comment|/* -- 0x6000&t;&t;MAC Tx reset control&n; */
DECL|macro|GM_MAC_TX_RESET
mdefine_line|#define GM_MAC_TX_RESET&t;&t;&t;(0x6000 | REG_SZ_8)
DECL|macro|GM_MAC_TX_RESET_NOW
mdefine_line|#define GM_MAC_TX_RESET_NOW&t;&t;0x01
multiline_comment|/* -- 0x6004&t;&t;MAC Rx reset control&n; */
DECL|macro|GM_MAC_RX_RESET
mdefine_line|#define GM_MAC_RX_RESET&t;&t;&t;(0x6004 | REG_SZ_8)
DECL|macro|GM_MAC_RX_RESET_NOW
mdefine_line|#define GM_MAC_RX_RESET_NOW&t;&t;0x01
multiline_comment|/* -- 0x6008&t;&t;Send Pause command register&n; */
DECL|macro|GM_MAC_SND_PAUSE
mdefine_line|#define GM_MAC_SND_PAUSE&t;&t;(0x6008 | REG_SZ_32)
DECL|macro|GM_MAC_SND_PAUSE_TIME_MASK
mdefine_line|#define GM_MAC_SND_PAUSE_TIME_MASK&t;0x0000ffff
DECL|macro|GM_MAC_SND_PAUSE_TIME_SHIFT
mdefine_line|#define GM_MAC_SND_PAUSE_TIME_SHIFT&t;0
DECL|macro|GM_MAC_SND_PAUSE_NOW
mdefine_line|#define GM_MAC_SND_PAUSE_NOW&t;&t;0x00010000
DECL|macro|GM_MAC_SND_PAUSE_DEFAULT
mdefine_line|#define GM_MAC_SND_PAUSE_DEFAULT&t;0x00001bf0
multiline_comment|/* -- 0x6010&t;&t;MAC transmit status&n; */
DECL|macro|GM_MAC_TX_STATUS
mdefine_line|#define GM_MAC_TX_STATUS&t;&t;(0x6010 | REG_SZ_16)
DECL|macro|GM_MAC_TX_STAT_SENT
mdefine_line|#define GM_MAC_TX_STAT_SENT&t;&t;0x0001
DECL|macro|GM_MAC_TX_STAT_UNDERRUN
mdefine_line|#define GM_MAC_TX_STAT_UNDERRUN&t;&t;0x0002
DECL|macro|GM_MAC_TX_STAT_MAX_PKT_ERR
mdefine_line|#define GM_MAC_TX_STAT_MAX_PKT_ERR&t;0x0004
DECL|macro|GM_MAC_TX_STAT_NORM_COLL_OVF
mdefine_line|#define GM_MAC_TX_STAT_NORM_COLL_OVF&t;0x0008
DECL|macro|GM_MAC_TX_STAT_EXCS_COLL_OVF
mdefine_line|#define GM_MAC_TX_STAT_EXCS_COLL_OVF&t;0x0010
DECL|macro|GM_MAC_TX_STAT_LATE_COLL_OVF
mdefine_line|#define GM_MAC_TX_STAT_LATE_COLL_OVF&t;0x0020
DECL|macro|GM_MAC_TX_STAT_FIRS_COLL_OVF
mdefine_line|#define GM_MAC_TX_STAT_FIRS_COLL_OVF&t;0x0040
DECL|macro|GM_MAC_TX_STAT_DEFER_TIMER_OVF
mdefine_line|#define GM_MAC_TX_STAT_DEFER_TIMER_OVF&t;0x0080
DECL|macro|GM_MAC_TX_STAT_PEAK_ATTMP_OVF
mdefine_line|#define GM_MAC_TX_STAT_PEAK_ATTMP_OVF&t;0x0100
multiline_comment|/* -- 0x6014&t;&t;MAC receive status&n; */
DECL|macro|GM_MAC_RX_STATUS
mdefine_line|#define GM_MAC_RX_STATUS&t;&t;(0x6014 | REG_SZ_16)
DECL|macro|GM_MAC_RX_STAT_RECEIVED
mdefine_line|#define GM_MAC_RX_STAT_RECEIVED&t;&t;0x0001
DECL|macro|GM_MAC_RX_STAT_FIFO_OVF
mdefine_line|#define GM_MAC_RX_STAT_FIFO_OVF&t;&t;0x0002
DECL|macro|GM_MAC_RX_STAT_FRAME_CTR_OVF
mdefine_line|#define GM_MAC_RX_STAT_FRAME_CTR_OVF&t;0x0004
DECL|macro|GM_MAC_RX_STAT_ALIGN_ERR_OVF
mdefine_line|#define GM_MAC_RX_STAT_ALIGN_ERR_OVF&t;0x0008
DECL|macro|GM_MAC_RX_STAT_CRC_ERR_OVF
mdefine_line|#define GM_MAC_RX_STAT_CRC_ERR_OVF&t;0x0010
DECL|macro|GM_MAC_RX_STAT_LEN_ERR_OVF
mdefine_line|#define GM_MAC_RX_STAT_LEN_ERR_OVF&t;0x0020
DECL|macro|GM_MAC_RX_STAT_CODE_ERR_OVF
mdefine_line|#define GM_MAC_RX_STAT_CODE_ERR_OVF&t;0x0040
multiline_comment|/* -- 0x6018&t;&t;MAC control &amp; status&n; */
DECL|macro|GM_MAC_CTRLSTAT
mdefine_line|#define GM_MAC_CTRLSTAT&t;&t;&t;(0x6018 | REG_SZ_32)
DECL|macro|GM_MAC_CTRLSTAT_PAUSE_RCVD
mdefine_line|#define GM_MAC_CTRLSTAT_PAUSE_RCVD&t;0x00000001
DECL|macro|GM_MAC_CTRLSTAT_PAUSE_STATE
mdefine_line|#define GM_MAC_CTRLSTAT_PAUSE_STATE&t;0x00000002
DECL|macro|GM_MAC_CTRLSTAT_PAUSE_NOT
mdefine_line|#define GM_MAC_CTRLSTAT_PAUSE_NOT&t;0x00000004
DECL|macro|GM_MAC_CTRLSTAT_PAUSE_TIM_MASK
mdefine_line|#define GM_MAC_CTRLSTAT_PAUSE_TIM_MASK&t;0xffff0000
DECL|macro|GM_MAC_CTRLSTAT_PAUSE_TIM_SHIFT
mdefine_line|#define GM_MAC_CTRLSTAT_PAUSE_TIM_SHIFT&t;16
multiline_comment|/* -- 0x6020&t;&t;MAC Tx mask&n; * &t;&t;&t;Same bits as MAC Tx status&n; */
DECL|macro|GM_MAC_TX_MASK
mdefine_line|#define GM_MAC_TX_MASK&t;&t;&t;(0x6020 | REG_SZ_16)
multiline_comment|/* -- 0x6024&t;&t;MAC Rx mask&n; * &t;&t;&t;Same bits as MAC Rx status&n; */
DECL|macro|GM_MAC_RX_MASK
mdefine_line|#define GM_MAC_RX_MASK&t;&t;&t;(0x6024 | REG_SZ_16)
multiline_comment|/* -- 0x6028&t;&t;MAC Control/Status mask&n; * &t;&t;&t;Same bits as MAC control/status low order byte&n; */
DECL|macro|GM_MAC_CTRLSTAT_MASK
mdefine_line|#define GM_MAC_CTRLSTAT_MASK&t;&t;(0x6024 | REG_SZ_8)
multiline_comment|/* -- 0x6030&t;&t;MAC Tx configuration&n; */
DECL|macro|GM_MAC_TX_CONFIG
mdefine_line|#define GM_MAC_TX_CONFIG&t;&t;(0x6030 | REG_SZ_16)
DECL|macro|GM_MAC_TX_CONF_ENABLE
mdefine_line|#define GM_MAC_TX_CONF_ENABLE&t;&t;0x0001
DECL|macro|GM_MAC_TX_CONF_IGNORE_CARRIER
mdefine_line|#define GM_MAC_TX_CONF_IGNORE_CARRIER&t;0x0002
DECL|macro|GM_MAC_TX_CONF_IGNORE_COLL
mdefine_line|#define GM_MAC_TX_CONF_IGNORE_COLL&t;0x0004
DECL|macro|GM_MAC_TX_CONF_ENABLE_IPG0
mdefine_line|#define GM_MAC_TX_CONF_ENABLE_IPG0&t;0x0008
DECL|macro|GM_MAC_TX_CONF_DONT_GIVEUP
mdefine_line|#define GM_MAC_TX_CONF_DONT_GIVEUP&t;0x0010
DECL|macro|GM_MAC_TX_CONF_DONT_GIVEUP_NLMT
mdefine_line|#define GM_MAC_TX_CONF_DONT_GIVEUP_NLMT&t;0x0020
DECL|macro|GM_MAC_TX_CONF_NO_BACKOFF
mdefine_line|#define GM_MAC_TX_CONF_NO_BACKOFF&t;0x0040
DECL|macro|GM_MAC_TX_CONF_SLOWDOWN
mdefine_line|#define GM_MAC_TX_CONF_SLOWDOWN&t;&t;0x0080
DECL|macro|GM_MAC_TX_CONF_NO_FCS
mdefine_line|#define GM_MAC_TX_CONF_NO_FCS&t;&t;0x0100
DECL|macro|GM_MAC_TX_CONF_CARRIER_EXT
mdefine_line|#define GM_MAC_TX_CONF_CARRIER_EXT&t;0x0200
multiline_comment|/* -- 0x6034&t;&t;MAC Rx configuration&n; */
DECL|macro|GM_MAC_RX_CONFIG
mdefine_line|#define GM_MAC_RX_CONFIG&t;&t;(0x6034 | REG_SZ_16)
DECL|macro|GM_MAC_RX_CONF_ENABLE
mdefine_line|#define GM_MAC_RX_CONF_ENABLE&t;&t;0x0001
DECL|macro|GM_MAC_RX_CONF_STRIP_PAD
mdefine_line|#define GM_MAC_RX_CONF_STRIP_PAD&t;0x0002
DECL|macro|GM_MAC_RX_CONF_STIP_FCS
mdefine_line|#define GM_MAC_RX_CONF_STIP_FCS&t;&t;0x0004
DECL|macro|GM_MAC_RX_CONF_RX_ALL
mdefine_line|#define GM_MAC_RX_CONF_RX_ALL&t;&t;0x0008
DECL|macro|GM_MAC_RX_CONF_RX_ALL_MULTI
mdefine_line|#define GM_MAC_RX_CONF_RX_ALL_MULTI&t;0x0010
DECL|macro|GM_MAC_RX_CONF_HASH_ENABLE
mdefine_line|#define GM_MAC_RX_CONF_HASH_ENABLE&t;0x0020
DECL|macro|GM_MAC_RX_CONF_ADDR_FLTR_ENABLE
mdefine_line|#define GM_MAC_RX_CONF_ADDR_FLTR_ENABLE&t;0x0040
DECL|macro|GM_MAC_RX_CONF_PASS_ERROR_FRAM
mdefine_line|#define GM_MAC_RX_CONF_PASS_ERROR_FRAM&t;0x0080
DECL|macro|GM_MAC_RX_CONF_CARRIER_EXT
mdefine_line|#define GM_MAC_RX_CONF_CARRIER_EXT&t;0x0100
multiline_comment|/* -- 0x6038&t;&t;MAC control configuration&n; */
DECL|macro|GM_MAC_CTRL_CONFIG
mdefine_line|#define GM_MAC_CTRL_CONFIG&t;&t;(0x6038 | REG_SZ_8)
DECL|macro|GM_MAC_CTRL_CONF_SND_PAUSE_EN
mdefine_line|#define GM_MAC_CTRL_CONF_SND_PAUSE_EN&t;0x01
DECL|macro|GM_MAC_CTRL_CONF_RCV_PAUSE_EN
mdefine_line|#define GM_MAC_CTRL_CONF_RCV_PAUSE_EN&t;0x02
DECL|macro|GM_MAC_CTRL_CONF_PASS_CTRL_FRAM
mdefine_line|#define GM_MAC_CTRL_CONF_PASS_CTRL_FRAM&t;0x04
multiline_comment|/* -- 0x603c&t;&t;MAC XIF configuration */
DECL|macro|GM_MAC_XIF_CONFIG
mdefine_line|#define GM_MAC_XIF_CONFIG&t;&t;(0x603c | REG_SZ_8)
DECL|macro|GM_MAC_XIF_CONF_TX_MII_OUT_EN
mdefine_line|#define GM_MAC_XIF_CONF_TX_MII_OUT_EN&t;0x01
DECL|macro|GM_MAC_XIF_CONF_MII_INT_LOOP
mdefine_line|#define GM_MAC_XIF_CONF_MII_INT_LOOP&t;0x02
DECL|macro|GM_MAC_XIF_CONF_DISABLE_ECHO
mdefine_line|#define GM_MAC_XIF_CONF_DISABLE_ECHO&t;0x04
DECL|macro|GM_MAC_XIF_CONF_GMII_MODE
mdefine_line|#define GM_MAC_XIF_CONF_GMII_MODE&t;0x08
DECL|macro|GM_MAC_XIF_CONF_MII_BUFFER_EN
mdefine_line|#define GM_MAC_XIF_CONF_MII_BUFFER_EN&t;0x10
DECL|macro|GM_MAC_XIF_CONF_LINK_LED
mdefine_line|#define GM_MAC_XIF_CONF_LINK_LED&t;0x20
DECL|macro|GM_MAC_XIF_CONF_FULL_DPLX_LED
mdefine_line|#define GM_MAC_XIF_CONF_FULL_DPLX_LED&t;0x40
multiline_comment|/* -- 0x6040&t;&t;MAC inter-packet GAP 0&n; */
DECL|macro|GM_MAC_INTR_PKT_GAP0
mdefine_line|#define GM_MAC_INTR_PKT_GAP0&t;&t;(0x6040 | REG_SZ_8)
DECL|macro|GM_MAC_INTR_PKT_GAP0_DEFAULT
mdefine_line|#define GM_MAC_INTR_PKT_GAP0_DEFAULT&t;0x00
multiline_comment|/* -- 0x6044&t;&t;MAC inter-packet GAP 1&n; */
DECL|macro|GM_MAC_INTR_PKT_GAP1
mdefine_line|#define GM_MAC_INTR_PKT_GAP1&t;&t;(0x6044 | REG_SZ_8)
DECL|macro|GM_MAC_INTR_PKT_GAP1_DEFAULT
mdefine_line|#define GM_MAC_INTR_PKT_GAP1_DEFAULT&t;0x08
multiline_comment|/* -- 0x6048&t;&t;MAC inter-packet GAP 2&n; */
DECL|macro|GM_MAC_INTR_PKT_GAP2
mdefine_line|#define GM_MAC_INTR_PKT_GAP2&t;&t;(0x6048 | REG_SZ_8)
DECL|macro|GM_MAC_INTR_PKT_GAP2_DEFAULT
mdefine_line|#define GM_MAC_INTR_PKT_GAP2_DEFAULT&t;0x04
multiline_comment|/* -- 604c&t;&t;MAC slot time&n; */
DECL|macro|GM_MAC_SLOT_TIME
mdefine_line|#define GM_MAC_SLOT_TIME&t;&t;(0x604C | REG_SZ_16)
DECL|macro|GM_MAC_SLOT_TIME_DEFAULT
mdefine_line|#define GM_MAC_SLOT_TIME_DEFAULT&t;0x0040
multiline_comment|/* -- 6050&t;&t;MAC minimum frame size&n; */
DECL|macro|GM_MAC_MIN_FRAME_SIZE
mdefine_line|#define GM_MAC_MIN_FRAME_SIZE&t;&t;(0x6050 | REG_SZ_16)
DECL|macro|GM_MAC_MIN_FRAME_SIZE_DEFAULT
mdefine_line|#define GM_MAC_MIN_FRAME_SIZE_DEFAULT&t;0x0040
multiline_comment|/* -- 6054&t;&t;MAC maximum frame size&n; */
DECL|macro|GM_MAC_MAX_FRAME_SIZE
mdefine_line|#define GM_MAC_MAX_FRAME_SIZE&t;&t;(0x6054 | REG_SZ_16)
DECL|macro|GM_MAC_MAX_FRAME_SIZE_DEFAULT
mdefine_line|#define GM_MAC_MAX_FRAME_SIZE_DEFAULT&t;0x05ee
DECL|macro|GM_MAC_MAX_FRAME_SIZE_ALIGN
mdefine_line|#define GM_MAC_MAX_FRAME_SIZE_ALIGN&t;0x5f0
multiline_comment|/* -- 6058&t;&t;MAC preamble length&n; */
DECL|macro|GM_MAC_PREAMBLE_LEN
mdefine_line|#define GM_MAC_PREAMBLE_LEN&t;&t;(0x6058 | REG_SZ_16)
DECL|macro|GM_MAC_PREAMBLE_LEN_DEFAULT
mdefine_line|#define GM_MAC_PREAMBLE_LEN_DEFAULT&t;0x0007
multiline_comment|/* -- 605c&t;&t;MAC jam size&n; */
DECL|macro|GM_MAC_JAM_SIZE
mdefine_line|#define GM_MAC_JAM_SIZE&t;&t;&t;(0x605c | REG_SZ_8)
DECL|macro|GM_MAC_JAM_SIZE_DEFAULT
mdefine_line|#define GM_MAC_JAM_SIZE_DEFAULT&t;&t;0x04
multiline_comment|/* -- 6060&t;&t;MAC attempt limit&n; */
DECL|macro|GM_MAC_ATTEMPT_LIMIT
mdefine_line|#define GM_MAC_ATTEMPT_LIMIT&t;&t;(0x6060 | REG_SZ_8)
DECL|macro|GM_MAC_ATTEMPT_LIMIT_DEFAULT
mdefine_line|#define GM_MAC_ATTEMPT_LIMIT_DEFAULT&t;0x10
multiline_comment|/* -- 6064&t;&t;MAC control type&n; */
DECL|macro|GM_MAC_CONTROL_TYPE
mdefine_line|#define GM_MAC_CONTROL_TYPE&t;&t;(0x6064 | REG_SZ_16)
DECL|macro|GM_MAC_CONTROL_TYPE_DEFAULT
mdefine_line|#define GM_MAC_CONTROL_TYPE_DEFAULT&t;0x8808
multiline_comment|/* -- 6080&t;&t;MAC address 15..0&n; * -- 6084&t;&t;MAC address 16..31&n; * -- 6088&t;&t;MAC address 32..47&n; */
DECL|macro|GM_MAC_ADDR_NORMAL0
mdefine_line|#define GM_MAC_ADDR_NORMAL0&t;&t;(0x6080 | REG_SZ_16)
DECL|macro|GM_MAC_ADDR_NORMAL1
mdefine_line|#define GM_MAC_ADDR_NORMAL1&t;&t;(0x6084 | REG_SZ_16)
DECL|macro|GM_MAC_ADDR_NORMAL2
mdefine_line|#define GM_MAC_ADDR_NORMAL2&t;&t;(0x6088 | REG_SZ_16)
multiline_comment|/* -- 608c&t;&t;MAC alternate address 15..0&n; * -- 6090&t;&t;MAC alternate address 16..31&n; * -- 6094&t;&t;MAC alternate address 32..47&n; */
DECL|macro|GM_MAC_ADDR_ALT0
mdefine_line|#define GM_MAC_ADDR_ALT0&t;&t;(0x608c | REG_SZ_16)
DECL|macro|GM_MAC_ADDR_ALT1
mdefine_line|#define GM_MAC_ADDR_ALT1&t;&t;(0x6090 | REG_SZ_16)
DECL|macro|GM_MAC_ADDR_ALT2
mdefine_line|#define GM_MAC_ADDR_ALT2&t;&t;(0x6094 | REG_SZ_16)
multiline_comment|/* -- 6098&t;&t;MAC control address 15..0&n; * -- 609c&t;&t;MAC control address 16..31&n; * -- 60a0&t;&t;MAC control address 32..47&n; */
DECL|macro|GM_MAC_ADDR_CTRL0
mdefine_line|#define GM_MAC_ADDR_CTRL0&t;&t;(0x6098 | REG_SZ_16)
DECL|macro|GM_MAC_ADDR_CTRL1
mdefine_line|#define GM_MAC_ADDR_CTRL1&t;&t;(0x609c | REG_SZ_16)
DECL|macro|GM_MAC_ADDR_CTRL2
mdefine_line|#define GM_MAC_ADDR_CTRL2&t;&t;(0x60a0 | REG_SZ_16)
multiline_comment|/* -- 60a4&t;&t;MAC address filter (0_0)&n; * -- 60a8&t;&t;MAC address filter (0_1)&n; * -- 60ac&t;&t;MAC address filter (0_2)&n; */
DECL|macro|GM_MAC_ADDR_FILTER0
mdefine_line|#define GM_MAC_ADDR_FILTER0&t;&t;(0x60a4 | REG_SZ_16)
DECL|macro|GM_MAC_ADDR_FILTER1
mdefine_line|#define GM_MAC_ADDR_FILTER1&t;&t;(0x60a8 | REG_SZ_16)
DECL|macro|GM_MAC_ADDR_FILTER2
mdefine_line|#define GM_MAC_ADDR_FILTER2&t;&t;(0x60ac | REG_SZ_16)
multiline_comment|/* -- 60b0&t;&t;MAC address filter mask 1,2&n; */
DECL|macro|GM_MAC_ADDR_FILTER_MASK1_2
mdefine_line|#define GM_MAC_ADDR_FILTER_MASK1_2&t;(0x60b0 | REG_SZ_8)
multiline_comment|/* -- 60b4&t;&t;MAC address filter mask 0&n; */
DECL|macro|GM_MAC_ADDR_FILTER_MASK0
mdefine_line|#define GM_MAC_ADDR_FILTER_MASK0&t;(0x60b4 | REG_SZ_16)
multiline_comment|/* -- [60c0 .. 60fc]&t;MAC hash table&n; */
DECL|macro|GM_MAC_ADDR_FILTER_HASH0
mdefine_line|#define GM_MAC_ADDR_FILTER_HASH0&t;(0x60c0 | REG_SZ_16)
multiline_comment|/* -- 6100&t;&t;MAC normal collision counter&n; */
DECL|macro|GM_MAC_COLLISION_CTR
mdefine_line|#define GM_MAC_COLLISION_CTR&t;&t;(0x6100 | REG_SZ_16)
multiline_comment|/* -- 6104&t;&t;MAC 1st successful collision counter&n; */
DECL|macro|GM_MAC_FIRST_COLLISION_CTR
mdefine_line|#define GM_MAC_FIRST_COLLISION_CTR&t;(0x6104 | REG_SZ_16)
multiline_comment|/* -- 6108&t;&t;MAC excess collision counter&n; */
DECL|macro|GM_MAC_EXCS_COLLISION_CTR
mdefine_line|#define GM_MAC_EXCS_COLLISION_CTR&t;(0x6108 | REG_SZ_16)
multiline_comment|/* -- 610c&t;&t;MAC late collision counter&n; */
DECL|macro|GM_MAC_LATE_COLLISION_CTR
mdefine_line|#define GM_MAC_LATE_COLLISION_CTR&t;(0x610c | REG_SZ_16)
multiline_comment|/* -- 6110&t;&t;MAC defer timer counter&n; */
DECL|macro|GM_MAC_DEFER_TIMER_COUNTER
mdefine_line|#define GM_MAC_DEFER_TIMER_COUNTER&t;(0x6110 | REG_SZ_16)
multiline_comment|/* -- 6114&t;&t;MAC peak attempts&n; */
DECL|macro|GM_MAC_PEAK_ATTEMPTS
mdefine_line|#define GM_MAC_PEAK_ATTEMPTS&t;&t;(0x6114 | REG_SZ_16)
multiline_comment|/* -- 6118&t;&t;MAC Rx frame counter&n; */
DECL|macro|GM_MAC_RX_FRAME_CTR
mdefine_line|#define GM_MAC_RX_FRAME_CTR&t;&t;(0x6118 | REG_SZ_16)
multiline_comment|/* -- 611c&t;&t;MAC Rx length error counter&n; */
DECL|macro|GM_MAC_RX_LEN_ERR_CTR
mdefine_line|#define GM_MAC_RX_LEN_ERR_CTR&t;&t;(0x611c | REG_SZ_16)
multiline_comment|/* -- 6120&t;&t;MAC Rx alignment error counter&n; */
DECL|macro|GM_MAC_RX_ALIGN_ERR_CTR
mdefine_line|#define GM_MAC_RX_ALIGN_ERR_CTR&t;&t;(0x6120 | REG_SZ_16)
multiline_comment|/* -- 6124&t;&t;MAC Rx CRC error counter&n; */
DECL|macro|GM_MAC_RX_CRC_ERR_CTR
mdefine_line|#define GM_MAC_RX_CRC_ERR_CTR&t;&t;(0x6124 | REG_SZ_16)
multiline_comment|/* -- 6128&t;&t;MAC Rx code violation error counter&n; */
DECL|macro|GM_MAC_RX_CODE_VIOLATION_CTR
mdefine_line|#define GM_MAC_RX_CODE_VIOLATION_CTR&t;(0x6128 | REG_SZ_16)
multiline_comment|/* -- 6130&t;&t;MAC random number seed&n; */
DECL|macro|GM_MAC_RANDOM_SEED
mdefine_line|#define GM_MAC_RANDOM_SEED&t;&t;(0x6130 | REG_SZ_16)
multiline_comment|/* -- 6134&t;&t;MAC state machine&n; */
DECL|macro|GM_MAC_STATE_MACHINE
mdefine_line|#define GM_MAC_STATE_MACHINE&t;&t;(0x6134 | REG_SZ_8)
multiline_comment|/*&n;&t; * MIF registers&n;&t; */
multiline_comment|/* -- 0x6200&t;RW&t;MIF bit bang clock&n; */
DECL|macro|GM_MIF_BB_CLOCK
mdefine_line|#define GM_MIF_BB_CLOCK&t;&t;&t;(0x6200 | REG_SZ_8)
multiline_comment|/* -- 0x6204&t;RW&t;MIF bit bang data&n; */
DECL|macro|GM_MIF_BB_DATA
mdefine_line|#define GM_MIF_BB_DATA&t;&t;&t;(0x6204 | REG_SZ_8)
multiline_comment|/* -- 0x6208&t;RW&t;MIF bit bang output enable&n; */
DECL|macro|GM_MIF_BB_OUT_ENABLE
mdefine_line|#define GM_MIF_BB_OUT_ENABLE&t;&t;(0x6208 | REG_SZ_8)
multiline_comment|/* -- 0x620c&t;RW&t;MIF frame control &amp; data&n; */
DECL|macro|GM_MIF_FRAME_CTL_DATA
mdefine_line|#define GM_MIF_FRAME_CTL_DATA&t;&t;(0x620c | REG_SZ_32)
DECL|macro|GM_MIF_FRAME_START_MASK
mdefine_line|#define GM_MIF_FRAME_START_MASK&t;&t;0xc0000000
DECL|macro|GM_MIF_FRAME_START_SHIFT
mdefine_line|#define GM_MIF_FRAME_START_SHIFT&t;30
DECL|macro|GM_MIF_FRAME_OPCODE_MASK
mdefine_line|#define GM_MIF_FRAME_OPCODE_MASK&t;0x30000000
DECL|macro|GM_MIF_FRAME_OPCODE_SHIFT
mdefine_line|#define GM_MIF_FRAME_OPCODE_SHIFT&t;28
DECL|macro|GM_MIF_FRAME_PHY_ADDR_MASK
mdefine_line|#define GM_MIF_FRAME_PHY_ADDR_MASK&t;0x0f800000
DECL|macro|GM_MIF_FRAME_PHY_ADDR_SHIFT
mdefine_line|#define GM_MIF_FRAME_PHY_ADDR_SHIFT&t;23
DECL|macro|GM_MIF_FRAME_REG_ADDR_MASK
mdefine_line|#define GM_MIF_FRAME_REG_ADDR_MASK&t;0x007c0000
DECL|macro|GM_MIF_FRAME_REG_ADDR_SHIFT
mdefine_line|#define GM_MIF_FRAME_REG_ADDR_SHIFT&t;18
DECL|macro|GM_MIF_FRAME_TURNAROUND_HI
mdefine_line|#define GM_MIF_FRAME_TURNAROUND_HI&t;0x00020000
DECL|macro|GM_MIF_FRAME_TURNAROUND_LO
mdefine_line|#define GM_MIF_FRAME_TURNAROUND_LO&t;0x00010000
DECL|macro|GM_MIF_FRAME_DATA_MASK
mdefine_line|#define GM_MIF_FRAME_DATA_MASK&t;&t;0x0000ffff
DECL|macro|GM_MIF_FRAME_DATA_SHIFT
mdefine_line|#define GM_MIF_FRAME_DATA_SHIFT&t;&t;0
multiline_comment|/* -- 0x6210&t;RW&t;MIF config reg&n; */
DECL|macro|GM_MIF_CFG
mdefine_line|#define GM_MIF_CFG&t;&t;&t;(0x6210 | REG_SZ_16)
DECL|macro|GM_MIF_CFGPS
mdefine_line|#define&t;GM_MIF_CFGPS&t;&t;&t;0x00000001&t;/* PHY Select */
DECL|macro|GM_MIF_CFGPE
mdefine_line|#define&t;GM_MIF_CFGPE&t;&t;&t;0x00000002&t;/* Poll Enable */
DECL|macro|GM_MIF_CFGBB
mdefine_line|#define&t;GM_MIF_CFGBB&t;&t;&t;0x00000004&t;/* Bit Bang Enable */
DECL|macro|GM_MIF_CFGPR_MASK
mdefine_line|#define&t;GM_MIF_CFGPR_MASK&t;&t;0x000000f8&t;/* Poll Register address */
DECL|macro|GM_MIF_CFGPR_SHIFT
mdefine_line|#define&t;GM_MIF_CFGPR_SHIFT&t;&t;3
DECL|macro|GM_MIF_CFGM0
mdefine_line|#define&t;GM_MIF_CFGM0&t;&t;&t;0x00000100&t;/* MDIO_0 Data / MDIO_0 attached */
DECL|macro|GM_MIF_CFGM1
mdefine_line|#define&t;GM_MIF_CFGM1&t;&t;&t;0x00000200&t;/* MDIO_1 Data / MDIO_1 attached */
DECL|macro|GM_MIF_CFGPD_MASK
mdefine_line|#define&t;GM_MIF_CFGPD_MASK&t;&t;0x00007c00&t;/* Poll Device PHY address */
DECL|macro|GM_MIF_CFGPD_SHIFT
mdefine_line|#define&t;GM_MIF_CFGPD_SHIFT&t;&t;10
DECL|macro|GM_MIF_POLL_DELAY
mdefine_line|#define&t;GM_MIF_POLL_DELAY&t;&t;200
DECL|macro|GM_INTERNAL_PHYAD
mdefine_line|#define&t;GM_INTERNAL_PHYAD&t;&t;1&t;&t;/* PHY address for int. transceiver */
DECL|macro|GM_EXTERNAL_PHYAD
mdefine_line|#define&t;GM_EXTERNAL_PHYAD&t;&t;0&t;&t;/* PHY address for ext. transceiver */
multiline_comment|/* -- 0x6214&t;RW&t;MIF interrupt mask reg&n; *&t;&t;&t;same as basic/status Register&n; */
DECL|macro|GM_MIF_IRQ_MASK
mdefine_line|#define GM_MIF_IRQ_MASK&t;&t;&t;(0x6214 | REG_SZ_16)
multiline_comment|/* -- 0x6218&t;RW&t;MIF basic/status reg&n; *&t;&t;&t;The Basic portion of this register indicates the last&n; *&t;&t;&t;value of the register read indicated in the POLL REG field&n; *&t;&t;&t;of the Configuration Register.&n; *&t;&t;&t;The Status portion indicates bit(s) that have changed.&n; *&t;&t;&t;The MIF Mask register is corresponding to this register in&n; *&t;&t;&t;terms of the bit(s) that need to be masked for generating&n; *&t;&t;&t;interrupt on the MIF Interrupt Bit of the Global Status Rgister.&n; */
DECL|macro|GM_MIF_STATUS
mdefine_line|#define GM_MIF_STATUS&t;&t;&t;(0x6218 | REG_SZ_32)
DECL|macro|GM_MIF_STATUS_MASK
mdefine_line|#define&t;GM_MIF_STATUS_MASK&t;&t;0x0000ffff&t;/* 0-15 : Status */
DECL|macro|GM_MIF_BASIC_MASK
mdefine_line|#define&t;GM_MIF_BASIC_MASK&t;&t;0xffff0000&t;/* 16-31 : Basic register */
multiline_comment|/*&n;&t; * PCS link registers&n;&t; */
multiline_comment|/* -- 0x9000&t;RW&t;PCS mii control reg&n; */
DECL|macro|GM_PCS_CONTROL
mdefine_line|#define GM_PCS_CONTROL&t;&t;&t;(0x9000 | REG_SZ_16)
multiline_comment|/* -- 0x9004&t;RW&t;PCS mii status reg&n; */
DECL|macro|GM_PCS_STATUS
mdefine_line|#define GM_PCS_STATUS&t;&t;&t;(0x9004 | REG_SZ_16)
multiline_comment|/* -- 0x9008&t;RW&t;PCS mii advertisement&n; */
DECL|macro|GM_PCS_ADVERTISEMENT
mdefine_line|#define GM_PCS_ADVERTISEMENT&t;&t;(0x9008 | REG_SZ_16)
multiline_comment|/* -- 0x900c&t;RW&t;PCS mii LP ability&n; */
DECL|macro|GM_PCS_ABILITY
mdefine_line|#define GM_PCS_ABILITY&t;&t;&t;(0x900c | REG_SZ_16)
multiline_comment|/* -- 0x9010&t;RW&t;PCS config&n; */
DECL|macro|GM_PCS_CONFIG
mdefine_line|#define GM_PCS_CONFIG&t;&t;&t;(0x9010 | REG_SZ_8)
multiline_comment|/* -- 0x9014&t;RW&t;PCS state machine&n; */
DECL|macro|GM_PCS_STATE_MACHINE
mdefine_line|#define GM_PCS_STATE_MACHINE&t;&t;(0x9014 | REG_SZ_32)
multiline_comment|/* -- 0x9018&t;RW&t;PCS interrupt status&n; */
DECL|macro|GM_PCS_IRQ_STATUS
mdefine_line|#define GM_PCS_IRQ_STATUS&t;&t;(0x9018 | REG_SZ_8)
multiline_comment|/* -- 0x9050&t;RW&t;PCS datapath mode&n; */
DECL|macro|GM_PCS_DATAPATH_MODE
mdefine_line|#define GM_PCS_DATAPATH_MODE&t;&t;(0x9050 | REG_SZ_8)
DECL|macro|GM_PCS_DATAPATH_INTERNAL
mdefine_line|#define GM_PCS_DATAPATH_INTERNAL&t;0x01&t;/* Internal serial link */
DECL|macro|GM_PCS_DATAPATH_SERDES
mdefine_line|#define GM_PCS_DATAPATH_SERDES&t;&t;0x02&t;/* 10-bit Serdes interface */
DECL|macro|GM_PCS_DATAPATH_MII
mdefine_line|#define GM_PCS_DATAPATH_MII&t;&t;0x04&t;/* Select mii/gmii mode */
DECL|macro|GM_PCS_DATAPATH_GMII_OUT
mdefine_line|#define GM_PCS_DATAPATH_GMII_OUT&t;0x08&t;/* serial mode only, copy data to gmii */
multiline_comment|/* -- 0x9054&t;RW&t;PCS serdes control&n; */
DECL|macro|GM_PCS_SERDES_CTRL
mdefine_line|#define GM_PCS_SERDES_CTRL&t;&t;(0x9054 | REG_SZ_8)
multiline_comment|/* -- 0x9058&t;RW&t;PCS serdes output select&n; */
DECL|macro|GM_PCS_SERDES_SELECT
mdefine_line|#define GM_PCS_SERDES_SELECT&t;&t;(0x9058 | REG_SZ_8)
multiline_comment|/* -- 0x905c&t;RW&t;PCS serdes state&n; */
DECL|macro|GM_PCS_SERDES_STATE
mdefine_line|#define GM_PCS_SERDES_STATE&t;&t;(0x905c | REG_SZ_8)
multiline_comment|/*&n;&t; * PHY registers&n;&t; */
multiline_comment|/*&n; * Standard PHY registers (from de4x5.h)&n; */
DECL|macro|MII_CR
mdefine_line|#define MII_CR       0x00          /* MII Management Control Register */
DECL|macro|MII_SR
mdefine_line|#define MII_SR       0x01          /* MII Management Status Register */
DECL|macro|MII_ID0
mdefine_line|#define MII_ID0      0x02          /* PHY Identifier Register 0 */
DECL|macro|MII_ID1
mdefine_line|#define MII_ID1      0x03          /* PHY Identifier Register 1 */
DECL|macro|MII_ANA
mdefine_line|#define MII_ANA      0x04          /* Auto Negotiation Advertisement */
DECL|macro|MII_ANLPA
mdefine_line|#define MII_ANLPA    0x05          /* Auto Negotiation Link Partner Ability */
DECL|macro|MII_ANE
mdefine_line|#define MII_ANE      0x06          /* Auto Negotiation Expansion */
DECL|macro|MII_ANP
mdefine_line|#define MII_ANP      0x07          /* Auto Negotiation Next Page TX */
multiline_comment|/*&n;** MII Management Control Register&n;*/
DECL|macro|MII_CR_RST
mdefine_line|#define MII_CR_RST  0x8000         /* RESET the PHY chip */
DECL|macro|MII_CR_LPBK
mdefine_line|#define MII_CR_LPBK 0x4000         /* Loopback enable */
DECL|macro|MII_CR_SPD
mdefine_line|#define MII_CR_SPD  0x2000         /* 0: 10Mb/s; 1: 100Mb/s */
DECL|macro|MII_CR_10
mdefine_line|#define MII_CR_10   0x0000         /* Set 10Mb/s */
DECL|macro|MII_CR_100
mdefine_line|#define MII_CR_100  0x2000         /* Set 100Mb/s */
DECL|macro|MII_CR_ASSE
mdefine_line|#define MII_CR_ASSE 0x1000         /* Auto Speed Select Enable */
DECL|macro|MII_CR_PD
mdefine_line|#define MII_CR_PD   0x0800         /* Power Down */
DECL|macro|MII_CR_ISOL
mdefine_line|#define MII_CR_ISOL 0x0400         /* Isolate Mode */
DECL|macro|MII_CR_RAN
mdefine_line|#define MII_CR_RAN  0x0200         /* Restart Auto Negotiation */
DECL|macro|MII_CR_FDM
mdefine_line|#define MII_CR_FDM  0x0100         /* Full Duplex Mode */
DECL|macro|MII_CR_CTE
mdefine_line|#define MII_CR_CTE  0x0080         /* Collision Test Enable */
multiline_comment|/*&n;** MII Management Status Register&n;*/
DECL|macro|MII_SR_T4C
mdefine_line|#define MII_SR_T4C  0x8000         /* 100BASE-T4 capable */
DECL|macro|MII_SR_TXFD
mdefine_line|#define MII_SR_TXFD 0x4000         /* 100BASE-TX Full Duplex capable */
DECL|macro|MII_SR_TXHD
mdefine_line|#define MII_SR_TXHD 0x2000         /* 100BASE-TX Half Duplex capable */
DECL|macro|MII_SR_TFD
mdefine_line|#define MII_SR_TFD  0x1000         /* 10BASE-T Full Duplex capable */
DECL|macro|MII_SR_THD
mdefine_line|#define MII_SR_THD  0x0800         /* 10BASE-T Half Duplex capable */
DECL|macro|MII_SR_ASSC
mdefine_line|#define MII_SR_ASSC 0x0020         /* Auto Speed Selection Complete*/
DECL|macro|MII_SR_RFD
mdefine_line|#define MII_SR_RFD  0x0010         /* Remote Fault Detected */
DECL|macro|MII_SR_ANC
mdefine_line|#define MII_SR_ANC  0x0008         /* Auto Negotiation capable */
DECL|macro|MII_SR_LKS
mdefine_line|#define MII_SR_LKS  0x0004         /* Link Status */
DECL|macro|MII_SR_JABD
mdefine_line|#define MII_SR_JABD 0x0002         /* Jabber Detect */
DECL|macro|MII_SR_XC
mdefine_line|#define MII_SR_XC   0x0001         /* Extended Capabilities */
multiline_comment|/*&n;** MII Management Auto Negotiation Advertisement Register&n;*/
DECL|macro|MII_ANA_TAF
mdefine_line|#define MII_ANA_TAF  0x03e0        /* Technology Ability Field */
DECL|macro|MII_ANA_T4AM
mdefine_line|#define MII_ANA_T4AM 0x0200        /* T4 Technology Ability Mask */
DECL|macro|MII_ANA_TXAM
mdefine_line|#define MII_ANA_TXAM 0x0180        /* TX Technology Ability Mask */
DECL|macro|MII_ANA_FDAM
mdefine_line|#define MII_ANA_FDAM 0x0140        /* Full Duplex Technology Ability Mask */
DECL|macro|MII_ANA_HDAM
mdefine_line|#define MII_ANA_HDAM 0x02a0        /* Half Duplex Technology Ability Mask */
DECL|macro|MII_ANA_100M
mdefine_line|#define MII_ANA_100M 0x0380        /* 100Mb Technology Ability Mask */
DECL|macro|MII_ANA_10M
mdefine_line|#define MII_ANA_10M  0x0060        /* 10Mb Technology Ability Mask */
DECL|macro|MII_ANA_CSMA
mdefine_line|#define MII_ANA_CSMA 0x0001        /* CSMA-CD Capable */
multiline_comment|/*&n;** MII Management Auto Negotiation Remote End Register&n;*/
DECL|macro|MII_ANLPA_NP
mdefine_line|#define MII_ANLPA_NP   0x8000      /* Next Page (Enable) */
DECL|macro|MII_ANLPA_ACK
mdefine_line|#define MII_ANLPA_ACK  0x4000      /* Remote Acknowledge */
DECL|macro|MII_ANLPA_RF
mdefine_line|#define MII_ANLPA_RF   0x2000      /* Remote Fault */
DECL|macro|MII_ANLPA_TAF
mdefine_line|#define MII_ANLPA_TAF  0x03e0      /* Technology Ability Field */
DECL|macro|MII_ANLPA_T4AM
mdefine_line|#define MII_ANLPA_T4AM 0x0200      /* T4 Technology Ability Mask */
DECL|macro|MII_ANLPA_TXAM
mdefine_line|#define MII_ANLPA_TXAM 0x0180      /* TX Technology Ability Mask */
DECL|macro|MII_ANLPA_FDAM
mdefine_line|#define MII_ANLPA_FDAM 0x0140      /* Full Duplex Technology Ability Mask */
DECL|macro|MII_ANLPA_HDAM
mdefine_line|#define MII_ANLPA_HDAM 0x02a0      /* Half Duplex Technology Ability Mask */
DECL|macro|MII_ANLPA_100M
mdefine_line|#define MII_ANLPA_100M 0x0380      /* 100Mb Technology Ability Mask */
DECL|macro|MII_ANLPA_10M
mdefine_line|#define MII_ANLPA_10M  0x0060      /* 10Mb Technology Ability Mask */
DECL|macro|MII_ANLPA_CSMA
mdefine_line|#define MII_ANLPA_CSMA 0x0001      /* CSMA-CD Capable */
DECL|macro|MII_ANLPA_PAUS
mdefine_line|#define MII_ANLPA_PAUS 0x0400 
multiline_comment|/*&n; * Model-specific PHY registers&n; *&n; * Note: Only the BCM5201 is described here for now. I&squot;ll add the 5400 once&n; *       I see a machine using it in real world.&n; */
multiline_comment|/* Supported PHYs (phy_type field ) */
DECL|macro|PHY_B5400
mdefine_line|#define PHY_B5400&t;0x5400
DECL|macro|PHY_B5201
mdefine_line|#define PHY_B5201&t;0x5201
DECL|macro|PHY_LXT971
mdefine_line|#define PHY_LXT971&t;0x0971
DECL|macro|PHY_UNKNOWN
mdefine_line|#define PHY_UNKNOWN&t;0
multiline_comment|/* Identification (for multi-PHY) */
DECL|macro|MII_BCM5201_OUI
mdefine_line|#define MII_BCM5201_OUI                         0x001018
DECL|macro|MII_BCM5201_MODEL
mdefine_line|#define MII_BCM5201_MODEL                       0x21
DECL|macro|MII_BCM5201_REV
mdefine_line|#define MII_BCM5201_REV                         0x01
DECL|macro|MII_BCM5201_ID
mdefine_line|#define MII_BCM5201_ID                          ((MII_BCM5201_OUI &lt;&lt; 10) | (MII_BCM5201_MODEL &lt;&lt; 4))
DECL|macro|MII_BCM5201_MASK
mdefine_line|#define MII_BCM5201_MASK                        0xfffffff0
DECL|macro|MII_BCM5400_OUI
mdefine_line|#define MII_BCM5400_OUI                         0x000818
DECL|macro|MII_BCM5400_MODEL
mdefine_line|#define MII_BCM5400_MODEL                       0x04
DECL|macro|MII_BCM5400_REV
mdefine_line|#define MII_BCM5400_REV                         0x01
DECL|macro|MII_BCM5400_ID
mdefine_line|#define MII_BCM5400_ID                          ((MII_BCM5400_OUI &lt;&lt; 10) | (MII_BCM5400_MODEL &lt;&lt; 4))
DECL|macro|MII_BCM5400_MASK
mdefine_line|#define MII_BCM5400_MASK                        0xfffffff0
DECL|macro|MII_LXT971_OUI
mdefine_line|#define MII_LXT971_OUI                          0x0004de
DECL|macro|MII_LXT971_MODEL
mdefine_line|#define MII_LXT971_MODEL                        0x0e
DECL|macro|MII_LXT971_REV
mdefine_line|#define MII_LXT971_REV                          0x00
DECL|macro|MII_LXT971_ID
mdefine_line|#define MII_LXT971_ID                           ((MII_LXT971_OUI &lt;&lt; 10) | (MII_LXT971_MODEL &lt;&lt; 4))
DECL|macro|MII_LXT971_MASK
mdefine_line|#define MII_LXT971_MASK                         0xfffffff0
multiline_comment|/* BCM5201 AUX STATUS register */
DECL|macro|MII_BCM5201_AUXCTLSTATUS
mdefine_line|#define MII_BCM5201_AUXCTLSTATUS&t;&t;0x18
DECL|macro|MII_BCM5201_AUXCTLSTATUS_DUPLEX
mdefine_line|#define MII_BCM5201_AUXCTLSTATUS_DUPLEX&t;&t;0x0001
DECL|macro|MII_BCM5201_AUXCTLSTATUS_SPEED
mdefine_line|#define MII_BCM5201_AUXCTLSTATUS_SPEED&t;&t;0x0002
multiline_comment|/* MII BCM5201 MULTIPHY interrupt register */
DECL|macro|MII_BCM5201_INTERRUPT
mdefine_line|#define MII_BCM5201_INTERRUPT&t;&t;&t;0x1A
DECL|macro|MII_BCM5201_INTERRUPT_INTENABLE
mdefine_line|#define MII_BCM5201_INTERRUPT_INTENABLE&t;&t;0x4000
DECL|macro|MII_BCM5201_AUXMODE2
mdefine_line|#define MII_BCM5201_AUXMODE2&t;&t;&t;0x1B
DECL|macro|MII_BCM5201_AUXMODE2_LOWPOWER
mdefine_line|#define MII_BCM5201_AUXMODE2_LOWPOWER&t;&t;0x0008
DECL|macro|MII_BCM5201_MULTIPHY
mdefine_line|#define MII_BCM5201_MULTIPHY                    0x1E
multiline_comment|/* MII BCM5201 MULTIPHY register bits */
DECL|macro|MII_BCM5201_MULTIPHY_SERIALMODE
mdefine_line|#define MII_BCM5201_MULTIPHY_SERIALMODE         0x0002
DECL|macro|MII_BCM5201_MULTIPHY_SUPERISOLATE
mdefine_line|#define MII_BCM5201_MULTIPHY_SUPERISOLATE       0x0008
multiline_comment|/* MII BCM5400 1000-BASET Control register */
DECL|macro|MII_BCM5400_GB_CONTROL
mdefine_line|#define MII_BCM5400_GB_CONTROL&t;&t;&t;0x09
DECL|macro|MII_BCM5400_GB_CONTROL_FULLDUPLEXCAP
mdefine_line|#define MII_BCM5400_GB_CONTROL_FULLDUPLEXCAP&t;0x0200
multiline_comment|/* MII BCM5400 AUXCONTROL register */
DECL|macro|MII_BCM5400_AUXCONTROL
mdefine_line|#define MII_BCM5400_AUXCONTROL                  0x18
DECL|macro|MII_BCM5400_AUXCONTROL_PWR10BASET
mdefine_line|#define MII_BCM5400_AUXCONTROL_PWR10BASET       0x0004
multiline_comment|/* MII BCM5400 AUXSTATUS register */
DECL|macro|MII_BCM5400_AUXSTATUS
mdefine_line|#define MII_BCM5400_AUXSTATUS                   0x19
DECL|macro|MII_BCM5400_AUXSTATUS_LINKMODE_MASK
mdefine_line|#define MII_BCM5400_AUXSTATUS_LINKMODE_MASK     0x0700
DECL|macro|MII_BCM5400_AUXSTATUS_LINKMODE_SHIFT
mdefine_line|#define MII_BCM5400_AUXSTATUS_LINKMODE_SHIFT    8  
multiline_comment|/* MII LXT971 STATUS2 register */
DECL|macro|MII_LXT971_STATUS2
mdefine_line|#define MII_LXT971_STATUS2&t;&t;&t;0x11
DECL|macro|MII_LXT971_STATUS2_SPEED
mdefine_line|#define MII_LXT971_STATUS2_SPEED&t;&t;0x4000
DECL|macro|MII_LXT971_STATUS2_LINK
mdefine_line|#define MII_LXT971_STATUS2_LINK&t;&t;&t;0x0400
DECL|macro|MII_LXT971_STATUS2_FULLDUPLEX
mdefine_line|#define MII_LXT971_STATUS2_FULLDUPLEX&t;&t;0x0200
DECL|macro|MII_LXT971_STATUS2_AUTONEG_COMPLETE
mdefine_line|#define MII_LXT971_STATUS2_AUTONEG_COMPLETE&t;0x0080
multiline_comment|/*&n;&t; * DMA descriptors&n;&t; */
multiline_comment|/* &n; * Descriptor counts and buffer sizes&n; */
DECL|macro|NTX
mdefine_line|#define NTX&t;&t;&t;64&t;&t;/* must be power of 2 */
DECL|macro|NTX_CONF
mdefine_line|#define NTX_CONF&t;&t;GM_TX_RING_SZ_64
DECL|macro|NRX
mdefine_line|#define NRX&t;&t;&t;64&t;&t;/* must be power of 2 */
DECL|macro|NRX_CONF
mdefine_line|#define NRX_CONF&t;&t;GM_RX_RING_SZ_64
DECL|macro|RX_COPY_THRESHOLD
mdefine_line|#define RX_COPY_THRESHOLD&t;256
DECL|macro|GMAC_BUFFER_ALIGN
mdefine_line|#define GMAC_BUFFER_ALIGN&t;32&t;&t;/* Align on a cache line */
DECL|macro|RX_BUF_ALLOC_SIZE
mdefine_line|#define RX_BUF_ALLOC_SIZE&t;(ETH_FRAME_LEN + GMAC_BUFFER_ALIGN + 2)
DECL|macro|RX_OFFSET
mdefine_line|#define RX_OFFSET&t;&t;2
multiline_comment|/*&n; * Definitions of Rx and Tx descriptors&n; */
DECL|struct|gmac_dma_desc
r_struct
id|gmac_dma_desc
(brace
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* data size and OWN bit */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* flags */
DECL|member|lo_addr
r_int
r_int
id|lo_addr
suffix:semicolon
multiline_comment|/* phys addr, low 32 bits */
DECL|member|hi_addr
r_int
r_int
id|hi_addr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Rx bits&n; */
multiline_comment|/* Bits in size */
DECL|macro|RX_SZ_OWN
mdefine_line|#define RX_SZ_OWN&t;&t;0x80000000&t;/* 1 = owned by chip */
DECL|macro|RX_SZ_MASK
mdefine_line|#define RX_SZ_MASK&t;&t;0x7FFF0000
DECL|macro|RX_SZ_SHIFT
mdefine_line|#define RX_SZ_SHIFT&t;&t;16
DECL|macro|RX_SZ_CKSUM_MASK
mdefine_line|#define RX_SZ_CKSUM_MASK&t;0x0000FFFF
multiline_comment|/* Bits in flags */
DECL|macro|RX_FL_CRC_ERROR
mdefine_line|#define RX_FL_CRC_ERROR&t;&t;0x40000000
DECL|macro|RX_FL_ALT_ADDR
mdefine_line|#define RX_FL_ALT_ADDR&t;&t;0x20000000&t;/* Packet rcv. from alt MAC address */
multiline_comment|/* &n; * Tx bits&n; */
multiline_comment|/* Bits in size */
DECL|macro|TX_SZ_MASK
mdefine_line|#define TX_SZ_MASK&t;&t;0x00007FFF
DECL|macro|TX_SZ_CRC_MASK
mdefine_line|#define TX_SZ_CRC_MASK&t;&t;0x00FF8000
DECL|macro|TX_SZ_CRC_STUFF
mdefine_line|#define TX_SZ_CRC_STUFF&t;&t;0x1F000000
DECL|macro|TX_SZ_CRC_ENABLE
mdefine_line|#define TX_SZ_CRC_ENABLE&t;0x20000000
DECL|macro|TX_SZ_EOP
mdefine_line|#define TX_SZ_EOP&t;&t;0x40000000
DECL|macro|TX_SZ_SOP
mdefine_line|#define TX_SZ_SOP&t;&t;0x80000000
multiline_comment|/* Bits in flags */
DECL|macro|TX_FL_INTERRUPT
mdefine_line|#define TX_FL_INTERRUPT&t;&t;0x00000001
DECL|macro|TX_FL_NO_CRC
mdefine_line|#define TX_FL_NO_CRC&t;&t;0x00000002
multiline_comment|/*&n;&t; * Other stuffs&n;&t; */
DECL|struct|gmac
r_struct
id|gmac
(brace
DECL|member|regs
r_volatile
r_int
r_int
op_star
id|regs
suffix:semicolon
multiline_comment|/* hardware registers, virtual addr */
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|of_node
r_struct
id|device_node
op_star
id|of_node
suffix:semicolon
DECL|member|tx_desc_page
r_int
r_int
id|tx_desc_page
suffix:semicolon
multiline_comment|/* page for DMA descriptors */
DECL|member|rx_desc_page
r_int
r_int
id|rx_desc_page
suffix:semicolon
multiline_comment|/* page for DMA descriptors */
DECL|member|rxring
r_volatile
r_struct
id|gmac_dma_desc
op_star
id|rxring
suffix:semicolon
DECL|member|rx_buff
r_struct
id|sk_buff
op_star
id|rx_buff
(braket
id|NRX
)braket
suffix:semicolon
DECL|member|next_rx
r_int
id|next_rx
suffix:semicolon
DECL|member|txring
r_volatile
r_struct
id|gmac_dma_desc
op_star
id|txring
suffix:semicolon
DECL|member|tx_buff
r_struct
id|sk_buff
op_star
id|tx_buff
(braket
id|NTX
)braket
suffix:semicolon
DECL|member|next_tx
r_int
id|next_tx
suffix:semicolon
DECL|member|tx_gone
r_int
id|tx_gone
suffix:semicolon
DECL|member|phy_addr
r_int
id|phy_addr
suffix:semicolon
DECL|member|phy_id
r_int
r_int
id|phy_id
suffix:semicolon
DECL|member|phy_type
r_int
id|phy_type
suffix:semicolon
DECL|member|phy_status
r_int
id|phy_status
suffix:semicolon
multiline_comment|/* Cached PHY status */
DECL|member|full_duplex
r_int
id|full_duplex
suffix:semicolon
multiline_comment|/* Current set to full duplex */
DECL|member|gigabit
r_int
id|gigabit
suffix:semicolon
multiline_comment|/* Current set to 1000BT */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|pci_bus
id|u8
id|pci_bus
suffix:semicolon
DECL|member|pci_devfn
id|u8
id|pci_devfn
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|opened
r_int
id|opened
suffix:semicolon
DECL|member|next_gmac
r_struct
id|net_device
op_star
id|next_gmac
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Register access macros. We hope the preprocessor will be smart enough&n; * to optimize them into one single access instruction&n; */
DECL|macro|GM_OUT
mdefine_line|#define GM_OUT(reg, v)&t;&t;(((reg) &amp; REG_SZ_32) ? out_le32(gm-&gt;regs + &bslash;&n;&t;&t;&t;&t;&t;(((reg) &amp; REG_MASK)&gt;&gt;2), (v))  &bslash;&n;&t;&t;&t;&t;: (((reg) &amp; REG_SZ_16) ? out_le16((volatile u16 *) &bslash;&n;&t;&t;&t;&t;&t;(gm-&gt;regs + (((reg) &amp; REG_MASK)&gt;&gt;2)), (v))  &bslash;&n;&t;&t;&t;&t;: out_8((volatile u8 *)(gm-&gt;regs + &bslash;&n;&t;&t;&t;&t;&t;(((reg) &amp; REG_MASK)&gt;&gt;2)), (v))))
DECL|macro|GM_IN
mdefine_line|#define GM_IN(reg)&t;&t;(((reg) &amp; REG_SZ_32) ? in_le32(gm-&gt;regs + &bslash;&n;&t;&t;&t;&t;&t;(((reg) &amp; REG_MASK)&gt;&gt;2))  &bslash;&n;&t;&t;&t;&t;: (((reg) &amp; REG_SZ_16) ? in_le16((volatile u16 *) &bslash;&n;&t;&t;&t;&t;&t;(gm-&gt;regs + (((reg) &amp; REG_MASK)&gt;&gt;2)))  &bslash;&n;&t;&t;&t;&t;: in_8((volatile u8 *)(gm-&gt;regs + &bslash;&n;&t;&t;&t;&t;&t;(((reg) &amp; REG_MASK)&gt;&gt;2)))))
DECL|macro|GM_BIS
mdefine_line|#define GM_BIS(r, v)&t;&t;GM_OUT((r), GM_IN(r) | (v))
DECL|macro|GM_BIC
mdefine_line|#define GM_BIC(r, v)&t;&t;GM_OUT((r), GM_IN(r) &amp; ~(v))
multiline_comment|/* Wrapper to alloc_skb to test various alignements */
DECL|macro|GMAC_ALIGNED_RX_SKB_ADDR
mdefine_line|#define GMAC_ALIGNED_RX_SKB_ADDR(addr) &bslash;&n;        ((((unsigned long)(addr) + GMAC_BUFFER_ALIGN - 1) &amp; &bslash;&n;        ~(GMAC_BUFFER_ALIGN - 1)) - (unsigned long)(addr))
r_static
r_inline
r_struct
id|sk_buff
op_star
DECL|function|gmac_alloc_skb
id|gmac_alloc_skb
c_func
(paren
r_int
r_int
id|length
comma
r_int
id|gfp_flags
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|length
op_plus
id|GMAC_BUFFER_ALIGN
comma
id|gfp_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
r_int
id|offset
op_assign
id|GMAC_ALIGNED_RX_SKB_ADDR
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
id|skb_reserve
c_func
(paren
id|skb
comma
id|offset
)paren
suffix:semicolon
)brace
)brace
r_return
id|skb
suffix:semicolon
)brace
eof
