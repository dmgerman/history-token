multiline_comment|/****************************************************************************&n; *******                                                              *******&n; *******                      L I S T                                 *******&n; *******                                                              *******&n; ****************************************************************************&n;&n; Author  : Jeremy Rolls.&n; Date    : 04-Nov-1990&n;&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; Version : 0.01&n;&n;&n;                            Mods&n; ----------------------------------------------------------------------------&n;  Date     By                Description&n; ----------------------------------------------------------------------------&n; ***************************************************************************/
macro_line|#ifndef _list_h
DECL|macro|_list_h
mdefine_line|#define _list_h 1
macro_line|#ifdef SCCS_LABELS
macro_line|#ifndef lint
DECL|variable|_rio_list_h_sccs
r_static
r_char
op_star
id|_rio_list_h_sccs
op_assign
l_string|&quot;@(#)list.h&t;1.9&quot;
suffix:semicolon
macro_line|#endif
macro_line|#endif
DECL|macro|PKT_IN_USE
mdefine_line|#define PKT_IN_USE    0x1
macro_line|#ifdef INKERNEL
DECL|macro|ZERO_PTR
mdefine_line|#define ZERO_PTR (ushort) 0x8000
DECL|macro|CaD
mdefine_line|#define&t;CaD&t;PortP-&gt;Caddr
multiline_comment|/*&n;** We can add another packet to a transmit queue if the packet pointer pointed&n;** to by the TxAdd pointer has PKT_IN_USE clear in its address.&n;*/
macro_line|#ifndef linux
macro_line|#if defined( MIPS ) &amp;&amp; !defined( MIPSEISA )
multiline_comment|/* May the shoes of the Devil dance on your grave for creating this */
DECL|macro|can_add_transmit
mdefine_line|#define   can_add_transmit(PacketP,PortP) &bslash;&n;          (!((uint)(PacketP = (struct PKT *)RIO_PTR(CaD,RINDW(PortP-&gt;TxAdd))) &bslash;&n;          &amp; (PKT_IN_USE&lt;&lt;2)))
macro_line|#elif  defined(MIPSEISA) || defined(nx6000) || &bslash;&n;       defined(drs6000)  || defined(UWsparc)
DECL|macro|can_add_transmit
mdefine_line|#define   can_add_transmit(PacketP,PortP) &bslash;&n;          (!((uint)(PacketP = (struct PKT *)RIO_PTR(CaD,RINDW(PortP-&gt;TxAdd))) &bslash;&n;&t;  &amp; PKT_IN_USE))
macro_line|#else
DECL|macro|can_add_transmit
mdefine_line|#define   can_add_transmit(PacketP,PortP) &bslash;&n;          (!((uint)(PacketP = (struct PKT *)RIO_PTR(CaD,*PortP-&gt;TxAdd)) &bslash;&n;&t;  &amp; PKT_IN_USE))
macro_line|#endif
multiline_comment|/*&n;** To add a packet to the queue, you set the PKT_IN_USE bit in the address,&n;** and then move the TxAdd pointer along one position to point to the next&n;** packet pointer. You must wrap the pointer from the end back to the start.&n;*/
macro_line|#if defined(MIPS) || defined(nx6000) || defined(drs6000) || defined(UWsparc)
DECL|macro|add_transmit
macro_line|#   define add_transmit(PortP)  &bslash;&n;&t;WINDW(PortP-&gt;TxAdd,RINDW(PortP-&gt;TxAdd) | PKT_IN_USE);&bslash;&n;&t;if (PortP-&gt;TxAdd == PortP-&gt;TxEnd)&bslash;&n;&t;    PortP-&gt;TxAdd = PortP-&gt;TxStart;&bslash;&n;&t;else&bslash;&n;&t;    PortP-&gt;TxAdd++;&bslash;&n;&t;WWORD(PortP-&gt;PhbP-&gt;tx_add , RIO_OFF(CaD,PortP-&gt;TxAdd));
macro_line|#elif defined(AIX)
DECL|macro|add_transmit
macro_line|#   define add_transmit(PortP)  &bslash;&n;&t;{&bslash;&n;&t;    register ushort *TxAddP = (ushort *)RIO_PTR(Cad,PortP-&gt;TxAddO);&bslash;&n;&t;    WINDW( TxAddP, RINDW( TxAddP ) | PKT_IN_USE );&bslash;&n;&t;    if (PortP-&gt;TxAddO == PortP-&gt;TxEndO )&bslash;&n;&t;&t;PortP-&gt;TxAddO = PortP-&gt;TxStartO;&bslash;&n;&t;    else&bslash;&n;&t;&t;PortP-&gt;TxAddO += sizeof(ushort);&bslash;&n;&t;    WWORD(((PHB *)RIO_PTR(Cad,PortP-&gt;PhbO))-&gt;tx_add , PortP-&gt;TxAddO );&bslash;&n;&t;}
macro_line|#else
DECL|macro|add_transmit
macro_line|#   define add_transmit(PortP)  &bslash;&n;&t;*PortP-&gt;TxAdd |= PKT_IN_USE;&bslash;&n;&t;if (PortP-&gt;TxAdd == PortP-&gt;TxEnd)&bslash;&n;&t;    PortP-&gt;TxAdd = PortP-&gt;TxStart;&bslash;&n;&t;else&bslash;&n;&t;    PortP-&gt;TxAdd++;&bslash;&n;&t;PortP-&gt;PhbP-&gt;tx_add = RIO_OFF(CaD,PortP-&gt;TxAdd);
macro_line|#endif
multiline_comment|/*&n;** can_remove_receive( PacketP, PortP ) returns non-zero if PKT_IN_USE is set&n;** for the next packet on the queue. It will also set PacketP to point to the&n;** relevent packet, [having cleared the PKT_IN_USE bit]. If PKT_IN_USE is clear,&n;** then can_remove_receive() returns 0.&n;*/
macro_line|#if defined(MIPS) || defined(nx6000) || defined(drs6000) || defined(UWsparc)
DECL|macro|can_remove_receive
macro_line|#   define can_remove_receive(PacketP,PortP) &bslash;&n;&t;((RINDW(PortP-&gt;RxRemove) &amp; PKT_IN_USE) ? &bslash;&n;&t;(PacketP=(struct PKT *)RIO_PTR(CaD,(RINDW(PortP-&gt;RxRemove) &amp; ~PKT_IN_USE))):0)
macro_line|#elif defined(AIX)
DECL|macro|can_remove_receive
macro_line|#   define can_remove_receive(PacketP,PortP) &bslash;&n;&t;((RINDW((ushort *)RIO_PTR(Cad,PortP-&gt;RxRemoveO)) &amp; PKT_IN_USE) ? &bslash;&n;&t;(PacketP=(struct PKT *)RIO_PTR(Cad,RINDW((ushort *)RIO_PTR(Cad,PortP-&gt;RxRemoveO)) &amp; ~PKT_IN_USE)):0)
macro_line|#else
DECL|macro|can_remove_receive
macro_line|#   define can_remove_receive(PacketP,PortP) &bslash;&n;&t;((*PortP-&gt;RxRemove &amp; PKT_IN_USE) ? &bslash;&n;&t;(PacketP=(struct PKT *)RIO_PTR(CaD,(*PortP-&gt;RxRemove &amp; ~PKT_IN_USE))):0)
macro_line|#endif
multiline_comment|/*&n;** Will God see it within his heart to forgive us for this thing that&n;** we have created? To remove a packet from the receive queue you clear&n;** its PKT_IN_USE bit, and then bump the pointers. Once the pointers&n;** get to the end, they must be wrapped back to the start.&n;*/
macro_line|#if defined(MIPS) || defined(nx6000) || defined(drs6000) || defined(UWsparc)
DECL|macro|remove_receive
macro_line|#   define remove_receive(PortP) &bslash;&n;&t;WINDW(PortP-&gt;RxRemove, (RINDW(PortP-&gt;RxRemove) &amp; ~PKT_IN_USE));&bslash;&n;&t;if (PortP-&gt;RxRemove == PortP-&gt;RxEnd)&bslash;&n;&t;    PortP-&gt;RxRemove = PortP-&gt;RxStart;&bslash;&n;&t;else&bslash;&n;&t;    PortP-&gt;RxRemove++;&bslash;&n;&t;WWORD(PortP-&gt;PhbP-&gt;rx_remove , RIO_OFF(CaD,PortP-&gt;RxRemove));
macro_line|#elif defined(AIX)
DECL|macro|remove_receive
macro_line|#   define remove_receive(PortP) &bslash;&n;    {&bslash;&n;        register ushort *RxRemoveP = (ushort *)RIO_PTR(Cad,PortP-&gt;RxRemoveO);&bslash;&n;        WINDW( RxRemoveP, RINDW( RxRemoveP ) &amp; ~PKT_IN_USE );&bslash;&n;        if (PortP-&gt;RxRemoveO == PortP-&gt;RxEndO)&bslash;&n;            PortP-&gt;RxRemoveO = PortP-&gt;RxStartO;&bslash;&n;        else&bslash;&n;            PortP-&gt;RxRemoveO += sizeof(ushort);&bslash;&n;        WWORD(((PHB *)RIO_PTR(Cad,PortP-&gt;PhbO))-&gt;rx_remove, PortP-&gt;RxRemoveO );&bslash;&n;    }
macro_line|#else
DECL|macro|remove_receive
macro_line|#   define remove_receive(PortP) &bslash;&n;&t;*PortP-&gt;RxRemove &amp;= ~PKT_IN_USE;&bslash;&n;&t;if (PortP-&gt;RxRemove == PortP-&gt;RxEnd)&bslash;&n;&t;    PortP-&gt;RxRemove = PortP-&gt;RxStart;&bslash;&n;&t;else&bslash;&n;&t;    PortP-&gt;RxRemove++;&bslash;&n;&t;PortP-&gt;PhbP-&gt;rx_remove = RIO_OFF(CaD,PortP-&gt;RxRemove);
macro_line|#endif
macro_line|#endif
macro_line|#else /* !IN_KERNEL */
DECL|macro|ZERO_PTR
mdefine_line|#define ZERO_PTR NULL
macro_line|#ifdef HOST
multiline_comment|/* #define can_remove_transmit(pkt,phb) ((((char*)pkt = (*(char**)(phb-&gt;tx_remove))-1) || 1)) &amp;&amp; (*phb-&gt;u3.s2.tx_remove_ptr &amp; PKT_IN_USE))   */
DECL|macro|remove_transmit
mdefine_line|#define remove_transmit(phb) *phb-&gt;u3.s2.tx_remove_ptr &amp;= ~(ushort)PKT_IN_USE;&bslash;&n;                             if (phb-&gt;tx_remove == phb-&gt;tx_end)&bslash;&n;                                phb-&gt;tx_remove = phb-&gt;tx_start;&bslash;&n;                             else&bslash;&n;                                phb-&gt;tx_remove++;
DECL|macro|can_add_receive
mdefine_line|#define can_add_receive(phb) !(*phb-&gt;u4.s2.rx_add_ptr &amp; PKT_IN_USE)
DECL|macro|add_receive
mdefine_line|#define add_receive(pkt,phb) *phb-&gt;rx_add = pkt;&bslash;&n;                             *phb-&gt;u4.s2.rx_add_ptr |= PKT_IN_USE;&bslash;&n;                             if (phb-&gt;rx_add == phb-&gt;rx_end)&bslash;&n;                                phb-&gt;rx_add = phb-&gt;rx_start;&bslash;&n;                             else&bslash;&n;                                phb-&gt;rx_add++;
macro_line|#endif
macro_line|#endif
macro_line|#ifdef RTA
DECL|macro|splx
mdefine_line|#define splx(oldspl)    if ((oldspl) == 0) spl0()
macro_line|#endif
macro_line|#endif /* ifndef _list.h */
multiline_comment|/*********** end of file ***********/
eof
