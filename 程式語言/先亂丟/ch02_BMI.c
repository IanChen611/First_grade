#include<stdio.h>

int main(){
    while(1){
        float height, weight;
        scanf("%f", &height);
        if(height==-1) break;
        scanf("%f", &weight);
        height = height * 0.01;
        weight = weight * 0.454;
        //printf("height = %f, weight = %f\n", height, weight);
        if(height<0.5 || height>2.5){
            printf("Input Height Error\n");
            continue;
        }
        if(weight<20 || weight>300){
            printf("Input Weight error\n");
            continue;
        }
        float bmi = weight / (height * height);
        if(bmi > 24){
            printf("BMI too high\n");
            continue;
        }
        else if(bmi < 18.5){
            printf("BMI too low\n");
        }
        else printf("%.2lf\n", bmi-0.005);
    }

}