
#ifndef  _MYERROR_H
#define  _MYERROR_H

//serial error     1
// error           2
// warning         3
// information     4


#define    DEBUG1(...)      fprintf(stderr,"SERI ERR: " __VA_ARGS__);
#define    DEBUG2(...)      fprintf(stderr,"ERR: " __VA_ARGS__);
#define    DEBUG3(...)      fprintf(stdout,"WARNING: " __VA_ARGS__);
#define    DEBUG4(...)      fprintf(stdout,"INFORMATION: " __VA_ARGS__);
#define    DEBUG()			fprintf(stdout,"\033[32mbug at func( %s ) : %d\033[0m\n", __func__, __LINE__);


#define    ERR(lever ,con, ret , ...)					\
		   do										\
			{										\
				if(con)								\
				{									\
					DEBUG##lever(__VA_ARGS__)		\
					ret;							\
				}									\
			}while(0)

#endif  //_MYERROR_H
