multiline_comment|/*&n; * ipmi_kcs_sm.h&n; *&n; * State machine for handling IPMI KCS interfaces.&n; *&n; * Author: MontaVista Software, Inc.&n; *         Corey Minyard &lt;minyard@mvista.com&gt;&n; *         source@mvista.com&n; *&n; * Copyright 2002 MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; *&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,&n; *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS&n; *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND&n; *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n; *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n; *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
r_struct
id|kcs_data
suffix:semicolon
r_void
id|init_kcs_data
c_func
(paren
r_struct
id|kcs_data
op_star
id|kcs
comma
r_int
r_int
id|port
comma
r_int
r_char
op_star
id|addr
)paren
suffix:semicolon
multiline_comment|/* Start a new transaction in the state machine.  This will return -2&n;   if the state machine is not idle, -1 if the size is invalid (to&n;   large or too small), or 0 if the transaction is successfully&n;   completed. */
r_int
id|start_kcs_transaction
c_func
(paren
r_struct
id|kcs_data
op_star
id|kcs
comma
r_char
op_star
id|data
comma
r_int
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* Return the results after the transaction.  This will return -1 if&n;   the buffer is too small, zero if no transaction is present, or the&n;   actual length of the result data. */
r_int
id|kcs_get_result
c_func
(paren
r_struct
id|kcs_data
op_star
id|kcs
comma
r_int
r_char
op_star
id|data
comma
r_int
id|length
)paren
suffix:semicolon
DECL|enum|kcs_result
r_enum
id|kcs_result
(brace
DECL|enumerator|KCS_CALL_WITHOUT_DELAY
id|KCS_CALL_WITHOUT_DELAY
comma
multiline_comment|/* Call the driver again immediately */
DECL|enumerator|KCS_CALL_WITH_DELAY
id|KCS_CALL_WITH_DELAY
comma
multiline_comment|/* Delay some before calling again. */
DECL|enumerator|KCS_TRANSACTION_COMPLETE
id|KCS_TRANSACTION_COMPLETE
comma
multiline_comment|/* A transaction is finished. */
DECL|enumerator|KCS_SM_IDLE
id|KCS_SM_IDLE
comma
multiline_comment|/* The SM is in idle state. */
DECL|enumerator|KCS_SM_HOSED
id|KCS_SM_HOSED
comma
multiline_comment|/* The hardware violated the state machine. */
DECL|enumerator|KCS_ATTN
id|KCS_ATTN
multiline_comment|/* The hardware is asserting attn and the&n;&t;&t;&t;&t;   state machine is idle. */
)brace
suffix:semicolon
multiline_comment|/* Call this periodically (for a polled interface) or upon receiving&n;   an interrupt (for a interrupt-driven interface).  If interrupt&n;   driven, you should probably poll this periodically when not in idle&n;   state.  This should be called with the time that passed since the&n;   last call, if it is significant.  Time is in microseconds. */
r_enum
id|kcs_result
id|kcs_event
c_func
(paren
r_struct
id|kcs_data
op_star
id|kcs
comma
r_int
id|time
)paren
suffix:semicolon
multiline_comment|/* Return the size of the KCS structure in bytes. */
r_int
id|kcs_size
c_func
(paren
r_void
)paren
suffix:semicolon
eof
