macro_line|#ifndef __LINUX_ETRAX_USB_H
DECL|macro|__LINUX_ETRAX_USB_H
mdefine_line|#define __LINUX_ETRAX_USB_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/list.h&gt;
DECL|struct|USB_IN_Desc
r_typedef
r_struct
id|USB_IN_Desc
(brace
DECL|member|sw_len
r_volatile
id|__u16
id|sw_len
suffix:semicolon
DECL|member|command
r_volatile
id|__u16
id|command
suffix:semicolon
DECL|member|next
r_volatile
r_int
r_int
id|next
suffix:semicolon
DECL|member|buf
r_volatile
r_int
r_int
id|buf
suffix:semicolon
DECL|member|hw_len
r_volatile
id|__u16
id|hw_len
suffix:semicolon
DECL|member|status
r_volatile
id|__u16
id|status
suffix:semicolon
DECL|typedef|USB_IN_Desc_t
)brace
id|USB_IN_Desc_t
suffix:semicolon
DECL|struct|USB_SB_Desc
r_typedef
r_struct
id|USB_SB_Desc
(brace
DECL|member|sw_len
r_volatile
id|__u16
id|sw_len
suffix:semicolon
DECL|member|command
r_volatile
id|__u16
id|command
suffix:semicolon
DECL|member|next
r_volatile
r_int
r_int
id|next
suffix:semicolon
DECL|member|buf
r_volatile
r_int
r_int
id|buf
suffix:semicolon
DECL|member|dummy
id|__u32
id|dummy
suffix:semicolon
DECL|typedef|USB_SB_Desc_t
)brace
id|USB_SB_Desc_t
suffix:semicolon
DECL|struct|USB_EP_Desc
r_typedef
r_struct
id|USB_EP_Desc
(brace
DECL|member|hw_len
r_volatile
id|__u16
id|hw_len
suffix:semicolon
DECL|member|command
r_volatile
id|__u16
id|command
suffix:semicolon
DECL|member|sub
r_volatile
r_int
r_int
id|sub
suffix:semicolon
DECL|member|next
r_volatile
r_int
r_int
id|next
suffix:semicolon
DECL|member|dummy
id|__u32
id|dummy
suffix:semicolon
DECL|typedef|USB_EP_Desc_t
)brace
id|USB_EP_Desc_t
suffix:semicolon
DECL|struct|virt_root_hub
r_struct
id|virt_root_hub
(brace
DECL|member|devnum
r_int
id|devnum
suffix:semicolon
DECL|member|urb
r_void
op_star
id|urb
suffix:semicolon
DECL|member|int_addr
r_void
op_star
id|int_addr
suffix:semicolon
DECL|member|send
r_int
id|send
suffix:semicolon
DECL|member|interval
r_int
id|interval
suffix:semicolon
DECL|member|numports
r_int
id|numports
suffix:semicolon
DECL|member|rh_int_timer
r_struct
id|timer_list
id|rh_int_timer
suffix:semicolon
DECL|member|wPortChange_1
r_volatile
id|__u16
id|wPortChange_1
suffix:semicolon
DECL|member|wPortChange_2
r_volatile
id|__u16
id|wPortChange_2
suffix:semicolon
DECL|member|prev_wPortStatus_1
r_volatile
id|__u16
id|prev_wPortStatus_1
suffix:semicolon
DECL|member|prev_wPortStatus_2
r_volatile
id|__u16
id|prev_wPortStatus_2
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|etrax_usb_intr_traffic
r_struct
id|etrax_usb_intr_traffic
(brace
DECL|member|sleeping
r_int
id|sleeping
suffix:semicolon
DECL|member|error
r_int
id|error
suffix:semicolon
DECL|member|wq
r_struct
id|wait_queue
op_star
id|wq
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|etrax_usb_hc
r_typedef
r_struct
id|etrax_usb_hc
(brace
DECL|member|bus
r_struct
id|usb_bus
op_star
id|bus
suffix:semicolon
DECL|member|rh
r_struct
id|virt_root_hub
id|rh
suffix:semicolon
DECL|member|intr
r_struct
id|etrax_usb_intr_traffic
id|intr
suffix:semicolon
DECL|typedef|etrax_hc_t
)brace
id|etrax_hc_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|STARTED
id|STARTED
comma
DECL|enumerator|NOT_STARTED
id|NOT_STARTED
comma
DECL|enumerator|UNLINK
id|UNLINK
comma
DECL|enumerator|TRANSFER_DONE
id|TRANSFER_DONE
comma
DECL|enumerator|WAITING_FOR_DESCR_INTR
id|WAITING_FOR_DESCR_INTR
DECL|typedef|etrax_usb_urb_state_t
)brace
id|etrax_usb_urb_state_t
suffix:semicolon
DECL|struct|etrax_usb_urb_priv
r_typedef
r_struct
id|etrax_usb_urb_priv
(brace
multiline_comment|/* The first_sb field is used for freeing all SB descriptors belonging&n;&t;   to an urb. The corresponding ep descriptor&squot;s sub pointer cannot be&n;&t;   used for this since the DMA advances the sub pointer as it processes&n;&t;   the sb list. */
DECL|member|first_sb
id|USB_SB_Desc_t
op_star
id|first_sb
suffix:semicolon
multiline_comment|/* The last_sb field referes to the last SB descriptor that belongs to&n;&t;   this urb. This is important to know so we can free the SB descriptors&n;&t;   that ranges between first_sb and last_sb. */
DECL|member|last_sb
id|USB_SB_Desc_t
op_star
id|last_sb
suffix:semicolon
multiline_comment|/* The rx_offset field is used in ctrl and bulk traffic to keep track&n;&t;   of the offset in the urb&squot;s transfer_buffer where incoming data should be&n;&t;   copied to. */
DECL|member|rx_offset
id|__u32
id|rx_offset
suffix:semicolon
multiline_comment|/* Counter used in isochronous transfers to keep track of the&n;&t;   number of packets received/transmitted.  */
DECL|member|isoc_packet_counter
id|__u32
id|isoc_packet_counter
suffix:semicolon
multiline_comment|/* This field is used to pass information about the urb&squot;s current state between&n;&t;   the various interrupt handlers (thus marked volatile). */
DECL|member|urb_state
r_volatile
id|etrax_usb_urb_state_t
id|urb_state
suffix:semicolon
multiline_comment|/* Connection between the submitted urb and ETRAX epid number */
DECL|member|epid
id|__u8
id|epid
suffix:semicolon
multiline_comment|/* The rx_data_list field is used for periodic traffic, to hold&n;&t;   received data for later processing in the the complete_urb functions,&n;&t;   where the data us copied to the urb&squot;s transfer_buffer. Basically, we&n;&t;   use this intermediate storage because we don&squot;t know when it&squot;s safe to&n;&t;   reuse the transfer_buffer (FIXME?). */
DECL|member|rx_data_list
r_struct
id|list_head
id|rx_data_list
suffix:semicolon
DECL|typedef|etrax_urb_priv_t
)brace
id|etrax_urb_priv_t
suffix:semicolon
multiline_comment|/* This struct is for passing data from the top half to the bottom half. */
DECL|struct|usb_interrupt_registers
r_typedef
r_struct
id|usb_interrupt_registers
(brace
DECL|member|hc
id|etrax_hc_t
op_star
id|hc
suffix:semicolon
DECL|member|r_usb_epid_attn
id|__u32
id|r_usb_epid_attn
suffix:semicolon
DECL|member|r_usb_status
id|__u8
id|r_usb_status
suffix:semicolon
DECL|member|r_usb_rh_port_status_1
id|__u16
id|r_usb_rh_port_status_1
suffix:semicolon
DECL|member|r_usb_rh_port_status_2
id|__u16
id|r_usb_rh_port_status_2
suffix:semicolon
DECL|member|r_usb_irq_mask_read
id|__u32
id|r_usb_irq_mask_read
suffix:semicolon
DECL|member|r_usb_fm_number
id|__u32
id|r_usb_fm_number
suffix:semicolon
DECL|member|usb_bh
r_struct
id|work_struct
id|usb_bh
suffix:semicolon
DECL|typedef|usb_interrupt_registers_t
)brace
id|usb_interrupt_registers_t
suffix:semicolon
multiline_comment|/* This struct is for passing data from the isoc top half to the isoc bottom half. */
DECL|struct|usb_isoc_complete_data
r_typedef
r_struct
id|usb_isoc_complete_data
(brace
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
DECL|member|usb_bh
r_struct
id|work_struct
id|usb_bh
suffix:semicolon
DECL|typedef|usb_isoc_complete_data_t
)brace
id|usb_isoc_complete_data_t
suffix:semicolon
multiline_comment|/* This struct holds data we get from the rx descriptors for DMA channel 9&n;   for periodic traffic (intr and isoc). */
DECL|struct|rx_data
r_typedef
r_struct
id|rx_data
(brace
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|typedef|rx_data_t
)brace
id|rx_data_t
suffix:semicolon
DECL|struct|urb_entry
r_typedef
r_struct
id|urb_entry
(brace
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|typedef|urb_entry_t
)brace
id|urb_entry_t
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------------&n;   Virtual Root HUB&n;   ------------------------------------------------------------------------- */
multiline_comment|/* destination of request */
DECL|macro|RH_INTERFACE
mdefine_line|#define RH_INTERFACE               0x01
DECL|macro|RH_ENDPOINT
mdefine_line|#define RH_ENDPOINT                0x02
DECL|macro|RH_OTHER
mdefine_line|#define RH_OTHER                   0x03
DECL|macro|RH_CLASS
mdefine_line|#define RH_CLASS                   0x20
DECL|macro|RH_VENDOR
mdefine_line|#define RH_VENDOR                  0x40
multiline_comment|/* Requests: bRequest &lt;&lt; 8 | bmRequestType */
DECL|macro|RH_GET_STATUS
mdefine_line|#define RH_GET_STATUS           0x0080
DECL|macro|RH_CLEAR_FEATURE
mdefine_line|#define RH_CLEAR_FEATURE        0x0100
DECL|macro|RH_SET_FEATURE
mdefine_line|#define RH_SET_FEATURE          0x0300
DECL|macro|RH_SET_ADDRESS
mdefine_line|#define RH_SET_ADDRESS&t;&t;0x0500
DECL|macro|RH_GET_DESCRIPTOR
mdefine_line|#define RH_GET_DESCRIPTOR&t;0x0680
DECL|macro|RH_SET_DESCRIPTOR
mdefine_line|#define RH_SET_DESCRIPTOR       0x0700
DECL|macro|RH_GET_CONFIGURATION
mdefine_line|#define RH_GET_CONFIGURATION&t;0x0880
DECL|macro|RH_SET_CONFIGURATION
mdefine_line|#define RH_SET_CONFIGURATION&t;0x0900
DECL|macro|RH_GET_STATE
mdefine_line|#define RH_GET_STATE            0x0280
DECL|macro|RH_GET_INTERFACE
mdefine_line|#define RH_GET_INTERFACE        0x0A80
DECL|macro|RH_SET_INTERFACE
mdefine_line|#define RH_SET_INTERFACE        0x0B00
DECL|macro|RH_SYNC_FRAME
mdefine_line|#define RH_SYNC_FRAME           0x0C80
multiline_comment|/* Our Vendor Specific Request */
DECL|macro|RH_SET_EP
mdefine_line|#define RH_SET_EP               0x2000
multiline_comment|/* Hub port features */
DECL|macro|RH_PORT_CONNECTION
mdefine_line|#define RH_PORT_CONNECTION         0x00
DECL|macro|RH_PORT_ENABLE
mdefine_line|#define RH_PORT_ENABLE             0x01
DECL|macro|RH_PORT_SUSPEND
mdefine_line|#define RH_PORT_SUSPEND            0x02
DECL|macro|RH_PORT_OVER_CURRENT
mdefine_line|#define RH_PORT_OVER_CURRENT       0x03
DECL|macro|RH_PORT_RESET
mdefine_line|#define RH_PORT_RESET              0x04
DECL|macro|RH_PORT_POWER
mdefine_line|#define RH_PORT_POWER              0x08
DECL|macro|RH_PORT_LOW_SPEED
mdefine_line|#define RH_PORT_LOW_SPEED          0x09
DECL|macro|RH_C_PORT_CONNECTION
mdefine_line|#define RH_C_PORT_CONNECTION       0x10
DECL|macro|RH_C_PORT_ENABLE
mdefine_line|#define RH_C_PORT_ENABLE           0x11
DECL|macro|RH_C_PORT_SUSPEND
mdefine_line|#define RH_C_PORT_SUSPEND          0x12
DECL|macro|RH_C_PORT_OVER_CURRENT
mdefine_line|#define RH_C_PORT_OVER_CURRENT     0x13
DECL|macro|RH_C_PORT_RESET
mdefine_line|#define RH_C_PORT_RESET            0x14
multiline_comment|/* Hub features */
DECL|macro|RH_C_HUB_LOCAL_POWER
mdefine_line|#define RH_C_HUB_LOCAL_POWER       0x00
DECL|macro|RH_C_HUB_OVER_CURRENT
mdefine_line|#define RH_C_HUB_OVER_CURRENT      0x01
DECL|macro|RH_DEVICE_REMOTE_WAKEUP
mdefine_line|#define RH_DEVICE_REMOTE_WAKEUP    0x00
DECL|macro|RH_ENDPOINT_STALL
mdefine_line|#define RH_ENDPOINT_STALL          0x01
multiline_comment|/* Our Vendor Specific feature */
DECL|macro|RH_REMOVE_EP
mdefine_line|#define RH_REMOVE_EP               0x00
DECL|macro|RH_ACK
mdefine_line|#define RH_ACK                     0x01
DECL|macro|RH_REQ_ERR
mdefine_line|#define RH_REQ_ERR                 -1
DECL|macro|RH_NACK
mdefine_line|#define RH_NACK                    0x00
multiline_comment|/* Field definitions for */
DECL|macro|USB_IN_command__eol__BITNR
mdefine_line|#define USB_IN_command__eol__BITNR      0 /* command macros */
DECL|macro|USB_IN_command__eol__WIDTH
mdefine_line|#define USB_IN_command__eol__WIDTH      1
DECL|macro|USB_IN_command__eol__no
mdefine_line|#define USB_IN_command__eol__no         0
DECL|macro|USB_IN_command__eol__yes
mdefine_line|#define USB_IN_command__eol__yes        1
DECL|macro|USB_IN_command__intr__BITNR
mdefine_line|#define USB_IN_command__intr__BITNR     3
DECL|macro|USB_IN_command__intr__WIDTH
mdefine_line|#define USB_IN_command__intr__WIDTH     1
DECL|macro|USB_IN_command__intr__no
mdefine_line|#define USB_IN_command__intr__no        0
DECL|macro|USB_IN_command__intr__yes
mdefine_line|#define USB_IN_command__intr__yes       1
DECL|macro|USB_IN_status__eop__BITNR
mdefine_line|#define USB_IN_status__eop__BITNR       1 /* status macros. */
DECL|macro|USB_IN_status__eop__WIDTH
mdefine_line|#define USB_IN_status__eop__WIDTH       1
DECL|macro|USB_IN_status__eop__no
mdefine_line|#define USB_IN_status__eop__no          0
DECL|macro|USB_IN_status__eop__yes
mdefine_line|#define USB_IN_status__eop__yes         1
DECL|macro|USB_IN_status__eot__BITNR
mdefine_line|#define USB_IN_status__eot__BITNR       5
DECL|macro|USB_IN_status__eot__WIDTH
mdefine_line|#define USB_IN_status__eot__WIDTH       1
DECL|macro|USB_IN_status__eot__no
mdefine_line|#define USB_IN_status__eot__no          0
DECL|macro|USB_IN_status__eot__yes
mdefine_line|#define USB_IN_status__eot__yes         1
DECL|macro|USB_IN_status__error__BITNR
mdefine_line|#define USB_IN_status__error__BITNR     6
DECL|macro|USB_IN_status__error__WIDTH
mdefine_line|#define USB_IN_status__error__WIDTH     1
DECL|macro|USB_IN_status__error__no
mdefine_line|#define USB_IN_status__error__no        0
DECL|macro|USB_IN_status__error__yes
mdefine_line|#define USB_IN_status__error__yes       1
DECL|macro|USB_IN_status__nodata__BITNR
mdefine_line|#define USB_IN_status__nodata__BITNR    7
DECL|macro|USB_IN_status__nodata__WIDTH
mdefine_line|#define USB_IN_status__nodata__WIDTH    1
DECL|macro|USB_IN_status__nodata__no
mdefine_line|#define USB_IN_status__nodata__no       0
DECL|macro|USB_IN_status__nodata__yes
mdefine_line|#define USB_IN_status__nodata__yes      1
DECL|macro|USB_IN_status__epid__BITNR
mdefine_line|#define USB_IN_status__epid__BITNR      8
DECL|macro|USB_IN_status__epid__WIDTH
mdefine_line|#define USB_IN_status__epid__WIDTH      5
DECL|macro|USB_EP_command__eol__BITNR
mdefine_line|#define USB_EP_command__eol__BITNR      0
DECL|macro|USB_EP_command__eol__WIDTH
mdefine_line|#define USB_EP_command__eol__WIDTH      1
DECL|macro|USB_EP_command__eol__no
mdefine_line|#define USB_EP_command__eol__no         0
DECL|macro|USB_EP_command__eol__yes
mdefine_line|#define USB_EP_command__eol__yes        1
DECL|macro|USB_EP_command__eof__BITNR
mdefine_line|#define USB_EP_command__eof__BITNR      1
DECL|macro|USB_EP_command__eof__WIDTH
mdefine_line|#define USB_EP_command__eof__WIDTH      1
DECL|macro|USB_EP_command__eof__no
mdefine_line|#define USB_EP_command__eof__no         0
DECL|macro|USB_EP_command__eof__yes
mdefine_line|#define USB_EP_command__eof__yes        1
DECL|macro|USB_EP_command__intr__BITNR
mdefine_line|#define USB_EP_command__intr__BITNR     3
DECL|macro|USB_EP_command__intr__WIDTH
mdefine_line|#define USB_EP_command__intr__WIDTH     1
DECL|macro|USB_EP_command__intr__no
mdefine_line|#define USB_EP_command__intr__no        0
DECL|macro|USB_EP_command__intr__yes
mdefine_line|#define USB_EP_command__intr__yes       1
DECL|macro|USB_EP_command__enable__BITNR
mdefine_line|#define USB_EP_command__enable__BITNR   4
DECL|macro|USB_EP_command__enable__WIDTH
mdefine_line|#define USB_EP_command__enable__WIDTH   1
DECL|macro|USB_EP_command__enable__no
mdefine_line|#define USB_EP_command__enable__no      0
DECL|macro|USB_EP_command__enable__yes
mdefine_line|#define USB_EP_command__enable__yes     1
DECL|macro|USB_EP_command__hw_valid__BITNR
mdefine_line|#define USB_EP_command__hw_valid__BITNR 5
DECL|macro|USB_EP_command__hw_valid__WIDTH
mdefine_line|#define USB_EP_command__hw_valid__WIDTH 1
DECL|macro|USB_EP_command__hw_valid__no
mdefine_line|#define USB_EP_command__hw_valid__no    0
DECL|macro|USB_EP_command__hw_valid__yes
mdefine_line|#define USB_EP_command__hw_valid__yes   1
DECL|macro|USB_EP_command__epid__BITNR
mdefine_line|#define USB_EP_command__epid__BITNR     8
DECL|macro|USB_EP_command__epid__WIDTH
mdefine_line|#define USB_EP_command__epid__WIDTH     5
DECL|macro|USB_SB_command__eol__BITNR
mdefine_line|#define USB_SB_command__eol__BITNR      0 /* command macros. */
DECL|macro|USB_SB_command__eol__WIDTH
mdefine_line|#define USB_SB_command__eol__WIDTH      1
DECL|macro|USB_SB_command__eol__no
mdefine_line|#define USB_SB_command__eol__no         0
DECL|macro|USB_SB_command__eol__yes
mdefine_line|#define USB_SB_command__eol__yes        1
DECL|macro|USB_SB_command__eot__BITNR
mdefine_line|#define USB_SB_command__eot__BITNR      1
DECL|macro|USB_SB_command__eot__WIDTH
mdefine_line|#define USB_SB_command__eot__WIDTH      1
DECL|macro|USB_SB_command__eot__no
mdefine_line|#define USB_SB_command__eot__no         0
DECL|macro|USB_SB_command__eot__yes
mdefine_line|#define USB_SB_command__eot__yes        1
DECL|macro|USB_SB_command__intr__BITNR
mdefine_line|#define USB_SB_command__intr__BITNR     3
DECL|macro|USB_SB_command__intr__WIDTH
mdefine_line|#define USB_SB_command__intr__WIDTH     1
DECL|macro|USB_SB_command__intr__no
mdefine_line|#define USB_SB_command__intr__no        0
DECL|macro|USB_SB_command__intr__yes
mdefine_line|#define USB_SB_command__intr__yes       1
DECL|macro|USB_SB_command__tt__BITNR
mdefine_line|#define USB_SB_command__tt__BITNR       4
DECL|macro|USB_SB_command__tt__WIDTH
mdefine_line|#define USB_SB_command__tt__WIDTH       2
DECL|macro|USB_SB_command__tt__zout
mdefine_line|#define USB_SB_command__tt__zout        0
DECL|macro|USB_SB_command__tt__in
mdefine_line|#define USB_SB_command__tt__in          1
DECL|macro|USB_SB_command__tt__out
mdefine_line|#define USB_SB_command__tt__out         2
DECL|macro|USB_SB_command__tt__setup
mdefine_line|#define USB_SB_command__tt__setup       3
DECL|macro|USB_SB_command__rem__BITNR
mdefine_line|#define USB_SB_command__rem__BITNR      8
DECL|macro|USB_SB_command__rem__WIDTH
mdefine_line|#define USB_SB_command__rem__WIDTH      6
DECL|macro|USB_SB_command__full__BITNR
mdefine_line|#define USB_SB_command__full__BITNR     6
DECL|macro|USB_SB_command__full__WIDTH
mdefine_line|#define USB_SB_command__full__WIDTH     1
DECL|macro|USB_SB_command__full__no
mdefine_line|#define USB_SB_command__full__no        0
DECL|macro|USB_SB_command__full__yes
mdefine_line|#define USB_SB_command__full__yes       1
macro_line|#endif
eof
