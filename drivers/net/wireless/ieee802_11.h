macro_line|#ifndef _IEEE802_11_H
DECL|macro|_IEEE802_11_H
mdefine_line|#define _IEEE802_11_H
DECL|macro|IEEE802_11_DATA_LEN
mdefine_line|#define IEEE802_11_DATA_LEN&t;&t;2304
multiline_comment|/* Actually, the standard seems to be inconsistent about what the&n;   maximum frame size really is.  S6.2.1.1.2 says 2304 octets, but the&n;   figure in section 7.1.2 says 2312 octects. */
DECL|macro|IEEE802_11_HLEN
mdefine_line|#define IEEE802_11_HLEN&t;&t;&t;30
DECL|macro|IEEE802_11_FRAME_LEN
mdefine_line|#define IEEE802_11_FRAME_LEN&t;&t;(IEEE802_11_DATA_LEN + IEEE802_11_HLEN)
DECL|struct|ieee802_11_hdr
r_struct
id|ieee802_11_hdr
(brace
DECL|member|frame_ctl
id|u16
id|frame_ctl
suffix:semicolon
DECL|member|duration_id
id|u16
id|duration_id
suffix:semicolon
DECL|member|addr1
id|u8
id|addr1
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|addr2
id|u8
id|addr2
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|addr3
id|u8
id|addr3
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|seq_ctl
id|u16
id|seq_ctl
suffix:semicolon
DECL|member|addr4
id|u8
id|addr4
(braket
id|ETH_ALEN
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
multiline_comment|/* Frame control field constants */
DECL|macro|IEEE802_11_FCTL_VERS
mdefine_line|#define IEEE802_11_FCTL_VERS&t;&t;0x0002
DECL|macro|IEEE802_11_FCTL_FTYPE
mdefine_line|#define IEEE802_11_FCTL_FTYPE&t;&t;0x000c
DECL|macro|IEEE802_11_FCTL_STYPE
mdefine_line|#define IEEE802_11_FCTL_STYPE&t;&t;0x00f0
DECL|macro|IEEE802_11_FCTL_TODS
mdefine_line|#define IEEE802_11_FCTL_TODS&t;&t;0x0100
DECL|macro|IEEE802_11_FCTL_FROMDS
mdefine_line|#define IEEE802_11_FCTL_FROMDS&t;&t;0x0200
DECL|macro|IEEE802_11_FCTL_MOREFRAGS
mdefine_line|#define IEEE802_11_FCTL_MOREFRAGS&t;0x0400
DECL|macro|IEEE802_11_FCTL_RETRY
mdefine_line|#define IEEE802_11_FCTL_RETRY&t;&t;0x0800
DECL|macro|IEEE802_11_FCTL_PM
mdefine_line|#define IEEE802_11_FCTL_PM&t;&t;0x1000
DECL|macro|IEEE802_11_FCTL_MOREDATA
mdefine_line|#define IEEE802_11_FCTL_MOREDATA&t;0x2000
DECL|macro|IEEE802_11_FCTL_WEP
mdefine_line|#define IEEE802_11_FCTL_WEP&t;&t;0x4000
DECL|macro|IEEE802_11_FCTL_ORDER
mdefine_line|#define IEEE802_11_FCTL_ORDER&t;&t;0x8000
DECL|macro|IEEE802_11_FTYPE_MGMT
mdefine_line|#define IEEE802_11_FTYPE_MGMT&t;&t;0x0000
DECL|macro|IEEE802_11_FTYPE_CTL
mdefine_line|#define IEEE802_11_FTYPE_CTL&t;&t;0x0004
DECL|macro|IEEE802_11_FTYPE_DATA
mdefine_line|#define IEEE802_11_FTYPE_DATA&t;&t;0x0008
multiline_comment|/* management */
DECL|macro|IEEE802_11_STYPE_ASSOC_REQ
mdefine_line|#define IEEE802_11_STYPE_ASSOC_REQ&t;0x0000
DECL|macro|IEEE802_11_STYPE_ASSOC_RESP
mdefine_line|#define IEEE802_11_STYPE_ASSOC_RESP &t;0x0010
DECL|macro|IEEE802_11_STYPE_REASSOC_REQ
mdefine_line|#define IEEE802_11_STYPE_REASSOC_REQ&t;0x0020
DECL|macro|IEEE802_11_STYPE_REASSOC_RESP
mdefine_line|#define IEEE802_11_STYPE_REASSOC_RESP&t;0x0030
DECL|macro|IEEE802_11_STYPE_PROBE_REQ
mdefine_line|#define IEEE802_11_STYPE_PROBE_REQ&t;0x0040
DECL|macro|IEEE802_11_STYPE_PROBE_RESP
mdefine_line|#define IEEE802_11_STYPE_PROBE_RESP&t;0x0050
DECL|macro|IEEE802_11_STYPE_BEACON
mdefine_line|#define IEEE802_11_STYPE_BEACON&t;&t;0x0080
DECL|macro|IEEE802_11_STYPE_ATIM
mdefine_line|#define IEEE802_11_STYPE_ATIM&t;&t;0x0090
DECL|macro|IEEE802_11_STYPE_DISASSOC
mdefine_line|#define IEEE802_11_STYPE_DISASSOC&t;0x00A0
DECL|macro|IEEE802_11_STYPE_AUTH
mdefine_line|#define IEEE802_11_STYPE_AUTH&t;&t;0x00B0
DECL|macro|IEEE802_11_STYPE_DEAUTH
mdefine_line|#define IEEE802_11_STYPE_DEAUTH&t;&t;0x00C0
multiline_comment|/* control */
DECL|macro|IEEE802_11_STYPE_PSPOLL
mdefine_line|#define IEEE802_11_STYPE_PSPOLL&t;&t;0x00A0
DECL|macro|IEEE802_11_STYPE_RTS
mdefine_line|#define IEEE802_11_STYPE_RTS&t;&t;0x00B0
DECL|macro|IEEE802_11_STYPE_CTS
mdefine_line|#define IEEE802_11_STYPE_CTS&t;&t;0x00C0
DECL|macro|IEEE802_11_STYPE_ACK
mdefine_line|#define IEEE802_11_STYPE_ACK&t;&t;0x00D0
DECL|macro|IEEE802_11_STYPE_CFEND
mdefine_line|#define IEEE802_11_STYPE_CFEND&t;&t;0x00E0
DECL|macro|IEEE802_11_STYPE_CFENDACK
mdefine_line|#define IEEE802_11_STYPE_CFENDACK&t;0x00F0
multiline_comment|/* data */
DECL|macro|IEEE802_11_STYPE_DATA
mdefine_line|#define IEEE802_11_STYPE_DATA&t;&t;0x0000
DECL|macro|IEEE802_11_STYPE_DATA_CFACK
mdefine_line|#define IEEE802_11_STYPE_DATA_CFACK&t;0x0010
DECL|macro|IEEE802_11_STYPE_DATA_CFPOLL
mdefine_line|#define IEEE802_11_STYPE_DATA_CFPOLL&t;0x0020
DECL|macro|IEEE802_11_STYPE_DATA_CFACKPOLL
mdefine_line|#define IEEE802_11_STYPE_DATA_CFACKPOLL&t;0x0030
DECL|macro|IEEE802_11_STYPE_NULLFUNC
mdefine_line|#define IEEE802_11_STYPE_NULLFUNC&t;0x0040
DECL|macro|IEEE802_11_STYPE_CFACK
mdefine_line|#define IEEE802_11_STYPE_CFACK&t;&t;0x0050
DECL|macro|IEEE802_11_STYPE_CFPOLL
mdefine_line|#define IEEE802_11_STYPE_CFPOLL&t;&t;0x0060
DECL|macro|IEEE802_11_STYPE_CFACKPOLL
mdefine_line|#define IEEE802_11_STYPE_CFACKPOLL&t;0x0070
DECL|macro|IEEE802_11_SCTL_FRAG
mdefine_line|#define IEEE802_11_SCTL_FRAG&t;&t;0x000F
DECL|macro|IEEE802_11_SCTL_SEQ
mdefine_line|#define IEEE802_11_SCTL_SEQ&t;&t;0xFFF0
macro_line|#endif /* _IEEE802_11_H */
eof
