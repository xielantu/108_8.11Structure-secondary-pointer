// 108_8.11结构体二级指针.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct XuanMin
{
	char name[32];
	int tickets;
};
void initXms(struct XuanMin** pxm, int* pn)//初始化选民信息//这个int* pn只提供地址，经过这个函数的调用后，赋给pn一个数值
{
	int i;
	if (*pxm == NULL)
	{
		printf("请输入有几个人参选：\n");
		scanf_s("%d", pn);
		*pxm = (struct XuanMin*)malloc(*pn * sizeof(struct XuanMin));
	}

	for (i = 0; i < *pn; i++)
	{
		(*pxm)->tickets = 0;
		printf("请输入第%d个选民的名字\n", i + 1);
		scanf_s("%s", (*pxm)->name, sizeof((*pxm)->name));
		(*pxm)++;
	}
	*pxm= *pxm - (*pn);//每次返回一个原来的起始地址
}

void printXms(struct XuanMin* p, int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		printf("名字：%s ,票数：%d\n", p->name, p->tickets);
		p++;
	}
}

int doVot(struct XuanMin* p, int len)
{
	int feipiao = 0;
	int i;
	int j;
	int mark;
	char tmpName[32] = { '\0' };
	struct XuanMin* pbak = p;

	for (i = 0; i < 5; i++)
	{
		mark = 0;
		printf("请输入你投给谁：\n");
		memset(tmpName, '\0', sizeof(tmpName));
		scanf_s("%s", tmpName, sizeof(tmpName));
		p = pbak;
		for (j = 0; j < len; j++)
		{
			if (strcmp(tmpName, p->name) == 0)
			{
				p->tickets++;
				mark = 1;
			}
			p++;
		}
		if (mark == 0)
		{
			printf("没有此候选人，放弃\n");
			feipiao++;
		}

	}


	return feipiao;
}

struct XuanMin* getMax(struct XuanMin* p, int len)
{
	struct XuanMin* max;
	int i;
	max = p;
	for (i = 0; i < len; i++)
	{
		if (max->tickets < p->tickets)
		{
			max = p;
		}
		p++;
	}

	return max;
}


int main()
{
	struct XuanMin* xm = NULL;
	struct XuanMin* final;
	int total = 0;

	//初始化选民信息
	initXms(&xm, &total);//A函数调B函数，来改变B函数里面的局部变量(total)
	printXms(xm, total);


	//唱票环节
	int feipiao = doVot(xm, total);
	printf("废票数是:%d\n", feipiao);
	printXms(xm, total);


	//公示结果
	final = getMax(xm, total);
	printf("%s以%d票当选！！废票有%d张\n", final->name, final->tickets, feipiao);

	return 0;
}

