#include<iostream>
#include<iomanip>
#include<ctime>
using namespace std;

void print(int **maze, int m, int n)//輸出迷宮及排版
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

//設迷宮中陣列各元素
void set_maze(int **maze, int m, int n)
{
	for (int i = 0; i < m + 2; i++)
	{
		for (int j = 0; j < n + 2; j++)
		{
			if (i == 0 || i == m + 1 || j == 0 || j == n + 1)//外牆全為 1
			{
				maze[i][j] = 1;
			}
			else if (i == 1 && j == 1 || i == m && j == n)//起點和終點為 0
			{
				maze[i][j] = 0;
			}
			else //其餘設亂數 0 和 1
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
	int m, n;//m 為迷宮的列數，n 為行數
	cout << "請輸入二維陣列維度: ";
	cin >> m >> n;
	srand(time(0));//亂數

	//設動態二維陣列
	int**maze = new int*[m + 2]; //m:陣列的第一維大小

	for (int i = 0; i < m + 2; i++)//第二維大小
		maze[i] = new int[n + 2];
	int M = 1, N = 1;//(M,N)為所走到的位置，先預設為起點(1,1)
	int *arr = new int[(m * n) / 2];//走過的路徑
	int step = 0;//step 紀錄回路的方向

	set_maze(maze, m, n);//呼叫，設迷宮中陣列各元素
	print(maze, m, n);//呼叫，輸出迷宮
	cout << endl;
	maze[M][N] = 2;//走過的位置設 2
	go(maze, arr, m, n, M, N, step);//呼叫，開始走迷宮

	system("pause");
	return 0;
}

void go(int **maze, int*arr, int m, int n, int M, int N, int step)
{
	// 1:上方, 2:右上, 3:右, 4:右下, 5:下, 6:左下, 7:左, 8:左上
	if (M == m && N == n)//若已走到(m,n)終點
	{
		cout << "可達終點" << endl;
		print(maze, m, n);
	}
	else if (maze[M - 1][N] == 0)//若上方= 0,則上方有路

	{
		maze[M - 1][N] = 2;//往上走，並將其位置的值設為2
		print(maze, m, n);//輸出走過的結果
		arr[step] = 5;//儲存回路方向，5為下方
		go(maze, arr, m, n, M - 1, N, step + 1);//繼續下一步的判斷，執行go的function
	}
	else if (maze[M - 1][N + 1] == 0)
	{
		maze[M - 1][N + 1] = 2;//往右上走，並將其位置的值設為2
		print(maze, m, n);
		arr[step] = 6;
		go(maze, arr, m, n, M - 1, N + 1, step + 1);
	}
	else if (maze[M][N + 1] == 0)
	{
		maze[M][N + 1] = 2;//往右走，並將其位置的值設為2
		print(maze, m, n);
		arr[step] = 7;
		go(maze, arr, m, n, M, N + 1, step + 1);
	}
	else if (maze[M + 1][N + 1] == 0)
	{
		maze[M + 1][N + 1] = 2;//往右下走，並將其位置的值設為2
		print(maze, m, n);
		arr[step] = 8;
		go(maze, arr, m, n, M + 1, N + 1, step + 1);
	}
	else if (maze[M + 1][N] == 0)
	{
		maze[M + 1][N] = 2;//往下走，並將其位置的值設為2
		print(maze, m, n);
		arr[step] = 1;
		go(maze, arr, m, n, M + 1, N, step + 1);
	}
	else if (maze[M + 1][N - 1] == 0)
	{
		maze[M + 1][N - 1] = 2;//往左下走，並將其位置的值設為2
		print(maze, m, n);
		arr[step] = 2;
		go(maze, arr, m, n, M + 1, N - 1, step + 1);
	}
	else if (maze[M][N - 1] == 0)
	{
		maze[M][N - 1] = 2;//往左走，並將其位置的值設為2
		print(maze, m, n);
		arr[step] = 3;
		go(maze, arr, m, n, M, N - 1, step + 1);
	}
	else if (maze[M - 1][N - 1] == 0)
	{
		maze[M - 1][N - 1] = 2;//往左上走，並將其位置的值設為2
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
		(maze[M - 1][N - 1] == 1 || maze[M - 1][N - 1] == 2) )//若八個方向是走過的或牆壁，則沒有路
	{
		
		cout << "This route is not to Exit in this maze!";
		cout << endl;
		goback(arr, step -1, m, n, M, N, maze);	
	}
}

void goback(int *arr, int step,int m,int n, int M, int N, int**maze)//遇到沒有路則往回走
{
	if (arr[step] == 1)
	{
		maze[M][N] = 1; //往回走，並把走過的位置設 1，堵起來
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
