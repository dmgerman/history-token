macro_line|#ifndef _SPARC_BPP_H
DECL|macro|_SPARC_BPP_H
mdefine_line|#define _SPARC_BPP_H
multiline_comment|/*&n; * Copyright (c) 1995 Picture Elements&n; *&t;Stephen Williams&n; *&t;Gus Baldauf&n; *&n; * Linux/SPARC port by Peter Zaitcev.&n; * Integration into SPARC tree by Tom Dyas.&n; */
macro_line|#include  &lt;linux/ioctl.h&gt;
multiline_comment|/*&n; * This is a driver that supports IEEE Std 1284-1994 communications&n; * with compliant or compatible devices. It will use whatever features&n; * the device supports, prefering those that are typically faster.&n; *&n; * When the device is opened, it is left in COMPATABILITY mode, and&n; * writes work like any printer device. The driver only attempt to&n; * negotiate 1284 modes when needed so that plugs can be pulled,&n; * switch boxes switched, etc., without disrupting things. It will&n; * also leave the device in compatibility mode when closed.&n; */
multiline_comment|/*&n; * This driver also supplies ioctls to manually manipulate the&n; * pins. This is great for testing devices, or writing code to deal&n; * with bizzarro-mode of the ACME Special TurboThingy Plus.&n; *&n; * NOTE: These ioctl currently do not interact well with&n; * read/write. Caveat emptor.&n; *&n; * PUT_PINS allows us to assign the sense of all the pins, including&n; * the data pins if being driven by the host. The GET_PINS returns the&n; * pins that the peripheral drives, including data if appropriate.&n; */
DECL|macro|BPP_PUT_PINS
macro_line|# define BPP_PUT_PINS _IOW(&squot;B&squot;, 1, int)
DECL|macro|BPP_GET_PINS
macro_line|# define BPP_GET_PINS _IOR(&squot;B&squot;, 2, void)
DECL|macro|BPP_PUT_DATA
macro_line|# define BPP_PUT_DATA _IOW(&squot;B&squot;, 3, int)
DECL|macro|BPP_GET_DATA
macro_line|# define BPP_GET_DATA _IOR(&squot;B&squot;, 4, void)
multiline_comment|/*&n; * Set the data bus to input mode. Disengage the data bin driver and&n; * be prepared to read values from the peripheral. If the arg is 0,&n; * then revert the bus to output mode.&n; */
DECL|macro|BPP_SET_INPUT
macro_line|# define BPP_SET_INPUT _IOW(&squot;B&squot;, 5, int)
multiline_comment|/*&n; * These bits apply to the PUT operation...&n; */
DECL|macro|BPP_PP_nStrobe
macro_line|# define BPP_PP_nStrobe   0x0001
DECL|macro|BPP_PP_nAutoFd
macro_line|# define BPP_PP_nAutoFd   0x0002
DECL|macro|BPP_PP_nInit
macro_line|# define BPP_PP_nInit     0x0004
DECL|macro|BPP_PP_nSelectIn
macro_line|# define BPP_PP_nSelectIn 0x0008
multiline_comment|/*&n; * These apply to the GET operation, which also reads the current value&n; * of the previously put values. A bit mask of these will be returned&n; * as a bit mask in the return code of the ioctl().&n; */
DECL|macro|BPP_GP_nAck
macro_line|# define BPP_GP_nAck   0x0100
DECL|macro|BPP_GP_Busy
macro_line|# define BPP_GP_Busy   0x0200
DECL|macro|BPP_GP_PError
macro_line|# define BPP_GP_PError 0x0400
DECL|macro|BPP_GP_Select
macro_line|# define BPP_GP_Select 0x0800
DECL|macro|BPP_GP_nFault
macro_line|# define BPP_GP_nFault 0x1000
macro_line|#endif
eof
