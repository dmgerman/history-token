multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* list of all controllers using this driver &n; * */
r_static
id|LIST_HEAD
(paren
id|hci_hcd_list
)paren
suffix:semicolon
multiline_comment|/* URB states (urb_state) */
multiline_comment|/* isoc, interrupt single state */
multiline_comment|/* bulk transfer main state and 0-length packet */
DECL|macro|US_BULK
mdefine_line|#define US_BULK&t;&t;0
DECL|macro|US_BULK0
mdefine_line|#define US_BULK0&t;1
multiline_comment|/* three setup states */
DECL|macro|US_CTRL_SETUP
mdefine_line|#define US_CTRL_SETUP&t;2
DECL|macro|US_CTRL_DATA
mdefine_line|#define US_CTRL_DATA&t;1
DECL|macro|US_CTRL_ACK
mdefine_line|#define US_CTRL_ACK&t;0
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* HC private part of a device descriptor&n; * */
DECL|macro|NUM_EDS
mdefine_line|#define NUM_EDS 32
DECL|struct|epd
r_typedef
r_struct
id|epd
(brace
DECL|member|pipe_head
r_struct
id|urb
op_star
id|pipe_head
suffix:semicolon
DECL|member|urb_queue
r_struct
id|list_head
id|urb_queue
suffix:semicolon
singleline_comment|//&t;int urb_state;
DECL|member|timeout
r_struct
id|timer_list
id|timeout
suffix:semicolon
DECL|member|last_iso
r_int
id|last_iso
suffix:semicolon
multiline_comment|/* timestamp of last queued ISOC transfer */
DECL|typedef|epd_t
)brace
id|epd_t
suffix:semicolon
DECL|struct|hci_device
r_struct
id|hci_device
(brace
DECL|member|ed
id|epd_t
id|ed
(braket
id|NUM_EDS
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* Virtual Root HUB &n; */
DECL|macro|usb_to_hci
mdefine_line|#define usb_to_hci(usb)&t;((struct hci_device *)(usb)-&gt;hcpriv)
DECL|struct|virt_root_hub
r_struct
id|virt_root_hub
(brace
DECL|member|devnum
r_int
id|devnum
suffix:semicolon
multiline_comment|/* Address of Root Hub endpoint */
DECL|member|urb
r_void
op_star
id|urb
suffix:semicolon
multiline_comment|/* interrupt URB of root hub */
DECL|member|send
r_int
id|send
suffix:semicolon
multiline_comment|/* active flag */
DECL|member|interval
r_int
id|interval
suffix:semicolon
multiline_comment|/* intervall of roothub interrupt transfers */
DECL|member|rh_int_timer
r_struct
id|timer_list
id|rh_int_timer
suffix:semicolon
multiline_comment|/* intervall timer for rh interrupt EP */
)brace
suffix:semicolon
macro_line|#if 1
multiline_comment|/* USB HUB CONSTANTS (not OHCI-specific; see hub.h and USB spec) */
multiline_comment|/* destination of request */
DECL|macro|RH_INTERFACE
mdefine_line|#define RH_INTERFACE&t;&t;0x01
DECL|macro|RH_ENDPOINT
mdefine_line|#define RH_ENDPOINT&t;&t;0x02
DECL|macro|RH_OTHER
mdefine_line|#define RH_OTHER&t;&t;0x03
DECL|macro|RH_CLASS
mdefine_line|#define RH_CLASS&t;&t;0x20
DECL|macro|RH_VENDOR
mdefine_line|#define RH_VENDOR&t;&t;0x40
multiline_comment|/* Requests: bRequest &lt;&lt; 8 | bmRequestType */
DECL|macro|RH_GET_STATUS
mdefine_line|#define RH_GET_STATUS&t;&t;0x0080
DECL|macro|RH_CLEAR_FEATURE
mdefine_line|#define RH_CLEAR_FEATURE&t;0x0100
DECL|macro|RH_SET_FEATURE
mdefine_line|#define RH_SET_FEATURE&t;&t;0x0300
DECL|macro|RH_SET_ADDRESS
mdefine_line|#define RH_SET_ADDRESS&t;&t;0x0500
DECL|macro|RH_GET_DESCRIPTOR
mdefine_line|#define RH_GET_DESCRIPTOR&t;0x0680
DECL|macro|RH_SET_DESCRIPTOR
mdefine_line|#define RH_SET_DESCRIPTOR&t;0x0700
DECL|macro|RH_GET_CONFIGURATION
mdefine_line|#define RH_GET_CONFIGURATION&t;0x0880
DECL|macro|RH_SET_CONFIGURATION
mdefine_line|#define RH_SET_CONFIGURATION&t;0x0900
DECL|macro|RH_GET_STATE
mdefine_line|#define RH_GET_STATE&t;&t;0x0280
DECL|macro|RH_GET_INTERFACE
mdefine_line|#define RH_GET_INTERFACE&t;0x0A80
DECL|macro|RH_SET_INTERFACE
mdefine_line|#define RH_SET_INTERFACE&t;0x0B00
DECL|macro|RH_SYNC_FRAME
mdefine_line|#define RH_SYNC_FRAME&t;&t;0x0C80
multiline_comment|/* Our Vendor Specific Request */
DECL|macro|RH_SET_EP
mdefine_line|#define RH_SET_EP&t;&t;0x2000
multiline_comment|/* Hub port features */
DECL|macro|RH_PORT_CONNECTION
mdefine_line|#define RH_PORT_CONNECTION&t;0x00
DECL|macro|RH_PORT_ENABLE
mdefine_line|#define RH_PORT_ENABLE&t;&t;0x01
DECL|macro|RH_PORT_SUSPEND
mdefine_line|#define RH_PORT_SUSPEND&t;&t;0x02
DECL|macro|RH_PORT_OVER_CURRENT
mdefine_line|#define RH_PORT_OVER_CURRENT&t;0x03
DECL|macro|RH_PORT_RESET
mdefine_line|#define RH_PORT_RESET&t;&t;0x04
DECL|macro|RH_PORT_POWER
mdefine_line|#define RH_PORT_POWER&t;&t;0x08
DECL|macro|RH_PORT_LOW_SPEED
mdefine_line|#define RH_PORT_LOW_SPEED&t;0x09
DECL|macro|RH_C_PORT_CONNECTION
mdefine_line|#define RH_C_PORT_CONNECTION&t;0x10
DECL|macro|RH_C_PORT_ENABLE
mdefine_line|#define RH_C_PORT_ENABLE&t;0x11
DECL|macro|RH_C_PORT_SUSPEND
mdefine_line|#define RH_C_PORT_SUSPEND&t;0x12
DECL|macro|RH_C_PORT_OVER_CURRENT
mdefine_line|#define RH_C_PORT_OVER_CURRENT&t;0x13
DECL|macro|RH_C_PORT_RESET
mdefine_line|#define RH_C_PORT_RESET&t;&t;0x14
multiline_comment|/* Hub features */
DECL|macro|RH_C_HUB_LOCAL_POWER
mdefine_line|#define RH_C_HUB_LOCAL_POWER&t;0x00
DECL|macro|RH_C_HUB_OVER_CURRENT
mdefine_line|#define RH_C_HUB_OVER_CURRENT&t;0x01
DECL|macro|RH_DEVICE_REMOTE_WAKEUP
mdefine_line|#define RH_DEVICE_REMOTE_WAKEUP&t;0x00
DECL|macro|RH_ENDPOINT_STALL
mdefine_line|#define RH_ENDPOINT_STALL&t;0x01
macro_line|#endif
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* struct for each HC &n; */
DECL|macro|MAX_TRANS
mdefine_line|#define MAX_TRANS&t;32
DECL|struct|td
r_typedef
r_struct
id|td
(brace
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
DECL|member|len
id|__u16
id|len
suffix:semicolon
DECL|member|iso_index
id|__u16
id|iso_index
suffix:semicolon
DECL|typedef|td_t
)brace
id|td_t
suffix:semicolon
DECL|struct|td_array
r_typedef
r_struct
id|td_array
(brace
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|td
id|td_t
id|td
(braket
id|MAX_TRANS
)braket
suffix:semicolon
DECL|typedef|td_array_t
)brace
id|td_array_t
suffix:semicolon
DECL|struct|hci
r_typedef
r_struct
id|hci
(brace
DECL|member|rh
r_struct
id|virt_root_hub
id|rh
suffix:semicolon
multiline_comment|/* roothub */
DECL|member|waitq
id|wait_queue_head_t
id|waitq
suffix:semicolon
multiline_comment|/* deletion of URBs and devices needs a waitqueue */
DECL|member|active
r_int
id|active
suffix:semicolon
multiline_comment|/* HC is operating */
DECL|member|ctrl_list
r_struct
id|list_head
id|ctrl_list
suffix:semicolon
multiline_comment|/* set of ctrl endpoints */
DECL|member|bulk_list
r_struct
id|list_head
id|bulk_list
suffix:semicolon
multiline_comment|/* set of bulk endpoints */
DECL|member|iso_list
r_struct
id|list_head
id|iso_list
suffix:semicolon
multiline_comment|/* set of isoc endpoints */
DECL|member|intr_list
r_struct
id|list_head
id|intr_list
suffix:semicolon
multiline_comment|/* ordered (tree) set of int endpoints */
DECL|member|del_list
r_struct
id|list_head
id|del_list
suffix:semicolon
multiline_comment|/* set of entpoints to be deleted */
DECL|member|td_array
id|td_array_t
op_star
id|td_array
suffix:semicolon
DECL|member|a_td_array
id|td_array_t
id|a_td_array
suffix:semicolon
DECL|member|i_td_array
id|td_array_t
id|i_td_array
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|hci_hcd_list
r_struct
id|list_head
id|hci_hcd_list
suffix:semicolon
multiline_comment|/* list of all hci_hcd */
DECL|member|bus
r_struct
id|usb_bus
op_star
id|bus
suffix:semicolon
multiline_comment|/* our bus */
singleline_comment|//&t;int trans;&t;&t;&t;/* number of transactions pending */
DECL|member|active_urbs
r_int
id|active_urbs
suffix:semicolon
DECL|member|active_trans
r_int
id|active_trans
suffix:semicolon
DECL|member|frame_number
r_int
id|frame_number
suffix:semicolon
multiline_comment|/* frame number */
DECL|member|hp
id|hcipriv_t
id|hp
suffix:semicolon
multiline_comment|/* individual part of hc type */
DECL|member|nakCnt
r_int
id|nakCnt
suffix:semicolon
DECL|member|last_packet_nak
r_int
id|last_packet_nak
suffix:semicolon
DECL|typedef|hci_t
)brace
id|hci_t
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* condition (error) CC codes and mapping OHCI like&n; */
DECL|macro|TD_CC_NOERROR
mdefine_line|#define TD_CC_NOERROR&t;&t;0x00
DECL|macro|TD_CC_CRC
mdefine_line|#define TD_CC_CRC&t;&t;0x01
DECL|macro|TD_CC_BITSTUFFING
mdefine_line|#define TD_CC_BITSTUFFING&t;0x02
DECL|macro|TD_CC_DATATOGGLEM
mdefine_line|#define TD_CC_DATATOGGLEM&t;0x03
DECL|macro|TD_CC_STALL
mdefine_line|#define TD_CC_STALL&t;&t;0x04
DECL|macro|TD_DEVNOTRESP
mdefine_line|#define TD_DEVNOTRESP&t;&t;0x05
DECL|macro|TD_PIDCHECKFAIL
mdefine_line|#define TD_PIDCHECKFAIL&t;&t;0x06
DECL|macro|TD_UNEXPECTEDPID
mdefine_line|#define TD_UNEXPECTEDPID&t;0x07
DECL|macro|TD_DATAOVERRUN
mdefine_line|#define TD_DATAOVERRUN&t;&t;0x08
DECL|macro|TD_DATAUNDERRUN
mdefine_line|#define TD_DATAUNDERRUN&t;&t;0x09
DECL|macro|TD_BUFFEROVERRUN
mdefine_line|#define TD_BUFFEROVERRUN&t;0x0C
DECL|macro|TD_BUFFERUNDERRUN
mdefine_line|#define TD_BUFFERUNDERRUN&t;0x0D
DECL|macro|TD_NOTACCESSED
mdefine_line|#define TD_NOTACCESSED&t;&t;0x0F
multiline_comment|/* urb interface functions */
r_static
r_int
id|hci_get_current_frame_number
(paren
r_struct
id|usb_device
op_star
id|usb_dev
)paren
suffix:semicolon
r_static
r_int
id|hci_unlink_urb
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
r_static
r_int
id|qu_queue_urb
(paren
id|hci_t
op_star
id|hci
comma
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
multiline_comment|/* root hub */
r_static
r_int
id|rh_init_int_timer
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
r_static
r_int
id|rh_submit_urb
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
r_static
r_int
id|rh_unlink_urb
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
multiline_comment|/* schedule functions */
r_static
r_int
id|sh_add_packet
(paren
id|hci_t
op_star
id|hci
comma
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
multiline_comment|/* hc specific functions */
r_static
r_inline
r_void
id|hc_flush_data_cache
(paren
id|hci_t
op_star
id|hci
comma
r_void
op_star
id|data
comma
r_int
id|len
)paren
suffix:semicolon
r_static
r_inline
r_int
id|hc_parse_trans
(paren
id|hci_t
op_star
id|hci
comma
r_int
op_star
id|actbytes
comma
id|__u8
op_star
id|data
comma
r_int
op_star
id|cc
comma
r_int
op_star
id|toggle
comma
r_int
id|length
comma
r_int
id|pid
comma
r_int
id|urb_state
)paren
suffix:semicolon
r_static
r_inline
r_int
id|hc_add_trans
(paren
id|hci_t
op_star
id|hci
comma
r_int
id|len
comma
r_void
op_star
id|data
comma
r_int
id|toggle
comma
r_int
id|maxps
comma
r_int
id|slow
comma
r_int
id|endpoint
comma
r_int
id|address
comma
r_int
id|pid
comma
r_int
id|format
comma
r_int
id|urb_state
)paren
suffix:semicolon
r_static
r_void
id|hc_start_int
(paren
id|hci_t
op_star
id|hci
)paren
suffix:semicolon
r_static
r_void
id|hc_stop_int
(paren
id|hci_t
op_star
id|hci
)paren
suffix:semicolon
r_static
r_void
id|SL811Write
(paren
id|hci_t
op_star
id|hci
comma
r_char
id|offset
comma
r_char
id|data
)paren
suffix:semicolon
multiline_comment|/* debug| print the main components of an URB     &n; * small: 0) header + data packets 1) just header */
DECL|function|urb_print
r_static
r_void
id|urb_print
(paren
r_struct
id|urb
op_star
id|urb
comma
r_char
op_star
id|str
comma
r_int
id|small
)paren
(brace
r_int
r_int
id|pipe
op_assign
id|urb-&gt;pipe
suffix:semicolon
r_int
id|i
comma
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb-&gt;dev
op_logical_or
op_logical_neg
id|urb-&gt;dev-&gt;bus
)paren
(brace
id|dbg
(paren
l_string|&quot;%s URB: no dev&quot;
comma
id|str
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;%s URB:[%4x] dev:%2d,ep:%2d-%c,type:%s,flags:%4x,len:%d/%d,stat:%d(%x)&bslash;n&quot;
comma
id|str
comma
id|hci_get_current_frame_number
(paren
id|urb-&gt;dev
)paren
comma
id|usb_pipedevice
(paren
id|pipe
)paren
comma
id|usb_pipeendpoint
(paren
id|pipe
)paren
comma
id|usb_pipeout
(paren
id|pipe
)paren
ques
c_cond
l_char|&squot;O&squot;
suffix:colon
l_char|&squot;I&squot;
comma
id|usb_pipetype
(paren
id|pipe
)paren
OL
l_int|2
ques
c_cond
(paren
id|usb_pipeint
(paren
id|pipe
)paren
ques
c_cond
l_string|&quot;INTR&quot;
suffix:colon
l_string|&quot;ISOC&quot;
)paren
suffix:colon
(paren
id|usb_pipecontrol
(paren
id|pipe
)paren
ques
c_cond
l_string|&quot;CTRL&quot;
suffix:colon
l_string|&quot;BULK&quot;
)paren
comma
id|urb-&gt;transfer_flags
comma
id|urb-&gt;actual_length
comma
id|urb-&gt;transfer_buffer_length
comma
id|urb-&gt;status
comma
id|urb-&gt;status
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|small
)paren
(brace
r_if
c_cond
(paren
id|usb_pipecontrol
(paren
id|pipe
)paren
)paren
(brace
id|printk
(paren
id|__FILE__
l_string|&quot;: cmd(8):&quot;
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|printk
(paren
l_string|&quot; %02x&quot;
comma
(paren
(paren
id|__u8
op_star
)paren
id|urb-&gt;setup_packet
)paren
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|urb-&gt;transfer_buffer_length
OG
l_int|0
op_logical_and
id|urb-&gt;transfer_buffer
)paren
(brace
id|printk
(paren
id|__FILE__
l_string|&quot;: data(%d/%d):&quot;
comma
id|urb-&gt;actual_length
comma
id|urb-&gt;transfer_buffer_length
)paren
suffix:semicolon
id|len
op_assign
id|usb_pipeout
(paren
id|pipe
)paren
ques
c_cond
id|urb
op_member_access_from_pointer
id|transfer_buffer_length
suffix:colon
id|urb-&gt;actual_length
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
l_int|2096
op_logical_and
id|i
OL
id|len
suffix:semicolon
id|i
op_increment
)paren
id|printk
(paren
l_string|&quot; %02x&quot;
comma
(paren
(paren
id|__u8
op_star
)paren
id|urb-&gt;transfer_buffer
)paren
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;%s stat:%d&bslash;n&quot;
comma
id|i
OL
id|len
ques
c_cond
l_string|&quot;...&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|urb-&gt;status
)paren
suffix:semicolon
)brace
)brace
)brace
eof
