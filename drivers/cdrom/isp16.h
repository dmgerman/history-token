multiline_comment|/* -- isp16.h&n; *&n; *  Header for detection and initialisation of cdrom interface (only) on&n; *  ISP16 (MAD16, Mozart) sound card.&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
multiline_comment|/* These are the default values */
DECL|macro|ISP16_CDROM_TYPE
mdefine_line|#define ISP16_CDROM_TYPE &quot;Sanyo&quot;
DECL|macro|ISP16_CDROM_IO_BASE
mdefine_line|#define ISP16_CDROM_IO_BASE 0x340
DECL|macro|ISP16_CDROM_IRQ
mdefine_line|#define ISP16_CDROM_IRQ 0
DECL|macro|ISP16_CDROM_DMA
mdefine_line|#define ISP16_CDROM_DMA 0
multiline_comment|/* Some (Media)Magic */
multiline_comment|/* define types of drive the interface on an ISP16 card may be looking at */
DECL|macro|ISP16_DRIVE_X
mdefine_line|#define ISP16_DRIVE_X 0x00
DECL|macro|ISP16_SONY
mdefine_line|#define ISP16_SONY  0x02
DECL|macro|ISP16_PANASONIC0
mdefine_line|#define ISP16_PANASONIC0 0x02
DECL|macro|ISP16_SANYO0
mdefine_line|#define ISP16_SANYO0 0x02
DECL|macro|ISP16_MITSUMI
mdefine_line|#define ISP16_MITSUMI  0x04
DECL|macro|ISP16_PANASONIC1
mdefine_line|#define ISP16_PANASONIC1 0x06
DECL|macro|ISP16_SANYO1
mdefine_line|#define ISP16_SANYO1 0x06
DECL|macro|ISP16_DRIVE_NOT_USED
mdefine_line|#define ISP16_DRIVE_NOT_USED 0x08  /* not used */
DECL|macro|ISP16_DRIVE_SET_MASK
mdefine_line|#define ISP16_DRIVE_SET_MASK 0xF1  /* don&squot;t change 0-bit or 4-7-bits*/
multiline_comment|/* ...for port */
DECL|macro|ISP16_DRIVE_SET_PORT
mdefine_line|#define ISP16_DRIVE_SET_PORT 0xF8D
multiline_comment|/* set io parameters */
DECL|macro|ISP16_BASE_340
mdefine_line|#define ISP16_BASE_340  0x00
DECL|macro|ISP16_BASE_330
mdefine_line|#define ISP16_BASE_330  0x40
DECL|macro|ISP16_BASE_360
mdefine_line|#define ISP16_BASE_360  0x80
DECL|macro|ISP16_BASE_320
mdefine_line|#define ISP16_BASE_320  0xC0
DECL|macro|ISP16_IRQ_X
mdefine_line|#define ISP16_IRQ_X  0x00
DECL|macro|ISP16_IRQ_5
mdefine_line|#define ISP16_IRQ_5  0x04  /* shouldn&squot;t be used to avoid sound card conflicts */
DECL|macro|ISP16_IRQ_7
mdefine_line|#define ISP16_IRQ_7  0x08  /* shouldn&squot;t be used to avoid sound card conflicts */
DECL|macro|ISP16_IRQ_3
mdefine_line|#define ISP16_IRQ_3  0x0C
DECL|macro|ISP16_IRQ_9
mdefine_line|#define ISP16_IRQ_9  0x10
DECL|macro|ISP16_IRQ_10
mdefine_line|#define ISP16_IRQ_10  0x14
DECL|macro|ISP16_IRQ_11
mdefine_line|#define ISP16_IRQ_11  0x18
DECL|macro|ISP16_DMA_X
mdefine_line|#define ISP16_DMA_X  0x03
DECL|macro|ISP16_DMA_3
mdefine_line|#define ISP16_DMA_3  0x00
DECL|macro|ISP16_DMA_5
mdefine_line|#define ISP16_DMA_5  0x00
DECL|macro|ISP16_DMA_6
mdefine_line|#define ISP16_DMA_6  0x01
DECL|macro|ISP16_DMA_7
mdefine_line|#define ISP16_DMA_7  0x02
DECL|macro|ISP16_IO_SET_MASK
mdefine_line|#define ISP16_IO_SET_MASK  0x20  /* don&squot;t change 5-bit */
multiline_comment|/* ...for port */
DECL|macro|ISP16_IO_SET_PORT
mdefine_line|#define ISP16_IO_SET_PORT  0xF8E
multiline_comment|/* enable the card */
DECL|macro|ISP16_C928__ENABLE_PORT
mdefine_line|#define ISP16_C928__ENABLE_PORT  0xF90  /* ISP16 with OPTi 82C928 chip */
DECL|macro|ISP16_C929__ENABLE_PORT
mdefine_line|#define ISP16_C929__ENABLE_PORT  0xF91  /* ISP16 with OPTi 82C929 chip */
DECL|macro|ISP16_ENABLE_CDROM
mdefine_line|#define ISP16_ENABLE_CDROM  0x80  /* seven bit */
multiline_comment|/* the magic stuff */
DECL|macro|ISP16_CTRL_PORT
mdefine_line|#define ISP16_CTRL_PORT  0xF8F
DECL|macro|ISP16_C928__CTRL
mdefine_line|#define ISP16_C928__CTRL  0xE2  /* ISP16 with OPTi 82C928 chip */
DECL|macro|ISP16_C929__CTRL
mdefine_line|#define ISP16_C929__CTRL  0xE3  /* ISP16 with OPTi 82C929 chip */
DECL|macro|ISP16_IO_BASE
mdefine_line|#define ISP16_IO_BASE 0xF8D
DECL|macro|ISP16_IO_SIZE
mdefine_line|#define ISP16_IO_SIZE 5  /* ports used from 0xF8D up to 0xF91 */
r_int
id|isp16_init
c_func
(paren
r_void
)paren
suffix:semicolon
eof
