macro_line|#ifndef __PPC_BOOT_CPC700_H
DECL|macro|__PPC_BOOT_CPC700_H
mdefine_line|#define __PPC_BOOT_CPC700_H
DECL|macro|CPC700_MEM_CFGADDR
mdefine_line|#define CPC700_MEM_CFGADDR    0xff500008
DECL|macro|CPC700_MEM_CFGDATA
mdefine_line|#define CPC700_MEM_CFGDATA    0xff50000c
DECL|macro|CPC700_MB0SA
mdefine_line|#define CPC700_MB0SA            0x38
DECL|macro|CPC700_MB0EA
mdefine_line|#define CPC700_MB0EA            0x58
DECL|macro|CPC700_MB1SA
mdefine_line|#define CPC700_MB1SA            0x3c
DECL|macro|CPC700_MB1EA
mdefine_line|#define CPC700_MB1EA            0x5c
DECL|macro|CPC700_MB2SA
mdefine_line|#define CPC700_MB2SA            0x40
DECL|macro|CPC700_MB2EA
mdefine_line|#define CPC700_MB2EA            0x60
DECL|macro|CPC700_MB3SA
mdefine_line|#define CPC700_MB3SA            0x44
DECL|macro|CPC700_MB3EA
mdefine_line|#define CPC700_MB3EA            0x64
DECL|macro|CPC700_MB4SA
mdefine_line|#define CPC700_MB4SA            0x48
DECL|macro|CPC700_MB4EA
mdefine_line|#define CPC700_MB4EA            0x68
r_static
r_inline
r_int
DECL|function|cpc700_read_memreg
id|cpc700_read_memreg
c_func
(paren
r_int
id|reg
)paren
(brace
id|out_be32
c_func
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|CPC700_MEM_CFGADDR
comma
id|reg
)paren
suffix:semicolon
r_return
id|in_be32
c_func
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|CPC700_MEM_CFGDATA
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
