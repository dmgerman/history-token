macro_line|#ifndef __I386_SGI_PIIX_H
DECL|macro|__I386_SGI_PIIX_H
mdefine_line|#define __I386_SGI_PIIX_H
multiline_comment|/*&n; * PIIX4 as used on SGI Visual Workstations&n; */
DECL|macro|PIIX_PM_START
mdefine_line|#define&t;PIIX_PM_START&t;&t;0x0F80
DECL|macro|SIO_GPIO_START
mdefine_line|#define&t;SIO_GPIO_START&t;&t;0x0FC0
DECL|macro|SIO_PM_START
mdefine_line|#define&t;SIO_PM_START&t;&t;0x0FC8
DECL|macro|PMBASE
mdefine_line|#define&t;PMBASE&t;&t;&t;PIIX_PM_START
DECL|macro|GPIREG0
mdefine_line|#define&t;GPIREG0&t;&t;&t;(PMBASE+0x30)
DECL|macro|GPIREG
mdefine_line|#define&t;GPIREG(x)&t;&t;(GPIREG0+((x)/8))
DECL|macro|GPIBIT
mdefine_line|#define&t;GPIBIT(x)&t;&t;(1 &lt;&lt; ((x)%8))
DECL|macro|PIIX_GPI_BD_ID1
mdefine_line|#define&t;PIIX_GPI_BD_ID1&t;&t;18
DECL|macro|PIIX_GPI_BD_ID2
mdefine_line|#define&t;PIIX_GPI_BD_ID2&t;&t;19
DECL|macro|PIIX_GPI_BD_ID3
mdefine_line|#define&t;PIIX_GPI_BD_ID3&t;&t;20
DECL|macro|PIIX_GPI_BD_ID4
mdefine_line|#define&t;PIIX_GPI_BD_ID4&t;&t;21
DECL|macro|PIIX_GPI_BD_REG
mdefine_line|#define&t;PIIX_GPI_BD_REG&t;&t;GPIREG(PIIX_GPI_BD_ID1)
DECL|macro|PIIX_GPI_BD_MASK
mdefine_line|#define&t;PIIX_GPI_BD_MASK&t;(GPIBIT(PIIX_GPI_BD_ID1) | &bslash;&n;&t;&t;&t;&t;GPIBIT(PIIX_GPI_BD_ID2) | &bslash;&n;&t;&t;&t;&t;GPIBIT(PIIX_GPI_BD_ID3) | &bslash;&n;&t;&t;&t;&t;GPIBIT(PIIX_GPI_BD_ID4) )
DECL|macro|PIIX_GPI_BD_SHIFT
mdefine_line|#define&t;PIIX_GPI_BD_SHIFT&t;(PIIX_GPI_BD_ID1 % 8)
DECL|macro|SIO_INDEX
mdefine_line|#define&t;SIO_INDEX&t;&t;0x2e
DECL|macro|SIO_DATA
mdefine_line|#define&t;SIO_DATA&t;&t;0x2f
DECL|macro|SIO_DEV_SEL
mdefine_line|#define&t;SIO_DEV_SEL&t;&t;0x7
DECL|macro|SIO_DEV_ENB
mdefine_line|#define&t;SIO_DEV_ENB&t;&t;0x30
DECL|macro|SIO_DEV_MSB
mdefine_line|#define&t;SIO_DEV_MSB&t;&t;0x60
DECL|macro|SIO_DEV_LSB
mdefine_line|#define&t;SIO_DEV_LSB&t;&t;0x61
DECL|macro|SIO_GP_DEV
mdefine_line|#define&t;SIO_GP_DEV&t;&t;0x7
DECL|macro|SIO_GP_BASE
mdefine_line|#define&t;SIO_GP_BASE&t;&t;SIO_GPIO_START
DECL|macro|SIO_GP_MSB
mdefine_line|#define&t;SIO_GP_MSB&t;&t;(SIO_GP_BASE&gt;&gt;8)
DECL|macro|SIO_GP_LSB
mdefine_line|#define&t;SIO_GP_LSB&t;&t;(SIO_GP_BASE&amp;0xff)
DECL|macro|SIO_GP_DATA1
mdefine_line|#define&t;SIO_GP_DATA1&t;&t;(SIO_GP_BASE+0)
DECL|macro|SIO_PM_DEV
mdefine_line|#define&t;SIO_PM_DEV&t;&t;0x8
DECL|macro|SIO_PM_BASE
mdefine_line|#define&t;SIO_PM_BASE&t;&t;SIO_PM_START
DECL|macro|SIO_PM_MSB
mdefine_line|#define&t;SIO_PM_MSB&t;&t;(SIO_PM_BASE&gt;&gt;8)
DECL|macro|SIO_PM_LSB
mdefine_line|#define&t;SIO_PM_LSB&t;&t;(SIO_PM_BASE&amp;0xff)
DECL|macro|SIO_PM_INDEX
mdefine_line|#define&t;SIO_PM_INDEX&t;&t;(SIO_PM_BASE+0)
DECL|macro|SIO_PM_DATA
mdefine_line|#define&t;SIO_PM_DATA&t;&t;(SIO_PM_BASE+1)
DECL|macro|SIO_PM_FER2
mdefine_line|#define&t;SIO_PM_FER2&t;&t;0x1
DECL|macro|SIO_PM_GP_EN
mdefine_line|#define&t;SIO_PM_GP_EN&t;&t;0x80
multiline_comment|/*&n; * This is the dev/reg where generating a config cycle will&n; * result in a PCI special cycle.&n; */
DECL|macro|SPECIAL_DEV
mdefine_line|#define SPECIAL_DEV&t;&t;0xff
DECL|macro|SPECIAL_REG
mdefine_line|#define SPECIAL_REG&t;&t;0x00
multiline_comment|/*&n; * PIIX4 needs to see a special cycle with the following data&n; * to be convinced the processor has gone into the stop grant&n; * state.  PIIX4 insists on seeing this before it will power&n; * down a system.&n; */
DECL|macro|PIIX_SPECIAL_STOP
mdefine_line|#define PIIX_SPECIAL_STOP&t;&t;0x00120002
DECL|macro|PIIX4_RESET_PORT
mdefine_line|#define PIIX4_RESET_PORT&t;0xcf9
DECL|macro|PIIX4_RESET_VAL
mdefine_line|#define PIIX4_RESET_VAL&t;&t;0x6
DECL|macro|PMSTS_PORT
mdefine_line|#define PMSTS_PORT&t;&t;0xf80&t;
singleline_comment|// 2 bytes&t;PM Status
DECL|macro|PMEN_PORT
mdefine_line|#define PMEN_PORT&t;&t;0xf82&t;
singleline_comment|// 2 bytes&t;PM Enable
DECL|macro|PMCNTRL_PORT
mdefine_line|#define&t;PMCNTRL_PORT&t;&t;0xf84&t;
singleline_comment|// 2 bytes&t;PM Control
DECL|macro|PM_SUSPEND_ENABLE
mdefine_line|#define PM_SUSPEND_ENABLE&t;0x2000&t;
singleline_comment|// start sequence to suspend state
multiline_comment|/*&n; * PMSTS and PMEN I/O bit definitions.&n; * (Bits are the same in both registers)&n; */
DECL|macro|PM_STS_RSM
mdefine_line|#define PM_STS_RSM&t;&t;(1&lt;&lt;15)&t;
singleline_comment|// Resume Status
DECL|macro|PM_STS_PWRBTNOR
mdefine_line|#define PM_STS_PWRBTNOR&t;&t;(1&lt;&lt;11)&t;
singleline_comment|// Power Button Override
DECL|macro|PM_STS_RTC
mdefine_line|#define PM_STS_RTC&t;&t;(1&lt;&lt;10)&t;
singleline_comment|// RTC status
DECL|macro|PM_STS_PWRBTN
mdefine_line|#define PM_STS_PWRBTN&t;&t;(1&lt;&lt;8)&t;
singleline_comment|// Power Button Pressed?
DECL|macro|PM_STS_GBL
mdefine_line|#define PM_STS_GBL&t;&t;(1&lt;&lt;5)&t;
singleline_comment|// Global Status
DECL|macro|PM_STS_BM
mdefine_line|#define PM_STS_BM&t;&t;(1&lt;&lt;4)&t;
singleline_comment|// Bus Master Status
DECL|macro|PM_STS_TMROF
mdefine_line|#define PM_STS_TMROF&t;&t;(1&lt;&lt;0)&t;
singleline_comment|// Timer Overflow Status.
multiline_comment|/*&n; * Stop clock GPI register&n; */
DECL|macro|PIIX_GPIREG0
mdefine_line|#define PIIX_GPIREG0&t;&t;&t;(0xf80 + 0x30)
multiline_comment|/*&n; * Stop clock GPI bit in GPIREG0&n; */
DECL|macro|PIIX_GPI_STPCLK
mdefine_line|#define&t;PIIX_GPI_STPCLK&t;&t;0x4&t;
singleline_comment|// STPCLK signal routed back in
macro_line|#endif
eof
