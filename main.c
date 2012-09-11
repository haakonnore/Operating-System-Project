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
    lines[3] = 1;
    lines[2] = 1;
    lines[1] = 1;
    lines[0] = 1;
    job[0]= 1;
    job[1]= 1;
    job[2]= 1;
    job[3]= 1;

    algFcfs(lines, job);

}

int algFcfs(int * lines, int * job){
    //letters is starttime, numbers is lines in the job
    // må endre mye, pekere som endreer verdi, ikke som i "vanlige" språk
    int roundnr = 0; // what cylce is beein controled at that iteration ( may go trough same cycle several times)
    int bussyUntil = 0; // if bussyUntil > roundnr, the cpu is busy, and new jobs must wait
    int counter = 0; //number of prossesed jobs
    int i;//indexing job 1 to 4
    int queue = 0;

    int a = 5000;
    while(counter < 4&& a >0){
        a--;
        printf("Control of fields, Roundnr = %i, bussyUntil = %i, counter = %i\n", roundnr, bussyUntil, counter);


        for(i = 0; i <4; i++){
            if(job[i]==roundnr && roundnr<bussyUntil){
                job[i]= bussyUntil+ queue;
                queue++;
            }
            else if(job[i]==roundnr){
                bussyUntil = lines[i] + roundnr+ 1;
                printf("Job%i starting at: %i, and finnish at: %i \n", i+1, roundnr, roundnr + lines[i]);
                job[i]--;
                roundnr--;
                counter++;
                if(queue>0)
                    queue--;
                break;
            }

        }


        roundnr++;
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
