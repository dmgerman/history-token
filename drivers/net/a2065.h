multiline_comment|/*&n; * Amiga Linux/68k A2065 Ethernet Driver&n; *&n; * (C) Copyright 1995 by Geert Uytterhoeven &lt;geert@linux-m68k.org&gt;&n; *&n; * ---------------------------------------------------------------------------&n; *&n; * This program is based on&n; *&n; *&t;ariadne.?:&t;Amiga Linux/68k Ariadne Ethernet Driver&n; *&t;&t;&t;(C) Copyright 1995 by Geert Uytterhoeven,&n; *&t;&t;&t;Peter De Schrijver&n; *&n; *&t;lance.c:&t;An AMD LANCE ethernet driver for linux.&n; *&t;&t;&t;Written 1993-94 by Donald Becker.&n; *&n; *&t;Am79C960:&t;PCnet(tm)-ISA Single-Chip Ethernet Controller&n; *&t;&t;&t;Advanced Micro Devices&n; *&t;&t;&t;Publication #16907, Rev. B, Amendment/0, May 1994&n; *&n; * ---------------------------------------------------------------------------&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of the Linux&n; * distribution for more details.&n; *&n; * ---------------------------------------------------------------------------&n; *&n; * The A2065 is a Zorro-II board made by Commodore/Ameristar. It contains:&n; *&n; *&t;- an Am7990 Local Area Network Controller for Ethernet (LANCE) with&n; *&t;  both 10BASE-2 (thin coax) and AUI (DB-15) connectors&n; */
multiline_comment|/*&n; *&t;&t;Am7990 Local Area Network Controller for Ethernet (LANCE)&n; */
DECL|struct|lance_regs
r_struct
id|lance_regs
(brace
DECL|member|rdp
r_int
r_int
id|rdp
suffix:semicolon
multiline_comment|/* Register Data Port */
DECL|member|rap
r_int
r_int
id|rap
suffix:semicolon
multiline_comment|/* Register Address Port */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;&t;Am7990 Control and Status Registers&n; */
DECL|macro|LE_CSR0
mdefine_line|#define LE_CSR0&t;&t;0x0000&t;&t;/* LANCE Controller Status */
DECL|macro|LE_CSR1
mdefine_line|#define LE_CSR1&t;&t;0x0001&t;&t;/* IADR[15:0] */
DECL|macro|LE_CSR2
mdefine_line|#define LE_CSR2&t;&t;0x0002&t;&t;/* IADR[23:16] */
DECL|macro|LE_CSR3
mdefine_line|#define LE_CSR3&t;&t;0x0003&t;&t;/* Misc */
multiline_comment|/*&n; *&t;&t;Bit definitions for CSR0 (LANCE Controller Status)&n; */
DECL|macro|LE_C0_ERR
mdefine_line|#define LE_C0_ERR&t;0x8000&t;&t;/* Error */
DECL|macro|LE_C0_BABL
mdefine_line|#define LE_C0_BABL&t;0x4000&t;&t;/* Babble: Transmitted too many bits */
DECL|macro|LE_C0_CERR
mdefine_line|#define LE_C0_CERR&t;0x2000&t;&t;/* No Heartbeat (10BASE-T) */
DECL|macro|LE_C0_MISS
mdefine_line|#define LE_C0_MISS&t;0x1000&t;&t;/* Missed Frame */
DECL|macro|LE_C0_MERR
mdefine_line|#define LE_C0_MERR&t;0x0800&t;&t;/* Memory Error */
DECL|macro|LE_C0_RINT
mdefine_line|#define LE_C0_RINT&t;0x0400&t;&t;/* Receive Interrupt */
DECL|macro|LE_C0_TINT
mdefine_line|#define LE_C0_TINT&t;0x0200&t;&t;/* Transmit Interrupt */
DECL|macro|LE_C0_IDON
mdefine_line|#define LE_C0_IDON&t;0x0100&t;&t;/* Initialization Done */
DECL|macro|LE_C0_INTR
mdefine_line|#define LE_C0_INTR&t;0x0080&t;&t;/* Interrupt Flag */
DECL|macro|LE_C0_INEA
mdefine_line|#define LE_C0_INEA&t;0x0040&t;&t;/* Interrupt Enable */
DECL|macro|LE_C0_RXON
mdefine_line|#define LE_C0_RXON&t;0x0020&t;&t;/* Receive On */
DECL|macro|LE_C0_TXON
mdefine_line|#define LE_C0_TXON&t;0x0010&t;&t;/* Transmit On */
DECL|macro|LE_C0_TDMD
mdefine_line|#define LE_C0_TDMD&t;0x0008&t;&t;/* Transmit Demand */
DECL|macro|LE_C0_STOP
mdefine_line|#define LE_C0_STOP&t;0x0004&t;&t;/* Stop */
DECL|macro|LE_C0_STRT
mdefine_line|#define LE_C0_STRT&t;0x0002&t;&t;/* Start */
DECL|macro|LE_C0_INIT
mdefine_line|#define LE_C0_INIT&t;0x0001&t;&t;/* Initialize */
multiline_comment|/*&n; *&t;&t;Bit definitions for CSR3&n; */
DECL|macro|LE_C3_BSWP
mdefine_line|#define LE_C3_BSWP&t;0x0004&t;&t;/* Byte Swap&n;&t;&t;&t;&t;&t;   (on for big endian byte order) */
DECL|macro|LE_C3_ACON
mdefine_line|#define LE_C3_ACON&t;0x0002&t;&t;/* ALE Control&n;&t;&t;&t;&t;&t;   (on for active low ALE) */
DECL|macro|LE_C3_BCON
mdefine_line|#define LE_C3_BCON&t;0x0001&t;&t;/* Byte Control */
multiline_comment|/*&n; *&t;&t;Mode Flags&n; */
DECL|macro|LE_MO_PROM
mdefine_line|#define LE_MO_PROM&t;0x8000&t;&t;/* Promiscuous Mode */
DECL|macro|LE_MO_INTL
mdefine_line|#define LE_MO_INTL&t;0x0040&t;&t;/* Internal Loopback */
DECL|macro|LE_MO_DRTY
mdefine_line|#define LE_MO_DRTY&t;0x0020&t;&t;/* Disable Retry */
DECL|macro|LE_MO_FCOLL
mdefine_line|#define LE_MO_FCOLL&t;0x0010&t;&t;/* Force Collision */
DECL|macro|LE_MO_DXMTFCS
mdefine_line|#define LE_MO_DXMTFCS&t;0x0008&t;&t;/* Disable Transmit CRC */
DECL|macro|LE_MO_LOOP
mdefine_line|#define LE_MO_LOOP&t;0x0004&t;&t;/* Loopback Enable */
DECL|macro|LE_MO_DTX
mdefine_line|#define LE_MO_DTX&t;0x0002&t;&t;/* Disable Transmitter */
DECL|macro|LE_MO_DRX
mdefine_line|#define LE_MO_DRX&t;0x0001&t;&t;/* Disable Receiver */
DECL|struct|lance_rx_desc
r_struct
id|lance_rx_desc
(brace
DECL|member|rmd0
r_int
r_int
id|rmd0
suffix:semicolon
multiline_comment|/* low address of packet */
DECL|member|rmd1_bits
r_int
r_char
id|rmd1_bits
suffix:semicolon
multiline_comment|/* descriptor bits */
DECL|member|rmd1_hadr
r_int
r_char
id|rmd1_hadr
suffix:semicolon
multiline_comment|/* high address of packet */
DECL|member|length
r_int
id|length
suffix:semicolon
multiline_comment|/* This length is 2s complement (negative)!&n;&t;&t;&t;&t;     * Buffer length&n;&t;&t;&t;&t;     */
DECL|member|mblength
r_int
r_int
id|mblength
suffix:semicolon
multiline_comment|/* Aactual number of bytes received */
)brace
suffix:semicolon
DECL|struct|lance_tx_desc
r_struct
id|lance_tx_desc
(brace
DECL|member|tmd0
r_int
r_int
id|tmd0
suffix:semicolon
multiline_comment|/* low address of packet */
DECL|member|tmd1_bits
r_int
r_char
id|tmd1_bits
suffix:semicolon
multiline_comment|/* descriptor bits */
DECL|member|tmd1_hadr
r_int
r_char
id|tmd1_hadr
suffix:semicolon
multiline_comment|/* high address of packet */
DECL|member|length
r_int
id|length
suffix:semicolon
multiline_comment|/* Length is 2s complement (negative)! */
DECL|member|misc
r_int
r_int
id|misc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;&t;Receive Flags&n; */
DECL|macro|LE_R1_OWN
mdefine_line|#define LE_R1_OWN&t;0x80&t;&t;/* LANCE owns the descriptor */
DECL|macro|LE_R1_ERR
mdefine_line|#define LE_R1_ERR&t;0x40&t;&t;/* Error */
DECL|macro|LE_R1_FRA
mdefine_line|#define LE_R1_FRA&t;0x20&t;&t;/* Framing Error */
DECL|macro|LE_R1_OFL
mdefine_line|#define LE_R1_OFL&t;0x10&t;&t;/* Overflow Error */
DECL|macro|LE_R1_CRC
mdefine_line|#define LE_R1_CRC&t;0x08&t;&t;/* CRC Error */
DECL|macro|LE_R1_BUF
mdefine_line|#define LE_R1_BUF&t;0x04&t;&t;/* Buffer Error */
DECL|macro|LE_R1_SOP
mdefine_line|#define LE_R1_SOP&t;0x02&t;&t;/* Start of Packet */
DECL|macro|LE_R1_EOP
mdefine_line|#define LE_R1_EOP&t;0x01&t;&t;/* End of Packet */
DECL|macro|LE_R1_POK
mdefine_line|#define LE_R1_POK       0x03&t;&t;/* Packet is complete: SOP + EOP */
multiline_comment|/*&n; *&t;&t;Transmit Flags&n; */
DECL|macro|LE_T1_OWN
mdefine_line|#define LE_T1_OWN&t;0x80&t;&t;/* LANCE owns the descriptor */
DECL|macro|LE_T1_ERR
mdefine_line|#define LE_T1_ERR&t;0x40&t;&t;/* Error */
DECL|macro|LE_T1_RES
mdefine_line|#define LE_T1_RES&t;0x20&t;&t;/* Reserved,&n;&t;&t;&t;&t;&t;   LANCE writes this with a zero */
DECL|macro|LE_T1_EMORE
mdefine_line|#define LE_T1_EMORE&t;0x10&t;&t;/* More than one retry needed */
DECL|macro|LE_T1_EONE
mdefine_line|#define LE_T1_EONE&t;0x08&t;&t;/* One retry needed */
DECL|macro|LE_T1_EDEF
mdefine_line|#define LE_T1_EDEF&t;0x04&t;&t;/* Deferred */
DECL|macro|LE_T1_SOP
mdefine_line|#define LE_T1_SOP&t;0x02&t;&t;/* Start of Packet */
DECL|macro|LE_T1_EOP
mdefine_line|#define LE_T1_EOP&t;0x01&t;&t;/* End of Packet */
DECL|macro|LE_T1_POK
mdefine_line|#define LE_T1_POK&t;0x03&t;&t;/* Packet is complete: SOP + EOP */
multiline_comment|/*&n; *&t;&t;Error Flags&n; */
DECL|macro|LE_T3_BUF
mdefine_line|#define LE_T3_BUF &t;0x8000&t;&t;/* Buffer Error */
DECL|macro|LE_T3_UFL
mdefine_line|#define LE_T3_UFL &t;0x4000&t;&t;/* Underflow Error */
DECL|macro|LE_T3_LCOL
mdefine_line|#define LE_T3_LCOL &t;0x1000&t;&t;/* Late Collision */
DECL|macro|LE_T3_CLOS
mdefine_line|#define LE_T3_CLOS &t;0x0800&t;&t;/* Loss of Carrier */
DECL|macro|LE_T3_RTY
mdefine_line|#define LE_T3_RTY &t;0x0400&t;&t;/* Retry Error */
DECL|macro|LE_T3_TDR
mdefine_line|#define LE_T3_TDR&t;0x03ff&t;&t;/* Time Domain Reflectometry */
multiline_comment|/*&n; *&t;&t;A2065 Expansion Board Structure&n; */
DECL|macro|A2065_LANCE
mdefine_line|#define A2065_LANCE&t;&t;0x4000
DECL|macro|A2065_RAM
mdefine_line|#define A2065_RAM&t;&t;0x8000
DECL|macro|A2065_RAM_SIZE
mdefine_line|#define A2065_RAM_SIZE&t;&t;0x8000
eof
