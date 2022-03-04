//advanced.c

#include "Advanced.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/* add noise to an image */
void Noise( int percentage, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
  //for loop that generates a psuedo random pixel an n number of times
  int x, y, noisePixels, z;
  noisePixels = (percentage * WIDTH * HEIGHT)/100;
  for (z = 0; z <= noisePixels; z++) {

    x = rand() % WIDTH;
    y = rand() % HEIGHT;

    R[x][y] = 255;
    G[x][y] = 255;
    B[x][y] = 255;

    }
}



void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
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

			RTemp[Column][Row] = ((9*Temp5) - Temp1 -Temp2 -Temp3 - Temp4 - Temp6 - Temp7 -Temp8 - Temp9);


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

			GTemp[Column][Row] = ((9*Temp5) - Temp1 -Temp2 -Temp3 - Temp4 - Temp6 - Temp7 -Temp8 - Temp9);

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

			BTemp[Column][Row] = ((9*Temp5) - Temp1 -Temp2 -Temp3 - Temp4 - Temp6 - Temp7 -Temp8 - Temp9);

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

void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits){
  int bitmask,x,y;
  for (y = 0; y < HEIGHT; y++) {
    for (x = 0; x < WIDTH; x++) {
      //takes the 1s complement of the binary number and ands it
      R[x][y] &= ~(1 << (rbits-1));
      G[x][y] &= ~(1 << (gbits-1));
      B[x][y] &= ~(1 << (bbits-1));

      //three for loops iterate through each bit and changes it to 1
      for(bitmask = 0; bitmask <= rbits-2; bitmask++) {
        R[x][y] |= 1 << bitmask;
      }

      for(bitmask = 0; bitmask <= gbits-2; bitmask++) {
        G[x][y] |= 1 << bitmask;
      }

      for(bitmask = 0; bitmask <= bbits-2; bitmask++) {
        B[x][y] |= 1 << bitmask;
      }

    }
  }


}
