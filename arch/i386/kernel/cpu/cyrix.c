macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/timer.h&gt;
macro_line|#include &quot;cpu.h&quot;
multiline_comment|/*&n; * Read NSC/Cyrix DEVID registers (DIR) to get more detailed info. about the CPU&n; */
DECL|function|do_cyrix_devid
r_void
id|__init
id|do_cyrix_devid
c_func
(paren
r_int
r_char
op_star
id|dir0
comma
r_int
r_char
op_star
id|dir1
)paren
(brace
r_int
r_char
id|ccr2
comma
id|ccr3
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* we test for DEVID by checking whether CCR3 is writable */
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|ccr3
op_assign
id|getCx86
c_func
(paren
id|CX86_CCR3
)paren
suffix:semicolon
id|setCx86
c_func
(paren
id|CX86_CCR3
comma
id|ccr3
op_xor
l_int|0x80
)paren
suffix:semicolon
id|getCx86
c_func
(paren
l_int|0xc0
)paren
suffix:semicolon
multiline_comment|/* dummy to change bus */
r_if
c_cond
(paren
id|getCx86
c_func
(paren
id|CX86_CCR3
)paren
op_eq
id|ccr3
)paren
(brace
multiline_comment|/* no DEVID regs. */
id|ccr2
op_assign
id|getCx86
c_func
(paren
id|CX86_CCR2
)paren
suffix:semicolon
id|setCx86
c_func
(paren
id|CX86_CCR2
comma
id|ccr2
op_xor
l_int|0x04
)paren
suffix:semicolon
id|getCx86
c_func
(paren
l_int|0xc0
)paren
suffix:semicolon
multiline_comment|/* dummy */
r_if
c_cond
(paren
id|getCx86
c_func
(paren
id|CX86_CCR2
)paren
op_eq
id|ccr2
)paren
multiline_comment|/* old Cx486SLC/DLC */
op_star
id|dir0
op_assign
l_int|0xfd
suffix:semicolon
r_else
(brace
multiline_comment|/* Cx486S A step */
id|setCx86
c_func
(paren
id|CX86_CCR2
comma
id|ccr2
)paren
suffix:semicolon
op_star
id|dir0
op_assign
l_int|0xfe
suffix:semicolon
)brace
)brace
r_else
(brace
id|setCx86
c_func
(paren
id|CX86_CCR3
comma
id|ccr3
)paren
suffix:semicolon
multiline_comment|/* restore CCR3 */
multiline_comment|/* read DIR0 and DIR1 CPU registers */
op_star
id|dir0
op_assign
id|getCx86
c_func
(paren
id|CX86_DIR0
)paren
suffix:semicolon
op_star
id|dir1
op_assign
id|getCx86
c_func
(paren
id|CX86_DIR1
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Cx86_dir0_msb is a HACK needed by check_cx686_cpuid/slop in bugs.h in&n; * order to identify the Cyrix CPU model after we&squot;re out of setup.c&n; *&n; * Actually since bugs.h doesnt even reference this perhaps someone should&n; * fix the documentation ???&n; */
DECL|variable|__initdata
r_static
r_int
r_char
id|Cx86_dir0_msb
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|Cx86_model
(braket
)braket
(braket
l_int|9
)braket
id|__initdata
op_assign
(brace
l_string|&quot;Cx486&quot;
comma
l_string|&quot;Cx486&quot;
comma
l_string|&quot;5x86 &quot;
comma
l_string|&quot;6x86&quot;
comma
l_string|&quot;MediaGX &quot;
comma
l_string|&quot;6x86MX &quot;
comma
l_string|&quot;M II &quot;
comma
l_string|&quot;Unknown&quot;
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|Cx486_name
(braket
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
l_string|&quot;SLC&quot;
comma
l_string|&quot;DLC&quot;
comma
l_string|&quot;SLC2&quot;
comma
l_string|&quot;DLC2&quot;
comma
l_string|&quot;SRx&quot;
comma
l_string|&quot;DRx&quot;
comma
l_string|&quot;SRx2&quot;
comma
l_string|&quot;DRx2&quot;
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|Cx486S_name
(braket
)braket
(braket
l_int|4
)braket
id|__initdata
op_assign
(brace
l_string|&quot;S&quot;
comma
l_string|&quot;S2&quot;
comma
l_string|&quot;Se&quot;
comma
l_string|&quot;S2e&quot;
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|Cx486D_name
(braket
)braket
(braket
l_int|4
)braket
id|__initdata
op_assign
(brace
l_string|&quot;DX&quot;
comma
l_string|&quot;DX2&quot;
comma
l_string|&quot;?&quot;
comma
l_string|&quot;?&quot;
comma
l_string|&quot;?&quot;
comma
l_string|&quot;DX4&quot;
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|Cx86_cb
(braket
)braket
id|__initdata
op_assign
l_string|&quot;?.5x Core/Bus Clock&quot;
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|cyrix_model_mult1
(braket
)braket
id|__initdata
op_assign
l_string|&quot;12??43&quot;
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|cyrix_model_mult2
(braket
)braket
id|__initdata
op_assign
l_string|&quot;12233445&quot;
suffix:semicolon
multiline_comment|/*&n; * Reset the slow-loop (SLOP) bit on the 686(L) which is set by some old&n; * BIOSes for compatability with DOS games.  This makes the udelay loop&n; * work correctly, and improves performance.&n; *&n; * FIXME: our newer udelay uses the tsc. We dont need to frob with SLOP&n; */
r_extern
r_void
id|calibrate_delay
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
DECL|function|check_cx686_slop
r_static
r_void
id|__init
id|check_cx686_slop
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|Cx86_dir0_msb
op_eq
l_int|3
)paren
(brace
r_int
r_char
id|ccr3
comma
id|ccr5
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|ccr3
op_assign
id|getCx86
c_func
(paren
id|CX86_CCR3
)paren
suffix:semicolon
id|setCx86
c_func
(paren
id|CX86_CCR3
comma
(paren
id|ccr3
op_amp
l_int|0x0f
)paren
op_or
l_int|0x10
)paren
suffix:semicolon
multiline_comment|/* enable MAPEN  */
id|ccr5
op_assign
id|getCx86
c_func
(paren
id|CX86_CCR5
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ccr5
op_amp
l_int|2
)paren
id|setCx86
c_func
(paren
id|CX86_CCR5
comma
id|ccr5
op_amp
l_int|0xfd
)paren
suffix:semicolon
multiline_comment|/* reset SLOP */
id|setCx86
c_func
(paren
id|CX86_CCR3
comma
id|ccr3
)paren
suffix:semicolon
multiline_comment|/* disable MAPEN */
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ccr5
op_amp
l_int|2
)paren
(brace
multiline_comment|/* possible wrong calibration done */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Recalibrating delay loop with SLOP bit reset&bslash;n&quot;
)paren
suffix:semicolon
id|calibrate_delay
c_func
(paren
)paren
suffix:semicolon
id|c-&gt;loops_per_jiffy
op_assign
id|loops_per_jiffy
suffix:semicolon
)brace
)brace
)brace
DECL|function|set_cx86_reorder
r_static
r_void
id|__init
id|set_cx86_reorder
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_OOSTORE
id|u8
id|ccr3
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Enable Memory access reorder on Cyrix/NSC processor.&bslash;n&quot;
)paren
suffix:semicolon
id|ccr3
op_assign
id|getCx86
c_func
(paren
id|CX86_CCR3
)paren
suffix:semicolon
id|setCx86
c_func
(paren
id|CX86_CCR3
comma
(paren
id|ccr3
op_amp
l_int|0x0f
)paren
op_or
l_int|0x10
)paren
suffix:semicolon
multiline_comment|/* enable MAPEN&#xfffd; */
multiline_comment|/* Load/Store Serialize to mem access disable (=reorder it)&#xfffd; */
id|setCx86
c_func
(paren
id|CX86_PCR0
comma
id|getCx86
c_func
(paren
id|CX86_PCR0
)paren
op_amp
op_complement
l_int|0x80
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NOHIGHMEM
multiline_comment|/* set load/store serialize from 1GB to 4GB */
id|ccr3
op_or_assign
l_int|0xe0
suffix:semicolon
macro_line|#endif
id|setCx86
c_func
(paren
id|CX86_CCR3
comma
id|ccr3
)paren
suffix:semicolon
macro_line|#endif&t;
)brace
DECL|function|set_cx86_memwb
r_static
r_void
id|__init
id|set_cx86_memwb
c_func
(paren
r_void
)paren
(brace
id|u32
id|cr0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Enable Memory-Write-back mode on Cyrix/NSC processor.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* CCR2 bit 2: unlock NW bit */
id|setCx86
c_func
(paren
id|CX86_CCR2
comma
id|getCx86
c_func
(paren
id|CX86_CCR2
)paren
op_amp
op_complement
l_int|0x04
)paren
suffix:semicolon
multiline_comment|/* set &squot;Not Write-through&squot; */
id|cr0
op_assign
l_int|0x20000000
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movl %%cr0,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;orl %0,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;movl %%eax,%%cr0&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|cr0
)paren
suffix:colon
l_string|&quot;ax&quot;
)paren
suffix:semicolon
multiline_comment|/* CCR2 bit 2: lock NW bit and set WT1 */
id|setCx86
c_func
(paren
id|CX86_CCR2
comma
id|getCx86
c_func
(paren
id|CX86_CCR2
)paren
op_or
l_int|0x14
)paren
suffix:semicolon
)brace
DECL|function|set_cx86_inc
r_static
r_void
id|__init
id|set_cx86_inc
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|ccr3
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Enable Incrementor on Cyrix/NSC processor.&bslash;n&quot;
)paren
suffix:semicolon
id|ccr3
op_assign
id|getCx86
c_func
(paren
id|CX86_CCR3
)paren
suffix:semicolon
id|setCx86
c_func
(paren
id|CX86_CCR3
comma
(paren
id|ccr3
op_amp
l_int|0x0f
)paren
op_or
l_int|0x10
)paren
suffix:semicolon
multiline_comment|/* enable MAPEN&#xfffd; */
multiline_comment|/* PCR1 -- Performance Control */
multiline_comment|/* Incrementor on, whatever that is */
id|setCx86
c_func
(paren
id|CX86_PCR1
comma
id|getCx86
c_func
(paren
id|CX86_PCR1
)paren
op_or
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/* PCR0 -- Performance Control */
multiline_comment|/* Incrementor Margin 10 */
id|setCx86
c_func
(paren
id|CX86_PCR0
comma
id|getCx86
c_func
(paren
id|CX86_PCR0
)paren
op_or
l_int|0x04
)paren
suffix:semicolon
id|setCx86
c_func
(paren
id|CX86_CCR3
comma
id|ccr3
)paren
suffix:semicolon
multiline_comment|/* disable MAPEN */
)brace
multiline_comment|/*&n; *&t;Configure later MediaGX and/or Geode processor.&n; */
DECL|function|geode_configure
r_static
r_void
id|__init
id|geode_configure
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u8
id|ccr3
comma
id|ccr4
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|ccr3
op_assign
id|getCx86
c_func
(paren
id|CX86_CCR3
)paren
suffix:semicolon
id|setCx86
c_func
(paren
id|CX86_CCR3
comma
(paren
id|ccr3
op_amp
l_int|0x0f
)paren
op_or
l_int|0x10
)paren
suffix:semicolon
multiline_comment|/* Enable */
id|ccr4
op_assign
id|getCx86
c_func
(paren
id|CX86_CCR4
)paren
suffix:semicolon
id|ccr4
op_or_assign
l_int|0x38
suffix:semicolon
multiline_comment|/* FPU fast, DTE cache, Mem bypass */
id|setCx86
c_func
(paren
id|CX86_CCR3
comma
id|ccr3
)paren
suffix:semicolon
id|set_cx86_memwb
c_func
(paren
)paren
suffix:semicolon
id|set_cx86_reorder
c_func
(paren
)paren
suffix:semicolon
id|set_cx86_inc
c_func
(paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|init_cyrix
r_static
r_void
id|__init
id|init_cyrix
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
r_int
r_char
id|dir0
comma
id|dir0_msn
comma
id|dir0_lsn
comma
id|dir1
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|c-&gt;x86_model_id
suffix:semicolon
r_const
r_char
op_star
id|p
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Bit 31 in normal CPUID used for nonstandard 3DNow ID;&n;&t;   3DNow is IDd by bit 31 in extended CPUID (1*32+31) anyway */
id|clear_bit
c_func
(paren
l_int|0
op_star
l_int|32
op_plus
l_int|31
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
multiline_comment|/* Cyrix used bit 24 in extended (AMD) CPUID for Cyrix MMX extensions */
r_if
c_cond
(paren
id|test_bit
c_func
(paren
l_int|1
op_star
l_int|32
op_plus
l_int|24
comma
id|c-&gt;x86_capability
)paren
)paren
(brace
id|clear_bit
c_func
(paren
l_int|1
op_star
l_int|32
op_plus
l_int|24
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|X86_FEATURE_CXMMX
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
)brace
id|do_cyrix_devid
c_func
(paren
op_amp
id|dir0
comma
op_amp
id|dir1
)paren
suffix:semicolon
id|check_cx686_slop
c_func
(paren
id|c
)paren
suffix:semicolon
id|Cx86_dir0_msb
op_assign
id|dir0_msn
op_assign
id|dir0
op_rshift
l_int|4
suffix:semicolon
multiline_comment|/* identifies CPU &quot;family&quot;   */
id|dir0_lsn
op_assign
id|dir0
op_amp
l_int|0xf
suffix:semicolon
multiline_comment|/* model or clock multiplier */
multiline_comment|/* common case step number/rev -- exceptions handled below */
id|c-&gt;x86_model
op_assign
(paren
id|dir1
op_rshift
l_int|4
)paren
op_plus
l_int|1
suffix:semicolon
id|c-&gt;x86_mask
op_assign
id|dir1
op_amp
l_int|0xf
suffix:semicolon
multiline_comment|/* Now cook; the original recipe is by Channing Corn, from Cyrix.&n;&t; * We do the same thing for each generation: we work out&n;&t; * the model, multiplier and stepping.  Black magic included,&n;&t; * to make the silicon step/rev numbers match the printed ones.&n;&t; */
r_switch
c_cond
(paren
id|dir0_msn
)paren
(brace
r_int
r_char
id|tmp
suffix:semicolon
r_case
l_int|0
suffix:colon
multiline_comment|/* Cx486SLC/DLC/SRx/DRx */
id|p
op_assign
id|Cx486_name
(braket
id|dir0_lsn
op_amp
l_int|7
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* Cx486S/DX/DX2/DX4 */
id|p
op_assign
(paren
id|dir0_lsn
op_amp
l_int|8
)paren
ques
c_cond
id|Cx486D_name
(braket
id|dir0_lsn
op_amp
l_int|5
)braket
suffix:colon
id|Cx486S_name
(braket
id|dir0_lsn
op_amp
l_int|3
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* 5x86 */
id|Cx86_cb
(braket
l_int|2
)braket
op_assign
id|cyrix_model_mult1
(braket
id|dir0_lsn
op_amp
l_int|5
)braket
suffix:semicolon
id|p
op_assign
id|Cx86_cb
op_plus
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* 6x86/6x86L */
id|Cx86_cb
(braket
l_int|1
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|Cx86_cb
(braket
l_int|2
)braket
op_assign
id|cyrix_model_mult1
(braket
id|dir0_lsn
op_amp
l_int|5
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dir1
OG
l_int|0x21
)paren
(brace
multiline_comment|/* 686L */
id|Cx86_cb
(braket
l_int|0
)braket
op_assign
l_char|&squot;L&squot;
suffix:semicolon
id|p
op_assign
id|Cx86_cb
suffix:semicolon
(paren
id|c-&gt;x86_model
)paren
op_increment
suffix:semicolon
)brace
r_else
multiline_comment|/* 686 */
id|p
op_assign
id|Cx86_cb
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* Emulate MTRRs using Cyrix&squot;s ARRs. */
id|set_bit
c_func
(paren
id|X86_FEATURE_CYRIX_ARR
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
multiline_comment|/* 6x86&squot;s contain this bug */
id|c-&gt;coma_bug
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* MediaGX/GXm or Geode GXM/GXLV/GX1 */
macro_line|#ifdef CONFIG_PCI
multiline_comment|/* It isn&squot;t really a PCI quirk directly, but the cure is the&n;&t;&t;   same. The MediaGX has deep magic SMM stuff that handles the&n;&t;&t;   SB emulation. It thows away the fifo on disable_dma() which&n;&t;&t;   is wrong and ruins the audio. &n;&n;&t;&t;   Bug2: VSA1 has a wrap bug so that using maximum sized DMA &n;&t;&t;   causes bad things. According to NatSemi VSA2 has another&n;&t;&t;   bug to do with &squot;hlt&squot;. I&squot;ve not seen any boards using VSA2&n;&t;&t;   and X doesn&squot;t seem to support it either so who cares 8).&n;&t;&t;   VSA1 we work around however.&n;&t;&t;*/
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Working around Cyrix MediaGX virtual DMA bugs.&bslash;n&quot;
)paren
suffix:semicolon
id|isa_dma_bridge_buggy
op_assign
l_int|2
suffix:semicolon
macro_line|#endif&t;&t;
id|c-&gt;x86_cache_size
op_assign
l_int|16
suffix:semicolon
multiline_comment|/* Yep 16K integrated cache thats it */
multiline_comment|/*&n;&t;&t; *  The 5510/5520 companion chips have a funky PIT.&n;&t;&t; */
r_if
c_cond
(paren
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_CYRIX
comma
id|PCI_DEVICE_ID_CYRIX_5510
comma
l_int|NULL
)paren
op_logical_or
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_CYRIX
comma
id|PCI_DEVICE_ID_CYRIX_5520
comma
l_int|NULL
)paren
)paren
id|pit_latch_buggy
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* GXm supports extended cpuid levels &squot;ala&squot; AMD */
r_if
c_cond
(paren
id|c-&gt;cpuid_level
op_eq
l_int|2
)paren
(brace
multiline_comment|/* Enable cxMMX extensions (GX1 Datasheet 54) */
id|setCx86
c_func
(paren
id|CX86_CCR7
comma
id|getCx86
c_func
(paren
id|CX86_CCR7
)paren
op_or
l_int|1
)paren
suffix:semicolon
multiline_comment|/* GXlv/GXm/GX1 */
r_if
c_cond
(paren
(paren
id|dir1
op_ge
l_int|0x50
op_logical_and
id|dir1
op_le
l_int|0x54
)paren
op_logical_or
id|dir1
op_ge
l_int|0x63
)paren
(brace
id|geode_configure
c_func
(paren
)paren
suffix:semicolon
)brace
id|get_model_name
c_func
(paren
id|c
)paren
suffix:semicolon
multiline_comment|/* get CPU marketing name */
r_return
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* MediaGX */
id|Cx86_cb
(braket
l_int|2
)braket
op_assign
(paren
id|dir0_lsn
op_amp
l_int|1
)paren
ques
c_cond
l_char|&squot;3&squot;
suffix:colon
l_char|&squot;4&squot;
suffix:semicolon
id|p
op_assign
id|Cx86_cb
op_plus
l_int|2
suffix:semicolon
id|c-&gt;x86_model
op_assign
(paren
id|dir1
op_amp
l_int|0x20
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|2
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
multiline_comment|/* 6x86MX/M II */
r_if
c_cond
(paren
id|dir1
OG
l_int|7
)paren
(brace
id|dir0_msn
op_increment
suffix:semicolon
multiline_comment|/* M II */
multiline_comment|/* Enable MMX extensions (App note 108) */
id|setCx86
c_func
(paren
id|CX86_CCR7
comma
id|getCx86
c_func
(paren
id|CX86_CCR7
)paren
op_or
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|c-&gt;coma_bug
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* 6x86MX, it has the bug. */
)brace
id|tmp
op_assign
(paren
op_logical_neg
(paren
id|dir0_lsn
op_amp
l_int|7
)paren
op_logical_or
id|dir0_lsn
op_amp
l_int|1
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|0
suffix:semicolon
id|Cx86_cb
(braket
id|tmp
)braket
op_assign
id|cyrix_model_mult2
(braket
id|dir0_lsn
op_amp
l_int|7
)braket
suffix:semicolon
id|p
op_assign
id|Cx86_cb
op_plus
id|tmp
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|dir1
op_amp
l_int|0x0f
)paren
OG
l_int|4
)paren
op_logical_or
(paren
(paren
id|dir1
op_amp
l_int|0xf0
)paren
op_eq
l_int|0x20
)paren
)paren
(paren
id|c-&gt;x86_model
)paren
op_increment
suffix:semicolon
multiline_comment|/* Emulate MTRRs using Cyrix&squot;s ARRs. */
id|set_bit
c_func
(paren
id|X86_FEATURE_CYRIX_ARR
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xf
suffix:colon
multiline_comment|/* Cyrix 486 without DEVID registers */
r_switch
c_cond
(paren
id|dir0_lsn
)paren
(brace
r_case
l_int|0xd
suffix:colon
multiline_comment|/* either a 486SLC or DLC w/o DEVID */
id|dir0_msn
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
id|Cx486_name
(braket
(paren
id|c-&gt;hard_math
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xe
suffix:colon
multiline_comment|/* a 486S A step */
id|dir0_msn
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
id|Cx486S_name
(braket
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* unknown (shouldn&squot;t happen, we know everyone ;-) */
id|dir0_msn
op_assign
l_int|7
suffix:semicolon
r_break
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|buf
comma
id|Cx86_model
(braket
id|dir0_msn
op_amp
l_int|7
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
id|strcat
c_func
(paren
id|buf
comma
id|p
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Cyrix CPUs without cpuid or with cpuid not yet enabled can be detected&n; * by the fact that they preserve the flags across the division of 5/2.&n; * PII and PPro exhibit this behavior too, but they have cpuid available.&n; */
multiline_comment|/*&n; * Perform the Cyrix 5/2 test. A Cyrix won&squot;t change&n; * the flags, while other 486 chips will.&n; */
DECL|function|test_cyrix_52div
r_static
r_inline
r_int
id|test_cyrix_52div
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|test
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sahf&bslash;n&bslash;t&quot;
multiline_comment|/* clear flags (%eax = 0x0005) */
l_string|&quot;div %b2&bslash;n&bslash;t&quot;
multiline_comment|/* divide 5 by 2 */
l_string|&quot;lahf&quot;
multiline_comment|/* store flags into %ah */
suffix:colon
l_string|&quot;=a&quot;
(paren
id|test
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|5
)paren
comma
l_string|&quot;q&quot;
(paren
l_int|2
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
multiline_comment|/* AH is 0x02 on Cyrix after the divide.. */
r_return
(paren
r_int
r_char
)paren
(paren
id|test
op_rshift
l_int|8
)paren
op_eq
l_int|0x02
suffix:semicolon
)brace
DECL|function|cyrix_identify
r_static
r_void
id|cyrix_identify
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
multiline_comment|/* Detect Cyrix with disabled CPUID */
r_if
c_cond
(paren
id|c-&gt;x86
op_eq
l_int|4
op_logical_and
id|test_cyrix_52div
c_func
(paren
)paren
)paren
(brace
r_int
r_char
id|dir0
comma
id|dir1
suffix:semicolon
id|strcpy
c_func
(paren
id|c-&gt;x86_vendor_id
comma
l_string|&quot;CyrixInstead&quot;
)paren
suffix:semicolon
id|c-&gt;x86_vendor
op_assign
id|X86_VENDOR_CYRIX
suffix:semicolon
multiline_comment|/* Actually enable cpuid on the older cyrix */
multiline_comment|/* Retrieve CPU revisions */
id|do_cyrix_devid
c_func
(paren
op_amp
id|dir0
comma
op_amp
id|dir1
)paren
suffix:semicolon
id|dir0
op_rshift_assign
l_int|4
suffix:semicolon
multiline_comment|/* Check it is an affected model */
r_if
c_cond
(paren
id|dir0
op_eq
l_int|5
op_logical_or
id|dir0
op_eq
l_int|3
)paren
(brace
r_int
r_char
id|ccr3
comma
id|ccr4
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Enabling CPUID on Cyrix processor.&bslash;n&quot;
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|ccr3
op_assign
id|getCx86
c_func
(paren
id|CX86_CCR3
)paren
suffix:semicolon
id|setCx86
c_func
(paren
id|CX86_CCR3
comma
(paren
id|ccr3
op_amp
l_int|0x0f
)paren
op_or
l_int|0x10
)paren
suffix:semicolon
multiline_comment|/* enable MAPEN  */
id|ccr4
op_assign
id|getCx86
c_func
(paren
id|CX86_CCR4
)paren
suffix:semicolon
id|setCx86
c_func
(paren
id|CX86_CCR4
comma
id|ccr4
op_or
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* enable cpuid  */
id|setCx86
c_func
(paren
id|CX86_CCR3
comma
id|ccr3
)paren
suffix:semicolon
multiline_comment|/* disable MAPEN */
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
id|generic_identify
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|cpu_dev
id|cyrix_cpu_dev
id|__initdata
op_assign
(brace
dot
id|c_vendor
op_assign
l_string|&quot;Cyrix&quot;
comma
dot
id|c_ident
op_assign
(brace
l_string|&quot;CyrixInstead&quot;
)brace
comma
dot
id|c_init
op_assign
id|init_cyrix
comma
dot
id|c_identify
op_assign
id|cyrix_identify
comma
)brace
suffix:semicolon
DECL|function|cyrix_init_cpu
r_int
id|__init
id|cyrix_init_cpu
c_func
(paren
r_void
)paren
(brace
id|cpu_devs
(braket
id|X86_VENDOR_CYRIX
)braket
op_assign
op_amp
id|cyrix_cpu_dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
singleline_comment|//early_arch_initcall(cyrix_init_cpu);
DECL|variable|__initdata
r_static
r_struct
id|cpu_dev
id|nsc_cpu_dev
id|__initdata
op_assign
(brace
dot
id|c_vendor
op_assign
l_string|&quot;NSC&quot;
comma
dot
id|c_ident
op_assign
(brace
l_string|&quot;Geode by NSC&quot;
)brace
comma
dot
id|c_init
op_assign
id|init_cyrix
comma
dot
id|c_identify
op_assign
id|generic_identify
comma
)brace
suffix:semicolon
DECL|function|nsc_init_cpu
r_int
id|__init
id|nsc_init_cpu
c_func
(paren
r_void
)paren
(brace
id|cpu_devs
(braket
id|X86_VENDOR_NSC
)braket
op_assign
op_amp
id|nsc_cpu_dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
singleline_comment|//early_arch_initcall(nsc_init_cpu);
eof
