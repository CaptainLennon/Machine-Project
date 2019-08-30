/*
WHO WANTS TOO BE A MILLIONAIRE?
VGP101 Week 6 and 7 Machine Project
Written by Lennon Marshall
*/

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h> 

void SetPosition(int X, int Y)
{
	HANDLE Screen;
	Screen = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position = { X, Y };

	SetConsoleCursorPosition(Screen, Position);							// function for setting cursor to specific position
}	

const int screenHEIGHT = 30;
const int screenWIDTH = 80;

bool LifeLine5050 = true;
bool LifeLineFriend = true;
bool LifeLineAudience = true;
bool Audience5050Combo = false;
bool Confirmed = false;
bool exitGame = false;
bool WinGame = false;
int nLifeLines = 3;
char playerName[18];
char takeHome[10] = "0";
char loserMoney[10] = "0";

struct Questions
{
	int nNum;																// Question Number
	char nReward[10];														// Reward if correct
	char cText[70];															// Question text
	char cAnswer[4][20];													// Four possible choices
	int nCorrect;															// Index of correct answer
	int n5050[2];															// Two incorrect choices to remove
	char cCallFriend[61];													// Advice from friend, sometimes correct
	int nAudience[4];														// Four percentages from audience
};

struct Questions question[15] = {
		{
			1,
			"500",
			"A luffa is a type of what?",
			{ "Sponge", "Fish", "Plant", "Instrument"},
			2,
			{1,3},
			"\"I use one everyday in the.shower, so I'd say sponge\"",
		},
		{
			2,
			"1,000",
			"What do the thieves set out to steal in the movie \"Reservoir Dogs\"?",
			{ "Money", "Drugs", "Guns", "Diamonds"},
			3,
			{0,2},
			"\"That's one of my favourite.movies! Diamonds is the answer\""
		},
		{
			3,
			"2,000",
			"What is the nearest star to Earth?",
			{ "Alpha Centauri", "Proxima Centauri", "The Sun", "Sirius"},
			2,
			{1,3},
			"\"Sorry that you wasted this on.something easy, it's the Sun\""
		},
		{
			4,
			"3,000",
			"A cat-o'-nine tails is a type of what?",
			{ "Whip", "Pokemon", "Flower", "Amoeba"},
			0,
			{1,3},
			"\"Your father uses one in the.bedroom, it's a whip\""
		},
		{
			5,
			"5,000",
			"What are bongo drums traditionally held between for playing?",
			{ "The Knees", "The Feet", "The Hands", "Not held at all"},
			0,
			{2,3},
			"\"I played some in college and.held it between my knees\"",
		},
		{
			6,
			"7,500",
			"Einstein was what character's dog in the film \"Back to the Future\"?",
			{ "Marty McFly", "Biff Tannen", "George McFly", "Emmett Brown"},
			3,
			{1,2},
			"\"I never saw that movie but.my guess is Marty McFly?\"",
		},
		{
			7,
			"10,000",
			"What Greek letter is used to represent electrical resistance?",
			{ "Alpha", "Delta", "Gamma", "Omega"},
			3,
			{0,2},
			"\"I think I've seen the Omega.symbol on my power adapters\"",
		},
		{
			8,
			"15,000",
			"Which is the largest planet in our solar system?",
			{ "Saturn", "Mars", "Jupiter", "Venus"},
			2,
			{1,3},
			"\"Saturn or Jupiter for sure,.so maybe Jupiter?\"",
		},
		{
			9,
			"25,000",
			"What was the first American film to show a toilet flushing?",
			{ "My Fair Lady", "Psycho", "Cape Fear", "Friday the 13th"},
			1,
			{0,3},
			"\"I heard on a podcast that it.was 1960's Psycho, good flick\"",
		},
		{
			10,
			"50,000",
			"What is frozen to make dry ice?",
			{ "Carbon Monoxide", "Carbon Dioxide", "Water", "Methane"},
			1,
			{0,3},
			"\"Methane stinks, water is wrong,.and monoxide is poison!\"",
		},
		{
			11,
			"75,000",
			"Who was the original voice of Mickey Mouse?",
			{ "Jim Henson", "Russi Taylor", "Ryan Gosling", "Walt Disney"},
			3,
			{1,2},
			"\"I'm sure Disney himself voiced.the character at first\"",
		},
		{
			12,
			"150,000",
			"What letter is most used in the English language?",
			{ "E", "T", "A", "S"},
			0,
			{2,3},
			"\"I feel like it's a vowel,.probably 'E', but I'm not 100%\"",
		},
		{
			13,
			"250,000",
			"What do you call feeling like you experienced something before?",
			{ "Matrix Glitch", "Deja Vu", "Recursion", "Bon Fete"},
			1,
			{0,3},
			"\"The French have a way with words,.it's definitely Deja Vu\"",
		},
		{
			14,
			"500,000",
			"Who was also known as \"The Scourge of God\"?",
			{ "Attila the Hun", "Friedrich Nietzsche", "Alexander the Great", "Richard Dawkins"},
			0,
			{1,2},
			"\"Scourge sounds violent,.so proabably Attila the Hun?\"",
		},
		{
			15,
			"1,000,000",
			"Whose statue was toppled from it's place in Red Square in 1991?",
			{ "Hitler's", "Stalin's", "Lenin's", "Mussolini's"},
			2,
			{0,1},
			"\"Lenin's, even though they.still keep his body preserved\"",
		}
};

void NextQuestion(int qNum, int length);									// Display the next Question and Answers

void Title();																// Display title screen and ask for player name

char mainScreen[screenHEIGHT][screenWIDTH] = {
		{" ERRRRRRRRRRRRRRRRRRT                                     ERRRRRRRRRRRRRRRRRRT"},
		{" F                  F                                     F   15 $1,000,000  F"},
		{" XRRRRRRRRRRRRRRRRRRV                                     SRRRRRRRRRRRRRRRRRRG"},
		{"                                                          F   14 $500,000    F"},
		{" ERRRRRRRRRRRRRRRRRRT                                     F   13 $250,000    F"},
		{" F [1]  50 / 50     F                                     F   12 $150,000    F"},
		{" F                  F                                     F   11 $75,000     F"},
		{" SYYYYYYYYYYYYYYYYYYG              ,)(8)).                SYYY10 $50,000YYYYYG"},
		{" F [2] qq (^_^) qq  F            (()))())()).             F    9 $25,000     F"},
		{" F                  F           (()\"````\"::= )            F    8 $15,000     F"},
		{" SYYYYYYYYYYYYYYYYYYG           )| _    _ ::= )           F    7 $10,000     F"},
		{" F [3] f d f d f d  F          (()(o)/ (o) ?(/)           F    6 $7,500      F"},
		{" F                  F           )(  c   .( :(/)           SYYYY5 $5,000YYYYYYG"},
		{" XRRRRRRRRRRRRRRRRRRV          (( \\ .__.  ,/(/)           F    4 $3,000      F"},
		{" ERRRRRRRRRRRRRRRRRRT           )  `.___,'/ (/)           F    3 $2,000      F"},
		{" F [4] Walk with    F              |    | (/)             F    2 $1,000      F"},
		{" F    $0            F            _.'    ,\\(/)__           F    1 $500        F"},
		{" XRRRRRRRRRRRRRRRRRRV        _.-\" ||` u  ||(/) \".         XRRRRRRRRRRRRRRRRRRV"},
		{"   UYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYP   "},
		{"   |                                                                       |   "},
		{"YYYI                                                                       OYYY"},
		{"   |                                                                       |   "},
		{"   JYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYK   "},
		{"    UYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYP UYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYP    "},
		{"YYYYI  A:                             OYI  B:                             OYYYY"},
		{"    JYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYLYK JYLYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYK    "},
		{"    UYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYMYP UYMYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYP    "},
		{"YYYYI  C:                             OYI  D:                             OYYYY"},
		{"    JYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYK JYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYK"},
		{"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYG   SYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY"}

};

char takehomeScreen[screenHEIGHT][screenWIDTH] = {
		{"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"},
		{"~~~~~~~~~ERRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRT~~~~~~~~~~"},
		{"~~~~~~~~~F                                                          F~~~~~~~~~~"},
		{"~~~~~~~~~F                                                          F~~~~~~~~~~"},
		{"~~~~~~~~~F                                                          F~~~~~~~~~~"},
		{"~~~~~~~~~F                                           ____________   F~~~~~~~~~~"},
		{"~~~~~~~~~F                                                          F~~~~~~~~~~"},
		{"~~~~~~~~~F                                          UYYYYYYYYYYYP   F~~~~~~~~~~"},
		{"~~~~~~~~~F           _____________________________ $|           |   F~~~~~~~~~~"},
		{"~~~~~~~~~F                                          JYYYYYYYYYYYK   F~~~~~~~~~~"},
		{"~~~~~~~~~F                                                          F~~~~~~~~~~"},
		{"~~~~~~~~~F       ____________________       _____________________   F~~~~~~~~~~"},
		{"~~~~~~~~~F                                                          F~~~~~~~~~~"},
		{"~~~~~~~~~F                                                          F~~~~~~~~~~"},
		{"~~~~~~~~~XRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRV~~~~~~~~~~"},
		{"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"}
};

void ConvertASCII(char string[screenHEIGHT][screenWIDTH]);					// Convert initial screen array to more advanced ASCII

void InitializeMainScreen();												// Write elements to main GUI

void InitializeTakeHomeScreen(char string[]);								// Write the ending screen cheque

void DrawScreen(char string[screenHEIGHT][screenWIDTH]);					// Draw entire updated screen

void CenterText(char string[], int line, int start, int end);				// Center text and write to screen

void ClearText(int line, int start, int end);								// Erase part of screen

void ClearQuestion();														// Clear Question and Answers text

void ClearMessageArea();													// Clear text from Message Area

void MoveScoreArrows(int qNum);												// Move arrows up the Scoreboard

void FiftyFifty(int qNum);													// Erase two wrong answers

void PhoneFriend(int qNum);													// Display friend's text in Message Area

void AskAudience(int qNum);													// Display Audience Poll in Message Area

void PollStats(int qNum, int a, int b, int c, int d);						// Generate stats weighted towards correct answer

void MenuSelect(int qNum);													// Evaluate user choice

void RemainingLifeLines();													// Display remaining number of life lines

void UpdateReward(int qNum);												// Update earned reward and losing reward

void WriteText(char screen[screenHEIGHT][screenWIDTH], char string[], int line, int start); // Write text to any screen

bool AreYouSure();															// Confirm user input for answers

bool testCorrect(int qNum, int answer);										// Check for correct answer and update reward or exit

void DrawTakeHome(int qNum, char string[]);									// Display the take home cheque screen

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	srand(time(NULL));
	system("color 1F");														// Set Console to White on Blue
	InitializeMainScreen();													// Create the GUI from array

	Title();																// Show title and get player name

	int qNum = 0;															// Initialize starting question

	do
	{
		NextQuestion(qNum, strlen(question[qNum].cText));					// Display current question
		DrawScreen(mainScreen);												// Draw updated screen
		MenuSelect(qNum);													// Get user choice and continue if correct
		qNum++;																// Advance to next question
		if (qNum == 15)														// Exit after last question
		{
			DrawTakeHome(qNum, takeHome);
			exitGame = true;
		}
	} while (exitGame != true);

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ConvertASCII(char string[screenHEIGHT][screenWIDTH])					// Converts letters into advanced ascii characters to draw later
{
	for (int i = 0; i < screenHEIGHT; i++)
	{
		for (int j = 0; j < screenWIDTH; j++)
		{
			switch (string[i][j])
			{
			case 'E':
				string[i][j] = 201;											// double-line top left corner
				break;
			case 'R':
				string[i][j] = 205;											// double horizontal
				break;
			case 'T':
				string[i][j] = 187;											// double top right
				break;
			case 'S':
				string[i][j] = 204;											// double to single - left junc
				break;
			case 'F':
				string[i][j] = 186;											// double vertical
				break;
			case 'G':
				string[i][j] = 185;											// double to single - right junc
				break;
			case 'X':
				string[i][j] = 200;											// double bottom left
				break;
			case 'V':
				string[i][j] = 188;											// double bottom right
				break;
			case 'Y':
				string[i][j] = 196;											// single horizontal
				break;
			case 'I':
				string[i][j] = 180;											// single right junc
				break;
			case 'O':
				string[i][j] = 195;											// single left junc
				break;
			case 'U':
				string[i][j] = 218;											// single top left
				break;
			case 'P':
				string[i][j] = 191;											// single top right
				break;
			case 'J':
				string[i][j] = 192;											// single bottom left
				break;
			case 'K':
				string[i][j] = 217;											// single bottom right
				break;
			case 'L':
				string[i][j] = 194;											// single top down junc
				break;
			case 'M':
				string[i][j] = 193;											// single bottom up junc
				break;
			case 'f':
				string[i][j] = 258;											// face 1
				break;
			case 'd':
				string[i][j] = 257;											// face 2
				break;
			case '>':
				string[i][j] = 272;											// arrow right
				break;
			case '<':
				string[i][j] = 273;											// arrow left
				break;
			case 'q':
				string[i][j] = 259;											// heart
				break;
			case '|':
				string[i][j] = 179;											// long vertical bar
				break;
			case '~':
				string[i][j] = 219;											// filled space
				break;
			default:
				break;
			}
		}
	}
};

void InitializeMainScreen()
{
	ConvertASCII(mainScreen);												// Convert main GUI to advanced ascii

	char lifeline1[] = "(Remove 2 Wrong)";									// update element
	WriteText(mainScreen, lifeline1, 6, 3);

	char lifeline2[17] = "(Call a Friend)";									// update element
	WriteText(mainScreen, lifeline2, 9, 3);

	char lifeline3[17] = "(Ask Audience)";									// update element
	WriteText(mainScreen, lifeline3, 12, 3);

};

void InitializeTakeHomeScreen(char string[])
{
	system("color f0");

	ConvertASCII(takehomeScreen);

	char logo1[] = { "Who Wants" };
	WriteText(takehomeScreen, logo1, 3, 13);

	char logo2[] = { "To Be A" };
	WriteText(takehomeScreen, logo2, 4, 14);

	char logo3[] = { "MILLIONAIRE?" };
	WriteText(takehomeScreen, logo3, 5, 12);

	char payto1[] = { "PAY TO THE" };
	WriteText(takehomeScreen, payto1, 7, 12);

	char payto2[] = { "ORDER OF" };
	WriteText(takehomeScreen, payto2, 8, 12);

	WriteText(takehomeScreen, playerName, 8, 25);

	WriteText(takehomeScreen, string, 8, 53);

	char date1[] = { "DATE" };
	WriteText(takehomeScreen, date1, 5, 48);

	SYSTEMTIME str_t;
	GetSystemTime(&str_t);
	char date2[11];
	snprintf(
		date2,
		sizeof(date2),
		"%d/%d/%d",
		str_t.wMonth, str_t.wDay, str_t.wYear
	);
	WriteText(takehomeScreen, date2, 5, 54);

	char memo1[] = { "MEMO" };
	WriteText(takehomeScreen, memo1, 11, 12);

	char memo2[18];
	snprintf(
		memo2,
		sizeof(memo2),
		"Used %d Life Lines!",
		3 - nLifeLines
	);
	WriteText(takehomeScreen, memo2, 11, 18);

	char signature[] = { "Regis Philbin" };
	WriteText(takehomeScreen, signature, 11, 48);

	char chequeNumbers[22];
	snprintf(
		chequeNumbers,
		sizeof(chequeNumbers),
		"%d %05d %d %05d",
		rand() % 9999 + 10000, rand() % 9999 + 80000, rand() % 99 + 100, rand() % 99999
	);
	WriteText(takehomeScreen, chequeNumbers, 13, 12);

	char congrats[] = { "CONGRATULATIONS!!" };
	WriteText(takehomeScreen, congrats, 16, 31);
};

void DrawScreen(char string[screenHEIGHT][screenWIDTH])
{
	system("CLS");
	for (int i = 0; i < screenHEIGHT; i++)
	{
		for (int j = 0; j < screenWIDTH; j++)
		{
			printf("%c", string[i][j]);
		}
		printf("\n");
	}
}

void NextQuestion(int qNum, int length)										// display question and answers
{
	ClearQuestion();														// clear question and answer areas
	ClearMessageArea();														// clear text area
	Audience5050Combo = false;												// reset lifeline combo

	char rewardText[50];
	if (qNum == 14)															// Write question reward amount
	{
		snprintf(rewardText, sizeof(rewardText), "\"This final question is.worth $%s!!\"", question[qNum].nReward);
	}
	else
	{
		snprintf(rewardText, sizeof(rewardText), "\"This question is worth $%s\"", question[qNum].nReward);
	}
	CenterText(rewardText, 2, 22, 56);

	CenterText(question[qNum].cText, 20, 4, 74);							// write question to screen

	WriteText(mainScreen, question[qNum].cAnswer[0], 24, 10);				// Write answer A
	WriteText(mainScreen, question[qNum].cAnswer[1], 24, 46);				// Write answer B
	WriteText(mainScreen, question[qNum].cAnswer[2], 27, 10);				// Write answer C
	WriteText(mainScreen, question[qNum].cAnswer[3], 27, 46);				// Write answer D

	MoveScoreArrows(qNum);													// Move scoreboard arrows up one
};

void ClearText(int line, int start, int end)
{
	int j = 0;
	for (int i = start; i < end; i++)
	{
		mainScreen[line][i] = { ' ' };								// Erase Text
		j++;
	}
};

void ClearQuestion()
{
	ClearMessageArea();
	ClearText(20, 6, 74);											// Clear Question
	ClearText(24, 10, 30);											// Clear Answer A
	ClearText(24, 46, 66);											// Clear Answer B
	ClearText(27, 10, 30);											// Clear Answer C
	ClearText(27, 46, 66);											// Clear Answer D	
};

void MoveScoreArrows(int qNum) {
	int oldArrows = 17 - qNum;									// find previous score line
	if (oldArrows == 7 || oldArrows == 12)						// replace arrows with box line
	{
		mainScreen[oldArrows][59] = 196;
		mainScreen[oldArrows][60] = 196;
		mainScreen[oldArrows][75] = 196;
		mainScreen[oldArrows][76] = 196;
	}
	else if (qNum > 0)											// or just erase previous arrows
	{
		mainScreen[oldArrows][59] = ' ';
		mainScreen[oldArrows][60] = ' ';
		mainScreen[oldArrows][75] = ' ';
		mainScreen[oldArrows][76] = ' ';
	}

	int scoreArrows;
	if (qNum == 14)												// skip a line to get to 1,000,000
	{
		scoreArrows = 1;
	}
	else
	{
		scoreArrows = 16 - qNum;								// draw arrows in scorebox for current question
	}
	mainScreen[scoreArrows][59] = 272;
	mainScreen[scoreArrows][60] = 272;
	mainScreen[scoreArrows][75] = 273;
	mainScreen[scoreArrows][76] = 273;
};

void Title() {

	char introScreen[29][74] = {
	{"       __    __ __ __  ___       __    __  ____ ____  ______  _____      "},
	{"      |  T__T  |  T  T/   \\     |  T__T  T/    |    \\|      T/ ___/      "},
	{"      |  |  |  |  l  Y     Y    |  |  |  Y  o  |  _  |      (   \\_       "},
	{"      |  |  |  |  _  |  O  |    |  |  |  |     |  |  l_j  l_j\\__  T      "},
	{"      l  `  '  |  |  |     |    l  `  '  |  _  |  |  | |  |  /  \\ |      "},
	{"       \\      /|  |  l     !     \\      /|  |  |  |  | |  |  \\    |      "},
	{"        \\_/\\_/ l__j__j\\___/       \\_/\\_/ l__j__l__j__j l__j   \\___j      "},
	{"                                                                         "},
	{"               ______  ___       ____    ___       ____                  "},
	{"              |      T/   \\     |    \\  /  _]     /    T                 "},
	{"              |      Y     Y    |  o  )/  [_     Y  o  |                 "},
	{"              l_j  l_|  O  |    |     Y    _]    |     |                 "},
	{"                |  | |     |    |  O  |   [_     |  _  |                 "},
	{"                |  | l     !    |     |     T    |  |  |                 "},
	{"                l__j  \\___/     l_____l_____j    l__j__j                 "},
	{"                                                                         "},
	{"   ___ ___ ____ _     _     ____ ___  ____   ____ ____ ____    ___ _____ "},
	{"  |   T   l    | T   | T   l    /   \\|    \\ /    l    |    \\  /  _/     T"},
	{"  | _   _ ||  T| |   | |    |  Y     |  _  Y  o  ||  T|  D  )/  [_|  Y  |"},
	{"  |  \\_/  ||  || l___| l___ |  |  O  |  |  |     ||  ||    /Y    _l__|  |"},
	{"  |   |   ||  ||     |     T|  |     |  |  |  _  ||  ||    \\|   [_   l__j"},
	{"  |   |   |j  l|     |     |j  l     |  |  |  |  |j  l|  .  |     T   __ "},
	{"  l___j___|____l_____l_____|____\\___/l__j__l__j__|____l__j\\_l_____j  l__j"},
	{"                                                                         "},
	{"      122222222222222222222222222222222222222222222222222222222222223    "},
	{"      4                                                             4    "},
	{"      4        PLEASE ENTER YOUR NAME:                              4    "},
	{"      4                                                             4    "},
	{"      522222222222222222222222222222222222222222222222222222222222226    "} };

	for (int i = 0; i < 29; i++)
	{
		for (int j = 0; j < 72; j++)
		{
			switch (introScreen[i][j])
			{
			case '1':
				introScreen[i][j] = 201;							// double-line top left corner
				break;
			case '2':
				introScreen[i][j] = 205;							// double horizontal
				break;
			case '3':
				introScreen[i][j] = 187;							// double top right
				break;
			case '4':
				introScreen[i][j] = 186;							// double vertical
				break;
			case '5':
				introScreen[i][j] = 200;							// double bottom left
				break;
			case '6':
				introScreen[i][j] = 188;							// double bottom right
				break;
			}
		}
	}

	for (int i = 0; i < 29; i++)
	{
		for (int j = 0; j < 74; j++)
		{
			printf("%c", introScreen[i][j]);
		}
		printf("\n");
	}

	SetPosition(39, 26);

	fgets(playerName, 17, stdin);

	CenterText(playerName, 1, 3, 20);
}

void CenterText(char string[], int line, int start, int end)	// center text in any given area
{
	int width = end - start;
	int length = strlen(string);								// get length of string
	int center = start + ((width / 2) - (length / 2));			// justify center
	int j = 0;

	if (length > (end - start))									// if sting is longer than space then split into 2 lines
	{
		char *next_token;
		char* lineOne = strtok_s(string, ".", &next_token);		// first string upto '.'
		char* lineTwo = strtok_s(0, ".", &next_token);			// second string after '.'
		length = strlen(lineOne);
		center = start + ((width / 2) - (length / 2));
		int length2 = strlen(lineTwo);
		int center2 = start + ((width / 2) - (length2 / 2));

		for (int i = center; i < center + length; i++)
		{
			if (string[j] == '.')
			{
				break;
			}
			mainScreen[line][i] = { string[j] };
			j++;
		}
		j = 0;
		for (int i = center2; i < center2 + length2; i++)
		{
			mainScreen[line + 1][i] = { lineTwo[j] };
			j++;
		}
	}
	else														// otherwise just write the text
	{
		for (int i = center; i < center + length; i++)
		{
			if (string[j] == '\n')
			{
				break;
			}
			mainScreen[line][i] = { string[j] };
			j++;
		}
	}
};

void ClearMessageArea() {
	for (int i = 1; i < 7; i++)
	{
		ClearText(i, 22, 56);
	}
};

void PollStats(int qNum, int a, int b, int c, int d)
{
	int temp = 0;
	question[qNum].nAudience[a] = rand() % 60 + 40;			// Generate percentage weighted towards correct
	temp = question[qNum].nAudience[a];
	question[qNum].nAudience[b] = rand() % (100 - temp);	// Generate remaining percentages
	temp += question[qNum].nAudience[b];
	question[qNum].nAudience[c] = rand() % (100 - temp);	// Generate remaining percentages
	temp += question[qNum].nAudience[c];
	question[qNum].nAudience[d] = 100 - temp;				// Generate remaining percentages
};

void PollStats5050(int qNum, int a, int b)
{
	int temp = 0;
	question[qNum].nAudience[a] = rand() % 60 + 40;			// Generate percentage weighted towards correct
	temp = question[qNum].nAudience[a];
	question[qNum].nAudience[b] = 100 - temp;				// Generate remaining percentage
};

void FiftyFifty(int qNum)
{
	ClearMessageArea();
	ClearText(5, 3, 20);
	ClearText(6, 3, 20);

	char topMessage[] = "\"Computer, please take away.two wrong answers\"";
	CenterText(topMessage, 2, 22, 56);

	if (question[qNum].n5050[0] == 0 || question[qNum].n5050[1] == 0)
	{
		ClearText(24, 10, 30);							// Erase answer A on screen
		question[qNum].nAudience[0] = 0;				// Set Audience Poll to 0
	}
	if (question[qNum].n5050[0] == 1 || question[qNum].n5050[1] == 1)
	{
		ClearText(24, 46, 66);							// Erase answer B on screen
		question[qNum].nAudience[1] = 0;				// Set Audience Poll to 0
	}
	if (question[qNum].n5050[0] == 2 || question[qNum].n5050[1] == 2)
	{
		ClearText(27, 10, 30);							// Erase answer C on screen
		question[qNum].nAudience[2] = 0;				// Set Audience Poll to 0
	}
	if (question[qNum].n5050[0] == 3 || question[qNum].n5050[1] == 3)
	{
		ClearText(27, 46, 66);							// Erase answer D on screen
		question[qNum].nAudience[3] = 0;				// Set Audience Poll to 0
	}
	LifeLine5050 = false;
	Audience5050Combo = true;							// flag for combination with ask audience
	nLifeLines--;
	RemainingLifeLines();
};

void PhoneFriend(int qNum) {
	ClearMessageArea();
	ClearText(8, 3, 20);
	ClearText(9, 3, 20);

	char topMessage[] = "Friend's Advice:";
	CenterText(topMessage, 1, 22, 56);
	CenterText(question[qNum].cCallFriend, 2, 22, 56);

	LifeLineFriend = false;
	nLifeLines--;
	RemainingLifeLines();
};

void AskAudience(int qNum)							// Generate audience poll stats
{
	ClearMessageArea();
	ClearText(11, 3, 20);
	ClearText(12, 3, 20);

	int a = question[qNum].nCorrect;
	int c = question[qNum].n5050[0];
	int d = question[qNum].n5050[1];
	int b = 6 - (a + c + d);

	if (Audience5050Combo == true)
	{
		PollStats5050(qNum, a, b);
	}
	else
	{
		PollStats(qNum, a, b, c, d);
	}

	char audiencePolltext[70];
	snprintf(
		audiencePolltext,
		sizeof(audiencePolltext),
		"\"The audience's votes are in.A: %2d%%  B: %2d%%  C: %2d%%  D: %2d%%\"",
		question[qNum].nAudience[0], question[qNum].nAudience[1], question[qNum].nAudience[2], question[qNum].nAudience[3]
	);
	CenterText(audiencePolltext, 2, 22, 56);

	LifeLineAudience = false;
	nLifeLines--;
	RemainingLifeLines();
};

void RemainingLifeLines()
{
	char subMessage[33];

	if (nLifeLines == 1)
	{
		snprintf(subMessage, sizeof(subMessage), "\"You have %d LifeLine left\"", nLifeLines);
	}
	else
	{
		snprintf(subMessage, sizeof(subMessage), "\"You have %d LifeLines left\"", nLifeLines);
	}

	CenterText(subMessage, 5, 22, 56);
};

bool AreYouSure()
{
	char response;

	char subMessage[] = "\"Is that your final answer?\" (Y/N)";
	CenterText(subMessage, 5, 22, 56);

	DrawScreen(mainScreen);

	do
	{
		SetPosition(39, 29);
		scanf_s(" %c", &response);
	} while (response != 'Y' && response != 'y' && response != 'N' && response != 'n');

	if (response == 'Y' || response == 'y')
	{
		return true;
	}
	else
	{
		return false;
	}
};

void WriteText(char screen[screenHEIGHT][screenWIDTH], char string[], int line, int start)
{
	int j = 0;
	for (int i = start; i < start + strlen(string); i++)
	{
		if (string[j] == '\n')
		{
			break;
		}
		screen[line][i] = { string[j] };
		j++;
	}
};

void UpdateReward(int qNum)
{
	strcpy_s(takeHome, question[qNum].nReward);
	WriteText(mainScreen, takeHome, 16, 7);
	if (question[qNum].nNum == 5 || question[qNum].nNum == 10)
	{
		strcpy_s(loserMoney, question[qNum].nReward);
	}
};

bool testCorrect(int qNum, int answer)
{
	if (question[qNum].nCorrect == answer)
	{
		UpdateReward(qNum);
		return true;
	}
	else
	{
		return false;
	}
};

void DrawTakeHome(int qNum, char string[])
{
	InitializeTakeHomeScreen(string);
	if (qNum == 0)
	{
		char eraseCongrats[] = "                   ";
		WriteText(takehomeScreen, eraseCongrats, 16, 31);
		char betterLuck[] = "BETTER LUCK NEXT TIME!";
		WriteText(takehomeScreen, betterLuck, 16, 29);
	}
	DrawScreen(takehomeScreen);
	SetPosition(1, 17);
	system("pause");
};

void MenuSelect(int qNum)
{
	char userChoice;
	bool nextQ = false;
	do
	{
		SetPosition(39, 29);
		scanf_s(" %c", &userChoice);

		switch (userChoice)
		{
		case '1':
			if (LifeLine5050 == true)
			{
				FiftyFifty(qNum);
				DrawScreen(mainScreen);
			}
			break;
		case '2':
			if (LifeLineFriend == true)
			{
				PhoneFriend(qNum);
				DrawScreen(mainScreen);
			}
			break;
		case '3':
			if (LifeLineAudience == true)
			{
				AskAudience(qNum);
				DrawScreen(mainScreen);
			}
			LifeLineAudience = false;
			break;
		case '4':
			DrawTakeHome(qNum, takeHome);
			exitGame = true;
			break; break;
		case 'a':
		case 'A':
			if (AreYouSure() == true)
			{
				nextQ = testCorrect(qNum, 0);
				if (nextQ == false)
				{
					DrawTakeHome(qNum, loserMoney);
					exitGame = true;
				}
			}
			break;
		case 'b':
		case 'B':
			if (AreYouSure() == true)
			{
				nextQ = testCorrect(qNum, 1);
				if (nextQ == false)
				{
					DrawTakeHome(qNum, loserMoney);
					exitGame = true;
				}
			}
			break;
		case 'c':
		case 'C':
			if (AreYouSure() == true)
			{
				nextQ = testCorrect(qNum, 2);
				if (nextQ == false)
				{
					DrawTakeHome(qNum, loserMoney);
					exitGame = true;
				}
			}
			break;
		case 'd':
		case 'D':
			if (AreYouSure() == true)
			{
				nextQ = testCorrect(qNum, 3);
				if (nextQ == false)
				{
					DrawTakeHome(qNum, loserMoney);
					exitGame = true;
				}
			}
			break;
		default:
			break;
		}
	} while (nextQ != true &&
		exitGame != true ||
		userChoice != 'a' &&
		userChoice != 'b' &&
		userChoice != 'c' &&
		userChoice != 'd' &&
		userChoice != 'A' &&
		userChoice != 'B' &&
		userChoice != 'C' &&
		userChoice != 'D' &&
		userChoice != '1' &&
		userChoice != '2' &&
		userChoice != '3' &&
		userChoice != '4'
		);

};