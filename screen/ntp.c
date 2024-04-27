#include "ntp.h"
#include <stdbool.h>

volatile bool keepRunning = true; // 控制线程循环的全局标志

void *syn_ntp_time(void) {
    while(keepRunning) {
        char* servers[] = {"time.windows.com", "ntp.aliyun.com", "pool.ntp.org"};
        int num_servers = sizeof(servers) / sizeof(servers[0]);

        for (int i = 0; i < num_servers && keepRunning; i++) {
            char command[256];
            snprintf(command, sizeof(command), "sntp -s %s", servers[i]);
            // if (system(command) == 0) {
            //     break; // 假设如果命令执行成功，则退出循环
            // }
        }
        for(int i = 0; i < 3600 && keepRunning; i++) {
            sleep(1); // 睡眠，但每秒检查一次是否应该停止
        }
    }
    return NULL;
}
