multiline_comment|/*&n; * Registers for the mk48t59 real-time-clock&n; */
macro_line|#ifndef _PPC_MK48T59_H
DECL|macro|_PPC_MK48T59_H
mdefine_line|#define _PPC_MK48T59_H
multiline_comment|/* RTC Offsets */
DECL|macro|MK48T59_RTC_SECONDS
mdefine_line|#define MK48T59_RTC_SECONDS&t;&t;0x1FF9
DECL|macro|MK48T59_RTC_MINUTES
mdefine_line|#define MK48T59_RTC_MINUTES&t;&t;0x1FFA
DECL|macro|MK48T59_RTC_HOURS
mdefine_line|#define MK48T59_RTC_HOURS&t;&t;0x1FFB
DECL|macro|MK48T59_RTC_DAY_OF_WEEK
mdefine_line|#define MK48T59_RTC_DAY_OF_WEEK&t;&t;0x1FFC
DECL|macro|MK48T59_RTC_DAY_OF_MONTH
mdefine_line|#define MK48T59_RTC_DAY_OF_MONTH&t;0x1FFD
DECL|macro|MK48T59_RTC_MONTH
mdefine_line|#define MK48T59_RTC_MONTH&t;&t;0x1FFE
DECL|macro|MK48T59_RTC_YEAR
mdefine_line|#define MK48T59_RTC_YEAR&t;&t;0x1FFF
DECL|macro|MK48T59_RTC_CONTROLA
mdefine_line|#define MK48T59_RTC_CONTROLA&t;&t;0x1FF8
DECL|macro|MK48T59_RTC_CA_WRITE
mdefine_line|#define MK48T59_RTC_CA_WRITE&t;&t;0x80
DECL|macro|MK48T59_RTC_CA_READ
mdefine_line|#define MK48T59_RTC_CA_READ&t;&t;0x40
DECL|macro|MK48T59_RTC_CA_CALIB_SIGN
mdefine_line|#define MK48T59_RTC_CA_CALIB_SIGN&t;0x20
DECL|macro|MK48T59_RTC_CA_CALIB_MASK
mdefine_line|#define MK48T59_RTC_CA_CALIB_MASK&t;0x1f
DECL|macro|MK48T59_RTC_CONTROLB
mdefine_line|#define MK48T59_RTC_CONTROLB&t;&t;0x1FF9
DECL|macro|MK48T59_RTC_CB_STOP
mdefine_line|#define MK48T59_RTC_CB_STOP&t;&t;0x80
macro_line|#ifndef BCD_TO_BIN
DECL|macro|BCD_TO_BIN
mdefine_line|#define BCD_TO_BIN(val) ((val)=((val)&amp;15) + ((val)&gt;&gt;4)*10)
macro_line|#endif
macro_line|#ifndef BIN_TO_BCD
DECL|macro|BIN_TO_BCD
mdefine_line|#define BIN_TO_BCD(val) ((val)=(((val)/10)&lt;&lt;4) + (val)%10)
macro_line|#endif
macro_line|#endif /* _PPC_MK48T59_H */
eof
