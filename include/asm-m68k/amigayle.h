multiline_comment|/*&n;** asm-m68k/amigayle.h -- This header defines the registers of the gayle chip&n;**                        found on the Amiga 1200&n;**                        This information was found by disassembling card.resource,&n;**                        so the definitions may not be 100% correct&n;**                        anyone has an official doc ?&n;**&n;** Copyright 1997 by Alain Malek&n;**&n;** This file is subject to the terms and conditions of the GNU General Public&n;** License.  See the file COPYING in the main directory of this archive&n;** for more details.&n;**&n;** Created: 11/28/97 by Alain Malek&n;*/
macro_line|#ifndef _M68K_AMIGAYLE_H_
DECL|macro|_M68K_AMIGAYLE_H_
mdefine_line|#define _M68K_AMIGAYLE_H_
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
multiline_comment|/* memory layout */
DECL|macro|GAYLE_RAM
mdefine_line|#define GAYLE_RAM&t;&t;(0x600000+zTwoBase)
DECL|macro|GAYLE_RAMSIZE
mdefine_line|#define GAYLE_RAMSIZE&t;&t;(0x400000)
DECL|macro|GAYLE_ATTRIBUTE
mdefine_line|#define GAYLE_ATTRIBUTE&t;&t;(0xa00000+zTwoBase)
DECL|macro|GAYLE_ATTRIBUTESIZE
mdefine_line|#define GAYLE_ATTRIBUTESIZE&t;(0x020000)
DECL|macro|GAYLE_IO
mdefine_line|#define GAYLE_IO&t;&t;(0xa20000+zTwoBase)&t;/* 16bit and even 8bit registers */
DECL|macro|GAYLE_IOSIZE
mdefine_line|#define GAYLE_IOSIZE&t;&t;(0x010000)
DECL|macro|GAYLE_IO_8BITODD
mdefine_line|#define GAYLE_IO_8BITODD&t;(0xa30000+zTwoBase)&t;/* odd 8bit registers */
multiline_comment|/* offset for accessing odd IO registers */
DECL|macro|GAYLE_ODD
mdefine_line|#define GAYLE_ODD&t;&t;(GAYLE_IO_8BITODD-GAYLE_IO-1)
multiline_comment|/* GAYLE registers */
DECL|struct|GAYLE
r_struct
id|GAYLE
(brace
DECL|member|cardstatus
id|u_char
id|cardstatus
suffix:semicolon
DECL|member|pad0
id|u_char
id|pad0
(braket
l_int|0x1000
op_minus
l_int|1
)braket
suffix:semicolon
DECL|member|intreq
id|u_char
id|intreq
suffix:semicolon
DECL|member|pad1
id|u_char
id|pad1
(braket
l_int|0x1000
op_minus
l_int|1
)braket
suffix:semicolon
DECL|member|inten
id|u_char
id|inten
suffix:semicolon
DECL|member|pad2
id|u_char
id|pad2
(braket
l_int|0x1000
op_minus
l_int|1
)braket
suffix:semicolon
DECL|member|config
id|u_char
id|config
suffix:semicolon
DECL|member|pad3
id|u_char
id|pad3
(braket
l_int|0x1000
op_minus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|GAYLE_ADDRESS
mdefine_line|#define GAYLE_ADDRESS&t;(0xda8000)&t;/* gayle main registers base address */
DECL|macro|GAYLE_RESET
mdefine_line|#define GAYLE_RESET&t;(0xa40000)&t;/* write 0x00 to start reset,&n;                                           read 1 byte to stop reset */
DECL|macro|gayle
mdefine_line|#define gayle (*(volatile struct GAYLE *)(zTwoBase+GAYLE_ADDRESS))
DECL|macro|gayle_reset
mdefine_line|#define gayle_reset (*(volatile u_char *)(zTwoBase+GAYLE_RESET))
DECL|macro|gayle_attribute
mdefine_line|#define gayle_attribute ((volatile u_char *)(GAYLE_ATTRIBUTE))
macro_line|#if 0
mdefine_line|#define gayle_inb(a) readb( GAYLE_IO+(a)+(((a)&amp;1)*GAYLE_ODD) )
mdefine_line|#define gayle_outb(v,a) writeb( v, GAYLE_IO+(a)+(((a)&amp;1)*GAYLE_ODD) )
mdefine_line|#define gayle_inw(a) readw( GAYLE_IO+(a) )
mdefine_line|#define gayle_outw(v,a) writew( v, GAYLE_IO+(a) )
macro_line|#endif
multiline_comment|/* GAYLE_CARDSTATUS bit def */
DECL|macro|GAYLE_CS_CCDET
mdefine_line|#define GAYLE_CS_CCDET&t;&t;0x40&t;/* credit card detect */
DECL|macro|GAYLE_CS_BVD1
mdefine_line|#define GAYLE_CS_BVD1&t;&t;0x20&t;/* battery voltage detect 1 */
DECL|macro|GAYLE_CS_SC
mdefine_line|#define GAYLE_CS_SC&t;&t;0x20&t;/* credit card status change */
DECL|macro|GAYLE_CS_BVD2
mdefine_line|#define GAYLE_CS_BVD2&t;&t;0x10&t;/* battery voltage detect 2 */
DECL|macro|GAYLE_CS_DA
mdefine_line|#define GAYLE_CS_DA&t;&t;0x10&t;/* digital audio */
DECL|macro|GAYLE_CS_WR
mdefine_line|#define GAYLE_CS_WR&t;&t;0x08&t;/* write enable (1 == enabled) */
DECL|macro|GAYLE_CS_BSY
mdefine_line|#define GAYLE_CS_BSY&t;&t;0x04&t;/* credit card busy */
DECL|macro|GAYLE_CS_IRQ
mdefine_line|#define GAYLE_CS_IRQ&t;&t;0x04&t;/* interrupt request */
multiline_comment|/* GAYLE_IRQ bit def */
DECL|macro|GAYLE_IRQ_IDE
mdefine_line|#define GAYLE_IRQ_IDE&t;&t;0x80
DECL|macro|GAYLE_IRQ_CCDET
mdefine_line|#define GAYLE_IRQ_CCDET&t;&t;0x40
DECL|macro|GAYLE_IRQ_BVD1
mdefine_line|#define GAYLE_IRQ_BVD1&t;&t;0x20
DECL|macro|GAYLE_IRQ_SC
mdefine_line|#define GAYLE_IRQ_SC&t;&t;0x20
DECL|macro|GAYLE_IRQ_BVD2
mdefine_line|#define GAYLE_IRQ_BVD2&t;&t;0x10
DECL|macro|GAYLE_IRQ_DA
mdefine_line|#define GAYLE_IRQ_DA&t;&t;0x10
DECL|macro|GAYLE_IRQ_WR
mdefine_line|#define GAYLE_IRQ_WR&t;&t;0x08
DECL|macro|GAYLE_IRQ_BSY
mdefine_line|#define GAYLE_IRQ_BSY&t;&t;0x04
DECL|macro|GAYLE_IRQ_IRQ
mdefine_line|#define GAYLE_IRQ_IRQ&t;&t;0x04
DECL|macro|GAYLE_IRQ_IDEACK1
mdefine_line|#define GAYLE_IRQ_IDEACK1&t;0x02
DECL|macro|GAYLE_IRQ_IDEACK0
mdefine_line|#define GAYLE_IRQ_IDEACK0&t;0x01
multiline_comment|/* GAYLE_CONFIG bit def&n;   (bit 0-1 for program voltage, bit 2-3 for access speed */
DECL|macro|GAYLE_CFG_0V
mdefine_line|#define GAYLE_CFG_0V&t;&t;0x00
DECL|macro|GAYLE_CFG_5V
mdefine_line|#define GAYLE_CFG_5V&t;&t;0x01
DECL|macro|GAYLE_CFG_12V
mdefine_line|#define GAYLE_CFG_12V&t;&t;0x02
DECL|macro|GAYLE_CFG_100NS
mdefine_line|#define GAYLE_CFG_100NS&t;&t;0x08
DECL|macro|GAYLE_CFG_150NS
mdefine_line|#define GAYLE_CFG_150NS&t;&t;0x04
DECL|macro|GAYLE_CFG_250NS
mdefine_line|#define GAYLE_CFG_250NS&t;&t;0x00
DECL|macro|GAYLE_CFG_720NS
mdefine_line|#define GAYLE_CFG_720NS&t;&t;0x0c
macro_line|#endif /* asm-m68k/amigayle.h */
eof
