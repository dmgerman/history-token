multiline_comment|/*&n; * linux/include/asm-arm/arch-pxa/poodle.h&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * Based on:&n; *   linux/include/asm-arm/arch-sa1100/collie.h&n; *&n; * ChangeLog:&n; *   04-06-2001 Lineo Japan, Inc.&n; *   04-16-2001 SHARP Corporation&n; *   Update to 2.6 John Lenz&n; */
macro_line|#ifndef __ASM_ARCH_POODLE_H
DECL|macro|__ASM_ARCH_POODLE_H
mdefine_line|#define __ASM_ARCH_POODLE_H  1
multiline_comment|/*&n; * GPIOs&n; */
multiline_comment|/* PXA GPIOs */
DECL|macro|POODLE_GPIO_ON_KEY
mdefine_line|#define POODLE_GPIO_ON_KEY&t;&t;(0)
DECL|macro|POODLE_GPIO_AC_IN
mdefine_line|#define POODLE_GPIO_AC_IN&t;&t;(1)
DECL|macro|POODLE_GPIO_CO
mdefine_line|#define POODLE_GPIO_CO&t;&t;&t;16
DECL|macro|POODLE_GPIO_TP_INT
mdefine_line|#define POODLE_GPIO_TP_INT&t;&t;(5)
DECL|macro|POODLE_GPIO_WAKEUP
mdefine_line|#define POODLE_GPIO_WAKEUP&t;&t;(11)&t;/* change battery */
DECL|macro|POODLE_GPIO_GA_INT
mdefine_line|#define POODLE_GPIO_GA_INT&t;&t;(10)
DECL|macro|POODLE_GPIO_IR_ON
mdefine_line|#define POODLE_GPIO_IR_ON&t;&t;(22)
DECL|macro|POODLE_GPIO_HP_IN
mdefine_line|#define POODLE_GPIO_HP_IN&t;&t;(4)
DECL|macro|POODLE_GPIO_CF_IRQ
mdefine_line|#define POODLE_GPIO_CF_IRQ&t;&t;(17)
DECL|macro|POODLE_GPIO_CF_CD
mdefine_line|#define POODLE_GPIO_CF_CD&t;&t;(14)
DECL|macro|POODLE_GPIO_CF_STSCHG
mdefine_line|#define POODLE_GPIO_CF_STSCHG&t;&t;(14)
DECL|macro|POODLE_GPIO_SD_PWR
mdefine_line|#define POODLE_GPIO_SD_PWR&t;&t;(33)
DECL|macro|POODLE_GPIO_nSD_CLK
mdefine_line|#define POODLE_GPIO_nSD_CLK&t;&t;(6)
DECL|macro|POODLE_GPIO_nSD_WP
mdefine_line|#define POODLE_GPIO_nSD_WP&t;&t;(7)
DECL|macro|POODLE_GPIO_nSD_INT
mdefine_line|#define POODLE_GPIO_nSD_INT&t;&t;(8)
DECL|macro|POODLE_GPIO_nSD_DETECT
mdefine_line|#define POODLE_GPIO_nSD_DETECT&t;&t;(9)
DECL|macro|POODLE_GPIO_MAIN_BAT_LOW
mdefine_line|#define POODLE_GPIO_MAIN_BAT_LOW&t;(13)
DECL|macro|POODLE_GPIO_BAT_COVER
mdefine_line|#define POODLE_GPIO_BAT_COVER&t;&t;(13)
DECL|macro|POODLE_GPIO_ADC_TEMP_ON
mdefine_line|#define POODLE_GPIO_ADC_TEMP_ON&t;&t;(21)
DECL|macro|POODLE_GPIO_BYPASS_ON
mdefine_line|#define POODLE_GPIO_BYPASS_ON&t;&t;(36)
DECL|macro|POODLE_GPIO_CHRG_ON
mdefine_line|#define POODLE_GPIO_CHRG_ON&t;&t;(38)
DECL|macro|POODLE_GPIO_CHRG_FULL
mdefine_line|#define POODLE_GPIO_CHRG_FULL&t;&t;(16)
multiline_comment|/* PXA GPIOs */
DECL|macro|POODLE_IRQ_GPIO_ON_KEY
mdefine_line|#define POODLE_IRQ_GPIO_ON_KEY&t;&t;IRQ_GPIO0
DECL|macro|POODLE_IRQ_GPIO_AC_IN
mdefine_line|#define POODLE_IRQ_GPIO_AC_IN&t;&t;IRQ_GPIO1
DECL|macro|POODLE_IRQ_GPIO_HP_IN
mdefine_line|#define POODLE_IRQ_GPIO_HP_IN&t;&t;IRQ_GPIO4
DECL|macro|POODLE_IRQ_GPIO_CO
mdefine_line|#define POODLE_IRQ_GPIO_CO&t;&t;IRQ_GPIO16
DECL|macro|POODLE_IRQ_GPIO_TP_INT
mdefine_line|#define POODLE_IRQ_GPIO_TP_INT&t;&t;IRQ_GPIO5
DECL|macro|POODLE_IRQ_GPIO_WAKEUP
mdefine_line|#define POODLE_IRQ_GPIO_WAKEUP&t;&t;IRQ_GPIO11
DECL|macro|POODLE_IRQ_GPIO_GA_INT
mdefine_line|#define POODLE_IRQ_GPIO_GA_INT&t;&t;IRQ_GPIO10
DECL|macro|POODLE_IRQ_GPIO_CF_IRQ
mdefine_line|#define POODLE_IRQ_GPIO_CF_IRQ&t;&t;IRQ_GPIO17
DECL|macro|POODLE_IRQ_GPIO_CF_CD
mdefine_line|#define POODLE_IRQ_GPIO_CF_CD&t;&t;IRQ_GPIO14
DECL|macro|POODLE_IRQ_GPIO_nSD_INT
mdefine_line|#define POODLE_IRQ_GPIO_nSD_INT&t;&t;IRQ_GPIO8
DECL|macro|POODLE_IRQ_GPIO_nSD_DETECT
mdefine_line|#define POODLE_IRQ_GPIO_nSD_DETECT&t;IRQ_GPIO9
DECL|macro|POODLE_IRQ_GPIO_MAIN_BAT_LOW
mdefine_line|#define POODLE_IRQ_GPIO_MAIN_BAT_LOW&t;IRQ_GPIO13
multiline_comment|/* SCOOP GPIOs */
DECL|macro|POODLE_SCOOP_CHARGE_ON
mdefine_line|#define POODLE_SCOOP_CHARGE_ON&t;SCOOP_GPCR_PA11
DECL|macro|POODLE_SCOOP_CP401
mdefine_line|#define POODLE_SCOOP_CP401&t;SCOOP_GPCR_PA13
DECL|macro|POODLE_SCOOP_VPEN
mdefine_line|#define POODLE_SCOOP_VPEN&t;SCOOP_GPCR_PA18
DECL|macro|POODLE_SCOOP_L_PCLK
mdefine_line|#define POODLE_SCOOP_L_PCLK&t;SCOOP_GPCR_PA20
DECL|macro|POODLE_SCOOP_L_LCLK
mdefine_line|#define POODLE_SCOOP_L_LCLK&t;SCOOP_GPCR_PA21
DECL|macro|POODLE_SCOOP_HS_OUT
mdefine_line|#define POODLE_SCOOP_HS_OUT&t;SCOOP_GPCR_PA22
DECL|macro|POODLE_SCOOP_IO_DIR
mdefine_line|#define POODLE_SCOOP_IO_DIR&t;( POODLE_SCOOP_VPEN | POODLE_SCOOP_HS_OUT )
DECL|macro|POODLE_SCOOP_IO_OUT
mdefine_line|#define POODLE_SCOOP_IO_OUT&t;( 0 )
multiline_comment|/*&n; * Flash Memory mappings&n; *&n; * We have the following mapping:&n; *                      phys            virt&n; *      boot ROM        00000000        ef800000&n; */
DECL|macro|FLASH_MEM_BASE
mdefine_line|#define FLASH_MEM_BASE&t;0xa0000a00
DECL|macro|FLASH_DATA
mdefine_line|#define&t;FLASH_DATA(adr) (*(volatile unsigned int*)(FLASH_MEM_BASE+(adr)))
DECL|macro|FLASH_DATA_F
mdefine_line|#define&t;FLASH_DATA_F(adr) (*(volatile float32 *)(FLASH_MEM_BASE+(adr)))
DECL|macro|FLASH_MAGIC_CHG
mdefine_line|#define FLASH_MAGIC_CHG(a,b,c,d) ( ( d &lt;&lt; 24 ) | ( c &lt;&lt; 16 )  | ( b &lt;&lt; 8 ) | a )
multiline_comment|/* COMADJ */
DECL|macro|FLASH_COMADJ_MAJIC
mdefine_line|#define FLASH_COMADJ_MAJIC&t;FLASH_MAGIC_CHG(&squot;C&squot;,&squot;M&squot;,&squot;A&squot;,&squot;D&squot;)
DECL|macro|FLASH_COMADJ_MAGIC_ADR
mdefine_line|#define&t;FLASH_COMADJ_MAGIC_ADR&t;0x00
DECL|macro|FLASH_COMADJ_DATA_ADR
mdefine_line|#define&t;FLASH_COMADJ_DATA_ADR&t;0x04
multiline_comment|/* UUID */
DECL|macro|FLASH_UUID_MAJIC
mdefine_line|#define FLASH_UUID_MAJIC&t;FLASH_MAGIC_CHG(&squot;U&squot;,&squot;U&squot;,&squot;I&squot;,&squot;D&squot;)
DECL|macro|FLASH_UUID_MAGIC_ADR
mdefine_line|#define&t;FLASH_UUID_MAGIC_ADR&t;0x08
DECL|macro|FLASH_UUID_DATA_ADR
mdefine_line|#define&t;FLASH_UUID_DATA_ADR&t;0x0C
multiline_comment|/* TOUCH PANEL */
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
multiline_comment|/* AD */
DECL|macro|FLASH_AD_MAJIC
mdefine_line|#define FLASH_AD_MAJIC&t;FLASH_MAGIC_CHG(&squot;B&squot;,&squot;V&squot;,&squot;A&squot;,&squot;D&squot;)
DECL|macro|FLASH_AD_MAGIC_ADR
mdefine_line|#define&t;FLASH_AD_MAGIC_ADR&t;0x30
DECL|macro|FLASH_AD_DATA_ADR
mdefine_line|#define&t;FLASH_AD_DATA_ADR&t;0x34
multiline_comment|/* PHAD */
DECL|macro|FLASH_PHAD_MAJIC
mdefine_line|#define FLASH_PHAD_MAJIC&t;FLASH_MAGIC_CHG(&squot;P&squot;,&squot;H&squot;,&squot;A&squot;,&squot;D&squot;)
DECL|macro|FLASH_PHAD_MAGIC_ADR
mdefine_line|#define&t;FLASH_PHAD_MAGIC_ADR&t;0x38
DECL|macro|FLASH_PHAD_DATA_ADR
mdefine_line|#define&t;FLASH_PHAD_DATA_ADR&t;0x3C
macro_line|#endif /* __ASM_ARCH_POODLE_H  */
eof
