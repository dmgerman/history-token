multiline_comment|/*&n; *&n; * IPACX specific defines&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
multiline_comment|/* All Registers original Siemens Spec  */
macro_line|#ifndef INCLUDE_IPACX_H
DECL|macro|INCLUDE_IPACX_H
mdefine_line|#define INCLUDE_IPACX_H
multiline_comment|/* D-channel registers   */
DECL|macro|IPACX_RFIFOD
mdefine_line|#define IPACX_RFIFOD        0x00    /* RD       */
DECL|macro|IPACX_XFIFOD
mdefine_line|#define IPACX_XFIFOD        0x00    /* WR       */
DECL|macro|IPACX_ISTAD
mdefine_line|#define IPACX_ISTAD         0x20    /* RD       */
DECL|macro|IPACX_MASKD
mdefine_line|#define IPACX_MASKD         0x20    /* WR       */
DECL|macro|IPACX_STARD
mdefine_line|#define IPACX_STARD         0x21    /* RD       */
DECL|macro|IPACX_CMDRD
mdefine_line|#define IPACX_CMDRD         0x21    /* WR       */
DECL|macro|IPACX_MODED
mdefine_line|#define IPACX_MODED         0x22    /* RD/WR    */
DECL|macro|IPACX_EXMD1
mdefine_line|#define IPACX_EXMD1         0x23    /* RD/WR    */
DECL|macro|IPACX_TIMR1
mdefine_line|#define IPACX_TIMR1         0x24    /* RD/WR    */
DECL|macro|IPACX_SAP1
mdefine_line|#define IPACX_SAP1          0x25    /* WR       */
DECL|macro|IPACX_SAP2
mdefine_line|#define IPACX_SAP2          0x26    /* WR       */
DECL|macro|IPACX_RBCLD
mdefine_line|#define IPACX_RBCLD         0x26    /* RD       */
DECL|macro|IPACX_RBCHD
mdefine_line|#define IPACX_RBCHD         0x27    /* RD       */
DECL|macro|IPACX_TEI1
mdefine_line|#define IPACX_TEI1          0x27    /* WR       */
DECL|macro|IPACX_TEI2
mdefine_line|#define IPACX_TEI2          0x28    /* WR       */
DECL|macro|IPACX_RSTAD
mdefine_line|#define IPACX_RSTAD         0x28    /* RD       */
DECL|macro|IPACX_TMD
mdefine_line|#define IPACX_TMD           0x29    /* RD/WR    */
DECL|macro|IPACX_CIR0
mdefine_line|#define IPACX_CIR0          0x2E    /* RD       */
DECL|macro|IPACX_CIX0
mdefine_line|#define IPACX_CIX0          0x2E    /* WR       */
DECL|macro|IPACX_CIR1
mdefine_line|#define IPACX_CIR1          0x2F    /* RD       */
DECL|macro|IPACX_CIX1
mdefine_line|#define IPACX_CIX1          0x2F    /* WR       */
multiline_comment|/* Transceiver registers    */
DECL|macro|IPACX_TR_CONF0
mdefine_line|#define IPACX_TR_CONF0      0x30    /* RD/WR    */
DECL|macro|IPACX_TR_CONF1
mdefine_line|#define IPACX_TR_CONF1      0x31    /* RD/WR    */
DECL|macro|IPACX_TR_CONF2
mdefine_line|#define IPACX_TR_CONF2      0x32    /* RD/WR    */
DECL|macro|IPACX_TR_STA
mdefine_line|#define IPACX_TR_STA        0x33    /* RD       */
DECL|macro|IPACX_TR_CMD
mdefine_line|#define IPACX_TR_CMD        0x34    /* RD/WR    */
DECL|macro|IPACX_SQRR1
mdefine_line|#define IPACX_SQRR1         0x35    /* RD       */
DECL|macro|IPACX_SQXR1
mdefine_line|#define IPACX_SQXR1         0x35    /* WR       */
DECL|macro|IPACX_SQRR2
mdefine_line|#define IPACX_SQRR2         0x36    /* RD       */
DECL|macro|IPACX_SQXR2
mdefine_line|#define IPACX_SQXR2         0x36    /* WR       */
DECL|macro|IPACX_SQRR3
mdefine_line|#define IPACX_SQRR3         0x37    /* RD       */
DECL|macro|IPACX_SQXR3
mdefine_line|#define IPACX_SQXR3         0x37    /* WR       */
DECL|macro|IPACX_ISTATR
mdefine_line|#define IPACX_ISTATR        0x38    /* RD       */
DECL|macro|IPACX_MASKTR
mdefine_line|#define IPACX_MASKTR        0x39    /* RD/WR    */
DECL|macro|IPACX_TR_MODE
mdefine_line|#define IPACX_TR_MODE       0x3A    /* RD/WR    */
DECL|macro|IPACX_ACFG1
mdefine_line|#define IPACX_ACFG1         0x3C    /* RD/WR    */
DECL|macro|IPACX_ACFG2
mdefine_line|#define IPACX_ACFG2         0x3D    /* RD/WR    */
DECL|macro|IPACX_AOE
mdefine_line|#define IPACX_AOE           0x3E    /* RD/WR    */
DECL|macro|IPACX_ARX
mdefine_line|#define IPACX_ARX           0x3F    /* RD       */
DECL|macro|IPACX_ATX
mdefine_line|#define IPACX_ATX           0x3F    /* WR       */
multiline_comment|/* IOM: Timeslot, DPS, CDA  */
DECL|macro|IPACX_CDA10
mdefine_line|#define IPACX_CDA10         0x40    /* RD/WR    */
DECL|macro|IPACX_CDA11
mdefine_line|#define IPACX_CDA11         0x41    /* RD/WR    */
DECL|macro|IPACX_CDA20
mdefine_line|#define IPACX_CDA20         0x42    /* RD/WR    */
DECL|macro|IPACX_CDA21
mdefine_line|#define IPACX_CDA21         0x43    /* RD/WR    */
DECL|macro|IPACX_CDA_TSDP10
mdefine_line|#define IPACX_CDA_TSDP10    0x44    /* RD/WR    */
DECL|macro|IPACX_CDA_TSDP11
mdefine_line|#define IPACX_CDA_TSDP11    0x45    /* RD/WR    */
DECL|macro|IPACX_CDA_TSDP20
mdefine_line|#define IPACX_CDA_TSDP20    0x46    /* RD/WR    */
DECL|macro|IPACX_CDA_TSDP21
mdefine_line|#define IPACX_CDA_TSDP21    0x47    /* RD/WR    */
DECL|macro|IPACX_BCHA_TSDP_BC1
mdefine_line|#define IPACX_BCHA_TSDP_BC1 0x48    /* RD/WR    */
DECL|macro|IPACX_BCHA_TSDP_BC2
mdefine_line|#define IPACX_BCHA_TSDP_BC2 0x49    /* RD/WR    */
DECL|macro|IPACX_BCHB_TSDP_BC1
mdefine_line|#define IPACX_BCHB_TSDP_BC1 0x4A    /* RD/WR    */
DECL|macro|IPACX_BCHB_TSDP_BC2
mdefine_line|#define IPACX_BCHB_TSDP_BC2 0x4B    /* RD/WR    */
DECL|macro|IPACX_TR_TSDP_BC1
mdefine_line|#define IPACX_TR_TSDP_BC1   0x4C    /* RD/WR    */
DECL|macro|IPACX_TR_TSDP_BC2
mdefine_line|#define IPACX_TR_TSDP_BC2   0x4D    /* RD/WR    */
DECL|macro|IPACX_CDA1_CR
mdefine_line|#define IPACX_CDA1_CR       0x4E    /* RD/WR    */
DECL|macro|IPACX_CDA2_CR
mdefine_line|#define IPACX_CDA2_CR       0x4F    /* RD/WR    */
multiline_comment|/* IOM: Contol, Sync transfer, Monitor    */
DECL|macro|IPACX_TR_CR
mdefine_line|#define IPACX_TR_CR         0x50    /* RD/WR    */
DECL|macro|IPACX_TRC_CR
mdefine_line|#define IPACX_TRC_CR        0x50    /* RD/WR    */
DECL|macro|IPACX_BCHA_CR
mdefine_line|#define IPACX_BCHA_CR       0x51    /* RD/WR    */
DECL|macro|IPACX_BCHB_CR
mdefine_line|#define IPACX_BCHB_CR       0x52    /* RD/WR    */
DECL|macro|IPACX_DCI_CR
mdefine_line|#define IPACX_DCI_CR        0x53    /* RD/WR    */
DECL|macro|IPACX_DCIC_CR
mdefine_line|#define IPACX_DCIC_CR       0x53    /* RD/WR    */
DECL|macro|IPACX_MON_CR
mdefine_line|#define IPACX_MON_CR        0x54    /* RD/WR    */
DECL|macro|IPACX_SDS1_CR
mdefine_line|#define IPACX_SDS1_CR       0x55    /* RD/WR    */
DECL|macro|IPACX_SDS2_CR
mdefine_line|#define IPACX_SDS2_CR       0x56    /* RD/WR    */
DECL|macro|IPACX_IOM_CR
mdefine_line|#define IPACX_IOM_CR        0x57    /* RD/WR    */
DECL|macro|IPACX_STI
mdefine_line|#define IPACX_STI           0x58    /* RD       */
DECL|macro|IPACX_ASTI
mdefine_line|#define IPACX_ASTI          0x58    /* WR       */
DECL|macro|IPACX_MSTI
mdefine_line|#define IPACX_MSTI          0x59    /* RD/WR    */
DECL|macro|IPACX_SDS_CONF
mdefine_line|#define IPACX_SDS_CONF      0x5A    /* RD/WR    */
DECL|macro|IPACX_MCDA
mdefine_line|#define IPACX_MCDA          0x5B    /* RD       */
DECL|macro|IPACX_MOR
mdefine_line|#define IPACX_MOR           0x5C    /* RD       */
DECL|macro|IPACX_MOX
mdefine_line|#define IPACX_MOX           0x5C    /* WR       */
DECL|macro|IPACX_MOSR
mdefine_line|#define IPACX_MOSR          0x5D    /* RD       */
DECL|macro|IPACX_MOCR
mdefine_line|#define IPACX_MOCR          0x5E    /* RD/WR    */
DECL|macro|IPACX_MSTA
mdefine_line|#define IPACX_MSTA          0x5F    /* RD       */
DECL|macro|IPACX_MCONF
mdefine_line|#define IPACX_MCONF         0x5F    /* WR       */
multiline_comment|/* Interrupt and general registers */
DECL|macro|IPACX_ISTA
mdefine_line|#define IPACX_ISTA          0x60    /* RD       */
DECL|macro|IPACX_MASK
mdefine_line|#define IPACX_MASK          0x60    /* WR       */
DECL|macro|IPACX_AUXI
mdefine_line|#define IPACX_AUXI          0x61    /* RD       */
DECL|macro|IPACX_AUXM
mdefine_line|#define IPACX_AUXM          0x61    /* WR       */
DECL|macro|IPACX_MODE1
mdefine_line|#define IPACX_MODE1         0x62    /* RD/WR    */
DECL|macro|IPACX_MODE2
mdefine_line|#define IPACX_MODE2         0x63    /* RD/WR    */
DECL|macro|IPACX_ID
mdefine_line|#define IPACX_ID            0x64    /* RD       */
DECL|macro|IPACX_SRES
mdefine_line|#define IPACX_SRES          0x64    /* WR       */
DECL|macro|IPACX_TIMR2
mdefine_line|#define IPACX_TIMR2         0x65    /* RD/WR    */
multiline_comment|/* B-channel registers */
DECL|macro|IPACX_OFF_B1
mdefine_line|#define IPACX_OFF_B1        0x70
DECL|macro|IPACX_OFF_B2
mdefine_line|#define IPACX_OFF_B2        0x80
DECL|macro|IPACX_ISTAB
mdefine_line|#define IPACX_ISTAB         0x00    /* RD       */
DECL|macro|IPACX_MASKB
mdefine_line|#define IPACX_MASKB         0x00    /* WR       */
DECL|macro|IPACX_STARB
mdefine_line|#define IPACX_STARB         0x01    /* RD       */
DECL|macro|IPACX_CMDRB
mdefine_line|#define IPACX_CMDRB         0x01    /* WR       */
DECL|macro|IPACX_MODEB
mdefine_line|#define IPACX_MODEB         0x02    /* RD/WR    */
DECL|macro|IPACX_EXMB
mdefine_line|#define IPACX_EXMB          0x03    /* RD/WR    */
DECL|macro|IPACX_RAH1
mdefine_line|#define IPACX_RAH1          0x05    /* WR       */
DECL|macro|IPACX_RAH2
mdefine_line|#define IPACX_RAH2          0x06    /* WR       */
DECL|macro|IPACX_RBCLB
mdefine_line|#define IPACX_RBCLB         0x06    /* RD       */
DECL|macro|IPACX_RBCHB
mdefine_line|#define IPACX_RBCHB         0x07    /* RD       */
DECL|macro|IPACX_RAL1
mdefine_line|#define IPACX_RAL1          0x07    /* WR       */
DECL|macro|IPACX_RAL2
mdefine_line|#define IPACX_RAL2          0x08    /* WR       */
DECL|macro|IPACX_RSTAB
mdefine_line|#define IPACX_RSTAB         0x08    /* RD       */
DECL|macro|IPACX_TMB
mdefine_line|#define IPACX_TMB           0x09    /* RD/WR    */
DECL|macro|IPACX_RFIFOB
mdefine_line|#define IPACX_RFIFOB        0x0A    /*- RD      */
DECL|macro|IPACX_XFIFOB
mdefine_line|#define IPACX_XFIFOB        0x0A    /*- WR      */
multiline_comment|/* Layer 1 Commands */
DECL|macro|IPACX_CMD_TIM
mdefine_line|#define IPACX_CMD_TIM    0x0
DECL|macro|IPACX_CMD_RES
mdefine_line|#define IPACX_CMD_RES    0x1
DECL|macro|IPACX_CMD_SSP
mdefine_line|#define IPACX_CMD_SSP    0x2
DECL|macro|IPACX_CMD_SCP
mdefine_line|#define IPACX_CMD_SCP    0x3
DECL|macro|IPACX_CMD_AR8
mdefine_line|#define IPACX_CMD_AR8    0x8
DECL|macro|IPACX_CMD_AR10
mdefine_line|#define IPACX_CMD_AR10   0x9
DECL|macro|IPACX_CMD_ARL
mdefine_line|#define IPACX_CMD_ARL    0xa
DECL|macro|IPACX_CMD_DI
mdefine_line|#define IPACX_CMD_DI     0xf
multiline_comment|/* Layer 1 Indications */
DECL|macro|IPACX_IND_DR
mdefine_line|#define IPACX_IND_DR     0x0
DECL|macro|IPACX_IND_RES
mdefine_line|#define IPACX_IND_RES    0x1
DECL|macro|IPACX_IND_TMA
mdefine_line|#define IPACX_IND_TMA    0x2
DECL|macro|IPACX_IND_SLD
mdefine_line|#define IPACX_IND_SLD    0x3
DECL|macro|IPACX_IND_RSY
mdefine_line|#define IPACX_IND_RSY    0x4
DECL|macro|IPACX_IND_DR6
mdefine_line|#define IPACX_IND_DR6    0x5
DECL|macro|IPACX_IND_PU
mdefine_line|#define IPACX_IND_PU     0x7
DECL|macro|IPACX_IND_AR
mdefine_line|#define IPACX_IND_AR     0x8
DECL|macro|IPACX_IND_ARL
mdefine_line|#define IPACX_IND_ARL    0xa
DECL|macro|IPACX_IND_CVR
mdefine_line|#define IPACX_IND_CVR    0xb
DECL|macro|IPACX_IND_AI8
mdefine_line|#define IPACX_IND_AI8    0xc
DECL|macro|IPACX_IND_AI10
mdefine_line|#define IPACX_IND_AI10   0xd
DECL|macro|IPACX_IND_AIL
mdefine_line|#define IPACX_IND_AIL    0xe
DECL|macro|IPACX_IND_DC
mdefine_line|#define IPACX_IND_DC     0xf
r_extern
r_void
id|init_ipacx
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|part
)paren
suffix:semicolon
r_extern
r_void
id|interrupt_ipacx
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
macro_line|#endif
eof
