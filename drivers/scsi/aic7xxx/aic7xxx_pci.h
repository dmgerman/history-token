multiline_comment|/*&n; * Adaptec AIC7xxx device driver for Linux.&n; *&n; * Copyright (c) 2000-2001 Adaptec Inc.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; *&n; * $Id$&n; *&n; */
macro_line|#ifndef _AIC7XXX_PCI_H_
DECL|macro|_AIC7XXX_PCI_H_
mdefine_line|#define _AIC7XXX_PCI_H_
DECL|macro|ID_ALL_MASK
mdefine_line|#define ID_ALL_MASK&t;&t;&t;0xFFFFFFFFFFFFFFFFull
DECL|macro|ID_DEV_VENDOR_MASK
mdefine_line|#define ID_DEV_VENDOR_MASK&t;&t;0xFFFFFFFF00000000ull
DECL|macro|ID_9005_GENERIC_MASK
mdefine_line|#define ID_9005_GENERIC_MASK&t;&t;0xFFF0FFFF00000000ull
DECL|macro|ID_9005_SISL_MASK
mdefine_line|#define ID_9005_SISL_MASK&t;&t;0x000FFFFF00000000ull
DECL|macro|ID_9005_SISL_ID
mdefine_line|#define ID_9005_SISL_ID&t;&t;&t;0x0005900500000000ull
DECL|macro|ID_AIC7850
mdefine_line|#define ID_AIC7850&t;&t;&t;0x5078900400000000ull
DECL|macro|ID_AHA_2902_04_10_15_20C_30C
mdefine_line|#define ID_AHA_2902_04_10_15_20C_30C&t;0x5078900478509004ull
DECL|macro|ID_AIC7855
mdefine_line|#define ID_AIC7855&t;&t;&t;0x5578900400000000ull
DECL|macro|ID_AIC7859
mdefine_line|#define ID_AIC7859&t;&t;&t;0x3860900400000000ull
DECL|macro|ID_AHA_2930CU
mdefine_line|#define ID_AHA_2930CU&t;&t;&t;0x3860900438699004ull
DECL|macro|ID_AIC7860
mdefine_line|#define ID_AIC7860&t;&t;&t;0x6078900400000000ull
DECL|macro|ID_AIC7860C
mdefine_line|#define ID_AIC7860C&t;&t;&t;0x6078900478609004ull
DECL|macro|ID_AHA_1480A
mdefine_line|#define ID_AHA_1480A&t;&t;&t;0x6075900400000000ull
DECL|macro|ID_AHA_2940AU_0
mdefine_line|#define ID_AHA_2940AU_0&t;&t;&t;0x6178900400000000ull
DECL|macro|ID_AHA_2940AU_1
mdefine_line|#define ID_AHA_2940AU_1&t;&t;&t;0x6178900478619004ull
DECL|macro|ID_AHA_2940AU_CN
mdefine_line|#define ID_AHA_2940AU_CN&t;&t;0x2178900478219004ull
DECL|macro|ID_AHA_2930C_VAR
mdefine_line|#define ID_AHA_2930C_VAR&t;&t;0x6038900438689004ull
DECL|macro|ID_AIC7870
mdefine_line|#define ID_AIC7870&t;&t;&t;0x7078900400000000ull
DECL|macro|ID_AHA_2940
mdefine_line|#define ID_AHA_2940&t;&t;&t;0x7178900400000000ull
DECL|macro|ID_AHA_3940
mdefine_line|#define ID_AHA_3940&t;&t;&t;0x7278900400000000ull
DECL|macro|ID_AHA_398X
mdefine_line|#define ID_AHA_398X&t;&t;&t;0x7378900400000000ull
DECL|macro|ID_AHA_2944
mdefine_line|#define ID_AHA_2944&t;&t;&t;0x7478900400000000ull
DECL|macro|ID_AHA_3944
mdefine_line|#define ID_AHA_3944&t;&t;&t;0x7578900400000000ull
DECL|macro|ID_AHA_4944
mdefine_line|#define ID_AHA_4944&t;&t;&t;0x7678900400000000ull
DECL|macro|ID_AIC7880
mdefine_line|#define ID_AIC7880&t;&t;&t;0x8078900400000000ull
DECL|macro|ID_AIC7880_B
mdefine_line|#define ID_AIC7880_B&t;&t;&t;0x8078900478809004ull
DECL|macro|ID_AHA_2940U
mdefine_line|#define ID_AHA_2940U&t;&t;&t;0x8178900400000000ull
DECL|macro|ID_AHA_3940U
mdefine_line|#define ID_AHA_3940U&t;&t;&t;0x8278900400000000ull
DECL|macro|ID_AHA_2944U
mdefine_line|#define ID_AHA_2944U&t;&t;&t;0x8478900400000000ull
DECL|macro|ID_AHA_3944U
mdefine_line|#define ID_AHA_3944U&t;&t;&t;0x8578900400000000ull
DECL|macro|ID_AHA_398XU
mdefine_line|#define ID_AHA_398XU&t;&t;&t;0x8378900400000000ull
DECL|macro|ID_AHA_4944U
mdefine_line|#define ID_AHA_4944U&t;&t;&t;0x8678900400000000ull
DECL|macro|ID_AHA_2940UB
mdefine_line|#define ID_AHA_2940UB&t;&t;&t;0x8178900478819004ull
DECL|macro|ID_AHA_2930U
mdefine_line|#define ID_AHA_2930U&t;&t;&t;0x8878900478889004ull
DECL|macro|ID_AHA_2940U_PRO
mdefine_line|#define ID_AHA_2940U_PRO&t;&t;0x8778900478879004ull
DECL|macro|ID_AHA_2940U_CN
mdefine_line|#define ID_AHA_2940U_CN&t;&t;&t;0x0078900478009004ull
DECL|macro|ID_AIC7895
mdefine_line|#define ID_AIC7895&t;&t;&t;0x7895900478959004ull
DECL|macro|ID_AIC7895_ARO
mdefine_line|#define ID_AIC7895_ARO&t;&t;&t;0x7890900478939004ull
DECL|macro|ID_AIC7895_ARO_MASK
mdefine_line|#define ID_AIC7895_ARO_MASK&t;&t;0xFFF0FFFFFFFFFFFFull
DECL|macro|ID_AHA_2940U_DUAL
mdefine_line|#define ID_AHA_2940U_DUAL&t;&t;0x7895900478919004ull
DECL|macro|ID_AHA_3940AU
mdefine_line|#define ID_AHA_3940AU&t;&t;&t;0x7895900478929004ull
DECL|macro|ID_AHA_3944AU
mdefine_line|#define ID_AHA_3944AU&t;&t;&t;0x7895900478949004ull
DECL|macro|ID_AIC7890
mdefine_line|#define ID_AIC7890&t;&t;&t;0x001F9005000F9005ull
DECL|macro|ID_AIC7890_ARO
mdefine_line|#define ID_AIC7890_ARO&t;&t;&t;0x00139005000F9005ull
DECL|macro|ID_AAA_131U2
mdefine_line|#define ID_AAA_131U2&t;&t;&t;0x0013900500039005ull
DECL|macro|ID_AHA_2930U2
mdefine_line|#define ID_AHA_2930U2&t;&t;&t;0x0011900501819005ull
DECL|macro|ID_AHA_2940U2B
mdefine_line|#define ID_AHA_2940U2B&t;&t;&t;0x00109005A1009005ull
DECL|macro|ID_AHA_2940U2_OEM
mdefine_line|#define ID_AHA_2940U2_OEM&t;&t;0x0010900521809005ull
DECL|macro|ID_AHA_2940U2
mdefine_line|#define ID_AHA_2940U2&t;&t;&t;0x00109005A1809005ull
DECL|macro|ID_AHA_2950U2B
mdefine_line|#define ID_AHA_2950U2B&t;&t;&t;0x00109005E1009005ull
DECL|macro|ID_AIC7892
mdefine_line|#define ID_AIC7892&t;&t;&t;0x008F9005FFFF9005ull
DECL|macro|ID_AIC7892_ARO
mdefine_line|#define ID_AIC7892_ARO&t;&t;&t;0x00839005FFFF9005ull
DECL|macro|ID_AHA_29160
mdefine_line|#define ID_AHA_29160&t;&t;&t;0x00809005E2A09005ull
DECL|macro|ID_AHA_29160_CPQ
mdefine_line|#define ID_AHA_29160_CPQ&t;&t;0x00809005E2A00E11ull
DECL|macro|ID_AHA_29160N
mdefine_line|#define ID_AHA_29160N&t;&t;&t;0x0080900562A09005ull
DECL|macro|ID_AHA_29160C
mdefine_line|#define ID_AHA_29160C&t;&t;&t;0x0080900562209005ull
DECL|macro|ID_AHA_29160B
mdefine_line|#define ID_AHA_29160B&t;&t;&t;0x00809005E2209005ull
DECL|macro|ID_AHA_19160B
mdefine_line|#define ID_AHA_19160B&t;&t;&t;0x0081900562A19005ull
DECL|macro|ID_AIC7896
mdefine_line|#define ID_AIC7896&t;&t;&t;0x005F9005FFFF9005ull
DECL|macro|ID_AIC7896_ARO
mdefine_line|#define ID_AIC7896_ARO&t;&t;&t;0x00539005FFFF9005ull
DECL|macro|ID_AHA_3950U2B_0
mdefine_line|#define ID_AHA_3950U2B_0&t;&t;0x00509005FFFF9005ull
DECL|macro|ID_AHA_3950U2B_1
mdefine_line|#define ID_AHA_3950U2B_1&t;&t;0x00509005F5009005ull
DECL|macro|ID_AHA_3950U2D_0
mdefine_line|#define ID_AHA_3950U2D_0&t;&t;0x00519005FFFF9005ull
DECL|macro|ID_AHA_3950U2D_1
mdefine_line|#define ID_AHA_3950U2D_1&t;&t;0x00519005B5009005ull
DECL|macro|ID_AIC7899
mdefine_line|#define ID_AIC7899&t;&t;&t;0x00CF9005FFFF9005ull
DECL|macro|ID_AIC7899_ARO
mdefine_line|#define ID_AIC7899_ARO&t;&t;&t;0x00C39005FFFF9005ull
DECL|macro|ID_AHA_3960D
mdefine_line|#define ID_AHA_3960D&t;&t;&t;0x00C09005F6209005ull
DECL|macro|ID_AHA_3960D_CPQ
mdefine_line|#define ID_AHA_3960D_CPQ&t;&t;0x00C09005F6200E11ull
DECL|macro|ID_AIC7810
mdefine_line|#define ID_AIC7810&t;&t;&t;0x1078900400000000ull
DECL|macro|ID_AIC7815
mdefine_line|#define ID_AIC7815&t;&t;&t;0x7815900400000000ull
macro_line|#endif /* _AIC7XXX_PCI_H_ */
eof
