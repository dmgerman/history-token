multiline_comment|/*&n; *&t;Wavelan Pcmcia driver&n; *&n; *&t;&t;Jean II - HPLB &squot;96&n; *&n; * Reorganization and extension of the driver.&n; * Original copyright follow. See wavelan_cs.h for details.&n; *&n; * This file contain the declarations of the Wavelan hardware. Note that&n; * the Pcmcia Wavelan include a i82593 controller (see definitions in&n; * file i82593.h).&n; *&n; * The main difference between the pcmcia hardware and the ISA one is&n; * the Ethernet Controller (i82593 instead of i82586). The i82593 allow&n; * only one send buffer. The PSA (Parameter Storage Area : EEprom for&n; * permanent storage of various info) is memory mapped, but not the&n; * MMI (Modem Management Interface).&n; */
multiline_comment|/*&n; * Definitions for the AT&amp;T GIS (formerly NCR) WaveLAN PCMCIA card: &n; *   An Ethernet-like radio transceiver controlled by an Intel 82593&n; *   coprocessor.&n; *&n; *&n; ****************************************************************************&n; *   Copyright 1995&n; *   Anthony D. Joseph&n; *   Massachusetts Institute of Technology&n; *&n; *   Permission to use, copy, modify, and distribute this program&n; *   for any purpose and without fee is hereby granted, provided&n; *   that this copyright and permission notice appear on all copies&n; *   and supporting documentation, the name of M.I.T. not be used&n; *   in advertising or publicity pertaining to distribution of the&n; *   program without specific prior permission, and notice be given&n; *   in supporting documentation that copying and distribution is&n; *   by permission of M.I.T.  M.I.T. makes no representations about&n; *   the suitability of this software for any purpose.  It is pro-&n; *   vided &quot;as is&quot; without express or implied warranty.         &n; ****************************************************************************&n; *&n; *&n; * Credits:&n; *     Special thanks to Jan Hoogendoorn of AT&amp;T GIS Utrecht for&n; *       providing extremely useful information about WaveLAN PCMCIA hardware&n; *&n; *     This driver is based upon several other drivers, in particular:&n; *       David Hinds&squot; Linux driver for the PCMCIA 3c589 ethernet adapter&n; *       Bruce Janson&squot;s Linux driver for the AT-bus WaveLAN adapter&n; *&t; Anders Klemets&squot; PCMCIA WaveLAN adapter driver&n; *       Robert Morris&squot; BSDI driver for the PCMCIA WaveLAN adapter&n; */
macro_line|#ifndef _WAVELAN_CS_H
DECL|macro|_WAVELAN_CS_H
mdefine_line|#define&t;_WAVELAN_CS_H
multiline_comment|/************************** MAGIC NUMBERS ***************************/
multiline_comment|/* The detection of the wavelan card is made by reading the MAC address&n; * from the card and checking it. If you have a non AT&amp;T product (OEM,&n; * like DEC RoamAbout, or Digital Ocean, Epson, ...), you must modify this&n; * part to accomodate your hardware...&n; */
DECL|variable|MAC_ADDRESSES
r_const
r_int
r_char
id|MAC_ADDRESSES
(braket
)braket
(braket
l_int|3
)braket
op_assign
(brace
(brace
l_int|0x08
comma
l_int|0x00
comma
l_int|0x0E
)brace
comma
multiline_comment|/* AT&amp;T Wavelan (standard) &amp; DEC RoamAbout */
(brace
l_int|0x08
comma
l_int|0x00
comma
l_int|0x6A
)brace
comma
multiline_comment|/* AT&amp;T Wavelan (alternate) */
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0xE1
)brace
comma
multiline_comment|/* Hitachi Wavelan */
(brace
l_int|0x00
comma
l_int|0x60
comma
l_int|0x1D
)brace
multiline_comment|/* Lucent Wavelan (another one) */
multiline_comment|/* Add your card here and send me the patch ! */
)brace
suffix:semicolon
multiline_comment|/*&n; * Constants used to convert channels to frequencies&n; */
multiline_comment|/* Frequency available in the 2.0 modem, in units of 250 kHz&n; * (as read in the offset register of the dac area).&n; * Used to map channel numbers used by `wfreqsel&squot; to frequencies&n; */
DECL|variable|channel_bands
r_const
r_int
id|channel_bands
(braket
)braket
op_assign
(brace
l_int|0x30
comma
l_int|0x58
comma
l_int|0x64
comma
l_int|0x7A
comma
l_int|0x80
comma
l_int|0xA8
comma
l_int|0xD0
comma
l_int|0xF0
comma
l_int|0xF8
comma
l_int|0x150
)brace
suffix:semicolon
multiline_comment|/* Frequencies of the 1.0 modem (fixed frequencies).&n; * Use to map the PSA `subband&squot; to a frequency&n; * Note : all frequencies apart from the first one need to be multiplied by 10&n; */
DECL|variable|fixed_bands
r_const
r_int
id|fixed_bands
(braket
)braket
op_assign
(brace
l_float|915e6
comma
l_float|2.425e8
comma
l_float|2.46e8
comma
l_float|2.484e8
comma
l_float|2.4305e8
)brace
suffix:semicolon
multiline_comment|/*************************** PC INTERFACE ****************************/
multiline_comment|/* WaveLAN host interface definitions */
DECL|macro|LCCR
mdefine_line|#define&t;LCCR(base)&t;(base)&t;&t;/* LAN Controller Command Register */
DECL|macro|LCSR
mdefine_line|#define&t;LCSR(base)&t;(base)&t;&t;/* LAN Controller Status Register */
DECL|macro|HACR
mdefine_line|#define&t;HACR(base)&t;(base+0x1)&t;/* Host Adapter Command Register */
DECL|macro|HASR
mdefine_line|#define&t;HASR(base)&t;(base+0x1)&t;/* Host Adapter Status Register */
DECL|macro|PIORL
mdefine_line|#define PIORL(base)&t;(base+0x2)&t;/* Program I/O Register Low */
DECL|macro|RPLL
mdefine_line|#define RPLL(base)&t;(base+0x2)&t;/* Receive Pointer Latched Low */
DECL|macro|PIORH
mdefine_line|#define PIORH(base)&t;(base+0x3)&t;/* Program I/O Register High */
DECL|macro|RPLH
mdefine_line|#define RPLH(base)&t;(base+0x3)&t;/* Receive Pointer Latched High */
DECL|macro|PIOP
mdefine_line|#define PIOP(base)&t;(base+0x4)&t;/* Program I/O Port */
DECL|macro|MMR
mdefine_line|#define MMR(base)&t;(base+0x6)&t;/* MMI Address Register */
DECL|macro|MMD
mdefine_line|#define MMD(base)&t;(base+0x7)&t;/* MMI Data Register */
multiline_comment|/* Host Adaptor Command Register bit definitions */
DECL|macro|HACR_LOF
mdefine_line|#define HACR_LOF&t;  (1 &lt;&lt; 3)&t;/* Lock Out Flag, toggle every 250ms */
DECL|macro|HACR_PWR_STAT
mdefine_line|#define HACR_PWR_STAT&t;  (1 &lt;&lt; 4)&t;/* Power State, 1=active, 0=sleep */
DECL|macro|HACR_TX_DMA_RESET
mdefine_line|#define HACR_TX_DMA_RESET (1 &lt;&lt; 5)&t;/* Reset transmit DMA ptr on high */
DECL|macro|HACR_RX_DMA_RESET
mdefine_line|#define HACR_RX_DMA_RESET (1 &lt;&lt; 6)&t;/* Reset receive DMA ptr on high */
DECL|macro|HACR_ROM_WEN
mdefine_line|#define HACR_ROM_WEN&t;  (1 &lt;&lt; 7)&t;/* EEPROM write enabled when true */
DECL|macro|HACR_RESET
mdefine_line|#define HACR_RESET              (HACR_TX_DMA_RESET | HACR_RX_DMA_RESET)
DECL|macro|HACR_DEFAULT
mdefine_line|#define&t;HACR_DEFAULT&t;&t;(HACR_PWR_STAT)
multiline_comment|/* Host Adapter Status Register bit definitions */
DECL|macro|HASR_MMI_BUSY
mdefine_line|#define HASR_MMI_BUSY&t;(1 &lt;&lt; 2)&t;/* MMI is busy when true */
DECL|macro|HASR_LOF
mdefine_line|#define HASR_LOF&t;(1 &lt;&lt; 3)&t;/* Lock out flag status */
DECL|macro|HASR_NO_CLK
mdefine_line|#define HASR_NO_CLK&t;(1 &lt;&lt; 4)&t;/* active when modem not connected */
multiline_comment|/* Miscellaneous bit definitions */
DECL|macro|PIORH_SEL_TX
mdefine_line|#define PIORH_SEL_TX&t;(1 &lt;&lt; 5)&t;/* PIOR points to 0=rx/1=tx buffer */
DECL|macro|MMR_MMI_WR
mdefine_line|#define MMR_MMI_WR&t;(1 &lt;&lt; 0)&t;/* Next MMI cycle is 0=read, 1=write */
DECL|macro|PIORH_MASK
mdefine_line|#define PIORH_MASK&t;0x1f&t;&t;/* only low 5 bits are significant */
DECL|macro|RPLH_MASK
mdefine_line|#define RPLH_MASK&t;0x1f&t;&t;/* only low 5 bits are significant */
DECL|macro|MMI_ADDR_MASK
mdefine_line|#define MMI_ADDR_MASK&t;0x7e&t;&t;/* Bits 1-6 of MMR are significant */
multiline_comment|/* Attribute Memory map */
DECL|macro|CIS_ADDR
mdefine_line|#define CIS_ADDR&t;0x0000&t;&t;/* Card Information Status Register */
DECL|macro|PSA_ADDR
mdefine_line|#define PSA_ADDR&t;0x0e00&t;&t;/* Parameter Storage Area address */
DECL|macro|EEPROM_ADDR
mdefine_line|#define EEPROM_ADDR&t;0x1000&t;&t;/* EEPROM address (unused ?) */
DECL|macro|COR_ADDR
mdefine_line|#define COR_ADDR&t;0x4000&t;&t;/* Configuration Option Register */
multiline_comment|/* Configuration Option Register bit definitions */
DECL|macro|COR_CONFIG
mdefine_line|#define COR_CONFIG&t;(1 &lt;&lt; 0)&t;/* Config Index, 0 when unconfigured */
DECL|macro|COR_SW_RESET
mdefine_line|#define COR_SW_RESET&t;(1 &lt;&lt; 7)&t;/* Software Reset on true */
DECL|macro|COR_LEVEL_IRQ
mdefine_line|#define COR_LEVEL_IRQ&t;(1 &lt;&lt; 6)&t;/* Level IRQ */
multiline_comment|/* Local Memory map */
DECL|macro|RX_BASE
mdefine_line|#define RX_BASE&t;&t;0x0000&t;&t;/* Receive memory, 8 kB */
DECL|macro|TX_BASE
mdefine_line|#define TX_BASE&t;&t;0x2000&t;&t;/* Transmit memory, 2 kB */
DECL|macro|UNUSED_BASE
mdefine_line|#define UNUSED_BASE&t;0x2800&t;&t;/* Unused, 22 kB */
DECL|macro|RX_SIZE
mdefine_line|#define RX_SIZE&t;&t;(TX_BASE-RX_BASE)&t;/* Size of receive area */
DECL|macro|RX_SIZE_SHIFT
mdefine_line|#define RX_SIZE_SHIFT&t;6&t;&t;/* Bits to shift in stop register */
DECL|macro|TRUE
mdefine_line|#define TRUE  1
DECL|macro|FALSE
mdefine_line|#define FALSE 0
DECL|macro|MOD_ENAL
mdefine_line|#define MOD_ENAL 1
DECL|macro|MOD_PROM
mdefine_line|#define MOD_PROM 2
multiline_comment|/* Size of a MAC address */
DECL|macro|WAVELAN_ADDR_SIZE
mdefine_line|#define WAVELAN_ADDR_SIZE&t;6
multiline_comment|/* Maximum size of Wavelan packet */
DECL|macro|WAVELAN_MTU
mdefine_line|#define WAVELAN_MTU&t;1500
DECL|macro|MAXDATAZ
mdefine_line|#define&t;MAXDATAZ&t;&t;(6 + 6 + 2 + WAVELAN_MTU)
multiline_comment|/********************** PARAMETER STORAGE AREA **********************/
multiline_comment|/*&n; * Parameter Storage Area (PSA).&n; */
DECL|typedef|psa_t
r_typedef
r_struct
id|psa_t
id|psa_t
suffix:semicolon
DECL|struct|psa_t
r_struct
id|psa_t
(brace
multiline_comment|/* For the PCMCIA Adapter, locations 0x00-0x0F are unused and fixed at 00 */
DECL|member|psa_io_base_addr_1
r_int
r_char
id|psa_io_base_addr_1
suffix:semicolon
multiline_comment|/* [0x00] Base address 1 ??? */
DECL|member|psa_io_base_addr_2
r_int
r_char
id|psa_io_base_addr_2
suffix:semicolon
multiline_comment|/* [0x01] Base address 2 */
DECL|member|psa_io_base_addr_3
r_int
r_char
id|psa_io_base_addr_3
suffix:semicolon
multiline_comment|/* [0x02] Base address 3 */
DECL|member|psa_io_base_addr_4
r_int
r_char
id|psa_io_base_addr_4
suffix:semicolon
multiline_comment|/* [0x03] Base address 4 */
DECL|member|psa_rem_boot_addr_1
r_int
r_char
id|psa_rem_boot_addr_1
suffix:semicolon
multiline_comment|/* [0x04] Remote Boot Address 1 */
DECL|member|psa_rem_boot_addr_2
r_int
r_char
id|psa_rem_boot_addr_2
suffix:semicolon
multiline_comment|/* [0x05] Remote Boot Address 2 */
DECL|member|psa_rem_boot_addr_3
r_int
r_char
id|psa_rem_boot_addr_3
suffix:semicolon
multiline_comment|/* [0x06] Remote Boot Address 3 */
DECL|member|psa_holi_params
r_int
r_char
id|psa_holi_params
suffix:semicolon
multiline_comment|/* [0x07] HOst Lan Interface (HOLI) Parameters */
DECL|member|psa_int_req_no
r_int
r_char
id|psa_int_req_no
suffix:semicolon
multiline_comment|/* [0x08] Interrupt Request Line */
DECL|member|psa_unused0
r_int
r_char
id|psa_unused0
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* [0x09-0x0F] unused */
DECL|member|psa_univ_mac_addr
r_int
r_char
id|psa_univ_mac_addr
(braket
id|WAVELAN_ADDR_SIZE
)braket
suffix:semicolon
multiline_comment|/* [0x10-0x15] Universal (factory) MAC Address */
DECL|member|psa_local_mac_addr
r_int
r_char
id|psa_local_mac_addr
(braket
id|WAVELAN_ADDR_SIZE
)braket
suffix:semicolon
multiline_comment|/* [0x16-1B] Local MAC Address */
DECL|member|psa_univ_local_sel
r_int
r_char
id|psa_univ_local_sel
suffix:semicolon
multiline_comment|/* [0x1C] Universal Local Selection */
DECL|macro|PSA_UNIVERSAL
mdefine_line|#define&t;&t;PSA_UNIVERSAL&t;0&t;&t;/* Universal (factory) */
DECL|macro|PSA_LOCAL
mdefine_line|#define&t;&t;PSA_LOCAL&t;1&t;&t;/* Local */
DECL|member|psa_comp_number
r_int
r_char
id|psa_comp_number
suffix:semicolon
multiline_comment|/* [0x1D] Compatability Number: */
DECL|macro|PSA_COMP_PC_AT_915
mdefine_line|#define&t;&t;PSA_COMP_PC_AT_915&t;0 &t;/* PC-AT 915 MHz&t;*/
DECL|macro|PSA_COMP_PC_MC_915
mdefine_line|#define&t;&t;PSA_COMP_PC_MC_915&t;1 &t;/* PC-MC 915 MHz&t;*/
DECL|macro|PSA_COMP_PC_AT_2400
mdefine_line|#define&t;&t;PSA_COMP_PC_AT_2400&t;2 &t;/* PC-AT 2.4 GHz&t;*/
DECL|macro|PSA_COMP_PC_MC_2400
mdefine_line|#define&t;&t;PSA_COMP_PC_MC_2400&t;3 &t;/* PC-MC 2.4 GHz&t;*/
DECL|macro|PSA_COMP_PCMCIA_915
mdefine_line|#define&t;&t;PSA_COMP_PCMCIA_915&t;4 &t;/* PCMCIA 915 MHz or 2.0 */
DECL|member|psa_thr_pre_set
r_int
r_char
id|psa_thr_pre_set
suffix:semicolon
multiline_comment|/* [0x1E] Modem Threshold Preset */
DECL|member|psa_feature_select
r_int
r_char
id|psa_feature_select
suffix:semicolon
multiline_comment|/* [0x1F] Call code required (1=on) */
DECL|macro|PSA_FEATURE_CALL_CODE
mdefine_line|#define&t;&t;PSA_FEATURE_CALL_CODE&t;0x01 &t;/* Call code required (Japan) */
DECL|member|psa_subband
r_int
r_char
id|psa_subband
suffix:semicolon
multiline_comment|/* [0x20] Subband&t;*/
DECL|macro|PSA_SUBBAND_915
mdefine_line|#define&t;&t;PSA_SUBBAND_915&t;&t;0&t;/* 915 MHz or 2.0 */
DECL|macro|PSA_SUBBAND_2425
mdefine_line|#define&t;&t;PSA_SUBBAND_2425&t;1&t;/* 2425 MHz&t;*/
DECL|macro|PSA_SUBBAND_2460
mdefine_line|#define&t;&t;PSA_SUBBAND_2460&t;2&t;/* 2460 MHz&t;*/
DECL|macro|PSA_SUBBAND_2484
mdefine_line|#define&t;&t;PSA_SUBBAND_2484&t;3&t;/* 2484 MHz&t;*/
DECL|macro|PSA_SUBBAND_2430_5
mdefine_line|#define&t;&t;PSA_SUBBAND_2430_5&t;4&t;/* 2430.5 MHz&t;*/
DECL|member|psa_quality_thr
r_int
r_char
id|psa_quality_thr
suffix:semicolon
multiline_comment|/* [0x21] Modem Quality Threshold */
DECL|member|psa_mod_delay
r_int
r_char
id|psa_mod_delay
suffix:semicolon
multiline_comment|/* [0x22] Modem Delay ??? (reserved) */
DECL|member|psa_nwid
r_int
r_char
id|psa_nwid
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* [0x23-0x24] Network ID */
DECL|member|psa_nwid_select
r_int
r_char
id|psa_nwid_select
suffix:semicolon
multiline_comment|/* [0x25] Network ID Select On Off */
DECL|member|psa_encryption_select
r_int
r_char
id|psa_encryption_select
suffix:semicolon
multiline_comment|/* [0x26] Encryption On Off */
DECL|member|psa_encryption_key
r_int
r_char
id|psa_encryption_key
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* [0x27-0x2E] Encryption Key */
DECL|member|psa_databus_width
r_int
r_char
id|psa_databus_width
suffix:semicolon
multiline_comment|/* [0x2F] AT bus width select 8/16 */
DECL|member|psa_call_code
r_int
r_char
id|psa_call_code
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* [0x30-0x37] (Japan) Call Code */
DECL|member|psa_nwid_prefix
r_int
r_char
id|psa_nwid_prefix
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* [0x38-0x39] Roaming domain */
DECL|member|psa_reserved
r_int
r_char
id|psa_reserved
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* [0x3A-0x3B] Reserved - fixed 00 */
DECL|member|psa_conf_status
r_int
r_char
id|psa_conf_status
suffix:semicolon
multiline_comment|/* [0x3C] Conf Status, bit 0=1:config*/
DECL|member|psa_crc
r_int
r_char
id|psa_crc
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* [0x3D] CRC-16 over PSA */
DECL|member|psa_crc_status
r_int
r_char
id|psa_crc_status
suffix:semicolon
multiline_comment|/* [0x3F] CRC Valid Flag */
)brace
suffix:semicolon
multiline_comment|/* Size for structure checking (if padding is correct) */
DECL|macro|PSA_SIZE
mdefine_line|#define&t;PSA_SIZE&t;64
multiline_comment|/* Calculate offset of a field in the above structure&n; * Warning : only even addresses are used */
DECL|macro|psaoff
mdefine_line|#define&t;psaoff(p,f) &t;((unsigned short) ((void *)(&amp;((psa_t *) ((void *) NULL + (p)))-&gt;f) - (void *) NULL))
multiline_comment|/******************** MODEM MANAGEMENT INTERFACE ********************/
multiline_comment|/*&n; * Modem Management Controller (MMC) write structure.&n; */
DECL|typedef|mmw_t
r_typedef
r_struct
id|mmw_t
id|mmw_t
suffix:semicolon
DECL|struct|mmw_t
r_struct
id|mmw_t
(brace
DECL|member|mmw_encr_key
r_int
r_char
id|mmw_encr_key
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* encryption key */
DECL|member|mmw_encr_enable
r_int
r_char
id|mmw_encr_enable
suffix:semicolon
multiline_comment|/* enable/disable encryption */
DECL|macro|MMW_ENCR_ENABLE_MODE
mdefine_line|#define&t;MMW_ENCR_ENABLE_MODE&t;0x02&t;/* Mode of security option */
DECL|macro|MMW_ENCR_ENABLE_EN
mdefine_line|#define&t;MMW_ENCR_ENABLE_EN&t;0x01&t;/* Enable security option */
DECL|member|mmw_unused0
r_int
r_char
id|mmw_unused0
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|mmw_des_io_invert
r_int
r_char
id|mmw_des_io_invert
suffix:semicolon
multiline_comment|/* Encryption option */
DECL|macro|MMW_DES_IO_INVERT_RES
mdefine_line|#define&t;MMW_DES_IO_INVERT_RES&t;0x0F&t;/* Reserved */
DECL|macro|MMW_DES_IO_INVERT_CTRL
mdefine_line|#define&t;MMW_DES_IO_INVERT_CTRL&t;0xF0&t;/* Control ??? (set to 0) */
DECL|member|mmw_unused1
r_int
r_char
id|mmw_unused1
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|mmw_loopt_sel
r_int
r_char
id|mmw_loopt_sel
suffix:semicolon
multiline_comment|/* looptest selection */
DECL|macro|MMW_LOOPT_SEL_DIS_NWID
mdefine_line|#define&t;MMW_LOOPT_SEL_DIS_NWID&t;0x40&t;/* disable NWID filtering */
DECL|macro|MMW_LOOPT_SEL_INT
mdefine_line|#define&t;MMW_LOOPT_SEL_INT&t;0x20&t;/* activate Attention Request */
DECL|macro|MMW_LOOPT_SEL_LS
mdefine_line|#define&t;MMW_LOOPT_SEL_LS&t;0x10&t;/* looptest w/o collision avoidance */
DECL|macro|MMW_LOOPT_SEL_LT3A
mdefine_line|#define MMW_LOOPT_SEL_LT3A&t;0x08&t;/* looptest 3a */
DECL|macro|MMW_LOOPT_SEL_LT3B
mdefine_line|#define&t;MMW_LOOPT_SEL_LT3B&t;0x04&t;/* looptest 3b */
DECL|macro|MMW_LOOPT_SEL_LT3C
mdefine_line|#define&t;MMW_LOOPT_SEL_LT3C&t;0x02&t;/* looptest 3c */
DECL|macro|MMW_LOOPT_SEL_LT3D
mdefine_line|#define&t;MMW_LOOPT_SEL_LT3D&t;0x01&t;/* looptest 3d */
DECL|member|mmw_jabber_enable
r_int
r_char
id|mmw_jabber_enable
suffix:semicolon
multiline_comment|/* jabber timer enable */
multiline_comment|/* Abort transmissions &gt; 200 ms */
DECL|member|mmw_freeze
r_int
r_char
id|mmw_freeze
suffix:semicolon
multiline_comment|/* freeze / unfreeeze signal level */
multiline_comment|/* 0 : signal level &amp; qual updated for every new message, 1 : frozen */
DECL|member|mmw_anten_sel
r_int
r_char
id|mmw_anten_sel
suffix:semicolon
multiline_comment|/* antenna selection */
DECL|macro|MMW_ANTEN_SEL_SEL
mdefine_line|#define MMW_ANTEN_SEL_SEL&t;0x01&t;/* direct antenna selection */
DECL|macro|MMW_ANTEN_SEL_ALG_EN
mdefine_line|#define&t;MMW_ANTEN_SEL_ALG_EN&t;0x02&t;/* antenna selection algo. enable */
DECL|member|mmw_ifs
r_int
r_char
id|mmw_ifs
suffix:semicolon
multiline_comment|/* inter frame spacing */
multiline_comment|/* min time between transmission in bit periods (.5 us) - bit 0 ignored */
DECL|member|mmw_mod_delay
r_int
r_char
id|mmw_mod_delay
suffix:semicolon
multiline_comment|/* modem delay (synchro) */
DECL|member|mmw_jam_time
r_int
r_char
id|mmw_jam_time
suffix:semicolon
multiline_comment|/* jamming time (after collision) */
DECL|member|mmw_unused2
r_int
r_char
id|mmw_unused2
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|mmw_thr_pre_set
r_int
r_char
id|mmw_thr_pre_set
suffix:semicolon
multiline_comment|/* level threshold preset */
multiline_comment|/* Discard all packet with signal &lt; this value (4) */
DECL|member|mmw_decay_prm
r_int
r_char
id|mmw_decay_prm
suffix:semicolon
multiline_comment|/* decay parameters */
DECL|member|mmw_decay_updat_prm
r_int
r_char
id|mmw_decay_updat_prm
suffix:semicolon
multiline_comment|/* decay update parameterz */
DECL|member|mmw_quality_thr
r_int
r_char
id|mmw_quality_thr
suffix:semicolon
multiline_comment|/* quality (z-quotient) threshold */
multiline_comment|/* Discard all packet with quality &lt; this value (3) */
DECL|member|mmw_netw_id_l
r_int
r_char
id|mmw_netw_id_l
suffix:semicolon
multiline_comment|/* NWID low order byte */
DECL|member|mmw_netw_id_h
r_int
r_char
id|mmw_netw_id_h
suffix:semicolon
multiline_comment|/* NWID high order byte */
multiline_comment|/* Network ID or Domain : create virtual net on the air */
multiline_comment|/* 2.0 Hardware extension - frequency selection support */
DECL|member|mmw_mode_select
r_int
r_char
id|mmw_mode_select
suffix:semicolon
multiline_comment|/* for analog tests (set to 0) */
DECL|member|mmw_unused3
r_int
r_char
id|mmw_unused3
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|mmw_fee_ctrl
r_int
r_char
id|mmw_fee_ctrl
suffix:semicolon
multiline_comment|/* frequency eeprom control */
DECL|macro|MMW_FEE_CTRL_PRE
mdefine_line|#define&t;MMW_FEE_CTRL_PRE&t;0x10&t;/* Enable protected instructions */
DECL|macro|MMW_FEE_CTRL_DWLD
mdefine_line|#define&t;MMW_FEE_CTRL_DWLD&t;0x08&t;/* Download eeprom to mmc */
DECL|macro|MMW_FEE_CTRL_CMD
mdefine_line|#define&t;MMW_FEE_CTRL_CMD&t;0x07&t;/* EEprom commands : */
DECL|macro|MMW_FEE_CTRL_READ
mdefine_line|#define&t;MMW_FEE_CTRL_READ&t;0x06&t;/* Read */
DECL|macro|MMW_FEE_CTRL_WREN
mdefine_line|#define&t;MMW_FEE_CTRL_WREN&t;0x04&t;/* Write enable */
DECL|macro|MMW_FEE_CTRL_WRITE
mdefine_line|#define&t;MMW_FEE_CTRL_WRITE&t;0x05&t;/* Write data to address */
DECL|macro|MMW_FEE_CTRL_WRALL
mdefine_line|#define&t;MMW_FEE_CTRL_WRALL&t;0x04&t;/* Write data to all addresses */
DECL|macro|MMW_FEE_CTRL_WDS
mdefine_line|#define&t;MMW_FEE_CTRL_WDS&t;0x04&t;/* Write disable */
DECL|macro|MMW_FEE_CTRL_PRREAD
mdefine_line|#define&t;MMW_FEE_CTRL_PRREAD&t;0x16&t;/* Read addr from protect register */
DECL|macro|MMW_FEE_CTRL_PREN
mdefine_line|#define&t;MMW_FEE_CTRL_PREN&t;0x14&t;/* Protect register enable */
DECL|macro|MMW_FEE_CTRL_PRCLEAR
mdefine_line|#define&t;MMW_FEE_CTRL_PRCLEAR&t;0x17&t;/* Unprotect all registers */
DECL|macro|MMW_FEE_CTRL_PRWRITE
mdefine_line|#define&t;MMW_FEE_CTRL_PRWRITE&t;0x15&t;/* Write addr in protect register */
DECL|macro|MMW_FEE_CTRL_PRDS
mdefine_line|#define&t;MMW_FEE_CTRL_PRDS&t;0x14&t;/* Protect register disable */
multiline_comment|/* Never issue this command (PRDS) : it&squot;s irreversible !!! */
DECL|member|mmw_fee_addr
r_int
r_char
id|mmw_fee_addr
suffix:semicolon
multiline_comment|/* EEprom address */
DECL|macro|MMW_FEE_ADDR_CHANNEL
mdefine_line|#define&t;MMW_FEE_ADDR_CHANNEL&t;0xF0&t;/* Select the channel */
DECL|macro|MMW_FEE_ADDR_OFFSET
mdefine_line|#define&t;MMW_FEE_ADDR_OFFSET&t;0x0F&t;/* Offset in channel data */
DECL|macro|MMW_FEE_ADDR_EN
mdefine_line|#define&t;MMW_FEE_ADDR_EN&t;&t;0xC0&t;/* FEE_CTRL enable operations */
DECL|macro|MMW_FEE_ADDR_DS
mdefine_line|#define&t;MMW_FEE_ADDR_DS&t;&t;0x00&t;/* FEE_CTRL disable operations */
DECL|macro|MMW_FEE_ADDR_ALL
mdefine_line|#define&t;MMW_FEE_ADDR_ALL&t;0x40&t;/* FEE_CTRL all operations */
DECL|macro|MMW_FEE_ADDR_CLEAR
mdefine_line|#define&t;MMW_FEE_ADDR_CLEAR&t;0xFF&t;/* FEE_CTRL clear operations */
DECL|member|mmw_fee_data_l
r_int
r_char
id|mmw_fee_data_l
suffix:semicolon
multiline_comment|/* Write data to EEprom */
DECL|member|mmw_fee_data_h
r_int
r_char
id|mmw_fee_data_h
suffix:semicolon
multiline_comment|/* high octet */
DECL|member|mmw_ext_ant
r_int
r_char
id|mmw_ext_ant
suffix:semicolon
multiline_comment|/* Setting for external antenna */
DECL|macro|MMW_EXT_ANT_EXTANT
mdefine_line|#define&t;MMW_EXT_ANT_EXTANT&t;0x01&t;/* Select external antenna */
DECL|macro|MMW_EXT_ANT_POL
mdefine_line|#define&t;MMW_EXT_ANT_POL&t;&t;0x02&t;/* Polarity of the antenna */
DECL|macro|MMW_EXT_ANT_INTERNAL
mdefine_line|#define&t;MMW_EXT_ANT_INTERNAL&t;0x00&t;/* Internal antenna */
DECL|macro|MMW_EXT_ANT_EXTERNAL
mdefine_line|#define&t;MMW_EXT_ANT_EXTERNAL&t;0x03&t;/* External antenna */
DECL|macro|MMW_EXT_ANT_IQ_TEST
mdefine_line|#define&t;MMW_EXT_ANT_IQ_TEST&t;0x1C&t;/* IQ test pattern (set to 0) */
)brace
suffix:semicolon
multiline_comment|/* Size for structure checking (if padding is correct) */
DECL|macro|MMW_SIZE
mdefine_line|#define&t;MMW_SIZE&t;37
multiline_comment|/* Calculate offset of a field in the above structure */
DECL|macro|mmwoff
mdefine_line|#define&t;mmwoff(p,f) &t;(unsigned short)((void *)(&amp;((mmw_t *)((void *)0 + (p)))-&gt;f) - (void *)0)
multiline_comment|/*&n; * Modem Management Controller (MMC) read structure.&n; */
DECL|typedef|mmr_t
r_typedef
r_struct
id|mmr_t
id|mmr_t
suffix:semicolon
DECL|struct|mmr_t
r_struct
id|mmr_t
(brace
DECL|member|mmr_unused0
r_int
r_char
id|mmr_unused0
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|mmr_des_status
r_int
r_char
id|mmr_des_status
suffix:semicolon
multiline_comment|/* encryption status */
DECL|member|mmr_des_avail
r_int
r_char
id|mmr_des_avail
suffix:semicolon
multiline_comment|/* encryption available (0x55 read) */
DECL|macro|MMR_DES_AVAIL_DES
mdefine_line|#define&t;MMR_DES_AVAIL_DES&t;0x55&t;&t;/* DES available */
DECL|macro|MMR_DES_AVAIL_AES
mdefine_line|#define&t;MMR_DES_AVAIL_AES&t;0x33&t;&t;/* AES (AT&amp;T) available */
DECL|member|mmr_des_io_invert
r_int
r_char
id|mmr_des_io_invert
suffix:semicolon
multiline_comment|/* des I/O invert register */
DECL|member|mmr_unused1
r_int
r_char
id|mmr_unused1
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|mmr_dce_status
r_int
r_char
id|mmr_dce_status
suffix:semicolon
multiline_comment|/* DCE status */
DECL|macro|MMR_DCE_STATUS_RX_BUSY
mdefine_line|#define&t;MMR_DCE_STATUS_RX_BUSY&t;&t;0x01&t;/* receiver busy */
DECL|macro|MMR_DCE_STATUS_LOOPT_IND
mdefine_line|#define&t;MMR_DCE_STATUS_LOOPT_IND&t;0x02&t;/* loop test indicated */
DECL|macro|MMR_DCE_STATUS_TX_BUSY
mdefine_line|#define&t;MMR_DCE_STATUS_TX_BUSY&t;&t;0x04&t;/* transmitter on */
DECL|macro|MMR_DCE_STATUS_JBR_EXPIRED
mdefine_line|#define&t;MMR_DCE_STATUS_JBR_EXPIRED&t;0x08&t;/* jabber timer expired */
DECL|macro|MMR_DCE_STATUS
mdefine_line|#define MMR_DCE_STATUS&t;&t;&t;0x0F&t;/* mask to get the bits */
DECL|member|mmr_dsp_id
r_int
r_char
id|mmr_dsp_id
suffix:semicolon
multiline_comment|/* DSP id (AA = Daedalus rev A) */
DECL|member|mmr_unused2
r_int
r_char
id|mmr_unused2
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|mmr_correct_nwid_l
r_int
r_char
id|mmr_correct_nwid_l
suffix:semicolon
multiline_comment|/* # of correct NWID&squot;s rxd (low) */
DECL|member|mmr_correct_nwid_h
r_int
r_char
id|mmr_correct_nwid_h
suffix:semicolon
multiline_comment|/* # of correct NWID&squot;s rxd (high) */
multiline_comment|/* Warning : Read high order octet first !!! */
DECL|member|mmr_wrong_nwid_l
r_int
r_char
id|mmr_wrong_nwid_l
suffix:semicolon
multiline_comment|/* # of wrong NWID&squot;s rxd (low) */
DECL|member|mmr_wrong_nwid_h
r_int
r_char
id|mmr_wrong_nwid_h
suffix:semicolon
multiline_comment|/* # of wrong NWID&squot;s rxd (high) */
DECL|member|mmr_thr_pre_set
r_int
r_char
id|mmr_thr_pre_set
suffix:semicolon
multiline_comment|/* level threshold preset */
DECL|macro|MMR_THR_PRE_SET
mdefine_line|#define&t;MMR_THR_PRE_SET&t;&t;0x3F&t;&t;/* level threshold preset */
DECL|macro|MMR_THR_PRE_SET_CUR
mdefine_line|#define&t;MMR_THR_PRE_SET_CUR&t;0x80&t;&t;/* Current signal above it */
DECL|member|mmr_signal_lvl
r_int
r_char
id|mmr_signal_lvl
suffix:semicolon
multiline_comment|/* signal level */
DECL|macro|MMR_SIGNAL_LVL
mdefine_line|#define&t;MMR_SIGNAL_LVL&t;&t;0x3F&t;&t;/* signal level */
DECL|macro|MMR_SIGNAL_LVL_VALID
mdefine_line|#define&t;MMR_SIGNAL_LVL_VALID&t;0x80&t;&t;/* Updated since last read */
DECL|member|mmr_silence_lvl
r_int
r_char
id|mmr_silence_lvl
suffix:semicolon
multiline_comment|/* silence level (noise) */
DECL|macro|MMR_SILENCE_LVL
mdefine_line|#define&t;MMR_SILENCE_LVL&t;&t;0x3F&t;&t;/* silence level */
DECL|macro|MMR_SILENCE_LVL_VALID
mdefine_line|#define&t;MMR_SILENCE_LVL_VALID&t;0x80&t;&t;/* Updated since last read */
DECL|member|mmr_sgnl_qual
r_int
r_char
id|mmr_sgnl_qual
suffix:semicolon
multiline_comment|/* signal quality */
DECL|macro|MMR_SGNL_QUAL
mdefine_line|#define&t;MMR_SGNL_QUAL&t;&t;0x0F&t;&t;/* signal quality */
DECL|macro|MMR_SGNL_QUAL_ANT
mdefine_line|#define&t;MMR_SGNL_QUAL_ANT&t;0x80&t;&t;/* current antenna used */
DECL|member|mmr_netw_id_l
r_int
r_char
id|mmr_netw_id_l
suffix:semicolon
multiline_comment|/* NWID low order byte ??? */
DECL|member|mmr_unused3
r_int
r_char
id|mmr_unused3
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* unused */
multiline_comment|/* 2.0 Hardware extension - frequency selection support */
DECL|member|mmr_fee_status
r_int
r_char
id|mmr_fee_status
suffix:semicolon
multiline_comment|/* Status of frequency eeprom */
DECL|macro|MMR_FEE_STATUS_ID
mdefine_line|#define&t;MMR_FEE_STATUS_ID&t;0xF0&t;&t;/* Modem revision id */
DECL|macro|MMR_FEE_STATUS_DWLD
mdefine_line|#define&t;MMR_FEE_STATUS_DWLD&t;0x08&t;&t;/* Download in progress */
DECL|macro|MMR_FEE_STATUS_BUSY
mdefine_line|#define&t;MMR_FEE_STATUS_BUSY&t;0x04&t;&t;/* EEprom busy */
DECL|member|mmr_unused4
r_int
r_char
id|mmr_unused4
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|mmr_fee_data_l
r_int
r_char
id|mmr_fee_data_l
suffix:semicolon
multiline_comment|/* Read data from eeprom (low) */
DECL|member|mmr_fee_data_h
r_int
r_char
id|mmr_fee_data_h
suffix:semicolon
multiline_comment|/* Read data from eeprom (high) */
)brace
suffix:semicolon
multiline_comment|/* Size for structure checking (if padding is correct) */
DECL|macro|MMR_SIZE
mdefine_line|#define&t;MMR_SIZE&t;36
multiline_comment|/* Calculate offset of a field in the above structure */
DECL|macro|mmroff
mdefine_line|#define&t;mmroff(p,f) &t;(unsigned short)((void *)(&amp;((mmr_t *)((void *)0 + (p)))-&gt;f) - (void *)0)
multiline_comment|/* Make the two above structures one */
DECL|union|mm_t
r_typedef
r_union
id|mm_t
(brace
DECL|member|w
r_struct
id|mmw_t
id|w
suffix:semicolon
multiline_comment|/* Write to the mmc */
DECL|member|r
r_struct
id|mmr_t
id|r
suffix:semicolon
multiline_comment|/* Read from the mmc */
DECL|typedef|mm_t
)brace
id|mm_t
suffix:semicolon
macro_line|#endif /* _WAVELAN_CS_H */
eof
