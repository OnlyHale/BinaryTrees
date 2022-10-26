/***************************************************************************************
*Project Name : BinaryTrees                                                            *
*File Name    : BinaryTrees.cpp                                                        *
*Language     : CPP,MSVS ver 2015 and above                                            *
*Programmers : Ратников Роман Олегович,группа:М3О-210Б-20                              *
*Modified By  :                                                                        *
*Created      : 13/12/2021                                                             *
*Last Revision: 14/12/2021                                                             *
*Comment      :Бинарные деревья       	                                               *
***************************************************************************************/
#include <Windows.h>
#include <iostream>
#include <iomanip>

#define N 20;
using namespace std;

struct Node

{
	int value;
	Node* parent;
	Node* childLeft;
	Node* childRight;

};

Node* root = NULL;

//Функция создания дерева
void CreateTree(int* values, int valuesCount);

// Функция печати узла

void printNode(Node* currentNode);

// Функция печати дерева
void printTree(Node* currentNode, int level);

// Функция подсчёта уровней
void countLevels(Node* currentNode, int& level);

// Функция подсчёта положительных и отрицательных чисел
void WhoIsMore(Node* currentNode, int& countPositive, int& countNegative);

// Функция подсчёта узлов
void countNodes(Node* currentNode, int& nodeCount);

// Функция поиска узла
void findNode(Node* currentNode, int findValue, Node** findedNode);

// Функция удаления узла
void delNode(Node* nodeToDel, Node** tree);

// Функция добавления узла
void addNode(Node* currentNode, int newValue);

// Обход дерева( прямой)
void treeBypass(Node* currentNode);


int main()

{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int* valueArray; //массив значений
	int valueArrLen = N; //число значений
	int treeLevels = 0; //счетчик уровней дерева
	int nodeCount = 0; //счетчик узлов в дереве
	int countPositive = 0; // счётчик положительных чисел
	int countNegative = 0; // счётчик отрицательных чисел
	int userInput; //ввод пользователя

	Node* tree = new Node();//ссылка на корень дерева

	Node* findedNode; //ссылка на найденый узел

	

	//создаем массив значений

	valueArray = new int[valueArrLen] {0, -100, 50, 100, -26, 7, -29, 34, -49, 77, -51, 21, -19, 3, -16, 75, -5 ,48 , -8 ,27};

	

	while (true)

	{

		if (root!=NULL)

		{

			cout << "Tree :\n";

			printTree(root, 0);

			treeLevels = 0;

			countLevels(root, treeLevels); //считаем число уровней

			

			

			nodeCount = 0;

			countNodes(root, nodeCount); //считаем узлы

			countNegative = 0;

			countPositive = 0;

			WhoIsMore(root, countPositive, countNegative);


			cout << "Levels : " << treeLevels - 1 << endl;

			cout << "NodeCt : " << nodeCount << endl;

			cout << "Count Positive : " << countPositive << endl;

			cout << "Count Negative : " << countNegative << endl;

			if (countPositive < countNegative)
			{
				cout << " Отрицательных чисел больше" << endl;
			}
			else if (countPositive > countNegative)
			{
				cout << " Положительных чисел больше" << endl;
			}
			else
			{

				cout << " Отрицательных и положительных чисел одинаковое количество" << endl;
			}

		}

		else

		{

			cout << "Дерева нет" << endl;

		}

		cout << "-----------------------------\n" << endl;

		cout << "1) Удалить элемент\n";

		cout << "2) Добавить элемент\n";

		cout << "3) Обход дерева\n";

		cout << "4) Создать дерево\n";

		cout << "5) Поиск узла\n";

		cout << "0) Выход\n";

		cout << "-----------------------------\n";

		cout << " Введите номер комнады:";

		cin >> userInput;

		

		system("cls");

		if (userInput == 0)
		{
			cout << " Завершение программы " << endl;
			break;
		}


		switch (userInput)

		{

		case 1:

				if(root!=NULL)

				{
					cout << " Введите значение узла " << endl;
					cin >> userInput;

					cin.ignore();

					system("cls");

					findNode(root, userInput, &findedNode);

					cout << "\t\t Исходное дерево \n\n";
					printTree(root, 0);

					delNode(findedNode, &root);

					

				}

				

			break;

			case 2:

				if (root!=NULL)

				{
					cout << " Введите значение: " << endl;
					cin >> userInput;

					cin.ignore();

					system("cls");

					addNode(root, userInput);

				}


				break;

			case 3:

				if (root!=NULL)

				{
					printTree(root, 0);
					treeBypass(root);

					system("pause");

					system("cls");

				}


				break;

			case 4:

				if (root!=NULL)

				{

					cout << "Дерево уже есть" << endl;

				}

				else

				{

					CreateTree(valueArray, valueArrLen); //создаем дерево

					

				}//if..else

				break;

			case 5:
				if (root != NULL)
				{
					cout << " Введите значение:" << endl;
					cin >> userInput;

					findNode(root, userInput, &findedNode);

					printNode(findedNode);
					
				}
				break;
			default:

				cout << " Повторите ввод\n";

				continue;

				break;

		}//switch

	}//while

	delete[] valueArray;

	return 0;

}//main

//создаем дерево

void CreateTree(int* values, int valuesCount)

{

	Node* temp = new Node;

	root = temp;

	Node* currentNode;

	temp->value = values[0];

	temp->parent = NULL;

	temp->childLeft = NULL;

	temp->childRight = NULL;

	//в цикле заполняем дерево значениями

	for (int i = 1; i < valuesCount; i++)

	{

		currentNode = temp;

		//в цикле ищем подходящее место для нового значения

		while (true)

		{

			//проверяем куда идти влево или вправо

			if (currentNode->value < values[i])

			{

				if (currentNode->childRight == NULL)

				{

					//создаем новый листок

					currentNode->childRight = new Node();

					currentNode->childRight->parent = currentNode;

					currentNode = currentNode->childRight;

					//заполняем значения

					currentNode->value = values[i];

					currentNode->childRight = NULL;

					currentNode->childLeft = NULL;

					break;

				}

				else

				{

					currentNode = currentNode->childRight;

				}

			}

			else

			{

				if (currentNode->childLeft == NULL)

				{

					//создаем новый листок

					currentNode->childLeft = new Node();

					currentNode->childLeft->parent = currentNode;

					currentNode = currentNode->childLeft;

					//заполняем значения

					currentNode->value = values[i];

					currentNode->childRight = NULL;

					currentNode->childLeft = NULL;

					break;

				}

				else

				{

					currentNode = currentNode->childLeft;

				}//if..else

			}//if..else

		}//while

	}//for i



}//createTree

//печать одного узла

void printNode(Node* currentNode)

{

	if (currentNode != NULL)

	{

		cout << "Value : " << currentNode->value << '\n';

		cout << "Prev : ";

		if (currentNode->parent != NULL) cout << currentNode->parent->value;

		else cout << '-';

		cout << '\n';

		cout << "Left : ";

		if (currentNode->childLeft != NULL) std::cout << currentNode->childLeft->value;

		else cout << '-';

		cout << '\n';

		cout << "Right : ";

		if (currentNode->childRight != NULL) cout << currentNode->childRight->value;

		else cout << '-';

		cout << '\n';

	}

	else cout << "Not Exist\n";

}//printNode

//печатает дерево в консоль

void printTree(Node* currentNode, int level)

{

	if (currentNode)

	{

		printTree(currentNode->childRight, level + 1);

		for (int i = 0; i < level; i++)
		{
			cout << "     ";
		}

		cout << "|" << currentNode->value << '\n';

		printTree(currentNode->childLeft, level + 1);

	}

	else

	{

		for (int i = 0; i < level; i++)
		{
			cout << "     ";
		}


		cout << "-\n";

	}

}//printTree

//считает уровни у дерева или поддерева

void countLevels(Node* currentNode, int& level)

{

	int levelsLeft; //число уровней по левой ветке

	int levelsRight; //число уровней по правой ветке

	//пока ссылка не пустая

	if (currentNode)

	{

		//если не пустая, то прибавляем число уровней

		level++;

		//считаем число уровней

		levelsLeft = level;

		levelsRight = level;

		//ищем число уровней по правой и левой ветке

		countLevels(currentNode->childRight, levelsLeft);

		countLevels(currentNode->childLeft, levelsRight);

		//выбирает большее число уровней

		if (levelsLeft < levelsRight)
		{
			level = levelsRight;
		}

		else
		{
			level = levelsLeft;
		}

	}//if

}//countLevels


//определяет каких чисел больше - отрицательных или положительных

void WhoIsMore(Node* currentNode, int& countPositive, int& countNegative)

{

	//пока ссылка не пустая

	if (currentNode)

	{

		//если значение положительное

		if (currentNode->value>=0)

		{

			countPositive++;

		}
		else
		{
			countNegative++;
		}//if

		//идем дальше в левую и правую ветку

		WhoIsMore(currentNode->childLeft, countPositive,countNegative);

		WhoIsMore(currentNode->childRight, countPositive, countNegative);

	}//if

}//findEvenSum

//считает число узлов

void countNodes(Node* currentNode, int& nodeCount)

{

	if (currentNode)

	{

		nodeCount++;

		countNodes(currentNode->childLeft, nodeCount);

		countNodes(currentNode->childRight, nodeCount);

	}//if

}//countNodes

//ищет нужный узел

void findNode(Node* currentNode, int findValue, Node** findedNode)

{

	*findedNode = NULL;

	if (currentNode)

	{

		if (currentNode->value < findValue)
		{
			findNode(currentNode->childRight, findValue, findedNode);
		}

		else

			if (currentNode->value > findValue)
			{
				findNode(currentNode->childLeft, findValue, findedNode);
			}

			else *findedNode = currentNode;

	}//if

}//findNode

//удалить узел из дерева

void delNode(Node* nodeToDel, Node** tree)

{

	if (nodeToDel == NULL)
	{

		return;
	}


	//удаление последнего элемента

	if (!nodeToDel->childLeft && !nodeToDel->childRight && nodeToDel->value == (*tree)->value)

	{

		(*tree)->value = NULL;

		return;

	}//if

	Node* currentNode = nodeToDel;

	//случай удаления узла без детей

	if (!currentNode->childLeft && !currentNode->childRight)

	{

		if (currentNode->parent != NULL)

		{

			if (currentNode->parent->childLeft == currentNode)
			{
				currentNode->parent->childLeft = NULL;
			}

			else
			{
				currentNode->parent->childRight = NULL;
			}

		}

		else

		{

			*tree = NULL;

		}//if..else

		currentNode->parent = NULL;

	}

	else

		//случай удаления узла с одним ребенком

		if ((!currentNode->childLeft && currentNode->childRight) || (currentNode->childLeft && !currentNode->childRight))

		{

			if (currentNode->childLeft)

			{

				currentNode->childLeft->parent = currentNode->parent;

				if (currentNode->parent)

				{

					if (currentNode->parent->childLeft == currentNode) currentNode->parent->childLeft = currentNode->childLeft;

					else currentNode->parent->childRight = currentNode->childLeft;

				}

				else

				{

					*tree = currentNode;

					(*tree)->parent = NULL;

				}

			}

			else

			{

				currentNode->childRight->parent = currentNode->parent;

				if (currentNode->parent)

				{

					if (currentNode->parent->childLeft == currentNode) currentNode->parent->childLeft = currentNode->childRight;

					else currentNode->parent->childRight = currentNode->childRight;

				}

				else

				{

					*tree = currentNode;

					(*tree)->parent = NULL;

				}

			}

		}

		else

			//случай удаления узла с двумя детьми

			if (currentNode->childLeft && currentNode->childRight)

			{

				Node* heir = currentNode;

				heir = heir->childRight;

				//ищем у правого ребенка младшего ребенка по левой стороне

				while (heir->childLeft != NULL) heir = heir->childLeft;

				//если подходит только правый потомок

				if (currentNode->childRight == heir)

				{

					heir->childLeft = currentNode->childLeft;

					heir->parent = currentNode->parent;

					if (currentNode->parent)

					{

						if (currentNode->parent->childLeft == currentNode) currentNode->parent->childLeft = heir;

						else currentNode->parent->childRight = heir;

					}

					else

					{

						heir->parent = NULL;

						*tree = heir;

					}

					return;

				}//if

				if (heir->childRight)

				{

					heir->parent->childLeft = heir->childRight;

					heir->childRight->parent = heir->parent;

				}

				else heir->parent->childLeft = NULL;

				if (currentNode->parent)

				{

					if (currentNode->parent->childLeft == currentNode) currentNode->parent->childLeft = heir;

					else currentNode->parent->childRight = heir;

				}

				else *tree = heir;

				heir->childLeft = currentNode->childLeft;

				heir->childRight = currentNode->childRight;

				heir->parent = currentNode->parent;

				system("pause");

			}//if..else

	(*tree)->parent = NULL;

}//deleteNode

//добавить узел в дерево

void addNode(Node* currentNode, int newValue)

{

	//в цикле ищем подходящее место для нового значения

	while (true)

	{

		//проверяем куда идти влево или вправо

		if (currentNode->value < newValue)

		{

			if (currentNode->childRight == NULL)

			{

				//создаем новый листок

				currentNode->childRight = new Node();

				currentNode->childRight->parent = currentNode;

				currentNode = currentNode->childRight;

				//заполняем значения

				currentNode->value = newValue;

				currentNode->childRight = NULL;

				currentNode->childLeft = NULL;

				break;

			}

			else

			{

				currentNode = currentNode->childRight;

			}//if..else

		}

		else

		{

			if (currentNode->childLeft == NULL)

			{

				//создаем новый листок

				currentNode->childLeft = new Node();

				currentNode->childLeft->parent = currentNode;

				currentNode = currentNode->childLeft;

				//заполняем значения

				currentNode->value = newValue;

				currentNode->childRight = NULL;

				currentNode->childLeft = NULL;

				break;

			}

			else

			{

				currentNode = currentNode->childLeft;

			}//if..else

		}//if..else

	}//while

}//addNode

//обход дерева

void treeBypass(Node* currentNode)

{

	if (currentNode)

	{

		treeBypass(currentNode->childLeft);

		printNode(currentNode);

		cout << '\n';

		treeBypass(currentNode->childRight);

	}//if

}//treeBypass
