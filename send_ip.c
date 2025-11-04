//VERSION2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define TARGET_IP "172.20.10.101"
#define TARGET_PORT 12345

int main() {
    int sockfd;
    struct sockaddr_in dest_addr;
    char buffer[BUFFER_SIZE];

    // 创建 UDP 套接字
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        return 1;
    }

    // 设置目标地址
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(TARGET_PORT);
    inet_pton(AF_INET, TARGET_IP, &dest_addr.sin_addr);

    printf("UDP发送程序已启动\n");
    printf("输入消息 (输入 'quit' 退出):\n");

    while (1) {
        printf("> ");
        fflush(stdout);

        // 读取用户输入
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            break;
        }

        // 去除换行符
        buffer[strcspn(buffer, "\n")] = 0;

        // 检查退出条件
        if (strcmp(buffer, "quit") == 0) {
            printf("程序退出\n");
            break;
        }

        // 发送数据
        if (sendto(sockfd, buffer, strlen(buffer), 0,
            (struct sockaddr*)&dest_addr, sizeof(dest_addr)) < 0) {
            perror("sendto failed");
            break;
        }

        printf("消息已发送: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}