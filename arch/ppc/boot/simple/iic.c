multiline_comment|/* Minimal support functions to read configuration from IIC EEPROMS&n; * on MPC8xx boards.  Originally written for RPGC RPX-Lite.&n; * Dan Malek (dmalek@jlc.net).&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/mpc8xx.h&gt;
macro_line|#include &lt;asm/commproc.h&gt;
multiline_comment|/* IIC functions.&n; * These are just the basic master read/write operations so we can&n; * examine serial EEPROM.&n; */
r_void
id|iic_read
c_func
(paren
id|uint
id|devaddr
comma
id|u_char
op_star
id|buf
comma
id|uint
id|offset
comma
id|uint
id|count
)paren
suffix:semicolon
DECL|variable|iic_init_done
r_static
r_int
id|iic_init_done
suffix:semicolon
r_static
r_void
DECL|function|iic_init
id|iic_init
c_func
(paren
r_void
)paren
(brace
r_volatile
id|iic_t
op_star
id|iip
suffix:semicolon
r_volatile
id|i2c8xx_t
op_star
id|i2c
suffix:semicolon
r_volatile
id|cpm8xx_t
op_star
id|cp
suffix:semicolon
r_volatile
id|immap_t
op_star
id|immap
suffix:semicolon
id|uint
id|dpaddr
suffix:semicolon
id|immap
op_assign
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
suffix:semicolon
id|cp
op_assign
(paren
id|cpm8xx_t
op_star
)paren
op_amp
(paren
id|immap-&gt;im_cpm
)paren
suffix:semicolon
multiline_comment|/* Reset the CPM.  This is necessary on the 860 processors&n;&t; * that may have started the SCC1 ethernet without relocating&n;&t; * the IIC.&n;&t; * This also stops the Ethernet in case we were loaded by a&n;&t; * BOOTP rom monitor.&n;&t; */
id|cp-&gt;cp_cpcr
op_assign
(paren
id|CPM_CR_RST
op_or
id|CPM_CR_FLG
)paren
suffix:semicolon
multiline_comment|/* Wait for it.&n;&t;*/
r_while
c_loop
(paren
id|cp-&gt;cp_cpcr
op_amp
(paren
id|CPM_CR_RST
op_or
id|CPM_CR_FLG
)paren
)paren
suffix:semicolon
multiline_comment|/* Remove any microcode patches.  We will install our own&n;&t; * later.&n;&t; */
id|cp-&gt;cp_cpmcr1
op_assign
l_int|0
suffix:semicolon
id|cp-&gt;cp_cpmcr2
op_assign
l_int|0
suffix:semicolon
id|cp-&gt;cp_cpmcr3
op_assign
l_int|0
suffix:semicolon
id|cp-&gt;cp_cpmcr4
op_assign
l_int|0
suffix:semicolon
id|cp-&gt;cp_rccr
op_assign
l_int|0
suffix:semicolon
id|iip
op_assign
(paren
id|iic_t
op_star
)paren
op_amp
id|cp-&gt;cp_dparam
(braket
id|PROFF_IIC
)braket
suffix:semicolon
id|i2c
op_assign
(paren
id|i2c8xx_t
op_star
)paren
op_amp
(paren
id|immap-&gt;im_i2c
)paren
suffix:semicolon
multiline_comment|/* Initialize Port B IIC pins.&n;&t;*/
id|cp-&gt;cp_pbpar
op_or_assign
l_int|0x00000030
suffix:semicolon
id|cp-&gt;cp_pbdir
op_or_assign
l_int|0x00000030
suffix:semicolon
id|cp-&gt;cp_pbodr
op_or_assign
l_int|0x00000030
suffix:semicolon
multiline_comment|/* Initialize the parameter ram.&n;&t;*/
multiline_comment|/* Allocate space for a two transmit and one receive buffer&n;&t; * descriptor in the DP ram.&n;&t; * For now, this address seems OK, but it may have to&n;&t; * change with newer versions of the firmware.&n;&t; */
id|dpaddr
op_assign
l_int|0x0840
suffix:semicolon
multiline_comment|/* Set up the IIC parameters in the parameter ram.&n;&t;*/
id|iip-&gt;iic_tbase
op_assign
id|dpaddr
suffix:semicolon
id|iip-&gt;iic_rbase
op_assign
id|dpaddr
op_plus
(paren
l_int|2
op_star
r_sizeof
(paren
id|cbd_t
)paren
)paren
suffix:semicolon
id|iip-&gt;iic_tfcr
op_assign
id|SMC_EB
suffix:semicolon
id|iip-&gt;iic_rfcr
op_assign
id|SMC_EB
suffix:semicolon
multiline_comment|/* This should really be done by the reader/writer.&n;&t;*/
id|iip-&gt;iic_mrblr
op_assign
l_int|128
suffix:semicolon
multiline_comment|/* Initialize Tx/Rx parameters.&n;&t;*/
id|cp-&gt;cp_cpcr
op_assign
id|mk_cr_cmd
c_func
(paren
id|CPM_CR_CH_I2C
comma
id|CPM_CR_INIT_TRX
)paren
op_or
id|CPM_CR_FLG
suffix:semicolon
r_while
c_loop
(paren
id|cp-&gt;cp_cpcr
op_amp
id|CPM_CR_FLG
)paren
suffix:semicolon
multiline_comment|/* Select an arbitrary address.  Just make sure it is unique.&n;&t;*/
id|i2c-&gt;i2c_i2add
op_assign
l_int|0x34
suffix:semicolon
multiline_comment|/* Make clock run maximum slow.&n;&t;*/
id|i2c-&gt;i2c_i2brg
op_assign
l_int|7
suffix:semicolon
multiline_comment|/* Disable interrupts.&n;&t;*/
id|i2c-&gt;i2c_i2cmr
op_assign
l_int|0
suffix:semicolon
id|i2c-&gt;i2c_i2cer
op_assign
l_int|0xff
suffix:semicolon
multiline_comment|/* Enable SDMA.&n;&t;*/
id|immap-&gt;im_siu_conf.sc_sdcr
op_assign
l_int|1
suffix:semicolon
id|iic_init_done
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Read from IIC.&n; * Caller provides device address, memory buffer, and byte count.&n; */
DECL|variable|iitemp
r_static
id|u_char
id|iitemp
(braket
l_int|32
)braket
suffix:semicolon
r_void
DECL|function|iic_read
id|iic_read
c_func
(paren
id|uint
id|devaddr
comma
id|u_char
op_star
id|buf
comma
id|uint
id|offset
comma
id|uint
id|count
)paren
(brace
r_volatile
id|iic_t
op_star
id|iip
suffix:semicolon
r_volatile
id|i2c8xx_t
op_star
id|i2c
suffix:semicolon
r_volatile
id|cbd_t
op_star
id|tbdf
comma
op_star
id|rbdf
suffix:semicolon
r_volatile
id|cpm8xx_t
op_star
id|cp
suffix:semicolon
r_volatile
id|immap_t
op_star
id|immap
suffix:semicolon
id|u_char
op_star
id|tb
suffix:semicolon
id|uint
id|temp
suffix:semicolon
multiline_comment|/* If the interface has not been initialized, do that now.&n;&t;*/
r_if
c_cond
(paren
op_logical_neg
id|iic_init_done
)paren
id|iic_init
c_func
(paren
)paren
suffix:semicolon
id|immap
op_assign
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
suffix:semicolon
id|cp
op_assign
(paren
id|cpm8xx_t
op_star
)paren
op_amp
(paren
id|immap-&gt;im_cpm
)paren
suffix:semicolon
id|iip
op_assign
(paren
id|iic_t
op_star
)paren
op_amp
id|cp-&gt;cp_dparam
(braket
id|PROFF_IIC
)braket
suffix:semicolon
id|i2c
op_assign
(paren
id|i2c8xx_t
op_star
)paren
op_amp
(paren
id|immap-&gt;im_i2c
)paren
suffix:semicolon
id|tbdf
op_assign
(paren
id|cbd_t
op_star
)paren
op_amp
id|cp-&gt;cp_dpmem
(braket
id|iip-&gt;iic_tbase
)braket
suffix:semicolon
id|rbdf
op_assign
(paren
id|cbd_t
op_star
)paren
op_amp
id|cp-&gt;cp_dpmem
(braket
id|iip-&gt;iic_rbase
)braket
suffix:semicolon
multiline_comment|/* Send a &quot;dummy write&quot; operation.  This is a write request with&n;&t; * only the offset sent, followed by another start condition.&n;&t; * This will ensure we start reading from the first location&n;&t; * of the EEPROM.&n;&t; */
id|tb
op_assign
id|iitemp
suffix:semicolon
id|tb
op_assign
(paren
id|u_char
op_star
)paren
(paren
(paren
(paren
id|uint
)paren
id|tb
op_plus
l_int|15
)paren
op_amp
op_complement
l_int|15
)paren
suffix:semicolon
id|tbdf-&gt;cbd_bufaddr
op_assign
(paren
r_int
)paren
id|tb
suffix:semicolon
op_star
id|tb
op_assign
id|devaddr
op_amp
l_int|0xfe
suffix:semicolon
multiline_comment|/* Device address */
op_star
(paren
id|tb
op_plus
l_int|1
)paren
op_assign
id|offset
suffix:semicolon
multiline_comment|/* Offset */
id|tbdf-&gt;cbd_datlen
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* Length */
id|tbdf-&gt;cbd_sc
op_assign
id|BD_SC_READY
op_or
id|BD_SC_LAST
op_or
id|BD_SC_WRAP
op_or
id|BD_IIC_START
suffix:semicolon
id|i2c-&gt;i2c_i2mod
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Enable */
id|i2c-&gt;i2c_i2cer
op_assign
l_int|0xff
suffix:semicolon
id|i2c-&gt;i2c_i2com
op_assign
l_int|0x81
suffix:semicolon
multiline_comment|/* Start master */
multiline_comment|/* Wait for IIC transfer.&n;&t;*/
macro_line|#if 0
r_while
c_loop
(paren
(paren
id|i2c-&gt;i2c_i2cer
op_amp
l_int|3
)paren
op_eq
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tbdf-&gt;cbd_sc
op_amp
id|BD_SC_READY
)paren
id|printf
c_func
(paren
l_string|&quot;IIC ra complete but tbuf ready&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
id|temp
op_assign
l_int|10000000
suffix:semicolon
r_while
c_loop
(paren
(paren
id|tbdf-&gt;cbd_sc
op_amp
id|BD_SC_READY
)paren
op_logical_and
(paren
id|temp
op_ne
l_int|0
)paren
)paren
id|temp
op_decrement
suffix:semicolon
macro_line|#if 0
multiline_comment|/* We can&squot;t do this...there is no serial port yet!&n;&t;*/
r_if
c_cond
(paren
id|temp
op_eq
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Timeout reading EEPROM&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
multiline_comment|/* Chip errata, clear enable.&n;&t;*/
id|i2c-&gt;i2c_i2mod
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* To read, we need an empty buffer of the proper length.&n;&t; * All that is used is the first byte for address, the remainder&n;&t; * is just used for timing (and doesn&squot;t really have to exist).&n;&t; */
id|tbdf-&gt;cbd_bufaddr
op_assign
(paren
r_int
)paren
id|tb
suffix:semicolon
op_star
id|tb
op_assign
id|devaddr
op_or
l_int|1
suffix:semicolon
multiline_comment|/* Device address */
id|rbdf-&gt;cbd_bufaddr
op_assign
(paren
id|uint
)paren
id|buf
suffix:semicolon
multiline_comment|/* Desination buffer */
id|tbdf-&gt;cbd_datlen
op_assign
id|rbdf-&gt;cbd_datlen
op_assign
id|count
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* Length */
id|tbdf-&gt;cbd_sc
op_assign
id|BD_SC_READY
op_or
id|BD_SC_LAST
op_or
id|BD_SC_WRAP
op_or
id|BD_IIC_START
suffix:semicolon
id|rbdf-&gt;cbd_sc
op_assign
id|BD_SC_EMPTY
op_or
id|BD_SC_WRAP
suffix:semicolon
multiline_comment|/* Chip bug, set enable here.&n;&t;*/
id|i2c-&gt;i2c_i2mod
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Enable */
id|i2c-&gt;i2c_i2cer
op_assign
l_int|0xff
suffix:semicolon
id|i2c-&gt;i2c_i2com
op_assign
l_int|0x81
suffix:semicolon
multiline_comment|/* Start master */
multiline_comment|/* Wait for IIC transfer.&n;&t;*/
macro_line|#if 0
r_while
c_loop
(paren
(paren
id|i2c-&gt;i2c_i2cer
op_amp
l_int|1
)paren
op_eq
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rbdf-&gt;cbd_sc
op_amp
id|BD_SC_EMPTY
)paren
id|printf
c_func
(paren
l_string|&quot;IIC read complete but rbuf empty&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
id|temp
op_assign
l_int|10000000
suffix:semicolon
r_while
c_loop
(paren
(paren
id|tbdf-&gt;cbd_sc
op_amp
id|BD_SC_READY
)paren
op_logical_and
(paren
id|temp
op_ne
l_int|0
)paren
)paren
id|temp
op_decrement
suffix:semicolon
macro_line|#endif
multiline_comment|/* Chip errata, clear enable.&n;&t;*/
id|i2c-&gt;i2c_i2mod
op_assign
l_int|0
suffix:semicolon
)brace
eof
