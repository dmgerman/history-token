multiline_comment|/*&n;** -----------------------------------------------------------------------------&n;**&n;**  Perle Specialix driver for Linux&n;**  Ported from existing RIO Driver for SCO sources.&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**&t;Module&t;&t;: map.h&n;**&t;SID&t;&t;: 1.2&n;**&t;Last Modified&t;: 11/6/98 11:34:11&n;**&t;Retrieved&t;: 11/6/98 11:34:21&n;**&n;**  ident @(#)map.h&t;1.2&n;**&n;** -----------------------------------------------------------------------------&n;*/
macro_line|#ifndef __rio_map_h__
DECL|macro|__rio_map_h__
mdefine_line|#define __rio_map_h__
macro_line|#ifdef SCCS_LABELS
DECL|variable|_map_h_sccs_
r_static
r_char
op_star
id|_map_h_sccs_
op_assign
l_string|&quot;@(#)map.h&t;1.2&quot;
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;** mapping structure passed to and from the config.rio program to&n;** determine the current topology of the world&n;*/
DECL|macro|MAX_MAP_ENTRY
mdefine_line|#define MAX_MAP_ENTRY 17
DECL|macro|TOTAL_MAP_ENTRIES
mdefine_line|#define&t;TOTAL_MAP_ENTRIES (MAX_MAP_ENTRY*RIO_SLOTS)
DECL|macro|MAX_NAME_LEN
mdefine_line|#define&t;MAX_NAME_LEN 32
DECL|struct|Map
r_struct
id|Map
(brace
DECL|member|HostUniqueNum
id|uint
id|HostUniqueNum
suffix:semicolon
multiline_comment|/* Supporting hosts unique number */
DECL|member|RtaUniqueNum
id|uint
id|RtaUniqueNum
suffix:semicolon
multiline_comment|/* Unique number */
multiline_comment|/*&n;&t;** The next two IDs must be swapped on big-endian architectures&n;&t;** when using a v2.04 /etc/rio/config with a v3.00 driver (when&n;&t;** upgrading for example).&n;&t;*/
DECL|member|ID
id|ushort
id|ID
suffix:semicolon
multiline_comment|/* ID used in the subnet */
DECL|member|ID2
id|ushort
id|ID2
suffix:semicolon
multiline_comment|/* ID of 2nd block of 8 for 16 port */
DECL|member|Flags
id|ulong
id|Flags
suffix:semicolon
multiline_comment|/* Booted, ID Given, Disconnected */
DECL|member|SysPort
id|ulong
id|SysPort
suffix:semicolon
multiline_comment|/* First tty mapped to this port */
DECL|member|Topology
r_struct
id|Top
id|Topology
(braket
id|LINKS_PER_UNIT
)braket
suffix:semicolon
multiline_comment|/* ID connected to each link */
DECL|member|Name
r_char
id|Name
(braket
id|MAX_NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* Cute name by which RTA is known */
)brace
suffix:semicolon
multiline_comment|/*&n;** Flag values:&n;*/
DECL|macro|RTA_BOOTED
mdefine_line|#define&t;RTA_BOOTED&t;&t;0x00000001
DECL|macro|RTA_NEWBOOT
mdefine_line|#define RTA_NEWBOOT&t;&t;0x00000010
DECL|macro|MSG_DONE
mdefine_line|#define&t;MSG_DONE&t;&t;0x00000020
DECL|macro|RTA_INTERCONNECT
mdefine_line|#define&t;RTA_INTERCONNECT&t;0x00000040
DECL|macro|RTA16_SECOND_SLOT
mdefine_line|#define&t;RTA16_SECOND_SLOT&t;0x00000080
DECL|macro|BEEN_HERE
mdefine_line|#define&t;BEEN_HERE&t;&t;0x00000100
DECL|macro|SLOT_TENTATIVE
mdefine_line|#define SLOT_TENTATIVE&t;&t;0x40000000
DECL|macro|SLOT_IN_USE
mdefine_line|#define SLOT_IN_USE&t;&t;0x80000000
multiline_comment|/*&n;** HostUniqueNum is the unique number from the host card that this RTA&n;** is to be connected to.&n;** RtaUniqueNum is the unique number of the RTA concerned. It will be ZERO&n;** if the slot in the table is unused. If it is the same as the HostUniqueNum&n;** then this slot represents a host card.&n;** Flags contains current boot/route state info&n;** SysPort is a value in the range 0-504, being the number of the first tty&n;** on this RTA. Each RTA supports 8 ports. The SysPort value must be modulo 8.&n;** SysPort 0-127 correspond to /dev/ttyr001 to /dev/ttyr128, with minor&n;** numbers 0-127. SysPort 128-255 correspond to /dev/ttyr129 to /dev/ttyr256,&n;** again with minor numbers 0-127, and so on for SysPorts 256-383 and 384-511&n;** ID will be in the range 0-16 for a `known&squot; RTA. ID will be 0xFFFF for an&n;** unused slot/unknown ID etc.&n;** The Topology array contains the ID of the unit connected to each of the&n;** four links on this unit. The entry will be 0xFFFF if NOTHING is connected&n;** to the link, or will be 0xFF00 if an UNKNOWN unit is connected to the link.&n;** The Name field is a null-terminated string, upto 31 characters, containing&n;** the &squot;cute&squot; name that the sysadmin/users know the RTA by. It is permissible&n;** for this string to contain any character in the range &bslash;040 to &bslash;176 inclusive.&n;** In particular, ctrl sequences and DEL (0x7F, &bslash;177) are not allowed. The&n;** special character &squot;%&squot; IS allowable, and needs no special action.&n;**&n;*/
macro_line|#endif
eof
