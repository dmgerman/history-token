macro_line|#ifndef _ATA_TIMING_H
DECL|macro|_ATA_TIMING_H
mdefine_line|#define _ATA_TIMING_H
multiline_comment|/*&n; * $Id: ata-timing.h,v 2.0 2002/03/12 13:02:22 vojtech Exp $&n; *&n; *  Copyright (C) 1996  Linus Torvalds, Igor Abramov, and Mark Lord&n; *  Copyright (C) 1999-2001 Vojtech Pavlik&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
DECL|macro|XFER_PIO_5
mdefine_line|#define XFER_PIO_5&t;&t;0x0d
DECL|macro|XFER_UDMA_SLOW
mdefine_line|#define XFER_UDMA_SLOW&t;&t;0x4f
DECL|struct|ata_timing
r_struct
id|ata_timing
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
r_extern
r_struct
id|ata_timing
id|ata_timing
(braket
)braket
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
DECL|macro|FIT
mdefine_line|#define FIT(v,x,y)&t;max_t(int,min_t(int,v,y),x)
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
multiline_comment|/* External interface to host chips channel timing setup.&n; *&n; * It&squot;s a bit elaborate due to the legacy we have to bear.&n; */
r_extern
r_int
id|ata_timing_mode
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_int
id|map
)paren
suffix:semicolon
r_extern
r_void
id|ata_timing_quantize
c_func
(paren
r_struct
id|ata_timing
op_star
id|t
comma
r_struct
id|ata_timing
op_star
id|q
comma
r_int
id|T
comma
r_int
id|UT
)paren
suffix:semicolon
r_extern
r_void
id|ata_timing_merge
c_func
(paren
r_struct
id|ata_timing
op_star
id|a
comma
r_struct
id|ata_timing
op_star
id|b
comma
r_struct
id|ata_timing
op_star
id|m
comma
r_int
r_int
id|what
)paren
suffix:semicolon
r_void
id|ata_timing_merge_8bit
c_func
(paren
r_struct
id|ata_timing
op_star
id|t
)paren
suffix:semicolon
r_extern
r_struct
id|ata_timing
op_star
id|ata_timing_data
c_func
(paren
r_int
id|speed
)paren
suffix:semicolon
r_extern
r_int
id|ata_timing_compute
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_int
id|speed
comma
r_struct
id|ata_timing
op_star
id|t
comma
r_int
id|T
comma
r_int
id|UT
)paren
suffix:semicolon
r_extern
id|u8
id|ata_best_pio_mode
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
suffix:semicolon
macro_line|#endif
eof
