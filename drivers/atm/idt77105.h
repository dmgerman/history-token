multiline_comment|/* drivers/atm/idt77105.h - IDT77105 (PHY) declarations */
multiline_comment|/* Written 1999 by Greg Banks, NEC Australia &lt;gnb@linuxfan.com&gt;. Based on suni.h */
macro_line|#ifndef DRIVER_ATM_IDT77105_H
DECL|macro|DRIVER_ATM_IDT77105_H
mdefine_line|#define DRIVER_ATM_IDT77105_H
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/atmioc.h&gt;
multiline_comment|/* IDT77105 registers */
DECL|macro|IDT77105_MCR
mdefine_line|#define IDT77105_MCR&t;&t;0x0&t;/* Master Control Register */
DECL|macro|IDT77105_ISTAT
mdefine_line|#define IDT77105_ISTAT&t;        0x1&t;/* Interrupt Status */
DECL|macro|IDT77105_DIAG
mdefine_line|#define IDT77105_DIAG   &t;0x2&t;/* Diagnostic Control */
DECL|macro|IDT77105_LEDHEC
mdefine_line|#define IDT77105_LEDHEC&t;&t;0x3&t;/* LED Driver &amp; HEC Status/Control */
DECL|macro|IDT77105_CTRLO
mdefine_line|#define IDT77105_CTRLO&t;&t;0x4&t;/* Low Byte Counter Register */
DECL|macro|IDT77105_CTRHI
mdefine_line|#define IDT77105_CTRHI&t;&t;0x5&t;/* High Byte Counter Register */
DECL|macro|IDT77105_CTRSEL
mdefine_line|#define IDT77105_CTRSEL&t;&t;0x6&t;/* Counter Register Read Select */
multiline_comment|/* IDT77105 register values */
multiline_comment|/* MCR */
DECL|macro|IDT77105_MCR_UPLO
mdefine_line|#define IDT77105_MCR_UPLO&t;0x80&t;/* R/W, User Prog&squot;le Output Latch */
DECL|macro|IDT77105_MCR_DREC
mdefine_line|#define IDT77105_MCR_DREC&t;0x40&t;/* R/W, Discard Receive Error Cells */
DECL|macro|IDT77105_MCR_ECEIO
mdefine_line|#define IDT77105_MCR_ECEIO&t;0x20&t;/* R/W, Enable Cell Error Interrupts&n;                                         * Only */
DECL|macro|IDT77105_MCR_TDPC
mdefine_line|#define IDT77105_MCR_TDPC&t;0x10&t;/* R/W, Transmit Data Parity Check */
DECL|macro|IDT77105_MCR_DRIC
mdefine_line|#define IDT77105_MCR_DRIC&t;0x08&t;/* R/W, Discard Received Idle Cells */
DECL|macro|IDT77105_MCR_HALTTX
mdefine_line|#define IDT77105_MCR_HALTTX&t;0x04&t;/* R/W, Halt Tx */
DECL|macro|IDT77105_MCR_UMODE
mdefine_line|#define IDT77105_MCR_UMODE&t;0x02&t;/* R/W, Utopia (cell/byte) Mode */
DECL|macro|IDT77105_MCR_EIP
mdefine_line|#define IDT77105_MCR_EIP&t;0x01&t;/* R/W, Enable Interrupt Pin */
multiline_comment|/* ISTAT */
DECL|macro|IDT77105_ISTAT_GOODSIG
mdefine_line|#define IDT77105_ISTAT_GOODSIG&t;0x40&t;/* R, Good Signal Bit */
DECL|macro|IDT77105_ISTAT_HECERR
mdefine_line|#define IDT77105_ISTAT_HECERR&t;0x20&t;/* sticky, HEC Error*/
DECL|macro|IDT77105_ISTAT_SCR
mdefine_line|#define IDT77105_ISTAT_SCR&t;0x10&t;/* sticky, Short Cell Received */
DECL|macro|IDT77105_ISTAT_TPE
mdefine_line|#define IDT77105_ISTAT_TPE&t;0x08&t;/* sticky, Transmit Parity Error */
DECL|macro|IDT77105_ISTAT_RSCC
mdefine_line|#define IDT77105_ISTAT_RSCC&t;0x04&t;/* sticky, Rx Signal Condition Change */
DECL|macro|IDT77105_ISTAT_RSE
mdefine_line|#define IDT77105_ISTAT_RSE&t;0x02&t;/* sticky, Rx Symbol Error */
DECL|macro|IDT77105_ISTAT_RFO
mdefine_line|#define IDT77105_ISTAT_RFO&t;0x01&t;/* sticky, Rx FIFO Overrun */
multiline_comment|/* DIAG */
DECL|macro|IDT77105_DIAG_FTD
mdefine_line|#define IDT77105_DIAG_FTD&t;0x80&t;/* R/W, Force TxClav deassert */
DECL|macro|IDT77105_DIAG_ROS
mdefine_line|#define IDT77105_DIAG_ROS&t;0x40&t;/* R/W, RxClav operation select */
DECL|macro|IDT77105_DIAG_MPCS
mdefine_line|#define IDT77105_DIAG_MPCS&t;0x20&t;/* R/W, Multi-PHY config&squot;n select */
DECL|macro|IDT77105_DIAG_RFLUSH
mdefine_line|#define IDT77105_DIAG_RFLUSH&t;0x10&t;/* R/W, clear receive FIFO */
DECL|macro|IDT77105_DIAG_ITPE
mdefine_line|#define IDT77105_DIAG_ITPE&t;0x08&t;/* R/W, Insert Tx payload error */
DECL|macro|IDT77105_DIAG_ITHE
mdefine_line|#define IDT77105_DIAG_ITHE&t;0x04&t;/* R/W, Insert Tx HEC error */
DECL|macro|IDT77105_DIAG_UMODE
mdefine_line|#define IDT77105_DIAG_UMODE&t;0x02&t;/* R/W, Utopia (cell/byte) Mode */
DECL|macro|IDT77105_DIAG_LCMASK
mdefine_line|#define IDT77105_DIAG_LCMASK&t;0x03&t;/* R/W, Loopback Control */
DECL|macro|IDT77105_DIAG_LC_NORMAL
mdefine_line|#define IDT77105_DIAG_LC_NORMAL         0x00&t;/* Receive from network */
DECL|macro|IDT77105_DIAG_LC_PHY_LOOPBACK
mdefine_line|#define IDT77105_DIAG_LC_PHY_LOOPBACK&t;0x02
DECL|macro|IDT77105_DIAG_LC_LINE_LOOPBACK
mdefine_line|#define IDT77105_DIAG_LC_LINE_LOOPBACK&t;0x03
multiline_comment|/* LEDHEC */
DECL|macro|IDT77105_LEDHEC_DRHC
mdefine_line|#define IDT77105_LEDHEC_DRHC&t;0x40&t;/* R/W, Disable Rx HEC check */
DECL|macro|IDT77105_LEDHEC_DTHC
mdefine_line|#define IDT77105_LEDHEC_DTHC&t;0x20&t;/* R/W, Disable Tx HEC calculation */
DECL|macro|IDT77105_LEDHEC_RPWMASK
mdefine_line|#define IDT77105_LEDHEC_RPWMASK&t;0x18&t;/* R/W, RxRef pulse width select */
DECL|macro|IDT77105_LEDHEC_TFS
mdefine_line|#define IDT77105_LEDHEC_TFS&t;0x04&t;/* R, Tx FIFO Status (1=empty) */
DECL|macro|IDT77105_LEDHEC_TLS
mdefine_line|#define IDT77105_LEDHEC_TLS&t;0x02&t;/* R, Tx LED Status (1=lit) */
DECL|macro|IDT77105_LEDHEC_RLS
mdefine_line|#define IDT77105_LEDHEC_RLS&t;0x01&t;/* R, Rx LED Status (1=lit) */
DECL|macro|IDT77105_LEDHEC_RPW_1
mdefine_line|#define IDT77105_LEDHEC_RPW_1&t;0x00&t;/* RxRef active for 1 RxClk cycle */
DECL|macro|IDT77105_LEDHEC_RPW_2
mdefine_line|#define IDT77105_LEDHEC_RPW_2&t;0x08&t;/* RxRef active for 2 RxClk cycle */
DECL|macro|IDT77105_LEDHEC_RPW_4
mdefine_line|#define IDT77105_LEDHEC_RPW_4&t;0x10&t;/* RxRef active for 4 RxClk cycle */
DECL|macro|IDT77105_LEDHEC_RPW_8
mdefine_line|#define IDT77105_LEDHEC_RPW_8&t;0x18&t;/* RxRef active for 8 RxClk cycle */
multiline_comment|/* CTRSEL */
DECL|macro|IDT77105_CTRSEL_SEC
mdefine_line|#define IDT77105_CTRSEL_SEC&t;0x08&t;/* W, Symbol Error Counter */
DECL|macro|IDT77105_CTRSEL_TCC
mdefine_line|#define IDT77105_CTRSEL_TCC&t;0x04&t;/* W, Tx Cell Counter */
DECL|macro|IDT77105_CTRSEL_RCC
mdefine_line|#define IDT77105_CTRSEL_RCC&t;0x02&t;/* W, Rx Cell Counter */
DECL|macro|IDT77105_CTRSEL_RHEC
mdefine_line|#define IDT77105_CTRSEL_RHEC&t;0x01&t;/* W, Rx HEC Error Counter */
macro_line|#ifdef __KERNEL__
r_int
id|idt77105_init
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
id|__init
suffix:semicolon
r_int
id|idt77105_stop
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Tunable parameters&n; */
multiline_comment|/* Time between samples of the hardware cell counters. Should be &lt;= 1 sec */
DECL|macro|IDT77105_STATS_TIMER_PERIOD
mdefine_line|#define IDT77105_STATS_TIMER_PERIOD     (HZ) 
multiline_comment|/* Time between checks to see if the signal has been found again */
DECL|macro|IDT77105_RESTART_TIMER_PERIOD
mdefine_line|#define IDT77105_RESTART_TIMER_PERIOD   (5 * HZ)
macro_line|#endif
eof
