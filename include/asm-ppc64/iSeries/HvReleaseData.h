multiline_comment|/*&n; * HvReleaseData.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
singleline_comment|//=============================================================================
singleline_comment|//
singleline_comment|//   This control block contains the critical information about the 
singleline_comment|//   release so that it can be changed in the future (ie, the virtual 
singleline_comment|//   address of the OS&squot;s NACA).
singleline_comment|//
singleline_comment|//-----------------------------------------------------------------------------
singleline_comment|// Standard Includes
singleline_comment|//-----------------------------------------------------------------------------
macro_line|#ifndef&t;_PPC64_TYPES_H
macro_line|#include&t;&lt;asm/types.h&gt;
macro_line|#endif
macro_line|#ifndef _HVRELEASEDATA_H
DECL|macro|_HVRELEASEDATA_H
mdefine_line|#define _HVRELEASEDATA_H
singleline_comment|//=============================================================================
singleline_comment|//
singleline_comment|//&t;When we IPL a secondary partition, we will check if if the 
singleline_comment|//&t;secondary xMinPlicVrmIndex &gt; the primary xVrmIndex.  
singleline_comment|//&t;If it is then this tells PLIC that this secondary is not 
singleline_comment|//&t;supported running on this &quot;old&quot; of a level of PLIC.
singleline_comment|//
singleline_comment|//&t;Likewise, we will compare the primary xMinSlicVrmIndex to 
singleline_comment|//&t;the secondary xVrmIndex. 
singleline_comment|//&t;If the primary xMinSlicVrmDelta &gt; secondary xVrmDelta then we 
singleline_comment|//&t;know that this PLIC does not support running an OS &quot;that old&quot;.
singleline_comment|//
singleline_comment|//=============================================================================
DECL|struct|HvReleaseData
r_struct
id|HvReleaseData
(brace
DECL|member|xDesc
id|u32
id|xDesc
suffix:semicolon
singleline_comment|// Descriptor&t;&quot;HvRD&quot; ebcdic&t;x00-x03
DECL|member|xSize
id|u16
id|xSize
suffix:semicolon
singleline_comment|// Size of this control block&t;x04-x05
DECL|member|xVpdAreasPtrOffset
id|u16
id|xVpdAreasPtrOffset
suffix:semicolon
singleline_comment|// Offset in NACA of ItVpdAreas&t;x06-x07
DECL|member|xSlicNacaAddr
r_struct
id|naca_struct
op_star
id|xSlicNacaAddr
suffix:semicolon
singleline_comment|// Virt addr of SLIC NACA  x08-x0F
DECL|member|xMsNucDataOffset
id|u32
id|xMsNucDataOffset
suffix:semicolon
singleline_comment|// Offset of Linux Mapping Data x10-x13
DECL|member|xRsvd1
id|u32
id|xRsvd1
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;x14-x17
DECL|member|xTagsMode
id|u16
id|xTagsMode
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 0 == tags active, 1 == tags inactive
DECL|member|xAddressSize
id|u16
id|xAddressSize
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 0 == 64-bit, 1 == 32-bit
DECL|member|xNoSharedProcs
id|u16
id|xNoSharedProcs
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 0 == shared procs, 1 == no shared
DECL|member|xNoHMT
id|u16
id|xNoHMT
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 0 == allow HMT, 1 == no HMT
DECL|member|xRsvd2
id|u16
id|xRsvd2
suffix:colon
l_int|12
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;x18-x19
DECL|member|xVrmIndex
id|u16
id|xVrmIndex
suffix:semicolon
singleline_comment|// VRM Index of OS image&t;x1A-x1B
DECL|member|xMinSupportedPlicVrmIndex
id|u16
id|xMinSupportedPlicVrmIndex
suffix:semicolon
singleline_comment|// Min PLIC level  (soft)&t;x1C-x1D
DECL|member|xMinCompatablePlicVrmIndex
id|u16
id|xMinCompatablePlicVrmIndex
suffix:semicolon
singleline_comment|// Min PLIC levelP (hard)&t;x1E-x1F
DECL|member|xVrmName
r_char
id|xVrmName
(braket
l_int|12
)braket
suffix:semicolon
singleline_comment|// Displayable name  &t;&t;x20-x2B
DECL|member|xRsvd3
r_char
id|xRsvd3
(braket
l_int|20
)braket
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;x2C-x3F
)brace
suffix:semicolon
macro_line|#endif 
singleline_comment|// _HVRELEASEDATA_H
eof
