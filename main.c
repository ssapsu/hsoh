#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define S_SIZE 50
#define YES 1
#define NO 0


typedef struct BOOK_LIST_NODE
{
    char title[S_SIZE];
    int year;
    struct BOOK_LIST_NODE* link;
    int is_checked_out;
} BOOK_LIST_NODE;

char buffer[S_SIZE];
BOOK_LIST_NODE* list = NULL;
BOOK_LIST_NODE* prev = NULL, * p, * next;

void print_menu(void);                //메뉴판을 생성하는 함수
void register_new_book(void);        //책을 등록하는 함수
void check_out(void);                //책을 대출하는 함수
void check_in(void);                //책을 반납하는 함수
void print_book_list(void);            //책 리스트를 출력하는 함수
void return_memory(void);            //메모리를 반납하는 함수

int main(void)
{
    int n = 0, get_num;

    printf("연결형 리스트를 이용한 도서관리 프로그램\n");

    /*
        무한 반복문을 사용하기 위해 n의 초기값을 0으로 설정하였다. 나중에 사용자가 4를 입력할 시 n에 4를 대입하여
        반복문을 탈출하도록 설정함.
        사용자로부터 숫자를 받아와서 메뉴 0~4까지 선택할 수 있게 switch문을 사용하였다.
    */

    while (n != 4)
    {
        print_menu();
        scanf("%d", &get_num);
        getchar();
        switch (get_num)
        {
            case 0:
            {
                register_new_book();
                break;
            }
            case 1:
            {
                check_out();
                break;
            }
            case 2:
            {
                check_in();
                break;
            }
            case 3:
            {
                print_book_list();
                break;
            }
            case 4:
            {
                return_memory();
                n = 4;
                break;
            }
            default:
            {
                printf("잘못 입력하였습니다.\n");
                break;
            }
        }
    }
    return 0;
}

void print_menu()
{
    printf("\n");
    printf("=====================\n");
    printf("0. 신규 등록\n");
    printf("1. 도서 대출\n");
    printf("2. 도서 반납\n");
    printf("3. 목록 출력\n");
    printf("4. 종료\n");
    printf("=====================\n");
}

void register_new_book()
{
    int year;
    p = (BOOK_LIST_NODE*)malloc(sizeof(BOOK_LIST_NODE));

    /*
        오류가 날 것에 대비하여 예외처리를 해준다.
    */

    if (p == NULL)
    {
        printf("동적 메모리 할당 오류\n");
        exit(1);
    }

    printf("등록할 책의 제목을 입력하시오: ");
    scanf("%s",buffer);
    getchar();
    strcpy(p->title, buffer);

    printf("책의 출판 연도를 입력하시오: ");
    gets(buffer);

    year = atoi(buffer);
    p->year = year;
    printf("%s\n를 성공적으로 등록하였습니다.\n", p->title);

    p->is_checked_out = NO;
    if (list == NULL)
        list = p;
    else
        prev->link = p;
    p->link = NULL;
    prev = p;
}

/*
    p의 값을 list의 주소로 받아와서 while문을 돌린다. 구조체 멤버들의 값을 가져오고 나면 p의 값을
    다음 노드의 주소로 바꿔서 p가 NULL일 때까지 돌린다.
*/

void print_book_list()
{
    int order = 0;
    p = list;
    while (p != NULL)
    {
        printf("순서 %d, 출판연도 %d, 대출여부 %d, 제목 %s\n  \n",order, p->year,p->is_checked_out ,p->title );
        order++;
        p = p->link;
    }
}

/*
    마찬가지로 check_in함수와 골자는 같다. 하지만 다음의 3가지 경우에 대해서 다음과 같이 진행함
    1,2 의 경우 문자열 비교함수strcmp를 사용하여 리스트에서의 책 제목과 사용자로부터 입력받은 값이 같은지 확인하고
    진행하였다.
        1. 책을 대여하려고 했지만 책이 이미 대출된 경우
            ->구조체 멤버 is_checked_out 이 참(1)인 경우 대출중임을 출력하고 반복문 탈출
        2. 대출되지 않은 책을 대여할 수 있게 된 경우
            ->구조체 멤버 is_checked_out 이 거짓(0)이므로 대출하였다는 말과 함께 is_checked_out 변수 값에 YES(1)를 대입하고 탈출
        3. 사용자로부터 입력받은 책의 제목이 리스트에 없을 경우
            ->while문을 끝마치고 나오기 전에 1,2의 조건이 실현되면 탈출하도록 설정하였으므로 존재하지 않는다는 문구를 출력하고 탈출
*/

void check_out()
{
    printf("대여할 책의 제목을 입력하시오: ");
    gets(buffer);
    p = list;
    while (p != NULL)
    {
        if (strcmp(p->title, buffer) == 0)
        {
            if (p->is_checked_out == YES)
            {
                printf("%s\n가 이미 대출중입니다.\n", buffer);
                break;
            }
                else
            {
                printf("%s\n 를 대출에 성공하였습니다.\n", buffer);
                p->is_checked_out=YES;
                break;
            }
        }
        p = p->link;
    }
    if (p == NULL)
        printf("%s\n 가 존재하지 않습니다.\n", buffer);
}

/*
    위 함수와 동일하게 먼저 사용자로부터 입력받은 문자열과 책 이름이 같은지 여부를 판단하고 만약 같다면 대출 여부를 따진 후
    반복문을 탈출하도록 설정
    책이 존재하지 않는 경우도 위의 주석 참고
*/

void check_in()
{
    printf("반납할 책의 제목을 입력하시오: ");
    p = list;
    gets(buffer);
    while (p != NULL)
    {
        if (strcmp(p->title, buffer) == 0)
        {
            if (p->is_checked_out == NO)
            {
                printf("%s\n는 대출중인 책이 아닙니다.\n\n", buffer);
                break;
            }
            else
            {
                printf("%s\n 반납에 성공하였습니다.\n\n", buffer);
                p->is_checked_out = NO;
                break;
            }
        }
        p = p->link;
    }
    if (p == NULL)
        printf("%s\n 가 존재하지 않습니다.\n", buffer);
}

/*
    p에 list 주소값을 할당하고 메모리 반납시킨 후, 다음 노드의 주소값을 p에 대입을 하여 p가 NULL일 때까지 수행하여
    할당된 메모리 모두를 반납한다.
*/

void return_memory()
{
    p = list;
    while (p != NULL)
    {
        next = p->link;
        free(p);
        p = next;
    }
    printf("메모리를 모두 반납하였습니다.\n");
}
