#include "Debug.h"
#include "string.h"
#include "stdio.h"
#include <stdarg.h>
#include "usart.h"
#include <stdlib.h>
#include <stdbool.h>
#include "oled.h"
#include "font.h"
#include "pid.h"

uint8_t sofa_data[50];
uint8_t camera_data[50];
int stop_flag = 0;


float parse_float_from_uart(const uint8_t* data, uint16_t length) {
    // 最小有效数据长度检查 (P1= + 1个数字字符 + !#+ = 8字节)
    if (length < 8) return 0.0f / 0.0f; // 返回NaN表示错误

    // 验证起始标记
    if (strncmp((char*)data, "@P1=", 4) != 0 && strncmp((char*)data, "@I1=", 4) != 0 && strncmp((char*)data, "@D1=", 4) != 0) {
        return 0.0f / 0.0f; // 起始标记错误，返回NaN
    }

    // 查找结束标记
    const uint8_t* end_ptr = data + 4; // 从数字部分开始搜索
    bool end_marker_found = false;

    // 在剩余数据中搜索结束标记
    for (uint16_t i = 4; i < length - 2; i++) {
        if (data[i] == '!' && data[i+1] == '#' && data[i+2] == '+') {
            end_ptr = &data[i];
            end_marker_found = true;
            break;
        }
    }

    if (!end_marker_found) return 0.0f / 0.0f; // 结束标记未找到

    // 计算数字部分长度
    uint16_t num_len = end_ptr - (data + 4);
    if (num_len == 0) return 0.0f / 0.0f; // 无数字内容

    // 创建临时缓冲区存放数字字符串
    char num_str[32]; // 足够存放长浮点数
    if (num_len >= sizeof(num_str)) {
        return 0.0f / 0.0f; // 数字部分过长
    }

    memcpy(num_str, data + 4, num_len);
    num_str[num_len] = '\0'; // 添加终止符

    // 验证数字格式 (可选但推荐)
    for (uint16_t i = 0; i < num_len; i++) {
        char c = num_str[i];
        if (!((c >= '0' && c <= '9') || c == '.' || c == '-' || c == '+')) {
            return 0.0f / 0.0f; // 非法字符
        }
    }

    // 转换为浮点数
    char* end_parse;
    float value = strtof(num_str, &end_parse);

    // 检查是否整个字符串都被转换
    if (end_parse != num_str + num_len) {
        return 0.0f / 0.0f; // 转换不完全
    }

    return value;
}



void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
    // if (huart == &huart1) {
    //     OLED_NewFrame();
    //     if (huart==&huart1){
    //         if (Size==10){
    //             if (camera_data[0]==0xA5 && camera_data[1]==0xA6 &&camera_data[9]==0x5B){
    //                 int data1=camera_data[2]+camera_data[3]+camera_data[4]+camera_data[5];
    //                 int data2=camera_data[5]+camera_data[6]+camera_data[7]+camera_data[8];
    //                 if (data2>data1){
    //                     OLED_PrintString(30, 30,"turn_right",&font16x16,OLED_COLOR_NORMAL);
    //                 }
    //                 else if(data2<data1){
    //                     OLED_PrintString(30, 30, "turn_left", &font16x16, OLED_COLOR_NORMAL);
    //                 }
    //                 else if(data2==0){
    //                     OLED_PrintString(30, 30, "no way", &font16x16, OLED_COLOR_NORMAL);
    //                 }
    //                 else{
    //                     OLED_PrintString(30, 30, "go ahead", &font16x16, OLED_COLOR_NORMAL);
    //                 }
    //             }
    //         }
    //         else if(Size==4){
    //             if (camera_data[0]==0xA5 && camera_data[1]==0xA6 &&camera_data[3]==0x5B){
    //                 int t=camera_data[2];
    //                 if(t==1){
    //                     OLED_PrintString(30, 30,"stop",&font16x16,OLED_COLOR_NORMAL);
    //                     stop_flag = 1;
    //                 }
    //                 else{
    //                     OLED_PrintString(30, 30,"go_ahead",&font16x16,OLED_COLOR_NORMAL);
    //
    //                 }
    //             }
    //         }
    //         OLED_ShowFrame();
    //         ///HAL_UART_Receive_DMA(&huart1, receivedata1, sizeof(receivedata1));
    //         HAL_UARTEx_ReceiveToIdle_DMA(&huart1, camera_data, sizeof(camera_data));
    //     }
    // }
    if (huart == &huart1){
    const uint8_t second = sofa_data[1];
    const uint8_t third = sofa_data[2];
    float value;
    if(second == 'P' && third == '1')
    {
        value = parse_float_from_uart(sofa_data,(uint16_t)strlen(sofa_data));
        angle_ring.kp = value;
    }
    else if(second == 'I' && third == '1')
    {
        value = parse_float_from_uart(sofa_data,(uint16_t)strlen(sofa_data));
        angle_ring.ki = value;
    }
    else if(second == 'D' && third == '1')
    {
        value = parse_float_from_uart(sofa_data,(uint16_t)strlen(sofa_data));
        angle_ring.kd = value;
    }
    else if(second == 'P' && third == 'l')
    {
        value = parse_float_from_uart(sofa_data,(uint16_t)strlen(sofa_data));
        speed_ring_l.kp = value;
    }
    else if(second == 'I' && third == 'l')
    {
        value = parse_float_from_uart(sofa_data,(uint16_t)strlen(sofa_data));
        speed_ring_l.ki = value;
    }
    else if(second == 'D' && third == 'l')
    {
        value = parse_float_from_uart(sofa_data,(uint16_t)strlen(sofa_data));
        speed_ring_l.kd = value;
    }
    else if(second == 'P' && third == 'r')
    {
        value = parse_float_from_uart(sofa_data,(uint16_t)strlen(sofa_data));
        speed_ring_r.kp = value;
    }
    else if(second == 'I' && third == 'r')
    {
        value = parse_float_from_uart(sofa_data,(uint16_t)strlen(sofa_data));
        speed_ring_r.ki = value;
    }
    else if(second == 'D' && third == 'r')
    {
        value = parse_float_from_uart(sofa_data,(uint16_t)strlen(sofa_data));
        speed_ring_r.kd = value;
    }
    else if(sofa_data[0] == 0)
    {
        ring_mode = 0;
    }
    else if(sofa_data[0] == 1)
    {
        ring_mode = 1;
    }
    else if(sofa_data[0] == 2)
    {
        ring_mode = 2;
    }
    else if(sofa_data[0] == 3)
    {
        ring_mode = 3;
    }
    HAL_UARTEx_ReceiveToIdle_IT(&huart1, sofa_data, sizeof(sofa_data));
    }
}



void UART_Printf(UART_HandleTypeDef *huart,const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[64];  // 减小缓冲区
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    if(len > 0 && len < sizeof(buffer)) {
        HAL_UART_Transmit( huart, (uint8_t*)buffer, len,100);
    }
}
//void UART_Printf(const char *format, ...) {
//    va_list args;
//    va_start(args, format);
//    char buffer[64];  // 减小缓冲区
//    int len = vsnprintf(buffer, sizeof(buffer), format, args);
//    va_end(args);
//
//    if(len > 0 && len < sizeof(buffer)) {
//        HAL_UART_Transmit(&huart1, (uint8_t*)buffer, len, 100);
//    }
//}








