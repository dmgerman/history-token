multiline_comment|/*  *********************************************************************&n;    *  SB1250 Board Support Package&n;    *  &n;    *  UART Constants&t;&t;&t;&t;File: sb1250_uart.h&n;    *  &n;    *  This module contains constants and macros useful for &n;    *  manipulating the SB1250&squot;s UARTs&n;    *&n;    *  SB1250 specification level:  User&squot;s manual 1/02/02&n;    *  &n;    *  Author:  Mitch Lichtenberg (mpl@broadcom.com)&n;    *  &n;    *********************************************************************  &n;    *&n;    *  Copyright 2000,2001,2002,2003&n;    *  Broadcom Corporation. All rights reserved.&n;    *  &n;    *  This program is free software; you can redistribute it and/or &n;    *  modify it under the terms of the GNU General Public License as &n;    *  published by the Free Software Foundation; either version 2 of &n;    *  the License, or (at your option) any later version.&n;    *&n;    *  This program is distributed in the hope that it will be useful,&n;    *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    *  GNU General Public License for more details.&n;    *&n;    *  You should have received a copy of the GNU General Public License&n;    *  along with this program; if not, write to the Free Software&n;    *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n;    *  MA 02111-1307 USA&n;    ********************************************************************* */
macro_line|#ifndef _SB1250_UART_H
DECL|macro|_SB1250_UART_H
mdefine_line|#define _SB1250_UART_H
macro_line|#include &quot;sb1250_defs.h&quot;
multiline_comment|/* ********************************************************************** &n;   * DUART Registers&n;   ********************************************************************** */
multiline_comment|/*&n; * DUART Mode Register #1 (Table 10-3)&n; * Register: DUART_MODE_REG_1_A&n; * Register: DUART_MODE_REG_1_B&n; */
DECL|macro|S_DUART_BITS_PER_CHAR
mdefine_line|#define S_DUART_BITS_PER_CHAR       0
DECL|macro|M_DUART_BITS_PER_CHAR
mdefine_line|#define M_DUART_BITS_PER_CHAR       _SB_MAKEMASK(2,S_DUART_BITS_PER_CHAR)
DECL|macro|V_DUART_BITS_PER_CHAR
mdefine_line|#define V_DUART_BITS_PER_CHAR(x)    _SB_MAKEVALUE(x,S_DUART_BITS_PER_CHAR)
DECL|macro|K_DUART_BITS_PER_CHAR_RSV0
mdefine_line|#define K_DUART_BITS_PER_CHAR_RSV0  0
DECL|macro|K_DUART_BITS_PER_CHAR_RSV1
mdefine_line|#define K_DUART_BITS_PER_CHAR_RSV1  1
DECL|macro|K_DUART_BITS_PER_CHAR_7
mdefine_line|#define K_DUART_BITS_PER_CHAR_7     2
DECL|macro|K_DUART_BITS_PER_CHAR_8
mdefine_line|#define K_DUART_BITS_PER_CHAR_8     3
DECL|macro|V_DUART_BITS_PER_CHAR_RSV0
mdefine_line|#define V_DUART_BITS_PER_CHAR_RSV0  V_DUART_BITS_PER_CHAR(K_DUART_BITS_PER_CHAR_RSV0)
DECL|macro|V_DUART_BITS_PER_CHAR_RSV1
mdefine_line|#define V_DUART_BITS_PER_CHAR_RSV1  V_DUART_BITS_PER_CHAR(K_DUART_BITS_PER_CHAR_RSV1)
DECL|macro|V_DUART_BITS_PER_CHAR_7
mdefine_line|#define V_DUART_BITS_PER_CHAR_7     V_DUART_BITS_PER_CHAR(K_DUART_BITS_PER_CHAR_7)
DECL|macro|V_DUART_BITS_PER_CHAR_8
mdefine_line|#define V_DUART_BITS_PER_CHAR_8     V_DUART_BITS_PER_CHAR(K_DUART_BITS_PER_CHAR_8)
DECL|macro|M_DUART_PARITY_TYPE_EVEN
mdefine_line|#define M_DUART_PARITY_TYPE_EVEN    0x00
DECL|macro|M_DUART_PARITY_TYPE_ODD
mdefine_line|#define M_DUART_PARITY_TYPE_ODD     _SB_MAKEMASK1(2)
DECL|macro|S_DUART_PARITY_MODE
mdefine_line|#define S_DUART_PARITY_MODE          3
DECL|macro|M_DUART_PARITY_MODE
mdefine_line|#define M_DUART_PARITY_MODE         _SB_MAKEMASK(2,S_DUART_PARITY_MODE)
DECL|macro|V_DUART_PARITY_MODE
mdefine_line|#define V_DUART_PARITY_MODE(x)      _SB_MAKEVALUE(x,S_DUART_PARITY_MODE)
DECL|macro|K_DUART_PARITY_MODE_ADD
mdefine_line|#define K_DUART_PARITY_MODE_ADD       0
DECL|macro|K_DUART_PARITY_MODE_ADD_FIXED
mdefine_line|#define K_DUART_PARITY_MODE_ADD_FIXED 1
DECL|macro|K_DUART_PARITY_MODE_NONE
mdefine_line|#define K_DUART_PARITY_MODE_NONE      2
DECL|macro|V_DUART_PARITY_MODE_ADD
mdefine_line|#define V_DUART_PARITY_MODE_ADD       V_DUART_PARITY_MODE(K_DUART_PARITY_MODE_ADD)
DECL|macro|V_DUART_PARITY_MODE_ADD_FIXED
mdefine_line|#define V_DUART_PARITY_MODE_ADD_FIXED V_DUART_PARITY_MODE(K_DUART_PARITY_MODE_ADD_FIXED)
DECL|macro|V_DUART_PARITY_MODE_NONE
mdefine_line|#define V_DUART_PARITY_MODE_NONE      V_DUART_PARITY_MODE(K_DUART_PARITY_MODE_NONE)
DECL|macro|M_DUART_ERR_MODE
mdefine_line|#define M_DUART_ERR_MODE            _SB_MAKEMASK1(5)    /* must be zero */
DECL|macro|M_DUART_RX_IRQ_SEL_RXRDY
mdefine_line|#define M_DUART_RX_IRQ_SEL_RXRDY    0
DECL|macro|M_DUART_RX_IRQ_SEL_RXFULL
mdefine_line|#define M_DUART_RX_IRQ_SEL_RXFULL   _SB_MAKEMASK1(6)
DECL|macro|M_DUART_RX_RTS_ENA
mdefine_line|#define M_DUART_RX_RTS_ENA          _SB_MAKEMASK1(7)
multiline_comment|/*&n; * DUART Mode Register #2 (Table 10-4)&n; * Register: DUART_MODE_REG_2_A&n; * Register: DUART_MODE_REG_2_B&n; */
DECL|macro|M_DUART_MODE_RESERVED1
mdefine_line|#define M_DUART_MODE_RESERVED1      _SB_MAKEMASK(3,0)   /* ignored */
DECL|macro|M_DUART_STOP_BIT_LEN_2
mdefine_line|#define M_DUART_STOP_BIT_LEN_2      _SB_MAKEMASK1(3)
DECL|macro|M_DUART_STOP_BIT_LEN_1
mdefine_line|#define M_DUART_STOP_BIT_LEN_1      0
DECL|macro|M_DUART_TX_CTS_ENA
mdefine_line|#define M_DUART_TX_CTS_ENA          _SB_MAKEMASK1(4)
DECL|macro|M_DUART_MODE_RESERVED2
mdefine_line|#define M_DUART_MODE_RESERVED2      _SB_MAKEMASK1(5)    /* must be zero */
DECL|macro|S_DUART_CHAN_MODE
mdefine_line|#define S_DUART_CHAN_MODE&t;    6
DECL|macro|M_DUART_CHAN_MODE
mdefine_line|#define M_DUART_CHAN_MODE           _SB_MAKEMASK(2,S_DUART_CHAN_MODE)
DECL|macro|V_DUART_CHAN_MODE
mdefine_line|#define V_DUART_CHAN_MODE(x)&t;    _SB_MAKEVALUE(x,S_DUART_CHAN_MODE)
DECL|macro|K_DUART_CHAN_MODE_NORMAL
mdefine_line|#define K_DUART_CHAN_MODE_NORMAL    0
DECL|macro|K_DUART_CHAN_MODE_LCL_LOOP
mdefine_line|#define K_DUART_CHAN_MODE_LCL_LOOP  2
DECL|macro|K_DUART_CHAN_MODE_REM_LOOP
mdefine_line|#define K_DUART_CHAN_MODE_REM_LOOP  3
DECL|macro|V_DUART_CHAN_MODE_NORMAL
mdefine_line|#define V_DUART_CHAN_MODE_NORMAL    V_DUART_CHAN_MODE(K_DUART_CHAN_MODE_NORMAL)
DECL|macro|V_DUART_CHAN_MODE_LCL_LOOP
mdefine_line|#define V_DUART_CHAN_MODE_LCL_LOOP  V_DUART_CHAN_MODE(K_DUART_CHAN_MODE_LCL_LOOP)
DECL|macro|V_DUART_CHAN_MODE_REM_LOOP
mdefine_line|#define V_DUART_CHAN_MODE_REM_LOOP  V_DUART_CHAN_MODE(K_DUART_CHAN_MODE_REM_LOOP)
multiline_comment|/*&n; * DUART Command Register (Table 10-5)&n; * Register: DUART_CMD_A&n; * Register: DUART_CMD_B&n; */
DECL|macro|M_DUART_RX_EN
mdefine_line|#define M_DUART_RX_EN               _SB_MAKEMASK1(0)
DECL|macro|M_DUART_RX_DIS
mdefine_line|#define M_DUART_RX_DIS              _SB_MAKEMASK1(1)
DECL|macro|M_DUART_TX_EN
mdefine_line|#define M_DUART_TX_EN               _SB_MAKEMASK1(2)
DECL|macro|M_DUART_TX_DIS
mdefine_line|#define M_DUART_TX_DIS              _SB_MAKEMASK1(3)
DECL|macro|S_DUART_MISC_CMD
mdefine_line|#define S_DUART_MISC_CMD&t;    4
DECL|macro|M_DUART_MISC_CMD
mdefine_line|#define M_DUART_MISC_CMD            _SB_MAKEMASK(3,S_DUART_MISC_CMD)
DECL|macro|V_DUART_MISC_CMD
mdefine_line|#define V_DUART_MISC_CMD(x)         _SB_MAKEVALUE(x,S_DUART_MISC_CMD)
DECL|macro|K_DUART_MISC_CMD_NOACTION0
mdefine_line|#define K_DUART_MISC_CMD_NOACTION0       0
DECL|macro|K_DUART_MISC_CMD_NOACTION1
mdefine_line|#define K_DUART_MISC_CMD_NOACTION1       1
DECL|macro|K_DUART_MISC_CMD_RESET_RX
mdefine_line|#define K_DUART_MISC_CMD_RESET_RX        2
DECL|macro|K_DUART_MISC_CMD_RESET_TX
mdefine_line|#define K_DUART_MISC_CMD_RESET_TX        3
DECL|macro|K_DUART_MISC_CMD_NOACTION4
mdefine_line|#define K_DUART_MISC_CMD_NOACTION4       4
DECL|macro|K_DUART_MISC_CMD_RESET_BREAK_INT
mdefine_line|#define K_DUART_MISC_CMD_RESET_BREAK_INT 5
DECL|macro|K_DUART_MISC_CMD_START_BREAK
mdefine_line|#define K_DUART_MISC_CMD_START_BREAK     6
DECL|macro|K_DUART_MISC_CMD_STOP_BREAK
mdefine_line|#define K_DUART_MISC_CMD_STOP_BREAK      7
DECL|macro|V_DUART_MISC_CMD_NOACTION0
mdefine_line|#define V_DUART_MISC_CMD_NOACTION0       V_DUART_MISC_CMD(K_DUART_MISC_CMD_NOACTION0)
DECL|macro|V_DUART_MISC_CMD_NOACTION1
mdefine_line|#define V_DUART_MISC_CMD_NOACTION1       V_DUART_MISC_CMD(K_DUART_MISC_CMD_NOACTION1)
DECL|macro|V_DUART_MISC_CMD_RESET_RX
mdefine_line|#define V_DUART_MISC_CMD_RESET_RX        V_DUART_MISC_CMD(K_DUART_MISC_CMD_RESET_RX)
DECL|macro|V_DUART_MISC_CMD_RESET_TX
mdefine_line|#define V_DUART_MISC_CMD_RESET_TX        V_DUART_MISC_CMD(K_DUART_MISC_CMD_RESET_TX)
DECL|macro|V_DUART_MISC_CMD_NOACTION4
mdefine_line|#define V_DUART_MISC_CMD_NOACTION4       V_DUART_MISC_CMD(K_DUART_MISC_CMD_NOACTION4)
DECL|macro|V_DUART_MISC_CMD_RESET_BREAK_INT
mdefine_line|#define V_DUART_MISC_CMD_RESET_BREAK_INT V_DUART_MISC_CMD(K_DUART_MISC_CMD_RESET_BREAK_INT)
DECL|macro|V_DUART_MISC_CMD_START_BREAK
mdefine_line|#define V_DUART_MISC_CMD_START_BREAK     V_DUART_MISC_CMD(K_DUART_MISC_CMD_START_BREAK)
DECL|macro|V_DUART_MISC_CMD_STOP_BREAK
mdefine_line|#define V_DUART_MISC_CMD_STOP_BREAK      V_DUART_MISC_CMD(K_DUART_MISC_CMD_STOP_BREAK)
DECL|macro|M_DUART_CMD_RESERVED
mdefine_line|#define M_DUART_CMD_RESERVED             _SB_MAKEMASK1(7) 
multiline_comment|/*&n; * DUART Status Register (Table 10-6)&n; * Register: DUART_STATUS_A&n; * Register: DUART_STATUS_B&n; * READ-ONLY&n; */
DECL|macro|M_DUART_RX_RDY
mdefine_line|#define M_DUART_RX_RDY              _SB_MAKEMASK1(0)
DECL|macro|M_DUART_RX_FFUL
mdefine_line|#define M_DUART_RX_FFUL             _SB_MAKEMASK1(1)
DECL|macro|M_DUART_TX_RDY
mdefine_line|#define M_DUART_TX_RDY              _SB_MAKEMASK1(2)
DECL|macro|M_DUART_TX_EMT
mdefine_line|#define M_DUART_TX_EMT              _SB_MAKEMASK1(3)
DECL|macro|M_DUART_OVRUN_ERR
mdefine_line|#define M_DUART_OVRUN_ERR           _SB_MAKEMASK1(4)
DECL|macro|M_DUART_PARITY_ERR
mdefine_line|#define M_DUART_PARITY_ERR          _SB_MAKEMASK1(5)
DECL|macro|M_DUART_FRM_ERR
mdefine_line|#define M_DUART_FRM_ERR             _SB_MAKEMASK1(6)
DECL|macro|M_DUART_RCVD_BRK
mdefine_line|#define M_DUART_RCVD_BRK            _SB_MAKEMASK1(7)
multiline_comment|/*&n; * DUART Baud Rate Register (Table 10-7)&n; * Register: DUART_CLK_SEL_A &n; * Register: DUART_CLK_SEL_B&n; */
DECL|macro|M_DUART_CLK_COUNTER
mdefine_line|#define M_DUART_CLK_COUNTER         _SB_MAKEMASK(12,0)
DECL|macro|V_DUART_BAUD_RATE
mdefine_line|#define V_DUART_BAUD_RATE(x)        (100000000/((x)*20)-1)
multiline_comment|/*&n; * DUART Data Registers (Table 10-8 and 10-9)&n; * Register: DUART_RX_HOLD_A&n; * Register: DUART_RX_HOLD_B&n; * Register: DUART_TX_HOLD_A&n; * Register: DUART_TX_HOLD_B&n; */
DECL|macro|M_DUART_RX_DATA
mdefine_line|#define M_DUART_RX_DATA             _SB_MAKEMASK(8,0)
DECL|macro|M_DUART_TX_DATA
mdefine_line|#define M_DUART_TX_DATA             _SB_MAKEMASK(8,0)
multiline_comment|/*&n; * DUART Input Port Register (Table 10-10)&n; * Register: DUART_IN_PORT&n; */
DECL|macro|M_DUART_IN_PIN0_VAL
mdefine_line|#define M_DUART_IN_PIN0_VAL         _SB_MAKEMASK1(0)
DECL|macro|M_DUART_IN_PIN1_VAL
mdefine_line|#define M_DUART_IN_PIN1_VAL         _SB_MAKEMASK1(1)
DECL|macro|M_DUART_IN_PIN2_VAL
mdefine_line|#define M_DUART_IN_PIN2_VAL         _SB_MAKEMASK1(2)
DECL|macro|M_DUART_IN_PIN3_VAL
mdefine_line|#define M_DUART_IN_PIN3_VAL         _SB_MAKEMASK1(3)
DECL|macro|M_DUART_IN_PIN4_VAL
mdefine_line|#define M_DUART_IN_PIN4_VAL         _SB_MAKEMASK1(4)
DECL|macro|M_DUART_IN_PIN5_VAL
mdefine_line|#define M_DUART_IN_PIN5_VAL         _SB_MAKEMASK1(5)
DECL|macro|M_DUART_RIN0_PIN
mdefine_line|#define M_DUART_RIN0_PIN            _SB_MAKEMASK1(6)
DECL|macro|M_DUART_RIN1_PIN
mdefine_line|#define M_DUART_RIN1_PIN            _SB_MAKEMASK1(7)
multiline_comment|/*&n; * DUART Input Port Change Status Register (Tables 10-11, 10-12, and 10-13)&n; * Register: DUART_INPORT_CHNG&n; */
DECL|macro|S_DUART_IN_PIN_VAL
mdefine_line|#define S_DUART_IN_PIN_VAL          0
DECL|macro|M_DUART_IN_PIN_VAL
mdefine_line|#define M_DUART_IN_PIN_VAL          _SB_MAKEMASK(4,S_DUART_IN_PIN_VAL)
DECL|macro|S_DUART_IN_PIN_CHNG
mdefine_line|#define S_DUART_IN_PIN_CHNG         4
DECL|macro|M_DUART_IN_PIN_CHNG
mdefine_line|#define M_DUART_IN_PIN_CHNG         _SB_MAKEMASK(4,S_DUART_IN_PIN_CHNG)
multiline_comment|/*&n; * DUART Output port control register (Table 10-14)&n; * Register: DUART_OPCR&n; */
DECL|macro|M_DUART_OPCR_RESERVED0
mdefine_line|#define M_DUART_OPCR_RESERVED0      _SB_MAKEMASK1(0)   /* must be zero */
DECL|macro|M_DUART_OPC2_SEL
mdefine_line|#define M_DUART_OPC2_SEL            _SB_MAKEMASK1(1)
DECL|macro|M_DUART_OPCR_RESERVED1
mdefine_line|#define M_DUART_OPCR_RESERVED1      _SB_MAKEMASK1(2)   /* must be zero */
DECL|macro|M_DUART_OPC3_SEL
mdefine_line|#define M_DUART_OPC3_SEL            _SB_MAKEMASK1(3)
DECL|macro|M_DUART_OPCR_RESERVED2
mdefine_line|#define M_DUART_OPCR_RESERVED2      _SB_MAKEMASK(4,4)  /* must be zero */
multiline_comment|/*&n; * DUART Aux Control Register (Table 10-15)&n; * Register: DUART_AUX_CTRL&n; */
DECL|macro|M_DUART_IP0_CHNG_ENA
mdefine_line|#define M_DUART_IP0_CHNG_ENA        _SB_MAKEMASK1(0)
DECL|macro|M_DUART_IP1_CHNG_ENA
mdefine_line|#define M_DUART_IP1_CHNG_ENA        _SB_MAKEMASK1(1)
DECL|macro|M_DUART_IP2_CHNG_ENA
mdefine_line|#define M_DUART_IP2_CHNG_ENA        _SB_MAKEMASK1(2)
DECL|macro|M_DUART_IP3_CHNG_ENA
mdefine_line|#define M_DUART_IP3_CHNG_ENA        _SB_MAKEMASK1(3)
DECL|macro|M_DUART_ACR_RESERVED
mdefine_line|#define M_DUART_ACR_RESERVED        _SB_MAKEMASK(4,4)
DECL|macro|M_DUART_CTS_CHNG_ENA
mdefine_line|#define M_DUART_CTS_CHNG_ENA        _SB_MAKEMASK1(0)
DECL|macro|M_DUART_CIN_CHNG_ENA
mdefine_line|#define M_DUART_CIN_CHNG_ENA        _SB_MAKEMASK1(2)
multiline_comment|/*&n; * DUART Interrupt Status Register (Table 10-16)&n; * Register: DUART_ISR&n; */
DECL|macro|M_DUART_ISR_TX_A
mdefine_line|#define M_DUART_ISR_TX_A            _SB_MAKEMASK1(0)
DECL|macro|M_DUART_ISR_RX_A
mdefine_line|#define M_DUART_ISR_RX_A            _SB_MAKEMASK1(1)
DECL|macro|M_DUART_ISR_BRK_A
mdefine_line|#define M_DUART_ISR_BRK_A           _SB_MAKEMASK1(2)
DECL|macro|M_DUART_ISR_IN_A
mdefine_line|#define M_DUART_ISR_IN_A            _SB_MAKEMASK1(3)
DECL|macro|M_DUART_ISR_TX_B
mdefine_line|#define M_DUART_ISR_TX_B            _SB_MAKEMASK1(4)
DECL|macro|M_DUART_ISR_RX_B
mdefine_line|#define M_DUART_ISR_RX_B            _SB_MAKEMASK1(5)
DECL|macro|M_DUART_ISR_BRK_B
mdefine_line|#define M_DUART_ISR_BRK_B           _SB_MAKEMASK1(6)
DECL|macro|M_DUART_ISR_IN_B
mdefine_line|#define M_DUART_ISR_IN_B            _SB_MAKEMASK1(7)
multiline_comment|/*&n; * DUART Channel A Interrupt Status Register (Table 10-17)&n; * DUART Channel B Interrupt Status Register (Table 10-18)&n; * Register: DUART_ISR_A&n; * Register: DUART_ISR_B&n; */
DECL|macro|M_DUART_ISR_TX
mdefine_line|#define M_DUART_ISR_TX              _SB_MAKEMASK1(0)
DECL|macro|M_DUART_ISR_RX
mdefine_line|#define M_DUART_ISR_RX              _SB_MAKEMASK1(1)
DECL|macro|M_DUART_ISR_BRK
mdefine_line|#define M_DUART_ISR_BRK             _SB_MAKEMASK1(2)
DECL|macro|M_DUART_ISR_IN
mdefine_line|#define M_DUART_ISR_IN              _SB_MAKEMASK1(3)
DECL|macro|M_DUART_ISR_RESERVED
mdefine_line|#define M_DUART_ISR_RESERVED        _SB_MAKEMASK(4,4)
multiline_comment|/*&n; * DUART Interrupt Mask Register (Table 10-19)&n; * Register: DUART_IMR&n; */
DECL|macro|M_DUART_IMR_TX_A
mdefine_line|#define M_DUART_IMR_TX_A            _SB_MAKEMASK1(0)
DECL|macro|M_DUART_IMR_RX_A
mdefine_line|#define M_DUART_IMR_RX_A            _SB_MAKEMASK1(1)
DECL|macro|M_DUART_IMR_BRK_A
mdefine_line|#define M_DUART_IMR_BRK_A           _SB_MAKEMASK1(2)
DECL|macro|M_DUART_IMR_IN_A
mdefine_line|#define M_DUART_IMR_IN_A            _SB_MAKEMASK1(3)
DECL|macro|M_DUART_IMR_ALL_A
mdefine_line|#define M_DUART_IMR_ALL_A&t;    _SB_MAKEMASK(4,0)
DECL|macro|M_DUART_IMR_TX_B
mdefine_line|#define M_DUART_IMR_TX_B            _SB_MAKEMASK1(4)
DECL|macro|M_DUART_IMR_RX_B
mdefine_line|#define M_DUART_IMR_RX_B            _SB_MAKEMASK1(5)
DECL|macro|M_DUART_IMR_BRK_B
mdefine_line|#define M_DUART_IMR_BRK_B           _SB_MAKEMASK1(6)
DECL|macro|M_DUART_IMR_IN_B
mdefine_line|#define M_DUART_IMR_IN_B            _SB_MAKEMASK1(7)
DECL|macro|M_DUART_IMR_ALL_B
mdefine_line|#define M_DUART_IMR_ALL_B           _SB_MAKEMASK(4,4)
multiline_comment|/*&n; * DUART Channel A Interrupt Mask Register (Table 10-20)&n; * DUART Channel B Interrupt Mask Register (Table 10-21)&n; * Register: DUART_IMR_A&n; * Register: DUART_IMR_B&n; */
DECL|macro|M_DUART_IMR_TX
mdefine_line|#define M_DUART_IMR_TX              _SB_MAKEMASK1(0)
DECL|macro|M_DUART_IMR_RX
mdefine_line|#define M_DUART_IMR_RX              _SB_MAKEMASK1(1)
DECL|macro|M_DUART_IMR_BRK
mdefine_line|#define M_DUART_IMR_BRK             _SB_MAKEMASK1(2)
DECL|macro|M_DUART_IMR_IN
mdefine_line|#define M_DUART_IMR_IN              _SB_MAKEMASK1(3)
DECL|macro|M_DUART_IMR_ALL
mdefine_line|#define M_DUART_IMR_ALL&t;&t;    _SB_MAKEMASK(4,0)
DECL|macro|M_DUART_IMR_RESERVED
mdefine_line|#define M_DUART_IMR_RESERVED        _SB_MAKEMASK(4,4)
multiline_comment|/*&n; * DUART Output Port Set Register (Table 10-22)&n; * Register: DUART_SET_OPR&n; */
DECL|macro|M_DUART_SET_OPR0
mdefine_line|#define M_DUART_SET_OPR0            _SB_MAKEMASK1(0)
DECL|macro|M_DUART_SET_OPR1
mdefine_line|#define M_DUART_SET_OPR1            _SB_MAKEMASK1(1)
DECL|macro|M_DUART_SET_OPR2
mdefine_line|#define M_DUART_SET_OPR2            _SB_MAKEMASK1(2)
DECL|macro|M_DUART_SET_OPR3
mdefine_line|#define M_DUART_SET_OPR3            _SB_MAKEMASK1(3)
DECL|macro|M_DUART_OPSR_RESERVED
mdefine_line|#define M_DUART_OPSR_RESERVED       _SB_MAKEMASK(4,4)
multiline_comment|/*&n; * DUART Output Port Clear Register (Table 10-23)&n; * Register: DUART_CLEAR_OPR&n; */
DECL|macro|M_DUART_CLR_OPR0
mdefine_line|#define M_DUART_CLR_OPR0            _SB_MAKEMASK1(0)
DECL|macro|M_DUART_CLR_OPR1
mdefine_line|#define M_DUART_CLR_OPR1            _SB_MAKEMASK1(1)
DECL|macro|M_DUART_CLR_OPR2
mdefine_line|#define M_DUART_CLR_OPR2            _SB_MAKEMASK1(2)
DECL|macro|M_DUART_CLR_OPR3
mdefine_line|#define M_DUART_CLR_OPR3            _SB_MAKEMASK1(3)
DECL|macro|M_DUART_OPCR_RESERVED
mdefine_line|#define M_DUART_OPCR_RESERVED       _SB_MAKEMASK(4,4)
multiline_comment|/*&n; * DUART Output Port RTS Register (Table 10-24)&n; * Register: DUART_OUT_PORT&n; */
DECL|macro|M_DUART_OUT_PIN_SET0
mdefine_line|#define M_DUART_OUT_PIN_SET0        _SB_MAKEMASK1(0)
DECL|macro|M_DUART_OUT_PIN_SET1
mdefine_line|#define M_DUART_OUT_PIN_SET1        _SB_MAKEMASK1(1)
DECL|macro|M_DUART_OUT_PIN_CLR0
mdefine_line|#define M_DUART_OUT_PIN_CLR0        _SB_MAKEMASK1(2)
DECL|macro|M_DUART_OUT_PIN_CLR1
mdefine_line|#define M_DUART_OUT_PIN_CLR1        _SB_MAKEMASK1(3)
DECL|macro|M_DUART_OPRR_RESERVED
mdefine_line|#define M_DUART_OPRR_RESERVED       _SB_MAKEMASK(4,4)
DECL|macro|M_DUART_OUT_PIN_SET
mdefine_line|#define M_DUART_OUT_PIN_SET(chan) &bslash;&n;    (chan == 0 ? M_DUART_OUT_PIN_SET0 : M_DUART_OUT_PIN_SET1)
DECL|macro|M_DUART_OUT_PIN_CLR
mdefine_line|#define M_DUART_OUT_PIN_CLR(chan) &bslash;&n;    (chan == 0 ? M_DUART_OUT_PIN_CLR0 : M_DUART_OUT_PIN_CLR1)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
multiline_comment|/* &n; * Full Interrupt Control Register&n; */
DECL|macro|S_DUART_SIG_FULL
mdefine_line|#define S_DUART_SIG_FULL           _SB_MAKE64(0)
DECL|macro|M_DUART_SIG_FULL
mdefine_line|#define M_DUART_SIG_FULL           _SB_MAKEMASK(4,S_DUART_SIG_FULL)
DECL|macro|V_DUART_SIG_FULL
mdefine_line|#define V_DUART_SIG_FULL(x)        _SB_MAKEVALUE(x,S_DUART_SIG_FULL)
DECL|macro|G_DUART_SIG_FULL
mdefine_line|#define G_DUART_SIG_FULL(x)        _SB_GETVALUE(x,S_DUART_SIG_FULL,M_DUART_SIG_FULL)
DECL|macro|S_DUART_INT_TIME
mdefine_line|#define S_DUART_INT_TIME           _SB_MAKE64(4)
DECL|macro|M_DUART_INT_TIME
mdefine_line|#define M_DUART_INT_TIME           _SB_MAKEMASK(4,S_DUART_INT_TIME)
DECL|macro|V_DUART_INT_TIME
mdefine_line|#define V_DUART_INT_TIME(x)        _SB_MAKEVALUE(x,S_DUART_INT_TIME)
DECL|macro|G_DUART_INT_TIME
mdefine_line|#define G_DUART_INT_TIME(x)        _SB_GETVALUE(x,S_DUART_INT_TIME,M_DUART_INT_TIME)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
multiline_comment|/* ********************************************************************** */
macro_line|#endif
eof
