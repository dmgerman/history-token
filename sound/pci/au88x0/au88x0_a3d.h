multiline_comment|/***************************************************************************&n; *            au88x0_a3d.h&n; *&n; *  Fri Jul 18 14:16:03 2003&n; *  Copyright  2003  mjander&n; *  mjander@users.sourceforge.net&n; ****************************************************************************/
multiline_comment|/*&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU Library General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; */
macro_line|#ifndef _AU88X0_A3D_H
DECL|macro|_AU88X0_A3D_H
mdefine_line|#define _AU88X0_A3D_H
singleline_comment|//#include &lt;openal.h&gt;
DECL|macro|HRTF_SZ
mdefine_line|#define HRTF_SZ 0x38
DECL|macro|DLINE_SZ
mdefine_line|#define DLINE_SZ 0x28
DECL|macro|CTRLID_HRTF
mdefine_line|#define CTRLID_HRTF&t;&t;1
DECL|macro|CTRLID_ITD
mdefine_line|#define CTRLID_ITD&t;&t;2
DECL|macro|CTRLID_ILD
mdefine_line|#define CTRLID_ILD&t;&t;4
DECL|macro|CTRLID_FILTER
mdefine_line|#define CTRLID_FILTER&t;8
DECL|macro|CTRLID_GAINS
mdefine_line|#define CTRLID_GAINS&t;16
multiline_comment|/* 3D parameter structs */
DECL|typedef|a3d_Hrtf_t
r_typedef
r_int
r_int
r_int
id|a3d_Hrtf_t
(braket
id|HRTF_SZ
)braket
suffix:semicolon
DECL|typedef|a3d_ItdDline_t
r_typedef
r_int
r_int
r_int
id|a3d_ItdDline_t
(braket
id|DLINE_SZ
)braket
suffix:semicolon
DECL|typedef|a3d_atmos_t
r_typedef
r_int
r_int
r_int
id|a3d_atmos_t
(braket
l_int|5
)braket
suffix:semicolon
DECL|typedef|a3d_LRGains_t
r_typedef
r_int
r_int
r_int
id|a3d_LRGains_t
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|a3d_Itd_t
r_typedef
r_int
r_int
r_int
id|a3d_Itd_t
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|a3d_Ild_t
r_typedef
r_int
r_int
r_int
id|a3d_Ild_t
(braket
l_int|2
)braket
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|vortex
r_void
op_star
id|vortex
suffix:semicolon
singleline_comment|// Formerly CAsp4HwIO*, now vortex_t*.
DECL|member|source
r_int
r_int
id|source
suffix:semicolon
multiline_comment|/* this_04 */
DECL|member|slice
r_int
r_int
id|slice
suffix:semicolon
multiline_comment|/* this_08 */
DECL|member|hrtf
id|a3d_Hrtf_t
id|hrtf
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|itd
id|a3d_Itd_t
id|itd
suffix:semicolon
DECL|member|ild
id|a3d_Ild_t
id|ild
suffix:semicolon
DECL|member|dline
id|a3d_ItdDline_t
id|dline
suffix:semicolon
DECL|member|filter
id|a3d_atmos_t
id|filter
suffix:semicolon
DECL|typedef|a3dsrc_t
)brace
id|a3dsrc_t
suffix:semicolon
multiline_comment|/* First Register bank */
DECL|macro|A3D_A_HrtfCurrent
mdefine_line|#define A3D_A_HrtfCurrent&t;0x18000&t;/* 56 ULONG */
DECL|macro|A3D_A_GainCurrent
mdefine_line|#define A3D_A_GainCurrent&t;0x180E0
DECL|macro|A3D_A_GainTarget
mdefine_line|#define A3D_A_GainTarget&t;0x180E4
DECL|macro|A3D_A_A12Current
mdefine_line|#define A3D_A_A12Current&t;0x180E8&t;/* Atmospheric current. */
DECL|macro|A3D_A_A21Target
mdefine_line|#define A3D_A_A21Target&t;&t;0x180EC&t;/* Atmospheric target */
DECL|macro|A3D_A_B01Current
mdefine_line|#define A3D_A_B01Current&t;0x180F0&t;/* Atmospheric current */
DECL|macro|A3D_A_B10Target
mdefine_line|#define A3D_A_B10Target&t;&t;0x180F4&t;/* Atmospheric target */
DECL|macro|A3D_A_B2Current
mdefine_line|#define A3D_A_B2Current&t;&t;0x180F8&t;/* Atmospheric current */
DECL|macro|A3D_A_B2Target
mdefine_line|#define A3D_A_B2Target&t;&t;0x180FC&t;/* Atmospheric target */
DECL|macro|A3D_A_HrtfTarget
mdefine_line|#define A3D_A_HrtfTarget&t;0x18100&t;/* 56 ULONG */
DECL|macro|A3D_A_ITDCurrent
mdefine_line|#define A3D_A_ITDCurrent&t;0x181E0
DECL|macro|A3D_A_ITDTarget
mdefine_line|#define A3D_A_ITDTarget&t;&t;0x181E4
DECL|macro|A3D_A_HrtfDelayLine
mdefine_line|#define A3D_A_HrtfDelayLine&t;0x181E8&t;/* 56 ULONG */
DECL|macro|A3D_A_ITDDelayLine
mdefine_line|#define A3D_A_ITDDelayLine&t;0x182C8&t;/* 40/45 ULONG */
DECL|macro|A3D_A_HrtfTrackTC
mdefine_line|#define A3D_A_HrtfTrackTC&t;0x1837C&t;/* Time Constants */
DECL|macro|A3D_A_GainTrackTC
mdefine_line|#define A3D_A_GainTrackTC&t;0x18380
DECL|macro|A3D_A_CoeffTrackTC
mdefine_line|#define A3D_A_CoeffTrackTC&t;0x18384
DECL|macro|A3D_A_ITDTrackTC
mdefine_line|#define A3D_A_ITDTrackTC&t;0x18388
DECL|macro|A3D_A_x1
mdefine_line|#define A3D_A_x1&t;&t;&t;0x1838C
DECL|macro|A3D_A_x2
mdefine_line|#define A3D_A_x2&t;&t;&t;0x18390
DECL|macro|A3D_A_y1
mdefine_line|#define A3D_A_y1&t;&t;&t;0x18394
DECL|macro|A3D_A_y2
mdefine_line|#define A3D_A_y2&t;&t;&t;0x18398
DECL|macro|A3D_A_HrtfOutL
mdefine_line|#define A3D_A_HrtfOutL&t;&t;0x1839C
DECL|macro|A3D_A_HrtfOutR
mdefine_line|#define A3D_A_HrtfOutR&t;&t;0x183A0
DECL|macro|A3D_A_TAIL
mdefine_line|#define &t;A3D_A_TAIL&t;&t;0x183A4
multiline_comment|/* Second register bank */
DECL|macro|A3D_B_HrtfCurrent
mdefine_line|#define A3D_B_HrtfCurrent&t;0x19000&t;/* 56 ULONG */
DECL|macro|A3D_B_GainCurrent
mdefine_line|#define A3D_B_GainCurrent&t;0x190E0
DECL|macro|A3D_B_GainTarget
mdefine_line|#define A3D_B_GainTarget&t;0x190E4
DECL|macro|A3D_B_A12Current
mdefine_line|#define A3D_B_A12Current&t;0x190E8
DECL|macro|A3D_B_A21Target
mdefine_line|#define A3D_B_A21Target&t;&t;0x190EC
DECL|macro|A3D_B_B01Current
mdefine_line|#define A3D_B_B01Current&t;0x190F0
DECL|macro|A3D_B_B10Target
mdefine_line|#define A3D_B_B10Target&t;&t;0x190F4
DECL|macro|A3D_B_B2Current
mdefine_line|#define A3D_B_B2Current&t;&t;0x190F8
DECL|macro|A3D_B_B2Target
mdefine_line|#define A3D_B_B2Target&t;&t;0x190FC
DECL|macro|A3D_B_HrtfTarget
mdefine_line|#define A3D_B_HrtfTarget&t;0x19100&t;/* 56 ULONG */
DECL|macro|A3D_B_ITDCurrent
mdefine_line|#define A3D_B_ITDCurrent&t;0x191E0
DECL|macro|A3D_B_ITDTarget
mdefine_line|#define A3D_B_ITDTarget&t;&t;0x191E4
DECL|macro|A3D_B_HrtfDelayLine
mdefine_line|#define A3D_B_HrtfDelayLine&t;0x191E8&t;/* 56 ULONG */
DECL|macro|A3D_B_TAIL
mdefine_line|#define &t;A3D_B_TAIL&t;&t;0x192C8
multiline_comment|/* There are 4 slices, 4 a3d each = 16 a3d sources. */
DECL|macro|A3D_SLICE_BANK_A
mdefine_line|#define A3D_SLICE_BANK_A&t;&t;0x18000&t;/* 4 sources */
DECL|macro|A3D_SLICE_BANK_B
mdefine_line|#define A3D_SLICE_BANK_B&t;&t;0x19000&t;/* 4 sources */
DECL|macro|A3D_SLICE_VDBDest
mdefine_line|#define A3D_SLICE_VDBDest&t;&t;0x19C00&t;/* 8 ULONG */
DECL|macro|A3D_SLICE_VDBSource
mdefine_line|#define A3D_SLICE_VDBSource&t;&t;0x19C20&t;/* 4 ULONG */
DECL|macro|A3D_SLICE_ABReg
mdefine_line|#define A3D_SLICE_ABReg&t;&t;&t;0x19C30
DECL|macro|A3D_SLICE_CReg
mdefine_line|#define A3D_SLICE_CReg&t;&t;&t;0x19C34
DECL|macro|A3D_SLICE_Control
mdefine_line|#define A3D_SLICE_Control&t;&t;0x19C38
DECL|macro|A3D_SLICE_DebugReserved
mdefine_line|#define A3D_SLICE_DebugReserved&t;0x19C3c&t;/* Dangerous! */
DECL|macro|A3D_SLICE_Pointers
mdefine_line|#define A3D_SLICE_Pointers&t;&t;0x19C40
DECL|macro|A3D_SLICE_TAIL
mdefine_line|#define &t;A3D_SLICE_TAIL&t;&t;0x1A000
singleline_comment|// Slice size: 0x2000
singleline_comment|// Source size: 0x3A4, 0x2C8
multiline_comment|/* Address generator macro. */
DECL|macro|a3d_addrA
mdefine_line|#define a3d_addrA(slice,source,reg) (((slice)&lt;&lt;0xd)+((source)*0x3A4)+(reg))
DECL|macro|a3d_addrB
mdefine_line|#define a3d_addrB(slice,source,reg) (((slice)&lt;&lt;0xd)+((source)*0x2C8)+(reg))
DECL|macro|a3d_addrS
mdefine_line|#define a3d_addrS(slice,reg) (((slice)&lt;&lt;0xd)+(reg))
singleline_comment|//#define a3d_addr(slice,source,reg) (((reg)&gt;=0x19000) ? a3d_addr2((slice),(source),(reg)) : a3d_addr1((slice),(source),(reg)))
macro_line|#endif&t;&t;&t;&t;/* _AU88X0_A3D_H */
eof
