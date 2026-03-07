#include <stdio.h>
#include <string.h>
#include "team.h"

int main() {
    struct Team team[N];       // 球队数据（局部变量）
    struct Match matches[MAX_MATCHES]; // 比分记录（局部变量）
    int match_cnt = 0;         // 场次计数（局部变量）
    int i, round, a, b, x, y;

    // 1. 初始化球队
    for (i = 0; i < N; i++) {
        sprintf(team[i].name, "球队%d", i+1);
        team[i].score = team[i].win = team[i].draw = team[i].lose = 0;
        team[i].goal = team[i].lose_goal = team[i].more_goal = 0;
    }

    // 2. 输入球队名称
    printf("输入10支球队名称：\n");
    for (i = 0; i < N; i++) {
        printf("第%d支：", i+1);
        scanf("%s", team[i].name);
    }

    // 3. 显示球队编号
    printf("\n球队编号：\n");
    for (i = 0; i < N; i++) printf("%d -- %s\n", i+1, team[i].name);

    // 4. 录入9轮比赛（每轮5场）
    for (round = 1; round <= 9; round++) {
        printf("\n==== 第%d轮比赛 ====\n", round);
        for (i = 0; i < 5; i++) {
        	printf("\n第%d场：", i+1);
            printf("输入 球队A 球队B 比分x:y：");
            scanf("%d%d%d%d", &a, &b, &x, &y);
            
            // 计算球队数据
            team_data(team, a, b, x, y);
            
            // 存储本轮比分
            a--; b--;
            matches[match_cnt].round = round;
            strcpy(matches[match_cnt].a_name, team[a].name);
            strcpy(matches[match_cnt].b_name, team[b].name);
            matches[match_cnt].a_goal = x;
            matches[match_cnt].b_goal = y;
            match_cnt++;
        }
        // 每轮结束展示积分榜
        sort_team(team);
        show_rank(team);
    }

    // 5. 最终展示+存储比分
    printf("\n==== 最终积分榜 ====\n");
    show_rank(team);
    save_matches(matches, match_cnt);

    return 0;
}
