multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/collie.h&n; *&n; * This file contains the hardware specific definitions for Assabet&n; * Only include this file from SA1100-specific files.&n; *&n; * ChangeLog:&n; *   04-06-2001 Lineo Japan, Inc.&n; *   04-16-2001 SHARP Corporation&n; *   07-07-2002 Chris Larson &lt;clarson@digi.com&gt;&n; *&n; */
macro_line|#ifndef __ASM_ARCH_COLLIE_H
DECL|macro|__ASM_ARCH_COLLIE_H
mdefine_line|#define __ASM_ARCH_COLLIE_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|COLLIE_SCP_CHARGE_ON
mdefine_line|#define COLLIE_SCP_CHARGE_ON&t;SCOOP_GPCR_PA11
DECL|macro|COLLIE_SCP_DIAG_BOOT1
mdefine_line|#define COLLIE_SCP_DIAG_BOOT1&t;SCOOP_GPCR_PA12
DECL|macro|COLLIE_SCP_DIAG_BOOT2
mdefine_line|#define COLLIE_SCP_DIAG_BOOT2&t;SCOOP_GPCR_PA13
DECL|macro|COLLIE_SCP_MUTE_L
mdefine_line|#define COLLIE_SCP_MUTE_L&t;SCOOP_GPCR_PA14
DECL|macro|COLLIE_SCP_MUTE_R
mdefine_line|#define COLLIE_SCP_MUTE_R&t;SCOOP_GPCR_PA15
DECL|macro|COLLIE_SCP_5VON
mdefine_line|#define COLLIE_SCP_5VON&t;&t;SCOOP_GPCR_PA16
DECL|macro|COLLIE_SCP_AMP_ON
mdefine_line|#define COLLIE_SCP_AMP_ON&t;SCOOP_GPCR_PA17
DECL|macro|COLLIE_SCP_VPEN
mdefine_line|#define COLLIE_SCP_VPEN&t;&t;SCOOP_GPCR_PA18
DECL|macro|COLLIE_SCP_LB_VOL_CHG
mdefine_line|#define COLLIE_SCP_LB_VOL_CHG&t;SCOOP_GPCR_PA19
DECL|macro|COLLIE_SCOOP_IO_DIR
mdefine_line|#define COLLIE_SCOOP_IO_DIR&t;( COLLIE_SCP_CHARGE_ON | COLLIE_SCP_MUTE_L | COLLIE_SCP_MUTE_R | &bslash;&n;&t;&t;&t;&t;COLLIE_SCP_5VON | COLLIE_SCP_AMP_ON | COLLIE_SCP_VPEN | &bslash;&n;&t;&t;&t;&t;COLLIE_SCP_LB_VOL_CHG )
DECL|macro|COLLIE_SCOOP_IO_OUT
mdefine_line|#define COLLIE_SCOOP_IO_OUT&t;( COLLIE_SCP_MUTE_L | COLLIE_SCP_MUTE_R | COLLIE_SCP_VPEN | &bslash;&n;&t;&t;&t;&t;COLLIE_SCP_CHARGE_ON )
multiline_comment|/* GPIOs for which the generic definition doesn&squot;t say much */
DECL|macro|COLLIE_GPIO_ON_KEY
mdefine_line|#define COLLIE_GPIO_ON_KEY&t;&t;GPIO_GPIO (0)
DECL|macro|COLLIE_GPIO_AC_IN
mdefine_line|#define COLLIE_GPIO_AC_IN&t;&t;GPIO_GPIO (1)
DECL|macro|COLLIE_GPIO_CF_IRQ
mdefine_line|#define COLLIE_GPIO_CF_IRQ&t;&t;GPIO_GPIO (14)
DECL|macro|COLLIE_GPIO_nREMOCON_INT
mdefine_line|#define COLLIE_GPIO_nREMOCON_INT&t;GPIO_GPIO (15)
DECL|macro|COLLIE_GPIO_UCB1x00_RESET
mdefine_line|#define COLLIE_GPIO_UCB1x00_RESET&t;GPIO_GPIO (16)
DECL|macro|COLLIE_GPIO_CO
mdefine_line|#define COLLIE_GPIO_CO&t;&t;&t;GPIO_GPIO (20)
DECL|macro|COLLIE_GPIO_MCP_CLK
mdefine_line|#define COLLIE_GPIO_MCP_CLK&t;&t;GPIO_GPIO (21)
DECL|macro|COLLIE_GPIO_CF_CD
mdefine_line|#define COLLIE_GPIO_CF_CD&t;&t;GPIO_GPIO (22)
DECL|macro|COLLIE_GPIO_UCB1x00_IRQ
mdefine_line|#define COLLIE_GPIO_UCB1x00_IRQ&t;&t;GPIO_GPIO (23)
DECL|macro|COLLIE_GPIO_WAKEUP
mdefine_line|#define COLLIE_GPIO_WAKEUP&t;&t;GPIO_GPIO (24)
DECL|macro|COLLIE_GPIO_GA_INT
mdefine_line|#define COLLIE_GPIO_GA_INT&t;&t;GPIO_GPIO (25)
DECL|macro|COLLIE_GPIO_MAIN_BAT_LOW
mdefine_line|#define COLLIE_GPIO_MAIN_BAT_LOW&t;GPIO_GPIO (26)
multiline_comment|/* Interrupts */
DECL|macro|COLLIE_IRQ_GPIO_ON_KEY
mdefine_line|#define COLLIE_IRQ_GPIO_ON_KEY&t;&t;IRQ_GPIO0
DECL|macro|COLLIE_IRQ_GPIO_AC_IN
mdefine_line|#define COLLIE_IRQ_GPIO_AC_IN&t;&t;IRQ_GPIO1
DECL|macro|COLLIE_IRQ_GPIO_CF_IRQ
mdefine_line|#define COLLIE_IRQ_GPIO_CF_IRQ&t;&t;IRQ_GPIO14
DECL|macro|COLLIE_IRQ_GPIO_nREMOCON_INT
mdefine_line|#define COLLIE_IRQ_GPIO_nREMOCON_INT&t;IRQ_GPIO15
DECL|macro|COLLIE_IRQ_GPIO_CO
mdefine_line|#define COLLIE_IRQ_GPIO_CO&t;&t;IRQ_GPIO20
DECL|macro|COLLIE_IRQ_GPIO_CF_CD
mdefine_line|#define COLLIE_IRQ_GPIO_CF_CD&t;&t;IRQ_GPIO22
DECL|macro|COLLIE_IRQ_GPIO_UCB1x00_IRQ
mdefine_line|#define COLLIE_IRQ_GPIO_UCB1x00_IRQ&t;IRQ_GPIO23
DECL|macro|COLLIE_IRQ_GPIO_WAKEUP
mdefine_line|#define COLLIE_IRQ_GPIO_WAKEUP&t;&t;IRQ_GPIO24
DECL|macro|COLLIE_IRQ_GPIO_GA_INT
mdefine_line|#define COLLIE_IRQ_GPIO_GA_INT&t;&t;IRQ_GPIO25
DECL|macro|COLLIE_IRQ_GPIO_MAIN_BAT_LOW
mdefine_line|#define COLLIE_IRQ_GPIO_MAIN_BAT_LOW&t;IRQ_GPIO26
DECL|macro|COLLIE_LCM_IRQ_GPIO_RTS
mdefine_line|#define COLLIE_LCM_IRQ_GPIO_RTS&t;&t;IRQ_LOCOMO_GPIO0
DECL|macro|COLLIE_LCM_IRQ_GPIO_CTS
mdefine_line|#define COLLIE_LCM_IRQ_GPIO_CTS&t;&t;IRQ_LOCOMO_GPIO1
DECL|macro|COLLIE_LCM_IRQ_GPIO_DSR
mdefine_line|#define COLLIE_LCM_IRQ_GPIO_DSR&t;&t;IRQ_LOCOMO_GPIO2
DECL|macro|COLLIE_LCM_IRQ_GPIO_DTR
mdefine_line|#define COLLIE_LCM_IRQ_GPIO_DTR&t;&t;IRQ_LOCOMO_GPIO3
DECL|macro|COLLIE_LCM_IRQ_GPIO_nSD_DETECT
mdefine_line|#define COLLIE_LCM_IRQ_GPIO_nSD_DETECT&t;IRQ_LOCOMO_GPIO13
DECL|macro|COLLIE_LCM_IRQ_GPIO_nSD_WP
mdefine_line|#define COLLIE_LCM_IRQ_GPIO_nSD_WP&t;IRQ_LOCOMO_GPIO14
multiline_comment|/*&n; * Flash Memory mappings&n; *&n; */
DECL|macro|FLASH_MEM_BASE
mdefine_line|#define FLASH_MEM_BASE 0xe8ffc000
DECL|macro|FLASH_DATA
mdefine_line|#define&t;FLASH_DATA(adr) (*(volatile unsigned int*)(FLASH_MEM_BASE+(adr)))
DECL|macro|FLASH_DATA_F
mdefine_line|#define&t;FLASH_DATA_F(adr) (*(volatile float32 *)(FLASH_MEM_BASE+(adr)))
DECL|macro|FLASH_MAGIC_CHG
mdefine_line|#define FLASH_MAGIC_CHG(a,b,c,d) ( ( d &lt;&lt; 24 ) | ( c &lt;&lt; 16 )  | ( b &lt;&lt; 8 ) | a )
singleline_comment|// COMADJ
DECL|macro|FLASH_COMADJ_MAJIC
mdefine_line|#define FLASH_COMADJ_MAJIC&t;FLASH_MAGIC_CHG(&squot;C&squot;,&squot;M&squot;,&squot;A&squot;,&squot;D&squot;)
DECL|macro|FLASH_COMADJ_MAGIC_ADR
mdefine_line|#define&t;FLASH_COMADJ_MAGIC_ADR&t;0x00
DECL|macro|FLASH_COMADJ_DATA_ADR
mdefine_line|#define&t;FLASH_COMADJ_DATA_ADR&t;0x04
singleline_comment|// TOUCH PANEL
DECL|macro|FLASH_TOUCH_MAJIC
mdefine_line|#define FLASH_TOUCH_MAJIC&t;FLASH_MAGIC_CHG(&squot;T&squot;,&squot;U&squot;,&squot;C&squot;,&squot;H&squot;)
DECL|macro|FLASH_TOUCH_MAGIC_ADR
mdefine_line|#define&t;FLASH_TOUCH_MAGIC_ADR&t;0x1C
DECL|macro|FLASH_TOUCH_XP_DATA_ADR
mdefine_line|#define&t;FLASH_TOUCH_XP_DATA_ADR&t;0x20
DECL|macro|FLASH_TOUCH_YP_DATA_ADR
mdefine_line|#define&t;FLASH_TOUCH_YP_DATA_ADR&t;0x24
DECL|macro|FLASH_TOUCH_XD_DATA_ADR
mdefine_line|#define&t;FLASH_TOUCH_XD_DATA_ADR&t;0x28
DECL|macro|FLASH_TOUCH_YD_DATA_ADR
mdefine_line|#define&t;FLASH_TOUCH_YD_DATA_ADR&t;0x2C
singleline_comment|// AD
DECL|macro|FLASH_AD_MAJIC
mdefine_line|#define FLASH_AD_MAJIC&t;FLASH_MAGIC_CHG(&squot;B&squot;,&squot;V&squot;,&squot;A&squot;,&squot;D&squot;)
DECL|macro|FLASH_AD_MAGIC_ADR
mdefine_line|#define&t;FLASH_AD_MAGIC_ADR&t;0x30
DECL|macro|FLASH_AD_DATA_ADR
mdefine_line|#define&t;FLASH_AD_DATA_ADR&t;0x34
multiline_comment|/* GPIO&squot;s on the TC35143AF (Toshiba Analog Frontend) */
DECL|macro|COLLIE_TC35143_GPIO_VERSION0
mdefine_line|#define COLLIE_TC35143_GPIO_VERSION0    UCB_IO_0&t;/* GPIO0=Version                 */
DECL|macro|COLLIE_TC35143_GPIO_TBL_CHK
mdefine_line|#define COLLIE_TC35143_GPIO_TBL_CHK     UCB_IO_1&t;/* GPIO1=TBL_CHK                 */
DECL|macro|COLLIE_TC35143_GPIO_VPEN_ON
mdefine_line|#define COLLIE_TC35143_GPIO_VPEN_ON     UCB_IO_2&t;/* GPIO2=VPNE_ON                 */
DECL|macro|COLLIE_TC35143_GPIO_IR_ON
mdefine_line|#define COLLIE_TC35143_GPIO_IR_ON       UCB_IO_3&t;/* GPIO3=IR_ON                   */
DECL|macro|COLLIE_TC35143_GPIO_AMP_ON
mdefine_line|#define COLLIE_TC35143_GPIO_AMP_ON      UCB_IO_4&t;/* GPIO4=AMP_ON                  */
DECL|macro|COLLIE_TC35143_GPIO_VERSION1
mdefine_line|#define COLLIE_TC35143_GPIO_VERSION1    UCB_IO_5&t;/* GPIO5=Version                 */
DECL|macro|COLLIE_TC35143_GPIO_FS8KLPF
mdefine_line|#define COLLIE_TC35143_GPIO_FS8KLPF     UCB_IO_5&t;/* GPIO5=fs 8k LPF               */
DECL|macro|COLLIE_TC35143_GPIO_BUZZER_BIAS
mdefine_line|#define COLLIE_TC35143_GPIO_BUZZER_BIAS UCB_IO_6&t;/* GPIO6=BUZZER BIAS             */
DECL|macro|COLLIE_TC35143_GPIO_MBAT_ON
mdefine_line|#define COLLIE_TC35143_GPIO_MBAT_ON     UCB_IO_7&t;/* GPIO7=MBAT_ON                 */
DECL|macro|COLLIE_TC35143_GPIO_BBAT_ON
mdefine_line|#define COLLIE_TC35143_GPIO_BBAT_ON     UCB_IO_8&t;/* GPIO8=BBAT_ON                 */
DECL|macro|COLLIE_TC35143_GPIO_TMP_ON
mdefine_line|#define COLLIE_TC35143_GPIO_TMP_ON      UCB_IO_9&t;/* GPIO9=TMP_ON                  */
DECL|macro|COLLIE_TC35143_GPIO_IN
mdefine_line|#define COLLIE_TC35143_GPIO_IN&t;&t;( UCB_IO_0 | UCB_IO_2 | UCB_IO_5 )
DECL|macro|COLLIE_TC35143_GPIO_OUT
mdefine_line|#define COLLIE_TC35143_GPIO_OUT&t;&t;( UCB_IO_1 | UCB_IO_3 | UCB_IO_4 | UCB_IO_6 | &bslash;&n;&t;&t;&t;&t;&t;UCB_IO_7 | UCB_IO_8 | UCB_IO_9 )
macro_line|#endif
eof
