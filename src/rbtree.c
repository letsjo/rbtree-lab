#include "rbtree.h"
#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nil = (node_t*)calloc(1, sizeof(node_t));

  nil->color = RBTREE_BLACK;

  p -> root = p -> nil = nil;
  return p;
}

node_t *rbtree_nil_init(rbtree *t) {
  t->nil->color = RBTREE_BLACK;
  t->nil->parent = t->nil;
  t->nil->left = t->nil;
  t->nil->right = t->nil;
  return t->nil;
}

void left_rotate(rbtree *t, node_t *x) {
  node_t *y = x->right;
  x->right = y->left;

  if (y->left != t->nil) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == t->nil) {
    t->root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void right_rotate(rbtree *t, node_t *x) {
  node_t *y = x->left;
  x->left = y->right;
  
  if (y->right != t->nil) {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == t->nil) {
    t->root = y;
  } else if (x == x->parent->right) {
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

void rbtree_insert_fixup(rbtree *t, node_t *z) {
  node_t *y;

  while (z->parent->color == RBTREE_RED) {
    // z의 부모가 조부모의 왼쪽 서브 트리일 경우
    if (z->parent == z->parent->parent->left) {
      y = z->parent->parent->right;
      
      // CASE 1 : 노드 z의 삼촌 y가 적색인 경우
      if (y->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      // CASE 2 : z의 삼촌 y가 흑색이며의 z가 오른쪽 자식인 경우
      else {
        if (z == z->parent->right) {
          z = z->parent;
          left_rotate(t, z);
        }
        // CASE 3 : z의 삼촌 y가 흑색이며의 z가 오른쪽 자식인 경우
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t, z->parent->parent);
      }
    }
    // z의 부모가 조부모의 왼쪽 서브 트리일 경우
    else {
      y = z->parent->parent->left;

      // CASE 4 : 노드 z의 삼촌 y가 적색인 경우
      if (y->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      // CASE 5 : z의 삼촌 y가 흑색이며의 z가 오른쪽 자식인 경우
      else {
        if (z == z->parent->left) {
          z = z->parent;
          right_rotate(t, z);
        }
        // CASE 6 : z의 삼촌 y가 흑색이며의 z가 오른쪽 자식인 경우
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        left_rotate(t, z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));
  new_node->key = key;
  new_node->left = t->nil;
  new_node->right = t->nil;
  new_node->color = RBTREE_RED;

  node_t *y = t->nil;
  node_t *x = t->root;

  while(x != t->nil){
    y = x; 
    if(new_node->key < x->key){
      x = x->left;
    }
    else{
      x = x->right;
    }
  }
  
  new_node->parent = y;

  if(y == t->nil){
    t->root = new_node;
  }
  else if(new_node->key < y->key){
    y->left = new_node;
  }
  else{
    y->right = new_node;
  }
  
  rbtree_insert_fixup(t, new_node);

  return new_node;
}

node_t *rbtree_min(const rbtree *t) {
  node_t* temp = t->root;
  while (temp->left != t->nil){
    temp = temp->left;
  }
  return temp;
}

node_t *rbtree_max(const rbtree *t) {
  node_t* temp = t->root;
  while (temp->right != t->nil){
    temp = temp->right;
  }
  return temp;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t* temp = t-> root;
  while(temp!=t->nil){
    if(temp->key == key){
      return temp;
    }

    if(temp->key>key){
      temp = temp->left;
    } else {
      temp = temp -> right;
    }
  }

  return NULL;
}

void rbtree_erase_fixup(rbtree *t, node_t *x) {
  while (x != t->root && x->color == RBTREE_BLACK) {
    // CASE 1 ~ 4 : LEFT CASE
    if (x == x->parent->left){
      node_t *w = x->parent->right;
      
      // CASE 1 : x의 형제 w가 적색인 경우
      if (w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t, x->parent);
        w = x->parent->right;
      }

      // CASE 2 : x의 형제 w는 흑색이고 w의 두 지식이 모두 흑색인 경우
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }

      // CASE 3 : x의 형제 w는 흑색, w의 왼쪽 자식은 적색, w의 오른쪽 자신은 흑색인 경우
      else{ 
        if (w->right->color == RBTREE_BLACK) {
            w->left->color = RBTREE_BLACK;
            w->color = RBTREE_RED;
            right_rotate(t, w);
            w = x->parent->right;
        }

        // CASE 4 : x의 형제 w는 흑색이고 w의 오른쪽 자식은 적색인 경우
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(t, x->parent);
        x = t->root;
      }
    }
    // CASE 5 ~ 8 : RIGHT CASE
    else {
      node_t *w = x->parent->left;

      // CASE 5 : x의 형제 w가 적색인 경우
      if (w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t, x->parent);
        w = x->parent->left;
      }

      // CASE 6 : x의 형제 w는 흑색이고 w의 두 지식이 모두 흑색인 경우
      if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }

      // CASE 7 : x의 형제 w는 흑색, w의 왼쪽 자식은 적색, w의 오른쪽 자신은 흑색인 경우
      else 
      {
          if (w->left->color == RBTREE_BLACK) {
            w->right->color = RBTREE_BLACK;
            w->color = RBTREE_RED;
            left_rotate(t, w);
            w = x->parent->left;
            }

        // CASE 8 : x의 형제 w는 흑색이고 w의 오른쪽 자식은 적색인 경우
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t, x->parent);
        x = t->root;
      }
    }
  }

  x->color = RBTREE_BLACK;
}

void rbtree_transplant(rbtree *t, node_t *eraseNode, node_t *child) {
  if (eraseNode -> parent == t->nil){
    t->root = child;
  } else if (eraseNode == eraseNode->parent->left){
    eraseNode->parent->left = child;
  } else {
    eraseNode->parent->right=child;
  }
  child->parent = eraseNode->parent;
}

void delete_rbtree(rbtree *t) {
  node_t *curr = t->root;
  node_t *temp;
  while (curr != t->nil) {
      if (curr->left != t->nil) {
          curr = curr->left;
      }
      else if (curr->right != t->nil) {
          temp = curr->right;
          while (temp->left != t->nil) {
              temp = temp->left;
          }
          curr = temp;
      }
      else {
          temp = curr;
          curr = curr->parent;
          if (curr != t->nil && temp == curr->left) {
              curr->left = t->nil;
          } else if (curr != t->nil && temp == curr->right) {
              curr->right = t->nil;
          }
          free(temp);
      }
  }

  free(t->nil);
  free(t);
}

int rbtree_erase(rbtree *t, node_t *p) {
  node_t *temp = p;
  node_t *child = t->nil;
  color_t target_color = temp->color;

  if(temp -> left == t->nil){
    child = p->right;
    rbtree_transplant(t,p,p->right);
  } else if (temp -> right == t->nil){
    child = p->left;
    rbtree_transplant(t,p,p->left);
  } else {
    temp = p->right;

    while(temp->left != t->nil){
      temp = temp->left;
    }

    target_color = temp -> color;
    child = temp -> right;

    if (temp->parent == p){
      child -> parent = temp;
    } else {
      rbtree_transplant(t,temp,temp->right);
      temp->right=p->right;
      temp->right->parent = temp;
    }

    rbtree_transplant(t,p,temp);
    temp->left = p->left;
    temp->left->parent = temp;
    temp->color = p->color;
  }

  if (target_color == RBTREE_BLACK){
    rbtree_erase_fixup(t,child);
  }

  free(p);

  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  node_t *curr = rbtree_min(t);
  int i = 0;
  while (curr != t->nil && i < n) {
    arr[i++] = curr->key;
    if (curr->right != t->nil) {
      curr = curr->right;
      while (curr->left != t->nil) {
        curr = curr->left;
      }
    } else {
      while (curr->parent != t->nil && curr == curr->parent->right) {
        curr = curr->parent;
      }
      curr = curr->parent;
    }
  }

  return 0;
}
