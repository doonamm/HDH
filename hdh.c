#include <stdio.h>

char defaultData[] = "123412512345";
int frameNum;
int n = 12;
int faultCount = 0;
int input[100];
int p[50];
int pf[100];
int tg[100][100];

void getDataDefault();
void getDataManual();
void getDataFrame();
void getAlgorithm();
void initialize();
void printResult();
int isHit(int data);
void FIFO();
void OPT();
void LRU();

int main(){
    int choice = 0;
    
    while(choice == 0){
        printf("---Page Replacement Algorithm---\n");
        printf("1. Default referenced sequence\n");
        printf("2. Manual input sequence\n");
        scanf("%d", &choice);
        
        switch(choice){
            case 1:
                getDataDefault();
                break;
            case 2:
                getDataManual();
                break;
            default:
                printf("Invalid choose: Please type again!\n");
                choice = 0;
                break;
        }
    }
    
    return 0;
}

void getDataDefault(){
    n=12;
    
    for(int i=0; i<n; i++){
        input[i] = defaultData[i] - '0';
    }
    
    getDataFrame();
}

void getDataManual(){
    printf("\nEnter length of page reference sequence:");
    scanf("%d", &n);
    printf("\nEnter the page reference sequence:");
    for(int i=0; i<n; i++){
        scanf("%d", &input[i]);
    }
    
    getDataFrame();
}

void getDataFrame(){
    frameNum = 0;
    while(frameNum < 1){
        printf("\nEnter no of frames:");
        scanf("%d", &frameNum);
    }
    
    getAlgorithm();
}
void getAlgorithm(){
    int choice = 0;
    while(choice == 0){
        printf("---Page Replacement algorithm---\n");
        printf("1. FIFO algorithm\n");
        printf("2. OPT algorithm\n");
        printf("3. LRU algorithm\n");
        scanf("%d", &choice);
        
        switch(choice){
            case 1:
                FIFO();
                break;
            case 2:
                OPT();
                break;
            case 3:
                LRU();
                break;
            default:
                printf("Invalid choose! Please type again.\n");
                choice = 0;
                break;
        }
    }
}

void initialize(){
    faultCount = 0;
    for(int i=0; i<frameNum; i++){
        p[i] = -1;
    }
}

void printResult(){
    printf("---Page Replacement algorithm---\n");
    
    for(int i=0; i<n; i++){
        printf("%d ", input[i]);
    }
    
    for(int i=0; i<frameNum; i++){
        printf("\n");
        for(int k=0; k<n; k++){
            if(tg[i][k] == -1){
                printf("  ");
            }
            else{
                printf("%d ", tg[i][k]);
            }
        }
    }
    
    printf("\n");
    for(int i=0; i<n; i++){
        if(pf[i] == 1){
            printf("* ");
        }
        else{
            printf("  ");
        }
    }
    
    printf("\n\nNumber of page faults: %d", faultCount);
}

int isHit(int data){
    int hit = 0;
    for(int i=0; i<frameNum; i++){
        if(p[i]==data){
            hit = 1;
            break;
        }
    }
    return hit;
}

void FIFO(){
    initialize();
    
    for(int i=0; i<n; i++){
        if(isHit(input[i]) == 0){
            int k;
            
            for(k=0; k<frameNum - 1; k++){
                p[k] = p[k+1];
            }
            
            p[k] = input[i];
            for(int j=0; j<frameNum; j++){
                tg[j][i] = p[j];
            }
            
            pf[i] = 1;
            tg[frameNum][i] = 1;
            faultCount++;
        }
        else{
            pf[i] = 0;
            for(int k=0; k<frameNum; k++){
                tg[k][i] = p[k];
            }
        }
    }
    
    printResult();
}
void OPT(){
    initialize();
    
    int near[50];
    for(int i=0; i<n ; i++){
        if(isHit(input[i]) == 0){
            for(int j=0; j<frameNum; j++){
                int pg = p[j];
                int found = 0;
                
                for(int k=i; k<n; k++){
                    if(pg == input[k]){
                        near[j] = k;
                        found = 1;
                        break;
                    }
                    else{
                        found = 0;
                    }
                }
            
                if(found == 0){
                    near[j] = 9999;
                }
            }
            
            int max = -9999;
            int repIndex = 0;
            
            for(int j=0; j<frameNum; j++){
                if(near[j] > max){
                    max = near[j];
                    repIndex = j;
                }
            }
            
            pf[i] = 1;
            p[repIndex] = input[i];
            faultCount++;
            tg[frameNum][i] = 1;
        }
        else{
            pf[i] = 0;
        }
        for(int k=0; k<frameNum; k++){
            tg[k][i] = p[k];
        }
    }
    
    printResult();
}
void LRU(){
    initialize();
    
    int least[50];
    
    for(int i=0; i<n ; i++){
        if(isHit(input[i]) == 0){
            for(int j=0; j<frameNum; j++){
                int pg = p[j];
                int found = 0;
                
                for(int k=i-1; k>=0; k--){
                    if(pg == input[k]){
                        least[j] = k;
                        found = 1;
                        break;
                    }
                    else{
                        found = 0;
                    }
                }
            
                if(found == 0){
                    least[j] = -9999;
                }
            }
            
            int min = 9999;
            int repIndex = 0;
            
            for(int j=0; j<frameNum; j++){
                if(least[j] < min){
                    min = least[j];
                    repIndex = j;
                }
            }
            
            pf[i] = 1;
            p[repIndex] = input[i];
            faultCount++;
            tg[frameNum][i] = 1;
        }
        else{
            pf[i] = 0;
        }
        for(int k=0; k<frameNum; k++){
            tg[k][i] = p[k];
        }
    }
    
    printResult();
}