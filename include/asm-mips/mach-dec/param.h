multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MACH_DEC_PARAM_H
DECL|macro|__ASM_MACH_DEC_PARAM_H
mdefine_line|#define __ASM_MACH_DEC_PARAM_H
multiline_comment|/*&n; * log2(HZ), change this here if you want another HZ value. This is also&n; * used in dec_time_init.  Minimum is 1, Maximum is 15.&n; */
DECL|macro|LOG_2_HZ
mdefine_line|#define LOG_2_HZ 7
DECL|macro|HZ
mdefine_line|#define HZ (1 &lt;&lt; LOG_2_HZ)
macro_line|#endif /* __ASM_MACH_DEC_PARAM_H */
eof
