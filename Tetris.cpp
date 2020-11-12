#include <iostream>
#include <Windows.h>
#include <thread>
#include <vector>

using namespace std;

// These are the tetris game pieces
wstring tetromino[7];
/*
Each piece is stored in a 16 character wstring
(i.e [0][1][2][3][4][5]...)
which can be thought of like a 2D array
(i.e
[00][01][02][03]
[04][05][06][07]
[08][09][10][11]
[12][12][14][15]
)
*/

/*
The following values determine the width and height
of the game field. The individual elements of the game
field will be stored as unisgned char.
*/
int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char* pField = nullptr;

/*
The following values determine the size
of the game window in which the game field
will appear.
*/
int nScreenWidth = 120; // Console screen size x (columns)
int nScreenHeight = 30; // Console screen size y (rows)


/*
The rotate function takes the above "2D array"
and rotates it clockwise. px and py represent the
x and y coordinates of each "cell".
The formulas represent the new x
and y coordinates of each "cell".
r determines how much to rotate by.
*/
int Rotate(int px, int py, int r)
{
	switch (r % 4) {
	case 0: return py * 4 + px; // 0 degrees
	case 1: return 12 + py - (px * 4); // 90 degrees
	case 2: return 15 - (py * 4) - px; // 180 degrees
	case 3: return 3 - py + (px * 4); // 270 degrees
	}
	return 0;
}

bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
{

	for (int px = 0; px < 4; px++)
		for (int py = 0; py < 4; py++)
		{
			// Get index into piece
			int pi = Rotate(px, py, nRotation);

			// Get index into field
			int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

			if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
			{
				if (nPosY + py >= 0 && nPosY + py < nFieldHeight)
				{
					if (tetromino[nTetromino][pi] == L'X' && pField[fi] != 0)
						return false;// Fail on first hit
				}
			}
		}

	return true;
}

int main() {

	// Create assets
	// Straight Tetromino
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");

	// Skew Tetromino 1
	tetromino[1].append(L"..X.");
	tetromino[1].append(L".XX.");
	tetromino[1].append(L".X..");
	tetromino[1].append(L"....");

	// Skew Tetromino 2
	tetromino[2].append(L".X..");
	tetromino[2].append(L".XX.");
	tetromino[2].append(L"..X.");
	tetromino[2].append(L"....");

	// Square Tetromino
	tetromino[3].append(L"....");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L"....");

	// T Tetromino
	tetromino[4].append(L"..X.");
	tetromino[4].append(L".XX.");
	tetromino[4].append(L"..X.");
	tetromino[4].append(L"....");

	// L Tetromino 1
	tetromino[5].append(L"....");
	tetromino[5].append(L".XX.");
	tetromino[5].append(L"..X.");
	tetromino[5].append(L"..X.");

	// L Tetromino 2
	tetromino[6].append(L"....");
	tetromino[6].append(L".XX.");
	tetromino[6].append(L".X..");
	tetromino[6].append(L".X..");

	pField = new unsigned char[nFieldWidth * nFieldHeight]; //Create play field buffer
	for (int x = 0; x < nFieldWidth; x++) // Board Boundary
		for (int y = 0; y < nFieldHeight; y++)
			pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;

	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	bool bGameOver = false;

	int nCurrentPiece = rand() % 7;
	int nCurrentRotation = 0;
	int nCurrentx = nFieldWidth / 2;
	int nCurrenty = 0;

	bool bKey[4];
	bool bRotateHold = false;

	int nSpeed = 20;
	int nSpeedCounter = 0;
	bool bForceDown = false;

	int nPieceCount = 0;
	int nScore = 0;

	vector<int> vLines;

	while (!bGameOver) {
		// GAME TIMING ======================================
		this_thread::sleep_for(50ms); // Small step = 1 game tick
		nSpeedCounter++;
		bForceDown = (nSpeedCounter == nSpeed);


		// INPUT ============================================
		for (int k = 0; k < 4; k++)								// R   L    D Z
			bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;


		// GAME LOGIC =======================================
		// Move game piece right
		nCurrentx += (bKey[0] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentx + 1, nCurrenty)) ? 1 : 0;

		// Move game piece left
		nCurrentx -= (bKey[1] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentx - 1, nCurrenty)) ? 1 : 0;

		// Move game piece down
		nCurrenty += (bKey[2] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentx, nCurrenty + 1)) ? 1 : 0;

		// Rotate game piece (& prevent wild spinning on key hold)
		if (bKey[3])
		{
			nCurrentRotation += (!bRotateHold && DoesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentx, nCurrenty)) ? 1 : 0;
			bRotateHold = true;
		}
		else {
			bRotateHold = false;
		}

		// Force the game piece down if it's time
		if (bForceDown) {
			// Increase Difficulty every 20 pieces
			nPieceCount++;
			if (nPieceCount % 20 == 0)
				if (nSpeed >= 10) nSpeed--;

			// Test if piece can be moved down
			if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentx, nCurrenty + 1)) {
				nCurrenty++; // Piece fits, so move it down one!
			}
			else {
				// Lock the current tetromino into the field
				for (int px = 0; px < 4; px++)
					for (int py = 0; py < 4; py++)
						if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
							pField[(nCurrenty + py) * nFieldWidth + (nCurrentx + px)] = nCurrentPiece + 1;

				// Check for any full horizontal lines
				for (int py = 0; py < 4; py++)
					if (nCurrenty + py < nFieldHeight - 1) {
						bool bLine = true;
						for (int px = 1; px < nFieldWidth - 1; px++)
							bLine &= (pField[(nCurrenty + py) * nFieldWidth + px]) != 0;

						if (bLine) {

							//Remove Line, set to =
							for (int px = 1; px < nFieldWidth - 1; px++)
								pField[(nCurrenty + py) * nFieldWidth + px] = 8;

							vLines.push_back(nCurrenty + py);
						}
					}

				nScore += 25;
				if (!vLines.empty()) nScore += (1 << vLines.size() * 100);

				// Choose the next tetromino
				nCurrentx = nFieldWidth / 2;
				nCurrenty = 0;
				nCurrentRotation = 0;
				nCurrentPiece = rand() % 7;

				// If the next piece does not fit at the top of screen, game over!
				bGameOver = !DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentx, nCurrenty + 1);
			}

			nSpeedCounter = 0;
		}


		// RENDER OUTPUT ====================================

		// Draw Field
		for (int x = 0; x < nFieldWidth; x++)
			for (int y = 0; y < nFieldHeight; y++)
				screen[(y + 2) * nScreenWidth + (x + 54)] = L" ABCDEFG=#"[pField[y * nFieldWidth + x]];

		// Draw Current Piece
		for (int px = 0; px < 4; px++)
			for (int py = 0; py < 4; py++)
				if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] == L'X')
					screen[(nCurrenty + py + 2) * nScreenWidth + (nCurrentx + px + 54)] = nCurrentPiece + 65;

		// Draw Score
		swprintf_s(&screen[2 * nScreenWidth + nFieldWidth + 6], 16, L"Score: %8d", nScore);

		//Animate line completion
		if (!vLines.empty()) {
			// Display frame to draw lines
			WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
			this_thread::sleep_for(400ms); // Delay a bit

			for (auto& v : vLines)
				for (int px = 1; px < nFieldWidth - 1; px++) {
					for (int py = v; py > 0; py--)
						pField[py * nFieldWidth + px] = pField[(py - 1) * nFieldWidth + px];
					pField[px] = 0;
				}
			vLines.clear();
		}


		// Displey Frame
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}

	// Oh Dear, Game Over!
	CloseHandle(hConsole);
	cout << "Game Over! Score: " << nScore << endl;
	system("pause");


	return 0;
}