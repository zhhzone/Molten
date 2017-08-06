/**
 * Copyright 2017 chuan-yun silkcutKs <silkcutbeta@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "molten_stack.h"

#define STACK_ELE(stack, m) ((void *)((char *)(stack)->elements + (stack)->size * (n)))

void mo_stack_init(mo_stack *stack, int size, dtor_func dtor)
{
    stack->max = 0;
    stack->size = size;
    stack->top = 0;
    stack->elements = NULL;
    stack->dtor = dtor;
}

int mo_stack_push(mo_stack *stack, void *element)
{
    if (stack->top >= stack->max) {
        stack->max += STACK_BLOC_SZE;
        stack->elements = erealloc(stack->elements, stack->max * stack->size, 0);
    }
    memcpy(STACK_ELE(stack, stack->top), element, stack->size);
    return stack->top++;
}

void *mo_stack_top(mo_stack *stack)
{
    if (stack->top > 0) {
        return STACK_ELE(stack, stack->top - 1);
    } else {
        return NULL;
    }
}

void *mo_stack_element(mo_stack *stack, int offset)
{
    return STACK_ELE(stack, offset - 1);
}

void mo_stack_del_top(mo_stack *stack)
{
    stack->dtor(STACK_ELE(stack, stack->top-1));
    --stack->top;
}

void mo_stack_pop(mo_stack *stack, void *element)
{
    memcpy(element, STACK_ELE(stack, stack->top-1), stack->size);
    mo_stack_del_top(stack);
}

void mo_stack_destroy(mo_stack *stack)
{
    if (stack->elements) {
        efree(stack->elements);
        stack->max = 0;
        stack->top = 0;
        stack->dtor = NULL;
        stack->elements = NULL;
    }
}

int mo_stack_empty(mo_stack *stack)
{
    return stack->top == 0;  
}

int mo_stack_top(mo_stack *stack)
{
    return stack->top;
}
