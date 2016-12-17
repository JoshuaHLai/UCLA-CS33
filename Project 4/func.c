#include "func.h"
#include "omp.h"

void Func1(int c[][TSIZE], int a[][TSIZE], int b[][TSIZE])
{
	int i, j, k, r;

	#pragma omp parallel for collapse(2) private(k, r, j)
        for (i=0; i<TSIZE; i++) {
                for (k=0; k<TSIZE; k++) {
                	r = a[i][k];
                     for (j=0; j<TSIZE; j++) {
				c[i][j]+=r*b[k][j];
                        }
                }
        }
}

void Func2(int d[][MSIZE], int c[][MSIZE])
{
	int i,j;
	int ii, jj;
	int block_size = MSIZE/500;

	#pragma omp parallel for private(ii, j, jj) schedule(dynamic)
	for(i=0; i<MSIZE; i+=block_size){
		for(j=0; j<MSIZE; j+=block_size){
			for(ii=i; ii<i+block_size; ii++){
				for(jj = j; jj<j+block_size; jj++){
					d[ii][jj]=c[jj][ii];
				}
			}
		}
	}
}

void Func3(int z[][MSIZE], int d[][MSIZE])
{
	int y, x;
	int near = 2;  	// The weight of neighbor
	int itself = 84; 	// The weight of center

	#pragma omp parallel for collapse(2) private(x) schedule(static)
	for (y=0; y<MSIZE; y++) {
		for (x=0; x<MSIZE; x++) {
			if (y>=1 && y<MSIZE-1) {
				if (x>=1 && x<MSIZE-1) {
					z[y][x] = ((d[y-1][x-1] + d[y-1][x+1] + d[y+1][x-1] + d[y+1][x+1] + d[y][x-1] + d[y][x+1] + d[y-1][x] + d[y+1][x]) << 1) + itself * d[y][x];				
				}
				else {
					if(x==0){
						z[y][x] = (((d[y-1][x] << 1) + d[y-1][x+1] + (d[y+1][x] << 1) + d[y+1][x+1] + d[y][x] + d[y][x+1]) << 1) + itself * d[y][x];
					}
					else {
						z[y][x] = ((d[y-1][x-1] + (d[y-1][x] << 1) + d[y+1][x-1] + (d[y+1][x] << 1) + d[y][x-1] + d[y][x]) << 1) + itself * d[y][x];
					}	
				}
			}
			else {
				if (y==0) {
					if (x>=1 && x<MSIZE-1) {
						z[y][x] = (((d[y][x-1] << 1) + (d[y][x+1] << 1) + d[y+1][x-1] + d[y+1][x+1] + d[y][x] + d[y+1][x]) << 1) + itself * d[y][x];
					}
					else {
						if (x==0) {
							z[y][x] = ((d[y][x] + (d[y][x+1] << 1) + (d[y+1][x] << 1) + d[y+1][x+1] + d[y][x] + d[y][x]) << 1) + itself * d[y][x];
						}
						else {
							z[y][x] = (((d[y][x-1] << 1) + d[y][x] + d[y+1][x-1] + (d[y+1][x] << 1) + d[y][x] + d[y][x]) << 1) + itself * d[y][x];
						}
					}
				}
				else {
					if (x>=1 && x<MSIZE-1){
						z[y][x] = ((d[y-1][x-1] + d[y-1][x+1] + (d[y][x-1] << 1) + (d[y][x+1] << 1) + d[y-1][x] + d[y][x]) << 1) + itself * d[y][x];
					}
					else {
						if (x==0) {
							z[y][x] = (((d[y-1][x] << 1) + d[y-1][x+1] + d[y][x] + (d[y][x+1] << 1) + d[y][x] + d[y][x]) << 1) + itself * d[y][x];
						}
						else {
							z[y][x] = ((d[y-1][x-1] + (d[y-1][x] << 1) + (d[y][x-1] << 1) + d[y][x] + d[y][x] + d[y][x]) << 1) + itself * d[y][x];
						}
					}
				}
			}
			
		}
	}
	#pragma omp parallel for private(x)
	for (y=0; y<MSIZE; y++) {
		for (x=0; x<MSIZE; x++) {
			z[y][x]/=100;
		}
	}
}
						
void Func4(int b[], int a[])
{
	int chuck_size=MSIZE;	 
	//int array_size=chuck_size;
	int chuck[chuck_size];
    	int i, j=0;

	int k = j*chuck_size;
	b[k]=a[k];
	for (i=1; i<chuck_size; i++)
	{
		b[k+i]=b[k+i-1]+a[k+i];
	}
	chuck[j]=b[k+4095];

	#pragma omp parallel for private(i) schedule(guided)
	for(j=1; j<chuck_size; j++) {
		int k = j*chuck_size;
		b[k]=a[k];
		for (i=1; i<chuck_size; i++)
		{
			b[k+i]=b[k+i-1]+a[k+i];
		}
		chuck[j]=b[k+4095];
	}
	
	for(j=1; j<chuck_size; j+=8) {
		chuck[j]=chuck[j-1]+chuck[j];
		chuck[j+1]=chuck[j]+chuck[j+1];
		chuck[j+2]=chuck[j+1]+chuck[j+2];
		chuck[j+3]=chuck[j+2]+chuck[j+3];
		chuck[j+4]=chuck[j+3]+chuck[j+4];
		chuck[j+5]=chuck[j+4]+chuck[j+5];
		chuck[j+6]=chuck[j+5]+chuck[j+6];
		chuck[j+7]=chuck[j+6]+chuck[j+7];
	}

	#pragma omp parallel for private(i)
	for(j=1; j<chuck_size; j++) {
		int k = j*chuck_size;
		int temp = chuck[j-1]/(j+1);
		for (i=0; i<chuck_size; i+=4) {
			b[k+i]+=temp;
			b[k+i+1]+=temp;
			b[k+i+2]+=temp;
			b[k+i+3]+=temp;
		}
	}
}

void Func5(int b[], int a[])
{
	int i = 0, j, stride, stride2, step;
	int temp;
	long log_N = 24;

	for (j = 0; j < VSIZE; j += 2) {
		b[j] = a[j];
		b[j + 1] = a[j] + a[j + 1];
	}

	for (i = 4; i < VSIZE; i *= 2) {
		int i_half = i / 2;
		for (j = 0; j < VSIZE; j += i) {
			b[j + i - 1] = b[j + i_half - 1] + b[j + i - 1];
		}
	}

	b[VSIZE - 1] = 0;
	for (i = (log_N - 1); i >= 0; i--) {
		stride2 = (2 << i) - 1;
		int power1 = (1 << i);
		stride = power1 - 1;
		step = stride2 + 1;

		//int power2= step;
		for (j = 0; j < VSIZE; j += step) {
			temp = b[j + power1 - 1];
			b[j + power1 - 1] = b[j + step - 1];
			b[j + step - 1] = temp + b[j + step - 1];
		}
	}
}

int main()
{
	return 0;
}
