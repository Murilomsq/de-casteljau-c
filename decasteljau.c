#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float lerp(float t0, float p0, float p1){
    return (1 - t0) * p0 + t0 * p1;
}

float * reduce(float t0, float * points, int points_size){
    float * points_new = (float * )malloc(points_size - 1); //dynamically allocate array to return it
    for(int i = 0; i < points_size - 1; i++){
        points_new[i] = lerp(t0, points[i], points[i + 1]); // lerping each point
    }
    return points_new;
}

float deCasteljau(float t0, float * points, float points_size){
    float * p = points;
    float * temp_points;
    
    //The idea here is to copy the contents of the return array from reduce() into a temporary array than free it
    //so it wont leak
    for(int i = 0; i < points_size - 1; i++){
        temp_points = reduce(t0, p, points_size);           
        memcpy(p, temp_points, sizeof(temp_points));
        free(temp_points);
    }
    return p[0];
}

int main()
{
    float arr[] = {1.4, 3.5, 8.0, 9.0, 15.0};
    printf("%f", deCasteljau(0.5, arr, sizeof(arr)/sizeof(float)));
    return 0;
}
