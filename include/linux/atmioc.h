multiline_comment|/* atmioc.h - ranges for ATM-related ioctl numbers */
multiline_comment|/* Written 1995-1999 by Werner Almesberger, EPFL LRC/ICA */
multiline_comment|/*&n; * See http://icawww1.epfl.ch/linux-atm/magic.html for the complete list of&n; * &quot;magic&quot; ioctl numbers.&n; */
macro_line|#ifndef _LINUX_ATMIOC_H
DECL|macro|_LINUX_ATMIOC_H
mdefine_line|#define _LINUX_ATMIOC_H
macro_line|#include &lt;asm/ioctl.h&gt;
multiline_comment|/* everybody including atmioc.h will also need _IO{,R,W,WR} */
DECL|macro|ATMIOC_PHYCOM
mdefine_line|#define ATMIOC_PHYCOM&t;  0x00 /* PHY device common ioctls, globally unique */
DECL|macro|ATMIOC_PHYCOM_END
mdefine_line|#define ATMIOC_PHYCOM_END 0x0f
DECL|macro|ATMIOC_PHYTYP
mdefine_line|#define ATMIOC_PHYTYP&t;  0x10 /* PHY dev type ioctls, unique per PHY type */
DECL|macro|ATMIOC_PHYTYP_END
mdefine_line|#define ATMIOC_PHYTYP_END 0x2f
DECL|macro|ATMIOC_PHYPRV
mdefine_line|#define ATMIOC_PHYPRV&t;  0x30 /* PHY dev private ioctls, unique per driver */
DECL|macro|ATMIOC_PHYPRV_END
mdefine_line|#define ATMIOC_PHYPRV_END 0x4f
DECL|macro|ATMIOC_SARCOM
mdefine_line|#define ATMIOC_SARCOM&t;  0x50 /* SAR device common ioctls, globally unique */
DECL|macro|ATMIOC_SARCOM_END
mdefine_line|#define ATMIOC_SARCOM_END 0x50
DECL|macro|ATMIOC_SARPRV
mdefine_line|#define ATMIOC_SARPRV&t;  0x60 /* SAR dev private ioctls, unique per driver */
DECL|macro|ATMIOC_SARPRV_END
mdefine_line|#define ATMIOC_SARPRV_END 0x7f
DECL|macro|ATMIOC_ITF
mdefine_line|#define ATMIOC_ITF&t;  0x80 /* Interface ioctls, globally unique */
DECL|macro|ATMIOC_ITF_END
mdefine_line|#define ATMIOC_ITF_END&t;  0x8f
DECL|macro|ATMIOC_BACKEND
mdefine_line|#define ATMIOC_BACKEND&t;  0x90 /* ATM generic backend ioctls, u. per backend */
DECL|macro|ATMIOC_BACKEND_END
mdefine_line|#define ATMIOC_BACKEND_END 0xaf
multiline_comment|/* 0xb0-0xbf: Reserved for future use */
DECL|macro|ATMIOC_AREQUIPA
mdefine_line|#define ATMIOC_AREQUIPA&t;  0xc0 /* Application requested IP over ATM, glob. u. */
DECL|macro|ATMIOC_LANE
mdefine_line|#define ATMIOC_LANE&t;  0xd0 /* LAN Emulation, globally unique */
DECL|macro|ATMIOC_MPOA
mdefine_line|#define ATMIOC_MPOA       0xd8 /* MPOA, globally unique */
DECL|macro|ATMIOC_CLIP
mdefine_line|#define&t;ATMIOC_CLIP&t;  0xe0 /* Classical IP over ATM control, globally u. */
DECL|macro|ATMIOC_CLIP_END
mdefine_line|#define&t;ATMIOC_CLIP_END&t;  0xef
DECL|macro|ATMIOC_SPECIAL
mdefine_line|#define&t;ATMIOC_SPECIAL&t;  0xf0 /* Special-purpose controls, globally unique */
DECL|macro|ATMIOC_SPECIAL_END
mdefine_line|#define&t;ATMIOC_SPECIAL_END 0xff
macro_line|#endif
eof
