multiline_comment|/*     &n; **********************************************************************&n; *     ecard.h&n; *     Copyright 1999, 2000 Creative Labs, Inc. &n; * &n; ********************************************************************** &n; * &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version. &n; * &n; *     This program is distributed in the hope that it will be useful, &n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of &n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the &n; *     GNU General Public License for more details. &n; * &n; *     You should have received a copy of the GNU General Public &n; *     License along with this program; if not, write to the Free &n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, &n; *     USA. &n; * &n; ********************************************************************** &n; */
macro_line|#ifndef _ECARD_H
DECL|macro|_ECARD_H
mdefine_line|#define _ECARD_H
macro_line|#include &quot;8010.h&quot;
macro_line|#include &quot;hwaccess.h&quot;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/* In A1 Silicon, these bits are in the HC register */
DECL|macro|HOOKN_BIT
mdefine_line|#define HOOKN_BIT   (1L &lt;&lt; 12)
DECL|macro|HANDN_BIT
mdefine_line|#define HANDN_BIT   (1L &lt;&lt; 11)
DECL|macro|PULSEN_BIT
mdefine_line|#define PULSEN_BIT  (1L &lt;&lt; 10)
DECL|macro|EC_GDI1
mdefine_line|#define EC_GDI1 (1 &lt;&lt; 13)
DECL|macro|EC_GDI0
mdefine_line|#define EC_GDI0 (1 &lt;&lt; 14)
DECL|macro|EC_NUM_CONTROL_BITS
mdefine_line|#define EC_NUM_CONTROL_BITS 20
DECL|macro|EC_AC3_DATA_SELN
mdefine_line|#define EC_AC3_DATA_SELN  0x0001L
DECL|macro|EC_EE_DATA_SEL
mdefine_line|#define EC_EE_DATA_SEL    0x0002L
DECL|macro|EC_EE_CNTRL_SELN
mdefine_line|#define EC_EE_CNTRL_SELN  0x0004L
DECL|macro|EC_EECLK
mdefine_line|#define EC_EECLK          0x0008L
DECL|macro|EC_EECS
mdefine_line|#define EC_EECS           0x0010L
DECL|macro|EC_EESDO
mdefine_line|#define EC_EESDO          0x0020L
DECL|macro|EC_TRIM_CSN
mdefine_line|#define EC_TRIM_CSN&t;  0x0040L
DECL|macro|EC_TRIM_SCLK
mdefine_line|#define EC_TRIM_SCLK&t;  0x0080L
DECL|macro|EC_TRIM_SDATA
mdefine_line|#define EC_TRIM_SDATA&t;  0x0100L
DECL|macro|EC_TRIM_MUTEN
mdefine_line|#define EC_TRIM_MUTEN&t;  0x0200L
DECL|macro|EC_ADCCAL
mdefine_line|#define EC_ADCCAL&t;  0x0400L
DECL|macro|EC_ADCRSTN
mdefine_line|#define EC_ADCRSTN&t;  0x0800L
DECL|macro|EC_DACCAL
mdefine_line|#define EC_DACCAL&t;  0x1000L
DECL|macro|EC_DACMUTEN
mdefine_line|#define EC_DACMUTEN&t;  0x2000L
DECL|macro|EC_LEDN
mdefine_line|#define EC_LEDN&t;&t;  0x4000L
DECL|macro|EC_SPDIF0_SEL_SHIFT
mdefine_line|#define EC_SPDIF0_SEL_SHIFT&t;15
DECL|macro|EC_SPDIF1_SEL_SHIFT
mdefine_line|#define EC_SPDIF1_SEL_SHIFT&t;17&t;
DECL|macro|EC_SPDIF0_SEL_MASK
mdefine_line|#define EC_SPDIF0_SEL_MASK&t;(0x3L &lt;&lt; EC_SPDIF0_SEL_SHIFT)
DECL|macro|EC_SPDIF1_SEL_MASK
mdefine_line|#define EC_SPDIF1_SEL_MASK&t;(0x7L &lt;&lt; EC_SPDIF1_SEL_SHIFT)
DECL|macro|EC_SPDIF0_SELECT
mdefine_line|#define EC_SPDIF0_SELECT(_x) (((_x) &lt;&lt; EC_SPDIF0_SEL_SHIFT) &amp; EC_SPDIF0_SEL_MASK)
DECL|macro|EC_SPDIF1_SELECT
mdefine_line|#define EC_SPDIF1_SELECT(_x) (((_x) &lt;&lt; EC_SPDIF1_SEL_SHIFT) &amp; EC_SPDIF1_SEL_MASK)
DECL|macro|EC_CURRENT_PROM_VERSION
mdefine_line|#define EC_CURRENT_PROM_VERSION 0x01 /* Self-explanatory.  This should&n;                                      * be incremented any time the EEPROM&squot;s&n;                                      * format is changed.  */
DECL|macro|EC_EEPROM_SIZE
mdefine_line|#define EC_EEPROM_SIZE&t;        0x40 /* ECARD EEPROM has 64 16-bit words */
multiline_comment|/* Addresses for special values stored in to EEPROM */
DECL|macro|EC_PROM_VERSION_ADDR
mdefine_line|#define EC_PROM_VERSION_ADDR&t;0x20&t;/* Address of the current prom version */
DECL|macro|EC_BOARDREV0_ADDR
mdefine_line|#define EC_BOARDREV0_ADDR&t;0x21&t;/* LSW of board rev */
DECL|macro|EC_BOARDREV1_ADDR
mdefine_line|#define EC_BOARDREV1_ADDR &t;0x22&t;/* MSW of board rev */ 
DECL|macro|EC_LAST_PROMFILE_ADDR
mdefine_line|#define EC_LAST_PROMFILE_ADDR&t;0x2f
DECL|macro|EC_SERIALNUM_ADD
mdefine_line|#define EC_SERIALNUM_ADD&t;0x30&t;/* First word of serial number.  The number&n;                                         * can be up to 30 characters in length&n;                                         * and is stored as a NULL-terminated&n;                                         * ASCII string.  Any unused bytes must be&n;                                         * filled with zeros */
DECL|macro|EC_CHECKSUM_ADDR
mdefine_line|#define EC_CHECKSUM_ADDR&t;0x3f    /* Location at which checksum is stored */
multiline_comment|/* Most of this stuff is pretty self-evident.  According to the hardware &n; * dudes, we need to leave the ADCCAL bit low in order to avoid a DC &n; * offset problem.  Weird.&n; */
DECL|macro|EC_RAW_RUN_MODE
mdefine_line|#define EC_RAW_RUN_MODE&t;(EC_DACMUTEN | EC_ADCRSTN | EC_TRIM_MUTEN | EC_TRIM_CSN)
DECL|macro|EC_DEFAULT_ADC_GAIN
mdefine_line|#define EC_DEFAULT_ADC_GAIN   0xC4C4
DECL|macro|EC_DEFAULT_SPDIF0_SEL
mdefine_line|#define EC_DEFAULT_SPDIF0_SEL 0x0
DECL|macro|EC_DEFAULT_SPDIF1_SEL
mdefine_line|#define EC_DEFAULT_SPDIF1_SEL 0x4
DECL|macro|HC_EA
mdefine_line|#define HC_EA 0x01L
multiline_comment|/* ECARD state structure.  This structure maintains the state&n; * for various portions of the ECARD&squot;s onboard hardware.&n; */
DECL|struct|ecard_state
r_struct
id|ecard_state
(brace
DECL|member|control_bits
id|u32
id|control_bits
suffix:semicolon
DECL|member|adc_gain
id|u16
id|adc_gain
suffix:semicolon
DECL|member|mux0_setting
id|u16
id|mux0_setting
suffix:semicolon
DECL|member|mux1_setting
id|u16
id|mux1_setting
suffix:semicolon
DECL|member|mux2_setting
id|u16
id|mux2_setting
suffix:semicolon
)brace
suffix:semicolon
r_void
id|emu10k1_ecard_init
c_func
(paren
r_struct
id|emu10k1_card
op_star
)paren
id|__devinit
suffix:semicolon
macro_line|#endif /* _ECARD_H */
eof
