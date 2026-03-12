#include<stdio.h>
#include<string.h>
#include"team.h"

//初始化球队，设置默认值
void init_teams(struct Team t[]){
	int i;
	for(i = 0; i < N; i++){
		sprintf(t[i].name, "球队%d", i + 1);		
		t[i].score = t[i].win = t[i].draw = t[i].lose = 0;
		t[i].goal = t[i].lose_goal = t[i].more_goal = 0;
	}
} 

//检查队名是否已存在（遍历
int check_name_exists(struct Team t[], char* name, int current){
	int i;
	for(i = 0; i < current; i++){
		if(strcmp(t[i].name, name) == 0){
			return 1;  //重复返回1
		}
	}
	return 0;  //不重复返回0
}

//用户输入队名（带检测
int input_team_names(struct Team t[]){
	char name[20];
	int i;
	
	printf("输入10支球队名称：\n");
	
	for(i = 0; i < N; i++){
		while(1){
			printf("第%d支：", i + 1);
			
			//读取整行输入
			if(fgets(name, sizeof(name), stdin) == NULL){
				printf("输入错误，请重新输入！\n");
				continue;
			} 
			
			//去掉换行符 
			name[strcspn(name,"\n")] = '\0';
			
			//检查是否为空 
			if(strlen(name) == 0){
				printf("队名不能为空，请重新输入！\n");
				continue;
			} 
			
			//检查是否与前面队名重复
			if(check_name_exists(t, name, i)){
				printf("队名重复，请输入不同的队名！\n");
				continue;
			}
			
			//名字有效，保存到数组
			strcpy(t[i].name, name);
			break; 
		}
	}
	return 1;
} 

//显示所有球队的编号
void show_team_list(struct Team t[]){
	int i;
	printf("\n球队编号\n");
	for(i = 0; i < N; i++){
		printf("%-2d -- %-10s\n", i + 1, t[i].name);
	} 
} 

//输入一场比赛带校验，返回1为成功，0失败
int input_one_match(struct Team t[], struct Match m[], int* match_cnt, int round, int match_num){
	int a, b, x, y; //队伍编号与进球数
	char input[50];
	
	while(1){
		printf("第%d场：", match_num);
		printf("输入 球队A编号 球队B编号 比分x:y:");
		
		//读取整行输入
		if(fgets(input,sizeof(input),stdin) == NULL){
			printf("输入错误！请重新输入\n");
			continue;
		} 
		
		//去掉换行符
		input[strcspn(input, "\n")] = '\0';
		
		//检查格式
		int parsed = sscanf(input, "%d%d%d:%d", &a, &b, &x, &y);
		if(parsed != 4){
			printf("格式错误！正确格式：球队A编号 球队B编号 比分x:比分y\n");
			continue; 
		} 
		
		//检查球队编号是否有效（1-10
		if(a < 1 || a > N || b < 1 || b > N){
			printf("球队编号无效！范围：1-%d\n", N);
			continue;
		} 
		
		//检查两支球队是否相同
		if(a == b){
			printf("错误：同一支球队不能比赛！\n");
			continue;
		} 
		
		//转下标
		a--;
		b--;
		 
		//检查A队是否在本轮已比赛
		if(is_team_in_round(m, *match_cnt, t[a].name, round)){
			printf("%s在本轮已经比赛过了！\n", t[a].name);
			continue;
		}
		
		//检查B队是否在本轮已比赛
		if(is_team_in_round(m, *match_cnt, t[b].name, round)){
			printf("%s在本轮已经比赛过了！\n", t[b].name);
			continue;
		}
		
		//检查两支球队是否已经比赛过
		if (is_match_exists(m, *match_cnt, t[a].name, t[b].name)) {
    		printf("这两支球队已经比赛过了！\n");
    		continue;
        }
		
		//更新球队数据
		team_data(t, a, b, x, y);
		
		//保存比赛记录
		m[*match_cnt].round = round;
		strcpy(m[*match_cnt].a_name, t[a].name);
		strcpy(m[*match_cnt].b_name, t[b].name);
		m[*match_cnt].a_goal = x;
		m[*match_cnt].b_goal = y;
		(*match_cnt)++;
		
		//显示比赛结果
		printf("  -> %s %d:%d %s\n",t[a].name, x, y, t[b].name);
		
		return 1; 
	} 
} 

//完成一轮比赛
void play_one_round(struct Team t[],struct Match m[], int* match_cnt, int round){
	int i;
	
	printf("\n==========第%d轮比赛==========\n",round);
	
	//输入5场比赛
	for(i = 0; i < 5; i++){
		input_one_match(t, m, match_cnt, round, i+1);
	} 
	
	//本轮比完后排序并显示积分榜
	show_rank(t); 
} 

//以下为原有函数 
//计算单场比赛后球队数据
void team_data(struct Team t[], int a, int b, int x, int y){
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

void show_rank(struct Team t[]) {
    int i, j;
    //创建名次数组
    int rank_idx[N];
    for (i = 0; i < N; i++) {
        rank_idx[i] = i;
    }

    // 第二步：冒泡排rank_idx数组
    // 分从高到低，积分相同看净胜球
    for (i = 0; i < N - 1; i++) {
        for (j = 0; j < N - 1; j++) {
            // 比较rank_idx里两个下标对应的球队积分
            int idx1 = rank_idx[j];   // 第j名对应的原始下标
            int idx2 = rank_idx[j+1]; // 第j+1名对应的原始下标
            // 积分低的往后排，积分相同则净胜球低的往后排
            if (t[idx1].score < t[idx2].score || 
                (t[idx1].score == t[idx2].score && t[idx1].more_goal < t[idx2].more_goal)) {
                // 只交换名次数组里的下标
                int temp = rank_idx[j];
                rank_idx[j] = rank_idx[j+1];
                rank_idx[j+1] = temp;
            }
        }
    }

    //显示排名，按名次数组找原始球队
    printf("%-4s %-6s %-10s %4s %4s %4s %4s %6s %6s %6s\n",
           "排名", "队伍编号", "队名", "积分", "胜", "平", "负", "进球", "失球", "净胜球");
    for (i = 0; i < 10; i++) {
        int idx = rank_idx[i]; // 找到当前排名对应的原始下标
        printf("%-4d %-6d %-10s %4d %4d %4d %4d %6d %6d %6d\n",
               i+1,          // 排名
               idx + 1,      // 球队原始编号
               t[idx].name,  // 队名
               t[idx].score, // 积分
               t[idx].win,   // 胜
               t[idx].draw,  // 平
               t[idx].lose,  // 负
               t[idx].goal,  // 进球
               t[idx].lose_goal, // 失球
               t[idx].more_goal); // 净胜球
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
	fprintf(fp, "%-4s %-12s %-12s %6s %6s\n", "轮次", "A队", "B队", "A进球", "B进球");
	printf("---------------------------------------------------------------\n");
    for (i = 0; i < cnt; i++) {
        fprintf(fp, "%-4d %-12s %-12s %6d %6d\n",
                m[i].round, m[i].a_name, m[i].b_name, m[i].a_goal, m[i].b_goal);
    }
    fclose(fp);
    printf("比分已保存到 matches.txt\n");
}

//检查两支球队是否已经比赛过
int is_match_exists(struct Match m[], int count, char* a_name, char* b_name) {
    int i;
    for (i = 0; i < count; i++) {
        if ((strcmp(m[i].a_name, a_name) == 0 && strcmp(m[i].b_name, b_name) == 0) ||
            (strcmp(m[i].a_name, b_name) == 0 && strcmp(m[i].b_name, a_name) == 0)) {
            return 1;
        }
    }
    return 0;
}

//检查某队是否在本轮比赛过 
int is_team_in_round(struct Match m[], int count, char* team_name, int round) {
    int i;
    for (i = 0; i < count; i++) {
        if (m[i].round == round) {
            if (strcmp(m[i].a_name, team_name) == 0 || strcmp(m[i].b_name, team_name) == 0) {
                return 1;
            }
        }
    }
    return 0;
}
