macro_line|#ifndef __reg_h__
DECL|macro|__reg_h__
mdefine_line|#define __reg_h__
multiline_comment|/*&n; * Exception frame offsets.&n; */
DECL|macro|EF_V0
mdefine_line|#define EF_V0&t;&t;0
DECL|macro|EF_T0
mdefine_line|#define EF_T0&t;&t;1
DECL|macro|EF_T1
mdefine_line|#define EF_T1&t;&t;2
DECL|macro|EF_T2
mdefine_line|#define EF_T2&t;&t;3
DECL|macro|EF_T3
mdefine_line|#define EF_T3&t;&t;4
DECL|macro|EF_T4
mdefine_line|#define EF_T4&t;&t;5
DECL|macro|EF_T5
mdefine_line|#define EF_T5&t;&t;6
DECL|macro|EF_T6
mdefine_line|#define EF_T6&t;&t;7
DECL|macro|EF_T7
mdefine_line|#define EF_T7&t;&t;8
DECL|macro|EF_S0
mdefine_line|#define EF_S0&t;&t;9
DECL|macro|EF_S1
mdefine_line|#define EF_S1&t;&t;10
DECL|macro|EF_S2
mdefine_line|#define EF_S2&t;&t;11
DECL|macro|EF_S3
mdefine_line|#define EF_S3&t;&t;12
DECL|macro|EF_S4
mdefine_line|#define EF_S4&t;&t;13
DECL|macro|EF_S5
mdefine_line|#define EF_S5&t;&t;14
DECL|macro|EF_S6
mdefine_line|#define EF_S6&t;&t;15
DECL|macro|EF_A3
mdefine_line|#define EF_A3&t;&t;16
DECL|macro|EF_A4
mdefine_line|#define EF_A4&t;&t;17
DECL|macro|EF_A5
mdefine_line|#define EF_A5&t;&t;18
DECL|macro|EF_T8
mdefine_line|#define EF_T8&t;&t;19
DECL|macro|EF_T9
mdefine_line|#define EF_T9&t;&t;20
DECL|macro|EF_T10
mdefine_line|#define EF_T10&t;&t;21
DECL|macro|EF_T11
mdefine_line|#define EF_T11&t;&t;22
DECL|macro|EF_RA
mdefine_line|#define EF_RA&t;&t;23
DECL|macro|EF_T12
mdefine_line|#define EF_T12&t;&t;24
DECL|macro|EF_AT
mdefine_line|#define EF_AT&t;&t;25
DECL|macro|EF_SP
mdefine_line|#define EF_SP&t;&t;26
DECL|macro|EF_PS
mdefine_line|#define EF_PS&t;&t;27
DECL|macro|EF_PC
mdefine_line|#define EF_PC&t;&t;28
DECL|macro|EF_GP
mdefine_line|#define EF_GP&t;&t;29
DECL|macro|EF_A0
mdefine_line|#define EF_A0&t;&t;30
DECL|macro|EF_A1
mdefine_line|#define EF_A1&t;&t;31
DECL|macro|EF_A2
mdefine_line|#define EF_A2&t;&t;32
DECL|macro|EF_SIZE
mdefine_line|#define EF_SIZE&t;&t;(33*8)
DECL|macro|HWEF_SIZE
mdefine_line|#define HWEF_SIZE&t;(6*8)&t;&t;/* size of PAL frame (PS-A2) */
DECL|macro|EF_SSIZE
mdefine_line|#define EF_SSIZE&t;(EF_SIZE - HWEF_SIZE)
multiline_comment|/*&n; * Map register number into core file offset.&n; */
DECL|macro|CORE_REG
mdefine_line|#define CORE_REG(reg, ubase) &bslash;&n;&t;(((unsigned long *)((unsigned long)(ubase)))[reg])
macro_line|#endif /* __reg_h__ */
eof
