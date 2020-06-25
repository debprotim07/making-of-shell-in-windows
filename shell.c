#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<ctype.h> 
#include<unistd.h> 
#include<math.h> 
#include<dirent.h> 
#include<time.h> 
 
int i,j,ec,fg,ec2; int last = 0; char fn[20],e,c; 
 
FILE *fp1,*fp2,*fp; 
 
void Create(); void Append(); void Delete(); void Display(); void TextEditor(); void cd(); void listHistory(); 
void newCmd(char* cmd); 
void ls(); void disp_time(); 
 
typedef struct{ char history[30]; 
}list; 
 
list history_list[100]; 
 
void basic_loop(void){ char input[50] = ""; char file_name[30]; 
 
char process_name[30]; 
 
while(strcmp("exit",input)!=0) 
{ 
printf("\n>>"); scanf("%s",input); 
 
newCmd(input); 
 
if(strcmp("help",input) == 0) 
{ printf("Shell Features are \n"); 
 
printf("1)  addition,subtraction,multiplication \n\t,power & division can be performed for 2 integers with no spacing.\n"); printf("2) editor -To use text editor\n"); printf("3) cd   - Prints the current directory.\n"); printf("4) history - History Command\n"); printf("5) ls   - Shows all files in current directory!\n"); printf("6) time  - Displays current date & time!\n"); 
printf("7) gcc   - Runs a compiler to compile C/C++ files in the current directory!\n"); printf("8) rm  - Removes a file.\n"); printf("9) start   - Shows the output of the compiled file!\n"); printf("10) run  - to run application!\n"); printf("11) exit  - To exit!"); 
} 
 
else if(strcmp("exit",input)==0) 
{     printf("Goodbye !"); 
    exit(0); 
} 
 
else if(strcmp("ls",input)==0) 
{ 
    ls(); 
} 
 
else if(strcmp("gcc",input) == 0) 
{     char system_call[100];     scanf("%s",file_name); 
 
    sprintf(system_call, "%s %s", input, file_name);     int error = system(system_call);     if(error == 0) 
    { 
        printf("Compilation successfull!\n"); 
    } 
 
} 
 
else if(strcmp("start",input) == 0) 
{     char system_call[100];     scanf("%s",file_name); 
 
    sprintf(system_call, "%s %s", input, file_name);     int error = system(system_call);     if(error == 0) 
    { 
        printf("Compilation successfull!\n"); 
    } 
 
} else if(strcmp("run",input) == 0) 
{     char system_call[100];     scanf("%s",process_name);     sprintf(system_call,"%s",process_name);     printf("Wait\n");     system(system_call);     printf("Application closed\n"); 
} 
 
else if(strcmp("time",input) == 0) 
    { 
        disp_time(); 
    } 
 
else if(isdigit(input[0])) 
{ float first, second; 
 
if(strchr(input,'+')) { 
sscanf(input,"%f+%f",&first,&second); printf("%f",first+second); 
} 
 
else if(strchr(input,'-')) 
    { 
    sscanf(input,"%f-%f",&first,&second);     printf("%f",first-second); 
 
} 
 
else if(strchr(input,'*')) 
    { 
        sscanf(input,"%f*%f",&first,&second);         printf("%f",first*second); 
} 
 
else if(strchr(input,'/')) 
    { 
        sscanf(input,"%f/%f",&first,&second);         printf("%f",first/second); 
 
} 
 
else if(strchr(input,'^')) 
    { 
        sscanf(input,"%f^%f",&first,&second);         printf("%f",pow(first,second)); 
 
} 
 
} else if(strcmp("rm",input)==0) 
{ 
  	Delete(); 
} else if(strcmp("editor",input) == 0) 
    { 
        printf("\nWelcome!"); 
        TextEditor(); 
} 
 
else if(strcmp("cd",input)==0) 
{ cd(); } 
 
else if(strcmp("history",input)==0) 
{ listHistory(); 
} 
 
else { printf("Unknown command! Please enter 'help' to get the list of commands"); 
} 
} 
 
} 
 
void TextEditor() 
{ do { printf("\n\nSelect functions:"); 
 
printf("\n1.Create a file.\n2.Display the contents.\n3.Append in a file.\n4.Delete a file.\n5.Exit the editor.\n"); printf("Enter your choice: "); scanf("%d",&ec); switch(ec) { case 1: Create(); break; 
 
case 2: Display(); break; 
 
case 3: Append(); break; 
 
case 4: Delete(); break; 
 
case 5: basic_loop(); break; 
} } while(1); 
 
} void Create() 
{ 
fp1=fopen("temp.txt","w"); 
 
printf("\nEnter the text and press '.' to save!\n\n"); while(1) { c=getchar(); 
 
fputc(c,fp1); 
if(c == '.') { fclose(fp1); printf("\nEnter then new filename: "); scanf("%s",fn); fp1=fopen("temp.txt","r"); fp2=fopen(fn,"w"); while(!feof(fp1)) 
{ 
 
c=getc(fp1); putc(c,fp2); } fclose(fp2); break; } 
} 
 
} 
 
void Display() 
{
 
printf("\nEnter file name: "); scanf("%s",fn); fp1=fopen(fn,"r"); 
if(fp1==NULL) 
{ printf("\n\tFile not found!"); goto end1; } while(!feof(fp1)) { c=getc(fp1); 
 
printf("%c",c); } end1: fclose(fp1); printf("\n\nPress any key to continue!"); 
} 
 
void Delete() 
{ 
 
  	printf("\nEnter file name: "); 
  	scanf("%s",fn); 
    fp1=fopen(fn,"r");     if(fp1==NULL) 
    { 
        printf("\nFile not found!"); 
  	  	goto end2; 
  	} 
  	fclose(fp1);   	if(remove(fn)==0) 
    { 
  	  	printf("\n\nFile deleted successfully!"); 
        goto end2; 
  	} 
  	else printf("\nError!\n"); 
  	end2: 
  	printf("\n\nPress any key to continue!"); 
} 
 
void Append() 
 
{ 
 
printf("\nEnter the file name: "); scanf("%s",fn); fp1=fopen(fn,"r"); 
if(fp1==NULL) 
{ printf("\nFile not found!"); goto end3; } while(!feof(fp1)) 
{
c=getc(fp1); printf("%c",c); } fclose(fp1); printf("\nType the text and press 'Ctrl+S' to append.\n"); fp1=fopen(fn,"a"); while(1) 
{ 
 
if(c==19)     goto end3; 
 
if(c==13) { c='\n'; 
 
printf("\n\t"); fputc(c,fp1); } else 
    { 
        printf("%c",c);         fputc(c,fp1); 
    } 
} end3: fclose(fp1); } 
 
void cd() { char *buf; 
 
buf=(char *)malloc(100*sizeof(char)); getcwd(buf,100); printf("The current directory is : %s",buf); 
 
} 
 
void ls() { 
DIR *d; 
 
struct dirent *dir; d = opendir("."); printf("\nThe files in the directory are: \n"); 
if (d) { while ((dir = readdir(d)) != NULL) 
{     printf("%s\n", dir->d_name); 
} closedir(d); 
} 
}
 
void newCmd(char* cmd) 
{     strcpy(history_list[last].history,cmd);     last++; 
} 
 
 
 
void listHistory() { printf("\nThe commands last entered are:\n"); 
int z; 
for (z = 0;z < last;z++) 
{ printf("%s\n",history_list[z].history); 
} 
} 
 
void disp_time() {     time_t t;     time(&t);     printf("Today's date and time : %s",ctime(&t)); 
} 
 
int main() 
{ 
printf("Welcome user to this basic UNIX shell! This has been implemented using C code.\n"); printf("\n Made by : \n"); 
printf("\n DEBPROTIM CHAKRABARTI (17BCE0408) \n"); printf("\n AAYUSH SAHAY (17BCE2141) \n"); printf("\n ANIKET GUPTA (17BCE2018) \n"); 
printf("\n\n"); printf("-----command prompt-----\n"); 
printf("\n"); 
 
basic_loop(); 
} 
