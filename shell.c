#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<pwd.h>
#include <pthread.h>
void maninfo(){
    char * str="ECHO(1)                                            User Commands                                             ECHO(1)\n"

"NAME\n"
"       echo - display a line of text\n"

"SYNOPSIS\n"
"       echo [SHORT-OPTION]... [STRING]...\n"
"       echo LONG-OPTION\n"

"DESCRIPTION\n"
"       Echo the STRING(s) to standard output.\n"

"       -n     do not output the trailing newline\n"

"       -e     enable interpretation of backslash escapes\n"
        
"       -E     disable interpretation of backslash escapes (default)\n"

"       --help display this help and exit\n"

"       --version output version information and exit\n"

"       If -e is in effect, the following sequences are recognized:\n"

"       \\     backslash\n"

"        \\a     alert (BEL)\n"

"       \\b     backspace\n"

"       \\c     produce no further output\n"

"       \\e     escape\n"

"       \\f     form feed\n"

"       \\n     new line\n"

"       \\r     carriage return\n"

"       \\t     horizontal tab\n"

"       \\v     vertical tab\n"

"       \\0NNN  byte with octal value NNN (1 to 3 digits)\n"

"       \\xHH   byte with hexadecimal value HH (1 to 2 digits)\n"

"       NOTE:  your  shell  may  have  its  own  version of echo, which usually supersedes the version described here.\n"
"       Please refer to your shell's documentation for details about the options it supports.\n";
    printf("%s",str);
}
int checklen(char s[]){
    char * word=strtok_r(s," ",&s);
    int t=0;
    while(word!=NULL){
        t++;
        word=strtok_r(s," ",&s);
    }
    return t;
}
void createarray(char args2[],char *args[],char s[]){
    char s4[10000];
    char s5[10000];
    getcwd(s4,10000);
    int t=0;
    for(int i=0;s4[i]!='\0';i++){
        t++;
        args2[i]=s4[i];
    }
    args2[t]='/';
    t++;
    for(int i=0;s[i]!='\0';i++){
        args2[t]=s[i];
        t++;
    }
    args2[t]=' ';
    t++;
    for(int k=0;args[k]!=NULL;k++){
        strncpy(s5,args[k],sizeof(s5)-1);
        s5[sizeof(s5)-1]='\0';
        for(int i=0;s5[i]!='\0';i++){
            args2[t]=s5[i];
            t++;
        }
        args2[t]=' ';
        t++;
    }
    args2[t]='\0';
}
int checklast(char s[]){
    char * word=strtok_r(s," ",&s);
    char *str=strdup(word);
    while(word!=NULL){
        str=strdup(word);
        word=strtok_r(s," ",&s);
    }
    if(strcmp(str,"&t")==0){
        return 1;
    }
    return 0;
}

void printdir(char s[],char * actual_dir){
    char s6[1000];
    char *s2;
    char path[10000];
    char *s3=s;
    char *word;
    int pflag=0;
    int lflag=0;
    word=strtok_r(s3," ",&s3);
    word=strtok_r(s3," ",&s3);
    if(word!=NULL){
        if(strcmp(word,"-P")==0){
        pflag=1;
        word=strtok_r(s3," ",&s3);
        if(word !=NULL && word[0]=='-'){
            if(word !=NULL && strcmp(word,"-L")==0){
                lflag=1;
                pflag=0;
            }
            else{
                printf("Invalid option");
                return ;
            }
        }
    }
    else if(strcmp(word,"-L")==0){
        lflag=1;
        word=strtok_r(s3," ",&s3);
        if(word !=NULL && word[0]=='-'){
            if(strcmp(word,"-P")==0){
                lflag=0;
                pflag=1;
                word=strtok_r(s3," ",&s3);
            }
            else{
                printf("Invalid option");
                return ;
            }
        }
    }
    if(word!=NULL){
        printf("too many arguments");
    }
    }
    if(pflag==0){
        printf("%s\n",actual_dir);
    }
    else{
        getcwd(s6,1000);
        printf("%s\n",s6);
    }
}

void changedir(char s[],char **actual_dir){
    char *s2;
    char *s3=strdup(s);
    char *word;
    int pflag=0;
    int lflag=0;
    word=strtok_r(s3," ",&s3);
    word=strtok_r(s3," ",&s3);
    if(strcmp(word,"-P")==0){
        pflag=1;
        word=strtok_r(s3," ",&s3);
        if(word[0]=='-'){
            if(strcmp(word,"-L")==0){
                lflag=1;
                pflag=0;
            }
            else{
                printf("Invalid option");
                return ;
            }
        }
    }
    else if(strcmp(word,"-L")==0){
        lflag=1;
        word=strtok_r(s3," ",&s3);
        if(word[0]=='-'){
            if(strcmp(word,"-P")==0){
                lflag=0;
                pflag=1;
                word=strtok_r(s3," ",&s3);
            }
            else{
                printf("Invalid option");
                return ;
            }
        }
    }
    s2=strdup(word);
    word=strtok_r(s3," ",&s3);
    if(word!=NULL){
        printf("too many arguments");
    }
    else{
        if(lflag==0){
            if(strcmp(s2,"~")==0){
                chdir(getenv("HOME"));
            }
            else{
                char *s4;
                if(s2[0]=='~'){
                    s4=strtok_r(s2,"~/",&s2);
                    chdir(getenv("HOME"));
                    s2=s4; 
                }
                if(chdir(s2)==-1){
                    printf("no such directory\n");
                    return ;
                }
            }
            char s7[1000];
            getcwd(s7,sizeof(s7));
            *actual_dir=strdup(s7);
        }
        else{
            if(strcmp(s2,"~")==0){
                chdir(getenv("HOME"));
            }
            else{
                char *s4;
                if(s2[0]=='~'){
                    s4=strtok_r(s2,"~/",&s2);
                    chdir(getenv("HOME"));
                    s2=s4; 
                }
                if(chdir(s2)==-1){
                        printf("no such directory\n");
                        return;
                }
                char * word=strtok_r(s2,"/",&s2);
                char *s8;
                while(word!=NULL){
                    s8=strcat(*actual_dir,"/");
                    s8=strcat(*actual_dir,word);
                    word=strtok_r(s2,"/",&s2);
                }
                *actual_dir=strdup(s8);
            }
        }

    }
}
void printstring(char s[]){
    char *s3=strdup(s);
    char *word=strtok_r(s,"\"",&s);

    if(strcmp(word,s3)==0){
        char * s4=strdup(word);
        word=strtok_r(s4," ",&s4);
        word=strtok_r(s4," ",&s4);
        if(strcmp(word,"--help")==0){
            maninfo();
        }
        else{
            printf("Invalid syntax");
        }
    }
    else{
        char * s5=strdup(word);
        char * s6;
        word=strtok_r(s5," ",&s5);
        int n=0;
        while(word!=NULL){
            s6=strdup(word);
            word=strtok_r(s5," ",&s5);
            n++;
        }
        if(n>2){
            printf("Invalid syntax\n");
        }
        else if(n==2 && strcmp(s6,"-n")==0){
            word=strtok_r(s,"\"",&s);
            printf("%s",word);        
        }
        else if(n==1){
            word=strtok_r(s,"\"",&s);
            printf("%s\n",word);   
        }
        else{
            printf("Invalid option");
        }   
    }
}
int main(){
    char str[1000];
    char *str2;
    char str4[1000];
    char str3[1000];
    char str5[1000];
    char current_dir[1000];
    char args2[10000];
    char *actual_dir;
    char filedir[1000];
    char * filename;
    getcwd(current_dir,sizeof(current_dir));
    getcwd(filedir,sizeof(filedir));
    actual_dir=current_dir;
    while(1){
        printf("<Shell %s>",actual_dir);
        fgets(str,1000,stdin);
        str[strlen(str)-1]='\0';
        strcpy(str4,str);
        strcpy(str3,str);
        strcpy(str5,str);
        char *temp=str4;
        str2=strtok_r(temp," ",&temp);
        
        if(strcmp(str2,"cd")==0){
            int _l=0,_p=0;
            int t=checklen(str3);
            if(t==1){
                int z=strlen(str);
                str[z]=' ';
                str[z+1]='~';
                str[z+2]='\0';
                changedir(str,&actual_dir);
            }
            else {
                changedir(str,&actual_dir);
            }
        }
        else if(strcmp(str2,"pwd")==0){
            printdir(strdup(str3),actual_dir);
            
        }
        else if(strcmp(str2,"exit")==0){
            return 0;
        }
        else if(strcmp(str2,"echo")==0){
            
                printstring(str3);
        }
        else if(strcmp(str2,"ls")==0){
            str2=strtok_r(temp," ",&temp);
            char *args[4]={"\0","\0","\0","\0"};
            int n=0;
            while(str2!=NULL){
                if(strcmp(str2,"&t")!=0){
                    args[n]=str2;
                    n++;
                }
                str2=strtok_r(temp," ",&temp);
            }
            char s10[1000];
            getcwd(s10,1000);
            args[n]=strdup(s10);
            args[n+1]=NULL;
            if(checklast(str5)==0){
            int x=fork();
            if(x==0){
                filename=strcat(filedir,"/ls");
                execv(filename,args);
                perror("message :");
            }
            else if(x>0){
                int w=wait(NULL);
            }}
            else{
                createarray(args2,args,"ls");
                pthread_t pt;
                pthread_create(&pt,NULL,(void *)(*system),(void *)args2);
                pthread_join(pt,NULL);
            }
        }
        else if(strcmp(str2,"cat")==0){
            str2=strtok_r(temp," ",&temp);
            char *args[1000];
            int n=0;
            while(str2!=NULL){
                if(strcmp(str2,"&t")!=0){
                    args[n]=str2;
                    n++;
                }
                str2=strtok_r(temp," ",&temp);
            }
            args[n]=NULL;
            if(checklast(str5)==0){
            int x=fork();
            if(x==0){
                filename=strcat(filedir,"/cat");
                execv(filename,args);
                perror("message :");
            }
            else if(x>0){
                int w=wait(NULL);
            }}
            else{
                createarray(args2,args,"cat");
                pthread_t pt;
                pthread_create(&pt,NULL,(void *)(*system),(void *)args2);
                pthread_join(pt,NULL);
            }
        }
        else if(strcmp(str2,"date")==0){
            str2=strtok_r(temp," ",&temp);
            char *args[1000];
            int n=0;

            while(str2!=NULL){
                if(strcmp(str2,"&t")!=0){
                    args[n]=str2;
                    n++;
                }
                str2=strtok_r(temp," ",&temp);
            }
            if(n==0){
                args[n]="\0";
                n++;
            }
            args[n]=NULL;
            if(checklast(str5)==0){
            int x=fork();
            if(x==0){
                filename=strcat(filedir,"/date");
                execv(filename,args);
                perror("message :");
            }
            else if(x>0){
                int w=wait(NULL);
            }
            }
             else{
                createarray(args2,args,"date");
                pthread_t pt;
                pthread_create(&pt,NULL,(void *)(*system),(void *)args2);
                pthread_join(pt,NULL);
            }
        }
        else if(strcmp(str2,"rm")==0){
            str2=strtok_r(temp," ",&temp);
            char *args[1000];
            int n=0;

            while(str2!=NULL){
                if(strcmp(str2,"&t")!=0){
                    args[n]=str2;
                    n++;
                }
                str2=strtok_r(temp," ",&temp);
            }
            args[n]=NULL;
            if(checklast(str5)==0){
            int x=fork();
            if(x==0){
                filename=strcat(filedir,"/rm");
                execv(filename,args);
                perror("message :");
            }
            else if(x>0){
                int w=wait(NULL);
            }}
             else{
                createarray(args2,args,"rm");
                pthread_t pt;
                pthread_create(&pt,NULL,(void *)(*system),(void *)args2);
                pthread_join(pt,NULL);
            }
        }
        else if(strcmp(str2,"mkdir")==0){
            str2=strtok_r(temp," ",&temp);
            char *args[1000];
            int n=0;

            while(str2!=NULL){
                if(strcmp(str2,"&t")!=0){
                    args[n]=str2;
                    n++;
                }
                str2=strtok_r(temp," ",&temp);
            }
            args[n]=NULL;
            if(checklast(str5)==0){
            int x=fork();
            if(x==0){
                filename=strcat(filedir,"/mkdir");
                execv(filename,args);
                perror("message :");
            }
            else if(x>0){
                int w=wait(NULL);
            }}
             else{
                createarray(args2,args,"mkdir");
                pthread_t pt;
                pthread_create(&pt,NULL,(void *)(*system),(void *)args2);
                pthread_join(pt,NULL);
            }
        }
        else{
            printf("%s: command not found\n",str2);
        }    
    }
    return 0;
}
