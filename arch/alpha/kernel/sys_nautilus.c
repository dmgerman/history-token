multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/sys_nautilus.c&n; *&n; *&t;Copyright (C) 1995 David A Rusling&n; *&t;Copyright (C) 1998 Richard Henderson&n; *&t;Copyright (C) 1999 Alpha Processor, Inc.,&n; *&t;&t;(David Daniel, Stig Telfer, Soohoon Lee)&n; *&n; * Code supporting NAUTILUS systems.&n; *&n; *&n; * NAUTILUS has the following I/O features:&n; *&n; * a) Driven by AMD 751 aka IRONGATE (northbridge):&n; *     4 PCI slots&n; *     1 AGP slot&n; *&n; * b) Driven by ALI M1543C (southbridge)&n; *     2 ISA slots&n; *     2 IDE connectors&n; *     1 dual drive capable FDD controller&n; *     2 serial ports&n; *     1 ECP/EPP/SP parallel port&n; *     2 USB ports&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/core_irongate.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;irq_impl.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
macro_line|#include &quot;machvec_impl.h&quot;
r_static
r_void
id|__init
DECL|function|nautilus_init_irq
id|nautilus_init_irq
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|alpha_using_srm
)paren
(brace
id|alpha_mv.device_interrupt
op_assign
id|srm_device_interrupt
suffix:semicolon
id|alpha_mv.kill_arch
op_assign
l_int|NULL
suffix:semicolon
)brace
id|init_i8259a_irqs
c_func
(paren
)paren
suffix:semicolon
id|common_init_isa_dma
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|nautilus_map_irq
id|nautilus_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|slot
comma
id|u8
id|pin
)paren
(brace
multiline_comment|/* Preserve the IRQ set up by the console.  */
id|u8
id|irq
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
op_amp
id|irq
)paren
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
r_void
DECL|function|nautilus_kill_arch
id|nautilus_kill_arch
c_func
(paren
r_int
id|mode
)paren
(brace
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|LINUX_REBOOT_CMD_RESTART
suffix:colon
(brace
id|u8
id|t8
suffix:semicolon
id|pcibios_read_config_byte
c_func
(paren
l_int|0
comma
l_int|0x38
comma
l_int|0x43
comma
op_amp
id|t8
)paren
suffix:semicolon
id|pcibios_write_config_byte
c_func
(paren
l_int|0
comma
l_int|0x38
comma
l_int|0x43
comma
id|t8
op_or
l_int|0x80
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|1
comma
l_int|0x92
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
l_int|0x92
)paren
suffix:semicolon
multiline_comment|/* NOTREACHED */
)brace
r_break
suffix:semicolon
r_case
id|LINUX_REBOOT_CMD_POWER_OFF
suffix:colon
(brace
id|u32
id|pmuport
suffix:semicolon
id|pcibios_read_config_dword
c_func
(paren
l_int|0
comma
l_int|0x88
comma
l_int|0x10
comma
op_amp
id|pmuport
)paren
suffix:semicolon
id|pmuport
op_and_assign
l_int|0xfffe
suffix:semicolon
id|outl
c_func
(paren
l_int|0xffff
comma
id|pmuport
)paren
suffix:semicolon
multiline_comment|/* clear pending events */
id|outw
c_func
(paren
l_int|0x2000
comma
id|pmuport
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/* power off */
multiline_comment|/* NOTREACHED */
)brace
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* Machine check handler code&n; *&n; * Perform analysis of a machine check that was triggered by the EV6&n; * CPU&squot;s fault-detection mechanism.&n; */
multiline_comment|/* IPR structures for EV6, containing the necessary data for the&n; * machine check handler to unpick the logout frame&n; */
multiline_comment|/* I_STAT */
DECL|macro|EV6__I_STAT__PAR
mdefine_line|#define EV6__I_STAT__PAR                ( 1 &lt;&lt; 29 )
multiline_comment|/* MM_STAT */
DECL|macro|EV6__MM_STAT__DC_TAG_PERR
mdefine_line|#define EV6__MM_STAT__DC_TAG_PERR       ( 1 &lt;&lt; 10 )
multiline_comment|/* DC_STAT */
DECL|macro|EV6__DC_STAT__SEO
mdefine_line|#define EV6__DC_STAT__SEO               ( 1 &lt;&lt; 4 )
DECL|macro|EV6__DC_STAT__ECC_ERR_LD
mdefine_line|#define EV6__DC_STAT__ECC_ERR_LD        ( 1 &lt;&lt; 3 )
DECL|macro|EV6__DC_STAT__ECC_ERR_ST
mdefine_line|#define EV6__DC_STAT__ECC_ERR_ST        ( 1 &lt;&lt; 2 )
DECL|macro|EV6__DC_STAT__TPERR_P1
mdefine_line|#define EV6__DC_STAT__TPERR_P1          ( 1 &lt;&lt; 1 )
DECL|macro|EV6__DC_STAT__TPERR_P0
mdefine_line|#define EV6__DC_STAT__TPERR_P0          ( 1      )
multiline_comment|/* C_STAT */
DECL|macro|EV6__C_STAT__BC_PERR
mdefine_line|#define EV6__C_STAT__BC_PERR            ( 0x01 )
DECL|macro|EV6__C_STAT__DC_PERR
mdefine_line|#define EV6__C_STAT__DC_PERR            ( 0x02 )
DECL|macro|EV6__C_STAT__DSTREAM_MEM_ERR
mdefine_line|#define EV6__C_STAT__DSTREAM_MEM_ERR    ( 0x03 )
DECL|macro|EV6__C_STAT__DSTREAM_BC_ERR
mdefine_line|#define EV6__C_STAT__DSTREAM_BC_ERR     ( 0x04 )
DECL|macro|EV6__C_STAT__DSTREAM_DC_ERR
mdefine_line|#define EV6__C_STAT__DSTREAM_DC_ERR     ( 0x05 )
DECL|macro|EV6__C_STAT__PROBE_BC_ERR0
mdefine_line|#define EV6__C_STAT__PROBE_BC_ERR0      ( 0x06 )
DECL|macro|EV6__C_STAT__PROBE_BC_ERR1
mdefine_line|#define EV6__C_STAT__PROBE_BC_ERR1      ( 0x07 )
DECL|macro|EV6__C_STAT__ISTREAM_MEM_ERR
mdefine_line|#define EV6__C_STAT__ISTREAM_MEM_ERR    ( 0x0B )
DECL|macro|EV6__C_STAT__ISTREAM_BC_ERR
mdefine_line|#define EV6__C_STAT__ISTREAM_BC_ERR     ( 0x0C )
DECL|macro|EV6__C_STAT__DSTREAM_MEM_DBL
mdefine_line|#define EV6__C_STAT__DSTREAM_MEM_DBL    ( 0x13 )
DECL|macro|EV6__C_STAT__DSTREAM_BC_DBL
mdefine_line|#define EV6__C_STAT__DSTREAM_BC_DBL     ( 0x14 )
DECL|macro|EV6__C_STAT__ISTREAM_MEM_DBL
mdefine_line|#define EV6__C_STAT__ISTREAM_MEM_DBL    ( 0x1B )
DECL|macro|EV6__C_STAT__ISTREAM_BC_DBL
mdefine_line|#define EV6__C_STAT__ISTREAM_BC_DBL     ( 0x1C )
multiline_comment|/* Take the two syndromes from the CBOX error chain and convert them&n; * into a bit number.  */
multiline_comment|/* NOTE - since I don&squot;t know of any difference between C0 and C1 I&n;   just ignore C1, since in all cases I&squot;ve seen so far they are&n;   identical.  */
DECL|variable|ev6_bit_to_syndrome
r_static
r_const
r_int
r_char
id|ev6_bit_to_syndrome
(braket
l_int|72
)braket
op_assign
(brace
l_int|0xce
comma
l_int|0xcb
comma
l_int|0xd3
comma
l_int|0xd5
comma
l_int|0xd6
comma
l_int|0xd9
comma
l_int|0xda
comma
l_int|0xdc
comma
multiline_comment|/* 0 */
l_int|0x23
comma
l_int|0x25
comma
l_int|0x26
comma
l_int|0x29
comma
l_int|0x2a
comma
l_int|0x2c
comma
l_int|0x31
comma
l_int|0x34
comma
multiline_comment|/* 8 */
l_int|0x0e
comma
l_int|0x0b
comma
l_int|0x13
comma
l_int|0x15
comma
l_int|0x16
comma
l_int|0x19
comma
l_int|0x1a
comma
l_int|0x1c
comma
multiline_comment|/* 16 */
l_int|0xe3
comma
l_int|0xe5
comma
l_int|0xe6
comma
l_int|0xe9
comma
l_int|0xea
comma
l_int|0xec
comma
l_int|0xf1
comma
l_int|0xf4
comma
multiline_comment|/* 24 */
l_int|0x4f
comma
l_int|0x4a
comma
l_int|0x52
comma
l_int|0x54
comma
l_int|0x57
comma
l_int|0x58
comma
l_int|0x5b
comma
l_int|0x5d
comma
multiline_comment|/* 32 */
l_int|0xa2
comma
l_int|0xa4
comma
l_int|0xa7
comma
l_int|0xa8
comma
l_int|0xab
comma
l_int|0xad
comma
l_int|0xb0
comma
l_int|0xb5
comma
multiline_comment|/* 40 */
l_int|0x8f
comma
l_int|0x8a
comma
l_int|0x92
comma
l_int|0x94
comma
l_int|0x97
comma
l_int|0x98
comma
l_int|0x9b
comma
l_int|0x9d
comma
multiline_comment|/* 48 */
l_int|0x62
comma
l_int|0x64
comma
l_int|0x67
comma
l_int|0x68
comma
l_int|0x6b
comma
l_int|0x6d
comma
l_int|0x70
comma
l_int|0x75
comma
multiline_comment|/* 56 */
l_int|0x01
comma
l_int|0x02
comma
l_int|0x04
comma
l_int|0x08
comma
l_int|0x10
comma
l_int|0x20
comma
l_int|0x40
comma
l_int|0x80
multiline_comment|/* 64 */
)brace
suffix:semicolon
DECL|function|ev6_syn2bit
r_static
r_int
id|ev6_syn2bit
c_func
(paren
r_int
r_int
id|c0
comma
r_int
r_int
id|c1
)paren
(brace
r_int
id|bit
suffix:semicolon
r_for
c_loop
(paren
id|bit
op_assign
l_int|0
suffix:semicolon
id|bit
OL
l_int|72
suffix:semicolon
id|bit
op_increment
)paren
r_if
c_cond
(paren
id|ev6_bit_to_syndrome
(braket
id|bit
)braket
op_eq
id|c0
)paren
r_return
id|bit
suffix:semicolon
r_for
c_loop
(paren
id|bit
op_assign
l_int|0
suffix:semicolon
id|bit
OL
l_int|72
suffix:semicolon
id|bit
op_increment
)paren
r_if
c_cond
(paren
id|ev6_bit_to_syndrome
(braket
id|bit
)braket
op_eq
id|c1
)paren
r_return
id|bit
op_plus
l_int|64
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* not found */
)brace
multiline_comment|/* Single bit ECC errors are categorized here.  */
macro_line|#if 0
r_static
r_const
r_char
op_star
id|interr
op_assign
l_string|&quot;CPU internal error&quot;
suffix:semicolon
r_static
r_const
r_char
op_star
id|slotb
op_assign
l_string|&quot;Slot-B error&quot;
suffix:semicolon
r_static
r_const
r_char
op_star
id|membus
op_assign
l_string|&quot;Memory/EV6-bus error&quot;
suffix:semicolon
macro_line|#else
DECL|variable|interr
r_static
r_const
r_char
op_star
id|interr
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|slotb
r_static
r_const
r_char
op_star
id|slotb
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|membus
r_static
r_const
r_char
op_star
id|membus
op_assign
l_string|&quot;&quot;
suffix:semicolon
macro_line|#endif
r_static
r_void
DECL|function|ev6_crd_interp
id|ev6_crd_interp
c_func
(paren
r_char
op_star
id|interp
comma
r_struct
id|el_common_EV6_mcheck
op_star
id|L
)paren
(brace
multiline_comment|/* Icache data or tag parity error.  */
r_if
c_cond
(paren
id|L-&gt;I_STAT
op_amp
id|EV6__I_STAT__PAR
)paren
(brace
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;%s: I_STAT[PAR]&bslash;n &quot;
l_string|&quot;Icache data or tag parity error&quot;
comma
id|interr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Dcache tag parity error (on issue) (DFAULT).  */
r_if
c_cond
(paren
id|L-&gt;MM_STAT
op_amp
id|EV6__MM_STAT__DC_TAG_PERR
)paren
(brace
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;%s: MM_STAT[DC_TAG_PERR]&bslash;n &quot;
l_string|&quot;Dcache tag parity error(on issue)&quot;
comma
id|interr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Errors relating to D-stream set non-zero DC_STAT.&n;&t;   Mask CRD bits.  */
r_switch
c_cond
(paren
id|L-&gt;DC_STAT
op_amp
(paren
id|EV6__DC_STAT__ECC_ERR_ST
op_or
id|EV6__DC_STAT__ECC_ERR_LD
)paren
)paren
(brace
r_case
id|EV6__DC_STAT__ECC_ERR_ST
suffix:colon
multiline_comment|/* Dcache single-bit ECC error on small store */
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;%s: DC_STAT[ECC_ERR_ST]&bslash;n &quot;
l_string|&quot;Dcache single-bit ECC error on small store&quot;
comma
id|interr
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|EV6__DC_STAT__ECC_ERR_LD
suffix:colon
r_switch
c_cond
(paren
id|L-&gt;C_STAT
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* Dcache single-bit error on speculative load */
multiline_comment|/* Bcache victim read on Dcache/Bcache miss */
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;%s: DC_STAT[ECC_ERR_LD] C_STAT=0&bslash;n &quot;
l_string|&quot;Dcache single-bit ECC error on speculative load&quot;
comma
id|slotb
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|EV6__C_STAT__DSTREAM_DC_ERR
suffix:colon
multiline_comment|/* Dcache single bit error on load */
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;%s: DC_STAT[ECC_ERR_LD] C_STAT[DSTREAM_DC_ERR]&bslash;n&quot;
l_string|&quot; Dcache single-bit ECC error on speculative load, bit %d&quot;
comma
id|interr
comma
id|ev6_syn2bit
c_func
(paren
id|L-&gt;DC0_SYNDROME
comma
id|L-&gt;DC1_SYNDROME
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|EV6__C_STAT__DSTREAM_BC_ERR
suffix:colon
multiline_comment|/* Bcache single-bit error on Dcache fill */
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;%s: DC_STAT[ECC_ERR_LD] C_STAT[DSTREAM_BC_ERR]&bslash;n&quot;
l_string|&quot; Bcache single-bit error on Dcache fill, bit %d&quot;
comma
id|slotb
comma
id|ev6_syn2bit
c_func
(paren
id|L-&gt;DC0_SYNDROME
comma
id|L-&gt;DC1_SYNDROME
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|EV6__C_STAT__DSTREAM_MEM_ERR
suffix:colon
multiline_comment|/* Memory single-bit error on Dcache fill */
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;%s (to Dcache): DC_STAT[ECC_ERR_LD] &quot;
l_string|&quot;C_STAT[DSTREAM_MEM_ERR]&bslash;n &quot;
l_string|&quot;Memory single-bit error on Dcache fill, &quot;
l_string|&quot;Address 0x%lX, bit %d&quot;
comma
id|membus
comma
id|L-&gt;C_ADDR
comma
id|ev6_syn2bit
c_func
(paren
id|L-&gt;DC0_SYNDROME
comma
id|L-&gt;DC1_SYNDROME
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/* I-stream, other misc errors go on C_STAT alone */
r_switch
c_cond
(paren
id|L-&gt;C_STAT
)paren
(brace
r_case
id|EV6__C_STAT__ISTREAM_BC_ERR
suffix:colon
multiline_comment|/* Bcache single-bit error on Icache fill (also MCHK) */
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;%s: C_STAT[ISTREAM_BC_ERR]&bslash;n &quot;
l_string|&quot;Bcache single-bit error on Icache fill, bit %d&quot;
comma
id|slotb
comma
id|ev6_syn2bit
c_func
(paren
id|L-&gt;DC0_SYNDROME
comma
id|L-&gt;DC1_SYNDROME
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|EV6__C_STAT__ISTREAM_MEM_ERR
suffix:colon
multiline_comment|/* Memory single-bit error on Icache fill (also MCHK) */
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;%s : C_STATISTREAM_MEM_ERR]&bslash;n &quot;
l_string|&quot;Memory single-bit error on Icache fill &quot;
l_string|&quot;addr 0x%lX, bit %d&quot;
comma
id|membus
comma
id|L-&gt;C_ADDR
comma
id|ev6_syn2bit
c_func
(paren
id|L-&gt;DC0_SYNDROME
comma
id|L-&gt;DC1_SYNDROME
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|EV6__C_STAT__PROBE_BC_ERR0
suffix:colon
r_case
id|EV6__C_STAT__PROBE_BC_ERR1
suffix:colon
multiline_comment|/* Bcache single-bit error on a probe hit */
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;%s: C_STAT[PROBE_BC_ERR]&bslash;n &quot;
l_string|&quot;Bcache single-bit error on a probe hit, &quot;
l_string|&quot;addr 0x%lx, bit %d&quot;
comma
id|slotb
comma
id|L-&gt;C_ADDR
comma
id|ev6_syn2bit
c_func
(paren
id|L-&gt;DC0_SYNDROME
comma
id|L-&gt;DC1_SYNDROME
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|ev6_mchk_interp
id|ev6_mchk_interp
c_func
(paren
r_char
op_star
id|interp
comma
r_struct
id|el_common_EV6_mcheck
op_star
id|L
)paren
(brace
multiline_comment|/* Machine check errors described by DC_STAT */
r_switch
c_cond
(paren
id|L-&gt;DC_STAT
)paren
(brace
r_case
id|EV6__DC_STAT__TPERR_P0
suffix:colon
r_case
id|EV6__DC_STAT__TPERR_P1
suffix:colon
multiline_comment|/* Dcache tag parity error (on retry) */
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;%s: DC_STAT[TPERR_P0|TPERR_P1]&bslash;n &quot;
l_string|&quot;Dcache tag parity error(on retry)&quot;
comma
id|interr
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|EV6__DC_STAT__SEO
suffix:colon
multiline_comment|/* Dcache second error on store */
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;%s: DC_STAT[SEO]&bslash;n &quot;
l_string|&quot;Dcache second error during mcheck&quot;
comma
id|interr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Machine check errors described by C_STAT */
r_switch
c_cond
(paren
id|L-&gt;C_STAT
)paren
(brace
r_case
id|EV6__C_STAT__DC_PERR
suffix:colon
multiline_comment|/* Dcache duplicate tag parity error */
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;%s: C_STAT[DC_PERR]&bslash;n &quot;
l_string|&quot;Dcache duplicate tag parity error at 0x%lX&quot;
comma
id|interr
comma
id|L-&gt;C_ADDR
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|EV6__C_STAT__BC_PERR
suffix:colon
multiline_comment|/* Bcache tag parity error */
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;%s: C_STAT[BC_PERR]&bslash;n &quot;
l_string|&quot;Bcache tag parity error at 0x%lX&quot;
comma
id|slotb
comma
id|L-&gt;C_ADDR
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|EV6__C_STAT__ISTREAM_BC_ERR
suffix:colon
multiline_comment|/* Bcache single-bit error on Icache fill (also CRD) */
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;%s: C_STAT[ISTREAM_BC_ERR]&bslash;n &quot;
l_string|&quot;Bcache single-bit error on Icache fill 0x%lX bit %d&quot;
comma
id|slotb
comma
id|L-&gt;C_ADDR
comma
id|ev6_syn2bit
c_func
(paren
id|L-&gt;DC0_SYNDROME
comma
id|L-&gt;DC1_SYNDROME
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|EV6__C_STAT__ISTREAM_MEM_ERR
suffix:colon
multiline_comment|/* Memory single-bit error on Icache fill (also CRD) */
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;%s: C_STAT[ISTREAM_MEM_ERR]&bslash;n &quot;
l_string|&quot;Memory single-bit error on Icache fill 0x%lX, bit %d&quot;
comma
id|membus
comma
id|L-&gt;C_ADDR
comma
id|ev6_syn2bit
c_func
(paren
id|L-&gt;DC0_SYNDROME
comma
id|L-&gt;DC1_SYNDROME
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|EV6__C_STAT__ISTREAM_BC_DBL
suffix:colon
multiline_comment|/* Bcache double-bit error on Icache fill */
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;%s: C_STAT[ISTREAM_BC_DBL]&bslash;n &quot;
l_string|&quot;Bcache double-bit error on Icache fill at 0x%lX&quot;
comma
id|slotb
comma
id|L-&gt;C_ADDR
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|EV6__C_STAT__DSTREAM_BC_DBL
suffix:colon
multiline_comment|/* Bcache double-bit error on Dcache fill */
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;%s: C_STAT[DSTREAM_BC_DBL]&bslash;n &quot;
l_string|&quot;Bcache double-bit error on Dcache fill at 0x%lX&quot;
comma
id|slotb
comma
id|L-&gt;C_ADDR
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|EV6__C_STAT__ISTREAM_MEM_DBL
suffix:colon
multiline_comment|/* Memory double-bit error on Icache fill */
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;%s: C_STAT[ISTREAM_MEM_DBL]&bslash;n &quot;
l_string|&quot;Memory double-bit error on Icache fill at 0x%lX&quot;
comma
id|membus
comma
id|L-&gt;C_ADDR
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
id|EV6__C_STAT__DSTREAM_MEM_DBL
suffix:colon
multiline_comment|/* Memory double-bit error on Dcache fill */
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;%s: C_STAT[DSTREAM_MEM_DBL]&bslash;n &quot;
l_string|&quot;Memory double-bit error on Dcache fill at 0x%lX&quot;
comma
id|membus
comma
id|L-&gt;C_ADDR
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|ev6_cpu_machine_check
id|ev6_cpu_machine_check
c_func
(paren
r_int
r_int
id|vector
comma
r_struct
id|el_common_EV6_mcheck
op_star
id|L
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_char
id|interp
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* This is verbose and looks intimidating.  Should it be printed for&n;&t;   corrected (CRD) machine checks? */
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;PALcode logout frame:  &quot;
l_string|&quot;MCHK_Code       %d  &quot;
l_string|&quot;MCHK_Frame_Rev  %d&bslash;n&quot;
l_string|&quot;I_STAT  %016lx  &quot;
l_string|&quot;DC_STAT %016lx  &quot;
l_string|&quot;C_ADDR  %016lx&bslash;n&quot;
l_string|&quot;SYND1   %016lx  &quot;
l_string|&quot;SYND0   %016lx  &quot;
l_string|&quot;C_STAT  %016lx&bslash;n&quot;
l_string|&quot;C_STS   %016lx  &quot;
l_string|&quot;RES     %016lx  &quot;
l_string|&quot;EXC_ADDR%016lx&bslash;n&quot;
l_string|&quot;IER_CM  %016lx  &quot;
l_string|&quot;ISUM    %016lx  &quot;
l_string|&quot;MM_STAT %016lx&bslash;n&quot;
l_string|&quot;PALBASE %016lx  &quot;
l_string|&quot;I_CTL   %016lx  &quot;
l_string|&quot;PCTX    %016lx&bslash;n&quot;
l_string|&quot;CPU registers: &quot;
l_string|&quot;PC      %016lx  &quot;
l_string|&quot;Return  %016lx&bslash;n&quot;
comma
id|L-&gt;MCHK_Code
comma
id|L-&gt;MCHK_Frame_Rev
comma
id|L-&gt;I_STAT
comma
id|L-&gt;DC_STAT
comma
id|L-&gt;C_ADDR
comma
id|L-&gt;DC1_SYNDROME
comma
id|L-&gt;DC0_SYNDROME
comma
id|L-&gt;C_STAT
comma
id|L-&gt;C_STS
comma
id|L-&gt;RESERVED0
comma
id|L-&gt;EXC_ADDR
comma
id|L-&gt;IER_CM
comma
id|L-&gt;ISUM
comma
id|L-&gt;MM_STAT
comma
id|L-&gt;PAL_BASE
comma
id|L-&gt;I_CTL
comma
id|L-&gt;PCTX
comma
id|regs-&gt;pc
comma
id|regs-&gt;r26
)paren
suffix:semicolon
multiline_comment|/* Attempt an interpretation on the meanings of the fields above.  */
id|sprintf
c_func
(paren
id|interp
comma
l_string|&quot;No interpretation available!&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vector
op_eq
id|SCB_Q_PROCERR
)paren
id|ev6_crd_interp
c_func
(paren
id|interp
comma
id|L
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|vector
op_eq
id|SCB_Q_PROCMCHK
)paren
id|ev6_mchk_interp
c_func
(paren
id|interp
comma
id|L
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;interpretation: %s&bslash;n&bslash;n&quot;
comma
id|interp
)paren
suffix:semicolon
)brace
multiline_comment|/* Perform analysis of a machine check that arrived from the system (NMI) */
r_static
r_void
DECL|function|naut_sys_machine_check
id|naut_sys_machine_check
c_func
(paren
r_int
r_int
id|vector
comma
r_int
r_int
id|la_ptr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;xtime %lx&bslash;n&quot;
comma
id|CURRENT_TIME
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PC %lx RA %lx&bslash;n&quot;
comma
id|regs-&gt;pc
comma
id|regs-&gt;r26
)paren
suffix:semicolon
id|irongate_pci_clr_err
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Machine checks can come from two sources - those on the CPU and those&n;   in the system.  They are analysed separately but all starts here.  */
r_void
DECL|function|nautilus_machine_check
id|nautilus_machine_check
c_func
(paren
r_int
r_int
id|vector
comma
r_int
r_int
id|la_ptr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_char
op_star
id|mchk_class
suffix:semicolon
r_int
id|cpu_analysis
op_assign
l_int|0
comma
id|sys_analysis
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Now for some analysis.  Machine checks fall into two classes --&n;&t;   those picked up by the system, and those picked up by the CPU.&n;&t;   Add to that the two levels of severity - correctable or not.  */
r_if
c_cond
(paren
id|vector
op_eq
id|SCB_Q_SYSMCHK
op_logical_and
(paren
(paren
id|IRONGATE0-&gt;dramms
op_amp
l_int|0x300
)paren
op_eq
l_int|0x300
)paren
)paren
(brace
r_int
r_int
id|nmi_ctl
suffix:semicolon
multiline_comment|/* Clear ALI NMI */
id|nmi_ctl
op_assign
id|inb
c_func
(paren
l_int|0x61
)paren
suffix:semicolon
id|nmi_ctl
op_or_assign
l_int|0x0c
suffix:semicolon
id|outb
c_func
(paren
id|nmi_ctl
comma
l_int|0x61
)paren
suffix:semicolon
id|nmi_ctl
op_and_assign
op_complement
l_int|0x0c
suffix:semicolon
id|outb
c_func
(paren
id|nmi_ctl
comma
l_int|0x61
)paren
suffix:semicolon
multiline_comment|/* Write again clears error bits.  */
id|IRONGATE0-&gt;stat_cmd
op_assign
id|IRONGATE0-&gt;stat_cmd
op_amp
op_complement
l_int|0x100
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|IRONGATE0-&gt;stat_cmd
suffix:semicolon
multiline_comment|/* Write again clears error bits.  */
id|IRONGATE0-&gt;dramms
op_assign
id|IRONGATE0-&gt;dramms
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|IRONGATE0-&gt;dramms
suffix:semicolon
id|draina
c_func
(paren
)paren
suffix:semicolon
id|wrmces
c_func
(paren
l_int|0x7
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|vector
)paren
(brace
r_case
id|SCB_Q_SYSERR
suffix:colon
id|mchk_class
op_assign
l_string|&quot;Correctable System Machine Check (NMI)&quot;
suffix:semicolon
id|sys_analysis
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCB_Q_SYSMCHK
suffix:colon
id|mchk_class
op_assign
l_string|&quot;Fatal System Machine Check (NMI)&quot;
suffix:semicolon
id|sys_analysis
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCB_Q_PROCERR
suffix:colon
id|mchk_class
op_assign
l_string|&quot;Correctable Processor Machine Check&quot;
suffix:semicolon
id|cpu_analysis
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCB_Q_PROCMCHK
suffix:colon
id|mchk_class
op_assign
l_string|&quot;Fatal Processor Machine Check&quot;
suffix:semicolon
id|cpu_analysis
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|mchk_class
op_assign
l_string|&quot;Unknown vector!&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;NAUTILUS Machine check 0x%lx [%s]&bslash;n&quot;
comma
id|vector
comma
id|mchk_class
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_analysis
)paren
id|ev6_cpu_machine_check
c_func
(paren
id|vector
comma
(paren
r_struct
id|el_common_EV6_mcheck
op_star
)paren
id|la_ptr
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sys_analysis
)paren
id|naut_sys_machine_check
c_func
(paren
id|vector
comma
id|la_ptr
comma
id|regs
)paren
suffix:semicolon
multiline_comment|/* Tell the PALcode to clear the machine check */
id|draina
c_func
(paren
)paren
suffix:semicolon
id|wrmces
c_func
(paren
l_int|0x7
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The System Vectors&n; */
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|nautilus_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;Nautilus&quot;
comma
id|DO_EV6_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_IRONGATE_IO
comma
id|DO_IRONGATE_BUS
comma
id|machine_check
suffix:colon
id|nautilus_machine_check
comma
id|max_dma_address
suffix:colon
id|ALPHA_NAUTILUS_MAX_DMA_ADDRESS
comma
id|min_io_address
suffix:colon
id|DEFAULT_IO_BASE
comma
id|min_mem_address
suffix:colon
id|IRONGATE_DEFAULT_MEM_BASE
comma
id|nr_irqs
suffix:colon
l_int|16
comma
id|device_interrupt
suffix:colon
id|isa_device_interrupt
comma
id|init_arch
suffix:colon
id|irongate_init_arch
comma
id|init_irq
suffix:colon
id|nautilus_init_irq
comma
id|init_rtc
suffix:colon
id|common_init_rtc
comma
id|init_pci
suffix:colon
id|common_init_pci
comma
id|kill_arch
suffix:colon
id|nautilus_kill_arch
comma
id|pci_map_irq
suffix:colon
id|nautilus_map_irq
comma
id|pci_swizzle
suffix:colon
id|common_swizzle
comma
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|nautilus
)paren
eof
