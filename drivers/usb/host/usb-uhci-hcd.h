macro_line|#ifndef __LINUX_USB_UHCI_H
DECL|macro|__LINUX_USB_UHCI_H
mdefine_line|#define __LINUX_USB_UHCI_H
multiline_comment|/*  $Id: usb-uhci-hcd.h,v 1.1 2002/05/14 20:36:57 acher Exp $ */
macro_line|#ifndef CONFIG_PCI
macro_line|#error &quot;UHCI needs the CONFIG_PCI option!&quot;
macro_line|#endif
DECL|macro|MODNAME
mdefine_line|#define MODNAME &quot;usb-uhci-hcd&quot;
DECL|macro|UHCI_LATENCY_TIMER
mdefine_line|#define UHCI_LATENCY_TIMER 0
DECL|function|uhci_wait_ms
r_static
id|__inline__
r_void
id|uhci_wait_ms
c_func
(paren
r_int
r_int
id|ms
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|in_interrupt
c_func
(paren
)paren
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
op_plus
id|ms
op_star
id|HZ
op_div
l_int|1000
)paren
suffix:semicolon
)brace
r_else
id|mdelay
c_func
(paren
id|ms
)paren
suffix:semicolon
)brace
multiline_comment|/* Command register */
DECL|macro|USBCMD
mdefine_line|#define   USBCMD&t;&t;0
DECL|macro|USBCMD_RS
mdefine_line|#define   USBCMD_RS&t;&t;0x0001&t;/* Run/Stop */
DECL|macro|USBCMD_HCRESET
mdefine_line|#define   USBCMD_HCRESET&t;0x0002&t;/* Host reset */
DECL|macro|USBCMD_GRESET
mdefine_line|#define   USBCMD_GRESET&t;&t;0x0004&t;/* Global reset */
DECL|macro|USBCMD_EGSM
mdefine_line|#define   USBCMD_EGSM&t;&t;0x0008&t;/* Global Suspend Mode */
DECL|macro|USBCMD_FGR
mdefine_line|#define   USBCMD_FGR&t;&t;0x0010&t;/* Force Global Resume */
DECL|macro|USBCMD_SWDBG
mdefine_line|#define   USBCMD_SWDBG&t;&t;0x0020&t;/* SW Debug mode */
DECL|macro|USBCMD_CF
mdefine_line|#define   USBCMD_CF&t;&t;0x0040&t;/* Config Flag (sw only) */
DECL|macro|USBCMD_MAXP
mdefine_line|#define   USBCMD_MAXP&t;&t;0x0080&t;/* Max Packet (0 = 32, 1 = 64) */
multiline_comment|/* Status register */
DECL|macro|USBSTS
mdefine_line|#define   USBSTS&t;&t;2
DECL|macro|USBSTS_USBINT
mdefine_line|#define   USBSTS_USBINT&t;&t;0x0001&t;/* Interrupt due to IOC */
DECL|macro|USBSTS_ERROR
mdefine_line|#define   USBSTS_ERROR&t;&t;0x0002&t;/* Interrupt due to error */
DECL|macro|USBSTS_RD
mdefine_line|#define   USBSTS_RD&t;&t;0x0004&t;/* Resume Detect */
DECL|macro|USBSTS_HSE
mdefine_line|#define   USBSTS_HSE&t;&t;0x0008&t;/* Host System Error - basically PCI problems */
DECL|macro|USBSTS_HCPE
mdefine_line|#define   USBSTS_HCPE&t;&t;0x0010&t;/* Host Controller Process Error - the scripts were buggy */
DECL|macro|USBSTS_HCH
mdefine_line|#define   USBSTS_HCH&t;&t;0x0020&t;/* HC Halted */
multiline_comment|/* Interrupt enable register */
DECL|macro|USBINTR
mdefine_line|#define   USBINTR&t;&t;4
DECL|macro|USBINTR_TIMEOUT
mdefine_line|#define   USBINTR_TIMEOUT&t;0x0001&t;/* Timeout/CRC error enable */
DECL|macro|USBINTR_RESUME
mdefine_line|#define   USBINTR_RESUME&t;0x0002&t;/* Resume interrupt enable */
DECL|macro|USBINTR_IOC
mdefine_line|#define   USBINTR_IOC&t;&t;0x0004&t;/* Interrupt On Complete enable */
DECL|macro|USBINTR_SP
mdefine_line|#define   USBINTR_SP&t;&t;0x0008&t;/* Short packet interrupt enable */
DECL|macro|USBFRNUM
mdefine_line|#define USBFRNUM&t;6
DECL|macro|USBFLBASEADD
mdefine_line|#define USBFLBASEADD&t;8
DECL|macro|USBSOF
mdefine_line|#define USBSOF&t;&t;12
multiline_comment|/* USB port status and control registers */
DECL|macro|USBPORTSC1
mdefine_line|#define   USBPORTSC1&t;16
DECL|macro|USBPORTSC2
mdefine_line|#define   USBPORTSC2&t;18
DECL|macro|USBPORTSC_CCS
mdefine_line|#define   USBPORTSC_CCS&t;&t;0x0001&t;/* Current Connect Status (&quot;device present&quot;) */
DECL|macro|USBPORTSC_CSC
mdefine_line|#define   USBPORTSC_CSC&t;&t;0x0002&t;/* Connect Status Change */
DECL|macro|USBPORTSC_PE
mdefine_line|#define   USBPORTSC_PE&t;&t;0x0004&t;/* Port Enable */
DECL|macro|USBPORTSC_PEC
mdefine_line|#define   USBPORTSC_PEC&t;&t;0x0008&t;/* Port Enable Change */
DECL|macro|USBPORTSC_LS
mdefine_line|#define   USBPORTSC_LS&t;&t;0x0030&t;/* Line Status */
DECL|macro|USBPORTSC_RD
mdefine_line|#define   USBPORTSC_RD&t;&t;0x0040&t;/* Resume Detect */
DECL|macro|USBPORTSC_LSDA
mdefine_line|#define   USBPORTSC_LSDA&t;0x0100&t;/* Low Speed Device Attached */
DECL|macro|USBPORTSC_PR
mdefine_line|#define   USBPORTSC_PR&t;&t;0x0200&t;/* Port Reset */
DECL|macro|USBPORTSC_SUSP
mdefine_line|#define   USBPORTSC_SUSP&t;0x1000&t;/* Suspend */
multiline_comment|/* Legacy support register */
DECL|macro|USBLEGSUP
mdefine_line|#define USBLEGSUP 0xc0
DECL|macro|USBLEGSUP_DEFAULT
mdefine_line|#define USBLEGSUP_DEFAULT 0x2000&t;/* only PIRQ enable set */
DECL|macro|UHCI_NULL_DATA_SIZE
mdefine_line|#define UHCI_NULL_DATA_SIZE&t;0x7ff&t;/* for UHCI controller TD */
DECL|macro|UHCI_PID
mdefine_line|#define UHCI_PID &t;&t;0xff&t;/* PID MASK */
DECL|macro|UHCI_PTR_BITS
mdefine_line|#define UHCI_PTR_BITS&t;&t;0x000F
DECL|macro|UHCI_PTR_TERM
mdefine_line|#define UHCI_PTR_TERM&t;&t;0x0001
DECL|macro|UHCI_PTR_QH
mdefine_line|#define UHCI_PTR_QH&t;&t;0x0002
DECL|macro|UHCI_PTR_DEPTH
mdefine_line|#define UHCI_PTR_DEPTH&t;&t;0x0004
DECL|macro|UHCI_NUMFRAMES
mdefine_line|#define UHCI_NUMFRAMES&t;&t;1024&t;/* in the frame list [array] */
DECL|macro|UHCI_MAX_SOF_NUMBER
mdefine_line|#define UHCI_MAX_SOF_NUMBER&t;2047&t;/* in an SOF packet */
DECL|macro|CAN_SCHEDULE_FRAMES
mdefine_line|#define CAN_SCHEDULE_FRAMES&t;1000&t;/* how far future frames can be scheduled */
multiline_comment|/* for TD &lt;status&gt; */
DECL|macro|TD_CTRL_SPD
mdefine_line|#define TD_CTRL_SPD&t;&t;(1 &lt;&lt; 29)&t;/* Short Packet Detect */
DECL|macro|TD_CTRL_C_ERR_MASK
mdefine_line|#define TD_CTRL_C_ERR_MASK&t;(3 &lt;&lt; 27)&t;/* Error Counter bits */
DECL|macro|TD_CTRL_LS
mdefine_line|#define TD_CTRL_LS&t;&t;(1 &lt;&lt; 26)&t;/* Low Speed Device */
DECL|macro|TD_CTRL_IOS
mdefine_line|#define TD_CTRL_IOS&t;&t;(1 &lt;&lt; 25)&t;/* Isochronous Select */
DECL|macro|TD_CTRL_IOC
mdefine_line|#define TD_CTRL_IOC&t;&t;(1 &lt;&lt; 24)&t;/* Interrupt on Complete */
DECL|macro|TD_CTRL_ACTIVE
mdefine_line|#define TD_CTRL_ACTIVE&t;&t;(1 &lt;&lt; 23)&t;/* TD Active */
DECL|macro|TD_CTRL_STALLED
mdefine_line|#define TD_CTRL_STALLED&t;&t;(1 &lt;&lt; 22)&t;/* TD Stalled */
DECL|macro|TD_CTRL_DBUFERR
mdefine_line|#define TD_CTRL_DBUFERR&t;&t;(1 &lt;&lt; 21)&t;/* Data Buffer Error */
DECL|macro|TD_CTRL_BABBLE
mdefine_line|#define TD_CTRL_BABBLE&t;&t;(1 &lt;&lt; 20)&t;/* Babble Detected */
DECL|macro|TD_CTRL_NAK
mdefine_line|#define TD_CTRL_NAK&t;&t;(1 &lt;&lt; 19)&t;/* NAK Received */
DECL|macro|TD_CTRL_CRCTIMEO
mdefine_line|#define TD_CTRL_CRCTIMEO&t;(1 &lt;&lt; 18)&t;/* CRC/Time Out Error */
DECL|macro|TD_CTRL_BITSTUFF
mdefine_line|#define TD_CTRL_BITSTUFF&t;(1 &lt;&lt; 17)&t;/* Bit Stuff Error */
DECL|macro|TD_CTRL_ACTLEN_MASK
mdefine_line|#define TD_CTRL_ACTLEN_MASK&t;0x7ff&t;/* actual length, encoded as n - 1 */
DECL|macro|TD_CTRL_ANY_ERROR
mdefine_line|#define TD_CTRL_ANY_ERROR&t;(TD_CTRL_STALLED | TD_CTRL_DBUFERR | &bslash;&n;&t;&t;&t;&t; TD_CTRL_BABBLE | TD_CTRL_CRCTIME | TD_CTRL_BITSTUFF)
DECL|macro|uhci_status_bits
mdefine_line|#define uhci_status_bits(ctrl_sts)&t;(ctrl_sts &amp; 0xFE0000)
DECL|macro|uhci_actual_length
mdefine_line|#define uhci_actual_length(desc)&t;((le32_to_cpu(desc-&gt;hw.td.status) + 1) &amp; TD_CTRL_ACTLEN_MASK)&t;/* 1-based */
multiline_comment|/* for TD &lt;flags&gt;: */
DECL|macro|UHCI_TD_REMOVE
mdefine_line|#define UHCI_TD_REMOVE&t;&t;0x0001&t;/* Remove when done */
multiline_comment|/* for TD &lt;info&gt;: (a.k.a. Token) */
DECL|macro|TD_TOKEN_TOGGLE
mdefine_line|#define TD_TOKEN_TOGGLE&t;&t;19
DECL|macro|uhci_maxlen
mdefine_line|#define uhci_maxlen(token)&t;((token) &gt;&gt; 21)
DECL|macro|uhci_toggle
mdefine_line|#define uhci_toggle(token)&t;(((token) &gt;&gt; TD_TOKEN_TOGGLE) &amp; 1)
DECL|macro|uhci_endpoint
mdefine_line|#define uhci_endpoint(token)&t;(((token) &gt;&gt; 15) &amp; 0xf)
DECL|macro|uhci_devaddr
mdefine_line|#define uhci_devaddr(token)&t;(((token) &gt;&gt; 8) &amp; 0x7f)
DECL|macro|uhci_devep
mdefine_line|#define uhci_devep(token)&t;(((token) &gt;&gt; 8) &amp; 0x7ff)
DECL|macro|uhci_packetid
mdefine_line|#define uhci_packetid(token)&t;((token) &amp; 0xff)
DECL|macro|uhci_packetout
mdefine_line|#define uhci_packetout(token)&t;(uhci_packetid(token) != USB_PID_IN)
DECL|macro|uhci_packetin
mdefine_line|#define uhci_packetin(token)&t;(uhci_packetid(token) == USB_PID_IN)
DECL|macro|uhci_do_toggle
mdefine_line|#define uhci_do_toggle(urb)     usb_dotoggle (urb-&gt;dev, usb_pipeendpoint (urb-&gt;pipe), usb_pipeout (urb-&gt;pipe))
DECL|macro|uhci_get_toggle
mdefine_line|#define uhci_get_toggle(urb)    usb_gettoggle (urb-&gt;dev, usb_pipeendpoint (urb-&gt;pipe), usb_pipeout (urb-&gt;pipe))
multiline_comment|/* ------------------------------------------------------------------------------------&n;   TD/QH-structures&n;   ------------------------------------------------------------------------------------ */
r_typedef
r_enum
(brace
DECL|enumerator|TD_TYPE
DECL|enumerator|QH_TYPE
id|TD_TYPE
comma
id|QH_TYPE
DECL|typedef|uhci_desc_type_t
)brace
id|uhci_desc_type_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|link
id|__u32
id|link
suffix:semicolon
DECL|member|status
id|__u32
id|status
suffix:semicolon
DECL|member|info
id|__u32
id|info
suffix:semicolon
DECL|member|buffer
id|__u32
id|buffer
suffix:semicolon
DECL|typedef|uhci_td_t
DECL|typedef|puhci_td_t
)brace
id|uhci_td_t
comma
op_star
id|puhci_td_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|head
id|__u32
id|head
suffix:semicolon
DECL|member|element
id|__u32
id|element
suffix:semicolon
multiline_comment|/* Queue element pointer */
DECL|typedef|uhci_qh_t
DECL|typedef|puhci_qh_t
)brace
id|uhci_qh_t
comma
op_star
id|puhci_qh_t
suffix:semicolon
r_typedef
r_struct
(brace
r_union
(brace
DECL|member|td
id|uhci_td_t
id|td
suffix:semicolon
DECL|member|qh
id|uhci_qh_t
id|qh
suffix:semicolon
DECL|member|hw
)brace
id|hw
suffix:semicolon
DECL|member|type
id|uhci_desc_type_t
id|type
suffix:semicolon
DECL|member|dma_addr
id|dma_addr_t
id|dma_addr
suffix:semicolon
DECL|member|horizontal
r_struct
id|list_head
id|horizontal
suffix:semicolon
DECL|member|vertical
r_struct
id|list_head
id|vertical
suffix:semicolon
DECL|member|desc_list
r_struct
id|list_head
id|desc_list
suffix:semicolon
DECL|member|last_used
r_int
id|last_used
suffix:semicolon
DECL|typedef|uhci_desc_t
DECL|typedef|puhci_desc_t
)brace
id|uhci_desc_t
comma
op_star
id|puhci_desc_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|desc_list
r_struct
id|list_head
id|desc_list
suffix:semicolon
singleline_comment|// list pointer to all corresponding TDs/QHs associated with this request
DECL|member|urb_list
r_struct
id|list_head
id|urb_list
suffix:semicolon
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
singleline_comment|// urb to which this data belongs
DECL|member|setup_packet_dma
id|dma_addr_t
id|setup_packet_dma
suffix:semicolon
DECL|member|transfer_buffer_dma
id|dma_addr_t
id|transfer_buffer_dma
suffix:semicolon
DECL|member|started
r_int
r_int
id|started
suffix:semicolon
DECL|member|next_queued_urb
r_struct
id|urb
op_star
id|next_queued_urb
suffix:semicolon
singleline_comment|// next queued urb for this EP
DECL|member|prev_queued_urb
r_struct
id|urb
op_star
id|prev_queued_urb
suffix:semicolon
DECL|member|bottom_qh
id|uhci_desc_t
op_star
id|bottom_qh
suffix:semicolon
DECL|member|next_qh
id|uhci_desc_t
op_star
id|next_qh
suffix:semicolon
singleline_comment|// next helper QH
DECL|member|use_loop
r_char
id|use_loop
suffix:semicolon
DECL|member|flags
r_char
id|flags
suffix:semicolon
DECL|typedef|urb_priv_t
DECL|typedef|purb_priv_t
)brace
id|urb_priv_t
comma
op_star
id|purb_priv_t
suffix:semicolon
DECL|struct|uhci_hcd
r_struct
id|uhci_hcd
(brace
DECL|member|maxports
r_int
r_int
id|maxports
suffix:semicolon
DECL|member|running
r_int
id|running
suffix:semicolon
DECL|member|apm_state
r_int
id|apm_state
suffix:semicolon
DECL|member|next
r_struct
id|uhci_hcd
op_star
id|next
suffix:semicolon
singleline_comment|// chain of uhci device contexts
DECL|member|urb_list_lock
id|spinlock_t
id|urb_list_lock
suffix:semicolon
singleline_comment|// lock to keep consistency 
DECL|member|qh_lock
id|spinlock_t
id|qh_lock
suffix:semicolon
DECL|member|td_lock
id|spinlock_t
id|td_lock
suffix:semicolon
DECL|member|avoid_bulk
id|atomic_t
id|avoid_bulk
suffix:semicolon
DECL|member|framelist
id|__u32
op_star
id|framelist
suffix:semicolon
DECL|member|framelist_dma
id|dma_addr_t
id|framelist_dma
suffix:semicolon
DECL|member|iso_td
id|uhci_desc_t
op_star
op_star
id|iso_td
suffix:semicolon
DECL|member|int_chain
id|uhci_desc_t
op_star
id|int_chain
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ls_control_chain
id|uhci_desc_t
op_star
id|ls_control_chain
suffix:semicolon
DECL|member|control_chain
id|uhci_desc_t
op_star
id|control_chain
suffix:semicolon
DECL|member|bulk_chain
id|uhci_desc_t
op_star
id|bulk_chain
suffix:semicolon
DECL|member|chain_end
id|uhci_desc_t
op_star
id|chain_end
suffix:semicolon
DECL|member|td1ms
id|uhci_desc_t
op_star
id|td1ms
suffix:semicolon
DECL|member|td32ms
id|uhci_desc_t
op_star
id|td32ms
suffix:semicolon
DECL|member|td128ms
id|uhci_desc_t
op_star
id|td128ms
suffix:semicolon
DECL|member|urb_list
r_struct
id|list_head
id|urb_list
suffix:semicolon
singleline_comment|// list of all pending urbs
DECL|member|free_desc_qh
r_struct
id|list_head
id|free_desc_qh
suffix:semicolon
singleline_comment|// Cool down pool for QH
DECL|member|free_desc_td
r_struct
id|list_head
id|free_desc_td
suffix:semicolon
singleline_comment|// Cool down pool for ISO/INT-TDs
DECL|member|urb_unlinked
r_struct
id|list_head
id|urb_unlinked
suffix:semicolon
singleline_comment|// list of all unlinked  urbs
DECL|member|uhci_pci
r_struct
id|pci_dev
op_star
id|uhci_pci
suffix:semicolon
DECL|member|desc_pool
r_struct
id|pci_pool
op_star
id|desc_pool
suffix:semicolon
DECL|member|unlink_urb_done
r_int
id|unlink_urb_done
suffix:semicolon
DECL|member|loop_usage
r_int
id|loop_usage
suffix:semicolon
singleline_comment|// URBs using bandwidth reclamation
DECL|member|timeout_check
r_int
id|timeout_check
suffix:semicolon
DECL|member|timeout_urbs
r_int
id|timeout_urbs
suffix:semicolon
DECL|member|last_error_time
r_int
id|last_error_time
suffix:semicolon
singleline_comment|// last error output in uhci_interrupt()
DECL|member|last_hcd_irq
r_int
id|last_hcd_irq
suffix:semicolon
DECL|member|reanimations
r_int
id|reanimations
suffix:semicolon
DECL|member|need_init
r_int
id|need_init
suffix:semicolon
singleline_comment|// Framework state
DECL|member|hcd
r_struct
id|usb_hcd
id|hcd
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|hcd_to_uhci
mdefine_line|#define hcd_to_uhci(hcd_ptr) list_entry(hcd_ptr, struct uhci_hcd, hcd)
DECL|macro|MAKE_TD_ADDR
mdefine_line|#define MAKE_TD_ADDR(a) ((a)-&gt;dma_addr&amp;~UHCI_PTR_QH)
DECL|macro|MAKE_QH_ADDR
mdefine_line|#define MAKE_QH_ADDR(a) ((a)-&gt;dma_addr|UHCI_PTR_QH)
DECL|macro|UHCI_GET_CURRENT_FRAME
mdefine_line|#define UHCI_GET_CURRENT_FRAME(uhci) (inw ((int)(uhci-&gt;hcd.regs) + USBFRNUM))
DECL|macro|CLEAN_TRANSFER_NO_DELETION
mdefine_line|#define CLEAN_TRANSFER_NO_DELETION 0
DECL|macro|CLEAN_TRANSFER_REGULAR
mdefine_line|#define CLEAN_TRANSFER_REGULAR 1
DECL|macro|CLEAN_TRANSFER_DELETION_MARK
mdefine_line|#define CLEAN_TRANSFER_DELETION_MARK 2
DECL|macro|CLEAN_NOT_FORCED
mdefine_line|#define CLEAN_NOT_FORCED 0
DECL|macro|CLEAN_FORCED
mdefine_line|#define CLEAN_FORCED 1
DECL|macro|PROCESS_ISO_REGULAR
mdefine_line|#define PROCESS_ISO_REGULAR 0
DECL|macro|PROCESS_ISO_FORCE
mdefine_line|#define PROCESS_ISO_FORCE 1
DECL|macro|PROCESS_INT_REGULAR
mdefine_line|#define PROCESS_INT_REGULAR 0
DECL|macro|PROCESS_INT_REMOVE
mdefine_line|#define PROCESS_INT_REMOVE 1
DECL|macro|UNLINK_ASYNC_STORE_URB
mdefine_line|#define UNLINK_ASYNC_STORE_URB 0
DECL|macro|UNLINK_ASYNC_DONT_STORE
mdefine_line|#define UNLINK_ASYNC_DONT_STORE 1
DECL|macro|is_td_active
mdefine_line|#define is_td_active(desc) (desc-&gt;hw.td.status &amp; cpu_to_le32(TD_CTRL_ACTIVE))
DECL|macro|set_qh_head
mdefine_line|#define set_qh_head(desc,val) (desc)-&gt;hw.qh.head=cpu_to_le32(val)
DECL|macro|set_qh_element
mdefine_line|#define set_qh_element(desc,val) (desc)-&gt;hw.qh.element=cpu_to_le32(val)
DECL|macro|set_td_link
mdefine_line|#define set_td_link(desc,val) (desc)-&gt;hw.td.link=cpu_to_le32(val)
DECL|macro|set_td_ioc
mdefine_line|#define set_td_ioc(desc) (desc)-&gt;hw.td.status |= cpu_to_le32(TD_CTRL_IOC)
DECL|macro|clr_td_ioc
mdefine_line|#define clr_td_ioc(desc) (desc)-&gt;hw.td.status &amp;= cpu_to_le32(~TD_CTRL_IOC)
macro_line|#endif
eof