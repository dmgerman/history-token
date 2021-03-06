multiline_comment|/*&n; * linux/drivers/s390/net/qeth_mpc.c&n; *&n; * Linux on zSeries OSA Express and HiperSockets support&n; *&n; * Copyright 2000,2003 IBM Corporation&n; * Author(s): Frank Pavlic &lt;pavlic@de.ibm.com&gt;&n; * &t;      Thomas Spatzier &lt;tspat@de.ibm.com&gt;&n; *&n; */
macro_line|#include &lt;asm/cio.h&gt;
macro_line|#include &quot;qeth_mpc.h&quot;
DECL|variable|VERSION_QETH_MPC_C
r_const
r_char
op_star
id|VERSION_QETH_MPC_C
op_assign
l_string|&quot;$Revision: 1.11 $&quot;
suffix:semicolon
DECL|variable|IDX_ACTIVATE_READ
r_int
r_char
id|IDX_ACTIVATE_READ
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|IDX_ACTIVATE_WRITE
r_int
r_char
id|IDX_ACTIVATE_WRITE
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|CM_ENABLE
r_int
r_char
id|CM_ENABLE
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|CM_SETUP
r_int
r_char
id|CM_SETUP
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|ULP_ENABLE
r_int
r_char
id|ULP_ENABLE
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|ULP_SETUP
r_int
r_char
id|ULP_SETUP
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|DM_ACT
r_int
r_char
id|DM_ACT
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|IPA_PDU_HEADER
r_int
r_char
id|IPA_PDU_HEADER
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|WRITE_CCW
r_int
r_char
id|WRITE_CCW
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|READ_CCW
r_int
r_char
id|READ_CCW
(braket
)braket
op_assign
initialization_block
suffix:semicolon
eof
