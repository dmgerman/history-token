multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Title&t;&t;:&t;SX/SI/XIO Board Hardware Definitions&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Author&t;&t;:&t;N.P.Vassallo&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Creation&t;:&t;16th March 1998&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Version&t;&t;:&t;3.0.0&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Copyright&t;:&t;(c) Specialix International Ltd. 1998&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Description&t;:&t;Prototypes, structures and definitions&t;*/
multiline_comment|/*&t;&t;&t;&t;describing the SX/SI/XIO board hardware&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
multiline_comment|/* History...&n;&n;3.0.0&t;16/03/98 NPV&t;Creation.&n;&n;*/
macro_line|#ifndef&t;_sxboards_h&t;&t;&t;&t;/* If SXBOARDS.H not already defined */
DECL|macro|_sxboards_h
mdefine_line|#define&t;_sxboards_h    1
multiline_comment|/*****************************************************************************&n;*******************************                 ******************************&n;*******************************   Board Types   ******************************&n;*******************************                 ******************************&n;*****************************************************************************/
multiline_comment|/* BUS types... */
DECL|macro|BUS_ISA
mdefine_line|#define&t;&t;BUS_ISA&t;&t;0
DECL|macro|BUS_MCA
mdefine_line|#define&t;&t;BUS_MCA&t;&t;1
DECL|macro|BUS_EISA
mdefine_line|#define&t;&t;BUS_EISA&t;2
DECL|macro|BUS_PCI
mdefine_line|#define&t;&t;BUS_PCI&t;&t;3
multiline_comment|/* Board phases... */
DECL|macro|SI1_Z280
mdefine_line|#define&t;&t;SI1_Z280&t;1
DECL|macro|SI2_Z280
mdefine_line|#define&t;&t;SI2_Z280&t;2
DECL|macro|SI3_T225
mdefine_line|#define&t;&t;SI3_T225&t;3
multiline_comment|/* Board types... */
DECL|macro|CARD_TYPE
mdefine_line|#define&t;&t;CARD_TYPE(bus,phase)&t;(bus&lt;&lt;4|phase)
DECL|macro|CARD_BUS
mdefine_line|#define&t;&t;CARD_BUS(type)&t;&t;((type&gt;&gt;4)&amp;0xF)
DECL|macro|CARD_PHASE
mdefine_line|#define&t;&t;CARD_PHASE(type)&t;(type&amp;0xF)
DECL|macro|TYPE_SI2_ISA
mdefine_line|#define&t;&t;TYPE_SI2_ISA&t;&t;CARD_TYPE(BUS_ISA,SI2_Z280)
DECL|macro|TYPE_SI2_EISA
mdefine_line|#define&t;&t;TYPE_SI2_EISA&t;&t;CARD_TYPE(BUS_EISA,SI2_Z280)
DECL|macro|TYPE_SI2_PCI
mdefine_line|#define&t;&t;TYPE_SI2_PCI&t;&t;CARD_TYPE(BUS_PCI,SI2_Z280)
DECL|macro|TYPE_SX_ISA
mdefine_line|#define&t;&t;TYPE_SX_ISA&t;&t;CARD_TYPE(BUS_ISA,SI3_T225)
DECL|macro|TYPE_SX_PCI
mdefine_line|#define&t;&t;TYPE_SX_PCI&t;&t;CARD_TYPE(BUS_PCI,SI3_T225)
multiline_comment|/*****************************************************************************&n;******************************                  ******************************&n;******************************   Phase 2 Z280   ******************************&n;******************************                  ******************************&n;*****************************************************************************/
multiline_comment|/* ISA board details... */
DECL|macro|SI2_ISA_WINDOW_LEN
mdefine_line|#define&t;&t;SI2_ISA_WINDOW_LEN&t;0x8000&t;&t;/* 32 Kbyte shared memory window */
DECL|macro|SI2_ISA_MEMORY_LEN
mdefine_line|#define &t;SI2_ISA_MEMORY_LEN&t;0x7FF8&t;&t;/* Usable memory */
DECL|macro|SI2_ISA_ADDR_LOW
mdefine_line|#define&t;&t;SI2_ISA_ADDR_LOW&t;0x0A0000&t;/* Lowest address = 640 Kbyte */
DECL|macro|SI2_ISA_ADDR_HIGH
mdefine_line|#define&t;&t;SI2_ISA_ADDR_HIGH&t;0xFF8000&t;/* Highest address = 16Mbyte - 32Kbyte */
DECL|macro|SI2_ISA_ADDR_STEP
mdefine_line|#define&t;&t;SI2_ISA_ADDR_STEP&t;SI2_ISA_WINDOW_LEN/* ISA board address step */
DECL|macro|SI2_ISA_IRQ_MASK
mdefine_line|#define&t;&t;SI2_ISA_IRQ_MASK&t;0x9800&t;&t;/* IRQs 15,12,11 */
multiline_comment|/* ISA board, register definitions... */
DECL|macro|SI2_ISA_ID_BASE
mdefine_line|#define&t;&t;SI2_ISA_ID_BASE&t;&t;0x7FF8&t;&t;&t;/* READ:  Board ID string */
DECL|macro|SI2_ISA_RESET
mdefine_line|#define&t;&t;SI2_ISA_RESET&t;&t;SI2_ISA_ID_BASE&t;&t;/* WRITE: Host Reset */
DECL|macro|SI2_ISA_IRQ11
mdefine_line|#define&t;&t;SI2_ISA_IRQ11&t;&t;(SI2_ISA_ID_BASE+1)&t;/* WRITE: Set IRQ11 */
DECL|macro|SI2_ISA_IRQ12
mdefine_line|#define&t;&t;SI2_ISA_IRQ12&t;&t;(SI2_ISA_ID_BASE+2)&t;/* WRITE: Set IRQ12 */
DECL|macro|SI2_ISA_IRQ15
mdefine_line|#define&t;&t;SI2_ISA_IRQ15&t;&t;(SI2_ISA_ID_BASE+3)&t;/* WRITE: Set IRQ15 */
DECL|macro|SI2_ISA_IRQSET
mdefine_line|#define&t;&t;SI2_ISA_IRQSET&t;&t;(SI2_ISA_ID_BASE+4)&t;/* WRITE: Set Host Interrupt */
DECL|macro|SI2_ISA_INTCLEAR
mdefine_line|#define&t;&t;SI2_ISA_INTCLEAR&t;(SI2_ISA_ID_BASE+5)&t;/* WRITE: Enable Host Interrupt */
DECL|macro|SI2_ISA_IRQ11_SET
mdefine_line|#define&t;&t;SI2_ISA_IRQ11_SET&t;0x10
DECL|macro|SI2_ISA_IRQ11_CLEAR
mdefine_line|#define&t;&t;SI2_ISA_IRQ11_CLEAR&t;0x00
DECL|macro|SI2_ISA_IRQ12_SET
mdefine_line|#define&t;&t;SI2_ISA_IRQ12_SET&t;0x10
DECL|macro|SI2_ISA_IRQ12_CLEAR
mdefine_line|#define&t;&t;SI2_ISA_IRQ12_CLEAR&t;0x00
DECL|macro|SI2_ISA_IRQ15_SET
mdefine_line|#define&t;&t;SI2_ISA_IRQ15_SET&t;0x10
DECL|macro|SI2_ISA_IRQ15_CLEAR
mdefine_line|#define&t;&t;SI2_ISA_IRQ15_CLEAR&t;0x00
DECL|macro|SI2_ISA_INTCLEAR_SET
mdefine_line|#define&t;&t;SI2_ISA_INTCLEAR_SET&t;0x10
DECL|macro|SI2_ISA_INTCLEAR_CLEAR
mdefine_line|#define&t;&t;SI2_ISA_INTCLEAR_CLEAR&t;0x00
DECL|macro|SI2_ISA_IRQSET_CLEAR
mdefine_line|#define&t;&t;SI2_ISA_IRQSET_CLEAR&t;0x10
DECL|macro|SI2_ISA_IRQSET_SET
mdefine_line|#define&t;&t;SI2_ISA_IRQSET_SET&t;0x00
DECL|macro|SI2_ISA_RESET_SET
mdefine_line|#define&t;&t;SI2_ISA_RESET_SET&t;0x00
DECL|macro|SI2_ISA_RESET_CLEAR
mdefine_line|#define&t;&t;SI2_ISA_RESET_CLEAR&t;0x10
multiline_comment|/* PCI board details... */
DECL|macro|SI2_PCI_WINDOW_LEN
mdefine_line|#define&t;&t;SI2_PCI_WINDOW_LEN&t;0x100000&t;/* 1 Mbyte memory window */
multiline_comment|/* PCI board register definitions... */
DECL|macro|SI2_PCI_SET_IRQ
mdefine_line|#define&t;&t;SI2_PCI_SET_IRQ&t;&t;0x40001&t;&t;/* Set Host Interrupt  */
DECL|macro|SI2_PCI_RESET
mdefine_line|#define&t;&t;SI2_PCI_RESET&t;&t;0xC0001&t;&t;/* Host Reset */
multiline_comment|/*****************************************************************************&n;******************************                  ******************************&n;******************************   Phase 3 T225   ******************************&n;******************************                  ******************************&n;*****************************************************************************/
multiline_comment|/* General board details... */
DECL|macro|SX_WINDOW_LEN
mdefine_line|#define&t;&t;SX_WINDOW_LEN&t;&t;64*1024&t;&t;/* 64 Kbyte memory window */
multiline_comment|/* ISA board details... */
DECL|macro|SX_ISA_ADDR_LOW
mdefine_line|#define&t;&t;SX_ISA_ADDR_LOW&t;&t;0x0A0000&t;/* Lowest address = 640 Kbyte */
DECL|macro|SX_ISA_ADDR_HIGH
mdefine_line|#define&t;&t;SX_ISA_ADDR_HIGH&t;0xFF8000&t;/* Highest address = 16Mbyte - 32Kbyte */
DECL|macro|SX_ISA_ADDR_STEP
mdefine_line|#define&t;&t;SX_ISA_ADDR_STEP&t;SX_WINDOW_LEN&t;/* ISA board address step */
DECL|macro|SX_ISA_IRQ_MASK
mdefine_line|#define&t;&t;SX_ISA_IRQ_MASK&t;&t;0x9E00&t;&t;/* IRQs 15,12,11,10,9 */
multiline_comment|/* Hardware register definitions... */
DECL|macro|SX_EVENT_STATUS
mdefine_line|#define&t;&t;SX_EVENT_STATUS&t;&t;0x7800&t;&t;/* READ:  T225 Event Status */
DECL|macro|SX_EVENT_STROBE
mdefine_line|#define&t;&t;SX_EVENT_STROBE&t;&t;0x7800&t;&t;/* WRITE: T225 Event Strobe */
DECL|macro|SX_EVENT_ENABLE
mdefine_line|#define&t;&t;SX_EVENT_ENABLE&t;&t;0x7880&t;&t;/* WRITE: T225 Event Enable */
DECL|macro|SX_VPD_ROM
mdefine_line|#define&t;&t;SX_VPD_ROM&t;&t;0x7C00&t;&t;/* READ:  Vital Product Data ROM */
DECL|macro|SX_CONFIG
mdefine_line|#define&t;&t;SX_CONFIG&t;&t;0x7C00&t;&t;/* WRITE: Host Configuration Register */
DECL|macro|SX_IRQ_STATUS
mdefine_line|#define&t;&t;SX_IRQ_STATUS&t;&t;0x7C80&t;&t;/* READ:  Host Interrupt Status */
DECL|macro|SX_SET_IRQ
mdefine_line|#define&t;&t;SX_SET_IRQ&t;&t;0x7C80&t;&t;/* WRITE: Set Host Interrupt */
DECL|macro|SX_RESET_STATUS
mdefine_line|#define&t;&t;SX_RESET_STATUS&t;&t;0x7D00&t;&t;/* READ:  Host Reset Status */
DECL|macro|SX_RESET
mdefine_line|#define&t;&t;SX_RESET&t;&t;0x7D00&t;&t;/* WRITE: Host Reset */
DECL|macro|SX_RESET_IRQ
mdefine_line|#define&t;&t;SX_RESET_IRQ&t;&t;0x7D80&t;&t;/* WRITE: Reset Host Interrupt */
multiline_comment|/* SX_VPD_ROM definitions... */
DECL|macro|SX_VPD_SLX_ID1
mdefine_line|#define&t;&t;SX_VPD_SLX_ID1&t;&t;0x00
DECL|macro|SX_VPD_SLX_ID2
mdefine_line|#define&t;&t;SX_VPD_SLX_ID2&t;&t;0x01
DECL|macro|SX_VPD_HW_REV
mdefine_line|#define&t;&t;SX_VPD_HW_REV&t;&t;0x02
DECL|macro|SX_VPD_HW_ASSEM
mdefine_line|#define&t;&t;SX_VPD_HW_ASSEM&t;&t;0x03
DECL|macro|SX_VPD_UNIQUEID4
mdefine_line|#define&t;&t;SX_VPD_UNIQUEID4&t;0x04
DECL|macro|SX_VPD_UNIQUEID3
mdefine_line|#define&t;&t;SX_VPD_UNIQUEID3&t;0x05
DECL|macro|SX_VPD_UNIQUEID2
mdefine_line|#define&t;&t;SX_VPD_UNIQUEID2&t;0x06
DECL|macro|SX_VPD_UNIQUEID1
mdefine_line|#define&t;&t;SX_VPD_UNIQUEID1&t;0x07
DECL|macro|SX_VPD_MANU_YEAR
mdefine_line|#define&t;&t;SX_VPD_MANU_YEAR&t;0x08
DECL|macro|SX_VPD_MANU_WEEK
mdefine_line|#define&t;&t;SX_VPD_MANU_WEEK&t;0x09
DECL|macro|SX_VPD_IDENT
mdefine_line|#define&t;&t;SX_VPD_IDENT&t;&t;0x10
DECL|macro|SX_VPD_IDENT_STRING
mdefine_line|#define&t;&t;SX_VPD_IDENT_STRING&t;&quot;JET HOST BY KEV#&quot;
multiline_comment|/* SX unique identifiers... */
DECL|macro|SX_UNIQUEID_MASK
mdefine_line|#define&t;&t;SX_UNIQUEID_MASK&t;0xF0
DECL|macro|SX_ISA_UNIQUEID1
mdefine_line|#define&t;&t;SX_ISA_UNIQUEID1&t;0x20
DECL|macro|SX_PCI_UNIQUEID1
mdefine_line|#define&t;&t;SX_PCI_UNIQUEID1&t;0x50
multiline_comment|/* SX_CONFIG definitions... */
DECL|macro|SX_CONF_BUSEN
mdefine_line|#define&t;&t;SX_CONF_BUSEN&t;&t;0x02&t;&t;/* Enable T225 memory and I/O */
DECL|macro|SX_CONF_HOSTIRQ
mdefine_line|#define&t;&t;SX_CONF_HOSTIRQ&t;&t;0x04&t;&t;/* Enable board to host interrupt */
multiline_comment|/* SX bootstrap... */
DECL|macro|SX_BOOTSTRAP
mdefine_line|#define&t;&t;SX_BOOTSTRAP&t;&t;&quot;&bslash;x28&bslash;x20&bslash;x21&bslash;x02&bslash;x60&bslash;x0a&quot;
DECL|macro|SX_BOOTSTRAP_SIZE
mdefine_line|#define&t;&t;SX_BOOTSTRAP_SIZE&t;6
DECL|macro|SX_BOOTSTRAP_ADDR
mdefine_line|#define&t;&t;SX_BOOTSTRAP_ADDR&t;(0x8000-SX_BOOTSTRAP_SIZE)
multiline_comment|/*****************************************************************************&n;**********************************          **********************************&n;**********************************   EISA   **********************************&n;**********************************          **********************************&n;*****************************************************************************/
DECL|macro|SI2_EISA_OFF
mdefine_line|#define&t;&t;SI2_EISA_OFF&t; &t;0x42
DECL|macro|SI2_EISA_VAL
mdefine_line|#define&t;&t;SI2_EISA_VAL&t; &t;0x01
DECL|macro|SI2_EISA_WINDOW_LEN
mdefine_line|#define&t;&t;SI2_EISA_WINDOW_LEN     0x10000
multiline_comment|/*****************************************************************************&n;***********************************         **********************************&n;***********************************   PCI   **********************************&n;***********************************         **********************************&n;*****************************************************************************/
multiline_comment|/* General definitions... */
DECL|macro|SPX_VENDOR_ID
mdefine_line|#define&t;&t;SPX_VENDOR_ID&t;&t;0x11CB&t;&t;/* Assigned by the PCI SIG */
DECL|macro|SPX_DEVICE_ID
mdefine_line|#define&t;&t;SPX_DEVICE_ID&t;&t;0x4000&t;&t;/* SI/XIO boards */
DECL|macro|SPX_PLXDEVICE_ID
mdefine_line|#define&t;&t;SPX_PLXDEVICE_ID&t;0x2000&t;&t;/* SX boards */
DECL|macro|SPX_SUB_VENDOR_ID
mdefine_line|#define&t;&t;SPX_SUB_VENDOR_ID&t;SPX_VENDOR_ID&t;/* Same as vendor id */
DECL|macro|SI2_SUB_SYS_ID
mdefine_line|#define&t;&t;SI2_SUB_SYS_ID&t;&t;0x400&t;&t;/* Phase 2 (Z280) board */
DECL|macro|SX_SUB_SYS_ID
mdefine_line|#define&t;&t;SX_SUB_SYS_ID&t;&t;0x200&t;&t;/* Phase 3 (t225) board */
macro_line|#endif&t;&t;&t;&t;&t;&t;/*_sxboards_h */
multiline_comment|/* End of SXBOARDS.H */
eof
