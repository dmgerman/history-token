multiline_comment|/* if_ether.h needed for definition of ETH_DATA_LEN and ETH_ALEN&n; */
macro_line|#include &quot;linux/if_ether.h&quot;
multiline_comment|/* frame layout based on par3.2 &quot;LLC PDU format&quot;&n; */
r_typedef
r_union
(brace
multiline_comment|/* pdu layout from pages 40 &amp; 44 */
r_struct
(brace
multiline_comment|/* general header, all pdu types */
DECL|member|dsap
r_int
id|dsap
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* dest service access point */
DECL|member|ssap
r_int
id|ssap
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* source service access point */
DECL|member|f1
r_int
id|f1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* I- U- or S- format id bits */
DECL|member|f2
r_int
id|f2
suffix:colon
l_int|1
suffix:semicolon
r_int
suffix:colon
l_int|6
suffix:semicolon
r_int
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pdu_hdr
)brace
id|pdu_hdr
suffix:semicolon
r_struct
(brace
DECL|member|dummy1
r_char
id|dummy1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* dsap + ssap */
DECL|member|byte1
r_char
id|byte1
suffix:semicolon
DECL|member|byte2
r_char
id|byte2
suffix:semicolon
DECL|member|pdu_cntl
)brace
id|pdu_cntl
suffix:semicolon
multiline_comment|/* unformatted control bytes */
r_struct
(brace
multiline_comment|/* header of an Information pdu */
DECL|member|dummy2
r_int
r_char
id|dummy2
(braket
l_int|2
)braket
suffix:semicolon
r_int
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ns
r_int
id|ns
suffix:colon
l_int|7
suffix:semicolon
DECL|member|i_pflag
r_int
id|i_pflag
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* poll/final bit */
DECL|member|nr
r_int
id|nr
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/* N(R)  */
DECL|member|is_info
r_int
r_char
id|is_info
(braket
id|ETH_DATA_LEN
)braket
suffix:semicolon
DECL|member|i_hdr
)brace
id|i_hdr
suffix:semicolon
r_struct
(brace
multiline_comment|/* header of a Supervisory pdu */
DECL|member|dummy3
r_int
r_char
id|dummy3
(braket
l_int|2
)braket
suffix:semicolon
r_int
suffix:colon
l_int|2
suffix:semicolon
DECL|member|ss
r_int
id|ss
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* supervisory function bits */
r_int
suffix:colon
l_int|4
suffix:semicolon
DECL|member|s_pflag
r_int
id|s_pflag
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* poll/final bit  */
DECL|member|nr
r_int
id|nr
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/* N(R)  */
DECL|member|s_hdr
)brace
id|s_hdr
suffix:semicolon
multiline_comment|/* when accessing the P/F bit or the N(R) field there&squot;s no need to distinguish&n;   I pdus from S pdus i_pflag and s_pflag / i_nr and s_nr map to the same&n;   physical location.&n; */
r_struct
(brace
multiline_comment|/* header of an Unnumbered pdu */
DECL|member|dummy4
r_int
r_char
id|dummy4
(braket
l_int|2
)braket
suffix:semicolon
r_int
suffix:colon
l_int|2
suffix:semicolon
DECL|member|mm1
r_int
id|mm1
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* modifier function part1 */
DECL|member|u_pflag
r_int
id|u_pflag
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* P/F for U- pdus */
DECL|member|mm2
r_int
id|mm2
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* modifier function part2 */
DECL|member|u_info
r_int
r_char
id|u_info
(braket
id|ETH_DATA_LEN
op_minus
l_int|1
)braket
suffix:semicolon
DECL|member|u_hdr
)brace
id|u_hdr
suffix:semicolon
r_struct
(brace
multiline_comment|/* mm field in an Unnumbered pdu */
DECL|member|dummy5
r_int
r_char
id|dummy5
(braket
l_int|2
)braket
suffix:semicolon
r_int
suffix:colon
l_int|2
suffix:semicolon
DECL|member|mm
r_int
id|mm
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* must be masked to get ridd of P/F !  */
DECL|member|u_mm
)brace
id|u_mm
suffix:semicolon
DECL|typedef|frame_type
DECL|typedef|frameptr
)brace
id|frame_type
comma
op_star
id|frameptr
suffix:semicolon
multiline_comment|/* frame format test macros: */
DECL|macro|IS_UFRAME
mdefine_line|#define IS_UFRAME( fr ) ( ( (fr)-&gt;pdu_hdr.f1) &amp; ( (fr)-&gt;pdu_hdr.f2) )
DECL|macro|IS_IFRAME
mdefine_line|#define IS_IFRAME( fr ) ( !( (fr)-&gt;pdu_hdr.f1) )
DECL|macro|IS_SFRAME
mdefine_line|#define IS_SFRAME( fr ) ( ( (fr)-&gt;pdu_hdr.f1) &amp; !( (fr)-&gt;pdu_hdr.f2) )
DECL|macro|IS_RSP
mdefine_line|#define IS_RSP( fr ) ( fr-&gt;pdu_hdr.ssap &amp; 0x01 )
multiline_comment|/* The transition table, the _encode tables and some tests in the&n;   source code depend on the numeric order of these values.&n;   Think twice before changing.&n; */
multiline_comment|/* frame names for TYPE 2 operation: */
DECL|macro|I_CMD
mdefine_line|#define I_CMD&t;&t;0
DECL|macro|RR_CMD
mdefine_line|#define RR_CMD&t;&t;1
DECL|macro|RNR_CMD
mdefine_line|#define RNR_CMD&t;&t;2
DECL|macro|REJ_CMD
mdefine_line|#define REJ_CMD&t;&t;3
DECL|macro|DISC_CMD
mdefine_line|#define DISC_CMD&t;4
DECL|macro|SABME_CMD
mdefine_line|#define SABME_CMD&t;5
DECL|macro|I_RSP
mdefine_line|#define I_RSP&t;&t;6
DECL|macro|RR_RSP
mdefine_line|#define RR_RSP&t;&t;7
DECL|macro|RNR_RSP
mdefine_line|#define RNR_RSP&t;&t;8
DECL|macro|REJ_RSP
mdefine_line|#define REJ_RSP&t;&t;9
DECL|macro|UA_RSP
mdefine_line|#define UA_RSP&t;&t;10
DECL|macro|DM_RSP
mdefine_line|#define DM_RSP&t;&t;11
DECL|macro|FRMR_RSP
mdefine_line|#define FRMR_RSP&t;12
multiline_comment|/* junk frame name: */
DECL|macro|BAD_FRAME
mdefine_line|#define BAD_FRAME&t;13
DECL|macro|NO_FRAME
mdefine_line|#define NO_FRAME&t;13
multiline_comment|/* frame names for TYPE 1 operation: */
DECL|macro|UI_CMD
mdefine_line|#define UI_CMD&t;&t;14
DECL|macro|XID_CMD
mdefine_line|#define XID_CMD&t;&t;15
DECL|macro|TEST_CMD
mdefine_line|#define TEST_CMD&t;16
DECL|macro|XID_RSP
mdefine_line|#define XID_RSP&t;&t;17
DECL|macro|TEST_RSP
mdefine_line|#define TEST_RSP&t;18
eof
