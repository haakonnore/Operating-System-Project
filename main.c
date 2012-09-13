#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char ** argv)
{

    srand( time(NULL));// Random seed for RR
    char * fileToRun;
    if(argc>4 || argc < 3)
        exit 1;
    if(argc == 4 && strcmp("RR",argv[1]))

    const char * strn = "./";
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
    lines[3] = 19;
    lines[2] = 13;
    lines[1] = 11;
    lines[0] = 28;
    job[0]= 1;
    job[1]= 1;
    job[2]= 1;
    job[3]= 1;

    if( strcmp(argv[1] ,"RR")==0&& argc == 4){
        char quantum  = atoi(argv[2]);
        algRR(lines, job, (int)quantum);
    }
    if( strcmp(argv[1] ,"FCFS")==0 && argc== 3)
        algFcfs(lines, job);
}

int algRR(int * lines, int * job, int quantum){
    int i;
    int min = job[0];
    int minI = 0;
    char one[200]   = "job1";
    char two[200]   = "job2";
    char tree [200] = "job3";
    char four[200]  = "job4";
    int counter = 0;
    int  roulette[4];
    int numInRoulette = 0;

    while (lines[0]>0|| lines[1]>0|| lines[2]>0||0< lines[3]){

        numInRoulette = 0;
        for(i = 0; i<4; i++){
            if(lines[i]>0 && job[i]<counter){
                roulette[numInRoulette++] = i;

            }
        }

//    printf("Min båt er lastet med %i kameler!\n", quantum);

  //              printf("Din båt er lastet med %i kameler!\n", quantum);


        if( numInRoulette > 0){

            int ran = rand() % numInRoulette; // bad random function
            int winner = roulette[ran];
            lines[winner] -= quantum;
            char buffer[20] = "";
            char count[50] = "";

            sprintf(buffer, "%d", counter);

            strcat(count, buffer);

            if(winner == 0){
                strcat(one, " ");
                strcat(one, count);
            }
            if(winner == 1){
                strcat(two, " ");
                strcat(two, count);
            }
            if(winner == 2){
                strcat(tree, " ");
                strcat(tree, count);
            }
            if(winner == 3){
                strcat(four, " ");
                strcat(four, count);
            }
        }


        counter+= quantum;
    }
    printf("%s\n", one);
    printf("%s\n", two);
    printf("%s\n", tree);
    printf("%s\n", four);
}


int algFcfs(int * lines, int * job){
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
