multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/* Board specific functions for those embedded 8xx boards that do&n; * not have boot monitor support for board information.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifdef CONFIG_8xx
macro_line|#include &lt;asm/mpc8xx.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_8260
macro_line|#include &lt;asm/mpc8260.h&gt;
macro_line|#include &lt;asm/immap_8260.h&gt;
macro_line|#endif
multiline_comment|/* For those boards that don&squot;t provide one.&n;*/
macro_line|#if !defined(CONFIG_MBX)
DECL|variable|bdinfo
r_static
id|bd_t
id|bdinfo
suffix:semicolon
macro_line|#endif
multiline_comment|/* IIC functions.&n; * These are just the basic master read/write operations so we can&n; * examine serial EEPROM.&n; */
r_extern
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
multiline_comment|/* Supply a default Ethernet address for those eval boards that don&squot;t&n; * ship with one.  This is an address from the MBX board I have, so&n; * it is unlikely you will find it on your network.&n; */
DECL|variable|def_enet_addr
r_static
id|ushort
id|def_enet_addr
(braket
)braket
op_assign
(brace
l_int|0x0800
comma
l_int|0x3e26
comma
l_int|0x1559
)brace
suffix:semicolon
macro_line|#if defined(CONFIG_MBX)
multiline_comment|/* The MBX hands us a pretty much ready to go board descriptor.  This&n; * is where the idea started in the first place.&n; */
r_void
DECL|function|embed_config
id|embed_config
c_func
(paren
id|bd_t
op_star
op_star
id|bdp
)paren
(brace
id|u_char
op_star
id|mp
suffix:semicolon
id|u_char
id|eebuf
(braket
l_int|128
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
id|bd_t
op_star
id|bd
suffix:semicolon
id|bd
op_assign
op_star
id|bdp
suffix:semicolon
multiline_comment|/* Read the first 128 bytes of the EEPROM.  There is more,&n;&t; * but this is all we need.&n;&t; */
id|iic_read
c_func
(paren
l_int|0xa4
comma
id|eebuf
comma
l_int|0
comma
l_int|128
)paren
suffix:semicolon
multiline_comment|/* All we are looking for is the Ethernet MAC address.  The&n;&t; * first 8 bytes are &squot;MOTOROLA&squot;, so check for part of that.&n;&t; * If it&squot;s there, assume we have a valid MAC address.  If not,&n;&t; * grab our default one.&n;&t; */
r_if
c_cond
(paren
(paren
op_star
(paren
id|uint
op_star
)paren
id|eebuf
)paren
op_eq
l_int|0x4d4f544f
)paren
id|mp
op_assign
op_amp
id|eebuf
(braket
l_int|0x4c
)braket
suffix:semicolon
r_else
id|mp
op_assign
(paren
id|u_char
op_star
)paren
id|def_enet_addr
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
id|bd-&gt;bi_enetaddr
(braket
id|i
)braket
op_assign
op_star
id|mp
op_increment
suffix:semicolon
multiline_comment|/* The boot rom passes these to us in MHz.  Linux now expects&n;&t; * them to be in Hz.&n;&t; */
id|bd-&gt;bi_intfreq
op_mul_assign
l_int|1000000
suffix:semicolon
id|bd-&gt;bi_busfreq
op_mul_assign
l_int|1000000
suffix:semicolon
multiline_comment|/* Stuff a baud rate here as well.&n;&t;*/
id|bd-&gt;bi_baudrate
op_assign
l_int|9600
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_MBX */
macro_line|#if defined(CONFIG_RPXLITE) || defined(CONFIG_RPXCLASSIC) || &bslash;&n;&t;defined(CONFIG_RPX6) || defined(CONFIG_EP405)
multiline_comment|/* Helper functions for Embedded Planet boards.&n;*/
multiline_comment|/* Because I didn&squot;t find anything that would do this.......&n;*/
id|u_char
DECL|function|aschex_to_byte
id|aschex_to_byte
c_func
(paren
id|u_char
op_star
id|cp
)paren
(brace
id|u_char
id|byte
comma
id|c
suffix:semicolon
id|c
op_assign
op_star
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c
op_ge
l_char|&squot;A&squot;
)paren
op_logical_and
(paren
id|c
op_le
l_char|&squot;F&squot;
)paren
)paren
(brace
id|c
op_sub_assign
l_char|&squot;A&squot;
suffix:semicolon
id|c
op_add_assign
l_int|10
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|c
op_ge
l_char|&squot;a&squot;
)paren
op_logical_and
(paren
id|c
op_le
l_char|&squot;f&squot;
)paren
)paren
(brace
id|c
op_sub_assign
l_char|&squot;a&squot;
suffix:semicolon
id|c
op_add_assign
l_int|10
suffix:semicolon
)brace
r_else
id|c
op_sub_assign
l_char|&squot;0&squot;
suffix:semicolon
id|byte
op_assign
id|c
op_star
l_int|16
suffix:semicolon
id|c
op_assign
op_star
id|cp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c
op_ge
l_char|&squot;A&squot;
)paren
op_logical_and
(paren
id|c
op_le
l_char|&squot;F&squot;
)paren
)paren
(brace
id|c
op_sub_assign
l_char|&squot;A&squot;
suffix:semicolon
id|c
op_add_assign
l_int|10
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|c
op_ge
l_char|&squot;a&squot;
)paren
op_logical_and
(paren
id|c
op_le
l_char|&squot;f&squot;
)paren
)paren
(brace
id|c
op_sub_assign
l_char|&squot;a&squot;
suffix:semicolon
id|c
op_add_assign
l_int|10
suffix:semicolon
)brace
r_else
id|c
op_sub_assign
l_char|&squot;0&squot;
suffix:semicolon
id|byte
op_add_assign
id|c
suffix:semicolon
r_return
id|byte
suffix:semicolon
)brace
r_static
r_void
DECL|function|rpx_eth
id|rpx_eth
c_func
(paren
id|bd_t
op_star
id|bd
comma
id|u_char
op_star
id|cp
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bd-&gt;bi_enetaddr
(braket
id|i
)braket
op_assign
id|aschex_to_byte
c_func
(paren
id|cp
)paren
suffix:semicolon
id|cp
op_add_assign
l_int|2
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_RPX6
r_static
id|uint
DECL|function|rpx_baseten
id|rpx_baseten
c_func
(paren
id|u_char
op_star
id|cp
)paren
(brace
id|uint
id|retval
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|cp
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|retval
op_mul_assign
l_int|10
suffix:semicolon
id|retval
op_add_assign
(paren
op_star
id|cp
)paren
op_minus
l_char|&squot;0&squot;
suffix:semicolon
id|cp
op_increment
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_RPXLITE) || defined(CONFIG_RPXCLASSIC)
r_static
r_void
DECL|function|rpx_brate
id|rpx_brate
c_func
(paren
id|bd_t
op_star
id|bd
comma
id|u_char
op_star
id|cp
)paren
(brace
id|uint
id|rate
suffix:semicolon
id|rate
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|cp
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|rate
op_mul_assign
l_int|10
suffix:semicolon
id|rate
op_add_assign
(paren
op_star
id|cp
)paren
op_minus
l_char|&squot;0&squot;
suffix:semicolon
id|cp
op_increment
suffix:semicolon
)brace
id|bd-&gt;bi_baudrate
op_assign
id|rate
op_star
l_int|100
suffix:semicolon
)brace
r_static
r_void
DECL|function|rpx_cpuspeed
id|rpx_cpuspeed
c_func
(paren
id|bd_t
op_star
id|bd
comma
id|u_char
op_star
id|cp
)paren
(brace
id|uint
id|num
comma
id|den
suffix:semicolon
id|num
op_assign
id|den
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|cp
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|num
op_mul_assign
l_int|10
suffix:semicolon
id|num
op_add_assign
(paren
op_star
id|cp
)paren
op_minus
l_char|&squot;0&squot;
suffix:semicolon
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;/&squot;
)paren
(brace
id|cp
op_increment
suffix:semicolon
id|den
op_assign
(paren
op_star
id|cp
)paren
op_minus
l_char|&squot;0&squot;
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* I don&squot;t know why the RPX just can&squot;t state the actual&n;&t; * CPU speed.....&n;&t; */
r_if
c_cond
(paren
id|den
)paren
(brace
id|num
op_div_assign
id|den
suffix:semicolon
id|num
op_mul_assign
id|den
suffix:semicolon
)brace
id|bd-&gt;bi_intfreq
op_assign
id|bd-&gt;bi_busfreq
op_assign
id|num
op_star
l_int|1000000
suffix:semicolon
multiline_comment|/* The 8xx can only run a maximum 50 MHz bus speed (until&n;&t; * Motorola changes this :-).  Greater than 50 MHz parts&n;&t; * run internal/2 for bus speed.&n;&t; */
r_if
c_cond
(paren
id|num
OG
l_int|50
)paren
id|bd-&gt;bi_busfreq
op_div_assign
l_int|2
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_RPXLITE) || defined(CONFIG_RPXCLASSIC) || defined(CONFIG_EP405)
r_static
r_void
DECL|function|rpx_memsize
id|rpx_memsize
c_func
(paren
id|bd_t
op_star
id|bd
comma
id|u_char
op_star
id|cp
)paren
(brace
id|uint
id|size
suffix:semicolon
id|size
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|cp
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|size
op_mul_assign
l_int|10
suffix:semicolon
id|size
op_add_assign
(paren
op_star
id|cp
)paren
op_minus
l_char|&squot;0&squot;
suffix:semicolon
id|cp
op_increment
suffix:semicolon
)brace
id|bd-&gt;bi_memsize
op_assign
id|size
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
)brace
macro_line|#endif /* LITE || CLASSIC || EP405 */
macro_line|#if defined(CONFIG_EP405)
r_static
r_void
DECL|function|rpx_nvramsize
id|rpx_nvramsize
c_func
(paren
id|bd_t
op_star
id|bd
comma
id|u_char
op_star
id|cp
)paren
(brace
id|uint
id|size
suffix:semicolon
id|size
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|cp
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|size
op_mul_assign
l_int|10
suffix:semicolon
id|size
op_add_assign
(paren
op_star
id|cp
)paren
op_minus
l_char|&squot;0&squot;
suffix:semicolon
id|cp
op_increment
suffix:semicolon
)brace
id|bd-&gt;bi_nvramsize
op_assign
id|size
op_star
l_int|1024
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_EP405 */
macro_line|#endif&t;/* Embedded Planet boards */
macro_line|#if defined(CONFIG_RPXLITE) || defined(CONFIG_RPXCLASSIC)
multiline_comment|/* Read the EEPROM on the RPX-Lite board.&n;*/
r_void
DECL|function|embed_config
id|embed_config
c_func
(paren
id|bd_t
op_star
op_star
id|bdp
)paren
(brace
id|u_char
id|eebuf
(braket
l_int|256
)braket
comma
op_star
id|cp
suffix:semicolon
id|bd_t
op_star
id|bd
suffix:semicolon
multiline_comment|/* Read the first 256 bytes of the EEPROM.  I think this&n;&t; * is really all there is, and I hope if it gets bigger the&n;&t; * info we want is still up front.&n;&t; */
id|bd
op_assign
op_amp
id|bdinfo
suffix:semicolon
op_star
id|bdp
op_assign
id|bd
suffix:semicolon
macro_line|#if 1
id|iic_read
c_func
(paren
l_int|0xa8
comma
id|eebuf
comma
l_int|0
comma
l_int|128
)paren
suffix:semicolon
id|iic_read
c_func
(paren
l_int|0xa8
comma
op_amp
id|eebuf
(braket
l_int|128
)braket
comma
l_int|128
comma
l_int|128
)paren
suffix:semicolon
multiline_comment|/* We look for two things, the Ethernet address and the&n;&t; * serial baud rate.  The records are separated by&n;&t; * newlines.&n;&t; */
id|cp
op_assign
id|eebuf
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;E&squot;
)paren
(brace
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;A&squot;
)paren
(brace
id|cp
op_add_assign
l_int|2
suffix:semicolon
id|rpx_eth
c_func
(paren
id|bd
comma
id|cp
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;S&squot;
)paren
(brace
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;B&squot;
)paren
(brace
id|cp
op_add_assign
l_int|2
suffix:semicolon
id|rpx_brate
c_func
(paren
id|bd
comma
id|cp
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;D&squot;
)paren
(brace
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;1&squot;
)paren
(brace
id|cp
op_add_assign
l_int|2
suffix:semicolon
id|rpx_memsize
c_func
(paren
id|bd
comma
id|cp
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;H&squot;
)paren
(brace
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;Z&squot;
)paren
(brace
id|cp
op_add_assign
l_int|2
suffix:semicolon
id|rpx_cpuspeed
c_func
(paren
id|bd
comma
id|cp
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Scan to the end of the record.&n;&t;&t;*/
r_while
c_loop
(paren
(paren
op_star
id|cp
op_ne
l_char|&squot;&bslash;n&squot;
)paren
op_logical_and
(paren
op_star
id|cp
op_ne
l_int|0xff
)paren
)paren
id|cp
op_increment
suffix:semicolon
multiline_comment|/* If the next character is a 0 or ff, we are done.&n;&t;&t;*/
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|cp
op_eq
l_int|0
)paren
op_logical_or
(paren
op_star
id|cp
op_eq
l_int|0xff
)paren
)paren
r_break
suffix:semicolon
)brace
id|bd-&gt;bi_memstart
op_assign
l_int|0
suffix:semicolon
macro_line|#else
multiline_comment|/* For boards without initialized EEPROM.&n;&t;*/
id|bd-&gt;bi_memstart
op_assign
l_int|0
suffix:semicolon
id|bd-&gt;bi_memsize
op_assign
(paren
l_int|8
op_star
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
id|bd-&gt;bi_intfreq
op_assign
l_int|48000000
suffix:semicolon
id|bd-&gt;bi_busfreq
op_assign
l_int|48000000
suffix:semicolon
id|bd-&gt;bi_baudrate
op_assign
l_int|9600
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif /* RPXLITE || RPXCLASSIC */
macro_line|#ifdef CONFIG_BSEIP
multiline_comment|/* Build a board information structure for the BSE ip-Engine.&n; * There is more to come since we will add some environment&n; * variables and a function to read them.&n; */
r_void
DECL|function|embed_config
id|embed_config
c_func
(paren
id|bd_t
op_star
op_star
id|bdp
)paren
(brace
id|u_char
op_star
id|cp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|bd_t
op_star
id|bd
suffix:semicolon
id|bd
op_assign
op_amp
id|bdinfo
suffix:semicolon
op_star
id|bdp
op_assign
id|bd
suffix:semicolon
multiline_comment|/* Baud rate and processor speed will eventually come&n;&t; * from the environment variables.&n;&t; */
id|bd-&gt;bi_baudrate
op_assign
l_int|9600
suffix:semicolon
multiline_comment|/* Get the Ethernet station address from the Flash ROM.&n;&t;*/
id|cp
op_assign
(paren
id|u_char
op_star
)paren
l_int|0xfe003ffa
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bd-&gt;bi_enetaddr
(braket
id|i
)braket
op_assign
op_star
id|cp
op_increment
suffix:semicolon
)brace
multiline_comment|/* The rest of this should come from the environment as well.&n;&t;*/
id|bd-&gt;bi_memstart
op_assign
l_int|0
suffix:semicolon
id|bd-&gt;bi_memsize
op_assign
(paren
l_int|16
op_star
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
id|bd-&gt;bi_intfreq
op_assign
l_int|48000000
suffix:semicolon
id|bd-&gt;bi_busfreq
op_assign
l_int|48000000
suffix:semicolon
)brace
macro_line|#endif /* BSEIP */
macro_line|#ifdef CONFIG_FADS
multiline_comment|/* Build a board information structure for the FADS.&n; */
r_void
DECL|function|embed_config
id|embed_config
c_func
(paren
id|bd_t
op_star
op_star
id|bdp
)paren
(brace
id|u_char
op_star
id|cp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|bd_t
op_star
id|bd
suffix:semicolon
id|bd
op_assign
op_amp
id|bdinfo
suffix:semicolon
op_star
id|bdp
op_assign
id|bd
suffix:semicolon
multiline_comment|/* Just fill in some known values.&n;&t; */
id|bd-&gt;bi_baudrate
op_assign
l_int|9600
suffix:semicolon
multiline_comment|/* Use default enet.&n;&t;*/
id|cp
op_assign
(paren
id|u_char
op_star
)paren
id|def_enet_addr
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bd-&gt;bi_enetaddr
(braket
id|i
)braket
op_assign
op_star
id|cp
op_increment
suffix:semicolon
)brace
id|bd-&gt;bi_memstart
op_assign
l_int|0
suffix:semicolon
id|bd-&gt;bi_memsize
op_assign
(paren
l_int|8
op_star
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
id|bd-&gt;bi_intfreq
op_assign
l_int|40000000
suffix:semicolon
id|bd-&gt;bi_busfreq
op_assign
l_int|40000000
suffix:semicolon
)brace
macro_line|#endif /* FADS */
macro_line|#ifdef CONFIG_8260
multiline_comment|/* Compute 8260 clock values if the rom doesn&squot;t provide them.&n; * We can&squot;t compute the internal core frequency (I don&squot;t know how to&n; * do that).&n; */
r_static
r_void
DECL|function|clk_8260
id|clk_8260
c_func
(paren
id|bd_t
op_star
id|bd
)paren
(brace
id|uint
id|scmr
comma
id|vco_out
comma
id|clkin
suffix:semicolon
id|uint
id|plldf
comma
id|pllmf
comma
id|busdf
comma
id|brgdf
comma
id|cpmdf
suffix:semicolon
r_volatile
id|immap_t
op_star
id|ip
suffix:semicolon
id|ip
op_assign
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
suffix:semicolon
id|scmr
op_assign
id|ip-&gt;im_clkrst.car_scmr
suffix:semicolon
multiline_comment|/* The clkin is always bus frequency.&n;&t;*/
id|clkin
op_assign
id|bd-&gt;bi_busfreq
suffix:semicolon
multiline_comment|/* Collect the bits from the scmr.&n;&t;*/
id|plldf
op_assign
(paren
id|scmr
op_rshift
l_int|12
)paren
op_amp
l_int|1
suffix:semicolon
id|pllmf
op_assign
id|scmr
op_amp
l_int|0xfff
suffix:semicolon
id|cpmdf
op_assign
(paren
id|scmr
op_rshift
l_int|16
)paren
op_amp
l_int|0x0f
suffix:semicolon
id|busdf
op_assign
(paren
id|scmr
op_rshift
l_int|20
)paren
op_amp
l_int|0x0f
suffix:semicolon
multiline_comment|/* This is arithmetic from the 8260 manual.&n;&t;*/
id|vco_out
op_assign
id|clkin
op_div
(paren
id|plldf
op_plus
l_int|1
)paren
suffix:semicolon
id|vco_out
op_mul_assign
l_int|2
op_star
(paren
id|pllmf
op_plus
l_int|1
)paren
suffix:semicolon
id|bd-&gt;bi_vco
op_assign
id|vco_out
suffix:semicolon
multiline_comment|/* Save for later */
id|bd-&gt;bi_cpmfreq
op_assign
id|vco_out
op_div
l_int|2
suffix:semicolon
multiline_comment|/* CPM Freq, in MHz */
multiline_comment|/* Set Baud rate divisor.  The power up default is divide by 16,&n;&t; * but we set it again here in case it was changed.&n;&t; */
id|ip-&gt;im_clkrst.car_sccr
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* DIV 16 BRG */
id|bd-&gt;bi_brgfreq
op_assign
id|vco_out
op_div
l_int|16
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_EST8260
r_void
DECL|function|embed_config
id|embed_config
c_func
(paren
id|bd_t
op_star
op_star
id|bdp
)paren
(brace
id|u_char
op_star
id|cp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|bd_t
op_star
id|bd
suffix:semicolon
id|bd
op_assign
op_star
id|bdp
suffix:semicolon
macro_line|#if 0
multiline_comment|/* This is actually provided by my boot rom.  I have it&n;&t; * here for those people that may load the kernel with&n;&t; * a JTAG/COP tool and not the rom monitor.&n;&t; */
id|bd-&gt;bi_baudrate
op_assign
l_int|115200
suffix:semicolon
id|bd-&gt;bi_intfreq
op_assign
l_int|200000000
suffix:semicolon
id|bd-&gt;bi_busfreq
op_assign
l_int|66666666
suffix:semicolon
id|bd-&gt;bi_cpmfreq
op_assign
l_int|66666666
suffix:semicolon
id|bd-&gt;bi_brgfreq
op_assign
l_int|33333333
suffix:semicolon
id|bd-&gt;bi_memsize
op_assign
l_int|16
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
macro_line|#else
multiline_comment|/* The boot rom passes these to us in MHz.  Linux now expects&n;&t; * them to be in Hz.&n;&t; */
id|bd-&gt;bi_intfreq
op_mul_assign
l_int|1000000
suffix:semicolon
id|bd-&gt;bi_busfreq
op_mul_assign
l_int|1000000
suffix:semicolon
id|bd-&gt;bi_cpmfreq
op_mul_assign
l_int|1000000
suffix:semicolon
id|bd-&gt;bi_brgfreq
op_mul_assign
l_int|1000000
suffix:semicolon
macro_line|#endif
id|cp
op_assign
(paren
id|u_char
op_star
)paren
id|def_enet_addr
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bd-&gt;bi_enetaddr
(braket
id|i
)braket
op_assign
op_star
id|cp
op_increment
suffix:semicolon
)brace
)brace
macro_line|#endif /* EST8260 */
macro_line|#ifdef CONFIG_SBS8260
r_void
DECL|function|embed_config
id|embed_config
c_func
(paren
id|bd_t
op_star
op_star
id|bdp
)paren
(brace
id|u_char
op_star
id|cp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|bd_t
op_star
id|bd
suffix:semicolon
multiline_comment|/* This should provided by the boot rom.&n;&t; */
id|bd
op_assign
op_amp
id|bdinfo
suffix:semicolon
op_star
id|bdp
op_assign
id|bd
suffix:semicolon
id|bd-&gt;bi_baudrate
op_assign
l_int|9600
suffix:semicolon
id|bd-&gt;bi_memsize
op_assign
l_int|64
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
multiline_comment|/* Set all of the clocks.  We have to know the speed of the&n;&t; * external clock.  The development board had 66 MHz.&n;&t; */
id|bd-&gt;bi_busfreq
op_assign
l_int|66666666
suffix:semicolon
id|clk_8260
c_func
(paren
id|bd
)paren
suffix:semicolon
multiline_comment|/* I don&squot;t know how to compute this yet.&n;&t;*/
id|bd-&gt;bi_intfreq
op_assign
l_int|133000000
suffix:semicolon
id|cp
op_assign
(paren
id|u_char
op_star
)paren
id|def_enet_addr
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bd-&gt;bi_enetaddr
(braket
id|i
)braket
op_assign
op_star
id|cp
op_increment
suffix:semicolon
)brace
)brace
macro_line|#endif /* SBS8260 */
macro_line|#ifdef CONFIG_RPX6
r_void
DECL|function|embed_config
id|embed_config
c_func
(paren
id|bd_t
op_star
op_star
id|bdp
)paren
(brace
id|u_char
op_star
id|cp
comma
op_star
id|keyvals
suffix:semicolon
r_int
id|i
suffix:semicolon
id|bd_t
op_star
id|bd
suffix:semicolon
id|keyvals
op_assign
(paren
id|u_char
op_star
)paren
op_star
id|bdp
suffix:semicolon
id|bd
op_assign
op_amp
id|bdinfo
suffix:semicolon
op_star
id|bdp
op_assign
id|bd
suffix:semicolon
multiline_comment|/* This is almost identical to the RPX-Lite/Classic functions&n;&t; * on the 8xx boards.  It would be nice to have a key lookup&n;&t; * function in a string, but the format of all of the fields&n;&t; * is slightly different.&n;&t; */
id|cp
op_assign
id|keyvals
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;E&squot;
)paren
(brace
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;A&squot;
)paren
(brace
id|cp
op_add_assign
l_int|2
suffix:semicolon
id|rpx_eth
c_func
(paren
id|bd
comma
id|cp
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;S&squot;
)paren
(brace
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;B&squot;
)paren
(brace
id|cp
op_add_assign
l_int|2
suffix:semicolon
id|bd-&gt;bi_baudrate
op_assign
id|rpx_baseten
c_func
(paren
id|cp
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;D&squot;
)paren
(brace
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;1&squot;
)paren
(brace
id|cp
op_add_assign
l_int|2
suffix:semicolon
id|bd-&gt;bi_memsize
op_assign
id|rpx_baseten
c_func
(paren
id|cp
)paren
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;X&squot;
)paren
(brace
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;T&squot;
)paren
(brace
id|cp
op_add_assign
l_int|2
suffix:semicolon
id|bd-&gt;bi_busfreq
op_assign
id|rpx_baseten
c_func
(paren
id|cp
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;N&squot;
)paren
(brace
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;V&squot;
)paren
(brace
id|cp
op_add_assign
l_int|2
suffix:semicolon
id|bd-&gt;bi_nvsize
op_assign
id|rpx_baseten
c_func
(paren
id|cp
)paren
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
)brace
)brace
multiline_comment|/* Scan to the end of the record.&n;&t;&t;*/
r_while
c_loop
(paren
(paren
op_star
id|cp
op_ne
l_char|&squot;&bslash;n&squot;
)paren
op_logical_and
(paren
op_star
id|cp
op_ne
l_int|0xff
)paren
)paren
id|cp
op_increment
suffix:semicolon
multiline_comment|/* If the next character is a 0 or ff, we are done.&n;&t;&t;*/
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|cp
op_eq
l_int|0
)paren
op_logical_or
(paren
op_star
id|cp
op_eq
l_int|0xff
)paren
)paren
r_break
suffix:semicolon
)brace
id|bd-&gt;bi_memstart
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* The memory size includes both the 60x and local bus DRAM.&n;&t; * I don&squot;t want to use the local bus DRAM for real memory,&n;&t; * so subtract it out.  It would be nice if they were separate&n;&t; * keys.&n;&t; */
id|bd-&gt;bi_memsize
op_sub_assign
l_int|32
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
multiline_comment|/* Set all of the clocks.  We have to know the speed of the&n;&t; * external clock.&n;&t; */
id|clk_8260
c_func
(paren
id|bd
)paren
suffix:semicolon
multiline_comment|/* I don&squot;t know how to compute this yet.&n;&t;*/
id|bd-&gt;bi_intfreq
op_assign
l_int|200000000
suffix:semicolon
)brace
macro_line|#endif /* RPX6 for testing */
macro_line|#ifdef CONFIG_ADS8260
r_void
DECL|function|embed_config
id|embed_config
c_func
(paren
id|bd_t
op_star
op_star
id|bdp
)paren
(brace
id|u_char
op_star
id|cp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|bd_t
op_star
id|bd
suffix:semicolon
multiline_comment|/* This should provided by the boot rom.&n;&t; */
id|bd
op_assign
op_amp
id|bdinfo
suffix:semicolon
op_star
id|bdp
op_assign
id|bd
suffix:semicolon
id|bd-&gt;bi_baudrate
op_assign
l_int|9600
suffix:semicolon
id|bd-&gt;bi_memsize
op_assign
l_int|16
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
multiline_comment|/* Set all of the clocks.  We have to know the speed of the&n;&t; * external clock.  The development board had 66 MHz.&n;&t; */
id|bd-&gt;bi_busfreq
op_assign
l_int|66666666
suffix:semicolon
id|clk_8260
c_func
(paren
id|bd
)paren
suffix:semicolon
multiline_comment|/* I don&squot;t know how to compute this yet.&n;&t;*/
id|bd-&gt;bi_intfreq
op_assign
l_int|200000000
suffix:semicolon
id|cp
op_assign
(paren
id|u_char
op_star
)paren
id|def_enet_addr
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bd-&gt;bi_enetaddr
(braket
id|i
)braket
op_assign
op_star
id|cp
op_increment
suffix:semicolon
)brace
)brace
macro_line|#endif /* ADS8260 */
macro_line|#ifdef CONFIG_WILLOW
r_void
DECL|function|embed_config
id|embed_config
c_func
(paren
id|bd_t
op_star
op_star
id|bdp
)paren
(brace
id|u_char
op_star
id|cp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|bd_t
op_star
id|bd
suffix:semicolon
multiline_comment|/* Willow has Open Firmware....I should learn how to get this&n;&t; * information from it.&n;&t; */
id|bd
op_assign
op_amp
id|bdinfo
suffix:semicolon
op_star
id|bdp
op_assign
id|bd
suffix:semicolon
id|bd-&gt;bi_baudrate
op_assign
l_int|9600
suffix:semicolon
id|bd-&gt;bi_memsize
op_assign
l_int|32
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
multiline_comment|/* Set all of the clocks.  We have to know the speed of the&n;&t; * external clock.  The development board had 66 MHz.&n;&t; */
id|bd-&gt;bi_busfreq
op_assign
l_int|66666666
suffix:semicolon
id|clk_8260
c_func
(paren
id|bd
)paren
suffix:semicolon
multiline_comment|/* I don&squot;t know how to compute this yet.&n;&t;*/
id|bd-&gt;bi_intfreq
op_assign
l_int|200000000
suffix:semicolon
id|cp
op_assign
(paren
id|u_char
op_star
)paren
id|def_enet_addr
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bd-&gt;bi_enetaddr
(braket
id|i
)braket
op_assign
op_star
id|cp
op_increment
suffix:semicolon
)brace
)brace
macro_line|#endif /* WILLOW */
macro_line|#ifdef CONFIG_TREEBOOT
multiline_comment|/* This could possibly work for all treeboot roms.&n;*/
macro_line|#if defined(CONFIG_ASH)
DECL|macro|BOARD_INFO_VECTOR
mdefine_line|#define BOARD_INFO_VECTOR       0xFFF80B50 /* openbios 1.19 moved this vector down  - armin */
macro_line|#else
DECL|macro|BOARD_INFO_VECTOR
mdefine_line|#define&t;BOARD_INFO_VECTOR&t;0xFFFE0B50
macro_line|#endif
r_void
DECL|function|embed_config
id|embed_config
c_func
(paren
id|bd_t
op_star
op_star
id|bdp
)paren
(brace
id|u_char
op_star
id|cp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|bd_t
op_star
id|bd
comma
op_star
id|treeboot_bd
suffix:semicolon
id|bd_t
op_star
(paren
op_star
id|get_board_info
)paren
(paren
r_void
)paren
op_assign
(paren
id|bd_t
op_star
(paren
op_star
)paren
(paren
r_void
)paren
)paren
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|BOARD_INFO_VECTOR
)paren
suffix:semicolon
macro_line|#if !defined(CONFIG_STB03xxx)
r_volatile
id|emac_t
op_star
id|emacp
suffix:semicolon
id|emacp
op_assign
(paren
id|emac_t
op_star
)paren
id|EMAC0_BASE
suffix:semicolon
multiline_comment|/* assume 1st emac - armin */
multiline_comment|/* shut down the Ethernet controller that the boot rom&n;&t; * sometimes leaves running.&n;&t; */
id|mtdcr
c_func
(paren
id|DCRN_MALCR
c_func
(paren
id|DCRN_MAL_BASE
)paren
comma
id|MALCR_MMSR
)paren
suffix:semicolon
multiline_comment|/* 1st reset MAL */
r_while
c_loop
(paren
id|mfdcr
c_func
(paren
id|DCRN_MALCR
c_func
(paren
id|DCRN_MAL_BASE
)paren
)paren
op_amp
id|MALCR_MMSR
)paren
(brace
)brace
suffix:semicolon
multiline_comment|/* wait for the reset */
id|emacp-&gt;em0mr0
op_assign
l_int|0x20000000
suffix:semicolon
multiline_comment|/* then reset EMAC */
id|eieio
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|bd
op_assign
op_amp
id|bdinfo
suffix:semicolon
op_star
id|bdp
op_assign
id|bd
suffix:semicolon
r_if
c_cond
(paren
(paren
id|treeboot_bd
op_assign
id|get_board_info
c_func
(paren
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|memcpy
c_func
(paren
id|bd
comma
id|treeboot_bd
comma
r_sizeof
(paren
id|bd_t
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Hmmm...better try to stuff some defaults.&n;&t;&t;*/
id|bd-&gt;bi_memsize
op_assign
l_int|16
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
id|cp
op_assign
(paren
id|u_char
op_star
)paren
id|def_enet_addr
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* I should probably put different ones here,&n;&t;&t;&t; * hopefully only one is used.&n;&t;&t;&t; */
id|bd
op_member_access_from_pointer
id|BD_EMAC_ADDR
c_func
(paren
l_int|0
comma
id|i
)paren
op_assign
op_star
id|cp
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
id|bd-&gt;bi_pci_enetaddr
(braket
id|i
)braket
op_assign
op_star
id|cp
op_increment
suffix:semicolon
macro_line|#endif
)brace
id|bd-&gt;bi_tbfreq
op_assign
l_int|200
op_star
l_int|1000
op_star
l_int|1000
suffix:semicolon
id|bd-&gt;bi_intfreq
op_assign
l_int|200000000
suffix:semicolon
id|bd-&gt;bi_busfreq
op_assign
l_int|100000000
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
id|bd-&gt;bi_pci_busfreq
op_assign
l_int|66666666
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Yeah, this look weird, but on Redwood 4 they are&n;&t; * different object in the structure.  When RW5 uses&n;&t; * OpenBIOS, it requires a special value.&n;&t; */
macro_line|#ifdef CONFIG_REDWOOD_5
id|bd-&gt;bi_tbfreq
op_assign
l_int|27
op_star
l_int|1000
op_star
l_int|1000
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_EP405
macro_line|#include &lt;linux/serial_reg.h&gt;
r_void
DECL|function|embed_config
id|embed_config
c_func
(paren
id|bd_t
op_star
op_star
id|bdp
)paren
(brace
id|u32
id|chcr0
suffix:semicolon
id|u_char
op_star
id|cp
suffix:semicolon
id|bd_t
op_star
id|bd
suffix:semicolon
multiline_comment|/* Different versions of the PlanetCore firmware vary in how&n;&t;   they set up the serial port - in particular whether they&n;&t;   use the internal or external serial clock for UART0.  Make&n;&t;   sure the UART is in a known state. */
multiline_comment|/* FIXME: We should use the board&squot;s 11.0592MHz external serial&n;&t;   clock - it will be more accurate for serial rates.  For&n;&t;   now, however the baud rates in ep405.h are for the internal&n;&t;   clock. */
id|chcr0
op_assign
id|mfdcr
c_func
(paren
id|DCRN_CHCR0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|chcr0
op_amp
l_int|0x1fff
)paren
op_ne
l_int|0x103e
)paren
(brace
id|mtdcr
c_func
(paren
id|DCRN_CHCR0
comma
(paren
id|chcr0
op_amp
l_int|0xffffe000
)paren
op_or
l_int|0x103e
)paren
suffix:semicolon
multiline_comment|/* The following tricks serial_init() into resetting the baud rate */
id|writeb
c_func
(paren
l_int|0
comma
id|UART0_IO_BASE
op_plus
id|UART_LCR
)paren
suffix:semicolon
)brace
id|bd
op_assign
op_amp
id|bdinfo
suffix:semicolon
op_star
id|bdp
op_assign
id|bd
suffix:semicolon
macro_line|#if 1
id|cp
op_assign
(paren
id|u_char
op_star
)paren
l_int|0xF0000EE0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;E&squot;
)paren
(brace
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;A&squot;
)paren
(brace
id|cp
op_add_assign
l_int|2
suffix:semicolon
id|rpx_eth
c_func
(paren
id|bd
comma
id|cp
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;D&squot;
)paren
(brace
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;1&squot;
)paren
(brace
id|cp
op_add_assign
l_int|2
suffix:semicolon
id|rpx_memsize
c_func
(paren
id|bd
comma
id|cp
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;N&squot;
)paren
(brace
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;V&squot;
)paren
(brace
id|cp
op_add_assign
l_int|2
suffix:semicolon
id|rpx_nvramsize
c_func
(paren
id|bd
comma
id|cp
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
(paren
op_star
id|cp
op_ne
l_char|&squot;&bslash;n&squot;
)paren
op_logical_and
(paren
op_star
id|cp
op_ne
l_int|0xff
)paren
)paren
id|cp
op_increment
suffix:semicolon
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|cp
op_eq
l_int|0
)paren
op_logical_or
(paren
op_star
id|cp
op_eq
l_int|0xff
)paren
)paren
r_break
suffix:semicolon
)brace
id|bd-&gt;bi_intfreq
op_assign
l_int|200000000
suffix:semicolon
id|bd-&gt;bi_busfreq
op_assign
l_int|100000000
suffix:semicolon
id|bd-&gt;bi_pci_busfreq
op_assign
l_int|33000000
suffix:semicolon
macro_line|#else
id|bd-&gt;bi_memsize
op_assign
l_int|64000000
suffix:semicolon
id|bd-&gt;bi_intfreq
op_assign
l_int|200000000
suffix:semicolon
id|bd-&gt;bi_busfreq
op_assign
l_int|100000000
suffix:semicolon
id|bd-&gt;bi_pci_busfreq
op_assign
l_int|33000000
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_RAINIER
multiline_comment|/* Rainier uses vxworks bootrom */
r_void
DECL|function|embed_config
id|embed_config
c_func
(paren
id|bd_t
op_star
op_star
id|bdp
)paren
(brace
id|u_char
op_star
id|cp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|bd_t
op_star
id|bd
suffix:semicolon
id|bd
op_assign
op_amp
id|bdinfo
suffix:semicolon
op_star
id|bdp
op_assign
id|bd
suffix:semicolon
id|bd-&gt;bi_memsize
op_assign
(paren
l_int|32
op_star
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
id|bd-&gt;bi_intfreq
op_assign
l_int|133000000
suffix:semicolon
singleline_comment|//the internal clock is 133 MHz
id|bd-&gt;bi_busfreq
op_assign
l_int|100000000
suffix:semicolon
id|bd-&gt;bi_pci_busfreq
op_assign
l_int|33000000
suffix:semicolon
id|cp
op_assign
(paren
id|u_char
op_star
)paren
id|def_enet_addr
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bd-&gt;bi_enetaddr
(braket
id|i
)braket
op_assign
op_star
id|cp
op_increment
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
