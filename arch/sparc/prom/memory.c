multiline_comment|/* $Id: memory.c,v 1.15 2000/01/29 01:09:12 anton Exp $&n; * memory.c: Prom routine for acquiring various bits of information&n; *           about RAM on the machine, both virtual and physical.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1997 Michael A. Griffith (grif@acm.org)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/sun4prom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
multiline_comment|/* This routine, for consistency, returns the ram parameters in the&n; * V0 prom memory descriptor format.  I choose this format because I&n; * think it was the easiest to work with.  I feel the religious&n; * arguments now... ;)  Also, I return the linked lists sorted to&n; * prevent paging_init() upset stomach as I have not yet written&n; * the pepto-bismol kernel module yet.&n; */
DECL|variable|prom_reg_memlist
r_struct
id|linux_prom_registers
id|prom_reg_memlist
(braket
l_int|64
)braket
suffix:semicolon
DECL|variable|prom_reg_tmp
r_struct
id|linux_prom_registers
id|prom_reg_tmp
(braket
l_int|64
)braket
suffix:semicolon
DECL|variable|prom_phys_total
r_struct
id|linux_mlist_v0
id|prom_phys_total
(braket
l_int|64
)braket
suffix:semicolon
DECL|variable|prom_prom_taken
r_struct
id|linux_mlist_v0
id|prom_prom_taken
(braket
l_int|64
)braket
suffix:semicolon
DECL|variable|prom_phys_avail
r_struct
id|linux_mlist_v0
id|prom_phys_avail
(braket
l_int|64
)braket
suffix:semicolon
DECL|variable|prom_ptot_ptr
r_struct
id|linux_mlist_v0
op_star
id|prom_ptot_ptr
op_assign
id|prom_phys_total
suffix:semicolon
DECL|variable|prom_ptak_ptr
r_struct
id|linux_mlist_v0
op_star
id|prom_ptak_ptr
op_assign
id|prom_prom_taken
suffix:semicolon
DECL|variable|prom_pavl_ptr
r_struct
id|linux_mlist_v0
op_star
id|prom_pavl_ptr
op_assign
id|prom_phys_avail
suffix:semicolon
DECL|variable|prom_memlist
r_struct
id|linux_mem_v0
id|prom_memlist
suffix:semicolon
multiline_comment|/* Internal Prom library routine to sort a linux_mlist_v0 memory&n; * list.  Used below in initialization.&n; */
r_static
r_void
id|__init
DECL|function|prom_sortmemlist
id|prom_sortmemlist
c_func
(paren
r_struct
id|linux_mlist_v0
op_star
id|thislist
)paren
(brace
r_int
id|swapi
op_assign
l_int|0
suffix:semicolon
r_int
id|i
comma
id|mitr
comma
id|tmpsize
suffix:semicolon
r_char
op_star
id|tmpaddr
suffix:semicolon
r_char
op_star
id|lowest
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|thislist
(braket
id|i
)braket
dot
id|theres_more
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
id|lowest
op_assign
id|thislist
(braket
id|i
)braket
dot
id|start_adr
suffix:semicolon
r_for
c_loop
(paren
id|mitr
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
id|thislist
(braket
id|mitr
op_minus
l_int|1
)braket
dot
id|theres_more
op_ne
l_int|0
suffix:semicolon
id|mitr
op_increment
)paren
r_if
c_cond
(paren
id|thislist
(braket
id|mitr
)braket
dot
id|start_adr
OL
id|lowest
)paren
(brace
id|lowest
op_assign
id|thislist
(braket
id|mitr
)braket
dot
id|start_adr
suffix:semicolon
id|swapi
op_assign
id|mitr
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lowest
op_eq
id|thislist
(braket
id|i
)braket
dot
id|start_adr
)paren
(brace
r_continue
suffix:semicolon
)brace
id|tmpaddr
op_assign
id|thislist
(braket
id|swapi
)braket
dot
id|start_adr
suffix:semicolon
id|tmpsize
op_assign
id|thislist
(braket
id|swapi
)braket
dot
id|num_bytes
suffix:semicolon
r_for
c_loop
(paren
id|mitr
op_assign
id|swapi
suffix:semicolon
id|mitr
OG
id|i
suffix:semicolon
id|mitr
op_decrement
)paren
(brace
id|thislist
(braket
id|mitr
)braket
dot
id|start_adr
op_assign
id|thislist
(braket
id|mitr
op_minus
l_int|1
)braket
dot
id|start_adr
suffix:semicolon
id|thislist
(braket
id|mitr
)braket
dot
id|num_bytes
op_assign
id|thislist
(braket
id|mitr
op_minus
l_int|1
)braket
dot
id|num_bytes
suffix:semicolon
)brace
id|thislist
(braket
id|i
)braket
dot
id|start_adr
op_assign
id|tmpaddr
suffix:semicolon
id|thislist
(braket
id|i
)braket
dot
id|num_bytes
op_assign
id|tmpsize
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Initialize the memory lists based upon the prom version. */
DECL|function|prom_meminit
r_void
id|__init
id|prom_meminit
c_func
(paren
r_void
)paren
(brace
r_int
id|node
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|iter
comma
id|num_regs
suffix:semicolon
r_struct
id|linux_mlist_v0
op_star
id|mptr
suffix:semicolon
multiline_comment|/* ptr for traversal */
r_switch
c_cond
(paren
id|prom_vers
)paren
(brace
r_case
id|PROM_V0
suffix:colon
multiline_comment|/* Nice, kind of easier to do in this case. */
multiline_comment|/* First, the total physical descriptors. */
r_for
c_loop
(paren
id|mptr
op_assign
(paren
op_star
(paren
id|romvec-&gt;pv_v0mem.v0_totphys
)paren
)paren
comma
id|iter
op_assign
l_int|0
suffix:semicolon
id|mptr
suffix:semicolon
id|mptr
op_assign
id|mptr-&gt;theres_more
comma
id|iter
op_increment
)paren
(brace
id|prom_phys_total
(braket
id|iter
)braket
dot
id|start_adr
op_assign
id|mptr-&gt;start_adr
suffix:semicolon
id|prom_phys_total
(braket
id|iter
)braket
dot
id|num_bytes
op_assign
id|mptr-&gt;num_bytes
suffix:semicolon
id|prom_phys_total
(braket
id|iter
)braket
dot
id|theres_more
op_assign
op_amp
id|prom_phys_total
(braket
id|iter
op_plus
l_int|1
)braket
suffix:semicolon
)brace
id|prom_phys_total
(braket
id|iter
op_minus
l_int|1
)braket
dot
id|theres_more
op_assign
l_int|0x0
suffix:semicolon
multiline_comment|/* Second, the total prom taken descriptors. */
r_for
c_loop
(paren
id|mptr
op_assign
(paren
op_star
(paren
id|romvec-&gt;pv_v0mem.v0_prommap
)paren
)paren
comma
id|iter
op_assign
l_int|0
suffix:semicolon
id|mptr
suffix:semicolon
id|mptr
op_assign
id|mptr-&gt;theres_more
comma
id|iter
op_increment
)paren
(brace
id|prom_prom_taken
(braket
id|iter
)braket
dot
id|start_adr
op_assign
id|mptr-&gt;start_adr
suffix:semicolon
id|prom_prom_taken
(braket
id|iter
)braket
dot
id|num_bytes
op_assign
id|mptr-&gt;num_bytes
suffix:semicolon
id|prom_prom_taken
(braket
id|iter
)braket
dot
id|theres_more
op_assign
op_amp
id|prom_prom_taken
(braket
id|iter
op_plus
l_int|1
)braket
suffix:semicolon
)brace
id|prom_prom_taken
(braket
id|iter
op_minus
l_int|1
)braket
dot
id|theres_more
op_assign
l_int|0x0
suffix:semicolon
multiline_comment|/* Last, the available physical descriptors. */
r_for
c_loop
(paren
id|mptr
op_assign
(paren
op_star
(paren
id|romvec-&gt;pv_v0mem.v0_available
)paren
)paren
comma
id|iter
op_assign
l_int|0
suffix:semicolon
id|mptr
suffix:semicolon
id|mptr
op_assign
id|mptr-&gt;theres_more
comma
id|iter
op_increment
)paren
(brace
id|prom_phys_avail
(braket
id|iter
)braket
dot
id|start_adr
op_assign
id|mptr-&gt;start_adr
suffix:semicolon
id|prom_phys_avail
(braket
id|iter
)braket
dot
id|num_bytes
op_assign
id|mptr-&gt;num_bytes
suffix:semicolon
id|prom_phys_avail
(braket
id|iter
)braket
dot
id|theres_more
op_assign
op_amp
id|prom_phys_avail
(braket
id|iter
op_plus
l_int|1
)braket
suffix:semicolon
)brace
id|prom_phys_avail
(braket
id|iter
op_minus
l_int|1
)braket
dot
id|theres_more
op_assign
l_int|0x0
suffix:semicolon
multiline_comment|/* Sort all the lists. */
id|prom_sortmemlist
c_func
(paren
id|prom_phys_total
)paren
suffix:semicolon
id|prom_sortmemlist
c_func
(paren
id|prom_prom_taken
)paren
suffix:semicolon
id|prom_sortmemlist
c_func
(paren
id|prom_phys_avail
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PROM_V2
suffix:colon
r_case
id|PROM_V3
suffix:colon
multiline_comment|/* Grrr, have to traverse the prom device tree ;( */
id|node
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
id|node
op_assign
id|prom_searchsiblings
c_func
(paren
id|node
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|num_regs
op_assign
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;available&quot;
comma
(paren
r_char
op_star
)paren
id|prom_reg_memlist
comma
r_sizeof
(paren
id|prom_reg_memlist
)paren
)paren
suffix:semicolon
id|num_regs
op_assign
(paren
id|num_regs
op_div
r_sizeof
(paren
r_struct
id|linux_prom_registers
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|iter
op_assign
l_int|0
suffix:semicolon
id|iter
OL
id|num_regs
suffix:semicolon
id|iter
op_increment
)paren
(brace
id|prom_phys_avail
(braket
id|iter
)braket
dot
id|start_adr
op_assign
(paren
r_char
op_star
)paren
id|prom_reg_memlist
(braket
id|iter
)braket
dot
id|phys_addr
suffix:semicolon
id|prom_phys_avail
(braket
id|iter
)braket
dot
id|num_bytes
op_assign
(paren
r_int
r_int
)paren
id|prom_reg_memlist
(braket
id|iter
)braket
dot
id|reg_size
suffix:semicolon
id|prom_phys_avail
(braket
id|iter
)braket
dot
id|theres_more
op_assign
op_amp
id|prom_phys_avail
(braket
id|iter
op_plus
l_int|1
)braket
suffix:semicolon
)brace
id|prom_phys_avail
(braket
id|iter
op_minus
l_int|1
)braket
dot
id|theres_more
op_assign
l_int|0x0
suffix:semicolon
id|num_regs
op_assign
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;reg&quot;
comma
(paren
r_char
op_star
)paren
id|prom_reg_memlist
comma
r_sizeof
(paren
id|prom_reg_memlist
)paren
)paren
suffix:semicolon
id|num_regs
op_assign
(paren
id|num_regs
op_div
r_sizeof
(paren
r_struct
id|linux_prom_registers
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|iter
op_assign
l_int|0
suffix:semicolon
id|iter
OL
id|num_regs
suffix:semicolon
id|iter
op_increment
)paren
(brace
id|prom_phys_total
(braket
id|iter
)braket
dot
id|start_adr
op_assign
(paren
r_char
op_star
)paren
id|prom_reg_memlist
(braket
id|iter
)braket
dot
id|phys_addr
suffix:semicolon
id|prom_phys_total
(braket
id|iter
)braket
dot
id|num_bytes
op_assign
(paren
r_int
r_int
)paren
id|prom_reg_memlist
(braket
id|iter
)braket
dot
id|reg_size
suffix:semicolon
id|prom_phys_total
(braket
id|iter
)braket
dot
id|theres_more
op_assign
op_amp
id|prom_phys_total
(braket
id|iter
op_plus
l_int|1
)braket
suffix:semicolon
)brace
id|prom_phys_total
(braket
id|iter
op_minus
l_int|1
)braket
dot
id|theres_more
op_assign
l_int|0x0
suffix:semicolon
id|node
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
id|node
op_assign
id|prom_searchsiblings
c_func
(paren
id|node
comma
l_string|&quot;virtual-memory&quot;
)paren
suffix:semicolon
id|num_regs
op_assign
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;available&quot;
comma
(paren
r_char
op_star
)paren
id|prom_reg_memlist
comma
r_sizeof
(paren
id|prom_reg_memlist
)paren
)paren
suffix:semicolon
id|num_regs
op_assign
(paren
id|num_regs
op_div
r_sizeof
(paren
r_struct
id|linux_prom_registers
)paren
)paren
suffix:semicolon
multiline_comment|/* Convert available virtual areas to taken virtual&n;&t;&t; * areas.  First sort, then convert.&n;&t;&t; */
r_for
c_loop
(paren
id|iter
op_assign
l_int|0
suffix:semicolon
id|iter
OL
id|num_regs
suffix:semicolon
id|iter
op_increment
)paren
(brace
id|prom_prom_taken
(braket
id|iter
)braket
dot
id|start_adr
op_assign
(paren
r_char
op_star
)paren
id|prom_reg_memlist
(braket
id|iter
)braket
dot
id|phys_addr
suffix:semicolon
id|prom_prom_taken
(braket
id|iter
)braket
dot
id|num_bytes
op_assign
(paren
r_int
r_int
)paren
id|prom_reg_memlist
(braket
id|iter
)braket
dot
id|reg_size
suffix:semicolon
id|prom_prom_taken
(braket
id|iter
)braket
dot
id|theres_more
op_assign
op_amp
id|prom_prom_taken
(braket
id|iter
op_plus
l_int|1
)braket
suffix:semicolon
)brace
id|prom_prom_taken
(braket
id|iter
op_minus
l_int|1
)braket
dot
id|theres_more
op_assign
l_int|0x0
suffix:semicolon
id|prom_sortmemlist
c_func
(paren
id|prom_prom_taken
)paren
suffix:semicolon
multiline_comment|/* Finally, convert. */
r_for
c_loop
(paren
id|iter
op_assign
l_int|0
suffix:semicolon
id|iter
OL
id|num_regs
suffix:semicolon
id|iter
op_increment
)paren
(brace
id|prom_prom_taken
(braket
id|iter
)braket
dot
id|start_adr
op_assign
id|prom_prom_taken
(braket
id|iter
)braket
dot
id|start_adr
op_plus
id|prom_prom_taken
(braket
id|iter
)braket
dot
id|num_bytes
suffix:semicolon
id|prom_prom_taken
(braket
id|iter
)braket
dot
id|num_bytes
op_assign
id|prom_prom_taken
(braket
id|iter
op_plus
l_int|1
)braket
dot
id|start_adr
op_minus
id|prom_prom_taken
(braket
id|iter
)braket
dot
id|start_adr
suffix:semicolon
)brace
id|prom_prom_taken
(braket
id|iter
op_minus
l_int|1
)braket
dot
id|num_bytes
op_assign
l_int|0xffffffff
op_minus
(paren
r_int
r_int
)paren
id|prom_prom_taken
(braket
id|iter
op_minus
l_int|1
)braket
dot
id|start_adr
suffix:semicolon
multiline_comment|/* Sort the other two lists. */
id|prom_sortmemlist
c_func
(paren
id|prom_phys_total
)paren
suffix:semicolon
id|prom_sortmemlist
c_func
(paren
id|prom_phys_avail
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PROM_SUN4
suffix:colon
macro_line|#ifdef CONFIG_SUN4&t;
multiline_comment|/* how simple :) */
id|prom_phys_total
(braket
l_int|0
)braket
dot
id|start_adr
op_assign
l_int|0x0
suffix:semicolon
id|prom_phys_total
(braket
l_int|0
)braket
dot
id|num_bytes
op_assign
op_star
(paren
id|sun4_romvec-&gt;memorysize
)paren
suffix:semicolon
id|prom_phys_total
(braket
l_int|0
)braket
dot
id|theres_more
op_assign
l_int|0x0
suffix:semicolon
id|prom_prom_taken
(braket
l_int|0
)braket
dot
id|start_adr
op_assign
l_int|0x0
suffix:semicolon
id|prom_prom_taken
(braket
l_int|0
)braket
dot
id|num_bytes
op_assign
l_int|0x0
suffix:semicolon
id|prom_prom_taken
(braket
l_int|0
)braket
dot
id|theres_more
op_assign
l_int|0x0
suffix:semicolon
id|prom_phys_avail
(braket
l_int|0
)braket
dot
id|start_adr
op_assign
l_int|0x0
suffix:semicolon
id|prom_phys_avail
(braket
l_int|0
)braket
dot
id|num_bytes
op_assign
op_star
(paren
id|sun4_romvec-&gt;memoryavail
)paren
suffix:semicolon
id|prom_phys_avail
(braket
l_int|0
)braket
dot
id|theres_more
op_assign
l_int|0x0
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Link all the lists into the top-level descriptor. */
id|prom_memlist.v0_totphys
op_assign
op_amp
id|prom_ptot_ptr
suffix:semicolon
id|prom_memlist.v0_prommap
op_assign
op_amp
id|prom_ptak_ptr
suffix:semicolon
id|prom_memlist.v0_available
op_assign
op_amp
id|prom_pavl_ptr
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* This returns a pointer to our libraries internal v0 format&n; * memory descriptor.&n; */
r_struct
id|linux_mem_v0
op_star
DECL|function|prom_meminfo
id|prom_meminfo
c_func
(paren
r_void
)paren
(brace
r_return
op_amp
id|prom_memlist
suffix:semicolon
)brace
eof
