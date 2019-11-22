#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>
#define S_size 100

char errorAlret[74] = "알수없는 문자, 숫자, 기호 또는 2가지 이상 입력하여 프로그램이 종료됩니다.";
char Menu[120] = "    1. 현재 달력 출력\n    2. 일정 목록 표시\n    3. 일정 추가 하기\n    4. 일정 삭제 하기\n\n\t0. 나가기\n\n";
char bar[65] = "===========================================================";

void Init() {
	system("cls");
}
void Stop() {
	system("pause");
}

struct Calendar {
	int Year;
	int Month;
	int Day;
	char Comment[100];
};
char schedule[20000]="";

void bubble_sort(struct Calendar list[], int n) {
	int i, j;
	struct Calendar temp;
	for (i = n - 1; i > 0; i--) {
		// 0 ~ (i-1)까지 반복
		for (j = 0; j < i; j++) {
			// j번째와 j+1번째의 요소가 크기 순이 아니면 교환
			if (list[j].Year < list[j + 1].Year) {
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}

int main() {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	struct Calendar data[100];
	FILE* Cal = NULL, *be=NULL;
	char buffer[200];
	char years[8] = "",months[4]="",days[4]="";
	int inputN; int year = tm.tm_year + 1900; int month = tm.tm_mon + 1; int cnt = 0;
	
	
	be = fopen("beplay.txt", "r+");
	
	while (fscanf(be,"%d %d %d %s", &data[cnt].Year, &data[cnt].Month, &data[cnt].Day, data[cnt].Comment)!=EOF)
	{
		cnt++;
	}


	fclose(be);

	while (1) {
		

		printf("======간단한 Calendar======\n\n");
		printf(Menu); printf("===========================\n"); scanf("%d", &inputN);
		Init();
		if (inputN == 1) {
			Cal = fopen("Calendar.txt", "r+");
			printf("현재 달력을 출력합니다.\n\n");
			int monthday[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }, startday = 1, allday = 1, line = 0;
			char buffer[S_size];
			monthday[2] = 28;  startday = 1; allday = 1;
			if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
				monthday[2] = 29;
			}
			allday += (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
			for (int i = 1; i < month; i++) {
				allday += (monthday[i]);
			}
			startday = allday % 7;
			fseek(Cal, 0, SEEK_SET);
			fprintf(Cal, "=========%d %d %d=========\n  일  월  화  수  목  금  토\n", year, month, tm.tm_mday);
			for (int i = 0; i < startday; i++) {
				fprintf(Cal, "    ");
			}
			for (int i = 1; i <= monthday[month]; i++) {
				if (i == tm.tm_mday) {
					fprintf(Cal, "  ●");
				}
				else {
					fprintf(Cal, "%4d", i);
				}
				if ((i + startday) % 7 == 0) {
					fprintf(Cal, "\n");
				}
			}
			fprintf(Cal, "============================\n\n");
			fseek(Cal, 0, SEEK_SET);
			for (int i = 0; i < 8; i++) {
				fgets(buffer, sizeof(buffer), Cal);
				printf("%s", buffer);
			}
			fclose(Cal);
			inputN = 0; Stop(); Init();
		}
		else if (inputN == 2) {
			for(int i=0;i<cnt;i++)
				printf("%d %d %d %s\n", data[i].Year, data[i].Month, data[i].Day, data[i].Comment);
			inputN = 0; Stop(); Init();
		}
		else if (inputN == 3) {
			
			printf("일정을 추가할 날짜를 입력해주세요.\n ex) %d %d %d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday); scanf("%d %d %d", &data[cnt].Year, &data[cnt].Month, &data[cnt].Day);
			while (data[cnt].Year < tm.tm_year + 1900) {
				Init(); printf("년도를 다시 입력해주세요. ex) %d\n", tm.tm_year + 1900); scanf("%d", &data[cnt].Year);
			}
			while (data[cnt].Month > 12 || data[cnt].Month < 1) {
				Init(); printf("달을 다시 입력해주세요. ex) %d\n", tm.tm_mon + 1); scanf("%d", &data[cnt].Month);
			}
			while (data[cnt].Day < 1 || data[cnt].Day > 31) {
				if (data[cnt].Month % 2 == 0) {
					if (data[cnt].Month == 2) {
						if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
							while (data[cnt].Day < 0 || data[cnt].Day > 29) {
								Init(); printf("일을 다시 입력해주세요. ex) %d\n", tm.tm_mday); scanf("%d", &data[cnt].Day);
							}
						}
						while (data[cnt].Day < 1 || data[cnt].Day > 28) {
							Init(); printf("일을 다시 입력해주세요. ex) %d\n", tm.tm_mday); scanf("%d", &data[cnt].Day);
						}
					}
					else {
						while (data[cnt].Day < 1 || data[cnt].Day > 30) {
							Init(); printf("일을 다시 입력해주세요. ex) %d\n", tm.tm_mday); scanf("%d", &data[cnt].Day);
						}
					}
				}
				else {
					while (data[cnt].Day < 1 || data[cnt].Day > 31) {
						Init(); printf("일을 다시 입력해주세요. ex) %d\n", tm.tm_mday); scanf("%d", &data[cnt].Day);
					}
				}
			}
			printf("일정의 내용을 입력해주세요. (한글 50자,영어 100자)\n"); scanf(" %[^\n]c", &data[cnt].Comment);
			while (strlen(data[cnt].Comment) > 100) {
				Init(); printf("일정 내용의 길이가 너무 깁니다. 다시 입력해주세요."); scanf("%[^\n]c", &data[cnt].Comment);
			}
			be = fopen("beplay.txt", "r+");
			
			char s1[20];
			strcat(schedule, "\n");
			sprintf(s1, "%d", data[cnt].Year);
			strcat(schedule, s1);
			strcat(schedule, "/");
			if (data[cnt].Month < 10)
				strcat(schedule, " ");
			sprintf(s1, "%d", data[cnt].Month);
			strcat(schedule, s1);
			strcat(schedule, "/");
			if (data[cnt].Day < 10)
				strcat(schedule, " ");

			sprintf(s1, "%d", data[cnt].Day);
			strcat(schedule, s1);
			strcat(schedule, " 일정 :");
			strcat(schedule, data[cnt].Comment);
			strcat(schedule,"\n");

			printf("입력 완료\n");
			cnt++;
			inputN = 0; Stop(); Init();
		}
		else if (inputN == 4) {
		printf("삭제할 문장과 년 월 일을 입력해주세요");
		int ye, da, mo;
		char chen[1000];
		printf("년 월 일"); scanf("%d %d %d", &ye, &mo, &da);
		printf("삭제할 문장:"); scanf("%s", chen);
		for (int i = 0; i < cnt; i++) {
			if (data[i].Year == ye) {
				if (data[i].Day == da) {
					if (data[i].Month == mo) {
						if (!strcmp(data[i].Comment, chen)) {
							cnt--;
							for (int j = i; j < cnt; j++) {
								data[j] = data[j + 1];
							}
						}
					}
				}
			}
		
		}
			inputN = 0; Stop(); Init();
		}
		else if (inputN == 0) {
		system("pause");
			Init();
			printf("프로그램이 종료됩니다.");
			be = fopen("beplay.txt", "w");
			for (int i = 0; i < cnt; i++) {
				if(i==cnt-1)
					fprintf(be, "%d %d %d %s", data[i].Year, data[i].Month, data[i].Day, data[i].Comment);
				else
					fprintf(be, "%d %d %d %s\n", data[i].Year, data[i].Month, data[i].Day, data[i].Comment);
			}
			return 0;
		}
		else {
		for (int i = 0; i < cnt; i++)
			printf("%d %d %d %s", data[i].Year, data[i].Month, data[i].Day,data[i].Comment);

			//printf(errorAlret);
			
		}
	}
}