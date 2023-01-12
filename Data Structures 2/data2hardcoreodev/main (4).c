#include <stdio.h>
#include <stdlib.h>

/*typedef struct DATA_s *DATA;
typedef struct DATA_s{
    int key;
    char value;
}DATA_t[1];*/ // Key-Value data structure

typedef struct LINKED_TREE_NODE_s *LINKED_TREE_NODE;
typedef struct LINKED_TREE_NODE_s {
    LINKED_TREE_NODE right;
    LINKED_TREE_NODE left;
    void *data;
}LINKED_TREE_NODE_t[1];

/*typedef struct LINKED_TREE_NODE_s *LINKED_TREE_NODE;
typedef struct LINKED_TREE_NODE_s {
    LINKED_TREE_NODE right;
    LINKED_TREE_NODE left;
    DATA data;
}LINKED_TREE_NODE_t[1];*/ // Tree node for key-value data structure

typedef struct LINKED_TREE_s *LINKED_TREE;
typedef struct LINKED_TREE_s {
    LINKED_TREE_NODE root;
}LINKED_TREE_t[1];

/*typedef struct LINKED_QUEUE_NODE_s *LINKED_QUEUE_NODE;
typedef struct LINKED_QUEUE_NODE_s {
    LINKED_QUEUE_NODE next;
    LINKED_TREE_NODE data;
}LINKED_QUEUE_NODE_t[1];*/ // Queue node to be used in breath_first

/*typedef struct LINKED_QUEUE_s *LINKED_QUEUE;
typedef struct LINKED_QUEUE_s {
    LINKED_QUEUE_NODE head;
}LINKED_QUEUE_t[1];*/ // Queue to be used in breath_first

typedef struct SIZE_ARR_DATA_s *SIZE_ARR_DATA;
typedef struct SIZE_ARR_DATA_s {
    LINKED_TREE_NODE *arr;
    int size;
}SIZE_ARR_DATA_t[1];

typedef struct STACK_s *STACK;
typedef struct STACK_s {
    SIZE_ARR_DATA arr[10];
    int size;
}STACK_t[1];

/*LINKED_QUEUE linked_queue_init() {
    LINKED_QUEUE queue = (LINKED_QUEUE)malloc(sizeof(LINKED_QUEUE_t));
    queue->head = NULL;
    return queue;
}*/ // Queue functions

/*LINKED_QUEUE_NODE linked_queue_node_init(void *data) {
    LINKED_QUEUE_NODE new = (LINKED_QUEUE_NODE)malloc(sizeof(LINKED_QUEUE_NODE_t));
    new->data = data;
    new->next = NULL;
    return new;
}*/ // Queue functions

/*void linked_queue_enqueue(LINKED_QUEUE queue, void *data) {
    if(queue->head != NULL) {
        LINKED_QUEUE_NODE curr = queue->head;
        while(curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = linked_queue_node_init(data);
    } else {
        queue->head = linked_queue_node_init(data);
    }
}*/ // Queue functions

/*void *linked_queue_dequeue(LINKED_QUEUE queue) {
    if(queue->head != NULL) {
        LINKED_QUEUE_NODE node = queue->head;
        void *data = node->data;
        queue->head = queue->head->next;
        free(node);
        return data;
    } else {
        printf("Error @ linked_queue_dequeue: Queue is already empty.\n");
        exit(1);
    }
}*/ // Queue functions

/*int linked_queue_is_empty(LINKED_QUEUE queue) {
    if(queue->head != NULL) {
        return 0;
    } else {
        return 1;
    }
}*/ // Queue functions

int compare(void *a, void *b) {
    int data1 = *((int *)a);
    int data2 = *((int *)b);

    if(data1 > data2) {
        return 1;
    } else if(data1 < data2) {
        return 0;
    } else {
        return -1;
    }
}

STACK stack_init() {
    STACK stack = (STACK)malloc(sizeof(STACK_t));
    stack->size = 0;
    return stack;
}

void stack_push(STACK stack, SIZE_ARR_DATA data) {
    if(stack->size < 10) {
        stack->size++;
        stack->arr[stack->size] = data;
    } else {
        printf("Error @ stack_push: Stack is full.\n");
        exit(1);
    }
}

SIZE_ARR_DATA stack_pop(STACK stack) {
    if(stack->size >= 1) {
        SIZE_ARR_DATA data = stack->arr[stack->size];
        stack->size--;
        return data;
    } else {
        printf("Error @ stack_pop: Stack is empty already.\n");
        exit(1);
    }
}

int stack_is_empty(STACK stack) {
    if(stack->size == 0) {
        return 1;
    } else {
        return 0;
    }
}

LINKED_TREE linked_tree_init() {
    LINKED_TREE tree = (LINKED_TREE)malloc(sizeof(LINKED_TREE_t));
    return tree;
}  // Initialize tree

LINKED_TREE_NODE linked_tree_node_init(void *data) {
    LINKED_TREE_NODE node = (LINKED_TREE_NODE)malloc(sizeof(LINKED_TREE_NODE_t));
    node->data = data;
    return node;
} // Initialize tree node

/*LINKED_TREE_NODE linked_tree_node_init(DATA data) {
    LINKED_TREE_NODE node = (LINKED_TREE_NODE)malloc(sizeof(LINKED_TREE_NODE_t));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}*/ // Tree node init for key-value data structure

void linked_tree_print(LINKED_TREE_NODE node, int i) {
    if(node != NULL) {
        i++;
        linked_tree_print(node->right, i);
        for (int j = 0; j < i; j++) {
            printf("\t");
        }
        printf("%d\n", *((int *)node->data));
        linked_tree_print(node->left, i);
    }
} // Print tree reversed inorder

void linked_tree_free_recursion(LINKED_TREE_NODE node) {
    if(node != NULL) {
        linked_tree_free_recursion(node->right);
        linked_tree_free_recursion(node->left);
        node->right = NULL;
        node->left = NULL;
        free(node);
    }
} // Recursion part of free function

void linked_tree_free(LINKED_TREE tree) {
    linked_tree_free_recursion(tree->root);
    free(tree);
} // Free tree

LINKED_TREE_NODE linked_tree_find_min(LINKED_TREE tree) {
    if(tree->root != NULL) {
        LINKED_TREE_NODE curr = tree->root;
        while(curr->left != NULL) {
            curr = curr->left;
        }
        return curr;
    } else {
        printf("Error @ linked_tree_find_min: Tree is empty.\n");
        exit(1);
    }
} // Find minimum in tree

void linked_tree_insert(LINKED_TREE tree, void *data) {
    if(tree->root != NULL) {
        LINKED_TREE_NODE curr = tree->root;
        while(1) {
            if(compare(curr->data, data) == 1) {
                if (curr->left != NULL) {
                    curr = curr->left;
                } else {
                    curr->left = linked_tree_node_init(data);
                    break;
                }
            } else if(compare(curr->data, data) == 0) {
                if (curr->right != NULL) {
                    curr = curr->right;
                } else {
                    curr->right = linked_tree_node_init(data);
                    break;
                }
            } else {
                printf("Error @linked_tree_insert: Duplicates are not possible.\n");
                exit(1);
            }
        }
    } else {
        tree->root = linked_tree_node_init(data);
    }
} // Create and insert a new node to the tree

void linked_tree_insert_node(LINKED_TREE tree, LINKED_TREE_NODE node) {
    if(tree->root != NULL) {
        LINKED_TREE_NODE curr = tree->root;
        while(1) {
            if(compare(curr->data, node->data) == 1) {
                if (curr->left != NULL) {
                    curr = curr->left;
                } else {
                    curr->left = node;
                    break;
                }
            } else if(compare(curr->data, node->data) == 0) {
                if (curr->right != NULL) {
                    curr = curr->right;
                } else {
                    curr->right = node;
                    break;
                }
            } else {
                printf("Error @linked_tree_insert: Duplicates are not possible.\n");
                exit(1);
            }
        }
    } else {
        tree->root = node;
    }
} // Insert the given node to the tree

/*void linked_tree_insert(LINKED_TREE tree, DATA data) {
    if(tree->root != NULL) {
        LINKED_TREE_NODE curr = tree->root;
        while(1) {
            if(curr->data->key > data->key) {
                if (curr->left != NULL) {
                    curr = curr->left;
                } else {
                    curr->left = linked_tree_node_init(data);
                    break;
                }
            } else if(curr->data->key < data->key) {
                if (curr->right != NULL) {
                    curr = curr->right;
                } else {
                    curr->right = linked_tree_node_init(data);
                    break;
                }
            } else {
                printf("Error @linked_tree_insert: Duplicates are not possible.\n");
                exit(1);
            }
        }
    } else {
        tree->root = linked_tree_node_init(data);
    }
}*/ // Tree insert for key-value data structure

void linked_tree_delete(LINKED_TREE tree, void * data) {
    if(tree->root != NULL) {
        LINKED_TREE_NODE curr = tree->root;
        LINKED_TREE_NODE parent = tree;
        int come_from = 1;
        while(1) {
            if(compare(curr->data, data) == 1) {
                if(curr->left != NULL) {
                    parent = curr;
                    come_from = 0;
                    curr = curr->left;
                } else {
                    printf("Error @linked_tree_delete: Node not found.\n");
                    exit(1);
                }
            } else if(compare(curr->data, data) == 0) {
                if(curr->right != NULL) {
                    parent = curr;
                    come_from = 1;
                    curr = curr->right;
                } else {
                    printf("Error @linked_tree_delete: Node not found.\n");
                    exit(1);
                }
            } else {
                if(curr->left != NULL && curr->right != NULL) {
                    LINKED_TREE_NODE min = curr->right;
                    LINKED_TREE_NODE min_parent = curr;
                    while(min->left != NULL) {
                        min_parent = min;
                        min = min->left;
                    }
                    if(min_parent == curr) {
                        min->left = curr->left;
                    } else {
                        min->left = curr->left;
                        min_parent->left = min->right;
                        min->right = curr->right;
                    }
                    if(come_from == 0) {
                        parent->left = min;
                    } else {
                        parent->right = min;
                    }
                    curr->left = NULL;
                    curr->right = NULL;
                    free(curr);
                    break;
                } else if(curr->left == NULL){
                    if(come_from == 0) {
                        parent->left = curr->right;
                    } else {
                        parent->right = curr->right;
                    }
                    free(curr);
                    break;
                } else {
                    if(come_from == 0) {
                        parent->left = curr->left;
                    } else {
                        parent->right = curr->left;
                    }
                    free(curr);
                    break;
                }
            }
        }
    } else {
        printf("Error @linked_tree_delete: Tree is empty.\n");
        exit(1);
    }
} // Delete the node with the given data from the tree

void linked_tree_traverse_preorder(LINKED_TREE_NODE node) {
    if(node != NULL) {
        printf("%d ", *((int *)node->data));
        linked_tree_traverse_preorder(node->left);
        linked_tree_traverse_preorder(node->right);
    }
} // Print the tree preorder

void linked_tree_traverse_inorder(LINKED_TREE_NODE node) {
    if(node != NULL) {
        linked_tree_traverse_inorder(node->left);
        printf("%d ", *((int *)node->data));
        linked_tree_traverse_inorder(node->right);
    }
} // Print the tree inorder

/*void linked_tree_breath_first(LINKED_TREE tree) {
    LINKED_QUEUE queue = linked_queue_init();
    if(tree->root != NULL) {
        LINKED_TREE_NODE curr = tree->root;
        linked_queue_enqueue(queue, curr);
        while(!linked_queue_is_empty(queue)) {
            curr = linked_queue_dequeue(queue);
            printf("%c", curr->data->value);
            if(curr->left != NULL) {
                linked_queue_enqueue(queue, curr->left);
            }
            if(curr->right != NULL) {
                linked_queue_enqueue(queue, curr->right);
            }
        }
    } else {
        printf("Error @ linked_tree_breath_first: Tree is empty.\n");
        exit(1);
    }
}*/ // Breath-first function

int linked_tree_height(LINKED_TREE_NODE node, int i, int max_i) {
    if(node != NULL) {
        i++;
        max_i = linked_tree_height(node->right, i, max_i);
        max_i = linked_tree_height(node->left, i, max_i);
        if(i > max_i) {
            max_i = i;
        }
    }
    return max_i;
} // Calculate the height of the tree

void linked_tree_to_array_inorder(LINKED_TREE_NODE node, LINKED_TREE_NODE *arr, int *iter) {
    if(node != NULL) {
        linked_tree_to_array_inorder(node->left, arr, iter);
        arr[*iter] = node;
        *(iter) = *(iter) + 1;
        linked_tree_to_array_inorder(node->right, arr, iter);
    }
} // Copy the tree to an array inoerderly

void linked_tree_balance_recursion(LINKED_TREE tree, LINKED_TREE_NODE *arr, int size) {
    if(size >= 0) {
        linked_tree_insert_node(tree, arr[size/2]);
        linked_tree_balance_recursion(tree, arr, size/2-1);
        linked_tree_balance_recursion(tree, &arr[size/2+1], size-size/2-1 );
    }
} // Recursion part of recursive balance function

void linked_tree_balance(LINKED_TREE tree, int size) {
    LINKED_TREE_NODE *arr = (LINKED_TREE_NODE *)malloc(sizeof(LINKED_TREE_NODE)*(size+1));
    int a = 0;
    int *iter = &a;
    linked_tree_to_array_inorder(tree->root, arr, iter);

    for(int i=0; i<size+1; i++) {
        arr[i]->right = NULL;
        arr[i]->left = NULL;
    }
    tree->root = NULL;
    linked_tree_balance_recursion(tree, arr, size);
} // Balance the tree recursively

/*void linked_tree_balance(LINKED_TREE_NODE node, LINKED_TREE_NODE *arr, int size) {
    if(size >= 0) {
        node = arr[size/2]; // Bu neden calismiyor?
        linked_tree_balance(node->left, arr, size/2-1);
        linked_tree_balance(node->right, &arr[size/2+1], size-size/2-1 );
    }
}*/ // !!!! BU NEDEN CALISMIYOR??? !!!!

void linked_tree_iterative_balance(LINKED_TREE tree, int size) {
    LINKED_TREE_NODE *arr = (LINKED_TREE_NODE *)malloc(sizeof(LINKED_TREE_NODE)*(size+1));
    int a = 0;
    int *iter = &a;
    linked_tree_to_array_inorder(tree->root, arr, iter);

    for(int i=0; i<size+1; i++) {
        arr[i]->right = NULL;
        arr[i]->left = NULL;
    }
    tree->root = NULL;

    STACK stack = stack_init();
    while((!stack_is_empty(stack)) || (size >= 0)) {
        if(size >= 0) {
            linked_tree_insert_node(tree, arr[size / 2]);
            if (size - size / 2 - 1 >= 0) {
                SIZE_ARR_DATA data = (SIZE_ARR_DATA)malloc(sizeof(SIZE_ARR_DATA_t));
                data->arr = &arr[size / 2 + 1];
                data->size = size - size / 2 - 1;
                stack_push(stack, data);
            }
            size = size / 2 - 1;
        } else {
            SIZE_ARR_DATA data = stack_pop(stack);
            arr = data->arr;
            size = data->size;
        }
    }
} // Balance tree iteratively


int main() {

/*
    int arr[] = {31, 45, 20, 67, 18, 82, 55, 39, 48, 99};
    LINKED_TREE tree = linked_tree_init();

    for(int i=0; i<10; i++) {
        linked_tree_insert(tree, (void *)&arr[i]);
    }
    linked_tree_print(tree->root, 0);

    linked_tree_traverse_preorder(tree->root);
    printf("\n----------------------------------------\n");
    linked_tree_traverse_inorder(tree->root);
*/ // Tests

/*
    int keys[986] = {512, 256, 128, 64, 32, 16, 8, 4, 2, 1, 3, 6, 5, 7, 12, 10, 9, 11, 14, 13, 15, 24, 20, 18, 17, 19,
            22, 21, 23, 28, 26, 25, 27, 30, 29, 31, 48, 40, 36, 34, 33, 35, 38, 37, 39, 44, 42, 41, 43, 46, 45, 47, 56, 52, 50,
            49, 51, 54, 53, 55, 60, 58, 57, 59, 62, 61, 63, 96, 80, 72, 68, 66, 65, 67, 70, 69, 71, 76, 74, 73, 75, 78, 77, 79,
            88, 84, 82, 81, 83, 86, 85, 87, 92, 90, 89, 91, 94, 93, 95, 112, 104, 100, 98, 97, 99, 102, 101, 103, 108, 106,
            105, 107, 110, 109, 111, 120, 116, 114, 113, 115, 118, 117, 119, 124, 122, 121, 123, 126, 125, 127, 192, 160,
            144, 136, 132, 130, 129, 131, 134, 133, 135, 140, 138, 137, 139, 142, 141, 143, 152, 148, 146, 145, 147, 150,
            149, 151, 156, 154, 153, 155, 158, 157, 159, 176, 168, 164, 162, 161, 163, 166, 165, 167, 172, 170, 169, 171,
            174, 173, 175, 184, 180, 178, 177, 179, 182, 181, 183, 188, 186, 185, 187, 190, 189, 191, 224, 208, 200, 196,
            194, 193, 195, 198, 197, 199, 204, 202, 201, 203, 206, 205, 207, 216, 212, 210, 209, 211, 214, 213, 215, 220,
            218, 217, 219, 222, 221, 223, 240, 232, 228, 226, 225, 227, 230, 229, 231, 236, 234, 233, 235, 238, 237, 239,
            248, 244, 242, 241, 243, 246, 245, 247, 252, 250, 249, 251, 254, 253, 255, 384, 320, 288, 272, 264, 260, 258,
            257, 259, 262, 261, 263, 268, 266, 265, 267, 270, 269, 271, 280, 276, 274, 273, 275, 278, 277, 279, 284, 282,
            281, 283, 286, 285, 287, 304, 296, 292, 290, 289, 291, 294, 293, 295, 300, 298, 297, 299, 302, 301, 303, 312,
            308, 306, 305, 307, 310, 309, 311, 316, 314, 313, 315, 318, 317, 319, 352, 336, 328, 324, 322, 321, 323, 326,
            325, 327, 332, 330, 329, 331, 334, 333, 335, 344, 340, 338, 337, 339, 342, 341, 343, 348, 346, 345, 347, 350,
            349, 351, 368, 360, 356, 354, 353, 355, 358, 357, 359, 364, 362, 361, 363, 366, 365, 367, 376, 372, 370, 369,
            371, 374, 373, 375, 380, 378, 377, 379, 382, 381, 383, 448, 416, 400, 392, 388, 386, 385, 387, 390, 389, 391,
            396, 394, 393, 395, 398, 397, 399, 408, 404, 402, 401, 403, 406, 405, 407, 412, 410, 409, 411, 414, 413, 415,
            432, 424, 420, 418, 417, 419, 422, 421, 423, 428, 426, 425, 427, 430, 429, 431, 440, 436, 434, 433, 435, 438,
            437, 439, 444, 442, 441, 443, 446, 445, 447, 480, 464, 456, 452, 450, 449, 451, 454, 453, 455, 460, 458, 457,
            459, 462, 461, 463, 472, 468, 466, 465, 467, 470, 469, 471, 476, 474, 473, 475, 478, 477, 479, 496, 488, 484,
            482, 481, 483, 486, 485, 487, 492, 490, 489, 491, 494, 493, 495, 504, 500, 498, 497, 499, 502, 501, 503, 508,
            506, 505, 507, 510, 509, 511, 768, 640, 576, 544, 528, 520, 516, 514, 513, 515, 518, 517, 519, 524, 522, 521,
            523, 526, 525, 527, 536, 532, 530, 529, 531, 534, 533, 535, 540, 538, 537, 539, 542, 541, 543, 560, 552, 548,
            546, 545, 547, 550, 549, 551, 556, 554, 553, 555, 558, 557, 559, 568, 564, 562, 561, 563, 566, 565, 567, 572,
            570, 569, 571, 574, 573, 575, 608, 592, 584, 580, 578, 577, 579, 582, 581, 583, 588, 586, 585, 587, 590, 589,
            591, 600, 596, 594, 593, 595, 598, 597, 599, 604, 602, 601, 603, 606, 605, 607, 624, 616, 612, 610, 609, 611,
            614, 613, 615, 620, 618, 617, 619, 622, 621, 623, 632, 628, 626, 625, 627, 630, 629, 631, 636, 634, 633, 635,
            638, 637, 639, 704, 672, 656, 648, 644, 642, 641, 643, 646, 645, 647, 652, 650, 649, 651, 654, 653, 655, 664,
            660, 658, 657, 659, 662, 661, 663, 668, 666, 665, 667, 670, 669, 671, 688, 680, 676, 674, 673, 675, 678, 677,
            679, 684, 682, 681, 683, 686, 685, 687, 696, 692, 690, 689, 691, 694, 693, 695, 700, 698, 697, 699, 702, 701,
            703, 736, 720, 712, 708, 706, 705, 707, 710, 709, 711, 716, 714, 713, 715, 718, 717, 719, 728, 724, 722, 721,
            723, 726, 725, 727, 732, 730, 729, 731, 734, 733, 735, 752, 744, 740, 738, 737, 739, 742, 741, 743, 748, 746,
            745, 747, 750, 749, 751, 760, 756, 754, 753, 755, 758, 757, 759, 764, 762, 761, 763, 766, 765, 767, 896, 832,
            800, 784, 776, 772, 770, 769, 771, 774, 773, 775, 780, 778, 777, 779, 782, 781, 783, 792, 788, 786, 785, 787,
            790, 789, 791, 796, 794, 793, 795, 798, 797, 799, 816, 808, 804, 802, 801, 803, 806, 805, 807, 812, 810, 809,
            811, 814, 813, 815, 824, 820, 818, 817, 819, 822, 821, 823, 828, 826, 825, 827, 830, 829, 831, 864, 848, 840,
            836, 834, 833, 835, 838, 837, 839, 844, 842, 841, 843, 846, 845, 847, 856, 852, 850, 849, 851, 854, 853, 855,
            860, 858, 857, 859, 862, 861, 863, 880, 872, 868, 866, 865, 867, 870, 869, 871, 876, 874, 873, 875, 878, 877,
            879, 888, 884, 882, 881, 883, 886, 885, 887, 892, 890, 889, 891, 894, 893, 895, 960, 928, 912, 904, 900, 898,
            897, 899, 902, 901, 903, 908, 906, 905, 907, 910, 909, 911, 920, 916, 914, 913, 915, 918, 917, 919, 924, 922,
            921, 923, 926, 925, 927, 944, 936, 932, 930, 929, 931, 934, 933, 935, 940, 938, 937, 939, 942, 941, 943, 952,
            948, 946, 945, 947, 950, 949, 951, 956, 954, 953, 955, 958, 957, 959, 976, 968, 964, 962, 961, 963, 966, 965,
            967, 972, 970, 969, 971, 974, 973, 975, 992, 984, 980, 978, 977, 979, 982, 981, 983, 988};
    int values[986] = {35, 105, 99, 101, 103, 116, 97, 32, 49, 50, 44, 48, 32, 49, 49, 44, 50, 49, 32, 44, 32,
            103, 49, 49, 49, 49, 48, 49, 44, 52, 49, 32, 49, 44, 49, 55, 100, 101, 44, 32, 44, 32, 51, 49, 49, 32, 50, 52, 44,
            44, 32, 51, 91, 51, 32, 50, 44, 49, 32, 49, 50, 48, 48, 48, 52, 44, 32, 46, 105, 49, 44, 44, 49, 49, 32, 49, 44, 32,
            49, 32, 49, 49, 48, 51, 55, 49, 49, 44, 32, 44, 51, 50, 48, 32, 44, 32, 49, 49, 48, 111, 56, 52, 49, 50, 44, 55,
            32, 49, 44, 44, 49, 49, 32, 44, 32, 93, 32, 49, 49, 49, 49, 52, 44, 49, 52, 32, 51, 44, 50, 44, 32, 104, 46, 32,
            48, 32, 32, 53, 51, 50, 44, 49, 50, 32, 53, 44, 51, 44, 61, 44, 32, 32, 51, 57, 50, 44, 32, 56, 32, 49, 44, 48, 57,
            104, 32, 57, 32, 44, 32, 49, 49, 48, 55, 49, 53, 44, 55, 32, 49, 123, 44, 44, 49, 48, 32, 44, 32, 32, 49, 49, 49,
            49, 55, 44, 62, 62, 54, 49, 52, 32, 49, 44, 49, 54, 48, 32, 44, 32, 49, 49, 48, 54, 48, 49, 49, 44, 48, 32, 49, 44,
            44, 49, 53, 32, 44, 32, 10, 44, 32, 49, 52, 52, 49, 44, 32, 51, 53, 51, 50, 44, 44, 32, 32, 50, 32, 49, 49, 51, 57,
            44, 44, 50, 32, 49, 44, 48, 52, 108, 60, 10, 10, 57, 32, 32, 44, 32, 52, 49, 48, 57, 57, 53, 44, 44, 32, 57, 55,
            55, 32, 57, 44, 53, 32, 49, 44, 51, 48, 52, 44, 44, 32, 105, 44, 32, 32, 51, 50, 52, 44, 32, 49, 56, 57, 55, 44,
            44, 32, 32, 48, 32, 49, 48, 51, 56, 44, 51, 50, 32, 49, 44, 49, 53, 35, 110, 49, 44, 32, 44, 32, 57, 49, 49, 32,
            57, 49, 44, 44, 32, 51, 49, 57, 32, 50, 44, 57, 32, 57, 55, 55, 56, 44, 44, 32, 49, 116, 48, 44, 32, 49, 55, 49,
            44, 32, 32, 48, 49, 49, 56, 52, 44, 44, 49, 44, 32, 49, 32, 49, 48, 48, 49, 44, 32, 49, 49, 49, 115, 105, 32, 32,
            53, 49, 53, 44, 44, 32, 51, 44, 32, 50, 44, 49, 32, 52, 49, 32, 49, 57, 44, 52, 32, 53, 49, 44, 51, 44, 32, 32, 52,
            109, 48, 49, 49, 56, 44, 48, 32, 51, 48, 53, 50, 44, 44, 32, 57, 51, 44, 32, 57, 44, 49, 32, 57, 32, 48, 55, 44,
            49, 32, 49, 110, 97, 44, 49, 44, 48, 56, 32, 44, 32, 49, 49, 49, 49, 49, 49, 44, 32, 53, 53, 32, 49, 44, 49, 52,
            44, 32, 44, 32, 52, 49, 48, 105, 49, 32, 54, 53, 44, 44, 32, 49, 49, 32, 48, 49, 54, 44, 32, 48, 49, 53, 49, 49,
            44, 53, 44, 54, 32, 32, 51, 49, 50, 44, 110, 117, 116, 99, 110, 53, 44, 48, 32, 45, 56, 51, 48, 32, 44, 44, 32,
            32, 45, 49, 44, 51, 49, 50, 56, 49, 44, 32, 50, 54, 45, 49, 44, 48, 57, 40, 32, 44, 32, 44, 32, 49, 51, 50, 32, 48,
            44, 32, 49, 57, 55, 49, 57, 44, 44, 32, 32, 49, 49, 55, 49, 48, 44, 49, 32, 49, 108, 41, 49, 44, 52, 48, 48, 44,
            44, 32, 32, 32, 51, 50, 49, 44, 32, 48, 51, 49, 49, 48, 48, 53, 44, 50, 44, 32, 49, 32, 49, 53, 32, 44, 44, 57, 44,
            32, 55, 51, 50, 32, 44, 44, 32, 32, 49, 48, 32, 49, 49, 57, 44, 49, 32, 49, 49, 54, 49, 55, 44, 44, 32, 114, 117,
            123, 49, 57, 32, 57, 57, 49, 44, 32, 44, 48, 49, 48, 53, 52, 44, 48, 32, 44, 32, 51, 32, 50, 44, 57, 49, 32, 49,
            49, 48, 56, 10, 51, 55, 56, 44, 32, 44, 49, 48, 44, 32, 49, 44, 49, 32, 49, 44, 32, 48, 49, 53, 49, 44, 32, 49, 44,
            49, 49, 32, 53, 44, 100, 10, 32, 48, 49, 32, 51, 48, 50, 44, 56, 56, 32, 49, 44, 49, 50, 51, 44, 32, 44, 32, 49,
            57, 55, 32, 50, 44, 32, 49, 49, 48, 9, 50, 49, 44, 53, 44, 32, 32, 49, 48, 52, 49, 48, 52, 44, 32, 44, 56, 44, 49,
            48, 32, 50, 44, 44, 51, 32, 49, 50, 49, 55, 100, 105, 101, 105, 32, 32, 44, 44, 32, 32, 49, 48, 51, 49, 56, 44,
            50, 32, 52, 49, 50, 49, 54, 44, 44, 32, 49, 44, 32, 48, 125, 49, 59, 10, 110, 50, 32, 49, 9, 105, 49, 110, 116,
            49, 44, 32, 105, 32, 32, 61, 49, 48, 49, 32, 48, 49, 59, 10, 50, 55, 9, 102, 44, 111, 114, 32, 116, 44, 44, 32,
            32, 40, 51, 105, 32, 32, 50, 61, 32, 44, 48, 59, 32, 49, 32, 32, 105, 57, 32, 60, 49, 57, 32, 49, 44, 55, 56, 32,
            49, 49, 32, 59, 32, 57, 105, 43, 44, 55, 43, 41, 44, 123, 10, 49, 32, 32, 9, 9, 49, 112, 114, 49, 49, 105, 110,
            48, 116, 102, 110, 60, 109, 49, 49, 44, 40, 34, 32, 37, 99, 52, 51, 34, 44, 50, 32, 109, 44, 44, 44, 101, 115,
            32, 115, 97, 32, 49, 103, 101, 49, 91, 105, 101, 32, 51, 57, 93, 41, 44, 59, 10, 50, 32, 9, 125, 57, 10, 9, 49,
            44, 55, 114, 101, 44, 116, 117, 32, 32, 114, 110, 49, 32, 48, 115, 115, 49, 49, 48, 56, 49, 44, 32, 55, 49, 49,
            48, 44, 55, 44, 115, 44, 32, 32, 59, 10, 51, 125, 10, 49};
    DATA data;

    for(int i=0; i<986; i++) {
        data = (DATA)malloc(sizeof(DATA_t));
        data->key = keys[i];
        data->value = values[i];

        linked_tree_insert(tree, data);
    }

    linked_tree_breath_first(tree);


*/ // Key and values

    int arr[] = {31, 45, 20, 67, 18, 82, 55, 39, 48, 99};
    LINKED_TREE tree = linked_tree_init();

    for(int i=0; i<10; i++) {
        linked_tree_insert_node(tree, linked_tree_node_init((void *)&arr[i]));
    }
    printf("Not balanced: \n");
    linked_tree_print(tree->root, 0);
    printf("Height is: %d\n\n", linked_tree_height(tree->root, 0, 0));

    printf("/-------------------------------------------------------/\n\n");

    linked_tree_balance(tree, 9);
    printf("Recursively balanced: \n");
    linked_tree_print(tree->root, 0);
    printf("Height is: %d\n\n", linked_tree_height(tree->root, 0, 0));

    printf("/-------------------------------------------------------/\n\n");

    linked_tree_iterative_balance(tree, 9);
    printf("Iteratively balanced: \n");
    linked_tree_print(tree->root, 0);
    printf("Height is: %d\n\n", linked_tree_height(tree->root, 0, 0));

    printf("/-------------------------------------------------------/\n\n");

    linked_tree_free(tree);

    return 0;
}
