multiline_comment|/* drivers/atm/uPD98402.h - NEC uPD98402 (PHY) declarations */
multiline_comment|/* Written 1995 by Werner Almesberger, EPFL LRC */
macro_line|#ifndef DRIVERS_ATM_uPD98402_H
DECL|macro|DRIVERS_ATM_uPD98402_H
mdefine_line|#define DRIVERS_ATM_uPD98402_H
multiline_comment|/*&n; * Registers&n; */
DECL|macro|uPD98402_CMR
mdefine_line|#define uPD98402_CMR&t;&t;0x00&t;/* Command Register */
DECL|macro|uPD98402_MDR
mdefine_line|#define uPD98402_MDR&t;&t;0x01&t;/* Mode Register */
DECL|macro|uPD98402_PICR
mdefine_line|#define uPD98402_PICR&t;&t;0x02&t;/* PHY Interrupt Cause Register */
DECL|macro|uPD98402_PIMR
mdefine_line|#define uPD98402_PIMR&t;&t;0x03&t;/* PHY Interrupt Mask Register */
DECL|macro|uPD98402_ACR
mdefine_line|#define uPD98402_ACR&t;&t;0x04&t;/* Alarm Cause Register */
DECL|macro|uPD98402_ACMR
mdefine_line|#define uPD98402_ACMR&t;&t;0x05&t;/* Alarm Cause Mask Register */
DECL|macro|uPD98402_PCR
mdefine_line|#define uPD98402_PCR&t;&t;0x06&t;/* Performance Cause Register */
DECL|macro|uPD98402_PCMR
mdefine_line|#define uPD98402_PCMR&t;&t;0x07&t;/* Performance Cause Mask Register */
DECL|macro|uPD98402_IACM
mdefine_line|#define uPD98402_IACM&t;&t;0x08&t;/* Internal Alarm Cause Mask Register */
DECL|macro|uPD98402_B1ECT
mdefine_line|#define uPD98402_B1ECT&t;&t;0x09&t;/* B1 Error Count Register */
DECL|macro|uPD98402_B2ECT
mdefine_line|#define uPD98402_B2ECT&t;&t;0x0a&t;/* B2 Error Count Register */
DECL|macro|uPD98402_B3ECT
mdefine_line|#define uPD98402_B3ECT&t;&t;0x0b&t;/* B3 Error Count Regster */
DECL|macro|uPD98402_PFECB
mdefine_line|#define uPD98402_PFECB&t;&t;0x0c&t;/* Path FEBE Count Register */
DECL|macro|uPD98402_LECCT
mdefine_line|#define uPD98402_LECCT&t;&t;0x0d&t;/* Line FEBE Count Register */
DECL|macro|uPD98402_HECCT
mdefine_line|#define uPD98402_HECCT&t;&t;0x0e&t;/* HEC Error Count Register */
DECL|macro|uPD98402_FJCT
mdefine_line|#define uPD98402_FJCT&t;&t;0x0f&t;/* Frequence Justification Count Reg */
DECL|macro|uPD98402_PCOCR
mdefine_line|#define uPD98402_PCOCR&t;&t;0x10&t;/* Perf. Counter Overflow Cause Reg */
DECL|macro|uPD98402_PCOMR
mdefine_line|#define uPD98402_PCOMR&t;&t;0x11&t;/* Perf. Counter Overflow Mask Reg */
DECL|macro|uPD98402_C11T
mdefine_line|#define uPD98402_C11T&t;&t;0x20&t;/* C11T Data Register */
DECL|macro|uPD98402_C12T
mdefine_line|#define uPD98402_C12T&t;&t;0x21&t;/* C12T Data Register */
DECL|macro|uPD98402_C13T
mdefine_line|#define uPD98402_C13T&t;&t;0x22&t;/* C13T Data Register */
DECL|macro|uPD98402_F1T
mdefine_line|#define uPD98402_F1T&t;&t;0x23&t;/* F1T Data Register */
DECL|macro|uPD98402_K2T
mdefine_line|#define uPD98402_K2T&t;&t;0x25&t;/* K2T Data Register */
DECL|macro|uPD98402_C2T
mdefine_line|#define uPD98402_C2T&t;&t;0x26&t;/* C2T Data Register */
DECL|macro|uPD98402_F2T
mdefine_line|#define uPD98402_F2T&t;&t;0x27&t;/* F2T Data Register */
DECL|macro|uPD98402_C11R
mdefine_line|#define uPD98402_C11R&t;&t;0x30&t;/* C11T Data Register */
DECL|macro|uPD98402_C12R
mdefine_line|#define uPD98402_C12R&t;&t;0x31&t;/* C12T Data Register */
DECL|macro|uPD98402_C13R
mdefine_line|#define uPD98402_C13R&t;&t;0x32&t;/* C13T Data Register */
DECL|macro|uPD98402_F1R
mdefine_line|#define uPD98402_F1R&t;&t;0x33&t;/* F1T Data Register */
DECL|macro|uPD98402_K2R
mdefine_line|#define uPD98402_K2R&t;&t;0x35&t;/* K2T Data Register */
DECL|macro|uPD98402_C2R
mdefine_line|#define uPD98402_C2R&t;&t;0x36&t;/* C2T Data Register */
DECL|macro|uPD98402_F2R
mdefine_line|#define uPD98402_F2R&t;&t;0x37&t;/* F2T Data Register */
multiline_comment|/* CMR is at 0x00 */
DECL|macro|uPD98402_CMR_PFRF
mdefine_line|#define uPD98402_CMR_PFRF&t;0x01&t;/* Send path FERF */
DECL|macro|uPD98402_CMR_LFRF
mdefine_line|#define uPD98402_CMR_LFRF&t;0x02&t;/* Send line FERF */
DECL|macro|uPD98402_CMR_PAIS
mdefine_line|#define uPD98402_CMR_PAIS&t;0x04&t;/* Send path AIS */
DECL|macro|uPD98402_CMR_LAIS
mdefine_line|#define uPD98402_CMR_LAIS&t;0x08&t;/* Send line AIS */
multiline_comment|/* MDR is at 0x01 */
DECL|macro|uPD98402_MDR_ALP
mdefine_line|#define uPD98402_MDR_ALP&t;0x01&t;/* ATM layer loopback */
DECL|macro|uPD98402_MDR_TPLP
mdefine_line|#define uPD98402_MDR_TPLP&t;0x02&t;/* PMD loopback, to host */
DECL|macro|uPD98402_MDR_RPLP
mdefine_line|#define uPD98402_MDR_RPLP&t;0x04&t;/* PMD loopback, to network */
DECL|macro|uPD98402_MDR_SS0
mdefine_line|#define uPD98402_MDR_SS0&t;0x08&t;/* SS0 */
DECL|macro|uPD98402_MDR_SS1
mdefine_line|#define uPD98402_MDR_SS1&t;0x10&t;/* SS1 */
DECL|macro|uPD98402_MDR_SS_MASK
mdefine_line|#define uPD98402_MDR_SS_MASK&t;0x18&t;/* mask */
DECL|macro|uPD98402_MDR_SS_SHIFT
mdefine_line|#define uPD98402_MDR_SS_SHIFT&t;3&t;/* shift */
DECL|macro|uPD98402_MDR_HEC
mdefine_line|#define uPD98402_MDR_HEC&t;0x20&t;/* disable HEC inbound processing */
DECL|macro|uPD98402_MDR_FSR
mdefine_line|#define uPD98402_MDR_FSR&t;0x40&t;/* disable frame scrambler */
DECL|macro|uPD98402_MDR_CSR
mdefine_line|#define uPD98402_MDR_CSR&t;0x80&t;/* disable cell scrambler */
multiline_comment|/* PICR is at 0x02, PIMR is at 0x03 */
DECL|macro|uPD98402_INT_PFM
mdefine_line|#define uPD98402_INT_PFM&t;0x01&t;/* performance counter has changed */
DECL|macro|uPD98402_INT_ALM
mdefine_line|#define uPD98402_INT_ALM&t;0x02&t;/* line fault */
DECL|macro|uPD98402_INT_RFO
mdefine_line|#define uPD98402_INT_RFO&t;0x04&t;/* receive FIFO overflow */
DECL|macro|uPD98402_INT_PCO
mdefine_line|#define uPD98402_INT_PCO&t;0x08&t;/* performance counter overflow */
DECL|macro|uPD98402_INT_OTD
mdefine_line|#define uPD98402_INT_OTD&t;0x20&t;/* OTD has occurred */
DECL|macro|uPD98402_INT_LOS
mdefine_line|#define uPD98402_INT_LOS&t;0x40&t;/* Loss Of Signal */
DECL|macro|uPD98402_INT_LOF
mdefine_line|#define uPD98402_INT_LOF&t;0x80&t;/* Loss Of Frame */
multiline_comment|/* ACR is as 0x04, ACMR is at 0x05 */
DECL|macro|uPD98402_ALM_PFRF
mdefine_line|#define uPD98402_ALM_PFRF&t;0x01&t;/* path FERF */
DECL|macro|uPD98402_ALM_LFRF
mdefine_line|#define uPD98402_ALM_LFRF&t;0x02&t;/* line FERF */
DECL|macro|uPD98402_ALM_PAIS
mdefine_line|#define uPD98402_ALM_PAIS&t;0x04&t;/* path AIS */
DECL|macro|uPD98402_ALM_LAIS
mdefine_line|#define uPD98402_ALM_LAIS&t;0x08&t;/* line AIS */
DECL|macro|uPD98402_ALM_LOD
mdefine_line|#define uPD98402_ALM_LOD&t;0x10&t;/* loss of delineation */
DECL|macro|uPD98402_ALM_LOP
mdefine_line|#define uPD98402_ALM_LOP&t;0x20&t;/* loss of pointer */
DECL|macro|uPD98402_ALM_OOF
mdefine_line|#define uPD98402_ALM_OOF&t;0x40&t;/* out of frame */
multiline_comment|/* PCR is at 0x06, PCMR is at 0x07 */
DECL|macro|uPD98402_PFM_PFEB
mdefine_line|#define uPD98402_PFM_PFEB&t;0x01&t;/* path FEBE */
DECL|macro|uPD98402_PFM_LFEB
mdefine_line|#define uPD98402_PFM_LFEB&t;0x02&t;/* line FEBE */
DECL|macro|uPD98402_PFM_B3E
mdefine_line|#define uPD98402_PFM_B3E&t;0x04&t;/* B3 error */
DECL|macro|uPD98402_PFM_B2E
mdefine_line|#define uPD98402_PFM_B2E&t;0x08&t;/* B2 error */
DECL|macro|uPD98402_PFM_B1E
mdefine_line|#define uPD98402_PFM_B1E&t;0x10&t;/* B1 error */
DECL|macro|uPD98402_PFM_FJ
mdefine_line|#define uPD98402_PFM_FJ&t;&t;0x20&t;/* frequency justification */
multiline_comment|/* IACM is at 0x08 */
DECL|macro|uPD98402_IACM_PFRF
mdefine_line|#define uPD98402_IACM_PFRF&t;0x01&t;/* don&squot;t generate path FERF */
DECL|macro|uPD98402_IACM_LFRF
mdefine_line|#define uPD98402_IACM_LFRF&t;0x02&t;/* don&squot;t generate line FERF */
multiline_comment|/* PCOCR is at 0x010, PCOMR is at 0x11 */
DECL|macro|uPD98402_PCO_B1EC
mdefine_line|#define uPD98402_PCO_B1EC&t;0x01&t;/* B1ECT overflow */
DECL|macro|uPD98402_PCO_B2EC
mdefine_line|#define uPD98402_PCO_B2EC&t;0x02&t;/* B2ECT overflow */
DECL|macro|uPD98402_PCO_B3EC
mdefine_line|#define uPD98402_PCO_B3EC&t;0x04&t;/* B3ECT overflow */
DECL|macro|uPD98402_PCO_PFBC
mdefine_line|#define uPD98402_PCO_PFBC&t;0x08&t;/* PFEBC overflow */
DECL|macro|uPD98402_PCO_LFBC
mdefine_line|#define uPD98402_PCO_LFBC&t;0x10&t;/* LFEVC overflow */
DECL|macro|uPD98402_PCO_HECC
mdefine_line|#define uPD98402_PCO_HECC&t;0x20&t;/* HECCT overflow */
DECL|macro|uPD98402_PCO_FJC
mdefine_line|#define uPD98402_PCO_FJC&t;0x40&t;/* FJCT overflow */
r_int
id|uPD98402_init
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif
eof
