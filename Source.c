#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable:4996)
//FILE* fopen(const char* filename, const char* mode);
/*
struct user{
	int friendList[];
	char* word[];
}User;
*/
char** arrayInit(char* arr[], int length){
	for (int i = 0; i < length; i++)
		arr[i] = NULL;
	return arr;
}


int* insertionSort(int* data, int n){
	int i, j, remember;
	for (i = 1; i < n; i++){
		remember = data[(j = i)];
		while (--j >= 0 && remember < data[j])
			data[j + 1] = data[j];
		data[j + 1] = remember;
	}
	return data;
}
/*menu0: read data*/
void menu0(FILE* user, FILE* friend, FILE* word){
	int userCount = 0;
	int friendCount = 0;
	int wordCount = 0;
	userCount = Read_By_four(user);
	friendCount = Read_By_three(friend);
	wordCount = Read_By_four(word);
	printf("Total users: %d\n"
		"Total friendship records : %d\n"
		"Total tweets : %d\n", userCount, friendCount, wordCount);

}

int Read_By_three(FILE* file){
	char str[50];
	int count = 0;
	while (feof(file) == 0){
		fgets(str, sizeof(str), file);
		fgets(str, sizeof(str), file);
		fgets(str, sizeof(str), file);
		count++;
	}
	fclose(file);
	return count;
}

int Read_By_four(FILE* file){
	char str[50];
	int count = 0;
	while (feof(file) == 0){
		fgets(str, sizeof(str), file);
		fgets(str, sizeof(str), file);
		fgets(str, sizeof(str), file);
		fgets(str, sizeof(str), file);
		count++;
	}
	fclose(file);
	return count;
}
/*menu2: top5 most tweeted words*/
typedef struct User{
	char num[50];
	char id[50];
	char word[50];
	struct user* next;
}user;

void LinkedList(user person){
	person.next = NULL;
}linkedList;
/*
void menu2(FILE* file){
	char str[50];
	while (feof(file) == 0){
		struct user* newUser;
		newUser = (user*)malloc(sizeof(user));
		fgets(str, sizeof(str), file);
		newUser->num = str;
		fgets(str, sizeof(str), file); //date
		fgets(str, sizeof(str), file); //year
		newUser->word = fgets(str, sizeof(str), file);
		fgets(str, sizeof(str), file);//개행문자
	}
}
*/
/*menu4: 특정 단어를 tweet한 사람 찾기*/
void menu4(FILE* file, FILE* file2){
	char word[50];
	char userList[50][50] = { '\0', };
	char tempUser[50];
	char str[50];
	char input[50];
	int i = 0;
	puts("단어를 입력하세요:");
	fgets(word, 50, stdin);
	/*userList배열을 초기화*/
	//printf("%s", word);
	//userList = arrayInit(userList, 50);
	while (feof(file) == 0 && i < 100){
		fgets(tempUser, sizeof(tempUser), file);
		fgets(str, sizeof(str), file);
		fgets(input, sizeof(input), file);
		fgets(str, sizeof(str), file);
		if (strcmp(word, input)==0){
			//char* nWord = (char*)malloc(sizeof(char) * 50);
			strcpy(userList[i], tempUser);
			i++;
		}
	}
	printf("%s를 트윗한 사람의 목록:\n", word);
	if (userList[0][0] == '\0')
		puts("그 단어를 트윗한 사람은 없습니다");
	else{
		for (int i = 0; userList[i][0] != '\0'; i++){
			while (feof(file2) == 0){
				char num[50];
				char str[50];
				char ID[50];
				fgets(num, sizeof(num), file2);//num
				fgets(str, sizeof(str), file2);//date
				fgets(ID, sizeof(ID), file2);//id
				fgets(str, sizeof(str), file2);
				if (strcmp(num, userList[i])==0){
					strcpy(userList[i], ID);
					break;
				}
			}
		}
		for (int i = 0; userList[i][0] != '\0'; i++){
			printf("%s", userList[i]);
		}
	}
}
int main(void){
	FILE* friendTxt = fopen("friend.txt", "rt");
	FILE* userTxt = fopen("user.txt", "rt");
	FILE* wordTxt = fopen("word.txt", "rt");
	if (friendTxt == NULL){
		puts("friendTxt 열기 실패!");
		return -1;
	}
	else if (userTxt == NULL){
		puts("userTxt 열기 실패!");
		return -1;
	}
	else if (wordTxt == NULL){
		puts("wordTxt 열기 실패!");
		return -1;
	}

	int selectMenu;
	printf(
		"0. Read data files\n"
		"1. display statistics\n"
		"2. Top 5 most tweeted words\n"
		"3. Top 5 most tweeted users\n"
		"4. Find users who tweeted a word(e.g., ’연세대’)\n"
		"5. Find all people who are friends of the above users\n"
		"6. Delete all mentions of a word\n"
		"7. Delete all users who mentioned a word\n"
		"8. Find strongly connected components\n"
		"9. Find shortest path from a given user\n"
		"99. Quit\n"
		"Select Menu : \n"
	);
	scanf("%d", &selectMenu);
	getchar(); // scanf 사용 후의 buffer에 남아있는 \n을 제거한다
	switch (selectMenu){
	case 0:
		menu0(userTxt, friendTxt, wordTxt);
		break;
	case 4:
		menu4(wordTxt, userTxt);
		break;
	case 99:
		puts("프로그램을 종료합니다");
		return -1;
	}
	return 0;
}
