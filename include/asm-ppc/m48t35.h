multiline_comment|/*&n; * BK Id: SCCS/s.m48t35.h 1.8 10/16/01 15:58:42 trini&n; */
multiline_comment|/*&n; *  Registers for the SGS-Thomson M48T35 Timekeeper RAM chip&n; *  and&n; *  Registers for the SGS-Thomson M48T37 Timekeeper RAM chip&n; *  The 37 is the 35 plus alarm and century thus the offsets&n; *  are shifted by the extra registers.&n; */
macro_line|#ifndef __PPC_M48T35_H
DECL|macro|__PPC_M48T35_H
mdefine_line|#define __PPC_M48T35_H
multiline_comment|/* RTC offsets */
DECL|macro|M48T35_RTC_FLAGS
mdefine_line|#define M48T35_RTC_FLAGS&t;(-8)&t;/* the negative regs are really T37 only */ 
DECL|macro|M48T35_RTC_CENTURY
mdefine_line|#define M48T35_RTC_CENTURY&t;(-7)
DECL|macro|M48T35_RTC_AL_SEC
mdefine_line|#define M48T35_RTC_AL_SEC&t;(-6)    
DECL|macro|M48T35_RTC_AL_MIN
mdefine_line|#define M48T35_RTC_AL_MIN&t;(-5)    
DECL|macro|M48T35_RTC_AL_HRS
mdefine_line|#define M48T35_RTC_AL_HRS&t;(-4)    
DECL|macro|M48T35_RTC_AL_DOM
mdefine_line|#define M48T35_RTC_AL_DOM&t;(-3)    
DECL|macro|M48T35_RTC_INTERRUPT
mdefine_line|#define M48T35_RTC_INTERRUPT&t;(-2)
DECL|macro|M48T35_RTC_WATCHDOG
mdefine_line|#define M48T35_RTC_WATCHDOG&t;(-1)
DECL|macro|M48T35_RTC_CONTROL
mdefine_line|#define M48T35_RTC_CONTROL&t;0&t;/* T35 starts here */ 
DECL|macro|M48T35_RTC_SECONDS
mdefine_line|#define M48T35_RTC_SECONDS&t;1
DECL|macro|M48T35_RTC_MINUTES
mdefine_line|#define M48T35_RTC_MINUTES&t;2
DECL|macro|M48T35_RTC_HOURS
mdefine_line|#define M48T35_RTC_HOURS&t;3
DECL|macro|M48T35_RTC_DAY
mdefine_line|#define M48T35_RTC_DAY&t;&t;4
DECL|macro|M48T35_RTC_DOM
mdefine_line|#define M48T35_RTC_DOM&t;&t;5
DECL|macro|M48T35_RTC_MONTH
mdefine_line|#define M48T35_RTC_MONTH&t;6
DECL|macro|M48T35_RTC_YEAR
mdefine_line|#define M48T35_RTC_YEAR&t;&t;7
multiline_comment|/* this way help us know which bits go with which regs */
DECL|macro|M48T35_RTC_FLAGS_BL
mdefine_line|#define M48T35_RTC_FLAGS_BL           0x10
DECL|macro|M48T35_RTC_FLAGS_AF
mdefine_line|#define M48T35_RTC_FLAGS_AF           0x40
DECL|macro|M48T35_RTC_FLAGS_WDF
mdefine_line|#define M48T35_RTC_FLAGS_WDF          0x80
DECL|macro|M48T35_RTC_INTERRUPT_AFE
mdefine_line|#define M48T35_RTC_INTERRUPT_AFE       0x80
DECL|macro|M48T35_RTC_INTERRUPT_ABE
mdefine_line|#define M48T35_RTC_INTERRUPT_ABE       0x20
DECL|macro|M48T35_RTC_INTERRUPT_ALL
mdefine_line|#define M48T35_RTC_INTERRUPT_ALL       (M48T35_RTC_INTERRUPT_AFE|M48T35_RTC_INTERRUPT_ABE)
DECL|macro|M48T35_RTC_WATCHDOG_RB
mdefine_line|#define M48T35_RTC_WATCHDOG_RB         0x03
DECL|macro|M48T35_RTC_WATCHDOG_BMB
mdefine_line|#define M48T35_RTC_WATCHDOG_BMB        0x7c
DECL|macro|M48T35_RTC_WATCHDOG_WDS
mdefine_line|#define M48T35_RTC_WATCHDOG_WDS        0x80
DECL|macro|M48T35_RTC_WATCHDOG_ALL
mdefine_line|#define M48T35_RTC_WATCHDOG_ALL        (M48T35_RTC_WATCHDOG_RB|M48T35_RTC_WATCHDOG_BMB|M48T35_RTC_W
DECL|macro|M48T35_RTC_CONTROL_WRITE
mdefine_line|#define M48T35_RTC_CONTROL_WRITE       0x80
DECL|macro|M48T35_RTC_CONTROL_READ
mdefine_line|#define M48T35_RTC_CONTROL_READ        0x40
DECL|macro|M48T35_RTC_CONTROL_CAL_SIGN
mdefine_line|#define M48T35_RTC_CONTROL_CAL_SIGN    0x20    
DECL|macro|M48T35_RTC_CONTROL_CAL_VALUE
mdefine_line|#define M48T35_RTC_CONTROL_CAL_VALUE   0x1f
DECL|macro|M48T35_RTC_CONTROL_LOCKED
mdefine_line|#define M48T35_RTC_CONTROL_LOCKED      (M48T35_RTC_WRITE|M48T35_RTC_READ)
DECL|macro|M48T35_RTC_CONTROL_CALIBRATION
mdefine_line|#define M48T35_RTC_CONTROL_CALIBRATION (M48T35_RTC_CONTROL_CAL_SIGN|M48T35_RTC_CONTROL_CAL_VALUE)
DECL|macro|M48T35_RTC_SECONDS_SEC_1
mdefine_line|#define M48T35_RTC_SECONDS_SEC_1       0x0f
DECL|macro|M48T35_RTC_SECONDS_SEC_10
mdefine_line|#define M48T35_RTC_SECONDS_SEC_10      0x70    
DECL|macro|M48T35_RTC_SECONDS_ST
mdefine_line|#define M48T35_RTC_SECONDS_ST          0x80
DECL|macro|M48T35_RTC_SECONDS_SEC_ALL
mdefine_line|#define M48T35_RTC_SECONDS_SEC_ALL     (M48T35_RTC_SECONDS_SEC_1|M48T35_RTC_SECONDS_SEC_10)
DECL|macro|M48T35_RTC_MINUTES_MIN_1
mdefine_line|#define M48T35_RTC_MINUTES_MIN_1       0x0f
DECL|macro|M48T35_RTC_MINUTES_MIN_10
mdefine_line|#define M48T35_RTC_MINUTES_MIN_10      0x70    
DECL|macro|M48T35_RTC_MINUTES_MIN_ALL
mdefine_line|#define M48T35_RTC_MINUTES_MIN_ALL     (M48T35_RTC_MINUTES_MIN_1|M48T35_RTC_MINUTES_MIN_10)
DECL|macro|M48T35_RTC_HOURS_HRS_1
mdefine_line|#define M48T35_RTC_HOURS_HRS_1         0x0f
DECL|macro|M48T35_RTC_HOURS_HRS_10
mdefine_line|#define M48T35_RTC_HOURS_HRS_10        0x30
DECL|macro|M48T35_RTC_HOURS_HRS_ALL
mdefine_line|#define M48T35_RTC_HOURS_HRS_ALL       (M48T35_RTC_HOURS_HRS_1|M48T35_RTC_HOURS_HRS_10)
DECL|macro|M48T35_RTC_DAY_DAY_1
mdefine_line|#define M48T35_RTC_DAY_DAY_1           0x03
DECL|macro|M48T35_RTC_DAY_FT
mdefine_line|#define M48T35_RTC_DAY_FT              0x40
DECL|macro|M48T35_RTC_ALARM_OFF
mdefine_line|#define M48T35_RTC_ALARM_OFF           0x00
DECL|macro|M48T35_RTC_WATCHDOG_OFF
mdefine_line|#define M48T35_RTC_WATCHDOG_OFF        0x00
multiline_comment|/* legacy */
DECL|macro|M48T35_RTC_SET
mdefine_line|#define M48T35_RTC_SET      0x80
DECL|macro|M48T35_RTC_STOPPED
mdefine_line|#define M48T35_RTC_STOPPED  0x80
DECL|macro|M48T35_RTC_READ
mdefine_line|#define M48T35_RTC_READ     0x40
multiline_comment|/* read/write conversions */
macro_line|#ifndef BCD_TO_BIN
DECL|macro|BCD_TO_BIN
mdefine_line|#define BCD_TO_BIN(x)   ((x)=((x)&amp;15) + ((x)&gt;&gt;4)*10)
macro_line|#endif
macro_line|#ifndef BIN_TO_BCD
DECL|macro|BIN_TO_BCD
mdefine_line|#define BIN_TO_BCD(x)   ((x)=(((x)/10)&lt;&lt;4) + (x)%10)
macro_line|#endif
macro_line|#endif
eof
