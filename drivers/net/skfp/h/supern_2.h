multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/*&n;&t;defines for AMD Supernet II chip set&n;&t;the chips are refered to as&n;&t;&t;FPLUS&t;Formac Plus&n;&t;&t;PLC&t;Physical Layer&n;&n;&t;added defines for AMD Supernet III chip set&n;&t;added comments on differences between Supernet II and Supernet III&n;&t;added defines for the Motorola ELM (MOT_ELM)&n;*/
macro_line|#ifndef&t;_SUPERNET_
DECL|macro|_SUPERNET_
mdefine_line|#define _SUPERNET_
multiline_comment|/*&n; * Define Supernet 3 when used&n; */
macro_line|#ifdef&t;PCI
macro_line|#ifndef&t;SUPERNET_3
DECL|macro|SUPERNET_3
mdefine_line|#define&t;SUPERNET_3
macro_line|#endif
DECL|macro|TAG
mdefine_line|#define TAG
macro_line|#endif
DECL|macro|MB
mdefine_line|#define&t;MB&t;0xff
DECL|macro|MW
mdefine_line|#define&t;MW&t;0xffff
DECL|macro|MD
mdefine_line|#define&t;MD&t;0xffffffff
multiline_comment|/*&n; * FORMAC frame status (rx_msext)&n; */
DECL|macro|FS_EI
mdefine_line|#define&t;FS_EI&t;&t;(1&lt;&lt;2)
DECL|macro|FS_AI
mdefine_line|#define&t;FS_AI&t;&t;(1&lt;&lt;1)
DECL|macro|FS_CI
mdefine_line|#define&t;FS_CI&t;&t;(1&lt;&lt;0)
DECL|macro|FS_MSVALID
mdefine_line|#define FS_MSVALID&t;(1&lt;&lt;15)&t;&t;/* end of queue */
DECL|macro|FS_MSRABT
mdefine_line|#define FS_MSRABT&t;(1&lt;&lt;14)&t;&t;/* frame was aborted during reception*/
DECL|macro|FS_SSRCRTG
mdefine_line|#define FS_SSRCRTG&t;(1&lt;&lt;12)&t;&t;/* if SA has set MSB (source-routing)*/
DECL|macro|FS_SEAC2
mdefine_line|#define FS_SEAC2&t;(FS_EI&lt;&lt;9)&t;/* error indicator */
DECL|macro|FS_SEAC1
mdefine_line|#define FS_SEAC1&t;(FS_AI&lt;&lt;9)&t;/* address indicator */
DECL|macro|FS_SEAC0
mdefine_line|#define FS_SEAC0&t;(FS_CI&lt;&lt;9)&t;/* copy indicator */
DECL|macro|FS_SFRMERR
mdefine_line|#define FS_SFRMERR&t;(1&lt;&lt;8)&t;&t;/* error detected (CRC or length) */
DECL|macro|FS_SADRRG
mdefine_line|#define FS_SADRRG&t;(1&lt;&lt;7)&t;&t;/* address recognized */
DECL|macro|FS_SFRMTY2
mdefine_line|#define FS_SFRMTY2&t;(1&lt;&lt;6)&t;&t;/* frame-class bit */
DECL|macro|FS_SFRMTY1
mdefine_line|#define FS_SFRMTY1&t;(1&lt;&lt;5)&t;&t;/* frame-type bit (impementor) */
DECL|macro|FS_SFRMTY0
mdefine_line|#define FS_SFRMTY0&t;(1&lt;&lt;4)&t;&t;/* frame-type bit (LLC) */
DECL|macro|FS_ERFBB1
mdefine_line|#define FS_ERFBB1&t;(1&lt;&lt;1)&t;&t;/* byte offset (depends on LSB bit) */
DECL|macro|FS_ERFBB0
mdefine_line|#define FS_ERFBB0&t;(1&lt;&lt;0)&t;&t;/*  - &quot; - */
multiline_comment|/*&n; * status frame type&n; */
DECL|macro|FRM_SMT
mdefine_line|#define&t;FRM_SMT&t;&t;(0)&t;/* asynchr. frames */
DECL|macro|FRM_LLCA
mdefine_line|#define&t;FRM_LLCA&t;(1)
DECL|macro|FRM_IMPA
mdefine_line|#define&t;FRM_IMPA&t;(2)&t;
DECL|macro|FRM_MAC
mdefine_line|#define&t;FRM_MAC&t;&t;(4)&t;/* synchr. frames */
DECL|macro|FRM_LLCS
mdefine_line|#define&t;FRM_LLCS&t;(5)
DECL|macro|FRM_IMPS
mdefine_line|#define&t;FRM_IMPS&t;(6)
multiline_comment|/*&n; * bits in rx_descr.i&t;(receive frame status word)&n; */
DECL|macro|RX_MSVALID
mdefine_line|#define RX_MSVALID&t;((long)1&lt;&lt;31)&t;/* memory status valid */
DECL|macro|RX_MSRABT
mdefine_line|#define RX_MSRABT&t;((long)1&lt;&lt;30)&t;/* memory status receive abort */
DECL|macro|RX_FS_E
mdefine_line|#define RX_FS_E&t;&t;((long)FS_SEAC2&lt;&lt;16)&t;/* error indicator */
DECL|macro|RX_FS_A
mdefine_line|#define RX_FS_A&t;&t;((long)FS_SEAC1&lt;&lt;16)&t;/* address indicator */
DECL|macro|RX_FS_C
mdefine_line|#define RX_FS_C&t;&t;((long)FS_SEAC0&lt;&lt;16)&t;/* copy indicator */
DECL|macro|RX_FS_CRC
mdefine_line|#define RX_FS_CRC&t;((long)FS_SFRMERR&lt;&lt;16)/* error detected */
DECL|macro|RX_FS_ADDRESS
mdefine_line|#define RX_FS_ADDRESS&t;((long)FS_SADRRG&lt;&lt;16)&t;/* address recognized */
DECL|macro|RX_FS_MAC
mdefine_line|#define RX_FS_MAC&t;((long)FS_SFRMTY2&lt;&lt;16)/* MAC frame */
DECL|macro|RX_FS_SMT
mdefine_line|#define RX_FS_SMT&t;((long)0&lt;&lt;16)&t;&t;/* SMT frame */
DECL|macro|RX_FS_IMPL
mdefine_line|#define RX_FS_IMPL&t;((long)FS_SFRMTY1&lt;&lt;16)/* implementer frame */
DECL|macro|RX_FS_LLC
mdefine_line|#define RX_FS_LLC&t;((long)FS_SFRMTY0&lt;&lt;16)/* LLC frame */
multiline_comment|/*&n; * receive frame descriptor&n; */
DECL|union|rx_descr
r_union
id|rx_descr
(brace
r_struct
(brace
macro_line|#ifdef&t;LITTLE_ENDIAN
DECL|member|rx_length
r_int
id|rx_length
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* frame length lower/upper byte */
DECL|member|rx_erfbb
r_int
id|rx_erfbb
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* received frame byte boundary */
DECL|member|rx_reserv2
r_int
id|rx_reserv2
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|rx_sfrmty
r_int
id|rx_sfrmty
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* frame type bits */
DECL|member|rx_sadrrg
r_int
id|rx_sadrrg
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* DA == MA or broad-/multicast */
DECL|member|rx_sfrmerr
r_int
id|rx_sfrmerr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* received frame not valid */
DECL|member|rx_seac0
r_int
id|rx_seac0
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* frame-copied  C-indicator */
DECL|member|rx_seac1
r_int
id|rx_seac1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* address-match A-indicator */
DECL|member|rx_seac2
r_int
id|rx_seac2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* frame-error   E-indicator */
DECL|member|rx_ssrcrtg
r_int
id|rx_ssrcrtg
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* == 1 SA has MSB set */
DECL|member|rx_reserv1
r_int
id|rx_reserv1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|rx_msrabt
r_int
id|rx_msrabt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* memory status receive abort */
DECL|member|rx_msvalid
r_int
id|rx_msvalid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* memory status valid */
macro_line|#else
r_int
id|rx_msvalid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* memory status valid */
r_int
id|rx_msrabt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* memory status receive abort */
r_int
id|rx_reserv1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
r_int
id|rx_ssrcrtg
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* == 1 SA has MSB set */
r_int
id|rx_seac2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* frame-error   E-indicator */
r_int
id|rx_seac1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* address-match A-indicator */
r_int
id|rx_seac0
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* frame-copied  C-indicator */
r_int
id|rx_sfrmerr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* received frame not valid */
r_int
id|rx_sadrrg
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* DA == MA or broad-/multicast */
r_int
id|rx_sfrmty
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* frame type bits */
r_int
id|rx_erfbb
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* received frame byte boundary */
r_int
id|rx_reserv2
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* reserved */
r_int
id|rx_length
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* frame length lower/upper byte */
macro_line|#endif
DECL|member|r
)brace
id|r
suffix:semicolon
DECL|member|i
r_int
id|i
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* defines for Receive Frame Descriptor access */
DECL|macro|RD_S_ERFBB
mdefine_line|#define RD_S_ERFBB&t;0x00030000L&t;/* received frame byte boundary */
DECL|macro|RD_S_RES2
mdefine_line|#define RD_S_RES2&t;0x000c0000L&t;/* reserved */
DECL|macro|RD_S_SFRMTY
mdefine_line|#define RD_S_SFRMTY&t;0x00700000L&t;/* frame type bits */
DECL|macro|RD_S_SADRRG
mdefine_line|#define RD_S_SADRRG&t;0x00800000L&t;/* DA == MA or broad-/multicast */
DECL|macro|RD_S_SFRMERR
mdefine_line|#define RD_S_SFRMERR&t;0x01000000L&t;/* received frame not valid */
DECL|macro|RD_S_SEAC
mdefine_line|#define&t;RD_S_SEAC&t;0x0e000000L&t;/* frame status indicators */
DECL|macro|RD_S_SEAC0
mdefine_line|#define RD_S_SEAC0&t;0x02000000L&t;/* frame-copied  case-indicator */
DECL|macro|RD_S_SEAC1
mdefine_line|#define RD_S_SEAC1&t;0x04000000L&t;/* address-match A-indicator */
DECL|macro|RD_S_SEAC2
mdefine_line|#define RD_S_SEAC2&t;0x08000000L&t;/* frame-error   E-indicator */
DECL|macro|RD_S_SSRCRTG
mdefine_line|#define RD_S_SSRCRTG&t;0x10000000L&t;/* == 1 SA has MSB set */
DECL|macro|RD_S_RES1
mdefine_line|#define RD_S_RES1&t;0x20000000L&t;/* reserved */
DECL|macro|RD_S_MSRABT
mdefine_line|#define RD_S_MSRABT&t;0x40000000L&t;/* memory status receive abort */
DECL|macro|RD_S_MSVALID
mdefine_line|#define RD_S_MSVALID&t;0x80000000L&t;/* memory status valid */
DECL|macro|RD_STATUS
mdefine_line|#define&t;RD_STATUS&t;0xffff0000L
DECL|macro|RD_LENGTH
mdefine_line|#define&t;RD_LENGTH&t;0x0000ffffL
multiline_comment|/* defines for Receive Frames Status Word values */
multiline_comment|/*RD_S_SFRMTY*/
DECL|macro|RD_FRM_SMT
mdefine_line|#define RD_FRM_SMT&t;(unsigned long)(0&lt;&lt;20)     /* asynchr. frames */
DECL|macro|RD_FRM_LLCA
mdefine_line|#define RD_FRM_LLCA&t;(unsigned long)(1&lt;&lt;20)
DECL|macro|RD_FRM_IMPA
mdefine_line|#define RD_FRM_IMPA&t;(unsigned long)(2&lt;&lt;20)
DECL|macro|RD_FRM_MAC
mdefine_line|#define RD_FRM_MAC&t;(unsigned long)(4&lt;&lt;20)     /* synchr. frames */
DECL|macro|RD_FRM_LLCS
mdefine_line|#define RD_FRM_LLCS&t;(unsigned long)(5&lt;&lt;20)
DECL|macro|RD_FRM_IMPS
mdefine_line|#define RD_FRM_IMPS&t;(unsigned long)(6&lt;&lt;20)
DECL|macro|TX_DESCRIPTOR
mdefine_line|#define TX_DESCRIPTOR&t;0x40000000L
DECL|macro|TX_OFFSET_3
mdefine_line|#define TX_OFFSET_3&t;0x18000000L
DECL|macro|TXP1
mdefine_line|#define TXP1&t;2
multiline_comment|/*&n; * transmit frame descriptor&n; */
DECL|union|tx_descr
r_union
id|tx_descr
(brace
r_struct
(brace
macro_line|#ifdef&t;LITTLE_ENDIAN
DECL|member|tx_length
r_int
id|tx_length
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* frame length lower/upper byte */
DECL|member|tx_res
r_int
id|tx_res
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* reserved &t; (bit 16..23) */
DECL|member|tx_xmtabt
r_int
id|tx_xmtabt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* transmit abort */
DECL|member|tx_nfcs
r_int
id|tx_nfcs
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* no frame check sequence */
DECL|member|tx_xdone
r_int
id|tx_xdone
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* give up token */
DECL|member|tx_rpxm
r_int
id|tx_rpxm
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* byte offset */
DECL|member|tx_pat1
r_int
id|tx_pat1
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* must be TXP1 */
DECL|member|tx_more
r_int
id|tx_more
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* more frame in chain */
macro_line|#else
r_int
id|tx_more
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* more frame in chain */
r_int
id|tx_pat1
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* must be TXP1 */
r_int
id|tx_rpxm
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* byte offset */
r_int
id|tx_xdone
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* give up token */
r_int
id|tx_nfcs
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* no frame check sequence */
r_int
id|tx_xmtabt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* transmit abort */
r_int
id|tx_res
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* reserved &t; (bit 16..23) */
r_int
id|tx_length
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* frame length lower/upper byte */
macro_line|#endif
DECL|member|t
)brace
id|t
suffix:semicolon
DECL|member|i
r_int
id|i
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* defines for Transmit Descriptor access */
DECL|macro|TD_C_MORE
mdefine_line|#define&t;TD_C_MORE&t;0x80000000L&t;/* more frame in chain */
DECL|macro|TD_C_DESCR
mdefine_line|#define&t;TD_C_DESCR&t;0x60000000L&t;/* must be TXP1 */
DECL|macro|TD_C_TXFBB
mdefine_line|#define&t;TD_C_TXFBB&t;0x18000000L&t;/* byte offset */
DECL|macro|TD_C_XDONE
mdefine_line|#define&t;TD_C_XDONE&t;0x04000000L&t;/* give up token */
DECL|macro|TD_C_NFCS
mdefine_line|#define TD_C_NFCS&t;0x02000000L&t;/* no frame check sequence */
DECL|macro|TD_C_XMTABT
mdefine_line|#define TD_C_XMTABT&t;0x01000000L&t;/* transmit abort */
DECL|macro|TD_C_LNCNU
mdefine_line|#define&t;TD_C_LNCNU&t;0x0000ff00L&t;
DECL|macro|TD_C_LNCNL
mdefine_line|#define TD_C_LNCNL&t;0x000000ffL
DECL|macro|TD_C_LNCN
mdefine_line|#define TD_C_LNCN&t;0x0000ffffL&t;/* frame length lower/upper byte */
multiline_comment|/*&n; * transmit pointer&n; */
DECL|union|tx_pointer
r_union
id|tx_pointer
(brace
DECL|struct|t
r_struct
id|t
(brace
macro_line|#ifdef&t;LITTLE_ENDIAN
DECL|member|tp_pointer
r_int
id|tp_pointer
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* pointer to tx_descr (low/high) */
DECL|member|tp_res
r_int
id|tp_res
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* reserved &t; (bit 16..23) */
DECL|member|tp_pattern
r_int
id|tp_pattern
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* fixed pattern (bit 24..31) */
macro_line|#else
r_int
id|tp_pattern
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* fixed pattern (bit 24..31) */
r_int
id|tp_res
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* reserved &t; (bit 16..23) */
r_int
id|tp_pointer
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* pointer to tx_descr (low/high) */
macro_line|#endif
DECL|member|t
)brace
id|t
suffix:semicolon
DECL|member|i
r_int
id|i
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* defines for Nontag Mode Pointer access */
DECL|macro|TD_P_CNTRL
mdefine_line|#define&t;TD_P_CNTRL&t;0xff000000L
DECL|macro|TD_P_RPXU
mdefine_line|#define TD_P_RPXU&t;0x0000ff00L
DECL|macro|TD_P_RPXL
mdefine_line|#define TD_P_RPXL&t;0x000000ffL
DECL|macro|TD_P_RPX
mdefine_line|#define TD_P_RPX&t;0x0000ffffL
DECL|macro|TX_PATTERN
mdefine_line|#define TX_PATTERN&t;0xa0
DECL|macro|TX_POINTER_END
mdefine_line|#define TX_POINTER_END&t;0xa0000000L
DECL|macro|TX_INT_PATTERN
mdefine_line|#define TX_INT_PATTERN&t;0xa0000000L
DECL|struct|tx_queue
r_struct
id|tx_queue
(brace
DECL|member|tq_next
r_struct
id|tx_queue
op_star
id|tq_next
suffix:semicolon
DECL|member|tq_pack_offset
id|u_short
id|tq_pack_offset
suffix:semicolon
multiline_comment|/* offset buffer memory */
DECL|member|tq_pad
id|u_char
id|tq_pad
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;&t;defines for FORMAC Plus (Am79C830)&n;*/
multiline_comment|/*&n; *  FORMAC+ read/write (r/w) registers&n; */
DECL|macro|FM_CMDREG1
mdefine_line|#define FM_CMDREG1&t;0x00&t;&t;/* write command reg 1 instruction */
DECL|macro|FM_CMDREG2
mdefine_line|#define FM_CMDREG2&t;0x01&t;&t;/* write command reg 2 instruction */
DECL|macro|FM_ST1U
mdefine_line|#define FM_ST1U&t;&t;0x00&t;&t;/* read upper 16-bit of status reg 1 */
DECL|macro|FM_ST1L
mdefine_line|#define FM_ST1L&t;&t;0x01&t;&t;/* read lower 16-bit of status reg 1 */
DECL|macro|FM_ST2U
mdefine_line|#define FM_ST2U&t;&t;0x02&t;&t;/* read upper 16-bit of status reg 2 */
DECL|macro|FM_ST2L
mdefine_line|#define FM_ST2L&t;&t;0x03&t;&t;/* read lower 16-bit of status reg 2 */
DECL|macro|FM_IMSK1U
mdefine_line|#define FM_IMSK1U&t;0x04&t;&t;/* r/w upper 16-bit of IMSK 1 */
DECL|macro|FM_IMSK1L
mdefine_line|#define FM_IMSK1L&t;0x05&t;&t;/* r/w lower 16-bit of IMSK 1 */
DECL|macro|FM_IMSK2U
mdefine_line|#define FM_IMSK2U&t;0x06&t;&t;/* r/w upper 16-bit of IMSK 2 */
DECL|macro|FM_IMSK2L
mdefine_line|#define FM_IMSK2L&t;0x07&t;&t;/* r/w lower 16-bit of IMSK 2 */
DECL|macro|FM_SAID
mdefine_line|#define FM_SAID&t;&t;0x08&t;&t;/* r/w short addr.-individual */
DECL|macro|FM_LAIM
mdefine_line|#define FM_LAIM&t;&t;0x09&t;&t;/* r/w long addr.-ind. (MSW of LAID) */
DECL|macro|FM_LAIC
mdefine_line|#define FM_LAIC&t;&t;0x0a&t;&t;/* r/w long addr.-ind. (middle)*/
DECL|macro|FM_LAIL
mdefine_line|#define FM_LAIL&t;&t;0x0b&t;&t;/* r/w long addr.-ind. (LSW) */
DECL|macro|FM_SAGP
mdefine_line|#define FM_SAGP&t;&t;0x0c&t;&t;/* r/w short address-group */
DECL|macro|FM_LAGM
mdefine_line|#define FM_LAGM&t;&t;0x0d&t;&t;/* r/w long addr.-gr. (MSW of LAGP) */
DECL|macro|FM_LAGC
mdefine_line|#define FM_LAGC&t;&t;0x0e&t;&t;/* r/w long addr.-gr. (middle) */
DECL|macro|FM_LAGL
mdefine_line|#define FM_LAGL&t;&t;0x0f&t;&t;/* r/w long addr.-gr. (LSW) */
DECL|macro|FM_MDREG1
mdefine_line|#define FM_MDREG1&t;0x10&t;&t;/* r/w 16-bit mode reg 1 */
DECL|macro|FM_STMCHN
mdefine_line|#define FM_STMCHN&t;0x11&t;&t;/* read state-machine reg */
DECL|macro|FM_MIR1
mdefine_line|#define FM_MIR1&t;&t;0x12&t;&t;/* read upper 16-bit of MAC Info Reg */
DECL|macro|FM_MIR0
mdefine_line|#define FM_MIR0&t;&t;0x13&t;&t;/* read lower 16-bit of MAC Info Reg */
DECL|macro|FM_TMAX
mdefine_line|#define FM_TMAX&t;&t;0x14&t;&t;/* r/w 16-bit TMAX reg */
DECL|macro|FM_TVX
mdefine_line|#define FM_TVX&t;&t;0x15&t;&t;/* write 8-bit TVX reg with NP7-0&n;&t;&t;&t;&t;&t;   read TVX on NP7-0, timer on NP15-8*/
DECL|macro|FM_TRT
mdefine_line|#define FM_TRT&t;&t;0x16&t;&t;/* r/w upper 16-bit of TRT timer */
DECL|macro|FM_THT
mdefine_line|#define FM_THT&t;&t;0x17&t;&t;/* r/w upper 16-bit of THT timer */
DECL|macro|FM_TNEG
mdefine_line|#define FM_TNEG&t;&t;0x18&t;&t;/* read upper 16-bit of TNEG (TTRT) */
DECL|macro|FM_TMRS
mdefine_line|#define FM_TMRS&t;&t;0x19&t;&t;/* read lower 5-bit of TNEG,TRT,THT */
multiline_comment|/* F E D C  B A 9 8  7 6 5 4  3 2 1 0&n;&t;&t;&t;   x |-TNEG4-0| |-TRT4-0-| |-THT4-0-| (x-late count) */
DECL|macro|FM_TREQ0
mdefine_line|#define FM_TREQ0&t;0x1a&t;&t;/* r/w 16-bit TREQ0 reg (LSW of TRT) */
DECL|macro|FM_TREQ1
mdefine_line|#define FM_TREQ1&t;0x1b&t;&t;/* r/w 16-bit TREQ1 reg (MSW of TRT) */
DECL|macro|FM_PRI0
mdefine_line|#define FM_PRI0&t;&t;0x1c&t;&t;/* r/w priority r. for asyn.-queue 0 */
DECL|macro|FM_PRI1
mdefine_line|#define FM_PRI1&t;&t;0x1d&t;&t;/* r/w priority r. for asyn.-queue 1 */
DECL|macro|FM_PRI2
mdefine_line|#define FM_PRI2&t;&t;0x1e&t;&t;/* r/w priority r. for asyn.-queue 2 */
DECL|macro|FM_TSYNC
mdefine_line|#define FM_TSYNC&t;0x1f&t;&t;/* r/w 16-bit of the TSYNC register */
DECL|macro|FM_MDREG2
mdefine_line|#define FM_MDREG2&t;0x20&t;&t;/* r/w 16-bit mode reg 2 */
DECL|macro|FM_FRMTHR
mdefine_line|#define FM_FRMTHR&t;0x21&t;&t;/* r/w the frame threshold register */
DECL|macro|FM_EACB
mdefine_line|#define FM_EACB&t;&t;0x22&t;&t;/* r/w end addr of claim/beacon area */
DECL|macro|FM_EARV
mdefine_line|#define FM_EARV&t;&t;0x23&t;&t;/* r/w end addr of receive queue */
multiline_comment|/* Supernet 3 */
DECL|macro|FM_EARV1
mdefine_line|#define&t;FM_EARV1&t;FM_EARV
DECL|macro|FM_EAS
mdefine_line|#define FM_EAS&t;&t;0x24&t;&t;/* r/w end addr of synchr. queue */
DECL|macro|FM_EAA0
mdefine_line|#define FM_EAA0&t;&t;0x25&t;&t;/* r/w end addr of asyn. queue 0 */
DECL|macro|FM_EAA1
mdefine_line|#define FM_EAA1&t;&t;0x26&t;&t;/* r/w end addr of asyn. queue 1 */
DECL|macro|FM_EAA2
mdefine_line|#define FM_EAA2&t;&t;0x27&t;&t;/* r/w end addr of asyn. queue 2 */
DECL|macro|FM_SACL
mdefine_line|#define FM_SACL&t;&t;0x28&t;&t;/* r/w start addr of claim frame */
DECL|macro|FM_SABC
mdefine_line|#define FM_SABC&t;&t;0x29&t;&t;/* r/w start addr of beacon frame */
DECL|macro|FM_WPXSF
mdefine_line|#define FM_WPXSF&t;0x2a&t;&t;/* r/w the write ptr. for special fr.*/
DECL|macro|FM_RPXSF
mdefine_line|#define FM_RPXSF&t;0x2b&t;&t;/* r/w the read ptr. for special fr. */
DECL|macro|FM_RPR
mdefine_line|#define FM_RPR&t;&t;0x2d&t;&t;/* r/w the read ptr. for receive qu. */
DECL|macro|FM_WPR
mdefine_line|#define FM_WPR&t;&t;0x2e&t;&t;/* r/w the write ptr. for receive qu.*/
DECL|macro|FM_SWPR
mdefine_line|#define FM_SWPR&t;&t;0x2f&t;&t;/* r/w the shadow wr.-ptr. for rec.q.*/
multiline_comment|/* Supernet 3 */
DECL|macro|FM_RPR1
mdefine_line|#define FM_RPR1         FM_RPR   
DECL|macro|FM_WPR1
mdefine_line|#define FM_WPR1         FM_WPR 
DECL|macro|FM_SWPR1
mdefine_line|#define FM_SWPR1        FM_SWPR
DECL|macro|FM_WPXS
mdefine_line|#define FM_WPXS&t;&t;0x30&t;&t;/* r/w the write ptr. for synchr. qu.*/
DECL|macro|FM_WPXA0
mdefine_line|#define FM_WPXA0&t;0x31&t;&t;/* r/w the write ptr. for asyn. qu.0 */
DECL|macro|FM_WPXA1
mdefine_line|#define FM_WPXA1&t;0x32&t;&t;/* r/w the write ptr. for asyn. qu.1 */
DECL|macro|FM_WPXA2
mdefine_line|#define FM_WPXA2&t;0x33&t;&t;/* r/w the write ptr. for asyn. qu.2 */
DECL|macro|FM_SWPXS
mdefine_line|#define FM_SWPXS&t;0x34&t;&t;/* r/w the shadow wr.-ptr. for syn.q.*/
DECL|macro|FM_SWPXA0
mdefine_line|#define FM_SWPXA0&t;0x35&t;&t;/* r/w the shad. wr.-ptr. for asyn.q0*/
DECL|macro|FM_SWPXA1
mdefine_line|#define FM_SWPXA1&t;0x36&t;&t;/* r/w the shad. wr.-ptr. for asyn.q1*/
DECL|macro|FM_SWPXA2
mdefine_line|#define FM_SWPXA2&t;0x37&t;&t;/* r/w the shad. wr.-ptr. for asyn.q2*/
DECL|macro|FM_RPXS
mdefine_line|#define FM_RPXS&t;&t;0x38&t;&t;/* r/w the read ptr. for synchr. qu. */
DECL|macro|FM_RPXA0
mdefine_line|#define FM_RPXA0&t;0x39&t;&t;/* r/w the read ptr. for asyn. qu. 0 */
DECL|macro|FM_RPXA1
mdefine_line|#define FM_RPXA1&t;0x3a&t;&t;/* r/w the read ptr. for asyn. qu. 1 */
DECL|macro|FM_RPXA2
mdefine_line|#define FM_RPXA2&t;0x3b&t;&t;/* r/w the read ptr. for asyn. qu. 2 */
DECL|macro|FM_MARR
mdefine_line|#define FM_MARR&t;&t;0x3c&t;&t;/* r/w the memory read addr register */
DECL|macro|FM_MARW
mdefine_line|#define FM_MARW&t;&t;0x3d&t;&t;/* r/w the memory write addr register*/
DECL|macro|FM_MDRU
mdefine_line|#define FM_MDRU&t;&t;0x3e&t;&t;/* r/w upper 16-bit of mem. data reg */
DECL|macro|FM_MDRL
mdefine_line|#define FM_MDRL&t;&t;0x3f&t;&t;/* r/w lower 16-bit of mem. data reg */
multiline_comment|/* following instructions relate to MAC counters and timer */
DECL|macro|FM_TMSYNC
mdefine_line|#define FM_TMSYNC&t;0x40&t;&t;/* r/w upper 16 bits of TMSYNC timer */
DECL|macro|FM_FCNTR
mdefine_line|#define FM_FCNTR&t;0x41&t;&t;/* r/w the 16-bit frame counter */
DECL|macro|FM_LCNTR
mdefine_line|#define FM_LCNTR&t;0x42&t;&t;/* r/w the 16-bit lost counter */
DECL|macro|FM_ECNTR
mdefine_line|#define FM_ECNTR&t;0x43&t;&t;/* r/w the 16-bit error counter */
multiline_comment|/* Supernet 3:&t;extensions to old register block */
DECL|macro|FM_FSCNTR
mdefine_line|#define&t;FM_FSCNTR&t;0x44&t;&t;/* r/? Frame Strip Counter */
DECL|macro|FM_FRSELREG
mdefine_line|#define&t;FM_FRSELREG&t;0x45&t;&t;/* r/w Frame Selection Register */
multiline_comment|/* Supernet 3:&t;extensions for 2. receive queue etc. */
DECL|macro|FM_MDREG3
mdefine_line|#define&t;FM_MDREG3&t;0x60&t;&t;/* r/w Mode Register 3 */
DECL|macro|FM_ST3U
mdefine_line|#define&t;FM_ST3U&t;&t;0x61&t;&t;/* read upper 16-bit of status reg 3 */
DECL|macro|FM_ST3L
mdefine_line|#define&t;FM_ST3L&t;&t;0x62&t;&t;/* read lower 16-bit of status reg 3 */
DECL|macro|FM_IMSK3U
mdefine_line|#define&t;FM_IMSK3U&t;0x63&t;&t;/* r/w upper 16-bit of IMSK reg 3 */
DECL|macro|FM_IMSK3L
mdefine_line|#define&t;FM_IMSK3L&t;0x64&t;&t;/* r/w lower 16-bit of IMSK reg 3 */
DECL|macro|FM_IVR
mdefine_line|#define&t;FM_IVR&t;&t;0x65&t;&t;/* read Interrupt Vector register */
DECL|macro|FM_IMR
mdefine_line|#define&t;FM_IMR&t;&t;0x66&t;&t;/* r/w Interrupt mask register */
multiline_comment|/* 0x67&t;Hidden */
DECL|macro|FM_RPR2
mdefine_line|#define&t;FM_RPR2&t;&t;0x68&t;&t;/* r/w the read ptr. for rec. qu. 2 */
DECL|macro|FM_WPR2
mdefine_line|#define&t;FM_WPR2&t;&t;0x69&t;&t;/* r/w the write ptr. for rec. qu. 2 */
DECL|macro|FM_SWPR2
mdefine_line|#define&t;FM_SWPR2&t;0x6a&t;&t;/* r/w the shadow wptr. for rec. q. 2 */
DECL|macro|FM_EARV2
mdefine_line|#define&t;FM_EARV2&t;0x6b&t;&t;/* r/w end addr of rec. qu. 2 */
DECL|macro|FM_UNLCKDLY
mdefine_line|#define&t;FM_UNLCKDLY&t;0x6c&t;&t;/* r/w Auto Unlock Delay register */
multiline_comment|/* Bit 15-8: RECV2 unlock threshold */
multiline_comment|/* Bit  7-0: RECV1 unlock threshold */
multiline_comment|/* 0x6f-0x73&t;Hidden */
DECL|macro|FM_LTDPA1
mdefine_line|#define&t;FM_LTDPA1&t;0x79&t;&t;/* r/w Last Trans desc ptr for A1 qu. */
multiline_comment|/* 0x80-0x9a&t;PLCS registers of built-in PLCS  (Supernet 3 only) */
multiline_comment|/* Supernet 3: Adderss Filter Registers */
DECL|macro|FM_AFCMD
mdefine_line|#define&t;FM_AFCMD&t;0xb0&t;&t;/* r/w Address Filter Command Reg */
DECL|macro|FM_AFSTAT
mdefine_line|#define&t;FM_AFSTAT&t;0xb2&t;&t;/* r/w Address Filter Status Reg */
DECL|macro|FM_AFBIST
mdefine_line|#define&t;FM_AFBIST&t;0xb4&t;&t;/* r/w Address Filter BIST signature */
DECL|macro|FM_AFCOMP2
mdefine_line|#define&t;FM_AFCOMP2&t;0xb6&t;&t;/* r/w Address Filter Comparand 2 */
DECL|macro|FM_AFCOMP1
mdefine_line|#define&t;FM_AFCOMP1&t;0xb8&t;&t;/* r/w Address Filter Comparand 1 */
DECL|macro|FM_AFCOMP0
mdefine_line|#define&t;FM_AFCOMP0&t;0xba&t;&t;/* r/w Address Filter Comparand 0 */
DECL|macro|FM_AFMASK2
mdefine_line|#define&t;FM_AFMASK2&t;0xbc&t;&t;/* r/w Address Filter Mask 2 */
DECL|macro|FM_AFMASK1
mdefine_line|#define&t;FM_AFMASK1&t;0xbe&t;&t;/* r/w Address Filter Mask 1 */
DECL|macro|FM_AFMASK0
mdefine_line|#define&t;FM_AFMASK0&t;0xc0&t;&t;/* r/w Address Filter Mask 0 */
DECL|macro|FM_AFPERS
mdefine_line|#define&t;FM_AFPERS&t;0xc2&t;&t;/* r/w Address Filter Personality Reg */
multiline_comment|/* Supernet 3: Orion (PDX?) Registers */
DECL|macro|FM_ORBIST
mdefine_line|#define&t;FM_ORBIST&t;0xd0&t;&t;/* r/w Orion BIST signature */
DECL|macro|FM_ORSTAT
mdefine_line|#define&t;FM_ORSTAT&t;0xd2&t;&t;/* r/w Orion Status Register */
multiline_comment|/*&n; * Mode Register 1 (MDREG1)&n; */
DECL|macro|FM_RES0
mdefine_line|#define FM_RES0&t;&t;0x0001&t;&t;/* reserved */
multiline_comment|/* SN3: other definition */
DECL|macro|FM_XMTINH_HOLD
mdefine_line|#define&t;FM_XMTINH_HOLD&t;0x0002&t;&t;/* transmit-inhibit/hold bit */
multiline_comment|/* SN3: other definition */
DECL|macro|FM_HOFLXI
mdefine_line|#define&t;FM_HOFLXI&t;0x0003&t;&t;/* SN3: Hold / Flush / Inhibit */
DECL|macro|FM_FULL_HALF
mdefine_line|#define&t;FM_FULL_HALF&t;0x0004&t;&t;/* full-duplex/half-duplex bit */
DECL|macro|FM_LOCKTX
mdefine_line|#define&t;FM_LOCKTX&t;0x0008&t;&t;/* lock-transmit-asynchr.-queues bit */
DECL|macro|FM_EXGPA0
mdefine_line|#define FM_EXGPA0&t;0x0010&t;&t;/* extended-group-addressing bit 0 */
DECL|macro|FM_EXGPA1
mdefine_line|#define FM_EXGPA1&t;0x0020&t;&t;/* extended-group-addressing bit 1 */
DECL|macro|FM_DISCRY
mdefine_line|#define FM_DISCRY&t;0x0040&t;&t;/* disable-carry bit */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_SELRA
mdefine_line|#define FM_SELRA&t;0x0080&t;&t;/* select input from PHY (1=RA,0=RB) */
DECL|macro|FM_ADDET
mdefine_line|#define FM_ADDET&t;0x0700&t;&t;/* address detection */
DECL|macro|FM_MDAMA
mdefine_line|#define FM_MDAMA&t;(0&lt;&lt;8)&t;&t;/* address detection : DA = MA */
DECL|macro|FM_MDASAMA
mdefine_line|#define FM_MDASAMA&t;(1&lt;&lt;8)&t;&t;/* address detection : DA=MA||SA=MA */
DECL|macro|FM_MRNNSAFNMA
mdefine_line|#define&t;FM_MRNNSAFNMA&t;(2&lt;&lt;8)&t;&t;/* rec. non-NSA frames DA=MA&amp;&amp;SA!=MA */
DECL|macro|FM_MRNNSAF
mdefine_line|#define&t;FM_MRNNSAF&t;(3&lt;&lt;8)&t;&t;/* rec. non-NSA frames DA = MA */
DECL|macro|FM_MDISRCV
mdefine_line|#define&t;FM_MDISRCV&t;(4&lt;&lt;8)&t;&t;/* disable receive function */
DECL|macro|FM_MRES0
mdefine_line|#define&t;FM_MRES0&t;(5&lt;&lt;8)&t;&t;/* reserve */
DECL|macro|FM_MLIMPROM
mdefine_line|#define&t;FM_MLIMPROM&t;(6&lt;&lt;8)&t;&t;/* limited-promiscuous mode */
DECL|macro|FM_MPROMISCOUS
mdefine_line|#define FM_MPROMISCOUS&t;(7&lt;&lt;8)&t;&t;/* address detection : promiscous */
DECL|macro|FM_SELSA
mdefine_line|#define FM_SELSA&t;0x0800&t;&t;/* select-short-address bit */
DECL|macro|FM_MMODE
mdefine_line|#define FM_MMODE&t;0x7000&t;&t;/* mode select */
DECL|macro|FM_MINIT
mdefine_line|#define FM_MINIT&t;(0&lt;&lt;12)&t;&t;/* initialize */
DECL|macro|FM_MMEMACT
mdefine_line|#define FM_MMEMACT&t;(1&lt;&lt;12)&t;&t;/* memory activate */
DECL|macro|FM_MONLINESP
mdefine_line|#define FM_MONLINESP&t;(2&lt;&lt;12)&t;&t;/* on-line special */
DECL|macro|FM_MONLINE
mdefine_line|#define FM_MONLINE&t;(3&lt;&lt;12)&t;&t;/* on-line (FDDI operational mode) */
DECL|macro|FM_MILOOP
mdefine_line|#define FM_MILOOP&t;(4&lt;&lt;12)&t;&t;/* internal loopback */
DECL|macro|FM_MRES1
mdefine_line|#define FM_MRES1&t;(5&lt;&lt;12)&t;&t;/* reserved */
DECL|macro|FM_MRES2
mdefine_line|#define FM_MRES2&t;(6&lt;&lt;12)&t;&t;/* reserved */
DECL|macro|FM_MELOOP
mdefine_line|#define FM_MELOOP&t;(7&lt;&lt;12)&t;&t;/* external loopback */
DECL|macro|FM_SNGLFRM
mdefine_line|#define&t;FM_SNGLFRM&t;0x8000&t;&t;/* single-frame-receive mode */
multiline_comment|/* SN3: reserved */
DECL|macro|MDR1INIT
mdefine_line|#define&t;MDR1INIT&t;(FM_MINIT | FM_MDAMA)
multiline_comment|/*&n; * Mode Register 2 (MDREG2)&n; */
DECL|macro|FM_AFULL
mdefine_line|#define&t;FM_AFULL&t;0x000f&t;&t;/* 4-bit value (empty loc.in txqueue)*/
DECL|macro|FM_RCVERR
mdefine_line|#define&t;FM_RCVERR&t;0x0010&t;&t;/* rec.-errored-frames bit */
DECL|macro|FM_SYMCTL
mdefine_line|#define&t;FM_SYMCTL&t;0x0020&t;&t;/* sysmbol-control bit */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_SYNPRQ
mdefine_line|#define&t;FM_SYNPRQ&t;0x0040&t;&t;/* synchron.-NP-DMA-request bit */
DECL|macro|FM_ENNPRQ
mdefine_line|#define&t;FM_ENNPRQ&t;0x0080&t;&t;/* enable-NP-DMA-request bit */
DECL|macro|FM_ENHSRQ
mdefine_line|#define&t;FM_ENHSRQ&t;0x0100&t;&t;/* enable-host-request bit */
DECL|macro|FM_RXFBB01
mdefine_line|#define&t;FM_RXFBB01&t;0x0600&t;&t;/* rec. frame byte boundary bit0 &amp; 1 */
DECL|macro|FM_LSB
mdefine_line|#define&t;FM_LSB&t;&t;0x0800&t;&t;/* determ. ordering of bytes in buffer*/
DECL|macro|FM_PARITY
mdefine_line|#define&t;FM_PARITY&t;0x1000&t;&t;/* 1 = even, 0 = odd */
DECL|macro|FM_CHKPAR
mdefine_line|#define&t;FM_CHKPAR&t;0x2000&t;&t;/* 1 = parity of 32-bit buffer BD-bus*/
DECL|macro|FM_STRPFCS
mdefine_line|#define&t;FM_STRPFCS&t;0x4000&t;&t;/* 1 = strips FCS field of rec.frame */
DECL|macro|FM_BMMODE
mdefine_line|#define&t;FM_BMMODE&t;0x8000&t;&t;/* Buffer-Memory-Mode (1 = tag mode) */
multiline_comment|/* SN3: 1 = tag, 0 = modified tag */
multiline_comment|/*&n; * Status Register 1, Upper 16 Bits (ST1U)&n; */
DECL|macro|FM_STEFRMS
mdefine_line|#define FM_STEFRMS&t;0x0001&t;&t;/* transmit end of frame: synchr. qu.*/
DECL|macro|FM_STEFRMA0
mdefine_line|#define FM_STEFRMA0&t;0x0002&t;&t;/* transmit end of frame: asyn. qu.0 */
DECL|macro|FM_STEFRMA1
mdefine_line|#define FM_STEFRMA1&t;0x0004&t;&t;/* transmit end of frame: asyn. qu.1 */
DECL|macro|FM_STEFRMA2
mdefine_line|#define FM_STEFRMA2&t;0x0008&t;&t;/* transmit end of frame: asyn. qu.2 */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_STECFRMS
mdefine_line|#define FM_STECFRMS&t;0x0010&t;&t;/* transmit end of chain of syn. qu. */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_STECFRMA0
mdefine_line|#define FM_STECFRMA0&t;0x0020&t;&t;/* transmit end of chain of asyn. q0 */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_STECFRMA1
mdefine_line|#define FM_STECFRMA1&t;0x0040&t;&t;/* transmit end of chain of asyn. q1 */
multiline_comment|/* SN3: STECMDA1 */
DECL|macro|FM_STECMDA1
mdefine_line|#define FM_STECMDA1&t;0x0040&t;&t;/* SN3: &squot;no description&squot; */
DECL|macro|FM_STECFRMA2
mdefine_line|#define FM_STECFRMA2&t;0x0080&t;&t;/* transmit end of chain of asyn. q2 */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_STEXDONS
mdefine_line|#define&t;FM_STEXDONS&t;0x0100&t;&t;/* transmit until XDONE in syn. qu. */
DECL|macro|FM_STBFLA
mdefine_line|#define&t;FM_STBFLA&t;0x0200&t;&t;/* asynchr.-queue trans. buffer full */
DECL|macro|FM_STBFLS
mdefine_line|#define&t;FM_STBFLS&t;0x0400&t;&t;/* synchr.-queue transm. buffer full */
DECL|macro|FM_STXABRS
mdefine_line|#define&t;FM_STXABRS&t;0x0800&t;&t;/* synchr. queue transmit-abort */
DECL|macro|FM_STXABRA0
mdefine_line|#define&t;FM_STXABRA0&t;0x1000&t;&t;/* asynchr. queue 0 transmit-abort */
DECL|macro|FM_STXABRA1
mdefine_line|#define&t;FM_STXABRA1&t;0x2000&t;&t;/* asynchr. queue 1 transmit-abort */
DECL|macro|FM_STXABRA2
mdefine_line|#define&t;FM_STXABRA2&t;0x4000&t;&t;/* asynchr. queue 2 transmit-abort */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_SXMTABT
mdefine_line|#define&t;FM_SXMTABT&t;0x8000&t;&t;/* transmit abort */
multiline_comment|/*&n; * Status Register 1, Lower 16 Bits (ST1L)&n; */
DECL|macro|FM_SQLCKS
mdefine_line|#define FM_SQLCKS&t;0x0001&t;&t;/* queue lock for synchr. queue */
DECL|macro|FM_SQLCKA0
mdefine_line|#define FM_SQLCKA0&t;0x0002&t;&t;/* queue lock for asynchr. queue 0 */
DECL|macro|FM_SQLCKA1
mdefine_line|#define FM_SQLCKA1&t;0x0004&t;&t;/* queue lock for asynchr. queue 1 */
DECL|macro|FM_SQLCKA2
mdefine_line|#define FM_SQLCKA2&t;0x0008&t;&t;/* queue lock for asynchr. queue 2 */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_STXINFLS
mdefine_line|#define FM_STXINFLS&t;0x0010&t;&t;/* transmit instruction full: syn. */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_STXINFLA0
mdefine_line|#define FM_STXINFLA0&t;0x0020&t;&t;/* transmit instruction full: asyn.0 */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_STXINFLA1
mdefine_line|#define FM_STXINFLA1&t;0x0040&t;&t;/* transmit instruction full: asyn.1 */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_STXINFLA2
mdefine_line|#define FM_STXINFLA2&t;0x0080&t;&t;/* transmit instruction full: asyn.2 */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_SPCEPDS
mdefine_line|#define FM_SPCEPDS&t;0x0100&t;&t;/* parity/coding error: syn. queue */
DECL|macro|FM_SPCEPDA0
mdefine_line|#define FM_SPCEPDA0&t;0x0200&t;&t;/* parity/coding error: asyn. queue0 */
DECL|macro|FM_SPCEPDA1
mdefine_line|#define FM_SPCEPDA1&t;0x0400&t;&t;/* parity/coding error: asyn. queue1 */
DECL|macro|FM_SPCEPDA2
mdefine_line|#define FM_SPCEPDA2&t;0x0800&t;&t;/* parity/coding error: asyn. queue2 */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_STBURS
mdefine_line|#define FM_STBURS&t;0x1000&t;&t;/* transmit buffer underrun: syn. q. */
DECL|macro|FM_STBURA0
mdefine_line|#define FM_STBURA0&t;0x2000&t;&t;/* transmit buffer underrun: asyn.0 */
DECL|macro|FM_STBURA1
mdefine_line|#define FM_STBURA1&t;0x4000&t;&t;/* transmit buffer underrun: asyn.1 */
DECL|macro|FM_STBURA2
mdefine_line|#define FM_STBURA2&t;0x8000&t;&t;/* transmit buffer underrun: asyn.2 */
multiline_comment|/* SN3: reserved */
multiline_comment|/*&n; * Status Register 2, Upper 16 Bits (ST2U)&n; */
DECL|macro|FM_SOTRBEC
mdefine_line|#define FM_SOTRBEC&t;0x0001&t;&t;/* other beacon received */
DECL|macro|FM_SMYBEC
mdefine_line|#define FM_SMYBEC&t;0x0002&t;&t;/* my beacon received */
DECL|macro|FM_SBEC
mdefine_line|#define FM_SBEC&t;&t;0x0004&t;&t;/* beacon state entered */
DECL|macro|FM_SLOCLM
mdefine_line|#define FM_SLOCLM&t;0x0008&t;&t;/* low claim received */
DECL|macro|FM_SHICLM
mdefine_line|#define FM_SHICLM&t;0x0010&t;&t;/* high claim received */
DECL|macro|FM_SMYCLM
mdefine_line|#define FM_SMYCLM&t;0x0020&t;&t;/* my claim received */
DECL|macro|FM_SCLM
mdefine_line|#define FM_SCLM&t;&t;0x0040&t;&t;/* claim state entered */
DECL|macro|FM_SERRSF
mdefine_line|#define FM_SERRSF&t;0x0080&t;&t;/* error in special frame */
DECL|macro|FM_SNFSLD
mdefine_line|#define FM_SNFSLD&t;0x0100&t;&t;/* NP and FORMAC+ simultaneous load */
DECL|macro|FM_SRFRCTOV
mdefine_line|#define FM_SRFRCTOV&t;0x0200&t;&t;/* receive frame counter overflow */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_SRCVFRM
mdefine_line|#define FM_SRCVFRM&t;0x0400&t;&t;/* receive frame */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_SRCVOVR
mdefine_line|#define FM_SRCVOVR&t;0x0800&t;&t;/* receive FIFO overflow */
DECL|macro|FM_SRBFL
mdefine_line|#define FM_SRBFL&t;0x1000&t;&t;/* receive buffer full */
DECL|macro|FM_SRABT
mdefine_line|#define FM_SRABT&t;0x2000&t;&t;/* receive abort */
DECL|macro|FM_SRBMT
mdefine_line|#define FM_SRBMT&t;0x4000&t;&t;/* receive buffer empty */
DECL|macro|FM_SRCOMP
mdefine_line|#define FM_SRCOMP&t;0x8000&t;&t;/* receive complete. Nontag mode */
multiline_comment|/*&n; * Status Register 2, Lower 16 Bits (ST2L)&n; * Attention: SN3 docu shows these bits the other way around&n; */
DECL|macro|FM_SRES0
mdefine_line|#define FM_SRES0&t;0x0001&t;&t;/* reserved */
DECL|macro|FM_SESTRIPTK
mdefine_line|#define FM_SESTRIPTK&t;0x0001&t;&t;/* SN3: &squot;no description&squot; */
DECL|macro|FM_STRTEXR
mdefine_line|#define FM_STRTEXR&t;0x0002&t;&t;/* TRT expired in claim | beacon st. */
DECL|macro|FM_SDUPCLM
mdefine_line|#define FM_SDUPCLM&t;0x0004&t;&t;/* duplicate claim received */
DECL|macro|FM_SSIFG
mdefine_line|#define FM_SSIFG&t;0x0008&t;&t;/* short interframe gap */
DECL|macro|FM_SFRMCTR
mdefine_line|#define FM_SFRMCTR&t;0x0010&t;&t;/* frame counter overflow */
DECL|macro|FM_SERRCTR
mdefine_line|#define FM_SERRCTR&t;0x0020&t;&t;/* error counter overflow */
DECL|macro|FM_SLSTCTR
mdefine_line|#define FM_SLSTCTR&t;0x0040&t;&t;/* lost counter overflow */
DECL|macro|FM_SPHINV
mdefine_line|#define FM_SPHINV&t;0x0080&t;&t;/* PHY invalid */
DECL|macro|FM_SADET
mdefine_line|#define FM_SADET&t;0x0100&t;&t;/* address detect */
DECL|macro|FM_SMISFRM
mdefine_line|#define FM_SMISFRM&t;0x0200&t;&t;/* missed frame */
DECL|macro|FM_STRTEXP
mdefine_line|#define FM_STRTEXP&t;0x0400&t;&t;/* TRT expired and late count &gt; 0 */
DECL|macro|FM_STVXEXP
mdefine_line|#define FM_STVXEXP&t;0x0800&t;&t;/* TVX expired */
DECL|macro|FM_STKISS
mdefine_line|#define FM_STKISS&t;0x1000&t;&t;/* token issued */
DECL|macro|FM_STKERR
mdefine_line|#define FM_STKERR&t;0x2000&t;&t;/* token error */
DECL|macro|FM_SMULTDA
mdefine_line|#define FM_SMULTDA&t;0x4000&t;&t;/* multiple destination address */
DECL|macro|FM_SRNGOP
mdefine_line|#define FM_SRNGOP&t;0x8000&t;&t;/* ring operational */
multiline_comment|/*&n; * Supernet 3:&n; * Status Register 3, Upper 16 Bits (ST3U)&n; */
DECL|macro|FM_SRQUNLCK1
mdefine_line|#define&t;FM_SRQUNLCK1&t;0x0001&t;&t;/* receive queue unlocked queue 1 */
DECL|macro|FM_SRQUNLCK2
mdefine_line|#define&t;FM_SRQUNLCK2&t;0x0002&t;&t;/* receive queue unlocked queue 2 */
DECL|macro|FM_SRPERRQ1
mdefine_line|#define&t;FM_SRPERRQ1&t;0x0004&t;&t;/* receive parity error rx queue 1 */
DECL|macro|FM_SRPERRQ2
mdefine_line|#define&t;FM_SRPERRQ2&t;0x0008&t;&t;/* receive parity error rx queue 2 */
multiline_comment|/* Bit 4-10: reserved */
DECL|macro|FM_SRCVOVR2
mdefine_line|#define&t;FM_SRCVOVR2&t;0x0800&t;&t;/* receive FIFO overfull rx queue 2 */
DECL|macro|FM_SRBFL2
mdefine_line|#define&t;FM_SRBFL2&t;0x1000&t;&t;/* receive buffer full rx queue 2 */
DECL|macro|FM_SRABT2
mdefine_line|#define&t;FM_SRABT2&t;0x2000&t;&t;/* receive abort rx queue 2 */
DECL|macro|FM_SRBMT2
mdefine_line|#define&t;FM_SRBMT2&t;0x4000&t;&t;/* receive buf empty rx queue 2 */
DECL|macro|FM_SRCOMP2
mdefine_line|#define&t;FM_SRCOMP2&t;0x8000&t;&t;/* receive comp rx queue 2 */
multiline_comment|/*&n; * Supernet 3:&n; * Status Register 3, Lower 16 Bits (ST3L)&n; */
DECL|macro|FM_AF_BIST_DONE
mdefine_line|#define&t;FM_AF_BIST_DONE&t;&t;0x0001&t;/* Address Filter BIST is done */
DECL|macro|FM_PLC_BIST_DONE
mdefine_line|#define&t;FM_PLC_BIST_DONE&t;0x0002&t;/* internal PLC Bist is done */
DECL|macro|FM_PDX_BIST_DONE
mdefine_line|#define&t;FM_PDX_BIST_DONE&t;0x0004&t;/* PDX BIST is done */
multiline_comment|/* Bit  3: reserved */
DECL|macro|FM_SICAMDAMAT
mdefine_line|#define&t;FM_SICAMDAMAT&t;&t;0x0010&t;/* Status internal CAM DA match */
DECL|macro|FM_SICAMDAXACT
mdefine_line|#define&t;FM_SICAMDAXACT&t;&t;0x0020&t;/* Status internal CAM DA exact match */
DECL|macro|FM_SICAMSAMAT
mdefine_line|#define&t;FM_SICAMSAMAT&t;&t;0x0040&t;/* Status internal CAM SA match */
DECL|macro|FM_SICAMSAXACT
mdefine_line|#define&t;FM_SICAMSAXACT&t;&t;0x0080&t;/* Status internal CAM SA exact match */
multiline_comment|/*&n; * MAC State-Machine Register FM_STMCHN&n; */
DECL|macro|FM_MDRTAG
mdefine_line|#define&t;FM_MDRTAG&t;0x0004&t;&t;/* tag bit of long word read */
DECL|macro|FM_SNPPND
mdefine_line|#define&t;FM_SNPPND&t;0x0008&t;&t;/* r/w from buffer mem. is pending */
DECL|macro|FM_TXSTAT
mdefine_line|#define&t;FM_TXSTAT&t;0x0070&t;&t;/* transmitter state machine state */
DECL|macro|FM_RCSTAT
mdefine_line|#define&t;FM_RCSTAT&t;0x0380&t;&t;/* receiver state machine state */
DECL|macro|FM_TM01
mdefine_line|#define&t;FM_TM01&t;&t;0x0c00&t;&t;/* indicate token mode */
DECL|macro|FM_SIM
mdefine_line|#define&t;FM_SIM&t;&t;0x1000&t;&t;/* indicate send immediate-mode */
DECL|macro|FM_REV
mdefine_line|#define&t;FM_REV&t;&t;0xe000&t;&t;/* FORMAC Plus revision number */
multiline_comment|/*&n; * Supernet 3&n; * Mode Register 3&n; */
DECL|macro|FM_MENRS
mdefine_line|#define&t;FM_MENRS&t;0x0001&t;&t;/* Ena enhanced rec status encoding */
DECL|macro|FM_MENXS
mdefine_line|#define&t;FM_MENXS&t;0x0002&t;&t;/* Ena enhanced xmit status encoding */
DECL|macro|FM_MENXCT
mdefine_line|#define&t;FM_MENXCT&t;0x0004&t;&t;/* Ena EXACT/INEXACT matching */
DECL|macro|FM_MENAFULL
mdefine_line|#define&t;FM_MENAFULL&t;0x0008&t;&t;/* Ena enh QCTRL encoding for AFULL */
DECL|macro|FM_MEIND
mdefine_line|#define&t;FM_MEIND&t;0x0030&t;&t;/* Ena enh A,C indicator settings */
DECL|macro|FM_MENQCTRL
mdefine_line|#define&t;FM_MENQCTRL&t;0x0040&t;&t;/* Ena enh QCTRL encoding */
DECL|macro|FM_MENRQAUNLCK
mdefine_line|#define&t;FM_MENRQAUNLCK&t;0x0080&t;&t;/* Ena rec q auto unlock */
DECL|macro|FM_MENDAS
mdefine_line|#define&t;FM_MENDAS&t;0x0100&t;&t;/* Ena DAS connections by cntr MUX */
DECL|macro|FM_MENPLCCST
mdefine_line|#define&t;FM_MENPLCCST&t;0x0200&t;&t;/* Ena Counter Segm test in PLC blck */
DECL|macro|FM_MENSGLINT
mdefine_line|#define&t;FM_MENSGLINT&t;0x0400&t;&t;/* Ena Vectored Interrupt reading */
DECL|macro|FM_MENDRCV
mdefine_line|#define&t;FM_MENDRCV&t;0x0800&t;&t;/* Ena dual receive queue operation */
DECL|macro|FM_MENFCLOC
mdefine_line|#define&t;FM_MENFCLOC&t;0x3000&t;&t;/* Ena FC location within frm data */
DECL|macro|FM_MENTRCMD
mdefine_line|#define&t;FM_MENTRCMD&t;0x4000&t;&t;/* Ena ASYNC1 xmit only after command */
DECL|macro|FM_MENTDLPBK
mdefine_line|#define&t;FM_MENTDLPBK&t;0x8000&t;&t;/* Ena TDAT to RDAT lkoopback */
multiline_comment|/*&n; * Supernet 3&n; * Frame Selection Register&n; */
DECL|macro|FM_RECV1
mdefine_line|#define&t;FM_RECV1&t;0x000f&t;&t;/* options for receive queue 1 */
DECL|macro|FM_RCV1_ALL
mdefine_line|#define&t;FM_RCV1_ALL&t;(0&lt;&lt;0)&t;&t;/* receive all frames */
DECL|macro|FM_RCV1_LLC
mdefine_line|#define&t;FM_RCV1_LLC&t;(1&lt;&lt;0)&t;&t;/* rec all LLC frames */
DECL|macro|FM_RCV1_SMT
mdefine_line|#define&t;FM_RCV1_SMT&t;(2&lt;&lt;0)&t;&t;/* rec all SMT frames */
DECL|macro|FM_RCV1_NSMT
mdefine_line|#define&t;FM_RCV1_NSMT&t;(3&lt;&lt;0)&t;&t;/* rec non-SMT frames */
DECL|macro|FM_RCV1_IMP
mdefine_line|#define&t;FM_RCV1_IMP&t;(4&lt;&lt;0)&t;&t;/* rec Implementor frames */
DECL|macro|FM_RCV1_MAC
mdefine_line|#define&t;FM_RCV1_MAC&t;(5&lt;&lt;0)&t;&t;/* rec all MAC frames */
DECL|macro|FM_RCV1_SLLC
mdefine_line|#define&t;FM_RCV1_SLLC&t;(6&lt;&lt;0)&t;&t;/* rec all sync LLC frames */
DECL|macro|FM_RCV1_ALLC
mdefine_line|#define&t;FM_RCV1_ALLC&t;(7&lt;&lt;0)&t;&t;/* rec all async LLC frames */
DECL|macro|FM_RCV1_VOID
mdefine_line|#define&t;FM_RCV1_VOID&t;(8&lt;&lt;0)&t;&t;/* rec all void frames */
DECL|macro|FM_RCV1_ALSMT
mdefine_line|#define&t;FM_RCV1_ALSMT&t;(9&lt;&lt;0)&t;&t;/* rec all async LLC &amp; SMT frames */
DECL|macro|FM_RECV2
mdefine_line|#define&t;FM_RECV2&t;0x00f0&t;&t;/* options for receive queue 2 */
DECL|macro|FM_RCV2_ALL
mdefine_line|#define&t;FM_RCV2_ALL&t;(0&lt;&lt;4)&t;&t;/* receive all other frames */
DECL|macro|FM_RCV2_LLC
mdefine_line|#define&t;FM_RCV2_LLC&t;(1&lt;&lt;4)&t;&t;/* rec all LLC frames */
DECL|macro|FM_RCV2_SMT
mdefine_line|#define&t;FM_RCV2_SMT&t;(2&lt;&lt;4)&t;&t;/* rec all SMT frames */
DECL|macro|FM_RCV2_NSMT
mdefine_line|#define&t;FM_RCV2_NSMT&t;(3&lt;&lt;4)&t;&t;/* rec non-SMT frames */
DECL|macro|FM_RCV2_IMP
mdefine_line|#define&t;FM_RCV2_IMP&t;(4&lt;&lt;4)&t;&t;/* rec Implementor frames */
DECL|macro|FM_RCV2_MAC
mdefine_line|#define&t;FM_RCV2_MAC&t;(5&lt;&lt;4)&t;&t;/* rec all MAC frames */
DECL|macro|FM_RCV2_SLLC
mdefine_line|#define&t;FM_RCV2_SLLC&t;(6&lt;&lt;4)&t;&t;/* rec all sync LLC frames */
DECL|macro|FM_RCV2_ALLC
mdefine_line|#define&t;FM_RCV2_ALLC&t;(7&lt;&lt;4)&t;&t;/* rec all async LLC frames */
DECL|macro|FM_RCV2_VOID
mdefine_line|#define&t;FM_RCV2_VOID&t;(8&lt;&lt;4)&t;&t;/* rec all void frames */
DECL|macro|FM_RCV2_ALSMT
mdefine_line|#define&t;FM_RCV2_ALSMT&t;(9&lt;&lt;4)&t;&t;/* rec all async LLC &amp; SMT frames */
DECL|macro|FM_ENXMTADSWAP
mdefine_line|#define&t;FM_ENXMTADSWAP&t;0x4000&t;&t;/* enh rec addr swap (phys -&gt; can) */
DECL|macro|FM_ENRCVADSWAP
mdefine_line|#define&t;FM_ENRCVADSWAP&t;0x8000&t;&t;/* enh tx addr swap (can -&gt; phys) */
multiline_comment|/*&n; * Supernet 3:&n; * Address Filter Command Register (AFCMD)&n; */
DECL|macro|FM_INST
mdefine_line|#define&t;FM_INST&t;&t;0x0007&t;&t;/* Address Filter Operation */
DECL|macro|FM_IINV_CAM
mdefine_line|#define FM_IINV_CAM&t;(0&lt;&lt;0)&t;&t;/* Invalidate CAM */
DECL|macro|FM_IWRITE_CAM
mdefine_line|#define FM_IWRITE_CAM&t;(1&lt;&lt;0)&t;&t;/* Write CAM */
DECL|macro|FM_IREAD_CAM
mdefine_line|#define FM_IREAD_CAM&t;(2&lt;&lt;0)&t;&t;/* Read CAM */
DECL|macro|FM_IRUN_BIST
mdefine_line|#define FM_IRUN_BIST&t;(3&lt;&lt;0)&t;&t;/* Run BIST */
DECL|macro|FM_IFIND
mdefine_line|#define FM_IFIND&t;(4&lt;&lt;0)&t;&t;/* Find */
DECL|macro|FM_IINV
mdefine_line|#define FM_IINV&t;&t;(5&lt;&lt;0)&t;&t;/* Invalidate */
DECL|macro|FM_ISKIP
mdefine_line|#define FM_ISKIP&t;(6&lt;&lt;0)&t;&t;/* Skip */
DECL|macro|FM_ICL_SKIP
mdefine_line|#define FM_ICL_SKIP&t;(7&lt;&lt;0)&t;&t;/* Clear all SKIP bits */
multiline_comment|/*&n; * Supernet 3:&n; * Address Filter Status Register (AFSTAT)&n; */
multiline_comment|/* Bit  0-4: reserved */
DECL|macro|FM_REV_NO
mdefine_line|#define&t;FM_REV_NO&t;0x00e0&t;&t;/* Revision Number of Address Filter */
DECL|macro|FM_BIST_DONE
mdefine_line|#define&t;FM_BIST_DONE&t;0x0100&t;&t;/* BIST complete */
DECL|macro|FM_EMPTY
mdefine_line|#define&t;FM_EMPTY&t;0x0200&t;&t;/* CAM empty */
DECL|macro|FM_ERROR
mdefine_line|#define&t;FM_ERROR&t;0x0400&t;&t;/* Error (improper operation) */
DECL|macro|FM_MULT
mdefine_line|#define&t;FM_MULT&t;&t;0x0800&t;&t;/* Multiple Match */
DECL|macro|FM_EXACT
mdefine_line|#define&t;FM_EXACT&t;0x1000&t;&t;/* Exact Match */
DECL|macro|FM_FOUND
mdefine_line|#define&t;FM_FOUND&t;0x2000&t;&t;/* Comparand found in CAM */
DECL|macro|FM_FULL
mdefine_line|#define&t;FM_FULL&t;&t;0x4000&t;&t;/* CAM full */
DECL|macro|FM_DONE
mdefine_line|#define&t;FM_DONE&t;&t;0x8000&t;&t;/* DONE indicator */
multiline_comment|/*&n; * Supernet 3:&n; * BIST Signature Register (AFBIST)&n; */
DECL|macro|AF_BIST_SIGNAT
mdefine_line|#define&t;AF_BIST_SIGNAT&t;0x0553&t;&t;/* Address Filter BIST Signature */
multiline_comment|/*&n; * Supernet 3:&n; * Personality Register (AFPERS)&n; */
DECL|macro|FM_VALID
mdefine_line|#define&t;FM_VALID&t;0x0001&t;&t;/* CAM Entry Valid */
DECL|macro|FM_DA
mdefine_line|#define&t;FM_DA&t;&t;0x0002&t;&t;/* Destination Address */
DECL|macro|FM_DAX
mdefine_line|#define&t;FM_DAX&t;&t;0x0004&t;&t;/* Destination Address Exact */
DECL|macro|FM_SA
mdefine_line|#define&t;FM_SA&t;&t;0x0008&t;&t;/* Source Address */
DECL|macro|FM_SAX
mdefine_line|#define&t;FM_SAX&t;&t;0x0010&t;&t;/* Source Address Exact */
DECL|macro|FM_SKIP
mdefine_line|#define&t;FM_SKIP&t;&t;0x0020&t;&t;/* Skip this entry */
multiline_comment|/*&n; * instruction set for command register 1 (NPADDR6-0 = 0x00)&n; */
DECL|macro|FM_IRESET
mdefine_line|#define FM_IRESET&t;0x01&t;&t;/* software reset */
DECL|macro|FM_IRMEMWI
mdefine_line|#define FM_IRMEMWI&t;0x02&t;&t;/* load Memory Data Reg., inc MARR */
DECL|macro|FM_IRMEMWO
mdefine_line|#define FM_IRMEMWO&t;0x03&t;&t;/* load MDR from buffer memory, n.i. */
DECL|macro|FM_IIL
mdefine_line|#define FM_IIL&t;&t;0x04&t;&t;/* idle/listen */
DECL|macro|FM_ICL
mdefine_line|#define FM_ICL&t;&t;0x05&t;&t;/* claim/listen */
DECL|macro|FM_IBL
mdefine_line|#define FM_IBL&t;&t;0x06&t;&t;/* beacon/listen */
DECL|macro|FM_ILTVX
mdefine_line|#define FM_ILTVX&t;0x07&t;&t;/* load TVX timer from TVX reg */
DECL|macro|FM_INRTM
mdefine_line|#define FM_INRTM&t;0x08&t;&t;/* nonrestricted token mode */
DECL|macro|FM_IENTM
mdefine_line|#define FM_IENTM&t;0x09&t;&t;/* enter nonrestricted token mode */
DECL|macro|FM_IERTM
mdefine_line|#define FM_IERTM&t;0x0a&t;&t;/* enter restricted token mode */
DECL|macro|FM_IRTM
mdefine_line|#define FM_IRTM&t;&t;0x0b&t;&t;/* restricted token mode */
DECL|macro|FM_ISURT
mdefine_line|#define FM_ISURT&t;0x0c&t;&t;/* send unrestricted token */
DECL|macro|FM_ISRT
mdefine_line|#define FM_ISRT&t;&t;0x0d&t;&t;/* send restricted token */
DECL|macro|FM_ISIM
mdefine_line|#define FM_ISIM&t;&t;0x0e&t;&t;/* enter send-immediate mode */
DECL|macro|FM_IESIM
mdefine_line|#define FM_IESIM&t;0x0f&t;&t;/* exit send-immediate mode */
DECL|macro|FM_ICLLS
mdefine_line|#define FM_ICLLS&t;0x11&t;&t;/* clear synchronous queue lock */
DECL|macro|FM_ICLLA0
mdefine_line|#define FM_ICLLA0&t;0x12&t;&t;/* clear asynchronous queue 0 lock */
DECL|macro|FM_ICLLA1
mdefine_line|#define FM_ICLLA1&t;0x14&t;&t;/* clear asynchronous queue 1 lock */
DECL|macro|FM_ICLLA2
mdefine_line|#define FM_ICLLA2&t;0x18&t;&t;/* clear asynchronous queue 2 lock */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_ICLLR
mdefine_line|#define FM_ICLLR&t;0x20&t;&t;/* clear receive queue (SN3:1) lock */
DECL|macro|FM_ICLLR2
mdefine_line|#define FM_ICLLR2&t;0x21&t;&t;/* SN3: clear receive queue 2 lock */
DECL|macro|FM_ITRXBUS
mdefine_line|#define FM_ITRXBUS&t;0x22&t;&t;/* SN3: Tristate X-Bus (SAS only) */
DECL|macro|FM_IDRXBUS
mdefine_line|#define FM_IDRXBUS&t;0x23&t;&t;/* SN3: drive X-Bus */
DECL|macro|FM_ICLLAL
mdefine_line|#define FM_ICLLAL&t;0x3f&t;&t;/* clear all queue locks */
multiline_comment|/*&n; * instruction set for command register 2 (NPADDR6-0 = 0x01)&n; */
DECL|macro|FM_ITRS
mdefine_line|#define FM_ITRS&t;&t;0x01&t;&t;/* transmit synchronous queue */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_ITRA0
mdefine_line|#define FM_ITRA0&t;0x02&t;&t;/* transmit asynchronous queue 0 */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_ITRA1
mdefine_line|#define FM_ITRA1&t;0x04&t;&t;/* transmit asynchronous queue 1 */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_ITRA2
mdefine_line|#define FM_ITRA2&t;0x08&t;&t;/* transmit asynchronous queue 2 */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_IACTR
mdefine_line|#define FM_IACTR&t;0x10&t;&t;/* abort current transmit activity */
DECL|macro|FM_IRSTQ
mdefine_line|#define FM_IRSTQ&t;0x20&t;&t;/* reset transmit queues */
DECL|macro|FM_ISTTB
mdefine_line|#define FM_ISTTB&t;0x30&t;&t;/* set tag bit */
DECL|macro|FM_IERSF
mdefine_line|#define FM_IERSF&t;0x40&t;&t;/* enable receive single frame */
multiline_comment|/* SN3: reserved */
DECL|macro|FM_ITR
mdefine_line|#define&t;FM_ITR&t;&t;0x50&t;&t;/* SN3: Transmit Command */
multiline_comment|/*&n; *&t;defines for PLC (Am79C864)&n; */
multiline_comment|/*&n; *  PLC read/write (r/w) registers&n; */
DECL|macro|PL_CNTRL_A
mdefine_line|#define PL_CNTRL_A&t;0x00&t;&t;/* control register A (r/w) */
DECL|macro|PL_CNTRL_B
mdefine_line|#define PL_CNTRL_B&t;0x01&t;&t;/* control register B (r/w) */
DECL|macro|PL_INTR_MASK
mdefine_line|#define PL_INTR_MASK&t;0x02&t;&t;/* interrupt mask (r/w) */
DECL|macro|PL_XMIT_VECTOR
mdefine_line|#define PL_XMIT_VECTOR&t;0x03&t;&t;/* transmit vector register (r/w) */
DECL|macro|PL_VECTOR_LEN
mdefine_line|#define PL_VECTOR_LEN&t;0x04&t;&t;/* transmit vector length (r/w) */
DECL|macro|PL_LE_THRESHOLD
mdefine_line|#define PL_LE_THRESHOLD&t;0x05&t;&t;/* link error event threshold (r/w) */
DECL|macro|PL_C_MIN
mdefine_line|#define PL_C_MIN&t;0x06&t;&t;/* minimum connect state time (r/w) */
DECL|macro|PL_TL_MIN
mdefine_line|#define PL_TL_MIN&t;0x07&t;&t;/* min. line state transmit t. (r/w) */
DECL|macro|PL_TB_MIN
mdefine_line|#define PL_TB_MIN&t;0x08&t;&t;/* minimum break time (r/w) */
DECL|macro|PL_T_OUT
mdefine_line|#define PL_T_OUT&t;0x09&t;&t;/* signal timeout (r/w) */
DECL|macro|PL_CNTRL_C
mdefine_line|#define PL_CNTRL_C&t;0x0a&t;&t;/* control register C (r/w) */
DECL|macro|PL_LC_LENGTH
mdefine_line|#define PL_LC_LENGTH&t;0x0b&t;&t;/* link confidence test time (r/w) */
DECL|macro|PL_T_SCRUB
mdefine_line|#define PL_T_SCRUB&t;0x0c&t;&t;/* scrub time = MAC TVX (r/w) */
DECL|macro|PL_NS_MAX
mdefine_line|#define PL_NS_MAX&t;0x0d&t;&t;/* max. noise time before break (r/w)*/
DECL|macro|PL_TPC_LOAD_V
mdefine_line|#define PL_TPC_LOAD_V&t;0x0e&t;&t;/* TPC timer load value (write only) */
DECL|macro|PL_TNE_LOAD_V
mdefine_line|#define PL_TNE_LOAD_V&t;0x0f&t;&t;/* TNE timer load value (write only) */
DECL|macro|PL_STATUS_A
mdefine_line|#define PL_STATUS_A&t;0x10&t;&t;/* status register A (read only) */
DECL|macro|PL_STATUS_B
mdefine_line|#define PL_STATUS_B&t;0x11&t;&t;/* status register B (read only) */
DECL|macro|PL_TPC
mdefine_line|#define PL_TPC&t;&t;0x12&t;&t;/* timer for PCM (ro) [20.48 us] */
DECL|macro|PL_TNE
mdefine_line|#define PL_TNE&t;&t;0x13&t;&t;/* time of noise event [0.32 us] */
DECL|macro|PL_CLK_DIV
mdefine_line|#define PL_CLK_DIV&t;0x14&t;&t;/* TNE clock divider (read only) */
DECL|macro|PL_BIST_SIGNAT
mdefine_line|#define PL_BIST_SIGNAT&t;0x15&t;&t;/* built in self test signature (ro)*/
DECL|macro|PL_RCV_VECTOR
mdefine_line|#define PL_RCV_VECTOR&t;0x16&t;&t;/* receive vector reg. (read only) */
DECL|macro|PL_INTR_EVENT
mdefine_line|#define PL_INTR_EVENT&t;0x17&t;&t;/* interrupt event reg. (read only) */
DECL|macro|PL_VIOL_SYM_CTR
mdefine_line|#define PL_VIOL_SYM_CTR&t;0x18&t;&t;/* violation symbol count. (read o) */
DECL|macro|PL_MIN_IDLE_CTR
mdefine_line|#define PL_MIN_IDLE_CTR&t;0x19&t;&t;/* minimum idle counter (read only) */
DECL|macro|PL_LINK_ERR_CTR
mdefine_line|#define PL_LINK_ERR_CTR&t;0x1a&t;&t;/* link error event ctr.(read only) */
macro_line|#ifdef&t;MOT_ELM
DECL|macro|PL_T_FOT_ASS
mdefine_line|#define&t;PL_T_FOT_ASS&t;0x1e&t;&t;/* FOTOFF Assert Timer */
DECL|macro|PL_T_FOT_DEASS
mdefine_line|#define&t;PL_T_FOT_DEASS&t;0x1f&t;&t;/* FOTOFF Deassert Timer */
macro_line|#endif&t;/* MOT_ELM */
macro_line|#ifdef&t;MOT_ELM
multiline_comment|/*&n; * Special Quad-Elm Registers.&n; * A Quad-ELM consists of for ELMs and these additional registers.&n; */
DECL|macro|QELM_XBAR_W
mdefine_line|#define&t;QELM_XBAR_W&t;0x80&t;&t;/* Crossbar Control ELM W */
DECL|macro|QELM_XBAR_X
mdefine_line|#define&t;QELM_XBAR_X&t;0x81&t;&t;/* Crossbar Control ELM X */
DECL|macro|QELM_XBAR_Y
mdefine_line|#define&t;QELM_XBAR_Y&t;0x82&t;&t;/* Crossbar Control ELM Y */
DECL|macro|QELM_XBAR_Z
mdefine_line|#define&t;QELM_XBAR_Z&t;0x83&t;&t;/* Crossbar Control ELM Z */
DECL|macro|QELM_XBAR_P
mdefine_line|#define&t;QELM_XBAR_P&t;0x84&t;&t;/* Crossbar Control Bus P */
DECL|macro|QELM_XBAR_S
mdefine_line|#define&t;QELM_XBAR_S&t;0x85&t;&t;/* Crossbar Control Bus S */
DECL|macro|QELM_XBAR_R
mdefine_line|#define&t;QELM_XBAR_R&t;0x86&t;&t;/* Crossbar Control Bus R */
DECL|macro|QELM_WR_XBAR
mdefine_line|#define&t;QELM_WR_XBAR&t;0x87&t;&t;/* Write the Crossbar now (write) */
DECL|macro|QELM_CTR_W
mdefine_line|#define&t;QELM_CTR_W&t;0x88&t;&t;/* Counter W */
DECL|macro|QELM_CTR_X
mdefine_line|#define&t;QELM_CTR_X&t;0x89&t;&t;/* Counter X */
DECL|macro|QELM_CTR_Y
mdefine_line|#define&t;QELM_CTR_Y&t;0x8a&t;&t;/* Counter Y */
DECL|macro|QELM_CTR_Z
mdefine_line|#define&t;QELM_CTR_Z&t;0x8b&t;&t;/* Counter Z */
DECL|macro|QELM_INT_MASK
mdefine_line|#define&t;QELM_INT_MASK&t;0x8c&t;&t;/* Interrupt mask register */
DECL|macro|QELM_INT_DATA
mdefine_line|#define&t;QELM_INT_DATA&t;0x8d&t;&t;/* Interrupt data (event) register */
DECL|macro|QELM_ELMB
mdefine_line|#define&t;QELM_ELMB&t;0x00&t;&t;/* Elm base */
DECL|macro|QELM_ELM_SIZE
mdefine_line|#define&t;QELM_ELM_SIZE&t;0x20&t;&t;/* ELM size */
macro_line|#endif&t;/* MOT_ELM */
multiline_comment|/*&n; * PLC control register A (PL_CNTRL_A: log. addr. 0x00)&n; * It is used for timer configuration, specification of PCM MAINT state option,&n; * counter interrupt frequency, PLC data path config. and Built In Self Test.&n; */
DECL|macro|PL_RUN_BIST
mdefine_line|#define&t;PL_RUN_BIST&t;0x0001&t;&t;/* begin running its Built In Self T.*/
DECL|macro|PL_RF_DISABLE
mdefine_line|#define&t;PL_RF_DISABLE&t;0x0002&t;&t;/* disable the Repeat Filter state m.*/
DECL|macro|PL_SC_REM_LOOP
mdefine_line|#define&t;PL_SC_REM_LOOP&t;0x0004&t;&t;/* remote loopback path */
DECL|macro|PL_SC_BYPASS
mdefine_line|#define&t;PL_SC_BYPASS&t;0x0008&t;&t;/* by providing a physical bypass */
DECL|macro|PL_LM_LOC_LOOP
mdefine_line|#define&t;PL_LM_LOC_LOOP&t;0x0010&t;&t;/* loop path just after elastic buff.*/
DECL|macro|PL_EB_LOC_LOOP
mdefine_line|#define&t;PL_EB_LOC_LOOP&t;0x0020&t;&t;/* loop path just prior to PDT/PDR IF*/
DECL|macro|PL_FOT_OFF
mdefine_line|#define&t;PL_FOT_OFF&t;0x0040&t;&t;/* assertion of /FOTOFF pin of PLC */
DECL|macro|PL_LOOPBACK
mdefine_line|#define&t;PL_LOOPBACK&t;0x0080&t;&t;/* it cause the /LPBCK pin ass. low */
DECL|macro|PL_MINI_CTR_INT
mdefine_line|#define&t;PL_MINI_CTR_INT 0x0100&t;&t;/* partially contr. when bit is ass. */
DECL|macro|PL_VSYM_CTR_INT
mdefine_line|#define&t;PL_VSYM_CTR_INT&t;0x0200&t;&t;/* controls when int bit is asserted */
DECL|macro|PL_ENA_PAR_CHK
mdefine_line|#define&t;PL_ENA_PAR_CHK&t;0x0400&t;&t;/* enable parity check */
DECL|macro|PL_REQ_SCRUB
mdefine_line|#define&t;PL_REQ_SCRUB&t;0x0800&t;&t;/* limited access to scrub capability*/
DECL|macro|PL_TPC_16BIT
mdefine_line|#define&t;PL_TPC_16BIT&t;0x1000&t;&t;/* causes the TPC as a 16 bit timer */
DECL|macro|PL_TNE_16BIT
mdefine_line|#define&t;PL_TNE_16BIT&t;0x2000&t;&t;/* causes the TNE as a 16 bit timer */
DECL|macro|PL_NOISE_TIMER
mdefine_line|#define&t;PL_NOISE_TIMER&t;0x4000&t;&t;/* allows the noise timing function */
multiline_comment|/*&n; * PLC control register B (PL_CNTRL_B: log. addr. 0x01)&n; * It contains signals and requeste to direct the process of PCM and it is also&n; * used to control the Line State Match interrupt.&n; */
DECL|macro|PL_PCM_CNTRL
mdefine_line|#define&t;PL_PCM_CNTRL&t;0x0003&t;&t;/* control PCM state machine */
DECL|macro|PL_PCM_NAF
mdefine_line|#define&t;PL_PCM_NAF&t;(0)&t;&t;/* state is not affected */
DECL|macro|PL_PCM_START
mdefine_line|#define&t;PL_PCM_START&t;(1)&t;&t;/* goes to the BREAK state */
DECL|macro|PL_PCM_TRACE
mdefine_line|#define&t;PL_PCM_TRACE&t;(2)&t;&t;/* goes to the TRACE state */
DECL|macro|PL_PCM_STOP
mdefine_line|#define&t;PL_PCM_STOP&t;(3)&t;&t;/* goes to the OFF state */
DECL|macro|PL_MAINT
mdefine_line|#define&t;PL_MAINT&t;0x0004&t;&t;/* if OFF state --&gt; MAINT state */
DECL|macro|PL_LONG
mdefine_line|#define&t;PL_LONG&t;&t;0x0008&t;&t;/* perf. a long Link Confid.Test(LCT)*/
DECL|macro|PL_PC_JOIN
mdefine_line|#define&t;PL_PC_JOIN&t;0x0010&t;&t;/* if NEXT state --&gt; JOIN state */
DECL|macro|PL_PC_LOOP
mdefine_line|#define&t;PL_PC_LOOP&t;0x0060&t;&t;/* loopback used in the LCT */
DECL|macro|PL_NOLCT
mdefine_line|#define&t;PL_NOLCT&t;(0&lt;&lt;5)&t;&t;/* no LCT is performed */
DECL|macro|PL_TPDR
mdefine_line|#define&t;PL_TPDR&t;&t;(1&lt;&lt;5)&t;&t;/* PCM asserts transmit PDR */
DECL|macro|PL_TIDLE
mdefine_line|#define&t;PL_TIDLE&t;(2&lt;&lt;5)&t;&t;/* PCM asserts transmit idle */
DECL|macro|PL_RLBP
mdefine_line|#define&t;PL_RLBP&t;&t;(3&lt;&lt;5)&t;&t;/* trans. PDR &amp; remote loopb. path */
DECL|macro|PL_CLASS_S
mdefine_line|#define&t;PL_CLASS_S&t;0x0080&t;&t;/* signif. that single att. station */
DECL|macro|PL_MAINT_LS
mdefine_line|#define&t;PL_MAINT_LS&t;0x0700&t;&t;/* line state while in the MAINT st. */
DECL|macro|PL_M_QUI0
mdefine_line|#define&t;PL_M_QUI0&t;(0&lt;&lt;8)&t;&t;/* transmit QUIET line state */
DECL|macro|PL_M_IDLE
mdefine_line|#define&t;PL_M_IDLE&t;(1&lt;&lt;8)&t;&t;/* transmit IDLE line state */
DECL|macro|PL_M_HALT
mdefine_line|#define&t;PL_M_HALT&t;(2&lt;&lt;8)&t;&t;/* transmit HALT line state */
DECL|macro|PL_M_MASTR
mdefine_line|#define&t;PL_M_MASTR&t;(3&lt;&lt;8)&t;&t;/* transmit MASTER line state */
DECL|macro|PL_M_QUI1
mdefine_line|#define&t;PL_M_QUI1&t;(4&lt;&lt;8)&t;&t;/* transmit QUIET line state */
DECL|macro|PL_M_QUI2
mdefine_line|#define&t;PL_M_QUI2&t;(5&lt;&lt;8)&t;&t;/* transmit QUIET line state */
DECL|macro|PL_M_TPDR
mdefine_line|#define&t;PL_M_TPDR&t;(6&lt;&lt;8)&t;&t;/* tr. PHY_DATA requ.-symbol is tr.ed*/
DECL|macro|PL_M_QUI3
mdefine_line|#define&t;PL_M_QUI3&t;(7&lt;&lt;8)&t;&t;/* transmit QUIET line state */
DECL|macro|PL_MATCH_LS
mdefine_line|#define&t;PL_MATCH_LS&t;0x7800&t;&t;/* line state to be comp. with curr.*/
DECL|macro|PL_I_ANY
mdefine_line|#define&t;PL_I_ANY&t;(0&lt;&lt;11)&t;&t;/* Int. on any change in *_LINE_ST */
DECL|macro|PL_I_IDLE
mdefine_line|#define&t;PL_I_IDLE&t;(1&lt;&lt;11)&t;&t;/* Interrupt on IDLE line state */
DECL|macro|PL_I_HALT
mdefine_line|#define&t;PL_I_HALT&t;(2&lt;&lt;11)&t;&t;/* Interrupt on HALT line state */
DECL|macro|PL_I_MASTR
mdefine_line|#define&t;PL_I_MASTR&t;(4&lt;&lt;11)&t;&t;/* Interrupt on MASTER line state */
DECL|macro|PL_I_QUIET
mdefine_line|#define&t;PL_I_QUIET&t;(8&lt;&lt;11)&t;&t;/* Interrupt on QUIET line state */
DECL|macro|PL_CONFIG_CNTRL
mdefine_line|#define&t;PL_CONFIG_CNTRL&t;0x8000&t;&t;/* control over scrub, byp. &amp; loopb.*/
multiline_comment|/*&n; * PLC control register C (PL_CNTRL_C: log. addr. 0x0a)&n; * It contains the scrambling control registers (PLC-S only)&n; */
DECL|macro|PL_C_CIPHER_ENABLE
mdefine_line|#define PL_C_CIPHER_ENABLE&t;(1&lt;&lt;0)&t;/* enable scrambler */
DECL|macro|PL_C_CIPHER_LPBCK
mdefine_line|#define PL_C_CIPHER_LPBCK&t;(1&lt;&lt;1)&t;/* loopback scrambler */
DECL|macro|PL_C_SDOFF_ENABLE
mdefine_line|#define PL_C_SDOFF_ENABLE&t;(1&lt;&lt;6)&t;/* enable SDOFF timer */
DECL|macro|PL_C_SDON_ENABLE
mdefine_line|#define PL_C_SDON_ENABLE&t;(1&lt;&lt;7)&t;/* enable SDON timer */
macro_line|#ifdef&t;MOT_ELM
DECL|macro|PL_C_FOTOFF_CTRL
mdefine_line|#define PL_C_FOTOFF_CTRL&t;(3&lt;&lt;2)&t;/* FOTOFF timer control */
DECL|macro|PL_C_FOTOFF_TIM
mdefine_line|#define PL_C_FOTOFF_TIM&t;&t;(0&lt;&lt;2)&t;/* FOTOFF use timer for (de)-assert */
DECL|macro|PL_C_FOTOFF_INA
mdefine_line|#define PL_C_FOTOFF_INA&t;&t;(2&lt;&lt;2)&t;/* FOTOFF forced inactive */
DECL|macro|PL_C_FOTOFF_ACT
mdefine_line|#define PL_C_FOTOFF_ACT&t;&t;(3&lt;&lt;2)&t;/* FOTOFF forced active */
DECL|macro|PL_C_FOTOFF_SRCE
mdefine_line|#define PL_C_FOTOFF_SRCE&t;(1&lt;&lt;4)&t;/* FOTOFF source is PCM state != OFF */
DECL|macro|PL_C_RXDATA_EN
mdefine_line|#define&t;PL_C_RXDATA_EN&t;&t;(1&lt;&lt;5)&t;/* Rec scr data forced to 0 */
DECL|macro|PL_C_SDNRZEN
mdefine_line|#define&t;PL_C_SDNRZEN&t;&t;(1&lt;&lt;8)&t;/* Monitor rec descr. data for act */
macro_line|#else&t;/* nMOT_ELM */
DECL|macro|PL_C_FOTOFF_CTRL
mdefine_line|#define PL_C_FOTOFF_CTRL&t;(3&lt;&lt;8)&t;/* FOTOFF timer control */
DECL|macro|PL_C_FOTOFF_0
mdefine_line|#define PL_C_FOTOFF_0&t;&t;(0&lt;&lt;8)&t;/* timer off */
DECL|macro|PL_C_FOTOFF_30
mdefine_line|#define PL_C_FOTOFF_30&t;&t;(1&lt;&lt;8)&t;/* 30uS */
DECL|macro|PL_C_FOTOFF_50
mdefine_line|#define PL_C_FOTOFF_50&t;&t;(2&lt;&lt;8)&t;/* 50uS */
DECL|macro|PL_C_FOTOFF_NEVER
mdefine_line|#define PL_C_FOTOFF_NEVER&t;(3&lt;&lt;8)&t;/* never */
DECL|macro|PL_C_SDON_TIMER
mdefine_line|#define PL_C_SDON_TIMER&t;&t;(3&lt;&lt;10)&t;/* SDON timer control */
DECL|macro|PL_C_SDON_084
mdefine_line|#define PL_C_SDON_084&t;&t;(0&lt;&lt;10)&t;/* 0.84 uS */
DECL|macro|PL_C_SDON_132
mdefine_line|#define PL_C_SDON_132&t;&t;(1&lt;&lt;10)&t;/* 1.32 uS */
DECL|macro|PL_C_SDON_252
mdefine_line|#define PL_C_SDON_252&t;&t;(2&lt;&lt;10)&t;/* 2.52 uS */
DECL|macro|PL_C_SDON_512
mdefine_line|#define PL_C_SDON_512&t;&t;(3&lt;&lt;10)&t;/* 5.12 uS */
DECL|macro|PL_C_SOFF_TIMER
mdefine_line|#define PL_C_SOFF_TIMER&t;&t;(3&lt;&lt;12)&t;/* SDOFF timer control */
DECL|macro|PL_C_SOFF_076
mdefine_line|#define PL_C_SOFF_076&t;&t;(0&lt;&lt;12)&t;/* 0.76 uS */
DECL|macro|PL_C_SOFF_132
mdefine_line|#define PL_C_SOFF_132&t;&t;(1&lt;&lt;12)&t;/* 1.32 uS */
DECL|macro|PL_C_SOFF_252
mdefine_line|#define PL_C_SOFF_252&t;&t;(2&lt;&lt;12)&t;/* 2.52 uS */
DECL|macro|PL_C_SOFF_512
mdefine_line|#define PL_C_SOFF_512&t;&t;(3&lt;&lt;12)&t;/* 5.12 uS */
DECL|macro|PL_C_TSEL
mdefine_line|#define PL_C_TSEL&t;&t;(3&lt;&lt;14)&t;/* scrambler path select */
macro_line|#endif&t;/* nMOT_ELM */
multiline_comment|/*&n; * PLC status register A (PL_STATUS_A: log. addr. 0x10)&n; * It is used to report status information to the Node Processor about the &n; * Line State Machine (LSM).&n; */
macro_line|#ifdef&t;MOT_ELM
DECL|macro|PLC_INT_MASK
mdefine_line|#define PLC_INT_MASK&t;0xc000&t;&t;/* ELM integration bits in status A */
DECL|macro|PLC_INT_C
mdefine_line|#define PLC_INT_C&t;0x0000&t;&t;/* ELM Revision Band C */
DECL|macro|PLC_INT_CAMEL
mdefine_line|#define PLC_INT_CAMEL&t;0x4000&t;&t;/* ELM integrated into CAMEL */
DECL|macro|PLC_INT_QE
mdefine_line|#define PLC_INT_QE&t;0x8000&t;&t;/* ELM integrated into Quad ELM */
DECL|macro|PLC_REV_MASK
mdefine_line|#define PLC_REV_MASK&t;0x3800&t;&t;/* revision bits in status A */
DECL|macro|PLC_REVISION_B
mdefine_line|#define PLC_REVISION_B&t;0x0000&t;&t;/* rev bits for ELM Rev B */
DECL|macro|PLC_REVISION_QA
mdefine_line|#define PLC_REVISION_QA&t;0x0800&t;&t;/* rev bits for ELM core in QELM-A */
macro_line|#else&t;/* nMOT_ELM */
DECL|macro|PLC_REV_MASK
mdefine_line|#define PLC_REV_MASK&t;0xf800&t;&t;/* revision bits in status A */
DECL|macro|PLC_REVISION_A
mdefine_line|#define PLC_REVISION_A&t;0x0000&t;&t;/* revision bits for PLC */
DECL|macro|PLC_REVISION_S
mdefine_line|#define PLC_REVISION_S&t;0xf800&t;&t;/* revision bits for PLC-S */
DECL|macro|PLC_REV_SN3
mdefine_line|#define PLC_REV_SN3&t;0x7800&t;&t;/* revision bits for PLC-S in IFCP */
macro_line|#endif&t;/* nMOT_ELM */
DECL|macro|PL_SYM_PR_CTR
mdefine_line|#define&t;PL_SYM_PR_CTR&t;0x0007&t;&t;/* contains the LSM symbol pair Ctr. */
DECL|macro|PL_UNKN_LINE_ST
mdefine_line|#define&t;PL_UNKN_LINE_ST&t;0x0008&t;&t;/* unknown line state bit from LSM */
DECL|macro|PL_LSM_STATE
mdefine_line|#define&t;PL_LSM_STATE&t;0x0010&t;&t;/* state bit of LSM */
DECL|macro|PL_LINE_ST
mdefine_line|#define&t;PL_LINE_ST&t;0x00e0&t;&t;/* contains recogn. line state of LSM*/
DECL|macro|PL_L_NLS
mdefine_line|#define&t;PL_L_NLS&t;(0&lt;&lt;5)&t;&t;/* noise line state */
DECL|macro|PL_L_ALS
mdefine_line|#define&t;PL_L_ALS&t;(1&lt;&lt;5)&t;&t;/* activ line state */
DECL|macro|PL_L_UND
mdefine_line|#define&t;PL_L_UND&t;(2&lt;&lt;5)&t;&t;/* undefined */
DECL|macro|PL_L_ILS4
mdefine_line|#define&t;PL_L_ILS4&t;(3&lt;&lt;5)&t;&t;/* idle l. s. (after 4 idle symbols) */
DECL|macro|PL_L_QLS
mdefine_line|#define&t;PL_L_QLS&t;(4&lt;&lt;5)&t;&t;/* quiet line state */
DECL|macro|PL_L_MLS
mdefine_line|#define&t;PL_L_MLS&t;(5&lt;&lt;5)&t;&t;/* master line state */
DECL|macro|PL_L_HLS
mdefine_line|#define&t;PL_L_HLS&t;(6&lt;&lt;5)&t;&t;/* halt line state */
DECL|macro|PL_L_ILS16
mdefine_line|#define&t;PL_L_ILS16&t;(7&lt;&lt;5)&t;&t;/* idle line state (after 16 idle s.)*/
DECL|macro|PL_PREV_LINE_ST
mdefine_line|#define&t;PL_PREV_LINE_ST&t;0x0300&t;&t;/* value of previous line state */
DECL|macro|PL_P_QLS
mdefine_line|#define&t;PL_P_QLS&t;(0&lt;&lt;8)&t;&t;/* quiet line state */
DECL|macro|PL_P_MLS
mdefine_line|#define&t;PL_P_MLS&t;(1&lt;&lt;8)&t;&t;/* master line state */
DECL|macro|PL_P_HLS
mdefine_line|#define&t;PL_P_HLS&t;(2&lt;&lt;8)&t;&t;/* halt line state */
DECL|macro|PL_P_ILS16
mdefine_line|#define&t;PL_P_ILS16&t;(3&lt;&lt;8)&t;&t;/* idle line state (after 16 idle s.)*/
DECL|macro|PL_SIGNAL_DET
mdefine_line|#define&t;PL_SIGNAL_DET&t;0x0400&t;&t;/* 1=that signal detect is deasserted*/
multiline_comment|/*&n; * PLC status register B (PL_STATUS_B: log. addr. 0x11)&n; * It contains signals and status from the repeat filter and PCM state machine.&n; */
DECL|macro|PL_BREAK_REASON
mdefine_line|#define&t;PL_BREAK_REASON&t;0x0007&t;&t;/* reason for PCM state mach.s to br.*/
DECL|macro|PL_B_NOT
mdefine_line|#define&t;PL_B_NOT&t;(0)&t;&t;/* PCM SM has not gone to BREAK state*/
DECL|macro|PL_B_PCS
mdefine_line|#define&t;PL_B_PCS&t;(1)&t;&t;/* PC_Start issued */
DECL|macro|PL_B_TPC
mdefine_line|#define&t;PL_B_TPC&t;(2)&t;&t;/* TPC timer expired after T_OUT */
DECL|macro|PL_B_TNE
mdefine_line|#define&t;PL_B_TNE&t;(3)&t;&t;/* TNE timer expired after NS_MAX */
DECL|macro|PL_B_QLS
mdefine_line|#define&t;PL_B_QLS&t;(4)&t;&t;/* quit line state detected */
DECL|macro|PL_B_ILS
mdefine_line|#define&t;PL_B_ILS&t;(5)&t;&t;/* idle line state detected */
DECL|macro|PL_B_HLS
mdefine_line|#define&t;PL_B_HLS&t;(6)&t;&t;/* halt line state detected */
DECL|macro|PL_TCF
mdefine_line|#define&t;PL_TCF&t;&t;0x0008&t;&t;/* transmit code flag (start exec.) */
DECL|macro|PL_RCF
mdefine_line|#define&t;PL_RCF&t;&t;0x0010&t;&t;/* receive code flag (start exec.) */
DECL|macro|PL_LSF
mdefine_line|#define&t;PL_LSF&t;&t;0x0020&t;&t;/* line state flag (l.s. has been r.)*/
DECL|macro|PL_PCM_SIGNAL
mdefine_line|#define&t;PL_PCM_SIGNAL&t;0x0040&t;&t;/* indic. that XMIT_VECTOR hb.written*/
DECL|macro|PL_PCM_STATE
mdefine_line|#define&t;PL_PCM_STATE&t;0x0780&t;&t;/* state bits of PCM state machine */
DECL|macro|PL_PC0
mdefine_line|#define&t;PL_PC0&t;&t;(0&lt;&lt;7)&t;&t;/* OFF&t;   - when /RST or PCM_CNTRL */
DECL|macro|PL_PC1
mdefine_line|#define&t;PL_PC1&t;&t;(1&lt;&lt;7)&t;&t;/* BREAK   - entry point in start PCM*/
DECL|macro|PL_PC2
mdefine_line|#define&t;PL_PC2&t;&t;(2&lt;&lt;7)&t;&t;/* TRACE   - to localize stuck Beacon*/
DECL|macro|PL_PC3
mdefine_line|#define&t;PL_PC3&t;&t;(3&lt;&lt;7)&t;&t;/* CONNECT - synchronize ends of conn*/
DECL|macro|PL_PC4
mdefine_line|#define&t;PL_PC4&t;&t;(4&lt;&lt;7)&t;&t;/* NEXT&t;   - to seperate the signalng*/
DECL|macro|PL_PC5
mdefine_line|#define&t;PL_PC5&t;&t;(5&lt;&lt;7)&t;&t;/* SIGNAL  - PCM trans/rec. bit infos*/
DECL|macro|PL_PC6
mdefine_line|#define&t;PL_PC6&t;&t;(6&lt;&lt;7)&t;&t;/* JOIN&t;   - 1. state to activ conn. */
DECL|macro|PL_PC7
mdefine_line|#define&t;PL_PC7&t;&t;(7&lt;&lt;7)&t;&t;/* VERIFY  - 2. - &quot; - (3. ACTIVE) */
DECL|macro|PL_PC8
mdefine_line|#define&t;PL_PC8&t;&t;(8&lt;&lt;7)&t;&t;/* ACTIVE  - PHY has been incorporated*/
DECL|macro|PL_PC9
mdefine_line|#define&t;PL_PC9&t;&t;(9&lt;&lt;7)&t;&t;/* MAINT   - for test purposes or so &n;&t;&t;&t;&t;&t;   that PCM op. completely in softw. */
DECL|macro|PL_PCI_SCRUB
mdefine_line|#define&t;PL_PCI_SCRUB&t;0x0800&t;&t;/* scrubbing function is being exec. */
DECL|macro|PL_PCI_STATE
mdefine_line|#define&t;PL_PCI_STATE&t;0x3000&t;&t;/* Physical Connect. Insertion SM */
DECL|macro|PL_CI_REMV
mdefine_line|#define&t;PL_CI_REMV&t;(0&lt;&lt;12)&t;&t;/* REMOVED */
DECL|macro|PL_CI_ISCR
mdefine_line|#define&t;PL_CI_ISCR&t;(1&lt;&lt;12)&t;&t;/* INSERT_SCRUB */
DECL|macro|PL_CI_RSCR
mdefine_line|#define&t;PL_CI_RSCR&t;(2&lt;&lt;12)&t;&t;/* REMOVE_SCRUB */
DECL|macro|PL_CI_INS
mdefine_line|#define&t;PL_CI_INS&t;(3&lt;&lt;12)&t;&t;/* INSERTED */
DECL|macro|PL_RF_STATE
mdefine_line|#define&t;PL_RF_STATE&t;0xc000&t;&t;/* state bit of repeate filter SM */
DECL|macro|PL_RF_REPT
mdefine_line|#define&t;PL_RF_REPT&t;(0&lt;&lt;14)&t;&t;/* REPEAT */
DECL|macro|PL_RF_IDLE
mdefine_line|#define&t;PL_RF_IDLE&t;(1&lt;&lt;14)&t;&t;/* IDLE */
DECL|macro|PL_RF_HALT1
mdefine_line|#define&t;PL_RF_HALT1&t;(2&lt;&lt;14)&t;&t;/* HALT1 */
DECL|macro|PL_RF_HALT2
mdefine_line|#define&t;PL_RF_HALT2&t;(3&lt;&lt;14)&t;&t;/* HALT2 */
multiline_comment|/*&n; * PLC interrupt event register (PL_INTR_EVENT: log. addr. 0x17)&n; * It is read only and is clearde whenever it is read!&n; * It is used by the PLC to report events to the node processor.&n; */
DECL|macro|PL_PARITY_ERR
mdefine_line|#define&t;PL_PARITY_ERR&t;0x0001&t;&t;/* p. error h.b.detected on TX9-0 inp*/
DECL|macro|PL_LS_MATCH
mdefine_line|#define&t;PL_LS_MATCH&t;0x0002&t;&t;/* l.s.== l.s. PLC_CNTRL_B&squot;s MATCH_LS*/
DECL|macro|PL_PCM_CODE
mdefine_line|#define&t;PL_PCM_CODE&t;0x0004&t;&t;/* transmit&amp;receive | LCT complete */
DECL|macro|PL_TRACE_PROP
mdefine_line|#define&t;PL_TRACE_PROP&t;0x0008&t;&t;/* master l.s. while PCM ACTIV|TRACE */
DECL|macro|PL_SELF_TEST
mdefine_line|#define&t;PL_SELF_TEST&t;0x0010&t;&t;/* QUIET|HALT while PCM in TRACE st. */
DECL|macro|PL_PCM_BREAK
mdefine_line|#define&t;PL_PCM_BREAK&t;0x0020&t;&t;/* PCM has entered the BREAK state */
DECL|macro|PL_PCM_ENABLED
mdefine_line|#define&t;PL_PCM_ENABLED&t;0x0040&t;&t;/* asserted SC_JOIN, scrub. &amp; ACTIV */
DECL|macro|PL_TPC_EXPIRED
mdefine_line|#define&t;PL_TPC_EXPIRED&t;0x0080&t;&t;/* TPC timer reached zero */
DECL|macro|PL_TNE_EXPIRED
mdefine_line|#define&t;PL_TNE_EXPIRED&t;0x0100&t;&t;/* TNE timer reached zero */
DECL|macro|PL_EBUF_ERR
mdefine_line|#define&t;PL_EBUF_ERR&t;0x0200&t;&t;/* elastic buff. det. over-|underflow*/
DECL|macro|PL_PHYINV
mdefine_line|#define&t;PL_PHYINV&t;0x0400&t;&t;/* physical layer invalid signal */
DECL|macro|PL_VSYM_CTR
mdefine_line|#define&t;PL_VSYM_CTR&t;0x0800&t;&t;/* violation symbol counter has incr.*/
DECL|macro|PL_MINI_CTR
mdefine_line|#define&t;PL_MINI_CTR&t;0x1000&t;&t;/* dep. on PLC_CNTRL_A&squot;s MINI_CTR_INT*/
DECL|macro|PL_LE_CTR
mdefine_line|#define&t;PL_LE_CTR&t;0x2000&t;&t;/* link error event counter */
DECL|macro|PL_LSDO
mdefine_line|#define&t;PL_LSDO&t;&t;0x4000&t;&t;/* SDO input pin changed to a 1 */
DECL|macro|PL_NP_ERR
mdefine_line|#define&t;PL_NP_ERR&t;0x8000&t;&t;/* NP has requested to r/w an inv. r.*/
multiline_comment|/*&n; * The PLC interrupt mask register (PL_INTR_MASK: log. addr. 0x02) constr. is&n; * equal PL_INTR_EVENT register.&n; * For each set bit, the setting of corresponding bit generate an int to NP. &n; */
macro_line|#ifdef&t;MOT_ELM
multiline_comment|/*&n; * Quad ELM Crosbar Control register values (QELM_XBAR_?)&n; */
DECL|macro|QELM_XOUT_IDLE
mdefine_line|#define&t;QELM_XOUT_IDLE&t;0x0000&t;&t;/* Idles/Passthrough */
DECL|macro|QELM_XOUT_P
mdefine_line|#define&t;QELM_XOUT_P&t;0x0001&t;&t;/* Output to: Bus P */
DECL|macro|QELM_XOUT_S
mdefine_line|#define&t;QELM_XOUT_S&t;0x0002&t;&t;/* Output to: Bus S */
DECL|macro|QELM_XOUT_R
mdefine_line|#define&t;QELM_XOUT_R&t;0x0003&t;&t;/* Output to: Bus R */
DECL|macro|QELM_XOUT_W
mdefine_line|#define&t;QELM_XOUT_W&t;0x0004&t;&t;/* Output to: ELM W */
DECL|macro|QELM_XOUT_X
mdefine_line|#define&t;QELM_XOUT_X&t;0x0005&t;&t;/* Output to: ELM X */
DECL|macro|QELM_XOUT_Y
mdefine_line|#define&t;QELM_XOUT_Y&t;0x0006&t;&t;/* Output to: ELM Y */
DECL|macro|QELM_XOUT_Z
mdefine_line|#define&t;QELM_XOUT_Z&t;0x0007&t;&t;/* Output to: ELM Z */
multiline_comment|/*&n; * Quad ELM Interrupt data and event registers.&n; */
DECL|macro|QELM_NP_ERR
mdefine_line|#define&t;QELM_NP_ERR&t;(1&lt;&lt;15)&t;&t;/* Node Processor Error */
DECL|macro|QELM_COUNT_Z
mdefine_line|#define&t;QELM_COUNT_Z&t;(1&lt;&lt;7)&t;&t;/* Counter Z Interrupt */
DECL|macro|QELM_COUNT_Y
mdefine_line|#define&t;QELM_COUNT_Y&t;(1&lt;&lt;6)&t;&t;/* Counter Y Interrupt */
DECL|macro|QELM_COUNT_X
mdefine_line|#define&t;QELM_COUNT_X&t;(1&lt;&lt;5)&t;&t;/* Counter X Interrupt */
DECL|macro|QELM_COUNT_W
mdefine_line|#define&t;QELM_COUNT_W&t;(1&lt;&lt;4)&t;&t;/* Counter W Interrupt */
DECL|macro|QELM_ELM_Z
mdefine_line|#define&t;QELM_ELM_Z&t;(1&lt;&lt;3)&t;&t;/* ELM Z Interrupt */
DECL|macro|QELM_ELM_Y
mdefine_line|#define&t;QELM_ELM_Y&t;(1&lt;&lt;2)&t;&t;/* ELM Y Interrupt */
DECL|macro|QELM_ELM_X
mdefine_line|#define&t;QELM_ELM_X&t;(1&lt;&lt;1)&t;&t;/* ELM X Interrupt */
DECL|macro|QELM_ELM_W
mdefine_line|#define&t;QELM_ELM_W&t;(1&lt;&lt;0)&t;&t;/* ELM W Interrupt */
macro_line|#endif&t;/* MOT_ELM */
multiline_comment|/*&n; * PLC Timing Parameters&n; */
DECL|macro|TP_C_MIN
mdefine_line|#define&t;TP_C_MIN&t;0xff9c&t;/*   2    ms */
DECL|macro|TP_TL_MIN
mdefine_line|#define&t;TP_TL_MIN&t;0xfff0&t;/*   0.3  ms */
DECL|macro|TP_TB_MIN
mdefine_line|#define&t;TP_TB_MIN&t;0xff10&t;/*   5    ms */
DECL|macro|TP_T_OUT
mdefine_line|#define&t;TP_T_OUT&t;0xd9db&t;/* 200    ms */
DECL|macro|TP_LC_LENGTH
mdefine_line|#define&t;TP_LC_LENGTH&t;0xf676&t;/*  50    ms */
DECL|macro|TP_LC_LONGLN
mdefine_line|#define&t;TP_LC_LONGLN&t;0xa0a2&t;/* 500    ms */
DECL|macro|TP_T_SCRUB
mdefine_line|#define&t;TP_T_SCRUB&t;0xff6d&t;/*   3.5  ms */
DECL|macro|TP_NS_MAX
mdefine_line|#define&t;TP_NS_MAX&t;0xf021&t;/*   1.3   ms */
multiline_comment|/*&n; * BIST values&n; */
DECL|macro|PLC_BIST
mdefine_line|#define PLC_BIST&t;0x6ecd&t;&t;/* BIST signature for PLC */
DECL|macro|PLCS_BIST
mdefine_line|#define PLCS_BIST&t;0x5b6b &t;&t;/* BIST signature for PLC-S */
DECL|macro|PLC_ELM_B_BIST
mdefine_line|#define&t;PLC_ELM_B_BIST&t;0x6ecd&t;&t;/* BIST signature of ELM Rev. B */
DECL|macro|PLC_ELM_D_BIST
mdefine_line|#define&t;PLC_ELM_D_BIST&t;0x5b6b&t;&t;/* BIST signature of ELM Rev. D */
DECL|macro|PLC_CAM_A_BIST
mdefine_line|#define&t;PLC_CAM_A_BIST&t;0x9e75&t;&t;/* BIST signature of CAMEL Rev. A */
DECL|macro|PLC_CAM_B_BIST
mdefine_line|#define&t;PLC_CAM_B_BIST&t;0x5b6b&t;&t;/* BIST signature of CAMEL Rev. B */
DECL|macro|PLC_IFD_A_BIST
mdefine_line|#define&t;PLC_IFD_A_BIST&t;0x9e75&t;&t;/* BIST signature of IFDDI Rev. A */
DECL|macro|PLC_IFD_B_BIST
mdefine_line|#define&t;PLC_IFD_B_BIST&t;0x5b6b&t;&t;/* BIST signature of IFDDI Rev. B */
DECL|macro|PLC_QELM_A_BIST
mdefine_line|#define&t;PLC_QELM_A_BIST&t;0x5b6b&t;&t;/* BIST signature of QELM Rev. A */
multiline_comment|/*&n; &t;FDDI board recources&t;&n; */
multiline_comment|/*&n; * request register array (log. addr: RQA_A + a&lt;&lt;1 {a=0..7}) write only.&n; * It specifies to FORMAC+ the type of buffer memory access the host requires.&n; */
DECL|macro|RQ_NOT
mdefine_line|#define&t;RQ_NOT&t;&t;0&t;&t;/* not request */
DECL|macro|RQ_RES
mdefine_line|#define&t;RQ_RES&t;&t;1&t;&t;/* reserved */
DECL|macro|RQ_SFW
mdefine_line|#define&t;RQ_SFW&t;&t;2&t;&t;/* special frame write */
DECL|macro|RQ_RRQ
mdefine_line|#define&t;RQ_RRQ&t;&t;3&t;&t;/* read request: receive queue */
DECL|macro|RQ_WSQ
mdefine_line|#define&t;RQ_WSQ&t;&t;4&t;&t;/* write request: synchronous queue */
DECL|macro|RQ_WA0
mdefine_line|#define&t;RQ_WA0&t;&t;5&t;&t;/* write requ.: asynchronous queue 0 */
DECL|macro|RQ_WA1
mdefine_line|#define&t;RQ_WA1&t;&t;6&t;&t;/* write requ.: asynchronous queue 1 */
DECL|macro|RQ_WA2
mdefine_line|#define&t;RQ_WA2&t;&t;7&t;&t;/* write requ.: asynchronous queue 2 */
DECL|macro|SZ_LONG
mdefine_line|#define&t;SZ_LONG&t;&t;(sizeof(long))
multiline_comment|/*&n; * FDDI defaults&n; * NOTE : In the ANSI docs, times are specified in units of &quot;symbol time&quot;.&n; * &t;  AMD chips use BCLK as unit. 1 BCKL == 2 symbols&n; */
DECL|macro|COMPLREF
mdefine_line|#define&t;COMPLREF&t;((u_long)32*256*256)&t;/* two&squot;s complement 21 bit */
DECL|macro|MSTOBCLK
mdefine_line|#define MSTOBCLK(x)&t;((u_long)(x)*12500L)
DECL|macro|MSTOTVX
mdefine_line|#define MSTOTVX(x)&t;(((u_long)(x)*1000L)/80/255)
macro_line|#endif&t;/* _SUPERNET_ */
eof
