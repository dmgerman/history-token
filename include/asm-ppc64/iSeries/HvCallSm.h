multiline_comment|/*&n; * HvCallSm.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
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
singleline_comment|//-----------------------------------------------------------------------------
singleline_comment|// Constants
singleline_comment|//-----------------------------------------------------------------------------
macro_line|#ifndef _HVCALLSM_H
DECL|macro|_HVCALLSM_H
mdefine_line|#define _HVCALLSM_H
DECL|macro|HvCallSmGet64BitsOfAccessMap
mdefine_line|#define HvCallSmGet64BitsOfAccessMap&t;HvCallSm  + 11
singleline_comment|//============================================================================
DECL|function|HvCallSm_get64BitsOfAccessMap
r_static
r_inline
id|u64
id|HvCallSm_get64BitsOfAccessMap
c_func
(paren
id|HvLpIndex
id|lpIndex
comma
id|u64
id|indexIntoBitMap
)paren
(brace
id|u64
id|retval
op_assign
id|HvCall2
c_func
(paren
id|HvCallSmGet64BitsOfAccessMap
comma
id|lpIndex
comma
id|indexIntoBitMap
)paren
suffix:semicolon
singleline_comment|// getPaca()-&gt;adjustHmtForNoOfSpinLocksHeld();
r_return
id|retval
suffix:semicolon
)brace
singleline_comment|//============================================================================
macro_line|#endif 
singleline_comment|// _HVCALLSM_H
eof
