multiline_comment|/*&n; *  System-common area definitions for NEC PC-9800 series&n; *&n; *  Copyright (C) 1999&t;TAKAI Kousuke &lt;tak@kmc.kyoto-u.ac.jp&gt;,&n; *&t;&t;&t;Kyoto University Microcomputer Club.&n; */
macro_line|#ifndef _ASM_I386_PC9800SCA_H_
DECL|macro|_ASM_I386_PC9800SCA_H_
mdefine_line|#define _ASM_I386_PC9800SCA_H_
DECL|macro|PC9800SCA_EXPMMSZ
mdefine_line|#define PC9800SCA_EXPMMSZ&t;&t;(0x0401)&t;/* B */
DECL|macro|PC9800SCA_SCSI_PARAMS
mdefine_line|#define PC9800SCA_SCSI_PARAMS&t;&t;(0x0460)&t;/* 8 * 4B */
DECL|macro|PC9800SCA_DISK_EQUIPS
mdefine_line|#define PC9800SCA_DISK_EQUIPS&t;&t;(0x0482)&t;/* B */
DECL|macro|PC9800SCA_XROM_ID
mdefine_line|#define PC9800SCA_XROM_ID&t;&t;(0x04C0)&t;/* 52B */
DECL|macro|PC9800SCA_BIOS_FLAG
mdefine_line|#define PC9800SCA_BIOS_FLAG&t;&t;(0x0501)&t;/* B */
DECL|macro|PC9800SCA_MMSZ16M
mdefine_line|#define PC9800SCA_MMSZ16M&t;&t;(0x0594)&t;/* W */
multiline_comment|/* PC-9821 have additional system common area in their BIOS-ROM segment. */
DECL|macro|PC9821SCA__BASE
mdefine_line|#define PC9821SCA__BASE&t;&t;&t;(0xF8E8 &lt;&lt; 4)
DECL|macro|PC9821SCA_ROM_ID
mdefine_line|#define PC9821SCA_ROM_ID&t;&t;(PC9821SCA__BASE + 0x00)
DECL|macro|PC9821SCA_ROM_FLAG4
mdefine_line|#define PC9821SCA_ROM_FLAG4&t;&t;(PC9821SCA__BASE + 0x05)
DECL|macro|PC9821SCA_RSFLAGS
mdefine_line|#define PC9821SCA_RSFLAGS&t;&t;(PC9821SCA__BASE + 0x11)&t;/* B */
macro_line|#endif /* !_ASM_I386_PC9800SCA_H_ */
eof
