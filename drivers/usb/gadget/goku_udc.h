multiline_comment|/*&n; * Toshiba TC86C001 (&quot;Goku-S&quot;) USB Device Controller driver&n; *&n; * Copyright (C) 2000-2002 Lineo&n; *      by Stuart Lynne, Tom Rushworth, and Bruce Balden&n; * Copyright (C) 2002 Toshiba Corporation&n; * Copyright (C) 2003 MontaVista Software (source@mvista.com)&n; *&n; * This file is licensed under the terms of the GNU General Public&n; * License version 2.  This program is licensed &quot;as is&quot; without any&n; * warranty of any kind, whether express or implied.&n; */
multiline_comment|/*&n; * PCI BAR 0 points to these registers.&n; */
DECL|struct|goku_udc_regs
r_struct
id|goku_udc_regs
(brace
multiline_comment|/* irq management */
DECL|member|int_status
id|u32
id|int_status
suffix:semicolon
multiline_comment|/* 0x000 */
DECL|member|int_enable
id|u32
id|int_enable
suffix:semicolon
DECL|macro|INT_SUSPEND
mdefine_line|#define INT_SUSPEND&t;&t;0x00001&t;&t;/* or resume */
DECL|macro|INT_USBRESET
mdefine_line|#define INT_USBRESET&t;&t;0x00002
DECL|macro|INT_ENDPOINT0
mdefine_line|#define INT_ENDPOINT0&t;&t;0x00004
DECL|macro|INT_SETUP
mdefine_line|#define INT_SETUP&t;&t;0x00008
DECL|macro|INT_STATUS
mdefine_line|#define INT_STATUS&t;&t;0x00010
DECL|macro|INT_STATUSNAK
mdefine_line|#define INT_STATUSNAK&t;&t;0x00020
DECL|macro|INT_EPxDATASET
mdefine_line|#define INT_EPxDATASET(n)&t;(0x00020 &lt;&lt; (n))&t;/* 0 &lt; n &lt; 4 */
DECL|macro|INT_EP1DATASET
macro_line|#&t;define INT_EP1DATASET&t;&t;0x00040
DECL|macro|INT_EP2DATASET
macro_line|#&t;define INT_EP2DATASET&t;&t;0x00080
DECL|macro|INT_EP3DATASET
macro_line|#&t;define INT_EP3DATASET&t;&t;0x00100
DECL|macro|INT_EPnNAK
mdefine_line|#define INT_EPnNAK(n)&t;&t;(0x00100 &lt; (n))&t;&t;/* 0 &lt; n &lt; 4 */
DECL|macro|INT_EP1NAK
macro_line|#&t;define INT_EP1NAK&t;&t;0x00200
DECL|macro|INT_EP2NAK
macro_line|#&t;define INT_EP2NAK&t;&t;0x00400
DECL|macro|INT_EP3NAK
macro_line|#&t;define INT_EP3NAK&t;&t;0x00800
DECL|macro|INT_SOF
mdefine_line|#define INT_SOF&t;&t;&t;0x01000
DECL|macro|INT_ERR
mdefine_line|#define INT_ERR&t;&t;&t;0x02000
DECL|macro|INT_MSTWRSET
mdefine_line|#define INT_MSTWRSET&t;&t;0x04000
DECL|macro|INT_MSTWREND
mdefine_line|#define INT_MSTWREND&t;&t;0x08000
DECL|macro|INT_MSTWRTMOUT
mdefine_line|#define INT_MSTWRTMOUT&t;&t;0x10000
DECL|macro|INT_MSTRDEND
mdefine_line|#define INT_MSTRDEND&t;&t;0x20000
DECL|macro|INT_SYSERROR
mdefine_line|#define INT_SYSERROR&t;&t;0x40000
DECL|macro|INT_PWRDETECT
mdefine_line|#define INT_PWRDETECT&t;&t;0x80000
DECL|macro|INT_DEVWIDE
mdefine_line|#define&t;INT_DEVWIDE&t;&t;(INT_PWRDETECT|INT_SYSERROR/*|INT_ERR*/|INT_USBRESET|INT_SUSPEND)
DECL|macro|INT_EP0
mdefine_line|#define&t;INT_EP0 &t;&t;(INT_SETUP|INT_ENDPOINT0/*|INT_STATUS*/|INT_STATUSNAK)
DECL|member|dma_master
id|u32
id|dma_master
suffix:semicolon
DECL|macro|MST_EOPB_DIS
mdefine_line|#define MST_EOPB_DIS&t;&t;0x0800
DECL|macro|MST_EOPB_ENA
mdefine_line|#define MST_EOPB_ENA&t;&t;0x0400
DECL|macro|MST_TIMEOUT_DIS
mdefine_line|#define MST_TIMEOUT_DIS&t;&t;0x0200
DECL|macro|MST_TIMEOUT_ENA
mdefine_line|#define MST_TIMEOUT_ENA&t;&t;0x0100
DECL|macro|MST_RD_EOPB
mdefine_line|#define MST_RD_EOPB&t;&t;0x0080&t;&t;/* write-only */
DECL|macro|MST_RD_RESET
mdefine_line|#define MST_RD_RESET&t;&t;0x0040
DECL|macro|MST_WR_RESET
mdefine_line|#define MST_WR_RESET&t;&t;0x0020
DECL|macro|MST_RD_ENA
mdefine_line|#define MST_RD_ENA&t;&t;0x0004&t;&t;/* 1:start, 0:ignore */
DECL|macro|MST_WR_ENA
mdefine_line|#define MST_WR_ENA&t;&t;0x0002&t;&t;/* 1:start, 0:ignore */
DECL|macro|MST_CONNECTION
mdefine_line|#define MST_CONNECTION&t;&t;0x0001&t;&t;/* 0 for ep1out/ep2in */
DECL|macro|MST_R_BITS
mdefine_line|#define MST_R_BITS&t;&t;(MST_EOPB_DIS|MST_EOPB_ENA &bslash;&n;&t;&t;&t;&t;&t;|MST_RD_ENA|MST_RD_RESET)
DECL|macro|MST_W_BITS
mdefine_line|#define MST_W_BITS&t;&t;(MST_TIMEOUT_DIS|MST_TIMEOUT_ENA &bslash;&n;&t;&t;&t;&t;&t;|MST_WR_ENA|MST_WR_RESET)
DECL|macro|MST_RW_BITS
mdefine_line|#define MST_RW_BITS&t;&t;(MST_R_BITS|MST_W_BITS &bslash;&n;&t;&t;&t;&t;&t;|MST_CONNECTION)
multiline_comment|/* these values assume (dma_master &amp; MST_CONNECTION) == 0 */
DECL|macro|UDC_MSTWR_ENDPOINT
mdefine_line|#define UDC_MSTWR_ENDPOINT        1
DECL|macro|UDC_MSTRD_ENDPOINT
mdefine_line|#define UDC_MSTRD_ENDPOINT        2
multiline_comment|/* dma master write */
DECL|member|out_dma_start
id|u32
id|out_dma_start
suffix:semicolon
DECL|member|out_dma_end
id|u32
id|out_dma_end
suffix:semicolon
DECL|member|out_dma_current
id|u32
id|out_dma_current
suffix:semicolon
multiline_comment|/* dma master read */
DECL|member|in_dma_start
id|u32
id|in_dma_start
suffix:semicolon
DECL|member|in_dma_end
id|u32
id|in_dma_end
suffix:semicolon
DECL|member|in_dma_current
id|u32
id|in_dma_current
suffix:semicolon
DECL|member|power_detect
id|u32
id|power_detect
suffix:semicolon
DECL|macro|PW_DETECT
mdefine_line|#define PW_DETECT&t;&t;0x04
DECL|macro|PW_RESETB
mdefine_line|#define PW_RESETB&t;&t;0x02
DECL|macro|PW_PULLUP
mdefine_line|#define PW_PULLUP&t;&t;0x01
DECL|member|_reserved0
id|u8
id|_reserved0
(braket
l_int|0x1d8
)braket
suffix:semicolon
multiline_comment|/* endpoint registers */
DECL|member|ep_fifo
id|u32
id|ep_fifo
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x200 */
DECL|member|_reserved1
id|u8
id|_reserved1
(braket
l_int|0x10
)braket
suffix:semicolon
DECL|member|ep_mode
id|u32
id|ep_mode
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* only 1-3 valid */
DECL|member|_reserved2
id|u8
id|_reserved2
(braket
l_int|0x10
)braket
suffix:semicolon
DECL|member|ep_status
id|u32
id|ep_status
(braket
l_int|4
)braket
suffix:semicolon
DECL|macro|EPxSTATUS_TOGGLE
mdefine_line|#define EPxSTATUS_TOGGLE&t;0x40
DECL|macro|EPxSTATUS_SUSPEND
mdefine_line|#define EPxSTATUS_SUSPEND&t;0x20
DECL|macro|EPxSTATUS_EP_MASK
mdefine_line|#define EPxSTATUS_EP_MASK&t;(0x07&lt;&lt;2)
DECL|macro|EPxSTATUS_EP_READY
macro_line|#&t;define EPxSTATUS_EP_READY&t;(0&lt;&lt;2)
DECL|macro|EPxSTATUS_EP_DATAIN
macro_line|#&t;define EPxSTATUS_EP_DATAIN&t;(1&lt;&lt;2)
DECL|macro|EPxSTATUS_EP_FULL
macro_line|#&t;define EPxSTATUS_EP_FULL&t;(2&lt;&lt;2)
DECL|macro|EPxSTATUS_EP_TX_ERR
macro_line|#&t;define EPxSTATUS_EP_TX_ERR&t;(3&lt;&lt;2)
DECL|macro|EPxSTATUS_EP_RX_ERR
macro_line|#&t;define EPxSTATUS_EP_RX_ERR&t;(4&lt;&lt;2)
DECL|macro|EPxSTATUS_EP_BUSY
macro_line|#&t;define EPxSTATUS_EP_BUSY&t;(5&lt;&lt;2)
DECL|macro|EPxSTATUS_EP_STALL
macro_line|#&t;define EPxSTATUS_EP_STALL&t;(6&lt;&lt;2)
DECL|macro|EPxSTATUS_EP_INVALID
macro_line|#&t;define EPxSTATUS_EP_INVALID&t;(7&lt;&lt;2)
DECL|macro|EPxSTATUS_FIFO_DISABLE
mdefine_line|#define EPxSTATUS_FIFO_DISABLE&t;0x02
DECL|macro|EPxSTATUS_STAGE_ERROR
mdefine_line|#define EPxSTATUS_STAGE_ERROR&t;0x01
DECL|member|_reserved3
id|u8
id|_reserved3
(braket
l_int|0x10
)braket
suffix:semicolon
DECL|member|EPxSizeLA
id|u32
id|EPxSizeLA
(braket
l_int|4
)braket
suffix:semicolon
DECL|macro|PACKET_ACTIVE
mdefine_line|#define PACKET_ACTIVE&t;&t;(1&lt;&lt;7)
DECL|macro|DATASIZE
mdefine_line|#define DATASIZE&t;&t;0x7f
DECL|member|_reserved3a
id|u8
id|_reserved3a
(braket
l_int|0x10
)braket
suffix:semicolon
DECL|member|EPxSizeLB
id|u32
id|EPxSizeLB
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* only 1,2 valid */
DECL|member|_reserved3b
id|u8
id|_reserved3b
(braket
l_int|0x10
)braket
suffix:semicolon
DECL|member|EPxSizeHA
id|u32
id|EPxSizeHA
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* only 1-3 valid */
DECL|member|_reserved3c
id|u8
id|_reserved3c
(braket
l_int|0x10
)braket
suffix:semicolon
DECL|member|EPxSizeHB
id|u32
id|EPxSizeHB
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* only 1,2 valid */
DECL|member|_reserved4
id|u8
id|_reserved4
(braket
l_int|0x30
)braket
suffix:semicolon
multiline_comment|/* SETUP packet contents */
DECL|member|bRequestType
id|u32
id|bRequestType
suffix:semicolon
multiline_comment|/* 0x300 */
DECL|member|bRequest
id|u32
id|bRequest
suffix:semicolon
DECL|member|wValueL
id|u32
id|wValueL
suffix:semicolon
DECL|member|wValueH
id|u32
id|wValueH
suffix:semicolon
DECL|member|wIndexL
id|u32
id|wIndexL
suffix:semicolon
DECL|member|wIndexH
id|u32
id|wIndexH
suffix:semicolon
DECL|member|wLengthL
id|u32
id|wLengthL
suffix:semicolon
DECL|member|wLengthH
id|u32
id|wLengthH
suffix:semicolon
multiline_comment|/* command interaction/handshaking */
DECL|member|SetupRecv
id|u32
id|SetupRecv
suffix:semicolon
multiline_comment|/* 0x320 */
DECL|member|CurrConfig
id|u32
id|CurrConfig
suffix:semicolon
DECL|member|StdRequest
id|u32
id|StdRequest
suffix:semicolon
DECL|member|Request
id|u32
id|Request
suffix:semicolon
DECL|member|DataSet
id|u32
id|DataSet
suffix:semicolon
DECL|macro|DATASET_A
mdefine_line|#define DATASET_A(epnum)&t;(1&lt;&lt;(2*(epnum)))
DECL|macro|DATASET_B
mdefine_line|#define DATASET_B(epnum)&t;(2&lt;&lt;(2*(epnum)))
DECL|macro|DATASET_AB
mdefine_line|#define DATASET_AB(epnum)&t;(3&lt;&lt;(2*(epnum)))
DECL|member|_reserved5
id|u8
id|_reserved5
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|UsbState
id|u32
id|UsbState
suffix:semicolon
DECL|macro|USBSTATE_CONFIGURED
mdefine_line|#define USBSTATE_CONFIGURED&t;0x04
DECL|macro|USBSTATE_ADDRESSED
mdefine_line|#define USBSTATE_ADDRESSED&t;0x02
DECL|macro|USBSTATE_DEFAULT
mdefine_line|#define USBSTATE_DEFAULT&t;0x01
DECL|member|EOP
id|u32
id|EOP
suffix:semicolon
DECL|member|Command
id|u32
id|Command
suffix:semicolon
multiline_comment|/* 0x340 */
DECL|macro|COMMAND_SETDATA0
mdefine_line|#define COMMAND_SETDATA0&t;2
DECL|macro|COMMAND_RESET
mdefine_line|#define COMMAND_RESET&t;&t;3
DECL|macro|COMMAND_STALL
mdefine_line|#define COMMAND_STALL&t;&t;4
DECL|macro|COMMAND_INVALID
mdefine_line|#define COMMAND_INVALID&t;&t;5
DECL|macro|COMMAND_FIFO_DISABLE
mdefine_line|#define COMMAND_FIFO_DISABLE&t;7
DECL|macro|COMMAND_FIFO_ENABLE
mdefine_line|#define COMMAND_FIFO_ENABLE&t;8
DECL|macro|COMMAND_INIT_DESCRIPTOR
mdefine_line|#define COMMAND_INIT_DESCRIPTOR&t;9
DECL|macro|COMMAND_FIFO_CLEAR
mdefine_line|#define COMMAND_FIFO_CLEAR&t;10&t;/* also stall */
DECL|macro|COMMAND_STALL_CLEAR
mdefine_line|#define COMMAND_STALL_CLEAR&t;11
DECL|macro|COMMAND_EP
mdefine_line|#define COMMAND_EP(n)&t;&t;((n) &lt;&lt; 4)
DECL|member|EPxSingle
id|u32
id|EPxSingle
suffix:semicolon
DECL|member|_reserved6
id|u8
id|_reserved6
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|EPxBCS
id|u32
id|EPxBCS
suffix:semicolon
DECL|member|_reserved7
id|u8
id|_reserved7
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|IntControl
id|u32
id|IntControl
suffix:semicolon
DECL|macro|ICONTROL_STATUSNAK
mdefine_line|#define ICONTROL_STATUSNAK&t;1
DECL|member|_reserved8
id|u8
id|_reserved8
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|reqmode
id|u32
id|reqmode
suffix:semicolon
singleline_comment|// 0x360 standard request mode, low 8 bits
DECL|macro|G_REQMODE_SET_INTF
mdefine_line|#define G_REQMODE_SET_INTF&t;(1&lt;&lt;7)
DECL|macro|G_REQMODE_GET_INTF
mdefine_line|#define G_REQMODE_GET_INTF&t;(1&lt;&lt;6)
DECL|macro|G_REQMODE_SET_CONF
mdefine_line|#define G_REQMODE_SET_CONF&t;(1&lt;&lt;5)
DECL|macro|G_REQMODE_GET_CONF
mdefine_line|#define G_REQMODE_GET_CONF&t;(1&lt;&lt;4)
DECL|macro|G_REQMODE_GET_DESC
mdefine_line|#define G_REQMODE_GET_DESC&t;(1&lt;&lt;3)
DECL|macro|G_REQMODE_SET_FEAT
mdefine_line|#define G_REQMODE_SET_FEAT&t;(1&lt;&lt;2)
DECL|macro|G_REQMODE_CLEAR_FEAT
mdefine_line|#define G_REQMODE_CLEAR_FEAT&t;(1&lt;&lt;1)
DECL|macro|G_REQMODE_GET_STATUS
mdefine_line|#define G_REQMODE_GET_STATUS&t;(1&lt;&lt;0)
DECL|member|ReqMode
id|u32
id|ReqMode
suffix:semicolon
DECL|member|_reserved9
id|u8
id|_reserved9
(braket
l_int|0x18
)braket
suffix:semicolon
DECL|member|PortStatus
id|u32
id|PortStatus
suffix:semicolon
multiline_comment|/* 0x380 */
DECL|member|_reserved10
id|u8
id|_reserved10
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|member|buff_test
id|u32
id|buff_test
suffix:semicolon
DECL|member|_reserved11
id|u8
id|_reserved11
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|UsbReady
id|u32
id|UsbReady
suffix:semicolon
DECL|member|_reserved12
id|u8
id|_reserved12
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|SetDescStall
id|u32
id|SetDescStall
suffix:semicolon
multiline_comment|/* 0x3a0 */
DECL|member|_reserved13
id|u8
id|_reserved13
(braket
l_int|0x45c
)braket
suffix:semicolon
multiline_comment|/* hardware could handle limited GET_DESCRIPTOR duties */
DECL|macro|DESC_LEN
mdefine_line|#define&t;DESC_LEN&t;0x80
DECL|member|descriptors
id|u32
id|descriptors
(braket
id|DESC_LEN
)braket
suffix:semicolon
multiline_comment|/* 0x800 */
DECL|member|_reserved14
id|u8
id|_reserved14
(braket
l_int|0x600
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
DECL|macro|MAX_FIFO_SIZE
mdefine_line|#define&t;MAX_FIFO_SIZE&t;64
DECL|macro|MAX_EP0_SIZE
mdefine_line|#define&t;MAX_EP0_SIZE&t;8&t;&t;/* ep0 fifo is bigger, though */
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* DRIVER DATA STRUCTURES and UTILITIES */
DECL|struct|goku_ep
r_struct
id|goku_ep
(brace
DECL|member|ep
r_struct
id|usb_ep
id|ep
suffix:semicolon
DECL|member|dev
r_struct
id|goku_udc
op_star
id|dev
suffix:semicolon
DECL|member|irqs
r_int
r_int
id|irqs
suffix:semicolon
DECL|member|num
r_int
id|num
suffix:colon
l_int|8
comma
DECL|member|dma
id|dma
suffix:colon
l_int|1
comma
DECL|member|is_in
id|is_in
suffix:colon
l_int|1
comma
DECL|member|stopped
id|stopped
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* analogous to a host-side qh */
DECL|member|queue
r_struct
id|list_head
id|queue
suffix:semicolon
DECL|member|desc
r_const
r_struct
id|usb_endpoint_descriptor
op_star
id|desc
suffix:semicolon
DECL|member|reg_fifo
id|u32
id|__iomem
op_star
id|reg_fifo
suffix:semicolon
DECL|member|reg_mode
id|u32
id|__iomem
op_star
id|reg_mode
suffix:semicolon
DECL|member|reg_status
id|u32
id|__iomem
op_star
id|reg_status
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|goku_request
r_struct
id|goku_request
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
DECL|member|mapped
r_int
id|mapped
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|ep0state
r_enum
id|ep0state
(brace
DECL|enumerator|EP0_DISCONNECT
id|EP0_DISCONNECT
comma
multiline_comment|/* no host */
DECL|enumerator|EP0_IDLE
id|EP0_IDLE
comma
multiline_comment|/* between STATUS ack and SETUP report */
DECL|enumerator|EP0_IN
DECL|enumerator|EP0_OUT
id|EP0_IN
comma
id|EP0_OUT
comma
multiline_comment|/* data stage */
DECL|enumerator|EP0_STATUS
id|EP0_STATUS
comma
multiline_comment|/* status stage */
DECL|enumerator|EP0_STALL
id|EP0_STALL
comma
multiline_comment|/* data or status stages */
DECL|enumerator|EP0_SUSPEND
id|EP0_SUSPEND
comma
multiline_comment|/* usb suspend */
)brace
suffix:semicolon
DECL|struct|goku_udc
r_struct
id|goku_udc
(brace
multiline_comment|/* each pci device provides one gadget, several endpoints */
DECL|member|gadget
r_struct
id|usb_gadget
id|gadget
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|ep
r_struct
id|goku_ep
id|ep
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|driver
r_struct
id|usb_gadget_driver
op_star
id|driver
suffix:semicolon
DECL|member|ep0state
r_enum
id|ep0state
id|ep0state
suffix:semicolon
DECL|member|got_irq
r_int
id|got_irq
suffix:colon
l_int|1
comma
DECL|member|got_region
id|got_region
suffix:colon
l_int|1
comma
DECL|member|req_config
id|req_config
suffix:colon
l_int|1
comma
DECL|member|configured
id|configured
suffix:colon
l_int|1
comma
DECL|member|enabled
id|enabled
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* pci state used to access those endpoints */
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|regs
r_struct
id|goku_udc_regs
id|__iomem
op_star
id|regs
suffix:semicolon
DECL|member|int_enable
id|u32
id|int_enable
suffix:semicolon
multiline_comment|/* statistics... */
DECL|member|irqs
r_int
r_int
id|irqs
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|macro|xprintk
mdefine_line|#define xprintk(dev,level,fmt,args...) &bslash;&n;&t;printk(level &quot;%s %s: &quot; fmt , driver_name , &bslash;&n;&t;&t;&t;pci_name(dev-&gt;pdev) , ## args)
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(dev,fmt,args...) &bslash;&n;&t;xprintk(dev , KERN_DEBUG , fmt , ## args)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(dev,fmt,args...) &bslash;&n;&t;do { } while (0)
macro_line|#endif /* DEBUG */
macro_line|#ifdef VERBOSE
DECL|macro|VDBG
mdefine_line|#define VDBG DBG
macro_line|#else
DECL|macro|VDBG
mdefine_line|#define VDBG(dev,fmt,args...) &bslash;&n;&t;do { } while (0)
macro_line|#endif&t;/* VERBOSE */
DECL|macro|ERROR
mdefine_line|#define ERROR(dev,fmt,args...) &bslash;&n;&t;xprintk(dev , KERN_ERR , fmt , ## args)
DECL|macro|WARN
mdefine_line|#define WARN(dev,fmt,args...) &bslash;&n;&t;xprintk(dev , KERN_WARNING , fmt , ## args)
DECL|macro|INFO
mdefine_line|#define INFO(dev,fmt,args...) &bslash;&n;&t;xprintk(dev , KERN_INFO , fmt , ## args)
eof
