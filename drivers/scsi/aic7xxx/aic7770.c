multiline_comment|/*&n; * Product specific probe and attach routines for:&n; * &t;27/284X and aic7770 motherboard SCSI controllers&n; *&n; * Copyright (c) 1994-1998, 2000, 2001 Justin T. Gibbs.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice immediately at the beginning of the file, without modification,&n; *    this list of conditions, and the following disclaimer.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU Public License (&quot;GPL&quot;).&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; * $Id: //depot/src/aic7xxx/aic7770.c#12 $&n; *&n; * $FreeBSD: src/sys/dev/aic7xxx/aic7770.c,v 1.1 2000/09/16 20:02:27 gibbs Exp $&n; */
macro_line|#include &quot;aic7xxx_osm.h&quot;
macro_line|#include &quot;aic7xxx_inline.h&quot;
macro_line|#include &quot;aic7xxx_93cx6.h&quot;
DECL|macro|ID_AIC7770
mdefine_line|#define ID_AIC7770&t;0x04907770
DECL|macro|ID_AHA_274x
mdefine_line|#define ID_AHA_274x&t;0x04907771
DECL|macro|ID_AHA_284xB
mdefine_line|#define ID_AHA_284xB&t;0x04907756 /* BIOS enabled */
DECL|macro|ID_AHA_284x
mdefine_line|#define ID_AHA_284x&t;0x04907757 /* BIOS disabled*/
r_static
r_void
id|aha2840_load_seeprom
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
DECL|variable|ahc_aic7770_VL_setup
r_static
id|ahc_device_setup_t
id|ahc_aic7770_VL_setup
suffix:semicolon
DECL|variable|ahc_aic7770_EISA_setup
r_static
id|ahc_device_setup_t
id|ahc_aic7770_EISA_setup
suffix:semicolon
suffix:semicolon
DECL|variable|ahc_aic7770_setup
r_static
id|ahc_device_setup_t
id|ahc_aic7770_setup
suffix:semicolon
DECL|variable|aic7770_ident_table
r_struct
id|aic7770_identity
id|aic7770_ident_table
(braket
)braket
op_assign
(brace
(brace
id|ID_AHA_274x
comma
l_int|0xFFFFFFFF
comma
l_string|&quot;Adaptec 274X SCSI adapter&quot;
comma
id|ahc_aic7770_EISA_setup
)brace
comma
(brace
id|ID_AHA_284xB
comma
l_int|0xFFFFFFFE
comma
l_string|&quot;Adaptec 284X SCSI adapter&quot;
comma
id|ahc_aic7770_VL_setup
)brace
comma
multiline_comment|/* Generic chip probes for devices we don&squot;t know &squot;exactly&squot; */
(brace
id|ID_AIC7770
comma
l_int|0xFFFFFFFF
comma
l_string|&quot;Adaptec aic7770 SCSI adapter&quot;
comma
id|ahc_aic7770_EISA_setup
)brace
)brace
suffix:semicolon
DECL|variable|ahc_num_aic7770_devs
r_const
r_int
id|ahc_num_aic7770_devs
op_assign
id|NUM_ELEMENTS
c_func
(paren
id|aic7770_ident_table
)paren
suffix:semicolon
r_struct
id|aic7770_identity
op_star
DECL|function|aic7770_find_device
id|aic7770_find_device
c_func
(paren
r_uint32
id|id
)paren
(brace
r_struct
id|aic7770_identity
op_star
id|entry
suffix:semicolon
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
id|ahc_num_aic7770_devs
suffix:semicolon
id|i
op_increment
)paren
(brace
id|entry
op_assign
op_amp
id|aic7770_ident_table
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;full_id
op_eq
(paren
id|id
op_amp
id|entry-&gt;id_mask
)paren
)paren
r_return
(paren
id|entry
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_int
DECL|function|aic7770_config
id|aic7770_config
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|aic7770_identity
op_star
id|entry
)paren
(brace
r_int
id|error
suffix:semicolon
id|u_int
id|hostconf
suffix:semicolon
id|u_int
id|irq
suffix:semicolon
id|u_int
id|intdef
suffix:semicolon
id|error
op_assign
id|entry
op_member_access_from_pointer
id|setup
c_func
(paren
id|ahc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
l_int|0
)paren
r_return
(paren
id|error
)paren
suffix:semicolon
id|error
op_assign
id|aic7770_map_registers
c_func
(paren
id|ahc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
l_int|0
)paren
r_return
(paren
id|error
)paren
suffix:semicolon
id|ahc-&gt;description
op_assign
id|entry-&gt;name
suffix:semicolon
id|error
op_assign
id|ahc_softc_init
c_func
(paren
id|ahc
)paren
suffix:semicolon
id|error
op_assign
id|ahc_reset
c_func
(paren
id|ahc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
l_int|0
)paren
r_return
(paren
id|error
)paren
suffix:semicolon
multiline_comment|/* Make sure we have a valid interrupt vector */
id|intdef
op_assign
id|ahc_inb
c_func
(paren
id|ahc
comma
id|INTDEF
)paren
suffix:semicolon
id|irq
op_assign
id|intdef
op_amp
id|VECTOR
suffix:semicolon
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
l_int|9
suffix:colon
r_case
l_int|10
suffix:colon
r_case
l_int|11
suffix:colon
r_case
l_int|12
suffix:colon
r_case
l_int|14
suffix:colon
r_case
l_int|15
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|printf
c_func
(paren
l_string|&quot;aic7770_config: illegal irq setting %d&bslash;n&quot;
comma
id|intdef
)paren
suffix:semicolon
r_return
(paren
id|ENXIO
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|intdef
op_amp
id|EDGE_TRIG
)paren
op_ne
l_int|0
)paren
id|ahc-&gt;flags
op_or_assign
id|AHC_EDGE_INTERRUPT
suffix:semicolon
r_switch
c_cond
(paren
id|ahc-&gt;chip
op_amp
(paren
id|AHC_EISA
op_or
id|AHC_VL
)paren
)paren
(brace
r_case
id|AHC_EISA
suffix:colon
(brace
id|u_int
id|biosctrl
suffix:semicolon
id|u_int
id|scsiconf
suffix:semicolon
id|u_int
id|scsiconf1
suffix:semicolon
id|biosctrl
op_assign
id|ahc_inb
c_func
(paren
id|ahc
comma
id|HA_274_BIOSCTRL
)paren
suffix:semicolon
id|scsiconf
op_assign
id|ahc_inb
c_func
(paren
id|ahc
comma
id|SCSICONF
)paren
suffix:semicolon
id|scsiconf1
op_assign
id|ahc_inb
c_func
(paren
id|ahc
comma
id|SCSICONF
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Get the primary channel information */
r_if
c_cond
(paren
(paren
id|biosctrl
op_amp
id|CHANNEL_B_PRIMARY
)paren
op_ne
l_int|0
)paren
id|ahc-&gt;flags
op_or_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|biosctrl
op_amp
id|BIOSMODE
)paren
op_eq
id|BIOSDISABLED
)paren
(brace
id|ahc-&gt;flags
op_or_assign
id|AHC_USEDEFAULTS
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|ahc-&gt;features
op_amp
id|AHC_WIDE
)paren
op_ne
l_int|0
)paren
(brace
id|ahc-&gt;our_id
op_assign
id|scsiconf1
op_amp
id|HWSCSIID
suffix:semicolon
r_if
c_cond
(paren
id|scsiconf
op_amp
id|TERM_ENB
)paren
id|ahc-&gt;flags
op_or_assign
id|AHC_TERM_ENB_A
suffix:semicolon
)brace
r_else
(brace
id|ahc-&gt;our_id
op_assign
id|scsiconf
op_amp
id|HSCSIID
suffix:semicolon
id|ahc-&gt;our_id_b
op_assign
id|scsiconf1
op_amp
id|HSCSIID
suffix:semicolon
r_if
c_cond
(paren
id|scsiconf
op_amp
id|TERM_ENB
)paren
id|ahc-&gt;flags
op_or_assign
id|AHC_TERM_ENB_A
suffix:semicolon
r_if
c_cond
(paren
id|scsiconf1
op_amp
id|TERM_ENB
)paren
id|ahc-&gt;flags
op_or_assign
id|AHC_TERM_ENB_B
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * We have no way to tell, so assume extended&n;&t;&t; * translation is enabled.&n;&t;&t; */
id|ahc-&gt;flags
op_or_assign
id|AHC_EXTENDED_TRANS_A
op_or
id|AHC_EXTENDED_TRANS_B
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|AHC_VL
suffix:colon
(brace
id|aha2840_load_seeprom
c_func
(paren
id|ahc
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Ensure autoflush is enabled&n;&t; */
id|ahc_outb
c_func
(paren
id|ahc
comma
id|SBLKCTL
comma
id|ahc_inb
c_func
(paren
id|ahc
comma
id|SBLKCTL
)paren
op_amp
op_complement
id|AUTOFLUSHDIS
)paren
suffix:semicolon
multiline_comment|/* Setup the FIFO threshold and the bus off time */
id|hostconf
op_assign
id|ahc_inb
c_func
(paren
id|ahc
comma
id|HOSTCONF
)paren
suffix:semicolon
id|ahc_outb
c_func
(paren
id|ahc
comma
id|BUSSPD
comma
id|hostconf
op_amp
id|DFTHRSH
)paren
suffix:semicolon
id|ahc_outb
c_func
(paren
id|ahc
comma
id|BUSTIME
comma
(paren
id|hostconf
op_lshift
l_int|2
)paren
op_amp
id|BOFF
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Generic aic7xxx initialization.&n;&t; */
id|error
op_assign
id|ahc_init
c_func
(paren
id|ahc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
l_int|0
)paren
r_return
(paren
id|error
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Link this softc in with all other ahc instances.&n;&t; */
id|ahc_softc_insert
c_func
(paren
id|ahc
)paren
suffix:semicolon
id|error
op_assign
id|aic7770_map_int
c_func
(paren
id|ahc
comma
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
l_int|0
)paren
r_return
(paren
id|error
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Enable the board&squot;s BUS drivers&n;&t; */
id|ahc_outb
c_func
(paren
id|ahc
comma
id|BCTL
comma
id|ENABLE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Allow interrupts.&n;&t; */
id|ahc_intr_enable
c_func
(paren
id|ahc
comma
id|TRUE
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read the 284x SEEPROM.&n; */
r_static
r_void
DECL|function|aha2840_load_seeprom
id|aha2840_load_seeprom
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
(brace
r_struct
id|seeprom_descriptor
id|sd
suffix:semicolon
r_struct
id|seeprom_config
id|sc
suffix:semicolon
r_uint16
id|checksum
op_assign
l_int|0
suffix:semicolon
r_uint8
id|scsi_conf
suffix:semicolon
r_int
id|have_seeprom
suffix:semicolon
id|sd.sd_ahc
op_assign
id|ahc
suffix:semicolon
id|sd.sd_control_offset
op_assign
id|SEECTL_2840
suffix:semicolon
id|sd.sd_status_offset
op_assign
id|STATUS_2840
suffix:semicolon
id|sd.sd_dataout_offset
op_assign
id|STATUS_2840
suffix:semicolon
id|sd.sd_chip
op_assign
id|C46
suffix:semicolon
id|sd.sd_MS
op_assign
l_int|0
suffix:semicolon
id|sd.sd_RDY
op_assign
id|EEPROM_TF
suffix:semicolon
id|sd.sd_CS
op_assign
id|CS_2840
suffix:semicolon
id|sd.sd_CK
op_assign
id|CK_2840
suffix:semicolon
id|sd.sd_DO
op_assign
id|DO_2840
suffix:semicolon
id|sd.sd_DI
op_assign
id|DI_2840
suffix:semicolon
r_if
c_cond
(paren
id|bootverbose
)paren
id|printf
c_func
(paren
l_string|&quot;%s: Reading SEEPROM...&quot;
comma
id|ahc_name
c_func
(paren
id|ahc
)paren
)paren
suffix:semicolon
id|have_seeprom
op_assign
id|read_seeprom
c_func
(paren
op_amp
id|sd
comma
(paren
r_uint16
op_star
)paren
op_amp
id|sc
comma
multiline_comment|/*start_addr*/
l_int|0
comma
r_sizeof
(paren
id|sc
)paren
op_div
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|have_seeprom
)paren
(brace
multiline_comment|/* Check checksum */
r_int
id|i
suffix:semicolon
r_int
id|maxaddr
op_assign
(paren
r_sizeof
(paren
id|sc
)paren
op_div
l_int|2
)paren
op_minus
l_int|1
suffix:semicolon
r_uint16
op_star
id|scarray
op_assign
(paren
r_uint16
op_star
)paren
op_amp
id|sc
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
id|maxaddr
suffix:semicolon
id|i
op_increment
)paren
id|checksum
op_assign
id|checksum
op_plus
id|scarray
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|checksum
op_ne
id|sc.checksum
)paren
(brace
r_if
c_cond
(paren
id|bootverbose
)paren
(brace
id|printf
(paren
l_string|&quot;checksum error&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|have_seeprom
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|bootverbose
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;done.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|have_seeprom
)paren
(brace
r_if
c_cond
(paren
id|bootverbose
)paren
id|printf
c_func
(paren
l_string|&quot;%s: No SEEPROM available&bslash;n&quot;
comma
id|ahc_name
c_func
(paren
id|ahc
)paren
)paren
suffix:semicolon
id|ahc-&gt;flags
op_or_assign
id|AHC_USEDEFAULTS
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Put the data we&squot;ve collected down into SRAM&n;&t;&t; * where ahc_init will find it.&n;&t;&t; */
r_int
id|i
suffix:semicolon
r_int
id|max_targ
op_assign
(paren
id|ahc-&gt;features
op_amp
id|AHC_WIDE
)paren
op_ne
l_int|0
ques
c_cond
l_int|16
suffix:colon
l_int|8
suffix:semicolon
r_uint16
id|discenable
suffix:semicolon
id|discenable
op_assign
l_int|0
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
id|max_targ
suffix:semicolon
id|i
op_increment
)paren
(brace
r_uint8
id|target_settings
suffix:semicolon
id|target_settings
op_assign
(paren
id|sc.device_flags
(braket
id|i
)braket
op_amp
id|CFXFER
)paren
op_lshift
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|sc.device_flags
(braket
id|i
)braket
op_amp
id|CFSYNCH
)paren
id|target_settings
op_or_assign
id|SOFS
suffix:semicolon
r_if
c_cond
(paren
id|sc.device_flags
(braket
id|i
)braket
op_amp
id|CFWIDEB
)paren
id|target_settings
op_or_assign
id|WIDEXFER
suffix:semicolon
r_if
c_cond
(paren
id|sc.device_flags
(braket
id|i
)braket
op_amp
id|CFDISC
)paren
id|discenable
op_or_assign
(paren
l_int|0x01
op_lshift
id|i
)paren
suffix:semicolon
id|ahc_outb
c_func
(paren
id|ahc
comma
id|TARG_SCSIRATE
op_plus
id|i
comma
id|target_settings
)paren
suffix:semicolon
)brace
id|ahc_outb
c_func
(paren
id|ahc
comma
id|DISC_DSB
comma
op_complement
(paren
id|discenable
op_amp
l_int|0xff
)paren
)paren
suffix:semicolon
id|ahc_outb
c_func
(paren
id|ahc
comma
id|DISC_DSB
op_plus
l_int|1
comma
op_complement
(paren
(paren
id|discenable
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
)paren
suffix:semicolon
id|ahc-&gt;our_id
op_assign
id|sc.brtime_id
op_amp
id|CFSCSIID
suffix:semicolon
id|scsi_conf
op_assign
(paren
id|ahc-&gt;our_id
op_amp
l_int|0x7
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sc.adapter_control
op_amp
id|CFSPARITY
)paren
id|scsi_conf
op_or_assign
id|ENSPCHK
suffix:semicolon
r_if
c_cond
(paren
id|sc.adapter_control
op_amp
id|CFRESETB
)paren
id|scsi_conf
op_or_assign
id|RESET_SCSI
suffix:semicolon
r_if
c_cond
(paren
id|sc.bios_control
op_amp
id|CF284XEXTEND
)paren
id|ahc-&gt;flags
op_or_assign
id|AHC_EXTENDED_TRANS_A
suffix:semicolon
multiline_comment|/* Set SCSICONF info */
id|ahc_outb
c_func
(paren
id|ahc
comma
id|SCSICONF
comma
id|scsi_conf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sc.adapter_control
op_amp
id|CF284XSTERM
)paren
id|ahc-&gt;flags
op_or_assign
id|AHC_TERM_ENB_A
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|ahc_aic7770_VL_setup
id|ahc_aic7770_VL_setup
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
(brace
r_int
id|error
suffix:semicolon
id|error
op_assign
id|ahc_aic7770_setup
c_func
(paren
id|ahc
)paren
suffix:semicolon
id|ahc-&gt;chip
op_or_assign
id|AHC_VL
suffix:semicolon
r_return
(paren
id|error
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|ahc_aic7770_EISA_setup
id|ahc_aic7770_EISA_setup
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
(brace
r_int
id|error
suffix:semicolon
id|error
op_assign
id|ahc_aic7770_setup
c_func
(paren
id|ahc
)paren
suffix:semicolon
id|ahc-&gt;chip
op_or_assign
id|AHC_EISA
suffix:semicolon
r_return
(paren
id|error
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|ahc_aic7770_setup
id|ahc_aic7770_setup
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
(brace
id|ahc-&gt;channel
op_assign
l_char|&squot;A&squot;
suffix:semicolon
id|ahc-&gt;channel_b
op_assign
l_char|&squot;B&squot;
suffix:semicolon
id|ahc-&gt;chip
op_assign
id|AHC_AIC7770
suffix:semicolon
id|ahc-&gt;features
op_assign
id|AHC_AIC7770_FE
suffix:semicolon
id|ahc-&gt;bugs
op_or_assign
id|AHC_TMODE_WIDEODD_BUG
suffix:semicolon
id|ahc-&gt;flags
op_or_assign
id|AHC_PAGESCBS
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
