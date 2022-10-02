#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>;
#include<stdlib.h>;
#include<string.h>;
// 存储航班最大容量
#define MAXSIZE 200
#define MAXSTR 30

//定义plane结构体类型
typedef struct plane {
	char plane_id[MAXSTR];		//航班号
	char start[MAXSTR];			//起点站
	char end[MAXSTR];			//终点站
	char time_start[MAXSTR];	//起飞时间
	char time_end[MAXSTR];		//到达时间
	char mode1[MAXSTR];			//机型
	int price;					//票价
	int tickets;				//票量
}Plane;

//定义顺序表L保存航班信息
struct PlaneList {
	Plane plane[MAXSIZE];
	int length;
}L;

//Ticket类型
typedef struct ticket {
	char plane_id[MAXSTR];		//航班id	
	int num;					//票数
}Ticket;
//用户类型
typedef struct user {
	char name[MAXSTR];			//用户姓名
	char phone[MAXSTR];			//手机号码
	Ticket tickets[MAXSTR];		//航班
	int lenght;					//航班数
}User;
//定义用户
User user;

//初始化用户
void InitUser() {
	strcpy(user.name, "张三");
	strcpy(user.phone, "100000");
}
//登录系统
int Login_System() {
	int login_id = 0;
	int flag = 0;
	int isExit = 0;
	//初始账号密码
	char user_id[9] = "z";
	char password_user[9] = "123456";
	char password_manager[9] = "000000";

	while (!isExit) {
		char id[9], password[9];
		system("cls");
		printf("默认账号为：z\n");
		printf("默认学生密码为：123456\n");
		printf("默认管理员密码：000000\n\n");
		printf("  —————————- 欢迎使用图书系统 -—————————\n");
		printf("\t\t\t输入 1 登录\n");
		printf("\t\t\t else 退出\n");
		isExit = 1;
		scanf("%d", &flag);
		if (flag != 1) {
			return 0;
		}
		//8位账号和密码，最后一个位置填入终止符
		id[8] = '\0';
		password[8] = '\0';

		printf("\n----请输入账号----\n");
		scanf("%s", id);
		printf("----请输入密码----\n");
		scanf("%s", password);

		//判断系统
		if (strcmp(user_id, id) == 0 && strcmp(password, password_user) == 0) {
			login_id = 1;//用户系统
			break;
		}
		if (strcmp(user_id, id) == 0 && strcmp(password, password_manager) == 0) {
			login_id = 2;//管理员系统
			break;
		}

		if (!login_id) {
			printf("账号或密码输入错误\n\n");
			printf("\t\t———— 错误 ————\n");
			printf("\t\t     输入 0 重试\n");
			printf("\t\t      else 退出\n");
			scanf("%d", &isExit);
		}
	}
	return login_id;
}
//菜单页面,含用户和管理员
void ShowMenu(int login_id) {
	if (login_id == 1) {
		printf("\t\t\t    ———————- 用户菜单 ———————-\n");
		printf("\t\t\t\t ╔════════════════════════════╗\n");
		printf("\t\t\t\t ║     1-查询       2-列表    ║\n");
		printf("\t\t\t\t ║	  		      ║\n");
		printf("\t\t\t\t ║     3-订票       4-退票    ║\n");
		printf("\t\t\t\t ║	  		      ║\n");
		printf("\t\t\t\t ║     5-排序       6-订单    ║\n");
		printf("\t\t\t\t ║    	     0-退出	      ║\n");
		printf("\t\t\t\t ╚════════════════════════════╝\n");
	}
	else {
		printf("\t\t\t   ———————- 管理员菜单 ———————-\n");
		printf("\t\t\t\t ╔════════════════════════════╗\n");
		printf("\t\t\t\t ║     1-录入       2-查询    ║\n");
		printf("\t\t\t\t ║	  		      ║\n");
		printf("\t\t\t\t ║     3-删除       4-修改    ║\n");
		printf("\t\t\t\t ║	  		      ║\n");
		printf("\t\t\t\t ║     5-列表       6-排序    ║\n");
		printf("\t\t\t\t ║    	     0-退出	      ║\n");
		printf("\t\t\t\t ╚════════════════════════════╝\n");
	}
	printf("请选择功能: ");
}
//保存信息至文件
void SaveInfo() {
	int i;
	//写入航班信息
	FILE* fp = fopen("plane.txt", "w+");
	if (!fp) {
		printf("打开plane.txt文件失败，请检查!\n");
		return;
	}
	for (i = 0; i < L.length; i++) {
		if (fprintf(fp, "%s %s %s %s %s %s %d %d\n", L.plane[i].plane_id, L.plane[i].start, L.plane[i].end, \
			L.plane[i].time_start, L.plane[i].time_end, L.plane[i].mode1, L.plane[i].price, L.plane[i].tickets) == EOF) {
			fclose(fp);
			printf("写入plane.txt文件失败，请检查！\n");
		}
	}
	fflush(stdin);
	if (fclose(fp) == EOF) {
		printf("关闭plane.txt文件失败，请检查！\n");
		return;
	}

	//写入用户购票信息
	fp = fopen("user.txt", "w+");
	if (!fp) {
		printf("打开user.txt文件失败\n");
		return;
	}
	for (i = 0; i < user.lenght; i++) {
		fprintf(fp, "%s %d ", user.tickets[i].plane_id, user.tickets[i].num);
	}
	fflush(stdin);
	if (fclose(fp) == EOF) {
		printf("关闭user.txt文件失败，请检查！\n");
		return;
	}
}
//于文件读取信息
void ReadInfo()
{
	FILE* fp = fopen("plane.txt", "a+");
	int i;
	if (!fp) {
		printf("打开plane.txt文件失败\n");
		return;
	}
	//按行读入航班信息
	for (i = 0; i < MAXSIZE; i++) {
		if (fscanf(fp, "%s%s%s%s%s%s%d%d\n", L.plane[i].plane_id, L.plane[i].start, L.plane[i].end, \
			L.plane[i].time_start, L.plane[i].time_end, L.plane[i].mode1, &L.plane[i].price, &L.plane[i].tickets) == EOF)
			break;
	}
	L.length = i;//保存长度
	if (fclose(fp) == EOF) {
		printf("关闭plane.txt文件失败，请检查！\n");
	}

	//读入用户订单信息
	fp = fopen("user.txt", "a+");
	if (!fp) {
		printf("打开文件失败\n");
		return;
	}
	for (i = 0; i < MAXSTR; i++) {
		if (fscanf(fp, "%s %d ", user.tickets[i].plane_id, &user.tickets[i].num) == EOF) {
			break;
		}
	}
	user.lenght = i;
	if (fclose(fp) == EOF) {
		printf("关闭user.txt文件失败，请检查！\n");
		return;
	}
	printf("读取文件成功\n");
}
//显示航班信息
void ShowInfo(int i) {
	printf(" %-12s%-11s%-16s%-18s\t%-17s\t%-16s%-10d%-10d\n", L.plane[i].plane_id, L.plane[i].start, L.plane[i].end, \
		L.plane[i].time_start, L.plane[i].time_end, L.plane[i].mode1, L.plane[i].price, L.plane[i].tickets);
}
//显示航班列表
void ShowList() {
	system("cls");
	int i;
	if (!L.length) {
		printf("无航班信息\n");
	}
	else {
		printf("航班信息列表\n");
		printf("════════════════════════════════════════════════════════");
		printf("════════════════════════════════════════════════════════════\n");
		printf("航班号\t    起点站\t终点站\t\t起飞时间\t\t到达时间\t\t机型\t\t票价\t票数\n\n");
		for (i = 0; i < L.length; i++) {
			printf("--------------------------------------------------------------------------------------------------------------------\n");
			ShowInfo(i);
		}
		printf("════════════════════════════════════════════════════════");
		printf("════════════════════════════════════════════════════════════\n");
	}
}
//录入航班
void AddPlane() {
	int ch;
	int hasExist = 0;
	system("cls");
	printf("\t\t\t——————- 录入 -——————\n");
	printf("\t\t\t\t     1 录入\n");
	printf("\t\t\t\t   else 返回\n");
	printf("请选择: ");
	scanf("%d", &ch);
	if (ch == 1) {
		if (L.length >= MAXSIZE) {
			printf("抱歉，容量已满,无法增加图书\n");
			return;
		}
		int len = L.length;
		printf("请按照提示添加航班信息：\n");
		printf("请输入航班号: ");
		scanf("%s", L.plane[len].plane_id);
		// 判断航班号是否已经存在
		for (int i = 0; i < len; i++) {
			if (strcmp(L.plane[len].plane_id, L.plane[i].plane_id) == 0) {
				hasExist = 1;
				break;
			}
		}
		if (hasExist == 1) {
			printf("该航班号已经存在，无法录入\n");
			return;
		}
		printf("请输入起点站: ");
		scanf("%s", L.plane[len].start);
		printf("请输入终点站: ");
		scanf("%s", L.plane[len].end);
		printf("请输入起飞时间: ");
		scanf("%s", L.plane[len].time_start);
		printf("请输入到达时间: ");
		scanf("%s", L.plane[len].time_end);
		printf("请输入机型: ");
		scanf("%s", L.plane[len].mode1);
		printf("请输入票价: ");
		scanf("%d", &L.plane[len].price);
		printf("请输入票数: ");
		scanf("%d", &L.plane[len].tickets);
		L.length++;
		SaveInfo();//保存信息至文件
		printf("录入成功，当前共有%d趟航班\n", L.length);
	}
}
//查询航班
void QueryPlane() {
	int i;
	int isExit = 0, hasExist = 0, flag;
	char plane_id[MAXSTR], start[MAXSTR], end[MAXSTR], time_start[MAXSTR], time_end[MAXSTR];

	while (!isExit)
	{
		system("cls");
		printf("\t\t\t—————- 查找方式 -—————\n");
		printf("\t\t\t\t   1.航班号\n");
		printf("\t\t\t\t   2.起点站\n");
		printf("\t\t\t\t   3.终点站\n");
		printf("\t\t\t\t   4.起飞时间(日期)\n");
		printf("\t\t\t\t   5.到达时间(日期)\n");
		printf("\t\t\t\t   6.返  回\n");
		isExit = 1;
		hasExist = 0;
		printf("请选择查找方式: ");
		scanf("%d", &flag);

		switch (flag)
		{
		case 1:
			printf("请输入航班号\n");
			plane_id[MAXSTR - 1] = '\0';
			scanf("%s", plane_id);

			for (i = 0; i < L.length; i++) {
				if (strcmp(L.plane[i].plane_id, plane_id) == 0)
				{
					printf("航班 %s 信息如下:\n", plane_id);
					printf("════════════════════════════════════════════════════════");
					printf("════════════════════════════════════════════════════════════\n");
					printf("航班号\t    起点站\t终点站\t\t起飞时间\t\t到达时间\t\t机型\t\t票价\t票数\n\n");
					ShowInfo(i);
					printf("════════════════════════════════════════════════════════");
					printf("════════════════════════════════════════════════════════════\n");
					hasExist = 1;
					break;
				}
			}
			break;
		case 2:
			printf("请输入起点站\n");
			start[MAXSTR - 1] = '\0';
			scanf("%s", start);

			for (i = 0; i < L.length; i++) {
				if (strcmp(L.plane[i].start, start) == 0)
				{
					if (!hasExist) {
						printf("起点站为  %s 的航班信息如下:\n", start);
						printf("════════════════════════════════════════════════════════");
						printf("════════════════════════════════════════════════════════════\n");
						printf("航班号\t    起点站\t终点站\t\t起飞时间\t\t到达时间\t\t机型\t\t票价\t票数\n\n");
					}
					ShowInfo(i);
					hasExist = 1;
				}
			}
			if (hasExist) {
				printf("════════════════════════════════════════════════════════");
				printf("════════════════════════════════════════════════════════════\n");
			}
			break;
		case 3:
			printf("请输入终点站\n");
			end[MAXSTR - 1] = '\0';
			scanf("%s", end);
			for (i = 0; i < L.length; i++) {
				if (strcmp(L.plane[i].end, end) == 0)
				{
					if (!hasExist) {
						printf("终点站为 %s 的航班信息如下:\n", end);
						printf("════════════════════════════════════════════════════════");
						printf("════════════════════════════════════════════════════════════\n");
						printf("航班号\t    起点站\t终点站\t\t起飞时间\t\t到达时间\t\t机型\t\t票价\t票数\n\n");
					}
					ShowInfo(i);
					hasExist = 1;
				}
			}
			if (hasExist) {
				printf("════════════════════════════════════════════════════════");
				printf("════════════════════════════════════════════════════════════\n");
			}
			break;
		case 4:
			printf("请输入起飞时间\n");
			//格式为XXXX-XX-XX
			time_start[10] = '\0';
			scanf("%s", time_start);
			for (i = 0; i < L.length; i++) {
				int isSameTime = 1;
				for (int j = 0; j < 10; j++) {
					if (L.plane[i].time_start[j] != time_start[j]) {
						isSameTime = 0;
					}
				}
				if (isSameTime)
				{
					if (!hasExist) {
						printf("起飞时间为 %s 的航班信息如下:\n", time_start);
						printf("════════════════════════════════════════════════════════");
						printf("════════════════════════════════════════════════════════════\n");
						printf("航班号\t    起点站\t终点站\t\t起飞时间\t\t到达时间\t\t机型\t\t票价\t票数\n\n");
					}
					hasExist = 1;
					ShowInfo(i);
				}
			}
			if (hasExist) {
				printf("════════════════════════════════════════════════════════");
				printf("════════════════════════════════════════════════════════════\n");
			}
			break;
		case 5:
			printf("请输入到达时间\n");
			//格式为XXXX-XX-XX
			time_end[10] = '\0';
			scanf("%s", time_end);
			for (i = 0; i < L.length; i++) {
				int isSameTime = 1;
				for (int j = 0; j < 10; j++) {
					if (L.plane[i].time_end[j] != time_end[j]) {
						isSameTime = 0;
					}
				}
				if (isSameTime)
				{
					if (!hasExist) {
						printf("起飞时间为 %s 的航班信息如下:\n", time_end);
						printf("════════════════════════════════════════════════════════");
						printf("════════════════════════════════════════════════════════════\n");
						printf("航班号\t    起点站\t终点站\t\t起飞时间\t\t到达时间\t\t机型\t\t票价\t票数\n\n");
					}
					hasExist = 1;
					ShowInfo(i);
				}
			}
			if (hasExist) {
				printf("════════════════════════════════════════════════════════");
				printf("════════════════════════════════════════════════════════════\n");
			}
			break;
		case 6:
			hasExist = 1;
			break;
		default:
			isExit = 0;
			hasExist = 1;
			printf("输入错误，请重新输入\n");
			system("pause");
		}

		//查找失败
		if (!hasExist) {
			system("cls");
			printf("没有查找到航班信息\n");
			printf("\t\t\t  ————— 失败 —————\n");
			printf("\t\t\t\t   输入0查找\n");
			printf("\t\t\t\t   else 返回\n");
			printf("请选择: ");
			scanf("%d", &isExit);
		}
	}
}
//排序功能
void SortPlane() {
	int i, j;
	int flag, isExit = 0, hasSort;
	//选择排序法
	while (!isExit) {
		system("cls");
		isExit = 1;
		hasSort = 1;
		printf("\t\t\t  ——————排序方式——————\n");
		printf("\t\t\t\t    1.航  班\n");
		printf("\t\t\t\t    2.票  价\n");
		printf("\t\t\t\t    3.起飞时间\n");
		printf("\t\t\t\t    4.返  回\n");
		printf("请选择排序方式:");
		scanf("%d", &flag);
		fflush(stdin);
		switch (flag) {
		case 1:
			for (i = 0; i < L.length - 1; i++) {
				int min = i;
				for (j = i + 1; j < L.length; j++) {
					if (strcmp(L.plane[j].plane_id, L.plane[min].plane_id) < 0) {
						min = j;
					}
				}
				//交换
				if (min != i)
				{
					Plane temp = L.plane[i];
					L.plane[i] = L.plane[min];
					L.plane[min] = temp;
				}
			}
			break;
		case 2:
			for (i = 0; i < L.length - 1; i++) {
				int min = i;
				for (j = i + 1; j < L.length; j++) {
					if (L.plane[j].price < L.plane[min].price) {
						min = j;
					}
				}
				//交换
				if (min != i)
				{
					Plane temp = L.plane[i];
					L.plane[i] = L.plane[min];
					L.plane[min] = temp;
				}
			}
			break;
		case 3:
			for (i = 0; i < L.length - 1; i++) {
				int min = i;
				for (j = i + 1; j < L.length; j++) {
					if (strcmp(L.plane[j].time_start, L.plane[min].time_start) < 0) {
						min = j;
					}
				}
				//交换
				if (min != i)
				{
					Plane temp = L.plane[i];
					L.plane[i] = L.plane[min];
					L.plane[min] = temp;
				}
			}
			break;
		case 4:
			hasSort = 0;
			break;
		default:
			isExit = 0;
			printf("输入错误，请重新输入\n");
			system("pause");
		}
	}
	if (hasSort) {
		ShowList();
		SaveInfo();
	}

}
//删除航班
void DeletePlane() {
	int i, flag, isExit = 0;
	char ch;
	char plane_id[MAXSTR];
	plane_id[MAXSTR - 1] = '\0';
	while (!isExit) {
		system("cls");
		isExit = 1;
		printf("\t\t\t  —————— 删除 ———————\n");
		printf("\t\t\t\t   1.显示列表\n");
		printf("\t\t\t\t   2.删除航班\n");
		printf("\t\t\t\t   3.返    回\n");
		printf("请选择 : ");
		scanf("%d", &flag);

		switch (flag) {
		case 1:
			//显示列表
			ShowList();
		case 2:
			printf("请输入航班号: ");
			scanf("%s", plane_id);
			for (i = 0; i < L.length; i++) {
				if (strcmp(L.plane[i].plane_id, plane_id) == 0)
				{
					printf("════════════════════════════════════════════════════════");
					printf("════════════════════════════════════════════════════════════\n");
					printf("航班号\t    起点站\t终点站\t\t起飞时间\t\t到达时间\t\t机型\t\t票价\t票数\n\n");
					ShowInfo(i);
					printf("════════════════════════════════════════════════════════");
					printf("════════════════════════════════════════════════════════════\n");
					break;
				}
			}
			if (i >= L.length) {
				printf("\n\n没有找到该航班号\n");
				isExit = 0;
				system("pause");
				break;
			}
			printf("输入 Y 确定删除\n");
			scanf(" %c", &ch);
			//进行删除，从指定位置开始，后一个元素赋给前一个元素
			if (ch == 'y' || ch == 'Y') {
				while (i < L.length - 1) {
					L.plane[i] = L.plane[i + 1];
					++i;
				}
				L.length--;
				SaveInfo();
				printf("删除成功,当前共有%d趟航班\n", L.length);
			}
			break;

		case 3:
			break;
		default:
			isExit = 0;
			printf("输入错误，请重新输入\n");
			system("pause");
		}
	}
}
//菜单---修改信息
void Menu_Updata() {//显示修改项目 

	printf("\t\t\t\t═════════ 修改航班信息═════════\n");
	printf("\t\t\t\t                    \n");
	printf("\t\t\t\t   --------1.航班号------\n");
	printf("\t\t\t\t                    \n");
	printf("\t\t\t\t   --------2.起点站------\n");
	printf("\t\t\t\t                    \n");
	printf("\t\t\t\t   --------3.终点站------\n");
	printf("\t\t\t\t                    \n");
	printf("\t\t\t\t   --------4.起飞时间----\n");
	printf("\t\t\t\t                    \n");
	printf("\t\t\t\t   --------5.到达时间----\n");
	printf("\t\t\t\t                    \n");
	printf("\t\t\t\t   --------6.机型--------\n");
	printf("\t\t\t\t                    \n");
	printf("\t\t\t\t   --------7.票价--------\n");
	printf("\t\t\t\t                    \n");
	printf("\t\t\t\t   --------8.票数--------\n");
	printf("\t\t\t\t                    \n");
	printf("\t\t\t\t   --------9.退出--------\n");
	printf("\t\t\t\t                    \n");
	printf("\t\t\t\t══════════════════════════════\n");
}
//修改指定航班信息
int UpdataInfo(int index) {
	int updata_id;
	int hasUpdata = 0;
	int isExit = 0;
	while (!isExit)
	{
		printf("请选择需要修改的航班信息 : ");
		scanf("%d", &updata_id);
		hasUpdata = 1;
		isExit = 1;
		switch (updata_id)
		{
		case 1:
			printf("请输入新的航班号\n");
			scanf("%s", L.plane[index].plane_id);
			break;

		case 2:
			printf("请输入新的起点站\n");
			scanf("%s", L.plane[index].start);
			break;

		case 3:
			printf("请输入新的终点站\n");
			scanf("%s", L.plane[index].end);
			break;

		case 4:
			printf("请输入新的起飞时间(不含空格)\n");
			scanf("%s", L.plane[index].time_start);
			break;

		case 5:
			printf("请输入新的到达时间(不含空格)\n");
			scanf("%s", L.plane[index].time_end);
			break;

		case 6:
			printf("请输入新的机型\n");
			scanf("%s", L.plane[index].mode1);
			break;

		case 7:
			printf("请输入新的票价\n");
			scanf("%d", &L.plane[index].price);
			break;

		case 8:
			printf("请输入新的票数\n");
			scanf("%d", &L.plane[index].tickets);
			break;

		case 9:
			hasUpdata = 0;
			break;
		default:
			hasUpdata = 0;
			isExit = 0;
			printf("输入错误，请重新输入\n");
		}
	}
	return hasUpdata;
}
//修改航班
void UpdataPlane() {
	int i, flag, isExit = 0;
	int hasUpdata = 0;
	char plane_id[MAXSTR];
	plane_id[MAXSTR - 1] = '\0';
	while (!isExit) {
		system("cls");
		isExit = 1;
		printf("\t\t\t  —————— 修改 ———————\n");
		printf("\t\t\t\t   1.显示列表\n");
		printf("\t\t\t\t   2.修改航班\n");
		printf("\t\t\t\t   3.返    回\n");
		printf("请选择 : ");
		scanf("%d", &flag);

		switch (flag) {
		case 1:
			//显示列表
			ShowList();
		case 2:
			//查找航班
			printf("请输入航班号: ");
			scanf("%s", plane_id);
			for (i = 0; i < L.length; i++) {
				if (strcmp(L.plane[i].plane_id, plane_id) == 0)
				{
					printf("════════════════════════════════════════════════════════");
					printf("════════════════════════════════════════════════════════════\n");
					printf("航班号\t    起点站\t终点站\t\t起飞时间\t\t到达时间\t\t机型\t\t票价\t票数\n\n");
					ShowInfo(i);
					printf("════════════════════════════════════════════════════════");
					printf("════════════════════════════════════════════════════════════\n");
					break;
				}
			}
			if (i >= L.length) {
				printf("没有找到该航班号\n");
				system("pause");
				isExit = 0;
				break;
			}

			//选择航班信息
			Menu_Updata();
			//修改对应信息
			hasUpdata = UpdataInfo(i);
			if (hasUpdata) {
				SaveInfo();
				printf("修改成功\n");
			}
			break;
		case 3:
			break;
		default:
			isExit = 0;
			printf("输入错误，请重新输入\n");
			system("pause");
		}
	}


}
//显示用户购票信息
void ShowTickets() {
	int i;
	system("cls");
	printf("\t\t\t————--———— 订单 ————————--\n");
	printf("\t\t\t   姓名: ");
	printf("%s", user.name);
	printf("\t\t手机号码:");
	printf("%s\n", user.phone);
	if (!user.lenght) {
		printf("您尚未购票\n");
		return;
	}
	printf("\t\t\t═════════════════════════════════════════\n");
	printf("\t\t\t 航班号\t\t\t\t票数\n");
	for (i = 0; i < user.lenght; i++) {
		printf("\t\t\t------------------------------------------\n");
		printf("\t\t\t %s\t\t\t\t%d\n", user.tickets[i].plane_id, user.tickets[i].num);
	}
	printf("\t\t\t═════════════════════════════════════════\n");
}
//用户购票
void BookTicket() {
	//num为购票票数，index为已购票的订单下标
	int i, j, num = 0, flag, isExit = 0, index = -1;
	char ch;
	char plane_id[MAXSTR];
	plane_id[MAXSTR - 1] = '\0';
	while (!isExit) {
		system("cls");
		isExit = 1;
		printf("\t\t\t——————- 订票 -——————\n");
		printf("\t\t\t\t   1.订  票\n");
		printf("\t\t\t\t   2.返  回\n");
		printf("请选择 : ");
		scanf("%d", &flag);
		fflush(stdin);
		switch (flag) {
		case 1:
			ShowList();
			printf("请输入航班号: ");
			scanf("%s", plane_id);
			system("cls");
			for (i = 0; i < L.length; i++) {
				if (strcmp(L.plane[i].plane_id, plane_id) == 0)
				{
					printf("\n该航班信息如下:\n");
					printf("════════════════════════════════════════════════════════");
					printf("════════════════════════════════════════════════════════════\n");
					printf("航班号\t    起点站\t终点站\t\t起飞时间\t\t到达时间\t\t机型\t\t票价\t票数\n\n");
					ShowInfo(i);
					printf("════════════════════════════════════════════════════════");
					printf("════════════════════════════════════════════════════════════\n");
					break;
				}
			}
			if (i >= L.length) {
				printf("没有找到该航班号\n");
				system("pause");
				isExit = 0;
				break;
			}

			printf("\n请输入票数: ");
			scanf("%d", &num);
			if (num < 0 || num > L.plane[i].tickets || user.lenght >= MAXSTR - num) {
				printf("购票失败\n");
				system("pause");
				isExit = 0;
				break;
			}
			printf("输入 Y 确定购买: ");
			scanf(" %c", &ch);
			if (ch == 'y' || ch == 'Y') {
				L.plane[i].tickets -= num;
				for (j = 0; j < user.lenght; j++) {
					if (!strcmp(user.tickets[j].plane_id, plane_id)) {
						index = j;
						break;
					}
				}
				if (index == -1) {//订单中没有购买过此航班
					user.tickets[user.lenght].num = num;
					strcpy(user.tickets[user.lenght++].plane_id, plane_id);
				}
				else {//订单已存在此航班，票数叠加即可
					user.tickets[index].num += num;
				}
				printf("购票成功\n");
			}
			break;
		case 2:
			break;
		default:
			isExit = 0;
			printf("输入错误，请重新输入\n");
			system("pause");
		}
	}
	SaveInfo();
}
//用户退票
void RefTicket() {
	//index标志用户订单下标，position标志航班下标，num为退票票数
	int i, num = 0, flag, isExit = 0, index = -1, position = -1;
	char ch;
	char plane_id[MAXSTR];
	plane_id[MAXSTR - 1] = '\0';
	while (!isExit) {
		system("cls");
		isExit = 1;
		printf("\t\t\t——————- 退票 -—————\n");
		printf("\t\t\t\t   1.退  票\n");
		printf("\t\t\t\t   2.返  回\n");
		printf("请选择 : ");
		scanf("%d", &flag);

		switch (flag) {
		case 1:
			ShowTickets();
			printf("请输入航班号: ");
			scanf("%s", plane_id);
			system("cls");
			//先判断订单是否有此航班
			for (i = 0; i < user.lenght; i++) {
				if (!strcmp(user.tickets[i].plane_id, plane_id)) {
					index = i;
					break;
				}
			}
			if (index == -1) {
				printf("没有购买此航票:%s\n", plane_id);
				system("pause");
				isExit = 0;
				break;
			}
			//找到该航班所在的位置
			for (i = 0; i < L.length; i++) {
				if (!strcmp(L.plane[i].plane_id, plane_id)) {
					position = i;
					break;
				}
			}
			if (position == -1) {
				printf("系统中没有指定的航班信息\n");
				system("pause");
				break;
			}
			printf("\n该航班信息如下:\n");
			printf("════════════════════════════════════════════════════════");
			printf("════════════════════════════════════════════════════════════\n");
			printf("航班号\t    起点站\t终点站\t\t起飞时间\t\t到达时间\t\t机型\t\t票价\t票数\n\n");
			ShowInfo(position);
			printf("════════════════════════════════════════════════════════");
			printf("════════════════════════════════════════════════════════════\n");

			printf("\n请输入退票的票数: ");
			scanf("%d", &num);
			if (num < 0 || num > user.tickets[index].num) {
				printf("退票失败\n");
				system("pause");
				isExit = 0;
				break;
			}
			printf("输入 Y 确定退票: ");
			scanf(" %c", &ch);
			if (ch == 'y' || ch == 'Y') {
				L.plane[position].tickets += num;
				if ((user.tickets[index].num -= num) == 0) {
					user.lenght--;
				}
				printf("退票成功\n");
			}
			break;
		case 2:
			break;
		default:
			isExit = 0;
			printf("输入错误，请重新输入\n");
			system("pause");
		}
	}
	SaveInfo();
}
//菜单功能
void View() {
	int isLoop = 1;
	//登录
	int login_id = Login_System();
	if (login_id == 1)
	{
		while (isLoop)
		{
			int flag;
			system("cls");
			ShowMenu(login_id);
			scanf("%d", &flag);
			switch (flag)
			{
			case 1:
				QueryPlane();
				break;
			case 2:
				ShowList();
				break;
			case 3:
				BookTicket();
				break;
			case 4:
				RefTicket();
				break;
			case 5:
				SortPlane();
				break;
			case 6:
				ShowTickets();
				break;
			case 0:
				isLoop = 0;
				break;
			default:
				printf("输入错误，请重新输入\n");
			}
			printf("\n\n\n");
			system("pause");
		}
	}
	if (login_id == 2)
	{
		while (isLoop)
		{
			int flag;
			system("cls");
			ShowMenu(login_id);
			fflush(stdin);
			scanf("%d", &flag);
			switch (flag)
			{
			case 1:
				AddPlane();
				break;
			case 2:
				QueryPlane();
				break;
			case 3:
				DeletePlane();
				break;
			case 4:
				UpdataPlane();
				break;
			case 5:
				ShowList();
				break;
			case 6:
				SortPlane();
				break;
			case 0:
				isLoop = 0;
				break;
			default:
				printf("输入错误，请重新输入\n");
			}
			printf("\n\n\n");
			system("pause");
		}
	}
	if (login_id == 0) {
		isLoop = 0;
		printf("感谢您的使用！\n");
	}
}