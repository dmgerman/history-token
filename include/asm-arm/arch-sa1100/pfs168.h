multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/pfs168.h&n; *&n; * Created 2000/06/05 by Nicolas Pitre &lt;nico@cam.org&gt;&n; *&n; * This file contains the hardware specific definitions for PFS-168&n; *&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
macro_line|#error &quot;include &lt;asm/hardware.h&gt; instead&quot;
macro_line|#endif
multiline_comment|/* GPIOs for which the generic definition doesn&squot;t say much */
DECL|macro|GPIO_RADIO_IRQ
mdefine_line|#define GPIO_RADIO_IRQ&t;&t;GPIO_GPIO (14)&t;/* Radio interrupt request  */
DECL|macro|GPIO_L3_I2C_SDA
mdefine_line|#define GPIO_L3_I2C_SDA&t;&t;GPIO_GPIO (15)&t;/* L3 and SMB control ports */
DECL|macro|GPIO_PS_MODE_SYNC
mdefine_line|#define GPIO_PS_MODE_SYNC&t;GPIO_GPIO (16)&t;/* Power supply mode/sync   */
DECL|macro|GPIO_L3_MODE
mdefine_line|#define GPIO_L3_MODE&t;&t;GPIO_GPIO (17)&t;/* L3 mode signal with LED  */
DECL|macro|GPIO_L3_I2C_SCL
mdefine_line|#define GPIO_L3_I2C_SCL&t;&t;GPIO_GPIO (18)&t;/* L3 and I2C control ports */
DECL|macro|GPIO_STEREO_64FS_CLK
mdefine_line|#define GPIO_STEREO_64FS_CLK&t;GPIO_GPIO (19)&t;/* SSP UDA1341 clock input  */
DECL|macro|GPIO_CF_IRQ
mdefine_line|#define GPIO_CF_IRQ&t;&t;GPIO_GPIO (21)&t;/* CF IRQ   */
DECL|macro|GPIO_MBGNT
mdefine_line|#define GPIO_MBGNT&t;&t;GPIO_GPIO (21)&t;/* 1111 MBGNT */
DECL|macro|GPIO_CF_CD
mdefine_line|#define GPIO_CF_CD&t;&t;GPIO_GPIO (22)&t;/* CF CD */
DECL|macro|GPIO_MBREQ
mdefine_line|#define GPIO_MBREQ&t;&t;GPIO_GPIO (22)&t;/* 1111 MBREQ */
DECL|macro|GPIO_UCB1300_IRQ
mdefine_line|#define GPIO_UCB1300_IRQ&t;GPIO_GPIO (23)&t;/* UCB GPIO and touchscreen */
DECL|macro|GPIO_CF_BVD2
mdefine_line|#define GPIO_CF_BVD2&t;&t;GPIO_GPIO (24)&t;/* CF BVD */
DECL|macro|GPIO_GFX_IRQ
mdefine_line|#define GPIO_GFX_IRQ&t;&t;GPIO_GPIO (24)&t;/* Graphics IRQ */
DECL|macro|GPIO_CF_BVD1
mdefine_line|#define GPIO_CF_BVD1&t;&t;GPIO_GPIO (25)&t;/* CF BVD */
DECL|macro|GPIO_NEP_IRQ
mdefine_line|#define GPIO_NEP_IRQ&t;&t;GPIO_GPIO (25)&t;/* Neponset IRQ */
DECL|macro|GPIO_BATT_LOW
mdefine_line|#define GPIO_BATT_LOW&t;&t;GPIO_GPIO (26)&t;/* Low battery */
DECL|macro|GPIO_RCLK
mdefine_line|#define GPIO_RCLK&t;&t;GPIO_GPIO (26)&t;/* CCLK/2  */
DECL|macro|IRQ_GPIO_CF_IRQ
mdefine_line|#define IRQ_GPIO_CF_IRQ&t;&t;IRQ_GPIO21
DECL|macro|IRQ_GPIO_CF_CD
mdefine_line|#define IRQ_GPIO_CF_CD&t;&t;IRQ_GPIO22
DECL|macro|IRQ_GPIO_MBREQ
mdefine_line|#define IRQ_GPIO_MBREQ&t;&t;IRQ_GPIO22
DECL|macro|IRQ_GPIO_UCB1300_IRQ
mdefine_line|#define IRQ_GPIO_UCB1300_IRQ&t;IRQ_GPIO23
DECL|macro|IRQ_GPIO_CF_BVD2
mdefine_line|#define IRQ_GPIO_CF_BVD2&t;IRQ_GPIO24
DECL|macro|IRQ_GPIO_CF_BVD1
mdefine_line|#define IRQ_GPIO_CF_BVD1&t;IRQ_GPIO25
DECL|macro|IRQ_GPIO_NEP_IRQ
mdefine_line|#define IRQ_GPIO_NEP_IRQ&t;IRQ_GPIO25
multiline_comment|/*&n; * PFS-168 definitions:&n; */
DECL|macro|SA1111_BASE
mdefine_line|#define SA1111_BASE             (0x40000000)
macro_line|#ifndef __ASSEMBLY__
DECL|macro|PFS168_COM5_VBASE
mdefine_line|#define PFS168_COM5_VBASE&t;&t;(*((volatile unsigned char *)(0xf0000000UL)))
DECL|macro|PFS168_COM6_VBASE
mdefine_line|#define PFS168_COM6_VBASE&t;&t;(*((volatile unsigned char *)(0xf0001000UL)))
DECL|macro|PFS168_SYSC1RTS
mdefine_line|#define PFS168_SYSC1RTS&t;&t;&t;(*((volatile unsigned char *)(0xf0002000UL)))
DECL|macro|PFS168_SYSLED
mdefine_line|#define PFS168_SYSLED&t;&t;&t;(*((volatile unsigned char *)(0xf0003000UL)))
DECL|macro|PFS168_SYSDTMF
mdefine_line|#define PFS168_SYSDTMF&t;&t;&t;(*((volatile unsigned char *)(0xf0004000UL)))
DECL|macro|PFS168_SYSLCDDE
mdefine_line|#define PFS168_SYSLCDDE&t;&t;&t;(*((volatile unsigned char *)(0xf0005000UL)))
DECL|macro|PFS168_SYSC1DSR
mdefine_line|#define PFS168_SYSC1DSR&t;&t;&t;(*((volatile unsigned char *)(0xf0006000UL)))
DECL|macro|PFS168_SYSC3TEN
mdefine_line|#define PFS168_SYSC3TEN&t;&t;&t;(*((volatile unsigned char *)(0xf0007000UL)))
DECL|macro|PFS168_SYSCTLA
mdefine_line|#define PFS168_SYSCTLA&t;&t;&t;(*((volatile unsigned char *)(0xf0008000UL)))
DECL|macro|PFS168_SYSCTLB
mdefine_line|#define PFS168_SYSCTLB&t;&t;&t;(*((volatile unsigned char *)(0xf0009000UL)))
DECL|macro|PFS168_ETH_VBASE
mdefine_line|#define PFS168_ETH_VBASE&t;&t;(*((volatile unsigned char *)(0xf000a000UL)))
macro_line|#endif
DECL|macro|PFS168_SYSLCDDE_STNDE
mdefine_line|#define PFS168_SYSLCDDE_STNDE&t;&t;(1&lt;&lt;0)&t;/* CSTN display enable/disable (1/0) */
DECL|macro|PFS168_SYSLCDDE_DESEL
mdefine_line|#define PFS168_SYSLCDDE_DESEL&t;&t;(1&lt;&lt;0)&t;/* Active/Passive (1/0) display enable mode */
DECL|macro|PFS168_SYSCTLA_BKLT
mdefine_line|#define PFS168_SYSCTLA_BKLT&t;&t;(1&lt;&lt;0)&t;/* LCD backlight invert on/off (1/0) */
DECL|macro|PFS168_SYSCTLA_RLY
mdefine_line|#define PFS168_SYSCTLA_RLY&t;&t;(1&lt;&lt;1)&t;/* Relay on/off (1/0) */
DECL|macro|PFS168_SYSCTLA_PXON
mdefine_line|#define PFS168_SYSCTLA_PXON&t;&t;(1&lt;&lt;2)&t;/* Opto relay connect/disconnect 1/0) */
DECL|macro|PFS168_SYSCTLA_IRDA_FSEL
mdefine_line|#define PFS168_SYSCTLA_IRDA_FSEL&t;(1&lt;&lt;3)&t;/* IRDA Frequency select (0 = SIR, 1 = MIR/ FIR) */
DECL|macro|PFS168_SYSCTLB_MG1
mdefine_line|#define PFS168_SYSCTLB_MG1&t;&t;(1&lt;&lt;0)&t;/* Motion detector gain select */
DECL|macro|PFS168_SYSCTLB_MG0
mdefine_line|#define PFS168_SYSCTLB_MG0&t;&t;(1&lt;&lt;1)&t;/* Motion detector gain select */
DECL|macro|PFS168_SYSCTLB_IRDA_MD1
mdefine_line|#define PFS168_SYSCTLB_IRDA_MD1&t;&t;(1&lt;&lt;2)&t;/* Range/Power select */
DECL|macro|PFS168_SYSCTLB_IRDA_MD0
mdefine_line|#define PFS168_SYSCTLB_IRDA_MD0&t;&t;(1&lt;&lt;3)&t;/* Range/Power select */
DECL|macro|PFS168_SYSCTLB_IRDA_MD_MASK
mdefine_line|#define PFS168_SYSCTLB_IRDA_MD_MASK&t;(PFS168_SYSCTLB_IRDA_MD1|PFS168_SYSCTLB_IRDA_MD0)
eof
