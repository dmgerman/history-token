multiline_comment|/*&n; * LED, LCD and Button panel driver for Cobalt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1997 by Andrew Bose&n; *&n; * Linux kernel version history:&n; *       March 2001: Ported from 2.0.34  by Liam Davies&n; *&n; */
singleline_comment|// function headers
r_static
r_int
id|dqpoll
c_func
(paren
r_volatile
r_int
r_int
comma
r_volatile
r_int
r_char
)paren
suffix:semicolon
r_static
r_int
id|timeout
c_func
(paren
r_volatile
r_int
r_int
)paren
suffix:semicolon
DECL|macro|LCD_CHARS_PER_LINE
mdefine_line|#define LCD_CHARS_PER_LINE 40
DECL|macro|FLASH_SIZE
mdefine_line|#define FLASH_SIZE 524288
DECL|macro|MAX_IDLE_TIME
mdefine_line|#define MAX_IDLE_TIME 120
DECL|struct|lcd_display
r_struct
id|lcd_display
(brace
DECL|member|buttons
r_int
r_int
id|buttons
suffix:semicolon
DECL|member|size1
r_int
id|size1
suffix:semicolon
DECL|member|size2
r_int
id|size2
suffix:semicolon
DECL|member|line1
r_int
r_char
id|line1
(braket
id|LCD_CHARS_PER_LINE
)braket
suffix:semicolon
DECL|member|line2
r_int
r_char
id|line2
(braket
id|LCD_CHARS_PER_LINE
)braket
suffix:semicolon
DECL|member|cursor_address
r_int
r_char
id|cursor_address
suffix:semicolon
DECL|member|character
r_int
r_char
id|character
suffix:semicolon
DECL|member|leds
r_int
r_char
id|leds
suffix:semicolon
DECL|member|RomImage
r_int
r_char
op_star
id|RomImage
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|LCD_DRIVER
mdefine_line|#define LCD_DRIVER&t;&quot;Cobalt LCD Driver v2.10&quot;
DECL|macro|LCD
mdefine_line|#define LCD&t;&t;&quot;lcd: &quot;
DECL|macro|kLCD_IR
mdefine_line|#define kLCD_IR&t;&t;0x0F000000
DECL|macro|kLCD_DR
mdefine_line|#define kLCD_DR&t;&t;0x0F000010
DECL|macro|kGPI
mdefine_line|#define kGPI&t;&t;0x0D000000
DECL|macro|kLED
mdefine_line|#define kLED&t;&t;0x0C000000
DECL|macro|kDD_R00
mdefine_line|#define kDD_R00         0x00
DECL|macro|kDD_R01
mdefine_line|#define kDD_R01         0x27
DECL|macro|kDD_R10
mdefine_line|#define kDD_R10         0x40
DECL|macro|kDD_R11
mdefine_line|#define kDD_R11         0x67
DECL|macro|kLCD_Addr
mdefine_line|#define kLCD_Addr       0x00000080
DECL|macro|LCDTimeoutValue
mdefine_line|#define LCDTimeoutValue&t;0xfff
singleline_comment|// Flash definitions AMD 29F040
DECL|macro|kFlashBase
mdefine_line|#define kFlashBase&t;0x0FC00000
DECL|macro|kFlash_Addr1
mdefine_line|#define kFlash_Addr1    0x5555
DECL|macro|kFlash_Addr2
mdefine_line|#define kFlash_Addr2    0x2AAA
DECL|macro|kFlash_Data1
mdefine_line|#define kFlash_Data1    0xAA
DECL|macro|kFlash_Data2
mdefine_line|#define kFlash_Data2    0x55
DECL|macro|kFlash_Prog
mdefine_line|#define kFlash_Prog     0xA0
DECL|macro|kFlash_Erase3
mdefine_line|#define kFlash_Erase3   0x80
DECL|macro|kFlash_Erase6
mdefine_line|#define kFlash_Erase6   0x10
DECL|macro|kFlash_Read
mdefine_line|#define kFlash_Read     0xF0
DECL|macro|kFlash_ID
mdefine_line|#define kFlash_ID       0x90
DECL|macro|kFlash_VenAddr
mdefine_line|#define kFlash_VenAddr  0x00
DECL|macro|kFlash_DevAddr
mdefine_line|#define kFlash_DevAddr  0x01
DECL|macro|kFlash_VenID
mdefine_line|#define kFlash_VenID    0x01
DECL|macro|kFlash_DevID
mdefine_line|#define kFlash_DevID    0xA4    
singleline_comment|// 29F040
singleline_comment|//#define kFlash_DevID  0xAD    // 29F016
singleline_comment|// Macros
DECL|macro|LCDWriteData
mdefine_line|#define LCDWriteData(x)&t;outl((x &lt;&lt; 24), kLCD_DR)
DECL|macro|LCDWriteInst
mdefine_line|#define LCDWriteInst(x)&t;outl((x &lt;&lt; 24), kLCD_IR)
DECL|macro|LCDReadData
mdefine_line|#define LCDReadData&t;(inl(kLCD_DR) &gt;&gt; 24)
DECL|macro|LCDReadInst
mdefine_line|#define LCDReadInst&t;(inl(kLCD_IR) &gt;&gt; 24)
DECL|macro|GPIRead
mdefine_line|#define GPIRead&t;&t;(inl(kGPI) &gt;&gt; 24)
DECL|macro|LEDSet
mdefine_line|#define LEDSet(x)&t;outb((char)x, kLED)
DECL|macro|WRITE_GAL
mdefine_line|#define WRITE_GAL(x,y)&t;outl(y, 0x04000000 | (x))
DECL|macro|BusyCheck
mdefine_line|#define BusyCheck()&t;while ((LCDReadInst &amp; 0x80) == 0x80)
DECL|macro|WRITE_FLASH
mdefine_line|#define WRITE_FLASH(x,y) outb((char)y, kFlashBase | (x))
DECL|macro|READ_FLASH
mdefine_line|#define READ_FLASH(x)&t;(inb(kFlashBase | (x)))
multiline_comment|/*&n; * Function command codes for io_ctl.&n; */
DECL|macro|LCD_On
mdefine_line|#define LCD_On&t;&t;&t;1
DECL|macro|LCD_Off
mdefine_line|#define LCD_Off&t;&t;&t;2
DECL|macro|LCD_Clear
mdefine_line|#define LCD_Clear&t;&t;3
DECL|macro|LCD_Reset
mdefine_line|#define LCD_Reset&t;&t;4
DECL|macro|LCD_Cursor_Left
mdefine_line|#define LCD_Cursor_Left&t;&t;5
DECL|macro|LCD_Cursor_Right
mdefine_line|#define LCD_Cursor_Right&t;6
DECL|macro|LCD_Disp_Left
mdefine_line|#define LCD_Disp_Left&t;&t;7
DECL|macro|LCD_Disp_Right
mdefine_line|#define LCD_Disp_Right&t;&t;8
DECL|macro|LCD_Get_Cursor
mdefine_line|#define LCD_Get_Cursor&t;&t;9
DECL|macro|LCD_Set_Cursor
mdefine_line|#define LCD_Set_Cursor&t;&t;10
DECL|macro|LCD_Home
mdefine_line|#define LCD_Home&t;&t;11
DECL|macro|LCD_Read
mdefine_line|#define LCD_Read&t;&t;12
DECL|macro|LCD_Write
mdefine_line|#define LCD_Write&t;&t;13
DECL|macro|LCD_Cursor_Off
mdefine_line|#define LCD_Cursor_Off&t;&t;14
DECL|macro|LCD_Cursor_On
mdefine_line|#define LCD_Cursor_On&t;&t;15
DECL|macro|LCD_Get_Cursor_Pos
mdefine_line|#define LCD_Get_Cursor_Pos&t;16
DECL|macro|LCD_Set_Cursor_Pos
mdefine_line|#define LCD_Set_Cursor_Pos&t;17
DECL|macro|LCD_Blink_Off
mdefine_line|#define LCD_Blink_Off           18
DECL|macro|LED_Set
mdefine_line|#define LED_Set&t;&t;&t;40
DECL|macro|LED_Bit_Set
mdefine_line|#define LED_Bit_Set&t;&t;41
DECL|macro|LED_Bit_Clear
mdefine_line|#define LED_Bit_Clear&t;&t;42
singleline_comment|//  Button defs
DECL|macro|BUTTON_Read
mdefine_line|#define BUTTON_Read             50
singleline_comment|//  Flash command codes
DECL|macro|FLASH_Erase
mdefine_line|#define FLASH_Erase&t;&t;60
DECL|macro|FLASH_Burn
mdefine_line|#define FLASH_Burn&t;&t;61
DECL|macro|FLASH_Read
mdefine_line|#define FLASH_Read&t;&t;62
singleline_comment|// Ethernet LINK check hackaroo
DECL|macro|LINK_Check
mdefine_line|#define LINK_Check              90
DECL|macro|LINK_Check_2
mdefine_line|#define LINK_Check_2&t;&t;91
singleline_comment|//  Button patterns  _B - single layer lcd boards
DECL|macro|BUTTON_NONE
mdefine_line|#define BUTTON_NONE               0x3F
DECL|macro|BUTTON_NONE_B
mdefine_line|#define BUTTON_NONE_B             0xFE
DECL|macro|BUTTON_Left
mdefine_line|#define BUTTON_Left               0x3B
DECL|macro|BUTTON_Left_B
mdefine_line|#define BUTTON_Left_B             0xFA
DECL|macro|BUTTON_Right
mdefine_line|#define BUTTON_Right              0x37
DECL|macro|BUTTON_Right_B
mdefine_line|#define BUTTON_Right_B            0xDE
DECL|macro|BUTTON_Up
mdefine_line|#define BUTTON_Up                 0x2F
DECL|macro|BUTTON_Up_B
mdefine_line|#define BUTTON_Up_B               0xF6
DECL|macro|BUTTON_Down
mdefine_line|#define BUTTON_Down               0x1F
DECL|macro|BUTTON_Down_B
mdefine_line|#define BUTTON_Down_B             0xEE
DECL|macro|BUTTON_Next
mdefine_line|#define BUTTON_Next               0x3D
DECL|macro|BUTTON_Next_B
mdefine_line|#define BUTTON_Next_B             0x7E
DECL|macro|BUTTON_Enter
mdefine_line|#define BUTTON_Enter              0x3E
DECL|macro|BUTTON_Enter_B
mdefine_line|#define BUTTON_Enter_B            0xBE
DECL|macro|BUTTON_Reset_B
mdefine_line|#define BUTTON_Reset_B            0xFC
singleline_comment|// debounce constants
DECL|macro|BUTTON_SENSE
mdefine_line|#define BUTTON_SENSE            160000
DECL|macro|BUTTON_DEBOUNCE
mdefine_line|#define BUTTON_DEBOUNCE&t;&t;5000
singleline_comment|//  Galileo register stuff
DECL|macro|kGal_DevBank2Cfg
mdefine_line|#define kGal_DevBank2Cfg        0x1466DB33
DECL|macro|kGal_DevBank2PReg
mdefine_line|#define kGal_DevBank2PReg       0x464
DECL|macro|kGal_DevBank3Cfg
mdefine_line|#define kGal_DevBank3Cfg        0x146FDFFB
DECL|macro|kGal_DevBank3PReg
mdefine_line|#define kGal_DevBank3PReg       0x468
singleline_comment|// Network
DECL|macro|kIPADDR
mdefine_line|#define kIPADDR&t;&t;&t;1
DECL|macro|kNETMASK
mdefine_line|#define kNETMASK&t;&t;2
DECL|macro|kGATEWAY
mdefine_line|#define kGATEWAY&t;&t;3
DECL|macro|kDNS
mdefine_line|#define kDNS&t;&t;&t;4
DECL|macro|kClassA
mdefine_line|#define kClassA&t;&t;&t;5
DECL|macro|kClassB
mdefine_line|#define kClassB&t;&t;&t;6
DECL|macro|kClassC
mdefine_line|#define kClassC&t;&t;&t;7
eof
