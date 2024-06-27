// #include <bits/stdc++.h>
// #define long long int
// using namespace std;

// Vertex* find(Vertex*& root, int key) {
// //   Vertex* v = root;
// //   Vertex* last = root;
// //   Vertex* next = NULL;
// //   while (v != NULL) {
// //     if (v->key >= key && (next == NULL || v->key < next->key)) {
// //       next = v;
// //     }
// //     last = v;
// //     if (v->key == key) {
// //       break;      
// //     }
// //     if (v->key < key) {
// //       v = v->right;
// //     } else {
// //       v = v->left;
// //     }
// //   }
// //   splay(root, last);
// //   return next;
//     Vertex* n = root;
//     Vertex* ans = root;
//     Vertex* null = NULL;
//     Vertex* r = n->right;
//     Vertex* l = n->left;
//     check = false;
//     if(n == NULL || n->key == key) return n;
//     while(n!=NULL && n->key == key){
//         if(key > n->key){
//             if(n->right == NULL) return null;
//             n = n->right;
//             r = n->right;
//             l = n->left;
//             check = false;
//         }
//         if(!check) ans = n;
//         n = n->left;
//         r = n->right;
//         l = n->left;
//         check = true;

//     }
//     // if(r == NULL || l == NULL){
//     //     if(r == NULL && l == NULL){
//     //         return (r->key > key)? r : null;
//     //     }
//     //     else if(r == NULL) return null;
//     //     else return r;
//     // }

// }
// bool find(int x) {  
//   Vertex* ansV = find(root, x);
//   return (ansV != NULL && ansV->key == x);
// }

// const int MODULO = 1000000001;

// int main(){
//   int n;
//   scanf("%d", &n);
//   int last_sum_result = 0;
//   for (int i = 0; i < n; i++) {
//     char buffer[10];
//     scanf("%s", buffer);
//     char type = buffer[0];
//     switch (type) {
//       case '+' : {
//         int x;
//         scanf("%d", &x);
//         insert((x + last_sum_result) % MODULO);
//       } break;
//       case '-' : {
//         int x;
//         scanf("%d", &x);
//         erase((x + last_sum_result) % MODULO);
//       } break;            
//       case '?' : {
//         int x;
//         scanf("%d", &x);
//         printf(find((x + last_sum_result) % MODULO) ? "Found\n" : "Not found\n");
//       } break;
//       case 's' : {
//         int l, r;
//         scanf("%d %d", &l, &r);
//         int res = sum((l + last_sum_result) % MODULO, (r + last_sum_result) % MODULO);
//         printf("%lld\n", res);
//         last_sum_result = int(res % MODULO);
//       }
//     }
//   }
//   return 0;
// }
