multiline_comment|/*&n; * Orion/Galileo specific header file.&n; *  -- Cort &lt;cort@fsmlabs.com&gt;&n; */
macro_line|#ifndef __LINUX_MIPS_ORION_H
DECL|macro|__LINUX_MIPS_ORION_H
mdefine_line|#define __LINUX_MIPS_ORION_H
multiline_comment|/* base address for the GT-64120 internal registers */
DECL|macro|GT64120_BASE
mdefine_line|#define GT64120_BASE (0x14000000)
multiline_comment|/* GT64120 and PCI_0 interrupt cause register */
DECL|macro|GT64120_CAUSE_LOW
mdefine_line|#define GT64120_CAUSE_LOW *(unsigned long *)(GT64120_BASE + 0xc18)
DECL|macro|GT64120_CAUSE_HIGH
mdefine_line|#define GT64120_CAUSE_HIGH *(unsigned long *)(GT64120_BASE + 0xc1c)
macro_line|#endif /* __LINUX_MIPS_ORION_H */
eof
