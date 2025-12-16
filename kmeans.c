#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct cord
{
    double value;
    struct cord *next;
};
struct vector
{
    struct vector *next;
    struct cord *cords;
};

struct center
{
    struct center *next;
    struct cord *cords;
    struct vector *assigned_vectors;
    int num_assigned;
};

struct center *closest_center(struct vector *vec, struct center *centers)
{
    struct center *curr_center = centers;
    struct center *closest = NULL;
    double min_distance = INFINITY;

    while(curr_center != NULL)
    {
        double distance = 0.0;
        struct cord *vec_cord = vec->cords;
        struct cord *center_cord = curr_center->cords;

        while (vec_cord != NULL && center_cord != NULL)
        {
            distance += pow(vec_cord->value - center_cord->value, 2);
            vec_cord = vec_cord->next;
            center_cord = center_cord->next;
        }

        distance = sqrt(distance);

        if (distance < min_distance)
        {
            min_distance = distance;
            closest = curr_center;
        }
        curr_center = curr_center->next;
    }
    return closest;
}

void assign_vector_to_center(struct vector *vec, struct center *center)
{
    if (center->assigned_vectors == NULL)
    {
        center->assigned_vectors = vec;
        center->num_assigned = 1;
        vec->next = NULL;
    }
    else
    {
        struct vector *curr = center->assigned_vectors;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = vec;
        vec->next = NULL;
        center->num_assigned += 1;
    }
}

//update all points and assign them to their closest center
void update_all_points(struct vector *vectors, struct center *centers)
{
    struct vector *curr_vec = vectors;

    while (curr_vec != NULL)
    {
        struct center *closest = closest_center(curr_vec, centers);
        assign_vector_to_center(curr_vec, closest);
        curr_vec = curr_vec->next;
    }
}


int main(int argc, char **argv)
{
    struct vector *head_vec, *curr_vec, *next_vec;
    struct cord *head_cord, *curr_cord, *next_cord;
    int i, j, rows = 0, cols, K=argv[1], iter;
    double n;
    char c;

    head_cord = malloc(sizeof(struct cord));
    curr_cord = head_cord;
    curr_cord->next = NULL;

    head_vec = malloc(sizeof(struct vector));
    curr_vec = head_vec;
    curr_vec->next = NULL;


    while (scanf("%lf%c", &n, &c) == 2)
    {

        if (c == '\n')
        {
            curr_cord->value = n;
            curr_vec->cords = head_cord;
            curr_vec->next = malloc(sizeof(struct vector));
            curr_vec = curr_vec->next;
            curr_vec->next = NULL;
            head_cord = malloc(sizeof(struct cord));
            curr_cord = head_cord;
            curr_cord->next = NULL;
            continue;
        }

        curr_cord->value = n;
        curr_cord->next = malloc(sizeof(struct cord));
        curr_cord = curr_cord->next;
        curr_cord->next = NULL;
    }

    if ((K<1) || (K>rows)){
        printf("Incorrect number of clusters");
    } 
    if (argc > 2){
        iter = (int)argv[2];
        if ((iter<2) || (iter>799)){
            printf("Incorrect maximum iteration!");
        }
    }
    else{
        iter = 400;
    }

    return 0;
}
