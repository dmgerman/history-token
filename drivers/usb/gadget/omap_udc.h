multiline_comment|/*&n; * omap_udc.h -- for omap 3.2 udc, with OTG support&n; *&n; * 2004 (C) Texas Instruments, Inc.&n; * 2004 (C) David Brownell&n; */
multiline_comment|/*&n; * USB device/endpoint management registers&n; */
DECL|macro|UDC_REG
mdefine_line|#define UDC_REG(offset)              __REG16(UDC_BASE + (offset))
DECL|macro|UDC_REV_REG
mdefine_line|#define&t;UDC_REV_REG&t;&t;&t;UDC_REG(0x0)&t;/* Revision */
DECL|macro|UDC_EP_NUM_REG
mdefine_line|#define&t;UDC_EP_NUM_REG&t;&t;&t;UDC_REG(0x4)&t;/* Which endpoint */
DECL|macro|UDC_SETUP_SEL
macro_line|#&t;define&t;UDC_SETUP_SEL&t;&t;(1 &lt;&lt; 6)
DECL|macro|UDC_EP_SEL
macro_line|#&t;define&t;UDC_EP_SEL&t;&t;(1 &lt;&lt; 5)
DECL|macro|UDC_EP_DIR
macro_line|#&t;define&t;UDC_EP_DIR&t;&t;(1 &lt;&lt; 4)
multiline_comment|/* low 4 bits for endpoint number */
DECL|macro|UDC_DATA_REG
mdefine_line|#define&t;UDC_DATA_REG&t;&t;&t;UDC_REG(0x08)&t;/* Endpoint FIFO */
DECL|macro|UDC_CTRL_REG
mdefine_line|#define&t;UDC_CTRL_REG&t;&t;&t;UDC_REG(0x0C)&t;/* Endpoint control */
DECL|macro|UDC_CLR_HALT
macro_line|#&t;define&t;UDC_CLR_HALT&t;&t;(1 &lt;&lt; 7)
DECL|macro|UDC_SET_HALT
macro_line|#&t;define&t;UDC_SET_HALT&t;&t;(1 &lt;&lt; 6)
DECL|macro|UDC_SET_FIFO_EN
macro_line|#&t;define&t;UDC_SET_FIFO_EN&t;&t;(1 &lt;&lt; 2)
DECL|macro|UDC_CLR_EP
macro_line|#&t;define&t;UDC_CLR_EP&t;&t;(1 &lt;&lt; 1)
DECL|macro|UDC_RESET_EP
macro_line|#&t;define&t;UDC_RESET_EP&t;&t;(1 &lt;&lt; 0)
DECL|macro|UDC_STAT_FLG_REG
mdefine_line|#define&t;UDC_STAT_FLG_REG&t;&t;UDC_REG(0x10)&t;/* Endpoint status */
DECL|macro|UDC_NO_RXPACKET
macro_line|#&t;define&t;UDC_NO_RXPACKET&t;&t;(1 &lt;&lt; 15)
DECL|macro|UDC_MISS_IN
macro_line|#&t;define&t;UDC_MISS_IN&t;&t;(1 &lt;&lt; 14)
DECL|macro|UDC_DATA_FLUSH
macro_line|#&t;define&t;UDC_DATA_FLUSH&t;&t;(1 &lt;&lt; 13)
DECL|macro|UDC_ISO_ERR
macro_line|#&t;define&t;UDC_ISO_ERR&t;&t;(1 &lt;&lt; 12)
DECL|macro|UDC_ISO_FIFO_EMPTY
macro_line|#&t;define&t;UDC_ISO_FIFO_EMPTY&t;(1 &lt;&lt; 9)
DECL|macro|UDC_ISO_FIFO_FULL
macro_line|#&t;define&t;UDC_ISO_FIFO_FULL&t;(1 &lt;&lt; 8)
DECL|macro|UDC_EP_HALTED
macro_line|#&t;define&t;UDC_EP_HALTED&t;&t;(1 &lt;&lt; 6)
DECL|macro|UDC_STALL
macro_line|#&t;define&t;UDC_STALL&t;&t;(1 &lt;&lt; 5)
DECL|macro|UDC_NAK
macro_line|#&t;define&t;UDC_NAK&t;&t;&t;(1 &lt;&lt; 4)
DECL|macro|UDC_ACK
macro_line|#&t;define&t;UDC_ACK&t;&t;&t;(1 &lt;&lt; 3)
DECL|macro|UDC_FIFO_EN
macro_line|#&t;define&t;UDC_FIFO_EN&t;&t;(1 &lt;&lt; 2)
DECL|macro|UDC_NON_ISO_FIFO_EMPTY
macro_line|#&t;define&t;UDC_NON_ISO_FIFO_EMPTY&t;(1 &lt;&lt; 1)
DECL|macro|UDC_NON_ISO_FIFO_FULL
macro_line|#&t;define&t;UDC_NON_ISO_FIFO_FULL&t;(1 &lt;&lt; 0)
DECL|macro|UDC_RXFSTAT_REG
mdefine_line|#define&t;UDC_RXFSTAT_REG&t;&t;&t;UDC_REG(0x14)&t;/* OUT bytecount */
DECL|macro|UDC_SYSCON1_REG
mdefine_line|#define&t;UDC_SYSCON1_REG&t;&t;&t;UDC_REG(0x18)&t;/* System config 1 */
DECL|macro|UDC_CFG_LOCK
macro_line|#&t;define&t;UDC_CFG_LOCK&t;&t;(1 &lt;&lt; 8)
DECL|macro|UDC_DATA_ENDIAN
macro_line|#&t;define&t;UDC_DATA_ENDIAN&t;&t;(1 &lt;&lt; 7)
DECL|macro|UDC_DMA_ENDIAN
macro_line|#&t;define&t;UDC_DMA_ENDIAN&t;&t;(1 &lt;&lt; 6)
DECL|macro|UDC_NAK_EN
macro_line|#&t;define&t;UDC_NAK_EN&t;&t;(1 &lt;&lt; 4)
DECL|macro|UDC_AUTODECODE_DIS
macro_line|#&t;define&t;UDC_AUTODECODE_DIS&t;(1 &lt;&lt; 3)
DECL|macro|UDC_SELF_PWR
macro_line|#&t;define&t;UDC_SELF_PWR&t;&t;(1 &lt;&lt; 2)
DECL|macro|UDC_SOFF_DIS
macro_line|#&t;define&t;UDC_SOFF_DIS&t;&t;(1 &lt;&lt; 1)
DECL|macro|UDC_PULLUP_EN
macro_line|#&t;define&t;UDC_PULLUP_EN&t;&t;(1 &lt;&lt; 0)
DECL|macro|UDC_SYSCON2_REG
mdefine_line|#define&t;UDC_SYSCON2_REG&t;&t;&t;UDC_REG(0x1C)&t;/* System config 2 */
DECL|macro|UDC_RMT_WKP
macro_line|#&t;define&t;UDC_RMT_WKP&t;&t;(1 &lt;&lt; 6)
DECL|macro|UDC_STALL_CMD
macro_line|#&t;define&t;UDC_STALL_CMD&t;&t;(1 &lt;&lt; 5)
DECL|macro|UDC_DEV_CFG
macro_line|#&t;define&t;UDC_DEV_CFG&t;&t;(1 &lt;&lt; 3)
DECL|macro|UDC_CLR_CFG
macro_line|#&t;define&t;UDC_CLR_CFG&t;&t;(1 &lt;&lt; 2)
DECL|macro|UDC_DEVSTAT_REG
mdefine_line|#define&t;UDC_DEVSTAT_REG&t;&t;&t;UDC_REG(0x20)&t;/* Device status */
DECL|macro|UDC_B_HNP_ENABLE
macro_line|#&t;define&t;UDC_B_HNP_ENABLE&t;(1 &lt;&lt; 9)
DECL|macro|UDC_A_HNP_SUPPORT
macro_line|#&t;define&t;UDC_A_HNP_SUPPORT&t;(1 &lt;&lt; 8)
DECL|macro|UDC_A_ALT_HNP_SUPPORT
macro_line|#&t;define&t;UDC_A_ALT_HNP_SUPPORT&t;(1 &lt;&lt; 7)
DECL|macro|UDC_R_WK_OK
macro_line|#&t;define&t;UDC_R_WK_OK&t;&t;(1 &lt;&lt; 6)
DECL|macro|UDC_USB_RESET
macro_line|#&t;define&t;UDC_USB_RESET&t;&t;(1 &lt;&lt; 5)
DECL|macro|UDC_SUS
macro_line|#&t;define&t;UDC_SUS&t;&t;&t;(1 &lt;&lt; 4)
DECL|macro|UDC_CFG
macro_line|#&t;define&t;UDC_CFG&t;&t;&t;(1 &lt;&lt; 3)
DECL|macro|UDC_ADD
macro_line|#&t;define&t;UDC_ADD&t;&t;&t;(1 &lt;&lt; 2)
DECL|macro|UDC_DEF
macro_line|#&t;define&t;UDC_DEF&t;&t;&t;(1 &lt;&lt; 1)
DECL|macro|UDC_ATT
macro_line|#&t;define&t;UDC_ATT&t;&t;&t;(1 &lt;&lt; 0)
DECL|macro|UDC_SOF_REG
mdefine_line|#define&t;UDC_SOF_REG&t;&t;&t;UDC_REG(0x24)&t;/* Start of frame */
DECL|macro|UDC_FT_LOCK
macro_line|#&t;define&t;UDC_FT_LOCK&t;&t;(1 &lt;&lt; 12)
DECL|macro|UDC_TS_OK
macro_line|#&t;define&t;UDC_TS_OK&t;&t;(1 &lt;&lt; 11)
DECL|macro|UDC_TS
macro_line|#&t;define&t;UDC_TS&t;&t;&t;0x03ff
DECL|macro|UDC_IRQ_EN_REG
mdefine_line|#define&t;UDC_IRQ_EN_REG&t;&t;&t;UDC_REG(0x28)&t;/* Interrupt enable */
DECL|macro|UDC_SOF_IE
macro_line|#&t;define&t;UDC_SOF_IE&t;&t;(1 &lt;&lt; 7)
DECL|macro|UDC_EPN_RX_IE
macro_line|#&t;define&t;UDC_EPN_RX_IE&t;&t;(1 &lt;&lt; 5)
DECL|macro|UDC_EPN_TX_IE
macro_line|#&t;define&t;UDC_EPN_TX_IE&t;&t;(1 &lt;&lt; 4)
DECL|macro|UDC_DS_CHG_IE
macro_line|#&t;define&t;UDC_DS_CHG_IE&t;&t;(1 &lt;&lt; 3)
DECL|macro|UDC_EP0_IE
macro_line|#&t;define&t;UDC_EP0_IE&t;&t;(1 &lt;&lt; 0)
DECL|macro|UDC_DMA_IRQ_EN_REG
mdefine_line|#define&t;UDC_DMA_IRQ_EN_REG&t;&t;UDC_REG(0x2C)&t;/* DMA irq enable */
multiline_comment|/* rx/tx dma channels numbered 1-3 not 0-2 */
DECL|macro|UDC_TX_DONE_IE
macro_line|#&t;define&t;UDC_TX_DONE_IE(n)&t;(1 &lt;&lt; (4 * (n) - 2))
DECL|macro|UDC_RX_CNT_IE
macro_line|#&t;define&t;UDC_RX_CNT_IE(n)&t;(1 &lt;&lt; (4 * (n) - 3))
DECL|macro|UDC_RX_EOT_IE
macro_line|#&t;define&t;UDC_RX_EOT_IE(n)&t;(1 &lt;&lt; (4 * (n) - 4))
DECL|macro|UDC_IRQ_SRC_REG
mdefine_line|#define&t;UDC_IRQ_SRC_REG&t;&t;&t;UDC_REG(0x30)&t;/* Interrupt source */
DECL|macro|UDC_TXN_DONE
macro_line|#&t;define&t;UDC_TXN_DONE&t;&t;(1 &lt;&lt; 10)
DECL|macro|UDC_RXN_CNT
macro_line|#&t;define&t;UDC_RXN_CNT&t;&t;(1 &lt;&lt; 9)
DECL|macro|UDC_RXN_EOT
macro_line|#&t;define&t;UDC_RXN_EOT&t;&t;(1 &lt;&lt; 8)
DECL|macro|UDC_SOF
macro_line|#&t;define&t;UDC_SOF&t;&t;&t;(1 &lt;&lt; 7)
DECL|macro|UDC_EPN_RX
macro_line|#&t;define&t;UDC_EPN_RX&t;&t;(1 &lt;&lt; 5)
DECL|macro|UDC_EPN_TX
macro_line|#&t;define&t;UDC_EPN_TX&t;&t;(1 &lt;&lt; 4)
DECL|macro|UDC_DS_CHG
macro_line|#&t;define&t;UDC_DS_CHG&t;&t;(1 &lt;&lt; 3)
DECL|macro|UDC_SETUP
macro_line|#&t;define&t;UDC_SETUP&t;&t;(1 &lt;&lt; 2)
DECL|macro|UDC_EP0_RX
macro_line|#&t;define&t;UDC_EP0_RX&t;&t;(1 &lt;&lt; 1)
DECL|macro|UDC_EP0_TX
macro_line|#&t;define&t;UDC_EP0_TX&t;&t;(1 &lt;&lt; 0)
DECL|macro|UDC_IRQ_SRC_MASK
macro_line|#&t;define&t;UDC_IRQ_SRC_MASK&t;0x7bf
DECL|macro|UDC_EPN_STAT_REG
mdefine_line|#define&t;UDC_EPN_STAT_REG&t;&t;UDC_REG(0x34)&t;/* EP irq status */
DECL|macro|UDC_DMAN_STAT_REG
mdefine_line|#define&t;UDC_DMAN_STAT_REG&t;&t;UDC_REG(0x38)&t;/* DMA irq status */
DECL|macro|UDC_DMA_RX_SB
macro_line|#&t;define&t;UDC_DMA_RX_SB&t;&t;(1 &lt;&lt; 12)
DECL|macro|UDC_DMA_RX_SRC
macro_line|#&t;define&t;UDC_DMA_RX_SRC(x)&t;(((x)&gt;&gt;8) &amp; 0xf)
DECL|macro|UDC_DMA_TX_SRC
macro_line|#&t;define&t;UDC_DMA_TX_SRC(x)&t;(((x)&gt;&gt;0) &amp; 0xf)
multiline_comment|/* DMA configuration registers:  up to three channels in each direction.  */
DECL|macro|UDC_RXDMA_CFG_REG
mdefine_line|#define&t;UDC_RXDMA_CFG_REG&t;&t;UDC_REG(0x40)&t;/* 3 eps for RX DMA */
DECL|macro|UDC_TXDMA_CFG_REG
mdefine_line|#define&t;UDC_TXDMA_CFG_REG&t;&t;UDC_REG(0x44)&t;/* 3 eps for TX DMA */
DECL|macro|UDC_DATA_DMA_REG
mdefine_line|#define&t;UDC_DATA_DMA_REG&t;&t;UDC_REG(0x48)&t;/* rx/tx fifo addr */
multiline_comment|/* rx/tx dma control, numbering channels 1-3 not 0-2 */
DECL|macro|UDC_TXDMA_REG
mdefine_line|#define&t;UDC_TXDMA_REG(chan)&t;&t;UDC_REG(0x50 - 4 + 4 * (chan))
DECL|macro|UDC_TXN_EOT
macro_line|#&t;define UDC_TXN_EOT&t;&t;(1 &lt;&lt; 15)&t;/* bytes vs packets */
DECL|macro|UDC_TXN_START
macro_line|#&t;define UDC_TXN_START&t;&t;(1 &lt;&lt; 14)&t;/* start transfer */
DECL|macro|UDC_TXN_TSC
macro_line|#&t;define UDC_TXN_TSC&t;&t;0x03ff&t;&t;/* units in xfer */
DECL|macro|UDC_RXDMA_REG
mdefine_line|#define&t;UDC_RXDMA_REG(chan)&t;&t;UDC_REG(0x60 - 4 + 4 * (chan))
DECL|macro|UDC_RXN_STOP
macro_line|#&t;define UDC_RXN_STOP&t;&t;(1 &lt;&lt; 15)&t;/* enable EOT irq */
DECL|macro|UDC_RXN_TC
macro_line|#&t;define UDC_RXN_TC&t;&t;0x00ff&t;&t;/* packets in xfer */
multiline_comment|/*&n; * Endpoint configuration registers (used before CFG_LOCK is set)&n; * UDC_EP_TX_REG(0) is unused&n; */
DECL|macro|UDC_EP_RX_REG
mdefine_line|#define&t;UDC_EP_RX_REG(endpoint)&t;&t;UDC_REG(0x80 + (endpoint)*4)
DECL|macro|UDC_EPN_RX_VALID
macro_line|#&t;define&t;UDC_EPN_RX_VALID&t;(1 &lt;&lt; 15)
DECL|macro|UDC_EPN_RX_DB
macro_line|#&t;define&t;UDC_EPN_RX_DB&t;&t;(1 &lt;&lt; 14)
multiline_comment|/* buffer size in bits 13, 12 */
DECL|macro|UDC_EPN_RX_ISO
macro_line|#&t;define&t;UDC_EPN_RX_ISO&t;&t;(1 &lt;&lt; 11)
multiline_comment|/* buffer pointer in low 11 bits */
DECL|macro|UDC_EP_TX_REG
mdefine_line|#define&t;UDC_EP_TX_REG(endpoint)&t;&t;UDC_REG(0xc0 + (endpoint)*4)
multiline_comment|/* same bitfields as in RX_REG */
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|struct|omap_req
r_struct
id|omap_req
(brace
DECL|member|req
r_struct
id|usb_request
id|req
suffix:semicolon
DECL|member|queue
r_struct
id|list_head
id|queue
suffix:semicolon
DECL|member|dma_bytes
r_int
id|dma_bytes
suffix:semicolon
DECL|member|mapped
r_int
id|mapped
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|omap_ep
r_struct
id|omap_ep
(brace
DECL|member|ep
r_struct
id|usb_ep
id|ep
suffix:semicolon
DECL|member|queue
r_struct
id|list_head
id|queue
suffix:semicolon
DECL|member|irqs
r_int
r_int
id|irqs
suffix:semicolon
DECL|member|iso
r_struct
id|list_head
id|iso
suffix:semicolon
DECL|member|desc
r_const
r_struct
id|usb_endpoint_descriptor
op_star
id|desc
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|14
)braket
suffix:semicolon
DECL|member|maxpacket
id|u16
id|maxpacket
suffix:semicolon
DECL|member|bEndpointAddress
id|u8
id|bEndpointAddress
suffix:semicolon
DECL|member|bmAttributes
id|u8
id|bmAttributes
suffix:semicolon
DECL|member|double_buf
r_int
id|double_buf
suffix:colon
l_int|1
suffix:semicolon
DECL|member|stopped
r_int
id|stopped
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fnf
r_int
id|fnf
suffix:colon
l_int|1
suffix:semicolon
DECL|member|has_dma
r_int
id|has_dma
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ackwait
id|u8
id|ackwait
suffix:semicolon
DECL|member|dma_channel
id|u8
id|dma_channel
suffix:semicolon
DECL|member|dma_counter
id|u16
id|dma_counter
suffix:semicolon
DECL|member|lch
r_int
id|lch
suffix:semicolon
DECL|member|udc
r_struct
id|omap_udc
op_star
id|udc
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|omap_udc
r_struct
id|omap_udc
(brace
DECL|member|gadget
r_struct
id|usb_gadget
id|gadget
suffix:semicolon
DECL|member|driver
r_struct
id|usb_gadget_driver
op_star
id|driver
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|ep
r_struct
id|omap_ep
id|ep
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|devstat
id|u16
id|devstat
suffix:semicolon
DECL|member|transceiver
r_struct
id|otg_transceiver
op_star
id|transceiver
suffix:semicolon
DECL|member|iso
r_struct
id|list_head
id|iso
suffix:semicolon
DECL|member|softconnect
r_int
id|softconnect
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vbus_active
r_int
id|vbus_active
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ep0_pending
r_int
id|ep0_pending
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ep0_in
r_int
id|ep0_in
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ep0_set_config
r_int
id|ep0_set_config
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ep0_reset_config
r_int
id|ep0_reset_config
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ep0_setup
r_int
id|ep0_setup
suffix:colon
l_int|1
suffix:semicolon
DECL|member|done
r_struct
id|completion
op_star
id|done
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(stuff...)&t;&t;printk(KERN_DEBUG &quot;udc: &quot; stuff)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(stuff...)&t;&t;do{}while(0)
macro_line|#endif
macro_line|#ifdef VERBOSE
DECL|macro|VDBG
macro_line|#    define VDBG&t;&t;DBG
macro_line|#else
DECL|macro|VDBG
macro_line|#    define VDBG(stuff...)&t;do{}while(0)
macro_line|#endif
DECL|macro|ERR
mdefine_line|#define ERR(stuff...)&t;&t;printk(KERN_ERR &quot;udc: &quot; stuff)
DECL|macro|WARN
mdefine_line|#define WARN(stuff...)&t;&t;printk(KERN_WARNING &quot;udc: &quot; stuff)
DECL|macro|INFO
mdefine_line|#define INFO(stuff...)&t;&t;printk(KERN_INFO &quot;udc: &quot; stuff)
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|macro|MOD_CONF_CTRL_0_REG
mdefine_line|#define&t;MOD_CONF_CTRL_0_REG&t;__REG32(MOD_CONF_CTRL_0)
DECL|macro|VBUS_W2FC_1510
mdefine_line|#define&t;VBUS_W2FC_1510&t;&t;(1 &lt;&lt; 17)&t;/* 0 gpio0, 1 dvdd2 pin */
DECL|macro|FUNC_MUX_CTRL_0_REG
mdefine_line|#define&t;FUNC_MUX_CTRL_0_REG&t;__REG32(FUNC_MUX_CTRL_0)
DECL|macro|VBUS_CTRL_1510
mdefine_line|#define&t;VBUS_CTRL_1510&t;&t;(1 &lt;&lt; 19)&t;/* 1 connected (software) */
DECL|macro|VBUS_MODE_1510
mdefine_line|#define&t;VBUS_MODE_1510&t;&t;(1 &lt;&lt; 18)&t;/* 0 hardware, 1 software */
DECL|macro|HMC_1510
mdefine_line|#define&t;HMC_1510&t;((MOD_CONF_CTRL_0_REG &gt;&gt; 1) &amp; 0x3f)
DECL|macro|HMC_1610
mdefine_line|#define&t;HMC_1610&t;(OTG_SYSCON_2_REG &amp; 0x3f)
DECL|macro|HMC
mdefine_line|#define&t;HMC&t;&t;(cpu_is_omap15xx() ? HMC_1510 : HMC_1610)
eof
