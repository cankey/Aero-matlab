/*
 * clapack_zheev.c
 *
 *This program is a C interface to zheev.
 *
 * Written by Remi Delmas.
 *
 */

#include "mex.h"

#define min(a,b) ((a)>(b) ? (b) : (a))
#define max(a,b) ((a)<(b) ? (b) : (a))

#if defined(ADD_)
	#define f77_zheev zheev_
#elif defined(UPCASE)
	#define f77_zheev ZHEEV
#else
	#define f77_zheev zheev
#endif

char *select_name;

void mexFunction(int nlhs_m, mxArray *plhs_m[], int nrhs_m, const mxArray *prhs_m[])
{

	int i;

	char * jobz;
	char * uplo;
	int * n;
	double * a;
	int * lda;
	double * w;
	double * work;
	int * lwork;
	double * rwork;
	int * info;

	plhs_m[2]=mxDuplicateArray(prhs_m[2]);
	n=(int *)mxGetPr(plhs_m[2]);

	plhs_m[4]=mxDuplicateArray(prhs_m[4]);
	lda=(int *)mxGetPr(plhs_m[4]);

	plhs_m[7]=mxDuplicateArray(prhs_m[7]);
	lwork=(int *)mxGetPr(plhs_m[7]);

	plhs_m[9]=mxDuplicateArray(prhs_m[9]);
	info=(int *)mxGetPr(plhs_m[9]);

	plhs_m[0] = mxDuplicateArray(prhs_m[0]);
	jobz = (char*) mxArrayToString(plhs_m[0]);

	plhs_m[1] = mxDuplicateArray(prhs_m[1]);
	uplo = (char*) mxArrayToString(plhs_m[1]);



	a=malloc((*lda)*(* n)*2*sizeof(double));
	for (i=0; i<(*lda)*(* n); i++)
	{
		a[i*2]=(mxGetPr(prhs_m[3]))[i];
		if (mxIsComplex(prhs_m[3]))
			a[i*2+1]=(mxGetPi(prhs_m[3]))[i];
		else
			a[i*2+1]=0;
	}



	plhs_m[5]=mxDuplicateArray(prhs_m[5]);
	w = mxGetPr(plhs_m[5]);

	work=malloc((max(1,*lwork))*(1)*2*sizeof(double));
	for (i=0; i<(max(1,*lwork))*(1); i++)
	{
		work[i*2]=(mxGetPr(prhs_m[6]))[i];
		if (mxIsComplex(prhs_m[6]))
			work[i*2+1]=(mxGetPi(prhs_m[6]))[i];
		else
			work[i*2+1]=0;
	}



	plhs_m[8]=mxDuplicateArray(prhs_m[8]);
	rwork = mxGetPr(plhs_m[8]);



#ifdef F77_INT
	F77_INT* F77_n = n , F77_lda = lda , F77_lwork = lwork , F77_info = info ;
#else
	#define F77_n n 
	#define F77_lda lda 
	#define F77_lwork lwork 
	#define F77_info info 
#endif

#ifdef F77_CHAR
	F77_CHAR* F77_jobz = jobz , F77_uplo = uplo ;
#else
	#define F77_jobz jobz 
	#define F77_uplo uplo 
#endif

	f77_zheev(F77_jobz, F77_uplo, F77_n, a, F77_lda, w, work, F77_lwork, rwork, F77_info);

	plhs_m[3] = mxCreateDoubleMatrix((*lda),(* n),mxCOMPLEX);
	for (i=0; i<(*lda)*(* n); i++)
	{
		(mxGetPr(plhs_m[3]))[i]=a[2*i];
		if (mxIsComplex(plhs_m[3]))
			(mxGetPi(plhs_m[3]))[i]=a[2*i+1];
	}

	plhs_m[6] = mxCreateDoubleMatrix((max(1,*lwork)),(1),mxCOMPLEX);
	for (i=0; i<(max(1,*lwork))*(1); i++)
	{
		(mxGetPr(plhs_m[6]))[i]=work[2*i];
		if (mxIsComplex(plhs_m[6]))
			(mxGetPi(plhs_m[6]))[i]=work[2*i+1];
	}

	return;
}
