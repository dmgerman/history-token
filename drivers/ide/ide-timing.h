macro_line|#ifndef _IDE_TIMING_H
DECL|macro|_IDE_TIMING_H
mdefine_line|#define _IDE_TIMING_H
multiline_comment|/*&n; * $Id: ide-timing.h,v 1.6 2001/12/23 22:47:56 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2001 Vojtech Pavlik&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/hdreg.h&gt;
DECL|macro|XFER_PIO_5
mdefine_line|#define XFER_PIO_5&t;&t;0x0d
DECL|macro|XFER_UDMA_SLOW
mdefine_line|#define XFER_UDMA_SLOW&t;&t;0x4f
DECL|struct|ide_timing
r_struct
id|ide_timing
(brace
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|setup
r_int
id|setup
suffix:semicolon
multiline_comment|/* t1 */
DECL|member|act8b
r_int
id|act8b
suffix:semicolon
multiline_comment|/* t2 for 8-bit io */
DECL|member|rec8b
r_int
id|rec8b
suffix:semicolon
multiline_comment|/* t2i for 8-bit io */
DECL|member|cyc8b
r_int
id|cyc8b
suffix:semicolon
multiline_comment|/* t0 for 8-bit io */
DECL|member|active
r_int
id|active
suffix:semicolon
multiline_comment|/* t2 or tD */
DECL|member|recover
r_int
id|recover
suffix:semicolon
multiline_comment|/* t2i or tK */
DECL|member|cycle
r_int
id|cycle
suffix:semicolon
multiline_comment|/* t0 */
DECL|member|udma
r_int
id|udma
suffix:semicolon
multiline_comment|/* t2CYCTYP/2 */
)brace
suffix:semicolon
multiline_comment|/*&n; * PIO 0-5, MWDMA 0-2 and UDMA 0-6 timings (in nanoseconds).&n; * These were taken from ATA/ATAPI-6 standard, rev 0a, except&n; * for PIO 5, which is a nonstandard extension and UDMA6, which&n; * is currently supported only by Maxtor drives. &n; */
DECL|variable|ide_timing
r_static
r_struct
id|ide_timing
id|ide_timing
(braket
)braket
op_assign
(brace
(brace
id|XFER_UDMA_6
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|15
)brace
comma
(brace
id|XFER_UDMA_5
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|20
)brace
comma
(brace
id|XFER_UDMA_4
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|30
)brace
comma
(brace
id|XFER_UDMA_3
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|45
)brace
comma
(brace
id|XFER_UDMA_2
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|60
)brace
comma
(brace
id|XFER_UDMA_1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|80
)brace
comma
(brace
id|XFER_UDMA_0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|120
)brace
comma
(brace
id|XFER_UDMA_SLOW
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|150
)brace
comma
(brace
id|XFER_MW_DMA_2
comma
l_int|25
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|70
comma
l_int|25
comma
l_int|120
comma
l_int|0
)brace
comma
(brace
id|XFER_MW_DMA_1
comma
l_int|45
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|80
comma
l_int|50
comma
l_int|150
comma
l_int|0
)brace
comma
(brace
id|XFER_MW_DMA_0
comma
l_int|60
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|215
comma
l_int|215
comma
l_int|480
comma
l_int|0
)brace
comma
(brace
id|XFER_SW_DMA_2
comma
l_int|60
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|120
comma
l_int|120
comma
l_int|240
comma
l_int|0
)brace
comma
(brace
id|XFER_SW_DMA_1
comma
l_int|90
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|240
comma
l_int|240
comma
l_int|480
comma
l_int|0
)brace
comma
(brace
id|XFER_SW_DMA_0
comma
l_int|120
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|480
comma
l_int|480
comma
l_int|960
comma
l_int|0
)brace
comma
(brace
id|XFER_PIO_5
comma
l_int|20
comma
l_int|50
comma
l_int|30
comma
l_int|100
comma
l_int|50
comma
l_int|30
comma
l_int|100
comma
l_int|0
)brace
comma
(brace
id|XFER_PIO_4
comma
l_int|25
comma
l_int|70
comma
l_int|25
comma
l_int|120
comma
l_int|70
comma
l_int|25
comma
l_int|120
comma
l_int|0
)brace
comma
(brace
id|XFER_PIO_3
comma
l_int|30
comma
l_int|80
comma
l_int|70
comma
l_int|180
comma
l_int|80
comma
l_int|70
comma
l_int|180
comma
l_int|0
)brace
comma
(brace
id|XFER_PIO_2
comma
l_int|30
comma
l_int|290
comma
l_int|40
comma
l_int|330
comma
l_int|100
comma
l_int|90
comma
l_int|240
comma
l_int|0
)brace
comma
(brace
id|XFER_PIO_1
comma
l_int|50
comma
l_int|290
comma
l_int|93
comma
l_int|383
comma
l_int|125
comma
l_int|100
comma
l_int|383
comma
l_int|0
)brace
comma
(brace
id|XFER_PIO_0
comma
l_int|70
comma
l_int|290
comma
l_int|240
comma
l_int|600
comma
l_int|165
comma
l_int|150
comma
l_int|600
comma
l_int|0
)brace
comma
(brace
id|XFER_PIO_SLOW
comma
l_int|120
comma
l_int|290
comma
l_int|240
comma
l_int|960
comma
l_int|290
comma
l_int|240
comma
l_int|960
comma
l_int|0
)brace
comma
(brace
op_minus
l_int|1
)brace
)brace
suffix:semicolon
DECL|macro|IDE_TIMING_SETUP
mdefine_line|#define IDE_TIMING_SETUP&t;0x01
DECL|macro|IDE_TIMING_ACT8B
mdefine_line|#define IDE_TIMING_ACT8B&t;0x02
DECL|macro|IDE_TIMING_REC8B
mdefine_line|#define IDE_TIMING_REC8B&t;0x04
DECL|macro|IDE_TIMING_CYC8B
mdefine_line|#define IDE_TIMING_CYC8B&t;0x08
DECL|macro|IDE_TIMING_8BIT
mdefine_line|#define IDE_TIMING_8BIT&t;&t;0x0e
DECL|macro|IDE_TIMING_ACTIVE
mdefine_line|#define IDE_TIMING_ACTIVE&t;0x10
DECL|macro|IDE_TIMING_RECOVER
mdefine_line|#define IDE_TIMING_RECOVER&t;0x20
DECL|macro|IDE_TIMING_CYCLE
mdefine_line|#define IDE_TIMING_CYCLE&t;0x40
DECL|macro|IDE_TIMING_UDMA
mdefine_line|#define IDE_TIMING_UDMA&t;&t;0x80
DECL|macro|IDE_TIMING_ALL
mdefine_line|#define IDE_TIMING_ALL&t;&t;0xff
DECL|macro|MIN
mdefine_line|#define MIN(a,b)&t;((a)&lt;(b)?(a):(b))
DECL|macro|MAX
mdefine_line|#define MAX(a,b)&t;((a)&gt;(b)?(a):(b))
DECL|macro|FIT
mdefine_line|#define FIT(v,min,max)&t;MAX(MIN(v,max),min)
DECL|macro|ENOUGH
mdefine_line|#define ENOUGH(v,unit)&t;(((v)-1)/(unit)+1)
DECL|macro|EZ
mdefine_line|#define EZ(v,unit)&t;((v)?ENOUGH(v,unit):0)
DECL|macro|XFER_MODE
mdefine_line|#define XFER_MODE&t;0xf0
DECL|macro|XFER_UDMA_133
mdefine_line|#define XFER_UDMA_133&t;0x48
DECL|macro|XFER_UDMA_100
mdefine_line|#define XFER_UDMA_100&t;0x44
DECL|macro|XFER_UDMA_66
mdefine_line|#define XFER_UDMA_66&t;0x42
DECL|macro|XFER_UDMA
mdefine_line|#define XFER_UDMA&t;0x40
DECL|macro|XFER_MWDMA
mdefine_line|#define XFER_MWDMA&t;0x20
DECL|macro|XFER_SWDMA
mdefine_line|#define XFER_SWDMA&t;0x10
DECL|macro|XFER_EPIO
mdefine_line|#define XFER_EPIO&t;0x01
DECL|macro|XFER_PIO
mdefine_line|#define XFER_PIO&t;0x00
DECL|function|ide_find_best_mode
r_static
r_int
id|ide_find_best_mode
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
id|map
)paren
(brace
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
r_int
id|best
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|id
)paren
r_return
id|XFER_PIO_SLOW
suffix:semicolon
r_if
c_cond
(paren
(paren
id|map
op_amp
id|XFER_UDMA
)paren
op_logical_and
(paren
id|id-&gt;field_valid
op_amp
l_int|4
)paren
)paren
(brace
multiline_comment|/* Want UDMA and UDMA bitmap valid */
r_if
c_cond
(paren
(paren
id|map
op_amp
id|XFER_UDMA_133
)paren
op_eq
id|XFER_UDMA_133
)paren
r_if
c_cond
(paren
(paren
id|best
op_assign
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0040
)paren
ques
c_cond
id|XFER_UDMA_6
suffix:colon
l_int|0
)paren
)paren
r_return
id|best
suffix:semicolon
r_if
c_cond
(paren
(paren
id|map
op_amp
id|XFER_UDMA_100
)paren
op_eq
id|XFER_UDMA_100
)paren
r_if
c_cond
(paren
(paren
id|best
op_assign
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0020
)paren
ques
c_cond
id|XFER_UDMA_5
suffix:colon
l_int|0
)paren
)paren
r_return
id|best
suffix:semicolon
r_if
c_cond
(paren
(paren
id|map
op_amp
id|XFER_UDMA_66
)paren
op_eq
id|XFER_UDMA_66
)paren
r_if
c_cond
(paren
(paren
id|best
op_assign
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0010
)paren
ques
c_cond
id|XFER_UDMA_4
suffix:colon
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0008
)paren
ques
c_cond
id|XFER_UDMA_3
suffix:colon
l_int|0
)paren
)paren
r_return
id|best
suffix:semicolon
r_if
c_cond
(paren
(paren
id|best
op_assign
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0004
)paren
ques
c_cond
id|XFER_UDMA_2
suffix:colon
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0002
)paren
ques
c_cond
id|XFER_UDMA_1
suffix:colon
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0001
)paren
ques
c_cond
id|XFER_UDMA_0
suffix:colon
l_int|0
)paren
)paren
r_return
id|best
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|map
op_amp
id|XFER_MWDMA
)paren
op_logical_and
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
)paren
(brace
multiline_comment|/* Want MWDMA and drive has EIDE fields */
r_if
c_cond
(paren
(paren
id|best
op_assign
(paren
id|id-&gt;dma_mword
op_amp
l_int|0x0004
)paren
ques
c_cond
id|XFER_MW_DMA_2
suffix:colon
(paren
id|id-&gt;dma_mword
op_amp
l_int|0x0002
)paren
ques
c_cond
id|XFER_MW_DMA_1
suffix:colon
(paren
id|id-&gt;dma_mword
op_amp
l_int|0x0001
)paren
ques
c_cond
id|XFER_MW_DMA_0
suffix:colon
l_int|0
)paren
)paren
r_return
id|best
suffix:semicolon
)brace
r_if
c_cond
(paren
id|map
op_amp
id|XFER_SWDMA
)paren
(brace
multiline_comment|/* Want SWDMA */
r_if
c_cond
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
(brace
multiline_comment|/* EIDE SWDMA */
r_if
c_cond
(paren
(paren
id|best
op_assign
(paren
id|id-&gt;dma_1word
op_amp
l_int|0x0004
)paren
ques
c_cond
id|XFER_SW_DMA_2
suffix:colon
(paren
id|id-&gt;dma_1word
op_amp
l_int|0x0002
)paren
ques
c_cond
id|XFER_SW_DMA_1
suffix:colon
(paren
id|id-&gt;dma_1word
op_amp
l_int|0x0001
)paren
ques
c_cond
id|XFER_SW_DMA_0
suffix:colon
l_int|0
)paren
)paren
r_return
id|best
suffix:semicolon
)brace
r_if
c_cond
(paren
id|id-&gt;capability
op_amp
l_int|1
)paren
(brace
multiline_comment|/* Pre-EIDE style SWDMA */
r_if
c_cond
(paren
(paren
id|best
op_assign
(paren
id|id-&gt;tDMA
op_eq
l_int|2
)paren
ques
c_cond
id|XFER_SW_DMA_2
suffix:colon
(paren
id|id-&gt;tDMA
op_eq
l_int|1
)paren
ques
c_cond
id|XFER_SW_DMA_1
suffix:colon
(paren
id|id-&gt;tDMA
op_eq
l_int|0
)paren
ques
c_cond
id|XFER_SW_DMA_0
suffix:colon
l_int|0
)paren
)paren
r_return
id|best
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|map
op_amp
id|XFER_EPIO
)paren
op_logical_and
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
)paren
(brace
multiline_comment|/* EIDE PIO modes */
r_if
c_cond
(paren
(paren
id|best
op_assign
(paren
id|drive-&gt;id-&gt;eide_pio_modes
op_amp
l_int|4
)paren
ques
c_cond
id|XFER_PIO_5
suffix:colon
(paren
id|drive-&gt;id-&gt;eide_pio_modes
op_amp
l_int|2
)paren
ques
c_cond
id|XFER_PIO_4
suffix:colon
(paren
id|drive-&gt;id-&gt;eide_pio_modes
op_amp
l_int|1
)paren
ques
c_cond
id|XFER_PIO_3
suffix:colon
l_int|0
)paren
)paren
r_return
id|best
suffix:semicolon
)brace
r_return
(paren
id|drive-&gt;id-&gt;tPIO
op_eq
l_int|2
)paren
ques
c_cond
id|XFER_PIO_2
suffix:colon
(paren
id|drive-&gt;id-&gt;tPIO
op_eq
l_int|1
)paren
ques
c_cond
id|XFER_PIO_1
suffix:colon
(paren
id|drive-&gt;id-&gt;tPIO
op_eq
l_int|0
)paren
ques
c_cond
id|XFER_PIO_0
suffix:colon
id|XFER_PIO_SLOW
suffix:semicolon
)brace
DECL|function|ide_timing_quantize
r_static
r_void
id|ide_timing_quantize
c_func
(paren
r_struct
id|ide_timing
op_star
id|t
comma
r_struct
id|ide_timing
op_star
id|q
comma
r_int
id|T
comma
r_int
id|UT
)paren
(brace
id|q-&gt;setup
op_assign
id|EZ
c_func
(paren
id|t-&gt;setup
op_star
l_int|1000
comma
id|T
)paren
suffix:semicolon
id|q-&gt;act8b
op_assign
id|EZ
c_func
(paren
id|t-&gt;act8b
op_star
l_int|1000
comma
id|T
)paren
suffix:semicolon
id|q-&gt;rec8b
op_assign
id|EZ
c_func
(paren
id|t-&gt;rec8b
op_star
l_int|1000
comma
id|T
)paren
suffix:semicolon
id|q-&gt;cyc8b
op_assign
id|EZ
c_func
(paren
id|t-&gt;cyc8b
op_star
l_int|1000
comma
id|T
)paren
suffix:semicolon
id|q-&gt;active
op_assign
id|EZ
c_func
(paren
id|t-&gt;active
op_star
l_int|1000
comma
id|T
)paren
suffix:semicolon
id|q-&gt;recover
op_assign
id|EZ
c_func
(paren
id|t-&gt;recover
op_star
l_int|1000
comma
id|T
)paren
suffix:semicolon
id|q-&gt;cycle
op_assign
id|EZ
c_func
(paren
id|t-&gt;cycle
op_star
l_int|1000
comma
id|T
)paren
suffix:semicolon
id|q-&gt;udma
op_assign
id|EZ
c_func
(paren
id|t-&gt;udma
op_star
l_int|1000
comma
id|UT
)paren
suffix:semicolon
)brace
DECL|function|ide_timing_merge
r_static
r_void
id|ide_timing_merge
c_func
(paren
r_struct
id|ide_timing
op_star
id|a
comma
r_struct
id|ide_timing
op_star
id|b
comma
r_struct
id|ide_timing
op_star
id|m
comma
r_int
r_int
id|what
)paren
(brace
r_if
c_cond
(paren
id|what
op_amp
id|IDE_TIMING_SETUP
)paren
id|m-&gt;setup
op_assign
id|MAX
c_func
(paren
id|a-&gt;setup
comma
id|b-&gt;setup
)paren
suffix:semicolon
r_if
c_cond
(paren
id|what
op_amp
id|IDE_TIMING_ACT8B
)paren
id|m-&gt;act8b
op_assign
id|MAX
c_func
(paren
id|a-&gt;act8b
comma
id|b-&gt;act8b
)paren
suffix:semicolon
r_if
c_cond
(paren
id|what
op_amp
id|IDE_TIMING_REC8B
)paren
id|m-&gt;rec8b
op_assign
id|MAX
c_func
(paren
id|a-&gt;rec8b
comma
id|b-&gt;rec8b
)paren
suffix:semicolon
r_if
c_cond
(paren
id|what
op_amp
id|IDE_TIMING_CYC8B
)paren
id|m-&gt;cyc8b
op_assign
id|MAX
c_func
(paren
id|a-&gt;cyc8b
comma
id|b-&gt;cyc8b
)paren
suffix:semicolon
r_if
c_cond
(paren
id|what
op_amp
id|IDE_TIMING_ACTIVE
)paren
id|m-&gt;active
op_assign
id|MAX
c_func
(paren
id|a-&gt;active
comma
id|b-&gt;active
)paren
suffix:semicolon
r_if
c_cond
(paren
id|what
op_amp
id|IDE_TIMING_RECOVER
)paren
id|m-&gt;recover
op_assign
id|MAX
c_func
(paren
id|a-&gt;recover
comma
id|b-&gt;recover
)paren
suffix:semicolon
r_if
c_cond
(paren
id|what
op_amp
id|IDE_TIMING_CYCLE
)paren
id|m-&gt;cycle
op_assign
id|MAX
c_func
(paren
id|a-&gt;cycle
comma
id|b-&gt;cycle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|what
op_amp
id|IDE_TIMING_UDMA
)paren
id|m-&gt;udma
op_assign
id|MAX
c_func
(paren
id|a-&gt;udma
comma
id|b-&gt;udma
)paren
suffix:semicolon
)brace
DECL|function|ide_timing_find_mode
r_static
r_struct
id|ide_timing
op_star
id|ide_timing_find_mode
c_func
(paren
r_int
id|speed
)paren
(brace
r_struct
id|ide_timing
op_star
id|t
suffix:semicolon
r_for
c_loop
(paren
id|t
op_assign
id|ide_timing
suffix:semicolon
id|t-&gt;mode
op_ne
id|speed
suffix:semicolon
id|t
op_increment
)paren
r_if
c_cond
(paren
id|t-&gt;mode
OL
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|t
suffix:semicolon
)brace
DECL|function|ide_timing_compute
r_static
r_int
id|ide_timing_compute
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
id|speed
comma
r_struct
id|ide_timing
op_star
id|t
comma
r_int
id|T
comma
r_int
id|UT
)paren
(brace
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
r_struct
id|ide_timing
op_star
id|s
comma
id|p
suffix:semicolon
multiline_comment|/*&n; * Find the mode.&n; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|s
op_assign
id|ide_timing_find_mode
c_func
(paren
id|speed
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n; * If the drive is an EIDE drive, it can tell us it needs extended&n; * PIO/MWDMA cycle timing.&n; */
r_if
c_cond
(paren
id|id
op_logical_and
id|id-&gt;field_valid
op_amp
l_int|2
)paren
(brace
multiline_comment|/* EIDE drive */
id|memset
c_func
(paren
op_amp
id|p
comma
l_int|0
comma
r_sizeof
(paren
id|p
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|speed
op_amp
id|XFER_MODE
)paren
(brace
r_case
id|XFER_PIO
suffix:colon
r_if
c_cond
(paren
id|speed
op_le
id|XFER_PIO_2
)paren
id|p.cycle
op_assign
id|p.cyc8b
op_assign
id|id-&gt;eide_pio
suffix:semicolon
r_else
id|p.cycle
op_assign
id|p.cyc8b
op_assign
id|id-&gt;eide_pio_iordy
suffix:semicolon
r_break
suffix:semicolon
r_case
id|XFER_MWDMA
suffix:colon
id|p.cycle
op_assign
id|id-&gt;eide_dma_min
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ide_timing_merge
c_func
(paren
op_amp
id|p
comma
id|t
comma
id|t
comma
id|IDE_TIMING_CYCLE
op_or
id|IDE_TIMING_CYC8B
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert the timing to bus clock counts.&n; */
id|ide_timing_quantize
c_func
(paren
id|s
comma
id|t
comma
id|T
comma
id|UT
)paren
suffix:semicolon
multiline_comment|/*&n; * Even in DMA/UDMA modes we still use PIO access for IDENTIFY, S.M.A.R.T&n; * and some other commands. We have to ensure that the DMA cycle timing is&n; * slower/equal than the fastest PIO timing.&n; */
r_if
c_cond
(paren
(paren
id|speed
op_amp
id|XFER_MODE
)paren
op_ne
id|XFER_PIO
)paren
(brace
id|ide_timing_compute
c_func
(paren
id|drive
comma
id|ide_find_best_mode
c_func
(paren
id|drive
comma
id|XFER_PIO
op_or
id|XFER_EPIO
)paren
comma
op_amp
id|p
comma
id|T
comma
id|UT
)paren
suffix:semicolon
id|ide_timing_merge
c_func
(paren
op_amp
id|p
comma
id|t
comma
id|t
comma
id|IDE_TIMING_ALL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Lenghten active &amp; recovery time so that cycle time is correct.&n; */
r_if
c_cond
(paren
id|t-&gt;act8b
op_plus
id|t-&gt;rec8b
OL
id|t-&gt;cyc8b
)paren
(brace
id|t-&gt;act8b
op_add_assign
(paren
id|t-&gt;cyc8b
op_minus
(paren
id|t-&gt;act8b
op_plus
id|t-&gt;rec8b
)paren
)paren
op_div
l_int|2
suffix:semicolon
id|t-&gt;rec8b
op_assign
id|t-&gt;cyc8b
op_minus
id|t-&gt;act8b
suffix:semicolon
)brace
r_if
c_cond
(paren
id|t-&gt;active
op_plus
id|t-&gt;recover
OL
id|t-&gt;cycle
)paren
(brace
id|t-&gt;active
op_add_assign
(paren
id|t-&gt;cycle
op_minus
(paren
id|t-&gt;active
op_plus
id|t-&gt;recover
)paren
)paren
op_div
l_int|2
suffix:semicolon
id|t-&gt;recover
op_assign
id|t-&gt;cycle
op_minus
id|t-&gt;active
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
