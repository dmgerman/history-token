multiline_comment|/*&n; *  Amiga Linux/m68k Ariadne Ethernet Driver&n; *&n; *  &#xfffd; Copyright 1995 by Geert Uytterhoeven (geert@linux-m68k.org)&n; *&t;&t;&t;Peter De Schrijver&n; *&t;&t;       (Peter.DeSchrijver@linux.cc.kuleuven.ac.be)&n; *&n; *  ----------------------------------------------------------------------------------&n; *&n; *  This program is based on&n; *&n; *&t;lance.c:&t;An AMD LANCE ethernet driver for linux.&n; *&t;&t;&t;Written 1993-94 by Donald Becker.&n; *&n; *&t;Am79C960:&t;PCnet(tm)-ISA Single-Chip Ethernet Controller&n; *&t;&t;&t;Advanced Micro Devices&n; *&t;&t;&t;Publication #16907, Rev. B, Amendment/0, May 1994&n; *&n; *&t;MC68230:&t;Parallel Interface/Timer (PI/T)&n; *&t;&t;&t;Motorola Semiconductors, December, 1983&n; *&n; *  ----------------------------------------------------------------------------------&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of the Linux&n; *  distribution for more details.&n; *&n; *  ----------------------------------------------------------------------------------&n; *&n; *  The Ariadne is a Zorro-II board made by Village Tronic. It contains:&n; *&n; *&t;- an Am79C960 PCnet-ISA Single-Chip Ethernet Controller with both&n; *&t;  10BASE-2 (thin coax) and 10BASE-T (UTP) connectors&n; *&n; *&t;- an MC68230 Parallel Interface/Timer configured as 2 parallel ports&n; */
multiline_comment|/*&n;     *&t;Am79C960 PCnet-ISA&n;     */
DECL|struct|Am79C960
r_struct
id|Am79C960
(brace
DECL|member|AddressPROM
r_volatile
id|u_short
id|AddressPROM
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* IEEE Address PROM (Unused in the Ariadne) */
DECL|member|RDP
r_volatile
id|u_short
id|RDP
suffix:semicolon
multiline_comment|/* Register Data Port */
DECL|member|RAP
r_volatile
id|u_short
id|RAP
suffix:semicolon
multiline_comment|/* Register Address Port */
DECL|member|Reset
r_volatile
id|u_short
id|Reset
suffix:semicolon
multiline_comment|/* Reset Chip on Read Access */
DECL|member|IDP
r_volatile
id|u_short
id|IDP
suffix:semicolon
multiline_comment|/* ISACSR Data Port */
)brace
suffix:semicolon
multiline_comment|/*&n;     *&t;Am79C960 Control and Status Registers&n;     *&n;     *&t;These values are already swap()ed!!&n;     *&n;     *&t;Only registers marked with a `-&squot; are intended for network software&n;     *&t;access&n;     */
DECL|macro|CSR0
mdefine_line|#define CSR0&t;&t;0x0000&t;/* - PCnet-ISA Controller Status */
DECL|macro|CSR1
mdefine_line|#define CSR1&t;&t;0x0100&t;/* - IADR[15:0] */
DECL|macro|CSR2
mdefine_line|#define CSR2&t;&t;0x0200&t;/* - IADR[23:16] */
DECL|macro|CSR3
mdefine_line|#define CSR3&t;&t;0x0300&t;/* - Interrupt Masks and Deferral Control */
DECL|macro|CSR4
mdefine_line|#define CSR4&t;&t;0x0400&t;/* - Test and Features Control */
DECL|macro|CSR6
mdefine_line|#define CSR6&t;&t;0x0600&t;/*   RCV/XMT Descriptor Table Length */
DECL|macro|CSR8
mdefine_line|#define CSR8&t;&t;0x0800&t;/* - Logical Address Filter, LADRF[15:0] */
DECL|macro|CSR9
mdefine_line|#define CSR9&t;&t;0x0900&t;/* - Logical Address Filter, LADRF[31:16] */
DECL|macro|CSR10
mdefine_line|#define CSR10&t;&t;0x0a00&t;/* - Logical Address Filter, LADRF[47:32] */
DECL|macro|CSR11
mdefine_line|#define CSR11&t;&t;0x0b00&t;/* - Logical Address Filter, LADRF[63:48] */
DECL|macro|CSR12
mdefine_line|#define CSR12&t;&t;0x0c00&t;/* - Physical Address Register, PADR[15:0] */
DECL|macro|CSR13
mdefine_line|#define CSR13&t;&t;0x0d00&t;/* - Physical Address Register, PADR[31:16] */
DECL|macro|CSR14
mdefine_line|#define CSR14&t;&t;0x0e00&t;/* - Physical Address Register, PADR[47:32] */
DECL|macro|CSR15
mdefine_line|#define CSR15&t;&t;0x0f00&t;/* - Mode Register */
DECL|macro|CSR16
mdefine_line|#define CSR16&t;&t;0x1000&t;/*   Initialization Block Address Lower */
DECL|macro|CSR17
mdefine_line|#define CSR17&t;&t;0x1100&t;/*   Initialization Block Address Upper */
DECL|macro|CSR18
mdefine_line|#define CSR18&t;&t;0x1200&t;/*   Current Receive Buffer Address */
DECL|macro|CSR19
mdefine_line|#define CSR19&t;&t;0x1300&t;/*   Current Receive Buffer Address */
DECL|macro|CSR20
mdefine_line|#define CSR20&t;&t;0x1400&t;/*   Current Transmit Buffer Address */
DECL|macro|CSR21
mdefine_line|#define CSR21&t;&t;0x1500&t;/*   Current Transmit Buffer Address */
DECL|macro|CSR22
mdefine_line|#define CSR22&t;&t;0x1600&t;/*   Next Receive Buffer Address */
DECL|macro|CSR23
mdefine_line|#define CSR23&t;&t;0x1700&t;/*   Next Receive Buffer Address */
DECL|macro|CSR24
mdefine_line|#define CSR24&t;&t;0x1800&t;/* - Base Address of Receive Ring */
DECL|macro|CSR25
mdefine_line|#define CSR25&t;&t;0x1900&t;/* - Base Address of Receive Ring */
DECL|macro|CSR26
mdefine_line|#define CSR26&t;&t;0x1a00&t;/*   Next Receive Descriptor Address */
DECL|macro|CSR27
mdefine_line|#define CSR27&t;&t;0x1b00&t;/*   Next Receive Descriptor Address */
DECL|macro|CSR28
mdefine_line|#define CSR28&t;&t;0x1c00&t;/*   Current Receive Descriptor Address */
DECL|macro|CSR29
mdefine_line|#define CSR29&t;&t;0x1d00&t;/*   Current Receive Descriptor Address */
DECL|macro|CSR30
mdefine_line|#define CSR30&t;&t;0x1e00&t;/* - Base Address of Transmit Ring */
DECL|macro|CSR31
mdefine_line|#define CSR31&t;&t;0x1f00&t;/* - Base Address of transmit Ring */
DECL|macro|CSR32
mdefine_line|#define CSR32&t;&t;0x2000&t;/*   Next Transmit Descriptor Address */
DECL|macro|CSR33
mdefine_line|#define CSR33&t;&t;0x2100&t;/*   Next Transmit Descriptor Address */
DECL|macro|CSR34
mdefine_line|#define CSR34&t;&t;0x2200&t;/*   Current Transmit Descriptor Address */
DECL|macro|CSR35
mdefine_line|#define CSR35&t;&t;0x2300&t;/*   Current Transmit Descriptor Address */
DECL|macro|CSR36
mdefine_line|#define CSR36&t;&t;0x2400&t;/*   Next Next Receive Descriptor Address */
DECL|macro|CSR37
mdefine_line|#define CSR37&t;&t;0x2500&t;/*   Next Next Receive Descriptor Address */
DECL|macro|CSR38
mdefine_line|#define CSR38&t;&t;0x2600&t;/*   Next Next Transmit Descriptor Address */
DECL|macro|CSR39
mdefine_line|#define CSR39&t;&t;0x2700&t;/*   Next Next Transmit Descriptor Address */
DECL|macro|CSR40
mdefine_line|#define CSR40&t;&t;0x2800&t;/*   Current Receive Status and Byte Count */
DECL|macro|CSR41
mdefine_line|#define CSR41&t;&t;0x2900&t;/*   Current Receive Status and Byte Count */
DECL|macro|CSR42
mdefine_line|#define CSR42&t;&t;0x2a00&t;/*   Current Transmit Status and Byte Count */
DECL|macro|CSR43
mdefine_line|#define CSR43&t;&t;0x2b00&t;/*   Current Transmit Status and Byte Count */
DECL|macro|CSR44
mdefine_line|#define CSR44&t;&t;0x2c00&t;/*   Next Receive Status and Byte Count */
DECL|macro|CSR45
mdefine_line|#define CSR45&t;&t;0x2d00&t;/*   Next Receive Status and Byte Count */
DECL|macro|CSR46
mdefine_line|#define CSR46&t;&t;0x2e00&t;/*   Poll Time Counter */
DECL|macro|CSR47
mdefine_line|#define CSR47&t;&t;0x2f00&t;/*   Polling Interval */
DECL|macro|CSR48
mdefine_line|#define CSR48&t;&t;0x3000&t;/*   Temporary Storage */
DECL|macro|CSR49
mdefine_line|#define CSR49&t;&t;0x3100&t;/*   Temporary Storage */
DECL|macro|CSR50
mdefine_line|#define CSR50&t;&t;0x3200&t;/*   Temporary Storage */
DECL|macro|CSR51
mdefine_line|#define CSR51&t;&t;0x3300&t;/*   Temporary Storage */
DECL|macro|CSR52
mdefine_line|#define CSR52&t;&t;0x3400&t;/*   Temporary Storage */
DECL|macro|CSR53
mdefine_line|#define CSR53&t;&t;0x3500&t;/*   Temporary Storage */
DECL|macro|CSR54
mdefine_line|#define CSR54&t;&t;0x3600&t;/*   Temporary Storage */
DECL|macro|CSR55
mdefine_line|#define CSR55&t;&t;0x3700&t;/*   Temporary Storage */
DECL|macro|CSR56
mdefine_line|#define CSR56&t;&t;0x3800&t;/*   Temporary Storage */
DECL|macro|CSR57
mdefine_line|#define CSR57&t;&t;0x3900&t;/*   Temporary Storage */
DECL|macro|CSR58
mdefine_line|#define CSR58&t;&t;0x3a00&t;/*   Temporary Storage */
DECL|macro|CSR59
mdefine_line|#define CSR59&t;&t;0x3b00&t;/*   Temporary Storage */
DECL|macro|CSR60
mdefine_line|#define CSR60&t;&t;0x3c00&t;/*   Previous Transmit Descriptor Address */
DECL|macro|CSR61
mdefine_line|#define CSR61&t;&t;0x3d00&t;/*   Previous Transmit Descriptor Address */
DECL|macro|CSR62
mdefine_line|#define CSR62&t;&t;0x3e00&t;/*   Previous Transmit Status and Byte Count */
DECL|macro|CSR63
mdefine_line|#define CSR63&t;&t;0x3f00&t;/*   Previous Transmit Status and Byte Count */
DECL|macro|CSR64
mdefine_line|#define CSR64&t;&t;0x4000&t;/*   Next Transmit Buffer Address */
DECL|macro|CSR65
mdefine_line|#define CSR65&t;&t;0x4100&t;/*   Next Transmit Buffer Address */
DECL|macro|CSR66
mdefine_line|#define CSR66&t;&t;0x4200&t;/*   Next Transmit Status and Byte Count */
DECL|macro|CSR67
mdefine_line|#define CSR67&t;&t;0x4300&t;/*   Next Transmit Status and Byte Count */
DECL|macro|CSR68
mdefine_line|#define CSR68&t;&t;0x4400&t;/*   Transmit Status Temporary Storage */
DECL|macro|CSR69
mdefine_line|#define CSR69&t;&t;0x4500&t;/*   Transmit Status Temporary Storage */
DECL|macro|CSR70
mdefine_line|#define CSR70&t;&t;0x4600&t;/*   Temporary Storage */
DECL|macro|CSR71
mdefine_line|#define CSR71&t;&t;0x4700&t;/*   Temporary Storage */
DECL|macro|CSR72
mdefine_line|#define CSR72&t;&t;0x4800&t;/*   Receive Ring Counter */
DECL|macro|CSR74
mdefine_line|#define CSR74&t;&t;0x4a00&t;/*   Transmit Ring Counter */
DECL|macro|CSR76
mdefine_line|#define CSR76&t;&t;0x4c00&t;/* - Receive Ring Length */
DECL|macro|CSR78
mdefine_line|#define CSR78&t;&t;0x4e00&t;/* - Transmit Ring Length */
DECL|macro|CSR80
mdefine_line|#define CSR80&t;&t;0x5000&t;/* - Burst and FIFO Threshold Control */
DECL|macro|CSR82
mdefine_line|#define CSR82&t;&t;0x5200&t;/* - Bus Activity Timer */
DECL|macro|CSR84
mdefine_line|#define CSR84&t;&t;0x5400&t;/*   DMA Address */
DECL|macro|CSR85
mdefine_line|#define CSR85&t;&t;0x5500&t;/*   DMA Address */
DECL|macro|CSR86
mdefine_line|#define CSR86&t;&t;0x5600&t;/*   Buffer Byte Counter */
DECL|macro|CSR88
mdefine_line|#define CSR88&t;&t;0x5800&t;/* - Chip ID */
DECL|macro|CSR89
mdefine_line|#define CSR89&t;&t;0x5900&t;/* - Chip ID */
DECL|macro|CSR92
mdefine_line|#define CSR92&t;&t;0x5c00&t;/*   Ring Length Conversion */
DECL|macro|CSR94
mdefine_line|#define CSR94&t;&t;0x5e00&t;/*   Transmit Time Domain Reflectometry Count */
DECL|macro|CSR96
mdefine_line|#define CSR96&t;&t;0x6000&t;/*   Bus Interface Scratch Register 0 */
DECL|macro|CSR97
mdefine_line|#define CSR97&t;&t;0x6100&t;/*   Bus Interface Scratch Register 0 */
DECL|macro|CSR98
mdefine_line|#define CSR98&t;&t;0x6200&t;/*   Bus Interface Scratch Register 1 */
DECL|macro|CSR99
mdefine_line|#define CSR99&t;&t;0x6300&t;/*   Bus Interface Scratch Register 1 */
DECL|macro|CSR104
mdefine_line|#define CSR104&t;&t;0x6800&t;/*   SWAP */
DECL|macro|CSR105
mdefine_line|#define CSR105&t;&t;0x6900&t;/*   SWAP */
DECL|macro|CSR108
mdefine_line|#define CSR108&t;&t;0x6c00&t;/*   Buffer Management Scratch */
DECL|macro|CSR109
mdefine_line|#define CSR109&t;&t;0x6d00&t;/*   Buffer Management Scratch */
DECL|macro|CSR112
mdefine_line|#define CSR112&t;&t;0x7000&t;/* - Missed Frame Count */
DECL|macro|CSR114
mdefine_line|#define CSR114&t;&t;0x7200&t;/* - Receive Collision Count */
DECL|macro|CSR124
mdefine_line|#define CSR124&t;&t;0x7c00&t;/* - Buffer Management Unit Test */
multiline_comment|/*&n;     *&t;Am79C960 ISA Control and Status Registers&n;     *&n;     *&t;These values are already swap()ed!!&n;     */
DECL|macro|ISACSR0
mdefine_line|#define ISACSR0&t;&t;0x0000&t;/* Master Mode Read Active */
DECL|macro|ISACSR1
mdefine_line|#define ISACSR1&t;&t;0x0100&t;/* Master Mode Write Active */
DECL|macro|ISACSR2
mdefine_line|#define ISACSR2&t;&t;0x0200&t;/* Miscellaneous Configuration */
DECL|macro|ISACSR4
mdefine_line|#define ISACSR4&t;&t;0x0400&t;/* LED0 Status (Link Integrity) */
DECL|macro|ISACSR5
mdefine_line|#define ISACSR5&t;&t;0x0500&t;/* LED1 Status */
DECL|macro|ISACSR6
mdefine_line|#define ISACSR6&t;&t;0x0600&t;/* LED2 Status */
DECL|macro|ISACSR7
mdefine_line|#define ISACSR7&t;&t;0x0700&t;/* LED3 Status */
multiline_comment|/*&n;     *&t;Bit definitions for CSR0 (PCnet-ISA Controller Status)&n;     *&n;     *&t;These values are already swap()ed!!&n;     */
DECL|macro|ERR
mdefine_line|#define ERR&t;&t;0x0080&t;/* Error */
DECL|macro|BABL
mdefine_line|#define BABL&t;&t;0x0040&t;/* Babble: Transmitted too many bits */
DECL|macro|CERR
mdefine_line|#define CERR&t;&t;0x0020&t;/* No Heartbeat (10BASE-T) */
DECL|macro|MISS
mdefine_line|#define MISS&t;&t;0x0010&t;/* Missed Frame */
DECL|macro|MERR
mdefine_line|#define MERR&t;&t;0x0008&t;/* Memory Error */
DECL|macro|RINT
mdefine_line|#define RINT&t;&t;0x0004&t;/* Receive Interrupt */
DECL|macro|TINT
mdefine_line|#define TINT&t;&t;0x0002&t;/* Transmit Interrupt */
DECL|macro|IDON
mdefine_line|#define IDON&t;&t;0x0001&t;/* Initialization Done */
DECL|macro|INTR
mdefine_line|#define INTR&t;&t;0x8000&t;/* Interrupt Flag */
DECL|macro|INEA
mdefine_line|#define INEA&t;&t;0x4000&t;/* Interrupt Enable */
DECL|macro|RXON
mdefine_line|#define RXON&t;&t;0x2000&t;/* Receive On */
DECL|macro|TXON
mdefine_line|#define TXON&t;&t;0x1000&t;/* Transmit On */
DECL|macro|TDMD
mdefine_line|#define TDMD&t;&t;0x0800&t;/* Transmit Demand */
DECL|macro|STOP
mdefine_line|#define STOP&t;&t;0x0400&t;/* Stop */
DECL|macro|STRT
mdefine_line|#define STRT&t;&t;0x0200&t;/* Start */
DECL|macro|INIT
mdefine_line|#define INIT&t;&t;0x0100&t;/* Initialize */
multiline_comment|/*&n;     *&t;Bit definitions for CSR3 (Interrupt Masks and Deferral Control)&n;     *&n;     *&t;These values are already swap()ed!!&n;     */
DECL|macro|BABLM
mdefine_line|#define BABLM&t;&t;0x0040&t;/* Babble Mask */
DECL|macro|MISSM
mdefine_line|#define MISSM&t;&t;0x0010&t;/* Missed Frame Mask */
DECL|macro|MERRM
mdefine_line|#define MERRM&t;&t;0x0008&t;/* Memory Error Mask */
DECL|macro|RINTM
mdefine_line|#define RINTM&t;&t;0x0004&t;/* Receive Interrupt Mask */
DECL|macro|TINTM
mdefine_line|#define TINTM&t;&t;0x0002&t;/* Transmit Interrupt Mask */
DECL|macro|IDONM
mdefine_line|#define IDONM&t;&t;0x0001&t;/* Initialization Done Mask */
DECL|macro|DXMT2PD
mdefine_line|#define DXMT2PD&t;&t;0x1000&t;/* Disable Transmit Two Part Deferral */
DECL|macro|EMBA
mdefine_line|#define EMBA&t;&t;0x0800&t;/* Enable Modified Back-off Algorithm */
multiline_comment|/*&n;     *&t;Bit definitions for CSR4 (Test and Features Control)&n;     *&n;     *&t;These values are already swap()ed!!&n;     */
DECL|macro|ENTST
mdefine_line|#define ENTST&t;&t;0x0080&t;/* Enable Test Mode */
DECL|macro|DMAPLUS
mdefine_line|#define DMAPLUS&t;&t;0x0040&t;/* Disable Burst Transaction Counter */
DECL|macro|TIMER
mdefine_line|#define TIMER&t;&t;0x0020&t;/* Timer Enable Register */
DECL|macro|DPOLL
mdefine_line|#define DPOLL&t;&t;0x0010&t;/* Disable Transmit Polling */
DECL|macro|APAD_XMT
mdefine_line|#define APAD_XMT&t;0x0008&t;/* Auto Pad Transmit */
DECL|macro|ASTRP_RCV
mdefine_line|#define ASTRP_RCV&t;0x0004&t;/* Auto Pad Stripping */
DECL|macro|MFCO
mdefine_line|#define MFCO&t;&t;0x0002&t;/* Missed Frame Counter Overflow Interrupt */
DECL|macro|MFCOM
mdefine_line|#define MFCOM&t;&t;0x0001&t;/* Missed Frame Counter Overflow Mask */
DECL|macro|RCVCCO
mdefine_line|#define RCVCCO&t;&t;0x2000&t;/* Receive Collision Counter Overflow Interrupt */
DECL|macro|RCVCCOM
mdefine_line|#define RCVCCOM&t;&t;0x1000&t;/* Receive Collision Counter Overflow Mask */
DECL|macro|TXSTRT
mdefine_line|#define TXSTRT&t;&t;0x0800&t;/* Transmit Start Status */
DECL|macro|TXSTRTM
mdefine_line|#define TXSTRTM&t;&t;0x0400&t;/* Transmit Start Mask */
DECL|macro|JAB
mdefine_line|#define JAB&t;&t;0x0200&t;/* Jabber Error */
DECL|macro|JABM
mdefine_line|#define JABM&t;&t;0x0100&t;/* Jabber Error Mask */
multiline_comment|/*&n;     *&t;Bit definitions for CSR15 (Mode Register)&n;     *&n;     *&t;These values are already swap()ed!!&n;     */
DECL|macro|PROM
mdefine_line|#define PROM&t;&t;0x0080&t;/* Promiscuous Mode */
DECL|macro|DRCVBC
mdefine_line|#define DRCVBC&t;&t;0x0040&t;/* Disable Receive Broadcast */
DECL|macro|DRCVPA
mdefine_line|#define DRCVPA&t;&t;0x0020&t;/* Disable Receive Physical Address */
DECL|macro|DLNKTST
mdefine_line|#define DLNKTST&t;&t;0x0010&t;/* Disable Link Status */
DECL|macro|DAPC
mdefine_line|#define DAPC&t;&t;0x0008&t;/* Disable Automatic Polarity Correction */
DECL|macro|MENDECL
mdefine_line|#define MENDECL&t;&t;0x0004&t;/* MENDEC Loopback Mode */
DECL|macro|LRTTSEL
mdefine_line|#define LRTTSEL&t;&t;0x0002&t;/* Low Receive Treshold/Transmit Mode Select */
DECL|macro|PORTSEL1
mdefine_line|#define PORTSEL1&t;0x0001&t;/* Port Select Bits */
DECL|macro|PORTSEL2
mdefine_line|#define PORTSEL2&t;0x8000&t;/* Port Select Bits */
DECL|macro|INTL
mdefine_line|#define INTL&t;&t;0x4000&t;/* Internal Loopback */
DECL|macro|DRTY
mdefine_line|#define DRTY&t;&t;0x2000&t;/* Disable Retry */
DECL|macro|FCOLL
mdefine_line|#define FCOLL&t;&t;0x1000&t;/* Force Collision */
DECL|macro|DXMTFCS
mdefine_line|#define DXMTFCS&t;&t;0x0800&t;/* Disable Transmit CRC */
DECL|macro|LOOP
mdefine_line|#define LOOP&t;&t;0x0400&t;/* Loopback Enable */
DECL|macro|DTX
mdefine_line|#define DTX&t;&t;0x0200&t;/* Disable Transmitter */
DECL|macro|DRX
mdefine_line|#define DRX&t;&t;0x0100&t;/* Disable Receiver */
multiline_comment|/*&n;     *&t;Bit definitions for ISACSR2 (Miscellaneous Configuration)&n;     *&n;     *&t;These values are already swap()ed!!&n;     */
DECL|macro|ASEL
mdefine_line|#define ASEL&t;&t;0x0200&t;/* Media Interface Port Auto Select */
multiline_comment|/*&n;     *&t;Bit definitions for ISACSR5-7 (LED1-3 Status)&n;     *&n;     *&t;These values are already swap()ed!!&n;     */
DECL|macro|LEDOUT
mdefine_line|#define LEDOUT&t;&t;0x0080&t;/* Current LED Status */
DECL|macro|PSE
mdefine_line|#define PSE&t;&t;0x8000&t;/* Pulse Stretcher Enable */
DECL|macro|XMTE
mdefine_line|#define XMTE&t;&t;0x1000&t;/* Enable Transmit Status Signal */
DECL|macro|RVPOLE
mdefine_line|#define RVPOLE&t;&t;0x0800&t;/* Enable Receive Polarity Signal */
DECL|macro|RCVE
mdefine_line|#define RCVE&t;&t;0x0400&t;/* Enable Receive Status Signal */
DECL|macro|JABE
mdefine_line|#define JABE&t;&t;0x0200&t;/* Enable Jabber Signal */
DECL|macro|COLE
mdefine_line|#define COLE&t;&t;0x0100&t;/* Enable Collision Signal */
multiline_comment|/*&n;     *&t;Receive Descriptor Ring Entry&n;     */
DECL|struct|RDRE
r_struct
id|RDRE
(brace
DECL|member|RMD0
r_volatile
id|u_short
id|RMD0
suffix:semicolon
multiline_comment|/* LADR[15:0] */
DECL|member|RMD1
r_volatile
id|u_short
id|RMD1
suffix:semicolon
multiline_comment|/* HADR[23:16] | Receive Flags */
DECL|member|RMD2
r_volatile
id|u_short
id|RMD2
suffix:semicolon
multiline_comment|/* Buffer Byte Count (two&squot;s complement) */
DECL|member|RMD3
r_volatile
id|u_short
id|RMD3
suffix:semicolon
multiline_comment|/* Message Byte Count */
)brace
suffix:semicolon
multiline_comment|/*&n;     *&t;Transmit Descriptor Ring Entry&n;     */
DECL|struct|TDRE
r_struct
id|TDRE
(brace
DECL|member|TMD0
r_volatile
id|u_short
id|TMD0
suffix:semicolon
multiline_comment|/* LADR[15:0] */
DECL|member|TMD1
r_volatile
id|u_short
id|TMD1
suffix:semicolon
multiline_comment|/* HADR[23:16] | Transmit Flags */
DECL|member|TMD2
r_volatile
id|u_short
id|TMD2
suffix:semicolon
multiline_comment|/* Buffer Byte Count (two&squot;s complement) */
DECL|member|TMD3
r_volatile
id|u_short
id|TMD3
suffix:semicolon
multiline_comment|/* Error Flags */
)brace
suffix:semicolon
multiline_comment|/*&n;     *&t;Receive Flags&n;     */
DECL|macro|RF_OWN
mdefine_line|#define RF_OWN&t;&t;0x0080&t;/* PCnet-ISA controller owns the descriptor */
DECL|macro|RF_ERR
mdefine_line|#define RF_ERR&t;&t;0x0040&t;/* Error */
DECL|macro|RF_FRAM
mdefine_line|#define RF_FRAM&t;&t;0x0020&t;/* Framing Error */
DECL|macro|RF_OFLO
mdefine_line|#define RF_OFLO&t;&t;0x0010&t;/* Overflow Error */
DECL|macro|RF_CRC
mdefine_line|#define RF_CRC&t;&t;0x0008&t;/* CRC Error */
DECL|macro|RF_BUFF
mdefine_line|#define RF_BUFF&t;&t;0x0004&t;/* Buffer Error */
DECL|macro|RF_STP
mdefine_line|#define RF_STP&t;&t;0x0002&t;/* Start of Packet */
DECL|macro|RF_ENP
mdefine_line|#define RF_ENP&t;&t;0x0001&t;/* End of Packet */
multiline_comment|/*&n;     *&t;Transmit Flags&n;     */
DECL|macro|TF_OWN
mdefine_line|#define TF_OWN&t;&t;0x0080&t;/* PCnet-ISA controller owns the descriptor */
DECL|macro|TF_ERR
mdefine_line|#define TF_ERR&t;&t;0x0040&t;/* Error */
DECL|macro|TF_ADD_FCS
mdefine_line|#define TF_ADD_FCS&t;0x0020&t;/* Controls FCS Generation */
DECL|macro|TF_MORE
mdefine_line|#define TF_MORE&t;&t;0x0010&t;/* More than one retry needed */
DECL|macro|TF_ONE
mdefine_line|#define TF_ONE&t;&t;0x0008&t;/* One retry needed */
DECL|macro|TF_DEF
mdefine_line|#define TF_DEF&t;&t;0x0004&t;/* Deferred */
DECL|macro|TF_STP
mdefine_line|#define TF_STP&t;&t;0x0002&t;/* Start of Packet */
DECL|macro|TF_ENP
mdefine_line|#define TF_ENP&t;&t;0x0001&t;/* End of Packet */
multiline_comment|/*&n;     *&t;Error Flags&n;     */
DECL|macro|EF_BUFF
mdefine_line|#define EF_BUFF&t;&t;0x0080&t;/* Buffer Error */
DECL|macro|EF_UFLO
mdefine_line|#define EF_UFLO&t;&t;0x0040&t;/* Underflow Error */
DECL|macro|EF_LCOL
mdefine_line|#define EF_LCOL&t;&t;0x0010&t;/* Late Collision */
DECL|macro|EF_LCAR
mdefine_line|#define EF_LCAR&t;&t;0x0008&t;/* Loss of Carrier */
DECL|macro|EF_RTRY
mdefine_line|#define EF_RTRY&t;&t;0x0004&t;/* Retry Error */
DECL|macro|EF_TDR
mdefine_line|#define EF_TDR&t;&t;0xff03&t;/* Time Domain Reflectometry */
multiline_comment|/*&n;     *&t;MC68230 Parallel Interface/Timer&n;     */
DECL|struct|MC68230
r_struct
id|MC68230
(brace
DECL|member|PGCR
r_volatile
id|u_char
id|PGCR
suffix:semicolon
multiline_comment|/* Port General Control Register */
DECL|member|Pad1
id|u_char
id|Pad1
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|PSRR
r_volatile
id|u_char
id|PSRR
suffix:semicolon
multiline_comment|/* Port Service Request Register */
DECL|member|Pad2
id|u_char
id|Pad2
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|PADDR
r_volatile
id|u_char
id|PADDR
suffix:semicolon
multiline_comment|/* Port A Data Direction Register */
DECL|member|Pad3
id|u_char
id|Pad3
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|PBDDR
r_volatile
id|u_char
id|PBDDR
suffix:semicolon
multiline_comment|/* Port B Data Direction Register */
DECL|member|Pad4
id|u_char
id|Pad4
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|PCDDR
r_volatile
id|u_char
id|PCDDR
suffix:semicolon
multiline_comment|/* Port C Data Direction Register */
DECL|member|Pad5
id|u_char
id|Pad5
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|PIVR
r_volatile
id|u_char
id|PIVR
suffix:semicolon
multiline_comment|/* Port Interrupt Vector Register */
DECL|member|Pad6
id|u_char
id|Pad6
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|PACR
r_volatile
id|u_char
id|PACR
suffix:semicolon
multiline_comment|/* Port A Control Register */
DECL|member|Pad7
id|u_char
id|Pad7
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|PBCR
r_volatile
id|u_char
id|PBCR
suffix:semicolon
multiline_comment|/* Port B Control Register */
DECL|member|Pad8
id|u_char
id|Pad8
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|PADR
r_volatile
id|u_char
id|PADR
suffix:semicolon
multiline_comment|/* Port A Data Register */
DECL|member|Pad9
id|u_char
id|Pad9
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|PBDR
r_volatile
id|u_char
id|PBDR
suffix:semicolon
multiline_comment|/* Port B Data Register */
DECL|member|Pad10
id|u_char
id|Pad10
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|PAAR
r_volatile
id|u_char
id|PAAR
suffix:semicolon
multiline_comment|/* Port A Alternate Register */
DECL|member|Pad11
id|u_char
id|Pad11
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|PBAR
r_volatile
id|u_char
id|PBAR
suffix:semicolon
multiline_comment|/* Port B Alternate Register */
DECL|member|Pad12
id|u_char
id|Pad12
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|PCDR
r_volatile
id|u_char
id|PCDR
suffix:semicolon
multiline_comment|/* Port C Data Register */
DECL|member|Pad13
id|u_char
id|Pad13
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|PSR
r_volatile
id|u_char
id|PSR
suffix:semicolon
multiline_comment|/* Port Status Register */
DECL|member|Pad14
id|u_char
id|Pad14
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|TCR
r_volatile
id|u_char
id|TCR
suffix:semicolon
multiline_comment|/* Timer Control Register */
DECL|member|Pad15
id|u_char
id|Pad15
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|TIVR
r_volatile
id|u_char
id|TIVR
suffix:semicolon
multiline_comment|/* Timer Interrupt Vector Register */
DECL|member|Pad16
id|u_char
id|Pad16
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|CPRH
r_volatile
id|u_char
id|CPRH
suffix:semicolon
multiline_comment|/* Counter Preload Register (High) */
DECL|member|Pad17
id|u_char
id|Pad17
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|CPRM
r_volatile
id|u_char
id|CPRM
suffix:semicolon
multiline_comment|/* Counter Preload Register (Mid) */
DECL|member|Pad18
id|u_char
id|Pad18
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|CPRL
r_volatile
id|u_char
id|CPRL
suffix:semicolon
multiline_comment|/* Counter Preload Register (Low) */
DECL|member|Pad19
id|u_char
id|Pad19
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|CNTRH
r_volatile
id|u_char
id|CNTRH
suffix:semicolon
multiline_comment|/* Count Register (High) */
DECL|member|Pad20
id|u_char
id|Pad20
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|CNTRM
r_volatile
id|u_char
id|CNTRM
suffix:semicolon
multiline_comment|/* Count Register (Mid) */
DECL|member|Pad21
id|u_char
id|Pad21
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|CNTRL
r_volatile
id|u_char
id|CNTRL
suffix:semicolon
multiline_comment|/* Count Register (Low) */
DECL|member|Pad22
id|u_char
id|Pad22
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|TSR
r_volatile
id|u_char
id|TSR
suffix:semicolon
multiline_comment|/* Timer Status Register */
DECL|member|Pad23
id|u_char
id|Pad23
(braket
l_int|11
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;     *&t;Ariadne Expansion Board Structure&n;     */
DECL|macro|ARIADNE_LANCE
mdefine_line|#define ARIADNE_LANCE&t;&t;0x360
DECL|macro|ARIADNE_PIT
mdefine_line|#define ARIADNE_PIT&t;&t;0x1000
DECL|macro|ARIADNE_BOOTPROM
mdefine_line|#define ARIADNE_BOOTPROM&t;0x4000&t;/* I guess it&squot;s here :-) */
DECL|macro|ARIADNE_BOOTPROM_SIZE
mdefine_line|#define ARIADNE_BOOTPROM_SIZE&t;0x4000
DECL|macro|ARIADNE_RAM
mdefine_line|#define ARIADNE_RAM&t;&t;0x8000&t;/* Always access WORDs!! */
DECL|macro|ARIADNE_RAM_SIZE
mdefine_line|#define ARIADNE_RAM_SIZE&t;0x8000
eof
