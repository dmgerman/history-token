multiline_comment|/*  *********************************************************************&n;    *  SB1250 Board Support Package&n;    *  &n;    *  Generic Bus Constants                     File: sb1250_genbus.h&n;    *  &n;    *  This module contains constants and macros useful for &n;    *  manipulating the SB1250&squot;s Generic Bus interface&n;    *  &n;    *  SB1250 specification level:  User&squot;s manual 1/02/02&n;    *  &n;    *  Author:  Mitch Lichtenberg&n;    *  &n;    *********************************************************************  &n;    *&n;    *  Copyright 2000,2001,2002,2003&n;    *  Broadcom Corporation. All rights reserved.&n;    *  &n;    *  This program is free software; you can redistribute it and/or &n;    *  modify it under the terms of the GNU General Public License as &n;    *  published by the Free Software Foundation; either version 2 of &n;    *  the License, or (at your option) any later version.&n;    *&n;    *  This program is distributed in the hope that it will be useful,&n;    *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    *  GNU General Public License for more details.&n;    *&n;    *  You should have received a copy of the GNU General Public License&n;    *  along with this program; if not, write to the Free Software&n;    *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n;    *  MA 02111-1307 USA&n;    ********************************************************************* */
macro_line|#ifndef _SB1250_GENBUS_H
DECL|macro|_SB1250_GENBUS_H
mdefine_line|#define _SB1250_GENBUS_H
macro_line|#include &quot;sb1250_defs.h&quot;
multiline_comment|/*&n; * Generic Bus Region Configuration Registers (Table 11-4)&n; */
DECL|macro|S_IO_RDY_ACTIVE
mdefine_line|#define S_IO_RDY_ACTIVE         0
DECL|macro|M_IO_RDY_ACTIVE
mdefine_line|#define M_IO_RDY_ACTIVE&t;&t;_SB_MAKEMASK1(S_IO_RDY_ACTIVE)
DECL|macro|S_IO_ENA_RDY
mdefine_line|#define S_IO_ENA_RDY            1
DECL|macro|M_IO_ENA_RDY
mdefine_line|#define M_IO_ENA_RDY&t;&t;_SB_MAKEMASK1(S_IO_ENA_RDY)
DECL|macro|S_IO_WIDTH_SEL
mdefine_line|#define S_IO_WIDTH_SEL&t;&t;2
DECL|macro|M_IO_WIDTH_SEL
mdefine_line|#define M_IO_WIDTH_SEL&t;&t;_SB_MAKEMASK(2,S_IO_WIDTH_SEL)
DECL|macro|K_IO_WIDTH_SEL_1
mdefine_line|#define K_IO_WIDTH_SEL_1&t;0
DECL|macro|K_IO_WIDTH_SEL_2
mdefine_line|#define K_IO_WIDTH_SEL_2&t;1
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|K_IO_WIDTH_SEL_1L
mdefine_line|#define K_IO_WIDTH_SEL_1L       2
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
DECL|macro|K_IO_WIDTH_SEL_4
mdefine_line|#define K_IO_WIDTH_SEL_4&t;3
DECL|macro|V_IO_WIDTH_SEL
mdefine_line|#define V_IO_WIDTH_SEL(x)&t;_SB_MAKEVALUE(x,S_IO_WIDTH_SEL)
DECL|macro|G_IO_WIDTH_SEL
mdefine_line|#define G_IO_WIDTH_SEL(x)&t;_SB_GETVALUE(x,S_IO_WIDTH_SEL,M_IO_WIDTH_SEL)
DECL|macro|S_IO_PARITY_ENA
mdefine_line|#define S_IO_PARITY_ENA&t;&t;4
DECL|macro|M_IO_PARITY_ENA
mdefine_line|#define M_IO_PARITY_ENA&t;&t;_SB_MAKEMASK1(S_IO_PARITY_ENA)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|S_IO_BURST_EN
mdefine_line|#define S_IO_BURST_EN&t;&t;5
DECL|macro|M_IO_BURST_EN
mdefine_line|#define M_IO_BURST_EN&t;&t;_SB_MAKEMASK1(S_IO_BURST_EN)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
DECL|macro|S_IO_PARITY_ODD
mdefine_line|#define S_IO_PARITY_ODD&t;&t;6
DECL|macro|M_IO_PARITY_ODD
mdefine_line|#define M_IO_PARITY_ODD&t;&t;_SB_MAKEMASK1(S_IO_PARITY_ODD)
DECL|macro|S_IO_NONMUX
mdefine_line|#define S_IO_NONMUX&t;&t;7
DECL|macro|M_IO_NONMUX
mdefine_line|#define M_IO_NONMUX&t;&t;_SB_MAKEMASK1(S_IO_NONMUX)
DECL|macro|S_IO_TIMEOUT
mdefine_line|#define S_IO_TIMEOUT&t;&t;8
DECL|macro|M_IO_TIMEOUT
mdefine_line|#define M_IO_TIMEOUT&t;&t;_SB_MAKEMASK(8,S_IO_TIMEOUT)
DECL|macro|V_IO_TIMEOUT
mdefine_line|#define V_IO_TIMEOUT(x)&t;&t;_SB_MAKEVALUE(x,S_IO_TIMEOUT)
DECL|macro|G_IO_TIMEOUT
mdefine_line|#define G_IO_TIMEOUT(x)&t;&t;_SB_GETVALUE(x,S_IO_TIMEOUT,M_IO_TIMEOUT)
multiline_comment|/*&n; * Generic Bus Region Size register (Table 11-5)&n; */
DECL|macro|S_IO_MULT_SIZE
mdefine_line|#define S_IO_MULT_SIZE&t;&t;0
DECL|macro|M_IO_MULT_SIZE
mdefine_line|#define M_IO_MULT_SIZE&t;&t;_SB_MAKEMASK(12,S_IO_MULT_SIZE)
DECL|macro|V_IO_MULT_SIZE
mdefine_line|#define V_IO_MULT_SIZE(x)&t;_SB_MAKEVALUE(x,S_IO_MULT_SIZE)
DECL|macro|G_IO_MULT_SIZE
mdefine_line|#define G_IO_MULT_SIZE(x)&t;_SB_GETVALUE(x,S_IO_MULT_SIZE,M_IO_MULT_SIZE)
DECL|macro|S_IO_REGSIZE
mdefine_line|#define S_IO_REGSIZE&t;&t;16&t; /* # bits to shift size for this reg */
multiline_comment|/*&n; * Generic Bus Region Address (Table 11-6)&n; */
DECL|macro|S_IO_START_ADDR
mdefine_line|#define S_IO_START_ADDR&t;&t;0
DECL|macro|M_IO_START_ADDR
mdefine_line|#define M_IO_START_ADDR&t;&t;_SB_MAKEMASK(14,S_IO_START_ADDR)
DECL|macro|V_IO_START_ADDR
mdefine_line|#define V_IO_START_ADDR(x)&t;_SB_MAKEVALUE(x,S_IO_START_ADDR)
DECL|macro|G_IO_START_ADDR
mdefine_line|#define G_IO_START_ADDR(x)&t;_SB_GETVALUE(x,S_IO_START_ADDR,M_IO_START_ADDR)
DECL|macro|S_IO_ADDRBASE
mdefine_line|#define S_IO_ADDRBASE&t;&t;16&t; /* # bits to shift addr for this reg */
multiline_comment|/*&n; * Generic Bus Region 0 Timing Registers (Table 11-7)&n; */
DECL|macro|S_IO_ALE_WIDTH
mdefine_line|#define S_IO_ALE_WIDTH&t;&t;0
DECL|macro|M_IO_ALE_WIDTH
mdefine_line|#define M_IO_ALE_WIDTH&t;&t;_SB_MAKEMASK(3,S_IO_ALE_WIDTH)
DECL|macro|V_IO_ALE_WIDTH
mdefine_line|#define V_IO_ALE_WIDTH(x)&t;_SB_MAKEVALUE(x,S_IO_ALE_WIDTH)
DECL|macro|G_IO_ALE_WIDTH
mdefine_line|#define G_IO_ALE_WIDTH(x)&t;_SB_GETVALUE(x,S_IO_ALE_WIDTH,M_IO_ALE_WIDTH)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_IO_EARLY_CS
mdefine_line|#define M_IO_EARLY_CS&t;        _SB_MAKEMASK1(3)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
DECL|macro|S_IO_ALE_TO_CS
mdefine_line|#define S_IO_ALE_TO_CS&t;&t;4
DECL|macro|M_IO_ALE_TO_CS
mdefine_line|#define M_IO_ALE_TO_CS&t;&t;_SB_MAKEMASK(2,S_IO_ALE_TO_CS)
DECL|macro|V_IO_ALE_TO_CS
mdefine_line|#define V_IO_ALE_TO_CS(x)&t;_SB_MAKEVALUE(x,S_IO_ALE_TO_CS)
DECL|macro|G_IO_ALE_TO_CS
mdefine_line|#define G_IO_ALE_TO_CS(x)&t;_SB_GETVALUE(x,S_IO_ALE_TO_CS,M_IO_ALE_TO_CS)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|S_IO_BURST_WIDTH
mdefine_line|#define S_IO_BURST_WIDTH           _SB_MAKE64(6)
DECL|macro|M_IO_BURST_WIDTH
mdefine_line|#define M_IO_BURST_WIDTH           _SB_MAKEMASK(2,S_IO_BURST_WIDTH)
DECL|macro|V_IO_BURST_WIDTH
mdefine_line|#define V_IO_BURST_WIDTH(x)        _SB_MAKEVALUE(x,S_IO_BURST_WIDTH)
DECL|macro|G_IO_BURST_WIDTH
mdefine_line|#define G_IO_BURST_WIDTH(x)        _SB_GETVALUE(x,S_IO_BURST_WIDTH,M_IO_BURST_WIDTH)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
DECL|macro|S_IO_CS_WIDTH
mdefine_line|#define S_IO_CS_WIDTH&t;&t;8
DECL|macro|M_IO_CS_WIDTH
mdefine_line|#define M_IO_CS_WIDTH&t;&t;_SB_MAKEMASK(5,S_IO_CS_WIDTH)
DECL|macro|V_IO_CS_WIDTH
mdefine_line|#define V_IO_CS_WIDTH(x)&t;_SB_MAKEVALUE(x,S_IO_CS_WIDTH)
DECL|macro|G_IO_CS_WIDTH
mdefine_line|#define G_IO_CS_WIDTH(x)&t;_SB_GETVALUE(x,S_IO_CS_WIDTH,M_IO_CS_WIDTH)
DECL|macro|S_IO_RDY_SMPLE
mdefine_line|#define S_IO_RDY_SMPLE&t;&t;13
DECL|macro|M_IO_RDY_SMPLE
mdefine_line|#define M_IO_RDY_SMPLE&t;&t;_SB_MAKEMASK(3,S_IO_RDY_SMPLE)
DECL|macro|V_IO_RDY_SMPLE
mdefine_line|#define V_IO_RDY_SMPLE(x)&t;_SB_MAKEVALUE(x,S_IO_RDY_SMPLE)
DECL|macro|G_IO_RDY_SMPLE
mdefine_line|#define G_IO_RDY_SMPLE(x)&t;_SB_GETVALUE(x,S_IO_RDY_SMPLE,M_IO_RDY_SMPLE)
multiline_comment|/*&n; * Generic Bus Timing 1 Registers (Table 11-8)&n; */
DECL|macro|S_IO_ALE_TO_WRITE
mdefine_line|#define S_IO_ALE_TO_WRITE&t;0
DECL|macro|M_IO_ALE_TO_WRITE
mdefine_line|#define M_IO_ALE_TO_WRITE&t;_SB_MAKEMASK(3,S_IO_ALE_TO_WRITE)
DECL|macro|V_IO_ALE_TO_WRITE
mdefine_line|#define V_IO_ALE_TO_WRITE(x)&t;_SB_MAKEVALUE(x,S_IO_ALE_TO_WRITE)
DECL|macro|G_IO_ALE_TO_WRITE
mdefine_line|#define G_IO_ALE_TO_WRITE(x)&t;_SB_GETVALUE(x,S_IO_ALE_TO_WRITE,M_IO_ALE_TO_WRITE)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_IO_RDY_SYNC
mdefine_line|#define M_IO_RDY_SYNC&t;        _SB_MAKEMASK1(3)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
DECL|macro|S_IO_WRITE_WIDTH
mdefine_line|#define S_IO_WRITE_WIDTH&t;4
DECL|macro|M_IO_WRITE_WIDTH
mdefine_line|#define M_IO_WRITE_WIDTH&t;_SB_MAKEMASK(4,S_IO_WRITE_WIDTH)
DECL|macro|V_IO_WRITE_WIDTH
mdefine_line|#define V_IO_WRITE_WIDTH(x)&t;_SB_MAKEVALUE(x,S_IO_WRITE_WIDTH)
DECL|macro|G_IO_WRITE_WIDTH
mdefine_line|#define G_IO_WRITE_WIDTH(x)&t;_SB_GETVALUE(x,S_IO_WRITE_WIDTH,M_IO_WRITE_WIDTH)
DECL|macro|S_IO_IDLE_CYCLE
mdefine_line|#define S_IO_IDLE_CYCLE&t;&t;8
DECL|macro|M_IO_IDLE_CYCLE
mdefine_line|#define M_IO_IDLE_CYCLE&t;&t;_SB_MAKEMASK(4,S_IO_IDLE_CYCLE)
DECL|macro|V_IO_IDLE_CYCLE
mdefine_line|#define V_IO_IDLE_CYCLE(x)&t;_SB_MAKEVALUE(x,S_IO_IDLE_CYCLE)
DECL|macro|G_IO_IDLE_CYCLE
mdefine_line|#define G_IO_IDLE_CYCLE(x)&t;_SB_GETVALUE(x,S_IO_IDLE_CYCLE,M_IO_IDLE_CYCLE)
DECL|macro|S_IO_OE_TO_CS
mdefine_line|#define S_IO_OE_TO_CS&t;&t;12
DECL|macro|M_IO_OE_TO_CS
mdefine_line|#define M_IO_OE_TO_CS&t;&t;_SB_MAKEMASK(2,S_IO_OE_TO_CS)
DECL|macro|V_IO_OE_TO_CS
mdefine_line|#define V_IO_OE_TO_CS(x)&t;_SB_MAKEVALUE(x,S_IO_OE_TO_CS)
DECL|macro|G_IO_OE_TO_CS
mdefine_line|#define G_IO_OE_TO_CS(x)&t;_SB_GETVALUE(x,S_IO_OE_TO_CS,M_IO_OE_TO_CS)
DECL|macro|S_IO_CS_TO_OE
mdefine_line|#define S_IO_CS_TO_OE&t;&t;14
DECL|macro|M_IO_CS_TO_OE
mdefine_line|#define M_IO_CS_TO_OE&t;&t;_SB_MAKEMASK(2,S_IO_CS_TO_OE)
DECL|macro|V_IO_CS_TO_OE
mdefine_line|#define V_IO_CS_TO_OE(x)&t;_SB_MAKEVALUE(x,S_IO_CS_TO_OE)
DECL|macro|G_IO_CS_TO_OE
mdefine_line|#define G_IO_CS_TO_OE(x)&t;_SB_GETVALUE(x,S_IO_CS_TO_OE,M_IO_CS_TO_OE)
multiline_comment|/*&n; * Generic Bus Interrupt Status Register (Table 11-9)&n; */
DECL|macro|M_IO_CS_ERR_INT
mdefine_line|#define M_IO_CS_ERR_INT&t;&t;_SB_MAKEMASK(0,8)
DECL|macro|M_IO_CS0_ERR_INT
mdefine_line|#define M_IO_CS0_ERR_INT&t;_SB_MAKEMASK1(0)
DECL|macro|M_IO_CS1_ERR_INT
mdefine_line|#define M_IO_CS1_ERR_INT&t;_SB_MAKEMASK1(1)
DECL|macro|M_IO_CS2_ERR_INT
mdefine_line|#define M_IO_CS2_ERR_INT&t;_SB_MAKEMASK1(2)
DECL|macro|M_IO_CS3_ERR_INT
mdefine_line|#define M_IO_CS3_ERR_INT&t;_SB_MAKEMASK1(3)
DECL|macro|M_IO_CS4_ERR_INT
mdefine_line|#define M_IO_CS4_ERR_INT&t;_SB_MAKEMASK1(4)
DECL|macro|M_IO_CS5_ERR_INT
mdefine_line|#define M_IO_CS5_ERR_INT&t;_SB_MAKEMASK1(5)
DECL|macro|M_IO_CS6_ERR_INT
mdefine_line|#define M_IO_CS6_ERR_INT&t;_SB_MAKEMASK1(6)
DECL|macro|M_IO_CS7_ERR_INT
mdefine_line|#define M_IO_CS7_ERR_INT&t;_SB_MAKEMASK1(7)
DECL|macro|M_IO_RD_PAR_INT
mdefine_line|#define M_IO_RD_PAR_INT&t;&t;_SB_MAKEMASK1(9)
DECL|macro|M_IO_TIMEOUT_INT
mdefine_line|#define M_IO_TIMEOUT_INT&t;_SB_MAKEMASK1(10)
DECL|macro|M_IO_ILL_ADDR_INT
mdefine_line|#define M_IO_ILL_ADDR_INT&t;_SB_MAKEMASK1(11)
DECL|macro|M_IO_MULT_CS_INT
mdefine_line|#define M_IO_MULT_CS_INT&t;_SB_MAKEMASK1(12)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_IO_COH_ERR
mdefine_line|#define M_IO_COH_ERR&t;        _SB_MAKEMASK1(14)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
multiline_comment|/*&n; * PCMCIA configuration register (Table 12-6)&n; */
DECL|macro|M_PCMCIA_CFG_ATTRMEM
mdefine_line|#define M_PCMCIA_CFG_ATTRMEM&t;_SB_MAKEMASK1(0)
DECL|macro|M_PCMCIA_CFG_3VEN
mdefine_line|#define M_PCMCIA_CFG_3VEN&t;_SB_MAKEMASK1(1)
DECL|macro|M_PCMCIA_CFG_5VEN
mdefine_line|#define M_PCMCIA_CFG_5VEN&t;_SB_MAKEMASK1(2)
DECL|macro|M_PCMCIA_CFG_VPPEN
mdefine_line|#define M_PCMCIA_CFG_VPPEN&t;_SB_MAKEMASK1(3)
DECL|macro|M_PCMCIA_CFG_RESET
mdefine_line|#define M_PCMCIA_CFG_RESET&t;_SB_MAKEMASK1(4)
DECL|macro|M_PCMCIA_CFG_APWRONEN
mdefine_line|#define M_PCMCIA_CFG_APWRONEN&t;_SB_MAKEMASK1(5)
DECL|macro|M_PCMCIA_CFG_CDMASK
mdefine_line|#define M_PCMCIA_CFG_CDMASK&t;_SB_MAKEMASK1(6)
DECL|macro|M_PCMCIA_CFG_WPMASK
mdefine_line|#define M_PCMCIA_CFG_WPMASK&t;_SB_MAKEMASK1(7)
DECL|macro|M_PCMCIA_CFG_RDYMASK
mdefine_line|#define M_PCMCIA_CFG_RDYMASK&t;_SB_MAKEMASK1(8)
DECL|macro|M_PCMCIA_CFG_PWRCTL
mdefine_line|#define M_PCMCIA_CFG_PWRCTL&t;_SB_MAKEMASK1(9)
multiline_comment|/*&n; * PCMCIA status register (Table 12-7)&n; */
DECL|macro|M_PCMCIA_STATUS_CD1
mdefine_line|#define M_PCMCIA_STATUS_CD1&t;_SB_MAKEMASK1(0)
DECL|macro|M_PCMCIA_STATUS_CD2
mdefine_line|#define M_PCMCIA_STATUS_CD2&t;_SB_MAKEMASK1(1)
DECL|macro|M_PCMCIA_STATUS_VS1
mdefine_line|#define M_PCMCIA_STATUS_VS1&t;_SB_MAKEMASK1(2)
DECL|macro|M_PCMCIA_STATUS_VS2
mdefine_line|#define M_PCMCIA_STATUS_VS2&t;_SB_MAKEMASK1(3)
DECL|macro|M_PCMCIA_STATUS_WP
mdefine_line|#define M_PCMCIA_STATUS_WP&t;_SB_MAKEMASK1(4)
DECL|macro|M_PCMCIA_STATUS_RDY
mdefine_line|#define M_PCMCIA_STATUS_RDY&t;_SB_MAKEMASK1(5)
DECL|macro|M_PCMCIA_STATUS_3VEN
mdefine_line|#define M_PCMCIA_STATUS_3VEN&t;_SB_MAKEMASK1(6)
DECL|macro|M_PCMCIA_STATUS_5VEN
mdefine_line|#define M_PCMCIA_STATUS_5VEN&t;_SB_MAKEMASK1(7)
DECL|macro|M_PCMCIA_STATUS_CDCHG
mdefine_line|#define M_PCMCIA_STATUS_CDCHG&t;_SB_MAKEMASK1(8)
DECL|macro|M_PCMCIA_STATUS_WPCHG
mdefine_line|#define M_PCMCIA_STATUS_WPCHG&t;_SB_MAKEMASK1(9)
DECL|macro|M_PCMCIA_STATUS_RDYCHG
mdefine_line|#define M_PCMCIA_STATUS_RDYCHG&t;_SB_MAKEMASK1(10)
multiline_comment|/*&n; * GPIO Interrupt Type Register (table 13-3)&n; */
DECL|macro|K_GPIO_INTR_DISABLE
mdefine_line|#define K_GPIO_INTR_DISABLE&t;0
DECL|macro|K_GPIO_INTR_EDGE
mdefine_line|#define K_GPIO_INTR_EDGE&t;1
DECL|macro|K_GPIO_INTR_LEVEL
mdefine_line|#define K_GPIO_INTR_LEVEL&t;2
DECL|macro|K_GPIO_INTR_SPLIT
mdefine_line|#define K_GPIO_INTR_SPLIT&t;3
DECL|macro|S_GPIO_INTR_TYPEX
mdefine_line|#define S_GPIO_INTR_TYPEX(n)&t;(((n)/2)*2)
DECL|macro|M_GPIO_INTR_TYPEX
mdefine_line|#define M_GPIO_INTR_TYPEX(n)&t;_SB_MAKEMASK(2,S_GPIO_INTR_TYPEX(n))
DECL|macro|V_GPIO_INTR_TYPEX
mdefine_line|#define V_GPIO_INTR_TYPEX(n,x)&t;_SB_MAKEVALUE(x,S_GPIO_INTR_TYPEX(n))
DECL|macro|G_GPIO_INTR_TYPEX
mdefine_line|#define G_GPIO_INTR_TYPEX(n,x)&t;_SB_GETVALUE(x,S_GPIO_INTR_TYPEX(n),M_GPIO_INTR_TYPEX(n))
DECL|macro|S_GPIO_INTR_TYPE0
mdefine_line|#define S_GPIO_INTR_TYPE0&t;0
DECL|macro|M_GPIO_INTR_TYPE0
mdefine_line|#define M_GPIO_INTR_TYPE0&t;_SB_MAKEMASK(2,S_GPIO_INTR_TYPE0)
DECL|macro|V_GPIO_INTR_TYPE0
mdefine_line|#define V_GPIO_INTR_TYPE0(x)&t;_SB_MAKEVALUE(x,S_GPIO_INTR_TYPE0)
DECL|macro|G_GPIO_INTR_TYPE0
mdefine_line|#define G_GPIO_INTR_TYPE0(x)&t;_SB_GETVALUE(x,S_GPIO_INTR_TYPE0,M_GPIO_INTR_TYPE0)
DECL|macro|S_GPIO_INTR_TYPE2
mdefine_line|#define S_GPIO_INTR_TYPE2&t;2
DECL|macro|M_GPIO_INTR_TYPE2
mdefine_line|#define M_GPIO_INTR_TYPE2&t;_SB_MAKEMASK(2,S_GPIO_INTR_TYPE2)
DECL|macro|V_GPIO_INTR_TYPE2
mdefine_line|#define V_GPIO_INTR_TYPE2(x)&t;_SB_MAKEVALUE(x,S_GPIO_INTR_TYPE2)
DECL|macro|G_GPIO_INTR_TYPE2
mdefine_line|#define G_GPIO_INTR_TYPE2(x)&t;_SB_GETVALUE(x,S_GPIO_INTR_TYPE2,M_GPIO_INTR_TYPE2)
DECL|macro|S_GPIO_INTR_TYPE4
mdefine_line|#define S_GPIO_INTR_TYPE4&t;4
DECL|macro|M_GPIO_INTR_TYPE4
mdefine_line|#define M_GPIO_INTR_TYPE4&t;_SB_MAKEMASK(2,S_GPIO_INTR_TYPE4)
DECL|macro|V_GPIO_INTR_TYPE4
mdefine_line|#define V_GPIO_INTR_TYPE4(x)&t;_SB_MAKEVALUE(x,S_GPIO_INTR_TYPE4)
DECL|macro|G_GPIO_INTR_TYPE4
mdefine_line|#define G_GPIO_INTR_TYPE4(x)&t;_SB_GETVALUE(x,S_GPIO_INTR_TYPE4,M_GPIO_INTR_TYPE4)
DECL|macro|S_GPIO_INTR_TYPE6
mdefine_line|#define S_GPIO_INTR_TYPE6&t;6
DECL|macro|M_GPIO_INTR_TYPE6
mdefine_line|#define M_GPIO_INTR_TYPE6&t;_SB_MAKEMASK(2,S_GPIO_INTR_TYPE6)
DECL|macro|V_GPIO_INTR_TYPE6
mdefine_line|#define V_GPIO_INTR_TYPE6(x)&t;_SB_MAKEVALUE(x,S_GPIO_INTR_TYPE6)
DECL|macro|G_GPIO_INTR_TYPE6
mdefine_line|#define G_GPIO_INTR_TYPE6(x)&t;_SB_GETVALUE(x,S_GPIO_INTR_TYPE6,M_GPIO_INTR_TYPE6)
DECL|macro|S_GPIO_INTR_TYPE8
mdefine_line|#define S_GPIO_INTR_TYPE8&t;8
DECL|macro|M_GPIO_INTR_TYPE8
mdefine_line|#define M_GPIO_INTR_TYPE8&t;_SB_MAKEMASK(2,S_GPIO_INTR_TYPE8)
DECL|macro|V_GPIO_INTR_TYPE8
mdefine_line|#define V_GPIO_INTR_TYPE8(x)&t;_SB_MAKEVALUE(x,S_GPIO_INTR_TYPE8)
DECL|macro|G_GPIO_INTR_TYPE8
mdefine_line|#define G_GPIO_INTR_TYPE8(x)&t;_SB_GETVALUE(x,S_GPIO_INTR_TYPE8,M_GPIO_INTR_TYPE8)
DECL|macro|S_GPIO_INTR_TYPE10
mdefine_line|#define S_GPIO_INTR_TYPE10&t;10
DECL|macro|M_GPIO_INTR_TYPE10
mdefine_line|#define M_GPIO_INTR_TYPE10&t;_SB_MAKEMASK(2,S_GPIO_INTR_TYPE10)
DECL|macro|V_GPIO_INTR_TYPE10
mdefine_line|#define V_GPIO_INTR_TYPE10(x)&t;_SB_MAKEVALUE(x,S_GPIO_INTR_TYPE10)
DECL|macro|G_GPIO_INTR_TYPE10
mdefine_line|#define G_GPIO_INTR_TYPE10(x)&t;_SB_GETVALUE(x,S_GPIO_INTR_TYPE10,M_GPIO_INTR_TYPE10)
DECL|macro|S_GPIO_INTR_TYPE12
mdefine_line|#define S_GPIO_INTR_TYPE12&t;12
DECL|macro|M_GPIO_INTR_TYPE12
mdefine_line|#define M_GPIO_INTR_TYPE12&t;_SB_MAKEMASK(2,S_GPIO_INTR_TYPE12)
DECL|macro|V_GPIO_INTR_TYPE12
mdefine_line|#define V_GPIO_INTR_TYPE12(x)&t;_SB_MAKEVALUE(x,S_GPIO_INTR_TYPE12)
DECL|macro|G_GPIO_INTR_TYPE12
mdefine_line|#define G_GPIO_INTR_TYPE12(x)&t;_SB_GETVALUE(x,S_GPIO_INTR_TYPE12,M_GPIO_INTR_TYPE12)
DECL|macro|S_GPIO_INTR_TYPE14
mdefine_line|#define S_GPIO_INTR_TYPE14&t;14
DECL|macro|M_GPIO_INTR_TYPE14
mdefine_line|#define M_GPIO_INTR_TYPE14&t;_SB_MAKEMASK(2,S_GPIO_INTR_TYPE14)
DECL|macro|V_GPIO_INTR_TYPE14
mdefine_line|#define V_GPIO_INTR_TYPE14(x)&t;_SB_MAKEVALUE(x,S_GPIO_INTR_TYPE14)
DECL|macro|G_GPIO_INTR_TYPE14
mdefine_line|#define G_GPIO_INTR_TYPE14(x)&t;_SB_GETVALUE(x,S_GPIO_INTR_TYPE14,M_GPIO_INTR_TYPE14)
macro_line|#endif
eof
