multiline_comment|/*&n; *&t;include/asm-mips/dec/kn05.h&n; *&n; *&t;DECstation 5000/260 (4max+ or KN05) and DECsystem 5900/260&n; *&t;definitions.&n; *&n; *&t;Copyright (C) 2002, 2003  Maciej W. Rozycki&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;WARNING!  All this information is pure guesswork based on the&n; *&t;ROM.  It is provided here in hope it will give someone some&n; *&t;food for thought.  No documentation for the KN05 module has&n; *&t;been located so far.&n; */
macro_line|#ifndef __ASM_MIPS_DEC_KN05_H
DECL|macro|__ASM_MIPS_DEC_KN05_H
mdefine_line|#define __ASM_MIPS_DEC_KN05_H
macro_line|#include &lt;asm/dec/ioasic_addrs.h&gt;
multiline_comment|/*&n; * The oncard MB (Memory Buffer) ASIC provides an additional address&n; * decoder.  Certain address ranges within the &quot;high&quot; 16 slots are&n; * passed to the I/O ASIC&squot;s decoder like with the KN03.  Others are&n; * handled locally.  &quot;Low&quot; slots are always passed.&n; */
DECL|macro|KN05_MB_ROM
mdefine_line|#define KN05_MB_ROM&t;(16*IOASIC_SLOT_SIZE)&t;/* KN05 card ROM */
DECL|macro|KN05_IOCTL
mdefine_line|#define KN05_IOCTL&t;(17*IOASIC_SLOT_SIZE)&t;/* I/O ASIC */
DECL|macro|KN05_ESAR
mdefine_line|#define KN05_ESAR&t;(18*IOASIC_SLOT_SIZE)&t;/* LANCE MAC address chip */
DECL|macro|KN05_LANCE
mdefine_line|#define KN05_LANCE&t;(19*IOASIC_SLOT_SIZE)&t;/* LANCE Ethernet */
DECL|macro|KN05_MB_INT
mdefine_line|#define KN05_MB_INT&t;(20*IOASIC_SLOT_SIZE)&t;/* MB interrupt register */
DECL|macro|KN05_MB_EA
mdefine_line|#define KN05_MB_EA&t;(21*IOASIC_SLOT_SIZE)&t;/* MB error address? */
DECL|macro|KN05_MB_EC
mdefine_line|#define KN05_MB_EC&t;(22*IOASIC_SLOT_SIZE)&t;/* MB error ??? */
DECL|macro|KN05_MB_CSR
mdefine_line|#define KN05_MB_CSR&t;(23*IOASIC_SLOT_SIZE)&t;/* MB control &amp; status */
DECL|macro|KN05_RES_24
mdefine_line|#define KN05_RES_24&t;(24*IOASIC_SLOT_SIZE)&t;/* unused? */
DECL|macro|KN05_RES_25
mdefine_line|#define KN05_RES_25&t;(25*IOASIC_SLOT_SIZE)&t;/* unused? */
DECL|macro|KN05_RES_26
mdefine_line|#define KN05_RES_26&t;(26*IOASIC_SLOT_SIZE)&t;/* unused? */
DECL|macro|KN05_RES_27
mdefine_line|#define KN05_RES_27&t;(27*IOASIC_SLOT_SIZE)&t;/* unused? */
DECL|macro|KN05_SCSI
mdefine_line|#define KN05_SCSI&t;(28*IOASIC_SLOT_SIZE)&t;/* ASC SCSI */
DECL|macro|KN05_RES_29
mdefine_line|#define KN05_RES_29&t;(29*IOASIC_SLOT_SIZE)&t;/* unused? */
DECL|macro|KN05_RES_30
mdefine_line|#define KN05_RES_30&t;(30*IOASIC_SLOT_SIZE)&t;/* unused? */
DECL|macro|KN05_RES_31
mdefine_line|#define KN05_RES_31&t;(31*IOASIC_SLOT_SIZE)&t;/* unused? */
multiline_comment|/*&n; * Bits for the MB interrupt register.&n; * The register appears read-only.&n; */
DECL|macro|KN05_MB_INT_TC
mdefine_line|#define KN05_MB_INT_TC&t;&t;(1&lt;&lt;0)&t;&t;/* TURBOchannel? */
DECL|macro|KN05_MB_INT_RTC
mdefine_line|#define KN05_MB_INT_RTC&t;&t;(1&lt;&lt;1)&t;&t;/* RTC? */
multiline_comment|/*&n; * Bits for the MB control &amp; status register.&n; * Set to 0x00bf8001 on my system by the ROM.&n; */
DECL|macro|KN05_MB_CSR_PF
mdefine_line|#define KN05_MB_CSR_PF&t;&t;(1&lt;&lt;0)&t;&t;/* PreFetching enable? */
DECL|macro|KN05_MB_CSR_F
mdefine_line|#define KN05_MB_CSR_F&t;&t;(1&lt;&lt;1)&t;&t;/* ??? */
DECL|macro|KN05_MB_CSR_ECC
mdefine_line|#define KN05_MB_CSR_ECC&t;&t;(0xff&lt;&lt;2)&t;/* ??? */
DECL|macro|KN05_MB_CSR_OD
mdefine_line|#define KN05_MB_CSR_OD&t;&t;(1&lt;&lt;10)&t;&t;/* ??? */
DECL|macro|KN05_MB_CSR_CP
mdefine_line|#define KN05_MB_CSR_CP&t;&t;(1&lt;&lt;11)&t;&t;/* ??? */
DECL|macro|KN05_MB_CSR_UNC
mdefine_line|#define KN05_MB_CSR_UNC&t;&t;(1&lt;&lt;12)&t;&t;/* ??? */
DECL|macro|KN05_MB_CSR_IM
mdefine_line|#define KN05_MB_CSR_IM&t;&t;(1&lt;&lt;13)&t;&t;/* ??? */
DECL|macro|KN05_MB_CSR_NC
mdefine_line|#define KN05_MB_CSR_NC&t;&t;(1&lt;&lt;14)&t;&t;/* ??? */
DECL|macro|KN05_MB_CSR_EE
mdefine_line|#define KN05_MB_CSR_EE&t;&t;(1&lt;&lt;15)&t;&t;/* (bus) Exception Enable? */
DECL|macro|KN05_MB_CSR_MSK
mdefine_line|#define KN05_MB_CSR_MSK&t;&t;(0x1f&lt;&lt;16)&t;/* ??? */
DECL|macro|KN05_MB_CSR_FW
mdefine_line|#define KN05_MB_CSR_FW&t;&t;(1&lt;&lt;21)&t;&t;/* ??? */
macro_line|#endif /* __ASM_MIPS_DEC_KN05_H */
eof
