multiline_comment|/* $Id: act2000_isa.h,v 1.4 2000/11/12 16:32:06 kai Exp $&n; *&n; * ISDN lowlevel-module for the IBM ISDN-S0 Active 2000 (ISA-Version).&n; *&n; * Copyright 1998 by Fritz Elfert (fritz@isdn4linux.de)&n; * Thanks to Friedemann Baitinger and IBM Germany&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n; *&n; */
macro_line|#ifndef act2000_isa_h
DECL|macro|act2000_isa_h
mdefine_line|#define act2000_isa_h
DECL|macro|ISA_POLL_LOOP
mdefine_line|#define ISA_POLL_LOOP 40        /* Try to read-write before give up */
r_typedef
r_enum
(brace
DECL|enumerator|INT_NO_CHANGE
id|INT_NO_CHANGE
op_assign
l_int|0
comma
multiline_comment|/* Do not change the Mask */
DECL|enumerator|INT_ON
id|INT_ON
op_assign
l_int|1
comma
multiline_comment|/* Set to Enable */
DECL|enumerator|INT_OFF
id|INT_OFF
op_assign
l_int|2
comma
multiline_comment|/* Set to Disable */
DECL|typedef|ISA_INT_T
)brace
id|ISA_INT_T
suffix:semicolon
multiline_comment|/**************************************************************************/
multiline_comment|/*      Configuration Register COR (RW)                                   */
multiline_comment|/**************************************************************************/
multiline_comment|/*    7    |   6    |    5   |   4    |    3   |    2   |    1   |    0   */
multiline_comment|/* Soft Res|  IRQM  |        IRQ Select        |   N/A  |  WAIT  |Proc err */
multiline_comment|/**************************************************************************/
DECL|macro|ISA_COR
mdefine_line|#define        ISA_COR             0&t;/* Offset for ISA config register */
DECL|macro|ISA_COR_PERR
mdefine_line|#define        ISA_COR_PERR     0x01&t;/* Processor Error Enabled        */
DECL|macro|ISA_COR_WS
mdefine_line|#define        ISA_COR_WS       0x02&t;/* Insert Wait State if 1         */
DECL|macro|ISA_COR_IRQOFF
mdefine_line|#define        ISA_COR_IRQOFF   0x38&t;/* No Interrupt                   */
DECL|macro|ISA_COR_IRQ07
mdefine_line|#define        ISA_COR_IRQ07    0x30&t;/* IRQ 7 Enable                   */
DECL|macro|ISA_COR_IRQ05
mdefine_line|#define        ISA_COR_IRQ05    0x28&t;/* IRQ 5 Enable                   */
DECL|macro|ISA_COR_IRQ03
mdefine_line|#define        ISA_COR_IRQ03    0x20&t;/* IRQ 3 Enable                   */
DECL|macro|ISA_COR_IRQ10
mdefine_line|#define        ISA_COR_IRQ10    0x18&t;/* IRQ 10 Enable                  */
DECL|macro|ISA_COR_IRQ11
mdefine_line|#define        ISA_COR_IRQ11    0x10&t;/* IRQ 11 Enable                  */
DECL|macro|ISA_COR_IRQ12
mdefine_line|#define        ISA_COR_IRQ12    0x08&t;/* IRQ 12 Enable                  */
DECL|macro|ISA_COR_IRQ15
mdefine_line|#define        ISA_COR_IRQ15    0x00&t;/* IRQ 15 Enable                  */
DECL|macro|ISA_COR_IRQPULSE
mdefine_line|#define        ISA_COR_IRQPULSE 0x40&t;/* 0 = Level 1 = Pulse Interrupt  */
DECL|macro|ISA_COR_RESET
mdefine_line|#define        ISA_COR_RESET    0x80&t;/* Soft Reset for Transputer      */
multiline_comment|/**************************************************************************/
multiline_comment|/*      Interrupt Source Register ISR (RO)                                */
multiline_comment|/**************************************************************************/
multiline_comment|/*    7    |   6    |    5   |   4    |    3   |    2   |    1   |    0   */
multiline_comment|/*   N/A   |  N/A   |   N/A  |Err sig |Ser ID  |IN Intr |Out Intr| Error  */
multiline_comment|/**************************************************************************/
DECL|macro|ISA_ISR
mdefine_line|#define        ISA_ISR             1&t;/* Offset for Interrupt Register  */
DECL|macro|ISA_ISR_ERR
mdefine_line|#define        ISA_ISR_ERR      0x01&t;/* Error Interrupt                */
DECL|macro|ISA_ISR_OUT
mdefine_line|#define        ISA_ISR_OUT      0x02&t;/* Output Interrupt               */
DECL|macro|ISA_ISR_INP
mdefine_line|#define        ISA_ISR_INP      0x04&t;/* Input Interrupt                */
DECL|macro|ISA_ISR_SERIAL
mdefine_line|#define        ISA_ISR_SERIAL   0x08&t;/* Read out Serial ID after Reset */
DECL|macro|ISA_ISR_ERRSIG
mdefine_line|#define        ISA_ISR_ERRSIG   0x10&t;/* Error Signal Input             */
DECL|macro|ISA_ISR_ERR_MASK
mdefine_line|#define        ISA_ISR_ERR_MASK 0xfe    /* Mask Error Interrupt           */
DECL|macro|ISA_ISR_OUT_MASK
mdefine_line|#define        ISA_ISR_OUT_MASK 0xfd    /* Mask Output Interrupt          */
DECL|macro|ISA_ISR_INP_MASK
mdefine_line|#define        ISA_ISR_INP_MASK 0xfb    /* Mask Input Interrupt           */
multiline_comment|/* Signature delivered after Reset at ISA_ISR_SERIAL (LSB first)          */
DECL|macro|ISA_SER_ID
mdefine_line|#define        ISA_SER_ID     0x0201&t;/* ID for ISA Card                */
multiline_comment|/**************************************************************************/
multiline_comment|/*      EEPROM Register EPR (RW)                                          */
multiline_comment|/**************************************************************************/
multiline_comment|/*    7    |   6    |    5   |   4    |    3   |    2   |    1   |    0   */
multiline_comment|/*   N/A   |  N/A   |   N/A  |ROM Hold| ROM CS |ROM CLK | ROM IN |ROM Out */
multiline_comment|/**************************************************************************/
DECL|macro|ISA_EPR
mdefine_line|#define        ISA_EPR             2&t;/* Offset for this Register       */
DECL|macro|ISA_EPR_OUT
mdefine_line|#define        ISA_EPR_OUT      0x01&t;/* Rome Register Out (RO)         */
DECL|macro|ISA_EPR_IN
mdefine_line|#define        ISA_EPR_IN       0x02&t;/* Rom Register In (WR)           */
DECL|macro|ISA_EPR_CLK
mdefine_line|#define        ISA_EPR_CLK      0x04&t;/* Rom Clock (WR)                 */
DECL|macro|ISA_EPR_CS
mdefine_line|#define        ISA_EPR_CS       0x08&t;/* Rom Cip Select (WR)            */
DECL|macro|ISA_EPR_HOLD
mdefine_line|#define        ISA_EPR_HOLD     0x10&t;/* Rom Hold Signal (WR)           */
multiline_comment|/**************************************************************************/
multiline_comment|/*      EEPROM enable Register EER (unused)                               */
multiline_comment|/**************************************************************************/
DECL|macro|ISA_EER
mdefine_line|#define        ISA_EER             3&t;/* Offset for this Register       */
multiline_comment|/**************************************************************************/
multiline_comment|/*      SLC Data Input SDI (RO)                                           */
multiline_comment|/**************************************************************************/
DECL|macro|ISA_SDI
mdefine_line|#define        ISA_SDI             4&t;/* Offset for this Register       */
multiline_comment|/**************************************************************************/
multiline_comment|/*      SLC Data Output SDO (WO)                                          */
multiline_comment|/**************************************************************************/
DECL|macro|ISA_SDO
mdefine_line|#define        ISA_SDO             5&t;/* Offset for this Register       */
multiline_comment|/**************************************************************************/
multiline_comment|/*      IMS C011 Mode 2 Input Status Register for INMOS CPU SIS (RW)      */
multiline_comment|/**************************************************************************/
multiline_comment|/*    7    |   6    |    5   |   4    |    3   |    2   |    1   |    0   */
multiline_comment|/*   N/A   |  N/A   |   N/A  |  N/A   |   N/A  |   N/A  |Int Ena |Data Pre */
multiline_comment|/**************************************************************************/
DECL|macro|ISA_SIS
mdefine_line|#define        ISA_SIS             6&t;/* Offset for this Register       */
DECL|macro|ISA_SIS_READY
mdefine_line|#define        ISA_SIS_READY    0x01&t;/* If 1 : data is available       */
DECL|macro|ISA_SIS_INT
mdefine_line|#define        ISA_SIS_INT      0x02&t;/* Enable Interrupt for READ      */
multiline_comment|/**************************************************************************/
multiline_comment|/*      IMS C011 Mode 2 Output Status Register from INMOS CPU SOS (RW)    */
multiline_comment|/**************************************************************************/
multiline_comment|/*    7    |   6    |    5   |   4    |    3   |    2   |    1   |    0   */
multiline_comment|/*   N/A   |  N/A   |   N/A  |  N/A   |   N/A  |   N/A  |Int Ena |Out Rdy */
multiline_comment|/**************************************************************************/
DECL|macro|ISA_SOS
mdefine_line|#define        ISA_SOS             7&t;/* Offset for this Register       */
DECL|macro|ISA_SOS_READY
mdefine_line|#define        ISA_SOS_READY    0x01&t;/* If 1 : we can write Data       */
DECL|macro|ISA_SOS_INT
mdefine_line|#define        ISA_SOS_INT      0x02&t;/* Enable Interrupt for WRITE     */
DECL|macro|ISA_REGION
mdefine_line|#define        ISA_REGION          8&t;/* Number of Registers            */
multiline_comment|/* Macros for accessing ports */
DECL|macro|ISA_PORT_COR
mdefine_line|#define ISA_PORT_COR (card-&gt;port+ISA_COR)
DECL|macro|ISA_PORT_ISR
mdefine_line|#define ISA_PORT_ISR (card-&gt;port+ISA_ISR)
DECL|macro|ISA_PORT_EPR
mdefine_line|#define ISA_PORT_EPR (card-&gt;port+ISA_EPR)
DECL|macro|ISA_PORT_EER
mdefine_line|#define ISA_PORT_EER (card-&gt;port+ISA_EER)
DECL|macro|ISA_PORT_SDI
mdefine_line|#define ISA_PORT_SDI (card-&gt;port+ISA_SDI)
DECL|macro|ISA_PORT_SDO
mdefine_line|#define ISA_PORT_SDO (card-&gt;port+ISA_SDO)
DECL|macro|ISA_PORT_SIS
mdefine_line|#define ISA_PORT_SIS (card-&gt;port+ISA_SIS)
DECL|macro|ISA_PORT_SOS
mdefine_line|#define ISA_PORT_SOS (card-&gt;port+ISA_SOS)
multiline_comment|/* Prototypes */
r_extern
r_int
id|act2000_isa_detect
c_func
(paren
r_int
r_int
id|portbase
)paren
suffix:semicolon
r_extern
r_int
id|act2000_isa_config_irq
c_func
(paren
id|act2000_card
op_star
id|card
comma
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_int
id|act2000_isa_config_port
c_func
(paren
id|act2000_card
op_star
id|card
comma
r_int
r_int
id|portbase
)paren
suffix:semicolon
r_extern
r_int
id|act2000_isa_download
c_func
(paren
id|act2000_card
op_star
id|card
comma
id|act2000_ddef
op_star
id|cb
)paren
suffix:semicolon
r_extern
r_void
id|act2000_isa_release
c_func
(paren
id|act2000_card
op_star
id|card
)paren
suffix:semicolon
r_extern
r_void
id|act2000_isa_receive
c_func
(paren
id|act2000_card
op_star
id|card
)paren
suffix:semicolon
r_extern
r_void
id|act2000_isa_send
c_func
(paren
id|act2000_card
op_star
id|card
)paren
suffix:semicolon
macro_line|#endif                          /* act2000_isa_h */
eof
