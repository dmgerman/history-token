multiline_comment|/* $Id: cpu.h,v 1.1 1999/10/19 20:51:53 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * cpu.h: Values of the PRId register used to match up&n; *        various MIPS cpu types.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#ifndef _ASM_CPU_H
DECL|macro|_ASM_CPU_H
mdefine_line|#define _ASM_CPU_H
multiline_comment|/*&n; * Assigned values for the product ID register.  In order to detect a&n; * certain CPU type exactly eventually additional registers may need to&n; * be examined.&n; */
DECL|macro|PRID_IMP_R2000
mdefine_line|#define PRID_IMP_R2000    0x0100
DECL|macro|PRID_IMP_R3000
mdefine_line|#define PRID_IMP_R3000    0x0200
DECL|macro|PRID_IMP_R6000
mdefine_line|#define PRID_IMP_R6000    0x0300
DECL|macro|PRID_IMP_R4000
mdefine_line|#define PRID_IMP_R4000    0x0400
DECL|macro|PRID_IMP_R6000A
mdefine_line|#define PRID_IMP_R6000A   0x0600
DECL|macro|PRID_IMP_R10000
mdefine_line|#define PRID_IMP_R10000   0x0900
DECL|macro|PRID_IMP_R4300
mdefine_line|#define PRID_IMP_R4300    0x0b00
DECL|macro|PRID_IMP_R8000
mdefine_line|#define PRID_IMP_R8000    0x1000
DECL|macro|PRID_IMP_R4600
mdefine_line|#define PRID_IMP_R4600    0x2000
DECL|macro|PRID_IMP_R4700
mdefine_line|#define PRID_IMP_R4700    0x2100
DECL|macro|PRID_IMP_R4640
mdefine_line|#define PRID_IMP_R4640    0x2200
DECL|macro|PRID_IMP_R4650
mdefine_line|#define PRID_IMP_R4650    0x2200&t;&t;/* Same as R4640 */
DECL|macro|PRID_IMP_R5000
mdefine_line|#define PRID_IMP_R5000    0x2300
DECL|macro|PRID_IMP_SONIC
mdefine_line|#define PRID_IMP_SONIC    0x2400
DECL|macro|PRID_IMP_MAGIC
mdefine_line|#define PRID_IMP_MAGIC    0x2500
DECL|macro|PRID_IMP_RM7000
mdefine_line|#define PRID_IMP_RM7000   0x2700
DECL|macro|PRID_IMP_NEVADA
mdefine_line|#define PRID_IMP_NEVADA   0x2800
DECL|macro|PRID_IMP_UNKNOWN
mdefine_line|#define PRID_IMP_UNKNOWN  0xff00
DECL|macro|PRID_REV_R4400
mdefine_line|#define PRID_REV_R4400    0x0040
DECL|macro|PRID_REV_R3000A
mdefine_line|#define PRID_REV_R3000A   0x0030
DECL|macro|PRID_REV_R3000
mdefine_line|#define PRID_REV_R3000    0x0020
DECL|macro|PRID_REV_R2000A
mdefine_line|#define PRID_REV_R2000A   0x0010
macro_line|#endif /* _ASM_CPU_H */
eof
