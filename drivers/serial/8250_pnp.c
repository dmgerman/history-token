multiline_comment|/*&n; *  linux/drivers/char/8250_pnp.c&n; *&n; *  Probe module for 8250/16550-type ISAPNP serial ports.&n; *&n; *  Based on drivers/char/serial.c, by Linus Torvalds, Theodore Ts&squot;o.&n; *&n; *  Copyright (C) 2001 Russell King, All Rights Reserved.&n; *&n; *  Ported to the Linux PnP Layer - (C) Adam Belay.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License.&n; *&n; *  $Id: 8250_pnp.c,v 1.10 2002/07/21 21:32:30 rmk Exp $&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/pnp.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &quot;8250.h&quot;
DECL|macro|UNKNOWN_DEV
mdefine_line|#define UNKNOWN_DEV 0x3000
DECL|variable|pnp_dev_table
r_static
r_const
r_struct
id|pnp_device_id
id|pnp_dev_table
(braket
)braket
op_assign
(brace
multiline_comment|/* Archtek America Corp. */
multiline_comment|/* Archtek SmartLink Modem 3334BT Plug &amp; Play */
(brace
l_string|&quot;AAC000F&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Anchor Datacomm BV */
multiline_comment|/* SXPro 144 External Data Fax Modem Plug &amp; Play */
(brace
l_string|&quot;ADC0001&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* SXPro 288 External Data Fax Modem Plug &amp; Play */
(brace
l_string|&quot;ADC0002&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* PROLiNK 1456VH ISA PnP K56flex Fax Modem */
(brace
l_string|&quot;AEI0250&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Actiontec ISA PNP 56K X2 Fax Modem */
(brace
l_string|&quot;AEI1240&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Rockwell 56K ACF II Fax+Data+Voice Modem */
(brace
l_string|&quot;AKY1021&quot;
comma
l_int|0
multiline_comment|/*SPCI_FL_NO_SHIRQ*/
)brace
comma
multiline_comment|/* AZT3005 PnP SOUND DEVICE */
(brace
l_string|&quot;AZT4001&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Best Data Products Inc. Smart One 336F PnP Modem */
(brace
l_string|&quot;BDP3336&quot;
comma
l_int|0
)brace
comma
multiline_comment|/*  Boca Research */
multiline_comment|/* Boca Complete Ofc Communicator 14.4 Data-FAX */
(brace
l_string|&quot;BRI0A49&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Boca Research 33,600 ACF Modem */
(brace
l_string|&quot;BRI1400&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Boca 33.6 Kbps Internal FD34FSVD */
(brace
l_string|&quot;BRI3400&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Boca 33.6 Kbps Internal FD34FSVD */
(brace
l_string|&quot;BRI0A49&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Best Data Products Inc. Smart One 336F PnP Modem */
(brace
l_string|&quot;BDP3336&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Computer Peripherals Inc */
multiline_comment|/* EuroViVa CommCenter-33.6 SP PnP */
(brace
l_string|&quot;CPI4050&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Creative Labs */
multiline_comment|/* Creative Labs Phone Blaster 28.8 DSVD PnP Voice */
(brace
l_string|&quot;CTL3001&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Creative Labs Modem Blaster 28.8 DSVD PnP Voice */
(brace
l_string|&quot;CTL3011&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Creative */
multiline_comment|/* Creative Modem Blaster Flash56 DI5601-1 */
(brace
l_string|&quot;DMB1032&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Creative Modem Blaster V.90 DI5660 */
(brace
l_string|&quot;DMB2001&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* E-Tech */
multiline_comment|/* E-Tech CyberBULLET PC56RVP */
(brace
l_string|&quot;ETT0002&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* FUJITSU */
multiline_comment|/* Fujitsu 33600 PnP-I2 R Plug &amp; Play */
(brace
l_string|&quot;FUJ0202&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Fujitsu FMV-FX431 Plug &amp; Play */
(brace
l_string|&quot;FUJ0205&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Fujitsu 33600 PnP-I4 R Plug &amp; Play */
(brace
l_string|&quot;FUJ0206&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Fujitsu Fax Voice 33600 PNP-I5 R Plug &amp; Play */
(brace
l_string|&quot;FUJ0209&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Archtek America Corp. */
multiline_comment|/* Archtek SmartLink Modem 3334BT Plug &amp; Play */
(brace
l_string|&quot;GVC000F&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Hayes */
multiline_comment|/* Hayes Optima 288 V.34-V.FC + FAX + Voice Plug &amp; Play */
(brace
l_string|&quot;HAY0001&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Hayes Optima 336 V.34 + FAX + Voice PnP */
(brace
l_string|&quot;HAY000C&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Hayes Optima 336B V.34 + FAX + Voice PnP */
(brace
l_string|&quot;HAY000D&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Hayes Accura 56K Ext Fax Modem PnP */
(brace
l_string|&quot;HAY5670&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Hayes Accura 56K Ext Fax Modem PnP */
(brace
l_string|&quot;HAY5674&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Hayes Accura 56K Fax Modem PnP */
(brace
l_string|&quot;HAY5675&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Hayes 288, V.34 + FAX */
(brace
l_string|&quot;HAYF000&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Hayes Optima 288 V.34 + FAX + Voice, Plug &amp; Play */
(brace
l_string|&quot;HAYF001&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* IBM */
multiline_comment|/* IBM Thinkpad 701 Internal Modem Voice */
(brace
l_string|&quot;IBM0033&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Intertex */
multiline_comment|/* Intertex 28k8 33k6 Voice EXT PnP */
(brace
l_string|&quot;IXDC801&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Intertex 33k6 56k Voice EXT PnP */
(brace
l_string|&quot;IXDC901&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Intertex 28k8 33k6 Voice SP EXT PnP */
(brace
l_string|&quot;IXDD801&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Intertex 33k6 56k Voice SP EXT PnP */
(brace
l_string|&quot;IXDD901&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Intertex 28k8 33k6 Voice SP INT PnP */
(brace
l_string|&quot;IXDF401&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Intertex 28k8 33k6 Voice SP EXT PnP */
(brace
l_string|&quot;IXDF801&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Intertex 33k6 56k Voice SP EXT PnP */
(brace
l_string|&quot;IXDF901&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Kortex International */
multiline_comment|/* KORTEX 28800 Externe PnP */
(brace
l_string|&quot;KOR4522&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* KXPro 33.6 Vocal ASVD PnP */
(brace
l_string|&quot;KORF661&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Lasat */
multiline_comment|/* LASAT Internet 33600 PnP */
(brace
l_string|&quot;LAS4040&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Lasat Safire 560 PnP */
(brace
l_string|&quot;LAS4540&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Lasat Safire 336  PnP */
(brace
l_string|&quot;LAS5440&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Microcom, Inc. */
multiline_comment|/* Microcom TravelPorte FAST V.34 Plug &amp; Play */
(brace
l_string|&quot;MNP0281&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Microcom DeskPorte V.34 FAST or FAST+ Plug &amp; Play */
(brace
l_string|&quot;MNP0336&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Microcom DeskPorte FAST EP 28.8 Plug &amp; Play */
(brace
l_string|&quot;MNP0339&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Microcom DeskPorte 28.8P Plug &amp; Play */
(brace
l_string|&quot;MNP0342&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Microcom DeskPorte FAST ES 28.8 Plug &amp; Play */
(brace
l_string|&quot;MNP0500&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Microcom DeskPorte FAST ES 28.8 Plug &amp; Play */
(brace
l_string|&quot;MNP0501&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Microcom DeskPorte 28.8S Internal Plug &amp; Play */
(brace
l_string|&quot;MNP0502&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Motorola */
multiline_comment|/* Motorola BitSURFR Plug &amp; Play */
(brace
l_string|&quot;MOT1105&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Motorola TA210 Plug &amp; Play */
(brace
l_string|&quot;MOT1111&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Motorola HMTA 200 (ISDN) Plug &amp; Play */
(brace
l_string|&quot;MOT1114&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Motorola BitSURFR Plug &amp; Play */
(brace
l_string|&quot;MOT1115&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Motorola Lifestyle 28.8 Internal */
(brace
l_string|&quot;MOT1190&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Motorola V.3400 Plug &amp; Play */
(brace
l_string|&quot;MOT1501&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Motorola Lifestyle 28.8 V.34 Plug &amp; Play */
(brace
l_string|&quot;MOT1502&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Motorola Power 28.8 V.34 Plug &amp; Play */
(brace
l_string|&quot;MOT1505&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Motorola ModemSURFR External 28.8 Plug &amp; Play */
(brace
l_string|&quot;MOT1509&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Motorola Premier 33.6 Desktop Plug &amp; Play */
(brace
l_string|&quot;MOT150A&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Motorola VoiceSURFR 56K External PnP */
(brace
l_string|&quot;MOT150F&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Motorola ModemSURFR 56K External PnP */
(brace
l_string|&quot;MOT1510&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Motorola ModemSURFR 56K Internal PnP */
(brace
l_string|&quot;MOT1550&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Motorola ModemSURFR Internal 28.8 Plug &amp; Play */
(brace
l_string|&quot;MOT1560&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Motorola Premier 33.6 Internal Plug &amp; Play */
(brace
l_string|&quot;MOT1580&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Motorola OnlineSURFR 28.8 Internal Plug &amp; Play */
(brace
l_string|&quot;MOT15B0&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Motorola VoiceSURFR 56K Internal PnP */
(brace
l_string|&quot;MOT15F0&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Com 1 */
multiline_comment|/*  Deskline K56 Phone System PnP */
(brace
l_string|&quot;MVX00A1&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* PC Rider K56 Phone System PnP */
(brace
l_string|&quot;MVX00F2&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* NEC 98NOTE SPEAKER PHONE FAX MODEM(33600bps) */
(brace
l_string|&quot;nEC8241&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Pace 56 Voice Internal Plug &amp; Play Modem */
(brace
l_string|&quot;PMC2430&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Generic */
multiline_comment|/* Generic standard PC COM port&t; */
(brace
l_string|&quot;PNP0500&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Generic 16550A-compatible COM port */
(brace
l_string|&quot;PNP0501&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Compaq 14400 Modem */
(brace
l_string|&quot;PNPC000&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Compaq 2400/9600 Modem */
(brace
l_string|&quot;PNPC001&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Dial-Up Networking Serial Cable between 2 PCs */
(brace
l_string|&quot;PNPC031&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Dial-Up Networking Parallel Cable between 2 PCs */
(brace
l_string|&quot;PNPC032&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Standard 9600 bps Modem */
(brace
l_string|&quot;PNPC100&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Standard 14400 bps Modem */
(brace
l_string|&quot;PNPC101&quot;
comma
l_int|0
)brace
comma
multiline_comment|/*  Standard 28800 bps Modem*/
(brace
l_string|&quot;PNPC102&quot;
comma
l_int|0
)brace
comma
multiline_comment|/*  Standard Modem*/
(brace
l_string|&quot;PNPC103&quot;
comma
l_int|0
)brace
comma
multiline_comment|/*  Standard 9600 bps Modem*/
(brace
l_string|&quot;PNPC104&quot;
comma
l_int|0
)brace
comma
multiline_comment|/*  Standard 14400 bps Modem*/
(brace
l_string|&quot;PNPC105&quot;
comma
l_int|0
)brace
comma
multiline_comment|/*  Standard 28800 bps Modem*/
(brace
l_string|&quot;PNPC106&quot;
comma
l_int|0
)brace
comma
multiline_comment|/*  Standard Modem */
(brace
l_string|&quot;PNPC107&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Standard 9600 bps Modem */
(brace
l_string|&quot;PNPC108&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Standard 14400 bps Modem */
(brace
l_string|&quot;PNPC109&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Standard 28800 bps Modem */
(brace
l_string|&quot;PNPC10A&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Standard Modem */
(brace
l_string|&quot;PNPC10B&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Standard 9600 bps Modem */
(brace
l_string|&quot;PNPC10C&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Standard 14400 bps Modem */
(brace
l_string|&quot;PNPC10D&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Standard 28800 bps Modem */
(brace
l_string|&quot;PNPC10E&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Standard Modem */
(brace
l_string|&quot;PNPC10F&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Standard PCMCIA Card Modem */
(brace
l_string|&quot;PNP2000&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Rockwell */
multiline_comment|/* Modular Technology */
multiline_comment|/* Rockwell 33.6 DPF Internal PnP */
multiline_comment|/* Modular Technology 33.6 Internal PnP */
(brace
l_string|&quot;ROK0030&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Kortex International */
multiline_comment|/* KORTEX 14400 Externe PnP */
(brace
l_string|&quot;ROK0100&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Rockwell 28.8 */
(brace
l_string|&quot;ROK4120&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Viking Components, Inc */
multiline_comment|/* Viking 28.8 INTERNAL Fax+Data+Voice PnP */
(brace
l_string|&quot;ROK4920&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Rockwell */
multiline_comment|/* British Telecom */
multiline_comment|/* Modular Technology */
multiline_comment|/* Rockwell 33.6 DPF External PnP */
multiline_comment|/* BT Prologue 33.6 External PnP */
multiline_comment|/* Modular Technology 33.6 External PnP */
(brace
l_string|&quot;RSS00A0&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Viking 56K FAX INT */
(brace
l_string|&quot;RSS0262&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* K56 par,VV,Voice,Speakphone,AudioSpan,PnP */
(brace
l_string|&quot;RSS0250&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* SupraExpress 28.8 Data/Fax PnP modem */
(brace
l_string|&quot;SUP1310&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* SupraExpress 33.6 Data/Fax PnP modem */
(brace
l_string|&quot;SUP1421&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* SupraExpress 33.6 Data/Fax PnP modem */
(brace
l_string|&quot;SUP1590&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* SupraExpress 33.6 Data/Fax PnP modem */
(brace
l_string|&quot;SUP1760&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Phoebe Micro */
multiline_comment|/* Phoebe Micro 33.6 Data Fax 1433VQH Plug &amp; Play */
(brace
l_string|&quot;TEX0011&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Archtek America Corp. */
multiline_comment|/* Archtek SmartLink Modem 3334BT Plug &amp; Play */
(brace
l_string|&quot;UAC000F&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* 3Com Corp. */
multiline_comment|/* Gateway Telepath IIvi 33.6 */
(brace
l_string|&quot;USR0000&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* U.S. Robotics Sporster 33.6K Fax INT PnP */
(brace
l_string|&quot;USR0002&quot;
comma
l_int|0
)brace
comma
multiline_comment|/*  Sportster Vi 14.4 PnP FAX Voicemail */
(brace
l_string|&quot;USR0004&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* U.S. Robotics 33.6K Voice INT PnP */
(brace
l_string|&quot;USR0006&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* U.S. Robotics 33.6K Voice EXT PnP */
(brace
l_string|&quot;USR0007&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* U.S. Robotics Courier V.Everything INT PnP */
(brace
l_string|&quot;USR0009&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* U.S. Robotics 33.6K Voice INT PnP */
(brace
l_string|&quot;USR2002&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* U.S. Robotics 56K Voice INT PnP */
(brace
l_string|&quot;USR2070&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* U.S. Robotics 56K Voice EXT PnP */
(brace
l_string|&quot;USR2080&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* U.S. Robotics 56K FAX INT */
(brace
l_string|&quot;USR3031&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* U.S. Robotics 56K FAX INT */
(brace
l_string|&quot;USR3050&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* U.S. Robotics 56K Voice INT PnP */
(brace
l_string|&quot;USR3070&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* U.S. Robotics 56K Voice EXT PnP */
(brace
l_string|&quot;USR3080&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* U.S. Robotics 56K Voice INT PnP */
(brace
l_string|&quot;USR3090&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* U.S. Robotics 56K Message  */
(brace
l_string|&quot;USR9100&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* U.S. Robotics 56K FAX EXT PnP*/
(brace
l_string|&quot;USR9160&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* U.S. Robotics 56K FAX INT PnP*/
(brace
l_string|&quot;USR9170&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* U.S. Robotics 56K Voice EXT PnP*/
(brace
l_string|&quot;USR9180&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* U.S. Robotics 56K Voice INT PnP*/
(brace
l_string|&quot;USR9190&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Rockwell&squot;s (PORALiNK) 33600 INT PNP */
(brace
l_string|&quot;WCI0003&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Unkown PnP modems */
(brace
l_string|&quot;PNPCXXX&quot;
comma
id|UNKNOWN_DEV
)brace
comma
multiline_comment|/* More unkown PnP modems */
(brace
l_string|&quot;PNPDXXX&quot;
comma
id|UNKNOWN_DEV
)brace
comma
(brace
l_string|&quot;&quot;
comma
l_int|0
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pnp
comma
id|pnp_dev_table
)paren
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_char
op_star
id|modem_names
(braket
)braket
id|__devinitdata
op_assign
(brace
l_string|&quot;MODEM&quot;
comma
l_string|&quot;Modem&quot;
comma
l_string|&quot;modem&quot;
comma
l_string|&quot;FAX&quot;
comma
l_string|&quot;Fax&quot;
comma
l_string|&quot;fax&quot;
comma
l_string|&quot;56K&quot;
comma
l_string|&quot;56k&quot;
comma
l_string|&quot;K56&quot;
comma
l_string|&quot;33.6&quot;
comma
l_string|&quot;28.8&quot;
comma
l_string|&quot;14.4&quot;
comma
l_string|&quot;33,600&quot;
comma
l_string|&quot;28,800&quot;
comma
l_string|&quot;14,400&quot;
comma
l_string|&quot;33.600&quot;
comma
l_string|&quot;28.800&quot;
comma
l_string|&quot;14.400&quot;
comma
l_string|&quot;33600&quot;
comma
l_string|&quot;28800&quot;
comma
l_string|&quot;14400&quot;
comma
l_string|&quot;V.90&quot;
comma
l_string|&quot;V.34&quot;
comma
l_string|&quot;V.32&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|check_name
r_static
r_int
id|__devinit
id|check_name
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_char
op_star
op_star
id|tmp
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|modem_names
suffix:semicolon
op_star
id|tmp
suffix:semicolon
id|tmp
op_increment
)paren
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|name
comma
op_star
id|tmp
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|check_resources
r_static
r_int
id|__devinit
id|check_resources
c_func
(paren
r_struct
id|pnp_option
op_star
id|option
)paren
(brace
r_struct
id|pnp_option
op_star
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|option
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|option
suffix:semicolon
id|tmp
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
)paren
(brace
r_struct
id|pnp_port
op_star
id|port
suffix:semicolon
r_for
c_loop
(paren
id|port
op_assign
id|tmp-&gt;port
suffix:semicolon
id|port
suffix:semicolon
id|port
op_assign
id|port-&gt;next
)paren
r_if
c_cond
(paren
(paren
id|port-&gt;size
op_eq
l_int|8
)paren
op_logical_and
(paren
(paren
id|port-&gt;min
op_eq
l_int|0x2f8
)paren
op_logical_or
(paren
id|port-&gt;min
op_eq
l_int|0x3f8
)paren
op_logical_or
(paren
id|port-&gt;min
op_eq
l_int|0x2e8
)paren
op_logical_or
(paren
id|port-&gt;min
op_eq
l_int|0x3e8
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Given a complete unknown PnP device, try to use some heuristics to&n; * detect modems. Currently use such heuristic set:&n; *     - dev-&gt;name or dev-&gt;bus-&gt;name must contain &quot;modem&quot; substring;&n; *     - device must have only one IO region (8 byte long) with base address&n; *       0x2e8, 0x3e8, 0x2f8 or 0x3f8.&n; *&n; * Such detection looks very ugly, but can detect at least some of numerous&n; * PnP modems, alternatively we must hardcode all modems in pnp_devices[]&n; * table.&n; */
DECL|function|serial_pnp_guess_board
r_static
r_int
id|__devinit
id|serial_pnp_guess_board
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_int
op_star
id|flags
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|check_name
c_func
(paren
id|pnp_dev_name
c_func
(paren
id|dev
)paren
)paren
op_logical_or
(paren
id|dev-&gt;card
op_logical_and
id|check_name
c_func
(paren
id|dev-&gt;card-&gt;name
)paren
)paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|check_resources
c_func
(paren
id|dev-&gt;independent
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|check_resources
c_func
(paren
id|dev-&gt;dependent
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_static
r_int
id|__devinit
DECL|function|serial_pnp_probe
id|serial_pnp_probe
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_const
r_struct
id|pnp_device_id
op_star
id|dev_id
)paren
(brace
r_struct
id|uart_port
id|port
suffix:semicolon
r_int
id|ret
comma
id|line
comma
id|flags
op_assign
id|dev_id-&gt;driver_data
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|UNKNOWN_DEV
)paren
(brace
id|ret
op_assign
id|serial_pnp_guess_board
c_func
(paren
id|dev
comma
op_amp
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|port
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|uart_port
)paren
)paren
suffix:semicolon
id|port.irq
op_assign
id|pnp_irq
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|port.iobase
op_assign
id|pnp_port_start
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef SERIAL_DEBUG_PNP
id|printk
c_func
(paren
l_string|&quot;Setup PNP port: port %x, irq %d, type %d&bslash;n&quot;
comma
id|port.iobase
comma
id|port.irq
comma
id|port.iotype
)paren
suffix:semicolon
macro_line|#endif
id|port.flags
op_assign
id|UPF_SKIP_TEST
op_or
id|UPF_BOOT_AUTOCONF
suffix:semicolon
id|port.uartclk
op_assign
l_int|1843200
suffix:semicolon
id|port.dev
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|line
op_assign
id|serial8250_register_port
c_func
(paren
op_amp
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line
op_ge
l_int|0
)paren
id|pnp_set_drvdata
c_func
(paren
id|dev
comma
(paren
r_void
op_star
)paren
(paren
id|line
op_plus
l_int|1
)paren
)paren
suffix:semicolon
r_return
id|line
op_ge
l_int|0
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|serial_pnp_remove
r_static
r_void
id|__devexit
id|serial_pnp_remove
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_int
id|line
op_assign
(paren
r_int
)paren
id|pnp_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line
)paren
id|serial8250_unregister_port
c_func
(paren
id|line
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|variable|serial_pnp_driver
r_static
r_struct
id|pnp_driver
id|serial_pnp_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;serial&quot;
comma
dot
id|id_table
op_assign
id|pnp_dev_table
comma
dot
id|probe
op_assign
id|serial_pnp_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|serial_pnp_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|serial8250_pnp_init
r_static
r_int
id|__init
id|serial8250_pnp_init
c_func
(paren
r_void
)paren
(brace
r_return
id|pnp_register_driver
c_func
(paren
op_amp
id|serial_pnp_driver
)paren
suffix:semicolon
)brace
DECL|function|serial8250_pnp_exit
r_static
r_void
id|__exit
id|serial8250_pnp_exit
c_func
(paren
r_void
)paren
(brace
id|pnp_unregister_driver
c_func
(paren
op_amp
id|serial_pnp_driver
)paren
suffix:semicolon
)brace
DECL|variable|serial8250_pnp_init
id|module_init
c_func
(paren
id|serial8250_pnp_init
)paren
suffix:semicolon
DECL|variable|serial8250_pnp_exit
id|module_exit
c_func
(paren
id|serial8250_pnp_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Generic 8250/16x50 PnP serial driver&quot;
)paren
suffix:semicolon
eof
