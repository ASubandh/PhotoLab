/*********************************************************************/
/* PhotoLab.c: Assignment 2 for EECS 22, Winter 2022
Name: Abhishek Subandh
Date Completed: 1/26/2022


*/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*** global definitions ***/
const int WIDTH  = 512;      /* image width */
const int HEIGHT = 288;      /* image height */
const int SLEN   =  80;      /* max. string length */

/*** function declarations ***/

/* print a menu */
void PrintMenu(void);

/* read image from a file */
int LoadImage(const char fname[SLEN],
	      unsigned char R[WIDTH][HEIGHT],
	      unsigned char G[WIDTH][HEIGHT],
	      unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
int SaveImage(const char fname[SLEN],
	      unsigned char R[WIDTH][HEIGHT],
	      unsigned char G[WIDTH][HEIGHT],
	      unsigned char B[WIDTH][HEIGHT]);

/* change a color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT],
		 unsigned char G[WIDTH][HEIGHT],
		 unsigned char B[WIDTH][HEIGHT]);

/* reverse image color */
void Negative(unsigned char R[WIDTH][HEIGHT],
	      unsigned char G[WIDTH][HEIGHT],
	      unsigned char B[WIDTH][HEIGHT]);

/* color filter */
void ColorFilter(unsigned char R[WIDTH][HEIGHT],
		 unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT],
		 int target_r, int target_g, int target_b, int threshold,
		 int replace_r, int replace_g, int replace_b);

/* edge detection */
void Edge(unsigned char R[WIDTH][HEIGHT],
	  unsigned char G[WIDTH][HEIGHT],
          unsigned char B[WIDTH][HEIGHT]);

/* mirror image vertically */
void VMirror(unsigned char R[WIDTH][HEIGHT],
	     unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);

/* shuffle the image */
void Shuffle(unsigned char R[WIDTH][HEIGHT],
	     unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);


/* add border */
void AddBorder(unsigned char R[WIDTH][HEIGHT],
	       unsigned char G[WIDTH][HEIGHT],
               unsigned char B[WIDTH][HEIGHT],
	       char color[SLEN], int border_width);

/* flip image vertically */
void VFlip(unsigned char R[WIDTH][HEIGHT],
	   unsigned char G[WIDTH][HEIGHT],
           unsigned char B[WIDTH][HEIGHT]);

/* test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT],
	      unsigned char G[WIDTH][HEIGHT],
	      unsigned char B[WIDTH][HEIGHT]);

int main(void)
{
    /* Two dimensional arrays to hold the current image data, */
    /* one array for each color component.                    */
    unsigned char   R[WIDTH][HEIGHT];
    unsigned char   G[WIDTH][HEIGHT];
    unsigned char   B[WIDTH][HEIGHT];

		//additional variables
		int input;
		//while loop that implements all the DIP operations
		while(1) {
		PrintMenu();
		scanf ("%d", &input);
		if (input == 1) {
			char ImageName[12];
			printf("Please input the file name to load: ");
			scanf("%s" ,&ImageName);
			LoadImage(ImageName,R,G,B);
		}
		else if (input == 2)
		{
			char ImageNameSave[12];
			printf("Please input the file name to save: ");
			scanf("%s" ,&ImageNameSave);
			SaveImage(ImageNameSave, R, G, B);
		}
		else if (input ==3)
		{
		BlackNWhite(R, G, B);
		printf("Black and White operation successfully done.\n");
		}
		else if (input == 4){
		Negative(R, G, B);
		printf("Negative operation successfully done.\n");
		}
		else if (input == 5) {
			 int i,j,k;
			 int colorDiff;
			 int replace_i,replace_j,replace_k;
			 printf("Enter Red component for the target: " );
			 scanf("%d", &i );
			 printf("\nEnter Green component for the target: " );
			 scanf(" %d", &j );
			 printf("\nEnter Blue component for the target: " );
			 scanf("  %d", &k );
			 printf("Enter threshold for color difference: ");
			 scanf("   %d", &colorDiff );
			 printf("Enter value for Red component for the target: " );
			 scanf("    %d", &replace_i );
			 printf("Enter value for Green component for the target: " );
			 scanf("     %d", &replace_j );
			 printf("Enter value for Blue component for the target: " );
			 scanf("      %d", &replace_k );
			 ColorFilter(R,G,B,i,j,k,colorDiff,replace_i,replace_j,replace_k);
			 printf("Color Filter operation is done.\n");
		}
		else if (input == 6){
			Edge(R,G,B);
			printf("Edge operation successfully done.\n");
		}
		else if (input == 7){
			printf("Shuffle operation successfully done. \n");
		}
		else if (input == 8){
			VFlip(R, G, B);
			printf("""Vertical Flip"" operation successfully done.\n");
		}
		else if (input == 9){
			VMirror(R, G, B);
			printf("Vertical Mirror operation successfully done.\n");
		}
		else if (input == 10){
			int i;
			char colorSelect[7];
			printf("Enter border width: ");
			scanf("%d", &i );
			printf("\nAvailable border colors : black, white, red, green, blue, yellow, cyan, pink, orange\nSelect border color from the options: ");
			scanf(" %s", &colorSelect);
			AddBorder(R,G,B,colorSelect,i);
			printf("Border operation successfully done!\n");

		}
		else if (input == 11){
			AutoTest(R,G,B);
			printf("AutoTest successfully done!\n");
		}
		else if (input == 12){
			exit(0);
		}
		//if (LoadImage("EngPlaza", R, G, B) != 0)
    //{
    //  return 1;
    //
		continue;
    /* End of replacing */
    //return 0;

	}

}

	  /* Please replace the following code with proper menu with function calls for DIP operations */



int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE *File;
    char Type[SLEN];
    int  Width, Height, MaxValue;
    int  x, y;
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "r");
    if (!File) {
        printf("\nCannot open file \"%s\" for reading!\n", fname);
        return 1;
    }
    fscanf(File, "%79s", Type);
    if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
        printf("\nUnsupported file format!\n");
        return 2;
    }
    fscanf(File, "%d", &Width);
    if (Width != WIDTH) {
        printf("\nUnsupported image width %d!\n", Width);
        return 3;
    }
    fscanf(File, "%d", &Height);
    if (Height != HEIGHT) {
        printf("\nUnsupported image height %d!\n", Height);
        return 4;
    }
    fscanf(File, "%d", &MaxValue);
    if (MaxValue != 255) {
        printf("\nUnsupported image maximum value %d!\n", MaxValue);
        return 5;
    }
    if ('\n' != fgetc(File)) {
        printf("\nCarriage return expected!\n");
        return 6;
    }
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            R[x][y] = fgetc(File);
            G[x][y] = fgetc(File);
            B[x][y] = fgetc(File);
        }
    }
    if (ferror(File)) {
        printf("\nFile error while reading from file!\n");
        return 7;
    }
    printf("%s was read successfully!\n", fname_ext);
    fclose(File);
    return 0;
}

int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE *File;
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];
    char SysCmd[SLEN * 5];
    int  x, y;

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "w");
    if (!File) {
        printf("\nCannot open file \"%s\" for writing!\n", fname);
        return 1;
    }
    fprintf(File, "P6\n");
    fprintf(File, "%d %d\n", WIDTH, HEIGHT);
    fprintf(File, "255\n");

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            fputc(R[x][y], File);
            fputc(G[x][y], File);
            fputc(B[x][y], File);
        }
    }

    if (ferror(File)) {
        printf("\nFile error while writing to file!\n");
        return 2;
    }
    fclose(File);
    printf("%s was saved successfully. \n", fname_ext);

    /*
     * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
     * and make it world readable
     */
    sprintf(SysCmd, "~eecs22/bin/pnmtojpeg_hw2.tcsh %s", fname_ext);
    if (system(SysCmd) != 0) {
        printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
        return 3;
    }
    printf("%s.jpg was stored for viewing. \n", fname);

    return 0;
}

/**************************************************************/
/* Please add your function definitions here...               */
/**************************************************************/
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){

//processing part
int Column, Row;
for (Column = 0; Column < 511; Column++){
	for (Row =0; Row < 288; Row++){

	R[Column][Row] = (R[Column][Row] + G[Column][Row] + B[Column][Row])/3;
	G[Column][Row] = (R[Column][Row] + G[Column][Row] + B[Column][Row])/3;
	B[Column][Row] = (R[Column][Row] + G[Column][Row] + B[Column][Row])/3;

		}

	}

}


void PrintMenu(void){
	//print statements
	printf("\n--------------------------------\n1: Load a PPM image\n2: Save an image in PPM and JPEG format");
	printf("\n3: Change a color image to Black & White\n4: Make a negative of an image");
	printf("\n5: Color filter an image\n6: Sketch the edge of an image\n7: Shuffle an image");
	printf("\n8: Flip an image vertically\n9: Mirror an image vertically\n10: Add Border to an image");
	printf("\n11: Test all functions\n12: Exit\nplease make your choice: ");
}

void Negative(unsigned char R[WIDTH][HEIGHT],unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
	//processing part
	int Column, Row;
	for (Column = 0; Column < 511; Column++){
		for (Row =0; Row < 288; Row++){
			R[Column][Row] = 255- R[Column][Row];
			G[Column][Row] = 255- G[Column][Row];
			B[Column][Row] = 255- B[Column][Row];
				}
			}
}

void ColorFilter(unsigned char R[WIDTH][HEIGHT],unsigned char G[WIDTH][HEIGHT],unsigned char B[WIDTH][HEIGHT],
int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b){

	//if statements to check if the input value is within the bounds
	if (replace_r < 0){
		replace_r = 0;
	}
	if (replace_r > 255){
		replace_r = 255;
	}
	if (replace_g < 0){
		replace_g = 0;
	}
	if (replace_b > 255){
		replace_b = 255;
	}
	if (replace_b < 0){
		replace_b = 0;
	}
	if (replace_b > 255){
		replace_b = 255;
	}
	//processing part
	int Column, Row;
	for (Column = 0; Column < 511; Column++){
		for (Row =0; Row < 288; Row++){


		if (((R[Column][Row]) >= (target_r - threshold)) && (((R[Column][Row])) <= (target_r + threshold))){

			R[Column][Row] = replace_r;
		}
		else {
			R[Column][Row] = R[Column][Row];
		}

		if (((G[Column][Row]) >= (target_g - threshold)) && ((G[Column][Row]) <= (target_g + threshold))) {
		G[Column][Row] = replace_g;

		}
		else {
			G[Column][Row] = G[Column][Row];
		}
		if (((B[Column][Row]) >= (target_b - threshold)) && ((B[Column][Row]) <= (target_b + threshold))) {
		B[Column][Row] = replace_b;

		}

		else {
			B[Column][Row] = B[Column][Row];
							}
				}
		}
}

void VMirror(unsigned char R[WIDTH][HEIGHT],unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
	int Column, Row;
	for (Column = 0; Column < 511; Column++){
		for (Row = 0; Row < 288; Row++){
			//R[Column][Row] = R[Column][144 + (144 - Row)];
			//G[Column][Row] = G[Column][144 + (144 - Row)];
			//B[Column][Row] = B[Column][144 + (144 - Row)];
			R[Column][144 + (144 - Row)] = R[Column][Row];
			G[Column][144 + (144 - Row)] = G[Column][Row];
			B[Column][144 + (144 - Row)] = B[Column][Row];
				}
			}
	}

void VFlip(unsigned char R[WIDTH][HEIGHT],unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
	//temp variable must be created when swapping
	int Column, Row, Temp;
	for (Column = 0; Column < 511; Column++){
		for (Row = 0; Row < 144; Row++){

			Temp = R[Column][Row];
			R[Column][Row] = R[Column][144 + (144 - Row)];
			R[Column][144 + (144 - Row)] = Temp;

			Temp = G[Column][Row];
			G[Column][Row] = G[Column][144 + (144 - Row)];
			G[Column][144 + (144 - Row)] = Temp;

			Temp = B[Column][Row];
			B[Column][Row] = B[Column][144 + (144 - Row)];
			B[Column][144 + (144 - Row)] = Temp;

				}
			}

}

void Edge(unsigned char R[WIDTH][HEIGHT],unsigned char G[WIDTH][HEIGHT],unsigned char B[WIDTH][HEIGHT]){
	int Column, Row, Temp1, Temp2, Temp3, Temp4, Temp5, Temp6, Temp7, Temp8, Temp9;
	int RTemp[WIDTH][HEIGHT];
	int GTemp[WIDTH][HEIGHT];
	int BTemp[WIDTH][HEIGHT];
	for (Column = 1; Column < 511; Column++){
		for (Row = 1; Row < 287; Row++){
			//temp variables to hold the value of the neighboring pixels
			//reused in the loop
			//definitely a more efficient way of doing this
			Temp1 = R[Column - 1][Row -1];
			Temp2 = R[Column][Row -1];
			Temp3 = R[Column + 1][Row -1];
			Temp4 = R[Column - 1][Row];
			Temp5 = R[Column][Row];
			Temp6 = R[Column + 1][Row];
			Temp7 = R[Column - 1][Row + 1];
			Temp8 = R[Column][Row + 1];
			Temp9 = R[Column + 1][Row + 1];

			RTemp[Column][Row] = ((8*Temp5) - Temp1 -Temp2 -Temp3 - Temp4 - Temp6 - Temp7 -Temp8 - Temp9);


			if (RTemp[Column][Row] < 0){
				RTemp[Column][Row] = 0;
			}
			else if (RTemp[Column][Row] > 255){
				RTemp[Column][Row] = 255;
			}

			//RTemp[Column][Row] = R[Column][Row];
			//R[Column][Row] = Temp5;

			Temp1 = G[Column - 1][Row -1];
			Temp2 = G[Column][Row -1];
			Temp3 = G[Column + 1][Row -1];
			Temp4 = G[Column - 1][Row];
			Temp5 = G[Column][Row];
			Temp6 = G[Column + 1][Row];
			Temp7 = G[Column - 1][Row + 1];
			Temp8 = G[Column][Row + 1];
			Temp9 = G[Column + 1][Row + 1];

			GTemp[Column][Row] = ((8*Temp5) - Temp1 -Temp2 -Temp3 - Temp4 - Temp6 - Temp7 -Temp8 - Temp9);

			if (GTemp[Column][Row] < 0){
				GTemp[Column][Row] = 0;
			}
			else if (GTemp[Column][Row] > 255){
				GTemp[Column][Row] = 255;
			}

			//GTemp[Column][Row] = G[Column][Row];
			//G[Column][Row] = Temp5;

			Temp1 = B[Column - 1][Row -1];
			Temp2 = B[Column][Row -1];
			Temp3 = B[Column + 1][Row -1];
			Temp4 = B[Column - 1][Row];
			Temp5 = B[Column][Row];
			Temp6 = B[Column + 1][Row];
			Temp7 = B[Column - 1][Row + 1];
			Temp8 = B[Column][Row + 1];
			Temp9 = B[Column + 1][Row + 1];

			BTemp[Column][Row] = ((8*Temp5) - Temp1 -Temp2 -Temp3 - Temp4 - Temp6 - Temp7 -Temp8 - Temp9);

			if (BTemp[Column][Row] < 0){
				BTemp[Column][Row] = 0;
			}
			else if (BTemp[Column][Row] > 255){
				BTemp[Column][Row] = 255;
			}

				}
			}

			for (Column = 1; Column < 511; Column++){
				for (Row = 1; Row < 287; Row++){
					R[Column][Row] = RTemp[Column][Row];
					G[Column][Row] = GTemp[Column][Row];
					B[Column][Row] = BTemp[Column][Row];

				}
			}
}

void AddBorder(unsigned char R[WIDTH][HEIGHT],unsigned char G[WIDTH][HEIGHT],unsigned char B[WIDTH][HEIGHT], char color[SLEN], int border_width) {
	//array that holds all the colors
	char *colors[9] = {"black", "white", "red", "green", "blue", "yellow", "cyan", "pink", "orange"};

	//temorary arrays that will hold the color of the border we want
	int RTemp[WIDTH][HEIGHT];
	int GTemp[WIDTH][HEIGHT];
	int BTemp[WIDTH][HEIGHT];

	//ints for the for loop
	int comparing;
	//int finalColor;
	//border width multiplier
	float border_width_2 = (border_width/2) * 9/16.0;

	//for loop that calculates which color the user input by comparing it to elements in the array - it breaks after it finds a match of the colors
	for (comparing = 0; comparing < 9; comparing++) {
		int colorComp = strcmp(colors[comparing], color);
		if (colorComp == 0) {
			//finalColor = comparing;
			break;
		}
	}

	//for black border
	if (comparing == 0){
		 RTemp[0][0] = 0;
		 GTemp[0][0] = 0;
		 BTemp[0][0] = 0;
	}
	//for white border
	else if (comparing == 1){

				RTemp[0][0] = 255;
				GTemp[0][0] = 255;
				BTemp[0][0] = 255;
	}
	//for red border
	else if (comparing == 2){

				RTemp[0][0] = 255;
				GTemp[0][0] = 0;
				BTemp[0][0] = 0;
	}
	//for green border
	else if (comparing == 3){

				RTemp[0][0] = 0;
				GTemp[0][0] = 255;
				BTemp[0][0] = 0;
	}
	//for blue border
	else if (comparing == 4){

				RTemp[0][0] = 0;
				GTemp[0][0] = 0;
				BTemp[0][0] = 255;
	}
	//for yellow border
	else if (comparing == 5){

				RTemp[0][0] = 255;
				GTemp[0][0] = 255;
				BTemp[0][0] = 0;
	}
	//for cyan border
	else if (comparing == 6){

				RTemp[0][0] = 0;
				GTemp[0][0] = 255;
				BTemp[0][0] = 255;
	}
	//for pink border
	else if (comparing == 7){

				RTemp[0][0] = 255;
				GTemp[0][0] = 192;
				BTemp[0][0] = 203;
	}
	//for orange border
	else if (comparing == 8){

				RTemp[0][0] = 255;
				GTemp[0][0] = 165;
				BTemp[0][0] = 0;
	}

//for loops that create the border: one for loop does one edge
	int Column, Row;

	for (Column = 0; Column < 511; Column++){
		for (Row = 0; Row < border_width/2; Row++){

			R[Column][Row] = RTemp[0][0];
			G[Column][Row] = GTemp[0][0];
			B[Column][Row] = BTemp[0][0];

				}
			}
	for (Column = 0; Column < 511; Column++){
		for (Row = 288 - (border_width/2); Row < 288; Row++){

			R[Column][Row] = RTemp[0][0];
			G[Column][Row] = GTemp[0][0];
			B[Column][Row] = BTemp[0][0];

				}
			}


	for (Column = 0; Column < border_width_2; Column++){
		for (Row = 0; Row < 288; Row++){

			R[Column][Row] = RTemp[0][0];
			G[Column][Row] = GTemp[0][0];
			B[Column][Row] = BTemp[0][0];

				}
			}
	for (Column = 512 - border_width_2; Column < 512; Column++){
		for (Row = 0; Row < 288; Row++){

			R[Column][Row] = RTemp[0][0];
			G[Column][Row] = GTemp[0][0];
			B[Column][Row] = BTemp[0][0];

				}
			}

	}
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
	//calls all functions
	LoadImage("EngPlaza",R,G,B);
	BlackNWhite(R,G,B);
	SaveImage("bw",R,G,B);
	printf("Black and White tested!\n\n");

	LoadImage("EngPlaza",R,G,B);
	Negative(R,G,B);
	SaveImage("negative",R,G,B);
	printf("Negative tested!\n\n");

	LoadImage("EngPlaza",R,G,B);
	ColorFilter(R,G,B, 190,100,150,60,0,0,255);
	SaveImage("colorfilter",R,G,B);
	printf("Color Filter tested!\n\n");

	LoadImage("EngPlaza",R,G,B);
	Edge(R,G,B);
	SaveImage("edge",R,G,B);
	printf("Edge tested!\n\n");

	LoadImage("EngPlaza",R,G,B);
	VFlip(R,G,B);
	SaveImage("vflip",R,G,B);
	printf("Vertical Flip tested!\n\n");

	LoadImage("EngPlaza",R,G,B);
	VMirror(R,G,B);
	SaveImage("vmirror",R,G,B);
	printf("Vertical Mirror tested!\n\n");

	LoadImage("EngPlaza",R,G,B);
	AddBorder(R,G,B,"orange",64);
	SaveImage("border",R,G,B);
	printf("Border tested!\n\n");

}


/* EOF */
