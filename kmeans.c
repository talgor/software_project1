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
    struct cord *sum_assigned;
    int num_assigned;
};

struct cord* create_cord_node(double val) {
    struct cord *new_node = malloc(sizeof(struct cord));
    new_node->value = val;
    new_node->next = NULL;
    return new_node;
}

struct center *create_center(struct vector *vec)
{
    struct center *new_center = malloc(sizeof(struct center));
    new_center->next = NULL;
    new_center->num_assigned = 0;
    
    new_center->cords = NULL;
    new_center->sum_assigned = NULL;

    struct cord *curr_v = vec->cords;
    struct cord *last_center = NULL;
    struct cord *last_sum = NULL;

    while (curr_v != NULL) {
        struct cord *new_center_cord = create_cord_node(curr_v->value);
        struct cord *new_sum_cord = create_cord_node(0.0);

        if (new_center->cords == NULL) {
            new_center->cords = new_center_cord;
            new_center->sum_assigned = new_sum_cord;
        } else {
            last_center->next = new_center_cord;
            last_sum->next = new_sum_cord;
        }
        
        last_center = new_center_cord;
        last_sum = new_sum_cord;
        curr_v = curr_v->next;
    }

    return new_center;
}


double points_distance(struct cord *p1, struct cord *p2){
    double distance = 0.0;
    while (p1 != NULL && p2 != NULL)
        {
            distance += pow(p1->value - p2->value, 2);
            p1 = p1->next;
            p2 = p2->next;
        }

        return sqrt(distance);
}

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

struct center* init_centers(struct vector *vectors, int K)
{
    struct center *head_center = NULL;
    struct center *last_center = NULL;
    struct vector *curr_vec = vectors;
    for(int i=0; i<K && curr_vec != NULL; i++) {
        struct center *new_center = create_center(curr_vec);
        if(head_center == NULL) {
            head_center = new_center;
        } else {
            last_center->next = new_center;
        }
        last_center = new_center;
        curr_vec = curr_vec->next;
    }
    return head_center;
}

void assign_vector_to_center(struct vector *vec, struct center *center)
{
    struct cord *vec_cord = vec->cords;
    struct cord *sum_cord = center->sum_assigned;
    while (vec_cord != NULL && sum_cord != NULL) {
        sum_cord->value += vec_cord->value;

        vec_cord = vec_cord->next;
        sum_cord = sum_cord->next;
    }
    center->num_assigned += 1;
}

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

int update_all_centers(struct center *centers)
{
    int moved = 0;
    double eps = 0.001;
    struct center *curr_cent = centers;
    while (curr_cent!=NULL)
    {
        ///calculate the updated coaordinates, and the distance
        struct cord *curr_cord = curr_cent->sum_assigned;
        while (curr_cord!=NULL)
        {
            curr_cord->value = curr_cord->value / curr_cent->num_assigned;
            curr_cord = curr_cord->next;
        }
        if (points_distance(curr_cent->cords, curr_cent->sum_assigned) >= eps)
        {
            moved = 1;
        }
        ///update the center, and delete all assigned points from it
        struct cord *tmp = curr_cent->cords;
        curr_cent->cords = curr_cent->sum_assigned;
        curr_cord = tmp;
        while (curr_cord!=NULL)
        {
            curr_cord->value = 0;
            curr_cord = curr_cord->next;
        }
        curr_cent->sum_assigned = tmp;
        curr_cent->num_assigned = 0;
        curr_cent = curr_cent->next;
    }
    return moved;
}

void print_centers(struct center *centers)
{
    struct center *curr_center = centers;
    while (curr_center != NULL) {
        struct cord *curr_cord = curr_center->cords;
        while (curr_cord != NULL) {
            printf("%.4f", curr_cord->value);
            if (curr_cord->next != NULL) {
                printf(",");
            }
            curr_cord = curr_cord->next;
        }
        printf("\n");
        curr_center = curr_center->next;
    }
}

int main(int argc, char **argv)
{
    struct vector *head_vec, *curr_vec;
    struct cord *head_cord, *curr_cord;
    int rows = 0, K=atoi(argv[1]), iter;
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
            rows++;
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
        iter = atoi(argv[2]);
        if ((iter<2) || (iter>799)){
            printf("Incorrect maximum iteration!");
        }
    }
    else{
        iter = 400;
    }

    struct center *centers = init_centers(head_vec, K);
    int count = 0;
    int changed = 1;
    while (changed && (count < iter))
    {
        update_all_points(head_vec, centers);
        changed = update_all_centers(centers);
        count++;
    }

    print_centers(centers);
    return 0;
}
