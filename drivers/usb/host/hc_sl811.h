multiline_comment|/*&n; * SL811HS HCD (Host Controller Driver) for USB.&n; * &n; * COPYRIGHT (C) by CYPRESS SEMICONDUCTOR INC &n; * &n; *&n; */
DECL|macro|GET_FRAME_NUMBER
mdefine_line|#define GET_FRAME_NUMBER(hci)&t;READ_REG32 (hci, HcFmNumber)
multiline_comment|/*&n; * Maximum number of root hub ports&n; */
DECL|macro|MAX_ROOT_PORTS
mdefine_line|#define MAX_ROOT_PORTS&t;&t;15&t;/* maximum OHCI root hub ports */
multiline_comment|/* control and status registers */
DECL|macro|HcRevision
mdefine_line|#define HcRevision&t;&t;0x00
DECL|macro|HcControl
mdefine_line|#define HcControl&t;&t;0x01
DECL|macro|HcCommandStatus
mdefine_line|#define HcCommandStatus&t;&t;0x02
DECL|macro|HcInterruptStatus
mdefine_line|#define HcInterruptStatus&t;0x03
DECL|macro|HcInterruptEnable
mdefine_line|#define HcInterruptEnable&t;0x04
DECL|macro|HcInterruptDisable
mdefine_line|#define HcInterruptDisable&t;0x05
DECL|macro|HcFmInterval
mdefine_line|#define HcFmInterval&t;&t;0x0D
DECL|macro|HcFmRemaining
mdefine_line|#define HcFmRemaining&t;&t;0x0E
DECL|macro|HcFmNumber
mdefine_line|#define HcFmNumber&t;&t;0x0F
DECL|macro|HcLSThreshold
mdefine_line|#define HcLSThreshold&t;&t;0x11
DECL|macro|HcRhDescriptorA
mdefine_line|#define HcRhDescriptorA&t;&t;0x12
DECL|macro|HcRhDescriptorB
mdefine_line|#define HcRhDescriptorB&t;&t;0x13
DECL|macro|HcRhStatus
mdefine_line|#define HcRhStatus&t;&t;0x14
DECL|macro|HcRhPortStatus
mdefine_line|#define HcRhPortStatus&t;&t;0x15
DECL|macro|HcHardwareConfiguration
mdefine_line|#define HcHardwareConfiguration 0x20
DECL|macro|HcDMAConfiguration
mdefine_line|#define HcDMAConfiguration&t;0x21
DECL|macro|HcTransferCounter
mdefine_line|#define HcTransferCounter&t;0x22
DECL|macro|HcuPInterrupt
mdefine_line|#define HcuPInterrupt&t;&t;0x24
DECL|macro|HcuPInterruptEnable
mdefine_line|#define HcuPInterruptEnable&t;0x25
DECL|macro|HcChipID
mdefine_line|#define HcChipID&t;&t;0x27
DECL|macro|HcScratch
mdefine_line|#define HcScratch&t;&t;0x28
DECL|macro|HcSoftwareReset
mdefine_line|#define HcSoftwareReset&t;&t;0x29
DECL|macro|HcITLBufferLength
mdefine_line|#define HcITLBufferLength&t;0x2A
DECL|macro|HcATLBufferLength
mdefine_line|#define HcATLBufferLength&t;0x2B
DECL|macro|HcBufferStatus
mdefine_line|#define HcBufferStatus&t;&t;0x2C
DECL|macro|HcReadBackITL0Length
mdefine_line|#define HcReadBackITL0Length&t;0x2D
DECL|macro|HcReadBackITL1Length
mdefine_line|#define HcReadBackITL1Length&t;0x2E
DECL|macro|HcITLBufferPort
mdefine_line|#define HcITLBufferPort&t;&t;0x40
DECL|macro|HcATLBufferPort
mdefine_line|#define HcATLBufferPort&t;&t;0x41
multiline_comment|/* OHCI CONTROL AND STATUS REGISTER MASKS */
multiline_comment|/*&n; * HcControl (control) register masks&n; */
DECL|macro|OHCI_CTRL_HCFS
mdefine_line|#define OHCI_CTRL_HCFS&t;&t;(3 &lt;&lt; 6)&t;/* BUS state mask */
DECL|macro|OHCI_CTRL_RWC
mdefine_line|#define OHCI_CTRL_RWC&t;&t;(1 &lt;&lt; 9)&t;/* remote wakeup connected */
DECL|macro|OHCI_CTRL_RWE
mdefine_line|#define OHCI_CTRL_RWE&t;&t;(1 &lt;&lt; 10)&t;/* remote wakeup enable */
multiline_comment|/* pre-shifted values for HCFS */
DECL|macro|OHCI_USB_RESET
mdefine_line|#define OHCI_USB_RESET&t;&t;(0 &lt;&lt; 6)
DECL|macro|OHCI_USB_RESUME
mdefine_line|#define OHCI_USB_RESUME&t;&t;(1 &lt;&lt; 6)
DECL|macro|OHCI_USB_OPER
mdefine_line|#define OHCI_USB_OPER&t;&t;(2 &lt;&lt; 6)
DECL|macro|OHCI_USB_SUSPEND
mdefine_line|#define OHCI_USB_SUSPEND&t;(3 &lt;&lt; 6)
multiline_comment|/*&n; * HcCommandStatus (cmdstatus) register masks&n; */
DECL|macro|OHCI_HCR
mdefine_line|#define OHCI_HCR&t;(1 &lt;&lt; 0)&t;/* host controller reset */
DECL|macro|OHCI_SO
mdefine_line|#define OHCI_SO&t;&t;(3 &lt;&lt; 16)&t;/* scheduling overrun count */
multiline_comment|/*&n; * masks used with interrupt registers:&n; * HcInterruptStatus (intrstatus)&n; * HcInterruptEnable (intrenable)&n; * HcInterruptDisable (intrdisable)&n; */
DECL|macro|OHCI_INTR_SO
mdefine_line|#define OHCI_INTR_SO&t;(1 &lt;&lt; 0)&t;/* scheduling overrun */
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
DECL|macro|OHCI_INTR_ATD
mdefine_line|#define OHCI_INTR_ATD&t;(1 &lt;&lt; 7)&t;/* scheduling overrun */
DECL|macro|OHCI_INTR_MIE
mdefine_line|#define OHCI_INTR_MIE&t;(1 &lt;&lt; 31)&t;/* master interrupt enable */
multiline_comment|/*&n; * HcHardwareConfiguration&n; */
DECL|macro|InterruptPinEnable
mdefine_line|#define InterruptPinEnable&t;(1 &lt;&lt; 0)
DECL|macro|InterruptPinTrigger
mdefine_line|#define InterruptPinTrigger&t;(1 &lt;&lt; 1)
DECL|macro|InterruptOutputPolarity
mdefine_line|#define InterruptOutputPolarity&t;(1 &lt;&lt; 2)
DECL|macro|DataBusWidth16
mdefine_line|#define DataBusWidth16&t;&t;(1 &lt;&lt; 3)
DECL|macro|DREQOutputPolarity
mdefine_line|#define DREQOutputPolarity&t;(1 &lt;&lt; 5)
DECL|macro|DACKInputPolarity
mdefine_line|#define DACKInputPolarity&t;(1 &lt;&lt; 6)
DECL|macro|EOTInputPolarity
mdefine_line|#define EOTInputPolarity&t;(1 &lt;&lt; 7)
DECL|macro|DACKMode
mdefine_line|#define DACKMode&t;&t;(1 &lt;&lt; 8)
DECL|macro|AnalogOCEnable
mdefine_line|#define AnalogOCEnable&t;&t;(1 &lt;&lt; 10)
DECL|macro|SuspendClkNotStop
mdefine_line|#define SuspendClkNotStop&t;(1 &lt;&lt; 11)
DECL|macro|DownstreamPort15KRSel
mdefine_line|#define DownstreamPort15KRSel&t;(1 &lt;&lt; 12)
multiline_comment|/* &n; * HcDMAConfiguration&n; */
DECL|macro|DMAReadWriteSelect
mdefine_line|#define DMAReadWriteSelect &t;(1 &lt;&lt; 0)
DECL|macro|ITL_ATL_DataSelect
mdefine_line|#define ITL_ATL_DataSelect&t;(1 &lt;&lt; 1)
DECL|macro|DMACounterSelect
mdefine_line|#define DMACounterSelect&t;(1 &lt;&lt; 2)
DECL|macro|DMAEnable
mdefine_line|#define DMAEnable&t;&t;(1 &lt;&lt; 4)
DECL|macro|BurstLen_1
mdefine_line|#define BurstLen_1&t;&t;0
DECL|macro|BurstLen_4
mdefine_line|#define BurstLen_4&t;&t;(1 &lt;&lt; 5)
DECL|macro|BurstLen_8
mdefine_line|#define BurstLen_8&t;&t;(2 &lt;&lt; 5)
multiline_comment|/*&n; * HcuPInterrupt&n; */
DECL|macro|SOFITLInt
mdefine_line|#define SOFITLInt&t;&t;(1 &lt;&lt; 0)
DECL|macro|ATLInt
mdefine_line|#define ATLInt&t;&t;&t;(1 &lt;&lt; 1)
DECL|macro|AllEOTInterrupt
mdefine_line|#define AllEOTInterrupt&t;&t;(1 &lt;&lt; 2)
DECL|macro|OPR_Reg
mdefine_line|#define OPR_Reg&t;&t;&t;(1 &lt;&lt; 4)
DECL|macro|HCSuspended
mdefine_line|#define HCSuspended&t;&t;(1 &lt;&lt; 5)
DECL|macro|ClkReady
mdefine_line|#define ClkReady&t;&t;(1 &lt;&lt; 6)
multiline_comment|/*&n; * HcBufferStatus&n; */
DECL|macro|ITL0BufferFull
mdefine_line|#define ITL0BufferFull&t;&t;(1 &lt;&lt; 0)
DECL|macro|ITL1BufferFull
mdefine_line|#define ITL1BufferFull&t;&t;(1 &lt;&lt; 1)
DECL|macro|ATLBufferFull
mdefine_line|#define ATLBufferFull&t;&t;(1 &lt;&lt; 2)
DECL|macro|ITL0BufferDone
mdefine_line|#define ITL0BufferDone&t;&t;(1 &lt;&lt; 3)
DECL|macro|ITL1BufferDone
mdefine_line|#define ITL1BufferDone&t;&t;(1 &lt;&lt; 4)
DECL|macro|ATLBufferDone
mdefine_line|#define ATLBufferDone&t;&t;(1 &lt;&lt; 5)
multiline_comment|/* OHCI ROOT HUB REGISTER MASKS */
multiline_comment|/* roothub.portstatus [i] bits */
DECL|macro|RH_PS_CCS
mdefine_line|#define RH_PS_CCS            0x00000001&t;/* current connect status */
DECL|macro|RH_PS_PES
mdefine_line|#define RH_PS_PES            0x00000002&t;/* port enable status */
DECL|macro|RH_PS_PSS
mdefine_line|#define RH_PS_PSS            0x00000004&t;/* port suspend status */
DECL|macro|RH_PS_POCI
mdefine_line|#define RH_PS_POCI           0x00000008&t;/* port over current indicator */
DECL|macro|RH_PS_PRS
mdefine_line|#define RH_PS_PRS            0x00000010&t;/* port reset status */
DECL|macro|RH_PS_PPS
mdefine_line|#define RH_PS_PPS            0x00000100&t;/* port power status */
DECL|macro|RH_PS_LSDA
mdefine_line|#define RH_PS_LSDA           0x00000200&t;/* low speed device attached */
DECL|macro|RH_PS_CSC
mdefine_line|#define RH_PS_CSC            0x00010000&t;/* connect status change */
DECL|macro|RH_PS_PESC
mdefine_line|#define RH_PS_PESC           0x00020000&t;/* port enable status change */
DECL|macro|RH_PS_PSSC
mdefine_line|#define RH_PS_PSSC           0x00040000&t;/* port suspend status change */
DECL|macro|RH_PS_OCIC
mdefine_line|#define RH_PS_OCIC           0x00080000&t;/* over current indicator change */
DECL|macro|RH_PS_PRSC
mdefine_line|#define RH_PS_PRSC           0x00100000&t;/* port reset status change */
multiline_comment|/* roothub.status bits */
DECL|macro|RH_HS_LPS
mdefine_line|#define RH_HS_LPS&t;&t;0x00000001&t;/* local power status */
DECL|macro|RH_HS_OCI
mdefine_line|#define RH_HS_OCI&t;&t;0x00000002&t;/* over current indicator */
DECL|macro|RH_HS_DRWE
mdefine_line|#define RH_HS_DRWE&t;&t;0x00008000&t;/* device remote wakeup enable */
DECL|macro|RH_HS_LPSC
mdefine_line|#define RH_HS_LPSC&t;&t;0x00010000&t;/* local power status change */
DECL|macro|RH_HS_OCIC
mdefine_line|#define RH_HS_OCIC&t;&t;0x00020000&t;/* over current indicator change */
DECL|macro|RH_HS_CRWE
mdefine_line|#define RH_HS_CRWE&t;&t;0x80000000&t;/* clear remote wakeup enable */
multiline_comment|/* roothub.b masks */
DECL|macro|RH_B_DR
mdefine_line|#define RH_B_DR&t;&t;&t;0x0000ffff&t;/* device removable flags */
DECL|macro|RH_B_PPCM
mdefine_line|#define RH_B_PPCM&t;&t;0xffff0000&t;/* port power control mask */
multiline_comment|/* roothub.a masks */
DECL|macro|RH_A_NDP
mdefine_line|#define&t;RH_A_NDP&t;&t;(0xff &lt;&lt; 0)&t;/* number of downstream ports */
DECL|macro|RH_A_PSM
mdefine_line|#define&t;RH_A_PSM&t;&t;(1 &lt;&lt; 8)&t;/* power switching mode */
DECL|macro|RH_A_NPS
mdefine_line|#define&t;RH_A_NPS&t;&t;(1 &lt;&lt; 9)&t;/* no power switching */
DECL|macro|RH_A_DT
mdefine_line|#define&t;RH_A_DT&t;&t;&t;(1 &lt;&lt; 10)&t;/* device type (mbz) */
DECL|macro|RH_A_OCPM
mdefine_line|#define&t;RH_A_OCPM&t;&t;(1 &lt;&lt; 11)&t;/* over current protection mode */
DECL|macro|RH_A_NOCP
mdefine_line|#define&t;RH_A_NOCP&t;&t;(1 &lt;&lt; 12)&t;/* no over current protection */
DECL|macro|RH_A_POTPGT
mdefine_line|#define&t;RH_A_POTPGT&t;&t;(0xff &lt;&lt; 24)&t;/* power on to power good time */
DECL|macro|URB_DEL
mdefine_line|#define URB_DEL 1
DECL|macro|PORT_STAT_DEFAULT
mdefine_line|#define PORT_STAT_DEFAULT&t;&t;0x0100
DECL|macro|PORT_CONNECT_STAT
mdefine_line|#define PORT_CONNECT_STAT  &t;&t;0x1
DECL|macro|PORT_ENABLE_STAT
mdefine_line|#define PORT_ENABLE_STAT&t;&t;0x2
DECL|macro|PORT_SUSPEND_STAT
mdefine_line|#define PORT_SUSPEND_STAT&t;&t;0x4
DECL|macro|PORT_OVER_CURRENT_STAT
mdefine_line|#define PORT_OVER_CURRENT_STAT&t;&t;0x8
DECL|macro|PORT_RESET_STAT
mdefine_line|#define PORT_RESET_STAT&t;&t;&t;0x10
DECL|macro|PORT_POWER_STAT
mdefine_line|#define PORT_POWER_STAT&t;&t;&t;0x100
DECL|macro|PORT_LOW_SPEED_DEV_ATTACH_STAT
mdefine_line|#define PORT_LOW_SPEED_DEV_ATTACH_STAT&t;0x200
DECL|macro|PORT_CHANGE_DEFAULT
mdefine_line|#define PORT_CHANGE_DEFAULT&t;&t;0x0
DECL|macro|PORT_CONNECT_CHANGE
mdefine_line|#define PORT_CONNECT_CHANGE&t;&t;0x1
DECL|macro|PORT_ENABLE_CHANGE
mdefine_line|#define PORT_ENABLE_CHANGE&t;&t;0x2
DECL|macro|PORT_SUSPEND_CHANGE
mdefine_line|#define PORT_SUSPEND_CHANGE&t;&t;0x4
DECL|macro|PORT_OVER_CURRENT_CHANGE
mdefine_line|#define PORT_OVER_CURRENT_CHANGE&t;0x8
DECL|macro|PORT_RESET_CHANGE
mdefine_line|#define PORT_RESET_CHANGE&t;&t;0x10
multiline_comment|/* Port Status Request info */
DECL|struct|portstat
r_typedef
r_struct
id|portstat
(brace
DECL|member|portChange
id|__u16
id|portChange
suffix:semicolon
DECL|member|portStatus
id|__u16
id|portStatus
suffix:semicolon
DECL|typedef|portstat_t
)brace
id|portstat_t
suffix:semicolon
DECL|struct|hcipriv
r_typedef
r_struct
id|hcipriv
(brace
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|disabled
r_int
id|disabled
suffix:semicolon
multiline_comment|/* e.g. got a UE, we&squot;re hung */
DECL|member|resume_count
id|atomic_t
id|resume_count
suffix:semicolon
multiline_comment|/* defending against multiple resumes */
DECL|member|regs
r_struct
id|ohci_regs
op_star
id|regs
suffix:semicolon
multiline_comment|/* OHCI controller&squot;s memory */
DECL|member|hcport
r_int
id|hcport
suffix:semicolon
multiline_comment|/* I/O base address */
DECL|member|hcport2
r_int
id|hcport2
suffix:semicolon
multiline_comment|/* I/O data reg addr */
DECL|member|RHportStatus
r_struct
id|portstat
op_star
id|RHportStatus
suffix:semicolon
multiline_comment|/* root hub port status */
DECL|member|intrstatus
r_int
id|intrstatus
suffix:semicolon
DECL|member|hc_control
id|__u32
id|hc_control
suffix:semicolon
multiline_comment|/* copy of the hc control reg */
DECL|member|frame
r_int
id|frame
suffix:semicolon
DECL|member|tl
id|__u8
op_star
id|tl
suffix:semicolon
DECL|member|xferPktLen
r_int
id|xferPktLen
suffix:semicolon
DECL|member|atl_len
r_int
id|atl_len
suffix:semicolon
DECL|member|atl_buffer_len
r_int
id|atl_buffer_len
suffix:semicolon
DECL|member|itl0_len
r_int
id|itl0_len
suffix:semicolon
DECL|member|itl1_len
r_int
id|itl1_len
suffix:semicolon
DECL|member|itl_buffer_len
r_int
id|itl_buffer_len
suffix:semicolon
DECL|member|itl_index
r_int
id|itl_index
suffix:semicolon
DECL|member|tl_last
r_int
id|tl_last
suffix:semicolon
DECL|member|units_left
r_int
id|units_left
suffix:semicolon
DECL|typedef|hcipriv_t
)brace
id|hcipriv_t
suffix:semicolon
r_struct
id|hci
suffix:semicolon
DECL|macro|cClt
mdefine_line|#define cClt        0&t;&t;
singleline_comment|// Control
DECL|macro|cISO
mdefine_line|#define cISO        1&t;&t;
singleline_comment|// ISO
DECL|macro|cBULK
mdefine_line|#define cBULK       2&t;&t;
singleline_comment|// BULK
DECL|macro|cInt
mdefine_line|#define cInt        3&t;&t;
singleline_comment|// Interrupt
DECL|macro|ISO_BIT
mdefine_line|#define ISO_BIT     0x10
multiline_comment|/*-------------------------------------------------------------------------&n; * EP0 use for configuration and Vendor Specific command interface&n; *------------------------------------------------------------------------*/
DECL|macro|cMemStart
mdefine_line|#define cMemStart       0x10
DECL|macro|EP0Buf
mdefine_line|#define EP0Buf          0x40&t;/* SL11H/SL811H memory start at 0x40 */
DECL|macro|EP0Len
mdefine_line|#define EP0Len          0x40&t;/* Length of config buffer EP0Buf */
DECL|macro|EP1Buf
mdefine_line|#define EP1Buf          0x60
DECL|macro|EP1Len
mdefine_line|#define EP1Len          0x40
multiline_comment|/*-------------------------------------------------------------------------&n; * SL11H/SL811H memory from 80h-ffh use as ping-pong buffer.&n; *------------------------------------------------------------------------*/
DECL|macro|uBufA
mdefine_line|#define uBufA           0x80&t;/* buffer A address for DATA0 */
DECL|macro|uBufB
mdefine_line|#define uBufB           0xc0&t;/* buffer B address for DATA1 */
DECL|macro|uXferLen
mdefine_line|#define uXferLen        0x40&t;/* xfer length */
DECL|macro|sMemSize
mdefine_line|#define sMemSize        0xc0&t;/* Total SL11 memory size */
DECL|macro|cMemEnd
mdefine_line|#define cMemEnd         256
multiline_comment|/*-------------------------------------------------------------------------&n; * SL811H Register Control memory map&n; * --Note: &n; *      --SL11H only has one control register set from 0x00-0x04&n; *      --SL811H has two control register set from 0x00-0x04 and 0x08-0x0c&n; *------------------------------------------------------------------------*/
DECL|macro|EP0Control
mdefine_line|#define EP0Control      0x00
DECL|macro|EP0Address
mdefine_line|#define EP0Address      0x01
DECL|macro|EP0XferLen
mdefine_line|#define EP0XferLen      0x02
DECL|macro|EP0Status
mdefine_line|#define EP0Status       0x03
DECL|macro|EP0Counter
mdefine_line|#define EP0Counter      0x04
DECL|macro|EP1Control
mdefine_line|#define EP1Control      0x08
DECL|macro|EP1Address
mdefine_line|#define EP1Address      0x09
DECL|macro|EP1XferLen
mdefine_line|#define EP1XferLen      0x0a
DECL|macro|EP1Status
mdefine_line|#define EP1Status       0x0b
DECL|macro|EP1Counter
mdefine_line|#define EP1Counter      0x0c
DECL|macro|CtrlReg
mdefine_line|#define CtrlReg         0x05
DECL|macro|IntEna
mdefine_line|#define IntEna          0x06
singleline_comment|// 0x07 is reserved
DECL|macro|IntStatus
mdefine_line|#define IntStatus       0x0d
DECL|macro|cDATASet
mdefine_line|#define cDATASet        0x0e
DECL|macro|cSOFcnt
mdefine_line|#define cSOFcnt         0x0f
DECL|macro|IntMask
mdefine_line|#define IntMask         0x57&t;/* Reset|DMA|EP0|EP2|EP1 for IntEna */
DECL|macro|HostMask
mdefine_line|#define HostMask        0x47&t;/* Host request command  for IntStatus */
DECL|macro|ReadMask
mdefine_line|#define ReadMask        0xd7&t;/* Read mask interrupt   for IntStatus */
multiline_comment|/*-------------------------------------------------------------------------&n; * Standard Chapter 9 definition&n; *-------------------------------------------------------------------------&n; */
DECL|macro|GET_STATUS
mdefine_line|#define GET_STATUS      0x00
DECL|macro|CLEAR_FEATURE
mdefine_line|#define CLEAR_FEATURE   0x01
DECL|macro|SET_FEATURE
mdefine_line|#define SET_FEATURE     0x03
DECL|macro|SET_ADDRESS
mdefine_line|#define SET_ADDRESS     0x05
DECL|macro|GET_DESCRIPTOR
mdefine_line|#define GET_DESCRIPTOR  0x06
DECL|macro|SET_DESCRIPTOR
mdefine_line|#define SET_DESCRIPTOR  0x07
DECL|macro|GET_CONFIG
mdefine_line|#define GET_CONFIG      0x08
DECL|macro|SET_CONFIG
mdefine_line|#define SET_CONFIG      0x09
DECL|macro|GET_INTERFACE
mdefine_line|#define GET_INTERFACE   0x0a
DECL|macro|SET_INTERFACE
mdefine_line|#define SET_INTERFACE   0x0b
DECL|macro|SYNCH_FRAME
mdefine_line|#define SYNCH_FRAME     0x0c
DECL|macro|DEVICE
mdefine_line|#define DEVICE          0x01
DECL|macro|CONFIGURATION
mdefine_line|#define CONFIGURATION   0x02
DECL|macro|STRING
mdefine_line|#define STRING          0x03
DECL|macro|INTERFACE
mdefine_line|#define INTERFACE       0x04
DECL|macro|ENDPOINT
mdefine_line|#define ENDPOINT        0x05
multiline_comment|/*-------------------------------------------------------------------------&n; * SL11H/SL811H definition&n; *-------------------------------------------------------------------------&n; */
DECL|macro|DATA0_WR
mdefine_line|#define DATA0_WR&t;0x07&t;
singleline_comment|// (Arm+Enable+tranmist to Host+DATA0)
DECL|macro|DATA1_WR
mdefine_line|#define DATA1_WR&t;0x47&t;
singleline_comment|// (Arm+Enable+tranmist to Host on DATA1)
DECL|macro|ZDATA0_WR
mdefine_line|#define ZDATA0_WR&t;0x05&t;
singleline_comment|// (Arm+Transaction Ignored+tranmist to Host+DATA0)
DECL|macro|ZDATA1_WR
mdefine_line|#define ZDATA1_WR&t;0x45&t;
singleline_comment|// (Arm+Transaction Ignored+tranmist to Host+DATA1)
DECL|macro|DATA0_RD
mdefine_line|#define DATA0_RD&t;0x03&t;
singleline_comment|// (Arm+Enable+received from Host+DATA0)
DECL|macro|DATA1_RD
mdefine_line|#define DATA1_RD&t;0x43&t;
singleline_comment|// (Arm+Enable+received from Host+DATA1)
DECL|macro|PID_SETUP
mdefine_line|#define PID_SETUP&t;0x2d&t;
singleline_comment|// USB Specification 1.1 Standard Definition
DECL|macro|PID_SOF
mdefine_line|#define PID_SOF&t;&t;0xA5
DECL|macro|PID_IN
mdefine_line|#define PID_IN&t;&t;0x69
DECL|macro|PID_OUT
mdefine_line|#define PID_OUT&t;&t;0xe1
DECL|macro|MAX_RETRY
mdefine_line|#define MAX_RETRY&t;0xffff
DECL|macro|TIMEOUT
mdefine_line|#define TIMEOUT&t;&t;5&t;&t;/* 2 mseconds */
DECL|macro|SL11H_HOSTCTLREG
mdefine_line|#define SL11H_HOSTCTLREG&t;0
DECL|macro|SL11H_BUFADDRREG
mdefine_line|#define SL11H_BUFADDRREG&t;1
DECL|macro|SL11H_BUFLNTHREG
mdefine_line|#define SL11H_BUFLNTHREG&t;2
DECL|macro|SL11H_PKTSTATREG
mdefine_line|#define SL11H_PKTSTATREG&t;3&t;/* read */
DECL|macro|SL11H_PIDEPREG
mdefine_line|#define SL11H_PIDEPREG&t;&t;3&t;/* write */
DECL|macro|SL11H_XFERCNTREG
mdefine_line|#define SL11H_XFERCNTREG&t;4&t;/* read */
DECL|macro|SL11H_DEVADDRREG
mdefine_line|#define SL11H_DEVADDRREG&t;4&t;/* write */
DECL|macro|SL11H_CTLREG1
mdefine_line|#define SL11H_CTLREG1&t;&t;5
DECL|macro|SL11H_INTENBLREG
mdefine_line|#define SL11H_INTENBLREG&t;6
DECL|macro|SL11H_HOSTCTLREG_B
mdefine_line|#define SL11H_HOSTCTLREG_B&t;8
DECL|macro|SL11H_BUFADDRREG_B
mdefine_line|#define SL11H_BUFADDRREG_B&t;9
DECL|macro|SL11H_BUFLNTHREG_B
mdefine_line|#define SL11H_BUFLNTHREG_B&t;0x0A
DECL|macro|SL11H_PKTSTATREG_B
mdefine_line|#define SL11H_PKTSTATREG_B&t;0x0B&t;/* read */
DECL|macro|SL11H_PIDEPREG_B
mdefine_line|#define SL11H_PIDEPREG_B&t;0x0B&t;/* write */
DECL|macro|SL11H_XFERCNTREG_B
mdefine_line|#define SL11H_XFERCNTREG_B&t;0x0C&t;/* read */
DECL|macro|SL11H_DEVADDRREG_B
mdefine_line|#define SL11H_DEVADDRREG_B&t;0x0C&t;/* write */
DECL|macro|SL11H_INTSTATREG
mdefine_line|#define SL11H_INTSTATREG&t;0x0D&t;/* write clears bitwise */
DECL|macro|SL11H_HWREVREG
mdefine_line|#define SL11H_HWREVREG&t;&t;0x0E&t;/* read */
DECL|macro|SL11H_SOFLOWREG
mdefine_line|#define SL11H_SOFLOWREG&t;&t;0x0E&t;/* write */
DECL|macro|SL11H_SOFTMRREG
mdefine_line|#define SL11H_SOFTMRREG&t;&t;0x0F&t;/* read */
DECL|macro|SL11H_CTLREG2
mdefine_line|#define SL11H_CTLREG2&t;&t;0x0F&t;/* write */
DECL|macro|SL11H_DATA_START
mdefine_line|#define SL11H_DATA_START&t;0x10
multiline_comment|/* Host control register bits (addr 0) */
DECL|macro|SL11H_HCTLMASK_ARM
mdefine_line|#define SL11H_HCTLMASK_ARM&t;1
DECL|macro|SL11H_HCTLMASK_ENBLEP
mdefine_line|#define SL11H_HCTLMASK_ENBLEP&t;2
DECL|macro|SL11H_HCTLMASK_WRITE
mdefine_line|#define SL11H_HCTLMASK_WRITE&t;4
DECL|macro|SL11H_HCTLMASK_ISOCH
mdefine_line|#define SL11H_HCTLMASK_ISOCH&t;0x10
DECL|macro|SL11H_HCTLMASK_AFTERSOF
mdefine_line|#define SL11H_HCTLMASK_AFTERSOF&t;0x20
DECL|macro|SL11H_HCTLMASK_SEQ
mdefine_line|#define SL11H_HCTLMASK_SEQ&t;0x40
DECL|macro|SL11H_HCTLMASK_PREAMBLE
mdefine_line|#define SL11H_HCTLMASK_PREAMBLE&t;0x80
multiline_comment|/* Packet status register bits (addr 3) */
DECL|macro|SL11H_STATMASK_ACK
mdefine_line|#define SL11H_STATMASK_ACK&t;1
DECL|macro|SL11H_STATMASK_ERROR
mdefine_line|#define SL11H_STATMASK_ERROR&t;2
DECL|macro|SL11H_STATMASK_TMOUT
mdefine_line|#define SL11H_STATMASK_TMOUT&t;4
DECL|macro|SL11H_STATMASK_SEQ
mdefine_line|#define SL11H_STATMASK_SEQ&t;8
DECL|macro|SL11H_STATMASK_SETUP
mdefine_line|#define SL11H_STATMASK_SETUP&t;0x10
DECL|macro|SL11H_STATMASK_OVF
mdefine_line|#define SL11H_STATMASK_OVF&t;0x20
DECL|macro|SL11H_STATMASK_NAK
mdefine_line|#define SL11H_STATMASK_NAK&t;0x40
DECL|macro|SL11H_STATMASK_STALL
mdefine_line|#define SL11H_STATMASK_STALL&t;0x80
multiline_comment|/* Control register 1 bits (addr 5) */
DECL|macro|SL11H_CTL1MASK_DSBLSOF
mdefine_line|#define SL11H_CTL1MASK_DSBLSOF&t;1
DECL|macro|SL11H_CTL1MASK_NOTXEOF2
mdefine_line|#define SL11H_CTL1MASK_NOTXEOF2&t;4
DECL|macro|SL11H_CTL1MASK_DSTATE
mdefine_line|#define SL11H_CTL1MASK_DSTATE&t;0x18
DECL|macro|SL11H_CTL1MASK_NSPD
mdefine_line|#define SL11H_CTL1MASK_NSPD&t;0x20
DECL|macro|SL11H_CTL1MASK_SUSPEND
mdefine_line|#define SL11H_CTL1MASK_SUSPEND&t;0x40
DECL|macro|SL11H_CTL1MASK_CLK12
mdefine_line|#define SL11H_CTL1MASK_CLK12&t;0x80
DECL|macro|SL11H_CTL1VAL_RESET
mdefine_line|#define SL11H_CTL1VAL_RESET&t;8
multiline_comment|/* Interrut enable (addr 6) and interrupt status register bits (addr 0xD) */
DECL|macro|SL11H_INTMASK_XFERDONE
mdefine_line|#define SL11H_INTMASK_XFERDONE&t;1
DECL|macro|SL11H_INTMASK_SOFINTR
mdefine_line|#define SL11H_INTMASK_SOFINTR&t;0x10
DECL|macro|SL11H_INTMASK_INSRMV
mdefine_line|#define SL11H_INTMASK_INSRMV&t;0x20
DECL|macro|SL11H_INTMASK_USBRESET
mdefine_line|#define SL11H_INTMASK_USBRESET&t;0x40
DECL|macro|SL11H_INTMASK_DSTATE
mdefine_line|#define SL11H_INTMASK_DSTATE&t;0x80&t;/* only in status reg */
multiline_comment|/* HW rev and SOF lo register bits (addr 0xE) */
DECL|macro|SL11H_HWRMASK_HWREV
mdefine_line|#define SL11H_HWRMASK_HWREV&t;0xF0
multiline_comment|/* SOF counter and control reg 2 (addr 0xF) */
DECL|macro|SL11H_CTL2MASK_SOFHI
mdefine_line|#define SL11H_CTL2MASK_SOFHI&t;0x3F
DECL|macro|SL11H_CTL2MASK_DSWAP
mdefine_line|#define SL11H_CTL2MASK_DSWAP&t;0x40
DECL|macro|SL11H_CTL2MASK_HOSTMODE
mdefine_line|#define SL11H_CTL2MASK_HOSTMODE&t;0xae
eof
