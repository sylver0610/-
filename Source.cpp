#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*ввод массива*/
void inputMatrix(int ***a,int row,int col)
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			cin >> (*a)[i][j];
}

/*вывод массива*/
void outputMatrix(int ***a,int row,int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			cout << (*a)[i][j] << " ";
		cout << endl;
	}
}

/*генерировать случайное значение для массива*/
void randomMatrix(int ***a,int row,int col)
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		(*a)[i][j] = rand() % 10;
}

/*скопировать данные массива a для массива b*/
void copyMatrix(int ***a,int ***b,int row,int col )
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			(*b)[i][j] = (*a)[i][j];
	}
}

/*выделить память для массива a и присвоить нулевое значение элементам массива*/
void copyMatrixNull(int ***a,int row )
{
	*a = new int* [row];
	for (int i = 0; i < row; i++)
	{
		(*a)[i] = new int[row];
		for (int j = 0; j < row; j++)
			(*a)[i][j] = 0;
	}
}

/*выделить память для массива a*/
void allocation(int ***a,int row,int col)
{
	*a= new int* [row];	
	for (int i = 0; i < row; i++)
		(*a)[i] = new int[col];
}

/*выделить память для массива a и скопировать данные массива b для массива a*/
void allocCopy(int ***a,int square,int ***b, int rowB, int colB)
{
	*a=new int* [square];
	for (int i = 0;i<square;i++)
		{		
			(*a)[i] = new int[square];
			for (int j=0;j<square;j++)
				(*a)[i][j] = (*b)[i+rowB][j+colB];
		}
}

int main()
{
	srand(time(NULL));
	int n1, m1, n2, m2, k, l = 2;
	system("chcp 866");
	cout << "Welcome to the program" << endl <<
		"fast matrix multiplication by the Strassen method\n\n";

	///////////////////////////////////////////////////////////////////////////////
	////////////////////Ввод размеров матрицы пользователем////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	do
	{
		cout << "Enter the dimensions of the first matrix\n";
		cin >> n1 >> m1;
	} while (n1 <= 0 || m1 <= 0);
	do
	{
		cout << "Enter the dimensions of the second matrix\n";
		cin >> n2 >> m2;
	} while (n2 <= 0 || m2 <= 0);
	
	int **M1,**M2;
	allocation(&M1,n1,m1);
	allocation(&M2,n2,m2);	
	

	///////////////////////////////////////////////////////////////////////////////
	////////////////Выбор способа заполнения и заполнение матриц///////////////////
	///////////////////////////////////////////////////////////////////////////////

	do
	{
		cout << "Choose a way to fill in the matrices\n" <<
			"1 - Manually \n2 - Randomly\n";
		cin >> k;
	} while (k < 1 || k > 2);
	switch (k)
	{
	case 1:
		inputMatrix(&M1,n1,m1);
		inputMatrix(&M2,n2,m2);

		cout << "\nMatrix 1\n\n";
		outputMatrix(&M1,n1,m1);

		cout << "\nMatrix 2\n\n";
		outputMatrix(&M2,n2,m2);	

		break;
	case 2:
		randomMatrix(&M1,n1,m1);		
		randomMatrix(&M2,n2,m2);		
				
		cout << "\nMatrix 1\n\n";
		outputMatrix(&M1,n1,m1);		
					
		cout << "\nMatrix 2\n\n";
		outputMatrix(&M2,n2,m2);	
								
		break;
	}

	///////////////////////////////////////////////////////////////////////////////
	/////////////////Приведение матриц к требуемому размеру////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	while (l < n1 || l < n2 || l < m1 || l < m2)
		l *= 2;

	int **M3, **M4;
	copyMatrixNull(&M3,l);
	copyMatrixNull(&M4,l);														
					
	copyMatrix(&M1,&M3,n1,m1);
	copyMatrix(&M2,&M4,n2,m2);	
	
	cout << "\nReduced matrices\n";

	cout << "\nMatrix 1\n\n";	
	outputMatrix(&M3,l,l);
				
	cout << "\nMatrix 2\n\n";
	outputMatrix(&M4,l,l);
					
	///////////////////////////////////////////////////////////////////////////////
	///////////////Разбиение матриц на подматрицы и их заполнение//////////////////
	///////////////////////////////////////////////////////////////////////////////

							
	int **mat1, **mat2, **mat3, **mat4, **mat5, **mat6, **mat7, **mat8;
	allocCopy(&mat1,l/2,&M3,0,0);
	allocCopy(&mat2,l/2,&M3,0,l/2);
	allocCopy(&mat3,l/2,&M3,l/2,0);
	allocCopy(&mat4,l/2,&M3,l/2,l/2);
	
	allocCopy(&mat5,l/2,&M4,0,0);
	allocCopy(&mat6,l/2,&M4,0,l/2);
	allocCopy(&mat7,l/2,&M4,l/2,0);
	allocCopy(&mat8,l/2,&M4,l/2,l/2);
																	
																												
	///////////////////////////////////////////////////////////////////////////////
	////////////////////////Создание промежуточных матриц//////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int** p1, **p2, **p3, **p4, **p5, **p6, **p7;

	allocation(&p1,l/2,l/2);
	allocation(&p2,l/2,l/2);
	allocation(&p3,l/2,l/2);
	allocation(&p4,l/2,l/2);
	allocation(&p5,l/2,l/2);
	allocation(&p6,l/2,l/2);
	allocation(&p7,l/2,l/2);																																	

	///////////////////////////////////////////////////////////////////////////////
	////////////////////Вычисление значений промежуточных матриц///////////////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < l / 2; i++)
	{
		for (int j = 0; j < l / 2; j++)
		{
			p1[i][j] = 0;
			for (int z = 0; z < l / 2; z++)
			{
				p1[i][j] += (mat1[i][z] + mat4[i][z]) * (mat5[z][j] + mat8[z][j]);
			}

			p2[i][j] = 0;
			for (int z = 0; z < l / 2; z++)
			{
				p2[i][j] += (mat3[i][z] + mat4[i][z]) * mat5[z][j];
			}

			p3[i][j] = 0;
			for (int z = 0; z < l / 2; z++)
			{
				p3[i][j] += mat1[i][z] * (mat6[z][j] - mat8[z][j]);
			}

			p4[i][j] = 0;
			for (int z = 0; z < l / 2; z++)
			{
				p4[i][j] += mat4[i][z] * (mat7[z][j] - mat5[z][j]);
			}

			p5[i][j] = 0;
			for (int z = 0; z < l / 2; z++)
			{
				p5[i][j] += (mat1[i][z] + mat2[i][z]) * mat8[z][j];
			}

			p6[i][j] = 0;
			for (int z = 0; z < l / 2; z++)
			{
				p6[i][j] += (mat3[i][z] - mat1[i][z]) * (mat5[z][j] + mat6[z][j]);
			}

			p7[i][j] = 0;
			for (int z = 0; z < l / 2; z++)
			{
				p7[i][j] += (mat2[i][z] - mat4[i][z]) * (mat7[z][j] + mat8[z][j]);
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	///////////////////////Создание вспомогательных матриц/////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int** mat9, **mat10, **mat11, **mat12;
	allocation(&mat9,l/2,l/2);
	allocation(&mat10,l/2,l/2);
	allocation(&mat11,l/2,l/2);
	allocation(&mat12,l/2,l/2);

	///////////////////////////////////////////////////////////////////////////////
	////////////Подсчет значений вспомогательных матриц из промежуточных///////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < l / 2; i++)
	{
		for (int j = 0; j < l / 2; j++)
		{
			mat9[i][j] = p1[i][j] + p4[i][j] - p5[i][j] + p7[i][j];
			mat10[i][j] = p3[i][j] + p5[i][j];
			mat11[i][j] = p2[i][j] + p4[i][j];
			mat12[i][j] = p1[i][j] - p2[i][j] + p3[i][j] + p6[i][j];
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	///////////////////Создание результирующей матрицы/////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int **M5;
	allocation(&M5,l,l);	

	///////////////////////////////////////////////////////////////////////////////
	///////Занесение информации из вспомогательных матриц в результирующую/////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < l / 2; i++)
	{
		for (int j = 0; j < l / 2; j++)
		{
			M5[i][j] = mat9[i][j];
			M5[i][j + l / 2] = mat10[i][j];
			M5[i + l / 2][j] = mat11[i][j];
			M5[i + l / 2][j + l / 2] = mat12[i][j];
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	////////////////Выравнивание границ результирующей матрицы/////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int x = 0, f = 100, s = 100;
	for (int i = 0; i < l; i++)
	{
		x = 0;
		for (int j = 0; j < l; j++)
		{
			if (M5[i][j] != 0)
			{
				x++;
				f = 100;
			}
		}
		if (x == 0 && i < f)
		{
			f = i;
		}
	}
	for (int i = 0; i < l; i++)
	{
		x = 0;
		for (int j = 0; j < l; j++)
		{
			if (M5[j][i] != 0)
			{
				x++;
				s = 100;
			}
		}
		if (x == 0 && i < s)
		{
			s = i;
		}
	}

	int **M6;
	allocation(&M6,f,s);
	copyMatrix(&M5,&M6,f,s);		
			
	///////////////////////////////////////////////////////////////////////////////
	///////////////////Вывод результирующей матрицы////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	cout << "\nResulting matrix\n\n";
	outputMatrix(&M6,f,s);	
					
	system("pause");

	///////////////////////////////////////////////////////////////////////////////
	/////////////////////Очистка динамической памяти///////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < n1; i++)
		delete[] M1[i];
	for (int i = 0; i < n2; i++)
		delete[] M2[i];
	for (int i = 0; i < l; i++)
	{
		delete[] M3[i];
		delete[] M4[i];
		delete[] M5[i];
	}
	for (int i = 0; i < f; i++)
		delete[] M6[i];
	for (int i = 0; i < l / 2; i++)
	{
		delete[] mat1[i];
		delete[] mat2[i];
		delete[] mat3[i];
		delete[] mat4[i];
		delete[] mat5[i];
		delete[] mat6[i];
		delete[] mat7[i];
		delete[] mat8[i];
		delete[] mat9[i];
		delete[] mat10[i];
		delete[] mat11[i];
		delete[] mat12[i];
		delete[] p1[i];
		delete[] p2[i];
		delete[] p3[i];
		delete[] p4[i];
		delete[] p5[i];
		delete[] p6[i];
		delete[] p7[i];
	}
	delete[] M1, M2, M3, M4, M5, M6;
	delete[] mat1, mat2, mat3, mat4, mat5, mat6, mat7, mat8, mat9, mat10, mat11, mat12;
	delete[] p1, p2, p3, p4, p5, p6, p7;
}