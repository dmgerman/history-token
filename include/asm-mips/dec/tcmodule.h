multiline_comment|/* &n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Offsets for the ROM header locations for&n; * TURBOchannel cards&n; *&n; * created from:&n; *&n; * TURBOchannel Firmware Specification&n; *&n; * EK-TCAAD-FS-004&n; * from Digital Equipment Corporation&n; *&n; * Jan.1998 Harald Koerfgen&n; */
macro_line|#ifndef __ASM_DEC_TCMOULE_H
DECL|macro|__ASM_DEC_TCMOULE_H
mdefine_line|#define __ASM_DEC_TCMOULE_H
DECL|macro|OLDCARD
mdefine_line|#define OLDCARD 0x3c0000
DECL|macro|TC_ROM_WIDTH
mdefine_line|#define TC_ROM_WIDTH&t;0x3e0
DECL|macro|TC_ROM_STRIDE
mdefine_line|#define TC_ROM_STRIDE&t;0x3e4
DECL|macro|TC_ROM_SIZE
mdefine_line|#define TC_ROM_SIZE&t;0x3e8
DECL|macro|TC_SLOT_SIZE
mdefine_line|#define TC_SLOT_SIZE&t;0x3ec
DECL|macro|TC_PATTERN0
mdefine_line|#define TC_PATTERN0&t;0x3f0
DECL|macro|TC_PATTERN1
mdefine_line|#define TC_PATTERN1&t;0x3f4
DECL|macro|TC_PATTERN2
mdefine_line|#define TC_PATTERN2&t;0x3f8
DECL|macro|TC_PATTERN3
mdefine_line|#define TC_PATTERN3&t;0x3fc
DECL|macro|TC_FIRM_VER
mdefine_line|#define TC_FIRM_VER&t;0x400
DECL|macro|TC_VENDOR
mdefine_line|#define TC_VENDOR&t;0x420
DECL|macro|TC_MODULE
mdefine_line|#define TC_MODULE&t;0x440
DECL|macro|TC_FIRM_TYPE
mdefine_line|#define TC_FIRM_TYPE&t;0x460
DECL|macro|TC_FLAGS
mdefine_line|#define TC_FLAGS&t;0x470
DECL|macro|TC_ROM_OBJECTS
mdefine_line|#define TC_ROM_OBJECTS&t;0x480
macro_line|#endif /* __ASM_DEC_TCMOULE_H */
eof
