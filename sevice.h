#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>;
#include<stdlib.h>;
#include<string.h>;
// �洢�����������
#define MAXSIZE 200
#define MAXSTR 30

//����plane�ṹ������
typedef struct plane {
	char plane_id[MAXSTR];		//�����
	char start[MAXSTR];			//���վ
	char end[MAXSTR];			//�յ�վ
	char time_start[MAXSTR];	//���ʱ��
	char time_end[MAXSTR];		//����ʱ��
	char mode1[MAXSTR];			//����
	int price;					//Ʊ��
	int tickets;				//Ʊ��
}Plane;

//����˳���L���溽����Ϣ
struct PlaneList {
	Plane plane[MAXSIZE];
	int length;
}L;

//Ticket����
typedef struct ticket {
	char plane_id[MAXSTR];		//����id	
	int num;					//Ʊ��
}Ticket;
//�û�����
typedef struct user {
	char name[MAXSTR];			//�û�����
	char phone[MAXSTR];			//�ֻ�����
	Ticket tickets[MAXSTR];		//����
	int lenght;					//������
}User;
//�����û�
User user;

//��ʼ���û�
void InitUser() {
	strcpy(user.name, "����");
	strcpy(user.phone, "100000");
}
//��¼ϵͳ
int Login_System() {
	int login_id = 0;
	int flag = 0;
	int isExit = 0;
	//��ʼ�˺�����
	char user_id[9] = "z";
	char password_user[9] = "123456";
	char password_manager[9] = "000000";

	while (!isExit) {
		char id[9], password[9];
		system("cls");
		printf("Ĭ���˺�Ϊ��z\n");
		printf("Ĭ��ѧ������Ϊ��123456\n");
		printf("Ĭ�Ϲ���Ա���룺000000\n\n");
		printf("  ������������������- ��ӭʹ��ͼ��ϵͳ -������������������\n");
		printf("\t\t\t���� 1 ��¼\n");
		printf("\t\t\t else �˳�\n");
		isExit = 1;
		scanf("%d", &flag);
		if (flag != 1) {
			return 0;
		}
		//8λ�˺ź����룬���һ��λ��������ֹ��
		id[8] = '\0';
		password[8] = '\0';

		printf("\n----�������˺�----\n");
		scanf("%s", id);
		printf("----����������----\n");
		scanf("%s", password);

		//�ж�ϵͳ
		if (strcmp(user_id, id) == 0 && strcmp(password, password_user) == 0) {
			login_id = 1;//�û�ϵͳ
			break;
		}
		if (strcmp(user_id, id) == 0 && strcmp(password, password_manager) == 0) {
			login_id = 2;//����Աϵͳ
			break;
		}

		if (!login_id) {
			printf("�˺Ż������������\n\n");
			printf("\t\t�������� ���� ��������\n");
			printf("\t\t     ���� 0 ����\n");
			printf("\t\t      else �˳�\n");
			scanf("%d", &isExit);
		}
	}
	return login_id;
}
//�˵�ҳ��,���û��͹���Ա
void ShowMenu(int login_id) {
	if (login_id == 1) {
		printf("\t\t\t    ��������������- �û��˵� ��������������-\n");
		printf("\t\t\t\t �X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
		printf("\t\t\t\t �U     1-��ѯ       2-�б�    �U\n");
		printf("\t\t\t\t �U	  		      �U\n");
		printf("\t\t\t\t �U     3-��Ʊ       4-��Ʊ    �U\n");
		printf("\t\t\t\t �U	  		      �U\n");
		printf("\t\t\t\t �U     5-����       6-����    �U\n");
		printf("\t\t\t\t �U    	     0-�˳�	      �U\n");
		printf("\t\t\t\t �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	}
	else {
		printf("\t\t\t   ��������������- ����Ա�˵� ��������������-\n");
		printf("\t\t\t\t �X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
		printf("\t\t\t\t �U     1-¼��       2-��ѯ    �U\n");
		printf("\t\t\t\t �U	  		      �U\n");
		printf("\t\t\t\t �U     3-ɾ��       4-�޸�    �U\n");
		printf("\t\t\t\t �U	  		      �U\n");
		printf("\t\t\t\t �U     5-�б�       6-����    �U\n");
		printf("\t\t\t\t �U    	     0-�˳�	      �U\n");
		printf("\t\t\t\t �^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	}
	printf("��ѡ����: ");
}
//������Ϣ���ļ�
void SaveInfo() {
	int i;
	//д�뺽����Ϣ
	FILE* fp = fopen("plane.txt", "w+");
	if (!fp) {
		printf("��plane.txt�ļ�ʧ�ܣ�����!\n");
		return;
	}
	for (i = 0; i < L.length; i++) {
		if (fprintf(fp, "%s %s %s %s %s %s %d %d\n", L.plane[i].plane_id, L.plane[i].start, L.plane[i].end, \
			L.plane[i].time_start, L.plane[i].time_end, L.plane[i].mode1, L.plane[i].price, L.plane[i].tickets) == EOF) {
			fclose(fp);
			printf("д��plane.txt�ļ�ʧ�ܣ����飡\n");
		}
	}
	fflush(stdin);
	if (fclose(fp) == EOF) {
		printf("�ر�plane.txt�ļ�ʧ�ܣ����飡\n");
		return;
	}

	//д���û���Ʊ��Ϣ
	fp = fopen("user.txt", "w+");
	if (!fp) {
		printf("��user.txt�ļ�ʧ��\n");
		return;
	}
	for (i = 0; i < user.lenght; i++) {
		fprintf(fp, "%s %d ", user.tickets[i].plane_id, user.tickets[i].num);
	}
	fflush(stdin);
	if (fclose(fp) == EOF) {
		printf("�ر�user.txt�ļ�ʧ�ܣ����飡\n");
		return;
	}
}
//���ļ���ȡ��Ϣ
void ReadInfo()
{
	FILE* fp = fopen("plane.txt", "a+");
	int i;
	if (!fp) {
		printf("��plane.txt�ļ�ʧ��\n");
		return;
	}
	//���ж��뺽����Ϣ
	for (i = 0; i < MAXSIZE; i++) {
		if (fscanf(fp, "%s%s%s%s%s%s%d%d\n", L.plane[i].plane_id, L.plane[i].start, L.plane[i].end, \
			L.plane[i].time_start, L.plane[i].time_end, L.plane[i].mode1, &L.plane[i].price, &L.plane[i].tickets) == EOF)
			break;
	}
	L.length = i;//���泤��
	if (fclose(fp) == EOF) {
		printf("�ر�plane.txt�ļ�ʧ�ܣ����飡\n");
	}

	//�����û�������Ϣ
	fp = fopen("user.txt", "a+");
	if (!fp) {
		printf("���ļ�ʧ��\n");
		return;
	}
	for (i = 0; i < MAXSTR; i++) {
		if (fscanf(fp, "%s %d ", user.tickets[i].plane_id, &user.tickets[i].num) == EOF) {
			break;
		}
	}
	user.lenght = i;
	if (fclose(fp) == EOF) {
		printf("�ر�user.txt�ļ�ʧ�ܣ����飡\n");
		return;
	}
	printf("��ȡ�ļ��ɹ�\n");
}
//��ʾ������Ϣ
void ShowInfo(int i) {
	printf(" %-12s%-11s%-16s%-18s\t%-17s\t%-16s%-10d%-10d\n", L.plane[i].plane_id, L.plane[i].start, L.plane[i].end, \
		L.plane[i].time_start, L.plane[i].time_end, L.plane[i].mode1, L.plane[i].price, L.plane[i].tickets);
}
//��ʾ�����б�
void ShowList() {
	system("cls");
	int i;
	if (!L.length) {
		printf("�޺�����Ϣ\n");
	}
	else {
		printf("������Ϣ�б�\n");
		printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
		printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
		printf("�����\t    ���վ\t�յ�վ\t\t���ʱ��\t\t����ʱ��\t\t����\t\tƱ��\tƱ��\n\n");
		for (i = 0; i < L.length; i++) {
			printf("--------------------------------------------------------------------------------------------------------------------\n");
			ShowInfo(i);
		}
		printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
		printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
	}
}
//¼�뺽��
void AddPlane() {
	int ch;
	int hasExist = 0;
	system("cls");
	printf("\t\t\t������������- ¼�� -������������\n");
	printf("\t\t\t\t     1 ¼��\n");
	printf("\t\t\t\t   else ����\n");
	printf("��ѡ��: ");
	scanf("%d", &ch);
	if (ch == 1) {
		if (L.length >= MAXSIZE) {
			printf("��Ǹ����������,�޷�����ͼ��\n");
			return;
		}
		int len = L.length;
		printf("�밴����ʾ��Ӻ�����Ϣ��\n");
		printf("�����뺽���: ");
		scanf("%s", L.plane[len].plane_id);
		// �жϺ�����Ƿ��Ѿ�����
		for (int i = 0; i < len; i++) {
			if (strcmp(L.plane[len].plane_id, L.plane[i].plane_id) == 0) {
				hasExist = 1;
				break;
			}
		}
		if (hasExist == 1) {
			printf("�ú�����Ѿ����ڣ��޷�¼��\n");
			return;
		}
		printf("���������վ: ");
		scanf("%s", L.plane[len].start);
		printf("�������յ�վ: ");
		scanf("%s", L.plane[len].end);
		printf("���������ʱ��: ");
		scanf("%s", L.plane[len].time_start);
		printf("�����뵽��ʱ��: ");
		scanf("%s", L.plane[len].time_end);
		printf("���������: ");
		scanf("%s", L.plane[len].mode1);
		printf("������Ʊ��: ");
		scanf("%d", &L.plane[len].price);
		printf("������Ʊ��: ");
		scanf("%d", &L.plane[len].tickets);
		L.length++;
		SaveInfo();//������Ϣ���ļ�
		printf("¼��ɹ�����ǰ����%d�˺���\n", L.length);
	}
}
//��ѯ����
void QueryPlane() {
	int i;
	int isExit = 0, hasExist = 0, flag;
	char plane_id[MAXSTR], start[MAXSTR], end[MAXSTR], time_start[MAXSTR], time_end[MAXSTR];

	while (!isExit)
	{
		system("cls");
		printf("\t\t\t����������- ���ҷ�ʽ -����������\n");
		printf("\t\t\t\t   1.�����\n");
		printf("\t\t\t\t   2.���վ\n");
		printf("\t\t\t\t   3.�յ�վ\n");
		printf("\t\t\t\t   4.���ʱ��(����)\n");
		printf("\t\t\t\t   5.����ʱ��(����)\n");
		printf("\t\t\t\t   6.��  ��\n");
		isExit = 1;
		hasExist = 0;
		printf("��ѡ����ҷ�ʽ: ");
		scanf("%d", &flag);

		switch (flag)
		{
		case 1:
			printf("�����뺽���\n");
			plane_id[MAXSTR - 1] = '\0';
			scanf("%s", plane_id);

			for (i = 0; i < L.length; i++) {
				if (strcmp(L.plane[i].plane_id, plane_id) == 0)
				{
					printf("���� %s ��Ϣ����:\n", plane_id);
					printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
					printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
					printf("�����\t    ���վ\t�յ�վ\t\t���ʱ��\t\t����ʱ��\t\t����\t\tƱ��\tƱ��\n\n");
					ShowInfo(i);
					printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
					printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
					hasExist = 1;
					break;
				}
			}
			break;
		case 2:
			printf("���������վ\n");
			start[MAXSTR - 1] = '\0';
			scanf("%s", start);

			for (i = 0; i < L.length; i++) {
				if (strcmp(L.plane[i].start, start) == 0)
				{
					if (!hasExist) {
						printf("���վΪ  %s �ĺ�����Ϣ����:\n", start);
						printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
						printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
						printf("�����\t    ���վ\t�յ�վ\t\t���ʱ��\t\t����ʱ��\t\t����\t\tƱ��\tƱ��\n\n");
					}
					ShowInfo(i);
					hasExist = 1;
				}
			}
			if (hasExist) {
				printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
				printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
			}
			break;
		case 3:
			printf("�������յ�վ\n");
			end[MAXSTR - 1] = '\0';
			scanf("%s", end);
			for (i = 0; i < L.length; i++) {
				if (strcmp(L.plane[i].end, end) == 0)
				{
					if (!hasExist) {
						printf("�յ�վΪ %s �ĺ�����Ϣ����:\n", end);
						printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
						printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
						printf("�����\t    ���վ\t�յ�վ\t\t���ʱ��\t\t����ʱ��\t\t����\t\tƱ��\tƱ��\n\n");
					}
					ShowInfo(i);
					hasExist = 1;
				}
			}
			if (hasExist) {
				printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
				printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
			}
			break;
		case 4:
			printf("���������ʱ��\n");
			//��ʽΪXXXX-XX-XX
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
						printf("���ʱ��Ϊ %s �ĺ�����Ϣ����:\n", time_start);
						printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
						printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
						printf("�����\t    ���վ\t�յ�վ\t\t���ʱ��\t\t����ʱ��\t\t����\t\tƱ��\tƱ��\n\n");
					}
					hasExist = 1;
					ShowInfo(i);
				}
			}
			if (hasExist) {
				printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
				printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
			}
			break;
		case 5:
			printf("�����뵽��ʱ��\n");
			//��ʽΪXXXX-XX-XX
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
						printf("���ʱ��Ϊ %s �ĺ�����Ϣ����:\n", time_end);
						printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
						printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
						printf("�����\t    ���վ\t�յ�վ\t\t���ʱ��\t\t����ʱ��\t\t����\t\tƱ��\tƱ��\n\n");
					}
					hasExist = 1;
					ShowInfo(i);
				}
			}
			if (hasExist) {
				printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
				printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
			}
			break;
		case 6:
			hasExist = 1;
			break;
		default:
			isExit = 0;
			hasExist = 1;
			printf("�����������������\n");
			system("pause");
		}

		//����ʧ��
		if (!hasExist) {
			system("cls");
			printf("û�в��ҵ�������Ϣ\n");
			printf("\t\t\t  ���������� ʧ�� ����������\n");
			printf("\t\t\t\t   ����0����\n");
			printf("\t\t\t\t   else ����\n");
			printf("��ѡ��: ");
			scanf("%d", &isExit);
		}
	}
}
//������
void SortPlane() {
	int i, j;
	int flag, isExit = 0, hasSort;
	//ѡ������
	while (!isExit) {
		system("cls");
		isExit = 1;
		hasSort = 1;
		printf("\t\t\t  ����������������ʽ������������\n");
		printf("\t\t\t\t    1.��  ��\n");
		printf("\t\t\t\t    2.Ʊ  ��\n");
		printf("\t\t\t\t    3.���ʱ��\n");
		printf("\t\t\t\t    4.��  ��\n");
		printf("��ѡ������ʽ:");
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
				//����
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
				//����
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
				//����
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
			printf("�����������������\n");
			system("pause");
		}
	}
	if (hasSort) {
		ShowList();
		SaveInfo();
	}

}
//ɾ������
void DeletePlane() {
	int i, flag, isExit = 0;
	char ch;
	char plane_id[MAXSTR];
	plane_id[MAXSTR - 1] = '\0';
	while (!isExit) {
		system("cls");
		isExit = 1;
		printf("\t\t\t  ������������ ɾ�� ��������������\n");
		printf("\t\t\t\t   1.��ʾ�б�\n");
		printf("\t\t\t\t   2.ɾ������\n");
		printf("\t\t\t\t   3.��    ��\n");
		printf("��ѡ�� : ");
		scanf("%d", &flag);

		switch (flag) {
		case 1:
			//��ʾ�б�
			ShowList();
		case 2:
			printf("�����뺽���: ");
			scanf("%s", plane_id);
			for (i = 0; i < L.length; i++) {
				if (strcmp(L.plane[i].plane_id, plane_id) == 0)
				{
					printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
					printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
					printf("�����\t    ���վ\t�յ�վ\t\t���ʱ��\t\t����ʱ��\t\t����\t\tƱ��\tƱ��\n\n");
					ShowInfo(i);
					printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
					printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
					break;
				}
			}
			if (i >= L.length) {
				printf("\n\nû���ҵ��ú����\n");
				isExit = 0;
				system("pause");
				break;
			}
			printf("���� Y ȷ��ɾ��\n");
			scanf(" %c", &ch);
			//����ɾ������ָ��λ�ÿ�ʼ����һ��Ԫ�ظ���ǰһ��Ԫ��
			if (ch == 'y' || ch == 'Y') {
				while (i < L.length - 1) {
					L.plane[i] = L.plane[i + 1];
					++i;
				}
				L.length--;
				SaveInfo();
				printf("ɾ���ɹ�,��ǰ����%d�˺���\n", L.length);
			}
			break;

		case 3:
			break;
		default:
			isExit = 0;
			printf("�����������������\n");
			system("pause");
		}
	}
}
//�˵�---�޸���Ϣ
void Menu_Updata() {//��ʾ�޸���Ŀ 

	printf("\t\t\t\t�T�T�T�T�T�T�T�T�T �޸ĺ�����Ϣ�T�T�T�T�T�T�T�T�T\n");
	printf("\t\t\t\t                    \n");
	printf("\t\t\t\t   --------1.�����------\n");
	printf("\t\t\t\t                    \n");
	printf("\t\t\t\t   --------2.���վ------\n");
	printf("\t\t\t\t                    \n");
	printf("\t\t\t\t   --------3.�յ�վ------\n");
	printf("\t\t\t\t                    \n");
	printf("\t\t\t\t   --------4.���ʱ��----\n");
	printf("\t\t\t\t                    \n");
	printf("\t\t\t\t   --------5.����ʱ��----\n");
	printf("\t\t\t\t                    \n");
	printf("\t\t\t\t   --------6.����--------\n");
	printf("\t\t\t\t                    \n");
	printf("\t\t\t\t   --------7.Ʊ��--------\n");
	printf("\t\t\t\t                    \n");
	printf("\t\t\t\t   --------8.Ʊ��--------\n");
	printf("\t\t\t\t                    \n");
	printf("\t\t\t\t   --------9.�˳�--------\n");
	printf("\t\t\t\t                    \n");
	printf("\t\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
}
//�޸�ָ��������Ϣ
int UpdataInfo(int index) {
	int updata_id;
	int hasUpdata = 0;
	int isExit = 0;
	while (!isExit)
	{
		printf("��ѡ����Ҫ�޸ĵĺ�����Ϣ : ");
		scanf("%d", &updata_id);
		hasUpdata = 1;
		isExit = 1;
		switch (updata_id)
		{
		case 1:
			printf("�������µĺ����\n");
			scanf("%s", L.plane[index].plane_id);
			break;

		case 2:
			printf("�������µ����վ\n");
			scanf("%s", L.plane[index].start);
			break;

		case 3:
			printf("�������µ��յ�վ\n");
			scanf("%s", L.plane[index].end);
			break;

		case 4:
			printf("�������µ����ʱ��(�����ո�)\n");
			scanf("%s", L.plane[index].time_start);
			break;

		case 5:
			printf("�������µĵ���ʱ��(�����ո�)\n");
			scanf("%s", L.plane[index].time_end);
			break;

		case 6:
			printf("�������µĻ���\n");
			scanf("%s", L.plane[index].mode1);
			break;

		case 7:
			printf("�������µ�Ʊ��\n");
			scanf("%d", &L.plane[index].price);
			break;

		case 8:
			printf("�������µ�Ʊ��\n");
			scanf("%d", &L.plane[index].tickets);
			break;

		case 9:
			hasUpdata = 0;
			break;
		default:
			hasUpdata = 0;
			isExit = 0;
			printf("�����������������\n");
		}
	}
	return hasUpdata;
}
//�޸ĺ���
void UpdataPlane() {
	int i, flag, isExit = 0;
	int hasUpdata = 0;
	char plane_id[MAXSTR];
	plane_id[MAXSTR - 1] = '\0';
	while (!isExit) {
		system("cls");
		isExit = 1;
		printf("\t\t\t  ������������ �޸� ��������������\n");
		printf("\t\t\t\t   1.��ʾ�б�\n");
		printf("\t\t\t\t   2.�޸ĺ���\n");
		printf("\t\t\t\t   3.��    ��\n");
		printf("��ѡ�� : ");
		scanf("%d", &flag);

		switch (flag) {
		case 1:
			//��ʾ�б�
			ShowList();
		case 2:
			//���Һ���
			printf("�����뺽���: ");
			scanf("%s", plane_id);
			for (i = 0; i < L.length; i++) {
				if (strcmp(L.plane[i].plane_id, plane_id) == 0)
				{
					printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
					printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
					printf("�����\t    ���վ\t�յ�վ\t\t���ʱ��\t\t����ʱ��\t\t����\t\tƱ��\tƱ��\n\n");
					ShowInfo(i);
					printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
					printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
					break;
				}
			}
			if (i >= L.length) {
				printf("û���ҵ��ú����\n");
				system("pause");
				isExit = 0;
				break;
			}

			//ѡ�񺽰���Ϣ
			Menu_Updata();
			//�޸Ķ�Ӧ��Ϣ
			hasUpdata = UpdataInfo(i);
			if (hasUpdata) {
				SaveInfo();
				printf("�޸ĳɹ�\n");
			}
			break;
		case 3:
			break;
		default:
			isExit = 0;
			printf("�����������������\n");
			system("pause");
		}
	}


}
//��ʾ�û���Ʊ��Ϣ
void ShowTickets() {
	int i;
	system("cls");
	printf("\t\t\t��������--�������� ���� ����������������--\n");
	printf("\t\t\t   ����: ");
	printf("%s", user.name);
	printf("\t\t�ֻ�����:");
	printf("%s\n", user.phone);
	if (!user.lenght) {
		printf("����δ��Ʊ\n");
		return;
	}
	printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
	printf("\t\t\t �����\t\t\t\tƱ��\n");
	for (i = 0; i < user.lenght; i++) {
		printf("\t\t\t------------------------------------------\n");
		printf("\t\t\t %s\t\t\t\t%d\n", user.tickets[i].plane_id, user.tickets[i].num);
	}
	printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
}
//�û���Ʊ
void BookTicket() {
	//numΪ��ƱƱ����indexΪ�ѹ�Ʊ�Ķ����±�
	int i, j, num = 0, flag, isExit = 0, index = -1;
	char ch;
	char plane_id[MAXSTR];
	plane_id[MAXSTR - 1] = '\0';
	while (!isExit) {
		system("cls");
		isExit = 1;
		printf("\t\t\t������������- ��Ʊ -������������\n");
		printf("\t\t\t\t   1.��  Ʊ\n");
		printf("\t\t\t\t   2.��  ��\n");
		printf("��ѡ�� : ");
		scanf("%d", &flag);
		fflush(stdin);
		switch (flag) {
		case 1:
			ShowList();
			printf("�����뺽���: ");
			scanf("%s", plane_id);
			system("cls");
			for (i = 0; i < L.length; i++) {
				if (strcmp(L.plane[i].plane_id, plane_id) == 0)
				{
					printf("\n�ú�����Ϣ����:\n");
					printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
					printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
					printf("�����\t    ���վ\t�յ�վ\t\t���ʱ��\t\t����ʱ��\t\t����\t\tƱ��\tƱ��\n\n");
					ShowInfo(i);
					printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
					printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
					break;
				}
			}
			if (i >= L.length) {
				printf("û���ҵ��ú����\n");
				system("pause");
				isExit = 0;
				break;
			}

			printf("\n������Ʊ��: ");
			scanf("%d", &num);
			if (num < 0 || num > L.plane[i].tickets || user.lenght >= MAXSTR - num) {
				printf("��Ʊʧ��\n");
				system("pause");
				isExit = 0;
				break;
			}
			printf("���� Y ȷ������: ");
			scanf(" %c", &ch);
			if (ch == 'y' || ch == 'Y') {
				L.plane[i].tickets -= num;
				for (j = 0; j < user.lenght; j++) {
					if (!strcmp(user.tickets[j].plane_id, plane_id)) {
						index = j;
						break;
					}
				}
				if (index == -1) {//������û�й�����˺���
					user.tickets[user.lenght].num = num;
					strcpy(user.tickets[user.lenght++].plane_id, plane_id);
				}
				else {//�����Ѵ��ڴ˺��࣬Ʊ�����Ӽ���
					user.tickets[index].num += num;
				}
				printf("��Ʊ�ɹ�\n");
			}
			break;
		case 2:
			break;
		default:
			isExit = 0;
			printf("�����������������\n");
			system("pause");
		}
	}
	SaveInfo();
}
//�û���Ʊ
void RefTicket() {
	//index��־�û������±꣬position��־�����±꣬numΪ��ƱƱ��
	int i, num = 0, flag, isExit = 0, index = -1, position = -1;
	char ch;
	char plane_id[MAXSTR];
	plane_id[MAXSTR - 1] = '\0';
	while (!isExit) {
		system("cls");
		isExit = 1;
		printf("\t\t\t������������- ��Ʊ -����������\n");
		printf("\t\t\t\t   1.��  Ʊ\n");
		printf("\t\t\t\t   2.��  ��\n");
		printf("��ѡ�� : ");
		scanf("%d", &flag);

		switch (flag) {
		case 1:
			ShowTickets();
			printf("�����뺽���: ");
			scanf("%s", plane_id);
			system("cls");
			//���ж϶����Ƿ��д˺���
			for (i = 0; i < user.lenght; i++) {
				if (!strcmp(user.tickets[i].plane_id, plane_id)) {
					index = i;
					break;
				}
			}
			if (index == -1) {
				printf("û�й���˺�Ʊ:%s\n", plane_id);
				system("pause");
				isExit = 0;
				break;
			}
			//�ҵ��ú������ڵ�λ��
			for (i = 0; i < L.length; i++) {
				if (!strcmp(L.plane[i].plane_id, plane_id)) {
					position = i;
					break;
				}
			}
			if (position == -1) {
				printf("ϵͳ��û��ָ���ĺ�����Ϣ\n");
				system("pause");
				break;
			}
			printf("\n�ú�����Ϣ����:\n");
			printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
			printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
			printf("�����\t    ���վ\t�յ�վ\t\t���ʱ��\t\t����ʱ��\t\t����\t\tƱ��\tƱ��\n\n");
			ShowInfo(position);
			printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T");
			printf("�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");

			printf("\n��������Ʊ��Ʊ��: ");
			scanf("%d", &num);
			if (num < 0 || num > user.tickets[index].num) {
				printf("��Ʊʧ��\n");
				system("pause");
				isExit = 0;
				break;
			}
			printf("���� Y ȷ����Ʊ: ");
			scanf(" %c", &ch);
			if (ch == 'y' || ch == 'Y') {
				L.plane[position].tickets += num;
				if ((user.tickets[index].num -= num) == 0) {
					user.lenght--;
				}
				printf("��Ʊ�ɹ�\n");
			}
			break;
		case 2:
			break;
		default:
			isExit = 0;
			printf("�����������������\n");
			system("pause");
		}
	}
	SaveInfo();
}
//�˵�����
void View() {
	int isLoop = 1;
	//��¼
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
				printf("�����������������\n");
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
				printf("�����������������\n");
			}
			printf("\n\n\n");
			system("pause");
		}
	}
	if (login_id == 0) {
		isLoop = 0;
		printf("��л����ʹ�ã�\n");
	}
}