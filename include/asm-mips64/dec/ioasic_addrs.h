multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Definitions for the address map in the JUNKIO Asic&n; *&n; * Created with Information from:&n; *&n; * &quot;DEC 3000 300/400/500/600/700/800/900 AXP Models System Programmer&squot;s Manual&quot;&n; *&n; * and the Mach Sources&n; *&n; * Copyright (C) 199x  the Anonymous&n; * Copyright (C) 2002, 2003  Maciej W. Rozycki&n; */
macro_line|#ifndef __ASM_MIPS_DEC_IOASIC_ADDRS_H
DECL|macro|__ASM_MIPS_DEC_IOASIC_ADDRS_H
mdefine_line|#define __ASM_MIPS_DEC_IOASIC_ADDRS_H
DECL|macro|IOASIC_SLOT_SIZE
mdefine_line|#define IOASIC_SLOT_SIZE 0x00040000
multiline_comment|/*&n; * Address ranges decoded by the I/O ASIC for onboard devices.&n; */
DECL|macro|IOASIC_SYS_ROM
mdefine_line|#define IOASIC_SYS_ROM&t;(0*IOASIC_SLOT_SIZE)&t;/* system board ROM */
DECL|macro|IOASIC_IOCTL
mdefine_line|#define IOASIC_IOCTL&t;(1*IOASIC_SLOT_SIZE)&t;/* I/O ASIC */
DECL|macro|IOASIC_ESAR
mdefine_line|#define IOASIC_ESAR &t;(2*IOASIC_SLOT_SIZE)&t;/* LANCE MAC address chip */
DECL|macro|IOASIC_LANCE
mdefine_line|#define IOASIC_LANCE &t;(3*IOASIC_SLOT_SIZE)&t;/* LANCE Ethernet */
DECL|macro|IOASIC_SCC0
mdefine_line|#define IOASIC_SCC0 &t;(4*IOASIC_SLOT_SIZE)&t;/* SCC #0 */
DECL|macro|IOASIC_VDAC_HI
mdefine_line|#define IOASIC_VDAC_HI&t;(5*IOASIC_SLOT_SIZE)&t;/* VDAC (maxine) */
DECL|macro|IOASIC_SCC1
mdefine_line|#define IOASIC_SCC1 &t;(6*IOASIC_SLOT_SIZE)&t;/* SCC #1 (3min, 3max+) */
DECL|macro|IOASIC_VDAC_LO
mdefine_line|#define IOASIC_VDAC_LO&t;(7*IOASIC_SLOT_SIZE)&t;/* VDAC (maxine) */
DECL|macro|IOASIC_TOY
mdefine_line|#define IOASIC_TOY &t;(8*IOASIC_SLOT_SIZE)&t;/* RTC */
DECL|macro|IOASIC_ISDN
mdefine_line|#define IOASIC_ISDN &t;(9*IOASIC_SLOT_SIZE)&t;/* ISDN (maxine) */
DECL|macro|IOASIC_ERRADDR
mdefine_line|#define IOASIC_ERRADDR&t;(9*IOASIC_SLOT_SIZE)&t;/* bus error address (3max+) */
DECL|macro|IOASIC_CHKSYN
mdefine_line|#define IOASIC_CHKSYN &t;(10*IOASIC_SLOT_SIZE)&t;/* ECC syndrome (3max+) */
DECL|macro|IOASIC_ACC_BUS
mdefine_line|#define IOASIC_ACC_BUS&t;(10*IOASIC_SLOT_SIZE)&t;/* ACCESS.bus (maxine) */
DECL|macro|IOASIC_MCR
mdefine_line|#define IOASIC_MCR &t;(11*IOASIC_SLOT_SIZE)&t;/* memory control (3max+) */
DECL|macro|IOASIC_FLOPPY
mdefine_line|#define IOASIC_FLOPPY &t;(11*IOASIC_SLOT_SIZE)&t;/* FDC (maxine) */
DECL|macro|IOASIC_SCSI
mdefine_line|#define IOASIC_SCSI &t;(12*IOASIC_SLOT_SIZE)&t;/* ASC SCSI */
DECL|macro|IOASIC_FDC_DMA
mdefine_line|#define IOASIC_FDC_DMA&t;(13*IOASIC_SLOT_SIZE)&t;/* FDC DMA (maxine) */
DECL|macro|IOASIC_SCSI_DMA
mdefine_line|#define IOASIC_SCSI_DMA&t;(14*IOASIC_SLOT_SIZE)&t;/* ??? */
DECL|macro|IOASIC_RES_15
mdefine_line|#define IOASIC_RES_15&t;(15*IOASIC_SLOT_SIZE)&t;/* unused? */
multiline_comment|/*&n; * Offsets for I/O ASIC registers (relative to (system_base + IOASIC_IOCTL)).&n; */
multiline_comment|/* all systems */
DECL|macro|IO_REG_SCSI_DMA_P
mdefine_line|#define IO_REG_SCSI_DMA_P&t;0x00&t;/* SCSI DMA Pointer */
DECL|macro|IO_REG_SCSI_DMA_BP
mdefine_line|#define IO_REG_SCSI_DMA_BP&t;0x10&t;/* SCSI DMA Buffer Pointer */
DECL|macro|IO_REG_LANCE_DMA_P
mdefine_line|#define IO_REG_LANCE_DMA_P&t;0x20&t;/* LANCE DMA Pointer */
DECL|macro|IO_REG_SCC0A_T_DMA_P
mdefine_line|#define IO_REG_SCC0A_T_DMA_P&t;0x30&t;/* SCC0A Transmit DMA Pointer */
DECL|macro|IO_REG_SCC0A_R_DMA_P
mdefine_line|#define IO_REG_SCC0A_R_DMA_P&t;0x40&t;/* SCC0A Receive DMA Pointer */
multiline_comment|/* except Maxine */
DECL|macro|IO_REG_SCC1A_T_DMA_P
mdefine_line|#define IO_REG_SCC1A_T_DMA_P&t;0x50&t;/* SCC1A Transmit DMA Pointer */
DECL|macro|IO_REG_SCC1A_R_DMA_P
mdefine_line|#define IO_REG_SCC1A_R_DMA_P&t;0x60&t;/* SCC1A Receive DMA Pointer */
multiline_comment|/* Maxine */
DECL|macro|IO_REG_AB_T_DMA_P
mdefine_line|#define IO_REG_AB_T_DMA_P&t;0x50&t;/* ACCESS.bus Transmit DMA Pointer */
DECL|macro|IO_REG_AB_R_DMA_P
mdefine_line|#define IO_REG_AB_R_DMA_P&t;0x60&t;/* ACCESS.bus Receive DMA Pointer */
DECL|macro|IO_REG_FLOPPY_DMA_P
mdefine_line|#define IO_REG_FLOPPY_DMA_P&t;0x70&t;/* Floppy DMA Pointer */
DECL|macro|IO_REG_ISDN_T_DMA_P
mdefine_line|#define IO_REG_ISDN_T_DMA_P&t;0x80&t;/* ISDN Transmit DMA Pointer */
DECL|macro|IO_REG_ISDN_T_DMA_BP
mdefine_line|#define IO_REG_ISDN_T_DMA_BP&t;0x90&t;/* ISDN Transmit DMA Buffer Pointer */
DECL|macro|IO_REG_ISDN_R_DMA_P
mdefine_line|#define IO_REG_ISDN_R_DMA_P&t;0xa0&t;/* ISDN Receive DMA Pointer */
DECL|macro|IO_REG_ISDN_R_DMA_BP
mdefine_line|#define IO_REG_ISDN_R_DMA_BP&t;0xb0&t;/* ISDN Receive DMA Buffer Pointer */
multiline_comment|/* all systems */
DECL|macro|IO_REG_DATA_0
mdefine_line|#define IO_REG_DATA_0&t;&t;0xc0&t;/* System Data Buffer 0 */
DECL|macro|IO_REG_DATA_1
mdefine_line|#define IO_REG_DATA_1&t;&t;0xd0&t;/* System Data Buffer 1 */
DECL|macro|IO_REG_DATA_2
mdefine_line|#define IO_REG_DATA_2&t;&t;0xe0&t;/* System Data Buffer 2 */
DECL|macro|IO_REG_DATA_3
mdefine_line|#define IO_REG_DATA_3&t;&t;0xf0&t;/* System Data Buffer 3 */
multiline_comment|/* all systems */
DECL|macro|IO_REG_SSR
mdefine_line|#define IO_REG_SSR&t;&t;0x100&t;/* System Support Register */
DECL|macro|IO_REG_SIR
mdefine_line|#define IO_REG_SIR&t;&t;0x110&t;/* System Interrupt Register */
DECL|macro|IO_REG_SIMR
mdefine_line|#define IO_REG_SIMR&t;&t;0x120&t;/* System Interrupt Mask Reg. */
DECL|macro|IO_REG_SAR
mdefine_line|#define IO_REG_SAR&t;&t;0x130&t;/* System Address Register */
multiline_comment|/* Maxine */
DECL|macro|IO_REG_ISDN_T_DATA
mdefine_line|#define IO_REG_ISDN_T_DATA&t;0x140&t;/* ISDN Xmit Data Register */
DECL|macro|IO_REG_ISDN_R_DATA
mdefine_line|#define IO_REG_ISDN_R_DATA&t;0x150&t;/* ISDN Receive Data Register */
multiline_comment|/* all systems */
DECL|macro|IO_REG_LANCE_SLOT
mdefine_line|#define IO_REG_LANCE_SLOT&t;0x160&t;/* LANCE I/O Slot Register */
DECL|macro|IO_REG_SCSI_SLOT
mdefine_line|#define IO_REG_SCSI_SLOT&t;0x170&t;/* SCSI Slot Register */
DECL|macro|IO_REG_SCC0A_SLOT
mdefine_line|#define IO_REG_SCC0A_SLOT&t;0x180&t;/* SCC0A DMA Slot Register */
multiline_comment|/* except Maxine */
DECL|macro|IO_REG_SCC1A_SLOT
mdefine_line|#define IO_REG_SCC1A_SLOT&t;0x190&t;/* SCC1A DMA Slot Register */
multiline_comment|/* Maxine */
DECL|macro|IO_REG_AB_SLOT
mdefine_line|#define IO_REG_AB_SLOT&t;&t;0x190&t;/* ACCESS.bus DMA Slot Register */
DECL|macro|IO_REG_FLOPPY_SLOT
mdefine_line|#define IO_REG_FLOPPY_SLOT&t;0x1a0&t;/* Floppy Slot Register */
multiline_comment|/* all systems */
DECL|macro|IO_REG_SCSI_SCR
mdefine_line|#define IO_REG_SCSI_SCR&t;&t;0x1b0&t;/* SCSI Partial-Word DMA Control */
DECL|macro|IO_REG_SCSI_SDR0
mdefine_line|#define IO_REG_SCSI_SDR0&t;0x1c0&t;/* SCSI DMA Partial Word 0 */
DECL|macro|IO_REG_SCSI_SDR1
mdefine_line|#define IO_REG_SCSI_SDR1&t;0x1d0&t;/* SCSI DMA Partial Word 1 */
DECL|macro|IO_REG_FCTR
mdefine_line|#define IO_REG_FCTR&t;&t;0x1e0&t;/* Free-Running Counter */
DECL|macro|IO_REG_RES_31
mdefine_line|#define IO_REG_RES_31&t;&t;0x1f0&t;/* unused */
multiline_comment|/*&n; * The upper 16 bits of the System Support Register are a part of the&n; * I/O ASIC&squot;s internal DMA engine and thus are common to all I/O ASIC&n; * machines.  The exception is the Maxine, which makes use of the&n; * FLOPPY and ISDN bits (otherwise unused) and has a different SCC&n; * wiring.&n; */
multiline_comment|/* all systems */
DECL|macro|IO_SSR_SCC0A_TX_DMA_EN
mdefine_line|#define IO_SSR_SCC0A_TX_DMA_EN&t;(1&lt;&lt;31)&t;&t;/* SCC0A transmit DMA enable */
DECL|macro|IO_SSR_SCC0A_RX_DMA_EN
mdefine_line|#define IO_SSR_SCC0A_RX_DMA_EN&t;(1&lt;&lt;30)&t;&t;/* SCC0A receive DMA enable */
DECL|macro|IO_SSR_RES_27
mdefine_line|#define IO_SSR_RES_27&t;&t;(1&lt;&lt;27)&t;&t;/* unused */
DECL|macro|IO_SSR_RES_26
mdefine_line|#define IO_SSR_RES_26&t;&t;(1&lt;&lt;26)&t;&t;/* unused */
DECL|macro|IO_SSR_RES_25
mdefine_line|#define IO_SSR_RES_25&t;&t;(1&lt;&lt;25)&t;&t;/* unused */
DECL|macro|IO_SSR_RES_24
mdefine_line|#define IO_SSR_RES_24&t;&t;(1&lt;&lt;24)&t;&t;/* unused */
DECL|macro|IO_SSR_RES_23
mdefine_line|#define IO_SSR_RES_23&t;&t;(1&lt;&lt;23)&t;&t;/* unused */
DECL|macro|IO_SSR_SCSI_DMA_DIR
mdefine_line|#define IO_SSR_SCSI_DMA_DIR&t;(1&lt;&lt;18)&t;&t;/* SCSI DMA direction */
DECL|macro|IO_SSR_SCSI_DMA_EN
mdefine_line|#define IO_SSR_SCSI_DMA_EN&t;(1&lt;&lt;17)&t;&t;/* SCSI DMA enable */
DECL|macro|IO_SSR_LANCE_DMA_EN
mdefine_line|#define IO_SSR_LANCE_DMA_EN&t;(1&lt;&lt;16)&t;&t;/* LANCE DMA enable */
multiline_comment|/* except Maxine */
DECL|macro|IO_SSR_SCC1A_TX_DMA_EN
mdefine_line|#define IO_SSR_SCC1A_TX_DMA_EN&t;(1&lt;&lt;29)&t;&t;/* SCC1A transmit DMA enable */
DECL|macro|IO_SSR_SCC1A_RX_DMA_EN
mdefine_line|#define IO_SSR_SCC1A_RX_DMA_EN&t;(1&lt;&lt;28)&t;&t;/* SCC1A receive DMA enable */
DECL|macro|IO_SSR_RES_22
mdefine_line|#define IO_SSR_RES_22&t;&t;(1&lt;&lt;22)&t;&t;/* unused */
DECL|macro|IO_SSR_RES_21
mdefine_line|#define IO_SSR_RES_21&t;&t;(1&lt;&lt;21)&t;&t;/* unused */
DECL|macro|IO_SSR_RES_20
mdefine_line|#define IO_SSR_RES_20&t;&t;(1&lt;&lt;20)&t;&t;/* unused */
DECL|macro|IO_SSR_RES_19
mdefine_line|#define IO_SSR_RES_19&t;&t;(1&lt;&lt;19)&t;&t;/* unused */
multiline_comment|/* Maxine */
DECL|macro|IO_SSR_AB_TX_DMA_EN
mdefine_line|#define IO_SSR_AB_TX_DMA_EN&t;(1&lt;&lt;29)&t;&t;/* ACCESS.bus xmit DMA enable */
DECL|macro|IO_SSR_AB_RX_DMA_EN
mdefine_line|#define IO_SSR_AB_RX_DMA_EN&t;(1&lt;&lt;28)&t;&t;/* ACCESS.bus recv DMA enable */
DECL|macro|IO_SSR_FLOPPY_DMA_DIR
mdefine_line|#define IO_SSR_FLOPPY_DMA_DIR&t;(1&lt;&lt;22)&t;&t;/* Floppy DMA direction */
DECL|macro|IO_SSR_FLOPPY_DMA_EN
mdefine_line|#define IO_SSR_FLOPPY_DMA_EN&t;(1&lt;&lt;21)&t;&t;/* Floppy DMA enable */
DECL|macro|IO_SSR_ISDN_TX_DMA_EN
mdefine_line|#define IO_SSR_ISDN_TX_DMA_EN&t;(1&lt;&lt;20)&t;&t;/* ISDN transmit DMA enable */
DECL|macro|IO_SSR_ISDN_RX_DMA_EN
mdefine_line|#define IO_SSR_ISDN_RX_DMA_EN&t;(1&lt;&lt;19)&t;&t;/* ISDN receive DMA enable */
multiline_comment|/*&n; * The lower 16 bits are system-specific.  Bits 15,11:8 are common and&n; * defined here.  The rest is defined in system-specific headers.&n; */
DECL|macro|KN0X_IO_SSR_DIAGDN
mdefine_line|#define KN0X_IO_SSR_DIAGDN&t;(1&lt;&lt;15)&t;&t;/* diagnostic jumper */
DECL|macro|KN0X_IO_SSR_SCC_RST
mdefine_line|#define KN0X_IO_SSR_SCC_RST&t;(1&lt;&lt;11)&t;&t;/* ~SCC0,1 (Z85C30) reset */
DECL|macro|KN0X_IO_SSR_RTC_RST
mdefine_line|#define KN0X_IO_SSR_RTC_RST&t;(1&lt;&lt;10)&t;&t;/* ~RTC (DS1287) reset */
DECL|macro|KN0X_IO_SSR_ASC_RST
mdefine_line|#define KN0X_IO_SSR_ASC_RST&t;(1&lt;&lt;9)&t;&t;/* ~ASC (NCR53C94) reset */
DECL|macro|KN0X_IO_SSR_LANCE_RST
mdefine_line|#define KN0X_IO_SSR_LANCE_RST&t;(1&lt;&lt;8)&t;&t;/* ~LANCE (Am7990) reset */
macro_line|#endif /* __ASM_MIPS_DEC_IOASIC_ADDRS_H */
eof
