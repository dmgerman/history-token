multiline_comment|/* &n; * abyss.h: Header for the abyss tms380tr module&n; *&n; * Authors:&n; * - Adam Fritzler &lt;mid@auk.cx&gt;&n; */
macro_line|#ifndef __LINUX_MADGETR_H
DECL|macro|__LINUX_MADGETR_H
mdefine_line|#define __LINUX_MADGETR_H
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * For Madge Smart 16/4 PCI Mk2.  Since we increment the base address&n; * to get everything correct for the TMS SIF, we do these as negatives&n; * as they fall below the SIF in addressing.&n; */
DECL|macro|PCIBM2_INT_STATUS_REG
mdefine_line|#define PCIBM2_INT_STATUS_REG          ((short)-15)/* 0x01 */
DECL|macro|PCIBM2_INT_CONTROL_REG
mdefine_line|#define PCIBM2_INT_CONTROL_REG         ((short)-14)/* 0x02 */
DECL|macro|PCIBM2_RESET_REG
mdefine_line|#define PCIBM2_RESET_REG               ((short)-12)/* 0x04 */
DECL|macro|PCIBM2_SEEPROM_REG
mdefine_line|#define PCIBM2_SEEPROM_REG             ((short)-9) /* 0x07 */
DECL|macro|PCIBM2_INT_CONTROL_REG_SINTEN
mdefine_line|#define PCIBM2_INT_CONTROL_REG_SINTEN           0x02
DECL|macro|PCIBM2_INT_CONTROL_REG_PCI_ERR_ENABLE
mdefine_line|#define PCIBM2_INT_CONTROL_REG_PCI_ERR_ENABLE   0x80
DECL|macro|PCIBM2_INT_STATUS_REG_PCI_ERR
mdefine_line|#define PCIBM2_INT_STATUS_REG_PCI_ERR           0x80
DECL|macro|PCIBM2_RESET_REG_CHIP_NRES
mdefine_line|#define PCIBM2_RESET_REG_CHIP_NRES              0x01
DECL|macro|PCIBM2_RESET_REG_FIFO_NRES
mdefine_line|#define PCIBM2_RESET_REG_FIFO_NRES              0x02
DECL|macro|PCIBM2_RESET_REG_SIF_NRES
mdefine_line|#define PCIBM2_RESET_REG_SIF_NRES               0x04
DECL|macro|PCIBM2_FIFO_THRESHOLD
mdefine_line|#define PCIBM2_FIFO_THRESHOLD   0x21
DECL|macro|PCIBM2_BURST_LENGTH
mdefine_line|#define PCIBM2_BURST_LENGTH     0x22
multiline_comment|/*&n; * Bits in PCIBM2_SEEPROM_REG.&n; */
DECL|macro|AT24_ENABLE
mdefine_line|#define AT24_ENABLE             0x04
DECL|macro|AT24_DATA
mdefine_line|#define AT24_DATA               0x02
DECL|macro|AT24_CLOCK
mdefine_line|#define AT24_CLOCK              0x01
multiline_comment|/*&n; * AT24 Commands.&n; */
DECL|macro|AT24_WRITE
mdefine_line|#define AT24_WRITE              0xA0
DECL|macro|AT24_READ
mdefine_line|#define AT24_READ               0xA1
multiline_comment|/*&n; * Addresses in AT24 SEEPROM.&n; */
DECL|macro|PCIBM2_SEEPROM_BIA
mdefine_line|#define PCIBM2_SEEPROM_BIA          0x12
DECL|macro|PCIBM2_SEEPROM_RING_SPEED
mdefine_line|#define PCIBM2_SEEPROM_RING_SPEED   0x18
DECL|macro|PCIBM2_SEEPROM_RAM_SIZE
mdefine_line|#define PCIBM2_SEEPROM_RAM_SIZE     0x1A
DECL|macro|PCIBM2_SEEPROM_HWF1
mdefine_line|#define PCIBM2_SEEPROM_HWF1         0x1C
DECL|macro|PCIBM2_SEEPROM_HWF2
mdefine_line|#define PCIBM2_SEEPROM_HWF2         0x1E
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __LINUX_MADGETR_H */
eof
