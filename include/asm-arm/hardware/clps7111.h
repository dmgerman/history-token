multiline_comment|/*&n; *  linux/include/asm-arm/hardware/clps7111.h&n; *&n; *  This file contains the hardware definitions of the CLPS7111 internal&n; *  registers.&n; *&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ASM_HARDWARE_CLPS7111_H
DECL|macro|__ASM_HARDWARE_CLPS7111_H
mdefine_line|#define __ASM_HARDWARE_CLPS7111_H
DECL|macro|CLPS7111_PHYS_BASE
mdefine_line|#define CLPS7111_PHYS_BASE&t;(0x80000000)
macro_line|#ifndef __ASSEMBLY__
DECL|macro|clps_readb
mdefine_line|#define clps_readb(off)&t;&t;__raw_readb(CLPS7111_BASE + (off))
DECL|macro|clps_readw
mdefine_line|#define clps_readw(off)&t;&t;__raw_readw(CLPS7111_BASE + (off))
DECL|macro|clps_readl
mdefine_line|#define clps_readl(off)&t;&t;__raw_readl(CLPS7111_BASE + (off))
DECL|macro|clps_writeb
mdefine_line|#define clps_writeb(val,off)&t;__raw_writeb(val, CLPS7111_BASE + (off))
DECL|macro|clps_writew
mdefine_line|#define clps_writew(val,off)&t;__raw_writew(val, CLPS7111_BASE + (off))
DECL|macro|clps_writel
mdefine_line|#define clps_writel(val,off)&t;__raw_writel(val, CLPS7111_BASE + (off))
macro_line|#endif
DECL|macro|PADR
mdefine_line|#define PADR&t;&t;(0x0000)
DECL|macro|PBDR
mdefine_line|#define PBDR&t;&t;(0x0001)
DECL|macro|PDDR
mdefine_line|#define PDDR&t;&t;(0x0003)
DECL|macro|PADDR
mdefine_line|#define PADDR&t;&t;(0x0040)
DECL|macro|PBDDR
mdefine_line|#define PBDDR&t;&t;(0x0041)
DECL|macro|PDDDR
mdefine_line|#define PDDDR&t;&t;(0x0043)
DECL|macro|PEDR
mdefine_line|#define PEDR&t;&t;(0x0080)
DECL|macro|PEDDR
mdefine_line|#define PEDDR&t;&t;(0x00c0)
DECL|macro|SYSCON1
mdefine_line|#define SYSCON1&t;&t;(0x0100)
DECL|macro|SYSFLG1
mdefine_line|#define SYSFLG1&t;&t;(0x0140)
DECL|macro|MEMCFG1
mdefine_line|#define MEMCFG1&t;&t;(0x0180)
DECL|macro|MEMCFG2
mdefine_line|#define MEMCFG2&t;&t;(0x01c0)
DECL|macro|DRFPR
mdefine_line|#define DRFPR&t;&t;(0x0200)
DECL|macro|INTSR1
mdefine_line|#define INTSR1&t;&t;(0x0240)
DECL|macro|INTMR1
mdefine_line|#define INTMR1&t;&t;(0x0280)
DECL|macro|LCDCON
mdefine_line|#define LCDCON&t;&t;(0x02c0)
DECL|macro|TC1D
mdefine_line|#define TC1D            (0x0300)
DECL|macro|TC2D
mdefine_line|#define TC2D&t;&t;(0x0340)
DECL|macro|RTCDR
mdefine_line|#define RTCDR&t;&t;(0x0380)
DECL|macro|RTCMR
mdefine_line|#define RTCMR&t;&t;(0x03c0)
DECL|macro|PMPCON
mdefine_line|#define PMPCON&t;&t;(0x0400)
DECL|macro|CODR
mdefine_line|#define CODR&t;&t;(0x0440)
DECL|macro|UARTDR1
mdefine_line|#define UARTDR1&t;&t;(0x0480)
DECL|macro|UBRLCR1
mdefine_line|#define UBRLCR1&t;&t;(0x04c0)
DECL|macro|SYNCIO
mdefine_line|#define SYNCIO&t;&t;(0x0500)
DECL|macro|PALLSW
mdefine_line|#define PALLSW&t;&t;(0x0540)
DECL|macro|PALMSW
mdefine_line|#define PALMSW&t;&t;(0x0580)
DECL|macro|STFCLR
mdefine_line|#define STFCLR&t;&t;(0x05c0)
DECL|macro|BLEOI
mdefine_line|#define BLEOI&t;&t;(0x0600)
DECL|macro|MCEOI
mdefine_line|#define MCEOI&t;&t;(0x0640)
DECL|macro|TEOI
mdefine_line|#define TEOI&t;&t;(0x0680)
DECL|macro|TC1EOI
mdefine_line|#define TC1EOI&t;&t;(0x06c0)
DECL|macro|TC2EOI
mdefine_line|#define TC2EOI&t;&t;(0x0700)
DECL|macro|RTCEOI
mdefine_line|#define RTCEOI&t;&t;(0x0740)
DECL|macro|UMSEOI
mdefine_line|#define UMSEOI&t;&t;(0x0780)
DECL|macro|COEOI
mdefine_line|#define COEOI&t;&t;(0x07c0)
DECL|macro|HALT
mdefine_line|#define HALT&t;&t;(0x0800)
DECL|macro|STDBY
mdefine_line|#define STDBY&t;&t;(0x0840)
DECL|macro|FBADDR
mdefine_line|#define FBADDR&t;&t;(0x1000)
DECL|macro|SYSCON2
mdefine_line|#define SYSCON2&t;&t;(0x1100)
DECL|macro|SYSFLG2
mdefine_line|#define SYSFLG2&t;&t;(0x1140)
DECL|macro|INTSR2
mdefine_line|#define INTSR2&t;&t;(0x1240)
DECL|macro|INTMR2
mdefine_line|#define INTMR2&t;&t;(0x1280)
DECL|macro|UARTDR2
mdefine_line|#define UARTDR2&t;&t;(0x1480)
DECL|macro|UBRLCR2
mdefine_line|#define UBRLCR2&t;&t;(0x14c0)
DECL|macro|SS2DR
mdefine_line|#define SS2DR&t;&t;(0x1500)
DECL|macro|SRXEOF
mdefine_line|#define SRXEOF&t;&t;(0x1600)
DECL|macro|SS2POP
mdefine_line|#define SS2POP&t;&t;(0x16c0)
DECL|macro|KBDEOI
mdefine_line|#define KBDEOI&t;&t;(0x1700)
multiline_comment|/* common bits: SYSCON1 / SYSCON2 */
DECL|macro|SYSCON_UARTEN
mdefine_line|#define SYSCON_UARTEN&t;&t;(1 &lt;&lt; 8)
DECL|macro|SYSCON1_KBDSCAN
mdefine_line|#define SYSCON1_KBDSCAN(x)&t;((x) &amp; 15)
DECL|macro|SYSCON1_KBDSCANMASK
mdefine_line|#define SYSCON1_KBDSCANMASK&t;(15)
DECL|macro|SYSCON1_TC1M
mdefine_line|#define SYSCON1_TC1M&t;&t;(1 &lt;&lt; 4)
DECL|macro|SYSCON1_TC1S
mdefine_line|#define SYSCON1_TC1S&t;&t;(1 &lt;&lt; 5)
DECL|macro|SYSCON1_TC2M
mdefine_line|#define SYSCON1_TC2M&t;&t;(1 &lt;&lt; 6)
DECL|macro|SYSCON1_TC2S
mdefine_line|#define SYSCON1_TC2S&t;&t;(1 &lt;&lt; 7)
DECL|macro|SYSCON1_UART1EN
mdefine_line|#define SYSCON1_UART1EN&t;&t;SYSCON_UARTEN
DECL|macro|SYSCON1_BZTOG
mdefine_line|#define SYSCON1_BZTOG&t;&t;(1 &lt;&lt; 9)
DECL|macro|SYSCON1_BZMOD
mdefine_line|#define SYSCON1_BZMOD&t;&t;(1 &lt;&lt; 10)
DECL|macro|SYSCON1_DBGEN
mdefine_line|#define SYSCON1_DBGEN&t;&t;(1 &lt;&lt; 11)
DECL|macro|SYSCON1_LCDEN
mdefine_line|#define SYSCON1_LCDEN&t;&t;(1 &lt;&lt; 12)
DECL|macro|SYSCON1_CDENTX
mdefine_line|#define SYSCON1_CDENTX&t;&t;(1 &lt;&lt; 13)
DECL|macro|SYSCON1_CDENRX
mdefine_line|#define SYSCON1_CDENRX&t;&t;(1 &lt;&lt; 14)
DECL|macro|SYSCON1_SIREN
mdefine_line|#define SYSCON1_SIREN&t;&t;(1 &lt;&lt; 15)
DECL|macro|SYSCON1_ADCKSEL
mdefine_line|#define SYSCON1_ADCKSEL(x)&t;(((x) &amp; 3) &lt;&lt; 16)
DECL|macro|SYSCON1_ADCKSEL_MASK
mdefine_line|#define SYSCON1_ADCKSEL_MASK&t;(3 &lt;&lt; 16)
DECL|macro|SYSCON1_EXCKEN
mdefine_line|#define SYSCON1_EXCKEN&t;&t;(1 &lt;&lt; 18)
DECL|macro|SYSCON1_WAKEDIS
mdefine_line|#define SYSCON1_WAKEDIS&t;&t;(1 &lt;&lt; 19)
DECL|macro|SYSCON1_IRTXM
mdefine_line|#define SYSCON1_IRTXM&t;&t;(1 &lt;&lt; 20)
multiline_comment|/* common bits: SYSFLG1 / SYSFLG2 */
DECL|macro|SYSFLG_UBUSY
mdefine_line|#define SYSFLG_UBUSY&t;&t;(1 &lt;&lt; 11)
DECL|macro|SYSFLG_URXFE
mdefine_line|#define SYSFLG_URXFE&t;&t;(1 &lt;&lt; 22)
DECL|macro|SYSFLG_UTXFF
mdefine_line|#define SYSFLG_UTXFF&t;&t;(1 &lt;&lt; 23)
DECL|macro|SYSFLG1_MCDR
mdefine_line|#define SYSFLG1_MCDR&t;&t;(1 &lt;&lt; 0)
DECL|macro|SYSFLG1_DCDET
mdefine_line|#define SYSFLG1_DCDET&t;&t;(1 &lt;&lt; 1)
DECL|macro|SYSFLG1_WUDR
mdefine_line|#define SYSFLG1_WUDR&t;&t;(1 &lt;&lt; 2)
DECL|macro|SYSFLG1_WUON
mdefine_line|#define SYSFLG1_WUON&t;&t;(1 &lt;&lt; 3)
DECL|macro|SYSFLG1_CTS
mdefine_line|#define SYSFLG1_CTS&t;&t;(1 &lt;&lt; 8)
DECL|macro|SYSFLG1_DSR
mdefine_line|#define SYSFLG1_DSR&t;&t;(1 &lt;&lt; 9)
DECL|macro|SYSFLG1_DCD
mdefine_line|#define SYSFLG1_DCD&t;&t;(1 &lt;&lt; 10)
DECL|macro|SYSFLG1_UBUSY
mdefine_line|#define SYSFLG1_UBUSY&t;&t;SYSFLG_UBUSY
DECL|macro|SYSFLG1_NBFLG
mdefine_line|#define SYSFLG1_NBFLG&t;&t;(1 &lt;&lt; 12)
DECL|macro|SYSFLG1_RSTFLG
mdefine_line|#define SYSFLG1_RSTFLG&t;&t;(1 &lt;&lt; 13)
DECL|macro|SYSFLG1_PFFLG
mdefine_line|#define SYSFLG1_PFFLG&t;&t;(1 &lt;&lt; 14)
DECL|macro|SYSFLG1_CLDFLG
mdefine_line|#define SYSFLG1_CLDFLG&t;&t;(1 &lt;&lt; 15)
DECL|macro|SYSFLG1_URXFE
mdefine_line|#define SYSFLG1_URXFE&t;&t;SYSFLG_URXFE
DECL|macro|SYSFLG1_UTXFF
mdefine_line|#define SYSFLG1_UTXFF&t;&t;SYSFLG_UTXFF
DECL|macro|SYSFLG1_CRXFE
mdefine_line|#define SYSFLG1_CRXFE&t;&t;(1 &lt;&lt; 24)
DECL|macro|SYSFLG1_CTXFF
mdefine_line|#define SYSFLG1_CTXFF&t;&t;(1 &lt;&lt; 25)
DECL|macro|SYSFLG1_SSIBUSY
mdefine_line|#define SYSFLG1_SSIBUSY&t;&t;(1 &lt;&lt; 26)
DECL|macro|SYSFLG1_ID
mdefine_line|#define SYSFLG1_ID&t;&t;(1 &lt;&lt; 29)
DECL|macro|SYSFLG2_SSRXOF
mdefine_line|#define SYSFLG2_SSRXOF&t;&t;(1 &lt;&lt; 0)
DECL|macro|SYSFLG2_RESVAL
mdefine_line|#define SYSFLG2_RESVAL&t;&t;(1 &lt;&lt; 1)
DECL|macro|SYSFLG2_RESFRM
mdefine_line|#define SYSFLG2_RESFRM&t;&t;(1 &lt;&lt; 2)
DECL|macro|SYSFLG2_SS2RXFE
mdefine_line|#define SYSFLG2_SS2RXFE&t;&t;(1 &lt;&lt; 3)
DECL|macro|SYSFLG2_SS2TXFF
mdefine_line|#define SYSFLG2_SS2TXFF&t;&t;(1 &lt;&lt; 4)
DECL|macro|SYSFLG2_SS2TXUF
mdefine_line|#define SYSFLG2_SS2TXUF&t;&t;(1 &lt;&lt; 5)
DECL|macro|SYSFLG2_CKMODE
mdefine_line|#define SYSFLG2_CKMODE&t;&t;(1 &lt;&lt; 6)
DECL|macro|SYSFLG2_UBUSY
mdefine_line|#define SYSFLG2_UBUSY&t;&t;SYSFLG_UBUSY
DECL|macro|SYSFLG2_URXFE
mdefine_line|#define SYSFLG2_URXFE&t;&t;SYSFLG_URXFE
DECL|macro|SYSFLG2_UTXFF
mdefine_line|#define SYSFLG2_UTXFF&t;&t;SYSFLG_UTXFF
DECL|macro|LCDCON_GSEN
mdefine_line|#define LCDCON_GSEN&t;&t;(1 &lt;&lt; 30)
DECL|macro|LCDCON_GSMD
mdefine_line|#define LCDCON_GSMD&t;&t;(1 &lt;&lt; 31)
DECL|macro|SYSCON2_SERSEL
mdefine_line|#define SYSCON2_SERSEL&t;&t;(1 &lt;&lt; 0)
DECL|macro|SYSCON2_KBD6
mdefine_line|#define SYSCON2_KBD6&t;&t;(1 &lt;&lt; 1)
DECL|macro|SYSCON2_DRAMZ
mdefine_line|#define SYSCON2_DRAMZ&t;&t;(1 &lt;&lt; 2)
DECL|macro|SYSCON2_KBWEN
mdefine_line|#define SYSCON2_KBWEN&t;&t;(1 &lt;&lt; 3)
DECL|macro|SYSCON2_SS2TXEN
mdefine_line|#define SYSCON2_SS2TXEN&t;&t;(1 &lt;&lt; 4)
DECL|macro|SYSCON2_PCCARD1
mdefine_line|#define SYSCON2_PCCARD1&t;&t;(1 &lt;&lt; 5)
DECL|macro|SYSCON2_PCCARD2
mdefine_line|#define SYSCON2_PCCARD2&t;&t;(1 &lt;&lt; 6)
DECL|macro|SYSCON2_SS2RXEN
mdefine_line|#define SYSCON2_SS2RXEN&t;&t;(1 &lt;&lt; 7)
DECL|macro|SYSCON2_UART2EN
mdefine_line|#define SYSCON2_UART2EN&t;&t;SYSCON_UARTEN
DECL|macro|SYSCON2_SS2MAEN
mdefine_line|#define SYSCON2_SS2MAEN&t;&t;(1 &lt;&lt; 9)
DECL|macro|SYSCON2_OSTB
mdefine_line|#define SYSCON2_OSTB&t;&t;(1 &lt;&lt; 12)
DECL|macro|SYSCON2_CLKENSL
mdefine_line|#define SYSCON2_CLKENSL&t;&t;(1 &lt;&lt; 13)
DECL|macro|SYSCON2_BUZFREQ
mdefine_line|#define SYSCON2_BUZFREQ&t;&t;(1 &lt;&lt; 14)
multiline_comment|/* common bits: UARTDR1 / UARTDR2 */
DECL|macro|UARTDR_FRMERR
mdefine_line|#define UARTDR_FRMERR&t;&t;(1 &lt;&lt; 8)
DECL|macro|UARTDR_PARERR
mdefine_line|#define UARTDR_PARERR&t;&t;(1 &lt;&lt; 9)
DECL|macro|UARTDR_OVERR
mdefine_line|#define UARTDR_OVERR&t;&t;(1 &lt;&lt; 10)
multiline_comment|/* common bits: UBRLCR1 / UBRLCR2 */
DECL|macro|UBRLCR_BAUD_MASK
mdefine_line|#define UBRLCR_BAUD_MASK&t;((1 &lt;&lt; 12) - 1)
DECL|macro|UBRLCR_BREAK
mdefine_line|#define UBRLCR_BREAK&t;&t;(1 &lt;&lt; 12)
DECL|macro|UBRLCR_PRTEN
mdefine_line|#define UBRLCR_PRTEN&t;&t;(1 &lt;&lt; 13)
DECL|macro|UBRLCR_EVENPRT
mdefine_line|#define UBRLCR_EVENPRT&t;&t;(1 &lt;&lt; 14)
DECL|macro|UBRLCR_XSTOP
mdefine_line|#define UBRLCR_XSTOP&t;&t;(1 &lt;&lt; 15)
DECL|macro|UBRLCR_FIFOEN
mdefine_line|#define UBRLCR_FIFOEN&t;&t;(1 &lt;&lt; 16)
DECL|macro|UBRLCR_WRDLEN5
mdefine_line|#define UBRLCR_WRDLEN5&t;&t;(0 &lt;&lt; 17)
DECL|macro|UBRLCR_WRDLEN6
mdefine_line|#define UBRLCR_WRDLEN6&t;&t;(1 &lt;&lt; 17)
DECL|macro|UBRLCR_WRDLEN7
mdefine_line|#define UBRLCR_WRDLEN7&t;&t;(2 &lt;&lt; 17)
DECL|macro|UBRLCR_WRDLEN8
mdefine_line|#define UBRLCR_WRDLEN8&t;&t;(3 &lt;&lt; 17)
DECL|macro|UBRLCR_WRDLEN_MASK
mdefine_line|#define UBRLCR_WRDLEN_MASK&t;(3 &lt;&lt; 17)
DECL|macro|SYNCIO_SMCKEN
mdefine_line|#define SYNCIO_SMCKEN&t;&t;(1 &lt;&lt; 13)
DECL|macro|SYNCIO_TXFRMEN
mdefine_line|#define SYNCIO_TXFRMEN&t;&t;(1 &lt;&lt; 14)
macro_line|#endif /* __ASM_HARDWARE_CLPS7111_H */
eof
