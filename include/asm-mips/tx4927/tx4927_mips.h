multiline_comment|/*&n; * Author: MontaVista Software, Inc.&n; *         source@mvista.com&n; *&n; * Copyright 2001-2002 MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,&n; *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS&n; *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND&n; *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n; *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n; *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASM_TX4927_TX4927_MIPS_H
DECL|macro|__ASM_TX4927_TX4927_MIPS_H
mdefine_line|#define __ASM_TX4927_TX4927_MIPS_H
macro_line|#ifndef __ASSEMBLY__
DECL|function|asm_wait
r_static
r_inline
r_void
id|asm_wait
c_func
(paren
r_void
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;.set&bslash;tmips3&bslash;n&bslash;t&quot;
l_string|&quot;wait&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tmips0&quot;
)paren
suffix:semicolon
)brace
DECL|macro|reg_rd08
mdefine_line|#define reg_rd08(r)    ((u8 )(*((vu8 *)(r))))
DECL|macro|reg_rd16
mdefine_line|#define reg_rd16(r)    ((u16)(*((vu16*)(r))))
DECL|macro|reg_rd32
mdefine_line|#define reg_rd32(r)    ((u32)(*((vu32*)(r))))
DECL|macro|reg_rd64
mdefine_line|#define reg_rd64(r)    ((u64)(*((vu64*)(r))))
DECL|macro|reg_wr08
mdefine_line|#define reg_wr08(r,v)  ((*((vu8 *)(r)))=((u8 )(v)))
DECL|macro|reg_wr16
mdefine_line|#define reg_wr16(r,v)  ((*((vu16*)(r)))=((u16)(v)))
DECL|macro|reg_wr32
mdefine_line|#define reg_wr32(r,v)  ((*((vu32*)(r)))=((u32)(v)))
DECL|macro|reg_wr64
mdefine_line|#define reg_wr64(r,v)  ((*((vu64*)(r)))=((u64)(v)))
DECL|typedef|vs8
r_typedef
r_volatile
id|__signed
r_char
id|vs8
suffix:semicolon
DECL|typedef|vu8
r_typedef
r_volatile
r_int
r_char
id|vu8
suffix:semicolon
DECL|typedef|vs16
r_typedef
r_volatile
id|__signed
r_int
id|vs16
suffix:semicolon
DECL|typedef|vu16
r_typedef
r_volatile
r_int
r_int
id|vu16
suffix:semicolon
DECL|typedef|vs32
r_typedef
r_volatile
id|__signed
r_int
id|vs32
suffix:semicolon
DECL|typedef|vu32
r_typedef
r_volatile
r_int
r_int
id|vu32
suffix:semicolon
DECL|typedef|s08
r_typedef
id|s8
id|s08
suffix:semicolon
DECL|typedef|vs08
r_typedef
id|vs8
id|vs08
suffix:semicolon
DECL|typedef|u08
r_typedef
id|u8
id|u08
suffix:semicolon
DECL|typedef|vu08
r_typedef
id|vu8
id|vu08
suffix:semicolon
macro_line|#if (_MIPS_SZLONG == 64)
DECL|typedef|vs64
r_typedef
r_volatile
id|__signed__
r_int
id|vs64
suffix:semicolon
DECL|typedef|vu64
r_typedef
r_volatile
r_int
r_int
id|vu64
suffix:semicolon
macro_line|#else
DECL|typedef|vs64
r_typedef
r_volatile
id|__signed__
r_int
r_int
id|vs64
suffix:semicolon
DECL|typedef|vu64
r_typedef
r_volatile
r_int
r_int
r_int
id|vu64
suffix:semicolon
macro_line|#endif
DECL|macro|BM_00_00
mdefine_line|#define BM_00_00 0x0000000000000001
DECL|macro|BM_01_00
mdefine_line|#define BM_01_00 0x0000000000000003
DECL|macro|BM_00_01
mdefine_line|#define BM_00_01 BM_01_00
DECL|macro|BM_02_00
mdefine_line|#define BM_02_00 0x0000000000000007
DECL|macro|BM_00_02
mdefine_line|#define BM_00_02 BM_02_00
DECL|macro|BM_03_00
mdefine_line|#define BM_03_00 0x000000000000000f
DECL|macro|BM_00_03
mdefine_line|#define BM_00_03 BM_03_00
DECL|macro|BM_04_00
mdefine_line|#define BM_04_00 0x000000000000001f
DECL|macro|BM_00_04
mdefine_line|#define BM_00_04 BM_04_00
DECL|macro|BM_05_00
mdefine_line|#define BM_05_00 0x000000000000003f
DECL|macro|BM_00_05
mdefine_line|#define BM_00_05 BM_05_00
DECL|macro|BM_06_00
mdefine_line|#define BM_06_00 0x000000000000007f
DECL|macro|BM_00_06
mdefine_line|#define BM_00_06 BM_06_00
DECL|macro|BM_07_00
mdefine_line|#define BM_07_00 0x00000000000000ff
DECL|macro|BM_00_07
mdefine_line|#define BM_00_07 BM_07_00
DECL|macro|BM_08_00
mdefine_line|#define BM_08_00 0x00000000000001ff
DECL|macro|BM_00_08
mdefine_line|#define BM_00_08 BM_08_00
DECL|macro|BM_09_00
mdefine_line|#define BM_09_00 0x00000000000003ff
DECL|macro|BM_00_09
mdefine_line|#define BM_00_09 BM_09_00
DECL|macro|BM_10_00
mdefine_line|#define BM_10_00 0x00000000000007ff
DECL|macro|BM_00_10
mdefine_line|#define BM_00_10 BM_10_00
DECL|macro|BM_11_00
mdefine_line|#define BM_11_00 0x0000000000000fff
DECL|macro|BM_00_11
mdefine_line|#define BM_00_11 BM_11_00
DECL|macro|BM_12_00
mdefine_line|#define BM_12_00 0x0000000000001fff
DECL|macro|BM_00_12
mdefine_line|#define BM_00_12 BM_12_00
DECL|macro|BM_13_00
mdefine_line|#define BM_13_00 0x0000000000003fff
DECL|macro|BM_00_13
mdefine_line|#define BM_00_13 BM_13_00
DECL|macro|BM_14_00
mdefine_line|#define BM_14_00 0x0000000000007fff
DECL|macro|BM_00_14
mdefine_line|#define BM_00_14 BM_14_00
DECL|macro|BM_15_00
mdefine_line|#define BM_15_00 0x000000000000ffff
DECL|macro|BM_00_15
mdefine_line|#define BM_00_15 BM_15_00
DECL|macro|BM_16_00
mdefine_line|#define BM_16_00 0x000000000001ffff
DECL|macro|BM_00_16
mdefine_line|#define BM_00_16 BM_16_00
DECL|macro|BM_17_00
mdefine_line|#define BM_17_00 0x000000000003ffff
DECL|macro|BM_00_17
mdefine_line|#define BM_00_17 BM_17_00
DECL|macro|BM_18_00
mdefine_line|#define BM_18_00 0x000000000007ffff
DECL|macro|BM_00_18
mdefine_line|#define BM_00_18 BM_18_00
DECL|macro|BM_19_00
mdefine_line|#define BM_19_00 0x00000000000fffff
DECL|macro|BM_00_19
mdefine_line|#define BM_00_19 BM_19_00
DECL|macro|BM_20_00
mdefine_line|#define BM_20_00 0x00000000001fffff
DECL|macro|BM_00_20
mdefine_line|#define BM_00_20 BM_20_00
DECL|macro|BM_21_00
mdefine_line|#define BM_21_00 0x00000000003fffff
DECL|macro|BM_00_21
mdefine_line|#define BM_00_21 BM_21_00
DECL|macro|BM_22_00
mdefine_line|#define BM_22_00 0x00000000007fffff
DECL|macro|BM_00_22
mdefine_line|#define BM_00_22 BM_22_00
DECL|macro|BM_23_00
mdefine_line|#define BM_23_00 0x0000000000ffffff
DECL|macro|BM_00_23
mdefine_line|#define BM_00_23 BM_23_00
DECL|macro|BM_24_00
mdefine_line|#define BM_24_00 0x0000000001ffffff
DECL|macro|BM_00_24
mdefine_line|#define BM_00_24 BM_24_00
DECL|macro|BM_25_00
mdefine_line|#define BM_25_00 0x0000000003ffffff
DECL|macro|BM_00_25
mdefine_line|#define BM_00_25 BM_25_00
DECL|macro|BM_26_00
mdefine_line|#define BM_26_00 0x0000000007ffffff
DECL|macro|BM_00_26
mdefine_line|#define BM_00_26 BM_26_00
DECL|macro|BM_27_00
mdefine_line|#define BM_27_00 0x000000000fffffff
DECL|macro|BM_00_27
mdefine_line|#define BM_00_27 BM_27_00
DECL|macro|BM_28_00
mdefine_line|#define BM_28_00 0x000000001fffffff
DECL|macro|BM_00_28
mdefine_line|#define BM_00_28 BM_28_00
DECL|macro|BM_29_00
mdefine_line|#define BM_29_00 0x000000003fffffff
DECL|macro|BM_00_29
mdefine_line|#define BM_00_29 BM_29_00
DECL|macro|BM_30_00
mdefine_line|#define BM_30_00 0x000000007fffffff
DECL|macro|BM_00_30
mdefine_line|#define BM_00_30 BM_30_00
DECL|macro|BM_31_00
mdefine_line|#define BM_31_00 0x00000000ffffffff
DECL|macro|BM_00_31
mdefine_line|#define BM_00_31 BM_31_00
DECL|macro|BM_32_00
mdefine_line|#define BM_32_00 0x00000001ffffffff
DECL|macro|BM_00_32
mdefine_line|#define BM_00_32 BM_32_00
DECL|macro|BM_33_00
mdefine_line|#define BM_33_00 0x00000003ffffffff
DECL|macro|BM_00_33
mdefine_line|#define BM_00_33 BM_33_00
DECL|macro|BM_34_00
mdefine_line|#define BM_34_00 0x00000007ffffffff
DECL|macro|BM_00_34
mdefine_line|#define BM_00_34 BM_34_00
DECL|macro|BM_35_00
mdefine_line|#define BM_35_00 0x0000000fffffffff
DECL|macro|BM_00_35
mdefine_line|#define BM_00_35 BM_35_00
DECL|macro|BM_36_00
mdefine_line|#define BM_36_00 0x0000001fffffffff
DECL|macro|BM_00_36
mdefine_line|#define BM_00_36 BM_36_00
DECL|macro|BM_37_00
mdefine_line|#define BM_37_00 0x0000003fffffffff
DECL|macro|BM_00_37
mdefine_line|#define BM_00_37 BM_37_00
DECL|macro|BM_38_00
mdefine_line|#define BM_38_00 0x0000007fffffffff
DECL|macro|BM_00_38
mdefine_line|#define BM_00_38 BM_38_00
DECL|macro|BM_39_00
mdefine_line|#define BM_39_00 0x000000ffffffffff
DECL|macro|BM_00_39
mdefine_line|#define BM_00_39 BM_39_00
DECL|macro|BM_40_00
mdefine_line|#define BM_40_00 0x000001ffffffffff
DECL|macro|BM_00_40
mdefine_line|#define BM_00_40 BM_40_00
DECL|macro|BM_41_00
mdefine_line|#define BM_41_00 0x000003ffffffffff
DECL|macro|BM_00_41
mdefine_line|#define BM_00_41 BM_41_00
DECL|macro|BM_42_00
mdefine_line|#define BM_42_00 0x000007ffffffffff
DECL|macro|BM_00_42
mdefine_line|#define BM_00_42 BM_42_00
DECL|macro|BM_43_00
mdefine_line|#define BM_43_00 0x00000fffffffffff
DECL|macro|BM_00_43
mdefine_line|#define BM_00_43 BM_43_00
DECL|macro|BM_44_00
mdefine_line|#define BM_44_00 0x00001fffffffffff
DECL|macro|BM_00_44
mdefine_line|#define BM_00_44 BM_44_00
DECL|macro|BM_45_00
mdefine_line|#define BM_45_00 0x00003fffffffffff
DECL|macro|BM_00_45
mdefine_line|#define BM_00_45 BM_45_00
DECL|macro|BM_46_00
mdefine_line|#define BM_46_00 0x00007fffffffffff
DECL|macro|BM_00_46
mdefine_line|#define BM_00_46 BM_46_00
DECL|macro|BM_47_00
mdefine_line|#define BM_47_00 0x0000ffffffffffff
DECL|macro|BM_00_47
mdefine_line|#define BM_00_47 BM_47_00
DECL|macro|BM_48_00
mdefine_line|#define BM_48_00 0x0001ffffffffffff
DECL|macro|BM_00_48
mdefine_line|#define BM_00_48 BM_48_00
DECL|macro|BM_49_00
mdefine_line|#define BM_49_00 0x0003ffffffffffff
DECL|macro|BM_00_49
mdefine_line|#define BM_00_49 BM_49_00
DECL|macro|BM_50_00
mdefine_line|#define BM_50_00 0x0007ffffffffffff
DECL|macro|BM_00_50
mdefine_line|#define BM_00_50 BM_50_00
DECL|macro|BM_51_00
mdefine_line|#define BM_51_00 0x000fffffffffffff
DECL|macro|BM_00_51
mdefine_line|#define BM_00_51 BM_51_00
DECL|macro|BM_52_00
mdefine_line|#define BM_52_00 0x001fffffffffffff
DECL|macro|BM_00_52
mdefine_line|#define BM_00_52 BM_52_00
DECL|macro|BM_53_00
mdefine_line|#define BM_53_00 0x003fffffffffffff
DECL|macro|BM_00_53
mdefine_line|#define BM_00_53 BM_53_00
DECL|macro|BM_54_00
mdefine_line|#define BM_54_00 0x007fffffffffffff
DECL|macro|BM_00_54
mdefine_line|#define BM_00_54 BM_54_00
DECL|macro|BM_55_00
mdefine_line|#define BM_55_00 0x00ffffffffffffff
DECL|macro|BM_00_55
mdefine_line|#define BM_00_55 BM_55_00
DECL|macro|BM_56_00
mdefine_line|#define BM_56_00 0x01ffffffffffffff
DECL|macro|BM_00_56
mdefine_line|#define BM_00_56 BM_56_00
DECL|macro|BM_57_00
mdefine_line|#define BM_57_00 0x03ffffffffffffff
DECL|macro|BM_00_57
mdefine_line|#define BM_00_57 BM_57_00
DECL|macro|BM_58_00
mdefine_line|#define BM_58_00 0x07ffffffffffffff
DECL|macro|BM_00_58
mdefine_line|#define BM_00_58 BM_58_00
DECL|macro|BM_59_00
mdefine_line|#define BM_59_00 0x0fffffffffffffff
DECL|macro|BM_00_59
mdefine_line|#define BM_00_59 BM_59_00
DECL|macro|BM_60_00
mdefine_line|#define BM_60_00 0x1fffffffffffffff
DECL|macro|BM_00_60
mdefine_line|#define BM_00_60 BM_60_00
DECL|macro|BM_61_00
mdefine_line|#define BM_61_00 0x3fffffffffffffff
DECL|macro|BM_00_61
mdefine_line|#define BM_00_61 BM_61_00
DECL|macro|BM_62_00
mdefine_line|#define BM_62_00 0x7fffffffffffffff
DECL|macro|BM_00_62
mdefine_line|#define BM_00_62 BM_62_00
DECL|macro|BM_63_00
mdefine_line|#define BM_63_00 0xffffffffffffffff
DECL|macro|BM_00_63
mdefine_line|#define BM_00_63 BM_63_00
DECL|macro|BM_01_01
mdefine_line|#define BM_01_01 0x0000000000000002
DECL|macro|BM_02_01
mdefine_line|#define BM_02_01 0x0000000000000006
DECL|macro|BM_01_02
mdefine_line|#define BM_01_02 BM_02_01
DECL|macro|BM_03_01
mdefine_line|#define BM_03_01 0x000000000000000e
DECL|macro|BM_01_03
mdefine_line|#define BM_01_03 BM_03_01
DECL|macro|BM_04_01
mdefine_line|#define BM_04_01 0x000000000000001e
DECL|macro|BM_01_04
mdefine_line|#define BM_01_04 BM_04_01
DECL|macro|BM_05_01
mdefine_line|#define BM_05_01 0x000000000000003e
DECL|macro|BM_01_05
mdefine_line|#define BM_01_05 BM_05_01
DECL|macro|BM_06_01
mdefine_line|#define BM_06_01 0x000000000000007e
DECL|macro|BM_01_06
mdefine_line|#define BM_01_06 BM_06_01
DECL|macro|BM_07_01
mdefine_line|#define BM_07_01 0x00000000000000fe
DECL|macro|BM_01_07
mdefine_line|#define BM_01_07 BM_07_01
DECL|macro|BM_08_01
mdefine_line|#define BM_08_01 0x00000000000001fe
DECL|macro|BM_01_08
mdefine_line|#define BM_01_08 BM_08_01
DECL|macro|BM_09_01
mdefine_line|#define BM_09_01 0x00000000000003fe
DECL|macro|BM_01_09
mdefine_line|#define BM_01_09 BM_09_01
DECL|macro|BM_10_01
mdefine_line|#define BM_10_01 0x00000000000007fe
DECL|macro|BM_01_10
mdefine_line|#define BM_01_10 BM_10_01
DECL|macro|BM_11_01
mdefine_line|#define BM_11_01 0x0000000000000ffe
DECL|macro|BM_01_11
mdefine_line|#define BM_01_11 BM_11_01
DECL|macro|BM_12_01
mdefine_line|#define BM_12_01 0x0000000000001ffe
DECL|macro|BM_01_12
mdefine_line|#define BM_01_12 BM_12_01
DECL|macro|BM_13_01
mdefine_line|#define BM_13_01 0x0000000000003ffe
DECL|macro|BM_01_13
mdefine_line|#define BM_01_13 BM_13_01
DECL|macro|BM_14_01
mdefine_line|#define BM_14_01 0x0000000000007ffe
DECL|macro|BM_01_14
mdefine_line|#define BM_01_14 BM_14_01
DECL|macro|BM_15_01
mdefine_line|#define BM_15_01 0x000000000000fffe
DECL|macro|BM_01_15
mdefine_line|#define BM_01_15 BM_15_01
DECL|macro|BM_16_01
mdefine_line|#define BM_16_01 0x000000000001fffe
DECL|macro|BM_01_16
mdefine_line|#define BM_01_16 BM_16_01
DECL|macro|BM_17_01
mdefine_line|#define BM_17_01 0x000000000003fffe
DECL|macro|BM_01_17
mdefine_line|#define BM_01_17 BM_17_01
DECL|macro|BM_18_01
mdefine_line|#define BM_18_01 0x000000000007fffe
DECL|macro|BM_01_18
mdefine_line|#define BM_01_18 BM_18_01
DECL|macro|BM_19_01
mdefine_line|#define BM_19_01 0x00000000000ffffe
DECL|macro|BM_01_19
mdefine_line|#define BM_01_19 BM_19_01
DECL|macro|BM_20_01
mdefine_line|#define BM_20_01 0x00000000001ffffe
DECL|macro|BM_01_20
mdefine_line|#define BM_01_20 BM_20_01
DECL|macro|BM_21_01
mdefine_line|#define BM_21_01 0x00000000003ffffe
DECL|macro|BM_01_21
mdefine_line|#define BM_01_21 BM_21_01
DECL|macro|BM_22_01
mdefine_line|#define BM_22_01 0x00000000007ffffe
DECL|macro|BM_01_22
mdefine_line|#define BM_01_22 BM_22_01
DECL|macro|BM_23_01
mdefine_line|#define BM_23_01 0x0000000000fffffe
DECL|macro|BM_01_23
mdefine_line|#define BM_01_23 BM_23_01
DECL|macro|BM_24_01
mdefine_line|#define BM_24_01 0x0000000001fffffe
DECL|macro|BM_01_24
mdefine_line|#define BM_01_24 BM_24_01
DECL|macro|BM_25_01
mdefine_line|#define BM_25_01 0x0000000003fffffe
DECL|macro|BM_01_25
mdefine_line|#define BM_01_25 BM_25_01
DECL|macro|BM_26_01
mdefine_line|#define BM_26_01 0x0000000007fffffe
DECL|macro|BM_01_26
mdefine_line|#define BM_01_26 BM_26_01
DECL|macro|BM_27_01
mdefine_line|#define BM_27_01 0x000000000ffffffe
DECL|macro|BM_01_27
mdefine_line|#define BM_01_27 BM_27_01
DECL|macro|BM_28_01
mdefine_line|#define BM_28_01 0x000000001ffffffe
DECL|macro|BM_01_28
mdefine_line|#define BM_01_28 BM_28_01
DECL|macro|BM_29_01
mdefine_line|#define BM_29_01 0x000000003ffffffe
DECL|macro|BM_01_29
mdefine_line|#define BM_01_29 BM_29_01
DECL|macro|BM_30_01
mdefine_line|#define BM_30_01 0x000000007ffffffe
DECL|macro|BM_01_30
mdefine_line|#define BM_01_30 BM_30_01
DECL|macro|BM_31_01
mdefine_line|#define BM_31_01 0x00000000fffffffe
DECL|macro|BM_01_31
mdefine_line|#define BM_01_31 BM_31_01
DECL|macro|BM_32_01
mdefine_line|#define BM_32_01 0x00000001fffffffe
DECL|macro|BM_01_32
mdefine_line|#define BM_01_32 BM_32_01
DECL|macro|BM_33_01
mdefine_line|#define BM_33_01 0x00000003fffffffe
DECL|macro|BM_01_33
mdefine_line|#define BM_01_33 BM_33_01
DECL|macro|BM_34_01
mdefine_line|#define BM_34_01 0x00000007fffffffe
DECL|macro|BM_01_34
mdefine_line|#define BM_01_34 BM_34_01
DECL|macro|BM_35_01
mdefine_line|#define BM_35_01 0x0000000ffffffffe
DECL|macro|BM_01_35
mdefine_line|#define BM_01_35 BM_35_01
DECL|macro|BM_36_01
mdefine_line|#define BM_36_01 0x0000001ffffffffe
DECL|macro|BM_01_36
mdefine_line|#define BM_01_36 BM_36_01
DECL|macro|BM_37_01
mdefine_line|#define BM_37_01 0x0000003ffffffffe
DECL|macro|BM_01_37
mdefine_line|#define BM_01_37 BM_37_01
DECL|macro|BM_38_01
mdefine_line|#define BM_38_01 0x0000007ffffffffe
DECL|macro|BM_01_38
mdefine_line|#define BM_01_38 BM_38_01
DECL|macro|BM_39_01
mdefine_line|#define BM_39_01 0x000000fffffffffe
DECL|macro|BM_01_39
mdefine_line|#define BM_01_39 BM_39_01
DECL|macro|BM_40_01
mdefine_line|#define BM_40_01 0x000001fffffffffe
DECL|macro|BM_01_40
mdefine_line|#define BM_01_40 BM_40_01
DECL|macro|BM_41_01
mdefine_line|#define BM_41_01 0x000003fffffffffe
DECL|macro|BM_01_41
mdefine_line|#define BM_01_41 BM_41_01
DECL|macro|BM_42_01
mdefine_line|#define BM_42_01 0x000007fffffffffe
DECL|macro|BM_01_42
mdefine_line|#define BM_01_42 BM_42_01
DECL|macro|BM_43_01
mdefine_line|#define BM_43_01 0x00000ffffffffffe
DECL|macro|BM_01_43
mdefine_line|#define BM_01_43 BM_43_01
DECL|macro|BM_44_01
mdefine_line|#define BM_44_01 0x00001ffffffffffe
DECL|macro|BM_01_44
mdefine_line|#define BM_01_44 BM_44_01
DECL|macro|BM_45_01
mdefine_line|#define BM_45_01 0x00003ffffffffffe
DECL|macro|BM_01_45
mdefine_line|#define BM_01_45 BM_45_01
DECL|macro|BM_46_01
mdefine_line|#define BM_46_01 0x00007ffffffffffe
DECL|macro|BM_01_46
mdefine_line|#define BM_01_46 BM_46_01
DECL|macro|BM_47_01
mdefine_line|#define BM_47_01 0x0000fffffffffffe
DECL|macro|BM_01_47
mdefine_line|#define BM_01_47 BM_47_01
DECL|macro|BM_48_01
mdefine_line|#define BM_48_01 0x0001fffffffffffe
DECL|macro|BM_01_48
mdefine_line|#define BM_01_48 BM_48_01
DECL|macro|BM_49_01
mdefine_line|#define BM_49_01 0x0003fffffffffffe
DECL|macro|BM_01_49
mdefine_line|#define BM_01_49 BM_49_01
DECL|macro|BM_50_01
mdefine_line|#define BM_50_01 0x0007fffffffffffe
DECL|macro|BM_01_50
mdefine_line|#define BM_01_50 BM_50_01
DECL|macro|BM_51_01
mdefine_line|#define BM_51_01 0x000ffffffffffffe
DECL|macro|BM_01_51
mdefine_line|#define BM_01_51 BM_51_01
DECL|macro|BM_52_01
mdefine_line|#define BM_52_01 0x001ffffffffffffe
DECL|macro|BM_01_52
mdefine_line|#define BM_01_52 BM_52_01
DECL|macro|BM_53_01
mdefine_line|#define BM_53_01 0x003ffffffffffffe
DECL|macro|BM_01_53
mdefine_line|#define BM_01_53 BM_53_01
DECL|macro|BM_54_01
mdefine_line|#define BM_54_01 0x007ffffffffffffe
DECL|macro|BM_01_54
mdefine_line|#define BM_01_54 BM_54_01
DECL|macro|BM_55_01
mdefine_line|#define BM_55_01 0x00fffffffffffffe
DECL|macro|BM_01_55
mdefine_line|#define BM_01_55 BM_55_01
DECL|macro|BM_56_01
mdefine_line|#define BM_56_01 0x01fffffffffffffe
DECL|macro|BM_01_56
mdefine_line|#define BM_01_56 BM_56_01
DECL|macro|BM_57_01
mdefine_line|#define BM_57_01 0x03fffffffffffffe
DECL|macro|BM_01_57
mdefine_line|#define BM_01_57 BM_57_01
DECL|macro|BM_58_01
mdefine_line|#define BM_58_01 0x07fffffffffffffe
DECL|macro|BM_01_58
mdefine_line|#define BM_01_58 BM_58_01
DECL|macro|BM_59_01
mdefine_line|#define BM_59_01 0x0ffffffffffffffe
DECL|macro|BM_01_59
mdefine_line|#define BM_01_59 BM_59_01
DECL|macro|BM_60_01
mdefine_line|#define BM_60_01 0x1ffffffffffffffe
DECL|macro|BM_01_60
mdefine_line|#define BM_01_60 BM_60_01
DECL|macro|BM_61_01
mdefine_line|#define BM_61_01 0x3ffffffffffffffe
DECL|macro|BM_01_61
mdefine_line|#define BM_01_61 BM_61_01
DECL|macro|BM_62_01
mdefine_line|#define BM_62_01 0x7ffffffffffffffe
DECL|macro|BM_01_62
mdefine_line|#define BM_01_62 BM_62_01
DECL|macro|BM_63_01
mdefine_line|#define BM_63_01 0xfffffffffffffffe
DECL|macro|BM_01_63
mdefine_line|#define BM_01_63 BM_63_01
DECL|macro|BM_02_02
mdefine_line|#define BM_02_02 0x0000000000000004
DECL|macro|BM_03_02
mdefine_line|#define BM_03_02 0x000000000000000c
DECL|macro|BM_02_03
mdefine_line|#define BM_02_03 BM_03_02
DECL|macro|BM_04_02
mdefine_line|#define BM_04_02 0x000000000000001c
DECL|macro|BM_02_04
mdefine_line|#define BM_02_04 BM_04_02
DECL|macro|BM_05_02
mdefine_line|#define BM_05_02 0x000000000000003c
DECL|macro|BM_02_05
mdefine_line|#define BM_02_05 BM_05_02
DECL|macro|BM_06_02
mdefine_line|#define BM_06_02 0x000000000000007c
DECL|macro|BM_02_06
mdefine_line|#define BM_02_06 BM_06_02
DECL|macro|BM_07_02
mdefine_line|#define BM_07_02 0x00000000000000fc
DECL|macro|BM_02_07
mdefine_line|#define BM_02_07 BM_07_02
DECL|macro|BM_08_02
mdefine_line|#define BM_08_02 0x00000000000001fc
DECL|macro|BM_02_08
mdefine_line|#define BM_02_08 BM_08_02
DECL|macro|BM_09_02
mdefine_line|#define BM_09_02 0x00000000000003fc
DECL|macro|BM_02_09
mdefine_line|#define BM_02_09 BM_09_02
DECL|macro|BM_10_02
mdefine_line|#define BM_10_02 0x00000000000007fc
DECL|macro|BM_02_10
mdefine_line|#define BM_02_10 BM_10_02
DECL|macro|BM_11_02
mdefine_line|#define BM_11_02 0x0000000000000ffc
DECL|macro|BM_02_11
mdefine_line|#define BM_02_11 BM_11_02
DECL|macro|BM_12_02
mdefine_line|#define BM_12_02 0x0000000000001ffc
DECL|macro|BM_02_12
mdefine_line|#define BM_02_12 BM_12_02
DECL|macro|BM_13_02
mdefine_line|#define BM_13_02 0x0000000000003ffc
DECL|macro|BM_02_13
mdefine_line|#define BM_02_13 BM_13_02
DECL|macro|BM_14_02
mdefine_line|#define BM_14_02 0x0000000000007ffc
DECL|macro|BM_02_14
mdefine_line|#define BM_02_14 BM_14_02
DECL|macro|BM_15_02
mdefine_line|#define BM_15_02 0x000000000000fffc
DECL|macro|BM_02_15
mdefine_line|#define BM_02_15 BM_15_02
DECL|macro|BM_16_02
mdefine_line|#define BM_16_02 0x000000000001fffc
DECL|macro|BM_02_16
mdefine_line|#define BM_02_16 BM_16_02
DECL|macro|BM_17_02
mdefine_line|#define BM_17_02 0x000000000003fffc
DECL|macro|BM_02_17
mdefine_line|#define BM_02_17 BM_17_02
DECL|macro|BM_18_02
mdefine_line|#define BM_18_02 0x000000000007fffc
DECL|macro|BM_02_18
mdefine_line|#define BM_02_18 BM_18_02
DECL|macro|BM_19_02
mdefine_line|#define BM_19_02 0x00000000000ffffc
DECL|macro|BM_02_19
mdefine_line|#define BM_02_19 BM_19_02
DECL|macro|BM_20_02
mdefine_line|#define BM_20_02 0x00000000001ffffc
DECL|macro|BM_02_20
mdefine_line|#define BM_02_20 BM_20_02
DECL|macro|BM_21_02
mdefine_line|#define BM_21_02 0x00000000003ffffc
DECL|macro|BM_02_21
mdefine_line|#define BM_02_21 BM_21_02
DECL|macro|BM_22_02
mdefine_line|#define BM_22_02 0x00000000007ffffc
DECL|macro|BM_02_22
mdefine_line|#define BM_02_22 BM_22_02
DECL|macro|BM_23_02
mdefine_line|#define BM_23_02 0x0000000000fffffc
DECL|macro|BM_02_23
mdefine_line|#define BM_02_23 BM_23_02
DECL|macro|BM_24_02
mdefine_line|#define BM_24_02 0x0000000001fffffc
DECL|macro|BM_02_24
mdefine_line|#define BM_02_24 BM_24_02
DECL|macro|BM_25_02
mdefine_line|#define BM_25_02 0x0000000003fffffc
DECL|macro|BM_02_25
mdefine_line|#define BM_02_25 BM_25_02
DECL|macro|BM_26_02
mdefine_line|#define BM_26_02 0x0000000007fffffc
DECL|macro|BM_02_26
mdefine_line|#define BM_02_26 BM_26_02
DECL|macro|BM_27_02
mdefine_line|#define BM_27_02 0x000000000ffffffc
DECL|macro|BM_02_27
mdefine_line|#define BM_02_27 BM_27_02
DECL|macro|BM_28_02
mdefine_line|#define BM_28_02 0x000000001ffffffc
DECL|macro|BM_02_28
mdefine_line|#define BM_02_28 BM_28_02
DECL|macro|BM_29_02
mdefine_line|#define BM_29_02 0x000000003ffffffc
DECL|macro|BM_02_29
mdefine_line|#define BM_02_29 BM_29_02
DECL|macro|BM_30_02
mdefine_line|#define BM_30_02 0x000000007ffffffc
DECL|macro|BM_02_30
mdefine_line|#define BM_02_30 BM_30_02
DECL|macro|BM_31_02
mdefine_line|#define BM_31_02 0x00000000fffffffc
DECL|macro|BM_02_31
mdefine_line|#define BM_02_31 BM_31_02
DECL|macro|BM_32_02
mdefine_line|#define BM_32_02 0x00000001fffffffc
DECL|macro|BM_02_32
mdefine_line|#define BM_02_32 BM_32_02
DECL|macro|BM_33_02
mdefine_line|#define BM_33_02 0x00000003fffffffc
DECL|macro|BM_02_33
mdefine_line|#define BM_02_33 BM_33_02
DECL|macro|BM_34_02
mdefine_line|#define BM_34_02 0x00000007fffffffc
DECL|macro|BM_02_34
mdefine_line|#define BM_02_34 BM_34_02
DECL|macro|BM_35_02
mdefine_line|#define BM_35_02 0x0000000ffffffffc
DECL|macro|BM_02_35
mdefine_line|#define BM_02_35 BM_35_02
DECL|macro|BM_36_02
mdefine_line|#define BM_36_02 0x0000001ffffffffc
DECL|macro|BM_02_36
mdefine_line|#define BM_02_36 BM_36_02
DECL|macro|BM_37_02
mdefine_line|#define BM_37_02 0x0000003ffffffffc
DECL|macro|BM_02_37
mdefine_line|#define BM_02_37 BM_37_02
DECL|macro|BM_38_02
mdefine_line|#define BM_38_02 0x0000007ffffffffc
DECL|macro|BM_02_38
mdefine_line|#define BM_02_38 BM_38_02
DECL|macro|BM_39_02
mdefine_line|#define BM_39_02 0x000000fffffffffc
DECL|macro|BM_02_39
mdefine_line|#define BM_02_39 BM_39_02
DECL|macro|BM_40_02
mdefine_line|#define BM_40_02 0x000001fffffffffc
DECL|macro|BM_02_40
mdefine_line|#define BM_02_40 BM_40_02
DECL|macro|BM_41_02
mdefine_line|#define BM_41_02 0x000003fffffffffc
DECL|macro|BM_02_41
mdefine_line|#define BM_02_41 BM_41_02
DECL|macro|BM_42_02
mdefine_line|#define BM_42_02 0x000007fffffffffc
DECL|macro|BM_02_42
mdefine_line|#define BM_02_42 BM_42_02
DECL|macro|BM_43_02
mdefine_line|#define BM_43_02 0x00000ffffffffffc
DECL|macro|BM_02_43
mdefine_line|#define BM_02_43 BM_43_02
DECL|macro|BM_44_02
mdefine_line|#define BM_44_02 0x00001ffffffffffc
DECL|macro|BM_02_44
mdefine_line|#define BM_02_44 BM_44_02
DECL|macro|BM_45_02
mdefine_line|#define BM_45_02 0x00003ffffffffffc
DECL|macro|BM_02_45
mdefine_line|#define BM_02_45 BM_45_02
DECL|macro|BM_46_02
mdefine_line|#define BM_46_02 0x00007ffffffffffc
DECL|macro|BM_02_46
mdefine_line|#define BM_02_46 BM_46_02
DECL|macro|BM_47_02
mdefine_line|#define BM_47_02 0x0000fffffffffffc
DECL|macro|BM_02_47
mdefine_line|#define BM_02_47 BM_47_02
DECL|macro|BM_48_02
mdefine_line|#define BM_48_02 0x0001fffffffffffc
DECL|macro|BM_02_48
mdefine_line|#define BM_02_48 BM_48_02
DECL|macro|BM_49_02
mdefine_line|#define BM_49_02 0x0003fffffffffffc
DECL|macro|BM_02_49
mdefine_line|#define BM_02_49 BM_49_02
DECL|macro|BM_50_02
mdefine_line|#define BM_50_02 0x0007fffffffffffc
DECL|macro|BM_02_50
mdefine_line|#define BM_02_50 BM_50_02
DECL|macro|BM_51_02
mdefine_line|#define BM_51_02 0x000ffffffffffffc
DECL|macro|BM_02_51
mdefine_line|#define BM_02_51 BM_51_02
DECL|macro|BM_52_02
mdefine_line|#define BM_52_02 0x001ffffffffffffc
DECL|macro|BM_02_52
mdefine_line|#define BM_02_52 BM_52_02
DECL|macro|BM_53_02
mdefine_line|#define BM_53_02 0x003ffffffffffffc
DECL|macro|BM_02_53
mdefine_line|#define BM_02_53 BM_53_02
DECL|macro|BM_54_02
mdefine_line|#define BM_54_02 0x007ffffffffffffc
DECL|macro|BM_02_54
mdefine_line|#define BM_02_54 BM_54_02
DECL|macro|BM_55_02
mdefine_line|#define BM_55_02 0x00fffffffffffffc
DECL|macro|BM_02_55
mdefine_line|#define BM_02_55 BM_55_02
DECL|macro|BM_56_02
mdefine_line|#define BM_56_02 0x01fffffffffffffc
DECL|macro|BM_02_56
mdefine_line|#define BM_02_56 BM_56_02
DECL|macro|BM_57_02
mdefine_line|#define BM_57_02 0x03fffffffffffffc
DECL|macro|BM_02_57
mdefine_line|#define BM_02_57 BM_57_02
DECL|macro|BM_58_02
mdefine_line|#define BM_58_02 0x07fffffffffffffc
DECL|macro|BM_02_58
mdefine_line|#define BM_02_58 BM_58_02
DECL|macro|BM_59_02
mdefine_line|#define BM_59_02 0x0ffffffffffffffc
DECL|macro|BM_02_59
mdefine_line|#define BM_02_59 BM_59_02
DECL|macro|BM_60_02
mdefine_line|#define BM_60_02 0x1ffffffffffffffc
DECL|macro|BM_02_60
mdefine_line|#define BM_02_60 BM_60_02
DECL|macro|BM_61_02
mdefine_line|#define BM_61_02 0x3ffffffffffffffc
DECL|macro|BM_02_61
mdefine_line|#define BM_02_61 BM_61_02
DECL|macro|BM_62_02
mdefine_line|#define BM_62_02 0x7ffffffffffffffc
DECL|macro|BM_02_62
mdefine_line|#define BM_02_62 BM_62_02
DECL|macro|BM_63_02
mdefine_line|#define BM_63_02 0xfffffffffffffffc
DECL|macro|BM_02_63
mdefine_line|#define BM_02_63 BM_63_02
DECL|macro|BM_03_03
mdefine_line|#define BM_03_03 0x0000000000000008
DECL|macro|BM_04_03
mdefine_line|#define BM_04_03 0x0000000000000018
DECL|macro|BM_03_04
mdefine_line|#define BM_03_04 BM_04_03
DECL|macro|BM_05_03
mdefine_line|#define BM_05_03 0x0000000000000038
DECL|macro|BM_03_05
mdefine_line|#define BM_03_05 BM_05_03
DECL|macro|BM_06_03
mdefine_line|#define BM_06_03 0x0000000000000078
DECL|macro|BM_03_06
mdefine_line|#define BM_03_06 BM_06_03
DECL|macro|BM_07_03
mdefine_line|#define BM_07_03 0x00000000000000f8
DECL|macro|BM_03_07
mdefine_line|#define BM_03_07 BM_07_03
DECL|macro|BM_08_03
mdefine_line|#define BM_08_03 0x00000000000001f8
DECL|macro|BM_03_08
mdefine_line|#define BM_03_08 BM_08_03
DECL|macro|BM_09_03
mdefine_line|#define BM_09_03 0x00000000000003f8
DECL|macro|BM_03_09
mdefine_line|#define BM_03_09 BM_09_03
DECL|macro|BM_10_03
mdefine_line|#define BM_10_03 0x00000000000007f8
DECL|macro|BM_03_10
mdefine_line|#define BM_03_10 BM_10_03
DECL|macro|BM_11_03
mdefine_line|#define BM_11_03 0x0000000000000ff8
DECL|macro|BM_03_11
mdefine_line|#define BM_03_11 BM_11_03
DECL|macro|BM_12_03
mdefine_line|#define BM_12_03 0x0000000000001ff8
DECL|macro|BM_03_12
mdefine_line|#define BM_03_12 BM_12_03
DECL|macro|BM_13_03
mdefine_line|#define BM_13_03 0x0000000000003ff8
DECL|macro|BM_03_13
mdefine_line|#define BM_03_13 BM_13_03
DECL|macro|BM_14_03
mdefine_line|#define BM_14_03 0x0000000000007ff8
DECL|macro|BM_03_14
mdefine_line|#define BM_03_14 BM_14_03
DECL|macro|BM_15_03
mdefine_line|#define BM_15_03 0x000000000000fff8
DECL|macro|BM_03_15
mdefine_line|#define BM_03_15 BM_15_03
DECL|macro|BM_16_03
mdefine_line|#define BM_16_03 0x000000000001fff8
DECL|macro|BM_03_16
mdefine_line|#define BM_03_16 BM_16_03
DECL|macro|BM_17_03
mdefine_line|#define BM_17_03 0x000000000003fff8
DECL|macro|BM_03_17
mdefine_line|#define BM_03_17 BM_17_03
DECL|macro|BM_18_03
mdefine_line|#define BM_18_03 0x000000000007fff8
DECL|macro|BM_03_18
mdefine_line|#define BM_03_18 BM_18_03
DECL|macro|BM_19_03
mdefine_line|#define BM_19_03 0x00000000000ffff8
DECL|macro|BM_03_19
mdefine_line|#define BM_03_19 BM_19_03
DECL|macro|BM_20_03
mdefine_line|#define BM_20_03 0x00000000001ffff8
DECL|macro|BM_03_20
mdefine_line|#define BM_03_20 BM_20_03
DECL|macro|BM_21_03
mdefine_line|#define BM_21_03 0x00000000003ffff8
DECL|macro|BM_03_21
mdefine_line|#define BM_03_21 BM_21_03
DECL|macro|BM_22_03
mdefine_line|#define BM_22_03 0x00000000007ffff8
DECL|macro|BM_03_22
mdefine_line|#define BM_03_22 BM_22_03
DECL|macro|BM_23_03
mdefine_line|#define BM_23_03 0x0000000000fffff8
DECL|macro|BM_03_23
mdefine_line|#define BM_03_23 BM_23_03
DECL|macro|BM_24_03
mdefine_line|#define BM_24_03 0x0000000001fffff8
DECL|macro|BM_03_24
mdefine_line|#define BM_03_24 BM_24_03
DECL|macro|BM_25_03
mdefine_line|#define BM_25_03 0x0000000003fffff8
DECL|macro|BM_03_25
mdefine_line|#define BM_03_25 BM_25_03
DECL|macro|BM_26_03
mdefine_line|#define BM_26_03 0x0000000007fffff8
DECL|macro|BM_03_26
mdefine_line|#define BM_03_26 BM_26_03
DECL|macro|BM_27_03
mdefine_line|#define BM_27_03 0x000000000ffffff8
DECL|macro|BM_03_27
mdefine_line|#define BM_03_27 BM_27_03
DECL|macro|BM_28_03
mdefine_line|#define BM_28_03 0x000000001ffffff8
DECL|macro|BM_03_28
mdefine_line|#define BM_03_28 BM_28_03
DECL|macro|BM_29_03
mdefine_line|#define BM_29_03 0x000000003ffffff8
DECL|macro|BM_03_29
mdefine_line|#define BM_03_29 BM_29_03
DECL|macro|BM_30_03
mdefine_line|#define BM_30_03 0x000000007ffffff8
DECL|macro|BM_03_30
mdefine_line|#define BM_03_30 BM_30_03
DECL|macro|BM_31_03
mdefine_line|#define BM_31_03 0x00000000fffffff8
DECL|macro|BM_03_31
mdefine_line|#define BM_03_31 BM_31_03
DECL|macro|BM_32_03
mdefine_line|#define BM_32_03 0x00000001fffffff8
DECL|macro|BM_03_32
mdefine_line|#define BM_03_32 BM_32_03
DECL|macro|BM_33_03
mdefine_line|#define BM_33_03 0x00000003fffffff8
DECL|macro|BM_03_33
mdefine_line|#define BM_03_33 BM_33_03
DECL|macro|BM_34_03
mdefine_line|#define BM_34_03 0x00000007fffffff8
DECL|macro|BM_03_34
mdefine_line|#define BM_03_34 BM_34_03
DECL|macro|BM_35_03
mdefine_line|#define BM_35_03 0x0000000ffffffff8
DECL|macro|BM_03_35
mdefine_line|#define BM_03_35 BM_35_03
DECL|macro|BM_36_03
mdefine_line|#define BM_36_03 0x0000001ffffffff8
DECL|macro|BM_03_36
mdefine_line|#define BM_03_36 BM_36_03
DECL|macro|BM_37_03
mdefine_line|#define BM_37_03 0x0000003ffffffff8
DECL|macro|BM_03_37
mdefine_line|#define BM_03_37 BM_37_03
DECL|macro|BM_38_03
mdefine_line|#define BM_38_03 0x0000007ffffffff8
DECL|macro|BM_03_38
mdefine_line|#define BM_03_38 BM_38_03
DECL|macro|BM_39_03
mdefine_line|#define BM_39_03 0x000000fffffffff8
DECL|macro|BM_03_39
mdefine_line|#define BM_03_39 BM_39_03
DECL|macro|BM_40_03
mdefine_line|#define BM_40_03 0x000001fffffffff8
DECL|macro|BM_03_40
mdefine_line|#define BM_03_40 BM_40_03
DECL|macro|BM_41_03
mdefine_line|#define BM_41_03 0x000003fffffffff8
DECL|macro|BM_03_41
mdefine_line|#define BM_03_41 BM_41_03
DECL|macro|BM_42_03
mdefine_line|#define BM_42_03 0x000007fffffffff8
DECL|macro|BM_03_42
mdefine_line|#define BM_03_42 BM_42_03
DECL|macro|BM_43_03
mdefine_line|#define BM_43_03 0x00000ffffffffff8
DECL|macro|BM_03_43
mdefine_line|#define BM_03_43 BM_43_03
DECL|macro|BM_44_03
mdefine_line|#define BM_44_03 0x00001ffffffffff8
DECL|macro|BM_03_44
mdefine_line|#define BM_03_44 BM_44_03
DECL|macro|BM_45_03
mdefine_line|#define BM_45_03 0x00003ffffffffff8
DECL|macro|BM_03_45
mdefine_line|#define BM_03_45 BM_45_03
DECL|macro|BM_46_03
mdefine_line|#define BM_46_03 0x00007ffffffffff8
DECL|macro|BM_03_46
mdefine_line|#define BM_03_46 BM_46_03
DECL|macro|BM_47_03
mdefine_line|#define BM_47_03 0x0000fffffffffff8
DECL|macro|BM_03_47
mdefine_line|#define BM_03_47 BM_47_03
DECL|macro|BM_48_03
mdefine_line|#define BM_48_03 0x0001fffffffffff8
DECL|macro|BM_03_48
mdefine_line|#define BM_03_48 BM_48_03
DECL|macro|BM_49_03
mdefine_line|#define BM_49_03 0x0003fffffffffff8
DECL|macro|BM_03_49
mdefine_line|#define BM_03_49 BM_49_03
DECL|macro|BM_50_03
mdefine_line|#define BM_50_03 0x0007fffffffffff8
DECL|macro|BM_03_50
mdefine_line|#define BM_03_50 BM_50_03
DECL|macro|BM_51_03
mdefine_line|#define BM_51_03 0x000ffffffffffff8
DECL|macro|BM_03_51
mdefine_line|#define BM_03_51 BM_51_03
DECL|macro|BM_52_03
mdefine_line|#define BM_52_03 0x001ffffffffffff8
DECL|macro|BM_03_52
mdefine_line|#define BM_03_52 BM_52_03
DECL|macro|BM_53_03
mdefine_line|#define BM_53_03 0x003ffffffffffff8
DECL|macro|BM_03_53
mdefine_line|#define BM_03_53 BM_53_03
DECL|macro|BM_54_03
mdefine_line|#define BM_54_03 0x007ffffffffffff8
DECL|macro|BM_03_54
mdefine_line|#define BM_03_54 BM_54_03
DECL|macro|BM_55_03
mdefine_line|#define BM_55_03 0x00fffffffffffff8
DECL|macro|BM_03_55
mdefine_line|#define BM_03_55 BM_55_03
DECL|macro|BM_56_03
mdefine_line|#define BM_56_03 0x01fffffffffffff8
DECL|macro|BM_03_56
mdefine_line|#define BM_03_56 BM_56_03
DECL|macro|BM_57_03
mdefine_line|#define BM_57_03 0x03fffffffffffff8
DECL|macro|BM_03_57
mdefine_line|#define BM_03_57 BM_57_03
DECL|macro|BM_58_03
mdefine_line|#define BM_58_03 0x07fffffffffffff8
DECL|macro|BM_03_58
mdefine_line|#define BM_03_58 BM_58_03
DECL|macro|BM_59_03
mdefine_line|#define BM_59_03 0x0ffffffffffffff8
DECL|macro|BM_03_59
mdefine_line|#define BM_03_59 BM_59_03
DECL|macro|BM_60_03
mdefine_line|#define BM_60_03 0x1ffffffffffffff8
DECL|macro|BM_03_60
mdefine_line|#define BM_03_60 BM_60_03
DECL|macro|BM_61_03
mdefine_line|#define BM_61_03 0x3ffffffffffffff8
DECL|macro|BM_03_61
mdefine_line|#define BM_03_61 BM_61_03
DECL|macro|BM_62_03
mdefine_line|#define BM_62_03 0x7ffffffffffffff8
DECL|macro|BM_03_62
mdefine_line|#define BM_03_62 BM_62_03
DECL|macro|BM_63_03
mdefine_line|#define BM_63_03 0xfffffffffffffff8
DECL|macro|BM_03_63
mdefine_line|#define BM_03_63 BM_63_03
DECL|macro|BM_04_04
mdefine_line|#define BM_04_04 0x0000000000000010
DECL|macro|BM_05_04
mdefine_line|#define BM_05_04 0x0000000000000030
DECL|macro|BM_04_05
mdefine_line|#define BM_04_05 BM_05_04
DECL|macro|BM_06_04
mdefine_line|#define BM_06_04 0x0000000000000070
DECL|macro|BM_04_06
mdefine_line|#define BM_04_06 BM_06_04
DECL|macro|BM_07_04
mdefine_line|#define BM_07_04 0x00000000000000f0
DECL|macro|BM_04_07
mdefine_line|#define BM_04_07 BM_07_04
DECL|macro|BM_08_04
mdefine_line|#define BM_08_04 0x00000000000001f0
DECL|macro|BM_04_08
mdefine_line|#define BM_04_08 BM_08_04
DECL|macro|BM_09_04
mdefine_line|#define BM_09_04 0x00000000000003f0
DECL|macro|BM_04_09
mdefine_line|#define BM_04_09 BM_09_04
DECL|macro|BM_10_04
mdefine_line|#define BM_10_04 0x00000000000007f0
DECL|macro|BM_04_10
mdefine_line|#define BM_04_10 BM_10_04
DECL|macro|BM_11_04
mdefine_line|#define BM_11_04 0x0000000000000ff0
DECL|macro|BM_04_11
mdefine_line|#define BM_04_11 BM_11_04
DECL|macro|BM_12_04
mdefine_line|#define BM_12_04 0x0000000000001ff0
DECL|macro|BM_04_12
mdefine_line|#define BM_04_12 BM_12_04
DECL|macro|BM_13_04
mdefine_line|#define BM_13_04 0x0000000000003ff0
DECL|macro|BM_04_13
mdefine_line|#define BM_04_13 BM_13_04
DECL|macro|BM_14_04
mdefine_line|#define BM_14_04 0x0000000000007ff0
DECL|macro|BM_04_14
mdefine_line|#define BM_04_14 BM_14_04
DECL|macro|BM_15_04
mdefine_line|#define BM_15_04 0x000000000000fff0
DECL|macro|BM_04_15
mdefine_line|#define BM_04_15 BM_15_04
DECL|macro|BM_16_04
mdefine_line|#define BM_16_04 0x000000000001fff0
DECL|macro|BM_04_16
mdefine_line|#define BM_04_16 BM_16_04
DECL|macro|BM_17_04
mdefine_line|#define BM_17_04 0x000000000003fff0
DECL|macro|BM_04_17
mdefine_line|#define BM_04_17 BM_17_04
DECL|macro|BM_18_04
mdefine_line|#define BM_18_04 0x000000000007fff0
DECL|macro|BM_04_18
mdefine_line|#define BM_04_18 BM_18_04
DECL|macro|BM_19_04
mdefine_line|#define BM_19_04 0x00000000000ffff0
DECL|macro|BM_04_19
mdefine_line|#define BM_04_19 BM_19_04
DECL|macro|BM_20_04
mdefine_line|#define BM_20_04 0x00000000001ffff0
DECL|macro|BM_04_20
mdefine_line|#define BM_04_20 BM_20_04
DECL|macro|BM_21_04
mdefine_line|#define BM_21_04 0x00000000003ffff0
DECL|macro|BM_04_21
mdefine_line|#define BM_04_21 BM_21_04
DECL|macro|BM_22_04
mdefine_line|#define BM_22_04 0x00000000007ffff0
DECL|macro|BM_04_22
mdefine_line|#define BM_04_22 BM_22_04
DECL|macro|BM_23_04
mdefine_line|#define BM_23_04 0x0000000000fffff0
DECL|macro|BM_04_23
mdefine_line|#define BM_04_23 BM_23_04
DECL|macro|BM_24_04
mdefine_line|#define BM_24_04 0x0000000001fffff0
DECL|macro|BM_04_24
mdefine_line|#define BM_04_24 BM_24_04
DECL|macro|BM_25_04
mdefine_line|#define BM_25_04 0x0000000003fffff0
DECL|macro|BM_04_25
mdefine_line|#define BM_04_25 BM_25_04
DECL|macro|BM_26_04
mdefine_line|#define BM_26_04 0x0000000007fffff0
DECL|macro|BM_04_26
mdefine_line|#define BM_04_26 BM_26_04
DECL|macro|BM_27_04
mdefine_line|#define BM_27_04 0x000000000ffffff0
DECL|macro|BM_04_27
mdefine_line|#define BM_04_27 BM_27_04
DECL|macro|BM_28_04
mdefine_line|#define BM_28_04 0x000000001ffffff0
DECL|macro|BM_04_28
mdefine_line|#define BM_04_28 BM_28_04
DECL|macro|BM_29_04
mdefine_line|#define BM_29_04 0x000000003ffffff0
DECL|macro|BM_04_29
mdefine_line|#define BM_04_29 BM_29_04
DECL|macro|BM_30_04
mdefine_line|#define BM_30_04 0x000000007ffffff0
DECL|macro|BM_04_30
mdefine_line|#define BM_04_30 BM_30_04
DECL|macro|BM_31_04
mdefine_line|#define BM_31_04 0x00000000fffffff0
DECL|macro|BM_04_31
mdefine_line|#define BM_04_31 BM_31_04
DECL|macro|BM_32_04
mdefine_line|#define BM_32_04 0x00000001fffffff0
DECL|macro|BM_04_32
mdefine_line|#define BM_04_32 BM_32_04
DECL|macro|BM_33_04
mdefine_line|#define BM_33_04 0x00000003fffffff0
DECL|macro|BM_04_33
mdefine_line|#define BM_04_33 BM_33_04
DECL|macro|BM_34_04
mdefine_line|#define BM_34_04 0x00000007fffffff0
DECL|macro|BM_04_34
mdefine_line|#define BM_04_34 BM_34_04
DECL|macro|BM_35_04
mdefine_line|#define BM_35_04 0x0000000ffffffff0
DECL|macro|BM_04_35
mdefine_line|#define BM_04_35 BM_35_04
DECL|macro|BM_36_04
mdefine_line|#define BM_36_04 0x0000001ffffffff0
DECL|macro|BM_04_36
mdefine_line|#define BM_04_36 BM_36_04
DECL|macro|BM_37_04
mdefine_line|#define BM_37_04 0x0000003ffffffff0
DECL|macro|BM_04_37
mdefine_line|#define BM_04_37 BM_37_04
DECL|macro|BM_38_04
mdefine_line|#define BM_38_04 0x0000007ffffffff0
DECL|macro|BM_04_38
mdefine_line|#define BM_04_38 BM_38_04
DECL|macro|BM_39_04
mdefine_line|#define BM_39_04 0x000000fffffffff0
DECL|macro|BM_04_39
mdefine_line|#define BM_04_39 BM_39_04
DECL|macro|BM_40_04
mdefine_line|#define BM_40_04 0x000001fffffffff0
DECL|macro|BM_04_40
mdefine_line|#define BM_04_40 BM_40_04
DECL|macro|BM_41_04
mdefine_line|#define BM_41_04 0x000003fffffffff0
DECL|macro|BM_04_41
mdefine_line|#define BM_04_41 BM_41_04
DECL|macro|BM_42_04
mdefine_line|#define BM_42_04 0x000007fffffffff0
DECL|macro|BM_04_42
mdefine_line|#define BM_04_42 BM_42_04
DECL|macro|BM_43_04
mdefine_line|#define BM_43_04 0x00000ffffffffff0
DECL|macro|BM_04_43
mdefine_line|#define BM_04_43 BM_43_04
DECL|macro|BM_44_04
mdefine_line|#define BM_44_04 0x00001ffffffffff0
DECL|macro|BM_04_44
mdefine_line|#define BM_04_44 BM_44_04
DECL|macro|BM_45_04
mdefine_line|#define BM_45_04 0x00003ffffffffff0
DECL|macro|BM_04_45
mdefine_line|#define BM_04_45 BM_45_04
DECL|macro|BM_46_04
mdefine_line|#define BM_46_04 0x00007ffffffffff0
DECL|macro|BM_04_46
mdefine_line|#define BM_04_46 BM_46_04
DECL|macro|BM_47_04
mdefine_line|#define BM_47_04 0x0000fffffffffff0
DECL|macro|BM_04_47
mdefine_line|#define BM_04_47 BM_47_04
DECL|macro|BM_48_04
mdefine_line|#define BM_48_04 0x0001fffffffffff0
DECL|macro|BM_04_48
mdefine_line|#define BM_04_48 BM_48_04
DECL|macro|BM_49_04
mdefine_line|#define BM_49_04 0x0003fffffffffff0
DECL|macro|BM_04_49
mdefine_line|#define BM_04_49 BM_49_04
DECL|macro|BM_50_04
mdefine_line|#define BM_50_04 0x0007fffffffffff0
DECL|macro|BM_04_50
mdefine_line|#define BM_04_50 BM_50_04
DECL|macro|BM_51_04
mdefine_line|#define BM_51_04 0x000ffffffffffff0
DECL|macro|BM_04_51
mdefine_line|#define BM_04_51 BM_51_04
DECL|macro|BM_52_04
mdefine_line|#define BM_52_04 0x001ffffffffffff0
DECL|macro|BM_04_52
mdefine_line|#define BM_04_52 BM_52_04
DECL|macro|BM_53_04
mdefine_line|#define BM_53_04 0x003ffffffffffff0
DECL|macro|BM_04_53
mdefine_line|#define BM_04_53 BM_53_04
DECL|macro|BM_54_04
mdefine_line|#define BM_54_04 0x007ffffffffffff0
DECL|macro|BM_04_54
mdefine_line|#define BM_04_54 BM_54_04
DECL|macro|BM_55_04
mdefine_line|#define BM_55_04 0x00fffffffffffff0
DECL|macro|BM_04_55
mdefine_line|#define BM_04_55 BM_55_04
DECL|macro|BM_56_04
mdefine_line|#define BM_56_04 0x01fffffffffffff0
DECL|macro|BM_04_56
mdefine_line|#define BM_04_56 BM_56_04
DECL|macro|BM_57_04
mdefine_line|#define BM_57_04 0x03fffffffffffff0
DECL|macro|BM_04_57
mdefine_line|#define BM_04_57 BM_57_04
DECL|macro|BM_58_04
mdefine_line|#define BM_58_04 0x07fffffffffffff0
DECL|macro|BM_04_58
mdefine_line|#define BM_04_58 BM_58_04
DECL|macro|BM_59_04
mdefine_line|#define BM_59_04 0x0ffffffffffffff0
DECL|macro|BM_04_59
mdefine_line|#define BM_04_59 BM_59_04
DECL|macro|BM_60_04
mdefine_line|#define BM_60_04 0x1ffffffffffffff0
DECL|macro|BM_04_60
mdefine_line|#define BM_04_60 BM_60_04
DECL|macro|BM_61_04
mdefine_line|#define BM_61_04 0x3ffffffffffffff0
DECL|macro|BM_04_61
mdefine_line|#define BM_04_61 BM_61_04
DECL|macro|BM_62_04
mdefine_line|#define BM_62_04 0x7ffffffffffffff0
DECL|macro|BM_04_62
mdefine_line|#define BM_04_62 BM_62_04
DECL|macro|BM_63_04
mdefine_line|#define BM_63_04 0xfffffffffffffff0
DECL|macro|BM_04_63
mdefine_line|#define BM_04_63 BM_63_04
DECL|macro|BM_05_05
mdefine_line|#define BM_05_05 0x0000000000000020
DECL|macro|BM_06_05
mdefine_line|#define BM_06_05 0x0000000000000060
DECL|macro|BM_05_06
mdefine_line|#define BM_05_06 BM_06_05
DECL|macro|BM_07_05
mdefine_line|#define BM_07_05 0x00000000000000e0
DECL|macro|BM_05_07
mdefine_line|#define BM_05_07 BM_07_05
DECL|macro|BM_08_05
mdefine_line|#define BM_08_05 0x00000000000001e0
DECL|macro|BM_05_08
mdefine_line|#define BM_05_08 BM_08_05
DECL|macro|BM_09_05
mdefine_line|#define BM_09_05 0x00000000000003e0
DECL|macro|BM_05_09
mdefine_line|#define BM_05_09 BM_09_05
DECL|macro|BM_10_05
mdefine_line|#define BM_10_05 0x00000000000007e0
DECL|macro|BM_05_10
mdefine_line|#define BM_05_10 BM_10_05
DECL|macro|BM_11_05
mdefine_line|#define BM_11_05 0x0000000000000fe0
DECL|macro|BM_05_11
mdefine_line|#define BM_05_11 BM_11_05
DECL|macro|BM_12_05
mdefine_line|#define BM_12_05 0x0000000000001fe0
DECL|macro|BM_05_12
mdefine_line|#define BM_05_12 BM_12_05
DECL|macro|BM_13_05
mdefine_line|#define BM_13_05 0x0000000000003fe0
DECL|macro|BM_05_13
mdefine_line|#define BM_05_13 BM_13_05
DECL|macro|BM_14_05
mdefine_line|#define BM_14_05 0x0000000000007fe0
DECL|macro|BM_05_14
mdefine_line|#define BM_05_14 BM_14_05
DECL|macro|BM_15_05
mdefine_line|#define BM_15_05 0x000000000000ffe0
DECL|macro|BM_05_15
mdefine_line|#define BM_05_15 BM_15_05
DECL|macro|BM_16_05
mdefine_line|#define BM_16_05 0x000000000001ffe0
DECL|macro|BM_05_16
mdefine_line|#define BM_05_16 BM_16_05
DECL|macro|BM_17_05
mdefine_line|#define BM_17_05 0x000000000003ffe0
DECL|macro|BM_05_17
mdefine_line|#define BM_05_17 BM_17_05
DECL|macro|BM_18_05
mdefine_line|#define BM_18_05 0x000000000007ffe0
DECL|macro|BM_05_18
mdefine_line|#define BM_05_18 BM_18_05
DECL|macro|BM_19_05
mdefine_line|#define BM_19_05 0x00000000000fffe0
DECL|macro|BM_05_19
mdefine_line|#define BM_05_19 BM_19_05
DECL|macro|BM_20_05
mdefine_line|#define BM_20_05 0x00000000001fffe0
DECL|macro|BM_05_20
mdefine_line|#define BM_05_20 BM_20_05
DECL|macro|BM_21_05
mdefine_line|#define BM_21_05 0x00000000003fffe0
DECL|macro|BM_05_21
mdefine_line|#define BM_05_21 BM_21_05
DECL|macro|BM_22_05
mdefine_line|#define BM_22_05 0x00000000007fffe0
DECL|macro|BM_05_22
mdefine_line|#define BM_05_22 BM_22_05
DECL|macro|BM_23_05
mdefine_line|#define BM_23_05 0x0000000000ffffe0
DECL|macro|BM_05_23
mdefine_line|#define BM_05_23 BM_23_05
DECL|macro|BM_24_05
mdefine_line|#define BM_24_05 0x0000000001ffffe0
DECL|macro|BM_05_24
mdefine_line|#define BM_05_24 BM_24_05
DECL|macro|BM_25_05
mdefine_line|#define BM_25_05 0x0000000003ffffe0
DECL|macro|BM_05_25
mdefine_line|#define BM_05_25 BM_25_05
DECL|macro|BM_26_05
mdefine_line|#define BM_26_05 0x0000000007ffffe0
DECL|macro|BM_05_26
mdefine_line|#define BM_05_26 BM_26_05
DECL|macro|BM_27_05
mdefine_line|#define BM_27_05 0x000000000fffffe0
DECL|macro|BM_05_27
mdefine_line|#define BM_05_27 BM_27_05
DECL|macro|BM_28_05
mdefine_line|#define BM_28_05 0x000000001fffffe0
DECL|macro|BM_05_28
mdefine_line|#define BM_05_28 BM_28_05
DECL|macro|BM_29_05
mdefine_line|#define BM_29_05 0x000000003fffffe0
DECL|macro|BM_05_29
mdefine_line|#define BM_05_29 BM_29_05
DECL|macro|BM_30_05
mdefine_line|#define BM_30_05 0x000000007fffffe0
DECL|macro|BM_05_30
mdefine_line|#define BM_05_30 BM_30_05
DECL|macro|BM_31_05
mdefine_line|#define BM_31_05 0x00000000ffffffe0
DECL|macro|BM_05_31
mdefine_line|#define BM_05_31 BM_31_05
DECL|macro|BM_32_05
mdefine_line|#define BM_32_05 0x00000001ffffffe0
DECL|macro|BM_05_32
mdefine_line|#define BM_05_32 BM_32_05
DECL|macro|BM_33_05
mdefine_line|#define BM_33_05 0x00000003ffffffe0
DECL|macro|BM_05_33
mdefine_line|#define BM_05_33 BM_33_05
DECL|macro|BM_34_05
mdefine_line|#define BM_34_05 0x00000007ffffffe0
DECL|macro|BM_05_34
mdefine_line|#define BM_05_34 BM_34_05
DECL|macro|BM_35_05
mdefine_line|#define BM_35_05 0x0000000fffffffe0
DECL|macro|BM_05_35
mdefine_line|#define BM_05_35 BM_35_05
DECL|macro|BM_36_05
mdefine_line|#define BM_36_05 0x0000001fffffffe0
DECL|macro|BM_05_36
mdefine_line|#define BM_05_36 BM_36_05
DECL|macro|BM_37_05
mdefine_line|#define BM_37_05 0x0000003fffffffe0
DECL|macro|BM_05_37
mdefine_line|#define BM_05_37 BM_37_05
DECL|macro|BM_38_05
mdefine_line|#define BM_38_05 0x0000007fffffffe0
DECL|macro|BM_05_38
mdefine_line|#define BM_05_38 BM_38_05
DECL|macro|BM_39_05
mdefine_line|#define BM_39_05 0x000000ffffffffe0
DECL|macro|BM_05_39
mdefine_line|#define BM_05_39 BM_39_05
DECL|macro|BM_40_05
mdefine_line|#define BM_40_05 0x000001ffffffffe0
DECL|macro|BM_05_40
mdefine_line|#define BM_05_40 BM_40_05
DECL|macro|BM_41_05
mdefine_line|#define BM_41_05 0x000003ffffffffe0
DECL|macro|BM_05_41
mdefine_line|#define BM_05_41 BM_41_05
DECL|macro|BM_42_05
mdefine_line|#define BM_42_05 0x000007ffffffffe0
DECL|macro|BM_05_42
mdefine_line|#define BM_05_42 BM_42_05
DECL|macro|BM_43_05
mdefine_line|#define BM_43_05 0x00000fffffffffe0
DECL|macro|BM_05_43
mdefine_line|#define BM_05_43 BM_43_05
DECL|macro|BM_44_05
mdefine_line|#define BM_44_05 0x00001fffffffffe0
DECL|macro|BM_05_44
mdefine_line|#define BM_05_44 BM_44_05
DECL|macro|BM_45_05
mdefine_line|#define BM_45_05 0x00003fffffffffe0
DECL|macro|BM_05_45
mdefine_line|#define BM_05_45 BM_45_05
DECL|macro|BM_46_05
mdefine_line|#define BM_46_05 0x00007fffffffffe0
DECL|macro|BM_05_46
mdefine_line|#define BM_05_46 BM_46_05
DECL|macro|BM_47_05
mdefine_line|#define BM_47_05 0x0000ffffffffffe0
DECL|macro|BM_05_47
mdefine_line|#define BM_05_47 BM_47_05
DECL|macro|BM_48_05
mdefine_line|#define BM_48_05 0x0001ffffffffffe0
DECL|macro|BM_05_48
mdefine_line|#define BM_05_48 BM_48_05
DECL|macro|BM_49_05
mdefine_line|#define BM_49_05 0x0003ffffffffffe0
DECL|macro|BM_05_49
mdefine_line|#define BM_05_49 BM_49_05
DECL|macro|BM_50_05
mdefine_line|#define BM_50_05 0x0007ffffffffffe0
DECL|macro|BM_05_50
mdefine_line|#define BM_05_50 BM_50_05
DECL|macro|BM_51_05
mdefine_line|#define BM_51_05 0x000fffffffffffe0
DECL|macro|BM_05_51
mdefine_line|#define BM_05_51 BM_51_05
DECL|macro|BM_52_05
mdefine_line|#define BM_52_05 0x001fffffffffffe0
DECL|macro|BM_05_52
mdefine_line|#define BM_05_52 BM_52_05
DECL|macro|BM_53_05
mdefine_line|#define BM_53_05 0x003fffffffffffe0
DECL|macro|BM_05_53
mdefine_line|#define BM_05_53 BM_53_05
DECL|macro|BM_54_05
mdefine_line|#define BM_54_05 0x007fffffffffffe0
DECL|macro|BM_05_54
mdefine_line|#define BM_05_54 BM_54_05
DECL|macro|BM_55_05
mdefine_line|#define BM_55_05 0x00ffffffffffffe0
DECL|macro|BM_05_55
mdefine_line|#define BM_05_55 BM_55_05
DECL|macro|BM_56_05
mdefine_line|#define BM_56_05 0x01ffffffffffffe0
DECL|macro|BM_05_56
mdefine_line|#define BM_05_56 BM_56_05
DECL|macro|BM_57_05
mdefine_line|#define BM_57_05 0x03ffffffffffffe0
DECL|macro|BM_05_57
mdefine_line|#define BM_05_57 BM_57_05
DECL|macro|BM_58_05
mdefine_line|#define BM_58_05 0x07ffffffffffffe0
DECL|macro|BM_05_58
mdefine_line|#define BM_05_58 BM_58_05
DECL|macro|BM_59_05
mdefine_line|#define BM_59_05 0x0fffffffffffffe0
DECL|macro|BM_05_59
mdefine_line|#define BM_05_59 BM_59_05
DECL|macro|BM_60_05
mdefine_line|#define BM_60_05 0x1fffffffffffffe0
DECL|macro|BM_05_60
mdefine_line|#define BM_05_60 BM_60_05
DECL|macro|BM_61_05
mdefine_line|#define BM_61_05 0x3fffffffffffffe0
DECL|macro|BM_05_61
mdefine_line|#define BM_05_61 BM_61_05
DECL|macro|BM_62_05
mdefine_line|#define BM_62_05 0x7fffffffffffffe0
DECL|macro|BM_05_62
mdefine_line|#define BM_05_62 BM_62_05
DECL|macro|BM_63_05
mdefine_line|#define BM_63_05 0xffffffffffffffe0
DECL|macro|BM_05_63
mdefine_line|#define BM_05_63 BM_63_05
DECL|macro|BM_06_06
mdefine_line|#define BM_06_06 0x0000000000000040
DECL|macro|BM_07_06
mdefine_line|#define BM_07_06 0x00000000000000c0
DECL|macro|BM_06_07
mdefine_line|#define BM_06_07 BM_07_06
DECL|macro|BM_08_06
mdefine_line|#define BM_08_06 0x00000000000001c0
DECL|macro|BM_06_08
mdefine_line|#define BM_06_08 BM_08_06
DECL|macro|BM_09_06
mdefine_line|#define BM_09_06 0x00000000000003c0
DECL|macro|BM_06_09
mdefine_line|#define BM_06_09 BM_09_06
DECL|macro|BM_10_06
mdefine_line|#define BM_10_06 0x00000000000007c0
DECL|macro|BM_06_10
mdefine_line|#define BM_06_10 BM_10_06
DECL|macro|BM_11_06
mdefine_line|#define BM_11_06 0x0000000000000fc0
DECL|macro|BM_06_11
mdefine_line|#define BM_06_11 BM_11_06
DECL|macro|BM_12_06
mdefine_line|#define BM_12_06 0x0000000000001fc0
DECL|macro|BM_06_12
mdefine_line|#define BM_06_12 BM_12_06
DECL|macro|BM_13_06
mdefine_line|#define BM_13_06 0x0000000000003fc0
DECL|macro|BM_06_13
mdefine_line|#define BM_06_13 BM_13_06
DECL|macro|BM_14_06
mdefine_line|#define BM_14_06 0x0000000000007fc0
DECL|macro|BM_06_14
mdefine_line|#define BM_06_14 BM_14_06
DECL|macro|BM_15_06
mdefine_line|#define BM_15_06 0x000000000000ffc0
DECL|macro|BM_06_15
mdefine_line|#define BM_06_15 BM_15_06
DECL|macro|BM_16_06
mdefine_line|#define BM_16_06 0x000000000001ffc0
DECL|macro|BM_06_16
mdefine_line|#define BM_06_16 BM_16_06
DECL|macro|BM_17_06
mdefine_line|#define BM_17_06 0x000000000003ffc0
DECL|macro|BM_06_17
mdefine_line|#define BM_06_17 BM_17_06
DECL|macro|BM_18_06
mdefine_line|#define BM_18_06 0x000000000007ffc0
DECL|macro|BM_06_18
mdefine_line|#define BM_06_18 BM_18_06
DECL|macro|BM_19_06
mdefine_line|#define BM_19_06 0x00000000000fffc0
DECL|macro|BM_06_19
mdefine_line|#define BM_06_19 BM_19_06
DECL|macro|BM_20_06
mdefine_line|#define BM_20_06 0x00000000001fffc0
DECL|macro|BM_06_20
mdefine_line|#define BM_06_20 BM_20_06
DECL|macro|BM_21_06
mdefine_line|#define BM_21_06 0x00000000003fffc0
DECL|macro|BM_06_21
mdefine_line|#define BM_06_21 BM_21_06
DECL|macro|BM_22_06
mdefine_line|#define BM_22_06 0x00000000007fffc0
DECL|macro|BM_06_22
mdefine_line|#define BM_06_22 BM_22_06
DECL|macro|BM_23_06
mdefine_line|#define BM_23_06 0x0000000000ffffc0
DECL|macro|BM_06_23
mdefine_line|#define BM_06_23 BM_23_06
DECL|macro|BM_24_06
mdefine_line|#define BM_24_06 0x0000000001ffffc0
DECL|macro|BM_06_24
mdefine_line|#define BM_06_24 BM_24_06
DECL|macro|BM_25_06
mdefine_line|#define BM_25_06 0x0000000003ffffc0
DECL|macro|BM_06_25
mdefine_line|#define BM_06_25 BM_25_06
DECL|macro|BM_26_06
mdefine_line|#define BM_26_06 0x0000000007ffffc0
DECL|macro|BM_06_26
mdefine_line|#define BM_06_26 BM_26_06
DECL|macro|BM_27_06
mdefine_line|#define BM_27_06 0x000000000fffffc0
DECL|macro|BM_06_27
mdefine_line|#define BM_06_27 BM_27_06
DECL|macro|BM_28_06
mdefine_line|#define BM_28_06 0x000000001fffffc0
DECL|macro|BM_06_28
mdefine_line|#define BM_06_28 BM_28_06
DECL|macro|BM_29_06
mdefine_line|#define BM_29_06 0x000000003fffffc0
DECL|macro|BM_06_29
mdefine_line|#define BM_06_29 BM_29_06
DECL|macro|BM_30_06
mdefine_line|#define BM_30_06 0x000000007fffffc0
DECL|macro|BM_06_30
mdefine_line|#define BM_06_30 BM_30_06
DECL|macro|BM_31_06
mdefine_line|#define BM_31_06 0x00000000ffffffc0
DECL|macro|BM_06_31
mdefine_line|#define BM_06_31 BM_31_06
DECL|macro|BM_32_06
mdefine_line|#define BM_32_06 0x00000001ffffffc0
DECL|macro|BM_06_32
mdefine_line|#define BM_06_32 BM_32_06
DECL|macro|BM_33_06
mdefine_line|#define BM_33_06 0x00000003ffffffc0
DECL|macro|BM_06_33
mdefine_line|#define BM_06_33 BM_33_06
DECL|macro|BM_34_06
mdefine_line|#define BM_34_06 0x00000007ffffffc0
DECL|macro|BM_06_34
mdefine_line|#define BM_06_34 BM_34_06
DECL|macro|BM_35_06
mdefine_line|#define BM_35_06 0x0000000fffffffc0
DECL|macro|BM_06_35
mdefine_line|#define BM_06_35 BM_35_06
DECL|macro|BM_36_06
mdefine_line|#define BM_36_06 0x0000001fffffffc0
DECL|macro|BM_06_36
mdefine_line|#define BM_06_36 BM_36_06
DECL|macro|BM_37_06
mdefine_line|#define BM_37_06 0x0000003fffffffc0
DECL|macro|BM_06_37
mdefine_line|#define BM_06_37 BM_37_06
DECL|macro|BM_38_06
mdefine_line|#define BM_38_06 0x0000007fffffffc0
DECL|macro|BM_06_38
mdefine_line|#define BM_06_38 BM_38_06
DECL|macro|BM_39_06
mdefine_line|#define BM_39_06 0x000000ffffffffc0
DECL|macro|BM_06_39
mdefine_line|#define BM_06_39 BM_39_06
DECL|macro|BM_40_06
mdefine_line|#define BM_40_06 0x000001ffffffffc0
DECL|macro|BM_06_40
mdefine_line|#define BM_06_40 BM_40_06
DECL|macro|BM_41_06
mdefine_line|#define BM_41_06 0x000003ffffffffc0
DECL|macro|BM_06_41
mdefine_line|#define BM_06_41 BM_41_06
DECL|macro|BM_42_06
mdefine_line|#define BM_42_06 0x000007ffffffffc0
DECL|macro|BM_06_42
mdefine_line|#define BM_06_42 BM_42_06
DECL|macro|BM_43_06
mdefine_line|#define BM_43_06 0x00000fffffffffc0
DECL|macro|BM_06_43
mdefine_line|#define BM_06_43 BM_43_06
DECL|macro|BM_44_06
mdefine_line|#define BM_44_06 0x00001fffffffffc0
DECL|macro|BM_06_44
mdefine_line|#define BM_06_44 BM_44_06
DECL|macro|BM_45_06
mdefine_line|#define BM_45_06 0x00003fffffffffc0
DECL|macro|BM_06_45
mdefine_line|#define BM_06_45 BM_45_06
DECL|macro|BM_46_06
mdefine_line|#define BM_46_06 0x00007fffffffffc0
DECL|macro|BM_06_46
mdefine_line|#define BM_06_46 BM_46_06
DECL|macro|BM_47_06
mdefine_line|#define BM_47_06 0x0000ffffffffffc0
DECL|macro|BM_06_47
mdefine_line|#define BM_06_47 BM_47_06
DECL|macro|BM_48_06
mdefine_line|#define BM_48_06 0x0001ffffffffffc0
DECL|macro|BM_06_48
mdefine_line|#define BM_06_48 BM_48_06
DECL|macro|BM_49_06
mdefine_line|#define BM_49_06 0x0003ffffffffffc0
DECL|macro|BM_06_49
mdefine_line|#define BM_06_49 BM_49_06
DECL|macro|BM_50_06
mdefine_line|#define BM_50_06 0x0007ffffffffffc0
DECL|macro|BM_06_50
mdefine_line|#define BM_06_50 BM_50_06
DECL|macro|BM_51_06
mdefine_line|#define BM_51_06 0x000fffffffffffc0
DECL|macro|BM_06_51
mdefine_line|#define BM_06_51 BM_51_06
DECL|macro|BM_52_06
mdefine_line|#define BM_52_06 0x001fffffffffffc0
DECL|macro|BM_06_52
mdefine_line|#define BM_06_52 BM_52_06
DECL|macro|BM_53_06
mdefine_line|#define BM_53_06 0x003fffffffffffc0
DECL|macro|BM_06_53
mdefine_line|#define BM_06_53 BM_53_06
DECL|macro|BM_54_06
mdefine_line|#define BM_54_06 0x007fffffffffffc0
DECL|macro|BM_06_54
mdefine_line|#define BM_06_54 BM_54_06
DECL|macro|BM_55_06
mdefine_line|#define BM_55_06 0x00ffffffffffffc0
DECL|macro|BM_06_55
mdefine_line|#define BM_06_55 BM_55_06
DECL|macro|BM_56_06
mdefine_line|#define BM_56_06 0x01ffffffffffffc0
DECL|macro|BM_06_56
mdefine_line|#define BM_06_56 BM_56_06
DECL|macro|BM_57_06
mdefine_line|#define BM_57_06 0x03ffffffffffffc0
DECL|macro|BM_06_57
mdefine_line|#define BM_06_57 BM_57_06
DECL|macro|BM_58_06
mdefine_line|#define BM_58_06 0x07ffffffffffffc0
DECL|macro|BM_06_58
mdefine_line|#define BM_06_58 BM_58_06
DECL|macro|BM_59_06
mdefine_line|#define BM_59_06 0x0fffffffffffffc0
DECL|macro|BM_06_59
mdefine_line|#define BM_06_59 BM_59_06
DECL|macro|BM_60_06
mdefine_line|#define BM_60_06 0x1fffffffffffffc0
DECL|macro|BM_06_60
mdefine_line|#define BM_06_60 BM_60_06
DECL|macro|BM_61_06
mdefine_line|#define BM_61_06 0x3fffffffffffffc0
DECL|macro|BM_06_61
mdefine_line|#define BM_06_61 BM_61_06
DECL|macro|BM_62_06
mdefine_line|#define BM_62_06 0x7fffffffffffffc0
DECL|macro|BM_06_62
mdefine_line|#define BM_06_62 BM_62_06
DECL|macro|BM_63_06
mdefine_line|#define BM_63_06 0xffffffffffffffc0
DECL|macro|BM_06_63
mdefine_line|#define BM_06_63 BM_63_06
DECL|macro|BM_07_07
mdefine_line|#define BM_07_07 0x0000000000000080
DECL|macro|BM_08_07
mdefine_line|#define BM_08_07 0x0000000000000180
DECL|macro|BM_07_08
mdefine_line|#define BM_07_08 BM_08_07
DECL|macro|BM_09_07
mdefine_line|#define BM_09_07 0x0000000000000380
DECL|macro|BM_07_09
mdefine_line|#define BM_07_09 BM_09_07
DECL|macro|BM_10_07
mdefine_line|#define BM_10_07 0x0000000000000780
DECL|macro|BM_07_10
mdefine_line|#define BM_07_10 BM_10_07
DECL|macro|BM_11_07
mdefine_line|#define BM_11_07 0x0000000000000f80
DECL|macro|BM_07_11
mdefine_line|#define BM_07_11 BM_11_07
DECL|macro|BM_12_07
mdefine_line|#define BM_12_07 0x0000000000001f80
DECL|macro|BM_07_12
mdefine_line|#define BM_07_12 BM_12_07
DECL|macro|BM_13_07
mdefine_line|#define BM_13_07 0x0000000000003f80
DECL|macro|BM_07_13
mdefine_line|#define BM_07_13 BM_13_07
DECL|macro|BM_14_07
mdefine_line|#define BM_14_07 0x0000000000007f80
DECL|macro|BM_07_14
mdefine_line|#define BM_07_14 BM_14_07
DECL|macro|BM_15_07
mdefine_line|#define BM_15_07 0x000000000000ff80
DECL|macro|BM_07_15
mdefine_line|#define BM_07_15 BM_15_07
DECL|macro|BM_16_07
mdefine_line|#define BM_16_07 0x000000000001ff80
DECL|macro|BM_07_16
mdefine_line|#define BM_07_16 BM_16_07
DECL|macro|BM_17_07
mdefine_line|#define BM_17_07 0x000000000003ff80
DECL|macro|BM_07_17
mdefine_line|#define BM_07_17 BM_17_07
DECL|macro|BM_18_07
mdefine_line|#define BM_18_07 0x000000000007ff80
DECL|macro|BM_07_18
mdefine_line|#define BM_07_18 BM_18_07
DECL|macro|BM_19_07
mdefine_line|#define BM_19_07 0x00000000000fff80
DECL|macro|BM_07_19
mdefine_line|#define BM_07_19 BM_19_07
DECL|macro|BM_20_07
mdefine_line|#define BM_20_07 0x00000000001fff80
DECL|macro|BM_07_20
mdefine_line|#define BM_07_20 BM_20_07
DECL|macro|BM_21_07
mdefine_line|#define BM_21_07 0x00000000003fff80
DECL|macro|BM_07_21
mdefine_line|#define BM_07_21 BM_21_07
DECL|macro|BM_22_07
mdefine_line|#define BM_22_07 0x00000000007fff80
DECL|macro|BM_07_22
mdefine_line|#define BM_07_22 BM_22_07
DECL|macro|BM_23_07
mdefine_line|#define BM_23_07 0x0000000000ffff80
DECL|macro|BM_07_23
mdefine_line|#define BM_07_23 BM_23_07
DECL|macro|BM_24_07
mdefine_line|#define BM_24_07 0x0000000001ffff80
DECL|macro|BM_07_24
mdefine_line|#define BM_07_24 BM_24_07
DECL|macro|BM_25_07
mdefine_line|#define BM_25_07 0x0000000003ffff80
DECL|macro|BM_07_25
mdefine_line|#define BM_07_25 BM_25_07
DECL|macro|BM_26_07
mdefine_line|#define BM_26_07 0x0000000007ffff80
DECL|macro|BM_07_26
mdefine_line|#define BM_07_26 BM_26_07
DECL|macro|BM_27_07
mdefine_line|#define BM_27_07 0x000000000fffff80
DECL|macro|BM_07_27
mdefine_line|#define BM_07_27 BM_27_07
DECL|macro|BM_28_07
mdefine_line|#define BM_28_07 0x000000001fffff80
DECL|macro|BM_07_28
mdefine_line|#define BM_07_28 BM_28_07
DECL|macro|BM_29_07
mdefine_line|#define BM_29_07 0x000000003fffff80
DECL|macro|BM_07_29
mdefine_line|#define BM_07_29 BM_29_07
DECL|macro|BM_30_07
mdefine_line|#define BM_30_07 0x000000007fffff80
DECL|macro|BM_07_30
mdefine_line|#define BM_07_30 BM_30_07
DECL|macro|BM_31_07
mdefine_line|#define BM_31_07 0x00000000ffffff80
DECL|macro|BM_07_31
mdefine_line|#define BM_07_31 BM_31_07
DECL|macro|BM_32_07
mdefine_line|#define BM_32_07 0x00000001ffffff80
DECL|macro|BM_07_32
mdefine_line|#define BM_07_32 BM_32_07
DECL|macro|BM_33_07
mdefine_line|#define BM_33_07 0x00000003ffffff80
DECL|macro|BM_07_33
mdefine_line|#define BM_07_33 BM_33_07
DECL|macro|BM_34_07
mdefine_line|#define BM_34_07 0x00000007ffffff80
DECL|macro|BM_07_34
mdefine_line|#define BM_07_34 BM_34_07
DECL|macro|BM_35_07
mdefine_line|#define BM_35_07 0x0000000fffffff80
DECL|macro|BM_07_35
mdefine_line|#define BM_07_35 BM_35_07
DECL|macro|BM_36_07
mdefine_line|#define BM_36_07 0x0000001fffffff80
DECL|macro|BM_07_36
mdefine_line|#define BM_07_36 BM_36_07
DECL|macro|BM_37_07
mdefine_line|#define BM_37_07 0x0000003fffffff80
DECL|macro|BM_07_37
mdefine_line|#define BM_07_37 BM_37_07
DECL|macro|BM_38_07
mdefine_line|#define BM_38_07 0x0000007fffffff80
DECL|macro|BM_07_38
mdefine_line|#define BM_07_38 BM_38_07
DECL|macro|BM_39_07
mdefine_line|#define BM_39_07 0x000000ffffffff80
DECL|macro|BM_07_39
mdefine_line|#define BM_07_39 BM_39_07
DECL|macro|BM_40_07
mdefine_line|#define BM_40_07 0x000001ffffffff80
DECL|macro|BM_07_40
mdefine_line|#define BM_07_40 BM_40_07
DECL|macro|BM_41_07
mdefine_line|#define BM_41_07 0x000003ffffffff80
DECL|macro|BM_07_41
mdefine_line|#define BM_07_41 BM_41_07
DECL|macro|BM_42_07
mdefine_line|#define BM_42_07 0x000007ffffffff80
DECL|macro|BM_07_42
mdefine_line|#define BM_07_42 BM_42_07
DECL|macro|BM_43_07
mdefine_line|#define BM_43_07 0x00000fffffffff80
DECL|macro|BM_07_43
mdefine_line|#define BM_07_43 BM_43_07
DECL|macro|BM_44_07
mdefine_line|#define BM_44_07 0x00001fffffffff80
DECL|macro|BM_07_44
mdefine_line|#define BM_07_44 BM_44_07
DECL|macro|BM_45_07
mdefine_line|#define BM_45_07 0x00003fffffffff80
DECL|macro|BM_07_45
mdefine_line|#define BM_07_45 BM_45_07
DECL|macro|BM_46_07
mdefine_line|#define BM_46_07 0x00007fffffffff80
DECL|macro|BM_07_46
mdefine_line|#define BM_07_46 BM_46_07
DECL|macro|BM_47_07
mdefine_line|#define BM_47_07 0x0000ffffffffff80
DECL|macro|BM_07_47
mdefine_line|#define BM_07_47 BM_47_07
DECL|macro|BM_48_07
mdefine_line|#define BM_48_07 0x0001ffffffffff80
DECL|macro|BM_07_48
mdefine_line|#define BM_07_48 BM_48_07
DECL|macro|BM_49_07
mdefine_line|#define BM_49_07 0x0003ffffffffff80
DECL|macro|BM_07_49
mdefine_line|#define BM_07_49 BM_49_07
DECL|macro|BM_50_07
mdefine_line|#define BM_50_07 0x0007ffffffffff80
DECL|macro|BM_07_50
mdefine_line|#define BM_07_50 BM_50_07
DECL|macro|BM_51_07
mdefine_line|#define BM_51_07 0x000fffffffffff80
DECL|macro|BM_07_51
mdefine_line|#define BM_07_51 BM_51_07
DECL|macro|BM_52_07
mdefine_line|#define BM_52_07 0x001fffffffffff80
DECL|macro|BM_07_52
mdefine_line|#define BM_07_52 BM_52_07
DECL|macro|BM_53_07
mdefine_line|#define BM_53_07 0x003fffffffffff80
DECL|macro|BM_07_53
mdefine_line|#define BM_07_53 BM_53_07
DECL|macro|BM_54_07
mdefine_line|#define BM_54_07 0x007fffffffffff80
DECL|macro|BM_07_54
mdefine_line|#define BM_07_54 BM_54_07
DECL|macro|BM_55_07
mdefine_line|#define BM_55_07 0x00ffffffffffff80
DECL|macro|BM_07_55
mdefine_line|#define BM_07_55 BM_55_07
DECL|macro|BM_56_07
mdefine_line|#define BM_56_07 0x01ffffffffffff80
DECL|macro|BM_07_56
mdefine_line|#define BM_07_56 BM_56_07
DECL|macro|BM_57_07
mdefine_line|#define BM_57_07 0x03ffffffffffff80
DECL|macro|BM_07_57
mdefine_line|#define BM_07_57 BM_57_07
DECL|macro|BM_58_07
mdefine_line|#define BM_58_07 0x07ffffffffffff80
DECL|macro|BM_07_58
mdefine_line|#define BM_07_58 BM_58_07
DECL|macro|BM_59_07
mdefine_line|#define BM_59_07 0x0fffffffffffff80
DECL|macro|BM_07_59
mdefine_line|#define BM_07_59 BM_59_07
DECL|macro|BM_60_07
mdefine_line|#define BM_60_07 0x1fffffffffffff80
DECL|macro|BM_07_60
mdefine_line|#define BM_07_60 BM_60_07
DECL|macro|BM_61_07
mdefine_line|#define BM_61_07 0x3fffffffffffff80
DECL|macro|BM_07_61
mdefine_line|#define BM_07_61 BM_61_07
DECL|macro|BM_62_07
mdefine_line|#define BM_62_07 0x7fffffffffffff80
DECL|macro|BM_07_62
mdefine_line|#define BM_07_62 BM_62_07
DECL|macro|BM_63_07
mdefine_line|#define BM_63_07 0xffffffffffffff80
DECL|macro|BM_07_63
mdefine_line|#define BM_07_63 BM_63_07
DECL|macro|BM_08_08
mdefine_line|#define BM_08_08 0x0000000000000100
DECL|macro|BM_09_08
mdefine_line|#define BM_09_08 0x0000000000000300
DECL|macro|BM_08_09
mdefine_line|#define BM_08_09 BM_09_08
DECL|macro|BM_10_08
mdefine_line|#define BM_10_08 0x0000000000000700
DECL|macro|BM_08_10
mdefine_line|#define BM_08_10 BM_10_08
DECL|macro|BM_11_08
mdefine_line|#define BM_11_08 0x0000000000000f00
DECL|macro|BM_08_11
mdefine_line|#define BM_08_11 BM_11_08
DECL|macro|BM_12_08
mdefine_line|#define BM_12_08 0x0000000000001f00
DECL|macro|BM_08_12
mdefine_line|#define BM_08_12 BM_12_08
DECL|macro|BM_13_08
mdefine_line|#define BM_13_08 0x0000000000003f00
DECL|macro|BM_08_13
mdefine_line|#define BM_08_13 BM_13_08
DECL|macro|BM_14_08
mdefine_line|#define BM_14_08 0x0000000000007f00
DECL|macro|BM_08_14
mdefine_line|#define BM_08_14 BM_14_08
DECL|macro|BM_15_08
mdefine_line|#define BM_15_08 0x000000000000ff00
DECL|macro|BM_08_15
mdefine_line|#define BM_08_15 BM_15_08
DECL|macro|BM_16_08
mdefine_line|#define BM_16_08 0x000000000001ff00
DECL|macro|BM_08_16
mdefine_line|#define BM_08_16 BM_16_08
DECL|macro|BM_17_08
mdefine_line|#define BM_17_08 0x000000000003ff00
DECL|macro|BM_08_17
mdefine_line|#define BM_08_17 BM_17_08
DECL|macro|BM_18_08
mdefine_line|#define BM_18_08 0x000000000007ff00
DECL|macro|BM_08_18
mdefine_line|#define BM_08_18 BM_18_08
DECL|macro|BM_19_08
mdefine_line|#define BM_19_08 0x00000000000fff00
DECL|macro|BM_08_19
mdefine_line|#define BM_08_19 BM_19_08
DECL|macro|BM_20_08
mdefine_line|#define BM_20_08 0x00000000001fff00
DECL|macro|BM_08_20
mdefine_line|#define BM_08_20 BM_20_08
DECL|macro|BM_21_08
mdefine_line|#define BM_21_08 0x00000000003fff00
DECL|macro|BM_08_21
mdefine_line|#define BM_08_21 BM_21_08
DECL|macro|BM_22_08
mdefine_line|#define BM_22_08 0x00000000007fff00
DECL|macro|BM_08_22
mdefine_line|#define BM_08_22 BM_22_08
DECL|macro|BM_23_08
mdefine_line|#define BM_23_08 0x0000000000ffff00
DECL|macro|BM_08_23
mdefine_line|#define BM_08_23 BM_23_08
DECL|macro|BM_24_08
mdefine_line|#define BM_24_08 0x0000000001ffff00
DECL|macro|BM_08_24
mdefine_line|#define BM_08_24 BM_24_08
DECL|macro|BM_25_08
mdefine_line|#define BM_25_08 0x0000000003ffff00
DECL|macro|BM_08_25
mdefine_line|#define BM_08_25 BM_25_08
DECL|macro|BM_26_08
mdefine_line|#define BM_26_08 0x0000000007ffff00
DECL|macro|BM_08_26
mdefine_line|#define BM_08_26 BM_26_08
DECL|macro|BM_27_08
mdefine_line|#define BM_27_08 0x000000000fffff00
DECL|macro|BM_08_27
mdefine_line|#define BM_08_27 BM_27_08
DECL|macro|BM_28_08
mdefine_line|#define BM_28_08 0x000000001fffff00
DECL|macro|BM_08_28
mdefine_line|#define BM_08_28 BM_28_08
DECL|macro|BM_29_08
mdefine_line|#define BM_29_08 0x000000003fffff00
DECL|macro|BM_08_29
mdefine_line|#define BM_08_29 BM_29_08
DECL|macro|BM_30_08
mdefine_line|#define BM_30_08 0x000000007fffff00
DECL|macro|BM_08_30
mdefine_line|#define BM_08_30 BM_30_08
DECL|macro|BM_31_08
mdefine_line|#define BM_31_08 0x00000000ffffff00
DECL|macro|BM_08_31
mdefine_line|#define BM_08_31 BM_31_08
DECL|macro|BM_32_08
mdefine_line|#define BM_32_08 0x00000001ffffff00
DECL|macro|BM_08_32
mdefine_line|#define BM_08_32 BM_32_08
DECL|macro|BM_33_08
mdefine_line|#define BM_33_08 0x00000003ffffff00
DECL|macro|BM_08_33
mdefine_line|#define BM_08_33 BM_33_08
DECL|macro|BM_34_08
mdefine_line|#define BM_34_08 0x00000007ffffff00
DECL|macro|BM_08_34
mdefine_line|#define BM_08_34 BM_34_08
DECL|macro|BM_35_08
mdefine_line|#define BM_35_08 0x0000000fffffff00
DECL|macro|BM_08_35
mdefine_line|#define BM_08_35 BM_35_08
DECL|macro|BM_36_08
mdefine_line|#define BM_36_08 0x0000001fffffff00
DECL|macro|BM_08_36
mdefine_line|#define BM_08_36 BM_36_08
DECL|macro|BM_37_08
mdefine_line|#define BM_37_08 0x0000003fffffff00
DECL|macro|BM_08_37
mdefine_line|#define BM_08_37 BM_37_08
DECL|macro|BM_38_08
mdefine_line|#define BM_38_08 0x0000007fffffff00
DECL|macro|BM_08_38
mdefine_line|#define BM_08_38 BM_38_08
DECL|macro|BM_39_08
mdefine_line|#define BM_39_08 0x000000ffffffff00
DECL|macro|BM_08_39
mdefine_line|#define BM_08_39 BM_39_08
DECL|macro|BM_40_08
mdefine_line|#define BM_40_08 0x000001ffffffff00
DECL|macro|BM_08_40
mdefine_line|#define BM_08_40 BM_40_08
DECL|macro|BM_41_08
mdefine_line|#define BM_41_08 0x000003ffffffff00
DECL|macro|BM_08_41
mdefine_line|#define BM_08_41 BM_41_08
DECL|macro|BM_42_08
mdefine_line|#define BM_42_08 0x000007ffffffff00
DECL|macro|BM_08_42
mdefine_line|#define BM_08_42 BM_42_08
DECL|macro|BM_43_08
mdefine_line|#define BM_43_08 0x00000fffffffff00
DECL|macro|BM_08_43
mdefine_line|#define BM_08_43 BM_43_08
DECL|macro|BM_44_08
mdefine_line|#define BM_44_08 0x00001fffffffff00
DECL|macro|BM_08_44
mdefine_line|#define BM_08_44 BM_44_08
DECL|macro|BM_45_08
mdefine_line|#define BM_45_08 0x00003fffffffff00
DECL|macro|BM_08_45
mdefine_line|#define BM_08_45 BM_45_08
DECL|macro|BM_46_08
mdefine_line|#define BM_46_08 0x00007fffffffff00
DECL|macro|BM_08_46
mdefine_line|#define BM_08_46 BM_46_08
DECL|macro|BM_47_08
mdefine_line|#define BM_47_08 0x0000ffffffffff00
DECL|macro|BM_08_47
mdefine_line|#define BM_08_47 BM_47_08
DECL|macro|BM_48_08
mdefine_line|#define BM_48_08 0x0001ffffffffff00
DECL|macro|BM_08_48
mdefine_line|#define BM_08_48 BM_48_08
DECL|macro|BM_49_08
mdefine_line|#define BM_49_08 0x0003ffffffffff00
DECL|macro|BM_08_49
mdefine_line|#define BM_08_49 BM_49_08
DECL|macro|BM_50_08
mdefine_line|#define BM_50_08 0x0007ffffffffff00
DECL|macro|BM_08_50
mdefine_line|#define BM_08_50 BM_50_08
DECL|macro|BM_51_08
mdefine_line|#define BM_51_08 0x000fffffffffff00
DECL|macro|BM_08_51
mdefine_line|#define BM_08_51 BM_51_08
DECL|macro|BM_52_08
mdefine_line|#define BM_52_08 0x001fffffffffff00
DECL|macro|BM_08_52
mdefine_line|#define BM_08_52 BM_52_08
DECL|macro|BM_53_08
mdefine_line|#define BM_53_08 0x003fffffffffff00
DECL|macro|BM_08_53
mdefine_line|#define BM_08_53 BM_53_08
DECL|macro|BM_54_08
mdefine_line|#define BM_54_08 0x007fffffffffff00
DECL|macro|BM_08_54
mdefine_line|#define BM_08_54 BM_54_08
DECL|macro|BM_55_08
mdefine_line|#define BM_55_08 0x00ffffffffffff00
DECL|macro|BM_08_55
mdefine_line|#define BM_08_55 BM_55_08
DECL|macro|BM_56_08
mdefine_line|#define BM_56_08 0x01ffffffffffff00
DECL|macro|BM_08_56
mdefine_line|#define BM_08_56 BM_56_08
DECL|macro|BM_57_08
mdefine_line|#define BM_57_08 0x03ffffffffffff00
DECL|macro|BM_08_57
mdefine_line|#define BM_08_57 BM_57_08
DECL|macro|BM_58_08
mdefine_line|#define BM_58_08 0x07ffffffffffff00
DECL|macro|BM_08_58
mdefine_line|#define BM_08_58 BM_58_08
DECL|macro|BM_59_08
mdefine_line|#define BM_59_08 0x0fffffffffffff00
DECL|macro|BM_08_59
mdefine_line|#define BM_08_59 BM_59_08
DECL|macro|BM_60_08
mdefine_line|#define BM_60_08 0x1fffffffffffff00
DECL|macro|BM_08_60
mdefine_line|#define BM_08_60 BM_60_08
DECL|macro|BM_61_08
mdefine_line|#define BM_61_08 0x3fffffffffffff00
DECL|macro|BM_08_61
mdefine_line|#define BM_08_61 BM_61_08
DECL|macro|BM_62_08
mdefine_line|#define BM_62_08 0x7fffffffffffff00
DECL|macro|BM_08_62
mdefine_line|#define BM_08_62 BM_62_08
DECL|macro|BM_63_08
mdefine_line|#define BM_63_08 0xffffffffffffff00
DECL|macro|BM_08_63
mdefine_line|#define BM_08_63 BM_63_08
DECL|macro|BM_09_09
mdefine_line|#define BM_09_09 0x0000000000000200
DECL|macro|BM_10_09
mdefine_line|#define BM_10_09 0x0000000000000600
DECL|macro|BM_09_10
mdefine_line|#define BM_09_10 BM_10_09
DECL|macro|BM_11_09
mdefine_line|#define BM_11_09 0x0000000000000e00
DECL|macro|BM_09_11
mdefine_line|#define BM_09_11 BM_11_09
DECL|macro|BM_12_09
mdefine_line|#define BM_12_09 0x0000000000001e00
DECL|macro|BM_09_12
mdefine_line|#define BM_09_12 BM_12_09
DECL|macro|BM_13_09
mdefine_line|#define BM_13_09 0x0000000000003e00
DECL|macro|BM_09_13
mdefine_line|#define BM_09_13 BM_13_09
DECL|macro|BM_14_09
mdefine_line|#define BM_14_09 0x0000000000007e00
DECL|macro|BM_09_14
mdefine_line|#define BM_09_14 BM_14_09
DECL|macro|BM_15_09
mdefine_line|#define BM_15_09 0x000000000000fe00
DECL|macro|BM_09_15
mdefine_line|#define BM_09_15 BM_15_09
DECL|macro|BM_16_09
mdefine_line|#define BM_16_09 0x000000000001fe00
DECL|macro|BM_09_16
mdefine_line|#define BM_09_16 BM_16_09
DECL|macro|BM_17_09
mdefine_line|#define BM_17_09 0x000000000003fe00
DECL|macro|BM_09_17
mdefine_line|#define BM_09_17 BM_17_09
DECL|macro|BM_18_09
mdefine_line|#define BM_18_09 0x000000000007fe00
DECL|macro|BM_09_18
mdefine_line|#define BM_09_18 BM_18_09
DECL|macro|BM_19_09
mdefine_line|#define BM_19_09 0x00000000000ffe00
DECL|macro|BM_09_19
mdefine_line|#define BM_09_19 BM_19_09
DECL|macro|BM_20_09
mdefine_line|#define BM_20_09 0x00000000001ffe00
DECL|macro|BM_09_20
mdefine_line|#define BM_09_20 BM_20_09
DECL|macro|BM_21_09
mdefine_line|#define BM_21_09 0x00000000003ffe00
DECL|macro|BM_09_21
mdefine_line|#define BM_09_21 BM_21_09
DECL|macro|BM_22_09
mdefine_line|#define BM_22_09 0x00000000007ffe00
DECL|macro|BM_09_22
mdefine_line|#define BM_09_22 BM_22_09
DECL|macro|BM_23_09
mdefine_line|#define BM_23_09 0x0000000000fffe00
DECL|macro|BM_09_23
mdefine_line|#define BM_09_23 BM_23_09
DECL|macro|BM_24_09
mdefine_line|#define BM_24_09 0x0000000001fffe00
DECL|macro|BM_09_24
mdefine_line|#define BM_09_24 BM_24_09
DECL|macro|BM_25_09
mdefine_line|#define BM_25_09 0x0000000003fffe00
DECL|macro|BM_09_25
mdefine_line|#define BM_09_25 BM_25_09
DECL|macro|BM_26_09
mdefine_line|#define BM_26_09 0x0000000007fffe00
DECL|macro|BM_09_26
mdefine_line|#define BM_09_26 BM_26_09
DECL|macro|BM_27_09
mdefine_line|#define BM_27_09 0x000000000ffffe00
DECL|macro|BM_09_27
mdefine_line|#define BM_09_27 BM_27_09
DECL|macro|BM_28_09
mdefine_line|#define BM_28_09 0x000000001ffffe00
DECL|macro|BM_09_28
mdefine_line|#define BM_09_28 BM_28_09
DECL|macro|BM_29_09
mdefine_line|#define BM_29_09 0x000000003ffffe00
DECL|macro|BM_09_29
mdefine_line|#define BM_09_29 BM_29_09
DECL|macro|BM_30_09
mdefine_line|#define BM_30_09 0x000000007ffffe00
DECL|macro|BM_09_30
mdefine_line|#define BM_09_30 BM_30_09
DECL|macro|BM_31_09
mdefine_line|#define BM_31_09 0x00000000fffffe00
DECL|macro|BM_09_31
mdefine_line|#define BM_09_31 BM_31_09
DECL|macro|BM_32_09
mdefine_line|#define BM_32_09 0x00000001fffffe00
DECL|macro|BM_09_32
mdefine_line|#define BM_09_32 BM_32_09
DECL|macro|BM_33_09
mdefine_line|#define BM_33_09 0x00000003fffffe00
DECL|macro|BM_09_33
mdefine_line|#define BM_09_33 BM_33_09
DECL|macro|BM_34_09
mdefine_line|#define BM_34_09 0x00000007fffffe00
DECL|macro|BM_09_34
mdefine_line|#define BM_09_34 BM_34_09
DECL|macro|BM_35_09
mdefine_line|#define BM_35_09 0x0000000ffffffe00
DECL|macro|BM_09_35
mdefine_line|#define BM_09_35 BM_35_09
DECL|macro|BM_36_09
mdefine_line|#define BM_36_09 0x0000001ffffffe00
DECL|macro|BM_09_36
mdefine_line|#define BM_09_36 BM_36_09
DECL|macro|BM_37_09
mdefine_line|#define BM_37_09 0x0000003ffffffe00
DECL|macro|BM_09_37
mdefine_line|#define BM_09_37 BM_37_09
DECL|macro|BM_38_09
mdefine_line|#define BM_38_09 0x0000007ffffffe00
DECL|macro|BM_09_38
mdefine_line|#define BM_09_38 BM_38_09
DECL|macro|BM_39_09
mdefine_line|#define BM_39_09 0x000000fffffffe00
DECL|macro|BM_09_39
mdefine_line|#define BM_09_39 BM_39_09
DECL|macro|BM_40_09
mdefine_line|#define BM_40_09 0x000001fffffffe00
DECL|macro|BM_09_40
mdefine_line|#define BM_09_40 BM_40_09
DECL|macro|BM_41_09
mdefine_line|#define BM_41_09 0x000003fffffffe00
DECL|macro|BM_09_41
mdefine_line|#define BM_09_41 BM_41_09
DECL|macro|BM_42_09
mdefine_line|#define BM_42_09 0x000007fffffffe00
DECL|macro|BM_09_42
mdefine_line|#define BM_09_42 BM_42_09
DECL|macro|BM_43_09
mdefine_line|#define BM_43_09 0x00000ffffffffe00
DECL|macro|BM_09_43
mdefine_line|#define BM_09_43 BM_43_09
DECL|macro|BM_44_09
mdefine_line|#define BM_44_09 0x00001ffffffffe00
DECL|macro|BM_09_44
mdefine_line|#define BM_09_44 BM_44_09
DECL|macro|BM_45_09
mdefine_line|#define BM_45_09 0x00003ffffffffe00
DECL|macro|BM_09_45
mdefine_line|#define BM_09_45 BM_45_09
DECL|macro|BM_46_09
mdefine_line|#define BM_46_09 0x00007ffffffffe00
DECL|macro|BM_09_46
mdefine_line|#define BM_09_46 BM_46_09
DECL|macro|BM_47_09
mdefine_line|#define BM_47_09 0x0000fffffffffe00
DECL|macro|BM_09_47
mdefine_line|#define BM_09_47 BM_47_09
DECL|macro|BM_48_09
mdefine_line|#define BM_48_09 0x0001fffffffffe00
DECL|macro|BM_09_48
mdefine_line|#define BM_09_48 BM_48_09
DECL|macro|BM_49_09
mdefine_line|#define BM_49_09 0x0003fffffffffe00
DECL|macro|BM_09_49
mdefine_line|#define BM_09_49 BM_49_09
DECL|macro|BM_50_09
mdefine_line|#define BM_50_09 0x0007fffffffffe00
DECL|macro|BM_09_50
mdefine_line|#define BM_09_50 BM_50_09
DECL|macro|BM_51_09
mdefine_line|#define BM_51_09 0x000ffffffffffe00
DECL|macro|BM_09_51
mdefine_line|#define BM_09_51 BM_51_09
DECL|macro|BM_52_09
mdefine_line|#define BM_52_09 0x001ffffffffffe00
DECL|macro|BM_09_52
mdefine_line|#define BM_09_52 BM_52_09
DECL|macro|BM_53_09
mdefine_line|#define BM_53_09 0x003ffffffffffe00
DECL|macro|BM_09_53
mdefine_line|#define BM_09_53 BM_53_09
DECL|macro|BM_54_09
mdefine_line|#define BM_54_09 0x007ffffffffffe00
DECL|macro|BM_09_54
mdefine_line|#define BM_09_54 BM_54_09
DECL|macro|BM_55_09
mdefine_line|#define BM_55_09 0x00fffffffffffe00
DECL|macro|BM_09_55
mdefine_line|#define BM_09_55 BM_55_09
DECL|macro|BM_56_09
mdefine_line|#define BM_56_09 0x01fffffffffffe00
DECL|macro|BM_09_56
mdefine_line|#define BM_09_56 BM_56_09
DECL|macro|BM_57_09
mdefine_line|#define BM_57_09 0x03fffffffffffe00
DECL|macro|BM_09_57
mdefine_line|#define BM_09_57 BM_57_09
DECL|macro|BM_58_09
mdefine_line|#define BM_58_09 0x07fffffffffffe00
DECL|macro|BM_09_58
mdefine_line|#define BM_09_58 BM_58_09
DECL|macro|BM_59_09
mdefine_line|#define BM_59_09 0x0ffffffffffffe00
DECL|macro|BM_09_59
mdefine_line|#define BM_09_59 BM_59_09
DECL|macro|BM_60_09
mdefine_line|#define BM_60_09 0x1ffffffffffffe00
DECL|macro|BM_09_60
mdefine_line|#define BM_09_60 BM_60_09
DECL|macro|BM_61_09
mdefine_line|#define BM_61_09 0x3ffffffffffffe00
DECL|macro|BM_09_61
mdefine_line|#define BM_09_61 BM_61_09
DECL|macro|BM_62_09
mdefine_line|#define BM_62_09 0x7ffffffffffffe00
DECL|macro|BM_09_62
mdefine_line|#define BM_09_62 BM_62_09
DECL|macro|BM_63_09
mdefine_line|#define BM_63_09 0xfffffffffffffe00
DECL|macro|BM_09_63
mdefine_line|#define BM_09_63 BM_63_09
DECL|macro|BM_10_10
mdefine_line|#define BM_10_10 0x0000000000000400
DECL|macro|BM_11_10
mdefine_line|#define BM_11_10 0x0000000000000c00
DECL|macro|BM_10_11
mdefine_line|#define BM_10_11 BM_11_10
DECL|macro|BM_12_10
mdefine_line|#define BM_12_10 0x0000000000001c00
DECL|macro|BM_10_12
mdefine_line|#define BM_10_12 BM_12_10
DECL|macro|BM_13_10
mdefine_line|#define BM_13_10 0x0000000000003c00
DECL|macro|BM_10_13
mdefine_line|#define BM_10_13 BM_13_10
DECL|macro|BM_14_10
mdefine_line|#define BM_14_10 0x0000000000007c00
DECL|macro|BM_10_14
mdefine_line|#define BM_10_14 BM_14_10
DECL|macro|BM_15_10
mdefine_line|#define BM_15_10 0x000000000000fc00
DECL|macro|BM_10_15
mdefine_line|#define BM_10_15 BM_15_10
DECL|macro|BM_16_10
mdefine_line|#define BM_16_10 0x000000000001fc00
DECL|macro|BM_10_16
mdefine_line|#define BM_10_16 BM_16_10
DECL|macro|BM_17_10
mdefine_line|#define BM_17_10 0x000000000003fc00
DECL|macro|BM_10_17
mdefine_line|#define BM_10_17 BM_17_10
DECL|macro|BM_18_10
mdefine_line|#define BM_18_10 0x000000000007fc00
DECL|macro|BM_10_18
mdefine_line|#define BM_10_18 BM_18_10
DECL|macro|BM_19_10
mdefine_line|#define BM_19_10 0x00000000000ffc00
DECL|macro|BM_10_19
mdefine_line|#define BM_10_19 BM_19_10
DECL|macro|BM_20_10
mdefine_line|#define BM_20_10 0x00000000001ffc00
DECL|macro|BM_10_20
mdefine_line|#define BM_10_20 BM_20_10
DECL|macro|BM_21_10
mdefine_line|#define BM_21_10 0x00000000003ffc00
DECL|macro|BM_10_21
mdefine_line|#define BM_10_21 BM_21_10
DECL|macro|BM_22_10
mdefine_line|#define BM_22_10 0x00000000007ffc00
DECL|macro|BM_10_22
mdefine_line|#define BM_10_22 BM_22_10
DECL|macro|BM_23_10
mdefine_line|#define BM_23_10 0x0000000000fffc00
DECL|macro|BM_10_23
mdefine_line|#define BM_10_23 BM_23_10
DECL|macro|BM_24_10
mdefine_line|#define BM_24_10 0x0000000001fffc00
DECL|macro|BM_10_24
mdefine_line|#define BM_10_24 BM_24_10
DECL|macro|BM_25_10
mdefine_line|#define BM_25_10 0x0000000003fffc00
DECL|macro|BM_10_25
mdefine_line|#define BM_10_25 BM_25_10
DECL|macro|BM_26_10
mdefine_line|#define BM_26_10 0x0000000007fffc00
DECL|macro|BM_10_26
mdefine_line|#define BM_10_26 BM_26_10
DECL|macro|BM_27_10
mdefine_line|#define BM_27_10 0x000000000ffffc00
DECL|macro|BM_10_27
mdefine_line|#define BM_10_27 BM_27_10
DECL|macro|BM_28_10
mdefine_line|#define BM_28_10 0x000000001ffffc00
DECL|macro|BM_10_28
mdefine_line|#define BM_10_28 BM_28_10
DECL|macro|BM_29_10
mdefine_line|#define BM_29_10 0x000000003ffffc00
DECL|macro|BM_10_29
mdefine_line|#define BM_10_29 BM_29_10
DECL|macro|BM_30_10
mdefine_line|#define BM_30_10 0x000000007ffffc00
DECL|macro|BM_10_30
mdefine_line|#define BM_10_30 BM_30_10
DECL|macro|BM_31_10
mdefine_line|#define BM_31_10 0x00000000fffffc00
DECL|macro|BM_10_31
mdefine_line|#define BM_10_31 BM_31_10
DECL|macro|BM_32_10
mdefine_line|#define BM_32_10 0x00000001fffffc00
DECL|macro|BM_10_32
mdefine_line|#define BM_10_32 BM_32_10
DECL|macro|BM_33_10
mdefine_line|#define BM_33_10 0x00000003fffffc00
DECL|macro|BM_10_33
mdefine_line|#define BM_10_33 BM_33_10
DECL|macro|BM_34_10
mdefine_line|#define BM_34_10 0x00000007fffffc00
DECL|macro|BM_10_34
mdefine_line|#define BM_10_34 BM_34_10
DECL|macro|BM_35_10
mdefine_line|#define BM_35_10 0x0000000ffffffc00
DECL|macro|BM_10_35
mdefine_line|#define BM_10_35 BM_35_10
DECL|macro|BM_36_10
mdefine_line|#define BM_36_10 0x0000001ffffffc00
DECL|macro|BM_10_36
mdefine_line|#define BM_10_36 BM_36_10
DECL|macro|BM_37_10
mdefine_line|#define BM_37_10 0x0000003ffffffc00
DECL|macro|BM_10_37
mdefine_line|#define BM_10_37 BM_37_10
DECL|macro|BM_38_10
mdefine_line|#define BM_38_10 0x0000007ffffffc00
DECL|macro|BM_10_38
mdefine_line|#define BM_10_38 BM_38_10
DECL|macro|BM_39_10
mdefine_line|#define BM_39_10 0x000000fffffffc00
DECL|macro|BM_10_39
mdefine_line|#define BM_10_39 BM_39_10
DECL|macro|BM_40_10
mdefine_line|#define BM_40_10 0x000001fffffffc00
DECL|macro|BM_10_40
mdefine_line|#define BM_10_40 BM_40_10
DECL|macro|BM_41_10
mdefine_line|#define BM_41_10 0x000003fffffffc00
DECL|macro|BM_10_41
mdefine_line|#define BM_10_41 BM_41_10
DECL|macro|BM_42_10
mdefine_line|#define BM_42_10 0x000007fffffffc00
DECL|macro|BM_10_42
mdefine_line|#define BM_10_42 BM_42_10
DECL|macro|BM_43_10
mdefine_line|#define BM_43_10 0x00000ffffffffc00
DECL|macro|BM_10_43
mdefine_line|#define BM_10_43 BM_43_10
DECL|macro|BM_44_10
mdefine_line|#define BM_44_10 0x00001ffffffffc00
DECL|macro|BM_10_44
mdefine_line|#define BM_10_44 BM_44_10
DECL|macro|BM_45_10
mdefine_line|#define BM_45_10 0x00003ffffffffc00
DECL|macro|BM_10_45
mdefine_line|#define BM_10_45 BM_45_10
DECL|macro|BM_46_10
mdefine_line|#define BM_46_10 0x00007ffffffffc00
DECL|macro|BM_10_46
mdefine_line|#define BM_10_46 BM_46_10
DECL|macro|BM_47_10
mdefine_line|#define BM_47_10 0x0000fffffffffc00
DECL|macro|BM_10_47
mdefine_line|#define BM_10_47 BM_47_10
DECL|macro|BM_48_10
mdefine_line|#define BM_48_10 0x0001fffffffffc00
DECL|macro|BM_10_48
mdefine_line|#define BM_10_48 BM_48_10
DECL|macro|BM_49_10
mdefine_line|#define BM_49_10 0x0003fffffffffc00
DECL|macro|BM_10_49
mdefine_line|#define BM_10_49 BM_49_10
DECL|macro|BM_50_10
mdefine_line|#define BM_50_10 0x0007fffffffffc00
DECL|macro|BM_10_50
mdefine_line|#define BM_10_50 BM_50_10
DECL|macro|BM_51_10
mdefine_line|#define BM_51_10 0x000ffffffffffc00
DECL|macro|BM_10_51
mdefine_line|#define BM_10_51 BM_51_10
DECL|macro|BM_52_10
mdefine_line|#define BM_52_10 0x001ffffffffffc00
DECL|macro|BM_10_52
mdefine_line|#define BM_10_52 BM_52_10
DECL|macro|BM_53_10
mdefine_line|#define BM_53_10 0x003ffffffffffc00
DECL|macro|BM_10_53
mdefine_line|#define BM_10_53 BM_53_10
DECL|macro|BM_54_10
mdefine_line|#define BM_54_10 0x007ffffffffffc00
DECL|macro|BM_10_54
mdefine_line|#define BM_10_54 BM_54_10
DECL|macro|BM_55_10
mdefine_line|#define BM_55_10 0x00fffffffffffc00
DECL|macro|BM_10_55
mdefine_line|#define BM_10_55 BM_55_10
DECL|macro|BM_56_10
mdefine_line|#define BM_56_10 0x01fffffffffffc00
DECL|macro|BM_10_56
mdefine_line|#define BM_10_56 BM_56_10
DECL|macro|BM_57_10
mdefine_line|#define BM_57_10 0x03fffffffffffc00
DECL|macro|BM_10_57
mdefine_line|#define BM_10_57 BM_57_10
DECL|macro|BM_58_10
mdefine_line|#define BM_58_10 0x07fffffffffffc00
DECL|macro|BM_10_58
mdefine_line|#define BM_10_58 BM_58_10
DECL|macro|BM_59_10
mdefine_line|#define BM_59_10 0x0ffffffffffffc00
DECL|macro|BM_10_59
mdefine_line|#define BM_10_59 BM_59_10
DECL|macro|BM_60_10
mdefine_line|#define BM_60_10 0x1ffffffffffffc00
DECL|macro|BM_10_60
mdefine_line|#define BM_10_60 BM_60_10
DECL|macro|BM_61_10
mdefine_line|#define BM_61_10 0x3ffffffffffffc00
DECL|macro|BM_10_61
mdefine_line|#define BM_10_61 BM_61_10
DECL|macro|BM_62_10
mdefine_line|#define BM_62_10 0x7ffffffffffffc00
DECL|macro|BM_10_62
mdefine_line|#define BM_10_62 BM_62_10
DECL|macro|BM_63_10
mdefine_line|#define BM_63_10 0xfffffffffffffc00
DECL|macro|BM_10_63
mdefine_line|#define BM_10_63 BM_63_10
DECL|macro|BM_11_11
mdefine_line|#define BM_11_11 0x0000000000000800
DECL|macro|BM_12_11
mdefine_line|#define BM_12_11 0x0000000000001800
DECL|macro|BM_11_12
mdefine_line|#define BM_11_12 BM_12_11
DECL|macro|BM_13_11
mdefine_line|#define BM_13_11 0x0000000000003800
DECL|macro|BM_11_13
mdefine_line|#define BM_11_13 BM_13_11
DECL|macro|BM_14_11
mdefine_line|#define BM_14_11 0x0000000000007800
DECL|macro|BM_11_14
mdefine_line|#define BM_11_14 BM_14_11
DECL|macro|BM_15_11
mdefine_line|#define BM_15_11 0x000000000000f800
DECL|macro|BM_11_15
mdefine_line|#define BM_11_15 BM_15_11
DECL|macro|BM_16_11
mdefine_line|#define BM_16_11 0x000000000001f800
DECL|macro|BM_11_16
mdefine_line|#define BM_11_16 BM_16_11
DECL|macro|BM_17_11
mdefine_line|#define BM_17_11 0x000000000003f800
DECL|macro|BM_11_17
mdefine_line|#define BM_11_17 BM_17_11
DECL|macro|BM_18_11
mdefine_line|#define BM_18_11 0x000000000007f800
DECL|macro|BM_11_18
mdefine_line|#define BM_11_18 BM_18_11
DECL|macro|BM_19_11
mdefine_line|#define BM_19_11 0x00000000000ff800
DECL|macro|BM_11_19
mdefine_line|#define BM_11_19 BM_19_11
DECL|macro|BM_20_11
mdefine_line|#define BM_20_11 0x00000000001ff800
DECL|macro|BM_11_20
mdefine_line|#define BM_11_20 BM_20_11
DECL|macro|BM_21_11
mdefine_line|#define BM_21_11 0x00000000003ff800
DECL|macro|BM_11_21
mdefine_line|#define BM_11_21 BM_21_11
DECL|macro|BM_22_11
mdefine_line|#define BM_22_11 0x00000000007ff800
DECL|macro|BM_11_22
mdefine_line|#define BM_11_22 BM_22_11
DECL|macro|BM_23_11
mdefine_line|#define BM_23_11 0x0000000000fff800
DECL|macro|BM_11_23
mdefine_line|#define BM_11_23 BM_23_11
DECL|macro|BM_24_11
mdefine_line|#define BM_24_11 0x0000000001fff800
DECL|macro|BM_11_24
mdefine_line|#define BM_11_24 BM_24_11
DECL|macro|BM_25_11
mdefine_line|#define BM_25_11 0x0000000003fff800
DECL|macro|BM_11_25
mdefine_line|#define BM_11_25 BM_25_11
DECL|macro|BM_26_11
mdefine_line|#define BM_26_11 0x0000000007fff800
DECL|macro|BM_11_26
mdefine_line|#define BM_11_26 BM_26_11
DECL|macro|BM_27_11
mdefine_line|#define BM_27_11 0x000000000ffff800
DECL|macro|BM_11_27
mdefine_line|#define BM_11_27 BM_27_11
DECL|macro|BM_28_11
mdefine_line|#define BM_28_11 0x000000001ffff800
DECL|macro|BM_11_28
mdefine_line|#define BM_11_28 BM_28_11
DECL|macro|BM_29_11
mdefine_line|#define BM_29_11 0x000000003ffff800
DECL|macro|BM_11_29
mdefine_line|#define BM_11_29 BM_29_11
DECL|macro|BM_30_11
mdefine_line|#define BM_30_11 0x000000007ffff800
DECL|macro|BM_11_30
mdefine_line|#define BM_11_30 BM_30_11
DECL|macro|BM_31_11
mdefine_line|#define BM_31_11 0x00000000fffff800
DECL|macro|BM_11_31
mdefine_line|#define BM_11_31 BM_31_11
DECL|macro|BM_32_11
mdefine_line|#define BM_32_11 0x00000001fffff800
DECL|macro|BM_11_32
mdefine_line|#define BM_11_32 BM_32_11
DECL|macro|BM_33_11
mdefine_line|#define BM_33_11 0x00000003fffff800
DECL|macro|BM_11_33
mdefine_line|#define BM_11_33 BM_33_11
DECL|macro|BM_34_11
mdefine_line|#define BM_34_11 0x00000007fffff800
DECL|macro|BM_11_34
mdefine_line|#define BM_11_34 BM_34_11
DECL|macro|BM_35_11
mdefine_line|#define BM_35_11 0x0000000ffffff800
DECL|macro|BM_11_35
mdefine_line|#define BM_11_35 BM_35_11
DECL|macro|BM_36_11
mdefine_line|#define BM_36_11 0x0000001ffffff800
DECL|macro|BM_11_36
mdefine_line|#define BM_11_36 BM_36_11
DECL|macro|BM_37_11
mdefine_line|#define BM_37_11 0x0000003ffffff800
DECL|macro|BM_11_37
mdefine_line|#define BM_11_37 BM_37_11
DECL|macro|BM_38_11
mdefine_line|#define BM_38_11 0x0000007ffffff800
DECL|macro|BM_11_38
mdefine_line|#define BM_11_38 BM_38_11
DECL|macro|BM_39_11
mdefine_line|#define BM_39_11 0x000000fffffff800
DECL|macro|BM_11_39
mdefine_line|#define BM_11_39 BM_39_11
DECL|macro|BM_40_11
mdefine_line|#define BM_40_11 0x000001fffffff800
DECL|macro|BM_11_40
mdefine_line|#define BM_11_40 BM_40_11
DECL|macro|BM_41_11
mdefine_line|#define BM_41_11 0x000003fffffff800
DECL|macro|BM_11_41
mdefine_line|#define BM_11_41 BM_41_11
DECL|macro|BM_42_11
mdefine_line|#define BM_42_11 0x000007fffffff800
DECL|macro|BM_11_42
mdefine_line|#define BM_11_42 BM_42_11
DECL|macro|BM_43_11
mdefine_line|#define BM_43_11 0x00000ffffffff800
DECL|macro|BM_11_43
mdefine_line|#define BM_11_43 BM_43_11
DECL|macro|BM_44_11
mdefine_line|#define BM_44_11 0x00001ffffffff800
DECL|macro|BM_11_44
mdefine_line|#define BM_11_44 BM_44_11
DECL|macro|BM_45_11
mdefine_line|#define BM_45_11 0x00003ffffffff800
DECL|macro|BM_11_45
mdefine_line|#define BM_11_45 BM_45_11
DECL|macro|BM_46_11
mdefine_line|#define BM_46_11 0x00007ffffffff800
DECL|macro|BM_11_46
mdefine_line|#define BM_11_46 BM_46_11
DECL|macro|BM_47_11
mdefine_line|#define BM_47_11 0x0000fffffffff800
DECL|macro|BM_11_47
mdefine_line|#define BM_11_47 BM_47_11
DECL|macro|BM_48_11
mdefine_line|#define BM_48_11 0x0001fffffffff800
DECL|macro|BM_11_48
mdefine_line|#define BM_11_48 BM_48_11
DECL|macro|BM_49_11
mdefine_line|#define BM_49_11 0x0003fffffffff800
DECL|macro|BM_11_49
mdefine_line|#define BM_11_49 BM_49_11
DECL|macro|BM_50_11
mdefine_line|#define BM_50_11 0x0007fffffffff800
DECL|macro|BM_11_50
mdefine_line|#define BM_11_50 BM_50_11
DECL|macro|BM_51_11
mdefine_line|#define BM_51_11 0x000ffffffffff800
DECL|macro|BM_11_51
mdefine_line|#define BM_11_51 BM_51_11
DECL|macro|BM_52_11
mdefine_line|#define BM_52_11 0x001ffffffffff800
DECL|macro|BM_11_52
mdefine_line|#define BM_11_52 BM_52_11
DECL|macro|BM_53_11
mdefine_line|#define BM_53_11 0x003ffffffffff800
DECL|macro|BM_11_53
mdefine_line|#define BM_11_53 BM_53_11
DECL|macro|BM_54_11
mdefine_line|#define BM_54_11 0x007ffffffffff800
DECL|macro|BM_11_54
mdefine_line|#define BM_11_54 BM_54_11
DECL|macro|BM_55_11
mdefine_line|#define BM_55_11 0x00fffffffffff800
DECL|macro|BM_11_55
mdefine_line|#define BM_11_55 BM_55_11
DECL|macro|BM_56_11
mdefine_line|#define BM_56_11 0x01fffffffffff800
DECL|macro|BM_11_56
mdefine_line|#define BM_11_56 BM_56_11
DECL|macro|BM_57_11
mdefine_line|#define BM_57_11 0x03fffffffffff800
DECL|macro|BM_11_57
mdefine_line|#define BM_11_57 BM_57_11
DECL|macro|BM_58_11
mdefine_line|#define BM_58_11 0x07fffffffffff800
DECL|macro|BM_11_58
mdefine_line|#define BM_11_58 BM_58_11
DECL|macro|BM_59_11
mdefine_line|#define BM_59_11 0x0ffffffffffff800
DECL|macro|BM_11_59
mdefine_line|#define BM_11_59 BM_59_11
DECL|macro|BM_60_11
mdefine_line|#define BM_60_11 0x1ffffffffffff800
DECL|macro|BM_11_60
mdefine_line|#define BM_11_60 BM_60_11
DECL|macro|BM_61_11
mdefine_line|#define BM_61_11 0x3ffffffffffff800
DECL|macro|BM_11_61
mdefine_line|#define BM_11_61 BM_61_11
DECL|macro|BM_62_11
mdefine_line|#define BM_62_11 0x7ffffffffffff800
DECL|macro|BM_11_62
mdefine_line|#define BM_11_62 BM_62_11
DECL|macro|BM_63_11
mdefine_line|#define BM_63_11 0xfffffffffffff800
DECL|macro|BM_11_63
mdefine_line|#define BM_11_63 BM_63_11
DECL|macro|BM_12_12
mdefine_line|#define BM_12_12 0x0000000000001000
DECL|macro|BM_13_12
mdefine_line|#define BM_13_12 0x0000000000003000
DECL|macro|BM_12_13
mdefine_line|#define BM_12_13 BM_13_12
DECL|macro|BM_14_12
mdefine_line|#define BM_14_12 0x0000000000007000
DECL|macro|BM_12_14
mdefine_line|#define BM_12_14 BM_14_12
DECL|macro|BM_15_12
mdefine_line|#define BM_15_12 0x000000000000f000
DECL|macro|BM_12_15
mdefine_line|#define BM_12_15 BM_15_12
DECL|macro|BM_16_12
mdefine_line|#define BM_16_12 0x000000000001f000
DECL|macro|BM_12_16
mdefine_line|#define BM_12_16 BM_16_12
DECL|macro|BM_17_12
mdefine_line|#define BM_17_12 0x000000000003f000
DECL|macro|BM_12_17
mdefine_line|#define BM_12_17 BM_17_12
DECL|macro|BM_18_12
mdefine_line|#define BM_18_12 0x000000000007f000
DECL|macro|BM_12_18
mdefine_line|#define BM_12_18 BM_18_12
DECL|macro|BM_19_12
mdefine_line|#define BM_19_12 0x00000000000ff000
DECL|macro|BM_12_19
mdefine_line|#define BM_12_19 BM_19_12
DECL|macro|BM_20_12
mdefine_line|#define BM_20_12 0x00000000001ff000
DECL|macro|BM_12_20
mdefine_line|#define BM_12_20 BM_20_12
DECL|macro|BM_21_12
mdefine_line|#define BM_21_12 0x00000000003ff000
DECL|macro|BM_12_21
mdefine_line|#define BM_12_21 BM_21_12
DECL|macro|BM_22_12
mdefine_line|#define BM_22_12 0x00000000007ff000
DECL|macro|BM_12_22
mdefine_line|#define BM_12_22 BM_22_12
DECL|macro|BM_23_12
mdefine_line|#define BM_23_12 0x0000000000fff000
DECL|macro|BM_12_23
mdefine_line|#define BM_12_23 BM_23_12
DECL|macro|BM_24_12
mdefine_line|#define BM_24_12 0x0000000001fff000
DECL|macro|BM_12_24
mdefine_line|#define BM_12_24 BM_24_12
DECL|macro|BM_25_12
mdefine_line|#define BM_25_12 0x0000000003fff000
DECL|macro|BM_12_25
mdefine_line|#define BM_12_25 BM_25_12
DECL|macro|BM_26_12
mdefine_line|#define BM_26_12 0x0000000007fff000
DECL|macro|BM_12_26
mdefine_line|#define BM_12_26 BM_26_12
DECL|macro|BM_27_12
mdefine_line|#define BM_27_12 0x000000000ffff000
DECL|macro|BM_12_27
mdefine_line|#define BM_12_27 BM_27_12
DECL|macro|BM_28_12
mdefine_line|#define BM_28_12 0x000000001ffff000
DECL|macro|BM_12_28
mdefine_line|#define BM_12_28 BM_28_12
DECL|macro|BM_29_12
mdefine_line|#define BM_29_12 0x000000003ffff000
DECL|macro|BM_12_29
mdefine_line|#define BM_12_29 BM_29_12
DECL|macro|BM_30_12
mdefine_line|#define BM_30_12 0x000000007ffff000
DECL|macro|BM_12_30
mdefine_line|#define BM_12_30 BM_30_12
DECL|macro|BM_31_12
mdefine_line|#define BM_31_12 0x00000000fffff000
DECL|macro|BM_12_31
mdefine_line|#define BM_12_31 BM_31_12
DECL|macro|BM_32_12
mdefine_line|#define BM_32_12 0x00000001fffff000
DECL|macro|BM_12_32
mdefine_line|#define BM_12_32 BM_32_12
DECL|macro|BM_33_12
mdefine_line|#define BM_33_12 0x00000003fffff000
DECL|macro|BM_12_33
mdefine_line|#define BM_12_33 BM_33_12
DECL|macro|BM_34_12
mdefine_line|#define BM_34_12 0x00000007fffff000
DECL|macro|BM_12_34
mdefine_line|#define BM_12_34 BM_34_12
DECL|macro|BM_35_12
mdefine_line|#define BM_35_12 0x0000000ffffff000
DECL|macro|BM_12_35
mdefine_line|#define BM_12_35 BM_35_12
DECL|macro|BM_36_12
mdefine_line|#define BM_36_12 0x0000001ffffff000
DECL|macro|BM_12_36
mdefine_line|#define BM_12_36 BM_36_12
DECL|macro|BM_37_12
mdefine_line|#define BM_37_12 0x0000003ffffff000
DECL|macro|BM_12_37
mdefine_line|#define BM_12_37 BM_37_12
DECL|macro|BM_38_12
mdefine_line|#define BM_38_12 0x0000007ffffff000
DECL|macro|BM_12_38
mdefine_line|#define BM_12_38 BM_38_12
DECL|macro|BM_39_12
mdefine_line|#define BM_39_12 0x000000fffffff000
DECL|macro|BM_12_39
mdefine_line|#define BM_12_39 BM_39_12
DECL|macro|BM_40_12
mdefine_line|#define BM_40_12 0x000001fffffff000
DECL|macro|BM_12_40
mdefine_line|#define BM_12_40 BM_40_12
DECL|macro|BM_41_12
mdefine_line|#define BM_41_12 0x000003fffffff000
DECL|macro|BM_12_41
mdefine_line|#define BM_12_41 BM_41_12
DECL|macro|BM_42_12
mdefine_line|#define BM_42_12 0x000007fffffff000
DECL|macro|BM_12_42
mdefine_line|#define BM_12_42 BM_42_12
DECL|macro|BM_43_12
mdefine_line|#define BM_43_12 0x00000ffffffff000
DECL|macro|BM_12_43
mdefine_line|#define BM_12_43 BM_43_12
DECL|macro|BM_44_12
mdefine_line|#define BM_44_12 0x00001ffffffff000
DECL|macro|BM_12_44
mdefine_line|#define BM_12_44 BM_44_12
DECL|macro|BM_45_12
mdefine_line|#define BM_45_12 0x00003ffffffff000
DECL|macro|BM_12_45
mdefine_line|#define BM_12_45 BM_45_12
DECL|macro|BM_46_12
mdefine_line|#define BM_46_12 0x00007ffffffff000
DECL|macro|BM_12_46
mdefine_line|#define BM_12_46 BM_46_12
DECL|macro|BM_47_12
mdefine_line|#define BM_47_12 0x0000fffffffff000
DECL|macro|BM_12_47
mdefine_line|#define BM_12_47 BM_47_12
DECL|macro|BM_48_12
mdefine_line|#define BM_48_12 0x0001fffffffff000
DECL|macro|BM_12_48
mdefine_line|#define BM_12_48 BM_48_12
DECL|macro|BM_49_12
mdefine_line|#define BM_49_12 0x0003fffffffff000
DECL|macro|BM_12_49
mdefine_line|#define BM_12_49 BM_49_12
DECL|macro|BM_50_12
mdefine_line|#define BM_50_12 0x0007fffffffff000
DECL|macro|BM_12_50
mdefine_line|#define BM_12_50 BM_50_12
DECL|macro|BM_51_12
mdefine_line|#define BM_51_12 0x000ffffffffff000
DECL|macro|BM_12_51
mdefine_line|#define BM_12_51 BM_51_12
DECL|macro|BM_52_12
mdefine_line|#define BM_52_12 0x001ffffffffff000
DECL|macro|BM_12_52
mdefine_line|#define BM_12_52 BM_52_12
DECL|macro|BM_53_12
mdefine_line|#define BM_53_12 0x003ffffffffff000
DECL|macro|BM_12_53
mdefine_line|#define BM_12_53 BM_53_12
DECL|macro|BM_54_12
mdefine_line|#define BM_54_12 0x007ffffffffff000
DECL|macro|BM_12_54
mdefine_line|#define BM_12_54 BM_54_12
DECL|macro|BM_55_12
mdefine_line|#define BM_55_12 0x00fffffffffff000
DECL|macro|BM_12_55
mdefine_line|#define BM_12_55 BM_55_12
DECL|macro|BM_56_12
mdefine_line|#define BM_56_12 0x01fffffffffff000
DECL|macro|BM_12_56
mdefine_line|#define BM_12_56 BM_56_12
DECL|macro|BM_57_12
mdefine_line|#define BM_57_12 0x03fffffffffff000
DECL|macro|BM_12_57
mdefine_line|#define BM_12_57 BM_57_12
DECL|macro|BM_58_12
mdefine_line|#define BM_58_12 0x07fffffffffff000
DECL|macro|BM_12_58
mdefine_line|#define BM_12_58 BM_58_12
DECL|macro|BM_59_12
mdefine_line|#define BM_59_12 0x0ffffffffffff000
DECL|macro|BM_12_59
mdefine_line|#define BM_12_59 BM_59_12
DECL|macro|BM_60_12
mdefine_line|#define BM_60_12 0x1ffffffffffff000
DECL|macro|BM_12_60
mdefine_line|#define BM_12_60 BM_60_12
DECL|macro|BM_61_12
mdefine_line|#define BM_61_12 0x3ffffffffffff000
DECL|macro|BM_12_61
mdefine_line|#define BM_12_61 BM_61_12
DECL|macro|BM_62_12
mdefine_line|#define BM_62_12 0x7ffffffffffff000
DECL|macro|BM_12_62
mdefine_line|#define BM_12_62 BM_62_12
DECL|macro|BM_63_12
mdefine_line|#define BM_63_12 0xfffffffffffff000
DECL|macro|BM_12_63
mdefine_line|#define BM_12_63 BM_63_12
DECL|macro|BM_13_13
mdefine_line|#define BM_13_13 0x0000000000002000
DECL|macro|BM_14_13
mdefine_line|#define BM_14_13 0x0000000000006000
DECL|macro|BM_13_14
mdefine_line|#define BM_13_14 BM_14_13
DECL|macro|BM_15_13
mdefine_line|#define BM_15_13 0x000000000000e000
DECL|macro|BM_13_15
mdefine_line|#define BM_13_15 BM_15_13
DECL|macro|BM_16_13
mdefine_line|#define BM_16_13 0x000000000001e000
DECL|macro|BM_13_16
mdefine_line|#define BM_13_16 BM_16_13
DECL|macro|BM_17_13
mdefine_line|#define BM_17_13 0x000000000003e000
DECL|macro|BM_13_17
mdefine_line|#define BM_13_17 BM_17_13
DECL|macro|BM_18_13
mdefine_line|#define BM_18_13 0x000000000007e000
DECL|macro|BM_13_18
mdefine_line|#define BM_13_18 BM_18_13
DECL|macro|BM_19_13
mdefine_line|#define BM_19_13 0x00000000000fe000
DECL|macro|BM_13_19
mdefine_line|#define BM_13_19 BM_19_13
DECL|macro|BM_20_13
mdefine_line|#define BM_20_13 0x00000000001fe000
DECL|macro|BM_13_20
mdefine_line|#define BM_13_20 BM_20_13
DECL|macro|BM_21_13
mdefine_line|#define BM_21_13 0x00000000003fe000
DECL|macro|BM_13_21
mdefine_line|#define BM_13_21 BM_21_13
DECL|macro|BM_22_13
mdefine_line|#define BM_22_13 0x00000000007fe000
DECL|macro|BM_13_22
mdefine_line|#define BM_13_22 BM_22_13
DECL|macro|BM_23_13
mdefine_line|#define BM_23_13 0x0000000000ffe000
DECL|macro|BM_13_23
mdefine_line|#define BM_13_23 BM_23_13
DECL|macro|BM_24_13
mdefine_line|#define BM_24_13 0x0000000001ffe000
DECL|macro|BM_13_24
mdefine_line|#define BM_13_24 BM_24_13
DECL|macro|BM_25_13
mdefine_line|#define BM_25_13 0x0000000003ffe000
DECL|macro|BM_13_25
mdefine_line|#define BM_13_25 BM_25_13
DECL|macro|BM_26_13
mdefine_line|#define BM_26_13 0x0000000007ffe000
DECL|macro|BM_13_26
mdefine_line|#define BM_13_26 BM_26_13
DECL|macro|BM_27_13
mdefine_line|#define BM_27_13 0x000000000fffe000
DECL|macro|BM_13_27
mdefine_line|#define BM_13_27 BM_27_13
DECL|macro|BM_28_13
mdefine_line|#define BM_28_13 0x000000001fffe000
DECL|macro|BM_13_28
mdefine_line|#define BM_13_28 BM_28_13
DECL|macro|BM_29_13
mdefine_line|#define BM_29_13 0x000000003fffe000
DECL|macro|BM_13_29
mdefine_line|#define BM_13_29 BM_29_13
DECL|macro|BM_30_13
mdefine_line|#define BM_30_13 0x000000007fffe000
DECL|macro|BM_13_30
mdefine_line|#define BM_13_30 BM_30_13
DECL|macro|BM_31_13
mdefine_line|#define BM_31_13 0x00000000ffffe000
DECL|macro|BM_13_31
mdefine_line|#define BM_13_31 BM_31_13
DECL|macro|BM_32_13
mdefine_line|#define BM_32_13 0x00000001ffffe000
DECL|macro|BM_13_32
mdefine_line|#define BM_13_32 BM_32_13
DECL|macro|BM_33_13
mdefine_line|#define BM_33_13 0x00000003ffffe000
DECL|macro|BM_13_33
mdefine_line|#define BM_13_33 BM_33_13
DECL|macro|BM_34_13
mdefine_line|#define BM_34_13 0x00000007ffffe000
DECL|macro|BM_13_34
mdefine_line|#define BM_13_34 BM_34_13
DECL|macro|BM_35_13
mdefine_line|#define BM_35_13 0x0000000fffffe000
DECL|macro|BM_13_35
mdefine_line|#define BM_13_35 BM_35_13
DECL|macro|BM_36_13
mdefine_line|#define BM_36_13 0x0000001fffffe000
DECL|macro|BM_13_36
mdefine_line|#define BM_13_36 BM_36_13
DECL|macro|BM_37_13
mdefine_line|#define BM_37_13 0x0000003fffffe000
DECL|macro|BM_13_37
mdefine_line|#define BM_13_37 BM_37_13
DECL|macro|BM_38_13
mdefine_line|#define BM_38_13 0x0000007fffffe000
DECL|macro|BM_13_38
mdefine_line|#define BM_13_38 BM_38_13
DECL|macro|BM_39_13
mdefine_line|#define BM_39_13 0x000000ffffffe000
DECL|macro|BM_13_39
mdefine_line|#define BM_13_39 BM_39_13
DECL|macro|BM_40_13
mdefine_line|#define BM_40_13 0x000001ffffffe000
DECL|macro|BM_13_40
mdefine_line|#define BM_13_40 BM_40_13
DECL|macro|BM_41_13
mdefine_line|#define BM_41_13 0x000003ffffffe000
DECL|macro|BM_13_41
mdefine_line|#define BM_13_41 BM_41_13
DECL|macro|BM_42_13
mdefine_line|#define BM_42_13 0x000007ffffffe000
DECL|macro|BM_13_42
mdefine_line|#define BM_13_42 BM_42_13
DECL|macro|BM_43_13
mdefine_line|#define BM_43_13 0x00000fffffffe000
DECL|macro|BM_13_43
mdefine_line|#define BM_13_43 BM_43_13
DECL|macro|BM_44_13
mdefine_line|#define BM_44_13 0x00001fffffffe000
DECL|macro|BM_13_44
mdefine_line|#define BM_13_44 BM_44_13
DECL|macro|BM_45_13
mdefine_line|#define BM_45_13 0x00003fffffffe000
DECL|macro|BM_13_45
mdefine_line|#define BM_13_45 BM_45_13
DECL|macro|BM_46_13
mdefine_line|#define BM_46_13 0x00007fffffffe000
DECL|macro|BM_13_46
mdefine_line|#define BM_13_46 BM_46_13
DECL|macro|BM_47_13
mdefine_line|#define BM_47_13 0x0000ffffffffe000
DECL|macro|BM_13_47
mdefine_line|#define BM_13_47 BM_47_13
DECL|macro|BM_48_13
mdefine_line|#define BM_48_13 0x0001ffffffffe000
DECL|macro|BM_13_48
mdefine_line|#define BM_13_48 BM_48_13
DECL|macro|BM_49_13
mdefine_line|#define BM_49_13 0x0003ffffffffe000
DECL|macro|BM_13_49
mdefine_line|#define BM_13_49 BM_49_13
DECL|macro|BM_50_13
mdefine_line|#define BM_50_13 0x0007ffffffffe000
DECL|macro|BM_13_50
mdefine_line|#define BM_13_50 BM_50_13
DECL|macro|BM_51_13
mdefine_line|#define BM_51_13 0x000fffffffffe000
DECL|macro|BM_13_51
mdefine_line|#define BM_13_51 BM_51_13
DECL|macro|BM_52_13
mdefine_line|#define BM_52_13 0x001fffffffffe000
DECL|macro|BM_13_52
mdefine_line|#define BM_13_52 BM_52_13
DECL|macro|BM_53_13
mdefine_line|#define BM_53_13 0x003fffffffffe000
DECL|macro|BM_13_53
mdefine_line|#define BM_13_53 BM_53_13
DECL|macro|BM_54_13
mdefine_line|#define BM_54_13 0x007fffffffffe000
DECL|macro|BM_13_54
mdefine_line|#define BM_13_54 BM_54_13
DECL|macro|BM_55_13
mdefine_line|#define BM_55_13 0x00ffffffffffe000
DECL|macro|BM_13_55
mdefine_line|#define BM_13_55 BM_55_13
DECL|macro|BM_56_13
mdefine_line|#define BM_56_13 0x01ffffffffffe000
DECL|macro|BM_13_56
mdefine_line|#define BM_13_56 BM_56_13
DECL|macro|BM_57_13
mdefine_line|#define BM_57_13 0x03ffffffffffe000
DECL|macro|BM_13_57
mdefine_line|#define BM_13_57 BM_57_13
DECL|macro|BM_58_13
mdefine_line|#define BM_58_13 0x07ffffffffffe000
DECL|macro|BM_13_58
mdefine_line|#define BM_13_58 BM_58_13
DECL|macro|BM_59_13
mdefine_line|#define BM_59_13 0x0fffffffffffe000
DECL|macro|BM_13_59
mdefine_line|#define BM_13_59 BM_59_13
DECL|macro|BM_60_13
mdefine_line|#define BM_60_13 0x1fffffffffffe000
DECL|macro|BM_13_60
mdefine_line|#define BM_13_60 BM_60_13
DECL|macro|BM_61_13
mdefine_line|#define BM_61_13 0x3fffffffffffe000
DECL|macro|BM_13_61
mdefine_line|#define BM_13_61 BM_61_13
DECL|macro|BM_62_13
mdefine_line|#define BM_62_13 0x7fffffffffffe000
DECL|macro|BM_13_62
mdefine_line|#define BM_13_62 BM_62_13
DECL|macro|BM_63_13
mdefine_line|#define BM_63_13 0xffffffffffffe000
DECL|macro|BM_13_63
mdefine_line|#define BM_13_63 BM_63_13
DECL|macro|BM_14_14
mdefine_line|#define BM_14_14 0x0000000000004000
DECL|macro|BM_15_14
mdefine_line|#define BM_15_14 0x000000000000c000
DECL|macro|BM_14_15
mdefine_line|#define BM_14_15 BM_15_14
DECL|macro|BM_16_14
mdefine_line|#define BM_16_14 0x000000000001c000
DECL|macro|BM_14_16
mdefine_line|#define BM_14_16 BM_16_14
DECL|macro|BM_17_14
mdefine_line|#define BM_17_14 0x000000000003c000
DECL|macro|BM_14_17
mdefine_line|#define BM_14_17 BM_17_14
DECL|macro|BM_18_14
mdefine_line|#define BM_18_14 0x000000000007c000
DECL|macro|BM_14_18
mdefine_line|#define BM_14_18 BM_18_14
DECL|macro|BM_19_14
mdefine_line|#define BM_19_14 0x00000000000fc000
DECL|macro|BM_14_19
mdefine_line|#define BM_14_19 BM_19_14
DECL|macro|BM_20_14
mdefine_line|#define BM_20_14 0x00000000001fc000
DECL|macro|BM_14_20
mdefine_line|#define BM_14_20 BM_20_14
DECL|macro|BM_21_14
mdefine_line|#define BM_21_14 0x00000000003fc000
DECL|macro|BM_14_21
mdefine_line|#define BM_14_21 BM_21_14
DECL|macro|BM_22_14
mdefine_line|#define BM_22_14 0x00000000007fc000
DECL|macro|BM_14_22
mdefine_line|#define BM_14_22 BM_22_14
DECL|macro|BM_23_14
mdefine_line|#define BM_23_14 0x0000000000ffc000
DECL|macro|BM_14_23
mdefine_line|#define BM_14_23 BM_23_14
DECL|macro|BM_24_14
mdefine_line|#define BM_24_14 0x0000000001ffc000
DECL|macro|BM_14_24
mdefine_line|#define BM_14_24 BM_24_14
DECL|macro|BM_25_14
mdefine_line|#define BM_25_14 0x0000000003ffc000
DECL|macro|BM_14_25
mdefine_line|#define BM_14_25 BM_25_14
DECL|macro|BM_26_14
mdefine_line|#define BM_26_14 0x0000000007ffc000
DECL|macro|BM_14_26
mdefine_line|#define BM_14_26 BM_26_14
DECL|macro|BM_27_14
mdefine_line|#define BM_27_14 0x000000000fffc000
DECL|macro|BM_14_27
mdefine_line|#define BM_14_27 BM_27_14
DECL|macro|BM_28_14
mdefine_line|#define BM_28_14 0x000000001fffc000
DECL|macro|BM_14_28
mdefine_line|#define BM_14_28 BM_28_14
DECL|macro|BM_29_14
mdefine_line|#define BM_29_14 0x000000003fffc000
DECL|macro|BM_14_29
mdefine_line|#define BM_14_29 BM_29_14
DECL|macro|BM_30_14
mdefine_line|#define BM_30_14 0x000000007fffc000
DECL|macro|BM_14_30
mdefine_line|#define BM_14_30 BM_30_14
DECL|macro|BM_31_14
mdefine_line|#define BM_31_14 0x00000000ffffc000
DECL|macro|BM_14_31
mdefine_line|#define BM_14_31 BM_31_14
DECL|macro|BM_32_14
mdefine_line|#define BM_32_14 0x00000001ffffc000
DECL|macro|BM_14_32
mdefine_line|#define BM_14_32 BM_32_14
DECL|macro|BM_33_14
mdefine_line|#define BM_33_14 0x00000003ffffc000
DECL|macro|BM_14_33
mdefine_line|#define BM_14_33 BM_33_14
DECL|macro|BM_34_14
mdefine_line|#define BM_34_14 0x00000007ffffc000
DECL|macro|BM_14_34
mdefine_line|#define BM_14_34 BM_34_14
DECL|macro|BM_35_14
mdefine_line|#define BM_35_14 0x0000000fffffc000
DECL|macro|BM_14_35
mdefine_line|#define BM_14_35 BM_35_14
DECL|macro|BM_36_14
mdefine_line|#define BM_36_14 0x0000001fffffc000
DECL|macro|BM_14_36
mdefine_line|#define BM_14_36 BM_36_14
DECL|macro|BM_37_14
mdefine_line|#define BM_37_14 0x0000003fffffc000
DECL|macro|BM_14_37
mdefine_line|#define BM_14_37 BM_37_14
DECL|macro|BM_38_14
mdefine_line|#define BM_38_14 0x0000007fffffc000
DECL|macro|BM_14_38
mdefine_line|#define BM_14_38 BM_38_14
DECL|macro|BM_39_14
mdefine_line|#define BM_39_14 0x000000ffffffc000
DECL|macro|BM_14_39
mdefine_line|#define BM_14_39 BM_39_14
DECL|macro|BM_40_14
mdefine_line|#define BM_40_14 0x000001ffffffc000
DECL|macro|BM_14_40
mdefine_line|#define BM_14_40 BM_40_14
DECL|macro|BM_41_14
mdefine_line|#define BM_41_14 0x000003ffffffc000
DECL|macro|BM_14_41
mdefine_line|#define BM_14_41 BM_41_14
DECL|macro|BM_42_14
mdefine_line|#define BM_42_14 0x000007ffffffc000
DECL|macro|BM_14_42
mdefine_line|#define BM_14_42 BM_42_14
DECL|macro|BM_43_14
mdefine_line|#define BM_43_14 0x00000fffffffc000
DECL|macro|BM_14_43
mdefine_line|#define BM_14_43 BM_43_14
DECL|macro|BM_44_14
mdefine_line|#define BM_44_14 0x00001fffffffc000
DECL|macro|BM_14_44
mdefine_line|#define BM_14_44 BM_44_14
DECL|macro|BM_45_14
mdefine_line|#define BM_45_14 0x00003fffffffc000
DECL|macro|BM_14_45
mdefine_line|#define BM_14_45 BM_45_14
DECL|macro|BM_46_14
mdefine_line|#define BM_46_14 0x00007fffffffc000
DECL|macro|BM_14_46
mdefine_line|#define BM_14_46 BM_46_14
DECL|macro|BM_47_14
mdefine_line|#define BM_47_14 0x0000ffffffffc000
DECL|macro|BM_14_47
mdefine_line|#define BM_14_47 BM_47_14
DECL|macro|BM_48_14
mdefine_line|#define BM_48_14 0x0001ffffffffc000
DECL|macro|BM_14_48
mdefine_line|#define BM_14_48 BM_48_14
DECL|macro|BM_49_14
mdefine_line|#define BM_49_14 0x0003ffffffffc000
DECL|macro|BM_14_49
mdefine_line|#define BM_14_49 BM_49_14
DECL|macro|BM_50_14
mdefine_line|#define BM_50_14 0x0007ffffffffc000
DECL|macro|BM_14_50
mdefine_line|#define BM_14_50 BM_50_14
DECL|macro|BM_51_14
mdefine_line|#define BM_51_14 0x000fffffffffc000
DECL|macro|BM_14_51
mdefine_line|#define BM_14_51 BM_51_14
DECL|macro|BM_52_14
mdefine_line|#define BM_52_14 0x001fffffffffc000
DECL|macro|BM_14_52
mdefine_line|#define BM_14_52 BM_52_14
DECL|macro|BM_53_14
mdefine_line|#define BM_53_14 0x003fffffffffc000
DECL|macro|BM_14_53
mdefine_line|#define BM_14_53 BM_53_14
DECL|macro|BM_54_14
mdefine_line|#define BM_54_14 0x007fffffffffc000
DECL|macro|BM_14_54
mdefine_line|#define BM_14_54 BM_54_14
DECL|macro|BM_55_14
mdefine_line|#define BM_55_14 0x00ffffffffffc000
DECL|macro|BM_14_55
mdefine_line|#define BM_14_55 BM_55_14
DECL|macro|BM_56_14
mdefine_line|#define BM_56_14 0x01ffffffffffc000
DECL|macro|BM_14_56
mdefine_line|#define BM_14_56 BM_56_14
DECL|macro|BM_57_14
mdefine_line|#define BM_57_14 0x03ffffffffffc000
DECL|macro|BM_14_57
mdefine_line|#define BM_14_57 BM_57_14
DECL|macro|BM_58_14
mdefine_line|#define BM_58_14 0x07ffffffffffc000
DECL|macro|BM_14_58
mdefine_line|#define BM_14_58 BM_58_14
DECL|macro|BM_59_14
mdefine_line|#define BM_59_14 0x0fffffffffffc000
DECL|macro|BM_14_59
mdefine_line|#define BM_14_59 BM_59_14
DECL|macro|BM_60_14
mdefine_line|#define BM_60_14 0x1fffffffffffc000
DECL|macro|BM_14_60
mdefine_line|#define BM_14_60 BM_60_14
DECL|macro|BM_61_14
mdefine_line|#define BM_61_14 0x3fffffffffffc000
DECL|macro|BM_14_61
mdefine_line|#define BM_14_61 BM_61_14
DECL|macro|BM_62_14
mdefine_line|#define BM_62_14 0x7fffffffffffc000
DECL|macro|BM_14_62
mdefine_line|#define BM_14_62 BM_62_14
DECL|macro|BM_63_14
mdefine_line|#define BM_63_14 0xffffffffffffc000
DECL|macro|BM_14_63
mdefine_line|#define BM_14_63 BM_63_14
DECL|macro|BM_15_15
mdefine_line|#define BM_15_15 0x0000000000008000
DECL|macro|BM_16_15
mdefine_line|#define BM_16_15 0x0000000000018000
DECL|macro|BM_15_16
mdefine_line|#define BM_15_16 BM_16_15
DECL|macro|BM_17_15
mdefine_line|#define BM_17_15 0x0000000000038000
DECL|macro|BM_15_17
mdefine_line|#define BM_15_17 BM_17_15
DECL|macro|BM_18_15
mdefine_line|#define BM_18_15 0x0000000000078000
DECL|macro|BM_15_18
mdefine_line|#define BM_15_18 BM_18_15
DECL|macro|BM_19_15
mdefine_line|#define BM_19_15 0x00000000000f8000
DECL|macro|BM_15_19
mdefine_line|#define BM_15_19 BM_19_15
DECL|macro|BM_20_15
mdefine_line|#define BM_20_15 0x00000000001f8000
DECL|macro|BM_15_20
mdefine_line|#define BM_15_20 BM_20_15
DECL|macro|BM_21_15
mdefine_line|#define BM_21_15 0x00000000003f8000
DECL|macro|BM_15_21
mdefine_line|#define BM_15_21 BM_21_15
DECL|macro|BM_22_15
mdefine_line|#define BM_22_15 0x00000000007f8000
DECL|macro|BM_15_22
mdefine_line|#define BM_15_22 BM_22_15
DECL|macro|BM_23_15
mdefine_line|#define BM_23_15 0x0000000000ff8000
DECL|macro|BM_15_23
mdefine_line|#define BM_15_23 BM_23_15
DECL|macro|BM_24_15
mdefine_line|#define BM_24_15 0x0000000001ff8000
DECL|macro|BM_15_24
mdefine_line|#define BM_15_24 BM_24_15
DECL|macro|BM_25_15
mdefine_line|#define BM_25_15 0x0000000003ff8000
DECL|macro|BM_15_25
mdefine_line|#define BM_15_25 BM_25_15
DECL|macro|BM_26_15
mdefine_line|#define BM_26_15 0x0000000007ff8000
DECL|macro|BM_15_26
mdefine_line|#define BM_15_26 BM_26_15
DECL|macro|BM_27_15
mdefine_line|#define BM_27_15 0x000000000fff8000
DECL|macro|BM_15_27
mdefine_line|#define BM_15_27 BM_27_15
DECL|macro|BM_28_15
mdefine_line|#define BM_28_15 0x000000001fff8000
DECL|macro|BM_15_28
mdefine_line|#define BM_15_28 BM_28_15
DECL|macro|BM_29_15
mdefine_line|#define BM_29_15 0x000000003fff8000
DECL|macro|BM_15_29
mdefine_line|#define BM_15_29 BM_29_15
DECL|macro|BM_30_15
mdefine_line|#define BM_30_15 0x000000007fff8000
DECL|macro|BM_15_30
mdefine_line|#define BM_15_30 BM_30_15
DECL|macro|BM_31_15
mdefine_line|#define BM_31_15 0x00000000ffff8000
DECL|macro|BM_15_31
mdefine_line|#define BM_15_31 BM_31_15
DECL|macro|BM_32_15
mdefine_line|#define BM_32_15 0x00000001ffff8000
DECL|macro|BM_15_32
mdefine_line|#define BM_15_32 BM_32_15
DECL|macro|BM_33_15
mdefine_line|#define BM_33_15 0x00000003ffff8000
DECL|macro|BM_15_33
mdefine_line|#define BM_15_33 BM_33_15
DECL|macro|BM_34_15
mdefine_line|#define BM_34_15 0x00000007ffff8000
DECL|macro|BM_15_34
mdefine_line|#define BM_15_34 BM_34_15
DECL|macro|BM_35_15
mdefine_line|#define BM_35_15 0x0000000fffff8000
DECL|macro|BM_15_35
mdefine_line|#define BM_15_35 BM_35_15
DECL|macro|BM_36_15
mdefine_line|#define BM_36_15 0x0000001fffff8000
DECL|macro|BM_15_36
mdefine_line|#define BM_15_36 BM_36_15
DECL|macro|BM_37_15
mdefine_line|#define BM_37_15 0x0000003fffff8000
DECL|macro|BM_15_37
mdefine_line|#define BM_15_37 BM_37_15
DECL|macro|BM_38_15
mdefine_line|#define BM_38_15 0x0000007fffff8000
DECL|macro|BM_15_38
mdefine_line|#define BM_15_38 BM_38_15
DECL|macro|BM_39_15
mdefine_line|#define BM_39_15 0x000000ffffff8000
DECL|macro|BM_15_39
mdefine_line|#define BM_15_39 BM_39_15
DECL|macro|BM_40_15
mdefine_line|#define BM_40_15 0x000001ffffff8000
DECL|macro|BM_15_40
mdefine_line|#define BM_15_40 BM_40_15
DECL|macro|BM_41_15
mdefine_line|#define BM_41_15 0x000003ffffff8000
DECL|macro|BM_15_41
mdefine_line|#define BM_15_41 BM_41_15
DECL|macro|BM_42_15
mdefine_line|#define BM_42_15 0x000007ffffff8000
DECL|macro|BM_15_42
mdefine_line|#define BM_15_42 BM_42_15
DECL|macro|BM_43_15
mdefine_line|#define BM_43_15 0x00000fffffff8000
DECL|macro|BM_15_43
mdefine_line|#define BM_15_43 BM_43_15
DECL|macro|BM_44_15
mdefine_line|#define BM_44_15 0x00001fffffff8000
DECL|macro|BM_15_44
mdefine_line|#define BM_15_44 BM_44_15
DECL|macro|BM_45_15
mdefine_line|#define BM_45_15 0x00003fffffff8000
DECL|macro|BM_15_45
mdefine_line|#define BM_15_45 BM_45_15
DECL|macro|BM_46_15
mdefine_line|#define BM_46_15 0x00007fffffff8000
DECL|macro|BM_15_46
mdefine_line|#define BM_15_46 BM_46_15
DECL|macro|BM_47_15
mdefine_line|#define BM_47_15 0x0000ffffffff8000
DECL|macro|BM_15_47
mdefine_line|#define BM_15_47 BM_47_15
DECL|macro|BM_48_15
mdefine_line|#define BM_48_15 0x0001ffffffff8000
DECL|macro|BM_15_48
mdefine_line|#define BM_15_48 BM_48_15
DECL|macro|BM_49_15
mdefine_line|#define BM_49_15 0x0003ffffffff8000
DECL|macro|BM_15_49
mdefine_line|#define BM_15_49 BM_49_15
DECL|macro|BM_50_15
mdefine_line|#define BM_50_15 0x0007ffffffff8000
DECL|macro|BM_15_50
mdefine_line|#define BM_15_50 BM_50_15
DECL|macro|BM_51_15
mdefine_line|#define BM_51_15 0x000fffffffff8000
DECL|macro|BM_15_51
mdefine_line|#define BM_15_51 BM_51_15
DECL|macro|BM_52_15
mdefine_line|#define BM_52_15 0x001fffffffff8000
DECL|macro|BM_15_52
mdefine_line|#define BM_15_52 BM_52_15
DECL|macro|BM_53_15
mdefine_line|#define BM_53_15 0x003fffffffff8000
DECL|macro|BM_15_53
mdefine_line|#define BM_15_53 BM_53_15
DECL|macro|BM_54_15
mdefine_line|#define BM_54_15 0x007fffffffff8000
DECL|macro|BM_15_54
mdefine_line|#define BM_15_54 BM_54_15
DECL|macro|BM_55_15
mdefine_line|#define BM_55_15 0x00ffffffffff8000
DECL|macro|BM_15_55
mdefine_line|#define BM_15_55 BM_55_15
DECL|macro|BM_56_15
mdefine_line|#define BM_56_15 0x01ffffffffff8000
DECL|macro|BM_15_56
mdefine_line|#define BM_15_56 BM_56_15
DECL|macro|BM_57_15
mdefine_line|#define BM_57_15 0x03ffffffffff8000
DECL|macro|BM_15_57
mdefine_line|#define BM_15_57 BM_57_15
DECL|macro|BM_58_15
mdefine_line|#define BM_58_15 0x07ffffffffff8000
DECL|macro|BM_15_58
mdefine_line|#define BM_15_58 BM_58_15
DECL|macro|BM_59_15
mdefine_line|#define BM_59_15 0x0fffffffffff8000
DECL|macro|BM_15_59
mdefine_line|#define BM_15_59 BM_59_15
DECL|macro|BM_60_15
mdefine_line|#define BM_60_15 0x1fffffffffff8000
DECL|macro|BM_15_60
mdefine_line|#define BM_15_60 BM_60_15
DECL|macro|BM_61_15
mdefine_line|#define BM_61_15 0x3fffffffffff8000
DECL|macro|BM_15_61
mdefine_line|#define BM_15_61 BM_61_15
DECL|macro|BM_62_15
mdefine_line|#define BM_62_15 0x7fffffffffff8000
DECL|macro|BM_15_62
mdefine_line|#define BM_15_62 BM_62_15
DECL|macro|BM_63_15
mdefine_line|#define BM_63_15 0xffffffffffff8000
DECL|macro|BM_15_63
mdefine_line|#define BM_15_63 BM_63_15
DECL|macro|BM_16_16
mdefine_line|#define BM_16_16 0x0000000000010000
DECL|macro|BM_17_16
mdefine_line|#define BM_17_16 0x0000000000030000
DECL|macro|BM_16_17
mdefine_line|#define BM_16_17 BM_17_16
DECL|macro|BM_18_16
mdefine_line|#define BM_18_16 0x0000000000070000
DECL|macro|BM_16_18
mdefine_line|#define BM_16_18 BM_18_16
DECL|macro|BM_19_16
mdefine_line|#define BM_19_16 0x00000000000f0000
DECL|macro|BM_16_19
mdefine_line|#define BM_16_19 BM_19_16
DECL|macro|BM_20_16
mdefine_line|#define BM_20_16 0x00000000001f0000
DECL|macro|BM_16_20
mdefine_line|#define BM_16_20 BM_20_16
DECL|macro|BM_21_16
mdefine_line|#define BM_21_16 0x00000000003f0000
DECL|macro|BM_16_21
mdefine_line|#define BM_16_21 BM_21_16
DECL|macro|BM_22_16
mdefine_line|#define BM_22_16 0x00000000007f0000
DECL|macro|BM_16_22
mdefine_line|#define BM_16_22 BM_22_16
DECL|macro|BM_23_16
mdefine_line|#define BM_23_16 0x0000000000ff0000
DECL|macro|BM_16_23
mdefine_line|#define BM_16_23 BM_23_16
DECL|macro|BM_24_16
mdefine_line|#define BM_24_16 0x0000000001ff0000
DECL|macro|BM_16_24
mdefine_line|#define BM_16_24 BM_24_16
DECL|macro|BM_25_16
mdefine_line|#define BM_25_16 0x0000000003ff0000
DECL|macro|BM_16_25
mdefine_line|#define BM_16_25 BM_25_16
DECL|macro|BM_26_16
mdefine_line|#define BM_26_16 0x0000000007ff0000
DECL|macro|BM_16_26
mdefine_line|#define BM_16_26 BM_26_16
DECL|macro|BM_27_16
mdefine_line|#define BM_27_16 0x000000000fff0000
DECL|macro|BM_16_27
mdefine_line|#define BM_16_27 BM_27_16
DECL|macro|BM_28_16
mdefine_line|#define BM_28_16 0x000000001fff0000
DECL|macro|BM_16_28
mdefine_line|#define BM_16_28 BM_28_16
DECL|macro|BM_29_16
mdefine_line|#define BM_29_16 0x000000003fff0000
DECL|macro|BM_16_29
mdefine_line|#define BM_16_29 BM_29_16
DECL|macro|BM_30_16
mdefine_line|#define BM_30_16 0x000000007fff0000
DECL|macro|BM_16_30
mdefine_line|#define BM_16_30 BM_30_16
DECL|macro|BM_31_16
mdefine_line|#define BM_31_16 0x00000000ffff0000
DECL|macro|BM_16_31
mdefine_line|#define BM_16_31 BM_31_16
DECL|macro|BM_32_16
mdefine_line|#define BM_32_16 0x00000001ffff0000
DECL|macro|BM_16_32
mdefine_line|#define BM_16_32 BM_32_16
DECL|macro|BM_33_16
mdefine_line|#define BM_33_16 0x00000003ffff0000
DECL|macro|BM_16_33
mdefine_line|#define BM_16_33 BM_33_16
DECL|macro|BM_34_16
mdefine_line|#define BM_34_16 0x00000007ffff0000
DECL|macro|BM_16_34
mdefine_line|#define BM_16_34 BM_34_16
DECL|macro|BM_35_16
mdefine_line|#define BM_35_16 0x0000000fffff0000
DECL|macro|BM_16_35
mdefine_line|#define BM_16_35 BM_35_16
DECL|macro|BM_36_16
mdefine_line|#define BM_36_16 0x0000001fffff0000
DECL|macro|BM_16_36
mdefine_line|#define BM_16_36 BM_36_16
DECL|macro|BM_37_16
mdefine_line|#define BM_37_16 0x0000003fffff0000
DECL|macro|BM_16_37
mdefine_line|#define BM_16_37 BM_37_16
DECL|macro|BM_38_16
mdefine_line|#define BM_38_16 0x0000007fffff0000
DECL|macro|BM_16_38
mdefine_line|#define BM_16_38 BM_38_16
DECL|macro|BM_39_16
mdefine_line|#define BM_39_16 0x000000ffffff0000
DECL|macro|BM_16_39
mdefine_line|#define BM_16_39 BM_39_16
DECL|macro|BM_40_16
mdefine_line|#define BM_40_16 0x000001ffffff0000
DECL|macro|BM_16_40
mdefine_line|#define BM_16_40 BM_40_16
DECL|macro|BM_41_16
mdefine_line|#define BM_41_16 0x000003ffffff0000
DECL|macro|BM_16_41
mdefine_line|#define BM_16_41 BM_41_16
DECL|macro|BM_42_16
mdefine_line|#define BM_42_16 0x000007ffffff0000
DECL|macro|BM_16_42
mdefine_line|#define BM_16_42 BM_42_16
DECL|macro|BM_43_16
mdefine_line|#define BM_43_16 0x00000fffffff0000
DECL|macro|BM_16_43
mdefine_line|#define BM_16_43 BM_43_16
DECL|macro|BM_44_16
mdefine_line|#define BM_44_16 0x00001fffffff0000
DECL|macro|BM_16_44
mdefine_line|#define BM_16_44 BM_44_16
DECL|macro|BM_45_16
mdefine_line|#define BM_45_16 0x00003fffffff0000
DECL|macro|BM_16_45
mdefine_line|#define BM_16_45 BM_45_16
DECL|macro|BM_46_16
mdefine_line|#define BM_46_16 0x00007fffffff0000
DECL|macro|BM_16_46
mdefine_line|#define BM_16_46 BM_46_16
DECL|macro|BM_47_16
mdefine_line|#define BM_47_16 0x0000ffffffff0000
DECL|macro|BM_16_47
mdefine_line|#define BM_16_47 BM_47_16
DECL|macro|BM_48_16
mdefine_line|#define BM_48_16 0x0001ffffffff0000
DECL|macro|BM_16_48
mdefine_line|#define BM_16_48 BM_48_16
DECL|macro|BM_49_16
mdefine_line|#define BM_49_16 0x0003ffffffff0000
DECL|macro|BM_16_49
mdefine_line|#define BM_16_49 BM_49_16
DECL|macro|BM_50_16
mdefine_line|#define BM_50_16 0x0007ffffffff0000
DECL|macro|BM_16_50
mdefine_line|#define BM_16_50 BM_50_16
DECL|macro|BM_51_16
mdefine_line|#define BM_51_16 0x000fffffffff0000
DECL|macro|BM_16_51
mdefine_line|#define BM_16_51 BM_51_16
DECL|macro|BM_52_16
mdefine_line|#define BM_52_16 0x001fffffffff0000
DECL|macro|BM_16_52
mdefine_line|#define BM_16_52 BM_52_16
DECL|macro|BM_53_16
mdefine_line|#define BM_53_16 0x003fffffffff0000
DECL|macro|BM_16_53
mdefine_line|#define BM_16_53 BM_53_16
DECL|macro|BM_54_16
mdefine_line|#define BM_54_16 0x007fffffffff0000
DECL|macro|BM_16_54
mdefine_line|#define BM_16_54 BM_54_16
DECL|macro|BM_55_16
mdefine_line|#define BM_55_16 0x00ffffffffff0000
DECL|macro|BM_16_55
mdefine_line|#define BM_16_55 BM_55_16
DECL|macro|BM_56_16
mdefine_line|#define BM_56_16 0x01ffffffffff0000
DECL|macro|BM_16_56
mdefine_line|#define BM_16_56 BM_56_16
DECL|macro|BM_57_16
mdefine_line|#define BM_57_16 0x03ffffffffff0000
DECL|macro|BM_16_57
mdefine_line|#define BM_16_57 BM_57_16
DECL|macro|BM_58_16
mdefine_line|#define BM_58_16 0x07ffffffffff0000
DECL|macro|BM_16_58
mdefine_line|#define BM_16_58 BM_58_16
DECL|macro|BM_59_16
mdefine_line|#define BM_59_16 0x0fffffffffff0000
DECL|macro|BM_16_59
mdefine_line|#define BM_16_59 BM_59_16
DECL|macro|BM_60_16
mdefine_line|#define BM_60_16 0x1fffffffffff0000
DECL|macro|BM_16_60
mdefine_line|#define BM_16_60 BM_60_16
DECL|macro|BM_61_16
mdefine_line|#define BM_61_16 0x3fffffffffff0000
DECL|macro|BM_16_61
mdefine_line|#define BM_16_61 BM_61_16
DECL|macro|BM_62_16
mdefine_line|#define BM_62_16 0x7fffffffffff0000
DECL|macro|BM_16_62
mdefine_line|#define BM_16_62 BM_62_16
DECL|macro|BM_63_16
mdefine_line|#define BM_63_16 0xffffffffffff0000
DECL|macro|BM_16_63
mdefine_line|#define BM_16_63 BM_63_16
DECL|macro|BM_17_17
mdefine_line|#define BM_17_17 0x0000000000020000
DECL|macro|BM_18_17
mdefine_line|#define BM_18_17 0x0000000000060000
DECL|macro|BM_17_18
mdefine_line|#define BM_17_18 BM_18_17
DECL|macro|BM_19_17
mdefine_line|#define BM_19_17 0x00000000000e0000
DECL|macro|BM_17_19
mdefine_line|#define BM_17_19 BM_19_17
DECL|macro|BM_20_17
mdefine_line|#define BM_20_17 0x00000000001e0000
DECL|macro|BM_17_20
mdefine_line|#define BM_17_20 BM_20_17
DECL|macro|BM_21_17
mdefine_line|#define BM_21_17 0x00000000003e0000
DECL|macro|BM_17_21
mdefine_line|#define BM_17_21 BM_21_17
DECL|macro|BM_22_17
mdefine_line|#define BM_22_17 0x00000000007e0000
DECL|macro|BM_17_22
mdefine_line|#define BM_17_22 BM_22_17
DECL|macro|BM_23_17
mdefine_line|#define BM_23_17 0x0000000000fe0000
DECL|macro|BM_17_23
mdefine_line|#define BM_17_23 BM_23_17
DECL|macro|BM_24_17
mdefine_line|#define BM_24_17 0x0000000001fe0000
DECL|macro|BM_17_24
mdefine_line|#define BM_17_24 BM_24_17
DECL|macro|BM_25_17
mdefine_line|#define BM_25_17 0x0000000003fe0000
DECL|macro|BM_17_25
mdefine_line|#define BM_17_25 BM_25_17
DECL|macro|BM_26_17
mdefine_line|#define BM_26_17 0x0000000007fe0000
DECL|macro|BM_17_26
mdefine_line|#define BM_17_26 BM_26_17
DECL|macro|BM_27_17
mdefine_line|#define BM_27_17 0x000000000ffe0000
DECL|macro|BM_17_27
mdefine_line|#define BM_17_27 BM_27_17
DECL|macro|BM_28_17
mdefine_line|#define BM_28_17 0x000000001ffe0000
DECL|macro|BM_17_28
mdefine_line|#define BM_17_28 BM_28_17
DECL|macro|BM_29_17
mdefine_line|#define BM_29_17 0x000000003ffe0000
DECL|macro|BM_17_29
mdefine_line|#define BM_17_29 BM_29_17
DECL|macro|BM_30_17
mdefine_line|#define BM_30_17 0x000000007ffe0000
DECL|macro|BM_17_30
mdefine_line|#define BM_17_30 BM_30_17
DECL|macro|BM_31_17
mdefine_line|#define BM_31_17 0x00000000fffe0000
DECL|macro|BM_17_31
mdefine_line|#define BM_17_31 BM_31_17
DECL|macro|BM_32_17
mdefine_line|#define BM_32_17 0x00000001fffe0000
DECL|macro|BM_17_32
mdefine_line|#define BM_17_32 BM_32_17
DECL|macro|BM_33_17
mdefine_line|#define BM_33_17 0x00000003fffe0000
DECL|macro|BM_17_33
mdefine_line|#define BM_17_33 BM_33_17
DECL|macro|BM_34_17
mdefine_line|#define BM_34_17 0x00000007fffe0000
DECL|macro|BM_17_34
mdefine_line|#define BM_17_34 BM_34_17
DECL|macro|BM_35_17
mdefine_line|#define BM_35_17 0x0000000ffffe0000
DECL|macro|BM_17_35
mdefine_line|#define BM_17_35 BM_35_17
DECL|macro|BM_36_17
mdefine_line|#define BM_36_17 0x0000001ffffe0000
DECL|macro|BM_17_36
mdefine_line|#define BM_17_36 BM_36_17
DECL|macro|BM_37_17
mdefine_line|#define BM_37_17 0x0000003ffffe0000
DECL|macro|BM_17_37
mdefine_line|#define BM_17_37 BM_37_17
DECL|macro|BM_38_17
mdefine_line|#define BM_38_17 0x0000007ffffe0000
DECL|macro|BM_17_38
mdefine_line|#define BM_17_38 BM_38_17
DECL|macro|BM_39_17
mdefine_line|#define BM_39_17 0x000000fffffe0000
DECL|macro|BM_17_39
mdefine_line|#define BM_17_39 BM_39_17
DECL|macro|BM_40_17
mdefine_line|#define BM_40_17 0x000001fffffe0000
DECL|macro|BM_17_40
mdefine_line|#define BM_17_40 BM_40_17
DECL|macro|BM_41_17
mdefine_line|#define BM_41_17 0x000003fffffe0000
DECL|macro|BM_17_41
mdefine_line|#define BM_17_41 BM_41_17
DECL|macro|BM_42_17
mdefine_line|#define BM_42_17 0x000007fffffe0000
DECL|macro|BM_17_42
mdefine_line|#define BM_17_42 BM_42_17
DECL|macro|BM_43_17
mdefine_line|#define BM_43_17 0x00000ffffffe0000
DECL|macro|BM_17_43
mdefine_line|#define BM_17_43 BM_43_17
DECL|macro|BM_44_17
mdefine_line|#define BM_44_17 0x00001ffffffe0000
DECL|macro|BM_17_44
mdefine_line|#define BM_17_44 BM_44_17
DECL|macro|BM_45_17
mdefine_line|#define BM_45_17 0x00003ffffffe0000
DECL|macro|BM_17_45
mdefine_line|#define BM_17_45 BM_45_17
DECL|macro|BM_46_17
mdefine_line|#define BM_46_17 0x00007ffffffe0000
DECL|macro|BM_17_46
mdefine_line|#define BM_17_46 BM_46_17
DECL|macro|BM_47_17
mdefine_line|#define BM_47_17 0x0000fffffffe0000
DECL|macro|BM_17_47
mdefine_line|#define BM_17_47 BM_47_17
DECL|macro|BM_48_17
mdefine_line|#define BM_48_17 0x0001fffffffe0000
DECL|macro|BM_17_48
mdefine_line|#define BM_17_48 BM_48_17
DECL|macro|BM_49_17
mdefine_line|#define BM_49_17 0x0003fffffffe0000
DECL|macro|BM_17_49
mdefine_line|#define BM_17_49 BM_49_17
DECL|macro|BM_50_17
mdefine_line|#define BM_50_17 0x0007fffffffe0000
DECL|macro|BM_17_50
mdefine_line|#define BM_17_50 BM_50_17
DECL|macro|BM_51_17
mdefine_line|#define BM_51_17 0x000ffffffffe0000
DECL|macro|BM_17_51
mdefine_line|#define BM_17_51 BM_51_17
DECL|macro|BM_52_17
mdefine_line|#define BM_52_17 0x001ffffffffe0000
DECL|macro|BM_17_52
mdefine_line|#define BM_17_52 BM_52_17
DECL|macro|BM_53_17
mdefine_line|#define BM_53_17 0x003ffffffffe0000
DECL|macro|BM_17_53
mdefine_line|#define BM_17_53 BM_53_17
DECL|macro|BM_54_17
mdefine_line|#define BM_54_17 0x007ffffffffe0000
DECL|macro|BM_17_54
mdefine_line|#define BM_17_54 BM_54_17
DECL|macro|BM_55_17
mdefine_line|#define BM_55_17 0x00fffffffffe0000
DECL|macro|BM_17_55
mdefine_line|#define BM_17_55 BM_55_17
DECL|macro|BM_56_17
mdefine_line|#define BM_56_17 0x01fffffffffe0000
DECL|macro|BM_17_56
mdefine_line|#define BM_17_56 BM_56_17
DECL|macro|BM_57_17
mdefine_line|#define BM_57_17 0x03fffffffffe0000
DECL|macro|BM_17_57
mdefine_line|#define BM_17_57 BM_57_17
DECL|macro|BM_58_17
mdefine_line|#define BM_58_17 0x07fffffffffe0000
DECL|macro|BM_17_58
mdefine_line|#define BM_17_58 BM_58_17
DECL|macro|BM_59_17
mdefine_line|#define BM_59_17 0x0ffffffffffe0000
DECL|macro|BM_17_59
mdefine_line|#define BM_17_59 BM_59_17
DECL|macro|BM_60_17
mdefine_line|#define BM_60_17 0x1ffffffffffe0000
DECL|macro|BM_17_60
mdefine_line|#define BM_17_60 BM_60_17
DECL|macro|BM_61_17
mdefine_line|#define BM_61_17 0x3ffffffffffe0000
DECL|macro|BM_17_61
mdefine_line|#define BM_17_61 BM_61_17
DECL|macro|BM_62_17
mdefine_line|#define BM_62_17 0x7ffffffffffe0000
DECL|macro|BM_17_62
mdefine_line|#define BM_17_62 BM_62_17
DECL|macro|BM_63_17
mdefine_line|#define BM_63_17 0xfffffffffffe0000
DECL|macro|BM_17_63
mdefine_line|#define BM_17_63 BM_63_17
DECL|macro|BM_18_18
mdefine_line|#define BM_18_18 0x0000000000040000
DECL|macro|BM_19_18
mdefine_line|#define BM_19_18 0x00000000000c0000
DECL|macro|BM_18_19
mdefine_line|#define BM_18_19 BM_19_18
DECL|macro|BM_20_18
mdefine_line|#define BM_20_18 0x00000000001c0000
DECL|macro|BM_18_20
mdefine_line|#define BM_18_20 BM_20_18
DECL|macro|BM_21_18
mdefine_line|#define BM_21_18 0x00000000003c0000
DECL|macro|BM_18_21
mdefine_line|#define BM_18_21 BM_21_18
DECL|macro|BM_22_18
mdefine_line|#define BM_22_18 0x00000000007c0000
DECL|macro|BM_18_22
mdefine_line|#define BM_18_22 BM_22_18
DECL|macro|BM_23_18
mdefine_line|#define BM_23_18 0x0000000000fc0000
DECL|macro|BM_18_23
mdefine_line|#define BM_18_23 BM_23_18
DECL|macro|BM_24_18
mdefine_line|#define BM_24_18 0x0000000001fc0000
DECL|macro|BM_18_24
mdefine_line|#define BM_18_24 BM_24_18
DECL|macro|BM_25_18
mdefine_line|#define BM_25_18 0x0000000003fc0000
DECL|macro|BM_18_25
mdefine_line|#define BM_18_25 BM_25_18
DECL|macro|BM_26_18
mdefine_line|#define BM_26_18 0x0000000007fc0000
DECL|macro|BM_18_26
mdefine_line|#define BM_18_26 BM_26_18
DECL|macro|BM_27_18
mdefine_line|#define BM_27_18 0x000000000ffc0000
DECL|macro|BM_18_27
mdefine_line|#define BM_18_27 BM_27_18
DECL|macro|BM_28_18
mdefine_line|#define BM_28_18 0x000000001ffc0000
DECL|macro|BM_18_28
mdefine_line|#define BM_18_28 BM_28_18
DECL|macro|BM_29_18
mdefine_line|#define BM_29_18 0x000000003ffc0000
DECL|macro|BM_18_29
mdefine_line|#define BM_18_29 BM_29_18
DECL|macro|BM_30_18
mdefine_line|#define BM_30_18 0x000000007ffc0000
DECL|macro|BM_18_30
mdefine_line|#define BM_18_30 BM_30_18
DECL|macro|BM_31_18
mdefine_line|#define BM_31_18 0x00000000fffc0000
DECL|macro|BM_18_31
mdefine_line|#define BM_18_31 BM_31_18
DECL|macro|BM_32_18
mdefine_line|#define BM_32_18 0x00000001fffc0000
DECL|macro|BM_18_32
mdefine_line|#define BM_18_32 BM_32_18
DECL|macro|BM_33_18
mdefine_line|#define BM_33_18 0x00000003fffc0000
DECL|macro|BM_18_33
mdefine_line|#define BM_18_33 BM_33_18
DECL|macro|BM_34_18
mdefine_line|#define BM_34_18 0x00000007fffc0000
DECL|macro|BM_18_34
mdefine_line|#define BM_18_34 BM_34_18
DECL|macro|BM_35_18
mdefine_line|#define BM_35_18 0x0000000ffffc0000
DECL|macro|BM_18_35
mdefine_line|#define BM_18_35 BM_35_18
DECL|macro|BM_36_18
mdefine_line|#define BM_36_18 0x0000001ffffc0000
DECL|macro|BM_18_36
mdefine_line|#define BM_18_36 BM_36_18
DECL|macro|BM_37_18
mdefine_line|#define BM_37_18 0x0000003ffffc0000
DECL|macro|BM_18_37
mdefine_line|#define BM_18_37 BM_37_18
DECL|macro|BM_38_18
mdefine_line|#define BM_38_18 0x0000007ffffc0000
DECL|macro|BM_18_38
mdefine_line|#define BM_18_38 BM_38_18
DECL|macro|BM_39_18
mdefine_line|#define BM_39_18 0x000000fffffc0000
DECL|macro|BM_18_39
mdefine_line|#define BM_18_39 BM_39_18
DECL|macro|BM_40_18
mdefine_line|#define BM_40_18 0x000001fffffc0000
DECL|macro|BM_18_40
mdefine_line|#define BM_18_40 BM_40_18
DECL|macro|BM_41_18
mdefine_line|#define BM_41_18 0x000003fffffc0000
DECL|macro|BM_18_41
mdefine_line|#define BM_18_41 BM_41_18
DECL|macro|BM_42_18
mdefine_line|#define BM_42_18 0x000007fffffc0000
DECL|macro|BM_18_42
mdefine_line|#define BM_18_42 BM_42_18
DECL|macro|BM_43_18
mdefine_line|#define BM_43_18 0x00000ffffffc0000
DECL|macro|BM_18_43
mdefine_line|#define BM_18_43 BM_43_18
DECL|macro|BM_44_18
mdefine_line|#define BM_44_18 0x00001ffffffc0000
DECL|macro|BM_18_44
mdefine_line|#define BM_18_44 BM_44_18
DECL|macro|BM_45_18
mdefine_line|#define BM_45_18 0x00003ffffffc0000
DECL|macro|BM_18_45
mdefine_line|#define BM_18_45 BM_45_18
DECL|macro|BM_46_18
mdefine_line|#define BM_46_18 0x00007ffffffc0000
DECL|macro|BM_18_46
mdefine_line|#define BM_18_46 BM_46_18
DECL|macro|BM_47_18
mdefine_line|#define BM_47_18 0x0000fffffffc0000
DECL|macro|BM_18_47
mdefine_line|#define BM_18_47 BM_47_18
DECL|macro|BM_48_18
mdefine_line|#define BM_48_18 0x0001fffffffc0000
DECL|macro|BM_18_48
mdefine_line|#define BM_18_48 BM_48_18
DECL|macro|BM_49_18
mdefine_line|#define BM_49_18 0x0003fffffffc0000
DECL|macro|BM_18_49
mdefine_line|#define BM_18_49 BM_49_18
DECL|macro|BM_50_18
mdefine_line|#define BM_50_18 0x0007fffffffc0000
DECL|macro|BM_18_50
mdefine_line|#define BM_18_50 BM_50_18
DECL|macro|BM_51_18
mdefine_line|#define BM_51_18 0x000ffffffffc0000
DECL|macro|BM_18_51
mdefine_line|#define BM_18_51 BM_51_18
DECL|macro|BM_52_18
mdefine_line|#define BM_52_18 0x001ffffffffc0000
DECL|macro|BM_18_52
mdefine_line|#define BM_18_52 BM_52_18
DECL|macro|BM_53_18
mdefine_line|#define BM_53_18 0x003ffffffffc0000
DECL|macro|BM_18_53
mdefine_line|#define BM_18_53 BM_53_18
DECL|macro|BM_54_18
mdefine_line|#define BM_54_18 0x007ffffffffc0000
DECL|macro|BM_18_54
mdefine_line|#define BM_18_54 BM_54_18
DECL|macro|BM_55_18
mdefine_line|#define BM_55_18 0x00fffffffffc0000
DECL|macro|BM_18_55
mdefine_line|#define BM_18_55 BM_55_18
DECL|macro|BM_56_18
mdefine_line|#define BM_56_18 0x01fffffffffc0000
DECL|macro|BM_18_56
mdefine_line|#define BM_18_56 BM_56_18
DECL|macro|BM_57_18
mdefine_line|#define BM_57_18 0x03fffffffffc0000
DECL|macro|BM_18_57
mdefine_line|#define BM_18_57 BM_57_18
DECL|macro|BM_58_18
mdefine_line|#define BM_58_18 0x07fffffffffc0000
DECL|macro|BM_18_58
mdefine_line|#define BM_18_58 BM_58_18
DECL|macro|BM_59_18
mdefine_line|#define BM_59_18 0x0ffffffffffc0000
DECL|macro|BM_18_59
mdefine_line|#define BM_18_59 BM_59_18
DECL|macro|BM_60_18
mdefine_line|#define BM_60_18 0x1ffffffffffc0000
DECL|macro|BM_18_60
mdefine_line|#define BM_18_60 BM_60_18
DECL|macro|BM_61_18
mdefine_line|#define BM_61_18 0x3ffffffffffc0000
DECL|macro|BM_18_61
mdefine_line|#define BM_18_61 BM_61_18
DECL|macro|BM_62_18
mdefine_line|#define BM_62_18 0x7ffffffffffc0000
DECL|macro|BM_18_62
mdefine_line|#define BM_18_62 BM_62_18
DECL|macro|BM_63_18
mdefine_line|#define BM_63_18 0xfffffffffffc0000
DECL|macro|BM_18_63
mdefine_line|#define BM_18_63 BM_63_18
DECL|macro|BM_19_19
mdefine_line|#define BM_19_19 0x0000000000080000
DECL|macro|BM_20_19
mdefine_line|#define BM_20_19 0x0000000000180000
DECL|macro|BM_19_20
mdefine_line|#define BM_19_20 BM_20_19
DECL|macro|BM_21_19
mdefine_line|#define BM_21_19 0x0000000000380000
DECL|macro|BM_19_21
mdefine_line|#define BM_19_21 BM_21_19
DECL|macro|BM_22_19
mdefine_line|#define BM_22_19 0x0000000000780000
DECL|macro|BM_19_22
mdefine_line|#define BM_19_22 BM_22_19
DECL|macro|BM_23_19
mdefine_line|#define BM_23_19 0x0000000000f80000
DECL|macro|BM_19_23
mdefine_line|#define BM_19_23 BM_23_19
DECL|macro|BM_24_19
mdefine_line|#define BM_24_19 0x0000000001f80000
DECL|macro|BM_19_24
mdefine_line|#define BM_19_24 BM_24_19
DECL|macro|BM_25_19
mdefine_line|#define BM_25_19 0x0000000003f80000
DECL|macro|BM_19_25
mdefine_line|#define BM_19_25 BM_25_19
DECL|macro|BM_26_19
mdefine_line|#define BM_26_19 0x0000000007f80000
DECL|macro|BM_19_26
mdefine_line|#define BM_19_26 BM_26_19
DECL|macro|BM_27_19
mdefine_line|#define BM_27_19 0x000000000ff80000
DECL|macro|BM_19_27
mdefine_line|#define BM_19_27 BM_27_19
DECL|macro|BM_28_19
mdefine_line|#define BM_28_19 0x000000001ff80000
DECL|macro|BM_19_28
mdefine_line|#define BM_19_28 BM_28_19
DECL|macro|BM_29_19
mdefine_line|#define BM_29_19 0x000000003ff80000
DECL|macro|BM_19_29
mdefine_line|#define BM_19_29 BM_29_19
DECL|macro|BM_30_19
mdefine_line|#define BM_30_19 0x000000007ff80000
DECL|macro|BM_19_30
mdefine_line|#define BM_19_30 BM_30_19
DECL|macro|BM_31_19
mdefine_line|#define BM_31_19 0x00000000fff80000
DECL|macro|BM_19_31
mdefine_line|#define BM_19_31 BM_31_19
DECL|macro|BM_32_19
mdefine_line|#define BM_32_19 0x00000001fff80000
DECL|macro|BM_19_32
mdefine_line|#define BM_19_32 BM_32_19
DECL|macro|BM_33_19
mdefine_line|#define BM_33_19 0x00000003fff80000
DECL|macro|BM_19_33
mdefine_line|#define BM_19_33 BM_33_19
DECL|macro|BM_34_19
mdefine_line|#define BM_34_19 0x00000007fff80000
DECL|macro|BM_19_34
mdefine_line|#define BM_19_34 BM_34_19
DECL|macro|BM_35_19
mdefine_line|#define BM_35_19 0x0000000ffff80000
DECL|macro|BM_19_35
mdefine_line|#define BM_19_35 BM_35_19
DECL|macro|BM_36_19
mdefine_line|#define BM_36_19 0x0000001ffff80000
DECL|macro|BM_19_36
mdefine_line|#define BM_19_36 BM_36_19
DECL|macro|BM_37_19
mdefine_line|#define BM_37_19 0x0000003ffff80000
DECL|macro|BM_19_37
mdefine_line|#define BM_19_37 BM_37_19
DECL|macro|BM_38_19
mdefine_line|#define BM_38_19 0x0000007ffff80000
DECL|macro|BM_19_38
mdefine_line|#define BM_19_38 BM_38_19
DECL|macro|BM_39_19
mdefine_line|#define BM_39_19 0x000000fffff80000
DECL|macro|BM_19_39
mdefine_line|#define BM_19_39 BM_39_19
DECL|macro|BM_40_19
mdefine_line|#define BM_40_19 0x000001fffff80000
DECL|macro|BM_19_40
mdefine_line|#define BM_19_40 BM_40_19
DECL|macro|BM_41_19
mdefine_line|#define BM_41_19 0x000003fffff80000
DECL|macro|BM_19_41
mdefine_line|#define BM_19_41 BM_41_19
DECL|macro|BM_42_19
mdefine_line|#define BM_42_19 0x000007fffff80000
DECL|macro|BM_19_42
mdefine_line|#define BM_19_42 BM_42_19
DECL|macro|BM_43_19
mdefine_line|#define BM_43_19 0x00000ffffff80000
DECL|macro|BM_19_43
mdefine_line|#define BM_19_43 BM_43_19
DECL|macro|BM_44_19
mdefine_line|#define BM_44_19 0x00001ffffff80000
DECL|macro|BM_19_44
mdefine_line|#define BM_19_44 BM_44_19
DECL|macro|BM_45_19
mdefine_line|#define BM_45_19 0x00003ffffff80000
DECL|macro|BM_19_45
mdefine_line|#define BM_19_45 BM_45_19
DECL|macro|BM_46_19
mdefine_line|#define BM_46_19 0x00007ffffff80000
DECL|macro|BM_19_46
mdefine_line|#define BM_19_46 BM_46_19
DECL|macro|BM_47_19
mdefine_line|#define BM_47_19 0x0000fffffff80000
DECL|macro|BM_19_47
mdefine_line|#define BM_19_47 BM_47_19
DECL|macro|BM_48_19
mdefine_line|#define BM_48_19 0x0001fffffff80000
DECL|macro|BM_19_48
mdefine_line|#define BM_19_48 BM_48_19
DECL|macro|BM_49_19
mdefine_line|#define BM_49_19 0x0003fffffff80000
DECL|macro|BM_19_49
mdefine_line|#define BM_19_49 BM_49_19
DECL|macro|BM_50_19
mdefine_line|#define BM_50_19 0x0007fffffff80000
DECL|macro|BM_19_50
mdefine_line|#define BM_19_50 BM_50_19
DECL|macro|BM_51_19
mdefine_line|#define BM_51_19 0x000ffffffff80000
DECL|macro|BM_19_51
mdefine_line|#define BM_19_51 BM_51_19
DECL|macro|BM_52_19
mdefine_line|#define BM_52_19 0x001ffffffff80000
DECL|macro|BM_19_52
mdefine_line|#define BM_19_52 BM_52_19
DECL|macro|BM_53_19
mdefine_line|#define BM_53_19 0x003ffffffff80000
DECL|macro|BM_19_53
mdefine_line|#define BM_19_53 BM_53_19
DECL|macro|BM_54_19
mdefine_line|#define BM_54_19 0x007ffffffff80000
DECL|macro|BM_19_54
mdefine_line|#define BM_19_54 BM_54_19
DECL|macro|BM_55_19
mdefine_line|#define BM_55_19 0x00fffffffff80000
DECL|macro|BM_19_55
mdefine_line|#define BM_19_55 BM_55_19
DECL|macro|BM_56_19
mdefine_line|#define BM_56_19 0x01fffffffff80000
DECL|macro|BM_19_56
mdefine_line|#define BM_19_56 BM_56_19
DECL|macro|BM_57_19
mdefine_line|#define BM_57_19 0x03fffffffff80000
DECL|macro|BM_19_57
mdefine_line|#define BM_19_57 BM_57_19
DECL|macro|BM_58_19
mdefine_line|#define BM_58_19 0x07fffffffff80000
DECL|macro|BM_19_58
mdefine_line|#define BM_19_58 BM_58_19
DECL|macro|BM_59_19
mdefine_line|#define BM_59_19 0x0ffffffffff80000
DECL|macro|BM_19_59
mdefine_line|#define BM_19_59 BM_59_19
DECL|macro|BM_60_19
mdefine_line|#define BM_60_19 0x1ffffffffff80000
DECL|macro|BM_19_60
mdefine_line|#define BM_19_60 BM_60_19
DECL|macro|BM_61_19
mdefine_line|#define BM_61_19 0x3ffffffffff80000
DECL|macro|BM_19_61
mdefine_line|#define BM_19_61 BM_61_19
DECL|macro|BM_62_19
mdefine_line|#define BM_62_19 0x7ffffffffff80000
DECL|macro|BM_19_62
mdefine_line|#define BM_19_62 BM_62_19
DECL|macro|BM_63_19
mdefine_line|#define BM_63_19 0xfffffffffff80000
DECL|macro|BM_19_63
mdefine_line|#define BM_19_63 BM_63_19
DECL|macro|BM_20_20
mdefine_line|#define BM_20_20 0x0000000000100000
DECL|macro|BM_21_20
mdefine_line|#define BM_21_20 0x0000000000300000
DECL|macro|BM_20_21
mdefine_line|#define BM_20_21 BM_21_20
DECL|macro|BM_22_20
mdefine_line|#define BM_22_20 0x0000000000700000
DECL|macro|BM_20_22
mdefine_line|#define BM_20_22 BM_22_20
DECL|macro|BM_23_20
mdefine_line|#define BM_23_20 0x0000000000f00000
DECL|macro|BM_20_23
mdefine_line|#define BM_20_23 BM_23_20
DECL|macro|BM_24_20
mdefine_line|#define BM_24_20 0x0000000001f00000
DECL|macro|BM_20_24
mdefine_line|#define BM_20_24 BM_24_20
DECL|macro|BM_25_20
mdefine_line|#define BM_25_20 0x0000000003f00000
DECL|macro|BM_20_25
mdefine_line|#define BM_20_25 BM_25_20
DECL|macro|BM_26_20
mdefine_line|#define BM_26_20 0x0000000007f00000
DECL|macro|BM_20_26
mdefine_line|#define BM_20_26 BM_26_20
DECL|macro|BM_27_20
mdefine_line|#define BM_27_20 0x000000000ff00000
DECL|macro|BM_20_27
mdefine_line|#define BM_20_27 BM_27_20
DECL|macro|BM_28_20
mdefine_line|#define BM_28_20 0x000000001ff00000
DECL|macro|BM_20_28
mdefine_line|#define BM_20_28 BM_28_20
DECL|macro|BM_29_20
mdefine_line|#define BM_29_20 0x000000003ff00000
DECL|macro|BM_20_29
mdefine_line|#define BM_20_29 BM_29_20
DECL|macro|BM_30_20
mdefine_line|#define BM_30_20 0x000000007ff00000
DECL|macro|BM_20_30
mdefine_line|#define BM_20_30 BM_30_20
DECL|macro|BM_31_20
mdefine_line|#define BM_31_20 0x00000000fff00000
DECL|macro|BM_20_31
mdefine_line|#define BM_20_31 BM_31_20
DECL|macro|BM_32_20
mdefine_line|#define BM_32_20 0x00000001fff00000
DECL|macro|BM_20_32
mdefine_line|#define BM_20_32 BM_32_20
DECL|macro|BM_33_20
mdefine_line|#define BM_33_20 0x00000003fff00000
DECL|macro|BM_20_33
mdefine_line|#define BM_20_33 BM_33_20
DECL|macro|BM_34_20
mdefine_line|#define BM_34_20 0x00000007fff00000
DECL|macro|BM_20_34
mdefine_line|#define BM_20_34 BM_34_20
DECL|macro|BM_35_20
mdefine_line|#define BM_35_20 0x0000000ffff00000
DECL|macro|BM_20_35
mdefine_line|#define BM_20_35 BM_35_20
DECL|macro|BM_36_20
mdefine_line|#define BM_36_20 0x0000001ffff00000
DECL|macro|BM_20_36
mdefine_line|#define BM_20_36 BM_36_20
DECL|macro|BM_37_20
mdefine_line|#define BM_37_20 0x0000003ffff00000
DECL|macro|BM_20_37
mdefine_line|#define BM_20_37 BM_37_20
DECL|macro|BM_38_20
mdefine_line|#define BM_38_20 0x0000007ffff00000
DECL|macro|BM_20_38
mdefine_line|#define BM_20_38 BM_38_20
DECL|macro|BM_39_20
mdefine_line|#define BM_39_20 0x000000fffff00000
DECL|macro|BM_20_39
mdefine_line|#define BM_20_39 BM_39_20
DECL|macro|BM_40_20
mdefine_line|#define BM_40_20 0x000001fffff00000
DECL|macro|BM_20_40
mdefine_line|#define BM_20_40 BM_40_20
DECL|macro|BM_41_20
mdefine_line|#define BM_41_20 0x000003fffff00000
DECL|macro|BM_20_41
mdefine_line|#define BM_20_41 BM_41_20
DECL|macro|BM_42_20
mdefine_line|#define BM_42_20 0x000007fffff00000
DECL|macro|BM_20_42
mdefine_line|#define BM_20_42 BM_42_20
DECL|macro|BM_43_20
mdefine_line|#define BM_43_20 0x00000ffffff00000
DECL|macro|BM_20_43
mdefine_line|#define BM_20_43 BM_43_20
DECL|macro|BM_44_20
mdefine_line|#define BM_44_20 0x00001ffffff00000
DECL|macro|BM_20_44
mdefine_line|#define BM_20_44 BM_44_20
DECL|macro|BM_45_20
mdefine_line|#define BM_45_20 0x00003ffffff00000
DECL|macro|BM_20_45
mdefine_line|#define BM_20_45 BM_45_20
DECL|macro|BM_46_20
mdefine_line|#define BM_46_20 0x00007ffffff00000
DECL|macro|BM_20_46
mdefine_line|#define BM_20_46 BM_46_20
DECL|macro|BM_47_20
mdefine_line|#define BM_47_20 0x0000fffffff00000
DECL|macro|BM_20_47
mdefine_line|#define BM_20_47 BM_47_20
DECL|macro|BM_48_20
mdefine_line|#define BM_48_20 0x0001fffffff00000
DECL|macro|BM_20_48
mdefine_line|#define BM_20_48 BM_48_20
DECL|macro|BM_49_20
mdefine_line|#define BM_49_20 0x0003fffffff00000
DECL|macro|BM_20_49
mdefine_line|#define BM_20_49 BM_49_20
DECL|macro|BM_50_20
mdefine_line|#define BM_50_20 0x0007fffffff00000
DECL|macro|BM_20_50
mdefine_line|#define BM_20_50 BM_50_20
DECL|macro|BM_51_20
mdefine_line|#define BM_51_20 0x000ffffffff00000
DECL|macro|BM_20_51
mdefine_line|#define BM_20_51 BM_51_20
DECL|macro|BM_52_20
mdefine_line|#define BM_52_20 0x001ffffffff00000
DECL|macro|BM_20_52
mdefine_line|#define BM_20_52 BM_52_20
DECL|macro|BM_53_20
mdefine_line|#define BM_53_20 0x003ffffffff00000
DECL|macro|BM_20_53
mdefine_line|#define BM_20_53 BM_53_20
DECL|macro|BM_54_20
mdefine_line|#define BM_54_20 0x007ffffffff00000
DECL|macro|BM_20_54
mdefine_line|#define BM_20_54 BM_54_20
DECL|macro|BM_55_20
mdefine_line|#define BM_55_20 0x00fffffffff00000
DECL|macro|BM_20_55
mdefine_line|#define BM_20_55 BM_55_20
DECL|macro|BM_56_20
mdefine_line|#define BM_56_20 0x01fffffffff00000
DECL|macro|BM_20_56
mdefine_line|#define BM_20_56 BM_56_20
DECL|macro|BM_57_20
mdefine_line|#define BM_57_20 0x03fffffffff00000
DECL|macro|BM_20_57
mdefine_line|#define BM_20_57 BM_57_20
DECL|macro|BM_58_20
mdefine_line|#define BM_58_20 0x07fffffffff00000
DECL|macro|BM_20_58
mdefine_line|#define BM_20_58 BM_58_20
DECL|macro|BM_59_20
mdefine_line|#define BM_59_20 0x0ffffffffff00000
DECL|macro|BM_20_59
mdefine_line|#define BM_20_59 BM_59_20
DECL|macro|BM_60_20
mdefine_line|#define BM_60_20 0x1ffffffffff00000
DECL|macro|BM_20_60
mdefine_line|#define BM_20_60 BM_60_20
DECL|macro|BM_61_20
mdefine_line|#define BM_61_20 0x3ffffffffff00000
DECL|macro|BM_20_61
mdefine_line|#define BM_20_61 BM_61_20
DECL|macro|BM_62_20
mdefine_line|#define BM_62_20 0x7ffffffffff00000
DECL|macro|BM_20_62
mdefine_line|#define BM_20_62 BM_62_20
DECL|macro|BM_63_20
mdefine_line|#define BM_63_20 0xfffffffffff00000
DECL|macro|BM_20_63
mdefine_line|#define BM_20_63 BM_63_20
DECL|macro|BM_21_21
mdefine_line|#define BM_21_21 0x0000000000200000
DECL|macro|BM_22_21
mdefine_line|#define BM_22_21 0x0000000000600000
DECL|macro|BM_21_22
mdefine_line|#define BM_21_22 BM_22_21
DECL|macro|BM_23_21
mdefine_line|#define BM_23_21 0x0000000000e00000
DECL|macro|BM_21_23
mdefine_line|#define BM_21_23 BM_23_21
DECL|macro|BM_24_21
mdefine_line|#define BM_24_21 0x0000000001e00000
DECL|macro|BM_21_24
mdefine_line|#define BM_21_24 BM_24_21
DECL|macro|BM_25_21
mdefine_line|#define BM_25_21 0x0000000003e00000
DECL|macro|BM_21_25
mdefine_line|#define BM_21_25 BM_25_21
DECL|macro|BM_26_21
mdefine_line|#define BM_26_21 0x0000000007e00000
DECL|macro|BM_21_26
mdefine_line|#define BM_21_26 BM_26_21
DECL|macro|BM_27_21
mdefine_line|#define BM_27_21 0x000000000fe00000
DECL|macro|BM_21_27
mdefine_line|#define BM_21_27 BM_27_21
DECL|macro|BM_28_21
mdefine_line|#define BM_28_21 0x000000001fe00000
DECL|macro|BM_21_28
mdefine_line|#define BM_21_28 BM_28_21
DECL|macro|BM_29_21
mdefine_line|#define BM_29_21 0x000000003fe00000
DECL|macro|BM_21_29
mdefine_line|#define BM_21_29 BM_29_21
DECL|macro|BM_30_21
mdefine_line|#define BM_30_21 0x000000007fe00000
DECL|macro|BM_21_30
mdefine_line|#define BM_21_30 BM_30_21
DECL|macro|BM_31_21
mdefine_line|#define BM_31_21 0x00000000ffe00000
DECL|macro|BM_21_31
mdefine_line|#define BM_21_31 BM_31_21
DECL|macro|BM_32_21
mdefine_line|#define BM_32_21 0x00000001ffe00000
DECL|macro|BM_21_32
mdefine_line|#define BM_21_32 BM_32_21
DECL|macro|BM_33_21
mdefine_line|#define BM_33_21 0x00000003ffe00000
DECL|macro|BM_21_33
mdefine_line|#define BM_21_33 BM_33_21
DECL|macro|BM_34_21
mdefine_line|#define BM_34_21 0x00000007ffe00000
DECL|macro|BM_21_34
mdefine_line|#define BM_21_34 BM_34_21
DECL|macro|BM_35_21
mdefine_line|#define BM_35_21 0x0000000fffe00000
DECL|macro|BM_21_35
mdefine_line|#define BM_21_35 BM_35_21
DECL|macro|BM_36_21
mdefine_line|#define BM_36_21 0x0000001fffe00000
DECL|macro|BM_21_36
mdefine_line|#define BM_21_36 BM_36_21
DECL|macro|BM_37_21
mdefine_line|#define BM_37_21 0x0000003fffe00000
DECL|macro|BM_21_37
mdefine_line|#define BM_21_37 BM_37_21
DECL|macro|BM_38_21
mdefine_line|#define BM_38_21 0x0000007fffe00000
DECL|macro|BM_21_38
mdefine_line|#define BM_21_38 BM_38_21
DECL|macro|BM_39_21
mdefine_line|#define BM_39_21 0x000000ffffe00000
DECL|macro|BM_21_39
mdefine_line|#define BM_21_39 BM_39_21
DECL|macro|BM_40_21
mdefine_line|#define BM_40_21 0x000001ffffe00000
DECL|macro|BM_21_40
mdefine_line|#define BM_21_40 BM_40_21
DECL|macro|BM_41_21
mdefine_line|#define BM_41_21 0x000003ffffe00000
DECL|macro|BM_21_41
mdefine_line|#define BM_21_41 BM_41_21
DECL|macro|BM_42_21
mdefine_line|#define BM_42_21 0x000007ffffe00000
DECL|macro|BM_21_42
mdefine_line|#define BM_21_42 BM_42_21
DECL|macro|BM_43_21
mdefine_line|#define BM_43_21 0x00000fffffe00000
DECL|macro|BM_21_43
mdefine_line|#define BM_21_43 BM_43_21
DECL|macro|BM_44_21
mdefine_line|#define BM_44_21 0x00001fffffe00000
DECL|macro|BM_21_44
mdefine_line|#define BM_21_44 BM_44_21
DECL|macro|BM_45_21
mdefine_line|#define BM_45_21 0x00003fffffe00000
DECL|macro|BM_21_45
mdefine_line|#define BM_21_45 BM_45_21
DECL|macro|BM_46_21
mdefine_line|#define BM_46_21 0x00007fffffe00000
DECL|macro|BM_21_46
mdefine_line|#define BM_21_46 BM_46_21
DECL|macro|BM_47_21
mdefine_line|#define BM_47_21 0x0000ffffffe00000
DECL|macro|BM_21_47
mdefine_line|#define BM_21_47 BM_47_21
DECL|macro|BM_48_21
mdefine_line|#define BM_48_21 0x0001ffffffe00000
DECL|macro|BM_21_48
mdefine_line|#define BM_21_48 BM_48_21
DECL|macro|BM_49_21
mdefine_line|#define BM_49_21 0x0003ffffffe00000
DECL|macro|BM_21_49
mdefine_line|#define BM_21_49 BM_49_21
DECL|macro|BM_50_21
mdefine_line|#define BM_50_21 0x0007ffffffe00000
DECL|macro|BM_21_50
mdefine_line|#define BM_21_50 BM_50_21
DECL|macro|BM_51_21
mdefine_line|#define BM_51_21 0x000fffffffe00000
DECL|macro|BM_21_51
mdefine_line|#define BM_21_51 BM_51_21
DECL|macro|BM_52_21
mdefine_line|#define BM_52_21 0x001fffffffe00000
DECL|macro|BM_21_52
mdefine_line|#define BM_21_52 BM_52_21
DECL|macro|BM_53_21
mdefine_line|#define BM_53_21 0x003fffffffe00000
DECL|macro|BM_21_53
mdefine_line|#define BM_21_53 BM_53_21
DECL|macro|BM_54_21
mdefine_line|#define BM_54_21 0x007fffffffe00000
DECL|macro|BM_21_54
mdefine_line|#define BM_21_54 BM_54_21
DECL|macro|BM_55_21
mdefine_line|#define BM_55_21 0x00ffffffffe00000
DECL|macro|BM_21_55
mdefine_line|#define BM_21_55 BM_55_21
DECL|macro|BM_56_21
mdefine_line|#define BM_56_21 0x01ffffffffe00000
DECL|macro|BM_21_56
mdefine_line|#define BM_21_56 BM_56_21
DECL|macro|BM_57_21
mdefine_line|#define BM_57_21 0x03ffffffffe00000
DECL|macro|BM_21_57
mdefine_line|#define BM_21_57 BM_57_21
DECL|macro|BM_58_21
mdefine_line|#define BM_58_21 0x07ffffffffe00000
DECL|macro|BM_21_58
mdefine_line|#define BM_21_58 BM_58_21
DECL|macro|BM_59_21
mdefine_line|#define BM_59_21 0x0fffffffffe00000
DECL|macro|BM_21_59
mdefine_line|#define BM_21_59 BM_59_21
DECL|macro|BM_60_21
mdefine_line|#define BM_60_21 0x1fffffffffe00000
DECL|macro|BM_21_60
mdefine_line|#define BM_21_60 BM_60_21
DECL|macro|BM_61_21
mdefine_line|#define BM_61_21 0x3fffffffffe00000
DECL|macro|BM_21_61
mdefine_line|#define BM_21_61 BM_61_21
DECL|macro|BM_62_21
mdefine_line|#define BM_62_21 0x7fffffffffe00000
DECL|macro|BM_21_62
mdefine_line|#define BM_21_62 BM_62_21
DECL|macro|BM_63_21
mdefine_line|#define BM_63_21 0xffffffffffe00000
DECL|macro|BM_21_63
mdefine_line|#define BM_21_63 BM_63_21
DECL|macro|BM_22_22
mdefine_line|#define BM_22_22 0x0000000000400000
DECL|macro|BM_23_22
mdefine_line|#define BM_23_22 0x0000000000c00000
DECL|macro|BM_22_23
mdefine_line|#define BM_22_23 BM_23_22
DECL|macro|BM_24_22
mdefine_line|#define BM_24_22 0x0000000001c00000
DECL|macro|BM_22_24
mdefine_line|#define BM_22_24 BM_24_22
DECL|macro|BM_25_22
mdefine_line|#define BM_25_22 0x0000000003c00000
DECL|macro|BM_22_25
mdefine_line|#define BM_22_25 BM_25_22
DECL|macro|BM_26_22
mdefine_line|#define BM_26_22 0x0000000007c00000
DECL|macro|BM_22_26
mdefine_line|#define BM_22_26 BM_26_22
DECL|macro|BM_27_22
mdefine_line|#define BM_27_22 0x000000000fc00000
DECL|macro|BM_22_27
mdefine_line|#define BM_22_27 BM_27_22
DECL|macro|BM_28_22
mdefine_line|#define BM_28_22 0x000000001fc00000
DECL|macro|BM_22_28
mdefine_line|#define BM_22_28 BM_28_22
DECL|macro|BM_29_22
mdefine_line|#define BM_29_22 0x000000003fc00000
DECL|macro|BM_22_29
mdefine_line|#define BM_22_29 BM_29_22
DECL|macro|BM_30_22
mdefine_line|#define BM_30_22 0x000000007fc00000
DECL|macro|BM_22_30
mdefine_line|#define BM_22_30 BM_30_22
DECL|macro|BM_31_22
mdefine_line|#define BM_31_22 0x00000000ffc00000
DECL|macro|BM_22_31
mdefine_line|#define BM_22_31 BM_31_22
DECL|macro|BM_32_22
mdefine_line|#define BM_32_22 0x00000001ffc00000
DECL|macro|BM_22_32
mdefine_line|#define BM_22_32 BM_32_22
DECL|macro|BM_33_22
mdefine_line|#define BM_33_22 0x00000003ffc00000
DECL|macro|BM_22_33
mdefine_line|#define BM_22_33 BM_33_22
DECL|macro|BM_34_22
mdefine_line|#define BM_34_22 0x00000007ffc00000
DECL|macro|BM_22_34
mdefine_line|#define BM_22_34 BM_34_22
DECL|macro|BM_35_22
mdefine_line|#define BM_35_22 0x0000000fffc00000
DECL|macro|BM_22_35
mdefine_line|#define BM_22_35 BM_35_22
DECL|macro|BM_36_22
mdefine_line|#define BM_36_22 0x0000001fffc00000
DECL|macro|BM_22_36
mdefine_line|#define BM_22_36 BM_36_22
DECL|macro|BM_37_22
mdefine_line|#define BM_37_22 0x0000003fffc00000
DECL|macro|BM_22_37
mdefine_line|#define BM_22_37 BM_37_22
DECL|macro|BM_38_22
mdefine_line|#define BM_38_22 0x0000007fffc00000
DECL|macro|BM_22_38
mdefine_line|#define BM_22_38 BM_38_22
DECL|macro|BM_39_22
mdefine_line|#define BM_39_22 0x000000ffffc00000
DECL|macro|BM_22_39
mdefine_line|#define BM_22_39 BM_39_22
DECL|macro|BM_40_22
mdefine_line|#define BM_40_22 0x000001ffffc00000
DECL|macro|BM_22_40
mdefine_line|#define BM_22_40 BM_40_22
DECL|macro|BM_41_22
mdefine_line|#define BM_41_22 0x000003ffffc00000
DECL|macro|BM_22_41
mdefine_line|#define BM_22_41 BM_41_22
DECL|macro|BM_42_22
mdefine_line|#define BM_42_22 0x000007ffffc00000
DECL|macro|BM_22_42
mdefine_line|#define BM_22_42 BM_42_22
DECL|macro|BM_43_22
mdefine_line|#define BM_43_22 0x00000fffffc00000
DECL|macro|BM_22_43
mdefine_line|#define BM_22_43 BM_43_22
DECL|macro|BM_44_22
mdefine_line|#define BM_44_22 0x00001fffffc00000
DECL|macro|BM_22_44
mdefine_line|#define BM_22_44 BM_44_22
DECL|macro|BM_45_22
mdefine_line|#define BM_45_22 0x00003fffffc00000
DECL|macro|BM_22_45
mdefine_line|#define BM_22_45 BM_45_22
DECL|macro|BM_46_22
mdefine_line|#define BM_46_22 0x00007fffffc00000
DECL|macro|BM_22_46
mdefine_line|#define BM_22_46 BM_46_22
DECL|macro|BM_47_22
mdefine_line|#define BM_47_22 0x0000ffffffc00000
DECL|macro|BM_22_47
mdefine_line|#define BM_22_47 BM_47_22
DECL|macro|BM_48_22
mdefine_line|#define BM_48_22 0x0001ffffffc00000
DECL|macro|BM_22_48
mdefine_line|#define BM_22_48 BM_48_22
DECL|macro|BM_49_22
mdefine_line|#define BM_49_22 0x0003ffffffc00000
DECL|macro|BM_22_49
mdefine_line|#define BM_22_49 BM_49_22
DECL|macro|BM_50_22
mdefine_line|#define BM_50_22 0x0007ffffffc00000
DECL|macro|BM_22_50
mdefine_line|#define BM_22_50 BM_50_22
DECL|macro|BM_51_22
mdefine_line|#define BM_51_22 0x000fffffffc00000
DECL|macro|BM_22_51
mdefine_line|#define BM_22_51 BM_51_22
DECL|macro|BM_52_22
mdefine_line|#define BM_52_22 0x001fffffffc00000
DECL|macro|BM_22_52
mdefine_line|#define BM_22_52 BM_52_22
DECL|macro|BM_53_22
mdefine_line|#define BM_53_22 0x003fffffffc00000
DECL|macro|BM_22_53
mdefine_line|#define BM_22_53 BM_53_22
DECL|macro|BM_54_22
mdefine_line|#define BM_54_22 0x007fffffffc00000
DECL|macro|BM_22_54
mdefine_line|#define BM_22_54 BM_54_22
DECL|macro|BM_55_22
mdefine_line|#define BM_55_22 0x00ffffffffc00000
DECL|macro|BM_22_55
mdefine_line|#define BM_22_55 BM_55_22
DECL|macro|BM_56_22
mdefine_line|#define BM_56_22 0x01ffffffffc00000
DECL|macro|BM_22_56
mdefine_line|#define BM_22_56 BM_56_22
DECL|macro|BM_57_22
mdefine_line|#define BM_57_22 0x03ffffffffc00000
DECL|macro|BM_22_57
mdefine_line|#define BM_22_57 BM_57_22
DECL|macro|BM_58_22
mdefine_line|#define BM_58_22 0x07ffffffffc00000
DECL|macro|BM_22_58
mdefine_line|#define BM_22_58 BM_58_22
DECL|macro|BM_59_22
mdefine_line|#define BM_59_22 0x0fffffffffc00000
DECL|macro|BM_22_59
mdefine_line|#define BM_22_59 BM_59_22
DECL|macro|BM_60_22
mdefine_line|#define BM_60_22 0x1fffffffffc00000
DECL|macro|BM_22_60
mdefine_line|#define BM_22_60 BM_60_22
DECL|macro|BM_61_22
mdefine_line|#define BM_61_22 0x3fffffffffc00000
DECL|macro|BM_22_61
mdefine_line|#define BM_22_61 BM_61_22
DECL|macro|BM_62_22
mdefine_line|#define BM_62_22 0x7fffffffffc00000
DECL|macro|BM_22_62
mdefine_line|#define BM_22_62 BM_62_22
DECL|macro|BM_63_22
mdefine_line|#define BM_63_22 0xffffffffffc00000
DECL|macro|BM_22_63
mdefine_line|#define BM_22_63 BM_63_22
DECL|macro|BM_23_23
mdefine_line|#define BM_23_23 0x0000000000800000
DECL|macro|BM_24_23
mdefine_line|#define BM_24_23 0x0000000001800000
DECL|macro|BM_23_24
mdefine_line|#define BM_23_24 BM_24_23
DECL|macro|BM_25_23
mdefine_line|#define BM_25_23 0x0000000003800000
DECL|macro|BM_23_25
mdefine_line|#define BM_23_25 BM_25_23
DECL|macro|BM_26_23
mdefine_line|#define BM_26_23 0x0000000007800000
DECL|macro|BM_23_26
mdefine_line|#define BM_23_26 BM_26_23
DECL|macro|BM_27_23
mdefine_line|#define BM_27_23 0x000000000f800000
DECL|macro|BM_23_27
mdefine_line|#define BM_23_27 BM_27_23
DECL|macro|BM_28_23
mdefine_line|#define BM_28_23 0x000000001f800000
DECL|macro|BM_23_28
mdefine_line|#define BM_23_28 BM_28_23
DECL|macro|BM_29_23
mdefine_line|#define BM_29_23 0x000000003f800000
DECL|macro|BM_23_29
mdefine_line|#define BM_23_29 BM_29_23
DECL|macro|BM_30_23
mdefine_line|#define BM_30_23 0x000000007f800000
DECL|macro|BM_23_30
mdefine_line|#define BM_23_30 BM_30_23
DECL|macro|BM_31_23
mdefine_line|#define BM_31_23 0x00000000ff800000
DECL|macro|BM_23_31
mdefine_line|#define BM_23_31 BM_31_23
DECL|macro|BM_32_23
mdefine_line|#define BM_32_23 0x00000001ff800000
DECL|macro|BM_23_32
mdefine_line|#define BM_23_32 BM_32_23
DECL|macro|BM_33_23
mdefine_line|#define BM_33_23 0x00000003ff800000
DECL|macro|BM_23_33
mdefine_line|#define BM_23_33 BM_33_23
DECL|macro|BM_34_23
mdefine_line|#define BM_34_23 0x00000007ff800000
DECL|macro|BM_23_34
mdefine_line|#define BM_23_34 BM_34_23
DECL|macro|BM_35_23
mdefine_line|#define BM_35_23 0x0000000fff800000
DECL|macro|BM_23_35
mdefine_line|#define BM_23_35 BM_35_23
DECL|macro|BM_36_23
mdefine_line|#define BM_36_23 0x0000001fff800000
DECL|macro|BM_23_36
mdefine_line|#define BM_23_36 BM_36_23
DECL|macro|BM_37_23
mdefine_line|#define BM_37_23 0x0000003fff800000
DECL|macro|BM_23_37
mdefine_line|#define BM_23_37 BM_37_23
DECL|macro|BM_38_23
mdefine_line|#define BM_38_23 0x0000007fff800000
DECL|macro|BM_23_38
mdefine_line|#define BM_23_38 BM_38_23
DECL|macro|BM_39_23
mdefine_line|#define BM_39_23 0x000000ffff800000
DECL|macro|BM_23_39
mdefine_line|#define BM_23_39 BM_39_23
DECL|macro|BM_40_23
mdefine_line|#define BM_40_23 0x000001ffff800000
DECL|macro|BM_23_40
mdefine_line|#define BM_23_40 BM_40_23
DECL|macro|BM_41_23
mdefine_line|#define BM_41_23 0x000003ffff800000
DECL|macro|BM_23_41
mdefine_line|#define BM_23_41 BM_41_23
DECL|macro|BM_42_23
mdefine_line|#define BM_42_23 0x000007ffff800000
DECL|macro|BM_23_42
mdefine_line|#define BM_23_42 BM_42_23
DECL|macro|BM_43_23
mdefine_line|#define BM_43_23 0x00000fffff800000
DECL|macro|BM_23_43
mdefine_line|#define BM_23_43 BM_43_23
DECL|macro|BM_44_23
mdefine_line|#define BM_44_23 0x00001fffff800000
DECL|macro|BM_23_44
mdefine_line|#define BM_23_44 BM_44_23
DECL|macro|BM_45_23
mdefine_line|#define BM_45_23 0x00003fffff800000
DECL|macro|BM_23_45
mdefine_line|#define BM_23_45 BM_45_23
DECL|macro|BM_46_23
mdefine_line|#define BM_46_23 0x00007fffff800000
DECL|macro|BM_23_46
mdefine_line|#define BM_23_46 BM_46_23
DECL|macro|BM_47_23
mdefine_line|#define BM_47_23 0x0000ffffff800000
DECL|macro|BM_23_47
mdefine_line|#define BM_23_47 BM_47_23
DECL|macro|BM_48_23
mdefine_line|#define BM_48_23 0x0001ffffff800000
DECL|macro|BM_23_48
mdefine_line|#define BM_23_48 BM_48_23
DECL|macro|BM_49_23
mdefine_line|#define BM_49_23 0x0003ffffff800000
DECL|macro|BM_23_49
mdefine_line|#define BM_23_49 BM_49_23
DECL|macro|BM_50_23
mdefine_line|#define BM_50_23 0x0007ffffff800000
DECL|macro|BM_23_50
mdefine_line|#define BM_23_50 BM_50_23
DECL|macro|BM_51_23
mdefine_line|#define BM_51_23 0x000fffffff800000
DECL|macro|BM_23_51
mdefine_line|#define BM_23_51 BM_51_23
DECL|macro|BM_52_23
mdefine_line|#define BM_52_23 0x001fffffff800000
DECL|macro|BM_23_52
mdefine_line|#define BM_23_52 BM_52_23
DECL|macro|BM_53_23
mdefine_line|#define BM_53_23 0x003fffffff800000
DECL|macro|BM_23_53
mdefine_line|#define BM_23_53 BM_53_23
DECL|macro|BM_54_23
mdefine_line|#define BM_54_23 0x007fffffff800000
DECL|macro|BM_23_54
mdefine_line|#define BM_23_54 BM_54_23
DECL|macro|BM_55_23
mdefine_line|#define BM_55_23 0x00ffffffff800000
DECL|macro|BM_23_55
mdefine_line|#define BM_23_55 BM_55_23
DECL|macro|BM_56_23
mdefine_line|#define BM_56_23 0x01ffffffff800000
DECL|macro|BM_23_56
mdefine_line|#define BM_23_56 BM_56_23
DECL|macro|BM_57_23
mdefine_line|#define BM_57_23 0x03ffffffff800000
DECL|macro|BM_23_57
mdefine_line|#define BM_23_57 BM_57_23
DECL|macro|BM_58_23
mdefine_line|#define BM_58_23 0x07ffffffff800000
DECL|macro|BM_23_58
mdefine_line|#define BM_23_58 BM_58_23
DECL|macro|BM_59_23
mdefine_line|#define BM_59_23 0x0fffffffff800000
DECL|macro|BM_23_59
mdefine_line|#define BM_23_59 BM_59_23
DECL|macro|BM_60_23
mdefine_line|#define BM_60_23 0x1fffffffff800000
DECL|macro|BM_23_60
mdefine_line|#define BM_23_60 BM_60_23
DECL|macro|BM_61_23
mdefine_line|#define BM_61_23 0x3fffffffff800000
DECL|macro|BM_23_61
mdefine_line|#define BM_23_61 BM_61_23
DECL|macro|BM_62_23
mdefine_line|#define BM_62_23 0x7fffffffff800000
DECL|macro|BM_23_62
mdefine_line|#define BM_23_62 BM_62_23
DECL|macro|BM_63_23
mdefine_line|#define BM_63_23 0xffffffffff800000
DECL|macro|BM_23_63
mdefine_line|#define BM_23_63 BM_63_23
DECL|macro|BM_24_24
mdefine_line|#define BM_24_24 0x0000000001000000
DECL|macro|BM_25_24
mdefine_line|#define BM_25_24 0x0000000003000000
DECL|macro|BM_24_25
mdefine_line|#define BM_24_25 BM_25_24
DECL|macro|BM_26_24
mdefine_line|#define BM_26_24 0x0000000007000000
DECL|macro|BM_24_26
mdefine_line|#define BM_24_26 BM_26_24
DECL|macro|BM_27_24
mdefine_line|#define BM_27_24 0x000000000f000000
DECL|macro|BM_24_27
mdefine_line|#define BM_24_27 BM_27_24
DECL|macro|BM_28_24
mdefine_line|#define BM_28_24 0x000000001f000000
DECL|macro|BM_24_28
mdefine_line|#define BM_24_28 BM_28_24
DECL|macro|BM_29_24
mdefine_line|#define BM_29_24 0x000000003f000000
DECL|macro|BM_24_29
mdefine_line|#define BM_24_29 BM_29_24
DECL|macro|BM_30_24
mdefine_line|#define BM_30_24 0x000000007f000000
DECL|macro|BM_24_30
mdefine_line|#define BM_24_30 BM_30_24
DECL|macro|BM_31_24
mdefine_line|#define BM_31_24 0x00000000ff000000
DECL|macro|BM_24_31
mdefine_line|#define BM_24_31 BM_31_24
DECL|macro|BM_32_24
mdefine_line|#define BM_32_24 0x00000001ff000000
DECL|macro|BM_24_32
mdefine_line|#define BM_24_32 BM_32_24
DECL|macro|BM_33_24
mdefine_line|#define BM_33_24 0x00000003ff000000
DECL|macro|BM_24_33
mdefine_line|#define BM_24_33 BM_33_24
DECL|macro|BM_34_24
mdefine_line|#define BM_34_24 0x00000007ff000000
DECL|macro|BM_24_34
mdefine_line|#define BM_24_34 BM_34_24
DECL|macro|BM_35_24
mdefine_line|#define BM_35_24 0x0000000fff000000
DECL|macro|BM_24_35
mdefine_line|#define BM_24_35 BM_35_24
DECL|macro|BM_36_24
mdefine_line|#define BM_36_24 0x0000001fff000000
DECL|macro|BM_24_36
mdefine_line|#define BM_24_36 BM_36_24
DECL|macro|BM_37_24
mdefine_line|#define BM_37_24 0x0000003fff000000
DECL|macro|BM_24_37
mdefine_line|#define BM_24_37 BM_37_24
DECL|macro|BM_38_24
mdefine_line|#define BM_38_24 0x0000007fff000000
DECL|macro|BM_24_38
mdefine_line|#define BM_24_38 BM_38_24
DECL|macro|BM_39_24
mdefine_line|#define BM_39_24 0x000000ffff000000
DECL|macro|BM_24_39
mdefine_line|#define BM_24_39 BM_39_24
DECL|macro|BM_40_24
mdefine_line|#define BM_40_24 0x000001ffff000000
DECL|macro|BM_24_40
mdefine_line|#define BM_24_40 BM_40_24
DECL|macro|BM_41_24
mdefine_line|#define BM_41_24 0x000003ffff000000
DECL|macro|BM_24_41
mdefine_line|#define BM_24_41 BM_41_24
DECL|macro|BM_42_24
mdefine_line|#define BM_42_24 0x000007ffff000000
DECL|macro|BM_24_42
mdefine_line|#define BM_24_42 BM_42_24
DECL|macro|BM_43_24
mdefine_line|#define BM_43_24 0x00000fffff000000
DECL|macro|BM_24_43
mdefine_line|#define BM_24_43 BM_43_24
DECL|macro|BM_44_24
mdefine_line|#define BM_44_24 0x00001fffff000000
DECL|macro|BM_24_44
mdefine_line|#define BM_24_44 BM_44_24
DECL|macro|BM_45_24
mdefine_line|#define BM_45_24 0x00003fffff000000
DECL|macro|BM_24_45
mdefine_line|#define BM_24_45 BM_45_24
DECL|macro|BM_46_24
mdefine_line|#define BM_46_24 0x00007fffff000000
DECL|macro|BM_24_46
mdefine_line|#define BM_24_46 BM_46_24
DECL|macro|BM_47_24
mdefine_line|#define BM_47_24 0x0000ffffff000000
DECL|macro|BM_24_47
mdefine_line|#define BM_24_47 BM_47_24
DECL|macro|BM_48_24
mdefine_line|#define BM_48_24 0x0001ffffff000000
DECL|macro|BM_24_48
mdefine_line|#define BM_24_48 BM_48_24
DECL|macro|BM_49_24
mdefine_line|#define BM_49_24 0x0003ffffff000000
DECL|macro|BM_24_49
mdefine_line|#define BM_24_49 BM_49_24
DECL|macro|BM_50_24
mdefine_line|#define BM_50_24 0x0007ffffff000000
DECL|macro|BM_24_50
mdefine_line|#define BM_24_50 BM_50_24
DECL|macro|BM_51_24
mdefine_line|#define BM_51_24 0x000fffffff000000
DECL|macro|BM_24_51
mdefine_line|#define BM_24_51 BM_51_24
DECL|macro|BM_52_24
mdefine_line|#define BM_52_24 0x001fffffff000000
DECL|macro|BM_24_52
mdefine_line|#define BM_24_52 BM_52_24
DECL|macro|BM_53_24
mdefine_line|#define BM_53_24 0x003fffffff000000
DECL|macro|BM_24_53
mdefine_line|#define BM_24_53 BM_53_24
DECL|macro|BM_54_24
mdefine_line|#define BM_54_24 0x007fffffff000000
DECL|macro|BM_24_54
mdefine_line|#define BM_24_54 BM_54_24
DECL|macro|BM_55_24
mdefine_line|#define BM_55_24 0x00ffffffff000000
DECL|macro|BM_24_55
mdefine_line|#define BM_24_55 BM_55_24
DECL|macro|BM_56_24
mdefine_line|#define BM_56_24 0x01ffffffff000000
DECL|macro|BM_24_56
mdefine_line|#define BM_24_56 BM_56_24
DECL|macro|BM_57_24
mdefine_line|#define BM_57_24 0x03ffffffff000000
DECL|macro|BM_24_57
mdefine_line|#define BM_24_57 BM_57_24
DECL|macro|BM_58_24
mdefine_line|#define BM_58_24 0x07ffffffff000000
DECL|macro|BM_24_58
mdefine_line|#define BM_24_58 BM_58_24
DECL|macro|BM_59_24
mdefine_line|#define BM_59_24 0x0fffffffff000000
DECL|macro|BM_24_59
mdefine_line|#define BM_24_59 BM_59_24
DECL|macro|BM_60_24
mdefine_line|#define BM_60_24 0x1fffffffff000000
DECL|macro|BM_24_60
mdefine_line|#define BM_24_60 BM_60_24
DECL|macro|BM_61_24
mdefine_line|#define BM_61_24 0x3fffffffff000000
DECL|macro|BM_24_61
mdefine_line|#define BM_24_61 BM_61_24
DECL|macro|BM_62_24
mdefine_line|#define BM_62_24 0x7fffffffff000000
DECL|macro|BM_24_62
mdefine_line|#define BM_24_62 BM_62_24
DECL|macro|BM_63_24
mdefine_line|#define BM_63_24 0xffffffffff000000
DECL|macro|BM_24_63
mdefine_line|#define BM_24_63 BM_63_24
DECL|macro|BM_25_25
mdefine_line|#define BM_25_25 0x0000000002000000
DECL|macro|BM_26_25
mdefine_line|#define BM_26_25 0x0000000006000000
DECL|macro|BM_25_26
mdefine_line|#define BM_25_26 BM_26_25
DECL|macro|BM_27_25
mdefine_line|#define BM_27_25 0x000000000e000000
DECL|macro|BM_25_27
mdefine_line|#define BM_25_27 BM_27_25
DECL|macro|BM_28_25
mdefine_line|#define BM_28_25 0x000000001e000000
DECL|macro|BM_25_28
mdefine_line|#define BM_25_28 BM_28_25
DECL|macro|BM_29_25
mdefine_line|#define BM_29_25 0x000000003e000000
DECL|macro|BM_25_29
mdefine_line|#define BM_25_29 BM_29_25
DECL|macro|BM_30_25
mdefine_line|#define BM_30_25 0x000000007e000000
DECL|macro|BM_25_30
mdefine_line|#define BM_25_30 BM_30_25
DECL|macro|BM_31_25
mdefine_line|#define BM_31_25 0x00000000fe000000
DECL|macro|BM_25_31
mdefine_line|#define BM_25_31 BM_31_25
DECL|macro|BM_32_25
mdefine_line|#define BM_32_25 0x00000001fe000000
DECL|macro|BM_25_32
mdefine_line|#define BM_25_32 BM_32_25
DECL|macro|BM_33_25
mdefine_line|#define BM_33_25 0x00000003fe000000
DECL|macro|BM_25_33
mdefine_line|#define BM_25_33 BM_33_25
DECL|macro|BM_34_25
mdefine_line|#define BM_34_25 0x00000007fe000000
DECL|macro|BM_25_34
mdefine_line|#define BM_25_34 BM_34_25
DECL|macro|BM_35_25
mdefine_line|#define BM_35_25 0x0000000ffe000000
DECL|macro|BM_25_35
mdefine_line|#define BM_25_35 BM_35_25
DECL|macro|BM_36_25
mdefine_line|#define BM_36_25 0x0000001ffe000000
DECL|macro|BM_25_36
mdefine_line|#define BM_25_36 BM_36_25
DECL|macro|BM_37_25
mdefine_line|#define BM_37_25 0x0000003ffe000000
DECL|macro|BM_25_37
mdefine_line|#define BM_25_37 BM_37_25
DECL|macro|BM_38_25
mdefine_line|#define BM_38_25 0x0000007ffe000000
DECL|macro|BM_25_38
mdefine_line|#define BM_25_38 BM_38_25
DECL|macro|BM_39_25
mdefine_line|#define BM_39_25 0x000000fffe000000
DECL|macro|BM_25_39
mdefine_line|#define BM_25_39 BM_39_25
DECL|macro|BM_40_25
mdefine_line|#define BM_40_25 0x000001fffe000000
DECL|macro|BM_25_40
mdefine_line|#define BM_25_40 BM_40_25
DECL|macro|BM_41_25
mdefine_line|#define BM_41_25 0x000003fffe000000
DECL|macro|BM_25_41
mdefine_line|#define BM_25_41 BM_41_25
DECL|macro|BM_42_25
mdefine_line|#define BM_42_25 0x000007fffe000000
DECL|macro|BM_25_42
mdefine_line|#define BM_25_42 BM_42_25
DECL|macro|BM_43_25
mdefine_line|#define BM_43_25 0x00000ffffe000000
DECL|macro|BM_25_43
mdefine_line|#define BM_25_43 BM_43_25
DECL|macro|BM_44_25
mdefine_line|#define BM_44_25 0x00001ffffe000000
DECL|macro|BM_25_44
mdefine_line|#define BM_25_44 BM_44_25
DECL|macro|BM_45_25
mdefine_line|#define BM_45_25 0x00003ffffe000000
DECL|macro|BM_25_45
mdefine_line|#define BM_25_45 BM_45_25
DECL|macro|BM_46_25
mdefine_line|#define BM_46_25 0x00007ffffe000000
DECL|macro|BM_25_46
mdefine_line|#define BM_25_46 BM_46_25
DECL|macro|BM_47_25
mdefine_line|#define BM_47_25 0x0000fffffe000000
DECL|macro|BM_25_47
mdefine_line|#define BM_25_47 BM_47_25
DECL|macro|BM_48_25
mdefine_line|#define BM_48_25 0x0001fffffe000000
DECL|macro|BM_25_48
mdefine_line|#define BM_25_48 BM_48_25
DECL|macro|BM_49_25
mdefine_line|#define BM_49_25 0x0003fffffe000000
DECL|macro|BM_25_49
mdefine_line|#define BM_25_49 BM_49_25
DECL|macro|BM_50_25
mdefine_line|#define BM_50_25 0x0007fffffe000000
DECL|macro|BM_25_50
mdefine_line|#define BM_25_50 BM_50_25
DECL|macro|BM_51_25
mdefine_line|#define BM_51_25 0x000ffffffe000000
DECL|macro|BM_25_51
mdefine_line|#define BM_25_51 BM_51_25
DECL|macro|BM_52_25
mdefine_line|#define BM_52_25 0x001ffffffe000000
DECL|macro|BM_25_52
mdefine_line|#define BM_25_52 BM_52_25
DECL|macro|BM_53_25
mdefine_line|#define BM_53_25 0x003ffffffe000000
DECL|macro|BM_25_53
mdefine_line|#define BM_25_53 BM_53_25
DECL|macro|BM_54_25
mdefine_line|#define BM_54_25 0x007ffffffe000000
DECL|macro|BM_25_54
mdefine_line|#define BM_25_54 BM_54_25
DECL|macro|BM_55_25
mdefine_line|#define BM_55_25 0x00fffffffe000000
DECL|macro|BM_25_55
mdefine_line|#define BM_25_55 BM_55_25
DECL|macro|BM_56_25
mdefine_line|#define BM_56_25 0x01fffffffe000000
DECL|macro|BM_25_56
mdefine_line|#define BM_25_56 BM_56_25
DECL|macro|BM_57_25
mdefine_line|#define BM_57_25 0x03fffffffe000000
DECL|macro|BM_25_57
mdefine_line|#define BM_25_57 BM_57_25
DECL|macro|BM_58_25
mdefine_line|#define BM_58_25 0x07fffffffe000000
DECL|macro|BM_25_58
mdefine_line|#define BM_25_58 BM_58_25
DECL|macro|BM_59_25
mdefine_line|#define BM_59_25 0x0ffffffffe000000
DECL|macro|BM_25_59
mdefine_line|#define BM_25_59 BM_59_25
DECL|macro|BM_60_25
mdefine_line|#define BM_60_25 0x1ffffffffe000000
DECL|macro|BM_25_60
mdefine_line|#define BM_25_60 BM_60_25
DECL|macro|BM_61_25
mdefine_line|#define BM_61_25 0x3ffffffffe000000
DECL|macro|BM_25_61
mdefine_line|#define BM_25_61 BM_61_25
DECL|macro|BM_62_25
mdefine_line|#define BM_62_25 0x7ffffffffe000000
DECL|macro|BM_25_62
mdefine_line|#define BM_25_62 BM_62_25
DECL|macro|BM_63_25
mdefine_line|#define BM_63_25 0xfffffffffe000000
DECL|macro|BM_25_63
mdefine_line|#define BM_25_63 BM_63_25
DECL|macro|BM_26_26
mdefine_line|#define BM_26_26 0x0000000004000000
DECL|macro|BM_27_26
mdefine_line|#define BM_27_26 0x000000000c000000
DECL|macro|BM_26_27
mdefine_line|#define BM_26_27 BM_27_26
DECL|macro|BM_28_26
mdefine_line|#define BM_28_26 0x000000001c000000
DECL|macro|BM_26_28
mdefine_line|#define BM_26_28 BM_28_26
DECL|macro|BM_29_26
mdefine_line|#define BM_29_26 0x000000003c000000
DECL|macro|BM_26_29
mdefine_line|#define BM_26_29 BM_29_26
DECL|macro|BM_30_26
mdefine_line|#define BM_30_26 0x000000007c000000
DECL|macro|BM_26_30
mdefine_line|#define BM_26_30 BM_30_26
DECL|macro|BM_31_26
mdefine_line|#define BM_31_26 0x00000000fc000000
DECL|macro|BM_26_31
mdefine_line|#define BM_26_31 BM_31_26
DECL|macro|BM_32_26
mdefine_line|#define BM_32_26 0x00000001fc000000
DECL|macro|BM_26_32
mdefine_line|#define BM_26_32 BM_32_26
DECL|macro|BM_33_26
mdefine_line|#define BM_33_26 0x00000003fc000000
DECL|macro|BM_26_33
mdefine_line|#define BM_26_33 BM_33_26
DECL|macro|BM_34_26
mdefine_line|#define BM_34_26 0x00000007fc000000
DECL|macro|BM_26_34
mdefine_line|#define BM_26_34 BM_34_26
DECL|macro|BM_35_26
mdefine_line|#define BM_35_26 0x0000000ffc000000
DECL|macro|BM_26_35
mdefine_line|#define BM_26_35 BM_35_26
DECL|macro|BM_36_26
mdefine_line|#define BM_36_26 0x0000001ffc000000
DECL|macro|BM_26_36
mdefine_line|#define BM_26_36 BM_36_26
DECL|macro|BM_37_26
mdefine_line|#define BM_37_26 0x0000003ffc000000
DECL|macro|BM_26_37
mdefine_line|#define BM_26_37 BM_37_26
DECL|macro|BM_38_26
mdefine_line|#define BM_38_26 0x0000007ffc000000
DECL|macro|BM_26_38
mdefine_line|#define BM_26_38 BM_38_26
DECL|macro|BM_39_26
mdefine_line|#define BM_39_26 0x000000fffc000000
DECL|macro|BM_26_39
mdefine_line|#define BM_26_39 BM_39_26
DECL|macro|BM_40_26
mdefine_line|#define BM_40_26 0x000001fffc000000
DECL|macro|BM_26_40
mdefine_line|#define BM_26_40 BM_40_26
DECL|macro|BM_41_26
mdefine_line|#define BM_41_26 0x000003fffc000000
DECL|macro|BM_26_41
mdefine_line|#define BM_26_41 BM_41_26
DECL|macro|BM_42_26
mdefine_line|#define BM_42_26 0x000007fffc000000
DECL|macro|BM_26_42
mdefine_line|#define BM_26_42 BM_42_26
DECL|macro|BM_43_26
mdefine_line|#define BM_43_26 0x00000ffffc000000
DECL|macro|BM_26_43
mdefine_line|#define BM_26_43 BM_43_26
DECL|macro|BM_44_26
mdefine_line|#define BM_44_26 0x00001ffffc000000
DECL|macro|BM_26_44
mdefine_line|#define BM_26_44 BM_44_26
DECL|macro|BM_45_26
mdefine_line|#define BM_45_26 0x00003ffffc000000
DECL|macro|BM_26_45
mdefine_line|#define BM_26_45 BM_45_26
DECL|macro|BM_46_26
mdefine_line|#define BM_46_26 0x00007ffffc000000
DECL|macro|BM_26_46
mdefine_line|#define BM_26_46 BM_46_26
DECL|macro|BM_47_26
mdefine_line|#define BM_47_26 0x0000fffffc000000
DECL|macro|BM_26_47
mdefine_line|#define BM_26_47 BM_47_26
DECL|macro|BM_48_26
mdefine_line|#define BM_48_26 0x0001fffffc000000
DECL|macro|BM_26_48
mdefine_line|#define BM_26_48 BM_48_26
DECL|macro|BM_49_26
mdefine_line|#define BM_49_26 0x0003fffffc000000
DECL|macro|BM_26_49
mdefine_line|#define BM_26_49 BM_49_26
DECL|macro|BM_50_26
mdefine_line|#define BM_50_26 0x0007fffffc000000
DECL|macro|BM_26_50
mdefine_line|#define BM_26_50 BM_50_26
DECL|macro|BM_51_26
mdefine_line|#define BM_51_26 0x000ffffffc000000
DECL|macro|BM_26_51
mdefine_line|#define BM_26_51 BM_51_26
DECL|macro|BM_52_26
mdefine_line|#define BM_52_26 0x001ffffffc000000
DECL|macro|BM_26_52
mdefine_line|#define BM_26_52 BM_52_26
DECL|macro|BM_53_26
mdefine_line|#define BM_53_26 0x003ffffffc000000
DECL|macro|BM_26_53
mdefine_line|#define BM_26_53 BM_53_26
DECL|macro|BM_54_26
mdefine_line|#define BM_54_26 0x007ffffffc000000
DECL|macro|BM_26_54
mdefine_line|#define BM_26_54 BM_54_26
DECL|macro|BM_55_26
mdefine_line|#define BM_55_26 0x00fffffffc000000
DECL|macro|BM_26_55
mdefine_line|#define BM_26_55 BM_55_26
DECL|macro|BM_56_26
mdefine_line|#define BM_56_26 0x01fffffffc000000
DECL|macro|BM_26_56
mdefine_line|#define BM_26_56 BM_56_26
DECL|macro|BM_57_26
mdefine_line|#define BM_57_26 0x03fffffffc000000
DECL|macro|BM_26_57
mdefine_line|#define BM_26_57 BM_57_26
DECL|macro|BM_58_26
mdefine_line|#define BM_58_26 0x07fffffffc000000
DECL|macro|BM_26_58
mdefine_line|#define BM_26_58 BM_58_26
DECL|macro|BM_59_26
mdefine_line|#define BM_59_26 0x0ffffffffc000000
DECL|macro|BM_26_59
mdefine_line|#define BM_26_59 BM_59_26
DECL|macro|BM_60_26
mdefine_line|#define BM_60_26 0x1ffffffffc000000
DECL|macro|BM_26_60
mdefine_line|#define BM_26_60 BM_60_26
DECL|macro|BM_61_26
mdefine_line|#define BM_61_26 0x3ffffffffc000000
DECL|macro|BM_26_61
mdefine_line|#define BM_26_61 BM_61_26
DECL|macro|BM_62_26
mdefine_line|#define BM_62_26 0x7ffffffffc000000
DECL|macro|BM_26_62
mdefine_line|#define BM_26_62 BM_62_26
DECL|macro|BM_63_26
mdefine_line|#define BM_63_26 0xfffffffffc000000
DECL|macro|BM_26_63
mdefine_line|#define BM_26_63 BM_63_26
DECL|macro|BM_27_27
mdefine_line|#define BM_27_27 0x0000000008000000
DECL|macro|BM_28_27
mdefine_line|#define BM_28_27 0x0000000018000000
DECL|macro|BM_27_28
mdefine_line|#define BM_27_28 BM_28_27
DECL|macro|BM_29_27
mdefine_line|#define BM_29_27 0x0000000038000000
DECL|macro|BM_27_29
mdefine_line|#define BM_27_29 BM_29_27
DECL|macro|BM_30_27
mdefine_line|#define BM_30_27 0x0000000078000000
DECL|macro|BM_27_30
mdefine_line|#define BM_27_30 BM_30_27
DECL|macro|BM_31_27
mdefine_line|#define BM_31_27 0x00000000f8000000
DECL|macro|BM_27_31
mdefine_line|#define BM_27_31 BM_31_27
DECL|macro|BM_32_27
mdefine_line|#define BM_32_27 0x00000001f8000000
DECL|macro|BM_27_32
mdefine_line|#define BM_27_32 BM_32_27
DECL|macro|BM_33_27
mdefine_line|#define BM_33_27 0x00000003f8000000
DECL|macro|BM_27_33
mdefine_line|#define BM_27_33 BM_33_27
DECL|macro|BM_34_27
mdefine_line|#define BM_34_27 0x00000007f8000000
DECL|macro|BM_27_34
mdefine_line|#define BM_27_34 BM_34_27
DECL|macro|BM_35_27
mdefine_line|#define BM_35_27 0x0000000ff8000000
DECL|macro|BM_27_35
mdefine_line|#define BM_27_35 BM_35_27
DECL|macro|BM_36_27
mdefine_line|#define BM_36_27 0x0000001ff8000000
DECL|macro|BM_27_36
mdefine_line|#define BM_27_36 BM_36_27
DECL|macro|BM_37_27
mdefine_line|#define BM_37_27 0x0000003ff8000000
DECL|macro|BM_27_37
mdefine_line|#define BM_27_37 BM_37_27
DECL|macro|BM_38_27
mdefine_line|#define BM_38_27 0x0000007ff8000000
DECL|macro|BM_27_38
mdefine_line|#define BM_27_38 BM_38_27
DECL|macro|BM_39_27
mdefine_line|#define BM_39_27 0x000000fff8000000
DECL|macro|BM_27_39
mdefine_line|#define BM_27_39 BM_39_27
DECL|macro|BM_40_27
mdefine_line|#define BM_40_27 0x000001fff8000000
DECL|macro|BM_27_40
mdefine_line|#define BM_27_40 BM_40_27
DECL|macro|BM_41_27
mdefine_line|#define BM_41_27 0x000003fff8000000
DECL|macro|BM_27_41
mdefine_line|#define BM_27_41 BM_41_27
DECL|macro|BM_42_27
mdefine_line|#define BM_42_27 0x000007fff8000000
DECL|macro|BM_27_42
mdefine_line|#define BM_27_42 BM_42_27
DECL|macro|BM_43_27
mdefine_line|#define BM_43_27 0x00000ffff8000000
DECL|macro|BM_27_43
mdefine_line|#define BM_27_43 BM_43_27
DECL|macro|BM_44_27
mdefine_line|#define BM_44_27 0x00001ffff8000000
DECL|macro|BM_27_44
mdefine_line|#define BM_27_44 BM_44_27
DECL|macro|BM_45_27
mdefine_line|#define BM_45_27 0x00003ffff8000000
DECL|macro|BM_27_45
mdefine_line|#define BM_27_45 BM_45_27
DECL|macro|BM_46_27
mdefine_line|#define BM_46_27 0x00007ffff8000000
DECL|macro|BM_27_46
mdefine_line|#define BM_27_46 BM_46_27
DECL|macro|BM_47_27
mdefine_line|#define BM_47_27 0x0000fffff8000000
DECL|macro|BM_27_47
mdefine_line|#define BM_27_47 BM_47_27
DECL|macro|BM_48_27
mdefine_line|#define BM_48_27 0x0001fffff8000000
DECL|macro|BM_27_48
mdefine_line|#define BM_27_48 BM_48_27
DECL|macro|BM_49_27
mdefine_line|#define BM_49_27 0x0003fffff8000000
DECL|macro|BM_27_49
mdefine_line|#define BM_27_49 BM_49_27
DECL|macro|BM_50_27
mdefine_line|#define BM_50_27 0x0007fffff8000000
DECL|macro|BM_27_50
mdefine_line|#define BM_27_50 BM_50_27
DECL|macro|BM_51_27
mdefine_line|#define BM_51_27 0x000ffffff8000000
DECL|macro|BM_27_51
mdefine_line|#define BM_27_51 BM_51_27
DECL|macro|BM_52_27
mdefine_line|#define BM_52_27 0x001ffffff8000000
DECL|macro|BM_27_52
mdefine_line|#define BM_27_52 BM_52_27
DECL|macro|BM_53_27
mdefine_line|#define BM_53_27 0x003ffffff8000000
DECL|macro|BM_27_53
mdefine_line|#define BM_27_53 BM_53_27
DECL|macro|BM_54_27
mdefine_line|#define BM_54_27 0x007ffffff8000000
DECL|macro|BM_27_54
mdefine_line|#define BM_27_54 BM_54_27
DECL|macro|BM_55_27
mdefine_line|#define BM_55_27 0x00fffffff8000000
DECL|macro|BM_27_55
mdefine_line|#define BM_27_55 BM_55_27
DECL|macro|BM_56_27
mdefine_line|#define BM_56_27 0x01fffffff8000000
DECL|macro|BM_27_56
mdefine_line|#define BM_27_56 BM_56_27
DECL|macro|BM_57_27
mdefine_line|#define BM_57_27 0x03fffffff8000000
DECL|macro|BM_27_57
mdefine_line|#define BM_27_57 BM_57_27
DECL|macro|BM_58_27
mdefine_line|#define BM_58_27 0x07fffffff8000000
DECL|macro|BM_27_58
mdefine_line|#define BM_27_58 BM_58_27
DECL|macro|BM_59_27
mdefine_line|#define BM_59_27 0x0ffffffff8000000
DECL|macro|BM_27_59
mdefine_line|#define BM_27_59 BM_59_27
DECL|macro|BM_60_27
mdefine_line|#define BM_60_27 0x1ffffffff8000000
DECL|macro|BM_27_60
mdefine_line|#define BM_27_60 BM_60_27
DECL|macro|BM_61_27
mdefine_line|#define BM_61_27 0x3ffffffff8000000
DECL|macro|BM_27_61
mdefine_line|#define BM_27_61 BM_61_27
DECL|macro|BM_62_27
mdefine_line|#define BM_62_27 0x7ffffffff8000000
DECL|macro|BM_27_62
mdefine_line|#define BM_27_62 BM_62_27
DECL|macro|BM_63_27
mdefine_line|#define BM_63_27 0xfffffffff8000000
DECL|macro|BM_27_63
mdefine_line|#define BM_27_63 BM_63_27
DECL|macro|BM_28_28
mdefine_line|#define BM_28_28 0x0000000010000000
DECL|macro|BM_29_28
mdefine_line|#define BM_29_28 0x0000000030000000
DECL|macro|BM_28_29
mdefine_line|#define BM_28_29 BM_29_28
DECL|macro|BM_30_28
mdefine_line|#define BM_30_28 0x0000000070000000
DECL|macro|BM_28_30
mdefine_line|#define BM_28_30 BM_30_28
DECL|macro|BM_31_28
mdefine_line|#define BM_31_28 0x00000000f0000000
DECL|macro|BM_28_31
mdefine_line|#define BM_28_31 BM_31_28
DECL|macro|BM_32_28
mdefine_line|#define BM_32_28 0x00000001f0000000
DECL|macro|BM_28_32
mdefine_line|#define BM_28_32 BM_32_28
DECL|macro|BM_33_28
mdefine_line|#define BM_33_28 0x00000003f0000000
DECL|macro|BM_28_33
mdefine_line|#define BM_28_33 BM_33_28
DECL|macro|BM_34_28
mdefine_line|#define BM_34_28 0x00000007f0000000
DECL|macro|BM_28_34
mdefine_line|#define BM_28_34 BM_34_28
DECL|macro|BM_35_28
mdefine_line|#define BM_35_28 0x0000000ff0000000
DECL|macro|BM_28_35
mdefine_line|#define BM_28_35 BM_35_28
DECL|macro|BM_36_28
mdefine_line|#define BM_36_28 0x0000001ff0000000
DECL|macro|BM_28_36
mdefine_line|#define BM_28_36 BM_36_28
DECL|macro|BM_37_28
mdefine_line|#define BM_37_28 0x0000003ff0000000
DECL|macro|BM_28_37
mdefine_line|#define BM_28_37 BM_37_28
DECL|macro|BM_38_28
mdefine_line|#define BM_38_28 0x0000007ff0000000
DECL|macro|BM_28_38
mdefine_line|#define BM_28_38 BM_38_28
DECL|macro|BM_39_28
mdefine_line|#define BM_39_28 0x000000fff0000000
DECL|macro|BM_28_39
mdefine_line|#define BM_28_39 BM_39_28
DECL|macro|BM_40_28
mdefine_line|#define BM_40_28 0x000001fff0000000
DECL|macro|BM_28_40
mdefine_line|#define BM_28_40 BM_40_28
DECL|macro|BM_41_28
mdefine_line|#define BM_41_28 0x000003fff0000000
DECL|macro|BM_28_41
mdefine_line|#define BM_28_41 BM_41_28
DECL|macro|BM_42_28
mdefine_line|#define BM_42_28 0x000007fff0000000
DECL|macro|BM_28_42
mdefine_line|#define BM_28_42 BM_42_28
DECL|macro|BM_43_28
mdefine_line|#define BM_43_28 0x00000ffff0000000
DECL|macro|BM_28_43
mdefine_line|#define BM_28_43 BM_43_28
DECL|macro|BM_44_28
mdefine_line|#define BM_44_28 0x00001ffff0000000
DECL|macro|BM_28_44
mdefine_line|#define BM_28_44 BM_44_28
DECL|macro|BM_45_28
mdefine_line|#define BM_45_28 0x00003ffff0000000
DECL|macro|BM_28_45
mdefine_line|#define BM_28_45 BM_45_28
DECL|macro|BM_46_28
mdefine_line|#define BM_46_28 0x00007ffff0000000
DECL|macro|BM_28_46
mdefine_line|#define BM_28_46 BM_46_28
DECL|macro|BM_47_28
mdefine_line|#define BM_47_28 0x0000fffff0000000
DECL|macro|BM_28_47
mdefine_line|#define BM_28_47 BM_47_28
DECL|macro|BM_48_28
mdefine_line|#define BM_48_28 0x0001fffff0000000
DECL|macro|BM_28_48
mdefine_line|#define BM_28_48 BM_48_28
DECL|macro|BM_49_28
mdefine_line|#define BM_49_28 0x0003fffff0000000
DECL|macro|BM_28_49
mdefine_line|#define BM_28_49 BM_49_28
DECL|macro|BM_50_28
mdefine_line|#define BM_50_28 0x0007fffff0000000
DECL|macro|BM_28_50
mdefine_line|#define BM_28_50 BM_50_28
DECL|macro|BM_51_28
mdefine_line|#define BM_51_28 0x000ffffff0000000
DECL|macro|BM_28_51
mdefine_line|#define BM_28_51 BM_51_28
DECL|macro|BM_52_28
mdefine_line|#define BM_52_28 0x001ffffff0000000
DECL|macro|BM_28_52
mdefine_line|#define BM_28_52 BM_52_28
DECL|macro|BM_53_28
mdefine_line|#define BM_53_28 0x003ffffff0000000
DECL|macro|BM_28_53
mdefine_line|#define BM_28_53 BM_53_28
DECL|macro|BM_54_28
mdefine_line|#define BM_54_28 0x007ffffff0000000
DECL|macro|BM_28_54
mdefine_line|#define BM_28_54 BM_54_28
DECL|macro|BM_55_28
mdefine_line|#define BM_55_28 0x00fffffff0000000
DECL|macro|BM_28_55
mdefine_line|#define BM_28_55 BM_55_28
DECL|macro|BM_56_28
mdefine_line|#define BM_56_28 0x01fffffff0000000
DECL|macro|BM_28_56
mdefine_line|#define BM_28_56 BM_56_28
DECL|macro|BM_57_28
mdefine_line|#define BM_57_28 0x03fffffff0000000
DECL|macro|BM_28_57
mdefine_line|#define BM_28_57 BM_57_28
DECL|macro|BM_58_28
mdefine_line|#define BM_58_28 0x07fffffff0000000
DECL|macro|BM_28_58
mdefine_line|#define BM_28_58 BM_58_28
DECL|macro|BM_59_28
mdefine_line|#define BM_59_28 0x0ffffffff0000000
DECL|macro|BM_28_59
mdefine_line|#define BM_28_59 BM_59_28
DECL|macro|BM_60_28
mdefine_line|#define BM_60_28 0x1ffffffff0000000
DECL|macro|BM_28_60
mdefine_line|#define BM_28_60 BM_60_28
DECL|macro|BM_61_28
mdefine_line|#define BM_61_28 0x3ffffffff0000000
DECL|macro|BM_28_61
mdefine_line|#define BM_28_61 BM_61_28
DECL|macro|BM_62_28
mdefine_line|#define BM_62_28 0x7ffffffff0000000
DECL|macro|BM_28_62
mdefine_line|#define BM_28_62 BM_62_28
DECL|macro|BM_63_28
mdefine_line|#define BM_63_28 0xfffffffff0000000
DECL|macro|BM_28_63
mdefine_line|#define BM_28_63 BM_63_28
DECL|macro|BM_29_29
mdefine_line|#define BM_29_29 0x0000000020000000
DECL|macro|BM_30_29
mdefine_line|#define BM_30_29 0x0000000060000000
DECL|macro|BM_29_30
mdefine_line|#define BM_29_30 BM_30_29
DECL|macro|BM_31_29
mdefine_line|#define BM_31_29 0x00000000e0000000
DECL|macro|BM_29_31
mdefine_line|#define BM_29_31 BM_31_29
DECL|macro|BM_32_29
mdefine_line|#define BM_32_29 0x00000001e0000000
DECL|macro|BM_29_32
mdefine_line|#define BM_29_32 BM_32_29
DECL|macro|BM_33_29
mdefine_line|#define BM_33_29 0x00000003e0000000
DECL|macro|BM_29_33
mdefine_line|#define BM_29_33 BM_33_29
DECL|macro|BM_34_29
mdefine_line|#define BM_34_29 0x00000007e0000000
DECL|macro|BM_29_34
mdefine_line|#define BM_29_34 BM_34_29
DECL|macro|BM_35_29
mdefine_line|#define BM_35_29 0x0000000fe0000000
DECL|macro|BM_29_35
mdefine_line|#define BM_29_35 BM_35_29
DECL|macro|BM_36_29
mdefine_line|#define BM_36_29 0x0000001fe0000000
DECL|macro|BM_29_36
mdefine_line|#define BM_29_36 BM_36_29
DECL|macro|BM_37_29
mdefine_line|#define BM_37_29 0x0000003fe0000000
DECL|macro|BM_29_37
mdefine_line|#define BM_29_37 BM_37_29
DECL|macro|BM_38_29
mdefine_line|#define BM_38_29 0x0000007fe0000000
DECL|macro|BM_29_38
mdefine_line|#define BM_29_38 BM_38_29
DECL|macro|BM_39_29
mdefine_line|#define BM_39_29 0x000000ffe0000000
DECL|macro|BM_29_39
mdefine_line|#define BM_29_39 BM_39_29
DECL|macro|BM_40_29
mdefine_line|#define BM_40_29 0x000001ffe0000000
DECL|macro|BM_29_40
mdefine_line|#define BM_29_40 BM_40_29
DECL|macro|BM_41_29
mdefine_line|#define BM_41_29 0x000003ffe0000000
DECL|macro|BM_29_41
mdefine_line|#define BM_29_41 BM_41_29
DECL|macro|BM_42_29
mdefine_line|#define BM_42_29 0x000007ffe0000000
DECL|macro|BM_29_42
mdefine_line|#define BM_29_42 BM_42_29
DECL|macro|BM_43_29
mdefine_line|#define BM_43_29 0x00000fffe0000000
DECL|macro|BM_29_43
mdefine_line|#define BM_29_43 BM_43_29
DECL|macro|BM_44_29
mdefine_line|#define BM_44_29 0x00001fffe0000000
DECL|macro|BM_29_44
mdefine_line|#define BM_29_44 BM_44_29
DECL|macro|BM_45_29
mdefine_line|#define BM_45_29 0x00003fffe0000000
DECL|macro|BM_29_45
mdefine_line|#define BM_29_45 BM_45_29
DECL|macro|BM_46_29
mdefine_line|#define BM_46_29 0x00007fffe0000000
DECL|macro|BM_29_46
mdefine_line|#define BM_29_46 BM_46_29
DECL|macro|BM_47_29
mdefine_line|#define BM_47_29 0x0000ffffe0000000
DECL|macro|BM_29_47
mdefine_line|#define BM_29_47 BM_47_29
DECL|macro|BM_48_29
mdefine_line|#define BM_48_29 0x0001ffffe0000000
DECL|macro|BM_29_48
mdefine_line|#define BM_29_48 BM_48_29
DECL|macro|BM_49_29
mdefine_line|#define BM_49_29 0x0003ffffe0000000
DECL|macro|BM_29_49
mdefine_line|#define BM_29_49 BM_49_29
DECL|macro|BM_50_29
mdefine_line|#define BM_50_29 0x0007ffffe0000000
DECL|macro|BM_29_50
mdefine_line|#define BM_29_50 BM_50_29
DECL|macro|BM_51_29
mdefine_line|#define BM_51_29 0x000fffffe0000000
DECL|macro|BM_29_51
mdefine_line|#define BM_29_51 BM_51_29
DECL|macro|BM_52_29
mdefine_line|#define BM_52_29 0x001fffffe0000000
DECL|macro|BM_29_52
mdefine_line|#define BM_29_52 BM_52_29
DECL|macro|BM_53_29
mdefine_line|#define BM_53_29 0x003fffffe0000000
DECL|macro|BM_29_53
mdefine_line|#define BM_29_53 BM_53_29
DECL|macro|BM_54_29
mdefine_line|#define BM_54_29 0x007fffffe0000000
DECL|macro|BM_29_54
mdefine_line|#define BM_29_54 BM_54_29
DECL|macro|BM_55_29
mdefine_line|#define BM_55_29 0x00ffffffe0000000
DECL|macro|BM_29_55
mdefine_line|#define BM_29_55 BM_55_29
DECL|macro|BM_56_29
mdefine_line|#define BM_56_29 0x01ffffffe0000000
DECL|macro|BM_29_56
mdefine_line|#define BM_29_56 BM_56_29
DECL|macro|BM_57_29
mdefine_line|#define BM_57_29 0x03ffffffe0000000
DECL|macro|BM_29_57
mdefine_line|#define BM_29_57 BM_57_29
DECL|macro|BM_58_29
mdefine_line|#define BM_58_29 0x07ffffffe0000000
DECL|macro|BM_29_58
mdefine_line|#define BM_29_58 BM_58_29
DECL|macro|BM_59_29
mdefine_line|#define BM_59_29 0x0fffffffe0000000
DECL|macro|BM_29_59
mdefine_line|#define BM_29_59 BM_59_29
DECL|macro|BM_60_29
mdefine_line|#define BM_60_29 0x1fffffffe0000000
DECL|macro|BM_29_60
mdefine_line|#define BM_29_60 BM_60_29
DECL|macro|BM_61_29
mdefine_line|#define BM_61_29 0x3fffffffe0000000
DECL|macro|BM_29_61
mdefine_line|#define BM_29_61 BM_61_29
DECL|macro|BM_62_29
mdefine_line|#define BM_62_29 0x7fffffffe0000000
DECL|macro|BM_29_62
mdefine_line|#define BM_29_62 BM_62_29
DECL|macro|BM_63_29
mdefine_line|#define BM_63_29 0xffffffffe0000000
DECL|macro|BM_29_63
mdefine_line|#define BM_29_63 BM_63_29
DECL|macro|BM_30_30
mdefine_line|#define BM_30_30 0x0000000040000000
DECL|macro|BM_31_30
mdefine_line|#define BM_31_30 0x00000000c0000000
DECL|macro|BM_30_31
mdefine_line|#define BM_30_31 BM_31_30
DECL|macro|BM_32_30
mdefine_line|#define BM_32_30 0x00000001c0000000
DECL|macro|BM_30_32
mdefine_line|#define BM_30_32 BM_32_30
DECL|macro|BM_33_30
mdefine_line|#define BM_33_30 0x00000003c0000000
DECL|macro|BM_30_33
mdefine_line|#define BM_30_33 BM_33_30
DECL|macro|BM_34_30
mdefine_line|#define BM_34_30 0x00000007c0000000
DECL|macro|BM_30_34
mdefine_line|#define BM_30_34 BM_34_30
DECL|macro|BM_35_30
mdefine_line|#define BM_35_30 0x0000000fc0000000
DECL|macro|BM_30_35
mdefine_line|#define BM_30_35 BM_35_30
DECL|macro|BM_36_30
mdefine_line|#define BM_36_30 0x0000001fc0000000
DECL|macro|BM_30_36
mdefine_line|#define BM_30_36 BM_36_30
DECL|macro|BM_37_30
mdefine_line|#define BM_37_30 0x0000003fc0000000
DECL|macro|BM_30_37
mdefine_line|#define BM_30_37 BM_37_30
DECL|macro|BM_38_30
mdefine_line|#define BM_38_30 0x0000007fc0000000
DECL|macro|BM_30_38
mdefine_line|#define BM_30_38 BM_38_30
DECL|macro|BM_39_30
mdefine_line|#define BM_39_30 0x000000ffc0000000
DECL|macro|BM_30_39
mdefine_line|#define BM_30_39 BM_39_30
DECL|macro|BM_40_30
mdefine_line|#define BM_40_30 0x000001ffc0000000
DECL|macro|BM_30_40
mdefine_line|#define BM_30_40 BM_40_30
DECL|macro|BM_41_30
mdefine_line|#define BM_41_30 0x000003ffc0000000
DECL|macro|BM_30_41
mdefine_line|#define BM_30_41 BM_41_30
DECL|macro|BM_42_30
mdefine_line|#define BM_42_30 0x000007ffc0000000
DECL|macro|BM_30_42
mdefine_line|#define BM_30_42 BM_42_30
DECL|macro|BM_43_30
mdefine_line|#define BM_43_30 0x00000fffc0000000
DECL|macro|BM_30_43
mdefine_line|#define BM_30_43 BM_43_30
DECL|macro|BM_44_30
mdefine_line|#define BM_44_30 0x00001fffc0000000
DECL|macro|BM_30_44
mdefine_line|#define BM_30_44 BM_44_30
DECL|macro|BM_45_30
mdefine_line|#define BM_45_30 0x00003fffc0000000
DECL|macro|BM_30_45
mdefine_line|#define BM_30_45 BM_45_30
DECL|macro|BM_46_30
mdefine_line|#define BM_46_30 0x00007fffc0000000
DECL|macro|BM_30_46
mdefine_line|#define BM_30_46 BM_46_30
DECL|macro|BM_47_30
mdefine_line|#define BM_47_30 0x0000ffffc0000000
DECL|macro|BM_30_47
mdefine_line|#define BM_30_47 BM_47_30
DECL|macro|BM_48_30
mdefine_line|#define BM_48_30 0x0001ffffc0000000
DECL|macro|BM_30_48
mdefine_line|#define BM_30_48 BM_48_30
DECL|macro|BM_49_30
mdefine_line|#define BM_49_30 0x0003ffffc0000000
DECL|macro|BM_30_49
mdefine_line|#define BM_30_49 BM_49_30
DECL|macro|BM_50_30
mdefine_line|#define BM_50_30 0x0007ffffc0000000
DECL|macro|BM_30_50
mdefine_line|#define BM_30_50 BM_50_30
DECL|macro|BM_51_30
mdefine_line|#define BM_51_30 0x000fffffc0000000
DECL|macro|BM_30_51
mdefine_line|#define BM_30_51 BM_51_30
DECL|macro|BM_52_30
mdefine_line|#define BM_52_30 0x001fffffc0000000
DECL|macro|BM_30_52
mdefine_line|#define BM_30_52 BM_52_30
DECL|macro|BM_53_30
mdefine_line|#define BM_53_30 0x003fffffc0000000
DECL|macro|BM_30_53
mdefine_line|#define BM_30_53 BM_53_30
DECL|macro|BM_54_30
mdefine_line|#define BM_54_30 0x007fffffc0000000
DECL|macro|BM_30_54
mdefine_line|#define BM_30_54 BM_54_30
DECL|macro|BM_55_30
mdefine_line|#define BM_55_30 0x00ffffffc0000000
DECL|macro|BM_30_55
mdefine_line|#define BM_30_55 BM_55_30
DECL|macro|BM_56_30
mdefine_line|#define BM_56_30 0x01ffffffc0000000
DECL|macro|BM_30_56
mdefine_line|#define BM_30_56 BM_56_30
DECL|macro|BM_57_30
mdefine_line|#define BM_57_30 0x03ffffffc0000000
DECL|macro|BM_30_57
mdefine_line|#define BM_30_57 BM_57_30
DECL|macro|BM_58_30
mdefine_line|#define BM_58_30 0x07ffffffc0000000
DECL|macro|BM_30_58
mdefine_line|#define BM_30_58 BM_58_30
DECL|macro|BM_59_30
mdefine_line|#define BM_59_30 0x0fffffffc0000000
DECL|macro|BM_30_59
mdefine_line|#define BM_30_59 BM_59_30
DECL|macro|BM_60_30
mdefine_line|#define BM_60_30 0x1fffffffc0000000
DECL|macro|BM_30_60
mdefine_line|#define BM_30_60 BM_60_30
DECL|macro|BM_61_30
mdefine_line|#define BM_61_30 0x3fffffffc0000000
DECL|macro|BM_30_61
mdefine_line|#define BM_30_61 BM_61_30
DECL|macro|BM_62_30
mdefine_line|#define BM_62_30 0x7fffffffc0000000
DECL|macro|BM_30_62
mdefine_line|#define BM_30_62 BM_62_30
DECL|macro|BM_63_30
mdefine_line|#define BM_63_30 0xffffffffc0000000
DECL|macro|BM_30_63
mdefine_line|#define BM_30_63 BM_63_30
DECL|macro|BM_31_31
mdefine_line|#define BM_31_31 0x0000000080000000
DECL|macro|BM_32_31
mdefine_line|#define BM_32_31 0x0000000180000000
DECL|macro|BM_31_32
mdefine_line|#define BM_31_32 BM_32_31
DECL|macro|BM_33_31
mdefine_line|#define BM_33_31 0x0000000380000000
DECL|macro|BM_31_33
mdefine_line|#define BM_31_33 BM_33_31
DECL|macro|BM_34_31
mdefine_line|#define BM_34_31 0x0000000780000000
DECL|macro|BM_31_34
mdefine_line|#define BM_31_34 BM_34_31
DECL|macro|BM_35_31
mdefine_line|#define BM_35_31 0x0000000f80000000
DECL|macro|BM_31_35
mdefine_line|#define BM_31_35 BM_35_31
DECL|macro|BM_36_31
mdefine_line|#define BM_36_31 0x0000001f80000000
DECL|macro|BM_31_36
mdefine_line|#define BM_31_36 BM_36_31
DECL|macro|BM_37_31
mdefine_line|#define BM_37_31 0x0000003f80000000
DECL|macro|BM_31_37
mdefine_line|#define BM_31_37 BM_37_31
DECL|macro|BM_38_31
mdefine_line|#define BM_38_31 0x0000007f80000000
DECL|macro|BM_31_38
mdefine_line|#define BM_31_38 BM_38_31
DECL|macro|BM_39_31
mdefine_line|#define BM_39_31 0x000000ff80000000
DECL|macro|BM_31_39
mdefine_line|#define BM_31_39 BM_39_31
DECL|macro|BM_40_31
mdefine_line|#define BM_40_31 0x000001ff80000000
DECL|macro|BM_31_40
mdefine_line|#define BM_31_40 BM_40_31
DECL|macro|BM_41_31
mdefine_line|#define BM_41_31 0x000003ff80000000
DECL|macro|BM_31_41
mdefine_line|#define BM_31_41 BM_41_31
DECL|macro|BM_42_31
mdefine_line|#define BM_42_31 0x000007ff80000000
DECL|macro|BM_31_42
mdefine_line|#define BM_31_42 BM_42_31
DECL|macro|BM_43_31
mdefine_line|#define BM_43_31 0x00000fff80000000
DECL|macro|BM_31_43
mdefine_line|#define BM_31_43 BM_43_31
DECL|macro|BM_44_31
mdefine_line|#define BM_44_31 0x00001fff80000000
DECL|macro|BM_31_44
mdefine_line|#define BM_31_44 BM_44_31
DECL|macro|BM_45_31
mdefine_line|#define BM_45_31 0x00003fff80000000
DECL|macro|BM_31_45
mdefine_line|#define BM_31_45 BM_45_31
DECL|macro|BM_46_31
mdefine_line|#define BM_46_31 0x00007fff80000000
DECL|macro|BM_31_46
mdefine_line|#define BM_31_46 BM_46_31
DECL|macro|BM_47_31
mdefine_line|#define BM_47_31 0x0000ffff80000000
DECL|macro|BM_31_47
mdefine_line|#define BM_31_47 BM_47_31
DECL|macro|BM_48_31
mdefine_line|#define BM_48_31 0x0001ffff80000000
DECL|macro|BM_31_48
mdefine_line|#define BM_31_48 BM_48_31
DECL|macro|BM_49_31
mdefine_line|#define BM_49_31 0x0003ffff80000000
DECL|macro|BM_31_49
mdefine_line|#define BM_31_49 BM_49_31
DECL|macro|BM_50_31
mdefine_line|#define BM_50_31 0x0007ffff80000000
DECL|macro|BM_31_50
mdefine_line|#define BM_31_50 BM_50_31
DECL|macro|BM_51_31
mdefine_line|#define BM_51_31 0x000fffff80000000
DECL|macro|BM_31_51
mdefine_line|#define BM_31_51 BM_51_31
DECL|macro|BM_52_31
mdefine_line|#define BM_52_31 0x001fffff80000000
DECL|macro|BM_31_52
mdefine_line|#define BM_31_52 BM_52_31
DECL|macro|BM_53_31
mdefine_line|#define BM_53_31 0x003fffff80000000
DECL|macro|BM_31_53
mdefine_line|#define BM_31_53 BM_53_31
DECL|macro|BM_54_31
mdefine_line|#define BM_54_31 0x007fffff80000000
DECL|macro|BM_31_54
mdefine_line|#define BM_31_54 BM_54_31
DECL|macro|BM_55_31
mdefine_line|#define BM_55_31 0x00ffffff80000000
DECL|macro|BM_31_55
mdefine_line|#define BM_31_55 BM_55_31
DECL|macro|BM_56_31
mdefine_line|#define BM_56_31 0x01ffffff80000000
DECL|macro|BM_31_56
mdefine_line|#define BM_31_56 BM_56_31
DECL|macro|BM_57_31
mdefine_line|#define BM_57_31 0x03ffffff80000000
DECL|macro|BM_31_57
mdefine_line|#define BM_31_57 BM_57_31
DECL|macro|BM_58_31
mdefine_line|#define BM_58_31 0x07ffffff80000000
DECL|macro|BM_31_58
mdefine_line|#define BM_31_58 BM_58_31
DECL|macro|BM_59_31
mdefine_line|#define BM_59_31 0x0fffffff80000000
DECL|macro|BM_31_59
mdefine_line|#define BM_31_59 BM_59_31
DECL|macro|BM_60_31
mdefine_line|#define BM_60_31 0x1fffffff80000000
DECL|macro|BM_31_60
mdefine_line|#define BM_31_60 BM_60_31
DECL|macro|BM_61_31
mdefine_line|#define BM_61_31 0x3fffffff80000000
DECL|macro|BM_31_61
mdefine_line|#define BM_31_61 BM_61_31
DECL|macro|BM_62_31
mdefine_line|#define BM_62_31 0x7fffffff80000000
DECL|macro|BM_31_62
mdefine_line|#define BM_31_62 BM_62_31
DECL|macro|BM_63_31
mdefine_line|#define BM_63_31 0xffffffff80000000
DECL|macro|BM_31_63
mdefine_line|#define BM_31_63 BM_63_31
DECL|macro|BM_32_32
mdefine_line|#define BM_32_32 0x0000000100000000
DECL|macro|BM_33_32
mdefine_line|#define BM_33_32 0x0000000300000000
DECL|macro|BM_32_33
mdefine_line|#define BM_32_33 BM_33_32
DECL|macro|BM_34_32
mdefine_line|#define BM_34_32 0x0000000700000000
DECL|macro|BM_32_34
mdefine_line|#define BM_32_34 BM_34_32
DECL|macro|BM_35_32
mdefine_line|#define BM_35_32 0x0000000f00000000
DECL|macro|BM_32_35
mdefine_line|#define BM_32_35 BM_35_32
DECL|macro|BM_36_32
mdefine_line|#define BM_36_32 0x0000001f00000000
DECL|macro|BM_32_36
mdefine_line|#define BM_32_36 BM_36_32
DECL|macro|BM_37_32
mdefine_line|#define BM_37_32 0x0000003f00000000
DECL|macro|BM_32_37
mdefine_line|#define BM_32_37 BM_37_32
DECL|macro|BM_38_32
mdefine_line|#define BM_38_32 0x0000007f00000000
DECL|macro|BM_32_38
mdefine_line|#define BM_32_38 BM_38_32
DECL|macro|BM_39_32
mdefine_line|#define BM_39_32 0x000000ff00000000
DECL|macro|BM_32_39
mdefine_line|#define BM_32_39 BM_39_32
DECL|macro|BM_40_32
mdefine_line|#define BM_40_32 0x000001ff00000000
DECL|macro|BM_32_40
mdefine_line|#define BM_32_40 BM_40_32
DECL|macro|BM_41_32
mdefine_line|#define BM_41_32 0x000003ff00000000
DECL|macro|BM_32_41
mdefine_line|#define BM_32_41 BM_41_32
DECL|macro|BM_42_32
mdefine_line|#define BM_42_32 0x000007ff00000000
DECL|macro|BM_32_42
mdefine_line|#define BM_32_42 BM_42_32
DECL|macro|BM_43_32
mdefine_line|#define BM_43_32 0x00000fff00000000
DECL|macro|BM_32_43
mdefine_line|#define BM_32_43 BM_43_32
DECL|macro|BM_44_32
mdefine_line|#define BM_44_32 0x00001fff00000000
DECL|macro|BM_32_44
mdefine_line|#define BM_32_44 BM_44_32
DECL|macro|BM_45_32
mdefine_line|#define BM_45_32 0x00003fff00000000
DECL|macro|BM_32_45
mdefine_line|#define BM_32_45 BM_45_32
DECL|macro|BM_46_32
mdefine_line|#define BM_46_32 0x00007fff00000000
DECL|macro|BM_32_46
mdefine_line|#define BM_32_46 BM_46_32
DECL|macro|BM_47_32
mdefine_line|#define BM_47_32 0x0000ffff00000000
DECL|macro|BM_32_47
mdefine_line|#define BM_32_47 BM_47_32
DECL|macro|BM_48_32
mdefine_line|#define BM_48_32 0x0001ffff00000000
DECL|macro|BM_32_48
mdefine_line|#define BM_32_48 BM_48_32
DECL|macro|BM_49_32
mdefine_line|#define BM_49_32 0x0003ffff00000000
DECL|macro|BM_32_49
mdefine_line|#define BM_32_49 BM_49_32
DECL|macro|BM_50_32
mdefine_line|#define BM_50_32 0x0007ffff00000000
DECL|macro|BM_32_50
mdefine_line|#define BM_32_50 BM_50_32
DECL|macro|BM_51_32
mdefine_line|#define BM_51_32 0x000fffff00000000
DECL|macro|BM_32_51
mdefine_line|#define BM_32_51 BM_51_32
DECL|macro|BM_52_32
mdefine_line|#define BM_52_32 0x001fffff00000000
DECL|macro|BM_32_52
mdefine_line|#define BM_32_52 BM_52_32
DECL|macro|BM_53_32
mdefine_line|#define BM_53_32 0x003fffff00000000
DECL|macro|BM_32_53
mdefine_line|#define BM_32_53 BM_53_32
DECL|macro|BM_54_32
mdefine_line|#define BM_54_32 0x007fffff00000000
DECL|macro|BM_32_54
mdefine_line|#define BM_32_54 BM_54_32
DECL|macro|BM_55_32
mdefine_line|#define BM_55_32 0x00ffffff00000000
DECL|macro|BM_32_55
mdefine_line|#define BM_32_55 BM_55_32
DECL|macro|BM_56_32
mdefine_line|#define BM_56_32 0x01ffffff00000000
DECL|macro|BM_32_56
mdefine_line|#define BM_32_56 BM_56_32
DECL|macro|BM_57_32
mdefine_line|#define BM_57_32 0x03ffffff00000000
DECL|macro|BM_32_57
mdefine_line|#define BM_32_57 BM_57_32
DECL|macro|BM_58_32
mdefine_line|#define BM_58_32 0x07ffffff00000000
DECL|macro|BM_32_58
mdefine_line|#define BM_32_58 BM_58_32
DECL|macro|BM_59_32
mdefine_line|#define BM_59_32 0x0fffffff00000000
DECL|macro|BM_32_59
mdefine_line|#define BM_32_59 BM_59_32
DECL|macro|BM_60_32
mdefine_line|#define BM_60_32 0x1fffffff00000000
DECL|macro|BM_32_60
mdefine_line|#define BM_32_60 BM_60_32
DECL|macro|BM_61_32
mdefine_line|#define BM_61_32 0x3fffffff00000000
DECL|macro|BM_32_61
mdefine_line|#define BM_32_61 BM_61_32
DECL|macro|BM_62_32
mdefine_line|#define BM_62_32 0x7fffffff00000000
DECL|macro|BM_32_62
mdefine_line|#define BM_32_62 BM_62_32
DECL|macro|BM_63_32
mdefine_line|#define BM_63_32 0xffffffff00000000
DECL|macro|BM_32_63
mdefine_line|#define BM_32_63 BM_63_32
DECL|macro|BM_33_33
mdefine_line|#define BM_33_33 0x0000000200000000
DECL|macro|BM_34_33
mdefine_line|#define BM_34_33 0x0000000600000000
DECL|macro|BM_33_34
mdefine_line|#define BM_33_34 BM_34_33
DECL|macro|BM_35_33
mdefine_line|#define BM_35_33 0x0000000e00000000
DECL|macro|BM_33_35
mdefine_line|#define BM_33_35 BM_35_33
DECL|macro|BM_36_33
mdefine_line|#define BM_36_33 0x0000001e00000000
DECL|macro|BM_33_36
mdefine_line|#define BM_33_36 BM_36_33
DECL|macro|BM_37_33
mdefine_line|#define BM_37_33 0x0000003e00000000
DECL|macro|BM_33_37
mdefine_line|#define BM_33_37 BM_37_33
DECL|macro|BM_38_33
mdefine_line|#define BM_38_33 0x0000007e00000000
DECL|macro|BM_33_38
mdefine_line|#define BM_33_38 BM_38_33
DECL|macro|BM_39_33
mdefine_line|#define BM_39_33 0x000000fe00000000
DECL|macro|BM_33_39
mdefine_line|#define BM_33_39 BM_39_33
DECL|macro|BM_40_33
mdefine_line|#define BM_40_33 0x000001fe00000000
DECL|macro|BM_33_40
mdefine_line|#define BM_33_40 BM_40_33
DECL|macro|BM_41_33
mdefine_line|#define BM_41_33 0x000003fe00000000
DECL|macro|BM_33_41
mdefine_line|#define BM_33_41 BM_41_33
DECL|macro|BM_42_33
mdefine_line|#define BM_42_33 0x000007fe00000000
DECL|macro|BM_33_42
mdefine_line|#define BM_33_42 BM_42_33
DECL|macro|BM_43_33
mdefine_line|#define BM_43_33 0x00000ffe00000000
DECL|macro|BM_33_43
mdefine_line|#define BM_33_43 BM_43_33
DECL|macro|BM_44_33
mdefine_line|#define BM_44_33 0x00001ffe00000000
DECL|macro|BM_33_44
mdefine_line|#define BM_33_44 BM_44_33
DECL|macro|BM_45_33
mdefine_line|#define BM_45_33 0x00003ffe00000000
DECL|macro|BM_33_45
mdefine_line|#define BM_33_45 BM_45_33
DECL|macro|BM_46_33
mdefine_line|#define BM_46_33 0x00007ffe00000000
DECL|macro|BM_33_46
mdefine_line|#define BM_33_46 BM_46_33
DECL|macro|BM_47_33
mdefine_line|#define BM_47_33 0x0000fffe00000000
DECL|macro|BM_33_47
mdefine_line|#define BM_33_47 BM_47_33
DECL|macro|BM_48_33
mdefine_line|#define BM_48_33 0x0001fffe00000000
DECL|macro|BM_33_48
mdefine_line|#define BM_33_48 BM_48_33
DECL|macro|BM_49_33
mdefine_line|#define BM_49_33 0x0003fffe00000000
DECL|macro|BM_33_49
mdefine_line|#define BM_33_49 BM_49_33
DECL|macro|BM_50_33
mdefine_line|#define BM_50_33 0x0007fffe00000000
DECL|macro|BM_33_50
mdefine_line|#define BM_33_50 BM_50_33
DECL|macro|BM_51_33
mdefine_line|#define BM_51_33 0x000ffffe00000000
DECL|macro|BM_33_51
mdefine_line|#define BM_33_51 BM_51_33
DECL|macro|BM_52_33
mdefine_line|#define BM_52_33 0x001ffffe00000000
DECL|macro|BM_33_52
mdefine_line|#define BM_33_52 BM_52_33
DECL|macro|BM_53_33
mdefine_line|#define BM_53_33 0x003ffffe00000000
DECL|macro|BM_33_53
mdefine_line|#define BM_33_53 BM_53_33
DECL|macro|BM_54_33
mdefine_line|#define BM_54_33 0x007ffffe00000000
DECL|macro|BM_33_54
mdefine_line|#define BM_33_54 BM_54_33
DECL|macro|BM_55_33
mdefine_line|#define BM_55_33 0x00fffffe00000000
DECL|macro|BM_33_55
mdefine_line|#define BM_33_55 BM_55_33
DECL|macro|BM_56_33
mdefine_line|#define BM_56_33 0x01fffffe00000000
DECL|macro|BM_33_56
mdefine_line|#define BM_33_56 BM_56_33
DECL|macro|BM_57_33
mdefine_line|#define BM_57_33 0x03fffffe00000000
DECL|macro|BM_33_57
mdefine_line|#define BM_33_57 BM_57_33
DECL|macro|BM_58_33
mdefine_line|#define BM_58_33 0x07fffffe00000000
DECL|macro|BM_33_58
mdefine_line|#define BM_33_58 BM_58_33
DECL|macro|BM_59_33
mdefine_line|#define BM_59_33 0x0ffffffe00000000
DECL|macro|BM_33_59
mdefine_line|#define BM_33_59 BM_59_33
DECL|macro|BM_60_33
mdefine_line|#define BM_60_33 0x1ffffffe00000000
DECL|macro|BM_33_60
mdefine_line|#define BM_33_60 BM_60_33
DECL|macro|BM_61_33
mdefine_line|#define BM_61_33 0x3ffffffe00000000
DECL|macro|BM_33_61
mdefine_line|#define BM_33_61 BM_61_33
DECL|macro|BM_62_33
mdefine_line|#define BM_62_33 0x7ffffffe00000000
DECL|macro|BM_33_62
mdefine_line|#define BM_33_62 BM_62_33
DECL|macro|BM_63_33
mdefine_line|#define BM_63_33 0xfffffffe00000000
DECL|macro|BM_33_63
mdefine_line|#define BM_33_63 BM_63_33
DECL|macro|BM_34_34
mdefine_line|#define BM_34_34 0x0000000400000000
DECL|macro|BM_35_34
mdefine_line|#define BM_35_34 0x0000000c00000000
DECL|macro|BM_34_35
mdefine_line|#define BM_34_35 BM_35_34
DECL|macro|BM_36_34
mdefine_line|#define BM_36_34 0x0000001c00000000
DECL|macro|BM_34_36
mdefine_line|#define BM_34_36 BM_36_34
DECL|macro|BM_37_34
mdefine_line|#define BM_37_34 0x0000003c00000000
DECL|macro|BM_34_37
mdefine_line|#define BM_34_37 BM_37_34
DECL|macro|BM_38_34
mdefine_line|#define BM_38_34 0x0000007c00000000
DECL|macro|BM_34_38
mdefine_line|#define BM_34_38 BM_38_34
DECL|macro|BM_39_34
mdefine_line|#define BM_39_34 0x000000fc00000000
DECL|macro|BM_34_39
mdefine_line|#define BM_34_39 BM_39_34
DECL|macro|BM_40_34
mdefine_line|#define BM_40_34 0x000001fc00000000
DECL|macro|BM_34_40
mdefine_line|#define BM_34_40 BM_40_34
DECL|macro|BM_41_34
mdefine_line|#define BM_41_34 0x000003fc00000000
DECL|macro|BM_34_41
mdefine_line|#define BM_34_41 BM_41_34
DECL|macro|BM_42_34
mdefine_line|#define BM_42_34 0x000007fc00000000
DECL|macro|BM_34_42
mdefine_line|#define BM_34_42 BM_42_34
DECL|macro|BM_43_34
mdefine_line|#define BM_43_34 0x00000ffc00000000
DECL|macro|BM_34_43
mdefine_line|#define BM_34_43 BM_43_34
DECL|macro|BM_44_34
mdefine_line|#define BM_44_34 0x00001ffc00000000
DECL|macro|BM_34_44
mdefine_line|#define BM_34_44 BM_44_34
DECL|macro|BM_45_34
mdefine_line|#define BM_45_34 0x00003ffc00000000
DECL|macro|BM_34_45
mdefine_line|#define BM_34_45 BM_45_34
DECL|macro|BM_46_34
mdefine_line|#define BM_46_34 0x00007ffc00000000
DECL|macro|BM_34_46
mdefine_line|#define BM_34_46 BM_46_34
DECL|macro|BM_47_34
mdefine_line|#define BM_47_34 0x0000fffc00000000
DECL|macro|BM_34_47
mdefine_line|#define BM_34_47 BM_47_34
DECL|macro|BM_48_34
mdefine_line|#define BM_48_34 0x0001fffc00000000
DECL|macro|BM_34_48
mdefine_line|#define BM_34_48 BM_48_34
DECL|macro|BM_49_34
mdefine_line|#define BM_49_34 0x0003fffc00000000
DECL|macro|BM_34_49
mdefine_line|#define BM_34_49 BM_49_34
DECL|macro|BM_50_34
mdefine_line|#define BM_50_34 0x0007fffc00000000
DECL|macro|BM_34_50
mdefine_line|#define BM_34_50 BM_50_34
DECL|macro|BM_51_34
mdefine_line|#define BM_51_34 0x000ffffc00000000
DECL|macro|BM_34_51
mdefine_line|#define BM_34_51 BM_51_34
DECL|macro|BM_52_34
mdefine_line|#define BM_52_34 0x001ffffc00000000
DECL|macro|BM_34_52
mdefine_line|#define BM_34_52 BM_52_34
DECL|macro|BM_53_34
mdefine_line|#define BM_53_34 0x003ffffc00000000
DECL|macro|BM_34_53
mdefine_line|#define BM_34_53 BM_53_34
DECL|macro|BM_54_34
mdefine_line|#define BM_54_34 0x007ffffc00000000
DECL|macro|BM_34_54
mdefine_line|#define BM_34_54 BM_54_34
DECL|macro|BM_55_34
mdefine_line|#define BM_55_34 0x00fffffc00000000
DECL|macro|BM_34_55
mdefine_line|#define BM_34_55 BM_55_34
DECL|macro|BM_56_34
mdefine_line|#define BM_56_34 0x01fffffc00000000
DECL|macro|BM_34_56
mdefine_line|#define BM_34_56 BM_56_34
DECL|macro|BM_57_34
mdefine_line|#define BM_57_34 0x03fffffc00000000
DECL|macro|BM_34_57
mdefine_line|#define BM_34_57 BM_57_34
DECL|macro|BM_58_34
mdefine_line|#define BM_58_34 0x07fffffc00000000
DECL|macro|BM_34_58
mdefine_line|#define BM_34_58 BM_58_34
DECL|macro|BM_59_34
mdefine_line|#define BM_59_34 0x0ffffffc00000000
DECL|macro|BM_34_59
mdefine_line|#define BM_34_59 BM_59_34
DECL|macro|BM_60_34
mdefine_line|#define BM_60_34 0x1ffffffc00000000
DECL|macro|BM_34_60
mdefine_line|#define BM_34_60 BM_60_34
DECL|macro|BM_61_34
mdefine_line|#define BM_61_34 0x3ffffffc00000000
DECL|macro|BM_34_61
mdefine_line|#define BM_34_61 BM_61_34
DECL|macro|BM_62_34
mdefine_line|#define BM_62_34 0x7ffffffc00000000
DECL|macro|BM_34_62
mdefine_line|#define BM_34_62 BM_62_34
DECL|macro|BM_63_34
mdefine_line|#define BM_63_34 0xfffffffc00000000
DECL|macro|BM_34_63
mdefine_line|#define BM_34_63 BM_63_34
DECL|macro|BM_35_35
mdefine_line|#define BM_35_35 0x0000000800000000
DECL|macro|BM_36_35
mdefine_line|#define BM_36_35 0x0000001800000000
DECL|macro|BM_35_36
mdefine_line|#define BM_35_36 BM_36_35
DECL|macro|BM_37_35
mdefine_line|#define BM_37_35 0x0000003800000000
DECL|macro|BM_35_37
mdefine_line|#define BM_35_37 BM_37_35
DECL|macro|BM_38_35
mdefine_line|#define BM_38_35 0x0000007800000000
DECL|macro|BM_35_38
mdefine_line|#define BM_35_38 BM_38_35
DECL|macro|BM_39_35
mdefine_line|#define BM_39_35 0x000000f800000000
DECL|macro|BM_35_39
mdefine_line|#define BM_35_39 BM_39_35
DECL|macro|BM_40_35
mdefine_line|#define BM_40_35 0x000001f800000000
DECL|macro|BM_35_40
mdefine_line|#define BM_35_40 BM_40_35
DECL|macro|BM_41_35
mdefine_line|#define BM_41_35 0x000003f800000000
DECL|macro|BM_35_41
mdefine_line|#define BM_35_41 BM_41_35
DECL|macro|BM_42_35
mdefine_line|#define BM_42_35 0x000007f800000000
DECL|macro|BM_35_42
mdefine_line|#define BM_35_42 BM_42_35
DECL|macro|BM_43_35
mdefine_line|#define BM_43_35 0x00000ff800000000
DECL|macro|BM_35_43
mdefine_line|#define BM_35_43 BM_43_35
DECL|macro|BM_44_35
mdefine_line|#define BM_44_35 0x00001ff800000000
DECL|macro|BM_35_44
mdefine_line|#define BM_35_44 BM_44_35
DECL|macro|BM_45_35
mdefine_line|#define BM_45_35 0x00003ff800000000
DECL|macro|BM_35_45
mdefine_line|#define BM_35_45 BM_45_35
DECL|macro|BM_46_35
mdefine_line|#define BM_46_35 0x00007ff800000000
DECL|macro|BM_35_46
mdefine_line|#define BM_35_46 BM_46_35
DECL|macro|BM_47_35
mdefine_line|#define BM_47_35 0x0000fff800000000
DECL|macro|BM_35_47
mdefine_line|#define BM_35_47 BM_47_35
DECL|macro|BM_48_35
mdefine_line|#define BM_48_35 0x0001fff800000000
DECL|macro|BM_35_48
mdefine_line|#define BM_35_48 BM_48_35
DECL|macro|BM_49_35
mdefine_line|#define BM_49_35 0x0003fff800000000
DECL|macro|BM_35_49
mdefine_line|#define BM_35_49 BM_49_35
DECL|macro|BM_50_35
mdefine_line|#define BM_50_35 0x0007fff800000000
DECL|macro|BM_35_50
mdefine_line|#define BM_35_50 BM_50_35
DECL|macro|BM_51_35
mdefine_line|#define BM_51_35 0x000ffff800000000
DECL|macro|BM_35_51
mdefine_line|#define BM_35_51 BM_51_35
DECL|macro|BM_52_35
mdefine_line|#define BM_52_35 0x001ffff800000000
DECL|macro|BM_35_52
mdefine_line|#define BM_35_52 BM_52_35
DECL|macro|BM_53_35
mdefine_line|#define BM_53_35 0x003ffff800000000
DECL|macro|BM_35_53
mdefine_line|#define BM_35_53 BM_53_35
DECL|macro|BM_54_35
mdefine_line|#define BM_54_35 0x007ffff800000000
DECL|macro|BM_35_54
mdefine_line|#define BM_35_54 BM_54_35
DECL|macro|BM_55_35
mdefine_line|#define BM_55_35 0x00fffff800000000
DECL|macro|BM_35_55
mdefine_line|#define BM_35_55 BM_55_35
DECL|macro|BM_56_35
mdefine_line|#define BM_56_35 0x01fffff800000000
DECL|macro|BM_35_56
mdefine_line|#define BM_35_56 BM_56_35
DECL|macro|BM_57_35
mdefine_line|#define BM_57_35 0x03fffff800000000
DECL|macro|BM_35_57
mdefine_line|#define BM_35_57 BM_57_35
DECL|macro|BM_58_35
mdefine_line|#define BM_58_35 0x07fffff800000000
DECL|macro|BM_35_58
mdefine_line|#define BM_35_58 BM_58_35
DECL|macro|BM_59_35
mdefine_line|#define BM_59_35 0x0ffffff800000000
DECL|macro|BM_35_59
mdefine_line|#define BM_35_59 BM_59_35
DECL|macro|BM_60_35
mdefine_line|#define BM_60_35 0x1ffffff800000000
DECL|macro|BM_35_60
mdefine_line|#define BM_35_60 BM_60_35
DECL|macro|BM_61_35
mdefine_line|#define BM_61_35 0x3ffffff800000000
DECL|macro|BM_35_61
mdefine_line|#define BM_35_61 BM_61_35
DECL|macro|BM_62_35
mdefine_line|#define BM_62_35 0x7ffffff800000000
DECL|macro|BM_35_62
mdefine_line|#define BM_35_62 BM_62_35
DECL|macro|BM_63_35
mdefine_line|#define BM_63_35 0xfffffff800000000
DECL|macro|BM_35_63
mdefine_line|#define BM_35_63 BM_63_35
DECL|macro|BM_36_36
mdefine_line|#define BM_36_36 0x0000001000000000
DECL|macro|BM_37_36
mdefine_line|#define BM_37_36 0x0000003000000000
DECL|macro|BM_36_37
mdefine_line|#define BM_36_37 BM_37_36
DECL|macro|BM_38_36
mdefine_line|#define BM_38_36 0x0000007000000000
DECL|macro|BM_36_38
mdefine_line|#define BM_36_38 BM_38_36
DECL|macro|BM_39_36
mdefine_line|#define BM_39_36 0x000000f000000000
DECL|macro|BM_36_39
mdefine_line|#define BM_36_39 BM_39_36
DECL|macro|BM_40_36
mdefine_line|#define BM_40_36 0x000001f000000000
DECL|macro|BM_36_40
mdefine_line|#define BM_36_40 BM_40_36
DECL|macro|BM_41_36
mdefine_line|#define BM_41_36 0x000003f000000000
DECL|macro|BM_36_41
mdefine_line|#define BM_36_41 BM_41_36
DECL|macro|BM_42_36
mdefine_line|#define BM_42_36 0x000007f000000000
DECL|macro|BM_36_42
mdefine_line|#define BM_36_42 BM_42_36
DECL|macro|BM_43_36
mdefine_line|#define BM_43_36 0x00000ff000000000
DECL|macro|BM_36_43
mdefine_line|#define BM_36_43 BM_43_36
DECL|macro|BM_44_36
mdefine_line|#define BM_44_36 0x00001ff000000000
DECL|macro|BM_36_44
mdefine_line|#define BM_36_44 BM_44_36
DECL|macro|BM_45_36
mdefine_line|#define BM_45_36 0x00003ff000000000
DECL|macro|BM_36_45
mdefine_line|#define BM_36_45 BM_45_36
DECL|macro|BM_46_36
mdefine_line|#define BM_46_36 0x00007ff000000000
DECL|macro|BM_36_46
mdefine_line|#define BM_36_46 BM_46_36
DECL|macro|BM_47_36
mdefine_line|#define BM_47_36 0x0000fff000000000
DECL|macro|BM_36_47
mdefine_line|#define BM_36_47 BM_47_36
DECL|macro|BM_48_36
mdefine_line|#define BM_48_36 0x0001fff000000000
DECL|macro|BM_36_48
mdefine_line|#define BM_36_48 BM_48_36
DECL|macro|BM_49_36
mdefine_line|#define BM_49_36 0x0003fff000000000
DECL|macro|BM_36_49
mdefine_line|#define BM_36_49 BM_49_36
DECL|macro|BM_50_36
mdefine_line|#define BM_50_36 0x0007fff000000000
DECL|macro|BM_36_50
mdefine_line|#define BM_36_50 BM_50_36
DECL|macro|BM_51_36
mdefine_line|#define BM_51_36 0x000ffff000000000
DECL|macro|BM_36_51
mdefine_line|#define BM_36_51 BM_51_36
DECL|macro|BM_52_36
mdefine_line|#define BM_52_36 0x001ffff000000000
DECL|macro|BM_36_52
mdefine_line|#define BM_36_52 BM_52_36
DECL|macro|BM_53_36
mdefine_line|#define BM_53_36 0x003ffff000000000
DECL|macro|BM_36_53
mdefine_line|#define BM_36_53 BM_53_36
DECL|macro|BM_54_36
mdefine_line|#define BM_54_36 0x007ffff000000000
DECL|macro|BM_36_54
mdefine_line|#define BM_36_54 BM_54_36
DECL|macro|BM_55_36
mdefine_line|#define BM_55_36 0x00fffff000000000
DECL|macro|BM_36_55
mdefine_line|#define BM_36_55 BM_55_36
DECL|macro|BM_56_36
mdefine_line|#define BM_56_36 0x01fffff000000000
DECL|macro|BM_36_56
mdefine_line|#define BM_36_56 BM_56_36
DECL|macro|BM_57_36
mdefine_line|#define BM_57_36 0x03fffff000000000
DECL|macro|BM_36_57
mdefine_line|#define BM_36_57 BM_57_36
DECL|macro|BM_58_36
mdefine_line|#define BM_58_36 0x07fffff000000000
DECL|macro|BM_36_58
mdefine_line|#define BM_36_58 BM_58_36
DECL|macro|BM_59_36
mdefine_line|#define BM_59_36 0x0ffffff000000000
DECL|macro|BM_36_59
mdefine_line|#define BM_36_59 BM_59_36
DECL|macro|BM_60_36
mdefine_line|#define BM_60_36 0x1ffffff000000000
DECL|macro|BM_36_60
mdefine_line|#define BM_36_60 BM_60_36
DECL|macro|BM_61_36
mdefine_line|#define BM_61_36 0x3ffffff000000000
DECL|macro|BM_36_61
mdefine_line|#define BM_36_61 BM_61_36
DECL|macro|BM_62_36
mdefine_line|#define BM_62_36 0x7ffffff000000000
DECL|macro|BM_36_62
mdefine_line|#define BM_36_62 BM_62_36
DECL|macro|BM_63_36
mdefine_line|#define BM_63_36 0xfffffff000000000
DECL|macro|BM_36_63
mdefine_line|#define BM_36_63 BM_63_36
DECL|macro|BM_37_37
mdefine_line|#define BM_37_37 0x0000002000000000
DECL|macro|BM_38_37
mdefine_line|#define BM_38_37 0x0000006000000000
DECL|macro|BM_37_38
mdefine_line|#define BM_37_38 BM_38_37
DECL|macro|BM_39_37
mdefine_line|#define BM_39_37 0x000000e000000000
DECL|macro|BM_37_39
mdefine_line|#define BM_37_39 BM_39_37
DECL|macro|BM_40_37
mdefine_line|#define BM_40_37 0x000001e000000000
DECL|macro|BM_37_40
mdefine_line|#define BM_37_40 BM_40_37
DECL|macro|BM_41_37
mdefine_line|#define BM_41_37 0x000003e000000000
DECL|macro|BM_37_41
mdefine_line|#define BM_37_41 BM_41_37
DECL|macro|BM_42_37
mdefine_line|#define BM_42_37 0x000007e000000000
DECL|macro|BM_37_42
mdefine_line|#define BM_37_42 BM_42_37
DECL|macro|BM_43_37
mdefine_line|#define BM_43_37 0x00000fe000000000
DECL|macro|BM_37_43
mdefine_line|#define BM_37_43 BM_43_37
DECL|macro|BM_44_37
mdefine_line|#define BM_44_37 0x00001fe000000000
DECL|macro|BM_37_44
mdefine_line|#define BM_37_44 BM_44_37
DECL|macro|BM_45_37
mdefine_line|#define BM_45_37 0x00003fe000000000
DECL|macro|BM_37_45
mdefine_line|#define BM_37_45 BM_45_37
DECL|macro|BM_46_37
mdefine_line|#define BM_46_37 0x00007fe000000000
DECL|macro|BM_37_46
mdefine_line|#define BM_37_46 BM_46_37
DECL|macro|BM_47_37
mdefine_line|#define BM_47_37 0x0000ffe000000000
DECL|macro|BM_37_47
mdefine_line|#define BM_37_47 BM_47_37
DECL|macro|BM_48_37
mdefine_line|#define BM_48_37 0x0001ffe000000000
DECL|macro|BM_37_48
mdefine_line|#define BM_37_48 BM_48_37
DECL|macro|BM_49_37
mdefine_line|#define BM_49_37 0x0003ffe000000000
DECL|macro|BM_37_49
mdefine_line|#define BM_37_49 BM_49_37
DECL|macro|BM_50_37
mdefine_line|#define BM_50_37 0x0007ffe000000000
DECL|macro|BM_37_50
mdefine_line|#define BM_37_50 BM_50_37
DECL|macro|BM_51_37
mdefine_line|#define BM_51_37 0x000fffe000000000
DECL|macro|BM_37_51
mdefine_line|#define BM_37_51 BM_51_37
DECL|macro|BM_52_37
mdefine_line|#define BM_52_37 0x001fffe000000000
DECL|macro|BM_37_52
mdefine_line|#define BM_37_52 BM_52_37
DECL|macro|BM_53_37
mdefine_line|#define BM_53_37 0x003fffe000000000
DECL|macro|BM_37_53
mdefine_line|#define BM_37_53 BM_53_37
DECL|macro|BM_54_37
mdefine_line|#define BM_54_37 0x007fffe000000000
DECL|macro|BM_37_54
mdefine_line|#define BM_37_54 BM_54_37
DECL|macro|BM_55_37
mdefine_line|#define BM_55_37 0x00ffffe000000000
DECL|macro|BM_37_55
mdefine_line|#define BM_37_55 BM_55_37
DECL|macro|BM_56_37
mdefine_line|#define BM_56_37 0x01ffffe000000000
DECL|macro|BM_37_56
mdefine_line|#define BM_37_56 BM_56_37
DECL|macro|BM_57_37
mdefine_line|#define BM_57_37 0x03ffffe000000000
DECL|macro|BM_37_57
mdefine_line|#define BM_37_57 BM_57_37
DECL|macro|BM_58_37
mdefine_line|#define BM_58_37 0x07ffffe000000000
DECL|macro|BM_37_58
mdefine_line|#define BM_37_58 BM_58_37
DECL|macro|BM_59_37
mdefine_line|#define BM_59_37 0x0fffffe000000000
DECL|macro|BM_37_59
mdefine_line|#define BM_37_59 BM_59_37
DECL|macro|BM_60_37
mdefine_line|#define BM_60_37 0x1fffffe000000000
DECL|macro|BM_37_60
mdefine_line|#define BM_37_60 BM_60_37
DECL|macro|BM_61_37
mdefine_line|#define BM_61_37 0x3fffffe000000000
DECL|macro|BM_37_61
mdefine_line|#define BM_37_61 BM_61_37
DECL|macro|BM_62_37
mdefine_line|#define BM_62_37 0x7fffffe000000000
DECL|macro|BM_37_62
mdefine_line|#define BM_37_62 BM_62_37
DECL|macro|BM_63_37
mdefine_line|#define BM_63_37 0xffffffe000000000
DECL|macro|BM_37_63
mdefine_line|#define BM_37_63 BM_63_37
DECL|macro|BM_38_38
mdefine_line|#define BM_38_38 0x0000004000000000
DECL|macro|BM_39_38
mdefine_line|#define BM_39_38 0x000000c000000000
DECL|macro|BM_38_39
mdefine_line|#define BM_38_39 BM_39_38
DECL|macro|BM_40_38
mdefine_line|#define BM_40_38 0x000001c000000000
DECL|macro|BM_38_40
mdefine_line|#define BM_38_40 BM_40_38
DECL|macro|BM_41_38
mdefine_line|#define BM_41_38 0x000003c000000000
DECL|macro|BM_38_41
mdefine_line|#define BM_38_41 BM_41_38
DECL|macro|BM_42_38
mdefine_line|#define BM_42_38 0x000007c000000000
DECL|macro|BM_38_42
mdefine_line|#define BM_38_42 BM_42_38
DECL|macro|BM_43_38
mdefine_line|#define BM_43_38 0x00000fc000000000
DECL|macro|BM_38_43
mdefine_line|#define BM_38_43 BM_43_38
DECL|macro|BM_44_38
mdefine_line|#define BM_44_38 0x00001fc000000000
DECL|macro|BM_38_44
mdefine_line|#define BM_38_44 BM_44_38
DECL|macro|BM_45_38
mdefine_line|#define BM_45_38 0x00003fc000000000
DECL|macro|BM_38_45
mdefine_line|#define BM_38_45 BM_45_38
DECL|macro|BM_46_38
mdefine_line|#define BM_46_38 0x00007fc000000000
DECL|macro|BM_38_46
mdefine_line|#define BM_38_46 BM_46_38
DECL|macro|BM_47_38
mdefine_line|#define BM_47_38 0x0000ffc000000000
DECL|macro|BM_38_47
mdefine_line|#define BM_38_47 BM_47_38
DECL|macro|BM_48_38
mdefine_line|#define BM_48_38 0x0001ffc000000000
DECL|macro|BM_38_48
mdefine_line|#define BM_38_48 BM_48_38
DECL|macro|BM_49_38
mdefine_line|#define BM_49_38 0x0003ffc000000000
DECL|macro|BM_38_49
mdefine_line|#define BM_38_49 BM_49_38
DECL|macro|BM_50_38
mdefine_line|#define BM_50_38 0x0007ffc000000000
DECL|macro|BM_38_50
mdefine_line|#define BM_38_50 BM_50_38
DECL|macro|BM_51_38
mdefine_line|#define BM_51_38 0x000fffc000000000
DECL|macro|BM_38_51
mdefine_line|#define BM_38_51 BM_51_38
DECL|macro|BM_52_38
mdefine_line|#define BM_52_38 0x001fffc000000000
DECL|macro|BM_38_52
mdefine_line|#define BM_38_52 BM_52_38
DECL|macro|BM_53_38
mdefine_line|#define BM_53_38 0x003fffc000000000
DECL|macro|BM_38_53
mdefine_line|#define BM_38_53 BM_53_38
DECL|macro|BM_54_38
mdefine_line|#define BM_54_38 0x007fffc000000000
DECL|macro|BM_38_54
mdefine_line|#define BM_38_54 BM_54_38
DECL|macro|BM_55_38
mdefine_line|#define BM_55_38 0x00ffffc000000000
DECL|macro|BM_38_55
mdefine_line|#define BM_38_55 BM_55_38
DECL|macro|BM_56_38
mdefine_line|#define BM_56_38 0x01ffffc000000000
DECL|macro|BM_38_56
mdefine_line|#define BM_38_56 BM_56_38
DECL|macro|BM_57_38
mdefine_line|#define BM_57_38 0x03ffffc000000000
DECL|macro|BM_38_57
mdefine_line|#define BM_38_57 BM_57_38
DECL|macro|BM_58_38
mdefine_line|#define BM_58_38 0x07ffffc000000000
DECL|macro|BM_38_58
mdefine_line|#define BM_38_58 BM_58_38
DECL|macro|BM_59_38
mdefine_line|#define BM_59_38 0x0fffffc000000000
DECL|macro|BM_38_59
mdefine_line|#define BM_38_59 BM_59_38
DECL|macro|BM_60_38
mdefine_line|#define BM_60_38 0x1fffffc000000000
DECL|macro|BM_38_60
mdefine_line|#define BM_38_60 BM_60_38
DECL|macro|BM_61_38
mdefine_line|#define BM_61_38 0x3fffffc000000000
DECL|macro|BM_38_61
mdefine_line|#define BM_38_61 BM_61_38
DECL|macro|BM_62_38
mdefine_line|#define BM_62_38 0x7fffffc000000000
DECL|macro|BM_38_62
mdefine_line|#define BM_38_62 BM_62_38
DECL|macro|BM_63_38
mdefine_line|#define BM_63_38 0xffffffc000000000
DECL|macro|BM_38_63
mdefine_line|#define BM_38_63 BM_63_38
DECL|macro|BM_39_39
mdefine_line|#define BM_39_39 0x0000008000000000
DECL|macro|BM_40_39
mdefine_line|#define BM_40_39 0x0000018000000000
DECL|macro|BM_39_40
mdefine_line|#define BM_39_40 BM_40_39
DECL|macro|BM_41_39
mdefine_line|#define BM_41_39 0x0000038000000000
DECL|macro|BM_39_41
mdefine_line|#define BM_39_41 BM_41_39
DECL|macro|BM_42_39
mdefine_line|#define BM_42_39 0x0000078000000000
DECL|macro|BM_39_42
mdefine_line|#define BM_39_42 BM_42_39
DECL|macro|BM_43_39
mdefine_line|#define BM_43_39 0x00000f8000000000
DECL|macro|BM_39_43
mdefine_line|#define BM_39_43 BM_43_39
DECL|macro|BM_44_39
mdefine_line|#define BM_44_39 0x00001f8000000000
DECL|macro|BM_39_44
mdefine_line|#define BM_39_44 BM_44_39
DECL|macro|BM_45_39
mdefine_line|#define BM_45_39 0x00003f8000000000
DECL|macro|BM_39_45
mdefine_line|#define BM_39_45 BM_45_39
DECL|macro|BM_46_39
mdefine_line|#define BM_46_39 0x00007f8000000000
DECL|macro|BM_39_46
mdefine_line|#define BM_39_46 BM_46_39
DECL|macro|BM_47_39
mdefine_line|#define BM_47_39 0x0000ff8000000000
DECL|macro|BM_39_47
mdefine_line|#define BM_39_47 BM_47_39
DECL|macro|BM_48_39
mdefine_line|#define BM_48_39 0x0001ff8000000000
DECL|macro|BM_39_48
mdefine_line|#define BM_39_48 BM_48_39
DECL|macro|BM_49_39
mdefine_line|#define BM_49_39 0x0003ff8000000000
DECL|macro|BM_39_49
mdefine_line|#define BM_39_49 BM_49_39
DECL|macro|BM_50_39
mdefine_line|#define BM_50_39 0x0007ff8000000000
DECL|macro|BM_39_50
mdefine_line|#define BM_39_50 BM_50_39
DECL|macro|BM_51_39
mdefine_line|#define BM_51_39 0x000fff8000000000
DECL|macro|BM_39_51
mdefine_line|#define BM_39_51 BM_51_39
DECL|macro|BM_52_39
mdefine_line|#define BM_52_39 0x001fff8000000000
DECL|macro|BM_39_52
mdefine_line|#define BM_39_52 BM_52_39
DECL|macro|BM_53_39
mdefine_line|#define BM_53_39 0x003fff8000000000
DECL|macro|BM_39_53
mdefine_line|#define BM_39_53 BM_53_39
DECL|macro|BM_54_39
mdefine_line|#define BM_54_39 0x007fff8000000000
DECL|macro|BM_39_54
mdefine_line|#define BM_39_54 BM_54_39
DECL|macro|BM_55_39
mdefine_line|#define BM_55_39 0x00ffff8000000000
DECL|macro|BM_39_55
mdefine_line|#define BM_39_55 BM_55_39
DECL|macro|BM_56_39
mdefine_line|#define BM_56_39 0x01ffff8000000000
DECL|macro|BM_39_56
mdefine_line|#define BM_39_56 BM_56_39
DECL|macro|BM_57_39
mdefine_line|#define BM_57_39 0x03ffff8000000000
DECL|macro|BM_39_57
mdefine_line|#define BM_39_57 BM_57_39
DECL|macro|BM_58_39
mdefine_line|#define BM_58_39 0x07ffff8000000000
DECL|macro|BM_39_58
mdefine_line|#define BM_39_58 BM_58_39
DECL|macro|BM_59_39
mdefine_line|#define BM_59_39 0x0fffff8000000000
DECL|macro|BM_39_59
mdefine_line|#define BM_39_59 BM_59_39
DECL|macro|BM_60_39
mdefine_line|#define BM_60_39 0x1fffff8000000000
DECL|macro|BM_39_60
mdefine_line|#define BM_39_60 BM_60_39
DECL|macro|BM_61_39
mdefine_line|#define BM_61_39 0x3fffff8000000000
DECL|macro|BM_39_61
mdefine_line|#define BM_39_61 BM_61_39
DECL|macro|BM_62_39
mdefine_line|#define BM_62_39 0x7fffff8000000000
DECL|macro|BM_39_62
mdefine_line|#define BM_39_62 BM_62_39
DECL|macro|BM_63_39
mdefine_line|#define BM_63_39 0xffffff8000000000
DECL|macro|BM_39_63
mdefine_line|#define BM_39_63 BM_63_39
DECL|macro|BM_40_40
mdefine_line|#define BM_40_40 0x0000010000000000
DECL|macro|BM_41_40
mdefine_line|#define BM_41_40 0x0000030000000000
DECL|macro|BM_40_41
mdefine_line|#define BM_40_41 BM_41_40
DECL|macro|BM_42_40
mdefine_line|#define BM_42_40 0x0000070000000000
DECL|macro|BM_40_42
mdefine_line|#define BM_40_42 BM_42_40
DECL|macro|BM_43_40
mdefine_line|#define BM_43_40 0x00000f0000000000
DECL|macro|BM_40_43
mdefine_line|#define BM_40_43 BM_43_40
DECL|macro|BM_44_40
mdefine_line|#define BM_44_40 0x00001f0000000000
DECL|macro|BM_40_44
mdefine_line|#define BM_40_44 BM_44_40
DECL|macro|BM_45_40
mdefine_line|#define BM_45_40 0x00003f0000000000
DECL|macro|BM_40_45
mdefine_line|#define BM_40_45 BM_45_40
DECL|macro|BM_46_40
mdefine_line|#define BM_46_40 0x00007f0000000000
DECL|macro|BM_40_46
mdefine_line|#define BM_40_46 BM_46_40
DECL|macro|BM_47_40
mdefine_line|#define BM_47_40 0x0000ff0000000000
DECL|macro|BM_40_47
mdefine_line|#define BM_40_47 BM_47_40
DECL|macro|BM_48_40
mdefine_line|#define BM_48_40 0x0001ff0000000000
DECL|macro|BM_40_48
mdefine_line|#define BM_40_48 BM_48_40
DECL|macro|BM_49_40
mdefine_line|#define BM_49_40 0x0003ff0000000000
DECL|macro|BM_40_49
mdefine_line|#define BM_40_49 BM_49_40
DECL|macro|BM_50_40
mdefine_line|#define BM_50_40 0x0007ff0000000000
DECL|macro|BM_40_50
mdefine_line|#define BM_40_50 BM_50_40
DECL|macro|BM_51_40
mdefine_line|#define BM_51_40 0x000fff0000000000
DECL|macro|BM_40_51
mdefine_line|#define BM_40_51 BM_51_40
DECL|macro|BM_52_40
mdefine_line|#define BM_52_40 0x001fff0000000000
DECL|macro|BM_40_52
mdefine_line|#define BM_40_52 BM_52_40
DECL|macro|BM_53_40
mdefine_line|#define BM_53_40 0x003fff0000000000
DECL|macro|BM_40_53
mdefine_line|#define BM_40_53 BM_53_40
DECL|macro|BM_54_40
mdefine_line|#define BM_54_40 0x007fff0000000000
DECL|macro|BM_40_54
mdefine_line|#define BM_40_54 BM_54_40
DECL|macro|BM_55_40
mdefine_line|#define BM_55_40 0x00ffff0000000000
DECL|macro|BM_40_55
mdefine_line|#define BM_40_55 BM_55_40
DECL|macro|BM_56_40
mdefine_line|#define BM_56_40 0x01ffff0000000000
DECL|macro|BM_40_56
mdefine_line|#define BM_40_56 BM_56_40
DECL|macro|BM_57_40
mdefine_line|#define BM_57_40 0x03ffff0000000000
DECL|macro|BM_40_57
mdefine_line|#define BM_40_57 BM_57_40
DECL|macro|BM_58_40
mdefine_line|#define BM_58_40 0x07ffff0000000000
DECL|macro|BM_40_58
mdefine_line|#define BM_40_58 BM_58_40
DECL|macro|BM_59_40
mdefine_line|#define BM_59_40 0x0fffff0000000000
DECL|macro|BM_40_59
mdefine_line|#define BM_40_59 BM_59_40
DECL|macro|BM_60_40
mdefine_line|#define BM_60_40 0x1fffff0000000000
DECL|macro|BM_40_60
mdefine_line|#define BM_40_60 BM_60_40
DECL|macro|BM_61_40
mdefine_line|#define BM_61_40 0x3fffff0000000000
DECL|macro|BM_40_61
mdefine_line|#define BM_40_61 BM_61_40
DECL|macro|BM_62_40
mdefine_line|#define BM_62_40 0x7fffff0000000000
DECL|macro|BM_40_62
mdefine_line|#define BM_40_62 BM_62_40
DECL|macro|BM_63_40
mdefine_line|#define BM_63_40 0xffffff0000000000
DECL|macro|BM_40_63
mdefine_line|#define BM_40_63 BM_63_40
DECL|macro|BM_41_41
mdefine_line|#define BM_41_41 0x0000020000000000
DECL|macro|BM_42_41
mdefine_line|#define BM_42_41 0x0000060000000000
DECL|macro|BM_41_42
mdefine_line|#define BM_41_42 BM_42_41
DECL|macro|BM_43_41
mdefine_line|#define BM_43_41 0x00000e0000000000
DECL|macro|BM_41_43
mdefine_line|#define BM_41_43 BM_43_41
DECL|macro|BM_44_41
mdefine_line|#define BM_44_41 0x00001e0000000000
DECL|macro|BM_41_44
mdefine_line|#define BM_41_44 BM_44_41
DECL|macro|BM_45_41
mdefine_line|#define BM_45_41 0x00003e0000000000
DECL|macro|BM_41_45
mdefine_line|#define BM_41_45 BM_45_41
DECL|macro|BM_46_41
mdefine_line|#define BM_46_41 0x00007e0000000000
DECL|macro|BM_41_46
mdefine_line|#define BM_41_46 BM_46_41
DECL|macro|BM_47_41
mdefine_line|#define BM_47_41 0x0000fe0000000000
DECL|macro|BM_41_47
mdefine_line|#define BM_41_47 BM_47_41
DECL|macro|BM_48_41
mdefine_line|#define BM_48_41 0x0001fe0000000000
DECL|macro|BM_41_48
mdefine_line|#define BM_41_48 BM_48_41
DECL|macro|BM_49_41
mdefine_line|#define BM_49_41 0x0003fe0000000000
DECL|macro|BM_41_49
mdefine_line|#define BM_41_49 BM_49_41
DECL|macro|BM_50_41
mdefine_line|#define BM_50_41 0x0007fe0000000000
DECL|macro|BM_41_50
mdefine_line|#define BM_41_50 BM_50_41
DECL|macro|BM_51_41
mdefine_line|#define BM_51_41 0x000ffe0000000000
DECL|macro|BM_41_51
mdefine_line|#define BM_41_51 BM_51_41
DECL|macro|BM_52_41
mdefine_line|#define BM_52_41 0x001ffe0000000000
DECL|macro|BM_41_52
mdefine_line|#define BM_41_52 BM_52_41
DECL|macro|BM_53_41
mdefine_line|#define BM_53_41 0x003ffe0000000000
DECL|macro|BM_41_53
mdefine_line|#define BM_41_53 BM_53_41
DECL|macro|BM_54_41
mdefine_line|#define BM_54_41 0x007ffe0000000000
DECL|macro|BM_41_54
mdefine_line|#define BM_41_54 BM_54_41
DECL|macro|BM_55_41
mdefine_line|#define BM_55_41 0x00fffe0000000000
DECL|macro|BM_41_55
mdefine_line|#define BM_41_55 BM_55_41
DECL|macro|BM_56_41
mdefine_line|#define BM_56_41 0x01fffe0000000000
DECL|macro|BM_41_56
mdefine_line|#define BM_41_56 BM_56_41
DECL|macro|BM_57_41
mdefine_line|#define BM_57_41 0x03fffe0000000000
DECL|macro|BM_41_57
mdefine_line|#define BM_41_57 BM_57_41
DECL|macro|BM_58_41
mdefine_line|#define BM_58_41 0x07fffe0000000000
DECL|macro|BM_41_58
mdefine_line|#define BM_41_58 BM_58_41
DECL|macro|BM_59_41
mdefine_line|#define BM_59_41 0x0ffffe0000000000
DECL|macro|BM_41_59
mdefine_line|#define BM_41_59 BM_59_41
DECL|macro|BM_60_41
mdefine_line|#define BM_60_41 0x1ffffe0000000000
DECL|macro|BM_41_60
mdefine_line|#define BM_41_60 BM_60_41
DECL|macro|BM_61_41
mdefine_line|#define BM_61_41 0x3ffffe0000000000
DECL|macro|BM_41_61
mdefine_line|#define BM_41_61 BM_61_41
DECL|macro|BM_62_41
mdefine_line|#define BM_62_41 0x7ffffe0000000000
DECL|macro|BM_41_62
mdefine_line|#define BM_41_62 BM_62_41
DECL|macro|BM_63_41
mdefine_line|#define BM_63_41 0xfffffe0000000000
DECL|macro|BM_41_63
mdefine_line|#define BM_41_63 BM_63_41
DECL|macro|BM_42_42
mdefine_line|#define BM_42_42 0x0000040000000000
DECL|macro|BM_43_42
mdefine_line|#define BM_43_42 0x00000c0000000000
DECL|macro|BM_42_43
mdefine_line|#define BM_42_43 BM_43_42
DECL|macro|BM_44_42
mdefine_line|#define BM_44_42 0x00001c0000000000
DECL|macro|BM_42_44
mdefine_line|#define BM_42_44 BM_44_42
DECL|macro|BM_45_42
mdefine_line|#define BM_45_42 0x00003c0000000000
DECL|macro|BM_42_45
mdefine_line|#define BM_42_45 BM_45_42
DECL|macro|BM_46_42
mdefine_line|#define BM_46_42 0x00007c0000000000
DECL|macro|BM_42_46
mdefine_line|#define BM_42_46 BM_46_42
DECL|macro|BM_47_42
mdefine_line|#define BM_47_42 0x0000fc0000000000
DECL|macro|BM_42_47
mdefine_line|#define BM_42_47 BM_47_42
DECL|macro|BM_48_42
mdefine_line|#define BM_48_42 0x0001fc0000000000
DECL|macro|BM_42_48
mdefine_line|#define BM_42_48 BM_48_42
DECL|macro|BM_49_42
mdefine_line|#define BM_49_42 0x0003fc0000000000
DECL|macro|BM_42_49
mdefine_line|#define BM_42_49 BM_49_42
DECL|macro|BM_50_42
mdefine_line|#define BM_50_42 0x0007fc0000000000
DECL|macro|BM_42_50
mdefine_line|#define BM_42_50 BM_50_42
DECL|macro|BM_51_42
mdefine_line|#define BM_51_42 0x000ffc0000000000
DECL|macro|BM_42_51
mdefine_line|#define BM_42_51 BM_51_42
DECL|macro|BM_52_42
mdefine_line|#define BM_52_42 0x001ffc0000000000
DECL|macro|BM_42_52
mdefine_line|#define BM_42_52 BM_52_42
DECL|macro|BM_53_42
mdefine_line|#define BM_53_42 0x003ffc0000000000
DECL|macro|BM_42_53
mdefine_line|#define BM_42_53 BM_53_42
DECL|macro|BM_54_42
mdefine_line|#define BM_54_42 0x007ffc0000000000
DECL|macro|BM_42_54
mdefine_line|#define BM_42_54 BM_54_42
DECL|macro|BM_55_42
mdefine_line|#define BM_55_42 0x00fffc0000000000
DECL|macro|BM_42_55
mdefine_line|#define BM_42_55 BM_55_42
DECL|macro|BM_56_42
mdefine_line|#define BM_56_42 0x01fffc0000000000
DECL|macro|BM_42_56
mdefine_line|#define BM_42_56 BM_56_42
DECL|macro|BM_57_42
mdefine_line|#define BM_57_42 0x03fffc0000000000
DECL|macro|BM_42_57
mdefine_line|#define BM_42_57 BM_57_42
DECL|macro|BM_58_42
mdefine_line|#define BM_58_42 0x07fffc0000000000
DECL|macro|BM_42_58
mdefine_line|#define BM_42_58 BM_58_42
DECL|macro|BM_59_42
mdefine_line|#define BM_59_42 0x0ffffc0000000000
DECL|macro|BM_42_59
mdefine_line|#define BM_42_59 BM_59_42
DECL|macro|BM_60_42
mdefine_line|#define BM_60_42 0x1ffffc0000000000
DECL|macro|BM_42_60
mdefine_line|#define BM_42_60 BM_60_42
DECL|macro|BM_61_42
mdefine_line|#define BM_61_42 0x3ffffc0000000000
DECL|macro|BM_42_61
mdefine_line|#define BM_42_61 BM_61_42
DECL|macro|BM_62_42
mdefine_line|#define BM_62_42 0x7ffffc0000000000
DECL|macro|BM_42_62
mdefine_line|#define BM_42_62 BM_62_42
DECL|macro|BM_63_42
mdefine_line|#define BM_63_42 0xfffffc0000000000
DECL|macro|BM_42_63
mdefine_line|#define BM_42_63 BM_63_42
DECL|macro|BM_43_43
mdefine_line|#define BM_43_43 0x0000080000000000
DECL|macro|BM_44_43
mdefine_line|#define BM_44_43 0x0000180000000000
DECL|macro|BM_43_44
mdefine_line|#define BM_43_44 BM_44_43
DECL|macro|BM_45_43
mdefine_line|#define BM_45_43 0x0000380000000000
DECL|macro|BM_43_45
mdefine_line|#define BM_43_45 BM_45_43
DECL|macro|BM_46_43
mdefine_line|#define BM_46_43 0x0000780000000000
DECL|macro|BM_43_46
mdefine_line|#define BM_43_46 BM_46_43
DECL|macro|BM_47_43
mdefine_line|#define BM_47_43 0x0000f80000000000
DECL|macro|BM_43_47
mdefine_line|#define BM_43_47 BM_47_43
DECL|macro|BM_48_43
mdefine_line|#define BM_48_43 0x0001f80000000000
DECL|macro|BM_43_48
mdefine_line|#define BM_43_48 BM_48_43
DECL|macro|BM_49_43
mdefine_line|#define BM_49_43 0x0003f80000000000
DECL|macro|BM_43_49
mdefine_line|#define BM_43_49 BM_49_43
DECL|macro|BM_50_43
mdefine_line|#define BM_50_43 0x0007f80000000000
DECL|macro|BM_43_50
mdefine_line|#define BM_43_50 BM_50_43
DECL|macro|BM_51_43
mdefine_line|#define BM_51_43 0x000ff80000000000
DECL|macro|BM_43_51
mdefine_line|#define BM_43_51 BM_51_43
DECL|macro|BM_52_43
mdefine_line|#define BM_52_43 0x001ff80000000000
DECL|macro|BM_43_52
mdefine_line|#define BM_43_52 BM_52_43
DECL|macro|BM_53_43
mdefine_line|#define BM_53_43 0x003ff80000000000
DECL|macro|BM_43_53
mdefine_line|#define BM_43_53 BM_53_43
DECL|macro|BM_54_43
mdefine_line|#define BM_54_43 0x007ff80000000000
DECL|macro|BM_43_54
mdefine_line|#define BM_43_54 BM_54_43
DECL|macro|BM_55_43
mdefine_line|#define BM_55_43 0x00fff80000000000
DECL|macro|BM_43_55
mdefine_line|#define BM_43_55 BM_55_43
DECL|macro|BM_56_43
mdefine_line|#define BM_56_43 0x01fff80000000000
DECL|macro|BM_43_56
mdefine_line|#define BM_43_56 BM_56_43
DECL|macro|BM_57_43
mdefine_line|#define BM_57_43 0x03fff80000000000
DECL|macro|BM_43_57
mdefine_line|#define BM_43_57 BM_57_43
DECL|macro|BM_58_43
mdefine_line|#define BM_58_43 0x07fff80000000000
DECL|macro|BM_43_58
mdefine_line|#define BM_43_58 BM_58_43
DECL|macro|BM_59_43
mdefine_line|#define BM_59_43 0x0ffff80000000000
DECL|macro|BM_43_59
mdefine_line|#define BM_43_59 BM_59_43
DECL|macro|BM_60_43
mdefine_line|#define BM_60_43 0x1ffff80000000000
DECL|macro|BM_43_60
mdefine_line|#define BM_43_60 BM_60_43
DECL|macro|BM_61_43
mdefine_line|#define BM_61_43 0x3ffff80000000000
DECL|macro|BM_43_61
mdefine_line|#define BM_43_61 BM_61_43
DECL|macro|BM_62_43
mdefine_line|#define BM_62_43 0x7ffff80000000000
DECL|macro|BM_43_62
mdefine_line|#define BM_43_62 BM_62_43
DECL|macro|BM_63_43
mdefine_line|#define BM_63_43 0xfffff80000000000
DECL|macro|BM_43_63
mdefine_line|#define BM_43_63 BM_63_43
DECL|macro|BM_44_44
mdefine_line|#define BM_44_44 0x0000100000000000
DECL|macro|BM_45_44
mdefine_line|#define BM_45_44 0x0000300000000000
DECL|macro|BM_44_45
mdefine_line|#define BM_44_45 BM_45_44
DECL|macro|BM_46_44
mdefine_line|#define BM_46_44 0x0000700000000000
DECL|macro|BM_44_46
mdefine_line|#define BM_44_46 BM_46_44
DECL|macro|BM_47_44
mdefine_line|#define BM_47_44 0x0000f00000000000
DECL|macro|BM_44_47
mdefine_line|#define BM_44_47 BM_47_44
DECL|macro|BM_48_44
mdefine_line|#define BM_48_44 0x0001f00000000000
DECL|macro|BM_44_48
mdefine_line|#define BM_44_48 BM_48_44
DECL|macro|BM_49_44
mdefine_line|#define BM_49_44 0x0003f00000000000
DECL|macro|BM_44_49
mdefine_line|#define BM_44_49 BM_49_44
DECL|macro|BM_50_44
mdefine_line|#define BM_50_44 0x0007f00000000000
DECL|macro|BM_44_50
mdefine_line|#define BM_44_50 BM_50_44
DECL|macro|BM_51_44
mdefine_line|#define BM_51_44 0x000ff00000000000
DECL|macro|BM_44_51
mdefine_line|#define BM_44_51 BM_51_44
DECL|macro|BM_52_44
mdefine_line|#define BM_52_44 0x001ff00000000000
DECL|macro|BM_44_52
mdefine_line|#define BM_44_52 BM_52_44
DECL|macro|BM_53_44
mdefine_line|#define BM_53_44 0x003ff00000000000
DECL|macro|BM_44_53
mdefine_line|#define BM_44_53 BM_53_44
DECL|macro|BM_54_44
mdefine_line|#define BM_54_44 0x007ff00000000000
DECL|macro|BM_44_54
mdefine_line|#define BM_44_54 BM_54_44
DECL|macro|BM_55_44
mdefine_line|#define BM_55_44 0x00fff00000000000
DECL|macro|BM_44_55
mdefine_line|#define BM_44_55 BM_55_44
DECL|macro|BM_56_44
mdefine_line|#define BM_56_44 0x01fff00000000000
DECL|macro|BM_44_56
mdefine_line|#define BM_44_56 BM_56_44
DECL|macro|BM_57_44
mdefine_line|#define BM_57_44 0x03fff00000000000
DECL|macro|BM_44_57
mdefine_line|#define BM_44_57 BM_57_44
DECL|macro|BM_58_44
mdefine_line|#define BM_58_44 0x07fff00000000000
DECL|macro|BM_44_58
mdefine_line|#define BM_44_58 BM_58_44
DECL|macro|BM_59_44
mdefine_line|#define BM_59_44 0x0ffff00000000000
DECL|macro|BM_44_59
mdefine_line|#define BM_44_59 BM_59_44
DECL|macro|BM_60_44
mdefine_line|#define BM_60_44 0x1ffff00000000000
DECL|macro|BM_44_60
mdefine_line|#define BM_44_60 BM_60_44
DECL|macro|BM_61_44
mdefine_line|#define BM_61_44 0x3ffff00000000000
DECL|macro|BM_44_61
mdefine_line|#define BM_44_61 BM_61_44
DECL|macro|BM_62_44
mdefine_line|#define BM_62_44 0x7ffff00000000000
DECL|macro|BM_44_62
mdefine_line|#define BM_44_62 BM_62_44
DECL|macro|BM_63_44
mdefine_line|#define BM_63_44 0xfffff00000000000
DECL|macro|BM_44_63
mdefine_line|#define BM_44_63 BM_63_44
DECL|macro|BM_45_45
mdefine_line|#define BM_45_45 0x0000200000000000
DECL|macro|BM_46_45
mdefine_line|#define BM_46_45 0x0000600000000000
DECL|macro|BM_45_46
mdefine_line|#define BM_45_46 BM_46_45
DECL|macro|BM_47_45
mdefine_line|#define BM_47_45 0x0000e00000000000
DECL|macro|BM_45_47
mdefine_line|#define BM_45_47 BM_47_45
DECL|macro|BM_48_45
mdefine_line|#define BM_48_45 0x0001e00000000000
DECL|macro|BM_45_48
mdefine_line|#define BM_45_48 BM_48_45
DECL|macro|BM_49_45
mdefine_line|#define BM_49_45 0x0003e00000000000
DECL|macro|BM_45_49
mdefine_line|#define BM_45_49 BM_49_45
DECL|macro|BM_50_45
mdefine_line|#define BM_50_45 0x0007e00000000000
DECL|macro|BM_45_50
mdefine_line|#define BM_45_50 BM_50_45
DECL|macro|BM_51_45
mdefine_line|#define BM_51_45 0x000fe00000000000
DECL|macro|BM_45_51
mdefine_line|#define BM_45_51 BM_51_45
DECL|macro|BM_52_45
mdefine_line|#define BM_52_45 0x001fe00000000000
DECL|macro|BM_45_52
mdefine_line|#define BM_45_52 BM_52_45
DECL|macro|BM_53_45
mdefine_line|#define BM_53_45 0x003fe00000000000
DECL|macro|BM_45_53
mdefine_line|#define BM_45_53 BM_53_45
DECL|macro|BM_54_45
mdefine_line|#define BM_54_45 0x007fe00000000000
DECL|macro|BM_45_54
mdefine_line|#define BM_45_54 BM_54_45
DECL|macro|BM_55_45
mdefine_line|#define BM_55_45 0x00ffe00000000000
DECL|macro|BM_45_55
mdefine_line|#define BM_45_55 BM_55_45
DECL|macro|BM_56_45
mdefine_line|#define BM_56_45 0x01ffe00000000000
DECL|macro|BM_45_56
mdefine_line|#define BM_45_56 BM_56_45
DECL|macro|BM_57_45
mdefine_line|#define BM_57_45 0x03ffe00000000000
DECL|macro|BM_45_57
mdefine_line|#define BM_45_57 BM_57_45
DECL|macro|BM_58_45
mdefine_line|#define BM_58_45 0x07ffe00000000000
DECL|macro|BM_45_58
mdefine_line|#define BM_45_58 BM_58_45
DECL|macro|BM_59_45
mdefine_line|#define BM_59_45 0x0fffe00000000000
DECL|macro|BM_45_59
mdefine_line|#define BM_45_59 BM_59_45
DECL|macro|BM_60_45
mdefine_line|#define BM_60_45 0x1fffe00000000000
DECL|macro|BM_45_60
mdefine_line|#define BM_45_60 BM_60_45
DECL|macro|BM_61_45
mdefine_line|#define BM_61_45 0x3fffe00000000000
DECL|macro|BM_45_61
mdefine_line|#define BM_45_61 BM_61_45
DECL|macro|BM_62_45
mdefine_line|#define BM_62_45 0x7fffe00000000000
DECL|macro|BM_45_62
mdefine_line|#define BM_45_62 BM_62_45
DECL|macro|BM_63_45
mdefine_line|#define BM_63_45 0xffffe00000000000
DECL|macro|BM_45_63
mdefine_line|#define BM_45_63 BM_63_45
DECL|macro|BM_46_46
mdefine_line|#define BM_46_46 0x0000400000000000
DECL|macro|BM_47_46
mdefine_line|#define BM_47_46 0x0000c00000000000
DECL|macro|BM_46_47
mdefine_line|#define BM_46_47 BM_47_46
DECL|macro|BM_48_46
mdefine_line|#define BM_48_46 0x0001c00000000000
DECL|macro|BM_46_48
mdefine_line|#define BM_46_48 BM_48_46
DECL|macro|BM_49_46
mdefine_line|#define BM_49_46 0x0003c00000000000
DECL|macro|BM_46_49
mdefine_line|#define BM_46_49 BM_49_46
DECL|macro|BM_50_46
mdefine_line|#define BM_50_46 0x0007c00000000000
DECL|macro|BM_46_50
mdefine_line|#define BM_46_50 BM_50_46
DECL|macro|BM_51_46
mdefine_line|#define BM_51_46 0x000fc00000000000
DECL|macro|BM_46_51
mdefine_line|#define BM_46_51 BM_51_46
DECL|macro|BM_52_46
mdefine_line|#define BM_52_46 0x001fc00000000000
DECL|macro|BM_46_52
mdefine_line|#define BM_46_52 BM_52_46
DECL|macro|BM_53_46
mdefine_line|#define BM_53_46 0x003fc00000000000
DECL|macro|BM_46_53
mdefine_line|#define BM_46_53 BM_53_46
DECL|macro|BM_54_46
mdefine_line|#define BM_54_46 0x007fc00000000000
DECL|macro|BM_46_54
mdefine_line|#define BM_46_54 BM_54_46
DECL|macro|BM_55_46
mdefine_line|#define BM_55_46 0x00ffc00000000000
DECL|macro|BM_46_55
mdefine_line|#define BM_46_55 BM_55_46
DECL|macro|BM_56_46
mdefine_line|#define BM_56_46 0x01ffc00000000000
DECL|macro|BM_46_56
mdefine_line|#define BM_46_56 BM_56_46
DECL|macro|BM_57_46
mdefine_line|#define BM_57_46 0x03ffc00000000000
DECL|macro|BM_46_57
mdefine_line|#define BM_46_57 BM_57_46
DECL|macro|BM_58_46
mdefine_line|#define BM_58_46 0x07ffc00000000000
DECL|macro|BM_46_58
mdefine_line|#define BM_46_58 BM_58_46
DECL|macro|BM_59_46
mdefine_line|#define BM_59_46 0x0fffc00000000000
DECL|macro|BM_46_59
mdefine_line|#define BM_46_59 BM_59_46
DECL|macro|BM_60_46
mdefine_line|#define BM_60_46 0x1fffc00000000000
DECL|macro|BM_46_60
mdefine_line|#define BM_46_60 BM_60_46
DECL|macro|BM_61_46
mdefine_line|#define BM_61_46 0x3fffc00000000000
DECL|macro|BM_46_61
mdefine_line|#define BM_46_61 BM_61_46
DECL|macro|BM_62_46
mdefine_line|#define BM_62_46 0x7fffc00000000000
DECL|macro|BM_46_62
mdefine_line|#define BM_46_62 BM_62_46
DECL|macro|BM_63_46
mdefine_line|#define BM_63_46 0xffffc00000000000
DECL|macro|BM_46_63
mdefine_line|#define BM_46_63 BM_63_46
DECL|macro|BM_47_47
mdefine_line|#define BM_47_47 0x0000800000000000
DECL|macro|BM_48_47
mdefine_line|#define BM_48_47 0x0001800000000000
DECL|macro|BM_47_48
mdefine_line|#define BM_47_48 BM_48_47
DECL|macro|BM_49_47
mdefine_line|#define BM_49_47 0x0003800000000000
DECL|macro|BM_47_49
mdefine_line|#define BM_47_49 BM_49_47
DECL|macro|BM_50_47
mdefine_line|#define BM_50_47 0x0007800000000000
DECL|macro|BM_47_50
mdefine_line|#define BM_47_50 BM_50_47
DECL|macro|BM_51_47
mdefine_line|#define BM_51_47 0x000f800000000000
DECL|macro|BM_47_51
mdefine_line|#define BM_47_51 BM_51_47
DECL|macro|BM_52_47
mdefine_line|#define BM_52_47 0x001f800000000000
DECL|macro|BM_47_52
mdefine_line|#define BM_47_52 BM_52_47
DECL|macro|BM_53_47
mdefine_line|#define BM_53_47 0x003f800000000000
DECL|macro|BM_47_53
mdefine_line|#define BM_47_53 BM_53_47
DECL|macro|BM_54_47
mdefine_line|#define BM_54_47 0x007f800000000000
DECL|macro|BM_47_54
mdefine_line|#define BM_47_54 BM_54_47
DECL|macro|BM_55_47
mdefine_line|#define BM_55_47 0x00ff800000000000
DECL|macro|BM_47_55
mdefine_line|#define BM_47_55 BM_55_47
DECL|macro|BM_56_47
mdefine_line|#define BM_56_47 0x01ff800000000000
DECL|macro|BM_47_56
mdefine_line|#define BM_47_56 BM_56_47
DECL|macro|BM_57_47
mdefine_line|#define BM_57_47 0x03ff800000000000
DECL|macro|BM_47_57
mdefine_line|#define BM_47_57 BM_57_47
DECL|macro|BM_58_47
mdefine_line|#define BM_58_47 0x07ff800000000000
DECL|macro|BM_47_58
mdefine_line|#define BM_47_58 BM_58_47
DECL|macro|BM_59_47
mdefine_line|#define BM_59_47 0x0fff800000000000
DECL|macro|BM_47_59
mdefine_line|#define BM_47_59 BM_59_47
DECL|macro|BM_60_47
mdefine_line|#define BM_60_47 0x1fff800000000000
DECL|macro|BM_47_60
mdefine_line|#define BM_47_60 BM_60_47
DECL|macro|BM_61_47
mdefine_line|#define BM_61_47 0x3fff800000000000
DECL|macro|BM_47_61
mdefine_line|#define BM_47_61 BM_61_47
DECL|macro|BM_62_47
mdefine_line|#define BM_62_47 0x7fff800000000000
DECL|macro|BM_47_62
mdefine_line|#define BM_47_62 BM_62_47
DECL|macro|BM_63_47
mdefine_line|#define BM_63_47 0xffff800000000000
DECL|macro|BM_47_63
mdefine_line|#define BM_47_63 BM_63_47
DECL|macro|BM_48_48
mdefine_line|#define BM_48_48 0x0001000000000000
DECL|macro|BM_49_48
mdefine_line|#define BM_49_48 0x0003000000000000
DECL|macro|BM_48_49
mdefine_line|#define BM_48_49 BM_49_48
DECL|macro|BM_50_48
mdefine_line|#define BM_50_48 0x0007000000000000
DECL|macro|BM_48_50
mdefine_line|#define BM_48_50 BM_50_48
DECL|macro|BM_51_48
mdefine_line|#define BM_51_48 0x000f000000000000
DECL|macro|BM_48_51
mdefine_line|#define BM_48_51 BM_51_48
DECL|macro|BM_52_48
mdefine_line|#define BM_52_48 0x001f000000000000
DECL|macro|BM_48_52
mdefine_line|#define BM_48_52 BM_52_48
DECL|macro|BM_53_48
mdefine_line|#define BM_53_48 0x003f000000000000
DECL|macro|BM_48_53
mdefine_line|#define BM_48_53 BM_53_48
DECL|macro|BM_54_48
mdefine_line|#define BM_54_48 0x007f000000000000
DECL|macro|BM_48_54
mdefine_line|#define BM_48_54 BM_54_48
DECL|macro|BM_55_48
mdefine_line|#define BM_55_48 0x00ff000000000000
DECL|macro|BM_48_55
mdefine_line|#define BM_48_55 BM_55_48
DECL|macro|BM_56_48
mdefine_line|#define BM_56_48 0x01ff000000000000
DECL|macro|BM_48_56
mdefine_line|#define BM_48_56 BM_56_48
DECL|macro|BM_57_48
mdefine_line|#define BM_57_48 0x03ff000000000000
DECL|macro|BM_48_57
mdefine_line|#define BM_48_57 BM_57_48
DECL|macro|BM_58_48
mdefine_line|#define BM_58_48 0x07ff000000000000
DECL|macro|BM_48_58
mdefine_line|#define BM_48_58 BM_58_48
DECL|macro|BM_59_48
mdefine_line|#define BM_59_48 0x0fff000000000000
DECL|macro|BM_48_59
mdefine_line|#define BM_48_59 BM_59_48
DECL|macro|BM_60_48
mdefine_line|#define BM_60_48 0x1fff000000000000
DECL|macro|BM_48_60
mdefine_line|#define BM_48_60 BM_60_48
DECL|macro|BM_61_48
mdefine_line|#define BM_61_48 0x3fff000000000000
DECL|macro|BM_48_61
mdefine_line|#define BM_48_61 BM_61_48
DECL|macro|BM_62_48
mdefine_line|#define BM_62_48 0x7fff000000000000
DECL|macro|BM_48_62
mdefine_line|#define BM_48_62 BM_62_48
DECL|macro|BM_63_48
mdefine_line|#define BM_63_48 0xffff000000000000
DECL|macro|BM_48_63
mdefine_line|#define BM_48_63 BM_63_48
DECL|macro|BM_49_49
mdefine_line|#define BM_49_49 0x0002000000000000
DECL|macro|BM_50_49
mdefine_line|#define BM_50_49 0x0006000000000000
DECL|macro|BM_49_50
mdefine_line|#define BM_49_50 BM_50_49
DECL|macro|BM_51_49
mdefine_line|#define BM_51_49 0x000e000000000000
DECL|macro|BM_49_51
mdefine_line|#define BM_49_51 BM_51_49
DECL|macro|BM_52_49
mdefine_line|#define BM_52_49 0x001e000000000000
DECL|macro|BM_49_52
mdefine_line|#define BM_49_52 BM_52_49
DECL|macro|BM_53_49
mdefine_line|#define BM_53_49 0x003e000000000000
DECL|macro|BM_49_53
mdefine_line|#define BM_49_53 BM_53_49
DECL|macro|BM_54_49
mdefine_line|#define BM_54_49 0x007e000000000000
DECL|macro|BM_49_54
mdefine_line|#define BM_49_54 BM_54_49
DECL|macro|BM_55_49
mdefine_line|#define BM_55_49 0x00fe000000000000
DECL|macro|BM_49_55
mdefine_line|#define BM_49_55 BM_55_49
DECL|macro|BM_56_49
mdefine_line|#define BM_56_49 0x01fe000000000000
DECL|macro|BM_49_56
mdefine_line|#define BM_49_56 BM_56_49
DECL|macro|BM_57_49
mdefine_line|#define BM_57_49 0x03fe000000000000
DECL|macro|BM_49_57
mdefine_line|#define BM_49_57 BM_57_49
DECL|macro|BM_58_49
mdefine_line|#define BM_58_49 0x07fe000000000000
DECL|macro|BM_49_58
mdefine_line|#define BM_49_58 BM_58_49
DECL|macro|BM_59_49
mdefine_line|#define BM_59_49 0x0ffe000000000000
DECL|macro|BM_49_59
mdefine_line|#define BM_49_59 BM_59_49
DECL|macro|BM_60_49
mdefine_line|#define BM_60_49 0x1ffe000000000000
DECL|macro|BM_49_60
mdefine_line|#define BM_49_60 BM_60_49
DECL|macro|BM_61_49
mdefine_line|#define BM_61_49 0x3ffe000000000000
DECL|macro|BM_49_61
mdefine_line|#define BM_49_61 BM_61_49
DECL|macro|BM_62_49
mdefine_line|#define BM_62_49 0x7ffe000000000000
DECL|macro|BM_49_62
mdefine_line|#define BM_49_62 BM_62_49
DECL|macro|BM_63_49
mdefine_line|#define BM_63_49 0xfffe000000000000
DECL|macro|BM_49_63
mdefine_line|#define BM_49_63 BM_63_49
DECL|macro|BM_50_50
mdefine_line|#define BM_50_50 0x0004000000000000
DECL|macro|BM_51_50
mdefine_line|#define BM_51_50 0x000c000000000000
DECL|macro|BM_50_51
mdefine_line|#define BM_50_51 BM_51_50
DECL|macro|BM_52_50
mdefine_line|#define BM_52_50 0x001c000000000000
DECL|macro|BM_50_52
mdefine_line|#define BM_50_52 BM_52_50
DECL|macro|BM_53_50
mdefine_line|#define BM_53_50 0x003c000000000000
DECL|macro|BM_50_53
mdefine_line|#define BM_50_53 BM_53_50
DECL|macro|BM_54_50
mdefine_line|#define BM_54_50 0x007c000000000000
DECL|macro|BM_50_54
mdefine_line|#define BM_50_54 BM_54_50
DECL|macro|BM_55_50
mdefine_line|#define BM_55_50 0x00fc000000000000
DECL|macro|BM_50_55
mdefine_line|#define BM_50_55 BM_55_50
DECL|macro|BM_56_50
mdefine_line|#define BM_56_50 0x01fc000000000000
DECL|macro|BM_50_56
mdefine_line|#define BM_50_56 BM_56_50
DECL|macro|BM_57_50
mdefine_line|#define BM_57_50 0x03fc000000000000
DECL|macro|BM_50_57
mdefine_line|#define BM_50_57 BM_57_50
DECL|macro|BM_58_50
mdefine_line|#define BM_58_50 0x07fc000000000000
DECL|macro|BM_50_58
mdefine_line|#define BM_50_58 BM_58_50
DECL|macro|BM_59_50
mdefine_line|#define BM_59_50 0x0ffc000000000000
DECL|macro|BM_50_59
mdefine_line|#define BM_50_59 BM_59_50
DECL|macro|BM_60_50
mdefine_line|#define BM_60_50 0x1ffc000000000000
DECL|macro|BM_50_60
mdefine_line|#define BM_50_60 BM_60_50
DECL|macro|BM_61_50
mdefine_line|#define BM_61_50 0x3ffc000000000000
DECL|macro|BM_50_61
mdefine_line|#define BM_50_61 BM_61_50
DECL|macro|BM_62_50
mdefine_line|#define BM_62_50 0x7ffc000000000000
DECL|macro|BM_50_62
mdefine_line|#define BM_50_62 BM_62_50
DECL|macro|BM_63_50
mdefine_line|#define BM_63_50 0xfffc000000000000
DECL|macro|BM_50_63
mdefine_line|#define BM_50_63 BM_63_50
DECL|macro|BM_51_51
mdefine_line|#define BM_51_51 0x0008000000000000
DECL|macro|BM_52_51
mdefine_line|#define BM_52_51 0x0018000000000000
DECL|macro|BM_51_52
mdefine_line|#define BM_51_52 BM_52_51
DECL|macro|BM_53_51
mdefine_line|#define BM_53_51 0x0038000000000000
DECL|macro|BM_51_53
mdefine_line|#define BM_51_53 BM_53_51
DECL|macro|BM_54_51
mdefine_line|#define BM_54_51 0x0078000000000000
DECL|macro|BM_51_54
mdefine_line|#define BM_51_54 BM_54_51
DECL|macro|BM_55_51
mdefine_line|#define BM_55_51 0x00f8000000000000
DECL|macro|BM_51_55
mdefine_line|#define BM_51_55 BM_55_51
DECL|macro|BM_56_51
mdefine_line|#define BM_56_51 0x01f8000000000000
DECL|macro|BM_51_56
mdefine_line|#define BM_51_56 BM_56_51
DECL|macro|BM_57_51
mdefine_line|#define BM_57_51 0x03f8000000000000
DECL|macro|BM_51_57
mdefine_line|#define BM_51_57 BM_57_51
DECL|macro|BM_58_51
mdefine_line|#define BM_58_51 0x07f8000000000000
DECL|macro|BM_51_58
mdefine_line|#define BM_51_58 BM_58_51
DECL|macro|BM_59_51
mdefine_line|#define BM_59_51 0x0ff8000000000000
DECL|macro|BM_51_59
mdefine_line|#define BM_51_59 BM_59_51
DECL|macro|BM_60_51
mdefine_line|#define BM_60_51 0x1ff8000000000000
DECL|macro|BM_51_60
mdefine_line|#define BM_51_60 BM_60_51
DECL|macro|BM_61_51
mdefine_line|#define BM_61_51 0x3ff8000000000000
DECL|macro|BM_51_61
mdefine_line|#define BM_51_61 BM_61_51
DECL|macro|BM_62_51
mdefine_line|#define BM_62_51 0x7ff8000000000000
DECL|macro|BM_51_62
mdefine_line|#define BM_51_62 BM_62_51
DECL|macro|BM_63_51
mdefine_line|#define BM_63_51 0xfff8000000000000
DECL|macro|BM_51_63
mdefine_line|#define BM_51_63 BM_63_51
DECL|macro|BM_52_52
mdefine_line|#define BM_52_52 0x0010000000000000
DECL|macro|BM_53_52
mdefine_line|#define BM_53_52 0x0030000000000000
DECL|macro|BM_52_53
mdefine_line|#define BM_52_53 BM_53_52
DECL|macro|BM_54_52
mdefine_line|#define BM_54_52 0x0070000000000000
DECL|macro|BM_52_54
mdefine_line|#define BM_52_54 BM_54_52
DECL|macro|BM_55_52
mdefine_line|#define BM_55_52 0x00f0000000000000
DECL|macro|BM_52_55
mdefine_line|#define BM_52_55 BM_55_52
DECL|macro|BM_56_52
mdefine_line|#define BM_56_52 0x01f0000000000000
DECL|macro|BM_52_56
mdefine_line|#define BM_52_56 BM_56_52
DECL|macro|BM_57_52
mdefine_line|#define BM_57_52 0x03f0000000000000
DECL|macro|BM_52_57
mdefine_line|#define BM_52_57 BM_57_52
DECL|macro|BM_58_52
mdefine_line|#define BM_58_52 0x07f0000000000000
DECL|macro|BM_52_58
mdefine_line|#define BM_52_58 BM_58_52
DECL|macro|BM_59_52
mdefine_line|#define BM_59_52 0x0ff0000000000000
DECL|macro|BM_52_59
mdefine_line|#define BM_52_59 BM_59_52
DECL|macro|BM_60_52
mdefine_line|#define BM_60_52 0x1ff0000000000000
DECL|macro|BM_52_60
mdefine_line|#define BM_52_60 BM_60_52
DECL|macro|BM_61_52
mdefine_line|#define BM_61_52 0x3ff0000000000000
DECL|macro|BM_52_61
mdefine_line|#define BM_52_61 BM_61_52
DECL|macro|BM_62_52
mdefine_line|#define BM_62_52 0x7ff0000000000000
DECL|macro|BM_52_62
mdefine_line|#define BM_52_62 BM_62_52
DECL|macro|BM_63_52
mdefine_line|#define BM_63_52 0xfff0000000000000
DECL|macro|BM_52_63
mdefine_line|#define BM_52_63 BM_63_52
DECL|macro|BM_53_53
mdefine_line|#define BM_53_53 0x0020000000000000
DECL|macro|BM_54_53
mdefine_line|#define BM_54_53 0x0060000000000000
DECL|macro|BM_53_54
mdefine_line|#define BM_53_54 BM_54_53
DECL|macro|BM_55_53
mdefine_line|#define BM_55_53 0x00e0000000000000
DECL|macro|BM_53_55
mdefine_line|#define BM_53_55 BM_55_53
DECL|macro|BM_56_53
mdefine_line|#define BM_56_53 0x01e0000000000000
DECL|macro|BM_53_56
mdefine_line|#define BM_53_56 BM_56_53
DECL|macro|BM_57_53
mdefine_line|#define BM_57_53 0x03e0000000000000
DECL|macro|BM_53_57
mdefine_line|#define BM_53_57 BM_57_53
DECL|macro|BM_58_53
mdefine_line|#define BM_58_53 0x07e0000000000000
DECL|macro|BM_53_58
mdefine_line|#define BM_53_58 BM_58_53
DECL|macro|BM_59_53
mdefine_line|#define BM_59_53 0x0fe0000000000000
DECL|macro|BM_53_59
mdefine_line|#define BM_53_59 BM_59_53
DECL|macro|BM_60_53
mdefine_line|#define BM_60_53 0x1fe0000000000000
DECL|macro|BM_53_60
mdefine_line|#define BM_53_60 BM_60_53
DECL|macro|BM_61_53
mdefine_line|#define BM_61_53 0x3fe0000000000000
DECL|macro|BM_53_61
mdefine_line|#define BM_53_61 BM_61_53
DECL|macro|BM_62_53
mdefine_line|#define BM_62_53 0x7fe0000000000000
DECL|macro|BM_53_62
mdefine_line|#define BM_53_62 BM_62_53
DECL|macro|BM_63_53
mdefine_line|#define BM_63_53 0xffe0000000000000
DECL|macro|BM_53_63
mdefine_line|#define BM_53_63 BM_63_53
DECL|macro|BM_54_54
mdefine_line|#define BM_54_54 0x0040000000000000
DECL|macro|BM_55_54
mdefine_line|#define BM_55_54 0x00c0000000000000
DECL|macro|BM_54_55
mdefine_line|#define BM_54_55 BM_55_54
DECL|macro|BM_56_54
mdefine_line|#define BM_56_54 0x01c0000000000000
DECL|macro|BM_54_56
mdefine_line|#define BM_54_56 BM_56_54
DECL|macro|BM_57_54
mdefine_line|#define BM_57_54 0x03c0000000000000
DECL|macro|BM_54_57
mdefine_line|#define BM_54_57 BM_57_54
DECL|macro|BM_58_54
mdefine_line|#define BM_58_54 0x07c0000000000000
DECL|macro|BM_54_58
mdefine_line|#define BM_54_58 BM_58_54
DECL|macro|BM_59_54
mdefine_line|#define BM_59_54 0x0fc0000000000000
DECL|macro|BM_54_59
mdefine_line|#define BM_54_59 BM_59_54
DECL|macro|BM_60_54
mdefine_line|#define BM_60_54 0x1fc0000000000000
DECL|macro|BM_54_60
mdefine_line|#define BM_54_60 BM_60_54
DECL|macro|BM_61_54
mdefine_line|#define BM_61_54 0x3fc0000000000000
DECL|macro|BM_54_61
mdefine_line|#define BM_54_61 BM_61_54
DECL|macro|BM_62_54
mdefine_line|#define BM_62_54 0x7fc0000000000000
DECL|macro|BM_54_62
mdefine_line|#define BM_54_62 BM_62_54
DECL|macro|BM_63_54
mdefine_line|#define BM_63_54 0xffc0000000000000
DECL|macro|BM_54_63
mdefine_line|#define BM_54_63 BM_63_54
DECL|macro|BM_55_55
mdefine_line|#define BM_55_55 0x0080000000000000
DECL|macro|BM_56_55
mdefine_line|#define BM_56_55 0x0180000000000000
DECL|macro|BM_55_56
mdefine_line|#define BM_55_56 BM_56_55
DECL|macro|BM_57_55
mdefine_line|#define BM_57_55 0x0380000000000000
DECL|macro|BM_55_57
mdefine_line|#define BM_55_57 BM_57_55
DECL|macro|BM_58_55
mdefine_line|#define BM_58_55 0x0780000000000000
DECL|macro|BM_55_58
mdefine_line|#define BM_55_58 BM_58_55
DECL|macro|BM_59_55
mdefine_line|#define BM_59_55 0x0f80000000000000
DECL|macro|BM_55_59
mdefine_line|#define BM_55_59 BM_59_55
DECL|macro|BM_60_55
mdefine_line|#define BM_60_55 0x1f80000000000000
DECL|macro|BM_55_60
mdefine_line|#define BM_55_60 BM_60_55
DECL|macro|BM_61_55
mdefine_line|#define BM_61_55 0x3f80000000000000
DECL|macro|BM_55_61
mdefine_line|#define BM_55_61 BM_61_55
DECL|macro|BM_62_55
mdefine_line|#define BM_62_55 0x7f80000000000000
DECL|macro|BM_55_62
mdefine_line|#define BM_55_62 BM_62_55
DECL|macro|BM_63_55
mdefine_line|#define BM_63_55 0xff80000000000000
DECL|macro|BM_55_63
mdefine_line|#define BM_55_63 BM_63_55
DECL|macro|BM_56_56
mdefine_line|#define BM_56_56 0x0100000000000000
DECL|macro|BM_57_56
mdefine_line|#define BM_57_56 0x0300000000000000
DECL|macro|BM_56_57
mdefine_line|#define BM_56_57 BM_57_56
DECL|macro|BM_58_56
mdefine_line|#define BM_58_56 0x0700000000000000
DECL|macro|BM_56_58
mdefine_line|#define BM_56_58 BM_58_56
DECL|macro|BM_59_56
mdefine_line|#define BM_59_56 0x0f00000000000000
DECL|macro|BM_56_59
mdefine_line|#define BM_56_59 BM_59_56
DECL|macro|BM_60_56
mdefine_line|#define BM_60_56 0x1f00000000000000
DECL|macro|BM_56_60
mdefine_line|#define BM_56_60 BM_60_56
DECL|macro|BM_61_56
mdefine_line|#define BM_61_56 0x3f00000000000000
DECL|macro|BM_56_61
mdefine_line|#define BM_56_61 BM_61_56
DECL|macro|BM_62_56
mdefine_line|#define BM_62_56 0x7f00000000000000
DECL|macro|BM_56_62
mdefine_line|#define BM_56_62 BM_62_56
DECL|macro|BM_63_56
mdefine_line|#define BM_63_56 0xff00000000000000
DECL|macro|BM_56_63
mdefine_line|#define BM_56_63 BM_63_56
DECL|macro|BM_57_57
mdefine_line|#define BM_57_57 0x0200000000000000
DECL|macro|BM_58_57
mdefine_line|#define BM_58_57 0x0600000000000000
DECL|macro|BM_57_58
mdefine_line|#define BM_57_58 BM_58_57
DECL|macro|BM_59_57
mdefine_line|#define BM_59_57 0x0e00000000000000
DECL|macro|BM_57_59
mdefine_line|#define BM_57_59 BM_59_57
DECL|macro|BM_60_57
mdefine_line|#define BM_60_57 0x1e00000000000000
DECL|macro|BM_57_60
mdefine_line|#define BM_57_60 BM_60_57
DECL|macro|BM_61_57
mdefine_line|#define BM_61_57 0x3e00000000000000
DECL|macro|BM_57_61
mdefine_line|#define BM_57_61 BM_61_57
DECL|macro|BM_62_57
mdefine_line|#define BM_62_57 0x7e00000000000000
DECL|macro|BM_57_62
mdefine_line|#define BM_57_62 BM_62_57
DECL|macro|BM_63_57
mdefine_line|#define BM_63_57 0xfe00000000000000
DECL|macro|BM_57_63
mdefine_line|#define BM_57_63 BM_63_57
DECL|macro|BM_58_58
mdefine_line|#define BM_58_58 0x0400000000000000
DECL|macro|BM_59_58
mdefine_line|#define BM_59_58 0x0c00000000000000
DECL|macro|BM_58_59
mdefine_line|#define BM_58_59 BM_59_58
DECL|macro|BM_60_58
mdefine_line|#define BM_60_58 0x1c00000000000000
DECL|macro|BM_58_60
mdefine_line|#define BM_58_60 BM_60_58
DECL|macro|BM_61_58
mdefine_line|#define BM_61_58 0x3c00000000000000
DECL|macro|BM_58_61
mdefine_line|#define BM_58_61 BM_61_58
DECL|macro|BM_62_58
mdefine_line|#define BM_62_58 0x7c00000000000000
DECL|macro|BM_58_62
mdefine_line|#define BM_58_62 BM_62_58
DECL|macro|BM_63_58
mdefine_line|#define BM_63_58 0xfc00000000000000
DECL|macro|BM_58_63
mdefine_line|#define BM_58_63 BM_63_58
DECL|macro|BM_59_59
mdefine_line|#define BM_59_59 0x0800000000000000
DECL|macro|BM_60_59
mdefine_line|#define BM_60_59 0x1800000000000000
DECL|macro|BM_59_60
mdefine_line|#define BM_59_60 BM_60_59
DECL|macro|BM_61_59
mdefine_line|#define BM_61_59 0x3800000000000000
DECL|macro|BM_59_61
mdefine_line|#define BM_59_61 BM_61_59
DECL|macro|BM_62_59
mdefine_line|#define BM_62_59 0x7800000000000000
DECL|macro|BM_59_62
mdefine_line|#define BM_59_62 BM_62_59
DECL|macro|BM_63_59
mdefine_line|#define BM_63_59 0xf800000000000000
DECL|macro|BM_59_63
mdefine_line|#define BM_59_63 BM_63_59
DECL|macro|BM_60_60
mdefine_line|#define BM_60_60 0x1000000000000000
DECL|macro|BM_61_60
mdefine_line|#define BM_61_60 0x3000000000000000
DECL|macro|BM_60_61
mdefine_line|#define BM_60_61 BM_61_60
DECL|macro|BM_62_60
mdefine_line|#define BM_62_60 0x7000000000000000
DECL|macro|BM_60_62
mdefine_line|#define BM_60_62 BM_62_60
DECL|macro|BM_63_60
mdefine_line|#define BM_63_60 0xf000000000000000
DECL|macro|BM_60_63
mdefine_line|#define BM_60_63 BM_63_60
DECL|macro|BM_61_61
mdefine_line|#define BM_61_61 0x2000000000000000
DECL|macro|BM_62_61
mdefine_line|#define BM_62_61 0x6000000000000000
DECL|macro|BM_61_62
mdefine_line|#define BM_61_62 BM_62_61
DECL|macro|BM_63_61
mdefine_line|#define BM_63_61 0xe000000000000000
DECL|macro|BM_61_63
mdefine_line|#define BM_61_63 BM_63_61
DECL|macro|BM_62_62
mdefine_line|#define BM_62_62 0x4000000000000000
DECL|macro|BM_63_62
mdefine_line|#define BM_63_62 0xc000000000000000
DECL|macro|BM_62_63
mdefine_line|#define BM_62_63 BM_63_62
DECL|macro|BM_63_63
mdefine_line|#define BM_63_63 0x8000000000000000
macro_line|#endif
macro_line|#endif /* __ASM_TX4927_TX4927_MIPS_H */
eof
