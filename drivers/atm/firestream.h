multiline_comment|/* drivers/atm/firestream.h - FireStream 155 (MB86697) and&n; *                            FireStream  50 (MB86695) device driver &n; */
multiline_comment|/* Written &amp; (C) 2000 by R.E.Wolff@BitWizard.nl &n; * Copied snippets from zatm.c by Werner Almesberger, EPFL LRC/ICA &n; * and ambassador.c Copyright (C) 1995-1999  Madge Networks Ltd &n; */
multiline_comment|/*&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2 of the License, or&n;  (at your option) any later version.&n;&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;  GNU General Public License for more details.&n;&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;&n;  The GNU GPL is contained in /usr/doc/copyright/GPL on a Debian&n;  system and in the file COPYING in the Linux kernel source.&n;*/
multiline_comment|/***********************************************************************&n; *                  first the defines for the chip.                    *&n; ***********************************************************************/
multiline_comment|/********************* General chip parameters. ************************/
DECL|macro|FS_NR_FREE_POOLS
mdefine_line|#define FS_NR_FREE_POOLS   8
DECL|macro|FS_NR_RX_QUEUES
mdefine_line|#define FS_NR_RX_QUEUES    4
multiline_comment|/********************* queues and queue access macros ******************/
multiline_comment|/* A queue entry. */
DECL|struct|FS_QENTRY
r_struct
id|FS_QENTRY
(brace
DECL|member|cmd
id|u32
id|cmd
suffix:semicolon
DECL|member|p0
DECL|member|p1
DECL|member|p2
id|u32
id|p0
comma
id|p1
comma
id|p2
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* A freepool entry. */
DECL|struct|FS_BPENTRY
r_struct
id|FS_BPENTRY
(brace
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|next
id|u32
id|next
suffix:semicolon
DECL|member|bsa
id|u32
id|bsa
suffix:semicolon
DECL|member|aal_bufsize
id|u32
id|aal_bufsize
suffix:semicolon
multiline_comment|/* The hardware doesn&squot;t look at this, but we need the SKB somewhere... */
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|fp
r_struct
id|freepool
op_star
id|fp
suffix:semicolon
DECL|member|dev
r_struct
id|fs_dev
op_star
id|dev
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|STATUS_CODE
mdefine_line|#define STATUS_CODE(qe)  ((qe-&gt;cmd &gt;&gt; 22) &amp; 0x3f)
multiline_comment|/* OFFSETS against the base of a QUEUE... */
DECL|macro|QSA
mdefine_line|#define QSA     0x00
DECL|macro|QEA
mdefine_line|#define QEA     0x04
DECL|macro|QRP
mdefine_line|#define QRP     0x08
DECL|macro|QWP
mdefine_line|#define QWP     0x0c
DECL|macro|QCNF
mdefine_line|#define QCNF    0x10   /* Only for Release queues! */
multiline_comment|/* Not for the transmit pending queue. */
multiline_comment|/* OFFSETS against the base of a FREE POOL... */
DECL|macro|FPCNF
mdefine_line|#define FPCNF   0x00
DECL|macro|FPSA
mdefine_line|#define FPSA    0x04
DECL|macro|FPEA
mdefine_line|#define FPEA    0x08
DECL|macro|FPCNT
mdefine_line|#define FPCNT   0x0c
DECL|macro|FPCTU
mdefine_line|#define FPCTU   0x10
DECL|macro|Q_SA
mdefine_line|#define Q_SA(b)     (b + QSA )
DECL|macro|Q_EA
mdefine_line|#define Q_EA(b)     (b + QEA )
DECL|macro|Q_RP
mdefine_line|#define Q_RP(b)     (b + QRP )
DECL|macro|Q_WP
mdefine_line|#define Q_WP(b)     (b + QWP )
DECL|macro|Q_CNF
mdefine_line|#define Q_CNF(b)    (b + QCNF)
DECL|macro|FP_CNF
mdefine_line|#define FP_CNF(b)   (b + FPCNF)
DECL|macro|FP_SA
mdefine_line|#define FP_SA(b)    (b + FPSA)
DECL|macro|FP_EA
mdefine_line|#define FP_EA(b)    (b + FPEA)
DECL|macro|FP_CNT
mdefine_line|#define FP_CNT(b)   (b + FPCNT)
DECL|macro|FP_CTU
mdefine_line|#define FP_CTU(b)   (b + FPCTU)
multiline_comment|/* bits in a queue register. */
DECL|macro|Q_FULL
mdefine_line|#define Q_FULL      0x1
DECL|macro|Q_EMPTY
mdefine_line|#define Q_EMPTY     0x2
DECL|macro|Q_INCWRAP
mdefine_line|#define Q_INCWRAP   0x4
DECL|macro|Q_ADDR_MASK
mdefine_line|#define Q_ADDR_MASK 0xfffffff0
multiline_comment|/* bits in a FreePool config register */
DECL|macro|RBFP_RBS
mdefine_line|#define RBFP_RBS    (0x1 &lt;&lt; 16)
DECL|macro|RBFP_RBSVAL
mdefine_line|#define RBFP_RBSVAL (0x1 &lt;&lt; 15)
DECL|macro|RBFP_CME
mdefine_line|#define RBFP_CME    (0x1 &lt;&lt; 12)
DECL|macro|RBFP_DLP
mdefine_line|#define RBFP_DLP    (0x1 &lt;&lt; 11)
DECL|macro|RBFP_BFPWT
mdefine_line|#define RBFP_BFPWT  (0x1 &lt;&lt;  0)
multiline_comment|/* FireStream commands. */
DECL|macro|QE_CMD_NULL
mdefine_line|#define QE_CMD_NULL             (0x00 &lt;&lt; 22)
DECL|macro|QE_CMD_REG_RD
mdefine_line|#define QE_CMD_REG_RD           (0x01 &lt;&lt; 22)
DECL|macro|QE_CMD_REG_RDM
mdefine_line|#define QE_CMD_REG_RDM          (0x02 &lt;&lt; 22)
DECL|macro|QE_CMD_REG_WR
mdefine_line|#define QE_CMD_REG_WR           (0x03 &lt;&lt; 22)
DECL|macro|QE_CMD_REG_WRM
mdefine_line|#define QE_CMD_REG_WRM          (0x04 &lt;&lt; 22)
DECL|macro|QE_CMD_CONFIG_TX
mdefine_line|#define QE_CMD_CONFIG_TX        (0x05 &lt;&lt; 22)
DECL|macro|QE_CMD_CONFIG_RX
mdefine_line|#define QE_CMD_CONFIG_RX        (0x06 &lt;&lt; 22)
DECL|macro|QE_CMD_PRP_RD
mdefine_line|#define QE_CMD_PRP_RD           (0x07 &lt;&lt; 22)
DECL|macro|QE_CMD_PRP_RDM
mdefine_line|#define QE_CMD_PRP_RDM          (0x2a &lt;&lt; 22)
DECL|macro|QE_CMD_PRP_WR
mdefine_line|#define QE_CMD_PRP_WR           (0x09 &lt;&lt; 22)
DECL|macro|QE_CMD_PRP_WRM
mdefine_line|#define QE_CMD_PRP_WRM          (0x2b &lt;&lt; 22)
DECL|macro|QE_CMD_RX_EN
mdefine_line|#define QE_CMD_RX_EN            (0x0a &lt;&lt; 22)
DECL|macro|QE_CMD_RX_PURGE
mdefine_line|#define QE_CMD_RX_PURGE         (0x0b &lt;&lt; 22)
DECL|macro|QE_CMD_RX_PURGE_INH
mdefine_line|#define QE_CMD_RX_PURGE_INH     (0x0c &lt;&lt; 22)
DECL|macro|QE_CMD_TX_EN
mdefine_line|#define QE_CMD_TX_EN            (0x0d &lt;&lt; 22)
DECL|macro|QE_CMD_TX_PURGE
mdefine_line|#define QE_CMD_TX_PURGE         (0x0e &lt;&lt; 22)
DECL|macro|QE_CMD_TX_PURGE_INH
mdefine_line|#define QE_CMD_TX_PURGE_INH     (0x0f &lt;&lt; 22)
DECL|macro|QE_CMD_RST_CG
mdefine_line|#define QE_CMD_RST_CG           (0x10 &lt;&lt; 22)
DECL|macro|QE_CMD_SET_CG
mdefine_line|#define QE_CMD_SET_CG           (0x11 &lt;&lt; 22)
DECL|macro|QE_CMD_RST_CLP
mdefine_line|#define QE_CMD_RST_CLP          (0x12 &lt;&lt; 22)
DECL|macro|QE_CMD_SET_CLP
mdefine_line|#define QE_CMD_SET_CLP          (0x13 &lt;&lt; 22)
DECL|macro|QE_CMD_OVERRIDE
mdefine_line|#define QE_CMD_OVERRIDE         (0x14 &lt;&lt; 22)
DECL|macro|QE_CMD_ADD_BFP
mdefine_line|#define QE_CMD_ADD_BFP          (0x15 &lt;&lt; 22)
DECL|macro|QE_CMD_DUMP_TX
mdefine_line|#define QE_CMD_DUMP_TX          (0x16 &lt;&lt; 22)
DECL|macro|QE_CMD_DUMP_RX
mdefine_line|#define QE_CMD_DUMP_RX          (0x17 &lt;&lt; 22)
DECL|macro|QE_CMD_LRAM_RD
mdefine_line|#define QE_CMD_LRAM_RD          (0x18 &lt;&lt; 22)
DECL|macro|QE_CMD_LRAM_RDM
mdefine_line|#define QE_CMD_LRAM_RDM         (0x28 &lt;&lt; 22)
DECL|macro|QE_CMD_LRAM_WR
mdefine_line|#define QE_CMD_LRAM_WR          (0x19 &lt;&lt; 22)
DECL|macro|QE_CMD_LRAM_WRM
mdefine_line|#define QE_CMD_LRAM_WRM         (0x29 &lt;&lt; 22)
DECL|macro|QE_CMD_LRAM_BSET
mdefine_line|#define QE_CMD_LRAM_BSET        (0x1a &lt;&lt; 22)
DECL|macro|QE_CMD_LRAM_BCLR
mdefine_line|#define QE_CMD_LRAM_BCLR        (0x1b &lt;&lt; 22)
DECL|macro|QE_CMD_CONFIG_SEGM
mdefine_line|#define QE_CMD_CONFIG_SEGM      (0x1c &lt;&lt; 22)
DECL|macro|QE_CMD_READ_SEGM
mdefine_line|#define QE_CMD_READ_SEGM        (0x1d &lt;&lt; 22)
DECL|macro|QE_CMD_CONFIG_ROUT
mdefine_line|#define QE_CMD_CONFIG_ROUT      (0x1e &lt;&lt; 22)
DECL|macro|QE_CMD_READ_ROUT
mdefine_line|#define QE_CMD_READ_ROUT        (0x1f &lt;&lt; 22)
DECL|macro|QE_CMD_CONFIG_TM
mdefine_line|#define QE_CMD_CONFIG_TM        (0x20 &lt;&lt; 22)
DECL|macro|QE_CMD_READ_TM
mdefine_line|#define QE_CMD_READ_TM          (0x21 &lt;&lt; 22)
DECL|macro|QE_CMD_CONFIG_TXBM
mdefine_line|#define QE_CMD_CONFIG_TXBM      (0x22 &lt;&lt; 22)
DECL|macro|QE_CMD_READ_TXBM
mdefine_line|#define QE_CMD_READ_TXBM        (0x23 &lt;&lt; 22)
DECL|macro|QE_CMD_CONFIG_RXBM
mdefine_line|#define QE_CMD_CONFIG_RXBM      (0x24 &lt;&lt; 22)
DECL|macro|QE_CMD_READ_RXBM
mdefine_line|#define QE_CMD_READ_RXBM        (0x25 &lt;&lt; 22)
DECL|macro|QE_CMD_CONFIG_REAS
mdefine_line|#define QE_CMD_CONFIG_REAS      (0x26 &lt;&lt; 22)
DECL|macro|QE_CMD_READ_REAS
mdefine_line|#define QE_CMD_READ_REAS        (0x27 &lt;&lt; 22)
DECL|macro|QE_TRANSMIT_DE
mdefine_line|#define QE_TRANSMIT_DE          (0x0 &lt;&lt; 30)
DECL|macro|QE_CMD_LINKED
mdefine_line|#define QE_CMD_LINKED           (0x1 &lt;&lt; 30)
DECL|macro|QE_CMD_IMM
mdefine_line|#define QE_CMD_IMM              (0x2 &lt;&lt; 30)
DECL|macro|QE_CMD_IMM_INQ
mdefine_line|#define QE_CMD_IMM_INQ          (0x3 &lt;&lt; 30)
DECL|macro|TD_EPI
mdefine_line|#define TD_EPI                  (0x1 &lt;&lt; 27)
DECL|macro|TD_COMMAND
mdefine_line|#define TD_COMMAND              (0x1 &lt;&lt; 28)
DECL|macro|TD_DATA
mdefine_line|#define TD_DATA                 (0x0 &lt;&lt; 29)
DECL|macro|TD_RM_CELL
mdefine_line|#define TD_RM_CELL              (0x1 &lt;&lt; 29)
DECL|macro|TD_OAM_CELL
mdefine_line|#define TD_OAM_CELL             (0x2 &lt;&lt; 29)
DECL|macro|TD_OAM_CELL_SEGMENT
mdefine_line|#define TD_OAM_CELL_SEGMENT     (0x3 &lt;&lt; 29)
DECL|macro|TD_BPI
mdefine_line|#define TD_BPI                  (0x1 &lt;&lt; 20)
DECL|macro|FP_FLAGS_EPI
mdefine_line|#define FP_FLAGS_EPI            (0x1 &lt;&lt; 27)
DECL|macro|TX_PQ
mdefine_line|#define TX_PQ(i)  (0x00  + (i) * 0x10)
DECL|macro|TXB_RQ
mdefine_line|#define TXB_RQ    (0x20)
DECL|macro|ST_Q
mdefine_line|#define ST_Q      (0x48)
DECL|macro|RXB_FP
mdefine_line|#define RXB_FP(i) (0x90  + (i) * 0x14)
DECL|macro|RXB_RQ
mdefine_line|#define RXB_RQ(i) (0x134 + (i) * 0x14)
DECL|macro|TXQ_HP
mdefine_line|#define TXQ_HP 0
DECL|macro|TXQ_LP
mdefine_line|#define TXQ_LP 1
multiline_comment|/* Phew. You don&squot;t want to know how many revisions these simple queue&n; * address macros went through before I got them nice and compact as&n; * they are now. -- REW&n; */
multiline_comment|/* And now for something completely different: &n; * The rest of the registers... */
DECL|macro|CMDR0
mdefine_line|#define CMDR0 0x34
DECL|macro|CMDR1
mdefine_line|#define CMDR1 0x38
DECL|macro|CMDR2
mdefine_line|#define CMDR2 0x3c
DECL|macro|CMDR3
mdefine_line|#define CMDR3 0x40
DECL|macro|SARMODE0
mdefine_line|#define SARMODE0     0x5c
DECL|macro|SARMODE0_TXVCS_0
mdefine_line|#define SARMODE0_TXVCS_0    (0x0 &lt;&lt; 0)
DECL|macro|SARMODE0_TXVCS_1k
mdefine_line|#define SARMODE0_TXVCS_1k   (0x1 &lt;&lt; 0)
DECL|macro|SARMODE0_TXVCS_2k
mdefine_line|#define SARMODE0_TXVCS_2k   (0x2 &lt;&lt; 0)
DECL|macro|SARMODE0_TXVCS_4k
mdefine_line|#define SARMODE0_TXVCS_4k   (0x3 &lt;&lt; 0)
DECL|macro|SARMODE0_TXVCS_8k
mdefine_line|#define SARMODE0_TXVCS_8k   (0x4 &lt;&lt; 0)
DECL|macro|SARMODE0_TXVCS_16k
mdefine_line|#define SARMODE0_TXVCS_16k  (0x5 &lt;&lt; 0)
DECL|macro|SARMODE0_TXVCS_32k
mdefine_line|#define SARMODE0_TXVCS_32k  (0x6 &lt;&lt; 0)
DECL|macro|SARMODE0_TXVCS_64k
mdefine_line|#define SARMODE0_TXVCS_64k  (0x7 &lt;&lt; 0)
DECL|macro|SARMODE0_TXVCS_32
mdefine_line|#define SARMODE0_TXVCS_32   (0x8 &lt;&lt; 0)
DECL|macro|SARMODE0_ABRVCS_0
mdefine_line|#define SARMODE0_ABRVCS_0   (0x0 &lt;&lt; 4)
DECL|macro|SARMODE0_ABRVCS_512
mdefine_line|#define SARMODE0_ABRVCS_512 (0x1 &lt;&lt; 4)
DECL|macro|SARMODE0_ABRVCS_1k
mdefine_line|#define SARMODE0_ABRVCS_1k  (0x2 &lt;&lt; 4)
DECL|macro|SARMODE0_ABRVCS_2k
mdefine_line|#define SARMODE0_ABRVCS_2k  (0x3 &lt;&lt; 4)
DECL|macro|SARMODE0_ABRVCS_4k
mdefine_line|#define SARMODE0_ABRVCS_4k  (0x4 &lt;&lt; 4)
DECL|macro|SARMODE0_ABRVCS_8k
mdefine_line|#define SARMODE0_ABRVCS_8k  (0x5 &lt;&lt; 4)
DECL|macro|SARMODE0_ABRVCS_16k
mdefine_line|#define SARMODE0_ABRVCS_16k (0x6 &lt;&lt; 4)
DECL|macro|SARMODE0_ABRVCS_32k
mdefine_line|#define SARMODE0_ABRVCS_32k (0x7 &lt;&lt; 4)
DECL|macro|SARMODE0_ABRVCS_32
mdefine_line|#define SARMODE0_ABRVCS_32  (0x9 &lt;&lt; 4) /* The others are &quot;8&quot;, this one really has to &n;&t;&t;&t;&t;&t;  be 9. Tell me you don&squot;t believe me. -- REW */
DECL|macro|SARMODE0_RXVCS_0
mdefine_line|#define SARMODE0_RXVCS_0    (0x0 &lt;&lt; 8)
DECL|macro|SARMODE0_RXVCS_1k
mdefine_line|#define SARMODE0_RXVCS_1k   (0x1 &lt;&lt; 8)
DECL|macro|SARMODE0_RXVCS_2k
mdefine_line|#define SARMODE0_RXVCS_2k   (0x2 &lt;&lt; 8)
DECL|macro|SARMODE0_RXVCS_4k
mdefine_line|#define SARMODE0_RXVCS_4k   (0x3 &lt;&lt; 8)
DECL|macro|SARMODE0_RXVCS_8k
mdefine_line|#define SARMODE0_RXVCS_8k   (0x4 &lt;&lt; 8)
DECL|macro|SARMODE0_RXVCS_16k
mdefine_line|#define SARMODE0_RXVCS_16k  (0x5 &lt;&lt; 8)
DECL|macro|SARMODE0_RXVCS_32k
mdefine_line|#define SARMODE0_RXVCS_32k  (0x6 &lt;&lt; 8)
DECL|macro|SARMODE0_RXVCS_64k
mdefine_line|#define SARMODE0_RXVCS_64k  (0x7 &lt;&lt; 8)
DECL|macro|SARMODE0_RXVCS_32
mdefine_line|#define SARMODE0_RXVCS_32   (0x8 &lt;&lt; 8) 
DECL|macro|SARMODE0_CALSUP_1
mdefine_line|#define SARMODE0_CALSUP_1  (0x0 &lt;&lt; 12)
DECL|macro|SARMODE0_CALSUP_2
mdefine_line|#define SARMODE0_CALSUP_2  (0x1 &lt;&lt; 12)
DECL|macro|SARMODE0_CALSUP_3
mdefine_line|#define SARMODE0_CALSUP_3  (0x2 &lt;&lt; 12)
DECL|macro|SARMODE0_CALSUP_4
mdefine_line|#define SARMODE0_CALSUP_4  (0x3 &lt;&lt; 12)
DECL|macro|SARMODE0_PRPWT_FS50_0
mdefine_line|#define SARMODE0_PRPWT_FS50_0  (0x0 &lt;&lt; 14)
DECL|macro|SARMODE0_PRPWT_FS50_2
mdefine_line|#define SARMODE0_PRPWT_FS50_2  (0x1 &lt;&lt; 14)
DECL|macro|SARMODE0_PRPWT_FS50_5
mdefine_line|#define SARMODE0_PRPWT_FS50_5  (0x2 &lt;&lt; 14)
DECL|macro|SARMODE0_PRPWT_FS50_11
mdefine_line|#define SARMODE0_PRPWT_FS50_11 (0x3 &lt;&lt; 14)
DECL|macro|SARMODE0_PRPWT_FS155_0
mdefine_line|#define SARMODE0_PRPWT_FS155_0 (0x0 &lt;&lt; 14)
DECL|macro|SARMODE0_PRPWT_FS155_1
mdefine_line|#define SARMODE0_PRPWT_FS155_1 (0x1 &lt;&lt; 14)
DECL|macro|SARMODE0_PRPWT_FS155_2
mdefine_line|#define SARMODE0_PRPWT_FS155_2 (0x2 &lt;&lt; 14)
DECL|macro|SARMODE0_PRPWT_FS155_3
mdefine_line|#define SARMODE0_PRPWT_FS155_3 (0x3 &lt;&lt; 14)
DECL|macro|SARMODE0_SRTS0
mdefine_line|#define SARMODE0_SRTS0     (0x1 &lt;&lt; 23)
DECL|macro|SARMODE0_SRTS1
mdefine_line|#define SARMODE0_SRTS1     (0x1 &lt;&lt; 24)
DECL|macro|SARMODE0_RUN
mdefine_line|#define SARMODE0_RUN       (0x1 &lt;&lt; 25)
DECL|macro|SARMODE0_UNLOCK
mdefine_line|#define SARMODE0_UNLOCK    (0x1 &lt;&lt; 26)
DECL|macro|SARMODE0_CWRE
mdefine_line|#define SARMODE0_CWRE      (0x1 &lt;&lt; 27)
DECL|macro|SARMODE0_INTMODE_READCLEAR
mdefine_line|#define SARMODE0_INTMODE_READCLEAR          (0x0 &lt;&lt; 28)
DECL|macro|SARMODE0_INTMODE_READNOCLEAR
mdefine_line|#define SARMODE0_INTMODE_READNOCLEAR        (0x1 &lt;&lt; 28)
DECL|macro|SARMODE0_INTMODE_READNOCLEARINHIBIT
mdefine_line|#define SARMODE0_INTMODE_READNOCLEARINHIBIT (0x2 &lt;&lt; 28)
DECL|macro|SARMODE0_INTMODE_READCLEARINHIBIT
mdefine_line|#define SARMODE0_INTMODE_READCLEARINHIBIT   (0x3 &lt;&lt; 28)  /* Tell me you don&squot;t believe me. */
DECL|macro|SARMODE0_GINT
mdefine_line|#define SARMODE0_GINT      (0x1 &lt;&lt; 30)
DECL|macro|SARMODE0_SHADEN
mdefine_line|#define SARMODE0_SHADEN    (0x1 &lt;&lt; 31)
DECL|macro|SARMODE1
mdefine_line|#define SARMODE1     0x60
DECL|macro|SARMODE1_TRTL_SHIFT
mdefine_line|#define SARMODE1_TRTL_SHIFT 0   /* Program to 0 */
DECL|macro|SARMODE1_RRTL_SHIFT
mdefine_line|#define SARMODE1_RRTL_SHIFT 4   /* Program to 0 */
DECL|macro|SARMODE1_TAGM
mdefine_line|#define SARMODE1_TAGM       (0x1 &lt;&lt;  8)  /* Program to 0 */
DECL|macro|SARMODE1_HECM0
mdefine_line|#define SARMODE1_HECM0      (0x1 &lt;&lt;  9)
DECL|macro|SARMODE1_HECM1
mdefine_line|#define SARMODE1_HECM1      (0x1 &lt;&lt; 10)
DECL|macro|SARMODE1_HECM2
mdefine_line|#define SARMODE1_HECM2      (0x1 &lt;&lt; 11)
DECL|macro|SARMODE1_GFCE
mdefine_line|#define SARMODE1_GFCE       (0x1 &lt;&lt; 14)
DECL|macro|SARMODE1_GFCR
mdefine_line|#define SARMODE1_GFCR       (0x1 &lt;&lt; 15)
DECL|macro|SARMODE1_PMS
mdefine_line|#define SARMODE1_PMS        (0x1 &lt;&lt; 18)
DECL|macro|SARMODE1_GPRI
mdefine_line|#define SARMODE1_GPRI       (0x1 &lt;&lt; 19)
DECL|macro|SARMODE1_GPAS
mdefine_line|#define SARMODE1_GPAS       (0x1 &lt;&lt; 20)
DECL|macro|SARMODE1_GVAS
mdefine_line|#define SARMODE1_GVAS       (0x1 &lt;&lt; 21)
DECL|macro|SARMODE1_GNAM
mdefine_line|#define SARMODE1_GNAM       (0x1 &lt;&lt; 22)
DECL|macro|SARMODE1_GPLEN
mdefine_line|#define SARMODE1_GPLEN      (0x1 &lt;&lt; 23)
DECL|macro|SARMODE1_DUMPE
mdefine_line|#define SARMODE1_DUMPE      (0x1 &lt;&lt; 24)
DECL|macro|SARMODE1_OAMCRC
mdefine_line|#define SARMODE1_OAMCRC     (0x1 &lt;&lt; 25)
DECL|macro|SARMODE1_DCOAM
mdefine_line|#define SARMODE1_DCOAM      (0x1 &lt;&lt; 26)
DECL|macro|SARMODE1_DCRM
mdefine_line|#define SARMODE1_DCRM       (0x1 &lt;&lt; 27)
DECL|macro|SARMODE1_TSTLP
mdefine_line|#define SARMODE1_TSTLP      (0x1 &lt;&lt; 28)
DECL|macro|SARMODE1_DEFHEC
mdefine_line|#define SARMODE1_DEFHEC     (0x1 &lt;&lt; 29)
DECL|macro|ISR
mdefine_line|#define ISR      0x64
DECL|macro|IUSR
mdefine_line|#define IUSR     0x68
DECL|macro|IMR
mdefine_line|#define IMR      0x6c
DECL|macro|ISR_LPCO
mdefine_line|#define ISR_LPCO          (0x1 &lt;&lt;  0)
DECL|macro|ISR_DPCO
mdefine_line|#define ISR_DPCO          (0x1 &lt;&lt;  1)
DECL|macro|ISR_RBRQ0_W
mdefine_line|#define ISR_RBRQ0_W       (0x1 &lt;&lt;  2)
DECL|macro|ISR_RBRQ1_W
mdefine_line|#define ISR_RBRQ1_W       (0x1 &lt;&lt;  3)
DECL|macro|ISR_RBRQ2_W
mdefine_line|#define ISR_RBRQ2_W       (0x1 &lt;&lt;  4)
DECL|macro|ISR_RBRQ3_W
mdefine_line|#define ISR_RBRQ3_W       (0x1 &lt;&lt;  5)
DECL|macro|ISR_RBRQ0_NF
mdefine_line|#define ISR_RBRQ0_NF      (0x1 &lt;&lt;  6)
DECL|macro|ISR_RBRQ1_NF
mdefine_line|#define ISR_RBRQ1_NF      (0x1 &lt;&lt;  7)
DECL|macro|ISR_RBRQ2_NF
mdefine_line|#define ISR_RBRQ2_NF      (0x1 &lt;&lt;  8)
DECL|macro|ISR_RBRQ3_NF
mdefine_line|#define ISR_RBRQ3_NF      (0x1 &lt;&lt;  9)
DECL|macro|ISR_BFP_SC
mdefine_line|#define ISR_BFP_SC        (0x1 &lt;&lt; 10)
DECL|macro|ISR_INIT
mdefine_line|#define ISR_INIT          (0x1 &lt;&lt; 11)
DECL|macro|ISR_INIT_ERR
mdefine_line|#define ISR_INIT_ERR      (0x1 &lt;&lt; 12) /* Documented as &quot;reserved&quot; */
DECL|macro|ISR_USCEO
mdefine_line|#define ISR_USCEO         (0x1 &lt;&lt; 13)
DECL|macro|ISR_UPEC0
mdefine_line|#define ISR_UPEC0         (0x1 &lt;&lt; 14)
DECL|macro|ISR_VPFCO
mdefine_line|#define ISR_VPFCO         (0x1 &lt;&lt; 15)
DECL|macro|ISR_CRCCO
mdefine_line|#define ISR_CRCCO         (0x1 &lt;&lt; 16)
DECL|macro|ISR_HECO
mdefine_line|#define ISR_HECO          (0x1 &lt;&lt; 17)
DECL|macro|ISR_TBRQ_W
mdefine_line|#define ISR_TBRQ_W        (0x1 &lt;&lt; 18)
DECL|macro|ISR_TBRQ_NF
mdefine_line|#define ISR_TBRQ_NF       (0x1 &lt;&lt; 19)
DECL|macro|ISR_CTPQ_E
mdefine_line|#define ISR_CTPQ_E        (0x1 &lt;&lt; 20)
DECL|macro|ISR_GFC_C0
mdefine_line|#define ISR_GFC_C0        (0x1 &lt;&lt; 21)
DECL|macro|ISR_PCI_FTL
mdefine_line|#define ISR_PCI_FTL       (0x1 &lt;&lt; 22)
DECL|macro|ISR_CSQ_W
mdefine_line|#define ISR_CSQ_W         (0x1 &lt;&lt; 23)
DECL|macro|ISR_CSQ_NF
mdefine_line|#define ISR_CSQ_NF        (0x1 &lt;&lt; 24)
DECL|macro|ISR_EXT_INT
mdefine_line|#define ISR_EXT_INT       (0x1 &lt;&lt; 25)
DECL|macro|ISR_RXDMA_S
mdefine_line|#define ISR_RXDMA_S       (0x1 &lt;&lt; 26)
DECL|macro|TMCONF
mdefine_line|#define TMCONF 0x78
multiline_comment|/* Bits? */
DECL|macro|CALPRESCALE
mdefine_line|#define CALPRESCALE 0x7c
multiline_comment|/* Bits? */
DECL|macro|CELLOSCONF
mdefine_line|#define CELLOSCONF 0x84
DECL|macro|CELLOSCONF_COTS
mdefine_line|#define CELLOSCONF_COTS   (0x1 &lt;&lt; 28)
DECL|macro|CELLOSCONF_CEN
mdefine_line|#define CELLOSCONF_CEN    (0x1 &lt;&lt; 27)
DECL|macro|CELLOSCONF_SC8
mdefine_line|#define CELLOSCONF_SC8    (0x3 &lt;&lt; 24)
DECL|macro|CELLOSCONF_SC4
mdefine_line|#define CELLOSCONF_SC4    (0x2 &lt;&lt; 24)
DECL|macro|CELLOSCONF_SC2
mdefine_line|#define CELLOSCONF_SC2    (0x1 &lt;&lt; 24)
DECL|macro|CELLOSCONF_SC1
mdefine_line|#define CELLOSCONF_SC1    (0x0 &lt;&lt; 24)
DECL|macro|CELLOSCONF_COBS
mdefine_line|#define CELLOSCONF_COBS   (0x1 &lt;&lt; 16)
DECL|macro|CELLOSCONF_COPK
mdefine_line|#define CELLOSCONF_COPK   (0x1 &lt;&lt;  8)
DECL|macro|CELLOSCONF_COST
mdefine_line|#define CELLOSCONF_COST   (0x1 &lt;&lt;  0)
multiline_comment|/* Bits? */
DECL|macro|RAS0
mdefine_line|#define RAS0 0x1bc
DECL|macro|RAS0_DCD_XHLT
mdefine_line|#define RAS0_DCD_XHLT (0x1 &lt;&lt; 31)
DECL|macro|RAS0_VPSEL
mdefine_line|#define RAS0_VPSEL    (0x1 &lt;&lt; 16)
DECL|macro|RAS0_VCSEL
mdefine_line|#define RAS0_VCSEL    (0x1 &lt;&lt;  0)
DECL|macro|RAS1
mdefine_line|#define RAS1 0x1c0
DECL|macro|RAS1_UTREG
mdefine_line|#define RAS1_UTREG    (0x1 &lt;&lt; 5)
DECL|macro|DMAMR
mdefine_line|#define DMAMR 0x1cc
DECL|macro|DMAMR_TX_MODE_FULL
mdefine_line|#define DMAMR_TX_MODE_FULL (0x0 &lt;&lt; 0)
DECL|macro|DMAMR_TX_MODE_PART
mdefine_line|#define DMAMR_TX_MODE_PART (0x1 &lt;&lt; 0)
DECL|macro|DMAMR_TX_MODE_NONE
mdefine_line|#define DMAMR_TX_MODE_NONE (0x2 &lt;&lt; 0) /* And 3 */
DECL|macro|RAS2
mdefine_line|#define RAS2 0x280
DECL|macro|RAS2_NNI
mdefine_line|#define RAS2_NNI  (0x1 &lt;&lt; 0)
DECL|macro|RAS2_USEL
mdefine_line|#define RAS2_USEL (0x1 &lt;&lt; 1)
DECL|macro|RAS2_UBS
mdefine_line|#define RAS2_UBS  (0x1 &lt;&lt; 2)
DECL|struct|fs_transmit_config
r_struct
id|fs_transmit_config
(brace
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|atm_hdr
id|u32
id|atm_hdr
suffix:semicolon
DECL|member|TMC
id|u32
id|TMC
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|spec
id|u32
id|spec
suffix:semicolon
DECL|member|rtag
id|u32
id|rtag
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TC_FLAGS_AAL5
mdefine_line|#define TC_FLAGS_AAL5      (0x0 &lt;&lt; 29)
DECL|macro|TC_FLAGS_TRANSPARENT_PAYLOAD
mdefine_line|#define TC_FLAGS_TRANSPARENT_PAYLOAD (0x1 &lt;&lt; 29)
DECL|macro|TC_FLAGS_TRANSPARENT_CELL
mdefine_line|#define TC_FLAGS_TRANSPARENT_CELL    (0x2 &lt;&lt; 29)
DECL|macro|TC_FLAGS_STREAMING
mdefine_line|#define TC_FLAGS_STREAMING (0x1 &lt;&lt; 28)
DECL|macro|TC_FLAGS_PACKET
mdefine_line|#define TC_FLAGS_PACKET    (0x0) 
DECL|macro|TC_FLAGS_TYPE_ABR
mdefine_line|#define TC_FLAGS_TYPE_ABR  (0x0 &lt;&lt; 22)
DECL|macro|TC_FLAGS_TYPE_CBR
mdefine_line|#define TC_FLAGS_TYPE_CBR  (0x1 &lt;&lt; 22)
DECL|macro|TC_FLAGS_TYPE_VBR
mdefine_line|#define TC_FLAGS_TYPE_VBR  (0x2 &lt;&lt; 22)
DECL|macro|TC_FLAGS_TYPE_UBR
mdefine_line|#define TC_FLAGS_TYPE_UBR  (0x3 &lt;&lt; 22)
DECL|macro|TC_FLAGS_CAL0
mdefine_line|#define TC_FLAGS_CAL0      (0x0 &lt;&lt; 20)
DECL|macro|TC_FLAGS_CAL1
mdefine_line|#define TC_FLAGS_CAL1      (0x1 &lt;&lt; 20)
DECL|macro|TC_FLAGS_CAL2
mdefine_line|#define TC_FLAGS_CAL2      (0x2 &lt;&lt; 20)
DECL|macro|TC_FLAGS_CAL3
mdefine_line|#define TC_FLAGS_CAL3      (0x3 &lt;&lt; 20)
DECL|macro|RC_FLAGS_NAM
mdefine_line|#define RC_FLAGS_NAM        (0x1 &lt;&lt; 13)
DECL|macro|RC_FLAGS_RXBM_PSB
mdefine_line|#define RC_FLAGS_RXBM_PSB   (0x0 &lt;&lt; 14)
DECL|macro|RC_FLAGS_RXBM_CIF
mdefine_line|#define RC_FLAGS_RXBM_CIF   (0x1 &lt;&lt; 14)
DECL|macro|RC_FLAGS_RXBM_PMB
mdefine_line|#define RC_FLAGS_RXBM_PMB   (0x2 &lt;&lt; 14)
DECL|macro|RC_FLAGS_RXBM_STR
mdefine_line|#define RC_FLAGS_RXBM_STR   (0x4 &lt;&lt; 14)
DECL|macro|RC_FLAGS_RXBM_SAF
mdefine_line|#define RC_FLAGS_RXBM_SAF   (0x6 &lt;&lt; 14)
DECL|macro|RC_FLAGS_RXBM_POS
mdefine_line|#define RC_FLAGS_RXBM_POS   (0x6 &lt;&lt; 14)
DECL|macro|RC_FLAGS_BFPS
mdefine_line|#define RC_FLAGS_BFPS       (0x1 &lt;&lt; 17)
DECL|macro|RC_FLAGS_BFPS_BFP
mdefine_line|#define RC_FLAGS_BFPS_BFP   (0x1 &lt;&lt; 17)
DECL|macro|RC_FLAGS_BFPS_BFP0
mdefine_line|#define RC_FLAGS_BFPS_BFP0  (0x0 &lt;&lt; 17)
DECL|macro|RC_FLAGS_BFPS_BFP1
mdefine_line|#define RC_FLAGS_BFPS_BFP1  (0x1 &lt;&lt; 17)
DECL|macro|RC_FLAGS_BFPS_BFP2
mdefine_line|#define RC_FLAGS_BFPS_BFP2  (0x2 &lt;&lt; 17)
DECL|macro|RC_FLAGS_BFPS_BFP3
mdefine_line|#define RC_FLAGS_BFPS_BFP3  (0x3 &lt;&lt; 17)
DECL|macro|RC_FLAGS_BFPS_BFP4
mdefine_line|#define RC_FLAGS_BFPS_BFP4  (0x4 &lt;&lt; 17)
DECL|macro|RC_FLAGS_BFPS_BFP5
mdefine_line|#define RC_FLAGS_BFPS_BFP5  (0x5 &lt;&lt; 17)
DECL|macro|RC_FLAGS_BFPS_BFP6
mdefine_line|#define RC_FLAGS_BFPS_BFP6  (0x6 &lt;&lt; 17)
DECL|macro|RC_FLAGS_BFPS_BFP7
mdefine_line|#define RC_FLAGS_BFPS_BFP7  (0x7 &lt;&lt; 17)
DECL|macro|RC_FLAGS_BFPS_BFP01
mdefine_line|#define RC_FLAGS_BFPS_BFP01 (0x8 &lt;&lt; 17)
DECL|macro|RC_FLAGS_BFPS_BFP23
mdefine_line|#define RC_FLAGS_BFPS_BFP23 (0x9 &lt;&lt; 17)
DECL|macro|RC_FLAGS_BFPS_BFP45
mdefine_line|#define RC_FLAGS_BFPS_BFP45 (0xa &lt;&lt; 17)
DECL|macro|RC_FLAGS_BFPS_BFP67
mdefine_line|#define RC_FLAGS_BFPS_BFP67 (0xb &lt;&lt; 17)
DECL|macro|RC_FLAGS_BFPS_BFP07
mdefine_line|#define RC_FLAGS_BFPS_BFP07 (0xc &lt;&lt; 17)
DECL|macro|RC_FLAGS_BFPS_BFP27
mdefine_line|#define RC_FLAGS_BFPS_BFP27 (0xd &lt;&lt; 17)
DECL|macro|RC_FLAGS_BFPS_BFP47
mdefine_line|#define RC_FLAGS_BFPS_BFP47 (0xe &lt;&lt; 17)
DECL|macro|RC_FLAGS_BFPS
mdefine_line|#define RC_FLAGS_BFPS       (0x1 &lt;&lt; 17)
DECL|macro|RC_FLAGS_BFPP
mdefine_line|#define RC_FLAGS_BFPP       (0x1 &lt;&lt; 21)
DECL|macro|RC_FLAGS_TEVC
mdefine_line|#define RC_FLAGS_TEVC       (0x1 &lt;&lt; 22)
DECL|macro|RC_FLAGS_TEP
mdefine_line|#define RC_FLAGS_TEP        (0x1 &lt;&lt; 23)
DECL|macro|RC_FLAGS_AAL5
mdefine_line|#define RC_FLAGS_AAL5       (0x0 &lt;&lt; 24)
DECL|macro|RC_FLAGS_TRANSP
mdefine_line|#define RC_FLAGS_TRANSP     (0x1 &lt;&lt; 24)
DECL|macro|RC_FLAGS_TRANSC
mdefine_line|#define RC_FLAGS_TRANSC     (0x2 &lt;&lt; 24)
DECL|macro|RC_FLAGS_ML
mdefine_line|#define RC_FLAGS_ML         (0x1 &lt;&lt; 27)
DECL|macro|RC_FLAGS_TRBRM
mdefine_line|#define RC_FLAGS_TRBRM      (0x1 &lt;&lt; 28)
DECL|macro|RC_FLAGS_PRI
mdefine_line|#define RC_FLAGS_PRI        (0x1 &lt;&lt; 29)
DECL|macro|RC_FLAGS_HOAM
mdefine_line|#define RC_FLAGS_HOAM       (0x1 &lt;&lt; 30)
DECL|macro|RC_FLAGS_CRC10
mdefine_line|#define RC_FLAGS_CRC10      (0x1 &lt;&lt; 31)
DECL|macro|RAC
mdefine_line|#define RAC 0x1c8
DECL|macro|RAM
mdefine_line|#define RAM 0x1c4
multiline_comment|/************************************************************************&n; *         Then the datastructures that the DRIVER uses.                *&n; ************************************************************************/
DECL|macro|TXQ_NENTRIES
mdefine_line|#define TXQ_NENTRIES  32
DECL|macro|RXRQ_NENTRIES
mdefine_line|#define RXRQ_NENTRIES 1024
DECL|struct|fs_vcc
r_struct
id|fs_vcc
(brace
DECL|member|channo
r_int
id|channo
suffix:semicolon
DECL|member|close_wait
id|wait_queue_head_t
id|close_wait
suffix:semicolon
DECL|member|last_skb
r_struct
id|sk_buff
op_star
id|last_skb
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|queue
r_struct
id|queue
(brace
DECL|member|sa
DECL|member|ea
r_struct
id|FS_QENTRY
op_star
id|sa
comma
op_star
id|ea
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|freepool
r_struct
id|freepool
(brace
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|bufsize
r_int
id|bufsize
suffix:semicolon
DECL|member|nr_buffers
r_int
id|nr_buffers
suffix:semicolon
DECL|member|n
r_int
id|n
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MAX_PHY
mdefine_line|#define MAX_PHY 0x20
DECL|struct|fs_dev
r_struct
id|fs_dev
(brace
DECL|member|next
r_struct
id|fs_dev
op_star
id|next
suffix:semicolon
multiline_comment|/* other FS devices */
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|irq
r_int
r_char
id|irq
suffix:semicolon
multiline_comment|/* IRQ */
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
multiline_comment|/* PCI stuff */
DECL|member|atm_dev
r_struct
id|atm_dev
op_star
id|atm_dev
(braket
id|MAX_PHY
)braket
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|start_number
r_int
id|start_number
suffix:semicolon
DECL|member|hw_base
r_int
r_int
id|hw_base
suffix:semicolon
multiline_comment|/* mem base address */
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
multiline_comment|/* Mapping of base address */
DECL|member|channo
r_int
id|channo
suffix:semicolon
DECL|member|channel_mask
r_int
r_int
id|channel_mask
suffix:semicolon
DECL|member|hp_txq
DECL|member|lp_txq
DECL|member|tx_relq
DECL|member|st_q
r_struct
id|queue
id|hp_txq
comma
id|lp_txq
comma
id|tx_relq
comma
id|st_q
suffix:semicolon
DECL|member|rx_fp
r_struct
id|freepool
id|rx_fp
(braket
id|FS_NR_FREE_POOLS
)braket
suffix:semicolon
DECL|member|rx_rq
r_struct
id|queue
id|rx_rq
(braket
id|FS_NR_RX_QUEUES
)braket
suffix:semicolon
DECL|member|nchannels
r_int
id|nchannels
suffix:semicolon
DECL|member|atm_vccs
r_struct
id|atm_vcc
op_star
op_star
id|atm_vccs
suffix:semicolon
DECL|member|tx_inuse
r_void
op_star
id|tx_inuse
suffix:semicolon
DECL|member|ntxpckts
r_int
id|ntxpckts
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Number of channesl that the FS50 supports. */
DECL|macro|FS50_CHANNEL_BITS
mdefine_line|#define FS50_CHANNEL_BITS  5
DECL|macro|FS50_NR_CHANNELS
mdefine_line|#define FS50_NR_CHANNELS      (1 &lt;&lt; FS50_CHANNEL_BITS)
DECL|macro|FS_DEV
mdefine_line|#define FS_DEV(atm_dev) ((struct fs_dev *) (atm_dev)-&gt;dev_data)
DECL|macro|FS_VCC
mdefine_line|#define FS_VCC(atm_vcc) ((struct fs_vcc *) (atm_vcc)-&gt;dev_data)
DECL|macro|FS_IS50
mdefine_line|#define FS_IS50  0x1
DECL|macro|FS_IS155
mdefine_line|#define FS_IS155 0x2
DECL|macro|IS_FS50
mdefine_line|#define IS_FS50(dev)  (dev-&gt;flags &amp; FS_IS50)
DECL|macro|IS_FS155
mdefine_line|#define IS_FS155(dev) (dev-&gt;flags &amp; FS_IS155)
multiline_comment|/* Within limits this is user-configurable. */
multiline_comment|/* Note: Currently the sum (10 -&gt; 1k channels) is hardcoded in the driver. */
DECL|macro|FS155_VPI_BITS
mdefine_line|#define FS155_VPI_BITS 4
DECL|macro|FS155_VCI_BITS
mdefine_line|#define FS155_VCI_BITS 6
DECL|macro|FS155_CHANNEL_BITS
mdefine_line|#define FS155_CHANNEL_BITS  (FS155_VPI_BITS + FS155_VCI_BITS)
DECL|macro|FS155_NR_CHANNELS
mdefine_line|#define FS155_NR_CHANNELS   (1 &lt;&lt; FS155_CHANNEL_BITS)
eof
