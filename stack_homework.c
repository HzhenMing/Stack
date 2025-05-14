/**
 * @file stack_homework.c
 * @author 黄振鸣
 * @brief 作业：使用链表和数组两种方式实现栈ADT
 * @note 
 * 1. 基于链表实现的栈在本程序中称作lstack / LStack（linked list stack）
 * 2. 基于数组实现的栈在本程序中称作tstack / TStack（table stack）
 * 3. 为了避免反复阅读的麻烦，本程序没有对各种功能函数进行声明，而是直接定义在main函数前面
 * @version 0.1
 * @date 2025-05-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/************************使用链表实现栈***********************/
/* 定义栈ADT结构体(实际上是一个链表，下称每个节点为栈元素) */
typedef struct linked_list_stack{
    int32_t data;                   //栈元素存储的数据
    struct linked_list_stack *next; //下一个栈元素（从栈顶指向栈底）
}lstack;

/**
 * @brief 栈初始化
 * 
 * @param target_stack 需要初始化的目标栈地址
 * @note 栈初始化后next指针指向NULL，表示内部无元素
 * 目标栈的地址在本程序中并非栈顶元素本身的地址，而是类似
 * 于链表的头指针的地址，指向栈顶元素
 * @return 无
 */
void vLStackInit(lstack *target_stack){
    /* 初始化时栈顶无元素，因此指向NULL */
    target_stack->next = NULL;
}

/**
 * @brief 数据入栈
 * 
 * @param target_stack 目标栈地址
 * @param data 需要入栈的数据
 * @return uint8_t 操作成功返回1，失败返回0
 */
uint8_t ucLStackPush(lstack *target_stack, int32_t data){
    /* 为新元素申请一块内存空间 */
    lstack *new_element = (lstack *)malloc(sizeof(lstack));
    /* 如果申请失败，返回0 */
    if(new_element == NULL) return 0;
    /* 将需要入栈的值赋值给新元素 */
    new_element->data = data;
    /* 将新元素的next指针指向原本的栈顶元素的next指针所指向的元素 */
    new_element->next = target_stack->next;
    /* 新元素成为栈顶 */
    target_stack->next = new_element;
    return 1;
}

/**
 * @brief 查看栈顶元素值
 * 
 * @param target_stack 需要查看的目标栈地址
 * @note 目标栈的地址就是栈顶元素的地址
 * @return int 栈顶元素值
 */
int32_t iLStackTop(lstack *target_stack){
    /* 如果此时栈为空，则提示用户并返回0 */
    if(target_stack->next == NULL){
        printf("Stack is empty!");
        return 0;
    }
    /* 返回栈顶元素值 */
    return target_stack->next->data;
}

/**
 * @brief 数据出栈
 * 
 * @param target_stack 目标栈地址
 * @return int 出栈数据
 */
int32_t iLStackPop(lstack *target_stack){
    /* 如果此时栈为空，则提示用户并返回0 */
    if(target_stack->next == NULL){
        printf("Stack is empty!");
        return 0;
    }
    /* 记录当前的栈顶元素（旧栈顶元素） */
    lstack *old_top_element = target_stack->next;
    /* 记录当前栈顶元素后弹出后的新栈顶元素 */
    lstack *new_top_element = old_top_element->next;
    /* 暂存需要返回的当前栈顶元素的数据 */
    int return_data = old_top_element->data;
    /* 释放旧的栈顶元素，即弹出 */
    free(old_top_element);
    /* 将target_stack指向新的栈顶元素 */
    target_stack->next = new_top_element;
    /* 返回弹出的数据 */
    return return_data;
}

/**
 * @brief 清空栈
 * 
 * @param target_stack 目标栈地址
 * @return 无
 */
void vMakeLStackEmpty(lstack *target_stack){
    /* 只要栈还没空，就不断弹出，直到栈被清空 */
    while(target_stack->next != NULL){
        lstack *next_top_element = target_stack->next->next;
        free(target_stack->next);
        target_stack->next = next_top_element;
    }
}

/**
 * @brief 打印栈
 * 
 * @param target_stack 目标栈地址
 * @return 无
 */
void vPrintLStack(lstack *target_stack){
    printf("Stack: >> "); //栈顶提示
    /* 循环打印各个数据，直到最后一个数据 */
    while(target_stack->next != NULL){
        /* 通过next指针不断向栈底的方向访问数据 */
        target_stack = target_stack->next;
        printf("%d ", target_stack->data);
    }
    printf("\b]\n"); //栈底提示
}

/************************使用数组实现栈***********************/
/* 定义栈ADT结构体 */
typedef struct table_stack{
    int32_t *tstack_container;  //用于容纳整个栈的存储空间
    int32_t capacity;           //用于指示栈容量
    int32_t top_index;           //栈顶索引
}tstack;

/**
 * @brief 初始化栈
 * 
 * @param target_stack 待初始化的栈
 * @param stack_size 想要创建的栈的大小
 * @return uint8_t 初始化成功返回1，失败返回0
 */
uint8_t ucTStackInit(tstack *target_stack, int32_t stack_size){
    /* 如果输入的栈大小超过限制，或者为负数，则返回0 */
    if((stack_size > 0x7FFFFFF) || (stack_size < 0)) return 0;
    /* 根据栈大小为栈分配内存空间 */
    target_stack->tstack_container = (int *)malloc(stack_size * sizeof(int));
    /* 如果分配不到内存，则返回0 */
    if(target_stack->tstack_container == NULL) return 0;
    /* 设置栈容量 */
    target_stack->capacity = stack_size;
    /* 初始化栈顶索引为-1，表示栈为空 */
    target_stack->top_index = -1;
    return 1;
}

/**
 * @brief 数据入栈
 * 
 * @param target_stack 目标栈地址
 * @param data 入栈数据
 * @return uint8_t 入栈成功返回1，失败返回0
 */
uint8_t ucTStackPush(tstack *target_stack, int32_t data){
    /* 如果栈已满，则提示用户，并返回0 */
    if(target_stack->top_index >= target_stack->capacity - 1){
        printf("Stack is full!\n");
        return 0;
    }
    /* 更新栈顶指针 */
    target_stack->top_index += 1;
    /* 数据入栈，并位于栈顶 */
    target_stack->tstack_container[target_stack->top_index] = data;
    return 1;
}

/**
 * @brief 获取栈顶数据
 * 
 * @param target_stack 目标栈地址
 * @return int32_t 栈顶数据
 */
int32_t iTStackTop(tstack *target_stack){
    /* 如果栈为空,则提示用户并返回0 */
    if(target_stack->top_index == -1){
        printf("Stack is empty!\n");
        return 0;
    }
    /* 返回栈顶数据 */
    return target_stack->tstack_container[target_stack->top_index];
}

/**
 * @brief 数据出栈
 * 
 * @param target_stack 目标栈地址
 * @return * int32_t 出栈数据
 */
int32_t iTStackPop(tstack *target_stack){
    /* 如果栈为空,则提示用户并返回0 */
    if(target_stack->top_index == -1){
        printf("Stack is empty!\n");
        return 0;
    }
    /* 暂存出栈数据的值(即栈顶数据的值) */
    int32_t return_data = target_stack->tstack_container[target_stack->top_index];
    /* 数据出栈后对应的栈顶索引要-1, 指向新的栈顶 */
    target_stack->top_index -= 1;
    return return_data;
}

/**
 * @brief 清空栈
 * 
 * @param target_stack 目标栈地址
 * @return 无
 */
void vMakeTStackEmpty(tstack *target_stack){
    /* 直接将栈顶索引设置为-1即可 */
    target_stack->top_index = -1;
}

/**
 * @brief 打印栈
 * 
 * @param target_stack 目标栈地址
 * @return 无
 */
void vPrintTStack(tstack *target_stack){
    printf("Stack: ["); //打印栈底提示
    /* 遍历整个栈空间，只要当前索引没有超过栈顶指针，就打印对应的数据 */
    for(int32_t i = 0; i <= target_stack->top_index; i++){
        printf("%d ", target_stack->tstack_container[i]);
    }
    printf("<<\n"); //打印栈顶提示
}

/* 主函数，作业任务实现： */
int main(void){
    printf("========================链表实现==========================\n");
    /* 1. 创建一个栈 */
    lstack lstack_test;
    vLStackInit(&lstack_test);

    /* 2. push操作，将元素5和元素2分别压栈 */
    ucLStackPush(&lstack_test, 5);
    ucLStackPush(&lstack_test, 2);
    printf("push操作，将元素5和元素2分别压栈：\n");
    vPrintLStack(&lstack_test);

    /* 3. top操作，查看栈顶元素值 */
    int32_t top_data = iLStackTop(&lstack_test);
    printf("\ntop操作，查看栈顶元素值：\n");
    printf("栈顶元素：%d\n", top_data);

    /* 4. pop操作，栈顶元素弹出并打印 */
    int32_t pop_data = iLStackPop(&lstack_test);
    printf("\npop操作，栈顶元素弹出并打印：\n");
    printf("弹出元素：%d\n", pop_data);
    vPrintLStack(&lstack_test);

    /* 5. push操作，将元素6和元素7分别压栈 */
    ucLStackPush(&lstack_test, 6);
    ucLStackPush(&lstack_test, 7);
    printf("\npush操作，将元素6和元素7分别压栈：\n");
    vPrintLStack(&lstack_test);

    /* 6. makeEmpty操作，清空栈 */
    vMakeLStackEmpty(&lstack_test);
    printf("\nmakeEmpty操作，清空栈：\n");
    vPrintLStack(&lstack_test);

    printf("========================数组实现==========================\n");
    /* 1. 创建一个栈 */
    tstack tstack_test;
    ucTStackInit(&tstack_test, 64);

    /* 2. push操作，将元素5和元素2分别压栈 */
    ucTStackPush(&tstack_test, 5);
    ucTStackPush(&tstack_test, 2);
    printf("push操作，将元素5和元素2分别压栈：\n");
    vPrintTStack(&tstack_test);

    /* 3. top操作，查看栈顶元素值 */
    int32_t top_data1 = iTStackTop(&tstack_test);
    printf("\ntop操作，查看栈顶元素值：\n");
    printf("栈顶元素：%d\n", top_data1);

    /* 4. pop操作，栈顶元素弹出并打印 */
    int32_t pop_data1 = iTStackPop(&tstack_test);
    printf("\npop操作，栈顶元素弹出并打印：\n");
    printf("弹出元素：%d\n", pop_data1);
    vPrintTStack(&tstack_test);

    /* 5. push操作，将元素6和元素7分别压栈 */
    ucTStackPush(&tstack_test, 6);
    ucTStackPush(&tstack_test, 7);
    printf("\npush操作，将元素6和元素7分别压栈：\n");
    vPrintTStack(&tstack_test);

    /* 6. makeEmpty操作，清空栈 */
    vMakeTStackEmpty(&tstack_test);
    printf("\nmakeEmpty操作，清空栈：\n");
    vPrintTStack(&tstack_test);
    return 0;
}
