macro_line|#ifndef _PARISC_PSW_H
DECL|macro|PSW_I
mdefine_line|#define&t;PSW_I&t;0x00000001
DECL|macro|PSW_D
mdefine_line|#define&t;PSW_D&t;0x00000002
DECL|macro|PSW_P
mdefine_line|#define&t;PSW_P&t;0x00000004
DECL|macro|PSW_Q
mdefine_line|#define&t;PSW_Q&t;0x00000008
DECL|macro|PSW_R
mdefine_line|#define&t;PSW_R&t;0x00000010
DECL|macro|PSW_F
mdefine_line|#define&t;PSW_F&t;0x00000020
DECL|macro|PSW_G
mdefine_line|#define&t;PSW_G&t;0x00000040&t;/* PA1.x only */
DECL|macro|PSW_O
mdefine_line|#define PSW_O&t;0x00000080&t;/* PA2.0 only */
DECL|macro|PSW_M
mdefine_line|#define&t;PSW_M&t;0x00010000
DECL|macro|PSW_V
mdefine_line|#define&t;PSW_V&t;0x00020000
DECL|macro|PSW_C
mdefine_line|#define&t;PSW_C&t;0x00040000
DECL|macro|PSW_B
mdefine_line|#define&t;PSW_B&t;0x00080000
DECL|macro|PSW_X
mdefine_line|#define&t;PSW_X&t;0x00100000
DECL|macro|PSW_N
mdefine_line|#define&t;PSW_N&t;0x00200000
DECL|macro|PSW_L
mdefine_line|#define&t;PSW_L&t;0x00400000
DECL|macro|PSW_H
mdefine_line|#define&t;PSW_H&t;0x00800000
DECL|macro|PSW_T
mdefine_line|#define&t;PSW_T&t;0x01000000
DECL|macro|PSW_S
mdefine_line|#define&t;PSW_S&t;0x02000000
DECL|macro|PSW_E
mdefine_line|#define&t;PSW_E&t;0x04000000
DECL|macro|PSW_W
mdefine_line|#define PSW_W&t;0x08000000&t;/* PA2.0 only */
DECL|macro|PSW_Z
mdefine_line|#define&t;PSW_Z&t;0x40000000&t;/* PA1.x only */
DECL|macro|PSW_Y
mdefine_line|#define&t;PSW_Y&t;0x80000000&t;/* PA1.x only */
multiline_comment|/* PSW bits to be used with ssm/rsm */
DECL|macro|PSW_SM_I
mdefine_line|#define PSW_SM_I        0x1
DECL|macro|PSW_SM_D
mdefine_line|#define PSW_SM_D        0x2
DECL|macro|PSW_SM_P
mdefine_line|#define PSW_SM_P        0x4
DECL|macro|PSW_SM_Q
mdefine_line|#define PSW_SM_Q        0x8
DECL|macro|PSW_SM_R
mdefine_line|#define PSW_SM_R        0x10
DECL|macro|PSW_SM_F
mdefine_line|#define PSW_SM_F        0x20
DECL|macro|PSW_SM_G
mdefine_line|#define PSW_SM_G        0x40
DECL|macro|PSW_SM_O
mdefine_line|#define PSW_SM_O        0x80
DECL|macro|PSW_SM_E
mdefine_line|#define PSW_SM_E        0x100
DECL|macro|PSW_SM_W
mdefine_line|#define PSW_SM_W        0x200
macro_line|#ifdef __LP64__
DECL|macro|USER_PSW
macro_line|#  define USER_PSW&t;(PSW_C | PSW_D | PSW_Q | PSW_I)
DECL|macro|USER_INIT_PSW
macro_line|#  define USER_INIT_PSW&t;(PSW_C | PSW_D | PSW_Q | PSW_I | PSW_N)
DECL|macro|KERNEL_PSW
macro_line|#  define KERNEL_PSW&t;(PSW_C | PSW_D | PSW_Q | PSW_W)
DECL|macro|PDC_PSW
macro_line|#  define PDC_PSW&t;(PSW_Q | PSW_W)
macro_line|#else
DECL|macro|USER_PSW
macro_line|#  define USER_PSW&t;(PSW_C | PSW_D | PSW_Q | PSW_I | PSW_P)
DECL|macro|USER_INIT_PSW
macro_line|#  define USER_INIT_PSW&t;(PSW_C | PSW_D | PSW_Q | PSW_I | PSW_N)
DECL|macro|KERNEL_PSW
macro_line|#  define KERNEL_PSW&t;(PSW_C | PSW_D | PSW_Q)
DECL|macro|PDC_PSW
macro_line|#  define PDC_PSW&t;(PSW_Q)
macro_line|#endif
macro_line|#endif
eof
