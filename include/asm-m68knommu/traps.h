multiline_comment|/*&n; *  linux/include/asm/traps.h&n; *&n; *  Copyright (C) 1993        Hamish Macdonald&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef _M68KNOMMU_TRAPS_H
DECL|macro|_M68KNOMMU_TRAPS_H
mdefine_line|#define _M68KNOMMU_TRAPS_H
macro_line|#ifndef __ASSEMBLY__
DECL|typedef|e_vector
r_typedef
r_void
(paren
op_star
id|e_vector
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
id|e_vector
id|vectors
(braket
)braket
suffix:semicolon
macro_line|#endif
DECL|macro|VEC_BUSERR
mdefine_line|#define VEC_BUSERR  (2)
DECL|macro|VEC_ADDRERR
mdefine_line|#define VEC_ADDRERR (3)
DECL|macro|VEC_ILLEGAL
mdefine_line|#define VEC_ILLEGAL (4)
DECL|macro|VEC_ZERODIV
mdefine_line|#define VEC_ZERODIV (5)
DECL|macro|VEC_CHK
mdefine_line|#define VEC_CHK     (6)
DECL|macro|VEC_TRAP
mdefine_line|#define VEC_TRAP    (7)
DECL|macro|VEC_PRIV
mdefine_line|#define VEC_PRIV    (8)
DECL|macro|VEC_TRACE
mdefine_line|#define VEC_TRACE   (9)
DECL|macro|VEC_LINE10
mdefine_line|#define VEC_LINE10  (10)
DECL|macro|VEC_LINE11
mdefine_line|#define VEC_LINE11  (11)
DECL|macro|VEC_RESV1
mdefine_line|#define VEC_RESV1   (12)
DECL|macro|VEC_COPROC
mdefine_line|#define VEC_COPROC  (13)
DECL|macro|VEC_FORMAT
mdefine_line|#define VEC_FORMAT  (14)
DECL|macro|VEC_UNINT
mdefine_line|#define VEC_UNINT   (15)
DECL|macro|VEC_SPUR
mdefine_line|#define VEC_SPUR    (24)
DECL|macro|VEC_INT1
mdefine_line|#define VEC_INT1    (25)
DECL|macro|VEC_INT2
mdefine_line|#define VEC_INT2    (26)
DECL|macro|VEC_INT3
mdefine_line|#define VEC_INT3    (27)
DECL|macro|VEC_INT4
mdefine_line|#define VEC_INT4    (28)
DECL|macro|VEC_INT5
mdefine_line|#define VEC_INT5    (29)
DECL|macro|VEC_INT6
mdefine_line|#define VEC_INT6    (30)
DECL|macro|VEC_INT7
mdefine_line|#define VEC_INT7    (31)
DECL|macro|VEC_SYS
mdefine_line|#define VEC_SYS     (32)
DECL|macro|VEC_TRAP1
mdefine_line|#define VEC_TRAP1   (33)
DECL|macro|VEC_TRAP2
mdefine_line|#define VEC_TRAP2   (34)
DECL|macro|VEC_TRAP3
mdefine_line|#define VEC_TRAP3   (35)
DECL|macro|VEC_TRAP4
mdefine_line|#define VEC_TRAP4   (36)
DECL|macro|VEC_TRAP5
mdefine_line|#define VEC_TRAP5   (37)
DECL|macro|VEC_TRAP6
mdefine_line|#define VEC_TRAP6   (38)
DECL|macro|VEC_TRAP7
mdefine_line|#define VEC_TRAP7   (39)
DECL|macro|VEC_TRAP8
mdefine_line|#define VEC_TRAP8   (40)
DECL|macro|VEC_TRAP9
mdefine_line|#define VEC_TRAP9   (41)
DECL|macro|VEC_TRAP10
mdefine_line|#define VEC_TRAP10  (42)
DECL|macro|VEC_TRAP11
mdefine_line|#define VEC_TRAP11  (43)
DECL|macro|VEC_TRAP12
mdefine_line|#define VEC_TRAP12  (44)
DECL|macro|VEC_TRAP13
mdefine_line|#define VEC_TRAP13  (45)
DECL|macro|VEC_TRAP14
mdefine_line|#define VEC_TRAP14  (46)
DECL|macro|VEC_TRAP15
mdefine_line|#define VEC_TRAP15  (47)
DECL|macro|VEC_FPBRUC
mdefine_line|#define VEC_FPBRUC  (48)
DECL|macro|VEC_FPIR
mdefine_line|#define VEC_FPIR    (49)
DECL|macro|VEC_FPDIVZ
mdefine_line|#define VEC_FPDIVZ  (50)
DECL|macro|VEC_FPUNDER
mdefine_line|#define VEC_FPUNDER (51)
DECL|macro|VEC_FPOE
mdefine_line|#define VEC_FPOE    (52)
DECL|macro|VEC_FPOVER
mdefine_line|#define VEC_FPOVER  (53)
DECL|macro|VEC_FPNAN
mdefine_line|#define VEC_FPNAN   (54)
DECL|macro|VEC_FPUNSUP
mdefine_line|#define VEC_FPUNSUP (55)
DECL|macro|VEC_UNIMPEA
mdefine_line|#define&t;VEC_UNIMPEA (60)
DECL|macro|VEC_UNIMPII
mdefine_line|#define&t;VEC_UNIMPII (61)
DECL|macro|VEC_USER
mdefine_line|#define VEC_USER    (64)
DECL|macro|VECOFF
mdefine_line|#define VECOFF(vec) ((vec)&lt;&lt;2)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Status register bits */
DECL|macro|PS_T
mdefine_line|#define PS_T  (0x8000)
DECL|macro|PS_S
mdefine_line|#define PS_S  (0x2000)
DECL|macro|PS_M
mdefine_line|#define PS_M  (0x1000)
DECL|macro|PS_C
mdefine_line|#define PS_C  (0x0001)
multiline_comment|/* structure for stack frames */
DECL|struct|frame
r_struct
id|frame
(brace
DECL|member|ptregs
r_struct
id|pt_regs
id|ptregs
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|iaddr
r_int
r_int
id|iaddr
suffix:semicolon
multiline_comment|/* instruction address */
DECL|member|fmt2
)brace
id|fmt2
suffix:semicolon
r_struct
(brace
DECL|member|effaddr
r_int
r_int
id|effaddr
suffix:semicolon
multiline_comment|/* effective address */
DECL|member|fmt3
)brace
id|fmt3
suffix:semicolon
r_struct
(brace
DECL|member|effaddr
r_int
r_int
id|effaddr
suffix:semicolon
multiline_comment|/* effective address */
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
multiline_comment|/* pc of faulted instr */
DECL|member|fmt4
)brace
id|fmt4
suffix:semicolon
r_struct
(brace
DECL|member|effaddr
r_int
r_int
id|effaddr
suffix:semicolon
multiline_comment|/* effective address */
DECL|member|ssw
r_int
r_int
id|ssw
suffix:semicolon
multiline_comment|/* special status word */
DECL|member|wb3s
r_int
r_int
id|wb3s
suffix:semicolon
multiline_comment|/* write back 3 status */
DECL|member|wb2s
r_int
r_int
id|wb2s
suffix:semicolon
multiline_comment|/* write back 2 status */
DECL|member|wb1s
r_int
r_int
id|wb1s
suffix:semicolon
multiline_comment|/* write back 1 status */
DECL|member|faddr
r_int
r_int
id|faddr
suffix:semicolon
multiline_comment|/* fault address */
DECL|member|wb3a
r_int
r_int
id|wb3a
suffix:semicolon
multiline_comment|/* write back 3 address */
DECL|member|wb3d
r_int
r_int
id|wb3d
suffix:semicolon
multiline_comment|/* write back 3 data */
DECL|member|wb2a
r_int
r_int
id|wb2a
suffix:semicolon
multiline_comment|/* write back 2 address */
DECL|member|wb2d
r_int
r_int
id|wb2d
suffix:semicolon
multiline_comment|/* write back 2 data */
DECL|member|wb1a
r_int
r_int
id|wb1a
suffix:semicolon
multiline_comment|/* write back 1 address */
DECL|member|wb1dpd0
r_int
r_int
id|wb1dpd0
suffix:semicolon
multiline_comment|/* write back 1 data/push data 0*/
DECL|member|pd1
r_int
r_int
id|pd1
suffix:semicolon
multiline_comment|/* push data 1*/
DECL|member|pd2
r_int
r_int
id|pd2
suffix:semicolon
multiline_comment|/* push data 2*/
DECL|member|pd3
r_int
r_int
id|pd3
suffix:semicolon
multiline_comment|/* push data 3*/
DECL|member|fmt7
)brace
id|fmt7
suffix:semicolon
r_struct
(brace
DECL|member|iaddr
r_int
r_int
id|iaddr
suffix:semicolon
multiline_comment|/* instruction address */
DECL|member|int1
r_int
r_int
id|int1
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* internal registers */
DECL|member|fmt9
)brace
id|fmt9
suffix:semicolon
r_struct
(brace
DECL|member|int1
r_int
r_int
id|int1
suffix:semicolon
DECL|member|ssw
r_int
r_int
id|ssw
suffix:semicolon
multiline_comment|/* special status word */
DECL|member|isc
r_int
r_int
id|isc
suffix:semicolon
multiline_comment|/* instruction stage c */
DECL|member|isb
r_int
r_int
id|isb
suffix:semicolon
multiline_comment|/* instruction stage b */
DECL|member|daddr
r_int
r_int
id|daddr
suffix:semicolon
multiline_comment|/* data cycle fault address */
DECL|member|int2
r_int
r_int
id|int2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|dobuf
r_int
r_int
id|dobuf
suffix:semicolon
multiline_comment|/* data cycle output buffer */
DECL|member|int3
r_int
r_int
id|int3
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|fmta
)brace
id|fmta
suffix:semicolon
r_struct
(brace
DECL|member|int1
r_int
r_int
id|int1
suffix:semicolon
DECL|member|ssw
r_int
r_int
id|ssw
suffix:semicolon
multiline_comment|/* special status word */
DECL|member|isc
r_int
r_int
id|isc
suffix:semicolon
multiline_comment|/* instruction stage c */
DECL|member|isb
r_int
r_int
id|isb
suffix:semicolon
multiline_comment|/* instruction stage b */
DECL|member|daddr
r_int
r_int
id|daddr
suffix:semicolon
multiline_comment|/* data cycle fault address */
DECL|member|int2
r_int
r_int
id|int2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|dobuf
r_int
r_int
id|dobuf
suffix:semicolon
multiline_comment|/* data cycle output buffer */
DECL|member|int3
r_int
r_int
id|int3
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|baddr
r_int
r_int
id|baddr
suffix:semicolon
multiline_comment|/* stage B address */
DECL|member|int4
r_int
r_int
id|int4
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|dibuf
r_int
r_int
id|dibuf
suffix:semicolon
multiline_comment|/* data cycle input buffer */
DECL|member|int5
r_int
r_int
id|int5
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ver
r_int
id|ver
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* stack frame version # */
DECL|member|int6
r_int
id|int6
suffix:colon
l_int|12
suffix:semicolon
DECL|member|int7
r_int
r_int
id|int7
(braket
l_int|18
)braket
suffix:semicolon
DECL|member|fmtb
)brace
id|fmtb
suffix:semicolon
DECL|member|un
)brace
id|un
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _M68KNOMMU_TRAPS_H */
eof
