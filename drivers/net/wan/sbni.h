multiline_comment|/* sbni.h:  definitions for a Granch SBNI12 driver, version 5.0.0&n; * Written 2001 Denis I.Timofeev (timofeev@granch.ru)&n; * This file is distributed under the GNU GPL&n; */
macro_line|#ifndef SBNI_H
DECL|macro|SBNI_H
mdefine_line|#define SBNI_H
macro_line|#if SBNI_DEBUG
DECL|macro|DP
mdefine_line|#define DP( A ) A
macro_line|#else
DECL|macro|DP
mdefine_line|#define DP( A )
macro_line|#endif
multiline_comment|/* We don&squot;t have official vendor id yet... */
DECL|macro|SBNI_PCI_VENDOR
mdefine_line|#define SBNI_PCI_VENDOR &t;0x55 
DECL|macro|SBNI_PCI_DEVICE
mdefine_line|#define SBNI_PCI_DEVICE &t;0x9f
DECL|macro|ISA_MODE
mdefine_line|#define ISA_MODE 0x00
DECL|macro|PCI_MODE
mdefine_line|#define PCI_MODE 0x01
DECL|macro|SBNI_IO_EXTENT
mdefine_line|#define&t;SBNI_IO_EXTENT&t;4
DECL|enum|sbni_reg
r_enum
id|sbni_reg
(brace
DECL|enumerator|CSR0
id|CSR0
op_assign
l_int|0
comma
DECL|enumerator|CSR1
id|CSR1
op_assign
l_int|1
comma
DECL|enumerator|DAT
id|DAT
op_assign
l_int|2
)brace
suffix:semicolon
multiline_comment|/* CSR0 mapping */
r_enum
(brace
DECL|enumerator|BU_EMP
id|BU_EMP
op_assign
l_int|0x02
comma
DECL|enumerator|RC_CHK
id|RC_CHK
op_assign
l_int|0x04
comma
DECL|enumerator|CT_ZER
id|CT_ZER
op_assign
l_int|0x08
comma
DECL|enumerator|TR_REQ
id|TR_REQ
op_assign
l_int|0x10
comma
DECL|enumerator|TR_RDY
id|TR_RDY
op_assign
l_int|0x20
comma
DECL|enumerator|EN_INT
id|EN_INT
op_assign
l_int|0x40
comma
DECL|enumerator|RC_RDY
id|RC_RDY
op_assign
l_int|0x80
)brace
suffix:semicolon
multiline_comment|/* CSR1 mapping */
DECL|macro|PR_RES
mdefine_line|#define PR_RES 0x80
DECL|struct|sbni_csr1
r_struct
id|sbni_csr1
(brace
DECL|member|rxl
r_int
id|rxl
suffix:colon
l_int|5
suffix:semicolon
DECL|member|rate
r_int
id|rate
suffix:colon
l_int|2
suffix:semicolon
r_int
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* fields in frame header */
DECL|macro|FRAME_ACK_MASK
mdefine_line|#define FRAME_ACK_MASK  (unsigned short)0x7000
DECL|macro|FRAME_LEN_MASK
mdefine_line|#define FRAME_LEN_MASK  (unsigned short)0x03FF
DECL|macro|FRAME_FIRST
mdefine_line|#define FRAME_FIRST     (unsigned short)0x8000
DECL|macro|FRAME_RETRY
mdefine_line|#define FRAME_RETRY     (unsigned short)0x0800
DECL|macro|FRAME_SENT_BAD
mdefine_line|#define FRAME_SENT_BAD  (unsigned short)0x4000
DECL|macro|FRAME_SENT_OK
mdefine_line|#define FRAME_SENT_OK   (unsigned short)0x3000
multiline_comment|/* state flags */
r_enum
(brace
DECL|enumerator|FL_WAIT_ACK
id|FL_WAIT_ACK
op_assign
l_int|0x01
comma
DECL|enumerator|FL_NEED_RESEND
id|FL_NEED_RESEND
op_assign
l_int|0x02
comma
DECL|enumerator|FL_PREV_OK
id|FL_PREV_OK
op_assign
l_int|0x04
comma
DECL|enumerator|FL_SLOW_MODE
id|FL_SLOW_MODE
op_assign
l_int|0x08
comma
DECL|enumerator|FL_SECONDARY
id|FL_SECONDARY
op_assign
l_int|0x10
comma
macro_line|#ifdef CONFIG_SBNI_MULTILINE
DECL|enumerator|FL_SLAVE
id|FL_SLAVE
op_assign
l_int|0x20
comma
macro_line|#endif
DECL|enumerator|FL_LINE_DOWN
id|FL_LINE_DOWN
op_assign
l_int|0x40
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|DEFAULT_IOBASEADDR
id|DEFAULT_IOBASEADDR
op_assign
l_int|0x210
comma
DECL|enumerator|DEFAULT_INTERRUPTNUMBER
id|DEFAULT_INTERRUPTNUMBER
op_assign
l_int|5
comma
DECL|enumerator|DEFAULT_RATE
id|DEFAULT_RATE
op_assign
l_int|0
comma
DECL|enumerator|DEFAULT_FRAME_LEN
id|DEFAULT_FRAME_LEN
op_assign
l_int|1012
)brace
suffix:semicolon
DECL|macro|DEF_RXL_DELTA
mdefine_line|#define DEF_RXL_DELTA&t;-1
DECL|macro|DEF_RXL
mdefine_line|#define DEF_RXL&t;&t;0xf
DECL|macro|SBNI_SIG
mdefine_line|#define SBNI_SIG 0x5a
DECL|macro|SBNI_MIN_LEN
mdefine_line|#define&t;SBNI_MIN_LEN&t;60&t;/* Shortest Ethernet frame without FCS */
DECL|macro|SBNI_MAX_FRAME
mdefine_line|#define SBNI_MAX_FRAME&t;1023
DECL|macro|ETHER_MAX_LEN
mdefine_line|#define ETHER_MAX_LEN&t;1518
DECL|macro|SBNI_TIMEOUT
mdefine_line|#define SBNI_TIMEOUT&t;(HZ/10)
DECL|macro|TR_ERROR_COUNT
mdefine_line|#define TR_ERROR_COUNT&t;32
DECL|macro|CHANGE_LEVEL_START_TICKS
mdefine_line|#define CHANGE_LEVEL_START_TICKS 4
DECL|macro|SBNI_MAX_NUM_CARDS
mdefine_line|#define SBNI_MAX_NUM_CARDS&t;16
multiline_comment|/* internal SBNI-specific statistics */
DECL|struct|sbni_in_stats
r_struct
id|sbni_in_stats
(brace
DECL|member|all_rx_number
id|u32
id|all_rx_number
suffix:semicolon
DECL|member|bad_rx_number
id|u32
id|bad_rx_number
suffix:semicolon
DECL|member|timeout_number
id|u32
id|timeout_number
suffix:semicolon
DECL|member|all_tx_number
id|u32
id|all_tx_number
suffix:semicolon
DECL|member|resend_tx_number
id|u32
id|resend_tx_number
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* SBNI ioctl params */
DECL|macro|SIOCDEVGETINSTATS
mdefine_line|#define SIOCDEVGETINSTATS &t;SIOCDEVPRIVATE
DECL|macro|SIOCDEVRESINSTATS
mdefine_line|#define SIOCDEVRESINSTATS &t;SIOCDEVPRIVATE+1
DECL|macro|SIOCDEVGHWSTATE
mdefine_line|#define SIOCDEVGHWSTATE   &t;SIOCDEVPRIVATE+2
DECL|macro|SIOCDEVSHWSTATE
mdefine_line|#define SIOCDEVSHWSTATE   &t;SIOCDEVPRIVATE+3
DECL|macro|SIOCDEVENSLAVE
mdefine_line|#define SIOCDEVENSLAVE  &t;SIOCDEVPRIVATE+4
DECL|macro|SIOCDEVEMANSIPATE
mdefine_line|#define SIOCDEVEMANSIPATE  &t;SIOCDEVPRIVATE+5
multiline_comment|/* data packet for SIOCDEVGHWSTATE/SIOCDEVSHWSTATE ioctl requests */
DECL|struct|sbni_flags
r_struct
id|sbni_flags
(brace
DECL|member|rxl
id|u32
id|rxl
suffix:colon
l_int|4
suffix:semicolon
DECL|member|rate
id|u32
id|rate
suffix:colon
l_int|2
suffix:semicolon
DECL|member|fixed_rxl
id|u32
id|fixed_rxl
suffix:colon
l_int|1
suffix:semicolon
DECL|member|slow_mode
id|u32
id|slow_mode
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mac_addr
id|u32
id|mac_addr
suffix:colon
l_int|24
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * CRC-32 stuff&n; */
DECL|macro|CRC32
mdefine_line|#define CRC32(c,crc) (crc32tab[((size_t)(crc) ^ (c)) &amp; 0xff] ^ (((crc) &gt;&gt; 8) &amp; 0x00FFFFFF))
multiline_comment|/* CRC generator 0xEDB88320 */
multiline_comment|/* CRC remainder 0x2144DF1C */
multiline_comment|/* CRC initial value 0x00000000 */
DECL|macro|CRC32_REMAINDER
mdefine_line|#define CRC32_REMAINDER 0x2144DF1C
DECL|macro|CRC32_INITIAL
mdefine_line|#define CRC32_INITIAL 0x00000000
macro_line|#ifndef __initdata
DECL|macro|__initdata
mdefine_line|#define __initdata
macro_line|#endif
DECL|macro|min
mdefine_line|#define min( x, y )&t;( (x) &lt; (y)  ?  (x)  :  (y) )
macro_line|#endif
eof
