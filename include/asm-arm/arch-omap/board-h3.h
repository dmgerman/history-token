multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/board-h3.h&n; *&n; * Copyright (C) 2001 RidgeRun, Inc.&n; * Copyright (C) 2004 Texas Instruments, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASM_ARCH_OMAP_H3_H
DECL|macro|__ASM_ARCH_OMAP_H3_H
mdefine_line|#define __ASM_ARCH_OMAP_H3_H
multiline_comment|/* In OMAP1710 H3 the Ethernet is directly connected to CS1 */
DECL|macro|OMAP1710_ETHR_BASE
mdefine_line|#define OMAP1710_ETHR_BASE&t;&t;0xE8000000
DECL|macro|OMAP1710_ETHR_SIZE
mdefine_line|#define OMAP1710_ETHR_SIZE&t;&t;SZ_4K
DECL|macro|OMAP1710_ETHR_START
mdefine_line|#define OMAP1710_ETHR_START&t;&t;0x04000000
multiline_comment|/* Intel STRATA NOR flash at CS3 */
DECL|macro|OMAP_NOR_FLASH_BASE
mdefine_line|#define OMAP_NOR_FLASH_BASE&t;&t;0xD8000000
DECL|macro|OMAP_NOR_FLASH_SIZE
mdefine_line|#define OMAP_NOR_FLASH_SIZE&t;&t;SZ_32M
DECL|macro|OMAP_NOR_FLASH_START
mdefine_line|#define OMAP_NOR_FLASH_START&t;&t;0x00000000
DECL|macro|MAXIRQNUM
mdefine_line|#define MAXIRQNUM&t;&t;&t;(IH_BOARD_BASE)
DECL|macro|MAXFIQNUM
mdefine_line|#define MAXFIQNUM&t;&t;&t;MAXIRQNUM
DECL|macro|MAXSWINUM
mdefine_line|#define MAXSWINUM&t;&t;&t;MAXIRQNUM
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;&t;(MAXIRQNUM + 1)
DECL|macro|OMAP_MCBSP1_BASE
mdefine_line|#define OMAP_MCBSP1_BASE&t;&t;OMAP1610_MCBSP1_BASE
DECL|macro|AUDIO_DRR2
mdefine_line|#define AUDIO_DRR2  (OMAP_MCBSP1_BASE + 0x00)
DECL|macro|AUDIO_DRR1
mdefine_line|#define AUDIO_DRR1  (OMAP_MCBSP1_BASE + 0x02)
DECL|macro|AUDIO_DXR2
mdefine_line|#define AUDIO_DXR2  (OMAP_MCBSP1_BASE + 0x04)
DECL|macro|AUDIO_DXR1
mdefine_line|#define AUDIO_DXR1  (OMAP_MCBSP1_BASE + 0x06)
DECL|macro|AUDIO_SPCR2
mdefine_line|#define AUDIO_SPCR2 (OMAP_MCBSP1_BASE + 0x08)
DECL|macro|AUDIO_SPCR1
mdefine_line|#define AUDIO_SPCR1 (OMAP_MCBSP1_BASE + 0x0a)
DECL|macro|AUDIO_RCR2
mdefine_line|#define AUDIO_RCR2  (OMAP_MCBSP1_BASE + 0x0c)
DECL|macro|AUDIO_RCR1
mdefine_line|#define AUDIO_RCR1  (OMAP_MCBSP1_BASE + 0x0e)
DECL|macro|AUDIO_XCR2
mdefine_line|#define AUDIO_XCR2  (OMAP_MCBSP1_BASE + 0x10)
DECL|macro|AUDIO_XCR1
mdefine_line|#define AUDIO_XCR1  (OMAP_MCBSP1_BASE + 0x12)
DECL|macro|AUDIO_SRGR2
mdefine_line|#define AUDIO_SRGR2 (OMAP_MCBSP1_BASE + 0x14)
DECL|macro|AUDIO_SRGR1
mdefine_line|#define AUDIO_SRGR1 (OMAP_MCBSP1_BASE + 0x16)
DECL|macro|AUDIO_MCR2
mdefine_line|#define AUDIO_MCR2  (OMAP_MCBSP1_BASE + 0x18)
DECL|macro|AUDIO_MCR1
mdefine_line|#define AUDIO_MCR1  (OMAP_MCBSP1_BASE + 0x1a)
DECL|macro|AUDIO_RCERA
mdefine_line|#define AUDIO_RCERA (OMAP_MCBSP1_BASE + 0x1c)
DECL|macro|AUDIO_RCERB
mdefine_line|#define AUDIO_RCERB (OMAP_MCBSP1_BASE + 0x1e)
DECL|macro|AUDIO_XCERA
mdefine_line|#define AUDIO_XCERA (OMAP_MCBSP1_BASE + 0x20)
DECL|macro|AUDIO_XCERB
mdefine_line|#define AUDIO_XCERB (OMAP_MCBSP1_BASE + 0x22)
DECL|macro|AUDIO_PCR0
mdefine_line|#define AUDIO_PCR0  (OMAP_MCBSP1_BASE + 0x24)
multiline_comment|/* UART3 Registers Maping through MPU bus */
DECL|macro|OMAP_MPU_UART3_BASE
mdefine_line|#define OMAP_MPU_UART3_BASE     0xFFFB9800      /* UART3 through MPU bus */
DECL|macro|UART3_RHR
mdefine_line|#define UART3_RHR               (OMAP_MPU_UART3_BASE + 0)
DECL|macro|UART3_THR
mdefine_line|#define UART3_THR               (OMAP_MPU_UART3_BASE + 0)
DECL|macro|UART3_DLL
mdefine_line|#define UART3_DLL               (OMAP_MPU_UART3_BASE + 0)
DECL|macro|UART3_IER
mdefine_line|#define UART3_IER               (OMAP_MPU_UART3_BASE + 4)
DECL|macro|UART3_DLH
mdefine_line|#define UART3_DLH               (OMAP_MPU_UART3_BASE + 4)
DECL|macro|UART3_IIR
mdefine_line|#define UART3_IIR               (OMAP_MPU_UART3_BASE + 8)
DECL|macro|UART3_FCR
mdefine_line|#define UART3_FCR               (OMAP_MPU_UART3_BASE + 8)
DECL|macro|UART3_EFR
mdefine_line|#define UART3_EFR               (OMAP_MPU_UART3_BASE + 8)
DECL|macro|UART3_LCR
mdefine_line|#define UART3_LCR               (OMAP_MPU_UART3_BASE + 0x0C)
DECL|macro|UART3_MCR
mdefine_line|#define UART3_MCR               (OMAP_MPU_UART3_BASE + 0x10)
DECL|macro|UART3_XON1_ADDR1
mdefine_line|#define UART3_XON1_ADDR1        (OMAP_MPU_UART3_BASE + 0x10)
DECL|macro|UART3_XON2_ADDR2
mdefine_line|#define UART3_XON2_ADDR2        (OMAP_MPU_UART3_BASE + 0x14)
DECL|macro|UART3_LSR
mdefine_line|#define UART3_LSR               (OMAP_MPU_UART3_BASE + 0x14)
DECL|macro|UART3_TCR
mdefine_line|#define UART3_TCR               (OMAP_MPU_UART3_BASE + 0x18)
DECL|macro|UART3_MSR
mdefine_line|#define UART3_MSR               (OMAP_MPU_UART3_BASE + 0x18)
DECL|macro|UART3_XOFF1
mdefine_line|#define UART3_XOFF1             (OMAP_MPU_UART3_BASE + 0x18)
DECL|macro|UART3_XOFF2
mdefine_line|#define UART3_XOFF2             (OMAP_MPU_UART3_BASE + 0x1C)
DECL|macro|UART3_SPR
mdefine_line|#define UART3_SPR               (OMAP_MPU_UART3_BASE + 0x1C)
DECL|macro|UART3_TLR
mdefine_line|#define UART3_TLR               (OMAP_MPU_UART3_BASE + 0x1C)
DECL|macro|UART3_MDR1
mdefine_line|#define UART3_MDR1              (OMAP_MPU_UART3_BASE + 0x20)
DECL|macro|UART3_MDR2
mdefine_line|#define UART3_MDR2              (OMAP_MPU_UART3_BASE + 0x24)
DECL|macro|UART3_SFLSR
mdefine_line|#define UART3_SFLSR             (OMAP_MPU_UART3_BASE + 0x28)
DECL|macro|UART3_TXFLL
mdefine_line|#define UART3_TXFLL             (OMAP_MPU_UART3_BASE + 0x28)
DECL|macro|UART3_RESUME
mdefine_line|#define UART3_RESUME            (OMAP_MPU_UART3_BASE + 0x2C)
DECL|macro|UART3_TXFLH
mdefine_line|#define UART3_TXFLH             (OMAP_MPU_UART3_BASE + 0x2C)
DECL|macro|UART3_SFREGL
mdefine_line|#define UART3_SFREGL            (OMAP_MPU_UART3_BASE + 0x30)
DECL|macro|UART3_RXFLL
mdefine_line|#define UART3_RXFLL             (OMAP_MPU_UART3_BASE + 0x30)
DECL|macro|UART3_SFREGH
mdefine_line|#define UART3_SFREGH            (OMAP_MPU_UART3_BASE + 0x34)
DECL|macro|UART3_RXFLH
mdefine_line|#define UART3_RXFLH             (OMAP_MPU_UART3_BASE + 0x34)
DECL|macro|UART3_BLR
mdefine_line|#define UART3_BLR               (OMAP_MPU_UART3_BASE + 0x38)
DECL|macro|UART3_ACREG
mdefine_line|#define UART3_ACREG             (OMAP_MPU_UART3_BASE + 0x3C)
DECL|macro|UART3_DIV16
mdefine_line|#define UART3_DIV16             (OMAP_MPU_UART3_BASE + 0x3C)
DECL|macro|UART3_SCR
mdefine_line|#define UART3_SCR               (OMAP_MPU_UART3_BASE + 0x40)
DECL|macro|UART3_SSR
mdefine_line|#define UART3_SSR               (OMAP_MPU_UART3_BASE + 0x44)
DECL|macro|UART3_EBLR
mdefine_line|#define UART3_EBLR              (OMAP_MPU_UART3_BASE + 0x48)
DECL|macro|UART3_OSC_12M_SEL
mdefine_line|#define UART3_OSC_12M_SEL       (OMAP_MPU_UART3_BASE + 0x4C)
DECL|macro|UART3_MVR
mdefine_line|#define UART3_MVR               (OMAP_MPU_UART3_BASE + 0x50)
macro_line|#endif /*  __ASM_ARCH_OMAP_H3_H */
eof
