multiline_comment|/*&n;** *************************************************************************&n;**&n;**&n;**     R C I F . H&n;**&n;**&n;**  RedCreek InterFace include file.&n;**&n;**  ---------------------------------------------------------------------&n;**  ---     Copyright (c) 1998-1999, RedCreek Communications Inc.     ---&n;**  ---                   All rights reserved.                        ---&n;**  ---------------------------------------------------------------------&n;**&n;** File Description:&n;**&n;** Header file private ioctl commands.&n;**&n;**&n;**  This program is free software; you can redistribute it and/or modify&n;**  it under the terms of the GNU General Public License as published by&n;**  the Free Software Foundation; either version 2 of the License, or&n;**  (at your option) any later version.&n;&n;**  This program is distributed in the hope that it will be useful,&n;**  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;**  GNU General Public License for more details.&n;&n;**  You should have received a copy of the GNU General Public License&n;**  along with this program; if not, write to the Free Software&n;**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;** *************************************************************************&n;*/
macro_line|#ifndef RCIF_H
DECL|macro|RCIF_H
mdefine_line|#define RCIF_H
multiline_comment|/* The following protocol revision # should be incremented every time&n;   a new protocol or new structures are used in this file. */
DECL|variable|USER_PROTOCOL_REV
r_int
id|USER_PROTOCOL_REV
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* used to track different protocol revisions */
multiline_comment|/* define a single TCB &amp; buffer */
r_typedef
r_struct
multiline_comment|/* a single buffer */
(brace
DECL|member|context
id|U32
id|context
suffix:semicolon
multiline_comment|/* context */
DECL|member|scount
id|U32
id|scount
suffix:semicolon
multiline_comment|/* segment count */
DECL|member|size
id|U32
id|size
suffix:semicolon
multiline_comment|/* segment size */
DECL|member|addr
id|U32
id|addr
suffix:semicolon
multiline_comment|/* segment physical address */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
DECL|typedef|singleB
DECL|typedef|psingleB
id|singleB
comma
op_star
id|psingleB
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* a single TCB */
(brace
multiline_comment|/*&n;     **  +-----------------------+&n;     **  |         1             |  one buffer in the TCB&n;     **  +-----------------------+&n;     **  |  &lt;user&squot;s Context&gt;     |  user&squot;s buffer reference&n;     **  +-----------------------+&n;     **  |         1             |  one segment buffer&n;     **  +-----------------------+                            _&n;     **  |    &lt;buffer size&gt;      |  size                       &bslash; &n;     **  +-----------------------+                              &bslash; segment descriptor&n;     **  |  &lt;physical address&gt;   |  physical address of buffer  /&n;     **  +-----------------------+                            _/&n;     */
DECL|member|bcount
id|U32
id|bcount
suffix:semicolon
multiline_comment|/* buffer count */
DECL|member|b
id|singleB
id|b
suffix:semicolon
multiline_comment|/* buffer */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
DECL|typedef|singleTCB
DECL|typedef|psingleTCB
id|singleTCB
comma
op_star
id|psingleTCB
suffix:semicolon
multiline_comment|/*&n;   When adding new entries, please add all 5 related changes, since &n;   it helps keep everything consistent:&n;      1) User structure entry&n;      2) User data entry&n;      3) Structure short-cut entry&n;      4) Data short-cut entry&n;      5) Command identifier entry&n;&n;   For Example (&quot;GETSPEED&quot;):&n;      1) struct  RCgetspeed_tag { U32 LinkSpeedCode; } RCgetspeed;&n;      2) struct  RCgetspeed_tag *getspeed;&n;      3) #define RCUS_GETSPEED  data.RCgetspeed;&n;      4) #define RCUD_GETSPEED  _RC_user_data.getspeed&n;      5) #define RCUC_GETSPEED  0x02&n;  &n;   Notes for the &quot;GETSPEED&quot; entry, above:&n;      1) RCgetspeed      - RC{name}&n;         RCgetspeed_tag  - RC{name}_tag&n;         LinkSpeedCode   - create any structure format desired (not too large,&n;                           since memory will be unioned with all other entries)&n;      2) RCgetspeed_tag  - RC{name}_tag chosen in #1&n;         getspeed        - arbitrary name (ptr to structure in #1)&n;      3) RCUS_GETSPEED   - RCUS_{NAME}   (&quot;NAME&quot; &amp; &quot;name&quot; do not have to the same)&n;         data.RCgetspeed - data.RC{name}  (&quot;RC{name}&quot; from #1)&n;      4) RCUD_GETSPEED   - _RC_user_data.getspeed  (&quot;getspeed&quot; from #2)&n;      5) RCUC_GETSPEED   - unique hex identifier entry.&n;*/
DECL|typedef|RCuser_struct
r_typedef
r_struct
id|RC_user_tag
id|RCuser_struct
suffix:semicolon
multiline_comment|/* 1) User structure entry */
DECL|struct|RC_user_tag
r_struct
id|RC_user_tag
(brace
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
r_union
(brace
multiline_comment|/* GETINFO structure */
DECL|struct|RCgetinfo_tag
r_struct
id|RCgetinfo_tag
(brace
DECL|member|mem_start
r_int
r_int
r_int
id|mem_start
suffix:semicolon
DECL|member|mem_end
r_int
r_int
r_int
id|mem_end
suffix:semicolon
DECL|member|base_addr
r_int
r_int
r_int
id|base_addr
suffix:semicolon
DECL|member|irq
r_int
r_char
id|irq
suffix:semicolon
DECL|member|dma
r_int
r_char
id|dma
suffix:semicolon
DECL|member|port
r_int
r_char
id|port
suffix:semicolon
DECL|member|RCgetinfo
)brace
id|RCgetinfo
suffix:semicolon
multiline_comment|/* &lt;---- RCgetinfo */
multiline_comment|/* GETSPEED structure */
DECL|struct|RCgetspeed_tag
r_struct
id|RCgetspeed_tag
(brace
DECL|member|LinkSpeedCode
id|U32
id|LinkSpeedCode
suffix:semicolon
DECL|member|RCgetspeed
)brace
id|RCgetspeed
suffix:semicolon
multiline_comment|/* &lt;---- RCgetspeed */
multiline_comment|/* SETSPEED structure */
DECL|struct|RCsetspeed_tag
r_struct
id|RCsetspeed_tag
(brace
DECL|member|LinkSpeedCode
id|U16
id|LinkSpeedCode
suffix:semicolon
DECL|member|RCsetspeed
)brace
id|RCsetspeed
suffix:semicolon
multiline_comment|/* &lt;---- RCsetspeed */
multiline_comment|/* GETPROM structure */
DECL|struct|RCgetprom_tag
r_struct
id|RCgetprom_tag
(brace
DECL|member|PromMode
id|U32
id|PromMode
suffix:semicolon
DECL|member|RCgetprom
)brace
id|RCgetprom
suffix:semicolon
multiline_comment|/* &lt;---- RCgetprom */
multiline_comment|/* SETPROM structure */
DECL|struct|RCsetprom_tag
r_struct
id|RCsetprom_tag
(brace
DECL|member|PromMode
id|U16
id|PromMode
suffix:semicolon
DECL|member|RCsetprom
)brace
id|RCsetprom
suffix:semicolon
multiline_comment|/* &lt;---- RCsetprom */
multiline_comment|/* GETBROADCAST structure */
DECL|struct|RCgetbroadcast_tag
r_struct
id|RCgetbroadcast_tag
(brace
DECL|member|BroadcastMode
id|U32
id|BroadcastMode
suffix:semicolon
DECL|member|RCgetbroadcast
)brace
id|RCgetbroadcast
suffix:semicolon
multiline_comment|/* &lt;---- RCgetbroadcast */
multiline_comment|/* SETBROADCAST structure */
DECL|struct|RCsetbroadcast_tag
r_struct
id|RCsetbroadcast_tag
(brace
DECL|member|BroadcastMode
id|U16
id|BroadcastMode
suffix:semicolon
DECL|member|RCsetbroadcast
)brace
id|RCsetbroadcast
suffix:semicolon
multiline_comment|/* &lt;---- RCsetbroadcast */
multiline_comment|/* GETFIRMWAREVER structure */
DECL|macro|FirmStringLen
mdefine_line|#define FirmStringLen 80
DECL|struct|RCgetfwver_tag
r_struct
id|RCgetfwver_tag
(brace
DECL|member|FirmString
id|U8
id|FirmString
(braket
id|FirmStringLen
)braket
suffix:semicolon
DECL|member|RCgetfwver
)brace
id|RCgetfwver
suffix:semicolon
multiline_comment|/* &lt;---- RCgetfwver */
multiline_comment|/* GETIPANDMASK structure */
DECL|struct|RCgetipnmask_tag
r_struct
id|RCgetipnmask_tag
(brace
DECL|member|IpAddr
id|U32
id|IpAddr
suffix:semicolon
DECL|member|NetMask
id|U32
id|NetMask
suffix:semicolon
DECL|member|RCgetipandmask
)brace
id|RCgetipandmask
suffix:semicolon
multiline_comment|/* &lt;---- RCgetipandmask */
multiline_comment|/* SETIPANDMASK structure */
DECL|struct|RCsetipnmask_tag
r_struct
id|RCsetipnmask_tag
(brace
DECL|member|IpAddr
id|U32
id|IpAddr
suffix:semicolon
DECL|member|NetMask
id|U32
id|NetMask
suffix:semicolon
DECL|member|RCsetipandmask
)brace
id|RCsetipandmask
suffix:semicolon
multiline_comment|/* &lt;---- RCsetipandmask */
multiline_comment|/* GETMAC structure */
DECL|macro|MAC_SIZE
mdefine_line|#define MAC_SIZE 10
DECL|struct|RCgetmac_tag
r_struct
id|RCgetmac_tag
(brace
DECL|member|mac
id|U8
id|mac
(braket
id|MAC_SIZE
)braket
suffix:semicolon
DECL|member|RCgetmac
)brace
id|RCgetmac
suffix:semicolon
multiline_comment|/* &lt;---- RCgetmac */
multiline_comment|/* SETMAC structure */
DECL|struct|RCsetmac_tag
r_struct
id|RCsetmac_tag
(brace
DECL|member|mac
id|U8
id|mac
(braket
id|MAC_SIZE
)braket
suffix:semicolon
DECL|member|RCsetmac
)brace
id|RCsetmac
suffix:semicolon
multiline_comment|/* &lt;---- RCsetmac */
multiline_comment|/* GETLINKSTATUS structure */
DECL|struct|RCgetlnkstatus_tag
r_struct
id|RCgetlnkstatus_tag
(brace
DECL|member|ReturnStatus
id|U32
id|ReturnStatus
suffix:semicolon
DECL|member|RCgetlnkstatus
)brace
id|RCgetlnkstatus
suffix:semicolon
multiline_comment|/* &lt;---- RCgetlnkstatus */
multiline_comment|/* GETLINKSTATISTICS structure */
DECL|struct|RCgetlinkstats_tag
r_struct
id|RCgetlinkstats_tag
(brace
DECL|member|StatsReturn
id|RCLINKSTATS
id|StatsReturn
suffix:semicolon
DECL|member|RCgetlinkstats
)brace
id|RCgetlinkstats
suffix:semicolon
multiline_comment|/* &lt;---- RCgetlinkstats */
multiline_comment|/* DEFAULT structure (when no command was recognized) */
DECL|struct|RCdefault_tag
r_struct
id|RCdefault_tag
(brace
DECL|member|rc
r_int
id|rc
suffix:semicolon
DECL|member|RCdefault
)brace
id|RCdefault
suffix:semicolon
multiline_comment|/* &lt;---- RCdefault */
DECL|member|data
)brace
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* struct RC_user_tag { ... } */
multiline_comment|/* 2) User data entry */
multiline_comment|/* RCUD = RedCreek User Data */
DECL|union|RC_user_data_tag
r_union
id|RC_user_data_tag
(brace
multiline_comment|/* structure tags used are taken from RC_user_tag structure above */
DECL|member|getinfo
r_struct
id|RCgetinfo_tag
op_star
id|getinfo
suffix:semicolon
DECL|member|getspeed
r_struct
id|RCgetspeed_tag
op_star
id|getspeed
suffix:semicolon
DECL|member|getprom
r_struct
id|RCgetprom_tag
op_star
id|getprom
suffix:semicolon
DECL|member|getbroadcast
r_struct
id|RCgetbroadcast_tag
op_star
id|getbroadcast
suffix:semicolon
DECL|member|getfwver
r_struct
id|RCgetfwver_tag
op_star
id|getfwver
suffix:semicolon
DECL|member|getipandmask
r_struct
id|RCgetipnmask_tag
op_star
id|getipandmask
suffix:semicolon
DECL|member|getmac
r_struct
id|RCgetmac_tag
op_star
id|getmac
suffix:semicolon
DECL|member|getlinkstatus
r_struct
id|RCgetlnkstatus_tag
op_star
id|getlinkstatus
suffix:semicolon
DECL|member|getlinkstatistics
r_struct
id|RCgetlinkstats_tag
op_star
id|getlinkstatistics
suffix:semicolon
DECL|member|rcdefault
r_struct
id|RCdefault_tag
op_star
id|rcdefault
suffix:semicolon
DECL|member|setspeed
r_struct
id|RCsetspeed_tag
op_star
id|setspeed
suffix:semicolon
DECL|member|setprom
r_struct
id|RCsetprom_tag
op_star
id|setprom
suffix:semicolon
DECL|member|setbroadcast
r_struct
id|RCsetbroadcast_tag
op_star
id|setbroadcast
suffix:semicolon
DECL|member|setipandmask
r_struct
id|RCsetipnmask_tag
op_star
id|setipandmask
suffix:semicolon
DECL|member|setmac
r_struct
id|RCsetmac_tag
op_star
id|setmac
suffix:semicolon
DECL|variable|_RC_user_data
)brace
id|_RC_user_data
suffix:semicolon
multiline_comment|/* declare as a global, so the defines below will work */
multiline_comment|/* 3) Structure short-cut entry */
multiline_comment|/* define structure short-cuts */
multiline_comment|/* structure names are taken from RC_user_tag structure above */
DECL|macro|RCUS_GETINFO
mdefine_line|#define RCUS_GETINFO           data.RCgetinfo;
DECL|macro|RCUS_GETSPEED
mdefine_line|#define RCUS_GETSPEED          data.RCgetspeed;
DECL|macro|RCUS_GETPROM
mdefine_line|#define RCUS_GETPROM           data.RCgetprom;
DECL|macro|RCUS_GETBROADCAST
mdefine_line|#define RCUS_GETBROADCAST      data.RCgetbroadcast;
DECL|macro|RCUS_GETFWVER
mdefine_line|#define RCUS_GETFWVER          data.RCgetfwver;
DECL|macro|RCUS_GETIPANDMASK
mdefine_line|#define RCUS_GETIPANDMASK      data.RCgetipandmask;
DECL|macro|RCUS_GETMAC
mdefine_line|#define RCUS_GETMAC            data.RCgetmac;
DECL|macro|RCUS_GETLINKSTATUS
mdefine_line|#define RCUS_GETLINKSTATUS     data.RCgetlnkstatus;
DECL|macro|RCUS_GETLINKSTATISTICS
mdefine_line|#define RCUS_GETLINKSTATISTICS data.RCgetlinkstats;
DECL|macro|RCUS_DEFAULT
mdefine_line|#define RCUS_DEFAULT           data.RCdefault;
DECL|macro|RCUS_SETSPEED
mdefine_line|#define RCUS_SETSPEED          data.RCsetspeed;
DECL|macro|RCUS_SETPROM
mdefine_line|#define RCUS_SETPROM           data.RCsetprom;
DECL|macro|RCUS_SETBROADCAST
mdefine_line|#define RCUS_SETBROADCAST      data.RCsetbroadcast;
DECL|macro|RCUS_SETIPANDMASK
mdefine_line|#define RCUS_SETIPANDMASK      data.RCsetipandmask;
DECL|macro|RCUS_SETMAC
mdefine_line|#define RCUS_SETMAC            data.RCsetmac;
multiline_comment|/* 4) Data short-cut entry */
multiline_comment|/* define data short-cuts */
multiline_comment|/* pointer names are from RC_user_data_tag union (just below RC_user_tag) */
DECL|macro|RCUD_GETINFO
mdefine_line|#define RCUD_GETINFO           _RC_user_data.getinfo
DECL|macro|RCUD_GETSPEED
mdefine_line|#define RCUD_GETSPEED          _RC_user_data.getspeed
DECL|macro|RCUD_GETPROM
mdefine_line|#define RCUD_GETPROM           _RC_user_data.getprom
DECL|macro|RCUD_GETBROADCAST
mdefine_line|#define RCUD_GETBROADCAST      _RC_user_data.getbroadcast
DECL|macro|RCUD_GETFWVER
mdefine_line|#define RCUD_GETFWVER          _RC_user_data.getfwver
DECL|macro|RCUD_GETIPANDMASK
mdefine_line|#define RCUD_GETIPANDMASK      _RC_user_data.getipandmask
DECL|macro|RCUD_GETMAC
mdefine_line|#define RCUD_GETMAC            _RC_user_data.getmac
DECL|macro|RCUD_GETLINKSTATUS
mdefine_line|#define RCUD_GETLINKSTATUS     _RC_user_data.getlinkstatus
DECL|macro|RCUD_GETLINKSTATISTICS
mdefine_line|#define RCUD_GETLINKSTATISTICS _RC_user_data.getlinkstatistics
DECL|macro|RCUD_DEFAULT
mdefine_line|#define RCUD_DEFAULT           _RC_user_data.rcdefault
DECL|macro|RCUD_SETSPEED
mdefine_line|#define RCUD_SETSPEED          _RC_user_data.setspeed
DECL|macro|RCUD_SETPROM
mdefine_line|#define RCUD_SETPROM           _RC_user_data.setprom
DECL|macro|RCUD_SETBROADCAST
mdefine_line|#define RCUD_SETBROADCAST      _RC_user_data.setbroadcast
DECL|macro|RCUD_SETIPANDMASK
mdefine_line|#define RCUD_SETIPANDMASK      _RC_user_data.setipandmask
DECL|macro|RCUD_SETMAC
mdefine_line|#define RCUD_SETMAC            _RC_user_data.setmac
multiline_comment|/* 5) Command identifier entry */
multiline_comment|/* define command identifiers */
DECL|macro|RCUC_GETINFO
mdefine_line|#define RCUC_GETINFO            0x01
DECL|macro|RCUC_GETSPEED
mdefine_line|#define RCUC_GETSPEED           0x02
DECL|macro|RCUC_GETFWVER
mdefine_line|#define RCUC_GETFWVER           0x03
DECL|macro|RCUC_GETIPANDMASK
mdefine_line|#define RCUC_GETIPANDMASK       0x04
DECL|macro|RCUC_GETMAC
mdefine_line|#define RCUC_GETMAC             0x05
DECL|macro|RCUC_GETLINKSTATUS
mdefine_line|#define RCUC_GETLINKSTATUS      0x06
DECL|macro|RCUC_GETLINKSTATISTICS
mdefine_line|#define RCUC_GETLINKSTATISTICS  0x07
DECL|macro|RCUC_GETPROM
mdefine_line|#define RCUC_GETPROM            0x14
DECL|macro|RCUC_GETBROADCAST
mdefine_line|#define RCUC_GETBROADCAST       0x15
DECL|macro|RCUC_DEFAULT
mdefine_line|#define RCUC_DEFAULT            0xff
DECL|macro|RCUC_SETSPEED
mdefine_line|#define RCUC_SETSPEED           0x08
DECL|macro|RCUC_SETIPANDMASK
mdefine_line|#define RCUC_SETIPANDMASK       0x09
DECL|macro|RCUC_SETMAC
mdefine_line|#define RCUC_SETMAC             0x0a
DECL|macro|RCUC_SETPROM
mdefine_line|#define RCUC_SETPROM            0x16
DECL|macro|RCUC_SETBROADCAST
mdefine_line|#define RCUC_SETBROADCAST       0x17
multiline_comment|/* define ioctl commands to use, when talking to RC 45/PCI driver */
DECL|macro|RCU_PROTOCOL_REV
mdefine_line|#define RCU_PROTOCOL_REV         SIOCDEVPRIVATE
DECL|macro|RCU_COMMAND
mdefine_line|#define RCU_COMMAND              SIOCDEVPRIVATE+1
multiline_comment|/*&n;   Intended use for the above defines is shown below (GETINFO, as this example):&n;&n;      RCuser_struct RCuser;           // declare RCuser structure&n;      struct ifreq ifr;               // declare an interface request structure&n;&n;      RCuser.cmd = RCUC_GETINFO;           // set user command to GETINFO&n;      ifr-&gt;ifr_data = (caddr_t) &amp;RCuser;   // set point to user structure&n;&n;      sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);   // get a socket&n;      ioctl(sock, RCU_COMMAND, &amp;ifr);                  // do ioctl on socket&n;&n;      RCUD_GETINFO = &amp;RCuser.RCUS_GETINFO;   // set data pointer for GETINFO&n;&n;      // print results&n;      printf(&quot;memory 0x%lx-0x%lx, base address 0x%x, irq 0x%x&bslash;n&quot;,&n;              RCUD_GETINFO-&gt;mem_start, RCUD_GETINFO-&gt;mem_end,&n;              RCUD_GETINFO-&gt;base_addr, RCUD_GETINFO-&gt;irq);&n;*/
macro_line|#endif   /* RCIF_H */
eof
