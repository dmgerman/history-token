multiline_comment|/*&n; * OHCI HCD (Host Controller Driver) for USB.&n; * &n; * (C) Copyright 1999 Roman Weissgaerber &lt;weissg@vienna.at&gt;&n; * (C) Copyright 2000-2001 David Brownell &lt;dbrownell@users.sourceforge.net&gt;&n; * &n; * This file is licenced under GPL&n; * $Id: ohci.h,v 1.5 2002/01/19 00:24:01 dbrownell Exp $&n; */
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
multiline_comment|/* map OHCI status to errno values */
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
multiline_comment|/* ED States */
DECL|macro|ED_NEW
mdefine_line|#define ED_NEW &t;&t;0x00&t;&t;/* unused, no dummy td */
DECL|macro|ED_UNLINK
mdefine_line|#define ED_UNLINK &t;0x01&t;&t;/* dummy td, maybe linked to hc */
DECL|macro|ED_OPER
mdefine_line|#define ED_OPER&t;&t;0x02&t;&t;/* dummy td, _is_ linked to hc */
DECL|macro|ED_URB_DEL
mdefine_line|#define ED_URB_DEL  &t;0x08&t;&t;/* masked in */
multiline_comment|/* usb_ohci_ed */
DECL|struct|ed
r_struct
id|ed
(brace
multiline_comment|/* first fields are hardware-specified */
DECL|member|hwINFO
id|__u32
id|hwINFO
suffix:semicolon
DECL|member|hwTailP
id|__u32
id|hwTailP
suffix:semicolon
DECL|member|hwHeadP
id|__u32
id|hwHeadP
suffix:semicolon
DECL|member|hwNextED
id|__u32
id|hwNextED
suffix:semicolon
DECL|member|ed_prev
r_struct
id|ed
op_star
id|ed_prev
suffix:semicolon
DECL|member|int_period
id|__u8
id|int_period
suffix:semicolon
DECL|member|int_branch
id|__u8
id|int_branch
suffix:semicolon
DECL|member|int_load
id|__u8
id|int_load
suffix:semicolon
DECL|member|int_interval
id|__u8
id|int_interval
suffix:semicolon
DECL|member|state
id|__u8
id|state
suffix:semicolon
singleline_comment|// ED_{NEW,UNLINK,OPER}
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|last_iso
id|__u16
id|last_iso
suffix:semicolon
DECL|member|ed_rm_list
r_struct
id|ed
op_star
id|ed_rm_list
suffix:semicolon
DECL|member|dma
id|dma_addr_t
id|dma
suffix:semicolon
DECL|member|unused
id|__u32
id|unused
(braket
l_int|3
)braket
suffix:semicolon
)brace
id|__attribute
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
multiline_comment|/* TD info field */
DECL|macro|TD_CC
mdefine_line|#define TD_CC       0xf0000000
DECL|macro|TD_CC_GET
mdefine_line|#define TD_CC_GET(td_p) ((td_p &gt;&gt;28) &amp; 0x0f)
DECL|macro|TD_CC_SET
mdefine_line|#define TD_CC_SET(td_p, cc) (td_p) = ((td_p) &amp; 0x0fffffff) | (((cc) &amp; 0x0f) &lt;&lt; 28)
DECL|macro|TD_EC
mdefine_line|#define TD_EC       0x0C000000
DECL|macro|TD_T
mdefine_line|#define TD_T        0x03000000
DECL|macro|TD_T_DATA0
mdefine_line|#define TD_T_DATA0  0x02000000
DECL|macro|TD_T_DATA1
mdefine_line|#define TD_T_DATA1  0x03000000
DECL|macro|TD_T_TOGGLE
mdefine_line|#define TD_T_TOGGLE 0x00000000
DECL|macro|TD_R
mdefine_line|#define TD_R        0x00040000
DECL|macro|TD_DI
mdefine_line|#define TD_DI       0x00E00000
DECL|macro|TD_DI_SET
mdefine_line|#define TD_DI_SET(X) (((X) &amp; 0x07)&lt;&lt; 21)
DECL|macro|TD_DP
mdefine_line|#define TD_DP       0x00180000
DECL|macro|TD_DP_SETUP
mdefine_line|#define TD_DP_SETUP 0x00000000
DECL|macro|TD_DP_IN
mdefine_line|#define TD_DP_IN    0x00100000
DECL|macro|TD_DP_OUT
mdefine_line|#define TD_DP_OUT   0x00080000
DECL|macro|TD_ISO
mdefine_line|#define TD_ISO&t;    0x00010000
DECL|macro|TD_DEL
mdefine_line|#define TD_DEL      0x00020000
multiline_comment|/* CC Codes */
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
DECL|macro|MAXPSW
mdefine_line|#define MAXPSW 1
DECL|struct|td
r_struct
id|td
(brace
multiline_comment|/* first hardware fields are in all tds */
DECL|member|hwINFO
id|__u32
id|hwINFO
suffix:semicolon
DECL|member|hwCBP
id|__u32
id|hwCBP
suffix:semicolon
multiline_comment|/* Current Buffer Pointer */
DECL|member|hwNextTD
id|__u32
id|hwNextTD
suffix:semicolon
multiline_comment|/* Next TD Pointer */
DECL|member|hwBE
id|__u32
id|hwBE
suffix:semicolon
multiline_comment|/* Memory Buffer End Pointer */
DECL|member|hwPSW
id|__u16
id|hwPSW
(braket
id|MAXPSW
)braket
suffix:semicolon
multiline_comment|/* PSW is only for ISO */
DECL|member|unused
id|__u8
id|unused
suffix:semicolon
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
DECL|member|data_dma
id|dma_addr_t
id|data_dma
suffix:semicolon
DECL|member|unused2
id|__u32
id|unused2
(braket
l_int|2
)braket
suffix:semicolon
)brace
id|__attribute
c_func
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
multiline_comment|/* iso needs 32 */
DECL|macro|OHCI_ED_SKIP
mdefine_line|#define OHCI_ED_SKIP&t;(1 &lt;&lt; 14)
multiline_comment|/*&n; * The HCCA (Host Controller Communications Area) is a 256 byte&n; * structure defined in the OHCI spec. The host controller is&n; * told the base address of it.  It must be 256-byte aligned.&n; */
DECL|macro|NUM_INTS
mdefine_line|#define NUM_INTS 32&t;/* part of the OHCI standard */
DECL|struct|ohci_hcca
r_struct
id|ohci_hcca
(brace
DECL|member|int_table
id|__u32
id|int_table
(braket
id|NUM_INTS
)braket
suffix:semicolon
multiline_comment|/* Interrupt ED table */
DECL|member|frame_no
id|__u16
id|frame_no
suffix:semicolon
multiline_comment|/* current frame number */
DECL|member|pad1
id|__u16
id|pad1
suffix:semicolon
multiline_comment|/* set to 0 on each frame_no change */
DECL|member|done_head
id|__u32
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
)brace
id|__attribute
c_func
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
multiline_comment|/*&n; * Maximum number of root hub ports.  &n; */
DECL|macro|MAX_ROOT_PORTS
mdefine_line|#define MAX_ROOT_PORTS&t;15&t;/* maximum OHCI root hub ports */
multiline_comment|/*&n; * This is the structure of the OHCI controller&squot;s memory mapped I/O&n; * region.  This is Memory Mapped I/O.  You must use the readl() and&n; * writel() macros defined in asm/io.h to access these!!&n; */
DECL|struct|ohci_regs
r_struct
id|ohci_regs
(brace
multiline_comment|/* control and status registers */
DECL|member|revision
id|__u32
id|revision
suffix:semicolon
DECL|member|control
id|__u32
id|control
suffix:semicolon
DECL|member|cmdstatus
id|__u32
id|cmdstatus
suffix:semicolon
DECL|member|intrstatus
id|__u32
id|intrstatus
suffix:semicolon
DECL|member|intrenable
id|__u32
id|intrenable
suffix:semicolon
DECL|member|intrdisable
id|__u32
id|intrdisable
suffix:semicolon
multiline_comment|/* memory pointers */
DECL|member|hcca
id|__u32
id|hcca
suffix:semicolon
DECL|member|ed_periodcurrent
id|__u32
id|ed_periodcurrent
suffix:semicolon
DECL|member|ed_controlhead
id|__u32
id|ed_controlhead
suffix:semicolon
DECL|member|ed_controlcurrent
id|__u32
id|ed_controlcurrent
suffix:semicolon
DECL|member|ed_bulkhead
id|__u32
id|ed_bulkhead
suffix:semicolon
DECL|member|ed_bulkcurrent
id|__u32
id|ed_bulkcurrent
suffix:semicolon
DECL|member|donehead
id|__u32
id|donehead
suffix:semicolon
multiline_comment|/* frame counters */
DECL|member|fminterval
id|__u32
id|fminterval
suffix:semicolon
DECL|member|fmremaining
id|__u32
id|fmremaining
suffix:semicolon
DECL|member|fmnumber
id|__u32
id|fmnumber
suffix:semicolon
DECL|member|periodicstart
id|__u32
id|periodicstart
suffix:semicolon
DECL|member|lsthresh
id|__u32
id|lsthresh
suffix:semicolon
multiline_comment|/* Root hub ports */
DECL|struct|ohci_roothub_regs
r_struct
id|ohci_roothub_regs
(brace
DECL|member|a
id|__u32
id|a
suffix:semicolon
DECL|member|b
id|__u32
id|b
suffix:semicolon
DECL|member|status
id|__u32
id|status
suffix:semicolon
DECL|member|portstatus
id|__u32
id|portstatus
(braket
id|MAX_ROOT_PORTS
)braket
suffix:semicolon
DECL|member|roothub
)brace
id|roothub
suffix:semicolon
multiline_comment|/* and some optional registers for legacy compatibility */
)brace
id|__attribute
c_func
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
multiline_comment|/* urb */
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
id|__u16
id|length
suffix:semicolon
singleline_comment|// # tds in this request
DECL|member|td_cnt
id|__u16
id|td_cnt
suffix:semicolon
singleline_comment|// tds already serviced
DECL|member|state
r_int
id|state
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
DECL|macro|URB_DEL
mdefine_line|#define URB_DEL 1
multiline_comment|/* Hash struct used for TD/ED hashing */
DECL|struct|hash_t
r_struct
id|hash_t
(brace
DECL|member|virt
r_void
op_star
id|virt
suffix:semicolon
DECL|member|dma
id|dma_addr_t
id|dma
suffix:semicolon
DECL|member|next
r_struct
id|hash_t
op_star
id|next
suffix:semicolon
singleline_comment|// chaining for collision cases
)brace
suffix:semicolon
multiline_comment|/* List of TD/ED hash entries */
DECL|struct|hash_list_t
r_struct
id|hash_list_t
(brace
DECL|member|head
r_struct
id|hash_t
op_star
id|head
suffix:semicolon
DECL|member|tail
r_struct
id|hash_t
op_star
id|tail
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TD_HASH_SIZE
mdefine_line|#define TD_HASH_SIZE    64    /* power&squot;o&squot;two */
DECL|macro|ED_HASH_SIZE
mdefine_line|#define ED_HASH_SIZE    64    /* power&squot;o&squot;two */
DECL|macro|TD_HASH_FUNC
mdefine_line|#define TD_HASH_FUNC(td_dma) ((td_dma ^ (td_dma &gt;&gt; 5)) % TD_HASH_SIZE)
DECL|macro|ED_HASH_FUNC
mdefine_line|#define ED_HASH_FUNC(ed_dma) ((ed_dma ^ (ed_dma &gt;&gt; 5)) % ED_HASH_SIZE)
multiline_comment|/*&n; * This is the full ohci controller description&n; *&n; * Note how the &quot;proper&quot; USB information is just&n; * a subset of what the full implementation needs. (Linus)&n; */
DECL|struct|ohci_hcd
r_struct
id|ohci_hcd
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/*&n;&t; * I/O memory used to communicate with the HC (uncached);&n;&t; */
DECL|member|regs
r_struct
id|ohci_regs
op_star
id|regs
suffix:semicolon
multiline_comment|/*&n;&t; * main memory used to communicate with the HC (uncached)&n;&t; */
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
(braket
l_int|2
)braket
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
DECL|member|ed_isotail
r_struct
id|ed
op_star
id|ed_isotail
suffix:semicolon
multiline_comment|/* last in iso list */
macro_line|#ifdef CONFIG_PCI
DECL|member|td_cache
r_struct
id|pci_pool
op_star
id|td_cache
suffix:semicolon
DECL|member|ed_cache
r_struct
id|pci_pool
op_star
id|ed_cache
suffix:semicolon
DECL|member|td_hash
r_struct
id|hash_list_t
id|td_hash
(braket
id|TD_HASH_SIZE
)braket
suffix:semicolon
DECL|member|ed_hash
r_struct
id|hash_list_t
id|ed_hash
(braket
id|ED_HASH_SIZE
)braket
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * driver state&n;&t; */
DECL|member|disabled
r_int
id|disabled
suffix:semicolon
multiline_comment|/* e.g. got a UE, we&squot;re hung */
DECL|member|sleeping
r_int
id|sleeping
suffix:semicolon
DECL|member|ohci_int_load
r_int
id|ohci_int_load
(braket
id|NUM_INTS
)braket
suffix:semicolon
DECL|member|hc_control
id|u32
id|hc_control
suffix:semicolon
multiline_comment|/* copy of hc control reg */
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* for HC bugs */
DECL|macro|OHCI_QUIRK_AMD756
mdefine_line|#define&t;OHCI_QUIRK_AMD756&t;0x01&t;&t;&t;/* erratum #4 */
multiline_comment|/*&n;&t; * framework state&n;&t; */
DECL|member|hcd
r_struct
id|usb_hcd
id|hcd
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|hcd_to_ohci
mdefine_line|#define hcd_to_ohci(hcd_ptr) list_entry(hcd_ptr, struct ohci_hcd, hcd)
eof
