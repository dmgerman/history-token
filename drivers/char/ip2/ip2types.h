multiline_comment|/*******************************************************************************&n;*&n;*   (c) 1998 by Computone Corporation&n;*&n;********************************************************************************&n;*&n;*&n;*   PACKAGE:     Linux tty Device Driver for IntelliPort II family of multiport&n;*                serial I/O controllers.&n;*&n;*   DESCRIPTION: Driver constants and type definitions.&n;*&n;*   NOTES:&n;*&n;*******************************************************************************/
macro_line|#ifndef IP2TYPES_H
DECL|macro|IP2TYPES_H
mdefine_line|#define IP2TYPES_H
singleline_comment|//*************
singleline_comment|//* Constants *
singleline_comment|//*************
singleline_comment|// Define some limits for this driver. Ports per board is a hardware limitation
singleline_comment|// that will not change. Current hardware limits this to 64 ports per board.
singleline_comment|// Boards per driver is a self-imposed limit.
singleline_comment|//
DECL|macro|IP2_MAX_BOARDS
mdefine_line|#define IP2_MAX_BOARDS        4
DECL|macro|IP2_PORTS_PER_BOARD
mdefine_line|#define IP2_PORTS_PER_BOARD   ABS_MOST_PORTS
DECL|macro|IP2_MAX_PORTS
mdefine_line|#define IP2_MAX_PORTS         (IP2_MAX_BOARDS*IP2_PORTS_PER_BOARD)
DECL|macro|ISA
mdefine_line|#define ISA    0
DECL|macro|PCI
mdefine_line|#define PCI    1
DECL|macro|EISA
mdefine_line|#define EISA   2
singleline_comment|//********************
singleline_comment|//* Type Definitions *
singleline_comment|//********************
DECL|typedef|PTTY
r_typedef
r_struct
id|tty_struct
op_star
id|PTTY
suffix:semicolon
DECL|typedef|PWAITQ
r_typedef
id|wait_queue_head_t
id|PWAITQ
suffix:semicolon
DECL|typedef|UCHAR
r_typedef
r_int
r_char
id|UCHAR
suffix:semicolon
DECL|typedef|UINT
r_typedef
r_int
r_int
id|UINT
suffix:semicolon
DECL|typedef|USHORT
r_typedef
r_int
r_int
id|USHORT
suffix:semicolon
DECL|typedef|ULONG
r_typedef
r_int
r_int
id|ULONG
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|irq
r_int
id|irq
(braket
id|IP2_MAX_BOARDS
)braket
suffix:semicolon
DECL|member|addr
r_int
r_int
id|addr
(braket
id|IP2_MAX_BOARDS
)braket
suffix:semicolon
DECL|member|type
r_int
id|type
(braket
id|IP2_MAX_BOARDS
)braket
suffix:semicolon
DECL|typedef|ip2config_t
)brace
id|ip2config_t
suffix:semicolon
macro_line|#endif
eof
