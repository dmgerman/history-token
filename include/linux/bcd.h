multiline_comment|/* Permission is hereby granted to copy, modify and redistribute this code&n; * in terms of the GNU Library General Public License, Version 2 or later,&n; * at your option.&n; */
multiline_comment|/* macros to translate to/from binary and binary-coded decimal (frequently&n; * found in RTC chips).&n; */
macro_line|#ifndef _BCD_H
DECL|macro|_BCD_H
mdefine_line|#define _BCD_H
DECL|macro|BCD2BIN
mdefine_line|#define BCD2BIN(val)&t;(((val) &amp; 0x0f) + ((val)&gt;&gt;4)*10)
DECL|macro|BIN2BCD
mdefine_line|#define BIN2BCD(val)&t;((((val)/10)&lt;&lt;4) + (val)%10)
multiline_comment|/* backwards compat */
DECL|macro|BCD_TO_BIN
mdefine_line|#define BCD_TO_BIN(val) ((val)=BCD2BIN(val))
DECL|macro|BIN_TO_BCD
mdefine_line|#define BIN_TO_BCD(val) ((val)=BIN2BCD(val))
macro_line|#endif /* _BCD_H */
eof
