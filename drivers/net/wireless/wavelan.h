multiline_comment|/*&n; *&t;WaveLAN ISA driver&n; *&n; *&t;&t;Jean II - HPLB &squot;96&n; *&n; * Reorganisation and extension of the driver.&n; * Original copyright follows. See wavelan.p.h for details.&n; *&n; * This file contains the declarations for the WaveLAN hardware. Note that&n; * the WaveLAN ISA includes a i82586 controller (see definitions in&n; * file i82586.h).&n; *&n; * The main difference between the ISA hardware and the PCMCIA one is&n; * the Ethernet controller (i82586 instead of i82593).&n; * The i82586 allows multiple transmit buffers.  The PSA needs to be accessed&n; * through the host interface.&n; */
macro_line|#ifndef _WAVELAN_H
DECL|macro|_WAVELAN_H
mdefine_line|#define&t;_WAVELAN_H
multiline_comment|/************************** MAGIC NUMBERS ***************************/
multiline_comment|/* Detection of the WaveLAN card is done by reading the MAC&n; * address from the card and checking it.  If you have a non-AT&amp;T&n; * product (OEM, like DEC RoamAbout, Digital Ocean, or Epson),&n; * you might need to modify this part to accommodate your hardware.&n; */
DECL|variable|MAC_ADDRESSES
r_static
r_const
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
multiline_comment|/* AT&amp;T WaveLAN (standard) &amp; DEC RoamAbout */
(brace
l_int|0x08
comma
l_int|0x00
comma
l_int|0x6A
)brace
comma
multiline_comment|/* AT&amp;T WaveLAN (alternate) */
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
multiline_comment|/* Add your card here and send me the patch! */
)brace
suffix:semicolon
DECL|macro|WAVELAN_ADDR_SIZE
mdefine_line|#define WAVELAN_ADDR_SIZE&t;6&t;/* Size of a MAC address */
DECL|macro|WAVELAN_MTU
mdefine_line|#define WAVELAN_MTU&t;&t;1500&t;/* Maximum size of WaveLAN packet */
DECL|macro|MAXDATAZ
mdefine_line|#define&t;MAXDATAZ&t;&t;(WAVELAN_ADDR_SIZE + WAVELAN_ADDR_SIZE + 2 + WAVELAN_MTU)
multiline_comment|/*&n; * Constants used to convert channels to frequencies&n; */
multiline_comment|/* Frequency available in the 2.0 modem, in units of 250 kHz&n; * (as read in the offset register of the dac area).&n; * Used to map channel numbers used by `wfreqsel&squot; to frequencies&n; */
DECL|variable|channel_bands
r_static
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
r_static
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
multiline_comment|/*&n; * Host Adaptor structure.&n; * (base is board port address).&n; */
DECL|typedef|hacs_u
r_typedef
r_union
id|hacs_u
id|hacs_u
suffix:semicolon
DECL|union|hacs_u
r_union
id|hacs_u
(brace
DECL|member|hu_command
r_int
r_int
id|hu_command
suffix:semicolon
multiline_comment|/* Command register */
DECL|macro|HACR_RESET
mdefine_line|#define&t;&t;HACR_RESET&t;&t;0x0001&t;/* Reset board */
DECL|macro|HACR_CA
mdefine_line|#define&t;&t;HACR_CA&t;&t;&t;0x0002&t;/* Set Channel Attention for 82586 */
DECL|macro|HACR_16BITS
mdefine_line|#define&t;&t;HACR_16BITS&t;&t;0x0004&t;/* 16-bit operation (0 =&gt; 8bits) */
DECL|macro|HACR_OUT0
mdefine_line|#define&t;&t;HACR_OUT0&t;&t;0x0008&t;/* General purpose output pin 0 */
multiline_comment|/* not used - must be 1 */
DECL|macro|HACR_OUT1
mdefine_line|#define&t;&t;HACR_OUT1&t;&t;0x0010&t;/* General purpose output pin 1 */
multiline_comment|/* not used - must be 1 */
DECL|macro|HACR_82586_INT_ENABLE
mdefine_line|#define&t;&t;HACR_82586_INT_ENABLE&t;0x0020&t;/* Enable 82586 interrupts */
DECL|macro|HACR_MMC_INT_ENABLE
mdefine_line|#define&t;&t;HACR_MMC_INT_ENABLE&t;0x0040&t;/* Enable MMC interrupts */
DECL|macro|HACR_INTR_CLR_ENABLE
mdefine_line|#define&t;&t;HACR_INTR_CLR_ENABLE&t;0x0080&t;/* Enable interrupt status read/clear */
DECL|member|hu_status
r_int
r_int
id|hu_status
suffix:semicolon
multiline_comment|/* Status Register */
DECL|macro|HASR_82586_INTR
mdefine_line|#define&t;&t;HASR_82586_INTR&t;&t;0x0001&t;/* Interrupt request from 82586 */
DECL|macro|HASR_MMC_INTR
mdefine_line|#define&t;&t;HASR_MMC_INTR&t;&t;0x0002&t;/* Interrupt request from MMC */
DECL|macro|HASR_MMC_BUSY
mdefine_line|#define&t;&t;HASR_MMC_BUSY&t;&t;0x0004&t;/* MMC busy indication */
DECL|macro|HASR_PSA_BUSY
mdefine_line|#define&t;&t;HASR_PSA_BUSY&t;&t;0x0008&t;/* LAN parameter storage area busy */
)brace
suffix:semicolon
DECL|typedef|ha_t
r_typedef
r_struct
id|ha_t
id|ha_t
suffix:semicolon
DECL|struct|ha_t
r_struct
id|ha_t
(brace
DECL|member|ha_cs
id|hacs_u
id|ha_cs
suffix:semicolon
multiline_comment|/* Command and status registers */
DECL|macro|ha_command
mdefine_line|#define &t;&t;ha_command&t;ha_cs.hu_command
DECL|macro|ha_status
mdefine_line|#define &t;&t;ha_status&t;ha_cs.hu_status
DECL|member|ha_mmcr
r_int
r_int
id|ha_mmcr
suffix:semicolon
multiline_comment|/* Modem Management Ctrl Register */
DECL|member|ha_pior0
r_int
r_int
id|ha_pior0
suffix:semicolon
multiline_comment|/* Program I/O Address Register Port 0 */
DECL|member|ha_piop0
r_int
r_int
id|ha_piop0
suffix:semicolon
multiline_comment|/* Program I/O Port 0 */
DECL|member|ha_pior1
r_int
r_int
id|ha_pior1
suffix:semicolon
multiline_comment|/* Program I/O Address Register Port 1 */
DECL|member|ha_piop1
r_int
r_int
id|ha_piop1
suffix:semicolon
multiline_comment|/* Program I/O Port 1 */
DECL|member|ha_pior2
r_int
r_int
id|ha_pior2
suffix:semicolon
multiline_comment|/* Program I/O Address Register Port 2 */
DECL|member|ha_piop2
r_int
r_int
id|ha_piop2
suffix:semicolon
multiline_comment|/* Program I/O Port 2 */
)brace
suffix:semicolon
DECL|macro|HA_SIZE
mdefine_line|#define HA_SIZE&t;&t;16
DECL|macro|hoff
mdefine_line|#define&t;hoff(p,f) &t;(unsigned short)((void *)(&amp;((ha_t *)((void *)0 + (p)))-&gt;f) - (void *)0)
DECL|macro|HACR
mdefine_line|#define&t;HACR(p)&t;&t;hoff(p, ha_command)
DECL|macro|HASR
mdefine_line|#define&t;HASR(p)&t;&t;hoff(p, ha_status)
DECL|macro|MMCR
mdefine_line|#define&t;MMCR(p)&t;&t;hoff(p, ha_mmcr)
DECL|macro|PIOR0
mdefine_line|#define&t;PIOR0(p)&t;hoff(p, ha_pior0)
DECL|macro|PIOP0
mdefine_line|#define&t;PIOP0(p)&t;hoff(p, ha_piop0)
DECL|macro|PIOR1
mdefine_line|#define&t;PIOR1(p)&t;hoff(p, ha_pior1)
DECL|macro|PIOP1
mdefine_line|#define&t;PIOP1(p)&t;hoff(p, ha_piop1)
DECL|macro|PIOR2
mdefine_line|#define&t;PIOR2(p)&t;hoff(p, ha_pior2)
DECL|macro|PIOP2
mdefine_line|#define&t;PIOP2(p)&t;hoff(p, ha_piop2)
multiline_comment|/*&n; * Program I/O Mode Register values.&n; */
DECL|macro|STATIC_PIO
mdefine_line|#define STATIC_PIO&t;&t;0&t;/* Mode 1: static mode */
multiline_comment|/* RAM access ??? */
DECL|macro|AUTOINCR_PIO
mdefine_line|#define AUTOINCR_PIO&t;&t;1&t;/* Mode 2: auto increment mode */
multiline_comment|/* RAM access ??? */
DECL|macro|AUTODECR_PIO
mdefine_line|#define AUTODECR_PIO&t;&t;2&t;/* Mode 3: auto decrement mode */
multiline_comment|/* RAM access ??? */
DECL|macro|PARAM_ACCESS_PIO
mdefine_line|#define PARAM_ACCESS_PIO&t;3&t;/* Mode 4: LAN parameter access mode */
multiline_comment|/* Parameter access. */
DECL|macro|PIO_MASK
mdefine_line|#define PIO_MASK&t;&t;3&t;/* register mask */
DECL|macro|PIOM
mdefine_line|#define PIOM(cmd,piono)&t;&t;((u_short)cmd &lt;&lt; 10 &lt;&lt; (piono * 2))
DECL|macro|HACR_DEFAULT
mdefine_line|#define&t;HACR_DEFAULT&t;&t;(HACR_OUT0 | HACR_OUT1 | HACR_16BITS | PIOM(STATIC_PIO, 0) | PIOM(AUTOINCR_PIO, 1) | PIOM(PARAM_ACCESS_PIO, 2))
DECL|macro|HACR_INTRON
mdefine_line|#define&t;HACR_INTRON&t;&t;(HACR_82586_INT_ENABLE | HACR_MMC_INT_ENABLE | HACR_INTR_CLR_ENABLE)
multiline_comment|/************************** MEMORY LAYOUT **************************/
multiline_comment|/*&n; * Onboard 64 k RAM layout.&n; * (Offsets from 0x0000.)&n; */
DECL|macro|OFFSET_RU
mdefine_line|#define OFFSET_RU&t;&t;0x0000&t;&t;/* 75% memory */
DECL|macro|OFFSET_CU
mdefine_line|#define OFFSET_CU&t;&t;0xC000&t;&t;/* 25% memory */
DECL|macro|OFFSET_SCB
mdefine_line|#define OFFSET_SCB&t;&t;(OFFSET_ISCP - sizeof(scb_t))
DECL|macro|OFFSET_ISCP
mdefine_line|#define OFFSET_ISCP&t;&t;(OFFSET_SCP - sizeof(iscp_t))
DECL|macro|OFFSET_SCP
mdefine_line|#define OFFSET_SCP&t;&t;I82586_SCP_ADDR
DECL|macro|RXBLOCKZ
mdefine_line|#define&t;RXBLOCKZ&t;&t;(sizeof(fd_t) + sizeof(rbd_t) + MAXDATAZ)
DECL|macro|TXBLOCKZ
mdefine_line|#define&t;TXBLOCKZ&t;&t;(sizeof(ac_tx_t) + sizeof(ac_nop_t) + sizeof(tbd_t) + MAXDATAZ)
DECL|macro|NRXBLOCKS
mdefine_line|#define&t;NRXBLOCKS&t;&t;((OFFSET_CU - OFFSET_RU) / RXBLOCKZ)
DECL|macro|NTXBLOCKS
mdefine_line|#define&t;NTXBLOCKS&t;&t;((OFFSET_SCB - OFFSET_CU) / TXBLOCKZ)
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
multiline_comment|/* [0x1D] Compatibility Number:&t; */
DECL|macro|PSA_COMP_PC_AT_915
mdefine_line|#define&t;&t;PSA_COMP_PC_AT_915&t;0 &t;/* PC-AT 915 MHz &t; */
DECL|macro|PSA_COMP_PC_MC_915
mdefine_line|#define&t;&t;PSA_COMP_PC_MC_915&t;1 &t;/* PC-MC 915 MHz&t; */
DECL|macro|PSA_COMP_PC_AT_2400
mdefine_line|#define&t;&t;PSA_COMP_PC_AT_2400&t;2 &t;/* PC-AT 2.4 GHz&t; */
DECL|macro|PSA_COMP_PC_MC_2400
mdefine_line|#define&t;&t;PSA_COMP_PC_MC_2400&t;3 &t;/* PC-MC 2.4 GHz &t; */
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
multiline_comment|/* [0x20] Subband&t;  */
DECL|macro|PSA_SUBBAND_915
mdefine_line|#define&t;&t;PSA_SUBBAND_915&t;&t;0&t;/* 915 MHz or 2.0 */
DECL|macro|PSA_SUBBAND_2425
mdefine_line|#define&t;&t;PSA_SUBBAND_2425&t;1&t;/* 2425 MHz&t;  */
DECL|macro|PSA_SUBBAND_2460
mdefine_line|#define&t;&t;PSA_SUBBAND_2460&t;2&t;/* 2460 MHz&t;  */
DECL|macro|PSA_SUBBAND_2484
mdefine_line|#define&t;&t;PSA_SUBBAND_2484&t;3&t;/* 2484 MHz&t;  */
DECL|macro|PSA_SUBBAND_2430_5
mdefine_line|#define&t;&t;PSA_SUBBAND_2430_5&t;4&t;/* 2430.5 MHz&t;  */
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
multiline_comment|/* [0x22] Modem Delay (?) (reserved) */
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
multiline_comment|/* [0x25] Network ID Select On/Off */
DECL|member|psa_encryption_select
r_int
r_char
id|psa_encryption_select
suffix:semicolon
multiline_comment|/* [0x26] Encryption On/Off */
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
DECL|macro|PSA_SIZE
mdefine_line|#define&t;PSA_SIZE&t;64
multiline_comment|/* Calculate offset of a field in the above structure.&n; * Warning:  only even addresses are used. */
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
multiline_comment|/* Enable or disable encryption. */
DECL|macro|MMW_ENCR_ENABLE_MODE
mdefine_line|#define&t;MMW_ENCR_ENABLE_MODE&t;0x02&t;/* mode of security option */
DECL|macro|MMW_ENCR_ENABLE_EN
mdefine_line|#define&t;MMW_ENCR_ENABLE_EN&t;0x01&t;/* Enable security option. */
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
multiline_comment|/* encryption option */
DECL|macro|MMW_DES_IO_INVERT_RES
mdefine_line|#define&t;MMW_DES_IO_INVERT_RES&t;0x0F&t;/* reserved */
DECL|macro|MMW_DES_IO_INVERT_CTRL
mdefine_line|#define&t;MMW_DES_IO_INVERT_CTRL&t;0xF0&t;/* control (?) (set to 0) */
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
mdefine_line|#define&t;MMW_LOOPT_SEL_DIS_NWID&t;0x40&t;/* Disable NWID filtering. */
DECL|macro|MMW_LOOPT_SEL_INT
mdefine_line|#define&t;MMW_LOOPT_SEL_INT&t;0x20&t;/* Activate Attention Request. */
DECL|macro|MMW_LOOPT_SEL_LS
mdefine_line|#define&t;MMW_LOOPT_SEL_LS&t;0x10&t;/* looptest, no collision avoidance */
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
multiline_comment|/* freeze or unfreeze signal level */
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
multiline_comment|/* decay update parameters */
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
multiline_comment|/* frequency EEPROM control */
DECL|macro|MMW_FEE_CTRL_PRE
mdefine_line|#define&t;MMW_FEE_CTRL_PRE&t;0x10&t;/* Enable protected instructions. */
DECL|macro|MMW_FEE_CTRL_DWLD
mdefine_line|#define&t;MMW_FEE_CTRL_DWLD&t;0x08&t;/* Download EEPROM to mmc. */
DECL|macro|MMW_FEE_CTRL_CMD
mdefine_line|#define&t;MMW_FEE_CTRL_CMD&t;0x07&t;/* EEPROM commands:  */
DECL|macro|MMW_FEE_CTRL_READ
mdefine_line|#define&t;MMW_FEE_CTRL_READ&t;0x06&t;/* Read */
DECL|macro|MMW_FEE_CTRL_WREN
mdefine_line|#define&t;MMW_FEE_CTRL_WREN&t;0x04&t;/* Write enable */
DECL|macro|MMW_FEE_CTRL_WRITE
mdefine_line|#define&t;MMW_FEE_CTRL_WRITE&t;0x05&t;/* Write data to address. */
DECL|macro|MMW_FEE_CTRL_WRALL
mdefine_line|#define&t;MMW_FEE_CTRL_WRALL&t;0x04&t;/* Write data to all addresses. */
DECL|macro|MMW_FEE_CTRL_WDS
mdefine_line|#define&t;MMW_FEE_CTRL_WDS&t;0x04&t;/* Write disable */
DECL|macro|MMW_FEE_CTRL_PRREAD
mdefine_line|#define&t;MMW_FEE_CTRL_PRREAD&t;0x16&t;/* Read addr from protect register */
DECL|macro|MMW_FEE_CTRL_PREN
mdefine_line|#define&t;MMW_FEE_CTRL_PREN&t;0x14&t;/* Protect register enable */
DECL|macro|MMW_FEE_CTRL_PRCLEAR
mdefine_line|#define&t;MMW_FEE_CTRL_PRCLEAR&t;0x17&t;/* Unprotect all registers. */
DECL|macro|MMW_FEE_CTRL_PRWRITE
mdefine_line|#define&t;MMW_FEE_CTRL_PRWRITE&t;0x15&t;/* Write address in protect register */
DECL|macro|MMW_FEE_CTRL_PRDS
mdefine_line|#define&t;MMW_FEE_CTRL_PRDS&t;0x14&t;/* Protect register disable */
multiline_comment|/* Never issue the PRDS command:  it&squot;s irreversible! */
DECL|member|mmw_fee_addr
r_int
r_char
id|mmw_fee_addr
suffix:semicolon
multiline_comment|/* EEPROM address */
DECL|macro|MMW_FEE_ADDR_CHANNEL
mdefine_line|#define&t;MMW_FEE_ADDR_CHANNEL&t;0xF0&t;/* Select the channel. */
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
multiline_comment|/* Write data to EEPROM. */
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
DECL|macro|MMW_SIZE
mdefine_line|#define&t;MMW_SIZE&t;37
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
multiline_comment|/* DSP ID (AA = Daedalus rev A) */
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
multiline_comment|/* # of correct NWIDs rxd (low) */
DECL|member|mmr_correct_nwid_h
r_int
r_char
id|mmr_correct_nwid_h
suffix:semicolon
multiline_comment|/* # of correct NWIDs rxd (high) */
multiline_comment|/* Warning:  read high-order octet first! */
DECL|member|mmr_wrong_nwid_l
r_int
r_char
id|mmr_wrong_nwid_l
suffix:semicolon
multiline_comment|/* # of wrong NWIDs rxd (low) */
DECL|member|mmr_wrong_nwid_h
r_int
r_char
id|mmr_wrong_nwid_h
suffix:semicolon
multiline_comment|/* # of wrong NWIDs rxd (high) */
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
multiline_comment|/* NWID low order byte (?) */
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
multiline_comment|/* Status of frequency EEPROM */
DECL|macro|MMR_FEE_STATUS_ID
mdefine_line|#define&t;MMR_FEE_STATUS_ID&t;0xF0&t;&t;/* Modem revision ID */
DECL|macro|MMR_FEE_STATUS_DWLD
mdefine_line|#define&t;MMR_FEE_STATUS_DWLD&t;0x08&t;&t;/* Download in progress */
DECL|macro|MMR_FEE_STATUS_BUSY
mdefine_line|#define&t;MMR_FEE_STATUS_BUSY&t;0x04&t;&t;/* EEPROM busy */
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
multiline_comment|/* Read data from EEPROM (low) */
DECL|member|mmr_fee_data_h
r_int
r_char
id|mmr_fee_data_h
suffix:semicolon
multiline_comment|/* Read data from EEPROM (high) */
)brace
suffix:semicolon
DECL|macro|MMR_SIZE
mdefine_line|#define&t;MMR_SIZE&t;36
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
macro_line|#endif /* _WAVELAN_H */
multiline_comment|/*&n; * This software may only be used and distributed&n; * according to the terms of the GNU General Public License.&n; *&n; * For more details, see wavelan.c.&n; */
eof
