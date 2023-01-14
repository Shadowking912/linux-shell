#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<pwd.h>
int main(int argc,char *argv[]){
    int fflag=0;
    int iflag=0;
    int h1=0;
    int h2=0;
    int nt=0;
    char s6[1000];
    getcwd(s6,1000);
    strcat(s6,"/rm");
    if(argc>1 && strcmp(s6,argv[0])==0){
        nt++;
    }
    if(argc>1+nt && argv[0+nt]!="\0"){
            if(strcmp(argv[0+nt],"-f")==0){
                h1=0;
                fflag=1;
            }
            else if(strcmp(argv[0+nt],"-i")==0){
                iflag=1;
            }
        }
    if(argc>1+nt && argv[1+nt]!="\0"){
        if(strcmp(argv[1+nt],"-f")==0){
            h1=1;
            fflag=1;
        }
        else if(strcmp(argv[1+nt],"-i")==0){
            iflag=1;
        }
    }
    if(fflag==0 && iflag==0 && argv[0+nt][0]=='-'){
        printf("Invalid option\n");
        return 0;
    }
    int nf=iflag+fflag;
    if(fflag==1){
        if(iflag==0 || h1==1){
            for(int i=nf;argv[i+nt]!=NULL;i++){
                if(access(argv[i+nt],F_OK)==0){
                    remove(argv[i+nt]);
                }

            }
        }
        else if(iflag==1 && h1==0){
            for(int i=nf;argv[i+nt]!=NULL;i++){
                if(access(argv[i+nt],F_OK)==0){

                printf("Do you want to remove regular file %s ?",argv[i+nt]);
                char *ch;
                fgets(ch,1,stdin);
                if(ch=="y"){
                    remove(argv[i+nt]);
                }
                }
                else{
                    printf("file %s doesnt exist\n",argv[i+nt]);
                }
            }
        }
    }
    else{
        if(iflag==0){
            for(int i=nf;argv[i+nt]!=NULL;i++){
                if(access(argv[i+nt],F_OK)==0){

                remove(argv[i+nt]);
                }
                else{
                    printf("file %s doesnt exist\n",argv[i+nt]);
                }
            }
        }
        else{
            for(int i=nf;argv[i+nt]!=NULL;i++){
                if(access(argv[i+nt],F_OK)==0){
                printf("Do you want to remove regular file %s ?",argv[i+nt]);
                char ch;
                scanf("%c",&ch);
                if(ch=='y'){
                    remove(argv[i+nt]);
                }
                }
                else{
                    printf("file %s doesnt exist\n",argv[i+nt]);
                }
            }
        }
    }
    return 0;
}