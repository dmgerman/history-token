multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Global definitions for the HIPPI interface.&n; *&n; * Version:&t;@(#)if_hippi.h&t;1.0.0&t;05/26/97&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Donald Becker, &lt;becker@super.org&gt;&n; *&t;&t;Alan Cox, &lt;alan@redhat.com&gt;&n; *&t;&t;Steve Whitehouse, &lt;gw7rrm@eeshack3.swan.ac.uk&gt;&n; *&t;&t;Jes Sorensen, &lt;Jes.Sorensen@cern.ch&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_IF_HIPPI_H
DECL|macro|_LINUX_IF_HIPPI_H
mdefine_line|#define _LINUX_IF_HIPPI_H
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/*&n; *&t;HIPPI magic constants.&n; */
DECL|macro|HIPPI_ALEN
mdefine_line|#define HIPPI_ALEN&t;6&t;&t;/* Bytes in one HIPPI hw-addr&t;   */
DECL|macro|HIPPI_HLEN
mdefine_line|#define HIPPI_HLEN&t;sizeof(struct hippi_hdr)
DECL|macro|HIPPI_ZLEN
mdefine_line|#define HIPPI_ZLEN&t;0&t;&t;/* Min. bytes in frame without FCS */
DECL|macro|HIPPI_DATA_LEN
mdefine_line|#define HIPPI_DATA_LEN&t;65280&t;&t;/* Max. bytes in payload&t;   */
DECL|macro|HIPPI_FRAME_LEN
mdefine_line|#define HIPPI_FRAME_LEN&t;(HIPPI_DATA_LEN + HIPPI_HLEN)
multiline_comment|/* Max. bytes in frame without FCS */
multiline_comment|/*&n; * Define LLC and SNAP constants.&n; */
DECL|macro|HIPPI_EXTENDED_SAP
mdefine_line|#define HIPPI_EXTENDED_SAP&t;0xAA
DECL|macro|HIPPI_UI_CMD
mdefine_line|#define HIPPI_UI_CMD&t;&t;0x03
multiline_comment|/*&n; *&t;Do we need to list some sort of ID&squot;s here?&n; */
multiline_comment|/*&n; *&t;HIPPI statistics collection data. &n; */
DECL|struct|hipnet_statistics
r_struct
id|hipnet_statistics
(brace
DECL|member|rx_packets
r_int
id|rx_packets
suffix:semicolon
multiline_comment|/* total packets received&t;*/
DECL|member|tx_packets
r_int
id|tx_packets
suffix:semicolon
multiline_comment|/* total packets transmitted&t;*/
DECL|member|rx_errors
r_int
id|rx_errors
suffix:semicolon
multiline_comment|/* bad packets received&t;&t;*/
DECL|member|tx_errors
r_int
id|tx_errors
suffix:semicolon
multiline_comment|/* packet transmit problems&t;*/
DECL|member|rx_dropped
r_int
id|rx_dropped
suffix:semicolon
multiline_comment|/* no space in linux buffers&t;*/
DECL|member|tx_dropped
r_int
id|tx_dropped
suffix:semicolon
multiline_comment|/* no space available in linux&t;*/
multiline_comment|/* detailed rx_errors: */
DECL|member|rx_length_errors
r_int
id|rx_length_errors
suffix:semicolon
DECL|member|rx_over_errors
r_int
id|rx_over_errors
suffix:semicolon
multiline_comment|/* receiver ring buff overflow&t;*/
DECL|member|rx_crc_errors
r_int
id|rx_crc_errors
suffix:semicolon
multiline_comment|/* recved pkt with crc error&t;*/
DECL|member|rx_frame_errors
r_int
id|rx_frame_errors
suffix:semicolon
multiline_comment|/* recv&squot;d frame alignment error */
DECL|member|rx_fifo_errors
r_int
id|rx_fifo_errors
suffix:semicolon
multiline_comment|/* recv&squot;r fifo overrun&t;&t;*/
DECL|member|rx_missed_errors
r_int
id|rx_missed_errors
suffix:semicolon
multiline_comment|/* receiver missed packet&t;*/
multiline_comment|/* detailed tx_errors */
DECL|member|tx_aborted_errors
r_int
id|tx_aborted_errors
suffix:semicolon
DECL|member|tx_carrier_errors
r_int
id|tx_carrier_errors
suffix:semicolon
DECL|member|tx_fifo_errors
r_int
id|tx_fifo_errors
suffix:semicolon
DECL|member|tx_heartbeat_errors
r_int
id|tx_heartbeat_errors
suffix:semicolon
DECL|member|tx_window_errors
r_int
id|tx_window_errors
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hippi_fp_hdr
r_struct
id|hippi_fp_hdr
(brace
macro_line|#if 0
id|__u8
id|ulp
suffix:semicolon
multiline_comment|/* must contain 4 */
macro_line|#if defined (__BIG_ENDIAN_BITFIELD)
id|__u8
id|d1_data_present
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* must be 1 */
id|__u8
id|start_d2_burst_boundary
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* must be zero */
id|__u8
id|reserved
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* must be zero */
macro_line|#if 0
id|__u16
id|reserved1
suffix:colon
l_int|5
suffix:semicolon
id|__u16
id|d1_area_size
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* must be 3 */
id|__u16
id|d2_offset
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* must be zero */
macro_line|#endif
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
id|__u8
id|reserved
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* must be zero */
id|__u8
id|start_d2_burst_boundary
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* must be zero */
id|__u8
id|d1_data_present
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* must be 1 */
macro_line|#if 0
id|__u16
id|d2_offset
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* must be zero */
id|__u16
id|d1_area_size
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* must be 3 */
id|__u16
id|reserved1
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* must be zero */
macro_line|#endif
macro_line|#else
macro_line|#error&t;&quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
macro_line|#else
DECL|member|fixed
id|__u32
id|fixed
suffix:semicolon
macro_line|#endif
DECL|member|d2_size
id|__u32
id|d2_size
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|hippi_le_hdr
r_struct
id|hippi_le_hdr
(brace
macro_line|#if defined (__BIG_ENDIAN_BITFIELD)
DECL|member|fc
r_int
r_int
id|fc
suffix:colon
l_int|3
suffix:semicolon
DECL|member|double_wide
r_int
r_int
id|double_wide
suffix:colon
l_int|1
suffix:semicolon
DECL|member|message_type
r_int
r_int
id|message_type
suffix:colon
l_int|4
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
r_int
r_int
id|message_type
suffix:colon
l_int|4
suffix:semicolon
r_int
r_int
id|double_wide
suffix:colon
l_int|1
suffix:semicolon
r_int
r_int
id|fc
suffix:colon
l_int|3
suffix:semicolon
macro_line|#endif
DECL|member|dest_switch_addr
id|__u8
id|dest_switch_addr
(braket
l_int|3
)braket
suffix:semicolon
macro_line|#if defined (__BIG_ENDIAN_BITFIELD)
DECL|member|dest_addr_type
id|__u8
id|dest_addr_type
suffix:colon
l_int|4
comma
DECL|member|src_addr_type
id|src_addr_type
suffix:colon
l_int|4
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|src_addr_type
id|__u8
id|src_addr_type
suffix:colon
l_int|4
comma
DECL|member|dest_addr_type
id|dest_addr_type
suffix:colon
l_int|4
suffix:semicolon
macro_line|#endif
DECL|member|src_switch_addr
id|__u8
id|src_switch_addr
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|reserved
id|__u16
id|reserved
suffix:semicolon
DECL|member|daddr
id|__u8
id|daddr
(braket
id|HIPPI_ALEN
)braket
suffix:semicolon
DECL|member|locally_administered
id|__u16
id|locally_administered
suffix:semicolon
DECL|member|saddr
id|__u8
id|saddr
(braket
id|HIPPI_ALEN
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|HIPPI_OUI_LEN
mdefine_line|#define HIPPI_OUI_LEN&t;3
multiline_comment|/*&n; * Looks like the dsap and ssap fields have been swapped by mistake in&n; * RFC 2067 &quot;IP over HIPPI&quot;.&n; */
DECL|struct|hippi_snap_hdr
r_struct
id|hippi_snap_hdr
(brace
DECL|member|dsap
id|__u8
id|dsap
suffix:semicolon
multiline_comment|/* always 0xAA */
DECL|member|ssap
id|__u8
id|ssap
suffix:semicolon
multiline_comment|/* always 0xAA */
DECL|member|ctrl
id|__u8
id|ctrl
suffix:semicolon
multiline_comment|/* always 0x03 */
DECL|member|oui
id|__u8
id|oui
(braket
id|HIPPI_OUI_LEN
)braket
suffix:semicolon
multiline_comment|/* organizational universal id (zero)*/
DECL|member|ethertype
id|__u16
id|ethertype
suffix:semicolon
multiline_comment|/* packet type ID field */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|hippi_hdr
r_struct
id|hippi_hdr
(brace
DECL|member|fp
r_struct
id|hippi_fp_hdr
id|fp
suffix:semicolon
DECL|member|le
r_struct
id|hippi_le_hdr
id|le
suffix:semicolon
DECL|member|snap
r_struct
id|hippi_snap_hdr
id|snap
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#endif&t;/* _LINUX_IF_HIPPI_H */
eof
