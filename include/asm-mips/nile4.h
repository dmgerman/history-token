multiline_comment|/*&n; *  asm-mips/nile4.h -- NEC Vrc-5074 Nile 4 definitions&n; *&n; *  Copyright (C) 2000 Geert Uytterhoeven &lt;geert@sonycom.com&gt;&n; *                     Sony Software Development Center Europe (SDCE), Brussels&n; *&n; *  This file is based on the following documentation:&n; *&n; *&t;NEC Vrc 5074 System Controller Data Sheet, June 1998&n; *&n; *  $Id: nile4.h,v 1.1 2000/01/26 00:07:45 ralf Exp $&n; */
DECL|macro|NILE4_BASE
mdefine_line|#define NILE4_BASE&t;&t;0xbfa00000
DECL|macro|NILE4_SIZE
mdefine_line|#define NILE4_SIZE&t;&t;0x00200000&t;&t;/* 2 MB */
multiline_comment|/*&n;     *  Physical Device Address Registers (PDARs)&n;     */
DECL|macro|NILE4_SDRAM0
mdefine_line|#define NILE4_SDRAM0&t;0x0000&t;/* SDRAM Bank 0 [R/W] */
DECL|macro|NILE4_SDRAM1
mdefine_line|#define NILE4_SDRAM1&t;0x0008&t;/* SDRAM Bank 1 [R/W] */
DECL|macro|NILE4_DCS2
mdefine_line|#define NILE4_DCS2&t;0x0010&t;/* Device Chip-Select 2 [R/W] */
DECL|macro|NILE4_DCS3
mdefine_line|#define NILE4_DCS3&t;0x0018&t;/* Device Chip-Select 3 [R/W] */
DECL|macro|NILE4_DCS4
mdefine_line|#define NILE4_DCS4&t;0x0020&t;/* Device Chip-Select 4 [R/W] */
DECL|macro|NILE4_DCS5
mdefine_line|#define NILE4_DCS5&t;0x0028&t;/* Device Chip-Select 5 [R/W] */
DECL|macro|NILE4_DCS6
mdefine_line|#define NILE4_DCS6&t;0x0030&t;/* Device Chip-Select 6 [R/W] */
DECL|macro|NILE4_DCS7
mdefine_line|#define NILE4_DCS7&t;0x0038&t;/* Device Chip-Select 7 [R/W] */
DECL|macro|NILE4_DCS8
mdefine_line|#define NILE4_DCS8&t;0x0040&t;/* Device Chip-Select 8 [R/W] */
DECL|macro|NILE4_PCIW0
mdefine_line|#define NILE4_PCIW0&t;0x0060&t;/* PCI Address Window 0 [R/W] */
DECL|macro|NILE4_PCIW1
mdefine_line|#define NILE4_PCIW1&t;0x0068&t;/* PCI Address Window 1 [R/W] */
DECL|macro|NILE4_INTCS
mdefine_line|#define NILE4_INTCS&t;0x0070&t;/* Controller Internal Registers and Devices */
multiline_comment|/* [R/W] */
DECL|macro|NILE4_BOOTCS
mdefine_line|#define NILE4_BOOTCS&t;0x0078&t;/* Boot ROM Chip-Select [R/W] */
multiline_comment|/*&n;     *  CPU Interface Registers&n;     */
DECL|macro|NILE4_CPUSTAT
mdefine_line|#define NILE4_CPUSTAT&t;0x0080&t;/* CPU Status [R/W] */
DECL|macro|NILE4_INTCTRL
mdefine_line|#define NILE4_INTCTRL&t;0x0088&t;/* Interrupt Control [R/W] */
DECL|macro|NILE4_INTSTAT0
mdefine_line|#define NILE4_INTSTAT0&t;0x0090&t;/* Interrupt Status 0 [R] */
DECL|macro|NILE4_INTSTAT1
mdefine_line|#define NILE4_INTSTAT1&t;0x0098&t;/* Interrupt Status 1 and CPU Interrupt */
multiline_comment|/* Enable [R/W] */
DECL|macro|NILE4_INTCLR
mdefine_line|#define NILE4_INTCLR&t;0x00A0&t;/* Interrupt Clear [R/W] */
DECL|macro|NILE4_INTPPES
mdefine_line|#define NILE4_INTPPES&t;0x00A8&t;/* PCI Interrupt Control [R/W] */
multiline_comment|/*&n;     *  Memory-Interface Registers&n;     */
DECL|macro|NILE4_MEMCTRL
mdefine_line|#define NILE4_MEMCTRL&t;0x00C0&t;/* Memory Control */
DECL|macro|NILE4_ACSTIME
mdefine_line|#define NILE4_ACSTIME&t;0x00C8&t;/* Memory Access Timing [R/W] */
DECL|macro|NILE4_CHKERR
mdefine_line|#define NILE4_CHKERR&t;0x00D0&t;/* Memory Check Error Status [R] */
multiline_comment|/*&n;     *  PCI-Bus Registers&n;     */
DECL|macro|NILE4_PCICTRL
mdefine_line|#define NILE4_PCICTRL&t;0x00E0&t;/* PCI Control [R/W] */
DECL|macro|NILE4_PCIARB
mdefine_line|#define NILE4_PCIARB&t;0x00E8&t;/* PCI Arbiter [R/W] */
DECL|macro|NILE4_PCIINIT0
mdefine_line|#define NILE4_PCIINIT0&t;0x00F0&t;/* PCI Master (Initiator) 0 [R/W] */
DECL|macro|NILE4_PCIINIT1
mdefine_line|#define NILE4_PCIINIT1&t;0x00F8&t;/* PCI Master (Initiator) 1 [R/W] */
DECL|macro|NILE4_PCIERR
mdefine_line|#define NILE4_PCIERR&t;0x00B8&t;/* PCI Error [R/W] */
multiline_comment|/*&n;     *  Local-Bus Registers&n;     */
DECL|macro|NILE4_LCNFG
mdefine_line|#define NILE4_LCNFG&t;0x0100&t;/* Local Bus Configuration [R/W] */
DECL|macro|NILE4_LCST2
mdefine_line|#define NILE4_LCST2&t;0x0110&t;/* Local Bus Chip-Select Timing 2 [R/W] */
DECL|macro|NILE4_LCST3
mdefine_line|#define NILE4_LCST3&t;0x0118&t;/* Local Bus Chip-Select Timing 3 [R/W] */
DECL|macro|NILE4_LCST4
mdefine_line|#define NILE4_LCST4&t;0x0120&t;/* Local Bus Chip-Select Timing 4 [R/W] */
DECL|macro|NILE4_LCST5
mdefine_line|#define NILE4_LCST5&t;0x0128&t;/* Local Bus Chip-Select Timing 5 [R/W] */
DECL|macro|NILE4_LCST6
mdefine_line|#define NILE4_LCST6&t;0x0130&t;/* Local Bus Chip-Select Timing 6 [R/W] */
DECL|macro|NILE4_LCST7
mdefine_line|#define NILE4_LCST7&t;0x0138&t;/* Local Bus Chip-Select Timing 7 [R/W] */
DECL|macro|NILE4_LCST8
mdefine_line|#define NILE4_LCST8&t;0x0140&t;/* Local Bus Chip-Select Timing 8 [R/W] */
DECL|macro|NILE4_DCSFN
mdefine_line|#define NILE4_DCSFN&t;0x0150&t;/* Device Chip-Select Muxing and Output */
multiline_comment|/* Enables [R/W] */
DECL|macro|NILE4_DCSIO
mdefine_line|#define NILE4_DCSIO&t;0x0158&t;/* Device Chip-Selects As I/O Bits [R/W] */
DECL|macro|NILE4_BCST
mdefine_line|#define NILE4_BCST&t;0x0178&t;/* Local Boot Chip-Select Timing [R/W] */
multiline_comment|/*&n;     *  DMA Registers&n;     */
DECL|macro|NILE4_DMACTRL0
mdefine_line|#define NILE4_DMACTRL0&t;0x0180&t;/* DMA Control 0 [R/W] */
DECL|macro|NILE4_DMASRCA0
mdefine_line|#define NILE4_DMASRCA0&t;0x0188&t;/* DMA Source Address 0 [R/W] */
DECL|macro|NILE4_DMADESA0
mdefine_line|#define NILE4_DMADESA0&t;0x0190&t;/* DMA Destination Address 0 [R/W] */
DECL|macro|NILE4_DMACTRL1
mdefine_line|#define NILE4_DMACTRL1&t;0x0198&t;/* DMA Control 1 [R/W] */
DECL|macro|NILE4_DMASRCA1
mdefine_line|#define NILE4_DMASRCA1&t;0x01A0&t;/* DMA Source Address 1 [R/W] */
DECL|macro|NILE4_DMADESA1
mdefine_line|#define NILE4_DMADESA1&t;0x01A8&t;/* DMA Destination Address 1 [R/W] */
multiline_comment|/*&n;     *  Timer Registers&n;     */
DECL|macro|NILE4_T0CTRL
mdefine_line|#define NILE4_T0CTRL&t;0x01C0&t;/* SDRAM Refresh Control [R/W] */
DECL|macro|NILE4_T0CNTR
mdefine_line|#define NILE4_T0CNTR&t;0x01C8&t;/* SDRAM Refresh Counter [R/W] */
DECL|macro|NILE4_T1CTRL
mdefine_line|#define NILE4_T1CTRL&t;0x01D0&t;/* CPU-Bus Read Time-Out Control [R/W] */
DECL|macro|NILE4_T1CNTR
mdefine_line|#define NILE4_T1CNTR&t;0x01D8&t;/* CPU-Bus Read Time-Out Counter [R/W] */
DECL|macro|NILE4_T2CTRL
mdefine_line|#define NILE4_T2CTRL&t;0x01E0&t;/* General-Purpose Timer Control [R/W] */
DECL|macro|NILE4_T2CNTR
mdefine_line|#define NILE4_T2CNTR&t;0x01E8&t;/* General-Purpose Timer Counter [R/W] */
DECL|macro|NILE4_T3CTRL
mdefine_line|#define NILE4_T3CTRL&t;0x01F0&t;/* Watchdog Timer Control [R/W] */
DECL|macro|NILE4_T3CNTR
mdefine_line|#define NILE4_T3CNTR&t;0x01F8&t;/* Watchdog Timer Counter [R/W] */
multiline_comment|/*&n;     *  PCI Configuration Space Registers&n;     */
DECL|macro|NILE4_PCI_BASE
mdefine_line|#define NILE4_PCI_BASE&t;0x0200
DECL|macro|NILE4_VID
mdefine_line|#define NILE4_VID&t;0x0200&t;/* PCI Vendor ID [R] */
DECL|macro|NILE4_DID
mdefine_line|#define NILE4_DID&t;0x0202&t;/* PCI Device ID [R] */
DECL|macro|NILE4_PCICMD
mdefine_line|#define NILE4_PCICMD&t;0x0204&t;/* PCI Command [R/W] */
DECL|macro|NILE4_PCISTS
mdefine_line|#define NILE4_PCISTS&t;0x0206&t;/* PCI Status [R/W] */
DECL|macro|NILE4_REVID
mdefine_line|#define NILE4_REVID&t;0x0208&t;/* PCI Revision ID [R] */
DECL|macro|NILE4_CLASS
mdefine_line|#define NILE4_CLASS&t;0x0209&t;/* PCI Class Code [R] */
DECL|macro|NILE4_CLSIZ
mdefine_line|#define NILE4_CLSIZ&t;0x020C&t;/* PCI Cache Line Size [R/W] */
DECL|macro|NILE4_MLTIM
mdefine_line|#define NILE4_MLTIM&t;0x020D&t;/* PCI Latency Timer [R/W] */
DECL|macro|NILE4_HTYPE
mdefine_line|#define NILE4_HTYPE&t;0x020E&t;/* PCI Header Type [R] */
DECL|macro|NILE4_BIST
mdefine_line|#define NILE4_BIST&t;0x020F&t;/* BIST [R] (unimplemented) */
DECL|macro|NILE4_BARC
mdefine_line|#define NILE4_BARC&t;0x0210&t;/* PCI Base Address Register Control [R/W] */
DECL|macro|NILE4_BAR0
mdefine_line|#define NILE4_BAR0&t;0x0218&t;/* PCI Base Address Register 0 [R/W] */
DECL|macro|NILE4_BAR1
mdefine_line|#define NILE4_BAR1&t;0x0220&t;/* PCI Base Address Register 1 [R/W] */
DECL|macro|NILE4_CIS
mdefine_line|#define NILE4_CIS&t;0x0228&t;/* PCI Cardbus CIS Pointer [R] */
multiline_comment|/* (unimplemented) */
DECL|macro|NILE4_SSVID
mdefine_line|#define NILE4_SSVID&t;0x022C&t;/* PCI Sub-System Vendor ID [R/W] */
DECL|macro|NILE4_SSID
mdefine_line|#define NILE4_SSID&t;0x022E&t;/* PCI Sub-System ID [R/W] */
DECL|macro|NILE4_ROM
mdefine_line|#define NILE4_ROM&t;0x0230&t;/* Expansion ROM Base Address [R] */
multiline_comment|/* (unimplemented) */
DECL|macro|NILE4_INTLIN
mdefine_line|#define NILE4_INTLIN&t;0x023C&t;/* PCI Interrupt Line [R/W] */
DECL|macro|NILE4_INTPIN
mdefine_line|#define NILE4_INTPIN&t;0x023D&t;/* PCI Interrupt Pin [R] */
DECL|macro|NILE4_MINGNT
mdefine_line|#define NILE4_MINGNT&t;0x023E&t;/* PCI Min_Gnt [R] (unimplemented) */
DECL|macro|NILE4_MAXLAT
mdefine_line|#define NILE4_MAXLAT&t;0x023F&t;/* PCI Max_Lat [R] (unimplemented) */
DECL|macro|NILE4_BAR2
mdefine_line|#define NILE4_BAR2&t;0x0240&t;/* PCI Base Address Register 2 [R/W] */
DECL|macro|NILE4_BAR3
mdefine_line|#define NILE4_BAR3&t;0x0248&t;/* PCI Base Address Register 3 [R/W] */
DECL|macro|NILE4_BAR4
mdefine_line|#define NILE4_BAR4&t;0x0250&t;/* PCI Base Address Register 4 [R/W] */
DECL|macro|NILE4_BAR5
mdefine_line|#define NILE4_BAR5&t;0x0258&t;/* PCI Base Address Register 5 [R/W] */
DECL|macro|NILE4_BAR6
mdefine_line|#define NILE4_BAR6&t;0x0260&t;/* PCI Base Address Register 6 [R/W] */
DECL|macro|NILE4_BAR7
mdefine_line|#define NILE4_BAR7&t;0x0268&t;/* PCI Base Address Register 7 [R/W] */
DECL|macro|NILE4_BAR8
mdefine_line|#define NILE4_BAR8&t;0x0270&t;/* PCI Base Address Register 8 [R/W] */
DECL|macro|NILE4_BARB
mdefine_line|#define NILE4_BARB&t;0x0278&t;/* PCI Base Address Register BOOT [R/W] */
multiline_comment|/*&n;     *  Serial-Port Registers&n;     */
DECL|macro|NILE4_UART_BASE
mdefine_line|#define NILE4_UART_BASE&t;0x0300
DECL|macro|NILE4_UARTRBR
mdefine_line|#define NILE4_UARTRBR&t;0x0300&t;/* UART Receiver Data Buffer [R] */
DECL|macro|NILE4_UARTTHR
mdefine_line|#define NILE4_UARTTHR&t;0x0300&t;/* UART Transmitter Data Holding [W] */
DECL|macro|NILE4_UARTIER
mdefine_line|#define NILE4_UARTIER&t;0x0308&t;/* UART Interrupt Enable [R/W] */
DECL|macro|NILE4_UARTDLL
mdefine_line|#define NILE4_UARTDLL&t;0x0300&t;/* UART Divisor Latch LSB [R/W] */
DECL|macro|NILE4_UARTDLM
mdefine_line|#define NILE4_UARTDLM&t;0x0308&t;/* UART Divisor Latch MSB [R/W] */
DECL|macro|NILE4_UARTIIR
mdefine_line|#define NILE4_UARTIIR&t;0x0310&t;/* UART Interrupt ID [R] */
DECL|macro|NILE4_UARTFCR
mdefine_line|#define NILE4_UARTFCR&t;0x0310&t;/* UART FIFO Control [W] */
DECL|macro|NILE4_UARTLCR
mdefine_line|#define NILE4_UARTLCR&t;0x0318&t;/* UART Line Control [R/W] */
DECL|macro|NILE4_UARTMCR
mdefine_line|#define NILE4_UARTMCR&t;0x0320&t;/* UART Modem Control [R/W] */
DECL|macro|NILE4_UARTLSR
mdefine_line|#define NILE4_UARTLSR&t;0x0328&t;/* UART Line Status [R/W] */
DECL|macro|NILE4_UARTMSR
mdefine_line|#define NILE4_UARTMSR&t;0x0330&t;/* UART Modem Status [R/W] */
DECL|macro|NILE4_UARTSCR
mdefine_line|#define NILE4_UARTSCR&t;0x0338&t;/* UART Scratch [R/W] */
DECL|macro|NILE4_UART_BASE_BAUD
mdefine_line|#define NILE4_UART_BASE_BAUD&t;520833&t;/* 100 MHz / 12 / 16 */
multiline_comment|/*&n;     *  Interrupt Lines&n;     */
DECL|macro|NILE4_INT_CPCE
mdefine_line|#define NILE4_INT_CPCE&t;0&t;/* CPU-Interface Parity-Error Interrupt */
DECL|macro|NILE4_INT_CNTD
mdefine_line|#define NILE4_INT_CNTD&t;1&t;/* CPU No-Target Decode Interrupt */
DECL|macro|NILE4_INT_MCE
mdefine_line|#define NILE4_INT_MCE&t;2&t;/* Memory-Check Error Interrupt */
DECL|macro|NILE4_INT_DMA
mdefine_line|#define NILE4_INT_DMA&t;3&t;/* DMA Controller Interrupt */
DECL|macro|NILE4_INT_UART
mdefine_line|#define NILE4_INT_UART&t;4&t;/* UART Interrupt */
DECL|macro|NILE4_INT_WDOG
mdefine_line|#define NILE4_INT_WDOG&t;5&t;/* Watchdog Timer Interrupt */
DECL|macro|NILE4_INT_GPT
mdefine_line|#define NILE4_INT_GPT&t;6&t;/* General-Purpose Timer Interrupt */
DECL|macro|NILE4_INT_LBRTD
mdefine_line|#define NILE4_INT_LBRTD&t;7&t;/* Local-Bus Ready Timer Interrupt */
DECL|macro|NILE4_INT_INTA
mdefine_line|#define NILE4_INT_INTA&t;8&t;/* PCI Interrupt Signal INTA# */
DECL|macro|NILE4_INT_INTB
mdefine_line|#define NILE4_INT_INTB&t;9&t;/* PCI Interrupt Signal INTB# */
DECL|macro|NILE4_INT_INTC
mdefine_line|#define NILE4_INT_INTC&t;10&t;/* PCI Interrupt Signal INTC# */
DECL|macro|NILE4_INT_INTD
mdefine_line|#define NILE4_INT_INTD&t;11&t;/* PCI Interrupt Signal INTD# */
DECL|macro|NILE4_INT_INTE
mdefine_line|#define NILE4_INT_INTE&t;12&t;/* PCI Interrupt Signal INTE# (ISA cascade) */
DECL|macro|NILE4_INT_RESV
mdefine_line|#define NILE4_INT_RESV&t;13&t;/* Reserved */
DECL|macro|NILE4_INT_PCIS
mdefine_line|#define NILE4_INT_PCIS&t;14&t;/* PCI SERR# Interrupt */
DECL|macro|NILE4_INT_PCIE
mdefine_line|#define NILE4_INT_PCIE&t;15&t;/* PCI Internal Error Interrupt */
multiline_comment|/*&n;     *  Nile 4 Register Access&n;     */
DECL|function|nile4_sync
r_static
r_inline
r_void
id|nile4_sync
c_func
(paren
r_void
)paren
(brace
r_volatile
id|u32
op_star
id|p
op_assign
(paren
r_volatile
id|u32
op_star
)paren
l_int|0xbfc00000
suffix:semicolon
(paren
r_void
)paren
(paren
op_star
id|p
)paren
suffix:semicolon
)brace
DECL|function|nile4_out32
r_static
r_inline
r_void
id|nile4_out32
c_func
(paren
id|u32
id|offset
comma
id|u32
id|val
)paren
(brace
op_star
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|NILE4_BASE
op_plus
id|offset
)paren
op_assign
id|val
suffix:semicolon
id|nile4_sync
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|nile4_in32
r_static
r_inline
id|u32
id|nile4_in32
c_func
(paren
id|u32
id|offset
)paren
(brace
id|u32
id|val
op_assign
op_star
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|NILE4_BASE
op_plus
id|offset
)paren
suffix:semicolon
id|nile4_sync
c_func
(paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|nile4_out16
r_static
r_inline
r_void
id|nile4_out16
c_func
(paren
id|u32
id|offset
comma
id|u16
id|val
)paren
(brace
op_star
(paren
r_volatile
id|u16
op_star
)paren
(paren
id|NILE4_BASE
op_plus
id|offset
)paren
op_assign
id|val
suffix:semicolon
id|nile4_sync
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|nile4_in16
r_static
r_inline
id|u16
id|nile4_in16
c_func
(paren
id|u32
id|offset
)paren
(brace
id|u16
id|val
op_assign
op_star
(paren
r_volatile
id|u16
op_star
)paren
(paren
id|NILE4_BASE
op_plus
id|offset
)paren
suffix:semicolon
id|nile4_sync
c_func
(paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|nile4_out8
r_static
r_inline
r_void
id|nile4_out8
c_func
(paren
id|u32
id|offset
comma
id|u8
id|val
)paren
(brace
op_star
(paren
r_volatile
id|u8
op_star
)paren
(paren
id|NILE4_BASE
op_plus
id|offset
)paren
op_assign
id|val
suffix:semicolon
id|nile4_sync
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|nile4_in8
r_static
r_inline
id|u8
id|nile4_in8
c_func
(paren
id|u32
id|offset
)paren
(brace
id|u8
id|val
op_assign
op_star
(paren
r_volatile
id|u8
op_star
)paren
(paren
id|NILE4_BASE
op_plus
id|offset
)paren
suffix:semicolon
id|nile4_sync
c_func
(paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Physical Device Address Registers&n;     */
r_extern
r_void
id|nile4_set_pdar
c_func
(paren
id|u32
id|pdar
comma
id|u32
id|phys
comma
id|u32
id|size
comma
r_int
id|width
comma
r_int
id|on_memory_bus
comma
r_int
id|visible
)paren
suffix:semicolon
multiline_comment|/*&n;     *  PCI Master Registers&n;     */
DECL|macro|NILE4_PCICMD_IACK
mdefine_line|#define NILE4_PCICMD_IACK&t;0&t;/* PCI Interrupt Acknowledge */
DECL|macro|NILE4_PCICMD_IO
mdefine_line|#define NILE4_PCICMD_IO&t;&t;1&t;/* PCI I/O Space */
DECL|macro|NILE4_PCICMD_MEM
mdefine_line|#define NILE4_PCICMD_MEM&t;3&t;/* PCI Memory Space */
DECL|macro|NILE4_PCICMD_CFG
mdefine_line|#define NILE4_PCICMD_CFG&t;5&t;/* PCI Configuration Space */
multiline_comment|/*&n;     *  PCI Address Spaces&n;     *&n;     *  Note that these are multiplexed using PCIINIT[01]!&n;     */
DECL|macro|NILE4_PCI_IO_BASE
mdefine_line|#define NILE4_PCI_IO_BASE&t;0xa6000000
DECL|macro|NILE4_PCI_MEM_BASE
mdefine_line|#define NILE4_PCI_MEM_BASE&t;0xa8000000
DECL|macro|NILE4_PCI_CFG_BASE
mdefine_line|#define NILE4_PCI_CFG_BASE&t;NILE4_PCI_MEM_BASE
DECL|macro|NILE4_PCI_IACK_BASE
mdefine_line|#define NILE4_PCI_IACK_BASE&t;NILE4_PCI_IO_BASE
r_extern
r_void
id|nile4_set_pmr
c_func
(paren
id|u32
id|pmr
comma
id|u32
id|type
comma
id|u32
id|addr
)paren
suffix:semicolon
multiline_comment|/*&n;     *  Interrupt Programming&n;     */
DECL|macro|NUM_I8259_INTERRUPTS
mdefine_line|#define NUM_I8259_INTERRUPTS&t;16
DECL|macro|NUM_NILE4_INTERRUPTS
mdefine_line|#define NUM_NILE4_INTERRUPTS&t;16
DECL|macro|IRQ_I8259_CASCADE
mdefine_line|#define IRQ_I8259_CASCADE&t;NILE4_INT_INTE
DECL|macro|is_i8259_irq
mdefine_line|#define is_i8259_irq(irq)&t;((irq) &lt; NUM_I8259_INTERRUPTS)
DECL|macro|nile4_to_irq
mdefine_line|#define nile4_to_irq(n)&t;&t;((n)+NUM_I8259_INTERRUPTS)
DECL|macro|irq_to_nile4
mdefine_line|#define irq_to_nile4(n)&t;&t;((n)-NUM_I8259_INTERRUPTS)
r_extern
r_void
id|nile4_map_irq
c_func
(paren
r_int
id|nile4_irq
comma
r_int
id|cpu_irq
)paren
suffix:semicolon
r_extern
r_void
id|nile4_map_irq_all
c_func
(paren
r_int
id|cpu_irq
)paren
suffix:semicolon
r_extern
r_void
id|nile4_enable_irq
c_func
(paren
r_int
id|nile4_irq
)paren
suffix:semicolon
r_extern
r_void
id|nile4_disable_irq
c_func
(paren
r_int
id|nile4_irq
)paren
suffix:semicolon
r_extern
r_void
id|nile4_disable_irq_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|u16
id|nile4_get_irq_stat
c_func
(paren
r_int
id|cpu_irq
)paren
suffix:semicolon
r_extern
r_void
id|nile4_enable_irq_output
c_func
(paren
r_int
id|cpu_irq
)paren
suffix:semicolon
r_extern
r_void
id|nile4_disable_irq_output
c_func
(paren
r_int
id|cpu_irq
)paren
suffix:semicolon
r_extern
r_void
id|nile4_set_pci_irq_polarity
c_func
(paren
r_int
id|pci_irq
comma
r_int
id|high
)paren
suffix:semicolon
r_extern
r_void
id|nile4_set_pci_irq_level_or_edge
c_func
(paren
r_int
id|pci_irq
comma
r_int
id|level
)paren
suffix:semicolon
r_extern
r_void
id|nile4_clear_irq
c_func
(paren
r_int
id|nile4_irq
)paren
suffix:semicolon
r_extern
r_void
id|nile4_clear_irq_mask
c_func
(paren
id|u32
id|mask
)paren
suffix:semicolon
r_extern
id|u8
id|nile4_i8259_iack
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|nile4_dump_irq_status
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Debug */
eof
