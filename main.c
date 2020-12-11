#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 40000
#define LN_SIZE 20
#define SN_SIZE 100

#define BI_FILE "seoul_bus_info.txt"

typedef struct location
{
    double x;
    double y;
} _location;

typedef struct bus_data
{
    int line_id;
    char line_name[LN_SIZE];
    int order;
    int link_id;
    int station_id;
    int ars_id;
    char station_name[SN_SIZE];
    _location loc;
} _bus_data;

void find_by_station_name(_bus_data* ptr_bus_info, int size);
void find_by_line_name(_bus_data* ptr_bus_info, int size);

_bus_data array_of_bus[SIZE];

int main(void)
{
    _bus_data* ptr_bus_info = NULL;

    int num_of_struct_array = 0;
    char buffer[sizeof(_bus_data)];

    int get_number = 0;

    /*
        파일이 없을 때 생길 오류에 대비하여 예외처리
    */
    ptr_bus_info = fopen(BI_FILE, "rb");
    if (ptr_bus_info == NULL)
    {
        fprintf(stderr, "%s 파일을 열 수 없습니다.\n", BI_FILE);
        return 1;
    }

    /*
        버퍼의 사이즈는 _bus_data 구조체 자료형의 크기로 설정, 따라서 한 줄 씩 읽어올 수 있다.
        읽어온 후, array_of_bus라는 _bus_data 구조체 배열의 station_name과 line_name 멤버에 문자열을 복사한다.
    */

    while (fgets(buffer, sizeof(buffer), ptr_bus_info))
    {
        sscanf(buffer, "%[^','],%[^','],%[^','],%[^','],%[^','],%[^','],%[^','],%[^','],%d,%s,%d,%d,%d,%d,%s,%lf,%lf", &array_of_bus[num_of_struct_array].line_id, array_of_bus[num_of_struct_array].line_name, &array_of_bus[num_of_struct_array].order, &array_of_bus[num_of_struct_array].link_id, &array_of_bus[num_of_struct_array].station_id, &array_of_bus[num_of_struct_array].ars_id, array_of_bus[num_of_struct_array].station_name, &array_of_bus[num_of_struct_array].loc.x, &array_of_bus[num_of_struct_array].loc.y);
        num_of_struct_array++;
    }

    /*
        get_number 정수형 변수로 사용자로부터 정수를 받아와서 사용자가 선택할 수 있게 했다.
        while문을 이용하여 무한반복을 하되, 사용자가 3을 넣으면 종료하도록 설정하였다.
        이때, 동시에 파일을 닫도록 설정하였다.
    */

    while (get_number != 3)
    {
        printf("===================================\n");
        printf(" 1. 정류장 정차 버스 찾기\n");
        printf(" 2. 버스노선의 정차 정류장 찾기\n");
        printf(" 3. 종료\n");
        printf("===================================\n");
        printf("정수값을 선택하시오: ");

        scanf("%d", &get_number);

        switch (get_number)
        {
        case 1:
            find_by_station_name(array_of_bus, num_of_struct_array);
            break;
        case 2:
            find_by_line_name(array_of_bus, num_of_struct_array);
            break;
        case 3:
            fclose(ptr_bus_info);
            break;
        }
    }
    return 0;
}

/*
    함수 find_by_station_name은 array_of_bus 배열의 주소와 num_of_struct_array를 받아온다.
    사용자로부터 정류장이름을 받아올 get_station_name 캐릭터형 배열과, _bus_data형의 ptr을 선언하고 ptr_bus_info
    즉, array_of_bus 배열의 주소를 받아온다.
    for문을 사용해 ptr을 처음부터 끝까지 돌려준다.
    이때, array_of_bus 배열의 station_name과 사용자로부터 입력받은 get_station_name이 같다면 출력 조건을 만족하도록 하여
    출력하도록 설정하였다.
    함수 find_by_line_name도 위 함수와 같은 방식을 채택하였다.
*/

void find_by_station_name(_bus_data* ptr_bus_info, int size)
{
    char get_station_name[SN_SIZE];
    _bus_data* ptr=ptr_bus_info;

    printf("정류장 이름을 입력하세요 (일부 명칭도 가능): ");
    scanf("%s", get_station_name);

    for (ptr; ptr < (ptr_bus_info+size); ptr++)
        if(strstr(ptr->station_name, get_station_name)!=NULL)
             printf("[%s] 정류소에 [%s] 버스가 정차합니다.\n", ptr->station_name, ptr->line_name);
}

void find_by_line_name(_bus_data* ptr_bus_info, int size)
{
    char get_line_name[LN_SIZE];
    _bus_data* ptr = ptr_bus_info;

    printf("버스노선명을 입력하세요 :");
    scanf("%s", get_line_name);

    for(ptr; ptr<(ptr_bus_info+size); ptr++)
        if (strcmp(get_line_name, ptr->line_name) == 0)
            printf("[%s] 버스가 [%s] 정류장에 정차합니다.\n", ptr->line_name, ptr->station_name);
}
