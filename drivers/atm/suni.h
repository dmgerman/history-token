multiline_comment|/* drivers/atm/suni.h - PMC PM5346 SUNI (PHY) declarations */
multiline_comment|/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef DRIVER_ATM_SUNI_H
DECL|macro|DRIVER_ATM_SUNI_H
mdefine_line|#define DRIVER_ATM_SUNI_H
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/atmioc.h&gt;
multiline_comment|/* SUNI registers */
DECL|macro|SUNI_MRI
mdefine_line|#define SUNI_MRI&t;&t;0x00&t;/* Master Reset and Identity / Load&n;&t;&t;&t;&t;&t;   Meter */
DECL|macro|SUNI_MC
mdefine_line|#define SUNI_MC&t;&t;&t;0x01&t;/* Master Configuration */
DECL|macro|SUNI_MIS
mdefine_line|#define SUNI_MIS&t;&t;0x02&t;/* Master Interrupt Status */
multiline_comment|/* no 0x03 */
DECL|macro|SUNI_MCM
mdefine_line|#define SUNI_MCM&t;&t;0x04&t;/* Master Clock Monitor */
DECL|macro|SUNI_MCT
mdefine_line|#define SUNI_MCT&t;&t;0x05&t;/* Master Control */
DECL|macro|SUNI_CSCS
mdefine_line|#define SUNI_CSCS&t;&t;0x06&t;/* Clock Synthesis Control and Status */
DECL|macro|SUNI_CRCS
mdefine_line|#define SUNI_CRCS&t;&t;0x07&t;/* Clock Recovery Control and Status */
multiline_comment|/* 0x08-0x0F reserved */
DECL|macro|SUNI_RSOP_CIE
mdefine_line|#define SUNI_RSOP_CIE&t;&t;0x10&t;/* RSOP Control/Interrupt Enable */
DECL|macro|SUNI_RSOP_SIS
mdefine_line|#define SUNI_RSOP_SIS&t;&t;0x11&t;/* RSOP Status/Interrupt Status */
DECL|macro|SUNI_RSOP_SBL
mdefine_line|#define SUNI_RSOP_SBL&t;&t;0x12&t;/* RSOP Section BIP-8 LSB */
DECL|macro|SUNI_RSOP_SBM
mdefine_line|#define SUNI_RSOP_SBM&t;&t;0x13&t;/* RSOP Section BIP-8 MSB */
DECL|macro|SUNI_TSOP_CTRL
mdefine_line|#define SUNI_TSOP_CTRL&t;&t;0x14&t;/* TSOP Control */
DECL|macro|SUNI_TSOP_DIAG
mdefine_line|#define SUNI_TSOP_DIAG&t;&t;0x15&t;/* TSOP Diagnostic */
multiline_comment|/* 0x16-0x17 reserved */
DECL|macro|SUNI_RLOP_CS
mdefine_line|#define SUNI_RLOP_CS&t;&t;0x18&t;/* RLOP Control/Status */
DECL|macro|SUNI_RLOP_IES
mdefine_line|#define SUNI_RLOP_IES&t;&t;0x19&t;/* RLOP Interrupt Enable/Status */
DECL|macro|SUNI_RLOP_LBL
mdefine_line|#define SUNI_RLOP_LBL&t;&t;0x1A&t;/* RLOP Line BIP-8/24 LSB */
DECL|macro|SUNI_RLOP_LB
mdefine_line|#define SUNI_RLOP_LB&t;&t;0x1B&t;/* RLOP Line BIP-8/24 */
DECL|macro|SUNI_RLOP_LBM
mdefine_line|#define SUNI_RLOP_LBM&t;&t;0x1C&t;/* RLOP Line BIP-8/24 MSB */
DECL|macro|SUNI_RLOP_LFL
mdefine_line|#define SUNI_RLOP_LFL&t;&t;0x1D&t;/* RLOP Line FEBE LSB */
DECL|macro|SUNI_RLOP_LF
mdefine_line|#define SUNI_RLOP_LF &t;&t;0x1E&t;/* RLOP Line FEBE */
DECL|macro|SUNI_RLOP_LFM
mdefine_line|#define SUNI_RLOP_LFM&t;&t;0x1F&t;/* RLOP Line FEBE MSB */
DECL|macro|SUNI_TLOP_CTRL
mdefine_line|#define SUNI_TLOP_CTRL&t;&t;0x20&t;/* TLOP Control */
DECL|macro|SUNI_TLOP_DIAG
mdefine_line|#define SUNI_TLOP_DIAG&t;&t;0x21&t;/* TLOP Diagnostic */
multiline_comment|/* 0x22-0x2F reserved */
DECL|macro|SUNI_RPOP_SC
mdefine_line|#define SUNI_RPOP_SC&t;&t;0x30&t;/* RPOP Status/Control */
DECL|macro|SUNI_RPOP_IS
mdefine_line|#define SUNI_RPOP_IS&t;&t;0x31&t;/* RPOP Interrupt Status */
multiline_comment|/* 0x32 reserved */
DECL|macro|SUNI_RPOP_IE
mdefine_line|#define SUNI_RPOP_IE&t;&t;0x33&t;/* RPOP Interrupt Enable */
multiline_comment|/* 0x34-0x36 reserved */
DECL|macro|SUNI_RPOP_PSL
mdefine_line|#define SUNI_RPOP_PSL&t;&t;0x37&t;/* RPOP Path Signal Label */
DECL|macro|SUNI_RPOP_PBL
mdefine_line|#define SUNI_RPOP_PBL&t;&t;0x38&t;/* RPOP Path BIP-8 LSB */
DECL|macro|SUNI_RPOP_PBM
mdefine_line|#define SUNI_RPOP_PBM&t;&t;0x39&t;/* RPOP Path BIP-8 MSB */
DECL|macro|SUNI_RPOP_PFL
mdefine_line|#define SUNI_RPOP_PFL&t;&t;0x3A&t;/* RPOP Path FEBE LSB */
DECL|macro|SUNI_RPOP_PFM
mdefine_line|#define SUNI_RPOP_PFM&t;&t;0x3B&t;/* RPOP Path FEBE MSB */
multiline_comment|/* 0x3C reserved */
DECL|macro|SUNI_RPOP_PBC
mdefine_line|#define SUNI_RPOP_PBC&t;&t;0x3D&t;/* RPOP Path BIP-8 Configuration */
multiline_comment|/* 0x3E-0x3F reserved */
DECL|macro|SUNI_TPOP_CD
mdefine_line|#define SUNI_TPOP_CD&t;&t;0x40&t;/* TPOP Control/Diagnostic */
DECL|macro|SUNI_TPOP_PC
mdefine_line|#define SUNI_TPOP_PC&t;&t;0x41&t;/* TPOP Pointer Control */
multiline_comment|/* 0x42-0x44 reserved */
DECL|macro|SUNI_TPOP_APL
mdefine_line|#define SUNI_TPOP_APL&t;&t;0x45&t;/* TPOP Arbitrary Pointer LSB */
DECL|macro|SUNI_TPOP_APM
mdefine_line|#define SUNI_TPOP_APM&t;&t;0x46&t;/* TPOP Arbitrary Pointer MSB */
multiline_comment|/* 0x47 reserved */
DECL|macro|SUNI_TPOP_PSL
mdefine_line|#define SUNI_TPOP_PSL&t;&t;0x48&t;/* TPOP Path Signal Label */
DECL|macro|SUNI_TPOP_PS
mdefine_line|#define SUNI_TPOP_PS&t;&t;0x49&t;/* TPOP Path Status */
multiline_comment|/* 0x4A-0x4F reserved */
DECL|macro|SUNI_RACP_CS
mdefine_line|#define SUNI_RACP_CS&t;&t;0x50&t;/* RACP Control/Status */
DECL|macro|SUNI_RACP_IES
mdefine_line|#define SUNI_RACP_IES&t;&t;0x51&t;/* RACP Interrupt Enable/Status */
DECL|macro|SUNI_RACP_MHP
mdefine_line|#define SUNI_RACP_MHP&t;&t;0x52&t;/* RACP Match Header Pattern */
DECL|macro|SUNI_RACP_MHM
mdefine_line|#define SUNI_RACP_MHM&t;&t;0x53&t;/* RACP Match Header Mask */
DECL|macro|SUNI_RACP_CHEC
mdefine_line|#define SUNI_RACP_CHEC&t;&t;0x54&t;/* RACP Correctable HCS Error Count */
DECL|macro|SUNI_RACP_UHEC
mdefine_line|#define SUNI_RACP_UHEC&t;&t;0x55&t;/* RACP Uncorrectable HCS Err Count */
DECL|macro|SUNI_RACP_RCCL
mdefine_line|#define SUNI_RACP_RCCL&t;&t;0x56&t;/* RACP Receive Cell Counter LSB */
DECL|macro|SUNI_RACP_RCC
mdefine_line|#define SUNI_RACP_RCC&t;&t;0x57&t;/* RACP Receive Cell Counter */
DECL|macro|SUNI_RACP_RCCM
mdefine_line|#define SUNI_RACP_RCCM&t;&t;0x58&t;/* RACP Receive Cell Counter MSB */
DECL|macro|SUNI_RACP_CFG
mdefine_line|#define SUNI_RACP_CFG&t;&t;0x59&t;/* RACP Configuration */
multiline_comment|/* 0x5A-0x5F reserved */
DECL|macro|SUNI_TACP_CS
mdefine_line|#define SUNI_TACP_CS&t;&t;0x60&t;/* TACP Control/Status */
DECL|macro|SUNI_TACP_IUCHP
mdefine_line|#define SUNI_TACP_IUCHP&t;&t;0x61&t;/* TACP Idle/Unassigned Cell Hdr Pat */
DECL|macro|SUNI_TACP_IUCPOP
mdefine_line|#define SUNI_TACP_IUCPOP&t;0x62&t;/* TACP Idle/Unassigned Cell Payload&n;&t;&t;&t;&t;&t;   Octet Pattern */
DECL|macro|SUNI_TACP_FIFO
mdefine_line|#define SUNI_TACP_FIFO&t;&t;0x63&t;/* TACP FIFO Configuration */
DECL|macro|SUNI_TACP_TCCL
mdefine_line|#define SUNI_TACP_TCCL&t;&t;0x64&t;/* TACP Transmit Cell Counter LSB */
DECL|macro|SUNI_TACP_TCC
mdefine_line|#define SUNI_TACP_TCC&t;&t;0x65&t;/* TACP Transmit Cell Counter */
DECL|macro|SUNI_TACP_TCCM
mdefine_line|#define SUNI_TACP_TCCM&t;&t;0x66&t;/* TACP Transmit Cell Counter MSB */
DECL|macro|SUNI_TACP_CFG
mdefine_line|#define SUNI_TACP_CFG&t;&t;0x67&t;/* TACP Configuration */
multiline_comment|/* 0x68-0x7F reserved */
DECL|macro|SUNI_MT
mdefine_line|#define&t;SUNI_MT&t;&t;&t;0x80&t;/* Master Test */
multiline_comment|/* 0x81-0xFF reserved */
multiline_comment|/* SUNI register values */
multiline_comment|/* MRI is reg 0 */
DECL|macro|SUNI_MRI_ID
mdefine_line|#define SUNI_MRI_ID&t;&t;0x0f&t;/* R, SUNI revision number */
DECL|macro|SUNI_MRI_ID_SHIFT
mdefine_line|#define SUNI_MRI_ID_SHIFT &t;0
DECL|macro|SUNI_MRI_TYPE
mdefine_line|#define SUNI_MRI_TYPE&t;&t;0x70&t;/* R, SUNI type (lite is 011) */
DECL|macro|SUNI_MRI_TYPE_SHIFT
mdefine_line|#define SUNI_MRI_TYPE_SHIFT &t;4
DECL|macro|SUNI_MRI_RESET
mdefine_line|#define SUNI_MRI_RESET&t;&t;0x80&t;/* RW, reset &amp; power down chip&n;&t;&t;&t;&t;&t;   0: normal operation&n;&t;&t;&t;&t;&t;   1: reset &amp; low power */
multiline_comment|/* MCT is reg 5 */
DECL|macro|SUNI_MCT_LOOPT
mdefine_line|#define SUNI_MCT_LOOPT&t;&t;0x01&t;/* RW, timing source, 0: from&n;&t;&t;&t;&t;&t;   TRCLK+/- */
DECL|macro|SUNI_MCT_DLE
mdefine_line|#define SUNI_MCT_DLE&t;&t;0x02&t;/* RW, diagnostic loopback */
DECL|macro|SUNI_MCT_LLE
mdefine_line|#define SUNI_MCT_LLE&t;&t;0x04&t;/* RW, line loopback */
DECL|macro|SUNI_MCT_FIXPTR
mdefine_line|#define SUNI_MCT_FIXPTR&t;&t;0x20&t;/* RW, disable transmit payload pointer&n;&t;&t;&t;&t;&t;   adjustments&n;&t;&t;&t;&t;&t;   0: payload ptr controlled by TPOP&n;&t;&t;&t;&t;&t;      ptr control reg&n;&t;&t;&t;&t;&t;   1: payload pointer fixed at 522 */
DECL|macro|SUNI_MCT_LCDV
mdefine_line|#define SUNI_MCT_LCDV&t;&t;0x40&t;/* R, loss of cell delineation */
DECL|macro|SUNI_MCT_LCDE
mdefine_line|#define SUNI_MCT_LCDE&t;&t;0x80&t;/* RW, loss of cell delineation&n;&t;&t;&t;&t;&t;   interrupt (1: on) */
multiline_comment|/* RSOP_CIE is reg 0x10 */
DECL|macro|SUNI_RSOP_CIE_OOFE
mdefine_line|#define SUNI_RSOP_CIE_OOFE&t;0x01&t;/* RW, enable interrupt on frame alarm&n;&t;&t;&t;&t;&t;   state change */
DECL|macro|SUNI_RSOP_CIE_LOFE
mdefine_line|#define SUNI_RSOP_CIE_LOFE&t;0x02&t;/* RW, enable interrupt on loss of&n;&t;&t;&t;&t;&t;   frame state change */
DECL|macro|SUNI_RSOP_CIE_LOSE
mdefine_line|#define SUNI_RSOP_CIE_LOSE&t;0x04&t;/* RW, enable interrupt on loss of&n;&t;&t;&t;&t;&t;   signal state change */
DECL|macro|SUNI_RSOP_CIE_BIPEE
mdefine_line|#define SUNI_RSOP_CIE_BIPEE&t;0x08&t;/* RW, enable interrupt on section&n;&t;&t;&t;&t;&t;   BIP-8 error (B1) */
DECL|macro|SUNI_RSOP_CIE_FOOF
mdefine_line|#define SUNI_RSOP_CIE_FOOF&t;0x20&t;/* W, force RSOP out of frame at next&n;&t;&t;&t;&t;&t;   boundary */
DECL|macro|SUNI_RSOP_CIE_DDS
mdefine_line|#define SUNI_RSOP_CIE_DDS&t;0x40&t;/* RW, disable scrambling */
multiline_comment|/* RSOP_SIS is reg 0x11 */
DECL|macro|SUNI_RSOP_SIS_OOFV
mdefine_line|#define SUNI_RSOP_SIS_OOFV&t;0x01&t;/* R, out of frame */
DECL|macro|SUNI_RSOP_SIS_LOFV
mdefine_line|#define SUNI_RSOP_SIS_LOFV&t;0x02&t;/* R, loss of frame */
DECL|macro|SUNI_RSOP_SIS_LOSV
mdefine_line|#define SUNI_RSOP_SIS_LOSV&t;0x04&t;/* R, loss of signal */
DECL|macro|SUNI_RSOP_SIS_OOFI
mdefine_line|#define SUNI_RSOP_SIS_OOFI&t;0x08&t;/* R, out of frame interrupt */
DECL|macro|SUNI_RSOP_SIS_LOFI
mdefine_line|#define SUNI_RSOP_SIS_LOFI&t;0x10&t;/* R, loss of frame interrupt */
DECL|macro|SUNI_RSOP_SIS_LOSI
mdefine_line|#define SUNI_RSOP_SIS_LOSI&t;0x20&t;/* R, loss of signal interrupt */
DECL|macro|SUNI_RSOP_SIS_BIPEI
mdefine_line|#define SUNI_RSOP_SIS_BIPEI&t;0x40&t;/* R, section BIP-8 interrupt */
multiline_comment|/* TSOP_CTRL is reg 0x14 */
DECL|macro|SUNI_TSOP_CTRL_LAIS
mdefine_line|#define SUNI_TSOP_CTRL_LAIS&t;0x01&t;/* insert alarm indication signal */
DECL|macro|SUNI_TSOP_CTRL_DS
mdefine_line|#define SUNI_TSOP_CTRL_DS&t;0x40&t;/* disable scrambling */
multiline_comment|/* TSOP_DIAG is reg 0x15 */
DECL|macro|SUNI_TSOP_DIAG_DFP
mdefine_line|#define SUNI_TSOP_DIAG_DFP&t;0x01&t;/* insert single bit error cont. */
DECL|macro|SUNI_TSOP_DIAG_DBIP8
mdefine_line|#define SUNI_TSOP_DIAG_DBIP8&t;0x02&t;/* insert section BIP err (cont) */
DECL|macro|SUNI_TSOP_DIAG_DLOS
mdefine_line|#define SUNI_TSOP_DIAG_DLOS&t;0x04&t;/* set line to zero (loss of signal) */
multiline_comment|/* TLOP_DIAG is reg 0x21 */
DECL|macro|SUNI_TLOP_DIAG_DBIP
mdefine_line|#define SUNI_TLOP_DIAG_DBIP&t;0x01&t;/* insert line BIP err (continuously) */
multiline_comment|/* TPOP_DIAG is reg 0x40 */
DECL|macro|SUNI_TPOP_DIAG_PAIS
mdefine_line|#define SUNI_TPOP_DIAG_PAIS&t;0x01&t;/* insert STS path alarm ind (cont) */
DECL|macro|SUNI_TPOP_DIAG_DB3
mdefine_line|#define SUNI_TPOP_DIAG_DB3&t;0x02&t;/* insert path BIP err (continuously) */
multiline_comment|/* TPOP_APM is reg 0x46 */
DECL|macro|SUNI_TPOP_APM_APTR
mdefine_line|#define SUNI_TPOP_APM_APTR&t;0x03&t;/* RW, arbitrary pointer, upper 2&n;&t;&t;&t;&t;&t;   bits */
DECL|macro|SUNI_TPOP_APM_APTR_SHIFT
mdefine_line|#define SUNI_TPOP_APM_APTR_SHIFT 0
DECL|macro|SUNI_TPOP_APM_S
mdefine_line|#define SUNI_TPOP_APM_S&t;&t;0x0c&t;/* RW, &quot;unused&quot; bits of payload&n;&t;&t;&t;&t;&t;   pointer */
DECL|macro|SUNI_TPOP_APM_S_SHIFT
mdefine_line|#define SUNI_TPOP_APM_S_SHIFT&t;2
DECL|macro|SUNI_TPOP_APM_NDF
mdefine_line|#define SUNI_TPOP_APM_NDF&t;0xf0&t; /* RW, NDF bits */
DECL|macro|SUNI_TPOP_APM_NDF_SHIFT
mdefine_line|#define SUNI_TPOP_APM_NDF_SHIFT&t;4
DECL|macro|SUNI_TPOP_S_SONET
mdefine_line|#define SUNI_TPOP_S_SONET&t;0&t;/* set S bits to 00 */
DECL|macro|SUNI_TPOP_S_SDH
mdefine_line|#define SUNI_TPOP_S_SDH&t;&t;2&t;/* set S bits to 10 */
multiline_comment|/* RACP_IES is reg 0x51 */
DECL|macro|SUNI_RACP_IES_FOVRI
mdefine_line|#define SUNI_RACP_IES_FOVRI&t;0x02&t;/* R, FIFO overrun */
DECL|macro|SUNI_RACP_IES_UHCSI
mdefine_line|#define SUNI_RACP_IES_UHCSI&t;0x04&t;/* R, uncorrectable HCS error */
DECL|macro|SUNI_RACP_IES_CHCSI
mdefine_line|#define SUNI_RACP_IES_CHCSI&t;0x08&t;/* R, correctable HCS error */
DECL|macro|SUNI_RACP_IES_OOCDI
mdefine_line|#define SUNI_RACP_IES_OOCDI&t;0x10&t;/* R, change of cell delineation&n;&t;&t;&t;&t;&t;   state */
DECL|macro|SUNI_RACP_IES_FIFOE
mdefine_line|#define SUNI_RACP_IES_FIFOE&t;0x20&t;/* RW, enable FIFO overrun interrupt */
DECL|macro|SUNI_RACP_IES_HCSE
mdefine_line|#define SUNI_RACP_IES_HCSE&t;0x40&t;/* RW, enable HCS error interrupt */
DECL|macro|SUNI_RACP_IES_OOCDE
mdefine_line|#define SUNI_RACP_IES_OOCDE&t;0x80&t;/* RW, enable cell delineation state&n;&t;&t;&t;&t;&t;   change interrupt */
multiline_comment|/* TACP_CS is reg 0x60 */
DECL|macro|SUNI_TACP_CS_FIFORST
mdefine_line|#define SUNI_TACP_CS_FIFORST&t;0x01&t;/* RW, reset transmit FIFO (sticky) */
DECL|macro|SUNI_TACP_CS_DSCR
mdefine_line|#define SUNI_TACP_CS_DSCR&t;0x02&t;/* RW, disable payload scrambling */
DECL|macro|SUNI_TACP_CS_HCAADD
mdefine_line|#define SUNI_TACP_CS_HCAADD&t;0x04&t;/* RW, add coset polynomial to HCS */
DECL|macro|SUNI_TACP_CS_DHCS
mdefine_line|#define SUNI_TACP_CS_DHCS&t;0x10&t;/* RW, insert HCS errors */
DECL|macro|SUNI_TACP_CS_FOVRI
mdefine_line|#define SUNI_TACP_CS_FOVRI&t;0x20&t;/* R, FIFO overrun */
DECL|macro|SUNI_TACP_CS_TSOCI
mdefine_line|#define SUNI_TACP_CS_TSOCI&t;0x40&t;/* R, TSOC input high */
DECL|macro|SUNI_TACP_CS_FIFOE
mdefine_line|#define SUNI_TACP_CS_FIFOE&t;0x80&t;/* RW, enable FIFO overrun interrupt */
multiline_comment|/* TACP_IUCHP is reg 0x61 */
DECL|macro|SUNI_TACP_IUCHP_CLP
mdefine_line|#define SUNI_TACP_IUCHP_CLP&t;0x01&t;/* RW, 8th bit of 4th octet of i/u&n;&t;&t;&t;&t;&t;   pattern */
DECL|macro|SUNI_TACP_IUCHP_PTI
mdefine_line|#define SUNI_TACP_IUCHP_PTI&t;0x0e&t;/* RW, 5th-7th bits of 4th octet of i/u&n;&t;&t;&t;&t;&t;   pattern */
DECL|macro|SUNI_TACP_IUCHP_PTI_SHIFT
mdefine_line|#define SUNI_TACP_IUCHP_PTI_SHIFT 1
DECL|macro|SUNI_TACP_IUCHP_GFC
mdefine_line|#define SUNI_TACP_IUCHP_GFC&t;0xf0&t;/* RW, 1st-4th bits of 1st octet of i/u&n;&t;&t;&t;&t;&t;   pattern */
DECL|macro|SUNI_TACP_IUCHP_GFC_SHIFT
mdefine_line|#define SUNI_TACP_IUCHP_GFC_SHIFT 4
multiline_comment|/* MT is reg 0x80 */
DECL|macro|SUNI_MT_HIZIO
mdefine_line|#define SUNI_MT_HIZIO&t;&t;0x01&t;/* RW, all but data bus &amp; MP interface&n;&t;&t;&t;&t;&t;   tri-state */
DECL|macro|SUNI_MT_HIZDATA
mdefine_line|#define SUNI_MT_HIZDATA&t;&t;0x02&t;/* W, also tri-state data bus */
DECL|macro|SUNI_MT_IOTST
mdefine_line|#define SUNI_MT_IOTST&t;&t;0x04&t;/* RW, enable test mode */
DECL|macro|SUNI_MT_DBCTRL
mdefine_line|#define SUNI_MT_DBCTRL&t;&t;0x08&t;/* W, control data bus by CSB pin */
DECL|macro|SUNI_MT_PMCTST
mdefine_line|#define SUNI_MT_PMCTST&t;&t;0x10&t;/* W, PMC test mode */
DECL|macro|SUNI_IDLE_PATTERN
mdefine_line|#define SUNI_IDLE_PATTERN       0x6a    /* idle pattern */
macro_line|#ifdef __KERNEL__
r_int
id|suni_init
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
