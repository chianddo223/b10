#include <stdio.h>
#include <stdlib.h>

struct st_jumsu{
    char name[20]; // 이름 (공백 없이 영어 알파벳으로 구성)
    int jumsu[3]; // 3과목 점수 (국, 영, 수)
    int sum;	// 총점
    float avg;	// 평균
    char grade;	// 평균에 대한 등급
  };

char getGrade(float score);
//파라미터: 평균 점수(score) 
//리턴값: 해당 평균 점수의 등급 ('A','B','C','D','F')
void makeJumsu(struct st_jumsu* p);
//파라미터: 점수 데이터의 포인터(p) 
//리턴값: 없음
//수행내용: 해당 학생의 점수 데이터 구조체 내의 과목 점수로 총점, 평균, 등급을 넣는다.
void printJumsu(struct st_jumsu* p);
//파라미터: 점수 데이터의 포인터(p) 
//리턴값: 없음
//수행내용: 해당 학생의 점수 데이터 구조체 내의 값을 출력한다.
int getClassSum(struct st_jumsu* data[], int size, int index);
//파라미터: 점수 데이터의 포인터 배열(data), 점수 데이터 개수, 과목번호(0~2) 
//리턴값: 과목번호에 해당하는 점수의 총 합계
//수행내용: 모든 점수 데이터의 특정 과목번호의 점수 합계를 구한다.
struct st_jumsu* firstRanking(struct st_jumsu* data[], int size, int index);
//파라미터: 점수 데이터의 포인터 배열(data), 점수 데이터 개수, 과목번호(0~2) 
//리턴값: 과목번호에 해당하는 모든 점수 중 가장 높은 점수를 가진 점수 데이터 포인터
//수행내용: 모든 점수 데이터의 특정 과목번호의 점수 중에 가장 높은 점수를 가진 데이터를 찾아 그 데이터의 구조체 포인터를 리턴한다.
int countGrade(struct st_jumsu* data[], int size, char grade);
//파라미터: 점수 데이터의 포인터 배열(data), 점수 데이터 개수, 등급문자(A,B,C,D,F) 
//리턴값: 모든 점수 데이터 중 특정 등급을 가진 점수 데이터의 개수
//수행내용: 모든 점수 데이터 중 특정 등급을 가진 점수 데이터의 개수를 계산하여 리턴한다.

int main(void){
    int all;
    struct st_jumsu* jdata[20]; // 최대 20명의 점수 데이터
    int sum_class[3] = {0}; // 과목별 총점
    float average_class[3]; // 과목별 평균
    char class_name[3][20] = {"Korean", "English", "Math"};

    scanf("%d", &all);
    for(int i=0; i<all; i++){
        jdata[i] = (struct st_jumsu*)malloc(sizeof(struct st_jumsu));
        scanf("%s %d %d %d", jdata[i]->name, &(jdata[i]->jumsu[0]), &(jdata[i]->jumsu[1]), &(jdata[i]->jumsu[2]));
        makeJumsu(jdata[i]);
    }
    
    for(int i=0; i<3; i++){
        sum_class[i] = getClassSum(jdata, all, i);
    }

    for(int i=0; i<all; i++){
        printf("%d) ", i+1);
        printJumsu(jdata[i]);
    }
    
    for(int i=0; i<3; i++){
        average_class[i] = sum_class[i] / (float)all;
        
        struct st_jumsu* data = firstRanking(jdata, all, i);
        printf("[%s] %s %d\n", class_name[i], data->name, data->jumsu[i]);
    }
    
    for(int i=0; i<5; i++){
        printf("[%c] %d\n", 'A'+ i, countGrade(jdata, all, 'A'+i));
    }
    return 0;
}

char getGrade(float score){
    if(score >= 90){
        return 'A';
    }else if(score >= 80){
        return 'B';
    }else if(score >= 70){
        return 'C';
    }else if(score >= 60){
        return 'D';
    }else{
        return 'F';
    }
}

int getClassSum(struct st_jumsu* data[], int size, int index){
    int sum = 0;

    for(int i=0; i<size; i++){
        sum += data[i]->jumsu[index];
    }
    
    return sum;
}

struct st_jumsu* firstRanking(struct st_jumsu* data[], int size, int index){
    int max = 0;
    int max_index = 0;
    for(int i=0; i<size; i++){
        if(data[i]->jumsu[index] > max){
            max = data[i]->jumsu[index];
            max_index = i;
        }
    }

    return data[max_index];
}

void makeJumsu(struct st_jumsu* p){
        p->sum = 0;
        p->sum = p->jumsu[0] + p->jumsu[1] + p->jumsu[2];
        p->avg = p->sum / 3.0;
        p->grade = getGrade(p->avg);
}

void printJumsu(struct st_jumsu* p){
    printf("%s - %d %.1f %c\n", p->name, p->sum, p->avg, p->grade);
}

int countGrade(struct st_jumsu* data[], int size, char grade){
        int count = 0;
        for(int i=0; i<size; i++){
            if(data[i]->grade == grade){
                count ++;
            }
        }
        return count;
}