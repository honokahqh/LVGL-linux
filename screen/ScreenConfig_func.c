#include "ScreenConfig.h"

#define TAG "Screnn Config function"
#define MAX_OUTPUT_SIZE 1024
#define MAX_LINES 15
#define MAX_LINE_LENGTH 100
static void ExecuteCommandAndCaptureOutput(char *cmd, char *res) {
    FILE *fp;
    size_t totalRead = 0;

    // 初始化结果空间
    memset(res, 0, MAX_OUTPUT_SIZE);

    // 执行命令
    fp = popen(cmd, "r");
    if (fp == NULL) {
        strncpy(res, "Failed to run command\n", MAX_OUTPUT_SIZE - 1);
        return;
    }

    // 读取命令的输出并直接写入到提供的res空间中，最多读取MAX_OUTPUT_SIZE-1字节保证空间足够容纳字符串终结符'\0'
    while (fgets(res + totalRead, MAX_OUTPUT_SIZE - totalRead, fp) != NULL && totalRead < MAX_OUTPUT_SIZE - 1) {
        totalRead = strlen(res); // 更新已读取的总长度
        if (totalRead >= MAX_OUTPUT_SIZE - 1) break; // 如果达到最大容量，提前结束
    }

    // 关闭管道
    pclose(fp);
}

void UpdateLabelsFromCmdOutput(char *cmd, int labelNum) {
    static char line_data[MAX_LINES][MAX_LINE_LENGTH];
    static int line_index = 0;
    char output[MAX_OUTPUT_SIZE];
    char *line;
    char *next_line;
    lv_obj_t * labels[MAX_LINES] = {ui_ConfigLabelDebugMsg1, ui_ConfigLabelDebugMsg2, ui_ConfigLabelDebugMsg3, ui_ConfigLabelDebugMsg4
        , ui_ConfigLabelDebugMsg5, ui_ConfigLabelDebugMsg6, ui_ConfigLabelDebugMsg7, ui_ConfigLabelDebugMsg8, ui_ConfigLabelDebugMsg9
        , ui_ConfigLabelDebugMsg10, ui_ConfigLabelDebugMsg11, ui_ConfigLabelDebugMsg12, ui_ConfigLabelDebugMsg13, ui_ConfigLabelDebugMsg14
        , ui_ConfigLabelDebugMsg15};
    if(labelNum > MAX_LINES) {
        LOG_I(TAG, "%s label num overflow %d", __func__, labelNum);
    }
    if (line_index == 0)
        memset(line_data, 0, sizeof(line_data));
    // 执行命令并获取输出
    ExecuteCommandAndCaptureOutput(cmd, output);

    // 处理输出
    line = strtok_r(output, "\r\n", &next_line);
    while (line != NULL) {
        if (line_index < labelNum) {
            strncpy(line_data[line_index++], line, MAX_LINE_LENGTH - 1);
            line_data[line_index - 1][MAX_LINE_LENGTH - 1] = '\0'; // 确保字符串以'\0'结尾
        } else {
            // 移动行
            for (int i = 1; i < labelNum; i++) {
                strcpy(line_data[i - 1], line_data[i]);
            }
            // 更新最后一行
            strncpy(line_data[labelNum - 1], line, MAX_LINE_LENGTH - 1);
            line_data[labelNum - 1][MAX_LINE_LENGTH - 1] = '\0';
        }
        line = strtok_r(NULL, "\r\n", &next_line);
    }

    for (int i = 0; i < line_index && i < MAX_LINES; i++) {
        lv_label_set_text(labels[i], line_data[i]);
    }
}