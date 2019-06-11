#include<fstream>
#include<iostream>
#include<string>
#include<cmath>


const int size_array = 613;
const int size_array_2 = 613*2-1;

void read_file(std::string file_name, double *coord, int size = size_array);
void write_file(std::string file_name, double array_to_write[], int size = size_array);
void discrete_fourier_transform( double input_array[], double *output_real, double *output_img, int size= size_array);
void bode(double input_real[], double input_img[],double *magnitude, double *phase, int size = size_array );
void convolution(double input_array1[], double input_array2[],double *output_array, int size = size_array_2);

int main(){


 	double array_x[size_array]={};
 	double array_X_real[size_array]={};
 	double array_X_img[size_array]={};
 	double mag_x[size_array]={};
 	double pha_x[size_array]={};

 	double array_y[size_array]={};
 	double array_Y_real[size_array]={};
 	double array_Y_img[size_array]={};
 	double mag_y[size_array]={};
 	double pha_y[size_array]={};

 	double array_z[size_array]={};
 	double array_Z_real[size_array]={};
 	double array_Z_img[size_array]={};
 	double mag_z[size_array]={};
 	double pha_z[size_array]={};

 	double array_fil[size_array]={};
 	double array_fil_real[size_array]={};
 	double array_fil_img[size_array]={};
 	double mag_fil[size_array]={};
 	double pha_fil[size_array]={};

 	double array_combx[size_array_2]={};
 	double array_combx_real[size_array_2]={};
 	double array_combx_img[size_array_2]={};
 	double mag_combx[size_array_2]={};
 	double pha_combx[size_array_2]={};

 	double array_comby[size_array_2]={};
 	double array_comby_real[size_array_2]={};
 	double array_comby_img[size_array_2]={};
 	double mag_comby[size_array_2]={};
 	double pha_comby[size_array_2]={};

 	double array_combz[size_array_2]={};
 	double array_combz_real[size_array_2]={};
 	double array_combz_img[size_array_2]={};
 	double mag_combz[size_array_2]={};
 	double pha_combz[size_array_2]={};

	read_file("accelerometer_x.txt",array_x);
	discrete_fourier_transform(array_x,array_X_real,array_X_img);
	bode(array_X_real,array_X_img,mag_x,pha_x);
	write_file("magnitude_x.txt",mag_x);

	read_file("accelerometer_y.txt",array_y);
	discrete_fourier_transform(array_y,array_Y_real,array_Y_img);
	bode(array_Y_real,array_Y_img,mag_y,pha_y);
	write_file("magnitude_y.txt",mag_y);

	read_file("accelerometer_z.txt",array_z);
	discrete_fourier_transform(array_z,array_Z_real,array_Z_img);
	bode(array_Z_real,array_Z_img,mag_z,pha_z);
	write_file("magnitude_z.txt",mag_z);

	read_file("filtro.txt",array_fil);
	discrete_fourier_transform(array_fil,array_fil_real,array_fil_img);
	bode(array_fil_real,array_fil_img,mag_fil,pha_fil);
	write_file("magnitude_filtro.txt",mag_fil);

	convolution(array_x,array_fil,array_combx);
	write_file("convolution_x.txt",array_combx,size_array_2);
	discrete_fourier_transform(array_combx,array_combx_real,array_combx_img,size_array_2);
	bode(array_combx_real,array_combx_img,mag_combx,pha_combx,size_array_2);
	write_file("convolution_magx.txt",mag_combx,size_array_2);

	convolution(array_y,array_fil,array_comby);
	write_file("convolution_y.txt",array_comby,size_array_2);
	discrete_fourier_transform(array_comby,array_comby_real,array_comby_img,size_array_2);
	bode(array_comby_real,array_comby_img,mag_comby,pha_comby,size_array_2);
	write_file("convolution_magy.txt",mag_comby,size_array_2);

	convolution(array_z,array_fil,array_combz);
	write_file("convolution_z.txt",array_combz,size_array_2);
	discrete_fourier_transform(array_combz,array_combz_real,array_combz_img,size_array_2);
	bode(array_combz_real,array_combz_img,mag_combz,pha_combz,size_array_2);
	write_file("convolution_magz.txt",mag_combz,size_array_2);

	return 0;
}

void read_file(std::string file_name,  double *coord, int size){
	std::ifstream Read;
	Read.open(file_name);
 	int idx = 0;
 	if (Read.is_open()) {
 	while (idx<size ) {
    	Read >> coord[idx];
    	idx ++;
 		}
	}
	Read.close();	
}

void write_file(std::string file_name, double array_to_write[],int size){
	std::ofstream Write;
	Write.open(file_name);
	int idx = 0;
	if (Write.is_open()) {
 	while (idx<size) {
    	Write << array_to_write[idx];
    	Write << "\n";
    	idx ++;
 		}
	}
	Write.close();
}

void discrete_fourier_transform(double input_array[], double *output_real, double *output_img, int size){
	for(int var_k = 0;var_k < size;var_k++){
		double real = 0;
		double imag = 0;
		for(int var_n = 0; var_n < size;var_n++){
			real+=input_array[var_n]*(cos(2*M_PI*var_k*var_n/size));
			imag+=-input_array[var_n]*(sin(2*M_PI*var_k*var_n/size));
		}
		output_real[var_k] = real;
		output_img[var_k] = imag; 
	}
}

void bode(double input_real[], double input_img[],double *magnitude,double *phase,int size){
	for (int idx = 0; idx < size ; idx++){
		magnitude[idx]=sqrt(pow(input_real[idx],2)+pow(input_img[idx],2));
		phase[idx] = atan2(input_img[idx],input_real[idx]);
	}
}

void convolution(double input_array1[], double input_array2[],double *output_array,int size){
	for(int idx=0;idx<size;idx++){
		output_array[idx]=0;
		
		for (int var_k = 0; var_k < size+1; var_k++)
		{

			if (idx-var_k<0){
				break;
			}else if (idx-var_k>size_array||var_k>size_array){

			}else{

				output_array[idx] += input_array1[var_k]*input_array2[idx-var_k];
			}
		}	
	}
}









