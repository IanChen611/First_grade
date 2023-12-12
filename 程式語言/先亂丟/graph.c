#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define pi 4

#define shapeText(TYPE) char name[10];\
        int (*sidesum)(struct TYPE*);\
        int (*area)(struct TYPE*);

typedef struct circle_s {
    shapeText(circle_s); 
    int radius;
} circle;

typedef struct rectangle_s {
    shapeText(rectangle_s); 
    int width, height;
} rectangle;

typedef struct square_s {
    shapeText(square_s); 
    int side;
} square;

typedef struct triangle_s {
    shapeText(triangle_s); 
    int s1, s2, s3;
} triangle;

int circle_area(circle *a){
    return pi*2*a->radius;
}

int circle_sidesum(circle *a){
    return 2*pi*a->radius;
}

int rectangle_area(rectangle *a){
    return a->height * a->width;
}

int rectangle_sidesum(rectangle *a){
    return a->height * 2 + a->width * 2;
}

int square_area(square *a){
    return a->side * a->side;
}

int square_sidesum(square *a){
    return a->side * 4;
}

int triangle_area(triangle *a){
    int s = a->s1 + a->s2 + a->s3;
    s = s / 2 ;
    return sqrt(s*(s-a->s1)*(s-a->s2)*(s-a->s3));
}

int triangle_sidesum(triangle *a){
    return a->s1 + a->s2 + a->s3;
}

int main(){
    int N;
    char buffer[15];
    for(int i=0;i<N;i++){
        gets(buffer);
        if(strcmp(buffer, "triangle")==0){
            triangle tem;
            int s1, s2, s3;
            scanf("%d %d %d", &s1, &s2, &s3);
            tem->s1 = s1;
            tem->s2 = s2;
            tem->s3 = s3;
            temarea = triangle_area(tem);
            tem->sidesum = triangle_sidesum(tem);
            printf("triangle %d %d\n", tem->sidesum, tem->area);
        }
    }
}

