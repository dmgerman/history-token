multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;es4h.h:&t;Hardware definition of the ES/4h Ethernet Switch, from&t;*/
multiline_comment|/*&t;&t;both the host and the 3051&squot;s point of view.&t;&t;*/
multiline_comment|/*&t;&t;NOTE: this name is a misnomer now that there is a PCI&t;*/
multiline_comment|/*&t;&t;board.  Everything that says &quot;es4h&quot; should really be&t;*/
multiline_comment|/*&t;&t;&quot;se4&quot;.  But we&squot;ll keep the old name for now.&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;$Id: es4h.h,v 1.10 1996/08/22 17:16:53 rick Exp $&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;EISA I/O Registers.  These are located at 0x1000 * slot-number&t;*/
multiline_comment|/*&t;plus the indicated address.  I.E. 0x4000-0x4009 for slot 4.&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|ES4H_MANUFmsb
mdefine_line|#define&t;ES4H_MANUFmsb&t;0x00&t;&t;/* Read-only */
DECL|macro|ES4H_MANUFlsb
mdefine_line|#define&t;ES4H_MANUFlsb&t;0x01&t;&t;/* Read-only */
DECL|macro|ES4H_MANUF_CODE
macro_line|#&t;define ES4H_MANUF_CODE&t;&t;0x1049&t;/* = &quot;DBI&quot; */
DECL|macro|ES4H_PRODUCT
mdefine_line|#define&t;ES4H_PRODUCT&t;0x02&t;&t;/* Read-only */
DECL|macro|ES4H_PRODUCT_CODE
macro_line|#&t;define ES4H_PRODUCT_CODE&t;0x0A
DECL|macro|EPC_PRODUCT_CODE
macro_line|#&t;define EPC_PRODUCT_CODE&t;&t;0x03
DECL|macro|ES4H_REVISION
mdefine_line|#define&t;ES4H_REVISION&t;0x03&t;&t;/* Read-only */
DECL|macro|ES4H_REVISION_CODE
macro_line|#&t;define ES4H_REVISION_CODE&t;0x01
DECL|macro|ES4H_EC
mdefine_line|#define&t;ES4H_EC&t;&t;0x04&t;&t;/* EISA Control */
DECL|macro|ES4H_EC_RESET
macro_line|#&t;define ES4H_EC_RESET&t;&t;0x04&t;/* WO, EISA reset */
DECL|macro|ES4H_EC_ENABLE
macro_line|#&t;define ES4H_EC_ENABLE&t;&t;0x01&t;/* RW, EISA enable - set to */
multiline_comment|/* 1 before memory enable */
DECL|macro|ES4H_PC
mdefine_line|#define&t;ES4H_PC&t;&t;0x05&t;&t;/* Processor Control */
DECL|macro|ES4H_PC_RESET
macro_line|#&t;define ES4H_PC_RESET&t;&t;0x04&t;/* RW, 3051 reset */
DECL|macro|ES4H_PC_INT
macro_line|#&t;define ES4H_PC_INT&t;&t;0x08&t;/* WO, assert 3051 intr. 3 */
DECL|macro|ES4H_MW
mdefine_line|#define&t;ES4H_MW&t;&t;0x06&t;&t;/* Memory Window select and enable */
DECL|macro|ES4H_MW_ENABLE
macro_line|#&t;define ES4H_MW_ENABLE&t;&t;0x80&t;/* WO, enable memory */
DECL|macro|ES4H_MW_SELECT_MASK
macro_line|#&t;define ES4H_MW_SELECT_MASK&t;0x1f&t;/* WO, 32k window selected */
DECL|macro|ES4H_IS
mdefine_line|#define&t;ES4H_IS&t;&t;0x07&t;&t;/* Interrupt, addr select */
DECL|macro|ES4H_IS_INTMASK
macro_line|#&t;define ES4H_IS_INTMASK&t;&t;0x07&t;/* WO, interrupt select */
DECL|macro|ES4H_IS_INTOFF
macro_line|#&t;define ES4H_IS_INTOFF&t;&t;0x00&t;&t;/* No IRQ */
DECL|macro|ES4H_IS_INT3
macro_line|#&t;define ES4H_IS_INT3&t;&t;0x03&t;&t;/* IRQ 3 */
DECL|macro|ES4H_IS_INT5
macro_line|#&t;define ES4H_IS_INT5&t;&t;0x02&t;&t;/* IRQ 5 */
DECL|macro|ES4H_IS_INT7
macro_line|#&t;define ES4H_IS_INT7&t;&t;0x01&t;&t;/* IRQ 7 */
DECL|macro|ES4H_IS_INT10
macro_line|#&t;define ES4H_IS_INT10&t;&t;0x04&t;&t;/* IRQ 10 */
DECL|macro|ES4H_IS_INT11
macro_line|#&t;define ES4H_IS_INT11&t;&t;0x05&t;&t;/* IRQ 11 */
DECL|macro|ES4H_IS_INT12
macro_line|#&t;define ES4H_IS_INT12&t;&t;0x06&t;&t;/* IRQ 12 */
DECL|macro|ES4H_IS_INT15
macro_line|#&t;define ES4H_IS_INT15&t;&t;0x07&t;&t;/* IRQ 15 */
DECL|macro|ES4H_IS_INTACK
macro_line|#&t;define ES4H_IS_INTACK&t;&t;0x10&t;/* WO, interrupt ack */
DECL|macro|ES4H_IS_INTPEND
macro_line|#&t;define ES4H_IS_INTPEND&t;&t;0x10&t;/* RO, interrupt pending */
DECL|macro|ES4H_IS_LINEAR
macro_line|#&t;define ES4H_IS_LINEAR&t;&t;0x40&t;/* WO, no memory windowing */
DECL|macro|ES4H_IS_AS15
macro_line|#&t;define ES4H_IS_AS15&t;&t;0x80&t;/* RW, address select bit 15 */
DECL|macro|ES4H_AS_23_16
mdefine_line|#define&t;ES4H_AS_23_16&t;0x08&t;&t;/* Address select bits 23-16 */
DECL|macro|ES4H_AS_31_24
mdefine_line|#define&t;ES4H_AS_31_24&t;0x09&t;&t;/* Address select bits 31-24 */
DECL|macro|ES4H_IO_MAX
mdefine_line|#define ES4H_IO_MAX&t;&t;0x09&t;&t;/* Size of I/O space */
multiline_comment|/*&n; * PCI&n; */
DECL|macro|SE6_RESET
mdefine_line|#define SE6_RESET&t;&t;PLX_USEROUT
multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;3051 Memory Map&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Note: 3051 has 4K I-cache, 2K D-cache.  1 cycle is 50 nsec.&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
DECL|macro|SE4_NPORTS
mdefine_line|#define&t;SE4_NPORTS&t;&t;4&t;&t;/* # of ethernet ports */
DECL|macro|SE6_NPORTS
mdefine_line|#define&t;SE6_NPORTS&t;&t;6&t;&t;/* # of ethernet ports */
DECL|macro|SE_NPORTS
mdefine_line|#define&t;SE_NPORTS&t;&t;6&t;&t;/* Max # of ethernet ports */
DECL|macro|ES4H_RAM_BASE
mdefine_line|#define&t;ES4H_RAM_BASE&t;&t;0x83000000&t;/* Base address of RAM */
DECL|macro|ES4H_RAM_SIZE
mdefine_line|#define&t;ES4H_RAM_SIZE&t;&t;0x00200000&t;/* Size of RAM (2MB) */
DECL|macro|ES4H_RAM_INTBASE
mdefine_line|#define&t;ES4H_RAM_INTBASE&t;0x83800000&t;/* Base of int-on-write RAM */
multiline_comment|/* a.k.a. PKT RAM */
multiline_comment|/* Ethernet controllers */
multiline_comment|/* See: i82596.h */
DECL|macro|ES4H_ETHER0_PORT
mdefine_line|#define&t;ES4H_ETHER0_PORT&t;0xA2000000
DECL|macro|ES4H_ETHER0_CMD
mdefine_line|#define&t;ES4H_ETHER0_CMD&t;&t;0xA2000100
DECL|macro|ES4H_ETHER1_PORT
mdefine_line|#define&t;ES4H_ETHER1_PORT&t;0xA2000200
DECL|macro|ES4H_ETHER1_CMD
mdefine_line|#define&t;ES4H_ETHER1_CMD&t;&t;0xA2000300
DECL|macro|ES4H_ETHER2_PORT
mdefine_line|#define&t;ES4H_ETHER2_PORT&t;0xA2000400
DECL|macro|ES4H_ETHER2_CMD
mdefine_line|#define&t;ES4H_ETHER2_CMD&t;&t;0xA2000500
DECL|macro|ES4H_ETHER3_PORT
mdefine_line|#define&t;ES4H_ETHER3_PORT&t;0xA2000600
DECL|macro|ES4H_ETHER3_CMD
mdefine_line|#define&t;ES4H_ETHER3_CMD&t;&t;0xA2000700
DECL|macro|ES4H_ETHER4_PORT
mdefine_line|#define&t;ES4H_ETHER4_PORT&t;0xA2000800&t;/* RS SE-6 only */
DECL|macro|ES4H_ETHER4_CMD
mdefine_line|#define&t;ES4H_ETHER4_CMD&t;&t;0xA2000900&t;/* RS SE-6 only */
DECL|macro|ES4H_ETHER5_PORT
mdefine_line|#define&t;ES4H_ETHER5_PORT&t;0xA2000A00&t;/* RS SE-6 only */
DECL|macro|ES4H_ETHER5_CMD
mdefine_line|#define&t;ES4H_ETHER5_CMD&t;&t;0xA2000B00&t;/* RS SE-6 only */
DECL|macro|ES4H_I8254
mdefine_line|#define&t;ES4H_I8254&t;&t;0xA2040000&t;/* 82C54 timers */
multiline_comment|/* See: i8254.h */
DECL|macro|SE4_I8254_HZ
mdefine_line|#define&t;SE4_I8254_HZ&t;&t;(23000000/4)&t;/* EISA clock input freq. */
DECL|macro|SE4_IDT_HZ
mdefine_line|#define&t;SE4_IDT_HZ&t;&t;(46000000)&t;/* EISA CPU freq. */
DECL|macro|SE6_I8254_HZ
mdefine_line|#define&t;SE6_I8254_HZ&t;&t;(20000000/4)&t;/* PCI clock input freq. */
DECL|macro|SE6_IDT_HZ
mdefine_line|#define&t;SE6_IDT_HZ&t;&t;(50000000)&t;/* PCI CPU freq. */
DECL|macro|ES4H_I8254_HZ
mdefine_line|#define&t;ES4H_I8254_HZ&t;&t;(23000000/4)&t;/* EISA clock input freq. */
DECL|macro|ES4H_GPP
mdefine_line|#define&t;ES4H_GPP&t;&t;0xA2050000&t;/* General purpose port */
multiline_comment|/*&n;&t; * SE-4 (EISA) GPP bits&n;&t; */
DECL|macro|ES4H_GPP_C0_100
macro_line|#&t;define ES4H_GPP_C0_100&t;&t;0x0001&t;/* WO, Chan 0: 100 ohm TP */
DECL|macro|ES4H_GPP_C0_SQE
macro_line|#&t;define ES4H_GPP_C0_SQE&t;&t;0x0002&t;/* WO, Chan 0: normal squelch */
DECL|macro|ES4H_GPP_C1_100
macro_line|#&t;define ES4H_GPP_C1_100&t;&t;0x0004&t;/* WO, Chan 1: 100 ohm TP */
DECL|macro|ES4H_GPP_C1_SQE
macro_line|#&t;define ES4H_GPP_C1_SQE&t;&t;0x0008&t;/* WO, Chan 1: normal squelch */
DECL|macro|ES4H_GPP_C2_100
macro_line|#&t;define ES4H_GPP_C2_100&t;&t;0x0010&t;/* WO, Chan 2: 100 ohm TP */
DECL|macro|ES4H_GPP_C2_SQE
macro_line|#&t;define ES4H_GPP_C2_SQE&t;&t;0x0020&t;/* WO, Chan 2: normal squelch */
DECL|macro|ES4H_GPP_C3_100
macro_line|#&t;define ES4H_GPP_C3_100&t;&t;0x0040&t;/* WO, Chan 3: 100 ohm TP */
DECL|macro|ES4H_GPP_C3_SQE
macro_line|#&t;define ES4H_GPP_C3_SQE&t;&t;0x0080&t;/* WO, Chan 3: normal squelch */
DECL|macro|ES4H_GPP_SQE
macro_line|#&t;define ES4H_GPP_SQE&t;&t;0x00AA&t;/* WO, All: normal squelch */
DECL|macro|ES4H_GPP_100
macro_line|#&t;define ES4H_GPP_100&t;&t;0x0055&t;/* WO, All: 100 ohm TP */
DECL|macro|ES4H_GPP_HOSTINT
macro_line|#&t;define ES4H_GPP_HOSTINT&t;&t;0x0100&t;/* RO, cause intr. to host */
multiline_comment|/* Hold high &gt; 250 nsec */
DECL|macro|SE4_GPP_EED
macro_line|#&t;define SE4_GPP_EED&t;&t;0x0200&t;/* RW, EEPROM data bit */
DECL|macro|SE4_GPP_EECS
macro_line|#&t;define SE4_GPP_EECS&t;&t;0x0400&t;/* RW, EEPROM chip select */
DECL|macro|SE4_GPP_EECK
macro_line|#&t;define SE4_GPP_EECK&t;&t;0x0800&t;/* RW, EEPROM clock */
multiline_comment|/*&n;&t; * SE-6 (PCI) GPP bits&n;&t; */
DECL|macro|SE6_GPP_EED
macro_line|#&t;define SE6_GPP_EED&t;&t;0x0001&t;/* RW, EEPROM data bit */
DECL|macro|SE6_GPP_EECS
macro_line|#&t;define SE6_GPP_EECS&t;&t;0x0002&t;/* RW, EEPROM chip select */
DECL|macro|SE6_GPP_EECK
macro_line|#&t;define SE6_GPP_EECK&t;&t;0x0004&t;/* RW, EEPROM clock */
DECL|macro|SE6_GPP_LINK
macro_line|#&t;define SE6_GPP_LINK&t;&t;0x00fc&t;/* R, Link status LEDs */
DECL|macro|ES4H_INTVEC
mdefine_line|#define&t;ES4H_INTVEC&t;&t;0xA2060000&t;/* RO: Interrupt Vector */
DECL|macro|ES4H_IV_DMA0
macro_line|#&t;define ES4H_IV_DMA0&t;&t;0x01&t;/* Chan 0 DMA interrupt */
DECL|macro|ES4H_IV_PKT0
macro_line|#&t;define ES4H_IV_PKT0&t;&t;0x02&t;/* Chan 0 PKT interrupt */
DECL|macro|ES4H_IV_DMA1
macro_line|#&t;define ES4H_IV_DMA1&t;&t;0x04&t;/* Chan 1 DMA interrupt */
DECL|macro|ES4H_IV_PKT1
macro_line|#&t;define ES4H_IV_PKT1&t;&t;0x08&t;/* Chan 1 PKT interrupt */
DECL|macro|ES4H_IV_DMA2
macro_line|#&t;define ES4H_IV_DMA2&t;&t;0x10&t;/* Chan 2 DMA interrupt */
DECL|macro|ES4H_IV_PKT2
macro_line|#&t;define ES4H_IV_PKT2&t;&t;0x20&t;/* Chan 2 PKT interrupt */
DECL|macro|ES4H_IV_DMA3
macro_line|#&t;define ES4H_IV_DMA3&t;&t;0x40&t;/* Chan 3 DMA interrupt */
DECL|macro|ES4H_IV_PKT3
macro_line|#&t;define ES4H_IV_PKT3&t;&t;0x80&t;/* Chan 3 PKT interrupt */
DECL|macro|ES4H_INTACK
mdefine_line|#define&t;ES4H_INTACK&t;&t;0xA2060000&t;/* WO: Interrupt Ack */
DECL|macro|ES4H_INTACK_8254
macro_line|#&t;define ES4H_INTACK_8254&t;&t;0x01&t;/* Real Time Clock (int 0) */
DECL|macro|ES4H_INTACK_HOST
macro_line|#&t;define ES4H_INTACK_HOST&t;&t;0x02&t;/* Host (int 1) */
DECL|macro|ES4H_INTACK_PKT0
macro_line|#&t;define ES4H_INTACK_PKT0&t;&t;0x04&t;/* Chan 0 Pkt (int 2) */
DECL|macro|ES4H_INTACK_PKT1
macro_line|#&t;define ES4H_INTACK_PKT1&t;&t;0x08&t;/* Chan 1 Pkt (int 3) */
DECL|macro|ES4H_INTACK_PKT2
macro_line|#&t;define ES4H_INTACK_PKT2&t;&t;0x10&t;/* Chan 2 Pkt (int 4) */
DECL|macro|ES4H_INTACK_PKT3
macro_line|#&t;define ES4H_INTACK_PKT3&t;&t;0x20&t;/* Chan 3 Pkt (int 5) */
DECL|macro|SE6_PLX
mdefine_line|#define&t;SE6_PLX&t;&t;&t;0xA2070000&t;/* PLX 9060, SE-6 (PCI) only */
multiline_comment|/* see plx9060.h */
DECL|macro|SE6_PCI_VENDOR_ID
mdefine_line|#define&t;SE6_PCI_VENDOR_ID&t;0x114F&t;&t;/* Digi PCI vendor ID */
DECL|macro|SE6_PCI_DEVICE_ID
mdefine_line|#define&t;SE6_PCI_DEVICE_ID&t;0x0003&t;&t;/* RS SE-6 device ID */
DECL|macro|SE6_PCI_ID
mdefine_line|#define&t;SE6_PCI_ID&t;&t;((SE6_PCI_DEVICE_ID&lt;&lt;16) | SE6_PCI_VENDOR_ID)
multiline_comment|/*&n; *&t;IDT Interrupts&n; */
DECL|macro|ES4H_INT_8254
mdefine_line|#define&t;ES4H_INT_8254&t;&t;IDT_INT0
DECL|macro|ES4H_INT_HOST
mdefine_line|#define&t;ES4H_INT_HOST&t;&t;IDT_INT1
DECL|macro|ES4H_INT_ETHER0
mdefine_line|#define&t;ES4H_INT_ETHER0&t;&t;IDT_INT2
DECL|macro|ES4H_INT_ETHER1
mdefine_line|#define&t;ES4H_INT_ETHER1&t;&t;IDT_INT3
DECL|macro|ES4H_INT_ETHER2
mdefine_line|#define&t;ES4H_INT_ETHER2&t;&t;IDT_INT4
DECL|macro|ES4H_INT_ETHER3
mdefine_line|#define&t;ES4H_INT_ETHER3&t;&t;IDT_INT5
multiline_comment|/*&n; *&t;Because there are differences between the SE-4 and the SE-6,&n; *&t;we assume that the following globals will be set up at init&n; *&t;time in main.c to containt the appropriate constants from above&n; */
r_extern
id|ushort
id|Gpp
suffix:semicolon
multiline_comment|/* Softcopy of GPP register */
r_extern
id|ushort
id|EEck
suffix:semicolon
multiline_comment|/* Clock bit */
r_extern
id|ushort
id|EEcs
suffix:semicolon
multiline_comment|/* CS bit */
r_extern
id|ushort
id|EEd
suffix:semicolon
multiline_comment|/* Data bit */
r_extern
id|ulong
id|I8254_Hz
suffix:semicolon
multiline_comment|/* i8254 input frequency */
r_extern
id|ulong
id|IDT_Hz
suffix:semicolon
multiline_comment|/* IDT CPU frequency */
r_extern
r_int
id|Nports
suffix:semicolon
multiline_comment|/* Number of ethernet controllers */
r_extern
r_int
id|Nchan
suffix:semicolon
multiline_comment|/* Nports+1 */
eof
