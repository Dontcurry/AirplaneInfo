#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char airNo[8];
	char start_station[12];
	char end_station[12];
	char schedule[12];
	int start_time;
	int end_time;
	char model[8];
	int price;
}AirType;


void ShowMenu() {	/*���˵�*/
	system("cls");		/*DOS��������*/
	printf("			������Ϣ��ѯϵͳ\n");
	printf("	-----------------���˵�--------------------\n");
	printf("	|		1���뺽����Ϣ		|\n");
	printf("	|		2��ʾ���к���		|\n");
	printf("	|		3��ѯ������Ϣ		|\n");
	printf("	|		0�˳�ϵͳ			|\n");
	printf("	-------------------------------------------\n");
}

/*�����ַ�������Ϊlens*/
void StringInput(char *t, int lens, char *msg) {
	char str[12];
	do {
		printf(msg);	/*��ʾ��ʾ��Ϣ*/
		scanf("%s", str);	/*�����ַ���*/
		if (strlen(str) > lens)
			printf("\n input error!\n");	/*���г�����֤������lensֵ��������*/
	} while (strlen(str) > lens);
	strcpy(t, str);	/*��������ַ����������ַ���t��*/
}

/*������ʼʱ��͵���ʱ��*/
int NumberInput(char *msg) {
	int t = 0;
	do {
		printf(msg);	/*��ʾ��ʾ��Ϣ*/
		scanf("%d", &t);	/*�������*/
		if (t > 2400 || t < 0) {
			printf("\nʱ�����[0,2400]��\n");/*���з�����֤*/

		}
	}while (t > 2400 || t < 0);
	return t;
}

/*��ȡ�ļ��е���Ϣ������ȷ�������м�¼�ĸ���*/
int GetNumberOfAirs() {
	FILE *fp;
	/*�ļ�ָ��*/
	AirType t;
	int count = 0;/*�����ļ��еļ�¼����*/

	fp = fopen("D:\\air", "rb");	/*��һ���������ļ���*/
	if (fp == NULL) {
		return 0;
	}
	fseek(fp, 0, SEEK_END);
	count = ftell(fp) / sizeof(AirType);
	fclose(fp);/*�ر��ļ�*/
	return count;
}

/*���ļ��е����ݶ��뵽����a*/
void LoadDataToArr(AirType *a) {
	FILE *fp;	/*�ļ�ָ��*/
	AirType *p;	/*�����¼ָ�����*/
	int count = 0;	/*�����ļ��еļ�¼����*/
	p = a;
	fp = fopen("D:\\air", "ab+");	/*��׷�ӷ�ʽ��һ���������ļ����ɶ���д�����ļ���������ᴴ��*/
	if (fp == NULL) {
		printf("\n�����������ļ���\n");
		exit(0);
	}
	while (!feof(fp)) {
		if (fread(p, sizeof(AirType), 1, fp) == 1) {	/*һ�δ��ļ��ж�ȡһ����¼*/
			p++;
			count++;

		}

	}
	fclose(fp);	/*�ر��ļ�*/
	printf("\n��ʼ���ɹ���%d����¼������.\n", count);
	return;
}

/*���µĺ����¼��ӵ��ļ���ĩβ*/
void AddDataToFile() {
	FILE *fp;
	AirType t;
	int count = 0;	/*�����ļ��еļ�¼����*/
	fp = fopen("D:\\air", "ab+");	/*��׷�ӷ�ʽ��һ���������ļ�*/
	if (fp == NULL) {
		printf("\n�����������ļ���\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_END);	/*���ļ�ָ���Ƶ�ĩβ��׼���������*/
	while (1) {
		StringInput(t.airNo, 8, "[����0���˳�����]����ţ�");
		if (strcmp(t.airNo, "0") == 0)
			break;
		StringInput(t.start_station, 12, "��ʼվ:");
		StringInput(t.end_station, 12, "�յ�վ:");
		StringInput(t.schedule, 12, "����:");
		t.start_time = NumberInput("���ʱ�䣺0-2400");	/*24��00��2400��ʾ*/
		t.end_time = NumberInput("���ʱ��:0-2400");
		StringInput(t.model, 8, "����:");
		t.price = NumberInput("Ʊ��:");
		fwrite(&t, sizeof(AirType), 1, fp);	/*��һ�������¼д���ļ�*/
		count++;

	}
	fclose(fp);
	printf("\n%d����¼��д�롣\n", count);
	return;
}

void PrintHead() {
	printf("\n�����	��ʼվ	�յ�վ	����	���ʱ��	��վʱ��	����	Ʊ��\n");
	return;
}

void PrintData(AirType *p) {
	printf("%-8s%-11s%-11s%-7s %4d  %4d %6s  %d \n",
		p->airNo, p->start_station, p->end_station, p->schedule, p->start_time,
		p->end_time, p->model, p->price);
	return;
}

/*��ʾ���еĺ�����Ϣ*/
void ShowAllInfo(AirType *a, int n) {
	int i;
	PrintHead();
	for (i = 0; i < n; i++) {
		PrintData(&a[i]);
	}
	getchar();
	return;
}

void Query(AirType *a, int n) {
	int select;
	char qairNo[8];
	char qstart_station[12];
	char qend_station[12];
	int qstart_time;
	int qend_time;
	int condition1 = 0, condition2 = 0, condition3 = 0, condition4 = 0;
	int i, count;
	count = 0;
	if (n == 0) {
		/*������Ϊ��*/
		printf("\nû�з��ֺ�����Ϣ!\n");
		return;
	}
	printf("\n[1]������Ų��� [2]�����վ���յ�վ�����ʱ�䣬����ʱ�����\n");
	printf("��ѡ��[1,2]:");
	scanf("%d", &select);
	if (select == 1) {
		StringInput(qairNo, 8, "�����뺽���:");
		PrintHead();
		for (i = 0; i < n; i++) {
			if (strcmp(a[i].airNo, qairNo) == 0) {
				PrintData(&a[i]);
				count++;
			}
		}
	}
	else if (select == 2) {
		StringInput(qstart_station, 12, "[����'0'��ʾ����վ]��ʼվ:");
		qstart_time = NumberInput("[���롮0����ʾ�������ʱ��]���ʱ��");
		StringInput(qend_station, 12, "[���롮0����ʾ����վ]����վ:");
		qend_time = NumberInput("[���롮0����ʾ���⵽��ʱ��]����ʱ��:");
		PrintHead();
		for (i = 0; i < n; i++) {
			if (strcmp(a[i].start_station, qstart_station) == 0 || strcmp(qstart_station, "0") == 0)
				condition1 = 1;
			else
				condition1 = 0;
			if (abs(a[i].start_time - qstart_time) < 100 || abs(a[i].start_time - qstart_time) > 2300 || qstart_time == 0)
				condition2 = 1;
			else
				condition2 = 0;
			if (strcmp(a[i].end_station, qend_station) == 0 || strcmp(qend_station, "0") == 0)
				condition3 = 1;
			else
				condition3 = 0;
			if (abs(a[i].end_time - qend_time) < 100 || abs(a[i].end_time - qend_time) > 2300 || qend_time == 0)
				condition4 = 1;
			else
				condition4 = 0;
			if (condition1&&condition2&&condition3&&condition4) {
				PrintData(&a[i]);
				count++;
			}
		}
	}
	if (count == 0) {
		printf("\nû�з��ּ�¼\n");
	}
	printf("�����������...");
	getchar();
}

int main() {
	int n, select;
	AirType *arr;
	n = GetNumberOfAirs();
	arr = (AirType*)malloc(n * sizeof(AirType));
	LoadDataToArr(arr);

	while (1) {
		ShowMenu();
		printf("\n	ѡ��0-3�����в�����");	/*��ʾ��ʾ��Ϣ*/
		scanf("%d", &select);
		switch (select) {
		case 1:AddDataToFile();
			free(arr);
			n = GetNumberOfAirs();
			arr = (AirType*)malloc(n * sizeof(AirType));
			LoadDataToArr(arr);
			break;	/*��Ӻ�����Ϣ*/
		case 2:ShowAllInfo(arr, n);
			break;
		case 3:
			Query(arr, n);
			break;
		case 0:
			return 0;
		}
		getchar();
	}
	return 0;
}
