multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******&t;&t;CIRRUS.H&t;&t;&t;&t;      *******&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Jeremy Rolls&n; Date    : 3 Aug 1990&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef _cirrus_h
macro_line|#ifndef lint
multiline_comment|/* static char* _cirrus_h_sccs = &quot;@(#)cirrus.h&t;1.16&quot;; */
macro_line|#endif
DECL|macro|_cirrus_h
mdefine_line|#define _cirrus_h 1
macro_line|#ifdef RTA
DECL|macro|TO_UART
mdefine_line|#define&t;TO_UART&t;RX
DECL|macro|TO_DRIVER
mdefine_line|#define TO_DRIVER TX
macro_line|#endif
macro_line|#ifdef HOST
DECL|macro|TO_UART
mdefine_line|#define&t;TO_UART&t;TX
DECL|macro|TO_DRIVER
mdefine_line|#define TO_DRIVER RX
macro_line|#endif
macro_line|#ifdef RTA
multiline_comment|/* Miscellaneous defines for CIRRUS addresses and related logic for&n;   interrupts etc.&n;*/
DECL|macro|MAP
mdefine_line|#define&t;MAP(a)&t;&t;((short *)(cirrus_base + (a)))
DECL|macro|outp
mdefine_line|#define outp(a,b)&t;(*MAP (a) =(b))
DECL|macro|inp
mdefine_line|#define inp(a)&t;&t;((*MAP (a)) &amp; 0xff)
DECL|macro|CIRRUS_FIRST
mdefine_line|#define&t;CIRRUS_FIRST&t;(short*)0x7300
DECL|macro|CIRRUS_SECOND
mdefine_line|#define&t;CIRRUS_SECOND&t;(short*)0x7200
DECL|macro|CIRRUS_THIRD
mdefine_line|#define&t;CIRRUS_THIRD&t;(short*)0x7100
DECL|macro|CIRRUS_FOURTH
mdefine_line|#define&t;CIRRUS_FOURTH&t;(short*)0x7000
DECL|macro|PORTS_ON_CIRRUS
mdefine_line|#define&t;PORTS_ON_CIRRUS&t;4
DECL|macro|CIRRUS_FIFO_SIZE
mdefine_line|#define&t;CIRRUS_FIFO_SIZE&t;12
DECL|macro|SPACE
mdefine_line|#define&t;SPACE&t;&t;0x20
DECL|macro|TAB
mdefine_line|#define&t;TAB&t;&t;0x09
DECL|macro|LINE_FEED
mdefine_line|#define&t;LINE_FEED&t;0x0a
DECL|macro|CARRIAGE_RETURN
mdefine_line|#define&t;CARRIAGE_RETURN&t;0x0d
DECL|macro|BACKSPACE
mdefine_line|#define&t;BACKSPACE&t;0x08
DECL|macro|SPACES_IN_TABS
mdefine_line|#define&t;SPACES_IN_TABS&t;8
DECL|macro|SEND_ESCAPE
mdefine_line|#define&t;SEND_ESCAPE&t;0x00
DECL|macro|START_BREAK
mdefine_line|#define START_BREAK&t;0x81
DECL|macro|TIMER_TICK
mdefine_line|#define&t;TIMER_TICK&t;0x82
DECL|macro|STOP_BREAK
mdefine_line|#define STOP_BREAK&t;0x83
DECL|macro|BASE
mdefine_line|#define BASE(a) ((a) &lt; 4 ? (short*)CIRRUS_FIRST : ((a) &lt; 8 ? (short *)CIRRUS_SECOND : ((a) &lt; 12 ? (short*)CIRRUS_THIRD : (short *)CIRRUS_FOURTH)))
DECL|macro|txack1
mdefine_line|#define txack1&t;((short *)0x7104) 
DECL|macro|rxack1
mdefine_line|#define rxack1&t;((short *)0x7102) 
DECL|macro|mdack1
mdefine_line|#define mdack1  ((short *)0x7106)
DECL|macro|txack2
mdefine_line|#define txack2  ((short *)0x7006) 
DECL|macro|rxack2
mdefine_line|#define rxack2&t;((short *)0x7004) 
DECL|macro|mdack2
mdefine_line|#define mdack2  ((short *)0x7100) 
DECL|macro|int_latch
mdefine_line|#define int_latch       ((short *) 0x7800)
DECL|macro|int_status
mdefine_line|#define int_status      ((short *) 0x7c00) 
DECL|macro|tx1_pending
mdefine_line|#define tx1_pending     0x20 
DECL|macro|rx1_pending
mdefine_line|#define rx1_pending     0x10 
DECL|macro|md1_pending
mdefine_line|#define md1_pending     0x40 
DECL|macro|tx2_pending
mdefine_line|#define tx2_pending     0x02 
DECL|macro|rx2_pending
mdefine_line|#define rx2_pending     0x01 
DECL|macro|md2_pending
mdefine_line|#define md2_pending     0x40 
DECL|macro|module1_bits
mdefine_line|#define module1_bits&t;0x07
DECL|macro|module1_modern
mdefine_line|#define module1_modern&t;0x08
DECL|macro|module2_bits
mdefine_line|#define module2_bits&t;0x70
DECL|macro|module2_modern
mdefine_line|#define module2_modern&t;0x80
DECL|macro|module_blank
mdefine_line|#define module_blank&t;0xf
DECL|macro|rs232_d25
mdefine_line|#define rs232_d25&t;0x0
DECL|macro|rs232_rj45
mdefine_line|#define&t;rs232_rj45&t;0x1
DECL|macro|rs422_d25
mdefine_line|#define rs422_d25&t;0x3
DECL|macro|parallel
mdefine_line|#define parallel&t;0x5
DECL|macro|CLK0
mdefine_line|#define&t;CLK0&t;0x00
DECL|macro|CLK1
mdefine_line|#define CLK1&t;0x01
DECL|macro|CLK2
mdefine_line|#define CLK2&t;0x02
DECL|macro|CLK3
mdefine_line|#define CLK3&t;0x03
DECL|macro|CLK4
mdefine_line|#define CLK4&t;0x04
DECL|macro|CIRRUS_REVC
mdefine_line|#define CIRRUS_REVC    0x42
DECL|macro|CIRRUS_REVE
mdefine_line|#define CIRRUS_REVE    0x44
DECL|macro|TURNON
mdefine_line|#define&t;TURNON&t;1
DECL|macro|TURNOFF
mdefine_line|#define TURNOFF 0
multiline_comment|/* The list of CIRRUS registers. &n;   NB. These registers are relative values on 8 bit boundaries whereas&n;   on the RTA&squot;s the CIRRUS registers are on word boundaries. Use pointer&n;   arithmetic (short *) to obtain the real addresses required */
DECL|macro|ccr
mdefine_line|#define ccr&t;0x05&t;/* Channel Command Register     */
DECL|macro|ier
mdefine_line|#define ier&t;0x06&t;/* Interrupt Enable Register    */
DECL|macro|cor1
mdefine_line|#define cor1&t;0x08&t;/* Channel Option Register 1    */
DECL|macro|cor2
mdefine_line|#define cor2&t;0x09&t;/* Channel Option Register 2    */
DECL|macro|cor3
mdefine_line|#define cor3&t;0x0a&t;/* Channel Option Register 3    */
DECL|macro|cor4
mdefine_line|#define cor4&t;0x1e&t;/* Channel Option Register 4    */
DECL|macro|cor5
mdefine_line|#define&t;cor5&t;0x1f&t;/* Channel Option Register 5&t;*/
DECL|macro|ccsr
mdefine_line|#define ccsr&t;0x0b&t;/* Channel Control Status Register */
DECL|macro|rdcr
mdefine_line|#define rdcr&t;0x0e&t;/* Receive Data Count Register  */
DECL|macro|tdcr
mdefine_line|#define tdcr&t;0x12&t;/* Transmit Data Count Register */
DECL|macro|mcor1
mdefine_line|#define mcor1&t;0x15&t;/* Modem Change Option Register 1 */
DECL|macro|mcor2
mdefine_line|#define mcor2&t;0x16&t;/* Modem Change Option Regsiter 2 */
DECL|macro|livr
mdefine_line|#define livr&t;0x18&t;/* Local Interrupt Vector Register */
DECL|macro|schr1
mdefine_line|#define schr1&t;0x1a&t;/* Special Character Register 1 */
DECL|macro|schr2
mdefine_line|#define schr2&t;0x1b&t;/* Special Character Register 2 */
DECL|macro|schr3
mdefine_line|#define schr3&t;0x1c&t;/* Special Character Register 3 */
DECL|macro|schr4
mdefine_line|#define schr4&t;0x1d&t;/* Special Character Register 4 */
DECL|macro|rtr
mdefine_line|#define rtr&t;0x20    /* Receive Timer Register */
DECL|macro|rtpr
mdefine_line|#define rtpr&t;0x21&t;/* Receive Timeout Period Register */
DECL|macro|lnc
mdefine_line|#define lnc&t;0x24&t;/* Lnext character */
DECL|macro|rivr
mdefine_line|#define rivr&t;0x43&t;/* Receive Interrupt Vector Register    */
DECL|macro|tivr
mdefine_line|#define tivr&t;0x42&t;/* Transmit Interrupt Vector Register   */
DECL|macro|mivr
mdefine_line|#define mivr&t;0x41&t;/* Modem Interrupt Vector Register      */
DECL|macro|gfrcr
mdefine_line|#define gfrcr&t;0x40&t;/* Global Firmware Revision code Reg    */
DECL|macro|ricr
mdefine_line|#define ricr&t;0x44&t;/* Receive Interrupting Channel Reg     */
DECL|macro|ticr
mdefine_line|#define ticr&t;0x45&t;/* Transmit Interrupting Channel Reg    */
DECL|macro|micr
mdefine_line|#define micr&t;0x46&t;/* Modem Interrupting Channel Register  */
DECL|macro|gcr
mdefine_line|#define gcr&t;0x4b&t;/* Global configuration register*/
DECL|macro|misr
mdefine_line|#define misr    0x4c    /* Modem interrupt status register */
DECL|macro|rbusr
mdefine_line|#define rbusr&t;0x59
DECL|macro|tbusr
mdefine_line|#define tbusr&t;0x5a
DECL|macro|mbusr
mdefine_line|#define mbusr&t;0x5b
DECL|macro|eoir
mdefine_line|#define eoir&t;0x60&t;/* End Of Interrupt Register */
DECL|macro|rdsr
mdefine_line|#define rdsr&t;0x62&t;/* Receive Data / Status Register */
DECL|macro|tdr
mdefine_line|#define tdr&t;0x63&t;/* Transmit Data Register */
DECL|macro|svrr
mdefine_line|#define svrr&t;0x67&t;/* Service Request Register */
DECL|macro|car
mdefine_line|#define car&t;0x68&t;/* Channel Access Register */
DECL|macro|mir
mdefine_line|#define mir&t;0x69&t;/* Modem Interrupt Register */
DECL|macro|tir
mdefine_line|#define tir&t;0x6a&t;/* Transmit Interrupt Register */
DECL|macro|rir
mdefine_line|#define rir&t;0x6b&t;/* Receive Interrupt Register */
DECL|macro|msvr1
mdefine_line|#define msvr1&t;0x6c&t;/* Modem Signal Value Register 1 */
DECL|macro|msvr2
mdefine_line|#define msvr2&t;0x6d&t;/* Modem Signal Value Register 2*/
DECL|macro|psvr
mdefine_line|#define psvr&t;0x6f&t;/* Printer Signal Value Register*/
DECL|macro|tbpr
mdefine_line|#define tbpr&t;0x72&t;/* Transmit Baud Rate Period Register */
DECL|macro|tcor
mdefine_line|#define tcor&t;0x76&t;/* Transmit Clock Option Register */
DECL|macro|rbpr
mdefine_line|#define rbpr&t;0x78&t;/* Receive Baud Rate Period Register */
DECL|macro|rber
mdefine_line|#define rber&t;0x7a&t;/* Receive Baud Rate Extension Register */
DECL|macro|rcor
mdefine_line|#define rcor&t;0x7c&t;/* Receive Clock Option Register*/
DECL|macro|ppr
mdefine_line|#define ppr&t;0x7e&t;/* Prescalar Period Register    */
multiline_comment|/* Misc registers used for forcing the 1400 out of its reset woes */
DECL|macro|airl
mdefine_line|#define airl&t;0x6d
DECL|macro|airm
mdefine_line|#define airm&t;0x6e
DECL|macro|airh
mdefine_line|#define airh&t;0x6f
DECL|macro|btcr
mdefine_line|#define btcr&t;0x66
DECL|macro|mtcr
mdefine_line|#define mtcr&t;0x6c
DECL|macro|tber
mdefine_line|#define tber&t;0x74
macro_line|#endif&t;&t;&t;&t;/* #ifdef RTA */
multiline_comment|/* Bit fields for particular registers */
multiline_comment|/* GCR */
DECL|macro|GCR_SERIAL
mdefine_line|#define GCR_SERIAL&t;0x00&t;/* Configure as serial channel */
DECL|macro|GCR_PARALLEL
mdefine_line|#define GCR_PARALLEL&t;0x80&t;/* Configure as parallel channel */
multiline_comment|/* RDSR - when status read from FIFO */
DECL|macro|RDSR_BREAK
mdefine_line|#define&t;RDSR_BREAK&t;&t;0x08&t;/* Break received */
DECL|macro|RDSR_TIMEOUT
mdefine_line|#define RDSR_TIMEOUT    &t;0x80    /* No new data timeout */
DECL|macro|RDSR_SC1
mdefine_line|#define RDSR_SC1  &t;  &t;0x10    /* Special char 1 (tx XON) matched */
DECL|macro|RDSR_SC2
mdefine_line|#define RDSR_SC2  &t;  &t;0x20    /* Special char 2 (tx XOFF) matched */
DECL|macro|RDSR_SC12_MASK
mdefine_line|#define RDSR_SC12_MASK&t;  &t;0x30    /* Mask for special chars 1 and 2 */
multiline_comment|/* PPR */
DECL|macro|PPR_DEFAULT
mdefine_line|#define PPR_DEFAULT&t;0x31&t;/* Default value - for a 25Mhz clock gives&n;&t;&t;&t;&t;   a timeout period of 1ms */
multiline_comment|/* LIVR */
DECL|macro|LIVR_EXCEPTION
mdefine_line|#define&t;LIVR_EXCEPTION&t;0x07&t;/* Receive exception interrupt */
multiline_comment|/* CCR */
DECL|macro|CCR_RESET
mdefine_line|#define&t;CCR_RESET&t;0x80&t;/* Reset channel */
DECL|macro|CCR_CHANGE
mdefine_line|#define&t;CCR_CHANGE&t;0x4e&t;/* COR&squot;s have changed - NB always change all&n;&t;&t;&t;&t;   COR&squot;s */
DECL|macro|CCR_WFLUSH
mdefine_line|#define&t;CCR_WFLUSH&t;0x82&t;/* Flush transmit FIFO and TSR / THR */
DECL|macro|CCR_SENDSC1
mdefine_line|#define&t;CCR_SENDSC1&t;0x21&t;/* Send special character one */
DECL|macro|CCR_SENDSC2
mdefine_line|#define CCR_SENDSC2&t;0x22&t;/* Send special character two */
DECL|macro|CCR_SENDSC3
mdefine_line|#define CCR_SENDSC3&t;0x23&t;/* Send special character three */
DECL|macro|CCR_SENDSC4
mdefine_line|#define CCR_SENDSC4&t;0x24&t;/* Send special character four */
DECL|macro|CCR_TENABLE
mdefine_line|#define CCR_TENABLE&t;0x18&t;/* Enable transmitter */
DECL|macro|CCR_TDISABLE
mdefine_line|#define&t;CCR_TDISABLE&t;0x14&t;/* Disable transmitter */
DECL|macro|CCR_RENABLE
mdefine_line|#define CCR_RENABLE&t;0x12&t;/* Enable receiver */
DECL|macro|CCR_RDISABLE
mdefine_line|#define CCR_RDISABLE&t;0x11&t;/* Disable receiver */
DECL|macro|CCR_READY
mdefine_line|#define&t;CCR_READY&t;0x00&t;/* CCR is ready for another command */
multiline_comment|/* CCSR */
DECL|macro|CCSR_TXENABLE
mdefine_line|#define CCSR_TXENABLE&t;0x08&t;/* Transmitter enable */
DECL|macro|CCSR_RXENABLE
mdefine_line|#define CCSR_RXENABLE&t;0x80&t;/* Receiver enable */
DECL|macro|CCSR_TXFLOWOFF
mdefine_line|#define CCSR_TXFLOWOFF&t;0x04&t;/* Transmit flow off */
DECL|macro|CCSR_TXFLOWON
mdefine_line|#define CCSR_TXFLOWON&t;0x02&t;/* Transmit flow on */
multiline_comment|/* SVRR */
DECL|macro|SVRR_RECEIVE
mdefine_line|#define&t;SVRR_RECEIVE&t;0x01&t;/* Receive interrupt pending */
DECL|macro|SVRR_TRANSMIT
mdefine_line|#define&t;SVRR_TRANSMIT&t;0x02&t;/* Transmit interrupt pending */
DECL|macro|SVRR_MODEM
mdefine_line|#define&t;SVRR_MODEM&t;0x04&t;/* Modem interrupt pending */
multiline_comment|/* CAR */
DECL|macro|CAR_PORTS
mdefine_line|#define CAR_PORTS&t;0x03&t;/* Bit fields for ports */
multiline_comment|/* IER */
DECL|macro|IER_MODEM
mdefine_line|#define&t;IER_MODEM&t;0x80&t;/* Change in modem status */
DECL|macro|IER_RECEIVE
mdefine_line|#define&t;IER_RECEIVE&t;0x10&t;/* Good data / data exception */
DECL|macro|IER_TRANSMITR
mdefine_line|#define IER_TRANSMITR&t;0x04&t;/* Transmit ready (FIFO empty) */
DECL|macro|IER_TRANSMITE
mdefine_line|#define&t;IER_TRANSMITE&t;0x02&t;/* Transmit empty */
DECL|macro|IER_TIMEOUT
mdefine_line|#define IER_TIMEOUT&t;0x01&t;/* Timeout on no data */
DECL|macro|IER_DEFAULT
mdefine_line|#define&t;IER_DEFAULT&t;0x94&t;/* Default values */
DECL|macro|IER_PARALLEL
mdefine_line|#define IER_PARALLEL    0x84    /* Default for Parallel */
DECL|macro|IER_EMPTY
mdefine_line|#define&t;IER_EMPTY&t;0x92&t;/* Transmitter empty rather than ready */
multiline_comment|/* COR1 - Driver only */
DECL|macro|COR1_INPCK
mdefine_line|#define&t;COR1_INPCK&t;0x10&t;/* Check parity of received characters */
multiline_comment|/* COR1 - driver and RTA */
DECL|macro|COR1_ODD
mdefine_line|#define&t;COR1_ODD&t;0x80&t;/* Odd parity */
DECL|macro|COR1_EVEN
mdefine_line|#define COR1_EVEN&t;0x00&t;/* Even parity */
DECL|macro|COR1_NOP
mdefine_line|#define&t;COR1_NOP&t;0x00&t;/* No parity */
DECL|macro|COR1_FORCE
mdefine_line|#define&t;COR1_FORCE&t;0x20&t;/* Force parity */
DECL|macro|COR1_NORMAL
mdefine_line|#define&t;COR1_NORMAL&t;0x40&t;/* With parity */
DECL|macro|COR1_1STOP
mdefine_line|#define&t;COR1_1STOP&t;0x00&t;/* 1 stop bit */
DECL|macro|COR1_15STOP
mdefine_line|#define&t;COR1_15STOP&t;0x04&t;/* 1.5 stop bits */
DECL|macro|COR1_2STOP
mdefine_line|#define&t;COR1_2STOP&t;0x08&t;/* 2 stop bits */
DECL|macro|COR1_5BITS
mdefine_line|#define&t;COR1_5BITS&t;0x00&t;/* 5 data bits */
DECL|macro|COR1_6BITS
mdefine_line|#define&t;COR1_6BITS&t;0x01&t;/* 6 data bits */
DECL|macro|COR1_7BITS
mdefine_line|#define&t;COR1_7BITS&t;0x02&t;/* 7 data bits */
DECL|macro|COR1_8BITS
mdefine_line|#define&t;COR1_8BITS&t;0x03&t;/* 8 data bits */
DECL|macro|COR1_HOST
mdefine_line|#define COR1_HOST       0xef    /* Safe host bits */
multiline_comment|/* RTA only */
DECL|macro|COR1_CINPCK
mdefine_line|#define COR1_CINPCK     0x00    /* Check parity of received characters */
DECL|macro|COR1_CNINPCK
mdefine_line|#define COR1_CNINPCK    0x10    /* Don&squot;t check parity */
multiline_comment|/* COR2 bits for both RTA and driver use */
DECL|macro|COR2_IXANY
mdefine_line|#define&t;COR2_IXANY&t;0x80&t;/* IXANY - any character is XON */
DECL|macro|COR2_IXON
mdefine_line|#define&t;COR2_IXON&t;0x40&t;/* IXON - enable tx soft flowcontrol */
DECL|macro|COR2_RTSFLOW
mdefine_line|#define&t;COR2_RTSFLOW&t;0x02&t;/* Enable tx hardware flow control */
multiline_comment|/* Additional driver bits */
DECL|macro|COR2_HUPCL
mdefine_line|#define&t;COR2_HUPCL&t;0x20&t;/* Hang up on close */
DECL|macro|COR2_CTSFLOW
mdefine_line|#define&t;COR2_CTSFLOW&t;0x04&t;/* Enable rx hardware flow control */
DECL|macro|COR2_IXOFF
mdefine_line|#define&t;COR2_IXOFF&t;0x01&t;/* Enable rx software flow control */
DECL|macro|COR2_DTRFLOW
mdefine_line|#define COR2_DTRFLOW&t;0x08&t;/* Enable tx hardware flow control */
multiline_comment|/* RTA use only */
DECL|macro|COR2_ETC
mdefine_line|#define COR2_ETC&t;0x20&t;/* Embedded transmit options */
DECL|macro|COR2_LOCAL
mdefine_line|#define&t;COR2_LOCAL&t;0x10&t;/* Local loopback mode */
DECL|macro|COR2_REMOTE
mdefine_line|#define&t;COR2_REMOTE&t;0x08&t;/* Remote loopback mode */
DECL|macro|COR2_HOST
mdefine_line|#define&t;COR2_HOST&t;0xc2&t;/* Safe host bits */
multiline_comment|/* COR3 - RTA use only */
DECL|macro|COR3_SCDRNG
mdefine_line|#define&t;COR3_SCDRNG&t;0x80&t;/* Enable special char detect for range */
DECL|macro|COR3_SCD34
mdefine_line|#define&t;COR3_SCD34&t;0x40&t;/* Special character detect for SCHR&squot;s 3 + 4 */
DECL|macro|COR3_FCT
mdefine_line|#define&t;COR3_FCT&t;0x20&t;/* Flow control transparency */
DECL|macro|COR3_SCD12
mdefine_line|#define&t;COR3_SCD12&t;0x10&t;/* Special character detect for SCHR&squot;s 1 + 2 */
DECL|macro|COR3_FIFO12
mdefine_line|#define&t;COR3_FIFO12&t;0x0c&t;/* 12 chars for receive FIFO threshold */
DECL|macro|COR3_FIFO10
mdefine_line|#define COR3_FIFO10     0x0a    /* 10 chars for receive FIFO threshold */
DECL|macro|COR3_FIFO8
mdefine_line|#define COR3_FIFO8      0x08    /* 8 chars for receive FIFO threshold */
DECL|macro|COR3_FIFO6
mdefine_line|#define COR3_FIFO6      0x06    /* 6 chars for receive FIFO threshold */
DECL|macro|COR3_THRESHOLD
mdefine_line|#define COR3_THRESHOLD  COR3_FIFO8&t;/* MUST BE LESS THAN MCOR_THRESHOLD */
DECL|macro|COR3_DEFAULT
mdefine_line|#define&t;COR3_DEFAULT&t;(COR3_FCT | COR3_THRESHOLD)
multiline_comment|/* Default bits for COR3 */
multiline_comment|/* COR4 driver and RTA use */
DECL|macro|COR4_IGNCR
mdefine_line|#define&t;COR4_IGNCR&t;0x80&t;/* Throw away CR&squot;s on input */
DECL|macro|COR4_ICRNL
mdefine_line|#define&t;COR4_ICRNL&t;0x40&t;/* Map CR -&gt; NL on input */
DECL|macro|COR4_INLCR
mdefine_line|#define&t;COR4_INLCR&t;0x20&t;/* Map NL -&gt; CR on input */
DECL|macro|COR4_IGNBRK
mdefine_line|#define&t;COR4_IGNBRK&t;0x10&t;/* Ignore Break */
DECL|macro|COR4_NBRKINT
mdefine_line|#define&t;COR4_NBRKINT&t;0x08&t;/* No interrupt on break (-BRKINT) */
DECL|macro|COR4_RAISEMOD
mdefine_line|#define COR4_RAISEMOD&t;0x01&t;/* Raise modem output lines on non-zero baud */
multiline_comment|/* COR4 driver only */
DECL|macro|COR4_IGNPAR
mdefine_line|#define COR4_IGNPAR&t;0x04&t;/* IGNPAR (ignore characters with errors) */
DECL|macro|COR4_PARMRK
mdefine_line|#define COR4_PARMRK&t;0x02&t;/* PARMRK */
DECL|macro|COR4_HOST
mdefine_line|#define COR4_HOST&t;0xf8&t;/* Safe host bits */
multiline_comment|/* COR4 RTA only */
DECL|macro|COR4_CIGNPAR
mdefine_line|#define COR4_CIGNPAR&t;0x02&t;/* Thrown away bad characters */
DECL|macro|COR4_CPARMRK
mdefine_line|#define COR4_CPARMRK&t;0x04&t;/* PARMRK characters */
DECL|macro|COR4_CNPARMRK
mdefine_line|#define COR4_CNPARMRK&t;0x03&t;/* Don&squot;t PARMRK */
multiline_comment|/* COR5 driver and RTA use */
DECL|macro|COR5_ISTRIP
mdefine_line|#define&t;COR5_ISTRIP&t;0x80&t;/* Strip input chars to 7 bits */
DECL|macro|COR5_LNE
mdefine_line|#define&t;COR5_LNE&t;0x40&t;/* Enable LNEXT processing */
DECL|macro|COR5_CMOE
mdefine_line|#define&t;COR5_CMOE&t;0x20&t;/* Match good and errored characters */
DECL|macro|COR5_ONLCR
mdefine_line|#define&t;COR5_ONLCR&t;0x02&t;/* NL -&gt; CR NL on output */
DECL|macro|COR5_OCRNL
mdefine_line|#define&t;COR5_OCRNL&t;0x01&t;/* CR -&gt; NL on output */
multiline_comment|/*&n;** Spare bits - these are not used in the CIRRUS registers, so we use&n;** them to set various other features.&n;*/
multiline_comment|/*&n;** tstop and tbusy indication&n;*/
DECL|macro|COR5_TSTATE_ON
mdefine_line|#define&t;COR5_TSTATE_ON&t;0x08&t;/* Turn on monitoring of tbusy and tstop */
DECL|macro|COR5_TSTATE_OFF
mdefine_line|#define&t;COR5_TSTATE_OFF&t;0x04&t;/* Turn off monitoring of tbusy and tstop */
multiline_comment|/*&n;** TAB3&n;*/
DECL|macro|COR5_TAB3
mdefine_line|#define&t;COR5_TAB3&t;0x10&t;/* TAB3 mode */
DECL|macro|COR5_HOST
mdefine_line|#define&t;COR5_HOST&t;0xc3&t;/* Safe host bits */
multiline_comment|/* CCSR */
DECL|macro|CCSR_TXFLOFF
mdefine_line|#define&t;CCSR_TXFLOFF&t;0x04&t;/* Tx is xoffed */
multiline_comment|/* MSVR1 */
multiline_comment|/* NB. DTR / CD swapped from Cirrus spec as the pins are also reversed on the&n;   RTA. This is because otherwise DCD would get lost on the 1 parallel / 3&n;   serial option.&n;*/
DECL|macro|MSVR1_CD
mdefine_line|#define&t;MSVR1_CD&t;0x80&t;/* CD (DSR on Cirrus) */
DECL|macro|MSVR1_RTS
mdefine_line|#define&t;MSVR1_RTS&t;0x40&t;/* RTS (CTS on Cirrus) */
DECL|macro|MSVR1_RI
mdefine_line|#define&t;MSVR1_RI&t;0x20&t;/* RI */
DECL|macro|MSVR1_DTR
mdefine_line|#define&t;MSVR1_DTR&t;0x10&t;/* DTR (CD on Cirrus) */
DECL|macro|MSVR1_CTS
mdefine_line|#define&t;MSVR1_CTS&t;0x01&t;/* CTS output pin (RTS on Cirrus) */
multiline_comment|/* Next two used to indicate state of tbusy and tstop to driver */
DECL|macro|MSVR1_TSTOP
mdefine_line|#define&t;MSVR1_TSTOP&t;0x08&t;/* Set if port flow controlled */
DECL|macro|MSVR1_TEMPTY
mdefine_line|#define&t;MSVR1_TEMPTY&t;0x04&t;/* Set if port tx buffer empty */
DECL|macro|MSVR1_HOST
mdefine_line|#define&t;MSVR1_HOST&t;0xf3&t;/* The bits the host wants */
multiline_comment|/* MSVR2 */
DECL|macro|MSVR2_DSR
mdefine_line|#define&t;MSVR2_DSR&t;0x02&t;/* DSR output pin (DTR on Cirrus) */
multiline_comment|/* MCOR */
DECL|macro|MCOR_CD
mdefine_line|#define&t;MCOR_CD&t;        0x80&t;/* CD (DSR on Cirrus) */
DECL|macro|MCOR_RTS
mdefine_line|#define&t;MCOR_RTS&t;0x40&t;/* RTS (CTS on Cirrus) */
DECL|macro|MCOR_RI
mdefine_line|#define&t;MCOR_RI&t;        0x20&t;/* RI */
DECL|macro|MCOR_DTR
mdefine_line|#define&t;MCOR_DTR&t;0x10&t;/* DTR (CD on Cirrus) */
DECL|macro|MCOR_DEFAULT
mdefine_line|#define MCOR_DEFAULT    (MCOR_CD | MCOR_RTS | MCOR_RI | MCOR_DTR)
DECL|macro|MCOR_FULLMODEM
mdefine_line|#define MCOR_FULLMODEM  MCOR_DEFAULT
DECL|macro|MCOR_RJ45
mdefine_line|#define MCOR_RJ45       (MCOR_CD | MCOR_RTS | MCOR_DTR)
DECL|macro|MCOR_RESTRICTED
mdefine_line|#define MCOR_RESTRICTED (MCOR_CD | MCOR_RTS)
multiline_comment|/* More MCOR - H/W Handshake (flowcontrol) stuff */
DECL|macro|MCOR_THRESH8
mdefine_line|#define&t;MCOR_THRESH8&t;0x08&t;/* eight characters then we stop */
DECL|macro|MCOR_THRESH9
mdefine_line|#define&t;MCOR_THRESH9&t;0x09&t;/* nine characters then we stop */
DECL|macro|MCOR_THRESH10
mdefine_line|#define&t;MCOR_THRESH10&t;0x0A&t;/* ten characters then we stop */
DECL|macro|MCOR_THRESH11
mdefine_line|#define&t;MCOR_THRESH11&t;0x0B&t;/* eleven characters then we stop */
DECL|macro|MCOR_THRESHBITS
mdefine_line|#define&t;MCOR_THRESHBITS 0x0F&t;/* mask for ANDing out the above */
DECL|macro|MCOR_THRESHOLD
mdefine_line|#define&t;MCOR_THRESHOLD&t;MCOR_THRESH9 /* MUST BE GREATER THAN COR3_THRESHOLD */
multiline_comment|/* RTPR */
DECL|macro|RTPR_DEFAULT
mdefine_line|#define RTPR_DEFAULT&t;0x02&t;/* Default */
multiline_comment|/* Defines for the subscripts of a CONFIG packet */
DECL|macro|CONFIG_COR1
mdefine_line|#define&t;CONFIG_COR1&t;1&t;/* Option register 1 */
DECL|macro|CONFIG_COR2
mdefine_line|#define&t;CONFIG_COR2&t;2&t;/* Option register 2 */
DECL|macro|CONFIG_COR4
mdefine_line|#define&t;CONFIG_COR4&t;3&t;/* Option register 4 */
DECL|macro|CONFIG_COR5
mdefine_line|#define&t;CONFIG_COR5&t;4&t;/* Option register 5 */
DECL|macro|CONFIG_TXXON
mdefine_line|#define&t;CONFIG_TXXON&t;5&t;/* Tx XON character */
DECL|macro|CONFIG_TXXOFF
mdefine_line|#define&t;CONFIG_TXXOFF&t;6&t;/* Tx XOFF character */
DECL|macro|CONFIG_RXXON
mdefine_line|#define&t;CONFIG_RXXON&t;7&t;/* Rx XON character */
DECL|macro|CONFIG_RXXOFF
mdefine_line|#define&t;CONFIG_RXXOFF&t;8&t;/* Rx XOFF character */
DECL|macro|CONFIG_LNEXT
mdefine_line|#define CONFIG_LNEXT&t;9&t;/* LNEXT character */
DECL|macro|CONFIG_TXBAUD
mdefine_line|#define&t;CONFIG_TXBAUD&t;10&t;/* Tx baud rate */
DECL|macro|CONFIG_RXBAUD
mdefine_line|#define&t;CONFIG_RXBAUD&t;11&t;/* Rx baud rate */
multiline_comment|/* Port status stuff */
DECL|macro|IDLE_CLOSED
mdefine_line|#define&t;IDLE_CLOSED&t;0&t;/* Closed */
DECL|macro|IDLE_OPEN
mdefine_line|#define IDLE_OPEN&t;1&t;/* Idle open */
DECL|macro|IDLE_BREAK
mdefine_line|#define IDLE_BREAK&t;2&t;/* Idle on break */
multiline_comment|/* Subscript of MODEM STATUS packet */
DECL|macro|MODEM_VALUE
mdefine_line|#define&t;MODEM_VALUE&t;3&t;/* Current values of handshake pins */
multiline_comment|/* Subscript of SBREAK packet */
DECL|macro|BREAK_LENGTH
mdefine_line|#define BREAK_LENGTH&t;1&t;/* Length of a break in slices of 0.01 seconds&n;&t;&t;&t;&t;   0 = stay on break until an EBREAK command&n;&t;&t;&t;&t;   is sent */
DECL|macro|PRE_EMPTIVE
mdefine_line|#define&t;PRE_EMPTIVE&t;0x80&t;/* Pre-emptive bit in command field */
multiline_comment|/* Packet types going from Host to remote - with the exception of OPEN, MOPEN,&n;   CONFIG, SBREAK and MEMDUMP the remaining bytes of the data array will not&n;   be used &n;*/
DECL|macro|OPEN
mdefine_line|#define&t;OPEN&t;&t;0x00&t;/* Open a port */
DECL|macro|CONFIG
mdefine_line|#define CONFIG&t;&t;0x01&t;/* Configure a port */
DECL|macro|MOPEN
mdefine_line|#define&t;MOPEN&t;&t;0x02&t;/* Modem open (block for DCD) */
DECL|macro|CLOSE
mdefine_line|#define&t;CLOSE&t;&t;0x03&t;/* Close a port */
DECL|macro|WFLUSH
mdefine_line|#define&t;WFLUSH&t;&t;(0x04 | PRE_EMPTIVE) /* Write flush */
DECL|macro|RFLUSH
mdefine_line|#define&t;RFLUSH&t;&t;(0x05 | PRE_EMPTIVE) /* Read flush */
DECL|macro|RESUME
mdefine_line|#define&t;RESUME&t;&t;(0x06 | PRE_EMPTIVE) /* Resume if xoffed */
DECL|macro|SBREAK
mdefine_line|#define&t;SBREAK&t;&t;0x07 &t;/* Start break */
DECL|macro|EBREAK
mdefine_line|#define&t;EBREAK&t;&t;0x08&t;/* End break */
DECL|macro|SUSPEND
mdefine_line|#define&t;SUSPEND&t;&t;(0x09 | PRE_EMPTIVE) /* Susp op (behave as tho xoffed) */
DECL|macro|FCLOSE
mdefine_line|#define FCLOSE          (0x0a | PRE_EMPTIVE) /* Force close */
DECL|macro|XPRINT
mdefine_line|#define XPRINT          0x0b    /* Xprint packet */
DECL|macro|MBIS
mdefine_line|#define MBIS&t;&t;(0x0c | PRE_EMPTIVE) /* Set modem lines */
DECL|macro|MBIC
mdefine_line|#define MBIC&t;&t;(0x0d | PRE_EMPTIVE) /* Clear modem lines */
DECL|macro|MSET
mdefine_line|#define MSET&t;&t;(0x0e | PRE_EMPTIVE) /* Set modem lines */
DECL|macro|PCLOSE
mdefine_line|#define PCLOSE&t;&t;0x0f&t;/* Pseudo close - Leaves rx/tx enabled */
DECL|macro|MGET
mdefine_line|#define MGET&t;&t;(0x10 | PRE_EMPTIVE) /* Force update of modem status */
DECL|macro|MEMDUMP
mdefine_line|#define MEMDUMP&t;&t;(0x11 | PRE_EMPTIVE) /* Send back mem from addr supplied */
DECL|macro|READ_REGISTER
mdefine_line|#define&t;READ_REGISTER&t;(0x12 | PRE_EMPTIVE) /* Read CD1400 register (debug) */
multiline_comment|/* &quot;Command&quot; packets going from remote to host COMPLETE and MODEM_STATUS&n;   use data[4] / data[3] to indicate current state and modem status respectively&n;*/
DECL|macro|COMPLETE
mdefine_line|#define&t;COMPLETE&t;(0x20 | PRE_EMPTIVE)
multiline_comment|/* Command complete */
DECL|macro|BREAK_RECEIVED
mdefine_line|#define BREAK_RECEIVED&t;(0x21 | PRE_EMPTIVE)
multiline_comment|/* Break received */
DECL|macro|MODEM_STATUS
mdefine_line|#define MODEM_STATUS&t;(0x22 | PRE_EMPTIVE)
multiline_comment|/* Change in modem status */
multiline_comment|/* &quot;Command&quot; packet that could go either way - handshake wake-up */
DECL|macro|HANDSHAKE
mdefine_line|#define HANDSHAKE&t;(0x23 | PRE_EMPTIVE)
multiline_comment|/* Wake-up to HOST / RTA */
macro_line|#endif
eof
