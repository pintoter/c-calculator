#include "s21_smartcalc.h"

void push(stack **head, lexeme lex) {
  stack *node = (stack *)calloc(1, sizeof(stack));
  if (node != NULL) {
    node->l = lex;
    node->next = *head;
    *head = node;
  }
}

int is_empty(stack *head) { return head == NULL; }

int is_next_empty(stack *head) { return head->next == NULL; }

lexeme peek(stack *head) {
  lexeme res = {0};
  if (!is_empty(head)) {
    res = head->l;
  }
  return res;
}

lexeme pop(stack **head) {
  lexeme res = {0};
  stack *node = NULL;
  if (*head != NULL) {
    res = (*head)->l;
    node = *head;
    *head = (*head)->next;
    free(node);
  }
  return res;
}