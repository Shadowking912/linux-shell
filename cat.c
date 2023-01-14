#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<pwd.h>
int main(int argc,char *argv[]){
    FILE * f;
    char c;
    char *c2;
    int nflag=0;
    int Eflag=0;
    int z=0;
    int nt=0;
    char s6[1000];
    getcwd(s6,1000);
    strcat(s6,"/cat");
    if(argc>1 && strcmp(s6,argv[0])==0){
        nt++;
    }
    if(argc>1+nt &&(strcmp(argv[0+nt],"-n")==0 || strcmp(argv[0+nt],"-E")==0)){
        z++;
        if(strcmp(argv[0+nt],"-n")==0){
            nflag=1;
        }
        else if(strcmp(argv[0+nt],"-E")==0){
            Eflag=1;
        }
    }
    if(argc>2+nt &&(strcmp(argv[1+nt],"-n")==0 || strcmp(argv[1+nt],"-E")==0)){
        z++;
        if(strcmp(argv[1+nt],"-n")==0){
            nflag=1;
        }
        else if(strcmp(argv[1+nt],"-E")==0){
            Eflag=1;
        }
    }
    if(argv[0+nt][0]=='-' && nflag==0 && Eflag==0){
        printf("invalid option\n");
        return 0;
    }
    for(int i=z;argv[i+nt]!=NULL;i++){
        f=fopen(argv[i+nt],"r");
        if(f!=NULL){
            if(nflag==1){
                int n=1;
                printf("1   ");
                if(Eflag==1){
                    c=fgetc(f);
                    while(c!=EOF){
                        if(c=='\r'){
                            
                            printf("^M$\n");
                        }
                        else if(c=='\n'){
                            n++;
                            printf("%d   ",n);
                        }
                        else{
                            printf("%c",c);
                        }
                        c=fgetc(f);
                    }
                }
                else{
                    c=fgetc(f);
                    while(c!=EOF){
                        if(c=='\n'){
                            n++;
                            printf("\n%d   ",n);
                        }
                        else{
                            printf("%c",c);
                        }
                        c=fgetc(f);
                    }
                }
            }
            else{
                if(Eflag==1){
                    c=fgetc(f);
                    c2=&c;
                    while(c!=EOF){
                        if(strcmp(c2,"\r")==0){
                            c=fgetc(f);
                            if(c=='\n'){
                                printf("^M$\n");
                            }
                        }
                        else{
                            if(c=='\n'){
                                printf("$");
                            }
                            printf("%c",c);
                        }
                        c=fgetc(f);
                    }
                }
                else{
                    c=fgetc(f);
                    while(c!=EOF){
                        printf("%c",c);
                        c=fgetc(f);
                    }
                }
            }
        }
        else{
            printf("Error: %s: No such file exits\n",argv[i+nt]);
        }
    }
    return 0;
}