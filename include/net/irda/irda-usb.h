multiline_comment|/*****************************************************************************&n; *&n; * Filename:      irda-usb.h&n; * Version:       0.8&n; * Description:   IrDA-USB Driver&n; * Status:        Experimental &n; * Author:        Dag Brattli &lt;dag@brattli.net&gt;&n; *&n; *      Copyright (C) 2001, Dag Brattli &lt;dag@brattli.net&gt;&n; *&t;Copyright (C) 2000, Roman Weissgaerber &lt;weissg@vienna.at&gt;&n; *          &n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License&n; *&t;along with this program; if not, write to the Free Software&n; *&t;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *****************************************************************************/
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irlap.h&gt;
macro_line|#include &lt;net/irda/irda_device.h&gt;
DECL|macro|RX_COPY_THRESHOLD
mdefine_line|#define RX_COPY_THRESHOLD 200
DECL|macro|IRDA_USB_MAX_MTU
mdefine_line|#define IRDA_USB_MAX_MTU 2051
DECL|macro|IRDA_USB_SPEED_MTU
mdefine_line|#define IRDA_USB_SPEED_MTU 64&t;&t;/* Weird, but work like this */
multiline_comment|/*&n; * Maximum number of URB on the Rx and Tx path, a number larger than 1&n; * is required for handling back-to-back (brickwalled) frames &n; */
DECL|macro|IU_MAX_ACTIVE_RX_URBS
mdefine_line|#define IU_MAX_ACTIVE_RX_URBS 1
DECL|macro|IU_MAX_RX_URBS
mdefine_line|#define IU_MAX_RX_URBS&t;(IU_MAX_ACTIVE_RX_URBS + 1) 
DECL|macro|IU_MAX_TX_URBS
mdefine_line|#define IU_MAX_TX_URBS  1
multiline_comment|/* Inbound header */
DECL|macro|MEDIA_BUSY
mdefine_line|#define MEDIA_BUSY    0x80
DECL|macro|SPEED_2400
mdefine_line|#define SPEED_2400    0x01
DECL|macro|SPEED_9600
mdefine_line|#define SPEED_9600    0x02
DECL|macro|SPEED_19200
mdefine_line|#define SPEED_19200   0x03
DECL|macro|SPEED_38400
mdefine_line|#define SPEED_38400   0x04
DECL|macro|SPEED_57600
mdefine_line|#define SPEED_57600   0x05
DECL|macro|SPEED_115200
mdefine_line|#define SPEED_115200  0x06
DECL|macro|SPEED_576000
mdefine_line|#define SPEED_576000  0x07
DECL|macro|SPEED_1152000
mdefine_line|#define SPEED_1152000 0x08
DECL|macro|SPEED_4000000
mdefine_line|#define SPEED_4000000 0x09
multiline_comment|/* device_info flags in struct usb_device_id */
DECL|macro|IUC_DEFAULT
mdefine_line|#define IUC_DEFAULT&t;0x00&t;/* Basic device compliant with 1.0 spec */
DECL|macro|IUC_SPEED_BUG
mdefine_line|#define IUC_SPEED_BUG&t;0x01&t;/* Device doesn&squot;t set speed after the frame */
DECL|macro|IUC_SIR_ONLY
mdefine_line|#define IUC_SIR_ONLY&t;0x02&t;/* Device doesn&squot;t behave at FIR speeds */
DECL|macro|IUC_SMALL_PKT
mdefine_line|#define IUC_SMALL_PKT&t;0x04&t;/* Device doesn&squot;t behave with big Rx packets */
DECL|macro|IUC_NO_WINDOW
mdefine_line|#define IUC_NO_WINDOW&t;0x08&t;/* Device doesn&squot;t behave with big Rx window */
DECL|macro|IUC_MAX_WINDOW
mdefine_line|#define IUC_MAX_WINDOW&t;0x10&t;/* Device underestimate the Rx window */
DECL|macro|IUC_MAX_XBOFS
mdefine_line|#define IUC_MAX_XBOFS&t;0x20&t;/* Device need more xbofs than advertised */
DECL|macro|USB_IRDA_HEADER
mdefine_line|#define USB_IRDA_HEADER   0x01
DECL|macro|USB_CLASS_IRDA
mdefine_line|#define USB_CLASS_IRDA    0x02 /* USB_CLASS_APP_SPEC subclass */ 
DECL|macro|USB_DT_IRDA
mdefine_line|#define USB_DT_IRDA       0x21
DECL|struct|irda_class_desc
r_struct
id|irda_class_desc
(brace
DECL|member|bLength
id|__u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|bcdSpecRevision
id|__u16
id|bcdSpecRevision
suffix:semicolon
DECL|member|bmDataSize
id|__u8
id|bmDataSize
suffix:semicolon
DECL|member|bmWindowSize
id|__u8
id|bmWindowSize
suffix:semicolon
DECL|member|bmMinTurnaroundTime
id|__u8
id|bmMinTurnaroundTime
suffix:semicolon
DECL|member|wBaudRate
id|__u16
id|wBaudRate
suffix:semicolon
DECL|member|bmAdditionalBOFs
id|__u8
id|bmAdditionalBOFs
suffix:semicolon
DECL|member|bIrdaRateSniff
id|__u8
id|bIrdaRateSniff
suffix:semicolon
DECL|member|bMaxUnicastList
id|__u8
id|bMaxUnicastList
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|irda_usb_cb
r_struct
id|irda_usb_cb
(brace
DECL|member|irda_desc
r_struct
id|irda_class_desc
op_star
id|irda_desc
suffix:semicolon
DECL|member|usbdev
r_struct
id|usb_device
op_star
id|usbdev
suffix:semicolon
multiline_comment|/* init: probe_irda */
DECL|member|ifnum
r_int
r_int
id|ifnum
suffix:semicolon
multiline_comment|/* Interface number of the USB dev. */
DECL|member|netopen
r_int
id|netopen
suffix:semicolon
multiline_comment|/* Device is active for network */
DECL|member|present
r_int
id|present
suffix:semicolon
multiline_comment|/* Device is present on the bus */
DECL|member|capability
id|__u32
id|capability
suffix:semicolon
multiline_comment|/* Capability of the hardware */
DECL|member|bulk_in_ep
DECL|member|bulk_out_ep
id|__u8
id|bulk_in_ep
comma
id|bulk_out_ep
suffix:semicolon
multiline_comment|/* Endpoint assignments */
DECL|member|bulk_out_mtu
id|__u16
id|bulk_out_mtu
suffix:semicolon
DECL|member|wait_q
id|wait_queue_head_t
id|wait_q
suffix:semicolon
multiline_comment|/* for timeouts */
DECL|member|rx_urb
r_struct
id|urb
id|rx_urb
(braket
id|IU_MAX_RX_URBS
)braket
suffix:semicolon
multiline_comment|/* URBs used to receive data frames */
DECL|member|rx_idle_urb
r_struct
id|urb
op_star
id|rx_idle_urb
suffix:semicolon
multiline_comment|/* Pointer to idle URB in Rx path */
DECL|member|tx_urb
r_struct
id|urb
id|tx_urb
suffix:semicolon
multiline_comment|/* URB used to send data frames */
DECL|member|speed_urb
r_struct
id|urb
id|speed_urb
suffix:semicolon
multiline_comment|/* URB used to send speed commands */
DECL|member|netdev
r_struct
id|net_device
op_star
id|netdev
suffix:semicolon
multiline_comment|/* Yes! we are some kind of netdev. */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|irlap
r_struct
id|irlap_cb
op_star
id|irlap
suffix:semicolon
multiline_comment|/* The link layer we are binded to */
DECL|member|qos
r_struct
id|qos_info
id|qos
suffix:semicolon
DECL|member|tx_list
id|hashbin_t
op_star
id|tx_list
suffix:semicolon
multiline_comment|/* Queued transmit skb&squot;s */
DECL|member|stamp
r_struct
id|timeval
id|stamp
suffix:semicolon
DECL|member|now
r_struct
id|timeval
id|now
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* For serializing operations */
DECL|member|xbofs
id|__u16
id|xbofs
suffix:semicolon
multiline_comment|/* Current xbofs setting */
DECL|member|new_xbofs
id|__s16
id|new_xbofs
suffix:semicolon
multiline_comment|/* xbofs we need to set */
DECL|member|speed
id|__u32
id|speed
suffix:semicolon
multiline_comment|/* Current speed */
DECL|member|new_speed
id|__s32
id|new_speed
suffix:semicolon
multiline_comment|/* speed we need to set */
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* Interface flags */
)brace
suffix:semicolon
eof
