multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Definitions for the address map in the JUNKIO Asic&n; *&n; * Created with Information from:&n; *&n; * &quot;DEC 3000 300/400/500/600/700/800/900 AXP Models System Programmer&squot;s Manual&quot;&n; *&n; * and the Mach Sources&n; */
macro_line|#ifndef IOASIC_ADDRS_H
DECL|macro|IOASIC_ADDRS_H
mdefine_line|#define IOASIC_ADDRS_H
DECL|macro|CHUNK_SIZE
mdefine_line|#define CHUNK_SIZE 0x00040000
DECL|macro|SYSTEM_ROM
mdefine_line|#define SYSTEM_ROM &t;(0*CHUNK_SIZE)&t;&t;/* ??? */
DECL|macro|IOCTL
mdefine_line|#define IOCTL &t;&t;(1*CHUNK_SIZE)
DECL|macro|ESAR
mdefine_line|#define ESAR &t;&t;(2*CHUNK_SIZE)
DECL|macro|LANCE
mdefine_line|#define LANCE &t;&t;(3*CHUNK_SIZE)
DECL|macro|SCC0
mdefine_line|#define SCC0 &t;&t;(4*CHUNK_SIZE)
DECL|macro|VDAC_HI
mdefine_line|#define VDAC_HI&t;&t;(5*CHUNK_SIZE)&t;&t;/* maxine only */
DECL|macro|SCC1
mdefine_line|#define SCC1 &t;&t;(6*CHUNK_SIZE)
DECL|macro|VDAC_LO
mdefine_line|#define VDAC_LO&t;&t;(7*CHUNK_SIZE)&t;&t;/* maxine only */
DECL|macro|TOY
mdefine_line|#define TOY &t;&t;(8*CHUNK_SIZE)
DECL|macro|ISDN
mdefine_line|#define ISDN &t;&t;(9*CHUNK_SIZE)&t;&t;/* maxine only */
DECL|macro|ERRADDR
mdefine_line|#define ERRADDR&t;&t;(9*CHUNK_SIZE)&t;&t;/* 3maxplus only */
DECL|macro|CHKSYN
mdefine_line|#define CHKSYN &t;&t;(10*CHUNK_SIZE)&t;&t;/* 3maxplus only */
DECL|macro|ACCESS_BUS
mdefine_line|#define ACCESS_BUS&t;(10*CHUNK_SIZE)&t;&t;/* maxine only */
DECL|macro|MCR
mdefine_line|#define MCR &t;&t;(11*CHUNK_SIZE)&t;&t;/* 3maxplus only */
DECL|macro|FLOPPY
mdefine_line|#define FLOPPY &t;&t;(11*CHUNK_SIZE)&t;&t;/* maxine only */
DECL|macro|SCSI
mdefine_line|#define SCSI &t;&t;(12*CHUNK_SIZE)
DECL|macro|FLOPPY_DMA
mdefine_line|#define FLOPPY_DMA &t;(13*CHUNK_SIZE)&t;&t;/* maxine only */
DECL|macro|SCSI_DMA
mdefine_line|#define SCSI_DMA &t;(14*CHUNK_SIZE)
DECL|macro|RESERVED_4
mdefine_line|#define RESERVED_4 &t;(15*CHUNK_SIZE)
multiline_comment|/*&n; * Offsets for IOCTL registers (relative to (system_base + IOCTL))&n; */
DECL|macro|SCSI_DMA_P
mdefine_line|#define SCSI_DMA_P&t;0x00&t;&t;&t;/* SCSI DMA Pointer */
DECL|macro|SCSI_DMA_BP
mdefine_line|#define SCSI_DMA_BP&t;0x10&t;&t;&t;/* SCSI DMA Buffer Pointer */
DECL|macro|LANCE_DMA_P
mdefine_line|#define LANCE_DMA_P&t;0x20&t;&t;&t;/* LANCE DMA Pointer */
DECL|macro|SCC0_T_DMA_P
mdefine_line|#define SCC0_T_DMA_P&t;0x30&t;&t;&t;/* Communication Port 1 Transmit DMA Pointer */
DECL|macro|SCC0_R_DMA_P
mdefine_line|#define SCC0_R_DMA_P&t;0x40&t;&t;&t;/* Communication Port 1 Receive DMA Pointer */
DECL|macro|SCC1_T_DMA_P
mdefine_line|#define SCC1_T_DMA_P&t;0x50&t;&t;&t;/* Communication Port 2 Transmit DMA Pointer */
DECL|macro|SCC1_R_DMA_P
mdefine_line|#define SCC1_R_DMA_P&t;0x60&t;&t;&t;/* Communication Port 2 Receive DMA Pointer */
DECL|macro|FLOPPY_DMA_P
mdefine_line|#define FLOPPY_DMA_P&t;0x70&t;&t;&t;/* Floppy DMA Pointer */
DECL|macro|ISDN_T_DMA_P
mdefine_line|#define ISDN_T_DMA_P&t;0x80&t;&t;&t;/* ISDN Transmit DMA Pointer */
DECL|macro|ISDN_T_DMA_BP
mdefine_line|#define ISDN_T_DMA_BP&t;0x90&t;&t;&t;/* ISDN Transmit DMA Buffer Pointer */
DECL|macro|ISDN_R_DMA_P
mdefine_line|#define ISDN_R_DMA_P&t;0xa0&t;&t;&t;/* ISDN Receive DMA Pointer */
DECL|macro|ISDN_R_DMA_BP
mdefine_line|#define ISDN_R_DMA_BP&t;0xb0&t;&t;&t;/* ISDN Receive DMA Buffer Pointer */
DECL|macro|SSR
mdefine_line|#define SSR&t;&t;0x100&t;&t;&t;/* System Support Register */
DECL|macro|SIR
mdefine_line|#define SIR&t;&t;0x110&t;&t;&t;/* System Interrupt Register */
DECL|macro|SIMR
mdefine_line|#define SIMR&t;&t;0x120&t;&t;&t;/* System Interrupt Mask Register */
DECL|macro|FCTR
mdefine_line|#define FCTR&t;&t;0x1e0&t;&t;&t;/* Free-Running Counter */
multiline_comment|/*&n; * Handle partial word SCSI DMA transfers&n; */
DECL|macro|SCSI_SCR
mdefine_line|#define&t;SCSI_SCR&t;0x1b0
DECL|macro|SCSI_SDR0
mdefine_line|#define&t;SCSI_SDR0&t;0x1c0
DECL|macro|SCSI_SDR1
mdefine_line|#define&t;SCSI_SDR1&t;0x1d0
multiline_comment|/*&n; * DMA defines for the System Support Register&n; */
DECL|macro|LANCE_DMA_EN
mdefine_line|#define LANCE_DMA_EN&t;(1UL&lt;&lt;16)&t;&t;&t;/* LANCE DMA enable */
DECL|macro|SCSI_DMA_EN
mdefine_line|#define SCSI_DMA_EN&t;(1UL&lt;&lt;17)&t;&t;&t;/* SCSI DMA enable */
DECL|macro|SCSI_DMA_DIR
mdefine_line|#define SCSI_DMA_DIR&t;(1UL&lt;&lt;18)&t;&t;&t;/* SCSI DMA direction */
DECL|macro|ISDN_REC_DMA_EN
mdefine_line|#define ISDN_REC_DMA_EN (1UL&lt;&lt;19)&t;&t;&t;/* ISDN receive DMA enable */
DECL|macro|ISDN_TRN_DMA_EN
mdefine_line|#define ISDN_TRN_DMA_EN (1UL&lt;&lt;20)&t;&t;&t;/* ISDN transmit DMA enable */
DECL|macro|FLOPPY_DMA_EN
mdefine_line|#define FLOPPY_DMA_EN&t;(1UL&lt;&lt;21)&t;&t;&t;/* Floppy DMA enable */
DECL|macro|FLOPPY_DMA_DIR
mdefine_line|#define FLOPPY_DMA_DIR&t;(1UL&lt;&lt;22)&t;&t;&t;/* Floppy DMA direction */
DECL|macro|SCC1A_DMA_EN
mdefine_line|#define SCC1A_DMA_EN&t;(1UL&lt;&lt;28)&t;&t;&t;/* SCC1 Channel A DMA enable */
DECL|macro|SCC1B_DMA_EN
mdefine_line|#define SCC1B_DMA_EN&t;(1UL&lt;&lt;29)&t;&t;&t;/* SCC1 Channel B DMA enable */
DECL|macro|SCC0A_DMA_EN
mdefine_line|#define SCC0A_DMA_EN&t;(1UL&lt;&lt;30)&t;&t;&t;/* SCC0 Channel A DMA enable */
DECL|macro|SCC0B_DMA_EN
mdefine_line|#define SCC0B_DMA_EN&t;(1UL&lt;&lt;31)&t;&t;&t;/* Scc0 Channel B DMA enable */
macro_line|#endif
eof
