multiline_comment|/*&n; * linux/include/asm-arm/arch-shark/param.h&n; *&n; * by Alexander Schulz&n; */
multiline_comment|/* This must be a power of 2 because the RTC&n; * can&squot;t use anything else.&n; */
DECL|macro|HZ
mdefine_line|#define HZ 64
DECL|macro|hz_to_std
mdefine_line|#define hz_to_std(a) ((a * HZ)/100)
eof
