multiline_comment|/*&n; * linux/drivers/usb/gadget/lh7a40x_udc.h&n; * Sharp LH7A40x on-chip full speed USB device controllers&n; *&n; * Copyright (C) 2004 Mikko Lahteenmaki, Nordic ID&n; * Copyright (C) 2004 Bo Henriksen, Nordic ID&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; */
macro_line|#ifndef __LH7A40X_H_
DECL|macro|__LH7A40X_H_
mdefine_line|#define __LH7A40X_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;linux/usb_ch9.h&gt;
macro_line|#include &lt;linux/usb_gadget.h&gt;
multiline_comment|/*&n; * Memory map&n; */
DECL|macro|USB_FA
mdefine_line|#define USB_FA&t;&t;&t;&t;&t;0x80000200&t;
singleline_comment|// function address register
DECL|macro|USB_PM
mdefine_line|#define USB_PM&t;&t;&t;&t;&t;0x80000204&t;
singleline_comment|// power management register
DECL|macro|USB_IN_INT
mdefine_line|#define USB_IN_INT&t;&t;&t;&t;0x80000208&t;
singleline_comment|// IN interrupt register bank (EP0-EP3)
DECL|macro|USB_OUT_INT
mdefine_line|#define USB_OUT_INT&t;&t;&t;&t;0x80000210&t;
singleline_comment|// OUT interrupt register bank (EP2)
DECL|macro|USB_INT
mdefine_line|#define USB_INT&t;&t;&t;&t;&t;0x80000218&t;
singleline_comment|// interrupt register bank
DECL|macro|USB_IN_INT_EN
mdefine_line|#define USB_IN_INT_EN&t;&t;&t;0x8000021C&t;
singleline_comment|// IN interrupt enable register bank
DECL|macro|USB_OUT_INT_EN
mdefine_line|#define USB_OUT_INT_EN&t;&t;&t;0x80000224&t;
singleline_comment|// OUT interrupt enable register bank
DECL|macro|USB_INT_EN
mdefine_line|#define USB_INT_EN&t;&t;&t;&t;0x8000022C&t;
singleline_comment|// USB interrupt enable register bank
DECL|macro|USB_FRM_NUM1
mdefine_line|#define USB_FRM_NUM1&t;&t;&t;0x80000230&t;
singleline_comment|// Frame number1 register
DECL|macro|USB_FRM_NUM2
mdefine_line|#define USB_FRM_NUM2&t;&t;&t;0x80000234&t;
singleline_comment|// Frame number2 register
DECL|macro|USB_INDEX
mdefine_line|#define USB_INDEX&t;&t;&t;&t;0x80000238&t;
singleline_comment|// index register
DECL|macro|USB_IN_MAXP
mdefine_line|#define USB_IN_MAXP&t;&t;&t;&t;0x80000240&t;
singleline_comment|// IN MAXP register
DECL|macro|USB_IN_CSR1
mdefine_line|#define USB_IN_CSR1&t;&t;&t;&t;0x80000244&t;
singleline_comment|// IN CSR1 register/EP0 CSR register
DECL|macro|USB_EP0_CSR
mdefine_line|#define USB_EP0_CSR&t;&t;&t;&t;0x80000244&t;
singleline_comment|// IN CSR1 register/EP0 CSR register
DECL|macro|USB_IN_CSR2
mdefine_line|#define USB_IN_CSR2&t;&t;&t;&t;0x80000248&t;
singleline_comment|// IN CSR2 register
DECL|macro|USB_OUT_MAXP
mdefine_line|#define USB_OUT_MAXP&t;&t;&t;0x8000024C&t;
singleline_comment|// OUT MAXP register
DECL|macro|USB_OUT_CSR1
mdefine_line|#define USB_OUT_CSR1&t;&t;&t;0x80000250&t;
singleline_comment|// OUT CSR1 register
DECL|macro|USB_OUT_CSR2
mdefine_line|#define USB_OUT_CSR2&t;&t;&t;0x80000254&t;
singleline_comment|// OUT CSR2 register
DECL|macro|USB_OUT_FIFO_WC1
mdefine_line|#define USB_OUT_FIFO_WC1&t;&t;0x80000258&t;
singleline_comment|// OUT FIFO write count1 register
DECL|macro|USB_OUT_FIFO_WC2
mdefine_line|#define USB_OUT_FIFO_WC2&t;&t;0x8000025C&t;
singleline_comment|// OUT FIFO write count2 register
DECL|macro|USB_RESET
mdefine_line|#define USB_RESET&t;&t;&t;&t;0x8000044C&t;
singleline_comment|// USB reset register
DECL|macro|USB_EP0_FIFO
mdefine_line|#define&t;USB_EP0_FIFO&t;&t;&t;0x80000280
DECL|macro|USB_EP1_FIFO
mdefine_line|#define&t;USB_EP1_FIFO&t;&t;&t;0x80000284
DECL|macro|USB_EP2_FIFO
mdefine_line|#define&t;USB_EP2_FIFO&t;&t;&t;0x80000288
DECL|macro|USB_EP3_FIFO
mdefine_line|#define&t;USB_EP3_FIFO&t;&t;&t;0x8000028c
multiline_comment|/*&n; * USB reset register&n; */
DECL|macro|USB_RESET_APB
mdefine_line|#define USB_RESET_APB&t;&t;&t;(1&lt;&lt;1)&t;
singleline_comment|//resets USB APB control side WRITE
DECL|macro|USB_RESET_IO
mdefine_line|#define USB_RESET_IO&t;&t;&t;(1&lt;&lt;0)&t;
singleline_comment|//resets USB IO side WRITE
multiline_comment|/*&n; * USB function address register&n; */
DECL|macro|USB_FA_ADDR_UPDATE
mdefine_line|#define USB_FA_ADDR_UPDATE&t;&t;(1&lt;&lt;7)
DECL|macro|USB_FA_FUNCTION_ADDR
mdefine_line|#define USB_FA_FUNCTION_ADDR&t;(0x7F)
multiline_comment|/*&n; * Power Management register&n; */
DECL|macro|PM_USB_DCP
mdefine_line|#define PM_USB_DCP&t;&t;&t;&t;(1&lt;&lt;5)
DECL|macro|PM_USB_ENABLE
mdefine_line|#define PM_USB_ENABLE&t;&t;&t;(1&lt;&lt;4)
DECL|macro|PM_USB_RESET
mdefine_line|#define PM_USB_RESET&t;&t;&t;(1&lt;&lt;3)
DECL|macro|PM_UC_RESUME
mdefine_line|#define PM_UC_RESUME&t;&t;&t;(1&lt;&lt;2)
DECL|macro|PM_SUSPEND_MODE
mdefine_line|#define PM_SUSPEND_MODE&t;&t;&t;(1&lt;&lt;1)
DECL|macro|PM_ENABLE_SUSPEND
mdefine_line|#define PM_ENABLE_SUSPEND&t;&t;(1&lt;&lt;0)
multiline_comment|/*&n; * IN interrupt register&n; */
DECL|macro|USB_IN_INT_EP3
mdefine_line|#define USB_IN_INT_EP3&t;&t;&t;&t;(1&lt;&lt;3)
DECL|macro|USB_IN_INT_EP1
mdefine_line|#define USB_IN_INT_EP1&t;&t;&t;&t;(1&lt;&lt;1)
DECL|macro|USB_IN_INT_EP0
mdefine_line|#define USB_IN_INT_EP0&t;&t;&t;&t;(1&lt;&lt;0)
multiline_comment|/*&n; * OUT interrupt register&n; */
DECL|macro|USB_OUT_INT_EP2
mdefine_line|#define USB_OUT_INT_EP2&t;&t;&t;&t;(1&lt;&lt;2)
multiline_comment|/*&n; * USB interrupt register&n; */
DECL|macro|USB_INT_RESET_INT
mdefine_line|#define USB_INT_RESET_INT&t;&t;&t;(1&lt;&lt;2)
DECL|macro|USB_INT_RESUME_INT
mdefine_line|#define USB_INT_RESUME_INT&t;&t;&t;(1&lt;&lt;1)
DECL|macro|USB_INT_SUSPEND_INT
mdefine_line|#define USB_INT_SUSPEND_INT&t;&t;&t;(1&lt;&lt;0)
multiline_comment|/*&n; * USB interrupt enable register&n; */
DECL|macro|USB_INT_EN_USB_RESET_INTER
mdefine_line|#define USB_INT_EN_USB_RESET_INTER&t;&t;(1&lt;&lt;2)
DECL|macro|USB_INT_EN_RESUME_INTER
mdefine_line|#define USB_INT_EN_RESUME_INTER&t;&t;&t;(1&lt;&lt;1)
DECL|macro|USB_INT_EN_SUSPEND_INTER
mdefine_line|#define USB_INT_EN_SUSPEND_INTER&t;&t;(1&lt;&lt;0)
multiline_comment|/*&n; * INCSR1 register&n; */
DECL|macro|USB_IN_CSR1_CLR_DATA_TOGGLE
mdefine_line|#define USB_IN_CSR1_CLR_DATA_TOGGLE&t;&t;(1&lt;&lt;6)
DECL|macro|USB_IN_CSR1_SENT_STALL
mdefine_line|#define USB_IN_CSR1_SENT_STALL&t;&t;&t;(1&lt;&lt;5)
DECL|macro|USB_IN_CSR1_SEND_STALL
mdefine_line|#define USB_IN_CSR1_SEND_STALL&t;&t;&t;(1&lt;&lt;4)
DECL|macro|USB_IN_CSR1_FIFO_FLUSH
mdefine_line|#define USB_IN_CSR1_FIFO_FLUSH&t;&t;&t;(1&lt;&lt;3)
DECL|macro|USB_IN_CSR1_FIFO_NOT_EMPTY
mdefine_line|#define USB_IN_CSR1_FIFO_NOT_EMPTY&t;&t;(1&lt;&lt;1)
DECL|macro|USB_IN_CSR1_IN_PKT_RDY
mdefine_line|#define USB_IN_CSR1_IN_PKT_RDY&t;&t;&t;(1&lt;&lt;0)
multiline_comment|/*&n; * INCSR2 register&n; */
DECL|macro|USB_IN_CSR2_AUTO_SET
mdefine_line|#define USB_IN_CSR2_AUTO_SET&t;&t;&t;(1&lt;&lt;7)
DECL|macro|USB_IN_CSR2_USB_DMA_EN
mdefine_line|#define USB_IN_CSR2_USB_DMA_EN&t;&t;&t;(1&lt;&lt;4)
multiline_comment|/*&n; * OUT CSR1 register&n; */
DECL|macro|USB_OUT_CSR1_CLR_DATA_REG
mdefine_line|#define USB_OUT_CSR1_CLR_DATA_REG&t;&t;(1&lt;&lt;7)
DECL|macro|USB_OUT_CSR1_SENT_STALL
mdefine_line|#define USB_OUT_CSR1_SENT_STALL&t;&t;&t;(1&lt;&lt;6)
DECL|macro|USB_OUT_CSR1_SEND_STALL
mdefine_line|#define USB_OUT_CSR1_SEND_STALL&t;&t;&t;(1&lt;&lt;5)
DECL|macro|USB_OUT_CSR1_FIFO_FLUSH
mdefine_line|#define USB_OUT_CSR1_FIFO_FLUSH&t;&t;&t;(1&lt;&lt;4)
DECL|macro|USB_OUT_CSR1_FIFO_FULL
mdefine_line|#define USB_OUT_CSR1_FIFO_FULL&t;&t;&t;(1&lt;&lt;1)
DECL|macro|USB_OUT_CSR1_OUT_PKT_RDY
mdefine_line|#define USB_OUT_CSR1_OUT_PKT_RDY&t;&t;(1&lt;&lt;0)
multiline_comment|/*&n; * OUT CSR2 register&n; */
DECL|macro|USB_OUT_CSR2_AUTO_CLR
mdefine_line|#define USB_OUT_CSR2_AUTO_CLR&t;&t;&t;(1&lt;&lt;7)
DECL|macro|USB_OUT_CSR2_USB_DMA_EN
mdefine_line|#define USB_OUT_CSR2_USB_DMA_EN&t;&t;&t;(1&lt;&lt;4)
multiline_comment|/*&n; * EP0 CSR&n; */
DECL|macro|EP0_CLR_SETUP_END
mdefine_line|#define EP0_CLR_SETUP_END&t;&t;(1&lt;&lt;7)&t;/* Clear &quot;Setup Ends&quot; Bit (w) */
DECL|macro|EP0_CLR_OUT
mdefine_line|#define EP0_CLR_OUT&t;&t;&t;&t;(1&lt;&lt;6)&t;/* Clear &quot;Out packet ready&quot; Bit (w) */
DECL|macro|EP0_SEND_STALL
mdefine_line|#define EP0_SEND_STALL&t;&t;&t;(1&lt;&lt;5)&t;/* Send STALL Handshake (rw) */
DECL|macro|EP0_SETUP_END
mdefine_line|#define EP0_SETUP_END&t;&t;&t;(1&lt;&lt;4)&t;/* Setup Ends (r) */
DECL|macro|EP0_DATA_END
mdefine_line|#define EP0_DATA_END&t;&t;&t;(1&lt;&lt;3)&t;/* Data end (rw) */
DECL|macro|EP0_SENT_STALL
mdefine_line|#define EP0_SENT_STALL&t;&t;&t;(1&lt;&lt;2)&t;/* Sent Stall Handshake (r) */
DECL|macro|EP0_IN_PKT_RDY
mdefine_line|#define EP0_IN_PKT_RDY&t;&t;&t;(1&lt;&lt;1)&t;/* In packet ready (rw) */
DECL|macro|EP0_OUT_PKT_RDY
mdefine_line|#define EP0_OUT_PKT_RDY&t;&t;&t;(1&lt;&lt;0)&t;/* Out packet ready (r) */
multiline_comment|/* general CSR */
DECL|macro|OUT_PKT_RDY
mdefine_line|#define OUT_PKT_RDY&t;&t;(1&lt;&lt;0)
DECL|macro|IN_PKT_RDY
mdefine_line|#define IN_PKT_RDY&t;&t;(1&lt;&lt;0)
multiline_comment|/*&n; * IN/OUT MAXP register&n; */
DECL|macro|USB_OUT_MAXP_MAXP
mdefine_line|#define USB_OUT_MAXP_MAXP&t;&t;&t;(0xF)
DECL|macro|USB_IN_MAXP_MAXP
mdefine_line|#define USB_IN_MAXP_MAXP&t;&t;&t;(0xF)
singleline_comment|// Max packet size
singleline_comment|//#define EP0_PACKETSIZE        0x10
DECL|macro|EP0_PACKETSIZE
mdefine_line|#define EP0_PACKETSIZE  &t;0x8
DECL|macro|EP0_MAXPACKETSIZE
mdefine_line|#define EP0_MAXPACKETSIZE  &t;0x10
DECL|macro|UDC_MAX_ENDPOINTS
mdefine_line|#define UDC_MAX_ENDPOINTS       4
DECL|macro|WAIT_FOR_SETUP
mdefine_line|#define WAIT_FOR_SETUP          0
DECL|macro|DATA_STATE_XMIT
mdefine_line|#define DATA_STATE_XMIT         1
DECL|macro|DATA_STATE_NEED_ZLP
mdefine_line|#define DATA_STATE_NEED_ZLP     2
DECL|macro|WAIT_FOR_OUT_STATUS
mdefine_line|#define WAIT_FOR_OUT_STATUS     3
DECL|macro|DATA_STATE_RECV
mdefine_line|#define DATA_STATE_RECV         4
multiline_comment|/* ********************************************************************************************* */
multiline_comment|/* IO&n; */
DECL|enum|ep_type
r_typedef
r_enum
id|ep_type
(brace
DECL|enumerator|ep_control
DECL|enumerator|ep_bulk_in
DECL|enumerator|ep_bulk_out
DECL|enumerator|ep_interrupt
id|ep_control
comma
id|ep_bulk_in
comma
id|ep_bulk_out
comma
id|ep_interrupt
DECL|typedef|ep_type_t
)brace
id|ep_type_t
suffix:semicolon
DECL|struct|lh7a40x_ep
r_struct
id|lh7a40x_ep
(brace
DECL|member|ep
r_struct
id|usb_ep
id|ep
suffix:semicolon
DECL|member|dev
r_struct
id|lh7a40x_udc
op_star
id|dev
suffix:semicolon
DECL|member|desc
r_const
r_struct
id|usb_endpoint_descriptor
op_star
id|desc
suffix:semicolon
DECL|member|queue
r_struct
id|list_head
id|queue
suffix:semicolon
DECL|member|pio_irqs
r_int
r_int
id|pio_irqs
suffix:semicolon
DECL|member|stopped
id|u8
id|stopped
suffix:semicolon
DECL|member|bEndpointAddress
id|u8
id|bEndpointAddress
suffix:semicolon
DECL|member|bmAttributes
id|u8
id|bmAttributes
suffix:semicolon
DECL|member|ep_type
id|ep_type_t
id|ep_type
suffix:semicolon
DECL|member|fifo
id|u32
id|fifo
suffix:semicolon
DECL|member|csr1
id|u32
id|csr1
suffix:semicolon
DECL|member|csr2
id|u32
id|csr2
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|lh7a40x_request
r_struct
id|lh7a40x_request
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
)brace
suffix:semicolon
DECL|struct|lh7a40x_udc
r_struct
id|lh7a40x_udc
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
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|ep0state
r_int
id|ep0state
suffix:semicolon
DECL|member|ep
r_struct
id|lh7a40x_ep
id|ep
(braket
id|UDC_MAX_ENDPOINTS
)braket
suffix:semicolon
DECL|member|usb_address
r_int
r_char
id|usb_address
suffix:semicolon
DECL|member|req_pending
DECL|member|req_std
DECL|member|req_config
r_int
id|req_pending
suffix:colon
l_int|1
comma
id|req_std
suffix:colon
l_int|1
comma
id|req_config
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|lh7a40x_udc
op_star
id|the_controller
suffix:semicolon
DECL|macro|ep_is_in
mdefine_line|#define ep_is_in(EP) &t;&t;(((EP)-&gt;bEndpointAddress&amp;USB_DIR_IN)==USB_DIR_IN)
DECL|macro|ep_index
mdefine_line|#define ep_index(EP) &t;&t;((EP)-&gt;bEndpointAddress&amp;0xF)
DECL|macro|ep_maxpacket
mdefine_line|#define ep_maxpacket(EP) &t;((EP)-&gt;ep.maxpacket)
macro_line|#endif
eof
