multiline_comment|/*&n; * OHCI HCD (Host Controller Driver) for USB.&n; * &n; * (C) Copyright 1999 Roman Weissgaerber &lt;weissg@vienna.at&gt;&n; * (C) Copyright 2000-2002 David Brownell &lt;dbrownell@users.sourceforge.net&gt;&n; * &n; * This file is licenced under the GPL.&n; */
multiline_comment|/*&n; * __hc32 and __hc16 are &quot;Host Controller&quot; types, they may be equivalent to&n; * __leXX (normally) or __beXX (given OHCI_BIG_ENDIAN), depending on the&n; * host controller implementation.&n; */
DECL|typedef|__hc32
r_typedef
id|__u32
id|__bitwise
id|__hc32
suffix:semicolon
DECL|typedef|__hc16
r_typedef
id|__u16
id|__bitwise
id|__hc16
suffix:semicolon
multiline_comment|/*&n; * OHCI Endpoint Descriptor (ED) ... holds TD queue&n; * See OHCI spec, section 4.2&n; *&n; * This is a &quot;Queue Head&quot; for those transfers, which is why&n; * both EHCI and UHCI call similar structures a &quot;QH&quot;.&n; */
DECL|struct|ed
r_struct
id|ed
(brace
multiline_comment|/* first fields are hardware-specified */
DECL|member|hwINFO
id|__hc32
id|hwINFO
suffix:semicolon
multiline_comment|/* endpoint config bitmap */
multiline_comment|/* info bits defined by hcd */
DECL|macro|ED_DEQUEUE
mdefine_line|#define ED_DEQUEUE&t;(1 &lt;&lt; 27)
multiline_comment|/* info bits defined by the hardware */
DECL|macro|ED_ISO
mdefine_line|#define ED_ISO&t;&t;(1 &lt;&lt; 15)
DECL|macro|ED_SKIP
mdefine_line|#define ED_SKIP&t;&t;(1 &lt;&lt; 14)
DECL|macro|ED_LOWSPEED
mdefine_line|#define ED_LOWSPEED&t;(1 &lt;&lt; 13)
DECL|macro|ED_OUT
mdefine_line|#define ED_OUT&t;&t;(0x01 &lt;&lt; 11)
DECL|macro|ED_IN
mdefine_line|#define ED_IN&t;&t;(0x02 &lt;&lt; 11)
DECL|member|hwTailP
id|__hc32
id|hwTailP
suffix:semicolon
multiline_comment|/* tail of TD list */
DECL|member|hwHeadP
id|__hc32
id|hwHeadP
suffix:semicolon
multiline_comment|/* head of TD list (hc r/w) */
DECL|macro|ED_C
mdefine_line|#define ED_C&t;&t;(0x02)&t;&t;&t;/* toggle carry */
DECL|macro|ED_H
mdefine_line|#define ED_H&t;&t;(0x01)&t;&t;&t;/* halted */
DECL|member|hwNextED
id|__hc32
id|hwNextED
suffix:semicolon
multiline_comment|/* next ED in list */
multiline_comment|/* rest are purely for the driver&squot;s use */
DECL|member|dma
id|dma_addr_t
id|dma
suffix:semicolon
multiline_comment|/* addr of ED */
DECL|member|dummy
r_struct
id|td
op_star
id|dummy
suffix:semicolon
multiline_comment|/* next TD to activate */
multiline_comment|/* host&squot;s view of schedule */
DECL|member|ed_next
r_struct
id|ed
op_star
id|ed_next
suffix:semicolon
multiline_comment|/* on schedule or rm_list */
DECL|member|ed_prev
r_struct
id|ed
op_star
id|ed_prev
suffix:semicolon
multiline_comment|/* for non-interrupt EDs */
DECL|member|td_list
r_struct
id|list_head
id|td_list
suffix:semicolon
multiline_comment|/* &quot;shadow list&quot; of our TDs */
multiline_comment|/* create --&gt; IDLE --&gt; OPER --&gt; ... --&gt; IDLE --&gt; destroy&n;&t; * usually:  OPER --&gt; UNLINK --&gt; (IDLE | OPER) --&gt; ...&n;&t; */
DECL|member|state
id|u8
id|state
suffix:semicolon
multiline_comment|/* ED_{IDLE,UNLINK,OPER} */
DECL|macro|ED_IDLE
mdefine_line|#define ED_IDLE &t;0x00&t;&t;/* NOT linked to HC */
DECL|macro|ED_UNLINK
mdefine_line|#define ED_UNLINK &t;0x01&t;&t;/* being unlinked from hc */
DECL|macro|ED_OPER
mdefine_line|#define ED_OPER&t;&t;0x02&t;&t;/* IS linked to hc */
DECL|member|type
id|u8
id|type
suffix:semicolon
multiline_comment|/* PIPE_{BULK,...} */
multiline_comment|/* periodic scheduling params (for intr and iso) */
DECL|member|branch
id|u8
id|branch
suffix:semicolon
DECL|member|interval
id|u16
id|interval
suffix:semicolon
DECL|member|load
id|u16
id|load
suffix:semicolon
DECL|member|last_iso
id|u16
id|last_iso
suffix:semicolon
multiline_comment|/* iso only */
multiline_comment|/* HC may see EDs on rm_list until next frame (frame_no == tick) */
DECL|member|tick
id|u16
id|tick
suffix:semicolon
)brace
id|__attribute__
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
DECL|macro|ED_MASK
mdefine_line|#define ED_MASK&t;((u32)~0x0f)&t;&t;/* strip hw status in low addr bits */
multiline_comment|/*&n; * OHCI Transfer Descriptor (TD) ... one per transfer segment&n; * See OHCI spec, sections 4.3.1 (general = control/bulk/interrupt)&n; * and 4.3.2 (iso)&n; */
DECL|struct|td
r_struct
id|td
(brace
multiline_comment|/* first fields are hardware-specified */
DECL|member|hwINFO
id|__hc32
id|hwINFO
suffix:semicolon
multiline_comment|/* transfer info bitmask */
multiline_comment|/* hwINFO bits for both general and iso tds: */
DECL|macro|TD_CC
mdefine_line|#define TD_CC       0xf0000000&t;&t;&t;/* condition code */
DECL|macro|TD_CC_GET
mdefine_line|#define TD_CC_GET(td_p) ((td_p &gt;&gt;28) &amp; 0x0f)
singleline_comment|//#define TD_CC_SET(td_p, cc) (td_p) = ((td_p) &amp; 0x0fffffff) | (((cc) &amp; 0x0f) &lt;&lt; 28)
DECL|macro|TD_DI
mdefine_line|#define TD_DI       0x00E00000&t;&t;&t;/* frames before interrupt */
DECL|macro|TD_DI_SET
mdefine_line|#define TD_DI_SET(X) (((X) &amp; 0x07)&lt;&lt; 21)
multiline_comment|/* these two bits are available for definition/use by HCDs in both&n;&t; * general and iso tds ... others are available for only one type&n;&t; */
DECL|macro|TD_DONE
mdefine_line|#define TD_DONE     0x00020000&t;&t;&t;/* retired to donelist */
DECL|macro|TD_ISO
mdefine_line|#define TD_ISO      0x00010000&t;&t;&t;/* copy of ED_ISO */
multiline_comment|/* hwINFO bits for general tds: */
DECL|macro|TD_EC
mdefine_line|#define TD_EC       0x0C000000&t;&t;&t;/* error count */
DECL|macro|TD_T
mdefine_line|#define TD_T        0x03000000&t;&t;&t;/* data toggle state */
DECL|macro|TD_T_DATA0
mdefine_line|#define TD_T_DATA0  0x02000000&t;&t;&t;&t;/* DATA0 */
DECL|macro|TD_T_DATA1
mdefine_line|#define TD_T_DATA1  0x03000000&t;&t;&t;&t;/* DATA1 */
DECL|macro|TD_T_TOGGLE
mdefine_line|#define TD_T_TOGGLE 0x00000000&t;&t;&t;&t;/* uses ED_C */
DECL|macro|TD_DP
mdefine_line|#define TD_DP       0x00180000&t;&t;&t;/* direction/pid */
DECL|macro|TD_DP_SETUP
mdefine_line|#define TD_DP_SETUP 0x00000000&t;&t;&t;/* SETUP pid */
DECL|macro|TD_DP_IN
mdefine_line|#define TD_DP_IN    0x00100000&t;&t;&t;&t;/* IN pid */
DECL|macro|TD_DP_OUT
mdefine_line|#define TD_DP_OUT   0x00080000&t;&t;&t;&t;/* OUT pid */
multiline_comment|/* 0x00180000 rsvd */
DECL|macro|TD_R
mdefine_line|#define TD_R        0x00040000&t;&t;&t;/* round: short packets OK? */
multiline_comment|/* (no hwINFO #defines yet for iso tds) */
DECL|member|hwCBP
id|__hc32
id|hwCBP
suffix:semicolon
multiline_comment|/* Current Buffer Pointer (or 0) */
DECL|member|hwNextTD
id|__hc32
id|hwNextTD
suffix:semicolon
multiline_comment|/* Next TD Pointer */
DECL|member|hwBE
id|__hc32
id|hwBE
suffix:semicolon
multiline_comment|/* Memory Buffer End Pointer */
multiline_comment|/* PSW is only for ISO */
DECL|macro|MAXPSW
mdefine_line|#define MAXPSW 1&t;&t;/* hardware allows 8 */
DECL|member|hwPSW
id|__hc16
id|hwPSW
(braket
id|MAXPSW
)braket
suffix:semicolon
multiline_comment|/* rest are purely for the driver&squot;s use */
DECL|member|index
id|__u8
id|index
suffix:semicolon
DECL|member|ed
r_struct
id|ed
op_star
id|ed
suffix:semicolon
DECL|member|td_hash
r_struct
id|td
op_star
id|td_hash
suffix:semicolon
multiline_comment|/* dma--&gt;td hashtable */
DECL|member|next_dl_td
r_struct
id|td
op_star
id|next_dl_td
suffix:semicolon
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
DECL|member|td_dma
id|dma_addr_t
id|td_dma
suffix:semicolon
multiline_comment|/* addr of this TD */
DECL|member|data_dma
id|dma_addr_t
id|data_dma
suffix:semicolon
multiline_comment|/* addr of data it points to */
DECL|member|td_list
r_struct
id|list_head
id|td_list
suffix:semicolon
multiline_comment|/* &quot;shadow list&quot;, TDs on same ED */
)brace
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|32
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* c/b/i need 16; only iso needs 32 */
DECL|macro|TD_MASK
mdefine_line|#define TD_MASK&t;((u32)~0x1f)&t;&t;/* strip hw status in low addr bits */
multiline_comment|/*&n; * Hardware transfer status codes -- CC from td-&gt;hwINFO or td-&gt;hwPSW&n; */
DECL|macro|TD_CC_NOERROR
mdefine_line|#define TD_CC_NOERROR      0x00
DECL|macro|TD_CC_CRC
mdefine_line|#define TD_CC_CRC          0x01
DECL|macro|TD_CC_BITSTUFFING
mdefine_line|#define TD_CC_BITSTUFFING  0x02
DECL|macro|TD_CC_DATATOGGLEM
mdefine_line|#define TD_CC_DATATOGGLEM  0x03
DECL|macro|TD_CC_STALL
mdefine_line|#define TD_CC_STALL        0x04
DECL|macro|TD_DEVNOTRESP
mdefine_line|#define TD_DEVNOTRESP      0x05
DECL|macro|TD_PIDCHECKFAIL
mdefine_line|#define TD_PIDCHECKFAIL    0x06
DECL|macro|TD_UNEXPECTEDPID
mdefine_line|#define TD_UNEXPECTEDPID   0x07
DECL|macro|TD_DATAOVERRUN
mdefine_line|#define TD_DATAOVERRUN     0x08
DECL|macro|TD_DATAUNDERRUN
mdefine_line|#define TD_DATAUNDERRUN    0x09
multiline_comment|/* 0x0A, 0x0B reserved for hardware */
DECL|macro|TD_BUFFEROVERRUN
mdefine_line|#define TD_BUFFEROVERRUN   0x0C
DECL|macro|TD_BUFFERUNDERRUN
mdefine_line|#define TD_BUFFERUNDERRUN  0x0D
multiline_comment|/* 0x0E, 0x0F reserved for HCD */
DECL|macro|TD_NOTACCESSED
mdefine_line|#define TD_NOTACCESSED     0x0F
multiline_comment|/* map OHCI TD status codes (CC) to errno values */
DECL|variable|cc_to_error
r_static
r_const
r_int
id|cc_to_error
(braket
l_int|16
)braket
op_assign
(brace
multiline_comment|/* No  Error  */
l_int|0
comma
multiline_comment|/* CRC Error  */
op_minus
id|EILSEQ
comma
multiline_comment|/* Bit Stuff  */
op_minus
id|EPROTO
comma
multiline_comment|/* Data Togg  */
op_minus
id|EILSEQ
comma
multiline_comment|/* Stall      */
op_minus
id|EPIPE
comma
multiline_comment|/* DevNotResp */
op_minus
id|ETIMEDOUT
comma
multiline_comment|/* PIDCheck   */
op_minus
id|EPROTO
comma
multiline_comment|/* UnExpPID   */
op_minus
id|EPROTO
comma
multiline_comment|/* DataOver   */
op_minus
id|EOVERFLOW
comma
multiline_comment|/* DataUnder  */
op_minus
id|EREMOTEIO
comma
multiline_comment|/* (for hw)   */
op_minus
id|EIO
comma
multiline_comment|/* (for hw)   */
op_minus
id|EIO
comma
multiline_comment|/* BufferOver */
op_minus
id|ECOMM
comma
multiline_comment|/* BuffUnder  */
op_minus
id|ENOSR
comma
multiline_comment|/* (for HCD)  */
op_minus
id|EALREADY
comma
multiline_comment|/* (for HCD)  */
op_minus
id|EALREADY
)brace
suffix:semicolon
multiline_comment|/*&n; * The HCCA (Host Controller Communications Area) is a 256 byte&n; * structure defined section 4.4.1 of the OHCI spec. The HC is&n; * told the base address of it.  It must be 256-byte aligned.&n; */
DECL|struct|ohci_hcca
r_struct
id|ohci_hcca
(brace
DECL|macro|NUM_INTS
mdefine_line|#define NUM_INTS 32
DECL|member|int_table
id|__hc32
id|int_table
(braket
id|NUM_INTS
)braket
suffix:semicolon
multiline_comment|/* periodic schedule */
multiline_comment|/* &n;&t; * OHCI defines u16 frame_no, followed by u16 zero pad.&n;&t; * Since some processors can&squot;t do 16 bit bus accesses,&n;&t; * portable access must be a 32 bit byteswapped access.&n;&t; */
DECL|member|frame_no
id|__hc32
id|frame_no
suffix:semicolon
multiline_comment|/* current frame number */
DECL|member|done_head
id|__hc32
id|done_head
suffix:semicolon
multiline_comment|/* info returned for an interrupt */
DECL|member|reserved_for_hc
id|u8
id|reserved_for_hc
(braket
l_int|116
)braket
suffix:semicolon
DECL|member|what
id|u8
id|what
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* spec only identifies 252 bytes :) */
)brace
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|256
)paren
)paren
)paren
suffix:semicolon
DECL|macro|ohci_frame_no
mdefine_line|#define ohci_frame_no(ohci) ((u16)hc32_to_cpup(ohci,&amp;(ohci)-&gt;hcca-&gt;frame_no))
multiline_comment|/*&n; * This is the structure of the OHCI controller&squot;s memory mapped I/O region.&n; * You must use readl() and writel() (in &lt;asm/io.h&gt;) to access these fields!!&n; * Layout is in section 7 (and appendix B) of the spec.&n; */
DECL|struct|ohci_regs
r_struct
id|ohci_regs
(brace
multiline_comment|/* control and status registers (section 7.1) */
DECL|member|revision
id|__hc32
id|revision
suffix:semicolon
DECL|member|control
id|__hc32
id|control
suffix:semicolon
DECL|member|cmdstatus
id|__hc32
id|cmdstatus
suffix:semicolon
DECL|member|intrstatus
id|__hc32
id|intrstatus
suffix:semicolon
DECL|member|intrenable
id|__hc32
id|intrenable
suffix:semicolon
DECL|member|intrdisable
id|__hc32
id|intrdisable
suffix:semicolon
multiline_comment|/* memory pointers (section 7.2) */
DECL|member|hcca
id|__hc32
id|hcca
suffix:semicolon
DECL|member|ed_periodcurrent
id|__hc32
id|ed_periodcurrent
suffix:semicolon
DECL|member|ed_controlhead
id|__hc32
id|ed_controlhead
suffix:semicolon
DECL|member|ed_controlcurrent
id|__hc32
id|ed_controlcurrent
suffix:semicolon
DECL|member|ed_bulkhead
id|__hc32
id|ed_bulkhead
suffix:semicolon
DECL|member|ed_bulkcurrent
id|__hc32
id|ed_bulkcurrent
suffix:semicolon
DECL|member|donehead
id|__hc32
id|donehead
suffix:semicolon
multiline_comment|/* frame counters (section 7.3) */
DECL|member|fminterval
id|__hc32
id|fminterval
suffix:semicolon
DECL|member|fmremaining
id|__hc32
id|fmremaining
suffix:semicolon
DECL|member|fmnumber
id|__hc32
id|fmnumber
suffix:semicolon
DECL|member|periodicstart
id|__hc32
id|periodicstart
suffix:semicolon
DECL|member|lsthresh
id|__hc32
id|lsthresh
suffix:semicolon
multiline_comment|/* Root hub ports (section 7.4) */
DECL|struct|ohci_roothub_regs
r_struct
id|ohci_roothub_regs
(brace
DECL|member|a
id|__hc32
id|a
suffix:semicolon
DECL|member|b
id|__hc32
id|b
suffix:semicolon
DECL|member|status
id|__hc32
id|status
suffix:semicolon
DECL|macro|MAX_ROOT_PORTS
mdefine_line|#define MAX_ROOT_PORTS&t;15&t;/* maximum OHCI root hub ports (RH_A_NDP) */
DECL|member|portstatus
id|__hc32
id|portstatus
(braket
id|MAX_ROOT_PORTS
)braket
suffix:semicolon
DECL|member|roothub
)brace
id|roothub
suffix:semicolon
multiline_comment|/* and optional &quot;legacy support&quot; registers (appendix B) at 0x0100 */
)brace
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|32
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* OHCI CONTROL AND STATUS REGISTER MASKS */
multiline_comment|/*&n; * HcControl (control) register masks&n; */
DECL|macro|OHCI_CTRL_CBSR
mdefine_line|#define OHCI_CTRL_CBSR&t;(3 &lt;&lt; 0)&t;/* control/bulk service ratio */
DECL|macro|OHCI_CTRL_PLE
mdefine_line|#define OHCI_CTRL_PLE&t;(1 &lt;&lt; 2)&t;/* periodic list enable */
DECL|macro|OHCI_CTRL_IE
mdefine_line|#define OHCI_CTRL_IE&t;(1 &lt;&lt; 3)&t;/* isochronous enable */
DECL|macro|OHCI_CTRL_CLE
mdefine_line|#define OHCI_CTRL_CLE&t;(1 &lt;&lt; 4)&t;/* control list enable */
DECL|macro|OHCI_CTRL_BLE
mdefine_line|#define OHCI_CTRL_BLE&t;(1 &lt;&lt; 5)&t;/* bulk list enable */
DECL|macro|OHCI_CTRL_HCFS
mdefine_line|#define OHCI_CTRL_HCFS&t;(3 &lt;&lt; 6)&t;/* host controller functional state */
DECL|macro|OHCI_CTRL_IR
mdefine_line|#define OHCI_CTRL_IR&t;(1 &lt;&lt; 8)&t;/* interrupt routing */
DECL|macro|OHCI_CTRL_RWC
mdefine_line|#define OHCI_CTRL_RWC&t;(1 &lt;&lt; 9)&t;/* remote wakeup connected */
DECL|macro|OHCI_CTRL_RWE
mdefine_line|#define OHCI_CTRL_RWE&t;(1 &lt;&lt; 10)&t;/* remote wakeup enable */
multiline_comment|/* pre-shifted values for HCFS */
DECL|macro|OHCI_USB_RESET
macro_line|#&t;define OHCI_USB_RESET&t;(0 &lt;&lt; 6)
DECL|macro|OHCI_USB_RESUME
macro_line|#&t;define OHCI_USB_RESUME&t;(1 &lt;&lt; 6)
DECL|macro|OHCI_USB_OPER
macro_line|#&t;define OHCI_USB_OPER&t;(2 &lt;&lt; 6)
DECL|macro|OHCI_USB_SUSPEND
macro_line|#&t;define OHCI_USB_SUSPEND&t;(3 &lt;&lt; 6)
multiline_comment|/*&n; * HcCommandStatus (cmdstatus) register masks&n; */
DECL|macro|OHCI_HCR
mdefine_line|#define OHCI_HCR&t;(1 &lt;&lt; 0)&t;/* host controller reset */
DECL|macro|OHCI_CLF
mdefine_line|#define OHCI_CLF  &t;(1 &lt;&lt; 1)&t;/* control list filled */
DECL|macro|OHCI_BLF
mdefine_line|#define OHCI_BLF  &t;(1 &lt;&lt; 2)&t;/* bulk list filled */
DECL|macro|OHCI_OCR
mdefine_line|#define OHCI_OCR  &t;(1 &lt;&lt; 3)&t;/* ownership change request */
DECL|macro|OHCI_SOC
mdefine_line|#define OHCI_SOC  &t;(3 &lt;&lt; 16)&t;/* scheduling overrun count */
multiline_comment|/*&n; * masks used with interrupt registers:&n; * HcInterruptStatus (intrstatus)&n; * HcInterruptEnable (intrenable)&n; * HcInterruptDisable (intrdisable)&n; */
DECL|macro|OHCI_INTR_SO
mdefine_line|#define OHCI_INTR_SO&t;(1 &lt;&lt; 0)&t;/* scheduling overrun */
DECL|macro|OHCI_INTR_WDH
mdefine_line|#define OHCI_INTR_WDH&t;(1 &lt;&lt; 1)&t;/* writeback of done_head */
DECL|macro|OHCI_INTR_SF
mdefine_line|#define OHCI_INTR_SF&t;(1 &lt;&lt; 2)&t;/* start frame */
DECL|macro|OHCI_INTR_RD
mdefine_line|#define OHCI_INTR_RD&t;(1 &lt;&lt; 3)&t;/* resume detect */
DECL|macro|OHCI_INTR_UE
mdefine_line|#define OHCI_INTR_UE&t;(1 &lt;&lt; 4)&t;/* unrecoverable error */
DECL|macro|OHCI_INTR_FNO
mdefine_line|#define OHCI_INTR_FNO&t;(1 &lt;&lt; 5)&t;/* frame number overflow */
DECL|macro|OHCI_INTR_RHSC
mdefine_line|#define OHCI_INTR_RHSC&t;(1 &lt;&lt; 6)&t;/* root hub status change */
DECL|macro|OHCI_INTR_OC
mdefine_line|#define OHCI_INTR_OC&t;(1 &lt;&lt; 30)&t;/* ownership change */
DECL|macro|OHCI_INTR_MIE
mdefine_line|#define OHCI_INTR_MIE&t;(1 &lt;&lt; 31)&t;/* master interrupt enable */
multiline_comment|/* OHCI ROOT HUB REGISTER MASKS */
multiline_comment|/* roothub.portstatus [i] bits */
DECL|macro|RH_PS_CCS
mdefine_line|#define RH_PS_CCS            0x00000001   &t;/* current connect status */
DECL|macro|RH_PS_PES
mdefine_line|#define RH_PS_PES            0x00000002   &t;/* port enable status*/
DECL|macro|RH_PS_PSS
mdefine_line|#define RH_PS_PSS            0x00000004   &t;/* port suspend status */
DECL|macro|RH_PS_POCI
mdefine_line|#define RH_PS_POCI           0x00000008   &t;/* port over current indicator */
DECL|macro|RH_PS_PRS
mdefine_line|#define RH_PS_PRS            0x00000010  &t;/* port reset status */
DECL|macro|RH_PS_PPS
mdefine_line|#define RH_PS_PPS            0x00000100   &t;/* port power status */
DECL|macro|RH_PS_LSDA
mdefine_line|#define RH_PS_LSDA           0x00000200    &t;/* low speed device attached */
DECL|macro|RH_PS_CSC
mdefine_line|#define RH_PS_CSC            0x00010000 &t;/* connect status change */
DECL|macro|RH_PS_PESC
mdefine_line|#define RH_PS_PESC           0x00020000   &t;/* port enable status change */
DECL|macro|RH_PS_PSSC
mdefine_line|#define RH_PS_PSSC           0x00040000    &t;/* port suspend status change */
DECL|macro|RH_PS_OCIC
mdefine_line|#define RH_PS_OCIC           0x00080000    &t;/* over current indicator change */
DECL|macro|RH_PS_PRSC
mdefine_line|#define RH_PS_PRSC           0x00100000   &t;/* port reset status change */
multiline_comment|/* roothub.status bits */
DECL|macro|RH_HS_LPS
mdefine_line|#define RH_HS_LPS&t;     0x00000001&t;&t;/* local power status */
DECL|macro|RH_HS_OCI
mdefine_line|#define RH_HS_OCI&t;     0x00000002&t;&t;/* over current indicator */
DECL|macro|RH_HS_DRWE
mdefine_line|#define RH_HS_DRWE&t;     0x00008000&t;&t;/* device remote wakeup enable */
DECL|macro|RH_HS_LPSC
mdefine_line|#define RH_HS_LPSC&t;     0x00010000&t;&t;/* local power status change */
DECL|macro|RH_HS_OCIC
mdefine_line|#define RH_HS_OCIC&t;     0x00020000&t;&t;/* over current indicator change */
DECL|macro|RH_HS_CRWE
mdefine_line|#define RH_HS_CRWE&t;     0x80000000&t;&t;/* clear remote wakeup enable */
multiline_comment|/* roothub.b masks */
DECL|macro|RH_B_DR
mdefine_line|#define RH_B_DR&t;&t;0x0000ffff&t;&t;/* device removable flags */
DECL|macro|RH_B_PPCM
mdefine_line|#define RH_B_PPCM&t;0xffff0000&t;&t;/* port power control mask */
multiline_comment|/* roothub.a masks */
DECL|macro|RH_A_NDP
mdefine_line|#define&t;RH_A_NDP&t;(0xff &lt;&lt; 0)&t;&t;/* number of downstream ports */
DECL|macro|RH_A_PSM
mdefine_line|#define&t;RH_A_PSM&t;(1 &lt;&lt; 8)&t;&t;/* power switching mode */
DECL|macro|RH_A_NPS
mdefine_line|#define&t;RH_A_NPS&t;(1 &lt;&lt; 9)&t;&t;/* no power switching */
DECL|macro|RH_A_DT
mdefine_line|#define&t;RH_A_DT&t;&t;(1 &lt;&lt; 10)&t;&t;/* device type (mbz) */
DECL|macro|RH_A_OCPM
mdefine_line|#define&t;RH_A_OCPM&t;(1 &lt;&lt; 11)&t;&t;/* over current protection mode */
DECL|macro|RH_A_NOCP
mdefine_line|#define&t;RH_A_NOCP&t;(1 &lt;&lt; 12)&t;&t;/* no over current protection */
DECL|macro|RH_A_POTPGT
mdefine_line|#define&t;RH_A_POTPGT&t;(0xff &lt;&lt; 24)&t;&t;/* power on to power good time */
multiline_comment|/* hcd-private per-urb state */
DECL|struct|urb_priv
r_typedef
r_struct
id|urb_priv
(brace
DECL|member|ed
r_struct
id|ed
op_star
id|ed
suffix:semicolon
DECL|member|length
id|u16
id|length
suffix:semicolon
singleline_comment|// # tds in this request
DECL|member|td_cnt
id|u16
id|td_cnt
suffix:semicolon
singleline_comment|// tds already serviced
DECL|member|pending
r_struct
id|list_head
id|pending
suffix:semicolon
DECL|member|td
r_struct
id|td
op_star
id|td
(braket
l_int|0
)braket
suffix:semicolon
singleline_comment|// all TDs in this request
DECL|typedef|urb_priv_t
)brace
id|urb_priv_t
suffix:semicolon
DECL|macro|TD_HASH_SIZE
mdefine_line|#define TD_HASH_SIZE    64    /* power&squot;o&squot;two */
singleline_comment|// sizeof (struct td) ~= 64 == 2^6 ... 
DECL|macro|TD_HASH_FUNC
mdefine_line|#define TD_HASH_FUNC(td_dma) ((td_dma ^ (td_dma &gt;&gt; 6)) % TD_HASH_SIZE)
multiline_comment|/*&n; * This is the full ohci controller description&n; *&n; * Note how the &quot;proper&quot; USB information is just&n; * a subset of what the full implementation needs. (Linus)&n; */
DECL|struct|ohci_hcd
r_struct
id|ohci_hcd
(brace
multiline_comment|/*&n;&t; * framework state&n;&t; */
DECL|member|hcd
r_struct
id|usb_hcd
id|hcd
suffix:semicolon
multiline_comment|/* must come first! */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/*&n;&t; * I/O memory used to communicate with the HC (dma-consistent)&n;&t; */
DECL|member|regs
r_struct
id|ohci_regs
id|__iomem
op_star
id|regs
suffix:semicolon
multiline_comment|/*&n;&t; * main memory used to communicate with the HC (dma-consistent).&n;&t; * hcd adds to schedule for a live hc any time, but removals finish&n;&t; * only at the start of the next frame.&n;&t; */
DECL|member|hcca
r_struct
id|ohci_hcca
op_star
id|hcca
suffix:semicolon
DECL|member|hcca_dma
id|dma_addr_t
id|hcca_dma
suffix:semicolon
DECL|member|ed_rm_list
r_struct
id|ed
op_star
id|ed_rm_list
suffix:semicolon
multiline_comment|/* to be removed */
DECL|member|ed_bulktail
r_struct
id|ed
op_star
id|ed_bulktail
suffix:semicolon
multiline_comment|/* last in bulk list */
DECL|member|ed_controltail
r_struct
id|ed
op_star
id|ed_controltail
suffix:semicolon
multiline_comment|/* last in ctrl list */
DECL|member|periodic
r_struct
id|ed
op_star
id|periodic
(braket
id|NUM_INTS
)braket
suffix:semicolon
multiline_comment|/* shadow int_table */
multiline_comment|/*&n;&t; * OTG controllers and transceivers need software interaction;&n;&t; * other external transceivers should be software-transparent &n;&t; */
DECL|member|transceiver
r_struct
id|otg_transceiver
op_star
id|transceiver
suffix:semicolon
DECL|member|power_budget
r_int
id|power_budget
suffix:semicolon
multiline_comment|/*&n;&t; * memory management for queue data structures&n;&t; */
DECL|member|td_cache
r_struct
id|dma_pool
op_star
id|td_cache
suffix:semicolon
DECL|member|ed_cache
r_struct
id|dma_pool
op_star
id|ed_cache
suffix:semicolon
DECL|member|td_hash
r_struct
id|td
op_star
id|td_hash
(braket
id|TD_HASH_SIZE
)braket
suffix:semicolon
DECL|member|pending
r_struct
id|list_head
id|pending
suffix:semicolon
multiline_comment|/*&n;&t; * driver state&n;&t; */
DECL|member|load
r_int
id|load
(braket
id|NUM_INTS
)braket
suffix:semicolon
DECL|member|hc_control
id|u32
id|hc_control
suffix:semicolon
multiline_comment|/* copy of hc control reg */
DECL|member|next_statechange
r_int
r_int
id|next_statechange
suffix:semicolon
multiline_comment|/* suspend/resume */
DECL|member|fminterval
id|u32
id|fminterval
suffix:semicolon
multiline_comment|/* saved register */
DECL|member|rh_resume
r_struct
id|work_struct
id|rh_resume
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* for HC bugs */
DECL|macro|OHCI_QUIRK_AMD756
mdefine_line|#define&t;OHCI_QUIRK_AMD756&t;0x01&t;&t;&t;/* erratum #4 */
DECL|macro|OHCI_QUIRK_SUPERIO
mdefine_line|#define&t;OHCI_QUIRK_SUPERIO&t;0x02&t;&t;&t;/* natsemi */
DECL|macro|OHCI_QUIRK_INITRESET
mdefine_line|#define&t;OHCI_QUIRK_INITRESET&t;0x04&t;&t;&t;/* SiS, OPTi, ... */
DECL|macro|OHCI_BIG_ENDIAN
mdefine_line|#define&t;OHCI_BIG_ENDIAN&t;&t;0x08&t;&t;&t;/* big endian HC */
singleline_comment|// there are also chip quirks/bugs in init logic
)brace
suffix:semicolon
DECL|macro|hcd_to_ohci
mdefine_line|#define hcd_to_ohci(hcd_ptr) container_of(hcd_ptr, struct ohci_hcd, hcd)
multiline_comment|/*-------------------------------------------------------------------------*/
macro_line|#ifndef DEBUG
DECL|macro|STUB_DEBUG_FILES
mdefine_line|#define STUB_DEBUG_FILES
macro_line|#endif&t;/* DEBUG */
DECL|macro|ohci_dbg
mdefine_line|#define ohci_dbg(ohci, fmt, args...) &bslash;&n;&t;dev_dbg ((ohci)-&gt;hcd.self.controller , fmt , ## args )
DECL|macro|ohci_err
mdefine_line|#define ohci_err(ohci, fmt, args...) &bslash;&n;&t;dev_err ((ohci)-&gt;hcd.self.controller , fmt , ## args )
DECL|macro|ohci_info
mdefine_line|#define ohci_info(ohci, fmt, args...) &bslash;&n;&t;dev_info ((ohci)-&gt;hcd.self.controller , fmt , ## args )
DECL|macro|ohci_warn
mdefine_line|#define ohci_warn(ohci, fmt, args...) &bslash;&n;&t;dev_warn ((ohci)-&gt;hcd.self.controller , fmt , ## args )
macro_line|#ifdef OHCI_VERBOSE_DEBUG
DECL|macro|ohci_vdbg
macro_line|#&t;define ohci_vdbg ohci_dbg
macro_line|#else
DECL|macro|ohci_vdbg
macro_line|#&t;define ohci_vdbg(ohci, fmt, args...) do { } while (0)
macro_line|#endif
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * While most USB host controllers implement their registers and&n; * in-memory communication descriptors in little-endian format,&n; * a minority (notably the IBM STB04XXX and the Motorola MPC5200&n; * processors) implement them in big endian format.&n; *&n; * This attempts to support either format at compile time without a&n; * runtime penalty, or both formats with the additional overhead&n; * of checking a flag bit.&n; */
macro_line|#ifdef CONFIG_USB_OHCI_BIG_ENDIAN
macro_line|#ifdef CONFIG_USB_OHCI_LITTLE_ENDIAN
DECL|macro|big_endian
mdefine_line|#define big_endian(ohci)&t;(ohci-&gt;flags &amp; OHCI_BIG_ENDIAN) /* either */
macro_line|#else
DECL|macro|big_endian
mdefine_line|#define big_endian(ohci)&t;1&t;&t;/* only big endian */
macro_line|#endif
multiline_comment|/*&n; * Big-endian read/write functions are arch-specific.&n; * Other arches can be added if/when they&squot;re needed.&n; */
macro_line|#if defined(CONFIG_PPC)
DECL|macro|readl_be
mdefine_line|#define readl_be(addr)&t;&t;in_be32((__force unsigned *)addr)
DECL|macro|writel_be
mdefine_line|#define writel_be(val, addr)&t;out_be32((__force unsigned *)addr, val)
macro_line|#endif
DECL|function|ohci_readl
r_static
r_inline
r_int
r_int
id|ohci_readl
(paren
r_const
r_struct
id|ohci_hcd
op_star
id|ohci
comma
id|__hc32
id|__iomem
op_star
id|regs
)paren
(brace
r_return
id|big_endian
c_func
(paren
id|ohci
)paren
ques
c_cond
id|readl_be
(paren
id|regs
)paren
suffix:colon
id|readl
(paren
(paren
id|__force
id|u32
op_star
)paren
id|regs
)paren
suffix:semicolon
)brace
DECL|function|ohci_writel
r_static
r_inline
r_void
id|ohci_writel
(paren
r_const
r_struct
id|ohci_hcd
op_star
id|ohci
comma
r_const
r_int
r_int
id|val
comma
id|__hc32
id|__iomem
op_star
id|regs
)paren
(brace
id|big_endian
c_func
(paren
id|ohci
)paren
ques
c_cond
id|writel_be
(paren
id|val
comma
id|regs
)paren
suffix:colon
id|writel
(paren
id|val
comma
(paren
id|__force
id|u32
op_star
)paren
id|regs
)paren
suffix:semicolon
)brace
macro_line|#else&t;/* !CONFIG_USB_OHCI_BIG_ENDIAN */
DECL|macro|big_endian
mdefine_line|#define big_endian(ohci)&t;0&t;&t;/* only little endian */
macro_line|#ifdef CONFIG_ARCH_LH7A404
multiline_comment|/* Marc Singer: at the time this code was written, the LH7A404&n;&t; * had a problem reading the USB host registers.  This&n;&t; * implementation of the ohci_readl function performs the read&n;&t; * twice as a work-around.&n;&t; */
r_static
r_inline
r_int
r_int
DECL|function|ohci_readl
id|ohci_readl
(paren
r_const
r_struct
id|ohci_hcd
op_star
id|ohci
comma
r_const
id|__hc32
op_star
id|regs
)paren
(brace
op_star
(paren
r_volatile
id|__force
r_int
r_int
op_star
)paren
id|regs
suffix:semicolon
r_return
op_star
(paren
r_volatile
id|__force
r_int
r_int
op_star
)paren
id|regs
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/* Standard version of ohci_readl uses standard, platform&n;&t; * specific implementation. */
r_static
r_inline
r_int
r_int
DECL|function|ohci_readl
id|ohci_readl
(paren
r_const
r_struct
id|ohci_hcd
op_star
id|ohci
comma
id|__hc32
id|__iomem
op_star
id|regs
)paren
(brace
r_return
id|readl
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|ohci_writel
r_static
r_inline
r_void
id|ohci_writel
(paren
r_const
r_struct
id|ohci_hcd
op_star
id|ohci
comma
r_const
r_int
r_int
id|val
comma
id|__hc32
id|__iomem
op_star
id|regs
)paren
(brace
id|writel
(paren
id|val
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* !CONFIG_USB_OHCI_BIG_ENDIAN */
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* cpu to ohci */
DECL|function|cpu_to_hc16
r_static
r_inline
id|__hc16
id|cpu_to_hc16
(paren
r_const
r_struct
id|ohci_hcd
op_star
id|ohci
comma
r_const
id|u16
id|x
)paren
(brace
r_return
id|big_endian
c_func
(paren
id|ohci
)paren
ques
c_cond
id|cpu_to_be16
c_func
(paren
id|x
)paren
suffix:colon
id|cpu_to_le16
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|cpu_to_hc16p
r_static
r_inline
id|__hc16
id|cpu_to_hc16p
(paren
r_const
r_struct
id|ohci_hcd
op_star
id|ohci
comma
r_const
id|u16
op_star
id|x
)paren
(brace
r_return
id|big_endian
c_func
(paren
id|ohci
)paren
ques
c_cond
id|cpu_to_be16p
c_func
(paren
id|x
)paren
suffix:colon
id|cpu_to_le16p
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|cpu_to_hc32
r_static
r_inline
id|__hc32
id|cpu_to_hc32
(paren
r_const
r_struct
id|ohci_hcd
op_star
id|ohci
comma
r_const
id|u32
id|x
)paren
(brace
r_return
id|big_endian
c_func
(paren
id|ohci
)paren
ques
c_cond
id|cpu_to_be32
c_func
(paren
id|x
)paren
suffix:colon
id|cpu_to_le32
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|cpu_to_hc32p
r_static
r_inline
id|__hc32
id|cpu_to_hc32p
(paren
r_const
r_struct
id|ohci_hcd
op_star
id|ohci
comma
r_const
id|u32
op_star
id|x
)paren
(brace
r_return
id|big_endian
c_func
(paren
id|ohci
)paren
ques
c_cond
id|cpu_to_be32p
c_func
(paren
id|x
)paren
suffix:colon
id|cpu_to_le32p
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
multiline_comment|/* ohci to cpu */
DECL|function|hc16_to_cpu
r_static
r_inline
id|u16
id|hc16_to_cpu
(paren
r_const
r_struct
id|ohci_hcd
op_star
id|ohci
comma
r_const
id|__hc16
id|x
)paren
(brace
r_return
id|big_endian
c_func
(paren
id|ohci
)paren
ques
c_cond
id|be16_to_cpu
c_func
(paren
id|x
)paren
suffix:colon
id|le16_to_cpu
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|hc16_to_cpup
r_static
r_inline
id|u16
id|hc16_to_cpup
(paren
r_const
r_struct
id|ohci_hcd
op_star
id|ohci
comma
r_const
id|__hc16
op_star
id|x
)paren
(brace
r_return
id|big_endian
c_func
(paren
id|ohci
)paren
ques
c_cond
id|be16_to_cpup
c_func
(paren
id|x
)paren
suffix:colon
id|le16_to_cpup
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|hc32_to_cpu
r_static
r_inline
id|u32
id|hc32_to_cpu
(paren
r_const
r_struct
id|ohci_hcd
op_star
id|ohci
comma
r_const
id|__hc32
id|x
)paren
(brace
r_return
id|big_endian
c_func
(paren
id|ohci
)paren
ques
c_cond
id|be32_to_cpu
c_func
(paren
id|x
)paren
suffix:colon
id|le32_to_cpu
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|hc32_to_cpup
r_static
r_inline
id|u32
id|hc32_to_cpup
(paren
r_const
r_struct
id|ohci_hcd
op_star
id|ohci
comma
r_const
id|__hc32
op_star
id|x
)paren
(brace
r_return
id|big_endian
c_func
(paren
id|ohci
)paren
ques
c_cond
id|be32_to_cpup
c_func
(paren
id|x
)paren
suffix:colon
id|le32_to_cpup
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|function|disable
r_static
r_inline
r_void
id|disable
(paren
r_struct
id|ohci_hcd
op_star
id|ohci
)paren
(brace
id|ohci-&gt;hcd.state
op_assign
id|USB_STATE_HALT
suffix:semicolon
)brace
DECL|macro|FI
mdefine_line|#define&t;FI&t;&t;&t;0x2edf&t;&t;/* 12000 bits per frame (-1) */
DECL|macro|FSMP
mdefine_line|#define&t;FSMP(fi) &t;&t;(0x7fff &amp; ((6 * ((fi) - 210)) / 7))
DECL|macro|LSTHRESH
mdefine_line|#define LSTHRESH&t;&t;0x628&t;&t;/* lowspeed bit threshold */
DECL|function|periodic_reinit
r_static
r_inline
r_void
id|periodic_reinit
(paren
r_struct
id|ohci_hcd
op_star
id|ohci
)paren
(brace
id|u32
id|fi
op_assign
id|ohci-&gt;fminterval
op_amp
l_int|0x0ffff
suffix:semicolon
id|ohci_writel
(paren
id|ohci
comma
(paren
(paren
l_int|9
op_star
id|fi
)paren
op_div
l_int|10
)paren
op_amp
l_int|0x3fff
comma
op_amp
id|ohci-&gt;regs-&gt;periodicstart
)paren
suffix:semicolon
)brace
multiline_comment|/* AMD-756 (D2 rev) reports corrupt register contents in some cases.&n; * The erratum (#4) description is incorrect.  AMD&squot;s workaround waits&n; * till some bits (mostly reserved) are clear; ok for all revs.&n; */
DECL|macro|read_roothub
mdefine_line|#define read_roothub(hc, register, mask) ({ &bslash;&n;&t;u32 temp = ohci_readl (hc, &amp;hc-&gt;regs-&gt;roothub.register); &bslash;&n;&t;if (temp == -1) &bslash;&n;&t;&t;disable (hc); &bslash;&n;&t;else if (hc-&gt;flags &amp; OHCI_QUIRK_AMD756) &bslash;&n;&t;&t;while (temp &amp; mask) &bslash;&n;&t;&t;&t;temp = ohci_readl (hc, &amp;hc-&gt;regs-&gt;roothub.register); &bslash;&n;&t;temp; })
DECL|function|roothub_a
r_static
id|u32
id|roothub_a
(paren
r_struct
id|ohci_hcd
op_star
id|hc
)paren
(brace
r_return
id|read_roothub
(paren
id|hc
comma
id|a
comma
l_int|0xfc0fe000
)paren
suffix:semicolon
)brace
DECL|function|roothub_b
r_static
r_inline
id|u32
id|roothub_b
(paren
r_struct
id|ohci_hcd
op_star
id|hc
)paren
(brace
r_return
id|ohci_readl
(paren
id|hc
comma
op_amp
id|hc-&gt;regs-&gt;roothub.b
)paren
suffix:semicolon
)brace
DECL|function|roothub_status
r_static
r_inline
id|u32
id|roothub_status
(paren
r_struct
id|ohci_hcd
op_star
id|hc
)paren
(brace
r_return
id|ohci_readl
(paren
id|hc
comma
op_amp
id|hc-&gt;regs-&gt;roothub.status
)paren
suffix:semicolon
)brace
DECL|function|roothub_portstatus
r_static
id|u32
id|roothub_portstatus
(paren
r_struct
id|ohci_hcd
op_star
id|hc
comma
r_int
id|i
)paren
(brace
r_return
id|read_roothub
(paren
id|hc
comma
id|portstatus
(braket
id|i
)braket
comma
l_int|0xffe0fce0
)paren
suffix:semicolon
)brace
eof
