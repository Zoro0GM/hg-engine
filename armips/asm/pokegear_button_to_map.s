.nds
.thumb

// Code is by AdAstra

.open "base/arm9.bin", 0x02000000

COMMONSCRIPT_ID equ 2509

// make pokegear button open map instead of pokegear
.org 0x02000000 + 0x3D500

push {r4, lr}
mov r4, r0
ldr r1, =COMMONSCRIPT_ID
mov r2, #0
mov r3, #0
bl #0x203FED4 // QueueScript
ldr r1,[r4,#0xc] // inline TaskManager_GetEnvironment
mov r0, #15
strh r0, [r1, 0x26] // state
mov r0, #1
pop {r4, pc} // return TRUE
.pool
.close
