multiline_comment|/* $Id: sgi.h,v 1.1.1.1 1997/06/01 03:17:12 ralf Exp $&n; * sgi.h: Definitions specific to SGI machines.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@sgi.com)&n; */
macro_line|#ifndef _MIPS_SGI_H
DECL|macro|_MIPS_SGI_H
mdefine_line|#define _MIPS_SGI_H
multiline_comment|/* UP=UniProcessor MP=MultiProcessor(capable) */
DECL|enum|sgi_mach
r_enum
id|sgi_mach
(brace
DECL|enumerator|ip4
id|ip4
comma
multiline_comment|/* R2k UP */
DECL|enumerator|ip5
id|ip5
comma
multiline_comment|/* R2k MP */
DECL|enumerator|ip6
id|ip6
comma
multiline_comment|/* R3k UP */
DECL|enumerator|ip7
id|ip7
comma
multiline_comment|/* R3k MP */
DECL|enumerator|ip9
id|ip9
comma
multiline_comment|/* R3k UP */
DECL|enumerator|ip12
id|ip12
comma
multiline_comment|/* R3kA UP, Indigo */
DECL|enumerator|ip15
id|ip15
comma
multiline_comment|/* R3kA MP */
DECL|enumerator|ip17
id|ip17
comma
multiline_comment|/* R4K UP */
DECL|enumerator|ip19
id|ip19
comma
multiline_comment|/* R4K MP */
DECL|enumerator|ip20
id|ip20
comma
multiline_comment|/* R4K UP, Indigo */
DECL|enumerator|ip21
id|ip21
comma
multiline_comment|/* TFP MP */
DECL|enumerator|ip22
id|ip22
comma
multiline_comment|/* R4x00 UP, Indigo2 */
DECL|enumerator|ip25
id|ip25
comma
multiline_comment|/* R10k MP */
DECL|enumerator|ip26
id|ip26
comma
multiline_comment|/* TFP UP, Indigo2 */
DECL|enumerator|ip28
id|ip28
comma
multiline_comment|/* R10k UP, Indigo2 */
DECL|enumerator|ip30
id|ip30
comma
DECL|enumerator|ip32
id|ip32
comma
)brace
suffix:semicolon
r_extern
r_enum
id|sgi_mach
id|sgimach
suffix:semicolon
r_extern
r_void
id|sgi_sysinit
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Many I/O space registers are byte sized and are contained within&n; * one byte per word, specifically the MSB, this macro helps out.&n; */
macro_line|#ifdef __MIPSEL__
DECL|macro|SGI_MSB
mdefine_line|#define SGI_MSB(regaddr)   (regaddr)
macro_line|#else
DECL|macro|SGI_MSB
mdefine_line|#define SGI_MSB(regaddr)   ((regaddr) | 0x3)
macro_line|#endif
macro_line|#endif /* !(_MIPS_SGI_H) */
eof
