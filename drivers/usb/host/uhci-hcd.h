macro_line|#ifndef __LINUX_UHCI_HCD_H
DECL|macro|__LINUX_UHCI_HCD_H
mdefine_line|#define __LINUX_UHCI_HCD_H
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
DECL|macro|usb_packetid
mdefine_line|#define usb_packetid(pipe)&t;(usb_pipein(pipe) ? USB_PID_IN : USB_PID_OUT)
DECL|macro|PIPE_DEVEP_MASK
mdefine_line|#define PIPE_DEVEP_MASK&t;&t;0x0007ff00
multiline_comment|/*&n; * Universal Host Controller Interface data structures and defines&n; */
multiline_comment|/* Command register */
DECL|macro|USBCMD
mdefine_line|#define USBCMD&t;&t;0
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
mdefine_line|#define USBSTS&t;&t;2
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
mdefine_line|#define USBINTR&t;&t;4
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
mdefine_line|#define USBPORTSC1&t;16
DECL|macro|USBPORTSC2
mdefine_line|#define USBPORTSC2&t;18
DECL|macro|USBPORTSC_CCS
mdefine_line|#define   USBPORTSC_CCS&t;&t;0x0001&t;/* Current Connect Status (&quot;device present&quot;) */
DECL|macro|USBPORTSC_CSC
mdefine_line|#define   USBPORTSC_CSC&t;&t;0x0002&t;/* Connect Status Change */
DECL|macro|USBPORTSC_PE
mdefine_line|#define   USBPORTSC_PE&t;&t;0x0004&t;/* Port Enable */
DECL|macro|USBPORTSC_PEC
mdefine_line|#define   USBPORTSC_PEC&t;&t;0x0008&t;/* Port Enable Change */
DECL|macro|USBPORTSC_DPLUS
mdefine_line|#define   USBPORTSC_DPLUS&t;0x0010&t;/* D+ high (line status) */
DECL|macro|USBPORTSC_DMINUS
mdefine_line|#define   USBPORTSC_DMINUS&t;0x0020&t;/* D- high (line status) */
DECL|macro|USBPORTSC_RD
mdefine_line|#define   USBPORTSC_RD&t;&t;0x0040&t;/* Resume Detect */
DECL|macro|USBPORTSC_RES1
mdefine_line|#define   USBPORTSC_RES1&t;0x0080&t;/* reserved, always 1 */
DECL|macro|USBPORTSC_LSDA
mdefine_line|#define   USBPORTSC_LSDA&t;0x0100&t;/* Low Speed Device Attached */
DECL|macro|USBPORTSC_PR
mdefine_line|#define   USBPORTSC_PR&t;&t;0x0200&t;/* Port Reset */
multiline_comment|/* OC and OCC from Intel 430TX and later (not UHCI 1.1d spec) */
DECL|macro|USBPORTSC_OC
mdefine_line|#define   USBPORTSC_OC&t;&t;0x0400&t;/* Over Current condition */
DECL|macro|USBPORTSC_OCC
mdefine_line|#define   USBPORTSC_OCC&t;&t;0x0800&t;/* Over Current Change R/WC */
DECL|macro|USBPORTSC_SUSP
mdefine_line|#define   USBPORTSC_SUSP&t;0x1000&t;/* Suspend */
DECL|macro|USBPORTSC_RES2
mdefine_line|#define   USBPORTSC_RES2&t;0x2000&t;/* reserved, write zeroes */
DECL|macro|USBPORTSC_RES3
mdefine_line|#define   USBPORTSC_RES3&t;0x4000&t;/* reserved, write zeroes */
DECL|macro|USBPORTSC_RES4
mdefine_line|#define   USBPORTSC_RES4&t;0x8000&t;/* reserved, write zeroes */
multiline_comment|/* Legacy support register */
DECL|macro|USBLEGSUP
mdefine_line|#define USBLEGSUP&t;&t;0xc0
DECL|macro|USBLEGSUP_DEFAULT
mdefine_line|#define   USBLEGSUP_DEFAULT&t;0x2000&t;/* only PIRQ enable set */
DECL|macro|UHCI_NULL_DATA_SIZE
mdefine_line|#define UHCI_NULL_DATA_SIZE&t;0x7FF&t;/* for UHCI controller TD */
DECL|macro|UHCI_PTR_BITS
mdefine_line|#define UHCI_PTR_BITS&t;&t;cpu_to_le32(0x000F)
DECL|macro|UHCI_PTR_TERM
mdefine_line|#define UHCI_PTR_TERM&t;&t;cpu_to_le32(0x0001)
DECL|macro|UHCI_PTR_QH
mdefine_line|#define UHCI_PTR_QH&t;&t;cpu_to_le32(0x0002)
DECL|macro|UHCI_PTR_DEPTH
mdefine_line|#define UHCI_PTR_DEPTH&t;&t;cpu_to_le32(0x0004)
DECL|macro|UHCI_PTR_BREADTH
mdefine_line|#define UHCI_PTR_BREADTH&t;cpu_to_le32(0x0000)
DECL|macro|UHCI_NUMFRAMES
mdefine_line|#define UHCI_NUMFRAMES&t;&t;1024&t;/* in the frame list [array] */
DECL|macro|UHCI_MAX_SOF_NUMBER
mdefine_line|#define UHCI_MAX_SOF_NUMBER&t;2047&t;/* in an SOF packet */
DECL|macro|CAN_SCHEDULE_FRAMES
mdefine_line|#define CAN_SCHEDULE_FRAMES&t;1000&t;/* how far future frames can be scheduled */
DECL|struct|uhci_frame_list
r_struct
id|uhci_frame_list
(brace
DECL|member|frame
id|__le32
id|frame
(braket
id|UHCI_NUMFRAMES
)braket
suffix:semicolon
DECL|member|frame_cpu
r_void
op_star
id|frame_cpu
(braket
id|UHCI_NUMFRAMES
)braket
suffix:semicolon
DECL|member|dma_handle
id|dma_addr_t
id|dma_handle
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|urb_priv
suffix:semicolon
multiline_comment|/*&n; * One role of a QH is to hold a queue of TDs for some endpoint.  Each QH is&n; * used with one URB, and qh-&gt;element (updated by the HC) is either:&n; *   - the next unprocessed TD for the URB, or&n; *   - UHCI_PTR_TERM (when there&squot;s no more traffic for this endpoint), or&n; *   - the QH for the next URB queued to the same endpoint.&n; *&n; * The other role of a QH is to serve as a &quot;skeleton&quot; framelist entry, so we&n; * can easily splice a QH for some endpoint into the schedule at the right&n; * place.  Then qh-&gt;element is UHCI_PTR_TERM.&n; *&n; * In the frame list, qh-&gt;link maintains a list of QHs seen by the HC:&n; *     skel1 --&gt; ep1-qh --&gt; ep2-qh --&gt; ... --&gt; skel2 --&gt; ...&n; */
DECL|struct|uhci_qh
r_struct
id|uhci_qh
(brace
multiline_comment|/* Hardware fields */
DECL|member|link
id|__le32
id|link
suffix:semicolon
multiline_comment|/* Next queue */
DECL|member|element
id|__le32
id|element
suffix:semicolon
multiline_comment|/* Queue element pointer */
multiline_comment|/* Software fields */
DECL|member|dma_handle
id|dma_addr_t
id|dma_handle
suffix:semicolon
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
DECL|member|urbp
r_struct
id|urb_priv
op_star
id|urbp
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* P: uhci-&gt;frame_list_lock */
DECL|member|remove_list
r_struct
id|list_head
id|remove_list
suffix:semicolon
multiline_comment|/* P: uhci-&gt;remove_list_lock */
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * for TD &lt;status&gt;:&n; */
DECL|macro|td_status
mdefine_line|#define td_status(td)&t;&t;le32_to_cpu((td)-&gt;status)
DECL|macro|TD_CTRL_SPD
mdefine_line|#define TD_CTRL_SPD&t;&t;(1 &lt;&lt; 29)&t;/* Short Packet Detect */
DECL|macro|TD_CTRL_C_ERR_MASK
mdefine_line|#define TD_CTRL_C_ERR_MASK&t;(3 &lt;&lt; 27)&t;/* Error Counter bits */
DECL|macro|TD_CTRL_C_ERR_SHIFT
mdefine_line|#define TD_CTRL_C_ERR_SHIFT&t;27
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
mdefine_line|#define TD_CTRL_ACTLEN_MASK&t;0x7FF&t;/* actual length, encoded as n - 1 */
DECL|macro|TD_CTRL_ANY_ERROR
mdefine_line|#define TD_CTRL_ANY_ERROR&t;(TD_CTRL_STALLED | TD_CTRL_DBUFERR | &bslash;&n;&t;&t;&t;&t; TD_CTRL_BABBLE | TD_CTRL_CRCTIME | TD_CTRL_BITSTUFF)
DECL|macro|uhci_maxerr
mdefine_line|#define uhci_maxerr(err)&t;&t;((err) &lt;&lt; TD_CTRL_C_ERR_SHIFT)
DECL|macro|uhci_status_bits
mdefine_line|#define uhci_status_bits(ctrl_sts)&t;((ctrl_sts) &amp; 0xF60000)
DECL|macro|uhci_actual_length
mdefine_line|#define uhci_actual_length(ctrl_sts)&t;(((ctrl_sts) + 1) &amp; TD_CTRL_ACTLEN_MASK) /* 1-based */
multiline_comment|/*&n; * for TD &lt;info&gt;: (a.k.a. Token)&n; */
DECL|macro|td_token
mdefine_line|#define td_token(td)&t;&t;le32_to_cpu((td)-&gt;token)
DECL|macro|TD_TOKEN_DEVADDR_SHIFT
mdefine_line|#define TD_TOKEN_DEVADDR_SHIFT&t;8
DECL|macro|TD_TOKEN_TOGGLE_SHIFT
mdefine_line|#define TD_TOKEN_TOGGLE_SHIFT&t;19
DECL|macro|TD_TOKEN_TOGGLE
mdefine_line|#define TD_TOKEN_TOGGLE&t;&t;(1 &lt;&lt; 19)
DECL|macro|TD_TOKEN_EXPLEN_SHIFT
mdefine_line|#define TD_TOKEN_EXPLEN_SHIFT&t;21
DECL|macro|TD_TOKEN_EXPLEN_MASK
mdefine_line|#define TD_TOKEN_EXPLEN_MASK&t;0x7FF&t;&t;/* expected length, encoded as n - 1 */
DECL|macro|TD_TOKEN_PID_MASK
mdefine_line|#define TD_TOKEN_PID_MASK&t;0xFF
DECL|macro|uhci_explen
mdefine_line|#define uhci_explen(len)&t;((len) &lt;&lt; TD_TOKEN_EXPLEN_SHIFT)
DECL|macro|uhci_expected_length
mdefine_line|#define uhci_expected_length(token) ((((token) &gt;&gt; 21) + 1) &amp; TD_TOKEN_EXPLEN_MASK)
DECL|macro|uhci_toggle
mdefine_line|#define uhci_toggle(token)&t;(((token) &gt;&gt; TD_TOKEN_TOGGLE_SHIFT) &amp; 1)
DECL|macro|uhci_endpoint
mdefine_line|#define uhci_endpoint(token)&t;(((token) &gt;&gt; 15) &amp; 0xf)
DECL|macro|uhci_devaddr
mdefine_line|#define uhci_devaddr(token)&t;(((token) &gt;&gt; TD_TOKEN_DEVADDR_SHIFT) &amp; 0x7f)
DECL|macro|uhci_devep
mdefine_line|#define uhci_devep(token)&t;(((token) &gt;&gt; TD_TOKEN_DEVADDR_SHIFT) &amp; 0x7ff)
DECL|macro|uhci_packetid
mdefine_line|#define uhci_packetid(token)&t;((token) &amp; TD_TOKEN_PID_MASK)
DECL|macro|uhci_packetout
mdefine_line|#define uhci_packetout(token)&t;(uhci_packetid(token) != USB_PID_IN)
DECL|macro|uhci_packetin
mdefine_line|#define uhci_packetin(token)&t;(uhci_packetid(token) == USB_PID_IN)
multiline_comment|/*&n; * The documentation says &quot;4 words for hardware, 4 words for software&quot;.&n; *&n; * That&squot;s silly, the hardware doesn&squot;t care. The hardware only cares that&n; * the hardware words are 16-byte aligned, and we can have any amount of&n; * sw space after the TD entry as far as I can tell.&n; *&n; * But let&squot;s just go with the documentation, at least for 32-bit machines.&n; * On 64-bit machines we probably want to take advantage of the fact that&n; * hw doesn&squot;t really care about the size of the sw-only area.&n; *&n; * Alas, not anymore, we have more than 4 words for software, woops.&n; * Everything still works tho, surprise! -jerdfelt&n; *&n; * td-&gt;link points to either another TD (not necessarily for the same urb or&n; * even the same endpoint), or nothing (PTR_TERM), or a QH (for queued urbs)&n; */
DECL|struct|uhci_td
r_struct
id|uhci_td
(brace
multiline_comment|/* Hardware fields */
DECL|member|link
id|__le32
id|link
suffix:semicolon
DECL|member|status
id|__le32
id|status
suffix:semicolon
DECL|member|token
id|__le32
id|token
suffix:semicolon
DECL|member|buffer
id|__le32
id|buffer
suffix:semicolon
multiline_comment|/* Software fields */
DECL|member|dma_handle
id|dma_addr_t
id|dma_handle
suffix:semicolon
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
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
multiline_comment|/* P: urb-&gt;lock */
DECL|member|remove_list
r_struct
id|list_head
id|remove_list
suffix:semicolon
multiline_comment|/* P: uhci-&gt;td_remove_list_lock */
DECL|member|frame
r_int
id|frame
suffix:semicolon
multiline_comment|/* for iso: what frame? */
DECL|member|fl_list
r_struct
id|list_head
id|fl_list
suffix:semicolon
multiline_comment|/* P: uhci-&gt;frame_list_lock */
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * The UHCI driver places Interrupt, Control and Bulk into QH&squot;s both&n; * to group together TD&squot;s for one transfer, and also to faciliate queuing&n; * of URB&squot;s. To make it easy to insert entries into the schedule, we have&n; * a skeleton of QH&squot;s for each predefined Interrupt latency, low-speed&n; * control, full-speed control and terminating QH (see explanation for&n; * the terminating QH below).&n; *&n; * When we want to add a new QH, we add it to the end of the list for the&n; * skeleton QH.&n; *&n; * For instance, the queue can look like this:&n; *&n; * skel int128 QH&n; * dev 1 interrupt QH&n; * dev 5 interrupt QH&n; * skel int64 QH&n; * skel int32 QH&n; * ...&n; * skel int1 QH&n; * skel low-speed control QH&n; * dev 5 control QH&n; * skel full-speed control QH&n; * skel bulk QH&n; * dev 1 bulk QH&n; * dev 2 bulk QH&n; * skel terminating QH&n; *&n; * The terminating QH is used for 2 reasons:&n; * - To place a terminating TD which is used to workaround a PIIX bug&n; *   (see Intel errata for explanation)&n; * - To loop back to the full-speed control queue for full-speed bandwidth&n; *   reclamation&n; *&n; * Isochronous transfers are stored before the start of the skeleton&n; * schedule and don&squot;t use QH&squot;s. While the UHCI spec doesn&squot;t forbid the&n; * use of QH&squot;s for Isochronous, it doesn&squot;t use them either. Since we don&squot;t&n; * need to use them either, we follow the spec diagrams in hope that it&squot;ll&n; * be more compatible with future UHCI implementations.&n; */
DECL|macro|UHCI_NUM_SKELQH
mdefine_line|#define UHCI_NUM_SKELQH&t;&t;12
DECL|macro|skel_int128_qh
mdefine_line|#define skel_int128_qh&t;&t;skelqh[0]
DECL|macro|skel_int64_qh
mdefine_line|#define skel_int64_qh&t;&t;skelqh[1]
DECL|macro|skel_int32_qh
mdefine_line|#define skel_int32_qh&t;&t;skelqh[2]
DECL|macro|skel_int16_qh
mdefine_line|#define skel_int16_qh&t;&t;skelqh[3]
DECL|macro|skel_int8_qh
mdefine_line|#define skel_int8_qh&t;&t;skelqh[4]
DECL|macro|skel_int4_qh
mdefine_line|#define skel_int4_qh&t;&t;skelqh[5]
DECL|macro|skel_int2_qh
mdefine_line|#define skel_int2_qh&t;&t;skelqh[6]
DECL|macro|skel_int1_qh
mdefine_line|#define skel_int1_qh&t;&t;skelqh[7]
DECL|macro|skel_ls_control_qh
mdefine_line|#define skel_ls_control_qh&t;skelqh[8]
DECL|macro|skel_fs_control_qh
mdefine_line|#define skel_fs_control_qh&t;skelqh[9]
DECL|macro|skel_bulk_qh
mdefine_line|#define skel_bulk_qh&t;&t;skelqh[10]
DECL|macro|skel_term_qh
mdefine_line|#define skel_term_qh&t;&t;skelqh[11]
multiline_comment|/*&n; * Search tree for determining where &lt;interval&gt; fits in the skelqh[]&n; * skeleton.&n; *&n; * An interrupt request should be placed into the slowest skelqh[]&n; * which meets the interval/period/frequency requirement.&n; * An interrupt request is allowed to be faster than &lt;interval&gt; but not slower.&n; *&n; * For a given &lt;interval&gt;, this function returns the appropriate/matching&n; * skelqh[] index value.&n; */
DECL|function|__interval_to_skel
r_static
r_inline
r_int
id|__interval_to_skel
c_func
(paren
r_int
id|interval
)paren
(brace
r_if
c_cond
(paren
id|interval
OL
l_int|16
)paren
(brace
r_if
c_cond
(paren
id|interval
OL
l_int|4
)paren
(brace
r_if
c_cond
(paren
id|interval
OL
l_int|2
)paren
r_return
l_int|7
suffix:semicolon
multiline_comment|/* int1 for 0-1 ms */
r_return
l_int|6
suffix:semicolon
multiline_comment|/* int2 for 2-3 ms */
)brace
r_if
c_cond
(paren
id|interval
OL
l_int|8
)paren
r_return
l_int|5
suffix:semicolon
multiline_comment|/* int4 for 4-7 ms */
r_return
l_int|4
suffix:semicolon
multiline_comment|/* int8 for 8-15 ms */
)brace
r_if
c_cond
(paren
id|interval
OL
l_int|64
)paren
(brace
r_if
c_cond
(paren
id|interval
OL
l_int|32
)paren
r_return
l_int|3
suffix:semicolon
multiline_comment|/* int16 for 16-31 ms */
r_return
l_int|2
suffix:semicolon
multiline_comment|/* int32 for 32-63 ms */
)brace
r_if
c_cond
(paren
id|interval
OL
l_int|128
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* int64 for 64-127 ms */
r_return
l_int|0
suffix:semicolon
multiline_comment|/* int128 for 128-255 ms (Max.) */
)brace
multiline_comment|/*&n; * Device states for the host controller.&n; *&n; * To prevent &quot;bouncing&quot; in the presence of electrical noise,&n; * we insist on a 1-second &quot;grace&quot; period, before switching to&n; * the RUNNING or SUSPENDED states, during which the state is&n; * not allowed to change.&n; *&n; * The resume process is divided into substates in order to avoid&n; * potentially length delays during the timer handler.&n; *&n; * States in which the host controller is halted must have values &lt;= 0.&n; */
DECL|enum|uhci_state
r_enum
id|uhci_state
(brace
DECL|enumerator|UHCI_RESET
id|UHCI_RESET
comma
DECL|enumerator|UHCI_RUNNING_GRACE
id|UHCI_RUNNING_GRACE
comma
multiline_comment|/* Before RUNNING */
DECL|enumerator|UHCI_RUNNING
id|UHCI_RUNNING
comma
multiline_comment|/* The normal state */
DECL|enumerator|UHCI_SUSPENDING_GRACE
id|UHCI_SUSPENDING_GRACE
comma
multiline_comment|/* Before SUSPENDED */
DECL|enumerator|UHCI_SUSPENDED
id|UHCI_SUSPENDED
op_assign
op_minus
l_int|10
comma
multiline_comment|/* When no devices are attached */
DECL|enumerator|UHCI_RESUMING_1
id|UHCI_RESUMING_1
comma
DECL|enumerator|UHCI_RESUMING_2
id|UHCI_RESUMING_2
)brace
suffix:semicolon
DECL|macro|hcd_to_uhci
mdefine_line|#define hcd_to_uhci(hcd_ptr) container_of(hcd_ptr, struct uhci_hcd, hcd)
DECL|macro|uhci_dev
mdefine_line|#define uhci_dev(u)&t;((u)-&gt;hcd.self.controller)
multiline_comment|/*&n; * This describes the full uhci information.&n; *&n; * Note how the &quot;proper&quot; USB information is just&n; * a subset of what the full implementation needs.&n; */
DECL|struct|uhci_hcd
r_struct
id|uhci_hcd
(brace
DECL|member|hcd
r_struct
id|usb_hcd
id|hcd
suffix:semicolon
multiline_comment|/* must come first! */
multiline_comment|/* debugfs */
DECL|member|dentry
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
multiline_comment|/* Grabbed from PCI */
DECL|member|io_addr
r_int
r_int
id|io_addr
suffix:semicolon
DECL|member|qh_pool
r_struct
id|dma_pool
op_star
id|qh_pool
suffix:semicolon
DECL|member|td_pool
r_struct
id|dma_pool
op_star
id|td_pool
suffix:semicolon
DECL|member|bus
r_struct
id|usb_bus
op_star
id|bus
suffix:semicolon
DECL|member|term_td
r_struct
id|uhci_td
op_star
id|term_td
suffix:semicolon
multiline_comment|/* Terminating TD, see UHCI bug */
DECL|member|skelqh
r_struct
id|uhci_qh
op_star
id|skelqh
(braket
id|UHCI_NUM_SKELQH
)braket
suffix:semicolon
multiline_comment|/* Skeleton QH&squot;s */
DECL|member|schedule_lock
id|spinlock_t
id|schedule_lock
suffix:semicolon
DECL|member|fl
r_struct
id|uhci_frame_list
op_star
id|fl
suffix:semicolon
multiline_comment|/* P: uhci-&gt;schedule_lock */
DECL|member|fsbr
r_int
id|fsbr
suffix:semicolon
multiline_comment|/* Full-speed bandwidth reclamation */
DECL|member|fsbrtimeout
r_int
r_int
id|fsbrtimeout
suffix:semicolon
multiline_comment|/* FSBR delay */
DECL|member|state
r_enum
id|uhci_state
id|state
suffix:semicolon
multiline_comment|/* FIXME: needs a spinlock */
DECL|member|state_end
r_int
r_int
id|state_end
suffix:semicolon
multiline_comment|/* Time of next transition */
DECL|member|resume_detect
r_int
id|resume_detect
suffix:semicolon
multiline_comment|/* Need a Global Resume */
DECL|member|saved_framenumber
r_int
r_int
id|saved_framenumber
suffix:semicolon
multiline_comment|/* Save during PM suspend */
multiline_comment|/* Support for port suspend/resume */
DECL|member|port_c_suspend
r_int
r_int
id|port_c_suspend
suffix:semicolon
multiline_comment|/* Bit-arrays of ports */
DECL|member|suspended_ports
r_int
r_int
id|suspended_ports
suffix:semicolon
DECL|member|resuming_ports
r_int
r_int
id|resuming_ports
suffix:semicolon
DECL|member|resume_timeout
r_int
r_int
id|resume_timeout
suffix:semicolon
multiline_comment|/* Time to stop signalling */
multiline_comment|/* Main list of URB&squot;s currently controlled by this HC */
DECL|member|urb_list
r_struct
id|list_head
id|urb_list
suffix:semicolon
multiline_comment|/* P: uhci-&gt;schedule_lock */
multiline_comment|/* List of QH&squot;s that are done, but waiting to be unlinked (race) */
DECL|member|qh_remove_list
r_struct
id|list_head
id|qh_remove_list
suffix:semicolon
multiline_comment|/* P: uhci-&gt;schedule_lock */
DECL|member|qh_remove_age
r_int
r_int
id|qh_remove_age
suffix:semicolon
multiline_comment|/* Age in frames */
multiline_comment|/* List of TD&squot;s that are done, but waiting to be freed (race) */
DECL|member|td_remove_list
r_struct
id|list_head
id|td_remove_list
suffix:semicolon
multiline_comment|/* P: uhci-&gt;schedule_lock */
DECL|member|td_remove_age
r_int
r_int
id|td_remove_age
suffix:semicolon
multiline_comment|/* Age in frames */
multiline_comment|/* List of asynchronously unlinked URB&squot;s */
DECL|member|urb_remove_list
r_struct
id|list_head
id|urb_remove_list
suffix:semicolon
multiline_comment|/* P: uhci-&gt;schedule_lock */
DECL|member|urb_remove_age
r_int
r_int
id|urb_remove_age
suffix:semicolon
multiline_comment|/* Age in frames */
multiline_comment|/* List of URB&squot;s awaiting completion callback */
DECL|member|complete_list
r_struct
id|list_head
id|complete_list
suffix:semicolon
multiline_comment|/* P: uhci-&gt;schedule_lock */
DECL|member|rh_numports
r_int
id|rh_numports
suffix:semicolon
DECL|member|stall_timer
r_struct
id|timer_list
id|stall_timer
suffix:semicolon
DECL|member|waitqh
id|wait_queue_head_t
id|waitqh
suffix:semicolon
multiline_comment|/* endpoint_disable waiters */
)brace
suffix:semicolon
DECL|struct|urb_priv
r_struct
id|urb_priv
(brace
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
DECL|member|qh
r_struct
id|uhci_qh
op_star
id|qh
suffix:semicolon
multiline_comment|/* QH for this URB */
DECL|member|td_list
r_struct
id|list_head
id|td_list
suffix:semicolon
multiline_comment|/* P: urb-&gt;lock */
DECL|member|fsbr
r_int
id|fsbr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* URB turned on FSBR */
DECL|member|fsbr_timeout
r_int
id|fsbr_timeout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* URB timed out on FSBR */
DECL|member|queued
r_int
id|queued
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* QH was queued (not linked in) */
DECL|member|short_control_packet
r_int
id|short_control_packet
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* If we get a short packet during */
multiline_comment|/*  a control transfer, retrigger */
multiline_comment|/*  the status phase */
DECL|member|inserttime
r_int
r_int
id|inserttime
suffix:semicolon
multiline_comment|/* In jiffies */
DECL|member|fsbrtime
r_int
r_int
id|fsbrtime
suffix:semicolon
multiline_comment|/* In jiffies */
DECL|member|queue_list
r_struct
id|list_head
id|queue_list
suffix:semicolon
multiline_comment|/* P: uhci-&gt;frame_list_lock */
)brace
suffix:semicolon
multiline_comment|/*&n; * Locking in uhci.c&n; *&n; * Almost everything relating to the hardware schedule and processing&n; * of URBs is protected by uhci-&gt;schedule_lock.  urb-&gt;status is protected&n; * by urb-&gt;lock; that&squot;s the one exception.&n; *&n; * To prevent deadlocks, never lock uhci-&gt;schedule_lock while holding&n; * urb-&gt;lock.  The safe order of locking is:&n; *&n; * #1 uhci-&gt;schedule_lock&n; * #2 urb-&gt;lock&n; */
macro_line|#endif
eof
