multiline_comment|/*&n; *    Disk Array driver for Compaq SMART2 Controllers&n; *    Copyright 1998 Compaq Computer Corporation&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2 of the License, or&n; *    (at your option) any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; *    NON INFRINGEMENT.  See the GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *    Questions/Comments/Bugfixes to iss_storagedev@hp.com&n; *&n; *    If you want to make changes, improve or add functionality to this&n; *    driver, you&squot;ll probably need the Compaq Array Controller Interface&n; *    Specificiation (Document number ECG086/1198)&n; */
multiline_comment|/*&n; * This file contains the controller communication implementation for&n; * Compaq SMART-1 and SMART-2 controllers.  To the best of my knowledge,&n; * this should support:&n; *&n; *  PCI:&n; *  SMART-2/P, SMART-2DH, SMART-2SL, SMART-221, SMART-3100ES, SMART-3200&n; *  Integerated SMART Array Controller, SMART-4200, SMART-4250ES&n; *&n; *  EISA:&n; *  SMART-2/E, SMART, IAES, IDA-2, IDA&n; */
multiline_comment|/*&n; * Memory mapped FIFO interface (SMART 42xx cards)&n; */
DECL|function|smart4_submit_command
r_static
r_void
id|smart4_submit_command
c_func
(paren
id|ctlr_info_t
op_star
id|h
comma
id|cmdlist_t
op_star
id|c
)paren
(brace
id|writel
c_func
(paren
id|c-&gt;busaddr
comma
id|h-&gt;vaddr
op_plus
id|S42XX_REQUEST_PORT_OFFSET
)paren
suffix:semicolon
)brace
multiline_comment|/*  &n; *  This card is the opposite of the other cards.  &n; *   0 turns interrupts on... &n; *   0x08 turns them off... &n; */
DECL|function|smart4_intr_mask
r_static
r_void
id|smart4_intr_mask
c_func
(paren
id|ctlr_info_t
op_star
id|h
comma
r_int
r_int
id|val
)paren
(brace
r_if
c_cond
(paren
id|val
)paren
(brace
multiline_comment|/* Turn interrupts on */
id|writel
c_func
(paren
l_int|0
comma
id|h-&gt;vaddr
op_plus
id|S42XX_REPLY_INTR_MASK_OFFSET
)paren
suffix:semicolon
)brace
r_else
multiline_comment|/* Turn them off */
(brace
id|writel
c_func
(paren
id|S42XX_INTR_OFF
comma
id|h-&gt;vaddr
op_plus
id|S42XX_REPLY_INTR_MASK_OFFSET
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  For older cards FIFO Full = 0. &n; *  On this card 0 means there is room, anything else FIFO Full. &n; * &n; */
DECL|function|smart4_fifo_full
r_static
r_int
r_int
id|smart4_fifo_full
c_func
(paren
id|ctlr_info_t
op_star
id|h
)paren
(brace
r_return
(paren
op_logical_neg
id|readl
c_func
(paren
id|h-&gt;vaddr
op_plus
id|S42XX_REQUEST_PORT_OFFSET
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* This type of controller returns -1 if the fifo is empty, &n; *    Not 0 like the others.&n; *    And we need to let it know we read a value out &n; */
DECL|function|smart4_completed
r_static
r_int
r_int
id|smart4_completed
c_func
(paren
id|ctlr_info_t
op_star
id|h
)paren
(brace
r_int
id|register_value
op_assign
id|readl
c_func
(paren
id|h-&gt;vaddr
op_plus
id|S42XX_REPLY_PORT_OFFSET
)paren
suffix:semicolon
multiline_comment|/* Fifo is empty */
r_if
c_cond
(paren
id|register_value
op_eq
l_int|0xffffffff
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Need to let it know we got the reply */
multiline_comment|/* We do this by writing a 0 to the port we just read from */
id|writel
c_func
(paren
l_int|0
comma
id|h-&gt;vaddr
op_plus
id|S42XX_REPLY_PORT_OFFSET
)paren
suffix:semicolon
r_return
(paren
(paren
r_int
r_int
)paren
id|register_value
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  This hardware returns interrupt pending at a different place and &n; *  it does not tell us if the fifo is empty, we will have check  &n; *  that by getting a 0 back from the comamnd_completed call. &n; */
DECL|function|smart4_intr_pending
r_static
r_int
r_int
id|smart4_intr_pending
c_func
(paren
id|ctlr_info_t
op_star
id|h
)paren
(brace
r_int
r_int
id|register_value
op_assign
id|readl
c_func
(paren
id|h-&gt;vaddr
op_plus
id|S42XX_INTR_STATUS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_value
op_amp
id|S42XX_INTR_PENDING
)paren
(brace
r_return
id|FIFO_NOT_EMPTY
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|smart4_access
r_static
r_struct
id|access_method
id|smart4_access
op_assign
(brace
id|smart4_submit_command
comma
id|smart4_intr_mask
comma
id|smart4_fifo_full
comma
id|smart4_intr_pending
comma
id|smart4_completed
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Memory mapped FIFO interface (PCI SMART2 and SMART 3xxx cards)&n; */
DECL|function|smart2_submit_command
r_static
r_void
id|smart2_submit_command
c_func
(paren
id|ctlr_info_t
op_star
id|h
comma
id|cmdlist_t
op_star
id|c
)paren
(brace
id|writel
c_func
(paren
id|c-&gt;busaddr
comma
id|h-&gt;vaddr
op_plus
id|COMMAND_FIFO
)paren
suffix:semicolon
)brace
DECL|function|smart2_intr_mask
r_static
r_void
id|smart2_intr_mask
c_func
(paren
id|ctlr_info_t
op_star
id|h
comma
r_int
r_int
id|val
)paren
(brace
id|writel
c_func
(paren
id|val
comma
id|h-&gt;vaddr
op_plus
id|INTR_MASK
)paren
suffix:semicolon
)brace
DECL|function|smart2_fifo_full
r_static
r_int
r_int
id|smart2_fifo_full
c_func
(paren
id|ctlr_info_t
op_star
id|h
)paren
(brace
r_return
id|readl
c_func
(paren
id|h-&gt;vaddr
op_plus
id|COMMAND_FIFO
)paren
suffix:semicolon
)brace
DECL|function|smart2_completed
r_static
r_int
r_int
id|smart2_completed
c_func
(paren
id|ctlr_info_t
op_star
id|h
)paren
(brace
r_return
id|readl
c_func
(paren
id|h-&gt;vaddr
op_plus
id|COMMAND_COMPLETE_FIFO
)paren
suffix:semicolon
)brace
DECL|function|smart2_intr_pending
r_static
r_int
r_int
id|smart2_intr_pending
c_func
(paren
id|ctlr_info_t
op_star
id|h
)paren
(brace
r_return
id|readl
c_func
(paren
id|h-&gt;vaddr
op_plus
id|INTR_PENDING
)paren
suffix:semicolon
)brace
DECL|variable|smart2_access
r_static
r_struct
id|access_method
id|smart2_access
op_assign
(brace
id|smart2_submit_command
comma
id|smart2_intr_mask
comma
id|smart2_fifo_full
comma
id|smart2_intr_pending
comma
id|smart2_completed
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *  IO access for SMART-2/E cards&n; */
DECL|function|smart2e_submit_command
r_static
r_void
id|smart2e_submit_command
c_func
(paren
id|ctlr_info_t
op_star
id|h
comma
id|cmdlist_t
op_star
id|c
)paren
(brace
id|outl
c_func
(paren
id|c-&gt;busaddr
comma
id|h-&gt;io_mem_addr
op_plus
id|COMMAND_FIFO
)paren
suffix:semicolon
)brace
DECL|function|smart2e_intr_mask
r_static
r_void
id|smart2e_intr_mask
c_func
(paren
id|ctlr_info_t
op_star
id|h
comma
r_int
r_int
id|val
)paren
(brace
id|outl
c_func
(paren
id|val
comma
id|h-&gt;io_mem_addr
op_plus
id|INTR_MASK
)paren
suffix:semicolon
)brace
DECL|function|smart2e_fifo_full
r_static
r_int
r_int
id|smart2e_fifo_full
c_func
(paren
id|ctlr_info_t
op_star
id|h
)paren
(brace
r_return
id|inl
c_func
(paren
id|h-&gt;io_mem_addr
op_plus
id|COMMAND_FIFO
)paren
suffix:semicolon
)brace
DECL|function|smart2e_completed
r_static
r_int
r_int
id|smart2e_completed
c_func
(paren
id|ctlr_info_t
op_star
id|h
)paren
(brace
r_return
id|inl
c_func
(paren
id|h-&gt;io_mem_addr
op_plus
id|COMMAND_COMPLETE_FIFO
)paren
suffix:semicolon
)brace
DECL|function|smart2e_intr_pending
r_static
r_int
r_int
id|smart2e_intr_pending
c_func
(paren
id|ctlr_info_t
op_star
id|h
)paren
(brace
r_return
id|inl
c_func
(paren
id|h-&gt;io_mem_addr
op_plus
id|INTR_PENDING
)paren
suffix:semicolon
)brace
DECL|variable|smart2e_access
r_static
r_struct
id|access_method
id|smart2e_access
op_assign
(brace
id|smart2e_submit_command
comma
id|smart2e_intr_mask
comma
id|smart2e_fifo_full
comma
id|smart2e_intr_pending
comma
id|smart2e_completed
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *  IO access for older SMART-1 type cards&n; */
DECL|macro|SMART1_SYSTEM_MASK
mdefine_line|#define SMART1_SYSTEM_MASK&t;&t;0xC8E
DECL|macro|SMART1_SYSTEM_DOORBELL
mdefine_line|#define SMART1_SYSTEM_DOORBELL&t;&t;0xC8F
DECL|macro|SMART1_LOCAL_MASK
mdefine_line|#define SMART1_LOCAL_MASK&t;&t;0xC8C
DECL|macro|SMART1_LOCAL_DOORBELL
mdefine_line|#define SMART1_LOCAL_DOORBELL&t;&t;0xC8D
DECL|macro|SMART1_INTR_MASK
mdefine_line|#define SMART1_INTR_MASK&t;&t;0xC89
DECL|macro|SMART1_LISTADDR
mdefine_line|#define SMART1_LISTADDR&t;&t;&t;0xC90
DECL|macro|SMART1_LISTLEN
mdefine_line|#define SMART1_LISTLEN&t;&t;&t;0xC94
DECL|macro|SMART1_TAG
mdefine_line|#define SMART1_TAG&t;&t;&t;0xC97
DECL|macro|SMART1_COMPLETE_ADDR
mdefine_line|#define SMART1_COMPLETE_ADDR&t;&t;0xC98
DECL|macro|SMART1_LISTSTATUS
mdefine_line|#define SMART1_LISTSTATUS&t;&t;0xC9E
DECL|macro|CHANNEL_BUSY
mdefine_line|#define CHANNEL_BUSY&t;&t;&t;0x01
DECL|macro|CHANNEL_CLEAR
mdefine_line|#define CHANNEL_CLEAR&t;&t;&t;0x02
DECL|function|smart1_submit_command
r_static
r_void
id|smart1_submit_command
c_func
(paren
id|ctlr_info_t
op_star
id|h
comma
id|cmdlist_t
op_star
id|c
)paren
(brace
multiline_comment|/*&n;&t; * This __u16 is actually a bunch of control flags on SMART&n;&t; * and below.  We want them all to be zero.&n;&t; */
id|c-&gt;hdr.size
op_assign
l_int|0
suffix:semicolon
id|outb
c_func
(paren
id|CHANNEL_CLEAR
comma
id|h-&gt;io_mem_addr
op_plus
id|SMART1_SYSTEM_DOORBELL
)paren
suffix:semicolon
id|outl
c_func
(paren
id|c-&gt;busaddr
comma
id|h-&gt;io_mem_addr
op_plus
id|SMART1_LISTADDR
)paren
suffix:semicolon
id|outw
c_func
(paren
id|c-&gt;size
comma
id|h-&gt;io_mem_addr
op_plus
id|SMART1_LISTLEN
)paren
suffix:semicolon
id|outb
c_func
(paren
id|CHANNEL_BUSY
comma
id|h-&gt;io_mem_addr
op_plus
id|SMART1_LOCAL_DOORBELL
)paren
suffix:semicolon
)brace
DECL|function|smart1_intr_mask
r_static
r_void
id|smart1_intr_mask
c_func
(paren
id|ctlr_info_t
op_star
id|h
comma
r_int
r_int
id|val
)paren
(brace
r_if
c_cond
(paren
id|val
op_eq
l_int|1
)paren
(brace
id|outb
c_func
(paren
l_int|0xFD
comma
id|h-&gt;io_mem_addr
op_plus
id|SMART1_SYSTEM_DOORBELL
)paren
suffix:semicolon
id|outb
c_func
(paren
id|CHANNEL_BUSY
comma
id|h-&gt;io_mem_addr
op_plus
id|SMART1_LOCAL_DOORBELL
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x01
comma
id|h-&gt;io_mem_addr
op_plus
id|SMART1_INTR_MASK
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x01
comma
id|h-&gt;io_mem_addr
op_plus
id|SMART1_SYSTEM_MASK
)paren
suffix:semicolon
)brace
r_else
(brace
id|outb
c_func
(paren
l_int|0
comma
id|h-&gt;io_mem_addr
op_plus
l_int|0xC8E
)paren
suffix:semicolon
)brace
)brace
DECL|function|smart1_fifo_full
r_static
r_int
r_int
id|smart1_fifo_full
c_func
(paren
id|ctlr_info_t
op_star
id|h
)paren
(brace
r_int
r_char
id|chan
suffix:semicolon
id|chan
op_assign
id|inb
c_func
(paren
id|h-&gt;io_mem_addr
op_plus
id|SMART1_SYSTEM_DOORBELL
)paren
op_amp
id|CHANNEL_CLEAR
suffix:semicolon
r_return
id|chan
suffix:semicolon
)brace
DECL|function|smart1_completed
r_static
r_int
r_int
id|smart1_completed
c_func
(paren
id|ctlr_info_t
op_star
id|h
)paren
(brace
r_int
r_char
id|status
suffix:semicolon
r_int
r_int
id|cmd
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|h-&gt;io_mem_addr
op_plus
id|SMART1_SYSTEM_DOORBELL
)paren
op_amp
id|CHANNEL_BUSY
)paren
(brace
id|outb
c_func
(paren
id|CHANNEL_BUSY
comma
id|h-&gt;io_mem_addr
op_plus
id|SMART1_SYSTEM_DOORBELL
)paren
suffix:semicolon
id|cmd
op_assign
id|inl
c_func
(paren
id|h-&gt;io_mem_addr
op_plus
id|SMART1_COMPLETE_ADDR
)paren
suffix:semicolon
id|status
op_assign
id|inb
c_func
(paren
id|h-&gt;io_mem_addr
op_plus
id|SMART1_LISTSTATUS
)paren
suffix:semicolon
id|outb
c_func
(paren
id|CHANNEL_CLEAR
comma
id|h-&gt;io_mem_addr
op_plus
id|SMART1_LOCAL_DOORBELL
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * this is x86 (actually compaq x86) only, so it&squot;s ok&n;&t;&t; */
r_if
c_cond
(paren
id|cmd
)paren
(paren
(paren
id|cmdlist_t
op_star
)paren
id|bus_to_virt
c_func
(paren
id|cmd
)paren
)paren
op_member_access_from_pointer
id|req.hdr.rcode
op_assign
id|status
suffix:semicolon
)brace
r_else
(brace
id|cmd
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|cmd
suffix:semicolon
)brace
DECL|function|smart1_intr_pending
r_static
r_int
r_int
id|smart1_intr_pending
c_func
(paren
id|ctlr_info_t
op_star
id|h
)paren
(brace
r_int
r_char
id|chan
suffix:semicolon
id|chan
op_assign
id|inb
c_func
(paren
id|h-&gt;io_mem_addr
op_plus
id|SMART1_SYSTEM_DOORBELL
)paren
op_amp
id|CHANNEL_BUSY
suffix:semicolon
r_return
id|chan
suffix:semicolon
)brace
DECL|variable|smart1_access
r_static
r_struct
id|access_method
id|smart1_access
op_assign
(brace
id|smart1_submit_command
comma
id|smart1_intr_mask
comma
id|smart1_fifo_full
comma
id|smart1_intr_pending
comma
id|smart1_completed
comma
)brace
suffix:semicolon
eof
