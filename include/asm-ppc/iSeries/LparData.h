multiline_comment|/*&n; * LparData.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef&t;_PPC_TYPES_H
macro_line|#include&t;&lt;asm/types.h&gt;
macro_line|#endif
macro_line|#ifndef _LPARDATA_H
DECL|macro|_LPARDATA_H
mdefine_line|#define _LPARDATA_H
macro_line|#include &lt;asm/page.h&gt;
r_extern
id|u32
id|msChunks
(braket
)braket
suffix:semicolon
DECL|macro|phys_to_absolute
mdefine_line|#define phys_to_absolute( x ) (((u64)msChunks[((x)&gt;&gt;18)])&lt;&lt;18)+((u64)((x)&amp;0x3ffff))
DECL|macro|physRpn_to_absRpn
mdefine_line|#define physRpn_to_absRpn( x ) (((u64)msChunks[((x)&gt;&gt;6)])&lt;&lt;6)+((u64)((x)&amp;0x3f))
DECL|macro|virt_to_absolute
mdefine_line|#define virt_to_absolute( x ) (((u64)msChunks[(((x)-KERNELBASE)&gt;&gt;18)])&lt;&lt;18)+((u64)((x)&amp;0x3ffff))
r_extern
id|u64
id|virt_to_absolute_outline
c_func
(paren
id|u32
id|address
)paren
suffix:semicolon
macro_line|#include &lt;asm/iSeries/Naca.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpNaca.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpPaca.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpRegSave.h&gt;
macro_line|#include &lt;asm/iSeries/Paca.h&gt;
macro_line|#include &lt;asm/iSeries/HvReleaseData.h&gt;
macro_line|#include &lt;asm/iSeries/LparMap.h&gt;
macro_line|#include &lt;asm/iSeries/ItVpdAreas.h&gt;
macro_line|#include &lt;asm/iSeries/ItIplParmsReal.h&gt;
macro_line|#include &lt;asm/iSeries/ItLpQueue.h&gt;
macro_line|#include &lt;asm/iSeries/IoHriProcessorVpd.h&gt;
macro_line|#include &lt;asm/page.h&gt;
r_extern
r_struct
id|LparMap
id|xLparMap
suffix:semicolon
r_extern
r_struct
id|Naca
id|xNaca
suffix:semicolon
r_extern
r_struct
id|Paca
id|xPaca
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|HvReleaseData
id|hvReleaseData
suffix:semicolon
r_extern
r_struct
id|ItLpNaca
id|itLpNaca
suffix:semicolon
r_extern
r_struct
id|ItIplParmsReal
id|xItIplParmsReal
suffix:semicolon
r_extern
r_struct
id|IoHriProcessorVpd
id|xIoHriProcessorVpd
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|ItLpQueue
id|xItLpQueue
suffix:semicolon
r_extern
r_struct
id|ItVpdAreas
id|itVpdAreas
suffix:semicolon
r_extern
id|u64
id|xMsVpd
(braket
)braket
suffix:semicolon
r_extern
id|u32
id|msChunks
(braket
)braket
suffix:semicolon
r_extern
id|u32
id|totalLpChunks
suffix:semicolon
r_extern
r_int
id|maxPacas
suffix:semicolon
multiline_comment|/*&n;#define phys_to_absolute( x ) (((u64)msChunks[((x)&gt;&gt;18)])&lt;&lt;18)+((u64)((x)&amp;0x3ffff))&n;&n;#define physRpn_to_absRpn( x ) (((u64)msChunks[((x)&gt;&gt;6)])&lt;&lt;6)+((u64)((x)&amp;0x3f))&n;&n;#define virt_to_absolute( x ) (((u64)msChunks[(((x)-KERNELBASE)&gt;&gt;18)])&lt;&lt;18)+((u64)((x)&amp;0x3ffff))&n;*/
macro_line|#endif /* _LPAR_DATA_H */
eof
