multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/cayman.h&n; *&n; * Cayman definitions&n; *&n; * Global defintions for the SH5 Cayman board&n; *&n; * Copyright (C) 2002 Stuart Menefy&n; */
multiline_comment|/* Setup for the SMSC FDC37C935 / LAN91C100FD */
DECL|macro|SMSC_IRQ
mdefine_line|#define SMSC_IRQ         IRQ_IRL1
multiline_comment|/* Setup for PCI Bus 2, which transmits interrupts via the EPLD */
DECL|macro|PCI2_IRQ
mdefine_line|#define PCI2_IRQ         IRQ_IRL3
eof
