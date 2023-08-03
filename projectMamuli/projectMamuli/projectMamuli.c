#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 10000	// ���� ���� ����

#include <stdio.h>		//�������
#include <time.h>		//�ð� �������, ���� ��¥ ��� �ϱ����� ���
#include <windows.h>	//����� �ܼ�â ����ϱ� ���ؼ�, Ŀ����ġ �̵��ϴ� �Լ� ����
#include <stdlib.h>		//exit�� ����Ͽ� �����ϱ����Ѱ�
#include <sys/stat.h>	//mkdir()�Լ��� �̿��Ͽ� ���丮�� ����� ���� ���
#include <string.h>		//���ڿ� ���� ó���� ���� ���
#include <io.h>			// ���� ���� ���� Ȯ�� �������
#include <conio.h>		// ���� ���� ���� Ȯ�� �������







// ==============================================   �Լ� ����   ===================================================
void info();	//����
void printCalender(int inputYear, int inputMonth);	// ������ �⵵, �� �Է½� �ش� Ķ���� ���, �ð��ڷ�
int mainScreen();									// ���ν�ũ�������� ��ɵ� (printCalender �� ���̻��)
int leapYear(int year);								// ���� ����
void inputScreen(year, month);						// �Է�â �Լ�
void printTitle();									// inputScreen ȭ�鿡 Title ���
void makeFolder(year, month);						// ���� ���� �Լ�
void printSaveInfo();								// ���� ���� �ȳ�����
void diary();										// ���̾ â �Լ�
int checkFileExists();								// ���� ���� ���� üũ �Լ�
int moveToTrashcan(char* prePath, char* postPath);	// ������ trashcan���� �̵���Ű�� �Լ�
void trashcan();									// ������ ����� �ϴ� �Լ�




// ==============================================   ����ü ===================================================
struct mainData {
	int year, month;
}mainData;

struct inputScreenData {
	char strPath[40];				// ���ڿ��� ��ġ�� ���� ū Ʋ(������ ��ΰ� ����ȴ�.)
	char strYear[20];				// year���� ���ڿ��� �ޱ� ���� ���� �迭
	char strMonth[20];				// month���� ���ڿ��� �ޱ� ���� ���� �迭
	char input[MAX_LENGTH];			// �� ������ ��� ����
	char titleDay[20];				// Ÿ��Ʋ ��¥
	char titleName[20];				// ����
	char strProjectFolder[40];
	char basic[20];					// ���ڿ��� "projectMamul"�� �߰��ϱ� ���� ����
	char fileName[20];				// �����̸�
	char getContents[100];			// ������ ������ ���� ����
} screenData;

struct diaryData {
	char year[20];
	char month[20];
	char input[10000];
	char fileName[20];
	char strPath[40];
	char basic[20];
	char filePath[40];
	char inputFileName[20];
	char getContents[100];
	char deleteFileName[20];
} diaryData;

struct trashData {
	char strTrashFolder[40];
	char filePath[40];
} trashData;




//=================================== ���� �Լ� ==========================================
int main(void) {
	int first;
	int start = 0;
	// �߰��� �׸�(day0518)
	int returnValue = 0;	// mainScreen���� ������ ����� ���ϰ�(1.�ۼ�, 2.���� 3.���� 4.����ȭ��)

	system("title ProjectMamuli");

	// ������ ���� �̸� �����
	mkdir("/projectMamuli/trash");

	while (1) {
		//����ȭ��
		printf("\n\n\n\n\n");
		printf("\t                    **************\n");
		printf("\t                    Project Mamuli\n");
		printf("\t                    **************\n");
		printf("\n\n\n\n");
		printf("\t\t���Ͻô� ����� �Է��ϼ��� ex) 1 (enter)\n\n\n");
		printf("\t  1. ����    2. ����    3. ���̾    4. ������    0. ����\n\n");
		printf("			:");
		scanf("%d", &first);


		// ����ȭ�� ���
		switch (first) {
		case 1:
			system("cls");
			printf("\t���ϴ� ��¥�� �Է��Ͻÿ�.(ex.2022 05) : ");
			scanf_s("%d %d", &mainData.year, &mainData.month);
			returnValue = mainScreen();

			break;

		case 2:
			system("cls");
			info();		//���� ����ֱ�

			returnValue = 4;
			break;	// ���򸻿��� ���´�.

		case 3:
			diary();

			returnValue = 4;
			break;
		case 4:
			printf("\n<������>\n");

			trashcan();

			break;
		case 0:
			printf("			���α׷��� �����մϴ�.");
			exit(0);		//����
		}


		// mainScreen ���
		switch (returnValue) {
		case 1:// 1. �ۼ� ���
			inputScreen(mainData.year, mainData.month);		// �Է� �Լ� ȣ��

			system("cls");
			break;

		case 2: // 2. �� �ٸ� ���
			printf("�ٸ� ��� ���̵�� �� �����غ�~");

			break;
		}
	}
	return 0;
}




//����ȭ�� �Լ� (�Է¹޾Ƽ� ��¥�� �°� ���)
int mainScreen() {
	int choice;	// ��� ���� ����
	int returnValue = 0;	// main�Լ��� �������� ��ȯ����

	// "Ķ���� �Լ� ȣ��"
	printCalender(mainData.year, mainData.month);	// main���� �޾ƿ� inputYear���� inputMonth���� Ķ���� �Լ��� �־��ش�.

	while (1)
	{
		printf("\n\n\n\t��� ����: 1. �ۼ�    2. ��¥ ����   3. ����ȭ��\n");
		printf("\t�Է� : ");
		scanf_s("%d", &choice);
		system("cls");
		if (choice == 1) {
			printCalender(mainData.year, mainData.month);
			printf("\n\t-------------------------------------------------\n");
			printf("\t���� �ۼ� ������� �̵��մϴ�.\n");
			printf("\t1�� �� ���� �ۼ� ������� �̵��մϴ�...");
			printf("\n\t-------------------------------------------------\n");
			Sleep(1000);
			returnValue = 1;
			break;
		}
		else if (choice == 2) {
			printf("\n\t-------------------------------------------------\n");
			printf("\t��¥ ���� ������� �̵��մϴ�.\n");
			printf("\t1�� �� ���� ������� �̵��մϴ�...");
			printf("\n\t-------------------------------------------------\n");
			Sleep(1000);
			system("cls");
			printf("\t���ϴ� ��¥�� �Է��Ͻÿ�.(ex.2022 05) : ");
			scanf_s("%d %d", &mainData.year, &mainData.month);
			printCalender(mainData.year, mainData.month);
			continue;
		}
		else if (choice == 3) {
			printCalender(mainData.year, mainData.month);
			printf("\n\t-------------------------------------------------\n");
			printf("\t3�� �� ����ȭ������ ���ư��ϴ�...\n");
			Sleep(1000);
			printf("\t2�� �� ����ȭ������ ���ư��ϴ�...\n");
			Sleep(1000);
			printf("\t1�� �� ����ȭ������ ���ư��ϴ�...");
			printf("\n\t-------------------------------------------------\n");
			Sleep(1000);

			system("cls");
			return;
		}
		else {
			printCalender(mainData.year, mainData.month);
			printf("\n\t1, 2, 3 �� �Է��Ͻÿ�.\n");
		}

	}

	return returnValue;
}



//����������������������������
// Ķ���� ���
void printCalender(int inputYear, int inputMonth) {
	int sum = 365;				// 1�� �ϼ�
	int start_date = 0;			// 1���� ���۵Ǵ� ������ ���ϴ� ����
	int total_days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	// ������ ���, 2���� ��¥ ���� 28 -> 29�� �� �ٲ��� �ϹǷ� 1�� �����ش�.
	if (leapYear(inputYear)) {
		total_days[1]++;
	}

	// 0����� �Է��� �⵵���� ��¥�� ��� ����
	for (int i = 1; i < inputYear; i++) {
		if (leapYear(i)) {
			sum += 366;
		}
		else {
			sum += 365;
		}
	}

	// ���� ���� ��¥�� ��� ����.
	// inputMonth - 1�� �ϴ� ������, ���� �� ������ ����ϱ� ���ؼ���.
	for (int i = 0; i < inputMonth - 1; i++) {
		sum += total_days[i];
	}

	// ��� ���� ��¥�� 7�� ������ ������ �������� ����.
	// 0 = ��, 1 = ��, 2 = ȭ, 3 = ��, 4 = ��, 5 = ��, 6 = ��
	start_date = sum % 7;

	// ���� year, month ���� ���
	printf("\n\t===================================================\n");
	printf("\n\t\t\t   %d�� %d��\n", inputYear, inputMonth);
	// ���� ���
	printf("\n\t---------------------------------------------------");
	printf("\n\t��\t��\tȭ\t��\t��\t��\t��");
	printf("\n\t---------------------------------------------------\n");
	// �� ���
	// 1�� ���� ���� ����
	for (int i = 0; i < start_date; i++) {
		printf("\t");
	}

	// ��¥ ����
	for (int i = 1; i <= total_days[inputMonth - 1]; i++) {
		printf("\t%2d  ", i);

		// start_date�� 6�� �Ǹ�, 7���� �� �ٿ� ��� ä�����Ƿ� �� ���� �ٷ� ��������ش�.
		if (start_date == 6) {
			printf("\n\n");
			// 0���� �ʱ�ȭ�ؼ� ���� �ٺ��� �ٽ� ����.
			start_date = 0;
		}
		else {
			start_date++;
		}
	}
	printf("\n");
}

// ����, ��� ������ ���� �Լ�
int leapYear(int year) {
	int leapyear;

	if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
		leapyear = 1;	// ������ ���, 1
	}
	else {
		leapyear = 0;	// ����� ���, 0
	}

	return leapyear;	// ����,��� �Ǵ��� �� ��ȯ
}



//���� ȭ�� �Լ�
void info() {
	int infoMenu;
	printf("\n\n\n	1. ���ǻ��� 2. �ϱ��Է� 3. ���� ���� ��ġ 0. ���θ޴�\n\n\n");

	printf("	-------------------------------------------------\n");
	printf("	������Ʈ �������� ���̾ �ۼ� ���α׷��Դϴ�.\n");
	printf("	ȿ�������� ���̾ ������ �����ϴµ� ������ �ݴϴ�.\n");
	printf("	���α׷��� ����ؼ� ȿ�������� ������ �����غ�����. \n");
	printf("	--------------------------------------------------\n");
	printf("			:");

	while (1)
	{
		scanf_s("%d", &infoMenu);
		system("cls");
		switch (infoMenu) {
		case 1:
			printf("\n\n\n	1. ���ǻ��� 2. �ϱ��Է� 3. ���� ���� ��ġ 0. ���θ޴�\n\n\n");
			printf("	�� �λ����� �Ϸ縦 �������.\n	�� ���������ٸ� �ٽý������ּ���\n");
			printf("	�� ��� �̿��� ������ �����ּ���.\n	�� �� ���̾�� ��ȣ���� ���մϴ�(������Ʈ����)\n");

			printf("			:");
			break;
		case 2:
			printf("\n\n\n	1. ���ǻ��� 2. �ϱ��Է� 3. ���� ���� ��ġ 0. ���θ޴�\n\n\n");
			printf("	�ϱ⸦ �Է��Ϸ��� ��¥�� ������� �����ϰ� �ش� ��¥�� �ϱ⸦ �ۼ��ϸ�˴ϴ�.\n");
			printf("	�ϱ⸦ �ۼ� �� �ƴ϶� ����, ������ ���� ����� ����� �� �ֽ��ϴ�.\n");
			printf("	�ϱ⸦ �ۼ������� �ش� ��¥�� ã�Ƶ� �ۼ��� �ϱ⸦ Ȯ���غ�����~~\n");
			printf("	�ۼ��� �ϱ�� ���Ϸ� ������ (3. ���� ���� ��ġ)�� ���� ����Ǵ� ��ġ�� Ȯ���ϼ���.\n");

			printf("			:");
			break;
		case 3:
			printf("\n\n\n	1. ���ǻ��� 2. �ϱ��Է� 3. ���� ���� ��ġ 0. ���θ޴�\n\n\n");
			printf("	������ġ�� C:\projectMamuli\n");

			printf("			:");
			break;
		case 0:
			printf("\n\n\n	1. ���ǻ��� 2. �ϱ��Է� 3. ���� ���� ��ġ 0. ���θ޴�\n\n\n");
			printf("	3�� �� ����ȭ������ ���ư��ϴ�...\n");
			Sleep(1000);
			printf("	2�� �� ����ȭ������ ���ư��ϴ�...\n");
			Sleep(1000);
			printf("	1�� �� ����ȭ������ ���ư��ϴ�...\n");
			Sleep(1000);

			system("cls");
			return;

		default:
			printf("\n\n\n	1. ���ǻ��� 2. �ϱ��Է� 3. ���� ���� ��ġ 0. ���θ޴�\n\n\n");
			printf("	����1, 2, 3, 0 �߿� �Է��ϼ������\n");
			printf("			:");
			break;

		}

	}
}




// �Է�â �Լ�
void inputScreen(year, month) {
	system("cls");
	printCalender(year, month);
	int getch;											// getchar�� ���ϰ��� ������ ����(EOF�� ��ȯ���� �ޱ� ����)
	unsigned int index = 0;
	int choice1 = 0, choice2 = 0, check = 0;

	// ���� ����
	makeFolder(year, month);

	// ���� �̸� �� ���� ��� �����
	printf("\n\n\t%s�� ��¥ �Է�(ex.20220525): ", screenData.strMonth);
	scanf("%s", screenData.titleDay);
	system("cls");

	strcpy(screenData.fileName, screenData.titleDay);				// ex)20220601
	strcat(screenData.fileName, ".txt");							// ex)20220601.txt
	strcat(screenData.strPath, "\/");								// ex)/projectMamuli/2022/06/
	strcat(screenData.strPath, screenData.fileName);				// ex)/projectMamuli/2022/06/20220601.txt

	// ���� ���� ���� Ȯ��
	check = checkFileExists();

	// -------------- ���� ���� ���� --------------
	FILE* file;

	file = fopen(screenData.strPath, "at");

	// ������ �������� ������ ���� �ۼ��Ѵ�.
	if (check == 0) {
		// ���� �ۼ��� ������ �ʱ�ȭ �����ʰ� "�߰� �ۼ�"�� ��.
		printTitle();
		// ���Ͽ� day, ���� �ֱ�
		fputs("-------------------------------------------------------------------\n", file);
		fputs("\t\tday: ", file);
		fputs(screenData.titleDay, file);
		fputs(" \| ���� : ", file);
		fputs(screenData.titleName, file);
		fputs("\n-------------------------------------------------------------------\n", file);
		fputs("����: \n\n", file);
	}
	// ������ �����ϸ� �߰� ���� �Է��� �Ѵ�.
	else if (check == 1) {
		fclose(file);
		file = fopen(screenData.strPath, "r");
		while (feof(file) == 0) {
			fgets(screenData.getContents, 100, file);
			printf("%s\n", screenData.getContents);
		}
		fclose(file);
		printf("\n-------------------------------------------------------------------\n");
		printf("�߰� ���� �Է�: \n\n");
		file = fopen(screenData.strPath, "at");
	}


	// ���Ͽ� ���� �ֱ�
	getchar();
	while (1) {
		getch = getchar();
		if (getch == -1) {
			screenData.input[index] = NULL;				// NULL���� ������, ctrl + z ���� �� ���� ������ ������ �����.
			break;
		}
		screenData.input[index] = getch;				// ���� �ϳ��� screenData.input[index]�� ���.
		index++;
	}
	fprintf(file, "%s\n", screenData.input);

	//fputs("\n", file);

	fclose(file);

	Sleep(500);
	printSaveInfo();

	while (1) {
		// ��� ����1
		system("cls");
		printf("\n-------------------------------------------------------------------\n");
		printf("1. �ۼ��� ���� ����\t2. ����ȭ��\n: ");
		scanf("%d", &choice1);

		if (choice1 == 1) {
			system("cls");
			// ���� ���� �����ͼ� ����ϱ�
			file = fopen(screenData.strPath, "r");
			while (feof(file) == 0) {
				fgets(screenData.getContents, 100, file);
				printf("%s", screenData.getContents);
			}
			fclose(file);


			printf("-------------------------------------------------------------------\n");
			// ��� ����2
			printf("1. ����\t2. ����ȭ��\n: ");
			scanf("%d", &choice2);

			switch (choice2) {
				// 1. �����ϱ�
			case 1:

				printf("\n\n============================== ����ȭ�� =============================\n\n");

				// Ÿ��Ʋ ���
				printTitle();

				file = fopen(screenData.strPath, "wt");


				// ���Ͽ� day, ���� �ֱ�
				fputs("-------------------------------------------------------------------\n", file);
				fputs("\t\tday: ", file);
				fputs(screenData.titleDay, file);
				fputs(" \| ���� : ", file);
				fputs(screenData.titleName, file);
				fputs("\n-------------------------------------------------------------------\n", file);
				fputs("����: \n\n", file);

				// ���Ͽ� ���� �ֱ�
				getchar();
				while (1) {
					getch = getchar();
					if (getch == -1) {
						screenData.input[index] = NULL;				// NULL���� ������, ctrl + z ���� �� ���� ������ ������ �����.
						break;
					}
					screenData.input[index] = getch;				// ���� �ϳ��� screenData.input[index]�� ���.
					index++;
				}
				fprintf(file, "%s\n", screenData.input);

				//fputs("\n", file);

				fclose(file);

				Sleep(500);
				printSaveInfo();
				break;

				// 2. ����ȭ������ �̵�
			case 2:
				system("cls");
				printf("\n-------------------------------------------------------------------\n");
				printf("	2�� �� ����ȭ������ ���ư��ϴ�...\n");
				Sleep(1000);
				printf("	1�� �� ����ȭ������ ���ư��ϴ�...\n");
				printf("-------------------------------------------------------------------\n");
				Sleep(1000);
				break;
			default:
				system("cls");
				printf("\n-------------------------------------------------------------------\n");
				printf("1�� 2 �� �ϳ��� �����ϼ���.");
				printf("\n-------------------------------------------------------------------\n");
				continue;
			}
		}
		else if (choice1 == 2) {
			printf("\n-------------------------------------------------------------------\n");
			printf("	2�� �� ����ȭ������ ���ư��ϴ�...\n");
			Sleep(1000);
			printf("	1�� �� ����ȭ������ ���ư��ϴ�...\n");
			printf("\n-------------------------------------------------------------------\n");
			Sleep(1000);
			break;
		}
		else {
			printf("\n-------------------------------------------------------------------\n");
			printf("\n1�� 2 �� �� �ϳ� �����Ͻÿ�.\n");
			printf("\n-------------------------------------------------------------------\n");
		}
	}
}


// ���� ���� ���� üũ �Լ�
int checkFileExists() {
	FILE* file;
	if (file = fopen(screenData.strPath, "r")) {
		fclose(file);
		return 1;
	}
	return 0;
}


// ���� ���� �Լ�
void makeFolder(year, month) {
	strcpy(screenData.strProjectFolder, "c:\\projectMamuli");
	strcpy(screenData.basic, "projectMamuli");

	// int�� year, month�� ���ڿ��� ��ȯ
	sprintf(screenData.strYear, "%d", year);
	sprintf(screenData.strMonth, "%d", month);

	// -------------- ���� ���� ���� --------------
	// c����̺꿡 projectMamuli ���� ����
	mkdir(screenData.strProjectFolder);

	// ���� ���� ����
	strcpy(screenData.strPath, "\/");
	strcat(strcat(strcat(screenData.strPath, screenData.basic), "\/"), screenData.strYear);
	// -> ex. /projectMamuli/2022
	mkdir(screenData.strPath);

	// �� ���� ����
	strcat(strcat(screenData.strPath, "\/"), screenData.strMonth);
	// -> ex. /projectMamuli/2022/06
	mkdir(screenData.strPath);
}


// inputScreen ��¥ ���� �Լ�
void printTitle() {
	printf("----------------------------------------\n");
	printf("day: %s | ���� : ", screenData.titleDay);
	scanf("%s", screenData.titleName);
	printf("----------------------------------------");

	printf("\n[���� ������: enter -> ctrl + z -> enter]\n");
	printf("���� : \n\n");
}


// ���� ���� �ȳ�����
void printSaveInfo() {
	for (int i = 0; i < 2; i++) {
		system("cls");
		printf("\n\n\n\n\t\t**************\n");
		printf("\n\t\t���� ������.\n");
		printf("\n\t\t**************\n");
		Sleep(300);
		system("cls");
		printf("\n\n\n\n\t\t**************\n");
		printf("\n\t\t���� ������..\n");
		printf("\n\t\t**************\n");
		Sleep(300);
		system("cls");
		printf("\n\n\n\n\t\t**************\n");
		printf("\n\t\t���� ������...\n");
		printf("\n\t\t**************\n");
		Sleep(300);
	}
}



// ���̾ â �Լ�
void diary() {
	int year, month;
	int choice1 = 0, choice2 = 0;
	FILE* file;

	struct _finddatai64_t findData;
	intptr_t hFile;
	char path[] = "/*.*";
	char prePath[40], postPath[40];

	while (1) {
		system("cls");
		printf("���ϴ� ��¥ �Է�(ex. 2022 06): ");
		scanf("%d %d", &year, &month);

		if (year <= 2000 || year >= 3000) {
			system("cls");
			printf("\n--------------------------------------------------------\n");
			printf("******************* Warning *******************\n\n2000�⵵ �̻�, 3000�⵵ ���� ���ڸ� �����ּ���!\n");
			printf("\n--------------------------------------------------------");
			Sleep(2500);
			continue;
		}
		if (month < 1 || month > 12) {
			system("cls");
			printf("\n--------------------------------------------------------\n");
			printf("******************* Warning *******************\n\n1�� ~ 12���� ���� �Է����ּ���!\n");
			printf("\n--------------------------------------------------------");
			Sleep(2500);
			continue;
		}

		// ��� �����ϱ�
		sprintf(diaryData.year, "%d", year);							// int���� year, month���� ���ڿ� ���¹ٲ۵�, diaryData.year ������ �־���.
		sprintf(diaryData.month, "%d", month);

		strcpy(diaryData.fileName, diaryData.year);						// ex)2022
		strcat(diaryData.fileName, "\/");								// ex)2022/
		strcat(diaryData.fileName, diaryData.month);					// ex)2022/5
		strcpy(diaryData.strPath, "\/projectMamuli\/");					// ex)/projectMamuli/
		strcat(diaryData.strPath, diaryData.fileName);					// ex)/projectMamuli/2022/5


		// �� ������ �̿��ϱ� ���� ��� ����
		strcpy(diaryData.filePath, diaryData.strPath);					// filePath�� ���� copy�ص�.
		strcat(diaryData.filePath, "/");								// ex)/projectMamuli/2022/5/

		system("cls");
		printf("\n�Է� ��¥: %s %s\n\n", diaryData.year, diaryData.month);


		strcat(diaryData.strPath, path);

		// ���� ���� ���� Ȯ�� �� ���� ��� ���
		if ((hFile = _findfirsti64(diaryData.strPath, &findData)) == -1L) {
			switch (errno) {
			case ENOENT:
				printf("������ �����ϴ�.");	break;
			case EINVAL:
				printf(stderr, "�߸��� ��� �̸��Դϴ�..\n"); exit(1); break;
			case ENOMEM:
				printf(stderr, "�޸𸮰� �����ϰų� ���� �̸��� �ʹ� ��ϴ�.\n"); exit(1); break;
			default:
				printf(stderr, "�˼����� ������ �߻��߽��ϴ�.\n"); exit(1); break;
			}
		}
		else {
			printf("----------------------------- ���� ��� -----------------------------\n\n");
			do {
				printf("%s\n", findData.name);
			} while (_findnexti64(hFile, &findData) == 0);
			_findclose(hFile);
		}


		// ��¥ ���Է� or ����ȭ��
		printf("\n\n======================================================================");
		printf("\n1. ��¥ ���Է�     2. �ۼ��� ���� ����     3. �����ϱ�     4. ����ȭ��\n: ");
		scanf("%d", &choice1);

		if (choice1 == 1) {
			system("cls");
			printf("\n\n-------------------------------------------------------------------\n");
			printf("\t1�� �� ��¥ ���Է� â���� �̵��մϴ�..\n");
			printf("-------------------------------------------------------------------\n");
			Sleep(1000);
			system("cls");
			continue;
		}
		else if (choice1 == 2) {
			printf("\n\n===================================================================\n");
			printf("���ϴ� ���ϸ� �Է�: ");
			scanf("%s", diaryData.inputFileName);
			// ���� ���� �����ͼ� ����ϱ�
			strcat(diaryData.filePath, diaryData.inputFileName);
			strcat(diaryData.filePath, ".txt");								// ex./projectMamuli/2022/6/20220601.txt

			system("cls");
			file = fopen(diaryData.filePath, "r");
			while (feof(file) == 0) {
				fgets(diaryData.getContents, 100, file);
				printf("%s\n", diaryData.getContents);
			}
			fclose(file);

			printf("\n\n===================================================================\n");
			printf("1. ����ȭ��     2. ����ȭ��\n: ");
			scanf("%d", &choice2);
			if (choice2 == 1) {
				system("cls");
				printf("\n-------------------------------------------------------------------\n");
				printf("	1�� �� ����ȭ������ ���ư��ϴ�...\n");
				printf("-------------------------------------------------------------------\n");
				Sleep(1000);
				continue;
			}
			else {
				system("cls");
				printf("\n-------------------------------------------------------------------\n");
				printf("	1�� �� ����ȭ������ ���ư��ϴ�...\n");
				printf("-------------------------------------------------------------------\n");
				Sleep(1000);
				system("cls");
				break;
			}
		}
		else if (choice1 == 3) {

			printf("\n\n===================================================================\n");
			printf("������ ���ϸ� �Է�: ");
			scanf("%s", diaryData.deleteFileName);
			// ������ ���� �ҷ��ͼ� �����ϱ�

			// ���� ���
			strcat(diaryData.filePath, diaryData.deleteFileName);
			strcat(diaryData.filePath, ".txt");								// ex./projectMamuli/2022/6/20220601.txt
			printf("�������: %s\n", diaryData.filePath);
			Sleep(1000);


			// �ٲ� ���
			strcpy(trashData.strTrashFolder, "/projectMamuli/trash/");
			strcpy(trashData.filePath, trashData.strTrashFolder);			// c:\\projectMamuli/trash/
			strcat(trashData.filePath, diaryData.deleteFileName);			// c:\\projectMamuli/trash/20220601
			strcat(trashData.filePath, ".txt");								// c:\\projectMamuli/trash/20220601.txt
			printf("�ٲ� ���: %s\n", trashData.filePath);
			Sleep(1000);


			strcpy(prePath, diaryData.filePath);
			strcpy(postPath, trashData.filePath);


			if (moveToTrashcan(prePath, postPath) == 0)
			{
				system("cls");
				remove(diaryData.filePath);
				printf("\n---------------------------------------------------------\n");
				printf("	���� ������...");
				printf("\n---------------------------------------------------------\n");
				Sleep(2000);
				system("cls");
				printf("\n---------------------------------------------------------\n");
				printf("     ���������� �̵��Ͽ����ϴ�.\n");
				printf("     ������ ����: %s", postPath);
				printf("\n---------------------------------------------------------\n");
				Sleep(2000);
			}
			else
			{
				system("cls");
				printf("\n---------------------------------------------------------\n");
				printf("	���� ������...");
				printf("\n---------------------------------------------------------\n");
				Sleep(2000);
				printf("\n---------------------------------------------------------\n");
				perror("	���� ���� �����С�");
				printf("\n---------------------------------------------------------\n");
				Sleep(2000);
			}

		}
		else if (choice1 == 4) {
			system("cls");
			printf("\n-------------------------------------------------------------------\n");
			printf("\n\t2�� �� ����ȭ������ ���ư��ϴ�...\n");
			Sleep(1000);
			printf("\t1�� �� ����ȭ������ ���ư��ϴ�...\n\n");
			printf("\n-------------------------------------------------------------------\n");
			Sleep(1000);
			system("cls");
			break;
		}
		else {
			system("cls");
			printf("\n-------------------------------------------------------------------\n\n");
			printf("********** Warning **********\n\n�߸� �Է��Ͽ����ϴ�.\n");
			printf("\n-------------------------------------------------------------------");
			Sleep(2000);
			system("cls");
		}
	}
}



//���������� �̵� �Լ�
int moveToTrashcan(char* prePath, char* postPath) {
	FILE* fp1, * fp2;
	char buffer[1000] = { 0, };

	printf("%s\n", prePath);
	printf("%s\n", postPath);

	fp1 = fopen(prePath, "r");
	fp2 = fopen(postPath, "w");


	if (fp1 == NULL) {
		printf("���� ������ �� �� �����ϴ�.");
		return -1;
	}

	if (fp2 == NULL) {
		printf("���� ������ �� �� �����ϴ�.");
		return -1;
	}

	while (fgets(buffer, 500, fp1) != NULL) {
		fgets(buffer, 500, fp1);
		fputs(buffer, fp2);
	}

	//printf("���� ���������� �Ǿ����ϴ�.");

	fclose(fp1);
	fclose(fp2);

	return 0;
}


// ������ �Լ�
void trashcan() {
	system("cls");
	struct _finddatai64_t findData;
	intptr_t hFile;
	char path[] = "/*.*";
	char basePath[40];
	int choice = 0;

	strcpy(basePath, "/projectMamuli/trash");
	strcat(basePath, path);

	while (1) {
		// ���� ���� ���� Ȯ�� �� ���� ��� ���
		if ((hFile = _findfirsti64(basePath, &findData)) == -1L) {
			switch (errno) {
			case ENOENT:
				printf("������ �����ϴ�.");	break;
			case EINVAL:
				printf(stderr, "�߸��� ��� �̸��Դϴ�..\n"); exit(1); break;
			case ENOMEM:
				printf(stderr, "�޸𸮰� �����ϰų� ���� �̸��� �ʹ� ��ϴ�.\n"); exit(1); break;
			default:
				printf(stderr, "�˼����� ������ �߻��߽��ϴ�.\n"); exit(1); break;
			}
		}
		else {
			printf("------------------------ ���� ��� ------------------------\n\n");
			do {
				printf("%s\n", findData.name);
			} while (_findnexti64(hFile, &findData) == 0);
			_findclose(hFile);
		}

		printf("\n\n=========================================================\n");
		printf("1. ����ȭ��\n:");
		scanf_s("%d", &choice);
		if (choice == 1) {
			printf("\n---------------------------------------------------------\n");
			printf("\t1�� �� ����ȭ������ ���ư��ϴ�...\n");
			printf("---------------------------------------------------------\n");
			Sleep(1000);
			system("cls");
			break;
		}
		else {
			break;
		}
	}
}