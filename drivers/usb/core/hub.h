macro_line|#ifndef __LINUX_HUB_H
DECL|macro|__LINUX_HUB_H
mdefine_line|#define __LINUX_HUB_H
multiline_comment|/*&n; * Hub protocol and driver data structures.&n; *&n; * Some of these are known to the &quot;virtual root hub&quot; code&n; * in host controller drivers.&n; */
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;&t;/* likely()/unlikely() */
multiline_comment|/*&n; * Hub request types&n; */
DECL|macro|USB_RT_HUB
mdefine_line|#define USB_RT_HUB&t;(USB_TYPE_CLASS | USB_RECIP_DEVICE)
DECL|macro|USB_RT_PORT
mdefine_line|#define USB_RT_PORT&t;(USB_TYPE_CLASS | USB_RECIP_OTHER)
multiline_comment|/*&n; * Hub class requests&n; * See USB 2.0 spec Table 11-16&n; */
DECL|macro|HUB_CLEAR_TT_BUFFER
mdefine_line|#define HUB_CLEAR_TT_BUFFER&t;8
DECL|macro|HUB_RESET_TT
mdefine_line|#define HUB_RESET_TT&t;&t;9
DECL|macro|HUB_GET_TT_STATE
mdefine_line|#define HUB_GET_TT_STATE&t;10
DECL|macro|HUB_STOP_TT
mdefine_line|#define HUB_STOP_TT&t;&t;11
multiline_comment|/*&n; * Hub Class feature numbers&n; * See USB 2.0 spec Table 11-17&n; */
DECL|macro|C_HUB_LOCAL_POWER
mdefine_line|#define C_HUB_LOCAL_POWER&t;0
DECL|macro|C_HUB_OVER_CURRENT
mdefine_line|#define C_HUB_OVER_CURRENT&t;1
multiline_comment|/*&n; * Port feature numbers&n; * See USB 2.0 spec Table 11-17&n; */
DECL|macro|USB_PORT_FEAT_CONNECTION
mdefine_line|#define USB_PORT_FEAT_CONNECTION&t;0
DECL|macro|USB_PORT_FEAT_ENABLE
mdefine_line|#define USB_PORT_FEAT_ENABLE&t;&t;1
DECL|macro|USB_PORT_FEAT_SUSPEND
mdefine_line|#define USB_PORT_FEAT_SUSPEND&t;&t;2
DECL|macro|USB_PORT_FEAT_OVER_CURRENT
mdefine_line|#define USB_PORT_FEAT_OVER_CURRENT&t;3
DECL|macro|USB_PORT_FEAT_RESET
mdefine_line|#define USB_PORT_FEAT_RESET&t;&t;4
DECL|macro|USB_PORT_FEAT_POWER
mdefine_line|#define USB_PORT_FEAT_POWER&t;&t;8
DECL|macro|USB_PORT_FEAT_LOWSPEED
mdefine_line|#define USB_PORT_FEAT_LOWSPEED&t;&t;9
DECL|macro|USB_PORT_FEAT_HIGHSPEED
mdefine_line|#define USB_PORT_FEAT_HIGHSPEED&t;&t;10
DECL|macro|USB_PORT_FEAT_C_CONNECTION
mdefine_line|#define USB_PORT_FEAT_C_CONNECTION&t;16
DECL|macro|USB_PORT_FEAT_C_ENABLE
mdefine_line|#define USB_PORT_FEAT_C_ENABLE&t;&t;17
DECL|macro|USB_PORT_FEAT_C_SUSPEND
mdefine_line|#define USB_PORT_FEAT_C_SUSPEND&t;&t;18
DECL|macro|USB_PORT_FEAT_C_OVER_CURRENT
mdefine_line|#define USB_PORT_FEAT_C_OVER_CURRENT&t;19
DECL|macro|USB_PORT_FEAT_C_RESET
mdefine_line|#define USB_PORT_FEAT_C_RESET&t;&t;20
DECL|macro|USB_PORT_FEAT_TEST
mdefine_line|#define USB_PORT_FEAT_TEST              21
DECL|macro|USB_PORT_FEAT_INDICATOR
mdefine_line|#define USB_PORT_FEAT_INDICATOR         22
multiline_comment|/* &n; * Hub Status and Hub Change results&n; * See USB 2.0 spec Table 11-19 and Table 11-20&n; */
DECL|struct|usb_port_status
r_struct
id|usb_port_status
(brace
DECL|member|wPortStatus
id|__u16
id|wPortStatus
suffix:semicolon
DECL|member|wPortChange
id|__u16
id|wPortChange
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* &n; * wPortStatus bit field&n; * See USB 2.0 spec Table 11-21&n; */
DECL|macro|USB_PORT_STAT_CONNECTION
mdefine_line|#define USB_PORT_STAT_CONNECTION&t;0x0001
DECL|macro|USB_PORT_STAT_ENABLE
mdefine_line|#define USB_PORT_STAT_ENABLE&t;&t;0x0002
DECL|macro|USB_PORT_STAT_SUSPEND
mdefine_line|#define USB_PORT_STAT_SUSPEND&t;&t;0x0004
DECL|macro|USB_PORT_STAT_OVERCURRENT
mdefine_line|#define USB_PORT_STAT_OVERCURRENT&t;0x0008
DECL|macro|USB_PORT_STAT_RESET
mdefine_line|#define USB_PORT_STAT_RESET&t;&t;0x0010
multiline_comment|/* bits 5 to 7 are reserved */
DECL|macro|USB_PORT_STAT_POWER
mdefine_line|#define USB_PORT_STAT_POWER&t;&t;0x0100
DECL|macro|USB_PORT_STAT_LOW_SPEED
mdefine_line|#define USB_PORT_STAT_LOW_SPEED&t;&t;0x0200
DECL|macro|USB_PORT_STAT_HIGH_SPEED
mdefine_line|#define USB_PORT_STAT_HIGH_SPEED        0x0400
DECL|macro|USB_PORT_STAT_TEST
mdefine_line|#define USB_PORT_STAT_TEST              0x0800
DECL|macro|USB_PORT_STAT_INDICATOR
mdefine_line|#define USB_PORT_STAT_INDICATOR         0x1000
multiline_comment|/* bits 13 to 15 are reserved */
multiline_comment|/* &n; * wPortChange bit field&n; * See USB 2.0 spec Table 11-22&n; * Bits 0 to 4 shown, bits 5 to 15 are reserved&n; */
DECL|macro|USB_PORT_STAT_C_CONNECTION
mdefine_line|#define USB_PORT_STAT_C_CONNECTION&t;0x0001
DECL|macro|USB_PORT_STAT_C_ENABLE
mdefine_line|#define USB_PORT_STAT_C_ENABLE&t;&t;0x0002
DECL|macro|USB_PORT_STAT_C_SUSPEND
mdefine_line|#define USB_PORT_STAT_C_SUSPEND&t;&t;0x0004
DECL|macro|USB_PORT_STAT_C_OVERCURRENT
mdefine_line|#define USB_PORT_STAT_C_OVERCURRENT&t;0x0008
DECL|macro|USB_PORT_STAT_C_RESET
mdefine_line|#define USB_PORT_STAT_C_RESET&t;&t;0x0010
multiline_comment|/*&n; * wHubCharacteristics (masks) &n; * See USB 2.0 spec Table 11-13, offset 3&n; */
DECL|macro|HUB_CHAR_LPSM
mdefine_line|#define HUB_CHAR_LPSM&t;&t;0x0003 /* D1 .. D0 */
DECL|macro|HUB_CHAR_COMPOUND
mdefine_line|#define HUB_CHAR_COMPOUND&t;0x0004 /* D2       */
DECL|macro|HUB_CHAR_OCPM
mdefine_line|#define HUB_CHAR_OCPM&t;&t;0x0018 /* D4 .. D3 */
DECL|macro|HUB_CHAR_TTTT
mdefine_line|#define HUB_CHAR_TTTT           0x0060 /* D6 .. D5 */
DECL|macro|HUB_CHAR_PORTIND
mdefine_line|#define HUB_CHAR_PORTIND        0x0080 /* D7       */
DECL|struct|usb_hub_status
r_struct
id|usb_hub_status
(brace
DECL|member|wHubStatus
id|__u16
id|wHubStatus
suffix:semicolon
DECL|member|wHubChange
id|__u16
id|wHubChange
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Hub Status &amp; Hub Change bit masks&n; * See USB 2.0 spec Table 11-19 and Table 11-20&n; * Bits 0 and 1 for wHubStatus and wHubChange&n; * Bits 2 to 15 are reserved for both&n; */
DECL|macro|HUB_STATUS_LOCAL_POWER
mdefine_line|#define HUB_STATUS_LOCAL_POWER&t;0x0001
DECL|macro|HUB_STATUS_OVERCURRENT
mdefine_line|#define HUB_STATUS_OVERCURRENT&t;0x0002
DECL|macro|HUB_CHANGE_LOCAL_POWER
mdefine_line|#define HUB_CHANGE_LOCAL_POWER&t;0x0001
DECL|macro|HUB_CHANGE_OVERCURRENT
mdefine_line|#define HUB_CHANGE_OVERCURRENT&t;0x0002
multiline_comment|/* &n; * Hub descriptor &n; * See USB 2.0 spec Table 11-13&n; */
DECL|struct|usb_hub_descriptor
r_struct
id|usb_hub_descriptor
(brace
DECL|member|bDescLength
id|__u8
id|bDescLength
suffix:semicolon
DECL|member|bDescriptorType
id|__u8
id|bDescriptorType
suffix:semicolon
DECL|member|bNbrPorts
id|__u8
id|bNbrPorts
suffix:semicolon
DECL|member|wHubCharacteristics
id|__u16
id|wHubCharacteristics
suffix:semicolon
DECL|member|bPwrOn2PwrGood
id|__u8
id|bPwrOn2PwrGood
suffix:semicolon
DECL|member|bHubContrCurrent
id|__u8
id|bHubContrCurrent
suffix:semicolon
multiline_comment|/* add 1 bit for hub status change; round to bytes */
DECL|member|DeviceRemovable
id|__u8
id|DeviceRemovable
(braket
(paren
id|USB_MAXCHILDREN
op_plus
l_int|1
op_plus
l_int|7
)paren
op_div
l_int|8
)braket
suffix:semicolon
DECL|member|PortPwrCtrlMask
id|__u8
id|PortPwrCtrlMask
(braket
(paren
id|USB_MAXCHILDREN
op_plus
l_int|1
op_plus
l_int|7
)paren
op_div
l_int|8
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
r_struct
id|usb_device
suffix:semicolon
multiline_comment|/*&n; * As of USB 2.0, full/low speed devices are segregated into trees.&n; * One type grows from USB 1.1 host controllers (OHCI, UHCI etc).&n; * The other type grows from high speed hubs when they connect to&n; * full/low speed devices using &quot;Transaction Translators&quot; (TTs).&n; *&n; * TTs should only be known to the hub driver, and high speed bus&n; * drivers (only EHCI for now).  They affect periodic scheduling and&n; * sometimes control/bulk error recovery.&n; */
DECL|struct|usb_tt
r_struct
id|usb_tt
(brace
DECL|member|hub
r_struct
id|usb_device
op_star
id|hub
suffix:semicolon
multiline_comment|/* upstream highspeed hub */
DECL|member|multi
r_int
id|multi
suffix:semicolon
multiline_comment|/* true means one TT per port */
multiline_comment|/* for control/bulk error recovery (CLEAR_TT_BUFFER) */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|clear_list
r_struct
id|list_head
id|clear_list
suffix:semicolon
multiline_comment|/* of usb_tt_clear */
DECL|member|kevent
r_struct
id|tq_struct
id|kevent
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|usb_tt_clear
r_struct
id|usb_tt_clear
(brace
DECL|member|clear_list
r_struct
id|list_head
id|clear_list
suffix:semicolon
DECL|member|tt
r_int
id|tt
suffix:semicolon
DECL|member|devinfo
id|u16
id|devinfo
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|usb_hub_tt_clear_buffer
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|pipe
)paren
suffix:semicolon
DECL|struct|usb_hub
r_struct
id|usb_hub
(brace
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* the &quot;real&quot; device */
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
multiline_comment|/* for interrupt polling pipe */
multiline_comment|/* buffer for urb ... 1 bit each for hub and children, rounded up */
DECL|member|buffer
r_char
id|buffer
(braket
(paren
id|USB_MAXCHILDREN
op_plus
l_int|1
op_plus
l_int|7
)paren
op_div
l_int|8
)braket
suffix:semicolon
DECL|member|error
r_int
id|error
suffix:semicolon
multiline_comment|/* last reported error */
DECL|member|nerrors
r_int
id|nerrors
suffix:semicolon
multiline_comment|/* track consecutive errors */
DECL|member|hub_list
r_struct
id|list_head
id|hub_list
suffix:semicolon
multiline_comment|/* all hubs */
DECL|member|event_list
r_struct
id|list_head
id|event_list
suffix:semicolon
multiline_comment|/* hubs w/data or errs ready */
DECL|member|descriptor
r_struct
id|usb_hub_descriptor
op_star
id|descriptor
suffix:semicolon
multiline_comment|/* class descriptor */
DECL|member|khubd_sem
r_struct
id|semaphore
id|khubd_sem
suffix:semicolon
DECL|member|tt
r_struct
id|usb_tt
id|tt
suffix:semicolon
multiline_comment|/* Transaction Translator */
)brace
suffix:semicolon
macro_line|#endif /* __LINUX_HUB_H */
eof
