#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <sys/select.h>
#include <net/if.h>
#include "lvgl_ScreenConfig.h"

#define TAG "net link"

void handle_event(struct nlmsghdr *nlh);
void *net_link_thread(void);

void handle_event(struct nlmsghdr *nlh) {
    struct ifinfomsg *ifi = (struct ifinfomsg *)NLMSG_DATA(nlh);
    if (nlh->nlmsg_type == RTM_NEWLINK) {
        if (ifi->ifi_flags & 0x40) {
            LOG_I(TAG, "Network interface %d is up\n", ifi->ifi_index);
            lv_label_set_text(ui_MainIconWiFi,"有");
            lv_obj_set_style_text_color(ui_MainIconWiFi, lv_color_hex(0xCDCDCD), LV_PART_MAIN | LV_STATE_DEFAULT );
        } else {
            LOG_E(TAG, "Network interface %d is down\n", ifi->ifi_index);
            lv_label_set_text(ui_MainIconWiFi,"无");
            lv_obj_set_style_text_color(ui_MainIconWiFi, lv_color_hex(0xC20404), LV_PART_MAIN | LV_STATE_DEFAULT );
        }
    } else if (nlh->nlmsg_type == RTM_DELLINK) {
        LOG_E(TAG, "Network interface %d is down\n", ifi->ifi_index);
    }
}

void *net_link_thread(void) {
    int sock_fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (sock_fd < 0) {
        perror("Cannot create netlink socket:");
        return -1;
    }

    struct sockaddr_nl sa;
    memset(&sa, 0, sizeof(sa));
    sa.nl_family = AF_NETLINK;
    sa.nl_groups = RTMGRP_LINK;

    if (bind(sock_fd, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
        perror("Cannot bind netlink socket:");
        close(sock_fd);
        return -1;
    }

    while (1) {
        fd_set fds;
        struct timeval tv;
        int ret;

        FD_ZERO(&fds);
        FD_SET(sock_fd, &fds);

        // 设置超时为0.5秒
        tv.tv_sec = 0;
        tv.tv_usec = 500000; // 500000 微秒 = 0.5秒

        ret = select(sock_fd + 1, &fds, NULL, NULL, &tv);
        if (ret < 0) {
            perror("select");
            break;
        } else if (ret == 0) {
            // 超时，没有事件，继续循环
            continue;
        }

        if (FD_ISSET(sock_fd, &fds)) {
            // 有从内核发来的消息
            char buffer[4096];
            int length = recv(sock_fd, buffer, sizeof(buffer), 0);
            if (length < 0) {
                perror("recv");
                continue;
            }

            for (struct nlmsghdr *nlh = (struct nlmsghdr *)buffer; 
                 NLMSG_OK(nlh, length); 
                 nlh = NLMSG_NEXT(nlh, length)) {
                handle_event(nlh);
            }
        }
        
        // 这里不再需要 usleep(500000); 因为 select 已经处理了等待
    }

    close(sock_fd);
    return 0;
}
