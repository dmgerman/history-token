macro_line|#ifndef _INCLUDE_CERF_H_
DECL|macro|_INCLUDE_CERF_H_
mdefine_line|#define _INCLUDE_CERF_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SA1100_CERF_CPLD
singleline_comment|// Map sa1100fb.c to sa1100_frontlight.c - Not pretty, but necessary.
DECL|macro|CERF_BACKLIGHT_ENABLE
mdefine_line|#define CERF_BACKLIGHT_ENABLE   sa1100_fl_enable
DECL|macro|CERF_BACKLIGHT_DISABLE
mdefine_line|#define CERF_BACKLIGHT_DISABLE  sa1100_fl_disable
singleline_comment|//
singleline_comment|// IO Pins for devices
singleline_comment|//
DECL|macro|CERF_PDA_CPLD
mdefine_line|#define CERF_PDA_CPLD             0xf1000000
DECL|macro|CERF_PDA_CPLD_WRCLRINT
mdefine_line|#define CERF_PDA_CPLD_WRCLRINT    (0x0)
DECL|macro|CERF_PDA_CPLD_BACKLIGHT
mdefine_line|#define CERF_PDA_CPLD_BACKLIGHT   (0x2)
DECL|macro|CERF_PDA_CPLD_SOUND_FREQ
mdefine_line|#define CERF_PDA_CPLD_SOUND_FREQ  (0x4)
DECL|macro|CERF_PDA_CPLD_KEYPAD_A
mdefine_line|#define CERF_PDA_CPLD_KEYPAD_A    (0x6)
DECL|macro|CERF_PDA_CPLD_BATTFAULT
mdefine_line|#define CERF_PDA_CPLD_BATTFAULT   (0x8)
DECL|macro|CERF_PDA_CPLD_KEYPAD_B
mdefine_line|#define CERF_PDA_CPLD_KEYPAD_B    (0xa)
DECL|macro|CERF_PDA_CPLD_SOUND_ENA
mdefine_line|#define CERF_PDA_CPLD_SOUND_ENA   (0xc)
DECL|macro|CERF_PDA_CPLD_SOUND_RESET
mdefine_line|#define CERF_PDA_CPLD_SOUND_RESET (0xe)
DECL|macro|GPIO_CF_BVD2
mdefine_line|#define GPIO_CF_BVD2              GPIO_GPIO (5)
DECL|macro|GPIO_CF_BVD1
mdefine_line|#define GPIO_CF_BVD1              GPIO_GPIO (6)
DECL|macro|GPIO_CF_RESET
mdefine_line|#define GPIO_CF_RESET             GPIO_GPIO (7)
DECL|macro|GPIO_CF_IRQ
mdefine_line|#define GPIO_CF_IRQ               GPIO_GPIO (8)
DECL|macro|GPIO_CF_CD
mdefine_line|#define GPIO_CF_CD                GPIO_GPIO (9)
DECL|macro|GPIO_PWR_SHUTDOWN
mdefine_line|#define GPIO_PWR_SHUTDOWN         GPIO_GPIO (25)
DECL|macro|UCB1200_GPIO_CONT_CS
mdefine_line|#define UCB1200_GPIO_CONT_CS      0x0001
DECL|macro|UCB1200_GPIO_CONT_DOWN
mdefine_line|#define UCB1200_GPIO_CONT_DOWN    0x0002
DECL|macro|UCB1200_GPIO_CONT_INC
mdefine_line|#define UCB1200_GPIO_CONT_INC     0x0004
DECL|macro|UCB1200_GPIO_CONT_ENA
mdefine_line|#define UCB1200_GPIO_CONT_ENA     0x0008
DECL|macro|UCB1200_GPIO_LCD_RESET
mdefine_line|#define UCB1200_GPIO_LCD_RESET    0x0010
DECL|macro|UCB1200_GPIO_IRDA_ENABLE
mdefine_line|#define UCB1200_GPIO_IRDA_ENABLE  0x0020
DECL|macro|UCB1200_GPIO_BT_ENABLE
mdefine_line|#define UCB1200_GPIO_BT_ENABLE    0x0040
DECL|macro|UCB1200_GPIO_L3_DATA
mdefine_line|#define UCB1200_GPIO_L3_DATA      0x0080
DECL|macro|UCB1200_GPIO_L3_CLOCK
mdefine_line|#define UCB1200_GPIO_L3_CLOCK     0x0100
DECL|macro|UCB1200_GPIO_L3_MODE
mdefine_line|#define UCB1200_GPIO_L3_MODE      0x0200
singleline_comment|//
singleline_comment|// IRQ for devices
singleline_comment|//
DECL|macro|IRQ_UCB1200_CONT_CS
mdefine_line|#define IRQ_UCB1200_CONT_CS     IRQ_UCB1200_IO0
DECL|macro|IRQ_UCB1200_CONT_DOWN
mdefine_line|#define IRQ_UCB1200_CONT_DOWN   IRQ_UCB1200_IO1
DECL|macro|IRQ_UCB1200_CONT_INC
mdefine_line|#define IRQ_UCB1200_CONT_INC    IRQ_UCB1200_IO2
DECL|macro|IRQ_UCB1200_CONT_ENA
mdefine_line|#define IRQ_UCB1200_CONT_ENA    IRQ_UCB1200_IO3
DECL|macro|IRQ_UCB1200_LCD_RESET
mdefine_line|#define IRQ_UCB1200_LCD_RESET   IRQ_UCB1200_IO4
DECL|macro|IRQ_UCB1200_IRDA_ENABLE
mdefine_line|#define IRQ_UCB1200_IRDA_ENABLE IRQ_UCB1200_IO5
DECL|macro|IRQ_UCB1200_BT_ENABLE
mdefine_line|#define IRQ_UCB1200_BT_ENABLE   IRQ_UCB1200_IO6
DECL|macro|IRQ_UCB1200_L3_DATA
mdefine_line|#define IRQ_UCB1200_L3_DATA     IRQ_UCB1200_IO7
DECL|macro|IRQ_UCB1200_L3_CLOCK
mdefine_line|#define IRQ_UCB1200_L3_CLOCK    IRQ_UCB1200_IO8
DECL|macro|IRQ_UCB1200_L3_MODE
mdefine_line|#define IRQ_UCB1200_L3_MODE     IRQ_UCB1200_IO9
DECL|macro|IRQ_GPIO_CF_BVD2
mdefine_line|#define IRQ_GPIO_CF_BVD2        IRQ_GPIO5
DECL|macro|IRQ_GPIO_CF_BVD1
mdefine_line|#define IRQ_GPIO_CF_BVD1        IRQ_GPIO6
DECL|macro|IRQ_GPIO_CF_IRQ
mdefine_line|#define IRQ_GPIO_CF_IRQ         IRQ_GPIO8
DECL|macro|IRQ_GPIO_CF_CD
mdefine_line|#define IRQ_GPIO_CF_CD          IRQ_GPIO9
singleline_comment|//
singleline_comment|// Device parameters
singleline_comment|//
DECL|macro|CERF_PDA_CPLD_SOUND_FREQ_8000
mdefine_line|#define CERF_PDA_CPLD_SOUND_FREQ_8000  (0x01)
DECL|macro|CERF_PDA_CPLD_SOUND_FREQ_11025
mdefine_line|#define CERF_PDA_CPLD_SOUND_FREQ_11025 (0x05)
DECL|macro|CERF_PDA_CPLD_SOUND_FREQ_16000
mdefine_line|#define CERF_PDA_CPLD_SOUND_FREQ_16000 (0x02)
DECL|macro|CERF_PDA_CPLD_SOUND_FREQ_22050
mdefine_line|#define CERF_PDA_CPLD_SOUND_FREQ_22050 (0x06)
DECL|macro|CERF_PDA_CPLD_SOUND_FREQ_32000
mdefine_line|#define CERF_PDA_CPLD_SOUND_FREQ_32000 (0x03)
DECL|macro|CERF_PDA_CPLD_SOUND_FREQ_44100
mdefine_line|#define CERF_PDA_CPLD_SOUND_FREQ_44100 (0x07)
DECL|macro|CERF_PDA_CPLD_SOUND_FREQ_48000
mdefine_line|#define CERF_PDA_CPLD_SOUND_FREQ_48000 (0x0b)
singleline_comment|//
singleline_comment|// General Functions
singleline_comment|//
DECL|macro|CERF_PDA_CPLD_Get
mdefine_line|#define CERF_PDA_CPLD_Get(x, y)      (*((char*)(CERF_PDA_CPLD + (x))) &amp; (y))
DECL|macro|CERF_PDA_CPLD_Set
mdefine_line|#define CERF_PDA_CPLD_Set(x, y, z)   (*((char*)(CERF_PDA_CPLD + (x))) = (*((char*)(CERF_PDA_CPLD + (x))) &amp; ~(z)) | (y))
DECL|macro|CERF_PDA_CPLD_UnSet
mdefine_line|#define CERF_PDA_CPLD_UnSet(x, y, z) (*((char*)(CERF_PDA_CPLD + (x))) = (*((char*)(CERF_PDA_CPLD + (x))) &amp; ~(z)) &amp; ~(y))
macro_line|#else 
singleline_comment|// CONFIG_SA1100_CERF_CPLD
DECL|macro|GPIO_CF_BVD2
mdefine_line|#define GPIO_CF_BVD2            GPIO_GPIO (19)
DECL|macro|GPIO_CF_BVD1
mdefine_line|#define GPIO_CF_BVD1            GPIO_GPIO (20)
DECL|macro|GPIO_CF_RESET
mdefine_line|#define GPIO_CF_RESET           0
DECL|macro|GPIO_CF_IRQ
mdefine_line|#define GPIO_CF_IRQ             GPIO_GPIO (22)
DECL|macro|GPIO_CF_CD
mdefine_line|#define GPIO_CF_CD              GPIO_GPIO (23)
DECL|macro|GPIO_LCD_RESET
mdefine_line|#define GPIO_LCD_RESET          GPIO_GPIO (15)
DECL|macro|IRQ_GPIO_CF_BVD2
mdefine_line|#define IRQ_GPIO_CF_BVD2        IRQ_GPIO19
DECL|macro|IRQ_GPIO_CF_BVD1
mdefine_line|#define IRQ_GPIO_CF_BVD1        IRQ_GPIO20
DECL|macro|IRQ_GPIO_CF_IRQ
mdefine_line|#define IRQ_GPIO_CF_IRQ         IRQ_GPIO22
DECL|macro|IRQ_GPIO_CF_CD
mdefine_line|#define IRQ_GPIO_CF_CD          IRQ_GPIO23
macro_line|#endif 
singleline_comment|// CONFIG_SA1100_CERF_CPLD
DECL|macro|GPIO_UCB1200_IRQ
mdefine_line|#define GPIO_UCB1200_IRQ        GPIO_GPIO (18)
DECL|macro|IRQ_GPIO_UCB1200_IRQ
mdefine_line|#define IRQ_GPIO_UCB1200_IRQ    IRQ_GPIO18
macro_line|#endif 
singleline_comment|// _INCLUDE_CERF_H_
eof
