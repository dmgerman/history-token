multiline_comment|/*&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; * ########################################################################&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * ########################################################################&n; *&n; * This is the interface to the remote debugger stub.&n; */
macro_line|#include &lt;linux/serialP.h&gt;
macro_line|#include &lt;linux/serial_reg.h&gt;
macro_line|#include &lt;asm/serial.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hp-lj/asic.h&gt;
r_int
id|putDebugChar
c_func
(paren
r_char
id|c
)paren
suffix:semicolon
r_char
id|getDebugChar
c_func
(paren
r_void
)paren
suffix:semicolon
singleline_comment|///////////////////////  andros values ///////////////////////////////////////////////////////
DECL|macro|SERIAL_REG
mdefine_line|#define SERIAL_REG(offset) (*((volatile unsigned int*)(HPSR_BASE_ADDR|offset)))
singleline_comment|// Register set base address
DECL|macro|HPSR_BASE_ADDR
mdefine_line|#define HPSR_BASE_ADDR   0xbfe00000UL
singleline_comment|// Transmit / Receive Data
DECL|macro|HPSR_DATA_OFFSET
mdefine_line|#define HPSR_DATA_OFFSET    0x00020010UL
singleline_comment|// Transmit control / status
DECL|macro|HPSR_TX_STAT_OFFSET
mdefine_line|#define HPSR_TX_STAT_OFFSET 0x0002000CUL
singleline_comment|// Receive status
DECL|macro|HPSR_RX_STAT_OFFSET
mdefine_line|#define HPSR_RX_STAT_OFFSET 0x00020008UL
DECL|macro|HPSR_TX_STAT_READY
mdefine_line|#define HPSR_TX_STAT_READY  0x8UL
DECL|macro|HPSR_RX_DATA_AVAIL
mdefine_line|#define HPSR_RX_DATA_AVAIL  0x4UL
singleline_comment|///////////////////////  harmony values ///////////////////////////////////////////////////////
singleline_comment|// Transmit / Receive Data
DECL|macro|H_HPSR_DATA_TX
mdefine_line|#define H_HPSR_DATA_TX       *((volatile unsigned int*)0xbff65014)
singleline_comment|// Transmit / Receive Data
DECL|macro|H_HPSR_DATA_RX
mdefine_line|#define H_HPSR_DATA_RX       *((volatile unsigned int*)0xbff65018)
singleline_comment|// Status
DECL|macro|H_HPSR_STAT
mdefine_line|#define H_HPSR_STAT          *((volatile unsigned int*)0xbff65004)
singleline_comment|// harmony serial status bits
DECL|macro|H_SER_STAT_TX_EMPTY
mdefine_line|#define H_SER_STAT_TX_EMPTY       0x04
DECL|macro|H_SER_STAT_RX_EMPTY
mdefine_line|#define H_SER_STAT_RX_EMPTY       0x10
DECL|function|putDebugChar
r_int
id|putDebugChar
c_func
(paren
r_char
id|c
)paren
(brace
r_if
c_cond
(paren
id|GetAsicId
c_func
(paren
)paren
op_eq
id|HarmonyAsic
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
(paren
(paren
(paren
id|H_HPSR_STAT
)paren
op_amp
id|H_SER_STAT_TX_EMPTY
)paren
op_ne
l_int|0
)paren
)paren
suffix:semicolon
id|H_HPSR_DATA_TX
op_assign
(paren
r_int
r_int
)paren
id|c
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|GetAsicId
c_func
(paren
)paren
op_eq
id|AndrosAsic
)paren
(brace
r_while
c_loop
(paren
(paren
(paren
id|SERIAL_REG
c_func
(paren
id|HPSR_TX_STAT_OFFSET
)paren
op_amp
id|HPSR_TX_STAT_READY
)paren
op_eq
l_int|0
)paren
)paren
suffix:semicolon
id|SERIAL_REG
c_func
(paren
id|HPSR_DATA_OFFSET
)paren
op_assign
(paren
r_int
r_int
)paren
id|c
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|getDebugChar
r_char
id|getDebugChar
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|GetAsicId
c_func
(paren
)paren
op_eq
id|HarmonyAsic
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
(paren
(paren
(paren
id|H_HPSR_STAT
)paren
op_amp
id|H_SER_STAT_RX_EMPTY
)paren
op_eq
l_int|0
)paren
)paren
suffix:semicolon
r_return
id|H_HPSR_DATA_RX
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|GetAsicId
c_func
(paren
)paren
op_eq
id|AndrosAsic
)paren
(brace
r_while
c_loop
(paren
(paren
id|SERIAL_REG
c_func
(paren
id|HPSR_RX_STAT_OFFSET
)paren
op_amp
id|HPSR_RX_DATA_AVAIL
)paren
op_eq
l_int|0
)paren
suffix:semicolon
r_return
(paren
id|SERIAL_REG
c_func
(paren
id|HPSR_DATA_OFFSET
)paren
)paren
suffix:semicolon
)brace
)brace
eof
