multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******                 R O U T E     H E A D E R&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Ian Nandhra / Jeremy Rolls&n; Date    :&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n;&n; ***************************************************************************/
macro_line|#ifndef _route_h
DECL|macro|_route_h
mdefine_line|#define _route_h
macro_line|#ifdef SCCS_LABELS
macro_line|#ifndef lint
multiline_comment|/* static char *_rio_route_h_sccs = &quot;@(#)route.h&t;1.3&quot;; */
macro_line|#endif
macro_line|#endif
DECL|macro|MAX_LINKS
mdefine_line|#define MAX_LINKS 4
DECL|macro|MAX_NODES
mdefine_line|#define MAX_NODES 17                          /* Maximum nodes in a subnet */
DECL|macro|NODE_BYTES
mdefine_line|#define NODE_BYTES ((MAX_NODES / 8) + 1)      /* Number of bytes needed for&n;                                                 1 bit per node */
DECL|macro|ROUTE_DATA_SIZE
mdefine_line|#define ROUTE_DATA_SIZE  (NODE_BYTES + 2)     /* Number of bytes for complete &n;                                                 info about cost etc. */
DECL|macro|ROUTES_PER_PACKET
mdefine_line|#define ROUTES_PER_PACKET ((PKT_MAX_DATA_LEN -2)/ ROUTE_DATA_SIZE)
multiline_comment|/* Number of nodes we can squeeze&n;                                                 into one packet */
DECL|macro|MAX_TOPOLOGY_PACKETS
mdefine_line|#define MAX_TOPOLOGY_PACKETS (MAX_NODES / ROUTES_PER_PACKET + 1)
multiline_comment|/************************************************&n; * Define the types of command for the ROUTE RUP.&n; ************************************************/
DECL|macro|ROUTE_REQUEST
mdefine_line|#define ROUTE_REQUEST    0                    /* Request an ID */
DECL|macro|ROUTE_FOAD
mdefine_line|#define ROUTE_FOAD       1                    /* Kill the RTA */
DECL|macro|ROUTE_ALREADY
mdefine_line|#define ROUTE_ALREADY    2                    /* ID given already */
DECL|macro|ROUTE_USED
mdefine_line|#define ROUTE_USED       3                    /* All ID&squot;s used */
DECL|macro|ROUTE_ALLOCATE
mdefine_line|#define ROUTE_ALLOCATE   4                    /* Here it is */
DECL|macro|ROUTE_REQ_TOP
mdefine_line|#define ROUTE_REQ_TOP    5                    /* I bet you didn&squot;t expect....&n;                                                 the Topological Inquisition */
DECL|macro|ROUTE_TOPOLOGY
mdefine_line|#define ROUTE_TOPOLOGY   6                    /* Topology request answered FD */
multiline_comment|/*******************************************************************&n; * Define the Route Map Structure&n; *&n; * The route map gives a pointer to a Link Structure to use.&n; * This allows Disconnected Links to be checked quickly&n; ******************************************************************/
DECL|typedef|COST_ROUTE
r_typedef
r_struct
id|COST_ROUTE
id|COST_ROUTE
suffix:semicolon
DECL|struct|COST_ROUTE
r_struct
id|COST_ROUTE
(brace
DECL|member|cost
r_int
r_char
id|cost
suffix:semicolon
multiline_comment|/* Cost down this link */
DECL|member|route
r_int
r_char
id|route
(braket
id|NODE_BYTES
)braket
suffix:semicolon
multiline_comment|/* Nodes thorough this route */
)brace
suffix:semicolon
DECL|typedef|ROUTE_STR
r_typedef
r_struct
id|ROUTE_STR
id|ROUTE_STR
suffix:semicolon
DECL|struct|ROUTE_STR
r_struct
id|ROUTE_STR
(brace
DECL|member|cost_route
id|COST_ROUTE
id|cost_route
(braket
id|MAX_LINKS
)braket
suffix:semicolon
multiline_comment|/* cost / route for this link */
DECL|member|favoured
id|ushort
id|favoured
suffix:semicolon
multiline_comment|/* favoured link */
)brace
suffix:semicolon
DECL|macro|NO_LINK
mdefine_line|#define NO_LINK            (short) 5      /* Link unattached */
DECL|macro|ROUTE_NO_ID
mdefine_line|#define ROUTE_NO_ID        (short) 100    /* No Id */
DECL|macro|ROUTE_DISCONNECT
mdefine_line|#define ROUTE_DISCONNECT   (ushort) 0xff  /* Not connected */
DECL|macro|ROUTE_INTERCONNECT
mdefine_line|#define ROUTE_INTERCONNECT (ushort) 0x40  /* Sub-net interconnect */
DECL|macro|SYNC_RUP
mdefine_line|#define SYNC_RUP         (ushort) 255
DECL|macro|COMMAND_RUP
mdefine_line|#define COMMAND_RUP      (ushort) 254
DECL|macro|ERROR_RUP
mdefine_line|#define ERROR_RUP        (ushort) 253
DECL|macro|POLL_RUP
mdefine_line|#define POLL_RUP         (ushort) 252
DECL|macro|BOOT_RUP
mdefine_line|#define BOOT_RUP         (ushort) 251
DECL|macro|ROUTE_RUP
mdefine_line|#define ROUTE_RUP        (ushort) 250
DECL|macro|STATUS_RUP
mdefine_line|#define STATUS_RUP       (ushort) 249
DECL|macro|POWER_RUP
mdefine_line|#define POWER_RUP        (ushort) 248
DECL|macro|HIGHEST_RUP
mdefine_line|#define HIGHEST_RUP      (ushort) 255   /* Set to Top one */
DECL|macro|LOWEST_RUP
mdefine_line|#define LOWEST_RUP       (ushort) 248   /* Set to bottom one */
macro_line|#endif
multiline_comment|/*********** end of file ***********/
eof
