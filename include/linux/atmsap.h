multiline_comment|/* atmsap.h - ATM Service Access Point addressing definitions */
multiline_comment|/* Written 1995-1999 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef _LINUX_ATMSAP_H
DECL|macro|_LINUX_ATMSAP_H
mdefine_line|#define _LINUX_ATMSAP_H
macro_line|#include &lt;linux/atmapi.h&gt;
multiline_comment|/*&n; * BEGIN_xx and END_xx markers are used for automatic generation of&n; * documentation. Do not change them.&n; */
multiline_comment|/*&n; * Layer 2 protocol identifiers&n; */
multiline_comment|/* BEGIN_L2 */
DECL|macro|ATM_L2_NONE
mdefine_line|#define ATM_L2_NONE&t;0&t;/* L2 not specified */
DECL|macro|ATM_L2_ISO1745
mdefine_line|#define ATM_L2_ISO1745  0x01&t;/* Basic mode ISO 1745 */
DECL|macro|ATM_L2_Q291
mdefine_line|#define ATM_L2_Q291&t;0x02&t;/* ITU-T Q.291 (Rec. I.441) */
DECL|macro|ATM_L2_X25_LL
mdefine_line|#define ATM_L2_X25_LL&t;0x06&t;/* ITU-T X.25, link layer */
DECL|macro|ATM_L2_X25_ML
mdefine_line|#define ATM_L2_X25_ML&t;0x07&t;/* ITU-T X.25, multilink */
DECL|macro|ATM_L2_LAPB
mdefine_line|#define ATM_L2_LAPB&t;0x08&t;/* Extended LAPB, half-duplex (Rec. T.71) */
DECL|macro|ATM_L2_HDLC_ARM
mdefine_line|#define ATM_L2_HDLC_ARM&t;0x09&t;/* HDLC ARM (ISO/IEC 4335) */
DECL|macro|ATM_L2_HDLC_NRM
mdefine_line|#define ATM_L2_HDLC_NRM&t;0x0a&t;/* HDLC NRM (ISO/IEC 4335) */
DECL|macro|ATM_L2_HDLC_ABM
mdefine_line|#define ATM_L2_HDLC_ABM&t;0x0b&t;/* HDLC ABM (ISO/IEC 4335) */
DECL|macro|ATM_L2_ISO8802
mdefine_line|#define ATM_L2_ISO8802&t;0x0c&t;/* LAN LLC (ISO/IEC 8802/2) */
DECL|macro|ATM_L2_X75
mdefine_line|#define ATM_L2_X75&t;0x0d&t;/* ITU-T X.75, SLP */
DECL|macro|ATM_L2_Q922
mdefine_line|#define ATM_L2_Q922&t;0x0e&t;/* ITU-T Q.922 */
DECL|macro|ATM_L2_USER
mdefine_line|#define ATM_L2_USER&t;0x10&t;/* user-specified */
DECL|macro|ATM_L2_ISO7776
mdefine_line|#define ATM_L2_ISO7776&t;0x11&t;/* ISO 7776 DTE-DTE */
multiline_comment|/* END_L2 */
multiline_comment|/*&n; * Layer 3 protocol identifiers&n; */
multiline_comment|/* BEGIN_L3 */
DECL|macro|ATM_L3_NONE
mdefine_line|#define ATM_L3_NONE&t;0&t;/* L3 not specified */
DECL|macro|ATM_L3_X25
mdefine_line|#define ATM_L3_X25&t;0x06&t;/* ITU-T X.25, packet layer */
DECL|macro|ATM_L3_ISO8208
mdefine_line|#define ATM_L3_ISO8208&t;0x07&t;/* ISO/IEC 8208 */
DECL|macro|ATM_L3_X223
mdefine_line|#define ATM_L3_X223&t;0x08&t;/* ITU-T X.223 | ISO/IEC 8878 */
DECL|macro|ATM_L3_ISO8473
mdefine_line|#define ATM_L3_ISO8473&t;0x09&t;/* ITU-T X.233 | ISO/IEC 8473 */
DECL|macro|ATM_L3_T70
mdefine_line|#define ATM_L3_T70&t;0x0a&t;/* ITU-T T.70 minimum network layer */
DECL|macro|ATM_L3_TR9577
mdefine_line|#define ATM_L3_TR9577&t;0x0b&t;/* ISO/IEC TR 9577 */
DECL|macro|ATM_L3_H310
mdefine_line|#define ATM_L3_H310&t;0x0c&t;/* ITU-T Recommendation H.310 */
DECL|macro|ATM_L3_H321
mdefine_line|#define ATM_L3_H321&t;0x0d&t;/* ITU-T Recommendation H.321 */
DECL|macro|ATM_L3_USER
mdefine_line|#define ATM_L3_USER&t;0x10&t;/* user-specified */
multiline_comment|/* END_L3 */
multiline_comment|/*&n; * High layer identifiers&n; */
multiline_comment|/* BEGIN_HL */
DECL|macro|ATM_HL_NONE
mdefine_line|#define ATM_HL_NONE&t;0&t;/* HL not specified */
DECL|macro|ATM_HL_ISO
mdefine_line|#define ATM_HL_ISO&t;0x01&t;/* ISO */
DECL|macro|ATM_HL_USER
mdefine_line|#define ATM_HL_USER&t;0x02&t;/* user-specific */
DECL|macro|ATM_HL_HLP
mdefine_line|#define ATM_HL_HLP&t;0x03&t;/* high layer profile - UNI 3.0 only */
DECL|macro|ATM_HL_VENDOR
mdefine_line|#define ATM_HL_VENDOR&t;0x04&t;/* vendor-specific application identifier */
multiline_comment|/* END_HL */
multiline_comment|/*&n; * ITU-T coded mode of operation&n; */
multiline_comment|/* BEGIN_IMD */
DECL|macro|ATM_IMD_NONE
mdefine_line|#define ATM_IMD_NONE&t; 0&t;/* mode not specified */
DECL|macro|ATM_IMD_NORMAL
mdefine_line|#define ATM_IMD_NORMAL&t; 1&t;/* normal mode of operation */
DECL|macro|ATM_IMD_EXTENDED
mdefine_line|#define ATM_IMD_EXTENDED 2&t;/* extended mode of operation */
multiline_comment|/* END_IMD */
multiline_comment|/*&n; * H.310 code points&n; */
DECL|macro|ATM_TT_NONE
mdefine_line|#define ATM_TT_NONE&t;0&t;/* terminal type not specified */
DECL|macro|ATM_TT_RX
mdefine_line|#define ATM_TT_RX&t;1&t;/* receive only */
DECL|macro|ATM_TT_TX
mdefine_line|#define ATM_TT_TX&t;2&t;/* send only */
DECL|macro|ATM_TT_RXTX
mdefine_line|#define ATM_TT_RXTX&t;3&t;/* receive and send */
DECL|macro|ATM_MC_NONE
mdefine_line|#define ATM_MC_NONE&t;0&t;/* no multiplexing */
DECL|macro|ATM_MC_TS
mdefine_line|#define ATM_MC_TS&t;1&t;/* transport stream (TS) */
DECL|macro|ATM_MC_TS_FEC
mdefine_line|#define ATM_MC_TS_FEC&t;2&t;/* transport stream with forward error corr. */
DECL|macro|ATM_MC_PS
mdefine_line|#define ATM_MC_PS&t;3&t;/* program stream (PS) */
DECL|macro|ATM_MC_PS_FEC
mdefine_line|#define ATM_MC_PS_FEC&t;4&t;/* program stream with forward error corr. */
DECL|macro|ATM_MC_H221
mdefine_line|#define ATM_MC_H221&t;5&t;/* ITU-T Rec. H.221 */
multiline_comment|/*&n; * SAP structures&n; */
DECL|macro|ATM_MAX_HLI
mdefine_line|#define ATM_MAX_HLI&t;8&t;/* maximum high-layer information length */
DECL|struct|atm_blli
r_struct
id|atm_blli
(brace
DECL|member|l2_proto
r_int
r_char
id|l2_proto
suffix:semicolon
multiline_comment|/* layer 2 protocol */
r_union
(brace
r_struct
(brace
DECL|member|mode
r_int
r_char
id|mode
suffix:semicolon
multiline_comment|/* mode of operation (ATM_IMD_xxx), 0 if */
multiline_comment|/* absent */
DECL|member|window
r_int
r_char
id|window
suffix:semicolon
multiline_comment|/* window size (k), 1-127 (0 to omit) */
DECL|member|itu
)brace
id|itu
suffix:semicolon
multiline_comment|/* ITU-T encoding */
DECL|member|user
r_int
r_char
id|user
suffix:semicolon
multiline_comment|/* user-specified l2 information */
DECL|member|l2
)brace
id|l2
suffix:semicolon
DECL|member|l3_proto
r_int
r_char
id|l3_proto
suffix:semicolon
multiline_comment|/* layer 3 protocol */
r_union
(brace
r_struct
(brace
DECL|member|mode
r_int
r_char
id|mode
suffix:semicolon
multiline_comment|/* mode of operation (ATM_IMD_xxx), 0 if */
multiline_comment|/* absent */
DECL|member|def_size
r_int
r_char
id|def_size
suffix:semicolon
multiline_comment|/* default packet size (log2), 4-12 (0 to */
multiline_comment|/* omit) */
DECL|member|window
r_int
r_char
id|window
suffix:semicolon
multiline_comment|/* packet window size, 1-127 (0 to omit) */
DECL|member|itu
)brace
id|itu
suffix:semicolon
multiline_comment|/* ITU-T encoding */
DECL|member|user
r_int
r_char
id|user
suffix:semicolon
multiline_comment|/* user specified l3 information */
r_struct
(brace
multiline_comment|/* if l3_proto = ATM_L3_H310 */
DECL|member|term_type
r_int
r_char
id|term_type
suffix:semicolon
multiline_comment|/* terminal type */
DECL|member|fw_mpx_cap
r_int
r_char
id|fw_mpx_cap
suffix:semicolon
multiline_comment|/* forward multiplexing capability */
multiline_comment|/* only if term_type != ATM_TT_NONE */
DECL|member|bw_mpx_cap
r_int
r_char
id|bw_mpx_cap
suffix:semicolon
multiline_comment|/* backward multiplexing capability */
multiline_comment|/* only if term_type != ATM_TT_NONE */
DECL|member|h310
)brace
id|h310
suffix:semicolon
r_struct
(brace
multiline_comment|/* if l3_proto = ATM_L3_TR9577 */
DECL|member|ipi
r_int
r_char
id|ipi
suffix:semicolon
multiline_comment|/* initial protocol id */
DECL|member|snap
r_int
r_char
id|snap
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* IEEE 802.1 SNAP identifier */
multiline_comment|/* (only if ipi == NLPID_IEEE802_1_SNAP) */
DECL|member|tr9577
)brace
id|tr9577
suffix:semicolon
DECL|member|l3
)brace
id|l3
suffix:semicolon
DECL|variable|__ATM_API_ALIGN
)brace
id|__ATM_API_ALIGN
suffix:semicolon
DECL|struct|atm_bhli
r_struct
id|atm_bhli
(brace
DECL|member|hl_type
r_int
r_char
id|hl_type
suffix:semicolon
multiline_comment|/* high layer information type */
DECL|member|hl_length
r_int
r_char
id|hl_length
suffix:semicolon
multiline_comment|/* length (only if hl_type == ATM_HL_USER || */
multiline_comment|/* hl_type == ATM_HL_ISO) */
DECL|member|hl_info
r_int
r_char
id|hl_info
(braket
id|ATM_MAX_HLI
)braket
suffix:semicolon
multiline_comment|/* high layer information */
)brace
suffix:semicolon
DECL|macro|ATM_MAX_BLLI
mdefine_line|#define ATM_MAX_BLLI&t;3&t;&t;/* maximum number of BLLI elements */
DECL|struct|atm_sap
r_struct
id|atm_sap
(brace
DECL|member|bhli
r_struct
id|atm_bhli
id|bhli
suffix:semicolon
multiline_comment|/* local SAP, high-layer information */
DECL|member|__ATM_API_ALIGN
r_struct
id|atm_blli
id|blli
(braket
id|ATM_MAX_BLLI
)braket
id|__ATM_API_ALIGN
suffix:semicolon
multiline_comment|/* local SAP, low-layer info */
)brace
suffix:semicolon
DECL|function|blli_in_use
r_static
id|__inline__
r_int
id|blli_in_use
c_func
(paren
r_struct
id|atm_blli
id|blli
)paren
(brace
r_return
id|blli.l2_proto
op_logical_or
id|blli.l3_proto
suffix:semicolon
)brace
macro_line|#endif
eof
