multiline_comment|/*&n; * Driver for PowerMac Burgundy onboard soundchips&n; * Copyright (c) 2001 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *   based on dmasound.c.&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef __BURGUNDY_H
DECL|macro|__BURGUNDY_H
mdefine_line|#define __BURGUNDY_H
DECL|macro|MASK_ADDR_BURGUNDY_INPSEL21
mdefine_line|#define MASK_ADDR_BURGUNDY_INPSEL21 (0x11 &lt;&lt; 12)
DECL|macro|MASK_ADDR_BURGUNDY_INPSEL3
mdefine_line|#define MASK_ADDR_BURGUNDY_INPSEL3 (0x12 &lt;&lt; 12)
DECL|macro|MASK_ADDR_BURGUNDY_GAINCH1
mdefine_line|#define MASK_ADDR_BURGUNDY_GAINCH1 (0x13 &lt;&lt; 12)
DECL|macro|MASK_ADDR_BURGUNDY_GAINCH2
mdefine_line|#define MASK_ADDR_BURGUNDY_GAINCH2 (0x14 &lt;&lt; 12)
DECL|macro|MASK_ADDR_BURGUNDY_GAINCH3
mdefine_line|#define MASK_ADDR_BURGUNDY_GAINCH3 (0x15 &lt;&lt; 12)
DECL|macro|MASK_ADDR_BURGUNDY_GAINCH4
mdefine_line|#define MASK_ADDR_BURGUNDY_GAINCH4 (0x16 &lt;&lt; 12)
DECL|macro|MASK_ADDR_BURGUNDY_VOLCH1
mdefine_line|#define MASK_ADDR_BURGUNDY_VOLCH1 (0x20 &lt;&lt; 12)
DECL|macro|MASK_ADDR_BURGUNDY_VOLCH2
mdefine_line|#define MASK_ADDR_BURGUNDY_VOLCH2 (0x21 &lt;&lt; 12)
DECL|macro|MASK_ADDR_BURGUNDY_VOLCH3
mdefine_line|#define MASK_ADDR_BURGUNDY_VOLCH3 (0x22 &lt;&lt; 12)
DECL|macro|MASK_ADDR_BURGUNDY_VOLCH4
mdefine_line|#define MASK_ADDR_BURGUNDY_VOLCH4 (0x23 &lt;&lt; 12)
DECL|macro|MASK_ADDR_BURGUNDY_OUTPUTSELECTS
mdefine_line|#define MASK_ADDR_BURGUNDY_OUTPUTSELECTS (0x2B &lt;&lt; 12)
DECL|macro|MASK_ADDR_BURGUNDY_OUTPUTENABLES
mdefine_line|#define MASK_ADDR_BURGUNDY_OUTPUTENABLES (0x2F &lt;&lt; 12)
DECL|macro|MASK_ADDR_BURGUNDY_MASTER_VOLUME
mdefine_line|#define MASK_ADDR_BURGUNDY_MASTER_VOLUME (0x30 &lt;&lt; 12)
DECL|macro|MASK_ADDR_BURGUNDY_MORE_OUTPUTENABLES
mdefine_line|#define MASK_ADDR_BURGUNDY_MORE_OUTPUTENABLES (0x60 &lt;&lt; 12)
DECL|macro|MASK_ADDR_BURGUNDY_ATTENSPEAKER
mdefine_line|#define MASK_ADDR_BURGUNDY_ATTENSPEAKER (0x62 &lt;&lt; 12)
DECL|macro|MASK_ADDR_BURGUNDY_ATTENLINEOUT
mdefine_line|#define MASK_ADDR_BURGUNDY_ATTENLINEOUT (0x63 &lt;&lt; 12)
DECL|macro|MASK_ADDR_BURGUNDY_ATTENHP
mdefine_line|#define MASK_ADDR_BURGUNDY_ATTENHP (0x64 &lt;&lt; 12)
DECL|macro|MASK_ADDR_BURGUNDY_VOLCD
mdefine_line|#define MASK_ADDR_BURGUNDY_VOLCD (MASK_ADDR_BURGUNDY_VOLCH1)
DECL|macro|MASK_ADDR_BURGUNDY_VOLLINE
mdefine_line|#define MASK_ADDR_BURGUNDY_VOLLINE (MASK_ADDR_BURGUNDY_VOLCH2)
DECL|macro|MASK_ADDR_BURGUNDY_VOLMIC
mdefine_line|#define MASK_ADDR_BURGUNDY_VOLMIC (MASK_ADDR_BURGUNDY_VOLCH3)
DECL|macro|MASK_ADDR_BURGUNDY_VOLMODEM
mdefine_line|#define MASK_ADDR_BURGUNDY_VOLMODEM (MASK_ADDR_BURGUNDY_VOLCH4)
DECL|macro|MASK_ADDR_BURGUNDY_GAINCD
mdefine_line|#define MASK_ADDR_BURGUNDY_GAINCD (MASK_ADDR_BURGUNDY_GAINCH1)
DECL|macro|MASK_ADDR_BURGUNDY_GAINLINE
mdefine_line|#define MASK_ADDR_BURGUNDY_GAINLINE (MASK_ADDR_BURGUNDY_GAINCH2)
DECL|macro|MASK_ADDR_BURGUNDY_GAINMIC
mdefine_line|#define MASK_ADDR_BURGUNDY_GAINMIC (MASK_ADDR_BURGUNDY_GAINCH3)
DECL|macro|MASK_ADDR_BURGUNDY_GAINMODEM
mdefine_line|#define MASK_ADDR_BURGUNDY_GAINMODEM (MASK_ADDR_BURGUNDY_VOLCH4)
multiline_comment|/* These are all default values for the burgundy */
DECL|macro|DEF_BURGUNDY_INPSEL21
mdefine_line|#define DEF_BURGUNDY_INPSEL21 (0xAA)
DECL|macro|DEF_BURGUNDY_INPSEL3
mdefine_line|#define DEF_BURGUNDY_INPSEL3 (0x0A)
DECL|macro|DEF_BURGUNDY_GAINCD
mdefine_line|#define DEF_BURGUNDY_GAINCD (0x33)
DECL|macro|DEF_BURGUNDY_GAINLINE
mdefine_line|#define DEF_BURGUNDY_GAINLINE (0x44)
DECL|macro|DEF_BURGUNDY_GAINMIC
mdefine_line|#define DEF_BURGUNDY_GAINMIC (0x44)
DECL|macro|DEF_BURGUNDY_GAINMODEM
mdefine_line|#define DEF_BURGUNDY_GAINMODEM (0x06)
multiline_comment|/* Remember: lowest volume here is 0x9b */
DECL|macro|DEF_BURGUNDY_VOLCD
mdefine_line|#define DEF_BURGUNDY_VOLCD (0xCCCCCCCC)
DECL|macro|DEF_BURGUNDY_VOLLINE
mdefine_line|#define DEF_BURGUNDY_VOLLINE (0x00000000)
DECL|macro|DEF_BURGUNDY_VOLMIC
mdefine_line|#define DEF_BURGUNDY_VOLMIC (0x00000000)
DECL|macro|DEF_BURGUNDY_VOLMODEM
mdefine_line|#define DEF_BURGUNDY_VOLMODEM (0xCCCCCCCC)
DECL|macro|DEF_BURGUNDY_OUTPUTSELECTS
mdefine_line|#define DEF_BURGUNDY_OUTPUTSELECTS (0x010f010f)
DECL|macro|DEF_BURGUNDY_OUTPUTENABLES
mdefine_line|#define DEF_BURGUNDY_OUTPUTENABLES (0x0A)
multiline_comment|/* #define DEF_BURGUNDY_MASTER_VOLUME (0xFFFFFFFF) */
multiline_comment|/* too loud */
DECL|macro|DEF_BURGUNDY_MASTER_VOLUME
mdefine_line|#define DEF_BURGUNDY_MASTER_VOLUME (0xDDDDDDDD)
DECL|macro|DEF_BURGUNDY_MORE_OUTPUTENABLES
mdefine_line|#define DEF_BURGUNDY_MORE_OUTPUTENABLES (0x7E)
DECL|macro|DEF_BURGUNDY_ATTENSPEAKER
mdefine_line|#define DEF_BURGUNDY_ATTENSPEAKER (0x44)
DECL|macro|DEF_BURGUNDY_ATTENLINEOUT
mdefine_line|#define DEF_BURGUNDY_ATTENLINEOUT (0xCC)
DECL|macro|DEF_BURGUNDY_ATTENHP
mdefine_line|#define DEF_BURGUNDY_ATTENHP (0xCC)
multiline_comment|/* OUTPUTENABLES bits */
DECL|macro|BURGUNDY_OUTPUT_LEFT
mdefine_line|#define BURGUNDY_OUTPUT_LEFT&t;0x02
DECL|macro|BURGUNDY_OUTPUT_RIGHT
mdefine_line|#define BURGUNDY_OUTPUT_RIGHT&t;0x04
DECL|macro|BURGUNDY_OUTPUT_INTERN
mdefine_line|#define BURGUNDY_OUTPUT_INTERN&t;0x80
multiline_comment|/* volume offset */
DECL|macro|BURGUNDY_VOLUME_OFFSET
mdefine_line|#define BURGUNDY_VOLUME_OFFSET&t;155
macro_line|#endif /* __BURGUNDY_H */
eof
