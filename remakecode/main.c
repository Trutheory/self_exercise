#include <stdio.h>
#include <string.h>
#include "team.h"

int main() {
    struct Team team[N];       // 球队数据
    struct Match matches[MAX_MATCHES]; // 比分记录
    int match_cnt = 0;         // 场次计数
    int i, round;

    // 1. 初始化球队
    init_teams(team);

    // 2. 输入球队名称
    input_team_names(team);

    // 3. 显示球队编号
    show_team_list(team);
    
    //新增清空输入缓冲避免回车影响输入
	int c;
	while((c = getchar()) != '\n' && c != EOF); 

    // 4. 录入9轮比赛（每轮5场）
    for (round = 1; round <= 9; round++) {
       play_one_round(team, matches, &match_cnt, round);
    }

    // 5. 最终展示+存储比分
    printf("\n============ 最终积分榜 ============\n");
    show_rank(team);
    show_rank(team);
    save_matches(matches, match_cnt);

    return 0;
}
