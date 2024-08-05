#include "r136.h"

// The intro code was back-ported from the "modern C++" version of R136, which
// makes it use some constructs that don't make much sense if the code had
// been written from scatch back in the late 90s. I chose closer resemblance
// to the "modern" code over "retro code purity", I guess. Mind you, it still
// compiles on Borland C++ 5.02!

/* Turn warning for 'Condition is always false' off (Borland) */
#pragma warn -ccc
/* Turn warning for 'Unreachable code' off (Borland) */
#pragma warn -rch


#define BLOCK_ROW_COUNT 8

#define S__ " "
#define BBB "\xDB"
#define TTT "\xDF"
#define LLL "\xDC"

// I apologize for the way these block diagrams are composed. In my mind this
// is still more readable than a long range of non-aligned \x escape codes.

const char *spider[2][BLOCK_ROW_COUNT] =
{
	{
		S__ S__ LLL LLL LLL S__ S__ S__ S__ S__ S__ S__ S__ LLL S__ BBB S__ LLL S__ S__ S__ S__ S__ S__ S__ S__ LLL LLL LLL S__ S__,
		S__ LLL TTT S__ S__ TTT TTT LLL LLL S__ S__ LLL TTT S__ TTT BBB TTT S__ TTT LLL S__ S__ LLL LLL TTT TTT S__ S__ TTT LLL S__,
		LLL BBB S__ LLL LLL LLL LLL S__ S__ BBB BBB BBB S__ TTT S__ LLL S__ TTT S__ BBB BBB BBB S__ S__ LLL LLL LLL LLL S__ BBB LLL,
		S__ S__ S__ BBB S__ S__ S__ TTT TTT BBB BBB BBB BBB LLL BBB BBB BBB LLL BBB BBB BBB BBB TTT TTT S__ S__ S__ BBB S__ S__ S__,
		S__ LLL BBB S__ S__ S__ S__ LLL LLL LLL TTT BBB BBB BBB BBB BBB BBB BBB BBB BBB TTT LLL LLL LLL S__ S__ S__ S__ BBB LLL S__,
		S__ S__ S__ LLL TTT TTT TTT S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ TTT TTT TTT LLL S__ S__ S__,
		S__ S__ BBB S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ BBB S__ S__,
		S__ TTT TTT S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ TTT TTT S__
	},
	{
		S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ BBB S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__,
		S__ S__ BBB TTT TTT LLL LLL S__ S__ S__ S__ S__ LLL TTT LLL BBB LLL TTT LLL S__ S__ S__ S__ S__ LLL LLL TTT TTT BBB S__ S__,
		S__ BBB S__ S__ S__ S__ S__ TTT TTT LLL LLL BBB S__ LLL S__ TTT S__ LLL S__ BBB LLL LLL TTT TTT S__ S__ S__ S__ S__ BBB S__,
		TTT TTT S__ BBB TTT TTT TTT LLL LLL BBB BBB BBB LLL S__ LLL BBB LLL S__ LLL BBB BBB BBB LLL LLL TTT TTT TTT BBB S__ TTT TTT,
		S__ S__ LLL TTT S__ S__ S__ S__ S__ TTT BBB BBB BBB BBB BBB BBB BBB BBB BBB BBB BBB TTT S__ S__ S__ S__ S__ TTT LLL S__ S__,
		S__ TTT TTT S__ LLL LLL LLL TTT TTT TTT S__ BBB BBB BBB BBB BBB BBB BBB BBB BBB S__ TTT TTT TTT LLL LLL LLL S__ TTT TTT S__,
		S__ S__ LLL TTT S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ TTT LLL S__ S__,
		S__ LLL BBB S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ BBB LLL S__
	}
};


#define SPIDER_DROP_HEIGHT 13
const int spider_width = strlen(spider[0][0]);

const char *line_section 		  = S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ BBB S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__;
const char *clear_spider_spaces = S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__;

const char *letters[3][BLOCK_ROW_COUNT] =
{
	{
		BBB TTT TTT TTT TTT TTT TTT TTT TTT TTT TTT LLL,
		BBB S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ BBB,
		BBB S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ BBB,
		BBB LLL LLL LLL LLL LLL LLL LLL LLL LLL LLL TTT,
		BBB S__ S__ S__ S__ S__ TTT LLL S__ S__ S__ S__,
		BBB S__ S__ S__ S__ S__ S__ S__ TTT LLL S__ S__,
		BBB S__ S__ S__ S__ S__ S__ S__ S__ S__ TTT LLL,
		S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__
	},
	{
		BBB TTT TTT TTT TTT TTT TTT TTT TTT TTT TTT LLL,
		BBB S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ BBB,
		BBB S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ BBB,
		BBB LLL LLL LLL LLL LLL LLL LLL LLL LLL LLL TTT,
		BBB S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__,
		BBB S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__,
		BBB S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__,
		S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__
	},
	{
		LLL LLL LLL LLL LLL LLL LLL LLL LLL LLL LLL S__,
		BBB S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ BBB,
		BBB S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ BBB,
		BBB S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ BBB,
		BBB TTT TTT TTT TTT TTT BBB TTT TTT TTT TTT S__,
		BBB S__ S__ S__ S__ S__ S__ TTT LLL S__ S__ S__,
		BBB S__ S__ S__ S__ S__ S__ S__ S__ TTT LLL S__,
		TTT S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ TTT
	}
};

const char *clear_left_letter_spaces  = "            ";
const char *clear_right_letter_spaces = "                    ";

#define LETTER_R     0
#define LETTER_P     1
#define LETTER_R_LOW 2

const int letter_width = strlen(letters[0][0]);
#define LETTER_SPACE_WIDTH 6

const char *vertical_space[BLOCK_ROW_COUNT] =
{
	" ",
	" ",
	" ",
	" ",
	" ",
	" ",
	" ",
	" "
};

const char *digits[BLOCK_ROW_COUNT] =
{
	LLL BBB S__ S__ S__ LLL TTT TTT TTT TTT TTT LLL S__ S__ S__ LLL TTT TTT TTT TTT TTT LLL,
	S__ BBB S__ S__ S__ S__ S__ S__ S__ S__ S__ BBB S__ S__ S__ BBB S__ S__ S__ S__ S__ S__,
	S__ BBB S__ S__ S__ S__ S__ S__ S__ S__ S__ BBB S__ S__ S__ BBB S__ S__ S__ S__ S__ S__,
	S__ BBB S__ S__ S__ S__ TTT TTT TTT TTT TTT LLL S__ S__ S__ LLL TTT TTT TTT TTT TTT LLL,
	S__ BBB S__ S__ S__ S__ S__ S__ S__ S__ S__ BBB S__ S__ S__ BBB S__ S__ S__ S__ S__ BBB,
	S__ BBB S__ S__ S__ S__ S__ S__ S__ S__ S__ BBB S__ S__ S__ BBB S__ S__ S__ S__ S__ BBB,
	S__ BBB S__ S__ S__ TTT LLL LLL LLL LLL LLL TTT S__ S__ S__ TTT LLL LLL LLL LLL LLL TTT,
	S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__ S__
};

const int digits_width = strlen(digits[0]);

void PrintAt(int y, int x, const char **block, int top_y, int left_x, int bottom_y, int right_x)
{
	int width = right_x - left_x + 1;
	char *buffer = (char*)malloc(width + 1);
   buffer[width] = 0;
	x++;
   y++;

	for (int i = top_y; i <= bottom_y; i++)
	{
		gotoxy(x, y + i - top_y);

		memcpy(buffer, block[i] + left_x, width);
		cputs(buffer);
	}

	free(buffer);
}

void PrintAt(int y, int x, const char **block, int rowcount)
{
	x++;
   y++;

	for (int i = 0; i < rowcount; i++)
	{
		gotoxy(x, y + i);

		cputs(block[i]);
	}
}

inline void PrintAt(int y, int x, const char *text)
{
	gotoxy(x + 1, y + 1);

	cputs(text);
}

// These are one less than the actual scren dimensions, as the original code
// is 0-based - curses just works that way.
#define SCREEN_BOTTOM_Y (25 - 1)
#define SCREEN_RIGHT_X  (80 - 1)

void LowerSpider(int spider_x)
{
	int spider_bottom_y = BLOCK_ROW_COUNT - 1;
	int spider_right_x = spider_width - 1;

	textcolor(BLACK);

	// Introduce the spider from the top of the screen
	for (int drop_index = BLOCK_ROW_COUNT; drop_index > 0; drop_index--)
	{
		for (int spider_switch = 0; spider_switch < 2; spider_switch++)
		{
			PrintAt(0, spider_x, spider[spider_switch], drop_index - 1, 0, spider_bottom_y, spider_right_x);
			delay(20);
		}
	}

	// Lower it to its final place, leaving a silk thread
	for (int drop_index = 0; drop_index < SPIDER_DROP_HEIGHT; drop_index++)
	{
		PrintAt(drop_index, spider_x, line_section);

		for (int spider_switch = 0; spider_switch < 2; spider_switch++)
		{
			PrintAt(drop_index + 1, spider_x, spider[spider_switch], BLOCK_ROW_COUNT);
			delay(20);
		}
	}
}

void SwoopInLetters(int screen_middle_x, int left_letter_final_x)
{
	int letter_bottom_y = BLOCK_ROW_COUNT - 1;
	int letter_right_x  = letter_width - 1;

	textcolor(BLACK);

	// Introduce letters from either side of the screen
	for (int flow_index = 0; flow_index < letter_width; flow_index++)
	{
		PrintAt(2, 0, letters[LETTER_R], 0, letter_right_x - flow_index, letter_bottom_y, letter_right_x);
		PrintAt(2, SCREEN_RIGHT_X - flow_index, letters[LETTER_P], 0, 0, letter_bottom_y, flow_index);
	}

	int right_letter_first_x = SCREEN_RIGHT_X - letter_width;

	int flow_index;

	// Bring the letters to the center
	for (flow_index = 0; flow_index < left_letter_final_x; flow_index++)
	{
		PrintAt(2, flow_index, vertical_space, BLOCK_ROW_COUNT);
		PrintAt(2, flow_index + 1, letters[LETTER_R], BLOCK_ROW_COUNT);

		PrintAt(2, right_letter_first_x - flow_index, letters[LETTER_P], BLOCK_ROW_COUNT);
		PrintAt(2, SCREEN_RIGHT_X - flow_index, vertical_space, BLOCK_ROW_COUNT);
	}

	// If the silk thread is just left of center due to screen width, bump the P one more place to the left
	if ((SCREEN_RIGHT_X % 2) == 0)
	{
		PrintAt(2, right_letter_first_x - flow_index, letters[LETTER_P], BLOCK_ROW_COUNT);
		PrintAt(2, SCREEN_RIGHT_X - flow_index, vertical_space, BLOCK_ROW_COUNT);
	}

	// Cut the silk thread to create the letter I
	PrintAt(1, screen_middle_x, TTT);
	PrintAt(1 + BLOCK_ROW_COUNT, screen_middle_x, LLL);
}

void SwoopInDigits(int screen_middle_x, int spider_x, int left_letter_final_x)
{
	int letters_top_y = (SCREEN_BOTTOM_Y - BLOCK_ROW_COUNT) / 2;
	if (letters_top_y < 2)
		letters_top_y = 2;

	textcolor(BLACK);

	// clear everything except for the R
	PrintAt(0, screen_middle_x, " ");
	PrintAt(1, screen_middle_x, " ");
	for (int i = 2; i < 2 + BLOCK_ROW_COUNT; i++)
		PrintAt(i, screen_middle_x, clear_right_letter_spaces);

	for (int i = 2 + BLOCK_ROW_COUNT; i < SPIDER_DROP_HEIGHT; i++)
		PrintAt(i, screen_middle_x, " ");

	for (int i = SPIDER_DROP_HEIGHT; i < SPIDER_DROP_HEIGHT + BLOCK_ROW_COUNT; i++)
		PrintAt(i, spider_x, clear_spider_spaces);

	// Lower the R to the vertical middle of the screen
	for (int i = 2; i < letters_top_y; i++)
	{
		PrintAt(i, left_letter_final_x, letters[LETTER_R_LOW], BLOCK_ROW_COUNT);
		PrintAt(i, left_letter_final_x, clear_left_letter_spaces);
		PrintAt(i + 1, left_letter_final_x, letters[LETTER_R], BLOCK_ROW_COUNT);
	}

	int digits_final_x = left_letter_final_x + letter_width + 3;
	int digits_bottom_y = BLOCK_ROW_COUNT - 1;

	textcolor(LIGHTRED);

	// Introduce the digits from the right-hand side of the screen
	for (int flow_index = 0; flow_index < digits_width; flow_index++)
		PrintAt(letters_top_y, SCREEN_RIGHT_X - flow_index, digits, 0, 0, digits_bottom_y, flow_index);

	// Bring the digits to the center
	for (int flow_index = SCREEN_RIGHT_X - digits_width; flow_index >= digits_final_x; flow_index--)
	{
		PrintAt(letters_top_y, flow_index, digits, BLOCK_ROW_COUNT);
		PrintAt(letters_top_y, flow_index + digits_width, vertical_space, BLOCK_ROW_COUNT);
	}
}

void RunIntro(void)
{
	int SCREEN_BOTTOM_Y, SCREEN_RIGHT_X;

	window(1, 1, 80, 25);
   _setcursortype(_NOCURSOR);
	textbackground(LIGHTGRAY);
	clrscr();

	int spider_x = (SCREEN_RIGHT_X - spider_width) / 2;

	LowerSpider(spider_x);

	int left_letter_final_x = SCREEN_RIGHT_X / 2 - letter_width - LETTER_SPACE_WIDTH;

	int screen_middle_x = SCREEN_RIGHT_X / 2;
	if ((SCREEN_RIGHT_X % 2) == 0)
		screen_middle_x--;

	SwoopInLetters(screen_middle_x, left_letter_final_x);

	delay(2000);

	SwoopInDigits(screen_middle_x, spider_x, left_letter_final_x);

	delay(2500);

	textbackground(BLACK);
	textcolor(LIGHTGRAY);
	clrscr();
   _setcursortype(_NORMALCURSOR);
}

void ShowSplashScreen(void)
{
	clrscr();
   textcolor(WHITE);
   PrintCentered("*** ", 8);
   textcolor(LIGHTRED);
   cputs("R136");
   textcolor(WHITE);
   cputs(" ***\r\n\r\n");
	PrintCentered("Ontwerp:\r\n", -2);
   textcolor(LIGHTGRAY);
   PrintCentered("Peter Wouda\r\n", -2);
	PrintCentered("Rutger van Bergen\r\n\r\n", -4);
   textcolor(WHITE);
	PrintCentered("Code:\r\n", -2);
   textcolor(LIGHTGRAY);
   PrintCentered("Rutger van Bergen\r\n\r\n", -4);
   textcolor(WHITE);
   PrintCentered("Testen:\r\n", -2);
   textcolor(LIGHTGRAY);
   PrintCentered("Machiel Keizer\r\n", -2);
	PrintCentered("Peter Wouda\r\n", -2);
	PrintCentered("Rutger van Bergen\r\n\r\n", -4);
	PrintCentered("Versie 2.4, (C) 1998, 2024 ", 6);
   textcolor(LIGHTRED);
   cputs("R.I.P.\r\n\r\n");
   textcolor(LIGHTGRAY);
}

void ShowStartMessage(void)
{
	clrscr();
	cputs("Terwijl je op het punt staat je avontuur te beginnen, denk je nog even na\r\n"
			"over waarom je hier, in deze verlaten, neertroostige omgeving staat.\r\n\r\n"
			"Het verhaal begint op het moment dat je met 3 andere wetenschappers een\r\n"
			"project begon over straling. In een vergevorderd stadium van het onderzoek\r\n"
			"werd er een fout gemaakt. In plaats van de gebruikelijke stoffen werden er\r\n"
			"andere, agressievere in de kernsplitser gebracht.\r\n"
			"Het resultaat was even interessant als bedreigend: er ontstond een nieuwe\r\n"
			"straling, de positronenstraling. Deze straling heft elektronen op waardoor\r\n"
			"stoffen compleet in het niets verdwijnen. Een bepaald gedeelte van de reaktor\r\n"
			"loste dan ook op in de lucht, en net op tijd kon een wereldramp voorkomen\r\n"
			"worden door het heldhaftig optreden van een van je collega's.\r\n"
			"De betreffende wetenschapper werd even blootgesteld aan de straling, en na\r\n"
			"het gebeuren zonderde hij zich af.\r\n\r\n"
			"Geschrokken door wat er gebeurde werd er besloten alles geheim te houden en\r\n"
			"het project te stoppen.\r\n"
			"De wetenschapper die aan de straling was blootgesteld hield zich niet aan de\r\n"
			"afspraak en stal wat van de agressieve stof. Hij bouwde een bom, de posi-\r\n"
			"tronenbom genaamd.\r\n");
	getch();
	clrscr();
	cputs("Hij vond dat de wereld de schuld had van zijn mutaties en hij wilde de\r\n"
			"wereld daarvoor laten boeten. Daarom verborg hij de bom, met een tijdmecha-\r\n"
			"nisme op een plaats die niemand zou durven betreden; de vallei der verderf.\r\n\r\n"
			"Een van de wetenschappers rook onraad en wilde de zaak gaan onderzoeken.\r\n"
			"Drie dagen later werd hij met een vleesmes in zijn rug op de stoep van zijn\r\n"
			"huis gevonden.\r\n"
			"Toen zijn huis werd doorzocht stootte men op twee dingen: de plaats waar de\r\n"
			"bom lag en licht radioactieve voetstappen.\r\n"
			"Jij en je collega begrepen wat er aan de hand was, en jullie besloten dat er\r\n"
			"moest worden ingegrepen. Aangezien je niet echt een held bent, werd er beslo-\r\n"
			"ten dat de andere wetenschapper op pad zou gaan. Jij zou achterblijven om\r\n"
			"zijn reis te coordineren via een geheime radiofrequentie.\r\n"
			"Je hebt nooit meer iets van hem gehoord.\r\n\r\n"
			"Nu ben jij aan de beurt.\r\n\r\n"
			"Je staat op de trap die naar de vallei leidt. Rechts van je staat een ver-\r\n"
			"weerd bordje: \"Betreden op eigen risico\". Je kijkt nog een keer achterom,\r\n"
			"en met trillende benen loop je naar beneden...\r\n");
	getch();
	clrscr();
	cputs("Type h voor help.\r\n\r\n");
}