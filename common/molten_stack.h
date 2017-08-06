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
#ifndef MOLTEN_STACK_H
#define MOLTEN_STACK_H

#define STACK_BLOCK_SIZE    64

/* our stack element only store data point for performance */
typedef void (*dtor_func)(void *element);

/* data will be delete */
typedef struct {
    int size, top, max;
    void *elements;
    dtor_func dtor;
} mo_stack;

void mo_stack_init(mo_stack *stack, int size, dtor_func dtor);
int mo_stack_push(mo_stack *stack, void *element);
void *mo_stack_top(mo_stack *stack);
void mo_stack_del_top(mo_stack *stack);
void mo_stack_del_top(mo_stack *stack);
void mo_stack_pop(mo_stack *stack, void *element);
void mo_stack_destroy(mo_stack *stack);
int mo_stack_empty(mo_stack *stack);
int mo_stack_top(mo_stack *stack);
void *mo_stack_element(mo_stack *stack, int offset);

#endif
