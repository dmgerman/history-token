multiline_comment|/*&n; *  linux/include/asm-arm/arch-pxa/serial.h&n; *&n; * Author:&t;Nicolas Pitre&n; * Copyright:&t;(C) 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
DECL|macro|BAUD_BASE
mdefine_line|#define BAUD_BASE&t;921600
multiline_comment|/* Standard COM flags */
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_SKIP_TEST)
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;5
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS&t;&bslash;&n;&t;{&t;&bslash;&n;&t;&t;type:&t;&t;&t;PORT_PXA,&t;&bslash;&n;&t;&t;xmit_fifo_size:&t;&t;64,&t;&t;&bslash;&n;&t;&t;baud_base:&t;&t;BAUD_BASE,&t;&bslash;&n;&t;&t;iomem_base:&t;&t;&amp;FFUART,&t;&bslash;&n;&t;&t;iomem_reg_shift:&t;2,&t;&t;&bslash;&n;&t;&t;io_type:&t;&t;SERIAL_IO_MEM,&t;&bslash;&n;&t;&t;irq:&t;&t;&t;IRQ_FFUART,&t;&bslash;&n;&t;&t;flags:&t;&t;&t;STD_COM_FLAGS,&t;&bslash;&n;&t;}, {&t;&bslash;&n;&t;&t;type:&t;&t;&t;PORT_PXA,&t;&bslash;&n;&t;&t;xmit_fifo_size:&t;&t;64,&t;&t;&bslash;&n;&t;&t;baud_base:&t;&t;BAUD_BASE,&t;&bslash;&n;&t;&t;iomem_base:&t;&t;&amp;STUART,&t;&bslash;&n;&t;&t;iomem_reg_shift:&t;2,&t;&t;&bslash;&n;&t;&t;io_type:&t;&t;SERIAL_IO_MEM,&t;&bslash;&n;&t;&t;irq:&t;&t;&t;IRQ_STUART,&t;&bslash;&n;&t;&t;flags:&t;&t;&t;STD_COM_FLAGS,&t;&bslash;&n;&t;}, {&t;&bslash;&n;&t;&t;type:&t;&t;&t;PORT_PXA,&t;&bslash;&n;&t;&t;xmit_fifo_size:&t;&t;64,&t;&t;&bslash;&n;&t;&t;baud_base:&t;&t;BAUD_BASE,&t;&bslash;&n;&t;&t;iomem_base:&t;&t;&amp;BTUART,&t;&bslash;&n;&t;&t;iomem_reg_shift:&t;2,&t;&t;&bslash;&n;&t;&t;io_type:&t;&t;SERIAL_IO_MEM,&t;&bslash;&n;&t;&t;irq:&t;&t;&t;IRQ_BTUART,&t;&bslash;&n;&t;&t;flags:&t;&t;&t;STD_COM_FLAGS,&t;&bslash;&n;&t;}
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS
eof
