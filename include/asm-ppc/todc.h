multiline_comment|/*&n; * include/asm-ppc/todc.h&n; *&n; * Definitions for the M48Txx and mc146818 series of Time of day/Real Time&n; * Clock chips.&n; *&n; * Author: Mark A. Greer&n; *         mgreer@mvista.com&n; *&n; * 2001 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
multiline_comment|/*&n; * Support for the M48T37/M48T59/.../mc146818 Real Time Clock chips.&n; * Purpose is to make one generic file that handles all of these chips instead&n; * of every platform implementing the same code over &amp; over again.&n; */
macro_line|#ifndef __PPC_KERNEL_TODC_H
DECL|macro|__PPC_KERNEL_TODC_H
mdefine_line|#define __PPC_KERNEL_TODC_H
r_typedef
r_struct
(brace
DECL|member|rtc_type
id|uint
id|rtc_type
suffix:semicolon
multiline_comment|/* your particular chip */
multiline_comment|/*&n;&t; * Following are the addresses of the AS0, AS1, and DATA registers&n;&t; * of these chips.  Note that these are board-specific.&n;&t; */
DECL|member|nvram_as0
r_int
r_int
id|nvram_as0
suffix:semicolon
DECL|member|nvram_as1
r_int
r_int
id|nvram_as1
suffix:semicolon
DECL|member|nvram_data
r_int
r_int
id|nvram_data
suffix:semicolon
multiline_comment|/*&n;&t; * Define bits to stop external set of regs from changing so&n;&t; * the chip can be read/written reliably.&n;&t; */
DECL|member|enable_read
r_int
r_char
id|enable_read
suffix:semicolon
DECL|member|enable_write
r_int
r_char
id|enable_write
suffix:semicolon
multiline_comment|/*&n;&t; * Following is the number of AS0 address bits.  This is normally&n;&t; * 8 but some bad hardware routes address lines incorrectly.&n;&t; */
DECL|member|as0_bits
r_int
id|as0_bits
suffix:semicolon
DECL|member|nvram_size
r_int
id|nvram_size
suffix:semicolon
multiline_comment|/* Size of NVRAM on chip */
DECL|member|sw_flags
r_int
id|sw_flags
suffix:semicolon
multiline_comment|/* Software control flags */
multiline_comment|/* Following are the register offsets for the particular chip */
DECL|member|year
r_int
id|year
suffix:semicolon
DECL|member|month
r_int
id|month
suffix:semicolon
DECL|member|day_of_month
r_int
id|day_of_month
suffix:semicolon
DECL|member|day_of_week
r_int
id|day_of_week
suffix:semicolon
DECL|member|hours
r_int
id|hours
suffix:semicolon
DECL|member|minutes
r_int
id|minutes
suffix:semicolon
DECL|member|seconds
r_int
id|seconds
suffix:semicolon
DECL|member|control_b
r_int
id|control_b
suffix:semicolon
DECL|member|control_a
r_int
id|control_a
suffix:semicolon
DECL|member|watchdog
r_int
id|watchdog
suffix:semicolon
DECL|member|interrupts
r_int
id|interrupts
suffix:semicolon
DECL|member|alarm_date
r_int
id|alarm_date
suffix:semicolon
DECL|member|alarm_hour
r_int
id|alarm_hour
suffix:semicolon
DECL|member|alarm_minutes
r_int
id|alarm_minutes
suffix:semicolon
DECL|member|alarm_seconds
r_int
id|alarm_seconds
suffix:semicolon
DECL|member|century
r_int
id|century
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n;&t; * Some RTC chips have their NVRAM buried behind a addr/data pair of&n;&t; * regs on the first level/clock registers.  The following fields&n;&t; * are the addresses for those addr/data regs.&n;&t; */
DECL|member|nvram_addr_reg
r_int
id|nvram_addr_reg
suffix:semicolon
DECL|member|nvram_data_reg
r_int
id|nvram_data_reg
suffix:semicolon
DECL|typedef|todc_info_t
)brace
id|todc_info_t
suffix:semicolon
multiline_comment|/*&n; * Define the types of TODC/RTC variants that are supported in&n; * arch/ppc/kernel/todc_time.c&n; * Make a new one of these for any chip somehow differs from what&squot;s already&n; * defined.  That way, if you ever need to put in code to touch those&n; * bits/registers in todc_time.c, you can put it inside an&n; * &squot;if (todc_info-&gt;rtc_type ==  TODC_TYPE_XXX)&squot; so you won&squot;t break&n; * anyone else.&n; */
DECL|macro|TODC_TYPE_MK48T35
mdefine_line|#define&t;TODC_TYPE_MK48T35&t;&t;1
DECL|macro|TODC_TYPE_MK48T37
mdefine_line|#define&t;TODC_TYPE_MK48T37&t;&t;2
DECL|macro|TODC_TYPE_MK48T59
mdefine_line|#define&t;TODC_TYPE_MK48T59&t;&t;3
DECL|macro|TODC_TYPE_DS1693
mdefine_line|#define&t;TODC_TYPE_DS1693&t;&t;4&t;/* Dallas DS1693 RTC */
DECL|macro|TODC_TYPE_DS1743
mdefine_line|#define&t;TODC_TYPE_DS1743&t;&t;5&t;/* Dallas DS1743 RTC */
DECL|macro|TODC_TYPE_DS1746
mdefine_line|#define&t;TODC_TYPE_DS1746&t;&t;6&t;/* Dallas DS1746 RTC */
DECL|macro|TODC_TYPE_DS1747
mdefine_line|#define&t;TODC_TYPE_DS1747&t;&t;7&t;/* Dallas DS1747 RTC */
DECL|macro|TODC_TYPE_DS1501
mdefine_line|#define&t;TODC_TYPE_DS1501&t;&t;8&t;/* Dallas DS1501 RTC */
DECL|macro|TODC_TYPE_DS1643
mdefine_line|#define TODC_TYPE_DS1643&t;&t;9&t;/* Dallas DS1643 RTC */
DECL|macro|TODC_TYPE_PC97307
mdefine_line|#define TODC_TYPE_PC97307&t;&t;10&t;/* PC97307 internal RTC */
DECL|macro|TODC_TYPE_DS1557
mdefine_line|#define TODC_TYPE_DS1557&t;&t;11&t;/* Dallas DS1557 RTC */
DECL|macro|TODC_TYPE_DS17285
mdefine_line|#define TODC_TYPE_DS17285&t;&t;12&t;/* Dallas DS17285 RTC */
DECL|macro|TODC_TYPE_DS1553
mdefine_line|#define TODC_TYPE_DS1553&t;&t;13&t;/* Dallas DS1553 RTC */
DECL|macro|TODC_TYPE_MC146818
mdefine_line|#define&t;TODC_TYPE_MC146818&t;&t;100&t;/* Leave room for m48txx&squot;s */
multiline_comment|/*&n; * Bit to clear/set to enable reads/writes to the chip&n; */
DECL|macro|TODC_MK48TXX_CNTL_A_R
mdefine_line|#define&t;TODC_MK48TXX_CNTL_A_R&t;&t;0x40
DECL|macro|TODC_MK48TXX_CNTL_A_W
mdefine_line|#define&t;TODC_MK48TXX_CNTL_A_W&t;&t;0x80
DECL|macro|TODC_MK48TXX_DAY_CB
mdefine_line|#define&t;TODC_MK48TXX_DAY_CB&t;&t;0x80
DECL|macro|TODC_DS1501_CNTL_B_TE
mdefine_line|#define&t;TODC_DS1501_CNTL_B_TE&t;&t;0x80
multiline_comment|/*&n; * Define flag bits used by todc routines.&n; */
DECL|macro|TODC_FLAG_2_LEVEL_NVRAM
mdefine_line|#define&t;TODC_FLAG_2_LEVEL_NVRAM&t;&t;0x00000001
multiline_comment|/*&n; * Define the values for the various RTC&squot;s that should to into the todc_info&n; * table.&n; * Note: The XXX_NVRAM_SIZE, XXX_NVRAM_ADDR_REG, and XXX_NVRAM_DATA_REG only&n; * matter if XXX_SW_FLAGS has TODC_FLAG_2_LEVEL_NVRAM set.&n; */
DECL|macro|TODC_TYPE_MK48T35_NVRAM_SIZE
mdefine_line|#define&t;TODC_TYPE_MK48T35_NVRAM_SIZE&t;&t;0x7ff8
DECL|macro|TODC_TYPE_MK48T35_SW_FLAGS
mdefine_line|#define&t;TODC_TYPE_MK48T35_SW_FLAGS&t;&t;0
DECL|macro|TODC_TYPE_MK48T35_YEAR
mdefine_line|#define&t;TODC_TYPE_MK48T35_YEAR&t;&t;&t;0x7fff
DECL|macro|TODC_TYPE_MK48T35_MONTH
mdefine_line|#define&t;TODC_TYPE_MK48T35_MONTH&t;&t;&t;0x7ffe
DECL|macro|TODC_TYPE_MK48T35_DOM
mdefine_line|#define&t;TODC_TYPE_MK48T35_DOM&t;&t;&t;0x7ffd&t;/* Day of Month */
DECL|macro|TODC_TYPE_MK48T35_DOW
mdefine_line|#define&t;TODC_TYPE_MK48T35_DOW&t;&t;&t;0x7ffc&t;/* Day of Week */
DECL|macro|TODC_TYPE_MK48T35_HOURS
mdefine_line|#define&t;TODC_TYPE_MK48T35_HOURS&t;&t;&t;0x7ffb
DECL|macro|TODC_TYPE_MK48T35_MINUTES
mdefine_line|#define&t;TODC_TYPE_MK48T35_MINUTES&t;&t;0x7ffa
DECL|macro|TODC_TYPE_MK48T35_SECONDS
mdefine_line|#define&t;TODC_TYPE_MK48T35_SECONDS&t;&t;0x7ff9
DECL|macro|TODC_TYPE_MK48T35_CNTL_B
mdefine_line|#define&t;TODC_TYPE_MK48T35_CNTL_B&t;&t;0x7ff9
DECL|macro|TODC_TYPE_MK48T35_CNTL_A
mdefine_line|#define&t;TODC_TYPE_MK48T35_CNTL_A&t;&t;0x7ff8
DECL|macro|TODC_TYPE_MK48T35_WATCHDOG
mdefine_line|#define&t;TODC_TYPE_MK48T35_WATCHDOG&t;&t;0x0000
DECL|macro|TODC_TYPE_MK48T35_INTERRUPTS
mdefine_line|#define&t;TODC_TYPE_MK48T35_INTERRUPTS&t;&t;0x0000
DECL|macro|TODC_TYPE_MK48T35_ALARM_DATE
mdefine_line|#define&t;TODC_TYPE_MK48T35_ALARM_DATE&t;&t;0x0000
DECL|macro|TODC_TYPE_MK48T35_ALARM_HOUR
mdefine_line|#define&t;TODC_TYPE_MK48T35_ALARM_HOUR&t;&t;0x0000
DECL|macro|TODC_TYPE_MK48T35_ALARM_MINUTES
mdefine_line|#define&t;TODC_TYPE_MK48T35_ALARM_MINUTES&t;&t;0x0000
DECL|macro|TODC_TYPE_MK48T35_ALARM_SECONDS
mdefine_line|#define&t;TODC_TYPE_MK48T35_ALARM_SECONDS&t;&t;0x0000
DECL|macro|TODC_TYPE_MK48T35_CENTURY
mdefine_line|#define&t;TODC_TYPE_MK48T35_CENTURY&t;&t;0x0000
DECL|macro|TODC_TYPE_MK48T35_FLAGS
mdefine_line|#define&t;TODC_TYPE_MK48T35_FLAGS&t;&t;&t;0x0000
DECL|macro|TODC_TYPE_MK48T35_NVRAM_ADDR_REG
mdefine_line|#define&t;TODC_TYPE_MK48T35_NVRAM_ADDR_REG&t;0
DECL|macro|TODC_TYPE_MK48T35_NVRAM_DATA_REG
mdefine_line|#define&t;TODC_TYPE_MK48T35_NVRAM_DATA_REG&t;0
DECL|macro|TODC_TYPE_MK48T37_NVRAM_SIZE
mdefine_line|#define&t;TODC_TYPE_MK48T37_NVRAM_SIZE&t;&t;0x7ff0
DECL|macro|TODC_TYPE_MK48T37_SW_FLAGS
mdefine_line|#define&t;TODC_TYPE_MK48T37_SW_FLAGS&t;&t;0
DECL|macro|TODC_TYPE_MK48T37_YEAR
mdefine_line|#define&t;TODC_TYPE_MK48T37_YEAR&t;&t;&t;0x7fff
DECL|macro|TODC_TYPE_MK48T37_MONTH
mdefine_line|#define&t;TODC_TYPE_MK48T37_MONTH&t;&t;&t;0x7ffe
DECL|macro|TODC_TYPE_MK48T37_DOM
mdefine_line|#define&t;TODC_TYPE_MK48T37_DOM&t;&t;&t;0x7ffd&t;/* Day of Month */
DECL|macro|TODC_TYPE_MK48T37_DOW
mdefine_line|#define&t;TODC_TYPE_MK48T37_DOW&t;&t;&t;0x7ffc&t;/* Day of Week */
DECL|macro|TODC_TYPE_MK48T37_HOURS
mdefine_line|#define&t;TODC_TYPE_MK48T37_HOURS&t;&t;&t;0x7ffb
DECL|macro|TODC_TYPE_MK48T37_MINUTES
mdefine_line|#define&t;TODC_TYPE_MK48T37_MINUTES&t;&t;0x7ffa
DECL|macro|TODC_TYPE_MK48T37_SECONDS
mdefine_line|#define&t;TODC_TYPE_MK48T37_SECONDS&t;&t;0x7ff9
DECL|macro|TODC_TYPE_MK48T37_CNTL_B
mdefine_line|#define&t;TODC_TYPE_MK48T37_CNTL_B&t;&t;0x7ff9
DECL|macro|TODC_TYPE_MK48T37_CNTL_A
mdefine_line|#define&t;TODC_TYPE_MK48T37_CNTL_A&t;&t;0x7ff8
DECL|macro|TODC_TYPE_MK48T37_WATCHDOG
mdefine_line|#define&t;TODC_TYPE_MK48T37_WATCHDOG&t;&t;0x7ff7
DECL|macro|TODC_TYPE_MK48T37_INTERRUPTS
mdefine_line|#define&t;TODC_TYPE_MK48T37_INTERRUPTS&t;&t;0x7ff6
DECL|macro|TODC_TYPE_MK48T37_ALARM_DATE
mdefine_line|#define&t;TODC_TYPE_MK48T37_ALARM_DATE&t;&t;0x7ff5
DECL|macro|TODC_TYPE_MK48T37_ALARM_HOUR
mdefine_line|#define&t;TODC_TYPE_MK48T37_ALARM_HOUR&t;&t;0x7ff4
DECL|macro|TODC_TYPE_MK48T37_ALARM_MINUTES
mdefine_line|#define&t;TODC_TYPE_MK48T37_ALARM_MINUTES&t;&t;0x7ff3
DECL|macro|TODC_TYPE_MK48T37_ALARM_SECONDS
mdefine_line|#define&t;TODC_TYPE_MK48T37_ALARM_SECONDS&t;&t;0x7ff2
DECL|macro|TODC_TYPE_MK48T37_CENTURY
mdefine_line|#define&t;TODC_TYPE_MK48T37_CENTURY&t;&t;0x7ff1
DECL|macro|TODC_TYPE_MK48T37_FLAGS
mdefine_line|#define&t;TODC_TYPE_MK48T37_FLAGS&t;&t;&t;0x7ff0
DECL|macro|TODC_TYPE_MK48T37_NVRAM_ADDR_REG
mdefine_line|#define&t;TODC_TYPE_MK48T37_NVRAM_ADDR_REG&t;0
DECL|macro|TODC_TYPE_MK48T37_NVRAM_DATA_REG
mdefine_line|#define&t;TODC_TYPE_MK48T37_NVRAM_DATA_REG&t;0
DECL|macro|TODC_TYPE_MK48T59_NVRAM_SIZE
mdefine_line|#define&t;TODC_TYPE_MK48T59_NVRAM_SIZE&t;&t;0x1ff0
DECL|macro|TODC_TYPE_MK48T59_SW_FLAGS
mdefine_line|#define&t;TODC_TYPE_MK48T59_SW_FLAGS&t;&t;0
DECL|macro|TODC_TYPE_MK48T59_YEAR
mdefine_line|#define&t;TODC_TYPE_MK48T59_YEAR&t;&t;&t;0x1fff
DECL|macro|TODC_TYPE_MK48T59_MONTH
mdefine_line|#define&t;TODC_TYPE_MK48T59_MONTH&t;&t;&t;0x1ffe
DECL|macro|TODC_TYPE_MK48T59_DOM
mdefine_line|#define&t;TODC_TYPE_MK48T59_DOM&t;&t;&t;0x1ffd&t;/* Day of Month */
DECL|macro|TODC_TYPE_MK48T59_DOW
mdefine_line|#define&t;TODC_TYPE_MK48T59_DOW&t;&t;&t;0x1ffc&t;/* Day of Week */
DECL|macro|TODC_TYPE_MK48T59_HOURS
mdefine_line|#define&t;TODC_TYPE_MK48T59_HOURS&t;&t;&t;0x1ffb
DECL|macro|TODC_TYPE_MK48T59_MINUTES
mdefine_line|#define&t;TODC_TYPE_MK48T59_MINUTES&t;&t;0x1ffa
DECL|macro|TODC_TYPE_MK48T59_SECONDS
mdefine_line|#define&t;TODC_TYPE_MK48T59_SECONDS&t;&t;0x1ff9
DECL|macro|TODC_TYPE_MK48T59_CNTL_B
mdefine_line|#define&t;TODC_TYPE_MK48T59_CNTL_B&t;&t;0x1ff9
DECL|macro|TODC_TYPE_MK48T59_CNTL_A
mdefine_line|#define&t;TODC_TYPE_MK48T59_CNTL_A&t;&t;0x1ff8
DECL|macro|TODC_TYPE_MK48T59_WATCHDOG
mdefine_line|#define&t;TODC_TYPE_MK48T59_WATCHDOG&t;&t;0x1fff
DECL|macro|TODC_TYPE_MK48T59_INTERRUPTS
mdefine_line|#define&t;TODC_TYPE_MK48T59_INTERRUPTS&t;&t;0x1fff
DECL|macro|TODC_TYPE_MK48T59_ALARM_DATE
mdefine_line|#define&t;TODC_TYPE_MK48T59_ALARM_DATE&t;&t;0x1fff
DECL|macro|TODC_TYPE_MK48T59_ALARM_HOUR
mdefine_line|#define&t;TODC_TYPE_MK48T59_ALARM_HOUR&t;&t;0x1fff
DECL|macro|TODC_TYPE_MK48T59_ALARM_MINUTES
mdefine_line|#define&t;TODC_TYPE_MK48T59_ALARM_MINUTES&t;&t;0x1fff
DECL|macro|TODC_TYPE_MK48T59_ALARM_SECONDS
mdefine_line|#define&t;TODC_TYPE_MK48T59_ALARM_SECONDS&t;&t;0x1fff
DECL|macro|TODC_TYPE_MK48T59_CENTURY
mdefine_line|#define&t;TODC_TYPE_MK48T59_CENTURY&t;&t;0x1fff
DECL|macro|TODC_TYPE_MK48T59_FLAGS
mdefine_line|#define&t;TODC_TYPE_MK48T59_FLAGS&t;&t;&t;0x1fff
DECL|macro|TODC_TYPE_MK48T59_NVRAM_ADDR_REG
mdefine_line|#define&t;TODC_TYPE_MK48T59_NVRAM_ADDR_REG&t;0
DECL|macro|TODC_TYPE_MK48T59_NVRAM_DATA_REG
mdefine_line|#define&t;TODC_TYPE_MK48T59_NVRAM_DATA_REG&t;0
DECL|macro|TODC_TYPE_DS1501_NVRAM_SIZE
mdefine_line|#define&t;TODC_TYPE_DS1501_NVRAM_SIZE&t;0x100
DECL|macro|TODC_TYPE_DS1501_SW_FLAGS
mdefine_line|#define&t;TODC_TYPE_DS1501_SW_FLAGS&t;TODC_FLAG_2_LEVEL_NVRAM
DECL|macro|TODC_TYPE_DS1501_YEAR
mdefine_line|#define&t;TODC_TYPE_DS1501_YEAR&t;&t;(TODC_TYPE_DS1501_NVRAM_SIZE + 0x06)
DECL|macro|TODC_TYPE_DS1501_MONTH
mdefine_line|#define&t;TODC_TYPE_DS1501_MONTH&t;&t;(TODC_TYPE_DS1501_NVRAM_SIZE + 0x05)
DECL|macro|TODC_TYPE_DS1501_DOM
mdefine_line|#define&t;TODC_TYPE_DS1501_DOM&t;&t;(TODC_TYPE_DS1501_NVRAM_SIZE + 0x04)
DECL|macro|TODC_TYPE_DS1501_DOW
mdefine_line|#define&t;TODC_TYPE_DS1501_DOW&t;&t;(TODC_TYPE_DS1501_NVRAM_SIZE + 0x03)
DECL|macro|TODC_TYPE_DS1501_HOURS
mdefine_line|#define&t;TODC_TYPE_DS1501_HOURS&t;&t;(TODC_TYPE_DS1501_NVRAM_SIZE + 0x02)
DECL|macro|TODC_TYPE_DS1501_MINUTES
mdefine_line|#define&t;TODC_TYPE_DS1501_MINUTES&t;(TODC_TYPE_DS1501_NVRAM_SIZE + 0x01)
DECL|macro|TODC_TYPE_DS1501_SECONDS
mdefine_line|#define&t;TODC_TYPE_DS1501_SECONDS&t;(TODC_TYPE_DS1501_NVRAM_SIZE + 0x00)
DECL|macro|TODC_TYPE_DS1501_CNTL_B
mdefine_line|#define&t;TODC_TYPE_DS1501_CNTL_B&t;&t;(TODC_TYPE_DS1501_NVRAM_SIZE + 0x0f)
DECL|macro|TODC_TYPE_DS1501_CNTL_A
mdefine_line|#define&t;TODC_TYPE_DS1501_CNTL_A&t;&t;(TODC_TYPE_DS1501_NVRAM_SIZE + 0x0f)
DECL|macro|TODC_TYPE_DS1501_WATCHDOG
mdefine_line|#define&t;TODC_TYPE_DS1501_WATCHDOG&t;(TODC_TYPE_DS1501_NVRAM_SIZE + 0xff)
DECL|macro|TODC_TYPE_DS1501_INTERRUPTS
mdefine_line|#define&t;TODC_TYPE_DS1501_INTERRUPTS&t;(TODC_TYPE_DS1501_NVRAM_SIZE + 0xff)
DECL|macro|TODC_TYPE_DS1501_ALARM_DATE
mdefine_line|#define&t;TODC_TYPE_DS1501_ALARM_DATE&t;(TODC_TYPE_DS1501_NVRAM_SIZE + 0x0b)
DECL|macro|TODC_TYPE_DS1501_ALARM_HOUR
mdefine_line|#define&t;TODC_TYPE_DS1501_ALARM_HOUR&t;(TODC_TYPE_DS1501_NVRAM_SIZE + 0x0a)
DECL|macro|TODC_TYPE_DS1501_ALARM_MINUTES
mdefine_line|#define&t;TODC_TYPE_DS1501_ALARM_MINUTES&t;(TODC_TYPE_DS1501_NVRAM_SIZE + 0x09)
DECL|macro|TODC_TYPE_DS1501_ALARM_SECONDS
mdefine_line|#define&t;TODC_TYPE_DS1501_ALARM_SECONDS&t;(TODC_TYPE_DS1501_NVRAM_SIZE + 0x08)
DECL|macro|TODC_TYPE_DS1501_CENTURY
mdefine_line|#define&t;TODC_TYPE_DS1501_CENTURY&t;(TODC_TYPE_DS1501_NVRAM_SIZE + 0x07)
DECL|macro|TODC_TYPE_DS1501_FLAGS
mdefine_line|#define&t;TODC_TYPE_DS1501_FLAGS&t;&t;(TODC_TYPE_DS1501_NVRAM_SIZE + 0xff)
DECL|macro|TODC_TYPE_DS1501_NVRAM_ADDR_REG
mdefine_line|#define&t;TODC_TYPE_DS1501_NVRAM_ADDR_REG&t;0x10
DECL|macro|TODC_TYPE_DS1501_NVRAM_DATA_REG
mdefine_line|#define&t;TODC_TYPE_DS1501_NVRAM_DATA_REG&t;0x13
DECL|macro|TODC_TYPE_DS1553_NVRAM_SIZE
mdefine_line|#define&t;TODC_TYPE_DS1553_NVRAM_SIZE&t;&t;0x1ff0
DECL|macro|TODC_TYPE_DS1553_SW_FLAGS
mdefine_line|#define&t;TODC_TYPE_DS1553_SW_FLAGS&t;&t;0
DECL|macro|TODC_TYPE_DS1553_YEAR
mdefine_line|#define&t;TODC_TYPE_DS1553_YEAR&t;&t;&t;0x1fff
DECL|macro|TODC_TYPE_DS1553_MONTH
mdefine_line|#define&t;TODC_TYPE_DS1553_MONTH&t;&t;&t;0x1ffe
DECL|macro|TODC_TYPE_DS1553_DOM
mdefine_line|#define&t;TODC_TYPE_DS1553_DOM&t;&t;&t;0x1ffd&t;/* Day of Month */
DECL|macro|TODC_TYPE_DS1553_DOW
mdefine_line|#define&t;TODC_TYPE_DS1553_DOW&t;&t;&t;0x1ffc&t;/* Day of Week */
DECL|macro|TODC_TYPE_DS1553_HOURS
mdefine_line|#define&t;TODC_TYPE_DS1553_HOURS&t;&t;&t;0x1ffb
DECL|macro|TODC_TYPE_DS1553_MINUTES
mdefine_line|#define&t;TODC_TYPE_DS1553_MINUTES&t;&t;0x1ffa
DECL|macro|TODC_TYPE_DS1553_SECONDS
mdefine_line|#define&t;TODC_TYPE_DS1553_SECONDS&t;&t;0x1ff9
DECL|macro|TODC_TYPE_DS1553_CNTL_B
mdefine_line|#define&t;TODC_TYPE_DS1553_CNTL_B&t;&t;&t;0x1ff9
DECL|macro|TODC_TYPE_DS1553_CNTL_A
mdefine_line|#define&t;TODC_TYPE_DS1553_CNTL_A&t;&t;&t;0x1ff8&t;/* control_a R/W regs */
DECL|macro|TODC_TYPE_DS1553_WATCHDOG
mdefine_line|#define&t;TODC_TYPE_DS1553_WATCHDOG&t;&t;0x1ff7
DECL|macro|TODC_TYPE_DS1553_INTERRUPTS
mdefine_line|#define&t;TODC_TYPE_DS1553_INTERRUPTS&t;&t;0x1ff6
DECL|macro|TODC_TYPE_DS1553_ALARM_DATE
mdefine_line|#define&t;TODC_TYPE_DS1553_ALARM_DATE&t;&t;0x1ff5
DECL|macro|TODC_TYPE_DS1553_ALARM_HOUR
mdefine_line|#define&t;TODC_TYPE_DS1553_ALARM_HOUR&t;&t;0x1ff4
DECL|macro|TODC_TYPE_DS1553_ALARM_MINUTES
mdefine_line|#define&t;TODC_TYPE_DS1553_ALARM_MINUTES&t;&t;0x1ff3
DECL|macro|TODC_TYPE_DS1553_ALARM_SECONDS
mdefine_line|#define&t;TODC_TYPE_DS1553_ALARM_SECONDS&t;&t;0x1ff2
DECL|macro|TODC_TYPE_DS1553_CENTURY
mdefine_line|#define&t;TODC_TYPE_DS1553_CENTURY&t;&t;0x1ff8
DECL|macro|TODC_TYPE_DS1553_FLAGS
mdefine_line|#define&t;TODC_TYPE_DS1553_FLAGS&t;&t;&t;0x1ff0
DECL|macro|TODC_TYPE_DS1553_NVRAM_ADDR_REG
mdefine_line|#define&t;TODC_TYPE_DS1553_NVRAM_ADDR_REG&t;&t;0
DECL|macro|TODC_TYPE_DS1553_NVRAM_DATA_REG
mdefine_line|#define&t;TODC_TYPE_DS1553_NVRAM_DATA_REG&t;&t;0
DECL|macro|TODC_TYPE_DS1557_NVRAM_SIZE
mdefine_line|#define&t;TODC_TYPE_DS1557_NVRAM_SIZE&t;&t;0x7fff0
DECL|macro|TODC_TYPE_DS1557_SW_FLAGS
mdefine_line|#define&t;TODC_TYPE_DS1557_SW_FLAGS&t;&t;0
DECL|macro|TODC_TYPE_DS1557_YEAR
mdefine_line|#define&t;TODC_TYPE_DS1557_YEAR&t;&t;&t;0x7ffff
DECL|macro|TODC_TYPE_DS1557_MONTH
mdefine_line|#define&t;TODC_TYPE_DS1557_MONTH&t;&t;&t;0x7fffe
DECL|macro|TODC_TYPE_DS1557_DOM
mdefine_line|#define&t;TODC_TYPE_DS1557_DOM&t;&t;&t;0x7fffd&t;/* Day of Month */
DECL|macro|TODC_TYPE_DS1557_DOW
mdefine_line|#define&t;TODC_TYPE_DS1557_DOW&t;&t;&t;0x7fffc&t;/* Day of Week */
DECL|macro|TODC_TYPE_DS1557_HOURS
mdefine_line|#define&t;TODC_TYPE_DS1557_HOURS&t;&t;&t;0x7fffb
DECL|macro|TODC_TYPE_DS1557_MINUTES
mdefine_line|#define&t;TODC_TYPE_DS1557_MINUTES&t;&t;0x7fffa
DECL|macro|TODC_TYPE_DS1557_SECONDS
mdefine_line|#define&t;TODC_TYPE_DS1557_SECONDS&t;&t;0x7fff9
DECL|macro|TODC_TYPE_DS1557_CNTL_B
mdefine_line|#define&t;TODC_TYPE_DS1557_CNTL_B&t;&t;&t;0x7fff9
DECL|macro|TODC_TYPE_DS1557_CNTL_A
mdefine_line|#define&t;TODC_TYPE_DS1557_CNTL_A&t;&t;&t;0x7fff8&t;/* control_a R/W regs */
DECL|macro|TODC_TYPE_DS1557_WATCHDOG
mdefine_line|#define&t;TODC_TYPE_DS1557_WATCHDOG&t;&t;0x7fff7
DECL|macro|TODC_TYPE_DS1557_INTERRUPTS
mdefine_line|#define&t;TODC_TYPE_DS1557_INTERRUPTS&t;&t;0x7fff6
DECL|macro|TODC_TYPE_DS1557_ALARM_DATE
mdefine_line|#define&t;TODC_TYPE_DS1557_ALARM_DATE&t;&t;0x7fff5
DECL|macro|TODC_TYPE_DS1557_ALARM_HOUR
mdefine_line|#define&t;TODC_TYPE_DS1557_ALARM_HOUR&t;&t;0x7fff4
DECL|macro|TODC_TYPE_DS1557_ALARM_MINUTES
mdefine_line|#define&t;TODC_TYPE_DS1557_ALARM_MINUTES&t;&t;0x7fff3
DECL|macro|TODC_TYPE_DS1557_ALARM_SECONDS
mdefine_line|#define&t;TODC_TYPE_DS1557_ALARM_SECONDS&t;&t;0x7fff2
DECL|macro|TODC_TYPE_DS1557_CENTURY
mdefine_line|#define&t;TODC_TYPE_DS1557_CENTURY&t;&t;0x7fff8
DECL|macro|TODC_TYPE_DS1557_FLAGS
mdefine_line|#define&t;TODC_TYPE_DS1557_FLAGS&t;&t;&t;0x7fff0
DECL|macro|TODC_TYPE_DS1557_NVRAM_ADDR_REG
mdefine_line|#define&t;TODC_TYPE_DS1557_NVRAM_ADDR_REG&t;&t;0
DECL|macro|TODC_TYPE_DS1557_NVRAM_DATA_REG
mdefine_line|#define&t;TODC_TYPE_DS1557_NVRAM_DATA_REG&t;&t;0
DECL|macro|TODC_TYPE_DS1643_NVRAM_SIZE
mdefine_line|#define&t;TODC_TYPE_DS1643_NVRAM_SIZE&t;&t;0x1ff8
DECL|macro|TODC_TYPE_DS1643_SW_FLAGS
mdefine_line|#define&t;TODC_TYPE_DS1643_SW_FLAGS&t;&t;0
DECL|macro|TODC_TYPE_DS1643_YEAR
mdefine_line|#define&t;TODC_TYPE_DS1643_YEAR&t;&t;&t;0x1fff
DECL|macro|TODC_TYPE_DS1643_MONTH
mdefine_line|#define&t;TODC_TYPE_DS1643_MONTH&t;&t;&t;0x1ffe
DECL|macro|TODC_TYPE_DS1643_DOM
mdefine_line|#define&t;TODC_TYPE_DS1643_DOM&t;&t;&t;0x1ffd&t;/* Day of Month */
DECL|macro|TODC_TYPE_DS1643_DOW
mdefine_line|#define&t;TODC_TYPE_DS1643_DOW&t;&t;&t;0x1ffc&t;/* Day of Week */
DECL|macro|TODC_TYPE_DS1643_HOURS
mdefine_line|#define&t;TODC_TYPE_DS1643_HOURS&t;&t;&t;0x1ffb
DECL|macro|TODC_TYPE_DS1643_MINUTES
mdefine_line|#define&t;TODC_TYPE_DS1643_MINUTES&t;&t;0x1ffa
DECL|macro|TODC_TYPE_DS1643_SECONDS
mdefine_line|#define&t;TODC_TYPE_DS1643_SECONDS&t;&t;0x1ff9
DECL|macro|TODC_TYPE_DS1643_CNTL_B
mdefine_line|#define&t;TODC_TYPE_DS1643_CNTL_B&t;&t;&t;0x1ff9
DECL|macro|TODC_TYPE_DS1643_CNTL_A
mdefine_line|#define&t;TODC_TYPE_DS1643_CNTL_A&t;&t;&t;0x1ff8&t;/* control_a R/W regs */
DECL|macro|TODC_TYPE_DS1643_WATCHDOG
mdefine_line|#define&t;TODC_TYPE_DS1643_WATCHDOG&t;&t;0x1fff
DECL|macro|TODC_TYPE_DS1643_INTERRUPTS
mdefine_line|#define&t;TODC_TYPE_DS1643_INTERRUPTS&t;&t;0x1fff
DECL|macro|TODC_TYPE_DS1643_ALARM_DATE
mdefine_line|#define&t;TODC_TYPE_DS1643_ALARM_DATE&t;&t;0x1fff
DECL|macro|TODC_TYPE_DS1643_ALARM_HOUR
mdefine_line|#define&t;TODC_TYPE_DS1643_ALARM_HOUR&t;&t;0x1fff
DECL|macro|TODC_TYPE_DS1643_ALARM_MINUTES
mdefine_line|#define&t;TODC_TYPE_DS1643_ALARM_MINUTES&t;&t;0x1fff
DECL|macro|TODC_TYPE_DS1643_ALARM_SECONDS
mdefine_line|#define&t;TODC_TYPE_DS1643_ALARM_SECONDS&t;&t;0x1fff
DECL|macro|TODC_TYPE_DS1643_CENTURY
mdefine_line|#define&t;TODC_TYPE_DS1643_CENTURY&t;&t;0x1ff8
DECL|macro|TODC_TYPE_DS1643_FLAGS
mdefine_line|#define&t;TODC_TYPE_DS1643_FLAGS&t;&t;&t;0x1fff
DECL|macro|TODC_TYPE_DS1643_NVRAM_ADDR_REG
mdefine_line|#define&t;TODC_TYPE_DS1643_NVRAM_ADDR_REG&t;&t;0
DECL|macro|TODC_TYPE_DS1643_NVRAM_DATA_REG
mdefine_line|#define&t;TODC_TYPE_DS1643_NVRAM_DATA_REG&t;&t;0
DECL|macro|TODC_TYPE_DS1693_NVRAM_SIZE
mdefine_line|#define&t;TODC_TYPE_DS1693_NVRAM_SIZE&t;&t;0 /* Not handled yet */
DECL|macro|TODC_TYPE_DS1693_SW_FLAGS
mdefine_line|#define&t;TODC_TYPE_DS1693_SW_FLAGS&t;&t;0
DECL|macro|TODC_TYPE_DS1693_YEAR
mdefine_line|#define&t;TODC_TYPE_DS1693_YEAR&t;&t;&t;0x09
DECL|macro|TODC_TYPE_DS1693_MONTH
mdefine_line|#define&t;TODC_TYPE_DS1693_MONTH&t;&t;&t;0x08
DECL|macro|TODC_TYPE_DS1693_DOM
mdefine_line|#define&t;TODC_TYPE_DS1693_DOM&t;&t;&t;0x07&t;/* Day of Month */
DECL|macro|TODC_TYPE_DS1693_DOW
mdefine_line|#define&t;TODC_TYPE_DS1693_DOW&t;&t;&t;0x06&t;/* Day of Week */
DECL|macro|TODC_TYPE_DS1693_HOURS
mdefine_line|#define&t;TODC_TYPE_DS1693_HOURS&t;&t;&t;0x04
DECL|macro|TODC_TYPE_DS1693_MINUTES
mdefine_line|#define&t;TODC_TYPE_DS1693_MINUTES&t;&t;0x02
DECL|macro|TODC_TYPE_DS1693_SECONDS
mdefine_line|#define&t;TODC_TYPE_DS1693_SECONDS&t;&t;0x00
DECL|macro|TODC_TYPE_DS1693_CNTL_B
mdefine_line|#define&t;TODC_TYPE_DS1693_CNTL_B&t;&t;&t;0x0b
DECL|macro|TODC_TYPE_DS1693_CNTL_A
mdefine_line|#define&t;TODC_TYPE_DS1693_CNTL_A&t;&t;&t;0x0a
DECL|macro|TODC_TYPE_DS1693_WATCHDOG
mdefine_line|#define&t;TODC_TYPE_DS1693_WATCHDOG&t;&t;0xff
DECL|macro|TODC_TYPE_DS1693_INTERRUPTS
mdefine_line|#define&t;TODC_TYPE_DS1693_INTERRUPTS&t;&t;0xff
DECL|macro|TODC_TYPE_DS1693_ALARM_DATE
mdefine_line|#define&t;TODC_TYPE_DS1693_ALARM_DATE&t;&t;0x49
DECL|macro|TODC_TYPE_DS1693_ALARM_HOUR
mdefine_line|#define&t;TODC_TYPE_DS1693_ALARM_HOUR&t;&t;0x05
DECL|macro|TODC_TYPE_DS1693_ALARM_MINUTES
mdefine_line|#define&t;TODC_TYPE_DS1693_ALARM_MINUTES&t;&t;0x03
DECL|macro|TODC_TYPE_DS1693_ALARM_SECONDS
mdefine_line|#define&t;TODC_TYPE_DS1693_ALARM_SECONDS&t;&t;0x01
DECL|macro|TODC_TYPE_DS1693_CENTURY
mdefine_line|#define&t;TODC_TYPE_DS1693_CENTURY&t;&t;0x48
DECL|macro|TODC_TYPE_DS1693_FLAGS
mdefine_line|#define&t;TODC_TYPE_DS1693_FLAGS&t;&t;&t;0xff
DECL|macro|TODC_TYPE_DS1693_NVRAM_ADDR_REG
mdefine_line|#define&t;TODC_TYPE_DS1693_NVRAM_ADDR_REG&t;&t;0
DECL|macro|TODC_TYPE_DS1693_NVRAM_DATA_REG
mdefine_line|#define&t;TODC_TYPE_DS1693_NVRAM_DATA_REG&t;&t;0
DECL|macro|TODC_TYPE_DS1743_NVRAM_SIZE
mdefine_line|#define&t;TODC_TYPE_DS1743_NVRAM_SIZE&t;&t;0x1ff8
DECL|macro|TODC_TYPE_DS1743_SW_FLAGS
mdefine_line|#define&t;TODC_TYPE_DS1743_SW_FLAGS&t;&t;0
DECL|macro|TODC_TYPE_DS1743_YEAR
mdefine_line|#define&t;TODC_TYPE_DS1743_YEAR&t;&t;&t;0x1fff
DECL|macro|TODC_TYPE_DS1743_MONTH
mdefine_line|#define&t;TODC_TYPE_DS1743_MONTH&t;&t;&t;0x1ffe
DECL|macro|TODC_TYPE_DS1743_DOM
mdefine_line|#define&t;TODC_TYPE_DS1743_DOM&t;&t;&t;0x1ffd&t;/* Day of Month */
DECL|macro|TODC_TYPE_DS1743_DOW
mdefine_line|#define&t;TODC_TYPE_DS1743_DOW&t;&t;&t;0x1ffc&t;/* Day of Week */
DECL|macro|TODC_TYPE_DS1743_HOURS
mdefine_line|#define&t;TODC_TYPE_DS1743_HOURS&t;&t;&t;0x1ffb
DECL|macro|TODC_TYPE_DS1743_MINUTES
mdefine_line|#define&t;TODC_TYPE_DS1743_MINUTES&t;&t;0x1ffa
DECL|macro|TODC_TYPE_DS1743_SECONDS
mdefine_line|#define&t;TODC_TYPE_DS1743_SECONDS&t;&t;0x1ff9
DECL|macro|TODC_TYPE_DS1743_CNTL_B
mdefine_line|#define&t;TODC_TYPE_DS1743_CNTL_B&t;&t;&t;0x1ff9
DECL|macro|TODC_TYPE_DS1743_CNTL_A
mdefine_line|#define&t;TODC_TYPE_DS1743_CNTL_A&t;&t;&t;0x1ff8&t;/* control_a R/W regs */
DECL|macro|TODC_TYPE_DS1743_WATCHDOG
mdefine_line|#define&t;TODC_TYPE_DS1743_WATCHDOG&t;&t;0x1fff
DECL|macro|TODC_TYPE_DS1743_INTERRUPTS
mdefine_line|#define&t;TODC_TYPE_DS1743_INTERRUPTS&t;&t;0x1fff
DECL|macro|TODC_TYPE_DS1743_ALARM_DATE
mdefine_line|#define&t;TODC_TYPE_DS1743_ALARM_DATE&t;&t;0x1fff
DECL|macro|TODC_TYPE_DS1743_ALARM_HOUR
mdefine_line|#define&t;TODC_TYPE_DS1743_ALARM_HOUR&t;&t;0x1fff
DECL|macro|TODC_TYPE_DS1743_ALARM_MINUTES
mdefine_line|#define&t;TODC_TYPE_DS1743_ALARM_MINUTES&t;&t;0x1fff
DECL|macro|TODC_TYPE_DS1743_ALARM_SECONDS
mdefine_line|#define&t;TODC_TYPE_DS1743_ALARM_SECONDS&t;&t;0x1fff
DECL|macro|TODC_TYPE_DS1743_CENTURY
mdefine_line|#define&t;TODC_TYPE_DS1743_CENTURY&t;&t;0x1ff8
DECL|macro|TODC_TYPE_DS1743_FLAGS
mdefine_line|#define&t;TODC_TYPE_DS1743_FLAGS&t;&t;&t;0x1fff
DECL|macro|TODC_TYPE_DS1743_NVRAM_ADDR_REG
mdefine_line|#define&t;TODC_TYPE_DS1743_NVRAM_ADDR_REG&t;&t;0
DECL|macro|TODC_TYPE_DS1743_NVRAM_DATA_REG
mdefine_line|#define&t;TODC_TYPE_DS1743_NVRAM_DATA_REG&t;&t;0
DECL|macro|TODC_TYPE_DS1746_NVRAM_SIZE
mdefine_line|#define&t;TODC_TYPE_DS1746_NVRAM_SIZE&t;&t;0x1fff8
DECL|macro|TODC_TYPE_DS1746_SW_FLAGS
mdefine_line|#define&t;TODC_TYPE_DS1746_SW_FLAGS&t;&t;0
DECL|macro|TODC_TYPE_DS1746_YEAR
mdefine_line|#define&t;TODC_TYPE_DS1746_YEAR&t;&t;&t;0x1ffff
DECL|macro|TODC_TYPE_DS1746_MONTH
mdefine_line|#define&t;TODC_TYPE_DS1746_MONTH&t;&t;&t;0x1fffe
DECL|macro|TODC_TYPE_DS1746_DOM
mdefine_line|#define&t;TODC_TYPE_DS1746_DOM&t;&t;&t;0x1fffd&t;/* Day of Month */
DECL|macro|TODC_TYPE_DS1746_DOW
mdefine_line|#define&t;TODC_TYPE_DS1746_DOW&t;&t;&t;0x1fffc&t;/* Day of Week */
DECL|macro|TODC_TYPE_DS1746_HOURS
mdefine_line|#define&t;TODC_TYPE_DS1746_HOURS&t;&t;&t;0x1fffb
DECL|macro|TODC_TYPE_DS1746_MINUTES
mdefine_line|#define&t;TODC_TYPE_DS1746_MINUTES&t;&t;0x1fffa
DECL|macro|TODC_TYPE_DS1746_SECONDS
mdefine_line|#define&t;TODC_TYPE_DS1746_SECONDS&t;&t;0x1fff9
DECL|macro|TODC_TYPE_DS1746_CNTL_B
mdefine_line|#define&t;TODC_TYPE_DS1746_CNTL_B&t;&t;&t;0x1fff9
DECL|macro|TODC_TYPE_DS1746_CNTL_A
mdefine_line|#define&t;TODC_TYPE_DS1746_CNTL_A&t;&t;&t;0x1fff8&t;/* control_a R/W regs */
DECL|macro|TODC_TYPE_DS1746_WATCHDOG
mdefine_line|#define&t;TODC_TYPE_DS1746_WATCHDOG&t;&t;0x00000
DECL|macro|TODC_TYPE_DS1746_INTERRUPTS
mdefine_line|#define&t;TODC_TYPE_DS1746_INTERRUPTS&t;&t;0x00000
DECL|macro|TODC_TYPE_DS1746_ALARM_DATE
mdefine_line|#define&t;TODC_TYPE_DS1746_ALARM_DATE&t;&t;0x00000
DECL|macro|TODC_TYPE_DS1746_ALARM_HOUR
mdefine_line|#define&t;TODC_TYPE_DS1746_ALARM_HOUR&t;&t;0x00000
DECL|macro|TODC_TYPE_DS1746_ALARM_MINUTES
mdefine_line|#define&t;TODC_TYPE_DS1746_ALARM_MINUTES&t;&t;0x00000
DECL|macro|TODC_TYPE_DS1746_ALARM_SECONDS
mdefine_line|#define&t;TODC_TYPE_DS1746_ALARM_SECONDS&t;&t;0x00000
DECL|macro|TODC_TYPE_DS1746_CENTURY
mdefine_line|#define&t;TODC_TYPE_DS1746_CENTURY&t;&t;0x00000
DECL|macro|TODC_TYPE_DS1746_FLAGS
mdefine_line|#define&t;TODC_TYPE_DS1746_FLAGS&t;&t;&t;0x00000
DECL|macro|TODC_TYPE_DS1746_NVRAM_ADDR_REG
mdefine_line|#define&t;TODC_TYPE_DS1746_NVRAM_ADDR_REG&t;&t;0
DECL|macro|TODC_TYPE_DS1746_NVRAM_DATA_REG
mdefine_line|#define&t;TODC_TYPE_DS1746_NVRAM_DATA_REG&t;&t;0
DECL|macro|TODC_TYPE_DS1747_NVRAM_SIZE
mdefine_line|#define&t;TODC_TYPE_DS1747_NVRAM_SIZE&t;&t;0x7fff8
DECL|macro|TODC_TYPE_DS1747_SW_FLAGS
mdefine_line|#define&t;TODC_TYPE_DS1747_SW_FLAGS&t;&t;0
DECL|macro|TODC_TYPE_DS1747_YEAR
mdefine_line|#define&t;TODC_TYPE_DS1747_YEAR&t;&t;&t;0x7ffff
DECL|macro|TODC_TYPE_DS1747_MONTH
mdefine_line|#define&t;TODC_TYPE_DS1747_MONTH&t;&t;&t;0x7fffe
DECL|macro|TODC_TYPE_DS1747_DOM
mdefine_line|#define&t;TODC_TYPE_DS1747_DOM&t;&t;&t;0x7fffd&t;/* Day of Month */
DECL|macro|TODC_TYPE_DS1747_DOW
mdefine_line|#define&t;TODC_TYPE_DS1747_DOW&t;&t;&t;0x7fffc&t;/* Day of Week */
DECL|macro|TODC_TYPE_DS1747_HOURS
mdefine_line|#define&t;TODC_TYPE_DS1747_HOURS&t;&t;&t;0x7fffb
DECL|macro|TODC_TYPE_DS1747_MINUTES
mdefine_line|#define&t;TODC_TYPE_DS1747_MINUTES&t;&t;0x7fffa
DECL|macro|TODC_TYPE_DS1747_SECONDS
mdefine_line|#define&t;TODC_TYPE_DS1747_SECONDS&t;&t;0x7fff9
DECL|macro|TODC_TYPE_DS1747_CNTL_B
mdefine_line|#define&t;TODC_TYPE_DS1747_CNTL_B&t;&t;&t;0x7fff9
DECL|macro|TODC_TYPE_DS1747_CNTL_A
mdefine_line|#define&t;TODC_TYPE_DS1747_CNTL_A&t;&t;&t;0x7fff8&t;/* control_a R/W regs */
DECL|macro|TODC_TYPE_DS1747_WATCHDOG
mdefine_line|#define&t;TODC_TYPE_DS1747_WATCHDOG&t;&t;0x00000
DECL|macro|TODC_TYPE_DS1747_INTERRUPTS
mdefine_line|#define&t;TODC_TYPE_DS1747_INTERRUPTS&t;&t;0x00000
DECL|macro|TODC_TYPE_DS1747_ALARM_DATE
mdefine_line|#define&t;TODC_TYPE_DS1747_ALARM_DATE&t;&t;0x00000
DECL|macro|TODC_TYPE_DS1747_ALARM_HOUR
mdefine_line|#define&t;TODC_TYPE_DS1747_ALARM_HOUR&t;&t;0x00000
DECL|macro|TODC_TYPE_DS1747_ALARM_MINUTES
mdefine_line|#define&t;TODC_TYPE_DS1747_ALARM_MINUTES&t;&t;0x00000
DECL|macro|TODC_TYPE_DS1747_ALARM_SECONDS
mdefine_line|#define&t;TODC_TYPE_DS1747_ALARM_SECONDS&t;&t;0x00000
DECL|macro|TODC_TYPE_DS1747_CENTURY
mdefine_line|#define&t;TODC_TYPE_DS1747_CENTURY&t;&t;0x00000
DECL|macro|TODC_TYPE_DS1747_FLAGS
mdefine_line|#define&t;TODC_TYPE_DS1747_FLAGS&t;&t;&t;0x00000
DECL|macro|TODC_TYPE_DS1747_NVRAM_ADDR_REG
mdefine_line|#define&t;TODC_TYPE_DS1747_NVRAM_ADDR_REG&t;&t;0
DECL|macro|TODC_TYPE_DS1747_NVRAM_DATA_REG
mdefine_line|#define&t;TODC_TYPE_DS1747_NVRAM_DATA_REG&t;&t;0
DECL|macro|TODC_TYPE_DS17285_NVRAM_SIZE
mdefine_line|#define TODC_TYPE_DS17285_NVRAM_SIZE&t;&t;(0x1000-0x80)    /* 4Kx8 NVRAM (minus RTC regs) */
DECL|macro|TODC_TYPE_DS17285_SW_FLAGS
mdefine_line|#define TODC_TYPE_DS17285_SW_FLAGS&t;&t;TODC_FLAG_2_LEVEL_NVRAM
DECL|macro|TODC_TYPE_DS17285_SECONDS
mdefine_line|#define TODC_TYPE_DS17285_SECONDS&t;&t;(TODC_TYPE_DS17285_NVRAM_SIZE + 0x00)
DECL|macro|TODC_TYPE_DS17285_ALARM_SECONDS
mdefine_line|#define TODC_TYPE_DS17285_ALARM_SECONDS&t;&t;(TODC_TYPE_DS17285_NVRAM_SIZE + 0x01)
DECL|macro|TODC_TYPE_DS17285_MINUTES
mdefine_line|#define TODC_TYPE_DS17285_MINUTES&t;&t;(TODC_TYPE_DS17285_NVRAM_SIZE + 0x02)
DECL|macro|TODC_TYPE_DS17285_ALARM_MINUTES
mdefine_line|#define TODC_TYPE_DS17285_ALARM_MINUTES&t;&t;(TODC_TYPE_DS17285_NVRAM_SIZE + 0x03)
DECL|macro|TODC_TYPE_DS17285_HOURS
mdefine_line|#define TODC_TYPE_DS17285_HOURS&t;&t;&t;(TODC_TYPE_DS17285_NVRAM_SIZE + 0x04)
DECL|macro|TODC_TYPE_DS17285_ALARM_HOUR
mdefine_line|#define TODC_TYPE_DS17285_ALARM_HOUR&t;&t;(TODC_TYPE_DS17285_NVRAM_SIZE + 0x05)
DECL|macro|TODC_TYPE_DS17285_DOW
mdefine_line|#define TODC_TYPE_DS17285_DOW&t;&t;&t;(TODC_TYPE_DS17285_NVRAM_SIZE + 0x06)
DECL|macro|TODC_TYPE_DS17285_DOM
mdefine_line|#define TODC_TYPE_DS17285_DOM&t;&t;&t;(TODC_TYPE_DS17285_NVRAM_SIZE + 0x07)
DECL|macro|TODC_TYPE_DS17285_MONTH
mdefine_line|#define TODC_TYPE_DS17285_MONTH&t;&t;&t;(TODC_TYPE_DS17285_NVRAM_SIZE + 0x08)
DECL|macro|TODC_TYPE_DS17285_YEAR
mdefine_line|#define TODC_TYPE_DS17285_YEAR&t;&t;&t;(TODC_TYPE_DS17285_NVRAM_SIZE + 0x09)
DECL|macro|TODC_TYPE_DS17285_CNTL_A
mdefine_line|#define TODC_TYPE_DS17285_CNTL_A&t;&t;(TODC_TYPE_DS17285_NVRAM_SIZE + 0x0A)
DECL|macro|TODC_TYPE_DS17285_CNTL_B
mdefine_line|#define TODC_TYPE_DS17285_CNTL_B&t;&t;(TODC_TYPE_DS17285_NVRAM_SIZE + 0x0B)
DECL|macro|TODC_TYPE_DS17285_CNTL_C
mdefine_line|#define TODC_TYPE_DS17285_CNTL_C&t;&t;(TODC_TYPE_DS17285_NVRAM_SIZE + 0x0C)
DECL|macro|TODC_TYPE_DS17285_CNTL_D
mdefine_line|#define TODC_TYPE_DS17285_CNTL_D&t;&t;(TODC_TYPE_DS17285_NVRAM_SIZE + 0x0D)
DECL|macro|TODC_TYPE_DS17285_WATCHDOG
mdefine_line|#define TODC_TYPE_DS17285_WATCHDOG&t;&t;0
DECL|macro|TODC_TYPE_DS17285_INTERRUPTS
mdefine_line|#define TODC_TYPE_DS17285_INTERRUPTS&t;&t;0
DECL|macro|TODC_TYPE_DS17285_ALARM_DATE
mdefine_line|#define TODC_TYPE_DS17285_ALARM_DATE&t;&t;0
DECL|macro|TODC_TYPE_DS17285_CENTURY
mdefine_line|#define TODC_TYPE_DS17285_CENTURY&t;&t;0
DECL|macro|TODC_TYPE_DS17285_FLAGS
mdefine_line|#define TODC_TYPE_DS17285_FLAGS&t;&t;&t;0
DECL|macro|TODC_TYPE_DS17285_NVRAM_ADDR_REG
mdefine_line|#define TODC_TYPE_DS17285_NVRAM_ADDR_REG&t;0x50
DECL|macro|TODC_TYPE_DS17285_NVRAM_DATA_REG
mdefine_line|#define TODC_TYPE_DS17285_NVRAM_DATA_REG&t;0x53
DECL|macro|TODC_TYPE_MC146818_NVRAM_SIZE
mdefine_line|#define&t;TODC_TYPE_MC146818_NVRAM_SIZE&t;&t;0&t;/* XXXX */
DECL|macro|TODC_TYPE_MC146818_SW_FLAGS
mdefine_line|#define&t;TODC_TYPE_MC146818_SW_FLAGS&t;&t;0
DECL|macro|TODC_TYPE_MC146818_YEAR
mdefine_line|#define&t;TODC_TYPE_MC146818_YEAR&t;&t;&t;0x09
DECL|macro|TODC_TYPE_MC146818_MONTH
mdefine_line|#define&t;TODC_TYPE_MC146818_MONTH&t;&t;0x08
DECL|macro|TODC_TYPE_MC146818_DOM
mdefine_line|#define&t;TODC_TYPE_MC146818_DOM&t;&t;&t;0x07&t;/* Day of Month */
DECL|macro|TODC_TYPE_MC146818_DOW
mdefine_line|#define&t;TODC_TYPE_MC146818_DOW&t;&t;&t;0x06&t;/* Day of Week */
DECL|macro|TODC_TYPE_MC146818_HOURS
mdefine_line|#define&t;TODC_TYPE_MC146818_HOURS&t;&t;0x04
DECL|macro|TODC_TYPE_MC146818_MINUTES
mdefine_line|#define&t;TODC_TYPE_MC146818_MINUTES&t;&t;0x02
DECL|macro|TODC_TYPE_MC146818_SECONDS
mdefine_line|#define&t;TODC_TYPE_MC146818_SECONDS&t;&t;0x00
DECL|macro|TODC_TYPE_MC146818_CNTL_B
mdefine_line|#define&t;TODC_TYPE_MC146818_CNTL_B&t;&t;0x0a
DECL|macro|TODC_TYPE_MC146818_CNTL_A
mdefine_line|#define&t;TODC_TYPE_MC146818_CNTL_A&t;&t;0x0b&t;/* control_a R/W regs */
DECL|macro|TODC_TYPE_MC146818_WATCHDOG
mdefine_line|#define&t;TODC_TYPE_MC146818_WATCHDOG&t;&t;0
DECL|macro|TODC_TYPE_MC146818_INTERRUPTS
mdefine_line|#define&t;TODC_TYPE_MC146818_INTERRUPTS&t;&t;0x0c
DECL|macro|TODC_TYPE_MC146818_ALARM_DATE
mdefine_line|#define&t;TODC_TYPE_MC146818_ALARM_DATE&t;&t;0xff
DECL|macro|TODC_TYPE_MC146818_ALARM_HOUR
mdefine_line|#define&t;TODC_TYPE_MC146818_ALARM_HOUR&t;&t;0x05
DECL|macro|TODC_TYPE_MC146818_ALARM_MINUTES
mdefine_line|#define&t;TODC_TYPE_MC146818_ALARM_MINUTES&t;0x03
DECL|macro|TODC_TYPE_MC146818_ALARM_SECONDS
mdefine_line|#define&t;TODC_TYPE_MC146818_ALARM_SECONDS&t;0x01
DECL|macro|TODC_TYPE_MC146818_CENTURY
mdefine_line|#define&t;TODC_TYPE_MC146818_CENTURY&t;&t;0xff
DECL|macro|TODC_TYPE_MC146818_FLAGS
mdefine_line|#define&t;TODC_TYPE_MC146818_FLAGS&t;&t;0xff
DECL|macro|TODC_TYPE_MC146818_NVRAM_ADDR_REG
mdefine_line|#define&t;TODC_TYPE_MC146818_NVRAM_ADDR_REG&t;0
DECL|macro|TODC_TYPE_MC146818_NVRAM_DATA_REG
mdefine_line|#define&t;TODC_TYPE_MC146818_NVRAM_DATA_REG&t;0
DECL|macro|TODC_TYPE_PC97307_NVRAM_SIZE
mdefine_line|#define&t;TODC_TYPE_PC97307_NVRAM_SIZE&t;&t;0&t;/* No NVRAM? */
DECL|macro|TODC_TYPE_PC97307_SW_FLAGS
mdefine_line|#define&t;TODC_TYPE_PC97307_SW_FLAGS&t;&t;0
DECL|macro|TODC_TYPE_PC97307_YEAR
mdefine_line|#define&t;TODC_TYPE_PC97307_YEAR&t;&t;&t;0x09
DECL|macro|TODC_TYPE_PC97307_MONTH
mdefine_line|#define&t;TODC_TYPE_PC97307_MONTH&t;&t;&t;0x08
DECL|macro|TODC_TYPE_PC97307_DOM
mdefine_line|#define&t;TODC_TYPE_PC97307_DOM&t;&t;&t;0x07&t;/* Day of Month */
DECL|macro|TODC_TYPE_PC97307_DOW
mdefine_line|#define&t;TODC_TYPE_PC97307_DOW&t;&t;&t;0x06&t;/* Day of Week */
DECL|macro|TODC_TYPE_PC97307_HOURS
mdefine_line|#define&t;TODC_TYPE_PC97307_HOURS&t;&t;&t;0x04
DECL|macro|TODC_TYPE_PC97307_MINUTES
mdefine_line|#define&t;TODC_TYPE_PC97307_MINUTES&t;&t;0x02
DECL|macro|TODC_TYPE_PC97307_SECONDS
mdefine_line|#define&t;TODC_TYPE_PC97307_SECONDS&t;&t;0x00
DECL|macro|TODC_TYPE_PC97307_CNTL_B
mdefine_line|#define&t;TODC_TYPE_PC97307_CNTL_B&t;&t;0x0a
DECL|macro|TODC_TYPE_PC97307_CNTL_A
mdefine_line|#define&t;TODC_TYPE_PC97307_CNTL_A&t;&t;0x0b&t;/* control_a R/W regs */
DECL|macro|TODC_TYPE_PC97307_WATCHDOG
mdefine_line|#define&t;TODC_TYPE_PC97307_WATCHDOG&t;&t;0x0c
DECL|macro|TODC_TYPE_PC97307_INTERRUPTS
mdefine_line|#define&t;TODC_TYPE_PC97307_INTERRUPTS&t;&t;0x0d
DECL|macro|TODC_TYPE_PC97307_ALARM_DATE
mdefine_line|#define&t;TODC_TYPE_PC97307_ALARM_DATE&t;&t;0xff
DECL|macro|TODC_TYPE_PC97307_ALARM_HOUR
mdefine_line|#define&t;TODC_TYPE_PC97307_ALARM_HOUR&t;&t;0x05
DECL|macro|TODC_TYPE_PC97307_ALARM_MINUTES
mdefine_line|#define&t;TODC_TYPE_PC97307_ALARM_MINUTES&t;&t;0x03
DECL|macro|TODC_TYPE_PC97307_ALARM_SECONDS
mdefine_line|#define&t;TODC_TYPE_PC97307_ALARM_SECONDS&t;&t;0x01
DECL|macro|TODC_TYPE_PC97307_CENTURY
mdefine_line|#define&t;TODC_TYPE_PC97307_CENTURY&t;&t;0xff
DECL|macro|TODC_TYPE_PC97307_FLAGS
mdefine_line|#define&t;TODC_TYPE_PC97307_FLAGS&t;&t;&t;0xff
DECL|macro|TODC_TYPE_PC97307_NVRAM_ADDR_REG
mdefine_line|#define&t;TODC_TYPE_PC97307_NVRAM_ADDR_REG&t;0
DECL|macro|TODC_TYPE_PC97307_NVRAM_DATA_REG
mdefine_line|#define&t;TODC_TYPE_PC97307_NVRAM_DATA_REG&t;0
multiline_comment|/*&n; * Define macros to allocate and init the todc_info_t table that will&n; * be used by the todc_time.c routines.&n; */
DECL|macro|TODC_ALLOC
mdefine_line|#define&t;TODC_ALLOC()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;static todc_info_t todc_info_alloc;&t;&t;&t;&t;&bslash;&n;&t;todc_info_t *todc_info = &amp;todc_info_alloc;
DECL|macro|TODC_INIT
mdefine_line|#define&t;TODC_INIT(clock_type, as0, as1, data, bits) {&t;&t;&t;&bslash;&n;&t;todc_info-&gt;rtc_type = clock_type;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;todc_info-&gt;nvram_as0  = (unsigned int)(as0);&t;&t;&t;&bslash;&n;&t;todc_info-&gt;nvram_as1  = (unsigned int)(as1);&t;&t;&t;&bslash;&n;&t;todc_info-&gt;nvram_data = (unsigned int)(data);&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;todc_info-&gt;as0_bits = (bits);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;todc_info-&gt;nvram_size     = clock_type ##_NVRAM_SIZE;&t;&t;&bslash;&n;&t;todc_info-&gt;sw_flags       = clock_type ##_SW_FLAGS;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;todc_info-&gt;year           = clock_type ##_YEAR;&t;&t;&t;&bslash;&n;&t;todc_info-&gt;month          = clock_type ##_MONTH;&t;&t;&bslash;&n;&t;todc_info-&gt;day_of_month   = clock_type ##_DOM;&t;&t;&t;&bslash;&n;&t;todc_info-&gt;day_of_week    = clock_type ##_DOW;&t;&t;&t;&bslash;&n;&t;todc_info-&gt;hours          = clock_type ##_HOURS;&t;&t;&bslash;&n;&t;todc_info-&gt;minutes        = clock_type ##_MINUTES;&t;&t;&bslash;&n;&t;todc_info-&gt;seconds        = clock_type ##_SECONDS;&t;&t;&bslash;&n;&t;todc_info-&gt;control_b      = clock_type ##_CNTL_B;&t;&t;&bslash;&n;&t;todc_info-&gt;control_a      = clock_type ##_CNTL_A;&t;&t;&bslash;&n;&t;todc_info-&gt;watchdog       = clock_type ##_WATCHDOG;&t;&t;&bslash;&n;&t;todc_info-&gt;interrupts     = clock_type ##_INTERRUPTS;&t;&t;&bslash;&n;&t;todc_info-&gt;alarm_date     = clock_type ##_ALARM_DATE;&t;&t;&bslash;&n;&t;todc_info-&gt;alarm_hour     = clock_type ##_ALARM_HOUR;&t;&t;&bslash;&n;&t;todc_info-&gt;alarm_minutes  = clock_type ##_ALARM_MINUTES;&t;&bslash;&n;&t;todc_info-&gt;alarm_seconds  = clock_type ##_ALARM_SECONDS;&t;&bslash;&n;&t;todc_info-&gt;century        = clock_type ##_CENTURY;&t;&t;&bslash;&n;&t;todc_info-&gt;flags          = clock_type ##_FLAGS;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;todc_info-&gt;nvram_addr_reg = clock_type ##_NVRAM_ADDR_REG;&t;&bslash;&n;&t;todc_info-&gt;nvram_data_reg = clock_type ##_NVRAM_DATA_REG;&t;&bslash;&n;}
r_extern
id|todc_info_t
op_star
id|todc_info
suffix:semicolon
r_int
r_char
id|todc_direct_read_val
c_func
(paren
r_int
id|addr
)paren
suffix:semicolon
r_void
id|todc_direct_write_val
c_func
(paren
r_int
id|addr
comma
r_int
r_char
id|val
)paren
suffix:semicolon
r_int
r_char
id|todc_m48txx_read_val
c_func
(paren
r_int
id|addr
)paren
suffix:semicolon
r_void
id|todc_m48txx_write_val
c_func
(paren
r_int
id|addr
comma
r_int
r_char
id|val
)paren
suffix:semicolon
r_int
r_char
id|todc_mc146818_read_val
c_func
(paren
r_int
id|addr
)paren
suffix:semicolon
r_void
id|todc_mc146818_write_val
c_func
(paren
r_int
id|addr
comma
r_int
r_char
id|val
)paren
suffix:semicolon
r_int
id|todc_time_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|todc_get_rtc_time
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|todc_set_rtc_time
c_func
(paren
r_int
r_int
id|nowtime
)paren
suffix:semicolon
r_void
id|todc_calibrate_decr
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* __PPC_KERNEL_TODC_H */
eof
