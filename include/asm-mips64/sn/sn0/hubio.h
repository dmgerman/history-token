multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Derived from IRIX &lt;sys/SN/SN0/hubio.h&gt;, Revision 1.80.&n; *&n; * Copyright (C) 1992 - 1997, 1999 Silicon Graphics, Inc.&n; * Copyright (C) 1999 by Ralf Baechle&n; */
macro_line|#ifndef&t;_ASM_SGI_SN_SN0_HUBIO_H
DECL|macro|_ASM_SGI_SN_SN0_HUBIO_H
mdefine_line|#define&t;_ASM_SGI_SN_SN0_HUBIO_H
multiline_comment|/*&n; * Hub I/O interface registers&n; *&n; * All registers in this file are subject to change until Hub chip tapeout.&n; * In general, the longer software name should be used when available.&n; */
multiline_comment|/* &n; * Slightly friendlier names for some common registers.&n; * The hardware definitions follow.&n; */
DECL|macro|IIO_WIDGET
mdefine_line|#define IIO_WIDGET&t;&t;IIO_WID      /* Widget identification */
DECL|macro|IIO_WIDGET_STAT
mdefine_line|#define IIO_WIDGET_STAT&t;&t;IIO_WSTAT    /* Widget status register */
DECL|macro|IIO_WIDGET_CTRL
mdefine_line|#define IIO_WIDGET_CTRL&t;&t;IIO_WCR&t;     /* Widget control register */
DECL|macro|IIO_WIDGET_TOUT
mdefine_line|#define IIO_WIDGET_TOUT&t;&t;IIO_WRTO     /* Widget request timeout */
DECL|macro|IIO_WIDGET_FLUSH
mdefine_line|#define IIO_WIDGET_FLUSH&t;IIO_WTFR     /* Widget target flush */ 
DECL|macro|IIO_PROTECT
mdefine_line|#define IIO_PROTECT&t;&t;IIO_ILAPR    /* IO interface protection */
DECL|macro|IIO_PROTECT_OVRRD
mdefine_line|#define IIO_PROTECT_OVRRD&t;IIO_ILAPO    /* IO protect override */
DECL|macro|IIO_OUTWIDGET_ACCESS
mdefine_line|#define IIO_OUTWIDGET_ACCESS&t;IIO_IOWA     /* Outbound widget access */
DECL|macro|IIO_INWIDGET_ACCESS
mdefine_line|#define IIO_INWIDGET_ACCESS&t;IIO_IIWA     /* Inbound widget access */
DECL|macro|IIO_INDEV_ERR_MASK
mdefine_line|#define IIO_INDEV_ERR_MASK&t;IIO_IIDEM    /* Inbound device error mask */
DECL|macro|IIO_LLP_CSR
mdefine_line|#define IIO_LLP_CSR&t;&t;IIO_ILCSR    /* LLP control and status */
DECL|macro|IIO_LLP_LOG
mdefine_line|#define IIO_LLP_LOG&t;&t;IIO_ILLR     /* LLP log */
DECL|macro|IIO_XTALKCC_TOUT
mdefine_line|#define IIO_XTALKCC_TOUT&t;IIO_IXCC     /* Xtalk credit count timeout*/
DECL|macro|IIO_XTALKTT_TOUT
mdefine_line|#define IIO_XTALKTT_TOUT&t;IIO_IXTT     /* Xtalk tail timeout */
DECL|macro|IIO_IO_ERR_CLR
mdefine_line|#define IIO_IO_ERR_CLR&t;&t;IIO_IECLR    /* IO error clear */
DECL|macro|IIO_BTE_CRB_CNT
mdefine_line|#define IIO_BTE_CRB_CNT         IIO_IBCN     /* IO BTE CRB count */
DECL|macro|IIO_LLP_CSR_IS_UP
mdefine_line|#define IIO_LLP_CSR_IS_UP&t;&t;0x00002000
DECL|macro|IIO_LLP_CSR_LLP_STAT_MASK
mdefine_line|#define&t;IIO_LLP_CSR_LLP_STAT_MASK&t;0x00003000
DECL|macro|IIO_LLP_CSR_LLP_STAT_SHFT
mdefine_line|#define&t;IIO_LLP_CSR_LLP_STAT_SHFT&t;12
multiline_comment|/* key to IIO_PROTECT_OVRRD */
DECL|macro|IIO_PROTECT_OVRRD_KEY
mdefine_line|#define IIO_PROTECT_OVRRD_KEY&t;0x53474972756c6573ull&t;/* &quot;SGIrules&quot; */
multiline_comment|/* BTE register names */
DECL|macro|IIO_BTE_STAT_0
mdefine_line|#define IIO_BTE_STAT_0&t;&t;IIO_IBLS_0   /* Also BTE length/status 0 */
DECL|macro|IIO_BTE_SRC_0
mdefine_line|#define IIO_BTE_SRC_0&t;&t;IIO_IBSA_0   /* Also BTE source address  0 */
DECL|macro|IIO_BTE_DEST_0
mdefine_line|#define IIO_BTE_DEST_0&t;&t;IIO_IBDA_0   /* Also BTE dest. address 0 */
DECL|macro|IIO_BTE_CTRL_0
mdefine_line|#define IIO_BTE_CTRL_0&t;&t;IIO_IBCT_0   /* Also BTE control/terminate 0 */
DECL|macro|IIO_BTE_NOTIFY_0
mdefine_line|#define IIO_BTE_NOTIFY_0 &t;IIO_IBNA_0   /* Also BTE notification 0 */
DECL|macro|IIO_BTE_INT_0
mdefine_line|#define IIO_BTE_INT_0&t;&t;IIO_IBIA_0   /* Also BTE interrupt 0 */
DECL|macro|IIO_BTE_OFF_0
mdefine_line|#define IIO_BTE_OFF_0&t;&t;0&t;     /* Base offset from BTE 0 regs. */
DECL|macro|IIO_BTE_OFF_1
mdefine_line|#define IIO_BTE_OFF_1&t;IIO_IBLS_1 - IIO_IBLS_0 /* Offset from base to BTE 1 */
multiline_comment|/* BTE register offsets from base */
DECL|macro|BTEOFF_STAT
mdefine_line|#define BTEOFF_STAT&t;&t;0
DECL|macro|BTEOFF_SRC
mdefine_line|#define BTEOFF_SRC&t;&t;(IIO_BTE_SRC_0 - IIO_BTE_STAT_0)
DECL|macro|BTEOFF_DEST
mdefine_line|#define BTEOFF_DEST&t;&t;(IIO_BTE_DEST_0 - IIO_BTE_STAT_0)
DECL|macro|BTEOFF_CTRL
mdefine_line|#define BTEOFF_CTRL&t;&t;(IIO_BTE_CTRL_0 - IIO_BTE_STAT_0)
DECL|macro|BTEOFF_NOTIFY
mdefine_line|#define BTEOFF_NOTIFY&t;&t;(IIO_BTE_NOTIFY_0 - IIO_BTE_STAT_0)
DECL|macro|BTEOFF_INT
mdefine_line|#define BTEOFF_INT&t;&t;(IIO_BTE_INT_0 - IIO_BTE_STAT_0)
multiline_comment|/*&n; * The following definitions use the names defined in the IO interface&n; * document for ease of reference.  When possible, software should &n; * generally use the the longer but clearer names defined above.&n; */
DECL|macro|IIO_BASE
mdefine_line|#define IIO_BASE&t;0x400000
DECL|macro|IIO_BASE_BTE0
mdefine_line|#define IIO_BASE_BTE0&t;0x410000
DECL|macro|IIO_BASE_BTE1
mdefine_line|#define IIO_BASE_BTE1&t;0x420000
DECL|macro|IIO_BASE_PERF
mdefine_line|#define IIO_BASE_PERF&t;0x430000
DECL|macro|IIO_PERF_CNT
mdefine_line|#define IIO_PERF_CNT&t;0x430008
DECL|macro|IO_PERF_SETS
mdefine_line|#define IO_PERF_SETS&t;32
DECL|macro|IIO_WID
mdefine_line|#define IIO_WID&t;&t;0x400000&t;/* Widget identification */
DECL|macro|IIO_WSTAT
mdefine_line|#define IIO_WSTAT&t;0x400008&t;/* Widget status */
DECL|macro|IIO_WCR
mdefine_line|#define IIO_WCR&t;&t;0x400020&t;/* Widget control */
DECL|macro|IIO_WSTAT_ECRAZY
mdefine_line|#define&t;IIO_WSTAT_ECRAZY&t;(1ULL &lt;&lt; 32)&t;/* Hub gone crazy */
DECL|macro|IIO_WSTAT_TXRETRY
mdefine_line|#define&t;IIO_WSTAT_TXRETRY&t;(1ULL &lt;&lt; 9)&t;/* Hub Tx Retry timeout */
DECL|macro|IIO_WSTAT_TXRETRY_MASK
mdefine_line|#define&t;IIO_WSTAT_TXRETRY_MASK&t;(0x7F)
DECL|macro|IIO_WSTAT_TXRETRY_SHFT
mdefine_line|#define&t;IIO_WSTAT_TXRETRY_SHFT&t;(16)
DECL|macro|IIO_WSTAT_TXRETRY_CNT
mdefine_line|#define&t;IIO_WSTAT_TXRETRY_CNT(w)&t;(((w) &gt;&gt; IIO_WSTAT_TXRETRY_SHFT) &amp; &bslash;&n;&t;&t;&t;&t;&t;  IIO_WSTAT_TXRETRY_MASK)
DECL|macro|IIO_ILAPR
mdefine_line|#define IIO_ILAPR&t;0x400100&t;/* Local Access Protection */
DECL|macro|IIO_ILAPO
mdefine_line|#define IIO_ILAPO&t;0x400108&t;/* Protection override */
DECL|macro|IIO_IOWA
mdefine_line|#define IIO_IOWA&t;0x400110&t;/* outbound widget access */
DECL|macro|IIO_IIWA
mdefine_line|#define IIO_IIWA&t;0x400118&t;/* inbound widget access */
DECL|macro|IIO_IIDEM
mdefine_line|#define IIO_IIDEM&t;0x400120&t;/* Inbound Device Error Mask */
DECL|macro|IIO_ILCSR
mdefine_line|#define IIO_ILCSR&t;0x400128&t;/* LLP control and status */
DECL|macro|IIO_ILLR
mdefine_line|#define IIO_ILLR&t;0x400130&t;/* LLP Log */
DECL|macro|IIO_IIDSR
mdefine_line|#define IIO_IIDSR&t;0x400138&t;/* Interrupt destination */
DECL|macro|IIO_IIBUSERR
mdefine_line|#define IIO_IIBUSERR&t;0x1400208&t;/* Reads here cause a bus error. */
multiline_comment|/* IO Interrupt Destination Register */
DECL|macro|IIO_IIDSR_SENT_SHIFT
mdefine_line|#define IIO_IIDSR_SENT_SHIFT&t;28
DECL|macro|IIO_IIDSR_SENT_MASK
mdefine_line|#define IIO_IIDSR_SENT_MASK&t;0x10000000
DECL|macro|IIO_IIDSR_ENB_SHIFT
mdefine_line|#define IIO_IIDSR_ENB_SHIFT&t;24
DECL|macro|IIO_IIDSR_ENB_MASK
mdefine_line|#define IIO_IIDSR_ENB_MASK&t;0x01000000
DECL|macro|IIO_IIDSR_NODE_SHIFT
mdefine_line|#define IIO_IIDSR_NODE_SHIFT&t;8
DECL|macro|IIO_IIDSR_NODE_MASK
mdefine_line|#define IIO_IIDSR_NODE_MASK&t;0x0000ff00
DECL|macro|IIO_IIDSR_LVL_SHIFT
mdefine_line|#define IIO_IIDSR_LVL_SHIFT&t;0
DECL|macro|IIO_IIDSR_LVL_MASK
mdefine_line|#define IIO_IIDSR_LVL_MASK&t;0x0000003f
multiline_comment|/* GFX Flow Control Node/Widget Register */
DECL|macro|IIO_IGFX_0
mdefine_line|#define IIO_IGFX_0&t;0x400140&t;/* gfx node/widget register 0 */
DECL|macro|IIO_IGFX_1
mdefine_line|#define IIO_IGFX_1&t;0x400148&t;/* gfx node/widget register 1 */
DECL|macro|IIO_IGFX_W_NUM_BITS
mdefine_line|#define IIO_IGFX_W_NUM_BITS&t;4&t;/* size of widget num field */
DECL|macro|IIO_IGFX_W_NUM_MASK
mdefine_line|#define IIO_IGFX_W_NUM_MASK&t;((1&lt;&lt;IIO_IGFX_W_NUM_BITS)-1)
DECL|macro|IIO_IGFX_W_NUM_SHIFT
mdefine_line|#define IIO_IGFX_W_NUM_SHIFT&t;0
DECL|macro|IIO_IGFX_N_NUM_BITS
mdefine_line|#define IIO_IGFX_N_NUM_BITS&t;9&t;/* size of node num field */
DECL|macro|IIO_IGFX_N_NUM_MASK
mdefine_line|#define IIO_IGFX_N_NUM_MASK&t;((1&lt;&lt;IIO_IGFX_N_NUM_BITS)-1)
DECL|macro|IIO_IGFX_N_NUM_SHIFT
mdefine_line|#define IIO_IGFX_N_NUM_SHIFT&t;4
DECL|macro|IIO_IGFX_P_NUM_BITS
mdefine_line|#define IIO_IGFX_P_NUM_BITS&t;1&t;/* size of processor num field */
DECL|macro|IIO_IGFX_P_NUM_MASK
mdefine_line|#define IIO_IGFX_P_NUM_MASK&t;((1&lt;&lt;IIO_IGFX_P_NUM_BITS)-1)
DECL|macro|IIO_IGFX_P_NUM_SHIFT
mdefine_line|#define IIO_IGFX_P_NUM_SHIFT&t;16
DECL|macro|IIO_IGFX_VLD_BITS
mdefine_line|#define IIO_IGFX_VLD_BITS&t;1&t;/* size of valid field */
DECL|macro|IIO_IGFX_VLD_MASK
mdefine_line|#define IIO_IGFX_VLD_MASK&t;((1&lt;&lt;IIO_IGFX_VLD_BITS)-1)
DECL|macro|IIO_IGFX_VLD_SHIFT
mdefine_line|#define IIO_IGFX_VLD_SHIFT&t;20
DECL|macro|IIO_IGFX_INIT
mdefine_line|#define IIO_IGFX_INIT(widget, node, cpu, valid)&t;&t;&t;&t;(&bslash;&n;&t;(((widget) &amp; IIO_IGFX_W_NUM_MASK) &lt;&lt; IIO_IGFX_W_NUM_SHIFT) |&t; &bslash;&n;&t;(((node)   &amp; IIO_IGFX_N_NUM_MASK) &lt;&lt; IIO_IGFX_N_NUM_SHIFT) |&t; &bslash;&n;&t;(((cpu)    &amp; IIO_IGFX_P_NUM_MASK) &lt;&lt; IIO_IGFX_P_NUM_SHIFT) |&t; &bslash;&n;&t;(((valid)  &amp; IIO_IGFX_VLD_MASK)   &lt;&lt; IIO_IGFX_VLD_SHIFT)&t; )
multiline_comment|/* Scratch registers (not all bits available) */
DECL|macro|IIO_SCRATCH_REG0
mdefine_line|#define IIO_SCRATCH_REG0&t;0x400150
DECL|macro|IIO_SCRATCH_REG1
mdefine_line|#define&t;IIO_SCRATCH_REG1&t;0x400158
DECL|macro|IIO_SCRATCH_MASK
mdefine_line|#define IIO_SCRATCH_MASK&t;0x0000000f00f11fff
DECL|macro|IIO_SCRATCH_BIT0_0
mdefine_line|#define IIO_SCRATCH_BIT0_0&t;0x0000000800000000
DECL|macro|IIO_SCRATCH_BIT0_1
mdefine_line|#define IIO_SCRATCH_BIT0_1&t;0x0000000400000000
DECL|macro|IIO_SCRATCH_BIT0_2
mdefine_line|#define IIO_SCRATCH_BIT0_2&t;0x0000000200000000
DECL|macro|IIO_SCRATCH_BIT0_3
mdefine_line|#define IIO_SCRATCH_BIT0_3&t;0x0000000100000000
DECL|macro|IIO_SCRATCH_BIT0_4
mdefine_line|#define IIO_SCRATCH_BIT0_4&t;0x0000000000800000
DECL|macro|IIO_SCRATCH_BIT0_5
mdefine_line|#define IIO_SCRATCH_BIT0_5&t;0x0000000000400000
DECL|macro|IIO_SCRATCH_BIT0_6
mdefine_line|#define IIO_SCRATCH_BIT0_6&t;0x0000000000200000
DECL|macro|IIO_SCRATCH_BIT0_7
mdefine_line|#define IIO_SCRATCH_BIT0_7&t;0x0000000000100000
DECL|macro|IIO_SCRATCH_BIT0_8
mdefine_line|#define IIO_SCRATCH_BIT0_8&t;0x0000000000010000
DECL|macro|IIO_SCRATCH_BIT0_9
mdefine_line|#define IIO_SCRATCH_BIT0_9&t;0x0000000000001000
DECL|macro|IIO_SCRATCH_BIT0_R
mdefine_line|#define IIO_SCRATCH_BIT0_R&t;0x0000000000000fff
multiline_comment|/* IO Translation Table Entries */
DECL|macro|IIO_NUM_ITTES
mdefine_line|#define IIO_NUM_ITTES&t;7&t;&t;/* ITTEs numbered 0..6 */
multiline_comment|/* Hw manuals number them 1..7! */
multiline_comment|/*&n; * As a permanent workaround for a bug in the PI side of the hub, we&squot;ve&n; * redefined big window 7 as small window 0.&n; */
DECL|macro|HUB_NUM_BIG_WINDOW
mdefine_line|#define HUB_NUM_BIG_WINDOW&t;IIO_NUM_ITTES - 1
multiline_comment|/*&n; * Use the top big window as a surrogate for the first small window&n; */
DECL|macro|SWIN0_BIGWIN
mdefine_line|#define SWIN0_BIGWIN&t;&t;HUB_NUM_BIG_WINDOW
DECL|macro|ILCSR_WARM_RESET
mdefine_line|#define ILCSR_WARM_RESET&t;0x100
multiline_comment|/*&n; * The IO LLP control status register and widget control register&n; */
macro_line|#ifdef _LANGUAGE_C
DECL|union|hubii_wid_u
r_typedef
r_union
id|hubii_wid_u
(brace
DECL|member|wid_reg_value
id|u64
id|wid_reg_value
suffix:semicolon
r_struct
(brace
DECL|member|wid_rsvd
id|u64
id|wid_rsvd
suffix:colon
l_int|32
comma
multiline_comment|/* unused */
DECL|member|wid_rev_num
id|wid_rev_num
suffix:colon
l_int|4
comma
multiline_comment|/* revision number */
DECL|member|wid_part_num
id|wid_part_num
suffix:colon
l_int|16
comma
multiline_comment|/* the widget type: hub=c101 */
DECL|member|wid_mfg_num
id|wid_mfg_num
suffix:colon
l_int|11
comma
multiline_comment|/* Manufacturer id (IBM) */
DECL|member|wid_rsvd1
id|wid_rsvd1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|wid_fields_s
)brace
id|wid_fields_s
suffix:semicolon
DECL|typedef|hubii_wid_t
)brace
id|hubii_wid_t
suffix:semicolon
DECL|union|hubii_wcr_u
r_typedef
r_union
id|hubii_wcr_u
(brace
DECL|member|wcr_reg_value
id|u64
id|wcr_reg_value
suffix:semicolon
r_struct
(brace
DECL|member|wcr_rsvd
id|u64
id|wcr_rsvd
suffix:colon
l_int|41
comma
multiline_comment|/* unused */
DECL|member|wcr_e_thresh
id|wcr_e_thresh
suffix:colon
l_int|5
comma
multiline_comment|/* elasticity threshold */
DECL|member|wcr_dir_con
id|wcr_dir_con
suffix:colon
l_int|1
comma
multiline_comment|/* widget direct connect */
DECL|member|wcr_f_bad_pkt
id|wcr_f_bad_pkt
suffix:colon
l_int|1
comma
multiline_comment|/* Force bad llp pkt enable */
DECL|member|wcr_xbar_crd
id|wcr_xbar_crd
suffix:colon
l_int|3
comma
multiline_comment|/* LLP crossbar credit */
DECL|member|wcr_rsvd1
id|wcr_rsvd1
suffix:colon
l_int|8
comma
multiline_comment|/* Reserved */
DECL|member|wcr_tag_mode
id|wcr_tag_mode
suffix:colon
l_int|1
comma
multiline_comment|/* Tag mode */
DECL|member|wcr_widget_id
id|wcr_widget_id
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* LLP crossbar credit */
DECL|member|wcr_fields_s
)brace
id|wcr_fields_s
suffix:semicolon
DECL|typedef|hubii_wcr_t
)brace
id|hubii_wcr_t
suffix:semicolon
DECL|macro|iwcr_dir_con
mdefine_line|#define&t;iwcr_dir_con&t;wcr_fields_s.wcr_dir_con
DECL|union|hubii_wstat_u
r_typedef
r_union
id|hubii_wstat_u
(brace
DECL|member|reg_value
id|u64
id|reg_value
suffix:semicolon
r_struct
(brace
DECL|member|rsvd1
id|u64
id|rsvd1
suffix:colon
l_int|31
comma
DECL|member|crazy
id|crazy
suffix:colon
l_int|1
comma
multiline_comment|/* Crazy bit&t;&t;*/
DECL|member|rsvd2
id|rsvd2
suffix:colon
l_int|8
comma
DECL|member|llp_tx_cnt
id|llp_tx_cnt
suffix:colon
l_int|8
comma
multiline_comment|/* LLP Xmit retry counter */
DECL|member|rsvd3
id|rsvd3
suffix:colon
l_int|6
comma
DECL|member|tx_max_rtry
id|tx_max_rtry
suffix:colon
l_int|1
comma
multiline_comment|/* LLP Retry Timeout Signal */
DECL|member|rsvd4
id|rsvd4
suffix:colon
l_int|2
comma
DECL|member|xt_tail_to
id|xt_tail_to
suffix:colon
l_int|1
comma
multiline_comment|/* Xtalk Tail Timeout&t;*/
DECL|member|xt_crd_to
id|xt_crd_to
suffix:colon
l_int|1
comma
multiline_comment|/* Xtalk Credit Timeout&t;*/
DECL|member|pending
id|pending
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Pending Requests&t;*/
DECL|member|wstat_fields_s
)brace
id|wstat_fields_s
suffix:semicolon
DECL|typedef|hubii_wstat_t
)brace
id|hubii_wstat_t
suffix:semicolon
DECL|union|hubii_ilcsr_u
r_typedef
r_union
id|hubii_ilcsr_u
(brace
DECL|member|icsr_reg_value
id|u64
id|icsr_reg_value
suffix:semicolon
r_struct
(brace
DECL|member|icsr_rsvd
id|u64
id|icsr_rsvd
suffix:colon
l_int|22
comma
multiline_comment|/* unused */
DECL|member|icsr_max_burst
id|icsr_max_burst
suffix:colon
l_int|10
comma
multiline_comment|/* max burst */
DECL|member|icsr_rsvd4
id|icsr_rsvd4
suffix:colon
l_int|6
comma
multiline_comment|/* reserved */
DECL|member|icsr_max_retry
id|icsr_max_retry
suffix:colon
l_int|10
comma
multiline_comment|/* max retry */
DECL|member|icsr_rsvd3
id|icsr_rsvd3
suffix:colon
l_int|2
comma
multiline_comment|/* reserved */
DECL|member|icsr_lnk_stat
id|icsr_lnk_stat
suffix:colon
l_int|2
comma
multiline_comment|/* link status */
DECL|member|icsr_bm8
id|icsr_bm8
suffix:colon
l_int|1
comma
multiline_comment|/* Bit mode 8 */
DECL|member|icsr_llp_en
id|icsr_llp_en
suffix:colon
l_int|1
comma
multiline_comment|/* LLP enable bit */
DECL|member|icsr_rsvd2
id|icsr_rsvd2
suffix:colon
l_int|1
comma
multiline_comment|/* reserver */
DECL|member|icsr_wrm_reset
id|icsr_wrm_reset
suffix:colon
l_int|1
comma
multiline_comment|/* Warm reset bit */
DECL|member|icsr_rsvd1
id|icsr_rsvd1
suffix:colon
l_int|2
comma
multiline_comment|/* Data ready offset */
DECL|member|icsr_null_to
id|icsr_null_to
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Null timeout   */
DECL|member|icsr_fields_s
)brace
id|icsr_fields_s
suffix:semicolon
DECL|typedef|hubii_ilcsr_t
)brace
id|hubii_ilcsr_t
suffix:semicolon
DECL|union|hubii_iowa_u
r_typedef
r_union
id|hubii_iowa_u
(brace
DECL|member|iowa_reg_value
id|u64
id|iowa_reg_value
suffix:semicolon
r_struct
(brace
DECL|member|iowa_rsvd
id|u64
id|iowa_rsvd
suffix:colon
l_int|48
comma
multiline_comment|/* unused */
DECL|member|iowa_wxoac
id|iowa_wxoac
suffix:colon
l_int|8
comma
multiline_comment|/* xtalk widget access bits */
DECL|member|iowa_rsvd1
id|iowa_rsvd1
suffix:colon
l_int|7
comma
multiline_comment|/* xtalk widget access bits */
DECL|member|iowa_w0oac
id|iowa_w0oac
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* xtalk widget access bits */
DECL|member|iowa_fields_s
)brace
id|iowa_fields_s
suffix:semicolon
DECL|typedef|hubii_iowa_t
)brace
id|hubii_iowa_t
suffix:semicolon
DECL|union|hubii_iiwa_u
r_typedef
r_union
id|hubii_iiwa_u
(brace
DECL|member|iiwa_reg_value
id|u64
id|iiwa_reg_value
suffix:semicolon
r_struct
(brace
DECL|member|iiwa_rsvd
id|u64
id|iiwa_rsvd
suffix:colon
l_int|48
comma
multiline_comment|/* unused */
DECL|member|iiwa_wxiac
id|iiwa_wxiac
suffix:colon
l_int|8
comma
multiline_comment|/* hub wid access bits */
DECL|member|iiwa_rsvd1
id|iiwa_rsvd1
suffix:colon
l_int|7
comma
multiline_comment|/* reserved */
DECL|member|iiwa_w0iac
id|iiwa_w0iac
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* hub wid0 access */
DECL|member|iiwa_fields_s
)brace
id|iiwa_fields_s
suffix:semicolon
DECL|typedef|hubii_iiwa_t
)brace
id|hubii_iiwa_t
suffix:semicolon
DECL|union|hubii_illr_u
r_typedef
r_union
id|hubii_illr_u
(brace
DECL|member|illr_reg_value
id|u64
id|illr_reg_value
suffix:semicolon
r_struct
(brace
DECL|member|illr_rsvd
id|u64
id|illr_rsvd
suffix:colon
l_int|32
comma
multiline_comment|/* unused */
DECL|member|illr_cb_cnt
id|illr_cb_cnt
suffix:colon
l_int|16
comma
multiline_comment|/* checkbit error count */
DECL|member|illr_sn_cnt
id|illr_sn_cnt
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* sequence number count */
DECL|member|illr_fields_s
)brace
id|illr_fields_s
suffix:semicolon
DECL|typedef|hubii_illr_t
)brace
id|hubii_illr_t
suffix:semicolon
multiline_comment|/* The structures below are defined to extract and modify the ii&n;performance registers */
multiline_comment|/* io_perf_sel allows the caller to specify what tests will be&n;   performed */
DECL|union|io_perf_sel
r_typedef
r_union
id|io_perf_sel
(brace
DECL|member|perf_sel_reg
id|u64
id|perf_sel_reg
suffix:semicolon
r_struct
(brace
DECL|member|perf_rsvd
id|u64
id|perf_rsvd
suffix:colon
l_int|48
comma
DECL|member|perf_icct
id|perf_icct
suffix:colon
l_int|8
comma
DECL|member|perf_ippr1
id|perf_ippr1
suffix:colon
l_int|4
comma
DECL|member|perf_ippr0
id|perf_ippr0
suffix:colon
l_int|4
suffix:semicolon
DECL|member|perf_sel_bits
)brace
id|perf_sel_bits
suffix:semicolon
DECL|typedef|io_perf_sel_t
)brace
id|io_perf_sel_t
suffix:semicolon
multiline_comment|/* io_perf_cnt is to extract the count from the hub registers. Due to&n;   hardware problems there is only one counter, not two. */
DECL|union|io_perf_cnt
r_typedef
r_union
id|io_perf_cnt
(brace
DECL|member|perf_cnt
id|u64
id|perf_cnt
suffix:semicolon
r_struct
(brace
DECL|member|perf_rsvd1
id|u64
id|perf_rsvd1
suffix:colon
l_int|32
comma
DECL|member|perf_rsvd2
id|perf_rsvd2
suffix:colon
l_int|12
comma
DECL|member|perf_cnt
id|perf_cnt
suffix:colon
l_int|20
suffix:semicolon
DECL|member|perf_cnt_bits
)brace
id|perf_cnt_bits
suffix:semicolon
DECL|typedef|io_perf_cnt_t
)brace
id|io_perf_cnt_t
suffix:semicolon
macro_line|#endif
DECL|macro|LNK_STAT_WORKING
mdefine_line|#define LNK_STAT_WORKING&t;0x2
DECL|macro|IIO_LLP_CB_MAX
mdefine_line|#define IIO_LLP_CB_MAX&t;0xffff
DECL|macro|IIO_LLP_SN_MAX
mdefine_line|#define IIO_LLP_SN_MAX&t;0xffff
multiline_comment|/* IO PRB Entries */
DECL|macro|IIO_NUM_IPRBS
mdefine_line|#define&t;IIO_NUM_IPRBS&t;(9)&t;&t;
DECL|macro|IIO_IOPRB_0
mdefine_line|#define IIO_IOPRB_0&t;0x400198&t;/* PRB entry 0 */
DECL|macro|IIO_IOPRB_8
mdefine_line|#define IIO_IOPRB_8&t;0x4001a0&t;/* PRB entry 8 */
DECL|macro|IIO_IOPRB_9
mdefine_line|#define IIO_IOPRB_9&t;0x4001a8&t;/* PRB entry 9 */
DECL|macro|IIO_IOPRB_A
mdefine_line|#define IIO_IOPRB_A&t;0x4001b0&t;/* PRB entry a */
DECL|macro|IIO_IOPRB_B
mdefine_line|#define IIO_IOPRB_B&t;0x4001b8&t;/* PRB entry b */
DECL|macro|IIO_IOPRB_C
mdefine_line|#define IIO_IOPRB_C&t;0x4001c0&t;/* PRB entry c */
DECL|macro|IIO_IOPRB_D
mdefine_line|#define IIO_IOPRB_D&t;0x4001c8&t;/* PRB entry d */
DECL|macro|IIO_IOPRB_E
mdefine_line|#define IIO_IOPRB_E&t;0x4001d0&t;/* PRB entry e */
DECL|macro|IIO_IOPRB_F
mdefine_line|#define IIO_IOPRB_F&t;0x4001d8&t;/* PRB entry f */
DECL|macro|IIO_IXCC
mdefine_line|#define IIO_IXCC&t;0x4001e0&t;/* Crosstalk credit count timeout */
DECL|macro|IIO_IXTCC
mdefine_line|#define IIO_IXTCC&t;IIO_IXCC
DECL|macro|IIO_IMEM
mdefine_line|#define IIO_IMEM&t;0x4001e8&t;/* Miscellaneous Enable Mask */
DECL|macro|IIO_IXTT
mdefine_line|#define IIO_IXTT&t;0x4001f0&t;/* Crosstalk tail timeout */
DECL|macro|IIO_IECLR
mdefine_line|#define IIO_IECLR&t;0x4001f8&t;/* IO error clear */
DECL|macro|IIO_IBCN
mdefine_line|#define IIO_IBCN        0x400200        /* IO BTE CRB count */
multiline_comment|/* &n; * IIO_IMEM Register fields.&n; */
DECL|macro|IIO_IMEM_W0ESD
mdefine_line|#define IIO_IMEM_W0ESD  0x1             /* Widget 0 shut down due to error */
DECL|macro|IIO_IMEM_B0ESD
mdefine_line|#define IIO_IMEM_B0ESD  (1 &lt;&lt; 4)        /* BTE 0 shut down due to error */
DECL|macro|IIO_IMEM_B1ESD
mdefine_line|#define IIO_IMEM_B1ESD  (1 &lt;&lt; 8)        /* BTE 1 Shut down due to error */
multiline_comment|/* PIO Read address Table Entries */
DECL|macro|IIO_IPCA
mdefine_line|#define IIO_IPCA&t;0x400300&t;/* PRB Counter adjust */
DECL|macro|IIO_NUM_PRTES
mdefine_line|#define IIO_NUM_PRTES&t;8&t;&t;/* Total number of PRB table entries */
DECL|macro|IIO_PRTE_0
mdefine_line|#define IIO_PRTE_0&t;0x400308&t;/* PIO Read address table entry 0 */
DECL|macro|IIO_PRTE
mdefine_line|#define IIO_PRTE(_x)&t;(IIO_PRTE_0 + (8 * (_x)))
DECL|macro|IIO_WIDPRTE
mdefine_line|#define&t;IIO_WIDPRTE(x)&t;IIO_PRTE(((x) - 8)) /* widget ID to its PRTE num */
DECL|macro|IIO_IPDR
mdefine_line|#define IIO_IPDR&t;0x400388&t;/* PIO table entry deallocation */
DECL|macro|IIO_ICDR
mdefine_line|#define IIO_ICDR&t;0x400390&t;/* CRB Entry Deallocation */
DECL|macro|IIO_IFDR
mdefine_line|#define IIO_IFDR&t;0x400398&t;/* IOQ FIFO Depth */
DECL|macro|IIO_IIAP
mdefine_line|#define IIO_IIAP&t;0x4003a0&t;/* IIQ Arbitration Parameters */
DECL|macro|IIO_IMMR
mdefine_line|#define IIO_IMMR&t;IIO_IIAP
DECL|macro|IIO_ICMR
mdefine_line|#define IIO_ICMR&t;0x4003a8&t;/* CRB Managment Register */
DECL|macro|IIO_ICCR
mdefine_line|#define IIO_ICCR&t;0x4003b0&t;/* CRB Control Register */
DECL|macro|IIO_ICTO
mdefine_line|#define IIO_ICTO&t;0x4003b8&t;/* CRB Time Out Register */
DECL|macro|IIO_ICTP
mdefine_line|#define IIO_ICTP&t;0x4003c0&t;/* CRB Time Out Prescalar */
multiline_comment|/*&n; * ICMR register fields&n; */
DECL|macro|IIO_ICMR_PC_VLD_SHFT
mdefine_line|#define IIO_ICMR_PC_VLD_SHFT&t;36
DECL|macro|IIO_ICMR_PC_VLD_MASK
mdefine_line|#define IIO_ICMR_PC_VLD_MASK&t;(0x7fffUL &lt;&lt; IIO_ICMR_PC_VLD_SHFT)
DECL|macro|IIO_ICMR_CRB_VLD_SHFT
mdefine_line|#define IIO_ICMR_CRB_VLD_SHFT&t;20
DECL|macro|IIO_ICMR_CRB_VLD_MASK
mdefine_line|#define IIO_ICMR_CRB_VLD_MASK&t;(0x7fffUL &lt;&lt; IIO_ICMR_CRB_VLD_SHFT)
DECL|macro|IIO_ICMR_FC_CNT_SHFT
mdefine_line|#define IIO_ICMR_FC_CNT_SHFT&t;16
DECL|macro|IIO_ICMR_FC_CNT_MASK
mdefine_line|#define IIO_ICMR_FC_CNT_MASK&t;(0xf &lt;&lt; IIO_ICMR_FC_CNT_SHFT)
DECL|macro|IIO_ICMR_C_CNT_SHFT
mdefine_line|#define IIO_ICMR_C_CNT_SHFT&t;4
DECL|macro|IIO_ICMR_C_CNT_MASK
mdefine_line|#define IIO_ICMR_C_CNT_MASK&t;(0xf &lt;&lt; IIO_ICMR_C_CNT_SHFT)
DECL|macro|IIO_ICMR_P_CNT_SHFT
mdefine_line|#define IIO_ICMR_P_CNT_SHFT&t;0
DECL|macro|IIO_ICMR_P_CNT_MASK
mdefine_line|#define IIO_ICMR_P_CNT_MASK&t;(0xf &lt;&lt; IIO_ICMR_P_CNT_SHFT)
DECL|macro|IIO_ICMR_PRECISE
mdefine_line|#define IIO_ICMR_PRECISE&t;(1UL &lt;&lt; 52)
DECL|macro|IIO_ICMR_CLR_RPPD
mdefine_line|#define IIO_ICMR_CLR_RPPD&t;(1UL &lt;&lt; 13)
DECL|macro|IIO_ICMR_CLR_RQPD
mdefine_line|#define IIO_ICMR_CLR_RQPD&t;(1UL &lt;&lt; 12)
multiline_comment|/* &n; * IIO PIO Deallocation register field masks : (IIO_IPDR)&n; */
DECL|macro|IIO_IPDR_PND
mdefine_line|#define&t;IIO_IPDR_PND&t;(1 &lt;&lt; 4)
multiline_comment|/*&n; * IIO CRB deallocation register field masks: (IIO_ICDR)&n; */
DECL|macro|IIO_ICDR_PND
mdefine_line|#define&t;IIO_ICDR_PND&t;(1 &lt;&lt; 4)
multiline_comment|/*&n; * IIO CRB control register Fields: IIO_ICCR &n; */
DECL|macro|IIO_ICCR_PENDING
mdefine_line|#define&t;IIO_ICCR_PENDING&t;(0x10000)
DECL|macro|IIO_ICCR_CMD_MASK
mdefine_line|#define&t;IIO_ICCR_CMD_MASK&t;(0xFF)
DECL|macro|IIO_ICCR_CMD_SHFT
mdefine_line|#define&t;IIO_ICCR_CMD_SHFT&t;(7)
DECL|macro|IIO_ICCR_CMD_NOP
mdefine_line|#define&t;IIO_ICCR_CMD_NOP&t;(0x0)&t;/* No Op */
DECL|macro|IIO_ICCR_CMD_WAKE
mdefine_line|#define&t;IIO_ICCR_CMD_WAKE&t;(0x100) /* Reactivate CRB entry and process */
DECL|macro|IIO_ICCR_CMD_TIMEOUT
mdefine_line|#define&t;IIO_ICCR_CMD_TIMEOUT&t;(0x200)&t;/* Make CRB timeout &amp; mark invalid */
DECL|macro|IIO_ICCR_CMD_EJECT
mdefine_line|#define&t;IIO_ICCR_CMD_EJECT&t;(0x400)&t;/* Contents of entry written to memory &n;&t;&t;&t;&t;&t; * via a WB&n;&t;&t;&t;&t;&t; */
DECL|macro|IIO_ICCR_CMD_FLUSH
mdefine_line|#define&t;IIO_ICCR_CMD_FLUSH&t;(0x800)
multiline_comment|/*&n; * CRB manipulation macros&n; *&t;The CRB macros are slightly complicated, since there are up to&n; * &t;four registers associated with each CRB entry.&n; */
DECL|macro|IIO_NUM_CRBS
mdefine_line|#define IIO_NUM_CRBS&t;&t;15&t;/* Number of CRBs */
DECL|macro|IIO_NUM_NORMAL_CRBS
mdefine_line|#define IIO_NUM_NORMAL_CRBS     12&t;/* Number of regular CRB entries */
DECL|macro|IIO_NUM_PC_CRBS
mdefine_line|#define IIO_NUM_PC_CRBS &t;4&t;/* Number of partial cache CRBs */
DECL|macro|IIO_ICRB_OFFSET
mdefine_line|#define IIO_ICRB_OFFSET&t;&t;8
DECL|macro|IIO_ICRB_0
mdefine_line|#define IIO_ICRB_0&t;&t;0x400400
multiline_comment|/* XXX - This is now tuneable:&n;&t;#define IIO_FIRST_PC_ENTRY 12&n; */
DECL|macro|IIO_ICRB_A
mdefine_line|#define IIO_ICRB_A(_x)&t;(IIO_ICRB_0 + (4 * IIO_ICRB_OFFSET * (_x)))
DECL|macro|IIO_ICRB_B
mdefine_line|#define IIO_ICRB_B(_x)  (IIO_ICRB_A(_x) + 1*IIO_ICRB_OFFSET)
DECL|macro|IIO_ICRB_C
mdefine_line|#define IIO_ICRB_C(_x)&t;(IIO_ICRB_A(_x) + 2*IIO_ICRB_OFFSET)
DECL|macro|IIO_ICRB_D
mdefine_line|#define IIO_ICRB_D(_x)  (IIO_ICRB_A(_x) + 3*IIO_ICRB_OFFSET)
multiline_comment|/* XXX - IBUE register coming for Hub 2 */
multiline_comment|/*&n; *&n; * CRB Register description.&n; *&n; * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING&n; * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING&n; * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING&n; * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING&n; * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING&n; *&n; * Many of the fields in CRB are status bits used by hardware&n; * for implementation of the protocol. It&squot;s very dangerous to&n; * mess around with the CRB registers. &n; * &n; * It&squot;s OK to read the CRB registers and try to make sense out of the&n; * fields in CRB. &n; *&n; * Updating CRB requires all activities in Hub IIO to be quiesced. &n; * otherwise, a write to CRB could corrupt other CRB entries.&n; * CRBs are here only as a back door peek to hub IIO&squot;s status.&n; * Quiescing implies  no dmas no PIOs &n; * either directly from the cpu or from sn0net.&n; * this is not something that can be done easily. So, AVOID updating&n; * CRBs.&n; */
multiline_comment|/*&n; * Fields in CRB Register A&n; */
macro_line|#ifdef _LANGUAGE_C
DECL|union|icrba_u
r_typedef
r_union
id|icrba_u
(brace
DECL|member|reg_value
id|u64
id|reg_value
suffix:semicolon
r_struct
(brace
DECL|member|resvd
id|u64
id|resvd
suffix:colon
l_int|6
comma
DECL|member|stall_bte0
id|stall_bte0
suffix:colon
l_int|1
comma
multiline_comment|/* Stall BTE 0 */
DECL|member|stall_bte1
id|stall_bte1
suffix:colon
l_int|1
comma
multiline_comment|/* Stall BTE 1 */
DECL|member|error
id|error
suffix:colon
l_int|1
comma
multiline_comment|/* CRB has an error&t;*/
DECL|member|ecode
id|ecode
suffix:colon
l_int|3
comma
multiline_comment|/* Error Code &t;&t;*/
DECL|member|lnetuce
id|lnetuce
suffix:colon
l_int|1
comma
multiline_comment|/* SN0net Uncorrectable error */
DECL|member|mark
id|mark
suffix:colon
l_int|1
comma
multiline_comment|/* CRB Has been marked &t;*/
DECL|member|xerr
id|xerr
suffix:colon
l_int|1
comma
multiline_comment|/* Error bit set in xtalk header */
DECL|member|sidn
id|sidn
suffix:colon
l_int|4
comma
multiline_comment|/* SIDN field from xtalk&t;*/
DECL|member|tnum
id|tnum
suffix:colon
l_int|5
comma
multiline_comment|/* TNUM field in xtalk&t;&t;*/
DECL|member|addr
id|addr
suffix:colon
l_int|38
comma
multiline_comment|/* Address of request&t;*/
DECL|member|valid
id|valid
suffix:colon
l_int|1
comma
multiline_comment|/* Valid status&t;&t;*/
DECL|member|iow
id|iow
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* IO Write operation&t;*/
DECL|member|icrba_fields_s
)brace
id|icrba_fields_s
suffix:semicolon
DECL|typedef|icrba_t
)brace
id|icrba_t
suffix:semicolon
multiline_comment|/* This is an alternate typedef for the HUB1 CRB A in order to allow&n;   runtime selection of the format based on the REV_ID field of the&n;   NI_STATUS_REV_ID register. */
DECL|union|h1_icrba_u
r_typedef
r_union
id|h1_icrba_u
(brace
DECL|member|reg_value
id|u64
id|reg_value
suffix:semicolon
r_struct
(brace
DECL|member|resvd
id|u64
id|resvd
suffix:colon
l_int|6
comma
DECL|member|unused
id|unused
suffix:colon
l_int|1
comma
multiline_comment|/* Unused but RW!!&t;*/
DECL|member|error
id|error
suffix:colon
l_int|1
comma
multiline_comment|/* CRB has an error&t;*/
DECL|member|ecode
id|ecode
suffix:colon
l_int|4
comma
multiline_comment|/* Error Code &t;&t;*/
DECL|member|lnetuce
id|lnetuce
suffix:colon
l_int|1
comma
multiline_comment|/* SN0net Uncorrectable error */
DECL|member|mark
id|mark
suffix:colon
l_int|1
comma
multiline_comment|/* CRB Has been marked &t;*/
DECL|member|xerr
id|xerr
suffix:colon
l_int|1
comma
multiline_comment|/* Error bit set in xtalk header */
DECL|member|sidn
id|sidn
suffix:colon
l_int|4
comma
multiline_comment|/* SIDN field from xtalk&t;*/
DECL|member|tnum
id|tnum
suffix:colon
l_int|5
comma
multiline_comment|/* TNUM field in xtalk&t;&t;*/
DECL|member|addr
id|addr
suffix:colon
l_int|38
comma
multiline_comment|/* Address of request&t;*/
DECL|member|valid
id|valid
suffix:colon
l_int|1
comma
multiline_comment|/* Valid status&t;&t;*/
DECL|member|iow
id|iow
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* IO Write operation&t;*/
DECL|member|h1_icrba_fields_s
)brace
id|h1_icrba_fields_s
suffix:semicolon
DECL|typedef|h1_icrba_t
)brace
id|h1_icrba_t
suffix:semicolon
multiline_comment|/* XXX - Is this still right?  Check the spec. */
DECL|macro|ICRBN_A_CERR_SHFT
mdefine_line|#define ICRBN_A_CERR_SHFT&t;54
DECL|macro|ICRBN_A_ERR_MASK
mdefine_line|#define ICRBN_A_ERR_MASK&t;0x3ff
multiline_comment|/*&n; * Easy access macros.&n; */
DECL|macro|a_error
mdefine_line|#define&t;a_error&t;&t;icrba_fields_s.error
DECL|macro|a_ecode
mdefine_line|#define&t;a_ecode&t;&t;icrba_fields_s.ecode
DECL|macro|a_lnetuce
mdefine_line|#define&t;a_lnetuce&t;icrba_fields_s.lnetuce
DECL|macro|a_mark
mdefine_line|#define&t;a_mark&t;&t;icrba_fields_s.mark
DECL|macro|a_xerr
mdefine_line|#define&t;a_xerr&t;&t;icrba_fields_s.xerr
DECL|macro|a_sidn
mdefine_line|#define&t;a_sidn&t;&t;icrba_fields_s.sidn
DECL|macro|a_tnum
mdefine_line|#define&t;a_tnum&t;&t;icrba_fields_s.tnum
DECL|macro|a_addr
mdefine_line|#define&t;a_addr&t;&t;icrba_fields_s.addr
DECL|macro|a_valid
mdefine_line|#define&t;a_valid&t;&t;icrba_fields_s.valid
DECL|macro|a_iow
mdefine_line|#define&t;a_iow&t;&t;icrba_fields_s.iow
macro_line|#endif /* LANGUAGE_C */
DECL|macro|IIO_ICRB_ADDR_SHFT
mdefine_line|#define&t;IIO_ICRB_ADDR_SHFT&t;2&t;/* Shift to get proper address */
multiline_comment|/*&n; * values for &quot;ecode&quot; field &n; */
DECL|macro|IIO_ICRB_ECODE_DERR
mdefine_line|#define&t;IIO_ICRB_ECODE_DERR&t;0&t;/* Directory error due to IIO access */
DECL|macro|IIO_ICRB_ECODE_PERR
mdefine_line|#define&t;IIO_ICRB_ECODE_PERR&t;1&t;/* Poison error on IO access */
DECL|macro|IIO_ICRB_ECODE_WERR
mdefine_line|#define&t;IIO_ICRB_ECODE_WERR&t;2&t;/* Write error by IIO access &n;&t;&t;&t;&t;&t; * e.g. WINV to a Read only line.&n;&t;&t;&t;&t;&t; */
DECL|macro|IIO_ICRB_ECODE_AERR
mdefine_line|#define&t;IIO_ICRB_ECODE_AERR&t;3&t;/* Access error caused by IIO access */
DECL|macro|IIO_ICRB_ECODE_PWERR
mdefine_line|#define&t;IIO_ICRB_ECODE_PWERR&t;4&t;/* Error on partial write&t;*/
DECL|macro|IIO_ICRB_ECODE_PRERR
mdefine_line|#define&t;IIO_ICRB_ECODE_PRERR&t;5&t;/* Error on partial read&t;*/
DECL|macro|IIO_ICRB_ECODE_TOUT
mdefine_line|#define&t;IIO_ICRB_ECODE_TOUT&t;6&t;/* CRB timeout before deallocating */
DECL|macro|IIO_ICRB_ECODE_XTERR
mdefine_line|#define&t;IIO_ICRB_ECODE_XTERR&t;7&t;/* Incoming xtalk pkt had error bit */
multiline_comment|/*&n; * Fields in CRB Register B&n; */
macro_line|#ifdef _LANGUAGE_C
DECL|union|icrbb_u
r_typedef
r_union
id|icrbb_u
(brace
DECL|member|reg_value
id|u64
id|reg_value
suffix:semicolon
r_struct
(brace
DECL|member|rsvd1
id|u64
id|rsvd1
suffix:colon
l_int|5
comma
DECL|member|btenum
id|btenum
suffix:colon
l_int|1
comma
multiline_comment|/* BTE to which entry belongs to */
DECL|member|cohtrans
id|cohtrans
suffix:colon
l_int|1
comma
multiline_comment|/* Coherent transaction&t;*/
DECL|member|xtsize
id|xtsize
suffix:colon
l_int|2
comma
multiline_comment|/* Xtalk operation size&n;&t;&t;&t;&t; * 0: Double Word&n;&t;&t;&t;&t; * 1: 32 Bytes.&n;&t;&t;&t;&t; * 2: 128 Bytes,&n;&t;&t;&t;&t; * 3: Reserved.&n;&t;&t;&t;&t; */
DECL|member|srcnode
id|srcnode
suffix:colon
l_int|9
comma
multiline_comment|/* Source Node ID&t;&t;*/
DECL|member|srcinit
id|srcinit
suffix:colon
l_int|2
comma
multiline_comment|/* Source Initiator: &n;&t;&t;&t;&t; * See below for field values.&n;&t;&t;&t;&t; */
DECL|member|useold
id|useold
suffix:colon
l_int|1
comma
multiline_comment|/* Use OLD command for processing */
DECL|member|imsgtype
id|imsgtype
suffix:colon
l_int|2
comma
multiline_comment|/* Incoming message type&n;&t;&t;&t;&t; * see below for field values &n;&t;&t;&t;&t; */
DECL|member|imsg
id|imsg
suffix:colon
l_int|8
comma
multiline_comment|/* Incoming message &t;*/
DECL|member|initator
id|initator
suffix:colon
l_int|3
comma
multiline_comment|/* Initiator of original request &n;&t;&t;&t;&t; * See below for field values.&n;&t;&t;&t;&t; */
DECL|member|reqtype
id|reqtype
suffix:colon
l_int|5
comma
multiline_comment|/* Identifies type of request&n;&t;&t;&t;&t; * See below for field values.&n;&t;&t;&t;&t; */
DECL|member|rsvd2
id|rsvd2
suffix:colon
l_int|7
comma
DECL|member|ackcnt
id|ackcnt
suffix:colon
l_int|11
comma
multiline_comment|/* Invalidate ack count&t;*/
DECL|member|resp
id|resp
suffix:colon
l_int|1
comma
multiline_comment|/* data response  given to processor */
DECL|member|ack
id|ack
suffix:colon
l_int|1
comma
multiline_comment|/* indicates data ack received &t;*/
DECL|member|hold
id|hold
suffix:colon
l_int|1
comma
multiline_comment|/* entry is gathering inval acks */
DECL|member|wb_pend
id|wb_pend
suffix:colon
l_int|1
comma
multiline_comment|/* waiting for writeback to complete */
DECL|member|intvn
id|intvn
suffix:colon
l_int|1
comma
multiline_comment|/* Intervention */
DECL|member|stall_ib
id|stall_ib
suffix:colon
l_int|1
comma
multiline_comment|/* Stall Ibuf (from crosstalk) */
DECL|member|stall_intr
id|stall_intr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Stall internal interrupts */
DECL|member|icrbb_field_s
)brace
id|icrbb_field_s
suffix:semicolon
DECL|typedef|icrbb_t
)brace
id|icrbb_t
suffix:semicolon
multiline_comment|/* This is an alternate typedef for the HUB1 CRB B in order to allow&n;   runtime selection of the format based on the REV_ID field of the&n;   NI_STATUS_REV_ID register. */
DECL|union|h1_icrbb_u
r_typedef
r_union
id|h1_icrbb_u
(brace
DECL|member|reg_value
id|u64
id|reg_value
suffix:semicolon
r_struct
(brace
DECL|member|rsvd1
id|u64
id|rsvd1
suffix:colon
l_int|5
comma
DECL|member|btenum
id|btenum
suffix:colon
l_int|1
comma
multiline_comment|/* BTE to which entry belongs to */
DECL|member|cohtrans
id|cohtrans
suffix:colon
l_int|1
comma
multiline_comment|/* Coherent transaction&t;*/
DECL|member|xtsize
id|xtsize
suffix:colon
l_int|2
comma
multiline_comment|/* Xtalk operation size&n;&t;&t;&t;&t;&t; * 0: Double Word&n;&t;&t;&t;&t;&t; * 1: 32 Bytes.&n;&t;&t;&t;&t;&t; * 2: 128 Bytes,&n;&t;&t;&t;&t;&t; * 3: Reserved.&n;&t;&t;&t;&t;&t; */
DECL|member|srcnode
id|srcnode
suffix:colon
l_int|9
comma
multiline_comment|/* Source Node ID&t;&t;*/
DECL|member|srcinit
id|srcinit
suffix:colon
l_int|2
comma
multiline_comment|/* Source Initiator: &n;&t;&t;&t;&t;&t; * See below for field values.&n;&t;&t;&t;&t;&t; */
DECL|member|useold
id|useold
suffix:colon
l_int|1
comma
multiline_comment|/* Use OLD command for processing */
DECL|member|imsgtype
id|imsgtype
suffix:colon
l_int|2
comma
multiline_comment|/* Incoming message type&n;&t;&t;&t;&t;&t; * see below for field values &n;&t;&t;&t;&t;&t; */
DECL|member|imsg
id|imsg
suffix:colon
l_int|8
comma
multiline_comment|/* Incoming message &t;*/
DECL|member|initator
id|initator
suffix:colon
l_int|3
comma
multiline_comment|/* Initiator of original request &n;&t;&t;&t;&t;&t; * See below for field values.&n;&t;&t;&t;&t;&t; */
DECL|member|rsvd2
id|rsvd2
suffix:colon
l_int|1
comma
DECL|member|pcache
id|pcache
suffix:colon
l_int|1
comma
multiline_comment|/* entry belongs to partial cache */
DECL|member|reqtype
id|reqtype
suffix:colon
l_int|5
comma
multiline_comment|/* Identifies type of request&n;&t;&t;&t;&t;&t; * See below for field values.&n;&t;&t;&t;&t;&t; */
DECL|member|stl_ib
id|stl_ib
suffix:colon
l_int|1
comma
multiline_comment|/* stall Ibus coming from xtalk&t;*/
DECL|member|stl_intr
id|stl_intr
suffix:colon
l_int|1
comma
multiline_comment|/* Stall internal interrupts */
DECL|member|stl_bte0
id|stl_bte0
suffix:colon
l_int|1
comma
multiline_comment|/* Stall BTE 0 &t;*/
DECL|member|stl_bte1
id|stl_bte1
suffix:colon
l_int|1
comma
multiline_comment|/* Stall BTE 1&t;*/
DECL|member|intrvn
id|intrvn
suffix:colon
l_int|1
comma
multiline_comment|/* Req was target of intervention */
DECL|member|ackcnt
id|ackcnt
suffix:colon
l_int|11
comma
multiline_comment|/* Invalidate ack count&t;*/
DECL|member|resp
id|resp
suffix:colon
l_int|1
comma
multiline_comment|/* data response  given to processor */
DECL|member|ack
id|ack
suffix:colon
l_int|1
comma
multiline_comment|/* indicates data ack received &t;*/
DECL|member|hold
id|hold
suffix:colon
l_int|1
comma
multiline_comment|/* entry is gathering inval acks */
DECL|member|wb_pend
id|wb_pend
suffix:colon
l_int|1
comma
multiline_comment|/* waiting for writeback to complete */
DECL|member|sleep
id|sleep
suffix:colon
l_int|1
comma
multiline_comment|/* xtalk req sleeping till IO-sync */
DECL|member|pnd_reply
id|pnd_reply
suffix:colon
l_int|1
comma
multiline_comment|/* replies not issed due to IOQ full */
DECL|member|pnd_req
id|pnd_req
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reqs not issued due to IOQ full */
DECL|member|h1_icrbb_field_s
)brace
id|h1_icrbb_field_s
suffix:semicolon
DECL|typedef|h1_icrbb_t
)brace
id|h1_icrbb_t
suffix:semicolon
DECL|macro|b_imsgtype
mdefine_line|#define&t;b_imsgtype&t;icrbb_field_s.imsgtype
DECL|macro|b_btenum
mdefine_line|#define&t;b_btenum&t;icrbb_field_s.btenum
DECL|macro|b_cohtrans
mdefine_line|#define&t;b_cohtrans&t;icrbb_field_s.cohtrans
DECL|macro|b_xtsize
mdefine_line|#define&t;b_xtsize&t;icrbb_field_s.xtsize
DECL|macro|b_srcnode
mdefine_line|#define&t;b_srcnode&t;icrbb_field_s.srcnode
DECL|macro|b_srcinit
mdefine_line|#define&t;b_srcinit&t;icrbb_field_s.srcinit
DECL|macro|b_imsgtype
mdefine_line|#define&t;b_imsgtype&t;icrbb_field_s.imsgtype
DECL|macro|b_imsg
mdefine_line|#define&t;b_imsg&t;&t;icrbb_field_s.imsg
DECL|macro|b_initiator
mdefine_line|#define&t;b_initiator&t;icrbb_field_s.initiator
macro_line|#endif /* LANGUAGE_C */
multiline_comment|/*&n; * values for field xtsize&n; */
DECL|macro|IIO_ICRB_XTSIZE_DW
mdefine_line|#define&t;IIO_ICRB_XTSIZE_DW&t;0&t;/* Xtalk operation size is 8 bytes  */
DECL|macro|IIO_ICRB_XTSIZE_32
mdefine_line|#define&t;IIO_ICRB_XTSIZE_32&t;1&t;/* Xtalk operation size is 32 bytes */
DECL|macro|IIO_ICRB_XTSIZE_128
mdefine_line|#define&t;IIO_ICRB_XTSIZE_128&t;2&t;/* Xtalk operation size is 128 bytes */
multiline_comment|/*&n; * values for field srcinit&n; */
DECL|macro|IIO_ICRB_PROC0
mdefine_line|#define&t;IIO_ICRB_PROC0&t;&t;0&t;/* Source of request is Proc 0 */
DECL|macro|IIO_ICRB_PROC1
mdefine_line|#define&t;IIO_ICRB_PROC1&t;&t;1&t;/* Source of request is Proc 1 */
DECL|macro|IIO_ICRB_GB_REQ
mdefine_line|#define&t;IIO_ICRB_GB_REQ&t;&t;2&t;/* Source is Guranteed BW request */
DECL|macro|IIO_ICRB_IO_REQ
mdefine_line|#define&t;IIO_ICRB_IO_REQ&t;&t;3&t;/* Source is Normal IO request&t;*/
multiline_comment|/*&n; * Values for field imsgtype&n; */
DECL|macro|IIO_ICRB_IMSGT_XTALK
mdefine_line|#define&t;IIO_ICRB_IMSGT_XTALK&t;0&t;/* Incoming Meessage from Xtalk&t;*/
DECL|macro|IIO_ICRB_IMSGT_BTE
mdefine_line|#define&t;IIO_ICRB_IMSGT_BTE&t;1&t;/* Incoming message from BTE &t;*/
DECL|macro|IIO_ICRB_IMSGT_SN0NET
mdefine_line|#define&t;IIO_ICRB_IMSGT_SN0NET&t;2&t;/* Incoming message from SN0 net */
DECL|macro|IIO_ICRB_IMSGT_CRB
mdefine_line|#define&t;IIO_ICRB_IMSGT_CRB&t;3&t;/* Incoming message from CRB ???  */
multiline_comment|/*&n; * values for field initiator.&n; */
DECL|macro|IIO_ICRB_INIT_XTALK
mdefine_line|#define&t;IIO_ICRB_INIT_XTALK&t;0&t;/* Message originated in xtalk&t;*/
DECL|macro|IIO_ICRB_INIT_BTE0
mdefine_line|#define&t;IIO_ICRB_INIT_BTE0&t;0x1&t;/* Message originated in BTE 0&t;*/
DECL|macro|IIO_ICRB_INIT_SN0NET
mdefine_line|#define&t;IIO_ICRB_INIT_SN0NET&t;0x2&t;/* Message originated in SN0net */
DECL|macro|IIO_ICRB_INIT_CRB
mdefine_line|#define&t;IIO_ICRB_INIT_CRB&t;0x3&t;/* Message originated in CRB ? &t;*/
DECL|macro|IIO_ICRB_INIT_BTE1
mdefine_line|#define&t;IIO_ICRB_INIT_BTE1&t;0x5&t;/* MEssage originated in BTE 1&t;*/
multiline_comment|/*&n; * Values for field reqtype.&n; */
multiline_comment|/* XXX - Need to fix this for Hub 2 */
DECL|macro|IIO_ICRB_REQ_DWRD
mdefine_line|#define&t;IIO_ICRB_REQ_DWRD&t;0&t;/* Request type double word&t;*/
DECL|macro|IIO_ICRB_REQ_QCLRD
mdefine_line|#define&t;IIO_ICRB_REQ_QCLRD&t;1&t;/* Request is Qrtr Caceh line Rd */
DECL|macro|IIO_ICRB_REQ_BLKRD
mdefine_line|#define&t;IIO_ICRB_REQ_BLKRD&t;2&t;/* Request is block read&t;*/
DECL|macro|IIO_ICRB_REQ_RSHU
mdefine_line|#define&t;IIO_ICRB_REQ_RSHU&t;6&t;/* Request is BTE block read&t;*/
DECL|macro|IIO_ICRB_REQ_REXU
mdefine_line|#define&t;IIO_ICRB_REQ_REXU&t;7&t;/* request is BTE Excl Read&t;*/
DECL|macro|IIO_ICRB_REQ_RDEX
mdefine_line|#define&t;IIO_ICRB_REQ_RDEX&t;8&t;/* Request is Read Exclusive&t;*/
DECL|macro|IIO_ICRB_REQ_WINC
mdefine_line|#define&t;IIO_ICRB_REQ_WINC&t;9&t;/* Request is Write Invalidate &t;*/
DECL|macro|IIO_ICRB_REQ_BWINV
mdefine_line|#define&t;IIO_ICRB_REQ_BWINV&t;10&t;/* Request is BTE Winv&t;&t;*/
DECL|macro|IIO_ICRB_REQ_PIORD
mdefine_line|#define&t;IIO_ICRB_REQ_PIORD&t;11&t;/* Request is PIO read&t;&t;*/
DECL|macro|IIO_ICRB_REQ_PIOWR
mdefine_line|#define&t;IIO_ICRB_REQ_PIOWR&t;12&t;/* Request is PIO Write &t;*/
DECL|macro|IIO_ICRB_REQ_PRDM
mdefine_line|#define&t;IIO_ICRB_REQ_PRDM&t;13&t;/* Request is Fetch&amp;Op&t;&t;*/
DECL|macro|IIO_ICRB_REQ_PWRM
mdefine_line|#define&t;IIO_ICRB_REQ_PWRM&t;14&t;/* Request is Store &amp;Op&t;&t;*/
DECL|macro|IIO_ICRB_REQ_PTPWR
mdefine_line|#define&t;IIO_ICRB_REQ_PTPWR&t;15&t;/* Request is Peer to peer&t;*/
DECL|macro|IIO_ICRB_REQ_WB
mdefine_line|#define&t;IIO_ICRB_REQ_WB&t;&t;16&t;/* Request is Write back&t;*/
DECL|macro|IIO_ICRB_REQ_DEX
mdefine_line|#define&t;IIO_ICRB_REQ_DEX&t;17&t;/* Retained DEX Cache line&t;*/
multiline_comment|/* &n; * Fields in CRB Register C &n; */
macro_line|#ifdef _LANGUAGE_C
DECL|union|icrbc_s
r_typedef
r_union
id|icrbc_s
(brace
DECL|member|reg_value
id|u64
id|reg_value
suffix:semicolon
r_struct
(brace
DECL|member|rsvd
id|u64
id|rsvd
suffix:colon
l_int|6
comma
DECL|member|sleep
id|sleep
suffix:colon
l_int|1
comma
DECL|member|pricnt
id|pricnt
suffix:colon
l_int|4
comma
multiline_comment|/* Priority count sent with Read req */
DECL|member|pripsc
id|pripsc
suffix:colon
l_int|4
comma
multiline_comment|/* Priority Pre scalar &t;*/
DECL|member|bteop
id|bteop
suffix:colon
l_int|1
comma
multiline_comment|/* BTE Operation &t;*/
DECL|member|push_be
id|push_be
suffix:colon
l_int|34
comma
multiline_comment|/* Push address Byte enable &n;&t;&t;&t;&t;&t; * Holds push addr, if CRB is for BTE&n;&t;&t;&t;&t;&t; * If CRB belongs to Partial cache,&n;&t;&t;&t;&t;&t; * this contains byte enables bits&n;&t;&t;&t;&t;&t; * ([47:46] = 0)&n;&t;&t;&t;&t;&t; */
DECL|member|suppl
id|suppl
suffix:colon
l_int|11
comma
multiline_comment|/* Supplemental field&t;*/
DECL|member|barrop
id|barrop
suffix:colon
l_int|1
comma
multiline_comment|/* Barrier Op bit set in xtalk req */
DECL|member|doresp
id|doresp
suffix:colon
l_int|1
comma
multiline_comment|/* Xtalk req needs a response &t;*/
DECL|member|gbr
id|gbr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* GBR bit set in xtalk packet &t;*/
DECL|member|icrbc_field_s
)brace
id|icrbc_field_s
suffix:semicolon
DECL|typedef|icrbc_t
)brace
id|icrbc_t
suffix:semicolon
DECL|macro|c_pricnt
mdefine_line|#define&t;c_pricnt&t;icrbc_field_s.pricnt
DECL|macro|c_pripsc
mdefine_line|#define&t;c_pripsc&t;icrbc_field_s.pripsc
DECL|macro|c_bteop
mdefine_line|#define&t;c_bteop&t;&t;icrbc_field_s.bteop
DECL|macro|c_bteaddr
mdefine_line|#define&t;c_bteaddr&t;icrbc_field_s.push_be&t;/* push_be field has 2 names */
DECL|macro|c_benable
mdefine_line|#define c_benable &t;icrbc_field_s.push_be&t;/* push_be field has 2 names */
DECL|macro|c_suppl
mdefine_line|#define&t;c_suppl&t;&t;icrbc_field_s.suppl
DECL|macro|c_barrop
mdefine_line|#define&t;c_barrop&t;icrbc_field_s.barrop
DECL|macro|c_doresp
mdefine_line|#define&t;c_doresp&t;icrbc_field_s.doresp
DECL|macro|c_gbr
mdefine_line|#define&t;c_gbr&t;icrbc_field_s.gbr
macro_line|#endif /* LANGUAGE_C */
multiline_comment|/*&n; * Fields in CRB Register D&n; */
macro_line|#ifdef _LANGUAGE_C
DECL|union|icrbd_s
r_typedef
r_union
id|icrbd_s
(brace
DECL|member|reg_value
id|u64
id|reg_value
suffix:semicolon
r_struct
(brace
DECL|member|rsvd
id|u64
id|rsvd
suffix:colon
l_int|38
comma
DECL|member|toutvld
id|toutvld
suffix:colon
l_int|1
comma
multiline_comment|/* Timeout in progress for this CRB */
DECL|member|ctxtvld
id|ctxtvld
suffix:colon
l_int|1
comma
multiline_comment|/* Context field below is valid&t;*/
DECL|member|rsvd2
id|rsvd2
suffix:colon
l_int|1
comma
DECL|member|context
id|context
suffix:colon
l_int|15
comma
multiline_comment|/* Bit vector:&n;&t;&t;&t;&t; * Has a bit set for each CRB entry&n;&t;&t;&t;&t; * which needs to be deallocated&n;&t;&t;&t;&t; * before this CRB entry is processed.&n;&t;&t;&t;&t; * Set only for barrier operations.&n;&t;&t;&t;&t; */
DECL|member|timeout
id|timeout
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Timeout Upper 8 bits&t;*/
DECL|member|icrbd_field_s
)brace
id|icrbd_field_s
suffix:semicolon
DECL|typedef|icrbd_t
)brace
id|icrbd_t
suffix:semicolon
DECL|macro|icrbd_toutvld
mdefine_line|#define&t;icrbd_toutvld&t;icrbd_field_s.toutvld
DECL|macro|icrbd_ctxtvld
mdefine_line|#define&t;icrbd_ctxtvld&t;icrbd_field_s.ctxtvld
DECL|macro|icrbd_context
mdefine_line|#define&t;icrbd_context&t;icrbd_field_s.context
DECL|union|hubii_ifdr_u
r_typedef
r_union
id|hubii_ifdr_u
(brace
DECL|member|hi_ifdr_value
id|u64
id|hi_ifdr_value
suffix:semicolon
r_struct
(brace
DECL|member|ifdr_rsvd
id|u64
id|ifdr_rsvd
suffix:colon
l_int|49
comma
DECL|member|ifdr_maxrp
id|ifdr_maxrp
suffix:colon
l_int|7
comma
DECL|member|ifdr_rsvd1
id|ifdr_rsvd1
suffix:colon
l_int|1
comma
DECL|member|ifdr_maxrq
id|ifdr_maxrq
suffix:colon
l_int|7
suffix:semicolon
DECL|member|hi_ifdr_fields
)brace
id|hi_ifdr_fields
suffix:semicolon
DECL|typedef|hubii_ifdr_t
)brace
id|hubii_ifdr_t
suffix:semicolon
macro_line|#endif /* LANGUAGE_C */
multiline_comment|/*&n; * Hardware designed names for the BTE control registers.&n; */
DECL|macro|IIO_IBLS_0
mdefine_line|#define IIO_IBLS_0&t;0x410000&t;/* BTE length/status 0 */
DECL|macro|IIO_IBSA_0
mdefine_line|#define IIO_IBSA_0&t;0x410008&t;/* BTE source address 0 */
DECL|macro|IIO_IBDA_0
mdefine_line|#define IIO_IBDA_0&t;0x410010&t;/* BTE destination address 0 */
DECL|macro|IIO_IBCT_0
mdefine_line|#define IIO_IBCT_0&t;0x410018&t;/* BTE control/terminate 0 */
DECL|macro|IIO_IBNA_0
mdefine_line|#define IIO_IBNA_0&t;0x410020&t;/* BTE notification address 0 */
DECL|macro|IIO_IBNR_0
mdefine_line|#define IIO_IBNR_0&t;IIO_IBNA_0
DECL|macro|IIO_IBIA_0
mdefine_line|#define IIO_IBIA_0&t;0x410028&t;/* BTE interrupt address 0 */&t;
DECL|macro|IIO_IBLS_1
mdefine_line|#define IIO_IBLS_1&t;0x420000&t;/* BTE length/status 1 */
DECL|macro|IIO_IBSA_1
mdefine_line|#define IIO_IBSA_1&t;0x420008&t;/* BTE source address 1 */
DECL|macro|IIO_IBDA_1
mdefine_line|#define IIO_IBDA_1&t;0x420010&t;/* BTE destination address 1 */
DECL|macro|IIO_IBCT_1
mdefine_line|#define IIO_IBCT_1&t;0x420018&t;/* BTE control/terminate 1 */
DECL|macro|IIO_IBNA_1
mdefine_line|#define IIO_IBNA_1&t;0x420020&t;/* BTE notification address 1 */
DECL|macro|IIO_IBNR_1
mdefine_line|#define IIO_IBNR_1&t;IIO_IBNA_1
DECL|macro|IIO_IBIA_1
mdefine_line|#define IIO_IBIA_1&t;0x420028&t;/* BTE interrupt address 1 */&t;
multiline_comment|/*&n; * More miscellaneous registers&n; */
DECL|macro|IIO_IPCR
mdefine_line|#define IIO_IPCR&t;0x430000&t;/* Performance Control */
DECL|macro|IIO_IPPR
mdefine_line|#define IIO_IPPR&t;0x430008&t;/* Performance Profiling */
multiline_comment|/*&n; * IO Error Clear register bit field definitions&n; */
DECL|macro|IECLR_BTE1
mdefine_line|#define IECLR_BTE1&t;&t;(1 &lt;&lt; 18)  /* clear bte error 1 ??? */
DECL|macro|IECLR_BTE0
mdefine_line|#define IECLR_BTE0&t;&t;(1 &lt;&lt; 17)  /* clear bte error 0 ??? */
DECL|macro|IECLR_CRAZY
mdefine_line|#define IECLR_CRAZY&t;&t;(1 &lt;&lt; 16)  /* clear crazy bit in wstat reg */
DECL|macro|IECLR_PRB_F
mdefine_line|#define IECLR_PRB_F&t;&t;(1 &lt;&lt; 15)  /* clear err bit in PRB_F reg */
DECL|macro|IECLR_PRB_E
mdefine_line|#define IECLR_PRB_E&t;&t;(1 &lt;&lt; 14)  /* clear err bit in PRB_E reg */
DECL|macro|IECLR_PRB_D
mdefine_line|#define IECLR_PRB_D&t;&t;(1 &lt;&lt; 13)  /* clear err bit in PRB_D reg */
DECL|macro|IECLR_PRB_C
mdefine_line|#define IECLR_PRB_C&t;&t;(1 &lt;&lt; 12)  /* clear err bit in PRB_C reg */
DECL|macro|IECLR_PRB_B
mdefine_line|#define IECLR_PRB_B&t;&t;(1 &lt;&lt; 11)  /* clear err bit in PRB_B reg */
DECL|macro|IECLR_PRB_A
mdefine_line|#define IECLR_PRB_A&t;&t;(1 &lt;&lt; 10)  /* clear err bit in PRB_A reg */
DECL|macro|IECLR_PRB_9
mdefine_line|#define IECLR_PRB_9&t;&t;(1 &lt;&lt; 9)   /* clear err bit in PRB_9 reg */
DECL|macro|IECLR_PRB_8
mdefine_line|#define IECLR_PRB_8&t;&t;(1 &lt;&lt; 8)   /* clear err bit in PRB_8 reg */
DECL|macro|IECLR_PRB_0
mdefine_line|#define IECLR_PRB_0&t;&t;(1 &lt;&lt; 0)   /* clear err bit in PRB_0 reg */
multiline_comment|/*&n; * IO PIO Read Table Entry format &n; */
macro_line|#ifdef&t;_LANGUAGE_C
DECL|union|iprte_a
r_typedef
r_union
id|iprte_a
(brace
DECL|member|entry
id|u64
id|entry
suffix:semicolon
r_struct
(brace
DECL|member|rsvd1
id|u64
id|rsvd1
suffix:colon
l_int|7
comma
multiline_comment|/* Reserved field &t;&t;*/
DECL|member|valid
id|valid
suffix:colon
l_int|1
comma
multiline_comment|/* Maps to a timeout entry&t;*/
DECL|member|rsvd2
id|rsvd2
suffix:colon
l_int|1
comma
DECL|member|srcnode
id|srcnode
suffix:colon
l_int|9
comma
multiline_comment|/* Node which did this PIO&t;*/
DECL|member|initiator
id|initiator
suffix:colon
l_int|2
comma
multiline_comment|/* If T5A or T5B or IO &t;&t;*/
DECL|member|rsvd3
id|rsvd3
suffix:colon
l_int|3
comma
DECL|member|addr
id|addr
suffix:colon
l_int|38
comma
multiline_comment|/* Physical address of PIO&t;*/
DECL|member|rsvd4
id|rsvd4
suffix:colon
l_int|3
suffix:semicolon
DECL|member|iprte_fields
)brace
id|iprte_fields
suffix:semicolon
DECL|typedef|iprte_a_t
)brace
id|iprte_a_t
suffix:semicolon
DECL|macro|iprte_valid
mdefine_line|#define&t;iprte_valid&t;iprte_fields.valid
DECL|macro|iprte_timeout
mdefine_line|#define&t;iprte_timeout&t;iprte_fields.timeout
DECL|macro|iprte_srcnode
mdefine_line|#define&t;iprte_srcnode&t;iprte_fields.srcnode
DECL|macro|iprte_init
mdefine_line|#define&t;iprte_init&t;iprte_fields.initiator
DECL|macro|iprte_addr
mdefine_line|#define&t;iprte_addr&t;iprte_fields.addr
macro_line|#endif /* _LANGUAGE_C */
DECL|macro|IPRTE_ADDRSHFT
mdefine_line|#define&t;IPRTE_ADDRSHFT&t;3
multiline_comment|/*&n; * Hub IIO PRB Register format.&n; */
macro_line|#ifdef&t;_LANGUAGE_C
multiline_comment|/*&n; * Note: Fields bnakctr, anakctr, xtalkctrmode, ovflow fields are &n; * &quot;Status&quot; fields, and should only be used in case of clean up after errors.&n; */
DECL|union|iprb_u
r_typedef
r_union
id|iprb_u
(brace
DECL|member|reg_value
id|u64
id|reg_value
suffix:semicolon
r_struct
(brace
DECL|member|rsvd1
id|u64
id|rsvd1
suffix:colon
l_int|15
comma
DECL|member|error
id|error
suffix:colon
l_int|1
comma
multiline_comment|/* Widget rcvd wr resp pkt w/ error */
DECL|member|ovflow
id|ovflow
suffix:colon
l_int|5
comma
multiline_comment|/* Over flow count. perf measurement */
DECL|member|fire_and_forget
id|fire_and_forget
suffix:colon
l_int|1
comma
multiline_comment|/* Launch Write without response */
DECL|member|mode
id|mode
suffix:colon
l_int|2
comma
multiline_comment|/* Widget operation Mode&t;*/
DECL|member|rsvd2
id|rsvd2
suffix:colon
l_int|2
comma
DECL|member|bnakctr
id|bnakctr
suffix:colon
l_int|14
comma
DECL|member|rsvd3
id|rsvd3
suffix:colon
l_int|2
comma
DECL|member|anakctr
id|anakctr
suffix:colon
l_int|14
comma
DECL|member|xtalkctr
id|xtalkctr
suffix:colon
l_int|8
suffix:semicolon
DECL|member|iprb_fields_s
)brace
id|iprb_fields_s
suffix:semicolon
DECL|typedef|iprb_t
)brace
id|iprb_t
suffix:semicolon
DECL|macro|iprb_regval
mdefine_line|#define iprb_regval&t;reg_value
DECL|macro|iprb_error
mdefine_line|#define&t;iprb_error&t;iprb_fields_s.error
DECL|macro|iprb_ovflow
mdefine_line|#define&t;iprb_ovflow&t;iprb_fields_s.ovflow
DECL|macro|iprb_ff
mdefine_line|#define&t;iprb_ff&t;&t;iprb_fields_s.fire_and_forget
DECL|macro|iprb_mode
mdefine_line|#define&t;iprb_mode&t;iprb_fields_s.mode
DECL|macro|iprb_bnakctr
mdefine_line|#define&t;iprb_bnakctr&t;iprb_fields_s.bnakctr
DECL|macro|iprb_anakctr
mdefine_line|#define&t;iprb_anakctr&t;iprb_fields_s.anakctr
DECL|macro|iprb_xtalkctr
mdefine_line|#define&t;iprb_xtalkctr&t;iprb_fields_s.xtalkctr
macro_line|#endif&t;/* _LANGUAGE_C */
multiline_comment|/*&n; * values for mode field in iprb_t.&n; * For details of the meanings of NAK and Accept, refer the PIO flow&n; * document&n; */
DECL|macro|IPRB_MODE_NORMAL
mdefine_line|#define&t;IPRB_MODE_NORMAL&t;(0)
DECL|macro|IPRB_MODE_COLLECT_A
mdefine_line|#define&t;IPRB_MODE_COLLECT_A&t;(1)&t;/* PRB in collect A mode */
DECL|macro|IPRB_MODE_SERVICE_A
mdefine_line|#define&t;IPRB_MODE_SERVICE_A&t;(2)&t;/* NAK B and Accept A */
DECL|macro|IPRB_MODE_SERVICE_B
mdefine_line|#define&t;IPRB_MODE_SERVICE_B&t;(3)&t;/* NAK A and Accept B */
multiline_comment|/*&n; * IO CRB entry C_A to E_A : Partial (cache) CRBS&n; */
macro_line|#ifdef _LANGUAGE_C
DECL|union|icrbp_a
r_typedef
r_union
id|icrbp_a
(brace
DECL|member|ip_reg
id|u64
id|ip_reg
suffix:semicolon
multiline_comment|/* the entire register value&t;*/
r_struct
(brace
DECL|member|error
id|u64
id|error
suffix:colon
l_int|1
comma
multiline_comment|/*    63, error occurred&t;&t;*/
DECL|member|ln_uce
id|ln_uce
suffix:colon
l_int|1
comma
multiline_comment|/*    62: uncorrectable memory &t;*/
DECL|member|ln_ae
id|ln_ae
suffix:colon
l_int|1
comma
multiline_comment|/*    61: protection violation &t;*/
DECL|member|ln_werr
id|ln_werr
suffix:colon
l_int|1
comma
multiline_comment|/*    60: write access error &t;*/
DECL|member|ln_aerr
id|ln_aerr
suffix:colon
l_int|1
comma
multiline_comment|/*    59: sn0net: Address error&t;*/
DECL|member|ln_perr
id|ln_perr
suffix:colon
l_int|1
comma
multiline_comment|/*    58: sn0net: poison error&t;*/
DECL|member|timeout
id|timeout
suffix:colon
l_int|1
comma
multiline_comment|/*    57: CRB timed out&t;&t;*/
DECL|member|l_bdpkt
id|l_bdpkt
suffix:colon
l_int|1
comma
multiline_comment|/*    56: truncated pkt on sn0net&t;*/
DECL|member|c_bdpkt
id|c_bdpkt
suffix:colon
l_int|1
comma
multiline_comment|/*    55: truncated pkt on xtalk&t;*/
DECL|member|c_err
id|c_err
suffix:colon
l_int|1
comma
multiline_comment|/*    54: incoming xtalk req, err set*/
DECL|member|rsvd1
id|rsvd1
suffix:colon
l_int|12
comma
multiline_comment|/* 53-42: reserved&t;&t;&t;*/
DECL|member|valid
id|valid
suffix:colon
l_int|1
comma
multiline_comment|/*    41: Valid status&t;&t;*/
DECL|member|sidn
id|sidn
suffix:colon
l_int|4
comma
multiline_comment|/* 40-37: SIDN field of xtalk rqst&t;*/
DECL|member|tnum
id|tnum
suffix:colon
l_int|5
comma
multiline_comment|/* 36-32: TNUM of xtalk request&t;*/
DECL|member|bo
id|bo
suffix:colon
l_int|1
comma
multiline_comment|/*    31: barrier op set in xtalk rqst*/
DECL|member|resprqd
id|resprqd
suffix:colon
l_int|1
comma
multiline_comment|/*    30: xtalk rqst requires response*/
DECL|member|gbr
id|gbr
suffix:colon
l_int|1
comma
multiline_comment|/*    29: gbr bit set in xtalk rqst&t;*/
DECL|member|size
id|size
suffix:colon
l_int|2
comma
multiline_comment|/* 28-27: size of xtalk request&t;*/
DECL|member|excl
id|excl
suffix:colon
l_int|4
comma
multiline_comment|/* 26-23: exclusive bit(s)&t;&t;*/
DECL|member|stall
id|stall
suffix:colon
l_int|3
comma
multiline_comment|/* 22-20: stall (xtalk, bte 0/1)&t;*/
DECL|member|intvn
id|intvn
suffix:colon
l_int|1
comma
multiline_comment|/*    19: rqst target of intervention*/
DECL|member|resp
id|resp
suffix:colon
l_int|1
comma
multiline_comment|/*    18: Data response given to t5&t;*/
DECL|member|ack
id|ack
suffix:colon
l_int|1
comma
multiline_comment|/*    17: Data ack received.&t;*/
DECL|member|hold
id|hold
suffix:colon
l_int|1
comma
multiline_comment|/*    16: crb gathering invalidate acks*/
DECL|member|wb
id|wb
suffix:colon
l_int|1
comma
multiline_comment|/*    15: writeback pending.&t;*/
DECL|member|ack_cnt
id|ack_cnt
suffix:colon
l_int|11
comma
multiline_comment|/* 14-04: counter of invalidate acks*/
DECL|member|tscaler
id|tscaler
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 03-00: Timeout prescaler&t;&t;*/
DECL|member|ip_fmt
)brace
id|ip_fmt
suffix:semicolon
DECL|typedef|icrbp_a_t
)brace
id|icrbp_a_t
suffix:semicolon
macro_line|#endif /* _LANGUAGE_C */
multiline_comment|/*&n; * A couple of defines to go with the above structure.&n; */
DECL|macro|ICRBP_A_CERR_SHFT
mdefine_line|#define ICRBP_A_CERR_SHFT&t;54
DECL|macro|ICRBP_A_ERR_MASK
mdefine_line|#define ICRBP_A_ERR_MASK&t;0x3ff
macro_line|#ifdef _LANGUAGE_C
DECL|union|hubii_idsr
r_typedef
r_union
id|hubii_idsr
(brace
DECL|member|iin_reg
id|u64
id|iin_reg
suffix:semicolon
r_struct
(brace
DECL|member|rsvd1
id|u64
id|rsvd1
suffix:colon
l_int|35
comma
DECL|member|isent
id|isent
suffix:colon
l_int|1
comma
DECL|member|rsvd2
id|rsvd2
suffix:colon
l_int|3
comma
DECL|member|ienable
id|ienable
suffix:colon
l_int|1
comma
DECL|member|rsvd
id|rsvd
suffix:colon
l_int|7
comma
DECL|member|node
id|node
suffix:colon
l_int|9
comma
DECL|member|rsvd4
id|rsvd4
suffix:colon
l_int|1
comma
DECL|member|level
id|level
suffix:colon
l_int|7
suffix:semicolon
DECL|member|iin_fmt
)brace
id|iin_fmt
suffix:semicolon
DECL|typedef|hubii_idsr_t
)brace
id|hubii_idsr_t
suffix:semicolon
macro_line|#endif /* LANGUAGE_C */
multiline_comment|/* &n; * IO BTE Length/Status (IIO_IBLS) register bit field definitions&n; */
DECL|macro|IBLS_BUSY
mdefine_line|#define IBLS_BUSY&t;&t;(0x1 &lt;&lt; 20)
DECL|macro|IBLS_ERROR_SHFT
mdefine_line|#define IBLS_ERROR_SHFT&t;&t;16
DECL|macro|IBLS_ERROR
mdefine_line|#define IBLS_ERROR&t;&t;(0x1 &lt;&lt; IBLS_ERROR_SHFT)
DECL|macro|IBLS_LENGTH_MASK
mdefine_line|#define IBLS_LENGTH_MASK&t;0xffff
multiline_comment|/*&n; * IO BTE Control/Terminate register (IBCT) register bit field definitions&n; */
DECL|macro|IBCT_POISON
mdefine_line|#define IBCT_POISON&t;&t;(0x1 &lt;&lt; 8)
DECL|macro|IBCT_NOTIFY
mdefine_line|#define IBCT_NOTIFY&t;&t;(0x1 &lt;&lt; 4)
DECL|macro|IBCT_ZFIL_MODE
mdefine_line|#define IBCT_ZFIL_MODE&t;&t;(0x1 &lt;&lt; 0)
multiline_comment|/*&n; * IO BTE Interrupt Address Register (IBIA) register bit field definitions&n; */
DECL|macro|IBIA_LEVEL_SHFT
mdefine_line|#define IBIA_LEVEL_SHFT&t;&t;16
DECL|macro|IBIA_LEVEL_MASK
mdefine_line|#define IBIA_LEVEL_MASK&t;&t;(0x7f &lt;&lt; IBIA_LEVEL_SHFT)
DECL|macro|IBIA_NODE_ID_SHFT
mdefine_line|#define IBIA_NODE_ID_SHFT&t;0
DECL|macro|IBIA_NODE_ID_MASK
mdefine_line|#define IBIA_NODE_ID_MASK&t;(0x1ff)
multiline_comment|/*&n; * Miscellaneous hub constants&n; */
multiline_comment|/* Number of widgets supported by hub */
DECL|macro|HUB_NUM_WIDGET
mdefine_line|#define HUB_NUM_WIDGET&t;&t;9
DECL|macro|HUB_WIDGET_ID_MIN
mdefine_line|#define HUB_WIDGET_ID_MIN&t;0x8
DECL|macro|HUB_WIDGET_ID_MAX
mdefine_line|#define HUB_WIDGET_ID_MAX&t;0xf
DECL|macro|HUB_WIDGET_PART_NUM
mdefine_line|#define HUB_WIDGET_PART_NUM&t;0xc101&t;
DECL|macro|MAX_HUBS_PER_XBOW
mdefine_line|#define MAX_HUBS_PER_XBOW&t;2
multiline_comment|/* &n; * Get a hub&squot;s widget id from widget control register &n; */
DECL|macro|IIO_WCR_WID_GET
mdefine_line|#define IIO_WCR_WID_GET(nasid)&t;(REMOTE_HUB_L(nasid, III_WCR) &amp; 0xf) 
DECL|macro|IIO_WST_ERROR_MASK
mdefine_line|#define IIO_WST_ERROR_MASK&t;(UINT64_CAST 1 &lt;&lt; 32) /* Widget status error */
multiline_comment|/*&n; * Number of credits Hub widget has while sending req/response to&n; * xbow. &n; * Value of 3 is required by Xbow 1.1&n; * We may be able to increase this to 4 with Xbow 1.2.&n; */
DECL|macro|HUBII_XBOW_CREDIT
mdefine_line|#define       HUBII_XBOW_CREDIT       3
DECL|macro|HUBII_XBOW_REV2_CREDIT
mdefine_line|#define&t;      HUBII_XBOW_REV2_CREDIT  4
macro_line|#endif /* _ASM_SGI_SN_SN0_HUBIO_H */
eof
