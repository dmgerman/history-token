multiline_comment|/*  *********************************************************************&n;    *  SB1250 Board Support Package&n;    *  &n;    *  Interrupt Mapper definitions&t;&t;File: sb1250_int.h&n;    *  &n;    *  This module contains constants for manipulating the SB1250&squot;s&n;    *  interrupt mapper and definitions for the interrupt sources.&n;    *  &n;    *  SB1250 specification level:  User&squot;s manual 1/02/02&n;    *  &n;    *  Author:  Mitch Lichtenberg&n;    *  &n;    *********************************************************************  &n;    *&n;    *  Copyright 2000,2001,2002,2003&n;    *  Broadcom Corporation. All rights reserved.&n;    *  &n;    *  This program is free software; you can redistribute it and/or &n;    *  modify it under the terms of the GNU General Public License as &n;    *  published by the Free Software Foundation; either version 2 of &n;    *  the License, or (at your option) any later version.&n;    *&n;    *  This program is distributed in the hope that it will be useful,&n;    *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    *  GNU General Public License for more details.&n;    *&n;    *  You should have received a copy of the GNU General Public License&n;    *  along with this program; if not, write to the Free Software&n;    *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n;    *  MA 02111-1307 USA&n;    ********************************************************************* */
macro_line|#ifndef _SB1250_INT_H
DECL|macro|_SB1250_INT_H
mdefine_line|#define _SB1250_INT_H
macro_line|#include &quot;sb1250_defs.h&quot;
multiline_comment|/*  *********************************************************************&n;    *  Interrupt Mapper Constants&n;    ********************************************************************* */
multiline_comment|/*&n; * Interrupt sources (Table 4-8, UM 0.2)&n; * &n; * First, the interrupt numbers.&n; */
DECL|macro|K_INT_WATCHDOG_TIMER_0
mdefine_line|#define K_INT_WATCHDOG_TIMER_0      0
DECL|macro|K_INT_WATCHDOG_TIMER_1
mdefine_line|#define K_INT_WATCHDOG_TIMER_1      1
DECL|macro|K_INT_TIMER_0
mdefine_line|#define K_INT_TIMER_0               2
DECL|macro|K_INT_TIMER_1
mdefine_line|#define K_INT_TIMER_1               3
DECL|macro|K_INT_TIMER_2
mdefine_line|#define K_INT_TIMER_2               4
DECL|macro|K_INT_TIMER_3
mdefine_line|#define K_INT_TIMER_3               5
DECL|macro|K_INT_SMB_0
mdefine_line|#define K_INT_SMB_0                 6
DECL|macro|K_INT_SMB_1
mdefine_line|#define K_INT_SMB_1                 7
DECL|macro|K_INT_UART_0
mdefine_line|#define K_INT_UART_0                8
DECL|macro|K_INT_UART_1
mdefine_line|#define K_INT_UART_1                9
DECL|macro|K_INT_SER_0
mdefine_line|#define K_INT_SER_0                 10
DECL|macro|K_INT_SER_1
mdefine_line|#define K_INT_SER_1                 11
DECL|macro|K_INT_PCMCIA
mdefine_line|#define K_INT_PCMCIA                12
DECL|macro|K_INT_ADDR_TRAP
mdefine_line|#define K_INT_ADDR_TRAP             13
DECL|macro|K_INT_PERF_CNT
mdefine_line|#define K_INT_PERF_CNT              14
DECL|macro|K_INT_TRACE_FREEZE
mdefine_line|#define K_INT_TRACE_FREEZE          15
DECL|macro|K_INT_BAD_ECC
mdefine_line|#define K_INT_BAD_ECC               16
DECL|macro|K_INT_COR_ECC
mdefine_line|#define K_INT_COR_ECC               17
DECL|macro|K_INT_IO_BUS
mdefine_line|#define K_INT_IO_BUS                18
DECL|macro|K_INT_MAC_0
mdefine_line|#define K_INT_MAC_0                 19
DECL|macro|K_INT_MAC_1
mdefine_line|#define K_INT_MAC_1                 20
DECL|macro|K_INT_MAC_2
mdefine_line|#define K_INT_MAC_2                 21
DECL|macro|K_INT_DM_CH_0
mdefine_line|#define K_INT_DM_CH_0               22
DECL|macro|K_INT_DM_CH_1
mdefine_line|#define K_INT_DM_CH_1               23
DECL|macro|K_INT_DM_CH_2
mdefine_line|#define K_INT_DM_CH_2               24
DECL|macro|K_INT_DM_CH_3
mdefine_line|#define K_INT_DM_CH_3               25
DECL|macro|K_INT_MBOX_0
mdefine_line|#define K_INT_MBOX_0                26
DECL|macro|K_INT_MBOX_1
mdefine_line|#define K_INT_MBOX_1                27
DECL|macro|K_INT_MBOX_2
mdefine_line|#define K_INT_MBOX_2                28
DECL|macro|K_INT_MBOX_3
mdefine_line|#define K_INT_MBOX_3                29
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|K_INT_CYCLE_CP0_INT
mdefine_line|#define K_INT_CYCLE_CP0_INT&t;    30
DECL|macro|K_INT_CYCLE_CP1_INT
mdefine_line|#define K_INT_CYCLE_CP1_INT&t;    31
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
DECL|macro|K_INT_GPIO_0
mdefine_line|#define K_INT_GPIO_0                32
DECL|macro|K_INT_GPIO_1
mdefine_line|#define K_INT_GPIO_1                33
DECL|macro|K_INT_GPIO_2
mdefine_line|#define K_INT_GPIO_2                34
DECL|macro|K_INT_GPIO_3
mdefine_line|#define K_INT_GPIO_3                35
DECL|macro|K_INT_GPIO_4
mdefine_line|#define K_INT_GPIO_4                36
DECL|macro|K_INT_GPIO_5
mdefine_line|#define K_INT_GPIO_5                37
DECL|macro|K_INT_GPIO_6
mdefine_line|#define K_INT_GPIO_6                38
DECL|macro|K_INT_GPIO_7
mdefine_line|#define K_INT_GPIO_7                39
DECL|macro|K_INT_GPIO_8
mdefine_line|#define K_INT_GPIO_8                40
DECL|macro|K_INT_GPIO_9
mdefine_line|#define K_INT_GPIO_9                41
DECL|macro|K_INT_GPIO_10
mdefine_line|#define K_INT_GPIO_10               42
DECL|macro|K_INT_GPIO_11
mdefine_line|#define K_INT_GPIO_11               43
DECL|macro|K_INT_GPIO_12
mdefine_line|#define K_INT_GPIO_12               44
DECL|macro|K_INT_GPIO_13
mdefine_line|#define K_INT_GPIO_13               45
DECL|macro|K_INT_GPIO_14
mdefine_line|#define K_INT_GPIO_14               46
DECL|macro|K_INT_GPIO_15
mdefine_line|#define K_INT_GPIO_15               47
DECL|macro|K_INT_LDT_FATAL
mdefine_line|#define K_INT_LDT_FATAL             48
DECL|macro|K_INT_LDT_NONFATAL
mdefine_line|#define K_INT_LDT_NONFATAL          49
DECL|macro|K_INT_LDT_SMI
mdefine_line|#define K_INT_LDT_SMI               50
DECL|macro|K_INT_LDT_NMI
mdefine_line|#define K_INT_LDT_NMI               51
DECL|macro|K_INT_LDT_INIT
mdefine_line|#define K_INT_LDT_INIT              52
DECL|macro|K_INT_LDT_STARTUP
mdefine_line|#define K_INT_LDT_STARTUP           53
DECL|macro|K_INT_LDT_EXT
mdefine_line|#define K_INT_LDT_EXT               54
DECL|macro|K_INT_PCI_ERROR
mdefine_line|#define K_INT_PCI_ERROR             55
DECL|macro|K_INT_PCI_INTA
mdefine_line|#define K_INT_PCI_INTA              56
DECL|macro|K_INT_PCI_INTB
mdefine_line|#define K_INT_PCI_INTB              57
DECL|macro|K_INT_PCI_INTC
mdefine_line|#define K_INT_PCI_INTC              58
DECL|macro|K_INT_PCI_INTD
mdefine_line|#define K_INT_PCI_INTD              59
DECL|macro|K_INT_SPARE_2
mdefine_line|#define K_INT_SPARE_2               60
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|K_INT_MAC_0_CH1
mdefine_line|#define K_INT_MAC_0_CH1&t;&t;    61
DECL|macro|K_INT_MAC_1_CH1
mdefine_line|#define K_INT_MAC_1_CH1&t;&t;    62
DECL|macro|K_INT_MAC_2_CH1
mdefine_line|#define K_INT_MAC_2_CH1&t;&t;    63
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
multiline_comment|/*&n; * Mask values for each interrupt&n; */
DECL|macro|M_INT_WATCHDOG_TIMER_0
mdefine_line|#define M_INT_WATCHDOG_TIMER_0      _SB_MAKEMASK1(K_INT_WATCHDOG_TIMER_0)
DECL|macro|M_INT_WATCHDOG_TIMER_1
mdefine_line|#define M_INT_WATCHDOG_TIMER_1      _SB_MAKEMASK1(K_INT_WATCHDOG_TIMER_1)
DECL|macro|M_INT_TIMER_0
mdefine_line|#define M_INT_TIMER_0               _SB_MAKEMASK1(K_INT_TIMER_0)
DECL|macro|M_INT_TIMER_1
mdefine_line|#define M_INT_TIMER_1               _SB_MAKEMASK1(K_INT_TIMER_1)
DECL|macro|M_INT_TIMER_2
mdefine_line|#define M_INT_TIMER_2               _SB_MAKEMASK1(K_INT_TIMER_2)
DECL|macro|M_INT_TIMER_3
mdefine_line|#define M_INT_TIMER_3               _SB_MAKEMASK1(K_INT_TIMER_3)
DECL|macro|M_INT_SMB_0
mdefine_line|#define M_INT_SMB_0                 _SB_MAKEMASK1(K_INT_SMB_0)
DECL|macro|M_INT_SMB_1
mdefine_line|#define M_INT_SMB_1                 _SB_MAKEMASK1(K_INT_SMB_1)
DECL|macro|M_INT_UART_0
mdefine_line|#define M_INT_UART_0                _SB_MAKEMASK1(K_INT_UART_0)
DECL|macro|M_INT_UART_1
mdefine_line|#define M_INT_UART_1                _SB_MAKEMASK1(K_INT_UART_1)
DECL|macro|M_INT_SER_0
mdefine_line|#define M_INT_SER_0                 _SB_MAKEMASK1(K_INT_SER_0)
DECL|macro|M_INT_SER_1
mdefine_line|#define M_INT_SER_1                 _SB_MAKEMASK1(K_INT_SER_1)
DECL|macro|M_INT_PCMCIA
mdefine_line|#define M_INT_PCMCIA                _SB_MAKEMASK1(K_INT_PCMCIA)
DECL|macro|M_INT_ADDR_TRAP
mdefine_line|#define M_INT_ADDR_TRAP             _SB_MAKEMASK1(K_INT_ADDR_TRAP)
DECL|macro|M_INT_PERF_CNT
mdefine_line|#define M_INT_PERF_CNT              _SB_MAKEMASK1(K_INT_PERF_CNT)
DECL|macro|M_INT_TRACE_FREEZE
mdefine_line|#define M_INT_TRACE_FREEZE          _SB_MAKEMASK1(K_INT_TRACE_FREEZE)
DECL|macro|M_INT_BAD_ECC
mdefine_line|#define M_INT_BAD_ECC               _SB_MAKEMASK1(K_INT_BAD_ECC)
DECL|macro|M_INT_COR_ECC
mdefine_line|#define M_INT_COR_ECC               _SB_MAKEMASK1(K_INT_COR_ECC)
DECL|macro|M_INT_IO_BUS
mdefine_line|#define M_INT_IO_BUS                _SB_MAKEMASK1(K_INT_IO_BUS)
DECL|macro|M_INT_MAC_0
mdefine_line|#define M_INT_MAC_0                 _SB_MAKEMASK1(K_INT_MAC_0)
DECL|macro|M_INT_MAC_1
mdefine_line|#define M_INT_MAC_1                 _SB_MAKEMASK1(K_INT_MAC_1)
DECL|macro|M_INT_MAC_2
mdefine_line|#define M_INT_MAC_2                 _SB_MAKEMASK1(K_INT_MAC_2)
DECL|macro|M_INT_DM_CH_0
mdefine_line|#define M_INT_DM_CH_0               _SB_MAKEMASK1(K_INT_DM_CH_0)
DECL|macro|M_INT_DM_CH_1
mdefine_line|#define M_INT_DM_CH_1               _SB_MAKEMASK1(K_INT_DM_CH_1)
DECL|macro|M_INT_DM_CH_2
mdefine_line|#define M_INT_DM_CH_2               _SB_MAKEMASK1(K_INT_DM_CH_2)
DECL|macro|M_INT_DM_CH_3
mdefine_line|#define M_INT_DM_CH_3               _SB_MAKEMASK1(K_INT_DM_CH_3)
DECL|macro|M_INT_MBOX_0
mdefine_line|#define M_INT_MBOX_0                _SB_MAKEMASK1(K_INT_MBOX_0)
DECL|macro|M_INT_MBOX_1
mdefine_line|#define M_INT_MBOX_1                _SB_MAKEMASK1(K_INT_MBOX_1)
DECL|macro|M_INT_MBOX_2
mdefine_line|#define M_INT_MBOX_2                _SB_MAKEMASK1(K_INT_MBOX_2)
DECL|macro|M_INT_MBOX_3
mdefine_line|#define M_INT_MBOX_3                _SB_MAKEMASK1(K_INT_MBOX_3)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_INT_CYCLE_CP0_INT
mdefine_line|#define M_INT_CYCLE_CP0_INT&t;    _SB_MAKEMASK1(K_INT_CYCLE_CP0_INT)
DECL|macro|M_INT_CYCLE_CP1_INT
mdefine_line|#define M_INT_CYCLE_CP1_INT&t;    _SB_MAKEMASK1(K_INT_CYCLE_CP1_INT)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
DECL|macro|M_INT_GPIO_0
mdefine_line|#define M_INT_GPIO_0                _SB_MAKEMASK1(K_INT_GPIO_0)
DECL|macro|M_INT_GPIO_1
mdefine_line|#define M_INT_GPIO_1                _SB_MAKEMASK1(K_INT_GPIO_1)
DECL|macro|M_INT_GPIO_2
mdefine_line|#define M_INT_GPIO_2                _SB_MAKEMASK1(K_INT_GPIO_2)
DECL|macro|M_INT_GPIO_3
mdefine_line|#define M_INT_GPIO_3                _SB_MAKEMASK1(K_INT_GPIO_3)
DECL|macro|M_INT_GPIO_4
mdefine_line|#define M_INT_GPIO_4                _SB_MAKEMASK1(K_INT_GPIO_4)
DECL|macro|M_INT_GPIO_5
mdefine_line|#define M_INT_GPIO_5                _SB_MAKEMASK1(K_INT_GPIO_5)
DECL|macro|M_INT_GPIO_6
mdefine_line|#define M_INT_GPIO_6                _SB_MAKEMASK1(K_INT_GPIO_6)
DECL|macro|M_INT_GPIO_7
mdefine_line|#define M_INT_GPIO_7                _SB_MAKEMASK1(K_INT_GPIO_7)
DECL|macro|M_INT_GPIO_8
mdefine_line|#define M_INT_GPIO_8                _SB_MAKEMASK1(K_INT_GPIO_8)
DECL|macro|M_INT_GPIO_9
mdefine_line|#define M_INT_GPIO_9                _SB_MAKEMASK1(K_INT_GPIO_9)
DECL|macro|M_INT_GPIO_10
mdefine_line|#define M_INT_GPIO_10               _SB_MAKEMASK1(K_INT_GPIO_10)
DECL|macro|M_INT_GPIO_11
mdefine_line|#define M_INT_GPIO_11               _SB_MAKEMASK1(K_INT_GPIO_11)
DECL|macro|M_INT_GPIO_12
mdefine_line|#define M_INT_GPIO_12               _SB_MAKEMASK1(K_INT_GPIO_12)
DECL|macro|M_INT_GPIO_13
mdefine_line|#define M_INT_GPIO_13               _SB_MAKEMASK1(K_INT_GPIO_13)
DECL|macro|M_INT_GPIO_14
mdefine_line|#define M_INT_GPIO_14               _SB_MAKEMASK1(K_INT_GPIO_14)
DECL|macro|M_INT_GPIO_15
mdefine_line|#define M_INT_GPIO_15               _SB_MAKEMASK1(K_INT_GPIO_15)
DECL|macro|M_INT_LDT_FATAL
mdefine_line|#define M_INT_LDT_FATAL             _SB_MAKEMASK1(K_INT_LDT_FATAL)
DECL|macro|M_INT_LDT_NONFATAL
mdefine_line|#define M_INT_LDT_NONFATAL          _SB_MAKEMASK1(K_INT_LDT_NONFATAL)
DECL|macro|M_INT_LDT_SMI
mdefine_line|#define M_INT_LDT_SMI               _SB_MAKEMASK1(K_INT_LDT_SMI)
DECL|macro|M_INT_LDT_NMI
mdefine_line|#define M_INT_LDT_NMI               _SB_MAKEMASK1(K_INT_LDT_NMI)
DECL|macro|M_INT_LDT_INIT
mdefine_line|#define M_INT_LDT_INIT              _SB_MAKEMASK1(K_INT_LDT_INIT)
DECL|macro|M_INT_LDT_STARTUP
mdefine_line|#define M_INT_LDT_STARTUP           _SB_MAKEMASK1(K_INT_LDT_STARTUP)
DECL|macro|M_INT_LDT_EXT
mdefine_line|#define M_INT_LDT_EXT               _SB_MAKEMASK1(K_INT_LDT_EXT)
DECL|macro|M_INT_PCI_ERROR
mdefine_line|#define M_INT_PCI_ERROR             _SB_MAKEMASK1(K_INT_PCI_ERROR)
DECL|macro|M_INT_PCI_INTA
mdefine_line|#define M_INT_PCI_INTA              _SB_MAKEMASK1(K_INT_PCI_INTA)
DECL|macro|M_INT_PCI_INTB
mdefine_line|#define M_INT_PCI_INTB              _SB_MAKEMASK1(K_INT_PCI_INTB)
DECL|macro|M_INT_PCI_INTC
mdefine_line|#define M_INT_PCI_INTC              _SB_MAKEMASK1(K_INT_PCI_INTC)
DECL|macro|M_INT_PCI_INTD
mdefine_line|#define M_INT_PCI_INTD              _SB_MAKEMASK1(K_INT_PCI_INTD)
DECL|macro|M_INT_SPARE_2
mdefine_line|#define M_INT_SPARE_2               _SB_MAKEMASK1(K_INT_SPARE_2)
macro_line|#if SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
DECL|macro|M_INT_MAC_0_CH1
mdefine_line|#define M_INT_MAC_0_CH1&t;&t;    _SB_MAKEMASK1(K_INT_MAC_0_CH1)
DECL|macro|M_INT_MAC_1_CH1
mdefine_line|#define M_INT_MAC_1_CH1&t;&t;    _SB_MAKEMASK1(K_INT_MAC_1_CH1)
DECL|macro|M_INT_MAC_2_CH1
mdefine_line|#define M_INT_MAC_2_CH1&t;&t;    _SB_MAKEMASK1(K_INT_MAC_2_CH1)
macro_line|#endif /* 1250 PASS2 || 112x PASS1 */
multiline_comment|/*&n; * Interrupt mappings&n; */
DECL|macro|K_INT_MAP_I0
mdefine_line|#define K_INT_MAP_I0&t;0&t;&t;/* interrupt pins on processor */
DECL|macro|K_INT_MAP_I1
mdefine_line|#define K_INT_MAP_I1&t;1
DECL|macro|K_INT_MAP_I2
mdefine_line|#define K_INT_MAP_I2&t;2
DECL|macro|K_INT_MAP_I3
mdefine_line|#define K_INT_MAP_I3&t;3
DECL|macro|K_INT_MAP_I4
mdefine_line|#define K_INT_MAP_I4&t;4
DECL|macro|K_INT_MAP_I5
mdefine_line|#define K_INT_MAP_I5&t;5
DECL|macro|K_INT_MAP_NMI
mdefine_line|#define K_INT_MAP_NMI&t;6&t;&t;/* nonmaskable */
DECL|macro|K_INT_MAP_DINT
mdefine_line|#define K_INT_MAP_DINT&t;7&t;&t;/* debug interrupt */
multiline_comment|/*&n; * LDT Interrupt Set Register (table 4-5)&n; */
DECL|macro|S_INT_LDT_INTMSG
mdefine_line|#define S_INT_LDT_INTMSG&t;      0
DECL|macro|M_INT_LDT_INTMSG
mdefine_line|#define M_INT_LDT_INTMSG              _SB_MAKEMASK(3,S_INT_LDT_INTMSG)
DECL|macro|V_INT_LDT_INTMSG
mdefine_line|#define V_INT_LDT_INTMSG(x)           _SB_MAKEVALUE(x,S_INT_LDT_INTMSG)
DECL|macro|G_INT_LDT_INTMSG
mdefine_line|#define G_INT_LDT_INTMSG(x)           _SB_GETVALUE(x,S_INT_LDT_INTMSG,M_INT_LDT_INTMSG)
DECL|macro|K_INT_LDT_INTMSG_FIXED
mdefine_line|#define K_INT_LDT_INTMSG_FIXED&t;      0
DECL|macro|K_INT_LDT_INTMSG_ARBITRATED
mdefine_line|#define K_INT_LDT_INTMSG_ARBITRATED   1
DECL|macro|K_INT_LDT_INTMSG_SMI
mdefine_line|#define K_INT_LDT_INTMSG_SMI&t;      2
DECL|macro|K_INT_LDT_INTMSG_NMI
mdefine_line|#define K_INT_LDT_INTMSG_NMI&t;      3
DECL|macro|K_INT_LDT_INTMSG_INIT
mdefine_line|#define K_INT_LDT_INTMSG_INIT&t;      4
DECL|macro|K_INT_LDT_INTMSG_STARTUP
mdefine_line|#define K_INT_LDT_INTMSG_STARTUP      5
DECL|macro|K_INT_LDT_INTMSG_EXTINT
mdefine_line|#define K_INT_LDT_INTMSG_EXTINT&t;      6
DECL|macro|K_INT_LDT_INTMSG_RESERVED
mdefine_line|#define K_INT_LDT_INTMSG_RESERVED     7
DECL|macro|M_INT_LDT_EDGETRIGGER
mdefine_line|#define M_INT_LDT_EDGETRIGGER         0
DECL|macro|M_INT_LDT_LEVELTRIGGER
mdefine_line|#define M_INT_LDT_LEVELTRIGGER        _SB_MAKEMASK1(3)
DECL|macro|M_INT_LDT_PHYSICALDEST
mdefine_line|#define M_INT_LDT_PHYSICALDEST        0
DECL|macro|M_INT_LDT_LOGICALDEST
mdefine_line|#define M_INT_LDT_LOGICALDEST         _SB_MAKEMASK1(4)
DECL|macro|S_INT_LDT_INTDEST
mdefine_line|#define S_INT_LDT_INTDEST             5
DECL|macro|M_INT_LDT_INTDEST
mdefine_line|#define M_INT_LDT_INTDEST             _SB_MAKEMASK(10,S_INT_LDT_INTDEST)
DECL|macro|V_INT_LDT_INTDEST
mdefine_line|#define V_INT_LDT_INTDEST(x)          _SB_MAKEVALUE(x,S_INT_LDT_INTDEST)
DECL|macro|G_INT_LDT_INTDEST
mdefine_line|#define G_INT_LDT_INTDEST(x)          _SB_GETVALUE(x,S_INT_LDT_INTDEST,M_INT_LDT_INTDEST)
DECL|macro|S_INT_LDT_VECTOR
mdefine_line|#define S_INT_LDT_VECTOR              13
DECL|macro|M_INT_LDT_VECTOR
mdefine_line|#define M_INT_LDT_VECTOR              _SB_MAKEMASK(8,S_INT_LDT_VECTOR)
DECL|macro|V_INT_LDT_VECTOR
mdefine_line|#define V_INT_LDT_VECTOR(x)           _SB_MAKEVALUE(x,S_INT_LDT_VECTOR)
DECL|macro|G_INT_LDT_VECTOR
mdefine_line|#define G_INT_LDT_VECTOR(x)           _SB_GETVALUE(x,S_INT_LDT_VECTOR,M_INT_LDT_VECTOR)
multiline_comment|/*&n; * Vector format (Table 4-6)&n; */
DECL|macro|M_LDTVECT_RAISEINT
mdefine_line|#define M_LDTVECT_RAISEINT&t;&t;0x00
DECL|macro|M_LDTVECT_RAISEMBOX
mdefine_line|#define M_LDTVECT_RAISEMBOX             0x40
macro_line|#endif
eof
