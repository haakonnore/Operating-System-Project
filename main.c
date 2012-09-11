#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    const char * strn = "/home/haakon/Input/test1.txt"; // hvordan lese input? Hvordan finne ut hvor filen kjøres fra (bane)
    FILE * fp = fopen(strn, "r");

    char * job1 = NULL;
    char * job2 = NULL;
    char * job3 = NULL;
    char * job4 = NULL;
    ssize_t readline;
    size_t len = 0;
    readline = getline(&job1,&len, fp);
    readline = getline(&job2,&len, fp);
    readline = getline(&job3,&len, fp);
    readline = getline(&job4,&len, fp);
    fclose(fp);
    int lines[4];
    lines[3] = numLines(job4); // fungerer men hacket inn filbane
    int job[4];
    job[3] = startJob(job4); // fungerer men hacket inn filbane
    lines[3] = 13;
    lines[2] = 2;
    lines[1] = 24;
    lines[0] = 40;
    job[0]= 13;
    job[1]= 22;
    job[2]= 29;
    job[3]= 18;

    algFcfs2(lines, job);

}



int algFcfs2(int * lines, int * job){
    int i;
    int min;
    int minI;
    int counter = 0;

    int nextStart = 0;
    while(counter < 4){
        min = 2147483647;
        for(i = 0; i<4; i++){
            if(job[i]< min && job[i]!=-1){
                min = job[i];
                minI = i;
            }
        }
        int start = min;
        if (start<nextStart){
            start = nextStart;
        }
        nextStart= start + lines[minI] + 1;
        printf("Job%i starts at %i and ends at %i\n", minI + 1, start, nextStart-1 );
        job[minI] = -1;
        counter++;
    }

}






int startJob(char * job){
    const char * toRead = "/home/haakon/Input/job4.txt"; // samme problem som i numlines(),
    FILE* fp2 = fopen(toRead, "r");
    ssize_t readline;
    size_t len = 0;
    char * firstLine = "";
    readline = getline(&firstLine,&len, fp2);

    return firstLine;

}



int numLines(char * job){

    char temp[159] = "/home/haakon/Input/";
    strcat(temp, job);
    const char * toRead = "/home/haakon/Input/job4.txt"; // setter man denne til temp, funker det ikke, vhrofor må man skrive den inn manuelt?
    FILE* fp2 = fopen(toRead, "r");
    ssize_t readline;
    int  numberOfLines = -1;
    int ch;
    do {
        ch = fgetc(fp2);
        if(ch == '\n')
                numberOfLines++;
    } while (ch != EOF);
    fclose(fp2);
    return numberOfLines ;
}
