multiline_comment|/* $Id: isar.h,v 1.9.6.2 2001/09/23 22:24:49 kai Exp $&n; *&n; * ISAR (Siemens PSB 7110) specific defines&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
DECL|macro|ISAR_IRQMSK
mdefine_line|#define ISAR_IRQMSK&t;0x04
DECL|macro|ISAR_IRQSTA
mdefine_line|#define ISAR_IRQSTA&t;0x04
DECL|macro|ISAR_IRQBIT
mdefine_line|#define ISAR_IRQBIT&t;0x75
DECL|macro|ISAR_CTRL_H
mdefine_line|#define ISAR_CTRL_H&t;0x61
DECL|macro|ISAR_CTRL_L
mdefine_line|#define ISAR_CTRL_L&t;0x60
DECL|macro|ISAR_IIS
mdefine_line|#define ISAR_IIS&t;0x58
DECL|macro|ISAR_IIA
mdefine_line|#define ISAR_IIA&t;0x58
DECL|macro|ISAR_HIS
mdefine_line|#define ISAR_HIS&t;0x50
DECL|macro|ISAR_HIA
mdefine_line|#define ISAR_HIA&t;0x50
DECL|macro|ISAR_MBOX
mdefine_line|#define ISAR_MBOX&t;0x4c
DECL|macro|ISAR_WADR
mdefine_line|#define ISAR_WADR&t;0x4a
DECL|macro|ISAR_RADR
mdefine_line|#define ISAR_RADR&t;0x48 
DECL|macro|ISAR_HIS_VNR
mdefine_line|#define ISAR_HIS_VNR&t;&t;0x14
DECL|macro|ISAR_HIS_DKEY
mdefine_line|#define ISAR_HIS_DKEY&t;&t;0x02
DECL|macro|ISAR_HIS_FIRM
mdefine_line|#define ISAR_HIS_FIRM&t;&t;0x1e
DECL|macro|ISAR_HIS_STDSP
mdefine_line|#define ISAR_HIS_STDSP&t;&t;0x08
DECL|macro|ISAR_HIS_DIAG
mdefine_line|#define ISAR_HIS_DIAG&t;&t;0x05
DECL|macro|ISAR_HIS_P0CFG
mdefine_line|#define ISAR_HIS_P0CFG&t;&t;0x3c
DECL|macro|ISAR_HIS_P12CFG
mdefine_line|#define ISAR_HIS_P12CFG&t;&t;0x24
DECL|macro|ISAR_HIS_SARTCFG
mdefine_line|#define ISAR_HIS_SARTCFG&t;0x25&t;
DECL|macro|ISAR_HIS_PUMPCFG
mdefine_line|#define ISAR_HIS_PUMPCFG&t;0x26&t;
DECL|macro|ISAR_HIS_PUMPCTRL
mdefine_line|#define ISAR_HIS_PUMPCTRL&t;0x2a&t;
DECL|macro|ISAR_HIS_IOM2CFG
mdefine_line|#define ISAR_HIS_IOM2CFG&t;0x27
DECL|macro|ISAR_HIS_IOM2REQ
mdefine_line|#define ISAR_HIS_IOM2REQ&t;0x07
DECL|macro|ISAR_HIS_IOM2CTRL
mdefine_line|#define ISAR_HIS_IOM2CTRL&t;0x2b
DECL|macro|ISAR_HIS_BSTREQ
mdefine_line|#define ISAR_HIS_BSTREQ&t;&t;0x0c
DECL|macro|ISAR_HIS_PSTREQ
mdefine_line|#define ISAR_HIS_PSTREQ&t;&t;0x0e
DECL|macro|ISAR_HIS_SDATA
mdefine_line|#define ISAR_HIS_SDATA&t;&t;0x20
DECL|macro|ISAR_HIS_DPS1
mdefine_line|#define ISAR_HIS_DPS1&t;&t;0x40
DECL|macro|ISAR_HIS_DPS2
mdefine_line|#define ISAR_HIS_DPS2&t;&t;0x80
DECL|macro|SET_DPS
mdefine_line|#define SET_DPS(x)&t;&t;((x&lt;&lt;6) &amp; 0xc0)
DECL|macro|ISAR_IIS_MSCMSD
mdefine_line|#define ISAR_IIS_MSCMSD&t;&t;0x3f
DECL|macro|ISAR_IIS_VNR
mdefine_line|#define ISAR_IIS_VNR&t;&t;0x15
DECL|macro|ISAR_IIS_DKEY
mdefine_line|#define ISAR_IIS_DKEY&t;&t;0x03
DECL|macro|ISAR_IIS_FIRM
mdefine_line|#define ISAR_IIS_FIRM&t;&t;0x1f
DECL|macro|ISAR_IIS_STDSP
mdefine_line|#define ISAR_IIS_STDSP&t;&t;0x09
DECL|macro|ISAR_IIS_DIAG
mdefine_line|#define ISAR_IIS_DIAG&t;&t;0x25
DECL|macro|ISAR_IIS_GSTEV
mdefine_line|#define ISAR_IIS_GSTEV&t;&t;0x00
DECL|macro|ISAR_IIS_BSTEV
mdefine_line|#define ISAR_IIS_BSTEV&t;&t;0x28
DECL|macro|ISAR_IIS_BSTRSP
mdefine_line|#define ISAR_IIS_BSTRSP&t;&t;0x2c
DECL|macro|ISAR_IIS_PSTRSP
mdefine_line|#define ISAR_IIS_PSTRSP&t;&t;0x2e
DECL|macro|ISAR_IIS_PSTEV
mdefine_line|#define ISAR_IIS_PSTEV&t;&t;0x2a
DECL|macro|ISAR_IIS_IOM2RSP
mdefine_line|#define ISAR_IIS_IOM2RSP&t;0x27
DECL|macro|ISAR_IIS_RDATA
mdefine_line|#define ISAR_IIS_RDATA&t;&t;0x20
DECL|macro|ISAR_IIS_INVMSG
mdefine_line|#define ISAR_IIS_INVMSG&t;&t;0x3f
DECL|macro|ISAR_CTRL_SWVER
mdefine_line|#define ISAR_CTRL_SWVER&t;0x10
DECL|macro|ISAR_CTRL_STST
mdefine_line|#define ISAR_CTRL_STST&t;0x40
DECL|macro|ISAR_MSG_HWVER
mdefine_line|#define ISAR_MSG_HWVER&t;{0x20, 0, 1}
DECL|macro|ISAR_DP1_USE
mdefine_line|#define ISAR_DP1_USE&t;1
DECL|macro|ISAR_DP2_USE
mdefine_line|#define ISAR_DP2_USE&t;2
DECL|macro|ISAR_RATE_REQ
mdefine_line|#define ISAR_RATE_REQ&t;3
DECL|macro|PMOD_DISABLE
mdefine_line|#define PMOD_DISABLE&t;0
DECL|macro|PMOD_FAX
mdefine_line|#define PMOD_FAX&t;1
DECL|macro|PMOD_DATAMODEM
mdefine_line|#define PMOD_DATAMODEM&t;2
DECL|macro|PMOD_HALFDUPLEX
mdefine_line|#define PMOD_HALFDUPLEX&t;3
DECL|macro|PMOD_V110
mdefine_line|#define PMOD_V110&t;4
DECL|macro|PMOD_DTMF
mdefine_line|#define PMOD_DTMF&t;5
DECL|macro|PMOD_DTMF_TRANS
mdefine_line|#define PMOD_DTMF_TRANS&t;6
DECL|macro|PMOD_BYPASS
mdefine_line|#define PMOD_BYPASS&t;7
DECL|macro|PCTRL_ORIG
mdefine_line|#define PCTRL_ORIG&t;0x80
DECL|macro|PV32P2_V23R
mdefine_line|#define PV32P2_V23R&t;0x40
DECL|macro|PV32P2_V22A
mdefine_line|#define PV32P2_V22A&t;0x20
DECL|macro|PV32P2_V22B
mdefine_line|#define PV32P2_V22B&t;0x10
DECL|macro|PV32P2_V22C
mdefine_line|#define PV32P2_V22C&t;0x08
DECL|macro|PV32P2_V21
mdefine_line|#define PV32P2_V21&t;0x02
DECL|macro|PV32P2_BEL
mdefine_line|#define PV32P2_BEL&t;0x01
singleline_comment|// LSB MSB in ISAR doc wrong !!! Arghhh
DECL|macro|PV32P3_AMOD
mdefine_line|#define PV32P3_AMOD&t;0x80
DECL|macro|PV32P3_V32B
mdefine_line|#define PV32P3_V32B&t;0x02
DECL|macro|PV32P3_V23B
mdefine_line|#define PV32P3_V23B&t;0x01
DECL|macro|PV32P4_48
mdefine_line|#define PV32P4_48&t;0x11
DECL|macro|PV32P5_48
mdefine_line|#define PV32P5_48&t;0x05
DECL|macro|PV32P4_UT48
mdefine_line|#define PV32P4_UT48&t;0x11
DECL|macro|PV32P5_UT48
mdefine_line|#define PV32P5_UT48&t;0x0d
DECL|macro|PV32P4_96
mdefine_line|#define PV32P4_96&t;0x11
DECL|macro|PV32P5_96
mdefine_line|#define PV32P5_96&t;0x03
DECL|macro|PV32P4_UT96
mdefine_line|#define PV32P4_UT96&t;0x11
DECL|macro|PV32P5_UT96
mdefine_line|#define PV32P5_UT96&t;0x0f
DECL|macro|PV32P4_B96
mdefine_line|#define PV32P4_B96&t;0x91
DECL|macro|PV32P5_B96
mdefine_line|#define PV32P5_B96&t;0x0b
DECL|macro|PV32P4_UTB96
mdefine_line|#define PV32P4_UTB96&t;0xd1
DECL|macro|PV32P5_UTB96
mdefine_line|#define PV32P5_UTB96&t;0x0f
DECL|macro|PV32P4_120
mdefine_line|#define PV32P4_120&t;0xb1
DECL|macro|PV32P5_120
mdefine_line|#define PV32P5_120&t;0x09
DECL|macro|PV32P4_UT120
mdefine_line|#define PV32P4_UT120&t;0xf1
DECL|macro|PV32P5_UT120
mdefine_line|#define PV32P5_UT120&t;0x0f
DECL|macro|PV32P4_144
mdefine_line|#define PV32P4_144&t;0x99
DECL|macro|PV32P5_144
mdefine_line|#define PV32P5_144&t;0x09
DECL|macro|PV32P4_UT144
mdefine_line|#define PV32P4_UT144&t;0xf9
DECL|macro|PV32P5_UT144
mdefine_line|#define PV32P5_UT144&t;0x0f
DECL|macro|PV32P6_CTN
mdefine_line|#define PV32P6_CTN&t;0x01
DECL|macro|PV32P6_ATN
mdefine_line|#define PV32P6_ATN&t;0x02
DECL|macro|PFAXP2_CTN
mdefine_line|#define PFAXP2_CTN&t;0x01
DECL|macro|PFAXP2_ATN
mdefine_line|#define PFAXP2_ATN&t;0x04
DECL|macro|PSEV_10MS_TIMER
mdefine_line|#define PSEV_10MS_TIMER&t;0x02
DECL|macro|PSEV_CON_ON
mdefine_line|#define PSEV_CON_ON&t;0x18
DECL|macro|PSEV_CON_OFF
mdefine_line|#define PSEV_CON_OFF&t;0x19
DECL|macro|PSEV_V24_OFF
mdefine_line|#define PSEV_V24_OFF&t;0x20
DECL|macro|PSEV_CTS_ON
mdefine_line|#define PSEV_CTS_ON&t;0x21
DECL|macro|PSEV_CTS_OFF
mdefine_line|#define PSEV_CTS_OFF&t;0x22
DECL|macro|PSEV_DCD_ON
mdefine_line|#define PSEV_DCD_ON&t;0x23
DECL|macro|PSEV_DCD_OFF
mdefine_line|#define PSEV_DCD_OFF&t;0x24
DECL|macro|PSEV_DSR_ON
mdefine_line|#define PSEV_DSR_ON&t;0x25
DECL|macro|PSEV_DSR_OFF
mdefine_line|#define PSEV_DSR_OFF&t;0x26
DECL|macro|PSEV_REM_RET
mdefine_line|#define PSEV_REM_RET&t;0xcc
DECL|macro|PSEV_REM_REN
mdefine_line|#define PSEV_REM_REN&t;0xcd
DECL|macro|PSEV_GSTN_CLR
mdefine_line|#define PSEV_GSTN_CLR&t;0xd4
DECL|macro|PSEV_RSP_READY
mdefine_line|#define PSEV_RSP_READY&t;0xbc
DECL|macro|PSEV_LINE_TX_H
mdefine_line|#define PSEV_LINE_TX_H&t;0xb3
DECL|macro|PSEV_LINE_TX_B
mdefine_line|#define PSEV_LINE_TX_B&t;0xb2
DECL|macro|PSEV_LINE_RX_H
mdefine_line|#define PSEV_LINE_RX_H&t;0xb1
DECL|macro|PSEV_LINE_RX_B
mdefine_line|#define PSEV_LINE_RX_B&t;0xb0
DECL|macro|PSEV_RSP_CONN
mdefine_line|#define PSEV_RSP_CONN&t;0xb5
DECL|macro|PSEV_RSP_DISC
mdefine_line|#define PSEV_RSP_DISC&t;0xb7
DECL|macro|PSEV_RSP_FCERR
mdefine_line|#define PSEV_RSP_FCERR&t;0xb9
DECL|macro|PSEV_RSP_SILDET
mdefine_line|#define PSEV_RSP_SILDET&t;0xbe
DECL|macro|PSEV_RSP_SILOFF
mdefine_line|#define PSEV_RSP_SILOFF&t;0xab
DECL|macro|PSEV_FLAGS_DET
mdefine_line|#define PSEV_FLAGS_DET&t;0xba
DECL|macro|PCTRL_CMD_FTH
mdefine_line|#define PCTRL_CMD_FTH&t;0xa7
DECL|macro|PCTRL_CMD_FRH
mdefine_line|#define PCTRL_CMD_FRH&t;0xa5
DECL|macro|PCTRL_CMD_FTM
mdefine_line|#define PCTRL_CMD_FTM&t;0xa8
DECL|macro|PCTRL_CMD_FRM
mdefine_line|#define PCTRL_CMD_FRM&t;0xa6
DECL|macro|PCTRL_CMD_SILON
mdefine_line|#define PCTRL_CMD_SILON&t;0xac
DECL|macro|PCTRL_CMD_CONT
mdefine_line|#define PCTRL_CMD_CONT&t;0xa2
DECL|macro|PCTRL_CMD_ESC
mdefine_line|#define PCTRL_CMD_ESC&t;0xa4
DECL|macro|PCTRL_CMD_SILOFF
mdefine_line|#define PCTRL_CMD_SILOFF 0xab
DECL|macro|PCTRL_CMD_HALT
mdefine_line|#define PCTRL_CMD_HALT&t;0xa9
DECL|macro|PCTRL_LOC_RET
mdefine_line|#define PCTRL_LOC_RET&t;0xcf
DECL|macro|PCTRL_LOC_REN
mdefine_line|#define PCTRL_LOC_REN&t;0xce
DECL|macro|SMODE_DISABLE
mdefine_line|#define SMODE_DISABLE&t;0
DECL|macro|SMODE_V14
mdefine_line|#define SMODE_V14&t;2
DECL|macro|SMODE_HDLC
mdefine_line|#define SMODE_HDLC&t;3
DECL|macro|SMODE_BINARY
mdefine_line|#define SMODE_BINARY&t;4
DECL|macro|SMODE_FSK_V14
mdefine_line|#define SMODE_FSK_V14&t;5
DECL|macro|SCTRL_HDMC_BOTH
mdefine_line|#define SCTRL_HDMC_BOTH&t;0x00
DECL|macro|SCTRL_HDMC_DTX
mdefine_line|#define SCTRL_HDMC_DTX&t;0x80
DECL|macro|SCTRL_HDMC_DRX
mdefine_line|#define SCTRL_HDMC_DRX&t;0x40
DECL|macro|S_P1_OVSP
mdefine_line|#define S_P1_OVSP&t;0x40
DECL|macro|S_P1_SNP
mdefine_line|#define S_P1_SNP&t;0x20
DECL|macro|S_P1_EOP
mdefine_line|#define S_P1_EOP&t;0x10
DECL|macro|S_P1_EDP
mdefine_line|#define S_P1_EDP&t;0x08
DECL|macro|S_P1_NSB
mdefine_line|#define S_P1_NSB&t;0x04
DECL|macro|S_P1_CHS_8
mdefine_line|#define S_P1_CHS_8&t;0x03
DECL|macro|S_P1_CHS_7
mdefine_line|#define S_P1_CHS_7&t;0x02
DECL|macro|S_P1_CHS_6
mdefine_line|#define S_P1_CHS_6&t;0x01
DECL|macro|S_P1_CHS_5
mdefine_line|#define S_P1_CHS_5&t;0x00
DECL|macro|S_P2_BFT_DEF
mdefine_line|#define S_P2_BFT_DEF&t;0x10
DECL|macro|IOM_CTRL_ENA
mdefine_line|#define IOM_CTRL_ENA&t;0x80
DECL|macro|IOM_CTRL_NOPCM
mdefine_line|#define IOM_CTRL_NOPCM&t;0x00
DECL|macro|IOM_CTRL_ALAW
mdefine_line|#define IOM_CTRL_ALAW&t;0x02
DECL|macro|IOM_CTRL_ULAW
mdefine_line|#define IOM_CTRL_ULAW&t;0x04
DECL|macro|IOM_CTRL_RCV
mdefine_line|#define IOM_CTRL_RCV&t;0x01
DECL|macro|IOM_P1_TXD
mdefine_line|#define IOM_P1_TXD&t;0x10
DECL|macro|HDLC_FED
mdefine_line|#define HDLC_FED&t;0x40
DECL|macro|HDLC_FSD
mdefine_line|#define HDLC_FSD&t;0x20
DECL|macro|HDLC_FST
mdefine_line|#define HDLC_FST&t;0x20
DECL|macro|HDLC_ERROR
mdefine_line|#define HDLC_ERROR&t;0x1c
DECL|macro|HDLC_ERR_FAD
mdefine_line|#define HDLC_ERR_FAD&t;0x10
DECL|macro|HDLC_ERR_RER
mdefine_line|#define HDLC_ERR_RER&t;0x08
DECL|macro|HDLC_ERR_CER
mdefine_line|#define HDLC_ERR_CER&t;0x04
DECL|macro|SART_NMD
mdefine_line|#define SART_NMD&t;0x01
DECL|macro|BSTAT_RDM0
mdefine_line|#define BSTAT_RDM0&t;0x1
DECL|macro|BSTAT_RDM1
mdefine_line|#define BSTAT_RDM1&t;0x2
DECL|macro|BSTAT_RDM2
mdefine_line|#define BSTAT_RDM2&t;0x4
DECL|macro|BSTAT_RDM3
mdefine_line|#define BSTAT_RDM3&t;0x8
DECL|macro|BSTEV_TBO
mdefine_line|#define BSTEV_TBO&t;0x1f
DECL|macro|BSTEV_RBO
mdefine_line|#define BSTEV_RBO&t;0x2f
multiline_comment|/* FAX State Machine */
DECL|macro|STFAX_NULL
mdefine_line|#define STFAX_NULL&t;0
DECL|macro|STFAX_READY
mdefine_line|#define STFAX_READY&t;1
DECL|macro|STFAX_LINE
mdefine_line|#define STFAX_LINE&t;2
DECL|macro|STFAX_CONT
mdefine_line|#define STFAX_CONT&t;3
DECL|macro|STFAX_ACTIV
mdefine_line|#define STFAX_ACTIV&t;4
DECL|macro|STFAX_ESCAPE
mdefine_line|#define STFAX_ESCAPE&t;5
DECL|macro|STFAX_SILDET
mdefine_line|#define STFAX_SILDET&t;6
r_extern
r_int
id|ISARVersion
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_char
op_star
id|s
)paren
suffix:semicolon
r_extern
r_void
id|isar_int_main
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
r_extern
r_void
id|initisar
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
suffix:semicolon
r_extern
r_void
id|isar_fill_fifo
c_func
(paren
r_struct
id|BCState
op_star
id|bcs
)paren
suffix:semicolon
r_extern
r_int
id|isar_auxcmd
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|isdn_ctrl
op_star
id|ic
)paren
suffix:semicolon
eof
