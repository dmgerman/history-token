multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;baycom_par.c  -- baycom par96 and picpar radio modem driver.&n; *&n; *&t;Copyright (C) 1996-2000  Thomas Sailer (sailer@ife.ee.ethz.ch)&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License&n; *&t;along with this program; if not, write to the Free Software&n; *&t;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  Please note that the GPL allows you to use the driver, NOT the radio.&n; *  In order to use the radio, you need a license from the communications&n; *  authority of your country.&n; *&n; *&n; *  Supported modems&n; *&n; *  par96:  This is a modem for 9600 baud FSK compatible to the G3RUH standard.&n; *          The modem does all the filtering and regenerates the receiver clock.&n; *          Data is transferred from and to the PC via a shift register.&n; *          The shift register is filled with 16 bits and an interrupt is&n; *          signalled. The PC then empties the shift register in a burst. This&n; *          modem connects to the parallel port, hence the name. The modem&n; *          leaves the implementation of the HDLC protocol and the scrambler&n; *          polynomial to the PC. This modem is no longer available (at least&n; *          from Baycom) and has been replaced by the PICPAR modem (see below).&n; *          You may however still build one from the schematics published in&n; *          cq-DL :-).&n; *&n; *  picpar: This is a redesign of the par96 modem by Henning Rech, DF9IC. The&n; *          modem is protocol compatible to par96, but uses only three low&n; *          power ICs and can therefore be fed from the parallel port and&n; *          does not require an additional power supply. It features&n; *          built in DCD circuitry. The driver should therefore be configured&n; *          for hardware DCD.&n; *&n; *&n; *  Command line options (insmod command line)&n; *&n; *  mode     driver mode string. Valid choices are par96 and picpar.&n; *  iobase   base address of the port; common values are 0x378, 0x278, 0x3bc&n; *&n; *&n; *  History:&n; *   0.1  26.06.1996  Adapted from baycom.c and made network driver interface&n; *        18.10.1996  Changed to new user space access routines (copy_{to,from}_user)&n; *   0.3  26.04.1997  init code/data tagged&n; *   0.4  08.07.1997  alternative ser12 decoding algorithm (uses delta CTS ints)&n; *   0.5  11.11.1997  split into separate files for ser12/par96&n; *   0.6  03.08.1999  adapt to Linus&squot; new __setup/__initcall&n; *                    removed some pre-2.2 kernel compatibility cruft&n; *   0.7  10.08.1999  Check if parport can do SPP and is safe to access during interrupt contexts&n; *   0.8  12.02.2000  adapted to softnet driver interface&n; *                    removed direct parport access, uses parport driver methods&n; *   0.9  03.07.2000  fix interface name handling&n; */
multiline_comment|/*****************************************************************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/hdlcdrv.h&gt;
macro_line|#include &lt;linux/baycom.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* --------------------------------------------------------------------- */
DECL|macro|BAYCOM_DEBUG
mdefine_line|#define BAYCOM_DEBUG
multiline_comment|/*&n; * modem options; bit mask&n; */
DECL|macro|BAYCOM_OPTIONS_SOFTDCD
mdefine_line|#define BAYCOM_OPTIONS_SOFTDCD  1
multiline_comment|/* --------------------------------------------------------------------- */
DECL|variable|bc_drvname
r_static
r_const
r_char
id|bc_drvname
(braket
)braket
op_assign
l_string|&quot;baycom_par&quot;
suffix:semicolon
DECL|variable|bc_drvinfo
r_static
r_const
r_char
id|bc_drvinfo
(braket
)braket
op_assign
id|KERN_INFO
l_string|&quot;baycom_par: (C) 1996-2000 Thomas Sailer, HB9JNX/AE4WA&bslash;n&quot;
id|KERN_INFO
l_string|&quot;baycom_par: version 0.9 compiled &quot;
id|__TIME__
l_string|&quot; &quot;
id|__DATE__
l_string|&quot;&bslash;n&quot;
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|macro|NR_PORTS
mdefine_line|#define NR_PORTS 4
DECL|variable|baycom_device
r_static
r_struct
id|net_device
op_star
id|baycom_device
(braket
id|NR_PORTS
)braket
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|macro|PAR96_BURSTBITS
mdefine_line|#define PAR96_BURSTBITS 16
DECL|macro|PAR96_BURST
mdefine_line|#define PAR96_BURST     4
DECL|macro|PAR96_PTT
mdefine_line|#define PAR96_PTT       2
DECL|macro|PAR96_TXBIT
mdefine_line|#define PAR96_TXBIT     1
DECL|macro|PAR96_ACK
mdefine_line|#define PAR96_ACK       0x40
DECL|macro|PAR96_RXBIT
mdefine_line|#define PAR96_RXBIT     0x20
DECL|macro|PAR96_DCD
mdefine_line|#define PAR96_DCD       0x10
DECL|macro|PAR97_POWER
mdefine_line|#define PAR97_POWER     0xf8
multiline_comment|/* ---------------------------------------------------------------------- */
multiline_comment|/*&n; * Information that need to be kept for each board.&n; */
DECL|struct|baycom_state
r_struct
id|baycom_state
(brace
DECL|member|hdrv
r_struct
id|hdlcdrv_state
id|hdrv
suffix:semicolon
DECL|member|pdev
r_struct
id|pardevice
op_star
id|pdev
suffix:semicolon
DECL|member|options
r_int
r_int
id|options
suffix:semicolon
DECL|struct|modem_state
r_struct
id|modem_state
(brace
DECL|member|arb_divider
r_int
id|arb_divider
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|member|shreg
r_int
r_int
id|shreg
suffix:semicolon
DECL|struct|modem_state_par96
r_struct
id|modem_state_par96
(brace
DECL|member|dcd_count
r_int
id|dcd_count
suffix:semicolon
DECL|member|dcd_shreg
r_int
r_int
id|dcd_shreg
suffix:semicolon
DECL|member|descram
r_int
r_int
id|descram
suffix:semicolon
DECL|member|scram
r_int
r_int
id|scram
suffix:semicolon
DECL|member|par96
)brace
id|par96
suffix:semicolon
DECL|member|modem
)brace
id|modem
suffix:semicolon
macro_line|#ifdef BAYCOM_DEBUG
DECL|struct|debug_vals
r_struct
id|debug_vals
(brace
DECL|member|last_jiffies
r_int
r_int
id|last_jiffies
suffix:semicolon
DECL|member|cur_intcnt
r_int
id|cur_intcnt
suffix:semicolon
DECL|member|last_intcnt
r_int
id|last_intcnt
suffix:semicolon
DECL|member|cur_pllcorr
r_int
id|cur_pllcorr
suffix:semicolon
DECL|member|last_pllcorr
r_int
id|last_pllcorr
suffix:semicolon
DECL|member|debug_vals
)brace
id|debug_vals
suffix:semicolon
macro_line|#endif /* BAYCOM_DEBUG */
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|baycom_int_freq
r_static
r_void
id|__inline__
id|baycom_int_freq
c_func
(paren
r_struct
id|baycom_state
op_star
id|bc
)paren
(brace
macro_line|#ifdef BAYCOM_DEBUG
r_int
r_int
id|cur_jiffies
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/*&n;&t; * measure the interrupt frequency&n;&t; */
id|bc-&gt;debug_vals.cur_intcnt
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cur_jiffies
op_minus
id|bc-&gt;debug_vals.last_jiffies
)paren
op_ge
id|HZ
)paren
(brace
id|bc-&gt;debug_vals.last_jiffies
op_assign
id|cur_jiffies
suffix:semicolon
id|bc-&gt;debug_vals.last_intcnt
op_assign
id|bc-&gt;debug_vals.cur_intcnt
suffix:semicolon
id|bc-&gt;debug_vals.cur_intcnt
op_assign
l_int|0
suffix:semicolon
id|bc-&gt;debug_vals.last_pllcorr
op_assign
id|bc-&gt;debug_vals.cur_pllcorr
suffix:semicolon
id|bc-&gt;debug_vals.cur_pllcorr
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* BAYCOM_DEBUG */
)brace
multiline_comment|/* --------------------------------------------------------------------- */
multiline_comment|/*&n; * ===================== PAR96 specific routines =========================&n; */
DECL|macro|PAR96_DESCRAM_TAP1
mdefine_line|#define PAR96_DESCRAM_TAP1 0x20000
DECL|macro|PAR96_DESCRAM_TAP2
mdefine_line|#define PAR96_DESCRAM_TAP2 0x01000
DECL|macro|PAR96_DESCRAM_TAP3
mdefine_line|#define PAR96_DESCRAM_TAP3 0x00001
DECL|macro|PAR96_DESCRAM_TAPSH1
mdefine_line|#define PAR96_DESCRAM_TAPSH1 17
DECL|macro|PAR96_DESCRAM_TAPSH2
mdefine_line|#define PAR96_DESCRAM_TAPSH2 12
DECL|macro|PAR96_DESCRAM_TAPSH3
mdefine_line|#define PAR96_DESCRAM_TAPSH3 0
DECL|macro|PAR96_SCRAM_TAP1
mdefine_line|#define PAR96_SCRAM_TAP1 0x20000 /* X^17 */
DECL|macro|PAR96_SCRAM_TAPN
mdefine_line|#define PAR96_SCRAM_TAPN 0x00021 /* X^0+X^5 */
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|par96_tx
r_static
id|__inline__
r_void
id|par96_tx
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|baycom_state
op_star
id|bc
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|data
op_assign
id|hdlcdrv_getbits
c_func
(paren
op_amp
id|bc-&gt;hdrv
)paren
suffix:semicolon
r_struct
id|parport
op_star
id|pp
op_assign
id|bc-&gt;pdev-&gt;port
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PAR96_BURSTBITS
suffix:semicolon
id|i
op_increment
comma
id|data
op_rshift_assign
l_int|1
)paren
(brace
r_int
r_char
id|val
op_assign
id|PAR97_POWER
suffix:semicolon
id|bc-&gt;modem.par96.scram
op_assign
(paren
(paren
id|bc-&gt;modem.par96.scram
op_lshift
l_int|1
)paren
op_or
(paren
id|bc-&gt;modem.par96.scram
op_amp
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|data
op_amp
l_int|1
)paren
)paren
id|bc-&gt;modem.par96.scram
op_xor_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|bc-&gt;modem.par96.scram
op_amp
(paren
id|PAR96_SCRAM_TAP1
op_lshift
l_int|1
)paren
)paren
id|bc-&gt;modem.par96.scram
op_xor_assign
(paren
id|PAR96_SCRAM_TAPN
op_lshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bc-&gt;modem.par96.scram
op_amp
(paren
id|PAR96_SCRAM_TAP1
op_lshift
l_int|2
)paren
)paren
id|val
op_or_assign
id|PAR96_TXBIT
suffix:semicolon
id|pp-&gt;ops
op_member_access_from_pointer
id|write_data
c_func
(paren
id|pp
comma
id|val
)paren
suffix:semicolon
id|pp-&gt;ops
op_member_access_from_pointer
id|write_data
c_func
(paren
id|pp
comma
id|val
op_or
id|PAR96_BURST
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|par96_rx
r_static
id|__inline__
r_void
id|par96_rx
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|baycom_state
op_star
id|bc
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|data
comma
id|mask
comma
id|mask2
comma
id|descx
suffix:semicolon
r_struct
id|parport
op_star
id|pp
op_assign
id|bc-&gt;pdev-&gt;port
suffix:semicolon
multiline_comment|/*&n;&t; * do receiver; differential decode and descramble on the fly&n;&t; */
r_for
c_loop
(paren
id|data
op_assign
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PAR96_BURSTBITS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bc-&gt;modem.par96.descram
op_assign
(paren
id|bc-&gt;modem.par96.descram
op_lshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pp-&gt;ops
op_member_access_from_pointer
id|read_status
c_func
(paren
id|pp
)paren
op_amp
id|PAR96_RXBIT
)paren
id|bc-&gt;modem.par96.descram
op_or_assign
l_int|1
suffix:semicolon
id|descx
op_assign
id|bc-&gt;modem.par96.descram
op_xor
(paren
id|bc-&gt;modem.par96.descram
op_rshift
l_int|1
)paren
suffix:semicolon
multiline_comment|/* now the diff decoded data is inverted in descram */
id|pp-&gt;ops
op_member_access_from_pointer
id|write_data
c_func
(paren
id|pp
comma
id|PAR97_POWER
op_or
id|PAR96_PTT
)paren
suffix:semicolon
id|descx
op_xor_assign
(paren
(paren
id|descx
op_rshift
id|PAR96_DESCRAM_TAPSH1
)paren
op_xor
(paren
id|descx
op_rshift
id|PAR96_DESCRAM_TAPSH2
)paren
)paren
suffix:semicolon
id|data
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|descx
op_amp
l_int|1
)paren
)paren
id|data
op_or_assign
l_int|0x8000
suffix:semicolon
id|pp-&gt;ops
op_member_access_from_pointer
id|write_data
c_func
(paren
id|pp
comma
id|PAR97_POWER
op_or
id|PAR96_PTT
op_or
id|PAR96_BURST
)paren
suffix:semicolon
)brace
id|hdlcdrv_putbits
c_func
(paren
op_amp
id|bc-&gt;hdrv
comma
id|data
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * do DCD algorithm&n;&t; */
r_if
c_cond
(paren
id|bc-&gt;options
op_amp
id|BAYCOM_OPTIONS_SOFTDCD
)paren
(brace
id|bc-&gt;modem.par96.dcd_shreg
op_assign
(paren
id|bc-&gt;modem.par96.dcd_shreg
op_rshift
l_int|16
)paren
op_or
(paren
id|data
op_lshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* search for flags and set the dcd counter appropriately */
r_for
c_loop
(paren
id|mask
op_assign
l_int|0x1fe00
comma
id|mask2
op_assign
l_int|0xfc00
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PAR96_BURSTBITS
suffix:semicolon
id|i
op_increment
comma
id|mask
op_lshift_assign
l_int|1
comma
id|mask2
op_lshift_assign
l_int|1
)paren
r_if
c_cond
(paren
(paren
id|bc-&gt;modem.par96.dcd_shreg
op_amp
id|mask
)paren
op_eq
id|mask2
)paren
id|bc-&gt;modem.par96.dcd_count
op_assign
id|HDLCDRV_MAXFLEN
op_plus
l_int|4
suffix:semicolon
multiline_comment|/* check for abort/noise sequences */
r_for
c_loop
(paren
id|mask
op_assign
l_int|0x1fe00
comma
id|mask2
op_assign
l_int|0x1fe00
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PAR96_BURSTBITS
suffix:semicolon
id|i
op_increment
comma
id|mask
op_lshift_assign
l_int|1
comma
id|mask2
op_lshift_assign
l_int|1
)paren
r_if
c_cond
(paren
(paren
(paren
id|bc-&gt;modem.par96.dcd_shreg
op_amp
id|mask
)paren
op_eq
id|mask2
)paren
op_logical_and
(paren
id|bc-&gt;modem.par96.dcd_count
op_ge
l_int|0
)paren
)paren
id|bc-&gt;modem.par96.dcd_count
op_sub_assign
id|HDLCDRV_MAXFLEN
op_minus
l_int|10
suffix:semicolon
multiline_comment|/* decrement and set the dcd variable */
r_if
c_cond
(paren
id|bc-&gt;modem.par96.dcd_count
op_ge
l_int|0
)paren
id|bc-&gt;modem.par96.dcd_count
op_sub_assign
l_int|2
suffix:semicolon
id|hdlcdrv_setdcd
c_func
(paren
op_amp
id|bc-&gt;hdrv
comma
id|bc-&gt;modem.par96.dcd_count
OG
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|hdlcdrv_setdcd
c_func
(paren
op_amp
id|bc-&gt;hdrv
comma
op_logical_neg
op_logical_neg
(paren
id|pp-&gt;ops
op_member_access_from_pointer
id|read_status
c_func
(paren
id|pp
)paren
op_amp
id|PAR96_DCD
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|par96_interrupt
r_static
r_void
id|par96_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
(paren
r_struct
id|net_device
op_star
)paren
id|dev_id
suffix:semicolon
r_struct
id|baycom_state
op_star
id|bc
op_assign
(paren
r_struct
id|baycom_state
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|bc
op_logical_or
id|bc-&gt;hdrv.magic
op_ne
id|HDLCDRV_MAGIC
)paren
r_return
suffix:semicolon
id|baycom_int_freq
c_func
(paren
id|bc
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * check if transmitter active&n;&t; */
r_if
c_cond
(paren
id|hdlcdrv_ptt
c_func
(paren
op_amp
id|bc-&gt;hdrv
)paren
)paren
id|par96_tx
c_func
(paren
id|dev
comma
id|bc
)paren
suffix:semicolon
r_else
(brace
id|par96_rx
c_func
(paren
id|dev
comma
id|bc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|bc-&gt;modem.arb_divider
op_le
l_int|0
)paren
(brace
id|bc-&gt;modem.arb_divider
op_assign
l_int|6
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|hdlcdrv_arbitrate
c_func
(paren
id|dev
comma
op_amp
id|bc-&gt;hdrv
)paren
suffix:semicolon
)brace
)brace
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|hdlcdrv_transmitter
c_func
(paren
id|dev
comma
op_amp
id|bc-&gt;hdrv
)paren
suffix:semicolon
id|hdlcdrv_receiver
c_func
(paren
id|dev
comma
op_amp
id|bc-&gt;hdrv
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|par96_wakeup
r_static
r_void
id|par96_wakeup
c_func
(paren
r_void
op_star
id|handle
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
(paren
r_struct
id|net_device
op_star
)paren
id|handle
suffix:semicolon
r_struct
id|baycom_state
op_star
id|bc
op_assign
(paren
r_struct
id|baycom_state
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;baycom_par: %s: why am I being woken up?&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parport_claim
c_func
(paren
id|bc-&gt;pdev
)paren
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;baycom_par: %s: I&squot;m broken.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|par96_open
r_static
r_int
id|par96_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|baycom_state
op_star
id|bc
op_assign
(paren
r_struct
id|baycom_state
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_struct
id|parport
op_star
id|pp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|bc
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|pp
op_assign
id|parport_find_base
c_func
(paren
id|dev-&gt;base_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pp
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;baycom_par: parport at 0x%lx unknown&bslash;n&quot;
comma
id|dev-&gt;base_addr
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pp-&gt;irq
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;baycom_par: parport at 0x%lx has no irq&bslash;n&quot;
comma
id|pp-&gt;base
)paren
suffix:semicolon
id|parport_put_port
c_func
(paren
id|pp
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_complement
id|pp-&gt;modes
)paren
op_amp
(paren
id|PARPORT_MODE_PCSPP
op_or
id|PARPORT_MODE_SAFEININT
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;baycom_par: parport at 0x%lx cannot be used&bslash;n&quot;
comma
id|pp-&gt;base
)paren
suffix:semicolon
id|parport_put_port
c_func
(paren
id|pp
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|bc-&gt;modem
comma
l_int|0
comma
r_sizeof
(paren
id|bc-&gt;modem
)paren
)paren
suffix:semicolon
id|bc-&gt;hdrv.par.bitrate
op_assign
l_int|9600
suffix:semicolon
id|bc-&gt;pdev
op_assign
id|parport_register_device
c_func
(paren
id|pp
comma
id|dev-&gt;name
comma
l_int|NULL
comma
id|par96_wakeup
comma
id|par96_interrupt
comma
id|PARPORT_DEV_EXCL
comma
id|dev
)paren
suffix:semicolon
id|parport_put_port
c_func
(paren
id|pp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bc-&gt;pdev
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;baycom_par: cannot register parport at 0x%lx&bslash;n&quot;
comma
id|dev-&gt;base_addr
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|parport_claim
c_func
(paren
id|bc-&gt;pdev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;baycom_par: parport at 0x%lx busy&bslash;n&quot;
comma
id|pp-&gt;base
)paren
suffix:semicolon
id|parport_unregister_device
c_func
(paren
id|bc-&gt;pdev
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|pp
op_assign
id|bc-&gt;pdev-&gt;port
suffix:semicolon
id|dev-&gt;irq
op_assign
id|pp-&gt;irq
suffix:semicolon
id|pp-&gt;ops
op_member_access_from_pointer
id|data_forward
c_func
(paren
id|pp
)paren
suffix:semicolon
id|bc-&gt;hdrv.par.bitrate
op_assign
l_int|9600
suffix:semicolon
id|pp-&gt;ops
op_member_access_from_pointer
id|write_data
c_func
(paren
id|pp
comma
id|PAR96_PTT
op_or
id|PAR97_POWER
)paren
suffix:semicolon
multiline_comment|/* switch off PTT */
id|pp-&gt;ops
op_member_access_from_pointer
id|enable_irq
c_func
(paren
id|pp
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: par96 at iobase 0x%lx irq %u options 0x%x&bslash;n&quot;
comma
id|bc_drvname
comma
id|dev-&gt;base_addr
comma
id|dev-&gt;irq
comma
id|bc-&gt;options
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|par96_close
r_static
r_int
id|par96_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|baycom_state
op_star
id|bc
op_assign
(paren
r_struct
id|baycom_state
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_struct
id|parport
op_star
id|pp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|bc
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|pp
op_assign
id|bc-&gt;pdev-&gt;port
suffix:semicolon
multiline_comment|/* disable interrupt */
id|pp-&gt;ops
op_member_access_from_pointer
id|disable_irq
c_func
(paren
id|pp
)paren
suffix:semicolon
multiline_comment|/* switch off PTT */
id|pp-&gt;ops
op_member_access_from_pointer
id|write_data
c_func
(paren
id|pp
comma
id|PAR96_PTT
op_or
id|PAR97_POWER
)paren
suffix:semicolon
id|parport_release
c_func
(paren
id|bc-&gt;pdev
)paren
suffix:semicolon
id|parport_unregister_device
c_func
(paren
id|bc-&gt;pdev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: close par96 at iobase 0x%lx irq %u&bslash;n&quot;
comma
id|bc_drvname
comma
id|dev-&gt;base_addr
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
multiline_comment|/*&n; * ===================== hdlcdrv driver interface =========================&n; */
r_static
r_int
id|baycom_ioctl
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ifreq
op_star
id|ifr
comma
r_struct
id|hdlcdrv_ioctl
op_star
id|hi
comma
r_int
id|cmd
)paren
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|variable|par96_ops
r_static
r_struct
id|hdlcdrv_ops
id|par96_ops
op_assign
(brace
dot
id|drvname
op_assign
id|bc_drvname
comma
dot
id|drvinfo
op_assign
id|bc_drvinfo
comma
dot
id|open
op_assign
id|par96_open
comma
dot
id|close
op_assign
id|par96_close
comma
dot
id|ioctl
op_assign
id|baycom_ioctl
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|baycom_setmode
r_static
r_int
id|baycom_setmode
c_func
(paren
r_struct
id|baycom_state
op_star
id|bc
comma
r_const
r_char
op_star
id|modestr
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|modestr
comma
l_string|&quot;picpar&quot;
comma
l_int|6
)paren
)paren
id|bc-&gt;options
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|modestr
comma
l_string|&quot;par96&quot;
comma
l_int|5
)paren
)paren
id|bc-&gt;options
op_assign
id|BAYCOM_OPTIONS_SOFTDCD
suffix:semicolon
r_else
id|bc-&gt;options
op_assign
op_logical_neg
op_logical_neg
id|strchr
c_func
(paren
id|modestr
comma
l_char|&squot;*&squot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|baycom_ioctl
r_static
r_int
id|baycom_ioctl
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ifreq
op_star
id|ifr
comma
r_struct
id|hdlcdrv_ioctl
op_star
id|hi
comma
r_int
id|cmd
)paren
(brace
r_struct
id|baycom_state
op_star
id|bc
suffix:semicolon
r_struct
id|baycom_ioctl
id|bi
suffix:semicolon
r_int
id|cmd2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|dev-&gt;priv
op_logical_or
(paren
(paren
r_struct
id|baycom_state
op_star
)paren
id|dev-&gt;priv
)paren
op_member_access_from_pointer
id|hdrv.magic
op_ne
id|HDLCDRV_MAGIC
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;bc_ioctl: invalid device struct&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|bc
op_assign
(paren
r_struct
id|baycom_state
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_ne
id|SIOCDEVPRIVATE
)paren
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|cmd2
comma
(paren
r_int
op_star
)paren
id|ifr-&gt;ifr_data
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_switch
c_cond
(paren
id|hi-&gt;cmd
)paren
(brace
r_default
suffix:colon
r_break
suffix:semicolon
r_case
id|HDLCDRVCTL_GETMODE
suffix:colon
id|strcpy
c_func
(paren
id|hi-&gt;data.modename
comma
id|bc-&gt;options
ques
c_cond
l_string|&quot;par96&quot;
suffix:colon
l_string|&quot;picpar&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|ifr-&gt;ifr_data
comma
id|hi
comma
r_sizeof
(paren
r_struct
id|hdlcdrv_ioctl
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|HDLCDRVCTL_SETMODE
suffix:colon
r_if
c_cond
(paren
id|netif_running
c_func
(paren
id|dev
)paren
op_logical_or
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
id|hi-&gt;data.modename
(braket
r_sizeof
(paren
id|hi-&gt;data.modename
)paren
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|baycom_setmode
c_func
(paren
id|bc
comma
id|hi-&gt;data.modename
)paren
suffix:semicolon
r_case
id|HDLCDRVCTL_MODELIST
suffix:colon
id|strcpy
c_func
(paren
id|hi-&gt;data.modename
comma
l_string|&quot;par96,picpar&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|ifr-&gt;ifr_data
comma
id|hi
comma
r_sizeof
(paren
r_struct
id|hdlcdrv_ioctl
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|HDLCDRVCTL_MODEMPARMASK
suffix:colon
r_return
id|HDLCDRV_PARMASK_IOBASE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|bi
comma
id|ifr-&gt;ifr_data
comma
r_sizeof
(paren
id|bi
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_switch
c_cond
(paren
id|bi.cmd
)paren
(brace
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
macro_line|#ifdef BAYCOM_DEBUG
r_case
id|BAYCOMCTL_GETDEBUG
suffix:colon
id|bi.data.dbg.debug1
op_assign
id|bc-&gt;hdrv.ptt_keyed
suffix:semicolon
id|bi.data.dbg.debug2
op_assign
id|bc-&gt;debug_vals.last_intcnt
suffix:semicolon
id|bi.data.dbg.debug3
op_assign
id|bc-&gt;debug_vals.last_pllcorr
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* BAYCOM_DEBUG */
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|ifr-&gt;ifr_data
comma
op_amp
id|bi
comma
r_sizeof
(paren
id|bi
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
multiline_comment|/*&n; * command line settable parameters&n; */
DECL|variable|mode
r_static
r_const
r_char
op_star
id|mode
(braket
id|NR_PORTS
)braket
op_assign
(brace
l_string|&quot;picpar&quot;
comma
)brace
suffix:semicolon
DECL|variable|iobase
r_static
r_int
id|iobase
(braket
id|NR_PORTS
)braket
op_assign
(brace
l_int|0x378
comma
)brace
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|mode
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|NR_PORTS
)paren
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|mode
comma
l_string|&quot;baycom operating mode; eg. par96 or picpar&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|iobase
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|NR_PORTS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|iobase
comma
l_string|&quot;baycom io base address&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Thomas M. Sailer, sailer@ife.ee.ethz.ch, hb9jnx@hb9w.che.eu&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Baycom par96 and picpar amateur radio modem driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|init_baycompar
r_static
r_int
id|__init
id|init_baycompar
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|found
op_assign
l_int|0
suffix:semicolon
r_char
id|set_hw
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|bc_drvinfo
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * register net devices&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_PORTS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_struct
id|baycom_state
op_star
id|bc
suffix:semicolon
r_char
id|ifname
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|ifname
comma
l_string|&quot;bcp%d&quot;
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mode
(braket
id|i
)braket
)paren
id|set_hw
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|set_hw
)paren
id|iobase
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|dev
op_assign
id|hdlcdrv_register
c_func
(paren
op_amp
id|par96_ops
comma
r_sizeof
(paren
r_struct
id|baycom_state
)paren
comma
id|ifname
comma
id|iobase
(braket
id|i
)braket
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dev
)paren
)paren
r_break
suffix:semicolon
id|bc
op_assign
(paren
r_struct
id|baycom_state
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|set_hw
op_logical_and
id|baycom_setmode
c_func
(paren
id|bc
comma
id|mode
(braket
id|i
)braket
)paren
)paren
id|set_hw
op_assign
l_int|0
suffix:semicolon
id|found
op_increment
suffix:semicolon
id|baycom_device
(braket
id|i
)braket
op_assign
id|dev
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_baycompar
r_static
r_void
id|__exit
id|cleanup_baycompar
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_PORTS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|baycom_device
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
id|hdlcdrv_unregister
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
DECL|variable|init_baycompar
id|module_init
c_func
(paren
id|init_baycompar
)paren
suffix:semicolon
DECL|variable|cleanup_baycompar
id|module_exit
c_func
(paren
id|cleanup_baycompar
)paren
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
macro_line|#ifndef MODULE
multiline_comment|/*&n; * format: baycom_par=io,mode&n; * mode: par96,picpar&n; */
DECL|function|baycom_par_setup
r_static
r_int
id|__init
id|baycom_par_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_static
r_int
id|nr_dev
suffix:semicolon
r_int
id|ints
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|nr_dev
op_ge
id|NR_PORTS
)paren
r_return
l_int|0
suffix:semicolon
id|str
op_assign
id|get_options
c_func
(paren
id|str
comma
l_int|2
comma
id|ints
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OL
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
id|mode
(braket
id|nr_dev
)braket
op_assign
id|str
suffix:semicolon
id|iobase
(braket
id|nr_dev
)braket
op_assign
id|ints
(braket
l_int|1
)braket
suffix:semicolon
id|nr_dev
op_increment
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;baycom_par=&quot;
comma
id|baycom_par_setup
)paren
suffix:semicolon
macro_line|#endif /* MODULE */
multiline_comment|/* --------------------------------------------------------------------- */
eof
