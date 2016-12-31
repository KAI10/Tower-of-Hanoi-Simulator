#include "iGraphics.h"

int power(int x, int y) //needed to count number of minimum steps
{
	if (!y) return 1;
	if (y % 2) return x * power(x, y - 1);
	return power(x * x, y / 2);
}

int polx[] = { 0, 150, 400, 650 }, polh = 340, diskh = 15, fact = 20, base = 100, i, j, k, ind = 1, x, y;
int save[1030][4], len[1030][4][11], from[1030], to[1030], aux[1030], moving_len[1030];
int count = 0, count1 = 0;
int N, lens = 0, mode = 0, steps, einput = 0;
char str[5];

/* polx = position of poles
polh = height of the vertex of pole
diskh  = height of disk
base = height of base
save[][] = saves number of disks in each pole in each step
len[][][] = saves length of the disks in each pole in each step
moving_len[] = saves length of moving disk in each step
from[],to[],aux[] saves which pole is origin,destination and auxiliary in each step
str[] used to take input
*/

void counting(void) //counitng the steps
{
	if (mode == 3){
		if (count1<(steps - 1)) count1++;
		else ind = 0;
	}
}

void lenset(void)  //setting the length of the disks to initial value
{
	for (i = 0; i<steps; i++){
		for (j = 0; j<4; j++){
			for (k = 0; k<11; k++) len[i][j][k] = 0;
		}
	}
	for (i = 1; i <= N; i++){
		len[0][1][i] = (N - i + 1)*fact;
	}

}

void xy_set(void)  //setting the intial position of the moving disk
{
	if (mode == 3){
		int f = from[count1], t = to[count1];
		x = polx[f] - moving_len[count1] / 2;
		y = base + save[count1][f] * diskh;
	}
}

void move_disk(void) //moving the disk from origin pole to destination pole
{
	if (mode == 3){
		int f = from[count1], t = to[count1], len = moving_len[count1];
		if (x == polx[f] - len / 2 && y != polh){
			if (polh - y > 15) y += 15;   //moving up
			else y = polh;
		}
		if (y == polh && x != polx[t] - len / 2){
			if (t>f){
				if (polx[t] - len / 2 - x > 25) x += 20;   //moving right
				else x = polx[t] - len / 2;
			}
			else{
				if (x - (polx[t] - len / 2) > 25) x -= 20; //moving left
				else x = polx[t] - len / 2;
			}
		}
		if (x == polx[t] - len / 2 && y > (base + (save[count1][t] - 1) * diskh)) y -= 15; //moving down
	}
}

void iDraw()
{
	iClear();

	if (mode <= 1){  //mode 0 means program not activated
		iText(250, 460, "Welcome to Tower of Hanoi", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(150, 150, 150);
		iRectangle(200, 250, 250, 30);
		iText(150, 420, "Click in the box to Activate");
		if (mode == 1){  //mode 1 means program activated, prompting for the value of N
			iSetColor(255, 255, 255);
			iText(600, 35, "By KAZI ASHIK ISLAM");
			iText(600, 20, "Student ID 1205007");
			iText(150, 400, "Enter Number of disks in the Box.");
			iText(150, 380, "You Can choose any number of disks between 1 & 10 (inclusive).");
			iText(150, 360, "Enter 't' to terminate the program.");
			iText(150, 340, "Press Enter to finish.");
			iText(205, 260, "Number of Disks : ");
			iText(350, 260, str);
			if (einput){ //einput means invalid input encountered
				iSetColor(255, 0, 0);
				iText(150, 200, "# Disk number must be set between 1 & 10 (inclusive).");
				iSetColor(255, 255, 255);
			}
		}
	}

	if (mode == 3){ //mode 3 means value of N obtained
		iSetColor(195, 195, 195);
		iText(30, 470, "Solution Simulation");
		iText(30, 450, "Press 'p' to  pause");
		iText(30, 430, "Press 'r' to resume");
		iText(30, 410, "Press 'END' to quit.");
		iText(600, 35, "By KAZI ASHIK ISLAM");
		iText(600, 20, "Student ID 1205007");
		iSetColor(0, 0, 0);
		iShowBMP(0, 70, "hanoi.bmp");

		if (count1 == 0){ //drawing all the disks in intial pole (1)
			for (i = 1; i <= save[0][1]; i++){
				iFilledRectangle(polx[1] - (len[0][1][i]) / 2, base + (i - 1) * diskh, len[0][1][i], diskh);
			}
		}
		else {
			int f = from[count1], t = to[count1], a = aux[count1];

			for (i = 1; i <= save[count1][f]; i++){
				iFilledRectangle(polx[f] - (len[count1][f][i]) / 2, base + (i - 1) * diskh, len[count1][f][i], diskh);
			}

			for (i = 1; i<save[count1][t]; i++){   //drawing 1 disk less, moving disk comes here and fills the gap
				iFilledRectangle(polx[t] - (len[count1][t][i]) / 2, base + (i - 1) * diskh, len[count1][t][i], diskh);
			}

			for (i = 1; i <= save[count1][a]; i++){
				iFilledRectangle(polx[a] - (len[count1][a][i]) / 2, base + (i - 1) * diskh, len[count1][a][i], diskh);
			}

			if (ind) iFilledRectangle(x, y, moving_len[count1], diskh); // ind = 1 means last step is not yet reached
			else {
				//last step reached
				iFilledRectangle(polx[3] - 10, base + (N - 1)*diskh, 20, diskh);
				iDelay(6);
				//restarting the program from mode 1
				einput = 0;
				ind = 1;
				mode = 1;
				count = 0;
				count1 = 0;
			}
		}
	}
}

void iMouseMove(int mx, int my)
{
	//printf("x = %d, y = %d\n",mx,my);
	//place your codes here
}

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here	
		if (mx >= 200 && mx <= 450 && my >= 250 && my <= 280 && mode == 0)
		{
			mode = 1;
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here	
	}
}

void iKeyboard(unsigned char key)
{
	if (mode == 1)
	{
		if (key == '\r')
		{
			if (str[0] == 't') exit(0);
			N = atoi(str); //extracting the numerical value

			for (i = 0; i <= lens; i++) str[i] = 0; //resetting 'str' for reusing
			lens = 0;

			if (N < 1 || N > 10) einput = 1; //invalid input
			else {
				iDelay(2);
				mode = 2;
			}
		}
		else
		{
			str[lens] = key;
			lens++;
		}
	}
	if (mode == 3)
	{
		if (key == 'p'){
			iPauseTimer(3);
			iPauseTimer(2);
			iPauseTimer(1);
		}
		if (key == 'r'){
			iResumeTimer(3);
			iResumeTimer(2);
			iResumeTimer(1);
		}
	}
}

void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
}

void transfer(int n, int f, int t, int a)
{
	int num_from, num_to;
	if (n>0){
		transfer(n - 1, f, a, t);  //recursive call
		count++;

		from[count] = f;
		to[count] = t;
		aux[count] = a;

		num_from = save[count - 1][f];   //number of disks in origin pole (in previous step)
		num_to = save[count - 1][t];     //number of disks in destination pole (in previous step)

		for (i = 0; i<4; i++){
			for (j = 0; j<11; j++){
				len[count][i][j] = len[count - 1][i][j];   //all the lengths of the disks in each pole is set the same at first
			}
		}

		moving_len[count] = len[count - 1][f][num_from];   //length of moving disk is the length of the uppermost disk in origin pole
		len[count][t][num_to + 1] = moving_len[count];     //it's shifted to the top of destination pole
		len[count][f][num_from] = 0;                       //so a blank is created at the top of origin pole

		save[count][f] = num_from - 1;          //disk number in origin pole reduced by one
		save[count][t] = num_to + 1;            //disk number in destination pole increased by one
		save[count][a] = save[count - 1][a];    //disk number in auxiliary pole, unchanged

		transfer(n - 1, a, t, f);    //recursive call
	}
	return;
}


void initiate(void) //initiating the program
{
	if (mode == 2){
		steps = power(2, N);
		for (i = 0; i<steps; i++){  //setting save
			for (j = 0; j<4; j++) save[i][j] = 0;
		}
		save[0][1] = N;
		lenset();
		mode = 3;
		transfer(N, 1, 3, 2);
	}
}

int main()
{
	str[0] = 0;

	iSetTimer(10, initiate);
	iSetTimer(1500, xy_set);
	iSetTimer(10, move_disk);
	iSetTimer(1500, counting);

	iInitialize(800, 500, "Tower of Hanoi");
	return 0;
}