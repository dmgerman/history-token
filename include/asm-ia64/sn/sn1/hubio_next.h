multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_SN1_HUBIO_NEXT_H
DECL|macro|_ASM_SN_SN1_HUBIO_NEXT_H
mdefine_line|#define _ASM_SN_SN1_HUBIO_NEXT_H
multiline_comment|/*&n; * Slightly friendlier names for some common registers.&n; */
DECL|macro|IIO_WIDGET
mdefine_line|#define IIO_WIDGET              IIO_WID      /* Widget identification */
DECL|macro|IIO_WIDGET_STAT
mdefine_line|#define IIO_WIDGET_STAT         IIO_WSTAT    /* Widget status register */
DECL|macro|IIO_WIDGET_CTRL
mdefine_line|#define IIO_WIDGET_CTRL         IIO_WCR      /* Widget control register */
DECL|macro|IIO_PROTECT
mdefine_line|#define IIO_PROTECT             IIO_ILAPR    /* IO interface protection */
DECL|macro|IIO_PROTECT_OVRRD
mdefine_line|#define IIO_PROTECT_OVRRD       IIO_ILAPO    /* IO protect override */
DECL|macro|IIO_OUTWIDGET_ACCESS
mdefine_line|#define IIO_OUTWIDGET_ACCESS    IIO_IOWA     /* Outbound widget access */
DECL|macro|IIO_INWIDGET_ACCESS
mdefine_line|#define IIO_INWIDGET_ACCESS     IIO_IIWA     /* Inbound widget access */
DECL|macro|IIO_INDEV_ERR_MASK
mdefine_line|#define IIO_INDEV_ERR_MASK      IIO_IIDEM    /* Inbound device error mask */
DECL|macro|IIO_LLP_CSR
mdefine_line|#define IIO_LLP_CSR             IIO_ILCSR    /* LLP control and status */
DECL|macro|IIO_LLP_LOG
mdefine_line|#define IIO_LLP_LOG             IIO_ILLR     /* LLP log */
DECL|macro|IIO_XTALKCC_TOUT
mdefine_line|#define IIO_XTALKCC_TOUT        IIO_IXCC     /* Xtalk credit count timeout*/
DECL|macro|IIO_XTALKTT_TOUT
mdefine_line|#define IIO_XTALKTT_TOUT        IIO_IXTT     /* Xtalk tail timeout */
DECL|macro|IIO_IO_ERR_CLR
mdefine_line|#define IIO_IO_ERR_CLR          IIO_IECLR    /* IO error clear */
DECL|macro|IIO_IGFX_0
mdefine_line|#define IIO_IGFX_0 &t;&t;IIO_IGFX0
DECL|macro|IIO_IGFX_1
mdefine_line|#define IIO_IGFX_1 &t;&t;IIO_IGFX1
DECL|macro|IIO_IBCT_0
mdefine_line|#define IIO_IBCT_0&t;&t;IIO_IBCT0
DECL|macro|IIO_IBCT_1
mdefine_line|#define IIO_IBCT_1&t;&t;IIO_IBCT1
DECL|macro|IIO_IBLS_0
mdefine_line|#define IIO_IBLS_0&t;&t;IIO_IBLS0
DECL|macro|IIO_IBLS_1
mdefine_line|#define IIO_IBLS_1&t;&t;IIO_IBLS1
DECL|macro|IIO_IBSA_0
mdefine_line|#define IIO_IBSA_0&t;&t;IIO_IBSA0
DECL|macro|IIO_IBSA_1
mdefine_line|#define IIO_IBSA_1&t;&t;IIO_IBSA1
DECL|macro|IIO_IBDA_0
mdefine_line|#define IIO_IBDA_0&t;&t;IIO_IBDA0
DECL|macro|IIO_IBDA_1
mdefine_line|#define IIO_IBDA_1&t;&t;IIO_IBDA1
DECL|macro|IIO_IBNA_0
mdefine_line|#define IIO_IBNA_0&t;&t;IIO_IBNA0
DECL|macro|IIO_IBNA_1
mdefine_line|#define IIO_IBNA_1&t;&t;IIO_IBNA1
DECL|macro|IIO_IBIA_0
mdefine_line|#define IIO_IBIA_0&t;&t;IIO_IBIA0
DECL|macro|IIO_IBIA_1
mdefine_line|#define IIO_IBIA_1&t;&t;IIO_IBIA1
DECL|macro|IIO_IOPRB_0
mdefine_line|#define IIO_IOPRB_0&t;&t;IIO_IPRB0
DECL|macro|IIO_PRTE_0
mdefine_line|#define IIO_PRTE_0      &t;IIO_IPRTE0        /* PIO Read address table entry 0 */
DECL|macro|IIO_PRTE
mdefine_line|#define IIO_PRTE(_x)    &t;(IIO_PRTE_0 + (8 * (_x)))
DECL|macro|IIO_NUM_IPRBS
mdefine_line|#define IIO_NUM_IPRBS &t;&t;(9) 
DECL|macro|IIO_WIDPRTE
mdefine_line|#define IIO_WIDPRTE(x)  IIO_PRTE(((x) - 8)) /* widget ID to its PRTE num */
DECL|macro|IIO_LLP_CSR_IS_UP
mdefine_line|#define IIO_LLP_CSR_IS_UP               0x00002000
DECL|macro|IIO_LLP_CSR_LLP_STAT_MASK
mdefine_line|#define IIO_LLP_CSR_LLP_STAT_MASK       0x00003000
DECL|macro|IIO_LLP_CSR_LLP_STAT_SHFT
mdefine_line|#define IIO_LLP_CSR_LLP_STAT_SHFT       12
DECL|macro|IIO_LLP_CB_MAX
mdefine_line|#define IIO_LLP_CB_MAX  0xffff&t;/* in ILLR CB_CNT, Max Check Bit errors */
DECL|macro|IIO_LLP_SN_MAX
mdefine_line|#define IIO_LLP_SN_MAX  0xffff&t;/* in ILLR SN_CNT, Max Sequence Number errors */
multiline_comment|/* key to IIO_PROTECT_OVRRD */
DECL|macro|IIO_PROTECT_OVRRD_KEY
mdefine_line|#define IIO_PROTECT_OVRRD_KEY   0x53474972756c6573ull   /* &quot;SGIrules&quot; */
multiline_comment|/* BTE register names */
DECL|macro|IIO_BTE_STAT_0
mdefine_line|#define IIO_BTE_STAT_0          IIO_IBLS_0   /* Also BTE length/status 0 */
DECL|macro|IIO_BTE_SRC_0
mdefine_line|#define IIO_BTE_SRC_0           IIO_IBSA_0   /* Also BTE source address  0 */
DECL|macro|IIO_BTE_DEST_0
mdefine_line|#define IIO_BTE_DEST_0          IIO_IBDA_0   /* Also BTE dest. address 0 */
DECL|macro|IIO_BTE_CTRL_0
mdefine_line|#define IIO_BTE_CTRL_0          IIO_IBCT_0   /* Also BTE control/terminate 0 */
DECL|macro|IIO_BTE_NOTIFY_0
mdefine_line|#define IIO_BTE_NOTIFY_0        IIO_IBNA_0   /* Also BTE notification 0 */
DECL|macro|IIO_BTE_INT_0
mdefine_line|#define IIO_BTE_INT_0           IIO_IBIA_0   /* Also BTE interrupt 0 */
DECL|macro|IIO_BTE_OFF_0
mdefine_line|#define IIO_BTE_OFF_0           0            /* Base offset from BTE 0 regs. */
DECL|macro|IIO_BTE_OFF_1
mdefine_line|#define IIO_BTE_OFF_1   IIO_IBLS_1 - IIO_IBLS_0 /* Offset from base to BTE 1 */
multiline_comment|/* BTE register offsets from base */
DECL|macro|BTEOFF_STAT
mdefine_line|#define BTEOFF_STAT             0
DECL|macro|BTEOFF_SRC
mdefine_line|#define BTEOFF_SRC              (IIO_BTE_SRC_0 - IIO_BTE_STAT_0)
DECL|macro|BTEOFF_DEST
mdefine_line|#define BTEOFF_DEST             (IIO_BTE_DEST_0 - IIO_BTE_STAT_0)
DECL|macro|BTEOFF_CTRL
mdefine_line|#define BTEOFF_CTRL             (IIO_BTE_CTRL_0 - IIO_BTE_STAT_0)
DECL|macro|BTEOFF_NOTIFY
mdefine_line|#define BTEOFF_NOTIFY           (IIO_BTE_NOTIFY_0 - IIO_BTE_STAT_0)
DECL|macro|BTEOFF_INT
mdefine_line|#define BTEOFF_INT              (IIO_BTE_INT_0 - IIO_BTE_STAT_0)
multiline_comment|/* names used in hub_diags.c; carried over from SN0 */
DECL|macro|IIO_BASE_BTE0
mdefine_line|#define IIO_BASE_BTE0   IIO_IBLS_0&t;&t;
DECL|macro|IIO_BASE_BTE1
mdefine_line|#define IIO_BASE_BTE1   IIO_IBLS_1&t;&t;
macro_line|#if 0
mdefine_line|#define IIO_BASE        IIO_WID
mdefine_line|#define IIO_BASE_PERF   IIO_IPCR   /* IO Performance Control */
mdefine_line|#define IIO_PERF_CNT    IIO_IPPR   /* IO Performance Profiling */
macro_line|#endif
multiline_comment|/* GFX Flow Control Node/Widget Register */
DECL|macro|IIO_IGFX_W_NUM_BITS
mdefine_line|#define IIO_IGFX_W_NUM_BITS&t;4&t;/* size of widget num field */
DECL|macro|IIO_IGFX_W_NUM_MASK
mdefine_line|#define IIO_IGFX_W_NUM_MASK&t;((1&lt;&lt;IIO_IGFX_W_NUM_BITS)-1)
DECL|macro|IIO_IGFX_W_NUM_SHIFT
mdefine_line|#define IIO_IGFX_W_NUM_SHIFT&t;0
DECL|macro|IIO_IGFX_PI_NUM_BITS
mdefine_line|#define IIO_IGFX_PI_NUM_BITS&t;1&t;/* size of PI num field */
DECL|macro|IIO_IGFX_PI_NUM_MASK
mdefine_line|#define IIO_IGFX_PI_NUM_MASK&t;((1&lt;&lt;IIO_IGFX_PI_NUM_BITS)-1)
DECL|macro|IIO_IGFX_PI_NUM_SHIFT
mdefine_line|#define IIO_IGFX_PI_NUM_SHIFT&t;4
DECL|macro|IIO_IGFX_N_NUM_BITS
mdefine_line|#define IIO_IGFX_N_NUM_BITS&t;8&t;/* size of node num field */
DECL|macro|IIO_IGFX_N_NUM_MASK
mdefine_line|#define IIO_IGFX_N_NUM_MASK&t;((1&lt;&lt;IIO_IGFX_N_NUM_BITS)-1)
DECL|macro|IIO_IGFX_N_NUM_SHIFT
mdefine_line|#define IIO_IGFX_N_NUM_SHIFT&t;5
DECL|macro|IIO_IGFX_P_NUM_BITS
mdefine_line|#define IIO_IGFX_P_NUM_BITS&t;1&t;/* size of processor num field */
DECL|macro|IIO_IGFX_P_NUM_MASK
mdefine_line|#define IIO_IGFX_P_NUM_MASK&t;((1&lt;&lt;IIO_IGFX_P_NUM_BITS)-1)
DECL|macro|IIO_IGFX_P_NUM_SHIFT
mdefine_line|#define IIO_IGFX_P_NUM_SHIFT&t;16
DECL|macro|IIO_IGFX_INIT
mdefine_line|#define IIO_IGFX_INIT(widget, pi, node, cpu)&t;&t;&t;&t;(&bslash;&n;&t;(((widget) &amp; IIO_IGFX_W_NUM_MASK) &lt;&lt; IIO_IGFX_W_NUM_SHIFT) |&t; &bslash;&n;&t;(((pi)     &amp; IIO_IGFX_PI_NUM_MASK)&lt;&lt; IIO_IGFX_PI_NUM_SHIFT)|&t; &bslash;&n;&t;(((node)   &amp; IIO_IGFX_N_NUM_MASK) &lt;&lt; IIO_IGFX_N_NUM_SHIFT) |&t; &bslash;&n;&t;(((cpu)    &amp; IIO_IGFX_P_NUM_MASK) &lt;&lt; IIO_IGFX_P_NUM_SHIFT))
multiline_comment|/* Scratch registers (all bits available) */
DECL|macro|IIO_SCRATCH_REG0
mdefine_line|#define IIO_SCRATCH_REG0        IIO_ISCR0
DECL|macro|IIO_SCRATCH_REG1
mdefine_line|#define IIO_SCRATCH_REG1        IIO_ISCR1
DECL|macro|IIO_SCRATCH_MASK
mdefine_line|#define IIO_SCRATCH_MASK        0xffffffffffffffff
DECL|macro|IIO_SCRATCH_BIT0_0
mdefine_line|#define IIO_SCRATCH_BIT0_0      0x0000000000000001
DECL|macro|IIO_SCRATCH_BIT0_1
mdefine_line|#define IIO_SCRATCH_BIT0_1      0x0000000000000002
DECL|macro|IIO_SCRATCH_BIT0_2
mdefine_line|#define IIO_SCRATCH_BIT0_2      0x0000000000000004
DECL|macro|IIO_SCRATCH_BIT0_3
mdefine_line|#define IIO_SCRATCH_BIT0_3      0x0000000000000008
DECL|macro|IIO_SCRATCH_BIT0_4
mdefine_line|#define IIO_SCRATCH_BIT0_4      0x0000000000000010
DECL|macro|IIO_SCRATCH_BIT0_5
mdefine_line|#define IIO_SCRATCH_BIT0_5      0x0000000000000020
DECL|macro|IIO_SCRATCH_BIT0_6
mdefine_line|#define IIO_SCRATCH_BIT0_6      0x0000000000000040
DECL|macro|IIO_SCRATCH_BIT0_7
mdefine_line|#define IIO_SCRATCH_BIT0_7      0x0000000000000080
DECL|macro|IIO_SCRATCH_BIT0_8
mdefine_line|#define IIO_SCRATCH_BIT0_8      0x0000000000000100
DECL|macro|IIO_SCRATCH_BIT0_9
mdefine_line|#define IIO_SCRATCH_BIT0_9      0x0000000000000200
DECL|macro|IIO_SCRATCH_BIT0_A
mdefine_line|#define IIO_SCRATCH_BIT0_A      0x0000000000000400
DECL|macro|IIO_SCRATCH_BIT1_0
mdefine_line|#define IIO_SCRATCH_BIT1_0      0x0000000000000001
DECL|macro|IIO_SCRATCH_BIT1_1
mdefine_line|#define IIO_SCRATCH_BIT1_1      0x0000000000000002
multiline_comment|/* IO Translation Table Entries */
DECL|macro|IIO_NUM_ITTES
mdefine_line|#define IIO_NUM_ITTES   7               /* ITTEs numbered 0..6 */
multiline_comment|/* Hw manuals number them 1..7! */
multiline_comment|/*&n; * IIO_IMEM Register fields.&n; */
DECL|macro|IIO_IMEM_W0ESD
mdefine_line|#define IIO_IMEM_W0ESD  0x1             /* Widget 0 shut down due to error */
DECL|macro|IIO_IMEM_B0ESD
mdefine_line|#define IIO_IMEM_B0ESD  (1 &lt;&lt; 4)        /* BTE 0 shut down due to error */
DECL|macro|IIO_IMEM_B1ESD
mdefine_line|#define IIO_IMEM_B1ESD  (1 &lt;&lt; 8)        /* BTE 1 Shut down due to error */
multiline_comment|/*&n; * As a permanent workaround for a bug in the PI side of the hub, we&squot;ve&n; * redefined big window 7 as small window 0.&n; XXX does this still apply for SN1??&n; */
DECL|macro|HUB_NUM_BIG_WINDOW
mdefine_line|#define HUB_NUM_BIG_WINDOW      IIO_NUM_ITTES - 1
multiline_comment|/*&n; * Use the top big window as a surrogate for the first small window&n; */
DECL|macro|SWIN0_BIGWIN
mdefine_line|#define SWIN0_BIGWIN            HUB_NUM_BIG_WINDOW
DECL|macro|IIO_NUM_PRTES
mdefine_line|#define IIO_NUM_PRTES   8               /* Total number of PRB table entries */
DECL|macro|ILCSR_WARM_RESET
mdefine_line|#define ILCSR_WARM_RESET        0x100
multiline_comment|/*&n; * CRB manipulation macros&n; *      The CRB macros are slightly complicated, since there are up to&n; *      four registers associated with each CRB entry.&n; */
DECL|macro|IIO_NUM_CRBS
mdefine_line|#define IIO_NUM_CRBS            15      /* Number of CRBs */
DECL|macro|IIO_NUM_NORMAL_CRBS
mdefine_line|#define IIO_NUM_NORMAL_CRBS     12      /* Number of regular CRB entries */
DECL|macro|IIO_NUM_PC_CRBS
mdefine_line|#define IIO_NUM_PC_CRBS         4       /* Number of partial cache CRBs */
DECL|macro|IIO_ICRB_OFFSET
mdefine_line|#define IIO_ICRB_OFFSET         8
DECL|macro|IIO_ICRB_0
mdefine_line|#define IIO_ICRB_0              IIO_ICRB0_A
DECL|macro|IIO_ICRB_ADDR_SHFT
mdefine_line|#define IIO_ICRB_ADDR_SHFT&t;2&t;/* Shift to get proper address */
multiline_comment|/* XXX - This is now tuneable:&n;        #define IIO_FIRST_PC_ENTRY 12&n; */
DECL|macro|IIO_ICRB_A
mdefine_line|#define IIO_ICRB_A(_x)  (IIO_ICRB_0 + (4 * IIO_ICRB_OFFSET * (_x)))
DECL|macro|IIO_ICRB_B
mdefine_line|#define IIO_ICRB_B(_x)  (IIO_ICRB_A(_x) + 1*IIO_ICRB_OFFSET)
DECL|macro|IIO_ICRB_C
mdefine_line|#define IIO_ICRB_C(_x)  (IIO_ICRB_A(_x) + 2*IIO_ICRB_OFFSET)
DECL|macro|IIO_ICRB_D
mdefine_line|#define IIO_ICRB_D(_x)  (IIO_ICRB_A(_x) + 3*IIO_ICRB_OFFSET)
DECL|macro|TNUM_TO_WIDGET_DEV
mdefine_line|#define TNUM_TO_WIDGET_DEV(_tnum)&t;(_tnum &amp; 0x7)
multiline_comment|/*&n; * values for &quot;ecode&quot; field&n; */
DECL|macro|IIO_ICRB_ECODE_DERR
mdefine_line|#define IIO_ICRB_ECODE_DERR     0       /* Directory error due to IIO access */
DECL|macro|IIO_ICRB_ECODE_PERR
mdefine_line|#define IIO_ICRB_ECODE_PERR     1       /* Poison error on IO access */
DECL|macro|IIO_ICRB_ECODE_WERR
mdefine_line|#define IIO_ICRB_ECODE_WERR     2       /* Write error by IIO access&n;                                         * e.g. WINV to a Read only line. */
DECL|macro|IIO_ICRB_ECODE_AERR
mdefine_line|#define IIO_ICRB_ECODE_AERR     3       /* Access error caused by IIO access */
DECL|macro|IIO_ICRB_ECODE_PWERR
mdefine_line|#define IIO_ICRB_ECODE_PWERR    4       /* Error on partial write       */
DECL|macro|IIO_ICRB_ECODE_PRERR
mdefine_line|#define IIO_ICRB_ECODE_PRERR    5       /* Error on partial read        */
DECL|macro|IIO_ICRB_ECODE_TOUT
mdefine_line|#define IIO_ICRB_ECODE_TOUT     6       /* CRB timeout before deallocating */
DECL|macro|IIO_ICRB_ECODE_XTERR
mdefine_line|#define IIO_ICRB_ECODE_XTERR    7       /* Incoming xtalk pkt had error bit */
multiline_comment|/*&n; * Number of credits Hub widget has while sending req/response to&n; * xbow.&n; * Value of 3 is required by Xbow 1.1&n; * We may be able to increase this to 4 with Xbow 1.2.&n; */
DECL|macro|HUBII_XBOW_CREDIT
mdefine_line|#define       HUBII_XBOW_CREDIT       3
DECL|macro|HUBII_XBOW_REV2_CREDIT
mdefine_line|#define       HUBII_XBOW_REV2_CREDIT  4
multiline_comment|/*&n; * Number of credits that xtalk devices should use when communicating&n; * with a Bedrock (depth of Bedrock&squot;s queue).&n; */
DECL|macro|HUB_CREDIT
mdefine_line|#define HUB_CREDIT 4
multiline_comment|/*&n; * Some IIO_PRB fields&n; */
DECL|macro|IIO_PRB_MULTI_ERR
mdefine_line|#define IIO_PRB_MULTI_ERR&t;(1LL &lt;&lt; 63)
DECL|macro|IIO_PRB_SPUR_RD
mdefine_line|#define IIO_PRB_SPUR_RD&t;&t;(1LL &lt;&lt; 51)
DECL|macro|IIO_PRB_SPUR_WR
mdefine_line|#define IIO_PRB_SPUR_WR&t;&t;(1LL &lt;&lt; 50)
DECL|macro|IIO_PRB_RD_TO
mdefine_line|#define IIO_PRB_RD_TO&t;&t;(1LL &lt;&lt; 49)
DECL|macro|IIO_PRB_ERROR
mdefine_line|#define IIO_PRB_ERROR&t;&t;(1LL &lt;&lt; 48)
multiline_comment|/*************************************************************************&n;&n; Some of the IIO field masks and shifts are defined here.&n; This is in order to maintain compatibility in SN0 and SN1 code&n; &n;**************************************************************************/
multiline_comment|/*&n; * ICMR register fields&n; * (Note: the IIO_ICMR_P_CNT and IIO_ICMR_PC_VLD from Hub are not&n; * present in Bedrock)&n; */
DECL|macro|IIO_ICMR_CRB_VLD_SHFT
mdefine_line|#define IIO_ICMR_CRB_VLD_SHFT   20
DECL|macro|IIO_ICMR_CRB_VLD_MASK
mdefine_line|#define IIO_ICMR_CRB_VLD_MASK   (0x7fffUL &lt;&lt; IIO_ICMR_CRB_VLD_SHFT)
DECL|macro|IIO_ICMR_FC_CNT_SHFT
mdefine_line|#define IIO_ICMR_FC_CNT_SHFT    16
DECL|macro|IIO_ICMR_FC_CNT_MASK
mdefine_line|#define IIO_ICMR_FC_CNT_MASK    (0xf &lt;&lt; IIO_ICMR_FC_CNT_SHFT)
DECL|macro|IIO_ICMR_C_CNT_SHFT
mdefine_line|#define IIO_ICMR_C_CNT_SHFT     4
DECL|macro|IIO_ICMR_C_CNT_MASK
mdefine_line|#define IIO_ICMR_C_CNT_MASK     (0xf &lt;&lt; IIO_ICMR_C_CNT_SHFT)
DECL|macro|IIO_ICMR_PRECISE
mdefine_line|#define IIO_ICMR_PRECISE        (1UL &lt;&lt; 52)
DECL|macro|IIO_ICMR_CLR_RPPD
mdefine_line|#define IIO_ICMR_CLR_RPPD       (1UL &lt;&lt; 13)
DECL|macro|IIO_ICMR_CLR_RQPD
mdefine_line|#define IIO_ICMR_CLR_RQPD       (1UL &lt;&lt; 12)
multiline_comment|/*&n; * IIO PIO Deallocation register field masks : (IIO_IPDR)&n; XXX present but not needed in bedrock?  See the manual.&n; */
DECL|macro|IIO_IPDR_PND
mdefine_line|#define IIO_IPDR_PND    (1 &lt;&lt; 4)
multiline_comment|/*&n; * IIO CRB deallocation register field masks: (IIO_ICDR)&n; */
DECL|macro|IIO_ICDR_PND
mdefine_line|#define IIO_ICDR_PND    (1 &lt;&lt; 4)
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
multiline_comment|/*&n; * IIO Incoming Error Packet Header (IIO_IIEPH1/IIO_IIEPH2)&n; */
DECL|macro|IIEPH1_VALID
mdefine_line|#define IIEPH1_VALID&t;&t;(1 &lt;&lt; 44)
DECL|macro|IIEPH1_OVERRUN
mdefine_line|#define IIEPH1_OVERRUN&t;&t;(1 &lt;&lt; 40)
DECL|macro|IIEPH1_ERR_TYPE_SHFT
mdefine_line|#define IIEPH1_ERR_TYPE_SHFT&t;32
DECL|macro|IIEPH1_ERR_TYPE_MASK
mdefine_line|#define IIEPH1_ERR_TYPE_MASK&t;0xf
DECL|macro|IIEPH1_SOURCE_SHFT
mdefine_line|#define IIEPH1_SOURCE_SHFT&t;20
DECL|macro|IIEPH1_SOURCE_MASK
mdefine_line|#define IIEPH1_SOURCE_MASK&t;11
DECL|macro|IIEPH1_SUPPL_SHFT
mdefine_line|#define IIEPH1_SUPPL_SHFT&t;8
DECL|macro|IIEPH1_SUPPL_MASK
mdefine_line|#define IIEPH1_SUPPL_MASK&t;11
DECL|macro|IIEPH1_CMD_SHFT
mdefine_line|#define IIEPH1_CMD_SHFT&t;&t;0
DECL|macro|IIEPH1_CMD_MASK
mdefine_line|#define IIEPH1_CMD_MASK&t;&t;7
DECL|macro|IIEPH2_TAIL
mdefine_line|#define IIEPH2_TAIL&t;&t;(1 &lt;&lt; 40)
DECL|macro|IIEPH2_ADDRESS_SHFT
mdefine_line|#define IIEPH2_ADDRESS_SHFT&t;0
DECL|macro|IIEPH2_ADDRESS_MASK
mdefine_line|#define IIEPH2_ADDRESS_MASK&t;38
DECL|macro|IIEPH1_ERR_SHORT_REQ
mdefine_line|#define IIEPH1_ERR_SHORT_REQ&t;2
DECL|macro|IIEPH1_ERR_SHORT_REPLY
mdefine_line|#define IIEPH1_ERR_SHORT_REPLY&t;3
DECL|macro|IIEPH1_ERR_LONG_REQ
mdefine_line|#define IIEPH1_ERR_LONG_REQ&t;4
DECL|macro|IIEPH1_ERR_LONG_REPLY
mdefine_line|#define IIEPH1_ERR_LONG_REPLY&t;5
multiline_comment|/*&n; * IO Error Clear register bit field definitions&n; */
DECL|macro|IECLR_PI1_FWD_INT
mdefine_line|#define IECLR_PI1_FWD_INT&t;(1 &lt;&lt; 31)  /* clear PI1_FORWARD_INT in iidsr */
DECL|macro|IECLR_PI0_FWD_INT
mdefine_line|#define IECLR_PI0_FWD_INT&t;(1 &lt;&lt; 30)  /* clear PI0_FORWARD_INT in iidsr */
DECL|macro|IECLR_SPUR_RD_HDR
mdefine_line|#define IECLR_SPUR_RD_HDR&t;(1 &lt;&lt; 29)  /* clear valid bit in ixss reg */
DECL|macro|IECLR_BTE1
mdefine_line|#define IECLR_BTE1&t;&t;(1 &lt;&lt; 18)  /* clear bte error 1 */
DECL|macro|IECLR_BTE0
mdefine_line|#define IECLR_BTE0&t;&t;(1 &lt;&lt; 17)  /* clear bte error 0 */
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
multiline_comment|/*&n; *&n; * CRB Register description.&n; *&n; * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING&n; * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING&n; * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING&n; * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING&n; * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING&n; *&n; * Many of the fields in CRB are status bits used by hardware&n; * for implementation of the protocol. It&squot;s very dangerous to&n; * mess around with the CRB registers.&n; *&n; * It&squot;s OK to read the CRB registers and try to make sense out of the&n; * fields in CRB.&n; *&n; * Updating CRB requires all activities in Hub IIO to be quiesced.&n; * otherwise, a write to CRB could corrupt other CRB entries.&n; * CRBs are here only as a back door peek to hub IIO&squot;s status.&n; * Quiescing implies  no dmas no PIOs&n; * either directly from the cpu or from sn0net.&n; * this is not something that can be done easily. So, AVOID updating&n; * CRBs.&n; */
macro_line|#ifdef _LANGUAGE_C
multiline_comment|/*&n; * Easy access macros for CRBs, all 4 registers (A-D)&n; */
DECL|typedef|icrba_t
r_typedef
id|ii_icrb0_a_u_t
id|icrba_t
suffix:semicolon
multiline_comment|/* what it was called on SN0/hub */
DECL|macro|a_error
mdefine_line|#define a_error         ii_icrb0_a_fld_s.ia_error
DECL|macro|a_ecode
mdefine_line|#define a_ecode         ii_icrb0_a_fld_s.ia_errcode
DECL|macro|a_lnetuce
mdefine_line|#define a_lnetuce       ii_icrb0_a_fld_s.ia_ln_uce
DECL|macro|a_mark
mdefine_line|#define a_mark          ii_icrb0_a_fld_s.ia_mark
DECL|macro|a_xerr
mdefine_line|#define a_xerr          ii_icrb0_a_fld_s.ia_xt_err
DECL|macro|a_sidn
mdefine_line|#define a_sidn          ii_icrb0_a_fld_s.ia_sidn
DECL|macro|a_tnum
mdefine_line|#define a_tnum          ii_icrb0_a_fld_s.ia_tnum
DECL|macro|a_addr
mdefine_line|#define a_addr          ii_icrb0_a_fld_s.ia_addr
DECL|macro|a_valid
mdefine_line|#define a_valid         ii_icrb0_a_fld_s.ia_vld
DECL|macro|a_iow
mdefine_line|#define a_iow           ii_icrb0_a_fld_s.ia_iow
DECL|macro|a_regvalue
mdefine_line|#define a_regvalue&t;ii_icrb0_a_regval
DECL|typedef|icrbb_t
r_typedef
id|ii_icrb0_b_u_t
id|icrbb_t
suffix:semicolon
DECL|macro|b_btenum
mdefine_line|#define b_btenum        ii_icrb0_b_fld_s.ib_bte_num
DECL|macro|b_cohtrans
mdefine_line|#define b_cohtrans      ii_icrb0_b_fld_s.ib_ct
DECL|macro|b_xtsize
mdefine_line|#define b_xtsize        ii_icrb0_b_fld_s.ib_size
DECL|macro|b_source
mdefine_line|#define b_source        ii_icrb0_b_fld_s.ib_source
DECL|macro|b_imsgtype
mdefine_line|#define b_imsgtype      ii_icrb0_b_fld_s.ib_imsgtype
DECL|macro|b_imsg
mdefine_line|#define b_imsg          ii_icrb0_b_fld_s.ib_imsg
DECL|macro|b_initiator
mdefine_line|#define b_initiator     ii_icrb0_b_fld_s.ib_init
DECL|macro|b_regvalue
mdefine_line|#define b_regvalue&t;ii_icrb0_b_regval
DECL|typedef|icrbc_t
r_typedef
id|ii_icrb0_c_u_t
id|icrbc_t
suffix:semicolon
DECL|macro|c_pricnt
mdefine_line|#define c_pricnt        ii_icrb0_c_fld_s.ic_pr_cnt
DECL|macro|c_pripsc
mdefine_line|#define c_pripsc        ii_icrb0_c_fld_s.ic_pr_psc
DECL|macro|c_bteop
mdefine_line|#define c_bteop         ii_icrb0_c_fld_s.ic_bte_op
DECL|macro|c_bteaddr
mdefine_line|#define c_bteaddr       ii_icrb0_c_fld_s.ic_pa_be /* ic_pa_be fld has 2 names*/
DECL|macro|c_benable
mdefine_line|#define c_benable       ii_icrb0_c_fld_s.ic_pa_be /* ic_pa_be fld has 2 names*/
DECL|macro|c_suppl
mdefine_line|#define c_suppl         ii_icrb0_c_fld_s.ic_suppl
DECL|macro|c_barrop
mdefine_line|#define c_barrop        ii_icrb0_c_fld_s.ic_bo
DECL|macro|c_doresp
mdefine_line|#define c_doresp        ii_icrb0_c_fld_s.ic_resprqd
DECL|macro|c_gbr
mdefine_line|#define c_gbr           ii_icrb0_c_fld_s.ic_gbr
DECL|macro|c_regvalue
mdefine_line|#define c_regvalue&t;ii_icrb0_c_regval
DECL|typedef|icrbd_t
r_typedef
id|ii_icrb0_d_u_t
id|icrbd_t
suffix:semicolon
DECL|macro|icrbd_ctxtvld
mdefine_line|#define icrbd_ctxtvld   ii_icrb0_d_fld_s.id_cvld
DECL|macro|icrbd_toutvld
mdefine_line|#define icrbd_toutvld   ii_icrb0_d_fld_s.id_tvld
DECL|macro|icrbd_context
mdefine_line|#define icrbd_context   ii_icrb0_d_fld_s.id_context
DECL|macro|d_regvalue
mdefine_line|#define d_regvalue&t;ii_icrb0_d_regval
macro_line|#endif /* LANGUAGE_C */
multiline_comment|/* Number of widgets supported by hub */
DECL|macro|HUB_NUM_WIDGET
mdefine_line|#define HUB_NUM_WIDGET          9
DECL|macro|HUB_WIDGET_ID_MIN
mdefine_line|#define HUB_WIDGET_ID_MIN       0x8
DECL|macro|HUB_WIDGET_ID_MAX
mdefine_line|#define HUB_WIDGET_ID_MAX       0xf
DECL|macro|HUB_WIDGET_PART_NUM
mdefine_line|#define HUB_WIDGET_PART_NUM     0xc110
DECL|macro|MAX_HUBS_PER_XBOW
mdefine_line|#define MAX_HUBS_PER_XBOW       2
macro_line|#ifdef _LANGUAGE_C
multiline_comment|/* A few more #defines for backwards compatibility */
DECL|macro|iprb_t
mdefine_line|#define iprb_t          ii_iprb0_u_t
DECL|macro|iprb_regval
mdefine_line|#define iprb_regval     ii_iprb0_regval
DECL|macro|iprb_mult_err
mdefine_line|#define iprb_mult_err&t;ii_iprb0_fld_s.i_mult_err
DECL|macro|iprb_spur_rd
mdefine_line|#define iprb_spur_rd&t;ii_iprb0_fld_s.i_spur_rd
DECL|macro|iprb_spur_wr
mdefine_line|#define iprb_spur_wr&t;ii_iprb0_fld_s.i_spur_wr
DECL|macro|iprb_rd_to
mdefine_line|#define iprb_rd_to&t;ii_iprb0_fld_s.i_rd_to
DECL|macro|iprb_ovflow
mdefine_line|#define iprb_ovflow     ii_iprb0_fld_s.i_of_cnt
DECL|macro|iprb_error
mdefine_line|#define iprb_error      ii_iprb0_fld_s.i_error
DECL|macro|iprb_ff
mdefine_line|#define iprb_ff         ii_iprb0_fld_s.i_f
DECL|macro|iprb_mode
mdefine_line|#define iprb_mode       ii_iprb0_fld_s.i_m
DECL|macro|iprb_bnakctr
mdefine_line|#define iprb_bnakctr    ii_iprb0_fld_s.i_nb
DECL|macro|iprb_anakctr
mdefine_line|#define iprb_anakctr    ii_iprb0_fld_s.i_na
DECL|macro|iprb_xtalkctr
mdefine_line|#define iprb_xtalkctr   ii_iprb0_fld_s.i_c
macro_line|#endif
DECL|macro|LNK_STAT_WORKING
mdefine_line|#define LNK_STAT_WORKING        0x2
DECL|macro|IIO_WSTAT_ECRAZY
mdefine_line|#define IIO_WSTAT_ECRAZY        (1ULL &lt;&lt; 32)    /* Hub gone crazy */
DECL|macro|IIO_WSTAT_TXRETRY
mdefine_line|#define IIO_WSTAT_TXRETRY       (1ULL &lt;&lt; 9)     /* Hub Tx Retry timeout */
DECL|macro|IIO_WSTAT_TXRETRY_MASK
mdefine_line|#define IIO_WSTAT_TXRETRY_MASK  (0x7F)   /* should be 0xFF?? */
DECL|macro|IIO_WSTAT_TXRETRY_SHFT
mdefine_line|#define IIO_WSTAT_TXRETRY_SHFT  (16)
DECL|macro|IIO_WSTAT_TXRETRY_CNT
mdefine_line|#define IIO_WSTAT_TXRETRY_CNT(w)        (((w) &gt;&gt; IIO_WSTAT_TXRETRY_SHFT) &amp; &bslash;&n;                                          IIO_WSTAT_TXRETRY_MASK)
multiline_comment|/* Number of II perf. counters we can multiplex at once */
DECL|macro|IO_PERF_SETS
mdefine_line|#define IO_PERF_SETS&t;32
macro_line|#if __KERNEL__
macro_line|#if _LANGUAGE_C
multiline_comment|/* XXX moved over from SN/SN0/hubio.h -- each should be checked for SN1 */
macro_line|#include &lt;asm/sn/alenlist.h&gt;
macro_line|#include &lt;asm/sn/dmamap.h&gt;
macro_line|#include &lt;asm/sn/iobus.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xtalk.h&gt;
multiline_comment|/* Bit for the widget in inbound access register */
DECL|macro|IIO_IIWA_WIDGET
mdefine_line|#define IIO_IIWA_WIDGET(_w)     ((uint64_t)(1ULL &lt;&lt; _w))
multiline_comment|/* Bit for the widget in outbound access register */
DECL|macro|IIO_IOWA_WIDGET
mdefine_line|#define IIO_IOWA_WIDGET(_w)     ((uint64_t)(1ULL &lt;&lt; _w))
multiline_comment|/* NOTE: The following define assumes that we are going to get&n; * widget numbers from 8 thru F and the device numbers within&n; * widget from 0 thru 7.&n; */
DECL|macro|IIO_IIDEM_WIDGETDEV_MASK
mdefine_line|#define IIO_IIDEM_WIDGETDEV_MASK(w, d)  ((uint64_t)(1ULL &lt;&lt; (8 * ((w) - 8) + (d))))
multiline_comment|/* IO Interrupt Destination Register */
DECL|macro|IIO_IIDSR_SENT_SHIFT
mdefine_line|#define IIO_IIDSR_SENT_SHIFT    28
DECL|macro|IIO_IIDSR_SENT_MASK
mdefine_line|#define IIO_IIDSR_SENT_MASK     0x10000000
DECL|macro|IIO_IIDSR_ENB_SHIFT
mdefine_line|#define IIO_IIDSR_ENB_SHIFT     24
DECL|macro|IIO_IIDSR_ENB_MASK
mdefine_line|#define IIO_IIDSR_ENB_MASK      0x01000000
DECL|macro|IIO_IIDSR_NODE_SHIFT
mdefine_line|#define IIO_IIDSR_NODE_SHIFT    8
DECL|macro|IIO_IIDSR_NODE_MASK
mdefine_line|#define IIO_IIDSR_NODE_MASK     0x0000ff00
DECL|macro|IIO_IIDSR_PI_ID_SHIFT
mdefine_line|#define IIO_IIDSR_PI_ID_SHIFT   8
DECL|macro|IIO_IIDSR_PI_ID_MASK
mdefine_line|#define IIO_IIDSR_PI_ID_MASK    0x00000010
DECL|macro|IIO_IIDSR_LVL_SHIFT
mdefine_line|#define IIO_IIDSR_LVL_SHIFT     0
DECL|macro|IIO_IIDSR_LVL_MASK
mdefine_line|#define IIO_IIDSR_LVL_MASK      0x0000007f
multiline_comment|/* Xtalk timeout threshhold register (IIO_IXTT) */
DECL|macro|IXTT_RRSP_TO_SHFT
mdefine_line|#define IXTT_RRSP_TO_SHFT&t;55&t;   /* read response timeout */
DECL|macro|IXTT_RRSP_TO_MASK
mdefine_line|#define IXTT_RRSP_TO_MASK&t;(0x1FULL &lt;&lt; IXTT_RRSP_TO_SHFT)
DECL|macro|IXTT_RRSP_PS_SHFT
mdefine_line|#define IXTT_RRSP_PS_SHFT&t;32&t;   /* read responsed TO prescalar */
DECL|macro|IXTT_RRSP_PS_MASK
mdefine_line|#define IXTT_RRSP_PS_MASK&t;(0x7FFFFFULL &lt;&lt; IXTT_RRSP_PS_SHFT)
DECL|macro|IXTT_TAIL_TO_SHFT
mdefine_line|#define IXTT_TAIL_TO_SHFT&t;0&t;   /* tail timeout counter threshold */
DECL|macro|IXTT_TAIL_TO_MASK
mdefine_line|#define IXTT_TAIL_TO_MASK&t;(0x3FFFFFFULL &lt;&lt; IXTT_TAIL_TO_SHFT)
multiline_comment|/*&n; * The IO LLP control status register and widget control register&n; */
macro_line|#ifdef LITTLE_ENDIAN
DECL|union|hubii_wcr_u
r_typedef
r_union
id|hubii_wcr_u
(brace
DECL|member|wcr_reg_value
r_uint64
id|wcr_reg_value
suffix:semicolon
r_struct
(brace
DECL|member|wcr_widget_id
r_uint64
id|wcr_widget_id
suffix:colon
l_int|4
comma
multiline_comment|/* LLP crossbar credit */
DECL|member|wcr_tag_mode
id|wcr_tag_mode
suffix:colon
l_int|1
comma
multiline_comment|/* Tag mode */
DECL|member|wcr_rsvd1
id|wcr_rsvd1
suffix:colon
l_int|8
comma
multiline_comment|/* Reserved */
DECL|member|wcr_xbar_crd
id|wcr_xbar_crd
suffix:colon
l_int|3
comma
multiline_comment|/* LLP crossbar credit */
DECL|member|wcr_f_bad_pkt
id|wcr_f_bad_pkt
suffix:colon
l_int|1
comma
multiline_comment|/* Force bad llp pkt enable */
DECL|member|wcr_dir_con
id|wcr_dir_con
suffix:colon
l_int|1
comma
multiline_comment|/* widget direct connect */
DECL|member|wcr_e_thresh
id|wcr_e_thresh
suffix:colon
l_int|5
comma
multiline_comment|/* elasticity threshold */
DECL|member|wcr_rsvd
id|wcr_rsvd
suffix:colon
l_int|41
suffix:semicolon
multiline_comment|/* unused */
DECL|member|wcr_fields_s
)brace
id|wcr_fields_s
suffix:semicolon
DECL|typedef|hubii_wcr_t
)brace
id|hubii_wcr_t
suffix:semicolon
macro_line|#else
DECL|union|hubii_wcr_u
r_typedef
r_union
id|hubii_wcr_u
(brace
DECL|member|wcr_reg_value
r_uint64
id|wcr_reg_value
suffix:semicolon
r_struct
(brace
DECL|member|wcr_rsvd
r_uint64
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
macro_line|#endif
DECL|macro|iwcr_dir_con
mdefine_line|#define iwcr_dir_con    wcr_fields_s.wcr_dir_con
multiline_comment|/* The structures below are defined to extract and modify the ii&n;performance registers */
multiline_comment|/* io_perf_sel allows the caller to specify what tests will be&n;   performed */
macro_line|#ifdef LITTLE_ENDIAN
DECL|union|io_perf_sel
r_typedef
r_union
id|io_perf_sel
(brace
DECL|member|perf_sel_reg
r_uint64
id|perf_sel_reg
suffix:semicolon
r_struct
(brace
DECL|member|perf_ippr0
r_uint64
id|perf_ippr0
suffix:colon
l_int|4
comma
DECL|member|perf_ippr1
id|perf_ippr1
suffix:colon
l_int|4
comma
DECL|member|perf_icct
id|perf_icct
suffix:colon
l_int|8
comma
DECL|member|perf_rsvd
id|perf_rsvd
suffix:colon
l_int|48
suffix:semicolon
DECL|member|perf_sel_bits
)brace
id|perf_sel_bits
suffix:semicolon
DECL|typedef|io_perf_sel_t
)brace
id|io_perf_sel_t
suffix:semicolon
macro_line|#else
DECL|union|io_perf_sel
r_typedef
r_union
id|io_perf_sel
(brace
DECL|member|perf_sel_reg
r_uint64
id|perf_sel_reg
suffix:semicolon
r_struct
(brace
DECL|member|perf_rsvd
r_uint64
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
macro_line|#endif
multiline_comment|/* io_perf_cnt is to extract the count from the hub registers. Due to&n;   hardware problems there is only one counter, not two. */
macro_line|#ifdef LITTLE_ENDIAN
DECL|union|io_perf_cnt
r_typedef
r_union
id|io_perf_cnt
(brace
DECL|member|perf_cnt
r_uint64
id|perf_cnt
suffix:semicolon
r_struct
(brace
DECL|member|perf_cnt
r_uint64
id|perf_cnt
suffix:colon
l_int|20
comma
DECL|member|perf_rsvd2
id|perf_rsvd2
suffix:colon
l_int|12
comma
DECL|member|perf_rsvd1
id|perf_rsvd1
suffix:colon
l_int|32
suffix:semicolon
DECL|member|perf_cnt_bits
)brace
id|perf_cnt_bits
suffix:semicolon
DECL|typedef|io_perf_cnt_t
)brace
id|io_perf_cnt_t
suffix:semicolon
macro_line|#else
DECL|union|io_perf_cnt
r_typedef
r_union
id|io_perf_cnt
(brace
DECL|member|perf_cnt
r_uint64
id|perf_cnt
suffix:semicolon
r_struct
(brace
DECL|member|perf_rsvd1
r_uint64
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
macro_line|#ifdef LITTLE_ENDIAN
DECL|union|iprte_a
r_typedef
r_union
id|iprte_a
(brace
DECL|member|entry
id|bdrkreg_t
id|entry
suffix:semicolon
r_struct
(brace
DECL|member|i_rsvd_1
id|bdrkreg_t
id|i_rsvd_1
suffix:colon
l_int|3
suffix:semicolon
DECL|member|i_addr
id|bdrkreg_t
id|i_addr
suffix:colon
l_int|38
suffix:semicolon
DECL|member|i_init
id|bdrkreg_t
id|i_init
suffix:colon
l_int|3
suffix:semicolon
DECL|member|i_source
id|bdrkreg_t
id|i_source
suffix:colon
l_int|8
suffix:semicolon
DECL|member|i_rsvd
id|bdrkreg_t
id|i_rsvd
suffix:colon
l_int|2
suffix:semicolon
DECL|member|i_widget
id|bdrkreg_t
id|i_widget
suffix:colon
l_int|4
suffix:semicolon
DECL|member|i_to_cnt
id|bdrkreg_t
id|i_to_cnt
suffix:colon
l_int|5
suffix:semicolon
DECL|member|i_vld
id|bdrkreg_t
id|i_vld
suffix:colon
l_int|1
suffix:semicolon
DECL|member|iprte_fields
)brace
id|iprte_fields
suffix:semicolon
DECL|typedef|iprte_a_t
)brace
id|iprte_a_t
suffix:semicolon
macro_line|#else
DECL|union|iprte_a
r_typedef
r_union
id|iprte_a
(brace
DECL|member|entry
id|bdrkreg_t
id|entry
suffix:semicolon
r_struct
(brace
DECL|member|i_vld
id|bdrkreg_t
id|i_vld
suffix:colon
l_int|1
suffix:semicolon
DECL|member|i_to_cnt
id|bdrkreg_t
id|i_to_cnt
suffix:colon
l_int|5
suffix:semicolon
DECL|member|i_widget
id|bdrkreg_t
id|i_widget
suffix:colon
l_int|4
suffix:semicolon
DECL|member|i_rsvd
id|bdrkreg_t
id|i_rsvd
suffix:colon
l_int|2
suffix:semicolon
DECL|member|i_source
id|bdrkreg_t
id|i_source
suffix:colon
l_int|8
suffix:semicolon
DECL|member|i_init
id|bdrkreg_t
id|i_init
suffix:colon
l_int|3
suffix:semicolon
DECL|member|i_addr
id|bdrkreg_t
id|i_addr
suffix:colon
l_int|38
suffix:semicolon
DECL|member|i_rsvd_1
id|bdrkreg_t
id|i_rsvd_1
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
macro_line|#endif
multiline_comment|/* PIO MANAGEMENT */
DECL|typedef|hub_piomap_t
r_typedef
r_struct
id|hub_piomap_s
op_star
id|hub_piomap_t
suffix:semicolon
r_extern
id|hub_piomap_t
id|hub_piomap_alloc
c_func
(paren
id|devfs_handle_t
id|dev
comma
multiline_comment|/* set up mapping for this device */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* device descriptor */
id|iopaddr_t
id|xtalk_addr
comma
multiline_comment|/* map for this xtalk_addr range */
r_int
id|byte_count
comma
r_int
id|byte_count_max
comma
multiline_comment|/* maximum size of a mapping */
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* defined in sys/pio.h */
r_extern
r_void
id|hub_piomap_free
c_func
(paren
id|hub_piomap_t
id|hub_piomap
)paren
suffix:semicolon
r_extern
id|caddr_t
id|hub_piomap_addr
c_func
(paren
id|hub_piomap_t
id|hub_piomap
comma
multiline_comment|/* mapping resources */
id|iopaddr_t
id|xtalk_addr
comma
multiline_comment|/* map for this xtalk addr */
r_int
id|byte_count
)paren
suffix:semicolon
multiline_comment|/* map this many bytes */
r_extern
r_void
id|hub_piomap_done
c_func
(paren
id|hub_piomap_t
id|hub_piomap
)paren
suffix:semicolon
r_extern
id|caddr_t
id|hub_piotrans_addr
c_func
(paren
id|devfs_handle_t
id|dev
comma
multiline_comment|/* translate to this device */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* device descriptor */
id|iopaddr_t
id|xtalk_addr
comma
multiline_comment|/* Crosstalk address */
r_int
id|byte_count
comma
multiline_comment|/* map this many bytes */
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* (currently unused) */
multiline_comment|/* DMA MANAGEMENT */
DECL|typedef|hub_dmamap_t
r_typedef
r_struct
id|hub_dmamap_s
op_star
id|hub_dmamap_t
suffix:semicolon
r_extern
id|hub_dmamap_t
id|hub_dmamap_alloc
c_func
(paren
id|devfs_handle_t
id|dev
comma
multiline_comment|/* set up mappings for dev */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* device descriptor */
r_int
id|byte_count_max
comma
multiline_comment|/* max size of a mapping */
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* defined in dma.h */
r_extern
r_void
id|hub_dmamap_free
c_func
(paren
id|hub_dmamap_t
id|dmamap
)paren
suffix:semicolon
r_extern
id|iopaddr_t
id|hub_dmamap_addr
c_func
(paren
id|hub_dmamap_t
id|dmamap
comma
multiline_comment|/* use mapping resources */
id|paddr_t
id|paddr
comma
multiline_comment|/* map for this address */
r_int
id|byte_count
)paren
suffix:semicolon
multiline_comment|/* map this many bytes */
r_extern
id|alenlist_t
id|hub_dmamap_list
c_func
(paren
id|hub_dmamap_t
id|dmamap
comma
multiline_comment|/* use mapping resources */
id|alenlist_t
id|alenlist
comma
multiline_comment|/* map this Addr/Length List */
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_void
id|hub_dmamap_done
c_func
(paren
id|hub_dmamap_t
id|dmamap
)paren
suffix:semicolon
multiline_comment|/* done w/ mapping resources */
r_extern
id|iopaddr_t
id|hub_dmatrans_addr
c_func
(paren
id|devfs_handle_t
id|dev
comma
multiline_comment|/* translate for this device */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* device descriptor */
id|paddr_t
id|paddr
comma
multiline_comment|/* system physical address */
r_int
id|byte_count
comma
multiline_comment|/* length */
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* defined in dma.h */
r_extern
id|alenlist_t
id|hub_dmatrans_list
c_func
(paren
id|devfs_handle_t
id|dev
comma
multiline_comment|/* translate for this device */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* device descriptor */
id|alenlist_t
id|palenlist
comma
multiline_comment|/* system addr/length list */
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* defined in dma.h */
r_extern
r_void
id|hub_dmamap_drain
c_func
(paren
id|hub_dmamap_t
id|map
)paren
suffix:semicolon
r_extern
r_void
id|hub_dmaaddr_drain
c_func
(paren
id|devfs_handle_t
id|vhdl
comma
id|paddr_t
id|addr
comma
r_int
id|bytes
)paren
suffix:semicolon
r_extern
r_void
id|hub_dmalist_drain
c_func
(paren
id|devfs_handle_t
id|vhdl
comma
id|alenlist_t
id|list
)paren
suffix:semicolon
multiline_comment|/* INTERRUPT MANAGEMENT */
DECL|typedef|hub_intr_t
r_typedef
r_struct
id|hub_intr_s
op_star
id|hub_intr_t
suffix:semicolon
r_extern
id|hub_intr_t
id|hub_intr_alloc
c_func
(paren
id|devfs_handle_t
id|dev
comma
multiline_comment|/* which device */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* device descriptor */
id|devfs_handle_t
id|owner_dev
)paren
suffix:semicolon
multiline_comment|/* owner of this interrupt */
r_extern
id|hub_intr_t
id|hub_intr_alloc_nothd
c_func
(paren
id|devfs_handle_t
id|dev
comma
multiline_comment|/* which device */
id|device_desc_t
id|dev_desc
comma
multiline_comment|/* device descriptor */
id|devfs_handle_t
id|owner_dev
)paren
suffix:semicolon
multiline_comment|/* owner of this interrupt */
r_extern
r_void
id|hub_intr_free
c_func
(paren
id|hub_intr_t
id|intr_hdl
)paren
suffix:semicolon
r_extern
r_int
id|hub_intr_connect
c_func
(paren
id|hub_intr_t
id|intr_hdl
comma
multiline_comment|/* xtalk intr resource hndl */
id|intr_func_t
id|intr_func
comma
multiline_comment|/* xtalk intr handler */
r_void
op_star
id|intr_arg
comma
multiline_comment|/* arg to intr handler */
id|xtalk_intr_setfunc_t
id|setfunc
comma
multiline_comment|/* func to set intr hw */
r_void
op_star
id|setfunc_arg
comma
multiline_comment|/* arg to setfunc */
r_void
op_star
id|thread
)paren
suffix:semicolon
multiline_comment|/* intr thread to use */
r_extern
r_void
id|hub_intr_disconnect
c_func
(paren
id|hub_intr_t
id|intr_hdl
)paren
suffix:semicolon
r_extern
id|devfs_handle_t
id|hub_intr_cpu_get
c_func
(paren
id|hub_intr_t
id|intr_hdl
)paren
suffix:semicolon
multiline_comment|/* CONFIGURATION MANAGEMENT */
r_extern
r_void
id|hub_provider_startup
c_func
(paren
id|devfs_handle_t
id|hub
)paren
suffix:semicolon
r_extern
r_void
id|hub_provider_shutdown
c_func
(paren
id|devfs_handle_t
id|hub
)paren
suffix:semicolon
DECL|macro|HUB_PIO_CONVEYOR
mdefine_line|#define HUB_PIO_CONVEYOR        0x1     /* PIO in conveyor belt mode */
DECL|macro|HUB_PIO_FIRE_N_FORGET
mdefine_line|#define HUB_PIO_FIRE_N_FORGET   0x2     /* PIO in fire-and-forget mode */
multiline_comment|/* Flags that make sense to hub_widget_flags_set */
DECL|macro|HUB_WIDGET_FLAGS
mdefine_line|#define HUB_WIDGET_FLAGS        (                               &bslash;&n;&t;&t;&t;&t; HUB_PIO_CONVEYOR       |       &bslash;&n;&t;&t;&t;&t; HUB_PIO_FIRE_N_FORGET          &bslash;&n;&t;&t;&t;&t;)
DECL|typedef|hub_widget_flags_t
r_typedef
r_int
id|hub_widget_flags_t
suffix:semicolon
multiline_comment|/* Set the PIO mode for a widget.  These two functions perform the&n; * same operation, but hub_device_flags_set() takes a hardware graph&n; * vertex while hub_widget_flags_set() takes a nasid and widget&n; * number.  In most cases, hub_device_flags_set() should be used.&n; */
r_extern
r_int
id|hub_widget_flags_set
c_func
(paren
id|nasid_t
id|nasid
comma
id|xwidgetnum_t
id|widget_num
comma
id|hub_widget_flags_t
id|flags
)paren
suffix:semicolon
multiline_comment|/* Depending on the flags set take the appropriate actions */
r_extern
r_int
id|hub_device_flags_set
c_func
(paren
id|devfs_handle_t
id|widget_dev
comma
id|hub_widget_flags_t
id|flags
)paren
suffix:semicolon
multiline_comment|/* Error Handling. */
r_extern
r_int
id|hub_ioerror_handler
c_func
(paren
id|devfs_handle_t
comma
r_int
comma
r_int
comma
r_struct
id|io_error_s
op_star
)paren
suffix:semicolon
r_extern
r_int
id|kl_ioerror_handler
c_func
(paren
id|cnodeid_t
comma
id|cnodeid_t
comma
id|cpuid_t
comma
r_int
comma
id|paddr_t
comma
id|caddr_t
comma
id|ioerror_mode_t
)paren
suffix:semicolon
r_extern
r_void
id|hub_widget_reset
c_func
(paren
id|devfs_handle_t
comma
id|xwidgetnum_t
)paren
suffix:semicolon
r_extern
r_int
id|hub_error_devenable
c_func
(paren
id|devfs_handle_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|hub_widgetdev_enable
c_func
(paren
id|devfs_handle_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|hub_widgetdev_shutdown
c_func
(paren
id|devfs_handle_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|hub_dma_enabled
c_func
(paren
id|devfs_handle_t
)paren
suffix:semicolon
macro_line|#endif /* _LANGUAGE_C */
macro_line|#endif /* _KERNEL */
macro_line|#endif  /* _ASM_SN_SN1_HUBIO_NEXT_H */
eof
