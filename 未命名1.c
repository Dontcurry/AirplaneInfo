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


void ShowMenu() {	/*主菜单*/
	system("cls");		/*DOS命令清屏*/
	printf("			航班信息查询系统\n");
	printf("	-----------------主菜单--------------------\n");
	printf("	|		1输入航班信息		|\n");
	printf("	|		2显示所有航班		|\n");
	printf("	|		3查询航班信息		|\n");
	printf("	|		0退出系统			|\n");
	printf("	-------------------------------------------\n");
}

/*输入字符串长度为lens*/
void StringInput(char *t, int lens, char *msg) {
	char str[12];
	do {
		printf(msg);	/*显示提示信息*/
		scanf("%s", str);	/*输入字符串*/
		if (strlen(str) > lens)
			printf("\n input error!\n");	/*进行长度验证，超过lens值重新输入*/
	} while (strlen(str) > lens);
	strcpy(t, str);	/*将输入的字符串拷贝到字符串t中*/
}

/*输入起始时间和到达时间*/
int NumberInput(char *msg) {
	int t = 0;
	do {
		printf(msg);	/*显示提示信息*/
		scanf("%d", &t);	/*输入分数*/
		if (t > 2400 || t < 0) {
			printf("\n时间介于[0,2400]！\n");/*进行分数验证*/

		}
	}while (t > 2400 || t < 0);
	return t;
}

/*读取文件中的信息，用于确定数组中记录的个数*/
int GetNumberOfAirs() {
	FILE *fp;
	/*文件指针*/
	AirType t;
	int count = 0;/*保存文件中的记录条数*/

	fp = fopen("D:\\air", "rb");	/*打开一个二进制文件读*/
	if (fp == NULL) {
		return 0;
	}
	fseek(fp, 0, SEEK_END);
	count = ftell(fp) / sizeof(AirType);
	fclose(fp);/*关闭文件*/
	return count;
}

/*将文件中的数据读入到数组a*/
void LoadDataToArr(AirType *a) {
	FILE *fp;	/*文件指针*/
	AirType *p;	/*定义记录指针变量*/
	int count = 0;	/*保存文件中的记录条数*/
	p = a;
	fp = fopen("D:\\air", "ab+");	/*以追加方式打开一个二进制文件，可读可写，若文件不存在则会创建*/
	if (fp == NULL) {
		printf("\n不能正常打开文件！\n");
		exit(0);
	}
	while (!feof(fp)) {
		if (fread(p, sizeof(AirType), 1, fp) == 1) {	/*一次从文件中读取一条记录*/
			p++;
			count++;

		}

	}
	fclose(fp);	/*关闭文件*/
	printf("\n初始化成功，%d条记录被调入.\n", count);
	return;
}

/*将新的航班记录添加到文件的末尾*/
void AddDataToFile() {
	FILE *fp;
	AirType t;
	int count = 0;	/*保存文件中的记录条数*/
	fp = fopen("D:\\air", "ab+");	/*以追加方式打开一个二进制文件*/
	if (fp == NULL) {
		printf("\n不能正常打开文件！\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_END);	/*将文件指针移到末尾，准备添加数据*/
	while (1) {
		StringInput(t.airNo, 8, "[按’0‘退出输入]航班号：");
		if (strcmp(t.airNo, "0") == 0)
			break;
		StringInput(t.start_station, 12, "起始站:");
		StringInput(t.end_station, 12, "终点站:");
		StringInput(t.schedule, 12, "班期:");
		t.start_time = NumberInput("起飞时间：0-2400");	/*24：00用2400表示*/
		t.end_time = NumberInput("起飞时间:0-2400");
		StringInput(t.model, 8, "机型:");
		t.price = NumberInput("票价:");
		fwrite(&t, sizeof(AirType), 1, fp);	/*将一条航班记录写入文件*/
		count++;

	}
	fclose(fp);
	printf("\n%d条记录被写入。\n", count);
	return;
}

void PrintHead() {
	printf("\n航班号	起始站	终点站	班期	起飞时间	到站时间	机型	票价\n");
	return;
}

void PrintData(AirType *p) {
	printf("%-8s%-11s%-11s%-7s %4d  %4d %6s  %d \n",
		p->airNo, p->start_station, p->end_station, p->schedule, p->start_time,
		p->end_time, p->model, p->price);
	return;
}

/*显示所有的航班信息*/
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
		/*若数组为空*/
		printf("\n没有发现航班信息!\n");
		return;
	}
	printf("\n[1]按航班号查找 [2]按起点站，终点站，起飞时间，到达时间查找\n");
	printf("请选择[1,2]:");
	scanf("%d", &select);
	if (select == 1) {
		StringInput(qairNo, 8, "请输入航班号:");
		PrintHead();
		for (i = 0; i < n; i++) {
			if (strcmp(a[i].airNo, qairNo) == 0) {
				PrintData(&a[i]);
				count++;
			}
		}
	}
	else if (select == 2) {
		StringInput(qstart_station, 12, "[输入'0'表示任意站]起始站:");
		qstart_time = NumberInput("[输入‘0’表示任意起飞时间]起飞时间");
		StringInput(qend_station, 12, "[输入‘0’表示任意站]到达站:");
		qend_time = NumberInput("[输入‘0’表示任意到达时间]到达时间:");
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
		printf("\n没有发现记录\n");
	}
	printf("按任意键返回...");
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
		printf("\n	选择（0-3）进行操作：");	/*显示提示信息*/
		scanf("%d", &select);
		switch (select) {
		case 1:AddDataToFile();
			free(arr);
			n = GetNumberOfAirs();
			arr = (AirType*)malloc(n * sizeof(AirType));
			LoadDataToArr(arr);
			break;	/*添加航班信息*/
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
