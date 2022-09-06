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

	printf("*p = %d  //포인터 p가 가리키는 곳에 저장된 값\n", *p);
	printf("p = %d %x //포인터 p에 저장된 주소값\n", p, p);
	printf("&p = %d %x //포인터 p의 주소값\n", &p, &p);

	printf("*pp = %d %x //포인터 pp가 가리키는 곳에 저장된 값\n", *pp, *pp);
	printf("pp = %d %x //포인터 pp에 저장된 주소값\n", pp, pp);
	printf("&pp = %d %x //포인터 pp의 주소값\n", &pp,&pp);

	printf("&*p = %d %x //포인터 p가 가리키고 있는 곳의 주소값\n", &*p);
	printf("&*pp = %d %x //포인터 pp가 가리키고 있는 곳의 주소값\n", &*pp);
	printf("&**pp = %d %x\n\n",&**pp);

	printf("a = %d \n", a);
	printf("*p = %d\n", *p);
	printf("**pp = %d\n", **pp);


}