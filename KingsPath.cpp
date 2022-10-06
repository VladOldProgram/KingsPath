/**
 * KingsPath.cpp - программа для нахождения количества способов,
 * какими шахматный король может обойти доску размера n x m
 * и вернуться в исходную клетку
 *
 * Copyright (c) 2021, Vladislav Shkut <shkut@cs.petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <iostream>
#include <fstream>

using namespace std;

int pathsNumber = 0;

void GetKingPathsNumber(int n, int m, int x, int y, int stepNumber, int** gameBoard, int* kingMovesX, int* kingMovesY)
{
	gameBoard[x][y] = stepNumber;
	stepNumber++;

	for (int i = 0; i < 8; i++) {
		int newX = x + kingMovesX[i];
		int newY = y + kingMovesY[i];

		if (i == 0 && n == 1 && m == 1) {
			pathsNumber++;
			break;
		}

		if (newX < 0 || newY < 0 || newX > n - 1 || newY > m - 1 || gameBoard[newX][newY] != 0)
			continue;

		if (stepNumber == n * m) {
			if ((newX == 0 && newY == 0) || (newX == 0 && newY == 1) || (newX == 1 && newY == 1) || (newX == 1 && newY == 0))
				pathsNumber++;
			gameBoard[newX][newY] = 0;
			continue;
		}

		if (stepNumber > n * m) return;

		GetKingPathsNumber(n, m, newX, newY, stepNumber, gameBoard, kingMovesX, kingMovesY);

		gameBoard[newX][newY] = 0;
	}
}

int main()
{
	ifstream fin("input.txt");
	int n, m;
	fin >> n;
	fin >> m;
	fin.close();

	int** gameBoard = new int*[n];
	for (int i = 0; i < n; i++)
		gameBoard[i] = new int[m];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			gameBoard[i][j] = 0;
	int kingMovesX[8] = { 0, 1, 1,  1,  0, -1, -1, -1 };
	int kingMovesY[8] = { 1, 1, 0, -1, -1, -1,  0,  1 };

	GetKingPathsNumber(n, m, 0, 0, 1, gameBoard, kingMovesX, kingMovesY);

	ofstream fout("output.txt");
	fout << pathsNumber;
	fout.close();

	for (int i = 0; i < n; i++)
		delete[] gameBoard[i];
	return 0;
}