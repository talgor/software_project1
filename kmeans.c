#include <stdio.h>
#include <stdlib.h>
struct center updatecenter(struct center *);
int cordSumAndAdvanceCord(struct vector);
void currToHead(struct vector);

struct cord
{
    double value;
    struct cord *next;
};
struct vector
{
    struct vector *next;
    struct cord *cords;
    struct cord *curr;
};

struct center{
    struct center *next;
    struct cord *cords;
    struct cord *curr;
    struct vector *assighned_points;
    int num_assigned;
};


//calculates the sum of values of the current coaordinate in all vectors in the linked list, recursively
//expects every vector to have a not empty list of cords
int cordSumAndAdvanceCord(struct vector *curr_vector){
    int val = *curr_vector -> curr -> value;
    *curr_vector -> curr = curr -> next;
    if (*curr_vector -> next == NULL){
        return val
    }
    return val + cordSumAndAdvanceCord(*curr_vector -> next)
}

//update all the vectors in the linked list given to have there currs pointing at there heads
void currToHead(struct vector *assighned_points){
    struct vector curr_vec;
    curr_vec = malloc(sizeof(struct vector));
    curr_vec = *assighned_points;
    curr_vec->curr = curr_vec->cords;
    while (curr_vec->next != NULL){
        curr_vec = curr_vec->next;
        curr_vec->curr = curr_vec->cords;
    }
    free(curr_vec)
    return 0
}



struct center updateCenter(struct center *center_head, int cols){
    int i;
    struct center updatedcenter;
    struct cord this;
    updatedcenter = malloc(sizeof(struct center))
    currToHead(*(center_head->assighned_points))
    for (i = 0; i < cols; i++){
        this = malloc(sizeof(struct cord));
        this->value = cordSumAndAdvanceCord(*(center_head->assighned_points)) / center-> num_assigned;
        this->next = NULL;
        if(updatedcenter->cords == NULL){
            updatedcenter->cords = this;
            updatedcenter->curr = this;
        }
        else{
            updatedcenter->curr->next = this;
            updatedcenter->curr = updatedcenter->curr->next
        }
    }
    updatedcenter->assighned_points = NULL;
    updatedcenter->num_assigned = 0;
    //need to write a function that will recursively erase that part
    return updatedcenter
}


int main(int argc, char **argv)
{

    struct vector *head_vec, *curr_vec, *next_vec;
    struct cord *head_cord, *curr_cord, *next_cord;
    int i, j, rows = 0, cols, K, iter;
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
            curr_vec->curr = head_cord;
            curr_vec->next = malloc(sizeof(struct vector));
            curr_vec = curr_vec->next;
            curr_vec->next = NULL;
            head_cord = malloc(sizeof(struct cord));
            curr_cord = head_cord;
            curr_cord->next = NULL;
            rows += 1;
            continue;
        }

        curr_cord->value = n;
        curr_cord->next = malloc(sizeof(struct cord));
        curr_cord = curr_cord->next;
        curr_cord->next = NULL;
    }

    rows += -1;



    K = (int)argv[1]
    if ((k<1) || (k>rows)){
        printf("Incorrect number of clusters");
    } 
    if (argc > 2){
        iter = (int)argv[2]
        if ((iter<2) || (iter>799)){
            printf("Incorrect maximum iteration!");
        }
    }
    else{
        iter = 400;
    }

    #need to recursively free everything
    return 0;
}

```

