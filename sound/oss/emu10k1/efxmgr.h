multiline_comment|/*     &n; **********************************************************************&n; *     sblive_fx.h&n; *     Copyright 1999, 2000 Creative Labs, Inc. &n; * &n; ********************************************************************** &n; * &n; *     Date                 Author          Summary of changes &n; *     ----                 ------          ------------------ &n; *     October 20, 1999     Bertrand Lee    base code release &n; * &n; ********************************************************************** &n; * &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version. &n; * &n; *     This program is distributed in the hope that it will be useful, &n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of &n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the &n; *     GNU General Public License for more details. &n; * &n; *     You should have received a copy of the GNU General Public &n; *     License along with this program; if not, write to the Free &n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, &n; *     USA. &n; * &n; ********************************************************************** &n; */
macro_line|#ifndef _EFXMGR_H
DECL|macro|_EFXMGR_H
mdefine_line|#define _EFXMGR_H
DECL|macro|WRITE_EFX
mdefine_line|#define WRITE_EFX(a, b, c) sblive_writeptr((a), MICROCODEBASE + (b), 0, (c))
DECL|macro|OP
mdefine_line|#define OP(op, z, w, x, y) &bslash;&n;        do { WRITE_EFX(card, (pc) * 2, ((x) &lt;&lt; 10) | (y)); &bslash;&n;        WRITE_EFX(card, (pc) * 2 + 1, ((op) &lt;&lt; 20) | ((z) &lt;&lt; 10) | (w)); &bslash;&n;        ++pc; } while (0)
DECL|macro|NUM_INPUTS
mdefine_line|#define NUM_INPUTS 0x20
DECL|macro|NUM_OUTPUTS
mdefine_line|#define NUM_OUTPUTS 0x20
DECL|macro|NUM_GPRS
mdefine_line|#define NUM_GPRS 0x100
DECL|macro|GPR_NAME_SIZE
mdefine_line|#define GPR_NAME_SIZE   32
DECL|macro|PATCH_NAME_SIZE
mdefine_line|#define PATCH_NAME_SIZE 32
DECL|struct|dsp_rpatch
r_struct
id|dsp_rpatch
(brace
DECL|member|name
r_char
id|name
(braket
id|PATCH_NAME_SIZE
)braket
suffix:semicolon
DECL|member|code_start
id|u16
id|code_start
suffix:semicolon
DECL|member|code_size
id|u16
id|code_size
suffix:semicolon
DECL|member|gpr_used
id|u32
id|gpr_used
(braket
id|NUM_GPRS
op_div
l_int|32
)braket
suffix:semicolon
DECL|member|gpr_input
id|u32
id|gpr_input
(braket
id|NUM_GPRS
op_div
l_int|32
)braket
suffix:semicolon
DECL|member|route
id|u32
id|route
(braket
id|NUM_OUTPUTS
)braket
suffix:semicolon
DECL|member|route_v
id|u32
id|route_v
(braket
id|NUM_OUTPUTS
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dsp_patch
r_struct
id|dsp_patch
(brace
DECL|member|name
r_char
id|name
(braket
id|PATCH_NAME_SIZE
)braket
suffix:semicolon
DECL|member|id
id|u8
id|id
suffix:semicolon
DECL|member|input
id|u32
id|input
suffix:semicolon
multiline_comment|/* bitmap of the lines used as inputs */
DECL|member|output
id|u32
id|output
suffix:semicolon
multiline_comment|/* bitmap of the lines used as outputs */
DECL|member|code_start
id|u16
id|code_start
suffix:semicolon
DECL|member|code_size
id|u16
id|code_size
suffix:semicolon
DECL|member|gpr_used
id|u32
id|gpr_used
(braket
id|NUM_GPRS
op_div
l_int|32
)braket
suffix:semicolon
multiline_comment|/* bitmap of used gprs */
DECL|member|gpr_input
id|u32
id|gpr_input
(braket
id|NUM_GPRS
op_div
l_int|32
)braket
suffix:semicolon
DECL|member|traml_istart
id|u8
id|traml_istart
suffix:semicolon
multiline_comment|/* starting address of the internal tram lines used */
DECL|member|traml_isize
id|u8
id|traml_isize
suffix:semicolon
multiline_comment|/* number of internal tram lines used */
DECL|member|traml_estart
id|u8
id|traml_estart
suffix:semicolon
DECL|member|traml_esize
id|u8
id|traml_esize
suffix:semicolon
DECL|member|tramb_istart
id|u16
id|tramb_istart
suffix:semicolon
multiline_comment|/* starting address of the internal tram memory used */
DECL|member|tramb_isize
id|u16
id|tramb_isize
suffix:semicolon
multiline_comment|/* amount of internal memory used */
DECL|member|tramb_estart
id|u32
id|tramb_estart
suffix:semicolon
DECL|member|tramb_esize
id|u32
id|tramb_esize
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dsp_gpr
r_struct
id|dsp_gpr
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
multiline_comment|/* gpr type, STATIC, DYNAMIC, INPUT, OUTPUT, CONTROL */
DECL|member|name
r_char
id|name
(braket
id|GPR_NAME_SIZE
)braket
suffix:semicolon
multiline_comment|/* gpr value, only valid for control gprs */
DECL|member|min
DECL|member|max
id|s32
id|min
comma
id|max
suffix:semicolon
multiline_comment|/* value range for this gpr, only valid for control gprs */
DECL|member|line
id|u8
id|line
suffix:semicolon
multiline_comment|/* which input/output line is the gpr attached, only valid for input/output gprs */
DECL|member|usage
id|u8
id|usage
suffix:semicolon
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|GPR_TYPE_NULL
id|GPR_TYPE_NULL
op_assign
l_int|0
comma
DECL|enumerator|GPR_TYPE_IO
id|GPR_TYPE_IO
comma
DECL|enumerator|GPR_TYPE_STATIC
id|GPR_TYPE_STATIC
comma
DECL|enumerator|GPR_TYPE_DYNAMIC
id|GPR_TYPE_DYNAMIC
comma
DECL|enumerator|GPR_TYPE_CONTROL
id|GPR_TYPE_CONTROL
comma
DECL|enumerator|GPR_TYPE_CONSTANT
id|GPR_TYPE_CONSTANT
)brace
suffix:semicolon
DECL|macro|GPR_BASE
mdefine_line|#define GPR_BASE 0x100
DECL|macro|OUTPUT_BASE
mdefine_line|#define OUTPUT_BASE 0x20
DECL|macro|MAX_PATCHES_PAGES
mdefine_line|#define MAX_PATCHES_PAGES 32
DECL|struct|patch_manager
r_struct
id|patch_manager
(brace
DECL|member|patch
r_void
op_star
id|patch
(braket
id|MAX_PATCHES_PAGES
)braket
suffix:semicolon
DECL|member|current_pages
r_int
id|current_pages
suffix:semicolon
DECL|member|rpatch
r_struct
id|dsp_rpatch
id|rpatch
suffix:semicolon
DECL|member|gpr
r_struct
id|dsp_gpr
id|gpr
(braket
id|NUM_GPRS
)braket
suffix:semicolon
multiline_comment|/* gpr usage table */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|ctrl_gpr
id|s16
id|ctrl_gpr
(braket
id|SOUND_MIXER_NRDEVICES
)braket
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PATCHES_PER_PAGE
mdefine_line|#define PATCHES_PER_PAGE (PAGE_SIZE / sizeof(struct dsp_patch))
DECL|macro|PATCH
mdefine_line|#define PATCH(mgr, i) ((struct dsp_patch *) (mgr)-&gt;patch[(i) / PATCHES_PER_PAGE] + (i) % PATCHES_PER_PAGE)
multiline_comment|/* PCM volume control */
DECL|macro|TMP_PCM_L
mdefine_line|#define TMP_PCM_L     0x100 
singleline_comment|//temp PCM L (after the vol control)       
DECL|macro|TMP_PCM_R
mdefine_line|#define TMP_PCM_R     0x101
DECL|macro|VOL_PCM_L
mdefine_line|#define VOL_PCM_L     0x102 
singleline_comment|//vol PCM
DECL|macro|VOL_PCM_R
mdefine_line|#define VOL_PCM_R     0x103
multiline_comment|/* Routing patch */
DECL|macro|TMP_AC_L
mdefine_line|#define TMP_AC_L      0x104 
singleline_comment|//tmp ac97 out
DECL|macro|TMP_AC_R
mdefine_line|#define TMP_AC_R      0x105
DECL|macro|TMP_REAR_L
mdefine_line|#define TMP_REAR_L    0x106 
singleline_comment|//output - Temp Rear
DECL|macro|TMP_REAR_R
mdefine_line|#define TMP_REAR_R    0x107
DECL|macro|TMP_DIGI_L
mdefine_line|#define TMP_DIGI_L    0x108 
singleline_comment|//output - Temp digital
DECL|macro|TMP_DIGI_R
mdefine_line|#define TMP_DIGI_R    0x109
DECL|macro|DSP_VOL_L
mdefine_line|#define DSP_VOL_L     0x10a 
singleline_comment|// main dsp volume
DECL|macro|DSP_VOL_R
mdefine_line|#define DSP_VOL_R     0x10b
multiline_comment|/* hw inputs */
DECL|macro|PCM_IN_L
mdefine_line|#define PCM_IN_L &t;0x00
DECL|macro|PCM_IN_R
mdefine_line|#define PCM_IN_R &t;0x01
DECL|macro|PCM1_IN_L
mdefine_line|#define PCM1_IN_L        0x04
DECL|macro|PCM1_IN_R
mdefine_line|#define PCM1_IN_R        0x05
singleline_comment|//mutilchannel playback stream appear here:
DECL|macro|MULTI_FRONT_L
mdefine_line|#define MULTI_FRONT_L&t;0x08
DECL|macro|MULTI_FRONT_R
mdefine_line|#define MULTI_FRONT_R&t;0x09
DECL|macro|MULTI_REAR_L
mdefine_line|#define MULTI_REAR_L&t;0x0a
DECL|macro|MULTI_REAR_R
mdefine_line|#define MULTI_REAR_R&t;0x0b
DECL|macro|MULTI_CENTER
mdefine_line|#define MULTI_CENTER&t;0x0c
DECL|macro|MULTI_LFE
mdefine_line|#define MULTI_LFE&t;0x0d
DECL|macro|AC97_IN_L
mdefine_line|#define AC97_IN_L&t;0x10
DECL|macro|AC97_IN_R
mdefine_line|#define AC97_IN_R&t;0x11
DECL|macro|SPDIF_CD_L
mdefine_line|#define SPDIF_CD_L&t;0x12
DECL|macro|SPDIF_CD_R
mdefine_line|#define SPDIF_CD_R&t;0x13
multiline_comment|/* hw outputs */
DECL|macro|AC97_FRONT_L
mdefine_line|#define AC97_FRONT_L&t;0x20
DECL|macro|AC97_FRONT_R
mdefine_line|#define AC97_FRONT_R&t;0x21
DECL|macro|DIGITAL_OUT_L
mdefine_line|#define DIGITAL_OUT_L&t;0x22
DECL|macro|DIGITAL_OUT_R
mdefine_line|#define DIGITAL_OUT_R&t;0x23
DECL|macro|DIGITAL_CENTER
mdefine_line|#define DIGITAL_CENTER&t;0x24
DECL|macro|DIGITAL_LFE
mdefine_line|#define DIGITAL_LFE&t;0x25
DECL|macro|ANALOG_REAR_L
mdefine_line|#define ANALOG_REAR_L&t;0x28
DECL|macro|ANALOG_REAR_R
mdefine_line|#define ANALOG_REAR_R&t;0x29
DECL|macro|ADC_REC_L
mdefine_line|#define ADC_REC_L&t;0x2a
DECL|macro|ADC_REC_R
mdefine_line|#define ADC_REC_R&t;0x2b
DECL|macro|ANALOG_CENTER
mdefine_line|#define ANALOG_CENTER&t;0x31
DECL|macro|ANALOG_LFE
mdefine_line|#define ANALOG_LFE&t;0x32
DECL|macro|INPUT_PATCH_START
mdefine_line|#define INPUT_PATCH_START(patch, nm, ln, i)&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;patch = PATCH(mgr, patch_n);&t;&t;&t;&bslash;&n;&t;strcpy(patch-&gt;name, nm);&t;&t;&t;&bslash;&n;&t;patch-&gt;code_start = pc * 2;&t;&t;&t;&bslash;&n;&t;patch-&gt;input = (1&lt;&lt;(0x1f&amp;ln));&t;&t;&t;&bslash;&n;&t;patch-&gt;output= (1&lt;&lt;(0x1f&amp;ln));&t;&t;&t;&bslash;&n;&t;patch-&gt;id = i;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|INPUT_PATCH_END
mdefine_line|#define INPUT_PATCH_END(patch)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;patch-&gt;code_size = pc * 2 - patch-&gt;code_start;&t;&bslash;&n;&t;patch_n++;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|ROUTING_PATCH_START
mdefine_line|#define ROUTING_PATCH_START(patch, nm)&t;&bslash;&n;do {&t;&t;&t;&t;&t;&bslash;&n;&t;patch = &amp;mgr-&gt;rpatch;&t;&t;&bslash;&n;&t;strcpy(patch-&gt;name, nm);&t;&bslash;&n;&t;patch-&gt;code_start = pc * 2;&t;&bslash;&n;} while(0)
DECL|macro|ROUTING_PATCH_END
mdefine_line|#define ROUTING_PATCH_END(patch)&t;&t;&t;&bslash;&n;do {                                                    &bslash;&n;&t;patch-&gt;code_size = pc * 2 - patch-&gt;code_start;      &bslash;&n;} while(0)
DECL|macro|CONNECT
mdefine_line|#define CONNECT(input, output) set_bit(input, &amp;rpatch-&gt;route[(output) - OUTPUT_BASE]);
DECL|macro|CONNECT_V
mdefine_line|#define CONNECT_V(input, output) set_bit(input, &amp;rpatch-&gt;route_v[(output) - OUTPUT_BASE]);
DECL|macro|OUTPUT_PATCH_START
mdefine_line|#define OUTPUT_PATCH_START(patch, nm, ln, i)&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;patch = PATCH(mgr, patch_n);&t;&t;&t;&bslash;&n;&t;strcpy(patch-&gt;name, nm);&t;&t;&t;&bslash;&n;&t;patch-&gt;code_start = pc * 2;&t;&t;&t;&bslash;&n;&t;patch-&gt;input = (1&lt;&lt;(0x1f&amp;ln));&t;&t;&t;&bslash;&n;&t;patch-&gt;output= (1&lt;&lt;(0x1f&amp;ln));&t;&t;&t;&bslash;&n;&t;patch-&gt;id = i;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|OUTPUT_PATCH_END
mdefine_line|#define OUTPUT_PATCH_END(patch)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;patch-&gt;code_size = pc * 2 - patch-&gt;code_start;&t;&bslash;&n;&t;patch_n++;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|GET_OUTPUT_GPR
mdefine_line|#define GET_OUTPUT_GPR(patch, g, ln)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;mgr-&gt;gpr[(g) - GPR_BASE].type = GPR_TYPE_IO;&t;&bslash;&n;&t;mgr-&gt;gpr[(g) - GPR_BASE].usage++;&t;&t;&bslash;&n;&t;mgr-&gt;gpr[(g) - GPR_BASE].line = ln;&t;&t;&bslash;&n;&t;set_bit((g) - GPR_BASE, patch-&gt;gpr_used);&t;&bslash;&n;} while(0)
DECL|macro|GET_INPUT_GPR
mdefine_line|#define GET_INPUT_GPR(patch, g, ln)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;mgr-&gt;gpr[(g) - GPR_BASE].type = GPR_TYPE_IO;&t;&bslash;&n;&t;mgr-&gt;gpr[(g) - GPR_BASE].usage++;&t;&t;&bslash;&n;&t;mgr-&gt;gpr[(g) - GPR_BASE].line = ln;&t;&t;&bslash;&n;&t;set_bit((g) - GPR_BASE, patch-&gt;gpr_used);&t;&bslash;&n;&t;set_bit((g) - GPR_BASE, patch-&gt;gpr_input);&t;&bslash;&n;} while(0)
DECL|macro|GET_DYNAMIC_GPR
mdefine_line|#define GET_DYNAMIC_GPR(patch, g)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;mgr-&gt;gpr[(g) - GPR_BASE].type = GPR_TYPE_DYNAMIC;&t;&bslash;&n;&t;mgr-&gt;gpr[(g) - GPR_BASE].usage++;&t;&t;&t;&bslash;&n;&t;set_bit((g) - GPR_BASE, patch-&gt;gpr_used);          &t;&bslash;&n;} while(0)
DECL|macro|GET_CONTROL_GPR
mdefine_line|#define GET_CONTROL_GPR(patch, g, nm, a, b)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;strcpy(mgr-&gt;gpr[(g) - GPR_BASE].name, nm);&t;&t;&bslash;&n;&t;mgr-&gt;gpr[(g) - GPR_BASE].type = GPR_TYPE_CONTROL;&t;&bslash;&n;&t;mgr-&gt;gpr[(g) - GPR_BASE].usage++;&t;&t;&t;&bslash;&n;&t;mgr-&gt;gpr[(g) - GPR_BASE].min = a;&t;&t;&t;&bslash;&n;&t;mgr-&gt;gpr[(g) - GPR_BASE].max = b;&t;&t;&t;&bslash;&n;&t;sblive_writeptr(card, g, 0, b);&t;&t;&t;&t;&bslash;&n;&t;set_bit((g) - GPR_BASE, patch-&gt;gpr_used);&t;&t;&bslash;&n;} while(0)
macro_line|#endif /* _EFXMGR_H */
eof
