#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
#include<pwd.h>
void sort(char *s[10000],int t){
    char s1[100];
    for(int i=0;i<t;i++){
        for(int j=i+1;j<t;j++){
            if(strcasecmp(s[i],s[j])>0){
                strcpy(s1,s[i]);
                strcpy(s[i],s[j]);
                strcpy(s[j],s1);
            }
        }
    }
}
int main(int argc,char *argv[]){
    char * s[10000];
    DIR *directory;
    struct dirent *d;
    int t=0;
    int rflag=0;
    int aflag=0;
    int nf=0;
    int nt=0;
    char s6[1000];
    getcwd(s6,1000);
    strcat(s6,"/ls");
    if(argc>1 && strcmp(s6,argv[0])==0){
        nt++;
    }
    if(argc>1+nt && argv[0+nt]!="\0"){
        if(strcmp(argv[0+nt],"-a")==0){
            aflag=1;
        }
        else if(strcmp(argv[0+nt],"-r")==0){
            rflag=1;
        }
    }
    if(argc>2+nt && argv[1+nt]!="\0"){
        if(strcmp(argv[1+nt],"-a")==0){
            aflag=1;
        }
        else if(strcmp(argv[1+nt],"-r")==0){
            rflag=1;
        }
    }
    if(aflag==0 && rflag==0 && argv[0+nt][0]=='-'){
        printf("Invalid option\n");
        return 0;
    }
    else if(aflag==0 && rflag==0 && argc>1+nt){
        printf("Too many arguments\n");
        return 0;
    }
    nf=aflag+rflag;
    directory=opendir(argv[nf+nt]);
    if(directory!=NULL){
        while((d=readdir(directory))!=NULL){
            s[t]=d->d_name;
            t++;
        }
        sort(s,t);
        
        if(rflag==1){
            if(aflag==1){
                for(int i=t-1;i>-1;i--){
                    printf("%s  ",s[i]);
                }
            }
            else{
                for(int i=t-1;i>-1;i--){
                    if(s[i][0]!='.'){
                        printf("%s  ",s[i]);
                    }
                }
            }
        }
        else{
            if(aflag==1){
                for(int i=0;i<t;i++){
                    printf("%s  ",s[i]);
                }
            }
            else{
                for(int i=0;i<t;i++){
                    if(s[i][0]!='.'){
                        printf("%s  ",s[i]);
                    }
                }
            }
        }
        printf("\n");
    }
    return 0;
}