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
	
	//新增规则
	printf("【比赛规则】\n");
	printf("  队名：不能重复，长度1-19个字符\n");
	printf("  比赛：不能输入相同队伍比赛，两支队伍不能重复比赛");
	printf("  积分：胜3分，平1分，负0分\n");
	printf("  排名：积分 > 净胜球 > 进球\n");
	printf("  输入：球队A 球队B 比分A:比分B（可用编号或队名）\n");
 
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
