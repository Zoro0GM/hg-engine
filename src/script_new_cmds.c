#include "../include/constants/file.h"
#include "../include/repel.h"
#include "../include/script.h"
#include "../include/task.h"
#include "../include/types.h"

#define SCRIPT_NEW_CMD_REPEL_USE    0
#define SCRIPT_NEW_CMD_PLAYER_SHAKE 1

#define SCRIPT_NEW_CMD_MAX 256

typedef struct AnimPlayerShakeTreeWork {
    int timer;
} AnimPlayerShakeTreeWork;

BOOL LONG_CALL Task_AnimPlayerShakeTree(TaskManager *taskman);
void LONG_CALL TaskManager_Call(TaskManager *taskman, TaskFunc taskFunc, void *env);

BOOL Script_RunNewCmd(SCRIPTCONTEXT *ctx)
{
    u8 sw = ScriptReadByte(ctx);
    u16 UNUSED arg0 = ScriptReadHalfword(ctx);

    switch (sw) {
    case SCRIPT_NEW_CMD_REPEL_USE:;
#ifdef IMPLEMENT_REUSABLE_REPELS
        u16 most_recent_repel = Repel_GetMostRecent();
        SetScriptVar(arg0, most_recent_repel);
        Repel_Use(most_recent_repel, HEAPID_MAIN_HEAP);
#endif
        break;
    case SCRIPT_NEW_CMD_PLAYER_SHAKE:;
        AnimPlayerShakeTreeWork *env = sys_AllocMemoryLo(11, sizeof(AnimPlayerShakeTreeWork));
        MI_CpuClearFast(env, sizeof(AnimPlayerShakeTreeWork));
        TaskManager_Call(ctx->fsys->taskman, Task_AnimPlayerShakeTree, env);
        return TRUE;

    default:
        break;
    }

    return FALSE;
}
