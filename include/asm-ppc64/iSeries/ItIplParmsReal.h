multiline_comment|/*&n; * ItIplParmsReal.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
singleline_comment|//==============================================================================
singleline_comment|//
singleline_comment|//&t;This struct maps the IPL Parameters DMA&squot;d from the SP.                  
singleline_comment|//
singleline_comment|// Warning:
singleline_comment|//&t;This data must map in exactly 64 bytes and match the architecture for
singleline_comment|//&t;the IPL parms
singleline_comment|//
singleline_comment|//=============================================================================
singleline_comment|//-------------------------------------------------------------------
singleline_comment|// Standard Includes
singleline_comment|//-------------------------------------------------------------------
macro_line|#ifndef&t;_PPC_TYPES_H
macro_line|#include&t;&lt;asm/types.h&gt;
macro_line|#endif
macro_line|#ifndef _ITIPLPARMSREAL_H
DECL|macro|_ITIPLPARMSREAL_H
mdefine_line|#define _ITIPLPARMSREAL_H
DECL|struct|ItIplParmsReal
r_struct
id|ItIplParmsReal
(brace
DECL|member|xFormat
id|u8
id|xFormat
suffix:semicolon
singleline_comment|// Defines format of IplParms&t;&t;x00-x00
DECL|member|xRsvd01
id|u8
id|xRsvd01
suffix:colon
l_int|6
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;&t;x01-x01
DECL|member|xAlternateSearch
id|u8
id|xAlternateSearch
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// Alternate search indicator&t;&t;...
DECL|member|xUaSupplied
id|u8
id|xUaSupplied
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// UA Supplied on programmed IPL&t;...
DECL|member|xLsUaFormat
id|u8
id|xLsUaFormat
suffix:semicolon
singleline_comment|// Format byte for UA&t;&t;&t;x02-x02
DECL|member|xRsvd02
id|u8
id|xRsvd02
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;&t;x03-x03
DECL|member|xLsUa
id|u32
id|xLsUa
suffix:semicolon
singleline_comment|// LS UA&t;&t;&t;&t;x04-x07
DECL|member|xUnusedLsLid
id|u32
id|xUnusedLsLid
suffix:semicolon
singleline_comment|// First OS LID to load&t;&t;&t;x08-x0B
DECL|member|xLsBusNumber
id|u16
id|xLsBusNumber
suffix:semicolon
singleline_comment|// LS Bus Number&t;&t;&t;x0C-x0D
DECL|member|xLsCardAdr
id|u8
id|xLsCardAdr
suffix:semicolon
singleline_comment|// LS Card Address&t;&t;&t;x0E-x0E
DECL|member|xLsBoardAdr
id|u8
id|xLsBoardAdr
suffix:semicolon
singleline_comment|// LS Board Address&t;&t;&t;x0F-x0F
DECL|member|xRsvd03
id|u32
id|xRsvd03
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;&t;x10-x13
DECL|member|xSpcnPresent
id|u8
id|xSpcnPresent
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// SPCN present&t;&t;&t;&t;x14-x14
DECL|member|xCpmPresent
id|u8
id|xCpmPresent
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// CPM present&t;&t;&t;&t;...
DECL|member|xRsvd04
id|u8
id|xRsvd04
suffix:colon
l_int|6
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;&t;...
DECL|member|xRsvd05
id|u8
id|xRsvd05
suffix:colon
l_int|4
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;&t;x15-x15
DECL|member|xKeyLock
id|u8
id|xKeyLock
suffix:colon
l_int|4
suffix:semicolon
singleline_comment|// Keylock setting&t;&t;&t;...
DECL|member|xRsvd06
id|u8
id|xRsvd06
suffix:colon
l_int|6
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;&t;x16-x16
DECL|member|xIplMode
id|u8
id|xIplMode
suffix:colon
l_int|2
suffix:semicolon
singleline_comment|// Ipl mode (A|B|C|D)&t;&t;&t;...
DECL|member|xHwIplType
id|u8
id|xHwIplType
suffix:semicolon
singleline_comment|// Fast v slow v slow EC HW IPL&t;&t;x17-x17
DECL|member|xCpmEnabledIpl
id|u16
id|xCpmEnabledIpl
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// CPM in effect when IPL initiated&t;x18-x19
DECL|member|xPowerOnResetIpl
id|u16
id|xPowerOnResetIpl
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// Indicate POR condition&t;&t;...
DECL|member|xMainStorePreserved
id|u16
id|xMainStorePreserved
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// Main Storage is preserved&t;&t;...
DECL|member|xRsvd07
id|u16
id|xRsvd07
suffix:colon
l_int|13
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;&t;...
DECL|member|xIplSource
id|u16
id|xIplSource
suffix:colon
l_int|16
suffix:semicolon
singleline_comment|// Ipl source&t;&t;&t;&t;x1A-x1B
DECL|member|xIplReason
id|u8
id|xIplReason
suffix:colon
l_int|8
suffix:semicolon
singleline_comment|// Reason for this IPL&t;&t;&t;x1C-x1C
DECL|member|xRsvd08
id|u8
id|xRsvd08
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;&t;x1D-x1D
DECL|member|xRsvd09
id|u16
id|xRsvd09
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;&t;x1E-x1F
DECL|member|xSysBoxType
id|u16
id|xSysBoxType
suffix:semicolon
singleline_comment|// System Box Type&t;&t;&t;x20-x21
DECL|member|xSysProcType
id|u16
id|xSysProcType
suffix:semicolon
singleline_comment|// System Processor Type&t;&t;x22-x23
DECL|member|xRsvd10
id|u32
id|xRsvd10
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;&t;x24-x27
DECL|member|xRsvd11
id|u64
id|xRsvd11
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;&t;x28-x2F
DECL|member|xRsvd12
id|u64
id|xRsvd12
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;&t;x30-x37
DECL|member|xRsvd13
id|u64
id|xRsvd13
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;&t;x38-x3F
)brace
suffix:semicolon
macro_line|#endif 
singleline_comment|// _ITIPLPARMSREAL_H
eof
