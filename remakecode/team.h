#ifndef TEAM_H
#define TEAM_H

#define N 10 //10支球队
#define MAX_MATCHES 45 //最多45场比赛

//球队结构体 
struct Team{
	char name[20]; //球队名称
	int score; //积分
	int win,draw,lose;
	int goal,lose_goal;
	int more_goal;  //净胜球 
}; 


//每轮比分存储结构
struct Match{
	int round; //轮次
	char a_name[20]; //a队名
	char b_name[20]; //b队名
	int a_goal; //a队进球
	int b_goal; //b队进球 
};

//声明核心函数
void team_data(struct Team t[], int a, int b, int x, int y); //计算球队数据
void show_rank(struct Team t[]); //展示积分榜
void save_matches(struct Match m[], int cnt); //存储比分
void init_teams(struct Team t[]); //初始化球队
int check_name_exists(struct Team t[],char* name, int current); //检查队名是否重复
int input_team_names(struct Team t[]);//输入队名（带检测
void show_team_list(struct Team t[]);//显示球队编号列表 
int input_one_match(struct Team t[],struct Match m[], int* match_cnt, int round, int match_num); //输入一场比赛（有校验输入
void play_one_round(struct Team t[], struct Match m[], int* match_cnt,int round); //完成一轮比赛 
int is_match_exists(struct Match m[], int count, char* a_name, char* b_name); //检查比赛是否重复
int is_team_in_round(struct Match m[], int count, char* team_name, int round); //检查队伍是否在本轮已比赛

#endif 
