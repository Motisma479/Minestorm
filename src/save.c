#include <stdio.h>
#include <stdlib.h>
/***********************************\
Made by : Robion Mathieu
last edit: 15/10/2021
Desc:
    File to test save systeme
    The save saves position of player
\***********************************/




///////////////////////////////////////////////////////////////////////////////////////////
//                                 Save / Load Function                                  //
///////////////////////////////////////////////////////////////////////////////////////////
void saveHScore(int score){
//load the file
    FILE* Save = fopen("save.txt", "w");
    if (Save == NULL)//cant't open the
    {
        printf("Cannot save.txt\n");
        return 1;
    }
//loading end

    fprintf(Save,"HihScore: %d", score);

    fclose(Save);//close file
}

int loadHScore(){
//load the file
    FILE* Save = fopen("save.txt", "r");
    if (Save == NULL)//cant't open the
    {
        printf("Cannot save.txt\n");
        return 1;
    }
//loading end
    char line[1024];
    
    int intHScore = atoi(fgets(line,1024,Save)+10);

    fclose(Save);//close file

    return intHScore;
}
///////////////////////////////////////////////////////////////////////////////////////////