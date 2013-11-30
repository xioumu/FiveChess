#include"stdio.h"
int main()
{   
    long i,j,k,r;
    __int64 w;
    FILE *output;
    output = fopen("zobrist.txt","w");
  for(r=0;r<=200;r++,fprintf(output,"\n"))
    for(i=0;i<10;i++,fprintf(output,"\n"))
      for(j=0;j<3;j++,fprintf(output,"\n"))
        for(k=0;k<3;k++)
          fprintf(output,"%ld ",(long)rand() + (long)(rand() << 16) );        
   for(k=0;k<=3;k++,fprintf(output,"\n")) 
    for(i=0;i<=15;i++,fprintf(output,"\n"))  
      for(j=0;j<=15;j++)
      { 
         w = rand(); 
         w <<= 16; w += rand(); 
         w <<= 16; w += rand();
         w <<= 16; w += rand();
         fprintf(output,"%I64d ",w );
      }
    fprintf(output,"\n");  
   for(k=0;k<=3;k++,fprintf(output,"\n")) 
    for(i=0;i<=15;i++,fprintf(output,"\n"))  
      for(j=0;j<=15;j++)
      {
         w = rand(); 
         w <<= 16; w += rand(); 
         w <<= 16; w += rand();
         w <<= 16; w += rand();
         fprintf(output,"%I64d ",w );
      }   
   return 0;           
}
