multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;yam.h  -- YAM radio modem driver.&n; *&n; *&t;Copyright (C) 1998 Frederic Rible F1OAT (frible@teaser.fr)&n; *&t;Adapted from baycom.c driver written by Thomas Sailer (sailer@ife.ee.ethz.ch)&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License&n; *&t;along with this program; if not, write to the Free Software&n; *&t;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  Please note that the GPL allows you to use the driver, NOT the radio.&n; *  In order to use the radio, you need a license from the communications&n; *  authority of your country.&n; *&n; *&n; */
multiline_comment|/*****************************************************************************/
DECL|macro|SIOCYAMRESERVED
mdefine_line|#define SIOCYAMRESERVED&t;(0)
DECL|macro|SIOCYAMSCFG
mdefine_line|#define SIOCYAMSCFG &t;(1)&t;/* Set configuration */
DECL|macro|SIOCYAMGCFG
mdefine_line|#define SIOCYAMGCFG &t;(2)&t;/* Get configuration */
DECL|macro|SIOCYAMSMCS
mdefine_line|#define SIOCYAMSMCS &t;(3)&t;/* Set mcs data */
DECL|macro|YAM_IOBASE
mdefine_line|#define YAM_IOBASE   (1 &lt;&lt; 0)
DECL|macro|YAM_IRQ
mdefine_line|#define YAM_IRQ      (1 &lt;&lt; 1)
DECL|macro|YAM_BITRATE
mdefine_line|#define YAM_BITRATE  (1 &lt;&lt; 2) /* Bit rate of radio port -&gt;57600 */
DECL|macro|YAM_MODE
mdefine_line|#define YAM_MODE     (1 &lt;&lt; 3) /* 0=simplex 1=duplex 2=duplex+tempo */
DECL|macro|YAM_HOLDDLY
mdefine_line|#define YAM_HOLDDLY  (1 &lt;&lt; 4) /* duplex tempo (sec) */
DECL|macro|YAM_TXDELAY
mdefine_line|#define YAM_TXDELAY  (1 &lt;&lt; 5) /* Tx Delay (ms) */
DECL|macro|YAM_TXTAIL
mdefine_line|#define YAM_TXTAIL   (1 &lt;&lt; 6) /* Tx Tail  (ms) */
DECL|macro|YAM_PERSIST
mdefine_line|#define YAM_PERSIST  (1 &lt;&lt; 7) /* Persist  (ms) */
DECL|macro|YAM_SLOTTIME
mdefine_line|#define YAM_SLOTTIME (1 &lt;&lt; 8) /* Slottime (ms) */
DECL|macro|YAM_BAUDRATE
mdefine_line|#define YAM_BAUDRATE (1 &lt;&lt; 9) /* Baud rate of rs232 port -&gt;115200 */
DECL|macro|YAM_MAXBITRATE
mdefine_line|#define YAM_MAXBITRATE  57600
DECL|macro|YAM_MAXBAUDRATE
mdefine_line|#define YAM_MAXBAUDRATE 115200
DECL|macro|YAM_MAXMODE
mdefine_line|#define YAM_MAXMODE     2
DECL|macro|YAM_MAXHOLDDLY
mdefine_line|#define YAM_MAXHOLDDLY  99
DECL|macro|YAM_MAXTXDELAY
mdefine_line|#define YAM_MAXTXDELAY  999
DECL|macro|YAM_MAXTXTAIL
mdefine_line|#define YAM_MAXTXTAIL   999
DECL|macro|YAM_MAXPERSIST
mdefine_line|#define YAM_MAXPERSIST  255
DECL|macro|YAM_MAXSLOTTIME
mdefine_line|#define YAM_MAXSLOTTIME 999
DECL|macro|YAM_FPGA_SIZE
mdefine_line|#define YAM_FPGA_SIZE&t;5302
DECL|struct|yamcfg
r_struct
id|yamcfg
(brace
DECL|member|mask
r_int
r_int
id|mask
suffix:semicolon
multiline_comment|/* Mask of commands */
DECL|member|iobase
r_int
r_int
id|iobase
suffix:semicolon
multiline_comment|/* IO Base of COM port */
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* IRQ of COM port */
DECL|member|bitrate
r_int
r_int
id|bitrate
suffix:semicolon
multiline_comment|/* Bit rate of radio port */
DECL|member|baudrate
r_int
r_int
id|baudrate
suffix:semicolon
multiline_comment|/* Baud rate of the RS232 port */
DECL|member|txdelay
r_int
r_int
id|txdelay
suffix:semicolon
multiline_comment|/* TxDelay */
DECL|member|txtail
r_int
r_int
id|txtail
suffix:semicolon
multiline_comment|/* TxTail */
DECL|member|persist
r_int
r_int
id|persist
suffix:semicolon
multiline_comment|/* Persistence */
DECL|member|slottime
r_int
r_int
id|slottime
suffix:semicolon
multiline_comment|/* Slottime */
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
multiline_comment|/* mode 0 (simp), 1(Dupl), 2(Dupl+delay) */
DECL|member|holddly
r_int
r_int
id|holddly
suffix:semicolon
multiline_comment|/* PTT delay in FullDuplex 2 mode */
)brace
suffix:semicolon
DECL|struct|yamdrv_ioctl_cfg
r_struct
id|yamdrv_ioctl_cfg
(brace
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
DECL|member|cfg
r_struct
id|yamcfg
id|cfg
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|yamdrv_ioctl_mcs
r_struct
id|yamdrv_ioctl_mcs
(brace
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
DECL|member|bitrate
r_int
id|bitrate
suffix:semicolon
DECL|member|bits
r_int
r_char
id|bits
(braket
id|YAM_FPGA_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
eof
