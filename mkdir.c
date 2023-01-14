#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<pwd.h>
#include <stdlib.h>
#include<sys/stat.h>
int main(int argc,char *argv[]){
    int pflag=0;
    int vflag=0;
    int nt=0;
    char s6[1000];
    getcwd(s6,1000);
    strcat(s6,"/mkdir");
    if(argc>1 && strcmp(s6,argv[0])==0){
        nt++;
    }
    if(argc>1+nt && argv[0+nt]!="\0"){
        if(strcmp(argv[0+nt],"-p")==0){
            pflag=1;
        }
        else if(strcmp(argv[0+nt],"-v")==0){
            vflag=1;
        }
    }
    if(argc>2+nt && argv[1+nt]!="\0"){
        if(strcmp(argv[1+nt],"-p")==0){
            pflag=1;
        }
        else if(strcmp(argv[1+nt],"-v")==0){
            vflag=1;
        }
    }
    else if(pflag==0 && vflag==0 && argv[0+nt][0]=='-'){
        printf("Invalid option\n");
        return 0;
    }
    int nf=pflag+vflag;
    char str3[1000];
    getcwd(str3,1000);
    if(pflag==1){
        if(vflag==1){
            if(chdir(argv[nf+nt])==0){
                printf("directory exists\n"); 
                chdir(str3);
            }
            else if(mkdir(argv[nf+nt],0700)==0){
                printf("created directory %s\n",argv[nf+nt]);
            }
            else{
                
                char *str=strdup(argv[nf+nt]);
                if(argv[nf+nt][0]=='~'){
                    chdir(getenv("HOME"));
                    char * word=strtok_r(str,"/",&str);
                }
                if(argv[nf+nt][0]=='/'){
                    printf("directory cannot be created :permission denied\n");
                    return 0;
                }
                char * word=strtok_r(str,"/",&str);
                while(word!=NULL){
                    mkdir(word,0700);
                    chdir(word);
                    word=strtok_r(str,"/",&str);
                }
                chdir(str3);
                printf("created directory %s\n",argv[nf+nt]);
            }
        }
        else{
            if(chdir(argv[nf+nt])==0){
                printf("directory exists\n"); 
                chdir(str3);
            }
            else if(mkdir(argv[nf+nt],0700)==0){
                printf("created directory %s\n",argv[nf+nt]);
            }
            else{
                char str3[1000];
                getcwd(str3,1000);
                char *str=strdup(argv[nf+nt]);
                if(argv[nf+nt][0]=='~'){
                    chdir(getenv("HOME"));
                    char * word=strtok_r(str,"/",&str);
                }
                if(argv[nf+nt][0]=='/'){
                    printf("directory cannot be created :permission denied\n");
                    return 0;
                }
                char * word=strtok_r(str,"/",&str);
                
                while(word!=NULL){
                    if(chdir(word)!=0){
                        mkdir(word,0700);
                        chdir(word);
                    }
                    word=strtok_r(str,"/",&str);
                }
                chdir(str3);
            } 
        }
    }
    else{
        if(vflag==1){
            if(chdir(argv[nf+nt])==0){
                printf("directory exists\n"); 
                chdir(str3);
            }
            else if(mkdir(argv[nf+nt],0700)==0){
                printf("created directory %s\n",argv[nf+nt]);
            }
            else{
                printf("cannot create directory :file or folder %s doesnt exist\n",argv[nf+nt]);
            }
        }
        else{
            if(chdir(argv[nf+nt])==0){
                printf("directory exists\n"); 
                chdir(str3);
            }
            else if(mkdir(argv[nf+nt],0700)!=0){
                printf("cannot create directory :file or folder %s doesnt exist\n",argv[nf+nt]);
            } 
        }
    }
    return 0;
}