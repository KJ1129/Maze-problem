#include<iostream>
#include<iomanip>
#include<ctime>
using namespace std;

void print(int **maze, int m, int n)//��X�g�c�αƪ�
{
	for (int i = 0; i < m + 2; i++)
	{
		for (int j = 0; j < n + 2; j++)
		{
			cout << setw(2) << maze[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

//�]�g�c���}�C�U����
void set_maze(int **maze, int m, int n)
{
	for (int i = 0; i < m + 2; i++)
	{
		for (int j = 0; j < n + 2; j++)
		{
			if (i == 0 || i == m + 1 || j == 0 || j == n + 1)//�~����� 1
			{
				maze[i][j] = 1;
			}
			else if (i == 1 && j == 1 || i == m && j == n)//�_�I�M���I�� 0
			{
				maze[i][j] = 0;
			}
			else //��l�]�ü� 0 �M 1
			{
				maze[i][j] = rand() % 2;
			}
		}
	}
}

void go(int **maze, int*arr, int m, int n, int M, int N, int step);
void goback(int *arr, int step,int m ,int n, int M, int N, int**maze);

int main()
{
	int m, n;//m ���g�c���C�ơAn �����
	cout << "�п�J�G���}�C����: ";
	cin >> m >> n;
	srand(time(0));//�ü�

	//�]�ʺA�G���}�C
	int**maze = new int*[m + 2]; //m:�}�C���Ĥ@���j�p

	for (int i = 0; i < m + 2; i++)//�ĤG���j�p
		maze[i] = new int[n + 2];
	int M = 1, N = 1;//(M,N)���Ҩ��쪺��m�A���w�]���_�I(1,1)
	int *arr = new int[(m * n) / 2];//���L�����|
	int step = 0;//step �����^������V

	set_maze(maze, m, n);//�I�s�A�]�g�c���}�C�U����
	print(maze, m, n);//�I�s�A��X�g�c
	cout << endl;
	maze[M][N] = 2;//���L����m�] 2
	go(maze, arr, m, n, M, N, step);//�I�s�A�}�l���g�c

	system("pause");
	return 0;
}

void go(int **maze, int*arr, int m, int n, int M, int N, int step)
{
	// 1:�W��, 2:�k�W, 3:�k, 4:�k�U, 5:�U, 6:���U, 7:��, 8:���W
	if (M == m && N == n)//�Y�w����(m,n)���I
	{
		cout << "�i�F���I" << endl;
		print(maze, m, n);
	}
	else if (maze[M - 1][N] == 0)//�Y�W��= 0,�h�W�観��

	{
		maze[M - 1][N] = 2;//���W���A�ñN���m���ȳ]��2
		print(maze, m, n);//��X���L�����G
		arr[step] = 5;//�x�s�^����V�A5���U��
		go(maze, arr, m, n, M - 1, N, step + 1);//�~��U�@�B���P�_�A����go��function
	}
	else if (maze[M - 1][N + 1] == 0)
	{
		maze[M - 1][N + 1] = 2;//���k�W���A�ñN���m���ȳ]��2
		print(maze, m, n);
		arr[step] = 6;
		go(maze, arr, m, n, M - 1, N + 1, step + 1);
	}
	else if (maze[M][N + 1] == 0)
	{
		maze[M][N + 1] = 2;//���k���A�ñN���m���ȳ]��2
		print(maze, m, n);
		arr[step] = 7;
		go(maze, arr, m, n, M, N + 1, step + 1);
	}
	else if (maze[M + 1][N + 1] == 0)
	{
		maze[M + 1][N + 1] = 2;//���k�U���A�ñN���m���ȳ]��2
		print(maze, m, n);
		arr[step] = 8;
		go(maze, arr, m, n, M + 1, N + 1, step + 1);
	}
	else if (maze[M + 1][N] == 0)
	{
		maze[M + 1][N] = 2;//���U���A�ñN���m���ȳ]��2
		print(maze, m, n);
		arr[step] = 1;
		go(maze, arr, m, n, M + 1, N, step + 1);
	}
	else if (maze[M + 1][N - 1] == 0)
	{
		maze[M + 1][N - 1] = 2;//�����U���A�ñN���m���ȳ]��2
		print(maze, m, n);
		arr[step] = 2;
		go(maze, arr, m, n, M + 1, N - 1, step + 1);
	}
	else if (maze[M][N - 1] == 0)
	{
		maze[M][N - 1] = 2;//�������A�ñN���m���ȳ]��2
		print(maze, m, n);
		arr[step] = 3;
		go(maze, arr, m, n, M, N - 1, step + 1);
	}
	else if (maze[M - 1][N - 1] == 0)
	{
		maze[M - 1][N - 1] = 2;//�����W���A�ñN���m���ȳ]��2
		print(maze, m, n);
		arr[step] = 4;
		go(maze, arr, m, n, M - 1, N - 1, step + 1);
	}
	else if ((maze[M - 1][N] == 1 || maze[M - 1][N] == 2) &&
		(maze[M - 1][N + 1] == 1 || maze[M - 1][N + 1] == 2) &&
		(maze[M][N + 1] == 1 || maze[M][N + 1] == 2) &&
		(maze[M + 1][N + 1] == 1 || maze[M + 1][N + 1] == 2) &&
		(maze[M + 1][N] == 1 || maze[M + 1][N] == 2) &&
		(maze[M + 1][N - 1] == 1 || maze[M + 1][N - 1] == 2) &&
		(maze[M][N - 1] == 1 || maze[M][N - 1] == 2) &&
		(maze[M - 1][N - 1] == 1 || maze[M - 1][N - 1] == 2) )//�Y�K�Ӥ�V�O���L��������A�h�S����
	{
		
		cout << "This route is not to Exit in this maze!";
		cout << endl;
		goback(arr, step -1, m, n, M, N, maze);	
	}
}

void goback(int *arr, int step,int m,int n, int M, int N, int**maze)//�J��S�����h���^��
{
	if (arr[step] == 1)
	{
		maze[M][N] = 1; //���^���A�ç⨫�L����m�] 1�A���_��
		arr[step] = 0;
		print(maze, m, n);
		go(maze, arr, m, n, M - 1, N, step);
	}
	else if (arr[step] == 2)
	{
		maze[M][N] = 1;
		arr[step] = 0;
		print(maze, m, n);
		go(maze, arr, m, n, M - 1, N + 1, step);
	}
	else if (arr[step] == 3)
	{
		maze[M][N] = 1;
		arr[step] = 0;
		print(maze, m, n);
		go(maze, arr, m, n, M, N + 1, step);
	}
	else if (arr[step] == 4)
	{
		maze[M][N] = 1;
		arr[step] = 0;
		print(maze, m, n);
		go(maze, arr, m, n, M + 1, N + 1, step);
	}
	else if (arr[step] == 5)
	{
		maze[M][N] = 1;
		arr[step] = 0;
		print(maze, m, n);
		go(maze, arr, m, n, M + 1, N, step);
	}
	else if (arr[step] == 6)
	{
		maze[M][N] = 1;
		arr[step] = 0;
		print(maze, m, n);
		go(maze, arr, m, n, M + 1, N - 1, step);
	}
	else if (arr[step] == 7)
	{
		maze[M][N] = 1;
		arr[step] = 0;
		print(maze, m, n);
		
		go(maze, arr, m, n, M, N - 1, step);
	}
	else if (arr[step] == 8)
	{
		maze[M][N] = 1;
		arr[step] = 0;
		print(maze, m, n);
		go(maze, arr, m, n, M - 1, N - 1, step);
	}
}
