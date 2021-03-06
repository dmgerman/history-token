multiline_comment|/*&n; * BRIEF MODULE DESCRIPTION&n; *&t;Galileo EV96100 reset routines.&n; *&n; * Copyright 2000 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; * This file was derived from Carsten Langgaard&squot;s&n; * arch/mips/mips-boards/generic/reset.c&n; *&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 1999,2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/gt64120.h&gt;
r_static
r_void
id|mips_machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
suffix:semicolon
r_static
r_void
id|mips_machine_halt
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|mips_machine_restart
r_static
r_void
id|mips_machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
(brace
id|set_c0_status
c_func
(paren
id|ST0_BEV
op_or
id|ST0_ERL
)paren
suffix:semicolon
id|change_c0_config
c_func
(paren
id|CONF_CM_CMASK
comma
id|CONF_CM_UNCACHED
)paren
suffix:semicolon
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|write_c0_wired
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;jr&bslash;t%0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
l_int|0xbfc00000
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|mips_machine_halt
r_static
r_void
id|mips_machine_halt
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;You can safely turn off the power&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
id|__asm__
c_func
(paren
l_string|&quot;.set&bslash;tmips3&bslash;n&bslash;t&quot;
l_string|&quot;wait&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tmips0&quot;
)paren
suffix:semicolon
)brace
DECL|function|mips_reboot_setup
r_void
id|mips_reboot_setup
c_func
(paren
r_void
)paren
(brace
id|_machine_restart
op_assign
id|mips_machine_restart
suffix:semicolon
id|_machine_halt
op_assign
id|mips_machine_halt
suffix:semicolon
)brace
eof
