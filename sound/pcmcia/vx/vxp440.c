DECL|macro|COMPILE_VXP440
mdefine_line|#define COMPILE_VXP440
multiline_comment|/*&n; add the following as /etc/pcmcia/vxp440.conf:&n;&n;  device &quot;snd-vxp440&quot;&n;    class &quot;audio&quot; module &quot;snd-vxp440&quot;&n;&n;  card &quot;Digigram VX-POCKET440&quot;&n;    manfid 0x01f1, 0x0100&n;    bind &quot;snd-vxp440&quot;&n;*/
macro_line|#include &quot;vxpocket.c&quot;
eof
