#include<stdio.h>

void main() {

	int a;
	int *p;
	int **pp;

	a = 100;
	p = &a;
	pp = &p;

	printf("a = %d\n", a);
	printf("&a = %d %x\n\n", &a,&a);

	printf("*p = %d  //������ p�� ����Ű�� ���� ����� ��\n", *p);
	printf("p = %d %x //������ p�� ����� �ּҰ�\n", p, p);
	printf("&p = %d %x //������ p�� �ּҰ�\n", &p, &p);

	printf("*pp = %d %x //������ pp�� ����Ű�� ���� ����� ��\n", *pp, *pp);
	printf("pp = %d %x //������ pp�� ����� �ּҰ�\n", pp, pp);
	printf("&pp = %d %x //������ pp�� �ּҰ�\n", &pp,&pp);

	printf("&*p = %d %x //������ p�� ����Ű�� �ִ� ���� �ּҰ�\n", &*p);
	printf("&*pp = %d %x //������ pp�� ����Ű�� �ִ� ���� �ּҰ�\n", &*pp);
	printf("&**pp = %d %x\n\n",&**pp);

	printf("a = %d \n", a);
	printf("*p = %d\n", *p);
	printf("**pp = %d\n", **pp);


}