multiline_comment|/* $Id: eicon_pci.c,v 1.15.6.3 2001/09/23 22:24:37 kai Exp $&n; *&n; * ISDN low-level module for Eicon active ISDN-Cards.&n; * Hardware-specific code for PCI cards.&n; *&n; * Copyright 1998-2000 by Armin Schindler (mac@melware.de)&n; * Copyright 1999,2000 Cytronics &amp; Melware (info@melware.de)&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * Thanks to&t;Eicon Networks for &n; *&t;&t;documents, informations and hardware. &n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;eicon.h&quot;
macro_line|#include &quot;eicon_pci.h&quot;
DECL|macro|N_DATA
macro_line|#undef N_DATA
macro_line|#include &quot;adapter.h&quot;
macro_line|#include &quot;uxio.h&quot;
DECL|variable|eicon_pci_revision
r_char
op_star
id|eicon_pci_revision
op_assign
l_string|&quot;$Revision: 1.15.6.3 $&quot;
suffix:semicolon
macro_line|#if CONFIG_PCI&t;         /* intire stuff is only for PCI */
macro_line|#ifdef CONFIG_ISDN_DRV_EICON_PCI
DECL|function|eicon_pci_find_card
r_int
id|eicon_pci_find_card
c_func
(paren
r_char
op_star
id|ID
)paren
(brace
r_int
id|pci_cards
op_assign
l_int|0
suffix:semicolon
r_int
id|card_id
op_assign
l_int|0
suffix:semicolon
r_int
id|had_q
op_assign
l_int|0
suffix:semicolon
r_int
id|ctype
op_assign
l_int|0
suffix:semicolon
r_char
id|did
(braket
l_int|20
)braket
suffix:semicolon
id|card_t
op_star
id|pCard
suffix:semicolon
id|word
id|wCardIndex
suffix:semicolon
id|pCard
op_assign
id|DivasCards
suffix:semicolon
r_for
c_loop
(paren
id|wCardIndex
op_assign
l_int|0
suffix:semicolon
id|wCardIndex
OL
id|MAX_CARDS
suffix:semicolon
id|wCardIndex
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|pCard-&gt;hw
)paren
op_logical_and
(paren
id|pCard-&gt;hw-&gt;in_use
)paren
)paren
(brace
r_switch
c_cond
(paren
id|pCard-&gt;hw-&gt;card_type
)paren
(brace
r_case
id|DIA_CARD_TYPE_DIVA_SERVER
suffix:colon
id|ctype
op_assign
id|EICON_CTYPE_MAESTRAP
suffix:semicolon
id|card_id
op_increment
suffix:semicolon
id|had_q
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIA_CARD_TYPE_DIVA_SERVER_B
suffix:colon
id|ctype
op_assign
id|EICON_CTYPE_MAESTRA
suffix:semicolon
id|card_id
op_increment
suffix:semicolon
id|had_q
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIA_CARD_TYPE_DIVA_SERVER_Q
suffix:colon
id|ctype
op_assign
id|EICON_CTYPE_MAESTRAQ
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|had_q
)paren
id|card_id
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|had_q
op_ge
l_int|4
)paren
id|had_q
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;eicon_pci: unknown card type %d !&bslash;n&quot;
comma
id|pCard-&gt;hw-&gt;card_type
)paren
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|did
comma
l_string|&quot;%s%d&quot;
comma
(paren
id|strlen
c_func
(paren
id|ID
)paren
OL
l_int|1
)paren
ques
c_cond
l_string|&quot;eicon&quot;
suffix:colon
id|ID
comma
id|pci_cards
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|ctype
)paren
op_logical_or
(paren
op_logical_neg
(paren
id|eicon_addcard
c_func
(paren
id|ctype
comma
l_int|0
comma
id|pCard-&gt;hw-&gt;irq
comma
id|did
comma
id|card_id
)paren
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;eicon_pci: Card could not be added !&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|pci_cards
op_increment
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: DriverID=&squot;%s&squot; CardID=%d&bslash;n&quot;
comma
id|eicon_ctype_name
(braket
id|ctype
)braket
comma
id|did
comma
id|card_id
)paren
suffix:semicolon
)brace
id|err
suffix:colon
suffix:semicolon
)brace
id|pCard
op_increment
suffix:semicolon
)brace
r_return
id|pci_cards
suffix:semicolon
)brace
r_void
DECL|function|eicon_pci_init_conf
id|eicon_pci_init_conf
c_func
(paren
id|eicon_card
op_star
id|card
)paren
(brace
r_int
id|j
suffix:semicolon
multiline_comment|/* initializing some variables */
id|card-&gt;ReadyInt
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|256
suffix:semicolon
id|j
op_increment
)paren
(brace
id|card-&gt;IdTable
(braket
id|j
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
(paren
id|card-&gt;d-&gt;channels
op_plus
l_int|1
)paren
suffix:semicolon
id|j
op_increment
)paren
(brace
id|card-&gt;bch
(braket
id|j
)braket
dot
id|e.busy
op_assign
l_int|0
suffix:semicolon
id|card-&gt;bch
(braket
id|j
)braket
dot
id|e.D3Id
op_assign
l_int|0
suffix:semicolon
id|card-&gt;bch
(braket
id|j
)braket
dot
id|e.B2Id
op_assign
l_int|0
suffix:semicolon
id|card-&gt;bch
(braket
id|j
)braket
dot
id|e.ref
op_assign
l_int|0
suffix:semicolon
id|card-&gt;bch
(braket
id|j
)braket
dot
id|e.Req
op_assign
l_int|0
suffix:semicolon
id|card-&gt;bch
(braket
id|j
)braket
dot
id|e.complete
op_assign
l_int|1
suffix:semicolon
id|card-&gt;bch
(braket
id|j
)braket
dot
id|fsm_state
op_assign
id|EICON_STATE_NULL
suffix:semicolon
)brace
)brace
macro_line|#endif
macro_line|#endif&t;/* CONFIG_PCI */
eof
