multiline_comment|/*&n; * Adaptec AIC79xx device driver for Linux.&n; *&n; * Copyright (c) 2000-2001 Adaptec Inc.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; *&n; * $Id$&n; *&n; */
macro_line|#ifndef _AIC79XX_PCI_H_
DECL|macro|_AIC79XX_PCI_H_
mdefine_line|#define _AIC79XX_PCI_H_
DECL|macro|ID_ALL_MASK
mdefine_line|#define ID_ALL_MASK&t;&t;&t;0xFFFFFFFFFFFFFFFFull
DECL|macro|ID_ALL_IROC_MASK
mdefine_line|#define ID_ALL_IROC_MASK&t;&t;0xFF7FFFFFFFFFFFFFull
DECL|macro|ID_DEV_VENDOR_MASK
mdefine_line|#define ID_DEV_VENDOR_MASK&t;&t;0xFFFFFFFF00000000ull
DECL|macro|ID_9005_GENERIC_MASK
mdefine_line|#define ID_9005_GENERIC_MASK&t;&t;0xFFF0FFFF00000000ull
DECL|macro|ID_9005_GENERIC_IROC_MASK
mdefine_line|#define ID_9005_GENERIC_IROC_MASK&t;0xFF70FFFF00000000ull
DECL|macro|ID_AIC7901
mdefine_line|#define ID_AIC7901&t;&t;&t;0x800F9005FFFF9005ull
DECL|macro|ID_AHA_29320A
mdefine_line|#define ID_AHA_29320A&t;&t;&t;0x8000900500609005ull
DECL|macro|ID_AHA_29320ALP
mdefine_line|#define ID_AHA_29320ALP&t;&t;&t;0x8017900500449005ull
DECL|macro|ID_AIC7901A
mdefine_line|#define ID_AIC7901A&t;&t;&t;0x801E9005FFFF9005ull
DECL|macro|ID_AHA_29320
mdefine_line|#define ID_AHA_29320&t;&t;&t;0x8012900500429005ull
DECL|macro|ID_AHA_29320B
mdefine_line|#define ID_AHA_29320B&t;&t;&t;0x8013900500439005ull
DECL|macro|ID_AHA_29320LP
mdefine_line|#define ID_AHA_29320LP&t;&t;&t;0x8014900500449005ull
DECL|macro|ID_AIC7902
mdefine_line|#define ID_AIC7902&t;&t;&t;0x801F9005FFFF9005ull
DECL|macro|ID_AIC7902_B
mdefine_line|#define ID_AIC7902_B&t;&t;&t;0x801D9005FFFF9005ull
DECL|macro|ID_AHA_39320
mdefine_line|#define ID_AHA_39320&t;&t;&t;0x8010900500409005ull
DECL|macro|ID_AHA_39320_B
mdefine_line|#define ID_AHA_39320_B&t;&t;&t;0x8015900500409005ull
DECL|macro|ID_AHA_39320A
mdefine_line|#define ID_AHA_39320A&t;&t;&t;0x8016900500409005ull
DECL|macro|ID_AHA_39320D
mdefine_line|#define ID_AHA_39320D&t;&t;&t;0x8011900500419005ull
DECL|macro|ID_AHA_39320D_B
mdefine_line|#define ID_AHA_39320D_B&t;&t;&t;0x801C900500419005ull
DECL|macro|ID_AHA_39320D_HP
mdefine_line|#define ID_AHA_39320D_HP&t;&t;0x8011900500AC0E11ull
DECL|macro|ID_AHA_39320D_B_HP
mdefine_line|#define ID_AHA_39320D_B_HP&t;&t;0x801C900500AC0E11ull
macro_line|#endif /* _AIC79XX_PCI_H_ */
eof
