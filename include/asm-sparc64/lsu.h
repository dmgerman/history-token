multiline_comment|/* $Id: lsu.h,v 1.2 1997/04/04 00:50:22 davem Exp $ */
macro_line|#ifndef _SPARC64_LSU_H
DECL|macro|_SPARC64_LSU_H
mdefine_line|#define _SPARC64_LSU_H
multiline_comment|/* LSU Control Register */
DECL|macro|LSU_CONTROL_PM
mdefine_line|#define LSU_CONTROL_PM&t;&t;0x000001fe00000000 /* Phys-watchpoint byte mask     */
DECL|macro|LSU_CONTROL_VM
mdefine_line|#define LSU_CONTROL_VM&t;&t;0x00000001fe000000 /* Virt-watchpoint byte mask     */
DECL|macro|LSU_CONTROL_PR
mdefine_line|#define LSU_CONTROL_PR&t;&t;0x0000000001000000 /* Phys-read watchpoint enable   */
DECL|macro|LSU_CONTROL_PW
mdefine_line|#define LSU_CONTROL_PW&t;&t;0x0000000000800000 /* Phys-write watchpoint enable  */
DECL|macro|LSU_CONTROL_VR
mdefine_line|#define LSU_CONTROL_VR&t;&t;0x0000000000400000 /* Virt-read watchpoint enable   */
DECL|macro|LSU_CONTROL_VW
mdefine_line|#define LSU_CONTROL_VW&t;&t;0x0000000000200000 /* Virt-write watchpoint enable  */
DECL|macro|LSU_CONTROL_FM
mdefine_line|#define LSU_CONTROL_FM&t;&t;0x00000000000ffff0 /* Parity mask enables.          */
DECL|macro|LSU_CONTROL_DM
mdefine_line|#define LSU_CONTROL_DM&t;&t;0x0000000000000008 /* Data MMU enable.              */
DECL|macro|LSU_CONTROL_IM
mdefine_line|#define LSU_CONTROL_IM&t;&t;0x0000000000000004 /* Instruction MMU enable.       */
DECL|macro|LSU_CONTROL_DC
mdefine_line|#define LSU_CONTROL_DC&t;&t;0x0000000000000002 /* Data cache enable.            */
DECL|macro|LSU_CONTROL_IC
mdefine_line|#define LSU_CONTROL_IC&t;&t;0x0000000000000001 /* Instruction cache enable.     */
macro_line|#endif /* !(_SPARC64_LSU_H) */
eof
