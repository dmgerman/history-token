multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; * Copyright (c) 2001-2003 International Business Machines, Corp.&n; * &n; * This file is part of the SCTP kernel reference Implementation&n; * &n; * SCTP Checksum functions&n; * &n; * The SCTP reference implementation is free software; &n; * you can redistribute it and/or modify it under the terms of &n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; * &n; * The SCTP reference implementation is distributed in the hope that it &n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.  &n; * &n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; * &n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by: &n; *    Dinakaran Joseph &n; *    Jon Grimm &lt;jgrimm@us.ibm.com&gt;&n; *    Sridhar Samudrala &lt;sri@us.ibm.com&gt;&n; * &n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
multiline_comment|/* The following code has been taken directly from&n; * draft-ietf-tsvwg-sctpcsum-03.txt&n; *&n; * The code has now been modified specifically for SCTP knowledge.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;net/sctp/sctp.h&gt;
DECL|macro|CRC32C_POLY
mdefine_line|#define CRC32C_POLY 0x1EDC6F41
DECL|macro|CRC32C
mdefine_line|#define CRC32C(c,d) (c=(c&gt;&gt;8)^crc_c[(c^(d))&amp;0xFF])
multiline_comment|/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
multiline_comment|/* Copyright 2001, D. Otis.  Use this program, code or tables    */
multiline_comment|/* extracted from it, as desired without restriction.            */
multiline_comment|/*                                                               */
multiline_comment|/* 32 Bit Reflected CRC table generation for SCTP.               */
multiline_comment|/* To accommodate serial byte data being shifted out least       */
multiline_comment|/* significant bit first, the table&squot;s 32 bit words are reflected */
multiline_comment|/* which flips both byte and bit MS and LS positions.  The CRC   */
multiline_comment|/* is calculated MS bits first from the perspective of the serial*/
multiline_comment|/* stream.  The x^32 term is implied and the x^0 term may also   */
multiline_comment|/* be shown as +1.  The polynomial code used is 0x1EDC6F41.      */
multiline_comment|/* Castagnoli93                                                  */
multiline_comment|/* x^32+x^28+x^27+x^26+x^25+x^23+x^22+x^20+x^19+x^18+x^14+x^13+  */
multiline_comment|/* x^11+x^10+x^9+x^8+x^6+x^0                                     */
multiline_comment|/* Guy Castagnoli Stefan Braeuer and Martin Herrman              */
multiline_comment|/* &quot;Optimization of Cyclic Redundancy-Check Codes                */
multiline_comment|/* with 24 and 32 Parity Bits&quot;,                                  */
multiline_comment|/* IEEE Transactions on Communications, Vol.41, No.6, June 1993  */
multiline_comment|/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
DECL|variable|crc_c
id|__u32
id|crc_c
(braket
l_int|256
)braket
op_assign
(brace
l_int|0x00000000
comma
l_int|0xF26B8303
comma
l_int|0xE13B70F7
comma
l_int|0x1350F3F4
comma
l_int|0xC79A971F
comma
l_int|0x35F1141C
comma
l_int|0x26A1E7E8
comma
l_int|0xD4CA64EB
comma
l_int|0x8AD958CF
comma
l_int|0x78B2DBCC
comma
l_int|0x6BE22838
comma
l_int|0x9989AB3B
comma
l_int|0x4D43CFD0
comma
l_int|0xBF284CD3
comma
l_int|0xAC78BF27
comma
l_int|0x5E133C24
comma
l_int|0x105EC76F
comma
l_int|0xE235446C
comma
l_int|0xF165B798
comma
l_int|0x030E349B
comma
l_int|0xD7C45070
comma
l_int|0x25AFD373
comma
l_int|0x36FF2087
comma
l_int|0xC494A384
comma
l_int|0x9A879FA0
comma
l_int|0x68EC1CA3
comma
l_int|0x7BBCEF57
comma
l_int|0x89D76C54
comma
l_int|0x5D1D08BF
comma
l_int|0xAF768BBC
comma
l_int|0xBC267848
comma
l_int|0x4E4DFB4B
comma
l_int|0x20BD8EDE
comma
l_int|0xD2D60DDD
comma
l_int|0xC186FE29
comma
l_int|0x33ED7D2A
comma
l_int|0xE72719C1
comma
l_int|0x154C9AC2
comma
l_int|0x061C6936
comma
l_int|0xF477EA35
comma
l_int|0xAA64D611
comma
l_int|0x580F5512
comma
l_int|0x4B5FA6E6
comma
l_int|0xB93425E5
comma
l_int|0x6DFE410E
comma
l_int|0x9F95C20D
comma
l_int|0x8CC531F9
comma
l_int|0x7EAEB2FA
comma
l_int|0x30E349B1
comma
l_int|0xC288CAB2
comma
l_int|0xD1D83946
comma
l_int|0x23B3BA45
comma
l_int|0xF779DEAE
comma
l_int|0x05125DAD
comma
l_int|0x1642AE59
comma
l_int|0xE4292D5A
comma
l_int|0xBA3A117E
comma
l_int|0x4851927D
comma
l_int|0x5B016189
comma
l_int|0xA96AE28A
comma
l_int|0x7DA08661
comma
l_int|0x8FCB0562
comma
l_int|0x9C9BF696
comma
l_int|0x6EF07595
comma
l_int|0x417B1DBC
comma
l_int|0xB3109EBF
comma
l_int|0xA0406D4B
comma
l_int|0x522BEE48
comma
l_int|0x86E18AA3
comma
l_int|0x748A09A0
comma
l_int|0x67DAFA54
comma
l_int|0x95B17957
comma
l_int|0xCBA24573
comma
l_int|0x39C9C670
comma
l_int|0x2A993584
comma
l_int|0xD8F2B687
comma
l_int|0x0C38D26C
comma
l_int|0xFE53516F
comma
l_int|0xED03A29B
comma
l_int|0x1F682198
comma
l_int|0x5125DAD3
comma
l_int|0xA34E59D0
comma
l_int|0xB01EAA24
comma
l_int|0x42752927
comma
l_int|0x96BF4DCC
comma
l_int|0x64D4CECF
comma
l_int|0x77843D3B
comma
l_int|0x85EFBE38
comma
l_int|0xDBFC821C
comma
l_int|0x2997011F
comma
l_int|0x3AC7F2EB
comma
l_int|0xC8AC71E8
comma
l_int|0x1C661503
comma
l_int|0xEE0D9600
comma
l_int|0xFD5D65F4
comma
l_int|0x0F36E6F7
comma
l_int|0x61C69362
comma
l_int|0x93AD1061
comma
l_int|0x80FDE395
comma
l_int|0x72966096
comma
l_int|0xA65C047D
comma
l_int|0x5437877E
comma
l_int|0x4767748A
comma
l_int|0xB50CF789
comma
l_int|0xEB1FCBAD
comma
l_int|0x197448AE
comma
l_int|0x0A24BB5A
comma
l_int|0xF84F3859
comma
l_int|0x2C855CB2
comma
l_int|0xDEEEDFB1
comma
l_int|0xCDBE2C45
comma
l_int|0x3FD5AF46
comma
l_int|0x7198540D
comma
l_int|0x83F3D70E
comma
l_int|0x90A324FA
comma
l_int|0x62C8A7F9
comma
l_int|0xB602C312
comma
l_int|0x44694011
comma
l_int|0x5739B3E5
comma
l_int|0xA55230E6
comma
l_int|0xFB410CC2
comma
l_int|0x092A8FC1
comma
l_int|0x1A7A7C35
comma
l_int|0xE811FF36
comma
l_int|0x3CDB9BDD
comma
l_int|0xCEB018DE
comma
l_int|0xDDE0EB2A
comma
l_int|0x2F8B6829
comma
l_int|0x82F63B78
comma
l_int|0x709DB87B
comma
l_int|0x63CD4B8F
comma
l_int|0x91A6C88C
comma
l_int|0x456CAC67
comma
l_int|0xB7072F64
comma
l_int|0xA457DC90
comma
l_int|0x563C5F93
comma
l_int|0x082F63B7
comma
l_int|0xFA44E0B4
comma
l_int|0xE9141340
comma
l_int|0x1B7F9043
comma
l_int|0xCFB5F4A8
comma
l_int|0x3DDE77AB
comma
l_int|0x2E8E845F
comma
l_int|0xDCE5075C
comma
l_int|0x92A8FC17
comma
l_int|0x60C37F14
comma
l_int|0x73938CE0
comma
l_int|0x81F80FE3
comma
l_int|0x55326B08
comma
l_int|0xA759E80B
comma
l_int|0xB4091BFF
comma
l_int|0x466298FC
comma
l_int|0x1871A4D8
comma
l_int|0xEA1A27DB
comma
l_int|0xF94AD42F
comma
l_int|0x0B21572C
comma
l_int|0xDFEB33C7
comma
l_int|0x2D80B0C4
comma
l_int|0x3ED04330
comma
l_int|0xCCBBC033
comma
l_int|0xA24BB5A6
comma
l_int|0x502036A5
comma
l_int|0x4370C551
comma
l_int|0xB11B4652
comma
l_int|0x65D122B9
comma
l_int|0x97BAA1BA
comma
l_int|0x84EA524E
comma
l_int|0x7681D14D
comma
l_int|0x2892ED69
comma
l_int|0xDAF96E6A
comma
l_int|0xC9A99D9E
comma
l_int|0x3BC21E9D
comma
l_int|0xEF087A76
comma
l_int|0x1D63F975
comma
l_int|0x0E330A81
comma
l_int|0xFC588982
comma
l_int|0xB21572C9
comma
l_int|0x407EF1CA
comma
l_int|0x532E023E
comma
l_int|0xA145813D
comma
l_int|0x758FE5D6
comma
l_int|0x87E466D5
comma
l_int|0x94B49521
comma
l_int|0x66DF1622
comma
l_int|0x38CC2A06
comma
l_int|0xCAA7A905
comma
l_int|0xD9F75AF1
comma
l_int|0x2B9CD9F2
comma
l_int|0xFF56BD19
comma
l_int|0x0D3D3E1A
comma
l_int|0x1E6DCDEE
comma
l_int|0xEC064EED
comma
l_int|0xC38D26C4
comma
l_int|0x31E6A5C7
comma
l_int|0x22B65633
comma
l_int|0xD0DDD530
comma
l_int|0x0417B1DB
comma
l_int|0xF67C32D8
comma
l_int|0xE52CC12C
comma
l_int|0x1747422F
comma
l_int|0x49547E0B
comma
l_int|0xBB3FFD08
comma
l_int|0xA86F0EFC
comma
l_int|0x5A048DFF
comma
l_int|0x8ECEE914
comma
l_int|0x7CA56A17
comma
l_int|0x6FF599E3
comma
l_int|0x9D9E1AE0
comma
l_int|0xD3D3E1AB
comma
l_int|0x21B862A8
comma
l_int|0x32E8915C
comma
l_int|0xC083125F
comma
l_int|0x144976B4
comma
l_int|0xE622F5B7
comma
l_int|0xF5720643
comma
l_int|0x07198540
comma
l_int|0x590AB964
comma
l_int|0xAB613A67
comma
l_int|0xB831C993
comma
l_int|0x4A5A4A90
comma
l_int|0x9E902E7B
comma
l_int|0x6CFBAD78
comma
l_int|0x7FAB5E8C
comma
l_int|0x8DC0DD8F
comma
l_int|0xE330A81A
comma
l_int|0x115B2B19
comma
l_int|0x020BD8ED
comma
l_int|0xF0605BEE
comma
l_int|0x24AA3F05
comma
l_int|0xD6C1BC06
comma
l_int|0xC5914FF2
comma
l_int|0x37FACCF1
comma
l_int|0x69E9F0D5
comma
l_int|0x9B8273D6
comma
l_int|0x88D28022
comma
l_int|0x7AB90321
comma
l_int|0xAE7367CA
comma
l_int|0x5C18E4C9
comma
l_int|0x4F48173D
comma
l_int|0xBD23943E
comma
l_int|0xF36E6F75
comma
l_int|0x0105EC76
comma
l_int|0x12551F82
comma
l_int|0xE03E9C81
comma
l_int|0x34F4F86A
comma
l_int|0xC69F7B69
comma
l_int|0xD5CF889D
comma
l_int|0x27A40B9E
comma
l_int|0x79B737BA
comma
l_int|0x8BDCB4B9
comma
l_int|0x988C474D
comma
l_int|0x6AE7C44E
comma
l_int|0xBE2DA0A5
comma
l_int|0x4C4623A6
comma
l_int|0x5F16D052
comma
l_int|0xAD7D5351
comma
)brace
suffix:semicolon
DECL|function|sctp_start_cksum
id|__u32
id|sctp_start_cksum
c_func
(paren
id|__u8
op_star
id|buffer
comma
id|__u16
id|length
)paren
(brace
id|__u32
id|crc32
op_assign
op_complement
(paren
id|__u32
)paren
l_int|0
suffix:semicolon
id|__u32
id|i
suffix:semicolon
multiline_comment|/* Optimize this routine to be SCTP specific, knowing how&n;&t; * to skip the checksum field of the SCTP header.&n;&t; */
multiline_comment|/* Calculate CRC up to the checksum. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
r_sizeof
(paren
r_struct
id|sctphdr
)paren
op_minus
r_sizeof
(paren
id|__u32
)paren
)paren
suffix:semicolon
id|i
op_increment
)paren
id|CRC32C
c_func
(paren
id|crc32
comma
id|buffer
(braket
id|i
)braket
)paren
suffix:semicolon
multiline_comment|/* Skip checksum field of the header. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
(paren
id|__u32
)paren
suffix:semicolon
id|i
op_increment
)paren
id|CRC32C
c_func
(paren
id|crc32
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Calculate the rest of the CRC. */
r_for
c_loop
(paren
id|i
op_assign
r_sizeof
(paren
r_struct
id|sctphdr
)paren
suffix:semicolon
id|i
OL
id|length
suffix:semicolon
id|i
op_increment
)paren
id|CRC32C
c_func
(paren
id|crc32
comma
id|buffer
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
id|crc32
suffix:semicolon
)brace
DECL|function|sctp_update_cksum
id|__u32
id|sctp_update_cksum
c_func
(paren
id|__u8
op_star
id|buffer
comma
id|__u16
id|length
comma
id|__u32
id|crc32
)paren
(brace
id|__u32
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
id|length
suffix:semicolon
id|i
op_increment
)paren
id|CRC32C
c_func
(paren
id|crc32
comma
id|buffer
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
id|crc32
suffix:semicolon
)brace
DECL|function|sctp_end_cksum
id|__u32
id|sctp_end_cksum
c_func
(paren
id|__u32
id|crc32
)paren
(brace
id|__u32
id|result
suffix:semicolon
id|__u8
id|byte0
comma
id|byte1
comma
id|byte2
comma
id|byte3
suffix:semicolon
id|result
op_assign
op_complement
id|crc32
suffix:semicolon
multiline_comment|/*  result  now holds the negated polynomial remainder;&n;&t; *  since the table and algorithm is &quot;reflected&quot; [williams95].&n;&t; *  That is,  result has the same value as if we mapped the message&n;&t; *  to a polyomial, computed the host-bit-order polynomial&n;&t; *  remainder, performed final negation, then did an end-for-end&n;&t; *  bit-reversal.&n;&t; *  Note that a 32-bit bit-reversal is identical to four inplace&n;&t; *  8-bit reversals followed by an end-for-end byteswap.&n;&t; *  In other words, the bytes of each bit are in the right order,&n;&t; *  but the bytes have been byteswapped.  So we now do an explicit&n;&t; *  byteswap.  On a little-endian machine, this byteswap and&n;&t; *  the final ntohl cancel out and could be elided.&n;&t; */
id|byte0
op_assign
id|result
op_amp
l_int|0xff
suffix:semicolon
id|byte1
op_assign
(paren
id|result
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|byte2
op_assign
(paren
id|result
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
id|byte3
op_assign
(paren
id|result
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
suffix:semicolon
id|crc32
op_assign
(paren
(paren
id|byte0
op_lshift
l_int|24
)paren
op_or
(paren
id|byte1
op_lshift
l_int|16
)paren
op_or
(paren
id|byte2
op_lshift
l_int|8
)paren
op_or
id|byte3
)paren
suffix:semicolon
r_return
id|crc32
suffix:semicolon
)brace
eof
