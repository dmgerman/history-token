multiline_comment|/*&n; *&n; *  drivers/scsi/pc980155.h&n; *&n; *  PC-9801-55 SCSI host adapter driver&n; *&n; *  Copyright (C) 1997-2003  Kyoto University Microcomputer Club&n; *&t;&t;&t;     (Linux/98 project)&n; *&t;&t;&t;     Tomoharu Ugawa &lt;ohirune@kmc.gr.jp&gt;&n; *&n; */
macro_line|#ifndef __PC980155_H
DECL|macro|__PC980155_H
mdefine_line|#define __PC980155_H
macro_line|#include &quot;wd33c93.h&quot;
DECL|macro|REG_ADDRST
mdefine_line|#define REG_ADDRST (base_io)
DECL|macro|REG_CONTRL
mdefine_line|#define REG_CONTRL (base_io + 2)
DECL|macro|REG_CWRITE
mdefine_line|#define REG_CWRITE (base_io + 4)
DECL|macro|REG_STATRD
mdefine_line|#define REG_STATRD (base_io + 4)
DECL|macro|WD_MEMORYBANK
mdefine_line|#define WD_MEMORYBANK&t;0x30
DECL|macro|WD_RESETINT
mdefine_line|#define WD_RESETINT&t;0x33
DECL|function|read_pc980155
r_static
r_inline
id|uchar
id|read_pc980155
c_func
(paren
r_const
id|wd33c93_regs
id|regs
comma
id|uchar
id|reg_num
)paren
(brace
id|outb
c_func
(paren
id|reg_num
comma
id|regs.SASR
)paren
suffix:semicolon
r_return
(paren
id|uchar
)paren
id|inb
c_func
(paren
id|regs.SCMD
)paren
suffix:semicolon
)brace
DECL|function|write_memorybank
r_static
r_inline
r_void
id|write_memorybank
c_func
(paren
r_const
id|wd33c93_regs
id|regs
comma
id|uchar
id|value
)paren
(brace
id|outb
c_func
(paren
id|WD_MEMORYBANK
comma
id|regs.SASR
)paren
suffix:semicolon
id|outb
c_func
(paren
id|value
comma
id|regs.SCMD
)paren
suffix:semicolon
)brace
DECL|macro|read_pc980155_resetint
mdefine_line|#define read_pc980155_resetint(regs) &bslash;&n;&t;read_pc980155((regs), WD_RESETINT)
DECL|macro|pc980155_int_enable
mdefine_line|#define pc980155_int_enable(regs) &bslash;&n;&t;write_memorybank((regs), read_pc980155((regs), WD_MEMORYBANK) | 0x04)
DECL|macro|pc980155_int_disable
mdefine_line|#define pc980155_int_disable(regs) &bslash;&n;&t;write_memorybank((regs), read_pc980155((regs), WD_MEMORYBANK) &amp; ~0x04)
DECL|macro|pc980155_assert_bus_reset
mdefine_line|#define pc980155_assert_bus_reset(regs) &bslash;&n;&t;write_memorybank((regs), read_pc980155((regs), WD_MEMORYBANK) | 0x02)
DECL|macro|pc980155_negate_bus_reset
mdefine_line|#define pc980155_negate_bus_reset(regs) &bslash;&n;&t;write_memorybank((regs), read_pc980155((regs), WD_MEMORYBANK) &amp; ~0x02)
macro_line|#endif /* __PC980155_H */
eof
