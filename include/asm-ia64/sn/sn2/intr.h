multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SN2_INTR_H
DECL|macro|_ASM_IA64_SN_SN2_INTR_H
mdefine_line|#define _ASM_IA64_SN_SN2_INTR_H
DECL|macro|SGI_UART_VECTOR
mdefine_line|#define SGI_UART_VECTOR (0xe9)
DECL|macro|SGI_SHUB_ERROR_VECTOR
mdefine_line|#define SGI_SHUB_ERROR_VECTOR   (0xea)
singleline_comment|// These two IRQ&squot;s are used by partitioning.
DECL|macro|SGI_XPC_NOTIFY
mdefine_line|#define SGI_XPC_NOTIFY&t;&t;&t;(0xe7)
DECL|macro|SGI_XPART_ACTIVATE
mdefine_line|#define SGI_XPART_ACTIVATE&t;&t;(0x30)
DECL|macro|IA64_SN2_FIRST_DEVICE_VECTOR
mdefine_line|#define IA64_SN2_FIRST_DEVICE_VECTOR&t;(0x31)
DECL|macro|IA64_SN2_LAST_DEVICE_VECTOR
mdefine_line|#define IA64_SN2_LAST_DEVICE_VECTOR&t;(0xe6)
DECL|macro|SN2_IRQ_RESERVED
mdefine_line|#define SN2_IRQ_RESERVED        (0x1)
DECL|macro|SN2_IRQ_CONNECTED
mdefine_line|#define SN2_IRQ_CONNECTED       (0x2)
macro_line|#endif /* _ASM_IA64_SN_SN2_INTR_H */
eof
