#define MAXSIZE 100
#define END '='
#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "math.h"
char ops[MAXSIZE];   //运算符栈
int  ops_top;        //运算符栈顶标识
double ovs[MAXSIZE];  //操作数栈
int  ovs_top;         //操作数栈顶标识
void push_ops(char x); //运算符进栈
void push_ovs(double x); //操作数进栈
char pop_ops(); //运算符出栈
double pop_ovs();//操作数出栈
char gettop_ops();  //取出运算符栈顶元素
double gettop_ovs();  //取出操作数栈顶元素
void inistack_ops();  //初始化运算符栈
void inistack_ovs(); //初始化操作数栈
char Precede(char t1,char t2);  //判断t1与t2的优先级别
int char_In(char c); //判断c是否为运算符
double Operate(double a,char theta,double b); //对出栈的两个数计算
double  EvaluateExpression( );//使用算符优先算法进行算术表示式求值
//ops[]为运算符栈，ovs[]为操作数栈
char input_h='n';//定义全局变量，用于缓存输入慢速【+】
char input_p='n';//定义全局变量，用于缓存输入【+】
int temp2=0;//定义全局变量，用于判断是否在完全入栈前进行运算 【+】 
int main(int argc, char* argv[]) {
	printf("计算器-花生皮编程\n");
	printf("请输入计算表达式，如1+2=\n");
	printf("%f",EvaluateExpression( ));
	getchar();
}
void push_ops(char x) { //运算符进栈
	if(ops_top==MAXSIZE-1) {
		printf("运算符栈已满！上溢");
		exit(1);
	} else
	{
		ops_top++;
		ops[ops_top]=x;
	}
}
void push_ovs(double x) { //操作数进栈
	if(ovs_top==MAXSIZE-1) {
		printf("操作数栈已满！上溢");
		exit(1);
	} else {
		ovs_top++;
		ovs[ovs_top]=x;
	}
}
char pop_ops() { //运算符出栈
	char y;
	if(ops_top==-1) {
		printf("输入有误");
		exit(1);
	} else {
		y=ops[ops_top];
		ops_top--;
	}
	return y;
}
double pop_ovs() { //操作数出栈
	double y;
	if(ovs_top==-1) {
		printf("输入有误");
		exit(1);
	} else {
		y=ovs[ovs_top];
		ovs_top--;
	}
	return y;
}
char gettop_ops() { //取出运算符栈顶元素
	if (ops_top!=-1)
		return ops[ops_top];
	else {
		printf("输入有误");
		exit(1);
	}
}
double gettop_ovs() { //取出操作数栈顶元素
	if (ovs_top!=-1)
		return ovs[ovs_top];
	else {
		printf("输入有误");
		exit(1);
	}
}
void inistack_ops() { //初始化运算符栈
	ops_top=-1;
}
void inistack_ovs() { //初始化操作数栈
	ovs_top=-1;
}
char Precede(char t1,char t2) { //判断t1与t2的优先级别
	char f;
	switch(t2) {
		case '+':
		case '-':
			if (t1=='('||t1==END)
				f='<';
			else
				f='>';
			break;
		case '*':
		case '/':
			if (t1=='*'||t1=='/'||t1==')')
				f='>';
			else f='<';
			break;
		case '(':
			if (t1==')') {
				printf("输入有误");
				exit(1);
			} else
				f='<';
			break;
		case ')':
			switch(t1) {
				case '(':
					f='=';
					break;
				case END:
					printf("输入有误");
					exit(1);
				default:
					f='>';
			}
			break;
		case END:
			switch(t1) {
				case END:
					f='=';
					break;
				case '(':
					printf("输入有误");
					exit(1);
				default:
					f='>';
			}
	}
	return f;
}
int char_In(char c) { //判断c是否为运算符
	switch(c) {
		case '+':
			if((!temp2)&&(char_In(input_h)||input_h=='n')) {//用于检测上一个输入是否为操作符【+】
				push_ovs(0);//向操作数栈填入一个0参与负数运算【+】
			}
			return 1;
		case '-':
			if((!temp2)&&(char_In(input_h)||input_h=='n')) {//用于检测上一个输入是否为操作符【+】
				push_ovs(0);//向操作数栈填入一个0参与负数运算【+】
			}
			return 1;
		case '(':
			if((!temp2)){
				if(input_h==')'||(input_h>='0'&&input_h<='9')||input_h=='.'){
					printf("输入有误");
					exit(0);
				}				
			} 
			return 1;
		case ')':
			if((!temp2)){
				if(!((input_h>='0'&&input_h<='9')||input_h==')')){
					printf("输入有误");
					exit(0);
				}				
			} 
			return 1;
		case '*':
		case '/':
		case END:
			return 1;
		default :
			return 0;
	}
}
double Operate(double a,char theta,double b) { //对出栈的两个数计算
	double c;
	switch(theta) { //theta为运算符
		case '+':
			c=a+b; //输出0-9的ASCII码
			break;
		case '-':
			c=a-b;
			break;
		case '*':
			c=a*b;
			break;
		case '/':
			c=a/b;
	}
	return c;
}
double EvaluateExpression( ) {
//使用算符优先算法进行算术表示式求值
//ops[]为运算符栈，ovs[]为操作数栈
	int cache_Len=0,i,j,flag=0;//flag用于计算连续输入数字个数 【+】
	double a,b,curnum;//curcum存储字符串转换成的小数 【+】
	char stack_x,theta,input_c,buff[MAXSIZE];//buff存储数字字符串 【+】
	inistack_ops();  //初始化运算符栈
	push_ops(END);   //使结束符进栈
	inistack_ovs(); //初始化操作数栈
	input_c=getchar();
	stack_x=gettop_ops();
	while(input_c!=END||stack_x!=END) { //判断计算是否结束
		if (char_In(input_c)) { //若输入的字符是7种运算符之一
			input_h=input_c;//缓存上一个输入【+】
			for(i=0; i<flag; i++) {//缓存字符串置空 【+】
				buff[i]='\0';
			}
			if(flag) {//将数字推向操作数栈 【+】
				push_ovs(curnum);
			}
			flag=0;//标志回滚【+】
			switch (Precede(stack_x,input_c)) {
				case '<':
					temp2=0;
					push_ops(input_c); //若栈顶(x)优先级<输入则输入进栈
					input_c=getchar();
					break;
				case '=':
					temp2=0;
					stack_x=pop_ops();//相等则出栈，即脱括号接受下一个字符
					input_c=getchar();
					break;
				case '>':
					temp2++;
					theta=pop_ops();
					b=pop_ovs();
					a=pop_ovs();
					push_ovs(Operate(a,theta,b));
					break;
			}
		} else if((input_c>='0'&&input_c<='9')||input_c=='.') { //input_c是操作数
			if(input_h==')'){//输入检查)右边不能为数字 
				printf("输入有误");
				exit(0);
			}
			input_h=input_c;//缓存上一个输入【+】
//			input_c=input_c-'0';
			flag++;//标志计数增加 【+】
			buff[flag-1]=input_c;//输入的字符暂时存储到buff缓存字符串中 【+】
			curnum=(double)atof(buff);//将字符串转换为小数 【+】
			input_c=getchar();
		} else {
			printf("输入有误");
			exit(1);
		}
		stack_x=gettop_ops();
	}
	return(gettop_ovs());
}