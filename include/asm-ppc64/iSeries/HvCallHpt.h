multiline_comment|/*&n; * HvCallHpt.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
singleline_comment|//============================================================================
singleline_comment|//
singleline_comment|//&t;This file contains the &quot;hypervisor call&quot; interface which is used to
singleline_comment|//&t;drive the hypervisor from the OS.
singleline_comment|//
singleline_comment|//============================================================================
singleline_comment|//-------------------------------------------------------------------
singleline_comment|// Standard Includes
singleline_comment|//-------------------------------------------------------------------
macro_line|#ifndef  _HVCALLSC_H
macro_line|#include &quot;HvCallSc.h&quot;
macro_line|#endif
macro_line|#ifndef  _HVTYPES_H
macro_line|#include &lt;asm/iSeries/HvTypes.h&gt;
macro_line|#endif
singleline_comment|//-------------------------------------------------------------------
singleline_comment|// Other Includes
singleline_comment|//-------------------------------------------------------------------
macro_line|#ifndef _PPC_MMU_H
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#endif
singleline_comment|//-----------------------------------------------------------------------------
singleline_comment|// Constants
singleline_comment|//-----------------------------------------------------------------------------
macro_line|#ifndef _HVCALLHPT_H
DECL|macro|_HVCALLHPT_H
mdefine_line|#define _HVCALLHPT_H
DECL|macro|HvCallHptGetHptAddress
mdefine_line|#define HvCallHptGetHptAddress&t;&t;HvCallHpt +  0
DECL|macro|HvCallHptGetHptPages
mdefine_line|#define HvCallHptGetHptPages&t;&t;HvCallHpt +  1
DECL|macro|HvCallHptSetPp
mdefine_line|#define HvCallHptSetPp&t;&t;&t;HvCallHpt +  5
DECL|macro|HvCallHptSetSwBits
mdefine_line|#define HvCallHptSetSwBits&t;&t;HvCallHpt +  6
DECL|macro|HvCallHptUpdate
mdefine_line|#define HvCallHptUpdate&t;&t;&t;HvCallHpt +  7
DECL|macro|HvCallHptInvalidateNoSyncICache
mdefine_line|#define HvCallHptInvalidateNoSyncICache&t;HvCallHpt +  8
DECL|macro|HvCallHptGet
mdefine_line|#define HvCallHptGet&t;&t;&t;HvCallHpt + 11
DECL|macro|HvCallHptFindNextValid
mdefine_line|#define HvCallHptFindNextValid&t;&t;HvCallHpt + 12
DECL|macro|HvCallHptFindValid
mdefine_line|#define HvCallHptFindValid&t;&t;HvCallHpt + 13
DECL|macro|HvCallHptAddValidate
mdefine_line|#define HvCallHptAddValidate&t;&t;HvCallHpt + 16
DECL|macro|HvCallHptInvalidateSetSwBitsGet
mdefine_line|#define HvCallHptInvalidateSetSwBitsGet HvCallHpt + 18
singleline_comment|//============================================================================
DECL|function|HvCallHpt_getHptAddress
r_static
r_inline
id|u64
id|HvCallHpt_getHptAddress
c_func
(paren
r_void
)paren
(brace
id|u64
id|retval
op_assign
id|HvCall0
c_func
(paren
id|HvCallHptGetHptAddress
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retval
suffix:semicolon
)brace
singleline_comment|//============================================================================
DECL|function|HvCallHpt_getHptPages
r_static
r_inline
id|u64
id|HvCallHpt_getHptPages
c_func
(paren
r_void
)paren
(brace
id|u64
id|retval
op_assign
id|HvCall0
c_func
(paren
id|HvCallHptGetHptPages
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retval
suffix:semicolon
)brace
singleline_comment|//=============================================================================
DECL|function|HvCallHpt_setPp
r_static
r_inline
r_void
id|HvCallHpt_setPp
c_func
(paren
id|u32
id|hpteIndex
comma
id|u8
id|value
)paren
(brace
id|HvCall2
c_func
(paren
id|HvCallHptSetPp
comma
id|hpteIndex
comma
id|value
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
)brace
singleline_comment|//=============================================================================
DECL|function|HvCallHpt_setSwBits
r_static
r_inline
r_void
id|HvCallHpt_setSwBits
c_func
(paren
id|u32
id|hpteIndex
comma
id|u8
id|bitson
comma
id|u8
id|bitsoff
)paren
(brace
id|HvCall3
c_func
(paren
id|HvCallHptSetSwBits
comma
id|hpteIndex
comma
id|bitson
comma
id|bitsoff
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
)brace
singleline_comment|//=============================================================================
DECL|function|HvCallHpt_invalidateNoSyncICache
r_static
r_inline
r_void
id|HvCallHpt_invalidateNoSyncICache
c_func
(paren
id|u32
id|hpteIndex
)paren
(brace
id|HvCall1
c_func
(paren
id|HvCallHptInvalidateNoSyncICache
comma
id|hpteIndex
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
)brace
singleline_comment|//=============================================================================
DECL|function|HvCallHpt_invalidateSetSwBitsGet
r_static
r_inline
id|u64
id|HvCallHpt_invalidateSetSwBitsGet
c_func
(paren
id|u32
id|hpteIndex
comma
id|u8
id|bitson
comma
id|u8
id|bitsoff
)paren
(brace
id|u64
id|compressedStatus
suffix:semicolon
id|compressedStatus
op_assign
id|HvCall4
c_func
(paren
id|HvCallHptInvalidateSetSwBitsGet
comma
id|hpteIndex
comma
id|bitson
comma
id|bitsoff
comma
l_int|1
)paren
suffix:semicolon
id|HvCall1
c_func
(paren
id|HvCallHptInvalidateNoSyncICache
comma
id|hpteIndex
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|compressedStatus
suffix:semicolon
)brace
singleline_comment|//=============================================================================
DECL|function|HvCallHpt_findValid
r_static
r_inline
id|u64
id|HvCallHpt_findValid
c_func
(paren
id|HPTE
op_star
id|hpte
comma
id|u64
id|vpn
)paren
(brace
id|u64
id|retIndex
op_assign
id|HvCall3Ret16
c_func
(paren
id|HvCallHptFindValid
comma
id|hpte
comma
id|vpn
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retIndex
suffix:semicolon
)brace
singleline_comment|//=============================================================================
DECL|function|HvCallHpt_findNextValid
r_static
r_inline
id|u64
id|HvCallHpt_findNextValid
c_func
(paren
id|HPTE
op_star
id|hpte
comma
id|u32
id|hpteIndex
comma
id|u8
id|bitson
comma
id|u8
id|bitsoff
)paren
(brace
id|u64
id|retIndex
op_assign
id|HvCall3Ret16
c_func
(paren
id|HvCallHptFindNextValid
comma
id|hpte
comma
id|hpteIndex
comma
id|bitson
comma
id|bitsoff
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retIndex
suffix:semicolon
)brace
singleline_comment|//=============================================================================
DECL|function|HvCallHpt_get
r_static
r_inline
r_void
id|HvCallHpt_get
c_func
(paren
id|HPTE
op_star
id|hpte
comma
id|u32
id|hpteIndex
)paren
(brace
id|HvCall2Ret16
c_func
(paren
id|HvCallHptGet
comma
id|hpte
comma
id|hpteIndex
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
)brace
singleline_comment|//============================================================================
DECL|function|HvCallHpt_addValidate
r_static
r_inline
r_void
id|HvCallHpt_addValidate
c_func
(paren
id|u32
id|hpteIndex
comma
id|u32
id|hBit
comma
id|HPTE
op_star
id|hpte
)paren
(brace
id|HvCall4
c_func
(paren
id|HvCallHptAddValidate
comma
id|hpteIndex
comma
id|hBit
comma
(paren
op_star
(paren
(paren
id|u64
op_star
)paren
id|hpte
)paren
)paren
comma
(paren
op_star
(paren
(paren
(paren
id|u64
op_star
)paren
id|hpte
)paren
op_plus
l_int|1
)paren
)paren
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
)brace
singleline_comment|//=============================================================================
macro_line|#endif 
singleline_comment|// _HVCALLHPT_H
eof
