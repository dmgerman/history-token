multiline_comment|/*******************************************************************************&n;*&n;*   (c) 1998 by Computone Corporation&n;*&n;********************************************************************************&n;*&n;*&n;*   PACKAGE:     Linux tty Device Driver for IntelliPort II family of multiport&n;*                serial I/O controllers.&n;*&n;*   DESCRIPTION: Driver constants for configuration and tuning&n;*&n;*   NOTES:&n;*&n;*******************************************************************************/
macro_line|#ifndef IP2IOCTL_H
DECL|macro|IP2IOCTL_H
mdefine_line|#define IP2IOCTL_H
singleline_comment|//*************
singleline_comment|//* Constants *
singleline_comment|//*************
singleline_comment|// High baud rates (if not defined elsewhere.
macro_line|#ifndef B153600   
DECL|macro|B153600
macro_line|#&t;define B153600   0010005
macro_line|#endif
macro_line|#ifndef B307200   
DECL|macro|B307200
macro_line|#&t;define B307200   0010006
macro_line|#endif
macro_line|#ifndef B921600   
DECL|macro|B921600
macro_line|#&t;define B921600   0010007
macro_line|#endif
macro_line|#endif
eof
