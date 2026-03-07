#include<stdio.h>
#include<string.h>
#include"team.h"


//计算单场比赛后球队数据
void team_data(struct Team t[], int a, int b, int x, int y){
	a--;
	b--; //均转为下标
	//更新进球/失球/净胜球
	t[a].goal += x; 
	t[a].lose_goal += y;
    t[b].goal += y; 
	t[b].lose_goal += x;
    t[a].more_goal = t[a].goal - t[a].lose_goal;
    t[b].more_goal = t[b].goal - t[b].lose_goal;
    //更新积分/胜负平
	if (x > y) { 
		t[a].score +=3; t[a].win++; t[b].lose++; 
	}
    else if (x < y) { 
		t[b].score +=3; t[b].win++; t[a].lose++;
	}
    else { 
		t[a].score++; t[b].score++; t[a].draw++; t[b].draw++; 
	}
}
//排序（积分-净胜球-进球）
void sort_team(struct Team t[]) {
    int i, j;
    struct Team temp;
    for (i = 0; i < N-1; i++) {
        for (j = i+1; j < N; j++) {
            if (t[j].score > t[i].score || 
                (t[j].score == t[i].score && t[j].more_goal > t[i].more_goal) ||
                (t[j].score == t[i].score && t[j].more_goal == t[i].more_goal && t[j].goal > t[i].goal)) {
                temp = t[i]; t[i] = t[j]; t[j] = temp;
            }
        }
    }
}
//展示积分榜
void show_rank(struct Team t[]) {
    int i;
    printf("\n========== 积分榜 =========\n");
    printf("%-4s %-10s %6s %4s %4s %4s %6s %6s %8s\n",
           "排名", "队名", "积分", "胜", "平", "负", "进球", "失球", "净胜球");
    printf("----------------------------------------------------------------\n");
    for (i = 0; i < N; i++) {
        printf("%-4d %-10s %6d %4d %4d %4d %6d %6d %8d\n",i + 1, t[i].name, t[i].score, t[i].win, t[i].draw,t[i].lose, t[i].goal, t[i].lose_goal, t[i].more_goal);
    }
}
//存储每轮比分到文件
void save_matches(struct Match m[], int cnt){
	int i;
	FILE*fp = fopen("matches.txt","w");
	if(!fp){
		printf("保存失败！\n");
		return;
	}
	fprintf(fp, "%-6s%-8s%-8s%6s%6s\n","轮次","a队","b队","a进球","b进球");
    for (i = 0; i < cnt; i++) {
        fprintf(fp, "%-2d  %-8s %-8s   %3d     %3d\n",
                m[i].round, m[i].a_name, m[i].b_name, m[i].a_goal, m[i].b_goal);
    }
    fclose(fp);
    printf("比分已保存到 matches.txt\n");
} 

