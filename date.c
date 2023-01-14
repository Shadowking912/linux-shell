#include<stdio.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<pwd.h>
int main(int argc,char *argv[]){
    int uflag=0;
    int iflag=0;
    int h=0;
    int nt=0;
    char s6[1000];
    getcwd(s6,1000);
    strcat(s6,"/date");
    if(argc>1 && strcmp(s6,argv[0])==0){
        nt++;
    }
    if(argc>0+nt && argv[0+nt]!="\0"){
            if(strcmp(argv[0+nt],"-u")==0){
                uflag=1;
            }
            else if(strcmp(argv[0+nt],"-I")==0){
                h=0;
                iflag=1;
            }
        }
    if(argc>1+nt && argv[1+nt]!="\0"){
        if(strcmp(argv[1+nt],"-u")==0){
            uflag=1;
        }
        else if(strcmp(argv[1+nt],"-I")==0){
            h=1;
            iflag=1;
        }
    }
    if(uflag==0 && iflag==0 && argv[0+nt][0]=='-'){
        printf("invalid option\n");
        return 0;
    }
    if(uflag==0 && iflag==0 && argc>0+nt){
        printf("Invalid syntax\n");
        return 0;
    }
    char * s2,*str;
    char c[100];
    time_t t,t2;
    struct tm *curtime,*utc;
    time(&t);
    time(&t2);
    

    if(uflag==1){
        utc=gmtime(&t2);
        if(iflag==1){
            strftime(c,sizeof(c),"%Y-%m-%d\n",utc);
            printf("%s",c);
        }
        else{
            strftime(c,sizeof(c),"%A %d %B %Y %I:%M:%S %p %Z\n",utc);
            printf("%s",c);
        }
    }
    else{
        curtime=localtime(&t);
        if(iflag==1){
                strftime(c,sizeof(c),"%Y-%m-%d\n",curtime);
                printf("%s",c);
        }
        else{
            strftime(c,sizeof(c),"%A %d %B %Y %I:%M:%S %p %Z\n",curtime);
            printf("%s",c);
        }
    }
    
}